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

#include "los_load_elf.h"
#include "fs/fd_table.h"
#include "los_config.h"
#include "los_vm_map.h"
#include "los_vm_syscall.h"
#include "los_vm_phys.h"
#include "los_vm_dump.h"
#ifdef LOSCFG_KERNEL_VDSO
#include "los_vdso.h"
#endif
#ifdef LOSCFG_DRIVERS_TZDRIVER
#include "tzdriver.h"
#endif

STATIC INT32 OsGetFileLength(UINT32 *fileLen, const CHAR *fileName)
{
    struct stat buf;
    INT32 ret;

    ret = stat(fileName, &buf);
    if (ret < 0) {
#ifndef LOSCFG_SHELL
        if (strcmp(fileName, "/bin/shell") != 0) {
#endif
            PRINT_ERR("%s[%d], Failed to stat file: %s, errno: %d\n", __FUNCTION__, __LINE__, fileName, errno);
#ifndef LOSCFG_SHELL
        }
#endif
        return LOS_NOK;
    }

    if (S_ISREG(buf.st_mode) == 0) {
        PRINT_ERR("%s[%d], The file: %s is invalid!\n", __FUNCTION__, __LINE__, fileName);
        return LOS_NOK;
    }
    if (buf.st_size > FILE_LENGTH_MAX) {
        PRINT_ERR("%s[%d], The file: %s length is out of limit!\n", __FUNCTION__, __LINE__, fileName);
        return LOS_NOK;
    }

    *fileLen = (UINT32)buf.st_size;
    return LOS_OK;
}

STATIC INT32 OsReadELFInfo(INT32 fd, UINT8 *buffer, size_t readSize, off_t offset)
{
    ssize_t byteNum;
    off_t returnPos;

    if (readSize > 0) {
        returnPos = lseek(fd, offset, SEEK_SET);
        if (returnPos != offset) {
            PRINT_ERR("%s[%d], Failed to seek the position!, offset: %#x\n", __FUNCTION__, __LINE__, offset);
            return LOS_NOK;
        }

        byteNum = read(fd, buffer, readSize);
        if (byteNum <= 0) {
            PRINT_ERR("%s[%d], Failed to read from offset: %#x!\n", __FUNCTION__, __LINE__, offset);
            return LOS_NOK;
        }
    }
    return LOS_OK;
}

