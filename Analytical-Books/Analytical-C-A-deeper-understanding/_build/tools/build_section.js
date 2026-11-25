// build_section.js — converts a section source (.md, house markup) into a house-style .docx
// Usage: node build_section.js <source.md> <output.docx>
//
// House markup:
//   front matter (key: value lines) then a line '---'
//   ## / ###  headings          blank line separates paragraphs
//   - bullet  /  "  - " level 2  1. numbered (each list restarts)
//   ```c Listing CC.SS-n  Title     code with line numbers
//   ```terminal   ```output   ```text
//   :::why :::hood :::myth :::precise :::history :::metal :::orbit   ...   :::
//   Table: caption   then pipe table;  optional line  <!-- widths: 30,70 -->
//   ![Figure CC.SS-n  Caption](image.png){w=15}     (width in cm)
//   inline: `code`  **bold**  *italic*
const fs = require('fs');
const path = require('path');
const {
  Document, Packer, Paragraph, TextRun, HeadingLevel, AlignmentType, Table, TableRow, TableCell,
  WidthType, ShadingType, BorderStyle, LevelFormat, Footer, PageNumber, ImageRun, LineRuleType,
} = require('docx');

const SERIF = 'Noto Serif', SANS = 'Noto Sans', MONO = 'Noto Sans Mono';
const INK = '1B1F24', NAVY = '1B2A4A', MUTED = '5A6270';
const CONTENT_W = 9638;

const BOXES = {
  why:      { label: 'Why this exists',            c: '1F5FAD', f: 'EAF1FB' },
  hood:     { label: 'Under the hood',             c: '5B3E96', f: 'F1ECF8' },
  myth:     { label: 'Common misconception',       c: 'B42318', f: 'FDECEA' },
  precise:  { label: 'Precisely speaking',         c: '0F6E6E', f: 'E7F4F4' },
  history:  { label: 'History',                    c: '8A5A00', f: 'FBF3E4' },
  metal:    { label: 'On the metal (AVR / ESP32)', c: '2E7D32', f: 'EAF5EA' },
  orbit:    { label: 'In orbit',                   c: NAVY,     f: 'E9ECF3' },
};

function runs(text, base = {}) {
  const out = [];
  const re = /(`[^`]+`|<sub>[^<]+<\/sub>|<sup>[^<]+<\/sup>|\*\*(?:[^*]|\*[^*]+\*)+?\*\*|\*[^*\s][^*]*\*)/g;
  let last = 0, m;
  while ((m = re.exec(text)) !== null) {
    if (m.index > last) out.push(new TextRun({ text: text.slice(last, m.index), ...base }));
    const tok = m[0];
    if (tok.startsWith('`')) out.push(new TextRun({ ...base, text: tok.slice(1, -1), font: MONO, size: base.size ? base.size - 2 : 19 }));
    else if (tok.startsWith('<sub>')) out.push(...runs(tok.slice(5, -6), { ...base, subScript: true }));
    else if (tok.startsWith('<sup>')) out.push(...runs(tok.slice(5, -6), { ...base, superScript: true }));
    else if (tok.startsWith('**')) out.push(...runs(tok.slice(2, -2), { ...base, bold: true }));
    else out.push(...runs(tok.slice(1, -1), { ...base, italics: true }));
    last = m.index + tok.length;
  }
  if (last < text.length) out.push(new TextRun({ text: text.slice(last), ...base }));
  return out;
}

// ---------- parse ----------
const [src, outFile] = process.argv.slice(2);
const raw = fs.readFileSync(src, 'utf8').replace(/\r/g, '');
const [fmText, ...rest] = raw.split('\n---\n');
const body = rest.join('\n---\n');
const fm = {};
fmText.split('\n').forEach(l => { const i = l.indexOf(':'); if (i > 0) fm[l.slice(0, i).trim()] = l.slice(i + 1).trim(); });
const baseDir = path.dirname(src);

const children = [];
let listInstance = 0;
const usedNumbering = new Set();

