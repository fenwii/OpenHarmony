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
#ifndef MAPLE_ME_INCLUDE_SSA_TAB_H
#define MAPLE_ME_INCLUDE_SSA_TAB_H
#include "mempool.h"
#include "mempool_allocator.h"
#include "phase.h"
#include "ver_symbol.h"
#include "ssa_mir_nodes.h"

namespace maple {
class VersionStTable;
class SSATab : public AnalysisResult {
  // represent the SSA table
 public:
  MIRModule &mirModule;
  SSATab(MemPool *memPool, MemPool *versmp, MIRModule *mod)
      : AnalysisResult(memPool),
        mirModule(*mod),
        versionStTable(versmp),
        originalStTable(memPool, mod),
        stmtsSSAPart(versmp),
        wholeProgramScope(false) {}

  ~SSATab() {}

  BaseNode *CreateSSAExpr(BaseNode *expr);
  void CreateSSAStmt(StmtNode *stmt, const BB *curbb, bool ignoreCallassignedDefs = false);
  VersionSt *GetVerSt(size_t verIdx) {
    return versionStTable.GetVersionStFromID(verIdx);
  }

  // following are handles to methods in originalStTable
  OriginalSt *CreateSymbolOriginalSt(MIRSymbol *mirSt, PUIdx puIdx, FieldID fld) {
    return originalStTable.CreateSymbolOriginalSt(mirSt, puIdx, fld);
  }

  OriginalSt *FindOrCreateSymbolOriginalSt(MIRSymbol *mirSt, PUIdx puIdx, FieldID fld) {
    return originalStTable.FindOrCreateSymbolOriginalSt(mirSt, puIdx, fld);
  }

  OriginalSt *GetOriginalStFromID(OStIdx id) {
    return originalStTable.GetOriginalStFromID(id);
  }

  OriginalSt *GetSymbolOriginalStFromID(OStIdx id) {
    OriginalSt *ost = originalStTable.GetOriginalStFromID(id);
    ASSERT(ost->IsSymbolOst(), "GetSymbolOriginalStFromid: id has wrong ost type");
    return ost;
  }

  MIRSymbol *GetMIRSymbolFromOriginalSt(const OriginalSt *ost) {
    return originalStTable.GetMIRSymbolFromOriginalSt(ost);
  }

  MIRSymbol *GetMIRSymbolFromID(OStIdx id) {
    return originalStTable.GetMIRSymbolFromID(id);
  }

  VersionStTable &GetVersionStTable() {
    return versionStTable;
  }

  size_t GetVersionStTableSize() {
    return versionStTable.GetVersionStVectorSize();
  }

  OriginalStTable &GetOriginalStTable() {
    return originalStTable;
  }

  size_t GetOriginalStTableSize() {
    return originalStTable.Size();
  }

  StmtsSSAPart &GetStmtsSSAPart() {
    return stmtsSSAPart;
  }

  bool IsWholeProgramScope() {
    return wholeProgramScope;
  }

  void SetWholeProgramScope(bool val) {
    wholeProgramScope = val;
  }

 private:
  VersionStTable versionStTable;  // this uses special versmp because it will be freed earlier
  OriginalStTable originalStTable;
  StmtsSSAPart stmtsSSAPart;  // this uses special versmp because it will be freed earlier
  bool wholeProgramScope;
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_SSA_TAB_H
