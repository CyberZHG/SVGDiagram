#include "svg_draw.h"
#include "svg_text_size.h"
#include "attribute_utils.h"

#include <format>
#include <ranges>
#include <algorithm>
using namespace std;
using namespace svg_diagram;

SVGDrawBoundingBox SVGDrawGroup::boundingBox() const {
    double xMin = 0.0, yMin = 0.0, xMax = 1.0, yMax = 1.0;
    bool first = true;
    for (const auto& child : children) {
        if (child->hasEntity()) {
            const auto [x1, y1, x2, y2] = child->boundingBox();
            if (first) {
                first = false;
                xMin = x1, yMin = y1;
                xMax = x2, yMax = y2;
            } else {
                xMin = min(xMin, x1);
                xMax = max(xMax, x2);
                yMin = min(yMin, y1);
                yMax = max(yMax, y2);
            }
        }
    }
    return {xMin, yMin, xMax, yMax};
}

bool SVGDrawGroup::hasEntity() const {
    for (const auto& child : children) {
        if (child->hasEntity()) {
            return true;
        }
    }
    return false;
}

string SVGDrawGroup::tag() const {
    return "g";
}
