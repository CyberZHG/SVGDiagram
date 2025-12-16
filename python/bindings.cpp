#include <pybind11/pybind11.h>
#include <string>
#include <memory>
#include "svg_diagram.h"
using namespace std;
using namespace svg_diagram;

namespace py = pybind11;

PYBIND11_MODULE(_core, m, py::mod_gil_not_used()) {
    py::class_<SVGNode, shared_ptr<SVGNode>>(m, "SVGNode")
        .def(py::init<>())
        .def("set_center", py::overload_cast<double, double>(&SVGNode::setCenter))
        .def("set_label", py::overload_cast<const string&>(&SVGNode::setLabel));
    py::class_<SVGEdge, shared_ptr<SVGEdge>>(m, "SVGEdge")
        .def(py::init<>())
        .def("set_label", py::overload_cast<const string&>(&SVGEdge::setLabel));
    py::class_<SVGGraph, shared_ptr<SVGGraph>>(m, "SVGGraph")
        .def(py::init<>())
        .def("set_label", py::overload_cast<const string&>(&SVGGraph::setLabel));
    py::class_<SVGDiagram>(m, "SVGDiagram")
        .def(py::init<>())
        .def("add_node", py::overload_cast<const string&>(&SVGDiagram::addNode))
        .def("add_edge", py::overload_cast<const string&, const string&>(&SVGDiagram::addEdge))
        .def("to_svg", py::overload_cast<const string&>(&SVGDiagram::render));
}
