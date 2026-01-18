#include "svg_diagram.h"
#include "test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGGraph, EmptyGraph) {
    SVGDiagram diagram;
    diagram.enableDebug();
    diagram.addSubgraph("test");
    const auto svg = diagram.render();
    const auto expected = "";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGGraph, OneCircle) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("gray");
    diagram.enableDebug();
    const auto graph = diagram.addSubgraph("cluster1");
    auto node = make_shared<SVGNode>("node1");
    graph->addNode(node);
    graph->defaultNodeAttributes().setShape(SVGNode::SHAPE_CIRCLE);
    graph->defaultNodeAttributes().setPenWidth(10.0);
    graph->defaultNodeAttributes().setAttribute(ATTR_KEY_FIXED_SIZE, "ON");
    graph->defaultNodeAttributes().setSize(20.0, 20.0);
    graph->setColor("black");
    graph->setFillColor("white");
    graph->setPenWidth(2.0);
    const auto svg = diagram.render();
    const auto expected = R"(<rect x="-31" y="-31" width="62" height="62" fill="gray"/>
<g class="cluster" id="cluster1">
  <rect x="-23" y="-23" width="46" height="46" fill="white" stroke="black" stroke-width="2"/>
  <rect x="-15" y="-15" width="30" height="30" fill="none" stroke="green"/>
</g>
<!-- Node: node1 -->
<g class="node" id="node1">
  <title>node1</title>
  <circle cx="0" cy="0" r="10" fill="none" stroke="black" stroke-width="10"/>
  <rect x="-4.2" y="-7" width="8.4" height="14" fill="none" stroke="blue"/>
  <rect x="-12.2" y="-11" width="24.4" height="22" fill="none" stroke="red"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGGraph, OneCircleWithLabel) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("gray");
    diagram.enableDebug();
    const auto graph = diagram.addSubgraph("cluster1");
    auto node = make_shared<SVGNode>("node1");
    graph->addNode(node);
    graph->defaultNodeAttributes().setShape(SVGNode::SHAPE_ELLIPSE);
    graph->defaultNodeAttributes().setAttribute(ATTR_KEY_FIXED_SIZE, "ON");
    graph->defaultNodeAttributes().setSize(100.0, 100.0);
    graph->setColor("black");
    graph->setFillColor("white");
    graph->setLabel("Subgraph");
    graph->setPrecomputedTextSize(60, 16);
    const auto svg = diagram.render();
    const auto expected = R"(<rect x="-66.5" y="-90.5" width="133" height="157" fill="gray"/>
<g class="cluster" id="cluster1">
  <rect x="-58.5" y="-82.5" width="117" height="141" fill="white" stroke="black"/>
  <rect x="-50.5" y="-74.5" width="101" height="125" fill="none" stroke="green"/>
</g>
<rect x="-30" y="-74.5" width="60" height="16" fill="none" stroke="blue"/>
<rect x="-38" y="-82.5" width="76" height="32" fill="none" stroke="red"/>
<text x="0" y="-66.5" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">Subgraph</text>
<!-- Node: node1 -->
<g class="node" id="node1">
  <title>node1</title>
  <ellipse cx="0" cy="0" rx="50" ry="50" fill="none" stroke="black"/>
  <rect x="-4.2" y="-7" width="8.4" height="14" fill="none" stroke="blue"/>
  <rect x="-12.2" y="-11" width="24.4" height="22" fill="none" stroke="red"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGGraph, OneCircleWithLongLabel) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("gray");
    diagram.enableDebug();
    const auto graph = diagram.addSubgraph("cluster1");
    auto node = make_shared<SVGNode>("node1");
    graph->addNode(node);
    graph->defaultNodeAttributes().setShape(SVGNode::SHAPE_ELLIPSE);
    graph->defaultNodeAttributes().setAttribute(ATTR_KEY_FIXED_SIZE, "ON");
    graph->defaultNodeAttributes().setSize(20.0, 20.0);
    graph->setColor("black");
    graph->setFillColor("white");
    graph->setLabel("Subgraph");
    graph->setPrecomputedTextSize(60, 16);
    const auto svg = diagram.render();
    const auto expected = R"(<rect x="-54" y="-50.5" width="108" height="77" fill="gray"/>
<g class="cluster" id="cluster1">
  <rect x="-46" y="-42.5" width="92" height="61" fill="white" stroke="black"/>
  <rect x="-38" y="-34.5" width="76" height="45" fill="none" stroke="green"/>
</g>
<rect x="-30" y="-34.5" width="60" height="16" fill="none" stroke="blue"/>
<rect x="-38" y="-42.5" width="76" height="32" fill="none" stroke="red"/>
<text x="0" y="-26.5" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">Subgraph</text>
<!-- Node: node1 -->
<g class="node" id="node1">
  <title>node1</title>
  <ellipse cx="0" cy="0" rx="10" ry="10" fill="none" stroke="black"/>
  <rect x="-4.2" y="-7" width="8.4" height="14" fill="none" stroke="blue"/>
  <rect x="-12.2" y="-11" width="24.4" height="22" fill="none" stroke="red"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGGraph, GraphGradientColor) {
    SVGDiagram diagram;
    const auto graph = diagram.addSubgraph("G");
    graph->setFillColor("gold:red");
    auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_ELLIPSE);
    node->setMargin(8, 4);
    node->setColor("none");
    node->setFillColor("red:gold");
    graph->addNode(node);
    const auto svg = diagram.render();
    const auto expected = R"s(<defs>
  <linearGradient id="G__fill_color">
    <stop offset="0%" stop-color="gold"/>
    <stop offset="100%" stop-color="red"/>
  </linearGradient>
</defs>
<g class="cluster" id="G">
  <rect x="-25.25340546095176" y="-23.556349186104047" width="50.50681092190352" height="47.112698372208094" fill="url('#G__fill_color')" stroke="none"/>
</g>
<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <defs>
    <linearGradient id="A__fill_color">
      <stop offset="0%" stop-color="red"/>
      <stop offset="100%" stop-color="gold"/>
    </linearGradient>
  </defs>
  <ellipse cx="0" cy="0" rx="17.25340546095176" ry="15.556349186104047" fill="url('#A__fill_color')" stroke="none"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}