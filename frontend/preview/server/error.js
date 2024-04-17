/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

export const http404 = (msg = undefined) => {
    return {
        status: 404,
        headers: {},
        content: msg || "Resource not found."
    };
};
