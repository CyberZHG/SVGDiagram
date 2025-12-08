#ifndef SVGDIAGRAM_GEOMETRY_UTILS_H
#define SVGDIAGRAM_GEOMETRY_UTILS_H

#include <optional>
#include <utility>

namespace svg_diagram {

    class GeometryUtils {
    public:
        static constexpr double EPSILON = 1e-9;

        using Point2D = std::pair<double, double>;

        static double distance(double x, double y);
        static double distance(const Point2D &p);
        static double distance(double x1, double y1, double x2, double y2);
        static Point2D normalize(double x, double y);

        static double cross(double x1, double y1, double x2, double y2);
        static bool isSameAngle(double angle, double x1, double y1);
        static std::optional<Point2D> intersect(double angle, double x1, double y1, double x2, double y2);

        static Point2D computeBezierDerivative(const Point2D& p0, const Point2D& p1, const Point2D& p2, const Point2D& p3, double t);
        static double computeBezierLength(const Point2D& p0, const Point2D& p1, const Point2D& p2, const Point2D& p3);
    };

}

#endif //SVGDIAGRAM_GEOMETRY_UTILS_H