import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, FancyBboxPatch
plt.rcParams.update({"font.family": ["Noto Sans", "DejaVu Sans"], "font.size": 10})
NAVY="#1B2A4A"; BLUE="#1F5FAD"; RED="#B42318"; MUTED="#5A6270"; GREEN="#2E7D32"

# ---- memory array with a 2-to-4 decoder ----
fig, ax = plt.subplots(figsize=(8.6, 4.8), dpi=200)
ax.set_xlim(-0.5, 12.5); ax.set_ylim(-1.9, 6.2); ax.axis("off")
ax.add_patch(FancyBboxPatch((0.2, 0.6), 2.2, 4.6, boxstyle="round,pad=0.02,rounding_size=0.15", fc="#FBF3E4", ec="#8A5A00", lw=1.4))
ax.text(1.3, 5.45, "row decoder", ha="center", fontsize=10, color="#8A5A00", weight="bold")
ax.text(1.3, 0.1, "address\nA1 A0 = 1 0", ha="center", va="top", fontsize=10)
ax.annotate("", xy=(1.3, 0.6), xytext=(1.3, 0.15), arrowprops=dict(arrowstyle="->", color=MUTED))
rows_y = [4.6, 3.5, 2.4, 1.3]
for r, y in enumerate(rows_y):
    active = (r == 2)
    col = RED if active else MUTED
    ax.text(2.25, y, f"{r:02b}", ha="right", va="center", fontsize=9, color=col, weight="bold" if active else None)
    ax.plot([2.4, 10.4], [y, y], color=col, lw=2.2 if active else 1.0, zorder=1)
    ax.text(10.55, y, f"word line {r}" + ("  (active)" if active else ""), va="center", fontsize=9, color=col)
    for c in range(4):
        x = 3.4 + c * 1.9
        ax.add_patch(Rectangle((x - 0.35, y - 0.33), 0.7, 0.66, fc="#EAF1FB" if not active else "#FDECEA",
                               ec=BLUE if not active else RED, lw=1.2, zorder=2))
        ax.text(x, y, "bit", ha="center", va="center", fontsize=9, color=NAVY, zorder=3)
        ax.plot([x + 0.35, x + 0.55], [y - 0.18, y - 0.18], color=GREEN, lw=1.2, zorder=2)   # cell to bit line
for c in range(4):
    x = 3.4 + c * 1.9 + 0.55
    ax.plot([x, x], [0.6, 5.1], color=GREEN, lw=1.2)
    ax.text(x, 0.15, f"bit line\n{3 - c}", ha="center", va="top", fontsize=9, color=GREEN)
ax.annotate("", xy=(7.2, -1.25), xytext=(7.2, -0.75), arrowprops=dict(arrowstyle="->", color=GREEN))
ax.text(7.2, -1.4, "to sense amplifiers: the 4 bits of the selected row are read together", ha="center", va="top", fontsize=9, color=GREEN)
fig.savefig("fig_array.png", bbox_inches="tight", facecolor="white")

# ---- flash cell cross-section ----
def flash(ax, charged):
    ax.set_xlim(0, 10); ax.set_ylim(-0.9, 7.6); ax.axis("off")
    ax.add_patch(Rectangle((0.5, 0), 9, 3.6, fc="#F4E3D0", ec=NAVY, lw=1))
    ax.text(5.0, 1.1, "p-type silicon", ha="center", va="center", fontsize=11, color=MUTED)
    ax.add_patch(Rectangle((1.0, 2.4), 2.2, 1.2, fc="#D6E4F5", ec=NAVY))
    ax.add_patch(Rectangle((6.8, 2.4), 2.2, 1.2, fc="#D6E4F5", ec=NAVY))
    ax.text(2.1, 3.0, "source", ha="center", va="center", fontsize=11); ax.text(7.9, 3.0, "drain", ha="center", va="center", fontsize=11)
    ax.add_patch(Rectangle((3.0, 3.6), 4.0, 0.3, fc="white", ec=NAVY, hatch="...."))
    ax.add_patch(Rectangle((3.0, 3.9), 4.0, 0.8, fc="#C9D1D9" if not charged else "#F6C9C5", ec=NAVY))
    ax.text(5.0, 4.3, "floating gate  − − −" if charged else "floating gate", ha="center", va="center",
            fontsize=11, color=RED if charged else NAVY)
    ax.add_patch(Rectangle((3.0, 4.7), 4.0, 0.3, fc="white", ec=NAVY, hatch="...."))
    ax.add_patch(Rectangle((3.0, 5.0), 4.0, 0.8, fc="#9AA1AC", ec=NAVY))
    ax.text(5.0, 5.4, "control gate", ha="center", va="center", fontsize=11, color="white", weight="bold")
    ax.text(8.45, 4.95, "insulating\noxide", ha="center", va="center", fontsize=10, color=MUTED)
    for yy in (3.75, 4.85):
        ax.plot([7.0, 7.75], [yy, 4.95 + (0.0 if yy > 4 else -0.25)], color=MUTED, lw=0.8)
    ax.text(5.0, 6.75, "electrons trapped: the transistor\nneeds a higher gate voltage to turn on" if charged
            else "no trapped charge: the transistor\nturns on at the normal gate voltage", ha="center", fontsize=11,
            color=RED if charged else MUTED)
    ax.text(5.0, -0.6, "programmed" if charged else "erased", ha="center", fontsize=12, weight="bold", color=RED if charged else BLUE)
fig, axs = plt.subplots(1, 2, figsize=(9.2, 4.0), dpi=200)
flash(axs[0], False); flash(axs[1], True)
fig.tight_layout(); fig.savefig("fig_flash.png", bbox_inches="tight", facecolor="white")
