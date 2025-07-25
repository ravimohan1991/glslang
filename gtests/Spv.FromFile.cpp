 //
// Copyright (C) 2016 Google, Inc.
// Copyright (C) 2019, 2022-2024 Arm Limited.
// Modifications Copyright (C) 2020 Advanced Micro Devices, Inc. All rights reserved.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of Google Inc. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <algorithm>

#include <gtest/gtest.h>

#include "TestFixture.h"

namespace glslangtest {
namespace {

struct IoMapData {
    const char* fileName;
    const char* entryPoint;
    int baseSamplerBinding;
    int baseTextureBinding;
    int baseImageBinding;
    int baseUboBinding;
    int baseSsboBinding;
    bool autoMapBindings;
    bool flattenUniforms;
};

std::string FileNameAsCustomTestSuffixIoMap(
    const ::testing::TestParamInfo<IoMapData>& info) {
    std::string name = info.param.fileName;
    // A valid test case suffix cannot have '.' and '-' inside.
    std::replace(name.begin(), name.end(), '.', '_');
    std::replace(name.begin(), name.end(), '-', '_');
    return name;
}

using CompileVulkanToSpirvTest = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileVulkanToSpirvTestNoLink = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileVulkanToSpirvDeadCodeElimTest = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileVulkan1_1ToSpirvTest = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileToSpirv14Test = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileToSpirv16Test = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileOpenGLToSpirvTest = GlslangTest<::testing::TestWithParam<std::string>>;
using VulkanSemantics = GlslangTest<::testing::TestWithParam<std::string>>;
using OpenGLSemantics = GlslangTest<::testing::TestWithParam<std::string>>;
using VulkanAstSemantics = GlslangTest<::testing::TestWithParam<std::string>>;
using HlslIoMap = GlslangTest<::testing::TestWithParam<IoMapData>>;
using GlslIoMap = GlslangTest<::testing::TestWithParam<IoMapData>>;
using CompileVulkanToSpirvTestQCOM = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileVulkanToSpirvTestAMD = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileVulkanToSpirvTestNV = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileVulkanToSpirv14TestNV = GlslangTest<::testing::TestWithParam<std::string>>;
using CompileUpgradeTextureToSampledTextureAndDropSamplersTest = GlslangTest<::testing::TestWithParam<std::string>>;
using GlslSpirvDebugInfoTest = GlslangTest<::testing::TestWithParam<std::string>>;
using GlslNonSemanticShaderDebugInfoTest = GlslangTest<::testing::TestWithParam<std::string>>;
using GlslNonSemanticShaderDebugInfoSpirv13Test = GlslangTest<::testing::TestWithParam<std::string>>;

// Compiling GLSL to SPIR-V under Vulkan semantics. Expected to successfully
// generate SPIR-V.
TEST_P(CompileVulkanToSpirvTest, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0,
                            Target::Spv);
}

// Compiling GLSL to SPIR-V under Vulkan semantics without linking. Expected to successfully generate SPIR-V.
TEST_P(CompileVulkanToSpirvTestNoLink, FromFile)
{
    options().compileOnly = true;
    // NOTE: Vulkan 1.3 is currently required to use the linkage capability
    // TODO(ncesario) make sure this is actually necessary
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(), Source::GLSL, Semantics::Vulkan,
                            glslang::EShTargetVulkan_1_3, glslang::EShTargetSpv_1_0, Target::Spv);
}

TEST_P(CompileVulkanToSpirvDeadCodeElimTest, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0,
                            Target::Spv);
}


TEST_P(CompileVulkan1_1ToSpirvTest, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_1, glslang::EShTargetSpv_1_3,
                            Target::Spv);
}

TEST_P(CompileToSpirv14Test, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_1, glslang::EShTargetSpv_1_4,
                            Target::Spv);
}

TEST_P(CompileToSpirv16Test, FromFileTargetVulkan1_3)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_3, glslang::EShTargetSpv_1_6,
                            Target::Spv);
}

TEST_P(CompileToSpirv16Test, FromFileTargetVulkan1_4)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_4, glslang::EShTargetSpv_1_6,
                            Target::Spv);
}

// Compiling GLSL to SPIR-V under OpenGL semantics. Expected to successfully
// generate SPIR-V.
TEST_P(CompileOpenGLToSpirvTest, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::OpenGL, glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0,
                            Target::Spv);
}

// GLSL-level Vulkan semantics test. Expected to error out before generating
// SPIR-V.
TEST_P(VulkanSemantics, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0,
                            Target::Spv, false);
}

// GLSL-level Vulkan semantics test. Expected to error out before generating
// SPIR-V.
TEST_P(OpenGLSemantics, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::OpenGL, glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0,
                            Target::Spv, false);
}

// GLSL-level Vulkan semantics test that need to see the AST for validation.
TEST_P(VulkanAstSemantics, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0,
                            Target::AST);
}

