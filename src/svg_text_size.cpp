#include "svg_text_size.h"
using namespace std;
using namespace svg_diagram;

double SVGTextSize::heightScale() const {
    return _heightScale;
}

void SVGTextSize::setHeightScale(const double scale) {
    _heightScale = scale;
}

double SVGTextSize::widthScale() const {
    return _widthScale;
}

void SVGTextSize::setWidthScale(const double scale) {
    _widthScale = scale;
}

double SVGTextSize::lineSpacingScale() const {
    return _lineSpacingScale;
}

void SVGTextSize::setLineSpacingScale(const double scale) {
    _lineSpacingScale = scale;
}

pair<double, double> SVGTextSize::computeTextSize(const string& text, const double fontSize, const string& fontFamily) const {
    return computeApproximateTextSize(text, fontSize);
}

pair<double, double> SVGTextSize::computeApproximateTextSize(const string& text, const double fontSize) const {
    if (text.empty()) {
        return {0.0, 0.0};
    }
    int numLines = 1, maxCharsInLine = 0;
    int numCharsInLine = 0;
    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == '\n' || text[i] == '\r') {
            maxCharsInLine = max(maxCharsInLine, numCharsInLine);
            if (i + 1 < text.length() && text[i + 1] == '\n') {
                ++i;
            }
            ++numLines;
        } else {
            ++numCharsInLine;
        }
    }
    maxCharsInLine = max(maxCharsInLine, numCharsInLine);
    const double approximateHeight = fontSize * (numLines * _heightScale + (numLines - 1) * _lineSpacingScale);
    const double approximateWidth = fontSize * (maxCharsInLine * _widthScale);
    return {approximateWidth, approximateHeight};
}
