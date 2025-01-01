#include "svg_diagram.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDrawCircle, OneCircleAutoSize) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    auto circle = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    const auto svg = circle->render();
    EXPECT_EQ(svg, R"(<circle cx="0" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle));
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, OneCircleFixedSize) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    diagram.setCanvasSize(100, 100);
    auto circle = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    const auto svg = circle->render();
    EXPECT_EQ(svg, R"(<circle cx="0" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle));
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, TwoCirclesAutoSize) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    auto circle1 = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    auto svg = circle1->render();
    EXPECT_EQ(svg, R"(<circle cx="0" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle1));
    auto circle2 = make_unique<SVGDrawCircle>(50.0, 0.0, 20.0);
    svg = circle2->render();
    EXPECT_EQ(svg, R"(<circle cx="50" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle2));
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, TwoCirclesFixedSize) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    diagram.setCanvasSize(100, 100);
    auto circle1 = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    auto svg = circle1->render();
    EXPECT_EQ(svg, R"(<circle cx="0" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle1));
    auto circle2 = make_unique<SVGDrawCircle>(50.0, 0.0, 20.0);
    svg = circle2->render();
    EXPECT_EQ(svg, R"(<circle cx="50" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle2));
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
