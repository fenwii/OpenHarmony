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
#include "me_cfg.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include "bb.h"
#include "ssa_mir_nodes.h"
#include "me_irmap.h"
#include "mir_builder.h"

namespace maple {

void MirCFG::BuildMirCFG() {
  MapleVector<BB*> entryBlocks(func->GetAlloc().Adapter());
  MapleVector<BB*> exitBlocks(func->GetAlloc().Adapter());
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    if (bIt == func->common_entry() || bIt == func->common_exit()) {
      continue;
    }
    BB *bb = *bIt;
    CHECK_FATAL(bb != nullptr, "null ptr check ");

    if (bb->GetAttributes(kBBAttrIsEntry)) {
      entryBlocks.push_back(bb);
    }
    if (bb->GetAttributes(kBBAttrIsExit)) {
      exitBlocks.push_back(bb);
    }
    switch (bb->GetKind()) {
      case kBBGoto: {
        StmtNode &lastStmt = bb->GetStmtNodes().back();
        if (lastStmt.GetOpCode() == OP_throw) {
          break;
        }
        ASSERT(lastStmt.GetOpCode() == OP_goto, "runtime check error");
        GotoNode &gotoStmt = static_cast<GotoNode&>(lastStmt);
        LabelIdx lblIdx = (LabelIdx)gotoStmt.GetOffset();
        BB *meBB = func->GetLabelBBIdMap()[lblIdx];
        bb->GetSucc().push_back(meBB);
        meBB->GetPred().push_back(bb);
        break;
      }
      case kBBCondGoto: {
        StmtNode &lastStmt = bb->GetStmtNodes().back();
        ASSERT(lastStmt.IsCondBr(), "runtime check error");
        /* succ[0] is fallthru, succ[1] is gotoBB */
        auto rightNextBB = bIt;
        ++rightNextBB;
        CHECK_FATAL(rightNextBB != eIt, "null ptr check ");
        (*rightNextBB)->GetPred().push_back(bb);
        bb->GetSucc().push_back(*rightNextBB);
        /* link goto */
        CondGotoNode &gotoStmt = static_cast<CondGotoNode&>(lastStmt);
        LabelIdx lblIdx = (LabelIdx)gotoStmt.GetOffset();
        BB *meBB = func->GetLabelBBIdMap()[lblIdx];
        bb->GetSucc().push_back(meBB);
        meBB->GetPred().push_back(bb);
        break;
      }
      case kBBSwitch: {
        StmtNode &lastStmt = bb->GetStmtNodes().back();
        ASSERT(lastStmt.GetOpCode() == OP_switch, "runtime check error");
        SwitchNode &switchStmt = static_cast<SwitchNode&>(lastStmt);
        LabelIdx lblIdx = switchStmt.GetDefaultLabel();
        BB *mirBB = func->GetLabelBBIdMap()[lblIdx];
        bb->GetSucc().push_back(mirBB);
        mirBB->GetPred().push_back(bb);
        for (size_t j = 0; j < switchStmt.GetSwitchTable().size(); j++) {
          lblIdx = switchStmt.GetCasePair(j).second;
          BB *meBB = func->GetLabelBBIdMap()[lblIdx];
          // Avoid duplicate succs.
          auto it = std::find(bb->GetSucc().begin(), bb->GetSucc().end(), meBB);
          if (it == bb->GetSucc().end()) {
            bb->GetSucc().push_back(meBB);
            meBB->GetPred().push_back(bb);
          }
        }
        break;
      }
      case kBBReturn:
        break;
      default: {
        // fall through?
        auto rightNextBB = bIt;
        ++rightNextBB;
        if (rightNextBB != eIt) {
          (*rightNextBB)->GetPred().push_back(bb);
          bb->GetSucc().push_back(*rightNextBB);
        }
        break;
      }
    }
    /* deal try blocks, add catch handler to try's succ */
    if (bb->GetAttributes(kBBAttrIsTry)) {
      ASSERT((func->GetBBTryNodeMap().find(bb) != func->GetBBTryNodeMap().end()), "try bb without try");
      StmtNode *currTry = func->GetBBTryNodeMap()[bb];
      TryNode *tryNode = static_cast<TryNode*>(currTry);
      bool hasFinallyHandler = false;
      /* add exception handler bb */
      for (size_t j = 0; j < tryNode->GetOffsetsCount(); j++) {
        LabelIdx labelIdx = tryNode->GetOffset(j);
        ASSERT(func->GetLabelBBIdMap().find(labelIdx) != func->GetLabelBBIdMap().end(), "runtime check error");
        BB *meBB = func->GetLabelBBIdMap()[labelIdx];
        ASSERT(meBB != nullptr, "null ptr check");
        ASSERT(meBB->GetAttributes(kBBAttrIsCatch), "runtime check error");
        size_t si = 0;
        if (meBB->GetAttributes(kBBAttrIsJSFinally) || meBB->GetAttributes(kBBAttrIsCatch)) {
          hasFinallyHandler = true;
        }
        /* avoid redundant succ */
        for (; si < bb->GetSucc().size(); si++) {
          if (meBB == bb->GetSucc(si)) {
            break;
          }
        }
        if (si == bb->GetSucc().size()) {
          bb->GetSucc().push_back(meBB);
          meBB->GetPred().push_back(bb);
        }
      }
      /* if try block don't have finally catch handler, add common_exit_bb as its succ */
      if (hasFinallyHandler == false) {
        if (!bb->GetAttributes(kBBAttrIsExit)) {
          bb->SetAttributes(kBBAttrIsExit);  // may exit
          exitBlocks.push_back(bb);
        }
      } else if ((func->GetMIRModule().GetSrcLang() == kSrcLangJava) && bb->GetAttributes(kBBAttrIsExit)) {
        // deal with throw bb, if throw bb in a tryblock and has finallyhandler
        auto &stmtNodes = bb->GetStmtNodes();
        if (!stmtNodes.empty() && stmtNodes.back().GetOpCode() == OP_throw) {
          bb->ClearAttributes(kBBAttrIsExit);
          ASSERT(bb == exitBlocks.back(), "runtime check error");
          exitBlocks.pop_back();
        }
      }
    }
  }
  // merge all blocks in entryBlocks
  for (auto it = entryBlocks.begin(); it != entryBlocks.end(); ++it) {
    func->GetCommonEntryBB()->GetSucc().push_back(*it);
  }
  // merge all blocks in exitBlocks
  for (auto it = exitBlocks.begin(); it != exitBlocks.end(); ++it) {
    func->GetCommonExitBB()->GetPred().push_back(*it);
  }
}

