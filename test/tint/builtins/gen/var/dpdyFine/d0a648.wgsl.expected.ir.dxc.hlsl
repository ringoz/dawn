SKIP: FAILED

float4 dpdyFine_d0a648() {
  float4 arg_0 = (1.0f).xxxx;
  float4 res = ddy_fine(arg_0);
  return res;
}

void fragment_main() {
  prevent_dce = dpdyFine_d0a648();
}

DXC validation failure:
hlsl.hlsl:8:3: error: use of undeclared identifier 'prevent_dce'
  prevent_dce = dpdyFine_d0a648();
  ^

