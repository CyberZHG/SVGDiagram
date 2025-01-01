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
    auto svg = text->generateXMLElements()[0]->toString();
    EXPECT_EQ(svg, R"(<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >Hello world!</text>)" + string("\n"));
    diagram.addSVGDraw(std::move(text));
    svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="112" height="32" viewBox="-56 -16 112 32">
  <rect x="-56" y="-16" width="112" height="32" fill="white" />
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
    auto svg = text->generateXMLElements()[0]->toString();
    auto expected = R"(<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16" >
  <tspan x="0" dy="-0.6em">Hello world!</tspan>
  <tspan x="0" dy="1.2em">世界你好！</tspan>
</text>
)";
    EXPECT_EQ(svg, expected);
    diagram.addSVGDraw(std::move(text));
    svg = diagram.render();
    expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="136" height="51.2" viewBox="-68 -25.6 136 51.2">
  <rect x="-68" y="-25.6" width="136" height="51.2" fill="white" />
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
    auto svg = text->generateXMLElements()[0]->toString();
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
<svg xmlns="http://www.w3.org/2000/svg" width="136" height="70.4" viewBox="-68 -35.2 136 70.4">
  <rect x="-68" y="-35.2" width="136" height="70.4" fill="white" />
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
