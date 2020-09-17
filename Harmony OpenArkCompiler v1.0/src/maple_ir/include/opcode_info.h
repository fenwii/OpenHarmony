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
#ifndef MAPLE_IR_INCLUDE_OPCODE_INFO_H
#define MAPLE_IR_INCLUDE_OPCODE_INFO_H
#include "types_def.h"
#include "opcodes.h"
#include "mpl_logging.h"

namespace maple {
enum OpcodeProp {
  kOpcodePropNone,
  kOpcodePropIsStmt,          // The instruction is a stmt, so has 2 stmt pointers
  kOpcodePropIsVarSize,       // The instruction size is not fixed
  kOpcodePropNotMMPL,         // The instruction is not allowed in Machine Maple IR
  kOpcodePropIsCompare,       // The instruction is one of the 6 comparison ops
  kOpcodePropIsTypeCvt,       // The instruction is a type conversion op
  kOpcodePropHasSSAUse,       // The instruction may incur a use in SSA form
  kOpcodePropHasSSADef,       // The instruction may incur a def in SSA form
  kOpcodePropIsCall,          // The instruction is among the call instructions
  kOpcodePropIsCallAssigned,  // The instruction is among the call instructions with implicit assignments of the
  // returned values
  kOpcodePropNotPure,  // The operation does not return same result with idential operands
  kOpcodePropMayThrowException,
};

constexpr unsigned long OPCODEISSTMT(1UL << kOpcodePropIsStmt);
constexpr unsigned long OPCODEISVARSIZE(1UL << kOpcodePropIsVarSize);
constexpr unsigned long OPCODENOTMMPL(1UL << kOpcodePropNotMMPL);
constexpr unsigned long OPCODEISCOMPARE(1UL << kOpcodePropIsCompare);
constexpr unsigned long OPCODEISTYPECVT(1UL << kOpcodePropIsTypeCvt);
constexpr unsigned long OPCODEHASSSAUSE(1UL << kOpcodePropHasSSAUse);
constexpr unsigned long OPCODEHASSSADEF(1UL << kOpcodePropHasSSADef);
constexpr unsigned long OPCODEISCALL(1UL << kOpcodePropIsCall);
constexpr unsigned long OPCODEISCALLASSIGNED(1UL << kOpcodePropIsCallAssigned);
constexpr unsigned long OPCODENOTPURE(1UL << kOpcodePropNotPure);
constexpr unsigned long OPCODEMAYTHROWEXCEPTION(1UL << kOpcodePropMayThrowException);
struct OpcodeDesc {
  uint8 instrucSize;  // size of instruction in bytes
  uint16 flag;        // stores the opcode property flags
  const char *name;
};

class OpcodeTable {
 public:
  OpcodeTable();
  ~OpcodeTable() {}

  OpcodeDesc GetTableItemAt(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o];
  }

  bool IsStmt(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODEISSTMT;
  }

  bool IsVarSize(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODEISVARSIZE;
  }

  bool NotMMPL(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODENOTMMPL;
  }

  bool IsCompare(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODEISCOMPARE;
  }

  bool IsTypeCvt(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODEISTYPECVT;
  }

  bool HasSSAUse(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODEHASSSAUSE;
  }

  bool HasSSADef(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODEHASSSADEF;
  }

  bool IsCall(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODEISCALL;
  }

  bool IsCallAssigned(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODEISCALLASSIGNED;
  }

  bool NotPure(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODENOTPURE;
  }

  bool MayThrowException(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].flag & OPCODEMAYTHROWEXCEPTION;
  }

  bool HasSideEffect(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return MayThrowException(o);
  }

  const char *GetName(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return table[o].name;
  }

  bool IsCondBr(Opcode o) const {
    ASSERT(o < kOpLast, "invalid opcode");
    return o == OP_brtrue || o == OP_brfalse;
  }

 private:
  OpcodeDesc table[kOpLast];
};

extern const OpcodeTable kOpcodeInfo;
}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_OPCODE_INFO_H
