extern crate console_error_panic_hook;

mod data;
mod sort;
mod utils;

use wasm_bindgen::{prelude::*, JsCast};
use web_sys::{
    HtmlElement, HtmlInputElement, HtmlTableCellElement, HtmlTableElement, HtmlTableRowElement,
    Text,
};

use data::Data;
use utils::document;
use sort::Sorted;

use std::{cell::RefCell, rc::Rc};

use std::panic;

#[wasm_bindgen]
extern "C" {
    #[wasm_bindgen(js_namespace = console)]
    fn log(s: &str);
}

#[wasm_bindgen(start)]
pub fn run() {
    panic::set_hook(Box::new(console_error_panic_hook::hook));

    let slider = Rc::new(RefCell::new(
        document()
            .get_element_by_id("slider")
            .unwrap()
            .dyn_into::<HtmlInputElement>()
            .unwrap(),
    ));
    let slider_onchange = slider.clone();
    let f = Closure::wrap(Box::new(move || {
        let len = slider_onchange.borrow().value_as_number();
        document()
            .get_element_by_id("slider_value")
            .unwrap()
            .dyn_into::<HtmlElement>()
            .unwrap()
            .set_inner_html(&len.to_string());
        let data = Sorted::sort(Data::new(len as usize));
        let table = document()
            .get_element_by_id("table")
            .unwrap()
            .dyn_into::<HtmlTableElement>()
            .unwrap();
        table.set_inner_html("");
        for vec in data {
            let row = table
                .insert_row()
                .unwrap()
                .dyn_into::<HtmlTableRowElement>()
                .unwrap();
            for n in vec {
                let cell = row
                    .insert_cell()
                    .unwrap()
                    .dyn_into::<HtmlTableCellElement>()
                    .unwrap();
                let text = document()
                    .create_text_node(&n.v.to_string())
                    .dyn_into::<Text>()
                    .unwrap();
                cell.append_child(&text).unwrap();
            }
        }
    }) as Box<dyn FnMut()>);
    slider
        .borrow()
        .set_oninput(Some(f.as_ref().unchecked_ref()));
    f.forget();
}
