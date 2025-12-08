#include "svg_nodes.h"

#include <format>
#include <cmath>

#include "attribute_utils.h"
#include "svg_text_size.h"
#include "geometry_utils.h"
using namespace std;
using namespace svg_diagram;

void SVGItem::setAttribute(const string_view& key, const string& value) {
    _attributes[key] = value;
}

void SVGItem::setAttributeIfNotExist(const string_view& key, const string& value) {
    if (!_attributes.contains(key)) {
        _attributes[key] = value;
    }
}

const string& SVGItem::getAttribute(const string_view& key) const {
    static const string EMPTY_STRING;
    if (const auto it = _attributes.find(key); it != _attributes.end()) {
        return it->second;
    }
    return EMPTY_STRING;
}

void SVGItem::setPrecomputedTextSize(const double width, const double height) {
    _precomputedTextWidth = width;
    _precomputedTextHeight = height;
}

std::pair<double, double> SVGItem::precomputedTextSize() const {
    return {_precomputedTextWidth, _precomputedTextHeight};
}

void SVGItem::setLabel(const string& label) {
    setAttribute(DOT_ATTR_KEY_LABEL, label);
}

void SVGItem::setMargin(const string& value) {
    setAttribute(DOT_ATTR_KEY_MARGIN, value);
}

void SVGItem::setMargin(const double margin) {
    setMargin(format("{}", margin));
}

void SVGItem::setMargin(const double marginX, const double marginY) {
    setMargin(format("{},{}", marginX, marginY));
}

void SVGItem::setMarginInPoints(const double margin) {
    setMargin(margin / SVG_DEFAULT_DPI);
}

void SVGItem::setMarginInPoints(const double marginX, const double marginY) {
    setMargin(marginX / SVG_DEFAULT_DPI, marginY / SVG_DEFAULT_DPI);
}

void SVGItem::setColor(const string& color) {
    setAttribute(DOT_ATTR_KEY_COLOR, color);
}

void SVGItem::setFillColor(const string& color) {
    setAttribute(DOT_ATTR_KEY_FILL_COLOR, color);
}

void SVGItem::setFontColor(const string& color) {
    setAttribute(DOT_ATTR_KEY_FONT_COLOR, color);
}

void SVGItem::setPenWidth(const double width) {
    setAttribute(DOT_ATTR_KEY_PEN_WIDTH, format("{}", width));
}

double SVGItem::penWidth() const {
    if (const auto it = _attributes.find(DOT_ATTR_KEY_PEN_WIDTH); it != _attributes.end()) {
        const auto width = AttributeUtils::pointToSVGPixel(AttributeUtils::parseLengthToInch(it->second));
        if (fabs(width - 1.0) < GeometryUtils::EPSILON) {
            return 1.0;
        }
        return width;
    }
    return 1.0;
}

void SVGItem::appendSVGDrawsLabelWithCenter(vector<unique_ptr<SVGDraw>>& svgDraws, const double cx, const double cy) {
    if (enabledDebug()) {
        const auto [textWidth, textHeight] = computeTextSize();
        const auto [marginX, marginY] = computeMarginInPoints();
        auto textRect = make_unique<SVGDrawRect>(cx, cy, textWidth, textHeight);
        textRect->setFill("none");
        textRect->setStroke("blue");
        svgDraws.emplace_back(std::move(textRect));
        auto marginRect = make_unique<SVGDrawRect>(cx, cy, textWidth + marginX * 2, textHeight + marginY * 2);
        marginRect->setFill("none");
        marginRect->setStroke("red");
        svgDraws.emplace_back(std::move(marginRect));
    }
    if (const auto label = getAttribute(DOT_ATTR_KEY_LABEL); !label.empty()) {
        auto draw = make_unique<SVGDrawText>(cx, cy, label);
        if (const auto& fontColor = getAttribute(DOT_ATTR_KEY_FONT_COLOR); fontColor != "black") {
            draw->setFill(fontColor);
        }
        svgDraws.emplace_back(std::move(draw));
    }
}

