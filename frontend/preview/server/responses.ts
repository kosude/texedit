/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

export class ResourceNotFoundError extends Response {
    constructor() {
        super("404 Resource not found",
            {
                status: 404
            });
    }
}

export class ResourceResponse extends Response {
    constructor(contents: ArrayBuffer, type: string) {
        super(contents,
            {
                status: 200,
                headers: { "Content-Type": type }
            });
    }
}
