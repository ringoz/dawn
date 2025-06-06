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
//   src/tint/lang/wgsl/builtin_fn.h.tmpl
//
// To regenerate run: './tools/run gen'
//
//                       Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#ifndef SRC_TINT_LANG_WGSL_BUILTIN_FN_H_
#define SRC_TINT_LANG_WGSL_BUILTIN_FN_H_

#include <cstdint>
#include <string>

#include "src/tint/utils/rtti/traits.h"

// \cond DO_NOT_DOCUMENT
namespace tint::wgsl {

/// Enumerator of all builtin functions
enum class BuiltinFn : uint8_t {
    kAbs,
    kAcos,
    kAcosh,
    kAll,
    kAny,
    kArrayLength,
    kAsin,
    kAsinh,
    kAtan,
    kAtan2,
    kAtanh,
    kBitcast,
    kCeil,
    kClamp,
    kCos,
    kCosh,
    kCountLeadingZeros,
    kCountOneBits,
    kCountTrailingZeros,
    kCross,
    kDegrees,
    kDeterminant,
    kDistance,
    kDot,
    kDot4I8Packed,
    kDot4U8Packed,
    kDpdx,
    kDpdxCoarse,
    kDpdxFine,
    kDpdy,
    kDpdyCoarse,
    kDpdyFine,
    kExp,
    kExp2,
    kExtractBits,
    kFaceForward,
    kFirstLeadingBit,
    kFirstTrailingBit,
    kFloor,
    kFma,
    kFract,
    kFrexp,
    kFwidth,
    kFwidthCoarse,
    kFwidthFine,
    kInsertBits,
    kInverseSqrt,
    kLdexp,
    kLength,
    kLog,
    kLog2,
    kMax,
    kMin,
    kMix,
    kModf,
    kNormalize,
    kPack2X16Float,
    kPack2X16Snorm,
    kPack2X16Unorm,
    kPack4X8Snorm,
    kPack4X8Unorm,
    kPack4XI8,
    kPack4XU8,
    kPack4XI8Clamp,
    kPack4XU8Clamp,
    kPow,
    kQuantizeToF16,
    kRadians,
    kReflect,
    kRefract,
    kReverseBits,
    kRound,
    kSaturate,
    kSelect,
    kSign,
    kSin,
    kSinh,
    kSmoothstep,
    kSqrt,
    kStep,
    kStorageBarrier,
    kTan,
    kTanh,
    kTranspose,
    kTrunc,
    kUnpack2X16Float,
    kUnpack2X16Snorm,
    kUnpack2X16Unorm,
    kUnpack4X8Snorm,
    kUnpack4X8Unorm,
    kUnpack4XI8,
    kUnpack4XU8,
    kWorkgroupBarrier,
    kWorkgroupUniformLoad,
    kTextureBarrier,
    kTextureDimensions,
    kTextureGather,
    kTextureGatherCompare,
    kTextureNumLayers,
    kTextureNumLevels,
    kTextureNumSamples,
    kTextureSample,
    kTextureSampleBias,
    kTextureSampleCompare,
    kTextureSampleCompareLevel,
    kTextureSampleGrad,
    kTextureSampleLevel,
    kTextureSampleBaseClampToEdge,
    kTextureStore,
    kTextureLoad,
    kInputAttachmentLoad,
    kAtomicLoad,
    kAtomicStore,
    kAtomicAdd,
    kAtomicSub,
    kAtomicMax,
    kAtomicMin,
    kAtomicAnd,
    kAtomicOr,
    kAtomicXor,
    kAtomicExchange,
    kAtomicCompareExchangeWeak,
    kSubgroupBallot,
    kSubgroupElect,
    kSubgroupBroadcast,
    kSubgroupBroadcastFirst,
    kSubgroupShuffle,
    kSubgroupShuffleXor,
    kSubgroupShuffleUp,
    kSubgroupShuffleDown,
    kSubgroupAdd,
    kSubgroupInclusiveAdd,
    kSubgroupExclusiveAdd,
    kSubgroupMul,
    kSubgroupInclusiveMul,
    kSubgroupExclusiveMul,
    kSubgroupAnd,
    kSubgroupOr,
    kSubgroupXor,
    kSubgroupMin,
    kSubgroupMax,
    kSubgroupAll,
    kSubgroupAny,
    kQuadBroadcast,
    kQuadSwapX,
    kQuadSwapY,
    kQuadSwapDiagonal,
    kSubgroupMatrixLoad,
    kSubgroupMatrixStore,
    kSubgroupMatrixMultiply,
    kSubgroupMatrixMultiplyAccumulate,
    kTintMaterialize,
    kNone,
};

/// Matches the BuiltinFn by name
/// @param name the builtin name to parse
/// @returns the parsed BuiltinFn, or BuiltinFn::kNone if `name` did not
/// match any builtin function.
BuiltinFn ParseBuiltinFn(std::string_view name);

/// @returns the name of the builtin function type. The spelling, including
/// case, matches the name in the WGSL spec.
const char* str(BuiltinFn i);

/// Emits the name of the builtin function type. The spelling, including case,
/// matches the name in the WGSL spec.
template <typename STREAM>
    requires(traits::IsOStream<STREAM>)
auto& operator<<(STREAM& o, BuiltinFn i) {
    return o << str(i);
}

/// All builtin functions
constexpr BuiltinFn kBuiltinFns[] = {
    BuiltinFn::kAbs,
    BuiltinFn::kAcos,
    BuiltinFn::kAcosh,
    BuiltinFn::kAll,
    BuiltinFn::kAny,
    BuiltinFn::kArrayLength,
    BuiltinFn::kAsin,
    BuiltinFn::kAsinh,
    BuiltinFn::kAtan,
    BuiltinFn::kAtan2,
    BuiltinFn::kAtanh,
    BuiltinFn::kBitcast,
    BuiltinFn::kCeil,
    BuiltinFn::kClamp,
    BuiltinFn::kCos,
    BuiltinFn::kCosh,
    BuiltinFn::kCountLeadingZeros,
    BuiltinFn::kCountOneBits,
    BuiltinFn::kCountTrailingZeros,
    BuiltinFn::kCross,
    BuiltinFn::kDegrees,
    BuiltinFn::kDeterminant,
    BuiltinFn::kDistance,
    BuiltinFn::kDot,
    BuiltinFn::kDot4I8Packed,
    BuiltinFn::kDot4U8Packed,
    BuiltinFn::kDpdx,
    BuiltinFn::kDpdxCoarse,
    BuiltinFn::kDpdxFine,
    BuiltinFn::kDpdy,
    BuiltinFn::kDpdyCoarse,
    BuiltinFn::kDpdyFine,
    BuiltinFn::kExp,
    BuiltinFn::kExp2,
    BuiltinFn::kExtractBits,
    BuiltinFn::kFaceForward,
    BuiltinFn::kFirstLeadingBit,
    BuiltinFn::kFirstTrailingBit,
    BuiltinFn::kFloor,
    BuiltinFn::kFma,
    BuiltinFn::kFract,
    BuiltinFn::kFrexp,
    BuiltinFn::kFwidth,
    BuiltinFn::kFwidthCoarse,
    BuiltinFn::kFwidthFine,
    BuiltinFn::kInsertBits,
    BuiltinFn::kInverseSqrt,
    BuiltinFn::kLdexp,
    BuiltinFn::kLength,
    BuiltinFn::kLog,
    BuiltinFn::kLog2,
    BuiltinFn::kMax,
    BuiltinFn::kMin,
    BuiltinFn::kMix,
    BuiltinFn::kModf,
    BuiltinFn::kNormalize,
    BuiltinFn::kPack2X16Float,
    BuiltinFn::kPack2X16Snorm,
    BuiltinFn::kPack2X16Unorm,
    BuiltinFn::kPack4X8Snorm,
    BuiltinFn::kPack4X8Unorm,
    BuiltinFn::kPack4XI8,
    BuiltinFn::kPack4XU8,
    BuiltinFn::kPack4XI8Clamp,
    BuiltinFn::kPack4XU8Clamp,
    BuiltinFn::kPow,
    BuiltinFn::kQuantizeToF16,
    BuiltinFn::kRadians,
    BuiltinFn::kReflect,
    BuiltinFn::kRefract,
    BuiltinFn::kReverseBits,
    BuiltinFn::kRound,
    BuiltinFn::kSaturate,
    BuiltinFn::kSelect,
    BuiltinFn::kSign,
    BuiltinFn::kSin,
    BuiltinFn::kSinh,
    BuiltinFn::kSmoothstep,
    BuiltinFn::kSqrt,
    BuiltinFn::kStep,
    BuiltinFn::kStorageBarrier,
    BuiltinFn::kTan,
    BuiltinFn::kTanh,
    BuiltinFn::kTranspose,
    BuiltinFn::kTrunc,
    BuiltinFn::kUnpack2X16Float,
    BuiltinFn::kUnpack2X16Snorm,
    BuiltinFn::kUnpack2X16Unorm,
    BuiltinFn::kUnpack4X8Snorm,
    BuiltinFn::kUnpack4X8Unorm,
    BuiltinFn::kUnpack4XI8,
    BuiltinFn::kUnpack4XU8,
    BuiltinFn::kWorkgroupBarrier,
    BuiltinFn::kWorkgroupUniformLoad,
    BuiltinFn::kTextureBarrier,
    BuiltinFn::kTextureDimensions,
    BuiltinFn::kTextureGather,
    BuiltinFn::kTextureGatherCompare,
    BuiltinFn::kTextureNumLayers,
    BuiltinFn::kTextureNumLevels,
    BuiltinFn::kTextureNumSamples,
    BuiltinFn::kTextureSample,
    BuiltinFn::kTextureSampleBias,
    BuiltinFn::kTextureSampleCompare,
    BuiltinFn::kTextureSampleCompareLevel,
    BuiltinFn::kTextureSampleGrad,
    BuiltinFn::kTextureSampleLevel,
    BuiltinFn::kTextureSampleBaseClampToEdge,
    BuiltinFn::kTextureStore,
    BuiltinFn::kTextureLoad,
    BuiltinFn::kInputAttachmentLoad,
    BuiltinFn::kAtomicLoad,
    BuiltinFn::kAtomicStore,
    BuiltinFn::kAtomicAdd,
    BuiltinFn::kAtomicSub,
    BuiltinFn::kAtomicMax,
    BuiltinFn::kAtomicMin,
    BuiltinFn::kAtomicAnd,
    BuiltinFn::kAtomicOr,
    BuiltinFn::kAtomicXor,
    BuiltinFn::kAtomicExchange,
    BuiltinFn::kAtomicCompareExchangeWeak,
    BuiltinFn::kSubgroupBallot,
    BuiltinFn::kSubgroupElect,
    BuiltinFn::kSubgroupBroadcast,
    BuiltinFn::kSubgroupBroadcastFirst,
    BuiltinFn::kSubgroupShuffle,
    BuiltinFn::kSubgroupShuffleXor,
    BuiltinFn::kSubgroupShuffleUp,
    BuiltinFn::kSubgroupShuffleDown,
    BuiltinFn::kSubgroupAdd,
    BuiltinFn::kSubgroupInclusiveAdd,
    BuiltinFn::kSubgroupExclusiveAdd,
    BuiltinFn::kSubgroupMul,
    BuiltinFn::kSubgroupInclusiveMul,
    BuiltinFn::kSubgroupExclusiveMul,
    BuiltinFn::kSubgroupAnd,
    BuiltinFn::kSubgroupOr,
    BuiltinFn::kSubgroupXor,
    BuiltinFn::kSubgroupMin,
    BuiltinFn::kSubgroupMax,
    BuiltinFn::kSubgroupAll,
    BuiltinFn::kSubgroupAny,
    BuiltinFn::kQuadBroadcast,
    BuiltinFn::kQuadSwapX,
    BuiltinFn::kQuadSwapY,
    BuiltinFn::kQuadSwapDiagonal,
    BuiltinFn::kSubgroupMatrixLoad,
    BuiltinFn::kSubgroupMatrixStore,
    BuiltinFn::kSubgroupMatrixMultiply,
    BuiltinFn::kSubgroupMatrixMultiplyAccumulate,
    BuiltinFn::kTintMaterialize,
};

/// All builtin function names
constexpr const char* kBuiltinFnStrings[] = {
    "abs",
    "acos",
    "acosh",
    "all",
    "any",
    "arrayLength",
    "asin",
    "asinh",
    "atan",
    "atan2",
    "atanh",
    "bitcast",
    "ceil",
    "clamp",
    "cos",
    "cosh",
    "countLeadingZeros",
    "countOneBits",
    "countTrailingZeros",
    "cross",
    "degrees",
    "determinant",
    "distance",
    "dot",
    "dot4I8Packed",
    "dot4U8Packed",
    "dpdx",
    "dpdxCoarse",
    "dpdxFine",
    "dpdy",
    "dpdyCoarse",
    "dpdyFine",
    "exp",
    "exp2",
    "extractBits",
    "faceForward",
    "firstLeadingBit",
    "firstTrailingBit",
    "floor",
    "fma",
    "fract",
    "frexp",
    "fwidth",
    "fwidthCoarse",
    "fwidthFine",
    "insertBits",
    "inverseSqrt",
    "ldexp",
    "length",
    "log",
    "log2",
    "max",
    "min",
    "mix",
    "modf",
    "normalize",
    "pack2x16float",
    "pack2x16snorm",
    "pack2x16unorm",
    "pack4x8snorm",
    "pack4x8unorm",
    "pack4xI8",
    "pack4xU8",
    "pack4xI8Clamp",
    "pack4xU8Clamp",
    "pow",
    "quantizeToF16",
    "radians",
    "reflect",
    "refract",
    "reverseBits",
    "round",
    "saturate",
    "select",
    "sign",
    "sin",
    "sinh",
    "smoothstep",
    "sqrt",
    "step",
    "storageBarrier",
    "tan",
    "tanh",
    "transpose",
    "trunc",
    "unpack2x16float",
    "unpack2x16snorm",
    "unpack2x16unorm",
    "unpack4x8snorm",
    "unpack4x8unorm",
    "unpack4xI8",
    "unpack4xU8",
    "workgroupBarrier",
    "workgroupUniformLoad",
    "textureBarrier",
    "textureDimensions",
    "textureGather",
    "textureGatherCompare",
    "textureNumLayers",
    "textureNumLevels",
    "textureNumSamples",
    "textureSample",
    "textureSampleBias",
    "textureSampleCompare",
    "textureSampleCompareLevel",
    "textureSampleGrad",
    "textureSampleLevel",
    "textureSampleBaseClampToEdge",
    "textureStore",
    "textureLoad",
    "inputAttachmentLoad",
    "atomicLoad",
    "atomicStore",
    "atomicAdd",
    "atomicSub",
    "atomicMax",
    "atomicMin",
    "atomicAnd",
    "atomicOr",
    "atomicXor",
    "atomicExchange",
    "atomicCompareExchangeWeak",
    "subgroupBallot",
    "subgroupElect",
    "subgroupBroadcast",
    "subgroupBroadcastFirst",
    "subgroupShuffle",
    "subgroupShuffleXor",
    "subgroupShuffleUp",
    "subgroupShuffleDown",
    "subgroupAdd",
    "subgroupInclusiveAdd",
    "subgroupExclusiveAdd",
    "subgroupMul",
    "subgroupInclusiveMul",
    "subgroupExclusiveMul",
    "subgroupAnd",
    "subgroupOr",
    "subgroupXor",
    "subgroupMin",
    "subgroupMax",
    "subgroupAll",
    "subgroupAny",
    "quadBroadcast",
    "quadSwapX",
    "quadSwapY",
    "quadSwapDiagonal",
    "subgroupMatrixLoad",
    "subgroupMatrixStore",
    "subgroupMatrixMultiply",
    "subgroupMatrixMultiplyAccumulate",
    "__tint_materialize",
};

/// Determines if the given `f` is a coarse derivative.
/// @param f the builtin type
/// @returns true if the given derivative is coarse.
bool IsCoarseDerivative(BuiltinFn f);

/// Determines if the given `f` is a fine derivative.
/// @param f the builtin type
/// @returns true if the given derivative is fine.
bool IsFineDerivative(BuiltinFn f);

/// Determine if the given `f` is a derivative builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a derivative builtin
bool IsDerivative(BuiltinFn f);

/// Determines if the given `f` is a texture operation builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a texture operation builtin
bool IsTexture(BuiltinFn f);

/// Determines if the given `f` is an image query builtin.
/// @param f the builtin type
/// @returns true if the given `f` is an image query builtin
bool IsImageQuery(BuiltinFn f);

/// Determines if the given `f` is a data packing builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a data packing builtin
bool IsDataPacking(BuiltinFn f);

/// Determines if the given `f` is a data unpacking builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a data unpacking builtin
bool IsDataUnpacking(BuiltinFn f);

/// Determines if the given `f` is a barrier builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a barrier builtin
bool IsBarrier(BuiltinFn f);

/// Determines if the given `f` is an atomic builtin.
/// @param f the builtin type
/// @returns true if the given `f` is an atomic builtin
bool IsAtomic(BuiltinFn f);

/// Determines if the given `f` is a builtin defined in the language extension
/// `packed_4x8_integer_dot_product`.
/// @param f the builtin type
/// @returns true if the given `f` is a builtin defined in the language extension
/// `packed_4x8_integer_dot_product`.
bool IsPacked4x8IntegerDotProductBuiltin(BuiltinFn f);

/// Determines if the given `f` is a subgroup builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a subgroup builtin
bool IsSubgroup(BuiltinFn f);

/// Determines if the given `f` is a subgroup matrix builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a subgroup matrix builtin
bool IsSubgroupMatrix(BuiltinFn f);

/// Determines if the given `f` is a quadSwap* builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a quadSwap* builtin
bool IsQuadSwap(BuiltinFn f);

/// Determines if the given `f` may have side-effects (i.e. writes to at least one of its inputs)
/// @returns true if intrinsic may have side-effects
bool HasSideEffects(BuiltinFn f);

}  // namespace tint::wgsl
// \endcond

#endif  // SRC_TINT_LANG_WGSL_BUILTIN_FN_H_
