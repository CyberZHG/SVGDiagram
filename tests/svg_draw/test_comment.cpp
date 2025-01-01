#include "svg_diagram.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDrawComment, DefaultComment) {
    const SVGDiagram diagram;
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
    const auto svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="-8 -8 16 16">
  <!-- Created by: https://github.com/CyberZHG/SVGDiagram -->
</svg>
)";
    EXPECT_EQ(svg, expected);
}

TEST(TestSVGDrawComment, EscapeComment) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    diagram.addSVGDraw(make_unique<SVGDrawComment>("A <!-- B --> C"));
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
    const auto svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="16" height="16" viewBox="-8 -8 16 16">
  <rect x="-8" y="-8" width="16" height="16" fill="white" />
  <!-- A <!‑‑ B ‑‑> C -->
</svg>
)";
    EXPECT_EQ(svg, expected);
}
