#ifndef SVGDIAGRAM_SVG_NODES_H
#define SVGDIAGRAM_SVG_NODES_H

#include <string>
#include <unordered_map>

namespace svg_diagram {

    class SVGNode final {
    public:
        SVGNode() = default;
        ~SVGNode() = default;

        static constexpr std::string_view ATTR_KEY_LABEL = "label";
        static constexpr std::string_view ATTR_KEY_SHAPE = "shape";
        static constexpr std::string_view ATTR_KEY_MARGIN = "margin";

        void setAttribute(const std::string_view& key, const std::string& value);
        [[nodiscard]] const std::string& getAttribute(const std::string_view& key) const;

    private:
        std::unordered_map<std::string_view, std::string> _attributes;
    };

}

#endif //SVGDIAGRAM_SVG_NODES_H