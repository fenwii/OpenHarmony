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
#ifndef MAPLE_ME_INCLUDE_ME_IR_H
#define MAPLE_ME_INCLUDE_ME_IR_H
#include <array>
#include "orig_symbol.h"

namespace maple {
class BB;
class PhiNode;
class MeStmt;
class IRMap;
class SSATab;
class VarMeExpr;
class RegMeExpr;
class OriginalSt;
class Dominance;
using MeStmtPtr = MeStmt*;
enum MeExprOp : std::uint8_t {
  kMeOpUnknown,
  kMeOpVar,
  kMeOpIvar,
  kMeOpAddrof,
  kMeOpAddroffunc,
  kMeOpGcmalloc,
  kMeOpReg,
  kMeOpConst,
  kMeOpConststr,
  kMeOpConststr16,
  kMeOpSizeoftype,
  kMeOpFieldsDist,
  kMeOpOp,
  kMeOpNary,
};  // cache the op to avoid dynamic cast

constexpr int kInvalidExprID = -1;
class MeExpr {
 public:
  MeExpr(int32 exprid, MeExprOp o)
      : op(kOpUndef), primType(kPtyInvalid), numOpnds(0), meOp(o), exprID(exprid), depth(0), treeID(0), next(nullptr) {}

  virtual ~MeExpr() = default;

  void SetOp(Opcode opcode) {
    op = opcode;
  }

  void SetPtyp(PrimType primtypeVal) {
    primType = primtypeVal;
  }

  void SetNumOpnds(uint8 val) {
    numOpnds = val;
  }

  void SetTreeID(uint32 val) {
    treeID = val;
  }

  void SetNext(MeExpr *nextPara) {
    next = nextPara;
  }

  Opcode GetOp() const {
    return op;
  }

  PrimType GetPrimType() const {
    return primType;
  }

  uint8 GetNumOpnds() const {
    return numOpnds;
  }

  MeExprOp GetMeOp() const {
    return meOp;
  }

  int32 GetExprID() const {
    return exprID;
  }

  uint8 GetDepth() const {
    return depth;
  }

  uint32 GetTreeID() const {
    return treeID;
  }

  MeExpr *GetNext() const {
    return next;
  }

  void InitBase(Opcode o, PrimType t, uint32 n) {
    op = o;
    primType = t;
    numOpnds = n;
  }

  virtual void Dump(IRMap*, int32 indent = 0) const {}

  virtual bool IsZero() const {
    return false;
  }

  virtual bool IsUseSameSymbol(MeExpr *expr) const {
    return expr && (exprID == expr->exprID);
  }

  virtual BaseNode *EmitExpr(SSATab*) = 0;
  bool IsLeaf() const {
    return numOpnds == 0;
  }

  bool IsGcmalloc() const {
    return op == OP_gcmalloc || op == OP_gcmallocjarray || op == OP_gcpermalloc || op == OP_gcpermallocjarray;
  }

  virtual bool IsVolatile(SSATab*) {
    return false;
  }

  bool IsTheSameWorkcand(MeExpr*) const;
  virtual void SetDefByStmt(MeStmt*) {}

  virtual MeExpr *GetOpnd(size_t i) const {
    return nullptr;
  }

  void UpdateDepth();                      // update the depth, suppose all sub nodes have already depth done.
  MeExpr *GetAddrExprBase();               // get the base of the address expression
  MeExpr *FindSymAppearance(OStIdx oidx);  // find the appearance of the symbol
  // in the expression; nullptr otherwise
  bool SymAppears(OStIdx oidx);  // check if symbol appears in the expression
  bool HasIvar() const;          // whether there is any iread node in the expression
  bool Pure() const {
    return !kOpcodeInfo.NotPure(op);
  }

  bool IsSameVariableValue(VarMeExpr*) const;
  MeExpr *ResolveMeExprValue();
  bool CouldThrowException() const;
  bool PointsToSomethingThatNeedsIncRef();
  virtual uint32 GetHashIndex() const {
    return 0;
  }

 private:
  Opcode op;
  PrimType primType;
  uint8 numOpnds;
  MeExprOp meOp;
  int32 exprID;
  uint8 depth;
  uint32 treeID;  // for bookkeeping purpose during SSAPRE
  MeExpr *next;
};

enum MeDefBy {
  kDefByNo,
  kDefByStmt,
  kDefByPhi,
  kDefByChi,
  kDefByMustDef,  // only applies to callassigned and its siblings
};

class ChiMeNode;      // forward decl
class MustDefMeNode;  // forward decl
class IassignMeStmt;  // forward decl


// represant dread
class VarMeExpr : public MeExpr {
 public:
 public:
  VarMeExpr(int32 exprid, OStIdx oidx, size_t vidx)
      : MeExpr(exprid, kMeOpVar),
        def{ .defStmt = nullptr },
        ostIdx(oidx),
        vstIdx(vidx),
        fieldID(0),
        inferredTyIdx(0),
        defBy(kDefByNo),
        maybeNull(true) {
  }

  ~VarMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  bool IsUseSameSymbol(MeExpr*) const;
  BaseNode *EmitExpr(SSATab*);
  bool IsValidVerIdx(SSATab *ssaTab);
  void SetDefByStmt(MeStmt *defStmt) {
    defBy = kDefByStmt;
    def.defStmt = defStmt;
  }

  bool IsDefByPhi() const {
    return defBy == kDefByPhi;
  }

  MeVarPhiNode *GetMeVarPhiDef() const {
    return IsDefByPhi() ? def.defPhi : nullptr;
  }

  BB *DefByBB();
  bool IsVolatile(SSATab*);
  // indicate if the variable is local variable but not a function formal variable
  bool IsPureLocal(SSATab*, const MIRFunction*) const;
  bool IsZeroVersion(SSATab*) const;
  BB *GetDefByBBMeStmt(Dominance*, MeStmtPtr&);
  VarMeExpr *ResolveVarMeValue();

  const OStIdx &GetOStIdx() const {
    return ostIdx;
  }

  size_t GetVstIdx() const {
    return vstIdx;
  }

  void SetVstIdx(size_t vstIdxVal) {
    vstIdx = vstIdxVal;
  }

  FieldID GetFieldID() const {
    return fieldID;
  }

  void SetFieldID(FieldID fieldId) {
    fieldID = fieldId;
  }

  TyIdx &GetInferredTyIdx() {
    return inferredTyIdx;
  }

  void SetInferredTyIdx(TyIdx inferredTyIdxVal) {
    inferredTyIdx = inferredTyIdxVal;
  }

  MeDefBy GetDefBy() const {
    return defBy;
  }

  void SetDefBy(MeDefBy defByVal) {
    defBy = defByVal;
  }

  bool GetMaybeNull() {
    return maybeNull;
  }

  void SetMaybeNull(bool maybeNullVal) {
    maybeNull = maybeNullVal;
  }

  MeStmt *GetDefStmt() const {
    return def.defStmt;
  }

  void SetDefStmt(MeStmt *defStmt) {
    def.defStmt = defStmt;
  }

  MeVarPhiNode *GetDefPhi() {
    return def.defPhi;
  }

  void SetDefPhi(MeVarPhiNode *defPhi) {
    def.defPhi = defPhi;
  }

  ChiMeNode *GetDefChi() {
    return def.defChi;
  }

  void SetDefChi(ChiMeNode *defChi) {
    def.defChi = defChi;
  }

  MustDefMeNode *GetDefMustDef() {
    return def.defMustDef;
  }

  void SetDefMustDef(MustDefMeNode *defMustDef) {
    def.defMustDef = defMustDef;
  }

 private:
  union {
    MeStmt *defStmt;  // definition stmt of this var
    MeVarPhiNode *defPhi;
    ChiMeNode *defChi;          // definition node by Chi
    MustDefMeNode *defMustDef;  // definition by callassigned
  } def;

  OStIdx ostIdx;  // the index in MEOptimizer's OriginalStTable;
  size_t vstIdx;  // the index in MEOptimizer's VersionStTable, 0 if not in VersionStTable
  FieldID fieldID;
  TyIdx inferredTyIdx; /* Non zero if it has a known type (allocation type is seen). */
  MeDefBy defBy;
  bool maybeNull;  // false if definitely not null
};

class MeVarPhiNode {
 public:
  explicit MeVarPhiNode(MapleAllocator *alloc)
      : lhs(nullptr), opnds(2, nullptr, alloc->Adapter()), isLive(true), defBB(nullptr) {
    opnds.pop_back();
    opnds.pop_back();
  }

  MeVarPhiNode(VarMeExpr *var, MapleAllocator *alloc)
      : lhs(var), opnds(2, nullptr, alloc->Adapter()), isLive(true), defBB(nullptr) {
    var->SetDefPhi(this);
    var->SetDefBy(kDefByPhi);
    opnds.pop_back();
    opnds.pop_back();
  }

