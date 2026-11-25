import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
plt.rcParams.update({"font.family": ["Noto Sans", "DejaVu Sans"], "font.size": 10})
NAVY = "#1B2A4A"; MUTED = "#5A6270"
P_COL = "#F4E3D0"; N_COL = "#D6E4F5"; GATE = "#9AA1AC"; CH = "#1F5FAD"


def panel(ax, on):
    ax.set_xlim(0, 10); ax.set_ylim(-0.7, 7.0); ax.axis("off")
    ax.add_patch(Rectangle((0.5, 0), 9, 4, fc=P_COL, ec=NAVY, lw=1))            # p-type body
    ax.text(5, 0.45, "p-type silicon\n(very few free electrons)", ha="center", fontsize=11, color=MUTED)
    ax.add_patch(Rectangle((1.0, 2.6), 2.4, 1.4, fc=N_COL, ec=NAVY, lw=1))      # source
    ax.add_patch(Rectangle((6.6, 2.6), 2.4, 1.4, fc=N_COL, ec=NAVY, lw=1))      # drain
    ax.text(2.2, 3.25, "n-type\nsource", ha="center", va="center", fontsize=11)
    ax.text(7.8, 3.25, "n-type\ndrain", ha="center", va="center", fontsize=11)
    ax.add_patch(Rectangle((3.2, 4.0), 3.6, 0.35, fc="white", ec=NAVY, lw=1, hatch="...."))  # oxide
    ax.add_patch(Rectangle((3.2, 4.35), 3.6, 0.9, fc=GATE, ec=NAVY, lw=1))      # gate
    ax.text(5, 4.8, "gate", ha="center", va="center", fontsize=11.5, color="white", weight="bold")
    for x in (2.2, 7.8):
        ax.plot([x, x], [4.0, 6.1], color=NAVY, lw=1.2)
    ax.plot([5, 5], [5.25, 6.1], color=NAVY, lw=1.2)
    ax.text(2.2, 6.25, "source 0 V", ha="center", fontsize=11)
    ax.text(7.8, 6.25, "drain 5 V", ha="center", fontsize=11)
    ax.text(5, 6.25, "gate 5 V" if on else "gate 0 V", ha="center", fontsize=11.5, weight="bold",
            color=CH if on else MUTED)
    if on:
        ax.add_patch(Rectangle((3.4, 3.72), 3.2, 0.28, fc=CH, ec="none"))
        ax.text(5, 3.15, "channel of electrons\nattracted by the gate", ha="center", va="center",
                fontsize=9.5, color=CH)
        ax.text(5, -0.55, "ON: current can flow", ha="center",
                fontsize=12, color=CH, weight="bold")
    else:
        ax.text(5, 3.25, "no channel", ha="center", va="center", fontsize=11, color=MUTED)
        ax.text(5, -0.55, "OFF: no conducting path", ha="center",
                fontsize=12, color=MUTED, weight="bold")


fig, axs = plt.subplots(1, 2, figsize=(9.6, 3.8), dpi=200)
panel(axs[0], False)
panel(axs[1], True)
fig.tight_layout()
fig.savefig("fig_mosfet.png", bbox_inches="tight", facecolor="white")
