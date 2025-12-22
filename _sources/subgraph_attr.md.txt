Subgraph Attributes
===================

`SVGGraph` is used to set default properties for a group of nodes or edges and does not render anything by default. Subgraphs can also be nested within an `SVGGraph`, with default properties inherited hierarchically.

## Inherited Attributes

In this example, there are two levels of subgraphs. The inner subgraph contains nodes A and B, with both the nodes and edges having `penWidth` set to 2. The outer subgraph contains the inner subgraph as well as nodes C and D, and sets the nodes' fill color to `lightgray`. Although the inner subgraph does not specify a fill color, nodes A and B inherit the default fill color from the outer subgraph.


`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

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
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

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
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
#include <vector>
#include <format>
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    auto subgraphInner = diagram.addSubgraph("subgraph-inner");
    const auto subgraphOuter = diagram.addSubgraph("subgraph-outer");
    subgraphOuter->addSubgraph(subgraphInner);

    auto node1 = diagram.addNode("A");
    node1->setLabel("A");
    node1->setCenter(0, 0);
    auto node2 = diagram.addNode("B");
    node2->setLabel("B");
    node2->setCenter(150, 0);
    auto edge1 = diagram.addEdge("A", "B");
    edge1->setArrowHead();
    subgraphInner->addNode(node1);
    subgraphInner->addNode(node2);
    subgraphInner->addEdge(edge1);
    subgraphInner->defaultNodeAttributes().setPenWidth(2);
    subgraphInner->defaultEdgeAttributes().setPenWidth(2);

    auto node3 = diagram.addNode("C");
    node3->setLabel("C");
    node3->setCenter(0, 60);
    auto node4 = diagram.addNode("D");
    node4->setLabel("D");
    node4->setCenter(150, 60);
    auto edge2 = diagram.addEdge("C", "D");
    edge2->setArrowHead();
    auto edge3 = diagram.addEdge("B", "C");
    edge3->setArrowHead();
    subgraphOuter->addNode(node3);
    subgraphOuter->addNode(node4);
    subgraphOuter->addEdge(edge2);
    subgraphOuter->addEdge(edge3);
    subgraphOuter->defaultNodeAttributes().setFillColor("lightgray");

    diagram.render("inherited.svg");
    return 0;
}
````
`````

![](_static/subgraph_attr/inherited.svg)

## Color & Label

When properties such as color, fill color, or label are set for a subgraph, the subgraph will also be displayed. The shape of a subgraph is always rectangular, and its text is always centered above the subgraph. The rectangle of the subgraph encloses all its child nodes, edges, and subgraphs.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram, SVGNode, SVGSubgraph

diagram = SVGDiagram()
subgraph_inner = SVGGraph("subgraph-inner")
subgraph_inner.set_label("Inner")
subgraph_inner.set_color("black")
subgraph_inner.set_fill_color("lightgreen")

subgraph_outer = diagram.add_subgraph("subgraph-outer")
subgraph_outer.add_subgraph(subgraph_inner)
subgraph_outer.set_label("Outer")
subgraph_outer.set_color("black")
subgraph_outer.set_fill_color("papayawhip")

node1 = SVGNode("A")
node1.set_label("A")
node1.set_center(0, 0)
node2 = SVGNode("B")
node2.set_label("B")
node2.set_center(150, 0)
edge = diagram.add_edge("A", "B")
edge.set_arrow_head()
subgraph_inner.add_node(node1)
subgraph_outer.add_node(node2)

svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram, createSVGNode, createSVGGraph } from 'sp-svg-diagram';

const diagram = new SVGDiagram();
const subgraphInner = createSVGGraph("subgraph-inner");
subgraphInner.setLabel("Inner");
subgraphInner.setColor("black");
subgraphInner.setFillColor("lightgreen");
const subgraphOuter = diagram.addSubgraph("subgraph-outer");
subgraphOuter.addSubgraph(subgraphInner);
subgraphOuter.setLabel("Outer");
subgraphOuter.setColor("black");
subgraphOuter.setFillColor("papayawhip");
const node1 = createSVGNode("A");
node1.setLabel("A");
node1.setCenter(0, 0);
const node2 = createSVGNode("B");
node2.setLabel("B");
node2.setCenter(150, 0);
const edge = diagram.addEdge("A", "B");
edge.setArrowHead();
subgraphInner.addNode(node1);
subgraphOuter.addNode(node2);
const svg = diagram.render();
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
#include <vector>
#include <format>
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    auto subgraphInner = std::make_shared<SVGGraph>("subgraph-inner");
    subgraphInner->setLabel("Inner");
    subgraphInner->setColor("black");
    subgraphInner->setFillColor("lightgreen");
    const auto subgraphOuter = diagram.addSubgraph("subgraph-outer");
    subgraphOuter->addSubgraph(subgraphInner);
    subgraphOuter->setLabel("Outer");
    subgraphOuter->setColor("black");
    subgraphOuter->setFillColor("papayawhip");
    auto node1 = std::make_shared<SVGNode>("A");
    node1->setLabel("A");
    node1->setCenter(0, 0);
    auto node2 = std::make_shared<SVGNode>("B");
    node2->setLabel("B");
    node2->setCenter(150, 0);
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead();
    subgraphInner->addNode(node1);
    subgraphOuter->addNode(node2);
    diagram.render("draw.svg");
    return 0;
}
````
`````

![](_static/subgraph_attr/draw.svg)
