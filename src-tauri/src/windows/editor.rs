/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use tauri::Wry;

use crate::browser;

pub struct Editor {}

impl Editor {
    pub fn menu(#[allow(unused)] app_name: &str) -> tauri::Menu {
        let mut m = tauri::Menu::new();

        // application menu (macos only)
        //
        #[cfg(target_os = "macos")]
        {
            m = m.add_submenu(tauri::Submenu::new(
                app_name,
                tauri::Menu::new()
                    .add_native_item(tauri::MenuItem::About(
                        app_name.to_string(),
                        tauri::AboutMetadata::default(),
                    ))
                    .add_native_item(tauri::MenuItem::Separator)
                    .add_native_item(tauri::MenuItem::Services)
                    .add_native_item(tauri::MenuItem::Separator)
                    .add_native_item(tauri::MenuItem::Hide)
                    .add_native_item(tauri::MenuItem::HideOthers)
                    .add_native_item(tauri::MenuItem::ShowAll)
                    .add_native_item(tauri::MenuItem::Separator)
                    .add_native_item(tauri::MenuItem::Quit),
            ));
        }

        // file menu
        //
        let file = tauri::Submenu::new(
            "File",
            tauri::Menu::new().add_item(tauri::CustomMenuItem::new(
                "file__close_window",
                "Close Window",
            )),
        );
        #[cfg(not(target_os = "macos"))]
        {
            file.inner = file
                .inner
                .add_native_item(tauri::MenuItem::Separator)
                .add_item(tauri::CustomMenuItem::new("file__exit", "Exit"));
        }
        m = m.add_submenu(file);

        // help menu
        //
        m = m.add_submenu(tauri::Submenu::new(
            "Help",
            tauri::Menu::new()
                .add_item(tauri::CustomMenuItem::new(
                    "help__git_repository",
                    "Git repository",
                ))
                .add_native_item(tauri::MenuItem::Separator)
                .add_native_item(tauri::MenuItem::About(
                    app_name.to_string(),
                    tauri::AboutMetadata::default()
                        .copyright("Copyright (c) 2024 Jack Bennett")
                        .comments("Integrated viewer, compiler and editor for LaTeX documents"),
                )),
        ));

        m
    }

    fn menu_event_handler_loc(ev: tauri::WindowMenuEvent<Wry>) {
        match ev.menu_item_id() {
            "file__close_window" => {
                ev.window().close().unwrap();
            }
            "file__exit" => {
                std::process::exit(0);
            }

            "help__git_repository" => {
                browser::open_url(browser::github_url());
            }
            _ => {}
        }
    }

    pub fn menu_event_handler() -> impl Fn(tauri::WindowMenuEvent<Wry>) {
        &Self::menu_event_handler_loc
    }
}
