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

#include "src/tint/lang/core/ir/break_if.h"

#include "gmock/gmock.h"
#include "src/tint/lang/core/ir/ir_helper_test.h"

namespace tint::core::ir {
namespace {

using namespace tint::core::number_suffixes;  // NOLINT
using IR_BreakIfTest = IRTestHelper;
using IR_BreakIfDeathTest = IR_BreakIfTest;

TEST_F(IR_BreakIfTest, Usage) {
    auto* loop = b.Loop();
    auto* cond = b.Constant(true);
    auto* arg1 = b.Constant(1_u);
    auto* arg2 = b.Constant(2_u);

    auto* brk = b.BreakIf(loop, cond, arg1, arg2);

    EXPECT_THAT(cond->UsagesUnsorted(), testing::UnorderedElementsAre(Usage{brk, 0u}));
    EXPECT_THAT(arg1->UsagesUnsorted(), testing::UnorderedElementsAre(Usage{brk, 1u}));
    EXPECT_THAT(arg2->UsagesUnsorted(), testing::UnorderedElementsAre(Usage{brk, 2u}));
}

TEST_F(IR_BreakIfTest, Results) {
    auto* loop = b.Loop();
    auto* cond = b.Constant(true);
    auto* arg1 = b.Constant(1_u);
    auto* arg2 = b.Constant(2_u);

    auto* brk = b.BreakIf(loop, cond, arg1, arg2);
    EXPECT_TRUE(brk->Results().IsEmpty());
}

TEST_F(IR_BreakIfDeathTest, Fail_NullLoop) {
    EXPECT_DEATH_IF_SUPPORTED(
        {
            Module mod;
            Builder b{mod};
            b.BreakIf(nullptr, true);
        },
        "internal compiler error");
}

TEST_F(IR_BreakIfTest, Clone) {
    auto* loop = b.Loop();
    auto* cond = b.Constant(true);
    auto* arg1 = b.Constant(1_u);
    auto* arg2 = b.Constant(2_u);

    auto* brk = b.BreakIf(loop, cond, arg1, arg2);

    auto* new_loop = clone_ctx.Clone(loop);
    clone_ctx.Replace(loop, new_loop);

    auto* new_brk = clone_ctx.Clone(brk);

    EXPECT_NE(brk, new_brk);

    EXPECT_EQ(new_loop, new_brk->Loop());

    auto args = new_brk->Args();
    EXPECT_EQ(2u, args.Length());

    auto new_cond = new_brk->Condition()->As<Constant>()->Value();
    ASSERT_TRUE(new_cond->Is<core::constant::Scalar<bool>>());
    EXPECT_TRUE(new_cond->As<core::constant::Scalar<bool>>()->ValueAs<bool>());

    auto new_arg0 = args[0]->As<Constant>()->Value();
    ASSERT_TRUE(new_arg0->Is<core::constant::Scalar<u32>>());
    EXPECT_EQ(1_u, new_arg0->As<core::constant::Scalar<u32>>()->ValueAs<u32>());

    auto new_arg1 = args[1]->As<Constant>()->Value();
    ASSERT_TRUE(new_arg1->Is<core::constant::Scalar<u32>>());
    EXPECT_EQ(2_u, new_arg1->As<core::constant::Scalar<u32>>()->ValueAs<u32>());
}

TEST_F(IR_BreakIfTest, CloneNoArgs) {
    auto* loop = b.Loop();
    auto* cond = b.Constant(true);

    auto* brk = b.BreakIf(loop, cond);
    auto* new_brk = clone_ctx.Clone(brk);

    auto args = new_brk->Args();
    EXPECT_EQ(0u, args.Length());
}

TEST_F(IR_BreakIfTest, SetLoop) {
    auto* loop1 = b.Loop();
    auto* loop2 = b.Loop();
    auto* cond = b.Constant(true);
    auto* arg1 = b.Constant(1_u);
    auto* arg2 = b.Constant(2_u);

    auto* brk = b.BreakIf(loop1, cond, arg1, arg2);
    EXPECT_THAT(loop1->Exits(), testing::ElementsAre(brk));

    brk->SetLoop(loop2);
    EXPECT_TRUE(loop1->Exits().IsEmpty());
    EXPECT_THAT(loop2->Exits(), testing::ElementsAre(brk));
}

TEST_F(IR_BreakIfTest, Destroy) {
    auto* loop = b.Loop();
    auto* cond = b.Constant(true);
    auto* inst = b.BreakIf(loop, cond);

    ASSERT_EQ(1u, loop->Body()->InboundSiblingBranches().Length());
    EXPECT_EQ(inst, loop->Body()->InboundSiblingBranches()[0]);

    inst->Destroy();

    EXPECT_EQ(0u, loop->Body()->InboundSiblingBranches().Length());
}

}  // namespace
}  // namespace tint::core::ir
