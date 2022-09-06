use crate::data::Data;

pub struct Sorted;

impl Sorted {
    pub fn sort(input: &mut Vec<Data>) -> Vec<Vec<Data>> {
        let len = input.len();
        let gaps = GapSequence::new(len);
        let mut res = vec![input.clone()];

        for gap in gaps {
            for i in gap..len {
                let mut j = i;

                while j >= gap && input[j - gap] > input[j] {
                    input.swap(j - gap, j);
                    res.push(input.clone());

                    j -= gap;
                }
            }
        }
        res
    }
}

struct GapSequence {
    gap: usize,
}

impl GapSequence {
    fn new(n: usize) -> Self {
        Self { gap: n }
    }
}

impl Iterator for GapSequence {
    type Item = usize;

    fn next(&mut self) -> Option<usize> {
        self.gap /= 2;

        if self.gap > 0 {
            Some(self.gap)
        } else {
            None
        }
    }
}
