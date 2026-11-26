const fs = require('fs');
const {
  Document, Packer, Paragraph, TextRun, HeadingLevel, AlignmentType, Table, TableRow, TableCell,
  WidthType, ShadingType, BorderStyle, LevelFormat, Footer, PageNumber, PageBreak, TabStopType,
} = require('docx');

const book = JSON.parse(fs.readFileSync('toc.json', 'utf8'));

// ---------- house fonts & colors ----------
const SERIF = 'Noto Serif', SANS = 'Noto Sans', MONO = 'Noto Sans Mono';
const INK = '1B1F24', NAVY = '1B2A4A', MUTED = '5A6270';
const CONTENT_W = 9638; // A4 (11906) minus 2 x 1134 (2 cm) margins

// ---------- inline markup: `code`, **bold**, *italic* ----------
function runs(text, base = {}) {
  const out = [];
  const re = /(`[^`]+`|\*\*[^*]+\*\*|\*[^*]+\*)/g;
  let last = 0, m;
  while ((m = re.exec(text)) !== null) {
    if (m.index > last) out.push(new TextRun({ text: text.slice(last, m.index), ...base }));
    const tok = m[0];
    if (tok.startsWith('`')) out.push(new TextRun({ text: tok.slice(1, -1), font: MONO, size: 19, ...base, ...(base.font ? {} : {}), }));
    else if (tok.startsWith('**')) out.push(new TextRun({ text: tok.slice(2, -2), bold: true, ...base }));
    else out.push(new TextRun({ text: tok.slice(1, -1), italics: true, ...base }));
    last = m.index + tok.length;
  }
  if (last < text.length) out.push(new TextRun({ text: text.slice(last), ...base }));
  return out;
}
const P = (text, opts = {}) => new Paragraph({ children: runs(text, opts.run || {}), ...opts.para });
const H1 = (t) => new Paragraph({ heading: HeadingLevel.HEADING_1, children: [new TextRun(t)] });
const H2 = (t) => new Paragraph({ heading: HeadingLevel.HEADING_2, children: [new TextRun(t)] });
const H3 = (t) => new Paragraph({ heading: HeadingLevel.HEADING_3, children: runs(t) });
const B = (t, lvl = 0) => new Paragraph({ numbering: { reference: 'bullets', level: lvl }, children: runs(t) });
const N = (t, ref = 'steps') => new Paragraph({ numbering: { reference: ref, level: 0 }, children: runs(t) });
const pageBreak = () => new Paragraph({ children: [new PageBreak()] });

// ---------- blocks ----------
function codeBlock(lines, title) {
  const out = [];
  if (title) out.push(new Paragraph({ spacing: { before: 120, after: 0 }, keepNext: true,
    children: [new TextRun({ text: title, font: SANS, size: 17, bold: true, color: MUTED })] }));
  lines.forEach((l, i) => {
    const num = String(i + 1).padStart(2, ' ');
    out.push(new Paragraph({
      shading: { type: ShadingType.CLEAR, fill: 'F4F5F7', color: 'auto' },
      border: { left: { style: BorderStyle.SINGLE, size: 12, color: '8A94A6', space: 6 } },
      spacing: { before: 0, after: 0, line: 260 }, keepLines: true, keepNext: i < lines.length - 1,
      indent: { left: 120 },
      children: [new TextRun({ text: num + '  ', font: MONO, size: 18, color: '9AA1AC' }),
                 new TextRun({ text: l || ' ', font: MONO, size: 19, color: INK })],
    }));
  });
  out.push(new Paragraph({ spacing: { before: 0, after: 120 }, children: [] }));
  return out;
}
function terminalBlock(lines) {
  const out = [new Paragraph({ spacing: { before: 120, after: 0 }, keepNext: true,
    children: [new TextRun({ text: 'Fedora terminal', font: SANS, size: 17, bold: true, color: MUTED })] })];
  lines.forEach((l, i) => {
    const isCmd = l.startsWith('$ ');
    const children = isCmd
      ? [new TextRun({ text: '$ ', font: MONO, size: 19, color: '7EE787', bold: true }),
         new TextRun({ text: l.slice(2), font: MONO, size: 19, color: 'F0F3F6' })]
      : [new TextRun({ text: l || ' ', font: MONO, size: 19, color: 'C9D1D9' })];
    out.push(new Paragraph({
      shading: { type: ShadingType.CLEAR, fill: '22272E', color: 'auto' },
      spacing: { before: 0, after: 0, line: 260 }, keepLines: true, keepNext: i < lines.length - 1,
      indent: { left: 120, right: 120 }, children,
    }));
  });
  out.push(new Paragraph({ spacing: { before: 0, after: 120 }, children: [] }));
  return out;
}
function outputBlock(lines) {
  const out = [new Paragraph({ spacing: { before: 120, after: 0 }, keepNext: true,
    children: [new TextRun({ text: 'Output', font: SANS, size: 17, bold: true, color: MUTED })] })];
  lines.forEach((l, i) => out.push(new Paragraph({
    shading: { type: ShadingType.CLEAR, fill: 'FBFAF4', color: 'auto' },
    border: { left: { style: BorderStyle.DOTTED, size: 12, color: 'B8A96A', space: 6 } },
    spacing: { before: 0, after: 0, line: 260 }, indent: { left: 120 }, keepNext: i < lines.length - 1,
    children: [new TextRun({ text: l || ' ', font: MONO, size: 19, color: INK })],
  })));
  out.push(new Paragraph({ spacing: { before: 0, after: 120 }, children: [] }));
  return out;
}
const BOXES = {
  'Why this exists':       { c: '1F5FAD', f: 'EAF1FB' },
  'Under the hood':        { c: '5B3E96', f: 'F1ECF8' },
  'Common misconception':  { c: 'B42318', f: 'FDECEA' },
  'Precisely speaking':    { c: '0F6E6E', f: 'E7F4F4' },
  'History':               { c: '8A5A00', f: 'FBF3E4' },
  'On the metal (AVR / ESP32)': { c: '2E7D32', f: 'EAF5EA' },
  'In orbit':              { c: NAVY,     f: 'E9ECF3' },
};
function box(label, paras) {
  const { c, f } = BOXES[label];
  const common = {
    shading: { type: ShadingType.CLEAR, fill: f, color: 'auto' },
    border: { left: { style: BorderStyle.SINGLE, size: 24, color: c, space: 8 } },
    indent: { left: 160, right: 160 },
  };
  const out = [new Paragraph({ ...common, spacing: { before: 160, after: 40 }, keepNext: true,
    children: [new TextRun({ text: label.toUpperCase(), font: SANS, size: 17, bold: true, color: c, characterSpacing: 20 })] })];
  paras.forEach((t, i) => out.push(new Paragraph({ ...common,
    spacing: { before: 0, after: i === paras.length - 1 ? 160 : 60 }, keepNext: i < paras.length - 1, children: runs(t) })));
  return out;
}

