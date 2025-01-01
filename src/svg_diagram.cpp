#include "svg_diagram.h"

#include <format>
#include <fstream>
using namespace std;
using namespace svg_diagram;

SVGDiagram::SVGDiagram() {
    _svgDraws.emplace_back(make_unique<SVGDrawComment>("Created by: https://github.com/CyberZHG/SVGDiagram"));
}

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

void SVGDiagram::addNode(const string& id, unique_ptr<SVGNode> node) {
    if (!_nodes.contains(id)) {
        _nodeIds.emplace_back(id);
    }
    _nodes[id] = std::move(node);
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
    string svg = generateSVGOpen();
    unordered_set<string> singletonNames;
    svg += renderDefs(singletonNames);
    for (const auto& draw : _svgDraws) {
        if (guardSingleton(singletonNames, draw)) {
            svg += draw->renderWithIndent(2);
        }
    }
    for (const auto& draw : _svgDrawsDynamic) {
        if (guardSingleton(singletonNames, draw)) {
            svg += draw->renderWithIndent(2);
        }
    }
    svg += generateSVGClose();
    return svg;
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

string SVGDiagram::generateSVGOpen() const {
    string svg = R"(<?xml version="1.0" encoding="UTF-8"?>)" + string("\n");
    double width = _width, height = _height;
    double viewBoxX = 0.0, viewBoxY = 0.0;
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
    if (width == 0.0) {
        width = maxX - minX + _margin.first * 2.0;
        viewBoxX = minX - _margin.first;
    } else {
        viewBoxX = (minX + maxX - _width) / 2.0;
    }
    if (height == 0.0) {
        height = maxY - minY + _margin.second * 2.0;
        viewBoxY = minY - _margin.second;
    } else {
        viewBoxY = (minY + maxY - _height) / 2.0;
    }
    svg += format(R"(<svg xmlns="http://www.w3.org/2000/svg" width="{}" height="{}")", width, height);
    svg += format(R"( viewBox="{} {} {} {}">)", viewBoxX, viewBoxY, width, height);
    svg += "\n";
    if (!_backgroundColor.empty()) {
        svg += format(R"(  <rect x="{}" y="{}" width="{}" height="{}" fill="{}" />)", viewBoxX, viewBoxY, width, height, _backgroundColor);
        svg += "\n";
    }
    return svg;
}

std::string SVGDiagram::renderDefs(unordered_set<string>& singletonNames) const {
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
        return "";
    }
    string svg = "  <defs>\n";
    for (const auto& index : defsIndices) {
        if (guardSingleton(singletonNames, _svgDraws[index])) {
            svg += _svgDraws[index]->renderWithIndent(4);
        }
    }
    for (const auto& index : dynamicDefsIndices) {
        if (guardSingleton(singletonNames, _svgDrawsDynamic[index])) {
            svg += _svgDrawsDynamic[index]->renderWithIndent(4);
        }
    }
    svg += "  </defs>\n";
    return svg;
}

string SVGDiagram::generateSVGClose() {
    return "</svg>\n";
}
