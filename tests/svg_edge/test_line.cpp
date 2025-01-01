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
    return R"(<!-- node_id = A -->
<circle cx="100" cy="100" r="17.69180601295413" fill="none" stroke="black"/>
<text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">A</text>
<!-- node_id = B -->
<circle cx="200" cy="150" r="26.40075756488817" fill="none" stroke="black"/>
<text x="200" y="150" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">B</text>)";
}

TEST(TestSVGEdgeLine, TwoCircleOneLine) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"(<!-- edge_id = A -> B -->
<line x1="116.15944255250696" y1="108.07972127625348" x2="176.05103437434232" y2="138.02551718717115" stroke="black"/>)";
    compareSVGWithDefaultGraphContent(svg, expected);
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
        R"(<!-- edge_id = A -> B -->
<line x1="82.09167780373907" y1="102.38777629283479" x2="-50" y2="120" stroke="black"/>
<line x1="-50" y1="120" x2="173.41497048088155" y2="146.80979645770577" stroke="black"/>)";
    compareSVGWithDefaultGraphContent(svg, expected);
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
        R"(<!-- edge_id = A -> A -->
<line x1="110.84008360777248" y1="114.45344481036331" x2="130" y2="140" stroke="black"/>
<line x1="130" y1="140" x2="100" y2="160" stroke="black"/>
<line x1="100" y1="160" x2="70" y2="140" stroke="black"/>
<line x1="70" y1="140" x2="89.15991639222753" y2="114.45344481036331" stroke="black"/>
<!-- edge_id = B -> B -->
<line x1="224.86066677979332" y1="140.05573328808268" x2="250" y2="130" stroke="black"/>
<line x1="250" y1="130" x2="270" y2="150" stroke="black"/>
<line x1="270" y1="150" x2="250" y2="170" stroke="black"/>
<line x1="250" y1="170" x2="224.86066677979332" y2="159.94426671191732" stroke="black"/>)";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- edge_id = A -> B -->
<line x1="116.15944255250696" y1="108.07972127625348" x2="176.05103437434232" y2="138.02551718717115" marker-end="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black"/>
)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- edge_id = A -> B -->
<line x1="116.15944255250696" y1="108.07972127625348" x2="176.05103437434232" y2="138.02551718717115" marker-start="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black"/>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- edge_id = A -> B -->
<line x1="116.15944255250696" y1="108.07972127625348" x2="176.05103437434232" y2="138.02551718717115" marker-end="url(#arrow_type_normal__fill_black__stroke_none)" marker-start="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black"/>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- edge_id = A -> B -->
<line x1="82.09167780373907" y1="102.38777629283479" x2="-50" y2="120" stroke="black"/>
<line x1="-50" y1="120" x2="173.41497048088155" y2="146.80979645770577" marker-end="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black"/>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- edge_id = A -> B -->
<line x1="82.09167780373907" y1="102.38777629283479" x2="-50" y2="120" marker-start="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black"/>
<line x1="-50" y1="120" x2="173.41497048088155" y2="146.80979645770577" stroke="black"/>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- edge_id = A -> B -->
<line x1="82.09167780373907" y1="102.38777629283479" x2="-50" y2="120" marker-start="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black"/>
<line x1="-50" y1="120" x2="173.41497048088155" y2="146.80979645770577" marker-end="url(#arrow_type_normal__fill_black__stroke_none)" stroke="black"/>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
