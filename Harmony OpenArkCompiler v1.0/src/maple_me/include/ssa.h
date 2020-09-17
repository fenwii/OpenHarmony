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
#ifndef MAPLE_ME_INCLUDE_SSA_H
#define MAPLE_ME_INCLUDE_SSA_H
#include <iostream>
#include "mir_module.h"
#include "mir_nodes.h"

namespace maple {
class BB;
class VersionSt;
class OriginalStTable;
class VersionStTable;
class SSATab;
class PhiNode {
 public:
  PhiNode(MapleAllocator *alloc, VersionSt *vsym) : result(vsym), phiOpnds(2, nullptr, alloc->Adapter()) {
    phiOpnds.pop_back();
    phiOpnds.pop_back();
  };
  ~PhiNode() {}

  void Dump(const MIRModule *mod);

  VersionSt *GetResult() {
    return result;
  }

  void SetResult(VersionSt *resultPara) {
    result = resultPara;
  }

  MapleVector<VersionSt*> &GetPhiOpns() {
    return phiOpnds;
  }

  VersionSt *GetPhiOpnd(size_t index) {
    ASSERT(index < phiOpnds.size(), "out of range in PhiNode::GetPhiOpnd");
    return phiOpnds.at(index);
  }

  void SetPhiOpnd(size_t index, VersionSt *opnd) {
    CHECK_FATAL(index < phiOpnds.size(), "out of range in PhiNode::SetPhiOpnd");
    phiOpnds[index] = opnd;
  }

  void SetPhiOpns(MapleVector<VersionSt*> phiOpndsPara) {
    phiOpnds = phiOpndsPara;
  }

 private:
  VersionSt *result;
  MapleVector<VersionSt*> phiOpnds;
};

class SSA {
 public:
  SSA(MemPool *memPool, SSATab *stab)
      : ssaAlloc(memPool),
        vstStacks(ssaAlloc.Adapter()),
        vstVersions(ssaAlloc.Adapter()),
        bbRenamed(ssaAlloc.Adapter()),
        ssaTab(stab) {}

  virtual ~SSA() {}

  void InitRenameStack(OriginalStTable*, size_t, VersionStTable&);
  VersionSt *CreateNewVersion(VersionSt *vsym, BB *defBB);
  void RenamePhi(BB *bb);
  void RenameDefs(StmtNode *stmt, BB *defBB);
  void RenameMustDefs(const StmtNode *stmt, BB *defBB);
  void RenameExpr(BaseNode *expr);
  void RenameUses(StmtNode *stmt);
  void RenamePhiUseInSucc(BB *bb);
  void RenameMayUses(BaseNode *node);

  const MapleAllocator &GetSsaAlloc() const {
    return ssaAlloc;
  }

  MapleVector<MapleStack<VersionSt*>*> &GetVstStacks() {
    return vstStacks;
  }

  MapleStack<VersionSt*> *GetVstStack(size_t idx) {
    ASSERT(idx < vstStacks.size(), "out of range of vstStacks");
    return vstStacks.at(idx);
  }

  MapleVector<bool> &GetBBsRenamed() {
    return bbRenamed;
  }

  bool GetBBRenamed(size_t idx) {
    ASSERT(idx < bbRenamed.size(), "BBId out of range");
    return bbRenamed.at(idx);
  }

  void SetBBRenamed(size_t idx, bool isRenamed) {
    CHECK_FATAL(idx < bbRenamed.size(), "BBId out of range");
    bbRenamed[idx] = isRenamed;
  }

  SSATab *GetSSATab() {
    return ssaTab;
  }

 private:
  MapleAllocator ssaAlloc;
  MapleVector<MapleStack<VersionSt*>*> vstStacks;  // rename stack for variable versions
  MapleVector<int32> vstVersions;                    //  maxium version for variables
  MapleVector<bool> bbRenamed;                       //   indicate bb is renamed or not
  SSATab *ssaTab;
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_SSA_H
