import schemdraw
import schemdraw.elements as elm
schemdraw.config(fontsize=12, font='Noto Sans', lw=1.4)
BLUE='#1F5FAD'; AMBER='#8A5A00'
with schemdraw.Drawing(file='fig_nand_cmos.png', dpi=200, show=False) as d:
    d.here = (0, 6)
    d.add(elm.Line().right(4))
    d.add(elm.Vdd().at((2, 6)).label('VDD'))
    p1 = d.add(elm.PFet(bulk=False).anchor('source').at((0, 6)).theta(0).reverse().color(BLUE))
    p2 = d.add(elm.PFet(bulk=False).anchor('source').at((4, 6)).theta(0).reverse().color(AMBER))
    d.add(elm.Line().at(p1.drain).down(0.6)); a = d.here
    d.add(elm.Line().at(p2.drain).down(0.6)); b = d.here
    d.add(elm.Line().at(a).to(b))
    d.add(elm.Dot().at(a))
    d.add(elm.Line().at(b).right(1.5))
    d.add(elm.Dot(open=True).label('out = NOT (A AND B)', loc='right'))
    n1 = d.add(elm.NFet(bulk=False).anchor('drain').at(a).theta(0).reverse().color(BLUE))
    n2 = d.add(elm.NFet(bulk=False).anchor('drain').at(n1.source).theta(0).reverse().color(AMBER))
    d.add(elm.Ground().at(n2.source))
    for f, lab, col in [(p1, 'A', BLUE), (p2, 'B', AMBER), (n1, 'A', BLUE), (n2, 'B', AMBER)]:
        d.add(elm.Line().at(f.gate).left(0.5).color(col))
        d.add(elm.Label().label(lab, loc='left', color=col))
    d.add(elm.Label().at((6.2, 5.0)).label('pMOS in parallel:\nout is pulled up if\nA = 0 OR B = 0', loc='right'))
    d.add(elm.Label().at((2.0, 1.6)).label('nMOS in series:\nout is pulled down only if\nA = 1 AND B = 1', loc='right'))
