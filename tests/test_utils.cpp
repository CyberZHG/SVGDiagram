#include "test_utils.h"

#include <regex>
#include <gtest/gtest.h>

#include "xml_element.h"
using namespace std;
using namespace svg_diagram;

void compareSVGContent(const string& a, const string& b) {
    XMLElement rootA, rootB;
    rootA.addChildren(XMLElement::parse(a));
    rootB.addChildren(XMLElement::parse(b));
    EXPECT_EQ(rootA, rootB);
}

void compareSVGWithDefaultGraphContent(const string& a, const string& b) {
    XMLElement rootA, rootB;
    rootA.addChildren(XMLElement::parse(a)[0]->children()[1]->children());
    rootB.addChildren(XMLElement::parse(b));
    EXPECT_EQ(rootA, rootB);
}
