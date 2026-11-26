# _build — how this book's files are produced

This folder lets any later session rebuild the book's .docx files exactly, in the house style.
It is working material, not part of the book's text.

## Layout
- `tools/build_section.js` — converts a section draft (`.md`, house markup) into a house-style `.docx`.
  Usage: `node tools/build_section.js sections/01.01/01.01.md out.docx`
  Needs Node.js with the `docx` package (`npm install docx`), and the Noto Serif / Sans / Sans Mono fonts.
- `index/` — `build_index.js` builds `_index.docx` from `toc.json`; `parse_toc.py` regenerates `toc.json`
  (and section file names) from `toc-draft-v1.md` using `overrides.json` for hand-shortened names.
- `sections/CC.SS/` — one folder per written section: the draft (`CC.SS.md`), figure sources
  (`.dot` for Graphviz, `figs.py` for matplotlib), the rendered figures (`.png`), and every program the
  section shows or uses.

## House markup (in the .md drafts)
Front matter (`ref:`, `title:`, `chapter:`, `part:`, `builds:`) then a line `---`.
`##` / `###` headings; blank line between paragraphs; `- ` bullets; `1. ` numbered lists.
Fenced blocks: ```` ```c Listing CC.SS-n  Title ````, ```` ```terminal ````, ```` ```output ````, ```` ```text ````.
Boxes: `:::why`, `:::hood`, `:::myth`, `:::precise`, `:::history`, `:::metal`, `:::orbit` ... `:::`.
Tables: optional `Table: caption` and `<!-- widths: 30,70 -->` lines, then a pipe table.
Figures: `![Figure CC.SS-n  Caption](file.png){w=15}` (width in cm).
Inline: `code`, **bold**, *italic*, <sub>sub</sub>, <sup>sup</sup>.

## Verification toolchain used so far
GCC 14.2.0 (`-std=c23 -Wall -Wextra -pedantic`) and avr-gcc 7.3.0 / avr-libc 2.0.0 on x86-64 Ubuntu 24.04.
AVR programs that need a chip are run on the simulator simavr 1.6 (`simavr -m atmega328p -f 16000000 prog.elf`);
for Arduino sketches a minimal stand-in for `Serial` writing to the UART is used (see `sections/01.03/mock_main.cpp`).
The reader's machine: Fedora 44, GCC 16.2.1.

## The lab runner (from Chapter 03, November 26, 2026)
Programs are now run on the reader's own machine: Fedora 45, GCC 16.2.1, glibc 2.44, binutils 2.47,
Clang 23.1.5, avr-gcc 15.3.0 / avr-libc 2.2.1 (Fedora has no simavr package, so AVR simulation stays in
the author's workspace). The runner is `_Analytical-C-Lab/_runner/`: a systemd user path unit
(`analytical-c-lab.path`) watches `queue/`; each `*.sh` job placed there is run once with bash from
`_Analytical-C-Lab/`, and its combined output and exit status go to `done/NAME.out` and `done/NAME.meta`.
Setup: `setup-runner.sh`; stop: `systemctl --user disable --now analytical-c-lab.path`.
Each section's Fedora build products are kept in `sections/CC.SS/fedora/`.
