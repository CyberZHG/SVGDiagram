#include "svg_diagram.h"

#include <format>
#include <fstream>
#include <unordered_set>
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
    const auto id = newEdgeId();
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
    const auto id = newEdgeId();
    addEdge(id, std::move(edge));
}

string SVGDiagram::render() {
    produceSVGDrawsDynamic();
    const auto [svgElement, gElement] = generateSVGElement();
    unordered_set<string> singletonNames;
    for (const auto& draw : _svgDraws) {
        gElement->addChildren(draw->generateXMLElements());
    }
    for (const auto& draw : _svgDrawsDynamic) {
        gElement->addChildren(draw->generateXMLElements());
    }
    return svgElement->toString();
}

void SVGDiagram::render(const string &filePath) {
    ofstream file(filePath);
    file << render();
    file.close();
}

string SVGDiagram::newEdgeId() {
    string newEdgeId;
    while (true) {
        newEdgeId = format("edge{}", _edgeIndex++);
        if (!_edges.contains(newEdgeId)) {
            break;
        }
    }
    return newEdgeId;
}

void SVGDiagram::produceSVGDrawsDynamic() {
    _svgDrawsDynamic.clear();
    for (const auto& id : _nodeIds) {
        const auto& node = _nodes.at(id);
        if (_enabledDebug) {
            node->enableDebug();
        }
        node->adjustNodeSize();
        _svgDrawsDynamic.emplace_back(make_unique<SVGDrawComment>(format("Node: {}", id)));
        auto group = make_unique<SVGDrawGroup>();
        group->setAttribute("id", id);
        group->setAttribute("class", "node");
        group->addChild(make_unique<SVGDrawTitle>(id));
        auto svgDraws = node->produceSVGDraws();
        group->addChildren(svgDraws);
        _svgDrawsDynamic.emplace_back(std::move(group));
    }
    for (const auto& id : _edgeIds) {
        const auto& edge = _edges.at(id);
        if (_enabledDebug) {
            edge->enableDebug();
        }
        _svgDrawsDynamic.emplace_back(make_unique<SVGDrawComment>(format("Edge: {} ({} -> {})", id, edge->nodeFrom(), edge->nodeTo())));
        auto group = make_unique<SVGDrawGroup>();
        group->setAttribute("id", id);
        group->setAttribute("class", "edge");
        group->addChild(make_unique<SVGDrawTitle>(format("{}->{}", edge->nodeFrom(), edge->nodeTo())));
        auto svgDraws = edge->produceSVGDraws(_nodes);
        group->addChildren(svgDraws);
        _svgDrawsDynamic.emplace_back(std::move(group));
    }
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
