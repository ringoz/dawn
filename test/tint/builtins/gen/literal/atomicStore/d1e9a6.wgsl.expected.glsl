//
// fragment_main
//
#version 310 es
precision highp float;
precision highp int;


struct SB_RW {
  int arg_0;
};

layout(binding = 0, std430)
buffer f_sb_rw_block_ssbo {
  SB_RW inner;
} v;
void atomicStore_d1e9a6() {
  atomicExchange(v.inner.arg_0, 1);
}
void main() {
  atomicStore_d1e9a6();
}
//
// compute_main
//
#version 310 es


struct SB_RW {
  int arg_0;
};

layout(binding = 0, std430)
buffer sb_rw_block_1_ssbo {
  SB_RW inner;
} v;
void atomicStore_d1e9a6() {
  atomicExchange(v.inner.arg_0, 1);
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  atomicStore_d1e9a6();
}