// ---------- tables ----------
const cellBorder = { style: BorderStyle.SINGLE, size: 4, color: 'C8CDD4' };
function table(widths, header, rows, opts = {}) {
  const total = widths.reduce((a, b) => a + b, 0);
  const mk = (txt, w, isHead, fill) => new TableCell({
    width: { size: w, type: WidthType.DXA },
    borders: { top: cellBorder, bottom: cellBorder, left: cellBorder, right: cellBorder },
    shading: isHead ? { type: ShadingType.CLEAR, fill: 'E4E8EE', color: 'auto' }
                    : (fill ? { type: ShadingType.CLEAR, fill, color: 'auto' } : undefined),
    margins: { top: 60, bottom: 60, left: 100, right: 100 },
    children: [new Paragraph({ spacing: { before: 0, after: 0 },
      children: runs(String(txt), isHead ? { bold: true, font: SANS, size: 19 } : { size: opts.size || 20 }) })],
  });
  return new Table({
    width: { size: total, type: WidthType.DXA }, columnWidths: widths,
    rows: [
      new TableRow({ tableHeader: true, children: header.map((h, i) => mk(h, widths[i], true)) }),
      ...rows.map((r) => new TableRow({ cantSplit: true,
        children: r.cells.map((t, i) => mk(t, widths[i], false, r.fill)) })),
    ],
  });
}
const gap = () => new Paragraph({ spacing: { before: 0, after: 120 }, children: [] });

// ---------- content ----------
const allChapters = [...book.front, ...book.parts.flatMap(p => p.chapters), ...book.back];
const nSections = allChapters.reduce((a, c) => a + c.sections.length, 0);
const children = [];

// Title page
children.push(
  new Paragraph({ spacing: { before: 2600, after: 0 }, alignment: AlignmentType.LEFT,
    children: [new TextRun({ text: 'Analytical C', font: SERIF, size: 72, bold: true, color: NAVY })] }),
  new Paragraph({ spacing: { before: 60, after: 400 },
    children: [new TextRun({ text: 'A deeper understanding', font: SERIF, size: 36, italics: true, color: MUTED })] }),
  new Paragraph({ border: { bottom: { style: BorderStyle.SINGLE, size: 8, color: NAVY, space: 1 } }, spacing: { after: 400 }, children: [] }),
  new Paragraph({ spacing: { after: 120 }, children: [new TextRun({ text: 'Book Index', font: SANS, size: 32, bold: true, color: INK })] }),
  new Paragraph({ spacing: { after: 600 }, children: [new TextRun({ text: 'Table of Contents · House Style · Revision Log', font: SANS, size: 24, color: MUTED })] }),
  new Paragraph({ spacing: { after: 60 }, children: [new TextRun({ text: 'Serajus, written with Claude', font: SERIF, size: 24, color: INK })] }),
  new Paragraph({ spacing: { after: 60 }, children: [new TextRun({ text: 'Version 1.16 · Approved November 24, 2026', font: SERIF, size: 22, color: MUTED })] }),
  new Paragraph({ children: [new TextRun({ text: `${allChapters.length} chapters · ${nSections} sections`, font: SERIF, size: 22, color: MUTED })] }),
  pageBreak(),
);

// 1. About
children.push(H1('1. About This Index'));
children.push(P('This document governs the whole book. It holds the approved Table of Contents, the house style that every section file must follow, and a log of every change made after approval. When a section is written, it is written against this index; when this index changes, the change is recorded in Part 6.'));
children.push(B('**Part 2** gives the book at a glance: every chapter, its part and its number of sections.'));
children.push(B('**Part 3** fixes the language baseline and the three machines on which every idea is tested.'));
children.push(B('**Part 4** is the house style: files, the anatomy of a section, typography, code, boxes, claims and sources, visuals and workflow.'));
children.push(B('**Part 5** is the detailed Table of Contents: for each section, its reference, file name, dependencies and the branches it must explore.'));
children.push(B('**Part 6** is the revision log.'));
children.push(P('Facts named in Part 5 (version numbers, dates, behaviors) are topics to be verified when their section is written, not claims already settled.', { run: { italics: true, color: MUTED } }));

