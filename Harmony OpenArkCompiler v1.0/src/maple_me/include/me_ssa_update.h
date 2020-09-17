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
#ifndef MAPLE_ME_INCLUDE_ME_SSA_UPDATE_H
#define MAPLE_ME_INCLUDE_ME_SSA_UPDATE_H
#include "me_function.h"
#include "me_dominance.h"
#include "me_irmap.h"

namespace maple {
class SSAUpdate {
 public:
  SSAUpdate &operator=(const SSAUpdate &p) = default;
  SSAUpdate(const SSAUpdate &p) = default;
  SSAUpdate(MeFunction *f, SSATab *stab, Dominance *d, MapleMap<OStIdx, MapleSet<BBId>*> *cands, MemPool *mp)
      : func(f),
        irMap(f->GetIRMap()),
        ssaTab(stab),
        dom(d),
        ssaUpdateMp(mp),
        ssaUpdateAlloc(ssaUpdateMp),
        updateCands(cands),
        renameStacks(std::less<OStIdx>(), ssaUpdateAlloc.Adapter()) {}

  ~SSAUpdate() {
    mempoolctrler.DeleteMemPool(ssaUpdateMp);
  }

  void Run();

 private:
  MeFunction *func;
  IRMap *irMap;
  SSATab *ssaTab;
  Dominance *dom;
  MemPool *ssaUpdateMp;
  MapleAllocator ssaUpdateAlloc;
  MapleMap<OStIdx, MapleSet<BBId>*> *updateCands;
  MapleMap<OStIdx, MapleStack<VarMeExpr*>*> renameStacks;
  void GetIterDomFrontier(const BB *bb, MapleSet<BBId> *dfset, std::vector<bool> &visitedMap);
  void InsertPhis();
  void RenamePhi(BB *bb);
  MeExpr *RenameExpr(MeExpr *meexpr, bool &changed);
  void RenameStmts(BB *bb);
  void RenamePhiOpndsInSucc(BB *bb);
  void RenameBB(BB *bb);
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ME_SSA_UPDATE_H
