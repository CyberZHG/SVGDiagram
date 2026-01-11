#include "attribute_utils.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestAttributeUtils, ParseMarginSingle) {
    auto [x, y] = AttributeUtils::parseMarginToInches("12.34");
    EXPECT_EQ(x, 12.34);
    EXPECT_EQ(y, 12.34);
}

TEST(TestAttributeUtils, ParseMarginDouble) {
    auto [x, y] = AttributeUtils::parseMarginToInches("12.34,56.78");
    EXPECT_EQ(x, 12.34);
    EXPECT_EQ(y, 56.78);
}

TEST(TestAttributeUtils, ParseMarginInvalid) {
    EXPECT_THROW(AttributeUtils::parseMarginToInches("A"), runtime_error);
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

TEST(TestAttributeUtils, parseLengthToInch) {
    EXPECT_EQ(AttributeUtils::parseLengthToInch("-1e2"), -100.0);
    EXPECT_EQ(AttributeUtils::parseLengthToInch(" 12 in"), 12.0);
    EXPECT_EQ(AttributeUtils::parseLengthToInch("72 pt"), 1.0);
    EXPECT_EQ(AttributeUtils::parseLengthToInch("2.54 cm "), 1.0);
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
    const auto commands = AttributeUtils::parseDCommands("M 10,10\nA 6 4 10 1 0 14,10a 6 4 10 1 1 14,10 Z");
    EXPECT_EQ(commands, AttributeUtils::DCommands({
        {'M', {10.0, 10.0}},
        {'A', {6.0, 4.0, 10.0, 1.0, 0.0, 14.0, 10.0}},
        {'a', {6.0, 4.0, 10.0, 1.0, 1.0, 14.0, 10.0}},
        {'Z', {}},
    }));
    const auto points = AttributeUtils::computeDPathPoints(commands);
    const auto expected = vector<pair<double, double>>({
        {10.0, 10.0},
        {14.0, 10.0},
        {28.0, 20.0},
    });
    EXPECT_EQ(points, expected);
}

TEST(TestAttributeUtils, ParseBool) {
    EXPECT_TRUE(AttributeUtils::parseBool("ON"));
    EXPECT_FALSE(AttributeUtils::parseBool("OFF"));
}

TEST(TestAttributeUtils, SplitString) {
    EXPECT_EQ(AttributeUtils::splitString("12345", ','), vector<string>({"12345"}));
    EXPECT_EQ(AttributeUtils::splitString("123,,45", ','), vector<string>({"123", "", "45"}));
    EXPECT_EQ(AttributeUtils::splitString("123,,45", ","), vector<string>({"123", "", "45"}));
    EXPECT_EQ(AttributeUtils::splitString(",12345,", ','), vector<string>({"", "12345", ""}));
}

TEST(TestAttributeUtils, ParseStyle) {
    auto style = AttributeUtils::parseStyle("filled,dashed");
    EXPECT_FALSE(style.solid);
    EXPECT_TRUE(style.dashed);
    EXPECT_FALSE(style.dotted);
    style = AttributeUtils::parseStyle("filled,dotted");
    EXPECT_FALSE(style.solid);
    EXPECT_FALSE(style.dashed);
    EXPECT_TRUE(style.dotted);
}

TEST(TestAttributeUtils, ParseColorList) {
    auto colorList = AttributeUtils::parseColorList("#FF0000");
    ASSERT_EQ(colorList.size(), 1);
    EXPECT_EQ(colorList[0].color, "#FF0000");
    EXPECT_EQ(colorList[0].opacity, 1.0);
    EXPECT_LE(colorList[0].weight, 0.0);
    colorList = AttributeUtils::parseColorList("#FF0000CC");
    ASSERT_EQ(colorList.size(), 1);
    EXPECT_EQ(colorList[0].color, "#FF0000");
    EXPECT_EQ(colorList[0].opacity, 0.8);
    EXPECT_LE(colorList[0].weight, 0.0);
    colorList = AttributeUtils::parseColorList("red:green:blue");
    ASSERT_EQ(colorList.size(), 3);
    EXPECT_EQ(colorList[0].color, "red");
    EXPECT_EQ(colorList[0].opacity, 1.0);
    EXPECT_LE(colorList[0].weight, 0.0);
    EXPECT_EQ(colorList[1].color, "green");
    EXPECT_EQ(colorList[1].opacity, 1.0);
    EXPECT_LE(colorList[1].weight, 0.0);
    EXPECT_EQ(colorList[2].color, "blue");
    EXPECT_EQ(colorList[2].opacity, 1.0);
    EXPECT_LE(colorList[2].weight, 0.0);
    colorList = AttributeUtils::parseColorList("red;0.2:green:blue");
    ASSERT_EQ(colorList.size(), 3);
    EXPECT_EQ(colorList[0].color, "red");
    EXPECT_LE(colorList[0].weight, 0.2);
    EXPECT_EQ(colorList[1].color, "green");
    EXPECT_LE(colorList[1].weight, 0.4);
    EXPECT_EQ(colorList[2].color, "blue");
    EXPECT_LE(colorList[2].weight, 0.4);
    colorList = AttributeUtils::parseColorList("red;0.2:green:blue;0.6");
    ASSERT_EQ(colorList.size(), 3);
    EXPECT_EQ(colorList[0].color, "red");
    EXPECT_LE(colorList[0].weight, 0.2);
    EXPECT_EQ(colorList[1].color, "green");
    EXPECT_LE(colorList[1].weight, 0.2);
    EXPECT_EQ(colorList[2].color, "blue");
    EXPECT_LE(colorList[2].weight, 0.6);
    colorList = AttributeUtils::parseColorList("red;0.6:blue;0.6");
    ASSERT_EQ(colorList.size(), 2);
    EXPECT_EQ(colorList[0].color, "red");
    EXPECT_LE(colorList[0].weight, 0.5);
    EXPECT_EQ(colorList[1].color, "blue");
    EXPECT_LE(colorList[1].weight, 0.5);
    colorList = AttributeUtils::parseColorList("red;30:blue;30");
    ASSERT_EQ(colorList.size(), 2);
    EXPECT_EQ(colorList[0].color, "red");
    EXPECT_LE(colorList[0].weight, 0.5);
    EXPECT_EQ(colorList[1].color, "blue");
    EXPECT_LE(colorList[1].weight, 0.5);
    colorList = AttributeUtils::parseColorList("red;1:green:blue;1");
    ASSERT_EQ(colorList.size(), 3);
    EXPECT_EQ(colorList[0].color, "red");
    EXPECT_LE(colorList[0].weight, 1.0 / 3.0);
    EXPECT_EQ(colorList[1].color, "green");
    EXPECT_LE(colorList[1].weight, 1.0 / 3.0);
    EXPECT_EQ(colorList[2].color, "blue");
    EXPECT_LE(colorList[2].weight, 1.0 / 3.0);
}

TEST(TestAttributeUtils, ParseRecordLabelTextOnly) {
    const auto result = AttributeUtils::parseRecordLabel("foo");
    EXPECT_EQ(result->children.size(), 1);
    EXPECT_EQ(result->children[0]->label, "foo");
    EXPECT_EQ(result->toString(), "foo");
}

TEST(TestAttributeUtils, ParseRecordLabelEscape) {
    const auto result = AttributeUtils::parseRecordLabel(R"(\{foo\ \|bar\})");
    EXPECT_EQ(result->children.size(), 1);
    EXPECT_EQ(result->children[0]->label, "{foo |bar}");
    EXPECT_EQ(result->toString(), R"(\{foo\ \|bar\})");
}

TEST(TestAttributeUtils, ParseRecordLabelSplit1) {
    const auto result = AttributeUtils::parseRecordLabel("foo|bar");
    EXPECT_EQ(result->children.size(), 2);
    EXPECT_EQ(result->children[0]->label, "foo");
    EXPECT_EQ(result->children[1]->label, "bar");
    EXPECT_EQ(result->toString(), "foo|bar");
}

TEST(TestAttributeUtils, ParseRecordLabelSplit2) {
    const auto result = AttributeUtils::parseRecordLabel("{foo|bar}");
    EXPECT_EQ(result->children.size(), 1);
    EXPECT_EQ(result->children[0]->children.size(), 2);
    EXPECT_EQ(result->children[0]->children[0]->label, "foo");
    EXPECT_EQ(result->children[0]->children[1]->label, "bar");
    EXPECT_EQ(result->toString(), "{foo|bar}");
}

TEST(TestAttributeUtils, ParseRecordFieldId1) {
    const auto result = AttributeUtils::parseRecordLabel("foo|<foobar>bar");
    EXPECT_EQ(result->children.size(), 2);
    EXPECT_EQ(result->children[0]->label, "foo");
    EXPECT_EQ(result->children[1]->label, "bar");
    EXPECT_EQ(result->children[1]->fieldId, "foobar");
    EXPECT_EQ(result->toString(), "foo|bar");
}

TEST(TestAttributeUtils, ParseRecordFieldId2) {
    const auto result = AttributeUtils::parseRecordLabel("foo|<\\<foobar\\>>bar");
    EXPECT_EQ(result->children.size(), 2);
    EXPECT_EQ(result->children[0]->label, "foo");
    EXPECT_EQ(result->children[1]->label, "bar");
    EXPECT_EQ(result->children[1]->fieldId, "<foobar>");
    EXPECT_EQ(result->toString(), "foo|bar");
}

TEST(TestAttributeUtils, ParseRecordSpecial1) {
    EXPECT_EQ(AttributeUtils::parseRecordLabel("{{foo}|{bar}}")->toString(), "{{foo}|{bar}}");
    EXPECT_EQ(AttributeUtils::parseRecordLabel("{{{}}|{||}}")->toString(), "{{{}}|{||}}");
}
