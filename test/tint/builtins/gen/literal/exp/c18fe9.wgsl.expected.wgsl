enable f16;

@group(0) @binding(0) var<storage, read_write> prevent_dce : f16;

fn exp_c18fe9() -> f16 {
  var res : f16 = exp(1.0h);
  return res;
}

@fragment
fn fragment_main() {
  prevent_dce = exp_c18fe9();
}

@compute @workgroup_size(1)
fn compute_main() {
  prevent_dce = exp_c18fe9();
}

struct VertexOutput {
  @builtin(position)
  pos : vec4<f32>,
  @location(0) @interpolate(flat)
  prevent_dce : f16,
}

@vertex
fn vertex_main() -> VertexOutput {
  var out : VertexOutput;
  out.pos = vec4<f32>();
  out.prevent_dce = exp_c18fe9();
  return out;
}
