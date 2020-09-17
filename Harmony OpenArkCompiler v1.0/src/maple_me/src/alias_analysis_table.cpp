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
#include "alias_analysis_table.h"
using namespace maple;
OriginalSt *AliasAnalysisTable::GetPrevLevelNode(const OriginalSt *ost) {
  ASSERT(ost != nullptr, "wrong stmt!");
  return prevLevelNode[ost->GetIndex()];
}

MapleVector<OriginalSt*> *AliasAnalysisTable::GetNextLevelNodes(const OriginalSt *ost) {
  ASSERT(ost != nullptr, "wrong stmt!");
  auto findNode = nextLevelNodes.find(ost->GetIndex());
  if (findNode == nextLevelNodes.end()) {
    MapleVector<OriginalSt*> *newOriginalStVec =
        alloc.GetMemPool()->New<MapleVector<OriginalSt*>>(alloc.Adapter());
    nextLevelNodes.insert(std::make_pair(ost->GetIndex(), newOriginalStVec));
    return newOriginalStVec;
  }
  return findNode->second;
}

OriginalSt *AliasAnalysisTable::FindOrCreateAddrofSymbolOriginalSt(const OriginalSt *ost) {
  ASSERT(ost != nullptr, "wrong stmt!");
  if (prevLevelNode.find(ost->GetIndex()) != prevLevelNode.end()) {
    return prevLevelNode[ost->GetIndex()];
  }
  // create a new node
  OriginalStTable *originalStTab = &(ssaTab->GetOriginalStTable());
  OriginalSt *prevLevelOst = memPool->New<OriginalSt>(originalStTab->Size(), ost->GetMIRSymbol(),
                                                      ost->GetPuIdx(), 0, &(originalStTab->GetAlloc()));
  originalStTab->GetOriginalStVector().push_back(prevLevelOst);
  prevLevelOst->SetIndirectLev(-1);
  MIRPtrType pointType(ost->GetTyIdx(), PTY_ptr);
  TyIdx newTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&pointType);
  prevLevelOst->SetTyIdx(newTyIdx);
  prevLevelOst->SetFieldID(ost->GetFieldID());
  GetNextLevelNodes(prevLevelOst)->push_back(const_cast<OriginalSt*>(ost));
  prevLevelNode.insert(std::make_pair(ost->GetIndex(), prevLevelOst));
  return prevLevelOst;
}

OriginalSt *AliasAnalysisTable::FindOrCreateExtraLevSymOrRegOriginalSt(OriginalSt *ost, TyIdx ptyIdx, FieldID fld) {
  ASSERT(ost != nullptr, "wrong stmt!");
  MapleVector<OriginalSt*> *nextLevelOsts = GetNextLevelNodes(ost);
  OriginalSt *nextLevOst = FindExtraLevOriginalSt(*nextLevelOsts, fld);
  if (nextLevOst != nullptr) {
    return nextLevOst;
  }

  // create a new node
  OriginalStTable *originalStTab = &(ssaTab->GetOriginalStTable());
  if (ost->IsSymbolOst()) {
    nextLevOst = memPool->New<OriginalSt>(originalStTab->Size(), ost->GetMIRSymbol(),
                                          ost->GetPuIdx(), fld, &(originalStTab->GetAlloc()));
  } else {
    nextLevOst = memPool->New<OriginalSt>(originalStTab->Size(), ost->GetPregIdx(),
                                          ost->GetPuIdx(), &(originalStTab->GetAlloc()));
  }
  originalStTab->GetOriginalStVector().push_back(nextLevOst);
  CHECK_FATAL(ost->GetIndirectLev() < INT8_MAX, "boundary check");
  nextLevOst->SetIndirectLev(ost->GetIndirectLev() + 1);
  prevLevelNode.insert(std::make_pair(nextLevOst->GetIndex(), ost));
  ptyIdx = (ptyIdx == 0) ? ost->GetTyIdx() : ptyIdx;
  if (ptyIdx != 0) {
    // use the tyIdx info from the instruction
    MIRPtrType *ptType = dynamic_cast<MIRPtrType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptyIdx));
    if (ptType != nullptr) {
      TyIdxFieldAttrPair fieldPair = ptType->GetPointedTyIdxFldAttrPairWithFieldID(fld);
      nextLevOst->SetTyIdx(fieldPair.first);
      nextLevOst->SetIsFinal(fieldPair.second.GetAttr(FLDATTR_final) && !mirModule->CurFunction()->IsConstructor());
      nextLevOst->SetIsPrivate(fieldPair.second.GetAttr(FLDATTR_private));
    } else {
      nextLevOst->SetTyIdx(TyIdx(PTY_void));
    }
  }
  ASSERT(!GlobalTables::GetTypeTable().GetTypeTable().empty(), "container check");
  if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(ost->GetTyIdx())->PointsToConstString()) {
    nextLevOst->SetIsFinal(true);
  }
  GetNextLevelNodes(ost)->push_back(nextLevOst);
  ASSERT(originalStTab->GetOriginalStFromID(ost->GetIndex()) == ost, "OriginalStTable:: index inconsistent");
  return nextLevOst;
}

