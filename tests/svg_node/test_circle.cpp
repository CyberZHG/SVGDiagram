#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodeCircle, OneCircleAutoSizeNoText) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMargin(8, 4);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: circle -->
<g class="node" id="circle">
  <title>circle</title>
  <circle cx="0" cy="0" r="15.913830462839549" fill="none" stroke="black"/>
  <rect x="-3.5" y="-7" width="7" height="14" fill="none" stroke="blue"/>
  <rect x="-11.5" y="-11" width="23" height="22" fill="none" stroke="red"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeText2) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMargin(8, 4);
    node->setLabel("2");
    node->setPrecomputedTextSize(10, 16);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: circle -->
<g class="node" id="circle">
  <title>circle</title>
  <circle cx="0" cy="0" r="17.69180601295413" fill="none" stroke="black"/>
  <rect x="-5" y="-8" width="10" height="16" fill="none" stroke="blue"/>
  <rect x="-13" y="-12" width="26" height="24" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">2</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeText42) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMargin(8, 4);
    node->setLabel("42");
    node->setPrecomputedTextSize(20, 16);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: circle -->
<g class="node" id="circle">
  <title>circle</title>
  <circle cx="0" cy="0" r="21.633307652783937" fill="none" stroke="black"/>
  <rect x="-10" y="-8" width="20" height="16" fill="none" stroke="blue"/>
  <rect x="-18" y="-12" width="36" height="24" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">42</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeTextA) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMargin(8, 4);
    node->setLabel("A");
    node->setPrecomputedTextSize(15, 16);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: circle -->
<g class="node" id="circle">
  <title>circle</title>
  <circle cx="0" cy="0" r="19.60229578391266" fill="none" stroke="black"/>
  <rect x="-7.5" y="-8" width="15" height="16" fill="none" stroke="blue"/>
  <rect x="-15.5" y="-12" width="31" height="24" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">A</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeTextTwoLines) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMargin(8, 4);
    node->setLabel("天朗气清\n惠风和畅");
    node->setPrecomputedTextSize(80, 35);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: circle -->
<g class="node" id="circle">
  <title>circle</title>
  <circle cx="0" cy="0" r="52.59515186782903" fill="none" stroke="black"/>
  <rect x="-40" y="-17.5" width="80" height="35" fill="none" stroke="blue"/>
  <rect x="-48" y="-21.5" width="96" height="43" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">
    <tspan x="0" dy="-0.6em">天朗气清</tspan>
    <tspan x="0" dy="1.2em">惠风和畅</tspan>
  </text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
