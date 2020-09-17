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
#include "me_ssa.h"
#include <iostream>
#include "bb.h"
#include "me_option.h"
#include "ssa_mir_nodes.h"
#include "ver_symbol.h"
#include "dominance.h"
#include "me_function.h"

/*
   This phase builds the SSA form of a function. Before this we have got the dominator tree
   and each bb's dominance frontiers. Then the algorithm follows this outline:

   Step 1: Inserting phi-node.
   With dominance frontiers, we can determine more
   precisely where phi-node might be needed. The basic idea is simple.
   A definition of x in block b forces a phi-node at every node in b's
   dominance frontiers. Since that phi-node is a new definition of x,
   it may, in turn, force the insertion of additional phi-node.

   Step 2: Renaming.
   Renames both definitions and uses of each symbol in
   a preorder walk over the dominator tree. In each block, we first
   rename the values defined by phi-node at the head of the block, then
   visit each stmt in the block: we rewrite each uses of a symbol with current
   SSA names(top of the stack which holds the current SSA version of the corresponding symbol),
   then it creates a new SSA name for the result of the stmt.
   This latter act makes the new name current. After all the stmts in the
   block have been rewritten, we rewrite the appropriate phi-node's
   parameters in each cfg successor of the block, using the current SSA names.
   Finally, it recurs on any children of the block in the dominator tree. When it
   returns from those recursive calls, we restores the stack of current SSA names to
   the state that existed before the current block was visited.
 */

namespace maple {
void MeSSA::BuildSSA() {
  InsertPhiNode();
  InitRenameStack(&func->GetMeSSATab()->GetOriginalStTable(), func->GetAllBBs().size(),
                  func->GetMeSSATab()->GetVersionStTable());
  // recurse down dominator tree in pre-order traversal
  const MapleSet<BBId> &children = dom->GetDomChildren(func->GetCommonEntryBB()->GetBBId().idx);
  for (const BBId &child : children) {
    RenameBB(func->GetBBFromID(child));
  }
}

void MeSSA::CollectDefBBs(std::map<OStIdx, std::set<BBId>> &ostDefBBs) {
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    auto *bb = *bIt;
    for (auto &stmt : bb->GetStmtNodes()) {
      if (HasMayDefPart(&stmt)) {
        MapleMap<OStIdx, MayDefNode> *mayDefs = SSAGenericGetMayDefNodes(&stmt, &GetSSATab()->GetStmtsSSAPart());
        MapleMap<OStIdx, MayDefNode>::iterator iter;
        for (iter = mayDefs->begin(); iter != mayDefs->end(); ++iter) {
          OriginalSt *ost = func->GetMeSSATab()->GetOriginalStFromID(iter->first);
          if (ost && (!ost->IsFinal() || func->GetMirFunc()->IsConstructor())) {
            ostDefBBs[iter->first].insert(bb->GetBBId());
          } else if (stmt.GetOpCode() == OP_intrinsiccallwithtype) {
            IntrinsiccallNode &innode = static_cast<IntrinsiccallNode&>(stmt);
            if (innode.GetIntrinsic() == INTRN_JAVA_CLINIT_CHECK) {
              ostDefBBs[iter->first].insert(bb->GetBBId());
            }
          }
        }
        if (stmt.GetOpCode() == OP_dassign || stmt.GetOpCode() == OP_maydassign) {
          VersionSt *vst = GetSSATab()->GetStmtsSSAPart().SSAPartOf(&stmt)->GetSSAVar();
          OriginalSt *ost = vst->GetOrigSt();
          if (ost && (!ost->IsFinal() || func->GetMirFunc()->IsConstructor())) {
            ostDefBBs[vst->GetOrigIdx()].insert(bb->GetBBId());
          }
        }
      }
      if (kOpcodeInfo.IsCallAssigned(stmt.GetOpCode())) {  // Needs to handle mustDef in callassigned stmt
        MapleVector<MustDefNode> *mustDefs = SSAGenericGetMustDefNode(&stmt, &GetSSATab()->GetStmtsSSAPart());
        MapleVector<MustDefNode>::iterator iter;
        for (iter = mustDefs->begin(); iter != mustDefs->end(); ++iter) {
          OriginalSt *ost = iter->GetResult()->GetOrigSt();
          if (ost && (!ost->IsFinal() || func->GetMirFunc()->IsConstructor())) {
            ostDefBBs[ost->GetIndex()].insert(bb->GetBBId());
          }
        }
      }
    }
  }
}

void MeSSA::InsertPhiNode() {
  std::map<OStIdx, std::set<BBId>> ost2DefBBs;
  CollectDefBBs(ost2DefBBs);
  OriginalStTable *otable = &func->GetMeSSATab()->GetOriginalStTable();
  for (size_t i = 1; i < otable->Size(); i++) {
    OriginalSt *ost = otable->GetOriginalStFromID(OStIdx(i));
    VersionSt *vst = func->GetMeSSATab()->GetVersionStTable().GetVersionStFromID(ost->GetZeroVersionIndex(), true);
    ASSERT(vst != nullptr, "null ptr check");
    if (ost2DefBBs[ost->GetIndex()].empty()) {
      continue;
    }
    // volatile variables will not have ssa form.
    if (ost->IsVolatile()) {
      continue;
    }
    std::deque<BB*> *workList = new std::deque<BB*>();
    for (auto it = ost2DefBBs[ost->GetIndex()].begin(); it != ost2DefBBs[ost->GetIndex()].end();
         it++) {
      BB *defBb = func->GetAllBBs()[(*it).idx];
      if (defBb != nullptr) {
        workList->push_back(defBb);
      }
    }
    while (!workList->empty()) {
      BB *defBB = workList->front();
      workList->pop_front();
      MapleSet<BBId> &dfs = dom->GetDomFrontier(defBB->GetBBId().idx);
      for (auto &bbID : dfs) {
        BB *dfBB = func->GetBBFromID(bbID);
        if (!dfBB->PhiofVerStInserted(vst)) {
          workList->push_back(dfBB);
          dfBB->InsertPhi(&func->GetAlloc(), vst);
          if (DEBUGFUNC(func)) {
            ost->Dump();
            LogInfo::MapleLogger() << " Defined In: BB" << defBB->GetBBId().idx << " Insert Phi Here: BB"
                                   << dfBB->GetBBId().idx << std::endl;
          }
        }
      }
    }
    delete workList;
  }
}

