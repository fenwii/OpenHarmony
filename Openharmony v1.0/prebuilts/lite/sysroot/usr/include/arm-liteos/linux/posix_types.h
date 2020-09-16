/*
 * This header was generated from the Linux kernel headers by update_headers.py,
 * to provide necessary information from kernel to userspace, such as constants,
 * structures, and macros, and thus, contains no copyrightable information.
 */
#ifndef _LINUX_POSIX_TYPES_H
#define _LINUX_POSIX_TYPES_H
#include <linux/stddef.h>
#undef __FD_SETSIZE
#define __FD_SETSIZE	1024
typedef struct {
	unsigned long fds_bits[__FD_SETSIZE / (8 * sizeof(long))];
} __kernel_fd_set;
typedef void (*__kernel_sighandler_t)(int);
typedef int __kernel_key_t;
typedef int __kernel_mqd_t;
#include <asm/posix_types.h>
#endif
