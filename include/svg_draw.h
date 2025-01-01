#ifndef SVGDIAGRAM_SVG_DRAW_H
#define SVGDIAGRAM_SVG_DRAW_H

#include <string>

namespace svg_diagram {

    struct SVGDrawBoundingBox {
        double x1, y1, x2, y2;

        SVGDrawBoundingBox() = default;
        SVGDrawBoundingBox(double x1, double y1, double x2, double y2);
    };

    class SVGDraw {
    public:
        SVGDraw() = default;
        explicit SVGDraw(const std::string& label);
        virtual ~SVGDraw() = default;

        [[nodiscard]] virtual std::string render() const = 0;
        [[nodiscard]] virtual SVGDrawBoundingBox boundingBox() const = 0;

        [[nodiscard]] const std::string& label() const;
        void setLabel(const std::string& label);

        [[nodiscard]] virtual bool hasEntity() const = 0;
        [[nodiscard]] virtual bool singleton() const = 0;

    private:
        std::string _label;
    };

    class SVGDrawComment final : public SVGDraw {
    public:
        using SVGDraw::SVGDraw;

        [[nodiscard]] std::string render() const override;
        [[nodiscard]] SVGDrawBoundingBox boundingBox() const override;

        [[nodiscard]] bool hasEntity() const override;
        [[nodiscard]] bool singleton() const override;
    };

}

#endif //SVGDIAGRAM_SVG_DRAW_H