// title block
children.push(
  new Paragraph({ spacing: { before: 0, after: 80 },
    children: [new TextRun({ text: `${fm.part}  ·  ${fm.chapter}`.toUpperCase(), font: SANS, size: 17, bold: true, color: MUTED, characterSpacing: 20 })] }),
  new Paragraph({ spacing: { before: 120, after: 40, line: 240, lineRule: LineRuleType.AUTO }, keepNext: true,
    children: [new TextRun({ text: `§${fm.ref}`, font: SANS, size: 30, bold: true, color: '1F5FAD' })] }),
  new Paragraph({ spacing: { before: 0, after: 160, line: 240, lineRule: LineRuleType.AUTO }, keepNext: true,
    children: [new TextRun({ text: fm.title, font: SERIF, size: 52, bold: true, color: NAVY })] }),
  new Paragraph({ spacing: { before: 0, after: 240 },
    border: { bottom: { style: BorderStyle.SINGLE, size: 8, color: NAVY, space: 8 } },
    children: [new TextRun({ text: 'Builds on  ', font: SANS, size: 19, bold: true, color: MUTED }),
               new TextRun({ text: fm.builds || '—', font: SANS, size: 19, color: MUTED })] }),
);

const lines = body.split('\n');
let i = 0;
let para = [];
function flushPara(extra = {}) {
  if (!para.length) return;
  const txt = para.join(' ');
  // a lead-in sentence ending in a colon stays with what it introduces
  const lead = /:\s*$/.test(txt) ? { keepNext: true } : {};
  children.push(new Paragraph({ children: runs(txt), ...lead, ...extra }));
  para = [];
}
function boxParaProps(key) {
  const b = BOXES[key];
  return {
    shading: { type: ShadingType.CLEAR, fill: b.f, color: 'auto' },
    border: { left: { style: BorderStyle.SINGLE, size: 24, color: b.c, space: 8 } },
    indent: { left: 160, right: 160 },
    keepLines: true,
  };
}
function codeLines(kind, lines, title) {
  if (title) children.push(new Paragraph({ spacing: { before: 160, after: 0 }, keepNext: true,
    children: runs(title, { font: SANS, size: 17, bold: true, color: MUTED }) }));
  if (kind === 'terminal' && !title) children.push(new Paragraph({ spacing: { before: 160, after: 0 }, keepNext: true,
    children: [new TextRun({ text: 'Fedora terminal', font: SANS, size: 17, bold: true, color: MUTED })] }));
  if (kind === 'output' && !title) children.push(new Paragraph({ spacing: { before: 160, after: 0 }, keepNext: true,
    children: [new TextRun({ text: 'Output', font: SANS, size: 17, bold: true, color: MUTED })] }));
  const width = String(lines.length).length;
  lines.forEach((l, k) => {
    const common = { spacing: { before: 0, after: 0, line: 260, lineRule: LineRuleType.AUTO }, keepLines: true,
      // keep a listing of up to 50 lines on one page; keep a terminal block
      // together with whatever follows it (normally its output)
      keepNext: (k < lines.length - 1 && lines.length <= 50) || (kind === 'terminal' && lines.length <= 50) };
    let p;
    if (kind === 'c' || kind === 'asm' || kind === 'make') {
      p = new Paragraph({ ...common,
        shading: { type: ShadingType.CLEAR, fill: 'F4F5F7', color: 'auto' },
        border: { left: { style: BorderStyle.SINGLE, size: 12, color: '8A94A6', space: 6 } }, indent: { left: 120 },
        children: [new TextRun({ text: String(k + 1).padStart(width, ' ') + '  ', font: MONO, size: 18, color: '9AA1AC' }),
                   new TextRun({ text: l || ' ', font: MONO, size: 19, color: INK })] });
    } else if (kind === 'terminal') {
      const isCmd = l.startsWith('$ ');
      p = new Paragraph({ ...common, shading: { type: ShadingType.CLEAR, fill: '22272E', color: 'auto' }, indent: { left: 120, right: 120 },
        children: isCmd
          ? [new TextRun({ text: '$ ', font: MONO, size: 19, color: '7EE787', bold: true }), new TextRun({ text: l.slice(2), font: MONO, size: 19, color: 'F0F3F6' })]
          : (l.startsWith('# ')
              ? [new TextRun({ text: l, font: MONO, size: 19, color: '8B949E', italics: true })]
              : [new TextRun({ text: l || ' ', font: MONO, size: 19, color: 'C9D1D9' })]) });
    } else if (kind === 'output') {
      p = new Paragraph({ ...common, shading: { type: ShadingType.CLEAR, fill: 'FBFAF4', color: 'auto' },
        border: { left: { style: BorderStyle.DOTTED, size: 12, color: 'B8A96A', space: 6 } }, indent: { left: 120 },
        children: [new TextRun({ text: l || ' ', font: MONO, size: 19, color: INK })] });
    } else { // text
      p = new Paragraph({ ...common, shading: { type: ShadingType.CLEAR, fill: 'F7F7F7', color: 'auto' }, indent: { left: 120 },
        children: [new TextRun({ text: l || ' ', font: MONO, size: 19, color: INK })] });
    }
    children.push(p);
  });
  children.push(new Paragraph({ spacing: { before: 0, after: 120 }, children: [] }));
}
const cellBorder = { style: BorderStyle.SINGLE, size: 4, color: 'C8CDD4' };
function pipeTable(rows, widthsPct, caption) {
  if (caption) children.push(new Paragraph({ spacing: { before: 160, after: 60 }, keepNext: true,
    children: runs(caption, { font: SANS, size: 17, bold: true, color: MUTED }) }));
  const parsed = rows.filter(r => !/^\|\s*:?-{2,}/.test(r)).map(r => r.trim().replace(/^\||\|$/g, '').split('|').map(c => c.trim()));
  const n = parsed[0].length;
  let pct = widthsPct || parsed[0].map(() => 100 / n);
  const widths = pct.map(p => Math.round(CONTENT_W * p / 100));
  widths[widths.length - 1] = CONTENT_W - widths.slice(0, -1).reduce((a, b) => a + b, 0);
  // Keep short tables (up to 12 rows) on one page; for longer ones keep
  // at least the header and the first two rows together.
  const keepRows = parsed.length <= 12 ? parsed.length - 1 : 3;
  const mk = (txt, w, head, keep) => new TableCell({
    width: { size: w, type: WidthType.DXA },
    borders: { top: cellBorder, bottom: cellBorder, left: cellBorder, right: cellBorder },
    shading: head ? { type: ShadingType.CLEAR, fill: 'E4E8EE', color: 'auto' } : undefined,
    margins: { top: 60, bottom: 60, left: 100, right: 100 },
    children: txt.split('<br>').map(t => new Paragraph({ spacing: { before: 0, after: 0 }, keepNext: keep,
      children: runs(t, head ? { bold: true, font: SANS, size: 19 } : { size: 20 }) })),
  });
  children.push(new Table({ width: { size: CONTENT_W, type: WidthType.DXA }, columnWidths: widths,
    rows: parsed.map((r, k) => new TableRow({ tableHeader: k === 0, cantSplit: true, children: r.map((c, j) => mk(c, widths[j], k === 0, k < keepRows)) })) }));
  children.push(new Paragraph({ spacing: { before: 0, after: 160 }, children: [] }));
}
function pngSize(file) {
  const b = fs.readFileSync(file);
  return { w: b.readUInt32BE(16), h: b.readUInt32BE(20), data: b };
}

