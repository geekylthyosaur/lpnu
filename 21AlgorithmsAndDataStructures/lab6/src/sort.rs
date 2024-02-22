use crate::data::Data;
use crate::log;

fn get_max(arr: &mut Vec<Data>) -> usize {
    let mut temp: usize = arr[0].v;
    for i in 1..arr.len() {
        if temp < arr[i].v {
            temp = arr[i].v;
        }
    }
    return temp;
}

fn get_min(arr: &mut Vec<Data>) -> usize {
    let mut temp: usize = arr[0].v;
    for i in 1..arr.len() {
        if temp > arr[i].v {
            temp = arr[i].v;
        }
    }
    return temp;
}

pub fn sort(arr: &mut Vec<Data>, res: &mut Vec<Vec<Data>>) {
    let min: usize = get_min(arr);
    let max: usize  = get_max(arr);
    let mut z: usize = 0;

    let mut count = vec![0; max - min +1];

    for i in 0..arr.len() {
        count[arr[i].v - min] = count[arr[i].v - min] + 1;
    }

    for i in min..max+1 {
        while count[i - min] > 0 {
            arr[z].v = i;
            z += 1;
            count[i - min] = count[i - min] - 1;
            res.push(arr.clone());
        }
    }
}