// 2. At a glance
children.push(pageBreak(), H1('2. The Book at a Glance'));
const glanceRows = [];
const addCh = (c, partLabel) => glanceRows.push({ cells: [c.num, c.title, String(c.sections.length), partLabel] });
book.front.forEach(c => addCh(c, 'Preliminary'));
book.parts.forEach(p => {
  glanceRows.push({ fill: 'F1F3F7', cells: ['', `**${p.id} — ${p.title}**`, '', ''] });
  p.chapters.forEach(c => addCh(c, p.id));
});
book.back.forEach(c => addCh(c, 'Reference'));
glanceRows.push({ fill: 'F1F3F7', cells: ['', '**Total**', `**${nSections}**`, ''] });
children.push(table([800, 5938, 1300, 1600], ['Ch.', 'Title', 'Sections', 'Part'], glanceRows));
children.push(gap());
children.push(P('**Order of dependence.** The machine → why C exists and how a program is built → data → expressions → control → functions and program structure → memory → structured data → the outside world → correctness and reliability → the metal, and beyond. Every “Builds on” reference in Part 5 points backward; none points forward.'));

// 3. Baseline
children.push(pageBreak(), H1('3. Language Baseline and Machines'));
children.push(H2('3.1 The C standard taught'));
children.push(B('**Primary baseline: C23**, as GCC 15 compiles it by default on Fedora (`-std=gnu23`). Strict standard behavior is shown with `-std=c23 -pedantic`.'));
children.push(B('**Earlier standards are marked where they differ.** Each difference from C99, C11 or C17 appears in a *Precisely speaking* box naming the version.'));
children.push(B('**Two embedded toolchains, compared honestly.** The Arduino IDE ships an older avr-gcc (7.3.0, default dialect GNU C11; sketches compiled as C++). Bare-metal work uses Fedora’s current avr-gcc. Where the same source is judged differently, the book shows it.'));
children.push(H2('3.2 The three machines'));
children.push(P('Every important idea is examined on three very different machines, because seeing one program behave on all three is what separates the C language from any single implementation of it.'));
children.push(table([1800, 2612, 2613, 2613], ['', 'Laptop', 'Arduino Uno', 'ESP32'], [
  { cells: ['CPU', 'x86-64', 'AVR ATmega328P (8-bit)', 'Xtensa LX6 (32-bit, dual-core)'] },
  { cells: ['Environment', 'Hosted: Fedora Linux', 'Freestanding: bare metal', 'FreeRTOS under ESP-IDF'] },
  { cells: ['Size of `int`', '32 bits', '16 bits', '32 bits'] },
  { cells: ['Notable traits', 'Virtual memory, rich OS', '2 KB SRAM, no hardware divide', 'Single-precision FPU, Wi-Fi'] },
  { cells: ['Toolchain', 'gcc (GCC 15)', 'avr-gcc + avr-libc, avrdude', 'ESP-IDF (xtensa gcc)'] },
], { size: 19 }));
children.push(P('Details in this table are verified again in the sections that rely on them.', { run: { italics: true, color: MUTED, size: 19 } }));

// 4. House style
children.push(pageBreak(), H1('4. House Style'));

children.push(H2('4.1 Files and naming'));
children.push(N('One section = one topic = one file, however long the file becomes.', 'n41'));
children.push(N('File name: `CC-ChapterName-SS-SectionName.docx`, where CC and SS are two-digit, zero-padded numbers.', 'n41'));
children.push(N('Words are joined by hyphens; characters such as `: / * & ’` are dropped or spelled out (“&” becomes “and”, “C++” becomes “Cpp”). Each name part is at most about 40 characters.', 'n41'));
children.push(N('The book folder holds `_index.docx` (this file), `_sources/` (resources and their list), `_Analytical-C-Lab/` (the reader’s experiments, one subfolder per section, e.g. `00-02/`), `_build/` (the converter, section drafts and figure sources that produce the files; see its README), and the section files.', 'n41'));
children.push(P('Example: `16-Iteration-03-Floating-Point-Control-Variables.docx`'));

children.push(H2('4.2 The anatomy of a section'));
children.push(P('Every section file follows this order. Parts marked “where relevant” are left out when they would be empty or forced.'));
[
  '**Title block**: the section reference and title (e.g. “§16.03 Floating-Point Control Variables”), with the chapter and part beneath it.',
  '**Builds on**: the earlier sections this one depends on, by reference.',
  '**The question**: the problem, puzzle or experiment that makes the topic necessary.',
  '**The journey**: the narrative, from intuition to mechanism to the precise rule, with boxes placed where they serve it.',
  '**Terms introduced**: each new term with a one-line definition, for review and memory.',
  '**Self-check**: questions that test understanding, not recall.',
  '**Experiments**: change, predict, run, explain, on Fedora.',
  '**Hands-on (AVR / ESP32)**, where relevant: a small hardware project that reveals the mechanism.',
  '**Answers**: to the self-check and the experiments’ predictions, with reasoning.',
  '**Sources and verification**: the standard clauses, manuals and datasheets relied on; the toolchains on which programs were run; and which statements are the author’s inference.',
].forEach(t => children.push(N(t, 'n42')));

