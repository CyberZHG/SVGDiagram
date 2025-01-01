#include "geometry_utils.h"

#include <cmath>
using namespace svg_diagram;

double GeometryUtils::distance(const double x1, const double y1, const double x2, const double y2) {
    const auto dx = x2 - x1;
    const auto dy = y2 - y1;
    return sqrt(dx * dx + dy * dy);
}
