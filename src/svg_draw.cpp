#include "svg_draw.h"

#include <format>
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

SVGDraw::SVGDraw(const string& label) : label(label) {
}

string SVGDraw::singletonName() const {
    return "";
}

string SVGDrawComment::render() const {
    string escapedLabel;
    for (const auto ch : label) {
        if (ch == '-') {
            escapedLabel += "‑";
        } else {
            escapedLabel += ch;
        }
    }
    return format("<!-- {} -->\n", escapedLabel);
}

SVGDrawBoundingBox SVGDrawComment::boundingBox() const {
    return {};
}

bool SVGDrawComment::hasEntity() const {
    return false;
}

bool SVGDrawEntity::hasEntity() const {
    return true;
}

SVGDrawBoundingBox SVGDrawNode::boundingBox() const {
    const double halfWidth = width / 2.0;
    const double halfHeight = height / 2.0;
    return {cx - halfWidth, cy - halfHeight, cx + halfWidth, cy + halfHeight};
}

SVGDrawCircle::SVGDrawCircle(const double x, const double y, const double radius) {
    cx = x;
    cy = y;
    width = height = radius * 2;
}

string SVGDrawCircle::render() const {
    const double radius = min(width, height) / 2;
    string svg = format(R"(<circle cx="{}" cy="{}" r="{}" )", cx, cy, radius);
    svg += "/>\n";
    return svg;
}

SVGDrawBoundingBox SVGDrawCircle::boundingBox() const {
    const double radius = min(width, height) / 2;
    return {cx - radius, cy - radius, cx + radius, cy + radius};
}
