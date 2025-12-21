from sp_svg_diagram import SVGDiagram, SVGNode

from .utils import compare_svg


def test_label():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_center(0, 0)
    node1.set_label("foobar")
    node2 = diagram.add_node("B")
    node2.set_center(150, 0)
    node2.set_label("Pybind11\nEmscripten")
    node3 = diagram.add_node("C")
    node3.set_center(300, 0)
    node3.set_label("星分翼轸\n地接衡庐")
    svg = diagram.render()
    compare_svg("node_attr", "label", svg)


def test_shape():
    diagram = SVGDiagram()
    shapes = [
        SVGNode.SHAPE_ELLIPSE,
        SVGNode.SHAPE_NONE,
        SVGNode.SHAPE_CIRCLE,
        SVGNode.SHAPE_DOUBLE_CIRCLE,
        SVGNode.SHAPE_RECT,
    ]
    for i, shape in enumerate(shapes):
        node = diagram.add_node(shape)
        node.set_shape(shape)
        node.set_center((i % 3) * 150.0, (i // 3) * 100.0)
        node.set_label(shape)
    svg = diagram.render()
    compare_svg("node_attr", "shape", svg)


def test_margin():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_center(0, 0)
    node1.set_label("Larger\nMargin")
    node1.set_margin(32, 8)
    node2 = diagram.add_node("B")
    node2.set_center(150, 0)
    node2.set_label("No\nMargin")
    node2.set_margin(0, 0)
    node3 = diagram.add_node("C")
    node3.set_center(300, 0)
    node3.set_label("Negative\nMargin")
    node3.set_margin(-10, -10)
    svg = diagram.render()
    compare_svg("node_attr", "margin", svg)


def test_text_size():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_label("🐱🐶🙈🙉🙊")
    node2 = diagram.add_node("B")
    node2.set_center(0, 50)
    node2.set_label("🐱🐶🙈🙉🙊")
    node2.set_text_size(80, 16)
    svg = diagram.render()
    compare_svg("node_attr", "text_size", svg)


def test_node_size():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_label("A")
    node2 = diagram.add_node("B")
    node2.set_label("B")
    node2.set_center(150, 0)
    node2.set_fixed_size(80, 30)
    svg = diagram.render()
    compare_svg("node_attr", "node_size", svg)


def test_color():
    diagram = SVGDiagram()
    node = diagram.add_node("A")
    node.set_label("color")
    node.set_color("limegreen")
    node.set_fill_color("#EEEEEE")
    node.set_font_color("rgb(66,92,214)")
    svg = diagram.render()
    compare_svg("node_attr", "color", svg)

def test_pen_width():
    diagram = SVGDiagram()
    for i in range(3):
        pen_width = 1 + i * 2
        node = diagram.add_node(f"node{i}")
        node.set_center(i * 150, 0)
        node.set_label(f"penWidth={pen_width}")
        node.set_pen_width(pen_width)
    svg = diagram.render()
    compare_svg("node_attr", "pen_width", svg)
