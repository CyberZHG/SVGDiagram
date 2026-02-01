#include <numbers>

#include "svg_diagram.h"

#include <format>
#include <cmath>
#include <random>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestExample, Random) {
    SVGDiagram diagram;
    diagram.setBackgroundColor("white");
    static mt19937 rng{random_device{}()};

    const auto shapes = vector{
        SVGNode::SHAPE_ELLIPSE, SVGNode::SHAPE_CIRCLE, SVGNode::SHAPE_DOUBLE_ELLIPSE, SVGNode::SHAPE_RECT,
        SVGNode::SHAPE_POLYGON,
    };
    uniform_int_distribution distShape(0, static_cast<int>(shapes.size() - 1));
    uniform_int_distribution distSides(3, 9);
    const auto styles = vector<string>{
        "solid", "dashed",
    };
    uniform_int_distribution distStyle(0, static_cast<int>(styles.size() - 1));
    const auto arrows = vector{
        SVGEdge::ARROW_EMPTY, SVGEdge::ARROW_NORMAL, SVGEdge::ARROW_NONE,
    };
    uniform_int_distribution distArrow(0, static_cast<int>(arrows.size() - 1));

    const auto& central = diagram.addNode("c");
    central->setCenter(0.0, 0.0);
    central->setShape(shapes[distShape(rng)]);
    central->setStyle(styles[distStyle(rng)]);
    central->setLabel("Central");
    constexpr double start = numbers::pi / 19.0;
    for (int i = 0; i < 17; ++i) {
        const auto nodeName = format("n_{}", i);
        const auto& node = diagram.addNode(nodeName);
        constexpr double shift = 2.0 * numbers::pi / 17.0;
        const double angle = start + i * shift;
        node->setCenter(130.0 * cos(angle), 130.0 * sin(angle));
        node->setShape(shapes[distShape(rng)]);
        node->setSides(distSides(rng));
        node->setStyle(styles[distStyle(rng)]);
        node->setLabel(format("{}", i));
        if (i % 2 == 0) {
            const auto& edge = diagram.addEdge("c", nodeName);
            edge->setArrowHead(arrows[distArrow(rng)]);
            edge->setArrowTail(arrows[distArrow(rng)]);
            edge->setStyle(styles[distStyle(rng)]);
            edge->addConnectionPoint(60.0 * cos(angle), 60.0 * sin(angle));
            edge->addConnectionPoint(80.0 * cos(angle + shift / 3.0), 80.0 * sin(angle + shift / 3.0));
        } else {
            const auto& edge = diagram.addEdge(nodeName, "c");
            edge->setArrowHead(arrows[distArrow(rng)]);
            edge->setArrowTail(arrows[distArrow(rng)]);
            edge->setStyle(styles[distStyle(rng)]);
            edge->addConnectionPoint(80.0 * cos(angle - shift / 3.0), 80.0 * sin(angle - shift / 3.0));
            edge->addConnectionPoint(60.0 * cos(angle), 60.0 * sin(angle));
        }
        diagram.addEdge(nodeName, format("n_{}", (i + 1) % 17));
        const auto& edge = diagram.addEdge(nodeName, format("n_{}", (i + 2) % 17));
        edge->addConnectionPoint(200.0 * cos(angle + shift), 200.0 * sin(angle + shift));
        edge->setArrowHead(arrows[distArrow(rng)]);
        edge->setArrowTail(arrows[distArrow(rng)]);
        edge->setStyle(styles[distStyle(rng)]);
    }
    for (int i = 0; i < 41; ++i) {
        const auto nodeName = format("n_o{}", i);
        const auto& node = diagram.addNode(nodeName);
        constexpr double shift = 2.0 * numbers::pi / 41.0;
        const double angle = start + i * shift;
        node->setCenter(290.0 * cos(angle), 290.0 * sin(angle));
        node->setShape(shapes[distShape(rng)]);
        node->setSides(distSides(rng));
        node->setStyle(styles[distStyle(rng)]);
        node->setLabel(format("{}", i));
        const int center = i / 2.4;
        for (int offset = -2; offset <= 2; ++offset) {
            const auto& edge = diagram.addEdge(nodeName, format("n_{}", (center + offset + 17) % 17));
            edge->setArrowHead(arrows[distArrow(rng)]);
            edge->setArrowTail(arrows[distArrow(rng)]);
            edge->setStyle(styles[distStyle(rng)]);
        }
        diagram.addEdge(nodeName, format("n_o{}", (i + 1) % 41));
        const auto& edge = diagram.addEdge(nodeName, format("n_o{}", (i + 3) % 41));
        edge->addConnectionPoint(350.0 * cos(angle + shift), 350.0 * sin(angle + shift));
        edge->setArrowHead(arrows[distArrow(rng)]);
        edge->setArrowTail(arrows[distArrow(rng)]);
        edge->setStyle(styles[distStyle(rng)]);
    }
    diagram.render("example_random.svg");
}
