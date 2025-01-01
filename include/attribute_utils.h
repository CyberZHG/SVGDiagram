#ifndef SVGDIAGRAM_ATTRIBUTE_UTILS_H
#define SVGDIAGRAM_ATTRIBUTE_UTILS_H

#include <string>
#include <vector>

namespace svg_diagram {

    constexpr int SVG_DEFAULT_DPI = 96;

    class AttributeUtils {
    public:
        static std::pair<double, double> parseMargin(const std::string& margin);
        static std::pair<double, double> parseMarginToPixels(const std::string& margin);

        static bool parseBool(const std::string& value);

        using DCommands = std::vector<std::pair<char, std::vector<double>>>;
        static DCommands parseDCommands(const std::string& d);
        static std::vector<std::pair<double, double>> computeDPathPoints(const DCommands& commands);
    };

}

#endif //SVGDIAGRAM_ATTRIBUTE_UTILS_H