bool MirCFG::FindExprUse(BaseNode *expr, StIdx stIdx) {
  if (expr->GetOpCode() == OP_addrof || expr->GetOpCode() == OP_dread) {
    AddrofNode *addofNode = static_cast<AddrofNode*>(expr);
    return addofNode->GetStIdx() == stIdx;
  } else if (expr->GetOpCode() == OP_iread) {
    return FindExprUse(expr->Opnd(0), stIdx);
  } else {
    for (size_t i = 0; i < expr->NumOpnds(); i++) {
      if (FindExprUse(expr->Opnd(i), stIdx)) {
        return true;
      }
    }
  }
  return false;
}

bool MirCFG::FindUse(StmtNode *stmt, StIdx stID) {
  Opcode opcode = stmt->GetOpCode();
  switch (opcode) {
    case OP_call:
    case OP_virtualcall:
    case OP_virtualicall:
    case OP_superclasscall:
    case OP_interfacecall:
    case OP_interfaceicall:
    case OP_customcall:
    case OP_polymorphiccall:
    case OP_icall:
    case OP_intrinsiccall:
    case OP_xintrinsiccall:
    case OP_intrinsiccallwithtype:
    case OP_callassigned:
    case OP_virtualcallassigned:
    case OP_virtualicallassigned:
    case OP_superclasscallassigned:
    case OP_interfacecallassigned:
    case OP_interfaceicallassigned:
    case OP_customcallassigned:
    case OP_polymorphiccallassigned:
    case OP_icallassigned:
    case OP_intrinsiccallassigned:
    case OP_xintrinsiccallassigned:
    case OP_intrinsiccallwithtypeassigned:
    case OP_syncenter:
    case OP_syncexit: {
      for (size_t i = 0; i < stmt->NumOpnds(); i++) {
        BaseNode *argExpr = stmt->Opnd(i);
        if (FindExprUse(argExpr, stID)) {
          return true;
        }
      }
      break;
    }
    case OP_dassign: {
      DassignNode *dNode = static_cast<DassignNode*>(stmt);
      return FindExprUse(dNode->GetRHS(), stID);
    }
    case OP_regassign: {
      RegassignNode *rNode = static_cast<RegassignNode*>(stmt);
      if (rNode->GetRegIdx() < 0) {
        return false;
      }
      return FindExprUse(rNode->Opnd(0), stID);
    }
    case OP_iassign: {
      IassignNode *iNode = static_cast<IassignNode*>(stmt);
      if (FindExprUse(iNode->Opnd(0), stID)) {
        return true;
      } else {
        return FindExprUse(iNode->GetRHS(), stID);
      }
    }
    case OP_assertnonnull:
    case OP_eval:
    case OP_free:
    case OP_switch: {
      BaseNode *argExpr = stmt->Opnd(0);
      return FindExprUse(argExpr, stID);
    }
    default:
      break;
  }
  return false;
}

