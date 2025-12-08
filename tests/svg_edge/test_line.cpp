#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

void TestSVGEdgeLineAddTwoNodesCase1(SVGDiagram& diagram) {
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
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="115.98055711430698" y1="107.99027855715349" x2="176.2299198125423" y2="138.11495990627114" stroke="black" stroke-width="1"/>
</g>)";
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
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="82.2899233838756" y1="102.36134354881658" x2="-50" y2="120" stroke="black" stroke-width="1"/>
  <line x1="-50" y1="120" x2="173.61354584857892" y2="146.83362550182946" stroke="black" stroke-width="1"/>
</g>)";
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
        R"(<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A->A</title>
  <line x1="110.72008360777248" y1="114.29344481036331" x2="130" y2="140" stroke="black" stroke-width="1"/>
  <line x1="130" y1="140" x2="100" y2="160" stroke="black" stroke-width="1"/>
  <line x1="100" y1="160" x2="70" y2="140" stroke="black" stroke-width="1"/>
  <line x1="70" y1="140" x2="89.27991639222753" y2="114.29344481036331" stroke="black" stroke-width="1"/>
</g>
<!-- Edge: B -> B (B -> B) -->
<g class="edge" id="B -> B">
  <title>B->B</title>
  <line x1="224.67497144161626" y1="140.1300114233535" x2="250" y2="130" stroke="black" stroke-width="1"/>
  <line x1="250" y1="130" x2="270" y2="150" stroke="black" stroke-width="1"/>
  <line x1="270" y1="150" x2="250" y2="170" stroke="black" stroke-width="1"/>
  <line x1="250" y1="170" x2="224.67497144161626" y2="159.8699885766465" stroke="black" stroke-width="1"/>
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
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
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

TEST(TestSVGEdgeLine, TwoCircleOneLineArrowTail) {
    SVGDiagram diagram;
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_NORMAL);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1() +
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
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="82.2899233838756" y1="102.36134354881658" x2="-50" y2="120" stroke="black" stroke-width="1"/>
  <line x1="-50" y1="120" x2="161.482517999437" y2="145.37790215993243" stroke="black" stroke-width="1"/>
  <polygon points="171.4112863843062,146.56935436611673 161.06550972727248,148.85297109463664 161.8995262716015,141.9028332252282 171.4112863843062,146.56935436611673" fill="black" stroke="black" stroke-width="1"/>
</g>)s";
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
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="70.17904235420805" y1="103.97612768610558" x2="-50" y2="120" stroke="black" stroke-width="1"/>
  <line x1="-50" y1="120" x2="173.61354584857892" y2="146.83362550182946" stroke="black" stroke-width="1"/>
  <polygon points="80.0913213610344,102.65449048519541 70.64161537452662,107.44542533849481 69.71646933388949,100.50683003371637 80.0913213610344,102.65449048519541" fill="black" stroke="black" stroke-width="1"/>
</g>)s";
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
        R"s(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="70.17904235420805" y1="103.97612768610558" x2="-50" y2="120" stroke="black" stroke-width="1"/>
  <line x1="-50" y1="120" x2="161.482517999437" y2="145.37790215993243" stroke="black" stroke-width="1"/>
  <polygon points="80.0913213610344,102.65449048519541 70.64161537452662,107.44542533849481 69.71646933388949,100.50683003371637 80.0913213610344,102.65449048519541" fill="black" stroke="black" stroke-width="1"/>
  <polygon points="171.4112863843062,146.56935436611673 161.06550972727248,148.85297109463664 161.8995262716015,141.9028332252282 171.4112863843062,146.56935436611673" fill="black" stroke="black" stroke-width="1"/>
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
    auto edge = std::make_unique<SVGEdge>("A", "B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->setLabel("42");
    edge->setPrecomputedTextSize(20, 16);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1WithDebug() +
        R"(<!-- Edge: edge1 (A -> B) -->
    <g class="edge" id="edge1">
      <title>A->B</title>
      <line x1="115.98055711430698" y1="107.99027855715349" x2="176.2299198125423" y2="138.11495990627114" stroke="black" stroke-width="1"/>
      <rect x="130.90523846342467" y="125.4526192317123" width="20" height="16" fill="none" stroke="blue"/>
      <rect x="130.90523846342467" y="125.4526192317123" width="20" height="16" fill="none" stroke="red"/>
      <text x="140.90523846342467" y="133.4526192317123" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">42</text>
    </g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeLine, TwoCircleOneLineOneConnectionWithLabel) {
    SVGDiagram diagram;
    diagram.enableDebug();
    TestSVGEdgeLineAddTwoNodesCase1(diagram);
    auto edge = std::make_unique<SVGEdge>();
    edge->setNodeFrom("A");
    edge->setNodeTo("B");
    edge->setSplines(SVGEdge::EDGE_SPLINES_LINE);
    edge->addConnectionPoint(-50, 120);
    edge->setLabel("42");
    edge->setPrecomputedTextSize(20, 16);
    diagram.addEdge(std::move(edge));
    const auto svg = diagram.render();
    const auto expected = TestSVGEdgeLineExpectedNodesSVGCase1WithDebug() +
        R"(<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="82.2899233838756" y1="102.36134354881658" x2="-50" y2="120" stroke="black" stroke-width="1"/>
  <line x1="-50" y1="120" x2="173.61354584857892" y2="146.83362550182946" stroke="black" stroke-width="1"/>
  <rect x="-15.536551001821415" y="126.53561387978141" width="20" height="16" fill="none" stroke="blue"/>
  <rect x="-15.536551001821415" y="126.53561387978141" width="20" height="16" fill="none" stroke="red"/>
  <text x="-5.536551001821415" y="134.5356138797814" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">42</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
