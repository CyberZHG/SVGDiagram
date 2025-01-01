#ifndef SVGDIAGRAM_SVG_NODES_H
#define SVGDIAGRAM_SVG_NODES_H

#include <string>
#include <unordered_map>

#include "svg_draw.h"

namespace svg_diagram {

    constexpr std::string_view DOT_ATTR_KEY_LABEL = "label";
    constexpr std::string_view DOT_ATTR_KEY_SHAPE = "shape";
    constexpr std::string_view DOT_ATTR_KEY_MARGIN = "margin";
    constexpr std::string_view DOT_ATTR_KEY_WIDTH = "width";
    constexpr std::string_view DOT_ATTR_KEY_HEIGHT = "height";
    constexpr std::string_view DOT_ATTR_KEY_FONT_NAME = "fontname";
    constexpr std::string_view DOT_ATTR_KEY_FONT_SIZE = "fontsize";
    constexpr std::string_view DOT_ATTR_KEY_FIXED_SIZE = "fixedsize";

    class SVGNode final {
    public:
        SVGNode() = default;
        SVGNode(double cx, double cy);
        ~SVGNode() = default;

        static constexpr std::string_view NODE_SHAPE_CIRCLE = "circle";

        void setAttribute(const std::string_view& key, const std::string& value);
        void setAttributeIfNotExist(const std::string_view& key, const std::string& value);
        [[nodiscard]] const std::string& getAttribute(const std::string_view& key) const;

        void setPrecomputedTextSize(double width, double height);
        void setLabel(const std::string& label);
        void setMargin(const std::string& value);
        void setMargin(double margin);
        void setMargin(double marginX, double marginY);
        void setMarginInPixels(double margin);
        void setMarginInPixels(double marginX, double marginY);

        void enableDebug();

        void adjustNodeSize();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDraws();
        // std::vector<double, double> getConnectionPoint(double angle);

    private:
        double _cx = 0.0;
        double _cy = 0.0;
        double _precomputedTextWidth = 0.0;
        double _precomputedTextHeight = 0.0;
        std::unordered_map<std::string_view, std::string> _attributes;

        bool _showTextBoxes = false;

        [[nodiscard]] std::pair<double, double> computeTextSize();
        [[nodiscard]] std::pair<double, double> computeMarginInPixels();
        [[nodiscard]] bool isFixedSize() const;

        void appendSVGDrawsLabel(std::vector<std::unique_ptr<SVGDraw>>& svgDraws);

        void adjustNodeSizeCircle();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsCircle();
    };

}

#endif //SVGDIAGRAM_SVG_NODES_H