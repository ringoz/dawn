#version 310 es


struct S {
  ivec3 v;
};

S P = S(ivec3(0));
void f() {
  ivec3 v = P.v;
  int x = P.v.x;
  int y = P.v.y;
  int z = P.v.z;
  ivec2 xx = P.v.xx;
  ivec2 xy = P.v.xy;
  ivec2 xz = P.v.xz;
  ivec2 yx = P.v.yx;
  ivec2 yy = P.v.yy;
  ivec2 yz = P.v.yz;
  ivec2 zx = P.v.zx;
  ivec2 zy = P.v.zy;
  ivec2 zz = P.v.zz;
  ivec3 xxx = P.v.xxx;
  ivec3 xxy = P.v.xxy;
  ivec3 xxz = P.v.xxz;
  ivec3 xyx = P.v.xyx;
  ivec3 xyy = P.v.xyy;
  ivec3 xyz = P.v.xyz;
  ivec3 xzx = P.v.xzx;
  ivec3 xzy = P.v.xzy;
  ivec3 xzz = P.v.xzz;
  ivec3 yxx = P.v.yxx;
  ivec3 yxy = P.v.yxy;
  ivec3 yxz = P.v.yxz;
  ivec3 yyx = P.v.yyx;
  ivec3 yyy = P.v.yyy;
  ivec3 yyz = P.v.yyz;
  ivec3 yzx = P.v.yzx;
  ivec3 yzy = P.v.yzy;
  ivec3 yzz = P.v.yzz;
  ivec3 zxx = P.v.zxx;
  ivec3 zxy = P.v.zxy;
  ivec3 zxz = P.v.zxz;
  ivec3 zyx = P.v.zyx;
  ivec3 zyy = P.v.zyy;
  ivec3 zyz = P.v.zyz;
  ivec3 zzx = P.v.zzx;
  ivec3 zzy = P.v.zzy;
  ivec3 zzz = P.v.zzz;
  ivec4 xxxx = P.v.xxxx;
  ivec4 xxxy = P.v.xxxy;
  ivec4 xxxz = P.v.xxxz;
  ivec4 xxyx = P.v.xxyx;
  ivec4 xxyy = P.v.xxyy;
  ivec4 xxyz = P.v.xxyz;
  ivec4 xxzx = P.v.xxzx;
  ivec4 xxzy = P.v.xxzy;
  ivec4 xxzz = P.v.xxzz;
  ivec4 xyxx = P.v.xyxx;
  ivec4 xyxy = P.v.xyxy;
  ivec4 xyxz = P.v.xyxz;
  ivec4 xyyx = P.v.xyyx;
  ivec4 xyyy = P.v.xyyy;
  ivec4 xyyz = P.v.xyyz;
  ivec4 xyzx = P.v.xyzx;
  ivec4 xyzy = P.v.xyzy;
  ivec4 xyzz = P.v.xyzz;
  ivec4 xzxx = P.v.xzxx;
  ivec4 xzxy = P.v.xzxy;
  ivec4 xzxz = P.v.xzxz;
  ivec4 xzyx = P.v.xzyx;
  ivec4 xzyy = P.v.xzyy;
  ivec4 xzyz = P.v.xzyz;
  ivec4 xzzx = P.v.xzzx;
  ivec4 xzzy = P.v.xzzy;
  ivec4 xzzz = P.v.xzzz;
  ivec4 yxxx = P.v.yxxx;
  ivec4 yxxy = P.v.yxxy;
  ivec4 yxxz = P.v.yxxz;
  ivec4 yxyx = P.v.yxyx;
  ivec4 yxyy = P.v.yxyy;
  ivec4 yxyz = P.v.yxyz;
  ivec4 yxzx = P.v.yxzx;
  ivec4 yxzy = P.v.yxzy;
  ivec4 yxzz = P.v.yxzz;
  ivec4 yyxx = P.v.yyxx;
  ivec4 yyxy = P.v.yyxy;
  ivec4 yyxz = P.v.yyxz;
  ivec4 yyyx = P.v.yyyx;
  ivec4 yyyy = P.v.yyyy;
  ivec4 yyyz = P.v.yyyz;
  ivec4 yyzx = P.v.yyzx;
  ivec4 yyzy = P.v.yyzy;
  ivec4 yyzz = P.v.yyzz;
  ivec4 yzxx = P.v.yzxx;
  ivec4 yzxy = P.v.yzxy;
  ivec4 yzxz = P.v.yzxz;
  ivec4 yzyx = P.v.yzyx;
  ivec4 yzyy = P.v.yzyy;
  ivec4 yzyz = P.v.yzyz;
  ivec4 yzzx = P.v.yzzx;
  ivec4 yzzy = P.v.yzzy;
  ivec4 yzzz = P.v.yzzz;
  ivec4 zxxx = P.v.zxxx;
  ivec4 zxxy = P.v.zxxy;
  ivec4 zxxz = P.v.zxxz;
  ivec4 zxyx = P.v.zxyx;
  ivec4 zxyy = P.v.zxyy;
  ivec4 zxyz = P.v.zxyz;
  ivec4 zxzx = P.v.zxzx;
  ivec4 zxzy = P.v.zxzy;
  ivec4 zxzz = P.v.zxzz;
  ivec4 zyxx = P.v.zyxx;
  ivec4 zyxy = P.v.zyxy;
  ivec4 zyxz = P.v.zyxz;
  ivec4 zyyx = P.v.zyyx;
  ivec4 zyyy = P.v.zyyy;
  ivec4 zyyz = P.v.zyyz;
  ivec4 zyzx = P.v.zyzx;
  ivec4 zyzy = P.v.zyzy;
  ivec4 zyzz = P.v.zyzz;
  ivec4 zzxx = P.v.zzxx;
  ivec4 zzxy = P.v.zzxy;
  ivec4 zzxz = P.v.zzxz;
  ivec4 zzyx = P.v.zzyx;
  ivec4 zzyy = P.v.zzyy;
  ivec4 zzyz = P.v.zzyz;
  ivec4 zzzx = P.v.zzzx;
  ivec4 zzzy = P.v.zzzy;
  ivec4 zzzz = P.v.zzzz;
}
layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
}
