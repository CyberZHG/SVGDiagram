#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodeDoubleEllipse, OneEllipse) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("ellipse");
    node->setShape(SVGNode::SHAPE_DOUBLE_ELLIPSE);
    node->setPrecomputedTextSize(10, 16);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: ellipse -->
<g class="node" id="ellipse">
  <title>ellipse</title>
  <ellipse cx="0" cy="0" rx="18.38477631085024" ry="16.970562748477143" fill="none" stroke="black"/>
  <ellipse cx="0" cy="0" rx="22.38477631085024" ry="20.970562748477143" fill="none" stroke="black"/>
  <rect x="-5" y="-8" width="10" height="16" fill="none" stroke="blue"/>
  <rect x="-13" y="-12" width="26" height="24" fill="none" stroke="red"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeDoubleEllipse, OneEllipseColor) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("ellipse");
    node->setShape(SVGNode::SHAPE_DOUBLE_ELLIPSE);
    node->setPrecomputedTextSize(10, 16);
    node->setColor("red");
    node->setFillColor("white");
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: ellipse -->
<g class="node" id="ellipse">
  <title>ellipse</title>
  <ellipse cx="0" cy="0" rx="18.38477631085024" ry="16.970562748477143" fill="white" stroke="red"/>
  <ellipse cx="0" cy="0" rx="22.38477631085024" ry="20.970562748477143" fill="none" stroke="red"/>
  <rect x="-5" y="-8" width="10" height="16" fill="none" stroke="blue"/>
  <rect x="-13" y="-12" width="26" height="24" fill="none" stroke="red"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeDoubleEllipse, TwoEllipsesPenWidth) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0.0, 0.0);
    node1->setShape(SVGNode::SHAPE_DOUBLE_ELLIPSE);
    node1->setPrecomputedTextSize(10, 16);
    node1->setPenWidth(2);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100.0, 0.0);
    node2->setShape(SVGNode::SHAPE_DOUBLE_ELLIPSE);
    node2->setPrecomputedTextSize(10, 16);
    node2->setPenWidth(2);
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead();
    edge->setArrowTail();
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="18.38477631085024" ry="16.970562748477143" fill="none" stroke="black" stroke-width="2"/>
  <ellipse cx="0" cy="0" rx="22.38477631085024" ry="20.970562748477143" fill="none" stroke="black" stroke-width="2"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <ellipse cx="100" cy="0" rx="18.38477631085024" ry="16.970562748477143" fill="none" stroke="black" stroke-width="2"/>
  <ellipse cx="100" cy="0" rx="22.38477631085024" ry="20.970562748477143" fill="none" stroke="black" stroke-width="2"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A-&gt;B</title>
  <line x1="34.89832060373717" y1="0" x2="65.10167939626282" y2="4.2738116622984855e-15" stroke="black"/>
  <polygon points="24.89832060373717,0 34.89832060373717,-3.4999999999999996 34.89832060373717,3.4999999999999996 24.89832060373717,0" fill="black" stroke="black"/>
  <polygon points="75.10167939626282,3.049164863151132e-15 65.10167939626282,3.500000000000005 65.10167939626282,-3.4999999999999964 75.10167939626282,3.049164863151132e-15" fill="black" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeDoubleEllipse, Dashed) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("ellipse");
    node->setShape(SVGNode::SHAPE_DOUBLE_ELLIPSE);
    node->appendStyleDashed();
    node->setPrecomputedTextSize(10, 16);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: ellipse -->
<g class="node" id="ellipse">
  <title>ellipse</title>
  <ellipse cx="0" cy="0" rx="18.38477631085024" ry="16.970562748477143" fill="none" stroke="black" stroke-dasharray="5,2"/>
  <ellipse cx="0" cy="0" rx="22.38477631085024" ry="20.970562748477143" fill="none" stroke="black" stroke-dasharray="5,2"/>
  <rect x="-5" y="-8" width="10" height="16" fill="none" stroke="blue"/>
  <rect x="-13" y="-12" width="26" height="24" fill="none" stroke="red"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
