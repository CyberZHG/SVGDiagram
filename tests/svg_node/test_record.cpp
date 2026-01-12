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

TEST(TestSVGNodeRecord, Spaces) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("{ { | } | }");
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

TEST(TestSVGNodeRecord, AlignSingleLinesMix) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("{ foo\\l | foobar | bar\\r }");
    node->setFontSize(16);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-32" y="-36" width="64" height="72" fill="none" stroke="black"/>
  <text x="-24" y="-24" text-anchor="start" dominant-baseline="central" font-family="Times,serif" font-size="16">foo</text>
  <line x1="-32" y1="-12" x2="32" y2="-12" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">foobar</text>
  <line x1="-32" y1="12" x2="32" y2="12" stroke="black"/>
  <text x="24" y="24" text-anchor="end" dominant-baseline="central" font-family="Times,serif" font-size="16">bar</text>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, AlignMultiLinesMix1) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("{ foo\\lfoobar\\l | foobar\nfoo\nbar\nbarfoo | bar\\rbarfoo\\r }");
    node->setFontSize(16);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-32" y="-84" width="64" height="168" fill="none" stroke="black"/>
  <text x="0" y="-62.4" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan text-anchor="start" x="-24" dy="-0.6em">foo</tspan><tspan text-anchor="start" x="-24" dy="1.2em">foobar</tspan>
  </text>
  <line x1="-32" y1="-40.8" x2="32" y2="-40.8" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan x="0" dy="-1.7999999999999998em">foobar</tspan><tspan x="0" dy="1.2em">foo</tspan><tspan x="0" dy="1.2em">bar</tspan><tspan x="0" dy="1.2em">barfoo</tspan>
  </text>
  <line x1="-32" y1="40.8" x2="32" y2="40.8" stroke="black"/>
  <text x="0" y="62.4" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan text-anchor="end" x="24" dy="-0.6em">bar</tspan><tspan text-anchor="end" x="24" dy="1.2em">barfoo</tspan>
  </text>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, AlignMultiLinesMix2) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("foo\\lfoobar\\l | foobar\nfoo\nbar\nbarfoo | bar\\rbarfoo\\r");
    node->setFontSize(16);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-96" y="-40.8" width="192" height="81.6" fill="none" stroke="black"/>
  <text x="-64" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan text-anchor="start" x="-88" dy="-0.6em">foo</tspan><tspan text-anchor="start" x="-88" dy="1.2em">foobar</tspan>
  </text>
  <line x1="-32" y1="-40.8" x2="-32" y2="40.8" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan x="0" dy="-1.7999999999999998em">foobar</tspan><tspan x="0" dy="1.2em">foo</tspan><tspan x="0" dy="1.2em">bar</tspan><tspan x="0" dy="1.2em">barfoo</tspan>
  </text>
  <line x1="32" y1="-40.8" x2="32" y2="40.8" stroke="black"/>
  <text x="64" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan text-anchor="end" x="88" dy="-0.6em">bar</tspan><tspan text-anchor="end" x="88" dy="1.2em">barfoo</tspan>
  </text>
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

