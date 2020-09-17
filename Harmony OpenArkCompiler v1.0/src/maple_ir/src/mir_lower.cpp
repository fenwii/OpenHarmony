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
#include "mir_lower.h"
#include "vtable_impl.h"

#define DO_LT_0_CHECK 1

namespace maple {
BlockNode *MIRLower::LowerIfStmt(IfStmtNode *ifStmt, bool recursive) {
  ASSERT(ifStmt != nullptr, "ifStmt is null");
  bool thenEmpty = ifStmt->GetThenPart() == nullptr || ifStmt->GetThenPart()->GetFirst() == nullptr;
  bool elseEmpty = ifStmt->GetElsePart() == nullptr || ifStmt->GetElsePart()->GetFirst() == nullptr;
  if (recursive) {
    if (!thenEmpty) {
      ifStmt->SetThenPart(LowerBlock(ifStmt->GetThenPart()));
    }
    if (!elseEmpty) {
      ifStmt->SetElsePart(LowerBlock(ifStmt->GetElsePart()));
    }
  }
  BlockNode *blk = mirModule.CurFuncCodeMemPool()->New<BlockNode>();
  if (thenEmpty && elseEmpty) {
    // generate EVAL <cond> statement
    UnaryStmtNode *evalStmt = mirModule.CurFuncCodeMemPool()->New<UnaryStmtNode>(OP_eval);
    evalStmt->SetOpnd(ifStmt->Opnd());
    evalStmt->SetSrcPos(ifStmt->GetSrcPos());
    blk->AddStatement(evalStmt);
  } else if (elseEmpty) {
    // brfalse <cond> <endlabel>
    // <thenPart>
    // label <endlabel>
    CondGotoNode *brFalseStmt = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(OP_brfalse);
    brFalseStmt->SetOpnd(ifStmt->Opnd());
    brFalseStmt->SetSrcPos(ifStmt->GetSrcPos());
    LabelIdx lableIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
    (void)mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(lableIdx);
    brFalseStmt->SetOffset(lableIdx);
    blk->AddStatement(brFalseStmt);
    blk->AppendStatementsFromBlock(ifStmt->GetThenPart());
    LabelNode *lableStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
    lableStmt->SetLabelIdx(lableIdx);
    blk->AddStatement(lableStmt);
  } else if (thenEmpty) {
    // brtrue <cond> <endlabel>
    // <elsePart>
    // label <endlabel>
    CondGotoNode *brTrueStmt = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(OP_brtrue);
    brTrueStmt->SetOpnd(ifStmt->Opnd());
    brTrueStmt->SetSrcPos(ifStmt->GetSrcPos());
    LabelIdx lableIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
    mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(lableIdx);
    brTrueStmt->SetOffset(lableIdx);
    blk->AddStatement(brTrueStmt);
    blk->AppendStatementsFromBlock(ifStmt->GetElsePart());
    LabelNode *lableStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
    lableStmt->SetLabelIdx(lableIdx);
    blk->AddStatement(lableStmt);
  } else {
    // brfalse <cond> <elselabel>
    // <thenPart>
    // goto <endlabel>
    // label <elselabel>
    // <elsePart>
    // label <endlabel>
    CondGotoNode *brFalseStmt = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(OP_brfalse);
    brFalseStmt->SetOpnd(ifStmt->Opnd());
    brFalseStmt->SetSrcPos(ifStmt->GetSrcPos());
    LabelIdx lIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
    (void)mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(lIdx);
    brFalseStmt->SetOffset(lIdx);
    blk->AddStatement(brFalseStmt);
    blk->AppendStatementsFromBlock(ifStmt->GetThenPart());
    ASSERT(ifStmt->GetThenPart()->GetLast()->GetOpCode() != OP_brtrue, "then or else block should not end with brtrue");
    ASSERT(ifStmt->GetThenPart()->GetLast()->GetOpCode() != OP_brfalse,
           "then or else block should not end with brfalse");
    bool fallThroughFromThen = !IfStmtNoFallThrough(ifStmt);
    LabelIdx gotoLableIdx = 0;
    if (fallThroughFromThen) {
      GotoNode *gotoStmt = mirModule.CurFuncCodeMemPool()->New<GotoNode>(OP_goto);
      gotoLableIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
      (void)mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(gotoLableIdx);
      gotoStmt->SetOffset(gotoLableIdx);
      blk->AddStatement(gotoStmt);
    }
    LabelNode *lableStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
    lableStmt->SetLabelIdx(lIdx);
    blk->AddStatement(lableStmt);
    blk->AppendStatementsFromBlock(ifStmt->GetElsePart());
    if (fallThroughFromThen) {
      lableStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
      lableStmt->SetLabelIdx(gotoLableIdx);
      blk->AddStatement(lableStmt);
    }
  }
  return blk;
}

//     while <cond> <body>
// is lowered to:
//     brfalse <cond> <endlabel>
//   label <bodylabel>
//     <body>
//     brtrue <cond> <bodylabel>
//   label <endlabel>
BlockNode *MIRLower::LowerWhileStmt(WhileStmtNode *whileStmt) {
  ASSERT(whileStmt != nullptr, "whileStmt is null");
  whileStmt->SetBody(LowerBlock(whileStmt->GetBody()));
  BlockNode *blk = mirModule.CurFuncCodeMemPool()->New<BlockNode>();
  CondGotoNode *brFalseStmt = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(OP_brfalse);
  brFalseStmt->SetOpnd(whileStmt->Opnd());
  brFalseStmt->SetSrcPos(whileStmt->GetSrcPos());
  LabelIdx lalbeIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
  (void)mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(lalbeIdx);
  brFalseStmt->SetOffset(lalbeIdx);
  blk->AddStatement(brFalseStmt);
  LabelIdx bodyLableIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
  (void)mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(bodyLableIdx);
  LabelNode *lableStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
  lableStmt->SetLabelIdx(bodyLableIdx);
  blk->AddStatement(lableStmt);
  ASSERT(whileStmt->GetBody(), "null ptr check");
  blk->AppendStatementsFromBlock(whileStmt->GetBody());
  CondGotoNode *brTrueStmt = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(OP_brtrue);
  brTrueStmt->SetOpnd(whileStmt->Opnd()->CloneTree(mirModule.CurFuncCodeMemPoolAllocator()));
  brTrueStmt->SetOffset(bodyLableIdx);
  blk->AddStatement(brTrueStmt);
  lableStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
  lableStmt->SetLabelIdx(lalbeIdx);
  blk->AddStatement(lableStmt);
  return blk;
}

//    doloop <do-var>(<start-expr>,<cont-expr>,<incr-amt>) {<body-stmts>}
// is lowered to:
//     dassign <do-var> (<start-expr>)
//     brfalse <cond-expr> <endlabel>
//   label <bodylabel>
//     <body-stmts>
//     dassign <do-var> (<incr-amt>)
//     brtrue <cond-expr>  <bodylabel>
//   label <endlabel>
BlockNode *MIRLower::LowerDoloopStmt(DoloopNode *doloop) {
  ASSERT(doloop != nullptr, "doloop is null");
  doloop->SetDoBody(LowerBlock(doloop->GetDoBody()));
  BlockNode *blk = mirModule.CurFuncCodeMemPool()->New<BlockNode>();
  if (doloop->IsPreg()) {
    PregIdx regIdx = (PregIdx)doloop->GetDoVarStIdx().FullIdx();
    MIRPreg *mirPReg = mirModule.CurFunction()->GetPregTab()->PregFromPregIdx(regIdx);
    PrimType primType = mirPReg->GetPrimType();
    ASSERT(primType != kPtyInvalid, "runtime check error");
    RegassignNode *startRegassign = mirModule.CurFuncCodeMemPool()->New<RegassignNode>();
    startRegassign->SetRegIdx(regIdx);
    startRegassign->SetPrimType(primType);
    startRegassign->SetOpnd(doloop->GetStartExpr());
    startRegassign->SetSrcPos(doloop->GetSrcPos());
    blk->AddStatement(startRegassign);
  } else {
    DassignNode *startDassign = mirModule.CurFuncCodeMemPool()->New<DassignNode>();
    startDassign->SetStIdx(doloop->GetDoVarStIdx());
    startDassign->SetRHS(doloop->GetStartExpr());
    startDassign->SetSrcPos(doloop->GetSrcPos());
    blk->AddStatement(startDassign);
  }
  CondGotoNode *brFalseStmt = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(OP_brfalse);
  brFalseStmt->SetOpnd(doloop->GetCondExpr());
  LabelIdx lIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
  (void)mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(lIdx);
  brFalseStmt->SetOffset(lIdx);
  blk->AddStatement(brFalseStmt);
  LabelIdx bodyLabelIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
  (void)mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(bodyLabelIdx);
  LabelNode *labelStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
  labelStmt->SetLabelIdx(bodyLabelIdx);
  blk->AddStatement(labelStmt);
  ASSERT(doloop->GetDoBody(), "null ptr check ");
  blk->AppendStatementsFromBlock(doloop->GetDoBody());
  if (doloop->IsPreg()) {
    PregIdx regIdx = (PregIdx)doloop->GetDoVarStIdx().FullIdx();
    MIRPreg *mirPreg = mirModule.CurFunction()->GetPregTab()->PregFromPregIdx(regIdx);
    PrimType doVarPType = mirPreg->GetPrimType();
    ASSERT(doVarPType != kPtyInvalid, "runtime check error");
    RegreadNode *readDoVar = mirModule.CurFuncCodeMemPool()->New<RegreadNode>();
    readDoVar->SetRegIdx(regIdx);
    readDoVar->SetPrimType(doVarPType);
    BinaryNode *add =
        mirModule.CurFuncCodeMemPool()->New<BinaryNode>(OP_add, doVarPType, doloop->GetIncrExpr(), readDoVar);
    RegassignNode *endRegassign = mirModule.CurFuncCodeMemPool()->New<RegassignNode>();
    endRegassign->SetRegIdx(regIdx);
    endRegassign->SetPrimType(doVarPType);
    endRegassign->SetOpnd(add);
    blk->AddStatement(endRegassign);
  } else {
    MIRSymbol *doVarSym = mirModule.CurFunction()->GetLocalOrGlobalSymbol(doloop->GetDoVarStIdx());
    PrimType doVarPType = doVarSym->GetType()->GetPrimType();
    DreadNode *readDovar =
        mirModule.CurFuncCodeMemPool()->New<DreadNode>(OP_dread, doVarPType, doloop->GetDoVarStIdx(), 0);
    BinaryNode *add =
        mirModule.CurFuncCodeMemPool()->New<BinaryNode>(OP_add, doVarPType, doloop->GetIncrExpr(), readDovar);
    DassignNode *endDassign = mirModule.CurFuncCodeMemPool()->New<DassignNode>();
    endDassign->SetStIdx(doloop->GetDoVarStIdx());
    endDassign->SetRHS(add);
    blk->AddStatement(endDassign);
  }
  CondGotoNode *brTrueStmt = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(OP_brtrue);
  brTrueStmt->SetOpnd(doloop->GetCondExpr()->CloneTree(mirModule.CurFuncCodeMemPoolAllocator()));
  brTrueStmt->SetOffset(bodyLabelIdx);
  blk->AddStatement(brTrueStmt);
  labelStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
  labelStmt->SetLabelIdx(lIdx);
  blk->AddStatement(labelStmt);
  return blk;
}

//     dowhile <body> <cond>
// is lowered to:
//   label <bodylabel>
//     <body>
//     brtrue <cond> <bodylabel>
BlockNode *MIRLower::LowerDowhileStmt(WhileStmtNode *doWhileStmt) {
  ASSERT(doWhileStmt != nullptr, "doWhildStmt is null");
  doWhileStmt->SetBody(LowerBlock(doWhileStmt->GetBody()));
  BlockNode *blk = mirModule.CurFuncCodeMemPool()->New<BlockNode>();
  LabelIdx lIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
  (void)mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(lIdx);
  LabelNode *labelStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
  labelStmt->SetLabelIdx(lIdx);
  blk->AddStatement(labelStmt);
  ASSERT(doWhileStmt->GetBody(), "null ptr check ");
  blk->AppendStatementsFromBlock(doWhileStmt->GetBody());
  CondGotoNode *brTrueStmt = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(OP_brtrue);
  brTrueStmt->SetOpnd(doWhileStmt->Opnd());
  brTrueStmt->SetOffset(lIdx);
  blk->AddStatement(brTrueStmt);
  return blk;
}

BlockNode *MIRLower::LowerBlock(BlockNode *block) {
  ASSERT(block != nullptr, "block is null");
  BlockNode *newBlock = mirModule.CurFuncCodeMemPool()->New<BlockNode>();
  BlockNode *tmp = nullptr;
  if (!block->GetFirst()) {
    return newBlock;
  }
  StmtNode *nextStmt = block->GetFirst();
  do {
    StmtNode *stmt = nextStmt;
    nextStmt = stmt->GetNext();
    switch (stmt->GetOpCode()) {
      case OP_if:
        tmp = LowerIfStmt(static_cast<IfStmtNode*>(stmt), true);
        ASSERT(tmp, "null ptr check");
        newBlock->AppendStatementsFromBlock(tmp);
        break;
      case OP_while:
        newBlock->AppendStatementsFromBlock(LowerWhileStmt(static_cast<WhileStmtNode*>(stmt)));
        break;
      case OP_dowhile:
        newBlock->AppendStatementsFromBlock(LowerDowhileStmt(static_cast<WhileStmtNode*>(stmt)));
        break;
      case OP_doloop:
        newBlock->AppendStatementsFromBlock(LowerDoloopStmt(static_cast<DoloopNode*>(stmt)));
        break;
      case OP_block:
        tmp = LowerBlock(static_cast<BlockNode*>(stmt));
        ASSERT(tmp, "null ptr check ");
        newBlock->AppendStatementsFromBlock(tmp);
        break;
      default:
        newBlock->AddStatement(stmt);
        break;
    }
  } while (nextStmt != nullptr);
  return newBlock;
}

// for lowering OP_cand and OP_cior that are top level operators in the
// condition operand of OP_brfalse and OP_brtrue
void MIRLower::LowerBrCondition(BlockNode *block) {
  ASSERT(block != nullptr, "block is null");
  if (!block->GetFirst()) {
    return;
  }
  StmtNode *nextStmt = block->GetFirst();
  do {
    StmtNode *stmt = nextStmt;
    nextStmt = stmt->GetNext();
    if (stmt->IsCondBr()) {
      CondGotoNode *condGoto = static_cast<CondGotoNode*>(stmt);
      if (condGoto->Opnd()->GetOpCode() == OP_cand || condGoto->Opnd()->GetOpCode() == OP_cior) {
        BinaryNode *cond = static_cast<BinaryNode*>(condGoto->Opnd());
        if ((stmt->GetOpCode() == OP_brfalse && cond->GetOpCode() == OP_cand) ||
            (stmt->GetOpCode() == OP_brtrue && cond->GetOpCode() == OP_cior)) {
          // short-circuit target label is same as original condGoto stmt
          condGoto->SetOpnd(cond->GetBOpnd(0));
          CondGotoNode *newCondGoto = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(Opcode(stmt->GetOpCode()));
          newCondGoto->SetOpnd(cond->GetBOpnd(1));
          newCondGoto->SetOffset(condGoto->GetOffset());
          block->InsertAfter(newCondGoto, condGoto);
          nextStmt = stmt;  // so it will be re-processed if another cand/cior
        } else {            // short-circuit target is next statement
          LabelIdx lIdx;
          LabelNode *labelStmt = nullptr;
          if (nextStmt->GetOpCode() == OP_label) {
            labelStmt = static_cast<LabelNode*>(nextStmt);
            lIdx = labelStmt->GetLabelIdx();
          } else {
            lIdx = mirModule.CurFunction()->GetLabelTab()->CreateLabel();
            (void)mirModule.CurFunction()->GetLabelTab()->AddToStringLabelMap(lIdx);
            labelStmt = mirModule.CurFuncCodeMemPool()->New<LabelNode>();
            labelStmt->SetLabelIdx(lIdx);
            block->InsertAfter(condGoto, labelStmt);
          }
          CondGotoNode *newCondGoto = mirModule.CurFuncCodeMemPool()->New<CondGotoNode>(
              stmt->GetOpCode() == OP_brfalse ? OP_brtrue : OP_brfalse);
          newCondGoto->SetOpnd(cond->GetBOpnd(0));
          newCondGoto->SetOffset(lIdx);
          block->InsertBefore(condGoto, newCondGoto);
          condGoto->SetOpnd(cond->GetBOpnd(1));
          nextStmt = newCondGoto;  // so it will be re-processed if another cand/cior
        }
      }
    }
  } while (nextStmt != nullptr);
}

void MIRLower::LowerFunc(MIRFunction *func) {
  ASSERT(func != nullptr, "func is null");
  mirModule.SetCurFunction(func);
  if (IsLowerExpandArray()) {
    ExpandArrayMrt(func);
  }
  BlockNode *origBody = func->GetBody();
  BlockNode *newBody = LowerBlock(origBody);
  LowerBrCondition(newBody);
  func->SetBody(newBody);
}

IfStmtNode *MIRLower::ExpandArrayMrtIfBlock(IfStmtNode *node) {
  ASSERT(node != nullptr, "node is null");
  if (node->GetThenPart()) {
    node->SetThenPart(ExpandArrayMrtBlock(node->GetThenPart()));
  }
  if (node->GetElsePart()) {
    node->SetElsePart(ExpandArrayMrtBlock(node->GetElsePart()));
  }
  return node;
}

WhileStmtNode *MIRLower::ExpandArrayMrtWhileBlock(WhileStmtNode *node) {
  ASSERT(node != nullptr, "node is null");
  if (node->GetBody()) {
    node->SetBody(ExpandArrayMrtBlock(node->GetBody()));
  }
  return node;
}

DoloopNode *MIRLower::ExpandArrayMrtDoloopBlock(DoloopNode *node) {
  ASSERT(node != nullptr, "node is null");
  if (node->GetDoBody()) {
    node->SetDoBody(ExpandArrayMrtBlock(node->GetDoBody()));
  }
  return node;
}

ForeachelemNode *MIRLower::ExpandArrayMrtForeachelemBlock(ForeachelemNode *node) {
  ASSERT(node != nullptr, "node is null");
  if (node->GetLoopBody()) {
    node->SetLoopBody(ExpandArrayMrtBlock(node->GetLoopBody()));
  }
  return node;
}

void MIRLower::AddArrayMrtMpl(BaseNode *exp, BlockNode *newBlock) {
  ASSERT(exp != nullptr, "exp is null");
  ASSERT(newBlock != nullptr, "newBlock is null");
  MIRModule &mod = mirModule;
  MIRBuilder *builder = mod.GetMIRBuilder();
  for (size_t i = 0; i < exp->NumOpnds(); i++) {
    AddArrayMrtMpl(exp->Opnd(i), newBlock);
  }
  if (exp->GetOpCode() == OP_array) {
    ArrayNode *arrayNode = static_cast<ArrayNode*>(exp);
    if (arrayNode->GetBoundsCheck()) {
      BaseNode *arrAddr = arrayNode->Opnd(0);
      BaseNode *index = arrayNode->Opnd(1);
      ASSERT(index != nullptr, "null ptr check");
      MIRType *indexType = GlobalTables::GetTypeTable().GetPrimType(index->GetPrimType());
      UnaryStmtNode *nullCheck = builder->CreateStmtUnary(OP_assertnonnull, arrAddr);
      newBlock->AddStatement(nullCheck);
#if DO_LT_0_CHECK
      ConstvalNode *indexZero = builder->GetConstUInt32(0);
      CompareNode *lessZero = builder->CreateExprCompare(OP_lt, GlobalTables::GetTypeTable().GetUInt1(),
                                                         GlobalTables::GetTypeTable().GetUInt32(), index, indexZero);
#endif
      MIRType *infoLenType = GlobalTables::GetTypeTable().GetInt32();
      MapleVector<BaseNode*> arguments(builder->GetCurrentFuncCodeMpAllocator()->Adapter());
      arguments.push_back(arrAddr);
      BaseNode *arrLen = builder->CreateExprIntrinsicop(INTRN_JAVA_ARRAY_LENGTH, OP_intrinsicop,
                                                        infoLenType, arguments);
      BaseNode *cpmIndex = index;
      if (arrLen->GetPrimType() != index->GetPrimType()) {
        cpmIndex = builder->CreateExprTypeCvt(OP_cvt, infoLenType, indexType, index);
      }
      CompareNode *largeLen = builder->CreateExprCompare(OP_ge, GlobalTables::GetTypeTable().GetUInt1(),
                                                         GlobalTables::GetTypeTable().GetUInt32(), cpmIndex, arrLen);
      // maybe should use cior
#if DO_LT_0_CHECK
      BinaryNode *indexCon =
          builder->CreateExprBinary(OP_lior, GlobalTables::GetTypeTable().GetUInt1(), lessZero, largeLen);
#endif
      MapleVector<BaseNode*> args(builder->GetCurrentFuncCodeMpAllocator()->Adapter());
#if DO_LT_0_CHECK
      args.push_back(indexCon);
      IntrinsiccallNode *boundaryTrinsicCall = builder->CreateStmtIntrinsicCall(INTRN_MPL_BOUNDARY_CHECK, args);
#else
      args.push_back(largeLen);
      IntrinsiccallNode *boundaryTrinsicCall = builder->CreateStmtIntrinsicCall(INTRN_MPL_BOUNDARY_CHECK, args);
#endif
      newBlock->AddStatement(boundaryTrinsicCall);
    }
  }
}

BlockNode *MIRLower::ExpandArrayMrtBlock(BlockNode *block) {
  ASSERT(block != nullptr, "block is null");
  BlockNode *newBlock = mirModule.CurFuncCodeMemPool()->New<BlockNode>();
  if (!block->GetFirst()) {
    return newBlock;
  }
  StmtNode *nextStmt = block->GetFirst();
  do {
    StmtNode *stmt = nextStmt;
    nextStmt = stmt->GetNext();
    switch (stmt->GetOpCode()) {
      case OP_if:
        newBlock->AddStatement(ExpandArrayMrtIfBlock(static_cast<IfStmtNode*>(stmt)));
        break;
      case OP_while:
        newBlock->AddStatement(ExpandArrayMrtWhileBlock(static_cast<WhileStmtNode*>(stmt)));
        break;
      case OP_dowhile:
        newBlock->AddStatement(ExpandArrayMrtWhileBlock(static_cast<WhileStmtNode*>(stmt)));
        break;
      case OP_doloop:
        newBlock->AddStatement(ExpandArrayMrtDoloopBlock(static_cast<DoloopNode*>(stmt)));
        break;
      case OP_foreachelem:
        newBlock->AddStatement(ExpandArrayMrtForeachelemBlock(static_cast<ForeachelemNode*>(stmt)));
        break;
      case OP_block:
        newBlock->AddStatement(ExpandArrayMrtBlock(static_cast<BlockNode*>(stmt)));
        break;
      default:
        AddArrayMrtMpl(stmt, newBlock);
        newBlock->AddStatement(stmt);
        break;
    }
  } while (nextStmt != nullptr);
  return newBlock;
}

void MIRLower::ExpandArrayMrt(MIRFunction *func) {
  ASSERT(func != nullptr, "func is null");
  if (ShouldOptArrayMrt(func)) {
    BlockNode *origBody = func->GetBody();
    BlockNode *newBody = ExpandArrayMrtBlock(origBody);
    func->SetBody(newBody);
  }
}

const std::set<std::string> MIRLower::kSetArrayHotFunc = {};
bool MIRLower::ShouldOptArrayMrt(const MIRFunction *func) {
  ASSERT(func != nullptr, "func is null");
  return (MIRLower::kSetArrayHotFunc.find(func->GetName()) != MIRLower::kSetArrayHotFunc.end());
}

}  // namespace maple
