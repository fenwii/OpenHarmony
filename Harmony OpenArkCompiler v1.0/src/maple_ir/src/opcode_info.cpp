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
#include "opcode_info.h"
#include "mir_nodes.h"

namespace maple {
OpcodeTable::OpcodeTable() {
#define STR(s) #s
#define OPCODE(O, P, F, S)     \
  table[OP_##O].flag = F;      \
  table[OP_##O].name = STR(O); \
  table[OP_##O].instrucSize = S;
#include "opcodes.def"
#undef OPCODE
  table[OP_maydassign].name = "dassign";  // maydassign is printed dassign
}

const OpcodeTable kOpcodeInfo;
}  // namespace maple
