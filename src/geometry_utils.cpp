#include "geometry_utils.h"

#include <cmath>
using namespace svg_diagram;

double GeometryUtils::distance(double x, double y) {
    return sqrt(x * x + y * y);
}

double GeometryUtils::distance(const double x1, const double y1, const double x2, const double y2) {
    return distance(x2 - x1, y2 - y1);
}
