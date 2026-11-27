# Figure 03.05-1: the 1,512 bytes of hello.o, to scale
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
plt.rcParams["font.family"] = "DejaVu Sans"
INK="#1B2A4A"; GREY="#5A6270"
C_HDR="#C9D6EA"; C_CODE="#F6D7A7"; C_DATA="#CFE8CF"; C_META="#E3DAF0"; C_TAB="#F3E6B3"; C_REL="#F4C7C3"; C_PAD="#FFFFFF"
regions = [
 (0x000, 0x040, "ELF header", C_HDR),
 (0x040, 0x055, ".text (21)", C_CODE),
 (0x055, 0x062, ".rodata (13)", C_DATA),
 (0x062, 0x091, ".comment (47)", C_META),
 (0x091, 0x098, "", C_PAD),
 (0x098, 0x0c8, ".note.gnu.property (48)", C_META),
 (0x0c8, 0x100, ".eh_frame (56)", C_META),
 (0x100, 0x190, ".symtab (144)", C_TAB),
 (0x190, 0x1a3, ".strtab (19)", C_TAB),
 (0x1a3, 0x1a8, "", C_PAD),
 (0x1a8, 0x1d8, ".rela.text (48)", C_REL),
 (0x1d8, 0x1f0, ".rela.eh_frame (24)", C_REL),
 (0x1f0, 0x264, ".shstrtab (116)", C_TAB),
 (0x264, 0x268, "", C_PAD),
 (0x268, 0x5e8, "section header table: 14 entries × 64 bytes (896)", C_HDR),
]
fig, ax = plt.subplots(figsize=(11, 8.6), dpi=200)
total = 0x5e8; W = 30.0; X0 = 4
scale = 80.0 / total
ax.set_xlim(0, 122); ax.set_ylim(-3, 90); ax.axis("off")
ax.text(0, 89, "The 1,512 bytes of hello.o, to scale (offsets in hexadecimal)", fontsize=11.5, weight="bold", color=GREY, va="top")
ytop = 84
fan = {".text (21)": 4.0, ".rodata (13)": 0.0, ".strtab (19)": 0.0, ".rela.eh_frame (24)": 0.0}
for (a, b, name, col) in regions:
    h = (b - a) * scale
    y = ytop - (b * scale)
    ax.add_patch(Rectangle((X0, y), W, h, facecolor=col, edgecolor=INK if name else "#BBBBBB", lw=0.8))
    if not name:
        continue
    if h > 2.2:
        ax.text(X0 - 0.8, ytop - a * scale, f"0x{a:03x}", ha="right", va="center", fontsize=7.6, color=GREY, family="DejaVu Sans Mono")
        ax.text(X0 + W/2, y + h/2, name.replace(": 14 entries", ":\n14 entries"), ha="center", va="center", fontsize=8.3, color=INK)
    else:
        ty = y + h/2 + fan.get(name, 0.0)
        ax.annotate(f"{name}, at 0x{a:03x}", xy=(X0 + W, y + h/2), xytext=(X0 + W + 4, ty), fontsize=8.3, color=INK, va="center",
                    arrowprops=dict(arrowstyle="-", color=GREY, lw=0.7))
ax.text(X0 - 0.8, ytop - total * scale, "0x5e8", ha="right", va="center", fontsize=7.6, color=GREY, family="DejaVu Sans Mono")
# legend / notes
notes = [
 (C_CODE, "machine code the program executes"),
 (C_DATA, "data the program reads: \"hello, world\""),
 (C_META, "kept, never executed: compiler name,\nISA note, unwind tables"),
 (C_TAB, "tables: symbols, symbol names,\nsection names"),
 (C_REL, "relocations: notes for the linker\nabout holes in .text and .eh_frame"),
 (C_HDR, "headers: what the file is,\nand where each section lies"),
 (C_PAD, "padding, to align the next section"),
]
yy = 70
ax.text(76, 77, "Kinds of bytes", fontsize=10, weight="bold", color=GREY)
for col, txt in notes:
    ax.add_patch(Rectangle((76, yy - 1.3), 3, 2.6, facecolor=col, edgecolor="#888888", lw=0.7))
    ax.text(80.5, yy, txt, fontsize=8.6, color=INK, va="center")
    yy -= 6
ax.text(76, 24, "Of 1,512 bytes, 34 are the program\nitself: 21 of code and 13 of data.\nThe rest describes those 34 bytes\nto the linker, the loader and the\ndebugger. .data, .bss and\n.note.GNU-stack are present but empty.", fontsize=9, color=INK, va="top", linespacing=1.4)
fig.savefig("fig_layout.png", bbox_inches="tight", facecolor="white")
