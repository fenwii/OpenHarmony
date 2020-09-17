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

/* Avoid duplicate header files,not include securecutil.h */
#include "securecutil.h"


#if defined(ANDROID) && (SECUREC_HAVE_WCTOMB || SECUREC_HAVE_MBTOWC)
#include <wchar.h>
#if SECUREC_HAVE_WCTOMB
/*
 * Convert wide characters to narrow multi-bytes
 */
int wctomb(char *s, wchar_t wc)
{
    return wcrtomb(s, wc, NULL);
}
#endif

#if SECUREC_HAVE_MBTOWC
/*
 * Converting narrow multi-byte characters to wide characters
 */
int mbtowc(wchar_t *pwc, const char *s, size_t n)
{
    return mbrtowc(pwc, s, n, NULL);
}
#endif
#endif

/* high Num << 8 | num of SPC Ver */
#define SECUREC_C_VERSION     (0x5 << 8)
#define SECUREC_SPC_VERSION   7
#define SECUREC_VERSION_STR   "Huawei Secure C V100R001C01SPC007B002"

/* SPC verNumber<->verStr like:
 * 0X201<->C01
 * 0X202<->SPC001   Redefine numbers after this version
 * 0X502<->SPC002
 * 0X503<->SPC003
 * ...
 * 0X50a<->SPC010
 * 0X50b<->SPC011
 * ...
 */
/* CP  verNumber<->verStr like:
 * 0X601<->CP0001
 * 0X602<->CP0002
 * ...
 */
const char *GetHwSecureCVersion(unsigned short *verNumber)
{
    if (verNumber != NULL) {
        *verNumber = (unsigned short)(SECUREC_C_VERSION | SECUREC_SPC_VERSION);
    }
    return SECUREC_VERSION_STR;
}
#if SECUREC_IN_KERNEL
EXPORT_SYMBOL(GetHwSecureCVersion);
#endif

