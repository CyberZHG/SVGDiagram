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

## Arrow

You can set the arrow styles for the start and end points; by default, no arrows are applied.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram, SVGEdge

diagram = SVGDiagram()
arrow_types = [
    SVGEdge.ARROW_NONE,
    SVGEdge.ARROW_NORMAL,
    SVGEdge.ARROW_EMPTY,
]
for i, arrow in enumerate(arrow_types):
    y = i * 60.0
    tail_id, head_id = f"A{i}", f"B{i}"
    node1 = diagram.add_node(tail_id)
    node1.set_center(0, y)
    node1.set_label("A")
    node2 = diagram.add_node(head_id)
    node2.set_center(150, y)
    node2.set_label("B")
    edge = diagram.add_edge(tail_id, head_id)
    edge.set_arrow_tail(SVGEdge.ARROW_NONE)
    edge.set_arrow_head(arrow)
    edge.set_label(arrow)
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram, SVGEdge } from 'sp-svg-diagram';

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
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
#include <vector>
#include <format>
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto arrowTypes = std::vector{
        SVGEdge::ARROW_NONE,
        SVGEdge::ARROW_NORMAL,
        SVGEdge::ARROW_EMPTY,
    };
    for (int i = 0; i < static_cast<int>(arrowTypes.size()); i++) {
        const double y = i * 60.0;
        const auto tailNodeID = std::format("A{}", i);
        const auto headNodeID = std::format("B{}", i);
        const auto node1 = diagram.addNode(tailNodeID);
        node1->setCenter(0, y);
        node1->setLabel("A");
        const auto node2 = diagram.addNode(headNodeID);
        node2->setCenter(150, y);
        node2->setLabel("B");
        const auto edge = diagram.addEdge(tailNodeID, headNodeID);
        edge->setArrowTail(SVGEdge::ARROW_NONE);
        edge->setArrowHead(std::string(arrowTypes[i]));
        edge->setLabel(std::string(arrowTypes[i]));
    }
    diagram.render("arrow.svg");
    return 0;
}
````
`````

![](_static/edge_attr/arrow.svg)

## Label

By default, the text of an `SVGEdge` is positioned to the right of the arrow direction and centered along the edge (excluding the arrow length).

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

diagram = SVGDiagram()
node1 = diagram.add_node("A")
node1.set_center(0, 0)
node1.set_label("A")
node2 = diagram.add_node("B")
node2.set_center(150, 0)
node2.set_label("B")
edge1 = diagram.add_edge("A", "B")
edge1.set_arrow_head()
edge1.set_label("A → B")
edge1.add_connection_point(75, 20)
edge2 = diagram.add_edge("B", "A")
edge2.set_arrow_head()
edge2.set_label("A ← B")
edge2.add_connection_point(75, -20)
svg = diagram.render()
compare_svg("edge_attr", "label", svg)
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

const diagram = new SVGDiagram();
const node1 = diagram.addNode("A");
node1.setCenter(0, 0);
node1.setLabel("A");
const node2 = diagram.addNode("B");
node2.setCenter(150, 0);
node2.setLabel("B");
const edge1 = diagram.addEdge("A", "B");
edge1.setArrowHead();
edge1.setLabel("A → B");
edge1.addConnectionPoint(75, 20);
const edge2 = diagram.addEdge("B", "A");
edge2.setArrowHead();
edge2.setLabel("A ← B");
edge2.addConnectionPoint(75, -20);
const svg = diagram.render();
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("B");
    const auto edge1 = diagram.addEdge("A", "B");
    edge1->setArrowHead();
    edge1->setLabel("A → B");
    edge1->addConnectionPoint(75, 20);
    const auto edge2 = diagram.addEdge("B", "A");
    edge2->setArrowHead();
    edge2->setLabel("A ← B");
    edge2->addConnectionPoint(75, -20);
    diagram.render("label.svg");
    return 0;
}
````
`````

![](_static/edge_attr/label.svg)

## Color

You can set the color of the line and the font. The arrow color matches the line color and is independent of fill color.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram, SVGEdge

diagram = SVGDiagram()
node1 = diagram.add_node("A")
node1.set_center(0, 0)
node1.set_label("A")
node2 = diagram.add_node("B")
node2.set_center(150, 0)
node2.set_label("B")
edge = diagram.add_edge("A", "B")
edge.set_arrow_head(SVGEdge.ARROW_NORMAL)
edge.set_arrow_tail(SVGEdge.ARROW_EMPTY)
edge.set_label("color")
edge.set_color("red")
edge.set_font_color("blue")
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram, SVGEdge } from 'sp-svg-diagram';

const diagram = new SVGDiagram();
const node1 = diagram.addNode("A");
node1.setCenter(0, 0);
node1.setLabel("A");
const node2 = diagram.addNode("B");
node2.setCenter(150, 0);
node2.setLabel("B");
const edge = diagram.addEdge("A", "B");
edge.setArrowHead(SVGEdge.ARROW_NORMAL);
edge.setArrowTail(SVGEdge.ARROW_EMPTY);
edge.setLabel("color");
edge.setColor("red")
edge.setFontColor("blue")
const svg = diagram.render();
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("B");
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    edge->setLabel("color");
    edge->setColor("red");
    edge->setFontColor("blue");
    diagram.render("color.svg");
    return 0;
}
````
`````

![](_static/edge_attr/color.svg)

## Pen Width

The thickness of the line, which also affects the arrow.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram, SVGEdge

diagram = SVGDiagram()
node1 = diagram.add_node("A")
node1.set_center(0, 0)
node1.set_label("A")
node2 = diagram.add_node("B")
node2.set_center(150, 0)
node2.set_label("B")
edge = diagram.add_edge("A", "B")
edge.set_arrow_head(SVGEdge.ARROW_NORMAL)
edge.set_arrow_tail(SVGEdge.ARROW_EMPTY)
edge.set_label("penWidth=3")
edge.set_pen_width(3)
edge.set_margin(4, 4)
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram, SVGEdge } from 'sp-svg-diagram';

const diagram = new SVGDiagram();
const node1 = diagram.addNode("A");
node1.setCenter(0, 0);
node1.setLabel("A");
const node2 = diagram.addNode("B");
node2.setCenter(150, 0);
node2.setLabel("B");
const edge = diagram.addEdge("A", "B");
edge.setArrowHead(SVGEdge.ARROW_NORMAL);
edge.setArrowTail(SVGEdge.ARROW_EMPTY);
edge.setLabel("penWidth=3");
edge.setPenWidth(3);
edge.setMargin(4, 4);
const svg = diagram.render();
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("B");
    const auto edge = diagram.addEdge("A", "B");
    edge->setArrowHead(SVGEdge::ARROW_NORMAL);
    edge->setArrowTail(SVGEdge::ARROW_EMPTY);
    edge->setLabel("penWidth=3");
    edge->setPenWidth(3);
    edge->setMargin(4);
    diagram.render("pen_width.svg");
    return 0;
}
````
`````

![](_static/edge_attr/pen_width.svg)
