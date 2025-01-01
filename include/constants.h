#ifndef SVGDIAGRAM_CONSTANTS_H
#define SVGDIAGRAM_CONSTANTS_H

#include <string_view>

namespace svg_diagram {
    constexpr int POINTS_PER_INCH = 72;
    constexpr double CENTIMETERS_PER_INCH = 2.54;

    constexpr std::string_view ATTR_KEY_ID = "id";
    constexpr std::string_view ATTR_KEY_LABEL = "label";
    constexpr std::string_view ATTR_KEY_SHAPE = "shape";
    constexpr std::string_view ATTR_KEY_SPLINES = "splines";
    constexpr std::string_view ATTR_KEY_MARGIN = "margin";
    constexpr std::string_view ATTR_KEY_WIDTH = "width";
    constexpr std::string_view ATTR_KEY_HEIGHT = "height";
    constexpr std::string_view ATTR_KEY_FONT_NAME = "fontname";
    constexpr std::string_view ATTR_KEY_FONT_SIZE = "fontsize";
    constexpr std::string_view ATTR_KEY_FIXED_SIZE = "fixedsize";
    constexpr std::string_view ATTR_KEY_ARROW_HEAD = "arrowhead";
    constexpr std::string_view ATTR_KEY_ARROW_TAIL = "arrowtail";
    constexpr std::string_view ATTR_KEY_COLOR = "color";
    constexpr std::string_view ATTR_KEY_FILL_COLOR = "fillcolor";
    constexpr std::string_view ATTR_KEY_FONT_COLOR = "fontcolor";
    constexpr std::string_view ATTR_KEY_PEN_WIDTH = "penwidth";
    constexpr std::string_view ATTR_KEY_STYLE = "style";

    constexpr std::string_view ATTR_DEF_COLOR = "black";
    constexpr std::string_view ATTR_DEF_COLOR_GRAPH = "none";
    constexpr std::string_view ATTR_DEF_FILL_COLOR = "none";
    constexpr std::string_view ATTR_DEF_FONT_COLOR = "black";
    constexpr std::string_view ATTR_DEF_FONT_NAME = "Times,serif";
    constexpr std::string_view ATTR_DEF_FONT_SIZE = "14";
    constexpr std::string_view ATTR_DEF_PEN_WIDTH = "1";
    constexpr std::string_view ATTR_DEF_MARGIN_NODE = "0.1111111111111111,0.05555555555555555";
    constexpr std::string_view ATTR_DEF_MARGIN_EDGE = "0,0";
    constexpr std::string_view ATTR_DEF_MARGIN_GRAPH = "0.1111111111111111,0.1111111111111111";
    constexpr std::string_view ATTR_DEF_STYLE = "solid,filled";

    constexpr std::string_view ATTR_STYLE_SOLID = "solid";
    constexpr std::string_view ATTR_STYLE_DASHED = "dashed";
    constexpr std::string_view ATTR_STYLE_DOTTED = "dotted";
    constexpr std::string_view ATTR_STYLE_FILLED = "filled";

    constexpr std::string_view SVG_ATTR_KEY_ID = "id";
    constexpr std::string_view SVG_ATTR_KEY_STYLE = "style";
    constexpr std::string_view SVG_ATTR_KEY_FILL = "fill";
    constexpr std::string_view SVG_ATTR_KEY_FILL_OPACITY = "fill-opacity";
    constexpr std::string_view SVG_ATTR_KEY_STROKE = "stroke";
    constexpr std::string_view SVG_ATTR_KEY_FONT_FAMILY = "font-family";
    constexpr std::string_view SVG_ATTR_KEY_FONT_SIZE = "font-size";
    constexpr std::string_view SVG_ATTR_KEY_MARKER_START = "marker-start";
    constexpr std::string_view SVG_ATTR_KEY_MARKER_END = "marker-end";
    constexpr std::string_view SVG_ATTR_KEY_STROKE_WIDTH = "stroke-width";
    constexpr std::string_view SVG_ATTR_KEY_STROKE_DASHARRAY = "stroke-dasharray";
    constexpr std::string_view SVG_ATTR_KEY_STROKE_OPACITY = "stroke-opacity";
    constexpr std::string_view SVG_ATTR_KEY_GRADIENT_TRANSFORM = "gradientTransform";
    constexpr std::string_view SVG_ATTR_KEY_OFFSET = "offset";
    constexpr std::string_view SVG_ATTR_KEY_STOP_COLOR = "stop-color";
    constexpr std::string_view SVG_ATTR_KEY_STOP_OPACITY = "stop-opacity";

    constexpr std::string_view SVG_ATTR_COLOR_NONE = "none";
}

#endif //SVGDIAGRAM_CONSTANTS_H