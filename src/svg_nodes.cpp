#include "svg_nodes.h"
using namespace std;
using namespace svg_diagram;

void SVGNode::setAttribute(const string_view& key, const string& value) {
    _attributes[key] = value;
}

static const string EMPTY_STRING;

const string& SVGNode::getAttribute(const string_view& key) const {
    if (const auto it = _attributes.find(key); it != _attributes.end()) {
        return it->second;
    }
    return EMPTY_STRING;
}
