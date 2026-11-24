import schemdraw
import schemdraw.elements as elm
schemdraw.config(fontsize=12, font='Noto Sans', lw=1.4)

def inverter(d, x0, vin_label, on_p, on_n, vout_label):
    NAVY='#1B2A4A'; GREEN='#2E7D32'; GREY='#9AA1AC'; RED='#B42318'
    d.here = (x0, 0)
    vdd = d.add(elm.Vdd().label('VDD (5 V)'))
    p = d.add(elm.PFet(bulk=False).anchor('source').theta(0).reverse().color(GREEN if on_p else GREY))
    # drain of pmos to output node
    d.add(elm.Line().at(p.drain).down(0.6))
    out = d.add(elm.Dot())
    n = d.add(elm.NFet(bulk=False).anchor('drain').theta(0).reverse().color(GREEN if on_n else GREY))
    d.add(elm.Ground().at(n.source))
    d.add(elm.Line().at(out.center).right(1.6))
    d.add(elm.Dot(open=True).label(vout_label, loc='right'))
    # gates joined to input
    d.add(elm.Line().at(p.gate).left(0.6))
    g1 = d.add(elm.Dot())
    d.add(elm.Line().at(n.gate).left(0.6))
    g2 = d.add(elm.Dot())
    d.add(elm.Line().at(g1.center).to(g2.center))
    d.add(elm.Line().at(((g1.center[0]+g2.center[0])/2, (g1.center[1]+g2.center[1])/2)).left(1.0))
    d.add(elm.Dot(open=True).label(vin_label, loc='left'))
    d.add(elm.Label().at((p.drain[0]+1.6, p.center[1])).label('pMOS: ' + ('ON' if on_p else 'off'), color=GREEN if on_p else GREY))
    d.add(elm.Label().at((n.drain[0]+1.6, n.center[1])).label('nMOS: ' + ('ON' if on_n else 'off'), color=GREEN if on_n else GREY))

with schemdraw.Drawing(file='fig_inverter.png', dpi=200, show=False) as d:
    inverter(d, 0, 'in = 1 (HIGH)', False, True, 'out = 0')
    inverter(d, 9, 'in = 0 (LOW)', True, False, 'out = 1')
