import { describe, it } from 'mocha';
import { strict as assert } from 'assert';
import { SVGDiagram } from '../index.js';

describe('Init', () => {
    it('init', () => {
        const diagram = new SVGDiagram();
        const nodeA = diagram.addNode("a");
        nodeA.setCenter(0.0, 0.0);
        nodeA.setLabel("foo");
        const nodeB = diagram.addNode("b");
        nodeB.setCenter(100.0, 100.0);
        nodeB.setLabel("bar");
        diagram.addEdge("a", "b");
        const svg = diagram.render();
        diagram.toSVG("init.svg", svg);
        assert(svg.length > 0);
    });
});