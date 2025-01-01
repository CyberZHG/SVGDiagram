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
    constexpr std::string_view DOT_ATTR_KEY_ARROW_HEAD = "arrowhead";
    constexpr std::string_view DOT_ATTR_KEY_ARROW_TAIL = "arrowtail";
    constexpr std::string_view DOT_ATTR_KEY_COLOR = "color";
    constexpr std::string_view DOT_ATTR_KEY_FILL_COLOR = "fillcolor";
    constexpr std::string_view DOT_ATTR_KEY_FONT_COLOR = "fontcolor";
    constexpr std::string_view DOT_ATTR_KEY_PEN_WIDTH = "penwidth";

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
        void setColor(const std::string& color);
        void setFillColor(const std::string& color);
        void setFontColor(const std::string& color);
        void setPenWidth(double width);
        [[nodiscard]] double penWidthInPixels() const;

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

        static constexpr std::string_view NODE_SHAPE_NONE = "none";
        static constexpr std::string_view NODE_SHAPE_CIRCLE = "circle";
        static constexpr std::string_view NODE_SHAPE_RECT = "rect";
        static constexpr std::string_view NODE_SHAPE_DEFAULT = NODE_SHAPE_CIRCLE;

        void setShape(const std::string& shape);
        void setShape(const std::string_view& shape);

        void setCenter(double cx, double cy);
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
        void updateNodeSize(double width, double height);

        void appendSVGDrawsLabel(std::vector<std::unique_ptr<SVGDraw>>& svgDraws);

        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsNone();

        void adjustNodeSizeCircle();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsCircle();
        [[nodiscard]] std::pair<double, double> computeConnectionPointCircle(double angle) const;

        void adjustNodeSizeRect();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsRect();
        [[nodiscard]] std::pair<double, double> computeConnectionPointRect(double angle) const;
    };

    class SVGEdge final : public SVGItem {
    public:
        using SVGItem::SVGItem;
        SVGEdge(const std::string& idFrom, const std::string& idTo);

        static constexpr std::string_view EDGE_SPLINES_LINE = "line";
        static constexpr std::string_view EDGE_SPLINES_SPLINE = "spline";
        static constexpr std::string_view EDGE_SPLINES_DEFAULT = EDGE_SPLINES_SPLINE;

        static constexpr std::string_view ARROW_SHAPE_NONE = "none";
        static constexpr std::string_view ARROW_SHAPE_NORMAL = SVGDrawMarker::SHAPE_NORMAL;
        static constexpr std::string_view ARROW_SHAPE_DEFAULT = ARROW_SHAPE_NORMAL;

        using NodesMapping = std::unordered_map<std::string, std::unique_ptr<SVGNode>>;

        void setNodeFrom(const std::string& id);
        [[nodiscard]] const std::string& nodeFrom() const;
        void setNodeTo(const std::string &id);
        [[nodiscard]] const std::string& nodeTo() const;
        void setConnection(const std::string& idFrom, const std::string& idTo);

        void setSplines(const std::string& value);
        void setSplines(const std::string_view& value);

        void addConnectionPoint(const std::pair<double, double>& point);
        void addConnectionPoint(double x, double y);

        std::vector<std::unique_ptr<SVGDraw>> produceSVGDraws(const NodesMapping& nodes);

        void setArrowHead();
        void setArrowHead(const std::string_view& shape);
        void setArrowTail();
        void setArrowTail(const std::string_view& shape);

    private:
        std::string _nodeFrom, _nodeTo;
        std::vector<std::pair<double, double>> _connectionPoints;

        static std::unique_ptr<SVGDrawMarker> produceSVGMarker(const std::string_view& shape);
        static std::string markerAttributeValue(const std::unique_ptr<SVGDrawMarker> &svgDraw);

        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsLine(const NodesMapping& nodes);
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsSpline(const NodesMapping& nodes);
    };

}

#endif //SVGDIAGRAM_SVG_NODES_H