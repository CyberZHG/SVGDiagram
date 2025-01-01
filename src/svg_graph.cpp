#include "svg_nodes.h"

#include <format>
#include <cmath>

#include "attribute_utils.h"
#include "svg_text_size.h"
#include "geometry_utils.h"
using namespace std;
using namespace svg_diagram;


void SVGGraph::addNode(shared_ptr<SVGNode>& node) {
    node->setParent(this);
    _nodes.emplace_back(node);
}

void SVGGraph::addEdge(shared_ptr<SVGEdge>& edge) {
    edge->setParent(this);
    _edges.emplace_back(edge);
}

void SVGGraph::addSubgraph(shared_ptr<SVGGraph>& subgraph) {
    subgraph->setParent(this);
    _graphs.emplace_back(subgraph);
}

void SVGGraph::removeNode(const SVGNode* node) {
    for (int i = 0; i < static_cast<int>(_nodes.size()); ++i) {
        if (_nodes[i].get() == node) {
            _nodes.erase(_nodes.begin() + i);  // Need to keep the original order
            break;
        }
    }
}

void SVGGraph::removeEdge(const SVGEdge* edge) {
    for (int i = 0; i < static_cast<int>(_edges.size()); ++i) {
        if (_edges[i].get() == edge) {
            _edges.erase(_edges.begin() + i);
            break;
        }
    }
}

void SVGGraph::removeSubgraph(const SVGGraph* subgraph) {
    for (int i = 0; i < static_cast<int>(_graphs.size()); ++i) {
        if (_graphs[i].get() == subgraph) {
            _graphs.erase(_graphs.begin() + i);
            break;
        }
    }
}

void SVGGraph::removeChild(const SVGItem* item) {
    removeNode(dynamic_cast<const SVGNode*>(item));
    removeEdge(dynamic_cast<const SVGEdge*>(item));
    removeSubgraph(dynamic_cast<const SVGGraph*>(item));
}

SVGNode& SVGGraph::defaultNodeAttributes() {
    return _defaultNode;
}

SVGEdge& SVGGraph::defaultEdgeAttributes() {
    return _defaultEdge;
}

optional<reference_wrapper<const string>> SVGGraph::defaultNodeAttribute(const string_view& key) const {
    if (const auto it = _defaultNode.attributes().find(key); it != _defaultNode.attributes().end()) {
        return std::ref(it->second);
    }
    if (parent() != nullptr) {
        return parent()->defaultNodeAttribute(key);
    }
    return {};
}

optional<reference_wrapper<const string>> SVGGraph::defaultEdgeAttribute(const string_view& key) const {
    if (const auto it = _defaultEdge.attributes().find(key); it != _defaultEdge.attributes().end()) {
        return it->second;
    }
    if (parent() != nullptr) {
        return parent()->defaultEdgeAttribute(key);
    }
    return {};
}

pair<double, double> SVGGraph::center() const {
    return {_cx, _cy};
}

void SVGGraph::adjustNodeSizes() {
    setAttributeIfNotExist(ATTR_KEY_MARGIN, string(ATTR_DEF_MARGIN_GRAPH));
    setAttributeIfNotExist(ATTR_KEY_FONT_NAME, string(ATTR_DEF_FONT_NAME));
    setAttributeIfNotExist(ATTR_KEY_FONT_SIZE, string(ATTR_DEF_FONT_SIZE));
    double minX = 0.0, minY = 0.0, maxX = 0.0, maxY = 0.0;
    bool first = true;
    const auto updateGraphSize = [&](const double cx, const double cy, const double width, const double height) {
        const double x1 = cx - width / 2.0;
        const double y1 = cy - height / 2.0;
        const double x2 = cx + width / 2.0;
        const double y2 = cy + height / 2.0;
        if (first) {
            first = false;
            minX = x1; minY = y1;
            maxX = x2; maxY = y2;
        } else {
            minX = min(minX, x1); minY = min(minY, y1);
            maxX = max(maxX, x2); maxY = max(maxY, y2);
        }
    };
    for (const auto& node : _nodes) {
        node->adjustNodeSize();
        const auto [cx, cy] = node->center();
        const auto strokeWidth = node->penWidth();
        const auto width = node->width() + strokeWidth;
        const auto height = node->height() + strokeWidth;
        updateGraphSize(cx, cy, width, height);
    }
    for (const auto& graph : _graphs) {
        graph->adjustNodeSizes();
        const auto [cx, cy] = graph->center();
        const auto strokeWidth = graph->penWidth();
        const auto width = graph->width() + strokeWidth;
        const auto height = graph->height() + strokeWidth;
        updateGraphSize(cx, cy, width, height);
    }
    if (first) {
        setSize(-1, -1);
    } else {
        const auto [marginWidth, marginHeight] = margin();
        if (const auto label = getAttribute(ATTR_KEY_LABEL); !label.empty()) {
            auto [textWidth, textHeight] = computeTextSize();
            textWidth += marginWidth * 2;
            if (textWidth > maxX - minX) {
                const double cx = (minX + maxX) / 2.0;
                minX = cx - textWidth / 2.0;
                maxX = cx + textWidth / 2.0;
            }
            minY -= textHeight + marginHeight;
            _textY = minY + textHeight / 2.0;
        }
        minX -= marginWidth; minY -= marginHeight;
        maxX += marginWidth; maxY += marginHeight;
        const auto width = maxX - minX;
        const auto height = maxY - minY;
        _cx = (minX + maxX) / 2.0;
        _cy = (minY + maxY) / 2.0;
        setSize(width, height);
    }
}

