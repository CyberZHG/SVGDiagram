#include "svg_text_size.h"
#include "attribute_utils.h"

#include <format>

#ifdef SVG_DIAGRAM_ENABLE_PANGO_CAIRO
#include <cairo.h>
#include <cairo-svg.h>
#include <pango/pangocairo.h>
#endif
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

#ifdef SVG_DIAGRAM_ENABLE_PANGO_CAIRO
pair<double, double> SVGTextSize::computeTextSize(const string& text, const double fontSize, const string& fontName) const {
    return computePangoCairoTextSize(text, fontSize, fontName);
}
#else
pair<double, double> SVGTextSize::computeTextSize(const string& text, const double fontSize, const string&) const {
    return computeApproximateTextSize(text, fontSize);
}
#endif

pair<double, double> SVGTextSize::computeApproximateTextSize(const string& text, const double fontSize) const {
    if (text.empty()) {
        return {0.0, 0.0};
    }
    const size_t n = text.length();
    int numLines = 1, maxCharsInLine = 0;
    int numCharsInLine = 0;
    for (size_t i = 0; i < n; ++i) {
        if (text[i] == '\n' || text[i] == '\r') {
            maxCharsInLine = max(maxCharsInLine, numCharsInLine);
            if (i + 1 < n && text[i + 1] == '\n') {
                ++i;
            }
            ++numLines;
            numCharsInLine = 0;
        } else if (i + 1 < n && text[i] == '\\' && (text[i + 1] == 'l' || text[i + 1] == 'r')) {
            maxCharsInLine = max(maxCharsInLine, numCharsInLine);
            if (i + 2 < n) {
                ++numLines;
            }
            ++i;
            numCharsInLine = 0;
        } else {
            ++numCharsInLine;
        }
    }
    maxCharsInLine = max(maxCharsInLine, numCharsInLine);
    const double approximateHeight = fontSize * (numLines * _heightScale + (numLines - 1) * _lineSpacingScale);
    const double approximateWidth = fontSize * (maxCharsInLine * _widthScale);
    return {approximateWidth, approximateHeight};
}

#ifdef SVG_DIAGRAM_ENABLE_PANGO_CAIRO
cairo_status_t dummy_cairo_write_func(void*, const unsigned char*, unsigned int) {
    return CAIRO_STATUS_SUCCESS;
}

pair<double, double> SVGTextSize::computePangoCairoTextSize(const string& text, const double fontSize, const string& fontName) {
    constexpr double PANGO_SCALE_DOUBLE = PANGO_SCALE;
    if (text.empty()) {
        return {0.0, 0.0};
    }
    const string font = format("{} {}", fontName, fontSize);
    const auto surface = cairo_svg_surface_create_for_stream(&dummy_cairo_write_func, nullptr, 400, 300);
    const auto cr = cairo_create(surface);
    PangoLayout* layout = pango_cairo_create_layout(cr);
    pango_layout_set_text(layout, text.c_str(), -1);
    PangoFontDescription* font_desc = pango_font_description_from_string(font.c_str());
    pango_layout_set_font_description(layout, font_desc);
    pango_font_description_free(font_desc);
    PangoRectangle ink_rect, logical_rect;
    pango_layout_get_extents(layout, &ink_rect, &logical_rect);
    g_object_unref(layout);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    return {ink_rect.width / PANGO_SCALE_DOUBLE, ink_rect.height / PANGO_SCALE_DOUBLE};
}
#endif
