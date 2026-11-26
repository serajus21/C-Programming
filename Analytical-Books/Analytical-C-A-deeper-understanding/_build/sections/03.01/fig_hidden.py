# Figure 03.01-1: what hello.c says, and what happens around it
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch, FancyArrowPatch
plt.rcParams["font.family"] = "DejaVu Sans"
INK = "#1B2A4A"; GREY = "#5A6270"; BLUE = "#1F5FAD"; PURP = "#5B3E96"
fig, ax = plt.subplots(figsize=(10.5, 9.2), dpi=200)
ax.set_xlim(0, 105); ax.set_ylim(0, 93); ax.axis("off")

def panel(x, y, w, h, title, sub, col, dashed=True):
    ax.add_patch(FancyBboxPatch((x, y), w, h, boxstyle="round,pad=0,rounding_size=1.5",
                 fill=False, ec=col, lw=1.3 if dashed else 1.8, ls=(0, (5, 3)) if dashed else "-"))
    ax.text(x + 1.5, y + h - 1.6, title, ha="left", va="top", fontsize=11.5, weight="bold", color=col)
    if sub:
        ax.text(x + 1.5, y + h - 4.4, sub, ha="left", va="top", fontsize=8.5, color=col)

def box(cx, cy, text, col=GREY, fill="#F4F6F9", w=40, h=5.6, bold=False, lw=1.1):
    ax.add_patch(FancyBboxPatch((cx - w/2, cy - h/2), w, h, boxstyle="round,pad=0,rounding_size=1.2",
                 fc=fill, ec=col, lw=lw))
    ax.text(cx, cy, text, ha="center", va="center", fontsize=9.3, color=INK,
            weight="bold" if bold else "normal", linespacing=1.3)
    return (cx, cy, w, h)

def arrow(p, q, col=GREY, ls="-", rad=0.0):
    ax.add_patch(FancyArrowPatch(p, q, arrowstyle="-|>", mutation_scale=11, color=col, lw=1.1,
                 linestyle=ls, connectionstyle=f"arc3,rad={rad}", shrinkA=0, shrinkB=0))

# left column: before, yours, after (vertical arrows run right of centre, clear of the titles)
L = 24; X = 38
panel(2, 63, 44, 29, "Before main", "not in hello.c (§02.06, §03.07)", GREY)
box(L, 82.5, "the shell asks the kernel to run\n./hello (execve)")
box(L, 75.5, "the dynamic loader ld.so loads\nthe C library, libc.so.6")
box(L, 68.5, "_start, from a startup file;\n__libc_start_main sets up the library")
arrow((X, 79.4), (X, 78.6)); arrow((X, 72.4), (X, 71.6))

panel(2, 30, 44, 30, "hello.c: the part you wrote", None, BLUE, dashed=False)
box(L, 51, "main() is called", BLUE, "#EAF1FB", bold=True, lw=1.6)
box(L, 43.5, 'printf("hello, world\\n");\n(compiled as a call to puts)', BLUE, "#EAF1FB", lw=1.6)
box(L, 36, "return 0;", BLUE, "#EAF1FB", bold=True, lw=1.6)
arrow((X, 65.4), (X, 54.1)); arrow((X, 47.9), (X, 46.6)); arrow((X, 40.4), (X, 39.1))

panel(2, 0.6, 44, 27.4, "After main", "not in hello.c (§03.07, §33.01)", GREY)
box(L, 17.6, "exit(0): atexit functions run,\nstreams flushed and closed")
box(L, 10.8, "exit_group(0): the kernel\nends the process")
box(L, 4.0, "the shell receives the status:\necho $? prints 0")
arrow((X, 32.9), (X, 20.7)); arrow((X, 14.5), (X, 13.9)); arrow((X, 7.7), (X, 7.1))

# right column: the library
R = 78
panel(55, 23, 47, 34, "Inside the C library", "not in hello.c (§31.01, §32.05)", PURP)
box(R, 44, "puts copies the 13 characters\ninto stdout's buffer", w=42)
box(R, 36.5, "if stdout is a terminal: written at once\nwith one system call, write(1, ..., 13);\notherwise later, inside exit", w=42, h=7.4)
box(R, 28.5, "the kernel sends the bytes\nto the terminal", w=42)
arrow((R, 41.1), (R, 40.4)); arrow((R, 32.6), (R, 31.5))
arrow((44, 43.5), (57, 44), PURP, (0, (4, 2)))
ax.text(50.5, 45.2, "call", fontsize=8.5, color=PURP, ha="center")
arrow((57, 28.5), (44, 35.5), PURP, (0, (4, 2)))
ax.text(49.5, 28.6, "return", fontsize=8.5, color=PURP, ha="center")
fig.savefig("fig_hidden.png", bbox_inches="tight", facecolor="white")
