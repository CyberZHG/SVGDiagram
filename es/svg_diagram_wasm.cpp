#include <functional>

#include "svg_diagram.h"

#include <string>
#include <memory>
#include <emscripten/bind.h>

#include "svg_diagram.h"
using namespace emscripten;
using namespace svg_diagram;

const auto __BIND__NODE_SHAPE_NONE = std::string(SVGNode::NODE_SHAPE_NONE);
const auto __BIND__NODE_SHAPE_CIRCLE = std::string(SVGNode::NODE_SHAPE_CIRCLE);
const auto __BIND__NODE_SHAPE_DOUBLE_CIRCLE = std::string(SVGNode::NODE_SHAPE_DOUBLE_CIRCLE);
const auto __BIND__NODE_SHAPE_RECT = std::string(SVGNode::NODE_SHAPE_RECT);
const auto __BIND__NODE_SHAPE_ELLIPSE = std::string(SVGNode::NODE_SHAPE_ELLIPSE);

EMSCRIPTEN_BINDINGS(SVGDiagramWASM) {
    constant("NODE_SHAPE_NONE", __BIND__NODE_SHAPE_NONE);
    constant("NODE_SHAPE_CIRCLE", __BIND__NODE_SHAPE_CIRCLE);
    constant("NODE_SHAPE_DOUBLE_CIRCLE", __BIND__NODE_SHAPE_DOUBLE_CIRCLE);
    constant("NODE_SHAPE_RECT", __BIND__NODE_SHAPE_RECT);
    constant("NODE_SHAPE_ELLIPSE", __BIND__NODE_SHAPE_ELLIPSE);
    class_<SVGItem>("SVGItem")
        .constructor<>()
        .smart_ptr<std::shared_ptr<SVGItem>>("SVGItem")
        .function("setLabel", &SVGItem::setLabel)
        .function("setFixedSize", &SVGItem::setFixedSize)
        .function("setTextSize", &SVGItem::setPrecomputedTextSize)
        .function("setMargin", select_overload<void(double, double)>(&SVGItem::setMargin))
        .function("setColor", &SVGItem::setColor)
        .function("setFillColor", &SVGItem::setFillColor)
        .function("setFontColor", &SVGItem::setFontColor)
        .function("setPenWidth", &SVGItem::setPenWidth)
    ;
    class_<SVGNode, base<SVGItem>>("SVGNode")
        .constructor<>()
        .smart_ptr<std::shared_ptr<SVGNode>>("SVGNode")
        .function("setCenter", &SVGNode::setCenter)
        .function("setShape", select_overload<void(const std::string&)>(&SVGNode::setShape))
    ;
    class_<SVGEdge, base<SVGItem>>("SVGEdge")
        .constructor<>()
        .smart_ptr<std::shared_ptr<SVGEdge>>("SVGEdge")
    ;
    class_<SVGDiagram>("SVGDiagram")
        .constructor<>()
        .function("addNode", select_overload<const std::shared_ptr<SVGNode>&(const std::string&)>(&SVGDiagram::addNode))
        .function("addEdge", select_overload<const std::shared_ptr<SVGEdge>&(const std::string&, const std::string&)>(&SVGDiagram::addEdge))
        .function("render", select_overload<std::string()>(&SVGDiagram::render))
    ;
}
