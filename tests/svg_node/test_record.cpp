#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

#ifndef SVG_DIAGRAM_ENABLE_PANGO_CAIRO

TEST(TestSVGNodeRecord, TextOnly) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("foo");
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-18.5" y="-11" width="37" height="22" fill="none" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, HorizontalSplit2) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("foo|bar");
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-37" y="-11" width="74" height="22" fill="none" stroke="black"/>
  <text x="-18.5" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="0" y1="-11" x2="0" y2="11" stroke="black"/>
  <text x="18.5" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, VerticalSplit2) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("{foo|bar}");
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-18.5" y="-22" width="37" height="44" fill="none" stroke="black"/>
  <text x="0" y="-11" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="-18.5" y1="0" x2="18.5" y2="0" stroke="black"/>
  <text x="0" y="11" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, PenWidth) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("{{foo|bar}|foobar}");
    node->setPenWidth(2);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-37" y="-22" width="74" height="44" fill="none" stroke="black" stroke-width="2"/>
  <text x="-18.5" y="-11" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="0" y1="-22" x2="0" y2="0" stroke="black" stroke-width="2"/>
  <text x="18.5" y="-11" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="-37" y1="0" x2="37" y2="0" stroke="black" stroke-width="2"/>
  <text x="0" y="11" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foobar</text>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, FontSize) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("{{foo|bar}|foobar}");
    node->setFontSize(16);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-40" y="-24" width="80" height="48" fill="none" stroke="black"/>
  <text x="-20" y="-12" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">foo</text>
  <line x1="0" y1="-24" x2="0" y2="0" stroke="black"/>
  <text x="20" y="-12" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">bar</text>
  <line x1="-40" y1="0" x2="40" y2="0" stroke="black"/>
  <text x="0" y="12" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">foobar</text>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, EmptyText) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("{{|}|}");
    node->setFontSize(16);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-24" y="-24" width="48" height="48" fill="none" stroke="black"/>
  <line x1="0" y1="-24" x2="0" y2="0" stroke="black"/>
  <line x1="-24" y1="0" x2="24" y2="0" stroke="black"/>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, SpecialCase1) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("hello\nworld|{b|{c|d|e}|f}|g|h");
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-83" y="-33" width="166" height="66" fill="none" stroke="black"/>
  <text x="-57.5" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">
    <tspan x="-57.5" dy="-0.6em">hello</tspan><tspan x="-57.5" dy="1.2em">world</tspan>
  </text>
  <line x1="-32" y1="-33" x2="-32" y2="33" stroke="black"/>
  <text x="2.5" y="-22" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">b</text>
  <line x1="-32" y1="-11" x2="37" y2="-11" stroke="black"/>
  <text x="-20.5" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">c</text>
  <line x1="-9" y1="-11" x2="-9" y2="11" stroke="black"/>
  <text x="2.5" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">d</text>
  <line x1="14" y1="-11" x2="14" y2="11" stroke="black"/>
  <text x="25.5" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">e</text>
  <line x1="-32" y1="11" x2="37" y2="11" stroke="black"/>
  <text x="2.5" y="22" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">f</text>
  <line x1="37" y1="-33" x2="37" y2="33" stroke="black"/>
  <text x="48.5" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">g</text>
  <line x1="60" y1="-33" x2="60" y2="33" stroke="black"/>
  <text x="71.5" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">h</text>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

#endif
