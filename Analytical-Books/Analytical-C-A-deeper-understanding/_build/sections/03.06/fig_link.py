# Figure 03.06-1: how the linker built hello's memory image from six input files
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
plt.rcParams["font.family"] = "DejaVu Sans"
INK="#1B2A4A"; GREY="#5A6270"
COL = {
 "crt1.o": "#F6D7A7", "crti.o": "#CFE8CF", "crtbegin.o": "#C9D6EA",
 "hello.o": "#F4C7C3", "crtend.o": "#E3DAF0", "crtn.o": "#F3E6B3",
 "linker": "#E6E6E6",
}
# output sections in address order: (address, name, [(file, size, note)])
segs = [
 ("LOAD 1: read only (R), from 0x400000", [
  ("0x400000", "ELF header and 13 program headers", [("linker", "0x318", "")]),
  ("0x400318", ".note.gnu.build-id", [("linker", "0x24", "")]),
  ("0x40033c", ".interp", [("linker", "0x1c", "/lib64/ld-linux-x86-64.so.2")]),
  ("0x400358", ".gnu.hash .dynsym .dynstr\n.gnu.version .gnu.version_r", [("linker", "0x100", "names for the loader")]),
  ("0x400458", ".rela.dyn .rela.plt", [("linker", "0x48", "notes for the loader")]),
  ("0x4004a0", ".rodata", [("crt1.o", "4", ""), ("crtbegin.o", "8", ""), ("hello.o", "13", "\"hello, world\" at 0x4004b0")]),
  ("0x4004c0", ".eh_frame_hdr", [("linker", "0x34", "an index to .eh_frame")]),
  ("0x4004f8", ".eh_frame", [("crt1.o", "0x58", ""), ("linker", "0x28", "for .plt"), ("hello.o", "0x20", ""), ("crtend.o", "4", "end marker")]),
  ("0x4005a0", ".note.gnu.property .note.ABI-tag", [("linker", "0x40", "properties merged from the inputs"), ("crt1.o", "0x20", "")]),
 ]),
 ("LOAD 2: read and execute (R E), from 0x401000", [
  ("0x401000", ".init", [("crti.o", "0x16", ""), ("crtn.o", "5", "")]),
  ("0x401020", ".plt", [("linker", "0x20", "puts@plt at 0x401030")]),
  ("0x401040", ".text", [("crt1.o", "0x45", "_start at 0x401040"), ("crtbegin.o", "0xa6", ""), ("hello.o", "0x15", "main at 0x401136")]),
  ("0x40114c", ".fini", [("crti.o", "8", ""), ("crtn.o", "5", "")]),
 ]),
 ("LOAD 3: read and write (RW), from 0x402df8", [
  ("0x402df8", ".init_array .fini_array", [("crtbegin.o", "8 + 8", "")]),
  ("0x402e08", ".dynamic", [("linker", "0x1d0", "NEEDED libc.so.6, ...")]),
  ("0x402fd8", ".got .got.plt", [("linker", "0x30", "puts's slot at 0x403000")]),
  ("0x403008", ".data", [("crt1.o", "4", "")]),
  ("0x40300c", ".bss", [("crtbegin.o", "1", "")]),
 ]),
]
rows = sum(len(s[1]) for s in segs) + len(segs)
fig, ax = plt.subplots(figsize=(11.5, 9.4), dpi=200)
ax.set_xlim(0, 120); ax.set_ylim(-4, rows*3.0 + 9); ax.axis("off")
ax.text(0, rows*3.0 + 8, "How the linker built hello's memory image (Fedora; addresses in hexadecimal, not to scale)",
        fontsize=11.5, weight="bold", color=GREY, va="top")
y = rows*3.0 + 3
X_ADDR = 0; X_NAME = 9.5; X_BAR = 47; BARW = 44
for title, secs in segs:
    ax.text(X_NAME, y, title, fontsize=9.6, weight="bold", color=INK, va="center")
    y -= 3.0
    for addr, name, parts in secs:
        ax.text(X_ADDR, y, addr, fontsize=8.2, family="DejaVu Sans Mono", color=GREY, va="center")
        ax.text(X_NAME, y, name, fontsize=8.4 if "\n" not in name else 7.6, family="DejaVu Sans Mono", color=INK, va="center")
        n = len(parts); w = BARW / n; x = X_BAR
        for f, size, note in parts:
            ax.add_patch(Rectangle((x, y-1.15), w-0.4, 2.3, facecolor=COL[f], edgecolor=INK, lw=0.6))
            lab = f if not size else f"{f} ({size})"
            if f == "linker": lab = ("made by the linker" if n < 3 else "linker") + (f" ({size})" if size else "")
            ax.text(x + (w-0.4)/2, y, lab, ha="center", va="center", fontsize=7.4, color=INK)
            x += w
        notes = "; ".join(p[2] for p in parts if p[2])
        if notes:
            ax.text(X_BAR + BARW + 1.0, y, notes, fontsize=7.6, color=GREY, va="center")
        y -= 3.0
# legend
ly = -2.0
ax.text(0, ly+3.2, "Where the bytes came from:", fontsize=9, weight="bold", color=GREY)
lx = 0
for f in ["crt1.o", "crti.o", "crtbegin.o", "hello.o", "crtend.o", "crtn.o", "linker"]:
    ax.add_patch(Rectangle((lx, ly-0.9), 2.4, 1.8, facecolor=COL[f], edgecolor=INK, lw=0.6))
    ax.text(lx+3.0, ly, "made by the linker" if f=="linker" else f, fontsize=8.2, va="center", color=INK)
    lx += 16.5 if f=="linker" else 13.5
plt.savefig("fig_link.png", bbox_inches="tight", facecolor="white")
