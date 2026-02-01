#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGEdgeArrowEmpty, TwoRectsEmptyArrow) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setShape(SVGNode::SHAPE_RECT);
    node1->setFixedSize(10, 10);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(50, 100);
    node2->setShape(SVGNode::SHAPE_RECT);
    node2->setFixedSize(10, 10);
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeArrowEmpty, TwoRectsEmptyArrowPenWidth) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setShape(SVGNode::SHAPE_RECT);
    node1->setFixedSize(10, 10);
    node1->setPenWidth(2.0);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(50, 100);
    node2->setShape(SVGNode::SHAPE_RECT);
    node2->setFixedSize(10, 10);
    node2->setPenWidth(2.0);
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    edge->setPenWidth(2.0);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}