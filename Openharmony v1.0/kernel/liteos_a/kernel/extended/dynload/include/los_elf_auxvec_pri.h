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

#ifndef _LOS_ELF_AUXVEC_H
#define _LOS_ELF_AUXVEC_H

#define AUX_VECTOR_SIZE_ARCH                 1
#define AUX_VECTOR_SIZE_BASE                 20
#define AUX_VECTOR_SIZE                      ((AUX_VECTOR_SIZE_ARCH + AUX_VECTOR_SIZE_BASE + 1) << 1)

/* AUX VECTOR */
#define AUX_NULL             0
#define AUX_IGNORE           1
#define AUX_EXECFD           2
#define AUX_PHDR             3
#define AUX_PHENT            4
#define AUX_PHNUM            5
#define AUX_PAGESZ           6
#define AUX_BASE             7
#define AUX_FLAGS            8
#define AUX_ENTRY            9
#define AUX_NOTELF           10
#define AUX_UID              11
#define AUX_EUID             12
#define AUX_GID              13
#define AUX_EGID             14
#define AUX_PLATFORM         15
#define AUX_HWCAP            16
#define AUX_CLKTCK           17
#define AUX_SECURE           23
#define AUX_BASE_PLATFORM    24
#define AUX_RANDOM           25
#define AUX_HWCAP2           26
#define AUX_EXECFN           31
#define AUX_SYSINFO_EHDR     33

#define AUX_VEC_ENTRY(vecEnt, vecId, auxId, auxVal) do { \
    (vecEnt)[(vecId)++] = (auxId); \
    (vecEnt)[(vecId)++] = (auxVal); \
} while (0)

#endif /* _LOS_ELF_AUXVEC_H */
