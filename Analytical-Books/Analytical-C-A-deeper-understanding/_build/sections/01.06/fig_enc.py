import matplotlib; matplotlib.use("Agg")
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
plt.rcParams["font.family"] = ["Noto Sans", "DejaVu Sans"]
C = {"op": ("#E9ECF3", "#1B2A4A"), "d": ("#EAF1FB", "#1F5FAD"),
     "r": ("#F1ECF8", "#5B3E96"), "K": ("#FBF3E4", "#8A5A00"), "k": ("#EAF5EA", "#2E7D32")}
rows = [
 ("add r24, r22   →  0x0F86   (stored as 86 0F)", "000011rdddddrrrr", "0000111110000110",
  [("opcode 000011",0,5,"op"),("r₄",6,6,"r"),("d = 11000 = 24",7,11,"d"),("r₃..r₀",12,15,"r")]),
 ("ldi r24, 0x0D   →  0xE08D   (stored as 8D E0)", "1110KKKKddddKKKK", "1110000010001101",
  [("opcode 1110",0,3,"op"),("K high = 0000",4,7,"K"),("d − 16 = 1000",8,11,"d"),("K low = 1101",12,15,"K")]),
 ("rjmp .-2   →  0xCFFF   (stored as FF CF)", "1100kkkkkkkkkkkk", "1100111111111111",
  [("opcode 1100",0,3,"op"),("k = 111111111111 = −1 (words)",4,15,"k")]),
]
fig, ax = plt.subplots(figsize=(9.2, 5.6), dpi=200)
ax.set_xlim(-0.2, 16.2); ax.set_ylim(len(rows)*2.25, -0.2); ax.axis("off")
for i,(title,pat,bits,fields) in enumerate(rows):
    y = i*2.25
    ax.text(0, y+0.15, title, fontsize=12, weight="bold", color="#1B2A4A", va="center", family="DejaVu Sans Mono")
    kind = {}
    for _,a,b,k in fields:
        for j in range(a,b+1): kind[j]=k
    for j in range(16):
        fc,ec = C[kind[j]]
        ax.add_patch(Rectangle((j, y+0.45), 1, 0.75, fc=fc, ec=ec, lw=1.2))
        ax.text(j+0.5, y+0.82, bits[j], ha="center", va="center", fontsize=13, family="DejaVu Sans Mono", color="#1B2A4A")
        ax.text(j+0.5, y+0.33, str(15-j), ha="center", va="center", fontsize=8.5, color="#8A93A3")
        ax.text(j+0.5, y+1.38, pat[j], ha="center", va="center", fontsize=9, family="DejaVu Sans Mono", color=ec)
    for lab,a,b,k in fields:
        ax.plot([a+0.08,b+0.92],[y+1.58,y+1.58], color=C[k][1], lw=1.4)
        ax.text((a+b+1)/2, y+1.8, lab, ha="center", va="center", fontsize=9.5, color=C[k][1])
plt.savefig("fig_enc.png", bbox_inches="tight", facecolor="white")