bool MirCFG::FindDef(StmtNode *stmt, StIdx stid) {
  if (stmt->GetOpCode() != OP_dassign && !kOpcodeInfo.IsCallAssigned(stmt->GetOpCode())) {
    return false;
  }
  if (stmt->GetOpCode() == OP_dassign) {
    DassignNode *dassStmt = static_cast<DassignNode *>(stmt);
    return dassStmt->GetStIdx() == stid;
  } else {
    CallNode *cnode = static_cast<CallNode *>(stmt);
    CallReturnVector &nrets = cnode->GetReturnVec();
    if (nrets.size() != 0) {
      ASSERT(nrets.size() == 1, "Single Ret value for now.");
      StIdx stidx = nrets[0].first;
      RegFieldPair regfieldpair = nrets[0].second;
      if (!regfieldpair.IsReg()) {
        return stidx == stid;
      }
    }
  }
  return false;
}

// Return true if there is no use or def of sym betweent from to to.
bool MirCFG::HasNoOccBetween(StmtNode *from, StmtNode *to, StIdx stIdx) {
  for (StmtNode *stmt = from; stmt && stmt != to; stmt = stmt->GetNext()) {
    if (FindUse(stmt, stIdx) || FindDef(stmt, stIdx)) {
      return false;
    }
  }
  return true;
}

