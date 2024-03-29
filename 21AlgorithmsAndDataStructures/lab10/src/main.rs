mod data; 

use eframe::egui::{
    self,
    text_edit::TextEdit,
};

use data::Arr;

fn main() {
    let options = eframe::NativeOptions::default();
    eframe::run_native(
        "Stack",
        options,
        Box::new(|_cc| Box::new(App::default())),
    );
}

#[derive(Default)]
struct App { 
    arr: Option<Arr>,
    len: String,
    found: Option<String>,
    price_to_find: String,
    cmp_counter: usize,
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Binary Search");
            ui.horizontal(|ui| {
                if ui.button("Create").clicked() {
                    if let Ok(len) = self.len.parse::<usize>() {
                        self.arr = Some(Arr::new(len));
                    }
                }
                ui.add(TextEdit::singleline(&mut self.len)
                    .hint_text("Length")
                    .desired_width(100.0)
                );
            });
            if let Some(arr) = &self.arr {
                ui.horizontal(|ui| {
                    if ui.button("Find").clicked() {
                        if let Ok(price_to_find) = self.price_to_find.parse::<usize>() {
                            (self.found, self.cmp_counter) = arr.search(price_to_find);
                        }
                    }
                    ui.add(TextEdit::singleline(&mut self.price_to_find)
                        .hint_text("Price")
                        .desired_width(100.0)
                    );
                    if let Some(found) = &self.found {
                        ui.label(format!("Found: {}", found));
                    } else {
                        ui.label("Not Found");
                    }
                });
                ui.label(format!("Number of comparisions: {}", self.cmp_counter));
                if ui.button("Print").clicked() {
                    arr.print();
                }
            }
        });
    }
}

