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
#include "func_emit.h"
#include "mir_function.h"

namespace maple {
void FuncEmit::EmitLabelForBB(MIRFunction *func, BB *bb) {
  ASSERT(bb->GetBBLabel() != 0, "Should have a label");
  // create labelnode
  LabelNode *label = func->GetCodeMempool()->New<LabelNode>();
  label->SetLabelIdx(bb->GetBBLabel());
  if (bb->IsEmpty()) {
    bb->SetFirst(label);
    bb->SetLast(label);
  } else {
    // Insert label before the first non-comment statement of bb
    StmtNode *first = bb->GetStmtNodes().begin().d();
    StmtNode *firstPrev = nullptr;
    while (first != nullptr && first->GetOpCode() == OP_comment) {
      firstPrev = first;
      first = first->GetNext();
    }
    // "first" points to the first non-comment statement, or nullptr
    if (first != nullptr) {
      label->InsertAfterThis(first);
      if (first == bb->GetStmtNodes().begin().d()) {
        bb->SetFirst(label);
      }
    } else {
      label->InsertBeforeThis(firstPrev);
      if (firstPrev == bb->GetStmtNodes().rbegin().base().d()) {
        bb->SetLast(label);
      }
    }
  }
}

static void ConvertMaydassign(BB *bb) {
  for (auto &stmt : bb->GetStmtNodes()) {
    if (stmt.GetOpCode() == OP_maydassign) {
      stmt.SetOpCode(OP_dassign);
    }
  }
}

// Inserting BBs in bblist into func's body.
void FuncEmit::EmitBeforeHSSA(MIRFunction *func, const MapleVector<BB*> &bbList) {
  StmtNode *lastStmt = nullptr;       /* last stmt of previous bb */
  func->GetBody()->SetFirst(nullptr); /* reset body first stmt */
  func->GetBody()->SetLast(nullptr);
  for (BB *bb : bbList) {
    if (bb == nullptr) {
      continue;
    }
    ConvertMaydassign(bb);
    if (bb->GetBBLabel() != 0) {
      EmitLabelForBB(func, bb);
    }
    if (!bb->IsEmpty()) {
      if (func->GetBody()->GetFirst() == nullptr) {
        func->GetBody()->SetFirst(bb->GetStmtNodes().begin().d());
      }
      if (lastStmt != nullptr) {
        bb->GetStmtNodes().push_front(lastStmt);
      }
      lastStmt = bb->GetStmtNodes().rbegin().base().d();
    }
    if (bb->AddBackEndTry()) {
      /* generate op_endtry andd added to next, it could be in an empty bb. */
      StmtNode *endtry = func->GetCodeMempool()->New<StmtNode>(OP_endtry);
      endtry->InsertBeforeThis(lastStmt);
      lastStmt = endtry;
    }
  }
  func->GetBody()->SetLast(lastStmt);
}

}  // namespace maple
