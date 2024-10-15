use std::{
    fs::File,
    io::{BufWriter, Write},
};

use eframe::egui::{self, Ui};
use meval::eval_str;
use random::Random;
use tokio::{
    sync::oneshot::{self, Receiver, Sender},
    task::JoinHandle,
};

#[tokio::main]
async fn main() {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default()
            .with_resizable(false)
            .with_inner_size([320.0, 480.0]),
        ..Default::default()
    };
    _ = eframe::run_native("Lab 1", options, Box::new(|_cc| Ok(Box::<App>::default())));
}

struct App {
    m: usize,
    a: usize,
    c: usize,
    x_0: usize,
    n: usize,
    period: Option<usize>,
    results: Vec<usize>,
    show_results: bool,
    written: bool,
    writing: bool,
    generating: bool,
    tx: Option<Sender<usize>>,
    rx: Receiver<usize>,
    handle: Option<JoinHandle<()>>,
}

impl Default for App {
    fn default() -> Self {
        let (tx, rx) = oneshot::channel::<usize>();
        Self {
            m: 0,
            a: 0,
            c: 0,
            x_0: 0,
            n: 0,
            period: None,
            results: Vec::new(),
            show_results: false,
            written: false,
            writing: false,
            generating: false,
            tx: Some(tx),
            rx,
            handle: None,
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        ctx.set_pixels_per_point(1.2);
        egui::CentralPanel::default().show(ctx, |ui| {
            self.inputs(ui);
            ui.vertical_centered(|ui| {
                self.controls(ui);
                self.results(ui);
            });
        });
    }
}

impl App {
    fn inputs(&mut self, ui: &mut Ui) {
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
    }

    fn controls(&mut self, ui: &mut Ui) {
        if !self.generating && !self.writing {
            if ui.add(egui::Button::new("Generate")).clicked() {
                if self.m == 0 {
                    return;
                }
                self.written = false;
                self.generating = true;
                let mut rng = Random::new(self.m, self.a, self.c, self.x_0);
                let tx = self.tx.take();
                tokio::spawn(async move {
                    let period = rng.period();
                    tx.unwrap().send(period).unwrap();
                });
                self.results = rng.into_iter().take(self.n).collect();
                self.show_results = self.results.len() > 0;
            }
        }
        if self.generating {
            ui.spinner();
            if let Ok(period) = self.rx.try_recv() {
                self.period = Some(period);
                self.generating = false;
                let (tx, rx) = oneshot::channel();
                self.tx = Some(tx);
                self.rx = rx;
            }
        }

        if self.writing {
            ui.spinner();
        }

        if self.show_results
            && !self.generating
            && !self.writing
            && ui.add(egui::Button::new("Write to file")).clicked()
        {
            if let Some(path) = rfd::FileDialog::new().pick_file() {
                self.writing = true;
                let path = path.display().to_string();
                let rng = Random::new(self.m, self.a, self.c, self.x_0);
                let period = self.period.unwrap_or(0);
                self.handle = Some(tokio::spawn(async move {
                    let file = File::options()
                        .create(true)
                        .write(true)
                        .truncate(true)
                        .open(&path)
                        .unwrap();
                    let mut writer = BufWriter::new(file);
                    for x in rng.take(period) {
                        writeln!(writer, "{x}").unwrap();
                    }
                    writer.flush().unwrap();
                }));
            }
        }

        if self.writing {
            if let Some(handle) = &self.handle {
                if handle.is_finished() {
                    self.writing = false;
                    self.written = true;
                }
            }
        }

        if self.written && !self.writing {
            ui.label(format!("Successfully written!"));
        }
    }

    fn results(&mut self, ui: &mut Ui) {
        if self.show_results {
            if !self.generating {
                ui.separator();
                ui.label(format!("Period = {}", self.period.unwrap_or(0)));
                ui.separator();
            }

            self.table(ui);
        }
    }

    fn table(&mut self, ui: &mut Ui) {
        egui::ScrollArea::vertical().show(ui, |ui| {
            egui::Grid::new("table")
                .striped(true)
                .min_col_width(250.0)
                .show(ui, |ui| {
                    for value in &self.results {
                        ui.with_layout(
                            egui::Layout::centered_and_justified(egui::Direction::LeftToRight),
                            |ui| {
                                ui.add(egui::Label::new(format!("{}", value)));
                            },
                        );
                        ui.end_row();
                    }
                });
        });
    }
}
