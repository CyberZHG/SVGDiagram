#include "svg_diagram.h"
#include "../test_utils.h"

#include <format>
#include <cmath>
#include <numbers>
#include <gtest/gtest.h>
using namespace std;
using namespace svg_diagram;

TEST(TestSVGNodePolygon, DefaultSquare) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("polygon");
    node->setShape(SVGNode::SHAPE_POLYGON);
    node->setPrecomputedTextSize(58.8, 14);
    node->setLabel("polygon");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, Triangle) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("triangle");
    node->setShape(SVGNode::SHAPE_POLYGON);
    node->setSides(2);
    node->setPrecomputedTextSize(67.2, 14);
    node->setLabel("triangle");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, Pentagon) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("pentagon");
    node->setShape(SVGNode::SHAPE_POLYGON);
    node->setSides(5);
    node->setPrecomputedTextSize(67.2, 14);
    node->setLabel("pentagon");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, Hexagon) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("hexagon");
    node->setShape(SVGNode::SHAPE_POLYGON);
    node->setSides(6);
    node->setPrecomputedTextSize(58.8, 14);
    node->setLabel("hexagon");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, SkewPositive) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("skew");
    node->setShape(SVGNode::SHAPE_POLYGON);
    node->setSides(4);
    node->setSkew(0.5);
    node->setPrecomputedTextSize(67.2, 14);
    node->setLabel("skew=0.5");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, SkewNegative) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("skew");
    node->setShape(SVGNode::SHAPE_POLYGON);
    node->setSides(4);
    node->setSkew(-0.5);
    node->setPrecomputedTextSize(75.6, 14);
    node->setLabel("skew=-0.5");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, DistortionPositive) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("distortion");
    node->setShape(SVGNode::SHAPE_POLYGON);
    node->setSides(4);
    node->setDistortion(0.5);
    node->setPrecomputedTextSize(67.2, 14);
    node->setLabel("dist=0.5");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, DistortionNegative) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("distortion");
    node->setShape(SVGNode::SHAPE_POLYGON);
    node->setSides(4);
    node->setDistortion(-0.5);
    node->setPrecomputedTextSize(75.6, 14);
    node->setLabel("dist=-0.5");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, SkewAndDistortion) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("combined");
    node->setShape(SVGNode::SHAPE_POLYGON);
    node->setSides(4);
    node->setSkew(0.3);
    node->setDistortion(0.3);
    node->setPrecomputedTextSize(67.2, 14);
    node->setLabel("combined");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, PolygonConnections) {
    SVGDiagram diagram;
    const auto& central = diagram.addNode("c");
    central->setCenter(0.0, 0.0);
    central->setShape(SVGNode::SHAPE_POLYGON);
    central->setSides(6);
    central->setPrecomputedTextSize(50.4, 14);
    central->setLabel("Center");

    for (int i = 0; i < 8; ++i) {
        const auto nodeName = format("n_{}", i);
        const auto& node = diagram.addNode(nodeName);
        const double angle = i * numbers::pi / 4.0;
        node->setCenter(120.0 * cos(angle), 120.0 * sin(angle));
        node->setShape(SVGNode::SHAPE_POLYGON);
        node->setSides(3 + i);
        node->setPrecomputedTextSize(8.4, 14);
        node->setLabel(format("{}", i));

        const auto& edge = diagram.addEdge("c", nodeName);
        edge->setArrowHead();
    }

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, PolygonStyles) {
    SVGDiagram diagram;
    const auto node1 = diagram.addNode("A");
    node1->setShape(SVGNode::SHAPE_POLYGON);
    node1->setSides(5);
    node1->setPrecomputedTextSize(42, 14);
    node1->setLabel("solid");
    node1->setColor("blue");
    node1->setFillColor("lightblue");

    const auto node2 = diagram.addNode("B");
    node2->setCenter(120, 0);
    node2->setShape(SVGNode::SHAPE_POLYGON);
    node2->setSides(5);
    node2->setPrecomputedTextSize(50.4, 14);
    node2->setLabel("dashed");
    node2->appendStyleDashed();
    node2->setColor("red");

    const auto node3 = diagram.addNode("C");
    node3->setCenter(240, 0);
    node3->setShape(SVGNode::SHAPE_POLYGON);
    node3->setSides(5);
    node3->setPrecomputedTextSize(50.4, 14);
    node3->setLabel("dotted");
    node3->appendStyleDotted();
    node3->setColor("green");

    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, ShapeTriangle) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("triangle");
    node->setShape(SVGNode::SHAPE_TRIANGLE);
    node->setPrecomputedTextSize(58.8, 14);
    node->setLabel("triangle");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, ShapePentagon) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("pentagon");
    node->setShape(SVGNode::SHAPE_PENTAGON);
    node->setPrecomputedTextSize(67.2, 14);
    node->setLabel("pentagon");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, ShapeHexagon) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("hexagon");
    node->setShape(SVGNode::SHAPE_HEXAGON);
    node->setPrecomputedTextSize(58.8, 14);
    node->setLabel("hexagon");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, ShapeSeptagon) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("septagon");
    node->setShape(SVGNode::SHAPE_SEPTAGON);
    node->setPrecomputedTextSize(67.2, 14);
    node->setLabel("septagon");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, ShapeOctagon) {
    SVGDiagram diagram;
    diagram.enableDebug();
    const auto node = diagram.addNode("octagon");
    node->setShape(SVGNode::SHAPE_OCTAGON);
    node->setPrecomputedTextSize(58.8, 14);
    node->setLabel("octagon");
    const auto svg = diagram.render();
    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    compareSVGWithExpectedFile(svg, info->test_suite_name(), info->name());
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}

TEST(TestSVGNodePolygon, ShapeConnections) {
    SVGDiagram diagram;
    const auto& central = diagram.addNode("c");
    central->setCenter(0.0, 0.0);
    central->setShape(SVGNode::SHAPE_HEXAGON);
    central->setPrecomputedTextSize(50.4, 14);
    central->setLabel("Center");

    const auto shapes = vector{
        SVGNode::SHAPE_TRIANGLE,
        SVGNode::SHAPE_POLYGON,
        SVGNode::SHAPE_PENTAGON,
        SVGNode::SHAPE_HEXAGON,
        SVGNode::SHAPE_SEPTAGON,
        SVGNode::SHAPE_OCTAGON,
    };

    for (int i = 0; i < static_cast<int>(shapes.size()); ++i) {
        const auto nodeName = format("n_{}", i);
        const auto& node = diagram.addNode(nodeName);
        const double angle = i * numbers::pi / 3.0;
        node->setCenter(120.0 * cos(angle), 120.0 * sin(angle));
        node->setShape(shapes[i]);
        if (shapes[i] == SVGNode::SHAPE_POLYGON) {
            node->setSides(4);
        }
        node->setPrecomputedTextSize(8.4, 14);
        node->setLabel(format("{}", i));

        const auto& edge = diagram.addEdge("c", nodeName);
        edge->setArrowHead();
    }

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
    diagram.render(format("{}_{}.svg", info->test_suite_name(), info->name()));
}
