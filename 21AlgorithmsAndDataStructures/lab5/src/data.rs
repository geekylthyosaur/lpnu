use fake::{Dummy, Fake};

#[derive(Debug, Clone, Copy, PartialEq, Dummy)]
pub struct Data {
    #[dummy(faker = "-1.0..1.0")]
    pub v: f32,
}

impl Data {
    pub fn new(len: usize) -> Vec<Self> {
        fake::vec![Data; len]
            .iter_mut()
            .map(|x| {
                if x.v < 0. {
                    Data { v: f32::sin(x.v) }
                } else { *x }
            })
            .collect::<Vec<Data>>()
    }

    pub fn diff(a: &Vec<Data>, b: &Vec<Data>) -> Vec<usize> {
        let mut res = Vec::new();

        for i in 0..a.len() {
            if a.get(i) != b.get(i) {
                res.push(i);
            }
        }

        res
    }
}

impl PartialOrd for Data {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        self.v.partial_cmp(&other.v)
    }
}
