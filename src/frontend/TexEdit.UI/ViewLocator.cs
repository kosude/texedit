/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

using Avalonia.Controls;
using Avalonia.Controls.Templates;
using TexEdit.UI.ViewModels;

namespace TexEdit.UI {
    public sealed class ViewLocator : IDataTemplate {
        public Control Build(object? data) {
            // generate name for view
            string? viewName = data?.GetType().FullName?.Replace("ViewModel", "View");
            if (viewName == null)
                goto EarlyOut;

            // get type of view
            Type? viewType = Type.GetType(viewName);
            if (viewType == null)
                goto EarlyOut;

            // build the view
            return (Control) Activator.CreateInstance(viewType)!;

        EarlyOut:
            return new TextBlock { Text = "Not found: " + viewName };
        }

        public bool Match(object? data) {
            return data is ViewModelBase;
        }
    }
}
