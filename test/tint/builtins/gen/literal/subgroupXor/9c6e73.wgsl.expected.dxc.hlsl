//
// fragment_main
//
RWByteAddressBuffer prevent_dce : register(u0);

int3 subgroupXor_9c6e73() {
  int3 tint_tmp = (1).xxx;
  int3 res = asint(WaveActiveBitXor(asuint(tint_tmp)));
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, asuint(subgroupXor_9c6e73()));
  return;
}
//
// compute_main
//
RWByteAddressBuffer prevent_dce : register(u0);

int3 subgroupXor_9c6e73() {
  int3 tint_tmp = (1).xxx;
  int3 res = asint(WaveActiveBitXor(asuint(tint_tmp)));
  return res;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, asuint(subgroupXor_9c6e73()));
  return;
}
