# Figure 03.04-1: inside cc1: the forms a function passes through, with dump options
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch, FancyArrowPatch
plt.rcParams["font.family"] = "DejaVu Sans"
INK="#1B2A4A"; GREY="#5A6270"; BLUE="#1F5FAD"; PURP="#5B3E96"; GREEN="#2E7D32"; ORANGE="#8A5A00"
fig, ax = plt.subplots(figsize=(11, 9.6), dpi=200)
ax.set_xlim(0, 110); ax.set_ylim(0, 96); ax.axis("off")
def box(x, y, w, h, text, ec=GREY, fc="#F4F6F9", fs=9.0, bold=False, lw=1.3, ha="center"):
    ax.add_patch(FancyBboxPatch((x, y), w, h, boxstyle="round,pad=0,rounding_size=1.0", fc=fc, ec=ec, lw=lw))
    tx = x + w/2 if ha == "center" else x + 1.5
    ax.text(tx, y + h/2, text, ha=ha, va="center", fontsize=fs, color=INK, weight="bold" if bold else "normal", linespacing=1.3)
def arrow(p, q, col=GREY):
    ax.add_patch(FancyArrowPatch(p, q, arrowstyle="-|>", mutation_scale=11, color=col, lw=1.2, shrinkA=0, shrinkB=0))
ax.text(1, 95, "Inside cc1: the forms a function passes through", fontsize=11.5, weight="bold", color=GREY, va="top")
ax.text(1, 91.2, "form, and the option that prints it", fontsize=9, color=GREY, va="top")
ax.text(55, 91.2, "what happened there, on the reader's Fedora", fontsize=9, color=GREY, va="top")
rows = [
 ("C text, after preprocessing\n(hello.i)", "-E", BLUE, "#EAF1FB", "printf(\"hello, world\\n\"); 573 lines with stdio.h (§03.03)"),
 ("GENERIC: a tree for each function", "-fdump-tree-original", PURP, "#F1ECF8", "the parse; the conversion to const char * restrict inserted (§03.02)"),
 ("GIMPLE: statements with at most\none operation each", "-fdump-tree-gimple", PURP, "#F1ECF8", "D.2347 = x / 10;  loops become labels and gotos"),
 ("lowered GIMPLE", "-fdump-tree-lower", PURP, "#F1ECF8", "printf(\"hello, world\\n\") becomes __builtin_puts(\"hello, world\")"),
 ("SSA form: every name assigned once", "-fdump-tree-ssa", PURP, "#F1ECF8", "s_8 = s_1 + i_2;  # s_1 = PHI <s_3(2), s_8(3)>"),
 ("optimized GIMPLE\n(after the tree passes)", "-fdump-tree-optimized", PURP, "#F1ECF8", "still _2 = x_1(D) / 10;  (at -O2)"),
 ("RTL: register transfer language,\nclose to the machine", "-fdump-rtl-expand", ORANGE, "#FBF3E4", "x / 10 becomes (x × 0xCCCCCCCD) >> 32 >> 3 here, even at -O0"),
 ("RTL after register allocation\nand final", "-fdump-rtl-final", ORANGE, "#FBF3E4", "pseudo-registers replaced by eax, edi ...; prologue and epilogue added"),
 ("assembly text (hello.s)", "-S", GREEN, "#EAF5EA", "movl $.LC0, %edi  /  call puts  (27 lines for hello.c)"),
]
y = 81.5; h = 7.2; gap = 1.5
for i, (name, opt, ec, fc, what) in enumerate(rows):
    box(1, y, 30, h, name, ec=ec, fc=fc, fs=8.6)
    ax.text(32.3, y + h/2, opt, fontsize=7.6, color=ec, va="center", family="DejaVu Sans Mono")
    box(55, y, 54, h, what, ec="#C9CED6", fc="#FFFFFF", fs=8.2, ha="left")
    if i < len(rows) - 1:
        arrow((16, y - 0.1), (16, y - gap + 0.1))
    y -= h + gap
ax.text(1, 1.0, "The tree passes (violet) work on a form mostly independent of the processor; the RTL passes (brown) on one that knows it.\nThe numbers in dump-file names (011t.lower, 274r.expand on GCC 16) give the order of the passes.", fontsize=8.2, color=GREY, va="bottom", linespacing=1.35)
fig.savefig("fig_cc1.png", bbox_inches="tight", facecolor="white")