STATIC INT32 OsVerifyELFEhdr(const LD_ELF_EHDR *ehdr, UINT32 fileLen)
{
    if (memcmp(ehdr->elfIdent, LD_ELFMAG, LD_SELFMAG) != 0) {
        PRINT_ERR("%s[%d], The file is not elf!\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }
    if ((ehdr->elfType != LD_ET_EXEC) && (ehdr->elfType != LD_ET_DYN)) {
        PRINT_ERR("%s[%d], The type of file is not ET_EXEC or ET_DYN!\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }
    if (ehdr->elfMachine != LD_EM_ARM) {
        PRINT_ERR("%s[%d], The type of machine is not EM_ARM!\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }
    if (ehdr->elfPhNum > ELF_PHDR_NUM_MAX) {
        PRINT_ERR("%s[%d], The num of program header is out of limit\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }
    if (ehdr->elfPhoff > fileLen) {
        PRINT_ERR("%s[%d], The offset of program header is invalid, elf file is bad\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }
    if (OsIsBadUserAddress((VADDR_T)ehdr->elfEntry)) {
        PRINT_ERR("%s[%d], The entry of program is invalid\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }

    return LOS_OK;
}

STATIC INT32 OsVerifyELFPhdr(const LD_ELF_PHDR *phdr)
{
    if ((phdr->fileSize > FILE_LENGTH_MAX) || (phdr->offset > FILE_LENGTH_MAX)) {
        PRINT_ERR("%s[%d], The size of phdr is out of limit\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }
    if (phdr->memSize > MEM_SIZE_MAX) {
        PRINT_ERR("%s[%d], The mem size of phdr is out of limit\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }
    if (OsIsBadUserAddress((VADDR_T)phdr->vAddr)) {
        PRINT_ERR("%s[%d], The vaddr of phdr is invalid\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }

    return LOS_OK;
}

STATIC INT32 OsELFLoadInit(const CHAR *fileName, ELFLoadInfo *loadInfo)
{
    INT32 ret;
#ifdef LOSCFG_FS_VFS
    const struct files_struct *oldFiles = OsCurrProcessGet()->files;
    loadInfo->oldFiles = (UINTPTR)create_files_snapshot(oldFiles);
#else
    loadInfo->oldFiles = NULL;
#endif
    loadInfo->execFD = INVALID_FD;
    loadInfo->interpFD = INVALID_FD;

    ret = OsGetFileLength(&loadInfo->execFileLen, fileName);
    if (ret != LOS_OK) {
        return -ENOENT;
    }

    loadInfo->execFD = open(fileName, O_RDONLY | O_EXECVE);
    if (loadInfo->execFD < 0) {
        if (get_errno() == EACCES) {
            return -EACCES;
        }
        PRINT_ERR("%s[%d], Failed to open ELF file: %s!\n", __FUNCTION__, __LINE__, fileName);
        return -ENOENT;
    }

#ifdef LOSCFG_DRIVERS_TZDRIVER
    ret = fs_getfilep(loadInfo->execFD, &OsCurrProcessGet()->execFile);
    if (ret) {
        PRINT_ERR("%s[%d], Failed to get struct file %s!\n", __FUNCTION__, __LINE__, fileName);
    }
#endif
    ret = OsReadELFInfo(loadInfo->execFD, (UINT8 *)&loadInfo->elfEhdr, sizeof(LD_ELF_EHDR), 0);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return -EIO;
    }

    ret = OsVerifyELFEhdr(&loadInfo->elfEhdr, loadInfo->execFileLen);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return -ENOEXEC;
    }

    return LOS_OK;
}

STATIC INT32 OsLoadProgramHdrs(ELFLoadInfo *loadInfo)
{
    LD_ELF_EHDR *elfEhdr = NULL;
    UINT32 size;
    INT32 ret;

    if (loadInfo->elfEhdr.elfPhNum < 1) {
        PRINT_ERR("%s[%d], No program sections in file: %s!\n", __FUNCTION__, __LINE__, loadInfo->fileName);
        return -ENOEXEC;
    }

    elfEhdr = &loadInfo->elfEhdr;
    if (elfEhdr->elfPhEntSize != sizeof(LD_ELF_PHDR)) {
        PRINT_ERR("%s[%d], e_phentsize is invalid, file: %s\n", __FUNCTION__, __LINE__, loadInfo->fileName);
        return -ENOEXEC;
    }

    size = sizeof(LD_ELF_PHDR) * elfEhdr->elfPhNum;
    if ((elfEhdr->elfPhoff + size) > loadInfo->execFileLen) {
        PRINT_ERR("%s[%d], Size for program header exceeds limit! file: %s\n", __FUNCTION__, __LINE__,
                  loadInfo->fileName);
        return -ENOEXEC;
    }

    loadInfo->elfPhdr = LOS_MemAlloc(m_aucSysMem0, size);
    if (loadInfo->elfPhdr == NULL) {
        PRINT_ERR("%s[%d], Failed to allocate for elfPhdr! file: %s\n", __FUNCTION__, __LINE__, loadInfo->fileName);
        return -ENOMEM;
    }

    ret = OsReadELFInfo(loadInfo->execFD, (UINT8 *)loadInfo->elfPhdr, size, elfEhdr->elfPhoff);
    if (ret != LOS_OK) {
        (VOID)LOS_MemFree(m_aucSysMem0, loadInfo->elfPhdr);
        loadInfo->elfPhdr = NULL;
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return -EIO;
    }

    return LOS_OK;
}

STATIC INT32 OsGetInterpEhdr(const CHAR *fileName, ELFLoadInfo *loadInfo)
{
    INT32 ret;

    ret = OsGetFileLength(&loadInfo->interpFileLen, fileName);
    if (ret != LOS_OK) {
        return -ENOENT;
    }

    loadInfo->interpFD = open(fileName, O_RDONLY);
    if (loadInfo->interpFD < 0) {
        PRINT_ERR("%s[%d], Failed to open ELF file: %s!\n", __FUNCTION__, __LINE__, fileName);
        return -ENOENT;
    }

    ret = OsReadELFInfo(loadInfo->interpFD, (UINT8 *)&loadInfo->interpELFEhdr, sizeof(LD_ELF_EHDR), 0);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return -EIO;
    }

    ret = OsVerifyELFEhdr(&loadInfo->interpELFEhdr, loadInfo->interpFileLen);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d], ELF header of file: %s is invalid!\n", __FUNCTION__, __LINE__, fileName);
        return -ELIBBAD;
    }

    return LOS_OK;
}

STATIC INT32 OsLoadInterpProgramHdrs(ELFLoadInfo *loadInfo)
{
    LD_ELF_EHDR *elfEhdr = &loadInfo->interpELFEhdr;
    UINT32 size;
    INT32 ret;

    if (elfEhdr->elfPhNum < 1) {
        PRINT_ERR("%s[%d], No program sections of interpreter!\n", __FUNCTION__, __LINE__);
        return -ELIBBAD;
    }

    if (elfEhdr->elfPhEntSize != sizeof(LD_ELF_PHDR)) {
        PRINT_ERR("%s[%d], e_phentsize of interpreter is invalid!\n", __FUNCTION__, __LINE__);
        return -ELIBBAD;
    }

    size = sizeof(LD_ELF_PHDR) * elfEhdr->elfPhNum;
    if ((elfEhdr->elfPhoff + size) > loadInfo->interpFileLen) {
        PRINT_ERR("%s[%d], Size for program header of interpreter exceeds limit!\n", __FUNCTION__, __LINE__);
        return -ELIBBAD;
    }

    loadInfo->interpELFPhdr = LOS_MemAlloc(m_aucSysMem0, size);
    if (loadInfo->interpELFPhdr == NULL) {
        PRINT_ERR("%s[%d], Failed to allocate for elfPhdr of interpreter!\n", __FUNCTION__, __LINE__);
        return -ENOMEM;
    }

    ret = OsReadELFInfo(loadInfo->interpFD, (UINT8 *)loadInfo->interpELFPhdr, size, elfEhdr->elfPhoff);
    if (ret != LOS_OK) {
        (VOID)LOS_MemFree(m_aucSysMem0, loadInfo->interpELFPhdr);
        loadInfo->interpELFPhdr = NULL;
        PRINT_ERR("%s[%d], Failed to read program header of interpreter!\n", __FUNCTION__, __LINE__);
        return -EIO;
    }

    return LOS_OK;
}

STATIC INT32 OsReadInterpInfo(ELFLoadInfo *loadInfo)
{
    LD_ELF_PHDR *elfPhdr = loadInfo->elfPhdr;
    CHAR *elfInterpName = NULL;
    INT32 ret, i;

    for (i = 0; i < loadInfo->elfEhdr.elfPhNum; ++i, ++elfPhdr) {
        if (elfPhdr->type != LD_PT_INTERP) {
            continue;
        }

        if (OsVerifyELFPhdr(elfPhdr) != LOS_OK) {
            return -ENOEXEC;
        }

        if ((elfPhdr->fileSize > FILE_PATH_MAX) || (elfPhdr->fileSize < FILE_PATH_MIN) ||
            (elfPhdr->offset + elfPhdr->fileSize > loadInfo->execFileLen)) {
            PRINT_ERR("%s[%d], The size of file is out of limit!\n", __FUNCTION__, __LINE__);
            return -ENOEXEC;
        }

        elfInterpName = LOS_MemAlloc(m_aucSysMem0, elfPhdr->fileSize);
        if (elfInterpName == NULL) {
            PRINT_ERR("%s[%d], Failed to allocate for elfInterpName!\n", __FUNCTION__, __LINE__);
            return -ENOMEM;
        }

        ret = OsReadELFInfo(loadInfo->execFD, (UINT8 *)elfInterpName, elfPhdr->fileSize, elfPhdr->offset);
        if (ret != LOS_OK) {
            PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
            ret = -EIO;
            goto OUT;
        }

        if (elfInterpName[elfPhdr->fileSize - 1] != '\0') {
            PRINT_ERR("%s[%d], The name of interpreter is invalid!\n", __FUNCTION__, __LINE__);
            ret = -ENOEXEC;
            goto OUT;
        }

        ret = OsGetInterpEhdr(INTERP_FULL_PATH, loadInfo);
        if (ret != LOS_OK) {
            PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
            goto OUT;
        }

        ret = OsLoadInterpProgramHdrs(loadInfo);
        if (ret != LOS_OK) {
            goto OUT;
        }

        (VOID)LOS_MemFree(m_aucSysMem0, elfInterpName);
        break;
    }

    return LOS_OK;

OUT:
    (VOID)LOS_MemFree(m_aucSysMem0, elfInterpName);
    return ret;
}

STATIC UINT32 OsGetProt(UINT32 pFlags)
{
    UINT32 prot;

    prot = (((pFlags & PF_R) ? PROT_READ : 0) |
            ((pFlags & PF_W) ? PROT_WRITE : 0) |
            ((pFlags & PF_X) ? PROT_EXEC : 0));
    return prot;
}

STATIC UINT32 OsGetAllocSize(const LD_ELF_PHDR *elfPhdr, INT32 phdrNum)
{
    const LD_ELF_PHDR *elfPhdrTemp = elfPhdr;
    UINTPTR addrMin = SIZE_MAX;
    UINTPTR addrMax = 0;
    UINT32 offStart = 0;
    UINT64 size;
    INT32 i;

    for (i = 0; i < phdrNum; ++i, ++elfPhdrTemp) {
        if (elfPhdrTemp->type != LD_PT_LOAD) {
            continue;
        }

        if (OsVerifyELFPhdr(elfPhdrTemp) != LOS_OK) {
            return 0;
        }

        if (elfPhdrTemp->vAddr < addrMin) {
            addrMin = elfPhdrTemp->vAddr;
            offStart = elfPhdrTemp->offset;
        }
        if ((elfPhdrTemp->vAddr + elfPhdrTemp->memSize) > addrMax) {
            addrMax = elfPhdrTemp->vAddr + elfPhdrTemp->memSize;
        }
    }

    if (OsIsBadUserAddress((VADDR_T)addrMax) || OsIsBadUserAddress((VADDR_T)addrMin) || (addrMax < addrMin)) {
        return 0;
    }
    size = ROUNDUP(addrMax, PAGE_SIZE) - ROUNDDOWN(addrMin, PAGE_SIZE) + ROUNDDOWN(offStart, PAGE_SIZE);

    return (size > UINT_MAX) ? 0 : (UINT32)size;
}

STATIC UINTPTR OsDoMmapFile(INT32 fd, UINTPTR addr, const LD_ELF_PHDR *elfPhdr, UINT32 prot, UINT32 flags,
                            UINT32 mapSize)
{
    UINTPTR mapAddr;
    UINT32 size;
    UINT32 offset = elfPhdr->offset - ROUNDOFFSET(elfPhdr->vAddr, PAGE_SIZE);
    addr = ROUNDDOWN(addr, PAGE_SIZE);

    if (mapSize != 0) {
        mapAddr = (UINTPTR)LOS_MMap(addr, mapSize, prot, flags, fd, offset >> PAGE_SHIFT);
    } else {
        size = elfPhdr->memSize + ROUNDOFFSET(elfPhdr->vAddr, PAGE_SIZE);
        if (size == 0) {
            return addr;
        }
        mapAddr = (UINTPTR)LOS_MMap(addr, size, prot, flags, fd, offset >> PAGE_SHIFT);
    }
    if (!LOS_IsUserAddress((VADDR_T)mapAddr)) {
        PRINT_ERR("%s %d, Failed to map a valid addr\n", __FUNCTION__, __LINE__);
        return 0;
    }
    return mapAddr;
}

INT32 OsGetKernelVaddr(const LosVmSpace *space, VADDR_T vaddr, VADDR_T *kvaddr)
{
    INT32 ret;
    PADDR_T paddr = 0;

    if ((space == NULL) || (vaddr == 0) || (kvaddr == NULL)) {
        PRINT_ERR("%s[%d], space: %#x, vaddr: %#x\n", __FUNCTION__, __LINE__, space, vaddr);
        return LOS_NOK;
    }

    if (LOS_IsKernelAddress(vaddr)) {
        *kvaddr = vaddr;
        return LOS_OK;
    }

    ret = LOS_ArchMmuQuery(&space->archMmu, vaddr, &paddr, NULL);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d], Failed to query the vaddr: %#x, status: %d\n", __FUNCTION__, __LINE__, vaddr, ret);
        return LOS_NOK;
    }
    *kvaddr = (VADDR_T)(UINTPTR)LOS_PaddrToKVaddr(paddr);
    if (*kvaddr == 0) {
        PRINT_ERR("%s[%d], kvaddr is null\n", __FUNCTION__, __LINE__);
        return LOS_NOK;
    }

    return LOS_OK;
}

STATIC INT32 OsSetBss(const LD_ELF_PHDR *elfPhdr, INT32 fd, UINTPTR bssStart, UINT32 bssEnd, UINT32 elfProt)
{
    UINTPTR bssPageStart, bssStartPageAlign, bssEndPageAlign;
    UINTPTR mapBase;
    UINT32 offset, size;
    UINT32 bssMapSize;
    INT32 stackFlags;
    INT32 ret;
    vaddr_t kvaddr = 0;

    bssPageStart = ROUNDDOWN(bssStart, PAGE_SIZE);
    bssStartPageAlign = ROUNDUP(bssStart, PAGE_SIZE);
    bssEndPageAlign = ROUNDUP(bssEnd, PAGE_SIZE);
    ret = LOS_UnMMap(bssPageStart, (bssEndPageAlign - bssPageStart));
    if ((ret != LOS_OK) && (bssPageStart != 0)) {
        PRINT_ERR("%s[%d], Failed to unmap a region, vaddr: %#x!\n", __FUNCTION__, __LINE__, bssPageStart);
    }

    ret = LOS_UserSpaceVmAlloc(OsCurrProcessGet()->vmSpace, PAGE_SIZE, (VOID **)&bssPageStart,
                               0, OsCvtProtFlagsToRegionFlags(elfProt, 0));
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d], Failed to do vmm alloc!\n", __FUNCTION__, __LINE__);
        return -ENOMEM;
    }
    ret = OsGetKernelVaddr(OsCurrProcessGet()->vmSpace, bssPageStart, &kvaddr);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return -EFAULT;
    }
    (VOID)memset_s((VOID *)(UINTPTR)kvaddr, PAGE_SIZE, 0, PAGE_SIZE);

    offset = ROUNDDOWN(elfPhdr->offset + elfPhdr->fileSize, PAGE_SIZE);
    size = ROUNDOFFSET(elfPhdr->offset + elfPhdr->fileSize, PAGE_SIZE);
    ret = OsReadELFInfo(fd, (UINT8 *)(UINTPTR)kvaddr, size, offset);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return -EIO;
    }

    bssMapSize = bssEndPageAlign - bssStartPageAlign;
    if (bssMapSize > 0) {
        stackFlags = MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS;
        mapBase = (UINTPTR)LOS_MMap(bssStartPageAlign, bssMapSize, elfProt, stackFlags, -1, 0);
        if (!LOS_IsUserAddress((VADDR_T)mapBase)) {
            PRINT_ERR("%s[%d], Failed to map bss\n", __FUNCTION__, __LINE__);
            return -ENOMEM;
        }
    }

    return LOS_OK;
}

STATIC INT32 OsMmapELFFile(INT32 fd, const LD_ELF_PHDR *elfPhdr, const LD_ELF_EHDR *elfEhdr, UINTPTR *elfLoadAddr,
                           UINT32 mapSize, UINTPTR *loadBase)
{
    const LD_ELF_PHDR *elfPhdrTemp = elfPhdr;
    UINTPTR vAddr, mapAddr, bssStart;
    UINT32 bssEnd, elfProt, elfFlags;
    INT32 ret, i;

    for (i = 0; i < elfEhdr->elfPhNum; ++i, ++elfPhdrTemp) {
        if (elfPhdrTemp->type != LD_PT_LOAD) {
            continue;
        }
        if (elfEhdr->elfType == LD_ET_EXEC) {
            if (OsVerifyELFPhdr(elfPhdrTemp) != LOS_OK) {
                return -ENOEXEC;
            }
        }

        elfProt = OsGetProt(elfPhdrTemp->flags);
        if ((elfProt & PROT_READ) == 0) {
            return -ENOEXEC;
        }
        elfFlags = MAP_PRIVATE;
        vAddr = elfPhdrTemp->vAddr;

        mapAddr = OsDoMmapFile(fd, (vAddr + *loadBase), elfPhdrTemp, elfProt, elfFlags, mapSize);
        if (!LOS_IsUserAddress((VADDR_T)mapAddr)) {
            return -ENOMEM;
        }
#ifdef LOSCFG_DRIVERS_TZDRIVER
        if ((elfPhdrTemp->flags & PF_R) && (elfPhdrTemp->flags & PF_X) && !(elfPhdrTemp->flags & PF_W)) {
            SetVmmRegionCodeStart(vAddr + *loadBase, elfPhdrTemp->memSize);
        }
#endif
        mapSize = 0;

        if (*elfLoadAddr == 0) {
            *elfLoadAddr = mapAddr + ROUNDOFFSET(vAddr, PAGE_SIZE);
        }

        if ((*loadBase == 0) && (elfEhdr->elfType == LD_ET_DYN)) {
            *loadBase = mapAddr;
            elfFlags |= MAP_FIXED;
        }

        if ((elfPhdrTemp->memSize > elfPhdrTemp->fileSize) && (elfPhdrTemp->flags & PF_W)) {
            bssStart = mapAddr + ROUNDOFFSET(vAddr, PAGE_SIZE) + elfPhdrTemp->fileSize;
            bssEnd = mapAddr + ROUNDOFFSET(vAddr, PAGE_SIZE) + elfPhdrTemp->memSize;
            ret = OsSetBss(elfPhdrTemp, fd, bssStart, bssEnd, elfProt);
            if (ret != LOS_OK) {
                return ret;
            }
        }
    }

    return LOS_OK;
}

STATIC INT32 OsLoadInterpBinary(const ELFLoadInfo *loadInfo, UINTPTR *interpMapBase)
{
    UINTPTR loadBase = 0;
    UINT32 mapSize;
    INT32 ret;

    mapSize = OsGetAllocSize(loadInfo->interpELFPhdr, loadInfo->interpELFEhdr.elfPhNum);
    if (mapSize == 0) {
        PRINT_ERR("%s[%d], Failed to get interp allocation size!\n", __FUNCTION__, __LINE__);
        return -EINVAL;
    }

    ret = OsMmapELFFile(loadInfo->interpFD, loadInfo->interpELFPhdr, &loadInfo->interpELFEhdr, interpMapBase,
                        mapSize, &loadBase);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return ret;
    }

    return LOS_OK;
}

STATIC CHAR *OsGetParamPtr(CHAR * const *ptr, INT32 index)
{
    UINTPTR userStrPtr = 0;
    INT32 ret;

    if (ptr == NULL) {
        return NULL;
    }

    if (LOS_IsKernelAddress((UINTPTR)ptr)) {
        return ptr[index];
    }
    ret = LOS_GetUser(&userStrPtr, (UINTPTR *)(ptr + index));
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d], %#x\n", __FUNCTION__, __LINE__, ptr);
        return NULL;
    }

    return (CHAR *)userStrPtr;
}

STATIC INT32 OsPutUserArg(INT32 val, const UINTPTR *sp)
{
    INT32 ret;

    if (sp == NULL) {
        return LOS_NOK;
    }

    ret = LOS_PutUser((INT32 *)&val, (INT32 *)sp);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return -EFAULT;
    }

    return LOS_OK;
}

STATIC INT32 OsPutUserArgv(UINTPTR *strPtr, UINTPTR **sp, INT32 count)
{
    INT32 len;
    INT32 i;
    CHAR *ptr = NULL;

    if ((strPtr == NULL) || (sp == NULL)) {
        return LOS_NOK;
    }

    for (i = 0; i < count; ++i) {
        /* put the addr of arg strings to user stack */
        if (OsPutUserArg(*strPtr, *sp) != LOS_OK) {
            return LOS_NOK;
        }
        ptr = OsGetParamPtr((CHAR **)strPtr, 0);
        if (ptr == NULL) {
            return LOS_NOK;
        }
        len = LOS_StrnlenUser(ptr, PATH_MAX);
        if (len == 0) {
            return LOS_NOK;
        }
        *strPtr += len;
        ++(*sp);
    }
    /* put zero to end of argv */
    if (OsPutUserArg(0, *sp) != LOS_OK) {
        return LOS_NOK;
    }
    ++(*sp);

    return LOS_OK;
}

STATIC INT32 OsCopyParams(ELFLoadInfo *loadInfo, INT32 argc, CHAR *const *argv)
{
    CHAR *strPtr = NULL;
    UINT32 offset, strLen;
    errno_t err;
    INT32 ret, i;
    vaddr_t kvaddr = 0;

    if ((argc > 0) && (argv == NULL)) {
        return -EINVAL;
    }

    ret = OsGetKernelVaddr(loadInfo->newSpace, loadInfo->stackParamBase, &kvaddr);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return -EFAULT;
    }

    for (i = argc - 1; i >= 0; --i) {
        strPtr = OsGetParamPtr(argv, i);
        if (LOS_IsKernelAddress((VADDR_T)(UINTPTR)strPtr)) {
            strLen = strlen(strPtr) + 1;
        } else {
            strLen = LOS_StrnlenUser(strPtr, PATH_MAX);
        }
        if (strLen < 1) {
            continue;
        }

        offset = loadInfo->topOfMem - loadInfo->stackParamBase;
        if (offset < strLen) {
            PRINT_ERR("%s[%d], The size of param is out of limit: %#x bytes!\n", __FUNCTION__, __LINE__,
                      USER_PARAM_BYTE_MAX);
            return -E2BIG;
        }
        loadInfo->topOfMem -= strLen;
        offset -= strLen;

        /* copy strings to user stack */
        if (LOS_IsKernelAddress((VADDR_T)(UINTPTR)strPtr)) {
            err = memcpy_s((VOID *)(UINTPTR)(kvaddr + offset), strLen, strPtr, strLen);
        } else {
            err = LOS_ArchCopyFromUser((VOID *)(UINTPTR)(kvaddr + offset), strPtr, strLen);
        }

        if (err != EOK) {
            PRINT_ERR("%s[%d], copy strings failed! err: %d\n", __FUNCTION__, __LINE__, err);
            return -EFAULT;
        }
    }

    return LOS_OK;
}

STATIC INT32 OsGetParamNum(CHAR *const *argv)
{
    CHAR *argPtr = NULL;
    INT32 count = 0;
    INT32 ret;

    if (argv == NULL) {
        return count;
    }

    argPtr = OsGetParamPtr(argv, count);
    while (argPtr != NULL) {
        ret = LOS_StrnlenUser(argPtr, PATH_MAX);
        if ((ret == 0) || (ret > PATH_MAX)) {
            PRINT_ERR("%s[%d], the len of string of argv is invalid, index: %d, len: %d\n", __FUNCTION__,
                      __LINE__, count, ret);
            break;
        }
        ++count;
        if (count >= STRINGS_COUNT_MAX) {
            break;
        }
        argPtr = OsGetParamPtr(argv, count);
    }

    return count;
}

STATIC UINT32 OsGetRndOffset(const ELFLoadInfo *loadInfo)
{
    UINT32 randomValue = 0;

#ifdef LOSCFG_ASLR
    if (read(loadInfo->randomDevFD, &randomValue, sizeof(UINT32)) == sizeof(UINT32)) {
        randomValue &= RANDOM_MASK;
    } else {
        randomValue = 0;
    }
#else
    (VOID)loadInfo;
#endif

    return ROUNDDOWN(randomValue, PAGE_SIZE);
}

STATIC VOID OsGetStackProt(ELFLoadInfo *loadInfo)
{
    LD_ELF_PHDR *elfPhdrTemp = loadInfo->elfPhdr;
    INT32 i;

    for (i = 0; i < loadInfo->elfEhdr.elfPhNum; ++i, ++elfPhdrTemp) {
        if (elfPhdrTemp->type == LD_PT_GNU_STACK) {
            loadInfo->stackProt = OsGetProt(elfPhdrTemp->flags);
        }
    }
}

STATIC INT32 OsSetArgParams(ELFLoadInfo *loadInfo, CHAR *const *argv, CHAR *const *envp)
{
    UINT32 vmFlags;
    INT32 ret;
    status_t status;

#ifdef LOSCFG_ASLR
    loadInfo->randomDevFD = open("/dev/urandom", O_RDONLY);
    if (loadInfo->randomDevFD < 0) {
        PRINT_ERR("%s: open /dev/urandom failed\n", __FUNCTION__);
    }
#endif

    (VOID)OsGetStackProt(loadInfo);
    if (((UINT32)loadInfo->stackProt & (PROT_READ | PROT_WRITE)) != (PROT_READ | PROT_WRITE)) {
        return -ENOEXEC;
    }
    loadInfo->stackTopMax = USER_STACK_TOP_MAX - OsGetRndOffset(loadInfo);
    loadInfo->stackBase = loadInfo->stackTopMax - USER_STACK_SIZE;
    loadInfo->stackSize = USER_STACK_SIZE;
    loadInfo->stackParamBase = loadInfo->stackTopMax - USER_PARAM_BYTE_MAX;
    vmFlags = OsCvtProtFlagsToRegionFlags(loadInfo->stackProt, 0);
    vmFlags |= VM_MAP_REGION_FLAG_STACK;
    status = LOS_UserSpaceVmAlloc((VOID *)loadInfo->newSpace, USER_PARAM_BYTE_MAX,
                                  (VOID **)&loadInfo->stackParamBase, 0, vmFlags);
    if (status != LOS_OK) {
        PRINT_ERR("%s[%d], Failed to create user stack! status: %d\n", __FUNCTION__, __LINE__, status);
        return -ENOMEM;
    }
    loadInfo->topOfMem = loadInfo->stackTopMax - sizeof(UINTPTR);

    loadInfo->argc = OsGetParamNum(argv);
    loadInfo->envc = OsGetParamNum(envp);
    ret = OsCopyParams(loadInfo, 1, (CHAR *const *)&loadInfo->fileName);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d], Failed to copy filename to user stack!\n", __FUNCTION__, __LINE__);
        return ret;
    }
    loadInfo->execName = (CHAR *)loadInfo->topOfMem;

    ret = OsCopyParams(loadInfo, loadInfo->envc, envp);
    if (ret != LOS_OK) {
        return ret;
    }
    ret = OsCopyParams(loadInfo, loadInfo->argc, argv);
    if (ret != LOS_OK) {
        return ret;
    }

    return LOS_OK;
}

