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

#include "ffconf.h"
#include "virpartff.h"
#include "string.h"
#include "diskio.h"

#ifdef LOSCFG_FS_FAT_VIRTUAL_PARTITION

#if FF_USE_LFN == 0 /* Non-LFN configuration */
#define DEF_NAMBUF
#define INIT_NAMBUF(fs)
#define FREE_NAMBUF()

#else /* LFN configuration */
#if (FF_MAX_LFN < 12) || (FF_MAX_LFN > 255)
#error Wrong _MAX_LFN value
#endif

#if FF_USE_LFN == 1 /* LFN enabled with static working buffer */
static WCHAR g_lfnBuf[FF_MAX_LFN + 1]; /* LFN enabled with static working buffer */
#define DEF_NAMBUF
#define INIT_NAMBUF(fs)
#define FREE_NAMBUF()

#elif FF_USE_LFN == 2 /* LFN enabled with dynamic working buffer on the stack */
#define DEF_NAMBUF      WCHAR lbuf[FF_MAX_LFN + 1];
#define INIT_NAMBUF(fs) { (fs)->lfnbuf = lbuf; }
#define FREE_NAMBUF()

#elif FF_USE_LFN == 3 /* LFN enabled with dynamic working buffer on the heap */
#define DEF_NAMBUF      WCHAR *lfn;
#define INIT_NAMBUF(fs) { lfn = ff_memalloc((FF_MAX_LFN + 1) * 2); if (!lfn) LEAVE_FF(fs, FR_NOT_ENOUGH_CORE); (fs)->lfnbuf = lfn; }
#define FREE_NAMBUF()   ff_memfree(lfn)

#else
#error Wrong FF_USE_LFN setting

#endif
#endif /* else FF_USE_LFN == 0 */


#if FF_FS_REENTRANT
#if FF_USE_LFN == 1
#error Static LFN work area cannot be used at thread-safe configuration
#endif
#define ENTER_FF(fs)        do { if (!lock_fs(fs)) return FR_TIMEOUT; } while (0)
#define LEAVE_FF(fs, res)   do { unlock_fs(fs, res); return res; } while (0)
#else
#define ENTER_FF(fs)
#define LEAVE_FF(fs, res) return (res)
#endif

extern FATFS *FatFs[FF_VOLUMES];

/*
* follow_virentry:
* Compare the top segment with the virtual partition entry and replace it to its CHILD FATFS
*
* Acceptable return vaule:
* - FR_OK      : The top segment matches one of the virtual partition entries, and the FATFS
*              has been replaced to the corresponding FATFS.
* - FR_DENIED  : The top segment does not matched any of the virtual partition entries, and
*              the FATFS has kept as it is. Or the virtual partition feature has been
*              switched down by any reason.
* - FR_INT_ERR : Assertion error
*/
FRESULT follow_virentry(FFOBJID *obj, const TCHAR *path)
{
TCHAR keyword[FF_MAX_LFN + 1] = {0};
FATFS *fs = obj->fs;
INT len;
UINT i;

(void)memset_s(keyword, sizeof(keyword), 0, sizeof(keyword));
/* Search and copy the first segment in path */
for (len = 0; *path != '/' && *path != '\\' && *path != '\0' && len < FF_MAX_LFN; path++, len++) {
keyword[len] = *path;
}

if (len == 0 || len > _MAX_ENTRYLENGTH) {
return FR_DENIED;
}

/*
* Compare the segment does match one for virtual partitions' entry or not,
* replace the FATFS if the result is positive
*/
for (i = 0; i < fs->vir_amount; i++) {
if (!CHILDFS(fs, i)) {
    return FR_INT_ERR;
}
if (memcmp((CHILDFS(fs, i))->namelabel, keyword, _MAX_ENTRYLENGTH + 1) == 0) {
    obj->fs = CHILDFS(fs, i);
    return FR_OK;
}
}

return FR_DENIED;
}

