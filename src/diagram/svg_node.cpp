#include "svg_nodes.h"

#include <format>
#include <cmath>
#include <functional>
#include <numbers>

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

void SVGNode::setSides(const int sides) {
    setAttribute(ATTR_KEY_SIDES, sides);
}

void SVGNode::setSkew(const double skew) {
    setAttribute(ATTR_KEY_SKEW, skew);
}

void SVGNode::setDistortion(const double distortion) {
    setAttribute(ATTR_KEY_DISTORTION, distortion);
}

void SVGNode::setOrientation(const double orientation) {
    setAttribute(ATTR_KEY_ORIENTATION, orientation);
}

void SVGNode::setPeripheries(const int peripheries) {
    setAttribute(ATTR_KEY_PERIPHERIES, peripheries);
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
        setPeripheries(2);
        adjustNodeSizeCircle();
    } else if (shape == SHAPE_NONE || shape == SHAPE_RECT) {
        adjustNodeSizeRect();
    } else if (shape == SHAPE_ELLIPSE) {
        adjustNodeSizeEllipse();
    } else if (shape == SHAPE_DOUBLE_ELLIPSE) {
        setPeripheries(2);
        adjustNodeSizeEllipse();
    } else if (shape == SHAPE_POLYGON) {
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_TRIANGLE) {
        setSides(3);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_PENTAGON) {
        setSides(5);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_HEXAGON) {
        setSides(6);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_SEPTAGON) {
        setSides(7);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_OCTAGON) {
        setSides(8);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_DOUBLE_OCTAGON) {
        setSides(8);
        setPeripheries(2);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_TRIPLE_OCTAGON) {
        setSides(8);
        setPeripheries(3);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_TRAPEZIUM) {
        setSides(4);
        setDistortion(-0.4);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_PARALLELOGRAM) {
        setSides(4);
        setSkew(0.6);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_HOUSE) {
        setSides(5);
        setDistortion(-0.64);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_DIAMOND) {
        setSides(4);
        setOrientation(45);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_INV_TRIANGLE) {
        setSides(3);
        setOrientation(180);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_INV_TRAPEZIUM) {
        setSides(4);
        setDistortion(-0.4);
        setOrientation(180);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_INV_HOUSE) {
        setSides(5);
        setDistortion(-0.64);
        setOrientation(180);
        adjustNodeSizePolygon();
    } else if (shape == SHAPE_RECORD) {
        adjustNodeSizeRecord();
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
    if (shape == SHAPE_CIRCLE || shape == SHAPE_DOUBLE_CIRCLE) {
        return produceSVGDrawsCircle();
    }
    if (shape == SHAPE_RECT) {
        return produceSVGDrawsRect();
    }
    if (shape == SHAPE_ELLIPSE || shape == SHAPE_DOUBLE_ELLIPSE) {
        return produceSVGDrawsEllipse();
    }
    if (shape == SHAPE_POLYGON || shape == SHAPE_TRIANGLE || shape == SHAPE_PENTAGON ||
        shape == SHAPE_HEXAGON || shape == SHAPE_SEPTAGON || shape == SHAPE_OCTAGON ||
        shape == SHAPE_DOUBLE_OCTAGON || shape == SHAPE_TRIPLE_OCTAGON ||
        shape == SHAPE_TRAPEZIUM || shape == SHAPE_PARALLELOGRAM || shape == SHAPE_HOUSE ||
        shape == SHAPE_DIAMOND || shape == SHAPE_INV_TRIANGLE || shape == SHAPE_INV_TRAPEZIUM ||
        shape == SHAPE_INV_HOUSE) {
        return produceSVGDrawsPolygon();
    }
    if (shape == SHAPE_RECORD) {
        return produceSVGDrawsRecord();
    }
    return produceSVGDrawsNone();
}

