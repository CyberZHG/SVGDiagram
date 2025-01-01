#!/usr/bin/env bash

emcmake cmake .. -B wasm -DSVG_DIAGRAM_BIND_ES=ON
(cd wasm && emmake make SVGDiagramWASM)
