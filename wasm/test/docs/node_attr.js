import { describe, it } from "mocha";
import { SVGDiagram, SVGNode } from "../../index.js";
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
    it("shape", async () => {
        const diagram = new SVGDiagram();
        const shapes = [
            SVGNode.SHAPE_ELLIPSE,
            SVGNode.SHAPE_NONE,
            SVGNode.SHAPE_CIRCLE,
            SVGNode.SHAPE_DOUBLE_CIRCLE,
            SVGNode.SHAPE_RECT,
        ];
        for (const [i, shape] of shapes.entries()) {
            console.log(shape);
            const node = diagram.addNode(shape);
            node.setShape(shape);
            node.setCenter((i % 3) * 150.0, Math.floor(i / 3) * 100.0);
            node.setLabel(shape);
        }
        const svg = diagram.render();
        await compareSVG("node_attr", "shape", svg);
    });
});
