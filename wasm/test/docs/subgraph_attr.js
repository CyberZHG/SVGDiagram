import { describe, it } from "mocha";
import { SVGDiagram, createNode, createSubgraph } from "../../index.js";
import { compareSVG } from "./utils.js";

describe("Docs/SubgraphAttributes", () => {
    it("inherited", async () => {
        const diagram = new SVGDiagram();
        const subgraphInner = diagram.addSubgraph("subgraph-inner");
        const subgraphOuter = diagram.addSubgraph("subgraph-outer");
        subgraphOuter.addSubgraph(subgraphInner);

        const node1 = diagram.addNode("A");
        node1.setLabel("A");
        node1.setCenter(0, 0);
        const node2 = diagram.addNode("B");
        node2.setLabel("B");
        node2.setCenter(150, 0);
        const edge1 = diagram.addEdge("A", "B");
        edge1.setArrowHead();
        subgraphInner.addNode(node1);
        subgraphInner.addNode(node2);
        subgraphInner.addEdge(edge1);
        subgraphInner.defaultNodeAttributes().setPenWidth(2);
        subgraphInner.defaultEdgeAttributes().setPenWidth(2);

        const node3 = diagram.addNode("C");
        node3.setLabel("C");
        node3.setCenter(0, 60);
        const node4 = diagram.addNode("D");
        node4.setLabel("D");
        node4.setCenter(150, 60);
        const edge2 = diagram.addEdge("C", "D");
        edge2.setArrowHead();
        const edge3 = diagram.addEdge("B", "C");
        edge3.setArrowHead();
        subgraphOuter.addNode(node3);
        subgraphOuter.addNode(node4);
        subgraphOuter.addEdge(edge2);
        subgraphOuter.addEdge(edge3);
        subgraphOuter.defaultNodeAttributes().setFillColor("lightgray");

        const svg = diagram.render();
        await compareSVG("subgraph_attr", "inherited", svg);
    });
    it("draw", async () => {
        const diagram = new SVGDiagram();
        const subgraphInner = createSubgraph("subgraph-inner");
        subgraphInner.setLabel("Inner");
        subgraphInner.setColor("black");
        subgraphInner.setFillColor("lightgreen");
        const subgraphOuter = diagram.addSubgraph("subgraph-outer");
        subgraphOuter.addSubgraph(subgraphInner);
        subgraphOuter.setLabel("Outer");
        subgraphOuter.setColor("black");
        subgraphOuter.setFillColor("papayawhip");
        const node1 = createNode("A");
        node1.setLabel("A");
        node1.setCenter(0, 0);
        const node2 = createNode("B");
        node2.setLabel("B");
        node2.setCenter(150, 0);
        const edge = diagram.addEdge("A", "B");
        edge.setArrowHead();
        subgraphInner.addNode(node1);
        subgraphOuter.addNode(node2);
        const svg = diagram.render();
        await compareSVG("subgraph_attr", "draw", svg);
    });
});