FRESULT f_checkname(const TCHAR *path)
{
FRESULT res;
DIR dj;
FATFS fs;
TCHAR *label = (TCHAR *)path;
DEF_NAMBUF

(void)memset_s(&fs, sizeof(fs), 0, sizeof(fs));
dj.obj.fs = &fs;
INIT_NAMBUF(&fs);
res = create_name(&dj, &path);
/* the last byte of file name can't be a space */
if (res == FR_OK && dj.fn[11] == 0x20) {
res = FR_INVALID_NAME;
return res;
}

FREE_NAMBUF();

for (; *label != '\0'; label++) {
if (label - path > _MAX_ENTRYLENGTH) {
    res = FR_INVALID_NAME;
    return res;
}
if (*label == '/' || *label == '\\') {
    res = FR_INVALID_NAME;
    return res;
}
}
return res;
}

FATFS *f_getfatfs(int vol)
{
FATFS *fs = NULL;
if (vol < 0 || vol >= FF_VOLUMES) {
fs = NULL;
} else {
fs = FatFs[vol];
}
return fs;
}

static FRESULT FatfsCheckBoundParam(FATFS *fs, DWORD clust)
{
if (fs->st_clst <= 2 || (fs->st_clst + fs->ct_clst) > fs->n_fatent) {
return FR_INT_ERR;
}
if (clust < 2 || clust > fs->n_fatent) {
return FR_INT_ERR;
}
if (clust >= (fs->st_clst + fs->ct_clst) || clust < fs->st_clst) {
return FR_CHAIN_ERR;
}

return FR_OK;
}

/*
* check_boundary:
* Check the chain occupied more than one virtual partition or not start at the var 'clust'
*
* Acceptable Return Value:
* - FR_OK          : The chain occupied only one virtual parition
* - FR_CHAIN_ERR   : The chain occupied more than one virtual parition
*/
FRESULT f_boundary(FATFS *fs, DWORD clust)
{
FFOBJID obj;
FRESULT res;
obj.fs = fs;
if (fs == NULL) {
return FR_INT_ERR;
}
if (fs->fs_type != FS_FAT32) {
return FR_INVAILD_FATFS;
}
ENTER_FF(fs);

res = FatfsCheckBoundParam(fs, clust);
if (res != FR_OK) {
LEAVE_FF(fs, res);
}
for (; ;) {
clust = get_fat(&obj, clust);
if (clust == 0xFFFFFFFF) {
    LEAVE_FF(fs, FR_DISK_ERR);
}
if (clust == 0x0FFFFFFF) {
    break;
}
if (clust < 2 || clust >= fs->n_fatent) {
    LEAVE_FF(fs, FR_INT_ERR);
}
if (clust >= (fs->st_clst + fs->ct_clst) || clust < fs->st_clst) {
    LEAVE_FF(fs, FR_CHAIN_ERR);
}
}

LEAVE_FF(fs, FR_OK);
}

/*
* f_unregvirfs:
* Uninitialized the CHILD FATFS object
*
* Acceptable Return Value:
* - FR_OK : Successfully initialized the CHILD FATFS object.
*/
FRESULT f_disvirfs(FATFS *fs)
{
if (ISCHILD(fs)) {
return FR_INVAILD_FATFS;
}

if (fs->vir_amount > _MAX_VIRVOLUMES) {
return FR_INT_ERR;
}

ENTER_FF(fs);

(void)f_unregvirfs(fs);
LEAVE_FF(fs, FR_OK);
}

FRESULT f_unregvirfs(FATFS *fs)
{
UINT i;

if (fs == NULL || ISCHILD(fs)) {
return FR_INVAILD_FATFS;
}

fs->vir_avail = FS_VIRDISABLE;
/* PARENT FATFS has linked to CHILD FATFS already */
if (fs->child_fs != NULL) {
/* Followed the CHILD FATFS and free the memory */
for (i = 0; i < fs->vir_amount; i++) {
    if (CHILDFS(fs, i) != NULL) {
        ff_memfree(CHILDFS(fs, i));
    }
}
/* Free the 'child_fs' feild */
ff_memfree(fs->child_fs);
fs->child_fs = NULL;
fs->vir_amount = 0xFFFFFFFF;
}

return FR_OK;
}

