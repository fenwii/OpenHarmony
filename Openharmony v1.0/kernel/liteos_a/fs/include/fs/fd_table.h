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

#ifndef __INCLUDE_FS_FDTABLE_H
#define __INCLUDE_FS_FDTABLE_H

#include <limits.h>
#include <sys/select.h>
#include <semaphore.h>
#include "linux/spinlock.h"

/* open file table for process fd */
struct file_table_s {
    signed short sysFd; /* system fd associate with the tg_filelist index */
};

struct fd_table_s {
    unsigned int max_fds;
    struct file_table_s *ft_fds; /* process fd array associate with system fd */
    fd_set *open_fds;
    fd_set *proc_fds;
    sem_t ft_sem; /* manage access to the file table */
};

struct files_struct {
    int count;
    struct fd_table_s *fdt;
    unsigned int file_lock;
    unsigned int next_fd;
#ifdef VFS_USING_WORKDIR
    spinlock_t workdir_lock;
    char workdir[PATH_MAX];
#endif
};

typedef struct ProcessCB LosProcessCB;

void files_refer(int fd);

struct files_struct *dup_fd(struct files_struct *oldf);

struct files_struct *alloc_files(void);

void delete_files(LosProcessCB *processCB, struct files_struct *files);

struct files_struct *create_files_snapshot(const struct files_struct *oldf);

void delete_files_snapshot(struct files_struct *files);

int alloc_fd(int minfd);

#endif
