#version 310 es
#extension GL_AMD_gpu_shader_half_float: require

float16_t u = 1.0hf;
int tint_f16_to_i32(float16_t value) {
  return mix(2147483647, mix((-2147483647 - 1), int(value), (value >= -65504.0hf)), (value <= 65504.0hf));
}
void f() {
  int v = tint_f16_to_i32(u);
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
}
