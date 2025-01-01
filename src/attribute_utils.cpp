#include "attribute_utils.h"
using namespace std;
using namespace svg_diagram;

pair<double, double> AttributeUtils::parseMargin(const string& margin) {
    if (const auto pos = margin.find(','); pos != string::npos) {
        const string left  = margin.substr(0, pos);
        const string right = margin.substr(pos + 1);
        return {stod(left), stod(right)};
    }
    double m = stod(margin);
    return {m, m};
}

pair<double, double> AttributeUtils::parseMarginToPixels(const string& margin) {
    const auto [width, height] = parseMargin(margin);
    return {width * SVG_DEFAULT_DPI, height * SVG_DEFAULT_DPI};
}

bool AttributeUtils::parseBool(const string& value) {
    if (value.empty()) {
        return false;
    }
    string lower = value;
    ranges::transform(lower, lower.begin(), [](const unsigned char c) {
        return tolower(c);
    });
    return lower == "true" || lower == "1" || lower == "on" || lower == "yes";
}
