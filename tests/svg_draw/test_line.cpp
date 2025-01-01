#include "svg_diagram.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDrawLine, SingleLineAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto line = make_unique<SVGDrawLine>(0.0, 0.0, 20.0, 30.0);
    line->setAttribute(SVG_ATTR_KEY_STROKE, "red");
    auto svg = line->generateXMLElements()[0]->toString();
    EXPECT_EQ(svg, R"(<line x1="0" y1="0" x2="20" y2="30" stroke="red" />)" + string("\n"));
    diagram.addSVGDraw(std::move(line));
    svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="36" height="46" viewBox="-8 -8 36 46">
  <rect x="-8" y="-8" width="36" height="46" fill="white" />
  <line x1="0" y1="0" x2="20" y2="30" stroke="red" />
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawLine, TwoLinesAutoSize) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    auto line1 = make_unique<SVGDrawLine>(0.0, 0.0, 20.0, 30.0);
    line1->setAttribute(SVG_ATTR_KEY_STROKE, "red");
    auto svg = line1->generateXMLElements()[0]->toString();
    EXPECT_EQ(svg, R"(<line x1="0" y1="0" x2="20" y2="30" stroke="red" />)" + string("\n"));
    diagram.addSVGDraw(std::move(line1));
    auto line2 = make_unique<SVGDrawLine>(10.0, 20.0, 5.0, 40.0);
    line2->setAttribute(SVG_ATTR_KEY_STROKE, "blue");
    svg = line2->generateXMLElements()[0]->toString();
    EXPECT_EQ(svg, R"(<line x1="10" y1="20" x2="5" y2="40" stroke="blue" />)" + string("\n"));
    diagram.addSVGDraw(std::move(line2));
    svg = diagram.render();
    const auto expected = R"(<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg" width="36" height="56" viewBox="-8 -8 36 56">
  <rect x="-8" y="-8" width="36" height="56" fill="white" />
  <line x1="0" y1="0" x2="20" y2="30" stroke="red" />
  <line x1="10" y1="20" x2="5" y2="40" stroke="blue" />
</svg>
)";
    EXPECT_EQ(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
