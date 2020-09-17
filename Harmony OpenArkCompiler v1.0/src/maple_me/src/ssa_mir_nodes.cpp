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
#include "ssa_mir_nodes.h"
#include "opcode_info.h"
#include "mir_function.h"
#include "printing.h"
#include "ssa_tab.h"

namespace maple {
bool HasMayUseDefPart(const StmtNode *stmtNode) {
  Opcode op = stmtNode->GetOpCode();
  return kOpcodeInfo.IsCall(op) || op == OP_syncenter || op == OP_syncexit;
}

bool HasMayDefPart(const StmtNode *stmtNode) {
  Opcode op = stmtNode->GetOpCode();
  return op == OP_iassign || op == OP_dassign || op == OP_maydassign || HasMayUseDefPart(stmtNode);
}

bool HasMayUsePart(const StmtNode *stmtNode) {
  Opcode op = stmtNode->GetOpCode();
  return op == OP_iread || op == OP_throw || op == OP_gosub || op == OP_retsub || op == OP_return ||
         HasMayUseDefPart(stmtNode);
}

void GenericSSAPrint(MIRModule *mod, const StmtNode *stmtNode, int32 indent, StmtsSSAPart *stmtsSsaprt) {
  stmtNode->Dump(mod, indent);
  // print SSAPart
  Opcode op = stmtNode->GetOpCode();
  AccessSSANodes *ssaPart = stmtsSsaprt->SSAPartOf(stmtNode);
  switch (op) {
    case OP_maydassign:
    case OP_dassign: {
      mod->GetOut() << " ";
      ssaPart->GetSSAVar()->Dump(mod);
      ssaPart->DumpMayDefNodes(mod);
      return;
    }
    case OP_regassign: {
      mod->GetOut() << "  ";
      ssaPart->GetSSAVar()->Dump(mod);
      return;
    }
    case OP_iassign: {
      ssaPart->DumpMayDefNodes(mod);
      return;
    }
    case OP_throw:
    case OP_retsub:
    case OP_return: {
      ssaPart->DumpMayUseNodes(mod);
      mod->GetOut() << std::endl;
      return;
    }
    default: {
      if (kOpcodeInfo.IsCallAssigned(op)) {
        ssaPart->DumpMayUseNodes(mod);
        ssaPart->DumpMustDefNodes(mod);
        ssaPart->DumpMayDefNodes(mod);
      } else if (HasMayUseDefPart(stmtNode)) {
        ssaPart->DumpMayUseNodes(mod);
        mod->GetOut() << std::endl;
        ssaPart->DumpMayDefNodes(mod);
      }
      return;
    }
  }
}

void SSAGenericInsertMayUseNode(const StmtNode *stmtNode, VersionSt *mayuse, StmtsSSAPart *stmtsSsaprt) {
  MapleMap<OStIdx, MayUseNode> *mayUseNodes = SSAGenericGetMayUseNode(stmtNode, stmtsSsaprt);
  if (mayUseNodes == nullptr) {
    return;
  }
  mayUseNodes->insert(std::make_pair(mayuse->GetOrigSt()->GetIndex(), MayUseNode(mayuse)));
}

MapleMap<OStIdx, MayUseNode> *SSAGenericGetMayUseNode(const StmtNode *stmtNode, StmtsSSAPart *stmtsSsaprt) {
  return &(stmtsSsaprt->SSAPartOf(stmtNode)->GetMayUseNodes());
}

void SSAGenericInsertMayDefNode(const StmtNode *stmtNode, VersionSt *vst, StmtNode *s, StmtsSSAPart *stmtsSsaprt) {
  MapleMap<OStIdx, MayDefNode> *mayDefNodes = SSAGenericGetMayDefNodes(stmtNode, stmtsSsaprt);
  if (mayDefNodes == nullptr) {
    return;
  }
  mayDefNodes->insert(std::make_pair(vst->GetOrigSt()->GetIndex(), MayDefNode(vst, s)));
}

MapleMap<OStIdx, MayDefNode> *SSAGenericGetMayDefNodes(const StmtNode *stmtNode, StmtsSSAPart *stmtsSsaprt) {
  if (stmtNode == nullptr) {
    return nullptr;
  }
  return &(stmtsSsaprt->SSAPartOf(stmtNode)->GetMayDefNodes());
}

static MapleMap<OStIdx, MayDefNode> *SSAGenericGetMayDefsFromVersionSt(VersionSt *vst, StmtsSSAPart *ssapart,
                                                                       std::unordered_set<VersionSt*> &visited) {
  if (vst == nullptr || vst->IsInitVersion() || visited.find(vst) != visited.end()) {
    return nullptr;
  }
  visited.insert(vst);
  if (vst->GetDefType() == VersionSt::kPhi) {
    PhiNode *phi = vst->GetPhi();
    for (size_t i = 0; i < phi->GetPhiOpns().size(); i++) {
      VersionSt *vsym = phi->GetPhiOpnd(i);
      MapleMap<OStIdx, MayDefNode> *mayDefs = SSAGenericGetMayDefsFromVersionSt(vsym, ssapart, visited);
      if (mayDefs != nullptr) {
        return mayDefs;
      }
    }
  } else if (vst->GetDefType() == VersionSt::kMayDef) {
    MayDefNode *maydef = vst->GetMayDef();
    return SSAGenericGetMayDefNodes(maydef->GetStmt(), ssapart);
  }
  return nullptr;
}

MapleMap<OStIdx, MayDefNode> *SSAGenericGetMayDefsFromVersionSt(VersionSt *sym, StmtsSSAPart *ssapart) {
  std::unordered_set<VersionSt*> visited;
  return SSAGenericGetMayDefsFromVersionSt(sym, ssapart, visited);
}

MapleVector<MustDefNode> *SSAGenericGetMustDefNode(const StmtNode *stmtNode, StmtsSSAPart *stmtsSsaprt) {
  return &(stmtsSsaprt->SSAPartOf(stmtNode)->GetMustDefNodes());
}

bool HasMayUseOpnd(const BaseNode *baseNode, SSATab *func) {
  const StmtNode *stmtNode = static_cast<const StmtNode*>(baseNode);
  if (HasMayUsePart(stmtNode)) {
    MapleMap<OStIdx, MayUseNode> *mayUses = SSAGenericGetMayUseNode(stmtNode, &func->GetStmtsSSAPart());
    if (!mayUses->empty()) {
      return true;
    }
  }
  for (size_t i = 0; i < baseNode->NumOpnds(); i++) {
    if (HasMayUseOpnd(baseNode->Opnd(i), func)) {
      return true;
    }
  }
  return false;
}

bool HasMayDef(const StmtNode *stmtNode, SSATab *func) {
  if (HasMayDefPart(stmtNode)) {
    MapleMap<OStIdx, MayDefNode> *mayDefs = SSAGenericGetMayDefNodes(stmtNode, &func->GetStmtsSSAPart());
    CHECK_FATAL(mayDefs, "should have maydefs here");
    if (!mayDefs->empty()) {
      return true;
    }
  }
  return false;
}

}  // namespace maple
