#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <format>
#include <vector>
#include <gtest/gtest.h>
using namespace svg_diagram;

static const auto OUTPUT_DIR = std::string("../docs/source/_static/node_attr/");

TEST(TestDocsNodeAttributes, Label) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("foobar");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("Pybind11\nEmscripten");
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("星分翼轸\n地接衡庐");
    diagram.render(OUTPUT_DIR + "label.svg");
}

TEST(TestDocsNodeAttributes, LabelDebug) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("foobar");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("Pybind11\nEmscripten");
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("星分翼轸\n地接衡庐");
    diagram.render(OUTPUT_DIR + "label_debug.svg");
}

TEST(TestDocsNodeAttributes, LabelAlign) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("align\\lleft\\lfoobar\\l");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("align\\rright\\rfoobar\\r");
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("align\\lmixed\\rfoobar");
    diagram.render(OUTPUT_DIR + "label_align.svg");
}

TEST(TestDocsNodeAttributes, Shape) {
    SVGDiagram diagram;
    const auto shapes = std::vector{
        SVGNode::SHAPE_ELLIPSE,
        SVGNode::SHAPE_DOUBLE_ELLIPSE,
        SVGNode::SHAPE_NONE,
        SVGNode::SHAPE_CIRCLE,
        SVGNode::SHAPE_DOUBLE_CIRCLE,
        SVGNode::SHAPE_RECT,
        SVGNode::SHAPE_POLYGON,
        SVGNode::SHAPE_TRIANGLE,
        SVGNode::SHAPE_PENTAGON,
        SVGNode::SHAPE_HEXAGON,
        SVGNode::SHAPE_SEPTAGON,
        SVGNode::SHAPE_OCTAGON,
        SVGNode::SHAPE_TRAPEZIUM,
        SVGNode::SHAPE_PARALLELOGRAM,
        SVGNode::SHAPE_HOUSE,
        SVGNode::SHAPE_DIAMOND,
        SVGNode::SHAPE_INV_TRIANGLE,
        SVGNode::SHAPE_INV_TRAPEZIUM,
        SVGNode::SHAPE_INV_HOUSE,
    };
    for (int i = 0; i < static_cast<int>(shapes.size()); ++i) {
        const auto shape = std::string(shapes[i]);
        const auto node = diagram.addNode(std::string(shapes[i]));
        node->setShape(shapes[i]);
        node->setCenter((i % 4) * 160.0, (i / 4) * 100.0);
        node->setLabel(shape);
        if (shapes[i] == SVGNode::SHAPE_POLYGON) {
            node->setSides(7);
        }
    }
    diagram.render(OUTPUT_DIR + "shape.svg");
}

TEST(TestDocsNodeAttributes, ShapeRecord) {
    SVGDiagram diagram;
    diagram.defaultNodeAttributes().setShape(SVGNode::SHAPE_RECORD);
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("horizontal|split|record");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("{vertical|split|record}");
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("foo|{foobar|{nested||record}|barfoo}|bar");
    diagram.render(OUTPUT_DIR + "shape_record.svg");
}

TEST(TestDocsNodeAttributes, ShapeDebug) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto shapes = std::vector{
        SVGNode::SHAPE_ELLIPSE,
        SVGNode::SHAPE_DOUBLE_ELLIPSE,
        SVGNode::SHAPE_NONE,
        SVGNode::SHAPE_CIRCLE,
        SVGNode::SHAPE_DOUBLE_CIRCLE,
        SVGNode::SHAPE_RECT,
        SVGNode::SHAPE_POLYGON,
        SVGNode::SHAPE_TRIANGLE,
        SVGNode::SHAPE_PENTAGON,
        SVGNode::SHAPE_HEXAGON,
        SVGNode::SHAPE_SEPTAGON,
        SVGNode::SHAPE_OCTAGON,
        SVGNode::SHAPE_TRAPEZIUM,
        SVGNode::SHAPE_PARALLELOGRAM,
        SVGNode::SHAPE_HOUSE,
        SVGNode::SHAPE_DIAMOND,
        SVGNode::SHAPE_INV_TRIANGLE,
        SVGNode::SHAPE_INV_TRAPEZIUM,
        SVGNode::SHAPE_INV_HOUSE,
    };
    for (int i = 0; i < static_cast<int>(shapes.size()); ++i) {
        const auto shape = std::string(shapes[i]);
        const auto node = diagram.addNode(std::string(shapes[i]));
        node->setShape(shapes[i]);
        node->setCenter((i % 4) * 160.0, (i / 4) * 90.0);
        node->setLabel(shape);
        if (shapes[i] == SVGNode::SHAPE_POLYGON) {
            node->setSides(7);
        }
    }
    diagram.render(OUTPUT_DIR + "shape_debug.svg");
}

TEST(TestDocsNodeAttributes, Margin) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("Larger\nMargin");
    node1->setMargin(32, 8);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("No\nMargin");
    node2->setMargin(0);
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("Negative\nMargin");
    node3->setMargin(-10);
    diagram.render(OUTPUT_DIR + "margin.svg");
}

