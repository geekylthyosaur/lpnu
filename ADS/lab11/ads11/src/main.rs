mod data; 
mod search;

use eframe::egui::{
    self,
    text_edit::TextEdit,
};

use data::Data;
use search::Haystack;

fn main() {
    let options = eframe::NativeOptions::default();
    eframe::run_native(
        "Stack",
        options,
        Box::new(|_cc| Box::new(App::default())),
    );
}

struct App { 
    data: Data,
    shortest: Option<String>,
}

impl Default for App {
    fn default() -> Self {
        Self {
            data: Data::new(),
            shortest: None,
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Knuth–Morris–Pratt algorithm");
            if self.shortest.is_none() {
                self.shortest = Some(self.data.text1.iter().fold(self.data.text1[0].clone(), |acc, item| {
                    if item.len() < acc.len() {
                        item.clone()
                    } else {
                        acc
                    }
                }));
            }
            ui.horizontal(|ui| {
                if let Some(shortest) = &self.shortest {
                    if ui.button("Start").clicked() {
                        self.data.text2.first_indexof_needle(shortest);
                    }
                    ui.label(format!("Shortest word: {}", shortest));
                }
            });
            ui.horizontal(|ui| {
                ui.text_edit_multiline(&mut self.data.text2.clone());
            });
        });
    }
}

