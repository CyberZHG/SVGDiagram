#include "svg_nodes.h"

#include <format>
#include <cmath>
#include <numbers>

#include "attribute_utils.h"
#include "svg_text_size.h"
#include "geometry_utils.h"
using namespace std;
using namespace svg_diagram;

SVGEdge::SVGEdge(const string& idFrom, const string& idTo) {
    _nodeFrom = idFrom;
    _nodeTo = idTo;
}

void SVGEdge::setAttributeIfNotExist(const std::string_view &key, const std::string &value) {
    if (attributes().contains(key)) {
        return;
    }
    if (parent() != nullptr) {
        if (const auto ret = parent()->defaultEdgeAttribute(key); ret.has_value()) {
            return;
        }
    }
    setAttribute(key, value);
}

const string& SVGEdge::getAttribute(const string_view& key) const {
    static const string EMPTY_STRING;
    if (const auto it = attributes().find(key); it != attributes().end()) {
        return it->second;
    }
    if (parent() != nullptr) {
        if (const auto ret = parent()->defaultEdgeAttribute(key); ret.has_value()) {
            return ret.value();
        }
    }
    return EMPTY_STRING;
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
    setAttribute(ATTR_KEY_SPLINES, value);
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
    setAttributeIfNotExist(ATTR_KEY_SPLINES, string(SPLINES_DEFAULT));
    setAttributeIfNotExist(ATTR_KEY_COLOR, string(ATTR_DEF_COLOR));
    setAttributeIfNotExist(ATTR_KEY_ARROW_HEAD, string(ARROW_NONE));
    setAttributeIfNotExist(ATTR_KEY_ARROW_TAIL, string(ARROW_NONE));
    setAttributeIfNotExist(ATTR_KEY_MARGIN, string(ATTR_DEF_MARGIN_EDGE));
    setAttributeIfNotExist(ATTR_KEY_FONT_NAME, string(ATTR_DEF_FONT_NAME));
    setAttributeIfNotExist(ATTR_KEY_FONT_SIZE, string(ATTR_DEF_FONT_SIZE));
    const auto splines = getAttribute(ATTR_KEY_SPLINES);
    if (splines == SPLINES_LINE) {
        return produceSVGDrawsLine(nodes);
    }
    return produceSVGDrawsSpline(nodes);
}

void SVGEdge::setArrowHead() {
    setArrowHead(ARROW_DEFAULT);
}

void SVGEdge::setArrowHead(const string_view& shape) {
    setArrowHead(string(shape));
}

void SVGEdge::setArrowHead(const string& shape) {
    setAttribute(ATTR_KEY_ARROW_HEAD, shape);
}

void SVGEdge::setArrowTail() {
    setArrowTail(ARROW_DEFAULT);
}

void SVGEdge::setArrowTail(const string_view& shape) {
    setArrowTail(string(shape));
}

void SVGEdge::setArrowTail(const string& shape) {
    setAttribute(ATTR_KEY_ARROW_TAIL, shape);
}

