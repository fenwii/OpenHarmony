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
#ifndef MAPLE_ME_INCLUDE_SSA_MIR_NODES_H
#define MAPLE_ME_INCLUDE_SSA_MIR_NODES_H
#include <iostream>
#include "bb.h"
#include "ver_symbol.h"

/* This file define data structures to store SSA information in the IR
   instructions */

namespace maple {
struct OriginalStComparator {
  bool operator()(const OriginalSt *lhs, const OriginalSt *rhs) const {
    return lhs->GetIndex() < rhs->GetIndex();
  }
};

class MayDefNode {
 public:
  MayDefNode(VersionSt *sym, StmtNode *st) : opnd(sym), result(sym), stmt(st) {}

  ~MayDefNode() {}

  VersionSt *GetOpnd() {
    return opnd;
  }

  VersionSt *GetResult() {
    return result;
  }

  StmtNode *GetStmt() {
    return stmt;
  }

  void SetOpnd(VersionSt *sym) {
    opnd = sym;
  }

  void SetResult(VersionSt *sym) {
    result = sym;
  }

  bool IsRequired() const {
    return result->IsLive();
  }

  void MarkRequired() {
    result->MarkLive();
  }

  void Dump(const MIRModule *mod) {
    result->Dump(mod);
    LogInfo::MapleLogger() << " = MAYD(";
    opnd->Dump(mod);
    LogInfo::MapleLogger() << ")" << std::endl;
  }

 private:
  VersionSt *opnd;
  VersionSt *result;
  StmtNode *stmt;
};

class MayUseNode {
 public:
  explicit MayUseNode(VersionSt *sym) : opnd(sym) {}

  ~MayUseNode() {}

  VersionSt *GetOpnd() const {
    return opnd;
  }

  void SetOpnd(VersionSt *sym) {
    opnd = sym;
  }

  void Dump(const MIRModule *mod) const {
    LogInfo::MapleLogger() << " MAYU(";
    opnd->Dump(mod);
    LogInfo::MapleLogger() << ")";
  }

 private:
  VersionSt *opnd;
};

// this is only used in the callassigned type of call statements
class MustDefNode {
 public:
  MustDefNode() {
    result = nullptr, stmt = nullptr;
  }

  explicit MustDefNode(VersionSt *sym, StmtNode *st) : result(sym), stmt(st) {}

  ~MustDefNode() {}

  VersionSt *GetResult() {
    return result;
  }

  void SetResult(VersionSt *sym) {
    result = sym;
  }

  StmtNode *GetStmt() {
    return stmt;
  }

  bool IsRequired() const {
    return result->IsLive();
  }

  void MarkRequired() {
    result->MarkLive();
  }

  void Dump(const MIRModule *mod) {
    result->Dump(mod);
    LogInfo::MapleLogger() << " = MUSTDEF" << std::endl;
  }

 private:
  VersionSt *result;
  StmtNode *stmt;
};

class AccessSSANodes {
 public:
  AccessSSANodes() = default;
  virtual ~AccessSSANodes() {}

  virtual const MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() const {
    CHECK_FATAL(false, "No mayDefNodes");
  }

  virtual MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() {
    CHECK_FATAL(false, "No mayDefNodes");
  }

  virtual const MapleMap<OStIdx, MayUseNode> &GetMayUseNodes() const {
    CHECK_FATAL(false, "No mayUseNodes");
  }

  virtual MapleMap<OStIdx, MayUseNode> &GetMayUseNodes() {
    CHECK_FATAL(false, "No mayUseNodes");
  }

  virtual const MapleVector<MustDefNode> &GetMustDefNodes() const {
    CHECK_FATAL(false, "No mustDefNodes");
  }

  virtual MapleVector<MustDefNode> &GetMustDefNodes() {
    CHECK_FATAL(false, "No mustDefNodes");
  }

  virtual const VersionSt *GetSSAVar() const {
    CHECK_FATAL(false, "No ssaVar");
  }

  virtual VersionSt *GetSSAVar() {
    CHECK_FATAL(false, "No ssaVar");
  }

