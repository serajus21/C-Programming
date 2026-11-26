import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
plt.rcParams["font.family"] = ["DejaVu Sans"]
NAVY="#1B2A4A"; BLUE=("#EAF1FB","#1F5FAD"); GRN=("#EAF5EA","#2E7D32"); AMB=("#FBF3E4","#8A5A00"); RED=("#FBE9E7","#B23A2B"); GREY="#8A93A3"
NB = 40                      # bit positions drawn: 39 .. 0
W = 0.25                     # cell width
fig, ax = plt.subplots(figsize=(10, 5.0), dpi=200)
ax.set_xlim(-3.3, NB*W + 3.2); ax.set_ylim(5.9, -0.5); ax.axis("off")
ax.text(-3.2, 0.0, "Listing 02.04-4: the value 1 shifted left by 32 places, three ways", fontsize=11.5, weight="bold", color=NAVY)
def row(y, onebit, col, label, sub, result, width_bits):
    ax.text(-3.2, y + 0.25, label, fontsize=10, color=NAVY, weight="bold", va="center")
    ax.text(0, y + 0.82, sub, fontsize=8.6, color=GREY, va="center", zorder=3, bbox=dict(facecolor="white", edgecolor="none", pad=1.0))
    for k in range(NB):
        bit = NB - 1 - k
        x = k * W
        inreg = bit < width_bits
        fc = col[0] if inreg else "white"
        ec = col[1] if inreg else "#D5D9E0"
        ax.add_patch(Rectangle((x, y), W, 0.5, facecolor=fc, edgecolor=ec, lw=0.8))
        if bit == onebit:
            ax.text(x + W/2, y + 0.25, "1", ha="center", va="center", fontsize=8.5, weight="bold", color=col[1])
    ax.text(NB*W + 0.2, y + 0.25, result, fontsize=10, va="center", color=NAVY, family="DejaVu Sans Mono")
# boundary of 32 bits
xb = (NB - 32) * W
ax.plot([xb, xb], [0.55, 5.25], ls="--", color=GREY, lw=1)
ax.text(xb + 0.1, 5.55, "32-bit boundary", fontsize=8.5, color=GREY, ha="left")
ax.text(0, 5.55, "bit 39", fontsize=8.5, color=GREY, ha="left")
ax.text(NB*W, 5.55, "bit 0", fontsize=8.5, color=GREY, ha="right")
row(0.7, 0, BLUE, "x86-64, GCC", "sall %cl: the count is masked to 5 bits; 32 becomes 0", "= 1", 32)
row(2.25, None, GRN, "AVR, avr-gcc", "a loop shifts one place at a time, 32 times; the 1 leaves the top", "= 0", 32)
row(3.8, 32, AMB, "x86-64, Clang -O2", "shlq %cl: a 64-bit shift; the 1 lands at bit 32", "= 4294967296", 64)
fig.savefig("fig_shift.png", bbox_inches="tight", facecolor="white")
