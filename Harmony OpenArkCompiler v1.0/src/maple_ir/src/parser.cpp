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
#include <climits>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include "mir_parser.h"
#include "mir_function.h"
#include "name_mangler.h"
#include "opcode_info.h"
#include "mir_pragma.h"
#include "bin_mplt.h"
#include "option.h"
#include "string_utils.h"

namespace maple {
constexpr char kLexerStringSp[] = "SP";
constexpr char kLexerStringFp[] = "FP";
constexpr char kLexerStringGp[] = "GP";
constexpr char kLexerStringThrownval[] = "thrownval";
constexpr char kLexerStringRetval[] = "retval";
std::map<TokenKind, MIRParser::FuncPtrParseMIRForElem> MIRParser::funcPtrMapForParseMIR =
    MIRParser::InitFuncPtrMapForParseMIR();

MIRFunction *MIRParser::CreateDummyFunction() {
  GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName("__$$__");
  maple::MIRBuilder mirBuilder(&mod);
  MIRSymbol *funcSt = mirBuilder.CreateSymbol(TyIdx(0), strIdx, kStFunc, kScUnused, nullptr, kScopeGlobal);
  CHECK_FATAL(funcSt != nullptr, "Failed to create MIRSymbol");
  // Don't add the function to the function table.
  // It appears Storage class kScUnused is not honored.
  MIRFunction *func = mirBuilder.CreateFunction(funcSt->GetStIdx(), false);
  CHECK_FATAL(func != nullptr, "Failed to create MIRFunction");
  func->SetPuidxOrigin(func->GetPuidx());
  MIRType *returnType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(PTY_void));
  func->SetReturnTyIdx(returnType->GetTypeIndex());
  func->SetClassTyIdx(0);
  func->SetBaseClassFuncNames(strIdx);
  funcSt->SetFunction(func);
  return func;
}

void MIRParser::ResetMaxPregNo(MIRFunction *func) {
  ASSERT(func != nullptr, "func is null");
  for (uint32 i = 0; i < func->GetFormalCount(); i++) {
    MIRSymbol *formalSt = func->GetFormal(i);
    if (formalSt->IsPreg()) {
      uint32 pRegNo =
          static_cast<uint32>(formalSt->GetPreg()->GetPregNo());  // no special register appears in the formals
      if (pRegNo > maxPregNo) {
        maxPregNo = pRegNo;
      }
    }
  }
}

MIRPreg *MIRParser::CreateMirPreg(uint32 pregNo) const {
  return mod.GetMemPool()->New<MIRPreg>(pregNo);
}

PregIdx MIRParser::LookupOrCreatePregIdx(uint32 pregNo, bool isRef, MIRFunction *func) {
  ASSERT(func != nullptr, "func is null");
  MIRPregTable *pRegTab = func->GetPregTab();
  PregIdx idx = pRegTab->GetPregIdxFromPregno(pregNo);
  if (idx == 0) {
    if (pregNo > maxPregNo) {
      maxPregNo = pregNo;
    }
    MIRPreg *preg = nullptr;
    preg = CreateMirPreg(pregNo);
    if (isRef) {
      preg->SetPrimType(PTY_ref);
    }
    idx = pRegTab->GetPregTable().size();
    pRegTab->GetPregTable().push_back(preg);
    pRegTab->SetPregNoToPregIdxMapItem(pregNo, idx);
  }
  return idx;
}

bool MIRParser::IsDelimitationTK(TokenKind tk) const {
  switch (tk) {
    case kTkRparen:
    case kTkComa:
      return true;
    default:
      return false;
  }
}

inline bool IsPowerOf2(uint64 i) {
  if (i == 0) {
    return false;
  }
  return (~(i - 1) & i) == i;
}

Opcode MIRParser::GetOpFromToken(TokenKind tk) const {
  switch (tk) {
#define OPCODE(X, Y, Z, S) \
  case TK_##X:             \
    return OP_##X;
#include "opcodes.def"
#undef OPCODE
    default:
      return kOpUndef;
  }
}

static bool IsClassInterfaceTypeName(const std::string &nameStr) {
  return (!nameStr.empty() && nameStr.front() == 'L' && StringUtils::EndsWith(nameStr, "_3B"));
}

bool MIRParser::IsStatement(TokenKind tk) const {
  if (tk == TK_LOC || tk == TK_ALIAS) {
    return true;
  }
  Opcode op = GetOpFromToken(tk);
  return kOpcodeInfo.IsStmt(op);
}

PrimType MIRParser::GetPrimitiveType(TokenKind tk) const {
#define LOAD_ALGO_PRIMARY_TYPE
  switch (tk) {
#define PRIMTYPE(P) \
  case TK_##P:      \
    return PTY_##P;
#include "prim_types.def"
#undef PRIMTYPE
    default:
      return kPtyInvalid;
  }
}

MIRIntrinsicID MIRParser::GetIntrinsicId(TokenKind tk) const {
  switch (tk) {
    default:
#define DEF_MIR_INTRINSIC(P, NAME, INTRN_CLASS, RETURN_TYPE, ...) \
  case TK_##P:                                                    \
    return INTRN_##P;
#include "intrinsics.def"
#undef DEF_MIR_INTRINSIC
  }
}

void MIRParser::Error(const std::string &str) {
  std::stringstream strStream;
  const std::string &lexName = lexer.GetName();
  int curidx = lexer.GetCurIdx() - lexName.length() + 1;
  strStream << "line: " << lexer.GetLineNum() << ":" << curidx << ":";
  message += strStream.str();
  message += str;
  message += ": ";
  message += lexer.GetTokenString();
  message += "\n";
}

const std::string &MIRParser::GetError() {
  if (lexer.GetTokenKind() == kTkInvalid) {
    std::stringstream strStream;
    strStream << "line: " << lexer.GetLineNum() << ":" << lexer.GetCurIdx() << ":";
    message += strStream.str();
    message += " invalid token\n";
  }
  return message;
}

void MIRParser::Warning(const std::string &str) {
  std::stringstream strStream;
  const std::string &lexName = lexer.GetName();
  int curidx = lexer.GetCurIdx() - lexName.length() + 1;
  strStream << "  >> warning line: " << lexer.GetLineNum() << ":" << curidx << ":";
  warningMessage += strStream.str();
  warningMessage += str;
  warningMessage += "\n";
}

const std::string &MIRParser::GetWarning() const {
  return warningMessage;
}

bool MIRParser::ParseSpecialReg(PregIdx &pRegIdx) {
  const std::string &lexName = lexer.GetName();
  int32 lexSize = lexName.size();
  int32 retValSize = strlen(kLexerStringRetval);
  if (strncmp(lexName.c_str(), kLexerStringRetval, retValSize) == 0 && (lexSize > retValSize) &&
      isdigit(lexName[retValSize])) {
    int32 retvalNo = lexName[retValSize] - '0';
    for (int32 i = retValSize + 1; (i < lexSize) && isdigit(lexName[i]); i++) {
      retvalNo = retvalNo * 10 + lexName[i] - '0';
    }
    pRegIdx = -kSregRetval0 - retvalNo;
    lexer.NextToken();
    return true;
  }

  std::map<std::string, enum maple::SpecialReg> pregMapIdx = { { kLexerStringSp, kSregSp },
                                                               { kLexerStringFp, kSregFp },
                                                               { kLexerStringGp, kSregGp },
                                                               { kLexerStringThrownval, kSregThrownval },
                                                               { kLexerStringRetval, kSregRetval0 } };
  if (pregMapIdx.find(lexName) != pregMapIdx.end()) {
    pRegIdx = -pregMapIdx[lexName];
    lexer.NextToken();
    return true;
  }

  Error("unrecognized special register ");
  return false;
}

bool MIRParser::ParseRefPseudoReg(PregIdx &pRegIdx) {
  uint32 pRegNo = static_cast<uint32>(lexer.GetTheIntVal());
  ASSERT(pRegNo <= 0xffff, "preg number must be 16 bits");
  pRegIdx = LookupOrCreatePregIdx(pRegNo, true, mod.CurFunction());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParsePseudoReg(PrimType primType, PregIdx &pRegIdx) {
  MIRFunction *func = mod.CurFunction();
  pRegIdx = LookupOrCreatePregIdx(static_cast<uint32>(lexer.GetTheIntVal()), false, func);
  MIRPreg *preg = func->GetPregTab()->PregFromPregIdx(pRegIdx);

  if (primType == kPtyInvalid || preg->GetPrimType() == primType) {
    lexer.NextToken();
    return true;
  }

  // check type consistenency for the preg
  if (preg->GetPrimType() == kPtyInvalid) {
    preg->SetPrimType(primType);
    lexer.NextToken();
    return true;
  }

  if ((primType == PTY_ref || primType == PTY_ptr) &&
      (preg->GetPrimType() == PTY_ref || preg->GetPrimType() == PTY_ptr)) {
    // PTY_ref and PTY_ptr are compatible with each other
    lexer.NextToken();
    return true;
  }

  Error("inconsistent preg primitive type at ");
  return false;
}

bool MIRParser::CheckPrimAndDerivedType(TokenKind tokenKind, TyIdx &tyIdx) {
  if (IsPrimitiveType(tokenKind)) {
    return ParsePrimType(tyIdx);
  }
  if (tokenKind == kTkLangle) {
    return ParseDerivedType(tyIdx);
  }
  return false;
}

bool MIRParser::ParseType(TyIdx &tyIdx) {
  TokenKind tk = lexer.GetTokenKind();
  if (IsVarName(tk)) {
    return ParseDefinedTypename(tyIdx);
  }
  if (CheckPrimAndDerivedType(tk, tyIdx)) {
    return true;
  }
  Error("token is not a type ");
  return false;
}

bool MIRParser::ParseFarrayType(TyIdx &arrayTyIdx) {
  TokenKind tokenKind = lexer.NextToken();
  TyIdx tyIdx;
  if (!CheckPrimAndDerivedType(tokenKind, tyIdx)) {
    Error("unexpect token parsing flexible array element type ");
    return false;
  }
  ASSERT(tyIdx != 0, "error encountered parsing flexible array element type ");
  if (mod.IsJavaModule()) {
    MIRJarrayType jarrayType(tyIdx);
    arrayTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&jarrayType);
  } else {
    MIRFarrayType farrayType(tyIdx);
    arrayTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&farrayType);
  }
  return true;
}

bool MIRParser::ParseArrayType(TyIdx &arrayTyIdx) {
  TokenKind tokenKind = lexer.GetTokenKind();
  if (tokenKind != kTkLbrack) {
    Error("expect [ for array type but get ");
    return false;
  }
  std::vector<uint32> vec;
  while (tokenKind == kTkLbrack) {
    tokenKind = lexer.NextToken();
    if (tokenKind == kTkRbrack && vec.empty()) {
      break;
    }
    if (tokenKind != kTkIntconst) {
      Error("expect int value parsing array type after [ but get ");
      return false;
    }
    int64 val = lexer.GetTheIntVal();
    if (val < 0) {
      Error("expect array value >= 0 ");
      return false;
    }
    vec.push_back(val);
    if (lexer.NextToken() != kTkRbrack) {
      Error("expect ] after int value parsing array type but get ");
      return false;
    }
    tokenKind = lexer.NextToken();
  }
  if (tokenKind == kTkRbrack && vec.empty()) {
    return ParseFarrayType(arrayTyIdx);
  }
  TyIdx tyIdx;
  if (!CheckPrimAndDerivedType(tokenKind, tyIdx)) {
    Error("unexpect token parsing array type after ] ");
    return false;
  }
  ASSERT(tyIdx != 0, "something wrong with parsing element type ");
  MIRArrayType arrayType(tyIdx, vec);
  arrayTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&arrayType);
  return true;
}

