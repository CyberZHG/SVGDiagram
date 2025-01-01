#include "attribute_utils.h"

#include <iostream>
#include <algorithm>
using namespace std;
using namespace svg_diagram;

double AttributeUtils::pointToSVGPixel(const double points) {
    return points / POINTS_PER_INCH * SVG_DEFAULT_DPI;
}

double AttributeUtils::inchToSVGPixel(const double inch) {
    return inch * SVG_DEFAULT_DPI;
}

double AttributeUtils::pointToInch(const double points) {
    return points / POINTS_PER_INCH;
}

double AttributeUtils::svgPixelToPoint(const double pixels) {
    return pixels / SVG_DEFAULT_DPI * POINTS_PER_INCH;
}

double AttributeUtils::centimeterToInch(const double centimeters) {
    return centimeters / CENTIMETERS_PER_INCH;
}

bool AttributeUtils::isPartOfDouble(const char ch) {
    return std::isdigit(ch) ||
           ch == '+' || ch == '-' ||
           ch == '.' || ch == 'e' || ch == 'E';
}

double AttributeUtils::parseLengthToInch(const string& s) {
    int numberStart = -1;
    for (int i = 0; i < static_cast<int>(s.length()); ++i) {
        if (isPartOfDouble(s[i])) {
            numberStart = i;
            break;
        }
    }
    if (numberStart == -1) {
        cerr << "[AttributeUtils::parseLengthToInch] Unable to parse: " << s << endl;
        return 0.0;
    }
    int numberEnd = static_cast<int>(s.length());
    for (int i = numberStart + 1; i < static_cast<int>(s.length()); ++i) {
        if (!isPartOfDouble(s[i])) {
            numberEnd = i;
            break;
        }
    }
    const double value = stod(s.substr(numberStart, numberEnd - numberStart));
    for (int i = numberEnd; i + 1 < static_cast<int>(s.length()); ++i) {
        if (s[i] == 'i' && s[i + 1] == 'n') {
            return value;
        }
        if (s[i] == 'p' && s[i + 1] == 't') {
            return pointToInch(value);
        }
        if (s[i] == 'c' && s[i + 1] == 'm') {
            return centimeterToInch(value);
        }
    }
    return value;
}

pair<double, double> AttributeUtils::parseMarginToInches(const string& margin) {
    if (const auto pos = margin.find(','); pos != string::npos) {
        const string left  = margin.substr(0, pos);
        const string right = margin.substr(pos + 1);
        return {parseLengthToInch(left), parseLengthToInch(right)};
    }
    double m = parseLengthToInch(margin);
    return {m, m};
}

pair<double, double> AttributeUtils::parseMarginToPixels(const string& margin) {
    const auto [width, height] = parseMarginToInches(margin);
    return {inchToSVGPixel(width), inchToSVGPixel(height)};
}

bool AttributeUtils::parseBool(const string& value) {
    if (value.empty()) {
        return false;
    }
    string lower = value;
    ranges::transform(lower, lower.begin(), [](const unsigned char c) {
        return tolower(c);
    });
    return lower == "true" || lower == "1" || lower == "on" || lower == "yes";
}

AttributeUtils::DCommands AttributeUtils::parseDCommands(const string& d) {
    auto readDouble = [&](const int start) -> pair<int, double> {
        int end = static_cast<int>(d.size());
        for (int i = start + 1; i < static_cast<int>(d.size()); ++i) {
            if (!isPartOfDouble(d[i])) {
                end = i;
                break;
            }
        }
        return {end, stod(d.substr(start, end - start))};
    };
    vector<pair<char, vector<double>>> commands;
    for (int i = 0; i < static_cast<int>(d.size()); ++i) {
        if (d[i] == ' ' || d[i] == ',' || d[i] == '\n' || d[i] == '\r' || d[i] == '\t') {
            continue;
        }
        if (isPartOfDouble(d[i])) {
            auto [next, value] = readDouble(i);
            commands[commands.size() - 1].second.push_back(value);
            i = next - 1;
        } else {
            commands.push_back({d[i], {}});
        }
    }
    return commands;
}

std::vector<std::pair<double, double>> AttributeUtils::computeDPathPoints(const DCommands& commands) {
    std::vector<std::pair<double, double>> points;
    for (const auto& [command, parameters] : commands) {
        switch (command) {
            case 'M':  // Move to absolute
            case 'L':  // Line to absolute
            case 'C':  // Draw a cubic Bézier curve to absolute
            case 'S':  // Draw a smooth cubic Bézier curve to absolute
            case 'Q':  // Draw a quadratic Bézier curve to absolute
            case 'T':  // Draw a smooth quadratic Bézier curve to absolute
                for (int i = 0; i < static_cast<int>(parameters.size()); i += 2) {
                    if (i + 1 < static_cast<int>(parameters.size())) {
                        points.emplace_back(parameters[i], parameters[i + 1]);
                    }
                }
                break;
            case 'm':  // Move to relative
            case 'l':  // Line to relative
            case 'c':  // Draw a cubic Bézier curve to relative
            case 's':  // Draw a smooth cubic Bézier curve to relative
            case 'q':  // Draw a quadratic Bézier curve to relative
            case 't':  // Draw a smooth quadratic Bézier curve to relative
                for (int i = 0; i < static_cast<int>(parameters.size()); i += 2) {
                    if (i + 1 < static_cast<int>(parameters.size())) {
                        const auto& [lastX, lastY] = points[points.size() - 1];
                        points.emplace_back(lastX + parameters[i], lastY + parameters[i + 1]);
                    }
                }
                break;
            case 'H':  // Horizontal line to absolute
                for (const double x : parameters) {
                    const auto lastY = points[points.size() - 1].second;
                    points.emplace_back(x, lastY);
                }
                break;
            case 'h':  // Horizontal line to relative
                for (const double dx : parameters) {
                    const auto& [lastX, lastY] = points[points.size() - 1];
                    points.emplace_back(lastX + dx, lastY);
                }
                break;
            case 'V':  // Vertical line to absolute
                for (const double y : parameters) {
                    const auto lastX = points[points.size() - 1].first;
                    points.emplace_back(lastX, y);
                }
                break;
            case 'v':  // Vertical line to relative
                for (const double dy : parameters) {
                    const auto& [lastX, lastY] = points[points.size() - 1];
                    points.emplace_back(lastX, lastY + dy);
                }
                break;
            case 'A':  // Draw an arc curve to absolute
                for (int i = 5; i < static_cast<int>(parameters.size()); i += 7) {
                    if (i + 1 < static_cast<int>(parameters.size())) {
                        points.emplace_back(parameters[i], parameters[i + 1]);
                    }
                }
                break;
            case 'a':  // Draw an arc curve to relative
                for (int i = 5; i < static_cast<int>(parameters.size()); i += 7) {
                    if (i + 1 < static_cast<int>(parameters.size())) {
                        const auto& [lastX, lastY] = points[points.size() - 1];
                        points.emplace_back(lastX + parameters[i], lastY + parameters[i + 1]);
                    }
                }
                break;
            case 'Z':  // Close the path
            default:
                break;
        }
    }
    return points;
}
