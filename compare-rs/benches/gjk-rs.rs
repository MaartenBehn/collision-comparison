use compare::load_data;
use criterion::{criterion_group, criterion_main, Criterion};
use gjk::{colliders::Collider, gjk::GJKNesterov};


fn test_nesterov(collider1: &Collider, collider2: &Collider) {
    let mut gjk = GJKNesterov::new(None, 1e-6);
    gjk.distance_nesterov_accelerated(collider1, collider2, 100);
}

fn bench_nesterov_accelerated(c: &mut Criterion) {

    let cases = load_data();

    c.bench_function("gjk-rs_nasterov_gjk", |b| b.iter(|| 
        for (_i, data) in cases.iter().enumerate() {
            test_nesterov(&data.0, &data.1);
        }
    ));
}

criterion_group!(benches, bench_nesterov_accelerated);
criterion_main!(benches);