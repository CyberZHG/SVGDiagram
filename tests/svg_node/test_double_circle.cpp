#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodeDoubleCircle, OneCircle) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("circle");
    node->setShape(SVGNode::SHAPE_DOUBLE_CIRCLE);
    node->setPrecomputedTextSize(10, 16);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeDoubleCircle, OneCircleColor) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("circle");
    node->setShape(SVGNode::SHAPE_DOUBLE_CIRCLE);
    node->setPrecomputedTextSize(10, 16);
    node->setColor("red");
    node->setFillColor("white");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeDoubleCircle, TwoCirclesPenWidth) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0.0, 0.0);
    node1->setShape(SVGNode::SHAPE_DOUBLE_CIRCLE);
    node1->setPrecomputedTextSize(10, 16);
    node1->setPenWidth(2);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100.0, 0.0);
    node2->setShape(SVGNode::SHAPE_DOUBLE_CIRCLE);
    node2->setPrecomputedTextSize(10, 16);
    node2->setPenWidth(2);
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead();
    edge->setArrowTail();

    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeDoubleCircle, Dashed) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("circle");
    node->setShape(SVGNode::SHAPE_DOUBLE_CIRCLE);
    node->appendStyleDashed();
    node->setPrecomputedTextSize(10, 16);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeDoubleCircle, Dotted) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("circle");
    node->setShape(SVGNode::SHAPE_DOUBLE_CIRCLE);
    node->appendStyleDotted();
    node->setPrecomputedTextSize(10, 16);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
