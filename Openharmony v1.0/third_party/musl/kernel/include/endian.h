#ifndef _ENDIAN_H
#define _ENDIAN_H

#include <features.h>

#define __NEED_uint16_t
#define __NEED_uint32_t
#define __NEED_uint64_t

#include <bits/alltypes.h>

#define __BIG_ENDIAN 4321
#define __LITTLE_ENDIAN 1234
#define __PDP_ENDIAN 3412

#define BIG_ENDIAN __BIG_ENDIAN
#define LITTLE_ENDIAN __LITTLE_ENDIAN
#define PDP_ENDIAN __PDP_ENDIAN
#define BYTE_ORDER __BYTE_ORDER

#include <stdint.h>

static __inline uint16_t __bswap16(uint16_t __x)
{
	return __x<<8 | __x>>8;
}

static __inline uint32_t __bswap32(uint32_t __x)
{
	return (__x>>24) | ((__x>>8)&(0xff00)) | ((__x<<8)&(0xff0000)) | ((__x<<24));
}

static __inline uint64_t __bswap64(uint64_t __x)
{
	return (__bswap32(__x)+0ULL)<<32 | __bswap32(__x>>32);
}

#if __BYTE_ORDER == __LITTLE_ENDIAN
#define htobe16(x) __bswap16(x)
#define be16toh(x) __bswap16(x)
#define htobe32(x) __bswap32(x)
#define be32toh(x) __bswap32(x)
#define htobe64(x) __bswap64(x)
#define be64toh(x) __bswap64(x)
#define htole16(x) (uint16_t)(x)
#define le16toh(x) (uint16_t)(x)
#define htole32(x) (uint32_t)(x)
#define le32toh(x) (uint32_t)(x)
#define htole64(x) (uint64_t)(x)
#define le64toh(x) (uint64_t)(x)
#else
#define htobe16(x) (uint16_t)(x)
#define be16toh(x) (uint16_t)(x)
#define htobe32(x) (uint32_t)(x)
#define be32toh(x) (uint32_t)(x)
#define htobe64(x) (uint64_t)(x)
#define be64toh(x) (uint64_t)(x)
#define htole16(x) __bswap16(x)
#define le16toh(x) __bswap16(x)
#define htole32(x) __bswap32(x)
#define le32toh(x) __bswap32(x)
#define htole64(x) __bswap64(x)
#define le64toh(x) __bswap64(x)
#endif

#if defined(_GNU_SOURCE) || defined(_BSD_SOURCE)
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define betoh16(x) __bswap16(x)
#define betoh32(x) __bswap32(x)
#define betoh64(x) __bswap64(x)
#define letoh16(x) (uint16_t)(x)
#define letoh32(x) (uint32_t)(x)
#define letoh64(x) (uint64_t)(x)
#else
#define betoh16(x) (uint16_t)(x)
#define betoh32(x) (uint32_t)(x)
#define betoh64(x) (uint64_t)(x)
#define letoh16(x) __bswap16(x)
#define letoh32(x) __bswap32(x)
#define letoh64(x) __bswap64(x)
#endif
#endif

static __inline uint32_t
be32dec(const void *pp)
{
    uint8_t const *p = (uint8_t const *)pp;

    return (((unsigned)p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

static __inline void
be32enc(void *pp, uint32_t u)
{
    uint8_t *p = (uint8_t *)pp;

    p[0] = (u >> 24) & 0xff;
    p[1] = (u >> 16) & 0xff;
    p[2] = (u >> 8) & 0xff;
    p[3] = u & 0xff;
}

static __inline void
be64enc(void *pp, uint64_t u)
{
    uint8_t *p = (uint8_t *)pp;

    be32enc(p, (uint32_t)(u >> 32));
    be32enc(p + 4, (uint32_t)(u & 0xffffffffU));
}

#endif
