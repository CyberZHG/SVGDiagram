#include "svg_diagram.h"
#include "../test_utils.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

void TestSVGEdgeSplineAddTwoNodesCase1(SVGDiagram& diagram) {
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

string TestSVGEdgeSplineExpectedNodesSVGCase2() {
    return R"(  <circle cx="100" cy="100" r="17.692" fill="none" stroke="black" />
  <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >A</text>
  <circle cx="200" cy="150" r="26.401" fill="none" stroke="black" />
  <text x="200" y="150" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >B</text>
)";
}

TEST(TestSVGEdgeSpline, TwoCircleOneLine) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"(  <line x1="115.824" y1="107.912" x2="176.386" y2="138.193" stroke="black" />)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnection) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"(  <path d="M 82.463 102.338 C 60.386 105.282 -65.221 112.581 -50 120 C -34.779 127.419 136.489 142.379 173.787 146.854" fill="none" stroke="black" />)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleTwoLineSelfCycle) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge1 = std::make_unique<SVGEdge>("A", "A");
    edge1->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge1->addConnectionPoint(130, 140);
    edge1->addConnectionPoint(100, 160);
    edge1->addConnectionPoint(70, 140);
    diagram.addEdge(std::move(edge1));
    auto edge2 = std::make_unique<SVGEdge>("B", "B");
    edge2->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge2->addConnectionPoint(250, 130);
    edge2->addConnectionPoint(270, 150);
    edge2->addConnectionPoint(250, 170);
    diagram.addEdge("B -> B", std::move(edge2));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"(  <path d="M 110.615 114.153 C 113.846 118.461 131.769 132.359 130 140 C 128.231 147.641 110 160 100 160 C 90 160 71.769 147.641 70 140 C 68.231 132.359 86.154 118.461 89.385 114.153" fill="none" stroke="black" />
  <path d="M 224.512 140.195 C 228.760 138.496 242.419 128.366 250 130 C 257.581 131.634 270 143.333 270 150 C 270 156.667 257.581 168.366 250 170 C 242.419 171.634 228.760 161.504 224.512 159.805" fill="none" stroke="black" />)";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

string TestSVGEdgeSplineExpectedArrowNormalSVG() {
    return R"(  <defs>
    <marker id="arrow_type_normal__fill_black__stroke_black" markerWidth="10" markerHeight="7" refX="10" refY="3.5" orient="auto-start-reverse">
      <polygon points="0 0 10 3.5 0 7" fill="black" stroke="black" />
    </marker>
  </defs>
)";
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineArrowHead) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedArrowNormalSVG() + TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(  <line x1="115.824" y1="107.912" x2="176.386" y2="138.193" marker-end="url(#arrow_type_normal__fill_black__stroke_black)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineArrowTail) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedArrowNormalSVG() + TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(  <line x1="115.824" y1="107.912" x2="176.386" y2="138.193" marker-start="url(#arrow_type_normal__fill_black__stroke_black)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineArrowBoth) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedArrowNormalSVG() + TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(  <line x1="115.824" y1="107.912" x2="176.386" y2="138.193" marker-end="url(#arrow_type_normal__fill_black__stroke_black)" marker-start="url(#arrow_type_normal__fill_black__stroke_black)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionArrowHead) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedArrowNormalSVG() + TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(  <path d="M 82.463 102.338 C 60.386 105.282 -65.221 112.581 -50 120 C -34.779 127.419 136.489 142.379 173.787 146.854" fill="none" marker-end="url(#arrow_type_normal__fill_black__stroke_black)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionArrowTail) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedArrowNormalSVG() + TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(  <path d="M 82.463 102.338 C 60.386 105.282 -65.221 112.581 -50 120 C -34.779 127.419 136.489 142.379 173.787 146.854" fill="none" marker-start="url(#arrow_type_normal__fill_black__stroke_black)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionArrowBoth) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedArrowNormalSVG() + TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(  <path d="M 82.463 102.338 C 60.386 105.282 -65.221 112.581 -50 120 C -34.779 127.419 136.489 142.379 173.787 146.854" fill="none" marker-end="url(#arrow_type_normal__fill_black__stroke_black)" marker-start="url(#arrow_type_normal__fill_black__stroke_black)" stroke="black" />)s";
    compareSVGContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