// Fix the initially created CFG
void MirCFG::FixMirCFG() {
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    if (bIt == func->common_entry() || bIt == func->common_exit()) {
      continue;
    }
    auto *bb = *bIt;
    // Split bb in try if there are use -- def the same ref var.
    if (bb->GetAttributes(kBBAttrIsTry)) {
      // 1. Split callassigned/dassign stmt to two insns if it redefine a symbole and also use
      //    the same symbol as its operand.
      for (StmtNode *stmt = to_ptr(bb->GetStmtNodes().begin()); stmt != nullptr; stmt = stmt->GetNext()) {
        MIRSymbol *sym = nullptr;
        if (kOpcodeInfo.IsCallAssigned(stmt->GetOpCode())) {
          CallNode *cnode = static_cast<CallNode *>(stmt);
          CallReturnVector &nrets = cnode->GetReturnVec();
          if (nrets.size() != 0) {
            ASSERT(nrets.size() == 1, "Single Ret value for now.");
            StIdx stidx = nrets[0].first;
            RegFieldPair regfieldpair = nrets[0].second;
            if (!regfieldpair.IsReg()) {
              sym = func->GetMirFunc()->GetLocalOrGlobalSymbol(stidx);
            }
          }
        } else if (stmt->GetOpCode() == OP_dassign) {
          DassignNode *dassStmt = static_cast<DassignNode*>(stmt);
          // exclude the case a = b;
          if (dassStmt->GetRHS()->GetOpCode() == OP_dread) {
            continue;
          }
          sym = func->GetMirFunc()->GetLocalOrGlobalSymbol(dassStmt->GetStIdx());
        }
        if (sym == nullptr || sym->GetType()->GetPrimType() != PTY_ref || !sym->IsLocal()) {
           continue;
        }
        if (FindUse(stmt, sym->GetStIdx())) {
          func->GetMirFunc()->IncTempCount();
          std::string tempStr = std::string("tempRet").append(std::to_string(func->GetMirFunc()->GetTempCount()));
          MIRBuilder *builder = func->GetMirFunc()->GetModule()->GetMIRBuilder();
          MIRSymbol *targetSt = builder->GetOrCreateLocalDecl(tempStr.c_str(), sym->GetType());
          targetSt->ResetIsDeleted();
          if (stmt->GetOpCode() == OP_dassign) {
            BaseNode *rhs = static_cast<DassignNode*>(stmt)->GetRHS();
            StmtNode *dassign = builder->CreateStmtDassign(targetSt, 0, rhs);
            bb->ReplaceStmt(stmt, dassign);
            stmt = dassign;
          } else {
            CallNode *cnode = static_cast<CallNode *>(stmt);
            CallReturnPair retPair = cnode->GetReturnPair(0);
            retPair.first = targetSt->GetStIdx();
            cnode->SetReturnPair(retPair, 0);
          }
          StmtNode *dassign = builder->CreateStmtDassign(sym, 0, builder->CreateExprDread(targetSt));
          if (stmt->GetNext() != nullptr) {
            bb->InsertStmtBefore(stmt->GetNext(), dassign);
          } else {
            ASSERT( stmt == &(bb->GetStmtNodes().back()), "just check");
            stmt->SetNext(dassign);
            dassign->SetPrev(stmt);
            bb->GetStmtNodes().update_back(dassign);
          }
        }
      }
    }
  }

  // 2. Split bb to two bbs if there are use and def the same ref var in bb.
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    if (bIt == func->common_entry() || bIt == func->common_exit()) {
      continue;
    }
    auto *bb = *bIt;
    if (bb && bb->GetAttributes(kBBAttrIsTry)) {
      for (auto &splitPoint : bb->GetStmtNodes()) {
        StmtNode *nextStmt = splitPoint.GetNext();
        if (nextStmt != nullptr &&
            (nextStmt->GetOpCode() == OP_dassign || kOpcodeInfo.IsCallAssigned(nextStmt->GetOpCode()))) {
          MIRSymbol *sym = nullptr;
          if (nextStmt->GetOpCode() == OP_dassign) {
            DassignNode *dassignStmt = static_cast<DassignNode*>(nextStmt);
            const StIdx stIdx = dassignStmt->GetStIdx();
            sym = func->GetMirFunc()->GetLocalOrGlobalSymbol(stIdx);
          } else {
            CallNode *cNode = static_cast<CallNode*>(nextStmt);
            CallReturnVector &nrets = cNode->GetReturnVec();
            if (!nrets.empty()) {
              ASSERT(nrets.size() == 1, "Single Ret value for now.");
              StIdx stIdx = nrets[0].first;
              RegFieldPair regFieldPair = nrets[0].second;
              if (!regFieldPair.IsReg()) {
                sym = func->GetMirFunc()->GetLocalOrGlobalSymbol(stIdx);
              }
            }
          }
          if (sym == nullptr || sym->GetType()->GetPrimType() != PTY_ref || !sym->IsLocal()) {
            continue;
          }
          if (HasNoOccBetween(bb->GetStmtNodes().begin().d(), nextStmt, sym->GetStIdx())) {
            continue;
          }
          BB *newBB = func->SplitBB(bb, &splitPoint);
          // because SplitBB will insert a bb, we need update bIt & eIt
          auto newBBIt = std::find(func->cbegin(), func->cend(), bb);
          bIt = build_filter_iterator(
              newBBIt, std::bind(FilterNullPtr<MapleVector<BB*>::const_iterator>, std::placeholders::_1, func->end()));
          eIt = func->valid_end();
          for (size_t si = 0; si < newBB->GetSucc().size(); si++) {
            BB *sucBB = newBB->GetSucc(si);
            if (sucBB->GetAttributes(kBBAttrIsCatch)) {
              bb->AddSuccBB(sucBB);
            }
          }
          break;
        }
      }
    }
    // removing outgoing exception edge from normal return bb
    if (bb->GetKind() != kBBReturn || !bb->GetAttributes(kBBAttrIsTry) || bb->IsEmpty()) {
      continue;
    }
    // make sure this is a normal return bb
    // throw, retsub and retgoto are not allowed here
    if (bb->GetStmtNodes().back().GetOpCode() != OP_return) {
      continue;
    }
    // fast path
    StmtNode *stmt = bb->GetTheOnlyStmtNode();
    if (stmt) {
      size_t si = 0;
      // simplify the cfg removing all succs of this bb
      for (; si < bb->GetSucc().size(); si++) {
        BB *sucBB = bb->GetSucc(si);
        if (sucBB->GetAttributes(kBBAttrIsCatch)) {
          sucBB->RemoveBBFromPred(bb);
          bb->RemoveBBFromSucc(sucBB);
          si--;
        }
      }
      continue;
    }
    // split this non-trivial bb
    StmtNode *splitPoint = bb->GetStmtNodes().back().GetPrev();
    while (splitPoint != nullptr && splitPoint->GetOpCode() == OP_comment) {
      splitPoint = splitPoint->GetPrev();
    }
    ASSERT(splitPoint != nullptr, "just check");
    BB *newBB = func->SplitBB(bb, splitPoint);
    // because SplitBB will insert a bb, we need update bIt & eIt
    auto newBBIt = std::find(func->cbegin(), func->cend(), bb);
    bIt = build_filter_iterator(
        newBBIt, std::bind(FilterNullPtr<MapleVector<BB*>::const_iterator>, std::placeholders::_1, func->end()));
    eIt = func->valid_end();
    // redirect all succs of new bb to bb
    size_t si = 0;
    for (; si < newBB->GetSucc().size(); si++) {
      BB *sucBB = newBB->GetSucc(si);
      if (sucBB->GetAttributes(kBBAttrIsCatch)) {
        sucBB->ReplacePred(newBB, bb);
        newBB->RemoveBBFromSucc(sucBB);
        si--;
      }
    }
    if (bIt == eIt) {
      break;
    }
  }
}


