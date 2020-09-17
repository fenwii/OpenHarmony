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
#ifndef MAPLE_ME_INCLUDE_IRMAP_H
#define MAPLE_ME_INCLUDE_IRMAP_H
#include "bb.h"
#include "ver_symbol.h"
#include "ssa_tab.h"
#include "me_ir.h"
#include "dominance.h"

namespace maple {
class IRMap : public AnalysisResult {
 public:
  IRMap(SSATab *ssatab, Dominance *dom, MemPool *memPool, MemPool *tmpMemPool, uint32 hashTableSize)
      : AnalysisResult(memPool),
        ssaTab(ssatab),
        mirModule(&ssatab->mirModule),
        dom(dom),
        irMapAlloc(memPool),
        tempAlloc(tmpMemPool),
        exprID(0),
        mapHashLength(hashTableSize),
        hashTable(mapHashLength, nullptr, irMapAlloc.Adapter()),
        verst2MeExprTable(ssaTab->GetVersionStTableSize(), nullptr, irMapAlloc.Adapter()),
        regMeExprTable(irMapAlloc.Adapter()),
        needAnotherPass(false),
        curBB(nullptr) {}

  virtual ~IRMap() {}

  virtual BB *GetBB(BBId id) = 0;
  virtual BB *GetBBForLabIdx(LabelIdx lidx, PUIdx pidx = 0) = 0;
  Dominance *GetDominance() {
    return dom;
  }

  MeExpr *HashMeExpr(MeExpr *meExpr);
  void PutToBucket(uint32, MeExpr*);
  void BuildBB(BB *bb, std::vector<bool> &bbIRMapProcessed);
  void BuildAssertMeStmt(NaryMeExpr*);
  MeStmt *BuildMeStmtWithNoSSAPart(StmtNode *stmt);
  MeStmt *BuildMeStmt(StmtNode*);
  MeExpr *BuildExpr(BaseNode*);
  MeExpr *BuildLHSVar(const VersionSt *verSt, DassignMeStmt *defMeStmt, DassignNode *dassign);
  MeExpr *BuildLHSReg(const VersionSt *verSt, RegassignMeStmt *defMeStmt, const RegassignNode *regassign);
  IvarMeExpr *BuildLHSIvar(MeExpr *baseAddr, IassignMeStmt *iassignMeStmt, FieldID fieldID);
  IvarMeExpr *BuildLHSIvarFromIassMeStmt(IassignMeStmt *iassignMeStmt);
  RegMeExpr *CreateRefRegMeExpr(MIRSymbol*);
  RegMeExpr *CreateRegRefMeExpr(MeExpr*);
  RegMeExpr *CreateRegRefMeExpr(MIRType*);
  VarMeExpr *CreateVarMeExprVersion(const VarMeExpr*);
  MeExpr *CreateAddrofMeExpr(MeExpr*);
  RegMeExpr *CreateRegMeExpr(PrimType);
  RegMeExpr *CreateRegMeExprVersion(const OriginalSt*);
  RegMeExpr *CreateRegMeExprVersion(const RegMeExpr*);
  MeExpr *ReplaceMeExprExpr(MeExpr*, MeExpr*, MeExpr*);
  bool ReplaceMeExprStmtOpnd(uint32, MeStmt*, MeExpr*, MeExpr*);
  bool ReplaceMeExprStmt(MeStmt*, MeExpr*, MeExpr*);
  MeExpr *GetMeExprByVerID(uint32 verid) {
    return verst2MeExprTable[verid];
  }

  VarMeExpr *GetOrCreateVarFromVerSt(const VersionSt *verSt);
  VarMeExpr *GetOrCreateZeroVersionVarMeExpr(OriginalSt *oSt);
  RegMeExpr *GetOrCreateRegFromVerSt(const VersionSt *verSt);
  MeExpr *GetMeExpr(size_t index) {
    ASSERT(index < verst2MeExprTable.size(), "index out of range");
    MeExpr *meExpr = verst2MeExprTable.at(index);
    if (meExpr != nullptr) {
      ASSERT(meExpr->GetMeOp() == kMeOpVar || meExpr->GetMeOp() == kMeOpReg, "opcode error");
    }
    return meExpr;
  }

  VarMeExpr *CreateNewGlobalTmp(GStrIdx strIdx, PrimType ptyp);
  VarMeExpr *CreateNewLocalRefVarTmp(GStrIdx strIdx, TyIdx tIdx);
  DassignMeStmt *CreateDassignMeStmt(MeExpr*, MeExpr*, BB*);
  RegassignMeStmt *CreateRegassignMeStmt(MeExpr*, MeExpr*, BB*);
  void InsertMeStmtBefore(BB*, MeStmt*, MeStmt*);
  void BuildChiList(MeStmt*, MapleMap<OStIdx, MayDefNode> &, MapleMap<OStIdx, ChiMeNode*> &);
  void BuildMustDefList(MeStmt *meStmt, MapleVector<MustDefNode> &, MapleVector<MustDefMeNode> &);
  void BuildMuList(MapleMap<OStIdx, MayUseNode> &, MapleMap<OStIdx, VarMeExpr*> &);
  void BuildPhiMeNode(BB*);
  VersionSt *GetVerSt(size_t veridx) const {
    return ssaTab->GetVerSt(veridx);
  }

