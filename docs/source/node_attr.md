Node Attributes
===============

## Label

`SVGNode` can be configured to display text in a horizontal layout, and the size of its border is determined jointly by the text sizes and the margins.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

diagram = SVGDiagram()
node1 = diagram.add_node("A")
node1.set_center(0, 0)
node1.set_label("foobar")
node2 = diagram.add_node("B")
node2.set_center(150, 0)
node2.set_label("Pybind11\nEmscripten")
node3 = diagram.add_node("C")
node3.set_center(300, 0)
node3.set_label("物华天宝\n人杰地灵")
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

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
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("foobar");
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("Pybind11\nEmscripten");
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("物华天宝\n人杰地灵");
    diagram.render("label.svg");
    return 0;
}
````
`````

![](_static/node_attr/label.svg)

In the figure below, the blue rectangle represents the estimated text size, the red rectangle represents the text box plus the default margin, and the outer frame of the `SVGNode` is the smallest ellipse that can enclose the red rectangle.

![](_static/node_attr/label_debug.svg)
