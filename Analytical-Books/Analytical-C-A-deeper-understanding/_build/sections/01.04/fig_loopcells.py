import schemdraw
import schemdraw.elements as elm
from schemdraw import logic
schemdraw.config(fontsize=12, font='Noto Sans', lw=1.4)

def loop(d, with_access):
    n1 = d.add(logic.Not().at((0, 0)).right())
    xl = n1.start[0]; xr = n1.end[0]
    n2 = d.add(logic.Not().at((xr, -2.2)).left())
    d.add(elm.Line().at(n1.end).to(n2.start))             # Q node (right side)
    d.add(elm.Line().at(n2.end).to(n1.start))             # Q' node (left side)
    d.add(elm.Dot().at((xr, -1.1))); d.add(elm.Dot().at((xl, -1.1)))
    d.add(elm.Label().at((xr + 0.35, -0.75)).label('Q'))
    d.add(elm.Label().at((xl - 0.4, -0.75)).label("Q′"))
    if with_access:
        d.add(elm.Line().at((xr, -1.1)).right(0.5))
        d.add(elm.Switch().right().label('access', loc='top'))
        d.add(elm.Line().right(0.4)); bl = d.here
        d.add(elm.Line().at((bl[0], 1.2)).to((bl[0], -3.4)))
        d.add(elm.Label().at((bl[0], -3.8)).label('bit line'))
        d.add(elm.Line().at((xl, -1.1)).left(0.5))
        sw_len = d.unit
        bl2 = (xl - 0.5 - sw_len - 0.4, -1.1)
        d.add(elm.Line().at(bl2).right(0.4))
        d.add(elm.Switch().right().label('access', loc='top'))
        d.add(elm.Line().at((bl2[0], 1.2)).to((bl2[0], -3.4)))
        d.add(elm.Label().at((bl2[0], -3.8)).label("bit line′"))
        d.add(elm.Label().at(((bl[0] + bl2[0]) / 2, 1.5)).label('word line = 1 closes both access switches'))

with schemdraw.Drawing(file='fig_loop.png', dpi=200, show=False) as d:
    loop(d, False)
with schemdraw.Drawing(file='fig_sram.png', dpi=200, show=False) as d:
    loop(d, True)
# DRAM cell
with schemdraw.Drawing(file='fig_dram.png', dpi=200, show=False) as d:
    d.add(elm.Label().at((0, 3.35)).label('bit line'))
    d.here = (0, 3)
    d.add(elm.Line().down(1.0))
    t = d.add(elm.NFet(bulk=False).anchor('drain').theta(0).reverse())
    d.add(elm.Capacitor().down().at(t.source))
    d.add(elm.Label().at((2.4, t.source[1] - 1.5)).label('storage capacitor'))
    d.add(elm.Ground())
    d.add(elm.Line().at(t.gate).left(1.2))
    d.add(elm.Label().label('word line', loc='left'))