pair<double, double> SVGItem::computeTextSize() {
    if (const auto [precomputedTextWidth, precomputedTextHeight] = precomputedTextSize();
        precomputedTextWidth > 0 && precomputedTextHeight > 0) {
        return {precomputedTextWidth, precomputedTextHeight};
        }
    const SVGTextSize textSize;
    const auto label = getAttribute(DOT_ATTR_KEY_LABEL);
    setAttributeIfNotExist(DOT_ATTR_KEY_FONT_NAME, "Times,serif");
    setAttributeIfNotExist(DOT_ATTR_KEY_FONT_SIZE, "14");
    const double fontSize = stod(getAttribute(DOT_ATTR_KEY_FONT_SIZE));
    const string fontFamily = getAttribute(DOT_ATTR_KEY_FONT_NAME);
    auto [width, height] = textSize.computeTextSize(label, fontSize, fontFamily);
    if (width == 0.0) {
        width = fontSize * SVGTextSize::DEFAULT_APPROXIMATION_WIDTH_SCALE;
    }
    if (height == 0.0) {
        height = fontSize * SVGTextSize::DEFAULT_APPROXIMATION_HEIGHT_SCALE;
    }
    return {width, height};
}

pair<double, double> SVGItem::computeMarginInPoints() {
    setAttributeIfNotExist(DOT_ATTR_KEY_MARGIN, "0.11,0.055");
    const auto margin = getAttribute(DOT_ATTR_KEY_MARGIN);
    return AttributeUtils::parseMarginToPixels(margin);
}

std::pair<double, double> SVGItem::computeTextSizeWithMargin() {
    const auto [width, height] = computeTextSize();
    const auto [marginX, marginY] = computeMarginInPoints();
    return {width + marginX * 2, height + marginY * 2};
}

void SVGItem::enableDebug() {
    _enabledDebug = true;
}

bool SVGItem::enabledDebug() const {
    return _enabledDebug;
}


SVGNode::SVGNode(const double cx, const double cy) {
    _cx = cx;
    _cy = cy;
}

void SVGNode::setShape(const string& shape) {
    setAttribute(DOT_ATTR_KEY_SHAPE, shape);
}

void SVGNode::setShape(const string_view& shape) {
    setShape(string(shape));
}

void SVGNode::setCenterInPoints(const double cx, const double cy) {
    _cx = cx;
    _cy = cy;
}

pair<double, double> SVGNode::centerInPoints() const {
    return {_cx, _cy};
}