STATIC INT32 OsPutParamToStack(ELFLoadInfo *loadInfo, const UINTPTR *auxVecInfo, INT32 vecIndex)
{
    UINTPTR argStart = loadInfo->topOfMem;
    UINTPTR *topMem = (UINTPTR *)ROUNDDOWN(loadInfo->topOfMem, sizeof(UINTPTR));
    UINTPTR *argsPtr = NULL;
    UINTPTR stackBase;
    INT32 items = (loadInfo->argc + 1) + (loadInfo->envc + 1) + 1;
    size_t size;
    INT32 stackFlags;

    loadInfo->topOfMem = ROUNDDOWN((UINTPTR)(topMem - vecIndex - items), STACK_ALIGN_SIZE);
    argsPtr = (UINTPTR *)loadInfo->topOfMem;
    loadInfo->stackTop = (UINTPTR)argsPtr;

    if ((loadInfo->stackTopMax - loadInfo->stackTop) > USER_PARAM_BYTE_MAX) {
        return -E2BIG;
    }

    if (OsPutUserArg(loadInfo->argc, argsPtr)) {
        PRINT_ERR("%s[%d], Failed to put argc to user stack!\n", __FUNCTION__, __LINE__);
        return -EFAULT;
    }

    argsPtr++;

    if ((OsPutUserArgv(&argStart, &argsPtr, loadInfo->argc) != LOS_OK) ||
        (OsPutUserArgv(&argStart, &argsPtr, loadInfo->envc) != LOS_OK)) {
        PRINT_ERR("%s[%d], Failed to put argv or envp to user stack!\n", __FUNCTION__, __LINE__);
        return -EFAULT;
    }

    size = LOS_ArchCopyToUser(argsPtr, auxVecInfo, vecIndex * sizeof(UINTPTR));
    if (size != 0) {
        PRINT_ERR("%s[%d], Failed to copy strings! Bytes not copied: %d\n", __FUNCTION__, __LINE__, size);
        return -EFAULT;
    }

    if ((loadInfo->stackSize - USER_PARAM_BYTE_MAX) > 0) {
        /* mmap an external region for user stack */
        stackFlags = MAP_PRIVATE | MAP_FIXED | MAP_ANONYMOUS;
        stackBase = (UINTPTR)LOS_MMap(loadInfo->stackBase, (loadInfo->stackSize - USER_PARAM_BYTE_MAX),
                                      loadInfo->stackProt, stackFlags, -1, 0);
        if (!LOS_IsUserAddress((VADDR_T)stackBase)) {
            PRINT_ERR("%s[%d], Failed to map user stack\n", __FUNCTION__, __LINE__);
            return -ENOMEM;
        }
    }

    return LOS_OK;
}

