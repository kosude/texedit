/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

using System.Diagnostics;

namespace TexEdit.Utils {
    public static class Browser {
        public static class Urls {
            public static string GitRepository => "https://github.com/kosude/texedit";
        }

        public static bool OpenWebPage(string url) {
            Process proc = new();

            Logging.Log($"Attempting to open webpage at {url}");

            try {
                proc.StartInfo.UseShellExecute = true;
                proc.StartInfo.FileName = url;
                proc.Start();
            } catch (Exception e) {
                Logging.Error(e.Message);
                return false;
            }

            return true;
        }
    }
}
