#ifndef SVGDIAGRAM_ATTRIBUTE_UTILS_H
#define SVGDIAGRAM_ATTRIBUTE_UTILS_H

#include <string>
#include <vector>
#include <memory>

namespace svg_diagram {

    struct AttributeParsedStyle {
        bool solid = false;
        bool dashed = false;
        bool dotted = false;
        bool filled = false;
    };

    struct AttributeParsedColor {
        std::string color;
        double opacity = 1.0;
        double weight = -1.0;
    };

    struct RecordLabel {
        std::string label;
        std::vector<std::unique_ptr<RecordLabel>> children;

        [[nodiscard]] std::string toString(bool top = true) const;
    };

    class AttributeUtils {
    public:
        static double pointToInch(double points);
        static double inchToPoint(double inches);
        static double centimeterToInch(double centimeters);

        static bool isPartOfDouble(char ch);
        static std::string removeSpaces(const std::string& str);
        static std::vector<std::string> splitString(const std::string& str, char delimiter);
        static std::vector<std::string> splitString(const std::string& str, const std::string& delimiter);

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
        static AttributeParsedStyle parseStyle(const std::string& value);
        static std::vector<AttributeParsedColor> parseColorList(const std::string& value);

        using DCommands = std::vector<std::pair<char, std::vector<double>>>;
        static DCommands parseDCommands(const std::string& d);
        static std::vector<std::pair<double, double>> computeDPathPoints(const DCommands& commands);

        static std::unique_ptr<RecordLabel> parseRecordLabel(const std::string& label);

    private:
        static std::unique_ptr<RecordLabel> parseRecordLabel(const std::string& label, size_t& index);
    };

}

#endif //SVGDIAGRAM_ATTRIBUTE_UTILS_H