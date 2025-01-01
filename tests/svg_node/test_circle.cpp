#include "svg_diagram.h"
#include "../test_utils.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodeCircle, OneCircleAutoSizeNoText) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_unique<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMarginInPixels(8, 4);
    diagram.addNode("circle", std::move(node));
    const auto svg = diagram.render();
    const auto expected = R"(  <circle cx="0" cy="0" r="16.971" fill="none" stroke="black" />
  <rect x="-4" y="-8" width="8" height="16" fill="none" stroke="blue" />
  <rect x="-12" y="-12" width="24" height="24" fill="none" stroke="red" />)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeText2) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_unique<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMarginInPixels(8, 4);
    node->setLabel("2");
    node->setPrecomputedTextSize(10, 16);
    diagram.addNode("circle", std::move(node));
    const auto svg = diagram.render();
    const auto expected = R"(  <circle cx="0" cy="0" r="17.692" fill="none" stroke="black" />
  <rect x="-5" y="-8" width="10" height="16" fill="none" stroke="blue" />
  <rect x="-13" y="-12" width="26" height="24" fill="none" stroke="red" />
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >2</text>)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeText42) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_unique<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMarginInPixels(8, 4);
    node->setLabel("42");
    node->setPrecomputedTextSize(20, 16);
    diagram.addNode("circle", std::move(node));
    const auto svg = diagram.render();
    const auto expected = R"(  <circle cx="0" cy="0" r="21.633" fill="none" stroke="black" />
  <rect x="-10" y="-8" width="20" height="16" fill="none" stroke="blue" />
  <rect x="-18" y="-12" width="36" height="24" fill="none" stroke="red" />
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >42</text>
)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeTextA) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_unique<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMarginInPixels(8, 4);
    node->setLabel("A");
    node->setPrecomputedTextSize(15, 16);
    diagram.addNode("circle", std::move(node));
    const auto svg = diagram.render();
    const auto expected = R"(  <circle cx="0" cy="0" r="19.602" fill="none" stroke="black" />
  <rect x="-7.5" y="-8" width="15" height="16" fill="none" stroke="blue" />
  <rect x="-15.5" y="-12" width="31" height="24" fill="none" stroke="red" />
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >A</text>
)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeTextTwoLines) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_unique<SVGNode>();
    node->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node->setMarginInPixels(8, 4);
    node->setLabel("天朗气清\n惠风和畅");
    node->setPrecomputedTextSize(80, 35);
    diagram.addNode("circle", std::move(node));
    const auto svg = diagram.render();
    const auto expected = R"(  <circle cx="0" cy="0" r="52.595" fill="none" stroke="black" />
  <rect x="-40" y="-17.5" width="80" height="35" fill="none" stroke="blue" />
  <rect x="-48" y="-21.5" width="96" height="43" fill="none" stroke="red" />
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >
    <tspan x="0" dy="-0.6em">天朗气清</tspan>
    <tspan x="0" dy="1.2em">惠风和畅</tspan>
  </text>
)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