  ~MeVarPhiNode() = default;

  void UpdateLHS(VarMeExpr *var) {
    lhs = var;
    var->SetDefBy(kDefByPhi);
    var->SetDefPhi(this);
  }

  bool IsPureLocal(SSATab *ssatab, MIRFunction *mirfunc);
  void Dump(IRMap *irmap) const;

  VarMeExpr *GetOpnd(size_t idx) const {
    ASSERT(idx < opnds.size(), "out of range in MeVarPhiNode::GetOpnd");
    return opnds.at(idx);
  }

  void SetOpnd(size_t idx, VarMeExpr *opnd) {
    CHECK_FATAL(idx < opnds.size(), "out of range in MeVarPhiNode::SetOpnd");
    opnds[idx] = opnd;
  }

  MapleVector<VarMeExpr*> &GetOpnds() {
    return opnds;
  }

  void SetIsLive(bool isliveVal) {
    isLive = isliveVal;
  }

  bool GetIsLive() {
    return isLive;
  }

  void SetDefBB(BB *defbbVal) {
    defBB = defbbVal;
  }

  BB *GetDefBB() {
    return defBB;
  }

  VarMeExpr *GetLHS() {
    return lhs;
  }

  void SetLHS(VarMeExpr *value) {
    lhs = value;
  }

 private:
  VarMeExpr *lhs;
  MapleVector<VarMeExpr*> opnds;
  bool isLive;
  BB *defBB;  // the bb that defines this phi
};

class RegMeExpr : public MeExpr {
 public:
  RegMeExpr(MapleAllocator *alloc, int32 exprid, PregIdx preg, PUIdx pidx, OStIdx oidx, uint32 vidx)
      : MeExpr(exprid, kMeOpReg),
        regIdx(preg),
        defBy(kDefByNo),
        recursivePtr(false),
        puIdx(pidx),
        ostIdx(oidx),
        vstIdx(vidx),
        phiUseSet(std::less<MeRegPhiNode*>(), alloc->Adapter()) {
    def.defStmt = nullptr;
  }

  ~RegMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  BaseNode *EmitExpr(SSATab*);
  void SetDefByStmt(MeStmt *defStmt) {
    defBy = kDefByStmt;
    def.defStmt = defStmt;
  }

  bool IsDefByPhi() const {
    return defBy == kDefByPhi;
  }

  MeRegPhiNode *GetMeRegPhiDef() {
    return IsDefByPhi() ? def.defPhi : nullptr;
  }

  bool IsUseSameSymbol(MeExpr*) const;
  BB *DefByBB();
  RegMeExpr *FindDefByStmt(std::set<RegMeExpr*> *visited);

  PregIdx16 GetRegIdx() const {
    return regIdx;
  }

  void SetRegIdx(PregIdx16 regIdxVal) {
    regIdx = regIdxVal;
  }

  MeDefBy GetDefBy() const {
    return defBy;
  }

  void SetDefBy(MeDefBy defByVal) {
    defBy = defByVal;
  }

  PUIdx GetPuIdx() const {
    return puIdx;
  }

  OStIdx GetOstIdx() const {
    return ostIdx;
  }

  MapleSet<MeRegPhiNode*> &GetPhiUseSet() {
    return phiUseSet;
  }

  MeStmt *GetDefStmt() const {
    return def.defStmt;
  }

  MeRegPhiNode *GetDefPhi() {
    return def.defPhi;
  }

  MustDefMeNode *GetDefMustDef() {
    return def.defMustDef;
  }

  void SetDefStmt(MeStmt *defStmtVal) {
    def.defStmt = defStmtVal;
  }

  void SetDefPhi(MeRegPhiNode *defPhiVal) {
    def.defPhi = defPhiVal;
  }

  void SetDefMustDef(MustDefMeNode *defMustDefVal) {
    def.defMustDef = defMustDefVal;
  }

 private:
  PregIdx16 regIdx;
  MeDefBy defBy;
  bool recursivePtr;  // if pointer to recursive data structures;
  // used only is_escaped is false
  PUIdx puIdx;
  OStIdx ostIdx;                      // the index in MEOptimizer's OriginalStTable;
  uint32 vstIdx;                      // the index in MEOptimizer's VersionStTable, 0 if not in VersionStTable
  MapleSet<MeRegPhiNode*> phiUseSet;  // the use set of this reg node, used by preg renamer
  union {
    MeStmt *defStmt;
    MeRegPhiNode *defPhi;
    MustDefMeNode *defMustDef;  // definition by callassigned
  } def;
};

class MeRegPhiNode {
 public:
  explicit MeRegPhiNode(MapleAllocator *alloc)
      : lhs(nullptr), opnds(2, nullptr, alloc->Adapter()), isLive(true), defBB(nullptr) {
    opnds.pop_back();
    opnds.pop_back();
  }

  ~MeRegPhiNode() = default;

  void UpdateLHS(RegMeExpr *reg) {
    lhs = reg;
    reg->SetDefBy(kDefByPhi);
    reg->SetDefPhi(this);
  }

  void Dump(IRMap *irMap) const;

  RegMeExpr *GetLHS() {
    return lhs;
  }

  void SetLHS(RegMeExpr *lhsVal) {
    lhs = lhsVal;
  }

  MapleVector<RegMeExpr*> &GetOpnds() {
    return opnds;
  }

  RegMeExpr *GetOpnd(size_t idx) {
    CHECK_FATAL(idx < opnds.size(), "out of range in MeRegPhiNode::GetOpnd");
    return opnds[idx];
  }

  void SetOpnd(size_t idx, RegMeExpr *opnd) {
    CHECK_FATAL(idx < opnds.size(), "out of range in MeRegPhiNode::SetOpnd");
    opnds[idx] = opnd;
  }

  void SetIsLive(bool isLiveVal) {
    isLive = isLiveVal;
  }

  bool GetIsLive() {
    return isLive;
  }

  void SetDefBB(BB *defBBVal) {
    defBB = defBBVal;
  }

  BB *GetDefBB() {
    return defBB;
  }

 private:
  RegMeExpr *lhs;
  MapleVector<RegMeExpr*> opnds;
  bool isLive;
  BB *defBB;  // the bb that defines this phi
};

class ConstMeExpr : public MeExpr {
 public:
  ConstMeExpr(int32 exprID, MIRConst *constValParam) : MeExpr(exprID, kMeOpConst), constVal(constValParam){};
  ~ConstMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  BaseNode *EmitExpr(SSATab*);
  bool GeZero() const;
  bool GtZero() const;
  bool IsZero() const;
  bool IsOne() const;
  int64 GetIntValue() const;

  MIRConst *GetConstVal() {
    return constVal;
  }

  uint32 GetHashIndex() const {
    MIRIntConst *intConst = dynamic_cast<MIRIntConst*>(constVal);
    if (intConst != nullptr) {
      return intConst->GetValue();
    }
    MIRFloatConst *floatConst = dynamic_cast<MIRFloatConst*>(constVal);
    if (floatConst != nullptr) {
      return floatConst->GetIntValue();
    }
    MIRDoubleConst *doubleConst = dynamic_cast<MIRDoubleConst*>(constVal);
    if (doubleConst != nullptr) {
      return doubleConst->GetIntValue();
    }
    MIRLblConst *lblConst = dynamic_cast<MIRLblConst*>(constVal);
    if (lblConst != nullptr) {
      return lblConst->GetValue();
    }
    ASSERT(false, "ComputeHash: const type not yet implemented");

    return 0;
  }

 private:
  MIRConst *constVal;
};

class ConststrMeExpr : public MeExpr {
 public:
  ConststrMeExpr(int32 exprID, UStrIdx idx) : MeExpr(exprID, kMeOpConststr), strIdx(idx){};
  ~ConststrMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  BaseNode *EmitExpr(SSATab*);

  UStrIdx &GetStrIdx() {
    return strIdx;
  }

  uint32 GetHashIndex() const {
    return strIdx.GetIdx() << 6;
  }

 private:
  UStrIdx strIdx;
};

class Conststr16MeExpr : public MeExpr {
 public:
  Conststr16MeExpr(int32 exprID, U16StrIdx idx) : MeExpr(exprID, kMeOpConststr16), strIdx(idx){};
  ~Conststr16MeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  BaseNode *EmitExpr(SSATab*);

  U16StrIdx &GetStrIdx() {
    return strIdx;
  }

  uint32 GetHashIndex() const {
    return strIdx.GetIdx() << 6;
  }

