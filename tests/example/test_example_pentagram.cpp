#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestExample, Pentagram) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");

    const auto labels = vector{
        "Adamah's\nRedemption",
        "Unground Visions",
        "Flame Mirror's\nRevelation",
        "Emanare's\nSource",
        "Scouring Flame's\nSundering",
        "Dual Birth",
    };
    const auto strokeColors = vector{"peru", "darkgoldenrod", "limegreen", "dodgerblue", "lightcoral"};
    const auto textColors = vector{"saddlebrown", "goldenrod", "olivedrab", "royalblue", "indianred"};

    const auto& centralNode = diagram.addNode("node_c");
    centralNode->setCenter(0.0, 0.0);
    centralNode->setLabel(labels[5]);
    centralNode->setShape(SVGNode::NODE_SHAPE_RECT);

    for (int i = 0; i < 5; ++i) {
        constexpr double RADIUS = 150.0;

        const auto& node = diagram.addNode(format("node_{}", i));
        const double nodeAngle = -numbers::pi / 2.3 + numbers::pi * 2 * i / 5.0;
        node->setCenter(RADIUS * cos(nodeAngle), RADIUS * sin(nodeAngle));
        node->setLabel(labels[i]);
        node->setShape(SVGNode::NODE_SHAPE_RECT);
        node->setColor(strokeColors[i]);
        node->setFontColor(textColors[i]);

        const auto from = "node_c";
        const auto to = format("node_{}", i);
        const auto& edge = diagram.addEdge(from, to);
        edge->setArrowHead();
        edge->setColor(strokeColors[i]);
    }

    diagram.render("example_pentagram.svg");
}