SKIP: INVALID


RWByteAddressBuffer prevent_dce : register(u0);
float3 subgroupShuffle_7c5d64() {
  float3 res = WaveReadLaneAt((1.0f).xxx, int(1));
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, asuint(subgroupShuffle_7c5d64()));
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, asuint(subgroupShuffle_7c5d64()));
}

FXC validation failure:
<scrubbed_path>(4,16-49): error X3004: undeclared identifier 'WaveReadLaneAt'


tint executable returned error: exit status 1
