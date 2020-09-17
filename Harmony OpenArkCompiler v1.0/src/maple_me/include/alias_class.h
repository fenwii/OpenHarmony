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
#ifndef MAPLE_ME_INCLUDE_ALIAS_CLASS_H
#define MAPLE_ME_INCLUDE_ALIAS_CLASS_H
#include "mempool.h"
#include "mempool_allocator.h"
#include "phase.h"
#include "ssa_tab.h"
#include "union_find.h"
#include "class_hierarchy.h"
#include "alias_analysis_table.h"

namespace maple {
class AliasElem {
 public:
  AliasElem(uint32 i, OriginalSt *origst)
      : id(i),
        ost(origst),
        notAllDefsSeen(false),
        nextLevNotAllDefsSeen(false),
        classSet(nullptr),
        assignSet(nullptr) {}

  ~AliasElem() {}

  void Dump(MIRModule *mod) const;

  uint32 GetClassID() const {
    return id;
  }

  OriginalSt *GetOriginalSt() const {
    return ost;
  }

  bool IsNotAllDefsSeen() const {
    return notAllDefsSeen;
  }

  void SetNotAllDefsSeen(bool allDefsSeen) {
    notAllDefsSeen = allDefsSeen;
  }

  bool IsNextLevNotAllDefsSeen() const {
    return nextLevNotAllDefsSeen;
  }

  void SetNextLevNotAllDefsSeen(bool allDefsSeen) {
    nextLevNotAllDefsSeen = allDefsSeen;
  }

  MapleSet<uint> *GetClassSet() const {
    return classSet;
  }

  void SetClassSet(MapleSet<uint> *set) {
    classSet = set;
  }

  MapleSet<uint> *GetAssignSet() const {
    return assignSet;
  }

  void SetAssignSet(MapleSet<uint> *set) {
    assignSet = set;
  }

 private:
  uint32 id;  // the original alias class id, before any union; start from 0
  OriginalSt *ost;
  bool notAllDefsSeen;         // applied to current level; unused for lev -1
  bool nextLevNotAllDefsSeen;  // remember that next level's elements need to be made notAllDefsSeen
  MapleSet<uint> *classSet;    // points to the set of members of its class; nullptr for single-member classes
  MapleSet<uint> *assignSet;   // points to the set of members that have assignments among themselves
};

class AliasClass : public AnalysisResult {
 public:
  AliasClass(MemPool *memPool, MIRModule *mod, SSATab *ssatb, bool lessThrowAliasParam, bool finalFieldHasAlias,
             bool ignoreIpa, bool setCalleeHasSideEffect = false, KlassHierarchy *kh = nullptr)
      : AnalysisResult(memPool),
        mirModule(mod),
        acMemPool(memPool),
        acAlloc(memPool),
        ssaTab(ssatb),
        unionFind(memPool),
        osym2Elem(ssatb->GetOriginalStTableSize(), nullptr, acAlloc.Adapter()),
        id2Elem(acAlloc.Adapter()),
        notAllDefsSeenClassSetRoots(acAlloc.Adapter()),
        globalsAffectedByCalls(std::less<uint>(), acAlloc.Adapter()),
        globalsMayAffectedByClinitCheck(acAlloc.Adapter()),
        lessThrowAlias(lessThrowAliasParam),
        finalFieldAlias(finalFieldHasAlias),
        ignoreIPA(ignoreIpa),
        calleeHasSideEffect(setCalleeHasSideEffect),
        klassHierarchy(kh),
        aliasAnalysisTable(nullptr) {}

  ~AliasClass() {}

  AliasAnalysisTable *GetAliasAnalysisTable() {
    if (aliasAnalysisTable == nullptr) {
      aliasAnalysisTable = acMemPool->New<AliasAnalysisTable>(ssaTab, acAlloc, mirModule);
    }
    return aliasAnalysisTable;
  }

  AliasElem *FindAliasElem(const OriginalSt *ost) const {
    return osym2Elem.at(ost->GetIndex().idx);
  }

  size_t GetAliasElemCount() const {
    return osym2Elem.size();
  }

  AliasElem *FindID2Elem(size_t id) const {
    return id2Elem.at(id);
  }

  bool IsCreatedByElimRC(const OriginalSt *ost) const {
    return ost->GetIndex().idx >= osym2Elem.size();
  }

  void ReinitUnionFind() {
    unionFind.Reinit();
  }

  void ApplyUnionForCopies(StmtNode *stmt);
  void CreateAssignSets();
  void DumpAssignSets();
  void UnionAllPointedTos();
  void ApplyUnionForPointedTos();
  void CollectRootIDOfNextLevelNodes(const OriginalSt *ost, std::set<uint> &rootIDOfNADSs);
  void UnionForNotAllDefsSeen();
  void CollectAliasGroups(std::map<uint, std::set<uint>> &aliasGroups);
  bool AliasAccordingToType(TyIdx tyidxA, TyIdx tyidxB);
  bool AliasAccordingToFieldID(const OriginalSt *ostA, const OriginalSt *ostB);
  void ReconstructAliasGroups();
  void CollectNotAllDefsSeenAes();
  void CreateClassSets();
  void DumpClassSets();
  void InsertMayDefUseCall(StmtNode *stmt, BBId bbid, bool hasSideEffect, bool hasNoPrivateDefEffect);
  void GenericInsertMayDefUse(StmtNode *stmt, BBId bbid);

