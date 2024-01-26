/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

using Avalonia.Controls;
using Avalonia.Interactivity;
using TexEdit.Utils;

namespace TexEdit.UI.Views {
    public sealed partial class EditorView : Window {
        public EditorView() {
            InitializeComponent();
        }

        private void MenuItem_File_Quit(object? s, RoutedEventArgs e) => UIApplication.Quit();

        private void MenuItem_Help_GitRepository(object? s, RoutedEventArgs e) => Browser.OpenWebPage(Browser.Urls.GitRepository);
    }
}
