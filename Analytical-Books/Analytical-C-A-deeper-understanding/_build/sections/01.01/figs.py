import math
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, FancyArrowPatch
plt.rcParams.update({"font.family": ["Noto Sans", "DejaVu Sans"], "font.size": 10.5})
NAVY="#1B2A4A"; BLUE="#1F5FAD"; GREEN="#2E7D32"; RED="#B42318"; MUTED="#5A6270"; AMBER="#8A5A00"

# ---------- Figure 1: logic levels of the ATmega328P at 5 V ----------
fig, ax = plt.subplots(figsize=(7.2, 5.0), dpi=200)
ax.set_xlim(0, 10); ax.set_ylim(-0.3, 5.6); ax.axis("off")
def axis(x):
    ax.plot([x, x], [0, 5.0], color=NAVY, lw=1.2)
    for v in [0,1,2,3,4,5]:
        ax.plot([x-0.08, x+0.08], [v, v], color=NAVY, lw=1)
        ax.text(x-0.15, v, f"{v} V", ha="right", va="center", fontsize=9, color=MUTED)
# output column
x0=1.6
axis(x0)
ax.add_patch(Rectangle((x0+0.1, 4.2), 2.1, 0.8, color="#EAF5EA", ec=GREEN))
ax.text(x0+1.15, 4.6, "guaranteed HIGH\n≥ 4.2 V", ha="center", va="center", fontsize=9, color=GREEN)
ax.add_patch(Rectangle((x0+0.1, 0.0), 2.1, 0.9, color="#EAF1FB", ec=BLUE))
ax.text(x0+1.15, 0.45, "guaranteed LOW\n≤ 0.9 V", ha="center", va="center", fontsize=9, color=BLUE)
ax.text(x0+1.15, 5.35, "What an output pin\nproduces", ha="center", fontsize=10, weight="bold", color=NAVY)
# input column
x1=6.4
axis(x1)
ax.add_patch(Rectangle((x1+0.1, 3.0), 2.1, 2.0, color="#EAF5EA", ec=GREEN))
ax.text(x1+1.15, 4.0, "read as 1\n≥ 3.0 V", ha="center", va="center", fontsize=9, color=GREEN)
ax.add_patch(Rectangle((x1+0.1, 1.5), 2.1, 1.5, color="#FDECEA", ec=RED, hatch="///", alpha=0.9))
ax.text(x1+1.15, 2.25, "not guaranteed\neither way", ha="center", va="center", fontsize=9, color=RED,
        bbox=dict(fc="white", ec="none", pad=1.5))
ax.add_patch(Rectangle((x1+0.1, 0.0), 2.1, 1.5, color="#EAF1FB", ec=BLUE))
ax.text(x1+1.15, 0.75, "read as 0\n≤ 1.5 V", ha="center", va="center", fontsize=9, color=BLUE)
ax.text(x1+1.15, 5.35, "What an input pin\naccepts", ha="center", fontsize=10, weight="bold", color=NAVY)
# noise margins
for (ya, yb, lab, col, xm) in [(4.2, 3.0, "high noise margin\n4.2 − 3.0 = 1.2 V", GREEN, 4.9),
                                (0.9, 1.5, "low noise margin\n1.5 − 0.9 = 0.6 V", BLUE, 4.9)]:
    ax.plot([x0+2.2, x1+0.1], [ya, ya], ls=":", color=col, lw=1)
    ax.plot([x0+2.2, x1+0.1], [yb, yb], ls=":", color=col, lw=1) if False else None
    ax.annotate("", xy=(xm, yb), xytext=(xm, ya), arrowprops=dict(arrowstyle="<->", color=col, lw=1.3))
    ax.text(xm-0.12, (ya+yb)/2, lab, ha="right", va="center", fontsize=8.5, color=col)
ax.plot([4.6, x1+0.1], [3.0, 3.0], ls=":", color=GREEN, lw=1)
ax.plot([4.6, x1+0.1], [1.5, 1.5], ls=":", color=BLUE, lw=1)
fig.savefig("fig2.png", bbox_inches="tight", facecolor="white")

# ---------- Figure 2: same noise, two levels vs ten levels ----------
sigma = 0.4
xs = [i*0.005 - 1.5 for i in range(int(8.0/0.005))]
def g(x, mu): return math.exp(-0.5*((x-mu)/sigma)**2)
fig, axs = plt.subplots(2, 1, figsize=(7.2, 4.6), dpi=200, sharex=True)
for ax, levels, title in [(axs[0], 2, "Two levels (binary): 0 V and 5 V"),
                          (axs[1], 10, "Ten levels (decimal): every 0.556 V")]:
    step = 5.0/(levels-1)
    for k in range(levels):
        mu = k*step
        ys = [g(x, mu) for x in xs]
        ax.plot(xs, ys, color=[BLUE, GREEN, AMBER, "#5B3E96"][k % 4], lw=1.2)
        ax.fill_between(xs, ys, alpha=0.12, color=[BLUE, GREEN, AMBER, "#5B3E96"][k % 4])
    for k in range(levels-1):
        ax.axvline((k+0.5)*step, color=RED, ls="--", lw=0.8)
    ax.set_yticks([]); ax.set_title(title, fontsize=10, loc="left", color=NAVY)
    for s in ["top", "right", "left"]: ax.spines[s].set_visible(False)
axs[1].set_xlabel("voltage actually received (V)   ·   dashed lines: decision thresholds")
axs[1].set_xlim(-1.5, 6.5)
fig.tight_layout()
fig.savefig("fig1.png", bbox_inches="tight", facecolor="white")

# ---------- Figure 3: a particle strike on a stored 1 (schematic) ----------
fig, ax = plt.subplots(figsize=(7.2, 3.4), dpi=200)
t = [i*0.01 for i in range(0, 1001)]
def node(tt, depth, flips):
    if tt < 3: return 5.0
    if not flips:
        return 5.0 - depth*math.exp(-(tt-3)/0.6)*(1-math.exp(-(tt-3)/0.05))
    return 5.0*math.exp(-(tt-3)/0.15)
ax.axhspan(3.0, 5.4, color="#EAF5EA", alpha=0.6); ax.axhspan(0, 1.5, color="#EAF1FB", alpha=0.6)
ax.axhspan(1.5, 3.0, color="#FDECEA", alpha=0.6)
ax.plot(t, [node(x, 1.6, False) for x in t], color=GREEN, lw=1.8, label="small strike: the cell recovers, still 1")
ax.plot(t, [node(x, 4.4, True) for x in t], color=RED, lw=1.8, label="large strike: the cell flips, now 0")
ax.axvline(3, color=MUTED, ls=":", lw=1); ax.text(3.05, 5.15, "particle passes", fontsize=9, color=MUTED)
ax.text(9.9, 4.2, "read as 1", ha="right", fontsize=9, color=GREEN)
ax.text(9.9, 2.1, "uncertain", ha="right", fontsize=9, color=RED)
ax.text(9.9, 0.6, "read as 0", ha="right", fontsize=9, color=BLUE)
ax.set_xlim(0, 10); ax.set_ylim(0, 5.4); ax.set_xticks([])
ax.set_xlabel("time  (schematic, not to scale; a real event lasts less than a nanosecond)")
ax.set_ylabel("voltage on the storage node (V)")
for s in ["top", "right"]: ax.spines[s].set_visible(False)
ax.legend(loc="center", bbox_to_anchor=(0.62, 0.42), fontsize=8.5, frameon=True, facecolor="white", edgecolor="none")
fig.tight_layout(); fig.savefig("fig3.png", bbox_inches="tight", facecolor="white")