 private:
  U16StrIdx strIdx;
};

class SizeoftypeMeExpr : public MeExpr {
 public:
  SizeoftypeMeExpr(int32 exprid, TyIdx idx) : MeExpr(exprid, kMeOpSizeoftype), tyIdx(idx){};
  ~SizeoftypeMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  BaseNode *EmitExpr(SSATab*);

  TyIdx &GetTyIdx() {
    return tyIdx;
  }

  uint32 GetHashIndex() const {
    return tyIdx.GetIdx() << 5;
  }

 private:
  TyIdx tyIdx;
};

class FieldsDistMeExpr : public MeExpr {
 public:
  FieldsDistMeExpr(int32 exprid, TyIdx idx, FieldID f1, FieldID f2)
      : MeExpr(exprid, kMeOpFieldsDist), tyIdx(idx), fieldID1(f1), fieldID2(f2) {}

  ~FieldsDistMeExpr() = default;
  void Dump(IRMap*, int32 indent = 0) const;
  BaseNode *EmitExpr(SSATab*);

  TyIdx &GetTyIdx() {
    return tyIdx;
  }

  FieldID GetFieldID1() {
    return fieldID1;
  }

  FieldID GetFieldID2() {
    return fieldID2;
  }

  uint32 GetHashIndex() const {
    return (tyIdx.GetIdx() << 10) + (static_cast<uint32>(fieldID1) << 5) + fieldID2;
  }

 private:
  TyIdx tyIdx;
  FieldID fieldID1;
  FieldID fieldID2;
};

class AddrofMeExpr : public MeExpr {
 public:
  AddrofMeExpr(int32 exprid, OStIdx idx) : MeExpr(exprid, kMeOpAddrof), ostIdx(idx), fieldID(0) {}

  ~AddrofMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  bool IsUseSameSymbol(MeExpr*) const;
  BaseNode *EmitExpr(SSATab*);

  OStIdx &GetOstIdx() {
    return ostIdx;
  }

  OStIdx GetOstIdx() const {
    return ostIdx;
  }

  FieldID GetFieldID() {
    return fieldID;
  }

  void SetFieldID(FieldID fieldIDVal) {
    fieldID = fieldIDVal;
  }

  uint32 GetHashIndex() const {
    return ostIdx.idx << 4;
  }

 private:
  OStIdx ostIdx;  // the index in MEOptimizer: OriginalStTable;
  FieldID fieldID;
};

class AddroffuncMeExpr : public MeExpr {
 public:
  AddroffuncMeExpr(int32 exprid, PUIdx puid) : MeExpr(exprid, kMeOpAddroffunc), puIdx(puid) {}

  ~AddroffuncMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  BaseNode *EmitExpr(SSATab*);

  PUIdx GetPuIdx() {
    return puIdx;
  }

  uint32 GetHashIndex() const {
    return puIdx << 5;
  }

 private:
  PUIdx puIdx;
};

class GcmallocMeExpr : public MeExpr {
 public:
  GcmallocMeExpr(int32 exprid, TyIdx tyid) : MeExpr(exprid, kMeOpGcmalloc), tyIdx(tyid) {}

  ~GcmallocMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  BaseNode *EmitExpr(SSATab*);

  TyIdx &GetTyIdx() {
    return tyIdx;
  }

  TyIdx GetTyIdx() const {
    return tyIdx;
  }

  uint32 GetHashIndex() const {
    return tyIdx.GetIdx() << 4;
  }

 private:
  TyIdx tyIdx;
};

constexpr int kOpndNumOfOpMeExpr = 3;
class OpMeExpr : public MeExpr {
 public:
  explicit OpMeExpr(int32 exprID) : MeExpr(exprID, kMeOpOp), tyIdx(TyIdx(0)) {}

  OpMeExpr(const OpMeExpr &opmeexpr, int32 exprID)
      : MeExpr(exprID, kMeOpOp),
        opnds(opmeexpr.opnds),
        opndType(opmeexpr.opndType),
        bitsOffset(opmeexpr.bitsOffset),
        bitsSize(opmeexpr.bitsSize),
        tyIdx(opmeexpr.tyIdx),
        fieldID(opmeexpr.fieldID) {
    InitBase(opmeexpr.GetOp(), opmeexpr.GetPrimType(), opmeexpr.GetNumOpnds());
  }

  ~OpMeExpr() = default;

  OpMeExpr(const OpMeExpr &) = delete;
  OpMeExpr &operator=(const OpMeExpr &) = delete;

  bool IsIdentical(const OpMeExpr *meexpr);
  void Dump(IRMap*, int32 indent = 0) const;
  bool IsUseSameSymbol(MeExpr*) const;
  BaseNode *EmitExpr(SSATab*);
  MeExpr *GetOpnd(size_t i) const {
    CHECK_FATAL(i < kOpndNumOfOpMeExpr, "OpMeExpr cannot have more than 3 operands");
    return opnds[i];
  }

  void SetOpnd(uint32 idx, MeExpr *opndsVal) {
    CHECK_FATAL(idx < kOpndNumOfOpMeExpr, "out of range in  OpMeExpr::SetOpnd");
    opnds[idx] = opndsVal;
  }

  PrimType GetOpndType() {
    return opndType;
  }

  void SetOpndType(PrimType opndTypeVal) {
    opndType = opndTypeVal;
  }

  uint8 GetBitsOffSet() {
    return bitsOffset;
  }

  void SetBitsOffSet(uint8 bitsOffSetVal) {
    bitsOffset = bitsOffSetVal;
  }

  uint8 GetBitsSize() {
    return bitsSize;
  }

  void SetBitsSize(uint8 bitsSizeVal) {
    bitsSize = bitsSizeVal;
  }

  TyIdx &GetTyIdx() {
    return tyIdx;
  }

  TyIdx GetTyIdx() const {
    return tyIdx;
  }

  void SetTyIdx(TyIdx tyIdxVal) {
    tyIdx = tyIdxVal;
  }

  FieldID GetFieldID() const {
    return fieldID;
  }

  void SetFieldID(FieldID fieldIDVal) {
    fieldID = fieldIDVal;
  }

  uint32 GetHashIndex() const {
    uint32 hashIdx = static_cast<uint32>(GetOp());
    for (auto &opnd : opnds) {
      if (opnd == nullptr) {
        break;
      }

      hashIdx += static_cast<uint32>(opnd->GetExprID()) << 3;
    }
    return hashIdx;
  }

 private:
  std::array<MeExpr*, kOpndNumOfOpMeExpr> opnds = { nullptr }; // kid
  PrimType opndType = kPtyInvalid;                           // from type
  uint8 bitsOffset = 0;
  uint8 bitsSize = 0;
  TyIdx tyIdx;
  FieldID fieldID = 0;  // this is also used to store puIdx
};

class IvarMeExpr : public MeExpr {
 public:
  explicit IvarMeExpr(int32 exprid)
      : MeExpr(exprid, kMeOpIvar),
        defStmt(nullptr),
        base(nullptr),
        tyIdx(0),
        inferredTyIdx(0),
        fieldID(0),
        maybeNull(true),
        mu(nullptr) {
    SetNumOpnds(1);
  }

  IvarMeExpr(int32 exprid, const IvarMeExpr &ivarme)
      : MeExpr(exprid, kMeOpIvar),
        defStmt(ivarme.defStmt),
        base(ivarme.base),
        tyIdx(ivarme.tyIdx),
        fieldID(ivarme.fieldID),
        maybeNull(true),
        mu(nullptr) {
    InitBase(ivarme.GetOp(), ivarme.GetPrimType(), ivarme.GetNumOpnds());
    mu = ivarme.mu;
  }

  ~IvarMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  BaseNode *EmitExpr(SSATab*);
  bool IsVolatile(SSATab*) {
    return IsVolatile();
  }

  bool IsVolatile();
  bool IsFinal();
  bool IsRCWeak();
  bool IsUseSameSymbol(MeExpr*) const;
  MeExpr *GetOpnd(size_t idx) const {
    ASSERT(idx == 0, "IvarMeExpr can only have 1 operand");
    return base;
  }

  IassignMeStmt *GetDefStmt() const {
    return defStmt;
  }

  void SetDefStmt(IassignMeStmt *defStmtPara) {
    defStmt = defStmtPara;
  }

  const MeExpr *GetBase() const {
    return base;
  }

  MeExpr *GetBase() {
    return base;
  }

  void SetBase(MeExpr *value) {
    base = value;
  }

  TyIdx GetTyIdx() const {
    return tyIdx;
  }

  void SetTyIdx(TyIdx tyIdxVal) {
    tyIdx = tyIdxVal;
  }

  TyIdx GetInferredTyIdx() const {
    return inferredTyIdx;
  }

  void SetInferredTyidx(TyIdx inferredTyIdxVal) {
    inferredTyIdx = inferredTyIdxVal;
  }

