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
#ifndef MAPLE_IR_INCLUDE_LEXER_H
#define MAPLE_IR_INCLUDE_LEXER_H
#include "types_def.h"
#include "tokens.h"
#include "mempool_allocator.h"
#include "stdio.h"
#include <fstream>

namespace maple {
class MIRModule;
class MIRParser;
class MIRLexer {
  friend MIRParser;

 public:
  explicit MIRLexer(MIRModule *mod);
  ~MIRLexer() {
    airFile = nullptr;
    if (airFileInternal.is_open()) {
      airFileInternal.close();
    }
  }

  void PrepareForFile(const char *filename);
  void PrepareForString(const std::string &src);
  TokenKind NextToken(void);
  TokenKind LexToken();
  TokenKind GetTokenKind() const {
    return kind;
  }

  uint32 GetLineNum() const {
    return lineNum;
  }

  int GetCurIdx() const {
    return curIdx;
  }

  // get the identifier name after the % or $ prefix
  const std::string &GetName() const {
    return name;
  }

  int64 GetTheIntVal() const {
    return theIntVal;
  }

  float GetTheFloatVal() const {
    return theFloatVal;
  }

  double GetTheDoubleVal() const {
    return theDoubleVal;
  }

  MapleVector<std::string> &GetSeenComments() {
    return seenComments;
  }

  std::string GetTokenString() const;  // for error reporting purpose
  void SetFile(std::ifstream *file) {
    airFile = file;
  }

  std::ifstream *GetFile() const {
    return airFile;
  }

 private:
  MIRModule *module;
  // for storing the different types of constant values
  int64 theIntVal;  // also indicates preg number under kTkPreg
  float theFloatVal;
  double theDoubleVal;
  MapleVector<std::string> seenComments;
  std::ifstream *airFile;
  std::ifstream airFileInternal;
  std::string line;
  size_t lineBufSize;  // the allocated size of line(buffer).
  uint32 currentLineSize;
  uint32 curIdx;
  uint32 lineNum;
  TokenKind kind;
  std::string name;  // store the name token without the % or $ prefix
  MapleUnorderedMap<std::string, TokenKind> keywordMap;

  void RemoveReturnInline(std::string &line) {
    if (line.back() == '\n') {
      line.pop_back();
    }
    if (line.back() == '\r') {
      line.pop_back();
    }
  }

  int ReadALine();  // read a line from MIR (text) file.
  void GenName();
  TokenKind GetConstVal();
  TokenKind GetSpecialFloatConst();
  TokenKind GetHexConst(uint32 valStart, bool negative);
  TokenKind GetIntConst(uint32 valStart, bool negative);
  TokenKind GetFloatConst(uint32 valStart, uint32 startIdx, bool negative);
  TokenKind GetSpecialTokenUsingOneCharacter(char c);
  TokenKind GetTokenWithPrefixDollar();
  TokenKind GetTokenWithPrefixPercent();
  TokenKind GetTokenWithPrefixAmpersand();
  TokenKind GetTokenWithPrefixAtOrCircumflex(char prefix);
  TokenKind GetTokenWithPrefixExclamation();
  TokenKind GetTokenWithPrefixQuotation();
  TokenKind GetTokenWithPrefixDoubleQuotation();
  TokenKind GetTokenSpecial();

  inline char GetCharAt(uint32 idx) const {
    return line[idx];
  }

  inline char GetCharAtWithUpperCheck(uint32 idx) const {
    return idx < currentLineSize ? line[idx] : 0;
  }

  inline char GetCharAtWithLowerCheck(uint32 idx) const {
    return idx >= 0 ? line[idx] : 0;
  }

  inline char GetCurrentCharWithUpperCheck() {
    return curIdx < currentLineSize ? line[curIdx] : 0;
  }

  inline char GetNextCurrentCharWithUpperCheck() {
    curIdx++;
    return curIdx < currentLineSize ? line[curIdx] : 0;
  }
};

inline bool IsPrimitiveType(TokenKind tk) {
  return tk >= TK_void && tk <= TK_agg;
}

inline bool IsVarName(TokenKind tk) {
  return tk == kTkLname || tk == kTkGname;
}

inline bool IsExprBinary(TokenKind tk) {
  return tk >= TK_add && tk <= TK_sub;
}

inline bool IsConstValue(TokenKind tk) {
  return tk >= kTkIntconst && tk <= kTkDoubleconst;
}

inline bool IsConstAddrExpr(TokenKind tk) {
  return tk == TK_addrof || tk == TK_addroffunc || tk == TK_conststr || tk == TK_conststr16;
}

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_LEXER_H
