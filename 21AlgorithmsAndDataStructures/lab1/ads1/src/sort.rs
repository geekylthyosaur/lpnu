use crate::data::Data;

pub struct Sorted;

impl Sorted {
    pub fn sort(v: &mut Vec<Data>) -> Vec<(usize, usize)> {
        remove_above_avg_price(v);
        let mut sorted = false;
        let mut res = Vec::new();
        for i in 0..v.len() {
            for j in 0..(v.len() - 1 - i) {
                sorted = true;
                if v[j] > v[j + 1] {
                    v.swap(j, j + 1);
                    res.push((j, j + 1));
                    sorted = false;
                }
            }
            if sorted { break }
        }
        res
    }
}

fn remove_above_avg_price(v: &mut Vec<Data>) {
    let avg_price = v.iter().map(|d| d.price).sum::<f32>() / v.len() as f32;
    v.retain(|d| d.price < avg_price);
}
