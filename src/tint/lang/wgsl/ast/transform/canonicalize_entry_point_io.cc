// Copyright 2021 The Dawn & Tint Authors
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

#include "src/tint/lang/wgsl/ast/transform/canonicalize_entry_point_io.h"

#include <algorithm>
#include <string>
#include <unordered_set>
#include <utility>

#include "src/tint/lang/core/builtin_value.h"
#include "src/tint/lang/core/fluent_types.h"
#include "src/tint/lang/wgsl/ast/disable_validation_attribute.h"
#include "src/tint/lang/wgsl/program/clone_context.h"
#include "src/tint/lang/wgsl/program/program_builder.h"
#include "src/tint/lang/wgsl/resolver/resolve.h"
#include "src/tint/lang/wgsl/sem/function.h"
#include "src/tint/utils/containers/transform.h"

using namespace tint::core::number_suffixes;  // NOLINT
using namespace tint::core::fluent_types;     // NOLINT

TINT_INSTANTIATE_TYPEINFO(tint::ast::transform::CanonicalizeEntryPointIO);
TINT_INSTANTIATE_TYPEINFO(tint::ast::transform::CanonicalizeEntryPointIO::HLSLWaveIntrinsic);
TINT_INSTANTIATE_TYPEINFO(tint::ast::transform::CanonicalizeEntryPointIO::HLSLClipDistance1);

namespace tint::ast::transform {

CanonicalizeEntryPointIO::CanonicalizeEntryPointIO() = default;
CanonicalizeEntryPointIO::~CanonicalizeEntryPointIO() = default;

namespace {

/// Info for a struct member
struct MemberInfo {
    /// The struct member item
    const StructMember* member;
    /// The struct member location if provided
    std::optional<uint32_t> location;
    /// The struct member blend_src if provided
    std::optional<uint32_t> blend_src;
    /// The struct member color if provided
    std::optional<uint32_t> color;
};

/// FXC is sensitive to field order in structures, this is used by StructMemberComparator to ensure
/// that FXC is happy with the order of emitted fields.
uint32_t BuiltinOrder(core::BuiltinValue builtin) {
    switch (builtin) {
        case core::BuiltinValue::kPosition:
            return 1;
        case core::BuiltinValue::kVertexIndex:
            return 2;
        case core::BuiltinValue::kInstanceIndex:
            return 3;
        case core::BuiltinValue::kFrontFacing:
            return 4;
        case core::BuiltinValue::kFragDepth:
            return 5;
        case core::BuiltinValue::kLocalInvocationId:
            return 6;
        case core::BuiltinValue::kLocalInvocationIndex:
            return 7;
        case core::BuiltinValue::kGlobalInvocationId:
            return 8;
        case core::BuiltinValue::kWorkgroupId:
            return 9;
        case core::BuiltinValue::kNumWorkgroups:
            return 10;
        case core::BuiltinValue::kSampleIndex:
            return 11;
        case core::BuiltinValue::kSampleMask:
            return 12;
        case core::BuiltinValue::kPointSize:
            return 13;
        case core::BuiltinValue::kClipDistances:
            return 14;
        default:
            break;
    }
    TINT_UNREACHABLE();
}

// Returns true if `attr` is a shader IO attribute.
bool IsShaderIOAttribute(const Attribute* attr) {
    return attr->IsAnyOf<BuiltinAttribute, InterpolateAttribute, InvariantAttribute,
                         LocationAttribute, ColorAttribute, BlendSrcAttribute>();
}

}  // namespace

/// PIMPL state for the transform
struct CanonicalizeEntryPointIO::State {
    /// OutputValue represents a shader result that the wrapper function produces.
    struct OutputValue {
        /// The name of the output value.
        std::string name;
        /// The type of the output value.
        Type type;
        /// The shader IO attributes.
        tint::Vector<const Attribute*, 8> attributes;
        /// The value itself.
        const Expression* value;
        /// The output location.
        std::optional<uint32_t> location;
        /// The output blend_src.
        std::optional<uint32_t> blend_src;
    };

    /// The clone context.
    program::CloneContext& ctx;
    /// The program builder
    ProgramBuilder& b;
    /// The entry point function (AST).
    const Function* func_ast;
    /// The entry point function (SEM).
    const sem::Function* func_sem;

