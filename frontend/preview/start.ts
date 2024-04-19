/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

// TODO: graphical response to errors - so they are visible to the user in the webview component.

import { Router, type ServeOptions } from "@stricjs/router";
import * as routes from "./server/routes";

const serveOpts: ServeOptions = {
    hostname: "localhost",
    port: 8080
}

new Router(serveOpts)
    .get("/", routes.index)
    .get("/*", (ctx) => routes.getResource(ctx.params["*"]))
    .get("/curpdf", routes.getResourceCurPDF)
    .use(404, () => new Response("Resource not found.", { status: 404 }))
    .listen();
