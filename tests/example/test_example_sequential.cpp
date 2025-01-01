#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestExample, Sequential) {
    SVGDiagram diagram;

    const auto labels = vector{
        "Part the Veil of Snow",
        "The Devil's Wall",
        "Stranger in the Night",
        "Night on Bald Mountain",
        "Exile's Shadow",
        "Songs and Dances of Death",
    };
    const auto strokeColors = vector{"darkgrey", "peru", "darkgoldenrod", "limegreen", "dodgerblue", "lightcoral"};
    const auto fillColors = vector{"floralwhite", "lightsalmon", "papayawhip", "lightgreen", "deepskyblue", "lightpink"};
    const auto textColors = vector{"black", "saddlebrown", "goldenrod", "olivedrab", "royalblue", "indianred", "indigo"};

    for (int i = 0; i < 6; ++i) {
        constexpr double X_SHIFT = 100.0;
        constexpr double Y_SHIFT = 80.0;

        const auto& node = diagram.addNode(format("node_{}", i));
        node->setCenter(i * X_SHIFT, i * Y_SHIFT);
        node->setLabel(labels[i]);
        node->setShape(SVGNode::NODE_SHAPE_RECT);
        node->setMarginInPixels(10, 20);
        node->setColor(strokeColors[i]);
        node->setFillColor(fillColors[i]);
        node->setFontColor(textColors[i]);
        node->setPenWidth(i + 1);

        if (i < 5) {
            const auto from = format("node_{}", i);
            const auto to = format("node_{}", i + 1);
            const auto& edge = diagram.addEdge(from, to);
            edge->addConnectionPoint((i - 0.5) * X_SHIFT, (i + 0.75) * Y_SHIFT);
            edge->setArrowHead();
            edge->setColor(strokeColors[i]);
            edge->setPenWidth(1 + i * 0.25);
        }
    }

    diagram.render("example_sequential.svg");
}