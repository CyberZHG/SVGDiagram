#include "svg_nodes.h"

#include <format>
#include <cmath>

#include "attribute_utils.h"
#include "svg_text_size.h"
#include "geometry_utils.h"
using namespace std;
using namespace svg_diagram;

const unordered_map<string_view, string>& SVGItem::attributes() const {
    return _attributes;
}

void SVGItem::setAttribute(const string_view& key, const string& value) {
    _attributes[key] = value;
}

void SVGItem::setAttribute(const string_view& key, const double value) {
    _attributes[key] = format("{}", value);
}

void SVGItem::setAttributeIfNotExist(const string_view& key, const string& value) {
    if (!_attributes.contains(key)) {
        _attributes[key] = value;
    }
}

void SVGItem::setDoubleAttributeIfNotExist(const string_view& key, const double value) {
    setAttributeIfNotExist(key, format("{}", value));
}

const string& SVGItem::getAttribute(const string_view& key) const {
    static const string EMPTY_STRING;
    if (const auto it = _attributes.find(key); it != _attributes.end()) {
        return it->second;
    }
    return EMPTY_STRING;
}

void SVGItem::setPrecomputedTextSize(const double width, const double height) {
    _precomputedTextWidth = width;
    _precomputedTextHeight = height;
}

pair<double, double> SVGItem::precomputedTextSize() const {
    return {_precomputedTextWidth, _precomputedTextHeight};
}

void SVGItem::setPrecomputedTextSize(const string& text, const double width, const double height) {
    _precomputedTextSizes[text] = {width, height};
}

const string& SVGItem::id() const {
    const auto it = _attributes.find(ATTR_KEY_ID);
    if (it == _attributes.end()) {
        throw runtime_error("Attribute 'ID' not found");
    }
    return it->second;
}

void SVGItem::setID(const string& id) {
    setAttribute(ATTR_KEY_ID, id);
}

void SVGItem::setLabel(const string& label) {
    setAttribute(ATTR_KEY_LABEL, label);
}

double SVGItem::width() const {
    return AttributeUtils::inchToPoint(stod(getAttribute(ATTR_KEY_WIDTH)));
}

void SVGItem::setWidth(const double width) {
    setAttribute(ATTR_KEY_WIDTH, AttributeUtils::pointToInch(width));
}

double SVGItem::height() const {
    return AttributeUtils::inchToPoint(stod(getAttribute(ATTR_KEY_HEIGHT)));
}

void SVGItem::setHeight(const double height) {
    setAttribute(ATTR_KEY_HEIGHT, AttributeUtils::pointToInch(height));
}

void SVGItem::setSize(const double width, const double height) {
    setWidth(width);
    setHeight(height);
}

void SVGItem::setFixedSize(const double width, const double height) {
    setSize(width, height);
    setAttribute(ATTR_KEY_FIXED_SIZE, "ON");
}

pair<double, double> SVGItem::margin() const {
    return AttributeUtils::parseMargin(getAttribute(ATTR_KEY_MARGIN));
}

void SVGItem::setMargin(const string& value) {
    setAttribute(ATTR_KEY_MARGIN, value);
}

void SVGItem::setMargin(const double margin) {
    setMargin(format("{}", AttributeUtils::pointToInch(margin)));
}

void SVGItem::setMargin(const double marginX, const double marginY) {
    setMargin(format("{},{}", AttributeUtils::pointToInch(marginX), AttributeUtils::pointToInch(marginY)));
}

string SVGItem::color() const {
    return getAttribute(ATTR_KEY_COLOR);
}

void SVGItem::setColor(const string& color) {
    setAttribute(ATTR_KEY_COLOR, color);
}

string SVGItem::fillColor() const {
    return getAttribute(ATTR_KEY_FILL_COLOR);
}

void SVGItem::setFillColor(const string& color) {
    setAttribute(ATTR_KEY_FILL_COLOR, color);
}

string SVGItem::fontColor() const {
    return getAttribute(ATTR_KEY_FONT_COLOR);
}

void SVGItem::setFontColor(const string& color) {
    setAttribute(ATTR_KEY_FONT_COLOR, color);
}

void SVGItem::setPenWidth(const double width) {
    setAttribute(ATTR_KEY_PEN_WIDTH, width);
}

double SVGItem::penWidth() const {
    if (color() == "none") {
        return 0.0;
    }
    if (const auto value = getAttribute(ATTR_KEY_PEN_WIDTH); !value.empty()) {
        const auto width = stod(value);
        if (fabs(width - 1.0) < GeometryUtils::EPSILON) {
            return 1.0;
        }
        return width;
    }
    return 1.0;
}

