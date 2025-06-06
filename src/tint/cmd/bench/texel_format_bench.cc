// Copyright 2023 The Dawn & Tint Authors
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

////////////////////////////////////////////////////////////////////////////////
// File generated by 'tools/src/cmd/gen' using the template:
//   src/tint/cmd/bench/texel_format_bench.cc.tmpl
//
// To regenerate run: './tools/run gen'
//
//                       Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/lang/core/texel_format.h"

#include <array>

#include "benchmark/benchmark.h"

namespace tint::core {
namespace {

void TexelFormatParser(::benchmark::State& state) {
    const char* kStrings[] = {
        "bgraunccrm",    "blranr3",       "bVra8unorm",    "bgra8unorm",   "bgra1unorm",
        "bgrJqqnorm",    "bgr7ll8unorm",  "qq32lppHat",    "c2fov",        "r32Goat",
        "r32float",      "r3viiloat",     "r3WWflo8t",     "rxxfMoat",     "rXsingg",
        "3siXt",         "r32s3nt",       "r32sint",       "E32sint",      "rPTTsint",
        "r32sidxx",      "r442uint",      "r3SSuiVVt",     "R32R22t",      "r32uint",
        "rFui9t",        "r32int",        "VOORRHnt",      "r8noym",       "lln8rrn77rm",
        "r8un4r00",      "r8unorm",       "8noom",         "zznorm",       "riiuppo1",
        "rg32floaXX",    "rg355flo99nII", "rrr32floSSaHH", "rg32float",    "kk3Hoat",
        "jg2loaRR",      "rg2loab",       "rg32jint",      "rg32snt",      "rgqint",
        "rg32sint",      "rg32inNN",      "g3vvint",       "rg2sQQnt",     "rg3furt",
        "rgj2uint",      "rg3wNN82t",     "rg32uint",      "rg32unt",      "rgrr2uint",
        "rG32uint",      "FFgba16float",  "rEb16loa",      "rga16frroat",  "rgba16float",
        "rgba6loat",     "Xba1JJfDoat",   "rga6fl8a",      "rg111kin",     "rgb16sint",
        "rgJa16sit",     "rgba16sint",    "rgca16sint",    "rgba16Oint",   "KKgba__v6sintt",
        "rg5a16xxnt",    "__ba1uqqFt",    "rgbqq6uint",    "rgba16uint",   "33ba16u66nt",
        "rtt6a1QQooint", "r66ba1uint",    "rgbx266loaOz",  "yygba32float", "gba3ZZHoat",
        "rgba32float",   "WWga32floq4t",  "rgba3OOfoat",   "rYoha2flat",   "ga32snt",
        "Fga32sint",     "rgb32sinw",     "rgba32sint",    "rgGf32sit",    "rgbaqKKsint",
        "rFba32smmnt",   "rgba32uit",     "rqba3uint",     "rgbabb2uin",   "rgba32uint",
        "rba32iint",     "qgba32uiOt",    "rgba32uiTTvv",  "rgbaFFsint",   "rgQa00siP",
        "rgPa8sint",     "rgba8sint",     "rgssa77snt",    "Cgbbb8siRRt",  "rgba8sinXX",
        "CqgbaOOsnorm",  "rgbu8ssrL",     "rgba8Xnorm",    "rgba8snorm",   "rgba8snrm",
        "ba8sqqor",      "rgba8snor22",   "rzzyaXui0t",    "rPbi8uint",    "rgaCnnint",
        "rgba8uint",     "bqqAAuinHH",    "rgba8unt",      "rgb8uiKf",     "raggunorm",
        "rgb8unorm",     "rgba8uTNo4m",   "rgba8unorm",    "rgla8unppr7",  "rg8zznNNrm",
        "bXXbauuuorm",
    };
    for (auto _ : state) {
        for (auto* str : kStrings) {
            auto result = ParseTexelFormat(str);
            benchmark::DoNotOptimize(result);
        }
    }
}  // NOLINT(readability/fn_size)

BENCHMARK(TexelFormatParser);

}  // namespace
}  // namespace tint::core
