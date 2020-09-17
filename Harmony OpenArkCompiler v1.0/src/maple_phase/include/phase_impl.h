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
#ifndef MAPLE_PHASE_INCLUDE_PHASE_IMPL_H
#define MAPLE_PHASE_INCLUDE_PHASE_IMPL_H
#include "class_hierarchy.h"
#include "mir_builder.h"

namespace maple {
class FuncOptimizeImpl {
 public:
  explicit FuncOptimizeImpl(MIRModule *mod, KlassHierarchy *kh = nullptr, bool trace = false);
  virtual ~FuncOptimizeImpl();
  // Each phase needs to implement its own Clone
  virtual FuncOptimizeImpl *Clone() = 0;
  MIRModule *GetModule() {
    return module;
  }

  const MIRModule *GetModule() const {
    return module;
  }

  virtual void ProcessFunc(MIRFunction *func);
  virtual void Finish() {}

 protected:
  void SetCurrentFunction(MIRFunction *func) {
    currFunc = func;
    ASSERT(builder, "builder is null in FuncOptimizeImpl::SetCurrentFunction");
    module->SetCurFunction(func);
  }

  virtual void ProcessBlock(StmtNode *stmt);
  // Each phase needs to implement its own ProcessStmt
  virtual void ProcessStmt(StmtNode *stmt) {}

  KlassHierarchy *klassHierarchy = nullptr;
  MIRFunction *currFunc = nullptr;
  MIRBuilder *builder;
  bool trace = false;

 private:
  MIRModule *module = nullptr;
};

class FuncOptimizeIterator {
 public:
  explicit FuncOptimizeIterator(const std::string &phaseName, FuncOptimizeImpl *phaseImpl);
  virtual ~FuncOptimizeIterator();
  virtual void Run();

 protected:
  FuncOptimizeImpl *phaseImpl;
};

#define OPT_TEMPLATE(OPT_NAME)                                                                 \
  KlassHierarchy *kh = static_cast<KlassHierarchy*>(mrm->GetAnalysisResult(MoPhase_CHA, mod)); \
  ASSERT(kh, "null ptr check");                                                                \
  FuncOptimizeIterator opt(PhaseName(), new OPT_NAME(mod, kh, TRACE_PHASE));                   \
  opt.Run();
}  // namespace maple
#endif  // MAPLE_PHASE_INCLUDE_PHASE_IMPL_H
