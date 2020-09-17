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
#include "bb.h"
#include "mempool_allocator.h"
#include "ver_symbol.h"
#include "me_ssa.h"
#include "me_ir.h"

namespace maple {
std::string BB::StrAttribute() const {
  switch (kind) {
    case kBBUnknown:
      return "unknown";
    case kBBCondGoto:
      return "condgoto";
    case kBBGoto:
      return "goto";
    case kBBFallthru:
      return "fallthru";
    case kBBReturn:
      return "return";
    case kBBAfterGosub:
      return "aftergosub";
    case kBBSwitch:
      return "switch";
    case kBBInvalid:
      return "invalid";
    default:
      CHECK_FATAL(false, "NYI");
  }
  return "NYI";
}

void BB::DumpBBAttribute(MIRModule *mod) {
  if (GetAttributes(kBBAttrIsEntry)) {
    mod->GetOut() << " Entry ";
  }
  if (GetAttributes(kBBAttrIsExit)) {
    mod->GetOut() << " Exit ";
  }
  if (GetAttributes(kBBAttrIsTry)) {
    mod->GetOut() << " Try ";
  }
  if (GetAttributes(kBBAttrIsTryEnd)) {
    mod->GetOut() << " Tryend ";
  }
  if (GetAttributes(kBBAttrIsJSCatch)) {
    mod->GetOut() << " JSCatch ";
  }
  if (GetAttributes(kBBAttrIsJSFinally)) {
    mod->GetOut() << " JSFinally ";
  }
  if (GetAttributes(kBBAttrIsJavaFinally)) {
    mod->GetOut() << " Catch::Finally ";
  } else if (GetAttributes(kBBAttrIsCatch)) {
    mod->GetOut() << " Catch ";
  }
  if (GetAttributes(kBBAttrIsInLoop)) {
    mod->GetOut() << " InLoop ";
  }
}

void BB::DumpHeader(MIRModule *mod) {
  mod->GetOut() << "============BB id:" << GetBBId().idx << " " << StrAttribute() << " [";
  DumpBBAttribute(mod);
  mod->GetOut() << "]===============\n";
  mod->GetOut() << "preds: ";
  for (auto it = pred.begin(); it != pred.end(); it++) {
    mod->GetOut() << (*it)->GetBBId().idx << " ";
  }
  mod->GetOut() << "\nsuccs: ";
  for (auto it = succ.begin(); it != succ.end(); it++) {
    mod->GetOut() << (*it)->GetBBId().idx << " ";
  }
  mod->GetOut() << "\n";
  if (bbLabel != 0) {
    static LabelNode lblNode;
    lblNode.SetLabelIdx(bbLabel);
    lblNode.Dump(mod, 0);
    mod->GetOut() << "\n";
  }
}

void BB::Dump(MIRModule *mod) {
  DumpHeader(mod);
  DumpPhi(mod);
  for (auto &stmt : stmtNodeList) {
    stmt.Dump(mod, 1);
  }
}

void BB::DumpPhi(const MIRModule *mod) {
  for (auto phiIt = phiList.begin(); phiIt != phiList.end(); phiIt++) {
    (*phiIt).second.Dump(mod);
  }
}

PhiNode *BB::PhiofVerStInserted(VersionSt *vsym) {
  auto phiit = phiList.find(vsym->GetOrigSt());
  return (phiit != phiList.end()) ? &(*phiit).second : nullptr;
}

void BB::InsertPhi(MapleAllocator *alloc, VersionSt *vsym) {
  PhiNode phiNode(alloc, vsym);
  for (auto prevIt = pred.begin(); prevIt != pred.end(); prevIt++) {
    phiNode.GetPhiOpns().push_back(vsym);
  }
  phiList.insert(std::make_pair(vsym->GetOrigSt(), phiNode));
}

bool BB::IsInList(MapleVector<BB*> &bblist) const {
  for (auto it = bblist.begin(); it != bblist.end(); it++) {
    if (*it == this) {
      return true;
    }
  }
  return false;
}

// remove the given bb from the BB vector bvec; nothing done if not found
int BB::RemoveBBFromVector(MapleVector<BB*> &bvec) {
  size_t i = 0;
  while (i < bvec.size()) {
    if (bvec[i] == this) {
      break;
    }
    i++;
  }
  if (i == bvec.size()) {
    // bb not in the vector
    return -1;
  }

  bvec.erase(bvec.cbegin() + i);
  return i;
}

void BB::RemoveBBFromPred(BB *bb) {
  int index = bb->RemoveBBFromVector(pred);
  ASSERT(index != -1, "-1 is a very large number in BB::RemoveBBFromPred");
  for (auto phiIt = phiList.begin(); phiIt != phiList.end(); phiIt++) {
    ASSERT((*phiIt).second.GetPhiOpns().size() > index, "index out of range in BB::RemoveBBFromPred");

    (*phiIt).second.GetPhiOpns().erase((*phiIt).second.GetPhiOpns().cbegin() + index);
  }
  for (auto phiIt = mevarPhiList.begin(); phiIt != mevarPhiList.end(); phiIt++) {
    ASSERT((*phiIt).second->GetOpnds().size() > index, "index out of range in BB::RemoveBBFromPred");

    (*phiIt).second->GetOpnds().erase((*phiIt).second->GetOpnds().cbegin() + index);
  }
  for (auto phiIt = meregPhiList.begin(); phiIt != meregPhiList.end(); phiIt++) {
    ASSERT((*phiIt).second->GetOpnds().size() > index, "index out of range in BB::RemoveBBFromPred");

    (*phiIt).second->GetOpnds().erase((*phiIt).second->GetOpnds().cbegin() + index);
  }
}

void BB::RemoveBBFromSucc(BB *bb) {
  bb->RemoveBBFromVector(succ);
}

/* add stmtnode to bb and update first_stmt_ and last_stmt_ */
void BB::AddStmtNode(StmtNode *stmt) {
  CHECK_FATAL(stmt != nullptr, "null ptr check");
  stmtNodeList.push_back(stmt);
}

/* add stmtnode at beginning of bb and update first_stmt_ and last_stmt_ */
void BB::PrependStmtNode(StmtNode *stmt) {
  stmtNodeList.push_front(stmt);
}

void BB::PrependMeStmt(MeStmt *meStmt) {
  meStmtList.push_front(meStmt);
  meStmt->SetBB(this);
}

// if the bb contains only one stmt other than comment, return that stmt
// otherwise return nullptr
StmtNode *BB::GetTheOnlyStmtNode() {
  StmtNode *onlyStmtNode = nullptr;
  for (auto &stmtNode : stmtNodeList) {
    if (stmtNode.GetOpCode() == OP_comment) {
      continue;
    }

    if (onlyStmtNode != nullptr) {
      return nullptr;
    }

    onlyStmtNode = &stmtNode;
  }

  return onlyStmtNode;
}

// warning: if stmt is not in the bb, this will cause undefined behavior
void BB::RemoveStmtNode(StmtNode *stmt) {
  CHECK_FATAL(stmt != nullptr, "null ptr check");
  stmtNodeList.erase(StmtNodes::iterator(stmt));
}

void BB::InsertStmtBefore(StmtNode *stmt, StmtNode *newStmt) {
  CHECK_FATAL(newStmt != nullptr, "null ptr check");
  CHECK_FATAL(stmt != nullptr, "null ptr check");
  stmtNodeList.insert(StmtNodes::iterator(stmt), newStmt);
}

void BB::ReplaceStmt(StmtNode *stmt, StmtNode *newStmt) {
  InsertStmtBefore(stmt, newStmt);
  RemoveStmtNode(stmt);
}

/* delete last_stmt_ and update */
void BB::RemoveLastStmt() {
  stmtNodeList.pop_back();
}

/* replace pred with newbb to keep position and
 * add this as succ of newpred */
void BB::ReplacePred(const BB *old, BB *newPred) {
  for (size_t i = 0; i < pred.size(); i++) {
    if (pred[i] == old) {
      pred[i] = newPred;
      newPred->succ.push_back(this);
      break;
    }
  }
  return;
}

/* replace succ in current position with newsucc
 * and add this as pred of newsucc */
void BB::ReplaceSucc(const BB *old, BB *newSucc) {
  for (size_t i = 0; i < succ.size(); i++) {
    if (succ[i] == old) {
      succ[i] = newSucc;
      newSucc->pred.push_back(this);
      break;
    }
  }
  return;
}

/* this is common_entry_bb, so newsucc's pred_ is left as is */
void BB::ReplaceSuccOfCommonEntryBB(const BB *old, BB *newSucc) {
  for (size_t i = 0; i < succ.size(); i++) {
    if (succ[i] == old) {
      succ[i] = newSucc;
      break;
    }
  }
  return;
}

void BB::FindReachableBBs(std::vector<bool> &visitedBBs) {
  CHECK_FATAL(GetBBId().idx < visitedBBs.size(), "out of range in BB::FindReachableBBs");
  if (visitedBBs[GetBBId().idx]) {
    return;
  }
  visitedBBs[GetBBId().idx] = true;
  for (auto it = succ.begin(); it != succ.end(); ++it) {
    (*it)->FindReachableBBs(visitedBBs);
  }
}

void BB::FindWillExitBBs(std::vector<bool> &visitedBBs) {
  CHECK_FATAL(GetBBId().idx < visitedBBs.size(), "out of range in BB::FindReachableBBs");
  if (visitedBBs[GetBBId().idx]) {
    return;
  }
  visitedBBs[GetBBId().idx] = true;
  for (auto it = pred.begin(); it != pred.end(); ++it) {
    (*it)->FindWillExitBBs(visitedBBs);
  }
}

void BB::SetFirstMe(MeStmt *stmt) {
  meStmtList.update_front(stmt);
}

void BB::SetLastMe(MeStmt *stmt) {
  meStmtList.update_back(stmt);
}

void BB::RemoveMeStmt(MeStmt *meStmt) {
  CHECK_FATAL(meStmt != nullptr, "null ptr check");
  meStmtList.erase(meStmt);
}

void BB::AddMeStmtFirst(MeStmt *meStmt) {
  CHECK_FATAL(meStmt != nullptr, "null ptr check");
  meStmtList.push_front(meStmt);
  meStmt->SetBB(this);
}

void BB::AddMeStmtLast(MeStmt *meStmt) {
  CHECK_FATAL(meStmt != nullptr, "null ptr check");
  meStmtList.push_back(meStmt);
  meStmt->SetBB(this);
}

void BB::InsertMeStmtBefore(MeStmt *meStmt, MeStmt *inStmt) {
  CHECK_FATAL(meStmt != nullptr, "null ptr check");
  CHECK_FATAL(inStmt != nullptr, "null ptr check");
  meStmtList.insert(meStmt, inStmt);
  inStmt->SetBB(this);
}

void BB::InsertMeStmtAfter(MeStmt *meStmt, MeStmt *inStmt) {
  meStmtList.insertAfter(meStmt, inStmt);
  inStmt->SetBB(this);
}

// insert instmt before br to the last of bb
void BB::InsertMeStmtLastBr(MeStmt *inStmt) {
  if (IsMeStmtEmpty()) {
    AddMeStmtLast(inStmt);
  } else {
    MeStmt *brStmt = meStmtList.rbegin().base().d();
    Opcode op = brStmt->GetOp();
    if (brStmt->IsCondBr() || op == OP_goto || op == OP_switch || op == OP_throw || op == OP_return || op == OP_gosub ||
        op == OP_retsub) {
      InsertMeStmtBefore(brStmt, inStmt);
    } else {
      AddMeStmtLast(inStmt);
    }
  }
}

void BB::ReplaceMeStmt(MeStmt *stmt, MeStmt *newStmt) {
  InsertMeStmtBefore(stmt, newStmt);
  RemoveMeStmt(stmt);
}

void BB::DumpMeVarPhiList(IRMap *irMap) {
  auto phiIt = mevarPhiList.begin();
  int count = 0;
  for (; phiIt != mevarPhiList.end(); phiIt++) {
    (*phiIt).second->Dump(irMap);
    int dumpVsyNum = DumpOptions::GetDumpVsyNum();
    if (dumpVsyNum > 0 && ++count >= dumpVsyNum) {
      break;
    }
    ASSERT(count >= 0, "mevarPhiList too large");
  }
}

void BB::DumpMeRegPhiList(IRMap *irMap) {
  auto phiIt = meregPhiList.begin();
  for (; phiIt != meregPhiList.end(); phiIt++) {
    (*phiIt).second->Dump(irMap);
  }
}

}  // namespace maple