children.push(H2('4.3 Page and typography'));
children.push(table([3000, 6638], ['Element', 'Setting'], [
  { cells: ['Page', 'A4, margins 2 cm, page numbers in the footer'] },
  { cells: ['Body text', `${SERIF}, 11 pt, line spacing 1.15`] },
  { cells: ['Headings', `${SANS}, bold, dark navy; three levels within a section`] },
  { cells: ['Code, commands, output', `${MONO}, 9.5 pt`] },
  { cells: ['Inline code', 'Monospace in running text, e.g. `counter <= 1.00`'] },
  { cells: ['New terms', '**Bold** at first appearance, with the definition in the same sentence'] },
  { cells: ['Emphasis', '*Italic*, used sparingly'] },
], { size: 19 }));

children.push(H2('4.4 Code, terminal and output blocks'));
children.push(B('Every program is complete and compiles as shown. Its first line is a comment naming its file.'));
children.push(B('Listings carry line numbers, so the text can refer to “line 6”. Indentation is 4 spaces, the brace opens on the same line, and braces are used even for single statements.'));
children.push(B('Commands appear in a separate terminal block, with each command preceded by `$`, and each command explained in the text.'));
children.push(B('Output is shown exactly as produced by an actual run, never typed from expectation. The toolchain and machine are named.'));
children.push(P('The three blocks look like this:'));
children.push(...codeBlock([
  '// float_counter.c',
  '#include <stdio.h>',
  '',
  'int main(void) {',
  '    for (double x = 0.0; x <= 1.00; x += 0.05) {',
  '        printf("%.17f\\n", x);',
  '    }',
  '}',
], 'Listing 16.03-1  A floating-point control variable'));
children.push(...terminalBlock([
  '$ gcc -std=c23 -Wall -Wextra float_counter.c -o float_counter',
  '$ ./float_counter | tail -n 2',
]));
children.push(...outputBlock(['0.90000000000000024', '0.95000000000000029']));

children.push(H2('4.5 Recurring boxes'));
children.push(P('Boxes are placed inside the journey where the reader needs them, never gathered at the end. Each has one purpose:'));
children.push(...box('Why this exists', ['The problem that forced the idea into being, and what life was like before it.']));
children.push(...box('Under the hood', ['What the compiler, linker, CPU or hardware actually does: registers, instructions, memory, signals.']));
children.push(...box('Common misconception', ['A wrong belief stated plainly, why it is tempting, and the precise correction.']));
children.push(...box('Precisely speaking', ['Exactly what the C standard says, naming the version and clause (e.g. C23 §6.8.5), or what a named implementation does. Fact, separated from narrative.']));
children.push(...box('History', ['Who needed the idea, when, and why; the people and machines behind it.']));
children.push(...box('On the metal (AVR / ESP32)', ['How the topic behaves on a microcontroller: memory limits, registers, timing, toolchain differences.']));
children.push(...box('In orbit', ['Why the topic matters to spacecraft and satellite systems: reliability, radiation, power and scarce resources.']));

children.push(H2('4.6 Claims, sources and precision'));
children.push(B('Every factual claim is either verified against a primary source (the standard, GCC or avr-libc manuals, ABI documents, datasheets) or tested by running a program.'));
children.push(B('Four kinds of statement are kept visibly apart: **established fact** (documented outside the standard, with its source named), **the standard** (what C requires), **the implementation** (what a named toolchain on a named machine does), and **inference** (the author’s reasoning, labeled as such).'));
children.push(B('Where the author is unsure, the text says so. Nothing is quietly guessed.'));
children.push(B('Outside knowledge and research are listed in the section’s *Sources and verification*. Nothing is copied from any book; quotations, where unavoidable, are short and attributed.'));

children.push(H2('4.7 Visuals'));
children.push(table([2600, 7038], ['Kind', 'Used for'], [
  { cells: ['Tables', 'Comparisons, truth tables, type sizes across machines, differences between standards'] },
  { cells: ['Circuit schematics', 'Gates, adders, latches, pin wiring'] },
  { cells: ['Bit-field diagrams', 'Which bits mean what: floats, masks, registers'] },
  { cells: ['Memory diagrams', 'Bytes at addresses, stack frames, program sections, memory maps'] },
  { cells: ['Flowcharts and graphs', 'Control flow, linker resolution, dependency order'] },
  { cells: ['Timing diagrams', 'Signals over time: timers, UART frames'] },
  { cells: ['Plots from real data', 'Results of the book’s own programs; the program is printed so the reader can reproduce it'] },
  { cells: ['Annotated code and assembly', 'C placed beside the machine code it becomes'] },
], { size: 19 }));
children.push(gap());
children.push(B('Every visual is drawn freshly for this book in one consistent style. No photographs or copied images; where a real photograph would help, the text says what to look at and points to the official source.'));
children.push(B('A visual appears only where it explains something words explain poorly. Most are drawn as plain boxes and arrows that are easy to copy with a stylus; for an intricate figure, the text says which part is worth copying.'));

children.push(H2('4.8 Cross-references and numbering'));
children.push(B('Sections: **§CC.SS**, e.g. §16.03. These references never change once approved.'));
children.push(B('Within a section: Listing 16.03-1, Figure 16.03-1, Table 16.03-1, numbered in order of appearance.'));
children.push(B('A forward reference (“we return to this in §24.06”) is allowed as a signpost, but a section never *depends* on a later one.'));

