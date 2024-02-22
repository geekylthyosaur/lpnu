mod data;
mod sort;

use eframe::egui;
use egui_extras::{Size, TableBuilder};

use crate::{data::Data, sort::Sorted};

fn main() {
    let options = eframe::NativeOptions::default();
    eframe::run_native(
        "Sorting",
        options,
        Box::new(|_cc| Box::new(SortingApp::new())),
    );
}

struct SortingApp {
    data: Option<Vec<Data>>,
    prev_data: Option<Vec<Data>>,
    data_len: usize,
    selected: Option<Vec<(usize, usize)>>,
    elapsed: Option<std::time::Duration>,
}

impl SortingApp {
    fn new() -> Self {
        Self {
            data: Some(fake::vec![Data; 1]),
            prev_data: None,
            data_len: 1,
            selected: None,
            elapsed: None,
        }
    }
}

impl eframe::App for SortingApp {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            if ui
                .add(egui::DragValue::new(&mut self.data_len).speed(0.1))
                .changed
            {
                self.data = Some(fake::vec![Data; self.data_len])
            }
            ui.end_row();
            if ui.button("Sort").clicked() {
                self.prev_data = self.data.to_owned();
                match &mut self.data {
                    Some(d) => {
                        use std::time::Instant;
                        let now = Instant::now();
                        self.selected = Some(Sorted::sort(d));
                        self.data_len = d.len();
                        self.elapsed = Some(now.elapsed());
                    }
                    None => {}
                };
            }
            if let Some(elapsed) = self.elapsed {
                ui.label(format!("{:.2?}", elapsed).to_string());
            }
            ui.end_row();
            egui::Grid::new("unique_id")
                .min_col_width(290.)
                .show(ui, |ui| {
                    ui.label("after");
                    ui.label("before");
                    ui.label("Indexes");
                    ui.end_row();
                });
            egui::Grid::new("another_unique_id")
                .min_row_height(500.)
                .show(ui, |ui| {
                    ui.push_id(1, |ui| {
                        TableBuilder::new(ui)
                            .striped(true)
                            .cell_layout(egui::Layout::left_to_right(egui::Align::Center))
                            .column(Size::initial(20.0).at_least(40.0))
                            .column(Size::initial(150.0).at_least(40.0))
                            .column(Size::initial(100.0).at_least(40.0))
                            .body(|mut body| {
                                if let Some(data) = self.data.as_ref() {
                                    for i in 0..data.len() {
                                        body.row(30., |mut row| {
                                            row.col(|ui| {
                                                ui.label(i.to_string());
                                            });
                                            row.col(|ui| {
                                                if let Some(v) = data.get(i) {
                                                    ui.label(v.name.clone());
                                                }
                                            });
                                            row.col(|ui| {
                                                if let Some(v) = data.get(i) {
                                                    ui.label(v.price.to_string());
                                                }
                                            });
                                        });
                                    }
                                }
                            });
                    });

                    ui.push_id(2, |ui| {
                        TableBuilder::new(ui)
                            .striped(true)
                            .cell_layout(egui::Layout::left_to_right(egui::Align::Center))
                            .column(Size::initial(20.0).at_least(40.0))
                            .column(Size::initial(150.0).at_least(40.0))
                            .column(Size::initial(100.0).at_least(40.0))
                            .body(|mut body| {
                                if let Some(data) = self.prev_data.as_ref() {
                                    for i in 0..data.len() {
                                        body.row(30., |mut row| {
                                            row.col(|ui| {
                                                ui.label(i.to_string());
                                            });
                                            row.col(|ui| {
                                                if let Some(v) = data.get(i) {
                                                    ui.label(v.name.clone());
                                                }
                                            });
                                            row.col(|ui| {
                                                if let Some(v) = data.get(i) {
                                                    ui.label(v.price.to_string());
                                                }
                                            });
                                        });
                                    }
                                }
                            });
                    });

                    ui.push_id(3, |ui| {
                        TableBuilder::new(ui)
                            .striped(true)
                            .cell_layout(egui::Layout::left_to_right(egui::Align::Center))
                            .column(Size::initial(40.0).at_least(40.0))
                            .column(Size::initial(40.0).at_least(40.0))
                            .body(|mut body| {
                                if let Some(selected) = self.selected.as_ref() {
                                    for i in 0..selected.len() {
                                        body.row(30., |mut row| {
                                            row.col(|ui| {
                                                if let Some(v) = selected.get(i) {
                                                    ui.label(v.0.to_string());
                                                }
                                            });
                                            row.col(|ui| {
                                                if let Some(v) = selected.get(i) {
                                                    ui.label(v.1.to_string());
                                                }
                                            });
                                        });
                                    }
                                }
                            });
                    });
                });
        });
    }
}
