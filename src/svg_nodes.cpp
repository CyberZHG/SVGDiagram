#include "svg_nodes.h"

#include <format>

#include "attribute_utils.h"
#include "svg_text_size.h"
#include "geometry_utils.h"
using namespace std;
using namespace svg_diagram;

SVGNode::SVGNode(const double cx, const double cy) {
    _cx = cx;
    _cy = cy;
}

void SVGNode::setAttribute(const string_view& key, const string& value) {
    _attributes[key] = value;
}

void SVGNode::setAttributeIfNotExist(const string_view& key, const string& value) {
    if (!_attributes.contains(key)) {
        _attributes[key] = value;
    }
}

static const string EMPTY_STRING;

const string& SVGNode::getAttribute(const string_view& key) const {
    if (const auto it = _attributes.find(key); it != _attributes.end()) {
        return it->second;
    }
    return EMPTY_STRING;
}

void SVGNode::setPrecomputedTextSize(const double width, const double height) {
    _precomputedTextWidth = width;
    _precomputedTextHeight = height;
}

void SVGNode::setLabel(const string& label) {
    setAttribute(DOT_ATTR_KEY_LABEL, label);
}

void SVGNode::setMargin(const string& value) {
    setAttribute(DOT_ATTR_KEY_MARGIN, value);
}

void SVGNode::setMargin(const double margin) {
    setMargin(format("{}", margin));
}

void SVGNode::setMargin(const double marginX, const double marginY) {
    setMargin(format("{},{}", marginX, marginY));
}

void SVGNode::setMarginInPixels(const double margin) {
    setMargin(margin / SVG_DEFAULT_DPI);
}

void SVGNode::setMarginInPixels(const double marginX, const double marginY) {
    setMargin(marginX / SVG_DEFAULT_DPI, marginY / SVG_DEFAULT_DPI);
}

void SVGNode::enableDebug() {
    _showTextBoxes = true;
}

void SVGNode::adjustNodeSize() {
    auto shape = NODE_SHAPE_CIRCLE;
    const auto it = _attributes.find(DOT_ATTR_KEY_SHAPE);
    if (it != _attributes.end()) {
        shape = string_view(it->second);
    }
    if (shape == NODE_SHAPE_CIRCLE) {
        adjustNodeSizeCircle();
    }
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDraws() {
    auto shape = NODE_SHAPE_CIRCLE;
    const auto it = _attributes.find(DOT_ATTR_KEY_SHAPE);
    if (it != _attributes.end()) {
        shape = string_view(it->second);
    }
    if (shape == NODE_SHAPE_CIRCLE) {
        return produceSVGDrawsCircle();
    }
    return {};
}

pair<double, double> SVGNode::computeTextSize() {
    if (_precomputedTextWidth > 0 && _precomputedTextHeight > 0) {
        return {_precomputedTextWidth, _precomputedTextHeight};
    }
    const SVGTextSize textSize;
    const auto label = getAttribute(DOT_ATTR_KEY_LABEL);
    setAttributeIfNotExist(DOT_ATTR_KEY_FONT_NAME, "Serif");
    setAttributeIfNotExist(DOT_ATTR_KEY_FONT_SIZE, "16");
    const double fontSize = stod(getAttribute(DOT_ATTR_KEY_FONT_SIZE));
    const string fontFamily = getAttribute(DOT_ATTR_KEY_FONT_NAME);
    auto [width, height] = textSize.computeTextSize(label, fontSize, fontFamily);
    if (width == 0.0) {
        width = fontSize * SVGTextSize::DEFAULT_APPROXIMATION_WIDTH_SCALE;
    }
    if (height == 0.0) {
        height = fontSize * SVGTextSize::DEFAULT_APPROXIMATION_HEIGHT_SCALE;
    }
    return {width, height};
}

pair<double, double> SVGNode::computeMarginInPixels() {
    setAttributeIfNotExist(DOT_ATTR_KEY_MARGIN, "0.11,0.055");
    const auto margin = getAttribute(DOT_ATTR_KEY_MARGIN);
    return AttributeUtils::parseMarginToPixels(margin);
}

bool SVGNode::isFixedSize() const {
    return AttributeUtils::parseBool(getAttribute(DOT_ATTR_KEY_FIXED_SIZE));
}

void SVGNode::adjustNodeSizeCircle() {
    const auto [textWidth, textHeight] = computeTextSize();
    const auto [marginX, marginY] = computeMarginInPixels();
    const auto diameter = GeometryUtils::distance(textWidth + marginX * 2, textHeight + marginY * 2);
    const auto diameterStr = format("{}", diameter);
    if (isFixedSize()) {
        setAttributeIfNotExist(DOT_ATTR_KEY_WIDTH, diameterStr);
        setAttributeIfNotExist(DOT_ATTR_KEY_HEIGHT, diameterStr);
    } else {
        setAttribute(DOT_ATTR_KEY_WIDTH, diameterStr);
        setAttribute(DOT_ATTR_KEY_HEIGHT, diameterStr);
    }
}

void SVGNode::appendSVGDrawsLabel(vector<unique_ptr<SVGDraw>>& svgDraws) {
    if (_showTextBoxes) {
        const auto [textWidth, textHeight] = computeTextSize();
        const auto [marginX, marginY] = computeMarginInPixels();
        auto textRect = make_unique<SVGDrawRect>(_cx, _cy, textWidth, textHeight);
        textRect->setFill("none");
        textRect->setStroke("blue");
        svgDraws.emplace_back(std::move(textRect));
        auto marginRect = make_unique<SVGDrawRect>(_cx, _cy, textWidth + marginX * 2, textHeight + marginY * 2);
        marginRect->setFill("none");
        marginRect->setStroke("red");
        svgDraws.emplace_back(std::move(marginRect));
    }
    if (const auto label = getAttribute(DOT_ATTR_KEY_LABEL); !label.empty()) {
        svgDraws.emplace_back(make_unique<SVGDrawText>(_cx, _cy, label));
    }
}

vector<unique_ptr<SVGDraw>> SVGNode::produceSVGDrawsCircle() {
    const double width = stod(getAttribute(DOT_ATTR_KEY_WIDTH));
    const double height = stod(getAttribute(DOT_ATTR_KEY_WIDTH));
    vector<unique_ptr<SVGDraw>> svgDraws;
    appendSVGDrawsLabel(svgDraws);
    auto circle = make_unique<SVGDrawCircle>(_cx, _cy, max(width, height) / 2.0);
    circle->setFill("none");
    circle->setStroke("black");
    svgDraws.emplace_back(std::move(circle));
    return svgDraws;
}
