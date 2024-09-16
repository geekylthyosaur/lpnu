use std::{
    fs::File,
    io::{Read, Write},
    num::ParseIntError,
};

use eframe::egui;
use md5::Digest;

fn main() -> eframe::Result {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default().with_inner_size([400.0, 240.0]),
        ..Default::default()
    };
    eframe::run_native("Lab 2", options, Box::new(|_| Ok(Box::<App>::default())))
}

struct App {
    string: String,
    hash: Digest,
    file_hash: Option<Digest>,
    file_name: Option<String>,
    hash_from_file: Option<Digest>,
}

impl Default for App {
    fn default() -> Self {
        Self {
            string: String::new(),
            hash: md5::compute(""),
            file_hash: None,
            file_name: None,
            hash_from_file: None,
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.horizontal(|ui| {
                ui.label(format!("MD5 hash: {:X}", self.hash));
                if ui.button("Write to file").clicked() {
                    if let Some(path) = rfd::FileDialog::new().pick_file() {
                        let mut file = File::options()
                            .create(true)
                            .write(true)
                            .truncate(true)
                            .open(&path)
                            .unwrap();

                        file.write_all(format!("{:X}", self.hash).as_bytes())
                            .unwrap();
                    }
                }
            });
            ui.separator();

            ui.vertical(|ui| {
                let label = ui.label("String to hash: ");
                ui.text_edit_singleline(&mut self.string)
                    .labelled_by(label.id);
            });
            ui.horizontal(|ui| {
                if ui.button("Select File").clicked() {
                    if let Some(path) = rfd::FileDialog::new().pick_file() {
                        let mut file = File::open(&path).unwrap();
                        self.string.clear();
                        file.read_to_string(&mut self.string).unwrap();
                        self.file_hash = Some(md5::compute(&self.string));
                        self.file_name = path.file_name().map(|s| s.to_string_lossy().to_string());
                    }
                }
                if let Some(name) = &self.file_name {
                    ui.label(name);
                }
            });
            self.hash = md5::compute(&self.string);

            ui.separator();
            ui.heading("Check file integrity");
            ui.horizontal(|ui| {
                if ui.button("Select File").clicked() {
                    if let Some(path) = rfd::FileDialog::new().pick_file() {
                        let mut file = File::open(&path).unwrap();
                        let mut buf = Vec::new();
                        file.read_to_end(&mut buf).unwrap();
                        self.file_hash = Some(md5::compute(&buf));
                    }
                }
                if let Some(hash) = &self.file_hash {
                    ui.label(format!("MD5 Hash: {:X}", hash));
                }
            });

            ui.horizontal(|ui| {
                if ui.button("Select Hash").clicked() {
                    if let Some(path) = rfd::FileDialog::new().pick_file() {
                        let mut file = File::open(&path).unwrap();
                        let mut buf = String::new();
                        file.read_to_string(&mut buf).unwrap();
                        let bytes = decode_hex(&buf).unwrap();
                        self.hash_from_file = Some(Digest({
                            let mut b = [0; 16];
                            b.copy_from_slice(&bytes);
                            b
                        }));
                    }
                }
                if let Some(hash) = &self.hash_from_file {
                    ui.label(format!("MD5 Hash: {:X}", hash));
                }
            });
        });
    }
}

fn decode_hex(s: &str) -> Result<Vec<u8>, ParseIntError> {
    (0..s.len())
        .step_by(2)
        .map(|i| u8::from_str_radix(&s[i..i + 2], 16))
        .collect()
}
