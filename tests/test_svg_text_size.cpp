#include "svg_text_size.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestTextSize, EmptyText) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("", 16);
    EXPECT_EQ(width, 0);
    EXPECT_EQ(height, 0);
}

TEST(TestTextSize, SpecialCase1) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("A", 16);
    EXPECT_EQ(width, 16 * 0.6);
    EXPECT_EQ(height, 16);
}

TEST(TestTextSize, SpecialCase2) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("ABC", 16);
    EXPECT_EQ(width, 16 * 0.6 * 3);
    EXPECT_EQ(height, 16);
}

TEST(TestTextSize, SpecialCase3) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("\nABC", 16);
    EXPECT_EQ(width, 16 * 0.6 * 3);
    EXPECT_EQ(height, 16 * (2 + 0.2));
}

TEST(TestTextSize, SpecialCase4) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("ABC\r", 16);
    EXPECT_EQ(width, 16 * 0.6 * 3);
    EXPECT_EQ(height, 16 * (2 + 0.2));
}

TEST(TestTextSize, SpecialCase5) {
    const SVGTextSize textSize;
    auto [width, height] =  textSize.computeApproximateTextSize("\n\r\r\n", 32);
    EXPECT_EQ(width, 0);
    EXPECT_EQ(height, 32 * (4 + 3 * 0.2));
}
