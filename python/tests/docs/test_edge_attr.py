from sp_svg_diagram import SVGDiagram, SVGEdge, SVGNode

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


def test_label():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_center(0, 0)
    node1.set_label("A")
    node2 = diagram.add_node("B")
    node2.set_center(150, 0)
    node2.set_label("B")
    edge1 = diagram.add_edge("A", "B")
    edge1.set_arrow_head()
    edge1.set_label("A → B")
    edge1.add_connection_point(76, 20)
    edge2 = diagram.add_edge("B", "A")
    edge2.set_arrow_head()
    edge2.set_label("A ← B")
    edge2.add_connection_point(76, -20)
    svg = diagram.render()
    compare_svg("edge_attr", "label", svg)


def test_label_tail_head():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_center(0, 0)
    node1.set_label("A")
    node2 = diagram.add_node("B")
    node2.set_center(150, 0)
    node2.set_label("B")
    edge1 = diagram.add_edge("A", "B")
    edge1.set_arrow_head()
    edge1.set_tail_label("tail")
    edge1.set_head_label("head")
    edge1.set_label_distance(1.5)
    edge1.set_margin(2.0)
    svg = diagram.render()
    compare_svg("edge_attr", "label_tail_head", svg)


def test_self_loop():
    diagram = SVGDiagram()
    loop_height, loop_angle = 30.0, 30.0
    node = diagram.add_node("A")
    node.set_label("Self Loops")
    edge1 = diagram.add_self_loop_to_left("A", loop_height, loop_angle)
    edge1.set_label("Left")
    edge1.set_arrow_head()
    edge2 = diagram.add_self_loop_to_right("A", loop_height, loop_angle)
    edge2.set_label("Right")
    edge2.set_arrow_head()
    edge3 = diagram.add_self_loop_to_top("A", loop_height, loop_angle)
    edge3.set_label("Top")
    edge3.set_arrow_head()
    edge4 = diagram.add_self_loop_to_bottom("A", loop_height, loop_angle)
    edge4.set_label("Bottom")
    edge4.set_arrow_head()
    svg = diagram.render()
    compare_svg("edge_attr", "self_loop", svg)


def test_color():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_center(0, 0)
    node1.set_label("A")
    node2 = diagram.add_node("B")
    node2.set_center(150, 0)
    node2.set_label("B")
    edge = diagram.add_edge("A", "B")
    edge.set_arrow_head(SVGEdge.ARROW_NORMAL)
    edge.set_arrow_tail(SVGEdge.ARROW_EMPTY)
    edge.set_label("color")
    edge.set_color("red")
    edge.set_font_color("blue")
    svg = diagram.render()
    compare_svg("edge_attr", "color", svg)


def test_pen_width():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_center(0, 0)
    node1.set_label("A")
    node2 = diagram.add_node("B")
    node2.set_center(150, 0)
    node2.set_label("B")
    edge = diagram.add_edge("A", "B")
    edge.set_arrow_head(SVGEdge.ARROW_NORMAL)
    edge.set_arrow_tail(SVGEdge.ARROW_EMPTY)
    edge.set_label("penWidth=3")
    edge.set_pen_width(3)
    edge.set_margin(4, 4)
    svg = diagram.render()
    compare_svg("edge_attr", "pen_width", svg)


def test_font():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_center(0, 0)
    node1.set_label("A")
    node2 = diagram.add_node("B")
    node2.set_center(150, 0)
    node2.set_label("B")
    edge = diagram.add_edge("A", "B")
    edge.set_label("font")
    edge.set_margin(4, 4)
    edge.set_font_name("Consolas")
    edge.set_font_size(16)
    edge.set_font("Consolas,'Courier New',monospace", 16)
    svg = diagram.render()
    compare_svg("edge_attr", "font", svg)


def test_stroke_style():
    diagram = SVGDiagram()
    labels = ["solid", "dashed", "dotted"]
    for i, label in enumerate(labels):
        y = i * 60.0
        tail_id, head_id = f"A{i}", f"B{i}"
        node1 = diagram.add_node(tail_id)
        node1.set_center(0, y)
        node1.set_label("A")
        node2 = diagram.add_node(head_id)
        node2.set_center(150, y)
        node2.set_label("B")
        edge = diagram.add_edge(tail_id, head_id)
        edge.set_arrow_head()
        edge.set_label(label)
        if i == 1:
            edge.append_style_dashed()
        elif i == 2:
            edge.append_style_dotted()
    svg = diagram.render()
    compare_svg("edge_attr", "stroke_style", svg)


def test_field():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_center(0, 0)
    node1.set_shape(SVGNode.SHAPE_RECORD)
    node1.set_label("|{|<foo> A|}|")
    node2 = diagram.add_node("B")
    node2.set_center(150, 0)
    node2.set_shape(SVGNode.SHAPE_RECORD)
    node2.set_label("{|{|<bar> B|}|}")
    edge = diagram.add_edge("A", "B")
    edge.set_field_from("foo")
    edge.set_field_to("bar")
    edge.add_connection_point(50, -20)
    edge.add_connection_point(100, 20)
    edge.set_arrow_head()
    svg = diagram.render()
    compare_svg("edge_attr", "field", svg)
