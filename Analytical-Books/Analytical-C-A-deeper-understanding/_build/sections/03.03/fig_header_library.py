# Figure 03.03-1: a header enters at phase 4 and serves phase 7; a library enters at phase 8
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch, FancyArrowPatch
plt.rcParams["font.family"] = "DejaVu Sans"
INK="#1B2A4A"; GREY="#5A6270"; BLUE="#1F5FAD"; PURP="#5B3E96"; GREEN="#2E7D32"; ORANGE="#8A5A00"
fig, ax = plt.subplots(figsize=(11, 7.4), dpi=200)
ax.set_xlim(0, 110); ax.set_ylim(0, 74); ax.axis("off")
def box(x, y, w, h, text, ec=GREY, fc="#F4F6F9", fs=9.2, bold=False, lw=1.2):
    ax.add_patch(FancyBboxPatch((x, y), w, h, boxstyle="round,pad=0,rounding_size=1.0", fc=fc, ec=ec, lw=lw))
    ax.text(x + w/2, y + h/2, text, ha="center", va="center", fontsize=fs, color=INK,
            weight="bold" if bold else "normal", linespacing=1.3)
def arrow(p, q, col=GREY, ls="-"):
    ax.add_patch(FancyArrowPatch(p, q, arrowstyle="-|>", mutation_scale=11, color=col, lw=1.2, linestyle=ls, shrinkA=0, shrinkB=0))
# main chain, left to right
box(1, 52, 17, 12, "hello.c\n8 lines, 162 bytes\n#include <stdio.h>", ec=INK, fs=9)
box(25, 52, 19, 12, "preprocessor\n(phases 1–4, in cc1)\npastes the header", ec=BLUE, fc="#EAF1FB", fs=9)
box(51, 52, 17, 12, "hello.i\n573 lines\n13,958 bytes", ec=INK, fs=9)
box(75, 52, 19, 12, "cc1, then as\n(phases 5–7)\ncc1 checks every call", ec=PURP, fc="#F1ECF8", fs=9)
box(75, 28, 19, 11, "hello.o\nmachine code\nU puts: a hole", ec=INK, fs=9)
box(75, 4, 19, 12, "linker ld\n(phase 8)\nresolves the hole", ec=GREEN, fc="#EAF5EA", fs=9)
box(99.5, 4, 10, 12, "hello\nthe\nprogram", ec=INK, fs=9)
arrow((18.3, 58), (24.7, 58)); arrow((44.3, 58), (50.7, 58)); arrow((68.3, 58), (74.7, 58))
arrow((84.5, 51.7), (84.5, 39.3)); arrow((84.5, 27.7), (84.5, 16.3)); arrow((94.3, 10), (99.2, 10))
# header, above the preprocessor
box(22, 30, 25, 15, "HEADER  /usr/include/stdio.h\nC source text, 34,258 bytes\npackage glibc-devel\n\ndeclarations, macros, types:\nwhat the compiler must know", ec=BLUE, fc="#FFFFFF", fs=8.6, lw=1.6)
arrow((34.5, 45.3), (34.5, 51.7), BLUE)
ax.text(36, 48.3, "read in phase 4", fontsize=8.4, color=BLUE, va="center")
# library, at the linker
box(33, 1, 33, 17, "LIBRARY  /lib64/libc.so.6\nELF shared object, 2,495,368 bytes\npackage glibc\n\ndefinitions: machine code;\nputs at address 0xd9a60:\nwhat the linker must supply", ec=GREEN, fc="#FFFFFF", fs=8.6, lw=1.6)
arrow((66.3, 10), (74.7, 10), GREEN)
ax.text(70.5, 11.2, "read in\nphase 8", fontsize=8.0, color=GREEN, va="bottom", ha="center")
# notes
ax.text(1, 70.5, "Where each kind of file enters the chain", fontsize=11.5, weight="bold", color=GREY, va="top")
ax.text(1, 22, "Without the header:\ncc1 refuses the call\n(implicit declaration,\nan error since GCC 14).", fontsize=8.6, color=PURP, va="top", linespacing=1.3)
ax.text(1, 10, "Without the library:\nld reports an\nundefined reference.", fontsize=8.6, color=GREEN, va="top", linespacing=1.3)
fig.savefig("fig_header_library.png", bbox_inches="tight", facecolor="white")
