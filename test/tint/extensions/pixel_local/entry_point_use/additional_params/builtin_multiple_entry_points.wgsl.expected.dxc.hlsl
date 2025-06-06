//
// f
//
RasterizerOrderedTexture2D<uint4> pixel_local_a : register(u1);
RasterizerOrderedTexture2D<int4> pixel_local_b : register(u6);
RasterizerOrderedTexture2D<float4> pixel_local_c : register(u3);

struct PixelLocal {
  uint a;
  int b;
  float c;
};

static PixelLocal P = (PixelLocal)0;

void load_from_pixel_local_storage(float4 my_input) {
  uint2 rov_texcoord = uint2(my_input.xy);
  P.a = pixel_local_a.Load(rov_texcoord).x;
  P.b = pixel_local_b.Load(rov_texcoord).x;
  P.c = pixel_local_c.Load(rov_texcoord).x;
}

void store_into_pixel_local_storage(float4 my_input) {
  uint2 rov_texcoord = uint2(my_input.xy);
  pixel_local_a[rov_texcoord] = uint4((P.a).xxxx);
  pixel_local_b[rov_texcoord] = int4((P.b).xxxx);
  pixel_local_c[rov_texcoord] = float4((P.c).xxxx);
}

struct tint_symbol_1 {
  float4 pos : SV_Position;
};

uint tint_ftou(float v) {
  return ((v <= 4294967040.0f) ? ((v < 0.0f) ? 0u : uint(v)) : 4294967295u);
}

void f_inner(float4 pos) {
  P.a = (P.a + tint_ftou(pos.x));
}

void f_inner_1(float4 pos) {
  float4 hlsl_sv_position = pos;
  load_from_pixel_local_storage(hlsl_sv_position);
  f_inner(pos);
  store_into_pixel_local_storage(hlsl_sv_position);
}

void f(tint_symbol_1 tint_symbol) {
  f_inner_1(float4(tint_symbol.pos.xyz, (1.0f / tint_symbol.pos.w)));
  return;
}
//
// f2
//
RasterizerOrderedTexture2D<uint4> pixel_local_a : register(u1);
RasterizerOrderedTexture2D<int4> pixel_local_b : register(u6);
RasterizerOrderedTexture2D<float4> pixel_local_c : register(u3);

struct PixelLocal {
  uint a;
  int b;
  float c;
};

static PixelLocal P = (PixelLocal)0;

void load_from_pixel_local_storage(float4 my_input) {
  uint2 rov_texcoord = uint2(my_input.xy);
  P.a = pixel_local_a.Load(rov_texcoord).x;
  P.b = pixel_local_b.Load(rov_texcoord).x;
  P.c = pixel_local_c.Load(rov_texcoord).x;
}

void store_into_pixel_local_storage(float4 my_input) {
  uint2 rov_texcoord = uint2(my_input.xy);
  pixel_local_a[rov_texcoord] = uint4((P.a).xxxx);
  pixel_local_b[rov_texcoord] = int4((P.b).xxxx);
  pixel_local_c[rov_texcoord] = float4((P.c).xxxx);
}

struct tint_symbol_1 {
  float4 pos : SV_Position;
};

int tint_ftoi(float v) {
  return ((v <= 2147483520.0f) ? ((v < -2147483648.0f) ? -2147483648 : int(v)) : 2147483647);
}

void f2_inner(float4 pos) {
  P.b = (P.b + tint_ftoi(pos.x));
}

void f2_inner_1(float4 pos) {
  float4 hlsl_sv_position = pos;
  load_from_pixel_local_storage(hlsl_sv_position);
  f2_inner(pos);
  store_into_pixel_local_storage(hlsl_sv_position);
}

void f2(tint_symbol_1 tint_symbol) {
  f2_inner_1(float4(tint_symbol.pos.xyz, (1.0f / tint_symbol.pos.w)));
  return;
}
//
// f3
//
RasterizerOrderedTexture2D<uint4> pixel_local_a : register(u1);
RasterizerOrderedTexture2D<int4> pixel_local_b : register(u6);
RasterizerOrderedTexture2D<float4> pixel_local_c : register(u3);

struct PixelLocal {
  uint a;
  int b;
  float c;
};

static PixelLocal P = (PixelLocal)0;

void load_from_pixel_local_storage(float4 my_input) {
  uint2 rov_texcoord = uint2(my_input.xy);
  P.a = pixel_local_a.Load(rov_texcoord).x;
  P.b = pixel_local_b.Load(rov_texcoord).x;
  P.c = pixel_local_c.Load(rov_texcoord).x;
}

void store_into_pixel_local_storage(float4 my_input) {
  uint2 rov_texcoord = uint2(my_input.xy);
  pixel_local_a[rov_texcoord] = uint4((P.a).xxxx);
  pixel_local_b[rov_texcoord] = int4((P.b).xxxx);
  pixel_local_c[rov_texcoord] = float4((P.c).xxxx);
}

struct tint_symbol_1 {
  float4 pos : SV_Position;
};

void f3_inner(float4 pos) {
  P.c = (P.c + pos.x);
}

void f3_inner_1(float4 pos) {
  float4 hlsl_sv_position = pos;
  load_from_pixel_local_storage(hlsl_sv_position);
  f3_inner(pos);
  store_into_pixel_local_storage(hlsl_sv_position);
}

void f3(tint_symbol_1 tint_symbol) {
  f3_inner_1(float4(tint_symbol.pos.xyz, (1.0f / tint_symbol.pos.w)));
  return;
}
