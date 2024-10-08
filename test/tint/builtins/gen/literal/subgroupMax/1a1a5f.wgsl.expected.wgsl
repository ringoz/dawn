enable subgroups;

@group(0) @binding(0) var<storage, read_write> prevent_dce : f32;

fn subgroupMax_1a1a5f() -> f32 {
  var res : f32 = subgroupMax(1.0f);
  return res;
}

@fragment
fn fragment_main() {
  prevent_dce = subgroupMax_1a1a5f();
}

@compute @workgroup_size(1)
fn compute_main() {
  prevent_dce = subgroupMax_1a1a5f();
}