STATIC INT32 OsMakeArgsStack(ELFLoadInfo *loadInfo, UINTPTR interpMapBase)
{
    UINTPTR auxVector[AUX_VECTOR_SIZE] = { 0 };
    UINTPTR *auxVecInfo = (UINTPTR *)auxVector;
    INT32 vecIndex = 0;
    INT32 ret;
#ifdef LOSCFG_KERNEL_VDSO
    vaddr_t vdsoLoadAddr;
#endif

    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_PHDR,   loadInfo->loadAddr + loadInfo->elfEhdr.elfPhoff);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_PHENT,  sizeof(LD_ELF_PHDR));
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_PHNUM,  loadInfo->elfEhdr.elfPhNum);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_PAGESZ, PAGE_SIZE);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_BASE,   interpMapBase);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_FLAGS,  0);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_ENTRY,  loadInfo->elfEhdr.elfEntry);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_UID,    0);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_EUID,   0);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_GID,    0);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_EGID,   0);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_HWCAP,  0);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_CLKTCK, 0);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_SECURE, 0);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_RANDOM, 0);
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_EXECFN, (UINTPTR)loadInfo->execName);

#ifdef LOSCFG_KERNEL_VDSO
    vdsoLoadAddr = OsLoadVdso(OsCurrProcessGet());
    if (vdsoLoadAddr != 0) {
        AUX_VEC_ENTRY(auxVector, vecIndex, AUX_SYSINFO_EHDR, vdsoLoadAddr);
    }
