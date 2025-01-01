#include "svg_text_size.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestTextSizeApproximation, EmptyText) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("", 16);
    EXPECT_EQ(width, 0);
    EXPECT_EQ(height, 0);
}

TEST(TestTextSizeApproximation, SpecialCase1) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("A", 16);
    EXPECT_EQ(width, 10.666666666666666);
    EXPECT_EQ(height, 21.333333333333332);
}

TEST(TestTextSizeApproximation, SpecialCase2) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("ABC", 16);
    EXPECT_EQ(width, 32);
    EXPECT_EQ(height, 21.333333333333332);
}

TEST(TestTextSizeApproximation, SpecialCase3) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("\nABC", 16);
    EXPECT_EQ(width, 32);
    EXPECT_EQ(height, 46.933333333333337);
}

TEST(TestTextSizeApproximation, SpecialCase4) {
    SVGTextSize textSize;
    textSize.setHeightScale(1.2);
    textSize.setWidthScale(0.8);
    textSize.setLineSpacingScale(0.15);
    auto [width, height] =  textSize.computeApproximateTextSize("ABC\r", 32);
    EXPECT_EQ(width, 102.4);
    EXPECT_EQ(height, 108.79999999999998);
}

TEST(TestTextSizeApproximation, SpecialCase5) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("\n\r\r\n", 32);
    EXPECT_EQ(width, 0);
    EXPECT_EQ(height, 196.26666666666665);
}

#ifdef SVG_DIAGRAM_ENABLE_PANGO_CAIRO
TEST(TestTextSizePangoCairo, EmptyText) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeTextSize("", 16);
    EXPECT_EQ(width, 0);
    EXPECT_EQ(height, 0);
}

TEST(TestTextSizePangoCairo, SpecialCase1) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeTextSize("A", 16);
    EXPECT_EQ(width, 14.7392578125);
    EXPECT_EQ(height, 14.3642578125);
}

TEST(TestTextSizePangoCairo, SpecialCase2) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeTextSize("ABC", 16);
    EXPECT_EQ(width, 42.1875);
    EXPECT_EQ(height, 14.71875);
}

TEST(TestTextSizePangoCairo, SpecialCase3) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeTextSize("\nABC", 16);
    EXPECT_EQ(width, 42.5);
    EXPECT_EQ(height, 21.6875);
}

TEST(TestTextSizePangoCairo, SpecialCase4) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeTextSize("ABC\r", 16);
    EXPECT_EQ(width, 42.5);
    EXPECT_EQ(height, 35.6962890625);
}

TEST(TestTextSizePangoCairo, SpecialCase5) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeTextSize("\n\r\r\n", 32);
    EXPECT_EQ(width, 0);
    EXPECT_EQ(height, 127.998046875);
}
#endif