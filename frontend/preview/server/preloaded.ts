/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

// @ts-ignore
import indexHtml from "../index.html";

// @ts-ignore
import styleCss from "../style/style.css";

// @ts-ignore
import pdfJs from "../lib/pdf.js/pdf.mjs";
// @ts-ignore
import pdfWorkerJs from "../lib/pdf.js/pdf.worker.mjs";

async function pl(f: string | URL): Promise<[ArrayBuffer, string]> {
    let file = Bun.file(f);
    return [await file.arrayBuffer(), file.type];
}

const preloadedResources: Record<string, [ArrayBuffer, string]> = {
    "index.html": await pl(indexHtml),
    "lib/pdf.js/pdf.mjs": await pl(pdfJs),
    "lib/pdf.js/pdf.worker.mjs": await pl(pdfWorkerJs),
    "style/style.css": await pl(styleCss),
};

// Return a tuple containing the content stream and the file's MIME type
export function getPreloadedResource(filename: string): [ArrayBuffer, string] | undefined {
    if (filename in preloadedResources) {
        return preloadedResources[filename];
    }

    return undefined;
}
