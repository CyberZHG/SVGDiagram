#include "svg_diagram.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

#ifndef SVG_DIAGRAM_ENABLE_PANGO_CAIRO
TEST(TestSVGDrawText, OneLineTextAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto text = make_unique<SVGDrawText>(0.0, 0.0, "Hello world!");
    auto svg = text->render();
    EXPECT_EQ(svg, R"(<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >Hello world!</text>)" + string("\n"));
    diagram.addSVGDraw(std::move(text));
    svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="144" height="37.33333333333333" viewBox="-72 -18.666666666666664 144 37.33333333333333">
  <rect x="-72" y="-18.666666666666664" width="144" height="37.33333333333333" fill="white" />
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >Hello world!</text>
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawText, TwoLinesAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto text = make_unique<SVGDrawText>(0.0, 0.0, "Hello world!\n世界你好！");
    auto svg = text->render();
    auto expected = R"(<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >
  <tspan x="0" dy="-0.6em">Hello world!</tspan>
  <tspan x="0" dy="1.2em">世界你好！</tspan>
</text>
)";
    EXPECT_EQ(svg, expected);
    diagram.addSVGDraw(std::move(text));
    svg = diagram.render();
    expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="176" height="62.93333333333334" viewBox="-88 -31.46666666666667 176 62.93333333333334">
  <rect x="-88" y="-31.46666666666667" width="176" height="62.93333333333334" fill="white" />
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >
    <tspan x="0" dy="-0.6em">Hello world!</tspan>
    <tspan x="0" dy="1.2em">世界你好！</tspan>
  </text>
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawText, ThreeLinesAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto text = make_unique<SVGDrawText>(0.0, 0.0, "Hello world!\n世界你好！\r\nSalve, mundus!");
    auto svg = text->render();
    auto expected = R"(<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >
  <tspan x="0" dy="-1.2em">Hello world!</tspan>
  <tspan x="0" dy="1.2em">世界你好！</tspan>
  <tspan x="0" dy="1.2em">Salve, mundus!</tspan>
</text>
)";
    EXPECT_EQ(svg, expected);
    diagram.addSVGDraw(std::move(text));
    svg = diagram.render();
    expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="176" height="88.53333333333333" viewBox="-88 -44.266666666666666 176 88.53333333333333">
  <rect x="-88" y="-44.266666666666666" width="176" height="88.53333333333333" fill="white" />
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >
    <tspan x="0" dy="-1.2em">Hello world!</tspan>
    <tspan x="0" dy="1.2em">世界你好！</tspan>
    <tspan x="0" dy="1.2em">Salve, mundus!</tspan>
  </text>
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
#endif
