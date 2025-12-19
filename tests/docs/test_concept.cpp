#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

static const auto OUTPUT_DIR = string("../docs/source/_static/concept/");

TEST(TestDocsConcept, Empty) {
    SVGDiagram diagram;
    diagram.render(OUTPUT_DIR + "empty.svg");
}

TEST(TestDocsConcept, Node) {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setCenter(0, 0);
    node->setLabel("foo\nbar");
    diagram.render(OUTPUT_DIR + "node.svg");
}

TEST(TestDocsConcept, Edge) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(60, 80);
    diagram.addEdge("A", "B");
    diagram.render(OUTPUT_DIR + "edge.svg");
}