/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

import mime from "mime";

import * as error from "./error.js";
import * as resources from "./resources.js"

// Route: /
export async function index() {
    return await getResource("index.html");
}

function getResourceHelper(contents, mimeType) {
    if (contents === undefined) {
        return error.http404(`Resource not found. ${resources.getLastLoadError()}`);
    }

    return {
        status: 200,
        headers: {
            "Content-Type": mimeType
        },
        content: contents
    };
}

// Route: /*
export async function getResource(filename) {
    var cont = await resources.loadResource(filename);
    return getResourceHelper(cont, mime.getType(filename));
}

// Route: /*.pdf
export async function getUncachedResource(filename) {
    var cont = await resources.loadResource(filename, false);
    return getResourceHelper(cont, mime.getType(filename));
}
