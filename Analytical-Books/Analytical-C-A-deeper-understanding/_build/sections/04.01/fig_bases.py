import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
plt.rcParams["font.family"] = ["Noto Sans", "DejaVu Sans"]
NAVY = "#1B2A4A"; GREY = "#8A93A3"
BLUE = ("#EAF1FB", "#1F5FAD"); PURP = ("#F1ECF8", "#5B3E96")
GREEN = ("#EAF5EA", "#2E7D32"); AMBER = ("#FBF3E4", "#8A5A00")
MONO = "DejaVu Sans Mono"

def boxes(ax, x0, y, digits, places, col, w=1.0):
    fc, ec = col
    for i, (d, p) in enumerate(zip(digits, places)):
        ax.add_patch(Rectangle((x0 + i*w, y), w, 0.8, fc=fc, ec=ec, lw=1.2))
        ax.text(x0 + i*w + w/2, y + 0.4, d, ha="center", va="center", fontsize=14, family=MONO, color=NAVY)
        ax.text(x0 + i*w + w/2, y - 0.25, p, ha="center", va="center", fontsize=8.5, color=GREY)

# ---- Figure 04.01-1: 57 in four systems -------------------------------------
fig, ax = plt.subplots(figsize=(9.4, 6.6), dpi=200)
ax.set_xlim(-3.2, 15.8); ax.set_ylim(-1.4, 10.2); ax.axis("off")

# decimal
ax.text(-3.1, 9.25, "base 10", fontsize=11, weight="bold", color=BLUE[1], va="center")
boxes(ax, 5.0, 8.85, "57", ["tens", "ones"], BLUE)
ax.text(8.0, 9.25, "5 × 10 + 7 × 1 = 57", fontsize=11, color=NAVY, va="center")

# octal digits (above the bits)
bits = "00111001"
x0 = 3.0
ax.text(-3.1, 6.65, "base 8", fontsize=11, weight="bold", color=PURP[1], va="center")
groups8 = [(0, 1, "0"), (2, 4, "7"), (5, 7, "1")]
for a, b, d in groups8:
    ax.add_patch(Rectangle((x0 + a + 0.06, 6.25), b - a + 1 - 0.12, 0.8, fc=PURP[0], ec=PURP[1], lw=1.2))
    ax.text(x0 + (a + b + 1)/2, 6.65, d, ha="center", va="center", fontsize=14, family=MONO, color=NAVY)
    ax.plot([x0 + a + 0.08, x0 + b + 0.92], [5.85, 5.85], color=PURP[1], lw=1.4)
    ax.plot([x0 + a + 0.08]*2, [5.85, 5.7], color=PURP[1], lw=1.4)
    ax.plot([x0 + b + 0.92]*2, [5.85, 5.7], color=PURP[1], lw=1.4)
ax.text(x0 + 0.95, 7.3, "sixty-fours", ha="center", fontsize=8.5, color=GREY)
ax.text(x0 + 3.5, 7.3, "eights", ha="center", fontsize=8.5, color=GREY)
ax.text(x0 + 6.5, 7.3, "ones", ha="center", fontsize=8.5, color=GREY)
ax.text(12.0, 6.65, "0 × 64 + 7 × 8 + 1 = 57\nwritten 071 in C", fontsize=11, color=NAVY, va="center")

# binary
ax.text(-3.1, 4.45, "base 2", fontsize=11, weight="bold", color=GREEN[1], va="center")
boxes(ax, x0, 4.05, bits, ["128", "64", "32", "16", "8", "4", "2", "1"], GREEN)
ax.text(12.0, 4.45, "32 + 16 + 8 + 1 = 57\nwritten 0b111001 (C23)", fontsize=11, color=NAVY, va="center")

# hex digits (below the bits)
ax.text(-3.1, 1.15, "base 16", fontsize=11, weight="bold", color=AMBER[1], va="center")
groups16 = [(0, 3, "3"), (4, 7, "9")]
for a, b, d in groups16:
    ax.plot([x0 + a + 0.08, x0 + b + 0.92], [3.15, 3.15], color=AMBER[1], lw=1.4)
    ax.plot([x0 + a + 0.08]*2, [3.15, 3.3], color=AMBER[1], lw=1.4)
    ax.plot([x0 + b + 0.92]*2, [3.15, 3.3], color=AMBER[1], lw=1.4)
    ax.add_patch(Rectangle((x0 + a + 0.06, 0.75), b - a + 1 - 0.12, 0.8, fc=AMBER[0], ec=AMBER[1], lw=1.2))
    ax.text(x0 + (a + b + 1)/2, 1.15, d, ha="center", va="center", fontsize=14, family=MONO, color=NAVY)
    ax.plot([x0 + (a + b + 1)/2]*2, [3.1, 1.6], color=AMBER[1], lw=0.8, ls=":")
ax.text(x0 + 2.0, 0.25, "sixteens", ha="center", fontsize=8.5, color=GREY)
ax.text(x0 + 6.0, 0.25, "ones", ha="center", fontsize=8.5, color=GREY)
ax.text(12.0, 1.15, "3 × 16 + 9 = 57\nwritten 0x39 in C", fontsize=11, color=NAVY, va="center")
ax.text(x0 + 4.0, -0.75, "Grouping always starts at the right: three bits per octal digit, four per hexadecimal digit.",
        ha="center", fontsize=9.5, color=NAVY, style="italic")
plt.savefig("fig_bases.png", bbox_inches="tight", facecolor="white")

# ---- Figure 04.01-2: 0xCCCCCCCD ---------------------------------------------
v = 0xCCCCCCCD
b = format(v, "032b")
fig, ax = plt.subplots(figsize=(10.0, 3.0), dpi=200)
ax.set_xlim(-0.2, 32.2); ax.set_ylim(-2.2, 1.8); ax.axis("off")
for i, ch in enumerate(b):
    nib = i // 4
    col = GREEN if nib % 2 == 0 else BLUE
    ax.add_patch(Rectangle((i, 0), 1, 0.9, fc=col[0], ec=col[1], lw=1.0))
    ax.text(i + 0.5, 0.45, ch, ha="center", va="center", fontsize=13, family=MONO, color=NAVY)
    if i % 4 == 0:
        ax.text(i + 0.5, 1.25, "bit " + str(31 - i), ha="left", va="center", fontsize=10, color=GREY)
for n in range(8):
    a = n*4
    d = b[a:a+4]
    ax.plot([a + 0.1, a + 3.9], [-0.2, -0.2], color=AMBER[1], lw=1.4)
    ax.text(a + 2, -0.7, format(int(d, 2), "X"), ha="center", va="center", fontsize=18, family=MONO, weight="bold", color=AMBER[1])
    ax.text(a + 2, -1.35, "8+4" if d == "1100" else "8+4+1", ha="center", va="center", fontsize=11, color=GREY)
ax.text(16, -2.05, "decimal: 3435973837 (no pattern visible)        hexadecimal: 0xCCCCCCCD", ha="center", fontsize=13, color=NAVY)
plt.savefig("fig_magic.png", bbox_inches="tight", facecolor="white")
