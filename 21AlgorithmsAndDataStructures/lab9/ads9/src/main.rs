mod rbtree;

use rbtree::RBTree;

use eframe::egui::{
    self,
    text_edit::TextEdit,
};
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
    n: String,
    m: String,
    min: Option<usize>,
    v_to_find: String,
    found_key: Option<usize>,
    ntree: RBTree<usize, f32>,
    mtree: RBTree<usize, f32>,
}

impl Default for App {
    fn default() -> Self {
        Self {
            n: String::new(),
            m: String::new(),
            min: None,
            v_to_find: String::new(),
            found_key: None,
            ntree: RBTree::new(),
            mtree: RBTree::new(),
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Red Black Tree");
            ui.horizontal(|ui| {
                if ui.button("Add").clicked() {
                    if let Ok(v) = self.n.parse::<f32>() {
                        if let Some(l) = self.ntree.get_last() {
                                self.ntree.insert(l.0 + 1, v);
                        } else {
                                self.ntree.insert(0, v);
                        }
                    }
                    let mut min = f32::MAX;
                    for (&k, &v) in self.ntree.iter() {
                        if v < min {
                            min = v;
                            self.min = Some(k);
                        }
                    }
                }
                ui.add(TextEdit::singleline(&mut self.n)
                       .hint_text("N")
                       .desired_width(100.0)
                       );
            });
            ui.horizontal(|ui| {
                if let Some(min) = self.min {
                    ui.label(format!("Min: {}", self.ntree.get(&min).unwrap()));
                    ui.label(format!("Min Color: {:?}", self.ntree.color(min)));
                    if let Some(parent) = self.ntree.parent(min) {
                        ui.label(format!("Min Parent: {}", self.ntree.get(&parent).unwrap()));
                        ui.label(format!("Min Parent Color: {:?}", self.ntree.color(parent)));
                    }
                }
            });
            ui.horizontal(|ui| {
                if ui.button("Add").clicked() {
                    if let Ok(v) = self.m.parse::<f32>() {
                        if let Some(l) = self.mtree.get_last() {
                                self.mtree.insert(l.0 + 1, v);
                        } else {
                                self.mtree.insert(0, v);
                        }
                    }
                }
                ui.add(TextEdit::singleline(&mut self.m)
                           .hint_text("M")
                           .desired_width(100.0)
                       );
            });
            ui.horizontal(|ui| {
                if ui.button("Find").clicked() {
                    if let Ok(v_to_find) = self.v_to_find.parse::<f32>() {
                        for (&k, &v) in self.mtree.iter() {
                            if v == v_to_find {
                                self.found_key = Some(k);
                                break;
                            }
                        }
                    }
                }
                ui.add(TextEdit::singleline(&mut self.v_to_find)
                           .hint_text("Find")
                           .desired_width(100.0)
                       );
                ui.label(format!("Found: {}", self.found_key.is_some()));
            });
            if let Some(found) = self.found_key {
                if let Some(left) = self.mtree.left(found) {
                    ui.horizontal(|ui| {
                        ui.label(format!("Left: {}", self.mtree.get(&left).unwrap()));
                        ui.label(format!("Color: {:?}", self.mtree.color(left)));
                    });
                }
                if let Some(right) = self.mtree.right(found) {
                    ui.horizontal(|ui| {
                        ui.label(format!("Right: {}", self.mtree.get(&right).unwrap()));
                        ui.label(format!("Color: {:?}", self.mtree.color(right)));
                    });
                }
                if let Some(parent) = self.mtree.parent(found) {
                    ui.horizontal(|ui| {
                        ui.label(format!("Parent: {}", self.mtree.get(&parent).unwrap()));
                        ui.label(format!("Color: {:?}", self.mtree.color(parent)));
                    });
                }
            }
        });
    }
}
