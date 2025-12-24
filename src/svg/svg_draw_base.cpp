#include "svg_draw.h"
#include "svg_text_size.h"
#include "attribute_utils.h"
#include "constants.h"

#include <format>
#include <ranges>
#include <regex>
#include <algorithm>
using namespace std;
using namespace svg_diagram;

SVGDrawBoundingBox::SVGDrawBoundingBox(double x1, double y1, double x2, double y2) {
    if (x1 > x2) {
        swap(x1, x2);
    }
    if (y1 > y2) {
        swap(y1, y2);
    }
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}

XMLElement::ChildrenType SVGDraw::generateXMLElements() const {
    const auto element = make_shared<XMLElement>(tag());
    addAttributesToXMLElement(element);
    return {element};
}

void SVGDraw::setAttribute(const string_view& key, const string& value) {
    _attributes[key] = value;
}

void SVGDraw::setAttribute(const string_view& key, const double value) {
    setAttribute(key, format("{}", value));
}

void SVGDraw::copyAttributes(const SVGDraw* other) {
    _attributes = other->_attributes;
}

void SVGDraw::setID(const string& id) {
    setAttribute(SVG_ATTR_KEY_ID, id);
}

void SVGDraw::setFill(const string& value) {
    setAttribute(SVG_ATTR_KEY_FILL, value);
}

void SVGDraw::setFillOpacity(const double opacity) {
    setAttribute(SVG_ATTR_KEY_FILL_OPACITY, opacity);
}

void SVGDraw::setStroke(const string& value) {
    setAttribute(SVG_ATTR_KEY_STROKE, value);
}

void SVGDraw::setStrokeWidth(const string& value) {
    setAttribute(SVG_ATTR_KEY_STROKE_WIDTH, value);
}

void SVGDraw::setStrokeWidth(const double value) {
    setStrokeWidth(format("{}", value));
}

void SVGDraw::setStrokeDashArray(const string& value) {
    setAttribute(SVG_ATTR_KEY_STROKE_DASHARRAY, value);
}

void SVGDraw::setStrokeOpacity(const double opacity) {
    setAttribute(SVG_ATTR_KEY_STROKE_OPACITY, opacity);
}

void SVGDraw::addAttributesToXMLElement(const XMLElement::ChildType& element) const {
    auto keys_view = _attributes | std::views::keys;
    std::vector<string> keys(keys_view.begin(), keys_view.end());
    ranges::sort(keys);
    for (const auto& key : keys) {
        if (const auto& value = _attributes.at(key); !value.empty()) {
            element->addAttribute(key, value);
        }
    }
}

bool SVGDrawEntity::hasEntity() const {
    return true;
}

SVGDrawBoundingBox SVGDrawNoEntity::boundingBox() const {
    return {};
}

bool SVGDrawNoEntity::hasEntity() const {
    return false;
}

SVGDrawContainer::SVGDrawContainer(unique_ptr<SVGDraw> draw) {
    this->addChild(std::move(draw));
}

SVGDrawContainer::SVGDrawContainer(vector<unique_ptr<SVGDraw>>& draws) {
    this->addChildren(draws);
}

void SVGDrawContainer::addChild(unique_ptr<SVGDraw> child) {
    children.emplace_back(std::move(child));
}

void SVGDrawContainer::addChildren(vector<unique_ptr<SVGDraw>>& draws) {
    for (auto& child : draws) {
        children.emplace_back(std::move(child));
    }
}

XMLElement::ChildrenType SVGDrawContainer::generateXMLElements() const {
    const auto element = make_shared<XMLElement>(tag());
    addAttributesToXMLElement(element);
    for (const auto& child : children) {
        element->addChildren(child->generateXMLElements());
    }
    return {element};
}
