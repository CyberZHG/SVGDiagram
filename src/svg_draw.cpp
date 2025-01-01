#include "svg_draw.h"
#include "svg_text_size.h"

#include <format>
#include <regex>
#include <sstream>
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

string SVGDraw::renderWithIndent(const int indent) const {
    auto svg = render();
    istringstream iss(svg);
    ostringstream oss;
    string line;
    string prefix(indent, ' ');
    while (getline(iss, line)) {
        oss << prefix << line << "\n";
    }
    return oss.str();
}

string SVGDraw::singletonName() const {
    return "";
}

SVGDrawComment::SVGDrawComment(const string& comment) {
    this->comment = comment;
}

string SVGDrawComment::render() const {
    string escapedComment;
    for (int i = 0; i < comment.length(); ++i) {
        if (i + 1 < comment.length() && comment[i] == '-' && comment[i + 1] == '-') {
            escapedComment += "‑‑";
            ++i;
        } else {
            escapedComment += comment[i];
        }
    }
    return format("<!-- {} -->\n", escapedComment);
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

void SVGDrawEntity::setAttribute(const string_view& key, const string& value) {
    _attributes[key] = value;
}

string SVGDrawEntity::renderAttributes() const {
    string svg;
    for (const auto& [key, value] : _attributes) {
        if (!value.empty()) {
            svg += format(R"( {}="{}")", key, value);
        }
    }
    return svg;
}

SVGDrawBoundingBox SVGDrawNode::boundingBox() const {
    const double halfWidth = width / 2.0;
    const double halfHeight = height / 2.0;
    return {cx - halfWidth, cy - halfHeight, cx + halfWidth, cy + halfHeight};
}

SVGDrawText::SVGDrawText() {
    setFont("Serif", 16);
}

SVGDrawText::SVGDrawText(const double x, const double y, const string& text) {
    cx = x;
    cy = y;
    this->text = text;
    setFont("Serif", 16);
}

void SVGDrawText::setFont(const string& fontFamily, double fontSize) {
    setAttribute(SVG_ATTR_KEY_FONT_FAMILY, fontFamily);
    setAttribute(SVG_ATTR_KEY_FONT_SIZE, format("{}", fontSize));
}

string SVGDrawText::render() const {
    auto splitLines = [](const string& s) -> vector<string> {
        regex re("\r\n|\r|\n");
        sregex_token_iterator it(s.begin(), s.end(), re, -1);
        sregex_token_iterator end;
        return {it, end};
    };
    string svg = format(R"(<text x="{}" y="{}" text-anchor="middle" dominant-baseline="central")", cx, cy);
    svg += renderAttributes();
    svg += " >";
    if (const auto lines = splitLines(text); lines.size() == 1) {
        svg += this->text;
    } else {
        svg += "\n";
        for (int i = 0; i < lines.size(); ++i) {
            double dy = SVGTextSize::DEFAULT_APPROXIMATION_HEIGHT_SCALE + SVGTextSize::DEFAULT_APPROXIMATION_LINE_SPACING_SCALE;
            if (i == 0) {
                dy = -(static_cast<double>(lines.size()) - 1) / 2 * dy;
            }
            svg += format(R"(  <tspan x="{}" dy="{}em">{}</tspan>)", cx, dy, lines[i]);
            svg += "\n";
        }
    }
    svg += "</text>\n";
    return svg;
}

SVGDrawBoundingBox SVGDrawText::boundingBox() const {
    const SVGTextSize textSize;
    const auto fontSize = stod(_attributes.at(SVG_ATTR_KEY_FONT_SIZE));
    const auto fontFamily = _attributes.at(SVG_ATTR_KEY_FONT_FAMILY);
    const auto [width, height] = textSize.computeTextSize(text, fontSize, fontFamily);
    return {cx - width / 2.0, cy - height / 2.0, cx + width / 2.0, cy + height / 2.0};
}

SVGDrawCircle::SVGDrawCircle(const double x, const double y, const double radius) {
    cx = x;
    cy = y;
    width = height = radius * 2;
}

string SVGDrawCircle::render() const {
    const double radius = min(width, height) / 2;
    string svg = format(R"(<circle cx="{}" cy="{}" r="{}")", cx, cy, radius);
    svg += renderAttributes();
    svg += " />\n";
    return svg;
}

SVGDrawBoundingBox SVGDrawCircle::boundingBox() const {
    const double radius = min(width, height) / 2;
    return {cx - radius, cy - radius, cx + radius, cy + radius};
}

SVGDrawLine::SVGDrawLine(const double x1, const double y1, const double x2, const double y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

string SVGDrawLine::render() const {
    string svg = format(R"(<line x1="{}" y1="{}" x2="{}" y2="{}")", x1, y1, x2, y2);
    svg += renderAttributes();
    svg += " />\n";
    return svg;
}

SVGDrawBoundingBox SVGDrawLine::boundingBox() const {
    return {x1, y1, x2, y2};
}
