#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodeCircle, OneCircleAutoSizeNoText) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::SHAPE_CIRCLE);
    node->setMargin(8, 4);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeText2) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::SHAPE_CIRCLE);
    node->setMargin(8, 4);
    node->setLabel("2");
    node->setPrecomputedTextSize(10, 16);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeText42) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::SHAPE_CIRCLE);
    node->setMargin(8, 4);
    node->setLabel("42");
    node->setPrecomputedTextSize(20, 16);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeTextA) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::SHAPE_CIRCLE);
    node->setMargin(8, 4);
    node->setLabel("A");
    node->setPrecomputedTextSize(15, 16);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodeCircle, OneCircleAutoSizeTextTwoLines) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto node = std::make_shared<SVGNode>();
    node->setShape(SVGNode::SHAPE_CIRCLE);
    node->setMargin(8, 4);
    node->setLabel("天朗气清\n惠风和畅");
    node->setPrecomputedTextSize(80, 35);
    diagram.addNode("circle", node);
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