  virtual void DumpMayDefNodes(const MIRModule *mod) const {
    for (auto mayDefNode : GetMayDefNodes()) {
      mayDefNode.second.Dump(mod);
    }
  }

  virtual void DumpMayUseNodes(const MIRModule *mod) const {
    for (std::pair<OStIdx, MayUseNode> mapItem : GetMayUseNodes()) {
      mapItem.second.Dump(mod);
    }
  }

  virtual void DumpMustDefNodes(const MIRModule *mod) const {
    for (MustDefNode mustDefNode : GetMustDefNodes()) {
      mustDefNode.Dump(mod);
    }
  }

  virtual void InsertMayDefNode(VersionSt *vst, StmtNode *stmtNode) {
    GetMayDefNodes().insert(std::make_pair(vst->GetOrigSt()->GetIndex(), MayDefNode(vst, stmtNode)));
  }

  virtual void InsertMustDefNode(VersionSt *sym, StmtNode *s) {
    GetMustDefNodes().push_back(MustDefNode(sym, s));
  }
};

class MayDefPart : public AccessSSANodes {
 public:
  explicit MayDefPart(MapleAllocator *alloc) : mayDefNodes(std::less<OStIdx>(), alloc->Adapter()) {}

  virtual ~MayDefPart() {}

  const MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() const override {
    return mayDefNodes;
  }

  MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() override {
    return mayDefNodes;
  }

 private:
  MapleMap<OStIdx, MayDefNode> mayDefNodes;
};

class MayUsePart : public AccessSSANodes {
 public:
  explicit MayUsePart(MapleAllocator *alloc) : mayUseNodes(std::less<OStIdx>(), alloc->Adapter()) {}

  virtual ~MayUsePart() {}

  const MapleMap<OStIdx, MayUseNode> &GetMayUseNodes() const override {
    return mayUseNodes;
  }

  MapleMap<OStIdx, MayUseNode> &GetMayUseNodes() override {
    return mayUseNodes;
  }

 private:
  MapleMap<OStIdx, MayUseNode> mayUseNodes;
};

class MustDefPart : public AccessSSANodes {
 public:
  explicit MustDefPart(MapleAllocator *alloc) : mustDefNodes(alloc->Adapter()) {}

  virtual ~MustDefPart() {}

  const MapleVector<MustDefNode> &GetMustDefNodes() const override {
    return mustDefNodes;
  }

  MapleVector<MustDefNode> &GetMustDefNodes() override {
    return mustDefNodes;
  }

  MapleVector<MustDefNode> &GetMustdefnodes() {
    return mustDefNodes;
  }

 private:
  MapleVector<MustDefNode> mustDefNodes;
};

class MayDefPartWithVersionSt : public AccessSSANodes {
 public:
  explicit MayDefPartWithVersionSt(MapleAllocator *alloc)
      : ssaVar(nullptr), mayDefNodes(std::less<OStIdx>(), alloc->Adapter()) {}

  ~MayDefPartWithVersionSt() {}

  const MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() const override {
    return mayDefNodes;
  }

  MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() override {
    return mayDefNodes;
  }

  const VersionSt *GetSSAVar() const override {
    return ssaVar;
  }

  VersionSt *GetSSAVar() override {
    return ssaVar;
  }

  void SetSSAVar(VersionSt *ssaVarPara) {
    ssaVar = ssaVarPara;
  }

 private:
  VersionSt *ssaVar;
  MapleMap<OStIdx, MayDefNode> mayDefNodes;
};

class VersionStPart : public AccessSSANodes {
 public:
  VersionStPart() : ssaVar(nullptr) {}

  ~VersionStPart() {}

  const VersionSt *GetSSAVar() const override {
    return ssaVar;
  }

  VersionSt *GetSSAVar() override {
    return ssaVar;
  }

  void SetSSAVar(VersionSt *ssaVarPara) {
    ssaVar = ssaVarPara;
  }

