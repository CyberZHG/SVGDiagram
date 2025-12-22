import SVGDiagramWASMModule from './wasm/SVGDiagramWASM.js';

import { writeFile } from 'fs/promises';

const SVGDiagramWASM = await SVGDiagramWASMModule();

/**
 * This function is only for testing.
 *
 * @param {string} expected
 * @param {string} actual
 * @return {boolean} Whether the two SVG strings are equivalent.
 */
const _compareSVG = SVGDiagramWASM._compareSVG;
/**
 * Create an SVGNode.
 *
 * @param {string} nodeID - An unique node ID.
 *
 * @returns {SVGNode} An SVGNode instance.
 */
const createSVGNode = SVGDiagramWASM.createSVGNode;
/**
 * Create an SVGEdge.
 *
 * @param {string} edgeID - An unique edge ID.
 *
 * @returns {SVGEdge} An SVGEdge instance.
 */
const createSVGEdge = SVGDiagramWASM.createSVGEdge;
/**
 * Create an SVGGraph.
 *
 * @param {string} graphID - An unique graph ID.
 *
 * @returns {SVGGraph} An SVGGraph instance.
 */
const createSVGGraph = SVGDiagramWASM.createSVGGraph;
const SVGDiagram = SVGDiagramWASM.SVGDiagram;
const SVGNode = SVGDiagramWASM.SVGNode;
const SVGEdge = SVGDiagramWASM.SVGEdge;
const SVGGraph = SVGDiagramWASM.SVGGraph;

SVGNode.SHAPE_NONE = SVGDiagramWASM.NODE_SHAPE_NONE;
SVGNode.SHAPE_CIRCLE = SVGDiagramWASM.NODE_SHAPE_CIRCLE;
SVGNode.SHAPE_DOUBLE_CIRCLE = SVGDiagramWASM.NODE_SHAPE_DOUBLE_CIRCLE;
SVGNode.SHAPE_RECT = SVGDiagramWASM.NODE_SHAPE_RECT;
SVGNode.SHAPE_ELLIPSE = SVGDiagramWASM.NODE_SHAPE_ELLIPSE;

SVGEdge.SPLINES_LINE = SVGDiagramWASM.EDGE_SPLINES_LINE;
SVGEdge.SPLINES_SPLINE = SVGDiagramWASM.EDGE_SPLINES_SPLINE;

SVGEdge.ARROW_NONE = SVGDiagramWASM.ARROW_SHAPE_NONE;
SVGEdge.ARROW_NORMAL = SVGDiagramWASM.ARROW_SHAPE_NORMAL;
SVGEdge.ARROW_EMPTY = SVGDiagramWASM.ARROW_SHAPE_EMPTY;

/**
 * Set the arrow shape at the end point.
 *
 * @param {string} arrowShape - Arrow shape from SVGEdge.ARROW_*
 */
SVGEdge.prototype.setArrowHead = function (arrowShape = SVGEdge.ARROW_NORMAL) {
    this._setArrowHead(arrowShape);
};
/**
 * Set the arrow shape at the start point.
 *
 * @param {string} arrowShape - Arrow shape from SVGEdge.ARROW_*
 */
SVGEdge.prototype.setArrowTail = function (arrowShape = SVGEdge.ARROW_NORMAL) {
    this._setArrowTail(arrowShape);
};
/**
 * Generate SVG and save to a local file.
 *
 * @param {string} file_path - Output file path.
 */
SVGDiagram.prototype.toSVG = async function(file_path) {
    await writeFile(file_path, this.render());
};

export {
    _compareSVG,
    createSVGNode,
    createSVGEdge,
    createSVGGraph,
    SVGDiagram,
    SVGNode,
    SVGEdge,
    SVGGraph,
};