let pendingWidths = null, pendingCaption = null;
while (i < lines.length) {
  const l = lines[i];
  // fenced code
  let m = l.match(/^```(\w+)\s*(.*)$/);
  if (m) {
    flushPara();
    const kind = m[1], title = m[2] || null; const buf = []; i++;
    while (i < lines.length && !lines[i].startsWith('```')) { buf.push(lines[i]); i++; }
    i++; codeLines(kind, buf, title); continue;
  }
  // box
  m = l.match(/^:::(\w+)\s*(.*)$/);
  if (m && BOXES[m[1]]) {
    flushPara();
    const key = m[1]; const b = BOXES[key]; const label = m[2] ? `${b.label}: ${m[2]}` : b.label;
    const props = boxParaProps(key);
    children.push(new Paragraph({ ...props, spacing: { before: 200, after: 60 }, keepNext: true,
      children: [new TextRun({ text: label.toUpperCase(), font: SANS, size: 17, bold: true, color: b.c, characterSpacing: 20 })] }));
    i++; const blocks = []; let cur = [];
    while (i < lines.length && !/^:::\s*$/.test(lines[i])) {
      if (lines[i].trim() === '') { if (cur.length) { blocks.push(cur); cur = []; } }
      else cur.push(lines[i]);
      i++;
    }
    if (cur.length) blocks.push(cur); i++;
    const items = [];
    blocks.forEach(bl => {
      if (bl.every(x => /^\s*- /.test(x))) bl.forEach(x => items.push({ bullet: true, t: x.replace(/^\s*- /, '') }));
      else if (bl[0].startsWith('```')) { items.push({ mono: bl.slice(1, -1) }); }
      else items.push({ t: bl.join(' ') });
    });
    items.forEach((it, k) => {
      const last = k === items.length - 1;
      if (it.mono) {
        it.mono.forEach((ml, q) => children.push(new Paragraph({ ...props, spacing: { before: 0, after: (q === it.mono.length - 1) ? (last ? 200 : 80) : 0, line: 260, lineRule: LineRuleType.AUTO }, keepNext: !last,
          children: [new TextRun({ text: ml || ' ', font: MONO, size: 18, color: INK })] })));
        return;
      }
      // long box paragraphs may break across pages, to avoid half-empty pages
      children.push(new Paragraph({ ...props, keepLines: it.t.length < 700, spacing: { before: 0, after: last ? 200 : 80 }, keepNext: !last,
        ...(it.bullet ? { numbering: { reference: 'boxbullets', level: 0 } } : {}),
        children: runs(it.t) }));
      if (it.bullet) usedNumbering.add('boxbullets');
    });
    continue;
  }
  // table
  m = l.match(/^<!--\s*widths:\s*([\d,\s.]+)-->/);
  if (m) { pendingWidths = m[1].split(',').map(Number); i++; continue; }
  m = l.match(/^Table:\s*(.*)$/);
  if (m) { flushPara(); pendingCaption = m[1]; i++; continue; }
  if (l.startsWith('|')) {
    flushPara(); const rows = [];
    while (i < lines.length && lines[i].startsWith('|')) { rows.push(lines[i]); i++; }
    pipeTable(rows, pendingWidths, pendingCaption); pendingWidths = null; pendingCaption = null; continue;
  }
  // figure
  m = l.match(/^!\[(.*)\]\((.*)\)(\{w=([\d.]+)\})?\s*$/);
  if (m) {
    flushPara();
    const file = path.join(baseDir, m[2]); const { w, h, data } = pngSize(file);
    const cm = parseFloat(m[4] || '15'); const pxW = Math.round(cm / 2.54 * 96); const pxH = Math.round(pxW * h / w);
    children.push(new Paragraph({ alignment: AlignmentType.CENTER, spacing: { before: 200, after: 60, line: 240, lineRule: LineRuleType.AUTO }, keepNext: true,
      children: [new ImageRun({ type: 'png', data, transformation: { width: pxW, height: pxH } })] }));
    children.push(new Paragraph({ alignment: AlignmentType.CENTER, spacing: { before: 0, after: 200 },
      children: runs(m[1], { font: SANS, size: 17, color: MUTED }) }));
    i++; continue;
  }
  // headings
  m = l.match(/^(#{2,3}) (.*)$/);
  if (m) {
    flushPara();
    children.push(new Paragraph({ heading: m[1] === '##' ? HeadingLevel.HEADING_1 : HeadingLevel.HEADING_2, children: runs(m[2]) }));
    i++; continue;
  }
  // lists
  if (/^\s*- /.test(l) || /^\d+\. /.test(l)) {
    flushPara();
    const numbered = /^\d+\. /.test(l);
    listInstance++;
    while (i < lines.length && (/^\s*- /.test(lines[i]) || /^\d+\. /.test(lines[i]) || /^\s{2,}\S/.test(lines[i]))) {
      const x = lines[i];
      if (/^\s{2,}- /.test(x)) {
        children.push(new Paragraph({ numbering: { reference: 'bullets', level: 1 }, children: runs(x.replace(/^\s*- /, '')) }));
      } else if (/^- /.test(x)) {
        children.push(new Paragraph({ numbering: { reference: 'bullets', level: 0 }, children: runs(x.slice(2)) }));
      } else if (/^\d+\. /.test(x)) {
        children.push(new Paragraph({ numbering: { reference: 'numbered', level: 0, instance: listInstance }, children: runs(x.replace(/^\d+\. /, '')) }));
      } else { // continuation line of previous item
        const prev = children.pop();
        children.push(prev); // keep; append as separate indented paragraph
        children.push(new Paragraph({ indent: { left: 400 }, spacing: { after: 60 }, children: runs(x.trim()) }));
      }
      i++;
    }
    continue;
  }
  if (l.trim() === '') { flushPara(); i++; continue; }
  para.push(l.trim()); i++;
}
flushPara();

const doc = new Document({
  creator: 'Serajus, with Claude',
  title: `Analytical C — §${fm.ref} ${fm.title}`,
  styles: {
    default: { document: { run: { font: SERIF, size: 22, color: INK }, paragraph: { spacing: { after: 140, line: 276, lineRule: LineRuleType.AUTO } } } },
    paragraphStyles: [
      { id: 'Title', name: 'Title', basedOn: 'Normal', next: 'Normal', run: { font: SERIF, size: 52, bold: true, color: NAVY }, paragraph: { spacing: { before: 0, after: 160 } } },
      { id: 'Heading1', name: 'Heading 1', basedOn: 'Normal', next: 'Normal', quickFormat: true,
        run: { font: SANS, size: 30, bold: true, color: NAVY }, paragraph: { spacing: { before: 360, after: 140 }, keepNext: true, outlineLevel: 0 } },
      { id: 'Heading2', name: 'Heading 2', basedOn: 'Normal', next: 'Normal', quickFormat: true,
        run: { font: SANS, size: 24, bold: true, color: INK }, paragraph: { spacing: { before: 260, after: 100 }, keepNext: true, outlineLevel: 1 } },
    ],
  },
  numbering: { config: [
    { reference: 'bullets', levels: [
      { level: 0, format: LevelFormat.BULLET, text: '•', alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 400, hanging: 260 }, spacing: { after: 60 } } } },
      { level: 1, format: LevelFormat.BULLET, text: '–', alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 800, hanging: 260 }, spacing: { after: 60 } } } },
    ] },
    { reference: 'boxbullets', levels: [
      { level: 0, format: LevelFormat.BULLET, text: '•', alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 460, hanging: 260 } } } },
    ] },
    { reference: 'numbered', levels: [
      { level: 0, format: LevelFormat.DECIMAL, text: '%1.', alignment: AlignmentType.LEFT, style: { paragraph: { indent: { left: 440, hanging: 340 }, spacing: { after: 80 } } } },
    ] },
  ] },
  sections: [{
    properties: { page: { size: { width: 11906, height: 16838 }, margin: { top: 1134, bottom: 1134, left: 1134, right: 1134 } } },
    footers: { default: new Footer({ children: [new Paragraph({ alignment: AlignmentType.CENTER,
      children: [new TextRun({ text: `Analytical C  ·  §${fm.ref} ${fm.title}  ·  `, font: SANS, size: 16, color: MUTED }),
                 new TextRun({ children: [PageNumber.CURRENT], font: SANS, size: 16, color: MUTED })] })] }) },
    children,
  }],
});
Packer.toBuffer(doc).then(buf => { fs.writeFileSync(outFile, buf); console.log('written', outFile, buf.length); });
