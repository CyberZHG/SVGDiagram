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
  <rect x="-20.599999999999998" y="-11" width="41.199999999999996" height="22" fill="none" stroke="black"/>
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
  <rect x="-41.199999999999996" y="-11" width="82.39999999999999" height="22" fill="none" stroke="black"/>
  <text x="-20.599999999999998" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="0" y1="-11" x2="0" y2="11" stroke="black"/>
  <text x="20.599999999999998" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
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
  <rect x="-20.599999999999998" y="-22" width="41.199999999999996" height="44" fill="none" stroke="black"/>
  <text x="0" y="-11" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="-20.599999999999998" y1="0" x2="20.599999999999998" y2="0" stroke="black"/>
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
  <rect x="-41.199999999999996" y="-22" width="82.39999999999999" height="44" fill="none" stroke="black" stroke-width="2"/>
  <text x="-20.599999999999998" y="-11" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="0" y1="-22" x2="0" y2="0" stroke="black" stroke-width="2"/>
  <text x="20.599999999999998" y="-11" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="-41.199999999999996" y1="0" x2="41.199999999999996" y2="0" stroke="black" stroke-width="2"/>
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
  <rect x="-44.8" y="-24" width="89.6" height="48" fill="none" stroke="black"/>
  <text x="-22.4" y="-12" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">foo</text>
  <line x1="0" y1="-24" x2="0" y2="0" stroke="black"/>
  <text x="22.4" y="-12" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">bar</text>
  <line x1="-44.8" y1="0" x2="44.8" y2="0" stroke="black"/>
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
  <rect x="-25.6" y="-24" width="51.2" height="48" fill="none" stroke="black"/>
  <line x1="0" y1="-24" x2="0" y2="0" stroke="black"/>
  <line x1="-25.6" y1="0" x2="25.6" y2="0" stroke="black"/>
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
  <rect x="-25.6" y="-24" width="51.2" height="48" fill="none" stroke="black"/>
  <line x1="0" y1="-24" x2="0" y2="0" stroke="black"/>
  <line x1="-25.6" y1="0" x2="25.6" y2="0" stroke="black"/>
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
  <rect x="-36.8" y="-36" width="73.6" height="72" fill="none" stroke="black"/>
  <text x="-28.799999999999997" y="-24" text-anchor="start" dominant-baseline="central" font-family="Times,serif" font-size="16">foo</text>
  <line x1="-36.8" y1="-12" x2="36.8" y2="-12" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">foobar</text>
  <line x1="-36.8" y1="12" x2="36.8" y2="12" stroke="black"/>
  <text x="28.799999999999997" y="24" text-anchor="end" dominant-baseline="central" font-family="Times,serif" font-size="16">bar</text>
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
  <rect x="-36.8" y="-84" width="73.6" height="168" fill="none" stroke="black"/>
  <text x="0" y="-62.4" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan text-anchor="start" x="-28.799999999999997" dy="-0.6em">foo</tspan><tspan text-anchor="start" x="-28.799999999999997" dy="1.2em">foobar</tspan>
  </text>
  <line x1="-36.8" y1="-40.8" x2="36.8" y2="-40.8" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan x="0" dy="-1.7999999999999998em">foobar</tspan><tspan x="0" dy="1.2em">foo</tspan><tspan x="0" dy="1.2em">bar</tspan><tspan x="0" dy="1.2em">barfoo</tspan>
  </text>
  <line x1="-36.8" y1="40.8" x2="36.8" y2="40.8" stroke="black"/>
  <text x="0" y="62.4" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan text-anchor="end" x="28.799999999999997" dy="-0.6em">bar</tspan><tspan text-anchor="end" x="28.799999999999997" dy="1.2em">barfoo</tspan>
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
  <rect x="-110.39999999999999" y="-40.8" width="220.79999999999998" height="81.6" fill="none" stroke="black"/>
  <text x="-73.6" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan text-anchor="start" x="-102.39999999999999" dy="-0.6em">foo</tspan><tspan text-anchor="start" x="-102.39999999999999" dy="1.2em">foobar</tspan>
  </text>
  <line x1="-36.8" y1="-40.8" x2="-36.8" y2="40.8" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan x="0" dy="-1.7999999999999998em">foobar</tspan><tspan x="0" dy="1.2em">foo</tspan><tspan x="0" dy="1.2em">bar</tspan><tspan x="0" dy="1.2em">barfoo</tspan>
  </text>
  <line x1="36.8" y1="-40.8" x2="36.8" y2="40.8" stroke="black"/>
  <text x="73.6" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="16">
    <tspan text-anchor="end" x="102.39999999999999" dy="-0.6em">bar</tspan><tspan text-anchor="end" x="102.39999999999999" dy="1.2em">barfoo</tspan>
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
  <rect x="-90" y="-33" width="180" height="66" fill="none" stroke="black"/>
  <text x="-61" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">
    <tspan x="-61" dy="-0.6em">hello</tspan><tspan x="-61" dy="1.2em">world</tspan>
  </text>
  <line x1="-32" y1="-33" x2="-32" y2="33" stroke="black"/>
  <text x="4.599999999999994" y="-22" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">b</text>
  <line x1="-32" y1="-11" x2="41.19999999999999" y2="-11" stroke="black"/>
  <text x="-19.8" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">c</text>
  <line x1="-7.600000000000001" y1="-11" x2="-7.600000000000001" y2="11" stroke="black"/>
  <text x="4.599999999999998" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">d</text>
  <line x1="16.799999999999997" y1="-11" x2="16.799999999999997" y2="11" stroke="black"/>
  <text x="28.999999999999996" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">e</text>
  <line x1="-32" y1="11" x2="41.19999999999999" y2="11" stroke="black"/>
  <text x="4.599999999999994" y="22" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">f</text>
  <line x1="41.19999999999999" y1="-33" x2="41.19999999999999" y2="33" stroke="black"/>
  <text x="53.39999999999999" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">g</text>
  <line x1="65.6" y1="-33" x2="65.6" y2="33" stroke="black"/>
  <text x="77.8" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">h</text>
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
  <rect x="-20.599999999999998" y="-11" width="41.199999999999996" height="22" fill="none" stroke="black"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="79.4" y="89" width="41.199999999999996" height="22" fill="none" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A-&gt;B</title>
  <line x1="11.35857864376269" y1="11.358578643762689" x2="88.64142135623732" y2="88.64142135623732" stroke="black"/>
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
  <rect x="-45" y="-33" width="90" height="66" fill="none" stroke="black"/>
  <line x1="-45" y1="-11" x2="45" y2="-11" stroke="black"/>
  <line x1="-20.6" y1="-11" x2="-20.6" y2="11" stroke="black"/>
  <text x="-3.552713678800501e-15" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="20.599999999999994" y1="-11" x2="20.599999999999994" y2="11" stroke="black"/>
  <line x1="-45" y1="11" x2="45" y2="11" stroke="black"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="55" y="67" width="90" height="66" fill="none" stroke="black"/>
  <line x1="79.4" y1="67" x2="79.4" y2="133" stroke="black"/>
  <line x1="79.4" y1="89" x2="120.6" y2="89" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="79.4" y1="111" x2="120.6" y2="111" stroke="black"/>
  <line x1="120.6" y1="67" x2="120.6" y2="133" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A-&gt;B</title>
  <line x1="11.35857864376269" y1="11.358578643762689" x2="80.35869475500797" y2="80.35869475500797" stroke="black"/>
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
  <rect x="-45" y="-33" width="90" height="66" fill="none" stroke="black"/>
  <line x1="-45" y1="-11" x2="45" y2="-11" stroke="black"/>
  <line x1="-20.6" y1="-11" x2="-20.6" y2="11" stroke="black"/>
  <text x="-3.552713678800501e-15" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="20.599999999999994" y1="-11" x2="20.599999999999994" y2="11" stroke="black"/>
  <line x1="-45" y1="11" x2="45" y2="11" stroke="black"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="55" y="67" width="90" height="66" fill="none" stroke="black"/>
  <line x1="79.4" y1="67" x2="79.4" y2="133" stroke="black"/>
  <line x1="79.4" y1="89" x2="120.6" y2="89" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="79.4" y1="111" x2="120.6" y2="111" stroke="black"/>
  <line x1="120.6" y1="67" x2="120.6" y2="133" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A-&gt;B</title>
  <line x1="-11.358578643762689" y1="11.35857864376269" x2="-50" y2="50" stroke="black"/>
  <line x1="-50" y1="50" x2="67.97729282797336" y2="89.32576427599112" stroke="black"/>
  <polygon points="77.4641258084785,92.4880419361595 66.87049564691443,92.64615581916793 69.0840900090323,86.00537273281432 77.4641258084785,92.4880419361595" fill="black" stroke="black"/>
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
  <rect x="-45" y="-33" width="90" height="66" fill="none" stroke="black"/>
  <line x1="-45" y1="-11" x2="45" y2="-11" stroke="black"/>
  <line x1="-20.6" y1="-11" x2="-20.6" y2="11" stroke="black"/>
  <text x="-3.552713678800501e-15" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="20.599999999999994" y1="-11" x2="20.599999999999994" y2="11" stroke="black"/>
  <line x1="-45" y1="11" x2="45" y2="11" stroke="black"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="55" y="67" width="90" height="66" fill="none" stroke="black"/>
  <line x1="79.4" y1="67" x2="79.4" y2="133" stroke="black"/>
  <line x1="79.4" y1="89" x2="120.6" y2="89" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="79.4" y1="111" x2="120.6" y2="111" stroke="black"/>
  <line x1="120.6" y1="67" x2="120.6" y2="133" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A-&gt;B</title>
  <path d="M -11.499999999999998 11.5 C -17.916666666666664 17.916666666666668 -65.06666666666666 36.422222222222224 -50 50 C -36.8016 61.894133333333336 35.702175200000006 80.42606906666666 67.9217287456 89.6529568992" fill="none" stroke="black"/>
  <polygon points="77.45102438548166,92.52930412247501 66.86624987630844,92.9903340455351 68.88901050758271,86.28895811005984 77.45102438548166,92.52930412247501" fill="black" stroke="black"/>
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
  <rect x="-45" y="-33" width="90" height="66" fill="none" stroke="black"/>
  <line x1="-45" y1="-11" x2="45" y2="-11" stroke="black"/>
  <line x1="-20.6" y1="-11" x2="-20.6" y2="11" stroke="black"/>
  <text x="-3.552713678800501e-15" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="20.599999999999994" y1="-11" x2="20.599999999999994" y2="11" stroke="black"/>
  <line x1="-45" y1="11" x2="45" y2="11" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A-&gt;A</title>
  <path d="M 3.0814157129579107 -11.5 C 14.331415712957911 -28.375 11.250000000000002 -41.5 2.541142108230758e-15 -41.5 C -8.853749999999998 -41.5 -12.648132118719026 -33.370781875 -8.379114833793334 -21.682127528125" fill="none" stroke="black"/>
  <polygon points="-3.780004146436692,-12.842680351811358 -11.50046903209861,-20.098327941741655 -5.290698689169098,-23.32923374167967 -3.780004146436692,-12.842680351811358" fill="black" stroke="black"/>
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
  <rect x="-45" y="-33" width="90" height="66" fill="none" stroke="black"/>
  <line x1="-45" y1="-11" x2="45" y2="-11" stroke="black"/>
  <text x="-32.8" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">A</text>
  <line x1="-20.6" y1="-11" x2="-20.6" y2="11" stroke="black"/>
  <text x="-3.552713678800501e-15" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">foo</text>
  <line x1="20.599999999999994" y1="-11" x2="20.599999999999994" y2="11" stroke="black"/>
  <line x1="-45" y1="11" x2="45" y2="11" stroke="black"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="55" y="67" width="90" height="66" fill="none" stroke="black"/>
  <line x1="79.4" y1="67" x2="79.4" y2="133" stroke="black"/>
  <line x1="79.4" y1="89" x2="120.6" y2="89" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">bar</text>
  <line x1="79.4" y1="111" x2="120.6" y2="111" stroke="black"/>
  <text x="100" y="122" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">B</text>
  <line x1="120.6" y1="67" x2="120.6" y2="133" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A-&gt;B</title>
  <line x1="33.3585786437627" y1="33.35857864376269" x2="58.358694755007974" y2="58.358694755007974" stroke="black"/>
  <polygon points="65.42976256687345,65.42976256687345 55.88382102085506,60.83356848916089 60.83356848916089,55.88382102085506 65.42976256687345,65.42976256687345" fill="black" stroke="black"/>
</g>
)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

#endif
