//
// fragment_main
//
RWByteAddressBuffer prevent_dce : register(u0);
RWTexture3D<int4> arg_0 : register(u0, space1);

int4 textureLoad_d41c72() {
  int4 res = arg_0.Load(int3((1).xxx));
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(textureLoad_d41c72()));
  return;
}
//
// compute_main
//
RWByteAddressBuffer prevent_dce : register(u0);
RWTexture3D<int4> arg_0 : register(u0, space1);

int4 textureLoad_d41c72() {
  int4 res = arg_0.Load(int3((1).xxx));
  return res;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(textureLoad_d41c72()));
  return;
}
