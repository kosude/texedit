/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

import { getPreloadedResource } from "./preloaded";
import { Errors, Successes } from "./responses";

// Route: /
export async function index(): Promise<Response> {
    return await getResource("index.html");
}

// Route: /*
export async function getResource(filename: string): Promise<Response> {
    const file = Bun.file(filename);

    // check if the file was preloaded at server init.
    let preload = getPreloadedResource(filename);
    if (preload) {
        return new Successes.ResourceResponse(preload.content, preload.type);
    }

    // if the resource wasn't found in the preloaded cache, then we assert that the file exists on disk and return its contents
    if (!await file.exists()) {
        return new Errors.ResourceNotFoundError();
    }
    return new Successes.ResourceResponse(
        await file.arrayBuffer(),
        file.type
    );
}

// Route: /curpdf
export async function getResourceCurPDF(pathArg: string | undefined): Promise<Response> {
    if (!pathArg) {
        return new Errors.InternalServerError("No PDF path was specified to the tepdfserver instance");
    }
    return await getResource(pathArg);
}