bool MIRParser::ParseBitFieldType(TyIdx &fieldTyIdx) {
  if (lexer.GetTokenKind() != kTkColon) {
    Error("expect : parsing field type but get ");
    return false;
  }
  if (lexer.NextToken() != kTkIntconst) {
    Error("expect int const val parsing field type but get ");
    return false;
  }
  ASSERT(lexer.GetTheIntVal() <= 0xFFU, "lexer.theIntVal is larger than max uint8 bitsize value.");
  uint8 bitSize = lexer.GetTheIntVal() & 0xFFU;
  PrimType primType = GetPrimitiveType(lexer.NextToken());
  if (primType == kPtyInvalid) {
    Error("expect primitive type but get ");
    return false;
  }
  if (!IsPrimitiveInteger(primType)) {
    Error("syntax error bit field should be integer type but get ");
    return false;
  }
  MIRBitFieldType bitFieldType(bitSize, primType);
  fieldTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&bitFieldType);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParsePragmaElement(MIRPragmaElement *elem) {
  ASSERT(elem != nullptr, "elem is null");

  TokenKind tk = lexer.GetTokenKind();
  lexer.NextToken();
  std::map<enum maple::TokenKind, enum maple::PragmaValueType> tkPragmaValType = {
    { TK_i8, kValueByte },          { TK_i16, kValueShort },
    { TK_u16, kValueChar },         { TK_i32, kValueInt },
    { TK_i64, kValueLong },         { TK_f32, kValueFloat },
    { TK_f64, kValueDouble },       { TK_retype, kValueMethodType },
    { TK_ref, kValueMethodHandle }, { TK_ptr, kValueString },
    { TK_type, kValueType },        { TK_var, kValueField },
    { TK_func, kValueMethod },      { TK_enum, kValueEnum },
    { TK_array, kValueArray },      { TK_annotation, kValueAnnotation },
    { TK_const, kValueNull },       { TK_u1, kValueBoolean }
  };
  if (tkPragmaValType.find(tk) == tkPragmaValType.end()) {
    Error("parsing pragma error: wrong element type");
    return false;
  }
  elem->SetType(tkPragmaValType[tk]);

  switch (tk) {
    case TK_i8:
    case TK_i16:
    case TK_i32:
      elem->SetI32Val((int32)lexer.GetTheIntVal());
      break;
    case TK_u16:
    case TK_ref:
      elem->SetU64Val((uint64)lexer.GetTheIntVal());
      break;
    case TK_i64:
    case TK_retype:
    case TK_const:
    case TK_u1:
      elem->SetI64Val(lexer.GetTheIntVal());
      break;
    case TK_f32:
      elem->SetFloatVal(lexer.GetTheFloatVal());
      break;
    case TK_f64:
      elem->SetDoubleVal(lexer.GetTheDoubleVal());
      break;
    case TK_ptr:
    case TK_var:
    case TK_func:
    case TK_enum:
      elem->SetI32Val(GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName()).GetIdx());
      break;
    case TK_type:
      lexer.NextToken();
      elem->SetI32Val(GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName()).GetIdx());
      lexer.NextToken();
      break;
    case TK_array:
      if (!ParsePragmaElementForArray(elem)) {
        return false;
      }
      break;
    case TK_annotation:
      if (!ParsePragmaElementForAnnotation(elem)) {
        return false;
      }
      break;
    default:
      return false;
  }
  return true;
}

bool MIRParser::ParsePragmaElementForArray(MIRPragmaElement *elem) {
  ASSERT(elem != nullptr, "elem is null");

  TokenKind tk;
  tk = lexer.GetTokenKind();
  if (tk != kTkLbrack) {
    Error("parsing pragma error: expecting [ but get ");
    return false;
  }
  tk = lexer.NextToken();
  if (tk != kTkIntconst) {
    Error("parsing pragma error: expecting int but get ");
    return false;
  }
  int64 size = lexer.GetTheIntVal();
  tk = lexer.NextToken();
  if (tk != kTkComa && size) {
    Error("parsing pragma error: expecting , but get ");
    return false;
  }
  for (int64 i = 0; i < size; i++) {
    MIRPragmaElement *e0 = mod.GetMemPool()->New<MIRPragmaElement>(&mod);
    tk = lexer.NextToken();
    if (!ParsePragmaElement(e0)) {
      Error("parsing pragma error type ");
      return false;
    }
    elem->PushSubElemVec(e0);
    tk = lexer.NextToken();
    if (tk != kTkComa && tk != kTkRbrack) {
      Error("parsing pragma error: expecting , or ] but get ");
      return false;
    }
  }
  return true;
}

bool MIRParser::ParsePragmaElementForAnnotation(MIRPragmaElement *elem) {
  ASSERT(elem != nullptr, "elem is null");
  TokenKind tk;
  tk = lexer.GetTokenKind();
  if (tk != kTkLangle) {
    Error("parsing pragma error: expecting < but get ");
    return false;
  }
  tk = lexer.NextToken();
  elem->SetTypeStrIdx(GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName()));
  tk = lexer.NextToken();
  if (tk != kTkRangle) {
    Error("parsing pragma error: expecting > but get ");
    return false;
  }
  tk = lexer.NextToken();
  if (tk != kTkLbrack) {
    Error("parsing pragma error: expecting [ but get ");
    return false;
  }
  tk = lexer.NextToken();
  if (tk != kTkIntconst) {
    Error("parsing pragma error: expecting int but get ");
    return false;
  }
  int64 size = lexer.GetTheIntVal();
  tk = lexer.NextToken();
  if (tk != kTkComa && size) {
    Error("parsing pragma error: expecting , but get ");
    return false;
  }
  for (int i = 0; i < size; i++) {
    MIRPragmaElement *e0 = mod.GetMemPool()->New<MIRPragmaElement>(&mod);
    tk = lexer.NextToken();
    if (tk != TK_label) {
      Error("parsing pragma error: expecting @ but get ");
      return false;
    }
    e0->SetNameStrIdx(GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName()));
    tk = lexer.NextToken();
    if (!ParsePragmaElement(e0)) {
      Error("parsing pragma error type ");
      return false;
    }
    elem->PushSubElemVec(e0);
    tk = lexer.NextToken();
    if (tk != kTkComa && tk != kTkRbrack) {
      Error("parsing pragma error: expecting , or ] but get ");
      return false;
    }
  }
  return true;
}

bool MIRParser::ParsePragma(MIRStructType &type) {
  MIRPragma *p = mod.GetMemPool()->New<MIRPragma>(&mod);
  p->SetVisibility(lexer.GetTheIntVal());
  TokenKind tk = lexer.NextToken();

  std::map<enum maple::TokenKind, enum maple::PragmaKind> tkPragmaKind = { { TK_class, kPragmaClass },
                                                                           { TK_func, kPragmaFunc },
                                                                           { TK_var, kPragmaVar },
                                                                           { TK_param, kPragmaParam },
                                                                           { TK_func_ex, kPragmaFuncExecptioni },
                                                                           { TK_func_var, kPragmaFuncVar } };
  if (tkPragmaKind.find(tk) == tkPragmaKind.end()) {
    Error("parsing pragma error: wrong kind ");
    return false;
  }
  p->SetKind(tkPragmaKind[tk]);

  if (tk == TK_param) {
    tk = lexer.NextToken();
    p->SetParamNum(lexer.GetTheIntVal());
  }
  tk = lexer.NextToken();
  if (tk != kTkGname && tk != kTkLname && tk != kTkFname) {
    Error("expect global or local token parsing pragma but get ");
    return false;
  }
  p->SetStrIdx(GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName()));
  tk = lexer.NextToken();
  TyIdx tyidx;
  if (!ParseType(tyidx)) {
    Error("parsing pragma error: wrong type ");
    return false;
  }
  p->SetTyIdx(tyidx);
  tk = lexer.GetTokenKind();
  if (tk != kTkLbrace) {
    Error("parsing pragma error: expecting { but get ");
    return false;
  }
  tk = lexer.NextToken();
  while (tk != kTkRbrace) {
    MIRPragmaElement *e = mod.GetMemPool()->New<MIRPragmaElement>(&mod);
    e->SetNameStrIdx(GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName()));
    tk = lexer.NextToken();
    if (!ParsePragmaElement(e)) {
      Error("parsing pragma error type ");
      return false;
    }
    p->PushElementVector(e);
    tk = lexer.NextToken();
    if (tk != kTkRbrace && tk != kTkComa) {
      Error("parsing pragma error syntax ");
      return false;
    }
    if (tk == kTkComa) {
      lexer.NextToken();
    }
  }
  lexer.NextToken();
  type.AddPragmaVec(p);
  return true;
}

// lexer.GetTokenKind() assumed to be the kTkLbrace that starts the fields
bool MIRParser::ParseFields(MIRStructType &type) {
  if (type.IsIncomplete()) {
    Warning("incomplete class/interface type");
  }
  TokenKind tk = lexer.NextToken();
  while (tk == TK_label || tk == kTkPrntfield || tk == TK_pragma) {
    bool isPragma = tk == TK_pragma;
    bool notaType = false;
    TyIdx fieldTyIdx(0);
    bool isParentField = false;
    if (tk == kTkPrntfield) {
      isParentField = true;
    }
    GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
    tk = lexer.NextToken();
    if (isPragma) {
      if (type.GetKind() == kTypeClass || type.GetKind() == kTypeClassIncomplete || type.GetKind() == kTypeInterface ||
          type.GetKind() == kTypeInterfaceIncomplete) {
        if (!ParsePragma(type)) {
          Error("parsing pragma error ");
          return false;
        }
      } else {
        Error("parsing pragma error ");
        return false;
      }
      notaType = true;
    } else if ((tk == kTkLbrack) && (GlobalTables::GetStrTable().GetStringFromStrIdx(strIdx) == "staticvalue")) {
      while (tk != kTkComa) {
        EncodedValue elem;
        if (tk != kTkLbrack) {
          Error("parsing staticvalue error ");
          return false;
        }
        tk = lexer.NextToken();
        uint32 i = 0;
        while (tk != kTkRbrack) {
          if (tk != kTkIntconst) {
            Error("parsing staticvalue error ");
            return false;
          }
          elem.encodedValue[i++] = lexer.GetTheIntVal();
          tk = lexer.NextToken();
        }
        tk = lexer.NextToken();
        if (type.GetKind() == kTypeClass || type.GetKind() == kTypeClassIncomplete ||
            type.GetKind() == kTypeInterface || type.GetKind() == kTypeInterfaceIncomplete) {
          type.AddStaticValue(elem);
        } else {
          Error("parsing staticvalue error ");
          return false;
        }
      }
      notaType = true;
    } else if (tk == kTkColon) {  // a bitfield
      if (!ParseBitFieldType(fieldTyIdx)) {
        Error("parsing struct type error ");
        return false;
      }
    } else if (tk == kTkLangle) {
      if (!ParseDerivedType(fieldTyIdx)) {
        Error("parsing struct type error ");
        return false;
      }
    } else if ((IsPrimitiveType(tk))) {
      if (!ParsePrimType(fieldTyIdx)) {
        Error("expect :<val> or primitive type or derived type parsing struct type ");
        return false;
      }
    } else if ((tk == kTkIntconst || tk == kTkString) && !isParentField &&
               (type.GetKind() == kTypeClass || type.GetKind() == kTypeClassIncomplete ||
                type.GetKind() == kTypeInterface || type.GetKind() == kTypeInterfaceIncomplete)) {
      uint32 infoVal = (tk == kTkIntconst)
                           ? lexer.GetTheIntVal()
                           : GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName()).GetIdx();
      type.AddInfo(MIRInfoPair(strIdx, infoVal));
      type.AddIsStringInfo(tk != kTkIntconst);
      notaType = true;
      lexer.NextToken();
    } else {
      Error("unexpected type parsing struct type at ");
      return false;
    }
    ASSERT((fieldTyIdx != 0 || notaType), "something wrong parsing struct type");
    if (!notaType) {
      FieldAttrs tA;
      if (!ParseFieldAttrs(tA)) {
        Error("bad type attribute in struct field at ");
        return false;
      }
      if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(fieldTyIdx)->HasTypeParam()) {
        tA.SetAttr(FLDATTR_generic);
      }
      FieldPair p = FieldPair(strIdx, TyIdxFieldAttrPair(fieldTyIdx, tA));
      bool isStaticField = false;
      if (tA.GetAttr(FLDATTR_static)) {
        // static and parent share the same ^ token
        isStaticField = true;
        isParentField = false;
      }
      if (isParentField) {
        type.GetParentFields().push_back(p);
      } else if (isStaticField) {
        type.GetStaticFields().push_back(p);
      } else {
        type.GetFields().push_back(p);
      }
      tk = lexer.GetTokenKind();
      bool isConst = tA.GetAttr(FLDATTR_static) && tA.GetAttr(FLDATTR_final) &&
                     (tA.GetAttr(FLDATTR_public) || tA.GetAttr(FLDATTR_protected));
      if (isConst && tk == kTkEqsign) {
        tk = lexer.NextToken();
        MIRConst *mirConst = nullptr;
        if (!ParseInitValue(mirConst, fieldTyIdx)) {
          Error("wrong initialiaton value at ");
          return false;
        }
        GlobalTables::GetConstPool().InsertConstPool(p.first, mirConst);
        tk = lexer.GetTokenKind();
      }
    } else {
      tk = lexer.GetTokenKind();
    }
    tk = lexer.GetTokenKind();
    if (tk == kTkRbrace) {
      return true;
    }
    if (tk != kTkComa) {
      Error(", missing after ");
      return false;
    }
    tk = lexer.NextToken();
    if (tk == kTkRbrace) {
      Error(",} is not legal, expect another field type after ,");
      return false;
    }
  }
  while (tk == kTkFname) {
    const std::string &funcName = lexer.GetName();
    GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(funcName);
    MIRSymbol *prevFuncSymbol = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(stridx);
    if (prevFuncSymbol && (prevFuncSymbol->GetStorageClass() != kScText || prevFuncSymbol->GetSKind() != kStFunc)) {
      // Based on the current maple format, a previous declaration at this
      // point can only come from another module. Check consistency.
      Error("redeclaration of name as func in ");
      return false;
    }
    // Always create a new symbol because we can not reuse symbol from other module
    maple::MIRBuilder mirBuilder(&mod);
    MIRSymbol *funcSymbol = mirBuilder.CreateSymbol(TyIdx(0), stridx, kStFunc, kScText, nullptr, kScopeGlobal);
    ASSERT(funcSymbol != nullptr, "Failed to create MIRSymbol");
    MIRFunction *fn = mod.GetMemPool()->New<MIRFunction>(&mod, funcSymbol->GetStIdx());
    ASSERT(fn != nullptr, "Failed to create MIRFunction");
    fn->Init();
    fn->SetPuidx(GlobalTables::GetFunctionTable().GetFuncTable().size());
    GlobalTables::GetFunctionTable().GetFuncTable().push_back(fn);
    funcSymbol->SetFunction(fn);
    fn->SetFileIndex(0);
    fn->SetBaseClassFuncNames(funcSymbol->GetNameStrIdx());
    FuncAttrs tA;
    if (lexer.NextToken() != kTkLparen) {
      if (!ParseFuncAttrs(tA)) {
        return false;
      }
      // Skip attribute checking
      fn->SetFuncAttrs(tA);
    }
    TyIdx funcTyidx;
    if (!ParseFuncType(funcTyidx)) {
      return false;
    }
    // tyIdx does not work. Calling EqualTo does not work either.
    MIRFuncType *funcType = static_cast<MIRFuncType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(funcTyidx));
    fn->SetMIRFuncType(funcType);
    fn->SetReturnStruct(GlobalTables::GetTypeTable().GetTypeFromTyIdx(funcType->GetRetTyIdx()));
    funcSymbol->SetTyIdx(funcTyidx);
    MethodPair p = MethodPair(funcSymbol->GetStIdx(), TyidxFuncAttrPair(funcTyidx, FuncAttrs(tA)));
    type.GetMethods().push_back(p);
    tk = lexer.GetTokenKind();
    if (tk == kTkComa) {
      tk = lexer.NextToken();
      if (tk == kTkRbrace) {
        Error(",} is not legal, expect another field type after ,");
        return false;
      }
    } else if (tk != kTkRbrace) {
      Error(", missing after ");
      return false;
    } else {
      return true;
    }
  }
  // interfaces_implemented
  while (tk == kTkGname) {
    tk = lexer.NextToken();
    if ((tk == kTkComa || tk == kTkRbrace) &&
        (type.GetKind() == kTypeClass || type.GetKind() == kTypeClassIncomplete)) {
      MIRClassType *classType = static_cast<MIRClassType*>(&type);
      std::string nameStr = lexer.GetName();
      GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(nameStr);
      TyIdx tyidx = mod.GetTypeNameTab()->GetTyIdxFromGStrIdx(strIdx);
      if (tyidx == 0) {
        MIRInterfaceType interfaceType(kTypeInterfaceIncomplete);
        interfaceType.GetNameStrIdx() = strIdx;
        tyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&interfaceType);
        mod.AddClass(tyidx);
        mod.AddExternStructType(tyidx);
        mod.GetTypeNameTab()->SetGStrIdxToTyIdx(strIdx, tyidx);
      }
      classType->GetInerfaceImplemented().push_back(tyidx);
    }
    if (tk == kTkComa) {
      tk = lexer.NextToken();
    }
  }
  // allow empty class for third party classes we do not have info
  if (tk == kTkRbrace) {
    return true;
  }
  Error("expect field or member function name in struct/class body but get ");
  return false;
}

