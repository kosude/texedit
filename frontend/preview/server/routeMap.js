/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

import * as routes from "./routes.js";
import * as error from "./error.js";

const routesMap = {
    "/": routes.index
};

const regexRoutesMap = {
    "[^\\/].*\\.pdf": routes.getUncachedResource,
    "[^\\/].*": routes.getResource
}

export async function mapRoute(url) {
    if (url in routesMap) {
        return routesMap[url]();
    }

    // some routes are defined by regex, so check each one of those if url didn't match a static route
    for (const [r, f] of Object.entries(regexRoutesMap)) {
        let matches = new RegExp(r).exec(url);
        if (matches !== null && matches !== undefined) {
            // matches[0] contains the first match so we discard it
            // what remains should be whatever is given in the url (i.e. the route string)
            return await f(matches.shift());
        }
    }

    return error.http404();
}