    /// The new entry point wrapper function's parameters.
    tint::Vector<const Parameter*, 8> wrapper_ep_parameters;

    /// The members of the wrapper function's struct parameter.
    tint::Vector<MemberInfo, 8> wrapper_struct_param_members;
    /// The name of the wrapper function's struct parameter.
    Symbol wrapper_struct_param_name;
    /// The parameters that will be passed to the original function.
    tint::Vector<const Expression*, 8> inner_call_parameters;
    /// The members of the wrapper function's struct return type.
    tint::Vector<MemberInfo, 8> wrapper_struct_output_members;
    /// The wrapper function output values.
    tint::Vector<OutputValue, 8> wrapper_output_values;
    /// The body of the wrapper function.
    tint::Vector<const Statement*, 8> wrapper_body;
    /// Input names used by the entrypoint
    std::unordered_set<std::string> input_names;
    /// A map of cloned attribute to builtin value
    Hashmap<const BuiltinAttribute*, core::BuiltinValue, 16> builtin_attrs;
    /// A map of builtin values to HLSL wave intrinsic functions.
    Hashmap<core::BuiltinValue, Symbol, 2> wave_intrinsics;
    /// The array length of the struct member with builtin attribute `clip_distances`. Now it is
    /// only set and used on HLSL and MSL backends.
    uint32_t clip_distances_size = 0;

    /// Constructor
    /// @param context the clone context
    /// @param builder the program builder
    /// @param function the entry point function
    State(program::CloneContext& context, ProgramBuilder& builder, const Function* function)
        : ctx(context), b(builder), func_ast(function), func_sem(ctx.src->Sem().Get(function)) {}

    /// Clones the attributes from @p in and adds it to @p out. If @p in is a builtin attribute,
    /// then builtin_attrs is updated with the builtin information.
    /// @param in the attribute to clone
    /// @param out the output Attributes
    template <size_t N>
    void CloneAttribute(const Attribute* in, tint::Vector<const Attribute*, N>& out) {
        auto* cloned = ctx.Clone(in);
        out.Push(cloned);
        if (auto* builtin = in->As<BuiltinAttribute>()) {
            builtin_attrs.Add(cloned->As<BuiltinAttribute>(), builtin->builtin);
        }
    }

    /// Clones the shader IO and internal attributes from @p in.
    /// @param in the attributes to clone
    /// @param do_interpolate whether to clone InterpolateAttribute
    /// @return the cloned attributes
    auto CloneShaderIOAttributes(tint::VectorRef<const Attribute*> in, bool do_interpolate) {
        tint::Vector<const Attribute*, 8> out;
        for (auto* attr : in) {
            if ((IsShaderIOAttribute(attr) &&
                 (do_interpolate || !attr->template Is<InterpolateAttribute>())) ||
                attr->Is<ast::InternalAttribute>()) {
                CloneAttribute(attr, out);
            }
        }
        return out;
    }

    /// @param attr the input attribute
    /// @returns the builtin value of the attribute
    core::BuiltinValue BuiltinOf(const BuiltinAttribute* attr) {
        if (attr->generation_id == b.ID()) {
            // attr belongs to the target program.
            // Obtain the builtin value from #builtin_attrs.
            if (auto builtin = builtin_attrs.Get(attr)) {
                return *builtin;
            }
        } else {
            // attr belongs to the source program.
            // Obtain the builtin value from the semantic info.
            return attr->builtin;
        }
        TINT_ICE() << "could not obtain builtin value from attribute";
    }

    /// @param attrs the input attribute list
    /// @returns the builtin value if any of the attributes in @p attrs is a builtin attribute,
    /// otherwise core::BuiltinValue::kUndefined
    core::BuiltinValue BuiltinOf(VectorRef<const Attribute*> attrs) {
        if (auto* builtin = GetAttribute<BuiltinAttribute>(attrs)) {
            return BuiltinOf(builtin);
        }
        return core::BuiltinValue::kUndefined;
    }

    /// Create or return a symbol for the wrapper function's struct parameter.
    /// @returns the symbol for the struct parameter
    Symbol InputStructSymbol() {
        if (!wrapper_struct_param_name.IsValid()) {
            wrapper_struct_param_name = b.Sym();
        }
        return wrapper_struct_param_name;
    }

