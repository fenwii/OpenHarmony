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
#ifndef MAPLE_IR_INCLUDE_MIR_CONST_H
#define MAPLE_IR_INCLUDE_MIR_CONST_H
#include <math.h>
#include "mir_type.h"

namespace maple {
class MIRConst;
using MIRConstPtr = MIRConst*;
#if MIR_FEATURE_FULL
class MIRSymbol;
enum MIRConstKind {
  kConstInvalid,
  kConstInt,
  kConstAddrof,
  kConstAddrofFunc,
  kConstLblConst,
  kConstStrConst,
  kConstStr16Const,
  kConstFloatConst,
  kConstDoubleConst,
  kConstFloat128Const,
  kConstAggConst,
  kConstStConst
};

class MIRConst {
 public:
  explicit MIRConst(MIRType *type, uint32 fieldID = 0) : kind(kConstInvalid), type(type), fieldID(fieldID) {}

  virtual ~MIRConst() {}

  virtual void Dump() const;

  uint32 GetFieldId() const {
    return fieldID;
  }

  void SetFieldID(uint32 fieldIdx) {
    fieldID = fieldIdx;
  }

  virtual bool IsZero() {
    return false;
  }

  virtual bool IsOne() {
    return false;
  }

  virtual bool IsMagicNum() {
    return false;
  }

  // NO OP
  virtual void Neg() {}

  virtual bool operator==(MIRConst &rhs) const {
    return &rhs == this;
  }

  MIRConstKind GetKind() {
    return kind;
  }

  const MIRConstKind GetKind() const {
    return kind;
  }

  void SetKind(MIRConstKind ind) {
    kind = ind;
  }

  MIRType *GetType() {
    return type;
  }

  const MIRType *GetType() const {
    return type;
  }

 private:
  MIRConstKind kind;
  MIRType *type;
  uint32 fieldID;
};

class MIRIntConst : public MIRConst {
 public:
  using value_type = int64;
  MIRIntConst(int64 val, MIRType *type, uint32 fieldID = 0) : MIRConst(type, fieldID), value(val) {
    if (!IsPrimitiveDynType(GetType()->GetPrimType())) {
      Trunc(GetPrimTypeBitSize(GetType()->GetPrimType()));
    }
    SetKind(kConstInt);
  }

  ~MIRIntConst() {}

  uint8 GetBitWidth() const {
    if (value == 0) {
      return 1;
    }
    uint8 width = 0;
    uint64 tmp = value < 0 ? -(value + 1) : value;
    while (tmp != 0) {
      width++;
      tmp = tmp >> 1u;
    }
    return width;
  }

  void Trunc(uint8 width) {
    int32 shiftBitNum = 64u - width;
    if (shiftBitNum < 0) {
      CHECK_FATAL(false, "shiftBitNum should not be less than zero");
    }
    uint32 unsignShiftBitNum = static_cast<uint32>(shiftBitNum);
    if (IsSignedInteger(GetType()->GetPrimType())) {
      value = (value << unsignShiftBitNum) >> unsignShiftBitNum;
    } else {
      value = ((static_cast<uint64>(value)) << unsignShiftBitNum) >> unsignShiftBitNum;
    }
  }

  int64 GetValueUnderType() const {
    uint32 bitSize = GetPrimTypeBitSize(GetNonDynType(GetType()->GetPrimType()));
    int32 shiftBitNum = 64u - bitSize;
    if (shiftBitNum < 0) {
      CHECK_FATAL(false, "shiftBitNum should not be less than zero");
    }
    if (IsSignedInteger(GetType()->GetPrimType())) {
      return static_cast<int64>(((value) << shiftBitNum) >> shiftBitNum);
    } else {
      uint64 unsignedVal = static_cast<uint64>(value);
      return static_cast<int64>((unsignedVal << shiftBitNum) >> shiftBitNum);
    }
  }

  void Dump() const;
  bool IsZero() {
    return value == 0 && IsPrimitiveInteger(GetType()->GetPrimType());
  }

  bool IsOne() {
    return value == 1 && IsPrimitiveInteger(GetType()->GetPrimType());
  };
  bool IsMagicNum() {
    constexpr int64 kMagicNum = 51;
    return value == kMagicNum && IsPrimitiveInteger(GetType()->GetPrimType());
  };
  bool IsAllBitsOne() {
    return value == -1 && IsPrimitiveInteger(GetType()->GetPrimType());
  };
  void Neg() {
    value = -value;
  }

  int64 GetValue() const {
    return value;
  }

  void SetValue(int64 val) {
    value = val;
  }

  bool operator==(MIRConst &rhs) const;

