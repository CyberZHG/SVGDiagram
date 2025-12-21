from sp_svg_diagram import SVGDiagram

from .utils import compare_svg


def test_inherited():
    diagram = SVGDiagram()
    subgraph_inner = diagram.add_subgraph("subgraph-inner")
    subgraph_outer = diagram.add_subgraph("subgraph-outer")
    subgraph_outer.add_subgraph(subgraph_inner)

    node1 = diagram.add_node("A")
    node1.set_label("A")
    node1.set_center(0, 0)
    node2 = diagram.add_node("B")
    node2.set_label("B")
    node2.set_center(150, 0)
    edge1 = diagram.add_edge("A", "B")
    edge1.set_arrow_head()
    subgraph_inner.add_node(node1)
    subgraph_inner.add_node(node2)
    subgraph_inner.add_edge(edge1)
    subgraph_inner.default_node_attributes().set_pen_width(2)
    subgraph_inner.default_edge_attributes().set_pen_width(2)

    node3 = diagram.add_node("C")
    node3.set_label("C")
    node3.set_center(0, 60)
    node4 = diagram.add_node("D")
    node4.set_label("D")
    node4.set_center(150, 60)
    edge2 = diagram.add_edge("C", "D")
    edge2.set_arrow_head()
    edge3 = diagram.add_edge("B", "C")
    edge3.set_arrow_head()
    subgraph_outer.add_node(node3)
    subgraph_outer.add_node(node4)
    subgraph_outer.add_edge(edge2)
    subgraph_outer.add_edge(edge3)
    subgraph_outer.default_node_attributes().set_fill_color("lightgray")

    svg = diagram.render()
    compare_svg("subgraph_attr", "inherited", svg)