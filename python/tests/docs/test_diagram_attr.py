from sp_svg_diagram import SVGDiagram

from .utils import compare_svg


def test_background_color():
    diagram = SVGDiagram()
    diagram.set_background_color("lightgray")
    node = diagram.add_node("A")
    node.set_label("A")
    svg = diagram.render()
    compare_svg("diagram_attr", "background_color", svg)
