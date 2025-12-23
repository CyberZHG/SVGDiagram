#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestExample, Pentagon) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    diagram.defaultNodeAttributes().setShape(SVGNode::SHAPE_CIRCLE);
    diagram.defaultEdgeAttributes().setMargin(4.0);
    diagram.defaultEdgeAttributes().setArrowHead();

    const auto labels = vector{
        "Planning\nBreeds\nSuccess",
        "Observation\nFeeds\nStrategy",
        "Deceit\nCloaks\nthe Truth",
        "Delusion\nEnsnares\nReason",
        "Opportunity\nHides in\nthe Margins",
        "Victory\nFlows from\nthe Turning of Tides",
    };
    const auto strokeColors = vector{"peru", "darkgoldenrod", "limegreen", "dodgerblue", "lightcoral"};
    const auto fillColors = vector{"lightsalmon", "papayawhip", "lightgreen", "deepskyblue", "lightpink"};
    const auto textColors = vector{"saddlebrown", "goldenrod", "olivedrab", "royalblue", "indianred", "indigo"};

    for (int i = 0; i < 5; ++i) {
        constexpr double RADIUS = 150.0;

        const auto& node = diagram.addNode(format("node_{}", i));
        const double nodeAngle = -numbers::pi / 2.0 + numbers::pi * 2 * i / 5.0;
        node->setCenter(RADIUS * cos(nodeAngle), RADIUS * sin(nodeAngle));
        node->setLabel(labels[i]);
        node->setColor(strokeColors[i]);
        node->setFillColor(fillColors[i]);
        node->setFontColor(textColors[i]);
        if (i == 1) {
            node->appendStyleDashed();
        } else if (i == 3) {
            node->setShape(SVGNode::SHAPE_DOUBLE_CIRCLE);
        }

        const auto from = format("node_{}", i);
        const auto to = format("node_{}", (i + 1) % 5);
        const auto& edge = diagram.addEdge(from, to);
        edge->setColor(strokeColors[i]);
        edge->setLabel(format("C{}", i + 1));
        edge->setFontColor(strokeColors[i]);
        if (i == 1) {
            edge->appendStyleDashed();
        }
    }

    const auto& node = diagram.addNode("node_c");
    node->setCenter(0.0, 0.0);
    node->setLabel(labels[5]);
    node->setShape(SVGNode::SHAPE_NONE);
    node->setFontColor(textColors[5]);
    node->setFont("Times,serif", 16);

    diagram.render("example_pentagon.svg");
}