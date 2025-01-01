#include "svg_diagram.h"

#include <format>
#include <fstream>
using namespace std;
using namespace svg_diagram;

void SVGDiagram::enableDebug() {
    _enabledDebug = true;
}

void SVGDiagram::clearSVGDraw() {
    _svgDraws.clear();
}

void SVGDiagram::addSVGDraw(std::unique_ptr<SVGDraw> svgDraw) {
    _svgDraws.emplace_back(std::move(svgDraw));
}

void SVGDiagram::addSVGDraw(std::vector<std::unique_ptr<SVGDraw>> svgDraws) {
    for (auto& svgDraw : svgDraws) {
        _svgDraws.emplace_back(std::move(svgDraw));
    }
}

void SVGDiagram::setCanvasSize(const int width, const int height) {
    _width = width;
    _height = height;
}

void SVGDiagram::setBackgroundColor(const std::string& backgroundColor) {
    _backgroundColor = backgroundColor;
}

const unique_ptr<SVGNode>& SVGDiagram::addNode(const string& id) {
    if (_nodes.contains(id)) {
        return _nodes.at(id);
    }
    _nodeIds.emplace_back(id);
    return _nodes[id] = make_unique<SVGNode>();
}

void SVGDiagram::addNode(const string& id, unique_ptr<SVGNode> node) {
    if (!_nodes.contains(id)) {
        _nodeIds.emplace_back(id);
    }
    _nodes[id] = std::move(node);
}

const unique_ptr<SVGEdge>& SVGDiagram::addEdge(const string& id) {
    if (_edges.contains(id)) {
        return _edges.at(id);
    }
    _edgeIds.emplace_back(id);
    return _edges[id] = make_unique<SVGEdge>();
}

const unique_ptr<SVGEdge>& SVGDiagram::addEdge(const string& from, const string& to) {
    const auto id = format("{} -> {}", from, to);
    const auto& edge = addEdge(id);
    edge->setConnection(from, to);
    return edge;
}

void SVGDiagram::addEdge(const string& id, unique_ptr<SVGEdge> edge) {
    if (!_edges.contains(id)) {
        _edgeIds.emplace_back(id);
    }
    _edges[id] = std::move(edge);
}

void SVGDiagram::addEdge(unique_ptr<SVGEdge> edge) {
    const auto id = format("{} -> {}", edge->nodeFrom(), edge->nodeTo());
    addEdge(id, std::move(edge));
}

std::string SVGDiagram::render() {
    produceSVGDrawsDynamic();
    const auto [svgElement, gElement] = generateSVGElement();
    unordered_set<string> singletonNames;
    if (const auto defsElements = renderDefs(singletonNames); defsElements != nullptr) {
        svgElement->addChild(defsElements);
    }
    for (const auto& draw : _svgDraws) {
        if (guardSingleton(singletonNames, draw)) {
            gElement->addChildren(draw->generateXMLElements());
        }
    }
    for (const auto& draw : _svgDrawsDynamic) {
        if (guardSingleton(singletonNames, draw)) {
            gElement->addChildren(draw->generateXMLElements());
        }
    }
    return svgElement->toString();
}

void SVGDiagram::render(const std::string &filePath) {
    ofstream file(filePath);
    file << render();
    file.close();
}

void SVGDiagram::produceSVGDrawsDynamic() {
    _svgDrawsDynamic.clear();
    for (const auto& id : _nodeIds) {
        const auto& node = _nodes.at(id);
        if (_enabledDebug) {
            node->enableDebug();
        }
        node->adjustNodeSize();
        _svgDrawsDynamic.emplace_back(make_unique<SVGDrawComment>(format("node_id = {}", id)));
        for (auto& draw : node->produceSVGDraws()) {
            _svgDrawsDynamic.emplace_back(std::move(draw));
        }
    }
    for (const auto& id : _edgeIds) {
        const auto& edge = _edges.at(id);
        if (_enabledDebug) {
            edge->enableDebug();
        }
        _svgDrawsDynamic.emplace_back(make_unique<SVGDrawComment>(format("edge_id = {}", id)));
        for (auto& draw : edge->produceSVGDraws(_nodes)) {
            _svgDrawsDynamic.emplace_back(std::move(draw));
        }
    }
}

