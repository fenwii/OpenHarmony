/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "stdio.h"
#include <stdarg.h>
#include <securec.h>
#include "fcntl.h"
#include "unistd.h"
#include <log.h>

typedef int SecInt32;
typedef unsigned int SecUnsignedInt32;
typedef long long SecInt64;
typedef unsigned long long SecUnsignedInt64;

#define SECUREC_BUFFER_SIZE 256

#define SECUREC_MAX_PRECISION SECUREC_BUFFER_SIZE
/* max. # bytes in multibyte char  ,see MB_LEN_MAX */
#define SECUREC_MB_LEN 16

/* state definitions */
#define SECUREC_FLAG_SIGN 0x00001U
#define SECUREC_FLAG_SIGN_SPACE 0x00002U
#define SECUREC_FLAG_LEFT 0x00004U
#define SECUREC_FLAG_LEADZERO 0x00008U
#define SECUREC_FLAG_LONG 0x00010U
#define SECUREC_FLAG_SHORT 0x00020U
#define SECUREC_FLAG_SIGNED 0x00040U
#define SECUREC_FLAG_ALTERNATE 0x00080U
#define SECUREC_FLAG_NEGATIVE 0x00100U
#define SECUREC_FLAG_FORCE_OCTAL 0x00200U
#define SECUREC_FLAG_LONG_DOUBLE 0x00400U
#define SECUREC_FLAG_WIDECHAR 0x00800U
#define SECUREC_FLAG_LONGLONG 0x01000U
#define SECUREC_FLAG_CHAR 0x02000U
#define SECUREC_FLAG_POINTER 0x04000U
#define SECUREC_FLAG_I64 0x08000U
#define SECUREC_FLAG_PTRDIFF 0x10000U
#define SECUREC_FLAG_SIZE 0x20000U
#ifdef SECUREC_COMPATIBLE_LINUX_FORMAT
#define SECUREC_FLAG_INTMAX 0x40000U
#endif


typedef enum {
    STAT_NORMAL,
    STAT_PERCENT,
    STAT_FLAG,
    STAT_WIDTH,
    STAT_DOT,
    STAT_PRECIS,
    STAT_SIZE,
    STAT_TYPE,
    STAT_INVALID
} SecFmtState;

#define SECUREC_PRINTF_TRUNCATE (-2)
typedef struct {
    int count;
    char *cur;
} SecPrintfStream;
#define SECUREC_ERROR_INVALID_PARAMTER(msg) printf("%s invalid argument\n", msg)
#define SECUREC_ERROR_INVALID_RANGE(msg) printf("%s invalid dest buffer size\n", msg)
#define SECUREC_ERROR_BUFFER_OVERLAP(msg) printf("%s buffer overlap\n", msg)

// Log type
#define LOG_BUF_SIZE (1024)
#define MAX_DOMAIN_TAG_SIZE 64
#define IOV_SIZE (3)
#define HILOG_IOV_SIZE 4
#define HITRACE_BUF_SIZE 128
#define MAX_INIT_RETRIES (500)
#define DOMAIN_MIN 0x0D000000
#define DOMAIN_MAX 0x0E000000

#define SECUREC_FLOAT_BUFSIZE (309 + 40)     /* max float point value */
#define SECUREC_FLOAT_BUFSIZE_LB (4932 + 40) /* max long double value */

#define SECUREC_INT_MAX 2147483647

#define SECUREC_MUL10(x) ((((x) << 2) + (x)) << 1)
#define SECUREC_INT_MAX_DIV_TEN 21474836
#define SECUREC_MUL10_ADD_BEYOND_MAX(val) (((val) > SECUREC_INT_MAX_DIV_TEN))

#ifdef SECUREC_STACK_SIZE_LESS_THAN_1K
#define SECUREC_FMT_STR_LEN (8)
#else
#define SECUREC_FMT_STR_LEN (16)
#endif

#ifndef SECUREC_PUTC
#define SECUREC_PUTC(_c, _stream) ((--(_stream)->count >= 0) ? (*(_stream)->cur++ = (char)(_c)) : EOF)
#endif
/* to clear e835 */
#ifndef SECUREC_PUTC_ZERO
#define SECUREC_PUTC_ZERO(_stream) ((--(_stream)->count >= 0) ? ((*(_stream)->cur++ = (char)('\0'))) : EOF)
#endif

#ifndef SECUREC_MALLOC
#define SECUREC_MALLOC(x) malloc((size_t)(x))
#endif

#ifndef SECUREC_FREE
#define SECUREC_FREE(x) free((void *)(x))
#endif

typedef char SecChar;
#define SECUREC_CHAR(x) x
/* put a char to output */
#define SECUREC_PUTC(_c, _stream) ((--(_stream)->count >= 0) ? (*(_stream)->cur++ = (char)(_c)) : EOF)
/* to clear e835 */

#define SECUREC_PUTC_ZERO(_stream) ((--(_stream)->count >= 0) ? ((*(_stream)->cur++ = (char)('\0'))) : EOF)

int SecPutWcharStrEndingZero(SecPrintfStream *str, int zeroNum)
{
    int succeed = 0;
    int i;

    for (i = 0; i < zeroNum && (SECUREC_PUTC_ZERO(str) != EOF); ++i) {
    }
    if (i == zeroNum) {
        succeed = 1;
    }
    return succeed;
}

void SecWriteMultiChar(char ch, int num, SecPrintfStream *f, int *pnumwritten)
{
    int count = num;
    while (count-- > 0) {
        if (SECUREC_PUTC(ch, f) == EOF) {
            *pnumwritten = -1;
            break;
        } else {
            ++(*pnumwritten);
        }
    }
}

void SecWriteString(const char *string, int len, SecPrintfStream *f, int *pnumwritten)
{
    const char *str = string;
    int count = len;
    while (count-- > 0) {
        if (SECUREC_PUTC(*str, f) == EOF) {
            *pnumwritten = -1;
            break;
        } else {
            ++(*pnumwritten);
            ++str;
        }
    }
}

#define SECUREC_WRITE_MULTI_CHAR SecWriteMultiChar
#define SECUREC_WRITE_STRING SecWriteString

typedef struct {
    unsigned int flags;
    int fldWidth;
    int precision;
    int bufferIsWide; /* flag for buffer contains wide chars */
    int dynWidth;     /* %*   1 width from variable parameter ;0 not */
    int dynPrecision; /* %.*  1 precision from variable parameter ;0 not */
} SecFormatAttr;

typedef union {
    char *str; /* not a null terminated  string */
    wchar_t *wStr;
} SecFormatBuf;

typedef union {
    char str[SECUREC_BUFFER_SIZE + 1];
#ifdef SECUREC_FOR_WCHAR
    wchar_t wStr[SECUREC_BUFFER_SIZE + 1];
#endif
} SecBuffer;

#ifdef SECUREC_COMPATIBLE_LINUX_FORMAT
/* to clear e506 warning */
static int SecIsSameSize(size_t sizeA, size_t sizeB)
{
    return sizeA == sizeB;
}
#endif
#define SECUREC_WHILE_ZERO while (0)

#define SECUREC_SPECIAL(_val, Base) case Base:                                      \
        do {                                        \
            *--formatBuf.str = digits[_val % Base]; \
        } while ((_val /= Base) != 0)

#define SECUREC_SAFE_WRITE_PREFIX(src, txtLen, _stream, outChars) \
    do {                                                          \
        for (ii = 0; ii < txtLen; ++ii) {                         \
            *((SecChar *)(void *)(_stream->cur)) = *(src);        \
            _stream->cur += sizeof(SecChar);                      \
            ++(src);                                              \
        }                                                         \
        _stream->count -= txtLen * (int)(sizeof(SecChar));        \
        *(outChars) = *(outChars) + (txtLen);                     \
    }                                                             \
    SECUREC_WHILE_ZERO
