#include "xml_element.h"
#include "attribute_utils.h"

#include <format>
#include <cmath>
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

void XMLElement::addAttribute(const string& name, const double value) {
    if (!_attributes.contains(name)) {
        _attributeKeys.push_back(name);
    }
    _attributes.emplace(name, format("{}", value));
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

const XMLElement::ChildrenType & XMLElement::children() const {
    return _children;
}

void XMLElement::setContent(const string& content) {
    _content = content;
}

string XMLElement::toString(const int indent) const {
    if (_tag.empty()) {
        string s;
        for (const auto& child : _children) {
            s += child->toString(indent);
        }
        return s;
    }
    const auto indentStr = string(indent, ' ');
    string s = indentStr + "<" + _tag;
    for (const auto& key : _attributeKeys) {
        s += format(R"( {}="{}")", key, escapeAttributeValue(_attributes.at(key)));
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

bool XMLElement::operator==(const XMLElement& other) const {
    constexpr double EPSILON = 1e-6;
    if (_tag != other._tag) {
        return false;
    }
    if (_content != other._content) {
        return false;
    }
    if (_attributes.size() != other._attributes.size()) {
        return false;
    }
    for (const auto& [key, value1] : _attributes) {
        if (!other._attributes.contains(key)) {
            return false;
        }
        const auto& value2 = other._attributes.at(key);
        const size_t n = value1.size(), m = value2.size();
        size_t i = 0, j = 0;
        while (i < n && j < m) {
            try {
                size_t pos1, pos2;
                const double doubleValue1 = stod(value1.substr(i), &pos1);
                const double doubleValue2 = stod(value2.substr(j), &pos2);
                if (fabs(doubleValue1 - doubleValue2) > EPSILON) {
                    return false;
                }
                if ((i == pos1) ^ (j == pos2)) {
                    return false;
                }
                if (i == pos1) {
                    if (value1[i++] != value2[j++]) {
                        return false;
                    }
                } else {
                    i += pos1;
                    j += pos2;
                }
            } catch (...) {
                if (value1[i++] != value2[j++]) {
                    return false;
                }
            }
        }
        if (i != n || j != m) {
            return false;
        }
    }
    if (_children.size() != other._children.size()) {
        return false;
    }
    for (int i = 0; i < static_cast<int>(_children.size()); ++i) {
        if (*_children[i].get() != *other._children[i].get()) {
            return false;
        }
    }
    return true;
}

XMLElement::ChildrenType XMLElement::parse(const string& source) {
    const auto [children, stop] = parse(source, 0);
    return children;
}

std::pair<XMLElement::ChildrenType, int> XMLElement::parse(const std::string &source, const int start) {
    constexpr int STATE_START = 0;
    int state = STATE_START;
    ChildrenType children;
    const int n = static_cast<int>(source.size());
    int i = start;
    while (i < n) {
        constexpr int STATE_TAG = 1;
        constexpr int STATE_FIND_CLOSE = 2;
        constexpr int STATE_ATTRIBUTE = 3;
        constexpr int STATE_CONTENT = 4;
        constexpr int STATE_CLOSE = 5;
        switch (state) {
            case STATE_START: {
                while (i < n && source[i] != '<') {
                    ++i;
                }
                state = STATE_TAG;
                i += 1;
                break;
            }
            case STATE_TAG: {
                if (source[i] == '/') {
                    return {children, i - 1};
                }
                if (source[i] == '!') {
                    i += 4;
                    const int commentStart = i;
                    for (; i + 2 < n; ++i) {
                        if (source[i] == '-' && source[i + 1] == '-' && source[i + 2] == '>') {
                            const auto comment = source.substr(commentStart, i - 1 - commentStart);
                            children.emplace_back(make_shared<XMLElementComment>(comment));
                            i += 3;
                            break;
                        }
                    }
                    state = STATE_START;
                } else {
                    const int tagStart = i;
                    while (i < n && isalpha(source[i])) {
                        ++i;
                    }
                    children.emplace_back(make_shared<XMLElement>(source.substr(tagStart, i - tagStart)));
                    state = STATE_FIND_CLOSE;
                }
                break;
            }
            case STATE_FIND_CLOSE: {
                while (i < n && isspace(source[i])) {
                    ++i;
                }
                if (i < n) {
                    if (source[i] == '>') {
                        state = STATE_CONTENT;
                        i += 1;
                    } else if (source[i] == '/') {
                        state = STATE_START;
                        i += 2;
                    } else {
                        state = STATE_ATTRIBUTE;
                    }
                }
                break;
            }
            case STATE_ATTRIBUTE: {
                const int keyStart = i;
                while (i < n && source[i] != '=') {
                    ++i;
                }
                const auto key = source.substr(keyStart, i - keyStart);
                i += 2;
                if (i < n) {
                    const int valueStart = i;
                    while (i < n && source[i] != '"') {
                        ++i;
                    }
                    const auto value = source.substr(valueStart, i - valueStart);
                    children[children.size() - 1]->addAttribute(key, value);
                    i += 1;
                }
                state = STATE_FIND_CLOSE;
                break;
            }
            case STATE_CONTENT: {
                const int contentStart = i;
                while (i < n && source[i] != '<') {
                    ++i;
                }
                if (i + 1 < n && source[i + 1] != '/') {
                    const auto [subChildren, nextIndex] = parse(source, i);
                    children[children.size() - 1]->addChildren(subChildren);
                    i = nextIndex;
                } else {
                    const auto content = source.substr(contentStart, i - contentStart);
                    children[children.size() - 1]->setContent(content);
                }
                state = STATE_CLOSE;
                break;
            }
            case STATE_CLOSE: {
                while (i < n && source[i] != '>') {
                    ++i;
                }
                i += 1;
                state = STATE_START;
                break;
            }
        }
    }
    return {children, n};
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
    for (int i = 0; i < static_cast<int>(_content.length()); ++i) {
        if (i + 1 < static_cast<int>(_content.length()) && _content[i] == '-' && _content[i + 1] == '-') {
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
