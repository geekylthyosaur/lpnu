mod data;
mod search;

use eframe::egui::{self, text_edit::TextEdit};

use data::Data;
use search::Haystack;

fn main() {
    let options = eframe::NativeOptions::default();
    eframe::run_native("Stack", options, Box::new(|_cc| Box::new(App::default())));
}

struct App {
    data: Data,
    shortest: Option<String>,
    found_index: Option<usize>,
    radio: Mode,
    str_to_search: String,
}

#[derive(PartialEq)]
enum Mode {
    Shortest,
    Enter,
}

impl Default for App {
    fn default() -> Self {
        Self {
            data: Data::new(),
            shortest: None,
            found_index: None,
            radio: Mode::Shortest,
            str_to_search: String::new(),
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Knuth–Morris–Pratt algorithm");
            ui.horizontal(|ui| {
                ui.radio_value(&mut self.radio, Mode::Shortest, "Shortest");
                ui.radio_value(&mut self.radio, Mode::Enter, "Enter");
            });
            if self.radio == Mode::Shortest {
                if ui.button("Restart").clicked() {
                    print!("{}[2J", 27 as char);
                    self.data = Data::new();
                    self.shortest = Some(self.data.text1.iter().fold(
                        self.data.text1[0].clone(),
                        |acc, item| {
                            if item.len() < acc.len() {
                                item.clone()
                            } else {
                                acc
                            }
                        },
                    ));
                }
                if self.shortest.is_none() {
                    print!("{}[2J", 27 as char);
                    self.shortest = Some(self.data.text1.iter().fold(
                        self.data.text1[0].clone(),
                        |acc, item| {
                            if item.len() < acc.len() {
                                item.clone()
                            } else {
                                acc
                            }
                        },
                    ));
                }
                if let Some(shortest) = &self.shortest {
                    ui.label(format!("Shortest word in first test: {}", shortest));
                    if ui.button("Search in second text").clicked() {
                        print!("{}[2J", 27 as char);
                        self.found_index = self.data.text2.first_indexof_needle(shortest);
                    }
                }
                ui.label(format!("Found index: {:?}", self.found_index));
                ui.add(TextEdit::multiline(&mut self.data.text1.join(" ")));
            } else {
                if ui.button("Restart").clicked() {
                    print!("{}[2J", 27 as char);
                    self.data = Data::new();
                }
                ui.text_edit_singleline(&mut self.str_to_search);
                ui.horizontal(|ui| {
                    if ui.button("Search in second text").clicked() {
                        print!("{}[2J", 27 as char);
                        self.found_index =
                            self.data.text2.first_indexof_needle(&self.str_to_search);
                    }
                });
                if ui.button("Fill").clicked() {
                    self.str_to_search = "abcabc".to_string();
                    self.data.text2 = "abcabdabcabc".to_string();
                }
                ui.label(format!("Found index: {:?}", self.found_index));
            }
            ui.add(TextEdit::multiline(&mut self.data.text2));
        });
    }
}