bool MIRParser::ParseStructType(TyIdx &styidx) {
  MIRTypeKind tkind = kTypeInvalid;
  switch (lexer.GetTokenKind()) {
    case TK_struct:
      tkind = kTypeStruct;
      break;
    case TK_structincomplete:
      tkind = kTypeStructIncomplete;
      break;
    case TK_union:
      tkind = kTypeUnion;
      break;
    default:;
  }
  if (lexer.NextToken() != kTkLbrace) {
    Error("expect { parsing struct body");
    return false;
  }
  MIRStructType structType(tkind);
  if (!ParseFields(structType)) {
    return false;
  }
  styidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&structType);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseClassType(TyIdx &styidx) {
  MIRTypeKind tkind = (lexer.GetTokenKind() == TK_class) ? kTypeClass : kTypeClassIncomplete;
  TyIdx parentTypeIdx(0);
  if (lexer.NextToken() == kTkLangle) {
    // parsing parent as class
    if (!ParseDerivedType(parentTypeIdx, kTypeClass)) {
      Error("parsing class parent type error ");
      return false;
    }
  }
  MIRClassType classType(tkind);
  classType.GetParentTyIdx() = parentTypeIdx;
  if (!ParseFields(classType)) {
    return false;
  }
  styidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&classType);
  // set up classTyIdx for methods
  for (size_t i = 0; i < classType.GetMethods().size(); i++) {
    StIdx stidx = classType.GetMethodsElement(i).first;
    MIRSymbol *st = GlobalTables::GetGsymTable().GetSymbolFromStidx(stidx.Idx());
    ASSERT(st->GetSKind() == kStFunc, "unexpected st->sKind");
    st->GetFunction()->GetClassTyidx() = styidx;
  }
  lexer.NextToken();
  mod.AddClass(styidx);
  return true;
}

bool MIRParser::ParseInterfaceType(TyIdx &styidx) {
  MIRTypeKind tkind = (lexer.GetTokenKind() == TK_interface) ? kTypeInterface : kTypeInterfaceIncomplete;
  std::vector<TyIdx> parents;
  TokenKind tk = lexer.NextToken();
  while (tk == kTkLangle) {
    TyIdx parentTypeIdx(0);
    // parsing parents as interfaces
    if (!ParseDerivedType(parentTypeIdx, kTypeInterface)) {
      Error("parsing interface parent type error ");
      return false;
    }
    parents.push_back(parentTypeIdx);
    tk = lexer.GetTokenKind();
  }
  MIRInterfaceType interfaceType(tkind);
  interfaceType.GetParentsTyIdx() = parents;
  if (!ParseFields(interfaceType)) {
    return false;
  }
  styidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&interfaceType);
  // set up classTyIdx for methods
  for (size_t i = 0; i < interfaceType.GetMethods().size(); i++) {
    StIdx stidx = interfaceType.GetMethodsElement(i).first;
    MIRSymbol *st = GlobalTables::GetGsymTable().GetSymbolFromStidx(stidx.Idx());
    ASSERT(st != nullptr, "st is null");
    ASSERT(st->GetSKind() == kStFunc, "unexpected st->sKind");
    st->GetFunction()->GetClassTyidx() = styidx;
  }
  mod.AddClass(styidx);
  lexer.NextToken();
  return true;
}

bool MIRParser::CheckAlignTk() {
  if (lexer.NextToken() != kTkLparen) {
    Error("unexpected token in alignment specification after ");
    return false;
  }
  if (lexer.NextToken() != kTkIntconst) {
    Error("unexpected token in alignment specification after ");
    return false;
  }
  if (!IsPowerOf2(lexer.GetTheIntVal())) {
    Error("specified alignment must be power of 2 instead of ");
    return false;
  }
  if (lexer.NextToken() != kTkRparen) {
    Error("unexpected token in alignment specification after ");
    return false;
  }
  return true;
}

bool MIRParser::ParseAlignAttrs(TypeAttrs &tA) {
  if (lexer.GetTokenKind() != TK_align) {
    Error("wrong TK kind taken from file");
    return false;
  }
  if (!CheckAlignTk()) {
    return false;
  }
  tA.SetAlign(lexer.GetTheIntVal());
  return true;
}

// for variable declaration type attribute specification
// it has also storage-class qualifier.
bool MIRParser::ParseVarTypeAttrs(MIRSymbol *st) {
  do {
    switch (lexer.GetTokenKind()) {
#define TYPE_ATTR
#define ATTR(X)            \
  case TK_##X:             \
    st->SetAttr(ATTR_##X); \
    break;
#include "all_attributes.def"
#undef ATTR
#undef TYPE_ATTR
      case TK_align: {
        if (!ParseAlignAttrs(st->GetAttrs())) {
          return false;
        }
        break;
      }
      default:
        return true;
    }  // switch
    lexer.NextToken();
  } while (true);
}

// for non-variable type attribute specification.
bool MIRParser::ParseTypeAttrs(TypeAttrs &t_a) {
  do {
    switch (lexer.GetTokenKind()) {
#define TYPE_ATTR
#define ATTR(X)            \
  case TK_##X:             \
    t_a.SetAttr(ATTR_##X); \
    break;
#include "all_attributes.def"
#undef ATTR
#undef TYPE_ATTR
      case TK_align: {
        if (!ParseAlignAttrs(t_a)) {
          return false;
        }
        break;
      }
      default:
        return true;
    }  // switch
    lexer.NextToken();
  } while (true);
}

bool MIRParser::ParseFieldAttrs(FieldAttrs &t_a) {
  do {
    switch (lexer.GetTokenKind()) {
#define FIELD_ATTR
#define ATTR(X)               \
  case TK_##X:                \
    t_a.SetAttr(FLDATTR_##X); \
    break;
#include "all_attributes.def"
#undef ATTR
#undef FIELD_ATTR
      case TK_align: {
        if (!CheckAlignTk()) {
          return false;
        }
        t_a.SetAlign(lexer.GetTheIntVal());
        break;
      }
      default:
        return true;
    }  // switch
    lexer.NextToken();
  } while (true);
}

bool MIRParser::ParseFuncAttrs(FuncAttrs &t_a) {
  do {
    switch (lexer.GetTokenKind()) {
#define FUNC_ATTR
#define ATTR(X)                \
  case TK_##X:                 \
    t_a.SetAttr(FUNCATTR_##X); \
    break;
#include "all_attributes.def"
#undef ATTR
#undef FUNC_ATTR
      default:
        return true;
    }  // switch
    lexer.NextToken();
  } while (true);
}

bool MIRParser::ParsePrimType(TyIdx &tyIdx) {
  PrimType primType = GetPrimitiveType(lexer.GetTokenKind());
  if (primType == kPtyInvalid) {
    tyIdx = TyIdx(0);
    Error("ParsePrimType failed, invalid token");
    return false;
  }
  lexer.NextToken();
  tyIdx = GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(primType))->GetTypeIndex();
  return true;
}

bool MIRParser::ParseTypeParam(TyIdx &definedTyIdx) {
  GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
  MIRTypeParam typeParm(stridx);
  definedTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&typeParm);
  lexer.NextToken();
  return true;
}

// LB not handled in binary format
bool MIRParser::ParseDefinedTypename(TyIdx &definedTyIdx, MIRTypeKind kind) {
  TokenKind tk = lexer.GetTokenKind();
  if (!IsVarName(tk)) {
    Error("expect global or local token parsing typedef type but get ");
    return false;
  }
  std::string nameStr = lexer.GetName();
  GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(nameStr);
  // check if type already exist
  definedTyIdx = mod.GetTypeNameTab()->GetTyIdxFromGStrIdx(strIdx);
  TyIdx prevTypeIdx(0);
  if (definedTyIdx.GetIdx()) {
    MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(definedTyIdx);
    MIRStructType *stype = dynamic_cast<MIRStructType*>(type);
    if (stype != nullptr) {
      // check whether need to update from incomplete class to interface
      if (stype->GetKind() == kind) {
        lexer.NextToken();
        return true;
      } else {
        prevTypeIdx = definedTyIdx;
      }
    }
  }
  if (tk == kTkGname) {
    definedTyIdx = mod.GetTypeNameTab()->GetTyIdxFromGStrIdx(strIdx);
    if (definedTyIdx == 0) {
      if (kind == kTypeInterface || kind == kTypeInterfaceIncomplete) {
        MIRInterfaceType interfaceType(kTypeInterfaceIncomplete);
        interfaceType.GetNameStrIdx() = strIdx;
        definedTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&interfaceType);
        mod.AddClass(definedTyIdx);
        mod.AddExternStructType(definedTyIdx);
        mod.GetTypeNameTab()->SetGStrIdxToTyIdx(strIdx, definedTyIdx);
      } else if (kind == kTypeClass || kind == kTypeClassIncomplete || IsClassInterfaceTypeName(nameStr)) {
        MIRClassType classType(kTypeClassIncomplete);
        classType.GetNameStrIdx() = strIdx;
        definedTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&classType);
        mod.AddClass(definedTyIdx);
        mod.AddExternStructType(definedTyIdx);
        mod.GetTypeNameTab()->SetGStrIdxToTyIdx(strIdx, definedTyIdx);
      } else {
        MIRTypeByName nameType(strIdx);
        definedTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&nameType);
        mod.GetTypeNameTab()->SetGStrIdxToTyIdx(strIdx, definedTyIdx);
      }
    }
  } else {
    definedTyIdx = mod.CurFunction()->GetTypeNameTable()->GetTyIdxFromGStrIdx(strIdx);
    if (definedTyIdx == 0) {
      MIRTypeByName nameType(strIdx);
      definedTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&nameType);
      mod.GetTypeNameTab()->SetGStrIdxToTyIdx(strIdx, definedTyIdx);
    }
  }
  // replace prevTypeIdx with definedTyIdx
  if (prevTypeIdx != 0 && prevTypeIdx != definedTyIdx) {
    // replace all uses of prevTypeIdx by tyIdx in type_table_
    typeDefIdxMap[prevTypeIdx] = definedTyIdx;
        // remove prevTypeIdx from classlist
    mod.RemoveClass(prevTypeIdx);
  }
  lexer.NextToken();
  return true;
}

