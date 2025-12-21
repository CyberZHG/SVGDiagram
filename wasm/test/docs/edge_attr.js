import { describe, it } from "mocha";
import {SVGDiagram, SVGEdge} from "../../index.js";
import { compareSVG } from "./utils.js";

describe("Docs/EdgeAttributes", () => {
    it("splines", async () => {
        const diagram = new SVGDiagram();
        const splinesTypes = [
            SVGEdge.SPLINES_SPLINE,
            SVGEdge.SPLINES_LINE,
        ];
        for (const [i, splines] of splinesTypes.entries()) {
            const y = i * 80.0;
            const tailID = `A${i}`;
            const headID = `B${i}`;
            const node1 = diagram.addNode(tailID);
            node1.setCenter(0, y);
            node1.setLabel("A");
            const node2 = diagram.addNode(headID);
            node2.setCenter(150, y);
            node2.setLabel("B");
            const edge = diagram.addEdge(tailID, headID);
            edge.setSplines(splines);
            edge.addConnectionPoint(50, y - 20);
            edge.addConnectionPoint(100, y + 20);
            edge.setLabel(splines);
        }
        const svg = diagram.render();
        await compareSVG("edge_attr", "splines", svg);
    });
    it("arrow", async () => {
        const diagram = new SVGDiagram();
        const arrowTypes = [
            SVGEdge.ARROW_NONE,
            SVGEdge.ARROW_NORMAL,
            SVGEdge.ARROW_EMPTY,
        ];
        for (const [i, arrow] of arrowTypes.entries()) {
            const y = i * 60.0;
            const tailID = `A${i}`;
            const headID = `B${i}`;
            const node1 = diagram.addNode(tailID);
            node1.setCenter(0, y);
            node1.setLabel("A");
            const node2 = diagram.addNode(headID);
            node2.setCenter(150, y);
            node2.setLabel("B");
            const edge = diagram.addEdge(tailID, headID);
            edge.setArrowTail(SVGEdge.ARROW_NONE);
            edge.setArrowHead(arrow);
            edge.setLabel(arrow);
        }
        const svg = diagram.render();
        await compareSVG("edge_attr", "arrow", svg);
    });
});
