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
#include "mir_parser.h"
#include "mir_function.h"
#include "opcode_info.h"

namespace maple {
std::map<TokenKind, MIRParser::FuncPtrParseExpr> MIRParser::funcPtrMapForParseExpr =
    MIRParser::InitFuncPtrMapForParseExpr();
std::map<TokenKind, MIRParser::FuncPtrParseStmt> MIRParser::funcPtrMapForParseStmt =
    MIRParser::InitFuncPtrMapForParseStmt();
std::map<TokenKind, MIRParser::FuncPtrParseStmtBlock> MIRParser::funcPtrMapForParseStmtBlock =
    MIRParser::InitFuncPtrMapForParseStmtBlock();

bool MIRParser::ParseStmtDassign(StmtNodePtr &stmt) {
  if (lexer.GetTokenKind() != TK_dassign) {
    Error("expect dassign but get ");
    return false;
  }
  DassignNode *assignstmt = mod.CurFuncCodeMemPool()->New<DassignNode>();
  // parse %i
  lexer.NextToken();
  StIdx stidx;
  if (!ParseDeclaredSt(stidx)) {
    return false;
  }
  if (stidx.FullIdx() == 0) {
    Error("expect a symbol parsing ParseStmtDassign");
    return false;
  }
  assignstmt->SetStIdx(stidx);
  TokenKind ntk = lexer.NextToken();
  // parse field id
  if (ntk == kTkIntconst) {  // may be a field id
    assignstmt->SetFieldID(lexer.GetTheIntVal());
    ntk = lexer.NextToken();
  }
  // parse expression like (constval i32 0)
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  assignstmt->SetRHS(expr);
  stmt = assignstmt;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtRegassign(StmtNodePtr &stmt) {
  RegassignNode *regassign = mod.CurFuncCodeMemPool()->New<RegassignNode>();
  if (!IsPrimitiveType(lexer.NextToken())) {
    Error("expect type parsing binary operator but get ");
    return false;
  }
  regassign->SetPrimType(GetPrimitiveType(lexer.GetTokenKind()));
  lexer.NextToken();
  if (lexer.GetTokenKind() == kTkSpecialreg) {
    if (!ParseSpecialReg(regassign->GetRegIdx())) {
      return false;
    }
  } else if (lexer.GetTokenKind() == kTkPreg) {
    if (!ParsePseudoReg(regassign->GetPrimType(), regassign->GetRegIdx())) {
      return false;
    }
  } else {
    Error("expect special or pseudo register but get ");
    return false;
  }
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  regassign->SetOpnd(expr);
  if (regassign->GetRegIdx() > 0) {  // check type consistenency for the preg
    MIRPreg *preg = mod.CurFunction()->GetPregTab()->PregFromPregIdx(regassign->GetRegIdx());
    if (preg->GetPrimType() == kPtyInvalid) {
      preg->SetPrimType(expr->GetPrimType());
    } else if (preg->GetPrimType() == PTY_dynany) {
      if (!IsPrimitiveDynType(expr->GetPrimType())) {
        Error("inconsistent preg primitive dynamic type at ");
        return false;
      }
    } else if (preg->GetPrimType() != expr->GetPrimType()) {
      if (!IsRefOrPtrAssign(preg->GetPrimType(), expr->GetPrimType()) &&
          !IsNoCvtNeeded(preg->GetPrimType(), expr->GetPrimType())) {
        Error("inconsistent preg primitive type or need a cvt ");
        return false;
      }
    }
  }
  stmt = regassign;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtIassign(StmtNodePtr &stmt) {
  // iassign <* [10] int> ()
  if (lexer.GetTokenKind() != TK_iassign) {
    Error("expect iassign but get ");
    return false;
  }
  // expect <> derived type
  lexer.NextToken();
  TyIdx tyIdx(0);
  if (!ParseDerivedType(tyIdx)) {
    Error("ParseStmtIassign failed when parisng derived type");
    return false;
  }
  IassignNode *iassign = mod.CurFuncCodeMemPool()->New<IassignNode>();
  iassign->SetTyIdx(tyIdx);
  if (lexer.GetTokenKind() == kTkIntconst) {
    iassign->SetFieldID(lexer.theIntVal);
    lexer.NextToken();
  }
  BaseNode *addr = nullptr;
  BaseNode *rhs = nullptr;
  // parse 2 operands then, #1 is address, the other would be value
  if (!ParseExprTwoOperand(addr, rhs)) {
    return false;
  }
  iassign->SetOpnd(addr, 0);
  iassign->SetRHS(rhs);
  lexer.NextToken();
  stmt = iassign;
  return true;
}

bool MIRParser::ParseStmtIassignoff(StmtNodePtr &stmt) {
  // iassign <prim-type> <offset> ( <addr-expr>, <rhs-expr> )
  IassignoffNode *iassignoff = mod.CurFuncCodeMemPool()->New<IassignoffNode>();
  if (!IsPrimitiveType(lexer.NextToken())) {
    Error("expect type parsing binary operator but get ");
    return false;
  }
  iassignoff->SetPrimType(GetPrimitiveType(lexer.GetTokenKind()));
  if (lexer.NextToken() != kTkIntconst) {
    Error("expect offset but get ");
    return false;
  }
  iassignoff->offset = lexer.GetTheIntVal();
  lexer.NextToken();
  BaseNode *addr = nullptr;
  BaseNode *rhs = nullptr;
  if (!ParseExprTwoOperand(addr, rhs)) {
    return false;
  }
  iassignoff->SetBOpnd(addr, 0);
  iassignoff->SetBOpnd(rhs, 1);
  lexer.NextToken();
  stmt = iassignoff;
  return true;
}

bool MIRParser::ParseStmtIassignFPoff(StmtNodePtr &stmt) {
  // iassignfpoff <prim-type> <offset> (<rhs-expr> )
  IassignFPoffNode *iassignoff = mod.CurFuncCodeMemPool()->New<IassignFPoffNode>();
  if (!IsPrimitiveType(lexer.NextToken())) {
    Error("expect type parsing binary operator but get ");
    return false;
  }
  iassignoff->SetPrimType(GetPrimitiveType(lexer.GetTokenKind()));
  if (lexer.NextToken() != kTkIntconst) {
    Error("expect offset but get ");
    return false;
  }
  iassignoff->SetOffset(lexer.GetTheIntVal());
  lexer.NextToken();
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  iassignoff->SetOpnd(expr);
  lexer.NextToken();
  stmt = iassignoff;
  return true;
}

bool MIRParser::ParseStmtDoloop(StmtNodePtr &stmt) {
  // syntax: doloop <do-var> (<start-expr>, <cont-expr>, <incr-amt>) {
  //              <body-stmts> }
  DoloopNode *doloopnode = mod.CurFuncCodeMemPool()->New<DoloopNode>();
  stmt = doloopnode;
  lexer.NextToken();
  if (lexer.GetTokenKind() == kTkPreg) {
    PregIdx pregidx = LookupOrCreatePregIdx(static_cast<uint32>(lexer.GetTheIntVal()), false, mod.CurFunction());
    doloopnode->SetIsPreg(true);
    doloopnode->GetDoVarStIdx().SetFullIdx(pregidx);
    // let other appearances handle the preg primitive type
  } else {
    StIdx stIdx;
    if (!ParseDeclaredSt(stIdx)) {
      return false;
    }
    if (stIdx.FullIdx() == 0) {
      Error("expect a symbol parsing ParseStmtDoloop");
      return false;
    }
    if (stIdx.IsGlobal()) {
      Error("expect local variable for doloop var but get ");
      return false;
    }
    doloopnode->SetDoVarStIdx(stIdx);
  }
  // parse (
  if (lexer.NextToken() != kTkLparen) {
    Error("expect ( but get ");
    return false;
  }
  // parse start expression
  lexer.NextToken();
  BaseNode *start = nullptr;
  if (!ParseExpression(start)) {
    Error("ParseStmtDoloop when parsing start expression");
    return false;
  }
  if (doloopnode->IsPreg()) {
    PregIdx regidx = (PregIdx)doloopnode->GetDoVarStIdx().FullIdx();
    MIRPreg *mpreg = mod.CurFunction()->GetPregTab()->PregFromPregIdx(regidx);
    if (mpreg->GetPrimType() == kPtyInvalid) {
      CHECK_FATAL(start != nullptr, "null ptr check");
      mpreg->SetPrimType(start->GetPrimType());
    }
  }
  if (lexer.GetTokenKind() != kTkComa) {
    Error("expect , after start expression but get ");
    return false;
  }
  doloopnode->SetStartExpr(start);
  // parse end expression
  lexer.NextToken();
  BaseNode *end = nullptr;
  if (!ParseExpression(end)) {  // here should be a compare expression
    Error("ParseStmtDoloop when parsing end expression");
    return false;
  }
  if (lexer.GetTokenKind() != kTkComa) {
    Error("expect , after condition expression but get ");
    return false;
  }
  doloopnode->SetContExpr(end);
  // parse renew induction expression
  lexer.NextToken();
  BaseNode *induction = nullptr;
  if (!ParseExpression(induction)) {
    Error("ParseStmtDoloop when parsing induction");
    return false;
  }
  // parse )
  if (lexer.GetTokenKind() != kTkRparen) {
    Error("expect ) parsing doloop but get ");
    return false;
  }
  doloopnode->SetIncrExpr(induction);
  // parse body of the loop
  lexer.NextToken();
  BlockNode *bodystmt = nullptr;
  if (!ParseStmtBlock(bodystmt)) {
    Error("ParseStmtDoloop when parsing body of the loop");
    return false;
  }
  doloopnode->SetDoBody(bodystmt);
  return true;
}

bool MIRParser::ParseStmtForeachelem(StmtNodePtr &stmt) {
  // syntax: foreachelem <elemvar> <arrayvar> {
  //              <body-stmts> }
  ForeachelemNode *fornode = mod.CurFuncCodeMemPool()->New<ForeachelemNode>();
  stmt = fornode;
  lexer.NextToken();  // skip foreachelem token
  StIdx stidx;
  if (!ParseDeclaredSt(stidx)) {
    return false;
  }
  if (stidx.FullIdx() == 0) {
    Error("error parsing element variable of foreachelem in ");
    return false;
  }
  if (stidx.IsGlobal()) {
    Error("illegal global scope for element variable for foreachelem in ");
    return false;
  }
  fornode->SetElemStIdx(stidx);
  lexer.NextToken();
  if (!ParseDeclaredSt(stidx)) {
    return false;
  }
  if (stidx.FullIdx() == 0) {
    Error("error parsing array/collection variable of foreachelem in ");
    return false;
  }
  fornode->SetArrayStIdx(stidx);
  lexer.NextToken();
  // parse body of the loop
  BlockNode *bodystmt = nullptr;
  if (!ParseStmtBlock(bodystmt)) {
    Error("error when parsing body of foreachelem loop in ");
    return false;
  }
  fornode->SetLoopBody(bodystmt);
  return true;
}

bool MIRParser::ParseStmtIf(StmtNodePtr &stmt) {
  if (lexer.GetTokenKind() != TK_if) {
    Error("expect if but get ");
    return false;
  }
  IfStmtNode *ifstmt = mod.CurFuncCodeMemPool()->New<IfStmtNode>();
  lexer.NextToken();
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  ifstmt->SetOpnd(expr);
  if (lexer.NextToken() != kTkLbrace) {
    Error("expect { begin if body but get ");
    return false;
  }
  BlockNode *thenblock = nullptr;
  if (!ParseStmtBlock(thenblock)) {
    Error("ParseStmtIf failed when parsing then block");
    return false;
  }
  ifstmt->SetThenPart(thenblock);
  BlockNode *elseblock = nullptr;
  if (lexer.GetTokenKind() == TK_else) {
    // has else part
    if (lexer.NextToken() != kTkLbrace) {
      Error("expect { begin if body but get ");
      return false;
    }
    if (!ParseStmtBlock(elseblock)) {
      Error("ParseStmtIf failed when parsing else block");
      return false;
    }
    ifstmt->SetElsePart(elseblock);
    if (elseblock != nullptr) {
      ifstmt->SetNumOpnds(ifstmt->GetNumOpnds() + 1);
    }
  }
  stmt = ifstmt;
  return true;
}

bool MIRParser::ParseStmtWhile(StmtNodePtr &stmt) {
  if (lexer.GetTokenKind() != TK_while) {
    Error("expect while but get ");
    return false;
  }
  WhileStmtNode *whilestmt = mod.CurFuncCodeMemPool()->New<WhileStmtNode>(OP_while);
  lexer.NextToken();
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  whilestmt->SetOpnd(expr);
  if (lexer.NextToken() != kTkLbrace) {
    Error("expect { begin if body but get ");
    return false;
  }
  BlockNode *whilebody = nullptr;
  if (!ParseStmtBlock(whilebody)) {
    Error("ParseStmtWhile failed when parse while body");
    return false;
  }
  whilestmt->SetBody(whilebody);
  stmt = whilestmt;
  return true;
}

bool MIRParser::ParseStmtDowhile(StmtNodePtr &stmt) {
  if (lexer.GetTokenKind() != TK_dowhile) {
    Error("expect while but get ");
    return false;
  }
  WhileStmtNode *whilestmt = mod.CurFuncCodeMemPool()->New<WhileStmtNode>(OP_dowhile);
  if (lexer.NextToken() != kTkLbrace) {
    Error("expect { begin if body but get ");
    return false;
  }
  BlockNode *dowhilebody = nullptr;
  if (!ParseStmtBlock(dowhilebody)) {
    Error("ParseStmtDowhile failed when trying to parsing do while body");
    return false;
  }
  whilestmt->SetBody(dowhilebody);
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  whilestmt->SetOpnd(expr);
  lexer.NextToken();
  stmt = whilestmt;
  return true;
}

bool MIRParser::ParseStmtLabel(StmtNodePtr &stmt) {
  GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
  LabelIdx labidx = mod.CurFunction()->GetLabelTab()->GetStIdxFromStrIdx(stridx);
  if (labidx == 0) {
    labidx = mod.CurFunction()->GetLabelTab()->CreateLabel();
    mod.CurFunction()->GetLabelTab()->SetSymbolFromStIdx(labidx, stridx);
    mod.CurFunction()->GetLabelTab()->AddToStringLabelMap(labidx);
  } else {
    if (definedLabels.size() > labidx && definedLabels[labidx]) {
      Error("label multiply declared ");
      return false;
    }
  }
  if (definedLabels.size() <= labidx) {
    definedLabels.resize(labidx + 1);
  }
  definedLabels[labidx] = true;
  LabelNode *labnode = mod.CurFuncCodeMemPool()->New<LabelNode>();
  labnode->SetLabelIdx(labidx);
  stmt = labnode;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtGoto(StmtNodePtr &stmt) {
  if (lexer.GetTokenKind() != TK_goto) {
    Error("expect goto but get ");
    return false;
  }
  if (lexer.NextToken() != TK_label) {
    Error("expect label in goto but get ");
    return false;
  }
  GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
  LabelIdx labidx = mod.CurFunction()->GetLabelTab()->GetStIdxFromStrIdx(stridx);
  if (labidx == 0) {
    labidx = mod.CurFunction()->GetLabelTab()->CreateLabel();
    mod.CurFunction()->GetLabelTab()->SetSymbolFromStIdx(labidx, stridx);
    mod.CurFunction()->GetLabelTab()->AddToStringLabelMap(labidx);
  }
  GotoNode *gotonode = mod.CurFuncCodeMemPool()->New<GotoNode>(OP_goto);
  gotonode->SetOffset(labidx);
  stmt = gotonode;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtBr(StmtNodePtr &stmt) {
  TokenKind tk = lexer.GetTokenKind();
  if (tk != TK_brtrue && tk != TK_brfalse) {
    Error("expect brtrue/brfalse but get ");
    return false;
  }
  if (lexer.NextToken() != TK_label) {
    Error("expect label in goto but get ");
    return false;
  }
  GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
  LabelIdx labidx = mod.CurFunction()->GetLabelTab()->GetStIdxFromStrIdx(stridx);
  if (labidx == 0) {
    labidx = mod.CurFunction()->GetLabelTab()->CreateLabel();
    mod.CurFunction()->GetLabelTab()->SetSymbolFromStIdx(labidx, stridx);
    mod.CurFunction()->GetLabelTab()->AddToStringLabelMap(labidx);
  }
  CondGotoNode *condgoto = mod.CurFuncCodeMemPool()->New<CondGotoNode>(tk == TK_brtrue ? OP_brtrue : OP_brfalse);
  condgoto->SetOffset(labidx);
  lexer.NextToken();
  // parse (<expr>)
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  condgoto->SetOpnd(expr);
  stmt = condgoto;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseSwitchCase(int32 &constval, LabelIdx &lblIdx) {
  // syntax <intconst0>: goto <label0>
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect intconst in switch but get ");
    return false;
  }
  constval = lexer.GetTheIntVal();
  if (lexer.NextToken() != kTkColon) {
    Error("expect : in switch but get ");
    return false;
  }
  if (lexer.NextToken() != TK_goto) {
    Error("expect goto in switch case but get ");
    return false;
  }
  if (lexer.NextToken() != TK_label) {
    Error("expect label in switch but get ");
    return false;
  }
  lblIdx = mod.CurFunction()->GetOrCreateLableIdxFromName(lexer.GetName());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtSwitch(StmtNodePtr &stmt) {
  SwitchNode *switchnode = mod.CurFuncCodeMemPool()->New<SwitchNode>(&mod);
  stmt = switchnode;
  lexer.NextToken();
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  switchnode->SetSwitchOpnd(expr);
  if (!IsPrimitiveInteger(expr->GetPrimType())) {
    Error("expect expression return integer but get ");
    return false;
  }
  if (lexer.NextToken() == TK_label) {
    switchnode->SetDefaultLabel(mod.CurFunction()->GetOrCreateLableIdxFromName(lexer.GetName()));
  } else {
    Error("expect label in switch but get ");
    return false;
  }
  if (lexer.NextToken() != kTkLbrace) {
    Error("expect { in switch but get ");
    return false;
  }
  // <intconst0>: goto <label0>
  // <intconst1>: goto <label1>
  // ...
  // <intconstn>: goto <labeln>
  TokenKind tk = lexer.NextToken();
  MapleVector<CasePair> &switchtable = switchnode->GetSwitchTable();
  std::set<int32> casesSet;
  while (tk != kTkRbrace) {
    int32 constVal = 0;
    LabelIdx lbl = 0;
    if (!ParseSwitchCase(constVal, lbl)) {
      Error("parse switch case failed ");
      return false;
    }
    if (casesSet.find(constVal) != casesSet.end()) {
      Error("duplicated switch case ");
      return false;
    }
    switchtable.push_back(CasePair(constVal, lbl));
    casesSet.insert(constVal);
    tk = lexer.GetTokenKind();
  }
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtRangegoto(StmtNodePtr &stmt) {
  RangegotoNode *rangegotonode = mod.CurFuncCodeMemPool()->New<RangegotoNode>(&mod);
  stmt = rangegotonode;
  lexer.NextToken();
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  if (!IsPrimitiveInteger(expr->GetPrimType())) {
    rangegotonode->SetOpnd(expr);
    Error("expect expression return integer but get ");
    return false;
  }
  if (lexer.NextToken() == kTkIntconst) {
    rangegotonode->SetTagOffset(lexer.GetTheIntVal());
  } else {
    Error("expect tag offset in rangegoto but get ");
    return false;
  }
  if (lexer.NextToken() != kTkLbrace) {
    Error("expect { in switch but get ");
    return false;
  }
  // <intconst0>: goto <label0>
  // <intconst1>: goto <label1>
  // ...
  // <intconstn>: goto <labeln>
  TokenKind tk = lexer.NextToken();
  std::set<uint16> casesSet;
  int32 minidx = UINT16_MAX;
  int32 maxidx = 0;
  while (tk != kTkRbrace) {
    int32 constVal = 0;
    LabelIdx lbl = 0;
    if (!ParseSwitchCase(constVal, lbl)) {
      Error("parse switch case failed ");
      return false;
    }
    if (constVal > UINT16_MAX || constVal < 0) {
      Error("rangegoto case tag not within unsigned 16 bits range ");
      return false;
    }
    if (casesSet.find(constVal) != casesSet.end()) {
      Error("duplicated switch case ");
      return false;
    }
    if (constVal < minidx) {
      minidx = constVal;
    }
    if (constVal > maxidx) {
      maxidx = constVal;
    }
    rangegotonode->AddRangeGoto(static_cast<uint32>(constVal), static_cast<uint32>(lbl));
    casesSet.insert(constVal);
    tk = lexer.GetTokenKind();
  }
  ASSERT(rangegotonode->GetNumOpnds() == 1, "Rangegoto is a UnaryOpnd; numOpnds must be 1");
  // check there is no gap
  if (static_cast<size_t>(static_cast<uint32>(maxidx - minidx) + 1) != casesSet.size()) {
    Error("gap not allowed in rangegoto case tags ");
    return false;
  }
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtMultiway(StmtNodePtr &stmt) {
  MultiwayNode *multiwaynode = mod.CurFuncCodeMemPool()->New<MultiwayNode>(&mod);
  stmt = multiwaynode;
  lexer.NextToken();
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  multiwaynode->SetMultiWayOpnd(expr);
  if (lexer.NextToken() == TK_label) {
    multiwaynode->SetDefaultlabel(mod.CurFunction()->GetOrCreateLableIdxFromName(lexer.GetName()));
  } else {
    Error("expect label in multiway but get ");
    return false;
  }
  if (lexer.NextToken() != kTkLbrace) {
    Error("expect { in switch but get ");
    return false;
  }
  // (<expr0>): goto <label0>
  // (<expr1>): goto <label1>
  // ...
  // (<exprn>): goto <labeln>
  TokenKind tk = lexer.NextToken();
  while (tk != kTkRbrace) {
    BaseNode *x = nullptr;
    if (!ParseExprOneOperand(x)) {
      return false;
    }
    if (lexer.NextToken() != kTkColon) {
      Error("expect : parsing multiway case tag specification but get ");
      return false;
    }
    if (lexer.NextToken() != TK_goto) {
      Error("expect goto in multiway case expression but get ");
      return false;
    }
    if (lexer.NextToken() != TK_label) {
      Error("expect goto label after multiway case expression but get ");
      return false;
    }
    LabelIdx lblIdx = mod.CurFunction()->GetOrCreateLableIdxFromName(lexer.GetName());
    lexer.NextToken();
    multiwaynode->AppendElemToMultiWayTable(MCasePair(static_cast<BaseNode*>(x), lblIdx));
    tk = lexer.GetTokenKind();
  }
  const MapleVector<MCasePair> &multiwaytable = multiwaynode->GetMultiWayTable();
  multiwaynode->SetNumOpnds(multiwaytable.size());
  lexer.NextToken();
  return true;
}

// used only when parsing mmpl
PUIdx MIRParser::EnterUndeclaredFunction(bool isMcount) {
  std::string funcName;
  if (isMcount) {
    funcName = "_mcount";
  } else {
    funcName = lexer.GetName();
  }
  GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(funcName);
  MIRSymbol *funcSt = GlobalTables::GetGsymTable().CreateSymbol(kScopeGlobal);
  funcSt->SetNameStrIdx(stridx);
  (void)GlobalTables::GetGsymTable().AddToStringSymbolMap(funcSt);
  funcSt->SetStorageClass(kScText);
  funcSt->SetSKind(kStFunc);
  MIRFunction *fn = mod.GetMemPool()->New<MIRFunction>(&mod, funcSt->GetStIdx());
  fn->Init();
  fn->SetPuidx(GlobalTables::GetFunctionTable().GetFuncTable().size());
  GlobalTables::GetFunctionTable().GetFuncTable().push_back(fn);
  funcSt->SetFunction(fn);
  MIRFuncType *functype = mod.GetMemPool()->New<MIRFuncType>();
  fn->SetMIRFuncType(functype);
  if (isMcount) {
    MIRType *rettype = GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(PTY_void));
    fn->SetReturnTyIdx(rettype->GetTypeIndex());
  }
  return fn->GetPuidx();
}

bool MIRParser::ParseStmtCallMcount(StmtNodePtr &stmt) {
  // syntax: call <PU-name> (<opnd0>, ..., <opndn>)
  Opcode o = OP_call;
  PUIdx pidx = EnterUndeclaredFunction(true);
  CallNode *callstmt = mod.CurFuncCodeMemPool()->New<CallNode>(&mod, o);
  callstmt->SetPUIdx(pidx);
  MapleVector<BaseNode*> opndsvec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
  callstmt->SetNOpnd(opndsvec);
  callstmt->SetNumOpnds(opndsvec.size());
  stmt = callstmt;
  return true;
}

bool MIRParser::ParseStmtCall(StmtNodePtr &stmt) {
  // syntax: call <PU-name> (<opnd0>, ..., <opndn>)
  TokenKind tk = lexer.GetTokenKind();
  Opcode o = GetOpFromToken(tk);
  ASSERT(kOpcodeInfo.IsCall(o), "ParseStmtCall: not a call opcode");
  bool hasassigned = kOpcodeInfo.IsCallAssigned(o);
  bool hasinstant = false;
  bool withtype = false;
  switch (tk) {
    case TK_polymorphiccall:
    case TK_polymorphiccallassigned:
      withtype = true;
      break;
    case TK_callinstant:
    case TK_virtualcallinstant:
    case TK_superclasscallinstant:
    case TK_interfacecallinstant:
    case TK_callinstantassigned:
    case TK_virtualcallinstantassigned:
    case TK_superclasscallinstantassigned:
    case TK_interfacecallinstantassigned:
      hasinstant = true;
      break;
    default:;
  }
  TyIdx polymophictyidx(0);
  if (o == OP_polymorphiccallassigned || o == OP_polymorphiccall) {
    TokenKind nextTk = lexer.NextToken();
    if (nextTk == kTkLangle) {
      nextTk = lexer.NextToken();
      if (nextTk == TK_func) {
        lexer.NextToken();
        if (!ParseFuncType(polymophictyidx)) {
          Error("error parsing functype in ParseStmtCall for polymorphiccallassigned at ");
          return false;
        }
      } else {
        Error("expect func in functype but get ");
        return false;
      }
    } else {
      Error("expect < in functype but get ");
      return false;
    }
  }
  TokenKind funcTk = lexer.NextToken();
  if (funcTk != kTkFname) {
    Error("expect func name in call but get ");
    return false;
  }
  PUIdx pidx;
  if (!ParseDeclaredFunc(pidx)) {
    if (mod.GetFlavor() < kMmpl) {
      Error("expect .mmpl");
      return false;
    }
    pidx = EnterUndeclaredFunction();
  }
  lexer.NextToken();
  CallNode *callstmt = nullptr;
  CallinstantNode *callinstantstmt = nullptr;
  if (withtype) {
    callstmt = mod.CurFuncCodeMemPool()->New<CallNode>(&mod, o);
    callstmt->SetTyIdx(polymophictyidx);
  } else if (hasinstant) {
    TokenKind langleTk = lexer.GetTokenKind();
    if (langleTk != kTkLangle) {
      Error("missing < in generic method instantiation at ");
      return false;
    }
    TokenKind lbraceTk = lexer.NextToken();
    if (lbraceTk != kTkLbrace) {
      Error("missing { in generic method instantiation at ");
      return false;
    }
    MIRInstantVectorType instvecty;
    if (!ParseGenericInstantVector(instvecty.GetInstantVec())) {
      Error("error parsing generic method instantiation at ");
      return false;
    }
    TokenKind rangleTk = lexer.GetTokenKind();
    if (rangleTk != kTkRangle) {
      Error("missing > in generic method instantiation at ");
      return false;
    }
    TyIdx tyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&instvecty);
    callinstantstmt = mod.CurFuncCodeMemPool()->New<CallinstantNode>(&mod, o, tyidx);
    callstmt = callinstantstmt;
    lexer.NextToken();  // skip the >
  } else {
    callstmt = mod.CurFuncCodeMemPool()->New<CallNode>(&mod, o);
  }
  callstmt->SetPUIdx(pidx);
  MapleVector<BaseNode*> opndsvec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
  if (!ParseExprNaryOperand(opndsvec)) {
    return false;
  }
  callstmt->SetNOpnd(opndsvec);
  callstmt->SetNumOpnds(opndsvec.size());
  if (hasassigned) {
    CallReturnVector retsvec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
    if (!ParseCallReturns(retsvec)) {
      return false;
    }
    if (!hasinstant) {
      ASSERT(callstmt != nullptr, "callstmt is null in MIRParser::ParseStmtCall");
      callstmt->SetReturnVec(retsvec);
    } else {
      ASSERT(callinstantstmt != nullptr, "callinstantstmt is null in MIRParser::ParseStmtCall");
      callinstantstmt->SetReturnVec(retsvec);
    }
  }
  lexer.NextToken();
  stmt = callstmt;
  return true;
}

bool MIRParser::ParseStmtIcall(StmtNodePtr &stmt, bool isAssigned) {
  // syntax: icall (<PU-ptr>, <opnd0>, ..., <opndn>)
  //         icallassigned <PU-ptr> (<opnd0>, ..., <opndn>) {
  //              dassign <var-name0> <field-id0>
  //              dassign <var-name1> <field-id1>
  //               . . .
  //              dassign <var-namen> <field-idn> }
  IcallNode *icallStmt = mod.CurFuncCodeMemPool()->New<IcallNode>(&mod, !isAssigned ? OP_icall : OP_icallassigned);
  lexer.NextToken();
  MapleVector<BaseNode*> opndsvec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
  if (!ParseExprNaryOperand(opndsvec)) {
    return false;
  }
  icallStmt->SetNOpnd(opndsvec);
  icallStmt->SetNumOpnds(opndsvec.size());
  if (isAssigned) {
    CallReturnVector retsvec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
    if (!ParseCallReturns(retsvec)) {
      return false;
    }
    icallStmt->SetReturnVec(retsvec);
  }
  lexer.NextToken();
  stmt = icallStmt;
  return true;
}

bool MIRParser::ParseStmtIcall(StmtNodePtr &stmt) {
  return ParseStmtIcall(stmt, false);
}

bool MIRParser::ParseStmtIcallassigned(StmtNodePtr &stmt) {
  return ParseStmtIcall(stmt, true);
}

bool MIRParser::ParseStmtIntrinsiccall(StmtNodePtr &stmt, bool isAssigned) {
  Opcode o = !isAssigned ? (lexer.GetTokenKind() == TK_intrinsiccall ? OP_intrinsiccall : OP_xintrinsiccall)
                         : (lexer.GetTokenKind() == TK_intrinsiccallassigned ? OP_intrinsiccallassigned
                                                                             : OP_xintrinsiccallassigned);
  IntrinsiccallNode *intrncallnode = mod.CurFuncCodeMemPool()->New<IntrinsiccallNode>(&mod, o);
  lexer.NextToken();
  if (o == !isAssigned ? OP_intrinsiccall : OP_intrinsiccallassigned) {
    intrncallnode->SetIntrinsic(GetIntrinsicId(lexer.GetTokenKind()));
  } else {
    intrncallnode->SetIntrinsic(static_cast<MIRIntrinsicID>(lexer.GetTheIntVal()));
  }
  lexer.NextToken();
  MapleVector<BaseNode*> opndsvec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
  if (!ParseExprNaryOperand(opndsvec)) {
    return false;
  }
  intrncallnode->SetNOpnd(opndsvec);
  intrncallnode->SetNumOpnds(opndsvec.size());
  if (isAssigned) {
    CallReturnVector retsvec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
    if (!ParseCallReturns(retsvec)) {
      return false;
    }
    // store return type of IntrinsiccallNode
    if (retsvec.size() == 1 && retsvec[0].first.Idx() != 0) {
      MIRSymbol *retsymbol = curFunc->GetSymTab()->GetSymbolFromStIdx(retsvec[0].first.Idx());
      MIRType *rettype = GlobalTables::GetTypeTable().GetTypeFromTyIdx(retsymbol->GetTyIdx());
      CHECK_FATAL(rettype != nullptr, "rettype is null in MIRParser::ParseStmtIntrinsiccallAssigned");
      intrncallnode->SetPrimType(rettype->GetPrimType());
    }
    intrncallnode->SetReturnVec(retsvec);
  }
  stmt = intrncallnode;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtIntrinsiccall(StmtNodePtr &stmt) {
  return ParseStmtIntrinsiccall(stmt, false);
}

bool MIRParser::ParseStmtIntrinsiccallassigned(StmtNodePtr &stmt) {
  return ParseStmtIntrinsiccall(stmt, true);
}

bool MIRParser::ParseStmtIntrinsiccallwithtype(StmtNodePtr &stmt, bool isAssigned) {
  Opcode o = !isAssigned ? OP_intrinsiccallwithtype : OP_intrinsiccallwithtypeassigned;
  IntrinsiccallNode *intrncallnode = mod.CurFuncCodeMemPool()->New<IntrinsiccallNode>(&mod, o);
  TokenKind tk = lexer.NextToken();
  TyIdx tyidx(0);
  if (IsPrimitiveType(tk)) {
    if (!ParsePrimType(tyidx)) {
      Error("expect primitive type in ParseStmtIntrinsiccallwithtype but get ");
      return false;
    }
  } else if (!ParseDerivedType(tyidx)) {
    Error("error parsing type in ParseStmtIntrinsiccallwithtype at ");
    return false;
  }
  intrncallnode->SetTyIdx(tyidx);
  intrncallnode->SetIntrinsic(GetIntrinsicId(lexer.GetTokenKind()));
  lexer.NextToken();
  MapleVector<BaseNode*> opndsvec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
  if (!ParseExprNaryOperand(opndsvec)) {
    return false;
  }
  intrncallnode->SetNOpnd(opndsvec);
  intrncallnode->SetNumOpnds(opndsvec.size());
  if (isAssigned) {
    CallReturnVector retsvec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
    if (!ParseCallReturns(retsvec)) {
      return false;
    }
    // store return type of IntrinsiccallNode
    if (retsvec.size() == 1 && retsvec[0].first.Idx() != 0) {
      MIRSymbol *retsymbol = curFunc->GetSymTab()->GetSymbolFromStIdx(retsvec[0].first.Idx());
      MIRType *rettype = GlobalTables::GetTypeTable().GetTypeFromTyIdx(retsymbol->GetTyIdx());
      CHECK_FATAL(rettype != nullptr, "rettype is null in MIRParser::ParseStmtIntrinsiccallwithtypeAssigned");
      intrncallnode->SetPrimType(rettype->GetPrimType());
    }
    intrncallnode->SetReturnVec(retsvec);
  }
  stmt = intrncallnode;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtIntrinsiccallwithtype(StmtNodePtr &stmt) {
  return ParseStmtIntrinsiccallwithtype(stmt, false);
}

bool MIRParser::ParseStmtIntrinsiccallwithtypeassigned(StmtNodePtr &stmt) {
  return ParseStmtIntrinsiccallwithtype(stmt, true);
}

bool MIRParser::ParseCallReturns(CallReturnVector &retsvec) {
  //             {
  //              dassign <var-name0> <field-id0>
  //              dassign <var-name1> <field-id1>
  //               . . .
  //              dassign <var-namen> <field-idn> }
  //              OR
  //             {
  //               regassign <type> <reg1>
  //               regassign <type> <reg2>
  //               regassign <type> <reg3>
  //             }
  if (lexer.NextToken() != kTkLbrace) {
    Error("expect { parsing call return values. ");
    return false;
  }
  TokenKind tk = lexer.NextToken();
  while (tk != kTkRbrace) {
    if (lexer.GetTokenKind() != TK_dassign && lexer.GetTokenKind() != TK_regassign) {
      Error("expect dassign/regassign but get ");
      return false;
    }
    bool isst = (lexer.GetTokenKind() == TK_dassign);
    if (isst) {
      // parse %i
      lexer.NextToken();
      StIdx stidx;
      // How to use islocal??
      if (!ParseDeclaredSt(stidx)) {
        return false;
      }
      if (lexer.GetTokenKind() == kTkLname) {
        MIRSymbolTable *lsymtab = mod.CurFunction()->GetSymTab();
        MIRSymbol *lsym = lsymtab->GetSymbolFromStIdx(stidx.Idx(), 0);
        ASSERT(lsym != nullptr, "lsym MIRSymbol is null");
        if (lsym->GetName().find("L_STR") == 0) {
          MIRType *ty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(lsym->GetTyIdx());
          MIRPtrType *ptrTy = static_cast<MIRPtrType*>(ty->CopyMIRTypeNode());
          ASSERT(ptrTy != nullptr, "null ptr check");
          ptrTy->SetPrimType(PTY_ptr);
          TyIdx newTyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(ptrTy);
          delete ptrTy;
          lsym->SetTyIdx(newTyidx);
        }
      }
      if (stidx.FullIdx() == 0) {
        Error("expect a symbol parsing ParseCallAssignedStmts. ");
        return false;
      }
      uint16 fieldid = 0;
      TokenKind ntk = lexer.NextToken();
      // parse field id
      if (ntk == kTkIntconst) {
        fieldid = lexer.GetTheIntVal();
      } else {
        Error("expect a fieldID parsing ParseCallAssignedStmts. ");
      }
      RegFieldPair regfieldpair;
      regfieldpair.SetFieldID(fieldid);
      retsvec.push_back(CallReturnPair(stidx, regfieldpair));
      tk = lexer.NextToken();
    } else {
      // parse type
      lexer.NextToken();
      TyIdx tyidx(0);
      // RegreadNode regreadexpr;
      bool ret = ParsePrimType(tyidx);
      if (ret != true) {
        Error("call ParsePrimType failed in ParseCallReturns");
        return false;
      }
      if (tyidx == 0) {
        Error("expect primitive type but get ");
        return false;
      }
      PrimType ptype = GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx);
      PregIdx pregidx;
      if (lexer.GetTokenKind() == kTkSpecialreg) {
        if (!ParseSpecialReg(pregidx)) {
          Error("expect specialreg parsing callassign CallReturnVector");
          return false;
        }
      } else if (lexer.GetTokenKind() == kTkPreg) {
        if (!ParsePseudoReg(ptype, pregidx)) {
          Error("expect pseudoreg parsing callassign CallReturnVector");
          return false;
        }
      } else {
        Error("expect special or pseudo register but get ");
        return false;
      }
      ASSERT(pregidx > 0, "register number is zero");
      ASSERT(pregidx <= 0xffff, "register number is over 16 bits");
      RegFieldPair regfieldpair;
      regfieldpair.SetPregIdx(pregidx);
      retsvec.push_back(CallReturnPair(StIdx(), regfieldpair));
      tk = lexer.GetTokenKind();
    }
  }
  return true;
}

bool MIRParser::ParseStmtJsTry(StmtNodePtr &stmt) {
  JsTryNode *trynode = mod.CurFuncCodeMemPool()->New<JsTryNode>();
  lexer.NextToken();
  // parse handler label
  if (lexer.GetTokenKind() == kTkIntconst && lexer.GetTheIntVal() == 0) {
    trynode->SetCatchOffset(0);
  } else {
    if (lexer.GetTokenKind() != TK_label) {
      Error("expect handler label in try but get ");
      return false;
    }
    GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
    LabelIdx labidx = mod.CurFunction()->GetLabelTab()->GetStIdxFromStrIdx(stridx);
    if (labidx == 0) {
      labidx = mod.CurFunction()->GetLabelTab()->CreateLabel();
      mod.CurFunction()->GetLabelTab()->SetSymbolFromStIdx(labidx, stridx);
      mod.CurFunction()->GetLabelTab()->AddToStringLabelMap(labidx);
    }
    trynode->SetCatchOffset(labidx);
  }
  lexer.NextToken();
  // parse finally label
  if (lexer.GetTokenKind() == kTkIntconst && lexer.GetTheIntVal() == 0) {
    trynode->SetFinallyOffset(0);
  } else {
    if (lexer.GetTokenKind() != TK_label) {
      Error("expect finally label in try but get ");
      return false;
    }
    GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
    LabelIdx labidx = mod.CurFunction()->GetLabelTab()->GetStIdxFromStrIdx(stridx);
    if (labidx == 0) {
      labidx = mod.CurFunction()->GetLabelTab()->CreateLabel();
      mod.CurFunction()->GetLabelTab()->SetSymbolFromStIdx(labidx, stridx);
      mod.CurFunction()->GetLabelTab()->AddToStringLabelMap(labidx);
    }
    trynode->SetFinallyOffset(labidx);
  }
  stmt = trynode;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtTry(StmtNodePtr &stmt) {
  TryNode *trynode = mod.CurFuncCodeMemPool()->New<TryNode>(&mod);
  lexer.NextToken();
  ASSERT(lexer.GetTokenKind() == kTkLbrace, "expect left brace in try but get ");
  lexer.NextToken();
  // parse handler label
  while (lexer.GetTokenKind() != kTkRbrace) {
    if (lexer.GetTokenKind() != TK_label) {
      Error("expect handler label in try but get ");
      return false;
    }
    GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
    LabelIdx labidx = mod.CurFunction()->GetLabelTab()->GetStIdxFromStrIdx(stridx);
    if (labidx == 0) {
      labidx = mod.CurFunction()->GetLabelTab()->CreateLabel();
      mod.CurFunction()->GetLabelTab()->SetSymbolFromStIdx(labidx, stridx);
      mod.CurFunction()->GetLabelTab()->AddToStringLabelMap(labidx);
    }
    trynode->AddOffset(labidx);
    lexer.NextToken();
  }
  stmt = trynode;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtCatch(StmtNodePtr &stmt) {
  CatchNode *catchnode = mod.CurFuncCodeMemPool()->New<CatchNode>(&mod);
  lexer.NextToken();
  ASSERT(lexer.GetTokenKind() == kTkLbrace, "expect left brace in catch but get ");
  lexer.NextToken();
  while (lexer.GetTokenKind() != kTkRbrace) {
    TyIdx tyidx(0);
    if (!ParseType(tyidx)) {
      Error("expect type parsing java catch statement");
      return false;
    }
    catchnode->PushBack(tyidx);
  }
  catchnode->SetNumOpnds(0);
  stmt = catchnode;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseUnaryStmt(Opcode op, StmtNodePtr &stmt) {
  lexer.NextToken();
  UnaryStmtNode *throwstmt = mod.CurFuncCodeMemPool()->New<UnaryStmtNode>(op);
  stmt = throwstmt;
  BaseNode *expr = nullptr;
  if (!ParseExprOneOperand(expr)) {
    return false;
  }
  throwstmt->SetOpnd(expr);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseUnaryStmtThrow(StmtNodePtr &stmt) {
  return ParseUnaryStmt(OP_throw, stmt);
}

bool MIRParser::ParseUnaryStmtDecRef(StmtNodePtr &stmt) {
  return ParseUnaryStmt(OP_decref, stmt);
}

bool MIRParser::ParseUnaryStmtIncRef(StmtNodePtr &stmt) {
  return ParseUnaryStmt(OP_incref, stmt);
}

bool MIRParser::ParseUnaryStmtDecRefReset(StmtNodePtr &stmt) {
  return ParseUnaryStmt(OP_decrefreset, stmt);
}

bool MIRParser::ParseUnaryStmtEval(StmtNodePtr &stmt) {
  return ParseUnaryStmt(OP_eval, stmt);
}

bool MIRParser::ParseUnaryStmtFree(StmtNodePtr &stmt) {
  return ParseUnaryStmt(OP_free, stmt);
}

bool MIRParser::ParseUnaryStmtAssertNonNull(StmtNodePtr &stmt) {
  return ParseUnaryStmt(OP_assertnonnull, stmt);
}

bool MIRParser::ParseStmtMarker(StmtNodePtr &stmt) {
  Opcode op;
  switch (paramTokenKindForStmt) {
    case TK_jscatch:
      op = OP_jscatch;
      break;
    case TK_finally:
      op = OP_finally;
      break;
    case TK_cleanuptry:
      op = OP_cleanuptry;
      break;
    case TK_endtry:
      op = OP_endtry;
      break;
    case TK_retsub:
      op = OP_retsub;
      break;
    case TK_membaracquire:
      op = OP_membaracquire;
      break;
    case TK_membarrelease:
      op = OP_membarrelease;
      break;
    case TK_membarstoreload:
      op = OP_membarstoreload;
      break;
    case TK_membarstorestore:
      op = OP_membarstorestore;
      break;
    default:
      return false;
  }
  StmtNode *stmtnode = mod.CurFuncCodeMemPool()->New<StmtNode>(op);
  stmt = stmtnode;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtGosub(StmtNodePtr &stmt) {
  if (lexer.NextToken() != TK_label) {
    Error("expect finally label in gosub but get ");
    return false;
  }
  GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
  LabelIdx labidx = mod.CurFunction()->GetLabelTab()->GetStIdxFromStrIdx(stridx);
  if (labidx == 0) {
    labidx = mod.CurFunction()->GetLabelTab()->CreateLabel();
    mod.CurFunction()->GetLabelTab()->SetSymbolFromStIdx(labidx, stridx);
    mod.CurFunction()->GetLabelTab()->AddToStringLabelMap(labidx);
  }
  GotoNode *gosubnode = mod.CurFuncCodeMemPool()->New<GotoNode>(OP_gosub);
  gosubnode->SetOffset(labidx);
  stmt = gosubnode;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseBinaryStmt(StmtNodePtr &stmt, Opcode op) {
  BinaryStmtNode *assstmt = mod.CurFuncCodeMemPool()->New<BinaryStmtNode>(op);
  lexer.NextToken();
  BaseNode *opnd0 = nullptr;
  BaseNode *opnd1 = nullptr;
  if (!ParseExprTwoOperand(opnd0, opnd1)) {
    return false;
  }
  assstmt->SetBOpnd(opnd0, 0);
  assstmt->SetBOpnd(opnd1, 1);
  stmt = assstmt;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseBinaryStmtAssertGE(StmtNodePtr &stmt) {
  return ParseBinaryStmt(stmt, OP_assertge);
}

bool MIRParser::ParseBinaryStmtAssertLT(StmtNodePtr &stmt) {
  return ParseBinaryStmt(stmt, OP_assertlt);
}

bool MIRParser::ParseNaryStmt(StmtNodePtr &stmt, Opcode op) {
  NaryStmtNode *stmtReturn = mod.CurFuncCodeMemPool()->New<NaryStmtNode>(&mod, op);
  if (lexer.NextToken() != kTkLparen) {
    Error("expect return with ( but get ");
    return false;
  }
  TokenKind exprTk = lexer.NextToken();
  if (exprTk == kTkRparen) {  // no operand
    stmt = stmtReturn;
    lexer.NextToken();
    return true;
  }
  BaseNode *expr = nullptr;
  if (!ParseExpression(expr)) {
    Error("ParseStmtReturn failed");
    return false;
  }
  stmtReturn->GetNopnd().push_back(expr);
  if (op == OP_syncenter) {
    if (lexer.GetTokenKind() == kTkComa) {
      lexer.NextToken();
      BaseNode *exprSync = nullptr;
      if (!ParseExpression(exprSync)) {
        Error("ParseStmtReturn failed");
        return false;
      }
      stmtReturn->GetNopnd().push_back(exprSync);
    } else {
      MIRType *inttype = GlobalTables::GetTypeTable().GetTypeFromTyIdx((TyIdx)PTY_i32);
      // default 2 for __sync_enter_fast()
      MIRIntConst *intconst = mod.GetMemPool()->New<MIRIntConst>(2, inttype);
      ConstvalNode *exprconst = mod.GetMemPool()->New<ConstvalNode>();
      exprconst->SetPrimType(PTY_i32);
      exprconst->SetConstVal(intconst);
      stmtReturn->GetNopnd().push_back(exprconst);
      stmtReturn->SetNumOpnds(stmtReturn->GetNopndSize());
    }
  }
  if (lexer.GetTokenKind() != kTkRparen) {
    Error("expect ) parsing return but get ");
    return false;
  }
  stmtReturn->SetNumOpnds(stmtReturn->GetNopndSize());
  stmt = stmtReturn;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseNaryStmtReturn(StmtNodePtr &stmt) {
  return ParseNaryStmt(stmt, OP_return);
}

bool MIRParser::ParseNaryStmtSyncEnter(StmtNodePtr &stmt) {
  return ParseNaryStmt(stmt, OP_syncenter);
}

bool MIRParser::ParseNaryStmtSyncExit(StmtNodePtr &stmt) {
  return ParseNaryStmt(stmt, OP_syncexit);
}

bool MIRParser::ParseLoc(StmtNodePtr &stmt) {
  if (lexer.NextToken() != kTkIntconst) {
    Error("expect intconst in LOC but get ");
    return false;
  }
  lastFileNum = lexer.GetTheIntVal();
  if (lexer.NextToken() != kTkIntconst) {
    Error("expect intconst in LOC but get ");
    return false;
  }
  lastLineNum = lexer.GetTheIntVal();
  if (firstLineNum == 0) {
    firstLineNum = lastLineNum;
  }
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStatement(StmtNodePtr &stmt) {
  paramTokenKindForStmt = lexer.GetTokenKind();
  uint32 mplNum = lexer.GetLineNum();
  uint32 lnum = lastLineNum;
  uint32 fnum = lastFileNum;
  std::map<TokenKind, FuncPtrParseStmt>::iterator itFuncPtr = funcPtrMapForParseStmt.find(paramTokenKindForStmt);
  if (itFuncPtr != funcPtrMapForParseStmt.end()) {
    if (!(this->*(itFuncPtr->second))(stmt)) {
      return false;
    }
  } else {
    return false;
  }
  if (stmt && stmt->GetSrcPos().MplLineNum() == 0) {
    stmt->GetSrcPos().SetFileNum(fnum);
    stmt->GetSrcPos().SetLineNum(lnum);
    stmt->GetSrcPos().SetMplLineNum(mplNum);
  }
  return true;
}

/* parse the statements enclosed by { and }
 */
bool MIRParser::ParseStmtBlock(BlockNodePtr &blk) {
  if (lexer.GetTokenKind() != kTkLbrace) {
    Error("expect { for func body but get ");
    return false;
  }
  blk = mod.CurFuncCodeMemPool()->New<BlockNode>();
  MIRFunction *fn = mod.CurFunction();
  paramCurrFuncForParseStmtBlock = fn;
  lexer.NextToken();
  // Insert _mcount for PI.
  if (mod.GetWithProfileInfo()) {
    StmtNode *stmtt = nullptr;
    if (!ParseStmtCallMcount(stmtt)) {
      return false;
    }
    blk->AddStatement(stmtt);
  }
  while (true) {
    TokenKind stmtTk = lexer.GetTokenKind();
    // calculate the mpl file line number mplNum here to get accurate result
    uint32 mplNum = lexer.GetLineNum();
    if (IsStatement(stmtTk)) {
      ParseStmtBlockForSeenComment(blk, mplNum);
      StmtNode *stmt = nullptr;
      if (!ParseStatement(stmt)) {
        Error("ParseStmtBlock failed when parsing a statement");
        return false;
      }
      if (stmt != nullptr) {  // stmt is nullptr if it is a LOC
        SetSrcPos(stmt, mplNum);
        blk->AddStatement(stmt);
      }
    } else {
      std::map<TokenKind, FuncPtrParseStmtBlock>::iterator itFuncPtr = funcPtrMapForParseStmtBlock.find(stmtTk);
      if (itFuncPtr == funcPtrMapForParseStmtBlock.end()) {
        if (stmtTk == kTkRbrace) {
          ParseStmtBlockForSeenComment(blk, mplNum);
          lexer.NextToken();
          return true;
        } else {
          Error("expect } or var or statement for func body but get ");
          return false;
        }
      } else {
        if (!(this->*(itFuncPtr->second))()) {
          return false;
        }
      }
    }
  }
}

void MIRParser::ParseStmtBlockForSeenComment(BlockNodePtr blk, uint32 mplNum) {
  // collect accumulated comments into comment statement nodes
  if (!lexer.seenComments.empty()) {
    for (size_t i = 0; i < lexer.seenComments.size(); i++) {
      CommentNode *cmnt = mod.CurFuncCodeMemPool()->New<CommentNode>(&mod);
      cmnt->SetComment(lexer.seenComments[i]);
      SetSrcPos(cmnt, mplNum);
      blk->AddStatement(cmnt);
    }
    lexer.GetSeenComments().clear();
  }
}

bool MIRParser::ParseStmtBlockForVar(TokenKind stmtTK) {
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  MIRSymbol *st = fn->GetSymTab()->CreateSymbol(kScopeLocal);
  st->SetStorageClass(kScAuto);
  st->SetSKind(kStVar);
  if (stmtTK == TK_tempvar) {
    st->SetIsTmp(true);
  }
  if (!ParseDeclareVar(st)) {
    return false;
  }
  if (!fn->GetSymTab()->AddToStringSymbolMap(st)) {
    Error("duplicate declare symbol parse function ");
    return false;
  }
  return true;
}

bool MIRParser::ParseStmtBlockForVar() {
  return ParseStmtBlockForVar(TK_var);
}

bool MIRParser::ParseStmtBlockForTempVar() {
  return ParseStmtBlockForVar(TK_tempvar);
}

bool MIRParser::ParseStmtBlockForReg() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkPreg) {
    Error("expect %%preg after reg");
    return false;
  }
  PregIdx pregidx;
  if (!ParseRefPseudoReg(pregidx)) {
    return false;
  }
  MIRPreg *preg = mod.CurFunction()->GetPregTab()->PregFromPregIdx(pregidx);
  TyIdx tyidx(0);
  if (!ParseType(tyidx)) {
    Error("ParseDeclareVar failed when parsing the type");
    return false;
  }
  ASSERT(tyidx.GetIdx() > 0, "parse declare var failed ");
  MIRType *mirtype = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyidx);
  preg->SetMIRType(mirtype);
  if (lexer.GetTokenKind() == kTkIntconst) {
    int64 theintval = lexer.GetTheIntVal();
    if (theintval != 0 && theintval != 1) {
      Error("parseDeclareReg failed");
      return false;
    }
    preg->SetNeedRC(theintval == 0 ? false : true);
  } else {
    Error("parseDeclareReg failed");
    return false;
  }
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtBlockForType() {
  paramParseLocalType = true;
  if (!ParseTypedef()) {
    return false;
  }
  return true;
}

bool MIRParser::ParseStmtBlockForFrameSize() {
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after frameSize but get ");
    return false;
  }
  fn->SetFrameSize(lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtBlockForUpformalSize() {
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after upFormalSize but get ");
    return false;
  }
  fn->SetUpFormalSize(lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtBlockForModuleID() {
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after moduleid but get ");
    return false;
  }
  fn->SetModuleID(lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtBlockForFuncSize() {
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after funcSize but get ");
    return false;
  }
  fn->SetFuncSize(lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtBlockForFuncID() {
  // funcid is for debugging purpose
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after funcid but get ");
    return false;
  }
  fn->SetPuidxOrigin(lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseStmtBlockForFormalWordsTypeTagged() {
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  uint8 *addr = ParseWordsInfo(fn->GetUpFormalSize());
  if (addr == nullptr) {
    Error("parser error for formalwordstypetagged");
    return false;
  }
  fn->SetFormalWordsTypeTagged(addr);
  return true;
}

bool MIRParser::ParseStmtBlockForLocalWordsTypeTagged() {
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  uint8 *addr = ParseWordsInfo(fn->GetFrameSize());
  if (addr == nullptr) {
    Error("parser error for localWordsTypeTagged");
    return false;
  }
  fn->SetLocalWordsTypeTagged(addr);
  return true;
}

bool MIRParser::ParseStmtBlockForFormalWordsRefCounted() {
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  uint8 *addr = ParseWordsInfo(fn->GetUpFormalSize());
  if (addr == nullptr) {
    Error("parser error for formalwordsrefcounted");
    return false;
  }
  fn->SetFormalWordsRefCounted(addr);
  return true;
}

bool MIRParser::ParseStmtBlockForLocalWordsRefCounted() {
  MIRFunction *fn = paramCurrFuncForParseStmtBlock;
  uint8 *addr = ParseWordsInfo(fn->GetFrameSize());
  if (addr == nullptr) {
    Error("parser error for localwordsrefcounted");
    return false;
  }
  fn->SetLocalWordsRefCounted(addr);
  return true;
}

bool MIRParser::ParseStmtBlockForFuncInfo() {
  lexer.NextToken();
  if (!ParseFuncInfo()) {
    return false;
  }
  return true;
}

/* exprparser */
static Opcode GetUnaryOp(TokenKind tk) {
  switch (tk) {
#define UNARYOP(P) \
  case TK_##P:     \
    return OP_##P;
#include "unary_op.def"
#undef UNARYOP
    default:
      return kOpUndef;
  }
}

static Opcode GetBinaryOp(TokenKind tk) {
  switch (tk) {
#define BINARYOP(P) \
  case TK_##P:      \
    return OP_##P;
#include "binary_op.def"
#undef BINARYOP
    default:
      return kOpUndef;
  }
}

static Opcode GetConvertOp(TokenKind tk) {
  switch (tk) {
    case TK_ceil:
      return OP_ceil;
    case TK_cvt:
      return OP_cvt;
    case TK_floor:
      return OP_floor;
    case TK_round:
      return OP_round;
    case TK_trunc:
      return OP_trunc;
    default:
      return kOpUndef;
  }
}

bool MIRParser::ParseExprOneOperand(BaseNodePtr &expr) {
  if (lexer.GetTokenKind() != kTkLparen) {
    Error("expect ( parsing operand parsing unary ");
    return false;
  }
  lexer.NextToken();
  if (!ParseExpression(expr)) {
    Error("expect expression as openrand of unary expression ");
    return false;
  }
  if (lexer.GetTokenKind() != kTkRparen) {
    Error("expect ) parsing operand parsing unary ");
    return false;
  }
  return true;
}

bool MIRParser::ParseExprTwoOperand(BaseNodePtr &opnd0, BaseNodePtr &opnd1) {
  if (lexer.GetTokenKind() != kTkLparen) {
    Error("expect ( parsing operand parsing unary ");
    return false;
  }
  lexer.NextToken();
  if (!ParseExpression(opnd0)) {
    return false;
  }
  if (lexer.GetTokenKind() != kTkComa) {
    Error("expect , between two operands but get ");
    return false;
  }
  lexer.NextToken();
  if (!ParseExpression(opnd1)) {
    return false;
  }
  if (lexer.GetTokenKind() != kTkRparen) {
    Error("expect ) parsing operand parsing unary ");
    return false;
  }
  return true;
}

bool MIRParser::ParseExprNaryOperand(MapleVector<BaseNode*> &opndVec) {
  if (lexer.GetTokenKind() != kTkLparen) {
    Error("expect ( parsing operand parsing nary operands ");
    return false;
  }
  TokenKind tk = lexer.NextToken();
  while (tk != kTkRparen) {
    BaseNode *opnd = nullptr;
    if (!ParseExpression(opnd)) {
      Error("expect expression parsing nary operands ");
      return false;
    }
    opndVec.push_back(opnd);
    tk = lexer.GetTokenKind();
    if (tk == kTkComa) {
      tk = lexer.NextToken();
    }
  }
  return true;
}

bool MIRParser::ParseDeclaredSt(StIdx &stidx) {
  TokenKind varTk = lexer.GetTokenKind();
  stidx.SetFullIdx(0);
  GStrIdx stridx = GlobalTables::GetStrTable().GetStrIdxFromName(lexer.GetName());
  if (stridx == 0) {
    Error("symbol not declared ");
    stidx.SetFullIdx(0);
    return false;
  }
  if (varTk == kTkGname) {
    stidx = GlobalTables::GetGsymTable().GetStIdxFromStrIdx(stridx);
    if (stidx.FullIdx() == 0) {
      Error("global symbol not declared ");
      return false;
    }
  } else if (varTk == kTkLname) {
    stidx = mod.CurFunction()->GetSymTab()->GetStIdxFromStrIdx(stridx);
    if (stidx.FullIdx() == 0) {
      Error("local symbol not declared ");
      return false;
    }
  } else {
    Error("expect global/local name but get ");
    return false;
  }
  return true;
}

bool MIRParser::ParseDeclaredFunc(PUIdx &puidx) {
  GStrIdx stridx = GlobalTables::GetStrTable().GetStrIdxFromName(lexer.GetName());
  if (stridx == 0) {
    Error("symbol not declared ");
    return false;
  }
  StIdx stidx = GlobalTables::GetGsymTable().GetStIdxFromStrIdx(stridx);
  if (stidx.FullIdx() == 0) {
    Error("function symbol not declared ");
    return false;
  }
  MIRSymbol *st = GlobalTables::GetGsymTable().GetSymbolFromStidx(stidx.Idx());
  if (st->GetSKind() != kStFunc) {
    Error("function name not declared as function");
    return false;
  }
  MIRFunction *func = st->GetFunction();
  puidx = func->GetPuidx();
  return true;
}

bool MIRParser::ParseExprDread(BaseNodePtr &expr) {
  if (lexer.GetTokenKind() != TK_dread) {
    Error("expect dread but get ");
    return false;
  }
  AddrofNode *dexpr = mod.CurFuncCodeMemPool()->New<AddrofNode>(OP_dread);
  expr = dexpr;
  lexer.NextToken();
  TyIdx tyidx(0);
  bool parseRet = ParsePrimType(tyidx);
  if (tyidx == 0 || !parseRet) {
    Error("expect primitive type but get ");
    return false;
  }
  expr->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  StIdx stidx;
  if (!ParseDeclaredSt(stidx)) {
    return false;
  }
  if (stidx.FullIdx() == 0) {
    Error("expect a symbol ParseExprDread failed");
    return false;
  }
  dexpr->SetStIdx(stidx);
  TokenKind endtk = lexer.NextToken();
  if (endtk == kTkIntconst) {
    dexpr->SetFieldID(lexer.GetTheIntVal());
    lexer.NextToken();
  } else if (!IsDelimitationTK(endtk)) {
    Error("expect , or ) delimitation token but get ");
    return false;
  } else {
    dexpr->SetFieldID(0);
  }
  if (!dexpr->CheckNode(&mod)) {
    Error("dread is not legal");
    return false;
  }
  return true;
}

bool MIRParser::ParseExprRegread(BaseNodePtr &expr) {
  RegreadNode *regread = mod.CurFuncCodeMemPool()->New<RegreadNode>();
  expr = regread;
  lexer.NextToken();
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    return false;
  }
  if (tyidx == 0) {
    Error("expect primitive type but get ");
    return false;
  }
  expr->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  if (lexer.GetTokenKind() == kTkSpecialreg) {
    return ParseSpecialReg(regread->GetRegIdx());
  }
  if (lexer.GetTokenKind() == kTkPreg) {
    if (expr->GetPrimType() == PTY_ptr || expr->GetPrimType() == PTY_ref) {
      return ParseRefPseudoReg(regread->GetRegIdx());
    } else {
      return ParsePseudoReg(expr->GetPrimType(), regread->GetRegIdx());
    }
  }
  Error("expect special or pseudo register but get ");
  return false;
}

bool MIRParser::ParseExprConstval(BaseNodePtr &expr) {
  ConstvalNode *exprconst = mod.CurFuncCodeMemPool()->New<ConstvalNode>();
  TokenKind typeTk = lexer.NextToken();
  if (!IsPrimitiveType(typeTk)) {
    Error("expect type for GetConstVal but get ");
    return false;
  }
  exprconst->SetPrimType(GetPrimitiveType(typeTk));
  lexer.NextToken();
  MIRConst *constval = nullptr;
  if (!ParseScalarValue(constval, GlobalTables::GetTypeTable().GetPrimType(exprconst->GetPrimType()))) {
    Error("expect scalar type but get ");
    return false;
  }
  exprconst->SetConstVal(constval);
  expr = exprconst;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprConststr(BaseNodePtr &expr) {
  ConststrNode *strconst = mod.CurFuncCodeMemPool()->New<ConststrNode>();
  TokenKind tk = lexer.NextToken();
  if (!IsPrimitiveType(tk)) {
    Error("expect primitive type for conststr but get ");
    return false;
  }
  strconst->SetPrimType(GetPrimitiveType(tk));
  if (!IsAddress(strconst->GetPrimType())) {
    Error("expect primitive type for conststr but get ");
    return false;
  }
  tk = lexer.NextToken();
  if (tk != kTkString) {
    Error("expect string literal for conststr but get ");
    return false;
  }
  strconst->SetStrIdx(GlobalTables::GetUStrTable().GetOrCreateStrIdxFromName(lexer.GetName()));
  expr = strconst;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprConststr16(BaseNodePtr &expr) {
  Conststr16Node *str16Const = mod.CurFuncCodeMemPool()->New<Conststr16Node>();
  TokenKind tk = lexer.NextToken();
  if (!IsPrimitiveType(tk)) {
    Error("expect primitive type for conststr16 but get ");
    return false;
  }
  str16Const->SetPrimType(GetPrimitiveType(tk));
  if (!IsAddress(str16Const->GetPrimType())) {
    Error("expect primitive type for conststr16 but get ");
    return false;
  }
  tk = lexer.NextToken();
  if (tk != kTkString) {
    Error("expect string literal for conststr16 but get ");
    return false;
  }
  // UTF-16 strings in mpl files are presented as UTF-8 strings
  // to keep the printable chars in ascii form
  // so we need to do a UTF8ToUTF16 conversion
  std::string str = lexer.GetName();
  std::u16string str16;
  NameMangler::UTF8ToUTF16(str16, str);
  str16Const->SetStrIdx(GlobalTables::GetU16StrTable().GetOrCreateStrIdxFromName(str16));
  expr = str16Const;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprSizeoftype(BaseNodePtr &expr) {
  SizeoftypeNode *exprSizeoftype = mod.CurFuncCodeMemPool()->New<SizeoftypeNode>();
  TokenKind typeTk = lexer.NextToken();
  if (!IsPrimitiveType(typeTk)) {
    Error("expect type for GetConstVal but get ");
    return false;
  }
  exprSizeoftype->SetPrimType(GetPrimitiveType(typeTk));
  lexer.NextToken();
  TyIdx tyidx(0);
  if (!ParseType(tyidx)) {
    Error("expect type parsing array but get ");
    return false;
  }
  exprSizeoftype->SetTyIdx(tyidx);
  expr = exprSizeoftype;
  return true;
}

bool MIRParser::ParseExprFieldsDist(BaseNodePtr &expr) {
  TokenKind typeTk = lexer.NextToken();
  if (!IsPrimitiveType(typeTk)) {
    Error("expect type for GetConstVal but get ");
    return false;
  }
  FieldsDistNode *node = mod.CurFuncCodeMemPool()->New<FieldsDistNode>();
  node->SetPrimType(GetPrimitiveType(typeTk));
  lexer.NextToken();
  TyIdx tyIdx(0);
  if (!ParseType(tyIdx)) {
    Error("expect type parsing array but get ");
    return false;
  }
  node->SetTyIdx(tyIdx);
  TokenKind tk = lexer.GetTokenKind();
  if (tk != kTkIntconst) {
    Error("expect type int but get");
    return false;
  }
  node->SetFiledID1(lexer.GetTheIntVal());
  tk = lexer.NextToken();
  if (tk != kTkIntconst) {
    Error("expect type int but get");
    return false;
  }
  node->SetFiledID2(lexer.GetTheIntVal());
  lexer.NextToken();
  expr = node;
  return true;
}

bool MIRParser::ParseExprBinary(BaseNodePtr &expr) {
  Opcode opcode = GetBinaryOp(lexer.GetTokenKind());
  if (opcode == kOpUndef) {
    Error("expect add operator but get ");
    return false;
  }
  BinaryNode *addexpr = mod.CurFuncCodeMemPool()->New<BinaryNode>(opcode);
  if (!IsPrimitiveType(lexer.NextToken())) {
    Error("expect type parsing binary operator but get ");
    return false;
  }
  addexpr->SetPrimType(GetPrimitiveType(lexer.GetTokenKind()));
  lexer.NextToken();
  BaseNode *opnd0 = nullptr;
  BaseNode *opnd1 = nullptr;
  if (!ParseExprTwoOperand(opnd0, opnd1)) {
    return false;
  }
  addexpr->SetBOpnd(opnd0, 0);
  addexpr->SetBOpnd(opnd1, 1);
  expr = addexpr;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprCompare(BaseNodePtr &expr) {
  Opcode opcode = GetBinaryOp(lexer.GetTokenKind());
  CompareNode *addexpr = mod.CurFuncCodeMemPool()->New<CompareNode>(opcode);
  if (!IsPrimitiveType(lexer.NextToken())) {
    Error("expect type parsing compare operator but get ");
    return false;
  }
  addexpr->SetPrimType(GetPrimitiveType(lexer.GetTokenKind()));
  if (!IsPrimitiveType(lexer.NextToken())) {
    Error("expect operand type parsing compare operator but get ");
    return false;
  }
  addexpr->SetOpndType(GetPrimitiveType(lexer.GetTokenKind()));
  lexer.NextToken();
  BaseNode *opnd0 = nullptr;
  BaseNode *opnd1 = nullptr;
  if (!ParseExprTwoOperand(opnd0, opnd1)) {
    return false;
  }
  addexpr->SetBOpnd(opnd0, 0);
  addexpr->SetBOpnd(opnd1, 1);
  expr = addexpr;
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprDepositbits(BaseNodePtr &expr) {
  // syntax: depositbits <int-type> <boffset> <bSize> (<opnd0>, <opnd1>)
  if (lexer.GetTokenKind() != TK_depositbits) {
    Error("expect depositbits but get ");
    return false;
  }
  DepositbitsNode *dpsbNode = mod.CurFuncCodeMemPool()->New<DepositbitsNode>();
  expr = dpsbNode;
  PrimType ptyp = GetPrimitiveType(lexer.NextToken());
  if (!IsPrimitiveInteger(ptyp)) {
    Error("expect <int-type> but get ");
    return false;
  }
  dpsbNode->SetPrimType(ptyp);
  if (lexer.NextToken() != kTkIntconst) {
    Error("expect boffset but get ");
    return false;
  }
  dpsbNode->SetBitsOffset(lexer.GetTheIntVal());
  if (lexer.NextToken() != kTkIntconst) {
    Error("expect bSize but get ");
    return false;
  }
  dpsbNode->SetBitsSize(lexer.GetTheIntVal());
  lexer.NextToken();
  BaseNode *opnd0 = nullptr;
  BaseNode *opnd1 = nullptr;
  if (!ParseExprTwoOperand(opnd0, opnd1)) {
    Error("ParseExprDepositbits when parsing two operand");
    return false;
  }
  dpsbNode->SetBOpnd(opnd0, 0);
  dpsbNode->SetBOpnd(opnd1, 1);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprIreadIaddrof(IreadNode *expr) {
  // syntax : iread/iaddrof <prim-type> <type> <field-id> (<addr-expr>)
  if (!IsPrimitiveType(lexer.NextToken())) {
    Error("expect primitive type but get ");
    return false;
  }
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    return false;
  }
  expr->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  tyidx = TyIdx(0);
  if (!ParseDerivedType(tyidx)) {
    Error("ParseExprIreadIaddrof failed when paring derived type");
    return false;
  }
  expr->SetTyIdx(tyidx);
  if (lexer.GetTokenKind() == kTkIntconst) {
    expr->SetFieldID(lexer.theIntVal);
    lexer.NextToken();
  }
  BaseNode *opnd0 = nullptr;
  if (!ParseExprOneOperand(opnd0)) {
    return false;
  }
  expr->SetOpnd(opnd0);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprIread(BaseNodePtr &expr) {
  // syntax : iread <prim-type> <type> <field-id> (<addr-expr>)
  IreadNode *iexpr = mod.CurFuncCodeMemPool()->New<IreadNode>(OP_iread);
  if (!ParseExprIreadIaddrof(iexpr)) {
    Error("ParseExprIread failed when trying to parse addof");
    return false;
  }
  expr = iexpr;
  return true;
}

bool MIRParser::ParseExprIaddrof(BaseNodePtr &expr) {
  // syntax : iaddrof <prim-type> <type> <field-id> (<addr-expr>)
  IreadNode *iexpr = mod.CurFuncCodeMemPool()->New<IreadNode>(OP_iaddrof);
  if (!ParseExprIreadIaddrof(iexpr)) {
    Error("ParseExprIaddrof failed when trying to parse addof");
    return false;
  }
  expr = iexpr;
  return true;
}

bool MIRParser::ParseExprIreadoff(BaseNodePtr &expr) {
  // syntax : iread <prim-type> <offset> (<addr-expr>)
  IreadoffNode *ireadoff = mod.CurFuncCodeMemPool()->New<IreadoffNode>();
  expr = ireadoff;
  if (!IsPrimitiveType(lexer.NextToken())) {
    Error("expect primitive type but get ");
    return false;
  }
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    return false;
  }
  ireadoff->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  if (!IsPrimitiveScalar(ireadoff->GetPrimType())) {
    Error("only scalar types allowed for ireadoff");
    return false;
  }
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect offset but get ");
    return false;
  }
  ireadoff->SetOffset(lexer.GetTheIntVal());
  lexer.NextToken();
  BaseNode *opnd = nullptr;
  if (!ParseExprOneOperand(opnd)) {
    Error("ParseExprIreadoff when paring one operand");
    return false;
  }
  ireadoff->SetOpnd(opnd);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprIreadFPoff(BaseNodePtr &expr) {
  // syntax : iread <prim-type> <offset>
  IreadFPoffNode *ireadoff = mod.CurFuncCodeMemPool()->New<IreadFPoffNode>();
  expr = ireadoff;
  if (!IsPrimitiveType(lexer.NextToken())) {
    Error("expect primitive type but get ");
    return false;
  }
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    return false;
  }
  ireadoff->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  if (!IsPrimitiveScalar(ireadoff->GetPrimType())) {
    Error("only scalar types allowed for ireadoff");
    return false;
  }
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect offset but get ");
    return false;
  }
  ireadoff->SetOffset(lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprAddrof(BaseNodePtr &expr) {
  // syntax: addrof <prim-type> <var-name> <field-id>
  AddrofNode *addrofNode = mod.CurFuncCodeMemPool()->New<AddrofNode>(OP_addrof);
  expr = addrofNode;
  if (lexer.GetTokenKind() != TK_addrof) {
    Error("expect addrof but get ");
    return false;
  }
  lexer.NextToken();
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    Error("expect primitive type but get ");
    return false;
  }
  addrofNode->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  StIdx stidx;
  if (!ParseDeclaredSt(stidx)) {
    return false;
  }
  if (stidx.FullIdx() == 0) {
    Error("expect symbol ParseExprAddroffunc");
    return false;
  }
  addrofNode->SetStIdx(stidx);
  TokenKind tk = lexer.NextToken();
  if (IsDelimitationTK(tk)) {
    addrofNode->SetFieldID(0);
  } else if (tk == kTkIntconst) {
    addrofNode->SetFieldID(lexer.GetTheIntVal());
    lexer.NextToken();
  } else {
    addrofNode->SetFieldID(0);
  }
  return true;
}

bool MIRParser::ParseExprAddroffunc(BaseNodePtr &expr) {
  AddroffuncNode *addroffuncNode = mod.CurFuncCodeMemPool()->New<AddroffuncNode>();
  expr = addroffuncNode;
  TokenKind tk = lexer.NextToken();
  if (tk != TK_a32 && tk != TK_a64 && tk != TK_ptr) {
    Error("expect address primitive type but get ");
    return false;
  }
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    Error("ParseExprAddroffunc failed when parsing primitive type");
    return false;
  }
  addroffuncNode->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  if (lexer.GetTokenKind() != kTkFname) {
    Error("expect function name but get ");
    return false;
  }
  PUIdx pidx;
  if (!ParseDeclaredFunc(pidx)) {
    if (mod.GetFlavor() < kMmpl) {
      Error("expect .mmpl file");
      return false;
    }
    pidx = EnterUndeclaredFunction();
  }
  addroffuncNode->SetPUIdx(pidx);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprAddroflabel(BaseNodePtr &expr) {
  // syntax: addroflabel <prim-type> <label>
  AddroflabelNode *addroflabelNode = mod.CurFuncCodeMemPool()->New<AddroflabelNode>();
  expr = addroflabelNode;
  TokenKind tk = lexer.NextToken();
  if (tk != TK_a32 && tk != TK_a64 && tk != TK_ptr) {
    Error("expect address primitive type but get ");
    return false;
  }
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    Error("ParseExprAddroflabel failed");
    return false;
  }
  addroflabelNode->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  if (lexer.GetTokenKind() != TK_label) {
    Error("expect label but get ");
    return false;
  }
  LabelIdx lblIdx = mod.CurFunction()->GetOrCreateLableIdxFromName(lexer.GetName());
  addroflabelNode->SetOffset(lblIdx);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprUnary(BaseNodePtr &expr) {
  // syntax op <prim-type> <label>
  Opcode op = GetUnaryOp(lexer.GetTokenKind());
  if (op == kOpUndef) {
    Error("expect unary op but get ");
    return false;
  }
  lexer.NextToken();
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    Error("expect primitive parsing unary operator ");
    return false;
  }
  UnaryNode *unaryNode = mod.CurFuncCodeMemPool()->New<UnaryNode>(op);
  expr = unaryNode;
  unaryNode->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  BaseNode *opnd = nullptr;
  if (!ParseExprOneOperand(opnd)) {
    Error("parsing unary wrong ");
    return false;
  }
  unaryNode->SetOpnd(opnd);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprGCMalloc(BaseNodePtr &expr) {
  // syntax op <prim-type> <type>
  TokenKind tk = lexer.GetTokenKind();
  if (tk != TK_gcmalloc && tk != TK_gcpermalloc) {
    Error("expect gcmalloc or gcpermalloc but get ");
    return false;
  }
  Opcode op = (tk == TK_gcmalloc) ? OP_gcmalloc : OP_gcpermalloc;
  lexer.NextToken();
  TyIdx ptyidx(0);
  if (IsPrimitiveType(lexer.GetTokenKind())) {
    if (!ParsePrimType(ptyidx)) {
      return false;
    }
  }
  TyIdx tyidx(0);
  if (!ParseType(tyidx)) {
    Error("expect type parsing unary operator ");
    return false;
  }
  GCMallocNode *mallocNode = mod.CurFuncCodeMemPool()->New<GCMallocNode>(op);
  expr = mallocNode;
  mallocNode->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(ptyidx));
  mallocNode->SetOrigPType(mallocNode->GetPrimType());
  mallocNode->SetTyIdx(tyidx);
  return true;
}

bool MIRParser::ParseExprJarray(BaseNodePtr &expr) {
  // syntax op <prim-type> <java-array-type> <label>
  Opcode op = GetUnaryOp(lexer.GetTokenKind());
  if (op != OP_gcmallocjarray && op != OP_gcpermallocjarray) {
    Error("expect gcmallocjarray or gcpermallocjarray but get ");
    return false;
  }
  TyIdx ptyidx(0);
  lexer.NextToken();
  if (IsPrimitiveType(lexer.GetTokenKind())) {
    if (!ParsePrimType(ptyidx)) {
      return false;
    }
  }
  TyIdx tyidx(0);
  if (!ParseType(tyidx)) {
    Error("expect primitive parsing unary operator ");
    return false;
  }
  JarrayMallocNode *jarrayNode = mod.CurFuncCodeMemPool()->New<JarrayMallocNode>(op);
  expr = jarrayNode;
  jarrayNode->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(ptyidx));
  jarrayNode->SetTyIdx(tyidx);
  BaseNode *opnd = nullptr;
  if (!ParseExprOneOperand(opnd)) {
    Error("parsing unary wrong ");
    return false;
  }
  jarrayNode->SetOpnd(opnd);
  lexer.NextToken();
  return true;
}

// parse extractbits, sext, zext
bool MIRParser::ParseExprExtractbits(BaseNodePtr &expr) {
  // extractbits <int-type> <boffset> <bSize> (<opnd0>)
  Opcode op = GetUnaryOp(lexer.GetTokenKind());
  if (op == kOpUndef) {
    Error("expect unary op but get ");
    return false;
  }
  ExtractbitsNode *extrctNode = mod.CurFuncCodeMemPool()->New<ExtractbitsNode>(op);
  expr = extrctNode;
  lexer.NextToken();
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    Error("expect int type after extractbits after");
    return false;
  }
  PrimType ptyp = GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx);
  if (!IsPrimitiveInteger(ptyp)) {
    Error("sematical error expect int type for extractbits");
    return false;
  }
  extrctNode->SetPrimType(ptyp);
  if (op == OP_extractbits) {
    if (lexer.GetTokenKind() != kTkIntconst) {
      Error("expect boffset but get ");
      return false;
    }
    extrctNode->SetBitsOffset(lexer.GetTheIntVal());
    lexer.NextToken();
  }
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect bSize but get ");
    return false;
  }
  extrctNode->SetBitsSize(lexer.GetTheIntVal());
  lexer.NextToken();
  BaseNode *opnd = nullptr;
  if (!ParseExprOneOperand(opnd)) {
    Error("ParseExprExtractbits failed");
    return false;
  }
  extrctNode->SetOpnd(opnd);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprTyconvert(BaseNodePtr &expr) {
  Opcode op = GetConvertOp(lexer.GetTokenKind());
  if (op == kOpUndef) {
    Error("expect covertion operator but get ");
    return false;
  }
  TypeCvtNode *cvtNode = mod.CurFuncCodeMemPool()->New<TypeCvtNode>(op);
  expr = static_cast<BaseNode*>(cvtNode);
  PrimType totype = GetPrimitiveType(lexer.NextToken());
  if (totype == kPtyInvalid) {
    Error("expect to-type parsing conversion");
    return false;
  }
  cvtNode->SetPrimType(totype);
  lexer.NextToken();
  PrimType fromType = GetPrimitiveType(lexer.GetTokenKind());
  if (fromType == kPtyInvalid) {
    Error("expect type parsing conversion ");
    return false;
  }
  cvtNode->SetFromType(fromType);
  lexer.NextToken();
  BaseNode *opnd = nullptr;
  if (!ParseExprOneOperand(opnd)) {
    return false;
  }
  cvtNode->SetOpnd(opnd);
  if (op == OP_retype) {
    cvtNode->SetFromType(opnd->GetPrimType());
  }
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprRetype(BaseNodePtr &expr) {
  RetypeNode *cvtNode = mod.CurFuncCodeMemPool()->New<RetypeNode>();
  expr = static_cast<BaseNode*>(cvtNode);
  PrimType totype = GetPrimitiveType(lexer.NextToken());
  if (totype == kPtyInvalid) {
    Error("expect to-type parsing conversion");
    return false;
  }
  cvtNode->SetPrimType(totype);
  lexer.NextToken();
  TyIdx tyidx(0);
  if (!ParseDerivedType(tyidx)) {
    Error("ParseExprRetype failed when parsing derived type ");
    return false;
  }
  cvtNode->SetTyIdx(tyidx);
  BaseNode *opnd = nullptr;
  if (!ParseExprOneOperand(opnd)) {
    return false;
  }
  cvtNode->SetOpnd(opnd);
  cvtNode->SetFromType(opnd->GetPrimType());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprTernary(BaseNodePtr &expr) {
  if (lexer.GetTokenKind() != TK_select) {
    Error("expect select but get ");
    return false;
  }
  TernaryNode *ternaryNode = mod.CurFuncCodeMemPool()->New<TernaryNode>(OP_select);
  expr = ternaryNode;
  lexer.NextToken();
  TyIdx tyidx(0);
  if (!ParsePrimType(tyidx)) {
    Error("expect primtype type but get ");
    return false;
  }
  ternaryNode->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  MapleVector<BaseNode*> opndVec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
  if (!ParseExprNaryOperand(opndVec)) {
    Error("ParseExprTernary failed");
    return false;
  }
  if (opndVec.size() != 3) {  // expect number of operands to be 3
    Error("expect 3 operands for ternary operator ");
    return false;
  }
  ternaryNode->SetOpnd(opndVec[0], 0);
  ternaryNode->SetOpnd(opndVec[1], 1);
  ternaryNode->SetOpnd(opndVec[2], 2);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseExprArray(BaseNodePtr &expr) {
  // syntax: array <addr-type> <array-type> (<opnd0>, <opnd1>, . . . , <opndn>)
  ArrayNode *arrayNode = mod.CurFuncCodeMemPool()->New<ArrayNode>(&mod);
  expr = arrayNode;
  if (lexer.GetTokenKind() != TK_array) {
    Error("expect array but get ");
    return false;
  }
  lexer.NextToken();
  if (lexer.GetTokenKind() == kTkIntconst) {
    if (lexer.GetTheIntVal() == 1) {
      arrayNode->SetBoundsCheck(true);
    } else if (lexer.GetTheIntVal() == 0) {
      arrayNode->SetBoundsCheck(false);
    } else {
      Error("expect bounds_check(0/1) but get ");
      return false;
    }
  }
  lexer.NextToken();
  TyIdx tyidx;
  if (!ParsePrimType(tyidx)) {
    Error("expect address type but get ");
    return false;
  }
  arrayNode->SetPrimType(GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(tyidx));
  tyidx = TyIdx(0);
  if (!ParseType(tyidx)) {
    Error("expect type parsing array but get ");
    return false;
  }
  arrayNode->SetTyIdx(tyidx);
  // number of operand can not be zero
  MapleVector<BaseNode*> opndVec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
  if (!ParseExprNaryOperand(opndVec)) {
    Error("ParseExprArray failed");
    return false;
  }
  if (opndVec.empty()) {
    Error("sematic error operands number of array expression is 0 ");
    return false;
  }
  arrayNode->SetNOpnd(opndVec);
  arrayNode->SetNumOpnds(opndVec.size());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseIntrinsicId(IntrinsicopNode *intrnopnode) {
  MIRIntrinsicID intrinid = GetIntrinsicId(lexer.GetTokenKind());
  if (intrinid <= INTRN_UNDEFINED || intrinid >= INTRN_LAST) {
    Error("wrong intrinsic id ");
    return false;
  }
  intrnopnode->SetIntrinsic(intrinid);
  return true;
}

bool MIRParser::ParseExprIntrinsicop(BaseNodePtr &expr) {
  // syntax: intrinsicop <prim-type> <intrinsic> (<opnd0>, ..., <opndn>)
  // syntax: intrinsicopwithtype <prim-type> <intrinsic> (<opnd0>, ..., <opndn>)
  Opcode opCode = OP_intrinsicopwithtype;
  TokenKind kind = lexer.GetTokenKind();
  if (kind == TK_intrinsicop) {
    opCode = OP_intrinsicop;
  } else if (kind != TK_intrinsicopwithtype) {
    Error("expect intrinsicop(withtype) but get ");
    return false;
  }
  lexer.NextToken();
  TyIdx pTyIdx(0);
  if (!ParsePrimType(pTyIdx)) {
    Error("ParseExprIntrinsicop(withtype) failed when parsing type");
    return false;
  }

  TyIdx tyIdx(0);
  if (opCode == OP_intrinsicopwithtype && !ParseDerivedType(tyIdx)) {
    Error("ParseExprIntrinsicop(withtype) failed when parsing derived type ");
    return false;
  }
  IntrinsicopNode *intrnopnode = mod.CurFuncCodeMemPool()->New<IntrinsicopNode>(
      &mod, opCode, GlobalTables::GetTypeTable().GetPrimTypeFromTyIdx(pTyIdx), tyIdx);
  expr = intrnopnode;
  if (!ParseIntrinsicId(intrnopnode)) {
    return false;
  }
  // number of operand can not be zero
  lexer.NextToken();
  MapleVector<BaseNode*> opndVec(mod.CurFuncCodeMemPoolAllocator()->Adapter());
  if (!ParseExprNaryOperand(opndVec)) {
    Error("ParseExprIntrinsicop(withtype) failed");
    return false;
  }
  intrnopnode->SetNOpnd(opndVec);
  intrnopnode->SetNumOpnds(opndVec.size());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseScalarValue(MIRConstPtr &stype, MIRType *type) {
  PrimType ptp = type->GetPrimType();
  if (IsPrimitiveInteger(ptp) || IsPrimitiveDynType(ptp) || ptp == PTY_gen) {
    if (lexer.GetTokenKind() != kTkIntconst) {
      Error("constant value incompatible with integer type at ");
      return false;
    }
    stype = mod.GetMemPool()->New<MIRIntConst>(lexer.GetTheIntVal(), type);
  } else if (ptp == PTY_f32) {
    if (lexer.GetTokenKind() != kTkFloatconst) {
      Error("constant value incompatible with single-precision float type at ");
      return false;
    }
    MIRFloatConst *fconst = GlobalTables::GetFpConstTable().GetOrCreateFloatConst(lexer.GetTheFloatVal());
    stype = fconst;
  } else if (ptp == PTY_f64) {
    if (lexer.GetTokenKind() != kTkDoubleconst && lexer.GetTokenKind() != kTkIntconst) {
      Error("constant value incompatible with double-precision float type at ");
      return false;
    }
    MIRDoubleConst *dconst = GlobalTables::GetFpConstTable().GetOrCreateDoubleConst(lexer.GetTheDoubleVal());
    stype = dconst;
  } else {
    return false;
  }
  return true;
}

bool MIRParser::ParseConstAddrLeafExpr(MIRConstPtr &cexpr, MIRType *type) {
  BaseNode *expr = nullptr;
  if (!ParseExpression(expr)) {
    return false;
  }
  CHECK_FATAL(expr != nullptr, "null ptr check");
  if (expr->GetOpCode() != OP_addrof && expr->GetOpCode() != OP_addroffunc && expr->GetOpCode() != OP_conststr &&
      expr->GetOpCode() != OP_conststr16) {
    Error("ParseConstAddrLeafExpr expects one of OP_addrof, OP_addroffunc, OP_conststr and OP_conststr16");
    return false;
  }
  if (expr->GetOpCode() == OP_addrof) {
    AddrofNode *anode = static_cast<AddrofNode*>(expr);
    MIRFunction *currfn = static_cast<MIRFunction*>(mod.CurFunction());
    MIRSymbol *var = currfn->GetLocalOrGlobalSymbol(anode->GetStIdx());
    var->SetNeedForwDecl();
    TyIdx ptyidx = var->GetTyIdx();
    MIRPtrType ptrtype(ptyidx, (mod.IsJavaModule() ? PTY_ref : PTY_ptr));
    ptyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&ptrtype);
    MIRType *exprty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptyidx);
    cexpr = mod.CurFuncCodeMemPool()->New<MIRAddrofConst>(anode->GetStIdx(), anode->GetFieldID(), exprty);
  } else if (expr->GetOpCode() == OP_addroffunc) {
    AddroffuncNode *aof = static_cast<AddroffuncNode*>(expr);
    MIRFunction *f = GlobalTables::GetFunctionTable().GetFunctionFromPuidx(aof->GetPUIdx());
    MIRSymbol *fname = f->GetFuncSymbol();
    TyIdx ptyidx = fname->GetTyIdx();
    MIRPtrType ptrtype(ptyidx);
    ptyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&ptrtype);
    MIRType *exprty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptyidx);
    cexpr = mod.CurFuncCodeMemPool()->New<MIRAddroffuncConst>(aof->GetPUIdx(), exprty);
  } else if (expr->GetOpCode() == OP_conststr) {
    ConststrNode *cs = static_cast<ConststrNode*>(expr);
    UStrIdx stridx = cs->GetStrIdx();
    TyIdx ptyidx = GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(PTY_u8))->GetTypeIndex();
    MIRPtrType ptrtype(ptyidx);
    ptyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&ptrtype);
    MIRType *exprty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptyidx);
    cexpr = mod.CurFuncCodeMemPool()->New<MIRStrConst>(stridx, exprty);
  } else {
    Conststr16Node *cs = static_cast<Conststr16Node*>(expr);
    U16StrIdx stridx = cs->GetStrIdx();
    TyIdx ptyidx = GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(PTY_u16))->GetTypeIndex();
    MIRPtrType ptrtype(ptyidx);
    ptyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&ptrtype);
    MIRType *exprty = GlobalTables::GetTypeTable().GetTypeFromTyIdx(ptyidx);
    cexpr = mod.CurFuncCodeMemPool()->New<MIRStr16Const>(stridx, exprty);
  }
  return true;
}

bool MIRParser::ParseExpression(BaseNodePtr &expr) {
  TokenKind tk = lexer.GetTokenKind();
  std::map<TokenKind, MIRParser::FuncPtrParseExpr>::iterator itFuncPtr = funcPtrMapForParseExpr.find(tk);
  if (itFuncPtr == funcPtrMapForParseExpr.end()) {
    Error("expect expression but get ");
    return false;
  } else {
    if (!(this->*(itFuncPtr->second))(expr)) {
      return false;
    }
  }
  return true;
}

std::map<TokenKind, MIRParser::FuncPtrParseExpr> MIRParser::InitFuncPtrMapForParseExpr() {
  std::map<TokenKind, MIRParser::FuncPtrParseExpr> funcPtrMap;
  funcPtrMap[TK_addrof] = &MIRParser::ParseExprAddrof;
  funcPtrMap[TK_addroffunc] = &MIRParser::ParseExprAddroffunc;
  funcPtrMap[TK_addroflabel] = &MIRParser::ParseExprAddroflabel;
  funcPtrMap[TK_abs] = &MIRParser::ParseExprUnary;
  funcPtrMap[TK_bnot] = &MIRParser::ParseExprUnary;
  funcPtrMap[TK_lnot] = &MIRParser::ParseExprUnary;
  funcPtrMap[TK_neg] = &MIRParser::ParseExprUnary;
  funcPtrMap[TK_recip] = &MIRParser::ParseExprUnary;
  funcPtrMap[TK_sqrt] = &MIRParser::ParseExprUnary;
  funcPtrMap[TK_alloca] = &MIRParser::ParseExprUnary;
  funcPtrMap[TK_malloc] = &MIRParser::ParseExprUnary;
  funcPtrMap[TK_gcmalloc] = &MIRParser::ParseExprGCMalloc;
  funcPtrMap[TK_gcpermalloc] = &MIRParser::ParseExprGCMalloc;
  funcPtrMap[TK_gcmallocjarray] = &MIRParser::ParseExprJarray;
  funcPtrMap[TK_gcpermallocjarray] = &MIRParser::ParseExprJarray;
  funcPtrMap[TK_sext] = &MIRParser::ParseExprExtractbits;
  funcPtrMap[TK_zext] = &MIRParser::ParseExprExtractbits;
  funcPtrMap[TK_extractbits] = &MIRParser::ParseExprExtractbits;
  funcPtrMap[TK_ceil] = &MIRParser::ParseExprTyconvert;
  funcPtrMap[TK_cvt] = &MIRParser::ParseExprTyconvert;
  funcPtrMap[TK_floor] = &MIRParser::ParseExprTyconvert;
  funcPtrMap[TK_round] = &MIRParser::ParseExprTyconvert;
  funcPtrMap[TK_trunc] = &MIRParser::ParseExprTyconvert;
  funcPtrMap[TK_retype] = &MIRParser::ParseExprRetype;
  funcPtrMap[TK_select] = &MIRParser::ParseExprTernary;
  funcPtrMap[TK_array] = &MIRParser::ParseExprArray;
  funcPtrMap[TK_intrinsicop] = &MIRParser::ParseExprIntrinsicop;
  funcPtrMap[TK_intrinsicopwithtype] = &MIRParser::ParseExprIntrinsicop;
  funcPtrMap[TK_constval] = &MIRParser::ParseExprConstval;
  funcPtrMap[TK_conststr] = &MIRParser::ParseExprConststr;
  funcPtrMap[TK_conststr16] = &MIRParser::ParseExprConststr16;
  funcPtrMap[TK_sizeoftype] = &MIRParser::ParseExprSizeoftype;
  funcPtrMap[TK_fieldsdist] = &MIRParser::ParseExprFieldsDist;
  funcPtrMap[TK_iaddrof] = &MIRParser::ParseExprIaddrof;
  funcPtrMap[TK_iread] = &MIRParser::ParseExprIread;
  funcPtrMap[TK_ireadoff] = &MIRParser::ParseExprIreadoff;
  funcPtrMap[TK_ireadfpoff] = &MIRParser::ParseExprIreadFPoff;
  funcPtrMap[TK_dread] = &MIRParser::ParseExprDread;
  funcPtrMap[TK_regread] = &MIRParser::ParseExprRegread;
  funcPtrMap[TK_add] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_ashr] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_band] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_bior] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_bxor] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_cand] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_cior] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_div] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_land] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_lior] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_lshr] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_max] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_min] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_mul] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_rem] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_shl] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_sub] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_CG_array_elem_add] = &MIRParser::ParseExprBinary;
  funcPtrMap[TK_cmp] = &MIRParser::ParseExprCompare;
  funcPtrMap[TK_cmpl] = &MIRParser::ParseExprCompare;
  funcPtrMap[TK_cmpg] = &MIRParser::ParseExprCompare;
  funcPtrMap[TK_eq] = &MIRParser::ParseExprCompare;
  funcPtrMap[TK_ge] = &MIRParser::ParseExprCompare;
  funcPtrMap[TK_gt] = &MIRParser::ParseExprCompare;
  funcPtrMap[TK_le] = &MIRParser::ParseExprCompare;
  funcPtrMap[TK_lt] = &MIRParser::ParseExprCompare;
  funcPtrMap[TK_ne] = &MIRParser::ParseExprCompare;
  funcPtrMap[TK_depositbits] = &MIRParser::ParseExprDepositbits;
  return funcPtrMap;
}

