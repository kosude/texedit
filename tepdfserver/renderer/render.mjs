/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

const url = "/curpdf";

const { pdfjsLibPromise } = globalThis;

pdfjsLibPromise.then((pdfjsLib) => {
    pdfjsLib.GlobalWorkerOptions.workerSrc = "/pdf.worker.mjs";

    const loadingTask = pdfjsLib.getDocument(url);
    loadingTask.promise.then((pdf) => {
        var pageNumber = 1;
        pdf.getPage(pageNumber).then((page) => {
            const viewport = page.getViewport({ scale: 2 });
            const outputScale = window.devicePixelRatio || 1;

            const canvas = document.getElementById("pdf-render");
            const context = canvas.getContext("2d");

            canvas.width = Math.floor(viewport.width * outputScale);
            canvas.height = Math.floor(viewport.height * outputScale);
            canvas.style.width = Math.floor(viewport.width * outputScale) + "px";
            canvas.style.height = Math.floor(viewport.height * outputScale) + "px";

            const transform = outputScale !== 1
                ? [outputScale, 0, 0, outputScale, 0, 0]
                : null;

            const renderContext = {
                canvasContext: context,
                viewport: viewport,
                transform: transform
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
