#include "svg_diagram.h"

#include <cmath>
#include <numbers>
#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestExample, Subgraph) {
    SVGDiagram diagram;
    diagram.defaultNodeAttributes().setMargin(10, 20);
    diagram.defaultEdgeAttributes().setMargin(4.0);
    diagram.defaultEdgeAttributes().setArrowHead();

    const auto labels = vector{
        "O Lips, \nWeave Me Songs and Psalms",
        "Twine Warnings and \nTales From the North",
        "Seek Not to Tread \nthe Sly Fox's Path",
        "Nor Yearn for \nthe Great Bear's Might",
        "If Truth May \nBe Subject to Witness",
        "I Offer Blood and \nTears to the Moonlight",
    };
    const auto strokeColors = vector{"darkgrey", "peru", "darkgoldenrod", "limegreen", "dodgerblue", "lightcoral"};
    const auto fillColors = vector{"floralwhite", "lightsalmon", "papayawhip", "lightgreen", "deepskyblue", "lightpink"};
    const auto textColors = vector{"black", "saddlebrown", "goldenrod", "olivedrab", "royalblue", "indianred", "indigo"};
    const auto centers = vector<pair<double, double>>{
        {-100, 50}, {100, 50},
        {-150, 120}, {-50, 120}, {50, 120}, {150, 120},
    };

    const auto startNode = diagram.addNode("start");
    startNode->setShape(SVGNode::NODE_SHAPE_CIRCLE);
    startNode->setLabel("START");
    startNode->setFontColor("white");
    startNode->setFillColor("darkgrey");
    startNode->setColor("none");
    vector<shared_ptr<SVGNode>> nodes(6);
    vector<shared_ptr<SVGEdge>> edges(6);
    for (int i = 0; i < 6; ++i) {
        const auto [cx, cy] = centers[i];
        nodes[i] = make_shared<SVGNode>(cx * 2.5, cy * 2.5);
        nodes[i]->setID(format("node_{}", i));
        nodes[i]->setLabel(labels[i]);
        nodes[i]->setColor(strokeColors[i]);
        nodes[i]->setFillColor(fillColors[i]);
        nodes[i]->setFontColor(textColors[i]);

        edges[i] = make_shared<SVGEdge>();
        edges[i]->setID(format("edge_{}", i));
        edges[i]->setColor(strokeColors[i]);
        edges[i]->setLabel(format("C{}", i));
        edges[i]->setFontColor(strokeColors[i]);
    }
    edges[0]->setNodeFrom("start"); edges[0]->setNodeTo("node_0");
    edges[1]->setNodeFrom("start"); edges[1]->setNodeTo("node_1");
    edges[2]->setNodeFrom("node_0"); edges[2]->setNodeTo("node_2");
    edges[3]->setNodeFrom("node_0"); edges[3]->setNodeTo("node_3");
    edges[4]->setNodeFrom("node_1"); edges[4]->setNodeTo("node_4");
    edges[5]->setNodeFrom("node_1"); edges[5]->setNodeTo("node_5");

    auto leftBottomSubgraph = make_shared<SVGGraph>("LBG");
    leftBottomSubgraph->defaultNodeAttributes().setShape(SVGNode::NODE_SHAPE_RECT);
    leftBottomSubgraph->addNode(nodes[2]);
    leftBottomSubgraph->addNode(nodes[3]);
    leftBottomSubgraph->addEdge(edges[2]);
    leftBottomSubgraph->addEdge(edges[3]);
    leftBottomSubgraph->setColor("white");
    leftBottomSubgraph->setFontColor("white");
    leftBottomSubgraph->setLabel("Left Bottom");
    leftBottomSubgraph->setPenWidth(5.0);
    auto rightBottomSubgraph = make_shared<SVGGraph>("RBG");
    rightBottomSubgraph->defaultNodeAttributes().setShape(SVGNode::NODE_SHAPE_RECT);
    rightBottomSubgraph->addNode(nodes[4]);
    rightBottomSubgraph->addNode(nodes[5]);
    rightBottomSubgraph->addEdge(edges[4]);
    rightBottomSubgraph->addEdge(edges[5]);
    rightBottomSubgraph->setColor("black");
    rightBottomSubgraph->setLabel("Right Bottom");
    rightBottomSubgraph->setPenWidth(5.0);

    const auto leftSubgraph = diagram.addSubgraph("LG");
    leftSubgraph->defaultEdgeAttributes().setPenWidth(5.0);
    leftSubgraph->addNode(nodes[0]);
    leftSubgraph->addEdge(edges[0]);
    leftSubgraph->addSubgraph(leftBottomSubgraph);
    leftSubgraph->setFillColor("black");
    leftSubgraph->setFontColor("white");
    leftSubgraph->setLabel("Left Subgraph");
    const auto rightSubgraph = diagram.addSubgraph("RG");
    rightSubgraph->defaultNodeAttributes().setPenWidth(5.0);
    rightSubgraph->addNode(nodes[1]);
    rightSubgraph->addEdge(edges[1]);
    rightSubgraph->addSubgraph(rightBottomSubgraph);
    rightSubgraph->setFillColor("white");
    rightSubgraph->setLabel("Right Subgraph");


    diagram.render("example_subgraph.svg");
}