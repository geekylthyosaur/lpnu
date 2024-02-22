use crate::data::Data;

pub struct Sorted;

impl Sorted {
    pub fn sort(mut v: Vec<Data>) -> Vec<Vec<Data>> {
        let mut res = vec![v.clone()];
        for i in 0..(v.len() - 1) {
            let mut min = i;
            for j in (i + 1)..v.len() {
                if v[j] < v[min] {
                    min = j;
                }
            }
            if min != i {
                v.swap(i, min);
                res.push(v.clone());
            }
        }
        res
    }
}
