#include "svg_diagram.h"
#include "../test_utils.h"

#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNode, UndefinedID) {
    const auto node = std::make_shared<SVGNode>();
    EXPECT_THROW(const auto id = node->id(), runtime_error);
}