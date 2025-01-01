#include "svg_draw.h"
#include "svg_text_size.h"
#include "attribute_utils.h"

#include <format>
#include <iostream>
#include <ranges>
#include <regex>
#include <sstream>
using namespace std;
using namespace svg_diagram;

SVGDrawBoundingBox::SVGDrawBoundingBox(double x1, double y1, double x2, double y2) {
    if (x1 > x2) {
        swap(x1, x2);
    }
    if (y1 > y2) {
        swap(y1, y2);
    }
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}

string SVGDraw::singletonName() const {
    return "";
}

void SVGDraw::setSingletonName(const string& singletonName) {
    _singletonName = singletonName;
}

bool SVGDraw::isDefs() const {
    return false;
}

void SVGDraw::setNumDecimals(const int numDecimals) {
    _numDecimals = numDecimals;
}

void SVGDraw::addAttributesToXMLElement(const XMLElement::ChildType& element) const {
    auto keys_view = _attributes | std::views::keys;
    std::vector<string> keys(keys_view.begin(), keys_view.end());
    ranges::sort(keys);
    for (const auto& key : keys) {
        if (const auto& value = _attributes.at(key); !value.empty()) {
            element->addAttribute(key, value);
        }
    }
}

SVGDrawComment::SVGDrawComment(const string& comment) {
    this->comment = comment;
}

XMLElement::ChildrenType SVGDrawComment::generateXMLElements() const {
    return {make_shared<XMLElementComment>(comment)};
}

SVGDrawBoundingBox SVGDrawComment::boundingBox() const {
    return {};
}

bool SVGDrawComment::hasEntity() const {
    return false;
}

void SVGDrawAttribute::setAttribute(const string_view& key, const string& value) {
    _attributes[key] = value;
}

void SVGDrawAttribute::setFill(const string& value) {
    setAttribute(SVG_ATTR_KEY_FILL, value);
}

void SVGDrawAttribute::setStroke(const string& value) {
    setAttribute(SVG_ATTR_KEY_STROKE, value);
}

void SVGDrawAttribute::setStrokeWidth(const string& value) {
    setAttribute(SVG_ATTR_KEY_STROKE_WIDTH, value);
}

bool SVGDrawEntity::hasEntity() const {
    return true;
}

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

void SVGDrawText::setFont(const string& fontFamily, double fontSize) {
    setAttribute(SVG_ATTR_KEY_FONT_FAMILY, fontFamily);
    setAttribute(SVG_ATTR_KEY_FONT_SIZE, format("{}", fontSize));
}

