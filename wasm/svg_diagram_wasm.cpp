#include <functional>

#include "svg_diagram.h"

#include <string>
#include <memory>
#include <emscripten/bind.h>

#include "svg_diagram.h"
using namespace emscripten;
using namespace std;
using namespace svg_diagram;

bool compareSVG(const string& a, const string& b) {
    XMLElement rootA, rootB;
    rootA.addChildren(XMLElement::parse(a));
    rootB.addChildren(XMLElement::parse(b));
    return rootA == rootB;
}

shared_ptr<SVGNode> createSVGNode(const string& id) {
    return make_shared<SVGNode>(id);
}

shared_ptr<SVGEdge> createSVGEdge(const string& id) {
    return make_shared<SVGEdge>(id);
}

shared_ptr<SVGGraph> createSVGGraph(const string& id) {
    return make_shared<SVGGraph>(id);
}

EMSCRIPTEN_BINDINGS(SVGDiagramWASM) {
    emscripten::function("_compareSVG", &compareSVG);
    emscripten::function("createSVGNode", &createSVGNode);
    emscripten::function("createSVGEdge", &createSVGEdge);
    emscripten::function("createSVGGraph", &createSVGGraph);
    constant("NODE_SHAPE_NONE", string(SVGNode::SHAPE_NONE));
    constant("NODE_SHAPE_CIRCLE", string(SVGNode::SHAPE_CIRCLE));
    constant("NODE_SHAPE_DOUBLE_CIRCLE", string(SVGNode::SHAPE_DOUBLE_CIRCLE));
    constant("NODE_SHAPE_RECT", string(SVGNode::SHAPE_RECT));
    constant("NODE_SHAPE_ELLIPSE", string(SVGNode::SHAPE_ELLIPSE));
    constant("NODE_SHAPE_DOUBLE_ELLIPSE", string(SVGNode::SHAPE_DOUBLE_ELLIPSE));
    constant("NODE_SHAPE_RECORD", string(SVGNode::SHAPE_RECORD));
    constant("EDGE_SPLINES_LINE", string(SVGEdge::SPLINES_LINE));
    constant("EDGE_SPLINES_SPLINE", string(SVGEdge::SPLINES_SPLINE));
    constant("ARROW_SHAPE_NONE", string(SVGEdge::ARROW_NONE));
    constant("ARROW_SHAPE_NORMAL", string(SVGEdge::ARROW_NORMAL));
    constant("ARROW_SHAPE_EMPTY", string(SVGEdge::ARROW_EMPTY));
    class_<SVGItem>("SVGItem")
        .constructor<>()
        .smart_ptr<shared_ptr<SVGItem>>("SVGItem")
        .function("setID", &SVGItem::setID)
        .function("setLabel", &SVGItem::setLabel)
        .function("setFixedSize", &SVGItem::setFixedSize)
        .function("setTextSize", select_overload<void(double, double)>(&SVGItem::setPrecomputedTextSize))
        .function("setPrecomputedTextSize", select_overload<void(const string&, double, double)>(&SVGItem::setPrecomputedTextSize))
        .function("setMargin", select_overload<void(double, double)>(&SVGItem::setMargin))
        .function("setColor", &SVGItem::setColor)
        .function("setFillColor", &SVGItem::setFillColor)
        .function("setFontColor", &SVGItem::setFontColor)
        .function("setPenWidth", &SVGItem::setPenWidth)
        .function("setFontName", &SVGItem::setFontName)
        .function("setFontSize", &SVGItem::setFontSize)
        .function("setFont", &SVGItem::setFont)
        .function("setStyle", &SVGItem::setStyle)
        .function("appendStyleSolid", &SVGItem::appendStyleSolid)
        .function("appendStyleDashed", &SVGItem::appendStyleDashed)
        .function("appendStyleDotted", &SVGItem::appendStyleDotted)
        .function("setGradientAngle", &SVGItem::setGradientAngle)
    ;
    class_<SVGNode, base<SVGItem>>("SVGNode")
        .constructor<>()
        .smart_ptr<shared_ptr<SVGNode>>("SVGNode")
        .function("setCenter", &SVGNode::setCenter)
        .function("setShape", select_overload<void(const string&)>(&SVGNode::setShape))
    ;
    class_<SVGEdge, base<SVGItem>>("SVGEdge")
        .constructor<>()
        .smart_ptr<shared_ptr<SVGEdge>>("SVGEdge")
        .function("setConnection", &SVGEdge::setConnection)
        .function("setSplines", select_overload<void(const string&)>(&SVGEdge::setSplines))
        .function("setFieldFrom", &SVGEdge::setFieldFrom)
        .function("setFieldTo", &SVGEdge::setFieldTo)
        .function("addConnectionPoint", select_overload<void(double, double)>(&SVGEdge::addConnectionPoint))
        .function("_setArrowHead", select_overload<void(const string&)>(&SVGEdge::setArrowHead))
        .function("_setArrowTail", select_overload<void(const string&)>(&SVGEdge::setArrowTail))
        .function("setTailLabel", &SVGEdge::setTailLabel)
        .function("setHeadLabel", &SVGEdge::setHeadLabel)
        .function("setLabelDistance", &SVGEdge::setLabelDistance)
    ;
    class_<SVGGraph, base<SVGItem>>("SVGGraph")
        .constructor<>()
        .smart_ptr<shared_ptr<SVGGraph>>("SVGGraph")
        .function("defaultNodeAttributes", &SVGGraph::defaultNodeAttributes, return_value_policy::reference())
        .function("defaultEdgeAttributes", &SVGGraph::defaultEdgeAttributes, return_value_policy::reference())
        .function("addNode", &SVGGraph::addNode)
        .function("addEdge", &SVGGraph::addEdge)
        .function("addSubgraph", &SVGGraph::addSubgraph)
    ;
    class_<SVGDiagram>("SVGDiagram")
        .constructor<>()
        .function("defaultNodeAttributes", &SVGDiagram::defaultNodeAttributes, return_value_policy::reference())
        .function("defaultEdgeAttributes", &SVGDiagram::defaultEdgeAttributes, return_value_policy::reference())
        .function("setBackgroundColor", &SVGDiagram::setBackgroundColor)
        .function("setFixedViewBox", &SVGDiagram::setFixedViewBox)
        .function("setRotation", select_overload<void(double)>(&SVGDiagram::setRotation))
        .function("addNode", select_overload<const shared_ptr<SVGNode>&(const string&)>(&SVGDiagram::addNode))
        .function("addEdge", select_overload<const shared_ptr<SVGEdge>&(const string&, const string&)>(&SVGDiagram::addEdge))
        .function("addSelfLoop", select_overload<const shared_ptr<SVGEdge>&(const string&, double, double, double)>(&SVGDiagram::addSelfLoop))
        .function("addSelfLoopToLeft", select_overload<const shared_ptr<SVGEdge>&(const string&, double, double)>(&SVGDiagram::addSelfLoopToLeft))
        .function("addSelfLoopToRight", select_overload<const shared_ptr<SVGEdge>&(const string&, double, double)>(&SVGDiagram::addSelfLoopToRight))
        .function("addSelfLoopToTop", select_overload<const shared_ptr<SVGEdge>&(const string&, double, double)>(&SVGDiagram::addSelfLoopToTop))
        .function("addSelfLoopToBottom", select_overload<const shared_ptr<SVGEdge>&(const string&, double, double)>(&SVGDiagram::addSelfLoopToBottom))
        .function("addSubgraph", select_overload<const shared_ptr<SVGGraph>&(const string&)>(&SVGDiagram::addSubgraph))
        .function("render", select_overload<string()>(&SVGDiagram::render))
    ;
}
