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

TEST(TestAttributeUtils, ParseDCommandMove) {
    const auto commands = AttributeUtils::parseDCommands("M 10,10\nm -20,5 5,-5");
    EXPECT_EQ(commands, AttributeUtils::DCommands({
        {'M', {10.0, 10.0}},
        {'m', {-20.0, 5.0, 5.0, -5.0}},
    }));
    const auto points = AttributeUtils::computeDPathPoints(commands);
    const auto expected = vector<pair<double, double>>({
        {10.0, 10.0},
        {-10.0, 15.0},
        {-5.0, 10.0},
    });
    EXPECT_EQ(points, expected);
}

TEST(TestAttributeUtils, ParseDCommandLineTo) {
    const auto commands = AttributeUtils::parseDCommands(
        "M -5,-5 L 10,10\nl -20,5 5,-5 H 20.0 h 10.0 -10.0 V 20.0 v 10 -10 .5"
    );
    EXPECT_EQ(commands, AttributeUtils::DCommands({
        {'M', {-5.0, -5.0}},
        {'L', {10.0, 10.0}},
        {'l', {-20.0, 5.0, 5.0, -5.0}},
        {'H', {20.0}},
        {'h', {10.0, -10.0}},
        {'V', {20.0}},
        {'v', {10.0, -10.0, 0.5}},
    }));
    const auto points = AttributeUtils::computeDPathPoints(commands);
    const auto expected = vector<pair<double, double>>({
        {-5.0, -5.0},
        {10.0, 10.0},
        {-10.0, 15.0},
        {-5.0, 10.0},
        {20.0, 10.0},
        {30.0, 10.0},
        {20.0, 10.0},
        {20.0, 20.0},
        {20.0, 30.0},
        {20.0, 20.0},
        {20.0, 20.5},
    });
    EXPECT_EQ(points, expected);
}

TEST(TestAttributeUtils, ParseDCommandArc) {
    const auto commands = AttributeUtils::parseDCommands("M 10,10\nA 6 4 10 1 0 14,10a 6 4 10 1 1 14,10");
    EXPECT_EQ(commands, AttributeUtils::DCommands({
        {'M', {10.0, 10.0}},
        {'A', {6.0, 4.0, 10.0, 1.0, 0.0, 14.0, 10.0}},
        {'a', {6.0, 4.0, 10.0, 1.0, 1.0, 14.0, 10.0}},
    }));
    const auto points = AttributeUtils::computeDPathPoints(commands);
    const auto expected = vector<pair<double, double>>({
        {10.0, 10.0},
        {14.0, 10.0},
        {28.0, 20.0},
    });
    EXPECT_EQ(points, expected);
}