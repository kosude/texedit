/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

export namespace Errors {
    export class ResourceNotFoundError extends Response {
        constructor() {
            super("404 Resource Not Found",
                {
                    status: 404
                });
        }
    }
    export class InternalServerError extends Response {
        constructor(msg: string) {
            super(`500 Internal Server Error: ${msg}`,
                {
                    status: 500
                });
        }
    }
}

export namespace Successes {
    export class ResourceResponse extends Response {
        constructor(contents: ArrayBuffer, type: string) {
            super(contents,
                {
                    status: 200,
                    headers: { "Content-Type": type }
                });
        }
    }
}
