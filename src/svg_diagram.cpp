#include "svg_diagram.h"

#include <format>
#include <fstream>
using namespace std;
using namespace svg_diagram;

SVGDiagram::SVGDiagram() {
    _svgDraws.emplace_back(make_unique<SVGDrawComment>("Created by: https://github.com/CyberZHG/SVGDiagram"));
}

void SVGDiagram::addSVGDraw(std::unique_ptr<SVGDraw> svgDraw) {
    _svgDraws.emplace_back(std::move(svgDraw));
}

std::string SVGDiagram::render() const {
    string svg = generateSVGOpen();
    for (const auto& draw : _svgDraws) {
        svg += draw->render();
    }
    svg += generateSVGClose();
    return svg;
}

void SVGDiagram::render(const std::string &filePath) const {
    ofstream file(filePath);
    file << render();
    file.close();
}

void SVGDiagram::setCanvasSize(const int width, const int height) {
    _width = width;
    _height = height;
}

string SVGDiagram::generateSVGOpen() const {
    string svg = R"(<?xml version="1.0" encoding="UTF-8"?>)" + string("\n");
    double width = _width, height = _height;
    double viewBoxX = 0.0, viewBoxY = 0.0;
    double minX = 0.0, maxX = 0.0, minY = 0.0, maxY = 0.0;
    bool firstEntity = true;
    for (const auto& draw : _svgDraws) {
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
    return svg;
}

string SVGDiagram::generateSVGClose() const {
    return "</svg>\n";
}
