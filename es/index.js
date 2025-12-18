import SVGDiagramWASMModule from './wasm/SVGDiagramWASM.js';

const SVGDiagramWASM = await SVGDiagramWASMModule();
const SVGDiagram = SVGDiagramWASM.SVGDiagram;
const SVGNode = SVGDiagramWASM.SVGNode;
const SVGEdge = SVGDiagramWASM.SVGEdge;

SVGNode.SHAPE_NONE = SVGDiagramWASM.NODE_SHAPE_NONE;
SVGNode.SHAPE_CIRCLE = SVGDiagramWASM.NODE_SHAPE_CIRCLE;
SVGNode.SHAPE_DOUBLE_CIRCLE = SVGDiagramWASM.NODE_DOUBLE_CIRCLE;
SVGNode.SHAPE_RECT = SVGDiagramWASM.NODE_SHAPE_RECT;
SVGNode.SHAPE_ELLIPSE = SVGDiagramWASM.NODE_SHAPE_ELLIPSE;

export { SVGDiagram, SVGNode, SVGEdge };
