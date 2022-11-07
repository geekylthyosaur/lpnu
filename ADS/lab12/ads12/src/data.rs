use fake::{faker::lorem::en::*, Fake};

#[derive(Default)]
pub struct Data {
    pub text1: Vec<String>,
    pub text2: String,
}

impl Data {
    pub fn new() -> Self {
        Data {
            text1: Words(2..10).fake::<Vec<String>>(),
            text2: Words(10..100).fake::<Vec<String>>().join(" "),
        }
    }
}