#define MOBILE_NUMBER_LENGTH 12
#define SECUREC_SAFE_WRITE_STR(src, txtLen, _stream, outChars)                                    \
    do {                                                                                          \
        if (txtLen < MOBILE_NUMBER_LENGTH) {                                                      \
            for (ii = 0; ii < txtLen; ++ii) {                                                     \
                *((SecChar *)(void *)(_stream->cur)) = *(src);                                    \
                _stream->cur += sizeof(SecChar);                                                  \
                ++(src);                                                                          \
            }                                                                                     \
        } else {                                                                                  \
            (void)memcpy_s(_stream->cur, ((size_t)(unsigned int)txtLen * (sizeof(SecChar))), src, \
                ((size_t)(unsigned int)txtLen * (sizeof(SecChar))));                              \
            _stream->cur += (size_t)(unsigned int)txtLen * (sizeof(SecChar));                     \
        }                                                                                         \
        _stream->count -= txtLen * (int)(sizeof(SecChar));                                        \
        *(outChars) = *(outChars) + (txtLen);                                                     \
    }                                                                                             \
    SECUREC_WHILE_ZERO

#define SECUREC_SAFE_WRITE_CHAR(_ch, _stream, outChars) do {                                                     \
        *((SecChar *)(void *)(_stream->cur)) = (SecChar)_ch; \
        _stream->cur += sizeof(SecChar);                     \
        _stream->count -= (int)(sizeof(SecChar));            \
        *(outChars) = *(outChars) + 1;                       \
    }                                                        \
    SECUREC_WHILE_ZERO

#define SECUREC_SAFE_PADDING(padChar, padLen, _stream, outChars)     \
    do {                                                             \
        for (ii = 0; ii < padLen; ++ii) {                            \
            *((SecChar *)(void *)(_stream->cur)) = (SecChar)padChar; \
            _stream->cur += sizeof(SecChar);                         \
        }                                                            \
        _stream->count -= padLen * (int)(sizeof(SecChar));           \
        *(outChars) = *(outChars) + (padLen);                        \
    }                                                                \
    SECUREC_WHILE_ZERO

/* The count variable can be reduced to 0, and the external function complements the \0 terminator. */
#define SECUREC_IS_REST_BUF_ENOUGH(needLen) ((int)(stream->count - (int)needLen * (int)(sizeof(SecChar))) >= 0)

#define SECUREC_FMT_STATE_OFFSET 256
#ifdef SECUREC_FOR_WCHAR
#define SECUREC_FMT_TYPE(c, fmtTable) \
    ((((unsigned int)(int)(c)) <= (unsigned int)(int)SECUREC_CHAR('~')) ? (fmtTable[(unsigned char)(c)]) : 0)
#define SECUREC_DECODE_STATE(c, fmtTable, laststate)                                               \
    (SecFmtState)(((fmtTable[(SECUREC_FMT_TYPE(c, fmtTable)) * ((unsigned char)STAT_INVALID + 1) + \
        (unsigned char)(laststate) + SECUREC_FMT_STATE_OFFSET])))
#else
#define SECUREC_DECODE_STATE(c, fmtTable, laststate)                                             \
    (SecFmtState)((fmtTable[(fmtTable[(unsigned char)(c)]) * ((unsigned char)STAT_INVALID + 1) + \
        (unsigned char)(laststate) + SECUREC_FMT_STATE_OFFSET]))
#endif

static void SecDecodeFlags(SecChar ch, SecFormatAttr *attr)
{
    switch (ch) {
        case SECUREC_CHAR(' '):
            attr->flags |= SECUREC_FLAG_SIGN_SPACE;
            break;
        case SECUREC_CHAR('+'):
            attr->flags |= SECUREC_FLAG_SIGN;
            break;
        case SECUREC_CHAR('-'):
            attr->flags |= SECUREC_FLAG_LEFT;
            break;
        case SECUREC_CHAR('0'):
            attr->flags |= SECUREC_FLAG_LEADZERO; /* add zero th the front */
            break;
        case SECUREC_CHAR('#'):
            attr->flags |= SECUREC_FLAG_ALTERNATE; /* output %x with 0x */
            break;
        default:
            break;
    }
    return;
}

static int SecDecodeSize(SecChar ch, SecFormatAttr *attr, const SecChar **format)
{
    switch (ch) {
#ifdef SECUREC_COMPATIBLE_LINUX_FORMAT
        case SECUREC_CHAR('j'):
            attr->flags |= SECUREC_FLAG_INTMAX;
            break;
#endif
        case SECUREC_CHAR('q'): /* fall-through */ /* FALLTHRU */
        case SECUREC_CHAR('L'):
            attr->flags |= SECUREC_FLAG_LONGLONG | SECUREC_FLAG_LONG_DOUBLE;
            break;
        case SECUREC_CHAR('l'):
            if (**format == SECUREC_CHAR('l')) {
                ++(*format);
                attr->flags |= SECUREC_FLAG_LONGLONG; /* long long */
            } else {
                attr->flags |= SECUREC_FLAG_LONG; /* long int or wchar_t */
            }
            break;
        case SECUREC_CHAR('t'):
            attr->flags |= SECUREC_FLAG_PTRDIFF;
            break;
#ifdef SECUREC_COMPATIBLE_LINUX_FORMAT
        case SECUREC_CHAR('z'):
            attr->flags |= SECUREC_FLAG_SIZE;
            break;
        case SECUREC_CHAR('Z'):
            attr->flags |= SECUREC_FLAG_SIZE;
            break;
#endif

        case SECUREC_CHAR('I'):
#ifdef SECUREC_ON_64BITS
            attr->flags |= SECUREC_FLAG_I64; /* %I  to  INT64 */
#endif
            if ((**format == SECUREC_CHAR('6')) && (*((*format) + 1) == SECUREC_CHAR('4'))) {
                (*format) += 2;
                attr->flags |= SECUREC_FLAG_I64; /* %I64  to  INT64 */
            } else if ((**format == SECUREC_CHAR('3')) && (*((*format) + 1) == SECUREC_CHAR('2'))) {
                (*format) += 2;
                attr->flags &= ~SECUREC_FLAG_I64; /* %I64  to  INT32 */
            } else if ((**format == SECUREC_CHAR('d')) || (**format == SECUREC_CHAR('i')) ||
                (**format == SECUREC_CHAR('o')) || (**format == SECUREC_CHAR('u')) || (**format == SECUREC_CHAR('x')) ||
                (**format == SECUREC_CHAR('X'))) {
                /* do nothing */
            } else {
                /* Compatibility  code for "%I" just print I */
                return -1;
            }
            break;

        case SECUREC_CHAR('h'):
            if (**format == SECUREC_CHAR('h')) {
                attr->flags |= SECUREC_FLAG_CHAR; /* char */
            } else {
                attr->flags |= SECUREC_FLAG_SHORT; /* short int */
            }
            break;

        case SECUREC_CHAR('w'):
            attr->flags |= SECUREC_FLAG_WIDECHAR; /* wide char */
            break;
        default:
            break;
    }

    return 0;
}

