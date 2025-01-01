#include "svg_draw.h"
#include "svg_text_size.h"
#include "constants.h"

#include <format>
#include <ranges>
using namespace std;
using namespace svg_diagram;

void SVGDrawLinearGradient::setRotation(const double angle) {
    setAttribute(SVG_ATTR_KEY_GRADIENT_TRANSFORM, format("rotate({})", angle));
}

string SVGDrawLinearGradient::tag() const {
    return "linearGradient";
}

SVGDrawStop::SVGDrawStop(const double offset, const string& color, const double opacity) {
    setOffset(offset);
    setColor(color);
    setOpacity(opacity);
}

void SVGDrawStop::setOffset(const double offset) {
    setAttribute(SVG_ATTR_KEY_OFFSET, format("{}%", 100.0 * offset));
}

void SVGDrawStop::setColor(const string& color) {
    setAttribute(SVG_ATTR_KEY_STOP_COLOR, color);
}

void SVGDrawStop::setOpacity(const double opacity) {
    if (0.0 <= opacity && opacity < 1.0) {
        setAttribute(SVG_ATTR_KEY_STOP_OPACITY, opacity);
    }
}

string SVGDrawStop::tag() const {
    return "stop";
}

string SVGDrawDefs::tag() const {
    return "defs";
}
