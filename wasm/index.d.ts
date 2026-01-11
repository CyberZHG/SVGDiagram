declare module 'sp-svg-diagram' {

    function _compareSVG(a: string, b: string): boolean
    const NODE_SHAPE_NONE: string
    const NODE_SHAPE_CIRCLE: string
    const NODE_SHAPE_DOUBLE_CIRCLE: string
    const NODE_SHAPE_RECT: string
    const NODE_SHAPE_ELLIPSE: string
    const NODE_SHAPE_RECORD: string
    const EDGE_SPLINES_LINE: string
    const EDGE_SPLINES_SPLINE: string
    const ARROW_SHAPE_NONE: string
    const ARROW_SHAPE_NORMAL: string
    const ARROW_SHAPE_EMPTY: string

    export class SVGItem {
        constructor()
        setID(itemId: string): void
        setLabel(label: string): void
        setFixedSize(width: number, height: number): void
        setTextSize(width: number, height: number): void
        setMargin(x: number, y: number): void
        setColor(color: string): void
        setFillColor(color: string): void
        setFontColor(color: string): void
        setPenWidth(width: number): void
        setFontName(name: string): void
        setFontSize(size: number): void
        setFont(name: string, size: number): void
        setStyle(style: string): void
        appendStyleSolid(): void
        appendStyleDashed(): void
        appendStyleDotted(): void
        setGradientAngle(angle: number): void
        delete(): void
    }

    export class SVGNode extends SVGItem {
        constructor()
        static SHAPE_NONE: string
        static SHAPE_CIRCLE: string
        static SHAPE_DOUBLE_CIRCLE: string
        static SHAPE_RECT: string
        static SHAPE_ELLIPSE: string
        setCenter(cx: number, cy: number): void
        setShape(shape: string): void
    }

    export class SVGEdge extends SVGItem {
        constructor()
        static SPLINES_LINE: string
        static SPLINES_SPLINE: string
        static ARROW_NONE: string
        static ARROW_NORMAL: string
        static ARROW_EMPTY: string
        setConnection(nodeFromId: string, nodeToId: string): void
        setSplines(splines: string): void
        setFieldFrom(fieldId: string): void
        setFieldTo(fieldId: string): void
        addConnectionPoint(x: number, y: number): void
        setArrowHead(arrow?: string): void
        setArrowTail(arrow?: string): void
        _setArrowHead(arrow: string): void
        _setArrowTail(arrow: string): void
    }

    export class SVGGraph extends SVGItem {
        constructor()
        defaultNodeAttributes(): SVGNode
        defaultEdgeAttributes(): SVGEdge
        addNode(nodeId: string): SVGNode
        addEdge(edgeId: string): SVGEdge
        addSubgraph(graphId: string): SVGGraph
    }

    export class SVGDiagram {
        constructor()
        defaultNodeAttributes(): SVGNode
        defaultEdgeAttributes(): SVGEdge
        setBackgroundColor(color: string): void
        setFixedViewBox(x: number, y: number, width: number, height: number): void
        setRotation(angle: number): void
        addNode(nodeId: string): SVGNode
        addEdge(edgeId: string): SVGEdge
        addSelfLoop(nodeID: string, dir: number, height: number, angle: number): SVGEdge
        addSelfLoopToLeft(nodeID: string, height: number, angle: number): SVGEdge
        addSelfLoopToRight(nodeID: string, height: number, angle: number): SVGEdge
        addSelfLoopToTop(nodeID: string, height: number, angle: number): SVGEdge
        addSelfLoopToBottom(nodeID: string, height: number, angle: number): SVGEdge
        addSubgraph(graphId: string): SVGGraph
        render(): string
    }

    export function createSVGNode(nodeId: string): SVGNode
    export function createSVGEdge(edgeId: string): SVGEdge
    export function createSVGGraph(graphId: string): SVGGraph
}