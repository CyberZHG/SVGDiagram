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
    node->setShape(SVGNode::NODE_SHAPE_DOUBLE_CIRCLE);
    node->setPrecomputedTextSize(10, 16);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: circle -->
<g class="node" id="circle">
  <title>circle</title>
  <circle cx="0" cy="0" r="17.69180601295413" fill="none" stroke="black"/>
  <circle cx="0" cy="0" r="21.69180601295413" fill="none" stroke="black"/>
  <rect x="-5" y="-8" width="10" height="16" fill="none" stroke="blue"/>
  <rect x="-13" y="-12" width="26" height="24" fill="none" stroke="red"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeDoubleCircle, OneCircleColor) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("circle");
    node->setShape(SVGNode::NODE_SHAPE_DOUBLE_CIRCLE);
    node->setPrecomputedTextSize(10, 16);
    node->setColor("red");
    node->setFillColor("white");
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: circle -->
<g class="node" id="circle">
  <title>circle</title>
  <circle cx="0" cy="0" r="17.69180601295413" fill="white" stroke="red"/>
  <circle cx="0" cy="0" r="21.69180601295413" fill="none" stroke="red"/>
  <rect x="-5" y="-8" width="10" height="16" fill="none" stroke="blue"/>
  <rect x="-13" y="-12" width="26" height="24" fill="none" stroke="red"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeDoubleCircle, TwoCirclesPenWidth) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0.0, 0.0);
    node1->setShape(SVGNode::NODE_SHAPE_DOUBLE_CIRCLE);
    node1->setPrecomputedTextSize(10, 16);
    node1->setPenWidth(2);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100.0, 0.0);
    node2->setShape(SVGNode::NODE_SHAPE_DOUBLE_CIRCLE);
    node2->setPrecomputedTextSize(10, 16);
    node2->setPenWidth(2);
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead();
    edge->setArrowTail();

    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <circle cx="0" cy="0" r="17.69180601295413" fill="none" stroke="black" stroke-width="2"/>
  <circle cx="0" cy="0" r="21.69180601295413" fill="none" stroke="black" stroke-width="2"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <circle cx="100" cy="0" r="17.69180601295413" fill="none" stroke="black" stroke-width="2"/>
  <circle cx="100" cy="0" r="21.69180601295413" fill="none" stroke="black" stroke-width="2"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="34.205350305841066" y1="0" x2="65.79464969415893" y2="4.18894727657622e-15" stroke="black"/>
  <polygon points="24.205350305841066,0 34.205350305841066,-3.4999999999999996 34.205350305841066,3.4999999999999996 24.205350305841066,0" fill="black" stroke="black"/>
  <polygon points="75.79464969415893,2.964300477428867e-15 65.79464969415893,3.500000000000005 65.79464969415893,-3.499999999999997 75.79464969415893,2.964300477428867e-15" fill="black" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}