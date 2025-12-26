#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGEdgeSelfLoop, SelfLoopRight) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoop("A", 0.0, 30, 30);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A->A</title>
  <path d="M 47.89734216109488 -12.83405415166254 C 64.77234216109488 -24.084054151662542 80.5 -11.25 80.5 0 C 80.5 11.25 64.77234216109488 24.084054151662542 47.89734216109488 12.83405415166254" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopRightArrowTail) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoop("A", 0.0, 30, 30);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A->A</title>
  <path d="M 58.61895784144792 -17.02376994017529 C 70.88215976772139 -18.563687131041288 80.5 -8.7975 80.5 0 C 80.5 11.25 64.77234216109488 24.084054151662542 47.89734216109488 12.83405415166254" fill="none" stroke="black"/>
  <polygon points="49.30707348952683,-13.384938811249395 57.34728548263201,-20.284575838363764 59.89507522042202,-13.764701034963636 49.30707348952683,-13.384938811249395" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopRightArrowHead) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoop("A", 0.0, 30, 30);
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A->A</title>
  <path d="M 47.89734216109488 -12.83405415166254 C 64.77234216109488 -24.084054151662542 80.5 -11.25 80.5 0 C 80.5 8.7975 70.88215976772138 18.563687131041288 58.61895784144791 17.023769940175285" fill="none" stroke="black"/>
  <polygon points="49.30707348952683,13.384938811249395 59.89507522042202,13.764701034963636 57.34728548263201,20.284575838363764 49.30707348952683,13.384938811249395" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopTop) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoop("A", 90, 20, 30);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A->A</title>
  <path d="M -10.609740180641014 -39.59608940925728 C -18.109740180641012 -50.84608940925728 -7.4999999999999964 -60.5 3.704556567420743e-15 -60.5 C 7.5000000000000036 -60.5 18.10974018064102 -50.84608940925728 10.609740180641019 -39.59608940925728" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}