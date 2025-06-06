//
// fragment_main
//
int4 tint_clamp(int4 e, int4 low, int4 high) {
  return min(max(e, low), high);
}

RWByteAddressBuffer prevent_dce : register(u0);

int4 clamp_1a32e3() {
  int4 arg_0 = (1).xxxx;
  int4 arg_1 = (1).xxxx;
  int4 arg_2 = (1).xxxx;
  int4 res = tint_clamp(arg_0, arg_1, arg_2);
  return res;
}

void fragment_main() {
  prevent_dce.Store4(0u, asuint(clamp_1a32e3()));
  return;
}
//
// compute_main
//
int4 tint_clamp(int4 e, int4 low, int4 high) {
  return min(max(e, low), high);
}

RWByteAddressBuffer prevent_dce : register(u0);

int4 clamp_1a32e3() {
  int4 arg_0 = (1).xxxx;
  int4 arg_1 = (1).xxxx;
  int4 arg_2 = (1).xxxx;
  int4 res = tint_clamp(arg_0, arg_1, arg_2);
  return res;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store4(0u, asuint(clamp_1a32e3()));
  return;
}
//
// vertex_main
//
int4 tint_clamp(int4 e, int4 low, int4 high) {
  return min(max(e, low), high);
}

int4 clamp_1a32e3() {
  int4 arg_0 = (1).xxxx;
  int4 arg_1 = (1).xxxx;
  int4 arg_2 = (1).xxxx;
  int4 res = tint_clamp(arg_0, arg_1, arg_2);
  return res;
}

struct VertexOutput {
  float4 pos;
  int4 prevent_dce;
};
struct tint_symbol_1 {
  nointerpolation int4 prevent_dce : TEXCOORD0;
  float4 pos : SV_Position;
};

VertexOutput vertex_main_inner() {
  VertexOutput tint_symbol = (VertexOutput)0;
  tint_symbol.pos = (0.0f).xxxx;
  tint_symbol.prevent_dce = clamp_1a32e3();
  return tint_symbol;
}

tint_symbol_1 vertex_main() {
  VertexOutput inner_result = vertex_main_inner();
  tint_symbol_1 wrapper_result = (tint_symbol_1)0;
  wrapper_result.pos = inner_result.pos;
  wrapper_result.prevent_dce = inner_result.prevent_dce;
  return wrapper_result;
}