static void FatfsSetParentFs(FATFS *pfs, FATFS *fs)
{
pfs->fs_type = fs->fs_type; /* Copy the feild info from PARENT FATFS object */
pfs->pdrv = fs->pdrv;
pfs->n_fats = fs->n_fats;
pfs->id = fs->id;
pfs->n_rootdir = fs->n_rootdir;
pfs->csize = fs->csize;
#if FF_MAX_SS != FF_MIN_SS
pfs->ssize = fs->ssize;
#endif
pfs->sobj = fs->sobj;

#if FF_FS_RPATH != 0
pfs->cdir = 0;
#endif
pfs->n_fatent = fs->n_fatent;
pfs->fsize = fs->fsize;
pfs->volbase = fs->volbase;
pfs->fatbase = fs->fatbase;
pfs->dirbase = fs->dirbase;
pfs->database = fs->database;
pfs->last_clst = 0xFFFFFFFF; /* Mark the 'last_clst' and 'free_clst' in CHILD FATFS is not been updated for now */
pfs->free_clst = 0xFFFFFFFF;
pfs->st_clst = 0xFFFFFFFF; /* Mark the 'st_clst' and 'ct_clst' in CHILD FATFS is not been update for now. */
pfs->ct_clst = 0xFFFFFFFF;
pfs->vir_flag = FS_CHILD; /* Mark the FATFS object is a CHILD */
pfs->vir_avail = FS_VIRENABLE; /* Mark the CHILD object is enable for now */
pfs->parent_fs = (void *)fs; /* Link to the PARENT object */
pfs->child_fs = (void *)NULL; /* Link the unrelated feild to NULL */
}

/*
* f_regvirfs:
* Initialized the CHILD FATFS object
*
* Acceptable Return Value:
* - FR_OK : Successfully initialized the CHILD FATFS object.
*
* Others Return Value:
* - FR_INVAILD_FATFS       :   The FATFS object has error or the info in it has been occuried
* - FR_DENIED              :   The virtual partition feature has been shut down by switcher
* - FR_DISK_ERR            :   A disk error happened
* - FR_NOT_ENOUGH_CORE     :   Not enough memory for allocate space for CHILD FATFS
* - FR_INVALID_PARAMETER   :   There is a invaild value in current setting
*/
FRESULT f_regvirfs(FATFS *fs)
{
UINT i;
FATFS *pfs = NULL;

if (fs == NULL || ISCHILD(fs)) {
return FR_INVAILD_FATFS;
}

if (fs->vir_amount > _MAX_VIRVOLUMES) {
return FR_INT_ERR;
}

fs->parent_fs = (void *)fs; /* Relink to itself */
/* Mark the FATFS object is PARENT */
fs->st_clst = 0xFFFFFFFF;
fs->ct_clst = 0xFFFFFFFF;
/* Allocate a space for linking to the child FATFS */
fs->child_fs = (void **)ff_memalloc(fs->vir_amount * sizeof(void *));
if (fs->child_fs == NULL) {
return FR_NOT_ENOUGH_CORE;
}
fs->vir_avail = FS_VIRENABLE; /* Mark the PARENT object is enable for now */

/* Set the CHILD object field */
for (i = 0; i < fs->vir_amount; i++) {
pfs = ff_memalloc(sizeof(FATFS)); /* Allocate a memeory for current child FATFS object */
if (pfs == NULL) { /* If allocate failed, must call 'f_unregvirfs' to free the previous FATFS object memory */
    goto ERROUT;
}
FatfsSetParentFs(pfs, fs);
*(fs->child_fs + i) = (void *)pfs;
}

return FR_OK;
ERROUT:
while (i > 0) {
--i;
ff_memfree(*(fs->child_fs + i));
}
ff_memfree(fs->child_fs);
fs->child_fs = NULL;

return FR_NOT_ENOUGH_CORE;
}

