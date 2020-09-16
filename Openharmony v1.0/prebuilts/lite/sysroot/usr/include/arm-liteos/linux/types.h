/*
 * This header was generated from the Linux kernel headers by update_headers.py,
 * to provide necessary information from kernel to userspace, such as constants,
 * structures, and macros, and thus, contains no copyrightable information.
 */
#ifndef _UAPI_LINUX_TYPES_H
#define _UAPI_LINUX_TYPES_H
#include <asm/types.h>
#ifndef __ASSEMBLY__
#ifndef	__KERNEL__
#if 0
#warning "Attempt to use kernel headers from user space, see http:
#endif
#endif
#include <linux/posix_types.h>
#if 0
#define __bitwise__ __attribute__((bitwise))
#else
#define __bitwise__
#endif
#define __bitwise __bitwise__
typedef __u16 __bitwise __le16;
typedef __u16 __bitwise __be16;
typedef __u32 __bitwise __le32;
typedef __u32 __bitwise __be32;
typedef __u64 __bitwise __le64;
typedef __u64 __bitwise __be64;
typedef __u16 __bitwise __sum16;
typedef __u32 __bitwise __wsum;
#define __aligned_u64 __u64 __attribute__((aligned(8)))
#define __aligned_be64 __be64 __attribute__((aligned(8)))
#define __aligned_le64 __le64 __attribute__((aligned(8)))
typedef unsigned __bitwise __poll_t;
#endif
#endif
