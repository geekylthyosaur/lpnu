use std::{
    fs::File,
    io::{stdin, stdout, Write},
};

fn main() {
    let n = input("N = ").parse::<usize>().expect("Invalid input");

    let mut random = Random {
        m: usize::pow(2, 12) - 1,
        a: usize::pow(4, 5),
        c: 2,
        x_0: 8,
    };

    print(format!("Period: {}\n", random.period()));

    for x in random.take(n) {
        print(format!("{x}\n"));
    }
}

struct Random {
    m: usize,
    a: usize,
    c: usize,
    x_0: usize,
}

impl Random {
    fn period(&mut self) -> usize {
        let x_0 = self.x_0;
        self.take_while(|&x| x != x_0).count()
    }
}

impl Iterator for Random {
    type Item = usize;

    fn next(&mut self) -> Option<Self::Item> {
        let x_1 = (self.a * self.x_0 + self.c) % self.m;
        self.x_0 = x_1;
        Some(x_1)
    }
}

fn input(prompt: &str) -> String {
    let mut input = String::new();

    print!("{prompt}");
    stdout().flush().unwrap();
    stdin().read_line(&mut input).expect("Failed to read line");

    input.trim().to_owned()
}

fn print(args: String) {
    let mut file = File::options()
        .create(true)
        .append(true)
        .open("output.txt")
        .unwrap();
    let mut handle = stdout().lock();
    file.write_all(args.as_bytes()).unwrap();
    handle.write_all(args.as_bytes()).unwrap();
}
