#ifndef SVGDIAGRAM_SVG_DIAGRAM_H
#define SVGDIAGRAM_SVG_DIAGRAM_H

#include <vector>
#include <memory>

#include "svg_draw.h"
#include "svg_nodes.h"

namespace svg_diagram {

    class SVGDiagram final {
    public:
        SVGDiagram() = default;
        ~SVGDiagram() = default;

        static constexpr double DEFAULT_MARGIN = 8;

        void enableDebug();

        void clearSVGDraw();
        void addSVGDraw(std::unique_ptr<SVGDraw> svgDraw);
        void addSVGDraw(std::vector<std::unique_ptr<SVGDraw>>& svgDraws);

        void setCanvasSize(int width, int height);
        void setBackgroundColor(const std::string& backgroundColor);
        void setFixedViewBox(double x0, double y0, double width, double height);
        void setRotation(double angle);
        void setRotation(double angle, double cx, double cy);

        SVGNode& defaultNodeAttributes();
        SVGEdge& defaultEdgeAttributes();

        const std::shared_ptr<SVGNode>& addNode(const std::string& id);
        void addNode(const std::string& id, std::shared_ptr<SVGNode>& node);
        const std::shared_ptr<SVGEdge>& addEdge(const std::string& id);
        const std::shared_ptr<SVGEdge>& addEdge(const std::string& from, const std::string& to);
        const std::shared_ptr<SVGEdge>& addSelfLoop(const std::string& nodeId, double dir, double height, double angle = 30);
        void addEdge(const std::string& id, std::shared_ptr<SVGEdge>& edge);
        void addEdge(std::shared_ptr<SVGEdge>& edge);
        const std::shared_ptr<SVGGraph>& addSubgraph(const std::string& id);
        void addSubgraph(const std::string& id, std::shared_ptr<SVGGraph>& subgraph);

        [[nodiscard]] std::string render();
        void render(const std::string& filePath);

    private:
        bool _enabledDebug = false;

        int _nodeIndex = 1;
        int _edgeIndex = 1;

        std::vector<std::unique_ptr<SVGDraw>> _svgDraws;
        std::vector<std::unique_ptr<SVGDraw>> _svgDrawsDynamic;
        double _viewBoxX = 0.0;
        double _viewBoxY = 0.0;
        double _width = 0.0;
        double _height = 0.0;
        bool _isFixedViewBox = false;
        double _rotation = 0.0;
        double _rotationCX = 0.0;
        double _rotationCY = 0.0;
        bool _hasRotationCenter = false;
        std::pair<double, double> _margin = {DEFAULT_MARGIN, DEFAULT_MARGIN};
        std::string _backgroundColor;

        SVGGraph _graph;
        std::unordered_map<std::string, std::shared_ptr<SVGNode>> _nodes;
        std::unordered_map<std::string, std::shared_ptr<SVGEdge>> _edges;
        std::unordered_map<std::string, std::shared_ptr<SVGGraph>> _subgraphs;

        std::string newEdgeId();

        void produceSVGDrawsDynamic();

        [[nodiscard]] std::pair<XMLElement::ChildType, XMLElement::ChildType> generateSVGElement() const;
    };

}

#endif //SVGDIAGRAM_SVG_DIAGRAM_H
