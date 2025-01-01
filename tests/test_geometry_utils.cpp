#include "geometry_utils.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestGeometryUtils, isSameAngle) {
    const auto xs = vector{1.0, 2.0, 3.0, 5.0, 7.0, 11.0, 13.0, 17.0, 19.0};
    const auto ys = vector{2.0, 3.0, 5.0, 7.0, 11.0, 13.0, 17.0, 19.0, 23.0};
    for (int i = 0; i < xs.size(); ++i) {
        EXPECT_TRUE(GeometryUtils::isSameAngle(atan2(ys[i], xs[i]), xs[i], ys[i]));
        EXPECT_TRUE(GeometryUtils::isSameAngle(atan2(ys[i], -xs[i]), -xs[i], ys[i]));
        EXPECT_TRUE(GeometryUtils::isSameAngle(atan2(-ys[i], xs[i]), xs[i], -ys[i]));
        EXPECT_TRUE(GeometryUtils::isSameAngle(atan2(-ys[i], -xs[i]), -xs[i], -ys[i]));
    }
    for (int i = 1; i < xs.size(); ++i) {
        EXPECT_FALSE(GeometryUtils::isSameAngle(atan2(ys[i], xs[i]), xs[i - 1], ys[i - 1]));
        EXPECT_FALSE(GeometryUtils::isSameAngle(atan2(ys[i], -xs[i]), -xs[i - 1], ys[i - 1]));
        EXPECT_FALSE(GeometryUtils::isSameAngle(atan2(-ys[i], xs[i]), xs[i - 1], -ys[i - 1]));
        EXPECT_FALSE(GeometryUtils::isSameAngle(atan2(-ys[i], -xs[i]), -xs[i - 1], -ys[i - 1]));
    }
}
