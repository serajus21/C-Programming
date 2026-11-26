import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, FancyArrowPatch
plt.rcParams["font.family"] = ["DejaVu Sans"]
NAVY="#1B2A4A"; BLUE=("#EAF1FB","#1F5FAD"); GRN=("#EAF5EA","#2E7D32"); GREY="#8A93A3"; AMB=("#FBF3E4","#8A5A00")
fig, ax = plt.subplots(figsize=(10, 6.4), dpi=200)
ax.set_xlim(-1.2, 14.4); ax.set_ylim(8.9, -0.6); ax.axis("off")

# Top: word-addressed memory
ax.text(-1.1, 0.0, "Word-addressed (PDP-7, B's birthplace): the smallest thing with an address is an 18-bit word",
        fontsize=11.5, weight="bold", color=NAVY, va="center")
s = "hello, world"
words = [s[i:i+2] for i in range(0, 12, 2)]
for k, w in enumerate(words):
    x = k*2.2
    ax.add_patch(Rectangle((x, 0.6), 2.1, 1.0, fc=BLUE[0], ec=BLUE[1], lw=1.4))
    ax.plot([x+1.05, x+1.05], [0.6, 1.6], color=BLUE[1], lw=0.8, ls=(0,(2,2)))
    for j, ch in enumerate(w):
        ax.text(x+0.52+j*1.05, 1.0, repr(ch), ha="center", va="center", fontsize=12, family="DejaVu Sans Mono", color=NAVY)
        ax.text(x+0.52+j*1.05, 1.42, "9 bits", ha="center", va="center", fontsize=7.5, color=GREY)
    ax.text(x+1.05, 1.85, f"word {10+k}", ha="center", va="center", fontsize=9.5, color=BLUE[1])
ax.annotate("", xy=(2.2+1.05, 2.05), xytext=(1.05, 2.05),
            arrowprops=dict(arrowstyle="->", color=BLUE[1], lw=1.4, connectionstyle="arc3,rad=0.35"))
ax.text(2.15, 2.75, "p + 1 = the next word: two characters further", ha="center", fontsize=9.5, color=BLUE[1])
ax.text(-1.1, 3.25, "To reach one character: find its word (n / 2), pick its half (n % 2), shift and mask.\n"
        "To change one: read the word, mask out the old 9 bits, insert the new ones, write the word back.",
        fontsize=10, color=NAVY, va="top")

# Bottom: byte-addressed memory
ax.text(-1.1, 4.75, "Byte-addressed data memory (PDP-11, AVR, x86-64): every 8-bit byte has its own address",
        fontsize=11.5, weight="bold", color=NAVY, va="center")
for k, ch in enumerate(s):
    x = k*1.1
    ax.add_patch(Rectangle((x, 5.3), 1.0, 1.0, fc=GRN[0], ec=GRN[1], lw=1.4))
    ax.text(x+0.5, 5.8, repr(ch), ha="center", va="center", fontsize=11, family="DejaVu Sans Mono", color=NAVY)
    ax.text(x+0.5, 6.55, f"{100+k}", ha="center", va="center", fontsize=8.5, color=GRN[1])
ax.annotate("", xy=(1.6, 6.85), xytext=(0.5, 6.85),
            arrowprops=dict(arrowstyle="->", color=GRN[1], lw=1.4, connectionstyle="arc3,rad=0.4"))
ax.text(2.0, 7.2, "char pointer + 1: one byte further", ha="left", va="center", fontsize=9.5, color=GRN[1])
# a 16-bit int spanning two bytes
ax.add_patch(Rectangle((8.8, 7.25), 2.0, 0.8, fc=AMB[0], ec=AMB[1], lw=1.4))
ax.plot([9.8, 9.8], [7.25, 8.05], color=AMB[1], lw=0.8, ls=(0,(2,2)))
ax.text(9.8, 7.65, "a 16-bit int", ha="center", va="center", fontsize=9.5, color=NAVY)
ax.add_patch(Rectangle((10.9, 7.25), 2.0, 0.8, fc=AMB[0], ec=AMB[1], lw=1.4))
ax.plot([11.9, 11.9], [7.25, 8.05], color=AMB[1], lw=0.8, ls=(0,(2,2)))
ax.text(11.9, 7.65, "the next int", ha="center", va="center", fontsize=9.5, color=NAVY)
ax.text(8.8, 8.45, "PDP-11 and AVR: int pointer + 1 is two bytes further\n(four on x86-64). The type tells the compiler how far.", fontsize=9.5, color=AMB[1], va="center")
ax.text(-1.1, 8.1, "To reach or change one character: one load or one store,\nat its own address.", fontsize=10, color=NAVY, va="center")
plt.savefig("fig_mem.png", bbox_inches="tight", facecolor="white")