bool MIRParser::ParsePointType(TyIdx &tyIdx) {
  TokenKind pdtk;
  if (lexer.GetTokenKind() == TK_func) {  // a function pointer
    pdtk = TK_func;
  } else if (lexer.GetTokenKind() != kTkAsterisk) {
    Error("expect * for point type but get ");
    return false;
  } else {
    pdtk = lexer.NextToken();
  }
  TyIdx pointTypeIdx(0);
  if (IsPrimitiveType(pdtk)) {
    if (!ParsePrimType(pointTypeIdx)) {
      return false;
    }
  } else if (pdtk == kTkAsterisk) {  // a point type
    if (!ParsePointType(pointTypeIdx)) {
      return false;
    }
  } else if (pdtk == kTkLbrack) {  // a array type
    if (!ParseArrayType(pointTypeIdx)) {
      return false;
    }
  } else if (pdtk == TK_struct || pdtk == TK_union || pdtk == TK_structincomplete) {
    if (!ParseStructType(pointTypeIdx)) {
      return false;
    }
  } else if (pdtk == TK_class || pdtk == TK_classincomplete) {
    if (!ParseClassType(pointTypeIdx)) {
      return false;
    }
  } else if (pdtk == kTkGname) {
    if (!ParseDefinedTypename(pointTypeIdx)) {
      return false;
    }
  } else if (pdtk == kTkLangle) {
    if (!ParseDerivedType(pointTypeIdx)) {
      return false;
    }
  } else if (pdtk == TK_func) {
    lexer.NextToken();
    if (!ParseFuncType(pointTypeIdx)) {
      return false;
    }
  } else {
    Error("unexpect type ");
    return false;
  }
  ASSERT(pointTypeIdx != 0, "something wrong with parsing element type ");
  PrimType pty = mod.IsJavaModule() ? PTY_ref : PTY_ptr;
  if (pdtk == maple::TK_constStr) {
    pty = PTY_ptr;
  }
  MIRPtrType pointType(pointTypeIdx, pty);  // use reference type here
  tyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&pointType);
  return true;
}

// used in parsing the parameter list (types only, without parameter names)
// in function pointer specification and member function prototypes inside
// structs and classes
bool MIRParser::ParseFuncType(TyIdx &tyIdx) {
  // parse parameters
  if (lexer.GetTokenKind() != kTkLparen) {
    Error("expect ( parse function type parameters but get ");
    return false;
  }
  std::vector<TyIdx> vecTyIdx;
  std::vector<TypeAttrs> vecAttrs;
  TokenKind tokenkind = lexer.NextToken();
  while (tokenkind != kTkRparen) {
    TyIdx tyIdxTmp(0);
    if (!ParseType(tyIdxTmp)) {
      Error("expect type parsing function parameters ");
      return false;
    }
    TypeAttrs typeAttrs;
    if (!ParseTypeAttrs(typeAttrs)) {
      Error("bad attribute in function parameter type at ");
      return false;
    }
    tokenkind = lexer.GetTokenKind();
    if (tokenkind == kTkComa) {
      tokenkind = lexer.NextToken();
      if (tokenkind == kTkRparen) {
        Error("syntax error, meeting ,) expect another type after , or ) without , ");
        return false;
      }
    }
    if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdxTmp)->HasTypeParam()) {
      typeAttrs.SetAttr(ATTR_generic);
    }
    vecTyIdx.push_back(tyIdxTmp);
    vecAttrs.push_back(typeAttrs);
  }
  // parse return type
  lexer.NextToken();
  TyIdx retTyIdx(0);
  if (!ParseType(retTyIdx)) {
    Error("expect return type for function type but get ");
    return false;
  }
  MIRType *funcType =
      GlobalTables::GetTypeTable().GetOrCreateFunctionType(&mod, retTyIdx, vecTyIdx, vecAttrs, false, true);
  tyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(funcType);
  return true;
}

// parse the generic type instantiation vector enclosed inside braces; syntax
// is: { <type-param> = <real-type> [, <type-param> = <real-type>] }
// where the contents enclosed in [ and ] can occur 0 or more times
bool MIRParser::ParseGenericInstantVector(GenericInstantVector &instantVec) {
  TokenKind tokenKind;
  TyIdx typeParmIdx;
  do {
    tokenKind = lexer.NextToken();  // skip the lbrace or comma
    if (!ParseTypeParam(typeParmIdx)) {
      Error("type parameter incorrectly specified in generic type/function instantiation at ");
      return false;
    }
    tokenKind = lexer.GetTokenKind();
    if (tokenKind != kTkEqsign) {
      Error("missing = in generic type/function instantiation at ");
      return false;
    }
    tokenKind = lexer.NextToken();  // skip the =
    TyIdx realTyIdx;
    if (!ParseType(realTyIdx)) {
      Error("error parsing type in generic type/function instantiation at ");
      return false;
    }
    instantVec.push_back(TypePair(typeParmIdx, realTyIdx));
    tokenKind = lexer.GetTokenKind();
    if (tokenKind == kTkRbrace) {
      lexer.NextToken();  // skip the rbrace
      return true;
    }
  } while (tokenKind == kTkComa);
  Error("error parsing generic type/function instantiation at ");
  return false;
}

bool MIRParser::ParseDerivedType(TyIdx &tyIdx, MIRTypeKind kind) {
  if (lexer.GetTokenKind() != kTkLangle) {
    Error("expect langle but get ");
    return false;
  }
  TokenKind ltk = lexer.NextToken();
  if (IsPrimitiveType(ltk)) {
    if (!ParsePrimType(tyIdx)) {
      Error("ParseDerivedType failed when parsing tyIdx at ");
      return false;
    }
  } else {
    switch (ltk) {
      case kTkAsterisk:  // point type
      case TK_func:
        if (!ParsePointType(tyIdx)) {
          Error("point type wrong when parsing derived type at ");
          return false;
        }
        break;
      case kTkLbrack:  // array type
        if (!ParseArrayType(tyIdx)) {
          Error("array type wrong when parsing derived type at ");
          return false;
        }
        break;
      case TK_struct:            // struct type
      case TK_structincomplete:  // structincomplete type
      case TK_union:             // union type
        if (!ParseStructType(tyIdx)) {
          Error("struct/union type wrong when parsing derived type at ");
          return false;
        }
        break;
      case TK_class:  // class type
      case TK_classincomplete:
        if (!ParseClassType(tyIdx)) {
          Error("class type wrong when parsing derived type at ");
          return false;
        }
        break;
      case TK_interface:  // interface type
      case TK_interfaceincomplete:
        if (!ParseInterfaceType(tyIdx)) {
          Error("interface type wrong when parsing derived type at ");
          return false;
        }
        break;
      case kTkLname:  // local type
      case kTkGname:  // global type
        if (!ParseDefinedTypename(tyIdx, kind)) {
          Error("type name wrong when parsing derived type at ");
          return false;
        }
        if (lexer.GetTokenKind() == kTkLbrace) {
          MIRGenericInstantType genericinstty(tyIdx);
          if (!ParseGenericInstantVector(genericinstty.GetInstantVec())) {
            Error("error parsing generic type instantiation at ");
            return false;
          }
          tyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&genericinstty);
        }
        break;
      case kTkTypeparam:
        if (!ParseTypeParam(tyIdx)) {
          Error("type parameter wrong when parsing derived type at ");
          return false;
        }
        break;
      default:
        Error("expect type token but get ");
        return false;
    }
  }
  // parse >
  if (lexer.GetTokenKind() != kTkRangle) {
    Error("expect > parse derived type but get ");
    return false;
  }
  lexer.NextToken();
  return true;
}

void MIRParser::FixupForwardReferencedTypeByMap() {
  for (size_t i = 1; i < GlobalTables::GetTypeTable().GetTypeTable().size(); i++) {
    MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(TyIdx(i));
    if (type->GetKind() == kTypePointer) {
      MIRPtrType *ptrType = static_cast<MIRPtrType*>(type);
      std::map<TyIdx, TyIdx>::iterator it = typeDefIdxMap.find(ptrType->GetPointedTyIdx());
      if (it != typeDefIdxMap.end()) {
        ptrType->SetPointedTyIdx(it->second);
      }
    } else if (type->GetKind() == kTypeStruct || type->GetKind() == kTypeStructIncomplete ||
               type->GetKind() == kTypeUnion || type->GetKind() == kTypeClass ||
               type->GetKind() == kTypeClassIncomplete || type->GetKind() == kTypeInterface ||
               type->GetKind() == kTypeInterfaceIncomplete) {
      if (type->GetKind() == kTypeClass || type->GetKind() == kTypeClassIncomplete) {
        MIRClassType *classType = static_cast<MIRClassType*>(type);
        std::map<TyIdx, TyIdx>::iterator it = typeDefIdxMap.find(classType->GetParentTyIdx());
        if (it != typeDefIdxMap.end()) {
          classType->GetParentTyIdx() = it->second;
        }
        for (size_t j = 0; j < classType->GetInerfaceImplemented().size(); j++) {
          std::map<TyIdx, TyIdx>::iterator it2 = typeDefIdxMap.find(classType->GetNthInerfaceImplemented(j));
          if (it2 != typeDefIdxMap.end()) {
            classType->SetNthInerfaceImplemented(j, it2->second);
          }
        }
      } else if (type->GetKind() == kTypeInterface || type->GetKind() == kTypeInterfaceIncomplete) {
        MIRInterfaceType *interfaceType = static_cast<MIRInterfaceType*>(type);
        for (uint32 j = 0; j < interfaceType->GetParentsTyIdx().size(); j++) {
          std::map<TyIdx, TyIdx>::iterator it = typeDefIdxMap.find(interfaceType->GetParentsElementTyIdx(j));
          if (it != typeDefIdxMap.end()) {
            interfaceType->SetParentsElementTyIdx(j, it->second);
          }
        }
      }
      MIRStructType *structType = static_cast<MIRStructType*>(type);
      for (uint32 j = 0; j < structType->GetFieldsSize(); j++) {
        TyIdx fieldTyIdx = structType->GetElemTyIdx(j);
        std::map<TyIdx, TyIdx>::iterator it = typeDefIdxMap.find(fieldTyIdx);
        if (it != typeDefIdxMap.end()) {
          structType->SetElemtTyIdx(j, it->second);
        }
      }
      for (size_t j = 0; j < structType->GetStaticFields().size(); j++) {
        TyIdx fieldTyIdx = structType->GetStaticElemtTyIdx(j);
        std::map<TyIdx, TyIdx>::iterator it = typeDefIdxMap.find(fieldTyIdx);
        if (it != typeDefIdxMap.end()) {
          structType->SetStaticElemtTyIdx(j, it->second);
        }
      }
      for (size_t j = 0; j < structType->GetMethods().size(); j++) {
        TyIdx methodTyIdx = structType->GetMethodsElement(j).second.first;
        std::map<TyIdx, TyIdx>::iterator it = typeDefIdxMap.find(methodTyIdx);
        if (it != typeDefIdxMap.end()) {
          structType->SetMethodTyIdx(j, it->second);
        }
      }
    }
  }
}

