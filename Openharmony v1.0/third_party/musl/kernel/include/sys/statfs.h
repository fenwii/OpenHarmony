#ifndef	_SYS_STATFS_H
#define	_SYS_STATFS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <features.h>

#include <sys/statvfs.h>

typedef struct __fsid_t {
	int __val[2];
} fsid_t;

#include <bits/statfs.h>

int statfs (const char *, struct statfs *);
int fstatfs (int, struct statfs *);

#if defined(_LARGEFILE64_SOURCE) || defined(_GNU_SOURCE)
#define statfs64 statfs
#define fstatfs64 fstatfs
#define fsblkcnt64_t fsblkcnt_t
#define fsfilcnt64_t fsfilcnt_t
#endif

#define TMPFS_MAGIC           0x01021994
#define MSDOS_SUPER_MAGIC     0x4d44
#define NFS_SUPER_MAGIC       0x6969
#define PROCFS_MAGIC          0x434f5250
#define JFFS2_SUPER_MAGIC     0x72b6

#ifdef __cplusplus
}
#endif

#endif
