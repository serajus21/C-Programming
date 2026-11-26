import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
plt.rcParams["font.family"] = ["DejaVu Sans"]
NAVY="#1B2A4A"; BLUE=("#EAF1FB","#1F5FAD"); RED=("#FCEBEB","#B3261E"); GREY="#8A93A3"
fig, ax = plt.subplots(figsize=(9.5, 3.1), dpi=200)
ax.set_xlim(-0.3, 10.6); ax.set_ylim(3.3, -0.4); ax.axis("off")
ax.text(0, 0.0, "struct record r  (5 ints, side by side in memory; offsets in bytes on the laptop)", fontsize=11, weight="bold", color=NAVY)
labels = ["readings[0]","readings[1]","readings[2]","readings[3]","checksum"]
for k,l in enumerate(labels):
    fc,ec = (RED if k==4 else BLUE)
    ax.add_patch(Rectangle((k*2.0, 0.6), 1.9, 0.9, fc=fc, ec=ec, lw=1.5))
    ax.text(k*2.0+0.95, 1.05, l, ha="center", va="center", fontsize=10.5, family="DejaVu Sans Mono", color=NAVY)
    ax.text(k*2.0+0.95, 1.75, f"offset {4*k}", ha="center", va="center", fontsize=9, color=GREY)
ax.plot([0, 7.9], [2.05, 2.05], color=BLUE[1], lw=1.4)
ax.text(3.95, 2.3, "the array: valid indexes 0 to 3", ha="center", fontsize=9.5, color=BLUE[1])
ax.annotate("", xy=(9.75, 1.52), xytext=(9.75, 2.6), arrowprops=dict(arrowstyle="->", color=RED[1], lw=1.6))
ax.text(9.0, 2.95, "readings[4] would be at offset 16:\nthe same bytes as checksum", ha="center", fontsize=9.5, color=RED[1])
plt.savefig("fig_overrun.png", bbox_inches="tight", facecolor="white")
