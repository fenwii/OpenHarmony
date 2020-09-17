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
#ifndef MAPLE_IR_INCLUDE_MIR_LOWER_H
#define MAPLE_IR_INCLUDE_MIR_LOWER_H
#include <iostream>
#include "mir_builder.h"
#include "opcodes.h"

namespace maple {
enum MirLowerPhase { kLowerUnder, kLowerMe, kLowerExpandArray, kLowerBe, kLowerCG };

#define LOWERME (1U << kLowerMe)
#define LOWEREXPANDARRAY (1U << kLowerExpandArray)
#define LOWERBE (1U << kLowerBe)
#define LOWERCG (1U << kLowerCG)
// check if a block node ends with an unconditional jump
inline bool OpCodeNoFallThrough(const Opcode opCode) {
  return opCode == OP_goto || opCode == OP_return || opCode == OP_switch || opCode == OP_throw || opCode == OP_gosub ||
         opCode == OP_retsub;
}

inline bool IfStmtNoFallThrough(const IfStmtNode *ifStmt) {
  return OpCodeNoFallThrough(ifStmt->GetThenPart()->GetLast()->GetOpCode());
}

class MIRLower {
 public:
  static const std::set<std::string> kSetArrayHotFunc;

 public:
  explicit MIRLower(MIRModule &mod, MIRFunction *f) : mirModule(mod), mirFunc(f), mirBuilder(nullptr), lowerPhase(0) {}

  virtual ~MIRLower() {}

  MIRFunction *GetMirFunc() {
    return mirFunc;
  }

  void Init() {
    mirBuilder = mirModule.GetMemPool()->New<MIRBuilder>(&mirModule);
  }

  virtual BlockNode *LowerIfStmt(IfStmtNode *ifStmt, bool recursive);
  virtual BlockNode *LowerWhileStmt(WhileStmtNode*);
  BlockNode *LowerDowhileStmt(WhileStmtNode*);
  BlockNode *LowerDoloopStmt(DoloopNode*);
  BlockNode *LowerBlock(BlockNode*);
  void LowerBrCondition(BlockNode *block);
  void LowerFunc(MIRFunction *func);
  void ExpandArrayMrt(MIRFunction *func);
  static bool ShouldOptArrayMrt(const MIRFunction *func);
  IfStmtNode *ExpandArrayMrtIfBlock(IfStmtNode *node);
  WhileStmtNode *ExpandArrayMrtWhileBlock(WhileStmtNode *node);
  DoloopNode *ExpandArrayMrtDoloopBlock(DoloopNode *node);
  ForeachelemNode *ExpandArrayMrtForeachelemBlock(ForeachelemNode *node);
  BlockNode *ExpandArrayMrtBlock(BlockNode *block);
  void AddArrayMrtMpl(BaseNode *exp, BlockNode *newblk);
  void SetLowerME() {
    lowerPhase |= LOWERME;
  }

  void SetLowerExpandArray() {
    lowerPhase |= LOWEREXPANDARRAY;
  }

  void SetLowerBE() {
    lowerPhase |= LOWERBE;
  }

  void SetLowerCG() {
    lowerPhase |= LOWERCG;
  }

  bool IsLowerME() const {
    return lowerPhase & LOWERME;
  }

  bool IsLowerExpandArray() const {
    return lowerPhase & LOWEREXPANDARRAY;
  }

  bool IsLowerBE() const {
    return lowerPhase & LOWERBE;
  }

  bool IsLowerCG() const {
    return lowerPhase & LOWERCG;
  }

 private:
  MIRModule &mirModule;
  MIRFunction *mirFunc;
  MIRBuilder *mirBuilder;
  uint32 lowerPhase;
};

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_MIR_LOWER_H