// used only after DSE because it looks at live field of VersionSt
void MirCFG::ConvertPhis2IdentityAssigns(BB *meBB) {
  auto phiIt = meBB->GetPhiList().begin();
  while (phiIt != meBB->GetPhiList().end()) {
    if (!(*phiIt).second.GetResult()->IsLive()) {
      phiIt++;
      continue;
    }
    // replace phi with identify assignment as it only has 1 opnd
    OriginalSt *ost = (*phiIt).first;
    if (ost->IsSymbolOst() && ost->GetIndirectLev() == 0) {
      MIRSymbol *st = ost->GetMIRSymbol();
      MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(st->GetTyIdx());
      AddrofNode *dread = func->GetMIRModule().GetMIRBuilder()->CreateDread(st, GetRegPrimType(type->GetPrimType()));
      AddrofSSANode *dread2 = func->GetMirFunc()->GetCodeMemPool()->New<AddrofSSANode>(dread);
      dread2->SetSSAVar((*phiIt).second.GetPhiOpnd(0));
      DassignNode *dassign = func->GetMIRModule().GetMIRBuilder()->CreateStmtDassign(st, 0, dread2);
      func->GetMeSSATab()->GetStmtsSSAPart().SetSSAPartOf(
          dassign, func->GetMeSSATab()->GetStmtsSSAPart().GetSSAPartMp()->New<MayDefPartWithVersionSt>(
              &func->GetMeSSATab()->GetStmtsSSAPart().GetSSAPartAlloc()));
      MayDefPartWithVersionSt *theSSAPart =
          static_cast<MayDefPartWithVersionSt*>(func->GetMeSSATab()->GetStmtsSSAPart().SSAPartOf(dassign));
      theSSAPart->SetSSAVar((*phiIt).second.GetResult());
      meBB->PrependStmtNode(dassign);
    }
    phiIt++;
  }
  meBB->GetPhiList().clear();  // delete all the phis
  auto varPhiIt = meBB->GetMevarPhiList().begin();
  while (varPhiIt != meBB->GetMevarPhiList().end()) {
    if (!(*varPhiIt).second->GetIsLive()) {
      varPhiIt++;
      continue;
    }
    // replace phi with identify assignment as it only has 1 opnd
    OriginalSt *ost = func->GetMeSSATab()->GetOriginalStFromID(varPhiIt->first);
    if (ost->IsSymbolOst() && ost->GetIndirectLev() == 0) {
      DassignMeStmt *dassign = func->GetIRMap()->NewInPool<DassignMeStmt>();
      MeVarPhiNode *varPhi = varPhiIt->second;
      dassign->SetLHS(varPhi->GetLHS());
      dassign->SetRHS(varPhi->GetOpnd(0));
      dassign->SetBB(varPhi->GetDefBB());
      dassign->SetIsLive(varPhi->GetIsLive());
      meBB->PrependMeStmt(dassign);
    }
    varPhiIt++;
  }
  meBB->GetMevarPhiList().clear();  // delete all the phis
  auto regPhiIt = meBB->GetMeregphiList().begin();
  while (regPhiIt != meBB->GetMeregphiList().end()) {
    if (!(*regPhiIt).second->GetIsLive()) {
      regPhiIt++;
      continue;
    }
    // replace phi with identify assignment as it only has 1 opnd
    OriginalSt *ost = func->GetMeSSATab()->GetOriginalStFromID(regPhiIt->first);
    if (ost->IsSymbolOst() && ost->GetIndirectLev() == 0) {
      RegassignMeStmt *regass = func->GetIRMap()->New<RegassignMeStmt>();
      MeRegPhiNode *regPhi = regPhiIt->second;
      regass->SetLHS(regPhi->GetLHS());
      regass->SetRHS(regPhi->GetOpnd(0));
      regass->SetBB(regPhi->GetDefBB());
      regass->SetIsLive(regPhi->GetIsLive());
      meBB->PrependMeStmt(regass);
    }
    regPhiIt++;
  }
  meBB->GetMeregphiList().clear();  // delete all the phis
}