    /// Call a wave intrinsic function for the subgroup builtin contained in @p attrs, if any.
    /// @param attrs the attribute list that may contain a subgroup builtin
    /// @returns an expression that calls a HLSL wave intrinsic, or nullptr
    const ast::CallExpression* CallWaveIntrinsic(VectorRef<const Attribute*> attrs) {
        // Helper to make a wave intrinsic.
        auto make_intrinsic = [&](const char* name, HLSLWaveIntrinsic::Op op) {
            auto symbol = b.Symbols().New(name);
            b.Func(symbol, Empty, b.ty.u32(), nullptr,
                   Vector{b.ASTNodes().Create<HLSLWaveIntrinsic>(b.ID(), b.AllocateNodeID(), op),
                          b.Disable(DisabledValidation::kFunctionHasNoBody)});
            return symbol;
        };

        // Get or create the intrinsic function.
        auto builtin = BuiltinOf(attrs);
        auto intrinsic = wave_intrinsics.GetOrAdd(builtin, [&] {
            if (builtin == core::BuiltinValue::kSubgroupInvocationId) {
                return make_intrinsic("__WaveGetLaneIndex",
                                      HLSLWaveIntrinsic::Op::kWaveGetLaneIndex);
            }
            if (builtin == core::BuiltinValue::kSubgroupSize) {
                return make_intrinsic("__WaveGetLaneCount",
                                      HLSLWaveIntrinsic::Op::kWaveGetLaneCount);
            }
            return Symbol();
        });
        if (!intrinsic) {
            return nullptr;
        }

        // Call the intrinsic function.
        return b.Call(intrinsic);
    }

    /// Add a shader input to the entry point.
    /// @param name the name of the shader input
    /// @param type the type of the shader input
    /// @param location the location if provided
    /// @param color the color if provided
    /// @param attrs the attributes to apply to the shader input
    /// @returns an expression which evaluates to the value of the shader input
    const Expression* AddInput(std::string name,
                               const core::type::Type* type,
                               std::optional<uint32_t> location,
                               std::optional<uint32_t> color,
                               tint::Vector<const Attribute*, 8> attrs) {
        auto ast_type = CreateASTTypeFor(ctx, type);

        auto builtin_attr = BuiltinOf(attrs);

        // Move it to the new structure member list.
        Symbol symbol =
            input_names.emplace(name).second ? b.Symbols().Register(name) : b.Symbols().New(name);
        wrapper_struct_param_members.Push({b.Member(symbol, ast_type, std::move(attrs)), location,
                                           /* blend_src */ std::nullopt, color});
        const Expression* expr = b.MemberAccessor(InputStructSymbol(), symbol);

        // If this is a fragment position builtin, we need to invert the 'w' component of the
        // vector.
        if (builtin_attr == core::BuiltinValue::kPosition) {
            auto* xyz = b.MemberAccessor(expr, "xyz");
            auto* w = b.MemberAccessor(b.MemberAccessor(InputStructSymbol(), symbol), "w");
            expr = b.Call<vec4<f32>>(xyz, b.Div(1_a, w));
        }

        return expr;
    }

    /// Add a shader output to the entry point.
    /// @param name the name of the shader output
    /// @param type the type of the shader output
    /// @param location the location if provided
    /// @param blend_src the blend_src if provided
    /// @param attrs the attributes to apply to the shader output
    /// @param value the value of the shader output
    void AddOutput(std::string name,
                   const core::type::Type* type,
                   std::optional<uint32_t> location,
                   std::optional<uint32_t> blend_src,
                   tint::Vector<const Attribute*, 8> attrs,
                   const Expression* value) {
        auto builtin_attr = BuiltinOf(attrs);

        if (func_ast->PipelineStage() == PipelineStage::kVertex &&
            builtin_attr == core::BuiltinValue::kClipDistances) {
            const auto* arrayType = type->As<core::type::Array>();
            if (DAWN_UNLIKELY(arrayType == nullptr || !arrayType->ConstantCount().has_value())) {
                TINT_ICE() << "The type of `clip_distances` is not a sized array";
            } else {
                clip_distances_size = *arrayType->ConstantCount();
            }
        }

        auto ast_type = CreateASTTypeFor(ctx, type);

        OutputValue output;
        output.name = name;
        output.type = ast_type;
        output.attributes = std::move(attrs);
        output.value = value;
        output.location = location;
        output.blend_src = blend_src;
        wrapper_output_values.Push(output);
    }

