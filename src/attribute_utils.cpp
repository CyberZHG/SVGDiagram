#include "attribute_utils.h"
using namespace std;
using namespace svg_diagram;

pair<double, double> AttributeUtils::parseMargin(const string& margin) {
    if (const auto pos = margin.find(','); pos != string::npos) {
        const string left  = margin.substr(0, pos);
        const string right = margin.substr(pos + 1);
        return {stod(left), stod(right)};
    }
    double m = stod(margin);
    return {m, m};
}
