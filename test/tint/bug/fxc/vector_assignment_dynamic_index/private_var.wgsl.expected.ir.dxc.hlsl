
cbuffer cbuffer_i : register(b0) {
  uint4 i[1];
};
static float3 v1 = (0.0f).xxx;
[numthreads(1, 1, 1)]
void main() {
  v1[min(i[0u].x, 2u)] = 1.0f;
}