void SVGNode::adjustNodeSize() {
    setAttributeIfNotExist(DOT_ATTR_KEY_SHAPE, string(NODE_SHAPE_DEFAULT));
    const auto shape = getAttribute(DOT_ATTR_KEY_SHAPE);
    if (shape == NODE_SHAPE_CIRCLE) {
        adjustNodeSizeCircle();
    } else if (shape == NODE_SHAPE_NONE || shape == NODE_SHAPE_RECT) {
        adjustNodeSizeRect();
    } else if (shape == NODE_SHAPE_ELLIPSE) {
        adjustNodeSizeEllipse();
    }
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDraws() {
    setAttributeIfNotExist(DOT_ATTR_KEY_SHAPE, string(NODE_SHAPE_DEFAULT));
    setAttributeIfNotExist(DOT_ATTR_KEY_COLOR, "black");
    setAttributeIfNotExist(DOT_ATTR_KEY_FILL_COLOR, "none");
    setAttributeIfNotExist(DOT_ATTR_KEY_FONT_COLOR, "black");
    setAttributeIfNotExist(DOT_ATTR_KEY_PEN_WIDTH, format("{}", AttributeUtils::svgPixelToPoint(1.0)));
    const auto shape = getAttribute(DOT_ATTR_KEY_SHAPE);
    if (shape == NODE_SHAPE_NONE) {
        return produceSVGDrawsNone();
    }
    if (shape == NODE_SHAPE_CIRCLE) {
        return produceSVGDrawsCircle();
    }
    if (shape == NODE_SHAPE_RECT) {
        return produceSVGDrawsRect();
    }
    if (shape == NODE_SHAPE_ELLIPSE) {
        return produceSVGDrawsEllipse();
    }
    return {};
}

pair<double, double> SVGNode::computeConnectionPoint(const double angle) {
    setAttributeIfNotExist(DOT_ATTR_KEY_SHAPE, string(NODE_SHAPE_DEFAULT));
    const auto shape = getAttribute(DOT_ATTR_KEY_SHAPE);
    if (shape == NODE_SHAPE_CIRCLE) {
        return computeConnectionPointCircle(angle);
    }
    if (shape == NODE_SHAPE_RECT) {
        return computeConnectionPointRect(angle);
    }
    if (shape == NODE_SHAPE_ELLIPSE) {
        return computeConnectionPointEllipse(angle);
    }
    return {0.0, 0.0};
}

/*
pair<double, double> SVGNode::computeConnectionPoint(const double x1, const double y1, const double x2, const double y2) {
    return computeConnectionPoint(atan2(y2 - y1, x2 - x1));
}

pair<double, double> SVGNode::computeConnectionPoint(const double x, const double y) {
    return computeConnectionPoint(_cx, _cy, x, y);
}

pair<double, double> SVGNode::computeConnectionPoint(const pair<double, double>& p) {
    return computeConnectionPoint(p.first, p.second);
}
*/

double SVGNode::computeAngle(const double x, const double y) const {
    return atan2(y - _cy, x - _cx);
}

double SVGNode::computeAngle(const pair<double, double>& p) const {
    return computeAngle(p.first, p.second);
}

bool SVGNode::isFixedSize() const {
    return AttributeUtils::parseBool(getAttribute(DOT_ATTR_KEY_FIXED_SIZE));
}

void SVGNode::updateNodeSize(const double width, const double height) {
    const auto widthString = format("{}", width);
    const auto heightString = format("{}", height);
    if (isFixedSize()) {
        setAttributeIfNotExist(DOT_ATTR_KEY_WIDTH, widthString);
        setAttributeIfNotExist(DOT_ATTR_KEY_HEIGHT, heightString);
    } else {
        setAttribute(DOT_ATTR_KEY_WIDTH, widthString);
        setAttribute(DOT_ATTR_KEY_HEIGHT, heightString);
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
    const double width = stod(getAttribute(DOT_ATTR_KEY_WIDTH));
    const double height = stod(getAttribute(DOT_ATTR_KEY_WIDTH));
    vector<unique_ptr<SVGDraw>> svgDraws;
    auto circle = make_unique<SVGDrawCircle>(_cx, _cy, max(width, height) / 2.0);
    circle->setStroke(getAttribute(DOT_ATTR_KEY_COLOR));
    circle->setFill(getAttribute(DOT_ATTR_KEY_FILL_COLOR));
    if (const auto strokeWidth = penWidth(); strokeWidth != 1.0) {
        circle->setStrokeWidth(getAttribute(DOT_ATTR_KEY_PEN_WIDTH));
    }
    svgDraws.emplace_back(std::move(circle));
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

pair<double, double> SVGNode::computeConnectionPointCircle(const double angle) const {
    const double width = stod(getAttribute(DOT_ATTR_KEY_WIDTH));
    const double penWidth = stod(getAttribute(DOT_ATTR_KEY_PEN_WIDTH));
    const double radius = (width + penWidth) / 2.0;
    return {_cx + radius * cos(angle), _cy + radius * sin(angle)};
}

void SVGNode::adjustNodeSizeRect() {
    updateNodeSize(computeTextSizeWithMargin());
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsRect() {
    const double width = stod(getAttribute(DOT_ATTR_KEY_WIDTH));
    const double height = stod(getAttribute(DOT_ATTR_KEY_HEIGHT));
    vector<unique_ptr<SVGDraw>> svgDraws;
    auto rect = make_unique<SVGDrawRect>(_cx, _cy, width, height);
    rect->setStroke(getAttribute(DOT_ATTR_KEY_COLOR));
    rect->setFill(getAttribute(DOT_ATTR_KEY_FILL_COLOR));
    if (const auto strokeWidth = penWidth(); strokeWidth != 1.0) {
        rect->setStrokeWidth(getAttribute(DOT_ATTR_KEY_PEN_WIDTH));
    }
    svgDraws.emplace_back(std::move(rect));
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

pair<double, double> SVGNode::computeConnectionPointRect(const double angle) const {
    const double strokeWidth = stod(getAttribute(DOT_ATTR_KEY_PEN_WIDTH));
    const double width = stod(getAttribute(DOT_ATTR_KEY_WIDTH)) + strokeWidth;
    const double height = stod(getAttribute(DOT_ATTR_KEY_HEIGHT)) + strokeWidth;
    double x1 = -width / 2, y1 = -height / 2;
    double x2 = width / 2, y2 = height / 2;
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
    const auto [marginX, marginY] = computeMarginInPoints();
    updateNodeSize((textWidth + marginX * 2) * sqrt(2.0), (textHeight + marginY * 2) * sqrt(2.0));
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsEllipse() {
    const double width = stod(getAttribute(DOT_ATTR_KEY_WIDTH));
    const double height = stod(getAttribute(DOT_ATTR_KEY_HEIGHT));
    vector<unique_ptr<SVGDraw>> svgDraws;
    auto ellipse = make_unique<SVGDrawEllipse>(_cx, _cy, width, height);
    ellipse->setStroke(getAttribute(DOT_ATTR_KEY_COLOR));
    ellipse->setFill(getAttribute(DOT_ATTR_KEY_FILL_COLOR));
    if (const auto strokeWidth = penWidth(); strokeWidth != 1.0) {
        ellipse->setStrokeWidth(getAttribute(DOT_ATTR_KEY_PEN_WIDTH));
    }
    svgDraws.emplace_back(std::move(ellipse));
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

pair<double, double> SVGNode::computeConnectionPointEllipse(const double angle) const {
    const double strokeWidth = stod(getAttribute(DOT_ATTR_KEY_PEN_WIDTH));
    const double width = stod(getAttribute(DOT_ATTR_KEY_WIDTH)) + strokeWidth;
    const double height = stod(getAttribute(DOT_ATTR_KEY_HEIGHT)) + strokeWidth;
    const double rx = width / 2, ry = height / 2;
    const double base = sqrt(ry * ry * cos(angle) * cos(angle) + rx * rx * sin(angle) * sin(angle));
    const double x = rx * ry * cos(angle) / base;
    const double y = rx * ry * sin(angle) / base;
    return {_cx + x, _cy + y};
}

SVGEdge::SVGEdge(const string& idFrom, const string& idTo) {
    _nodeFrom = idFrom;
    _nodeTo = idTo;
}

void SVGEdge::setNodeFrom(const string& id) {
    _nodeFrom = id;
}

const string& SVGEdge::nodeFrom() const {
    return _nodeFrom;
}

void SVGEdge::setNodeTo(const string& id) {
    _nodeTo = id;
}

const string& SVGEdge::nodeTo() const {
    return _nodeTo;
}

void SVGEdge::setConnection(const string& idFrom, const string& idTo) {
    _nodeFrom = idFrom;
    _nodeTo = idTo;
}

void SVGEdge::setSplines(const string& value) {
    setAttribute(DOT_ATTR_KEY_SPLINES, value);
}

void SVGEdge::setSplines(const string_view& value) {
    setSplines(string(value));
}

void SVGEdge::addConnectionPoint(const pair<double, double>& point) {
    _connectionPoints.emplace_back(point);
}

void SVGEdge::addConnectionPoint(const double x, const double y) {
    addConnectionPoint({x, y});
}

vector<unique_ptr<SVGDraw>> SVGEdge::produceSVGDraws(const NodesMapping& nodes) {
    setAttributeIfNotExist(DOT_ATTR_KEY_SPLINES, string(EDGE_SPLINES_DEFAULT));
    setAttributeIfNotExist(DOT_ATTR_KEY_COLOR, "black");
    setAttributeIfNotExist(DOT_ATTR_KEY_PEN_WIDTH, "1");
    setAttributeIfNotExist(DOT_ATTR_KEY_ARROW_HEAD, "none");
    setAttributeIfNotExist(DOT_ATTR_KEY_ARROW_TAIL, "none");
    setAttributeIfNotExist(DOT_ATTR_KEY_MARGIN, "0,0");
    const auto splines = getAttribute(DOT_ATTR_KEY_SPLINES);
    if (splines == EDGE_SPLINES_LINE) {
        return produceSVGDrawsLine(nodes);
    }
    if (splines == EDGE_SPLINES_SPLINE) {
        return produceSVGDrawsSpline(nodes);
    }
    return {};
}

void SVGEdge::setArrowHead() {
    setArrowHead(ARROW_SHAPE_DEFAULT);
}

void SVGEdge::setArrowHead(const string_view& shape) {
    setAttribute(DOT_ATTR_KEY_ARROW_HEAD, string(shape));
}

void SVGEdge::setArrowTail() {
    setArrowTail(ARROW_SHAPE_DEFAULT);
}

void SVGEdge::setArrowTail(const string_view& shape) {
    setAttribute(DOT_ATTR_KEY_ARROW_TAIL, string(shape));
}

std::pair<double, double> SVGEdge::computeTextCenter(const double cx, const double cy, double dx, double dy) {
    const auto [width, height] = computeTextSizeWithMargin();
    const auto points = vector<pair<double, double>>{
        {cx - width / 2, cy - height / 2},
        {cx - width / 2, cy + height / 2},
        {cx + width / 2, cy + height / 2},
        {cx + width / 2, cy - height / 2},
    };
    const auto d = GeometryUtils::normalize(dx, dy);
    dx = d.first, dy = d.second;
    const double ux = -dy, uy = dx;
    double maxShift = 0.0;
    for (const auto& [x, y] : points) {
        const double totalArea = GeometryUtils::cross(x - cx, y - cy, dx, dy);
        const double unitArea = GeometryUtils::cross(dx, dy, ux, uy);
        const double shift = totalArea / unitArea;
        maxShift = max(maxShift, shift);
    }
    return {cx + ux * maxShift, cy + uy * maxShift};
}

vector<unique_ptr<SVGDraw>> SVGEdge::produceSVGDrawsLine(const NodesMapping& nodes) {
    const auto& nodeFrom = nodes.at(_nodeFrom);
    const auto& nodeTo = nodes.at(_nodeTo);
    const auto arrowHeadShape = getAttribute(DOT_ATTR_KEY_ARROW_HEAD);
    const auto arrowTailShape = getAttribute(DOT_ATTR_KEY_ARROW_TAIL);
    vector<unique_ptr<SVGDraw>> svgDraws;
    vector<unique_ptr<SVGDraw>> svgDrawArrows;
    vector<pair<double, double>> points;
    if (_connectionPoints.empty()) {
        const double angleFrom = nodeFrom->computeAngle(nodeTo->centerInPoints());
        const double angleTo = nodeTo->computeAngle(nodeFrom->centerInPoints());
        points.emplace_back(addArrow(arrowTailShape, svgDrawArrows, nodeFrom->computeConnectionPoint(angleFrom), angleFrom));
        points.emplace_back(addArrow(arrowHeadShape, svgDrawArrows, nodeTo->computeConnectionPoint(angleTo), angleTo));
    } else {
        const double angleFrom = nodeFrom->computeAngle(_connectionPoints[0]);
        points.emplace_back(addArrow(arrowTailShape, svgDrawArrows, nodeFrom->computeConnectionPoint(angleFrom), angleFrom));
        for (const auto& [x, y] : _connectionPoints) {
            points.emplace_back(x, y);
        }
        const size_t n = _connectionPoints.size();
        const double angleTo = nodeTo->computeAngle(_connectionPoints[n - 1]);
        points.emplace_back(addArrow(arrowHeadShape, svgDrawArrows, nodeTo->computeConnectionPoint(angleTo), angleTo));
    }
    for (size_t i = 0; i + 1 < points.size(); ++i) {
        const auto& [x1, y1] = points[i];
        const auto& [x2, y2] = points[i + 1];
        svgDraws.emplace_back(make_unique<SVGDrawLine>(x1, y1, x2, y2));
    }
    const auto strokeWidth = penWidth();
    for (const auto& line : svgDraws) {
        const auto& draw = dynamic_cast<SVGDrawLine*>(line.get());
        draw->setStroke(getAttribute(DOT_ATTR_KEY_COLOR));
        if (strokeWidth != 1.0) {
            draw->setStrokeWidth(getAttribute(DOT_ATTR_KEY_PEN_WIDTH));
        }
    }
    for (auto& arrow : svgDrawArrows) {
        svgDraws.emplace_back(std::move(arrow));
    }
    if (const auto label = getAttribute(DOT_ATTR_KEY_LABEL); !label.empty()) {
        double totalLength = 0.0;
        for (size_t i = 0; i + 1 < points.size(); ++i) {
            const auto& [x1, y1] = points[i];
            const auto& [x2, y2] = points[i + 1];
            totalLength += GeometryUtils::distance(x1, y1, x2, y2);
        }
        const double halfLength = totalLength / 2.0;
        double sumLength = 0.0;
        size_t index = 0;
        double lineX = 0.0, lineY = 0.0;
        for (size_t i = 0; i + 1 < points.size(); ++i) {
            const auto& [x1, y1] = points[i];
            const auto& [x2, y2] = points[i + 1];
            const double length = GeometryUtils::distance(x1, y1, x2, y2);
            const double nextSum = sumLength + length;
            if (nextSum > halfLength) {
                index = i;
                const double ratio = (halfLength - sumLength) / length;
                lineX = x1 + ratio * (x2 - x1);
                lineY = y1 + ratio * (y2 - y1);
                break;
            }
            sumLength = nextSum;
        }
        const double dx = points[index + 1].first - points[index].first;
        const double dy = points[index + 1].second - points[index].second;
        const auto [cx, cy] = computeTextCenter(lineX, lineY, dx, dy);
        appendSVGDrawsLabelWithCenter(svgDraws, cx, cy);
    }
    return svgDraws;
}

vector<unique_ptr<SVGDraw>> SVGEdge::produceSVGDrawsSpline(const NodesMapping& nodes) {
    static constexpr double NUM_SPLINE_LENGTH_APPROXIMATION_SEGMENTS = 100;
    constexpr double SPLINE_LENGTH_APPROXIMATION_STEP = 1.0 / NUM_SPLINE_LENGTH_APPROXIMATION_SEGMENTS;
    if (_connectionPoints.empty()) {
        return produceSVGDrawsLine(nodes);
    }
    const auto& nodeFrom = nodes.at(_nodeFrom);
    const auto& nodeTo = nodes.at(_nodeTo);
    const auto arrowHeadShape = getAttribute(DOT_ATTR_KEY_ARROW_HEAD);
    const auto arrowTailShape = getAttribute(DOT_ATTR_KEY_ARROW_TAIL);
    vector<unique_ptr<SVGDraw>> svgDraws;
    vector<unique_ptr<SVGDraw>> svgDrawArrows;
    const auto strokeWidth = penWidth();
    vector<pair<double, double>> points;
    const double angleFrom = nodeFrom->computeAngle(_connectionPoints[0]);
    auto [sx, sy] = addArrow(arrowTailShape, svgDrawArrows, nodeFrom->computeConnectionPoint(angleFrom), angleFrom);
    points.emplace_back(sx, sy);
    points.emplace_back(sx, sy);
    for (const auto& [x, y] : _connectionPoints) {
        points.emplace_back(x, y);
    }
    const double angleTo = nodeTo->computeAngle(_connectionPoints[_connectionPoints.size() - 1]);
    auto [ex, ey] = addArrow(arrowHeadShape, svgDrawArrows, nodeTo->computeConnectionPoint(angleTo), angleTo);
    points.emplace_back(ex, ey);
    points.emplace_back(ex, ey);
    auto d = format("M {} {}", points[1].first, points[1].second);
    vector<vector<pair<double, double>>> splines;
    for (int i = 1; i + 2 < static_cast<int>(points.size()); ++i) {
        const auto [x0, y0] = points[i - 1];
        const auto [x1, y1] = points[i];
        const auto [x2, y2] = points[i + 1];
        const auto [x3, y3] = points[i + 2];
        const double c1x = x1 + (x2 - x0) / 6.0;
        const double c1y = y1 + (y2 - y0) / 6.0;
        const double c2x = x2 - (x3 - x1) / 6.0;
        const double c2y = y2 - (y3 - y1) / 6.0;
        d += format(" C {} {} {} {} {} {}", c1x, c1y, c2x, c2y, x2, y2);
        splines.emplace_back(vector{points[i], {c1x, c1y}, {c2x, c2y}, points[i + 1]});
    }
    auto path = make_unique<SVGDrawPath>(d);
    path->setStroke(getAttribute(DOT_ATTR_KEY_COLOR));
    path->setFill("none");
    if (strokeWidth != 1.0) {
        path->setStrokeWidth(getAttribute(DOT_ATTR_KEY_PEN_WIDTH));
    }
    svgDraws.emplace_back(std::move(path));
    for (auto& arrow : svgDrawArrows) {
        svgDraws.emplace_back(std::move(arrow));
    }
    if (const auto label = getAttribute(DOT_ATTR_KEY_LABEL); !label.empty()) {
        double totalLength = 0.0;
        vector<double> lengths(splines.size());
        for (size_t i = 0; i < splines.size(); ++i) {
            lengths[i] = GeometryUtils::computeBezierLength(splines[i][0], splines[i][1], splines[i][2], splines[i][3]);
            totalLength += lengths[i];
        }
        const double halfLength = totalLength / 2.0;
        double sumLength = 0.0;
        double splineX = 0.0, splineY = 0.0;
        double dx = 0.0, dy = 0.0;
        for (size_t i = 0; i < splines.size(); ++i) {
            const double nextSum = sumLength + lengths[i];
            if (nextSum > halfLength) {
                const double targetLength = halfLength - sumLength;
                auto [x1, y1] = splines[i][0];
                double totalSegmentLength = 0.0;
                for (int j = 1; j < NUM_SPLINE_LENGTH_APPROXIMATION_SEGMENTS; ++j) {
                    const double t = j * SPLINE_LENGTH_APPROXIMATION_STEP;
                    const auto [x2, y2] = GeometryUtils::computeBezierAt(splines[i], t);
                    totalSegmentLength += GeometryUtils::distance(x1, y1, x2, y2);
                    if (j + 1 == NUM_SPLINE_LENGTH_APPROXIMATION_SEGMENTS || totalSegmentLength > targetLength - GeometryUtils::EPSILON) {
                        const double tMid = t - SPLINE_LENGTH_APPROXIMATION_STEP * 0.5;
                        auto point = GeometryUtils::computeBezierAt(splines[i], tMid);
                        splineX = point.first, splineY = point.second;
                        point = GeometryUtils::computeBezierDerivative(splines[i], tMid);
                        dx = point.first, dy = point.second;
                        break;
                    }
                    x1 = x2;
                    y1 = y2;
                }
                break;
            }
            sumLength = nextSum;
        }
        const auto [cx, cy] = computeTextCenter(splineX, splineY, dx, dy);
        appendSVGDrawsLabelWithCenter(svgDraws, cx, cy);
    }
    return svgDraws;
}

double SVGEdge::computeArrowTipMargin(const string_view& shape) const {
    if (shape == ARROW_SHAPE_NORMAL) {
        return computeArrowTipMarginNormal();
    }
    return 0.0;
}

double SVGEdge::computeArrowTipMarginNormal() const {
    const double angle = atan(ARROW_HALF_HEIGHT / ARROW_WIDTH);
    const double strokeWidth = penWidth();
    const double margin = strokeWidth / 2.0 / sin(angle);
    return margin;
}

pair<double, double> SVGEdge::addArrow(const string_view& shape, vector<unique_ptr<SVGDraw>>& svgDraws, const pair<double, double>& connectionPoint, const double angle) const {
    const double arrowTipMargin = computeArrowTipMargin(shape);
    const pair arrowTip = {connectionPoint.first + arrowTipMargin * cos(angle), connectionPoint.second + arrowTipMargin * sin(angle)};
    if (shape == ARROW_SHAPE_NORMAL) {
        return addArrowNormal(svgDraws, arrowTip, angle);
    }
    return {connectionPoint.first - 0.2 * cos(angle), connectionPoint.second - 0.2 * sin(angle)};
}

pair<double, double> SVGEdge::addArrowNormal(vector<unique_ptr<SVGDraw>>& svgDraws, const pair<double, double>& connectionPoint, const double angle) const {
    const double x0 = connectionPoint.first;
    const double y0 = connectionPoint.second;
    const double sideLen = GeometryUtils::distance(ARROW_WIDTH, ARROW_HALF_HEIGHT);
    const double halfAngle = atan(ARROW_HALF_HEIGHT / ARROW_WIDTH);
    const double x1 = x0 + sideLen * cos(angle - halfAngle);
    const double y1 = y0 + sideLen * sin(angle - halfAngle);
    const double x2 = x0 + sideLen * cos(angle + halfAngle);
    const double y2 = y0 + sideLen * sin(angle + halfAngle);
    auto polygon = make_unique<SVGDrawPolygon>(vector<pair<double, double>>{{x0, y0}, {x1, y1}, {x2, y2}, {x0, y0}});
    polygon->setStroke(getAttribute(DOT_ATTR_KEY_COLOR));
    polygon->setFill(getAttribute(DOT_ATTR_KEY_COLOR));
    if (const double strokeWidth = penWidth(); strokeWidth != 1.0) {
        polygon->setStrokeWidth(getAttribute(DOT_ATTR_KEY_PEN_WIDTH));
    }
    svgDraws.emplace_back(std::move(polygon));
    return {x0 + ARROW_WIDTH * cos(angle), y0 + ARROW_WIDTH * sin(angle)};
}
