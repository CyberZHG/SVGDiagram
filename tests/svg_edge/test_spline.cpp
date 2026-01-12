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
  <path d="M 81.96777431615375 102.40429675784617 C 59.97314526346146 105.33691396487181 -65.22051442665283 112.60156557545295 -50 120 C -34.77948557334717 127.39843442454705 136.07571739672557 142.32908608760707 173.2908608760707 146.79490330512849" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionDashed) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->appendStyleDashed();
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 81.96777431615375 102.40429675784617 C 59.97314526346146 105.33691396487181 -65.22051442665283 112.60156557545295 -50 120 C -34.77948557334717 127.39843442454705 136.07571739672557 142.32908608760707 173.2908608760707 146.79490330512849" fill="none" stroke="black" stroke-dasharray="5,2"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionDotted) {
    SVGDiagram diagram;
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_shared<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->appendStyleDotted();
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 81.96777431615375 102.40429675784617 C 59.97314526346146 105.33691396487181 -65.22051442665283 112.60156557545295 -50 120 C -34.77948557334717 127.39843442454705 136.07571739672557 142.32908608760707 173.2908608760707 146.79490330512849" fill="none" stroke="black" stroke-dasharray="1,5"/>
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
  <path d="M 110.91508360777247 114.5534448103633 C 114.09590300647706 118.79453734196942 131.81918060129541 132.42557413506054 130 140 C 128.18081939870459 147.57442586493946 110 160 100 160 C 90 160 71.81918060129541 147.57442586493946 70 140 C 68.18081939870459 132.42557413506054 85.90409699352294 118.79453734196942 89.08491639222753 114.5534448103633" fill="none" stroke="black"/>
</g>
<!-- Edge: B -> B (B -> B) -->
<g class="edge" id="B -> B">
  <title>B->B</title>
  <path d="M 224.97672636615397 140.0093094535384 C 229.14727197179496 138.341091211282 242.49612106102566 128.33488490892307 250 130 C 257.50387893897437 131.66511509107693 270 143.33333333333334 270 150 C 270 156.66666666666666 257.50387893897437 168.33488490892307 250 170 C 242.49612106102566 171.66511509107693 229.14727197179496 161.658908788718 224.97672636615397 159.9906905464616" fill="none" stroke="black"/>
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
  <path d="M 81.96777431615375 102.40429675784617 C 59.97314526346146 105.33691396487181 -65.22051442665283 112.60156557545295 -50 120 C -35.9971267274794 126.80655967058328 109.73494692819183 139.98838801184394 161.94144596979942 145.53139684203126" fill="none" stroke="black"/>
  <polygon points="171.7866096472173,146.6274381833161 161.46075378140225,148.99950492740516 162.23526421905245,142.04248447451218 171.7866096472173,146.6274381833161" fill="black" stroke="black"/>
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
  <path d="M 70.52795981389337 103.59317007658065 C 32.817629342270166 107.02411332007136 -63.4549347531611 113.4597839687004 -50 120 C -34.77948557334717 127.39843442454705 136.07571739672557 142.32908608760707 173.2908608760707 146.79490330512849" fill="none" stroke="black"/>
  <polygon points="80.46233772509785,102.56074801811785 70.87769156192687,107.07567414451367 70.15411919800688,100.11317150292199 80.46233772509785,102.56074801811785" fill="black" stroke="black"/>
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
  <path d="M 70.52795981389337 103.59317007658065 C 32.817629342270166 107.02411332007136 -63.4549347531611 113.4597839687004 -50 120 C -35.9971267274794 126.80655967058328 109.73494692819183 139.98838801184394 161.94144596979942 145.53139684203126" fill="none" stroke="black"/>
  <polygon points="80.46233772509785,102.56074801811785 70.87769156192687,107.07567414451367 70.15411919800688,100.11317150292199 80.46233772509785,102.56074801811785" fill="black" stroke="black"/>
  <polygon points="171.7866096472173,146.6274381833161 161.46075378140225,148.99950492740516 162.23526421905245,142.04248447451218 171.7866096472173,146.6274381833161" fill="black" stroke="black"/>
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
    edge->setTailLabel("tail");
    edge->setHeadLabel("head");
    edge->setPrecomputedTextSize(20, 16);
    edge->setPrecomputedTextSize("tail", 40, 16);
    edge->setPrecomputedTextSize("head", 40, 16);
    edge->setLabelDistance(3);
    edge->setMargin(2.0);
    diagram.addEdge(edge);
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2WithDebug() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="81.96777431615375" y1="102.40429675784617" x2="59.97314526346146" y2="105.33691396487181" stroke="blue"/>
  <line x1="-65.22051442665283" y1="112.60156557545295" x2="-50" y2="120" stroke="blue"/>
  <line x1="-50" y1="120" x2="-34.77948557334717" y2="127.39843442454705" stroke="blue"/>
  <line x1="136.07571739672557" y1="142.32908608760707" x2="173.2908608760707" y2="146.79490330512849" stroke="blue"/>
  <path d="M 81.96777431615375 102.40429675784617 C 59.97314526346146 105.33691396487181 -65.22051442665283 112.60156557545295 -50 120 C -34.77948557334717 127.39843442454705 136.07571739672557 142.32908608760707 173.2908608760707 146.79490330512849" fill="none" stroke="black"/>
  <rect x="-17.20122102712405" y="131.0871692690356" width="20" height="16" fill="none" stroke="blue"/>
  <rect x="-19.20122102712405" y="129.0871692690356" width="24" height="20" fill="none" stroke="red"/>
  <text x="-7.201221027124049" y="139.0871692690356" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">42</text>
  <rect x="31.550302829854928" y="85.38918908533613" width="40" height="16" fill="none" stroke="blue"/>
  <rect x="29.550302829854928" y="83.38918908533613" width="44" height="20" fill="none" stroke="red"/>
  <text x="51.55030282985493" y="93.38918908533613" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">tail</text>
  <rect x="121.80512369814704" y="147.68114655756878" width="40" height="16" fill="none" stroke="blue"/>
  <rect x="119.80512369814704" y="145.68114655756878" width="44" height="20" fill="none" stroke="red"/>
  <text x="141.80512369814704" y="155.68114655756878" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">head</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
