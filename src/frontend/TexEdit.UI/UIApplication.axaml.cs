/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

using Avalonia;
using Avalonia.Controls.ApplicationLifetimes;

using TexEdit.Utils;

namespace TexEdit.UI {
    public class UIApplication : Application {
        public static void Quit(int status = 0) {
            Logging.Notification("Closing TexEdit");

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
    }
}
