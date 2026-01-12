#include "svg_draw.h"
#include "svg_text_size.h"
#include "attribute_utils.h"
#include "constants.h"

#include <format>
#include <ranges>
#include <regex>
#include <algorithm>
using namespace std;
using namespace svg_diagram;


SVGDrawNode::SVGDrawNode(const double cx, const double cy, const double width, const double height) {
    this->cx = cx;
    this->cy = cy;
    this->width = width;
    this->height = height;
}

SVGDrawBoundingBox SVGDrawNode::boundingBox() const {
    const double halfWidth = width / 2.0;
    const double halfHeight = height / 2.0;
    return {cx - halfWidth, cy - halfHeight, cx + halfWidth, cy + halfHeight};
}

SVGDrawText::SVGDrawText() {
    setFont("Times,serif", 14);
}

SVGDrawText::SVGDrawText(const double x, const double y, const string& text) {
    cx = x;
    cy = y;
    this->text = text;
    setFont("Times,serif", 14);
}

SVGDrawText::SVGDrawText(const double x, const double y, const double width, const double height, const string& text) {
    cx = x;
    cy = y;
    this->width = width;
    this->height = height;
    this->text = text;
    setFont("Times,serif", 14);
}

void SVGDrawText::setFont(const string& fontFamily, double fontSize) {
    setAttribute(SVG_ATTR_KEY_FONT_FAMILY, fontFamily);
    setAttribute(SVG_ATTR_KEY_FONT_SIZE, format("{}", fontSize));
}

XMLElement::ChildrenType SVGDrawText::generateXMLElements() const {
    vector<char> aligns;
    vector<string> lines;
    const auto n = text.length();
    for (size_t i = 0, start = 0; i <= n; i++) {
        bool split = false;
        size_t step = 0;
        if (i == n) {
            split = !(i >= 2 && text[i - 2] == '\\' && (text[i - 1] == 'l' || text[i - 1] == 'r'));
            if (split) {
                aligns.push_back('c');
            }
        } else if (i + 1 < n && text[i] == '\r' && text[i + 1] == '\n') {
            aligns.push_back('c');
            split = true;
            step = 1;
        } else if (i + 1 < n && text[i] == '\\' && text[i + 1] == 'l') {
            aligns.push_back('l');
            split = true;
            step = 1;
        } else if (i + 1 < n && text[i] == '\\' && text[i + 1] == 'r') {
            aligns.push_back('r');
            split = true;
            step = 1;
        } else if (text[i] == '\n' || text[i] == '\r') {
            aligns.push_back('c');
            split = true;
        }
        if (split) {
            lines.push_back(text.substr(start, i - start));
            i += step;
            start = i + 1;
        }
    }
    const auto textElement = make_shared<XMLElement>(tag());
    textElement->addAttribute("x", cx);
    textElement->addAttribute("y", cy);
    textElement->addAttribute("text-anchor", "middle");
    textElement->addAttribute("dominant-baseline", "central");
    addAttributesToXMLElement(textElement);
    if (lines.size() == 1) {
        if (width > 0.0 && aligns[0] == 'l') {
            textElement->addAttribute("text-anchor", "start");
            textElement->addAttribute("x", cx - width / 2);
        } else if (width > 0.0 && aligns[0] == 'r') {
            textElement->addAttribute("text-anchor", "end");
            textElement->addAttribute("x", cx + width / 2);
        }
        textElement->setContent(lines[0]);
    } else {
        XMLElement::ChildrenType spans;
        for (int i = 0; i < static_cast<int>(lines.size()); ++i) {
            double dy = SVGTextSize::DEFAULT_APPROXIMATION_HEIGHT_SCALE + SVGTextSize::DEFAULT_APPROXIMATION_LINE_SPACING_SCALE;
            if (i == 0) {
                dy = -(static_cast<double>(lines.size()) - 1) / 2 * dy;
            }
            const auto tspanElement = make_shared<XMLElement>("tspan");
            if (width > 0.0 && aligns[i] == 'l') {
                tspanElement->addAttribute("text-anchor", "start");
                tspanElement->addAttribute("x", cx - width / 2);
            } else if (width > 0.0 && aligns[i] == 'r') {
                tspanElement->addAttribute("text-anchor", "end");
                tspanElement->addAttribute("x", cx + width / 2);
            } else {
                tspanElement->addAttribute("x", cx);
            }
            tspanElement->addAttribute("dy", format("{}em", dy));
            tspanElement->setContent(lines[i]);
            spans.emplace_back(tspanElement);
        }
        textElement->addChildren(spans);
    }
    return {textElement};
}

