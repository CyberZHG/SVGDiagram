#include <pybind11/pybind11.h>
#include <string>
#include <memory>
#include "svg_diagram.h"
using namespace std;
using namespace svg_diagram;

namespace py = pybind11;

bool compareSVG(const string& a, const string& b) {
    XMLElement rootA, rootB;
    rootA.addChildren(XMLElement::parse(a));
    rootB.addChildren(XMLElement::parse(b));
    return rootA == rootB;
}

PYBIND11_MODULE(_core, m, py::mod_gil_not_used()) {
    m.def("_compare_svg", &compareSVG);
    py::class_<SVGNode, shared_ptr<SVGNode>>(m, "SVGNode")
        .def(py::init<const string&>(), py::arg("node_id") = string())
        .def_property_readonly_static("SHAPE_NONE", [](py::object) { return string(SVGNode::SHAPE_NONE); })
        .def_property_readonly_static("SHAPE_CIRCLE", [](py::object) { return string(SVGNode::SHAPE_CIRCLE); })
        .def_property_readonly_static("SHAPE_DOUBLE_CIRCLE", [](py::object) { return string(SVGNode::SHAPE_DOUBLE_CIRCLE); })
        .def_property_readonly_static("SHAPE_RECT", [](py::object) { return string(SVGNode::SHAPE_RECT); })
        .def_property_readonly_static("SHAPE_ELLIPSE", [](py::object) { return string(SVGNode::SHAPE_ELLIPSE); })
        .def("set_center", py::overload_cast<double, double>(&SVGNode::setCenter))
        .def("set_id", &SVGNode::setID)
        .def("set_label", py::overload_cast<const string&>(&SVGNode::setLabel))
        .def("set_shape", py::overload_cast<const string&>(&SVGNode::setShape))
        .def("set_fixed_size", &SVGNode::setFixedSize)
        .def("set_text_size", &SVGNode::setPrecomputedTextSize)
        .def("set_margin", py::overload_cast<double, double>(&SVGNode::setMargin))
        .def("set_color", &SVGNode::setColor)
        .def("set_fill_color", &SVGNode::setFillColor)
        .def("set_font_color", &SVGNode::setFontColor)
        .def("set_pen_width", &SVGNode::setPenWidth)
        .def("set_font_name", &SVGNode::setFontName)
        .def("set_font_size", &SVGNode::setFontSize)
        .def("set_font", &SVGNode::setFont)
    ;
    py::class_<SVGEdge, shared_ptr<SVGEdge>>(m, "SVGEdge")
        .def(py::init<const string&>(), py::arg("edge_id") = string())
        .def_property_readonly_static("SPLINES_LINE", [](py::object) { return string(SVGEdge::SPLINES_LINE); })
        .def_property_readonly_static("SPLINES_SPLINE", [](py::object) { return string(SVGEdge::SPLINES_SPLINE); })
        .def_property_readonly_static("ARROW_NONE", [](py::object) { return string(SVGEdge::ARROW_NONE); })
        .def_property_readonly_static("ARROW_NORMAL", [](py::object) { return string(SVGEdge::ARROW_NORMAL); })
        .def_property_readonly_static("ARROW_EMPTY", [](py::object) { return string(SVGEdge::ARROW_EMPTY); })
        .def("set_connection", &SVGEdge::setConnection)
        .def("set_id", &SVGEdge::setID)
        .def("set_label", py::overload_cast<const string&>(&SVGEdge::setLabel))
        .def("set_text_size", &SVGEdge::setPrecomputedTextSize)
        .def("set_margin", py::overload_cast<double, double>(&SVGEdge::setMargin))
        .def("set_color", &SVGEdge::setColor)
        .def("set_fill_color", &SVGEdge::setFillColor)
        .def("set_font_color", &SVGEdge::setFontColor)
        .def("set_pen_width", &SVGEdge::setPenWidth)
        .def("set_font_name", &SVGEdge::setFontName)
        .def("set_font_size", &SVGEdge::setFontSize)
        .def("set_font", &SVGEdge::setFont)
        .def("set_splines", py::overload_cast<const string&>(&SVGEdge::setSplines))
        .def("add_connection_point", py::overload_cast<double, double>(&SVGEdge::addConnectionPoint))
        .def("set_arrow_head", py::overload_cast<const string_view&>(&SVGEdge::setArrowHead), py::arg("arrow_shape") = string(SVGEdge::ARROW_NORMAL))
        .def("set_arrow_tail", py::overload_cast<const string_view&>(&SVGEdge::setArrowTail), py::arg("arrow_shape") = string(SVGEdge::ARROW_NORMAL))
    ;
    py::class_<SVGGraph, shared_ptr<SVGGraph>>(m, "SVGGraph")
        .def(py::init<const string&>(), py::arg("graph_id") = string())
        .def("set_id", &SVGGraph::setID)
        .def("set_label", py::overload_cast<const string&>(&SVGGraph::setLabel))
        .def("set_text_size", &SVGGraph::setPrecomputedTextSize)
        .def("set_margin", py::overload_cast<double, double>(&SVGGraph::setMargin))
        .def("set_color", &SVGGraph::setColor)
        .def("set_fill_color", &SVGGraph::setFillColor)
        .def("set_font_color", &SVGGraph::setFontColor)
        .def("set_pen_width", &SVGGraph::setPenWidth)
        .def("set_font_name", &SVGGraph::setFontName)
        .def("set_font_size", &SVGGraph::setFontSize)
        .def("set_font", &SVGGraph::setFont)
        .def("default_node_attributes", &SVGGraph::defaultNodeAttributes, py::return_value_policy::reference_internal)
        .def("default_edge_attributes", &SVGGraph::defaultEdgeAttributes, py::return_value_policy::reference_internal)
        .def("add_node", &SVGGraph::addNode)
        .def("add_edge", &SVGGraph::addEdge)
        .def("add_subgraph", &SVGGraph::addSubgraph)
    ;
    py::class_<SVGDiagram>(m, "SVGDiagram")
        .def(py::init<>())
        .def("set_background_color", &SVGDiagram::setBackgroundColor)
        .def("add_node", py::overload_cast<const string&>(&SVGDiagram::addNode))
        .def("add_edge", py::overload_cast<const string&, const string&>(&SVGDiagram::addEdge))
        .def("add_subgraph", py::overload_cast<const string&>(&SVGDiagram::addSubgraph))
        .def("render", py::overload_cast<>(&SVGDiagram::render))
        .def("to_svg", py::overload_cast<const string&>(&SVGDiagram::render))
    ;
}
