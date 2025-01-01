#ifndef SVGDIAGRAM_SVG_DRAW_H
#define SVGDIAGRAM_SVG_DRAW_H

#include <string>
#include <map>

#include "xml_element.h"

namespace svg_diagram {

    constexpr std::string_view SVG_ATTR_KEY_FILL = "fill";
    constexpr std::string_view SVG_ATTR_KEY_STROKE = "stroke";
    constexpr std::string_view SVG_ATTR_KEY_FONT_FAMILY = "font-family";
    constexpr std::string_view SVG_ATTR_KEY_FONT_SIZE = "font-size";
    constexpr std::string_view SVG_ATTR_KEY_MARKER_START = "marker-start";
    constexpr std::string_view SVG_ATTR_KEY_MARKER_END = "marker-end";
    constexpr std::string_view SVG_ATTR_KEY_STROKE_WIDTH = "stroke-width";

    struct SVGDrawBoundingBox {
        double x1, y1, x2, y2;

        SVGDrawBoundingBox() = default;
        SVGDrawBoundingBox(double x1, double y1, double x2, double y2);
    };

    class SVGDraw {
    public:
        SVGDraw() = default;
        virtual ~SVGDraw() = default;

        static constexpr int DEFAULT_NUM_DECIMALS = 3;

        /** Generate a vector of XML elements.
         *
         * @return XML elements.
         */
        [[nodiscard]] virtual XMLElement::ChildrenType generateXMLElements() const = 0;

        /** Compute a bounding box for this object.
         *
         * @return Bounding box.
         */
        [[nodiscard]] virtual SVGDrawBoundingBox boundingBox() const = 0;

        /** Whether a visible shape will be rendered.
         *
         * @return Whether it is visible.
         */
        [[nodiscard]] virtual bool hasEntity() const = 0;

        /** If the return value is not empty,
         * this class will be rendered only once when generating the SVG.
         *
         * @return An unique ID.
         */
        [[nodiscard]] virtual std::string singletonName() const;
        void setSingletonName(const std::string& singletonName);

        [[nodiscard]] virtual bool isDefs() const;

        void setNumDecimals(int numDecimals);

    protected:
        std::map<std::string_view, std::string> _attributes;

        void addAttributesToXMLElement(const XMLElement::ChildType& element) const;

    private:
        int _numDecimals = DEFAULT_NUM_DECIMALS;
        std::string _singletonName;
    };

    class SVGDrawComment final : public SVGDraw {
    public:
        using SVGDraw::SVGDraw;
        explicit SVGDrawComment(const std::string& comment);

        std::string comment;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;

        [[nodiscard]] bool hasEntity() const override;
    };

    class SVGDrawAttribute : public SVGDraw {
    public:
        using SVGDraw::SVGDraw;

        void setAttribute(const std::string_view& key, const std::string& value);
        void setFill(const std::string& value);
        void setStroke(const std::string& value);
        void setStrokeWidth(const std::string& value);
    };

    class SVGDrawEntity : public SVGDrawAttribute {
    public:
        using SVGDrawAttribute::SVGDrawAttribute;

        [[nodiscard]] bool hasEntity() const override;
    };

    class SVGDrawNode : public SVGDrawEntity {
    public:
        using SVGDrawEntity::SVGDrawEntity;
        SVGDrawNode(double cx, double cy, double width, double height);

        double cx, cy, width, height;

        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawText final : public SVGDrawNode {
    public:
        SVGDrawText();
        SVGDrawText(double x, double y, const std::string& text);

        std::string text;

        void setFont(const std::string& fontFamily, double fontSize);

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawCircle final : public SVGDrawNode {
    public:
        using SVGDrawNode::SVGDrawNode;
        SVGDrawCircle(double x, double y, double radius);

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;

        /** A circle should have the same width and height.
         * If the width or height is misconfigured,
         * the circle’s diameter will be determined by the smaller of the two values.
         *
         * @return Bounding box.
         */
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawRect final : public SVGDrawNode {
    public:
        using SVGDrawNode::SVGDrawNode;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
    };

    class SVGDrawEllipse final : public SVGDrawNode {
    public:
        using SVGDrawNode::SVGDrawNode;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
    };

    class SVGDrawLine final : public SVGDrawEntity {
    public:
        using SVGDrawEntity::SVGDrawEntity;
        SVGDrawLine(double x1, double y1, double x2, double y2);

        double x1, y1, x2, y2;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawPath final : public SVGDrawEntity {
    public:
        using SVGDrawEntity::SVGDrawEntity;
        explicit SVGDrawPath(const std::string& d);

        std::string d;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawDefs : public SVGDrawAttribute {
    public:
        using SVGDrawAttribute::SVGDrawAttribute;

        [[nodiscard]] bool isDefs() const override;
        [[nodiscard]] bool hasEntity() const override;

        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawMarker final : public SVGDrawDefs {
    public:
        using SVGDrawDefs::SVGDrawDefs;

        static constexpr std::string_view SHAPE_NORMAL = "normal";

        void setShape(const std::string& shape);

        [[nodiscard]] std::string singletonName() const override;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;

    private:
        std::string _shape;

        [[nodiscard]] XMLElement::ChildrenType renderNormal() const;
    };

}

#endif //SVGDIAGRAM_SVG_DRAW_H
