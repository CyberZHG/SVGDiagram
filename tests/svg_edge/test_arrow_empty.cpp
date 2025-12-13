#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGEdgeArrowEmpty, TwoRectsEmptyArrow) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setShape(SVGNode::NODE_SHAPE_RECT);
    node1->setFixedSize(10, 10);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(50, 100);
    node2->setShape(SVGNode::NODE_SHAPE_RECT);
    node2->setFixedSize(10, 10);
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_EMPTY);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_EMPTY);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-5" y="-5" width="10" height="10" fill="none" stroke="black"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="45" y="95" width="10" height="10" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="7.899013540169989" y1="15.798027080339974" x2="42.10098645983001" y2="84.20197291966002" stroke="black"/>
  <polygon points="3.4268775851704087,6.853755170340816 11.029508708669695,14.23277949609012 4.768518371670282,17.363274664589827 3.4268775851704087,6.853755170340816" fill="none" stroke="black"/>
  <polygon points="46.57312241482959,93.14624482965918 38.970491291330305,85.76722050390988 45.23148162832972,82.63672533541018 46.57312241482959,93.14624482965918" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeArrowEmpty, TwoRectsEmptyArrowPenWidth) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setShape(SVGNode::NODE_SHAPE_RECT);
    node1->setFixedSize(10, 10);
    node1->setPenWidth(2.0);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(50, 100);
    node2->setShape(SVGNode::NODE_SHAPE_RECT);
    node2->setFixedSize(10, 10);
    node2->setPenWidth(2.0);
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead(SVGEdge::ARROW_SHAPE_EMPTY);
    edge->setArrowTail(SVGEdge::ARROW_SHAPE_EMPTY);
    edge->setPenWidth(2.0);
    const auto svg = diagram.render();
  const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <rect x="-5" y="-5" width="10" height="10" fill="none" stroke="black" stroke-width="2"/>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <rect x="45" y="95" width="10" height="10" fill="none" stroke="black" stroke-width="2"/>
</g>
<!-- Edge: edge1 (A -> B) -->
<g class="edge" id="edge1">
  <title>A->B</title>
  <line x1="8.825891125340396" y1="17.65178225068079" x2="41.1741088746596" y2="82.3482177493192" stroke="black" stroke-width="2"/>
  <polygon points="4.353755170340817,8.707510340681631 11.956386293840103,16.086534666430936 5.695395956840691,19.217029834930642 4.353755170340817,8.707510340681631" fill="none" stroke="black" stroke-width="2"/>
  <polygon points="45.64624482965918,91.29248965931836 38.043613706159896,83.91346533356906 44.30460404315931,80.78297016506936 45.64624482965918,91.29248965931836" fill="none" stroke="black" stroke-width="2"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}