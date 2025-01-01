#ifndef SVGDIAGRAM_SVG_DIAGRAM_H
#define SVGDIAGRAM_SVG_DIAGRAM_H

#include <vector>

#include "svg_draw.h"
#include "svg_nodes.h"

namespace svg_diagram {

    class SVGDiagram final {
    public:
        SVGDiagram();
        ~SVGDiagram() = default;

        static constexpr double DEFAULT_MARGIN = 8;

        void clearSVGDraw();
        void addSVGDraw(std::unique_ptr<SVGDraw> svgDraw);
        void addSVGDraw(std::vector<std::unique_ptr<SVGDraw>> svgDraws);

        void setCanvasSize(int width, int height);
        void setBackgroundColor(const std::string& backgroundColor);

        void addNode(const std::string& id, std::unique_ptr<SVGNode> node);

        [[nodiscard]] std::string render();
        void render(const std::string& filePath);

    private:
        std::vector<std::unique_ptr<SVGDraw>> _svgDraws;
        std::vector<std::unique_ptr<SVGDraw>> _svgDrawsDynamic;
        double _width = 0.0;
        double _height = 0.0;
        std::pair<double, double> _margin = {DEFAULT_MARGIN, DEFAULT_MARGIN};
        std::string _backgroundColor;

        std::unordered_map<std::string, std::unique_ptr<SVGNode>> _nodes;

        void produceSVGDrawsDynamic();

        [[nodiscard]] std::string generateSVGOpen() const;
        [[nodiscard]] std::string generateSVGClose() const;
    };

}

#endif //SVGDIAGRAM_SVG_DIAGRAM_H
