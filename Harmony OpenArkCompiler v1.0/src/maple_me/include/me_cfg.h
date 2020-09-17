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
#ifndef MAPLE_ME_INCLUDE_ME_CFG_H
#define MAPLE_ME_INCLUDE_ME_CFG_H
#include "me_function.h"
#include "me_phase.h"

namespace maple {
class MirCFG {
 public:
  explicit MirCFG(MeFunction *f) : func(f), hasDoWhile(false) {}


  ~MirCFG() {}

  void BuildMirCFG();
  void FixMirCFG();
  void ConvertPhis2IdentityAssigns(BB *meBB);
  void UnreachCodeAnalysis(bool updatePhi = false);
  void WontExitAnalysis();
  void Verify();
  void VerifyLabels();
  void Dump();
  void DumpToFile(const char *prefix, bool dumpInStrs = false);
  void AddAuxilaryBB();
  bool FindExprUse(BaseNode *expr, StIdx stIdx);
  bool FindUse(StmtNode *stmt, StIdx stid);
  bool FindDef(StmtNode *stmt, StIdx stid);
  bool HasNoOccBetween(StmtNode *from, StmtNode *to, StIdx stIdx);

  MeFunction *GetFunc() {
    return func;
  }

  bool GetHasDoWhile() {
    return hasDoWhile;
  }

  void SetHasDoWhile(bool hdw) {
    hasDoWhile = hdw;
  }

 private:
  MeFunction *func;
  bool hasDoWhile;
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ME_CFG_H
