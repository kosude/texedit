/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

import fs from "fs/promises";
import path from "path";

var cachedResources = {};

var loadError;

const basePath = path.join(import.meta.dirname, "..");

export async function loadResource(filename, cache = true) {
    var cont;

    if (cache && (filename in cachedResources)) {
        return cachedResources[filename];
    }

    try {
        cont = (await fs.readFile(`${basePath}/${filename}`));
    } catch (err) {
        loadError = err;
        return undefined;
    }

    if (cache) {
        cachedResources[filename] = cont;
    }

    return cont;
}

export function getLastLoadError() {
    return loadError;
}
