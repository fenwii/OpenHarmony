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
#ifndef MAPLE_ME_INCLUDE_ALIAS_ANALYSIS_TABLE_H
#define MAPLE_ME_INCLUDE_ALIAS_ANALYSIS_TABLE_H
#include "orig_symbol.h"
#include "ssa_tab.h"

namespace maple {
class AliasAnalysisTable {
 public:
  AliasAnalysisTable(SSATab *ssaTable, MapleAllocator allocator, MIRModule *module)
      : ssaTab(ssaTable),
        alloc(allocator),
        mirModule(module),
        prevLevelNode(alloc.Adapter()),
        nextLevelNodes(alloc.Adapter()),
        memPool(ssaTab->GetMempool()) {}

  OriginalSt *GetPrevLevelNode(const OriginalSt *ost);
  MapleVector<OriginalSt*> *GetNextLevelNodes(const OriginalSt *ost);
  OriginalSt *FindOrCreateAddrofSymbolOriginalSt(const OriginalSt *ost);
  OriginalSt *FindOrCreateExtraLevSymOrRegOriginalSt(OriginalSt *ost, TyIdx ptyidx, FieldID fld);
  OriginalSt *FindOrCreateExtraLevOriginalSt(OriginalSt *ost, TyIdx ptyidx, FieldID fld);
  OriginalSt *FindExtraLevOriginalSt(const MapleVector<OriginalSt*> &nextLevelOsts, FieldID fld);
  OriginalSt *FindOrCreateDiffFieldOriginalSt(const OriginalSt *ost, FieldID fld);
  OriginalSt *FindDiffFieldOriginalSt(const OriginalSt *ost, FieldID fld);
  ~AliasAnalysisTable() = default;

 private:
  SSATab *ssaTab;
  MapleAllocator alloc;
  MIRModule *mirModule;
  MapleMap<OStIdx, OriginalSt*> prevLevelNode;                 // index is the OStIdx
  MapleMap<OStIdx, MapleVector<OriginalSt*>*> nextLevelNodes;  // index is the OStIdx
  MemPool *memPool;
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ALIAS_ANALYSIS_TABLE_H
