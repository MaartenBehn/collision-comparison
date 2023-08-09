use gjk::{json_loder::load_test_file, colliders::Collider};


pub mod ncollide;
pub mod collision;

pub fn load_data() -> Vec<(Collider, Collider, f64)>{
    let path = "../data/nao_test_cases.json";
    load_test_file(path)
}