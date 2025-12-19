import { _compareSVG } from '../../index.js';
import { strict as assert } from 'assert';
import { readFile } from 'fs/promises';

const REFERENCE_OUTPUTS_FOLDER = "../docs/source/_static/"

async function compareSVG(docFolder, svgName, svg) {
    await readFile(REFERENCE_OUTPUTS_FOLDER + docFolder + "/" + svgName + ".svg")
    .then(function (expected) {
        assert(_compareSVG(svg, expected), expected);
    });
}

export { compareSVG };
