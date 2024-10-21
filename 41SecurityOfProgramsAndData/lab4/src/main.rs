#![feature(path_add_extension)]

use std::{
    fmt,
    fs::File,
    io::{Read, Write},
    path::PathBuf,
};

use eframe::egui;
use rsa::{Pkcs1v15Encrypt, RsaPrivateKey, RsaPublicKey};
use tokio::task::JoinHandle;

type RsaKeypair = (RsaPublicKey, RsaPrivateKey);

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
    action: Action,
    keypair: Option<RsaKeypair>,
    handle: Option<JoinHandle<()>>,
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.horizontal(|ui| {
                ui.label("Keypair");
                if self.keypair.is_none() {
                    if ui.button("Import").clicked() {
                        todo!()
                    }
                    if ui.button("Generate").clicked() {
                        let mut rng = rand::thread_rng();
                        let bits = 2048;
                        let private = RsaPrivateKey::new(&mut rng, bits).unwrap();
                        let public = RsaPublicKey::from(&private);
                        self.keypair = Some((public, private));
                    }
                } else {
                    if ui.button("Export").clicked() {
                        todo!()
                    }
                    if ui.button("Clear").clicked() {
                        self.keypair = None;
                    }
                }
            });

            ui.vertical(|ui| {
                ui.menu_button(self.action.to_string(), |ui| {
                    if ui.button(Action::Encrypt.to_string()).clicked() {
                        self.action = Action::Encrypt;
                        ui.close_menu();
                    }
                    if ui.button(Action::Decrypt.to_string()).clicked() {
                        self.action = Action::Decrypt;
                        ui.close_menu();
                    }
                });

                if let Some(keypair) = self.keypair.clone() {
                    if ui.button("Choose File").clicked() {
                        if let Some(path) = rfd::FileDialog::new().pick_file() {
                            self.handle = Some(match self.action {
                                Action::Encrypt => tokio::spawn(encrypt(path, keypair)),
                                Action::Decrypt => tokio::spawn(decrypt(path, keypair)),
                            });
                        }
                    }
                }

                if let Some(handle) = &self.handle {
                    ui.spinner();
                    if handle.is_finished() {
                        self.handle.take();
                    }
                } else {
                    ui.label(self.action.to_string());
                }
            });
        });
    }
}

const CHUNK_SIZE: usize = 190;
const RSA_KEY_SIZE: usize = 2048;

async fn encrypt(path: PathBuf, keypair: RsaKeypair) {
    let mut input_file = File::open(&path).unwrap();
    let mut output_path = path.clone();
    output_path.set_extension("encrypted");
    let mut output_file = File::options()
        .create(true)
        .write(true)
        .truncate(true)
        .open(output_path)
        .unwrap();

    let mut bytes = Vec::new();
    input_file.read_to_end(&mut bytes).unwrap();

    let mut rng = rand::thread_rng();
    let mut encrypted = Vec::new();

    let mut offset = 0;
    while offset < bytes.len() {
        let end = (offset + CHUNK_SIZE).min(bytes.len());
        let mut chunk = bytes[offset..end].to_vec();

        if chunk.len() < CHUNK_SIZE {
            chunk.resize(CHUNK_SIZE, 0);
        }

        let enc_chunk = keypair
            .0
            .encrypt(&mut rng, Pkcs1v15Encrypt, &chunk)
            .unwrap();
        encrypted.extend(enc_chunk);
        offset += CHUNK_SIZE;
    }

    output_file.write_all(&encrypted).unwrap();
}

async fn decrypt(path: PathBuf, keypair: RsaKeypair) {
    let mut input_file = File::open(&path).unwrap();
    let output_path = path.with_file_name(path.file_stem().unwrap());
    let mut output_file = File::options()
        .create(true)
        .write(true)
        .truncate(true)
        .open(output_path)
        .unwrap();

    let mut bytes = Vec::new();
    input_file.read_to_end(&mut bytes).unwrap();

    let mut decrypted = Vec::new();
    let mut offset = 0;

    while offset < bytes.len() {
        let end = (offset + (RSA_KEY_SIZE / 8)).min(bytes.len());
        let chunk = &bytes[offset..end];

        let dec_chunk = keypair.1.decrypt(Pkcs1v15Encrypt, chunk).unwrap();
        decrypted.extend(dec_chunk);
        offset += RSA_KEY_SIZE / 8;
    }

    output_file.write_all(&decrypted).unwrap();
}

#[derive(Default)]
enum Action {
    #[default]
    Encrypt,
    Decrypt,
}

impl fmt::Display for Action {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Encrypt => write!(f, "Encrypt"),
            Self::Decrypt => write!(f, "Decrypt"),
        }
    }
}