    /// Process a non-struct parameter.
    /// This creates a new object for the shader input, moving the shader IO
    /// attributes to it. It also adds an expression to the list of parameters
    /// that will be passed to the original function.
    /// @param param the original function parameter
    void ProcessNonStructParameter(const sem::Parameter* param) {
        if (auto* wave_intrinsic_call = CallWaveIntrinsic(param->Declaration()->attributes)) {
            inner_call_parameters.Push(wave_intrinsic_call);
            for (auto* attr : param->Declaration()->attributes) {
                ctx.Remove(param->Declaration()->attributes, attr);
            }
            return;
        }

        // Do not add interpolation attributes on vertex input
        bool do_interpolate = func_ast->PipelineStage() != PipelineStage::kVertex;
        // Remove the shader IO attributes from the inner function parameter, and attach them to the
        // new object instead.
        tint::Vector<const Attribute*, 8> attributes;
        for (auto* attr : param->Declaration()->attributes) {
            if (IsShaderIOAttribute(attr)) {
                ctx.Remove(param->Declaration()->attributes, attr);
                if ((do_interpolate || !attr->Is<InterpolateAttribute>())) {
                    CloneAttribute(attr, attributes);
                }
            }
        }

        auto name = param->Declaration()->name->symbol.Name();
        auto* input_expr = AddInput(name, param->Type(), param->Attributes().location,
                                    param->Attributes().color, std::move(attributes));
        inner_call_parameters.Push(input_expr);
    }

    /// Process a struct parameter.
    /// This creates new objects for each struct member, moving the shader IO
    /// attributes to them. It also creates the structure that will be passed to
    /// the original function.
    /// @param param the original function parameter
    void ProcessStructParameter(const sem::Parameter* param) {
        // Do not add interpolation attributes on vertex input
        bool do_interpolate = func_ast->PipelineStage() != PipelineStage::kVertex;

        auto* str = param->Type()->As<sem::Struct>();

        // Recreate struct members in the outer entry point and build an initializer
        // list to pass them through to the inner function.
        tint::Vector<const Expression*, 8> inner_struct_values;
        for (auto* member : str->Members()) {
            if (DAWN_UNLIKELY(member->Type()->Is<core::type::Struct>())) {
                TINT_ICE() << "nested IO struct";
            }

            if (auto* wave_intrinsic_call = CallWaveIntrinsic(member->Declaration()->attributes)) {
                inner_struct_values.Push(wave_intrinsic_call);
                continue;
            }

            auto name = member->Name().Name();

            auto attributes =
                CloneShaderIOAttributes(member->Declaration()->attributes, do_interpolate);
            auto* input_expr = AddInput(name, member->Type(), member->Attributes().location,
                                        member->Attributes().color, std::move(attributes));
            inner_struct_values.Push(input_expr);
        }

        // Construct the original structure using the new shader input objects.
        inner_call_parameters.Push(
            b.Call(ctx.Clone(param->Declaration()->type), inner_struct_values));
    }

    /// Process the entry point return type.
    /// This generates a list of output values that are returned by the original
    /// function.
    /// @param inner_ret_type the original function return type
    /// @param original_result the result object produced by the original function
    void ProcessReturnType(const core::type::Type* inner_ret_type, Symbol original_result) {
        // Do not add interpolation attributes on fragment output
        bool do_interpolate = func_ast->PipelineStage() != PipelineStage::kFragment;
        if (auto* str = inner_ret_type->As<sem::Struct>()) {
            for (auto* member : str->Members()) {
                if (DAWN_UNLIKELY(member->Type()->Is<core::type::Struct>())) {
                    TINT_ICE() << "nested IO struct";
                }

                auto name = member->Name().Name();
                auto attributes =
                    CloneShaderIOAttributes(member->Declaration()->attributes, do_interpolate);

                // Extract the original structure member.
                AddOutput(name, member->Type(), member->Attributes().location,
                          member->Attributes().blend_src, std::move(attributes),
                          b.MemberAccessor(original_result, name));
            }
        } else if (!inner_ret_type->Is<core::type::Void>()) {
            auto attributes =
                CloneShaderIOAttributes(func_ast->return_type_attributes, do_interpolate);

            // Propagate the non-struct return value as is.
            AddOutput("value", func_sem->ReturnType(), func_sem->ReturnLocation(),
                      func_sem->ReturnIndex(), std::move(attributes), b.Expr(original_result));
        }
    }

