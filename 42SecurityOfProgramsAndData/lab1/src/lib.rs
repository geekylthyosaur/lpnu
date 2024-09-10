use std::ops;

pub struct Random<T> {
    /// Comparision module
    m: T,
    /// Multiplier
    a: T,
    /// Increment
    c: T,
    /// Seed
    x_0: T,
    x: T,
}

impl<T: Copy> Random<T> {
    pub fn new(m: T, a: T, c: T, x_0: T) -> Self {
        Self {
            m,
            a,
            c,
            x_0,
            x: x_0,
        }
    }
}

impl<T> Random<T>
where
    T: Copy + ops::Add<Output = T> + ops::Mul<Output = T> + ops::Rem<Output = T>,
    T: Copy + PartialEq + std::hash::Hash + Eq,
    Random<T>: Iterator<Item = T>,
{
    pub fn period(&mut self) -> usize {
        let mut seen = std::collections::HashSet::new();
        let mut count = 0;

        while seen.insert(self.x) {
            count += 1;
            self.x = (self.a * self.x + self.c) % self.m;
        }

        count
    }
}

impl<T> Iterator for Random<T>
where
    T: Copy + ops::Add<Output = T> + ops::Mul<Output = T> + ops::Rem<Output = T>,
{
    type Item = T;

    fn next(&mut self) -> Option<Self::Item> {
        self.x = (self.a * self.x + self.c) % self.m;
        Some(self.x)
    }
}
