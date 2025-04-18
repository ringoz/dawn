//
// fragment_main
//
RWByteAddressBuffer prevent_dce : register(u0);
Texture2DArray arg_0 : register(t0, space1);
SamplerState arg_1 : register(s1, space1);

float textureSampleLevel_e6ce9e() {
  float res = arg_0.SampleLevel(arg_1, float3((1.0f).xx, float(1u)), 1, int2((1).xx)).x;
  return res;
}

void fragment_main() {
  prevent_dce.Store(0u, asuint(textureSampleLevel_e6ce9e()));
  return;
}
//
// compute_main
//
RWByteAddressBuffer prevent_dce : register(u0);
Texture2DArray arg_0 : register(t0, space1);
SamplerState arg_1 : register(s1, space1);

float textureSampleLevel_e6ce9e() {
  float res = arg_0.SampleLevel(arg_1, float3((1.0f).xx, float(1u)), 1, int2((1).xx)).x;
  return res;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store(0u, asuint(textureSampleLevel_e6ce9e()));
  return;
}
//
// vertex_main
//
Texture2DArray arg_0 : register(t0, space1);
SamplerState arg_1 : register(s1, space1);

float textureSampleLevel_e6ce9e() {
  float res = arg_0.SampleLevel(arg_1, float3((1.0f).xx, float(1u)), 1, int2((1).xx)).x;
  return res;
}

struct VertexOutput {
  float4 pos;
  float prevent_dce;
};
struct tint_symbol_1 {
  nointerpolation float prevent_dce : TEXCOORD0;
  float4 pos : SV_Position;
};

VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = (VertexOutput)0;
  tint_symbol.pos = (0.0f).xxxx;
  tint_symbol.prevent_dce = textureSampleLevel_e6ce9e();
  return tint_symbol;
}

tint_symbol_1 vertex_main() {
  VertexOutput inner_result = vertex_main_inner();
  tint_symbol_1 wrapper_result = (tint_symbol_1)0;
  wrapper_result.pos = inner_result.pos;
  wrapper_result.prevent_dce = inner_result.prevent_dce;
  return wrapper_result;
}
