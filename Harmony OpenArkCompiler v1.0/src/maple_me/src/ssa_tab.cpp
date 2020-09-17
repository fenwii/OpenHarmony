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
#include "ssa_tab.h"
#include <iostream>
#include <fstream>
#include "ssa_mir_nodes.h"
#include "opcode_info.h"
#include "mir_function.h"

// Allocate data structures to store SSA information. Only statement nodes and
// tree nodes that incur defs and uses are relevant. Tree nodes are made larger
// by allocating the larger SSANodes.  Statement nodes' SSA information is
// stored in class SSATab's StmtsSSAPart, which has an array of pointers indexed
// by the stmtID field of each statement node.

namespace maple {
BaseNode *SSATab::CreateSSAExpr(BaseNode *expr) {
  if (expr->GetOpCode() == OP_addrof || expr->GetOpCode() == OP_dread) {
    AddrofNode *addrofNode = static_cast<AddrofNode*>(expr);
    AddrofSSANode *ssaNode = mirModule.CurFunction()->GetCodeMemPool()->New<AddrofSSANode>(addrofNode);
    MIRSymbol *st = mirModule.CurFunction()->GetLocalOrGlobalSymbol(ssaNode->GetStIdx());
    OriginalSt *ost = FindOrCreateSymbolOriginalSt(st, mirModule.CurFunction()->GetPuidx(), ssaNode->GetFieldID());
    VersionSt *vst = versionStTable.FindOrCreateVersionSt(ost, kInitVersion);
    ssaNode->SetSSAVar(vst);
    return ssaNode;
  } else if (expr->GetOpCode() == OP_regread) {
    RegreadNode *rreadNode = static_cast<RegreadNode*>(expr);
    RegreadSSANode *ssaNode = mirModule.CurFunction()->GetCodeMemPool()->New<RegreadSSANode>(rreadNode);
    OriginalSt *ost =
        originalStTable.FindOrCreatePregOriginalSt(ssaNode->GetRegIdx(), mirModule.CurFunction()->GetPuidx());
    VersionSt *vst = versionStTable.FindOrCreateVersionSt(ost, kInitVersion);
    ssaNode->SetSSAVar(vst);
    return ssaNode;
  } else if (expr->GetOpCode() == OP_iread) {
    IreadNode *ireadNode = static_cast<IreadNode*>(expr);
    IreadSSANode *ssaNode = mirModule.CurFunction()->GetCodeMempool()->New<IreadSSANode>(
        mirModule.CurFuncCodeMemPoolAllocator(), ireadNode);
    BaseNode *newOpnd = CreateSSAExpr(expr->Opnd(0));
    if (newOpnd != nullptr) {
      ssaNode->SetOpnd(newOpnd, 0);
    }
    return ssaNode;
  } else {
    for (size_t i = 0; i < expr->NumOpnds(); i++) {
      BaseNode *newOpnd = CreateSSAExpr(expr->Opnd(i));
      if (newOpnd != nullptr) {
        expr->SetOpnd(newOpnd, i);
      }
    }
    return nullptr;
  }
}

void SSATab::CreateSSAStmt(StmtNode *stmt, const BB *curbb, bool ignoreCallassignedDefs) {
  for (size_t i = 0; i < stmt->NumOpnds(); i++) {
    BaseNode *newOpnd = CreateSSAExpr(stmt->Opnd(i));
    if (newOpnd != nullptr) {
      stmt->SetOpnd(newOpnd, i);
    }
  }
  switch (stmt->GetOpCode()) {
    case OP_maydassign:
    case OP_dassign: {
      MayDefPartWithVersionSt *theSSAPart =
          stmtsSSAPart.GetSSAPartMp()->New<MayDefPartWithVersionSt>(&stmtsSSAPart.GetSSAPartAlloc());
      stmtsSSAPart.SetSSAPartOf(stmt, theSSAPart);
      DassignNode *dnode = dynamic_cast<DassignNode*>(stmt);
      MIRSymbol *st = mirModule.CurFunction()->GetLocalOrGlobalSymbol(dnode->GetStIdx());
      CHECK_FATAL(st != nullptr, "null ptr check");

      OriginalSt *ost = FindOrCreateSymbolOriginalSt(st, mirModule.CurFunction()->GetPuidx(), dnode->GetFieldID());
      VersionSt *vst = versionStTable.FindOrCreateVersionSt(ost, kInitVersion);
      theSSAPart->SetSSAVar(vst);
      // if the rhs may throw exception, we insert MayDef of the lhs var
      if (stmt->GetOpCode() == OP_maydassign) {
        theSSAPart->InsertMayDefNode(theSSAPart->GetSSAVar(), dnode);
      }
      return;
    }
    case OP_regassign: {
      RegassignNode *regNode = static_cast<RegassignNode*>(stmt);
      OriginalSt *ost =
          originalStTable.FindOrCreatePregOriginalSt(regNode->GetRegIdx(), mirModule.CurFunction()->GetPuidx());
      VersionSt *vst = versionStTable.FindOrCreateVersionSt(ost, kInitVersion);
      stmtsSSAPart.SetSSAPartOf(stmt, vst);
      return;
    }
    case OP_return:
    case OP_throw:
    case OP_gosub:
    case OP_retsub:
      stmtsSSAPart.SetSSAPartOf(stmt, stmtsSSAPart.GetSSAPartMp()->New<MayUsePart>(&stmtsSSAPart.GetSSAPartAlloc()));
      return;
    case OP_syncenter:
    case OP_syncexit:
      stmtsSSAPart.SetSSAPartOf(stmt,
                                stmtsSSAPart.GetSSAPartMp()->New<MayDefMayUsePart>(&stmtsSSAPart.GetSSAPartAlloc()));
      return;
    case OP_iassign:
      stmtsSSAPart.SetSSAPartOf(stmt, stmtsSSAPart.GetSSAPartMp()->New<MayDefPart>(&stmtsSSAPart.GetSSAPartAlloc()));
      return;
    default: {
      if (kOpcodeInfo.IsCallAssigned(stmt->GetOpCode())) {
        MayDefMayUseMustDefPart *theSSAPart =
            stmtsSSAPart.GetSSAPartMp()->New<MayDefMayUseMustDefPart>(&stmtsSSAPart.GetSSAPartAlloc());
        stmtsSSAPart.SetSSAPartOf(stmt, theSSAPart);
        // insert the mustdefs
        CallReturnVector *nrets = static_cast<NaryStmtNode*>(stmt)->GetCallReturnVector();
        ASSERT(nrets != nullptr, "CreateSSAStmt: failed to retrieve call return vector");
        if (nrets->empty()) {
          return;
        }
        for (CallReturnPair &retPair : *nrets) {
          if (!retPair.second.IsReg()) {
            StIdx stidx = retPair.first;
            MIRSymbolTable *symtab = mirModule.CurFunction()->GetSymTab();
            MIRSymbol *st = symtab->GetSymbolFromStIdx(stidx.Idx());
            OriginalSt *ost =
                FindOrCreateSymbolOriginalSt(st, mirModule.CurFunction()->GetPuidx(), retPair.second.GetFieldID());
            VersionSt *vst = versionStTable.FindOrCreateVersionSt(ost, kInitVersion);
            theSSAPart->InsertMustDefNode(vst, stmt);
          } else {
            ASSERT(false, "NYI");
          }
        }
        return;
      } else if (kOpcodeInfo.IsCall(stmt->GetOpCode())) {
        stmtsSSAPart.SetSSAPartOf(stmt,
                                  stmtsSSAPart.GetSSAPartMp()->New<MayDefMayUsePart>(&stmtsSSAPart.GetSSAPartAlloc()));
        return;
      }
    }
  }
  return;
}

}  // namespace maple
