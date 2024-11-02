#![feature(path_add_extension)]

use std::{
    fmt,
    fs::{read_to_string, File},
    io::{Read, Write},
    path::PathBuf,
};

use dsa::{
    pkcs8::{
        der::{Decode, Encode},
        DecodePrivateKey, EncodePrivateKey,
    },
    signature::{Signer, Verifier},
    Components, KeySize, Signature, SigningKey, VerifyingKey,
};
use eframe::egui;
use sha2::{Digest, Sha256};

#[tokio::main]
async fn main() -> eframe::Result {
    let options = eframe::NativeOptions {
        viewport: egui::ViewportBuilder::default().with_inner_size([400.0, 240.0]),
        ..Default::default()
    };
    eframe::run_native("Lab 5", options, Box::new(|_| Ok(Box::<App>::default())))
}

struct Keypair {
    signing_key: SigningKey,
    verifying_key: VerifyingKey,
}

#[derive(Default)]
struct App {
    action: Action,
    keypair: Option<Keypair>,
    signature: Option<String>,
    verify_result: Option<bool>,
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.horizontal(|ui| {
                ui.label("Keypair");
                if self.keypair.is_none() {
                    if ui.button("Import").clicked() {
                        if let Some(path) = rfd::FileDialog::new().pick_file() {
                            let bytes = std::fs::read(path).unwrap();
                            let signing_key = SigningKey::from_pkcs8_der(&bytes).unwrap();
                            let verifying_key = signing_key.verifying_key().to_owned();
                            self.keypair = Some(Keypair {
                                signing_key,
                                verifying_key,
                            });
                            self.verify_result = None;
                            self.signature = None;
                            self.action = Action::default();
                        }
                    }
                    if ui.button("Generate").clicked() {
                        let mut csprng = rand::thread_rng();
                        let components = Components::generate(&mut csprng, KeySize::DSA_2048_256);
                        let signing_key = SigningKey::generate(&mut csprng, components).to_owned();
                        let verifying_key = signing_key.verifying_key().to_owned();
                        self.keypair = Some(Keypair {
                            signing_key,
                            verifying_key,
                        });
                        self.signature = None;
                        self.verify_result = None;
                        self.action = Action::default();
                    }
                } else if let Some(Keypair { signing_key, .. }) = &self.keypair {
                    if ui.button("Export").clicked() {
                        if let Some(path) = rfd::FileDialog::new().save_file() {
                            let signing_key_der = signing_key.to_pkcs8_der().unwrap();
                            std::fs::write(path, signing_key_der.as_bytes()).unwrap();
                            self.signature = None;
                            self.verify_result = None;
                            self.action = Action::default();
                        }
                    }
                    if ui.button("Clear").clicked() {
                        self.signature = None;
                        self.keypair = None;
                        self.verify_result = None;
                        self.action = Action::default();
                    }
                }
            });