  FieldID GetFieldID() const {
    return fieldID;
  }

  void SetFieldID(FieldID fieldIDVal) {
    fieldID = fieldIDVal;
  }


  bool GetMaybeNull() {
    return maybeNull;
  }

  void SetMaybeNull(bool maybeNullVal) {
    maybeNull = maybeNullVal;
  }

  VarMeExpr *GetMu() {
    return mu;
  }

  void SetMuVal(VarMeExpr *muVal) {
    mu = muVal;
  }

  uint32 GetHashIndex() const {
    return static_cast<uint32>(OP_iread) + fieldID + (static_cast<uint32>(base->GetExprID()) << 4);
  }

 private:
  IassignMeStmt *defStmt;
  MeExpr *base;
  TyIdx tyIdx;
  TyIdx inferredTyIdx;  // may be a subclass of above tyIdx
  FieldID fieldID;
  bool maybeNull;  // false if definitely not null
  VarMeExpr *mu;   // use of mu, only one for IvarMeExpr
};

// for array, intrinsicop and intrinsicopwithtype
class NaryMeExpr : public MeExpr {
 public:
  NaryMeExpr(MapleAllocator *alloc, int32 expid, TyIdx tidx, MIRIntrinsicID intrinid, bool bcheck)
      : MeExpr(expid, kMeOpNary), tyIdx(tidx), intrinsic(intrinid), opnds(alloc->Adapter()), boundCheck(bcheck) {}

  NaryMeExpr(MapleAllocator *alloc, int32 expid, NaryMeExpr &meexpr)
      : MeExpr(expid, kMeOpNary),
        tyIdx(meexpr.tyIdx),
        intrinsic(meexpr.intrinsic),
        opnds(alloc->Adapter()),
        boundCheck(meexpr.boundCheck) {
    InitBase(meexpr.GetOp(), meexpr.GetPrimType(), meexpr.GetNumOpnds());
    for (size_t i = 0; i < meexpr.opnds.size(); i++) {
      opnds.push_back(meexpr.opnds[i]);
    }
  }

  ~NaryMeExpr() = default;

  void Dump(IRMap*, int32 indent = 0) const;
  bool IsIdentical(NaryMeExpr*) const;
  bool IsUseSameSymbol(MeExpr*) const;
  BaseNode *EmitExpr(SSATab*);
  MeExpr *GetOpnd(size_t idx) const {
    ASSERT(idx < opnds.size(), "NaryMeExpr operand out of bounds");
    return opnds[idx];
  }

  const TyIdx &GetTyIdx() const {
    return tyIdx;
  }

  TyIdx &GetTyIdx() {
    return tyIdx;
  }

  MIRIntrinsicID GetIntrinsic() const {
    return intrinsic;
  }

  const MapleVector<MeExpr*> &GetOpnds() const {
    return opnds;
  }

  MapleVector<MeExpr*> &GetOpnds() {
    return opnds;
  }

  void SetOpnd(size_t idx, MeExpr *val) {
    opnds[idx] = val;
  }

  bool GetBoundCheck() {
    return boundCheck;
  }

  const bool GetBoundCheck() const {
    return boundCheck;
  }

  void SetBoundCheck(bool ch) {
    boundCheck = ch;
  }

  uint32 GetHashIndex() const {
    uint32 hashIdx = static_cast<uint32>(GetOp());
    for (uint32 i = 0; i < GetNumOpnds(); i++) {
      hashIdx += static_cast<uint32>(opnds[i]->GetExprID()) << 3;
    }
    return hashIdx;
  }

 private:
  TyIdx tyIdx;
  MIRIntrinsicID intrinsic;
  MapleVector<MeExpr*> opnds;
  bool boundCheck;
};

class MeStmt {
 public:
  explicit MeStmt(const StmtNode *sst) : isLive(true), bb(nullptr), prev(nullptr), next(nullptr) {
    ASSERT(sst != nullptr, "StmtNode nullptr check");
    op = sst->GetOpCode();
    srcPos = sst->GetSrcPos();
  }

  explicit MeStmt(Opcode op1) : op(op1), isLive(true), bb(nullptr), prev(nullptr), next(nullptr) {}

  virtual ~MeStmt() = default;

  bool GetIsLive() const {
    return isLive;
  }

  void SetIsLive(bool value) {
    isLive = value;
  }

  virtual void Dump(IRMap*) const;
  MeStmt *GetNextMeStmt();
  virtual size_t NumMeStmtOpnds() const {
    return 0;
  }

  virtual MeExpr *GetOpnd(size_t) const {
    return nullptr;
  }

  virtual void SetOpnd(uint32 idx, MeExpr *val) {}

  bool IsAssertBce() const {
    return op == OP_assertlt || op == OP_assertge;
  }

  bool IsReturn() const {
    return op == OP_gosub || op == OP_retsub || op == OP_throw || op == OP_return;
  }

  bool IsCondBr() const {
    return op == OP_brtrue || op == OP_brfalse;
  }

  bool IsAssign() const {
    return op == OP_dassign || op == OP_maydassign || op == OP_iassign || op == OP_regassign;
  }

  void SetCallReturn(MeExpr*);
  virtual MIRType *GetReturnType() const {
    return nullptr;
  }

  void EmitCallReturnVector(SSATab *ssatab, CallReturnVector *nrets);
  virtual MapleVector<MustDefMeNode> *GetMustDefList() {
    return nullptr;
  }

  const virtual MeExpr *GetAssignedLHS() const {
    return nullptr;
  }

  virtual MeExpr *GetAssignedLHS() {
    return nullptr;
  }

  virtual MapleMap<OStIdx, ChiMeNode*> *GetChiList() {
    return nullptr;
  }

  virtual MapleMap<OStIdx, VarMeExpr*> *GetMuList() {
    return nullptr;
  }

  void CopyBase(MeStmt *mestmt) {
    bb = mestmt->bb;
    srcPos = mestmt->srcPos;
    isLive = mestmt->isLive;
  }

  bool IsTheSameWorkcand(MeStmt*) const;
  virtual bool NeedDecref() const {
    return false;
  }

  virtual void EnableNeedDecref() {}

  virtual void DisableNeedDecref() {}

  virtual bool NeedIncref() const {
    return false;
  }

  virtual void EnableNeedIncref() {}

  virtual void DisableNeedIncref() {}

  virtual MeExpr *GetLHS() {
    return nullptr;
  }

  virtual MeExpr *GetRHS() {
    return nullptr;
  }

  virtual VarMeExpr *GetVarLHS() const {
    return nullptr;
  }

  virtual RegMeExpr *GetRegLHS() {
    return nullptr;
  }

  virtual MeExpr *GetLHSRef(SSATab *ssatab, bool excludelocalrefvar) {
    return nullptr;
  }

  virtual StmtNode *EmitStmt(SSATab *ssatab);
  void RemoveNode() {
    // remove this node from the double link list
    if (prev != nullptr) {
      prev->next = next;
    }
    if (next != nullptr) {
      next->prev = prev;
    }
  }

  void AddNext(MeStmt *node) {
    // add node to the next of this list
    node->next = next;
    node->prev = this;
    if (next != nullptr) {
      next->prev = node;
    }
    next = node;
  }

  void AddPrev(MeStmt *node) {
    // add node to the prev of this list
    node->prev = prev;
    node->next = this;
    if (prev != nullptr) {
      prev->next = node;
    }
    prev = node;
  }

  BB *GetBB() const {
    return bb;
  }

  void SetBB(BB *curBB) {
    bb = curBB;
  }

  const SrcPosition &GetSrcPosition() const {
    return srcPos;
  }

  void SetSrcPos(SrcPosition pos) {
    srcPos = pos;
  }

  void SetPrev(MeStmt *v) {
    prev = v;
  }

  void SetNext(MeStmt *n) {
    next = n;
  }

  MeStmt *GetPrev() {
    return prev;
  }

  MeStmt *GetNext() {
    return next;
  }

  const Opcode GetOp() const {
    return op;
  }

  void SetOp(Opcode currOp) {
    op = currOp;
  }

 private:
  Opcode op;
  bool isLive;
  BB *bb;
  SrcPosition srcPos;
  MeStmt *prev;
  MeStmt *next;
};

class ChiMeNode {
 public:
  explicit ChiMeNode(MeStmt *mestmt) : rhs(nullptr), lhs(nullptr), base(mestmt), isLive(true) {}

  ~ChiMeNode() = default;

  bool GetIsLive() const {
    return isLive;
  }

  void SetIsLive(bool value) {
    isLive = value;
  }

  VarMeExpr *GetRHS() const {
    return rhs;
  }

  void SetRHS(VarMeExpr *value) {
    rhs = value;
  }

  VarMeExpr *GetLHS() const {
    return lhs;
  }

