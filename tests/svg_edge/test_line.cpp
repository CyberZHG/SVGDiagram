#include "svg_diagram.h"
#include "../test_utils.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

void TestSVGEdgeLineAddTwoNodesCase1(SVGDiagram& diagram) {
    auto node1 = std::make_unique<SVGNode>(100, 100);
    node1->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node1->setMarginInPixels(8, 4);
    node1->setPrecomputedTextSize(10, 16);
    node1->setLabel("A");
    diagram.addNode("A", std::move(node1));
    auto node2 = std::make_unique<SVGNode>(200, 150);
    node2->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node2->setMarginInPixels(16, 8);
    node2->setPrecomputedTextSize(10, 16);
    node2->setLabel("B");
    diagram.addNode("B", std::move(node2));
}

string TestSVGEdgeLineExpectedNodesSVGCase1() {
    return R"(  <circle cx="100" cy="100" r="17.692" fill="none" stroke="black" />
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >A</text>
  <circle cx="200" cy="150" r="26.401" fill="none" stroke="black" />
  <text x="200" y="150" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >B</text>
)";
}

TEST(TestSVGEdgeLine, TwoCircleOneLine) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"(  <line x1="115.824" y1="107.912" x2="176.386" y2="138.193" stroke="black" />)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnection) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"(  <line x1="82.463" y1="102.338" x2="-50" y2="120" stroke="black" />
  <line x1="-50" y1="120" x2="173.787" y2="146.854" stroke="black" />)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleTwoLineSelfCycle) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge1 = std::make_unique<SVGEdge>("A", "A");
    edge1->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge1->addConnectionPoint(130, 140);
    edge1->addConnectionPoint(100, 160);
    edge1->addConnectionPoint(70, 140);
    diagram.addEdge(std::move(edge1));
    auto edge2 = std::make_unique<SVGEdge>("B", "B");
    edge2->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge2->addConnectionPoint(250, 130);
    edge2->addConnectionPoint(270, 150);
    edge2->addConnectionPoint(250, 170);
    diagram.addEdge("B -> B", std::move(edge2));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"(  <line x1="110.615" y1="114.153" x2="130" y2="140" stroke="black" />
  <line x1="130" y1="140" x2="100" y2="160" stroke="black" />
  <line x1="100" y1="160" x2="70" y2="140" stroke="black" />
  <line x1="70" y1="140" x2="89.385" y2="114.153" stroke="black" />
  <line x1="224.512" y1="140.195" x2="250" y2="130" stroke="black" />
  <line x1="250" y1="130" x2="270" y2="150" stroke="black" />
  <line x1="270" y1="150" x2="250" y2="170" stroke="black" />
  <line x1="250" y1="170" x2="224.512" y2="159.805" stroke="black" />)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedArrowNormalSVG() + TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(  <line x1="115.824" y1="107.912" x2="176.386" y2="138.193" marker-end="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineArrowTail) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedArrowNormalSVG() + TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(  <line x1="115.824" y1="107.912" x2="176.386" y2="138.193" marker-start="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineArrowBoth) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedArrowNormalSVG() + TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(  <line x1="115.824" y1="107.912" x2="176.386" y2="138.193" marker-end="url(#arrow_type_normal__fill_black__stroke_none)" marker-start="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionArrowHead) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedArrowNormalSVG() + TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(  <line x1="82.463" y1="102.338" x2="-50" y2="120" stroke="black" />
  <line x1="-50" y1="120" x2="173.787" y2="146.854" marker-end="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionArrowTail) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedArrowNormalSVG() + TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(  <line x1="82.463" y1="102.338" x2="-50" y2="120" marker-start="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black" />
  <line x1="-50" y1="120" x2="173.787" y2="146.854" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionArrowBoth) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedArrowNormalSVG() + TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(  <line x1="82.463" y1="102.338" x2="-50" y2="120" marker-start="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black" />
  <line x1="-50" y1="120" x2="173.787" y2="146.854" marker-end="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