 private:
  int64 value;
};

class MIRAddrofConst : public MIRConst {
 public:
  MIRAddrofConst(StIdx sy, FieldID fi, MIRType *ty) : MIRConst(ty), stIdx(sy), fldID(fi) {
    SetKind(kConstAddrof);
  }

  ~MIRAddrofConst() {}

  const StIdx &GetSymbolIndex() const {
    return stIdx;
  }

  FieldID GetFieldID() const {
    return fldID;
  }

  /* virtual */
  void Dump() const;
  /* virtual */
  bool operator==(MIRConst &rhs) const;

 private:
  StIdx stIdx;
  FieldID fldID;
};

class MIRAddroffuncConst : public MIRConst {
 public:
  MIRAddroffuncConst(PUIdx idx, MIRType *ty, uint32 fieldID = 0) : MIRConst(ty, fieldID), puIdx(idx) {
    SetKind(kConstAddrofFunc);
  }

  ~MIRAddroffuncConst() {}

  PUIdx GetValue() const {
    return puIdx;
  }

  /* virtual */
  void Dump() const;
  /* virtual */
  bool operator==(MIRConst &rhs) const;

 private:
  PUIdx puIdx;
};

class MIRLblConst : public MIRConst {
 public:
  MIRLblConst(LabelIdx val, MIRType *type) : MIRConst(type), value(val) {
    SetKind(kConstLblConst);
  }

  ~MIRLblConst() {}

  bool operator==(MIRConst &rhs) const;

  LabelIdx GetValue() const {
    return value;
  }

 private:
  LabelIdx value;
};

class MIRStrConst : public MIRConst {
 public:
  MIRStrConst(UStrIdx val, MIRType *type, uint32 fieldID = 0) : MIRConst(type, fieldID), value(val) {
    SetKind(kConstStrConst);
  }

  MIRStrConst(const std::string &str, MIRType *type);

  ~MIRStrConst() {}

  void Dump() const;
  bool operator==(MIRConst &rhs) const;
  UStrIdx GetValue() {
    return value;
  }

  static PrimType GetPrimType() {
    return kPrimType;
  }

 private:
  UStrIdx value;
  static const PrimType kPrimType = PTY_a64;
};

class MIRStr16Const : public MIRConst {
 public:
  using value_type = const char*;
  MIRStr16Const(U16StrIdx val, MIRType *type) : MIRConst(type), value(val) {
    SetKind(kConstStr16Const);
  }

  MIRStr16Const(const std::u16string &str, MIRType *type);

  ~MIRStr16Const() {}

  static PrimType GetPrimType() {
    return kPrimType;
  }

  void Dump() const;
  bool operator==(MIRConst &rhs) const;
  U16StrIdx GetValue() const {
    return value;
  }

 private:
  static const PrimType kPrimType = PTY_a64;
  U16StrIdx value;
};

class MIRFloatConst : public MIRConst {
 public:
  using value_type = float;
  MIRFloatConst(float val, MIRType *type) : MIRConst(type) {
    value.floatValue = val;
    SetKind(kConstFloatConst);
  }

  ~MIRFloatConst() {}

  void SetFloatValue(float fvalue) {
    value.floatValue = fvalue;
  }

  value_type GetFloatValue() const {
    return value.floatValue;
  }

  static PrimType GetPrimType() {
    return kPrimType;
  }

  int32 GetIntValue() const {
    return value.intValue;
  }

  value_type GetValue() const {
    return GetFloatValue();
  }

  void Dump() const;
  bool IsZero() {
    return fabs(value.floatValue) <= 1e-6;
  }

  bool IsOne() {
    return value.floatValue == 1;
  };
  bool IsAllBitsOne() {
    return value.floatValue == -1;
  };
  void Neg() {
    value.floatValue = -value.floatValue;
  }

  bool operator==(MIRConst &rhs) const;

 private:
  static const PrimType kPrimType = PTY_f32;
  union {
    value_type floatValue;
    int32 intValue;
  } value;
};

class MIRDoubleConst : public MIRConst {
 public:
  using value_type = double;
  MIRDoubleConst(double val, MIRType *type) : MIRConst(type) {
    value.dValue = val;
    SetKind(kConstDoubleConst);
  }

  ~MIRDoubleConst() {}

  uint32 GetIntLow32() const {
    uint64 unsignVal = static_cast<uint64>(value.intValue);
    return static_cast<uint32>(unsignVal & 0xffffffff);
  }

  uint32 GetIntHigh32() const {
    uint64 unsignVal = static_cast<uint64>(value.intValue);
    return static_cast<uint32>((unsignVal & 0xffffffff00000000) >> 32);
  }