  void SetLHS(VarMeExpr *value) {
    lhs = value;
  }

  void Dump(IRMap *irmap) const;

  MeStmt *GetBase() const {
    return base;
  }

  void SetBase(MeStmt *value) {
    base = value;
  }

 private:
  VarMeExpr *rhs;
  VarMeExpr *lhs;
  MeStmt *base;
  bool isLive;
};

class MustDefMeNode {
 public:
  MustDefMeNode(MeExpr *x, MeStmt *mestmt) : lhs(x), base(mestmt), isLive(true) {
    if (x->GetMeOp() == kMeOpReg) {
      RegMeExpr *reg = static_cast<RegMeExpr*>(x);
      reg->SetDefBy(kDefByMustDef);
      reg->SetDefMustDef(this);
    } else {
      CHECK(x->GetMeOp() == kMeOpVar, "unexpected opcode");
      VarMeExpr *var = static_cast<VarMeExpr*>(x);
      var->SetDefBy(kDefByMustDef);
      var->SetDefMustDef(this);
    }
  }

  const MeExpr *GetLHS() const {
    return lhs;
  }

  MeExpr *GetLHS() {
    return lhs;
  }

  void SetLHS(MeExpr *value) {
    lhs = value;
  }

  const MeStmt *GetBase() const {
    return base;
  }

  MeStmt *GetBase() {
    return base;
  }

  void SetBase(MeStmt *value) {
    base = value;
  }

  bool GetIsLive() const {
    return isLive;
  }

  void SetIsLive(bool value) {
    isLive = value;
  }

  MustDefMeNode(const MustDefMeNode &mustDef) {
    lhs = mustDef.lhs;
    base = mustDef.base;
    isLive = mustDef.isLive;
    UpdateLHS(lhs);
  }

  MustDefMeNode &operator=(const MustDefMeNode &mustDef) {
    if (&mustDef != this) {
      lhs = mustDef.lhs;
      base = mustDef.base;
      isLive = mustDef.isLive;
      UpdateLHS(lhs);
    }
    return *this;
  }

  void UpdateLHS(MeExpr *x) {
    lhs = x;
    if (x->GetMeOp() == kMeOpReg) {
      RegMeExpr *reg = static_cast<RegMeExpr*>(x);
      reg->SetDefBy(kDefByMustDef);
      reg->SetDefMustDef(this);
    } else {
      ASSERT(lhs->GetMeOp() == kMeOpVar, "unexpected opcode");
      VarMeExpr *var = static_cast<VarMeExpr*>(x);
      var->SetDefBy(kDefByMustDef);
      var->SetDefMustDef(this);
    }
  }

  ~MustDefMeNode() = default;

  void Dump(IRMap*) const;

 private:
  MeExpr *lhs;  // could be var or register, can we make this private?
  MeStmt *base;
  bool isLive;
};

class DassignMeStmt : public MeStmt {
 public:
  DassignMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : MeStmt(stt),
        rhs(nullptr),
        lhs(nullptr),
        chiList(std::less<OStIdx>(), alloc->Adapter()),
        propagated(false),
        needDecref(false),
        needIncref(false),
        wasMayDassign(false) {}

  explicit DassignMeStmt(MapleAllocator *alloc)
      : MeStmt(OP_dassign),
        rhs(nullptr),
        lhs(nullptr),
        chiList(std::less<OStIdx>(), alloc->Adapter()),
        propagated(false),
        needDecref(false),
        needIncref(false),
        wasMayDassign(false) {}

  DassignMeStmt(MapleAllocator *alloc, DassignMeStmt *dass)
      : MeStmt(dass->GetOp()),
        rhs(dass->rhs),
        lhs(dass->GetVarLHS()),
        chiList(std::less<OStIdx>(), alloc->Adapter()),
        propagated(false),
        needDecref(false),
        needIncref(false),
        wasMayDassign(false) {}

  ~DassignMeStmt() = default;

  size_t NumMeStmtOpnds() const {
    return 1;
  }

  MeExpr *GetOpnd(size_t) const {
    return rhs;
  }

  void SetOpnd(uint32 idx, MeExpr *val) {
    rhs = val;
  }

  MapleMap<OStIdx, ChiMeNode*> *GetChiList() {
    return &chiList;
  }

  void SetChiList(MapleMap<OStIdx, ChiMeNode*> &value) {
    chiList = value;
  }

  bool NeedDecref() const {
    return needDecref;
  }

  void EnableNeedDecref() {
    needDecref = true;
  }

  void DisableNeedDecref() {
    needDecref = false;
  }

  bool NeedIncref() const {
    return needIncref;
  }

  void EnableNeedIncref() {
    needIncref = true;
  }

  void DisableNeedIncref() {
    needIncref = false;
  }

  void SetNoNeedIncref() {
    needIncref = false;
  }

  bool Propagated() const {
    return propagated;
  }

  void SetPropagated(bool value) {
    propagated = value;
  }

  bool GetWasMayDassign() const {
    return wasMayDassign;
  }

  void SetWasMayDassign(bool value) {
    wasMayDassign = value;
  }

  void Dump(IRMap*) const;
  MeExpr *GetLHS() {
    return lhs;
  }

  void SetLHS(VarMeExpr *value) {
    lhs = value;
  }

  MeExpr *GetRHS() {
    return rhs;
  }

  void SetRHS(MeExpr *value) {
    rhs = value;
  }

  VarMeExpr *GetVarLHS() const {
    return lhs;
  }

  MeExpr *GetLHSRef(SSATab *ssatab, bool excludelocalrefvar);
  void UpdateLHS(VarMeExpr *var) {
    lhs = var;
    var->SetDefBy(kDefByStmt);
    var->SetDefStmt(this);
  }

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MeExpr *rhs;
  VarMeExpr *lhs;
  MapleMap<OStIdx, ChiMeNode*> chiList;
  bool propagated;     // the RHS has been propagated forward
  bool needDecref;     // to be determined by analyzerc phase
  bool needIncref;     // to be determined by analyzerc phase
  bool wasMayDassign;  // was converted back to dassign by may2dassign phase
};

class RegassignMeStmt : public MeStmt {
 public:
  explicit RegassignMeStmt(const StmtNode *stt) : MeStmt(stt), rhs(nullptr), lhs(nullptr), needIncref(false) {}

  RegassignMeStmt() : MeStmt(OP_regassign), rhs(nullptr), lhs(nullptr), needIncref(false) {}

  RegassignMeStmt(RegMeExpr *reg, MeExpr *val) : MeStmt(OP_regassign), rhs(val), lhs(reg), needIncref(false) {
    reg->SetDefBy(kDefByStmt);
    reg->SetDefStmt(this);
  }

  ~RegassignMeStmt() = default;

  size_t NumMeStmtOpnds() const {
    return 1;
  }

  MeExpr *GetOpnd(size_t) const {
    return rhs;
  }

  void SetOpnd(uint32 idx, MeExpr *val) {
    rhs = val;
  }

  void Dump(IRMap*) const;
  bool NeedIncref() const {
    return needIncref;
  }

  void EnableNeedIncref() {
    needIncref = true;
  }

  void DisableNeedIncref() {
    needIncref = false;
  }

  MeExpr *GetLHS() {
    return lhs;
  }

  MeExpr *GetRHS() {
    return rhs;
  }

  void SetRHS(MeExpr *value) {
    rhs = value;
  }

  RegMeExpr *GetRegLHS() {
    return lhs;
  }

  void SetLHS(RegMeExpr *value) {
    lhs = value;
  }

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MeExpr *rhs;
  RegMeExpr *lhs;
  bool needIncref;  // to be determined by analyzerc phase
};

class MaydassignMeStmt : public MeStmt {
 public:
  MaydassignMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : MeStmt(stt),
        rhs(nullptr),
        mayDSSym(nullptr),
        fieldID(0),
        chiList(std::less<OStIdx>(), alloc->Adapter()),
        needDecref(false),
        needIncref(false) {}

  ~MaydassignMeStmt() = default;

  size_t NumMeStmtOpnds() const {
    return 1;
  }

  MeExpr *GetOpnd(size_t) const {
    return rhs;
  }

  void SetOpnd(uint32 idx, MeExpr *val) {
    rhs = val;
  }

  MapleMap<OStIdx, ChiMeNode*> *GetChiList() {
    return &chiList;
  }

  void SetChiList(MapleMap<OStIdx, ChiMeNode*> &value) {
    chiList = value;
  }

  bool NeedDecref() const {
    return needDecref;
  }

  void EnableNeedDecref() {
    needDecref = true;
  }

  void DisableNeedDecref() {
    needDecref = false;
  }

  bool NeedIncref() const {
    return needIncref;
  }

  void EnableNeedIncref() {
    needIncref = true;
  }

