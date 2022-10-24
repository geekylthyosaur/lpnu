use fake::{faker::lorem::en::*, Dummy, Fake};

#[derive(Debug, Clone, PartialEq, Ord, Eq, Dummy)]
pub struct Book {
    #[dummy(faker = "Word()")]
    name: String, 
    #[dummy(faker = "20..10000")]
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
        let mut right_i = self.len - 1;
        let mut cmp_counter = 0;

        while left_i <= right_i {
            cmp_counter += 1;
            let mid = (left_i + right_i) / 2;
            if self.arr[mid].price < price {
                cmp_counter += 1;
                left_i = mid + 1;
            } else if self.arr[mid].price > price {
                cmp_counter += 1;
                right_i = mid - 1;
            } else {
                return (Some(self.arr[mid].name.clone()), cmp_counter);
            }
        }
        (None, cmp_counter)
    }
}

impl PartialOrd for Book {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        self.price.partial_cmp(&other.price)
    }
}
