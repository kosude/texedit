/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

const url = "/curpdf";

const { pdfjsLibPromise } = globalThis;

pdfjsLibPromise.then((pdfjsLib) => {
    pdfjsLib.GlobalWorkerOptions.workerSrc = "lib/pdf.js/pdf.worker.mjs";

    const loadingTask = pdfjsLib.getDocument(url);
    loadingTask.promise.then((pdf) => {
        var pageNumber = 1;
        pdf.getPage(pageNumber).then((page) => {
            const scale = 1.5;
            const viewport = page.getViewport({ scale });
            const outputScale = window.devicePixelRatio || 1;

            const canvas = document.getElementById("pdf-render");
            const context = canvas.getContext("2d");

            canvas.width = Math.floor(viewport.width * outputScale);
            canvas.height = Math.floor(viewport.height * outputScale);
            canvas.style.width = Math.floor(viewport.width) + "px";
            canvas.style.height = Math.floor(viewport.height) + "px";

            const transform = outputScale !== 1
            ? [outputScale, 0, 0, outputScale, 0, 0]
            : null;

            const renderContext = {
                canvasContext: context,
                transform,
                viewport,
            };
            var renderTask = page.render(renderContext);
            renderTask.promise.then(() => {
                console.log("PDF rendered");
            });
        });
    }, (reason) => {
        console.error(reason);
    });
});
