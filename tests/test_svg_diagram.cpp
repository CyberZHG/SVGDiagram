#include "svg_diagram.h"
#include "test_utils.h"

#include <vector>
#include <format>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGDiagram, AddSVGDraws) {
    SVGDiagram diagram;
    diagram.enableDebug();
    auto comments = vector<unique_ptr<SVGDraw>>();
    comments.emplace_back(make_unique<SVGDrawComment>("foo1"));
    comments.emplace_back(make_unique<SVGDrawComment>("bar1"));
    auto group = make_unique<SVGDrawGroup>(comments);
    comments.clear();
    comments.emplace_back(make_unique<SVGDrawComment>("foo2"));
    comments.emplace_back(make_unique<SVGDrawText>());
    diagram.addSVGDraw(std::move(group));
    diagram.addSVGDraw(comments);
    const auto svg = diagram.render();
    const auto expected = R"(<g>
  <!-- foo1 -->
  <!-- bar1 -->
</g>
<!-- foo2 -->
<text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14"/>)";
    compareSVGWithDefaultGraphContent(svg, expected);
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGDiagram, DuplicateNodeId) {
    SVGDiagram diagram;
    auto node = diagram.addNode("foo");
    EXPECT_THROW(diagram.addNode("foo"), runtime_error);
    EXPECT_THROW(diagram.addNode("foo", node), runtime_error);
}

TEST(TestSVGDiagram, DuplicateEdgeId) {
    SVGDiagram diagram;
    auto edge = diagram.addEdge("foo");
    EXPECT_THROW(diagram.addEdge("foo"), runtime_error);
    EXPECT_THROW(diagram.addEdge("foo", edge), runtime_error);
}

TEST(TestSVGDiagram, DuplicateSubgraphId) {
    SVGDiagram diagram;
    auto subgraph = diagram.addSubgraph("foo");
    EXPECT_THROW(diagram.addSubgraph("foo"), runtime_error);
    EXPECT_THROW(diagram.addSubgraph("foo", subgraph), runtime_error);
    EXPECT_NO_THROW(diagram.addSubgraph("bar", subgraph));
}