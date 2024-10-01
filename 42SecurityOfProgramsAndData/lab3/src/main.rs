#![feature(split_array)]
#![feature(path_add_extension)]

use std::{
    fs::File,
    io::{Read, Write},
    path::PathBuf,
};

use eframe::egui;
use tokio::task::JoinHandle;

const ROUNDS: usize = 12;

type Key = [u8; 8];

#[tokio::main]
async fn main() -> eframe::Result {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default().with_inner_size([400.0, 240.0]),
        ..Default::default()
    };
    eframe::run_native("Lab 3", options, Box::new(|_| Ok(Box::<App>::default())))
}

#[derive(Default)]
struct App {
    password: String,
    key: Key,
    handle: Option<JoinHandle<()>>,
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.vertical_centered(|ui| {
                let label = ui.label("Password: ");
                ui.text_edit_singleline(&mut self.password)
                    .labelled_by(label.id);
                let hash = md5::compute(&self.password);
                self.key = *hash.0.split_array_ref::<8>().0;
            });

            ui.separator();

            ui.horizontal(|ui| {
                if let Some(handle) = &self.handle {
                    ui.spinner();
                    if handle.is_finished() {
                        self.handle.take();
                    }
                } else {
                    if ui.button("Encrypt").clicked() {
                        if let Some(path) = rfd::FileDialog::new().pick_file() {
                            self.handle = Some(tokio::spawn(encrypt(path, self.key)));
                        }
                    }
                    if ui.button("Decrypt").clicked() {
                        if let Some(path) = rfd::FileDialog::new().pick_file() {
                            self.handle = Some(tokio::spawn(decrypt(path, self.key)));
                        }
                    }
                }
            });
        });
    }
}

async fn encrypt(path: PathBuf, key: Key) {
    let mut input_file = File::open(&path).unwrap();
    let mut output_path = path;
    output_path.add_extension("encrypted");
    let mut output_file = File::options()
        .create(true)
        .write(true)
        .truncate(true)
        .open(output_path)
        .unwrap();
    let mut bytes = Vec::new();
    input_file.read_to_end(&mut bytes).unwrap();
    pad(&mut bytes, 16);
    let output = rc5::encrypt::<u64>(&key, &bytes, ROUNDS).unwrap();
    output_file.write_all(&output).unwrap();
}

async fn decrypt(path: PathBuf, key: Key) {
    let mut input_file = File::open(&path).unwrap();
    let output_path = PathBuf::from(path.file_stem().unwrap());
    let mut output_file = File::options()
        .create(true)
        .write(true)
        .truncate(true)
        .open(output_path)
        .unwrap();
    let mut bytes = Vec::new();
    input_file.read_to_end(&mut bytes).unwrap();
    let mut output = rc5::decrypt::<u64>(&key, &bytes, ROUNDS).unwrap();
    unpad(&mut output);
    output_file.write_all(&output).unwrap();
}

fn pad(bytes: &mut Vec<u8>, block_size: usize) {
    let padding_len = block_size - (bytes.len() % block_size);
    bytes.extend(vec![padding_len as u8; padding_len]);
}

fn unpad(bytes: &mut Vec<u8>) {
    if let Some(&last_byte) = bytes.last() {
        let padding_len = last_byte as usize;
        if bytes.len() >= padding_len {
            bytes.truncate(bytes.len() - padding_len);
        }
    }
}