XMLElement::ChildrenType SVGDrawText::generateXMLElements() const {
    auto splitLines = [](const string& s) -> vector<string> {
        regex re("\r\n|\r|\n");
        sregex_token_iterator it(s.begin(), s.end(), re, -1);
        sregex_token_iterator end;
        return {it, end};
    };
    const auto textElement = make_shared<XMLElement>("text");
    textElement->addAttribute("x", cx);
    textElement->addAttribute("y", cy);
    textElement->addAttribute("text-anchor", "middle");
    textElement->addAttribute("dominant-baseline", "central");
    addAttributesToXMLElement(textElement);
    if (const auto lines = splitLines(text); lines.size() == 1) {
        textElement->setContent(text);
    } else {
        XMLElement::ChildrenType spans;
        for (int i = 0; i < lines.size(); ++i) {
            double dy = SVGTextSize::DEFAULT_APPROXIMATION_HEIGHT_SCALE + SVGTextSize::DEFAULT_APPROXIMATION_LINE_SPACING_SCALE;
            if (i == 0) {
                dy = -(static_cast<double>(lines.size()) - 1) / 2 * dy;
            }
            const auto tspanElement = make_shared<XMLElement>("tspan");
            tspanElement->addAttribute("x", cx);
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
    const auto [width, height] = textSize.computeTextSize(text, fontSize, fontFamily);
    return {cx - width / 2.0, cy - height / 2.0, cx + width / 2.0, cy + height / 2.0};
}

SVGDrawCircle::SVGDrawCircle(const double x, const double y, const double radius) {
    cx = x;
    cy = y;
    width = height = radius * 2;
}

XMLElement::ChildrenType SVGDrawCircle::generateXMLElements() const {
    const double radius = min(width, height) / 2;
    const auto circleElement = make_shared<XMLElement>("circle");
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

XMLElement::ChildrenType SVGDrawRect::generateXMLElements() const {
    const double x = cx - width / 2;
    const double y = cy - height / 2;
    const auto rectElement = make_shared<XMLElement>("rect");
    rectElement->addAttribute("x", x);
    rectElement->addAttribute("y", y);
    rectElement->addAttribute("width", width);
    rectElement->addAttribute("height", height);
    addAttributesToXMLElement(rectElement);
    return {rectElement};
}

XMLElement::ChildrenType SVGDrawEllipse::generateXMLElements() const {
    const double rx = width / 2;
    const double ry = height / 2;
    const auto ellipseElement = make_shared<XMLElement>("ellipse");
    ellipseElement->addAttribute("cx", cx);
    ellipseElement->addAttribute("cy", cy);
    ellipseElement->addAttribute("rx", rx);
    ellipseElement->addAttribute("ry", ry);
    addAttributesToXMLElement(ellipseElement);
    return {ellipseElement};
}

SVGDrawLine::SVGDrawLine(const double x1, const double y1, const double x2, const double y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

XMLElement::ChildrenType SVGDrawLine::generateXMLElements() const {
    const auto lineElement = make_shared<XMLElement>("line");
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

SVGDrawPath::SVGDrawPath(const string& d) {
    this->d = d;
}

XMLElement::ChildrenType SVGDrawPath::generateXMLElements() const {
    const auto commands = AttributeUtils::parseDCommands(d);
    string reformat;
    for (int i = 0; i < commands.size(); ++i) {
        const auto& [command, parameters] = commands[i];
        if (i > 0) {
            reformat += ' ';
        }
        reformat += command;
        for (const auto& parameter : parameters) {
            reformat += format(" {}", parameter);
        }
    }
    const auto pathElement = make_shared<XMLElement>("path");
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

bool SVGDrawDefs::isDefs() const {
    return true;
}

bool SVGDrawDefs::hasEntity() const {
    return false;
}

SVGDrawBoundingBox SVGDrawDefs::boundingBox() const {
    return {};
}

void SVGDrawMarker::setShape(const string& shape) {
    _shape = shape;
}

string SVGDrawMarker::singletonName() const {
    string fill = "black";
    if (const auto it = _attributes.find(SVG_ATTR_KEY_FILL); it != _attributes.end()) {
        fill = it->second;
    }
    string stroke = "none";
    if (const auto it = _attributes.find(SVG_ATTR_KEY_STROKE); it != _attributes.end()) {
        stroke = it->second;
    }
    return format("arrow_type_{}__fill_{}__stroke_{}", _shape, fill, stroke);
}

XMLElement::ChildrenType SVGDrawMarker::generateXMLElements() const {
    if (_shape == SHAPE_NORMAL) {
        return renderNormal();
    }
    cerr << "Unknown marker shape: " << _shape << endl;
    return {};
}

XMLElement::ChildrenType SVGDrawMarker::renderNormal() const {
    const auto markerElement = make_shared<XMLElement>("marker");
    markerElement->addAttribute("id", singletonName());
    markerElement->addAttribute("markerWidth", 10.0);
    markerElement->addAttribute("markerHeight", 7.0);
    markerElement->addAttribute("refX", 10.0);
    markerElement->addAttribute("refY", 3.5);
    markerElement->addAttribute("orient", "auto-start-reverse");
    const auto polygonElement = make_shared<XMLElement>("polygon");
    polygonElement->addAttribute("points", format("0 0 10 3.5 0 7"));
    addAttributesToXMLElement(polygonElement);
    markerElement->addChild(polygonElement);
    return {markerElement};
}
