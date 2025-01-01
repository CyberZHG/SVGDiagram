#ifndef SVGDIAGRAM_GEOMETRY_UTILS_H
#define SVGDIAGRAM_GEOMETRY_UTILS_H
#include <optional>

namespace svg_diagram {

    class GeometryUtils {
    public:
        static constexpr double EPSILON = 1e-9;

        static double distance(double x, double y);
        static double distance(double x1, double y1, double x2, double y2);

        static double cross(double x1, double y1, double x2, double y2);
        static bool isSameAngle(double angle, double x1, double y1);
        static std::optional<std::pair<double, double>> intersect(double angle, double x1, double y1, double x2, double y2);
    };

}

#endif //SVGDIAGRAM_GEOMETRY_UTILS_H