void SVGEdge::setSelfLoopAttributes(double dir, const double height, double angle) {
    dir = -dir / 180 * numbers::pi;
    angle = angle / 180 * numbers::pi;
    setSplines(SPLINES_SELF_LOOP);
    setAttribute(ATTR_KEY_SELF_LOOP_DIR, dir);
    setAttribute(ATTR_KEY_SELF_LOOP_ANGLE, angle);
    setAttribute(ATTR_KEY_SELF_LOOP_HEIGHT, height);
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
    const auto arrowHeadShape = getAttribute(ATTR_KEY_ARROW_HEAD);
    const auto arrowTailShape = getAttribute(ATTR_KEY_ARROW_TAIL);
    vector<unique_ptr<SVGDraw>> svgDraws;
    vector<unique_ptr<SVGDraw>> svgDrawArrows;
    vector<pair<double, double>> drawPoints, distancePoints;
    if (_connectionPoints.empty()) {
        const double angleFrom = nodeFrom->computeAngle(nodeTo->center());
        const double angleTo = nodeTo->computeAngle(nodeFrom->center());
        distancePoints.emplace_back(nodeFrom->computeConnectionPoint(angleFrom));
        distancePoints.emplace_back(nodeTo->computeConnectionPoint(angleTo));
        drawPoints.emplace_back(addArrow(arrowTailShape, svgDrawArrows, distancePoints[0], angleFrom));
        drawPoints.emplace_back(addArrow(arrowHeadShape, svgDrawArrows, distancePoints[1], angleTo));
    } else {
        const double angleFrom = nodeFrom->computeAngle(_connectionPoints[0]);
        distancePoints.emplace_back(nodeFrom->computeConnectionPoint(angleFrom));
        drawPoints.emplace_back(addArrow(arrowTailShape, svgDrawArrows, distancePoints[0], angleFrom));
        for (const auto& [x, y] : _connectionPoints) {
            distancePoints.emplace_back(x, y);
            drawPoints.emplace_back(x, y);
        }
        const size_t n = _connectionPoints.size();
        const double angleTo = nodeTo->computeAngle(_connectionPoints[n - 1]);
        distancePoints.emplace_back(nodeTo->computeConnectionPoint(angleTo));
        drawPoints.emplace_back(addArrow(arrowHeadShape, svgDrawArrows, distancePoints.back(), angleTo));
    }
    for (size_t i = 0; i + 1 < drawPoints.size(); ++i) {
        const auto& [x1, y1] = drawPoints[i];
        const auto& [x2, y2] = drawPoints[i + 1];
        svgDraws.emplace_back(make_unique<SVGDrawLine>(x1, y1, x2, y2));
    }
    setStrokeStyles(svgDraws[0].get());
    for (size_t i = 1; i < svgDraws.size(); ++i) {
        svgDraws[i]->copyAttributes(svgDraws[0].get());
    }
    for (const auto& line : svgDraws) {
        const auto& draw = dynamic_cast<SVGDrawLine*>(line.get());
        setStrokeStyles(draw);
    }
    for (auto& arrow : svgDrawArrows) {
        svgDraws.emplace_back(std::move(arrow));
    }
    if (const auto label = getAttribute(ATTR_KEY_LABEL); !label.empty()) {
        double totalLength = 0.0;
        for (size_t i = 0; i + 1 < distancePoints.size(); ++i) {
            const auto& [x1, y1] = distancePoints[i];
            const auto& [x2, y2] = distancePoints[i + 1];
            totalLength += GeometryUtils::distance(x1, y1, x2, y2);
        }
        const double halfLength = totalLength / 2.0;
        double sumLength = 0.0;
        size_t index = 0;
        double lineX = 0.0, lineY = 0.0;
        for (size_t i = 0; i + 1 < distancePoints.size(); ++i) {
            const auto& [x1, y1] = distancePoints[i];
            const auto& [x2, y2] = distancePoints[i + 1];
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
        const double dx = distancePoints[index + 1].first - distancePoints[index].first;
        const double dy = distancePoints[index + 1].second - distancePoints[index].second;
        const auto [cx, cy] = computeTextCenter(lineX, lineY, dx, dy);
        appendSVGDrawsLabelWithCenter(svgDraws, cx, cy);
    }
    return svgDraws;
}

vector<unique_ptr<SVGDraw>> SVGEdge::produceSVGDrawsSpline(const NodesMapping& nodes) {
    static constexpr double NUM_SPLINE_LENGTH_APPROXIMATION_SEGMENTS = 100;
    const auto splinesType = getAttribute(ATTR_KEY_SPLINES);
    constexpr double SPLINE_LENGTH_APPROXIMATION_STEP = 1.0 / NUM_SPLINE_LENGTH_APPROXIMATION_SEGMENTS;
    if (_connectionPoints.empty() && splinesType != SPLINES_SELF_LOOP) {
        return produceSVGDrawsLine(nodes);
    }
    const auto& nodeFrom = nodes.at(_nodeFrom);
    const auto& nodeTo = nodes.at(_nodeTo);
    const auto arrowHeadShape = getAttribute(ATTR_KEY_ARROW_HEAD);
    const auto arrowTailShape = getAttribute(ATTR_KEY_ARROW_TAIL);
    vector<unique_ptr<SVGDraw>> svgDraws;
    vector<unique_ptr<SVGDraw>> svgDrawArrows;
    vector<vector<pair<double, double>>> splines;
    if (splinesType == SPLINES_SELF_LOOP) {
        const double selfCycleDir = stod(getAttribute(ATTR_KEY_SELF_LOOP_DIR));
        const double selfCycleAngle = stod(getAttribute(ATTR_KEY_SELF_LOOP_ANGLE));
        const double selfCycleHeight = stod(getAttribute(ATTR_KEY_SELF_LOOP_HEIGHT));
        const double nodeAngleFrom = selfCycleDir - selfCycleAngle / 2.0;
        const double nodeAngleTo = selfCycleDir + selfCycleAngle / 2.0;
        auto [rx, ry] = nodeFrom->computeConnectionPoint(selfCycleDir);
        rx += selfCycleHeight * cos(selfCycleDir);
        ry += selfCycleHeight * sin(selfCycleDir);
        const auto startPoint = nodeFrom->computeConnectionPoint(nodeAngleFrom);
        const auto stopPoint = nodeTo->computeConnectionPoint(nodeAngleTo);
        const double nx = cos(selfCycleDir), ny = sin(selfCycleDir);
        const double tx = -ny, ty = nx;
        const double radius = 0.5625 * selfCycleHeight;
        const double shift = 0.375 * selfCycleHeight;
        const double c1x = startPoint.first + nx * radius - tx * shift;
        const double c1y = startPoint.second + ny * radius - ty * shift;
        const double c2x = rx - tx * shift;
        const double c2y = ry - ty * shift;
        const double c3x = rx + tx * shift;
        const double c3y = ry + ty * shift;
        const double c4x = stopPoint.first + nx * radius + tx * shift;
        const double c4y = stopPoint.second + ny * radius + ty * shift;
        splines.emplace_back(vector{startPoint, {c1x, c1y}, {c2x, c2y}, {rx, ry}});
        splines.emplace_back(vector{{rx, ry}, {c3x, c3y}, {c4x, c4y}, stopPoint});
    } else {
        vector<pair<double, double>> points;
        const double nodeAngleFrom = nodeFrom->computeAngle(_connectionPoints[0]);
        const auto startPoint = nodeFrom->computeConnectionPoint(nodeAngleFrom);
        points.emplace_back(startPoint);
        points.emplace_back(startPoint);
        for (const auto& [x, y] : _connectionPoints) {
            points.emplace_back(x, y);
        }
        const double nodeAngleTo = nodeTo->computeAngle(_connectionPoints[_connectionPoints.size() - 1]);
        const auto stopPoint = nodeTo->computeConnectionPoint(nodeAngleTo);
        points.emplace_back(stopPoint);
        points.emplace_back(stopPoint);
        for (int i = 1; i + 2 < static_cast<int>(points.size()); ++i) {
            const auto [x0, y0] = points[i - 1];
            const auto [x1, y1] = points[i];
            auto [x2, y2] = points[i + 1];
            const auto [x3, y3] = points[i + 2];
            const double c1x = x1 + (x2 - x0) / 6.0;
            const double c1y = y1 + (y2 - y0) / 6.0;
            const double c2x = x2 - (x3 - x1) / 6.0;
            const double c2y = y2 - (y3 - y1) / 6.0;
            splines.emplace_back(vector{points[i], {c1x, c1y}, {c2x, c2y}, points[i + 1]});
        }
    }
    auto d = format("M {} {}", splines[0][0].first, splines[0][0].second);
    for (size_t i = 0; i < splines.size(); ++i) {
        const auto& spline = splines[i];
        auto [c1x, c1y] = spline[1];
        auto [c2x, c2y] = spline[2];
        auto [x2, y2] = spline[3];
        if (i == 0 && arrowTailShape != ARROW_NONE) {
            const auto [t, endPoint] = GeometryUtils::findPointOnBezierWithL2Distance(
                spline[0], spline[1], spline[2], spline[3], spline[0],
                ARROW_WIDTH + computeArrowTipMargin(arrowTailShape));
            const auto& [nx, ny] = endPoint;
            const double arrowAngleFrom = atan2(ny - spline[0].second, nx - spline[0].first);
            addArrow(arrowTailShape, svgDrawArrows, spline[0], arrowAngleFrom);
            const auto [spline1, spline2] = GeometryUtils::splitBezierAt(spline, t);
            d = format("M {} {}", nx, ny);
            c1x = spline2[1].first, c1y = spline2[1].second;
            c2x = spline2[2].first, c2y = spline2[2].second;
            x2 = spline2[3].first, y2 = spline2[3].second;
        } else if (i + 1 == splines.size() && arrowHeadShape != ARROW_NONE) {
            const auto [t, endPoint] = GeometryUtils::findPointOnBezierWithL2Distance(
                spline[3], spline[2], spline[1], spline[0], spline[3],
                ARROW_WIDTH + computeArrowTipMargin(arrowHeadShape));
            const auto& [nx, ny] = endPoint;
            const double arrowAngleTo = atan2(ny - spline[3].second, nx - spline[3].first);
            addArrow(arrowHeadShape, svgDrawArrows, spline[3], arrowAngleTo);
            const auto [spline1, spline2] = GeometryUtils::splitBezierAt(spline, 1 - t);
            c1x = spline1[1].first, c1y = spline1[1].second;
            c2x = spline1[2].first, c2y = spline1[2].second;
            x2 = spline1[3].first, y2 = spline1[3].second;
        }
        d += format(" C {} {} {} {} {} {}", c1x, c1y, c2x, c2y, x2, y2);
    }
    if (enabledDebug()) {
        for (const auto& spline : splines) {
            auto line1 = make_unique<SVGDrawLine>(spline[0].first, spline[0].second, spline[1].first, spline[1].second);
            auto line2 = make_unique<SVGDrawLine>(spline[2].first, spline[2].second, spline[3].first, spline[3].second);
            line1->setStroke("blue");
            line2->setStroke("blue");
            svgDraws.emplace_back(std::move(line1));
            svgDraws.emplace_back(std::move(line2));
        }
    }
    auto path = make_unique<SVGDrawPath>(d);
    setStrokeStyles(path.get());
    path->setFill("none");
    svgDraws.emplace_back(std::move(path));
    for (auto& arrow : svgDrawArrows) {
        svgDraws.emplace_back(std::move(arrow));
    }
    if (const auto label = getAttribute(ATTR_KEY_LABEL); !label.empty()) {
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



void SVGEdge::setArrowStyles(SVGDraw *draw, const bool fill) const {
    if (const auto colorList = AttributeUtils::parseColorList(color()); !colorList.empty()) {
        const auto& color = colorList[0];
        draw->setStroke(color.color);
        if (color.opacity < 1.0) {
            draw->setStrokeOpacity(color.opacity);
        }
        if (fill) {
            draw->setFill(color.color);
            if (color.opacity < 1.0) {
                draw->setFillOpacity(color.opacity);
            }
        } else {
            draw->setFill("none");
        }
    }
    if (const auto strokeWidth = penWidth(); strokeWidth != 1.0) {
        draw->setStrokeWidth(strokeWidth);
    }
}

double SVGEdge::computeArrowTipMargin(const string_view& shape) const {
    if (shape == ARROW_NORMAL || shape == ARROW_EMPTY) {
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
    if (shape == ARROW_NORMAL) {
        return addArrowNormal(svgDraws, arrowTip, angle, true);
    }
    if (shape == ARROW_EMPTY) {
        return addArrowNormal(svgDraws, arrowTip, angle, false);
    }
    return {connectionPoint.first - 0.2 * cos(angle), connectionPoint.second - 0.2 * sin(angle)};
}

pair<double, double> SVGEdge::addArrowNormal(vector<unique_ptr<SVGDraw>>& svgDraws, const pair<double, double>& connectionPoint, const double angle, const bool fill) const {
    const double x0 = connectionPoint.first;
    const double y0 = connectionPoint.second;
    const double sideLen = GeometryUtils::distance(ARROW_WIDTH, ARROW_HALF_HEIGHT);
    const double halfAngle = atan(ARROW_HALF_HEIGHT / ARROW_WIDTH);
    const double x1 = x0 + sideLen * cos(angle - halfAngle);
    const double y1 = y0 + sideLen * sin(angle - halfAngle);
    const double x2 = x0 + sideLen * cos(angle + halfAngle);
    const double y2 = y0 + sideLen * sin(angle + halfAngle);
    auto polygon = make_unique<SVGDrawPolygon>(vector<pair<double, double>>{{x0, y0}, {x1, y1}, {x2, y2}, {x0, y0}});
    setArrowStyles(polygon.get(), fill);
    svgDraws.emplace_back(std::move(polygon));
    return {x0 + ARROW_WIDTH * cos(angle), y0 + ARROW_WIDTH * sin(angle)};
}
