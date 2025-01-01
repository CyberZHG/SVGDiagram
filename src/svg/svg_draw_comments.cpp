#include "svg_draw.h"
#include "svg_text_size.h"
#include "attribute_utils.h"

#include <ranges>
#include <regex>
using namespace std;
using namespace svg_diagram;


SVGDrawComment::SVGDrawComment(const string& comment) {
    this->comment = comment;
}

XMLElement::ChildrenType SVGDrawComment::generateXMLElements() const {
    return {make_shared<XMLElementComment>(comment)};
}

string SVGDrawComment::tag() const {
    return "!--";
}

SVGDrawTitle::SVGDrawTitle(const string& title) {
    this->title = title;
}

XMLElement::ChildrenType SVGDrawTitle::generateXMLElements() const {
    const auto titleElement = make_shared<XMLElement>(tag());
    addAttributesToXMLElement(titleElement);
    titleElement->setContent(title);
    return {titleElement};
}

string SVGDrawTitle::tag() const {
    return "title";
}
