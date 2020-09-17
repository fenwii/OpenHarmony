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
#ifndef MAPLE_IR_INCLUDE_JAVA_EH_LOWER_H
#define MAPLE_IR_INCLUDE_JAVA_EH_LOWER_H
#include "phase_impl.h"
#include "module_phase.h"
#include "class_hierarchy.h"

namespace maple {
const std::string strDivOpnd = "__div_opnd1";
const std::string strDivRes = "__div_res";
const std::string strMCCThrowArrayIndexOutOfBoundsException = "MCC_ThrowArrayIndexOutOfBoundsException";
const std::string strMCCThrowNullPointerException = "MCC_ThrowNullPointerException";
class JavaEHLowerer : public FuncOptimizeImpl {
 public:
  explicit JavaEHLowerer(MIRModule *mod, KlassHierarchy *kh, bool dump);
  ~JavaEHLowerer() = default;

  FuncOptimizeImpl *Clone() override {
    return new JavaEHLowerer(*this);
  }

  void ProcessFunc(MIRFunction *func) override;

 private:
  BlockNode *DoLowerBlock(BlockNode*);
  BaseNode *DoLowerExpr(BaseNode*, BlockNode*);
  BaseNode *DoLowerDiv(BinaryNode*, BlockNode*);
  BaseNode *DoLowerRem(BinaryNode *expr, BlockNode *blkNode) {
    return DoLowerDiv(expr, blkNode);
  }

  void DoLowerBoundaryCheck(IntrinsiccallNode*, BlockNode*);

  uint32 divSTIndex;  // The index of divide operand and result.
  bool useRegTmp;     // Use register to save temp variable or not.
};

class JavaEHLowererPhase : public ModulePhase {
 public:
  explicit JavaEHLowererPhase(ModulePhaseID id) : ModulePhase(id) {}

  ~JavaEHLowererPhase() = default;

  std::string PhaseName() const override {
    return "javaehlower";
  }

  AnalysisResult *Run(MIRModule *mod, ModuleResultMgr *mrm) override {
    OPT_TEMPLATE(JavaEHLowerer);
    return nullptr;
  }
};

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_JAVA_EH_LOWER_H
