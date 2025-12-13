#include "geometry_utils.h"

#include <vector>
#include <cmath>
using namespace std;
using namespace svg_diagram;

double GeometryUtils::distance(const double x, const double y) {
    return sqrt(x * x + y * y);
}

double GeometryUtils::distance(const Point2D& p) {
    const auto& [x, y] = p;
    return sqrt(x * x + y * y);
}

double GeometryUtils::distance(const double x1, const double y1, const double x2, const double y2) {
    return distance(x2 - x1, y2 - y1);
}

GeometryUtils::Point2D GeometryUtils::normalize(const double x, const double y) {
    const double length = distance(x, y);
    return {x / length, y / length};
}

double GeometryUtils::cross(const double x1, const double y1, const double x2, const double y2) {
    return x1 * y2 - y1 * x2;
}

bool GeometryUtils::isSameAngle(const double angle, const double x1, const double y1) {
    const auto otherAngle = atan2(y1, x1);
    return fabs(angle - otherAngle) < EPSILON;
}

optional<GeometryUtils::Point2D> GeometryUtils::intersect(const double angle, const double x1, const double y1, const double x2, const double y2) {
    if (fabs(x1 - x2) < EPSILON && fabs(y1 - y2) < EPSILON) {
        if (isSameAngle(angle, x1, y1)) {
            return {{x1, y1}};
        }
        return nullopt;
    }
    const double dx = cos(angle), dy = sin(angle);
    const double sx = x2 - x1, sy = y2 - y1;
    const double c1 = cross(dx, dy, sx, sy);
    if (fabs(c1) < EPSILON) {
        return nullopt;
    }
    const double c2 = cross(x1, y1, x2, y2);
    const double r = c2 / c1;
    const double rx = dx * r, ry = dy * r;
    double t = 0.0;
    if (x1 != x2) {
        t = (rx - x1) / (x2 - x1);
    } else {
        t = (ry - y1) / (y2 - y1);
    }
    if (r > -EPSILON && t > -EPSILON && t < 1.0 + EPSILON) {
        return {{rx, ry}};
    }
    return nullopt;
}

/** Compute the derivative with the given t.
 *
 * B'(t) = 3(1-t)^2 (P_1 - P_0) + 6(1-t)t (P_2 - P_1) + 3t^2 (P_3 - P_2)
 */
GeometryUtils::Point2D GeometryUtils::computeBezierDerivative(const Point2D& p0, const Point2D& p1, const Point2D& p2, const Point2D& p3, const double t) {
    const auto x0 = p0.first, y0 = p0.second;
    const auto x1 = p1.first, y1 = p1.second;
    const auto x2 = p2.first, y2 = p2.second;
    const auto x3 = p3.first, y3 = p3.second;

    const double a = 3.0 * (1.0 - t) * (1.0 - t);
    const double b = 6.0 * (1.0 - t) * t;
    const double c = 3.0 * t * t;

    const double dx = a * (x1 - x0) + b * (x2 - x1) + c * (x3 - x2);
    const double dy = a * (y1 - y0) + b * (y2 - y1) + c * (y3 - y2);
    return {dx, dy};
}

GeometryUtils::Point2D GeometryUtils::computeBezierDerivative(const vector<Point2D>& points, const double t) {
    return computeBezierDerivative(points[0], points[1], points[2], points[3], t);
}

/** Compute the length of a bezier spline using 16-point Gauss-Legendre.
 *
 * B(t) = (1-t)^3 P_0 + 3(1-t)^2t P_1 + 3(1-t)t^2 P_2 + t^3 P_3
 */
double GeometryUtils::computeBezierLength(const Point2D& p0, const Point2D& p1, const Point2D& p2, const Point2D& p3) {
    // See: https://github.com/ampl/gsl/blob/d00bd4fcac4fbdac1b211df97950b0df53993738/integration/glfixed.c#L68-L69
    static const vector x16 = {
        -0.9894009349916499325961542,
        -0.9445750230732325760779884,
        -0.8656312023878317438804679,
        -0.7554044083550030338951012,
        -0.6178762444026437484466718,
        -0.4580167776572273863424194,
        -0.2816035507792589132304605,
        -0.0950125098376374401853193,
        0.0950125098376374401853193,
        0.2816035507792589132304605,
        0.4580167776572273863424194,
        0.6178762444026437484466718,
        0.7554044083550030338951012,
        0.8656312023878317438804679,
        0.9445750230732325760779884,
        0.9894009349916499325961542,
    };
    static const vector w16 = {
        0.0271524594117540948517806,
        0.0622535239386478928628438,
        0.0951585116824927848099251,
        0.1246289712555338720524763,
        0.1495959888165767320815017,
        0.1691565193950025381893121,
        0.1826034150449235888667637,
        0.1894506104550684962853967,
        0.1894506104550684962853967,
        0.1826034150449235888667637,
        0.1691565193950025381893121,
        0.1495959888165767320815017,
        0.1246289712555338720524763,
        0.0951585116824927848099251,
        0.0622535239386478928628438,
        0.0271524594117540948517806,
    };
    double total = 0.0;
    for (size_t i = 0; i < x16.size(); ++i) {
        const double t = 0.5 * (x16[i] + 1.0);
        const auto [dx, dy] = computeBezierDerivative(p0, p1, p2, p3, t);
        total += w16[i] * distance(dx, dy);
    }
    return total / 2.0;
}

/** Compute the point location on a bezier spline.
 *
 * B(t) = (1-t)^3 P_0 + 3(1-t)^2t P_1 + 3(1-t)t^2 P_2 + t^3 P_3
 */
GeometryUtils::Point2D GeometryUtils::computeBezierAt(const Point2D& p0, const Point2D& p1, const Point2D& p2, const Point2D& p3, const double t) {
    const auto x0 = p0.first, y0 = p0.second;
    const auto x1 = p1.first, y1 = p1.second;
    const auto x2 = p2.first, y2 = p2.second;
    const auto x3 = p3.first, y3 = p3.second;

    const double a = (1 - t) * (1 - t) * (1 - t);
    const double b = 3 * (1 - t) * (1 - t) * t;
    const double c = 3 * (1 - t) * t * t;
    const double d = t * t * t;

    const double x = a * x0 + b * x1 + c * x2 + d * x3;
    const double y = a * y0 + b * y1 + c * y2 + d * y3;
    return {x, y};
}

GeometryUtils::Point2D GeometryUtils::computeBezierAt(const vector<Point2D>& points, const double t) {
    return computeBezierAt(points[0], points[1], points[2], points[3], t);
}
