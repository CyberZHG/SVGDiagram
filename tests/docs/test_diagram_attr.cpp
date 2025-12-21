#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <format>
#include <vector>
#include <gtest/gtest.h>
using namespace svg_diagram;

static const auto OUTPUT_DIR = std::string("../docs/source/_static/diagram_attr/");

TEST(TestDocsDiagramAttributes, BackgroundColor) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("lightgray");
    const auto node = diagram.addNode("A");
    node->setLabel("A");
    diagram.render(OUTPUT_DIR + "background_color.svg");
}