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
import pdfJs from "pdfjs-dist/build/pdf.mjs"
// @ts-ignore
import pdfJsMap from "pdfjs-dist/build/pdf.mjs.map"
// @ts-ignore
import pdfWorkerJs from "pdfjs-dist/build/pdf.worker.mjs";
// @ts-ignore
import pdfWorkerJsMap from "pdfjs-dist/build/pdf.worker.mjs.map";

// @ts-ignore
import renderJs from "../renderer/render.mjs";

export interface EmbeddedResource {
    content: ArrayBuffer,
    type: string
};

async function pl(f: any): Promise<EmbeddedResource> {
    let file = Bun.file(f);
    return {
        content: await file.arrayBuffer(),
        type: file.type
    };
}

const preloadedResources: Record<string, EmbeddedResource > = {
    "index.html": await pl(indexHtml),

    "style/style.css": await pl(styleCss),

    "pdf.mjs": await pl(pdfJs),
    "pdf.worker.mjs": await pl(pdfWorkerJs),
    "pdf.mjs.map": await pl(pdfJsMap),
    "pdf.worker.mjs.map": await pl(pdfWorkerJsMap),

    "renderer/render.mjs": await pl(renderJs),
};

// Return a tuple containing the content stream and the file's MIME type
export function getPreloadedResource(filename: string): EmbeddedResource | undefined {
    if (filename in preloadedResources) {
        return preloadedResources[filename];
    }

    return undefined;
}
