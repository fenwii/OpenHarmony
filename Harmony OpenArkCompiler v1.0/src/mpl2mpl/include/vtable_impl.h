/*
 * Copyright (c) [2019] Huawei Technologies Co.,Ltd.All rights reserved.
 *
 * OpenArkCompiler is licensed under the Mulan PSL v1.
 * You can use this software according to the terms and conditions of the Mulan PSL v1.
 * You may obtain a copy of Mulan PSL v1 at:
 *
 *     http://license.coscl.org.cn/MulanPSL
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT, MERCHANTABILITY OR
 * FIT FOR A PARTICULAR PURPOSE.
 * See the Mulan PSL v1 for more details.
 */
#ifndef MPL2MPL_INCLUDE_VTABLE_IMPL_H
#define MPL2MPL_INCLUDE_VTABLE_IMPL_H
#include "module_phase.h"
#include "phase_impl.h"

namespace maple {
static constexpr int kNumOfMCCParas = 5;
enum CallKind { kVirtual = 1, kNoVirtual = 2};

#ifdef USE_32BIT_REF
static constexpr char kInterfaceMethod[] = "MCC_getFuncPtrFromItab";
#else
static constexpr char kInterfaceMethod[] = "MCC_getFuncPtrFromItabSecondHash64";
#endif

class VtableImpl : public FuncOptimizeImpl {
 public:
  VtableImpl(MIRModule *mod, KlassHierarchy *kh, bool dump);
  ~VtableImpl() {}

  void ProcessFunc(MIRFunction *func) override;
  FuncOptimizeImpl *Clone() override {
    return new (std::nothrow) VtableImpl(*this);
  }

 private:
  MIRModule *mirModule;
  KlassHierarchy *klassHierarchy;
  MIRFunction *mccItabFunc;
  void ReplaceResolveInterface(StmtNode *stmt, const ResolveFuncNode *resolveNode);
};

class DoVtableImpl : public ModulePhase {
 public:
  explicit DoVtableImpl(ModulePhaseID id) : ModulePhase(id) {}

  std::string PhaseName() const override {
    return "VtableImpl";
  }

  ~DoVtableImpl() {}

  AnalysisResult *Run(MIRModule *mod, ModuleResultMgr *mrm) override {
    OPT_TEMPLATE(VtableImpl);
    return nullptr;
  }
};

}  // namespace maple
#endif  // MPL2MPL_INCLUDE_VTABLE_IMPL_H
