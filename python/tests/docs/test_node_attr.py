from sp_svg_diagram import SVGDiagram

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
    node3.set_label("物华天宝\n人杰地灵")
    svg = diagram.render()
    compare_svg("node_attr", "label", svg)
