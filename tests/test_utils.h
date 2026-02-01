#ifndef SVGDIAGRAM_TEST_UTILS_H
#define SVGDIAGRAM_TEST_UTILS_H

#include <string>

void compareSVGContent(const std::string& a, const std::string& b);
void compareSVGWithDefaultGraphContent(const std::string& a, const std::string& b);

std::string readExpectedSVG(const std::string& testSuite, const std::string& testName);
void compareSVGWithExpectedFile(const std::string& svg, const std::string& testSuite, const std::string& testName);

#endif //SVGDIAGRAM_TEST_UTILS_H