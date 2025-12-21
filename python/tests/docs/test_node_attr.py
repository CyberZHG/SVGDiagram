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