            ui.vertical(|ui| {
                if let Some(Keypair {
                    signing_key,
                    verifying_key,
                }) = &self.keypair
                {
                    ui.horizontal(|ui| {
                        ui.menu_button(self.action.to_string(), |ui| {
                            if ui.button(Action::default().to_string()).clicked() {
                                self.action = Action::default();
                                self.verify_result = None;
                                ui.close_menu();
                            }
                            if ui.button(Action::Verify(None).to_string()).clicked() {
                                self.action = Action::Verify(None);
                                self.signature = None;
                                ui.close_menu();
                            }
                        });
                        if let Action::Sign { input } = &self.action {
                            ui.menu_button(
                                if matches!(input, Input::String(_)) {
                                    "Text"
                                } else {
                                    "File"
                                },
                                |ui| {
                                    if ui.button("Text").clicked() {
                                        self.action = Action::default();
                                        ui.close_menu();
                                    }
                                    if ui.button("File").clicked() {
                                        self.action = Action::Sign {
                                            input: Input::File(None),
                                        };
                                        self.signature = None;
                                        ui.close_menu();
                                    }
                                },
                            );
                        }
                    });
                    match &mut self.action {
                        Action::Sign { input } => {
                            match input {
                                Input::String(s) => {
                                    ui.text_edit_singleline(s);
                                    let signature = sign_message(s.as_bytes(), signing_key);
                                    self.signature = Some(signature);
                                }
                                Input::File(p) => {
                                    ui.horizontal(|ui| {
                                        if ui.button("Select").clicked() {
                                            if let Some(path) = rfd::FileDialog::new().pick_file() {
                                                let mut file = File::open(&path).unwrap();
                                                let mut content = Vec::new();
                                                file.read_to_end(&mut content).unwrap();

                                                let signature = sign_message(&content, signing_key);
                                                self.signature = Some(signature.clone());
                                                *p = Some(path);
                                            }
                                        }
                                        if let Some(p) = p {
                                            ui.label(format!("{}", p.to_string_lossy()));
                                        }
                                        if p.is_some() && ui.button("x").clicked() {
                                            self.signature = None;
                                            *p = None;
                                        }
                                    });
                                }
                            };
                        }
                        Action::Verify(p) => {
                            ui.horizontal(|ui| {
                                if ui.button("Select").clicked() {
                                    if let Some(path) = rfd::FileDialog::new()
                                        .set_title("File to verify")
                                        .pick_file()
                                    {
                                        let mut file = File::open(&path).unwrap();
                                        let mut content = Vec::new();
                                        file.read_to_end(&mut content).unwrap();

                                        if let Some(sig_path) = rfd::FileDialog::new()
                                            .set_title("Signature")
                                            .pick_file()
                                        {
                                            let sig_hex = read_to_string(sig_path).unwrap();
                                            let signature =
                                                Signature::from_der(&hex::decode(sig_hex).unwrap())
                                                    .unwrap();
                                            self.verify_result = Some(verify_signature(
                                                &content,
                                                &signature,
                                                verifying_key,
                                            ));
                                            *p = Some(path);
                                        }
                                    }
                                }
                                if let Some(p) = p {
                                    ui.label(format!("{}", p.to_string_lossy()));
                                }
                                if p.is_some() && ui.button("x").clicked() {
                                    self.verify_result = None;
                                    *p = None;
                                }
                            });
                            if let Some(result) = self.verify_result {
                                if result {
                                    ui.label("Signature matches!");
                                } else {
                                    ui.label("Signature does not match!");
                                }
                            }
                        }
                    }
                }
                ui.horizontal(|ui| {
                    if matches!(&self.action, Action::Sign { .. }) {
                        if let Some(sig) = &self.signature {
                            if ui.button("Export").clicked() {
                                if let Some(path) = rfd::FileDialog::new().save_file() {
                                    let mut signature_file =
                                        File::create(path.with_extension("sig")).unwrap();
                                    signature_file.write_all(sig.as_bytes()).unwrap();
                                }
                            }
                            ui.with_layout(egui::Layout::default().with_main_wrap(true), |ui| {
                                ui.label(format!("Signature: {}", sig))
                            });
                        }
                    }
                });
            });
        });
    }
}

enum Input {
    String(String),
    File(Option<PathBuf>),
}

enum Action {
    Sign { input: Input },
    Verify(Option<PathBuf>),
}

impl Default for Action {
    fn default() -> Self {
        Self::Sign {
            input: Input::String(String::new()),
        }
    }
}

fn sign_message(message: &[u8], signing_key: &SigningKey) -> String {
    let hash = Sha256::digest(message);
    let signature = signing_key.sign(&hash);
    hex::encode(signature.to_der().unwrap())
}

fn verify_signature(message: &[u8], signature: &Signature, verifying_key: &VerifyingKey) -> bool {
    let hash = Sha256::digest(message);
    verifying_key.verify(&hash, signature).is_ok()
}

impl fmt::Display for Action {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Self::Sign { .. } => write!(f, "Sign"),
            Self::Verify(_) => write!(f, "Verify"),
        }
    }
}
