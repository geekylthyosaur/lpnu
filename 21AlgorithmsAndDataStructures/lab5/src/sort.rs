use crate::data::Data;

fn merge(arr: &mut Vec<Data>, res: &mut Vec<Vec<Data>>, l: usize, m: usize, r: usize) {
    let (mut i, mut j, mut k);
    let n1 = m - l + 1;
    let n2 = r - m;
 
    let mut L = Vec::new();
    let mut R = Vec::new();
 
    for i in 0..n1 {
        L.push(arr[l + i]);
    }
    for j in 0..n2 {
        R.push(arr[m + 1 + j]);
    }
    res.push(L.clone());
    res.push(R.clone());
 
    i = 0;
    j = 0;
    k = l;

    while i < n1 && j < n2 {
        if L[i] >= R[j] {
            arr[k] = L[i];
            i += 1;
        } else {
            arr[k] = R[j];
            j += 1;
        }
        k += 1;
    }
 
    while i < n1 {
        arr[k] = L[i];
        i += 1;
        k += 1;
    }
    while j < n2 {
        arr[k] = R[j];
        j += 1;
        k += 1;
    }
}
 
pub fn merge_sort(arr: &mut Vec<Data>, res: &mut Vec<Vec<Data>>, l: usize, r: usize) {
    if l < r {
        let m = l + (r - l) / 2;
 
        merge_sort(arr, res, l, m);
        merge_sort(arr, res, m + 1, r);
 
        merge(arr, res, l, m, r);
    }
}
