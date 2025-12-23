#include "svg_nodes.h"

#include <format>
#include <cmath>

#include "attribute_utils.h"
#include "svg_text_size.h"
#include "geometry_utils.h"
using namespace std;
using namespace svg_diagram;

SVGNode::SVGNode(const double cx, const double cy) {
    _cx = cx;
    _cy = cy;
}

void SVGNode::setAttributeIfNotExist(const string_view &key, const string &value) {
    if (attributes().contains(key)) {
        return;
    }
    if (parent() != nullptr) {
        if (const auto ret = parent()->defaultNodeAttribute(key); ret.has_value()) {
            return;
        }
    }
    setAttribute(key, value);
}

const string& SVGNode::getAttribute(const std::string_view& key) const {
    static const string EMPTY_STRING;
    if (const auto it = attributes().find(key); it != attributes().end()) {
        return it->second;
    }
    if (parent() != nullptr) {
        if (const auto ret = parent()->defaultNodeAttribute(key); ret.has_value()) {
            return ret.value();
        }
    }
    return EMPTY_STRING;
}

void SVGNode::setShape(const string& shape) {
    setAttribute(ATTR_KEY_SHAPE, shape);
}

void SVGNode::setShape(const string_view& shape) {
    setShape(string(shape));
}

void SVGNode::setCenter(const double cx, const double cy) {
    _cx = cx;
    _cy = cy;
}

pair<double, double> SVGNode::center() const {
    return {_cx, _cy};
}

