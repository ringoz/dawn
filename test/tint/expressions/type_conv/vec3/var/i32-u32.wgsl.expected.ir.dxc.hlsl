
static int3 u = (int(1)).xxx;
void f() {
  uint3 v = uint3(u);
}

[numthreads(1, 1, 1)]
void unused_entry_point() {
}