    /// Comparison function used to reorder struct members such that all members with
    /// color attributes appear first (ordered by color slot), then location attributes (ordered by
    /// location slot), then blend_src attributes (ordered by blend_src slot), followed by those
    /// with builtin attributes (ordered by BuiltinOrder).
    /// @param x a struct member
    /// @param y another struct member
    /// @returns true if a comes before b
    bool StructMemberComparator(const MemberInfo& x, const MemberInfo& y) {
        if (x.color.has_value() && y.color.has_value() && x.color != y.color) {
            // Both have color attributes: smallest goes first.
            return x.color < y.color;
        } else if (x.color.has_value() != y.color.has_value()) {
            // The member with the color goes first
            return x.color.has_value();
        }

        if (x.location.has_value() && y.location.has_value() && x.location != y.location) {
            // Both have location attributes: smallest goes first.
            return x.location < y.location;
        } else if (x.location.has_value() != y.location.has_value()) {
            // The member with the location goes first
            return x.location.has_value();
        }

        if (x.blend_src.has_value() && y.blend_src.has_value() && x.blend_src != y.blend_src) {
            // Both have blend_src attributes: smallest goes first.
            return x.blend_src < y.blend_src;
        } else if (x.blend_src.has_value() != y.blend_src.has_value()) {
            // The member with the blend_src goes first
            return x.blend_src.has_value();
        }

        {
            auto* x_blt = GetAttribute<BuiltinAttribute>(x.member->attributes);
            auto* y_blt = GetAttribute<BuiltinAttribute>(y.member->attributes);
            if (x_blt && y_blt) {
                // Both are builtins: order matters for FXC.
                auto builtin_a = BuiltinOf(x_blt);
                auto builtin_b = BuiltinOf(y_blt);
                auto order_a = BuiltinOrder(builtin_a);
                auto order_b = BuiltinOrder(builtin_b);
                if (order_a != order_b) {
                    return order_a < order_b;
                }
            } else if ((x_blt != nullptr) != (y_blt != nullptr)) {
                // The member with the builtin goes first
                return x_blt != nullptr;
            }
        }

        // Control flow reaches here if x is the same as y.
        // Sort algorithms sometimes do that.
        return false;
    }

    /// Create the wrapper function's struct parameter and type objects.
    void CreateInputStruct() {
        // Sort the struct members to satisfy HLSL interfacing matching rules.
        std::sort(wrapper_struct_param_members.begin(), wrapper_struct_param_members.end(),
                  [&](auto& x, auto& y) { return StructMemberComparator(x, y); });

        auto members =
            tint::Transform(wrapper_struct_param_members, [](auto& info) { return info.member; });

        // Create the new struct type.
        auto struct_name = b.Sym();
        auto* in_struct = b.create<Struct>(b.Ident(struct_name), std::move(members), Empty);
        ctx.InsertBefore(ctx.src->AST().GlobalDeclarations(), func_ast, in_struct);

        // Create a new function parameter using this struct type.
        auto* param = b.Param(InputStructSymbol(), b.ty(struct_name));
        wrapper_ep_parameters.Push(param);
    }

    /// Get an existing member symbol from a set of member names or create a new symbol
    /// @param member_names the set of the existing member names
    /// @param symbol_name the name of the symbol
    /// @returns the symbol that represents the member name we want
    Symbol GetOrCreateMemberName(std::unordered_set<std::string>* member_names,
                                 std::string symbol_name) {
        Symbol member_name;
        if (member_names->count(symbol_name)) {
            member_name = b.Symbols().New(symbol_name);
        } else {
            member_name = b.Symbols().Register(symbol_name);
        }
        member_names->insert(member_name.Name());
        return member_name;
    }

