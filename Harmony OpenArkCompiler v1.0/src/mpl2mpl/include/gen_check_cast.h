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
#ifndef MPL2MPL_INCLUDE_GEN_CHECK_CAST_H
#define MPL2MPL_INCLUDE_GEN_CHECK_CAST_H
#include "class_hierarchy.h"
#include "module_phase.h"
#include "phase_impl.h"

namespace maple {
static constexpr char kMCCReflectThrowCastException[] = "MCC_Reflect_ThrowCastException";
static constexpr char kMCCReflectCheckCastingNoArray[] = "MCC_Reflect_Check_Casting_NoArray";
static constexpr char kMCCReflectCheckCastingArray[] = "MCC_Reflect_Check_Casting_Array";


class CheckCastGenerator : public FuncOptimizeImpl {
 public:
  CheckCastGenerator(MIRModule *mod, KlassHierarchy *kh, bool dump);
  ~CheckCastGenerator() {}

  FuncOptimizeImpl *Clone() override {
    return new (std::nothrow) CheckCastGenerator(*this);
  }

  void ProcessFunc(MIRFunction *func) override;

 private:
  MIRType *pointerObjType = nullptr;
  MIRFunction *throwCastException = nullptr;
  MIRFunction *checkCastingNoArray = nullptr;
  MIRFunction *checkCastingArray = nullptr;

  void InitTypes();
  void InitFuncs();
  void GenAllCheckCast();
  void GenCheckCast(BaseNode *stmt);
  BaseNode *GetObjectShadow(BaseNode *opnd);
  MIRSymbol *GetOrCreateClassInfoSymbol(const std::string &className);
  bool FindUseExpr(BaseNode *node, StIdx idx);
  bool FindUse(StIdx idx);
};

class DoCheckCastGeneration : public ModulePhase {
 public:
  explicit DoCheckCastGeneration(ModulePhaseID id) : ModulePhase(id) {}

  ~DoCheckCastGeneration() {}

  std::string PhaseName() const override {
    return "gencheckcast";
  }

  AnalysisResult *Run(MIRModule *mod, ModuleResultMgr *mrm) override {
    OPT_TEMPLATE(CheckCastGenerator);
    return nullptr;
  }
};


}  // namespace maple
#endif  // MPL2MPL_INCLUDE_GEN_CHECK_CAST_H
