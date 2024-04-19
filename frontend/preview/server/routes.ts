/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

import { getPreloadedResource } from "./preloaded";
import { ResourceNotFoundError, ResourceResponse } from "./responses";

// Route: /
export async function index(): Promise<Response> {
    return await getResource("index.html");
}

// Route: /*
export async function getResource(filename: string): Promise<Response> {
    const file = Bun.file(filename);

    let preload = getPreloadedResource(filename);
    if (preload) {
        return new ResourceResponse(preload[0], preload[1]);
    }

    if (!await file.exists()) {
        return new ResourceNotFoundError();
    }

    return new ResourceResponse(
        await file.arrayBuffer(),
        file.type
    );
}
