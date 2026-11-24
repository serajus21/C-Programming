import schemdraw
from schemdraw import logic
import schemdraw.elements as elm
schemdraw.config(fontsize=12, font='Noto Sans', lw=1.4)
# Gate symbols
with schemdraw.Drawing(file='fig_symbols.png', dpi=200, show=False) as d:
    x = 0
    for G, name in [(logic.Not, 'NOT'), (logic.And, 'AND'), (logic.Or, 'OR'),
                    (logic.Nand, 'NAND'), (logic.Nor, 'NOR'), (logic.Xor, 'XOR')]:
        g = d.add(G().at((x, 0)).right())
        d.add(elm.Label().at(((g.in1[0] + g.out[0]) / 2, -1.3)).label(name))
        x += 3.2
# XOR from four NANDs
with schemdraw.Drawing(file='fig_xor_nand.png', dpi=200, show=False) as d:
    n1 = d.add(logic.Nand().at((2, 0)).anchor('in1').right().label('n1', loc='bottom'))
    n2 = d.add(logic.Nand().at((6, 1.6)).anchor('in2').right().label('n2', loc='top'))
    n3 = d.add(logic.Nand().at((6, -1.6)).anchor('in1').right().label('n3', loc='bottom'))
    n4 = d.add(logic.Nand().at((10, 0)).anchor('in1').right())
    # inputs
    d.add(logic.Wire('-|', k=0.8).at((0, 2.1)).to(n2.in1))
    d.add(elm.Dot().at((1.0, 2.1)))
    d.add(logic.Wire('|-').at((1.0, 2.1)).to(n1.in1))
    d.add(logic.Wire('-|', k=0.8).at((0, -2.1)).to(n3.in2))
    d.add(elm.Dot().at((1.0, -2.1)))
    d.add(logic.Wire('|-').at((1.0, -2.1)).to(n1.in2))
    d.add(elm.Label().at((-0.3, 2.1)).label('A', loc='left'))
    d.add(elm.Label().at((-0.3, -2.1)).label('B', loc='left'))
    d.add(elm.Dot().at((4.6, n1.out[1])))
    d.add(elm.Line().at(n1.out).to((4.6, n1.out[1])))
    d.add(logic.Wire('|-').at((4.6, n1.out[1])).to(n2.in2))
    d.add(logic.Wire('|-').at((4.6, n1.out[1])).to(n3.in1))
    d.add(logic.Wire('-|').at(n2.out).to(n4.in1))
    d.add(logic.Wire('-|').at(n3.out).to(n4.in2))
    d.add(elm.Line().at(n4.out).right(0.8))
    d.add(elm.Label().label('A XOR B', loc='right'))
