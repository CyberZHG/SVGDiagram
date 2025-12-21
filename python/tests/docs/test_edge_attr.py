from sp_svg_diagram import SVGDiagram, SVGEdge

from .utils import compare_svg


def test_splines():
    diagram = SVGDiagram()
    splines_types = [
        SVGEdge.SPLINES_SPLINE,
        SVGEdge.SPLINES_LINE,
    ]
    for i, splines in enumerate(splines_types):
        y = i * 80.0
        tail_id, head_id = f"A{i}", f"B{i}"
        node1 = diagram.add_node(tail_id)
        node1.set_center(0, y)
        node1.set_label("A")
        node2 = diagram.add_node(head_id)
        node2.set_center(150, y)
        node2.set_label("B")
        edge = diagram.add_edge(tail_id, head_id)
        edge.set_splines(splines)
        edge.add_connection_point(50, y - 20)
        edge.add_connection_point(100, y + 20)
        edge.set_label(splines)
    svg = diagram.render()
    compare_svg("edge_attr", "splines", svg)


def test_arrow():
    diagram = SVGDiagram()
    arrow_types = [
        SVGEdge.ARROW_NONE,
        SVGEdge.ARROW_NORMAL,
        SVGEdge.ARROW_EMPTY,
    ]
    for i, arrow in enumerate(arrow_types):
        y = i * 60.0
        tail_id, head_id = f"A{i}", f"B{i}"
        node1 = diagram.add_node(tail_id)
        node1.set_center(0, y)
        node1.set_label("A")
        node2 = diagram.add_node(head_id)
        node2.set_center(150, y)
        node2.set_label("B")
        edge = diagram.add_edge(tail_id, head_id)
        edge.set_arrow_tail(SVGEdge.ARROW_NONE)
        edge.set_arrow_head(arrow)
        edge.set_label(arrow)
    svg = diagram.render()
    compare_svg("edge_attr", "arrow", svg)
