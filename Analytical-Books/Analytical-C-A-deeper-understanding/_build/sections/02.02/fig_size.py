import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch
plt.rcParams["font.family"] = ["DejaVu Sans"]
NAVY="#1B2A4A"; BLUE="#1F5FAD"; GREY="#8A93A3"
rows = [("An empty main", 138),
        ("STEP 0: UART set-up, nothing printed", 276),
        ("STEP 1: one character, our own code\n(n % 10 brings in libgcc's division)", 374),
        ("STEP 2: printf, integers", 1730),
        ("STEP 3: printf with floating point\n(linked with printf_flt)", 3212)]
fig, ax = plt.subplots(figsize=(9, 4.2), dpi=200)
ys = list(range(len(rows)))[::-1]
for y,(lab,v) in zip(ys,rows):
    ax.add_patch(FancyBboxPatch((0, y-0.18), v, 0.36, boxstyle="round,pad=0,rounding_size=0.04",
                 mutation_aspect=0.004, fc=BLUE, ec="none"))
    ax.text(v+50, y, f"{v:,} bytes", va="center", fontsize=10.5, color=NAVY)
ax.set_yticks(ys); ax.set_yticklabels([r[0] for r in rows], fontsize=10, color=NAVY)
ax.set_xlim(0, 3900); ax.set_ylim(-0.6, len(rows)-0.4)
ax.set_xlabel("code size (bytes, the text column of avr-size; each build is separate)", fontsize=10, color=GREY)
for s in ["top","right","left"]: ax.spines[s].set_visible(False)
ax.spines["bottom"].set_color("#C9CED8"); ax.tick_params(axis="x", colors=GREY, labelsize=9); ax.tick_params(axis="y", length=0)
ax.xaxis.grid(True, color="#E6E9EF", lw=0.8); ax.set_axisbelow(True)
ax.text(3900, -0.55, "The Uno has 32,768 bytes of flash, of which its bootloader uses 512.", ha="right", va="bottom", fontsize=9, color=GREY)
plt.tight_layout(); plt.savefig("fig_size.png", facecolor="white")
