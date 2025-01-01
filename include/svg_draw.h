#ifndef SVGDIAGRAM_SVG_DRAW_H
#define SVGDIAGRAM_SVG_DRAW_H

#include <string>
#include <map>

namespace svg_diagram {

    constexpr std::string_view SVG_ATTRIBUTE_FILL = "fill";
    constexpr std::string_view SVG_ATTRIBUTE_STROKE = "stroke";
    constexpr std::string_view SVG_ATTRIBUTE_FONT_FAMILY = "font-family";
    constexpr std::string_view SVG_ATTRIBUTE_FONT_SIZE = "font-size";

    struct SVGDrawBoundingBox {
        double x1, y1, x2, y2;

        SVGDrawBoundingBox() = default;
        SVGDrawBoundingBox(double x1, double y1, double x2, double y2);
    };

    class SVGDraw {
    public:
        SVGDraw() = default;
        virtual ~SVGDraw() = default;

        /** Generate a SVG string.
         *
         * @return SVG string.
         */
        [[nodiscard]] virtual std::string render() const = 0;
        [[nodiscard]] std::string renderWithIndent(int indent) const;

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
    };

    class SVGDrawComment final : public SVGDraw {
    public:
        using SVGDraw::SVGDraw;
        explicit SVGDrawComment(const std::string& comment);

        std::string comment;

        [[nodiscard]] std::string render() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;

        [[nodiscard]] bool hasEntity() const override;
    };

    class SVGDrawEntity : public SVGDraw {
    public:
        using SVGDraw::SVGDraw;

        [[nodiscard]] bool hasEntity() const override;
        void setAttribute(const std::string_view& key, const std::string& value);

    protected:
        std::map<std::string_view, std::string> _attributes;

        [[nodiscard]] std::string renderAttributes() const;
    };

    class SVGDrawNode : public SVGDrawEntity {
    public:
        using SVGDrawEntity::SVGDrawEntity;

        double cx, cy, width, height;

        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawText final : public SVGDrawNode {
    public:
        SVGDrawText();
        SVGDrawText(double x, double y, const std::string& text);

        std::string text;

        void setFont(const std::string& fontFamily, double fontSize);

        [[nodiscard]] std::string render() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawCircle final : public SVGDrawNode {
    public:
        using SVGDrawNode::SVGDrawNode;
        SVGDrawCircle(double x, double y, double radius);

        [[nodiscard]] std::string render() const override;

        /** A circle should have the same width and height.
         * If the width or height is misconfigured,
         * the circle’s diameter will be determined by the smaller of the two values.
         *
         * @return Bounding box.
         */
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

    class SVGDrawLine final : public SVGDrawEntity {
    public:
        using SVGDrawEntity::SVGDrawEntity;
        SVGDrawLine(double x1, double y1, double x2, double y2);

        double x1, y1, x2, y2;

        [[nodiscard]] std::string render() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;
    };

}

#endif //SVGDIAGRAM_SVG_DRAW_H
