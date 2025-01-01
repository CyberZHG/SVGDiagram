#include <numbers>

#include "svg_diagram.h"
#include "../test_utils.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodeRect, RectConnections) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    const auto& central = diagram.addNode("c");
    central->setCenter(0.0, 0.0);
    central->setShape(SVGNode::NODE_SHAPE_RECT);
    central->setLabel("Central");
    constexpr double start = numbers::pi / 19.0;
    for (int i = 0; i < 17; ++i) {
        const auto nodeName = format("n_{}", i);
        const auto& node = diagram.addNode(nodeName);
        constexpr double shift = 2.0 * numbers::pi / 17.0;
        const double angle = start + i * shift;
        node->setCenter(120.0 * cos(angle), 120.0 * sin(angle));
        node->setShape(SVGNode::NODE_SHAPE_RECT);
        node->setLabel(format("{}", i));
        if (i % 2 == 0) {
            const auto& edge = diagram.addEdge("c", nodeName);
            edge->setArrowHead();
            edge->addConnectionPoint(60.0 * cos(angle), 60.0 * sin(angle));
            edge->addConnectionPoint(80.0 * cos(angle + shift / 3.0), 80.0 * sin(angle + shift / 3.0));
        } else {
            const auto& edge = diagram.addEdge(nodeName, "c");
            edge->setArrowHead();
            edge->addConnectionPoint(80.0 * cos(angle - shift / 3.0), 80.0 * sin(angle - shift / 3.0));
            edge->addConnectionPoint(60.0 * cos(angle), 60.0 * sin(angle));
        }
        diagram.addEdge(nodeName, format("n_{}", (i + 1) % 17));
        const auto& edge = diagram.addEdge(nodeName, format("n_{}", (i + 2) % 17));
        edge->addConnectionPoint(200.0 * cos(angle + shift / 2), 200.0 * sin(angle + shift / 2));
        edge->setArrowHead();
    }
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}