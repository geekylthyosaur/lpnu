use anyhow::{ensure, Context, Result};
use std::collections::HashMap;

fn z_array(string: &str) -> Result<Vec<usize>> {
    let len = string.len();
    ensure!(len > 1, "Length of string must be greater than 1");

    let mut z_arr = vec![0_usize; len];
    z_arr[0] = len;

    let chars = string.as_bytes();

    // Initial comparison of s[1:] with prefix
    for i in 1..len {
        if chars[i] != chars[i - 1] {
            break;
        }

        z_arr[1] += 1;
    }

    let (mut right, mut left) = (0, 0);
    if z_arr[1] > 0 {
        right = z_arr[1];
        left = 1;
    }

    for k in 2..len {
        // Case 1
        if k > right {
            for i in k..len {
                if chars[i] == chars[i - k] {
                    z_arr[k] += 1;
                } else {
                    break;
                }
            }
            right = k + z_arr[k] - 1;
            left = k;
        }
        // Calculate length of beta
        else if (right - k + 1) > z_arr[k - left] {
            z_arr[k] = z_arr[k - left];
        }
        // Compare characters just past r
        else {
            let mut matches = 0;
            for i in right + 1..len {
                if chars[i] != chars[i - k] {
                    break;
                }
                matches += 1;
            }

            left = k;
            right += matches;
            z_arr[k] = right - k + 1
        }
    }

    Ok(z_arr)
}

fn n_array(string: &str) -> Result<Vec<usize>> {
    let mut n_arr = z_array(string.chars().rev().collect::<String>().as_str())
        .with_context(|| format!("Failed to find Z array for string \"{}\"", string))?;
    n_arr.reverse();
    Ok(n_arr)
}

fn big_l_prime_array(pattern: &str, n_arr: &[usize]) -> Vec<usize> {
    let len = pattern.len();
    let mut l_prime = vec![0; len];

    for (j, &n_j) in n_arr.iter().enumerate() {
        let i = len - n_j;
        if i < len {
            l_prime[i] = j + 1;
        }
    }

    l_prime
}

fn big_l_array(pattern: &str, l_prime_arr: &[usize]) -> Vec<usize> {
    let len = pattern.len();
    let mut l_arr = vec![0; len];
    l_arr[1] = l_prime_arr[1];

    for i in 2..len {
        l_arr[i] = *[l_arr[i - 1], l_prime_arr[i]].iter().max().unwrap();
    }

    l_arr
}

fn small_l_prime_array(n_arr: &[usize]) -> Vec<usize> {
    let len = n_arr.len();
    let mut small_l_prime_arr = vec![0; len];

    for i in 0..len {
        // Prefix matching a suffix
        if n_arr[i] == i + 1 {
            small_l_prime_arr[len - i - 1] = i + 1;
        }
    }

    for i in (0..len - 1).rev() {
        // "Smear" them out to the left
        if small_l_prime_arr[i] == 0 {
            small_l_prime_arr[i] = small_l_prime_arr[i + 1];
        }
    }

    small_l_prime_arr
}

fn good_suffix_table(pattern: &str) -> Result<(Vec<usize>, Vec<usize>, Vec<usize>)> {
    let n_arr = n_array(pattern)?;
    let l_prime_arr = big_l_prime_array(pattern, n_arr.as_slice());
    let big_l_arr = big_l_array(pattern, l_prime_arr.as_slice());
    let small_l_prime_arr = small_l_prime_array(n_arr.as_slice());

    Ok((l_prime_arr, big_l_arr, small_l_prime_arr))
}

fn dense_bad_char_table(
    pattern: &str,
    alpha_map: &HashMap<char, usize>,
) -> Result<Vec<Vec<usize>>> {
    let mut table: Vec<Vec<usize>> = Vec::new();
    let mut next = vec![0_usize; alpha_map.len()];

    for (i, character) in pattern.chars().enumerate() {
        ensure!(
            alpha_map.contains_key(&character),
            format!("{} not found in alphabet", character)
        );

        table.push(next.clone());
        let &index = alpha_map.get(&character).unwrap();
        next[index] = i + 1;
    }

    Ok(table)
}

pub struct BoyerMoore {
    alpha_map: HashMap<char, usize>,
    bad_char: Vec<Vec<usize>>,
    big_l: Vec<usize>,
    small_l_prime: Vec<usize>,
}

impl BoyerMoore {
    pub fn new(pattern: &str, alphabet: &str) -> Result<Self> {
        let mut alpha_map = HashMap::new();
        for (i, c) in alphabet.chars().enumerate() {
            alpha_map.insert(c, i);
        }
        let bad_char = dense_bad_char_table(pattern, &alpha_map)?;
        let (_, big_l, small_l_prime) = good_suffix_table(pattern)?;

        Ok(Self {
            alpha_map,
            bad_char,
            big_l,
            small_l_prime,
        })
    }

    pub fn bad_char_rule(&self, offset: usize, character: char) -> Result<usize> {
        ensure!(
            self.alpha_map.contains_key(&character),
            format!("{} not found in alphabet", character)
        );
        ensure!(
            offset < self.bad_char.len(),
            format!("Invalid offset {}", offset)
        );

        let &index = self.alpha_map.get(&character).unwrap();
        Ok((offset as isize - (self.bad_char[offset][index] as isize - 1)) as usize)
    }

    pub fn good_suffix_rule(&self, offset: usize) -> Result<usize> {
        let len = self.big_l.len();
        ensure!(offset < len, format!("Invalid offset {}", offset));

        if offset == len - 1 {
            return Ok(0);
        }

        let offset = offset + 1; // offset points to the leftmost matching position of p

        if self.big_l[offset] > 0 {
            return Ok(len - self.big_l[offset]);
        }

        Ok(len - self.small_l_prime[offset])
    }

    pub fn match_skip(&self) -> usize {
        self.small_l_prime.len() - self.small_l_prime[1]
    }
}