// HLSL-level Vulkan semantics tests.
TEST_P(HlslIoMap, FromFile)
{
    loadFileCompileIoMapAndCheck(GlobalTestSettings.testRoot, GetParam().fileName,
                                 Source::HLSL, Semantics::Vulkan,
                                 Target::Spv, GetParam().entryPoint,
                                 GetParam().baseSamplerBinding,
                                 GetParam().baseTextureBinding,
                                 GetParam().baseImageBinding,
                                 GetParam().baseUboBinding,
                                 GetParam().baseSsboBinding,
                                 GetParam().autoMapBindings,
                                 GetParam().flattenUniforms);
}

// GLSL-level Vulkan semantics tests.
TEST_P(GlslIoMap, FromFile)
{
    loadFileCompileIoMapAndCheck(GlobalTestSettings.testRoot, GetParam().fileName,
                                 Source::GLSL, Semantics::Vulkan,
                                 Target::Spv, GetParam().entryPoint,
                                 GetParam().baseSamplerBinding,
                                 GetParam().baseTextureBinding,
                                 GetParam().baseImageBinding,
                                 GetParam().baseUboBinding,
                                 GetParam().baseSsboBinding,
                                 GetParam().autoMapBindings,
                                 GetParam().flattenUniforms);
}

// Compiling GLSL to SPIR-V under Vulkan semantics (QCOM extensions enabled).
// Expected to successfully generate SPIR-V.
TEST_P(CompileVulkanToSpirvTestQCOM, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0,
                            Target::Spv);
}

// Compiling GLSL to SPIR-V under Vulkan semantics (AMD extensions enabled).
// Expected to successfully generate SPIR-V.
TEST_P(CompileVulkanToSpirvTestAMD, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0,
                            Target::Spv);
}

// Compiling GLSL to SPIR-V under Vulkan semantics (NV extensions enabled).
// Expected to successfully generate SPIR-V.
TEST_P(CompileVulkanToSpirvTestNV, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0,
                            Target::Spv);
}

TEST_P(CompileVulkanToSpirv14TestNV, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(),
                            Source::GLSL, Semantics::Vulkan, glslang::EShTargetVulkan_1_1, glslang::EShTargetSpv_1_4,
                            Target::Spv);
}

TEST_P(CompileUpgradeTextureToSampledTextureAndDropSamplersTest, FromFile)
{
    loadCompileUpgradeTextureToSampledTextureAndDropSamplersAndCheck(GlobalTestSettings.testRoot,
                                                                     GetParam(),
                                                                     Source::GLSL,
                                                                     Semantics::Vulkan,
                                                                     Target::Spv);
}

TEST_P(GlslSpirvDebugInfoTest, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(), Source::GLSL, Semantics::Vulkan,
                            glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0, Target::Spv, true, "",
                            "/baseResults/", false, true, false);
}

TEST_P(GlslNonSemanticShaderDebugInfoTest, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(), Source::GLSL, Semantics::Vulkan,
                            glslang::EShTargetVulkan_1_0, glslang::EShTargetSpv_1_0, Target::Spv, true, "",
                            "/baseResults/", false, true, true);
}

