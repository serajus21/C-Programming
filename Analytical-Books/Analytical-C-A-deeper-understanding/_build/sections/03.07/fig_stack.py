# Figure 03.07-1: hello's stack at its first instruction (Fedora, under gdb, so without address randomization)
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, FancyArrowPatch
plt.rcParams["font.family"] = "DejaVu Sans"
INK="#1B2A4A"; GREY="#5A6270"
C_ARG="#F6D7A7"; C_ENV="#CFE8CF"; C_AUX="#C9D6EA"; C_NUL="#E6E6E6"; C_STR="#F4C7C3"
rows = [  # (address label, content, colour, note)
 ("0x7fffffffe3a0", "1", C_ARG, "argc       ← rsp at the first instruction"),
 ("0x7fffffffe3a8", "0x7fffffffe6e4", C_ARG, "argv[0]    → the program's path"),
 ("0x7fffffffe3b0", "0", C_NUL, "argv[argc] = NULL"),
 ("0x7fffffffe3b8", "0x7fffffffe764", C_ENV, "envp[0]    → \"NAME=value\""),
 ("0x7fffffffe3c0", "0x7fffffffe774", C_ENV, "envp[1]"),
 ("...", "...", C_ENV, "one pointer per environment variable"),
 ("", "0", C_NUL, "NULL: end of the environment"),
 ("", "type, value", C_AUX, "auxiliary vector: AT_PHDR 0x400040, AT_PHNUM 13,"),
 ("", "type, value", C_AUX, "AT_ENTRY 0x401040, AT_BASE (the interpreter),"),
 ("", "...", C_AUX, "AT_PAGESZ 4096, AT_RANDOM, AT_SYSINFO_EHDR (vDSO), ..."),
 ("", "0, 0", C_NUL, "AT_NULL: end of the auxiliary vector"),
 ("", "(padding)", C_NUL, ""),
 ("0x7fffffffe6e4", "\"/home/.../hello\\0\"", C_STR, "the strings themselves: argv[0], the environment strings,"),
 ("0x7fffffffe764", "\"...=...\\0\" ...", C_STR, "and the 16 bytes AT_RANDOM points to (order simplified)"),
 ("0x7ffffffff000", "", None, "top of the stack (the stack grows downward, toward lower addresses)"),
]
fig, ax = plt.subplots(figsize=(11.0, 7.6), dpi=200)
n = len(rows); H = 1.0
ax.set_xlim(0, 100); ax.set_ylim(-1.2, n*H + 2.2); ax.axis("off")
ax.text(0, n*H + 1.6, "hello's stack at its first instruction (Fedora, under gdb; lower addresses at the top, each cell 8 bytes, each auxiliary entry 16)",
        fontsize=11, weight="bold", color=GREY, va="center")
for i, (addr, content, col, note) in enumerate(rows):
    y = n*H - (i+1)*H
    ax.text(0, y + H/2, addr, fontsize=8.6, family="DejaVu Sans Mono", color=GREY, va="center")
    if col is not None:
        ax.add_patch(Rectangle((17, y+0.06), 26, H-0.12, facecolor=col, edgecolor=INK, lw=0.6))
        ax.text(30, y + H/2, content, fontsize=8.6, family="DejaVu Sans Mono", color=INK, va="center", ha="center")
    else:
        ax.plot([17, 43], [y+H-0.06, y+H-0.06], color=INK, lw=1.4)
    ax.text(45, y + H/2, note, fontsize=8.6, color=INK, va="center")
# brackets
def bracket(i0, i1, label):
    y0 = n*H - i0*H - 0.1; y1 = n*H - (i1+1)*H + 0.1
    ax.plot([15.5, 15, 15, 15.5], [y0, y0, y1, y1], color=GREY, lw=0.9)
    ax.text(14.5, (y0+y1)/2, label, fontsize=8, color=GREY, ha="right", va="center", rotation=90)
legend = [(C_ARG, "argc and argv"), (C_ENV, "envp"), (C_AUX, "auxiliary vector"), (C_STR, "strings"), (C_NUL, "terminators")]
x = 0
for col, lab in legend:
    ax.add_patch(Rectangle((x, -1.0), 2.2, 0.7, facecolor=col, edgecolor=INK, lw=0.6))
    ax.text(x+3, -0.65, lab, fontsize=8.4, va="center", color=INK)
    x += 19
plt.savefig("fig_stack.png", bbox_inches="tight", facecolor="white")
