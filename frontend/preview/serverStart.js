/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

// TODO: graphical response to errors - so they are visible to the user in the webview component.

import * as http from "http";

import * as routeMap from "./server/routeMap.js";

const host = "localhost";
const port = 8080;

function respond(httpRes, objRes) {
    for (const [k, v] of Object.entries(objRes.headers)) {
        httpRes.setHeader(k, v);
    }

    httpRes.writeHead(objRes.status);

    httpRes.write(objRes.content);

    httpRes.end();
}

const server = http.createServer(async (req, res) => {
    respond(res, await routeMap.mapRoute(req.url));

});

server.listen(port, host, () => {
    console.log(`Server is running on http://${host}:${port}`);
});
