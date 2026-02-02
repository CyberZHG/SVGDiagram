#include <numbers>

#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodeRect, RectConnections) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    const auto& central = diagram.addNode("c");
    central->setCenter(0.0, 0.0);
    central->setShape(SVGNode::SHAPE_RECT);
    central->setLabel("Central");
    constexpr double start = numbers::pi / 19.0;
    for (int i = 0; i < 17; ++i) {
        const auto nodeName = format("n_{}", i);
        const auto& node = diagram.addNode(nodeName);
        constexpr double shift = 2.0 * numbers::pi / 17.0;
        const double angle = start + i * shift;
        node->setCenter(120.0 * cos(angle), 120.0 * sin(angle));
        node->setShape(SVGNode::SHAPE_RECT);
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
        edge->setLabel(format("{}", i));
    }
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRect, RectConnectionOnCorner) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setShape(SVGNode::SHAPE_RECT);
    node1->setFixedSize(20, 20);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(30, 30);
    node2->setShape(SVGNode::SHAPE_RECT);
    node2->setFixedSize(20, 20);
    const auto edge = diagram.addEdge("A", "B");

    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

#ifndef SVG_DIAGRAM_ENABLE_PANGO_CAIRO

TEST(TestSVGNodeRect, TextSingeLineAlignLeft) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECT);
    node->setLabel("foo\\l");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRect, TextSingeLineAlignRight) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECT);
    node->setLabel("foo\\r");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRect, TextAlignLeft) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECT);
    node->setLabel(R"(foo\lfoobar\lbar\l)");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRect, TextAlignRight) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECT);
    node->setLabel(R"(foo\rfoobar\rbar\r)");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRect, TextAlignMix) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECT);
    node->setLabel("foo\\lfoobar\nbar\\r");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRect, Peripheries) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setShape(SVGNode::SHAPE_RECT);
    node1->setLabel("P=1");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100, 0);
    node2->setShape(SVGNode::SHAPE_RECT);
    node2->setLabel("P=2");
    node2->setPeripheries(2);
    const auto node3 = diagram.addNode("C");
    node3->setCenter(200, 0);
    node3->setShape(SVGNode::SHAPE_RECT);
    node3->setLabel("P=3");
    node3->setPeripheries(3);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRect, PeripheriesConnection) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setShape(SVGNode::SHAPE_RECT);
    node1->setLabel("A");
    node1->setPeripheries(2);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100, 0);
    node2->setShape(SVGNode::SHAPE_RECT);
    node2->setLabel("B");
    node2->setPeripheries(2);
    diagram.addEdge("A", "B");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

#endif
