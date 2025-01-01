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
        node3.setLabel("星分翼轸\n地接衡庐");
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
            const node = diagram.addNode(shape);
            node.setShape(shape);
            node.setCenter((i % 3) * 150.0, Math.floor(i / 3) * 100.0);
            node.setLabel(shape);
        }
        const svg = diagram.render();
        await compareSVG("node_attr", "shape", svg);
    });
    it("margin", async () => {
        const diagram = new SVGDiagram();
        const node1 = diagram.addNode("A");
        node1.setCenter(0, 0);
        node1.setLabel("Larger\nMargin");
        node1.setMargin(32, 8);
        const node2 = diagram.addNode("B");
        node2.setCenter(150, 0);
        node2.setLabel("No\nMargin");
        node2.setMargin(0, 0);
        const node3 = diagram.addNode("C");
        node3.setCenter(300, 0);
        node3.setLabel("Negative\nMargin");
        node3.setMargin(-10, -10);
        const svg = diagram.render();
        await compareSVG("node_attr", "margin", svg);
    });
    it("textSize", async () => {
        const diagram = new SVGDiagram();
        const node1 = diagram.addNode("A");
        node1.setLabel("🐱🐶🙈🙉🙊");
        const node2 = diagram.addNode("B");
        node2.setCenter(0, 50);
        node2.setLabel("🐱🐶🙈🙉🙊");
        node2.setTextSize(80, 16);
        const svg = diagram.render();
        await compareSVG("node_attr", "text_size", svg);
    });
    it("nodeSize", async () => {
        const diagram = new SVGDiagram();
        const node1 = diagram.addNode("A");
        node1.setLabel("A");
        const node2 = diagram.addNode("B");
        node2.setLabel("B");
        node2.setCenter(150, 0);
        node2.setFixedSize(80, 30);
        const svg = diagram.render();
        await compareSVG("node_attr", "node_size", svg);
    });
    it("color", async () => {
        const diagram = new SVGDiagram();
        const node = diagram.addNode("A");
        node.setLabel("color");
        node.setColor("limegreen");
        node.setFillColor("#EEEEEE");
        node.setFontColor("rgb(66,92,214)");
        const svg = diagram.render();
        await compareSVG("node_attr", "color", svg);
    });
    it("penWidth", async () => {
        const diagram = new SVGDiagram();
        for (let i = 0; i < 3; i++) {
            const penWidth = 1 + i * 2;
            const node = diagram.addNode(`node${i}`);
            node.setCenter(i * 150, 0);
            node.setLabel(`penWidth=${penWidth}`);
            node.setPenWidth(penWidth);
        }
        const svg = diagram.render();
        await compareSVG("node_attr", "pen_width", svg);
    });
    it("font", async () => {
        const diagram = new SVGDiagram();
        for (let i = 0; i < 3; i++) {
            const fontSize = 14 + i;
            const node = diagram.addNode(`node${i}`);
            node.setCenter(i * 150, 0);
            node.setLabel(`fontSize=${fontSize}`);
            node.setFontName("Consolas")
            node.setFontSize(fontSize)
            node.setFont("Consolas,'Courier New',monospace", fontSize)
        }
        const svg = diagram.render();
        await compareSVG("node_attr", "font", svg);
    });
    it("strokeStyle", async () => {
        const diagram = new SVGDiagram();
        const labels = ["solid", "dashed", "dotted"]
        for (const [i, label] of labels.entries()) {
            const node = diagram.addNode(`node${i}`);
            node.setCenter(i * 150, 0);
            node.setLabel(labels[i]);
            if (i === 1) {
                node.appendStyleDashed();
            } else if (i === 2) {
                node.appendStyleDotted();
            }
        }
        const svg = diagram.render();
        await compareSVG("node_attr", "stroke_style", svg);
    });
});