bool MIRParser::ParseTypedef() {
  bool isLocal = paramParseLocalType;
  if (lexer.GetTokenKind() != TK_type) {
    Error("expect type but get ");
    return false;
  }
  TokenKind tokenKind = lexer.NextToken();
  if (tokenKind != kTkGname && tokenKind != kTkLname) {
    Error("expect type name but get ");
    return false;
  }
  const std::string &name = lexer.GetName();
  GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(name);
  TyIdx prevTyIdx;
  MIRStructType *prevStructType = nullptr;
  TyIdx tyIdx(0);
  // dbginfo class/interface init
  if (tokenKind == kTkGname) {
    if (isLocal) {
      Error("A local type must use local type name ");
      return false;
    }
    prevTyIdx = mod.GetTypeNameTab()->GetTyIdxFromGStrIdx(strIdx);
    if (prevTyIdx != 0) {
      MIRType *prevType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(prevTyIdx);
      prevStructType = dynamic_cast<MIRStructType*>(prevType);
      ASSERT(prevStructType != nullptr, "prevStructType is null");
      if ((prevType->GetKind() != kTypeByName) && (prevStructType && !prevStructType->IsIncomplete())) {
        // allow duplicated type def if kKeepFirst is set which is the default
        if (options & kKeepFirst) {
          lexer.NextToken();
          Warning("redefined global type");
          if (!ParseDerivedType(tyIdx, kTypeUnknown)) {
            Error("error passing derived type at ");
            return false;
          }
          return true;
        } else {
          Error("redefined global type");
          return false;
        }
      }
    }
  } else {
    if (!isLocal) {
      Error("A global type must use global type name ");
      return false;
    }
    prevTyIdx = mod.CurFunction()->GetTypeNameTable()->GetTyIdxFromGStrIdx(strIdx);
    if (prevTyIdx != 0) {
      MIRType *prevType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(prevTyIdx);
      prevStructType = dynamic_cast<MIRStructType*>(prevType);
      if ((prevType->GetKind() != kTypeByName) && (prevStructType && !prevStructType->IsIncomplete())) {
        Error("redefined local type name ");
        return false;
      }
    }
  }
  // at this point,if prev_tyidx is not zero, this type name has been
  // forward-referenced
  tokenKind = lexer.NextToken();
  tyIdx = TyIdx(0);
  if (IsPrimitiveType(tokenKind)) {
    if (!ParsePrimType(tyIdx)) {
      Error("expect primitive type after typedef but get ");
      return false;
    }
  } else if (!ParseDerivedType(tyIdx, kTypeUnknown)) {
    Error("error passing derived type at ");
    return false;
  }
  // for class/interface types, prev_tyidx could also be set during processing
  // so we check again right before SetGStrIdxToTyIdx
  if (isLocal) {
    prevTyIdx = mod.CurFunction()->GetTypeNameTable()->GetTyIdxFromGStrIdx(strIdx);
    mod.CurFunction()->GetTypeNameTable()->SetGStrIdxToTyIdx(strIdx, tyIdx);
    ASSERT(GlobalTables::GetTypeTable().GetTypeTable().empty() == false, "container check");
    if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->GetNameStrIdx() == 0) {
      GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->SetNameStrIdx(strIdx);
      GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->SetNameIsLocal(true);
    }
  } else {
    prevTyIdx = mod.GetTypeNameTab()->GetTyIdxFromGStrIdx(strIdx);
    mod.GetTypeNameTab()->SetGStrIdxToTyIdx(strIdx, tyIdx);
    mod.GetTypeDefOrder().push_back(strIdx);
    ASSERT(GlobalTables::GetTypeTable().GetTypeTable().empty() == false, "container check");
    if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->GetNameStrIdx() == 0) {
      GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->SetNameStrIdx(strIdx);
    }
  }
  if (prevTyIdx != 0 && prevTyIdx != tyIdx) {
    // replace all uses of prev_tyidx by tyIdx in type_table_
    typeDefIdxMap[prevTyIdx] = tyIdx;  // record the real tydix
    // remove prev_tyidx from classlist
    mod.RemoveClass(prevTyIdx);
  }
  // Merge class or interface type at the cross-module level
  ASSERT(GlobalTables::GetTypeTable().GetTypeTable().empty() == false, "container check");
  MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  if (!isLocal && (type->GetKind() == kTypeClass || type->GetKind() == kTypeClassIncomplete ||
                   type->GetKind() == kTypeInterface || type->GetKind() == kTypeInterfaceIncomplete)) {
    prevTyIdx = GlobalTables::GetTypeNameTable().GetTyidxFromGstrIdx(strIdx);
    if (prevTyIdx == 0) {
      GlobalTables::GetTypeNameTable().SetGStrIdxToTyIdx(strIdx, tyIdx);
    } else {
      MIRStructType *structType = static_cast<MIRStructType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx));
      MIRStructType *prevSType = static_cast<MIRStructType*>(GlobalTables::GetTypeTable().GetTypeFromTyIdx(prevTyIdx));
      if (!structType->IsIncomplete()) {
        if (prevSType->IsIncomplete()) {
          // New definition is strong and previous definition is weak.
          GlobalTables::GetTypeNameTable().SetGStrIdxToTyIdx(strIdx, tyIdx);
        } else if (!prevSType->IsIncomplete() && !structType->IsIncomplete()) {
          // Both are strong, something must be wrong
          Error("redefined class/interface type name");
          return false;
        }
      }
    }
    // setup eh root type
    MIRType *ehType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
    if (mod.GetThrowableTyIdx() == 0 &&
        (ehType->GetKind() == kTypeClass || ehType->GetKind() == kTypeClassIncomplete)) {
      GStrIdx ehTypeNameIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(
          NameMangler::GetInternalNameLiteral(NameMangler::kJavaLangObjectStr));
      if (ehTypeNameIdx == ehType->GetNameStrIdx()) {
        mod.SetThrowableTyIdx(tyIdx);
      }
    }
  }
  return true;
}

bool MIRParser::ParseJavaClassInterface(MIRSymbol *symbol, bool isClass) {
  ASSERT(symbol != nullptr, "symbol is null");
  TokenKind tk = lexer.NextToken();
  if (tk != kTkGname) {
    Error("expect global name for javaclass but get ");
    return false;
  }
  symbol->SetNameStrIdx(lexer.GetName());
  lexer.NextToken();
  TyIdx tyidx(0);
  if (!ParseType(tyidx)) {
    Error("ParseType failed trying parsing the type");
    return false;
  }
  MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyidx);
  if (isClass && type->GetKind() != kTypeClass && type->GetKind() != kTypeClassIncomplete) {
    Error("type in javaclass declaration must be of class type at ");
    return false;
  } else if (!isClass && type->GetKind() != kTypeInterface && type->GetKind() != kTypeInterfaceIncomplete) {
    Error("type in javainterface declaration must be of interface type at ");
    return false;
  }
  symbol->SetTyIdx(tyidx);
  if (!ParseTypeAttrs(symbol->GetAttrs())) {
    Error("bad type attribute in variable declaration at ");
    return false;
  }
  if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyidx)->HasTypeParam()) {
    symbol->SetAttr(ATTR_generic);
  }
  return true;
}

bool MIRParser::ParseStorageClass(MIRSymbol *symbol) const {
  TokenKind tk = lexer.GetTokenKind();
  switch (tk) {
    case TK_fstatic:
      symbol->SetStorageClass(kScFstatic);
      return true;
    case TK_pstatic:
      symbol->SetStorageClass(kScPstatic);
      return true;
    case TK_extern:
      symbol->SetStorageClass(kScExtern);
      return true;
    default:
      break;
  }
  return false;
}

bool MIRParser::ParseDeclareReg(MIRSymbol *symbol, MIRFunction *func) {
  ASSERT(symbol != nullptr, "symbol is null");
  TokenKind tk = lexer.GetTokenKind();
  // i.e, reg %1 u1
  if (tk != TK_reg) {  // reg
    Error("expect reg bug get ");
    return false;
  }
  TokenKind regNumTK = lexer.NextToken();
  if (regNumTK != kTkPreg) {
    Error("expect preg but get");
    return false;
  }
  uint32 thePRegNo = static_cast<uint32>(lexer.GetTheIntVal());
  lexer.NextToken();
  // parse ty
  TyIdx tyIdx(0);
  if (!ParseType(tyIdx)) {
    Error("ParseDeclarePreg failed while parsing the type");
    return false;
  }
  ASSERT(tyIdx.GetIdx() > 0, "parse declare preg failed");
  if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->GetKind() == kTypeByName) {
    Error("type in var declaration cannot be forward-referenced at ");
    return false;
  }
  symbol->SetTyIdx(tyIdx);
  MIRType *mirType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  PregIdx pRegIdx = LookupOrCreatePregIdx(thePRegNo, mirType->GetPrimType() == PTY_ref, func);
  MIRPregTable *pRegTab = func->GetPregTab();
  MIRPreg *preg = pRegTab->PregFromPregIdx(pRegIdx);
  preg->SetIsRef(mirType->GetPrimType() == PTY_ref);
  preg->SetPrimType(mirType->GetPrimType());
  symbol->SetPreg(preg);
  if (!ParseVarTypeAttrs(symbol)) {
    Error("bad type attribute in variable declaration at ");
    return false;
  }
  if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->HasTypeParam()) {
    symbol->SetAttr(ATTR_generic);
    mod.CurFunction()->GetFuncAttrs().SetAttr(FUNCATTR_generic);
  }
  return true;
}

bool MIRParser::ParseDeclareVar(MIRSymbol *symbol) {
  ASSERT(symbol != nullptr, "symbol is null");
  TokenKind tk = lexer.GetTokenKind();
  // i.e, var %i i32
  if (tk != TK_var && tk != TK_tempvar) {  // var
    Error("expect var but get ");
    return false;
  }
  bool isLocal = symbol->IsLocal();
  // %i
  TokenKind nameTk = lexer.NextToken();
  if (isLocal) {
    if (nameTk == TK_static) {
      symbol->SetStorageClass(kScPstatic);
      nameTk = lexer.NextToken();
    }
    if (nameTk != kTkLname) {
      Error("expect local name but get ");
      return false;
    }
  } else {
    if (nameTk != kTkGname) {
      Error("expect global name but get ");
      return false;
    }
  }
  GStrIdx symbolStrID = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
  symbol->SetNameStrIdx(symbolStrID);
  tk = lexer.NextToken();
  if (ParseStorageClass(symbol)) {
    lexer.NextToken();
  }
  // i32
  TyIdx tyIdx(0);
  if (!ParseType(tyIdx)) {
    Error("ParseDeclareVar failed when parsing the type");
    return false;
  }
  ASSERT(tyIdx.GetIdx() > 0, "parse declare var failed ");
  if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->GetKind() == kTypeByName) {
    Error("type in var declaration cannot be forward-referenced at ");
    return false;
  }
  symbol->SetTyIdx(tyIdx);
  if (!ParseVarTypeAttrs(symbol)) {
    Error("bad type attribute in variable declaration at ");
    return false;
  }
  if (symbol->GetStorageClass() == kScExtern && symbol->IsStatic()) {
    const std::string &staticFieldName = symbol->GetName();
    size_t pos = staticFieldName.find(NameMangler::kClassNameSplitterStr) + 3;
    if (pos != 0 && pos != std::string::npos) {
      std::string className = staticFieldName.substr(0, pos);
      MIRSymbol *classSt =
          GlobalTables::GetGsymTable().GetSymbolFromStrIdx(GlobalTables::GetStrTable().GetStrIdxFromName(className));
      if (classSt != nullptr) {
        symbol->SetStorageClass(kScGlobal);
      }
    }
  }
  if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx)->HasTypeParam()) {
    symbol->SetAttr(ATTR_generic);
    if (isLocal) {
      mod.CurFunction()->GetFuncAttrs().SetAttr(FUNCATTR_generic);
    }
  }
  tk = lexer.GetTokenKind();
  // take a look if there are any initialized values
  if (tk == kTkEqsign) {
    // parse initialized values
    MIRConst *mirConst = nullptr;
    lexer.NextToken();
    if (!ParseInitValue(mirConst, tyIdx)) {
      Error("wrong initialiaton value at ");
      return false;
    }
    symbol->SetKonst(mirConst);
  }
  return true;
}

bool MIRParser::ParsePrototype(MIRFunction *func, MIRSymbol *funcSymbol, TyIdx &funcTyIdx) {
  ASSERT(func != nullptr, "func is null");
  ASSERT(funcSymbol != nullptr, "funcSymbol is null");
  if (lexer.GetTokenKind() == kTkLbrace) {
    if (mod.GetFlavor() < kMmpl) {
      Error("funcion prototype missing for non-MMPL flavor of Maple IR");
      return false;
    }
    // mmpl flavor has no prototype declaration, return normally
    return true;
  }
  std::vector<TyIdx> vecType;       // for storing the parameter types
  std::vector<TypeAttrs> vecAttrs;  // for storing the parameter type attributes
  // this part for parsing the argument list and return type
  if (lexer.GetTokenKind() != kTkLparen) {
    Error("expect ( for func but get ");
    return false;
  }
  // parse parameters
  bool varArgs = false;
  TokenKind pmTk = lexer.NextToken();
  if (pmTk != kTkRparen) {
    if (pmTk == kTkDotdotdot) {
      varArgs = true;
      func->SetVarArgs();
      pmTk = lexer.NextToken();
      if (pmTk != kTkRparen) {
        Error("expect ) after ... but get");
        return false;
      }
    } else {
      MIRSymbol *symbol = func->GetSymTab()->CreateSymbol(kScopeLocal);
      ASSERT(symbol != nullptr, "Failed to create MIRSymbol");
      symbol->SetStorageClass(kScFormal);
      TokenKind symbolTK = lexer.GetTokenKind();
      if (symbolTK == TK_reg) {
        symbol->SetSKind(kStPreg);
        if (!ParseDeclareReg(symbol, func)) {
          Error("ParseFunction expect preg for parameter");
          return false;
        }
        func->AddFormal(symbol);
        vecType.push_back(symbol->GetTyIdx());
        vecAttrs.push_back(symbol->GetAttrs());
        if (!ParsePrototypeRemaining(func, vecType, vecAttrs, varArgs)) {
          return false;
        }
      } else {
        symbol->SetSKind(kStVar);
        if (!ParseDeclareVar(symbol)) {
          Error("ParseFunction expect scalar value");
          return false;
        }
        (void)func->GetSymTab()->AddToStringSymbolMap(symbol);
        func->AddFormal(symbol);
        vecType.push_back(symbol->GetTyIdx());
        vecAttrs.push_back(symbol->GetAttrs());
        if (!ParsePrototypeRemaining(func, vecType, vecAttrs, varArgs)) {
          return false;
        }
      }
    }
  }
  // parse return type
  lexer.NextToken();
  TyIdx tyIdx(0);
  if (!ParseType(tyIdx)) {
    return false;
  }
  MIRType *retType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  func->SetReturnStruct(retType);
  MIRType *funcType =
      GlobalTables::GetTypeTable().GetOrCreateFunctionType(&mod, tyIdx, vecType, vecAttrs, varArgs, true);
  funcTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(funcType);
  funcSymbol->SetTyIdx(funcTyIdx);
  func->SetMIRFuncType(static_cast<MIRFuncType*>(funcType));
  return true;
}

