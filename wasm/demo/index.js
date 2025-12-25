import { SVGDiagram } from 'sp-svg-diagram';
import { writeFile } from 'fs/promises';

const diagram = new SVGDiagram();
const nodeA = diagram.addNode("a");
nodeA.setCenter(0.0, 0.0);
nodeA.setLabel("foo");
const nodeB = diagram.addNode("b");
nodeB.setCenter(100.0, 100.0);
nodeB.setLabel("bar");
diagram.addEdge("a", "b");
await writeFile("demo.svg", diagram.render());
