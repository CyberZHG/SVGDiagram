#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestExample, Pentagram) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    diagram.defaultNodeAttributes().setShape(SVGNode::SHAPE_RECORD);
    diagram.defaultEdgeAttributes().setMargin(4.0);
    diagram.defaultEdgeAttributes().setArrowHead();

    const auto labels = vector{
        "{C1|Adamah's|Redemption}",
        "{C2|{Unground|Visions}}",
        "{C3|{Flame|Mirror's}|Revelation}",
        "{C4|Emanare's|Source}",
        "{C5|{Scouring|Flame's}|Sundering}",
        "{C6|Dual\\ Birth}",
    };
    const auto strokeColors = vector{"peru", "darkgoldenrod", "limegreen", "dodgerblue", "lightcoral"};
    const auto textColors = vector{"saddlebrown", "goldenrod", "olivedrab", "royalblue", "indianred"};
    const auto selfLoopDirs = vector{90, 0, -90, -90, 180};

    const auto& centralNode = diagram.addNode("node_c");
    centralNode->setCenter(0.0, 0.0);
    centralNode->setLabel(labels[5]);

    for (int i = 0; i < 5; ++i) {
        constexpr double RADIUS = 150.0;

        const auto& node = diagram.addNode(format("node_{}", i));
        const double nodeAngle = -numbers::pi / 2.3 + numbers::pi * 2 * i / 5.0;
        node->setCenter(RADIUS * cos(nodeAngle), RADIUS * sin(nodeAngle));
        node->setLabel(labels[i]);
        node->setColor(strokeColors[i]);
        node->setFontColor(textColors[i]);

        const auto from = "node_c";
        const auto to = format("node_{}", i);
        const auto& edge = diagram.addEdge(from, to);
        edge->setColor(strokeColors[i]);
        edge->setHeadLabel(format("C{}", i + 1));
        edge->setLabelDistance(2.0);
        edge->setFontColor(strokeColors[i]);

        const auto& loop = diagram.addSelfLoop(to, selfLoopDirs[i], 30.0, 20.0);
        loop->setColor(strokeColors[i]);
        loop->setFontColor(strokeColors[i]);
        loop->setArrowHead();
        loop->setLabel(format("C{}", i + 1));
    }

    diagram.render("example_pentagram.svg");
}