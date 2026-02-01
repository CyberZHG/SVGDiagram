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
    const auto expected = R"(<!-- Node: polygon -->
<g class="node" id="polygon">
  <title>polygon</title>
  <ellipse cx="0" cy="0" rx="52.89158723275375" ry="15.556349186104043" fill="none" stroke="green"/>
  <polygon points="37.4,-10.999999999999998 37.4,10.999999999999998 -37.39999999999999,11 -37.400000000000006,-10.999999999999998" fill="none" stroke="black"/>
  <rect x="-29.4" y="-7" width="58.8" height="14" fill="none" stroke="blue"/>
  <rect x="-37.4" y="-11" width="74.8" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">polygon</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: triangle -->
<g class="node" id="triangle">
  <title>triangle</title>
  <ellipse cx="0" cy="0" rx="58.83128419472076" ry="15.556349186104047" fill="none" stroke="green"/>
  <polygon points="3.602377193939652e-15,-15.556349186104047 50.949386649890116,7.778174593052021 -50.9493866498901,7.778174593052029" fill="none" stroke="black"/>
  <rect x="-33.6" y="-7" width="67.2" height="14" fill="none" stroke="blue"/>
  <rect x="-41.6" y="-11" width="83.2" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">triangle</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: pentagon -->
<g class="node" id="pentagon">
  <title>pentagon</title>
  <ellipse cx="0" cy="0" rx="58.83128419472076" ry="15.556349186104047" fill="none" stroke="green"/>
  <polygon points="3.602377193939652e-15,-15.556349186104047 55.951876195401255,-4.807176268937032 34.580161223084126,12.585350861989056 -34.58016122308412,12.585350861989056 -55.951876195401255,-4.80717626893703" fill="none" stroke="black"/>
  <rect x="-33.6" y="-7" width="67.2" height="14" fill="none" stroke="blue"/>
  <rect x="-41.6" y="-11" width="83.2" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">pentagon</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: hexagon -->
<g class="node" id="hexagon">
  <title>hexagon</title>
  <ellipse cx="0" cy="0" rx="43.185800135384" ry="12.701705922171765" fill="none" stroke="green"/>
  <polygon points="21.592900067691996,-11 43.185800135384,-2.82034527336256e-15 21.592900067692014,10.999999999999996 -21.592900067691975,11.000000000000004 -43.185800135384,7.196200896854983e-15 -21.592900067692018,-10.999999999999995" fill="none" stroke="black"/>
  <rect x="-29.4" y="-7" width="58.8" height="14" fill="none" stroke="blue"/>
  <rect x="-37.4" y="-11" width="74.8" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">hexagon</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: skew -->
<g class="node" id="skew">
  <title>skew</title>
  <ellipse cx="0" cy="0" rx="58.83128419472075" ry="15.556349186104043" fill="none" stroke="green"/>
  <polygon points="56.91021393199563,-10.999999999999998 36.11021393199563,10.999999999999998 -56.91021393199563,11 -36.11021393199564,-10.999999999999998" fill="none" stroke="black"/>
  <rect x="-33.6" y="-7" width="67.2" height="14" fill="none" stroke="blue"/>
  <rect x="-41.6" y="-11" width="83.2" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">skew=0.5</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: skew -->
<g class="node" id="skew">
  <title>skew</title>
  <ellipse cx="0" cy="0" rx="64.77098115668774" ry="15.556349186104043" fill="none" stroke="green"/>
  <polygon points="39.75595668474518,-10.999999999999998 62.65595668474517,10.999999999999998 -39.75595668474517,11 -62.655956684745185,-10.999999999999998" fill="none" stroke="black"/>
  <rect x="-37.8" y="-7" width="75.6" height="14" fill="none" stroke="blue"/>
  <rect x="-45.8" y="-11" width="91.6" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">skew=-0.5</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: distortion -->
<g class="node" id="distortion">
  <title>distortion</title>
  <ellipse cx="0" cy="0" rx="58.83128419472075" ry="15.556349186104043" fill="none" stroke="green"/>
  <polygon points="31.802392883315438,-10.999999999999998 61.218034980675824,10.999999999999998 -61.21803498067581,11 -31.802392883315445,-10.999999999999998" fill="none" stroke="black"/>
  <rect x="-33.6" y="-7" width="67.2" height="14" fill="none" stroke="blue"/>
  <rect x="-41.6" y="-11" width="83.2" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">dist=0.5</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: distortion -->
<g class="node" id="distortion">
  <title>distortion</title>
  <ellipse cx="0" cy="0" rx="64.77098115668774" ry="15.556349186104043" fill="none" stroke="green"/>
  <polygon points="67.39870197391711,-10.999999999999998 35.013211395573244,10.999999999999998 -35.013211395573244,11 -67.39870197391711,-10.999999999999998" fill="none" stroke="black"/>
  <rect x="-37.8" y="-7" width="75.6" height="14" fill="none" stroke="blue"/>
  <rect x="-45.8" y="-11" width="91.6" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">dist=-0.5</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: combined -->