static int SecDecodeTypeC(SecFormatAttr *attr, unsigned int cValue, SecFormatBuf *formatBuf, SecBuffer *buffer)
{
    int textLen;
    wchar_t wchar;

#if (defined(SECUREC_COMPATIBLE_LINUX_FORMAT)) && !(defined(__hpux)) && !(defined(SECUREC_ON_SOLARIS))
    attr->flags &= ~SECUREC_FLAG_LEADZERO;
#endif

#ifdef SECUREC_FOR_WCHAR
    attr->bufferIsWide = 1;
    wchar = (wchar_t)cValue;
    if (attr->flags & SECUREC_FLAG_SHORT) {
        /* multibyte character to wide  character */
        char tempchar[2];
        tempchar[0] = (char)(wchar & 0x00ff);
        tempchar[1] = '\0';

        if (mbtowc(buffer->wStr, tempchar, sizeof(tempchar)) < 0) {
            return -1;
        }
    } else {
        buffer->wStr[0] = wchar;
    }
    formatBuf->wStr = buffer->wStr;
    textLen = 1; /* only 1 wide character */
#else
    attr->bufferIsWide = 0;
    if (attr->flags & (SECUREC_FLAG_LONG | SECUREC_FLAG_WIDECHAR)) {
        wchar = (wchar_t)cValue;
        /* wide  character  to multibyte character */
        // SECUREC_MASK_MSVC_CRT_WARNING
        textLen = wctomb(buffer->str, wchar);
        // SECUREC_END_MASK_MSVC_CRT_WARNING
        if (textLen < 0) {
            return -1;
        }
    } else {
        /* get  multibyte character from argument */
        unsigned short temp;
        temp = (unsigned short)cValue;
        buffer->str[0] = (char)temp;
        textLen = 1;
    }
    formatBuf->str = buffer->str;
#endif

    return textLen;
}

static int SecDecodeTypeS(SecFormatAttr *attr, char *argPtr, SecFormatBuf *formatBuf)
{
    /* literal string to print null ptr, define it on stack rather than const text area
       is to avoid gcc warning with pointing const text with variable */
    static char strNullString[8] = "(null)";
    static wchar_t wStrNullString[8] = { L'(', L'n', L'u', L'l', L'l', L')', L'\0', L'\0' };

    int finalPrecision;
    char *strEnd = NULL;
    wchar_t *wStrEnd = NULL;
    int textLen;

#if (defined(SECUREC_COMPATIBLE_LINUX_FORMAT)) && (!defined(SECUREC_ON_UNIX))
    attr->flags &= ~SECUREC_FLAG_LEADZERO;
#endif
    finalPrecision = (attr->precision == -1) ? SECUREC_INT_MAX : attr->precision;
    formatBuf->str = argPtr;

#ifdef SECUREC_FOR_WCHAR
#if defined(SECUREC_COMPATIBLE_LINUX_FORMAT)
    if (!(attr->flags & SECUREC_FLAG_LONG)) {
        attr->flags |= SECUREC_FLAG_SHORT;
    }
#endif
    if (attr->flags & SECUREC_FLAG_SHORT) {
        if (formatBuf->str == NULL) { /* NULL passed, use special string */
            formatBuf->str = strNullString;
        }
        strEnd = formatBuf->str;
        for (textLen = 0; textLen < finalPrecision && *strEnd; textLen++) {
            ++strEnd;
        }
        /* textLen now contains length in multibyte chars */
    } else {
        if (formatBuf->wStr == NULL) { /* NULL passed, use special string */
            formatBuf->wStr = wStrNullString;
        }
        attr->bufferIsWide = 1;
        wStrEnd = formatBuf->wStr;
        while (finalPrecision-- && *wStrEnd) {
            ++wStrEnd;
        }
        textLen = (int)(wStrEnd - formatBuf->wStr); /* in wchar_ts */
        /* textLen now contains length in wide chars */
    }
#else /* SECUREC_FOR_WCHAR */
    if (attr->flags & (SECUREC_FLAG_LONG | SECUREC_FLAG_WIDECHAR)) {
        if (formatBuf->wStr == NULL) { /* NULL passed, use special string */
            formatBuf->wStr = wStrNullString;
        }
        attr->bufferIsWide = 1;
        wStrEnd = formatBuf->wStr;
        while (finalPrecision-- && *wStrEnd) {
            ++wStrEnd;
        }
        textLen = (int)(wStrEnd - formatBuf->wStr);
    } else {
        if (formatBuf->str == NULL) { /* meet NULL, use special string */
            formatBuf->str = strNullString;
        }

        if (finalPrecision == SECUREC_INT_MAX) {
            /* precision NOT assigned */
            /* The strlen performance is high when the string length is greater than 32 */
            textLen = (int)strlen(formatBuf->str);
        } else {
            /* precision assigned */
            strEnd = formatBuf->str;
            while (finalPrecision-- && *strEnd) {
                ++strEnd;
            }
            textLen = (int)(strEnd - formatBuf->str); /* length of the string */
        }
    }

#endif /* SECUREC_FOR_WCHAR */
    return textLen;
}

#define PUBLIC_FLAG_LEN (8)
#define PRIVATE_FLAG_LEN (9)
#define PUBLIC_FLAG "{public}"
#define PRIVATE_FLAG "{private}"
#define bool _Bool
static int g_hilogTrue = 1;
static int g_hilogFalse = 0;