TEST_P(GlslNonSemanticShaderDebugInfoSpirv13Test, FromFile)
{
    loadFileCompileAndCheck(GlobalTestSettings.testRoot, GetParam(), Source::GLSL, Semantics::Vulkan,
                            glslang::EShTargetVulkan_1_1, glslang::EShTargetSpv_1_3, Target::Spv, true, "",
                            "/baseResults/", false, true, true);
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileVulkanToSpirvTest,
    ::testing::ValuesIn(std::vector<std::string>({
        // Test looping constructs.
        // No tests yet for making sure break and continue from a nested loop
        // goes to the innermost target.
        "spv.barrier.vert",
        "spv.do-simple.vert",
        "spv.do-while-continue-break.vert",
        "spv.for-complex-condition.vert",
        "spv.for-continue-break.vert",
        "spv.for-simple.vert",
        "spv.for-notest.vert",
        "spv.for-nobody.vert",
        "spv.while-continue-break.vert",
        "spv.while-simple.vert",
        // vulkan-specific tests
        "rayQuery.rgen",
        "rayQuery-no-cse.rgen",
        "rayQuery-initialize.rgen",
        "rayQuery-allOps.rgen",
        "rayQuery-allOps.Error.rgen",
        "rayQuery-committed.Error.rgen",
        "rayQuery-allOps.comp",
        "rayQuery-allOps.frag",
        "rayQuery-initialization.Error.comp",
        "rayQuery-global.rgen",
        "rayQuery-types.comp",
        "rayQuery-OpConvertUToAccelerationStructureKHR.comp",
        "spv.set.vert",
        "spv.double.comp",
        "spv.100ops.frag",
        "spv.130.frag",
        "spv.140.frag",
        "spv.150.geom",
        "spv.150.vert",
        "spv.16bitstorage.frag",
        "spv.16bitstorage_Error.frag",
        "spv.16bitstorage-int.frag",
        "spv.16bitstorage_Error-int.frag",
        "spv.16bitstorage-uint.frag",
        "spv.16bitstorage_Error-uint.frag",
        "spv.300BuiltIns.vert",
        "spv.300layout.frag",
        "spv.300layout.vert",
        "spv.300layoutp.vert",
        "spv.310.comp",
        "spv.310.bitcast.frag",
        "spv.330.geom",
        "spv.400.frag",
        "spv.400.tesc",
        "spv.400.tese",
        "spv.420.geom",
        "spv.430.frag",
        "spv.430.vert",
        "spv.450.tesc",
        "spv.450.geom",
        "spv.450.noRedecl.tesc",
        "spv.8bitstorage-int.frag",
        "spv.8bitstorage_Error-int.frag",
        "spv.8bitstorage-uint.frag",
        "spv.8bitstorage_Error-uint.frag",
        "spv.8bitstorage-ubo.vert",
        "spv.8bitstorage-ssbo.vert",
        "spv.8bit-16bit-construction.frag",
        "spv.accessChain.frag",
        "spv.aggOps.frag",
        "spv.always-discard.frag",
        "spv.always-discard2.frag",
        "spv.arbPostDepthCoverage.frag",
        "spv.arbPostDepthCoverage_Error.frag",
        "spv.atomicCounter.comp",
        "spv.bitCast.frag",
        "spv.bool.vert",
        "spv.boolInBlock.frag",
        "spv.branch-return.vert",
        "spv.bufferhandle11.frag",
        "spv.bufferhandle12.frag",
        "spv.bufferhandle13.frag",
        "spv.bufferhandle14.frag",
        "spv.bufferhandle15.frag",
        "spv.bufferhandle16.frag",
        "spv.bufferhandle17_Errors.frag",
        "spv.bufferhandle18.frag",
        "spv.bufferhandle19_Errors.frag",
        "spv.bufferhandle2.frag",
        "spv.bufferhandle3_Errors.frag",
        "spv.bufferhandle4.frag",
        "spv.bufferhandle5.frag",
        "spv.bufferhandle6.frag",
        "spv.bufferhandle7.frag",
        "spv.bufferhandle8.frag",
        "spv.bufferhandle9.frag",
        "spv.bufferhandleUvec2.frag",
        "spv.bufferhandle_Error.frag",
        "spv.builtInXFB.vert",
        "spv.conditionalDemote.frag",
        "spv.conditionalDiscard.frag",
        "spv.constructComposite.comp",
        "spv.constStruct.vert",
        "spv.constConstruct.vert",
        "spv.controlFlowAttributes.frag",
        "spv.conversion.frag",
        "spv.dataOut.frag",
        "spv.dataOutIndirect.frag",
        "spv.dataOutIndirect.vert",
        "spv.debugPrintf.frag",
        "spv.debugPrintf_Error.frag",
        "spv.demoteDisabled.frag",
        "spv.deepRvalue.frag",
        "spv.depthOut.frag",
        "spv.depthUnchanged.frag",
        "spv.discard-dce.frag",
        "spv.doWhileLoop.frag",
        "spv.earlyReturnDiscard.frag",
        "spv.expect_assume.assumeEXT.comp",
        "spv.expect_assume.expectEXT.comp",
        "spv.expect_assume.expectEXT.exttypes.comp",
        "spv.ext.ShaderTileImage.color.frag",
        "spv.ext.ShaderTileImage.depth_stencil.frag",
        "spv.ext.ShaderTileImage.subpassinput.frag",
        "spv.ext.ShaderTileImage.typemismatch.frag",
        "spv.ext.ShaderTileImage.overlap.frag",
        "spv.ext.ShaderTileImage.wronglayout.frag",
        "spv.extPostDepthCoverage.frag",
        "spv.extPostDepthCoverage_Error.frag",
        "spv.float16convertonlyarith.comp",
        "spv.float16convertonlystorage.comp",
        "spv.flowControl.frag",
        "spv.forLoop.frag",
        "spv.forwardFun.frag",
        "spv.fp8_error.frag",
        "spv.fragmentDensity.frag",
        "spv.fragmentDensity.vert",
        "spv.fragmentDensity-es.frag",
        "spv.fragmentDensity-neg.frag",
        "spv.fsi.frag",
        "spv.fsi_Error.frag",
        "spv.fullyCovered.frag",
        "spv.functionCall.frag",
        "spv.functionNestedOpaque.vert",
        "spv.functionSemantics.frag",
        "spv.functionParameterTypes.frag",
        "spv.GeometryShaderPassthrough.geom",
        "spv.funcall.array.frag",
        "spv.load.bool.array.interface.block.frag",
        "spv.int_dot.frag",
        "spv.int_dot_Error.frag",
        "spv.interpOps.frag",
        "spv.int64.frag",
        "spv.intOps.vert",
        "spv.intrinsicsDebugBreak.frag",
        "spv.intrinsicsSpirvByReference.vert",
        "spv.intrinsicsSpirvDecorate.frag",
        "spv.intrinsicsSpirvDecorateId.comp",
        "spv.intrinsicsSpirvDecorateString.comp",
        "spv.intrinsicsSpirvExecutionMode.frag",
        "spv.intrinsicsSpirvInstruction.vert",
        "spv.intrinsicsSpirvLiteral.vert",
        "spv.intrinsicsSpirvStorageClass.rchit",
        "spv.intrinsicsSpirvType.rgen",
        "spv.intrinsicsSpirvTypeLocalVar.vert",
        "spv.intrinsicsSpirvTypeWithTypeSpecifier.vert",
        "spv.invariantAll.vert",
        "spv.layer.tese",
        "spv.layoutNested.vert",
        "spv.length.frag",
        "spv.localAggregates.frag",
        "spv.loops.frag",
        "spv.loopsArtificial.frag",
        "spv.matFun.vert",
        "spv.matrix.frag",
        "spv.matrix2.frag",
        "spv.maximalReconvergence.vert",
        "spv.memoryQualifier.frag",
        "spv.merge-unreachable.frag",
        "spv.multiStruct.comp",
        "spv.multiStructFuncall.frag",
        "spv.newTexture.frag",
        "spv.noDeadDecorations.vert",
        "spv.nonSquare.vert",
        "spv.nonuniform.frag",
        "spv.nonuniform2.frag",
        "spv.nonuniform3.frag",
        "spv.nonuniform4.frag",
        "spv.nonuniform5.frag",
        "spv.noWorkgroup.comp",
        "spv.nvAtomicFp16Vec.frag",
        "spv.nullInit.comp",
        "spv.offsets.frag",
        "spv.Operations.frag",
        "spv.paramMemory.frag",
        "spv.paramMemory.420.frag",
        "spv.precision.frag",
        "spv.precisionArgs.frag",
        "spv.precisionNonESSamp.frag",
        "spv.precisionTexture.frag",
        "spv.prepost.frag",
        "spv.privateVariableTypes.frag",
        "spv.qualifiers.vert",
        "spv.sample.frag",
        "spv.sampleId.frag",
        "spv.samplePosition.frag",
        "spv.sampleMaskOverrideCoverage.frag",
        "spv.scalarlayout.frag",
        "spv.scalarlayoutfloat16.frag",
        "spv.shaderBallot.comp",
        "spv.shaderDrawParams.vert",
        "spv.shaderGroupVote.comp",
        "spv.shaderStencilExport.frag",
        "spv.shiftOps.frag",
        "spv.simpleFunctionCall.frag",
        "spv.simpleMat.vert",
        "spv.sparseTexture.frag",
        "spv.sparseTextureClamp.frag",
        "spv.structAssignment.frag",
        "spv.structCopy.comp",
        "spv.structDeref.frag",
        "spv.structure.frag",
        "spv.switch.frag",
        "spv.swizzle.frag",
        "spv.swizzleInversion.frag",
        "spv.test.frag",
        "spv.test.vert",
        "spv.texture.frag",
        "spv.texture.vert",
        "spv.textureBuffer.vert",
        "spv.image.frag",
        "spv.imageAtomic64.frag",
        "spv.imageAtomic64.comp",
        "spv.types.frag",
        "spv.uint.frag",
        "spv.uniformArray.frag",
        "spv.variableArrayIndex.frag",
        "spv.varyingArray.frag",
        "spv.varyingArrayIndirect.frag",
        "spv.vecMatConstruct.frag",
        "spv.voidFunction.frag",
        "spv.whileLoop.frag",
        "spv.AofA.frag",
        "spv.queryL.frag",
        "spv.separate.frag",
        "spv.shortCircuit.frag",
        "spv.pushConstant.vert",
        "spv.pushConstantAnon.vert",
        "spv.subpass.frag",
        "spv.specConstant.vert",
        "spv.specConstant.comp",
        "spv.specConstantComposite.vert",
        "spv.specConstantOperations.vert",
        "spv.specConstant.float16.comp",
        "spv.specConstant.int16.comp",
        "spv.specConstant.int8.comp",
        "spv.specConstantOp.int16.comp",
        "spv.specConstantOp.int8.comp",
        "spv.specConstantOp.float16.comp",
        "spv.storageBuffer.vert",
        "spv.terminate.frag",
        "spv.subgroupUniformControlFlow.vert",
        "spv.subgroupSizeARB.frag",
        "spv.precise.tese",
        "spv.precise.tesc",
        "spv.viewportindex.tese",
        "spv.volatileAtomic.comp",
        "spv.vulkan100.subgroupArithmetic.comp",
        "spv.vulkan100.subgroupPartitioned.comp",
        "spv.xfb.vert",
        "spv.xfb2.vert",
        "spv.xfb3.vert",
        "spv.samplerlessTextureFunctions.frag",
        "spv.smBuiltins.vert",
        "spv.smBuiltins.frag",
        "spv.ARMCoreBuiltIns.vert",
        "spv.ARMCoreBuiltIns.frag",
        "spv.builtin.PrimitiveShadingRateEXT.vert",
        "spv.builtin.ShadingRateEXT.frag",
        "spv.fragmentShaderBarycentric3.frag",
        "spv.fragmentShaderBarycentric4.frag",
        "spv.ext.textureShadowLod.frag",
        "spv.ext.textureShadowLod.error.frag",
        "spv.floatFetch.frag",
        "spv.atomicRvalue.error.vert",
        "spv.sampledImageBlock.frag",
        "spv.multiple.var.same.const.frag",
        "spv.textureoffset_non_const.vert",
        "spv.sparsetextureoffset_non_const.vert",
        "spv.sparsetextureoffset_non_const_fail.vert",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileVulkanToSpirvTestNoLink,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.exportFunctions.comp",
    })),
    FileNameAsCustomTestSuffix
);

