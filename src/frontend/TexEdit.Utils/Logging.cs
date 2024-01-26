/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

namespace TexEdit.Utils {
    public static class Logging {
        public static void Log(string str) {
            Console.WriteLine($"texedit: LOG  : {str}");
        }

        public static void Notification(string str) {
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.WriteLine($"texedit: NOTE : {str}");
            Console.ResetColor();
        }

        public static void Warning(string str) {
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine($"texedit: WARN : {str}");
            Console.ResetColor();
        }

        public static void Error(string str) {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.WriteLine($"texedit: ERROR: {str}");
            Console.ResetColor();
        }

        public static void FatalError(string str) {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.BackgroundColor = ConsoleColor.Yellow;
            Console.WriteLine($"texedit: FATAL: {str}");
            Console.ResetColor();

            Environment.Exit(1);
        }
    }
}
