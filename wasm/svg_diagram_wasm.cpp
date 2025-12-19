#include <functional>

#include "svg_diagram.h"

#include <string>
#include <memory>
#include <emscripten/bind.h>

#include "svg_diagram.h"
using namespace emscripten;
using namespace svg_diagram;

EMSCRIPTEN_BINDINGS(SVGDiagramWASM) {
    constant("NODE_SHAPE_NONE", std::string(SVGNode::NODE_SHAPE_NONE));
    constant("NODE_SHAPE_CIRCLE", std::string(SVGNode::NODE_SHAPE_CIRCLE));
    constant("NODE_SHAPE_DOUBLE_CIRCLE", std::string(SVGNode::NODE_SHAPE_DOUBLE_CIRCLE));
    constant("NODE_SHAPE_RECT", std::string(SVGNode::NODE_SHAPE_RECT));
    constant("NODE_SHAPE_ELLIPSE", std::string(SVGNode::NODE_SHAPE_ELLIPSE));
    constant("EDGE_SPLINES_LINE", std::string(SVGEdge::EDGE_SPLINES_LINE));
    constant("EDGE_SPLINES_SPLINE", std::string(SVGEdge::EDGE_SPLINES_SPLINE));
    constant("ARROW_SHAPE_NONE", std::string(SVGEdge::ARROW_SHAPE_NONE));
    constant("ARROW_SHAPE_NORMAL", std::string(SVGEdge::ARROW_SHAPE_NORMAL));
    constant("ARROW_SHAPE_EMPTY", std::string(SVGEdge::ARROW_SHAPE_EMPTY));
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
        .function("setConnection", &SVGEdge::setConnection)
        .function("setSplines", select_overload<void(const std::string&)>(&SVGEdge::setSplines))
        .function("setConnectionPoint", select_overload<void(double, double)>(&SVGEdge::addConnectionPoint))
        .function("setArrowHead", select_overload<void(const std::string_view&)>(&SVGEdge::setArrowHead))
        .function("setArrowTail", select_overload<void(const std::string_view&)>(&SVGEdge::setArrowTail))
    ;
    class_<SVGGraph, base<SVGItem>>("SVGGraph")
        .constructor<>()
        .smart_ptr<std::shared_ptr<SVGGraph>>("SVGGraph")
    ;
    class_<SVGDiagram>("SVGDiagram")
        .constructor<>()
        .function("addNode", select_overload<const std::shared_ptr<SVGNode>&(const std::string&)>(&SVGDiagram::addNode))
        .function("addEdge", select_overload<const std::shared_ptr<SVGEdge>&(const std::string&, const std::string&)>(&SVGDiagram::addEdge))
        .function("addSubgraph", select_overload<const std::shared_ptr<SVGGraph>&(const std::string&)>(&SVGDiagram::addSubgraph))
        .function("render", select_overload<std::string()>(&SVGDiagram::render))
    ;
}