std::map<TokenKind, MIRParser::FuncPtrParseStmt> MIRParser::InitFuncPtrMapForParseStmt() {
  std::map<TokenKind, MIRParser::FuncPtrParseStmt> funcPtrMap;
  funcPtrMap[TK_dassign] = &MIRParser::ParseStmtDassign;
  funcPtrMap[TK_iassign] = &MIRParser::ParseStmtIassign;
  funcPtrMap[TK_iassignoff] = &MIRParser::ParseStmtIassignoff;
  funcPtrMap[TK_iassignfpoff] = &MIRParser::ParseStmtIassignFPoff;
  funcPtrMap[TK_regassign] = &MIRParser::ParseStmtRegassign;
  funcPtrMap[TK_doloop] = &MIRParser::ParseStmtDoloop;
  funcPtrMap[TK_foreachelem] = &MIRParser::ParseStmtForeachelem;
  funcPtrMap[TK_dowhile] = &MIRParser::ParseStmtDowhile;
  funcPtrMap[TK_if] = &MIRParser::ParseStmtIf;
  funcPtrMap[TK_while] = &MIRParser::ParseStmtWhile;
  funcPtrMap[TK_goto] = &MIRParser::ParseStmtGoto;
  funcPtrMap[TK_brfalse] = &MIRParser::ParseStmtBr;
  funcPtrMap[TK_brtrue] = &MIRParser::ParseStmtBr;
  funcPtrMap[TK_switch] = &MIRParser::ParseStmtSwitch;
  funcPtrMap[TK_rangegoto] = &MIRParser::ParseStmtRangegoto;
  funcPtrMap[TK_multiway] = &MIRParser::ParseStmtMultiway;
  funcPtrMap[TK_call] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_virtualcall] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_virtualicall] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_superclasscall] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_interfacecall] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_interfaceicall] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_customcall] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_polymorphiccall] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_callinstant] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_virtualcallinstant] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_superclasscallinstant] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_interfacecallinstant] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_callassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_virtualcallassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_virtualicallassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_superclasscallassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_interfacecallassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_interfaceicallassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_customcallassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_polymorphiccallassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_callinstantassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_virtualcallinstantassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_superclasscallinstantassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_interfacecallinstantassigned] = &MIRParser::ParseStmtCall;
  funcPtrMap[TK_icall] = &MIRParser::ParseStmtIcall;
  funcPtrMap[TK_icallassigned] = &MIRParser::ParseStmtIcallassigned;
  funcPtrMap[TK_intrinsiccall] = &MIRParser::ParseStmtIntrinsiccall;
  funcPtrMap[TK_intrinsiccallassigned] = &MIRParser::ParseStmtIntrinsiccallassigned;
  funcPtrMap[TK_xintrinsiccall] = &MIRParser::ParseStmtIntrinsiccall;
  funcPtrMap[TK_xintrinsiccallassigned] = &MIRParser::ParseStmtIntrinsiccallassigned;
  funcPtrMap[TK_intrinsiccallwithtype] = &MIRParser::ParseStmtIntrinsiccallwithtype;
  funcPtrMap[TK_intrinsiccallwithtypeassigned] = &MIRParser::ParseStmtIntrinsiccallwithtypeassigned;
  funcPtrMap[TK_return] = &MIRParser::ParseNaryStmtReturn;
  funcPtrMap[TK_jstry] = &MIRParser::ParseStmtJsTry;
  funcPtrMap[TK_try] = &MIRParser::ParseStmtTry;
  funcPtrMap[TK_catch] = &MIRParser::ParseStmtCatch;
  funcPtrMap[TK_syncenter] = &MIRParser::ParseNaryStmtSyncEnter;
  funcPtrMap[TK_syncexit] = &MIRParser::ParseNaryStmtSyncExit;
  funcPtrMap[TK_throw] = &MIRParser::ParseUnaryStmtThrow;
  funcPtrMap[TK_decref] = &MIRParser::ParseUnaryStmtDecRef;
  funcPtrMap[TK_incref] = &MIRParser::ParseUnaryStmtIncRef;
  funcPtrMap[TK_decrefreset] = &MIRParser::ParseUnaryStmtDecRefReset;
  funcPtrMap[TK_jscatch] = &MIRParser::ParseStmtMarker;
  funcPtrMap[TK_finally] = &MIRParser::ParseStmtMarker;
  funcPtrMap[TK_cleanuptry] = &MIRParser::ParseStmtMarker;
  funcPtrMap[TK_endtry] = &MIRParser::ParseStmtMarker;
  funcPtrMap[TK_retsub] = &MIRParser::ParseStmtMarker;
  funcPtrMap[TK_membaracquire] = &MIRParser::ParseStmtMarker;
  funcPtrMap[TK_membarrelease] = &MIRParser::ParseStmtMarker;
  funcPtrMap[TK_membarstoreload] = &MIRParser::ParseStmtMarker;
  funcPtrMap[TK_membarstorestore] = &MIRParser::ParseStmtMarker;
  funcPtrMap[TK_gosub] = &MIRParser::ParseStmtGosub;
  funcPtrMap[TK_eval] = &MIRParser::ParseUnaryStmtEval;
  funcPtrMap[TK_free] = &MIRParser::ParseUnaryStmtFree;
  funcPtrMap[TK_assertnonnull] = &MIRParser::ParseUnaryStmtAssertNonNull;
  funcPtrMap[TK_assertge] = &MIRParser::ParseBinaryStmtAssertGE;
  funcPtrMap[TK_assertlt] = &MIRParser::ParseBinaryStmtAssertLT;
  funcPtrMap[TK_label] = &MIRParser::ParseStmtLabel;
  funcPtrMap[TK_LOC] = &MIRParser::ParseLoc;
  funcPtrMap[TK_ALIAS] = &MIRParser::ParseAlias;
  return funcPtrMap;
}

