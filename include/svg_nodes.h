#ifndef SVGDIAGRAM_SVG_NODES_H
#define SVGDIAGRAM_SVG_NODES_H

#include <string>
#include <unordered_map>
#include <memory>
#include <optional>

#include "svg_draw.h"

namespace svg_diagram {

    constexpr std::string_view ATTRIBUTE_KEY_ID = "id";
    constexpr std::string_view ATTRIBUTE_KEY_LABEL = "label";
    constexpr std::string_view ATTRIBUTE_KEY_SHAPE = "shape";
    constexpr std::string_view ATTRIBUTE_KEY_SPLINES = "splines";
    constexpr std::string_view ATTRIBUTE_KEY_MARGIN = "margin";
    constexpr std::string_view ATTRIBUTE_KEY_WIDTH = "width";
    constexpr std::string_view ATTRIBUTE_KEY_HEIGHT = "height";
    constexpr std::string_view ATTRIBUTE_KEY_FONT_NAME = "fontname";
    constexpr std::string_view ATTRIBUTE_KEY_FONT_SIZE = "fontsize";
    constexpr std::string_view ATTRIBUTE_KEY_FIXED_SIZE = "fixedsize";
    constexpr std::string_view ATTRIBUTE_KEY_ARROW_HEAD = "arrowhead";
    constexpr std::string_view ATTRIBUTE_KEY_ARROW_TAIL = "arrowtail";
    constexpr std::string_view ATTRIBUTE_KEY_COLOR = "color";
    constexpr std::string_view ATTRIBUTE_KEY_FILL_COLOR = "fillcolor";
    constexpr std::string_view ATTRIBUTE_KEY_FONT_COLOR = "fontcolor";
    constexpr std::string_view ATTRIBUTE_KEY_PEN_WIDTH = "penwidth";

    class SVGNode;
    class SVGGraph;
    using NodesMapping = std::unordered_map<std::string, std::shared_ptr<SVGNode>>;

    class SVGItem {
    public:
        SVGItem() = default;
        explicit SVGItem(const std::string& id);
        virtual ~SVGItem() = default;

        void enableDebug();
        [[nodiscard]] bool enabledDebug() const;

        void setParent(SVGGraph* parent);
        [[nodiscard]] SVGGraph* parent() const;

        [[nodiscard]] const std::unordered_map<std::string_view, std::string>& attributes() const;
        void setAttribute(const std::string_view& key, const std::string& value);
        void setAttribute(const std::string_view& key, double value);
        virtual void setAttributeIfNotExist(const std::string_view& key, const std::string& value);
        void setDoubleAttributeIfNotExist(const std::string_view& key, double value);
        [[nodiscard]] virtual const std::string& getAttribute(const std::string_view& key) const;

        void setPrecomputedTextSize(double width, double height);
        [[nodiscard]] std::pair<double, double> precomputedTextSize() const;
        [[nodiscard]] const std::string& id() const;
        void setID(const std::string& id);
        void setLabel(const std::string& label);
        [[nodiscard]] double width() const;
        void setWidth(double width);
        [[nodiscard]] double height() const;
        void setHeight(double height);
        void setSize(double width, double height);
        void setFixedSize(double width, double height);
        [[nodiscard]] std::pair<double, double> margin() const;
        void setMargin(const std::string& value);
        void setMargin(double margin);
        void setMargin(double marginX, double marginY);
        [[nodiscard]] std::string color() const;
        void setColor(const std::string& color);
        [[nodiscard]] std::string fillColor() const;
        void setFillColor(const std::string& color);
        [[nodiscard]] std::string fontColor() const;
        void setFontColor(const std::string& color);
        void setPenWidth(double width);
        [[nodiscard]] double penWidth() const;
        void setFontName(const std::string& fontName);
        void setFontSize(double fontSize);
        void setFont(const std::string& fontName, double fontSize);

    protected:
        void appendSVGDrawsLabelWithCenter(std::vector<std::unique_ptr<SVGDraw>>& svgDraws, double cx, double cy);

        [[nodiscard]] std::pair<double, double> computeTextSize();
        [[nodiscard]] std::pair<double, double> computeMargin();
        [[nodiscard]] std::pair<double, double> computeTextSizeWithMargin();

    private:
        SVGGraph* _parent = nullptr;
        bool _enabledDebug = false;
        double _precomputedTextWidth = 0.0;
        double _precomputedTextHeight = 0.0;
        std::unordered_map<std::string_view, std::string> _attributes;
    };

    class SVGNode final : public SVGItem {
    public:
        using SVGItem::SVGItem;
        SVGNode(double cx, double cy);

        static constexpr std::string_view SHAPE_NONE = "none";
        static constexpr std::string_view SHAPE_CIRCLE = "circle";
        static constexpr std::string_view SHAPE_DOUBLE_CIRCLE = "doublecircle";
        static constexpr std::string_view SHAPE_RECT = "rect";
        static constexpr std::string_view SHAPE_ELLIPSE = "ellipse";
        static constexpr std::string_view SHAPE_DEFAULT = SHAPE_ELLIPSE;

        static constexpr auto DOUBLE_BORDER_MARGIN = 4.0;

        void setAttributeIfNotExist(const std::string_view& key, const std::string& value) override;

