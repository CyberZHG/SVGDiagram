import math

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


def test_opacity():
    diagram = SVGDiagram()
    ids = ["A", "B", "C"]
    colors = ["#00FFFFCC", "#FF00FFCC", "#FFFF00CC"]
    for i, (node_id, color) in enumerate(zip(ids, colors)):
        node = diagram.add_node(node_id)
        angle = -math.pi / 2.0 + math.pi * 2 * i / 3.0
        node.set_center(50.0 * math.cos(angle), 50.0 * math.sin(angle))
        node.set_fixed_size(150, 150)
        node.set_color("none")
        node.set_fill_color(colors[i])
    svg = diagram.render()
    compare_svg("node_attr", "opacity", svg)


def test_gradient_color():
    diagram = SVGDiagram()
    node1 = diagram.add_node("A")
    node1.set_fill_color("gold:#FF0000EE")
    node1.set_label("A")
    node1.set_fixed_size(120, 80)
    node2 = diagram.add_node("B")
    node2.set_center(150, 0)
    node2.set_fill_color("gold:#FF0000EE")
    node2.set_label("B")
    node2.set_gradient_angle(45)
    node2.set_fixed_size(120, 80)
    node3 = diagram.add_node("C")
    node3.set_center(300, 0)
    node3.set_fill_color("white;1e-6:red:orange:yellow:green:blue:purple")
    node3.set_label("C")
    node3.set_gradient_angle(-90)
    node3.set_fixed_size(120, 80)
    svg = diagram.render()
    compare_svg("node_attr", "gradient_color", svg)


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


def test_font():
    diagram = SVGDiagram()
    for i in range(3):
        font_size = 14 + i
        node = diagram.add_node(f"node{i}")
        node.set_center(i * 150, 0)
        node.set_label(f"fontSize={font_size}")
        node.set_font_name("Consolas")
        node.set_font_size(font_size)
        node.set_font("Consolas,'Courier New',monospace", font_size)
    svg = diagram.render()
    compare_svg("node_attr", "font", svg)


def test_stroke_style():
    diagram = SVGDiagram()
    labels = ["solid", "dashed", "dotted"]
    for i, label in enumerate(labels):
        node = diagram.add_node(f"node{i}")
        node.set_center(i * 150, 0)
        node.set_label(label)
        if i == 1:
            node.append_style_dashed()
        elif i == 2:
            node.append_style_dotted()
    svg = diagram.render()
    compare_svg("node_attr", "stroke_style", svg)
