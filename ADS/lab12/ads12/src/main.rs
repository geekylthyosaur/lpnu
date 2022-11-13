use std::{
    io::{self, Write},
    str::from_utf8,
    thread, time,
};
use eframe::egui::{self, text_edit::TextEdit};
use fake::{faker::lorem::en::*, Fake};

use anyhow::{Context, Result};
use log::error;
use termcolor::{Color, ColorChoice, ColorSpec, StandardStream, WriteColor};

use boyer_moore::BoyerMoore;

/// Prints text and pattern with appropriate colors.
fn visualize(
    mut stdout: &mut StandardStream,
    text: &str,
    pattern: &str,
    t_off: usize,
    p_off: usize,
    matched: bool,
    sleep_time: f32,
) -> Result<()> {
    const ARROW_HEAD: &str = "\u{0025C0}";
    const ARROW_BODY: &str = "\u{01F89C}";
    let mut spec = ColorSpec::new();

    for i in (p_off..pattern.len()).rev() {
        if matched || i > p_off {
            write!(&mut stdout, "{}", &text[..t_off + i])?;
            stdout.set_color(spec.set_bold(true).set_fg(Some(Color::Green)))?;
            write!(&mut stdout, "{}", &pattern[i..])?;
            stdout.reset()?;
            writeln!(&mut stdout, "{}", &text[t_off + pattern.len()..])?;

            write!(&mut stdout, "{}{}", " ".repeat(t_off), &pattern[..i],)?;
            stdout.set_color(spec.set_bold(true).set_fg(Some(Color::Green)))?;
            writeln!(&mut stdout, "{}", &pattern[i..])?;
        } else {
            write!(&mut stdout, "{}", &text[..t_off + p_off])?;
            stdout.set_color(spec.set_bold(true).set_fg(Some(Color::Red)))?;
            write!(&mut stdout, "{}", &text[t_off + p_off..t_off + p_off + 1])?;
            stdout.set_color(spec.set_bold(true).set_fg(Some(Color::Green)))?;
            write!(&mut stdout, "{}", &pattern[p_off + 1..])?;
            stdout.reset()?;
            writeln!(&mut stdout, "{}", &text[t_off + pattern.len()..])?;

            write!(&mut stdout, "{}{}", " ".repeat(t_off), &pattern[..p_off],)?;
            stdout.set_color(spec.set_bold(true).set_fg(Some(Color::Red)))?;
            write!(&mut stdout, "{}", &pattern[p_off..p_off + 1])?;
            stdout.set_color(spec.set_bold(true).set_fg(Some(Color::Green)))?;
            writeln!(&mut stdout, "{}", &pattern[p_off + 1..])?;
        }
        stdout.reset()?;

        write!(&mut stdout, "{}", " ".repeat(t_off + i),)?;
        stdout.set_color(spec.set_bold(true).set_fg(Some(Color::Rgb(127, 127, 127))))?;
        writeln!(
            &mut stdout,
            "{}{}",
            ARROW_HEAD,
            ARROW_BODY.repeat(pattern.len() - i - 1),
        )?;
        stdout.reset()?;

        thread::sleep(time::Duration::from_secs_f32(sleep_time));
        if i > p_off {
            print!("\u{1B}[3F");
            stdout.flush().with_context(|| "Failed to flush stdout")?;
        }
    }

    println!();
    Ok(())
}

