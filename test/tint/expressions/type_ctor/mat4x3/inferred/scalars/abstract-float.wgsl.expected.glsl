#version 310 es

layout(binding = 0, std430)
buffer out_block_1_ssbo {
  mat4x3 inner;
} v;
void tint_store_and_preserve_padding(mat4x3 value_param) {
  v.inner[0u] = value_param[0u];
  v.inner[1u] = value_param[1u];
  v.inner[2u] = value_param[2u];
  v.inner[3u] = value_param[3u];
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  tint_store_and_preserve_padding(mat4x3(vec3(0.0f, 1.0f, 2.0f), vec3(3.0f, 4.0f, 5.0f), vec3(6.0f, 7.0f, 8.0f), vec3(9.0f, 10.0f, 11.0f)));
}
