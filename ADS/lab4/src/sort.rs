use crate::data::Data;

pub fn sort(input: &mut [Data]) -> Vec<Vec<Data>> {
    let mut res = vec![input.to_vec()];
    if input.len() > 1 {
        let pivot = lomuto_partition(&mut input[..], &mut res);
        sort(&mut input[..pivot]);
        sort(&mut input[pivot + 1..]);
    }
    res.push(input.to_vec());
    res
}

fn lomuto_partition(input: &mut [Data], res: &mut Vec<Vec<Data>>) -> usize {
    let pivot = input.len() - 1;
    let mut swap = 0;
    for i in 0..pivot {
        if input[i] < input[pivot] {
            if swap != i {
                input.swap(swap, i);
                res.push(input.to_vec());
            }
            swap += 1;
        }
    }

    if swap != pivot {
        input.swap(swap, pivot);
        res.push(input.to_vec());
    }
    swap
}
