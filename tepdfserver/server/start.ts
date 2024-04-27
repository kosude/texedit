/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

// TODO: graphical response to errors - so they are visible to the user in the webview component.

import { Router, type ServeOptions } from "@stricjs/router";
import * as routes from "./routes";
import * as cli from "./cli";

const args = cli.handleParsedArgs();
if (!args) {
    process.exit(0);
}

const serveOpts: ServeOptions = {
    hostname: "localhost",
    port: args["port"] as string ?? 6950
}

var r = new Router(serveOpts)
    .get("/", routes.index)
    .get("/*", (ctx) => routes.getResource(ctx.params["*"]))
    .get("/curpdf", () => routes.getResourceCurPDF(args["path"] as string | undefined))
    .use(404, () => new Response("Resource not found.", { status: 404 }));

// this output will be read and scanned by the texedit GUI
if (args["child"]) {
    console.log(`tepdfserver:Port=${r.port}`);
}

r.listen();
