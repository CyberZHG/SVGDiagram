#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

void TestSVGEdgeLineAddTwoNodesCase1(SVGDiagram& diagram) {
    auto node1 = std::make_shared<SVGNode>(100, 100);
    node1->setShape(SVGNode::SHAPE_CIRCLE);
    node1->setMargin(8, 4);
    node1->setPrecomputedTextSize(10, 16);
    node1->setLabel("A");
    diagram.addNode("A", node1);
    auto node2 = std::make_shared<SVGNode>(200, 150);
    node2->setShape(SVGNode::SHAPE_CIRCLE);
    node2->setMargin(16, 8);
    node2->setPrecomputedTextSize(10, 16);
    node2->setLabel("B");
    diagram.addNode("B", node2);
}

string TestSVGEdgeLineExpectedNodesSVGCase1() {
    return R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <circle cx="100" cy="100" r="17.69180601295413" fill="none" stroke="black"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">A</text>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <circle cx="200" cy="150" r="26.40075756488817" fill="none" stroke="black"/>
  <text x="200" y="150" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">B</text>
</g>)";
}

TEST(TestSVGEdgeLine, TwoCircleOneLine) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnection) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleTwoLineSelfCycle) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge1 = std::make_shared<SVGEdge>("A", "A");
    edge1->setSplines(SVGEdge::SPLINES_LINE);
    edge1->addConnectionPoint(130, 140);
    edge1->addConnectionPoint(100, 160);
    edge1->addConnectionPoint(70, 140);
    diagram.addEdge(edge1);
    auto edge2 = std::make_shared<SVGEdge>("B", "B");
    edge2->setSplines(SVGEdge::SPLINES_LINE);
    edge2->addConnectionPoint(250, 130);
    edge2->addConnectionPoint(270, 150);
    edge2->addConnectionPoint(250, 170);
    diagram.addEdge("B -> B", edge2);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

string TestSVGEdgeLineExpectedArrowNormalSVG() {
    return R"(  <defs>
    <marker id="arrow_type_normal__fill_black__stroke_none" markerWidth="10" markerHeight="7" refX="10" refY="3.5" orient="auto-start-reverse">
      <polygon points="0 0 10 3.5 0 7" fill="black" stroke="none" />
    </marker>
  </defs>
)";
}

TEST(TestSVGEdgeLine, TwoCircleOneLineArrowHead) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineArrowTail) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineArrowBoth) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionArrowHead) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionArrowTail) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionArrowBoth) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionArrowBothDashed) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    edge->appendStyleDashed();
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionArrowBothDotted) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    edge->appendStyleDotted();
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionArrowBothOpacity) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    edge->setColor("#00000088");
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

string TestSVGEdgeLineExpectedNodesSVGCase1WithDebug() {
    return R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <circle cx="100" cy="100" r="17.69180601295413" fill="none" stroke="black"/>
  <rect x="95" y="92" width="10" height="16" fill="none" stroke="blue"/>
  <rect x="87" y="88" width="26" height="24" fill="none" stroke="red"/>
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">A</text>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <circle cx="200" cy="150" r="26.40075756488817" fill="none" stroke="black"/>
  <rect x="195" y="142" width="10" height="16" fill="none" stroke="blue"/>
  <rect x="179" y="134" width="42" height="32" fill="none" stroke="red"/>
  <text x="200" y="150" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">B</text>
</g>)";
}

TEST(TestSVGEdgeLine, TwoCircleOneLineWithLabel) {
    SVGDiagram diagram;
    diagram.enableDebug();
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->setLabel("42");
    edge->setTailLabel("tail");
    edge->setHeadLabel("head");
    edge->setPrecomputedTextSize(20, 16);
    edge->setPrecomputedTextSize("tail", 40, 16);
    edge->setPrecomputedTextSize("head", 40, 16);
    edge->setLabelDistance(1);
    edge->setMargin(2.0);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionWithLabel) {
    SVGDiagram diagram;
    diagram.enableDebug();
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>();
    edge->setNodeFrom("A");
    edge->setNodeTo("B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setLabel("42");
    edge->setTailLabel("tail");
    edge->setHeadLabel("head");
    edge->setPrecomputedTextSize(20, 16);
    edge->setPrecomputedTextSize("tail", 40, 16);
    edge->setPrecomputedTextSize("head", 40, 16);
    edge->setLabelDistance(2);
    edge->setMargin(2.0);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
