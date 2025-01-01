#ifndef SVGDIAGRAM_SVG_NODES_H
#define SVGDIAGRAM_SVG_NODES_H

#include <string>
#include <unordered_map>

#include "svg_draw.h"

namespace svg_diagram {

    constexpr std::string_view DOT_ATTR_KEY_LABEL = "label";
    constexpr std::string_view DOT_ATTR_KEY_SHAPE = "shape";
    constexpr std::string_view DOT_ATTR_KEY_SPLINES = "splines";
    constexpr std::string_view DOT_ATTR_KEY_MARGIN = "margin";
    constexpr std::string_view DOT_ATTR_KEY_WIDTH = "width";
    constexpr std::string_view DOT_ATTR_KEY_HEIGHT = "height";
    constexpr std::string_view DOT_ATTR_KEY_FONT_NAME = "fontname";
    constexpr std::string_view DOT_ATTR_KEY_FONT_SIZE = "fontsize";
    constexpr std::string_view DOT_ATTR_KEY_FIXED_SIZE = "fixedsize";

    class SVGItem {
    public:
        SVGItem() = default;
        virtual ~SVGItem() = default;

        void enableDebug();
        [[nodiscard]] bool enabledDebug() const;

        void setAttribute(const std::string_view& key, const std::string& value);
        void setAttributeIfNotExist(const std::string_view& key, const std::string& value);
        [[nodiscard]] const std::string& getAttribute(const std::string_view& key) const;

        void setPrecomputedTextSize(double width, double height);
        [[nodiscard]] std::pair<double, double> precomputedTextSize() const;
        void setLabel(const std::string& label);
        void setMargin(const std::string& value);
        void setMargin(double margin);
        void setMargin(double marginX, double marginY);
        void setMarginInPixels(double margin);
        void setMarginInPixels(double marginX, double marginY);

    private:
        bool _enabledDebug = false;
        double _precomputedTextWidth = 0.0;
        double _precomputedTextHeight = 0.0;
        std::unordered_map<std::string_view, std::string> _attributes;
    };

    class SVGNode final : public SVGItem {
    public:
        using SVGItem::SVGItem;
        SVGNode(double cx, double cy);

        static constexpr std::string_view NODE_SHAPE_CIRCLE = "circle";
        static constexpr std::string_view NODE_SHAPE_DEFAULT = NODE_SHAPE_CIRCLE;

        void setShape(const std::string& shape);
        void setShape(const std::string_view& shape);
        [[nodiscard]] std::pair<double, double> center() const;

        void adjustNodeSize();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDraws();

        std::pair<double, double> computeConnectionPoint(double angle);
        std::pair<double, double> computeConnectionPoint(double x1, double y1, double x2, double y2);
        std::pair<double, double> computeConnectionPoint(double x, double y);
        std::pair<double, double> computeConnectionPoint(const std::pair<double, double>& p);

    private:
        double _cx = 0.0;
        double _cy = 0.0;

        [[nodiscard]] std::pair<double, double> computeTextSize();
        [[nodiscard]] std::pair<double, double> computeMarginInPixels();
        [[nodiscard]] bool isFixedSize() const;

        void appendSVGDrawsLabel(std::vector<std::unique_ptr<SVGDraw>>& svgDraws);

        void adjustNodeSizeCircle();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsCircle();
        [[nodiscard]] std::pair<double, double> computeConnectionPointCircle(double angle) const;
    };

    class SVGEdge final : public SVGItem {
    public:
        using SVGItem::SVGItem;
        SVGEdge(const std::string& idFrom, const std::string& idTo);

        static constexpr std::string_view EDGE_SPLINES_LINE = "line";
        static constexpr std::string_view EDGE_SPLINES_DEFAULT = EDGE_SPLINES_LINE;

        using NodesMapping = std::unordered_map<std::string, std::unique_ptr<SVGNode>>;

        [[nodiscard]] const std::string& nodeFrom() const;
        [[nodiscard]] const std::string& nodeTo() const;

        void setSplines(const std::string& value);
        void setSplines(const std::string_view& value);

        void addConnectionPoint(const std::pair<double, double>& point);
        void addConnectionPoint(double x, double y);

        std::vector<std::unique_ptr<SVGDraw>> produceSVGDraws(const NodesMapping& nodes);

    private:
        std::string _nodeFrom, _nodeTo;
        std::vector<std::pair<double, double>> _connectionPoints;

        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsLine(const NodesMapping& nodes);
    };

}

#endif //SVGDIAGRAM_SVG_NODES_H