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
node3.set_label("星分翼轸\n地接衡庐")
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
node3.setLabel("星分翼轸\n地接衡庐");
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
    node3->setLabel("星分翼轸\n地接衡庐");
    diagram.render("label.svg");
    return 0;
}
````
`````

![](_static/node_attr/label.svg)

In the figure below, the blue rectangle represents the estimated text size, the red rectangle represents the text box plus the default margin, and the outer frame of the `SVGNode` is the smallest ellipse that can enclose the red rectangle.

![](_static/node_attr/label_debug.svg)

## Shape

The default border shape of an SVGNode is an ellipse.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram, SVGNode

diagram = SVGDiagram()
shapes = [
    SVGNode.SHAPE_ELLIPSE,
    SVGNode.SHAPE_NONE,
    SVGNode.SHAPE_CIRCLE,
    SVGNode.SHAPE_DOUBLE_CIRCLE,
    SVGNode.SHAPE_RECT,
]
for i, shape in enumerate(shapes):
    node = diagram.add_node(shape)
    node.set_shape(shape)
    node.set_center((i % 3) * 150.0, (i // 3) * 100.0)
    node.set_label(shape)
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram, SVGNode } from 'sp-svg-diagram';

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
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
#include <string>
#include <vector>
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto shapes = std::vector{
        SVGNode::NODE_SHAPE_ELLIPSE,
        SVGNode::NODE_SHAPE_NONE,
        SVGNode::NODE_SHAPE_CIRCLE,
        SVGNode::NODE_SHAPE_DOUBLE_CIRCLE,
        SVGNode::NODE_SHAPE_RECT,
    };
    for (int i = 0; i < static_cast<int>(shapes.size()); ++i) {
        const auto shape = std::string(shapes[i]);
        const auto node = diagram.addNode(std::string(shapes[i]));
        node->setShape(shapes[i]);
        node->setCenter((i % 3) * 150.0, (i / 3) * 100.0);
        node->setLabel(shape);
    }
    diagram.render("shape.svg");
    return 0;
}
````
`````

![](_static/node_attr/shape.svg)

The figure below illustrates the relationship between the border size and the text:

![](_static/node_attr/shape_debug.svg)

## Margin

You can set horizontal and vertical margins. The default values are 8 and 4 respectively.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

diagram = SVGDiagram()
node1 = diagram.add_node("A")
node1.set_center(0, 0)
node1.set_label("Larger\nMargin")
node1.set_margin(32, 8)
node2 = diagram.add_node("B")
node2.set_center(150, 0)
node2.set_label("No\nMargin")
node2.set_margin(0, 0)
node3 = diagram.add_node("C")
node3.set_center(300, 0)
node3.set_label("Negative\nMargin")
node3.set_margin(-10, -10)
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

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
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setCenter(0, 0);
    node1->setLabel("Larger\nMargin");
    node1->setMargin(32, 8);
    const auto node2 = diagram.addNode("B");
    node2->setCenter(150, 0);
    node2->setLabel("No\nMargin");
    node2->setMargin(0);
    const auto node3 = diagram.addNode("C");
    node3->setCenter(300, 0);
    node3->setLabel("Negative\nMargin");
    node3->setMargin(-10);
    diagram.render("margin.svg");
    return 0;
}
````
`````

![](_static/node_attr/margin.svg)

Although negative margins can be specified, undefined behavior will occur if the absolute value exceeds half of the text size.

![](_static/node_attr/margin_debug.svg)

## Text Size

By default, the library estimates text size. In the C++ version, you can get a better estimation with the `SVG_DIAGRAM_ENABLE_PANGO_CAIRO` compile option. If you are able to use a different approach to calculate or better estimate text sizes, you can also fix the text box size by configuring the relevant properties.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

diagram = SVGDiagram()
node1 = diagram.add_node("A")
node1.set_label("🐱🐶🙈🙉🙊")
node2 = diagram.add_node("B")
node2.set_center(0, 50)
node2.set_label("🐱🐶🙈🙉🙊")
node2.set_text_size(80, 16)
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

const diagram = new SVGDiagram();
const node1 = diagram.addNode("A");
node1.setLabel("🐱🐶🙈🙉🙊");
const node2 = diagram.addNode("B");
node2.setCenter(0, 50);
node2.setLabel("🐱🐶🙈🙉🙊");
node2.setTextSize(80, 16);
const svg = diagram.render();
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setLabel("🐱🐶🙈🙉🙊");
    const auto node2 = diagram.addNode("B");
    node2->setLabel("🐱🐶🙈🙉🙊");
    node2->setCenter(0, 50);
    node2->setPrecomputedTextSize(80, 16);
    diagram.render("text_size.svg");
    return 0;
}
````
`````

![](_static/node_attr/text_size.svg)

In the figure below, the blue rectangle represents the size of the text:

![](_static/node_attr/text_size_debug.svg)

## Node Size

You can directly set the size of an `SVGNode`. When this property is set, both the text size and margin will be ignored.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

diagram = SVGDiagram()
node1 = diagram.add_node("A")
node1.set_label("A")
node2 = diagram.add_node("B")
node2.set_label("B")
node2.set_center(150, 0)
node2.set_fixed_size(80, 30)
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