// analyse the CFG to find the BBs that are not reachable from function entries
// and delete them
void MirCFG::UnreachCodeAnalysis(bool updatePhi) {
  std::vector<bool> visitedBBs(func->NumBBs(), false);
  func->GetCommonEntryBB()->FindReachableBBs(visitedBBs);
  // delete the unreached bb
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    if (bIt == func->common_exit()) {
      continue;
    }
    auto *bb = *bIt;
    uint32 idx = bb->GetBBId().idx;
    if (!visitedBBs[idx] && !bb->GetAttributes(kBBAttrIsEntry)) {
      bb->SetAttributes(kBBAttrWontExit);
      /* avoid redundant pred before adding to common_exit_bb's pred list */
      size_t pi = 0;
      for (; pi < func->GetCommonExitBB()->GetPred().size(); pi++) {
        if (bb == func->GetCommonExitBB()->GetPred(pi)) {
          break;
        }
      }
      if (pi == func->GetCommonExitBB()->GetPred().size()) {
        func->GetCommonExitBB()->GetPred().push_back(bb);
      }
      if (!MeOptions::quiet) {
        LogInfo::MapleLogger() << "#### BB " << bb->GetBBId().idx << " deleted because unreachable\n";
      }
      if (bb->GetAttributes(kBBAttrIsTryEnd)) {
        // unreachable bb has try end info
        auto bbIt = std::find(func->rbegin(), func->rend(), bb);
        auto prevIt = ++bbIt;
        for (auto it = prevIt; it != func->rend(); ++it) {
          if (*it != nullptr) {
            // move entrytry tag to previous bb with try
            if ((*it)->GetAttributes(kBBAttrIsTry) && !(*it)->GetAttributes(kBBAttrIsTryEnd)) {
              (*it)->SetAttributes(kBBAttrIsTryEnd);
              func->GetEndTryBB2TryBB()[*it] = func->GetEndTryBB2TryBB()[bb];
            }
            break;
          }
        }
      }
      func->DeleteBasicBlock(bb);
      // remove the bb from its succ's pred_ list
      for (auto it = bb->GetSucc().begin(); it != bb->GetSucc().end(); it++) {
        BB *sucBB = *it;
        if (!updatePhi) {
          bb->RemoveBBFromVector(sucBB->GetPred());
        } else {
          sucBB->RemoveBBFromPred(bb);
          if (sucBB->GetPred().size() == 1) {
            ConvertPhis2IdentityAssigns(sucBB);
          } else if (sucBB->GetPred().empty()) {
            sucBB->GetPhiList().clear();
          }
        }
      }
      // remove the bb from common_exit_bb's pred list if it is there
      for (auto it = func->GetCommonExitBB()->GetPred().begin();
           it != func->GetCommonExitBB()->GetPred().end(); it++) {
        if (*it == bb) {
          func->GetCommonExitBB()->RemoveBBFromPred(bb);
          break;
        }
      }
    }
  }
}

// analyse the CFG to find the BBs that will not reach any function exit; these
// are BBs inside infinite loops; mark their wontExit flag and create
// artificial edges from them to common_exit_bb
void MirCFG::WontExitAnalysis() {
  if (func->NumBBs() == 0) {
    return;
  }
  std::vector<bool> visitedBBs(func->NumBBs(), false);
  func->GetCommonExitBB()->FindWillExitBBs(visitedBBs);
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    if (bIt == func->common_entry()) {
      continue;
    }
    auto *bb = *bIt;
    uint32 idx = bb->GetBBId().idx;
    if (!visitedBBs[idx]) {
      bb->SetAttributes(kBBAttrWontExit);
      if (!MeOptions::quiet) {
        LogInfo::MapleLogger() << "#### BB " << idx << " wont exit\n";
      }
      if (bb->GetKind() == kBBGoto) {
        // create artificial BB to transition to common_exit_bb
        BB *newBB = func->NewBasicBlock();
        // update bIt & eIt
        auto newBBIt = std::find(func->cbegin(), func->cend(), bb);
        bIt = build_filter_iterator(
            newBBIt, std::bind(FilterNullPtr<MapleVector<BB*>::const_iterator>, std::placeholders::_1, func->end()));
        eIt = func->valid_end();
        newBB->SetKind(kBBReturn);
        newBB->SetAttributes(kBBAttrIsExit);
        newBB->SetAttributes(kBBAttrArtificial);
        bb->GetSucc().push_back(newBB);
        newBB->GetPred().push_back(bb);
        func->GetCommonExitBB()->GetPred().push_back(newBB);
      }
    }
  }
}

