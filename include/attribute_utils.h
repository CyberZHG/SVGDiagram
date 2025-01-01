#ifndef SVGDIAGRAM_ATTRIBUTE_UTILS_H
#define SVGDIAGRAM_ATTRIBUTE_UTILS_H

#include <string>

namespace svg_diagram {

    constexpr int SVG_DEFAULT_DPI = 96;

    class AttributeUtils {
    public:
        static std::pair<double, double> parseMargin(const std::string& margin);
        static std::pair<double, double> parseMarginToPixels(const std::string& margin);

        static bool parseBool(const std::string& value);
    };

}

#endif //SVGDIAGRAM_ATTRIBUTE_UTILS_H