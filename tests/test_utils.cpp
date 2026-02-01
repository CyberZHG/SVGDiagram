#include "test_utils.h"

#include <regex>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <gtest/gtest.h>

#include "xml_element.h"
using namespace std;
using namespace svg_diagram;

static const string EXPECTED_DIR = "../tests/expected/";

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

string readExpectedSVG(const string& testSuite, const string& testName) {
    const string filePath = EXPECTED_DIR + testSuite + "/" + testName + ".svg";
    ifstream file(filePath);
    if (!file.is_open()) {
        ADD_FAILURE() << "Failed to open expected SVG file: " << filePath;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void compareSVGWithExpectedFile(const string& svg, const string& testSuite, const string& testName) {
    const string expected = readExpectedSVG(testSuite, testName);
    if (expected.empty()) {
        return;
    }
    compareSVGContent(svg, expected);
}