// CFG Verify
// Check bb-vec and bb-list are strictly consistent.
void MirCFG::Verify() {
  // Check every bb in bb-list.
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    if (bIt == func->common_entry() || bIt == func->common_exit()) {
      continue;
    }
    auto *bb = *bIt;
    ASSERT(bb->GetBBId().idx < func->GetAllBBs().size(), "CFG Error!");
    ASSERT(func->GetBBFromID(bb->GetBBId()) == bb, "CFG Error!");
    if (bb->IsEmpty()) {
      continue;
    }
    ASSERT(bb->GetKind() != kBBUnknown, "runtime check error");
    /* verify succ[1] is goto bb */
    if (bb->GetKind() == kBBCondGoto) {
      ASSERT(bb->GetAttributes(kBBAttrIsTry) || bb->GetAttributes(kBBAttrWontExit) ||
             (bb->GetStmtNodes().rbegin().base().d() != nullptr && bb->GetSucc().size() == 2), "");
      ASSERT(bb->GetSucc(1)->GetBBLabel() == static_cast<CondGotoNode&>(bb->GetStmtNodes().back()).GetOffset(),
             "runtime check error");
    } else if (bb->GetKind() == kBBGoto) {
      if (bb->GetStmtNodes().back().GetOpCode() == OP_throw) {
        continue;
      }
      ASSERT(bb->GetAttributes(kBBAttrIsTry) || bb->GetAttributes(kBBAttrWontExit) ||
             (bb->GetStmtNodes().rbegin().base().d() != nullptr && bb->GetSucc().size() == 1), "");
      ASSERT(bb->GetSucc(0)->GetBBLabel() == static_cast<GotoNode&>(bb->GetStmtNodes().back()).GetOffset(),
             "runtime check error");
    }
  }
}

// check that all the target labels in jump statements are defined
void MirCFG::VerifyLabels(void) {
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    BB *mirBB = *bIt;
    auto &stmtNodes = mirBB->GetStmtNodes();
    if (stmtNodes.rbegin().base().d() == nullptr) {
      continue;
    }
    if (mirBB->GetKind() == kBBGoto) {
      if (mirBB->GetStmtNodes().back().GetOpCode() == OP_throw) {
        continue;
      }
      ASSERT(func->GetLabelBBIdMap()[(LabelIdx) static_cast<GotoNode&>(stmtNodes.back()).GetOffset()]->GetBBLabel() ==
          (LabelIdx) static_cast<GotoNode&>(stmtNodes.back()).GetOffset(), "undefined label in goto");
    } else if (mirBB->GetKind() == kBBCondGoto) {
      ASSERT(
          func->GetLabelBBIdMap()[(LabelIdx) static_cast<CondGotoNode&>(stmtNodes.back()).GetOffset()]->GetBBLabel() ==
              (LabelIdx) static_cast<CondGotoNode&>(stmtNodes.back()).GetOffset(),
              "undefined label in conditional branch");
    } else if (mirBB->GetKind() == kBBSwitch) {
      SwitchNode &switchStmt = static_cast<SwitchNode&>(stmtNodes.back());
      LabelIdx targetLabIdx = switchStmt.GetDefaultLabel();
      BB *bb = func->GetLabelBBIdMap()[targetLabIdx];
      ASSERT(bb->GetBBLabel() == targetLabIdx, "undefined label in switch");
      for (size_t j = 0; j < switchStmt.GetSwitchTable().size(); j++) {
        targetLabIdx = switchStmt.GetCasePair(j).second;
        bb = func->GetLabelBBIdMap()[targetLabIdx];
        ASSERT(bb->GetBBLabel() == targetLabIdx, "undefined switch target label");
      }
    }
  }
}

void MirCFG::Dump() {
  // BSF  Dump the cfg
  // map<uint32, uint32> visited_map;
  // set<uint32> visited_set;
  LogInfo::MapleLogger() << "####### CFG Dump: ";
  ASSERT(func->NumBBs() != 0, "size to be allocated is 0");
  bool *visitedMap = static_cast<bool*>(calloc(func->NumBBs(), sizeof(bool)));
  if (visitedMap != nullptr) {
    std::queue<BB*> qu;
    qu.push(func->GetFirstBB());
    while (!qu.empty()) {
      BB *bb = qu.front();
      qu.pop();
      if (bb == nullptr) {
        continue;
      }
      BBId id = bb->GetBBId();
      if (visitedMap[id.idx] == true) {
        continue;
      }
      LogInfo::MapleLogger() << id.idx << " ";
      visitedMap[id.idx] = true;
      auto it = bb->GetSucc().begin();
      while (it != bb->GetSucc().end()) {
        BB *kidBB = *it;
        if (!visitedMap[kidBB->GetBBId().idx]) {
          qu.push(kidBB);
        }
        it++;
      }
    }
    LogInfo::MapleLogger() << "\n";
    free(visitedMap);
  }
}

