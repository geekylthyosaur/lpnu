use std::{
    fs::File,
    io::{BufRead, BufReader, Read, Write},
    num::ParseIntError,
};

use eframe::egui;
use md5::Digest;
use tokio::sync::oneshot;

#[tokio::main]
async fn main() -> eframe::Result {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default().with_inner_size([400.0, 240.0]),
        ..Default::default()
    };
    eframe::run_native("Lab 2", options, Box::new(|_| Ok(Box::<App>::default())))
}

enum Input {
    String(String),
    File { name: String },
}

struct App {
    output_hash: Digest,
    input: Input,
    hash_from_file: Option<Digest>,
    rx: Option<oneshot::Receiver<Digest>>,
}

impl Default for App {
    fn default() -> Self {
        Self {
            output_hash: md5::compute(""),
            input: Input::String(String::new()),
            hash_from_file: None,
            rx: None,
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

            if let Input::String(s) = &mut self.input {
                ui.vertical(|ui| {
                    let label = ui.label("String to hash: ");
                    ui.text_edit_singleline(s).labelled_by(label.id);
                });
                self.output_hash = md5::compute(s.as_bytes());
            }
            ui.horizontal(|ui| {
                if ui.button("Select File").clicked() {
                    if let Some(path) = rfd::FileDialog::new().pick_file() {
                        self.input = Input::File {
                            name: path
                                .file_name()
                                .map(|s| s.to_string_lossy().to_string())
                                .unwrap(),
                        };
                        let (tx, rx) = oneshot::channel();
                        self.rx = Some(rx);
                        tokio::spawn(async move {
                            let file = File::open(&path).unwrap();
                            let len = file.metadata().unwrap().len();
                            let buf_len = len.min(1024 * 1024) as usize;
                            let mut reader = BufReader::with_capacity(buf_len, file);
                            let mut ctx = md5::Context::new();
                            loop {
                                let part = reader.fill_buf().unwrap();
                                if part.is_empty() {
                                    break;
                                }
                                ctx.consume(part);
                                let part_len = part.len();
                                reader.consume(part_len);
                            }
                            tx.send(ctx.compute()).unwrap();
                        });
                    }
                }
                if let Some(rx) = &mut self.rx {
                    ui.spinner();
                    if let Ok(hash) = rx.try_recv() {
                        self.output_hash = hash;
                        self.rx.take();
                    }
                }
                if let Input::File { name } = &self.input {
                    ui.label(name);
                    if ui.button("x").clicked() {
                        self.input = Input::String(String::new());
                        self.hash_from_file.take();
                    }
                }
            });

            if matches!(self.input, Input::File { .. }) {
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