children.push(H2('4.9 Language and tone'));
children.push(B('Plain, precise English; every technical term defined when it first appears; familiar everyday examples before abstract ones.'));
children.push(B('Storytelling in the manner of a ground-up textbook: the reader is led through a journey to the concept, not handed a list of facts. Standards and rules appear when the story needs them, not as the main theme.'));
children.push(B('Intuition before formulas; the reason a concept exists before the procedure for using it; and the meaning of every symbol explained.'));
children.push(B('Mistakes and misconceptions are named plainly and corrected precisely.'));
children.push(B('American English spelling throughout (behavior, organize, meter, gray), and dates written month first (November 24, 2026). Punctuation stays logical: a period or comma goes inside quotation marks only when it belongs to the quoted text, so that quoted code and commands are never altered.'));

children.push(H2('4.10 Workflow'));
children.push(N('Sections are written strictly one at a time, in order, each reviewed before the next begins.', 'n410'));
children.push(N('The first section written is a sample; its depth, length and layout are reviewed before the rest follow that form.', 'n410'));
children.push(N('Any change to this index after approval (a new section, a changed scope, a style rule) is entered in the revision log.', 'n410'));

// 5. Detailed TOC
children.push(pageBreak(), H1('5. Detailed Table of Contents'));
children.push(P('Each entry gives the section’s reference and title, its file name, the sections it builds on, and the branches it must explore. The bullets set the section’s scope; they are not its final headings.'));
function chapterBlock(c) {
  children.push(new Paragraph({ heading: HeadingLevel.HEADING_2, pageBreakBefore: false,
    children: [new TextRun(`Chapter ${c.num} — ${c.title}`)] }));
  c.sections.forEach(s => {
    children.push(new Paragraph({ heading: HeadingLevel.HEADING_3,
      children: [new TextRun({ text: `§${s.ref}`, color: '1F5FAD' }), new TextRun({ text: '   ' }), ...runs(s.title)] }));
    children.push(new Paragraph({ spacing: { before: 0, after: 20 }, keepNext: true,
      children: [new TextRun({ text: 'File  ', font: SANS, size: 17, bold: true, color: MUTED }),
                 new TextRun({ text: s.file, font: MONO, size: 17, color: MUTED })] }));
    if (s.builds) children.push(new Paragraph({ spacing: { before: 0, after: 60 }, keepNext: s.bullets.length > 0,
      children: [new TextRun({ text: 'Builds on  ', font: SANS, size: 17, bold: true, color: MUTED }),
                 new TextRun({ text: s.builds, font: SANS, size: 17, color: MUTED })] }));
    s.bullets.forEach(b => children.push(B(b.text, Math.min(b.lvl, 1))));
  });
}
const partBanner = (t, brk = true) => new Paragraph({ pageBreakBefore: brk, spacing: { before: brk ? 0 : 360, after: 200 },
  border: { bottom: { style: BorderStyle.SINGLE, size: 8, color: NAVY, space: 4 } },
  children: [new TextRun({ text: t, font: SANS, size: 30, bold: true, color: NAVY })] });
children.push(partBanner('Preliminary', false));
book.front.forEach(chapterBlock);
book.parts.forEach(p => { children.push(partBanner(`${p.id} — ${p.title}`)); p.chapters.forEach(chapterBlock); });
children.push(partBanner('Reference'));
book.back.forEach(chapterBlock);