MeSSA::MeSSA(MeFunction *func, Dominance *dom, MemPool *memPool)
    : SSA(memPool, func->GetMeSSATab()), AnalysisResult(memPool), func(func), dom(dom) {}

void MeSSA::RenameBB(BB *bb) {
  if (GetBBRenamed(bb->GetBBId().idx)) {
    return;
  }

  SetBBRenamed(bb->GetBBId().idx, true);

  // record stack size for variable versions before processing rename. It is used for stack pop up.
  std::vector<uint32> oriStackSize;
  oriStackSize.resize(GetVstStacks().size());
  for (size_t i = 1; i < GetVstStacks().size(); i++) {
    oriStackSize[i] = GetVstStack(i)->size();
  }
  RenamePhi(bb);
  for (auto &stmt : bb->GetStmtNodes()) {
    RenameUses(&stmt);
    RenameDefs(&stmt, bb);
    RenameMustDefs(&stmt, bb);
  }
  RenamePhiUseInSucc(bb);
  // Rename child in Dominator Tree.
  ASSERT(bb->GetBBId().idx < dom->GetDomChildrenSize(), "index out of range in MeSSA::RenameBB");
  const MapleSet<BBId> &children = dom->GetDomChildren(bb->GetBBId().idx);
  for (const BBId &child : children) {
    RenameBB(func->GetBBFromID(child));
  }
  for (size_t i = 1; i < GetVstStacks().size(); i++) {
    while (GetVstStack(i)->size() > oriStackSize[i]) {
      GetVstStack(i)->pop();
    }
  }
}

bool MeSSA::VerifySSAOpnd(BaseNode *node) {
  Opcode op = node->GetOpCode();
  size_t vtableSize = func->GetMeSSATab()->GetVersionStTable().GetVersionStVectorSize();
  if (op == OP_dread || op == OP_addrof) {
    AddrofSSANode *addrofSSANode = static_cast<AddrofSSANode*>(node);
    VersionSt *verSt = addrofSSANode->GetSSAVar();
    CHECK_FATAL(verSt->GetIndex() < vtableSize, "runtime check error");
    return true;
  } else if (op == OP_regread) {
    RegreadSSANode *regNode = static_cast<RegreadSSANode*>(node);
    VersionSt *verSt = regNode->GetSSAVar();
    CHECK_FATAL(verSt->GetIndex() < vtableSize, "runtime check error");
    return true;
  }
  for (size_t i = 0; i < node->NumOpnds(); i++) {
    VerifySSAOpnd(node->Opnd(i));
  }
  return true;
}

bool MeSSA::VerifySSA() {
  VersionStTable *versionStTable = &func->GetMeSSATab()->GetVersionStTable();
  if (!versionStTable->Verify()) {
    return false;
  }
  size_t vtableSize = func->GetMeSSATab()->GetVersionStTable().GetVersionStVectorSize();
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    auto *bb = *bIt;
    Opcode opcode;
    for (auto &stmt : bb->GetStmtNodes()) {
      opcode = stmt.GetOpCode();
      if (opcode == OP_dassign || opcode == OP_regassign) {
        VersionSt *verSt = func->GetMeSSATab()->GetStmtsSSAPart().SSAPartOf(&stmt)->GetSSAVar();
        CHECK_FATAL(verSt->GetIndex() < vtableSize, "runtime check error");
      }
      for (size_t i = 0; i < stmt.NumOpnds(); i++) {
        CHECK_FATAL(VerifySSAOpnd(stmt.Opnd(i)), "runtime check error");
      }
    }
  }
  return true;
}

AnalysisResult *MeDoSSA::Run(MeFunction *func, MeFuncResultMgr *m, ModuleResultMgr *mrm) {
  Dominance *dom = static_cast<Dominance*>(m->GetAnalysisResult(MeFuncPhase_DOMINANCE, func));
  CHECK_FATAL(dom != nullptr, "dominance phase has problem");
  SSATab *ssatab = static_cast<SSATab*>(m->GetAnalysisResult(MeFuncPhase_SSATAB, func));
  CHECK_FATAL(ssatab != nullptr, "ssaTab phase has problem");
  MemPool *ssamp = NewMemPool();
  MeSSA *ssa = ssamp->New<MeSSA>(func, dom, ssamp);
  ssa->BuildSSA();
  ssa->VerifySSA();
  if (DEBUGFUNC(func)) {
    ssatab->GetVersionStTable().Dump(&ssatab->mirModule);
  }
  return ssa;
}

}  // namespace maple
