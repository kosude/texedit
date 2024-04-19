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
        return new Successes.ResourceResponse(preload[0], preload[1]);
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
export async function getResourceCurPDF(): Promise<Response> {
    let pdf = Bun.env["CURPDF"];
    if (!pdf) {
        return new Errors.InternalServerError("CURPDF environment variable is not set");
    }
    return await getResource(pdf);
}