// 6. Revision log
children.push(pageBreak(), H1('6. Revision Log'));
children.push(P('Every change after approval is entered here, newest last.'));
children.push(table([1300, 1900, 6438], ['Version', 'Date', 'Change'], [
  { cells: ['1.0', 'Nov 24, 2026', `Table of Contents approved: ${allChapters.length} chapters, ${nSections} sections. House style, naming rules, language baseline and visual rules established.`] },
  { cells: ['1.1', 'Nov 24, 2026', 'Folder layout: `_Analytical-C-Lab/` added for experiments. §00.02 updated: lab path changed to match; Table 00.02-2 now records GCC 16.2.1 on Fedora 44 printing 202311 (run by the reader).'] },
  { cells: ['1.2', 'Nov 24, 2026', 'Folder layout: `_build/` added, holding the converter, section drafts, figure sources and programs, so that any later session can rebuild the files identically.'] },
  { cells: ['1.3', 'Nov 24, 2026', 'Proofreading of Chapter 00 (author’s pass and an independent review). §00.01: four kinds of statement (established fact added); compile-time folding of 0.1 + 0.2 stated; `double` is 32-bit on avr-gcc; C23 macro `__STDC_IEC_60559_BFP__`; Patriot account made precise and its return fixed at §07.08; Experiment 00.01-3 uses `%.70f`; ESP32 identified as the original Xtensa LX6 part; Figure 00.01-1 relabelled. §00.02: Arduino IDE and ESP32 board package added; exact `file` output; warnings, `-std=c23`, `-pedantic`, `__STDC_HOSTED__` and error-position explanations corrected; VS Code install now `dnf install --refresh code`; `dnf search` fields; avr-gcc 15.3 on Fedora; long commands split. House style: four kinds of statement; short tables kept on one page. TOC: §00.02 bullet 4 and §03.02 bullet 2 corrected.'] },
  { cells: ['1.4', 'Nov 25, 2026', 'House style: American English spelling, month-first dates, comma thousands separators; applied to §00.01, §00.02, §01.01 and the TOC (e.g. Four Kinds of Behavior, A Catalog of Undefined Behavior). Proofreading of §01.01 (author’s pass and an independent review): ESP32-to-Uno logic levels corrected (2.64 V guaranteed, below the 3.0 V threshold; level shifter); ATmega328P VOH at 3 V is 2.3 V (HIGH margin 0.5 V); ENIAC and von Neumann history corrected (two-state elements grouped in tens); SRAM cell, SSD charge trap, voltage definition, single-event-upset mechanism and Figure 01.01-3 made precise; ESP32 variant and safety notes added to the hands-on. TOC: §01.01 builds on §00.01, §00.02. Converter: listings up to 50 lines and terminal blocks kept with what follows; long box paragraphs may break.'] },
  { cells: ['1.5', 'Nov 25, 2026', 'Proofreading of §01.02, §01.03 and §01.04 (author’s pass and an independent review of each). §01.02: cross-references corrected (§09.01 and §02.03 for pure functions, §35.01 for latch-up, §36.03 for the pin circuitry); MOSFET blocking mechanism (two back-to-back junctions), the weak HIGH of nMOS, Shannon’s hindrance notation and the 74HC00’s buffered gates made precise; Figures 01.02-1 and 01.02-3 redrawn; expected hands-on output, a decoupling capacitor and an ESP32 note added. §01.03: §20.01 for file scope; Self-check 6 and Experiment 01.03-1 answers corrected; carry rows aligned; Listing 01.03-3 now measures true carry propagation (128 pairs, one in 512, travel all eight stages); flags described for processors that keep them (RISC-V and Xtensa keep none); AVR SUB flag rules sourced to the Instruction Set Manual; Figure 01.03-2 junction dot moved. §01.04: hands-on latch sketch corrected so that the power-up line shows the real race (pull-up resistors; HIGH written before OUTPUT); EEPROM wear time corrected to about 5.5 minutes (3.3 ms per write); `inc` acknowledged; ceramic resonator, hold time, scrubbing write-back, DDR4 temperature limit, MMU translation and cross-references (§13.05, §35.03, §37.03, §27.02) corrected; Figures 01.04-5, -6 and -8 redrawn. TOC: §01.04 builds on §01.02, §01.03, and its bullets now name metastability, DRAM and the compiler’s view of a variable; §39.02 gains a bullet on functions without side effects.'] },
  { cells: ['1.6', 'Nov 25, 2026', 'Proofreading of §01.05 (author’s pass and an independent review). Cross-references corrected (§03.05 and §21.03 for relocation, §08.01 for character codes, §03.07, §36.05 and §16.06 for start-up code; the wrong §06.04 removed; §34.06 described as avoiding code injection, not preventing it); a broken promise that §01.06 would decode the reset vector removed. Technical corrections: memory is built from storage cells, not flip-flops; on the AVR, data becomes code only through SPM from the boot section; tests and jumps described without assuming flags (the Xtensa has none); instructions that touch data memory take two cycles; only SRAM1 (128 KB) of the ESP32 is on both buses; x86-64 traps on invalid opcodes; the reset vector shown is that of the plain C blink program, and start-up code calls main. Voyager 1 dates and the General Electric attribution made precise. Figures 01.05-1, -2 and -3 redrawn (Figure 01.05-2 now shows the instruction’s address field reaching memory). TOC: §01.05 builds on §01.02, §01.03, §01.04.'] },
  { cells: ['1.7', 'Nov 25, 2026', 'Proofreading of §01.06 (author’s pass and an independent review); Chapters 00 and 01 are now fully proofread. Corrections: x × 10 computed as 2 × (x + 4x); the Apollo Guidance Computer’s program memory (about 70 KB) is larger than the Uno’s flash, not smaller; the example of two encodings is now a true one (`add %rdi,%rax` as 48 01 f8 or 48 03 c7); padding after `add8` includes a 1-byte nop; -Wconversion gives two warnings; the chapter summary no longer claims Figure 01.06-3 follows the chapter’s order; feedback gives latches, flip-flops and registers, stored charge gives larger memories. Made precise: the one-instruction-per-line principle (pseudo-instructions), the link between LDI and avr-gcc’s register conventions (labeled as inference), clr/inc for loading 1, cycle-exact timing against the resonator’s accuracy, reset through the Uno’s bootloader, Kathleen Booth’s 1947 report and David Wheeler’s role. Figures 01.06-1 and 01.06-2 enlarged. American spelling and comma thousands throughout.'] },
  { cells: ['1.8', 'Nov 25, 2026', 'Workflow: from §02.01 on, each section is proofread immediately after it is written (author’s pass and an independent review) before the next begins; items left for the reader to confirm on GCC 15/16 are listed in `_build/proofreading/reader-confirmations.md` and checked when the reader reaches them. §02.01 written and proofread. Corrections: an `int` addition is one instruction on x86-64 and the ESP32 but two on the AVR; the UART is §37.04 (printf through it §31.06), not Chapter 36; `=+` reversed in 1976; Thompson tried FORTRAN before B; the BCPL port at Bell Labs dated 1968–69, with Ritchie among the porters; only data memory is byte-addressed on the AVR and ESP32; BNF introduced by Backus in 1959; `const` removed from the 1972-style listing (it arrived in 1989); `UBRR0` set for about 115,200 baud in double-speed mode; Experiment 02.01-3 no longer presumes an odd AVR address; the size increase of C Unix included new capabilities. Figure 02.01-3 redrawn with separate pcc and GCC front ends and pcc’s documented targets; Figure 02.01-2 labels data memory and int sizes per machine. Several historical details hedged or made precise (PDP-7 character packing, ALGOL 68 `+:=`, staged cFS release, TRIPOS dates).'] },
  { cells: ['1.9', 'Nov 25, 2026', '§02.02 written and proofread (author’s pass and an independent review). Corrections before release: the cost of `printf` measured against STEP 0 (1,454 bytes), and STEP 1’s extra bytes traced to libgcc’s division routine for `%`; an empty `main` (138 bytes) added for comparison; `text` versus `data` explained; the reason for `volatile` corrected; C23’s minimum `int` range (−32,768); operators may call support routines (division, variable shifts on the AVR); conservative garbage collectors (Boehm) acknowledged; the bounds sanitizer’s exception for a trailing array (`-fstrict-flex-arrays`); `objdump -dr` to see called names; freestanding defined by the library and start-up, not by the absence of an operating system; heap versus stack in the no-allocation rule; the Ariane 5 shutdown described as the specified response; Xtensa’s zero-extending `L8UI` as the reason for unsigned `char`. Figure 02.02-3 redrawn with each build shown separately.'] },
  { cells: ['1.10', 'Nov 26, 2026', '§02.03 written and proofread (author’s pass and an independent review). Corrections before release: the C23 clause numbers identified as those of draft N3096, with their later numbering given; the “need not evaluate” permission described as a normative paragraph, not an example; C99’s and C11’s wording of the volatile requirement distinguished; prompt-before-input stated as the standard’s intent; unspecified orders described as neither fixed nor documented; `memset_explicit` dated to glibc 2.43 and its no-removal property stated as the standard’s intention; the shared final `+ 1` in the duplicated computation, and the true windows for undetected upsets; the 35-cycle layout behind the sketch’s 437,504 µs; time described as unobservable in the core language (hosted clocks and `thrd_sleep` acknowledged); Fedora’s possible non-PIE output described. Figures 02.03-1 and 02.03-2 relabeled. §02.02: its C23 clause numbers marked as those of draft N3096.'] },
  { cells: ['1.11', 'Nov 26, 2026', '§02.04 written and proofread (author’s pass and an independent review). Corrections before release: three distinct results for `1 << 32`, not four; the image of the contract attributed to §02.02; the AVR’s division by zero described as giving a meaningless quotient (−1 for 7, +1 for a negative dividend); the “why not implementation-defined?” argument rebuilt on the optimizer’s freedom, since implementation-defined behavior may include a signal; the loop example changed to `i <= n`, where `-fwrapv` actually changes GCC’s code; Clang’s 64-bit shift described as a merged shift and widening; constraints and the three ways undefined behavior is indicated added; Annex J described as an informative overview (218 J.2 entries in N3096); P0907’s three reasons for keeping signed overflow undefined; avr-libc’s missing `setlocale` described as a conformance gap; the AVR shift loop’s low-byte count; Figure 02.04-2 relabeled.'] },
  { cells: ['1.12', 'Nov 26, 2026', '§02.05 written and proofread (author’s pass and an independent review). Corrections before release: GCC’s default changed three times, not four, and only the gnu11 and gnu23 changes needed porting advice; the Arduino IDE’s compiler is nearly nine years old; GCC 13 knows only -std=c2x, and Experiment 02.05-5 compiles with -c; the <stdbool.h> result explained by GCC’s system-header leniency; -pedantic-errors described accurately; C23’s change list attributed to Annex M; GCC 14’s 202000 described as a pre-publication value, not a measure of completeness; GCC 14 accepting a 1978-style definition under -std=c23 with only a warning (a diagnostic); wchar_t dated to C89; the names C18 and C2X added; ESP32 values conditioned on the core version; Figure 02.05-1 corrected (avr-gcc 7.3 date; the first band labeled as GNU C from 1987).'] },
  { cells: ['1.13', 'Nov 26, 2026', '§02.06 written and proofread (author’s pass and an independent review); Chapter 02 is complete. Corrections before release: <stdbit.h> and <stdbool.h> described correctly for C23; the claim that kernels are compiled with -ffreestanding withdrawn; 35 bytes of instructions, not 173; the startup code described as repeating reset values for jumps to address 0, its parts attributed to avr-libc’s crt file and libgcc; vfprintf’s writes into r6 and r7 before its flags check; the true reason Serial.flush() is needed without init(); the Uno’s Optiboot bootloader added to the chain; ld.so started by the kernel before _start; how init() leaves the program; FreeRTOS tasks referred to §38.03; -ffreestanding still relying on memcpy and its relatives; Figure 02.06-1 corrected (main task created before the scheduler starts; exit_group); GCC’s hosted default as the reason avr-gcc reports 1; vector numbering in the datasheet; forward references to §03.07 and §38.03.'] },
  { cells: ['1.14', 'Nov 26, 2026', '§03.01 written and proofread (author’s pass and an independent review). Verification: from Chapter 03 on, programs run on the reader’s own machine (found to be Fedora 45, with GCC 16.2.1, glibc 2.44, binutils 2.47 and Clang 23.1.5) through a lab runner, a systemd user service that executes job scripts placed in _Analytical-C-Lab/_runner/queue and writes their output to _runner/done; results are cross-checked in the author’s workspace (Ubuntu 24.04, GCC 14.2); AVR programs are compiled with the reader’s avr-gcc 15.3 and simulated in the workspace, since Fedora has no simavr package. Found on the way: the reader’s GCC does not build position-independent executables by default (an item left open by §02.03). Corrections before release: the binary’s string is 13 bytes, since GCC substituted puts; printf’s result does not reveal a failed buffered write, and only fflush or fclose does; the -H output and include guards explained correctly; comments described as recognized in the same pass that forms tokens; the jobs of white space limited to ordinary program text; the compiler not obliged to know printf, though GCC does; main’s privileges noted; printf replaced by puts only when its result is unused; exit status as the least significant byte; the 1978 program’s printf call undefined in C89, hence K&R’s 1988 #include; empty parentheses in C89–C17 definitions; preprocessing tokens and maximal munch; the history of // and /* */ attributed to Ritchie and Kernighan; Apple’s two updates of February 2014; the ELF difference of the AVR builds explained by the source file’s name and inlining; padding in the executable; figure 03.01-1 showing when the write happens.'] },
  { cells: ['1.15', 'Nov 26, 2026', '§03.02 written and proofread (author’s pass and an independent review); outputs from the reader’s Fedora 45 through the lab runner. It keeps §00.02’s promise to explain why cc1, as and collect2/ld run in that order. Corrections before release: GCC’s -### quotes only some arguments; the Ubuntu cross-check’s real differences stated (PIE startup files Scrt1.o/crtbeginS.o, sizes, -imultiarch needed to run cc1 by hand on Debian/Ubuntu); line markers explain the line numbering of -E output; GCC’s acceptance of CR LF described as its own choice; C23’s digit separator added to the preprocessing-number rule; trigraphs converted only in strict ISO modes before C23; the out-of-range hexadecimal escape as a constraint violation; sem.c an error only since GCC 14; collect2’s role and link-time optimization (-flto) noted; Intel HEX record fields explained; the Arduino IDE’s verbose output and avrdude described accurately. §03.01 corrected at the same time: the file avr_hello.c now matches Listing 03.01-9 as printed (746 bytes; its verbose copy 4,901), with the AVR outputs rerun on the reader’s machine.'] },
  { cells: ['1.16', 'Nov 26, 2026', '§03.02 reworked after a high-effort depth review requested by the user (the section had first been drafted at a reduced reasoning setting), then reviewed again independently. Added, all run on the reader’s Fedora: the C89 Rationale’s reasons for the phases, for line joining and for joining string literals; why a comment becomes one space (a/**/b and -traditional-cpp); Defect Report #003’s reasons for the greedy preprocessing-number rule (12abc and a macro); keywords existing only from phase 7 (#define int long) and the stray @; two character sets shown with -fexec-charset=IBM1047; a glimpse of the parse with -fdump-tree-original; the driver’s specs (startfile; avr-gcc device specs), exit statuses, temporary files, -pipe, -no-integrated-cpp and -Wl,-v; Clang’s -fno-integrated-as; “Why this order” rebuilt around the relocation hole in greet.o (objdump -dr), the alternatives tried and Ritchie’s account of B; Experiment 03.02-7 (jumps the assembler resolves); prediction self-checks; the figure redrawn. Corrected: the assembler described consistently as finishing phase 7; the purpose of phase 2; collect2’s evidence; quotations checked word for word; EBCDIC’s two newline codes; where GCC replaces printf by puts; which phase orders are dependencies and which are precedence decisions; the forced order stated as “translate each unit, then combine”.'] },
]));

