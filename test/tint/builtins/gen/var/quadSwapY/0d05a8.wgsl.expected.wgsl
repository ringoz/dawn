enable subgroups;

@group(0) @binding(0) var<storage, read_write> prevent_dce : vec2<i32>;

fn quadSwapY_0d05a8() -> vec2<i32> {
  var arg_0 = vec2<i32>(1i);
  var res : vec2<i32> = quadSwapY(arg_0);
  return res;
}

@fragment
fn fragment_main() {
  prevent_dce = quadSwapY_0d05a8();
}

@compute @workgroup_size(1)
fn compute_main() {
  prevent_dce = quadSwapY_0d05a8();
}
