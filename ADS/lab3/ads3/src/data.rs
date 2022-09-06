use fake::{Dummy, Fake};

#[derive(Debug, Clone, PartialEq, Dummy)]
pub struct Data {
    #[dummy()]
    pub v: [f32; 2],
}

impl Data {
    pub fn new(len: usize) -> Vec<Self> {
        fake::vec![Data; len]
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
        self.v[0].partial_cmp(&other.v[0])
    }
}
