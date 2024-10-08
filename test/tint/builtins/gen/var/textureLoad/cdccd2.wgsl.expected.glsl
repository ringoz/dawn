#version 460

layout(binding = 0, std430) buffer prevent_dce_block_ssbo {
  uvec4 inner;
} prevent_dce;

layout(binding = 0, rg32ui) uniform highp uimage2DArray arg_0;
uvec4 textureLoad_cdccd2() {
  ivec2 arg_1 = ivec2(1);
  uint arg_2 = 1u;
  uvec4 res = imageLoad(arg_0, ivec3(arg_1, int(arg_2)));
  return res;
}

void fragment_main() {
  prevent_dce.inner = textureLoad_cdccd2();
}

void main() {
  fragment_main();
  return;
}
#version 460

layout(binding = 0, std430) buffer prevent_dce_block_ssbo {
  uvec4 inner;
} prevent_dce;

layout(binding = 0, rg32ui) uniform highp uimage2DArray arg_0;
uvec4 textureLoad_cdccd2() {
  ivec2 arg_1 = ivec2(1);
  uint arg_2 = 1u;
  uvec4 res = imageLoad(arg_0, ivec3(arg_1, int(arg_2)));
  return res;
}

void compute_main() {
  prevent_dce.inner = textureLoad_cdccd2();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
