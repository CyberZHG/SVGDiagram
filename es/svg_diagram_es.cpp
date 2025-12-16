#include "svg_diagram.h"

#include <string>
#include <memory>
#include <emscripten/bind.h>

#include "svg_diagram.h"
using namespace emscripten;
using namespace svg_diagram;

EMSCRIPTEN_BINDINGS(SVGDiagramWASM) {
    class_<SVGItem>("SVGItem")
        .constructor<>()
        .smart_ptr<std::shared_ptr<SVGItem>>("SVGItem")
        .function("setLabel", &SVGItem::setLabel)
    ;
    class_<SVGNode, base<SVGItem>>("SVGNode")
        .constructor<>()
        .smart_ptr<std::shared_ptr<SVGNode>>("SVGNode")
        .function("setCenter", &SVGNode::setCenter)
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