const diagram = new SVGDiagram();
const node1 = diagram.addNode("A");
node1.setLabel("A");
const node2 = diagram.addNode("B");
node2.setLabel("B");
node2.setCenter(150, 0);
node2.setFixedSize(80, 30);
const svg = diagram.render();
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setLabel("A");
    const auto node2 = diagram.addNode("B");
    node2->setLabel("B");
    node2->setCenter(150, 0);
    node2->setFixedSize(80, 30);
    diagram.render("node_size.svg");
    return 0;
}
````
`````

![](_static/node_attr/node_size.svg)

## Color

There are three color-related properties: `color` sets the node's border color, `fillColor` sets the node's fill color, and `fontColor` sets the text color. Any color format supported by SVG can be used.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

diagram = SVGDiagram()
node = diagram.add_node("A")
node.set_label("color")
node.set_color("limegreen")
node.set_fill_color("#EEEEEE")
node.set_font_color("rgb(66,92,214)")
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

const diagram = new SVGDiagram();
const node = diagram.addNode("A");
node.setLabel("color");
node.setColor("limegreen");
node.setFillColor("#EEEEEE");
node.setFontColor("rgb(66,92,214)");
const svg = diagram.render();
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto node = diagram.addNode("A");
    node->setLabel("color");
    node->setColor("limegreen");
    node->setFillColor("#EEEEEE");
    node->setFontColor("rgb(66,92,214)");
    diagram.render("color.svg");
    return 0;
}
````
`````

![](_static/node_attr/color.svg)

## Pen Width

The stroke width of the node's border.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

diagram = SVGDiagram()
for i in range(3):
    pen_width = 1 + i * 2
    node = diagram.add_node(f"node{i}")
    node.set_center(i * 150, 0)
    node.set_label(f"penWidth={pen_width}")
    node.set_pen_width(pen_width)
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

const diagram = new SVGDiagram();
for (let i = 0; i < 3; i++) {
    const penWidth = 1 + i * 2;
    const node = diagram.addNode(`node${i}`);
    node.setCenter(i * 150, 0);
    node.setLabel(`penWidth=${penWidth}`);
    node.setPenWidth(penWidth);
}
const svg = diagram.render();
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
#include <format>
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    for (int i = 0; i < 3; ++i) {
        const auto penWidth = 1 + i * 2;
        const auto node = diagram.addNode(std::format("node{}", i));
        node->setCenter(i * 150, 0);
        node->setLabel(std::format("penWidth={}", penWidth));
        node->setPenWidth(penWidth);
    }
    diagram.render("pen_width.svg");
    return 0;
}
````
`````

![](_static/node_attr/pen_width.svg)

## Font

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

diagram = SVGDiagram()
for i in range(3):
    font_size = 14 + i
    node = diagram.add_node(f"node{i}")
    node.set_center(i * 150, 0)
    node.set_label(f"fontSize={font_size}")
    node.set_font_name("Consolas")
    node.set_font_size(font_size)
    node.set_font("Consolas,'Courier New',monospace", font_size)
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

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
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
#include <format>
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    for (int i = 0; i < 3; ++i) {
        const auto fontSize = 14 + i;
        const auto node = diagram.addNode(std::format("node{}", i));
        node->setCenter(i * 150, 0);
        node->setLabel(std::format("fontSize={}", fontSize));
        node->setFontName("Consolas");
        node->setFontSize(fontSize);
        node->setFont("Consolas,'Courier New',monospace", fontSize);
    }
    diagram.render("font.svg");
    return 0;
}
````
`````

![](_static/node_attr/font.svg)

## Stroke Style

The default node style is `filled`. As long as either `color` or `fillColor` is set, both the border and the fill will be rendered. The node border also supports two dashed styles, `dashed` and `dotted`; if both are specified, the style that appears last takes precedence.

`````{tab-set}
````{tab-item} Python
```python
from sp_svg_diagram import SVGDiagram

diagram = SVGDiagram()
labels = ["filled", "dashed", "dotted"]
for i, label in enumerate(labels):
    node = diagram.add_node(f"node{i}")
    node.set_center(i * 150, 0)
    node.set_label(label)
    node.set_fill_color("lightgray")
    if i == 1:
        node.append_style_dashed()  # The style is "filled,dashed"
    elif i == 2:
        node.append_style_dotted()  # The style is "filled,dotted"
svg = diagram.render()
```
````
````{tab-item} JavaScript
```javascript
import { SVGDiagram } from 'sp-svg-diagram';

const diagram = new SVGDiagram();
const labels = ["filled", "dashed", "dotted"]
for (const [i, label] of labels.entries()) {
    const node = diagram.addNode(`node${i}`);
    node.setCenter(i * 150, 0);
    node.setLabel(labels[i]);
    node.setFillColor("lightgray");
    if (i === 1) {
        node.appendStyleDashed();  // The style is "filled,dashed"
    } else if (i === 2) {
        node.appendStyleDotted();  // The style is "filled,dotted"
    }
}
const svg = diagram.render();
````

````{tab-item} C++
```c++
#include "svg_diagram.h"
#include <format>
#include <vector>
#include <string>
using namespace svg_diagram;

int main() {
    SVGDiagram diagram;
    const auto labels = std::vector<std::string>({"filled", "dashed", "dotted"});
    for (int i = 0; i < static_cast<int>(labels.size()); ++i) {
        const auto node = diagram.addNode(std::format("node{}", i));
        node->setCenter(i * 150, 0);
        node->setLabel(labels[i]);
        node->setFillColor("lightgray");
        if (i == 1) {
            node->appendStyleDashed();  // The style is "filled,dashed"
        } else if (i == 2) {
            node->appendStyleDotted();  // The style is "filled,dotted"
        }
    }
    diagram.render("stroke_style.svg");
    return 0;
}
````
`````

![](_static/node_attr/stroke_style.svg)
