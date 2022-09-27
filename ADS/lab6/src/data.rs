use fake::{Dummy, Fake};

#[derive(Debug, Clone, Copy, PartialEq, Dummy)]
pub struct Data {
    #[dummy(faker = "0..100")]
    pub v: usize,
}

impl Data {
    pub fn new(len: usize) -> Vec<Self> {
        let mut data = fake::vec![Data; len];
        data.dedup();
        data

    }

    pub fn diff(a: &Vec<Data>, b: &Vec<Data>) -> Vec<usize> {
        let mut res = Vec::new();

        for i in 0..a.len() {
            if a[i] != b[i] {
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

