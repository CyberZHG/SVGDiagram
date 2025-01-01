import SVGDiagramWASMModule from './wasm/SVGDiagramWASM.js';

const SVGDiagramWASM = await SVGDiagramWASMModule();
const SVGDiagram = SVGDiagramWASM.SVGDiagram;

export { SVGDiagram };