/// Searches for all occurrences of `pattern` in `text`.
fn boyer_moore_search(
    pattern: &str,
    bm: BoyerMoore,
    text: &str,
    sleep_time: f32,
    stdout: &mut StandardStream,
    skip: bool,
) -> Result<(Vec<usize>, i32, i32)> {
    let mut occurrences = Vec::new();
    let mut alignments = 0;
    let mut comparisons = 0;

    let pattern = pattern.as_bytes();
    let text = text.as_bytes();
    let mut i = 0;

    while i < text.len() - pattern.len() + 1 {
        let mut shift = 1;
        let mut mismatched = false;
        let mut mismatch_index = 0;
        let mut skip_bc = 0;
        let mut _skip_gs = 0;
        alignments += 1;

        for j in (0..pattern.len()).rev() {
            comparisons += 1;

            if pattern[j] != text[i + j] {
                skip_bc = bm.bad_char_rule(j, text[i + j] as char)?;
                _skip_gs = bm.good_suffix_rule(j)?;
                shift = *[shift, skip_bc].iter().max().unwrap();
                mismatched = true;
                mismatch_index = j;
                break;
            }
        }

        if !mismatched {
            occurrences.push(i);
            _skip_gs = bm.match_skip();
        }
        if !skip {
        visualize(
            stdout,
            from_utf8(text)?,
            from_utf8(pattern)?,
            i,
            mismatch_index,
            !mismatched,
            sleep_time,
        )?;
        println!("Comparisons: {}", comparisons);

        if i < text.len() - pattern.len() {
            if skip_bc > 0 {
                println!("Bad character shift: {}", skip_bc);
            }

            print!("Press Enter to continue ...\r");
            io::stdout()
                .flush()
                .with_context(|| "Failed to flush stdout")?;
            let mut _input = String::new();
            io::stdin()
                .read_line(&mut _input)
                .with_context(|| "Failed to read input from stdin")?;
            print!("\u{1B}[F\u{1B}[K");
            io::stdout()
                .flush()
                .with_context(|| "Failed to flush stdout")?;
        }

        println!();
        }
        i += shift;
    }

    Ok((occurrences, alignments, comparisons))
}

fn run(text: &str, pattern: &str, skip: bool) -> Result<()> {
    let mut stdout = StandardStream::stdout(ColorChoice::Auto);

    const ALPHABET: &str = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz ";

    const SLEEP_TIME: f32 = 0.25;

    let bm = BoyerMoore::new(pattern, ALPHABET)
        .with_context(|| "Failed to initialize Boyer-Moore object")?;
    println!();

    match boyer_moore_search(pattern, bm, text, SLEEP_TIME, &mut stdout, skip) {
        Ok((occurrences, _, _)) => println!(
            "Occurrences: {:#?}",
            occurrences,
        ),
        Err(err) => {
            for source in err.chain() {
                error!("{}", source);
            }
        }
    }

    Ok(())
}

struct App {
    data: String,
    str_to_search: String,
    found_index: Option<usize>,
    radio: Mode,
}

#[derive(PartialEq)]
enum Mode {
    Text,
    Enter,
}

impl Default for App {
    fn default() -> Self {
        Self {
            data: String::new(),
            str_to_search: String::new(),
            found_index: None,
            radio: Mode::Text,
        }
    }
}

impl eframe::App for App {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Boyer Moore algorithm");
            ui.horizontal(|ui| {
                ui.radio_value(&mut self.radio, Mode::Text, "Text");
                ui.radio_value(&mut self.radio, Mode::Enter, "Enter");
            });
            if self.radio == Mode::Text {
                if ui.button("Restart").clicked() {
                    print!("{}[2J", 27 as char);
                    self.data = Words(10..100).fake::<Vec<String>>().join(" ");
                    self.str_to_search = Word().fake::<String>();
                }
                ui.text_edit_singleline(&mut self.str_to_search);
                if ui.button("Search in second text").clicked() {
                    print!("{}[2J", 27 as char);
                    run(&self.data, &self.str_to_search, true).unwrap();
                }
                ui.label(format!("Found index: {:?}", self.found_index));
            } else {
                if ui.button("Restart").clicked() {
                    print!("{}[2J", 27 as char);
                    self.data = Words(10..100).fake::<Vec<String>>().join(" ");
                    self.str_to_search = Word().fake::<String>();
                }
                ui.text_edit_singleline(&mut self.str_to_search);
                ui.horizontal(|ui| {
                    if ui.button("Search in second text").clicked() {
                        print!("{}[2J", 27 as char);
                        run(&self.data, &self.str_to_search, false).unwrap();
                    }
                });
                if ui.button("Fill").clicked() {
                    self.str_to_search = "abc".to_string();
                    self.data = "abddbcdbcabcdabc".to_string();
                }
                ui.label(format!("Found index: {:?}", self.found_index));
            }
            ui.add(TextEdit::multiline(&mut self.data));
        });
    }
}

fn main() {
    env_logger::init();
    let options = eframe::NativeOptions::default();
    eframe::run_native("Stack", options, Box::new(|_cc| Box::new(App::default())));
}
