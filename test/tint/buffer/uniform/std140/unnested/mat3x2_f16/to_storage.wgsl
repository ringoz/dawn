// flags:  --hlsl-shader-model 62
enable f16;

@group(0) @binding(0) var<uniform> u : mat3x2<f16>;
@group(0) @binding(1) var<storage, read_write> s : mat3x2<f16>;

@compute @workgroup_size(1)
fn f() {
    s = u;
    s[1] = u[0];
    s[1] = u[0].yx;
    s[0][1] = u[1][0];
}
