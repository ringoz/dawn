@group(1) @binding(0) var arg_0 : texture_storage_1d<rgba32sint, write>;

fn textureStore_1dc954() {
  textureStore(arg_0, 1u, vec4<i32>(1i));
}

@fragment
fn fragment_main() {
  textureStore_1dc954();
}

@compute @workgroup_size(1)
fn compute_main() {
  textureStore_1dc954();
}
