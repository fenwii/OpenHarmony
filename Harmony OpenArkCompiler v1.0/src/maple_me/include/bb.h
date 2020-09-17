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
#ifndef MAPLE_ME_INCLUDE_BB_H
#define MAPLE_ME_INCLUDE_BB_H
#include "ptr_list_ref.h"
#include "ssa.h"

namespace maple {
class VersionSt;
class OriginalSt;
class MeStmt;
class MeVarPhiNode;
class MeRegPhiNode;
class IRMap;
enum BBKind {
  kBBUnknown,  // uninitialized
  kBBCondGoto,
  kBBGoto,  // unconditional branch
  kBBFallthru,
  kBBReturn,
  kBBAfterGosub,  // the BB that follows a gosub, as it is an entry point
  kBBSwitch,
  kBBInvalid
};

enum BBAttr {
  kBBNone,
  kBBIsEntry,   // is this BB a function entry point?
  kBBIsExit,    // is this BB a function exit point?
  kBBWontExit,  // this BB will not reach any exit block
  kBBIsTry,     // bb is tryblock which means more successor(handler)
  kBBIsTryEnd,  // bb is tryblock and with endtry
  kBBIsJSCatch,
  kBBIsJSFinally,
  kBBIsCatch,        // bb is start of catch handler
  kBBIsJavaFinally,  // bb is start of finally handler
  kBBArtificial,     // bb is inserted by maple_me
  kBBIsInLoop        // Is bb in a loop body
};

struct BBId {
  size_t idx;

  BBId() : idx(0) {}

  explicit BBId(size_t i) : idx(i) {}

  bool operator==(const BBId &x) const {
    return idx == x.idx;
  }

  bool operator!=(const BBId &x) const {
    return idx != x.idx;
  }

  bool operator<(const BBId &x) const {
    return idx < x.idx;
  }
};

struct OStIdx {
  size_t idx;

  OStIdx() {
    idx = 0;
  }

  explicit OStIdx(size_t i) : idx(i) {}

  bool operator==(const OStIdx &x) const {
    return idx == x.idx;
  }

  bool operator!=(const OStIdx &x) const {
    return idx != x.idx;
  }

  bool operator<(const OStIdx &x) const {
    return idx < x.idx;
  }
};

constexpr uint32 kBBAttrIsEntry = (1U << kBBIsEntry);
constexpr uint32 kBBAttrIsExit = (1U << kBBIsExit);
constexpr uint32 kBBAttrWontExit = (1U << kBBWontExit);
constexpr uint32 kBBAttrIsTry = (1U << kBBIsTry);
constexpr uint32 kBBAttrIsTryEnd = (1U << kBBIsTryEnd);
constexpr uint32 kBBAttrIsJSCatch = (1U << kBBIsJSCatch);
constexpr uint32 kBBAttrIsJSFinally = (1U << kBBIsJSFinally);
constexpr uint32 kBBAttrIsCatch = (1U << kBBIsCatch);
constexpr uint32 kBBAttrIsJavaFinally = (1U << kBBIsJavaFinally);
constexpr uint32 kBBAttrArtificial = (1U << kBBArtificial);
constexpr uint32 kBBAttrIsInLoop = (1U << kBBIsInLoop);
constexpr uint32 kBBVectorInitialSize = 2;
using StmtNodes = PtrListRef<StmtNode>;
using MeStmts = PtrListRef<MeStmt>;
class BB {
 public:
  BB(MapleAllocator *alloc, MapleAllocator *versAlloc, BBId id)
      : id(id),
        bbLabel(0),
        pred(kBBVectorInitialSize, nullptr, alloc->Adapter()),
        succ(kBBVectorInitialSize, nullptr, alloc->Adapter()),
        phiList(versAlloc->Adapter()),
        mevarPhiList(alloc->Adapter()),
        meregPhiList(alloc->Adapter()),
        frequency(0),
        kind(kBBUnknown),
        attributes(0) {
    pred.pop_back();
    pred.pop_back();
    succ.pop_back();
    succ.pop_back();
  }

  BB(MapleAllocator *alloc, MapleAllocator *versAlloc, BBId id, StmtNode *fstmt, StmtNode *lstmt)
      : id(id),
        bbLabel(0),
        pred(kBBVectorInitialSize, nullptr, alloc->Adapter()),
        succ(kBBVectorInitialSize, nullptr, alloc->Adapter()),
        phiList(versAlloc->Adapter()),
        mevarPhiList(alloc->Adapter()),
        meregPhiList(alloc->Adapter()),
        frequency(0),
        kind(kBBUnknown),
        attributes(0),
        stmtNodeList(fstmt, lstmt) {
    pred.pop_back();
    pred.pop_back();
    succ.pop_back();
    succ.pop_back();
  }