bool SVGDiagram::guardSingleton(unordered_set<string>& singletonNames, const unique_ptr<SVGDraw>& svgDraw) {
    const auto name = svgDraw->singletonName();
    if (name.empty()) {
        return true;
    }
    if (singletonNames.contains(name)) {
        return false;
    }
    singletonNames.emplace(name);
    return true;
}

pair<XMLElement::ChildType, XMLElement::ChildType> SVGDiagram::generateSVGElement() const {
    double width = _width, height = _height;
    double minX = 0.0, maxX = 0.0, minY = 0.0, maxY = 0.0;
    bool firstEntity = true;
    const auto updateMinMax = [&](const std::vector<std::unique_ptr<SVGDraw>>& svgDraws) {
        for (const auto& draw : svgDraws) {
            if (draw->hasEntity()) {
                const auto boundingBox = draw->boundingBox();
                if (firstEntity) {
                    firstEntity = false;
                    minX = boundingBox.x1;
                    minY = boundingBox.y1;
                    maxX = boundingBox.x2;
                    maxY = boundingBox.y2;
                } else {
                    minX = min(minX, boundingBox.x1);
                    minY = min(minY, boundingBox.y1);
                    maxX = max(maxX, boundingBox.x2);
                    maxY = max(maxY, boundingBox.y2);
                }
            }
        }
    };
    updateMinMax(_svgDraws);
    updateMinMax(_svgDrawsDynamic);
    double translateX = _margin.first - minX;
    double translateY = _margin.second - minY;
    if (width == 0.0) {
        width = maxX - minX + _margin.first * 2.0;
    } else {
        translateX = (width - maxX - minX) / 2.0;
    }
    if (height == 0.0) {
        height = maxY - minY + _margin.second * 2.0;
    } else {
        translateY = (height - maxY - minY) / 2.0;
    }
    const auto svgElement = make_shared<XMLElement>("svg");
    svgElement->addAttribute("width", width);
    svgElement->addAttribute("height", height);
    svgElement->addAttribute("viewBox", format("0 0 {} {}", width, height));
    svgElement->addAttribute("xmlns", "http://www.w3.org/2000/svg");
    svgElement->addAttribute("xmlns:xlink", "http://www.w3.org/1999/xlink");
    svgElement->addChild(make_shared<XMLElementComment>("Generated by: https://github.com/CyberZHG/SVGDiagram"));
    const auto gElement = make_shared<XMLElement>("g");
    gElement->addAttribute("id", "graph0");
    gElement->addAttribute("class", "graph");
    gElement->addAttribute("transform", format("translate({},{}) scale(1.0)", translateX, translateY));
    if (!_backgroundColor.empty()) {
        const auto rectElement = make_shared<XMLElement>("rect");
        rectElement->addAttribute("x", -translateX);
        rectElement->addAttribute("y", -translateY);
        rectElement->addAttribute("width", width);
        rectElement->addAttribute("height", height);
        rectElement->addAttribute("fill", _backgroundColor);
        gElement->addChild(rectElement);
    }
    svgElement->addChild(gElement);
    return {svgElement, gElement};
}

XMLElement::ChildType SVGDiagram::renderDefs(unordered_set<string>& singletonNames) const {
    vector<int> defsIndices, dynamicDefsIndices;
    for (int i = 0; i < _svgDraws.size(); ++i) {
        if (_svgDraws[i]->isDefs()) {
            defsIndices.emplace_back(i);
        }
    }
    for (int i = 0; i < _svgDrawsDynamic.size(); ++i) {
        if (_svgDrawsDynamic[i]->isDefs()) {
            dynamicDefsIndices.emplace_back(i);
        }
    }
    if (defsIndices.empty() && dynamicDefsIndices.empty()) {
        return nullptr;
    }
    const auto defsElement = make_shared<XMLElement>("defs");
    for (const auto& index : defsIndices) {
        if (guardSingleton(singletonNames, _svgDraws[index])) {
            defsElement->addChildren(_svgDraws[index]->generateXMLElements());
        }
    }
    for (const auto& index : dynamicDefsIndices) {
        if (guardSingleton(singletonNames, _svgDrawsDynamic[index])) {
            defsElement->addChildren(_svgDrawsDynamic[index]->generateXMLElements());
        }
    }
    return defsElement;
}

string SVGDiagram::generateSVGClose() {
    string svg = "  </g>\n";
    svg += "</svg>\n";
    return svg;
}
