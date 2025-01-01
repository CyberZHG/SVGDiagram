#include "svg_diagram.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDraw, NumDecimal) {
    const SVGDrawComment draw;
    EXPECT_EQ(draw.formatDouble(0.0), "0");
    EXPECT_EQ(draw.formatDouble(1.2), "1.2");
    EXPECT_EQ(draw.formatDouble(1.23), "1.23");
    EXPECT_EQ(draw.formatDouble(1.234), "1.234");
    EXPECT_EQ(draw.formatDouble(1.2345), "1.234");
    EXPECT_EQ(draw.formatDouble(1.23456), "1.235");
}
