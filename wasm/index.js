import SVGDiagramWASMModule from './wasm/SVGDiagramWASM.js';

import { writeFile } from 'fs/promises';

const SVGDiagramWASM = await SVGDiagramWASMModule();
const _compareSVG = SVGDiagramWASM._compareSVG;
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

SVGEdge.prototype.setArrowHead = function (arrowShape = SVGEdge.ARROW_NORMAL) {
    this._setArrowHead(arrowShape);
};
SVGEdge.prototype.setArrowTail = function (arrowShape = SVGEdge.ARROW_NORMAL) {
    this._setArrowTail(arrowShape);
};

SVGDiagram.prototype.toSVG = async function(file_path) {
    await writeFile(file_path, this.render());
};

export { _compareSVG, SVGDiagram, SVGNode, SVGEdge, SVGGraph };
