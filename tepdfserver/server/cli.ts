/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

import { parseArgs } from "util";

const { values } = parseArgs({
    args: Bun.argv,
    options: {
        path: {
            type: "string"
        },
        port: {
            type: "string"
        },

        child: {
            type: "boolean",
        },

        help: {
            type: "boolean",
            short: "h",
        },
        version: {
            type: "boolean",
            short: "V",
        },
    },
    strict: true,
    allowPositionals: true
});

function validateRequiredArgs(): boolean {
    const required = [
        [values.path, "--path"]
    ];

    for (let i = 0; i < required.length; i++) {
        let a = required[i];

        if (!a[0]) {
            console.error(`tepdfserver: missing required argument: ${a[1]}`);
            console.error(`tepdfserver: use the -h option for usage information`);
            return false;
        }
    }

    return true;
}

export type ArgResults = { [longOption: string]: undefined | string | boolean | Array<string | boolean> };

// undefined is returned if the program should exit immediately
export function handleParsedArgs(): ArgResults | undefined {
    if (values.help) {
        usage();
        return undefined;
    }
    if (values.version) {
        version();
        return undefined;
    }

    if (!validateRequiredArgs()) {
        return undefined;
    }

    return values;
}

function usage() {
    console.log(`Usage: tepdfserver [-h] [-V] [--child] [--port=<PORT>] --path=<PATH>`);
    console.log(``);
    console.log(`    --path=<PATH>  Required: specify path to read PDF from`);
    console.log(`    --port=<PORT>  Optionally specify a port to use`);
    console.log(`    --child        Run as a child of a parent TexEdit process`);
    console.log(``);
    console.log(`    -h             Print this help message`);
    console.log(`    -V             Print the version`);
}

function version() {
    // @ts-expect-error: VERSION is defined on the Bun cli when building
    console.log(`tepdfserver, from texedit ${VERSION}`);
}
