import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch
plt.rcParams["font.family"] = ["Noto Sans", "DejaVu Sans"]
names = ["HALT","LOAD","STORE","ADD","SUB","JUMP","JZ","OUT"]
mem = {0:0x39,1:0x78,2:0x59,3:0x38,4:0x9A,5:0x58,6:0xC8,7:0xA0,8:0x39,9:0xE0,10:0x00,24:10,25:0,26:1}
dnames = {24:"n", 25:"sum", 26:"one"}
fig, ax = plt.subplots(figsize=(8.6, 4.6), dpi=200)
ax.set_xlim(0, 8); ax.set_ylim(-0.15, 4.35); ax.axis("off"); ax.invert_yaxis()
for a in range(32):
    r, c = divmod(a, 8)
    x, y = c, r + 0.25
    if a <= 10:   fc, ec = "#EAF1FB", "#1F5FAD"
    elif a in dnames: fc, ec = "#EAF5EA", "#2E7D32"
    else:         fc, ec = "#F4F5F7", "#B8BEC8"
    ax.add_patch(FancyBboxPatch((x+0.05, y+0.05), 0.9, 0.9, boxstyle="round,pad=0,rounding_size=0.06", fc=fc, ec=ec, lw=1.3))
    ax.text(x+0.1, y+0.17, str(a), fontsize=8.5, color="#5A6270", va="center")
    v = mem.get(a, 0)
    ax.text(x+0.5, y+0.42, f"{v:08b}", fontsize=9.5, family="DejaVu Sans Mono", ha="center", va="center", color="#1B2A4A")
    if a <= 10:
        op, ad = v >> 5, v & 31
        lab = names[op] + ("" if op in (0, 7) else f" {ad}")
        ax.text(x+0.5, y+0.72, lab, fontsize=9.5, ha="center", va="center", color="#1F5FAD", weight="bold")
    elif a in dnames:
        ax.text(x+0.5, y+0.72, f"{dnames[a]} = {v}", fontsize=9.5, ha="center", va="center", color="#2E7D32", weight="bold")
ax.text(0.05, 0.08, "each cell: its address, its bits, and their meaning", fontsize=9, color="#5A6270")
ax.text(4.6, 0.08, "■ instructions", fontsize=9.5, color="#1F5FAD")
ax.text(5.95, 0.08, "■ data", fontsize=9.5, color="#2E7D32")
ax.text(6.75, 0.08, "■ unused", fontsize=9.5, color="#8A93A3")
plt.savefig("fig_mem.png", bbox_inches="tight", facecolor="white")
