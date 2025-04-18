enable subgroups;
enable f16;

@group(0) @binding(0) var<storage, read_write> prevent_dce : f16;

fn subgroupShuffle_b0f28d() -> f16 {
  var res : f16 = subgroupShuffle(1.0h, 1i);
  return res;
}

@fragment
fn fragment_main() {
  prevent_dce = subgroupShuffle_b0f28d();
}

@compute @workgroup_size(1)
fn compute_main() {
  prevent_dce = subgroupShuffle_b0f28d();
}