 private:
  VersionSt *ssaVar;
};

class MayDefMayUsePart : public AccessSSANodes {
 public:
  explicit MayDefMayUsePart(MapleAllocator *alloc)
      : mayDefNodes(std::less<OStIdx>(), alloc->Adapter()), mayUseNodes(std::less<OStIdx>(), alloc->Adapter()) {}

  ~MayDefMayUsePart() {}

  const MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() const override {
    return mayDefNodes;
  }

  MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() override {
    return mayDefNodes;
  }

  const MapleMap<OStIdx, MayUseNode> &GetMayUseNodes() const override {
    return mayUseNodes;
  }

  MapleMap<OStIdx, MayUseNode> &GetMayUseNodes() override {
    return mayUseNodes;
  }

 private:
  MapleMap<OStIdx, MayDefNode> mayDefNodes;
  MapleMap<OStIdx, MayUseNode> mayUseNodes;
};

class MayDefMayUseMustDefPart : public AccessSSANodes {
 public:
  explicit MayDefMayUseMustDefPart(MapleAllocator *alloc)
      : mayDefNodes(std::less<OStIdx>(), alloc->Adapter()),
        mayUseNodes(std::less<OStIdx>(), alloc->Adapter()),
        mustDefNodes(alloc->Adapter()) {}

  ~MayDefMayUseMustDefPart() {}

  const MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() const override {
    return mayDefNodes;
  }

  MapleMap<OStIdx, MayDefNode> &GetMayDefNodes() override {
    return mayDefNodes;
  }

  const MapleMap<OStIdx, MayUseNode> &GetMayUseNodes() const override {
    return mayUseNodes;
  }

  MapleMap<OStIdx, MayUseNode> &GetMayUseNodes() override {
    return mayUseNodes;
  }

  const MapleVector<MustDefNode> &GetMustDefNodes() const override {
    return mustDefNodes;
  }

  MapleVector<MustDefNode> &GetMustDefNodes() override {
    return mustDefNodes;
  }

 private:
  MapleMap<OStIdx, MayDefNode> mayDefNodes;
  MapleMap<OStIdx, MayUseNode> mayUseNodes;
  MapleVector<MustDefNode> mustDefNodes;
};

// statement nodes are covered by StmtsSSAPart
class StmtsSSAPart {
 public:
  // Key of ssaPart is stmtID
  // Each element of ssaPart, depending on the stmt, can be pointer to one of:
  // (1) MayDefPart
  // (2) MayUsePart
  // (3) MayDefMayUsePart
  // (4) MayDefPartWithVersionSt
  // (5) MayDefMayUseMustDefPart
  // (6) VersionSt
  explicit StmtsSSAPart(MemPool *memPool)
      : ssaPartMp(memPool), ssaPartAlloc(memPool), ssaPart(ssaPartAlloc.Adapter()) {}

  ~StmtsSSAPart() {}

  AccessSSANodes *SSAPartOf(const StmtNode *s) {
    return ssaPart[s->GetStmtID()];
  }

  template <class T>
  void SetSSAPartOf(const StmtNode *s, T *p) {
    ssaPart[s->GetStmtID()] = p;
  }

  template <>
  void SetSSAPartOf(const StmtNode *s, VersionSt *vst) {
    VersionStPart *vStSSAPart = GetSSAPartMp()->New<VersionStPart>();
    vStSSAPart->SetSSAVar(vst);
    ssaPart[s->GetStmtID()] = vStSSAPart;
  }

  MemPool *GetSSAPartMp() {
    return ssaPartMp;
  }

  MapleAllocator &GetSSAPartAlloc() {
    return ssaPartAlloc;
  }

 private:
  MemPool *ssaPartMp;
  MapleAllocator ssaPartAlloc;
  MapleMap<uint32, AccessSSANodes*> ssaPart;  // key is stmtID
};

// The following expression nodes need extra fields to represent SSA
class AddrofSSANode : public AddrofNode {
 public:
  explicit AddrofSSANode(const AddrofNode *addrnode) : AddrofNode(addrnode->GetOpCode()) {
    SetPrimType(addrnode->GetPrimType());
    SetStIdx(addrnode->GetStIdx());
    SetFieldID(addrnode->GetFieldID());
    ssaVar = nullptr;
  }