pair<double, double> SVGNode::computeConnectionPoint(const double angle) {
    setAttributeIfNotExist(ATTR_KEY_SHAPE, string(SHAPE_DEFAULT));
    const auto shape = getAttribute(ATTR_KEY_SHAPE);
    if (shape == SHAPE_CIRCLE || shape == SHAPE_DOUBLE_CIRCLE) {
        return computeConnectionPointCircle(angle);
    }
    if (shape == SHAPE_RECT || shape == SHAPE_NONE) {
        return computeConnectionPointRect(angle);
    }
    if (shape == SHAPE_RECORD) {
        return computeConnectionPointRecord(angle);
    }
    if (shape == SHAPE_ELLIPSE || shape == SHAPE_DOUBLE_ELLIPSE) {
        return computeConnectionPointEllipse(angle);
    }
    if (shape == SHAPE_POLYGON || shape == SHAPE_TRIANGLE || shape == SHAPE_PENTAGON ||
        shape == SHAPE_HEXAGON || shape == SHAPE_SEPTAGON || shape == SHAPE_OCTAGON ||
        shape == SHAPE_DOUBLE_OCTAGON || shape == SHAPE_TRIPLE_OCTAGON ||
        shape == SHAPE_TRAPEZIUM || shape == SHAPE_PARALLELOGRAM || shape == SHAPE_HOUSE ||
        shape == SHAPE_DIAMOND || shape == SHAPE_INV_TRIANGLE || shape == SHAPE_INV_TRAPEZIUM ||
        shape == SHAPE_INV_HOUSE) {
        return computeConnectionPointPolygon(angle);
    }
    return computeConnectionPointEllipse(angle);
}

pair<double, double> SVGNode::computeFieldConnectionPoint(const string& fieldId, const double angle) {
    const auto shape = getAttribute(ATTR_KEY_SHAPE);
    if (shape != SHAPE_RECORD || !_recordPositions.contains(fieldId)) {
        return computeConnectionPoint(angle);
    }
    const auto& [cx, cy, width, height] = _recordPositions.at(fieldId);
    return computeConnectionPointRect(cx, cy, width, height, angle);
}

double SVGNode::computeAngle(const double x, const double y) const {
    return atan2(y - _cy, x - _cx);
}

double SVGNode::computeAngle(const pair<double, double>& p) const {
    return computeAngle(p.first, p.second);
}

