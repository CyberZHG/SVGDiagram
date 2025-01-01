#include "svg_draw.h"
#include "svg_text_size.h"
#include "attribute_utils.h"

#include <format>
#include <ranges>
#include <regex>
#include <algorithm>
using namespace std;
using namespace svg_diagram;


SVGDrawLine::SVGDrawLine(const double x1, const double y1, const double x2, const double y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

XMLElement::ChildrenType SVGDrawLine::generateXMLElements() const {
    const auto lineElement = make_shared<XMLElement>(tag());
    lineElement->addAttribute("x1", x1);
    lineElement->addAttribute("y1", y1);
    lineElement->addAttribute("x2", x2);
    lineElement->addAttribute("y2", y2);
    addAttributesToXMLElement(lineElement);
    return {lineElement};
}

SVGDrawBoundingBox SVGDrawLine::boundingBox() const {
    return {x1, y1, x2, y2};
}

string SVGDrawLine::tag() const {
    return "line";
}

SVGDrawPath::SVGDrawPath(const string& d) {
    this->d = d;
}

XMLElement::ChildrenType SVGDrawPath::generateXMLElements() const {
    const auto commands = AttributeUtils::parseDCommands(d);
    string reformat;
    for (int i = 0; i < static_cast<int>(commands.size()); ++i) {
        const auto& [command, parameters] = commands[i];
        if (i > 0) {
            reformat += ' ';
        }
        reformat += command;
        for (const auto& parameter : parameters) {
            reformat += format(" {}", parameter);
        }
    }
    const auto pathElement = make_shared<XMLElement>(tag());
    pathElement->addAttribute("d", reformat);
    addAttributesToXMLElement(pathElement);
    return {pathElement};
}

SVGDrawBoundingBox SVGDrawPath::boundingBox() const {
    double xMin = 0.0, yMin = 0.0, xMax = 0.0, yMax = 0.0;
    const auto commands = AttributeUtils::parseDCommands(d);
    if (const auto points = AttributeUtils::computeDPathPoints(commands); !points.empty()) {
        xMin = xMax = points[0].first;
        yMin = yMax = points[0].second;
        for (const auto&[x, y] : points) {
            xMin = min(xMin, x);
            yMin = min(yMin, y);
            xMax = max(xMax, x);
            yMax = max(yMax, y);
        }
    }
    return {xMin, yMin, xMax, yMax};
}

string SVGDrawPath::tag() const {
    return "path";
}
