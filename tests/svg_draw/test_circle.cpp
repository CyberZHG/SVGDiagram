#include "svg_diagram.h"

#include <format>
#include <gtest/gtest.h>

#include "../test_utils.h"
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDrawCircle, OneCircleAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto circle = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    auto svg = circle->generateXMLElements()[0]->toString();
    compareSVGContent(svg, R"(<circle cx="0" cy="0" r="20"/>)" + string("\n"));
    diagram.addSVGDraw(std::move(circle));
    svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, OneCircleFixedSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    diagram.setCanvasSize(100, 100);
    auto circle = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    auto svg = circle->generateXMLElements()[0]->toString();
    compareSVGContent(svg, R"(<circle cx="0" cy="0" r="20"/>)" + string("\n"));
    diagram.addSVGDraw(std::move(circle));
    svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, TwoCirclesAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto circle1 = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    auto svg = circle1->generateXMLElements()[0]->toString();
    compareSVGContent(svg, R"(<circle cx="0" cy="0" r="20"/>)" + string("\n"));
    diagram.addSVGDraw(std::move(circle1));
    auto circle2 = make_unique<SVGDrawCircle>(50.0, 0.0, 20.0);
    svg = circle2->generateXMLElements()[0]->toString();
    compareSVGContent(svg, R"(<circle cx="50" cy="0" r="20"/>)" + string("\n"));
    diagram.addSVGDraw(std::move(circle2));
    svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, TwoCirclesFixedSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    diagram.setCanvasSize(100, 100);
    auto circle1 = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    auto svg = circle1->generateXMLElements()[0]->toString();
    compareSVGContent(svg, R"(<circle cx="0" cy="0" r="20"/>)" + string("\n"));
    diagram.addSVGDraw(std::move(circle1));
    auto circle2 = make_unique<SVGDrawCircle>(50.0, 0.0, 20.0);
    svg = circle2->generateXMLElements()[0]->toString();
    compareSVGContent(svg, R"(<circle cx="50" cy="0" r="20"/>)" + string("\n"));
    diagram.addSVGDraw(std::move(circle2));
    svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, OneCircleFillAndStroke) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    auto circle = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    circle->setAttribute(SVG_ATTR_KEY_STROKE, "blue");
    circle->setAttribute(SVG_ATTR_KEY_FILL, "none");
    auto svg = circle->generateXMLElements()[0]->toString();
    compareSVGContent(svg, R"(<circle cx="0" cy="0" r="20" fill="none" stroke="blue"/>)" + string("\n"));
    diagram.addSVGDraw(std::move(circle));
    svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
