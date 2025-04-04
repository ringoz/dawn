struct VertexOutputs {
  float clipDistance[8];
  float4 position;
};

struct main_outputs {
  float4 VertexOutputs_position : SV_Position;
  float4 VertexOutputs_clipDistance0 : SV_ClipDistance0;
  float4 VertexOutputs_clipDistance1 : SV_ClipDistance1;
};


VertexOutputs main_inner() {
  VertexOutputs v = {(float[8])0, float4(1.0f, 2.0f, 3.0f, 4.0f)};
  return v;
}

main_outputs main() {
  VertexOutputs v_1 = main_inner();
  float v_2[8] = v_1.clipDistance;
  float4 v_3 = float4(v_2[0u], v_2[1u], v_2[2u], v_2[3u]);
  main_outputs v_4 = {v_1.position, v_3, float4(v_2[4u], v_2[5u], v_2[6u], v_2[7u])};
  return v_4;
}

