#include "xml_element.h"

#include <format>
using namespace std;
using namespace svg_diagram;

XMLElement::XMLElement(const string& tag) {
    _tag = tag;
}

XMLElement::XMLElement(const string& tag, const string& content) {
    _tag = tag;
    _content = content;
}

XMLElement::XMLElement(const string& tag, const AttributesType& attributes) {
    _tag = tag;
    addAttributes(attributes);
}

XMLElement::XMLElement(const string& tag, const AttributesType& attributes, const ChildType &child) {
    _tag = tag;
    addAttributes(attributes);
    addChild(child);
}

XMLElement::XMLElement(const string& tag, const AttributesType& attributes, const ChildrenType& children) {
    _tag = tag;
    addAttributes(attributes);
    addChildren(children);
}

XMLElement::XMLElement(const string& tag, const AttributesType& attributes, const string& content) {
    _tag = tag;
    addAttributes(attributes);
    _content = content;
}

void XMLElement::setTag(const string& tag) {
    _tag = tag;
}

void XMLElement::addAttribute(const string& name, const string& value) {
    if (!_attributes.contains(name)) {
        _attributeKeys.push_back(name);
    }
    _attributes.emplace(name, value);
}

void XMLElement::addAttributes(const AttributesType& attributes) {
    for (const auto& [key, value] : attributes) {
        addAttribute(key, value);
    }
}

void XMLElement::addChild(const ChildType& child) {
    _children.emplace_back(child);
}

void XMLElement::addChildren(const ChildrenType& children) {
    for (auto& child : children) {
        addChild(child);
    }
}

void XMLElement::setContent(const string& content) {
    _content = content;
}

string XMLElement::toString(const int indent) const {
    const auto indentStr = string(indent, ' ');
    string s = indentStr + "<" + _tag;
    for (const auto& [key, value] : _attributes) {
        s += format(R"( {}="{}")", key, escapeAttributeValue(value));
    }
    if (_content.empty() && _children.empty()) {
        s += "/>\n";
    } else {
        s += ">";
        if (!_children.empty()) {
            s += "\n";
            for (const auto& child : _children) {
                s += child->toString(indent + 2);
            }
            s += indentStr;
        }
        s += _content;
        s += "</" + _tag + ">\n";
    }
    return s;
}

std::string XMLElement::toString() const {
    return toString(0);
}

string XMLElement::escapeAttributeValue(const string& value) {
    string escapedValue;
    for (const auto ch : value) {
        if (ch == '"') {
            escapedValue += "&quot;";
        } else {
            escapedValue += ch;
        }
    }
    return escapedValue;
}

XMLElementComment::XMLElementComment(const string& content) {
    _content = content;
}

string XMLElementComment::toString(const int indent) const {
    string escapedComment;
    for (int i = 0; i < _content.length(); ++i) {
        if (i + 1 < _content.length() && _content[i] == '-' && _content[i + 1] == '-') {
            escapedComment += "‑‑";
            ++i;
        } else {
            escapedComment += _content[i];
        }
    }
    const auto indentStr = string(indent, ' ');
    return indentStr + format("<!-- {} -->\n", escapedComment);
}

std::string XMLElementComment::toString() const {
    return toString(0);
}
