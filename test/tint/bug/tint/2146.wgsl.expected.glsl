#version 310 es
#extension GL_AMD_gpu_shader_half_float: require

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  f16vec4 a = f16vec4(0.0hf);
  float16_t b = 1.0hf;
  a.x = (a.x + b);
}