static FRESULT FatfsCheckScanFatParam(FATFS *fs)
{
if (fs == NULL) {
return FR_INVAILD_FATFS;
}

if (ISNORMAL(fs)) {
return FR_DENIED;
}

if (fs->fs_type != FS_FAT32 || ISPARENT(fs)) {
return FR_INVAILD_FATFS;
}

if (fs->st_clst < 3 || fs->st_clst >= fs->n_fatent) {
return FR_INVAILD_FATFS;
}

if (fs->ct_clst == 0 || fs->ct_clst > (fs->n_fatent - 3)) {
return FR_INVAILD_FATFS;
}

if ((fs->st_clst + fs->ct_clst) > fs->n_fatent || (fs->st_clst + fs->ct_clst) < 3) {
return FR_INVAILD_FATFS;
}

return FR_OK;
}

/*
* f_scanfat:
* Scan the FAT inside the boundary of CHILD FATFS limit, and update the free cluster and last cluster
*
* Acceptable Return Value:
* - FR_OK : Successfully scaned the FAT and update field.
*
* Others Return Value:
* - FR_INVAILD_FATFS   :   The FATFS object has error or the info in it has been occuried
* - FR_DENIED          :   The virtual partition feature has been shut down by switcher
* - FR_DISK_ERR        :   A disk error happened
*/
FRESULT f_scanfat(FATFS *fs)
{
FRESULT res;
DWORD clst;
DWORD link;
FFOBJID obj;

res = FatfsCheckScanFatParam(fs);
if (res != FR_OK) {
return res;
}

ENTER_FF(fs);
res = FR_OK;
obj.fs = fs;

fs->free_clst = fs->ct_clst;
for (clst = fs->st_clst; clst < fs->st_clst + fs->ct_clst; clst++) {
link = get_fat(&obj, clst);
if (link == 0xFFFFFFFF) {
    LEAVE_FF(fs, FR_DISK_ERR);
}
if (link == 0) {
    continue;
}
fs->free_clst--;
}
fs->last_clst = fs->st_clst - 1;

LEAVE_FF(fs, res);
}

static FRESULT FatfsCheckStart(BYTE *work, FATFS *fs, BYTE vol)
{
DWORD startBaseSect, countBaseSect;

countBaseSect = LD2PC(vol); /* Volume Base Sectors Count */
startBaseSect = LD2PS(vol); /* Volume Base Start Sector */

/* Check ASCII for Keyword "LITE" */
if (ld_dword(work + VR_VertifyString) != 0x4C495445) {
return FR_NOVIRPART;
}
/* Check whether filesystem has been changed or not */
if (work[VR_PartitionFSType] != fs->fs_type) {
return FR_MODIFIED;
}
/* Check whether volume base sector has benn changed or not */
if (ld_dword(work + VR_PartitionStSec) != startBaseSect) {
return FR_MODIFIED;
}
/* Check whether volume base size hase been changed or not */
if (ld_dword(work + VR_PartitionCtSec) != countBaseSect) {
return FR_MODIFIED;
}
/* Check whether volume cluster size has been changed or not */
if (ld_word(work + VR_PartitionClstSz) != fs->csize) {
return FR_MODIFIED;
}
/* Check whether volume start cluster is cluster #3 or not */
if (ld_dword(work + VR_PartitionCtClst) != fs->n_fatent) {
return FR_MODIFIED;
}
/* Check whether virtual partition overlimit */
if (work[VR_PartitionCnt] > _MAX_VIRVOLUMES) {
return FR_MODIFIED;
}

return FR_OK;
}

