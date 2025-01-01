#include "geometry_utils.h"

#include <cmath>
using namespace std;
using namespace svg_diagram;

double GeometryUtils::distance(const double x, const double y) {
    return sqrt(x * x + y * y);
}

double GeometryUtils::distance(const double x1, const double y1, const double x2, const double y2) {
    return distance(x2 - x1, y2 - y1);
}

double GeometryUtils::cross(const double x1, const double y1, const double x2, const double y2) {
    return x1 * y2 - y1 * x2;
}

bool GeometryUtils::isSameAngle(const double angle, const double x1, const double y1) {
    const double x2 = cos(angle);
    const double y2 = sin(angle);
    return fabs(cross(x1, y1, x2, y2)) < EPSILON;
}

optional<pair<double, double>> GeometryUtils::intersect(const double angle, const double x1, const double y1, const double x2, const double y2) {
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
