use fake::{faker::lorem::en::*, Fake, Dummy};

#[derive(Debug, Clone, PartialEq, Eq, Ord, Dummy)]
pub struct Book {
    #[dummy(faker = "Word()")]
    name: String, 
    #[dummy(faker = "20..100")]
    price: usize,
}

#[derive(Debug)]
pub struct Arr {
    arr: Vec<Book>,
    len: usize,
}

impl Arr {
    pub fn new(len: usize) -> Self {
        let mut arr = fake::vec![Book; len];
        arr.sort();
        Self { arr, len }
    }

    pub fn search(&self, price: usize) -> (Option<String>, usize) {
        let mut left_i = 0;
        let mut right_i = if let Some(res) = self.len.checked_sub(1) { res } else { return (None, 0) };
        let mut cmp_counter = 0;

        while left_i <= right_i {
            cmp_counter += 1;
            let mid = (left_i + right_i) / 2;
            print!("Left: {: <3} Mid: {: <3} Right: {: <3}\t", left_i, mid, right_i);
            match self.arr[mid].price {
                v if v < price => {
                    cmp_counter += 1;
                    println!("{} < {}", v, price);
                    left_i = mid + 1;
                },
                v if v > price => {
                    cmp_counter += 2;
                    println!("{} > {}", v, price);
                    right_i = if let Some(res) = mid.checked_sub(1) { res } else { break; };
                },
                v => {
                    cmp_counter += 2;
                    println!("{} == {}", v, price);
                    return (Some(self.arr[mid].name.clone()), cmp_counter);
                }
            }
        }
        (None, cmp_counter)
    }

    pub fn print(&self) {
        for i in &self.arr {
            println!("{: <20} {}", i.name, i.price);
        }
    }
}

impl PartialOrd for Book {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        self.price.partial_cmp(&other.price)
    }
}
