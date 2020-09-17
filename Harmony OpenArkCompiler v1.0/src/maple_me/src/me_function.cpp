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
#include "me_function.h"
#include <iostream>
#include <fstream>
#include <functional>
#include "ssa_mir_nodes.h"
#include "me_ssa.h"
#include "me_cfg.h"
#include "mir_lower.h"
#include "mir_builder.h"
#include "me_irmap.h"
#include "me_phase.h"

namespace maple {
#if DEBUG
MIRModule *g_mirmodule = nullptr;
MeFunction *g_func = nullptr;
MeIRMap *g_irmap = nullptr;
SSATab *g_ssatab = nullptr;
#endif
void MeFunction::PartialInit(bool isSecondPass) {
  theCFG = nullptr;
  irmap = nullptr;
  regNum = 0;
  hasEH = false;
  secondPass = isSecondPass;
  if ((mirModule.GetSrcLang() == kSrcLangJava) && (!mirModule.CurFunction()->GetInfoVector().empty())) {
    std::string string("INFO_registers");
    GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(string);
    regNum = mirModule.CurFunction()->GetInfo(stridx);
    std::string trynum("INFO_tries_size");
    stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(trynum);
    uint32 num = mirModule.CurFunction()->GetInfo(stridx);
    hasEH = (num != 0);
  }
}


void MeFunction::Dump(bool DumpSimpIr) {
  LogInfo::MapleLogger() << ">>>>> Dump IR for Function " << mirFunc->GetName() << "<<<<<\n";
  if (irmap == nullptr || DumpSimpIr) {
    return;
  }
  auto eIt = valid_end();
  for (auto bIt = valid_begin(); bIt != eIt; ++bIt) {
    auto *bb = *bIt;
    bb->DumpHeader(&mirModule);
    bb->DumpMeVarPhiList(irmap);
    bb->DumpMeRegPhiList(irmap);
    for (auto &meStmt : bb->GetMeStmts()) {
      meStmt.Dump(irmap);
    }
  }
}

void MeFunction::SetTryBlockInfo(const StmtNode *nextStmt, StmtNode *tryStmt, BB *lastTryBB, BB *curBB, BB *newBB) {
  if (nextStmt->GetOpCode() == OP_endtry) {
    curBB->SetAttributes(kBBAttrIsTryEnd);
    ASSERT(lastTryBB != nullptr, "null ptr check");
    endTryBB2TryBB[curBB] = lastTryBB;
  } else {
    newBB->SetAttributes(kBBAttrIsTry);
    bbTryNodeMap[newBB] = tryStmt;
  }
}

void MeFunction::CreateBasicBlocks() {
  if (mirModule.CurFunction()->IsEmpty()) {
    if (!MeOptions::quiet) {
      LogInfo::MapleLogger() << "function is empty, cfg is nullptr\n";
    }
    return;
  }
  // create common_entry/exit bb first as bbVec[0] and bb_vec[1]
  auto *commonEntryBB = NewBasicBlock();
  commonEntryBB->SetAttributes(kBBAttrIsEntry);
  auto *commonExitBB = NewBasicBlock();
  commonExitBB->SetAttributes(kBBAttrIsExit);
  auto *firstBB = NewBasicBlock();
  firstBB->SetAttributes(kBBAttrIsEntry);
  StmtNode *nextStmt = mirModule.CurFunction()->GetBody()->GetFirst();
  ASSERT(nextStmt != nullptr, "function has no statement");
  BB *curBB = firstBB;
  StmtNode *tryStmt = nullptr;  // record current try stmt for map<bb, try_stmt>
  BB *lastTryBB = nullptr;      // bb containing try_stmt
  do {
    StmtNode *stmt = nextStmt;
    nextStmt = stmt->GetNext();
    switch (stmt->GetOpCode()) {
      case OP_goto: {
        if (curBB->IsEmpty()) {
          curBB->SetFirst(stmt);
        }
        curBB->SetLast(stmt);
        curBB->SetKind(kBBGoto);
        if (nextStmt != nullptr) {
          BB *newBB = NewBasicBlock();
          if (tryStmt != nullptr) {
            SetTryBlockInfo(nextStmt, tryStmt, lastTryBB, curBB, newBB);
          }
          curBB = newBB;
        }
        break;
      }
      case OP_dassign: {
        if (curBB->IsEmpty()) {
          curBB->SetFirst(stmt);
        }
        if (static_cast<DassignNode*>(stmt)->GetRHS()->MayThrowException()) {
          stmt->SetOpCode(OP_maydassign);
          if (tryStmt != nullptr) {
            // breaks new BB only inside try blocks
            curBB->SetLast(stmt);
            curBB->SetKind(kBBFallthru);
            BB *newBB = NewBasicBlock();
            SetTryBlockInfo(nextStmt, tryStmt, lastTryBB, curBB, newBB);
            curBB = newBB;
            break;
          }
        }
        if ((nextStmt == nullptr) && to_ptr(curBB->GetStmtNodes().rbegin()) == nullptr) {
          curBB->SetLast(stmt);
        }
        break;
      }
      case OP_brfalse:
      case OP_brtrue: {
        if (curBB->IsEmpty()) {
          curBB->SetFirst(stmt);
        }
        curBB->SetLast(stmt);
        curBB->SetKind(kBBCondGoto);
        BB *newBB = NewBasicBlock();
        if (tryStmt != nullptr) {
          SetTryBlockInfo(nextStmt, tryStmt, lastTryBB, curBB, newBB);
        }
        curBB = newBB;
        break;
      }
      case OP_if:
      case OP_doloop:
      case OP_dowhile:
      case OP_while: {
        ASSERT(false, "NYI");
        break;
      }
      case OP_throw:
        if (tryStmt != nullptr) {
          // handle as goto
          if (curBB->IsEmpty()) {
            curBB->SetFirst(stmt);
          }
          curBB->SetLast(stmt);
          curBB->SetKind(kBBGoto);
          if (nextStmt != nullptr) {
            BB *newBB = NewBasicBlock();
            SetTryBlockInfo(nextStmt, tryStmt, lastTryBB, curBB, newBB);
            curBB = newBB;
          }
          break;
        }
      // fall thru to handle as return
      case OP_gosub:
      case OP_retsub:
      case OP_return: {
        if (curBB->IsEmpty()) {
          curBB->SetFirst(stmt);
        }
        curBB->SetLast(stmt);
        curBB->SetKind(kBBReturn);
        curBB->SetAttributes(kBBAttrIsExit);
        if (nextStmt != nullptr) {
          BB *newBB = NewBasicBlock();
          if (tryStmt != nullptr) {
            SetTryBlockInfo(nextStmt, tryStmt, lastTryBB, curBB, newBB);
          }
          curBB = newBB;
          if (stmt->GetOpCode() == OP_gosub) {
            curBB->SetAttributes(kBBAttrIsEntry);
          }
        }
        break;
      }
      case OP_endtry:
        if (mirModule.GetSrcLang() == kSrcLangJava) {
          if (tryStmt == nullptr) {
            break;
          }
          /* skip OP_entry and generate it in emit phase */
          ASSERT(lastTryBB != nullptr, "null ptr check");
          tryStmt = nullptr;  // reset intryblocks
          if (!curBB->IsEmpty()) {
            StmtNode *lastStmt = stmt->GetPrev();
            ASSERT(curBB->GetStmtNodes().rbegin().base().d() == nullptr ||
                   curBB->GetStmtNodes().rbegin().base().d() == lastStmt,
                   "something wrong building BB");
            curBB->SetLast(lastStmt);
            if (curBB->GetKind() == kBBUnknown) {
              curBB->SetKind(kBBFallthru);
            }
            curBB->SetAttributes(kBBAttrIsTryEnd);
            endTryBB2TryBB[curBB] = lastTryBB;
            curBB = NewBasicBlock();
          } else if (curBB->GetBBLabel() != 0) {
            // create the empty BB
            curBB->SetKind(kBBFallthru);
            curBB->SetAttributes(kBBAttrIsTryEnd);
            endTryBB2TryBB[curBB] = lastTryBB;
            curBB = NewBasicBlock();
          } else {
          }  // endtry has already been processed in SetTryBlockInfo()
          lastTryBB = nullptr;
        } else {
          if (curBB->IsEmpty()) {
            curBB->SetFirst(stmt);
          }
          if ((nextStmt == nullptr) && (curBB->GetStmtNodes().rbegin().base().d() == nullptr)) {
            curBB->SetLast(stmt);
          }
        }
        break;
      case OP_try: {
        // start a new bb or with a label
        if (!curBB->IsEmpty()) {
          // prepare a new bb
          StmtNode *lastStmt = stmt->GetPrev();
          ASSERT(curBB->GetStmtNodes().rbegin().base().d() == nullptr ||
                 curBB->GetStmtNodes().rbegin().base().d() == lastStmt,
                 "something wrong building BB");
          curBB->SetLast(lastStmt);
          if (curBB->GetKind() == kBBUnknown) {
            curBB->SetKind(kBBFallthru);
          }
          BB *newBB = NewBasicBlock();
          // assume no nested try, so no need to call SetTryBlockInfo()
          curBB = newBB;
        }
        curBB->SetFirst(stmt);
        tryStmt = stmt;
        lastTryBB = curBB;
        curBB->SetAttributes(kBBAttrIsTry);
        bbTryNodeMap[curBB] = tryStmt;
        // prepare a new bb that contains only a OP_try. It is needed for
        // dse to work correctly: assignments in a try block should not affect
        // assignments before the try block as exceptions might occur.
        curBB->SetLast(stmt);
        curBB->SetKind(kBBFallthru);
        BB *newBB = NewBasicBlock();
        SetTryBlockInfo(nextStmt, tryStmt, lastTryBB, curBB, newBB);
        curBB = newBB;
        break;
      }
      case OP_catch: {
        // start a new bb or with a label
        if (!curBB->IsEmpty()) {
          // prepare a new bb
          StmtNode *lastStmt = stmt->GetPrev();
          ASSERT(curBB->GetStmtNodes().rbegin().base().d() == nullptr ||
                 curBB->GetStmtNodes().rbegin().base().d() == lastStmt,
                 "something wrong building BB");
          curBB->SetLast(lastStmt);
          if (curBB->GetKind() == kBBUnknown) {
            curBB->SetKind(kBBFallthru);
          }
          BB *newBB = NewBasicBlock();
          if (tryStmt != nullptr) {
            SetTryBlockInfo(nextStmt, tryStmt, lastTryBB, curBB, newBB);
          }
          curBB = newBB;
        }
        curBB->SetFirst(stmt);
        curBB->SetAttributes(kBBAttrIsCatch);
        CatchNode *catchNode = static_cast<CatchNode*>(stmt);
        const MapleVector<TyIdx> &exceptiontyidxvec = catchNode->GetExceptionTyIdxVec();
        for (size_t i = 0; i < exceptiontyidxvec.size(); i++) {
          MIRType *eType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(exceptiontyidxvec[i]);
          ASSERT(eType != nullptr && (eType->GetPrimType() == maple::PTY_ptr || eType->GetPrimType() == maple::PTY_ref),
                 "wrong exception type");
          MIRPtrType *epType = static_cast<MIRPtrType*>(eType);
          MIRType *pointType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(epType->GetPointedTyIdx());
          const std::string &ename = GlobalTables::GetStrTable().GetStringFromStrIdx(pointType->GetNameStrIdx());
          if ((pointType->GetPrimType() == maple::PTY_void) || (ename.compare("Ljava/lang/Throwable;") == 0) ||
              (ename.compare("Ljava/lang/Exception;") == 0)) {
            // "Ljava/lang/Exception;" is risk to set isJavaFinally because it
            // only deal with "throw exception". if throw error,  it's wrong
            curBB->SetAttributes(kBBAttrIsJavaFinally);  // this is a start of finally handler
          }
        }
        break;
      }
      case OP_label: {
        LabelNode *lblNode = static_cast<LabelNode*>(stmt);
        LabelIdx labidx = lblNode->GetLabelIdx();
        if (!curBB->IsEmpty() || curBB->GetBBLabel() != 0) {
          // prepare a new bb
          StmtNode *lastStmt = stmt->GetPrev();
          ASSERT((curBB->GetStmtNodes().rbegin().base().d() == nullptr ||
                  curBB->GetStmtNodes().rbegin().base().d() == lastStmt),
                 "something wrong building BB");
          if (curBB->GetStmtNodes().rbegin().base().d() == nullptr && (lastStmt->GetOpCode() != OP_label)) {
            if (mirModule.GetSrcLang() == kSrcLangJava && lastStmt->GetOpCode() == OP_endtry) {
              if (curBB->GetStmtNodes().empty()) {
                curBB->SetLast(nullptr);
              } else {
                // find a valid stmt which is not label or endtry
                StmtNode *p = lastStmt->GetPrev();
                ASSERT(p != nullptr, "null ptr check");
                ASSERT(p->GetOpCode() != OP_label, "runtime check error");
                ASSERT(p->GetOpCode() != OP_endtry, "runtime check error");
                curBB->SetLast(p);
              }
            } else {
              curBB->SetLast(lastStmt);
            }
          }
          if (curBB->GetKind() == kBBUnknown) {
            curBB->SetKind(kBBFallthru);
          }
          BB *newBB = NewBasicBlock();
          if (tryStmt != nullptr) {
            newBB->SetAttributes(kBBAttrIsTry);
            bbTryNodeMap[newBB] = tryStmt;
          }
          curBB = newBB;
        }
        labelBBIdMap[labidx] = curBB;
        curBB->SetBBLabel(labidx);
        break;
      }
      case OP_jscatch: {
        if (curBB->IsEmpty()) {
          curBB->SetFirst(stmt);
        }
        curBB->SetAttributes(kBBAttrIsEntry);
        curBB->SetAttributes(kBBAttrIsJSCatch);
        break;
      }
      case OP_finally: {
        ASSERT(curBB->GetStmtNodes().empty(), "runtime check error");
        curBB->SetFirst(stmt);
        curBB->SetAttributes(kBBAttrIsEntry);
        curBB->SetAttributes(kBBAttrIsJSFinally);
        break;
      }
      case OP_switch: {
        if (curBB->IsEmpty()) {
          curBB->SetFirst(stmt);
        }
        curBB->SetLast(stmt);
        curBB->SetKind(kBBSwitch);
        BB *newBB = NewBasicBlock();
        if (tryStmt != nullptr) {
          SetTryBlockInfo(nextStmt, tryStmt, lastTryBB, curBB, newBB);
        }
        curBB = newBB;
        break;
      }
      default: {
        if (curBB->IsEmpty()) {
          curBB->SetFirst(stmt);
        }
        if ((nextStmt == nullptr) && (curBB->GetStmtNodes().rbegin().base().d() == nullptr)) {
          curBB->SetLast(stmt);
        }
        break;
      }
    }
  } while (nextStmt != nullptr);
  ASSERT(tryStmt == nullptr,
         "unclosed try");    // tryandendtry should be one-one mapping
  ASSERT(lastTryBB == nullptr,
         "unclosed tryBB");  // tryandendtry should be one-one mapping
  auto *lastBB = curBB;
  if (lastBB->IsEmpty()) {
    // insert a return statement
    lastBB->SetFirst(mirModule.GetMIRBuilder()->CreateStmtReturn(nullptr));
    lastBB->SetLast(lastBB->GetStmtNodes().begin().d());
    lastBB->SetAttributes(kBBAttrIsExit);
    lastBB->SetKind(kBBReturn);
  } else if (lastBB->GetKind() == kBBUnknown) {
    lastBB->SetKind(kBBReturn);
  }
  return;
}

void MeFunction::Prepare(unsigned long rangeNum) {
  if (!MeOptions::quiet) {
    LogInfo::MapleLogger() << "---Preparing Function  < " << mirModule.CurFunction()->GetName() << " > [" << rangeNum
                           << "] ---\n";
  }
  /* lower first */
  MIRLower mirLowerer(mirModule, mirModule.CurFunction());
  mirLowerer.Init();
  mirLowerer.SetLowerME();
  mirLowerer.SetLowerExpandArray();
  mirLowerer.LowerFunc(mirModule.CurFunction());
  CreateBasicBlocks();
  if (NumBBs() == 0) {
    /* there's no basicblock generated */
    return;
  }
  RemoveEhEdgesInSyncRegion();
  theCFG = memPool->New<MirCFG>(this);
  theCFG->BuildMirCFG();
  theCFG->FixMirCFG();
  theCFG->VerifyLabels();
  theCFG->UnreachCodeAnalysis();
  theCFG->WontExitAnalysis();
  theCFG->Verify();
}

void MeFunction::Verify() {
  theCFG->Verify();
  theCFG->VerifyLabels();
}

BB *MeFunction::NewBasicBlock() {
  BB *newBB = memPool->New<BB>(&alloc, &versAlloc, BBId(nextBBId++));
  bbVec.push_back(newBB);
  return newBB;
}

// new a basic block and insert before position
BB *MeFunction::InsertNewBasicBlock(BB *position) {
  BB *newbb = memPool->New<BB>(&alloc, &versAlloc, BBId(nextBBId++));

  auto bIt = std::find(begin(), end(), position);
  auto idx = position->GetBBId().idx;
  auto newIt = bbVec.insert(bIt, newbb);
  auto eIt = end();
  // update bb's idx
  for (auto it = newIt; it != eIt; ++it) {
    if ((*it) != nullptr) {
      (*it)->SetBBId(BBId(idx));
    }
    idx++;
  }
  return newbb;
}

void MeFunction::DeleteBasicBlock(const BB *bb) {
  ASSERT(bbVec[bb->GetBBId().idx] == bb, "runtime check error");
  /* update first_bb_ and last_bb if needed */
  bbVec.at(bb->GetBBId().idx) = nullptr;
}

/* get next bb in bbVec */
BB *MeFunction::NextBB(const BB *bb) {
  auto bbIt = std::find(begin(), end(), bb);
  CHECK_FATAL(bbIt != end(), "bb must be inside bb_vec");
  for (auto it = ++bbIt; it != end(); ++it) {
    if (*it != nullptr) {
      return *it;
    }
  }
  return nullptr;
}

/* get prev bb in bbVec */
BB *MeFunction::PrevBB(const BB *bb) {
  auto bbIt = std::find(rbegin(), rend(), bb);
  CHECK_FATAL(bbIt != rend(), "bb must be inside bb_vec");
  for (auto it = ++bbIt; it != rend(); ++it) {
    if (*it != nullptr) {
      return *it;
    }
  }
  return nullptr;
}

/* clone stmtnode in orig bb to newBB */
void MeFunction::CloneBasicBlock(BB *newBB, BB *orig) {
  if (orig == nullptr || orig->IsEmpty()) {
    return;
  }
  for (auto &stmt : orig->GetStmtNodes()) {
    StmtNode *newStmt = static_cast<StmtNode*>(stmt.CloneTree(mirModule.CurFuncCodeMemPoolAllocator()));
    ASSERT(newStmt != nullptr, "null ptr check");
    newStmt->SetNext(nullptr);
    newStmt->SetPrev(nullptr);
    newBB->AddStmtNode(newStmt);
    if (meSSATab != nullptr) {
      meSSATab->CreateSSAStmt(newStmt, newBB);
    }
  }
}

/* Split BB at split_point */
BB *MeFunction::SplitBB(BB *bb, StmtNode *splitPoint) {
  BB *newBB = memPool->New<BB>(&alloc, &versAlloc, BBId(nextBBId++));
  StmtNode *newBBStart = splitPoint->GetNext();
  // Fix Stmt in BB.
  if (newBBStart != nullptr) {
    newBBStart->SetPrev(nullptr);
    for (StmtNode *stmt = newBBStart; stmt != nullptr;) {
      StmtNode *nextStmt = stmt->GetNext();
      newBB->AddStmtNode(stmt);
      if (meSSATab != nullptr) {
        meSSATab->CreateSSAStmt(stmt, newBB);
      }
      stmt = nextStmt;
    }
  }
  bb->SetLast(splitPoint);
  splitPoint->SetNext(nullptr);
  // Fix BB in CFG
  newBB->SetKind(bb->GetKind());
  bb->SetKind(kBBFallthru);
  auto bIt = std::find(begin(), end(), bb);
  auto idx = bb->GetBBId().idx;
  auto newIt = bbVec.insert(++bIt, newBB);
  auto eIt = end();
  // update bb's idx
  for (auto it = newIt; it != eIt; ++it) {
    idx++;
    if ((*it) != nullptr) {
      (*it)->SetBBId(BBId(idx));
    }
  }
  // Special Case: commonExitBB is orig bb's succ
  auto *commonExitBB = *common_exit();
  for (size_t i = 0; i < commonExitBB->GetPred().size(); i++) {
    if (commonExitBB->GetPred(i) == bb) {
      commonExitBB->SetPred(i, newBB);
      break;
    }
  }
  for (size_t i = 0; i < bb->GetSucc().size(); i++) {
    BB *succ = bb->GetSucc(i);
    succ->ReplacePred(bb, newBB);
  }
  bb->GetSucc().clear();
  bb->GetSucc().push_back(newBB);
  newBB->GetPred().push_back(bb);
  // Setup flags
  newBB->CopyFlagsAfterSplit(bb);
  if (newBB->GetAttributes(kBBAttrIsTryEnd)) {
    endTryBB2TryBB[newBB] = endTryBB2TryBB[bb];
    endTryBB2TryBB[bb] = nullptr;
    bb->ClearAttributes(kBBAttrIsTryEnd);
  }
  bb->ClearAttributes(kBBAttrIsExit);
  return newBB;
}

/* create label for bb */
void MeFunction::CreateBBLabel(BB *bb) {
  if (bb->GetBBLabel() != 0) {
    return;
  }
  LabelIdx label = mirModule.CurFunction()->GetLabelTab()->CreateLabelWithPrefix('m');
  mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(label);
  bb->SetBBLabel(label);
  labelBBIdMap.insert(std::make_pair(label, bb));
}

// Recognize the following kind of simple pattern and remove corresponding EH edges
// @label78044   catch { <* void> }
//  dassign %Reg0_R524935 0 (regread ptr %%thrownval)
//  syncexit (dread ref %Reg8_R460958)
//  endtry
//  throw (dread ptr %Reg0_R524935)
void MeFunction::RemoveEhEdgesInSyncRegion() {
  if (endTryBB2TryBB.size() != 1) {
    return;
  }
  for (auto iter : endTryBB2TryBB) {
    BB *tryBB = iter.second;
    BB *endtryBB = iter.first;
    CHECK_FATAL(tryBB != nullptr, "null ptr check ");
    CHECK_FATAL(endtryBB != nullptr, "null ptr check ");
    // Filter out complex cases
    if (!(endtryBB->GetAttributes(kBBAttrIsCatch) || endtryBB->GetAttributes(kBBAttrIsJSCatch)) ||
        endtryBB->GetKind() != kBBFallthru || !endtryBB->GetAttributes(kBBAttrIsTryEnd) ||
        !endtryBB->GetAttributes(kBBAttrIsJSFinally) || endtryBB->GetStmtNodes().back().GetOpCode() != OP_syncexit ||
        tryBB->GetStmtNodes().back().GetOpCode() != OP_try) {
      return;
    }
    for (auto it : bbTryNodeMap) {
      BB *bb = it.first;
      if (bb != tryBB && bb != endtryBB) {
        for (auto &stmt : bb->GetStmtNodes()) {
          if (stmt.GetOpCode() == OP_try || stmt.GetOpCode() == OP_catch || stmt.GetOpCode() == OP_throw) {
            return;
          }
        }
      }
    }
    // Unmark unnecessary isTry flags
    for (auto it : bbTryNodeMap) {
      BB *bb = it.first;
      if (bb != tryBB && bb != endtryBB) {
        bb->ClearAttributes(kBBAttrIsTry);
      }
    }
  }
}

}  // namespace maple
