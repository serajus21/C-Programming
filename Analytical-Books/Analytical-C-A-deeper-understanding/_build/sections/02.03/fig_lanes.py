import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
plt.rcParams["font.family"] = ["DejaVu Sans"]
NAVY="#1B2A4A"; BLUE=("#EAF1FB","#1F5FAD"); GRN=("#EAF5EA","#2E7D32"); AMB=("#FBF3E4","#8A5A00"); GREY="#8A93A3"
fig, ax = plt.subplots(figsize=(10, 3.6), dpi=200)
ax.set_xlim(-2.6, 12.9); ax.set_ylim(3.9, -0.3); ax.axis("off")
ax.text(-2.5, 0.0, "Listing 02.03-1, two builds: the same observable behavior, very different work", fontsize=11.5, weight="bold", color=NAVY)
# lane O0
ax.text(-2.5, 1.0, "gcc -O0", fontsize=11, color=NAVY, va="center", family="DejaVu Sans Mono")
for k in range(24):
    x = k*0.36
    ax.add_patch(Rectangle((x, 0.75), 0.3, 0.5, fc=BLUE[0], ec=BLUE[1], lw=0.8))
ax.text(4.3, 1.55, "100 passes: load i, add it to total in memory, add 1 to i in memory, compare, jump (shown in part)", fontsize=8.8, color=BLUE[1], ha="center")
ax.add_patch(Rectangle((9.0, 0.7), 3.8, 0.6, fc=AMB[0], ec=AMB[1], lw=1.4))
ax.text(10.9, 1.0, "printf: total = 5050", fontsize=9.5, ha="center", va="center", color=NAVY, family="DejaVu Sans Mono")
# lane O2
ax.text(-2.5, 2.7, "gcc -O2", fontsize=11, color=NAVY, va="center", family="DejaVu Sans Mono")
ax.add_patch(Rectangle((0, 2.45), 2.4, 0.5, fc=GRN[0], ec=GRN[1], lw=1.0))
ax.text(1.2, 2.7, "5050 → register", fontsize=8.5, ha="center", va="center", color=GRN[1])
ax.add_patch(Rectangle((9.0, 2.4), 3.8, 0.6, fc=AMB[0], ec=AMB[1], lw=1.4))
ax.text(10.9, 2.7, "printf: total = 5050", fontsize=9.5, ha="center", va="center", color=NAVY, family="DejaVu Sans Mono")
ax.plot([10.9, 10.9], [1.3, 2.4], color=AMB[1], lw=1.2, ls=(0,(3,2)))
ax.text(10.9, 3.45, "observable: identical", fontsize=9.5, ha="center", color=AMB[1])
ax.text(4.3, 3.45, "not observable: free to differ", fontsize=9.5, ha="center", color=GREY)
plt.savefig("fig_lanes.png", bbox_inches="tight", facecolor="white")
