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
        .def("set_center", py::overload_cast<double, double>(&SVGNode::setCenter), py::arg("cx"), py::arg("cy"))
        .def("set_id", &SVGNode::setID, py::arg("node_id"))
        .def("set_label", py::overload_cast<const string&>(&SVGNode::setLabel), py::arg("label"))
        .def("set_shape", py::overload_cast<const string&>(&SVGNode::setShape), py::arg("shape"))
        .def("set_fixed_size", &SVGNode::setFixedSize, py::arg("width"), py::arg("height"))
        .def("set_text_size", &SVGNode::setPrecomputedTextSize, py::arg("width"), py::arg("height"))
        .def("set_margin", py::overload_cast<double, double>(&SVGNode::setMargin), py::arg("x_margin"), py::arg("y_margin"))
        .def("set_color", &SVGNode::setColor, py::arg("color"))
        .def("set_fill_color", &SVGNode::setFillColor, py::arg("color"))
        .def("set_font_color", &SVGNode::setFontColor, py::arg("color"))
        .def("set_pen_width", &SVGNode::setPenWidth, py::arg("pen_width"))
        .def("set_font_name", &SVGNode::setFontName, py::arg("font_name"))
        .def("set_font_size", &SVGNode::setFontSize, py::arg("font_size"))
        .def("set_font", &SVGNode::setFont, py::arg("font_name"), py::arg("font_size"))
    ;
    py::class_<SVGEdge, shared_ptr<SVGEdge>>(m, "SVGEdge")
        .def(py::init<const string&>(), py::arg("edge_id") = string())
        .def_property_readonly_static("SPLINES_LINE", [](py::object) { return string(SVGEdge::SPLINES_LINE); })
        .def_property_readonly_static("SPLINES_SPLINE", [](py::object) { return string(SVGEdge::SPLINES_SPLINE); })
        .def_property_readonly_static("ARROW_NONE", [](py::object) { return string(SVGEdge::ARROW_NONE); })
        .def_property_readonly_static("ARROW_NORMAL", [](py::object) { return string(SVGEdge::ARROW_NORMAL); })
        .def_property_readonly_static("ARROW_EMPTY", [](py::object) { return string(SVGEdge::ARROW_EMPTY); })
        .def("set_connection", &SVGEdge::setConnection, py::arg("tail_node_id"), py::arg("head_node_id"))
        .def("set_id", &SVGEdge::setID, py::arg("edge_id"))
        .def("set_label", py::overload_cast<const string&>(&SVGEdge::setLabel), py::arg("label"))
        .def("set_text_size", &SVGEdge::setPrecomputedTextSize, py::arg("width"), py::arg("height"))
        .def("set_margin", py::overload_cast<double, double>(&SVGEdge::setMargin), py::arg("x_margin"), py::arg("y_margin"))
        .def("set_color", &SVGEdge::setColor, py::arg("color"))
        .def("set_fill_color", &SVGEdge::setFillColor, py::arg("color"))
        .def("set_font_color", &SVGEdge::setFontColor, py::arg("color"))
        .def("set_pen_width", &SVGEdge::setPenWidth, py::arg("pen_width"))
        .def("set_font_name", &SVGEdge::setFontName, py::arg("font_name"))
        .def("set_font_size", &SVGEdge::setFontSize, py::arg("font_size"))
        .def("set_font", &SVGEdge::setFont, py::arg("font_name"), py::arg("font_size"))
        .def("set_splines", py::overload_cast<const string&>(&SVGEdge::setSplines), py::arg("splines"))
        .def("add_connection_point", py::overload_cast<double, double>(&SVGEdge::addConnectionPoint), py::arg("x"), py::arg("y"))
        .def("set_arrow_head", py::overload_cast<const string_view&>(&SVGEdge::setArrowHead), py::arg("arrow_shape") = string(SVGEdge::ARROW_NORMAL))
        .def("set_arrow_tail", py::overload_cast<const string_view&>(&SVGEdge::setArrowTail), py::arg("arrow_shape") = string(SVGEdge::ARROW_NORMAL))
    ;
    py::class_<SVGGraph, shared_ptr<SVGGraph>>(m, "SVGGraph")
        .def(py::init<const string&>(), py::arg("graph_id") = string())
        .def("set_id", &SVGGraph::setID, py::arg("graph_id"))
        .def("set_label", py::overload_cast<const string&>(&SVGGraph::setLabel), py::arg("label"))
        .def("set_text_size", &SVGGraph::setPrecomputedTextSize, py::arg("width"), py::arg("height"))
        .def("set_margin", py::overload_cast<double, double>(&SVGGraph::setMargin), py::arg("x_margin"), py::arg("y_margin"))
        .def("set_color", &SVGGraph::setColor, py::arg("color"))
        .def("set_fill_color", &SVGGraph::setFillColor, py::arg("color"))
        .def("set_font_color", &SVGGraph::setFontColor, py::arg("color"))
        .def("set_pen_width", &SVGGraph::setPenWidth, py::arg("pen_width"))
        .def("set_font_name", &SVGGraph::setFontName, py::arg("font_name"))
        .def("set_font_size", &SVGGraph::setFontSize, py::arg("font_size"))
        .def("set_font", &SVGGraph::setFont, py::arg("font_name"), py::arg("font_size"))
        .def("default_node_attributes", &SVGGraph::defaultNodeAttributes, py::return_value_policy::reference_internal)
        .def("default_edge_attributes", &SVGGraph::defaultEdgeAttributes, py::return_value_policy::reference_internal)
        .def("add_node", &SVGGraph::addNode, py::arg("node"))
        .def("add_edge", &SVGGraph::addEdge, py::arg("edge"))
        .def("add_subgraph", &SVGGraph::addSubgraph, py::arg("subgraph"))
    ;
    py::class_<SVGDiagram>(m, "SVGDiagram")
        .def(py::init<>())
        .def("set_background_color", &SVGDiagram::setBackgroundColor, py::arg("color"))
        .def("add_node", py::overload_cast<const string&>(&SVGDiagram::addNode), py::arg("node"))
        .def("add_edge", py::overload_cast<const string&, const string&>(&SVGDiagram::addEdge), py::arg("tail_node_id"), py::arg("head_node_id"))
        .def("add_subgraph", py::overload_cast<const string&>(&SVGDiagram::addSubgraph), py::arg("subgraph"))
        .def("render", py::overload_cast<>(&SVGDiagram::render))
        .def("to_svg", py::overload_cast<const string&>(&SVGDiagram::render), py::arg("file_path"))
    ;
}