vector<unique_ptr<SVGDraw>> SVGGraph::produceSVGDraws(const NodesMapping &nodes) {
    adjustNodeSizes();
    vector<unique_ptr<SVGDraw>> svgDraws;
    for (auto& draw : produceClusterSVGDraws()) {
        svgDraws.emplace_back(std::move(draw));
    }
    for (auto& draw : produceNodeSVGDraws()) {
        svgDraws.emplace_back(std::move(draw));
    }
    for (auto& draw : produceEdgeSVGDraws(nodes)) {
        svgDraws.emplace_back(std::move(draw));
    }
    return svgDraws;
}

vector<shared_ptr<SVGNode>> SVGGraph::findNodes() const {
    vector<shared_ptr<SVGNode>> nodes = _nodes;
    for (auto& graph : _graphs) {
        for (auto& node : graph->findNodes()) {
            nodes.emplace_back(std::move(node));
        }
    }
    return nodes;
}

vector<unique_ptr<SVGDraw>> SVGGraph::produceNodeSVGDraws() const {
    vector<unique_ptr<SVGDraw>> svgDraws;
    for (const auto& node : _nodes) {
        if (enabledDebug()) {
            node->enableDebug();
        }
        const auto& id = node->id();
        svgDraws.emplace_back(make_unique<SVGDrawComment>(format("Node: {}", id)));
        auto group = make_unique<SVGDrawGroup>();
        group->setAttribute("id", id);
        group->setAttribute("class", "node");
        group->addChild(make_unique<SVGDrawTitle>(id));
        auto subDraws = node->produceSVGDraws();
        group->addChildren(subDraws);
        svgDraws.emplace_back(std::move(group));
    }
    for (const auto& graph : _graphs) {
        for (auto subDraws = graph->produceNodeSVGDraws(); auto& subDraw : subDraws) {
            svgDraws.emplace_back(std::move(subDraw));
        }
    }
    return svgDraws;
}

vector<unique_ptr<SVGDraw>> SVGGraph::produceEdgeSVGDraws(const NodesMapping& nodes) const {
    vector<unique_ptr<SVGDraw>> svgDraws;
    for (auto& edge : _edges) {
        if (enabledDebug()) {
            edge->enableDebug();
        }
        const auto& id = edge->id();
        svgDraws.emplace_back(make_unique<SVGDrawComment>(format("Edge: {} ({} -> {})", id, edge->nodeFrom(), edge->nodeTo())));
        auto group = make_unique<SVGDrawGroup>();
        group->setAttribute("id", id);
        group->setAttribute("class", "edge");
        group->addChild(make_unique<SVGDrawTitle>(format("{}->{}", edge->nodeFrom(), edge->nodeTo())));
        auto subDraws = edge->produceSVGDraws(nodes);
        group->addChildren(subDraws);
        svgDraws.emplace_back(std::move(group));
    }
    for (auto& graph : _graphs) {
        for (auto subDraws = graph->produceEdgeSVGDraws(nodes); auto& subDraw : subDraws) {
            svgDraws.emplace_back(std::move(subDraw));
        }
    }
    return svgDraws;
}

std::vector<std::unique_ptr<SVGDraw>> SVGGraph::produceClusterSVGDraws() {
    vector<unique_ptr<SVGDraw>> svgDraws;
    setAttributeIfNotExist(ATTR_KEY_COLOR, string(ATTR_DEF_COLOR_GRAPH));
    setAttributeIfNotExist(ATTR_KEY_FILL_COLOR, string(ATTR_DEF_FILL_COLOR));
    setAttributeIfNotExist(ATTR_KEY_FONT_COLOR, string(ATTR_DEF_FONT_COLOR));
    setAttributeIfNotExist(ATTR_KEY_PEN_WIDTH, string(ATTR_DEF_PEN_WIDTH));
    setAttributeIfNotExist(ATTR_KEY_FONT_NAME, string(ATTR_DEF_FONT_NAME));
    setAttributeIfNotExist(ATTR_KEY_FONT_SIZE, string(ATTR_DEF_FONT_SIZE));
    if (const auto _width = width(), _height = height(); _width > 0 && _height > 0) {
        const auto& _color = color();
        const auto& _fillColor = fillColor();
        if (_color != "none" || _fillColor != "none") {
            auto group = make_unique<SVGDrawGroup>();
            group->setAttribute("id", id());
            group->setAttribute("class", "cluster");
            auto rect = make_unique<SVGDrawRect>(_cx, _cy, _width, _height);
            rect->setStroke(color());
            rect->setFill(fillColor());
            if (const auto strokeWidth = penWidth(); strokeWidth != 1.0) {
                rect->setStrokeWidth(strokeWidth);
            }
            group->addChild(std::move(rect));
            if (enabledDebug()) {
                const auto [marginX, marginY] = margin();
                auto childrenRect = make_unique<SVGDrawRect>(_cx, _cy, _width - marginX * 2.0, _height - marginY * 2.0);
                childrenRect->setFill("none");
                childrenRect->setStroke("green");
                group->addChild(std::move(childrenRect));
            }
            svgDraws.emplace_back(std::move(group));
        }
        if (const auto& _label = getAttribute(ATTR_KEY_LABEL); !_label.empty()) {
            appendSVGDrawsLabelWithCenter(svgDraws, _cx, _textY);
        }
    }
    for (const auto& graph : _graphs) {
        if (enabledDebug()) {
            graph->enableDebug();
        }
        for (auto subDraws = graph->produceClusterSVGDraws(); auto& subDraw : subDraws) {
            svgDraws.emplace_back(std::move(subDraw));
        }
    }
    return svgDraws;
}
