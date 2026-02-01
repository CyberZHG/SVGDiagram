#include "svg_diagram.h"

#include <format>
#include <vector>
#include <memory>
#include <gtest/gtest.h>

#include "../test_utils.h"
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDrawDefs, LinearGradient) {
    SVGDiagram diagram;
    diagram.clearSVGDraw();
    auto stop1 = make_unique<SVGDrawStop>(0.05, "gold");
    auto stop2 = make_unique<SVGDrawStop>(0.95, "red", 0.8);
    auto stops = vector<unique_ptr<SVGDraw>>();
    stops.emplace_back(std::move(stop1));
    stops.emplace_back(std::move(stop2));
    auto linearGradient = make_unique<SVGDrawLinearGradient>(stops);
    linearGradient->setID("gradient-test");
    linearGradient->setRotation(90);
    auto defs = make_unique<SVGDrawDefs>(std::move(linearGradient));
    diagram.addSVGDraw(std::move(defs));
    auto circle = make_unique<SVGDrawCircle>(5, 5, 4);
    circle->setFill("url('#gradient-test')");
    diagram.addSVGDraw(std::move(circle));
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}