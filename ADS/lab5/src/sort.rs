use crate::data::Data;

pub fn sort(input: &mut [Data], res: &mut Vec<Vec<Data>>) {
    if input.len() < 2 {return;}
    
    let len = input.len();
    let mid = len / 2;
    sort(&mut input[..mid], res);
    sort(&mut input[mid..], res);

    let mut tmp = Vec::with_capacity(len);
    let mut i = 0;
    let mut j = mid;

    while i < mid && j < len {
        if input[i] < input[j] {
            tmp.push(input[i]);
            i += 1;
        } else {
            tmp.push(input[j]);
            j += 1;
        }
    }
    if i < mid {
        tmp.extend_from_slice(&input[i..mid]);
    } else if j < len {
        tmp.extend_from_slice(&input[j..len]);
    }
    res.push(tmp.to_vec());

    input.copy_from_slice(&tmp[..]);
}

