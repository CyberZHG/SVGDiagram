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
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopRightArrowTail) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToRight("A", 30, 30);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopRightArrowHead) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToRight("A", 30, 30);
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopTop) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToTop("A", 30, 30);
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopBottom) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToBottom("A", 30, 30);
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGEdgeSelfLoop, SelfLoopLeft) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setFixedSize(100, 80);
    const auto edge = diagram.addSelfLoopToLeft("A", 30, 30);
    edge->setArrowHead(SVGEdge::ARROW_EMPTY);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
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
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