int HiLogSecOutputS(SecPrintfStream *stream, bool isDebugMode, const char *cformat, va_list arglist)
{
    const SecChar *format = cformat;

    char *floatBuf = NULL;
    SecFormatBuf formatBuf;
    static const char *itoaUpperDigits = "0123456789ABCDEFX";
    static const char *itoaLowerDigits = "0123456789abcdefx";
    const char *digits = itoaUpperDigits;
    int ii;

    unsigned int radix;
    int charsOut; /* characters written */

    int prefixLen = 0;
    int padding;

    int textLen;        /* length of the text */
    int bufferSize; /* size of formatBuf.str */
    int noOutput = 0;

    SecFmtState state;
    SecFmtState laststate;

    SecChar prefix[2] = { 0 };
    SecChar ch; /* currently read character */
    static char PRIVACY_STRING[] = "<private>";
    static wchar_t WPRIVACY_STRING[] = { L'<', L'p', L'r', L'i', L'v', L'a', L't', L'e', L'>', L'\0'};
    bool isPrivacy = g_hilogTrue;

    static const unsigned char fmtCharTable[337] = {
        /* type 0:    nospecial meanin;
           1:   '%';
           2:    '.'
           3:    '*'
           4:    '0'
           5:    '1' ... '9'
           6:    ' ', '+', '-', '#'
           7:     'h', 'l', 'L', 'F', 'w' , 'N','z','q','t','j'
           8:     'd','o','u','i','x','X','e','f','g'
         */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x06, 0x00, 0x00, 0x06, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x06, 0x00, 0x06, 0x02, 0x00,
        0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x08, 0x08, 0x00, 0x07, 0x00, 0x00, 0x07, 0x00, 0x07, 0x00,
        0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x07, 0x08, 0x07, 0x00, 0x07, 0x00, 0x00, 0x08,
        0x08, 0x07, 0x00, 0x08, 0x07, 0x08, 0x00, 0x07, 0x08, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00,
        /* fill zero  for normal char 128 byte for 0x80 - 0xff */
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        /* state  0: normal
           1: percent
           2: flag
           3: width
           4: dot
           5: precis
           6: size
           7: type
           8: invalid
         */
        0x00, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x01, 0x00, 0x08, 0x08, 0x08, 0x08, 0x08,
        0x01, 0x00, 0x00, 0x04, 0x04, 0x04, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x03, 0x03, 0x08, 0x05,
        0x08, 0x08, 0x00, 0x00, 0x00, 0x02, 0x02, 0x03, 0x05, 0x05, 0x08, 0x00, 0x00, 0x00, 0x03, 0x03,
        0x03, 0x05, 0x05, 0x08, 0x00, 0x00, 0x00, 0x02, 0x02, 0x02, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00,
        0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x00,
        0x00
    };

    SecFormatAttr formatAttr;
    SecBuffer buffer;
    formatAttr.flags = 0;
    formatAttr.bufferIsWide = 0; /* flag for buffer contains wide chars */
    formatAttr.fldWidth = 0;
    formatAttr.precision = 0;
    formatAttr.dynWidth = 0;
    formatAttr.dynPrecision = 0;

    charsOut = 0;
    textLen = 0;
    state = STAT_NORMAL; /* starting state */
    formatBuf.str = NULL;

    /* loop each format character */
    /* remove format != NULL */
    while ((ch = *format++) != SECUREC_CHAR('\0') && charsOut >= 0) {
        laststate = state;
        state = SECUREC_DECODE_STATE(ch, fmtCharTable, laststate);

        switch (state) {
            case STAT_NORMAL:

            NORMAL_CHAR:

                /* normal state, write character */
                if (SECUREC_IS_REST_BUF_ENOUGH(1 /* only one char */)) {
                    SECUREC_SAFE_WRITE_CHAR(ch, stream, &charsOut); /* char * cast to wchar * */
                } else {
#ifdef SECUREC_FOR_WCHAR
                    SECUREC_WRITE_CHAR(ch, stream, &charsOut);
#else
                    /* optimize function call to code */
                    charsOut = -1;
                    stream->count = -1;
#endif
                }

                continue;

            case STAT_PERCENT:
                /* set default values */
                prefixLen = 0;
                noOutput = 0;
                formatAttr.flags = 0;
                formatAttr.fldWidth = 0;
                formatAttr.precision = -1;
                formatAttr.bufferIsWide = 0;
                isPrivacy = g_hilogTrue;
                if (0 == strncmp(format, PUBLIC_FLAG, PUBLIC_FLAG_LEN)) {
                    isPrivacy = g_hilogFalse;
                    format += PUBLIC_FLAG_LEN;
                    break;
                }
                if (0 == strncmp(format, PRIVATE_FLAG, PRIVATE_FLAG_LEN)) {
                    isPrivacy = g_hilogTrue;
                    format += PRIVATE_FLAG_LEN;
                    break;
                }

                if (*format == SECUREC_CHAR('%')) {
                    isPrivacy = g_hilogFalse;
                }

                break;

            case STAT_FLAG:
                /* set flag based on which flag character */
                SecDecodeFlags(ch, &formatAttr);
                break;

            case STAT_WIDTH:
                /* update width value */
                if (ch == SECUREC_CHAR('*')) {
                    /* get width */
                    formatAttr.fldWidth = (int)va_arg(arglist, int);
                    if (formatAttr.fldWidth < 0) {
                        formatAttr.flags |= SECUREC_FLAG_LEFT;
                        formatAttr.fldWidth = -formatAttr.fldWidth;
                    }
                    formatAttr.dynWidth = 1;
                } else {
                    if (laststate != STAT_WIDTH) {
                        formatAttr.fldWidth = 0;
                    }
                    if (SECUREC_MUL10_ADD_BEYOND_MAX(formatAttr.fldWidth)) {
                        return -1;
                    }
                    formatAttr.fldWidth =
                        (int)SECUREC_MUL10((unsigned int)formatAttr.fldWidth) + (ch - SECUREC_CHAR('0'));
                    formatAttr.dynWidth = 0;
                }
                break;

            case STAT_DOT:
                formatAttr.precision = 0;
                break;

            case STAT_PRECIS:
                /* update precison value */
                if (ch == SECUREC_CHAR('*')) {
                    /* get precision from arg list */
                    formatAttr.precision = (int)va_arg(arglist, int);
                    if (formatAttr.precision < 0) {
                        formatAttr.precision = -1;
                    }
                    formatAttr.dynPrecision = 1;
                } else {
                    /* add digit to current precision */
                    if (SECUREC_MUL10_ADD_BEYOND_MAX(formatAttr.precision)) {
                        return -1;
                    }
                    formatAttr.precision =
                        (int)SECUREC_MUL10((unsigned int)formatAttr.precision) + (ch - SECUREC_CHAR('0'));
                    formatAttr.dynPrecision = 0;
                }
                break;

            case STAT_SIZE:
                /* read a size specifier, set the formatAttr.flags based on it */
                if (SecDecodeSize(ch, &formatAttr, &format) != 0) {
                    /* Compatibility  code for "%I" just print I */
                    state = STAT_NORMAL;
                    goto NORMAL_CHAR;
                }
                break;

            case STAT_TYPE:

                switch (ch) {
                    case SECUREC_CHAR('C'):
                        /* wide char */
                        if (!(formatAttr.flags & (SECUREC_FLAG_SHORT | SECUREC_FLAG_LONG | SECUREC_FLAG_WIDECHAR))) {
#ifdef SECUREC_FOR_WCHAR
                            formatAttr.flags |= SECUREC_FLAG_SHORT;
#else
                            formatAttr.flags |= SECUREC_FLAG_WIDECHAR;
#endif
                        }
                        /* fall-through */
                        /* FALLTHRU */
                    case SECUREC_CHAR('c'): {
                        unsigned int cValue = (unsigned int)va_arg(arglist, int);
                        textLen = SecDecodeTypeC(&formatAttr, cValue, &formatBuf, &buffer);
                        if (textLen < 0) {
                            noOutput = 1;
                        }
                    } break;
                    case SECUREC_CHAR('S'): /* wide char string */
#ifndef SECUREC_FOR_WCHAR
                        if (!(formatAttr.flags & (SECUREC_FLAG_SHORT | SECUREC_FLAG_LONG | SECUREC_FLAG_WIDECHAR))) {
                            formatAttr.flags |= SECUREC_FLAG_WIDECHAR;
                        }
#else
                        if (!(formatAttr.flags & (SECUREC_FLAG_SHORT | SECUREC_FLAG_LONG | SECUREC_FLAG_WIDECHAR))) {
                            formatAttr.flags |= SECUREC_FLAG_SHORT;
                        }
#endif
                        /* fall-through */
                        /* FALLTHRU */
                    case SECUREC_CHAR('s'): {
                        char *argPtr = (char *)va_arg(arglist, char *);
                        textLen = SecDecodeTypeS(&formatAttr, argPtr, &formatBuf);
                    } break;

                    case SECUREC_CHAR('n'):
                        /* higher risk disable it */
                        return -1;

                    case SECUREC_CHAR('E'): /* fall-through */ /* FALLTHRU */
                    case SECUREC_CHAR('F'): /* fall-through */ /* FALLTHRU */
                    case SECUREC_CHAR('G'): /* fall-through */ /* FALLTHRU */
                    case SECUREC_CHAR('A'): /* fall-through */ /* FALLTHRU */
                        /* convert format char to lower , use Explicit conversion to clean up compilation warning */
                        ch = (SecChar)(ch + ((SecChar)(SECUREC_CHAR('a')) - (SECUREC_CHAR('A'))));
                        /* fall-through */
                        /* FALLTHRU */
                    case SECUREC_CHAR('e'): /* fall-through */ /* FALLTHRU */
                    case SECUREC_CHAR('f'): /* fall-through */ /* FALLTHRU */
                    case SECUREC_CHAR('g'): /* fall-through */ /* FALLTHRU */
                    case SECUREC_CHAR('a'): {
                        /* floating point conversion */
                        formatBuf.str = buffer.str; /* output buffer for float string with default size */

                        /* compute the precision value */
                        if (formatAttr.precision < 0) {
                            formatAttr.precision = 6;
                        } else if (formatAttr.precision == 0 && ch == SECUREC_CHAR('g')) {
                            formatAttr.precision = 1;
                        }

                        /* calc buffer size to store long double value */
                        if (formatAttr.flags & SECUREC_FLAG_LONG_DOUBLE) {
                            if (formatAttr.precision > (SECUREC_INT_MAX - SECUREC_FLOAT_BUFSIZE_LB)) {
                                noOutput = 1;
                                break;
                            }
                            bufferSize = SECUREC_FLOAT_BUFSIZE_LB + formatAttr.precision;
                        } else {
                            if (formatAttr.precision > (SECUREC_INT_MAX - SECUREC_FLOAT_BUFSIZE)) {
                                noOutput = 1;
                                break;
                            }
                            bufferSize = SECUREC_FLOAT_BUFSIZE + formatAttr.precision;
                        }
                        if (formatAttr.fldWidth > bufferSize) {
                            bufferSize = formatAttr.fldWidth;
                        }

                        if (bufferSize >= SECUREC_BUFFER_SIZE) {
                            /* the current vlaue of SECUREC_BUFFER_SIZE could NOT store the formatted float string */
                            /* size include '+' and '\0' */
                            floatBuf = (char *)SECUREC_MALLOC(((size_t)(unsigned int)bufferSize + (size_t)2));
                            if (floatBuf != NULL) {
                                formatBuf.str = floatBuf;
                            } else {
                                noOutput = 1;
                                break;
                            }
                        }

                        {
                            /* add following code to call system sprintf API for float number */
                            const SecChar *pFltFmt = format - 2; /* point to the position before 'f' or 'g' */
                            int k = 0;
                            int fltFmtStrLen;
                            char fltFmtBuf[SECUREC_FMT_STR_LEN];
                            char *fltFmtStr = fltFmtBuf;
                            char *fltFmtHeap = NULL; /* to clear warning */

                            while (SECUREC_CHAR('%') != *pFltFmt && SECUREC_CHAR('}') != *pFltFmt) { /* must meet '%' */
                                --pFltFmt;
                            }

                            fltFmtStrLen = (int)((format - pFltFmt) + 1); /* with ending terminator */
                            if (fltFmtStrLen > SECUREC_FMT_STR_LEN) {
                                /* if SECUREC_FMT_STR_LEN is NOT enough, alloc a new buffer */
                                fltFmtHeap = (char *)SECUREC_MALLOC((size_t)((unsigned int)fltFmtStrLen));
                                if (fltFmtHeap == NULL) {
                                    noOutput = 1;
                                    break;
                                } else {
                                    if (SECUREC_CHAR('%') != *pFltFmt) {
                                        fltFmtHeap[0] = '%';
                                        ++k;
                                    }
                                    for (; k < fltFmtStrLen - 1; ++k) {
                                        /* convert wchar to char */
                                        fltFmtHeap[k] = (char)(pFltFmt[k]); /* copy the format string */
                                    }
                                    fltFmtHeap[k] = '\0';

                                    fltFmtStr = fltFmtHeap;
                                }
                            } else {
                                if (SECUREC_CHAR('%') != *pFltFmt) {
                                    fltFmtBuf[0] = '%';
                                    ++k;
                                }
                                /* purpose of the repeat code is to solve the tool alarm  Redundant_Null_Check */
                                for (; k < fltFmtStrLen - 1; ++k) {
                                    /* convert wchar to char */
                                    fltFmtBuf[k] = (char)(pFltFmt[k]); /* copy the format string */
                                }
                                fltFmtBuf[k] = '\0';
                            }

#ifdef SECUREC_COMPATIBLE_LINUX_FORMAT
                            if (formatAttr.flags & SECUREC_FLAG_LONG_DOUBLE) {
                                long double tmp = (long double)va_arg(arglist, long double);
                                /* call system sprintf to format float value */
                                if (formatAttr.dynWidth && formatAttr.dynPrecision) {
                                    textLen = sprintf_s(formatBuf.str, SECUREC_BUFFER_SIZE + 1, (char *)fltFmtStr,
                                        formatAttr.fldWidth, formatAttr.precision, tmp);
                                } else if (formatAttr.dynWidth) {
                                    textLen = sprintf_s(formatBuf.str, SECUREC_BUFFER_SIZE + 1, (char *)fltFmtStr,
                                        formatAttr.fldWidth, tmp);
                                } else if (formatAttr.dynPrecision) {
                                    textLen = sprintf_s(formatBuf.str, SECUREC_BUFFER_SIZE + 1, (char *)fltFmtStr,
                                        formatAttr.precision, tmp);
                                } else {
                                    textLen = sprintf_s(formatBuf.str, SECUREC_BUFFER_SIZE + 1, (char *)fltFmtStr, tmp);
                                }
                            } else
#endif
                            {
                                double tmp = (double)va_arg(arglist, double);
                                if (formatAttr.dynWidth && formatAttr.dynPrecision) {
                                    textLen = sprintf_s(formatBuf.str, SECUREC_BUFFER_SIZE + 1, (char *)fltFmtStr,
                                        formatAttr.fldWidth, formatAttr.precision, tmp);
                                } else if (formatAttr.dynWidth) {
                                    textLen = sprintf_s(formatBuf.str, SECUREC_BUFFER_SIZE + 1, (char *)fltFmtStr,
                                        formatAttr.fldWidth, tmp);
                                } else if (formatAttr.dynPrecision) {
                                    textLen = sprintf_s(formatBuf.str, SECUREC_BUFFER_SIZE + 1, (char *)fltFmtStr,
                                        formatAttr.precision, tmp);
                                } else {
                                    textLen = sprintf_s(formatBuf.str, SECUREC_BUFFER_SIZE + 1, (char *)fltFmtStr, tmp);
                                }
                            }

                            if (fltFmtHeap != NULL) {
                                /* if buffer is alloced on heap, free it */
                                SECUREC_FREE(fltFmtHeap);
                                fltFmtHeap = NULL;
                                /* to clear e438 last value assigned not used , the compiler will optimize this code */
                                (void)fltFmtHeap;
                            }
                            if (textLen < 0) {
                                /* bufferSize is large enough,just validation the return value */
                                noOutput = 1;
                                break;
                            }

                            formatAttr.fldWidth =
                                textLen;          /* no padding ,this variable to calculate amount of padding */
                            prefixLen = 0;        /* no padding ,this variable to  calculate amount of padding */
                            formatAttr.flags = 0; /* clear all internal formatAttr.flags */
                            break;
                        }
                    }

                    case SECUREC_CHAR('p'):
                        /* print a pointer */
#if defined(SECUREC_COMPATIBLE_WIN_FORMAT)
                        formatAttr.flags &= ~SECUREC_FLAG_LEADZERO;
#else
                        formatAttr.flags |= SECUREC_FLAG_POINTER;
#endif

#ifdef SECUREC_ON_64BITS
                        formatAttr.flags |= SECUREC_FLAG_I64; /* converting an int64 */
#else
                        formatAttr.flags |= SECUREC_FLAG_LONG; /* converting a long */
#endif

#if (defined(SECUREC_COMPATIBLE_LINUX_FORMAT) || defined(SECUREC_VXWORKS_PLATFORM)) && (!defined(SECUREC_ON_UNIX))

#if defined(SECUREC_VXWORKS_PLATFORM)
                        formatAttr.precision = 1;
#else
                        formatAttr.precision = 0;
#endif
                        formatAttr.flags |= SECUREC_FLAG_ALTERNATE; /* "0x" is not default prefix in UNIX */
                        digits = itoaLowerDigits;
                        goto OUTPUT_HEX;
#else
                                                               /* not linux vxwoks */
#if defined(_AIX) || defined(SECUREC_ON_SOLARIS)
                        formatAttr.precision = 1;
#else
                        formatAttr.precision = 2 * sizeof(void *);
#endif

#endif

#if defined(SECUREC_ON_UNIX)
                        digits = itoaLowerDigits;
                        goto OUTPUT_HEX;
#endif

                        /* fall-through */
                        /* FALLTHRU */
                    case SECUREC_CHAR('X'):
                        /* unsigned upper hex output */
                        digits = itoaUpperDigits;
                        goto OUTPUT_HEX;

                    case SECUREC_CHAR('x'):
                        /* unsigned lower hex output */
                        digits = itoaLowerDigits;

                    OUTPUT_HEX:
                        radix = 16;
                        if (formatAttr.flags & SECUREC_FLAG_ALTERNATE) {
                            /* alternate form means '0x' prefix */
                            prefix[0] = SECUREC_CHAR('0');
                            prefix[1] = (SecChar)(digits[16]); /* 'x' or 'X' */

#if (defined(SECUREC_COMPATIBLE_LINUX_FORMAT) || defined(SECUREC_VXWORKS_PLATFORM))
                            if (ch == 'p') {
                                prefix[1] = SECUREC_CHAR('x');
                            }
#endif
#if defined(_AIX) || defined(SECUREC_ON_SOLARIS)
                            if (ch == 'p') {
                                prefixLen = 0;
                            } else {
                                prefixLen = 2;
                            }
#else
                            prefixLen = 2;
#endif
                        }
                        goto OUTPUT_INT;
                    case SECUREC_CHAR('i'): /* fall-through */ /* FALLTHRU */
                    case SECUREC_CHAR('d'): /* fall-through */ /* FALLTHRU */
                        /* signed decimal output */
                        formatAttr.flags |= SECUREC_FLAG_SIGNED;
                        /* fall-through */
                        /* FALLTHRU */
                    case SECUREC_CHAR('u'):
                        radix = 10;
                        goto OUTPUT_INT;
                    case SECUREC_CHAR('o'):
                        /* unsigned octal output */
                        radix = 8;
                        if (formatAttr.flags & SECUREC_FLAG_ALTERNATE) {
                            /* alternate form means force a leading 0 */
                            formatAttr.flags |= SECUREC_FLAG_FORCE_OCTAL;
                        }
                    OUTPUT_INT : {
                        SecUnsignedInt64 number; /* number to convert */
                        SecInt64 l;                  /* temp long value */
                        unsigned char tch;
#if defined(SECUREC_VXWORKS_VERSION_5_4) && !defined(SECUREC_ON_64BITS)
                        SecUnsignedInt32 digit = 0; /* ascii value of digit */
                        SecUnsignedInt32 quotientHigh = 0;
                        SecUnsignedInt32 quotientLow = 0;
#endif

                        /* read argument into variable l */
                        if (formatAttr.flags & SECUREC_FLAG_I64) {
                            l = (SecInt64)va_arg(arglist, SecInt64);
                        } else if (formatAttr.flags & SECUREC_FLAG_LONGLONG) {
                            l = (SecInt64)va_arg(arglist, SecInt64);
                        } else
#ifdef SECUREC_ON_64BITS
                            if (formatAttr.flags & SECUREC_FLAG_LONG) {
                            l = (long)va_arg(arglist, long);
                        } else
#endif /* SECUREC_ON_64BITS */
                            if (formatAttr.flags & SECUREC_FLAG_CHAR) {
                            if (formatAttr.flags & SECUREC_FLAG_SIGNED) {
                                l = (char)va_arg(arglist, int); /* sign extend */
                                if (l >= 128) {                 /* on some platform, char is always unsigned */
                                    SecUnsignedInt64 tmpL = (SecUnsignedInt64)l;
                                    formatAttr.flags |= SECUREC_FLAG_NEGATIVE;
                                    tch = (unsigned char)(~(tmpL));
                                    l = tch + 1;
                                }
                            } else {
                                l = (unsigned char)va_arg(arglist, int); /* zero-extend */
                            }
                        } else if (formatAttr.flags & SECUREC_FLAG_SHORT) {
                            if (formatAttr.flags & SECUREC_FLAG_SIGNED) {
                                l = (short)va_arg(arglist, int); /* sign extend */
                            } else {
                                l = (unsigned short)va_arg(arglist, int); /* zero-extend */
                            }
                        }
#ifdef SECUREC_COMPATIBLE_LINUX_FORMAT
                        else if (formatAttr.flags & SECUREC_FLAG_PTRDIFF) {
                            l = (ptrdiff_t)va_arg(arglist, ptrdiff_t); /* sign extend */
                        } else if (formatAttr.flags & SECUREC_FLAG_SIZE) {
                            if (formatAttr.flags & SECUREC_FLAG_SIGNED) {
                                /* No suitable macros were found to handle the branch */
                                if (SecIsSameSize(sizeof(size_t), sizeof(long))) {
                                    l = va_arg(arglist, long); /* sign extend */
                                } else if (SecIsSameSize(sizeof(size_t), sizeof(long long))) {
                                    l = va_arg(arglist, long long); /* sign extend */
                                } else {
                                    l = va_arg(arglist, int); /* sign extend */
                                }
                            } else {
                                l = (SecInt64)(size_t)va_arg(arglist, size_t); /* sign extend */
                            }
                        } else if (formatAttr.flags & SECUREC_FLAG_INTMAX) {
                            if (formatAttr.flags & SECUREC_FLAG_SIGNED) {
                                l = va_arg(arglist, SecInt64); /* sign extend */
                            } else {
                                l = (SecInt64)(SecUnsignedInt64)va_arg(arglist, SecUnsignedInt64); /* sign extend */
                            }
                        }
#endif
                        else {
                            if (formatAttr.flags & SECUREC_FLAG_SIGNED) {
                                l = va_arg(arglist, int); /* sign extend */
                            } else {
                                l = (unsigned int)va_arg(arglist, int); /* zero-extend */
                            }
                        }

                        /* check for negative; copy into number */
                        if ((formatAttr.flags & SECUREC_FLAG_SIGNED) && l < 0) {
                            number = (SecUnsignedInt64)(-l);
                            formatAttr.flags |= SECUREC_FLAG_NEGATIVE;
                        } else {
                            number = (SecUnsignedInt64)l;
                        }

                        if (((formatAttr.flags & SECUREC_FLAG_I64) == 0) &&
#ifdef SECUREC_COMPATIBLE_LINUX_FORMAT
                            ((formatAttr.flags & SECUREC_FLAG_INTMAX) == 0) &&
#endif
#ifdef SECUREC_ON_64BITS
                            ((formatAttr.flags & SECUREC_FLAG_PTRDIFF) == 0) &&
                            ((formatAttr.flags & SECUREC_FLAG_SIZE) == 0) &&
#if !defined(SECUREC_COMPATIBLE_WIN_FORMAT) /* on window 64 system sizeof long is 32bit */
                            ((formatAttr.flags & SECUREC_FLAG_LONG) == 0) &&
#endif
#endif
                            ((formatAttr.flags & SECUREC_FLAG_LONGLONG) == 0)) {

                            number &= 0xffffffff;
                        }

                        /* check precision value for default */
                        if (formatAttr.precision < 0) {
                            formatAttr.precision = 1; /* default precision */
                        } else {
#if defined(SECUREC_COMPATIBLE_WIN_FORMAT)
                            formatAttr.flags &= ~SECUREC_FLAG_LEADZERO;
#else
                            if (!(formatAttr.flags & SECUREC_FLAG_POINTER)) {
                                formatAttr.flags &= ~SECUREC_FLAG_LEADZERO;
                            }
#endif
                            if (formatAttr.precision > SECUREC_MAX_PRECISION) {
                                formatAttr.precision = SECUREC_MAX_PRECISION;
                            }
                        }

                        /* Check if data is 0; if so, turn off hex prefix,if 'p',add 0x prefix,else not add prefix */
                        if (number == 0) {
#if !(defined(SECUREC_VXWORKS_PLATFORM) || defined(__hpux))
                            prefixLen = 0;
#else
                            if ((ch == 'p') && (formatAttr.flags & SECUREC_FLAG_ALTERNATE))
                                prefixLen = 2;
                            else
                                prefixLen = 0;
#endif
                        }

                        /* Convert data to ASCII */
                        formatBuf.str = &buffer.str[SECUREC_BUFFER_SIZE];

                        if (number > 0) {
#ifdef SECUREC_ON_64BITS
                            switch (radix) {
                                /* the compiler will optimize each one */
                                SECUREC_SPECIAL(number, 10);
                                break;
                                SECUREC_SPECIAL(number, 16);
                                break;
                                SECUREC_SPECIAL(number, 8);
                                break;
                                default:
                                    break;
                            }
#else /* for 32 bits system */
                            if (number <= 0xFFFFFFFFUL) {
                                /* in most case, the value to be converted is small value */
                                SecUnsignedInt32 n32Tmp = (SecUnsignedInt32)number;
                                switch (radix) {
                                    SECUREC_SPECIAL(n32Tmp, 16);
                                    break;
                                    SECUREC_SPECIAL(n32Tmp, 8);
                                    break;

#ifdef _AIX
                                    /* the compiler will optimize div 10 */
                                    SECUREC_SPECIAL(n32Tmp, 10);
                                    break;
#else
                                    case 10: {
                                        /* fast div 10 */
                                        SecUnsignedInt32 q;
                                        SecUnsignedInt32 r;
                                        do {
                                            *--formatBuf.str = digits[n32Tmp % 10];
                                            q = (n32Tmp >> 1) + (n32Tmp >> 2);
                                            q = q + (q >> 4);
                                            q = q + (q >> 8);
                                            q = q + (q >> 16);
                                            q = q >> 3;
                                            r = n32Tmp - (((q << 2) + q) << 1);
                                            n32Tmp = (r > 9) ? (q + 1) : q;
                                        } while (n32Tmp != 0);
                                    } break;
#endif
                                    default:
                                        break;
                                } /* end switch */
                            } else {
                                /* the value to be converted is greater than 4G */
#if defined(SECUREC_VXWORKS_VERSION_5_4)
                                do {
                                    if (0 != SecU64Div32((SecUnsignedInt32)((number >> 16) >> 16),
                                        (SecUnsignedInt32)number, (SecUnsignedInt32)radix, &quotientHigh, &quotientLow,
                                        &digit)) {
                                        noOutput = 1;
                                        break;
                                    }
                                    *--formatBuf.str = digits[digit];

                                    number = (SecUnsignedInt64)quotientHigh;
                                    number = (number << 32) + quotientLow;
                                } while (number != 0);
#else
                                switch (radix) {
                                    /* the compiler will optimize div 10 */
                                    SECUREC_SPECIAL(number, 10);
                                    break;
                                    SECUREC_SPECIAL(number, 16);
                                    break;
                                    SECUREC_SPECIAL(number, 8);
                                    break;
                                    default:
                                        break;
                                }
#endif
                            }
#endif
                        } /* END if (number > 0) */
                        /* compute length of number,.if textLen > 0, then formatBuf.str must be in buffer.str */
                        textLen = (int)((char *)&buffer.str[SECUREC_BUFFER_SIZE] - formatBuf.str);
                        if (formatAttr.precision > textLen) {
                            for (ii = 0; ii < formatAttr.precision - textLen; ++ii) {
                                *--formatBuf.str = '0';
                            }
                            textLen = formatAttr.precision;
                        }

                        /* Force a leading zero if FORCEOCTAL flag set */
                        if ((formatAttr.flags & SECUREC_FLAG_FORCE_OCTAL) &&
                            (textLen == 0 || formatBuf.str[0] != '0')) {
                            *--formatBuf.str = '0';
                            ++textLen; /* add a zero */
                        }
                    } break;
                    default:
                        break;
                }

                if (noOutput == 0) {
                    if (formatAttr.flags & SECUREC_FLAG_SIGNED) {
                        if (formatAttr.flags & SECUREC_FLAG_NEGATIVE) {
                            /* prefix is a '-' */
                            prefix[0] = SECUREC_CHAR('-');
                            prefixLen = 1;
                        } else if (formatAttr.flags & SECUREC_FLAG_SIGN) {
                            /* prefix is '+' */
                            prefix[0] = SECUREC_CHAR('+');
                            prefixLen = 1;
                        } else if (formatAttr.flags & SECUREC_FLAG_SIGN_SPACE) {
                            /* prefix is ' ' */
                            prefix[0] = SECUREC_CHAR(' ');
                            prefixLen = 1;
                        }
                    }

#if defined(SECUREC_COMPATIBLE_LINUX_FORMAT) && (!defined(SECUREC_ON_UNIX))
                    if ((formatAttr.flags & SECUREC_FLAG_POINTER) && (0 == textLen)) {
                        formatAttr.flags &= ~SECUREC_FLAG_LEADZERO;
                        formatBuf.str = &buffer.str[SECUREC_BUFFER_SIZE - 1];
                        *formatBuf.str-- = '\0';
                        *formatBuf.str-- = ')';
                        *formatBuf.str-- = 'l';
                        *formatBuf.str-- = 'i';
                        *formatBuf.str-- = 'n';
                        *formatBuf.str = '(';
                        textLen = 5;
                    }
#endif

                    /* calculate amount of padding */
                    padding = (formatAttr.fldWidth - textLen) - prefixLen;

                    /* put out the padding, prefix, and text, in the correct order */

                    if (!(formatAttr.flags & (SECUREC_FLAG_LEFT | SECUREC_FLAG_LEADZERO)) && padding > 0) {
                        /* pad on left with blanks */
                        if (SECUREC_IS_REST_BUF_ENOUGH(padding)) {
                            /* char * cast to wchar * */
                            SECUREC_SAFE_PADDING(SECUREC_CHAR(' '), padding, stream, &charsOut);
                        } else {
                            SECUREC_WRITE_MULTI_CHAR(SECUREC_CHAR(' '), padding, stream, &charsOut);
                        }
                    }


                    /* write prefix */
                    if (prefixLen > 0) {
                        SecChar *pPrefix = prefix;
                        if (SECUREC_IS_REST_BUF_ENOUGH(prefixLen)) {
                            /* max prefix len is 2, use loop copy */ /* char * cast to wchar * */
                            SECUREC_SAFE_WRITE_PREFIX(pPrefix, prefixLen, stream, &charsOut);
                        } else {
                            SECUREC_WRITE_STRING(prefix, prefixLen, stream, &charsOut);
                        }
                    }

                    if ((formatAttr.flags & SECUREC_FLAG_LEADZERO) && !(formatAttr.flags & SECUREC_FLAG_LEFT) &&
                        padding > 0) {
                        /* write leading zeros */
                        if (SECUREC_IS_REST_BUF_ENOUGH(padding)) {
                            /* char * cast to wchar * */
                            SECUREC_SAFE_PADDING(SECUREC_CHAR('0'), padding, stream, &charsOut);
                        } else {
                            SECUREC_WRITE_MULTI_CHAR(SECUREC_CHAR('0'), padding, stream, &charsOut);
                        }
                    }

                    /* write text */
#ifndef SECUREC_FOR_WCHAR
                    if (!isDebugMode && isPrivacy) {
                        if (formatAttr.bufferIsWide) {
                            formatBuf.wStr = WPRIVACY_STRING;
                            textLen = sizeof(WPRIVACY_STRING) / sizeof(wchar_t) - 1;
                        } else {
                            formatBuf.str = PRIVACY_STRING;
                            textLen = strlen(PRIVACY_STRING);
                        }
                    }
                    if (formatAttr.bufferIsWide && (textLen > 0)) {
                        wchar_t *p = formatBuf.wStr;
                        int count = textLen;
                        while (count--) {
                            char tmpBuf[SECUREC_MB_LEN + 1];
                            // SECUREC_MASK_MSVC_CRT_WARNING
                            int retVal = wctomb(tmpBuf, *p++);
                            // SECUREC_END_MASK_MSVC_CRT_WARNING
                            if (retVal <= 0) {
                                charsOut = -1;
                                break;
                            }
                            SECUREC_WRITE_STRING(tmpBuf, retVal, stream, &charsOut);
                        }
                    } else {
                        if (SECUREC_IS_REST_BUF_ENOUGH(textLen)) {
                            SECUREC_SAFE_WRITE_STR(formatBuf.str, textLen, stream, &charsOut);
                        } else {
                            SECUREC_WRITE_STRING(formatBuf.str, textLen, stream, &charsOut);
                        }
                    }
#else /* SECUREC_FOR_WCHAR */
                    if (formatAttr.bufferIsWide == 0 && textLen > 0) {
                        int count = textLen;
                        char *p = formatBuf.str;

                        while (count > 0) {
                            wchar_t wchar = L'\0';
                            int retVal = mbtowc(&wchar, p, (size_t)MB_CUR_MAX);
                            if (retVal <= 0) {
                                charsOut = -1;
                                break;
                            }
                            SECUREC_WRITE_CHAR(wchar, stream, &charsOut);
                            p += retVal;
                            count -= retVal;
                        }
                    } else {
                        if (SECUREC_IS_REST_BUF_ENOUGH(textLen)) {
                            SECUREC_SAFE_WRITE_STR(formatBuf.wStr, textLen, stream,
                                &charsOut); /* char * cast to wchar * */
                        } else {
                            SECUREC_WRITE_STRING(formatBuf.wStr, textLen, stream, &charsOut);
                        }
                    }
#endif /* SECUREC_FOR_WCHAR */

                    if (charsOut >= 0 && (formatAttr.flags & SECUREC_FLAG_LEFT) && padding > 0) {
                        /* pad on right with blanks */
                        if (SECUREC_IS_REST_BUF_ENOUGH(padding)) {
                            /* char * cast to wchar * */
                            SECUREC_SAFE_PADDING(SECUREC_CHAR(' '), padding, stream, &charsOut);
                        } else {
                            SECUREC_WRITE_MULTI_CHAR(SECUREC_CHAR(' '), padding, stream, &charsOut);
                        }
                    }

                    /* we're done! */
                }
                if (floatBuf != NULL) {
                    SECUREC_FREE(floatBuf);
                    floatBuf = NULL;
                }
                break;
            case STAT_INVALID:
                return -1;
            default:
                return -1; /* input format is wrong, directly return */
        }
    }

    if (state != STAT_NORMAL && state != STAT_TYPE) {
        return -1;
    }

    return charsOut; /* the number of characters written */
} /* arglist must not be declare as const */


