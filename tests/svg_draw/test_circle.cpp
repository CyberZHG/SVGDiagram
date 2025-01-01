#include "svg_diagram.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDrawCircle, OneCircleAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto circle = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    auto svg = circle->render();
    EXPECT_EQ(svg, R"(<circle cx="0" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle));
    svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="56" height="56" viewBox="-28 -28 56 56">
  <rect x="-28" y="-28" width="56" height="56" fill="white" />
  <circle cx="0" cy="0" r="20" />
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, OneCircleFixedSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    diagram.setCanvasSize(100, 100);
    auto circle = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    auto svg = circle->render();
    EXPECT_EQ(svg, R"(<circle cx="0" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle));
    svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="100" height="100" viewBox="-50 -50 100 100">
  <rect x="-50" y="-50" width="100" height="100" fill="white" />
  <circle cx="0" cy="0" r="20" />
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, TwoCirclesAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto circle1 = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    auto svg = circle1->render();
    EXPECT_EQ(svg, R"(<circle cx="0" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle1));
    auto circle2 = make_unique<SVGDrawCircle>(50.0, 0.0, 20.0);
    svg = circle2->render();
    EXPECT_EQ(svg, R"(<circle cx="50" cy="0" r="20" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle2));
    svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="106" height="56" viewBox="-28 -28 106 56">
  <rect x="-28" y="-28" width="106" height="56" fill="white" />
  <circle cx="0" cy="0" r="20" />
  <circle cx="50" cy="0" r="20" />
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, TwoCirclesFixedSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
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
    svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="100" height="100" viewBox="-25 -50 100 100">
  <rect x="-25" y="-50" width="100" height="100" fill="white" />
  <circle cx="0" cy="0" r="20" />
  <circle cx="50" cy="0" r="20" />
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawCircle, OneCircleFillAndStroke) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    auto circle = make_unique<SVGDrawCircle>(0.0, 0.0, 20.0);
    circle->setAttribute(SVG_ATTRIBUTE_STROKE, "blue");
    circle->setAttribute(SVG_ATTRIBUTE_FILL, "none");
    auto svg = circle->render();
    EXPECT_EQ(svg, R"(<circle cx="0" cy="0" r="20" fill="none" stroke="blue" />)" + string("\n"));
    diagram.addSVGDraw(std::move(circle));
    svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="56" height="56" viewBox="-28 -28 56 56">
  <circle cx="0" cy="0" r="20" fill="none" stroke="blue" />
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