#endif
    AUX_VEC_ENTRY(auxVector, vecIndex, AUX_NULL,   0);

    ret = OsPutParamToStack(loadInfo, auxVecInfo, vecIndex);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d], Failed to put param to user stack\n", __FUNCTION__, __LINE__);
        return ret;
    }

    return LOS_OK;
}

STATIC INT32 OsLoadELFSegment(ELFLoadInfo *loadInfo)
{
    LD_ELF_PHDR *elfPhdrTemp = loadInfo->elfPhdr;
    UINTPTR loadBase = 0;
    UINTPTR interpMapBase = 0;
    UINT32 mapSize = 0;
    INT32 ret;
    loadInfo->loadAddr = 0;

    if (loadInfo->elfEhdr.elfType == LD_ET_DYN) {
        loadBase = EXEC_MMAP_BASE + OsGetRndOffset(loadInfo);
        mapSize = OsGetAllocSize(elfPhdrTemp, loadInfo->elfEhdr.elfPhNum);
        if (mapSize == 0) {
            PRINT_ERR("%s[%d], Failed to get allocation size of file: %s!\n", __FUNCTION__, __LINE__,
                      loadInfo->fileName);
            return -EINVAL;
        }
    }

    ret = OsMmapELFFile(loadInfo->execFD, loadInfo->elfPhdr, &loadInfo->elfEhdr, &loadInfo->loadAddr, mapSize,
                        &loadBase);
    if (ret != LOS_OK) {
        PRINT_ERR("%s[%d]\n", __FUNCTION__, __LINE__);
        return ret;
    }

    if (loadInfo->interpFD != INVALID_FD) {
        ret = OsLoadInterpBinary(loadInfo, &interpMapBase);
        if (ret != LOS_OK) {
            return ret;
        }

        loadInfo->elfEntry = loadInfo->interpELFEhdr.elfEntry + interpMapBase;
        loadInfo->elfEhdr.elfEntry = loadInfo->elfEhdr.elfEntry + loadBase;
    } else {
        loadInfo->elfEntry = loadInfo->elfEhdr.elfEntry;
    }

    ret = OsMakeArgsStack(loadInfo, interpMapBase);
    if (ret != LOS_OK) {
        return ret;
    }
    if (!LOS_IsUserAddress((VADDR_T)loadInfo->stackTop)) {
        PRINT_ERR("%s[%d], StackTop is out of limit!\n", __FUNCTION__, __LINE__);
        return -EINVAL;
    }

    return LOS_OK;
}

