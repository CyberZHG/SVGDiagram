Edge Attributes
===============

## Splines

When connection points are provided, the `splines` of an `SVGEdge` default to cubic Bézier curves.


`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram, SVGEdge

diagram = SVGDiagram()
splines_types = [
    SVGEdge.SPLINES_SPLINE,
    SVGEdge.SPLINES_LINE,
]
for i, splines in enumerate(splines_types):
    y = i * 80.0
    tail_id, head_id = f"A{i}", f"B{i}"
    node1 = diagram.add_node(tail_id)
    node1.set_center(0, y)
    node1.set_label("A")
    node2 = diagram.add_node(head_id)
    node2.set_center(150, y)
    node2.set_label("B")
    edge = diagram.add_edge(tail_id, head_id)
    edge.set_splines(splines)
    edge.add_connection_point(50, y - 20)
    edge.add_connection_point(100, y + 20)
    edge.set_label(splines)
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram, SVGEdge } from 'sp-svg-diagram';

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
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
#include <vector>
#include <format>
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto splinesTypes = std::vector{
        SVGEdge::SPLINES_SPLINE,
        SVGEdge::SPLINES_LINE,
    };
    for (int i = 0; i < static_cast<int>(splinesTypes.size()); i++) {
        const double y = i * 80.0;
        const auto tailNodeID = std::format("A{}", i);
        const auto headNodeID = std::format("B{}", i);
        const auto node1 = diagram.addNode(tailNodeID);
        node1->setCenter(0, y);
        node1->setLabel("A");
        const auto node2 = diagram.addNode(headNodeID);
        node2->setCenter(150, y);
        node2->setLabel("B");
        const auto edge = diagram.addEdge(tailNodeID, headNodeID);
        edge->setSplines(splinesTypes[i]);
        edge->addConnectionPoint(50, y - 20);
        edge->addConnectionPoint(100, y + 20);
        edge->setLabel(std::string(splinesTypes[i]));
    }
    diagram.render("splines.svg");
    return 0;
}
````
`````

![](_static/edge_attr/splines.svg)

In the figure below, you can see the tangent directions of the curve at the connection points.

![](_static/edge_attr/splines_debug.svg)