void SVGNode::adjustNodeSize() {
    setAttributeIfNotExist(ATTR_KEY_SHAPE, string(SHAPE_DEFAULT));
    setAttributeIfNotExist(ATTR_KEY_FONT_NAME, string(ATTR_DEF_FONT_NAME));
    setAttributeIfNotExist(ATTR_KEY_FONT_SIZE, string(ATTR_DEF_FONT_SIZE));
    const auto shape = getAttribute(ATTR_KEY_SHAPE);
    if (shape == SHAPE_CIRCLE) {
        adjustNodeSizeCircle();
    } else if (shape == SHAPE_DOUBLE_CIRCLE) {
        adjustNodeSizeDoubleCircle();
    } else if (shape == SHAPE_NONE || shape == SHAPE_RECT) {
        adjustNodeSizeRect();
    } else if (shape == SHAPE_ELLIPSE) {
        adjustNodeSizeEllipse();
    }
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDraws() {
    setAttributeIfNotExist(ATTR_KEY_SHAPE, string(SHAPE_DEFAULT));
    setAttributeIfNotExist(ATTR_KEY_COLOR, string(ATTR_DEF_COLOR));
    setAttributeIfNotExist(ATTR_KEY_FILL_COLOR, string(ATTR_DEF_FILL_COLOR));
    setAttributeIfNotExist(ATTR_KEY_FONT_COLOR, string(ATTR_DEF_FONT_COLOR));
    setAttributeIfNotExist(ATTR_KEY_FONT_NAME, string(ATTR_DEF_FONT_NAME));
    setAttributeIfNotExist(ATTR_KEY_FONT_SIZE, string(ATTR_DEF_FONT_SIZE));
    setAttributeIfNotExist(ATTR_KEY_STYLE, string(ATTR_DEF_STYLE));
    const auto shape = getAttribute(ATTR_KEY_SHAPE);
    if (shape == SHAPE_CIRCLE) {
        return produceSVGDrawsCircle();
    }
    if (shape == SHAPE_DOUBLE_CIRCLE) {
        return produceSVGDrawsDoubleCircle();
    }
    if (shape == SHAPE_RECT) {
        return produceSVGDrawsRect();
    }
    if (shape == SHAPE_ELLIPSE) {
        return produceSVGDrawsEllipse();
    }
    return produceSVGDrawsNone();
}

pair<double, double> SVGNode::computeConnectionPoint(const double angle) {
    setAttributeIfNotExist(ATTR_KEY_SHAPE, string(SHAPE_DEFAULT));
    const auto shape = getAttribute(ATTR_KEY_SHAPE);
    if (shape == SHAPE_CIRCLE) {
        return computeConnectionPointCircle(angle);
    }
    if (shape == SHAPE_DOUBLE_CIRCLE) {
        return computeConnectionPointDoubleCircle(angle);
    }
    if (shape == SHAPE_RECT || shape == SHAPE_NONE) {
        return computeConnectionPointRect(angle);
    }
    if (shape == SHAPE_ELLIPSE) {
        return computeConnectionPointEllipse(angle);
    }
    return {0.0, 0.0};
}

double SVGNode::computeAngle(const double x, const double y) const {
    return atan2(y - _cy, x - _cx);
}

double SVGNode::computeAngle(const pair<double, double>& p) const {
    return computeAngle(p.first, p.second);
}

bool SVGNode::isFixedSize() const {
    return AttributeUtils::parseBool(getAttribute(ATTR_KEY_FIXED_SIZE));
}

void SVGNode::updateNodeSize(const double width, const double height) {
    if (isFixedSize()) {
        setDoubleAttributeIfNotExist(ATTR_KEY_WIDTH, AttributeUtils::pointToInch(width));
        setDoubleAttributeIfNotExist(ATTR_KEY_HEIGHT, AttributeUtils::pointToInch(height));
    } else {
        setWidth(width);
        setHeight(height);
    }
}

void SVGNode::updateNodeSize(const pair<double, double>& size) {
    updateNodeSize(size.first, size.second);
}

void SVGNode::appendSVGDrawsLabel(vector<unique_ptr<SVGDraw>>& svgDraws) {
    appendSVGDrawsLabelWithCenter(svgDraws, _cx, _cy);
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsNone() {
    vector<unique_ptr<SVGDraw>> svgDraws;
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

void SVGNode::adjustNodeSizeCircle() {
    const auto diameter = GeometryUtils::distance(computeTextSizeWithMargin());
    updateNodeSize(diameter, diameter);
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsCircle() {
    vector<unique_ptr<SVGDraw>> svgDraws;
    auto circle = make_unique<SVGDrawCircle>(_cx, _cy, max(width(), height()) / 2.0);
    setStrokeStyles(circle.get());
    circle->setFill(fillColor());
    svgDraws.emplace_back(std::move(circle));
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

pair<double, double> SVGNode::computeConnectionPointCircle(const double angle) const {
    const double radius = (width() + penWidth()) / 2.0;
    return {_cx + radius * cos(angle), _cy + radius * sin(angle)};
}

void SVGNode::adjustNodeSizeDoubleCircle() {
    adjustNodeSizeCircle();
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsDoubleCircle() {
    vector<unique_ptr<SVGDraw>> svgDraws;
    const double radius = max(width(), height()) / 2.0;
    auto circleInner = make_unique<SVGDrawCircle>(_cx, _cy, radius);
    setStrokeStyles(circleInner.get());
    circleInner->setFill(fillColor());
    svgDraws.emplace_back(std::move(circleInner));
    auto circleOuter = make_unique<SVGDrawCircle>(_cx, _cy, radius + DOUBLE_BORDER_MARGIN);
    setStrokeStyles(circleOuter.get());
    circleOuter->setFill("none");
    svgDraws.emplace_back(std::move(circleOuter));
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

std::pair<double, double> SVGNode::computeConnectionPointDoubleCircle(const double angle) const {
    const double radius = (width() + penWidth()) / 2.0 + DOUBLE_BORDER_MARGIN;
    return {_cx + radius * cos(angle), _cy + radius * sin(angle)};
}

void SVGNode::adjustNodeSizeRect() {
    updateNodeSize(computeTextSizeWithMargin());
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsRect() {
    vector<unique_ptr<SVGDraw>> svgDraws;
    auto rect = make_unique<SVGDrawRect>(_cx, _cy, width(), height());
    setStrokeStyles(rect.get());
    rect->setFill(fillColor());
    svgDraws.emplace_back(std::move(rect));
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

pair<double, double> SVGNode::computeConnectionPointRect(const double angle) const {
    const double strokeWidth = penWidth();
    const double totalWidth = width() + strokeWidth;
    const double totalHeight = height() + strokeWidth;
    double x1 = -totalWidth / 2, y1 = -totalHeight / 2;
    double x2 = totalWidth / 2, y2 = totalHeight / 2;
    const auto vertices = vector<pair<double, double>>{{x1, y1}, {x2, y1}, {x2, y2}, {x1, y2}};
    for (const auto& [x, y] : vertices) {
        if (GeometryUtils::isSameAngle(angle, x, y)) {
            return {_cx + x, _cy + y};
        }
    }
    for (int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        x1 = vertices[i].first;
        y1 = vertices[i].second;
        x2 = vertices[(i + 1) % vertices.size()].first;
        y2 = vertices[(i + 1) % vertices.size()].second;
        if (const auto intersect = GeometryUtils::intersect(angle, x1, y1, x2, y2); intersect != nullopt) {
            return {_cx + intersect.value().first, _cy + intersect.value().second};
        }
    }
    return {_cx, _cy};
}

void SVGNode::adjustNodeSizeEllipse() {
    const auto [textWidth, textHeight] = computeTextSize();
    const auto [marginX, marginY] = computeMargin();
    updateNodeSize((textWidth + marginX * 2) * sqrt(2.0), (textHeight + marginY * 2) * sqrt(2.0));
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsEllipse() {
    vector<unique_ptr<SVGDraw>> svgDraws;
    auto ellipse = make_unique<SVGDrawEllipse>(_cx, _cy, width(), height());
    setStrokeStyles(ellipse.get());
    ellipse->setFill(fillColor());
    svgDraws.emplace_back(std::move(ellipse));
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

pair<double, double> SVGNode::computeConnectionPointEllipse(const double angle) const {
    const double strokeWidth = penWidth();
    const double totalWidth = width() + strokeWidth;
    const double totalHeight = height() + strokeWidth;
    const double rx = totalWidth / 2, ry = totalHeight / 2;
    const double base = sqrt(ry * ry * cos(angle) * cos(angle) + rx * rx * sin(angle) * sin(angle));
    const double x = rx * ry * cos(angle) / base;
    const double y = rx * ry * sin(angle) / base;
    return {_cx + x, _cy + y};
}
