import { describe, it } from "mocha";
import {SVGDiagram} from "../../index.js";
import { compareSVG } from "./utils.js";

describe("Docs/DiagramAttributes", () => {
    it("backgroundColor", async () => {
        const diagram = new SVGDiagram();
        diagram.setBackgroundColor("lightgray");
        const node = diagram.addNode("A");
        node.setLabel("A");
        const svg = diagram.render();
        await compareSVG("diagram_attr", "background_color", svg);
    });
});
