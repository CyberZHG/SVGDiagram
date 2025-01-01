#ifndef SVGDIAGRAM_SVG_DIAGRAM_H
#define SVGDIAGRAM_SVG_DIAGRAM_H

#include <unordered_set>
#include <vector>

#include "svg_draw.h"
#include "svg_nodes.h"

namespace svg_diagram {

    class SVGDiagram final {
    public:
        SVGDiagram();
        ~SVGDiagram() = default;

        static constexpr double DEFAULT_MARGIN = 8;

        void enableDebug();

        void clearSVGDraw();
        void addSVGDraw(std::unique_ptr<SVGDraw> svgDraw);
        void addSVGDraw(std::vector<std::unique_ptr<SVGDraw>> svgDraws);

        void setCanvasSize(int width, int height);
        void setBackgroundColor(const std::string& backgroundColor);

        const std::unique_ptr<SVGNode>& addNode(const std::string& id);
        void addNode(const std::string& id, std::unique_ptr<SVGNode> node);
        const std::unique_ptr<SVGEdge>& addEdge(const std::string& id);
        const std::unique_ptr<SVGEdge>& addEdge(const std::string& from, const std::string& to);
        void addEdge(const std::string& id, std::unique_ptr<SVGEdge> edge);
        void addEdge(std::unique_ptr<SVGEdge> edge);

        [[nodiscard]] std::string render();
        void render(const std::string& filePath);

    private:
        bool _enabledDebug = false;

        std::vector<std::unique_ptr<SVGDraw>> _svgDraws;
        std::vector<std::unique_ptr<SVGDraw>> _svgDrawsDynamic;
        double _width = 0.0;
        double _height = 0.0;
        std::pair<double, double> _margin = {DEFAULT_MARGIN, DEFAULT_MARGIN};
        std::string _backgroundColor;

        std::unordered_map<std::string, std::unique_ptr<SVGNode>> _nodes;
        std::unordered_map<std::string, std::unique_ptr<SVGEdge>> _edges;
        std::vector<std::string> _nodeIds;
        std::vector<std::string> _edgeIds;

        void produceSVGDrawsDynamic();

        static bool guardSingleton(std::unordered_set<std::string>& singletonNames, const std::unique_ptr<SVGDraw>& svgDraw);

        [[nodiscard]] std::string generateSVGOpen() const;
        [[nodiscard]] std::string renderDefs(std::unordered_set<std::string>& singletonNames) const;
        static std::string generateSVGClose();
    };

}

#endif //SVGDIAGRAM_SVG_DIAGRAM_H
