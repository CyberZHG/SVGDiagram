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

void SVGDraw::setAttribute(const string_view& key, const string& value) {
    _attributes[key] = value;
}

void SVGDraw::setFill(const string& value) {
    setAttribute(SVG_ATTR_KEY_FILL, value);
}

void SVGDraw::setStroke(const string& value) {
    setAttribute(SVG_ATTR_KEY_STROKE, value);
}

void SVGDraw::setStrokeWidth(const string& value) {
    setAttribute(SVG_ATTR_KEY_STROKE_WIDTH, value);
}

void SVGDraw::setStrokeWidth(const double value) {
    setStrokeWidth(format("{}", value));
}

void SVGDraw::setStrokeDashArray(const string& value) {
    setAttribute(SVG_ATTR_KEY_STROKE_DASHARRAY, value);
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

SVGDrawGroup::SVGDrawGroup(vector<unique_ptr<SVGDraw>>& draws) {
    this->addChildren(draws);
}

void SVGDrawGroup::addChild(unique_ptr<SVGDraw> child) {
    children.emplace_back(std::move(child));
}

void SVGDrawGroup::addChildren(vector<unique_ptr<SVGDraw>>& draws) {
    for (auto& child : draws) {
        children.emplace_back(std::move(child));
    }
}

XMLElement::ChildrenType SVGDrawGroup::generateXMLElements() const {
    const auto groupElement = make_shared<XMLElement>("g");
    addAttributesToXMLElement(groupElement);
    for (const auto& child : children) {
        groupElement->addChildren(child->generateXMLElements());
    }
    return {groupElement};
}

SVGDrawBoundingBox SVGDrawGroup::boundingBox() const {
    double xMin = 0.0, yMin = 0.0, xMax = 1.0, yMax = 1.0;
    bool first = true;
    for (const auto& child : children) {
        if (child->hasEntity()) {
            const auto [x1, y1, x2, y2] = child->boundingBox();
            if (first) {
                first = false;
                xMin = x1, yMin = y1;
                xMax = x2, yMax = y2;
            } else {
                xMin = min(xMin, x1);
                xMax = max(xMax, x2);
                yMin = min(yMin, y1);
                yMax = max(yMax, y2);
            }
        }
    }
    return {xMin, yMin, xMax, yMax};
}

bool SVGDrawGroup::hasEntity() const {
    for (const auto& child : children) {
        if (child->hasEntity()) {
            return true;
        }
    }
    return false;
}

SVGDrawTitle::SVGDrawTitle(const string& title) {
    this->title = title;
}

XMLElement::ChildrenType SVGDrawTitle::generateXMLElements() const {
    const auto titleElement = make_shared<XMLElement>("title");
    addAttributesToXMLElement(titleElement);
    titleElement->setContent(title);
    return {titleElement};
}

SVGDrawBoundingBox SVGDrawTitle::boundingBox() const {
    return {};
}

bool SVGDrawTitle::hasEntity() const {
    return false;
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
        for (int i = 0; i < static_cast<int>(lines.size()); ++i) {
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

SVGDrawPolygon::SVGDrawPolygon(const vector<pair<double, double>>& points) {
    this->points = points;
}

XMLElement::ChildrenType SVGDrawPolygon::generateXMLElements() const {
    const auto polygonElement = make_shared<XMLElement>("polygon");
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
