mod stack;

use stack::Stack;

use eframe::egui;
use egui_extras::{Size, TableBuilder};

fn main() {
    let options = eframe::NativeOptions::default();
    eframe::run_native(
        "Stack",
        options,
        Box::new(|_cc| Box::new(App::default())),
    );
}

struct App {
    value_to_push: String,
    value_to_find: String,
    found_index: usize,
    stack: Stack<f32>,
}

impl Default for App {
    fn default() -> Self {
        Self {
            value_to_push: String::new(),
            value_to_find: String::new(),
            found_index: 0,
            stack: Stack::new(),
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Stack");
            ui.horizontal(|ui| {
                if ui.button("Push").clicked() {
                    let value = self.value_to_push.parse::<f32>().unwrap();
                    self.stack = self.stack.push(value);
                }
                ui.text_edit_singleline(&mut self.value_to_push);
            });
            ui.horizontal(|ui| {
                if ui.button("Find").clicked() {
                    let value = self.value_to_find.parse::<f32>().unwrap();
                    if let Some(i) = self.stack.iter().position(|&i| i == value) {
                        self.found_index = i;
                    }
                }
                ui.text_edit_singleline(&mut self.value_to_find);
                ui.label(format!("Found: {}", self.found_index));
            });
            ui.horizontal(|ui| {
                if ui.button("Pop").clicked() {
                    self.stack = self.stack.pop();
                }
                if ui.button("Join with random").clicked() {
                    let random_stack = Stack::new_random();
                    for item in random_stack.iter() {
                        self.stack = self.stack.push(*item);
                    }
                }
            });
            ui.horizontal(|ui| {
                let count = self.stack.iter().count();
                ui.label(format!("Length: {}", count));
                ui.label(format!("Min: {:.2}", self.stack.iter().fold(f32::INFINITY, |a, &b| a.min(b))));
                ui.label(format!("Max: {:.2}", self.stack.iter().fold(f32::NEG_INFINITY, |a, &b| a.max(b))));
                if let Some(tfs) = self.stack.iter().nth(2) {
                    ui.label(format!("Third from start: {:.2}", tfs));
                }
                if count > 1 {
                    if let Some(tfs) = self.stack.iter().nth(count - 2) {
                        ui.label(format!("Second last: {:.2}", tfs));
                    }
                }
            });
            TableBuilder::new(ui)
                .striped(true)
                .cell_layout(egui::Layout::left_to_right(egui::Align::Center))
                .column(Size::exact(100.0).at_least(100.0))
                .header(20.0, |mut header| {
                    header.col(|ui| {
                        ui.heading("Stack");
                    });
                })
                .body(|mut body| {
                    for item in self.stack.iter() {
                        body.row(30.0, |mut row| {
                            row.col(|ui| {
                                    ui.label(format!("{:.2}", item));
                            });
                        });
                    }
                });
        });
    }
}