int HiLogSecVsnprintfImpl(char *string, size_t count, bool isDebugMode, const char *format, va_list arglist)
{
    SecPrintfStream str;
    int retVal;

    str.count = (int)count; /* this count include \0 character */
    str.cur = string;

    retVal = HiLogSecOutputS(&str, isDebugMode, format, arglist);
    if ((retVal >= 0) && (SECUREC_PUTC_ZERO(&str) != EOF)) {
        return (retVal);
    } else if (str.count < 0) {
        /* the buffer was too small; we return truncation */
        string[count - 1] = 0;
        return SECUREC_PRINTF_TRUNCATE;
    }

    return -1;
}


int HiLog_Printf(char *strDest, size_t destMax, size_t count, bool isDebugMode, const char *format, va_list arglist)
{
    int retVal;

    if (format == NULL || strDest == NULL || destMax == 0 || destMax > SECUREC_STRING_MAX_LEN ||
        (count > (SECUREC_STRING_MAX_LEN - 1) && count != (size_t)-1)) {
        if (strDest != NULL && destMax > 0) {
            strDest[0] = '\0';
        }
        SECUREC_ERROR_INVALID_PARAMTER("hilog_printf");
        return -1;
    }

    if (destMax > count) {
        retVal = HiLogSecVsnprintfImpl(strDest, count + 1, isDebugMode, format, arglist);
        if (retVal == SECUREC_PRINTF_TRUNCATE) { /* lsd add to keep dest buffer not destroyed 2014.2.18 */
            /* the string has been truncated, return  -1 */
            return -1; /* to skip error handler,  return strlen(strDest) or -1 */
        }
    } else { /* destMax <= count */
        retVal = HiLogSecVsnprintfImpl(strDest, destMax, isDebugMode, format, arglist);
#ifdef SECUREC_COMPATIBLE_WIN_FORMAT
        if (retVal == SECUREC_PRINTF_TRUNCATE && count == (size_t)-1) {
            return -1;
        }
#endif
    }

    if (retVal < 0) {
        strDest[0] = '\0'; /* empty the dest strDest */

        if (retVal == SECUREC_PRINTF_TRUNCATE) {
            /* Buffer too small */
            SECUREC_ERROR_INVALID_RANGE("hilog_printf");
        }

        SECUREC_ERROR_INVALID_PARAMTER("hilog_printf");
        return -1;
    }

    return retVal;
}

