from sp_svg_diagram import SVGDiagram

from .utils import compare_svg


def test_empty():
    diagram = SVGDiagram()
    svg = diagram.render()
    compare_svg("concept", "empty", svg)


def test_node():
    diagram = SVGDiagram()
    node = diagram.add_node("A")
    node.set_center(0, 0)
    node.set_label("foo\nbar")
    svg = diagram.render()
    compare_svg("concept", "node", svg)


def test_edge():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_center(0, 0)
    node2 = diagram.add_node("B")
    node2.set_center(60, 80)
    diagram.add_edge("A", "B")
    svg = diagram.render()
    compare_svg("concept", "edge", svg)
