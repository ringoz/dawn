#version 310 es

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  ivec2 a = ivec2(1073757184, -1006616064);
  uvec2 b = uvec2(a);
}
