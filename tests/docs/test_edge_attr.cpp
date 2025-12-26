#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <format>
#include <vector>
#include <gtest/gtest.h>
using namespace svg_diagram;

static const auto OUTPUT_DIR = std::string("../docs/source/_static/edge_attr/");

TEST(TestDocsEdgeAttributes, Splines) {
    SVGDiagram diagram;
    const auto splinesTypes = std::vector{
        SVGEdge::SPLINES_SPLINE,
        SVGEdge::SPLINES_LINE,
    };
    for (int i = 0; i < static_cast<int>(splinesTypes.size()); i++) {
        const double y = i * 80.0;
        const auto tailNodeID = std::format("A{}", i);
        const auto headNodeID = std::format("B{}", i);
        const auto node1 = diagram.addNode(tailNodeID);
        node1->setCenter(0, y);
        node1->setLabel("A");
        const auto node2 = diagram.addNode(headNodeID);
        node2->setCenter(150, y);
        node2->setLabel("B");
        const auto edge = diagram.addEdge(tailNodeID, headNodeID);
        edge->setSplines(splinesTypes[i]);
        edge->addConnectionPoint(50, y - 20);
        edge->addConnectionPoint(100, y + 20);
        edge->setLabel(std::string(splinesTypes[i]));
    }
    diagram.render(OUTPUT_DIR + "splines.svg");
}

TEST(TestDocsEdgeAttributes, SplinesDebug) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto splinesTypes = std::vector{
        SVGEdge::SPLINES_SPLINE,
        SVGEdge::SPLINES_LINE,
    };
    for (int i = 0; i < static_cast<int>(splinesTypes.size()); i++) {
        const double y = i * 80.0;
        const auto tailNodeID = std::format("A{}", i);
        const auto headNodeID = std::format("B{}", i);
        const auto node1 = diagram.addNode(tailNodeID);
        node1->setCenter(0, y);
        node1->setLabel("A");
        const auto node2 = diagram.addNode(headNodeID);
        node2->setCenter(150, y);
        node2->setLabel("B");
        const auto edge = diagram.addEdge(tailNodeID, headNodeID);
        edge->setSplines(splinesTypes[i]);
        edge->addConnectionPoint(50, y - 20);
        edge->addConnectionPoint(100, y + 20);
        edge->setLabel(std::string(splinesTypes[i]));
    }
    diagram.render(OUTPUT_DIR + "splines_debug.svg");
}

TEST(TestDocsEdgeAttributes, Arrow) {
    SVGDiagram diagram;
    const auto arrowTypes = std::vector{
        SVGEdge::ARROW_NONE,
        SVGEdge::ARROW_NORMAL,
        SVGEdge::ARROW_EMPTY,
    };
    for (int i = 0; i < static_cast<int>(arrowTypes.size()); i++) {
        const double y = i * 60.0;
        const auto tailNodeID = std::format("A{}", i);
        const auto headNodeID = std::format("B{}", i);
        const auto node1 = diagram.addNode(tailNodeID);
        node1->setCenter(0, y);
        node1->setLabel("A");
        const auto node2 = diagram.addNode(headNodeID);
        node2->setCenter(150, y);
        node2->setLabel("B");
        const auto edge = diagram.addEdge(tailNodeID, headNodeID);
        edge->setArrowTail(SVGEdge::ARROW_NONE);
        edge->setArrowHead(std::string(arrowTypes[i]));
        edge->setLabel(std::string(arrowTypes[i]));
    }
    diagram.render(OUTPUT_DIR + "arrow.svg");
}

TEST(TestDocsEdgeAttributes, Label) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("B");
    const auto edge1 = diagram.addEdge("A", "B");
    edge1->setArrowHead();
    edge1->setLabel("A → B");
    edge1->addConnectionPoint(76, 20);
    const auto edge2 = diagram.addEdge("B", "A");
    edge2->setArrowHead();
    edge2->setLabel("A ← B");
    edge2->addConnectionPoint(76, -20);
    diagram.render(OUTPUT_DIR + "label.svg");
}

TEST(TestDocsEdgeAttributes, LabelDebug) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("B");
    const auto edge1 = diagram.addEdge("A", "B");
    edge1->setArrowHead();
    edge1->setLabel("A → B");
    edge1->addConnectionPoint(75, 20);
    const auto edge2 = diagram.addEdge("B", "A");
    edge2->setArrowHead();
    edge2->setLabel("A ← B");
    edge2->addConnectionPoint(75, -20);
    diagram.render(OUTPUT_DIR + "label_debug.svg");
}

TEST(TestDocsEdgeAttributes, SelfLoop) {
    SVGDiagram diagram;
    constexpr double loopHeight = 30.0, loopAngle = 30.0;
    const auto node = diagram.addNode("A");
    node->setLabel("Self Loops");
    const auto edge1 = diagram.addSelfLoopToLeft("A", loopHeight, loopAngle);
    edge1->setLabel("Left");
    edge1->setArrowHead();
    const auto edge2 = diagram.addSelfLoopToRight("A", loopHeight, loopAngle);
    edge2->setLabel("Right");
    edge2->setArrowHead();
    const auto edge3 = diagram.addSelfLoopToTop("A", loopHeight, loopAngle);
    edge3->setLabel("Top");
    edge3->setArrowHead();
    const auto edge4 = diagram.addSelfLoopToBottom("A", loopHeight, loopAngle);
    edge4->setLabel("Bottom");
    edge4->setArrowHead();
    diagram.render(OUTPUT_DIR + "self_loop.svg");
}

TEST(TestDocsEdgeAttributes, Color) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("B");
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    edge->setLabel("color");
    edge->setColor("red");
    edge->setFontColor("blue");
    diagram.render(OUTPUT_DIR + "color.svg");
}

TEST(TestDocsEdgeAttributes, PenWidth) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("B");
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    edge->setLabel("penWidth=3");
    edge->setPenWidth(3);
    edge->setMargin(4);
    diagram.render(OUTPUT_DIR + "pen_width.svg");
}

TEST(TestDocsEdgeAttributes, Font) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("B");
    const auto edge = diagram.addEdge("A", "B");
    edge->setLabel("font");
    edge->setMargin(4);
    edge->setFontName("Consolas");
    edge->setFontSize(16);
    edge->setFont("Consolas,'Courier New',monospace", 16);
    diagram.render(OUTPUT_DIR + "font.svg");
}

TEST(TestDocsEdgeAttributes, StrokeStyle) {
    SVGDiagram diagram;
    const auto labels = std::vector<std::string>({"solid", "dashed", "dotted"});
    for (int i = 0; i < static_cast<int>(labels.size()); i++) {
        const double y = i * 60.0;
        const auto tailNodeID = std::format("A{}", i);
        const auto headNodeID = std::format("B{}", i);
        const auto node1 = diagram.addNode(tailNodeID);
        node1->setCenter(0, y);
        node1->setLabel("A");
        const auto node2 = diagram.addNode(headNodeID);
        node2->setCenter(150, y);
        node2->setLabel("B");
        const auto edge = diagram.addEdge(tailNodeID, headNodeID);
        edge->setArrowHead();
        edge->setLabel(labels[i]);
        if (i == 1) {
            edge->appendStyleDashed();
        } else if (i == 2) {
            edge->appendStyleDotted();
        }
    }
    diagram.render(OUTPUT_DIR + "stroke_style.svg");
}