OriginalSt *AliasAnalysisTable::FindOrCreateExtraLevOriginalSt(OriginalSt *ost, TyIdx ptyIdx, FieldID fld) {
  ASSERT(ost != nullptr, "wrong stmt!");
  if (ost->IsSymbolOst() || ost->IsPregOst()) {
    return FindOrCreateExtraLevSymOrRegOriginalSt(ost, ptyIdx, fld);
  }
  return nullptr;
}

OriginalSt *AliasAnalysisTable::FindExtraLevOriginalSt(const MapleVector<OriginalSt*> &nextLevelOsts, FieldID fld) {
  for (OriginalSt *nextLevelOst : nextLevelOsts) {
    if (nextLevelOst->GetFieldID() == fld) {
      return nextLevelOst;
    }
  }
  return nullptr;
}

OriginalSt *AliasAnalysisTable::FindOrCreateDiffFieldOriginalSt(const OriginalSt *ost, FieldID fld) {
  ASSERT(ost != nullptr, "wrong stmt!");
  OriginalSt *parentOst = prevLevelNode[ost->GetIndex()];
  if (parentOst == nullptr) {
    ASSERT(ost->IsSymbolOst(), "only SymbolOriginalSt expected");
    parentOst = FindOrCreateAddrofSymbolOriginalSt(ost);
  }
  MapleVector<OriginalSt*> *nextLevelOsts = GetNextLevelNodes(ost);
  OriginalSt *nextLevOst = FindExtraLevOriginalSt(*nextLevelOsts, fld);
  if (nextLevOst != nullptr) {
    return nextLevOst;
  }

  // create a new node
  TyIdxFieldAttrPair nextLevFieldPair;
  if (parentOst->GetTyIdx() != 0) {
    MIRPtrType *ptType =
        dynamic_cast<MIRPtrType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(parentOst->GetTyIdx()));
    if (ptType != nullptr) {
      nextLevFieldPair = ptType->GetPointedTyIdxFldAttrPairWithFieldID(fld);
    }
  }
  OriginalStTable *originalStTab = &(ssaTab->GetOriginalStTable());
  if (parentOst->IsSymbolOst()) {
    nextLevOst = memPool->New<OriginalSt>(originalStTab->Size(), parentOst->GetMIRSymbol(),
                                          parentOst->GetPuIdx(), fld, &(originalStTab->GetAlloc()));
    originalStTab->GetOriginalStVector().push_back(nextLevOst);
    ASSERT(parentOst->GetIndirectLev() < INT8_MAX, "boundary check");
    nextLevOst->SetIndirectLev(parentOst->GetIndirectLev() + 1);
    prevLevelNode.insert(std::make_pair(nextLevOst->GetIndex(), parentOst));
    nextLevOst->SetTyIdx(nextLevFieldPair.first);
    bool isFinal = nextLevFieldPair.second.GetAttr(FLDATTR_final) && !mirModule->CurFunction()->IsConstructor();
    nextLevOst->SetIsFinal(isFinal);
    ASSERT(!GlobalTables::GetTypeTable().GetTypeTable().empty(), "container check");
    if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(parentOst->GetTyIdx())->PointsToConstString()) {
      nextLevOst->SetIsFinal(true);
    }
    nextLevOst->SetIsPrivate(nextLevFieldPair.second.GetAttr(FLDATTR_private));
    nextLevelOsts->push_back(nextLevOst);
    return nextLevOst;
  }
  return nullptr;
}

OriginalSt *AliasAnalysisTable::FindDiffFieldOriginalSt(const OriginalSt *ost, FieldID fld) {
  ASSERT(ost != nullptr, "wrong stmt!");
  OriginalSt *parentOst = prevLevelNode[ost->GetIndex()];
  MapleVector<OriginalSt*> *nextLevelOsts = GetNextLevelNodes(parentOst);
  return FindExtraLevOriginalSt(*nextLevelOsts, fld);
}