  int64 GetIntValue() const {
    return value.intValue;
  }

  value_type GetValue() const {
    return value.dValue;
  }

  static PrimType GetPrimType() {
    return kPrimType;
  }

  void Dump() const;
  bool IsZero() {
    return fabs(value.dValue) <= 1e-15;
  }

  bool IsOne() {
    return value.dValue == 1;
  };
  bool IsAllBitsOne() {
    return value.dValue == -1;
  };
  void Neg() {
    value.dValue = -value.dValue;
  }

  bool operator==(MIRConst &rhs) const;

 private:
  static const PrimType kPrimType = PTY_f64;
  union {
    value_type dValue;
    int64 intValue;
  } value;
};

class MIRFloat128Const : public MIRConst {
 public:
  MIRFloat128Const(const uint64 *val, MIRType *type) : MIRConst(type) {
    MIR_ASSERT(val && "val must not nullptr!");
    value = val;
    SetKind(kConstFloat128Const);
  }

  ~MIRFloat128Const() {}

  const uint64 *GetIntValue() const {
    return value;
  }

  static PrimType GetPrimType() {
    return kPrimType;
  }

  bool IsZero() {
    MIR_ASSERT(value && "value must not be nullptr!");
    return value[0] == 0 && value[1] == 0;
  }

  bool IsOne() {
    MIR_ASSERT(value && "value must not be nullptr!");
    return value[0] == 0 && value[1] == 0x3FFF000000000000;
  };
  bool IsAllBitsOne() {
    MIR_ASSERT(value && "value must not be nullptr!");
    return (value[0] == 0xffffffffffffffff && value[1] == 0xffffffffffffffff);
  };
  bool operator==(MIRConst &rhs) const;
  void Dump() const;

 private:
  static const PrimType kPrimType = PTY_f128;
  // value[0]: Low 64 bits; value[1]: High 64 bits.
  const uint64 *value;
};

class MIRAggConst : public MIRConst {
 public:
  MIRAggConst(MIRModule *mod, MIRType *type)
      : MIRConst(type), allocator(nullptr), constVec(mod->GetMPAllocator().Adapter()) {
    SetKind(kConstAggConst);
  }

  MIRAggConst(MIRModule *mod, MIRType *type, MemPool *memPool)
      : MIRConst(type), allocator(memPool), constVec(allocator.Adapter()) {
    SetKind(kConstAggConst);
  }

  ~MIRAggConst() {}

  MIRConst *GetAggConstElement(unsigned int fieldidx) {
    for (size_t i = 0; i < constVec.size(); ++i) {
      if (constVec[i] == nullptr) {
        CHECK_FATAL(false, "exist nullptr in constVec");
      }
      if (fieldidx == constVec[i]->GetFieldId()) {
        return constVec[i];
      }
    }
    return nullptr;
  }

  MapleVector<MIRConst*> &GetConstVec() {
    return constVec;
  }

  MIRConstPtr &GetConstVecItem(size_t index) {
    CHECK_FATAL(index < constVec.size(), "index out of range");
    return constVec[index];
  }

  void SetConstVecItem(uint32 index, MIRConst *mirConst) {
    CHECK_FATAL(index < constVec.size(), "index out of range");
    constVec[index] = mirConst;
  }

  void PushBack(MIRConst *elem) {
    constVec.push_back(elem);
  }

  void Dump() const;
  bool operator==(MIRConst &rhs) const;

 private:
  MapleAllocator allocator;
  MapleVector<MIRConst*> constVec;
};

// the const has one or more symbols
class MIRStConst : public MIRConst {
 public:
  MIRStConst(MIRModule *mod, MIRType *type)
      : MIRConst(type), stVec(mod->GetMPAllocator().Adapter()), stOffsetVec(mod->GetMPAllocator().Adapter()) {
    SetKind(kConstStConst);
  }

  MapleVector<MIRSymbol*> &GetStVec() {
    return stVec;
  }

  MIRSymbol *GetStVecItem(size_t index) {
    CHECK_FATAL(index < stVec.size(), "array index out of range");
    return stVec[index];
  }

  MapleVector<uint32> &GetStOffsetVec() {
    return stOffsetVec;
  }

  uint32 GetStOffsetVecItem(size_t index) const {
    CHECK_FATAL(index < stOffsetVec.size(), "array index out of range");
    return stOffsetVec[index];
  }

  ~MIRStConst() {}

 private:
  MapleVector<MIRSymbol*> stVec;    // symbols that in the st const
  MapleVector<uint32> stOffsetVec;  // symbols offset
};

#endif  // MIR_FEATURE_FULL
}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_MIR_CONST_H
