/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

using Avalonia;
using Avalonia.ReactiveUI;

using TexEdit.Utils;
using TexEdit.UI;

namespace TexEdit {
    class Program {
        [STAThread]
        static void Main(string[] args) {
            Logging.Notification("Starting TexEdit frontend");

            // start UI
            BuildAvaloniaApp().StartWithClassicDesktopLifetime(args);
        }

        static AppBuilder BuildAvaloniaApp() {
            return AppBuilder.Configure<UIApplication>()
                .UsePlatformDetect()
                .LogToTrace()
                .UseReactiveUI();
        }
    }
}
