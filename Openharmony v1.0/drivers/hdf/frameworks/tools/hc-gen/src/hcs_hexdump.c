/*
 * Copyright (c) 2013-2019, Huawei Technologies Co., Ltd. All rights reserved.
 * Copyright (c) 2020, Huawei Device Co., Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this list of
 * conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list
 * of conditions and the following disclaimer in the documentation and/or other materials
 * provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used
 * to endorse or promote products derived from this software without specific prior written
 * permission.
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
#include <hcs_file.h>
#include <hcs_log.h>
#include <hcs_option.h>

#define HCS_HEXDUMP_ENTRY_SYMBOL "hdfConfigEntrySymbol"
#define HCS_HEXDUMP_FILE_SUFFIX "_hex.c"
#define PRINT_SKIP_STEP 2
#define NUMS_PER_LINE 16

int32_t HcsHexdumpOutput(FILE *in, FILE *out)
{
    const char *prefix = HcsOptGetSymbolNamePrefix();
    if (prefix == NULL) {
        prefix = "";
    }
    if (fprintf(out, "static const unsigned char g_%s%s[] = {\n", prefix, HCS_HEXDUMP_ENTRY_SYMBOL) < 0) {
        return EOUTPUT;
    }
    uint32_t writeCount = 0;
    int32_t byte;
    while ((byte = getc(in)) != EOF) {
        if (fprintf(out, "%s0x%02x", (writeCount % NUMS_PER_LINE) ? ", " : &",\n    "[PRINT_SKIP_STEP * !writeCount],
            byte) < 0) {
            return EOUTPUT;
        }
        writeCount++;
    }
    if (fprintf(out, "\n};\n") < 0) {
        return EOUTPUT;
    }

    if (fprintf(out, "static const unsigned int g_%sLen = %u;\n", HCS_HEXDUMP_ENTRY_SYMBOL, writeCount) < 0) {
        return EOUTPUT;
    }
    if (fprintf(out,
        "void HdfGetBuildInConfigData(const unsigned char** data, unsigned int* size)\n"
        "{\n"
        "    *data = g_%s%s;\n"
        "    *size = g_%s%sLen;\n"
        "}",
        prefix, HCS_HEXDUMP_ENTRY_SYMBOL,  prefix, HCS_HEXDUMP_ENTRY_SYMBOL) < 0) {
        return EOUTPUT;
    }
    return NOERR;
}

int32_t HcsBinaryToHexdump(const char *inputFileName)
{
    struct HcsFile *source = NULL;
    if (HcsOpenSourceFile(inputFileName, &source, "rb")) {
        HCS_ERROR("can not open %s", inputFileName);
        return EINVALF;
    }

    struct HcsFile *out = HcsOpenOutputFile(HCS_HEXDUMP_FILE_SUFFIX);
    if (out == NULL) {
        HCS_ERROR("can not open %s", HcsGetOutPutFileName());
        return EINVALF;
    }

    int32_t ret = HcsHexdumpOutput(source->file, out->file);
    if (ret) {
        HCS_ERROR("fail to gen bytecode hexdump in C style");
    }
    HcsCloseFile(source);
    HcsCloseFile(out);
    return ret;
}