    /// Handle `clip_distances` in HLSL
    /// @param assignments the assignments to the members of the output wrapper struct
    /// @param member_names the set that contains all the member names in the output wrapper struct
    /// @param clip_distances_inner_array_name the `clip_distances` member in inner struct
    /// @param wrapper_struct_name the symbol of the output wrapper struct
    /// @param old_struct_member_attributes the attributes of the old `clip_distances` member
    void HandleClipDistancesInHLSL(
        tint::Vector<const Statement*, 8>* assignments,
        std::unordered_set<std::string>* member_names,
        const Symbol& clip_distances_inner_array_name,
        const Symbol& wrapper_struct_name,
        tint::Vector<const Attribute*, 8>&& old_struct_member_attributes) {
        auto TranslateClipDistancesIntoF32 =
            [&](const Symbol& new_member, core::u32 inner_array_index,
                tint::VectorRef<const ast::Attribute*>&& new_member_attributes) {
                assignments->Push(
                    b.Assign(b.MemberAccessor(wrapper_struct_name, new_member),
                             b.IndexAccessor(clip_distances_inner_array_name, inner_array_index)));
                wrapper_struct_output_members.Push({
                    /* member */ b.Member(new_member, b.ty.f32(), std::move(new_member_attributes)),
                    /* location */ std::nullopt,
                    /* blend_src */ std::nullopt,
                    /* color */ std::nullopt,
                });
            };

        auto TranslateClipDistancesIntoVector =
            [&](const Symbol& new_member, uint32_t vector_size, uint32_t inner_array_offset,
                tint::VectorRef<const ast::Attribute*>&& new_member_attributes) {
                for (uint32_t i = 0; i < vector_size; ++i) {
                    assignments->Push(b.Assign(
                        b.IndexAccessor(b.MemberAccessor(wrapper_struct_name, new_member), u32(i)),
                        b.IndexAccessor(clip_distances_inner_array_name,
                                        u32(inner_array_offset + i))));
                }
                wrapper_struct_output_members.Push({
                    /* member */ b.Member(new_member, b.ty.vec(b.ty.f32(), vector_size),
                                          std::move(new_member_attributes)),
                    /* location */ std::nullopt,
                    /* blend_src */ std::nullopt,
                    /* color */ std::nullopt,
                });
            };

        // float clip_distance_0 : SV_ClipDistance0;
        auto attribute_vector_0 = std::move(old_struct_member_attributes);
        attribute_vector_0.Push(b.Disable(ast::DisabledValidation::kIgnoreClipDistancesType));
        auto new_member_0 = GetOrCreateMemberName(member_names, "clip_distance_0");
        if (clip_distances_size == 1u) {
            TranslateClipDistancesIntoF32(new_member_0, 0_u, std::move(attribute_vector_0));
            return;
        }

        // floatN clip_distance_0 : SV_ClipDistance0;
        uint32_t clip_distance0_size = std::min(clip_distances_size, 4u);
        TranslateClipDistancesIntoVector(new_member_0, clip_distance0_size, 0,
                                         std::move(attribute_vector_0));

        // It is enough to just generate SV_ClipDistance0.
        if (clip_distances_size <= 4u) {
            return;
        }

        // float clip_distance_1 : SV_ClipDistance1;
        auto attribute_vector_1 =
            Vector{b.ASTNodes().Create<HLSLClipDistance1>(b.ID(), b.AllocateNodeID())};
        auto new_member_1 = GetOrCreateMemberName(member_names, "clip_distance_1");

        if (clip_distances_size == 5u) {
            TranslateClipDistancesIntoF32(new_member_1, 4_u, std::move(attribute_vector_1));
            return;
        }

        // floatN clip_distance_1 : SV_ClipDistance1;
        uint32_t clip_distances1_size = clip_distances_size - 4u;
        TranslateClipDistancesIntoVector(new_member_1, clip_distances1_size, 4u,
                                         std::move(attribute_vector_1));
    }