<g class="node" id="combined">
  <title>combined</title>
  <ellipse cx="0" cy="0" rx="58.83128419472075" ry="15.556349186104043" fill="none" stroke="green"/>
  <polygon points="45.92882713590478,-10.999999999999998 51.09821239432101,10.999999999999998 -63.578212394321,11 -33.44882713590479,-10.999999999999998" fill="none" stroke="black"/>
  <rect x="-33.6" y="-7" width="67.2" height="14" fill="none" stroke="blue"/>
  <rect x="-41.6" y="-11" width="83.2" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">combined</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: A -->
<g class="node" id="A">
  <title>A</title>
  <polygon points="2.511272563082931e-15,-15.556349186104047 39.00491369390953,-4.807176268937032 24.1063623910923,12.585350861989056 -24.106362391092297,12.585350861989056 -39.00491369390953,-4.80717626893703" fill="lightblue" stroke="blue"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">solid</text>
</g>
<!-- Node: B -->
<g class="node" id="B">
  <title>B</title>
  <polygon points="120,-15.556349186104047 164.65390119440679,-4.807176268937032 147.5976286684229,12.585350861989056 92.40237133157709,12.585350861989056 75.34609880559323,-4.80717626893703" fill="none" stroke="red" stroke-dasharray="5,2"/>
  <text x="120" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">dashed</text>
</g>
<!-- Node: C -->
<g class="node" id="C">
  <title>C</title>
  <polygon points="240,-15.556349186104047 284.6539011944068,-4.807176268937032 267.5976286684229,12.585350861989056 212.4023713315771,12.585350861989056 195.34609880559321,-4.80717626893703" fill="none" stroke="green" stroke-dasharray="1,5"/>
  <text x="240" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">dotted</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: triangle -->
<g class="node" id="triangle">
  <title>triangle</title>
  <ellipse cx="0" cy="0" rx="52.891587232753764" ry="15.556349186104047" fill="none" stroke="green"/>
  <polygon points="3.2386756503207453e-15,-15.556349186104047 45.80545819004544,7.778174593052021 -45.80545819004543,7.778174593052029" fill="none" stroke="black"/>
  <rect x="-29.4" y="-7" width="58.8" height="14" fill="none" stroke="blue"/>
  <rect x="-37.4" y="-11" width="74.8" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">triangle</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: pentagon -->
<g class="node" id="pentagon">
  <title>pentagon</title>
  <ellipse cx="0" cy="0" rx="58.83128419472076" ry="15.556349186104047" fill="none" stroke="green"/>
  <polygon points="3.602377193939652e-15,-15.556349186104047 55.951876195401255,-4.807176268937032 34.580161223084126,12.585350861989056 -34.58016122308412,12.585350861989056 -55.951876195401255,-4.80717626893703" fill="none" stroke="black"/>
  <rect x="-33.6" y="-7" width="67.2" height="14" fill="none" stroke="blue"/>
  <rect x="-41.6" y="-11" width="83.2" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">pentagon</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: hexagon -->
<g class="node" id="hexagon">
  <title>hexagon</title>
  <ellipse cx="0" cy="0" rx="43.185800135384" ry="12.701705922171765" fill="none" stroke="green"/>
  <polygon points="21.592900067691996,-11 43.185800135384,-2.82034527336256e-15 21.592900067692014,10.999999999999996 -21.592900067691975,11.000000000000004 -43.185800135384,7.196200896854983e-15 -21.592900067692018,-10.999999999999995" fill="none" stroke="black"/>
  <rect x="-29.4" y="-7" width="58.8" height="14" fill="none" stroke="blue"/>
  <rect x="-37.4" y="-11" width="74.8" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">hexagon</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: septagon -->
<g class="node" id="septagon">
  <title>septagon</title>
  <ellipse cx="0" cy="0" rx="58.83128419472076" ry="15.556349186104047" fill="none" stroke="green"/>
  <polygon points="3.602377193939652e-15,-15.556349186104047 45.9961501374565,-9.699225071689282 57.35626107093463,3.4616133498424237 25.525937563493144,14.015786314898882 -25.525937563493137,14.015786314898882 -57.35626107093463,3.4616133498424255 -45.99615013745651,-9.69922507168928" fill="none" stroke="black"/>
  <rect x="-33.6" y="-7" width="67.2" height="14" fill="none" stroke="blue"/>
  <rect x="-41.6" y="-11" width="83.2" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">septagon</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
    const auto expected = R"(<!-- Node: octagon -->
<g class="node" id="octagon">
  <title>octagon</title>
  <ellipse cx="0" cy="0" rx="40.48146829093554" ry="11.906314203216334" fill="none" stroke="green"/>
  <polygon points="15.491587232753758,-11 37.400000000000006,-4.556349186104046 37.400000000000006,4.556349186104046 15.491587232753758,11 -15.491587232753755,11 -37.400000000000006,4.556349186104048 -37.400000000000006,-4.556349186104045 -15.49158723275378,-10.999999999999998" fill="none" stroke="black"/>
  <rect x="-29.4" y="-7" width="58.8" height="14" fill="none" stroke="blue"/>
  <rect x="-37.4" y="-11" width="74.8" height="22" fill="none" stroke="red"/>
  <text x="0" y="0" text-anchor="middle" dominant-baseline="central" font-family="Times,serif" font-size="14">octagon</text>
</g>)";
    compareSVGWithDefaultGraphContent(svg, expected);

    const ::testing::TestInfo* info = ::testing::UnitTest::GetInstance()->current_test_info();
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
