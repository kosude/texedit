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
    public static class Program {
        [STAThread]
        public static void Main(string[] args) {
            Logging.Notification("Starting TexEdit frontend");

            // start UI
            BuildAvaloniaApp().StartWithClassicDesktopLifetime(args);
        }

        private static AppBuilder BuildAvaloniaApp() {
            return AppBuilder.Configure<UIApplication>()
                .UsePlatformDetect()
                .LogToTrace()
                .UseReactiveUI();
        }
    }
}