        [[nodiscard]] const std::string& getAttribute(const std::string_view& key) const override;

        void setShape(const std::string& shape);
        void setShape(const std::string_view& shape);

        void setCenter(double cx, double cy);
        [[nodiscard]] std::pair<double, double> center() const;

        void adjustNodeSize();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDraws();

        std::pair<double, double> computeConnectionPoint(double angle);

        [[nodiscard]] double computeAngle(double x, double y) const;
        [[nodiscard]] double computeAngle(const std::pair<double, double>& p) const;

    private:
        double _cx = 0.0;
        double _cy = 0.0;

        [[nodiscard]] bool isFixedSize() const;
        void updateNodeSize(double width, double height);
        void updateNodeSize(const std::pair<double, double>& size);

        void appendSVGDrawsLabel(std::vector<std::unique_ptr<SVGDraw>>& svgDraws);

        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsNone();

        void adjustNodeSizeCircle();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsCircle();
        [[nodiscard]] std::pair<double, double> computeConnectionPointCircle(double angle) const;

        void adjustNodeSizeDoubleCircle();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsDoubleCircle();
        [[nodiscard]] std::pair<double, double> computeConnectionPointDoubleCircle(double angle) const;

        void adjustNodeSizeRect();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsRect();
        [[nodiscard]] std::pair<double, double> computeConnectionPointRect(double angle) const;

        void adjustNodeSizeEllipse();
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsEllipse();
        [[nodiscard]] std::pair<double, double> computeConnectionPointEllipse(double angle) const;
    };

    class SVGEdge final : public SVGItem {
    public:
        using SVGItem::SVGItem;
        SVGEdge(const std::string& idFrom, const std::string& idTo);

        static constexpr std::string_view SPLINES_LINE = "line";
        static constexpr std::string_view SPLINES_SPLINE = "spline";
        static constexpr std::string_view SPLINES_DEFAULT = SPLINES_SPLINE;

        static constexpr std::string_view ARROW_NONE = "none";
        static constexpr std::string_view ARROW_NORMAL = "normal";
        static constexpr std::string_view ARROW_EMPTY = "empty";
        static constexpr std::string_view ARROW_DEFAULT = ARROW_NORMAL;

        void setAttributeIfNotExist(const std::string_view& key, const std::string& value) override;
        [[nodiscard]] const std::string& getAttribute(const std::string_view& key) const override;

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

        static constexpr double ARROW_WIDTH = 10.0;
        static constexpr double ARROW_HEIGHT = 7.0;
        static constexpr double ARROW_HALF_HEIGHT = ARROW_HEIGHT / 2.0;

        std::pair<double, double> computeTextCenter(double cx, double cy, double dx, double dy);

        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsLine(const NodesMapping& nodes);
        std::vector<std::unique_ptr<SVGDraw>> produceSVGDrawsSpline(const NodesMapping& nodes);

        [[nodiscard]] double computeArrowTipMargin(const std::string_view& shape) const;
        [[nodiscard]] double computeArrowTipMarginNormal() const;
        std::pair<double, double> addArrow(const std::string_view& shape, std::vector<std::unique_ptr<SVGDraw>>& svgDraws, const std::pair<double, double>& connectionPoint, double angle) const;
        std::pair<double, double> addArrowNormal(std::vector<std::unique_ptr<SVGDraw>>& svgDraws, const std::pair<double, double>& connectionPoint, double angle, bool solid = true) const;
    };

    class SVGGraph final : public SVGItem {
    public:
        using SVGItem::SVGItem;

        void addNode(std::shared_ptr<SVGNode>& node);
        void addEdge(std::shared_ptr<SVGEdge>& edge);
        void addSubgraph(std::shared_ptr<SVGGraph>& subgraph);

        SVGNode& defaultNodeAttributes();
        SVGEdge& defaultEdgeAttributes();

        [[nodiscard]] std::optional<std::reference_wrapper<const std::string>> defaultNodeAttribute(const std::string_view& key) const;
        [[nodiscard]] std::optional<std::reference_wrapper<const std::string>> defaultEdgeAttribute(const std::string_view& key) const;

        [[nodiscard]] std::pair<double, double> center() const;

        void adjustNodeSizes();
        [[nodiscard]] std::vector<std::unique_ptr<SVGDraw>> produceSVGDraws(const NodesMapping& nodes);

        [[nodiscard]] std::vector<std::shared_ptr<SVGNode>> findNodes() const;

    private:
        double _cx = 0.0;
        double _cy = 0.0;
        double _textY = 0.0;

        std::vector<std::shared_ptr<SVGNode>> _nodes;
        std::vector<std::shared_ptr<SVGEdge>> _edges;
        std::vector<std::shared_ptr<SVGGraph>> _graphs;

        SVGNode _defaultNode;
        SVGEdge _defaultEdge;

        [[nodiscard]] std::vector<std::unique_ptr<SVGDraw>> produceNodeSVGDraws() const;
        [[nodiscard]] std::vector<std::unique_ptr<SVGDraw>> produceEdgeSVGDraws(const NodesMapping& nodes) const;
        [[nodiscard]] std::vector<std::unique_ptr<SVGDraw>> produceClusterSVGDraws();
    };

}

#endif //SVGDIAGRAM_SVG_NODES_H