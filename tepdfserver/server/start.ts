/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

// TODO: graphical response to errors - so they are visible to the user in the webview component.

import { Router, type ServeOptions } from "@stricjs/router";
import * as routes from "./routes";

const serveOpts: ServeOptions = {
    hostname: "localhost",
    port: 6950
}

var r = new Router(serveOpts)
    .get("/", routes.index)
    .get("/*", (ctx) => routes.getResource(ctx.params["*"]))
    .get("/curpdf", routes.getResourceCurPDF)
    .use(404, () => new Response("Resource not found.", { status: 404 }));

// this output will be read and scanned by the texedit GUI
// TODO: only print this when this program is invoked by texedit (i.e. add cli flag)
console.log(`tepdfserver:Port=${r.port}`);

r.listen();