static FRESULT FatfsCheckPercent(FATFS *fs, WORD i)
{
if ((CHILDFS(fs, i))->st_clst + (CHILDFS(fs, i))->ct_clst < fs->n_fatent) {
fs->st_clst = (CHILDFS(fs, i))->st_clst + (CHILDFS(fs, i))->ct_clst;
fs->ct_clst = fs->n_fatent - ((CHILDFS(fs, i))->st_clst + (CHILDFS(fs, i))->ct_clst);
} else if ((CHILDFS(fs, i))->st_clst + (CHILDFS(fs, i))->ct_clst == fs->n_fatent) {
fs->st_clst = 0xFFFFFFFF;
fs->ct_clst = 0xFFFFFFFF;
} else {
(void)f_unregvirfs(fs);
return FR_MODIFIED;
}

return FR_OK;
}

static FRESULT FatfsCheckPartClst(FATFS *fs, WORD i)
{
if (i == 0) {
/* First virtual partition must start at cluster #3 */
if ((CHILDFS(fs, i))->st_clst != 3) {
    (void)f_unregvirfs(fs);
    return FR_MODIFIED;
}
} else {
/* Check whether the current virtual partition is closely next to the previous virtual partition */
if ((CHILDFS(fs, i))->st_clst != (CHILDFS(fs, (i - 1))->st_clst + CHILDFS(fs, (i - 1))->ct_clst)) {
    (void)f_unregvirfs(fs);
    return FR_MODIFIED;
}
}

return FR_OK;
}

static void FatfsSetChildClst(BYTE *work, FATFS *fs, WORD i)
{
(CHILDFS(fs, i))->st_clst = ld_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_StartClust);
(CHILDFS(fs, i))->ct_clst = ld_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_CountClust);
}

/*
* f_ckvtlpt :
* Check the external SD virtual paritition sectors and read configure from it
*
* Acceptable Return Value:
* - FR_OK          : The external SD configure is complete, all info has been set to the
*                  each CHILD FATFS
* - FR_NOT_MATCHED : The virtual partition's configure does not matched as current setting
* - FR_MODIFIED    : The virtual partition's configure has been destoried partly or completely
* - FR_NOVIRPART   : The external SD has not been apllied as virtual partition yet
*
* Others Return Value:
* - FR_INVAILD_FATFS : The FATFS object has error or the info in it has been occuried
* - FR_DENIED          : The virtual partition feature has been shut down by switcher
* - FR_INVALID_DRIVE   : The drive index is error
* - FR_DISK_ERR        : A Disk error happend
*/
FRESULT f_checkvirpart(FATFS *fs, const TCHAR *path, BYTE vol)
{
FRESULT res;
WORD i;
DWORD virSect;
DWORD tmp;
BYTE pdrv;
BYTE *work = NULL;
CHAR label[_MAX_ENTRYLENGTH + 1];
DWORD *labelTmp = NULL; /* to clear the compilation warning */

if (fs == NULL || (disk_status(fs->pdrv) & STA_NOINIT)) {
return FR_INVAILD_FATFS; /* The object is invalid */
}

/* Lock the filesystem object */
res = find_volume(&path, &fs, FA_WRITE); /* Update the filesystem info to the parent fs */
if (res != FR_OK) {
LEAVE_FF(fs, res);
}

if (ISCHILD(fs)) {
LEAVE_FF(fs, FR_INT_ERR);
}
/* Data will be save at the last reserve sector ,which is the front one of the fat base sector */
virSect = fs->fatbase - 1;

pdrv = LD2PD(vol); /* Driver index */

work = (BYTE *)ff_memalloc(SS(fs));
if (work == NULL) {
LEAVE_FF(fs, FR_NOT_ENOUGH_CORE);
}
/* Check and vertify partition information */
if (disk_read(pdrv, work, virSect, 1) != RES_OK) {
res = FR_DISK_ERR;
goto EXIT;
} /* Load VBR */

res = FatfsCheckStart(work, fs, vol);
if (res != FR_OK) {
goto EXIT;
}
/* Check the virtual parition amount if matched current setting or not */
fs->vir_amount = work[VR_PartitionCnt];
res = f_regvirfs(fs);
if (res != FR_OK) {
goto EXIT;
}

for (i = 0; i < _MAX_VIRVOLUMES; i++) {
if (i < work[VR_PartitionCnt]) {
    if (work[VR_PARTITION + i * VR_ITEMSIZE + VR_Available] != 0x80) {
        (void)f_unregvirfs(fs);
        res = FR_MODIFIED;
        goto EXIT;
    }
} else {
    if (work[VR_PARTITION + i * VR_ITEMSIZE + VR_Available] != 0x00) {
        (void)f_unregvirfs(fs);
        res = FR_MODIFIED;
        goto EXIT;
    }
    break;
}

(void)memset_s(label, sizeof(label), 0, sizeof(label));

tmp = ld_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_Entry + 0);
labelTmp = (DWORD *)label;
*labelTmp = tmp;
tmp = ld_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_Entry + 4);
*((DWORD *)(label + 4)) = tmp;
tmp = ld_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_Entry + 8);
*((DWORD *)(label + 8)) = tmp;
tmp = ld_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_Entry + 12);
*((DWORD *)(label + 12)) = tmp;

