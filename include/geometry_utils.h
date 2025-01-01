#ifndef SVGDIAGRAM_GEOMETRY_UTILS_H
#define SVGDIAGRAM_GEOMETRY_UTILS_H

namespace svg_diagram {

    class GeometryUtils {
    public:
        static double distance(double x, double y);
        static double distance(double x1, double y1, double x2, double y2);
    };

}

#endif //SVGDIAGRAM_GEOMETRY_UTILS_H