#include "xml_element.h"

#include <sstream>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestXMLElementParse, SingleTag) {
    const auto expected = R"(<svg/>)" + string("\n");
    const auto elements = XMLElement::parse(expected);
    const auto output = elements[0]->toString();
    EXPECT_EQ(output, expected);
}

TEST(TestXMLElementParse, SingleTagOpenAndClose) {
    const auto input = R"(<svg></svg>)" + string("\n");
    const auto elements = XMLElement::parse(input);
    const auto output = elements[0]->toString();
    const auto expected = R"(<svg/>)" + string("\n");
    EXPECT_EQ(output, expected);
}

TEST(TestXMLElementParse, SingleTagAttributes) {
    const auto expected = R"(<svg width="10" height="10"/>)" + string("\n");
    const auto elements = XMLElement::parse(expected);
    const auto output = elements[0]->toString();
    EXPECT_EQ(output, expected);
}

TEST(TestXMLElementParse, SingleTagContent) {
    const auto expected = R"(<text> foo </text>)" + string("\n");
    const auto elements = XMLElement::parse(expected);
    const auto output = elements[0]->toString();
    EXPECT_EQ(output, expected);
}

TEST(TestXMLElementParse, SpecialCase1) {
    const auto expected = R"s(<svg width="152.09256357784233" height="102.09256357784231" viewBox="0 0 152.09256357784233 102.09256357784231" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
  <g id="graph0" class="graph" transform="translate(-78.30819398704587,-78.30819398704587) scale(1.0)">
    <!-- node_id = A -->
    <circle cx="100" cy="100" r="17.692" fill="none" stroke="black"/>
    <text x="100" y="100" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16">A</text>
    <!-- node_id = B -->
    <circle cx="200" cy="150" r="26.401" fill="none" stroke="black"/>
    <text x="200" y="150" text-anchor="middle" dominant-baseline="central" font-family="Serif" font-size="16">B</text>
    <!-- edge_id = A -> B -->
    <line x1="115.824" y1="107.912" x2="176.386" y2="138.193" stroke="black"/>
  </g>
</svg>
)s";
    const auto elements = XMLElement::parse(expected);
    const auto output = elements[0]->toString();
    EXPECT_EQ(output, expected);
}

TEST(TestXMLElementCompare, NotEqualTag) {
    const XMLElement a("a");
    const XMLElement b("b");
    EXPECT_NE(a, b);
}

TEST(TestXMLElementCompare, NotEqualContent) {
    const XMLElement a("text", "foo");
    const XMLElement b("text", "bar");
    EXPECT_NE(a, b);
}

TEST(TestXMLElementCompare, NotEqualAttributesLength) {
    const XMLElement a("text", {{"id", "foo"}, {"class", "bar"}});
    const XMLElement b("text", {{"id", "foo"}});
    EXPECT_NE(a, b);
}

TEST(TestXMLElementCompare, NotEqualAttributeName) {
    const XMLElement a("text", {{"id", "foo"}});
    const XMLElement b("text", {{"class", "foo"}});
    EXPECT_NE(a, b);
}

TEST(TestXMLElementCompare, NotEqualAttributeValueLength) {
    const XMLElement a("text", {{"class", "123"}});
    const XMLElement b("text", {{"class", "123d"}});
    EXPECT_NE(a, b);
}

TEST(TestXMLElementCompare, NotEqualAttributeValueNumberText) {
    const XMLElement a("text", {{"class", "a"}});
    const XMLElement b("text", {{"class", "b"}});
    EXPECT_NE(a, b);
}

TEST(TestXMLElementCompare, NotEqualChildrenSize) {
    const auto comment1 = make_shared<XMLElementComment>("foo");
    const auto comment2 = make_shared<XMLElementComment>("bar");
    const XMLElement a("g", {}, comment1);
    const XMLElement b("g", {}, {comment1, comment2});
    EXPECT_NE(a, b);
}

TEST(TestXMLElementCompare, EmptyTag) {
    const auto comment1 = make_shared<XMLElementComment>("foo");
    const auto comment2 = make_shared<XMLElementComment>("bar");
    const XMLElement a("", {}, {comment1, comment2});
    const XMLElement b("", {}, {comment1, comment2});
    EXPECT_EQ(a.toString(), b.toString());
}

TEST(TestXMLElementCompare, Comment) {
    const XMLElementComment a("foo");
    const XMLElementComment b("foo");
    EXPECT_EQ(a.toString(), b.toString());
}

TEST(TestXMLElementCompare, NotEqualAttributeValueNumberAndText) {
    const XMLElement a("text", {{"class", "d"}});
    const XMLElement b("text", {{"class", "1"}});
    EXPECT_NE(a, b);
}

TEST(TestXMLElementCompare, SpecialCase1) {
    const auto xml1 = R"(<svg width="10" height="10"/>)" + string("\n");
    const auto xml2 = R"(<svg height="10" width="10"/>)" + string("\n");
    const auto xml3 = R"(<svg width="10" height="10.00000001"/>)" + string("\n");
    const auto xml4 = R"(<svg width="10" height="11"/>)" + string("\n");
    const auto element1 = XMLElement::parse(xml1)[0];
    const auto element2 = XMLElement::parse(xml2)[0];
    const auto element3 = XMLElement::parse(xml3)[0];
    const auto element4 = XMLElement::parse(xml4)[0];
    EXPECT_EQ(*element1.get(), *element2.get());
    EXPECT_EQ(*element1.get(), *element3.get());
    EXPECT_NE(*element1.get(), *element4.get());
    EXPECT_EQ(*element2.get(), *element3.get());
    EXPECT_NE(*element2.get(), *element4.get());
    EXPECT_NE(*element3.get(), *element4.get());
}

TEST(TestXMLElementCompare, SpecialCase2) {
    const auto xml1 = R"(<svg width="10" id="a"><text>foo</text></svg>)" + string("\n");
    const auto xml2 = R"(<svg width="10" id="a"><text>foo</text></svg>)" + string("\n");
    const auto xml3 = R"(<svg width="10" id="b"><text>foo</text></svg>)" + string("\n");
    const auto xml4 = R"(<svg width="10" id="a"><text>bar</text></svg>)" + string("\n");
    const auto element1 = XMLElement::parse(xml1)[0];
    const auto element2 = XMLElement::parse(xml2)[0];
    const auto element3 = XMLElement::parse(xml3)[0];
    const auto element4 = XMLElement::parse(xml4)[0];
    EXPECT_EQ(*element1.get(), *element2.get());
    EXPECT_NE(*element1.get(), *element3.get());
    EXPECT_NE(*element1.get(), *element4.get());
}

TEST(TestXMLElementConstruct, ConstructWithContent) {
    XMLElement element("text", "bar");
    stringstream ss;
    PrintTo(element, &ss);
    const auto expected = R"(<text>bar</text>)";
    string output;
    ss >> output;
    EXPECT_EQ(output, expected);
}

TEST(TestXMLElementConstruct, ConstructWithAttributes) {
    const XMLElement element("g", {{"id", "foo\""}, {"class", "bar"}});
    const auto expected = XMLElement::parse(R"(<g id="foo&quot;" class="bar"/>)");
    EXPECT_EQ(element, *expected[0].get());
}

TEST(TestXMLElementConstruct, ConstructWithAttributesAndContent) {
    XMLElement element("g", {{"id", "foo"}, {"class", "bar"}}, "foobar");
    element.setTag("text");
    const auto expected = XMLElement::parse(R"(<text id="foo" class="bar">foobar</text>)");
    EXPECT_EQ(element, *expected[0].get());
}