import { describe, it } from "mocha";
import { SVGDiagram } from "../../index.js";
import { compareSVG } from "./utils.js";

describe("Docs/NodeAttributes", () => {
    it("label", async () => {
        const diagram = new SVGDiagram();
        const node1 = diagram.addNode("A");
        node1.setCenter(0.0, 0.0);
        node1.setLabel("foobar");
        const node2 = diagram.addNode("B");
        node2.setCenter(150.0, 0.0);
        node2.setLabel("Pybind11\nEmscripten");
        const node3 = diagram.addNode("C");
        node3.setCenter(300.0, 0.0);
        node3.setLabel("物华天宝\n人杰地灵");
        const svg = diagram.render();
        await compareSVG("node_attr", "label", svg);
    });
});
