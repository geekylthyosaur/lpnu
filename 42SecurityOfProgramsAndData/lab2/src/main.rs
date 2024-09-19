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
    output_hash: Digest,
    input_string: Option<String>,
    input_file: Option<Vec<u8>>,
    file_name: Option<String>,
    hash_from_file: Option<Digest>,
}

impl Default for App {
    fn default() -> Self {
        Self {
            output_hash: md5::compute(""),
            input_string: Some(String::new()),
            input_file: None,
            file_name: None,
            hash_from_file: None,
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.horizontal(|ui| {
                ui.label(format!("MD5 hash: {:X}", self.output_hash));
                if ui.button("Write to file").clicked() {
                    if let Some(path) = rfd::FileDialog::new().pick_file() {
                        let mut file = File::options()
                            .create(true)
                            .write(true)
                            .truncate(true)
                            .open(&path)
                            .unwrap();

                        file.write_all(format!("{:X}", self.output_hash).as_bytes())
                            .unwrap();
                    }
                }
            });
            ui.separator();

            if let Some(s) = self.input_string.as_mut() {
                ui.vertical(|ui| {
                    let label = ui.label("String to hash: ");
                    ui.text_edit_singleline(s).labelled_by(label.id);
                });
            }
            ui.horizontal(|ui| {
                if ui.button("Select File").clicked() {
                    if let Some(path) = rfd::FileDialog::new().pick_file() {
                        let mut file = File::open(&path).unwrap();
                        let mut buf = Vec::new();
                        file.read_to_end(&mut buf).unwrap();
                        self.file_name = path.file_name().map(|s| s.to_string_lossy().to_string());
                        self.input_file = Some(buf);
                        self.input_string.take();
                    }
                }
                if let Some(name) = &self.file_name {
                    ui.label(name);
                }
                if self.input_file.is_some() {
                    if ui.button("x").clicked() {
                        self.file_name.take();
                        self.input_file.take();
                        self.input_string = Some(String::new());
                        self.hash_from_file.take();
                    }
                }
            });

            let bytes = if let Some(s) = &self.input_string {
                s.as_bytes()
            } else {
                self.input_file.as_ref().unwrap()
            };
            self.output_hash = md5::compute(bytes);

            if self.input_file.is_some() {
                ui.separator();
                ui.heading("Check file integrity");

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

                if Some(self.output_hash) == self.hash_from_file {
                    ui.label("File is OK");
                } else if Some(self.output_hash) != self.hash_from_file
                    && self.hash_from_file.is_some()
                {
                    ui.label("Integrity compromised");
                }
            }
        });
    }
}

fn decode_hex(s: &str) -> Result<Vec<u8>, ParseIntError> {
    (0..s.len())
        .step_by(2)
        .map(|i| u8::from_str_radix(&s[i..i + 2], 16))
        .collect()
}