  bool GetAttributes(uint32 attrKind) const {
    return (attributes & attrKind) != 0;
  }

  void SetAttributes(uint32 attrKind) {
    attributes |= attrKind;
  }

  void ClearAttributes(uint32 attrKind) {
    attributes &= (~attrKind);
  }

  virtual bool IsGoto() const {
    return kind == kBBGoto;
  }

  virtual bool IsFuncEntry() const {
    return false;
  }

  virtual bool AddBackEndTry() const {
    return GetAttributes(kBBAttrIsTryEnd);
  }

  void Dump(MIRModule *mod);
  void DumpHeader(MIRModule *mod);
  void DumpBBAttribute(MIRModule *mod);
  std::string StrAttribute() const;
  void InsertBefore(BB *bb);  // insert this before bb in optimizer bb list
  void AddPredBB(BB *predVal) {
    ASSERT(predVal != nullptr, "null ptr check");
    pred.push_back(predVal);
    predVal->succ.push_back(this);
  }

  // This is to help new bb to keep some flags from original bb after logically splitting.
  void CopyFlagsAfterSplit(const BB *bb) {
    bb->GetAttributes(kBBAttrIsTry) ? SetAttributes(kBBAttrIsTry) : ClearAttributes(kBBAttrIsTry);
    bb->GetAttributes(kBBAttrIsTryEnd) ? SetAttributes(kBBAttrIsTryEnd) : ClearAttributes(kBBAttrIsTryEnd);
    bb->GetAttributes(kBBAttrIsExit) ? SetAttributes(kBBAttrIsExit) : ClearAttributes(kBBAttrIsExit);
    bb->GetAttributes(kBBAttrWontExit) ? SetAttributes(kBBAttrWontExit) : ClearAttributes(kBBAttrWontExit);
  }

  BBId GetBBId() const {
    return id;
  }

  void SetBBId(BBId idx) {
    id = idx;
  }

  uint32 UintID() const {
    return id.idx;
  }

  StmtNode *GetTheOnlyStmtNode();
  bool IsEmpty() const {
    return stmtNodeList.empty();
  }

  void SetFirst(StmtNode *stmt) {
    stmtNodeList.update_front(stmt);
  }

  void SetLast(StmtNode *stmt) {
    stmtNodeList.update_back(stmt);
  }

  void SetFirstMe(MeStmt *stmt);
  void SetLastMe(MeStmt *stmt);
  bool IsInList(MapleVector<BB*> &) const;
  bool IsPredBB(BB *bb) const {
    // if this is a pred of bb return true;
    // otherwise return false;
    return IsInList(bb->pred);
  }

  bool IsSuccBB(BB *bb) const {
    return IsInList(bb->succ);
  }

  void AddSuccBB(BB *succPara) {
    succ.push_back(succPara);
    succPara->pred.push_back(this);
  }

  void ReplacePred(const BB *old, BB *newPred);
  void ReplaceSucc(const BB *old, BB *newSucc);
  void ReplaceSuccOfCommonEntryBB(const BB *old, BB *newSucc);
  void AddStmtNode(StmtNode *stmt);
  void PrependStmtNode(StmtNode *stmt);
  void RemoveStmtNode(StmtNode *stmt);
  void RemoveLastStmt();
  void InsertStmtBefore(StmtNode *stmt, StmtNode *newStmt);
  void ReplaceStmt(StmtNode *stmt, StmtNode *newStmt);
  int RemoveBBFromVector(MapleVector<BB*> &);
  void RemoveBBFromPred(BB *bb);
  void RemoveBBFromSucc(BB *bb);
  void RemovePred(BB *predBB) {
    predBB->RemoveBBFromSucc(this);
    RemoveBBFromPred(predBB);
  }

  void RemoveSucc(BB *succBB) {
    succBB->RemoveBBFromPred(this);
    RemoveBBFromSucc(succBB);
  }

