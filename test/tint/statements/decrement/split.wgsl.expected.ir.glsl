#version 310 es

void tint_symbol() {
  int b = 2;
  int c = (b - -(b));
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
}
