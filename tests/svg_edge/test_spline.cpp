#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

void TestSVGEdgeSplineAddTwoNodesCase1(SVGDiagram& diagram) {
    auto node1 = std::make_unique<SVGNode>(100, 100);
    node1->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node1->setMarginInPoints(8, 4);
    node1->setPrecomputedTextSize(10, 16);
    node1->setLabel("A");
    diagram.addNode("A", std::move(node1));
    auto node2 = std::make_unique<SVGNode>(200, 150);
    node2->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    node2->setMarginInPoints(16, 8);
    node2->setPrecomputedTextSize(10, 16);
    node2->setLabel("B");
    diagram.addNode("B", std::move(node2));
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
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="115.98055711430698" y1="107.99027855715349" x2="176.2299198125423" y2="138.11495990627114" stroke="black" stroke-width="1"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
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
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 82.2899233838756 102.36134354881658 C 60.24160281989634 105.30111962401381 -65.22060374411723 112.58795300783119 -50 120 C -34.77939625588278 127.41204699216881 136.34462154048242 142.36135458485788 173.61354584857892 146.83362550182946" fill="none" stroke="black" stroke-width="1"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
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
        R"(<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A->A</title>
  <path d="M 110.72008360777248 114.29344481036331 C 113.93340300647706 118.57787067530276 131.78668060129542 132.38224080172722 130 140 C 128.21331939870458 147.61775919827278 110 160 100 160 C 90 160 71.78668060129542 147.61775919827278 70 140 C 68.21331939870458 132.38224080172722 86.06659699352295 118.57787067530276 89.27991639222753 114.29344481036331" fill="none" stroke="black" stroke-width="1"/>
</g>
<!-- Edge: B -> B (B -> B) -->
<g class="edge" id="B -> B">
  <title>B->B</title>
  <path d="M 224.67497144161626 140.1300114233535 C 228.8958095346802 138.44167618612792 242.4458285736027 128.35500190389226 250 130 C 257.55417142639726 131.64499809610774 270 143.33333333333334 270 150 C 270 156.66666666666666 257.55417142639726 168.35500190389226 250 170 C 242.4458285736027 171.64499809610774 228.8958095346802 161.55832381387208 224.67497144161626 159.8699885766465" fill="none" stroke="black" stroke-width="1"/>
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
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="115.98055711430698" y1="107.99027855715349" x2="165.30175557055543" y2="132.6508777852777" stroke="black" stroke-width="1"/>
  <polygon points="174.24602748055457,137.12301374027726 163.73650798630555,135.78137295377738 166.86700315480527,129.52038261677797 174.24602748055457,137.12301374027726" fill="black" stroke="black" stroke-width="1"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="126.90872135629387" y1="113.45436067814693" x2="176.2299198125423" y2="138.11495990627114" stroke="black" stroke-width="1"/>
  <polygon points="117.96444944629471,108.98222472314735 128.47396894054373,110.32386550964723 125.34347377204402,116.58485584664663 117.96444944629471,108.98222472314735" fill="black" stroke="black" stroke-width="1"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="126.90872135629387" y1="113.45436067814693" x2="165.30175557055543" y2="132.6508777852777" stroke="black" stroke-width="1"/>
  <polygon points="117.96444944629471,108.98222472314735 128.47396894054373,110.32386550964723 125.34347377204402,116.58485584664663 117.96444944629471,108.98222472314735" fill="black" stroke="black" stroke-width="1"/>
  <polygon points="174.24602748055457,137.12301374027726 163.73650798630555,135.78137295377738 166.86700315480527,129.52038261677797 174.24602748055457,137.12301374027726" fill="black" stroke="black" stroke-width="1"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 82.2899233838756 102.36134354881658 C 60.24160281989634 105.30111962401381 -63.198765769260234 112.83057356481402 -50 120 C -36.801234230739766 127.16942643518598 126.23543166619748 141.1482517999437 161.482517999437 145.37790215993243" fill="none" stroke="black" stroke-width="1"/>
  <polygon points="171.4112863843062,146.56935436611673 161.06550972727248,148.85297109463664 161.8995262716015,141.9028332252282 171.4112863843062,146.56935436611673" fill="black" stroke="black" stroke-width="1"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 70.17904235420805 103.97612768610558 C 50.14920196184004 106.64677307175465 -67.23908391572849 112.85708369737935 -50 120 C -32.76091608427152 127.14291630262065 136.34462154048242 142.36135458485788 173.61354584857892 146.83362550182946" fill="none" stroke="black" stroke-width="1"/>
  <polygon points="80.0913213610344,102.65449048519541 70.64161537452662,107.44542533849481 69.71646933388949,100.50683003371637 80.0913213610344,102.65449048519541" fill="black" stroke="black" stroke-width="1"/>
</g>)s";
    compareSVGWithDefaultGraphContent(svg, expected);
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
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2() +
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 70.17904235420805 103.97612768610558 C 50.14920196184004 106.64677307175465 -65.21724594087149 113.0997042543622 -50 120 C -34.78275405912851 126.9002957456378 126.23543166619748 141.1482517999437 161.482517999437 145.37790215993243" fill="none" stroke="black" stroke-width="1"/>
  <polygon points="80.0913213610344,102.65449048519541 70.64161537452662,107.44542533849481 69.71646933388949,100.50683003371637 80.0913213610344,102.65449048519541" fill="black" stroke="black" stroke-width="1"/>
  <polygon points="171.4112863843062,146.56935436611673 161.06550972727248,148.85297109463664 161.8995262716015,141.9028332252282 171.4112863843062,146.56935436611673" fill="black" stroke="black" stroke-width="1"/>
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
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->setLabel("42");
    edge->setPrecomputedTextSize(20, 16);
    edge->setMarginInPoints(2.0);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2WithDebug() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="115.98055711430698" y1="107.99027855715349" x2="176.2299198125423" y2="138.11495990627114" stroke="black" stroke-width="1"/>
  <rect x="129.70523846342465" y="127.85261923171231" width="20" height="16" fill="none" stroke="blue"/>
  <rect x="127.70523846342465" y="125.85261923171231" width="24" height="20" fill="none" stroke="red"/>
  <text x="139.70523846342465" y="135.8526192317123" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">42</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSpline, TwoCircleOneLineOneConnectionWithLabel) {
    SVGDiagram diagram;
    diagram.enableDebug();
    TestSVGEdgeSplineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_SPLINE);
    edge->addConnectionPoint(-50, 120);
    edge->setLabel("42");
    edge->setPrecomputedTextSize(20, 16);
    edge->setMarginInPoints(2.0);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeSplineExpectedNodesSVGCase2WithDebug() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <path d="M 82.2899233838756 102.36134354881658 C 60.24160281989634 105.30111962401381 -65.22060374411723 112.58795300783119 -50 120 C -34.77939625588278 127.41204699216881 136.34462154048242 142.36135458485788 173.61354584857892 146.83362550182946" fill="none" stroke="black" stroke-width="1"/>
  <rect x="-17.146953277543147" y="131.09970362028665" width="20" height="16" fill="none" stroke="blue"/>
  <rect x="-19.146953277543147" y="129.09970362028665" width="24" height="20" fill="none" stroke="red"/>
  <text x="-7.146953277543149" y="139.09970362028665" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">42</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
