// flags:  --hlsl-shader-model 62
enable f16;
var<private> t : f16;
fn m() -> mat2x3<f16> {
    t = t + 1.0h;
    return mat2x3<f16>(1.0h, 2.0h, 3.0h,
                       4.0h, 5.0h, 6.0h);
}
fn f() {
    var v : mat2x3<f32> = mat2x3<f32>(m());
}