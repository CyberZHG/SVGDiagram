from sp_svg_diagram import SVGDiagram


if __name__ == "__main__":
    diagram = SVGDiagram()
    node_a = diagram.add_node("a")
    node_a.set_center(0, 0)
    node_a.set_label("foo")
    node_b = diagram.add_node("b")
    node_b.set_center(100, 60)
    node_b.set_label("bar")
    diagram.add_edge("a", "b")
    diagram.to_svg("demo.svg")
