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

SVGDraw::SVGDraw(const std::string &label) : _label(label) {
}

const string & SVGDraw::label() const {
    return _label;
}

void SVGDraw::setLabel(const string& label) {
    _label = label;
}

std::string SVGDrawComment::render() const {
    string escapedLabel;
    for (const auto ch : label()) {
        if (ch == '-') {
            escapedLabel += "-";
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

bool SVGDrawComment::singleton() const {
    return false;
}
