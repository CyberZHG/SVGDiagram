#ifndef SVGDIAGRAM_SVG_DRAW_H
#define SVGDIAGRAM_SVG_DRAW_H

#include <string>
#include <map>
#include <memory>

#include "xml_element.h"

namespace svg_diagram {

    struct SVGDrawBoundingBox {
        double x1, y1, x2, y2;

        SVGDrawBoundingBox() = default;
        SVGDrawBoundingBox(double x1, double y1, double x2, double y2);
    };

    class SVGDraw {
    public:
        SVGDraw() = default;
        virtual ~SVGDraw() = default;

        /** Generate a vector of XML elements.
         *
         * @return XML elements.
         */
        [[nodiscard]] virtual XMLElement::ChildrenType generateXMLElements() const;

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

        void setAttribute(const std::string_view& key, const std::string& value);
        void setAttribute(const std::string_view& key, double value);
        void copyAttributes(const SVGDraw* other);

        void setID(const std::string& id);
        void setFill(const std::string& value);
        void setFillOpacity(double opacity);
        void setStroke(const std::string& value);
        void setStrokeWidth(const std::string& value);
        void setStrokeWidth(double value);
        void setStrokeDashArray(const std::string& value);
        void setStrokeOpacity(double opacity);

    protected:
        [[nodiscard]] virtual std::string tag() const = 0;
        std::map<std::string_view, std::string> _attributes;

        void addAttributesToXMLElement(const XMLElement::ChildType& element) const;
    };

    class SVGDrawEntity : public SVGDraw {
    public:
        using SVGDraw::SVGDraw;

        [[nodiscard]] bool hasEntity() const override;
    };

    class SVGDrawNoEntity : virtual public SVGDraw {
    public:
        using SVGDraw::SVGDraw;

        [[nodiscard]] bool hasEntity() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawContainer : virtual public SVGDraw {
    public:
        using SVGDraw::SVGDraw;
        explicit SVGDrawContainer(std::unique_ptr<SVGDraw> draw);
        explicit SVGDrawContainer(std::vector<std::unique_ptr<SVGDraw>>& draws);

        std::vector<std::unique_ptr<SVGDraw>> children;

        void addChild(std::unique_ptr<SVGDraw> child);
        void addChildren(std::vector<std::unique_ptr<SVGDraw>>& draws);

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
    };

    class SVGDrawComment final : public SVGDrawNoEntity {
    public:
        using SVGDrawNoEntity::SVGDrawNoEntity;
        explicit SVGDrawComment(const std::string& comment);

        std::string comment;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;

        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawTitle final : public SVGDrawNoEntity {
    public:
        using SVGDrawNoEntity::SVGDrawNoEntity;
        explicit SVGDrawTitle(const std::string& title);

        std::string title;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawNode : public SVGDrawEntity {
    public:
        using SVGDrawEntity::SVGDrawEntity;
        SVGDrawNode(double cx, double cy, double width, double height);

        double cx = 0;
        double cy = 0;
        double width = 0;
        double height= 0;

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

    protected:
        [[nodiscard]] std::string tag() const override;
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

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawRect final : public SVGDrawNode {
    public:
        using SVGDrawNode::SVGDrawNode;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawEllipse final : public SVGDrawNode {
    public:
        using SVGDrawNode::SVGDrawNode;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawPolygon final : public SVGDrawNode {
    public:
        using SVGDrawNode::SVGDrawNode;
        explicit SVGDrawPolygon(const std::vector<std::pair<double, double>>& points);

        std::vector<std::pair<double, double>> points;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawLine final : public SVGDrawEntity {
    public:
        using SVGDrawEntity::SVGDrawEntity;
        SVGDrawLine(double x1, double y1, double x2, double y2);

        double x1 = 0, y1 = 0, x2 = 0, y2 = 0;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawPath final : public SVGDrawEntity {
    public:
        using SVGDrawEntity::SVGDrawEntity;
        explicit SVGDrawPath(const std::string& d);

        std::string d;

        [[nodiscard]] XMLElement::ChildrenType generateXMLElements() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawGroup final : public SVGDrawContainer {
    public:
        using SVGDrawContainer::SVGDrawContainer;

        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
        [[nodiscard]] bool hasEntity() const override;

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawDefs final : public SVGDrawContainer, public SVGDrawNoEntity {
    public:
        using SVGDrawContainer::SVGDrawContainer;

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawLinearGradient final : public SVGDrawContainer, public SVGDrawNoEntity {
    public:
        using SVGDrawContainer::SVGDrawContainer;

        void setRotation(double angle);

    protected:
        [[nodiscard]] std::string tag() const override;
    };

    class SVGDrawStop final : public SVGDrawNoEntity {
    public:
        using SVGDrawNoEntity::SVGDrawNoEntity;
        SVGDrawStop(double offset, const std::string& color, double opacity = 1.0);

        void setOffset(double offset);
        void setColor(const std::string& color);
        void setOpacity(double opacity);

    protected:
        [[nodiscard]] std::string tag() const override;
    };

}

#endif //SVGDIAGRAM_SVG_DRAW_H