/* replace special char in FunctionName for output file */
static void ReplaceFilename(std::string &fileName) {
  for (size_t i = 0; i < fileName.length(); i++) {
    if (fileName[i] == ';' || fileName[i] == '/' || fileName[i] == '|') {
      fileName[i] = '_';
    }
  }
}

static bool ContainsConststr(const BaseNode *x) {
  if (x->GetOpCode() == OP_conststr || x->GetOpCode() == OP_conststr16) {
    return true;
  }
  for (size_t i = 0; i < x->NumOpnds(); i++)
    if (ContainsConststr(x->Opnd(i))) {
      return true;
    }
  return false;
}

/* generate dot file for cfg */
void MirCFG::DumpToFile(const char *prefix, bool dumpInStrs) {
  if (MeOptions::noDot) {
    return;
  }
  std::ofstream cfgFile;
  std::streambuf *coutBuf = LogInfo::MapleLogger().rdbuf(); /* keep original cout buffer */
  std::streambuf *buf = cfgFile.rdbuf();
  LogInfo::MapleLogger().rdbuf(buf);
  std::string fileName;
  if (prefix != nullptr) {
    fileName.append(prefix);
    fileName.append("-");
  }
  // the func name length may exceed OS's file name limit, so truncate after 80 chars
  if (func->GetName().size() <= 80) {
    fileName.append(func->GetName());
  } else {
    fileName.append(func->GetName().c_str(), 80);
  }
  ReplaceFilename(fileName);
  fileName.append(".dot");
  cfgFile.open(fileName.c_str(), std::ios::trunc);
  cfgFile << "digraph {\n";
  cfgFile << " # /*" << func->GetName().c_str() << " (red line is exception handler)*/\n";
  /* dump edge */
  auto eIt = func->valid_end();
  for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
    auto *bb = *bIt;
    if (bIt == func->common_exit()) {
      /* specical case for common_exit_bb */
      for (auto it = bb->GetPred().begin(); it != bb->GetPred().end(); it++) {
        cfgFile << "BB" << (*it)->GetBBId().idx << " -> "
                << "BB" << bb->GetBBId().idx << "[style=dotted];\n";
      }
      continue;
    }
    for (auto it = bb->GetSucc().begin(); it != bb->GetSucc().end(); it++) {
      cfgFile << "BB" << bb->GetBBId().idx << " -> "
              << "BB" << (*it)->GetBBId().idx;
      if (bb == func->GetCommonEntryBB()) {
        cfgFile << "[style=dotted];\n";
        continue;
      }
      if ((*it)->GetAttributes(kBBAttrIsCatch)) {
        /* succ is exception handler */
        cfgFile << "[color=red];\n";
      } else {
        cfgFile << ";\n";
      }
    }
  }
  /* dump instruction in each BB */
  if (dumpInStrs) {
    eIt = func->valid_end();
    for (auto bIt = func->valid_begin(); bIt != eIt; ++bIt) {
      auto *bb = *bIt;
      if (bb->IsEmpty()) {
        continue;
      }
      if (bb->GetKind() == kBBCondGoto) {
        cfgFile << "BB" << bb->GetBBId().idx << "[shape=diamond,label= \" BB" << bb->GetBBId().idx << ":\n{ ";
      } else {
        cfgFile << "BB" << bb->GetBBId().idx << "[shape=box,label= \" BB" << bb->GetBBId().idx << ":\n{ ";
      }
      if (bb->GetBBLabel() != 0) {
        cfgFile << "@" << func->GetMirFunc()->GetLabelName(bb->GetBBLabel()) << ":\n";
      }
      for (auto phiIt = bb->GetPhiList().begin(); phiIt != bb->GetPhiList().end(); phiIt++) {
        (*phiIt).second.Dump(&(func->GetMIRModule()));
      }
      for (auto &stmt : bb->GetStmtNodes()) {
        // avoid printing content that may contain " as this needs to be quoted
        if (stmt.GetOpCode() == OP_comment) {
          continue;
        }
        if (ContainsConststr(&stmt)) {
          continue;
        }
        stmt.Dump(&(func->GetMIRModule()), 1);
      }
      cfgFile << "}\"];\n";
    }
  }
  cfgFile << "}\n";
  cfgFile.flush();
  cfgFile.close();
  LogInfo::MapleLogger().rdbuf(coutBuf);
}

}  // namespace maple
