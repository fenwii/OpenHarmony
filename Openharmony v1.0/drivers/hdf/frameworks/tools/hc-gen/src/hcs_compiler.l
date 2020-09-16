%option noyywrap
%option nodefault
%option yylineno
%option nounput
%option noinput
%x CMT

%{
/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 *    conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 *    of conditions and the following disclaimer in the documentation and/or other materials
 *    provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "hcs_parser.h"
#include "hcs_gen_parser.h"

#ifdef LEXER_DEBUG_ENABLE
#define LEXER_DEBUG(...) printf(__VA_ARGS__)
#else
#define LEXER_DEBUG(...)
#endif

extern void HcsCompilererror (char *s);
%}

%%
"/*"            {BEGIN(CMT);}
<CMT>"*/"   {BEGIN(INITIAL); }
<CMT>([^*]|\n)+|.
<CMT><<EOF>>    {LEXER_DEBUG("%d:unterminated coment\n",  HcsCompilerlineno); return 0;}
"//".*\n
"{"                 { LEXER_DEBUG("{\n"); return HcsCompilertext[0]; };
"}"                 { LEXER_DEBUG("}\n"); return HcsCompilertext[0]; };
":"                 { LEXER_DEBUG(":\n"); return HcsCompilertext[0]; };
"["                 { LEXER_DEBUG("[\n"); return HcsCompilertext[0]; };
"]"                 { LEXER_DEBUG("]\n"); return HcsCompilertext[0]; };
";"                 { LEXER_DEBUG(";\n"); return HcsCompilertext[0]; };
"&"                 { LEXER_DEBUG("REF\n"); return HcsCompilertext[0]; }
"="                 { LEXER_DEBUG("=\n"); return HcsCompilertext[0]; }
","                 { LEXER_DEBUG("=\n"); return HcsCompilertext[0]; }
"root"              { LEXER_DEBUG("root\n"); return ROOT; }
"true"              { HcsCompilerlval.i = 1; return NUMBER; }
"false"             { HcsCompilerlval.i = 0; return NUMBER; }
"#include"          { LEXER_DEBUG("INCLUDE\n"); return INCLUDE; }
"delete"            { return DELETE; }
"template"          { return TEMPLATE; }

0x[0-9A-Fa-f]+      { HcsCompilerlval.i = strtoll(HcsCompilertext, NULL, 16);
                      LEXER_DEBUG("NUMBER : %u\n", HcsCompilerlval.i);
                      return NUMBER;
                    }
0[0-9]+             { HcsCompilerlval.i = strtoll(HcsCompilertext, NULL, 8);
                      LEXER_DEBUG("NUMBER : %u\n", HcsCompilerlval.i);
                      return NUMBER;
                    }
[-+]?[0-9]+         { HcsCompilerlval.i = atoll(HcsCompilertext);
                      LEXER_DEBUG("NUMBER : %u\n", HcsCompilerlval.i);
                      return NUMBER;
                    }
0b[01]+             {
                      HcsCompilerlval.i = strtoll(HcsCompilertext + 2, NULL, 2);
                      LEXER_DEBUG("NUMBER : %u\n", HcsCompilerlval.i);
                      return NUMBER;
                    }
[a-zA-Z0-9_]+       { HcsCompilerlval.s = strdup(HcsCompilertext);
                      LEXER_DEBUG("STRING : %s \n", HcsCompilertext);
                      return LITERAL;
                    }
[a-zA-Z0-9_\.?]+    { HcsCompilerlval.s = strdup(HcsCompilertext);
                      LEXER_DEBUG("REF_PATH : %s \n", HcsCompilertext);
                      return REF_PATH;
                    }
\"[^\"\n]*\"        { LEXER_DEBUG("CONST_STRING : %s\n", HcsCompilertext);
                      char *constString = strdup(HcsCompilertext + 1);
                      constString[strlen(constString) - 1] = '\0';
                      HcsCompilerlval.s = constString;
                      return STRING;
                    }
\"[^\"\n]*$         { HcsCompilererror("Unterminated string"); }
"\n"
[ \t]               { } /* ignore */
[\r]                { } /* ignore */
.                   { HcsCompilererror("bad input character"); }

%%
extern FILE *HcsCompilerin;
void HcsSetCompilerIn(FILE *in)
{
    HcsCompilerin = in;
}
