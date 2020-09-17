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
#include "ssa.h"
#include <iostream>
#include "ssa_tab.h"
#include "ssa_mir_nodes.h"
#include "ver_symbol.h"

namespace maple {
void SSA::InitRenameStack(OriginalStTable *otable, size_t bbsize, VersionStTable &versttab) {
  vstStacks.resize(otable->Size());
  vstVersions.resize(otable->Size(), 0);
  bbRenamed.resize(bbsize, false);
  for (size_t i = 1; i < otable->Size(); i++) {
    MapleStack<VersionSt*> *vstack = ssaAlloc.GetMemPool()->New<MapleStack<VersionSt*>>(ssaAlloc.Adapter());
    OriginalSt *ost = otable->GetOriginalStFromID(OStIdx(i));
    VersionSt *temp = (ost->GetIndirectLev() >= 0) ? versttab.GetVersionStFromID(ost->GetZeroVersionIndex(), true)
                                                   : &versttab.GetDummyVersionSt();
    vstack->push(temp);
    vstStacks[i] = vstack;
  }

}

VersionSt *SSA::CreateNewVersion(VersionSt *vsym, BB *defBB) {
  CHECK_FATAL(vsym->GetVersion() == 0, "rename before?");
  // volatile variables will keep zero version.
  if (vsym->GetOrigSt()->IsVolatile()) {
    return vsym;
  }
  ASSERT(vsym->GetOrigIdx().idx < vstVersions.size(), "index out of range in SSA::CreateNewVersion");
  VersionSt *newVersionSym = ssaTab->GetVersionStTable().CreateVSymbol(vsym, ++vstVersions[vsym->GetOrigIdx().idx]);
  vstStacks[vsym->GetOrigIdx().idx]->push(newVersionSym);
  newVersionSym->SetDefBB(defBB);
  return newVersionSym;
}

void SSA::RenamePhi(BB *bb) {
  MapleMap<OriginalSt*, PhiNode>::iterator phiIt;
  for (phiIt = bb->GetPhiList().begin(); phiIt != bb->GetPhiList().end(); phiIt++) {
    VersionSt *vsym = (*phiIt).second.GetResult();
    // It shows that this BB has been renamed.
    if (vsym->GetVersion() > 0) {
      return;
    }
    VersionSt *newVersionSym = CreateNewVersion(vsym, bb);
    (*phiIt).second.SetResult(newVersionSym);
    newVersionSym->SetDefType(VersionSt::kPhi);
    newVersionSym->SetPhi(&(*phiIt).second);
  }
}

void SSA::RenameDefs(StmtNode *stmt, BB *defBB) {
  Opcode opcode = stmt->GetOpCode();
  switch (opcode) {
    case OP_regassign: {
      RegassignNode *regNode = static_cast<RegassignNode*>(stmt);
      if (regNode->GetRegIdx() < 0) {
        return;
      }
      VersionSt *theSSAPart = ssaTab->GetStmtsSSAPart().SSAPartOf(stmt)->GetSSAVar();
      VersionSt *newVersionSym = CreateNewVersion(theSSAPart, defBB);
      newVersionSym->SetDefType(VersionSt::kRegassign);
      newVersionSym->SetRegassignNode(regNode);
      ssaTab->GetStmtsSSAPart().SetSSAPartOf(stmt, newVersionSym);
      return;
    }
    case OP_dassign: {
      DassignNode *dnode = static_cast<DassignNode*>(stmt);
      MayDefPartWithVersionSt *thessapart =
          static_cast<MayDefPartWithVersionSt*>(ssaTab->GetStmtsSSAPart().SSAPartOf(stmt));
      VersionSt *newVersionSym = CreateNewVersion(thessapart->GetSSAVar(), defBB);
      thessapart->SetSSAVar(newVersionSym);
      newVersionSym->SetDefType(VersionSt::kDassign);
      newVersionSym->SetDassignNode(dnode);
    }
    // intentional fall though
    case OP_call:
    case OP_virtualcall:
    case OP_virtualicall:
    case OP_superclasscall:
    case OP_interfacecall:
    case OP_interfaceicall:
    case OP_customcall:
    case OP_polymorphiccall:
    case OP_icall:
    case OP_intrinsiccall:
    case OP_xintrinsiccall:
    case OP_intrinsiccallwithtype:
    case OP_callassigned:
    case OP_virtualcallassigned:
    case OP_virtualicallassigned:
    case OP_superclasscallassigned:
    case OP_interfacecallassigned:
    case OP_interfaceicallassigned:
    case OP_customcallassigned:
    case OP_polymorphiccallassigned:
    case OP_icallassigned:
    case OP_intrinsiccallassigned:
    case OP_xintrinsiccallassigned:
    case OP_intrinsiccallwithtypeassigned:
    case OP_syncenter:
    case OP_syncexit:
    case OP_maydassign:
    case OP_iassign: {
      MapleMap<OStIdx, MayDefNode> *mayDefList = SSAGenericGetMayDefNodes(stmt, &ssaTab->GetStmtsSSAPart());
      for (auto it = mayDefList->begin(); it != mayDefList->end(); it++) {
        MayDefNode &maydef = it->second;
        VersionSt *vsym = maydef.GetResult();
        ASSERT(vsym->GetOrigIdx().idx < vstStacks.size(), "index out of range in SSA::RenameMayDefs");
        maydef.SetOpnd(vstStacks[vsym->GetOrigIdx().idx]->top());
        VersionSt *newVersionSym = CreateNewVersion(vsym, defBB);
        maydef.SetResult(newVersionSym);
        newVersionSym->SetDefType(VersionSt::kMayDef);
        newVersionSym->SetMayDef(&maydef);
      }
      return;
    }
    default:
      return;
  }
}

void SSA::RenameMustDefs(const StmtNode *stmt, BB *defBB) {
  Opcode opcode = stmt->GetOpCode();
  switch (opcode) {
    case OP_callassigned:
    case OP_virtualcallassigned:
    case OP_virtualicallassigned:
    case OP_superclasscallassigned:
    case OP_interfacecallassigned:
    case OP_interfaceicallassigned:
    case OP_customcallassigned:
    case OP_polymorphiccallassigned:
    case OP_icallassigned:
    case OP_intrinsiccallassigned:
    case OP_xintrinsiccallassigned:
    case OP_intrinsiccallwithtypeassigned: {
      MapleVector<MustDefNode> *mustDefs = SSAGenericGetMustDefNode(stmt, &ssaTab->GetStmtsSSAPart());
      MapleVector<MustDefNode>::iterator it = mustDefs->begin();
      for (; it != mustDefs->end(); it++) {
        VersionSt *newVersionSym = CreateNewVersion((*it).GetResult(), defBB);
        (*it).SetResult(newVersionSym);
        newVersionSym->SetDefType(VersionSt::kMustDef);
        newVersionSym->SetMustDef(&(*it));
      }
      return;
    }
    default:
      return;
  }
}

void SSA::RenameMayUses(BaseNode *node) {
  if (node->GetOpCode() == OP_iread) {
    IreadSSANode *iread = static_cast<IreadSSANode*>(node);
    VersionSt *vsym = iread->GetMayUse().GetOpnd();
    CHECK_FATAL(vsym != nullptr, "SSA::RenameMayUses: iread has no mayUse opnd");
    ASSERT(vsym->GetOrigIdx().idx < vstStacks.size(), "index out of range in SSA::RenameMayUses");
    iread->GetMayUse().SetOpnd(vstStacks[vsym->GetOrigIdx().idx]->top());
    return;
  }
  MapleMap<OStIdx, MayUseNode> *mayUseList =
      SSAGenericGetMayUseNode(static_cast<StmtNode*>(node), &ssaTab->GetStmtsSSAPart());
  MapleMap<OStIdx, MayUseNode>::iterator it = mayUseList->begin();
  for (; it != mayUseList->end(); it++) {
    MayUseNode &mayuse = it->second;
    VersionSt *vsym = mayuse.GetOpnd();
    ASSERT(vsym->GetOrigIdx().idx < vstStacks.size(), "index out of range in SSA::RenameMayUses");
    mayuse.SetOpnd(vstStacks.at(vsym->GetOrigIdx().idx)->top());
  }
}

void SSA::RenameExpr(BaseNode *expr) {
  if (expr->GetOpCode() == OP_addrof || expr->GetOpCode() == OP_dread) {
    AddrofSSANode *addrofNode = static_cast<AddrofSSANode*>(expr);
    VersionSt *vsym = addrofNode->GetSSAVar();
    ASSERT(vsym->GetOrigIdx().idx < vstStacks.size(), "index out of range in SSA::RenameExpr");
    addrofNode->SetSSAVar(vstStacks[vsym->GetOrigIdx().idx]->top());
    return;
  } else if (expr->GetOpCode() == OP_regread) {
    RegreadSSANode *regNode = static_cast<RegreadSSANode*>(expr);
    if (regNode->GetRegIdx() < 0) {
      return;
    }
    VersionSt *vsym = regNode->GetSSAVar();
    ASSERT(vsym->GetOrigIdx().idx < vstStacks.size(), "index out of range in SSA::RenameExpr");
    regNode->SetSSAVar(vstStacks[vsym->GetOrigIdx().idx]->top());
    return;
  } else if (expr->GetOpCode() == OP_iread) {
    RenameMayUses(expr);
    RenameExpr(expr->Opnd(0));
  } else {
    for (size_t i = 0; i < expr->NumOpnds(); i++) {
      RenameExpr(expr->Opnd(i));
    }
  }
}

void SSA::RenameUses(StmtNode *stmt) {
  Opcode opcode = stmt->GetOpCode();
  switch (opcode) {
    case OP_brfalse:
    case OP_brtrue: {
      RenameExpr(stmt->Opnd(0));
      break;
    }
    case OP_return: {
      NaryStmtNode *retnode = static_cast<NaryStmtNode*>(stmt);
      BaseNode *retValue = retnode->NumOpnds() == 0 ? nullptr : retnode->Opnd(0);
      RenameMayUses(stmt);
      if (retValue != nullptr) {
        RenameExpr(retValue);
      }
      break;
    }
    case OP_call:
    case OP_virtualcall:
    case OP_virtualicall:
    case OP_superclasscall:
    case OP_interfacecall:
    case OP_interfaceicall:
    case OP_customcall:
    case OP_polymorphiccall:
    case OP_icall:
    case OP_intrinsiccall:
    case OP_xintrinsiccall:
    case OP_intrinsiccallwithtype:
    case OP_callassigned:
    case OP_virtualcallassigned:
    case OP_virtualicallassigned:
    case OP_superclasscallassigned:
    case OP_interfacecallassigned:
    case OP_interfaceicallassigned:
    case OP_customcallassigned:
    case OP_polymorphiccallassigned:
    case OP_icallassigned:
    case OP_intrinsiccallassigned:
    case OP_xintrinsiccallassigned:
    case OP_intrinsiccallwithtypeassigned:
    case OP_syncenter:
    case OP_syncexit: {
      RenameMayUses(stmt);
      for (size_t i = 0; i < stmt->NumOpnds(); i++) {
        BaseNode *argExpr = stmt->Opnd(i);
        RenameExpr(argExpr);
      }
      break;
    }
    case OP_maydassign:
    case OP_dassign: {
      DassignNode *dnode = static_cast<DassignNode*>(stmt);
      RenameExpr(dnode->GetRHS());
      break;
    }
    case OP_regassign: {
      RegassignNode *rnode = static_cast<RegassignNode*>(stmt);
      if (rnode->GetRegIdx() < 0) {
        return;
      }
      RenameExpr(rnode->Opnd(0));
      break;
    }
    case OP_iassign: {
      IassignNode *inode = static_cast<IassignNode*>(stmt);
      RenameExpr(inode->Opnd(0));
      RenameExpr(inode->GetRHS());
      break;
    }
    case OP_throw:
      RenameMayUses(stmt);
    //  fallthrough;
    case OP_assertnonnull:
    case OP_eval:
    case OP_free:
    case OP_switch: {
      BaseNode *argExpr = stmt->Opnd(0);
      RenameExpr(argExpr);
      break;
    }
    case OP_gosub:
    case OP_retsub:
      RenameMayUses(stmt);
      break;
    case OP_comment:
    case OP_label:
    case OP_goto:
    case OP_jstry:
    case OP_jscatch:
    case OP_finally:
    case OP_endtry:
    case OP_cleanuptry:
    case OP_try:
    case OP_catch:
    case OP_membaracquire:
    case OP_membarrelease:
    case OP_membarstoreload:
    case OP_membarstorestore:
      break;
    default:
      CHECK_FATAL(false, "NYI");
      break;
  }
}

void SSA::RenamePhiUseInSucc(BB *bb) {
  for (BB *succBB : bb->GetSucc()) {
    // find index of bb in succ_bb->pred[]
    size_t index = 0;
    while (index < succBB->GetPred().size()) {
      if (succBB->GetPred(index) == bb) {
        break;
      }
      index++;
    }
    CHECK_FATAL(index < succBB->GetPred().size(), "RenamePhiUseInSucc: cannot find corresponding pred");
    // rename the phiOpnds[index] in all the phis in succ_bb
    for (auto phiIt = succBB->GetPhiList().begin();
         phiIt != succBB->GetPhiList().end(); phiIt++) {
      PhiNode &phiNode = phiIt->second;
      ASSERT(phiNode.GetPhiOpnd(index)->GetOrigIdx().idx < vstStacks.size(), "out of range SSA::RenamePhiUseInSucc");
      phiNode.SetPhiOpnd(index, vstStacks.at(phiNode.GetPhiOpnd(index)->GetOrigIdx().idx)->top());
    }
  }
}

void PhiNode::Dump(const MIRModule *mod) {
  GetResult()->Dump(mod);
  LogInfo::MapleLogger() << " = PHI(";
  for (size_t i = 0; i < GetPhiOpns().size(); i++) {
    GetPhiOpnd(i)->Dump(mod);
    if (i < GetPhiOpns().size() - 1) {
      LogInfo::MapleLogger() << ',';
    }
  }
  LogInfo::MapleLogger() << ")" << std::endl;
}

}  // namespace maple
