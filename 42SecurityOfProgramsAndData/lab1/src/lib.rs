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
        let mut rng = self.clone();
        let mut seen = std::collections::HashSet::new();
        let mut count = 0;
        while seen.insert(rng.next()) {
            count += 1;
            if count > 100 {
                let mut a = self.clone();
                let mut b = self.clone();
                _ = a.next();
                _ = b.next();
                _ = b.next();
                let mut count = 1;
                while a.x != b.x {
                    count += 1;
                    _ = a.next();
                    _ = b.next();
                    _ = b.next();
                }
                return count;
            }
        }
        count
    }
}

impl Iterator for Random {
    type Item = usize;

    fn next(&mut self) -> Option<Self::Item> {
        let x = self.x;
        self.x = (self.a.checked_mul(self.x)?.checked_add(self.c)?).checked_rem(self.m)?;
        Some(x)
    }
}