STATIC VOID OsFlushAspace(ELFLoadInfo *loadInfo)
{
    LosProcessCB *processCB = OsCurrProcessGet();

    OsExecDestroyTaskGroup();

    loadInfo->oldSpace = processCB->vmSpace;
    processCB->vmSpace = loadInfo->newSpace;
    processCB->vmSpace->heapBase += OsGetRndOffset(loadInfo);
    processCB->vmSpace->heapNow = processCB->vmSpace->heapBase;
    processCB->vmSpace->mapBase += OsGetRndOffset(loadInfo);
    LOS_ArchMmuContextSwitch(&OsCurrProcessGet()->vmSpace->archMmu);
}

STATIC VOID OsDeInitLoadInfo(ELFLoadInfo *loadInfo)
{
#ifdef LOSCFG_ASLR
    (VOID)close(loadInfo->randomDevFD);
#endif

    if (loadInfo->elfPhdr != NULL) {
        (VOID)LOS_MemFree(m_aucSysMem0, loadInfo->elfPhdr);
    }

    if (loadInfo->interpELFPhdr != NULL) {
        (VOID)LOS_MemFree(m_aucSysMem0, loadInfo->interpELFPhdr);
    }
}

STATIC VOID OsDeInitFiles(ELFLoadInfo *loadInfo)
{
    if (loadInfo->execFD != INVALID_FD) {
        (VOID)close(loadInfo->execFD);
    }

    if (loadInfo->interpFD != INVALID_FD) {
        (VOID)close(loadInfo->interpFD);
    }
#ifdef LOSCFG_FS_VFS
    delete_files_snapshot((struct files_struct *)loadInfo->oldFiles);
#endif
}

