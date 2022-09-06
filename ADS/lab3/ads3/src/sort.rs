use crate::data::Data;

pub struct Sorted;

impl Sorted {
    pub fn sort(v: &mut Vec<Data>) -> Vec<Vec<Data>> {
        let mut res = vec![v.clone()];
        let mut sublistcount = v.len() / 2;
        while sublistcount > 0 {
            for start_position in 0..sublistcount {
                Self::gap_insertion_sort(v, start_position, sublistcount);
                res.push(v.clone());
            }
            sublistcount /= 2;
        }
        res
    }

    fn gap_insertion_sort(nlist: &mut Vec<Data>, start: usize, gap: usize) {
        for i in ((start + gap)..nlist.len()).step_by(gap) {
            let current_value = nlist[i].clone();
            let mut position = i;
            
            while position >= gap && nlist[position - gap] > current_value {
                nlist[position] = nlist[position - gap].clone();
                position = position - gap;
            }
            nlist[position] = current_value;
        }
    }
}