// ---------- document ----------
const doc = new Document({
  creator: 'Serajus, with Claude',
  title: 'Analytical C : A deeper understanding — Book Index',
  styles: {
    default: { document: { run: { font: SERIF, size: 22, color: INK }, paragraph: { spacing: { after: 120, line: 276 } } } },
    paragraphStyles: [
      { id: 'Heading1', name: 'Heading 1', basedOn: 'Normal', next: 'Normal', quickFormat: true,
        run: { font: SANS, size: 36, bold: true, color: NAVY }, paragraph: { spacing: { before: 240, after: 200 }, keepNext: true, outlineLevel: 0 } },
      { id: 'Heading2', name: 'Heading 2', basedOn: 'Normal', next: 'Normal', quickFormat: true,
        run: { font: SANS, size: 28, bold: true, color: NAVY }, paragraph: { spacing: { before: 320, after: 120 }, keepNext: true, outlineLevel: 1 } },
      { id: 'Heading3', name: 'Heading 3', basedOn: 'Normal', next: 'Normal', quickFormat: true,
        run: { font: SANS, size: 23, bold: true, color: INK }, paragraph: { spacing: { before: 220, after: 40 }, keepNext: true, outlineLevel: 2 } },
    ],
  },
  numbering: { config: [
    { reference: 'bullets', levels: [
      { level: 0, format: LevelFormat.BULLET, text: '•', alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 360, hanging: 240 }, spacing: { after: 40 } } } },
      { level: 1, format: LevelFormat.BULLET, text: '–', alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 720, hanging: 240 }, spacing: { after: 40 } } } },
    ] },
    ...['steps', 'n41', 'n42', 'n410'].map(ref => ({ reference: ref, levels: [
      { level: 0, format: LevelFormat.DECIMAL, text: '%1.', alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 400, hanging: 300 }, spacing: { after: 60 } } } },
    ] })),
  ] },
  sections: [{
    properties: { page: { size: { width: 11906, height: 16838 }, margin: { top: 1134, bottom: 1134, left: 1134, right: 1134 } } },
    footers: { default: new Footer({ children: [new Paragraph({ alignment: AlignmentType.CENTER,
      children: [new TextRun({ text: 'Analytical C · Book Index · ', font: SANS, size: 16, color: MUTED }),
                 new TextRun({ children: [PageNumber.CURRENT], font: SANS, size: 16, color: MUTED })] })] }) },
    children,
  }],
});
Packer.toBuffer(doc).then(buf => { fs.writeFileSync('_index.docx', buf); console.log('written', buf.length); });
