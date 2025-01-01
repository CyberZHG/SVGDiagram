#include "svg_diagram.h"
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("foo");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(100, 50);
    node2->setLabel("bar");
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead();
    diagram.render("demo.svg");
    return 0;
}