double SVGNode::computeFieldAngle(const string &fieldId, const pair<double, double>& p) const {
    const auto shape = getAttribute(ATTR_KEY_SHAPE);
    if (shape != SHAPE_RECORD || !_recordPositions.contains(fieldId)) {
        return computeAngle(p);
    }
    const auto& [cx, cy, width, height] = _recordPositions.at(fieldId);
    return atan2(p.second - cy, p.first - cx);
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
    appendSVGDrawsLabelWithLocation(svgDraws, _cx, _cy);
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
    setAttributeIfNotExist(ATTR_KEY_PERIPHERIES, string(ATTR_DEF_PERIPHERIES));
    const int peripheries = stoi(getAttribute(ATTR_KEY_PERIPHERIES));
    vector<unique_ptr<SVGDraw>> svgDraws;
    const double radius = max(width(), height()) / 2.0;
    auto circle = make_unique<SVGDrawCircle>(_cx, _cy, radius);
    setStrokeStyles(circle.get());
    setFillStyles(circle.get(), svgDraws);
    svgDraws.emplace_back(std::move(circle));
    for (int p = 1; p < peripheries; ++p) {
        auto circleOuter = make_unique<SVGDrawCircle>(_cx, _cy, radius + DOUBLE_BORDER_MARGIN * p);
        setStrokeStyles(circleOuter.get());
        circleOuter->setFill("none");
        svgDraws.emplace_back(std::move(circleOuter));
    }
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

pair<double, double> SVGNode::computeConnectionPointCircle(const double angle) const {
    const auto& peripheriesStr = getAttribute(ATTR_KEY_PERIPHERIES);
    const int peripheries = peripheriesStr.empty() ? 1 : stoi(peripheriesStr);
    const double radius = (width() + penWidth()) / 2.0 + DOUBLE_BORDER_MARGIN * (peripheries - 1);
    return {_cx + radius * cos(angle), _cy + radius * sin(angle)};
}

void SVGNode::adjustNodeSizeRect() {
    updateNodeSize(computeTextSizeWithMargin());
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsRect() {
    setAttributeIfNotExist(ATTR_KEY_PERIPHERIES, string(ATTR_DEF_PERIPHERIES));
    const int peripheries = stoi(getAttribute(ATTR_KEY_PERIPHERIES));
    vector<unique_ptr<SVGDraw>> svgDraws;
    auto rect = make_unique<SVGDrawRect>(_cx, _cy, width(), height());
    setStrokeStyles(rect.get());
    setFillStyles(rect.get(), svgDraws);
    svgDraws.emplace_back(std::move(rect));
    for (int p = 1; p < peripheries; ++p) {
        auto rectOuter = make_unique<SVGDrawRect>(_cx, _cy, width() + DOUBLE_BORDER_MARGIN * 2 * p, height() + DOUBLE_BORDER_MARGIN * 2 * p);
        setStrokeStyles(rectOuter.get());
        rectOuter->setFill("none");
        svgDraws.emplace_back(std::move(rectOuter));
    }
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

pair<double, double> SVGNode::computeConnectionPointRect(const double angle) const {
    const auto& peripheriesStr = getAttribute(ATTR_KEY_PERIPHERIES);
    const int peripheries = peripheriesStr.empty() ? 1 : stoi(peripheriesStr);
    const double offset = DOUBLE_BORDER_MARGIN * (peripheries - 1);
    return computeConnectionPointRect(_cx, _cy, width() + offset * 2, height() + offset * 2, angle);
}

pair<double, double> SVGNode::computeConnectionPointRect(const double cx, const double cy, const double width, const double height, const double angle) const {
    const double strokeWidth = penWidth();
    const double totalWidth = width + strokeWidth;
    const double totalHeight = height + strokeWidth;
    double x1 = -totalWidth / 2, y1 = -totalHeight / 2;
    double x2 = totalWidth / 2, y2 = totalHeight / 2;
    const auto vertices = vector<pair<double, double>>{{x1, y1}, {x2, y1}, {x2, y2}, {x1, y2}};
    for (const auto& [x, y] : vertices) {
        if (GeometryUtils::isSameAngle(angle, x, y)) {
            return {cx + x, cy + y};
        }
    }
    double x = 0.0, y = 0.0;
    for (int i = 0; i < static_cast<int>(vertices.size()); ++i) {
        x1 = vertices[i].first;
        y1 = vertices[i].second;
        x2 = vertices[(i + 1) % vertices.size()].first;
        y2 = vertices[(i + 1) % vertices.size()].second;
        if (const auto intersect = GeometryUtils::intersect(angle, x1, y1, x2, y2); intersect != nullopt) {
            x = _cx + intersect.value().first;
            y = _cy + intersect.value().second;
        }
    }
    return {x, y};
}

void SVGNode::adjustNodeSizeEllipse() {
    const auto [textWidth, textHeight] = computeTextSize();
    const auto [marginX, marginY] = computeMargin();
    updateNodeSize((textWidth + marginX * 2) * sqrt(2.0), (textHeight + marginY * 2) * sqrt(2.0));
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsEllipse() {
    setAttributeIfNotExist(ATTR_KEY_PERIPHERIES, string(ATTR_DEF_PERIPHERIES));
    const int peripheries = stoi(getAttribute(ATTR_KEY_PERIPHERIES));
    vector<unique_ptr<SVGDraw>> svgDraws;
    auto ellipse = make_unique<SVGDrawEllipse>(_cx, _cy, width(), height());
    setStrokeStyles(ellipse.get());
    setFillStyles(ellipse.get(), svgDraws);
    svgDraws.emplace_back(std::move(ellipse));
    for (int p = 1; p < peripheries; ++p) {
        auto ellipseOuter = make_unique<SVGDrawEllipse>(_cx, _cy, width() + DOUBLE_BORDER_MARGIN * 2 * p, height() + DOUBLE_BORDER_MARGIN * 2 * p);
        setStrokeStyles(ellipseOuter.get());
        ellipseOuter->setFill("none");
        svgDraws.emplace_back(std::move(ellipseOuter));
    }
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

pair<double, double> SVGNode::computeConnectionPointEllipse(const double angle) const {
    const auto& peripheriesStr = getAttribute(ATTR_KEY_PERIPHERIES);
    const int peripheries = peripheriesStr.empty() ? 1 : stoi(peripheriesStr);
    const double strokeWidth = penWidth();
    const double totalWidth = width() + strokeWidth + DOUBLE_BORDER_MARGIN * 2 * (peripheries - 1);
    const double totalHeight = height() + strokeWidth + DOUBLE_BORDER_MARGIN * 2 * (peripheries - 1);
    const double rx = totalWidth / 2, ry = totalHeight / 2;
    const double base = sqrt(ry * ry * cos(angle) * cos(angle) + rx * rx * sin(angle) * sin(angle));
    const double x = rx * ry * cos(angle) / base;
    const double y = rx * ry * sin(angle) / base;
    return {_cx + x, _cy + y};
}

void SVGNode::adjustNodeSizePolygon() {
    setAttributeIfNotExist(ATTR_KEY_SIDES, string(ATTR_DEF_SIDES));
    setAttributeIfNotExist(ATTR_KEY_SKEW, string(ATTR_DEF_SKEW));
    setAttributeIfNotExist(ATTR_KEY_DISTORTION, string(ATTR_DEF_DISTORTION));
    setAttributeIfNotExist(ATTR_KEY_ORIENTATION, string(ATTR_DEF_ORIENTATION));
    const auto [textWidth, textHeight] = computeTextSize();
    const auto [marginX, marginY] = computeMargin();
    const double boxWidth = textWidth + marginX * 2;
    const double boxHeight = textHeight + marginY * 2;
    updateNodeSize(boxWidth * numbers::sqrt2, boxHeight * numbers::sqrt2);
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsPolygon() {
    setAttributeIfNotExist(ATTR_KEY_PERIPHERIES, string(ATTR_DEF_PERIPHERIES));
    const int peripheries = stoi(getAttribute(ATTR_KEY_PERIPHERIES));
    vector<unique_ptr<SVGDraw>> svgDraws;
    if (enabledDebug()) {
        auto ellipse = make_unique<SVGDrawEllipse>(_cx, _cy, width(), height());
        ellipse->setStroke("green");
        ellipse->setFill("none");
        svgDraws.emplace_back(std::move(ellipse));
    }
    const auto vertices = computePolygonVertices();
    auto polygon = make_unique<SVGDrawPolygon>(vertices);
    setStrokeStyles(polygon.get());
    setFillStyles(polygon.get(), svgDraws);
    svgDraws.emplace_back(std::move(polygon));
    for (int p = 1; p < peripheries; ++p) {
        const auto verticesOuter = computePolygonVertices(DOUBLE_BORDER_MARGIN * p);
        auto polygonOuter = make_unique<SVGDrawPolygon>(verticesOuter);
        setStrokeStyles(polygonOuter.get());
        polygonOuter->setFill("none");
        svgDraws.emplace_back(std::move(polygonOuter));
    }
    appendSVGDrawsLabel(svgDraws);
    return svgDraws;
}

vector<pair<double, double>> SVGNode::computePolygonVertices() const {
    auto sides = stoi(getAttribute(ATTR_KEY_SIDES));
    const auto skew = stod(getAttribute(ATTR_KEY_SKEW));
    const auto distortion = stod(getAttribute(ATTR_KEY_DISTORTION));
    const auto orientation = stod(getAttribute(ATTR_KEY_ORIENTATION));
    if (sides < 3) {
        sides = 3;
    }
    const double rx = width() / 2.0;
    const double ry = height() / 2.0;
    const double sectorAngle = 2.0 * numbers::pi / sides;
    const double skewDist = hypot(fabs(distortion) + fabs(skew), 1.0);
    const double gDistortion = -distortion * numbers::sqrt2 / cos(sectorAngle / 2.0) / 2.0;
    const double gSkew = -skew / 2.0;
    const double orientationRad = -orientation * numbers::pi / 180.0;
    const double cosOri = cos(orientationRad);
    const double sinOri = sin(orientationRad);

    vector<pair<double, double>> vertices;
    vertices.reserve(sides);
    const double angleOffset = (sides % 2 == 0) ? sectorAngle / 2.0 : 0.0;
    for (int i = 0; i < sides; ++i) {
        const double baseAngle = -numbers::pi / 2.0 + angleOffset + sectorAngle * i;
        const double unitX = cos(baseAngle);
        const double unitY = sin(baseAngle);
        const double x = unitX * (skewDist + unitY * gDistortion) + unitY * gSkew;
        const double y = unitY;

        const double rotX = x * cosOri - y * sinOri;
        const double rotY = x * sinOri + y * cosOri;
        vertices.emplace_back(_cx + rotX * rx, _cy + rotY * ry);
    }
    return vertices;
}

vector<pair<double, double>> SVGNode::computePolygonVertices(const double scaleOffset) const {
    auto sides = stoi(getAttribute(ATTR_KEY_SIDES));
    const auto skew = stod(getAttribute(ATTR_KEY_SKEW));
    const auto distortion = stod(getAttribute(ATTR_KEY_DISTORTION));
    const auto orientation = stod(getAttribute(ATTR_KEY_ORIENTATION));
    if (sides < 3) {
        sides = 3;
    }
    const double rx = width() / 2.0 + scaleOffset;
    const double ry = height() / 2.0 + scaleOffset;
    const double sectorAngle = 2.0 * numbers::pi / sides;
    const double skewDist = hypot(fabs(distortion) + fabs(skew), 1.0);
    const double gDistortion = -distortion * numbers::sqrt2 / cos(sectorAngle / 2.0) / 2.0;
    const double gSkew = -skew / 2.0;
    const double orientationRad = -orientation * numbers::pi / 180.0;
    const double cosOri = cos(orientationRad);
    const double sinOri = sin(orientationRad);

    vector<pair<double, double>> vertices;
    vertices.reserve(sides);
    const double angleOffset = (sides % 2 == 0) ? sectorAngle / 2.0 : 0.0;
    for (int i = 0; i < sides; ++i) {
        const double baseAngle = -numbers::pi / 2.0 + angleOffset + sectorAngle * i;
        const double unitX = cos(baseAngle);
        const double unitY = sin(baseAngle);
        const double x = unitX * (skewDist + unitY * gDistortion) + unitY * gSkew;
        const double y = unitY;

        const double rotX = x * cosOri - y * sinOri;
        const double rotY = x * sinOri + y * cosOri;
        vertices.emplace_back(_cx + rotX * rx, _cy + rotY * ry);
    }
    return vertices;
}

pair<double, double> SVGNode::computeConnectionPointPolygon(const double angle) const {
    const auto& peripheriesStr = getAttribute(ATTR_KEY_PERIPHERIES);
    const int peripheries = peripheriesStr.empty() ? 1 : stoi(peripheriesStr);
    const auto vertices = computePolygonVertices(DOUBLE_BORDER_MARGIN * (peripheries - 1));
    const int n = static_cast<int>(vertices.size());
    for (int i = 0; i < n; ++i) {
        const auto& [x1, y1] = vertices[i];
        const auto& [x2, y2] = vertices[(i + 1) % n];

        const double rx1 = x1 - _cx;
        const double ry1 = y1 - _cy;
        const double rx2 = x2 - _cx;
        const double ry2 = y2 - _cy;

        if (const auto intersect = GeometryUtils::intersect(angle, rx1, ry1, rx2, ry2); intersect != nullopt) {
            return {_cx + intersect.value().first, _cy + intersect.value().second};
        }
    }
    return computeConnectionPointEllipse(angle);
}

void SVGNode::adjustNodeSizeRecord() {
    _recordSizes.clear();
    function<pair<double, double>(const unique_ptr<RecordLabel>&, bool)> adjustRecordSize;
    adjustRecordSize = [&](const unique_ptr<RecordLabel>& recordLabel, const bool horizontal) -> pair<double, double> {
        if (recordLabel->children.empty()) {
            const SVGTextSize textSize;
            const double fontSize = stod(getAttribute(ATTR_KEY_FONT_SIZE));
            const string fontFamily = getAttribute(ATTR_KEY_FONT_NAME);
            auto [width, height] = textSize.computeTextSize(recordLabel->label, fontSize, fontFamily);
            if (width == 0.0) {
                width = fontSize * SVGTextSize::DEFAULT_APPROXIMATION_WIDTH_SCALE;
            }
            if (height == 0.0) {
                height = fontSize * SVGTextSize::DEFAULT_APPROXIMATION_HEIGHT_SCALE;
            }
            const auto [marginX, marginY] = computeMargin();
            width += marginX * 2;
            height += marginY * 2;
            _recordSizes[reinterpret_cast<uintptr_t>(recordLabel.get())] = {width, height};
            return {width, height};
        }
        double width = 0.0, height = 0.0;
        for (const auto& child : recordLabel->children) {
            const auto [subWidth, subHeight] = adjustRecordSize(child, !horizontal);
            if (horizontal) {
                width += subWidth;
                height = max(height, subHeight);
            } else {
                height += subHeight;
                width = max(width, subWidth);
            }
        }
        _recordSizes[reinterpret_cast<uintptr_t>(recordLabel.get())] = {width, height};
        return {width, height};
    };
    _recordLabel = AttributeUtils::parseRecordLabel(getAttribute(ATTR_KEY_LABEL));
    const auto [width, height] = adjustRecordSize(_recordLabel, true);
    updateNodeSize(width, height);
}

std::vector<std::unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsRecord() {
    const auto nodeWidth = width();
    const auto nodeHeight = height();
    vector<unique_ptr<SVGDraw>> svgDraws;
    auto rect = make_unique<SVGDrawRect>(_cx, _cy, nodeWidth, nodeHeight);
    setStrokeStyles(rect.get());
    setFillStyles(rect.get(), svgDraws);
    svgDraws.emplace_back(std::move(rect));
    const auto [marginX, marginY] = margin();

    _recordPositions.clear();
    function<void(const unique_ptr<RecordLabel>&, bool, double, double, double, double)> drawRecordLabel;
    drawRecordLabel = [&](const unique_ptr<RecordLabel>& recordLabel, const bool horizontal, double x1, double y1, const double x2, const double y2) {
        const double cx = (x1 + x2) / 2;
        const double cy = (y1 + y2) / 2;
        if (!recordLabel->fieldId.empty()) {
            _recordPositions[recordLabel->fieldId] = {cx, cy, x2 - x1, y2 - y1};
        }
        if (recordLabel->children.empty()) {
            appendSVGDrawsLabelWithLocation(svgDraws, recordLabel->label, cx, cy, x2 - x1 - marginX * 2, y2 - y1 - marginY * 2);
            return;
        }
        bool first = true;
        for (const auto& child : recordLabel->children) {
            if (first) {
                first = false;
            } else {
                if (horizontal) {
                    auto line = make_unique<SVGDrawLine>(x1, y1, x1, y2);
                    setStrokeStyles(line.get());
                    svgDraws.emplace_back(std::move(line));
                } else {
                    auto line = make_unique<SVGDrawLine>(x1, y1, x2, y1);
                    setStrokeStyles(line.get());
                    svgDraws.emplace_back(std::move(line));
                }
            }
            const auto [subWidth, subHeight] = _recordSizes[reinterpret_cast<uintptr_t>(child.get())];
            if (horizontal) {
                drawRecordLabel(child, false, x1, y1, x1 + subWidth, y2);
                x1 += subWidth;
            } else {
                drawRecordLabel(child, true, x1, y1, x2, y1 + subHeight);
                y1 += subHeight;
            }
        }
    };
    const double x1 = _cx - nodeWidth / 2, y1 = _cy - nodeHeight / 2;
    const double x2 = _cx + nodeWidth / 2, y2 = _cy + nodeHeight / 2;
    drawRecordLabel(_recordLabel, true, x1, y1, x2, y2);

    return svgDraws;
}

std::pair<double, double> SVGNode::computeConnectionPointRecord(const double angle) const {
    return computeConnectionPointRect(angle);
}