if (f_checkname(label) != FR_OK) {
    (void)f_unregvirfs(fs);
    res = FR_MODIFIED;
    goto EXIT;
}
(void)memcpy_s((CHILDFS(fs, i))->namelabel, _MAX_ENTRYLENGTH + 1, label, _MAX_ENTRYLENGTH + 1);

FatfsSetChildClst(work, fs, i);

/* External SD setting has overlimit the whole partition cluster amount */
if ((QWORD)(CHILDFS(fs, i))->st_clst + (QWORD)((CHILDFS(fs, i))->ct_clst) > (QWORD)fs->n_fatent) {
    (void)f_unregvirfs(fs);
    res = FR_MODIFIED;
    goto EXIT;
}

res = FatfsCheckPartClst(fs, i);
if (res != FR_OK) {
    goto EXIT;
}
if (i == (work[VR_PartitionCnt] - 1)) {
    /*
     * If the external SD virtual partition percent exceeds the error tolerance based on current virtual
     * partition percent setting
     */
    res = FatfsCheckPercent(fs, i);
    if (res != FR_OK) {
        goto EXIT;
    }
}
}
EXIT:
ff_memfree(work);
LEAVE_FF(fs, res);
}

static void FatfsClacPartInfo(FATFS *fs, DOUBLE virpartper, UINT i)
{
if (i == 0) {
(CHILDFS(fs, i))->st_clst = 3;
(CHILDFS(fs, i))->ct_clst = (DWORD)((fs->n_fatent - 3) *
                                    g_fatVirPart.virtualinfo.virpartpercent[i]);

fs->st_clst = (CHILDFS(fs, i))->st_clst + (CHILDFS(fs, i))->ct_clst;
fs->ct_clst = fs->n_fatent - fs->st_clst;
} else if (i != (fs->vir_amount - 1)) {
(CHILDFS(fs, i))->st_clst = (CHILDFS(fs, (i - 1)))->st_clst + (CHILDFS(fs, (i - 1)))->ct_clst;
(CHILDFS(fs, i))->ct_clst = (DWORD)((fs->n_fatent - 3) *
                                     g_fatVirPart.virtualinfo.virpartpercent[i]);
} else {
(CHILDFS(fs, i))->st_clst = (CHILDFS(fs, (i - 1)))->st_clst + (CHILDFS(fs, (i - 1)))->ct_clst;
if (virpartper <= (1 + _FLOAT_ACC) && virpartper >= (1 - _FLOAT_ACC)) {
    (CHILDFS(fs, i))->ct_clst = fs->n_fatent - (CHILDFS(fs, i))->st_clst;
    fs->st_clst = 0xFFFFFFFF;
    fs->ct_clst = 0xFFFFFFFF;
} else {
    (CHILDFS(fs, i))->ct_clst = (DWORD)((fs->n_fatent - 3) *
                                         g_fatVirPart.virtualinfo.virpartpercent[i]);
    fs->st_clst = (CHILDFS(fs, i))->st_clst + (CHILDFS(fs, i))->ct_clst;
    fs->ct_clst = fs->n_fatent - fs->st_clst;
}
}
}

