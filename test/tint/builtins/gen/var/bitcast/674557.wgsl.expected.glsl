//
// fragment_main
//
#version 310 es
#extension GL_AMD_gpu_shader_half_float: require
precision highp float;
precision highp int;

layout(binding = 0, std430)
buffer f_prevent_dce_block_ssbo {
  f16vec2 inner;
} v;
f16vec2 tint_bitcast_to_f16(int src) {
  return unpackFloat2x16(uint(src));
}
f16vec2 bitcast_674557() {
  int arg_0 = 1;
  f16vec2 res = tint_bitcast_to_f16(arg_0);
  return res;
}
void main() {
  v.inner = bitcast_674557();
}
//
// compute_main
//
#version 310 es
#extension GL_AMD_gpu_shader_half_float: require

layout(binding = 0, std430)
buffer prevent_dce_block_1_ssbo {
  f16vec2 inner;
} v;
f16vec2 tint_bitcast_to_f16(int src) {
  return unpackFloat2x16(uint(src));
}
f16vec2 bitcast_674557() {
  int arg_0 = 1;
  f16vec2 res = tint_bitcast_to_f16(arg_0);
  return res;
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  v.inner = bitcast_674557();
}
//
// vertex_main
//
#version 310 es
#extension GL_AMD_gpu_shader_half_float: require


struct VertexOutput {
  vec4 pos;
  f16vec2 prevent_dce;
};

layout(location = 0) flat out f16vec2 tint_interstage_location0;
f16vec2 tint_bitcast_to_f16(int src) {
  return unpackFloat2x16(uint(src));
}
f16vec2 bitcast_674557() {
  int arg_0 = 1;
  f16vec2 res = tint_bitcast_to_f16(arg_0);
  return res;
}
VertexOutput vertex_main_inner() {
  VertexOutput v = VertexOutput(vec4(0.0f), f16vec2(0.0hf));
  v.pos = vec4(0.0f);
  v.prevent_dce = bitcast_674557();
  return v;
}
void main() {
  VertexOutput v_1 = vertex_main_inner();
  gl_Position = vec4(v_1.pos.x, -(v_1.pos.y), ((2.0f * v_1.pos.z) - v_1.pos.w), v_1.pos.w);
  tint_interstage_location0 = v_1.prevent_dce;
  gl_PointSize = 1.0f;
}