  ~AddrofSSANode() {}

  void Dump(const MIRModule *mod, int32 indent) const {
    AddrofNode::Dump(mod, indent);
    if (ssaVar != nullptr) {
      ssaVar->Dump(mod, true);
    }
  }

  VersionSt *GetSSAVar() {
    return ssaVar;
  }

  void SetSSAVar(VersionSt *ssaVarPara) {
    ssaVar = ssaVarPara;
  }

 private:
  VersionSt *ssaVar;
};

class IreadSSANode : public IreadNode {
 public:
  IreadSSANode(MapleAllocator *alloc, IreadNode *inode) : IreadNode(inode->GetOpCode()), mayUse(nullptr) {
    SetPrimType(inode->GetPrimType());
    tyIdx = inode->GetTyIdx();
    fieldID = inode->GetFieldID();
    SetOpnd(inode->Opnd());
  }

  ~IreadSSANode() {}

  void Dump(const MIRModule *mod, int32 indent) const {
    if (mayUse.GetOpnd() != nullptr) {
      mayUse.Dump(mod);
    }
    IreadNode::Dump(mod, indent);
  }

  MayUseNode &GetMayUse() {
    return mayUse;
  }

 private:
  MayUseNode mayUse;
};

class RegreadSSANode : public RegreadNode {
 public:
  explicit RegreadSSANode(const RegreadNode *rreadnode) : RegreadNode() {
    SetPrimType(rreadnode->GetPrimType());
    SetRegIdx(rreadnode->GetRegIdx());
    ssaVar = nullptr;
  }

  ~RegreadSSANode() {}

  void Dump(const MIRModule *mod, int32 indent) const {
    RegreadNode::Dump(mod, indent);
    if (ssaVar != nullptr) {
      ssaVar->Dump(mod, true);
    }
  }

  VersionSt *GetSSAVar() {
    return ssaVar;
  }

  void SetSSAVar(VersionSt *ssaVarPara) {
    ssaVar = ssaVarPara;
  }

 private:
  VersionSt *ssaVar;
};

void GenericSSAPrint(MIRModule *mod, const StmtNode *stmtNode, int32 indent, StmtsSSAPart *stmtsSsaprt);
void SSAGenericInsertMayUseNode(const StmtNode *stmtNode, VersionSt *usesym, StmtsSSAPart *stmtsSsaprt);
void SSAGenericInsertMayDefNode(const StmtNode *stmtNode, VersionSt *vst, StmtNode *s, StmtsSSAPart *stmtsSsaprt);
MapleMap<OStIdx, MayUseNode> *SSAGenericGetMayUseNode(const StmtNode *stmtNode, StmtsSSAPart *stmtsSsaprt);
MapleMap<OStIdx, MayDefNode> *SSAGenericGetMayDefNodes(const StmtNode *stmtNode, StmtsSSAPart *stmtsSsaprt);
MapleMap<OStIdx, MayDefNode> *SSAGenericGetMayDefsFromVersionSt(VersionSt *sym, StmtsSSAPart *ssapart);
MapleVector<MustDefNode> *SSAGenericGetMustDefNode(const StmtNode *stmtNode, StmtsSSAPart *stmtsSsaprt);
bool HasMayUseDefPart(const StmtNode *stmtNode);
bool HasMayDefPart(const StmtNode *stmtNode);
bool HasMayUsePart(const StmtNode *stmtNode);
bool HasMayUseOpnd(const BaseNode *baseNode, SSATab *func);
bool HasMayDef(const StmtNode *stmtNode, SSATab *func);
inline bool HasMallocOpnd(const BaseNode *x) {
  return x->GetOpCode() == OP_malloc || x->GetOpCode() == OP_gcmalloc || x->GetOpCode() == OP_gcmallocjarray ||
         x->GetOpCode() == OP_alloca;
}

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_SSA_MIR_NODES_H
