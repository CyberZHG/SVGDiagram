#ifndef SVGDIAGRAM_XML_ELEMENT_H
#define SVGDIAGRAM_XML_ELEMENT_H

#include <unordered_map>
#include <vector>

namespace svg_diagram {

    class XMLElement {
    public:
        XMLElement() = default;
        virtual ~XMLElement() = default;

        using AttributesType = std::unordered_map<std::string, std::string>;
        using ChildType = std::shared_ptr<XMLElement>;
        using ChildrenType = std::vector<ChildType>;

        explicit XMLElement(const std::string& tag);
        XMLElement(const std::string& tag, const std::string& content);
        XMLElement(const std::string& tag, const AttributesType& attributes);
        XMLElement(const std::string& tag, const AttributesType& attributes, const ChildType &child);
        XMLElement(const std::string& tag, const AttributesType& attributes, const ChildrenType& children);
        XMLElement(const std::string& tag, const AttributesType& attributes, const std::string& content);

        void setTag(const std::string& tag);
        void addAttribute(const std::string& name, const std::string& value);
        void addAttributes(const AttributesType& attributes);
        void addChild(const ChildType& child);
        void addChildren(const ChildrenType& children);
        void setContent(const std::string& content);

        [[nodiscard]] virtual std::string toString(int indent) const;
        [[nodiscard]] virtual std::string toString() const;

    protected:
        std::string _tag;
        AttributesType _attributes;
        std::vector<std::string> _attributeKeys;
        ChildrenType _children;
        std::string _content;

        static std::string escapeAttributeValue(const std::string& value) ;
    };

    class XMLElementComment final : public XMLElement {
    public:
        using XMLElement::XMLElement;
        explicit XMLElementComment(const std::string& content);

        [[nodiscard]] std::string toString(int indent) const override;
        [[nodiscard]] std::string toString() const override;
    };

};

#endif //SVGDIAGRAM_XML_ELEMENT_H