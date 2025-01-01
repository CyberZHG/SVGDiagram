#include "svg_diagram.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDrawComment, DefaultComment) {
    const SVGDiagram diagram;
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