// if prototype declaration, only create the symbol and type;
// if a redeclaration, re-process the symbol and type declaration;
// if function declaration, link MIRFunction to ->mod in addition
bool MIRParser::ParseFunction(uint32 fileIdx) {
  TokenKind tokenKind = lexer.GetTokenKind();
  if (tokenKind != TK_func) {
    Error("expect func but get ");
    return false;
  }
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkGname && lexer.GetTokenKind() != kTkFname) {
    Error("expect function name for func but get ");
    return false;
  }
  const std::string &funcName = lexer.GetName();
  GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(funcName);
  MIRSymbol *funcSymbol = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(strIdx);
  MIRFunction *func = nullptr;
  lexer.NextToken();
  FuncAttrs funcAttrs;
  if (!ParseFuncAttrs(funcAttrs)) {
    Error("bad function attribute in function declaration at ");
    return false;
  }
  if (funcSymbol != nullptr) {
    // there has been an earlier forward declaration, so check consistency
    if (funcSymbol->GetStorageClass() != kScText || funcSymbol->GetSKind() != kStFunc) {
      Error("redeclaration of name as func in ");
      return false;
    }
    if (funcSymbol->GetFunction()->GetBody()) {
      // Function definition has been processed. Here it may be
      // another declaration due to multi-mpl merge. If this
      // is indeed another definition, we will throw error.
      MIRSymbol *tmpSymbol = mod.GetMemPool()->New<MIRSymbol>();
      tmpSymbol->SetStorageClass(kScText);
      tmpSymbol->SetSKind(kStFunc);
      MIRFunction *tmpFunc = mod.GetMemPool()->New<MIRFunction>(&mod, tmpSymbol->GetStIdx());
      tmpFunc->Init();
      tmpSymbol->SetFunction(tmpFunc);
      TyIdx tmpTyIdx;
      if (!ParsePrototype(tmpFunc, tmpSymbol, tmpTyIdx)) {
        return false;
      }
      if (lexer.GetTokenKind() == kTkLbrace) {
        Error("function body defined second time in ");
        return false;
      }
      return true;
    }
    // Skip attribute checking
    func = funcSymbol->GetFunction();
    func->ClearFormals();
    func->GetArgumentsTyIdx().clear();
    func->GetArgumentsAttrs().clear();
    func->SetSymTab(mod.GetMemPool()->New<MIRSymbolTable>(&mod.GetMPAllocator()));
    func->SetPregTab(mod.GetMemPool()->New<MIRPregTable>(&mod, &mod.GetMPAllocator()));
    func->SetTypeNameTab(mod.GetMemPool()->New<MIRTypeNameTable>(&mod.GetMPAllocator()));
    func->SetLabelTab(mod.GetMemPool()->New<MIRLabelTable>(&mod.GetMPAllocator()));
    // update with current attr
    if (funcAttrs.GetAttrFlag()) {
      if (func->IsIpaSeen()) {
        funcAttrs.SetAttr(FUNCATTR_ipaseen);
      }
      if (func->IsNoDefEffect()) {
        funcAttrs.SetAttr(FUNCATTR_nodefeffect);
      }
      if (func->IsNoRetNewlyAllocObj()) {
        funcAttrs.SetAttr(FUNCATTR_noret_newly_alloc_obj);
      }
      if (func->IsPure()) {
        funcAttrs.SetAttr(FUNCATTR_pure);
      }
      if (func->IsNoThrowException()) {
        funcAttrs.SetAttr(FUNCATTR_nothrow_exception);
      }
      if (func->IsNoUseEffect()) {
        funcAttrs.SetAttr(FUNCATTR_nouseeffect);
      }
      if (func->IsNoPrivateUseEffect()) {
        funcAttrs.SetAttr(FUNCATTR_noprivate_useeffect);
      }
      if (func->IsNoPrivateDefEffect()) {
        funcAttrs.SetAttr(FUNCATTR_noprivate_defeffect);
      }
      func->SetFuncAttrs(funcAttrs);
    }
  } else {
    maple::MIRBuilder mirBuilder(&mod);
    funcSymbol = mirBuilder.CreateSymbol(TyIdx(0), strIdx, kStFunc, kScText, nullptr, kScopeGlobal);
    func = mod.GetMemPool()->New<MIRFunction>(&mod, funcSymbol->GetStIdx());
    func->Init();
    func->SetPuidx(GlobalTables::GetFunctionTable().GetFuncTable().size());
    GlobalTables::GetFunctionTable().GetFuncTable().push_back(func);
    funcSymbol->SetFunction(func);
    func->GetFuncAttrs() = funcAttrs;
  }
  func->SetFileIndex(fileIdx);
  curFunc = func;
  if (mod.IsJavaModule()) {
    func->SetBaseClassFuncNames(funcSymbol->GetNameStrIdx());
  }
  TyIdx funcTyidx;
  if (!ParsePrototype(func, funcSymbol, funcTyidx)) {
    return false;
  }
  if (lexer.GetTokenKind() == kTkLbrace) {  // #2 parse Function body
    definedLabels.clear();
    maxPregNo = 0;
    ResetMaxPregNo(func);  // reset the maxPregNo due to the change of parameters
    mod.SetCurFunction(func);
    mod.AddFunction(func);
    // set maple line number for function
    func->GetSrcPosition().SetMplLineNum(lexer.GetLineNum());
    // initialize source line number to be 0
    // to avoid carrying over info from previous function
    firstLineNum = 0;
    lastLineNum = 0;
    func->NewBody();
    BlockNode *block = nullptr;
    if (!ParseStmtBlock(block)) {
      Error("ParseFunction failed when parsing stmt block");
      ResetCurrentFunction();
      return false;
    }
    func->SetBody(block);
    mod.CurFunction()->GetPregTab()->SetIndex(maxPregNo + 1);
    // set source file number for function
    func->GetSrcPosition().SetLineNum(firstLineNum);
    func->GetSrcPosition().SetFileNum(lastFileNum);
    // check if any local type name is undefined
    for (auto it : func->GetTypeNameTab()->GetGStrIdxToTyIdxMap()) {
      MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(it.second);
      if (type->GetKind() == kTypeByName) {
        std::string strStream;
        const std::string &name = GlobalTables::GetStrTable().GetStringFromStrIdx(it.first);
        strStream += "type %";
        strStream += name;
        strStream += " used but not defined\n";
        message += strStream;
        ResetCurrentFunction();
        return false;
      }
    }
  }
  ResetCurrentFunction();
  return true;
}

bool MIRParser::ParseInitValue(MIRConstPtr &theConst, TyIdx tyIdx) {
  TokenKind tokenKind = lexer.GetTokenKind();
  MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyIdx);
  ASSERT(type != nullptr, "type is null");
  if (tokenKind != kTkLbrack) {  // scalar
    MIRConst *mirConst = nullptr;
    if (IsConstValue(tokenKind)) {
      if (!ParseScalarValue(mirConst, type)) {
        Error("ParseInitValue expect scalar value");
        return false;
      }
      lexer.NextToken();
    } else if (IsConstAddrExpr(tokenKind)) {
      if (!ParseConstAddrLeafExpr(mirConst, type)) {
        Error("ParseInitValue expect const addr expr");
        return false;
      }
    } else {
      Error("initialiation value expected but get ");
      return false;
    }
    theConst = mirConst;
  } else {  // aggregates
    if (type->GetKind() == kTypeArray) {
      MIRArrayType *arrayType = static_cast<MIRArrayType*>(type);
      MIRType *elemType = GlobalTables::GetTypeTable().GetTypeFromTyIdx(arrayType->GetElemTyIdx());
      MIRAggConst *newConst = mod.GetMemPool()->New<MIRAggConst>(&mod, type);
      theConst = newConst;
      MapleVector<MIRConst*> &constVec = newConst->GetConstVec();
      tokenKind = lexer.NextToken();
      if (tokenKind == kTkRbrack) {
        Error("illegal empty initialization for array at ");
        return false;
      }
      do {
        // parse single const or another dimension array
        MIRConst *subConst = nullptr;
        if (IsConstValue(tokenKind)) {
          if (!ParseScalarValue(subConst, elemType)) {
            Error("ParseInitValue expect scalar value");
            return false;
          }
          lexer.NextToken();
        } else if (IsConstAddrExpr(tokenKind)) {
          if (!ParseConstAddrLeafExpr(subConst, type)) {
            Error("ParseInitValue expect const addr expr");
            return false;
          }
        } else if (tokenKind == kTkLbrack) {
          if (elemType->GetKind() == kTypeStruct && arrayType->GetDim() == 1) {
            if (!ParseInitValue(subConst, arrayType->GetElemTyIdx())) {
              Error("initializaton value wrong when parsing structure array ");
              return false;
            }
          } else {
            std::vector<uint32> sizeSubArray;
            ASSERT(arrayType->GetDim() > 1, "array dim must large then 1");
            for (uint16 i = 1; i < arrayType->GetDim(); i++) {
              sizeSubArray.push_back(arrayType->GetSizeArrayItem(i));
            }
            MIRArrayType subArraytype(elemType->GetTypeIndex(), sizeSubArray);
            TyIdx arrayTyIdx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&subArraytype);
            if (!ParseInitValue(subConst, arrayTyIdx)) {
              Error("initializaton value wrong when parsing sub array ");
              return false;
            }
          }
        } else {
          Error("expect const value or group of const values but get ");
          return false;
        }
        constVec.push_back(subConst);
        // parse comma or rbrack
        tokenKind = lexer.GetTokenKind();
        if (tokenKind == kTkComa) {
          tokenKind = lexer.NextToken();
          if (tokenKind == kTkRbrack) {
            Error("not expect, followed by ] ");
            return false;
          }
        }
      } while (tokenKind != kTkRbrack);
      lexer.NextToken();
    } else if (type->GetKind() == kTypeStruct) {
      MIRAggConst *newConst = mod.GetMemPool()->New<MIRAggConst>(&mod, type);
      uint32 theFieldID;
      TyIdx fieldTyIdx;
      theConst = newConst;
      MapleVector<MIRConst*> &constVec = newConst->GetConstVec();
      tokenKind = lexer.NextToken();
      if (tokenKind == kTkRbrack) {
        Error("illegal empty initialization for struct at ");
        return false;
      }
      do {
        if (lexer.GetTokenKind() != kTkIntconst) {
          Error("expect field ID in struct initialization but get ");
          return false;
        }
        theFieldID = lexer.GetTheIntVal();
        if (lexer.NextToken() != kTkEqsign) {
          Error("expect = after field ID in struct initialization but get ");
          return false;
        }
        fieldTyIdx = static_cast<MIRStructType*>(type)->GetFieldTyIdx(theFieldID);
        if (fieldTyIdx == 0) {
          Error("field ID out of range at struct initialization at ");
          return false;
        }
        tokenKind = lexer.NextToken();
        MIRConst *subConst = nullptr;
        if (IsConstValue(tokenKind)) {
          if (!ParseScalarValue(subConst, GlobalTables::GetTypeTable().GetTypeFromTyIdx(fieldTyIdx))) {
            Error("ParseInitValue expect scalar value");
            return false;
          }
          lexer.NextToken();
        } else if (IsConstAddrExpr(tokenKind)) {
          if (!ParseConstAddrLeafExpr(subConst, type)) {
            Error("ParseInitValue expect const addr expr");
            return false;
          }
        } else if (tokenKind == kTkLbrack) {
          if (!ParseInitValue(subConst, fieldTyIdx)) {
            Error("parse init value wrong when parse sub struct ");
            return false;
          }
        } else {
          Error("expect const value or group of const values but get ");
          return false;
        }
        ASSERT(subConst != nullptr, "subConst is null in MIRParser::ParseInitValue");
        subConst->SetFieldID(theFieldID);
        constVec.push_back(subConst);
        tokenKind = lexer.GetTokenKind();
        // parse comma or rbrack
        if (tokenKind == kTkComa) {
          tokenKind = lexer.NextToken();
          if (tokenKind == kTkRbrack) {
            Error("not expect \',\' followed by ] ");
            return false;
          }
        }
      } while (tokenKind != kTkRbrack);
      lexer.NextToken();
    } else {
      Error("non-struct should not have aggregate initialization in ");
      return false;
    }
  }
  return true;
}