  void DisableNeedIncref() {
    needIncref = false;
  }

  OriginalSt *GetMayDassignSym() const {
    return mayDSSym;
  }

  void SetMayDassignSym(OriginalSt *sym) {
    mayDSSym = sym;
  }

  FieldID GetFieldID() const {
    return fieldID;
  }

  void SetFieldID(FieldID fieldIDVal) {
    fieldID = fieldIDVal;
  }

  void Dump(IRMap*) const;
  MeExpr *GetLHS() {
    return chiList.begin()->second->GetLHS();
  }

  MeExpr *GetRHS() {
    return rhs;
  }

  void SetRHS(MeExpr *value) {
    rhs = value;
  }

  VarMeExpr *GetVarLHS() const {
    return chiList.begin()->second->GetLHS();
  }

  MeExpr *GetLHSRef(SSATab *ssatab, bool excludelocalrefvar);
  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MeExpr *rhs;
  OriginalSt *mayDSSym;
  FieldID fieldID;
  MapleMap<OStIdx, ChiMeNode*> chiList;
  bool needDecref;  // to be determined by analyzerc phase
  bool needIncref;  // to be determined by analyzerc phase
};

class IassignMeStmt : public MeStmt {
 public:
  IassignMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : MeStmt(stt),
        tyIdx(0),
        lhsVar(nullptr),
        rhs(nullptr),
        chiList(std::less<OStIdx>(), alloc->Adapter()),
        needDecref(false),
        needIncref(false) {}

  IassignMeStmt(MapleAllocator *alloc, const IassignMeStmt &iss)
      : MeStmt(iss),
        tyIdx(iss.tyIdx),
        lhsVar(iss.lhsVar),
        rhs(iss.rhs),
        chiList(iss.chiList),
        needDecref(false),
        needIncref(false) {}

  IassignMeStmt(MapleAllocator *alloc, TyIdx tidx, IvarMeExpr *l, MeExpr *r, const MapleMap<OStIdx, ChiMeNode*> *clist)
      : MeStmt(OP_iassign), tyIdx(tidx), lhsVar(l), rhs(r), chiList(*clist), needDecref(false), needIncref(false) {
    l->SetDefStmt(this);
  }

  ~IassignMeStmt() = default;

  TyIdx GetTyIdx() const {
    return tyIdx;
  }

  void SetTyIdx(TyIdx idx) {
    tyIdx = idx;
  }

  size_t NumMeStmtOpnds() const {
    return 2;
  }

  MeExpr *GetOpnd(size_t idx) const {
    return idx == 0 ? lhsVar->GetBase() : rhs;
  }

  void SetOpnd(uint32 idx, MeExpr *val) {
    if (idx == 0) {
      lhsVar->SetBase(val);
    } else {
      rhs = val;
    }
  }

  MapleMap<OStIdx, ChiMeNode*> *GetChiList() {
    return &chiList;
  }

  void SetChiList(MapleMap<OStIdx, ChiMeNode*> &value) {
    chiList = value;
  }

  MeExpr *GetLHSRef(SSATab *ssatab, bool excludelocalrefvar);
  bool NeedDecref() const {
    return needDecref;
  }

  void EnableNeedDecref() {
    needDecref = true;
  }

  void DisableNeedDecref() {
    needDecref = false;
  }

  bool NeedIncref() const {
    return needIncref;
  }

  void EnableNeedIncref() {
    needIncref = true;
  }

  void DisableNeedIncref() {
    needIncref = false;
  }

  void Dump(IRMap*) const;
  MeExpr *GetLHS() {
    return lhsVar;
  }

  MeExpr *GetRHS() {
    return rhs;
  }

  void SetRHS(MeExpr *val) {
    rhs = val;
  }

  IvarMeExpr *GetLHSVal() const {
    return lhsVar;
  }

  void SetLHSVal(IvarMeExpr *val) {
    lhsVar = val;
  }

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  TyIdx tyIdx;
  IvarMeExpr *lhsVar;
  MeExpr *rhs;
  MapleMap<OStIdx, ChiMeNode*> chiList;
  bool needDecref;  // to be determined by analyzerc phase
  bool needIncref;  // to be determined by analyzerc phase
};

class NaryMeStmt : public MeStmt {
 public:
  NaryMeStmt(MapleAllocator *alloc, const StmtNode *stt) : MeStmt(stt), opnds(alloc->Adapter()) {}

  NaryMeStmt(MapleAllocator *alloc, Opcode op) : MeStmt(op), opnds(alloc->Adapter()) {}

  NaryMeStmt(MapleAllocator *alloc, NaryMeStmt *nstmt) : MeStmt(nstmt->GetOp()), opnds(alloc->Adapter()) {
    for (MeExpr *o : nstmt->opnds) {
      opnds.push_back(o);
    }
  }

  virtual ~NaryMeStmt() = default;

  size_t NumMeStmtOpnds() const {
    return opnds.size();
  }

  MeExpr *GetOpnd(size_t idx) const {
    ASSERT(idx < opnds.size(), "out of range in NaryMeStmt::GetOpnd");
    return opnds.at(idx);
  }

  void SetOpnd(uint32 idx, MeExpr *val) {
    opnds[idx] = val;
  }

  MapleVector<MeExpr*> &GetOpnds() {
    return opnds;
  }

  void SetOpnds(MapleVector<MeExpr*> &opndsVal) {
    opnds = opndsVal;
  }

  void DumpOpnds(IRMap*) const;
  void Dump(IRMap*) const;
  virtual MapleMap<OStIdx, VarMeExpr*> *GetMuList() {
    return nullptr;
  }

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MapleVector<MeExpr*> opnds;
};

class MuChiMePart {
 public:
  explicit MuChiMePart(MapleAllocator *alloc)
      : muList(std::less<OStIdx>(), alloc->Adapter()), chiList(std::less<OStIdx>(), alloc->Adapter()) {}

  virtual MapleMap<OStIdx, ChiMeNode*> *GetChiList() {
    return &chiList;
  }

  void SetChiList(MapleMap<OStIdx, ChiMeNode*> &value) {
    chiList = value;
  }

  virtual ~MuChiMePart() = default;

 protected:
  MapleMap<OStIdx, VarMeExpr*> muList;
  MapleMap<OStIdx, ChiMeNode*> chiList;
};

class AssignedPart {
 public:
  explicit AssignedPart(MapleAllocator *alloc) : mustDefList(alloc->Adapter()), needDecref(false), needIncref(false) {}

  explicit AssignedPart(const MapleVector<MustDefMeNode> &mustdefList)
      : mustDefList(mustdefList), needDecref(false), needIncref(false) {}

  virtual ~AssignedPart() = default;

  void DumpAssignedPart(IRMap *irmap) const;
  VarMeExpr *GetAssignedPartLHSRef(SSATab *ssatab, bool excludelocalrefvar);

 protected:
  MapleVector<MustDefMeNode> mustDefList;
  bool needDecref;  // to be determined by analyzerc phase
  bool needIncref;  // to be determined by analyzerc phase
};

class CallMeStmt : public NaryMeStmt, public MuChiMePart, public AssignedPart {
 public:
  CallMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : NaryMeStmt(alloc, stt),
        MuChiMePart(alloc),
        AssignedPart(alloc),
        puIdx(static_cast<const CallNode*>(stt)->GetPUIdx()),
        stmtID(stt->GetStmtID()),
        tyIdx(static_cast<const CallNode*>(stt)->GetTyIdx()) {}

  CallMeStmt(MapleAllocator *alloc, Opcode op)
      : NaryMeStmt(alloc, op), MuChiMePart(alloc), AssignedPart(alloc), puIdx(0), stmtID(0) {}

  CallMeStmt(MapleAllocator *alloc, CallMeStmt *cstmt)
      : NaryMeStmt(alloc, cstmt),
        MuChiMePart(alloc),
        AssignedPart(cstmt->mustDefList),
        puIdx(cstmt->GetPUIdx()),
        stmtID(0) {}

  virtual ~CallMeStmt() = default;

  PUIdx GetPUIdx() const {
    return puIdx;
  }

  void SetPUIdx(PUIdx idx) {
    puIdx = idx;
  }

  uint32 GetStmtID() const {
    return stmtID;
  }

  void Dump(IRMap*) const;
  MapleMap<OStIdx, VarMeExpr*> *GetMuList() {
    return &muList;
  }

  MapleMap<OStIdx, ChiMeNode*> *GetChiList() {
    return &chiList;
  }

  MapleVector<MustDefMeNode> *GetMustDefList() {
    return &mustDefList;
  }

  size_t MustDefListSize() const {
    return mustDefList.size();
  }