TEST(TestSVGNodeRecord, RegularConnection) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setShape(SVGNode::SHAPE_RECORD);
    node1->setLabel("foo");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100, 100);
    node2->setShape(SVGNode::SHAPE_RECORD);
    node2->setLabel("bar");
    const auto edge = diagram.addEdge("A", "B");
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-18.5" y="-11" width="37" height="22" fill="none" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="81.5" y="89" width="37" height="22" fill="none" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="11.358578643762694" y1="11.358578643762693" x2="88.64142135623732" y2="88.64142135623732" stroke="black"/>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, FieldConnectionLine) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setShape(SVGNode::SHAPE_RECORD);
    node1->setLabel("{|{|<foo> foo|}|}");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100, 100);
    node2->setShape(SVGNode::SHAPE_RECORD);
    node2->setLabel("|{|<bar>bar|}|");
    const auto edge = diagram.addEdge("A", "B");
    edge->setFieldFrom("foo");
    edge->setFieldTo("bar");
    edge->setArrowHead();
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-41.5" y="-33" width="83" height="66" fill="none" stroke="black"/>
  <line x1="-41.5" y1="-11" x2="41.5" y2="-11" stroke="black"/>
  <line x1="-18.5" y1="-11" x2="-18.5" y2="11" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="18.5" y1="-11" x2="18.5" y2="11" stroke="black"/>
  <line x1="-41.5" y1="11" x2="41.5" y2="11" stroke="black"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="58.5" y="67" width="83" height="66" fill="none" stroke="black"/>
  <line x1="81.5" y1="67" x2="81.5" y2="133" stroke="black"/>
  <line x1="81.5" y1="89" x2="118.5" y2="89" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="81.5" y1="111" x2="118.5" y2="111" stroke="black"/>
  <line x1="118.5" y1="67" x2="118.5" y2="133" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="11.358578643762694" y1="11.358578643762693" x2="80.35869475500797" y2="80.35869475500797" stroke="black"/>
  <polygon points="87.42976256687345,87.42976256687345 77.88382102085505,82.8335684891609 82.8335684891609,77.88382102085505 87.42976256687345,87.42976256687345" fill="black" stroke="black"/>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, FieldConnectionTwoLines) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setShape(SVGNode::SHAPE_RECORD);
    node1->setLabel("{|{|<foo> foo|}|}");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100, 100);
    node2->setShape(SVGNode::SHAPE_RECORD);
    node2->setLabel("|{|<bar>bar|}|");
    const auto edge = diagram.addEdge("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->setFieldFrom("foo");
    edge->setFieldTo("bar");
    edge->addConnectionPoint(-50, 50);
    edge->setArrowHead();
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-41.5" y="-33" width="83" height="66" fill="none" stroke="black"/>
  <line x1="-41.5" y1="-11" x2="41.5" y2="-11" stroke="black"/>
  <line x1="-18.5" y1="-11" x2="-18.5" y2="11" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="18.5" y1="-11" x2="18.5" y2="11" stroke="black"/>
  <line x1="-41.5" y1="11" x2="41.5" y2="11" stroke="black"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="58.5" y="67" width="83" height="66" fill="none" stroke="black"/>
  <line x1="81.5" y1="67" x2="81.5" y2="133" stroke="black"/>
  <line x1="81.5" y1="89" x2="118.5" y2="89" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="81.5" y1="111" x2="118.5" y2="111" stroke="black"/>
  <line x1="118.5" y1="67" x2="118.5" y2="133" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="-11.358578643762689" y1="11.35857864376269" x2="-50" y2="50" stroke="black"/>
  <line x1="-50" y1="50" x2="70.07729282797335" y2="90.02576427599112" stroke="black"/>
  <polygon points="79.5641258084785,93.18804193615951 68.97049564691443,93.34615581916793 71.18409000903229,86.70537273281433 79.5641258084785,93.18804193615951" fill="black" stroke="black"/>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, FieldConnectionSpline) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setShape(SVGNode::SHAPE_RECORD);
    node1->setLabel("{|{|<foo> foo|}|}");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100, 100);
    node2->setShape(SVGNode::SHAPE_RECORD);
    node2->setLabel("|{|<bar>bar|}|");
    const auto edge = diagram.addEdge("A", "B");
    edge->setFieldFrom("foo");
    edge->setFieldTo("bar");
    edge->addConnectionPoint(-50, 50);
    edge->setArrowHead();
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-41.5" y="-33" width="83" height="66" fill="none" stroke="black"/>
  <line x1="-41.5" y1="-11" x2="41.5" y2="-11" stroke="black"/>
  <line x1="-18.5" y1="-11" x2="-18.5" y2="11" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="18.5" y1="-11" x2="18.5" y2="11" stroke="black"/>
  <line x1="-41.5" y1="11" x2="41.5" y2="11" stroke="black"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="58.5" y="67" width="83" height="66" fill="none" stroke="black"/>
  <line x1="81.5" y1="67" x2="81.5" y2="133" stroke="black"/>
  <line x1="81.5" y1="89" x2="118.5" y2="89" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="81.5" y1="111" x2="118.5" y2="111" stroke="black"/>
  <line x1="118.5" y1="67" x2="118.5" y2="133" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M -11.499999999999998 11.5 C -17.916666666666664 17.916666666666668 -65.41666666666667 36.30555555555556 -50 50 C -36.46416666666667 62.023722222222226 37.45758000000001 80.98540044444444 70.070608162 90.35895195533334" fill="none" stroke="black"/>
  <polygon points="79.55134594050354,93.22824022764296 68.96623574132386,93.6814974076439 70.99391678613308,86.98160863390136 79.55134594050354,93.22824022764296" fill="black" stroke="black"/>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, FieldConnectionSelfLoop) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setShape(SVGNode::SHAPE_RECORD);
    node->setLabel("{|{|<foo> foo|}|}");
    const auto edge = diagram.addSelfLoopToTop("A", 30);
    edge->setFieldFrom("foo");
    edge->setFieldTo("foo");
    edge->setArrowHead();
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-41.5" y="-33" width="83" height="66" fill="none" stroke="black"/>
  <line x1="-41.5" y1="-11" x2="41.5" y2="-11" stroke="black"/>
  <line x1="-18.5" y1="-11" x2="-18.5" y2="11" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="18.5" y1="-11" x2="18.5" y2="11" stroke="black"/>
  <line x1="-41.5" y1="11" x2="41.5" y2="11" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A->A</title>
  <path d="M 3.081415712957911 -11.500000000000002 C 14.331415712957913 -28.375 11.250000000000002 -41.5 2.541142108230758e-15 -41.5 C -8.853749999999998 -41.5 -12.648132118719026 -33.370781875 -8.379114833793334 -21.682127528125005" fill="none" stroke="black"/>
  <polygon points="-3.7800041464366925,-12.84268035181136 -11.500469032098612,-20.098327941741655 -5.290698689169099,-23.32923374167967 -3.7800041464366925,-12.84268035181136" fill="black" stroke="black"/>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeRecord, FieldConnectionLineUnknownField) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setShape(SVGNode::SHAPE_RECORD);
    node1->setLabel("{|{A|<foo> foo|}|}");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100, 100);
    node2->setShape(SVGNode::SHAPE_RECORD);
    node2->setLabel("|{|<bar>bar|B}|");
    const auto edge = diagram.addEdge("A", "B");
    edge->setFieldFrom("foobar");
    edge->setFieldTo("barfoo");
    edge->setArrowHead();
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-41.5" y="-33" width="83" height="66" fill="none" stroke="black"/>
  <line x1="-41.5" y1="-11" x2="41.5" y2="-11" stroke="black"/>
  <text x="-30" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">A</text>
  <line x1="-18.5" y1="-11" x2="-18.5" y2="11" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="18.5" y1="-11" x2="18.5" y2="11" stroke="black"/>
  <line x1="-41.5" y1="11" x2="41.5" y2="11" stroke="black"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="58.5" y="67" width="83" height="66" fill="none" stroke="black"/>
  <line x1="81.5" y1="67" x2="81.5" y2="133" stroke="black"/>
  <line x1="81.5" y1="89" x2="118.5" y2="89" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="81.5" y1="111" x2="118.5" y2="111" stroke="black"/>
  <text x="100" y="122" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">B</text>
  <line x1="118.5" y1="67" x2="118.5" y2="133" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="33.3585786437627" y1="33.35857864376269" x2="58.358694755007974" y2="58.358694755007974" stroke="black"/>
  <polygon points="65.42976256687345,65.42976256687345 55.88382102085506,60.83356848916089 60.83356848916089,55.88382102085506 65.42976256687345,65.42976256687345" fill="black" stroke="black"/>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

#endif
