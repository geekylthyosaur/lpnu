#![feature(core_intrinsics)]
#[derive(Debug, Clone, Copy)]
pub struct Random {
    /// Comparision module
    m: usize,
    /// Multiplier
    a: usize,
    /// Increment
    c: usize,
    /// Seed
    x: usize,
}

impl Random {
    pub fn new(m: usize, a: usize, c: usize, x_0: usize) -> Self {
        Self { m, a, c, x: x_0 }
    }
}

impl Random {
    pub fn period(&mut self) -> usize {
        let mut a = self.clone();
        let mut b = self.clone();
        let mut x = a.next();
        b.next();
        let mut y = b.next();
        let mut count = 1;
        while x != y {
            count += 1;
            x = a.next();
            b.next();
            y = b.next();
        }
        count
    }
}

use std::intrinsics::unchecked_rem;

impl Iterator for Random {
    type Item = usize;

    fn next(&mut self) -> Option<Self::Item> {
        let x = self.x;
        self.x =
            unsafe { unchecked_rem(self.a.unchecked_mul(self.x).unchecked_add(self.c), self.m) };
        Some(x)
    }
}
