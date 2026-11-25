import schemdraw
from schemdraw import logic
import schemdraw.elements as elm
schemdraw.config(fontsize=12, font='Noto Sans', lw=1.4)

# Two inverters in a loop
with schemdraw.Drawing(file='fig_loop.png', dpi=200, show=False) as d:
    n1 = d.add(logic.Not().at((0, 0)).right())
    n2 = d.add(logic.Not().at((n1.out[0] + 1.6, -2.2)).left())
    d.add(logic.Wire('-|').at(n1.out).to((n1.out[0] + 2.8, n2.in1[1])))
    d.add(elm.Line().at((n1.out[0] + 2.8, n2.in1[1])).to(n2.in1))
    d.add(logic.Wire('-|').at(n2.out).to(n1.in1))
    d.add(elm.Dot().at((n1.out[0] + 1.2, n1.out[1])))
    d.add(elm.Label().at((n1.out[0] + 1.2, n1.out[1] + 0.45)).label('Q'))
    d.add(elm.Dot().at((n2.out[0] - 0.4, n2.out[1])))
    d.add(elm.Label().at((n2.out[0] - 0.4, n2.out[1] - 0.45)).label("Q′"))

# SR latch from two NOR gates
with schemdraw.Drawing(file='fig_sr.png', dpi=200, show=False) as d:
    g1 = d.add(logic.Nor().at((3, 0)).anchor('in1').right())
    g2 = d.add(logic.Nor().at((3, -3.0)).anchor('in2').right())
    d.add(elm.Line().at((0, g1.in1[1])).to(g1.in1)); d.add(elm.Label().at((-0.2, g1.in1[1])).label('R (reset)', loc='left'))
    d.add(elm.Line().at((0, g2.in2[1])).to(g2.in2)); d.add(elm.Label().at((-0.2, g2.in2[1])).label('S (set)', loc='left'))
    d.add(elm.Line().at(g1.out).right(2.2)); d.add(elm.Label().label('Q', loc='right'))
    d.add(elm.Line().at(g2.out).right(2.2)); d.add(elm.Label().label("Q′", loc='right'))
    x1 = g1.out[0] + 1.0
    d.add(elm.Dot().at((x1, g1.out[1])))
    d.add(elm.Line().at((x1, g1.out[1])).down(1.0))
    d.add(elm.Line().to((g2.in1[0] - 1.0, g1.out[1] - 1.0)))
    d.add(logic.Wire('|-').at((g2.in1[0] - 1.0, g1.out[1] - 1.0)).to(g2.in1))
    x2 = g2.out[0] + 0.6
    d.add(elm.Dot().at((x2, g2.out[1])))
    d.add(elm.Line().at((x2, g2.out[1])).up(1.0))
    d.add(elm.Line().to((g1.in2[0] - 0.6, g2.out[1] + 1.0)))
    d.add(logic.Wire('|-').at((g1.in2[0] - 0.6, g2.out[1] + 1.0)).to(g1.in2))

# Timing: D latch versus D flip-flop
w = {'signal': [
    {'name': 'clock (or enable)',  'wave': 'l.h...l...h...l.'},
    {'name': 'D (input)',          'wave': 'l..h.l..h...l...'},
    {'name': 'Q of a D latch',     'wave': 'l..h.l....h.l...'},
    {'name': 'Q of a D flip-flop', 'wave': 'l.........h.....'},
]}
d = schemdraw.Drawing(show=False)
d.add(logic.TimingDiagram(w, ygap=.6, risetime=.15, grid=False))
d.save('fig_timing.png', dpi=200)