  void FindReachableBBs(std::vector<bool> &);
  void FindWillExitBBs(std::vector<bool> &);
  PhiNode *PhiofVerStInserted(VersionSt *vsym);
  void InsertPhi(MapleAllocator *alloc, VersionSt *vsym);
  void DumpPhi(const MIRModule*);
  bool IsMeStmtEmpty() const {
    return meStmtList.empty();
  }

  void PrependMeStmt(MeStmt *meStmt);
  void RemoveMeStmt(MeStmt *meStmt);
  void AddMeStmtFirst(MeStmt *meStmt);
  void AddMeStmtLast(MeStmt *meStmt);
  void InsertMeStmtBefore(MeStmt *meStmt, MeStmt *inStmt);
  void InsertMeStmtAfter(MeStmt *meStmt, MeStmt *inStmt);
  void InsertMeStmtLastBr(MeStmt *inStmt);
  void ReplaceMeStmt(MeStmt *stmt, MeStmt *newStmt);
  void DumpMeVarPhiList(IRMap *irMap);
  void DumpMeRegPhiList(IRMap *irMap);

  StmtNodes &GetStmtNodes() {
    return stmtNodeList;
  }

  const StmtNodes &GetStmtNodes() const {
    return stmtNodeList;
  }

  MeStmts &GetMeStmts() {
    return meStmtList;
  }

  const MeStmts &GetMeStmts() const {
    return meStmtList;
  }

  virtual ~BB(){};

  const LabelIdx GetBBLabel() const {
    return bbLabel;
  }

  void SetBBLabel(LabelIdx idx) {
    bbLabel = idx;
  }

  const uint32 &GetFrequency() const {
    return frequency;
  }

  void SetFrequency(uint32 f) {
    frequency = f;
  }

  const BBKind GetKind() const {
    return kind;
  }

  void SetKind(BBKind ind) {
    kind = ind;
  }

  MapleVector<BB*> &GetPred() {
    return pred;
  }

  const BB *GetPred(size_t cnt) const {
    ASSERT(cnt < pred.size(), "out of range in BB::GetPred");
    return pred.at(cnt);
  }

  BB *GetPred(size_t cnt) {
    ASSERT(cnt < pred.size(), "out of range in BB::GetPred");
    return pred.at(cnt);
  }

  void SetPred(size_t cnt, BB *pp) {
    CHECK_FATAL(cnt < pred.size(), "out of range in BB::SetPred");
    pred[cnt] = pp;
  }

  MapleVector<BB*> &GetSucc() {
    return succ;
  }

  const MapleVector<BB*> &GetSucc() const {
    return succ;
  }

  const BB *GetSucc(size_t cnt) const {
    ASSERT(cnt < succ.size(), "out of range in BB::GetSucc");
    return succ.at(cnt);
  }

  BB *GetSucc(size_t cnt) {
    ASSERT(cnt < succ.size(), "out of range in BB::GetSucc");
    return succ.at(cnt);
  }

  void SetSucc(size_t cnt, BB *ss) {
    CHECK_FATAL(cnt < succ.size(), "out of range in BB::SetSucc");
    succ[cnt] = ss;
  }

  MapleMap<OriginalSt*, PhiNode> &GetPhiList() {
    return phiList;
  }

  const MapleMap<OStIdx, MeVarPhiNode*> &GetMevarPhiList() const {
    return mevarPhiList;
  }

  MapleMap<OStIdx, MeVarPhiNode*> &GetMevarPhiList() {
    return mevarPhiList;
  }

  MapleMap<OStIdx, MeRegPhiNode*> &GetMeregphiList() {
    return meregPhiList;
  }

 private:
  BBId id;
  LabelIdx bbLabel;       // the BB's label
  MapleVector<BB*> pred;  // predecessor list
  MapleVector<BB*> succ;  // successor list
  MapleMap<OriginalSt*, PhiNode> phiList;
  MapleMap<OStIdx, MeVarPhiNode*> mevarPhiList;
  MapleMap<OStIdx, MeRegPhiNode*> meregPhiList;
  uint32 frequency;
  BBKind kind;
  uint32 attributes;
  StmtNodes stmtNodeList;
  MeStmts meStmtList;
};

}  // namespace maple

namespace std {

template <>
struct hash<maple::BBId> {
  size_t operator()(const maple::BBId &x) const {
    return x.idx;
  }
};

template <>
struct hash<maple::OStIdx> {
  size_t operator()(const maple::OStIdx &x) const {
    return x.idx;
  }
};

}  // namespace std

#endif  // MAPLE_ME_INCLUDE_BB_H
