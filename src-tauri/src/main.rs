/*
 *   Copyright (c) 2024 Jack Bennett.
 *   All Rights Reserved.
 *
 *   See the LICENCE file for more information.
 */

// Prevents additional console window on Windows in release, DO NOT REMOVE!!
#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

mod browser;
mod log;
mod windows;

use tauri::{utils::assets::EmbeddedAssets, Wry};

fn main() {
    let context = tauri::generate_context!();
    create_tauri_builder(&context)
        .run(context)
        .expect("Tauri error encountered");
}

fn create_tauri_builder(ctx: &tauri::Context<EmbeddedAssets>) -> tauri::Builder<Wry> {
    tauri::Builder::default()
        .menu(windows::Editor::menu(&ctx.package_info().name))
        .on_menu_event(windows::Editor::menu_event_handler())
}