    /// Create and return the wrapper function's struct result object.
    /// @returns the struct type
    Struct* CreateOutputStruct() {
        tint::Vector<const Statement*, 8> assignments;

        auto wrapper_result = b.Symbols().New("wrapper_result");

        // Create the struct members and their corresponding assignment statements.
        std::unordered_set<std::string> member_names;
        for (auto& outval : wrapper_output_values) {
            auto* builtin_attribute = GetAttribute<BuiltinAttribute>(outval.attributes);
            if (builtin_attribute != nullptr &&
                builtin_attribute->builtin == core::BuiltinValue::kClipDistances) {
                Symbol clip_distances_inner_array = b.Symbols().New("tmp_inner_clip_distances");

                // Consume outval.type in the let statement as in HLSL `SV_ClipDistance` always has
                // different type.
                assignments.Push(
                    b.Decl(b.Let(clip_distances_inner_array, outval.type, outval.value)));
                HandleClipDistancesInHLSL(&assignments, &member_names, clip_distances_inner_array,
                                          wrapper_result, std::move(outval.attributes));
                continue;
            }

            // Use the original output name, unless that is already taken.
            Symbol name = GetOrCreateMemberName(&member_names, outval.name);

            assignments.Push(b.Assign(b.MemberAccessor(wrapper_result, name), outval.value));

            wrapper_struct_output_members.Push({
                /* member */ b.Member(name, outval.type, std::move(outval.attributes)),
                /* location */ outval.location,
                /* blend_src */ outval.blend_src,
                /* color */ std::nullopt,
            });
        }

        // Sort the struct members to satisfy HLSL interfacing matching rules.
        std::sort(wrapper_struct_output_members.begin(), wrapper_struct_output_members.end(),
                  [&](auto& x, auto& y) { return StructMemberComparator(x, y); });

        tint::Vector<const StructMember*, 8> members;
        for (auto& mem : wrapper_struct_output_members) {
            members.Push(mem.member);
        }

        // Create the new struct type.
        auto* out_struct = b.create<Struct>(b.Ident(b.Sym()), std::move(members), Empty);
        ctx.InsertBefore(ctx.src->AST().GlobalDeclarations(), func_ast, out_struct);

        // Create the output struct object, assign its members, and return it.
        auto* result_object = b.Var(wrapper_result, b.ty(out_struct->name->symbol));
        wrapper_body.Push(b.Decl(result_object));
        for (auto* assignment : assignments) {
            wrapper_body.Push(assignment);
        }
        wrapper_body.Push(b.Return(wrapper_result));

        return out_struct;
    }

    // Recreate the original function without entry point attributes and call it.
    /// @returns the inner function call expression
    const CallExpression* CallInnerFunction() {
        // Add a suffix to the function name, as the wrapper function will take the original entry
        // point name.
        auto ep_name = func_ast->name->symbol.Name();
        auto inner_name = b.Symbols().New(ep_name + "_inner");

        // Clone everything, dropping the function and return type attributes.
        // The parameter attributes will have already been stripped during
        // processing.
        auto* inner_function = b.create<Function>(b.Ident(inner_name), ctx.Clone(func_ast->params),
                                                  ctx.Clone(func_ast->return_type),
                                                  ctx.Clone(func_ast->body), Empty, Empty);
        ctx.Replace(func_ast, inner_function);

        // Call the function.
        return b.Call(inner_function->name->symbol, inner_call_parameters);
    }

