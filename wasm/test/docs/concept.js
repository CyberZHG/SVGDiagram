import { describe, it } from "mocha";
import { SVGDiagram } from "../../index.js";
import { compareSVG } from "./utils.js";

describe("Docs/Concept", () => {
    it("empty", async () => {
        const diagram = new SVGDiagram();
        const svg = diagram.render();
        await compareSVG("concept", "empty", svg);
    });
    it("node", async () => {
        const diagram = new SVGDiagram();
        const node = diagram.addNode("A");
        node.setCenter(0.0, 0.0);
        node.setLabel("foo\nbar");
        const svg = diagram.render();
        await compareSVG("concept", "node", svg);
    });
    it("edge", async () => {
        const diagram = new SVGDiagram();
        const node1 = diagram.addNode("A");
        node1.setCenter(0.0, 0.0);
        const node2 = diagram.addNode("B");
        node2.setCenter(60.0, 80.0);
        diagram.addEdge("A", "B");
        const svg = diagram.render();
        await compareSVG("concept", "edge", svg);
    });
});
