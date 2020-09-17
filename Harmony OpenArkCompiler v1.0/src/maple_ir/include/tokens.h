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
#ifndef MAPLE_IR_INCLUDE_TOKENS_H
#define MAPLE_IR_INCLUDE_TOKENS_H

namespace maple {
enum TokenKind {
  kTkInvalid,
// keywords from this file
#define KEYWORD(STR) TK_##STR,
#include "keywords.def"
#undef KEYWORD
  // non-keywords starting here
  // constants
  kTkIntconst,
  kTkFloatconst,
  kTkDoubleconst,
  // local name
  kTkLname,
  // global name
  kTkGname,
  // function name
  kTkFname,
  // pseudo register
  kTkPreg,
  // special register
  kTkSpecialreg,
  // parent field
  kTkPrntfield,
  // type parameter name
  kTkTypeparam,
  // misc.
  kTkNewline,
  kTkLparen,     // (
  kTkRparen,     // )
  kTkLbrace,     // {
  kTkRbrace,     // }
  kTkLbrack,     // [
  kTkRbrack,     // ]
  kTkLangle,     // <
  kTkRangle,     // >
  kTkEqsign,     // =
  kTkComa,       // ,
  kTkDotdotdot,  // ...
  kTkColon,      // :
  kTkAsterisk,   // *
  kTkString,     // a literal string enclosed between "
  kTkEof
};

}  // namespace maple
#endif  // MAPLE_IR_INCLUDE_TOKENS_H
