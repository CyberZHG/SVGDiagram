#include <random>

#include "geometry_utils.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestGeometryUtils, isSameAngle) {
    const auto xs = vector{1.0, 2.0, 3.0, 5.0, 7.0, 11.0, 13.0, 17.0, 19.0};
    const auto ys = vector{2.0, 3.0, 5.0, 7.0, 11.0, 13.0, 17.0, 19.0, 23.0};
    for (size_t i = 0; i < xs.size(); ++i) {
        EXPECT_TRUE(GeometryUtils::isSameAngle(atan2(ys[i], xs[i]), xs[i], ys[i]));
        EXPECT_TRUE(GeometryUtils::isSameAngle(atan2(ys[i], -xs[i]), -xs[i], ys[i]));
        EXPECT_TRUE(GeometryUtils::isSameAngle(atan2(-ys[i], xs[i]), xs[i], -ys[i]));
        EXPECT_TRUE(GeometryUtils::isSameAngle(atan2(-ys[i], -xs[i]), -xs[i], -ys[i]));
    }
    for (size_t i = 1; i < xs.size(); ++i) {
        EXPECT_FALSE(GeometryUtils::isSameAngle(atan2(ys[i], xs[i]), xs[i - 1], ys[i - 1]));
        EXPECT_FALSE(GeometryUtils::isSameAngle(atan2(ys[i], -xs[i]), -xs[i - 1], ys[i - 1]));
        EXPECT_FALSE(GeometryUtils::isSameAngle(atan2(-ys[i], xs[i]), xs[i - 1], -ys[i - 1]));
        EXPECT_FALSE(GeometryUtils::isSameAngle(atan2(-ys[i], -xs[i]), -xs[i - 1], -ys[i - 1]));
    }
}

TEST(TestGeometryUtils, computeBezierLengthStraightLine) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution uniform(-1000.0,1000.0);
    for (int caseIndex = 0; caseIndex < 100; ++caseIndex) {
        const double x1 = uniform(gen);
        const double y1 = uniform(gen);
        const double x2 = uniform(gen);
        const double y2 = uniform(gen);
        const double length1 = GeometryUtils::computeBezierLength({x1, y1}, {x1, y1}, {x2, y2}, {x2, y2});
        const double length2 = GeometryUtils::distance(x1, y1, x2, y2);
        EXPECT_DOUBLE_EQ(length1, length2);
    }
}
