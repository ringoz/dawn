#version 310 es
#extension GL_AMD_gpu_shader_half_float: require

f16mat2x3 m = f16mat2x3(f16vec3(0.0hf, 1.0hf, 2.0hf), f16vec3(3.0hf, 4.0hf, 5.0hf));
layout(binding = 0, std430)
buffer out_block_1_ssbo {
  f16mat2x3 inner;
} v;
void tint_store_and_preserve_padding(f16mat2x3 value_param) {
  v.inner[0u] = value_param[0u];
  v.inner[1u] = value_param[1u];
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  tint_store_and_preserve_padding(f16mat2x3(m));
}