void SVGItem::setFontName(const string& fontName) {
    setAttribute(ATTR_KEY_FONT_NAME, fontName);
}

void SVGItem::setFontSize(const double fontSize) {
    setAttribute(ATTR_KEY_FONT_SIZE, fontSize);
}

void SVGItem::setFont(const string& fontName, const double fontSize) {
    setFontName(fontName);
    setFontSize(fontSize);
}

void SVGItem::setStyle(const string& style) {
    setAttribute(ATTR_KEY_STYLE, style);
}

void SVGItem::appendStyle(const string& newStyle) {
    auto style = getAttribute(ATTR_KEY_STYLE);
    if (style.empty()) {
        style = string(ATTR_KEY_STYLE);
    }
    if (!style.empty()) {
        style += ',';
    }
    style += newStyle;
    setStyle(style);
}

void SVGItem::appendStyleSolid() {
    appendStyle(string(ATTR_STYLE_SOLID));
}

void SVGItem::appendStyleDashed() {
    appendStyle(string(ATTR_STYLE_DASHED));
}

void SVGItem::appendStyleDotted() {
    appendStyle(string(ATTR_STYLE_DOTTED));
}

AttributeParsedStyle SVGItem::style() const {
    return AttributeUtils::parseStyle(getAttribute(ATTR_KEY_STYLE));
}

void SVGItem::setGradientAngle(const double angle) {
    setAttribute(ATTR_KEY_GRADIENT_ANGLE, angle);
}

double SVGItem::gradientAngle() const {
    if (const auto it = _attributes.find(ATTR_KEY_GRADIENT_ANGLE); it != _attributes.end()) {
        return stod(it->second);
    }
    return 0.0;
}

void SVGItem::appendSVGDrawsLabelWithLocation(vector<unique_ptr<SVGDraw>>& svgDraws, const double cx, const double cy) {
    appendSVGDrawsLabelWithLocation(svgDraws, getAttribute(ATTR_KEY_LABEL), cx, cy);
}

void SVGItem::appendSVGDrawsLabelWithLocation(vector<unique_ptr<SVGDraw>>& svgDraws, const string& label, double cx, double cy, double textWidth, double textHeight) {
    if (textWidth == 0.0 || textHeight == 0.0) {
        const auto [width, height] = computeTextSize(label);
        textWidth = width;
        textHeight = height;
    }
    if (enabledDebug()) {
        const auto [marginX, marginY] = computeMargin();
        auto textRect = make_unique<SVGDrawRect>(cx, cy, textWidth, textHeight);
        textRect->setFill("none");
        textRect->setStroke("blue");
        svgDraws.emplace_back(std::move(textRect));
        auto marginRect = make_unique<SVGDrawRect>(cx, cy, textWidth + marginX * 2, textHeight + marginY * 2);
        marginRect->setFill("none");
        marginRect->setStroke("red");
        svgDraws.emplace_back(std::move(marginRect));
    }
    if (!label.empty()) {
        auto draw = make_unique<SVGDrawText>(cx, cy, textWidth, textHeight, label);
        if (const auto& color = fontColor(); color != "black") {
            draw->setFill(color);
        }
        const string fontFamily = getAttribute(ATTR_KEY_FONT_NAME);
        const double fontSize = stod(getAttribute(ATTR_KEY_FONT_SIZE));
        draw->setFont(fontFamily, fontSize);
        svgDraws.emplace_back(std::move(draw));
    }
}

pair<double, double> SVGItem::computeTextSize() {
    if (_precomputedTextWidth > 0 && _precomputedTextHeight > 0) {
        return {_precomputedTextWidth, _precomputedTextHeight};
    }
    const auto label = getAttribute(ATTR_KEY_LABEL);
    const auto [width, height] = computeTextSize(label);
    setPrecomputedTextSize(width, height);
    _precomputedTextSizes[label] = {width, height};
    return {width, height};
}

pair<double, double> SVGItem::computeTextSize(const string& label) {
    if (const auto it = _precomputedTextSizes.find(label); it != _precomputedTextSizes.end()) {
        return it->second;
    }
    if (label == getAttribute(ATTR_KEY_LABEL) && _precomputedTextWidth > 0 && _precomputedTextHeight > 0) {
        _precomputedTextSizes[label] = {_precomputedTextWidth, _precomputedTextHeight};
        return precomputedTextSize();
    }
    const SVGTextSize textSize;
    const double fontSize = stod(getAttribute(ATTR_KEY_FONT_SIZE));
    const string fontFamily = getAttribute(ATTR_KEY_FONT_NAME);
    auto [width, height] = textSize.computeTextSize(label, fontSize, fontFamily);
    if (width == 0.0) {
        width = fontSize * SVGTextSize::DEFAULT_APPROXIMATION_WIDTH_SCALE;
    }
    if (height == 0.0) {
        height = fontSize * SVGTextSize::DEFAULT_APPROXIMATION_HEIGHT_SCALE;
    }
    _precomputedTextSizes[label] = {width, height};
    return {width, height};
}