#define HILOG_DRIVER "/dev/hilog"
static char g_logLevelInfo[HILOG_LEVEL_MAX] = {
    'N', // "NONE"
    'N', // "NONE"
    'N', // "NONE"
    'D', // "DEBUG"
    'I', // "INFO"
    'W', // "WARN"
    'E', // "ERROR"
    'F'  // "FATAL"
};

#ifdef LOSCFG_BASE_CORE_HILOG
extern int HiLogWriteInternal(const char *buffer, size_t bufLen);
#else
static int g_hilogFd = -1;
#endif

int HiLogPrintArgs(LogType bufID, LogLevel prio, unsigned int domain, const char *tag, const char *fmt, va_list ap)
{
    int ret;
    char buf[LOG_BUF_SIZE] = {0};
    bool isDebugMode = 1;
    unsigned int bufLen;

#ifdef OHOS_RELEASE
    isDebugMode = 0;
#endif
    if (snprintf_s(buf, sizeof(buf), sizeof(buf) - 1, "%c %05X/%s: ", g_logLevelInfo[prio], (domain & DOMAIN_FILTER),
        tag) == -1) {
        return 0;
    }

    bufLen = strlen(buf);
    if (bufLen >= MAX_DOMAIN_TAG_SIZE) {
        return 0;
    }
    HiLog_Printf(buf + bufLen, LOG_BUF_SIZE - bufLen, LOG_BUF_SIZE - bufLen - 1, isDebugMode, fmt, ap);

#ifdef LOSCFG_BASE_CORE_HILOG
    ret = HiLogWriteInternal(buf, strlen(buf) + 1);
#else
    if (g_hilogFd == -1) {
        g_hilogFd = open(HILOG_DRIVER, O_WRONLY);
    }
    ret = write(g_hilogFd, buf, strlen(buf) + 1);
#endif
    return ret;
}

int HiLogPrint(LogType bufID, LogLevel prio, unsigned int domain, const char *tag, const char *fmt, ...)
{
    int ret;
    va_list ap;
    va_start(ap, fmt);
    ret = HiLogPrintArgs(bufID, prio, domain, tag, fmt, ap);
    va_end(ap);
    return ret;
}
