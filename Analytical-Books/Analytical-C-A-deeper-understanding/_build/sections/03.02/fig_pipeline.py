# Figure 03.02-1: the standard's eight phases, and the programs GCC runs for them
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch, FancyArrowPatch
plt.rcParams["font.family"] = "DejaVu Sans"
INK="#1B2A4A"; GREY="#5A6270"; BLUE="#1F5FAD"; PURP="#5B3E96"; GREEN="#2E7D32"; ORANGE="#8A5A00"
fig, ax = plt.subplots(figsize=(11, 8.6), dpi=200)
ax.set_xlim(0, 110); ax.set_ylim(0, 86); ax.axis("off")
def box(x, y, w, h, text, ec=GREY, fc="#F4F6F9", fs=9.2, bold=False, ls="-", lw=1.1):
    ax.add_patch(FancyBboxPatch((x, y), w, h, boxstyle="round,pad=0,rounding_size=1.0", fc=fc, ec=ec, lw=lw, ls=ls))
    ax.text(x + w/2, y + h/2, text, ha="center", va="center", fontsize=fs, color=INK,
            weight="bold" if bold else "normal", linespacing=1.3)
def arrow(p, q, col=GREY, ls="-"):
    ax.add_patch(FancyArrowPatch(p, q, arrowstyle="-|>", mutation_scale=11, color=col, lw=1.1, linestyle=ls, shrinkA=0, shrinkB=0))

ax.text(2, 84, "The standard's phases (§5.1.1.2)", fontsize=11.5, weight="bold", color=GREY, va="top")
ax.text(64, 84, "What GCC actually runs", fontsize=11.5, weight="bold", color=GREY, va="top")
phases = [
 ("1  map the file's characters; end of line → newline", BLUE),
 ("2  join lines that end in a backslash", BLUE),
 ("3  cut into preprocessing tokens; comment → one space", BLUE),
 ("4  directives, #include, macro expansion", BLUE),
 ("5  escape sequences → character codes", PURP),
 ("6  join adjacent string literals", PURP),
 ("7  tokens → syntax → meaning → translation", PURP),
 ("8  resolve external references; link the library", GREEN),
]
y0 = 76; dy = 8.2
for i, (t, c) in enumerate(phases):
    y = y0 - i*dy
    box(2, y - 3, 50, 6, t, ec=c, fs=9)
# right column: programs
top = y0 + 3; bot = y0 - 6*dy - 3
ax.add_patch(FancyBboxPatch((64, bot), 28, top - bot, boxstyle="round,pad=0,rounding_size=1.0", fc="#EAF1FB", ec=BLUE, lw=1.5))
mid = y0 - 3*dy - 4.1
ax.plot([64, 92], [mid, mid], color=BLUE, lw=1.0, ls=(0, (4, 3)))
ax.text(78, (top + mid)/2 + 2, "cc1", ha="center", fontsize=12, weight="bold", color=INK)
ax.text(78, (top + mid)/2 - 4, "the compiler proper;\nits built-in preprocessor\ndoes phases 1-4", ha="center", va="center", fontsize=9.2, color=INK, linespacing=1.3)
ax.text(78, (mid + bot)/2, "phases 5-7, as far as\nassembly language:\nparsing, checking,\nchoosing instructions", ha="center", va="center", fontsize=9.2, color=INK, linespacing=1.3)
box(64, 11.0, 28, 6, "as   the assembler:\nfinishes phase 7", ec=ORANGE, fc="#FBF3E4", lw=1.5)
box(64, 0.6, 28, 6, "collect2, which runs ld,\nthe linker", ec=GREEN, fc="#EAF5EA", lw=1.5)
arrow((52.5, y0 - 1.5*dy), (63.5, y0 - 1.5*dy), BLUE)
arrow((52.5, y0 - 5.0*dy), (63.5, y0 - 5.0*dy), PURP)
arrow((52.5, y0 - 7*dy), (63.5, 5.6), GREEN)
arrow((78, bot - 0.2), (78, 17.2)); ax.text(79, (bot + 17.2)/2, "hello.s", fontsize=8.8, color=GREY, va="center")
arrow((78, 10.8), (78, 6.8)); ax.text(79, 8.8, "hello.o", fontsize=8.8, color=GREY, va="center")
ax.text(78, top + 1.0, "hello.c", fontsize=8.8, color=GREY, ha="center", va="bottom")
def stop(y, opt, out):
    ax.text(93.8, y, f"{opt}\n{out}", fontsize=8.8, color=INK, va="center", linespacing=1.3)
    ax.plot([92.2, 93.4], [y, y], color=GREY, lw=1.0)
stop(mid, "-E stops here:", "text (hello.i with\n-save-temps)")
stop(bot + 1.5, "-S stops here,\ninside phase 7:", "hello.s (text)")
stop(14, "-c stops here:", "hello.o (object)")
stop(3.6, "no option:", "hello (program)")
ax.text(27, 6.5, "also into the linker: the startup files crt1.o, crti.o,\ncrtbegin.o, crtend.o, crtn.o, and the C library (-lc)", fontsize=8.6, color=GREEN, ha="center", va="center", linespacing=1.3)
arrow((52.5, 4.6), (63.5, 2.6), GREEN)
fig.savefig("fig_pipeline.png", bbox_inches="tight", facecolor="white")
