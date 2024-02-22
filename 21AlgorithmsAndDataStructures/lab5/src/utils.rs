use wasm_bindgen::prelude::*;

#[wasm_bindgen]
extern "C" {
    #[wasm_bindgen(js_namespace = console)]
    fn log(s: &str);
}

fn window() -> web_sys::Window {
    web_sys::window().expect("No global 'window' exist!")
}

pub fn document() -> web_sys::Document {
    window()
        .document()
        .expect("Should have a document on a window!")
}