std::map<TokenKind, MIRParser::FuncPtrParseStmtBlock> MIRParser::InitFuncPtrMapForParseStmtBlock() {
  std::map<TokenKind, MIRParser::FuncPtrParseStmtBlock> funcPtrMap;
  funcPtrMap[TK_var] = &MIRParser::ParseStmtBlockForVar;
  funcPtrMap[TK_tempvar] = &MIRParser::ParseStmtBlockForTempVar;
  funcPtrMap[TK_reg] = &MIRParser::ParseStmtBlockForReg;
  funcPtrMap[TK_type] = &MIRParser::ParseStmtBlockForType;
  funcPtrMap[TK_framesize] = &MIRParser::ParseStmtBlockForFrameSize;
  funcPtrMap[TK_upformalsize] = &MIRParser::ParseStmtBlockForUpformalSize;
  funcPtrMap[TK_moduleid] = &MIRParser::ParseStmtBlockForModuleID;
  funcPtrMap[TK_funcsize] = &MIRParser::ParseStmtBlockForFuncSize;
  funcPtrMap[TK_funcid] = &MIRParser::ParseStmtBlockForFuncID;
  funcPtrMap[TK_formalwordstypetagged] = &MIRParser::ParseStmtBlockForFormalWordsTypeTagged;
  funcPtrMap[TK_localwordstypetagged] = &MIRParser::ParseStmtBlockForLocalWordsTypeTagged;
  funcPtrMap[TK_formalwordsrefcounted] = &MIRParser::ParseStmtBlockForFormalWordsRefCounted;
  funcPtrMap[TK_localwordsrefcounted] = &MIRParser::ParseStmtBlockForLocalWordsRefCounted;
  funcPtrMap[TK_funcinfo] = &MIRParser::ParseStmtBlockForFuncInfo;
  return funcPtrMap;
}

void MIRParser::SetSrcPos(StmtNodePtr stmt, uint32 mplNum) {
  stmt->GetSrcPos().SetFileNum(lastFileNum);
  stmt->GetSrcPos().SetLineNum(lastLineNum);
  stmt->GetSrcPos().SetMplLineNum(mplNum);
}

}  // namespace maple
