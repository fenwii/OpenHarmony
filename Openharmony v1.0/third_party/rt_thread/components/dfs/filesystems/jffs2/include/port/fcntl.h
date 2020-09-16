#ifndef CYGONCE_ISO_FCNTL_H
#define CYGONCE_ISO_FCNTL_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cplusplus */
#endif /* __cplusplus */

#define __CC_ARM
/* File access modes used for open() and fnctl() */
/* for vfs_jffs2.c                                                             */
/*------------------------------------------------------------------------*/
/* File access modes used for open() and fnctl() */

/* File access mode mask */
#define JFFS2_O_ACCMODE (O_RDONLY | O_WRONLY | O_NONBLOCK | O_APPEND)


#define JFFS2_O_EXECVE     (1 << 2)    /* Execute use */

#define READ_OP                4
#define WRITE_OP               2
#define EXEC_OP                1
#define JFFS2_USER_SHFIT       6
#define JFFS2_GROUP_SHFIT      3
#define JFFS2_MODE_ALL         (READ_OP | WRITE_OP | EXEC_OP)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cplusplus */
#endif /* __cplusplus */

#endif
/* EOF fcntl.h */
