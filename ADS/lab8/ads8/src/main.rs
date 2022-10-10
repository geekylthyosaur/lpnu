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
    stack: Stack<f32>,
}

impl Default for App {
    fn default() -> Self {
        Self {
            value_to_push: String::new(),
            stack: Stack::new(),
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Stack");
            ui.horizontal(|ui| {
                ui.text_edit_singleline(&mut self.value_to_push);
                if ui.button("Push").clicked() {
                    let value = self.value_to_push.parse::<f32>().unwrap();
                    self.stack = self.stack.push(value);
                }
            });
            if ui.button("Pop").clicked() {
                self.stack = self.stack.pop();
            }
            TableBuilder::new(ui)
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
                                    ui.label(item.to_string());
                            });
                        });
                    }
                });
        });
    }
}
