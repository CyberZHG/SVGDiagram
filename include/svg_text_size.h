#ifndef SVGDIAGRAM_TEXT_SIZE_H
#define SVGDIAGRAM_TEXT_SIZE_H
#include <string>

namespace svg_diagram {

    class SVGTextSize final {
    public:
        SVGTextSize() = default;
        ~SVGTextSize() = default;

        static constexpr double DEFAULT_APPROXIMATION_HEIGHT_SCALE = 1.0;
        static constexpr double DEFAULT_APPROXIMATION_WIDTH_SCALE = 0.5;
        static constexpr double DEFAULT_APPROXIMATION_LINE_SPACING_SCALE = 0.2;

        [[nodiscard]] double heightScale() const;
        void setHeightScale(double scale);
        [[nodiscard]] double widthScale() const;
        void setWidthScale(double scale);
        [[nodiscard]] double lineSpacingScale() const;
        void setLineSpacingScale(double scale);

        /** Compute the text size.
         * By default, a simple approximation is used.
         * If PangoCairo is enabled, the text is rendered for precise measurement.
         *
         * @param text Text.
         * @param fontSize Font size in pixels.
         * @param fontName Font family.
         * @return Width and height.
         */
        [[nodiscard]] std::pair<double, double> computeTextSize(const std::string& text, double fontSize, const std::string& fontName = "Serif") const;

        /** Compute the approximate text size
         * based on the number of lines and the maximum number of characters per line.
         *
         * @param text Text.
         * @param fontSize Font size in pixels.
         * @return Width and height.
         */
        [[nodiscard]] std::pair<double, double> computeApproximateTextSize(const std::string& text, double fontSize) const;

    private:
        double _heightScale = DEFAULT_APPROXIMATION_HEIGHT_SCALE;
        double _widthScale = DEFAULT_APPROXIMATION_WIDTH_SCALE;
        double _lineSpacingScale = DEFAULT_APPROXIMATION_LINE_SPACING_SCALE;
#ifdef SVG_DIAGRAM_ENABLE_PANGO_CAIRO
        static std::pair<double, double> computePangoCairoTextSize(const std::string& text, double fontSize, const std::string& fontFamily = "Serif") ;
#endif
    };
}

#endif //SVGDIAGRAM_TEXT_SIZE_H