    /// Process the entry point function.
    void Process() {
        // Exit early if there is no shader IO to handle.
        if (func_sem->Parameters().Length() == 0 &&
            func_sem->ReturnType()->Is<core::type::Void>()) {
            return;
        }

        // Process the entry point parameters, collecting those that need to be
        // aggregated into a single structure.
        if (!func_sem->Parameters().IsEmpty()) {
            for (auto* param : func_sem->Parameters()) {
                if (param->Type()->Is<core::type::Struct>()) {
                    ProcessStructParameter(param);
                } else {
                    ProcessNonStructParameter(param);
                }
            }

            // Create a structure parameter for the outer entry point if necessary.
            if (!wrapper_struct_param_members.IsEmpty()) {
                CreateInputStruct();
            }
        }

        // Recreate the original function and call it.
        auto* call_inner = CallInnerFunction();

        // Process the return type, and start building the wrapper function body.
        std::function<Type()> wrapper_ret_type = [&] { return b.ty.void_(); };
        if (func_sem->ReturnType()->Is<core::type::Void>()) {
            // The function call is just a statement with no result.
            wrapper_body.Push(b.CallStmt(call_inner));
        } else {
            // Capture the result of calling the original function.
            auto* inner_result = b.Let(b.Symbols().New("inner_result"), call_inner);
            wrapper_body.Push(b.Decl(inner_result));

            // Process the original return type to determine the outputs that the
            // outer function needs to produce.
            ProcessReturnType(func_sem->ReturnType(), inner_result->name->symbol);
        }

        // Produce the entry point outputs, if necessary.
        if (!wrapper_output_values.IsEmpty()) {
            auto* output_struct = CreateOutputStruct();
            wrapper_ret_type = [&, output_struct] { return b.ty(output_struct->name->symbol); };
        }

        // Create the wrapper entry point function.
        Symbol name = ctx.Clone(func_ast->name->symbol);
        auto* wrapper_func =
            b.create<Function>(b.Ident(name), wrapper_ep_parameters, b.ty(wrapper_ret_type()),
                               b.Block(wrapper_body), ctx.Clone(func_ast->attributes), Empty);
        ctx.InsertAfter(ctx.src->AST().GlobalDeclarations(), func_ast, wrapper_func);
    }
};

Transform::ApplyResult CanonicalizeEntryPointIO::Apply(const Program& src,
                                                       const DataMap&,
                                                       DataMap&) const {
    ProgramBuilder b;
    program::CloneContext ctx{&b, &src, /* auto_clone_symbols */ true};

    // Remove entry point IO attributes from struct declarations.
    // New structures will be created for each entry point, as necessary.
    for (auto* ty : src.AST().TypeDecls()) {
        if (auto* struct_ty = ty->As<Struct>()) {
            for (auto* member : struct_ty->members) {
                for (auto* attr : member->attributes) {
                    if (IsShaderIOAttribute(attr)) {
                        ctx.Remove(member->attributes, attr);
                    }
                }
            }
        }
    }

    for (auto* func_ast : src.AST().Functions()) {
        if (!func_ast->IsEntryPoint()) {
            continue;
        }

        State state(ctx, b, func_ast);
        state.Process();
    }

    ctx.Clone();
    return resolver::Resolve(b);
}

CanonicalizeEntryPointIO::HLSLWaveIntrinsic::HLSLWaveIntrinsic(GenerationID pid, NodeID nid, Op o)
    : Base(pid, nid, Empty), op(o) {}
CanonicalizeEntryPointIO::HLSLWaveIntrinsic::~HLSLWaveIntrinsic() = default;
std::string CanonicalizeEntryPointIO::HLSLWaveIntrinsic::InternalName() const {
    StringStream ss;
    switch (op) {
        case Op::kWaveGetLaneCount:
            return "intrinsic_wave_get_lane_count";
        case Op::kWaveGetLaneIndex:
            return "intrinsic_wave_get_lane_index";
    }
    return ss.str();
}

const CanonicalizeEntryPointIO::HLSLWaveIntrinsic*
CanonicalizeEntryPointIO::HLSLWaveIntrinsic::Clone(ast::CloneContext& ctx) const {
    return ctx.dst->ASTNodes().Create<CanonicalizeEntryPointIO::HLSLWaveIntrinsic>(
        ctx.dst->ID(), ctx.dst->AllocateNodeID(), op);
}

CanonicalizeEntryPointIO::HLSLClipDistance1::HLSLClipDistance1(GenerationID pid, NodeID nid)
    : Base(pid, nid, Empty) {}

CanonicalizeEntryPointIO::HLSLClipDistance1::~HLSLClipDistance1() = default;

std::string CanonicalizeEntryPointIO::HLSLClipDistance1::InternalName() const {
    return "SV_ClipDistance1";
}

const CanonicalizeEntryPointIO::HLSLClipDistance1*
CanonicalizeEntryPointIO::HLSLClipDistance1::Clone(ast::CloneContext& ctx) const {
    return ctx.dst->ASTNodes().Create<CanonicalizeEntryPointIO::HLSLClipDistance1>(
        ctx.dst->ID(), ctx.dst->AllocateNodeID());
}

}  // namespace tint::ast::transform
