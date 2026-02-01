#include "svg_diagram.h"

#include <format>
#include <gtest/gtest.h>

#include "../test_utils.h"
using namespace std;
using namespace svg_diagram;

#ifndef SVG_DIAGRAM_ENABLE_PANGO_CAIRO
TEST(TestSVGDrawText, OneLineTextAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto text = make_unique<SVGDrawText>(0.0, 0.0, "Hello world!");
    auto svg = text->generateXMLElements()[0]->toString();
    EXPECT_EQ(svg, R"(<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">Hello&#160;world!</text>)" + string("\n"));
    diagram.addSVGDraw(std::move(text));
    svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawText, TwoLinesAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto text = make_unique<SVGDrawText>(0.0, 0.0, "Hello world!\n世界你好！");
    auto svg = text->generateXMLElements()[0]->toString();
    auto expected = R"(<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">
  <tspan x="0" dy="-0.6em">Hello&#160;world!</tspan><tspan x="0" dy="1.2em">世界你好！</tspan>
</text>
)";
    compareSVGContent(svg, expected);
    diagram.addSVGDraw(std::move(text));
    svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawText, ThreeLinesAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto text = make_unique<SVGDrawText>(0.0, 0.0, "Hello world!\n世界你好！\r\nSalve, mundus!");
    auto svg = text->generateXMLElements()[0]->toString();
    auto expected = R"(<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">
  <tspan x="0" dy="-1.2em">Hello&#160;world!</tspan><tspan x="0" dy="1.2em">世界你好！</tspan><tspan x="0" dy="1.2em">Salve,&#160;mundus!</tspan>
</text>
)";
    compareSVGContent(svg, expected);
    diagram.addSVGDraw(std::move(text));
    svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawText, Escape) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto text = make_unique<SVGDrawText>(0.0, 0.0, "<rect>");
    const auto svg = text->generateXMLElements()[0]->toString();
    const auto expected = R"(<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">&lt;rect&gt;</text>)";
    compareSVGContent(svg, expected);
    diagram.addSVGDraw(std::move(text));
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
#endif