  const MeExpr *GetAssignedLHS() const {
    return mustDefList.empty() ? nullptr : mustDefList.front().GetLHS();
  }

  MeExpr *GetAssignedLHS() {
    return mustDefList.empty() ? nullptr : mustDefList.front().GetLHS();
  }

  MeExpr *GetLHSRef(SSATab *ssatab, bool excludelocalrefvar) {
    return GetAssignedPartLHSRef(ssatab, excludelocalrefvar);
  }

  bool NeedDecref() const {
    return needDecref;
  }

  void EnableNeedDecref() {
    needDecref = true;
  }

  void DisableNeedDecref() {
    needDecref = false;
  }

  bool NeedIncref() const {
    return needIncref;
  }

  void EnableNeedIncref() {
    needIncref = true;
  }

  void DisableNeedIncref() {
    needIncref = false;
  }

  MIRType *GetReturnType() const {
    MIRFunction *callee = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(puIdx);
    return callee->GetReturnType();
  }

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  PUIdx puIdx;
  // Used in trim call graph
  uint32 stmtID;
  TyIdx tyIdx;
};

class IcallMeStmt : public NaryMeStmt, public MuChiMePart, public AssignedPart {
 public:
  IcallMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : NaryMeStmt(alloc, stt),
        MuChiMePart(alloc),
        AssignedPart(alloc),
        retTyIdx(static_cast<const IcallNode*>(stt)->GetRetTyIdx()),
        stmtID(stt->GetStmtID()) {}

  IcallMeStmt(MapleAllocator *alloc, Opcode op)
      : NaryMeStmt(alloc, op), MuChiMePart(alloc), AssignedPart(alloc), retTyIdx(0), stmtID(0) {}

  IcallMeStmt(MapleAllocator *alloc, IcallMeStmt *cstmt)
      : NaryMeStmt(alloc, cstmt),
        MuChiMePart(alloc),
        AssignedPart(cstmt->mustDefList),
        retTyIdx(cstmt->retTyIdx),
        stmtID(cstmt->stmtID) {}

  virtual ~IcallMeStmt() = default;

  void Dump(IRMap*) const;
  MapleMap<OStIdx, VarMeExpr*> *GetMuList() {
    return &muList;
  }

  MapleMap<OStIdx, ChiMeNode*> *GetChiList() {
    return &chiList;
  }

  MapleVector<MustDefMeNode> *GetMustDefList() {
    return &mustDefList;
  }

  const MeExpr *GetAssignedLHS() const {
    return mustDefList.empty() ? nullptr : mustDefList.front().GetLHS();
  }

  MeExpr *GetLHSRef(SSATab *ssatab, bool excludelocalrefvar) {
    return GetAssignedPartLHSRef(ssatab, excludelocalrefvar);
  }

  bool NeedDecref() const {
    return needDecref;
  }

  void EnableNeedDecref() {
    needDecref = true;
  }

  void DisableNeedDecref() {
    needDecref = false;
  }

  bool NeedIncref() const {
    return needIncref;
  }

  void EnableNeedIncref() {
    needIncref = true;
  }

  void DisableNeedIncref() {
    needIncref = false;
  }

  MIRType *GetReturnType() const {
    return GlobalTables::GetTypeTable().GetTypeFromTyIdx(retTyIdx);
  }

  StmtNode *EmitStmt(SSATab *ssatab);

  TyIdx GetRetTyIdx() const {
    return retTyIdx;
  }

  void SetRetTyIdx(TyIdx idx) {
    retTyIdx = idx;
  }

 private:
  // return type for callee
  TyIdx retTyIdx;
  // Used in trim call graph
  uint32 stmtID;
};

class IntrinsiccallMeStmt : public NaryMeStmt, public MuChiMePart, public AssignedPart {
 public:
  IntrinsiccallMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : NaryMeStmt(alloc, stt),
        MuChiMePart(alloc),
        AssignedPart(alloc),
        intrinsic(static_cast<const IntrinsiccallNode*>(stt)->GetIntrinsic()),
        tyIdx(static_cast<const IntrinsiccallNode*>(stt)->GetTyIdx()),
        retPType(stt->GetPrimType()) {}

  IntrinsiccallMeStmt(MapleAllocator *alloc, Opcode op, MIRIntrinsicID id, TyIdx tyid = TyIdx())
      : NaryMeStmt(alloc, op),
        MuChiMePart(alloc),
        AssignedPart(alloc),
        intrinsic(id),
        tyIdx(tyid),
        retPType(kPtyInvalid) {}

  IntrinsiccallMeStmt(MapleAllocator *alloc, IntrinsiccallMeStmt *intrn)
      : NaryMeStmt(alloc, intrn),
        MuChiMePart(alloc),
        AssignedPart(intrn->mustDefList),
        intrinsic(intrn->GetIntrinsic()),
        tyIdx(intrn->tyIdx),
        retPType(intrn->retPType) {}

  virtual ~IntrinsiccallMeStmt() = default;

  void Dump(IRMap*) const;
  MapleMap<OStIdx, VarMeExpr*> *GetMuList() {
    return &muList;
  }

  MapleMap<OStIdx, ChiMeNode*> *GetChiList() {
    return &chiList;
  }

  MIRType *GetReturnType() const {
    if (!mustDefList.empty()) {
      return GlobalTables::GetTypeTable().GetPrimType(mustDefList.front().GetLHS()->GetPrimType());
    }
    return GlobalTables::GetTypeTable().GetPrimType(retPType);
  }

  MapleVector<MustDefMeNode> *GetMustDefList() {
    return &mustDefList;
  }

  MustDefMeNode &GetMustDefListItem(int i) {
    return mustDefList[i];
  }

  const MeExpr *GetAssignedLHS() const {
    return mustDefList.empty() ? nullptr : mustDefList.front().GetLHS();
  }

  MeExpr *GetAssignedLHS() {
    return mustDefList.empty() ? nullptr : mustDefList.front().GetLHS();
  }

  MeExpr *GetLHSRef(SSATab *ssatab, bool excludelocalrefvar) {
    return GetAssignedPartLHSRef(ssatab, excludelocalrefvar);
  }

  bool NeedDecref() const {
    return needDecref;
  }

  void EnableNeedDecref() {
    needDecref = true;
  }

  void DisableNeedDecref() {
    needDecref = false;
  }

  bool NeedIncref() const {
    return needIncref;
  }

  void EnableNeedIncref() {
    needIncref = true;
  }

  void DisableNeedIncref() {
    needIncref = false;
  }

  StmtNode *EmitStmt(SSATab *ssatab);

  MIRIntrinsicID GetIntrinsic() const {
    return intrinsic;
  }

  void SetIntrinsic(MIRIntrinsicID id) {
    intrinsic = id;
  }

  TyIdx GetTyIdx() const {
    return tyIdx;
  }

 private:
  MIRIntrinsicID intrinsic;
  TyIdx tyIdx;
  // Used to store return value type
  PrimType retPType;
};

class RetMeStmt : public NaryMeStmt {
 public:
  RetMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : NaryMeStmt(alloc, stt), muList(std::less<OStIdx>(), alloc->Adapter()) {}

  ~RetMeStmt() = default;

  void Dump(IRMap*) const;
  MapleMap<OStIdx, VarMeExpr*> *GetMuList() {
    return &muList;
  }

 private:
  MapleMap<OStIdx, VarMeExpr*> muList;
};

// eval, free, decref, incref, decrefreset, assertnonnull
class UnaryMeStmt : public MeStmt {
 public:
  explicit UnaryMeStmt(const StmtNode *stt) : MeStmt(stt), opnd(nullptr), notNeedLock(false), decrefBeforeExit(false) {}

  explicit UnaryMeStmt(Opcode o) : MeStmt(o), opnd(nullptr), notNeedLock(false), decrefBeforeExit(false) {}

  explicit UnaryMeStmt(UnaryMeStmt *umestmt)
      : MeStmt(umestmt->GetOp()),
        opnd(umestmt->opnd),
        notNeedLock(umestmt->GetNotNeedLock()),
        decrefBeforeExit(false) {}

  virtual ~UnaryMeStmt() = default;

  size_t NumMeStmtOpnds() const {
    return 1;
  }

  MeExpr *GetOpnd(size_t idx) const {
    return opnd;
  }

  void SetOpnd(uint32 idx, MeExpr *val) {
    opnd = val;
  }

  MeExpr *GetOpnd() const {
    return opnd;
  }

  void SetMeStmtOpndValue(MeExpr *val) {
    opnd = val;
  }

  bool GetNotNeedLock() const {
    return notNeedLock;
  }

  void SetNotNeedLock(bool currNotNeedLock) {
    notNeedLock = currNotNeedLock;
  }

  bool GetDecrefBeforeExit() const {
    return decrefBeforeExit;
  }

