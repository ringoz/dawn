//
// fragment_main
//
#version 310 es
precision highp float;
precision highp int;

layout(binding = 0, rgba8) uniform highp writeonly image2D f_arg_0;
void textureStore_73bbbc() {
  imageStore(f_arg_0, ivec2(uvec2(1u)), vec4(1.0f));
}
void main() {
  textureStore_73bbbc();
}
//
// compute_main
//
#version 310 es

layout(binding = 0, rgba8) uniform highp writeonly image2D arg_0;
void textureStore_73bbbc() {
  imageStore(arg_0, ivec2(uvec2(1u)), vec4(1.0f));
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  textureStore_73bbbc();
}
