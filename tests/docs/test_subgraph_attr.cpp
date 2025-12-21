#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <format>
#include <vector>
#include <gtest/gtest.h>
using namespace svg_diagram;

static const auto OUTPUT_DIR = std::string("../docs/source/_static/subgraph_attr/");

TEST(TestDocsSubgraphAttributes, Inherited) {
    SVGDiagram diagram;
    auto subgraphInner = diagram.addSubgraph("subgraph-inner");
    const auto subgraphOuter = diagram.addSubgraph("subgraph-outer");
    subgraphOuter->addSubgraph(subgraphInner);

    auto node1 = diagram.addNode("A");
    node1->setLabel("A");
    node1->setCenter(0, 0);
    auto node2 = diagram.addNode("B");
    node2->setLabel("B");
    node2->setCenter(150, 0);
    auto edge1 = diagram.addEdge("A", "B");
    edge1->setArrowHead();
    subgraphInner->addNode(node1);
    subgraphInner->addNode(node2);
    subgraphInner->addEdge(edge1);
    subgraphInner->defaultNodeAttributes().setPenWidth(2);
    subgraphInner->defaultEdgeAttributes().setPenWidth(2);

    auto node3 = diagram.addNode("C");
    node3->setLabel("C");
    node3->setCenter(0, 60);
    auto node4 = diagram.addNode("D");
    node4->setLabel("D");
    node4->setCenter(150, 60);
    auto edge2 = diagram.addEdge("C", "D");
    edge2->setArrowHead();
    auto edge3 = diagram.addEdge("B", "C");
    edge3->setArrowHead();
    subgraphOuter->addNode(node3);
    subgraphOuter->addNode(node4);
    subgraphOuter->addEdge(edge2);
    subgraphOuter->addEdge(edge3);
    subgraphOuter->defaultNodeAttributes().setFillColor("lightgray");

    diagram.render(OUTPUT_DIR + "inherited.svg");
}

TEST(TestDocsSubgraphAttributes, Draw) {
    SVGDiagram diagram;
    auto subgraphInner = std::make_shared<SVGGraph>("subgraph-inner");
    subgraphInner->setLabel("Inner");
    subgraphInner->setColor("black");
    subgraphInner->setFillColor("lightgreen");
    const auto subgraphOuter = diagram.addSubgraph("subgraph-outer");
    subgraphOuter->addSubgraph(subgraphInner);
    subgraphOuter->setLabel("Outer");
    subgraphOuter->setColor("black");
    subgraphOuter->setFillColor("papayawhip");
    auto node1 = std::make_shared<SVGNode>("A");
    node1->setLabel("A");
    node1->setCenter(0, 0);
    auto node2 = std::make_shared<SVGNode>("B");
    node2->setLabel("B");
    node2->setCenter(150, 0);
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead();
    subgraphInner->addNode(node1);
    subgraphOuter->addNode(node2);
    diagram.render(OUTPUT_DIR + "draw.svg");
}