bool MIRParser::ParseFuncInfo(void) {
  if (lexer.GetTokenKind() != kTkLbrace) {
    Error("expect left brace after funcinfo but get ");
    return false;
  }
  MIRFunction *func = mod.CurFunction();
  TokenKind tokenKind = lexer.NextToken();
  while (tokenKind == TK_label) {
    GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
    tokenKind = lexer.NextToken();
    if (tokenKind == kTkIntconst) {
      uint32 fieldVal = lexer.GetTheIntVal();
      func->GetInfoVector().push_back(MIRInfoPair(strIdx, fieldVal));
      func->InfoIsString().push_back(false);
    } else if (tokenKind == kTkString) {
      GStrIdx literalStrIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
      func->GetInfoVector().push_back(MIRInfoPair(strIdx, literalStrIdx.GetIdx()));
      func->InfoIsString().push_back(true);
    } else {
      Error("illegal value after funcinfo field name at ");
      return false;
    }
    tokenKind = lexer.NextToken();
    if (tokenKind == kTkRbrace) {
      lexer.NextToken();
      return true;
    }
    if (tokenKind == kTkComa) {
      tokenKind = lexer.NextToken();
    } else {
      Error("expect comma after funcinfo field value but get ");
      return false;
    }
  }
  Error("expect field name in funcinfo but get ");
  return false;
}

bool MIRParser::ParseAlias(StmtNodePtr &stmt) {
  TokenKind nameTk = lexer.NextToken();
  if (nameTk != kTkLname) {
    Error("expect local in ALIAS but get ");
    return false;
  }
  GStrIdx srcStrIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
  nameTk = lexer.NextToken();
  if (nameTk != kTkLname) {
    Error("expect local in ALIAS but get ");
    return false;
  }
  GStrIdx mplStrIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
  lexer.NextToken();
  TyIdx tyIdx(0);
  if (!ParseType(tyIdx)) {
    Error("parseType failed when parsing ALIAS ");
    return false;
  }
  GStrIdx signStrIdx(0);
  if (lexer.GetTokenKind() == kTkString) {
    // ignore the signature string
    lexer.NextToken();
  }
  MIRAliasVars aliasVar;
  aliasVar.memPoolStrIdx = mplStrIdx;
  aliasVar.tyIdx = tyIdx;
  aliasVar.sigStrIdx = signStrIdx;
  mod.CurFunction()->SetAliasVarMap(srcStrIdx, aliasVar);
  return true;
}

uint8 *MIRParser::ParseWordsInfo(uint32 size) {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkEqsign) {
    Error("expect = after it but get ");
    return nullptr;
  }
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkLbrack) {
    Error("expect [ for it but get ");
    return nullptr;
  }
  uint8 *origp = static_cast<uint8*>(mod.GetMemPool()->Malloc(BlockSize2BitVectorSize(size)));
  // initialize it based on the input
  for (uint32 *p = reinterpret_cast<uint32*>(origp); lexer.NextToken() == kTkIntconst; p++) {
    *p = static_cast<uint32>(lexer.GetTheIntVal());
  }
  if (lexer.GetTokenKind() != kTkRbrack) {
    Error("expect ] at end of globalwordstypetagged but get ");
    return nullptr;
  }
  lexer.NextToken();
  return origp;
}

static void GenJStringType(MIRModule *module) {
  MIRStructType metaClassType(kTypeStructIncomplete);
  GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName("dummy");
  metaClassType.GetFields().push_back(FieldPair(stridx, TyIdxFieldAttrPair(TyIdx(PTY_ref), FieldAttrs())));
  stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName("__class_meta__");
  TyIdx tyidx = GlobalTables::GetTypeTable().GetOrCreateMIRType(&metaClassType);
  // Global?
  module->GetTypeNameTab()->SetGStrIdxToTyIdx(stridx, tyidx);
  ASSERT(GlobalTables::GetTypeTable().GetTypeTable().empty() == false, "container check");
  if (GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyidx)->GetNameStrIdx() == 0) {
    GlobalTables::GetTypeTable().GetTypeFromTyIdx(tyidx)->SetNameStrIdx(stridx);
  }
}

bool MIRParser::ParseMIR(std::ifstream *mplfile) {
  std::ifstream *origFile = lexer.GetFile();
  // parse mplfile
  lexer.SetFile(mplfile);
  // try to read the first line
  if (lexer.ReadALine() < 0) {
    lexer.lineNum = 0;
  } else {
    lexer.lineNum = 1;
  }
  // for optimized functions file
  bool status = ParseMIR(0, kParseOptFunc);
  // restore airFile
  lexer.SetFile(origFile);
  return status;
}

bool MIRParser::ParseMIR(uint32 fileIdx, uint32 option, bool isIPA, bool isComb) {
  if ((option & kParseOptFunc) == 0) {
    PrepareParsingMIR();
  }
  if (option != 0) {
    this->options |= option;
  }
  // profiling setup
  mod.SetWithProfileInfo(((this->options & kWithProfileInfo) != 0));
  bool atEof = false;
  paramFileIdx = fileIdx;
  paramIsIPA = isIPA;
  paramIsComb = isComb;
  lexer.NextToken();
  while (!atEof) {
    paramTokenKind = lexer.GetTokenKind();
    std::map<TokenKind, FuncPtrParseMIRForElem>::iterator itFuncPtr = funcPtrMapForParseMIR.find(paramTokenKind);
    if (itFuncPtr == funcPtrMapForParseMIR.end()) {
      if (paramTokenKind == kTkEof) {
        atEof = true;
      } else {
        Error("expect func or var but get ");
        return false;
      }
    } else {
      if (!(this->*(itFuncPtr->second))()) {
        return false;
      }
    }
  }
  // fix the typedef type
  FixupForwardReferencedTypeByMap();
  // check if any global type name is undefined
  for (auto it = mod.GetTypeNameTab()->GetGStrIdxToTyIdxMap().begin();
       it != mod.GetTypeNameTab()->GetGStrIdxToTyIdxMap().end(); it++) {
    MIRType *type = GlobalTables::GetTypeTable().GetTypeFromTyIdx(it->second);
    CHECK_FATAL(type != nullptr, "type is null");
    if (type->GetKind() == kTypeByName) {
      std::string strStream;
      const std::string &name = GlobalTables::GetStrTable().GetStringFromStrIdx(it->first);
      strStream += "type $";
      strStream += name;
      strStream += " used but not defined\n";
      message += strStream;
      return false;
    }
  }
  if (!isIPA && isComb) {
    for (auto it = paramImportFileList.begin(); it != paramImportFileList.end(); it++) {
      BinaryMplt binmplt(mod);
      std::string importfilename = *it;
      if (!binmplt.Import(importfilename, false, true)) {  // not a binary mplt
        std::ifstream mpltFile(importfilename);
        if (!mpltFile.is_open()) {
          FATAL(kLncFatal, "cannot open MPLT file: %s\n", importfilename.c_str());
        }
        bool failedParse = !ParseMPLT(&mpltFile, importfilename);
        mpltFile.close();
        if (failedParse) {
          return false;
        }
      }
    }
  }
  return true;
}

std::map<TokenKind, MIRParser::FuncPtrParseMIRForElem> MIRParser::InitFuncPtrMapForParseMIR() {
  std::map<TokenKind, MIRParser::FuncPtrParseMIRForElem> funcPtrMap;
  funcPtrMap[TK_func] = &MIRParser::ParseMIRForFunc;
  funcPtrMap[TK_tempvar] = &MIRParser::ParseMIRForVar;
  funcPtrMap[TK_var] = &MIRParser::ParseMIRForVar;
  funcPtrMap[TK_javaclass] = &MIRParser::ParseMIRForClass;
  funcPtrMap[TK_javainterface] = &MIRParser::ParseMIRForInterface;
  funcPtrMap[TK_type] = &MIRParser::ParseTypedef;
  funcPtrMap[TK_flavor] = &MIRParser::ParseMIRForFlavor;
  funcPtrMap[TK_srclang] = &MIRParser::ParseMIRForSrcLang;
  funcPtrMap[TK_globalmemsize] = &MIRParser::ParseMIRForGlobalMemSize;
  funcPtrMap[TK_globalmemmap] = &MIRParser::ParseMIRForGlobalMemMap;
  funcPtrMap[TK_globalwordstypetagged] = &MIRParser::ParseMIRForGlobalWordsTypeTagged;
  funcPtrMap[TK_globalwordsrefcounted] = &MIRParser::ParseMIRForGlobalWordsRefCounted;
  funcPtrMap[TK_id] = &MIRParser::ParseMIRForID;
  funcPtrMap[TK_numfuncs] = &MIRParser::ParseMIRForNumFuncs;
  funcPtrMap[TK_entryfunc] = &MIRParser::ParseMIRForEntryFunc;
  funcPtrMap[TK_fileinfo] = &MIRParser::ParseMIRForFileInfo;
  funcPtrMap[TK_filedata] = &MIRParser::ParseMIRForFileData;
  funcPtrMap[TK_srcfileinfo] = &MIRParser::ParseMIRForSrcFileInfo;
  funcPtrMap[TK_import] = &MIRParser::ParseMIRForImport;
  funcPtrMap[TK_importpath] = &MIRParser::ParseMIRForImportPath;
  return funcPtrMap;
}

bool MIRParser::ParseMIRForFunc() {
  curFunc = nullptr;
  if (!ParseFunction(paramFileIdx)) {
    return false;
  }
  if ((this->options & kParseOptFunc) && curFunc) {
    curFunc->GetFuncAttrs().SetAttr(FUNCATTR_optimized);
    mod.AddOptFuncs(curFunc);
  }
  return true;
}

bool MIRParser::ParseMIRForVar() {
  MIRSymbol st(0, kScopeGlobal);
  st.SetStorageClass(kScGlobal);
  st.SetSKind(kStVar);
  if (paramTokenKind == TK_tempvar) {
    st.SetIsTmp(true);
  }
  if (!ParseDeclareVar(&st)) {
    return false;
  }
  MIRSymbol *prevSt = GlobalTables::GetGsymTable().GetSymbolFromStrIdx(st.GetNameStrIdx());
  if (prevSt != nullptr) {
    if (prevSt->GetTyIdx() == st.GetTyIdx() &&
        (prevSt->GetStorageClass() == st.GetStorageClass() || prevSt->GetStorageClass() == kScExtern ||
         st.GetStorageClass() == kScExtern) &&
        prevSt->GetSKind() == st.GetSKind() && (prevSt->GetKonst() == nullptr || st.GetKonst() == nullptr)) {
      // previously declared: accumulate new information to the symbol
      prevSt->GetAttrs().SetAttrFlag(prevSt->GetAttrs().GetAttrFlag() | st.GetAttrs().GetAttrFlag());
      if (prevSt->GetKonst() == nullptr) {
        prevSt->SetKonst(st.GetKonst());
      }
      if (prevSt->GetStorageClass() == kScExtern) {
        prevSt->SetStorageClass(st.GetStorageClass());
      }
    } else {
    }
  } else {  // seeing the first time
    maple::MIRBuilder mirBuilder(&mod);
    MIRSymbol *newst = mirBuilder.CreateSymbol(st.GetTyIdx(), st.GetNameStrIdx(), st.GetSKind(), st.GetStorageClass(),
                                               nullptr, kScopeGlobal);
    newst->SetAttrs(st.GetAttrs());
    newst->SetNameStrIdx(st.GetNameStrIdx());
    newst->SetValue(st.GetValue());
  }
  return true;
}

bool MIRParser::ParseMIRForClass() {
  MIRSymbol *st = GlobalTables::GetGsymTable().CreateSymbol(kScopeGlobal);
  st->SetStorageClass(kScInvalid);
  st->SetSKind(kStJavaClass);
  if (!ParseJavaClassInterface(st, true)) {
    return false;
  }
  if (!GlobalTables::GetGsymTable().AddToStringSymbolMap(st)) {
    Error("duplicate symbol name used in javaclass at ");
    return false;
  }
  return true;
}

