#ifndef SVGDIAGRAM_SVG_DIAGRAM_H
#define SVGDIAGRAM_SVG_DIAGRAM_H

#include <vector>

#include "svg_draw.h"

namespace svg_diagram {

    class SVGDiagram final {
    public:
        SVGDiagram();
        ~SVGDiagram() = default;

        static constexpr double DEFAULT_MARGIN = 8;

        void addSVGDraw(std::unique_ptr<SVGDraw> svgDraw);

        [[nodiscard]] std::string render() const;
        void render(const std::string& filePath) const;

        void setCanvasSize(int width, int height);
        void setBackgroundColor(const std::string& backgroundColor);

    private:
        std::vector<std::unique_ptr<SVGDraw>> _svgDraws;
        double _width = 0.0;
        double _height = 0.0;
        std::pair<double, double> _margin = {DEFAULT_MARGIN, DEFAULT_MARGIN};
        std::string _backgroundColor;

        [[nodiscard]] std::string generateSVGOpen() const;
        [[nodiscard]] std::string generateSVGClose() const;
    };

}

#endif //SVGDIAGRAM_SVG_DIAGRAM_H
