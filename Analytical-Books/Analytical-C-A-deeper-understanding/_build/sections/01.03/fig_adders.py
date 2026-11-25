import schemdraw
from schemdraw import logic
import schemdraw.elements as elm
schemdraw.config(fontsize=12, font='Noto Sans', lw=1.4)

# Half adder: XOR gives the sum, AND gives the carry
with schemdraw.Drawing(file='fig_half_adder.png', dpi=200, show=False) as d:
    x = d.add(logic.Xor().at((3, 1.2)).anchor('in1').right())
    a = d.add(logic.And().at((3, -1.2)).anchor('in1').right())
    d.add(elm.Line().at((0, x.in1[1])).to(x.in1))
    d.add(elm.Label().at((-0.2, x.in1[1])).label('A', loc='left'))
    d.add(elm.Line().at((0, x.in2[1] - 0.0)).to((0.8, x.in2[1])))
    d.add(elm.Label().at((-0.2, x.in2[1])).label('B', loc='left'))
    d.add(elm.Line().at((0.8, x.in2[1])).to(x.in2))
    d.add(elm.Dot().at((1.4, x.in1[1])))
    d.add(logic.Wire('|-').at((1.4, x.in1[1])).to(a.in1))
    d.add(elm.Dot().at((2.0, x.in2[1])))
    d.add(logic.Wire('|-').at((2.0, x.in2[1])).to(a.in2))
    d.add(elm.Line().at(x.out).right(1)); d.add(elm.Label().label('S (sum)', loc='right'))
    d.add(elm.Line().at(a.out).right(1)); d.add(elm.Label().label('C (carry)', loc='right'))

# Full adder from two half adders and an OR gate
with schemdraw.Drawing(file='fig_full_adder.png', dpi=200, show=False) as d:
    x1 = d.add(logic.Xor().at((3, 2.0)).anchor('in1').right().label('XOR 1', loc='top'))
    a1 = d.add(logic.And().at((3, -1.6)).anchor('in1').right().label('AND 1', loc='bottom'))
    x2 = d.add(logic.Xor().at((8, 2.6)).anchor('in2').right().label('XOR 2', loc='top'))
    a2 = d.add(logic.And().at((8, 0.6)).anchor('in2').right().label('AND 2', loc='bottom'))
    o = d.add(logic.Or().at((12.5, -0.2)).anchor('in1').right())
    # inputs A, B
    d.add(elm.Line().at((0, x1.in1[1])).to(x1.in1)); d.add(elm.Label().at((-0.2, x1.in1[1])).label('A', loc='left'))
    d.add(elm.Line().at((0, x1.in2[1])).to(x1.in2)); d.add(elm.Label().at((-0.2, x1.in2[1])).label('B', loc='left'))
    d.add(elm.Dot().at((1.2, x1.in1[1]))); d.add(logic.Wire('|-').at((1.2, x1.in1[1])).to(a1.in1))
    d.add(elm.Dot().at((1.8, x1.in2[1]))); d.add(logic.Wire('|-').at((1.8, x1.in2[1])).to(a1.in2))
    # carry in
    cin_y = x2.in1[1] + 0.9
    d.add(elm.Line().at((0, cin_y)).to((6.6, cin_y))); d.add(elm.Label().at((-0.2, cin_y)).label('Cin', loc='left'))
    d.add(logic.Wire('|-').at((6.6, cin_y)).to(x2.in1))
    d.add(elm.Dot().at((6.6, x2.in1[1]))); d.add(logic.Wire('|-').at((6.6, x2.in1[1])).to(a2.in1))
    # XOR1 output to XOR2 and AND2
    d.add(logic.Wire('-|').at(x1.out).to((7.2, x2.in2[1]))); d.add(elm.Line().at((7.2, x2.in2[1])).to(x2.in2))
    d.add(elm.Dot().at((7.2, x1.out[1])))
    d.add(logic.Wire('|-').at((7.2, x2.in2[1])).to(a2.in2))
    # ORs
    d.add(logic.Wire('-|').at(a2.out).to(o.in1))
    d.add(logic.Wire('-|').at(a1.out).to(o.in2))
    d.add(elm.Line().at(x2.out).right(4.5)); d.add(elm.Label().label('S', loc='right'))
    d.add(elm.Line().at(o.out).right(1)); d.add(elm.Label().label('Cout', loc='right'))
