import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch
plt.rcParams.update({"font.family": ["Noto Sans", "DejaVu Sans"], "font.size": 10.5})
BLUE="#1F5FAD"; RED="#B42318"; MUTED="#5A6270"; NAVY="#1B2A4A"
fig, ax = plt.subplots(figsize=(9.0, 3.2), dpi=200)
ax.set_xlim(-1.6, 13.2); ax.set_ylim(-0.4, 4.6); ax.axis("off")
xs = [9.6, 6.6, 3.6, 0.6]                 # full adder 0 at right, 3 at left
for i, x in enumerate(xs):
    ax.add_patch(FancyBboxPatch((x, 1.4), 1.8, 1.3, boxstyle="round,pad=0.02,rounding_size=0.15",
                                fc="#EAF1FB", ec=BLUE, lw=1.5))
    ax.text(x + 0.9, 2.05, f"full\nadder {i}", ha="center", va="center", fontsize=10.5)
    ax.annotate("", xy=(x + 0.55, 2.7), xytext=(x + 0.55, 3.6), arrowprops=dict(arrowstyle="->", color=MUTED))
    ax.annotate("", xy=(x + 1.25, 2.7), xytext=(x + 1.25, 3.6), arrowprops=dict(arrowstyle="->", color=MUTED))
    ax.text(x + 0.55, 3.75, f"A{i}", ha="center", fontsize=10)
    ax.text(x + 1.25, 3.75, f"B{i}", ha="center", fontsize=10)
    ax.annotate("", xy=(x + 0.9, 0.5), xytext=(x + 0.9, 1.4), arrowprops=dict(arrowstyle="->", color=MUTED))
    ax.text(x + 0.9, 0.15, f"S{i}", ha="center", fontsize=10.5, weight="bold")
for i in range(3):                        # carries flow right to left
    x_from = xs[i]; x_to = xs[i + 1] + 1.8
    ax.annotate("", xy=(x_to, 2.05), xytext=(x_from, 2.05), arrowprops=dict(arrowstyle="->", color=RED, lw=1.8))
    ax.text((x_from + x_to) / 2, 2.2, f"c{i + 1}", ha="center", color=RED, fontsize=10)
ax.annotate("", xy=(xs[0] + 1.8, 2.05), xytext=(xs[0] + 2.9, 2.05), arrowprops=dict(arrowstyle="->", color=RED, lw=1.8))
ax.text(xs[0] + 3.0, 2.05, "carry in\n(0 to add)", va="center", fontsize=9.5, color=MUTED)
ax.annotate("", xy=(-0.5, 2.05), xytext=(xs[3], 2.05), arrowprops=dict(arrowstyle="->", color=RED, lw=1.8))
ax.text(-0.6, 2.05, "carry out\n(the C flag)", ha="right", va="center", fontsize=9.5, color=MUTED)
ax.text(6.0, -0.35, "bit 3 (most significant) on the left, bit 0 on the right, as numbers are written",
        ha="center", fontsize=9, color=MUTED, style="italic")
fig.savefig("fig_ripple.png", bbox_inches="tight", facecolor="white")
