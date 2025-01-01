#include "xml_element.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestXMLElement, Comment) {
    XMLElementComment comment("Created by: https://github.com/CyberZHG/SVGDiagram");
    auto output = comment.toString();
    auto expected = "<!-- Created by: https://github.com/CyberZHG/SVGDiagram -->\n";
    EXPECT_EQ(expected, output);
    comment.setContent("<!-- Created by: https://github.com/CyberZHG/SVGDiagram -->");
    output = comment.toString();
    expected = "<!-- <!‑‑ Created by: https://github.com/CyberZHG/SVGDiagram ‑‑> -->\n";
    EXPECT_EQ(expected, output);
}

TEST(TestXMLElement, SpecialCase1) {
    const auto text1 = make_shared<XMLElement>("text", "foo");
    const auto text2 = make_shared<XMLElement>("text", XMLElement::AttributesType{{"font-size", "18"}}, "bar");
    const auto rect = make_shared<XMLElement>("g",
        XMLElement::AttributesType{{"id", "\""}},
        XMLElement::ChildrenType{text1, text2});
    const auto circle = make_shared<XMLElement>("circle",
        XMLElement::AttributesType{{"cx", "0"}, {"cy", "0"}, {"r", "20"}});
    const XMLElement element("svg",
        {
            {"width", "48"},
            {"height", "48"},
            {"viewBox", "0 0 48 48"},
            {"xmlns", "http://www.w3.org/2000/svg"},
            {"xmlns:xlink", "http://www.w3.org/1999/xlink"},
        }, {rect, circle});
    const auto output = element.toString();
    const auto expected = R"(<svg width="48" height="48" viewBox="0 0 48 48" xmlns="http://www.w3.org/2000/svg" xmlns:xlink="http://www.w3.org/1999/xlink">
  <g id="&quot;">
    <text>foo</text>
    <text font-size="18">bar</text>
  </g>
  <circle cx="0" r="20" cy="0"/>
</svg>
)";
    EXPECT_EQ(expected, output);
}
