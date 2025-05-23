//
// fragment_main
//
float3 tint_atanh(float3 x) {
  return (log(((1.0f + x) / (1.0f - x))) * 0.5f);
}

RWByteAddressBuffer prevent_dce : register(u0);

float3 atanh_440cca() {
  float3 arg_0 = (0.5f).xxx;
  float3 res = tint_atanh(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, asuint(atanh_440cca()));
  return;
}
//
// compute_main
//
float3 tint_atanh(float3 x) {
  return (log(((1.0f + x) / (1.0f - x))) * 0.5f);
}

RWByteAddressBuffer prevent_dce : register(u0);

float3 atanh_440cca() {
  float3 arg_0 = (0.5f).xxx;
  float3 res = tint_atanh(arg_0);
  return res;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, asuint(atanh_440cca()));
  return;
}
//
// vertex_main
//
float3 tint_atanh(float3 x) {
  return (log(((1.0f + x) / (1.0f - x))) * 0.5f);
}

float3 atanh_440cca() {
  float3 arg_0 = (0.5f).xxx;
  float3 res = tint_atanh(arg_0);
  return res;
}

struct VertexOutput {
  float4 pos;
  float3 prevent_dce;
};
struct tint_symbol_1 {
  nointerpolation float3 prevent_dce : TEXCOORD0;
  float4 pos : SV_Position;
};

VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = (VertexOutput)0;
  tint_symbol.pos = (0.0f).xxxx;
  tint_symbol.prevent_dce = atanh_440cca();
  return tint_symbol;
}

tint_symbol_1 vertex_main() {
  VertexOutput inner_result = vertex_main_inner();
  tint_symbol_1 wrapper_result = (tint_symbol_1)0;
  wrapper_result.pos = inner_result.pos;
  wrapper_result.prevent_dce = inner_result.prevent_dce;
  return wrapper_result;
}
