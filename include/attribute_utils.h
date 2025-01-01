#ifndef SVGDIAGRAM_ATTRIBUTE_UTILS_H
#define SVGDIAGRAM_ATTRIBUTE_UTILS_H

#include <string>

namespace svg_diagram {

    class AttributeUtils {
    public:
        static std::pair<double, double> parseMargin(const std::string& margin);
    };

}

#endif //SVGDIAGRAM_ATTRIBUTE_UTILS_H