  void Dump(IRMap*) const;

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MeExpr *opnd;
  bool notNeedLock;
  bool decrefBeforeExit;  // true if decref is inserted due to anticipated function exit
};

class GotoMeStmt : public MeStmt {
 public:
  explicit GotoMeStmt(const StmtNode *stt) : MeStmt(stt), offset(static_cast<const GotoNode*>(stt)->GetOffset()) {}

  ~GotoMeStmt() = default;

  uint32 GetOffset() const {
    return offset;
  }

  void SetOffset(uint32 o) {
    offset = o;
  }

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  uint32 offset;  // the label
};

class CondGotoMeStmt : public UnaryMeStmt {
 public:
  explicit CondGotoMeStmt(const StmtNode *stt)
      : UnaryMeStmt(stt), offset(static_cast<const CondGotoNode*>(stt)->GetOffset()) {}

  ~CondGotoMeStmt() = default;

  uint32 GetOffset() {
    return offset;
  }

  void SetOffset(uint32 currOffset) {
    offset = currOffset;
  }

  void Dump(IRMap*) const;
  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  uint32 offset;  // the label
};

class JsTryMeStmt : public MeStmt {
 public:
  explicit JsTryMeStmt(const StmtNode *stt)
      : MeStmt(stt),
        catchOffset(static_cast<const JsTryNode*>(stt)->GetCatchOffset()),
        finallyOffset(static_cast<const JsTryNode*>(stt)->GetFinallyOffset()) {}

  ~JsTryMeStmt() = default;

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  uint16 catchOffset;
  uint16 finallyOffset;
};

class TryMeStmt : public MeStmt {
 public:
  TryMeStmt(MapleAllocator *alloc, const StmtNode *stt) : MeStmt(stt), offsets(alloc->Adapter()) {}

  ~TryMeStmt() = default;

  void OffsetsPushBack(LabelIdx curr) {
    offsets.push_back(curr);
  }

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MapleVector<LabelIdx> offsets;
};

class CatchMeStmt : public MeStmt {
 public:
  CatchMeStmt(MapleAllocator *alloc, StmtNode *stt) : MeStmt(stt), exceptionTyIdxVec(alloc->Adapter()) {
    for (auto it : static_cast<CatchNode*>(stt)->GetExceptionTyIdxVec()) {
      exceptionTyIdxVec.push_back(it);
    }
  }

  ~CatchMeStmt() = default;

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MapleVector<TyIdx> exceptionTyIdxVec;
};

class SwitchMeStmt : public UnaryMeStmt {
 public:
  SwitchMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : UnaryMeStmt(stt),
        defaultLabel(static_cast<const SwitchNode*>(stt)->GetDefaultLabel()),
        switchTable(alloc->Adapter()) {
    switchTable = static_cast<const SwitchNode*>(stt)->GetSwitchTable();
  }

  ~SwitchMeStmt() = default;

  LabelIdx GetDefaultLabel() const {
    return defaultLabel;
  }

  void SetDefaultLabel(LabelIdx curr) {
    defaultLabel = curr;
  }

  CaseVector &GetSwitchTable() {
    return switchTable;
  }

  void Dump(IRMap*) const;
  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  LabelIdx defaultLabel;
  CaseVector switchTable;
};

class CommentMeStmt : public MeStmt {
 public:
  CommentMeStmt(MapleAllocator *alloc, const StmtNode *stt) : MeStmt(stt), comment(alloc->GetMemPool()) {
    comment = static_cast<const CommentNode*>(stt)->GetComment();
  }

  ~CommentMeStmt() = default;

  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MapleString comment;
};

class WithMuMeStmt : public MeStmt {
 public:
  WithMuMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : MeStmt(stt), muList(std::less<OStIdx>(), alloc->Adapter()) {}

  virtual ~WithMuMeStmt() = default;

  MapleMap<OStIdx, VarMeExpr*> *GetMuList() {
    return &muList;
  }

  const MapleMap<OStIdx, VarMeExpr*> *GetMuList() const {
    return &muList;
  }

 private:
  MapleMap<OStIdx, VarMeExpr*> muList;
};

class GosubMeStmt : public WithMuMeStmt {
 public:
  GosubMeStmt(MapleAllocator *alloc, const StmtNode *stt)
      : WithMuMeStmt(alloc, stt), offset(static_cast<const GotoNode*>(stt)->GetOffset()) {}

  ~GosubMeStmt() = default;

  void Dump(IRMap*) const;
  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  uint32 offset;  // the label
};

class ThrowMeStmt : public WithMuMeStmt {
 public:
  ThrowMeStmt(MapleAllocator *alloc, const StmtNode *stt) : WithMuMeStmt(alloc, stt), opnd(nullptr) {}

  ~ThrowMeStmt() = default;

  size_t NumMeStmtOpnds() const {
    return 1;
  }

  MeExpr *GetOpnd(size_t idx) const {
    return opnd;
  }

  void SetOpnd(uint32 idx, MeExpr *val) {
    opnd = val;
  }

  MeExpr *GetOpnd() const {
    return opnd;
  }

  void SetMeStmtOpndValue(MeExpr *val) {
    opnd = val;
  }

  void Dump(IRMap*) const;
  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MeExpr *opnd;
};

class SyncMeStmt : public NaryMeStmt, public MuChiMePart {
 public:
  SyncMeStmt(MapleAllocator *alloc, const StmtNode *stt) : NaryMeStmt(alloc, stt), MuChiMePart(alloc) {}

  ~SyncMeStmt() = default;

  void Dump(IRMap*) const;
  MapleMap<OStIdx, VarMeExpr*> *GetMuList() {
    return &muList;
  }

  MapleMap<OStIdx, ChiMeNode*> *GetChiList() {
    return &chiList;
  }
};

// assert ge or lt for boundary check
class AssertMeStmt : public MeStmt {
 public:
  explicit AssertMeStmt(const StmtNode *stt) : MeStmt(stt) {
    Opcode op = stt->GetOpCode();
    CHECK(op == OP_assertge || op == OP_assertlt, "runtime check error");
  }

  explicit AssertMeStmt(Opcode op1) : MeStmt(op1) {
    Opcode op = op1;
    CHECK(op == OP_assertge || op == OP_assertlt, "runtime check error");
  }

  AssertMeStmt(const AssertMeStmt &assmestmt) : MeStmt(assmestmt.GetOp()) {
    SetOp(assmestmt.GetOp());
    opnds[0] = assmestmt.opnds[0];
    opnds[1] = assmestmt.opnds[1];
  }

  AssertMeStmt(MeExpr *arrexpr, MeExpr *indxexpr, bool ilt) : MeStmt(ilt ? OP_assertlt : OP_assertge) {
    opnds[0] = arrexpr;
    opnds[1] = indxexpr;
  }

  ~AssertMeStmt() = default;

  bool HasSameVersion(const AssertMeStmt *assmestmt) const {
    ASSERT(GetOp() == assmestmt->GetOp(), "runtime check error");
    return (opnds[0] == assmestmt->opnds[0] && opnds[1] == assmestmt->opnds[1]);
  }

  MeExpr *GetIndexExpr() const {
    return opnds[1];
  }

  MeExpr *GetArrayExpr() const {
    return opnds[0];
  }

  void SetOpnd(uint32 i, MeExpr *opnd) {
    CHECK_FATAL(i < 2, "AssertMeStmt has two opnds");
    opnds[i] = opnd;
  }

  MeExpr *GetOpnd(size_t i) const {
    CHECK_FATAL(i < 2, "AssertMeStmt has two opnds");
    return opnds[i];
  }

  void Dump(IRMap*) const;
  StmtNode *EmitStmt(SSATab *ssatab);

 private:
  MeExpr *opnds[2];
  AssertMeStmt &operator=(const AssertMeStmt &assmestmt) {
    if (&assmestmt == this) {
      return *this;
    }
    SetOp(assmestmt.GetOp());
    opnds[0] = assmestmt.opnds[0];
    opnds[1] = assmestmt.opnds[1];
    return *this;
  }
};

MapleMap<OStIdx, ChiMeNode*> *GenericGetChiListFromVarMeExpr(VarMeExpr *expr);
void DumpMuList(IRMap *irmap, const MapleMap<OStIdx, VarMeExpr*> &mulist, int32 indent);
void DumpChiList(IRMap *irmap, const MapleMap<OStIdx, ChiMeNode*> &chilist);
class DumpOptions {
 public:

  static bool GetSimpleDump() {
    return simpleDump;
  }

  static int GetDumpVsyNum() {
    return dumpVsymNum;
  }

 private:
  static bool simpleDump;
  static int dumpVsymNum;
};

}  // namespace maple
#endif  // MAPLE_ME_INCLUDE_ME_IR_H