SVGDrawBoundingBox SVGDrawText::boundingBox() const {
    const SVGTextSize textSize;
    const auto fontSize = stod(_attributes.at(SVG_ATTR_KEY_FONT_SIZE));
    const auto fontFamily = _attributes.at(SVG_ATTR_KEY_FONT_FAMILY);
    if (width != 0.0 && height != 0.0) {
        return {cx - width / 2.0, cy - height / 2.0, cx + width / 2.0, cy + height / 2.0};
    }
    const auto [_width, _height] = textSize.computeTextSize(text, fontSize, fontFamily);
    return {cx - _width / 2.0, cy - _height / 2.0, cx + _width / 2.0, cy + _height / 2.0};
}

string SVGDrawText::tag() const {
    return "text";
}

SVGDrawCircle::SVGDrawCircle(const double x, const double y, const double radius) {
    cx = x;
    cy = y;
    width = height = radius * 2;
}

XMLElement::ChildrenType SVGDrawCircle::generateXMLElements() const {
    const double radius = min(width, height) / 2;
    const auto circleElement = make_shared<XMLElement>(tag());
    circleElement->addAttribute("cx", cx);
    circleElement->addAttribute("cy", cy);
    circleElement->addAttribute("r", radius);
    addAttributesToXMLElement(circleElement);
    return {circleElement};
}

SVGDrawBoundingBox SVGDrawCircle::boundingBox() const {
    const double radius = min(width, height) / 2;
    return {cx - radius, cy - radius, cx + radius, cy + radius};
}

string SVGDrawCircle::tag() const {
    return "circle";
}

XMLElement::ChildrenType SVGDrawRect::generateXMLElements() const {
    const double x = cx - width / 2;
    const double y = cy - height / 2;
    const auto rectElement = make_shared<XMLElement>(tag());
    rectElement->addAttribute("x", x);
    rectElement->addAttribute("y", y);
    rectElement->addAttribute("width", width);
    rectElement->addAttribute("height", height);
    addAttributesToXMLElement(rectElement);
    return {rectElement};
}

string SVGDrawRect::tag() const {
    return "rect";
}

XMLElement::ChildrenType SVGDrawEllipse::generateXMLElements() const {
    const double rx = width / 2;
    const double ry = height / 2;
    const auto ellipseElement = make_shared<XMLElement>(tag());
    ellipseElement->addAttribute("cx", cx);
    ellipseElement->addAttribute("cy", cy);
    ellipseElement->addAttribute("rx", rx);
    ellipseElement->addAttribute("ry", ry);
    addAttributesToXMLElement(ellipseElement);
    return {ellipseElement};
}

string SVGDrawEllipse::tag() const {
    return "ellipse";
}

SVGDrawPolygon::SVGDrawPolygon(const vector<pair<double, double>>& points) {
    this->points = points;
}

XMLElement::ChildrenType SVGDrawPolygon::generateXMLElements() const {
    const auto polygonElement = make_shared<XMLElement>(tag());
    string path;
    if (!points.empty()) {
        path += format("{},{}", points[0].first, points[0].second);
        for (size_t i = 1; i < points.size(); ++i) {
            path += format(" {},{}", points[i].first, points[i].second);
        }
    }
    polygonElement->addAttribute("points", path);
    addAttributesToXMLElement(polygonElement);
    return {polygonElement};
}

SVGDrawBoundingBox SVGDrawPolygon::boundingBox() const {
    if (points.empty()) {
        return {};
    }
    double xMin = points[0].first, yMin = points[0].second;
    double xMax = points[0].first, yMax = points[0].second;
    for (size_t i = 1; i < points.size(); ++i) {
        xMin = min(xMin, points[i].first);
        xMax = max(xMax, points[i].first);
        yMin = min(yMin, points[i].second);
        yMax = max(yMax, points[i].second);
    }
    return {xMin, yMin, xMax, yMax};
}

string SVGDrawPolygon::tag() const {
    return "polygon";
}
