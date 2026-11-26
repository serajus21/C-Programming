import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import FancyBboxPatch
plt.rcParams["font.family"] = ["DejaVu Sans"]
NAVY="#1B2A4A"; GREY="#8A93A3"; LINE="#5A6270"
BLUE=("#EAF1FB","#1F5FAD"); GRN=("#EAF5EA","#2E7D32"); AMB=("#FBF3E4","#8A5A00"); PUR=("#F1ECF8","#5E3A8C")
fig, ax = plt.subplots(figsize=(11, 5.2), dpi=200)
ax.set_xlim(1975, 2029); ax.set_ylim(-0.2, 6.3); ax.axis("off")
ax.text(1975, 6.1, "The editions of C, and what GCC compiles when you give no -std option", fontsize=12, weight="bold", color=NAVY)
# axis
ax.plot([1976, 2028], [3.2, 3.2], color=LINE, lw=1.2)
for y in range(1980, 2030, 5):
    ax.plot([y, y], [3.13, 3.27], color=LINE, lw=1)
    ax.text(y, 2.92, str(y), ha="center", fontsize=8.5, color=GREY)
# editions
eds = [(1978, "K&R", "the book\n(no standard)"), (1989.95, "C89", "ANSI\n(none)"), (1990.6, "C90", "ISO\n(none)"),
       (1995.3, "C95", "199409"), (1999.95, "C99", "199901"), (2011.95, "C11", "201112"),
       (2018.5, "C17", "201710"), (2024.83, "C23", "202311")]
for i, (x, name, ver) in enumerate(eds):
    h = 4.25 if i % 2 == 0 else 5.0
    ha = "center"; dx = 0
    if name == "C89": h, ha, dx = 4.25, "right", -0.35
    if name == "C90": h, ha, dx = 4.25, "left", 0.35
    ax.plot([x, x], [3.2, h - 0.12], color=LINE, lw=0.9)
    ax.plot([x], [3.2], marker="o", ms=6, color=NAVY)
    ax.text(x + dx, h, name, ha=ha, va="bottom", fontsize=10.5, weight="bold", color=NAVY)
    ax.text(x + dx, h + 0.33, ver, ha=ha, va="bottom", fontsize=7.6, color=GREY, linespacing=1.0)
ax.text(1976, 5.25, "upper line: __STDC_VERSION__\nlower line: edition", ha="left", fontsize=7.6, color=GREY, style="italic")
# GCC default bands
def band(x0, x1, col, label, sub):
    ax.add_patch(FancyBboxPatch((x0, 1.7), x1 - x0, 0.55, boxstyle="round,pad=0,rounding_size=0.12", facecolor=col[0], edgecolor=col[1], lw=1.1))
    ax.text((x0 + x1) / 2, 1.975, label, ha="center", va="center", fontsize=9, color=col[1], weight="bold")
    ax.text((x0 + x1) / 2, 1.55, sub, ha="center", va="top", fontsize=7.8, color=col[1])
ax.text(1976, 2.5, "GCC's default dialect", fontsize=9.5, color=NAVY, weight="bold")
band(1987.4, 2015.3, AMB, "GNU C, later named gnu89 / gnu90", "GCC 1.0 (1987) to 4.9")
band(2015.3, 2018.35, PUR, "gnu11", "GCC 5–7")
band(2018.35, 2025.3, BLUE, "gnu17", "GCC 8–14")
band(2025.3, 2028.2, GRN, "gnu23", "GCC 15+")
# your compilers
def mark(x, text, y=0.75):
    ax.annotate("", xy=(x, 1.2), xytext=(x, y + 0.1), arrowprops=dict(arrowstyle="->", color=LINE, lw=1))
    ax.text(x, y, text, ha="center", va="top", fontsize=8.2, color=NAVY)
mark(2018.05, "avr-gcc 7.3 (Jan 2018)\ninside the Arduino IDE:\ngnu11", 0.85)
mark(2026.75, "GCC 16 on your\nFedora 44:\ngnu23", 0.85)
fig.savefig("fig_timeline.png", bbox_inches="tight", facecolor="white")