 protected:
  MIRModule *mirModule;
  virtual bool InConstructorLikeFunc() const {
    return true;
  }

 private:
  MemPool *acMemPool;
  MapleAllocator acAlloc;
  SSATab *ssaTab;
  UnionFind unionFind;
  MapleVector<AliasElem*> osym2Elem;                    // index is OStIdx
  MapleVector<AliasElem*> id2Elem;                      // index is the id
  MapleVector<AliasElem*> notAllDefsSeenClassSetRoots;  // root of the not_all_defs_seen class sets
  MapleSet<uint> globalsAffectedByCalls;                // set of class ids of globals
  // aliased at calls; needed only when wholeProgramScope is true
  MapleSet<OStIdx> globalsMayAffectedByClinitCheck;
  bool lessThrowAlias;
  bool finalFieldAlias;  // whether to regard final fields as having alias;
  bool ignoreIPA;        // whether to ignore information provided by IPA
  bool calleeHasSideEffect;
  KlassHierarchy *klassHierarchy;
  AliasAnalysisTable *aliasAnalysisTable;
  bool CallHasNoSideEffectOrPrivateDefEffect(StmtNode *stmt, FuncAttrKind attrKind);
  bool CallHasSideEffect(StmtNode *stmt);
  bool CallHasNoPrivateDefEffect(StmtNode *stmt);
  AliasElem *FindOrCreateAliasElem(OriginalSt *ost);
  AliasElem *FindOrCreateExtraLevAliasElem(BaseNode *expr, TyIdx tyIdx, FieldID fieldId);
  AliasElem *CreateAliasElemsExpr(BaseNode *expr);
  void SetNotAllDefsSeenForMustDefs(const StmtNode *callas);
  void SetPtrOpndNextLevNADS(const BaseNode *opnd, AliasElem *ae, bool hasNoPrivateDefEffect);
  void SetPtrOpndsNextLevNADS(uint start, uint end, MapleVector<BaseNode*> &opnds, bool hasNoPrivateDefEffect);
  void ApplyUnionForDassignCopy(const AliasElem *lhsAe, const AliasElem *rhsAe, const BaseNode *rhs);
  AliasElem *FindOrCreateDummyNADSAe();
  void CollectMayDefForMustDefs(const StmtNode *stmt, std::set<OriginalSt*> &mayDefOsts);
  void CollectMayUseForCallOpnd(const StmtNode *stmt, std::set<OriginalSt*> &mayUseOsts);
  void InsertMayDefNodeForCall(std::set<OriginalSt*> &mayDefOsts, MapleMap<OStIdx, MayDefNode> *mayDefNodes,
                               StmtNode *stmt, BBId bbid, bool hasNoPrivateDefEffect);
  void InsertMayUseExpr(BaseNode *expr);
  void CollectMayUseFromGlobalsAffectedByCalls(std::set<OriginalSt*> &mayUseOsts);
  void CollectMayUseFromNADS(std::set<OriginalSt*> &mayUseOsts);
  void InsertMayUseNode(std::set<OriginalSt*> &mayUseOsts, MapleMap<OStIdx, MayUseNode> *mayUseNodes);
  void InsertMayUseReturn(const StmtNode *stmt);
  void CollectPtsToOfReturnOpnd(const OriginalSt *ost, std::set<OriginalSt*> &mayUseOsts);
  void InsertReturnOpndMayUse(const StmtNode *stmt);
  void InsertMayUseAll(const StmtNode *stmt);
  void CollectMayDefForDassign(const StmtNode *stmt, std::set<OriginalSt*> &mayDefOsts);
  void InsertMayDefNode(std::set<OriginalSt*> &mayDefOsts, MapleMap<OStIdx, MayDefNode> *mayDefNodes, StmtNode *stmt,
                        BBId bbid);
  void InsertMayDefDassign(StmtNode *stmt, BBId bbid);
  void CollectMayDefForIassign(StmtNode *stmt, std::set<OriginalSt*> &mayDefOsts);
  void InsertMayDefNodeExcludeFinalOst(std::set<OriginalSt*> &mayDefOsts, MapleMap<OStIdx, MayDefNode> *mayDefNodes,
                                       StmtNode *stmt, BBId bbid);
  void InsertMayDefIassign(StmtNode *stmt, BBId bbid);
  void InsertMayDefUseSyncOps(StmtNode *stmt, BBId bbid);
  void InsertMayUseNodeExcludeFinalOst(const std::set<OriginalSt*> &mayUseOsts, MapleMap<OStIdx, MayUseNode> *mayUseNodes);
  void InsertMayDefUseIntrncall(StmtNode *stmt, BBId bbid);
  void InsertMayDefUseClinitCheck(IntrinsiccallNode *stmt, BBId bbid);
  virtual BB *GetBB(BBId id) = 0;
  void ProcessIdsAliasWithRoot(const std::set<uint> &idsAliasWithRoot, std::vector<uint> &newGroups);
  void UpdateNextLevelNodes(std::vector<OriginalSt*> &nextLevelOsts, const AliasElem &aliasElem);
  void UnionNodes(std::vector<OriginalSt*> &nextLevelOsts);
  int GetOffset(const Klass &super, Klass &base) const;
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ALIAS_CLASS_H
