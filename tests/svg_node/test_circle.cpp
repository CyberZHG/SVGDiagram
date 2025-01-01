#include "svg_diagram.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodeCircle, OneCircleAutoSizeNoText) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    SVGNode node;
    node.adjustNodeSize();
    diagram.addSVGDraw(node.produceSVGDraws());
    const auto svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="48.433708498984764" height="48.433708498984764" viewBox="-24.216854249492382 -24.216854249492382 48.433708498984764 48.433708498984764">
  <circle cx="0" cy="0" r="16.216854249492382" fill="none" stroke="black" />
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeText42) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    SVGNode node;
    node.setAttribute(DOT_ATTR_KEY_LABEL, "42");
    node.adjustNodeSize();
    diagram.addSVGDraw(node.produceSVGDraws());
    const auto svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="48.433708498984764" height="48.433708498984764" viewBox="-24.216854249492382 -24.216854249492382 48.433708498984764 48.433708498984764">
  <circle cx="0" cy="0" r="16.216854249492382" fill="none" stroke="black" />
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >42</text>
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeTextTwoLines) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    SVGNode node;
    node.setAttribute(DOT_ATTR_KEY_LABEL, "AB\nCD");
    node.adjustNodeSize();
    diagram.addSVGDraw(node.produceSVGDraws());
    const auto svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="62.01015869776647" height="62.01015869776647" viewBox="-31.005079348883235 -31.005079348883235 62.01015869776647 62.01015869776647">
  <circle cx="0" cy="0" r="23.005079348883235" fill="none" stroke="black" />
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >
    <tspan x="0" dy="-0.6em">AB</tspan>
    <tspan x="0" dy="1.2em">CD</tspan>
  </text>
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