TEST(TestDocsNodeAttributes, MarginDebug) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("Larger\nMargin");
    node1->setMargin(32, 8);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("No\nMargin");
    node2->setMargin(0);
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("Negative\nMargin");
    node3->setMargin(-10);
    diagram.render(OUTPUT_DIR + "margin_debug.svg");
}

TEST(TestDocsNodeAttributes, TextSize) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setLabel("🐱🐶🙈🙉🙊");
    const auto node2 = diagram.addNode("B");
    node2->setLabel("🐱🐶🙈🙉🙊");
    node2->setCenter(0, 50);
    node2->setPrecomputedTextSize(80, 16);
    diagram.render(OUTPUT_DIR + "text_size.svg");
}

TEST(TestDocsNodeAttributes, TextSizeDebug) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node1 = diagram.addNode("A");
    node1->setLabel("🐱🐶🙈🙉🙊");
    const auto node2 = diagram.addNode("B");
    node2->setLabel("🐱🐶🙈🙉🙊");
    node2->setCenter(0, 50);
    node2->setPrecomputedTextSize(80, 16);
    diagram.render(OUTPUT_DIR + "text_size_debug.svg");
}

TEST(TestDocsNodeAttributes, NodeSize) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setLabel("B");
    node2->setCenter(150, 0);
    node2->setFixedSize(80, 30);
    diagram.render(OUTPUT_DIR + "node_size.svg");
}

TEST(TestDocsNodeAttributes, NodeSizeDebug) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node1 = diagram.addNode("A");
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setLabel("B");
    node2->setCenter(150, 0);
    node2->setFixedSize(80, 30);
    diagram.render(OUTPUT_DIR + "node_size_debug.svg");
}

TEST(TestDocsNodeAttributes, Color) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setLabel("color");
    node->setColor("limegreen");
    node->setFillColor("#EEEEEE");
    node->setFontColor("rgb(66,92,214)");
    diagram.render(OUTPUT_DIR + "color.svg");
}

TEST(TestDocsNodeAttributes, Opacity) {
    SVGDiagram diagram;
    const std::vector<std::string> ids = {"A", "B", "C"};
    const std::vector<std::string> colors = {"#00FFFFCC", "#FF00FFCC", "#FFFF00CC"};
    for (int i = 0; i < static_cast<int>(ids.size()); ++i) {
        const auto node = diagram.addNode(ids[i]);
        const double angle = -std::numbers::pi / 2.0 + std::numbers::pi * 2 * i / 3.0;
        node->setCenter(50.0 * cos(angle), 50.0 * sin(angle));
        node->setFixedSize(150, 150);
        node->setColor("none");
        node->setFillColor(colors[i]);
    }
    diagram.render(OUTPUT_DIR + "opacity.svg");
}

TEST(TestDocsNodeAttributes, GradientColor) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setFillColor("gold:#FF0000EE");
    node1->setLabel("A");
    node1->setFixedSize(120, 80);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setFillColor("gold:#FF0000EE");
    node2->setLabel("B");
    node2->setGradientAngle(45);
    node2->setFixedSize(120, 80);
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setFillColor("white;1e-6:red:orange:yellow:green:blue:purple");
    node3->setLabel("C");
    node3->setGradientAngle(-90);
    node3->setFixedSize(120, 80);
    diagram.render(OUTPUT_DIR + "gradient_color.svg");
}

TEST(TestDocsNodeAttributes, PenWidth) {
    SVGDiagram diagram;
    for (int i = 0; i < 3; ++i) {
        const auto penWidth = 1 + i * 2;
        const auto node = diagram.addNode(std::format("node{}", i));
        node->setCenter(i * 150, 0);
        node->setLabel(std::format("penWidth={}", penWidth));
        node->setPenWidth(penWidth);
    }
    diagram.render(OUTPUT_DIR + "pen_width.svg");
}

TEST(TestDocsNodeAttributes, Font) {
    SVGDiagram diagram;
    for (int i = 0; i < 3; ++i) {
        const auto fontSize = 14 + i;
        const auto node = diagram.addNode(std::format("node{}", i));
        node->setCenter(i * 150, 0);
        node->setLabel(std::format("fontSize={}", fontSize));
        node->setFontName("Consolas");
        node->setFontSize(fontSize);
        node->setFont("Consolas,'Courier New',monospace", fontSize);
    }
    diagram.render(OUTPUT_DIR + "font.svg");
}

TEST(TestDocsNodeAttributes, StrokeStyle) {
    SVGDiagram diagram;
    const auto labels = std::vector<std::string>({"solid", "dashed", "dotted"});
    for (int i = 0; i < static_cast<int>(labels.size()); ++i) {
        const auto node = diagram.addNode(std::format("node{}", i));
        node->setCenter(i * 150, 0);
        node->setLabel(labels[i]);
        if (i == 0) {
            node->appendStyleSolid();
        } else if (i == 1) {
            node->appendStyleDashed();
        } else if (i == 2) {
            node->appendStyleDotted();
        }
    }
    diagram.render(OUTPUT_DIR + "stroke_style.svg");
}
