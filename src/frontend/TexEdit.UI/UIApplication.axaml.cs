/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;
using Avalonia.Markup.Xaml;

using TexEdit.UI.ViewModels;
using TexEdit.UI.Views;
using TexEdit.Utils;

namespace TexEdit.UI {
    public sealed class UIApplication : Application {
        public override void Initialize() {
            AvaloniaXamlLoader.Load(this);
        }

        public override void OnFrameworkInitializationCompleted() {
            if (ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop) {
                desktop.MainWindow = new EditorView
                {
                    DataContext = new EditorViewModel()
                };

                desktop.Exit += PrintExitDialogue;
            }

            base.OnFrameworkInitializationCompleted();
        }

        public static void Quit(int status = 0) {
            if (Current?.ApplicationLifetime is IClassicDesktopStyleApplicationLifetime desktop) {
                // if we can't get the main window then just exit as standard
                if (desktop.MainWindow == null) {
                    goto UngracefulOut;
                }

                desktop.MainWindow.Close();
                return;
            }

        UngracefulOut:
            Environment.Exit(status);
        }

        private static void PrintExitDialogue(object? s, ControlledApplicationLifetimeExitEventArgs e) {
            Logging.Notification("TexEdit frontend closed");
        }
    }
}
