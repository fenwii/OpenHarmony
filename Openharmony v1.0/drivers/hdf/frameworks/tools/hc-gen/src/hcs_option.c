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

#include <unistd.h>
#include "hcs_file.h"
#include "hcs_compiler.h"
#include "hcs_log.h"

#define ARG_COUNT_MIN 2
#define USAGE(option, info) HCS_PRINT("  %-12s%s\n", option, info)

bool g_genTextConfigOutput = false;
bool g_genByteCodeConfigOutput = true;
bool g_genByteCodeHexdump = false;
bool g_verbosePrint = false;
bool g_decompile = false;
bool g_shouldAlign = false;
const char *g_symbolPrefix = NULL;

bool HcsOptShouldAlign()
{
    return g_shouldAlign;
}

void HcsOptSetAlign(bool align)
{
    g_shouldAlign = align;
}


bool HcsOptShouldGenTextConfig()
{
    return g_genTextConfigOutput;
}
bool HcsOptShouldGenByteCodeConfig()
{
    return g_genByteCodeConfigOutput;
}
bool HcsOptDecompile()
{
    return g_decompile;
}

const char *HcsOptGetSymbolNamePrefix()
{
    return g_symbolPrefix;
}

bool HcsOptShouldGenHexdump()
{
    return g_genByteCodeHexdump;
}

void ShowUsage()
{
    HCS_PRINT("Usage: hc-gen [Options] [File]\n");
    HCS_PRINT("options:\n");
    USAGE("-o <file>", "output file name, default same as input");
    USAGE("-a", "hcb align with four bytes");
    USAGE("-b", "output binary output, default enable");
    USAGE("-t", "output config in C language source file style");
    USAGE("-i", "output binary hex dump in C language source file style");
    USAGE("-p <prefix>", "prefix of generated symbol name");
    USAGE("-d", "decompile hcb to hcs");
    USAGE("-V", "show verbose info");
    USAGE("-v", "show version");
    USAGE("-h", "show this help message");
}

#define HCS_SUPPORT_ARGS "o:ap:bditvVh"

void ShowVersionInfo()
{
    HCS_PRINT("Hcs compiler v%u.%u\n", HCS_COMPILER_VERSION_MAJOR, HCS_COMPILER_VERSION_MINOR);
    HCS_PRINT("Copyright (c) Huawei Technologies Co., Ltd. 2020\n");
}

static int32_t ProcessOption(int32_t argc, char *argv[])
{
    int32_t op = 0;
    while (op != HCS_OPTION_END) {
        op = getopt(argc, argv, HCS_SUPPORT_ARGS);
        switch (op) {
            case 'o':
                if (HcsSetOutPutName(optarg)) {
                    return EOPTION;
                }
                break;
            case 'a':
                g_shouldAlign = true;
                break;
            case 'b':
                g_genByteCodeConfigOutput = true;
                break;
            case 't':
                g_genTextConfigOutput = true;
                g_genByteCodeConfigOutput = false;
                break;
            case 'p':
                g_symbolPrefix = optarg;
                break;
            case 'i':
                g_genByteCodeHexdump = true;
                break;
            case 'V':
                g_verbosePrint = true;
                break;
            case 'd':
                g_decompile = true;
                break;
            case 'v':
                ShowVersionInfo();
                return EFAIL;
            case 'h': /* fall-through */
            case '?':
                ShowUsage();
                return EOPTION;
            default:
                break;
        }
    }

    return NOERR;
}

int32_t DoOption(int32_t argc, char *argv[])
{
    if (argc < ARG_COUNT_MIN) {
        ShowUsage();
        return EOPTION;
    }

    int32_t ret = ProcessOption(argc, argv);
    if (ret) {
        return ret;
    }

    if (optind >= argc) {
        HCS_ERROR("Miss input file name");
        return EOPTION;
    } else {
        const char *inputFIlePath = argv[optind];
        HCS_DEBUG("opt info:input file name:%s\n", inputFIlePath);
        HcsSetInputFileName(inputFIlePath);
    }
    return 0;
}

bool HcsVerbosePrint()
{
    return g_verbosePrint;
}