INT32 OsLoadELFFile(ELFLoadInfo *loadInfo)
{
    INT32 ret;

    ret = OsELFLoadInit(loadInfo->fileName, loadInfo);
    if (ret != LOS_OK) {
        goto OUT;
    }

    ret = OsLoadProgramHdrs(loadInfo);
    if (ret != LOS_OK) {
        goto OUT;
    }

    ret = OsReadInterpInfo(loadInfo);
    if (ret != LOS_OK) {
        goto OUT;
    }

    ret = OsSetArgParams(loadInfo, loadInfo->argv, loadInfo->envp);
    if (ret != LOS_OK) {
        goto OUT;
    }

    (VOID)OsFlushAspace(loadInfo);

    ret = OsLoadELFSegment(loadInfo);
    if (ret != LOS_OK) {
        OsCurrProcessGet()->vmSpace = loadInfo->oldSpace;
        LOS_ArchMmuContextSwitch(&OsCurrProcessGet()->vmSpace->archMmu);
        goto OUT;
    }

    (VOID)OsDeInitLoadInfo(loadInfo);

    return LOS_OK;

OUT:
    OsDeInitFiles(loadInfo);
    (VOID)LOS_VmSpaceFree(loadInfo->newSpace);
    (VOID)OsDeInitLoadInfo(loadInfo);
    return ret;
}