// Cases with deliberately unreachable code.
// By default the compiler will aggressively eliminate
// unreachable merges and continues.
INSTANTIATE_TEST_SUITE_P(
    GlslWithDeadCode, CompileVulkanToSpirvDeadCodeElimTest,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.dead-after-continue.vert",
        "spv.dead-after-discard.frag",
        "spv.dead-after-return.vert",
        "spv.dead-after-loop-break.vert",
        "spv.dead-after-switch-break.vert",
        "spv.dead-complex-continue-after-return.vert",
        "spv.dead-complex-merge-after-return.vert",
    })),
    FileNameAsCustomTestSuffix
);

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileVulkan1_1ToSpirvTest,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.1.3.8bitstorage-ubo.vert",
        "spv.1.3.8bitstorage-ssbo.vert",
        "spv.1.3.coopmat.comp",
        "spv.deviceGroup.frag",
        "spv.drawParams.vert",
        "spv.int8.frag",
        "spv.vulkan110.int16.frag",
        "spv.int32.frag",
        "spv.explicittypes.frag",
        "spv.float16NoRelaxed.vert",
        "spv.float32.frag",
        "spv.float64.frag",
        "spv.memoryScopeSemantics.comp",
        "spv.memoryScopeSemantics_Error.comp",
        "spv.multiView.frag",
        "spv.queueFamilyScope.comp",
        "spv.RayGenShader11.rgen",
        "spv.subgroup.frag",
        "spv.subgroup.geom",
        "spv.subgroup.tesc",
        "spv.subgroup.tese",
        "spv.subgroup.vert",
        "spv.subgroupArithmetic.comp",
        "spv.subgroupBasic.comp",
        "spv.subgroupBallot.comp",
        "spv.subgroupBallotNeg.comp",
        "spv.subgroupClustered.comp",
        "spv.subgroupClusteredNeg.comp",
        "spv.subgroupPartitioned.comp",
        "spv.subgroupRotate.comp",
        "spv.subgroupShuffle.comp",
        "spv.subgroupShuffleRelative.comp",
        "spv.subgroupQuad.comp",
        "spv.subgroupVote.comp",
        "spv.subgroupExtendedTypesArithmetic.comp",
        "spv.subgroupExtendedTypesArithmeticNeg.comp",
        "spv.subgroupExtendedTypesBallot.comp",
        "spv.subgroupExtendedTypesBallotNeg.comp",
        "spv.subgroupExtendedTypesClustered.comp",
        "spv.subgroupExtendedTypesClusteredNeg.comp",
        "spv.subgroupExtendedTypesPartitioned.comp",
        "spv.subgroupExtendedTypesPartitionedNeg.comp",
        "spv.subgroupExtendedTypesRotate.comp",
        "spv.subgroupExtendedTypesRotateNeg.comp",
        "spv.subgroupExtendedTypesShuffle.comp",
        "spv.subgroupExtendedTypesShuffleNeg.comp",
        "spv.subgroupExtendedTypesShuffleRelative.comp",
        "spv.subgroupExtendedTypesShuffleRelativeNeg.comp",
        "spv.subgroupExtendedTypesQuad.comp",
        "spv.subgroupExtendedTypesQuadNeg.comp",
        "spv.subgroupExtendedTypesVote.comp",
        "spv.subgroupExtendedTypesVoteNeg.comp",
        "spv.vulkan110.storageBuffer.vert",

        // These tests use the Vulkan memory model.
        "spv.bfloat16.comp",
        "spv.bfloat16_error.comp",
        "spv.bfloat16_error.frag",
        "spv.bufferhandle1.frag",
        "spv.bufferhandle10.frag",
        "spv.coopmat.comp",
        "spv.coopmat_Error.comp",
        "spv.coopmatKHR.comp",
        "spv.coopmat_armlayout.comp",
        "spv.coopmatKHR_arithmetic.comp",
        "spv.coopmatKHR_arithmeticError.comp",
        "spv.coopmatKHR_Error.comp",
        "spv.coopmatKHR_constructor.comp",
        "spv.coopmatKHR_constructorError.comp",
        "spv.coopvec.comp",
        "spv.coopvec2.comp",
        "spv.coopvecloadstore.comp",
        "spv.coopvec_Error.comp",
        "spv.coopvecTraining.comp",
        "spv.coopvecTraining_Error.comp",
        "spv.intcoopmat.comp",
        "spv.intrinsicsInteractWithCoopMat.comp",
        "spv.replicate.comp",
        "spv.replicatespec.comp",
        "spv.atomicAdd.bufferReference.comp",
        "spv.nontemporalbuffer.frag",
        "spv.atomicFloat.comp",
    })),
    FileNameAsCustomTestSuffix
);

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileToSpirv14Test,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.1.4.LoopControl.frag",
        "spv.1.4.NonWritable.frag",
        "spv.1.4.OpEntryPoint.frag",
        "spv.1.4.OpEntryPoint.opaqueParams.vert",
        "spv.1.4.OpSelect.frag",
        "spv.1.4.OpCopyLogical.comp",
        "spv.1.4.OpCopyLogicalBool.comp",
        "spv.1.4.OpCopyLogical.funcall.frag",
        "spv.1.4.funcall.array.frag",
        "spv.1.4.load.bool.array.interface.block.frag",
        "spv.1.4.image.frag",
        "spv.1.4.sparseTexture.frag",
        "spv.1.4.texture.frag",
        "spv.1.4.constructComposite.comp",
        "spv.ext.AnyHitShader.rahit",
        "spv.ext.AnyHitShader_Errors.rahit",
        "spv.ext.ClosestHitShader.rchit",
        "spv.ext.ClosestHitShader_Subgroup.rchit",
        "spv.ext.ClosestHitShader_Errors.rchit",
        "spv.ext.IntersectShader.rint",
        "spv.ext.IntersectShader_Errors.rint",
        "spv.ext.MissShader.rmiss",
        "spv.ext.MissShader_Errors.rmiss",
        "spv.ext.RayPrimCull_Errors.rgen",
        "spv.ext.RayCallable.rcall",
        "spv.ext.RayCallable_Errors.rcall",
        "spv.ext.RayConstants.rgen",
        "spv.ext.RayGenShader.rgen",
        "spv.ext.RayGenShader_Errors.rgen",
        "spv.ext.RayGenShader11.rgen",
        "spv.ext.RayGenShaderArray.rgen",
        "spv.ext.RayGenSBTlayout.rgen",
        "spv.ext.RayGenSBTlayout140.rgen",
        "spv.ext.RayGenSBTlayout430.rgen",
        "spv.ext.RayGenSBTlayoutscalar.rgen",
        "spv.ext.World3x4.rahit",
        "spv.ext.AccelDecl.frag",
        "spv.ext.RayQueryDecl.frag",

        // SPV_KHR_workgroup_memory_explicit_layout depends on SPIR-V 1.4.
        "spv.WorkgroupMemoryExplicitLayout.SingleBlock.comp",
        "spv.WorkgroupMemoryExplicitLayout.MultiBlock.comp",
        "spv.WorkgroupMemoryExplicitLayout.8BitAccess.comp",
        "spv.WorkgroupMemoryExplicitLayout.16BitAccess.comp",
        "spv.WorkgroupMemoryExplicitLayout.NonBlock.comp",
        "spv.WorkgroupMemoryExplicitLayout.MixBlockNonBlock_Errors.comp",
        "spv.WorkgroupMemoryExplicitLayout.std140.comp",
        "spv.WorkgroupMemoryExplicitLayout.std430.comp",
        "spv.WorkgroupMemoryExplicitLayout.scalar.comp",

        // SPV_EXT_mesh_shader
        "spv.ext.meshShaderBuiltins.mesh",
        "spv.ext.meshShaderBuiltinsShadingRate.mesh",
        "spv.ext.meshShaderRedeclBuiltins.mesh",
        "spv.ext.meshShaderTaskMem.mesh",
        "spv.ext.meshShaderUserDefined.mesh",
        "spv.ext.meshTaskShader.task",
        "spv.atomiAddEXT.error.mesh",
        "spv.atomiAddEXT.task",
        "spv.460.subgroupEXT.task",
        "spv.460.subgroupEXT.mesh",

        // SPV_NV_shader_execution_reorder

        "spv.nv.hitobject-errors.rgen",
        "spv.nv.hitobject-allops.rgen",
        "spv.nv.hitobject-allops.rchit",
        "spv.nv.hitobject-allops.rmiss",


        // SPV_NV_displacment_micromap

        "spv.nv.dmm-allops.rgen",
        "spv.nv.dmm-allops.rchit",
        "spv.nv.dmm-allops.rahit",
        "spv.nv.dmm-allops.mesh",
        "spv.nv.dmm-allops.comp",

        // SPV_NV_cluster_acceleration_structure
        "spv.nv.cluster-allops.rgen",
        "spv.nv.cluster-allops.rchit",
        "spv.nv.cluster-allops.rmiss",
        "spv.nv.cluster-allops.rahit",
        "spv.nv.cluster-allops.frag",

        // SPV_NV_linear_swept_spheres

        "spv.nv.lss-allops.rgen",
        "spv.nv.lss-allops.rchit",
        "spv.nv.lss-allops.rmiss",
        "spv.nv.lss-allops.frag",
        "spv.nv.lss-spheregeomcap.rgen",
        "spv.nv.lss-lssgeomcap.rgen",

    })),
    FileNameAsCustomTestSuffix
);

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileToSpirv16Test,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.1.6.conditionalDiscard.frag",
        "spv.1.6.helperInvocation.frag",
        "spv.1.6.helperInvocation.memmodel.frag",
        "spv.1.6.specConstant.comp",
        "spv.1.6.samplerBuffer.frag",
        "spv.1.6.separate.frag",
        "spv.1.6.quad.frag",
        "spv.coopmat2_constructor.comp",
        "spv.coopmat2_error.comp",
        "spv.coopmat2_tensor.comp",
        "spv.1.6.nontemporalimage.frag",
        "spv.noexplicitlayout.comp",
        "spv.floate4m3.comp",
        "spv.floate4m3_error.comp",
        "spv.floate5m2.comp",
        "spv.floate5m2_error.comp",
    })),
    FileNameAsCustomTestSuffix
);


// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Hlsl, HlslIoMap,
    ::testing::ValuesIn(std::vector<IoMapData>{
        { "spv.register.autoassign.frag", "main_ep", 5, 10, 0, 20, 30, true, false },
        { "spv.register.noautoassign.frag", "main_ep", 5, 10, 0, 15, 30, false, false },
        { "spv.register.autoassign-2.frag", "main", 5, 10, 0, 15, 30, true, true },
        { "spv.register.subpass.frag", "main", 0, 20, 0, 0, 0, true, true },
        { "spv.buffer.autoassign.frag", "main", 5, 10, 0, 15, 30, true, true },
        { "spv.ssbo.autoassign.frag", "main", 5, 10, 0, 15, 30, true, true },
        { "spv.ssboAlias.frag", "main", 0, 0, 0, 0, 83, true, false },
        { "spv.rw.autoassign.frag", "main", 5, 10, 20, 15, 30, true, true },
        { "spv.register.autoassign.rangetest.frag", "main",
                glslang::TQualifier::layoutBindingEnd-2,
                glslang::TQualifier::layoutBindingEnd+5,
                0, 20, 30, true, false },
    }),
    FileNameAsCustomTestSuffixIoMap
);

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Hlsl, GlslIoMap,
    ::testing::ValuesIn(std::vector<IoMapData>{
        { "spv.glsl.register.autoassign.frag", "main", 5, 10, 0, 20, 30, true, false },
        { "spv.glsl.register.noautoassign.frag", "main", 5, 10, 0, 15, 30, false, false },
    }),
    FileNameAsCustomTestSuffixIoMap
);

