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
#include "me_irmap.h"
#include "dominance.h"
#include "mir_builder.h"

namespace maple {
void MeIRMap::DumpBB(BB *bb) {
  int i = 0;
  for (auto &mestmt : bb->GetMeStmts()) {
    if (GetDumpStmtNum()) {
      LogInfo::MapleLogger() << "(" << i++ << ") ";
    }
    mestmt.Dump(this);
  }
}

void MeIRMap::Dump() {
  // back up mempool and use a new mempool every time
  // we dump IRMap, restore the mempool afterwards
  MIRFunction *mirFunction = func->GetMirFunc();
  MemPool *backup = mirFunction->GetCodeMempool();
  mirFunction->SetMemPool(mempoolctrler.NewMemPool("IR Dump"));
  LogInfo::MapleLogger() << "===================Me IR dump==================\n";
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    auto *bb = *bIt;
    bb->DumpHeader(GetMIRModule());
    LogInfo::MapleLogger() << "frequency : " << bb->GetFrequency() << "\n";
    bb->DumpMeVarPhiList(this);
    bb->DumpMeRegPhiList(this);
    int i = 0;
    for (auto &mestmt : bb->GetMeStmts()) {
      if (GetDumpStmtNum()) {
        LogInfo::MapleLogger() << "(" << i++ << ") ";
      }
      mestmt.EmitStmt(GetSSATab())->Dump(GetMIRModule(), 0);
      mestmt.Dump(this);
    }
  }
  mempoolctrler.DeleteMemPool(mirFunction->GetCodeMempool());
  mirFunction->SetMemPool(backup);
}

// this function only emits statement
void MeIRMap::EmitBBStmts(BB *bb, BlockNode *curblk) {
  ASSERT(curblk != nullptr, "null ptr check");
  auto &meStmts = bb->GetMeStmts();
  for (auto &mestmt : meStmts) {
    if (!GetNeedAnotherPass()) {
      if (mestmt.GetOp() == OP_interfaceicall || mestmt.GetOp() == OP_virtualicall) {
        mestmt.SetOp(OP_icall);
      } else if (mestmt.GetOp() == OP_interfaceicallassigned || mestmt.GetOp() == OP_virtualicallassigned) {
        mestmt.SetOp(OP_icallassigned);
      }
    }
    StmtNode *stmt = mestmt.EmitStmt(GetSSATab());
    ASSERT(stmt != nullptr, "null ptr check");
    curblk->AddStatement(stmt);
  }
}

void MeIRMap::EmitBB(BB *bb, BlockNode *curblk) {
  ASSERT(curblk != nullptr, "null ptr check");
  // emit head. label
  LabelIdx labidx = bb->GetBBLabel();
  if (labidx != 0) {
    // not a empty bb
    LabelNode *lbnode = GetSSATab()->mirModule.CurFunction()->GetCodeMempool()->New<LabelNode>();
    lbnode->SetLabelIdx(labidx);
    curblk->AddStatement(lbnode);
  }
  EmitBBStmts(bb, curblk);
  if (bb->GetAttributes(kBBAttrIsTryEnd)) {
    /* generate op_endtry */
    StmtNode *endtry = GetSSATab()->mirModule.CurFunction()->GetCodeMempool()->New<StmtNode>(OP_endtry);
    curblk->AddStatement(endtry);
  }
}

AnalysisResult *MeDoIRMap::Run(MeFunction *func, MeFuncResultMgr *m, ModuleResultMgr *mrm) {
  Dominance *dom = static_cast<Dominance*>(m->GetAnalysisResult(MeFuncPhase_DOMINANCE, func));
  ASSERT(dom, "dominance phase has problem");
  MemPool *irMapMemPool = NewMemPool();
  MeIRMap *irmap = irMapMemPool->New<MeIRMap>(func, dom, irMapMemPool, NewMemPool());
  func->SetIRMap(irmap);
#if DEBUG
  g_irmap = irmap;
#endif
  std::vector<bool> bbIRMapProcessed(func->NumBBs(), false);
  irmap->BuildBB(func->GetCommonEntryBB(), bbIRMapProcessed);
  if (DEBUGFUNC(func)) {
    irmap->Dump();
  }
  irmap->GetTempAlloc().SetMemPool(nullptr);
  // delete input IR code for current function
  MIRFunction *mirFunc = func->GetMirFunc();
  mempoolctrler.DeleteMemPool(mirFunc->GetCodeMempool());
  mirFunc->SetCodeMemPool(nullptr);
  // delete versionst_table
#if MIR_FEATURE_FULL
  // nullify all references to the versionst_table contents
  for (size_t i = 0; i < func->GetMeSSATab()->GetVersionStTable().GetVersionStVectorSize(); i++) {
    func->GetMeSSATab()->GetVersionStTable().SetVersionStVectorItem(i, nullptr);
  }
  // clear BB's phi_list_ which uses versionst; nullify first_stmt_, last_stmt_
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    auto *bb = *bIt;
    bb->GetPhiList().clear();
    bb->SetFirst(nullptr);
    bb->SetLast(nullptr);
  }
#endif
  mempoolctrler.DeleteMemPool(func->GetMeSSATab()->GetVersionStTable().GetVSTAlloc().GetMemPool());
  return irmap;
}

}  // namespace maple
