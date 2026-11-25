# Voltage transfer curve of a CMOS inverter, computed from the simple
# "square-law" transistor model.  VDD = 5 V, |Vt| = 0.7 V, matched devices.
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
plt.rcParams.update({"font.family": ["Noto Sans", "DejaVu Sans"], "font.size": 10})
VDD, VT, K = 5.0, 0.7, 1.0


def ids(vgs, vds):                      # current through one transistor
    if vgs <= VT:
        return 0.0                      # off
    if vds >= vgs - VT:                 # saturation
        return 0.5 * K * (vgs - VT) ** 2
    return K * ((vgs - VT) * vds - 0.5 * vds ** 2)   # linear region


def vout_for(vin):                      # find Vout where I(nMOS) = I(pMOS)
    lo, hi = 0.0, VDD
    for _ in range(80):
        mid = 0.5 * (lo + hi)
        i_n = ids(vin, mid)             # nMOS: Vgs = Vin, Vds = Vout
        i_p = ids(VDD - vin, VDD - mid) # pMOS: Vsg = VDD - Vin, Vsd = VDD - Vout
        if i_n > i_p:
            hi = mid                    # pull-down stronger: Vout must be lower
        else:
            lo = mid
    return 0.5 * (lo + hi)


vins = [i * 0.005 for i in range(1001)]
vouts = [vout_for(v) for v in vins]
fig, ax = plt.subplots(figsize=(6.4, 4.2), dpi=200)
ax.axvspan(1.5, 3.0, color="#FDECEA", alpha=0.7, lw=0)
ax.plot(vins, vouts, color="#1F5FAD", lw=2)
ax.text(1.97, 0.1, "band an\nATmega328P\ninput does\nnot guarantee", ha="center", va="bottom",
        fontsize=8.5, color="#B42318")
ax.annotate("input LOW: output firmly HIGH", xy=(0.9, 5.0), xytext=(0.1, 3.4), fontsize=9,
            arrowprops=dict(arrowstyle="->", color="#5A6270"))
ax.annotate("input HIGH: output firmly LOW", xy=(4.1, 0.02), xytext=(2.9, 1.4), fontsize=9,
            arrowprops=dict(arrowstyle="->", color="#5A6270"))
ax.set_xlabel("input voltage (V)")
ax.set_ylabel("output voltage (V)")
ax.set_xlim(0, 5); ax.set_ylim(-0.1, 5.3)
for s in ["top", "right"]:
    ax.spines[s].set_visible(False)
fig.tight_layout()
fig.savefig("fig_vtc.png", bbox_inches="tight", facecolor="white")
for v in [0.5, 1.5, 2.0, 2.3, 2.4, 2.5, 2.6, 2.7, 3.0, 3.5, 4.5]:
    print(f"Vin = {v:.2f} V  ->  Vout = {vout_for(v):.3f} V")
