use std::{fs::File, io::Write};

use eframe::egui;
use meval::eval_str;
use random::Random;

fn main() {
    for x in Random::new(2147483648usize, 65536, 28657, 33).take(20) {
        println!("{x}");
    }
    return;
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default()
            .with_resizable(false)
            .with_inner_size([320.0, 480.0]),
        ..Default::default()
    };
    _ = eframe::run_native("Lab 1", options, Box::new(|_cc| Ok(Box::<App>::default())));
}

struct App {
    m: i64,
    a: i64,
    c: i64,
    x_0: i64,
    n: usize,
    period: usize,
    results: Vec<i64>,
    show_results: bool,
    picked_path: Option<String>,
    written: bool,
    current_page: usize,
    results_per_page: usize,
}

impl Default for App {
    fn default() -> Self {
        Self {
            m: 4095,
            a: 1024,
            c: 2,
            x_0: 8,
            n: 0,
            period: 0,
            results: Vec::new(),
            show_results: false,
            picked_path: None,
            written: false,
            current_page: 0,
            results_per_page: 10,
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        ctx.set_pixels_per_point(1.2);
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.horizontal(|ui| {
                ui.label("Comparision module");
                ui.with_layout(egui::Layout::right_to_left(egui::Align::RIGHT), |ui| {
                    ui.add(
                        egui::DragValue::new(&mut self.m)
                            .prefix("m = ")
                            .custom_parser(|s| eval_str(s).ok()),
                    );
                });
            });

            ui.horizontal(|ui| {
                ui.label("Multiplier");
                ui.with_layout(egui::Layout::right_to_left(egui::Align::RIGHT), |ui| {
                    ui.add(
                        egui::DragValue::new(&mut self.a)
                            .prefix("a = ")
                            .custom_parser(|s| eval_str(s).ok()),
                    );
                });
            });

            ui.horizontal(|ui| {
                ui.label("Increment");
                ui.with_layout(egui::Layout::right_to_left(egui::Align::RIGHT), |ui| {
                    ui.add(
                        egui::DragValue::new(&mut self.c)
                            .prefix("c = ")
                            .custom_parser(|s| eval_str(s).ok()),
                    );
                });
            });

            ui.horizontal(|ui| {
                ui.label("Seed");
                ui.with_layout(egui::Layout::right_to_left(egui::Align::RIGHT), |ui| {
                    ui.add(
                        egui::DragValue::new(&mut self.x_0)
                            .prefix("x_0 = ")
                            .custom_parser(|s| eval_str(s).ok()),
                    );
                });
            });

            ui.horizontal(|ui| {
                ui.label("N");
                ui.with_layout(egui::Layout::right_to_left(egui::Align::RIGHT), |ui| {
                    ui.add(egui::DragValue::new(&mut self.n));
                });
            });

            ui.vertical_centered(|ui| {
                if ui.add(egui::Button::new("Generate")).clicked() {
                    let mut rng = Random::new(self.m, self.a, self.c, self.x_0);
                    self.period = rng.period();
                    if self.n == 0 {
                        self.n = self.period;
                    }
                    self.results = rng.into_iter().take(self.n).collect();
                    self.results.insert(0, self.x_0);
                    self.show_results = true;
                }

                if self.show_results && ui.add(egui::Button::new("Write to file")).clicked() {
                    if let Some(path) = rfd::FileDialog::new().pick_file() {
                        let path = path.display().to_string();
                        let mut file = File::options()
                            .create(true)
                            .write(true)
                            .truncate(true)
                            .open(&path)
                            .unwrap();
                        let text = self
                            .results
                            .iter()
                            .map(|x| format!("{x}\n"))
                            .collect::<String>();
                        file.write_all(text.as_bytes()).unwrap();
                        self.picked_path = Some(path);
                        self.written = true;
                    }
                }

                if self.written {
                    ui.label(format!("Successfully written!"));
                }

                if self.show_results {
                    ui.separator();
                    ui.label(format!("Period = {}", self.period));
                    ui.separator();

                    // Pagination controls
                    let total_pages =
                        (self.results.len() + self.results_per_page - 1) / self.results_per_page;

                    if self.current_page > 0 {
                        if ui.button("Previous").clicked() {
                            self.current_page -= 1;
                        }
                    }
                    if self.current_page < total_pages - 1 {
                        if ui.button("Next").clicked() {
                            self.current_page += 1;
                        }
                    }

                    ui.label(format!("Page {}/{}", self.current_page + 1, total_pages));

                    ui.separator();

                    let start = self.current_page * self.results_per_page;
                    let end = (start + self.results_per_page).min(self.results.len());

                    egui::ScrollArea::vertical().show(ui, |ui| {
                        egui::Grid::new("table")
                            .striped(true)
                            .min_col_width(250.0)
                            .show(ui, |ui| {
                                for value in &self.results[start..end] {
                                    ui.with_layout(
                                        egui::Layout::centered_and_justified(
                                            egui::Direction::LeftToRight,
                                        ),
                                        |ui| {
                                            ui.add(egui::Label::new(format!("{}", value)));
                                        },
                                    );
                                    ui.end_row();
                                }
                            });
                    });
                }
            });
        });
    }
}