bool MIRParser::ParseMIRForInterface() {
  MIRSymbol *st = GlobalTables::GetGsymTable().CreateSymbol(kScopeGlobal);
  st->SetStorageClass(kScInvalid);
  st->SetSKind(kStJavaInterface);
  if (!ParseJavaClassInterface(st, false)) {
    return false;
  }
  if (!GlobalTables::GetGsymTable().AddToStringSymbolMap(st)) {
    Error("duplicate symbol name used in javainterface at ");
    return false;
  }
  return true;
}

bool MIRParser::ParseMIRForFlavor() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after flavor but get ");
    return false;
  }
  mod.SetFlavor((MIRFlavor)lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseMIRForSrcLang() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after srclang but get ");
    return false;
  }
  mod.SetSrcLang((MIRSrcLang)lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseMIRForGlobalMemSize() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after globalmemsize but get ");
    return false;
  }
  mod.SetGlobalMemSize(lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseMIRForGlobalMemMap() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkEqsign) {
    Error("expect = after globalmemmap but get ");
    return false;
  }
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkLbrack) {
    Error("expect [ for globalmemmap but get ");
    return false;
  }
  mod.SetGlobalBlockMap(static_cast<uint8*>(mod.GetMemPool()->Malloc(mod.GetGlobalMemSize())));
  // initialize globalblkmap based on the input
  for (uint32 *p = reinterpret_cast<uint32*>(mod.GetGlobalBlockMap()); lexer.NextToken() == kTkIntconst; p++) {
    *p = static_cast<uint32>(lexer.GetTheIntVal());
  }
  if (lexer.GetTokenKind() != kTkRbrack) {
    Error("expect ] at end of globalmemmap but get ");
    return false;
  }
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseMIRForGlobalWordsTypeTagged() {
  uint8 *typeAddr = ParseWordsInfo(mod.GetGlobalMemSize());
  if (typeAddr == nullptr) {
    Error("parser error for globalwordstypetagged");
    return false;
  }
  mod.SetGlobalWordsTypeTagged(typeAddr);
  return true;
}

bool MIRParser::ParseMIRForGlobalWordsRefCounted() {
  uint8 *refAddr = ParseWordsInfo(mod.GetGlobalMemSize());
  if (refAddr == nullptr) {
    Error("parser error for globalwordsrefcounted");
    return false;
  }
  mod.SetGlobalWordsRefCounted(refAddr);
  return true;
}

bool MIRParser::ParseMIRForID() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after id but get ");
    return false;
  }
  mod.SetID(lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseMIRForNumFuncs() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkIntconst) {
    Error("expect integer after numfuncs but get ");
    return false;
  }
  mod.SetNumFuncs(lexer.GetTheIntVal());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseMIRForEntryFunc() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkFname) {
    Error("expect function name for func but get ");
    return false;
  }
  mod.SetEntryFuncName(lexer.GetName());
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseMIRForFileInfo() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkLbrace) {
    Error("expect left brace after fileInfo but get ");
    return false;
  }
  TokenKind tk = lexer.NextToken();
  while (tk == TK_label) {
    GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
    tk = lexer.NextToken();
    if (tk == kTkIntconst) {
      uint32 fieldval = lexer.GetTheIntVal();
      mod.GetFileInfo().push_back(MIRInfoPair(stridx, fieldval));
      mod.GetFileInfoIsString().push_back(false);
    } else if (tk == kTkString) {
      GStrIdx litstridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
      mod.GetFileInfo().push_back(MIRInfoPair(stridx, litstridx.GetIdx()));
      mod.GetFileInfoIsString().push_back(true);
    } else {
      Error("illegal value after fileInfo field name at ");
      return false;
    }
    tk = lexer.NextToken();
    if (tk == kTkRbrace) {
      lexer.NextToken();
      return true;
    }
    if (tk == kTkComa) {
      tk = lexer.NextToken();
    } else {
      Error("expect comma after fileInfo field value but get ");
      return false;
    }
  }
  Error("expect field name in fileInfo but get ");
  return false;
}

bool MIRParser::ParseMIRForFileData() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkLbrace) {
    Error("expect left brace after fileData but get ");
    return false;
  }
  TokenKind tk = lexer.NextToken();
  while (tk == TK_label) {
    GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
    tk = lexer.NextToken();
    std::vector<uint8> data;
    while (tk == kTkIntconst) {
      uint32 fieldval = lexer.GetTheIntVal();
      data.push_back(fieldval);
      tk = lexer.NextToken();
    }
    mod.GetFileData().push_back(MIRDataPair(stridx, data));
    if (tk == kTkComa) {
      tk = lexer.NextToken();
    } else if (tk == kTkRbrace) {
      lexer.NextToken();
      return true;
    } else {
      Error("expect comma after fileData field value but get ");
      return false;
    }
  }
  Error("expect field name in fileData but get ");
  return false;
}

bool MIRParser::ParseMIRForSrcFileInfo() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkLbrace) {
    Error("expect left brace after fileInfo but get ");
    return false;
  }
  TokenKind tk = lexer.NextToken();
  while (tk == kTkIntconst) {
    uint32 fieldval = lexer.GetTheIntVal();
    tk = lexer.NextToken();
    if (tk == kTkString) {
      GStrIdx stridx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
      mod.GetSrcFileInfo().push_back(MIRInfoPair(stridx, fieldval));
    } else {
      Error("illegal value after srcfileinfo field name at ");
      return false;
    }
    tk = lexer.NextToken();
    if (tk == kTkRbrace) {
      lexer.NextToken();
      return true;
    }
    if (tk == kTkComa) {
      tk = lexer.NextToken();
    } else {
      Error("expect comma after srcfileinfo field value but get ");
      return false;
    }
  }
  Error("expect field name in srcfileinfo but get ");
  return false;
}

bool MIRParser::ParseMIRForImport() {
  bool firstImport = true;
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkString) {
    Error("expect file name string after import but get ");
    return false;
  }
  std::string importFileName = lexer.GetName();
  paramImportFileList.push_back(importFileName);
  // check illegal file name for the .mplt file
  std::string::size_type lastDot = importFileName.find_last_of(".");
  if (lastDot == std::string::npos || lastDot != importFileName.length() - strlen(".mplt")) {
    FATAL(kLncFatal, "MPLT file has no or wrong suffix: %s\n", importFileName.c_str());
  }
  if (importFileName.compare(lastDot, strlen(".mplt"), ".mplt") != 0) {
    FATAL(kLncFatal, "MPLT file has wrong suffix: %s\n", importFileName.c_str());
  }
  if (paramIsIPA && firstImport) {
    BinaryMplt *binmplt = new BinaryMplt(mod);
    mod.SetBinMplt(binmplt);
    if (!(*binmplt).Import(importFileName, paramIsIPA && !firstImport, paramIsComb)) {  // not a binary mplt
      std::ifstream mpltFile(importFileName);
      if (!mpltFile.is_open()) {
        FATAL(kLncFatal, "cannot open MPLT file: %s\n", importFileName.c_str());
      }
      bool failedParse = !ParseMPLT(&mpltFile, importFileName);
      mpltFile.close();
      if (failedParse) {  // parse the mplt file
        return false;
      }
    }
  } else {
    BinaryMplt binmplt(mod);
    if (!binmplt.Import(importFileName, paramIsIPA, false)) {  // not a binary mplt
      std::ifstream mpltFile(importFileName);
      if (!mpltFile.is_open()) {
        FATAL(kLncFatal, "cannot open MPLT file: %s\n", importFileName.c_str());
      }
      bool failedParse = !ParseMPLT(&mpltFile, importFileName);
      mpltFile.close();
      if (failedParse) {  // parse the mplt file
        return false;
      }
    }
  }
  if (GlobalTables::GetStrTable().GetStrIdxFromName("__class_meta__") == 0) {
    GenJStringType(&mod);
  }
  GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(importFileName);
  auto it = mod.GetImportFiles().begin();
  mod.GetImportFiles().insert(it, strIdx);
  // record the imported file for later reading summary info, if exists
  mod.GetImportedMplt().push_back(importFileName);
  lexer.NextToken();
  return true;
}

bool MIRParser::ParseMIRForImportPath() {
  lexer.NextToken();
  if (lexer.GetTokenKind() != kTkString) {
    Error("expect path string after importpath but get ");
    return false;
  }
  GStrIdx litStrIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(lexer.GetName());
  mod.GetImportPaths().push_back(litStrIdx);
  lexer.NextToken();
  return true;
}

void MIRParser::PrepareParsingMIR() {
  dummyFunction = CreateDummyFunction();
  mod.SetCurFunction(dummyFunction);
  lexer.PrepareForFile(mod.GetFileName().c_str());
}

bool MIRParser::ParseTypeFromString(const std::string &src, TyIdx &tyIdx) {
  lexer.PrepareForString(src);
  return ParseType(tyIdx);
}

bool MIRParser::ParseMPLT(std::ifstream *mpltFile, const std::string &importFileName) {
  // save relevant values for the main input file
  std::ifstream *airFileSave = lexer.GetFile();
  int lineNumSave = lexer.lineNum;
  std::string modFileNameSave = mod.GetFileName();
  // set up to read next line from the import file
  lexer.curIdx = 0;
  lexer.currentLineSize = 0;
  lexer.SetFile(mpltFile);
  lexer.lineNum = 0;
  mod.SetFileName(importFileName);
  bool atEof = false;
  lexer.NextToken();
  while (!atEof) {
    TokenKind tokenKind = lexer.GetTokenKind();
    switch (tokenKind) {
      default: {
        Error("expect func or var but get ");
        return false;
      }
      case kTkEof:
        atEof = true;
        break;
      case TK_type:
        paramParseLocalType = false;
        if (!ParseTypedef()) {
          return false;
        }
        break;
      case TK_var: {
        tokenKind = lexer.NextToken();
        if (tokenKind == kTkGname) {
          std::string literalName = lexer.GetName();
          GStrIdx strIdx = GlobalTables::GetStrTable().GetOrCreateStrIdxFromName(literalName);
          GlobalTables::GetConstPool().PutLiteralNameAsImported(strIdx);
          lexer.NextToken();
        } else {
          return false;
        }
        break;
      }
    }
  }
  // restore old values to continue reading from the main input file
  lexer.curIdx = 0;  // to force reading new line
  lexer.currentLineSize = 0;
  lexer.lineNum = lineNumSave;
  lexer.SetFile(airFileSave);
  mod.SetFileName(modFileNameSave);
  return true;
}

bool MIRParser::ParseMPLTStandalone(std::ifstream *mpltFile, const std::string &importFileName) {
  PrepareParsingMIR();
  if (!ParseMPLT(mpltFile, importFileName)) {
    return false;
  }
  lexer.lineNum = 0;
  // fix the typedef type
  FixupForwardReferencedTypeByMap();
  return true;
}

bool MIRParser::ParsePrototypeRemaining(MIRFunction *func, std::vector<TyIdx> &vecTyIdx,
                                        std::vector<TypeAttrs> &vecAttrs, bool &varArgs) {
  ASSERT(func != nullptr, "func is null");
  TokenKind pmTk = lexer.GetTokenKind();
  while (pmTk != kTkRparen) {
    // parse ","
    if (pmTk != kTkComa) {
      Error("expect , after a declare var/preg but get");
      return false;
    }
    pmTk = lexer.NextToken();
    if (pmTk == kTkDotdotdot) {
      varArgs = true;
      func->SetVarArgs();
      pmTk = lexer.NextToken();
      if (pmTk != kTkRparen) {
        Error("expect ) after ... but get");
        return false;
      }
      break;
    }
    MIRSymbol *symbol = func->GetSymTab()->CreateSymbol(kScopeLocal);
    symbol->SetStorageClass(kScFormal);
    TokenKind loopStTK = lexer.GetTokenKind();
    if (loopStTK == TK_reg) {
      symbol->SetSKind(kStPreg);
      if (!ParseDeclareReg(symbol, func)) {
        Error("ParseFunction expect scalar value");
        return false;
      }
    } else {
      symbol->SetSKind(kStVar);
      if (!ParseDeclareVar(symbol)) {
        Error("ParseFunction expect scalar value");
        return false;
      }
      (void)func->GetSymTab()->AddToStringSymbolMap(symbol);
    }
    func->AddFormal(symbol);
    vecTyIdx.push_back(symbol->GetTyIdx());
    vecAttrs.push_back(symbol->GetAttrs());
    pmTk = lexer.GetTokenKind();
  }
  return true;
}

void MIRParser::EmitError(const std::string &fileName) {
  if (!strlen(GetError().c_str())) {
    return;
  }
  ERR(kLncErr, "%s \n%s", fileName.c_str(), GetError().c_str());
}

void MIRParser::EmitWarning(const std::string &fileName) {
  if (!strlen(GetWarning().c_str())) {
    return;
  }
  WARN(kLncWarn, "%s \n%s\n", fileName.c_str(), GetWarning().c_str());
}

}  // namespace maple
