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
    const auto edge = diagram.addSelfLoopToRight("A", 30, 30);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A-&gt;A</title>
  <path d="M 47.89734216109488 12.83405415166254 C 64.77234216109488 24.084054151662542 80.5 11.25 80.5 0 C 80.5 -11.25 64.77234216109488 -24.084054151662542 47.89734216109488 -12.83405415166254" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopRightArrowTail) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToRight("A", 30, 30);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A-&gt;A</title>
  <path d="M 58.61895784144792 17.02376994017529 C 70.88215976772139 18.563687131041288 80.5 8.7975 80.5 0 C 80.5 -11.25 64.77234216109488 -24.084054151662542 47.89734216109488 -12.83405415166254" fill="none" stroke="black"/>
  <polygon points="49.30707348952683,13.384938811249395 59.89507522042202,13.764701034963636 57.34728548263201,20.284575838363764 49.30707348952683,13.384938811249395" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopRightArrowHead) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToRight("A", 30, 30);
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A-&gt;A</title>
  <path d="M 47.89734216109488 12.83405415166254 C 64.77234216109488 24.084054151662542 80.5 11.25 80.5 0 C 80.5 -8.7975 70.88215976772138 -18.563687131041288 58.61895784144791 -17.023769940175285" fill="none" stroke="black"/>
  <polygon points="49.30707348952683,-13.384938811249395 57.34728548263201,-20.284575838363764 59.89507522042202,-13.764701034963636 49.30707348952683,-13.384938811249395" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopTop) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToTop("A", 30, 30);
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A-&gt;A</title>
  <path d="M 10.609740180641019 -39.59608940925728 C 21.85974018064102 -56.47108940925728 11.250000000000004 -70.5 4.3168799669944195e-15 -70.5 C -8.774999999999995 -70.5 -17.160465925901992 -61.96481079659213 -15.086650933298866 -50.20126254709266" fill="none" stroke="black"/>
  <polygon points="-11.19837407695433,-40.99048048160449 -18.311947010992483,-48.842045937748885 -11.86301944917474,-51.56442234493938 -11.19837407695433,-40.99048048160449" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopBottom) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToBottom("A", 30, 30);
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A-&gt;A</title>
  <path d="M -10.609740180641014 39.59608940925728 C -21.859740180641012 56.47108940925728 -11.249999999999996 70.5 4.3168799669944195e-15 70.5 C 8.775000000000006 70.5 17.160465925902 61.96481079659213 15.086650933298873 50.20126254709266" fill="none" stroke="black"/>
  <polygon points="11.198374076954336,40.9904804816045 18.311947010992487,48.842045937748885 11.863019449174741,51.56442234493939 11.198374076954336,40.9904804816045" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopLeft) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToLeft("A", 30, 30);
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A-&gt;A</title>
  <path d="M -47.89734216109488 -12.834054151662555 C -64.77234216109488 -24.084054151662556 -80.5 -11.25000000000001 -80.5 -9.858406733136192e-15 C -80.5 8.79749999999999 -70.88215976772138 18.563687131041284 -58.61895784144791 17.023769940175285" fill="none" stroke="black"/>
  <polygon points="-49.30707348952683,13.384938811249395 -57.34728548263201,20.28457583836376 -59.89507522042202,13.764701034963629 -49.30707348952683,13.384938811249395" fill="none" stroke="black"/>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopRightLabel) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToRight("A", 30, 30);
    edge->setArrowHead();
    edge->setLabel("center");
    edge->setTailLabel("tail");
    edge->setHeadLabel("head");
    edge->setPrecomputedTextSize("center", 40, 16);
    edge->setPrecomputedTextSize("tail", 40, 16);
    edge->setPrecomputedTextSize("head", 40, 16);
    const auto svg = diagram.render();
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <ellipse cx="0" cy="0" rx="50" ry="40" fill="none" stroke="black"/>
</g>
<!-- Edge: edge1 (A -> A) -->
<g class="edge" id="edge1">
  <title>A-&gt;A</title>
  <path d="M 47.89734216109488 12.83405415166254 C 64.77234216109488 24.084054151662542 80.5 11.25 80.5 0 C 80.5 -8.7975 70.88215976772138 -18.563687131041288 58.61895784144791 -17.023769940175285" fill="none" stroke="black"/>
  <polygon points="49.30707348952683,-13.384938811249395 57.34728548263201,-20.284575838363764 59.89507522042202,-13.764701034963636 49.30707348952683,-13.384938811249395" fill="black" stroke="black"/>
  <text x="100.60635246078508" y="-0.4489418057759338" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">center</text>
  <text x="54.720495567088804" y="28.331036296302486" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">tail</text>
  <text x="54.72049556708881" y="-28.33103629630249" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">head</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
