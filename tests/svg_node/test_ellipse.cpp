#include <numbers>

#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodeEllipse, EllipseConnections) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    const auto& central = diagram.addNode("c");
    central->setCenter(0.0, 0.0);
    central->setShape(SVGNode::SHAPE_ELLIPSE);
    central->setLabel("Central");
    constexpr double start = numbers::pi / 19.0;
    for (int i = 0; i < 17; ++i) {
        const auto nodeName = format("n_{}", i);
        const auto& node = diagram.addNode(nodeName);
        constexpr double shift = 2.0 * numbers::pi / 17.0;
        const double angle = start + i * shift;
        node->setCenter(120.0 * cos(angle), 120.0 * sin(angle));
        node->setShape(SVGNode::SHAPE_ELLIPSE);
        node->setLabel(format("{}", i));
        if (i % 2 == 0) {
            const auto& edge = diagram.addEdge("c", nodeName);
            edge->setArrowHead();
            edge->addConnectionPoint(60.0 * cos(angle), 60.0 * sin(angle));
            edge->addConnectionPoint(80.0 * cos(angle + shift / 3.0), 80.0 * sin(angle + shift / 3.0));
            edge->setLabel(format("{}", i));
        } else {
            const auto& edge = diagram.addEdge(nodeName, "c");
            edge->setArrowHead();
            edge->addConnectionPoint(80.0 * cos(angle - shift / 3.0), 80.0 * sin(angle - shift / 3.0));
            edge->addConnectionPoint(60.0 * cos(angle), 60.0 * sin(angle));
            edge->setLabel(format("{}", i));
        }
        diagram.addEdge(nodeName, format("n_{}", (i + 1) % 17));
        const auto& edge = diagram.addEdge(nodeName, format("n_{}", (i + 2) % 17));
        edge->addConnectionPoint(200.0 * cos(angle + shift / 2), 200.0 * sin(angle + shift / 2));
        edge->setArrowHead();
        edge->setArrowTail();
        edge->setLabel(format("{}", i));
    }
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeEllipse, StrokeOpacity) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_ELLIPSE);
    node->setMargin(8, 4);
    node->setColor("#FF000011");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeEllipse, FillOpacity) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_ELLIPSE);
    node->setMargin(8, 4);
    node->setColor("none");
    node->setFillColor("#FF000011");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeEllipse, FillGradientColor2) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_ELLIPSE);
    node->setMargin(8, 4);
    node->setColor("none");
    node->setFillColor("red:gold");
    node->setGradientAngle(-45);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeEllipse, FillGradientColor3) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_ELLIPSE);
    node->setMargin(8, 4);
    node->setColor("none");
    node->setFillColor("red:gold:#FF00FF88");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeEllipse, FillColorSegment2) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_ELLIPSE);
    node->setMargin(8, 4);
    node->setColor("none");
    node->setFillColor("red;0.4:gold");
    node->setGradientAngle(45);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeEllipse, FillColorSegment3) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_ELLIPSE);
    node->setMargin(8, 4);
    node->setColor("none");
    node->setFillColor("red:gold;.2:#FF00FF88");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
