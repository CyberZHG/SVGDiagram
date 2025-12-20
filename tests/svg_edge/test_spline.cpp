#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

void TestSVGEdgeSplineAddTwoNodesCase1(SVGDiagram& diagram) {
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

string TestSVGEdgeSplineExpectedNodesSVGCase2() {
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

TEST(TestSVGEdgeSpline, TwoCircleOneLine) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="116.09236051318196" y1="108.04618025659099" x2="176.1181164136673" y2="138.05905820683367" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnection) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 82.16601989629028 102.37786401382796 C 60.13834991357524 105.31488667818996 -65.2205693912463 112.59318861076264 -50 120 C -34.7794306087537 127.40681138923736 136.2411968698067 142.3489436243768 173.48943624376807 146.81873234925217" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleTwoLineSelfCycle) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge1 = std::make_shared<SVGEdge>("A", "A");
    edge1->setSplines(SVGEdge::SPLINES_SPLINE);
    edge1->addConnectionPoint(130, 140);
    edge1->addConnectionPoint(100, 160);
    edge1->addConnectionPoint(70, 140);
    diagram.addEdge(edge1);
    auto edge2 = std::make_shared<SVGEdge>("B", "B");
    edge2->setSplines(SVGEdge::SPLINES_SPLINE);
    edge2->addConnectionPoint(250, 130);
    edge2->addConnectionPoint(270, 150);
    edge2->addConnectionPoint(250, 170);
    diagram.addEdge("B -> B", edge2);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"(<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A->A</title>
  <path d="M 110.79508360777247 114.3934448103633 C 113.99590300647705 118.66120400863609 131.7991806012954 132.39890746839387 130 140 C 128.2008193987046 147.60109253160613 110 160 100 160 C 90 160 71.7991806012954 147.60109253160613 70 140 C 68.2008193987046 132.39890746839387 86.00409699352295 118.66120400863609 89.20491639222753 114.3934448103633" fill="none" stroke="black"/>
</g>
<!-- Edge: B -> B (B -> B) -->
<g class="edge" id="B -> B">
  <title>B->B</title>
  <path d="M 224.7910310279769 140.08358758880922 C 228.99252585664743 138.402989657341 242.46517183799614 128.34726459813487 250 130 C 257.53482816200386 131.65273540186513 270 143.33333333333334 270 150 C 270 156.66666666666666 257.53482816200386 168.34726459813487 250 170 C 242.46517183799614 171.65273540186513 228.99252585664743 161.597010342659 224.7910310279769 159.91641241119078" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

string TestSVGEdgeSplineExpectedArrowNormalSVG() {
    return R"(  <defs>
    <marker id="arrow_type_normal__fill_black__stroke_none" markerWidth="10" markerHeight="7" refX="10" refY="3.5" orient="auto-start-reverse">
      <polygon points="0 0 10 3.5 0 7" fill="black" stroke="none" />
    </marker>
  </defs>
)";
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineArrowHead) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
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

TEST(TestSVGEdgeSpline, TwoCircleOneLineArrowTail) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
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

TEST(TestSVGEdgeSpline, TwoCircleOneLineArrowBoth) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
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

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionArrowHead) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 82.16601989629028 102.37786401382796 C 60.13834991357524 105.31488667818996 -63.28221825374662 112.82579074726259 -50 120 C -36.71778174625338 127.17420925273741 126.54944118230833 141.185932941877 161.85932941877 145.42311953025242" fill="none" stroke="black"/>
  <polygon points="171.7880978036392,146.61457173643672 161.44232114660548,148.89818846495663 162.2763376909345,141.94805059554818 171.7880978036392,146.61457173643672" fill="black" stroke="black"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionArrowTail) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 70.5552279772989 103.92596960302681 C 50.46268998108242 106.604974669189 -67.15570137774486 112.85120620896244 -50 120 C -32.84429862225514 127.14879379103756 136.2411968698067 142.3489436243768 173.48943624376807 146.81873234925217" fill="none" stroke="black"/>
  <polygon points="80.46750698412525,102.60433240211664 71.01780099761747,107.39526725541604 70.09265495698034,100.4566719506376 80.46750698412525,102.60433240211664" fill="black" stroke="black"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionArrowBoth) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_NORMAL);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 70.5552279772989 103.92596960302681 C 50.46268998108242 106.604974669189 -65.21735024024518 113.0838083454624 -50 120 C -34.78264975975482 126.9161916545376 126.54944118230833 141.185932941877 161.85932941877 145.42311953025242" fill="none" stroke="black"/>
  <polygon points="80.46750698412525,102.60433240211664 71.01780099761747,107.39526725541604 70.09265495698034,100.4566719506376 80.46750698412525,102.60433240211664" fill="black" stroke="black"/>
  <polygon points="171.7880978036392,146.61457173643672 161.44232114660548,148.89818846495663 162.2763376909345,141.94805059554818 171.7880978036392,146.61457173643672" fill="black" stroke="black"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

string TestSVGEdgeSplineExpectedNodesSVGCase2WithDebug() {
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

TEST(TestSVGEdgeSpline, TwoCircleOneLineWithLabel) {
    SVGDiagram diagram;
    diagram.enableDebug();
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->setLabel("42");
    edge->setPrecomputedTextSize(20, 16);
    edge->setMargin(2.0);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2WithDebug() +
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

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionWithLabel) {
    SVGDiagram diagram;
    diagram.enableDebug();
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->setLabel("42");
    edge->setPrecomputedTextSize(20, 16);
    edge->setMargin(2.0);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2WithDebug() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 82.16601989629028 102.37786401382796 C 60.13834991357524 105.31488667818996 -65.2205693912463 112.59318861076264 -50 120 C -34.7794306087537 127.40681138923736 136.2411968698067 142.3489436243768 173.48943624376807 146.81873234925217" fill="none" stroke="black"/>
  <rect x="-17.167825519552075" y="131.09488273820648" width="20" height="16" fill="none" stroke="blue"/>
  <rect x="-19.167825519552075" y="129.09488273820648" width="24" height="20" fill="none" stroke="red"/>
  <text x="-7.167825519552074" y="139.09488273820648" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">42</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
