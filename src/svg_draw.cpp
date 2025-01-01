#include "svg_draw.h"
#include "svg_text_size.h"
#include "attribute_utils.h"

#include <format>
#include <iostream>
#include <ranges>
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

void SVGDraw::setSingletonName(const string& singletonName) {
    _singletonName = singletonName;
}

bool SVGDraw::isDefs() const {
    return false;
}

void SVGDraw::setNumDecimals(const int numDecimals) {
    _numDecimals = numDecimals;
}

string SVGDraw::formatDouble(const double value) const {
    string str = format("{}", value);
    int numDecimals = 0;
    bool start = false;
    for (const auto& ch : str) {
        if (ch == '.') {
            start = true;
        } else if (start) {
            ++numDecimals;
        }
    }
    if (numDecimals <= _numDecimals) {
        return str;
    }
    return format("{:.{}f}", value, _numDecimals);
}

std::string SVGDraw::renderAttributes() const {
    string svg;
    auto keys_view = _attributes | std::views::keys;
    std::vector<string> keys(keys_view.begin(), keys_view.end());
    ranges::sort(keys);
    for (const auto& key : keys) {
        if (const auto& value = _attributes.at(key); !value.empty()) {
            svg += format(R"( {}="{}")", key, value);
        }
    }
    return svg;
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

void SVGDrawEntity::setFill(const string& value) {
    setAttribute(SVG_ATTR_KEY_FILL, value);
}

void SVGDrawEntity::setStroke(const string& value) {
    setAttribute(SVG_ATTR_KEY_STROKE, value);
}

SVGDrawNode::SVGDrawNode(const double cx, const double cy, const double width, const double height) {
    this->cx = cx;
    this->cy = cy;
    this->width = width;
    this->height = height;
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
    string svg = format(R"(<text x="{}" y="{}" text-anchor="middle" dominant-baseline="central")", formatDouble(cx), formatDouble(cy));
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
            svg += format(R"(  <tspan x="{}" dy="{}em">{}</tspan>)", formatDouble(cx), dy, lines[i]);
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
    string svg = format(R"(<circle cx="{}" cy="{}" r="{}")", formatDouble(cx), formatDouble(cy), formatDouble(radius));
    svg += renderAttributes();
    svg += " />\n";
    return svg;
}

SVGDrawBoundingBox SVGDrawCircle::boundingBox() const {
    const double radius = min(width, height) / 2;
    return {cx - radius, cy - radius, cx + radius, cy + radius};
}

std::string SVGDrawRect::render() const {
    const double x = cx - width / 2;
    const double y = cy - height / 2;
    string svg = format(R"(<rect x="{}" y="{}" width="{}" height="{}")", formatDouble(x), formatDouble(y), formatDouble(width), formatDouble(height));
    svg += renderAttributes();
    svg += " />\n";
    return svg;
}

SVGDrawLine::SVGDrawLine(const double x1, const double y1, const double x2, const double y2) {
    this->x1 = x1;
    this->y1 = y1;
    this->x2 = x2;
    this->y2 = y2;
}

string SVGDrawLine::render() const {
    string svg = format(R"(<line x1="{}" y1="{}" x2="{}" y2="{}")", formatDouble(x1), formatDouble(y1), formatDouble(x2), formatDouble(y2));
    svg += renderAttributes();
    svg += " />\n";
    return svg;
}

SVGDrawBoundingBox SVGDrawLine::boundingBox() const {
    return {x1, y1, x2, y2};
}

SVGDrawPath::SVGDrawPath(const string& d) {
    this->d = d;
}

string SVGDrawPath::render() const {
    const auto commands = AttributeUtils::parseDCommands(d);
    string reformat;
    for (int i = 0; i < commands.size(); ++i) {
        const auto& [command, parameters] = commands[i];
        if (i > 0) {
            reformat += ' ';
        }
        reformat += command;
        for (const auto& parameter : parameters) {
            reformat += format(" {}", formatDouble(parameter));
        }
    }
    string svg = format(R"(<path d="{}")", reformat);
    svg += renderAttributes();
    svg += " />\n";
    return svg;
}

SVGDrawBoundingBox SVGDrawPath::boundingBox() const {
    double xMin = 0.0, yMin = 0.0, xMax = 0.0, yMax = 0.0;
    const auto commands = AttributeUtils::parseDCommands(d);
    if (const auto points = AttributeUtils::computeDPathPoints(commands); !points.empty()) {
        xMin = xMax = points[0].first;
        yMin = yMax = points[0].second;
        for (const auto&[x, y] : points) {
            xMin = min(xMin, x);
            yMin = min(yMin, y);
            xMax = max(xMax, x);
            yMax = max(yMax, y);
        }
    }
    return {xMin, yMin, xMax, yMax};
}

bool SVGDrawDefs::isDefs() const {
    return true;
}

bool SVGDrawDefs::hasEntity() const {
    return false;
}

SVGDrawBoundingBox SVGDrawDefs::boundingBox() const {
    return {};
}

void SVGDrawMarker::setShape(const string& shape) {
    _shape = shape;
}

std::string SVGDrawMarker::singletonName() const {
    return format("arrow_type_{}", _shape);
}

string SVGDrawMarker::render() const {
    if (_shape == SHAPE_NORMAL) {
        return renderNormal();
    }
    cerr << "Unknown marker shape: " << _shape << endl;
    return "";
}

string SVGDrawMarker::renderNormal() const {
    string svg = format(R"(<marker id="{}")", singletonName());
    svg += format(R"( markerWidth="{}" markerHeight="{}")", formatDouble(10.0), formatDouble(7.0));
    svg += format(R"( refX="{}" refY="{}" orient="auto-start-reverse")", formatDouble(10.0), formatDouble(3.5));
    svg += renderAttributes();
    svg += ">\n";
    svg += R"(  <polygon points="0 0)";
    svg += format(" {} {}", formatDouble(10.0), formatDouble(3.5));
    svg += format(" 0 {}", formatDouble(7.0));
    svg += R"(" />)" + string("\n");
    svg += "</marker>\n";
    return svg;
}
