#ifndef	_ERRNO_H
#define _ERRNO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#include <bits/errno.h>

void set_errno(int err_code);
int get_errno(void);
int *__errno_location(void);

#ifdef __GNUC__
__attribute__((const))
#endif
extern volatile int* __errno(void);
#define errno (*__errno())

#ifdef _GNU_SOURCE
extern char *program_invocation_short_name, *program_invocation_name;
#endif

#ifdef __cplusplus
}
#endif

#endif