pair<double, double> SVGItem::computeMargin() {
    setAttributeIfNotExist(ATTR_KEY_MARGIN, string(ATTR_DEF_MARGIN_NODE));
    return margin();
}

std::pair<double, double> SVGItem::computeTextSizeWithMargin() {
    const auto [width, height] = computeTextSize();
    const auto [marginX, marginY] = computeMargin();
    return {width + marginX * 2, height + marginY * 2};
}

std::pair<double, double> SVGItem::computeTextSizeWithMargin(const string& label) {
    const auto [width, height] = computeTextSize(label);
    const auto [marginX, marginY] = computeMargin();
    return {width + marginX * 2, height + marginY * 2};
}

void SVGItem::setStrokeStyles(SVGDraw* draw) const {
    if (const auto colorList = AttributeUtils::parseColorList(color()); !colorList.empty()) {
        const auto& color = colorList[0];
        draw->setStroke(color.color);
        if (color.color != SVG_ATTR_COLOR_NONE) {
            if (0.0 <= color.opacity && color.opacity < 1.0) {
                draw->setStrokeOpacity(color.opacity);
            }
            if (const auto strokeWidth = penWidth(); strokeWidth != 1.0) {
                draw->setStrokeWidth(strokeWidth);
            }
        }
    }
    if (const auto parsedStyle = style(); parsedStyle.dashed) {
        draw->setStrokeDashArray("5,2");
    } else if (parsedStyle.dotted) {
        draw->setStrokeDashArray("1,5");
    }
}

void SVGItem::setFillStyles(SVGDraw* draw, vector<unique_ptr<SVGDraw>>& svgDraws) const {
    if (const auto colorList = AttributeUtils::parseColorList(fillColor()); !colorList.empty()) {
        if (colorList.size() == 1) {
            const auto& color = colorList[0];
            draw->setFill(color.color);
            if (color.color != SVG_ATTR_COLOR_NONE) {
                if (0.0 <= color.opacity && color.opacity < 1.0) {
                    draw->setFillOpacity(color.opacity);
                }
            }
        } else if (colorList.size() > 1) {
            vector<unique_ptr<SVGDraw>> stops;
            if (const auto& firstColor = colorList[0]; firstColor.weight < 0.0) {
                // Linear gradient
                const double offset = 1.0 / static_cast<double>(colorList.size() - 1);
                for (int i = 0; i < static_cast<int>(colorList.size()); ++i) {
                    const auto& color = colorList[i];
                    stops.emplace_back(make_unique<SVGDrawStop>(i * offset, color.color, color.opacity));
                }
            } else {
                // Segmented color
                double last = 0.0;
                for (int i = 0; i < static_cast<int>(colorList.size()); ++i) {
                    const auto&[color, opacity, weight] = colorList[i];
                    if (i > 0) {
                        stops.emplace_back(make_unique<SVGDrawStop>(last, color, opacity));
                    }
                    last += weight;
                    if (i + 1 < static_cast<int>(colorList.size())) {
                        stops.emplace_back(make_unique<SVGDrawStop>(last - 1e-6, color, opacity));
                    }
                }
            }
            const auto gradientID = id() + "__fill_color";
            auto linearGradient = make_unique<SVGDrawLinearGradient>(stops);
            linearGradient->setID(gradientID);
            if (const auto angle = gradientAngle(); angle != 0.0) {
                linearGradient->setRotation(-angle);
            }
            auto defs = make_unique<SVGDrawDefs>(std::move(linearGradient));
            svgDraws.emplace_back(std::move(defs));
            draw->setFill(format("url('#{}')", gradientID));
        }
    }
}

SVGItem::SVGItem(const string& id) {
    setID(id);
}

void SVGItem::enableDebug() {
    _enabledDebug = true;
}

bool SVGItem::enabledDebug() const {
    return _enabledDebug;
}

void SVGItem::setParent(SVGGraph* parent) {
    if (_parent != nullptr) {
        _parent->removeChild(this);
    }
    _parent = parent;
}

SVGGraph * SVGItem::parent() const {
    return _parent;
}
