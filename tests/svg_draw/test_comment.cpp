#include "svg_diagram.h"

#include <format>
#include <gtest/gtest.h>

#include "../test_utils.h"
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDrawComment, DefaultComment) {
    SVGDiagram diagram;
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawComment, EscapeComment) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    diagram.setBackgroundColor("white");
    diagram.addSVGDraw(make_unique<SVGDrawComment>("A <!-- B --> C"));
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDrawComment, EmptyBoundingBox) {
    auto boundingBox = SVGDrawComment().boundingBox();
    ASSERT_EQ(boundingBox.x2, 0.0);
    boundingBox = SVGDrawTitle().boundingBox();
    ASSERT_EQ(boundingBox.x2, 0.0);
    boundingBox = SVGDrawPolygon().boundingBox();
    ASSERT_EQ(boundingBox.x2, 0.0);
}

TEST(TestSVGDrawComment, Tag) {
    ASSERT_EQ(SVGDrawComment().tag(), "!--");
}
