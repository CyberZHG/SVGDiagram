#include "attribute_utils.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestAttributeUtils, ParseMarginSingle) {
    auto [x, y] =  AttributeUtils::parseMargin("12.34");
    EXPECT_EQ(x, 12.34);
    EXPECT_EQ(y, 12.34);
}

TEST(TestAttributeUtils, ParseMarginDouble) {
    auto [x, y] =  AttributeUtils::parseMargin("12.34,56.78");
    EXPECT_EQ(x, 12.34);
    EXPECT_EQ(y, 56.78);
}
