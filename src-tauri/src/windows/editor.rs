/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

use tauri::{utils::assets::EmbeddedAssets, Wry};

use crate::browser;

pub struct Editor {}

impl Editor {
    pub fn menu(ctx: &tauri::Context<EmbeddedAssets>) -> tauri::Menu {
        let file = tauri::Submenu::new(
            "File",
            tauri::Menu::new()
                .add_item(tauri::CustomMenuItem::new(
                    "file__close_window",
                    "Close Window",
                ))
                .add_native_item(tauri::MenuItem::Separator)
                .add_item(tauri::CustomMenuItem::new("file__exit", "Exit")),
        );

        let help = tauri::Submenu::new(
            "Help",
            tauri::Menu::new().add_item(tauri::CustomMenuItem::new(
                "help__git_repository",
                "Git repository",
            )),
        );

        tauri::Menu::new().add_submenu(file).add_submenu(help)
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
