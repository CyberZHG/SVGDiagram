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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="116.09236051318196" y1="108.04618025659099" x2="176.1181164136673" y2="138.05905820683367" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="82.16601989629028" y1="102.37786401382796" x2="-50" y2="120" stroke="black"/>
  <line x1="-50" y1="120" x2="173.48943624376807" y2="146.81873234925217" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"(<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A->A</title>
  <line x1="110.79508360777247" y1="114.3934448103633" x2="130" y2="140" stroke="black"/>
  <line x1="130" y1="140" x2="100" y2="160" stroke="black"/>
  <line x1="100" y1="160" x2="70" y2="140" stroke="black"/>
  <line x1="70" y1="140" x2="89.20491639222753" y2="114.3934448103633" stroke="black"/>
</g>
<!-- Edge: B -> B (B -> B) -->
<g class="edge" id="B -> B">
  <title>B->B</title>
  <line x1="224.7910310279769" y1="140.08358758880922" x2="250" y2="130" stroke="black"/>
  <line x1="250" y1="130" x2="270" y2="150" stroke="black"/>
  <line x1="270" y1="150" x2="250" y2="170" stroke="black"/>
  <line x1="250" y1="170" x2="224.7910310279769" y2="159.91641241119078" stroke="black"/>
</g>)";
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
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_LINE);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="116.09236051318196" y1="108.04618025659099" x2="165.64120389512738" y2="132.8206019475637" stroke="black"/>
  <polygon points="174.58547580512652,137.29273790256326 164.0759563108775,135.95109711606338 167.20645147937722,129.69010677906397 174.58547580512652,137.29273790256326" fill="black" stroke="black"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="126.56927303172192" y1="113.28463651586095" x2="176.1181164136673" y2="138.05905820683367" stroke="black"/>
  <polygon points="117.62500112172276,108.81250056086138 128.13452061597178,110.15414134736126 125.00402544747207,116.41513168436066 117.62500112172276,108.81250056086138" fill="black" stroke="black"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="126.56927303172192" y1="113.28463651586095" x2="165.64120389512738" y2="132.8206019475637" stroke="black"/>
  <polygon points="117.62500112172276,108.81250056086138 128.13452061597178,110.15414134736126 125.00402544747207,116.41513168436066 117.62500112172276,108.81250056086138" fill="black" stroke="black"/>
  <polygon points="174.58547580512652,137.29273790256326 164.0759563108775,135.95109711606338 167.20645147937722,129.69010677906397 174.58547580512652,137.29273790256326" fill="black" stroke="black"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="82.16601989629028" y1="102.37786401382796" x2="-50" y2="120" stroke="black"/>
  <line x1="-50" y1="120" x2="161.85932941877" y2="145.42311953025242" stroke="black"/>
  <polygon points="171.7880978036392,146.61457173643672 161.44232114660548,148.89818846495663 162.2763376909345,141.94805059554818 171.7880978036392,146.61457173643672" fill="black" stroke="black"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="70.5552279772989" y1="103.92596960302681" x2="-50" y2="120" stroke="black"/>
  <line x1="-50" y1="120" x2="173.48943624376807" y2="146.81873234925217" stroke="black"/>
  <polygon points="80.46750698412525,102.60433240211664 71.01780099761747,107.39526725541604 70.09265495698034,100.4566719506376 80.46750698412525,102.60433240211664" fill="black" stroke="black"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="70.5552279772989" y1="103.92596960302681" x2="-50" y2="120" stroke="black"/>
  <line x1="-50" y1="120" x2="161.85932941877" y2="145.42311953025242" stroke="black"/>
  <polygon points="80.46750698412525,102.60433240211664 71.01780099761747,107.39526725541604 70.09265495698034,100.4566719506376 80.46750698412525,102.60433240211664" fill="black" stroke="black"/>
  <polygon points="171.7880978036392,146.61457173643672 161.44232114660548,148.89818846495663 162.2763376909345,141.94805059554818 171.7880978036392,146.61457173643672" fill="black" stroke="black"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    edge->setPrecomputedTextSize(20, 16);
    edge->setMargin(2.0);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1WithDebug() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="116.09236051318196" y1="108.04618025659099" x2="176.1181164136673" y2="138.05905820683367" stroke="black"/>
  <rect x="129.70523846342462" y="127.85261923171234" width="20" height="16" fill="none" stroke="blue"/>
  <rect x="127.70523846342462" y="125.85261923171234" width="24" height="20" fill="none" stroke="red"/>
  <text x="139.70523846342462" y="135.85261923171234" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">42</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    edge->setPrecomputedTextSize(20, 16);
    edge->setMargin(2.0);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1WithDebug() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="82.16601989629028" y1="102.37786401382796" x2="-50" y2="120" stroke="black"/>
  <line x1="-50" y1="120" x2="173.48943624376807" y2="146.81873234925217" stroke="black"/>
  <rect x="-15.801535228950762" y="128.74381577252592" width="20" height="16" fill="none" stroke="blue"/>
  <rect x="-17.801535228950762" y="126.74381577252592" width="24" height="20" fill="none" stroke="red"/>
  <text x="-5.801535228950761" y="136.74381577252592" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">42</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
