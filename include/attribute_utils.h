#ifndef SVGDIAGRAM_ATTRIBUTE_UTILS_H
#define SVGDIAGRAM_ATTRIBUTE_UTILS_H

#include <string>
#include <vector>

namespace svg_diagram {

    constexpr int POINTS_PER_INCH = 72;
    constexpr double CENTIMETERS_PER_INCH = 2.54;

    class AttributeUtils {
    public:
        static double pointToInch(double points);
        static double inchToPoint(double inches);
        static double centimeterToInch(double centimeters);

        static bool isPartOfDouble(char ch);

        /** Parse a string to inch value.
         *
         * The default unit is inch. The available units are `in` (inch), `pt` (point), and `cm` (centimeter).
         *
         * @param s
         * @return Inch value.
         */
        static double parseLengthToInch(const std::string& s);

        static std::pair<double, double> parseMarginToInches(const std::string& margin);
        static std::pair<double, double> parseMargin(const std::string& margin);

        static bool parseBool(const std::string& value);

        using DCommands = std::vector<std::pair<char, std::vector<double>>>;
        static DCommands parseDCommands(const std::string& d);
        static std::vector<std::pair<double, double>> computeDPathPoints(const DCommands& commands);
    };

}

#endif //SVGDIAGRAM_ATTRIBUTE_UTILS_H