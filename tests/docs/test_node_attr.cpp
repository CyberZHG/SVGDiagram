#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

static const auto OUTPUT_DIR = string("../docs/source/_static/node_attr/");

TEST(TestDocsNodeAttributes, Label) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("foobar");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("Pybind11\nEmscripten");
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("物华天宝\n人杰地灵");
    diagram.render(OUTPUT_DIR + "label.svg");
}

TEST(TestDocsNodeAttributes, LabelDebug) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("foobar");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("Pybind11\nEmscripten");
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("物华天宝\n人杰地灵");
    diagram.render(OUTPUT_DIR + "label_debug.svg");
}