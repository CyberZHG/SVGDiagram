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
    EXPECT_EQ(width, 16 * textSize.widthScale());
    EXPECT_EQ(height, 16);
}

TEST(TestTextSizeApproximation, SpecialCase2) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("ABC", 16);
    EXPECT_EQ(width, 16 * 3 * textSize.widthScale());
    EXPECT_EQ(height, 16 * textSize.heightScale());
}

TEST(TestTextSizeApproximation, SpecialCase3) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("\nABC", 16);
    EXPECT_EQ(width, 16 * 3 * textSize.widthScale());
    EXPECT_EQ(height, 16 * (2 * textSize.heightScale() + 1 * textSize.lineSpacingScale()));
}

TEST(TestTextSizeApproximation, SpecialCase4) {
    SVGTextSize textSize;
    textSize.setHeightScale(1.2);
    textSize.setWidthScale(0.8);
    textSize.setLineSpacingScale(0.15);
    auto [width, height] =  textSize.computeApproximateTextSize("ABC\r", 32);
    EXPECT_EQ(width, 32 * 3 * textSize.widthScale());
    EXPECT_EQ(height, 32 * (2 * textSize.heightScale() + 1 * textSize.lineSpacingScale()));
}

TEST(TestTextSizeApproximation, SpecialCase5) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("\n\r\r\n", 32);
    EXPECT_EQ(width, 0);
    EXPECT_EQ(height, 32 * (4 * textSize.heightScale() + 3 * textSize.lineSpacingScale()));
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

TEST(TestTextSize, SingleLineAlignLeft) {
    const SVGTextSize textSize;
    auto [width1, height1] =  textSize.computeTextSize("foo", 16);
    auto [width2, height2] =  textSize.computeTextSize("foo\\l", 16);
    EXPECT_EQ(width1, width2);
    EXPECT_EQ(height1, height2);
}

TEST(TestTextSize, SingleLineAlignRight) {
    const SVGTextSize textSize;
    auto [width1, height1] =  textSize.computeTextSize("foo", 16);
    auto [width2, height2] =  textSize.computeTextSize("foo\\r", 16);
    EXPECT_EQ(width1, width2);
    EXPECT_EQ(height1, height2);
}

TEST(TestTextSize, MultiLineAlignLeft1) {
    const SVGTextSize textSize;
    auto [width1, height1] =  textSize.computeTextSize("foo\nbar\nfoobar", 16);
    auto [width2, height2] =  textSize.computeTextSize("foo\\lbar\\lfoobar\\l", 16);
    EXPECT_EQ(width1, width2);
    EXPECT_EQ(height1, height2);
}

TEST(TestTextSize, MultiLineAlignLeft2) {
    const SVGTextSize textSize;
    auto [width1, height1] =  textSize.computeTextSize("foo\nfoobar\nbar", 16);
    auto [width2, height2] =  textSize.computeTextSize("foo\\lfoobar\\lbar\\l", 16);
    EXPECT_EQ(width1, width2);
    EXPECT_EQ(height1, height2);
}

TEST(TestTextSize, MultiLineAlignRight) {
    const SVGTextSize textSize;
    auto [width1, height1] =  textSize.computeTextSize("foo\nbar\nfoobar", 16);
    auto [width2, height2] =  textSize.computeTextSize("foo\\rbar\\rfoobar\\r", 16);
    EXPECT_EQ(width1, width2);
    EXPECT_EQ(height1, height2);
}

TEST(TestTextSize, MultiLineAlignMix) {
    const SVGTextSize textSize;
    auto [width1, height1] =  textSize.computeTextSize("foo\nbar\nfoobar", 16);
    auto [width2, height2] =  textSize.computeTextSize("foo\\lbar\nfoobar\\r", 16);
    EXPECT_EQ(width1, width2);
    EXPECT_EQ(height1, height2);
}
