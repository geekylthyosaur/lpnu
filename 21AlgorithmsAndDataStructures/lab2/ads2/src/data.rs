use fake::{Dummy, Fake};

#[derive(Debug, Clone, PartialEq, Dummy)]
pub struct Data {
    #[dummy()]
    pub v: f32,
}

impl Data {
    pub fn new(len: usize) -> Vec<Self> {
        let mut vec = fake::vec![Data; len];
        vec.iter_mut()
            .step_by(2)
            .for_each(|x| x.v = f32::sqrt(f32::abs(x.v - 10.)));
        vec
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