/*
* f_mkvtlpt:
* Apply the current virtual partition's setting to external SD card and to the CHILD FATFS
*
* Acceptable Return Value:
* - FR_OK : Successfully applied current setting to external SD card and
*              CHILD FATFS
*
* Others Return Value  :
* - FR_INVAILD_FATFS   : The FATFS object has error or the info in it has been occuried
* - FR_DENIED          : The virtual partition feature has been shut down by switcher
* - FR_INVALID_DRIVE   : The drive index is error
* - FR_DISK_ERR        : A Disk error happend
*/
FRESULT f_makevirpart(FATFS *fs, const TCHAR *path, BYTE vol)
{
FRESULT res;
DWORD virSect;
DWORD startBaseSect, countBaseSect;
DWORD tmp;
CHAR label[_MAX_ENTRYLENGTH + 1];
DWORD *labelTmp = NULL; /* to clear the compilation warning */
UINT i;
BYTE pdrv;
BYTE *work = NULL;
DOUBLE virpartper = 0.0;

if (fs == NULL || (disk_status(fs->pdrv) & STA_NOINIT)) {
return FR_INVAILD_FATFS; /* The object is invalid */
}

/* Lock the filesystem object */
res = find_volume(&path, &fs, FA_WRITE); /* Update the filesystem info to the parent fs */
if (res != FR_OK) {
LEAVE_FF(fs, res);
}

/* Only available in FAT32 filesystem */
if (ISCHILD(fs)) {
LEAVE_FF(fs, FR_INVAILD_FATFS);
}
/* Data will be save at the last reserve sector,which is the front one of the fat base sector */
virSect = fs->fatbase - 1;
/* Search the fs index, which same as the volume index */
pdrv = LD2PD(vol); /* Driver index */
countBaseSect = LD2PC(vol); /* Volume Base Sectors Count */
startBaseSect = LD2PS(vol); /* Volume Base Start Sector */

fs->vir_amount = g_fatVirPart.virtualinfo.virpartnum;
res = f_regvirfs(fs);
if (res != FR_OK) {
LEAVE_FF(fs, res);
}

work = (BYTE *)ff_memalloc(SS(fs));
if (work == NULL) {
LEAVE_FF(fs, FR_NOT_ENOUGH_CORE);
}
/* Data Cluster is begin from the Cluster #3 to the last cluster */
/* Cluster #0 #1 is for VBR, reserve sectors and fat */
/* Cluster #2 is for root directory */
(void)memset_s(work, SS(fs), 0, SS(fs));

for (i = 0; i < fs->vir_amount; i++) {
/* Copy the Entry label and write to work sector's buffer */
(void)memset_s(label, sizeof(label), 0, sizeof(label));
(void)memcpy_s(label, _MAX_ENTRYLENGTH + 1, g_fatVirPart.virtualinfo.virpartname[i], _MAX_ENTRYLENGTH + 1);
labelTmp = (DWORD *)label;
tmp = *labelTmp;
st_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_Entry + 0, tmp);
tmp = *((DWORD *)(label + 4));
st_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_Entry + 4, tmp);
tmp = *((DWORD *)(label + 8));
st_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_Entry + 8, tmp);
tmp = *((DWORD *)(label + 12));
st_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_Entry + 12, tmp);

virpartper += g_fatVirPart.virtualinfo.virpartpercent[i];

(void)memcpy_s((CHILDFS(fs, i))->namelabel, _MAX_ENTRYLENGTH + 1, g_fatVirPart.virtualinfo.virpartname[i],
               _MAX_ENTRYLENGTH + 1);