  MeRegPhiNode *CreateMeRegPhi(RegMeExpr*);
  MeVarPhiNode *CreateMeVarPhi(VarMeExpr*);
  bool Verify();  // iterate hash table and check with meexpr_table
  BB *GetFalseBrBB(CondGotoMeStmt*);
  std::string PhaseName() const {
    return "irmap";
  }

  virtual void Dump() = 0;
  virtual void SetCurFunction(BB *bb) {}

  MeExpr *CreateIntConstMeExpr(int64, PrimType);
  MeExpr *CreateConstMeExpr(PrimType, MIRConst*);
  MeExpr *CreateMeExprBinary(Opcode, PrimType, MeExpr*, MeExpr*);
  MeExpr *CreateMeExprSelect(PrimType, MeExpr*, MeExpr*, MeExpr*);
  MeExpr *CreateMeExprCompare(Opcode, PrimType, PrimType, MeExpr*, MeExpr*);
  MeExpr *CreateMeExprIntrinsiciop1(MIRIntrinsicID, PrimType, MeExpr*);
  MeExpr *CreateMeExprTypeCvt(PrimType, PrimType, MeExpr*);
  MeExpr *CreateAddrofMeExprFromNewSymbol(MIRSymbol*, PUIdx);
  IntrinsiccallMeStmt *CreateIntrinsicCallMeStmt(MIRIntrinsicID idx, std::vector<MeExpr*> &opnds,
                                                 TyIdx tyidx = TyIdx());
  IntrinsiccallMeStmt *CreateIntrinsicCallAssignedMeStmt(MIRIntrinsicID idx, std::vector<MeExpr*> &opnds, MeExpr *ret,
                                                         TyIdx tyidx = TyIdx());
  template <class T, typename... Arguments>
  T *NewInPool(Arguments&&... args) {
    return irMapAlloc.GetMemPool()->New<T>(&irMapAlloc, std::forward<Arguments>(args)...);
  }

  template <class T, typename... Arguments>
  T *New(Arguments&&... args) {
    return irMapAlloc.GetMemPool()->New<T>(std::forward<Arguments>(args)...);
  }

  SSATab *GetSSATab() const {
    return ssaTab;
  }

  MIRModule *GetMIRModule() const {
    return mirModule;
  }

  const MapleAllocator &GetIRMapAlloc() const {
    return irMapAlloc;
  }

  MapleAllocator &GetIRMapAlloc() {
    return irMapAlloc;
  }

  const MapleAllocator &GetTmpAlloc() const {
    return tempAlloc;
  }

  MapleAllocator &GetTempAlloc() {
    return tempAlloc;
  }

  int32 GetExprID() const {
    return exprID;
  }

  void SetExprID(int32 id) {
    exprID = id;
  }

  const MapleVector<MeExpr*> &GetVerst2MeExprTable() const {
    return verst2MeExprTable;
  }

  MeExpr *GetVerst2MeExprTableItem(int i) {
    return verst2MeExprTable[i];
  }

  size_t GetVerst2MeExprTableSize() const {
    return verst2MeExprTable.size();
  }

  void PushBackVerst2MeExprTable(MeExpr *item) {
    verst2MeExprTable.push_back(item);
  }

  MapleVector<RegMeExpr*> &GetRegMeExprTable() {
    return regMeExprTable;
  }

  void SetNeedAnotherPass(bool need) {
    needAnotherPass = need;
  }

  bool GetNeedAnotherPass() const {
    return needAnotherPass;
  }

  bool GetDumpStmtNum() const {
    return dumpStmtNum;
  }

  void SetDumpStmtNum(bool num) {
    dumpStmtNum = num;
  }

 private:
  SSATab *ssaTab;
  MIRModule *mirModule;
  Dominance *dom;
  MapleAllocator irMapAlloc;
  MapleAllocator tempAlloc;
  int32 exprID;                                    // for allocating exprid_ in MeExpr
  uint32 mapHashLength;                            // size of hashTable
  MapleVector<MeExpr*> hashTable;                  // the value number hash table
  MapleVector<MeExpr*> verst2MeExprTable;          // map versionst to MeExpr.
  MapleVector<RegMeExpr*> regMeExprTable;          // record all the regmeexpr created by ssapre
  bool needAnotherPass;                            // set to true if CFG has changed
  bool dumpStmtNum = false;
  BB *curBB;  // current maple_me::BB being visited
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_IRMAP_H