// clang-format off
INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileOpenGLToSpirvTest,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.460.frag",
        "spv.460.vert",
        "spv.460.comp",
        "spv.atomic.comp",
        "spv.atomicFloat_Error.comp",
        "spv.glFragColor.frag",
        "spv.rankShift.comp",
        "spv.specConst.vert",
        "spv.specTexture.frag",
        "spv.OVR_multiview.vert",
        "spv.uniformInitializer.frag",
        "spv.uniformInitializerSpecConstant.frag",
        "spv.uniformInitializerStruct.frag",
        "spv.xfbOffsetOnBlockMembersAssignment.vert",
        "spv.xfbOffsetOnStructMembersAssignment.vert",
        "spv.xfbOverlapOffsetCheckWithBlockAndMember.vert",
        "spv.xfbStrideJustOnce.vert",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, VulkanSemantics,
    ::testing::ValuesIn(std::vector<std::string>({
        "vulkan.frag",
        "vulkan.vert",
        "vulkan.comp",
        "samplerlessTextureFunctions.frag",
        "spv.intrinsicsFakeEnable.vert",
        "spv.specConstArrayCheck.vert",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, OpenGLSemantics,
    ::testing::ValuesIn(std::vector<std::string>({
        "glspv.esversion.vert",
        "glspv.version.frag",
        "glspv.version.vert",
        "glspv.frag",
        "glspv.vert",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, VulkanAstSemantics,
    ::testing::ValuesIn(std::vector<std::string>({
        "vulkan.ast.vert",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileVulkanToSpirvTestQCOM,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.tpipSampleWeighted.frag",
        "spv.tpipBoxFilter.frag",
        "spv.tpipBlockMatchSSD.frag",
        "spv.tpipBlockMatchSAD.frag",
        "spv.tpipTextureArrays.frag",
        "spv.tpipBlockMatchGatherSAD.frag",
        "spv.tpipBlockMatchGatherSSD.frag",
        "spv.tpipBlockMatchWindowSAD.frag",
        "spv.tpipBlockMatchWindowSSD.frag",
        "spv.qcom.tileShading.0.comp",
        "spv.qcom.tileShading.1.comp",
        "spv.qcom.es.tileShading.0.comp",
        "spv.qcom.es.tileShading.1.comp",
        "spv.qcom.es.tileShading.2.comp",
        "spv.qcom.tileShading.0.frag",
        "spv.qcom.tileShading.1.frag",
        "spv.qcom.es.tileShading.0.frag",
        "spv.qcom.es.tileShading.1.frag",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileVulkanToSpirvTestAMD,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.16bitxfb.vert",
        "spv.float16.frag",
        "spv.float16Fetch.frag",
        "spv.imageLoadStoreLod.frag",
        "spv.int16.frag",
        "spv.int16.amd.frag",
        "spv.shaderBallotAMD.comp",
        "spv.shaderFragMaskAMD.frag",
        "spv.textureGatherBiasLod.frag",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileVulkanToSpirvTestNV,
    ::testing::ValuesIn(std::vector<std::string>({
    "spv.sampleMaskOverrideCoverage.frag",
    "spv.GeometryShaderPassthrough.geom",
    "spv.viewportArray2.vert",
    "spv.viewportArray2.tesc",
    "spv.stereoViewRendering.vert",
    "spv.stereoViewRendering.tesc",
    "spv.multiviewPerViewAttributes.vert",
    "spv.multiviewPerViewAttributes.tesc",
    "spv.atomicInt64.comp",
    "spv.atomicStoreInt64.comp",
    "spv.shadingRate.frag",
    "spv.RayGenShader.rgen",
    "spv.RayGenShaderArray.rgen",
    "spv.RayGenShader_Errors.rgen",
    "spv.RayConstants.rgen",
    "spv.IntersectShader.rint",
    "spv.IntersectShader_Errors.rint",
    "spv.AnyHitShader.rahit",
    "spv.AnyHitShader_Errors.rahit",
    "spv.ClosestHitShader.rchit",
    "spv.ClosestHitShader_Errors.rchit",
    "spv.MissShader.rmiss",
    "spv.MissShader_Errors.rmiss",
    "spv.RayCallable.rcall",
    "spv.RayCallable_Errors.rcall",
    "spv.fragmentShaderBarycentric.frag",
    "spv.fragmentShaderBarycentric2.frag",
    "spv.computeShaderDerivatives.comp",
    "spv.computeShaderDerivatives2.comp",
    "spv.computeShaderDerivativesSpec.comp",
    "spv.computeShaderDerivativesSpec2.comp",
    "spv.shaderImageFootprint.frag",
    "spv.meshShaderBuiltins.mesh",
    "spv.meshShaderUserDefined.mesh",
    "spv.meshShaderPerViewBuiltins.mesh",
    "spv.meshShaderPerViewUserDefined.mesh",
    "spv.meshShaderPerView_Errors.mesh",
    "spv.meshShaderSharedMem.mesh",
    "spv.meshShaderTaskMem.mesh",
    "spv.320.meshShaderUserDefined.mesh",
    "spv.meshShaderRedeclBuiltins.mesh",
    "spv.meshShaderRedeclPerViewBuiltins.mesh",
    "spv.meshTaskShader.task",
    "spv.perprimitiveNV.frag",
    "spv.nvgpushader5.frag"
})),
FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileVulkanToSpirv14TestNV,
    ::testing::ValuesIn(std::vector<std::string>({
    "spv.RayGenShaderMotion.rgen",
    "spv.IntersectShaderMotion.rint",
    "spv.AnyHitShaderMotion.rahit",
    "spv.ClosestHitShaderMotion.rchit",
    "spv.MissShaderMotion.rmiss",
})),
FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, CompileUpgradeTextureToSampledTextureAndDropSamplersTest,
    ::testing::ValuesIn(std::vector<std::string>({
      "spv.texture.sampler.transform.frag",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, GlslSpirvDebugInfoTest,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.pp.line.frag",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, GlslNonSemanticShaderDebugInfoTest,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.debuginfo.glsl.vert",
        "spv.debuginfo.glsl.frag",
        "spv.debuginfo.glsl.comp",
        "spv.debuginfo.glsl.geom",
        "spv.debuginfo.glsl.tesc",
        "spv.debuginfo.glsl.tese",
        "spv.debuginfo.bufferref.glsl.frag",
        "spv.debuginfo.const_params.glsl.comp",
        "spv.debuginfo.scalar_types.glsl.frag",
        "spv.debuginfo.rt_types.glsl.rgen",
        "spv.debuginfo.include.glsl.frag",
        "spv.debuginfo.multiline.glsl.frag",
        "spv.debuginfo.implicit_br.glsl.frag",
        "spv.debuginfo.non_ascii.glsl.frag",
        "spv.debuginfo.continued.glsl.vert",
    })),
    FileNameAsCustomTestSuffix
);

INSTANTIATE_TEST_SUITE_P(
    Glsl, GlslNonSemanticShaderDebugInfoSpirv13Test,
    ::testing::ValuesIn(std::vector<std::string>({
        "spv.debuginfo.coopmatKHR.comp",
    })),
    FileNameAsCustomTestSuffix
);
// clang-format on

}  // anonymous namespace
}  // namespace glslangtest