FatfsClacPartInfo(fs, virpartper, i);
(CHILDFS(fs, i))->last_clst = (CHILDFS(fs, i))->st_clst - 1;
work[VR_PARTITION + i * VR_ITEMSIZE + VR_Available] = 0x80;
}

/* Set the data to sector */
work[VR_PartitionCnt] = fs->vir_amount;
work[VR_PartitionFSType] = fs->fs_type;
st_dword(work + VR_PartitionStSec, startBaseSect);
st_dword(work + VR_PartitionCtSec, countBaseSect);
st_word(work + VR_PartitionClstSz, fs->csize);
st_dword(work + VR_PartitionCtClst, fs->n_fatent);
for (i = 0; i < fs->vir_amount; i++) {
st_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_StartClust,
         (CHILDFS(fs, i))->st_clst);
st_dword(work + VR_PARTITION + i * VR_ITEMSIZE + VR_CountClust,
         (CHILDFS(fs, i))->ct_clst);
}

/* ASCII for Keyword "LITE" */
st_dword(work + VR_VertifyString, 0x4C495445);

/* Write into the data area */
if (disk_write(pdrv, work, virSect, 1) != RES_OK) {
(void)f_unregvirfs(fs);
res = FR_DISK_ERR;
}

ff_memfree(work);
LEAVE_FF(fs, res);
}

FRESULT f_getvirfree(const TCHAR *path, DWORD *nclst, DWORD *cclst)
{
FATFS *fs = NULL;
FRESULT res;
DWORD clst, link;
DWORD nfree;
UINT i;
DIR dj;

/* Find volume to Update the global FSINFO */
res = find_volume(&path, &fs, 0);
if (res != FR_OK) {
LEAVE_FF(fs, res);
}

/* Following the entry keyword, decide to replace the PARENT FATFS to CHILD FATFS or not */
dj.obj.fs = fs;
if (ISVIRPART(fs)) {
/* Check the virtual partition top directory, and match the virtual fs */
res = follow_virentry(&dj.obj, path);
if (res == FR_INT_ERR) {
    LEAVE_FF(fs, res);
}
if (res == FR_OK) {
    fs = dj.obj.fs;
}
} else {
/* Virtual Partition Feature was off, deny this operation */
LEAVE_FF(fs, FR_DENIED);
}

/* If current FATFS is a CHILD FATFS */
if (ISCHILD(fs)) {
/* If CHILD FATFS' free_clst is invaild, the scan the FAT and update it */
if (fs->free_clst > fs->ct_clst) {
    dj.obj.fs = fs;
    fs->free_clst = fs->ct_clst;
    for (clst = fs->st_clst; clst < fs->st_clst + fs->ct_clst; clst++) {
        link = get_fat(&dj.obj, clst);
        if (link == 0) {
            continue;
        }
        fs->free_clst--;
    }
}
*nclst = fs->free_clst;
*cclst = fs->ct_clst;
LEAVE_FF(fs, FR_OK);
} else {
nfree = 0;
if (fs->ct_clst == 0xFFFFFFFF) {
    LEAVE_FF(fs, FR_DENIED);
}
for (i = 0; i < fs->vir_amount; i++) {
    if (CHILDFS(fs, i)->free_clst > CHILDFS(fs, i)->ct_clst) {
        dj.obj.fs = CHILDFS(fs, i);
        CHILDFS(fs, i)->free_clst = CHILDFS(fs, i)->ct_clst;
        for (clst = CHILDFS(fs, i)->st_clst; clst < CHILDFS(fs, i)->st_clst + CHILDFS(fs, i)->ct_clst; clst++) {
            link = get_fat(&dj.obj, clst);
            if (link == 0) {
                continue;
            }
            CHILDFS(fs, i)->free_clst--;
        }
    }
    nfree += CHILDFS(fs, i)->free_clst;
}
*nclst = fs->free_clst - nfree;
*cclst = fs->ct_clst;
LEAVE_FF(fs, FR_OK);
}
}
#endif
