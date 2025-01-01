#ifndef SVGDIAGRAM_XML_ELEMENT_H
#define SVGDIAGRAM_XML_ELEMENT_H

#include <unordered_map>
#include <vector>
#include <memory>

namespace svg_diagram {

    /** A helper class for generating XML strings.
     *
     * This class is not fault-tolerant and only processes a limited subset of the standard XML format.
     */
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
        void addAttribute(const std::string &name, double value);
        void addAttributes(const AttributesType& attributes);
        void addChild(const ChildType& child);
        void addChildren(const ChildrenType& children);
        [[nodiscard]] const ChildrenType& children() const;
        void setContent(const std::string& content);

        [[nodiscard]] virtual std::string toString(int indent) const;
        [[nodiscard]] virtual std::string toString() const;

        /** Check whether the two XML elements have the same function.
         *
         * NOTE that this is only used for unit testing.
         * During comparison, all numbers found in attribute text are treated as floating-point values.
         * If the absolute difference between them is less than EPSILON, the two numbers are considered equal.
         *
         * @param other Another XML element.
         * @return
         */
        bool operator==(const XMLElement& other) const;

        /** Parse XML from string.
         *
         * NOTE that this is only used for unit testing. It can only parse the output of this class.
         *
         * @param source XML string.
         * @return XML element.
         */
        static ChildrenType parse(const std::string& source);

    protected:
        std::string _tag;
        AttributesType _attributes;
        std::vector<std::string> _attributeKeys;
        ChildrenType _children;
        std::string _content;

        static std::string escapeAttributeValue(const std::string& value);

        static std::pair<ChildrenType, int> parse(const std::string& source, int start);
    };

    class XMLElementComment final : public XMLElement {
    public:
        using XMLElement::XMLElement;
        explicit XMLElementComment(const std::string& content);

        [[nodiscard]] std::string toString(int indent) const override;
        [[nodiscard]] std::string toString() const override;
    };

    inline void PrintTo(const XMLElement& element, std::ostream* os) {
        *os << element.toString();
    }

};

#endif //SVGDIAGRAM_XML_ELEMENT_H