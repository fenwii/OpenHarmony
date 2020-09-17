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
#ifndef MAPLE_ME_INCLUDE_ME_ALIAS_CLASS_H
#define MAPLE_ME_INCLUDE_ME_ALIAS_CLASS_H
#include "alias_class.h"
#include "me_phase.h"
#include "me_function.h"

namespace maple {
class MeAliasClass : public AliasClass {
 public:
  MeAliasClass(MemPool *memPool, MIRModule *mod, SSATab *ssaTab, MeFunction *func, bool lessAliasAtThrow,
               bool finalFieldHasAlias, bool ignoreIPA, bool debug, bool setCalleeHasSideEffect, KlassHierarchy *kh)
      : AliasClass(memPool, mod, ssaTab, lessAliasAtThrow, finalFieldHasAlias, ignoreIPA, setCalleeHasSideEffect, kh),
        func(func) {}

  virtual ~MeAliasClass() = default;

 private:
  MeFunction *func;
  BB *GetBB(BBId id) {
    if (func->GetAllBBs().size() < id.idx) {
      return nullptr;
    }
    return func->GetBBFromID(id);
  }

  bool InConstructorLikeFunc() const {
    return func->GetMirFunc()->IsConstructor() || HasWriteToStaticFinal();
  }

  bool HasWriteToStaticFinal() const;
};

class MeDoAliasClass : public MeFuncPhase {
 public:
  explicit MeDoAliasClass(MePhaseID id) : MeFuncPhase(id) {}

  virtual ~MeDoAliasClass() = default;
  AnalysisResult *Run(MeFunction *ir, MeFuncResultMgr *m, ModuleResultMgr *mrm) override;
  std::string PhaseName() const override {
    return "aliasclass";
  }
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ME_ALIAS_CLASS_H
