# FAT<a name="EN-US_TOPIC_0000001052170495"></a>

## Overview<a name="section17906101815113"></a>

There are FAT12, FAT16, and FAT32. A FAT file system divides a hard disk into five areas: MBR, DBR, FAT, DIR, and DATA.

FAT supports multiple media, especially removable storage media \(such as USB flash drives, SD cards, and portable hard disks\). In this way, embedded devices can be better compatible with desktop systems such as Windows and Linux, facilitating file management and operation.

FAT in the OpenHarmony kernel features low code, less resource occupation, tailorability, and multiple physical media support. It is compatible with systems such as Windows and Linux, and provides functions such as identification of multiple devices and partitions.

The OpenHarmony kernel supports multiple partitions on the hard disk. A FAT file system can be created on the primary or logical partition. The OpenHarmony kernel can also identify other types of file systems on the hard disk.

## Important Notes<a name="section781233610116"></a>

-   A maximum of 256 FATFS files or folders that can be opened simultaneously.

-   After a file is opened in writable mode, the file cannot be opened again before it is closed. To open a file for multiple times, the read-only attribute can be used only. If a file is opened for a long time and is not closed, data loss will occur. The file can be saved only after being closed.

-   The size of an individual FAT file cannot be greater than 4 GB.

-   When there are two SD card slots, the first card inserted is card 0, and that inserted later is card 1.

-   When multi-partition is enabled and there are multiple partitions, the device node  **/dev/mmcblk0**  \(primary device\) registered by card 0 and  **/dev/mmcblk0p0**  \(secondary device\) are the same device. In this case, you cannot perform operations on the primary device.

-   The read and write pointers are not separated. Therefore, after a file is opened in  **O\_APPEND**  mode, the read pointer is also at the end of the file. You must manually set the position of the read pointer before reading the file.

-   The file modification time is obtained by the  **stat**  and  **lstat**  functions. The creation time and last access time cannot be obtained. As limited by the FAT protocol, the time before 1980 is not supported.

-   When you use  **open**  with the parameter  **O\_TRUNC**  to open a file, the file content will be cleared.

-   You can perform the following operations on FAT files:  **open**,  **close**,  **read**,  **write**,  **seek**,  **sync**,  **opendir**,  **closedir**,  **readdir**,  **rewinddir**,  **readdir\_r**,  **statfs**,  **remove**,  **unlink**,  **mkdir**,  **rmdir**,  **rename**,  **stat**,  **stat64**,  **seek64**,  **fallocate**,  **fallocate64**,  **truncate**,  **truncate64**,  **mount**, and  **umount**.

-   To prevent SD card exceptions and memory leakage, opened files and directories must be closed and mounted nodes must be unmounted before an SD card is removed.

-   If a FAT file system has been mounted before the  **format**  operation, ensure that all directories and files are closed. Otherwise, the  **format**  operation will fail.

-   FAT supports mounting with the read-only attribute.

    -   When  **MS\_RDONLY**  is carried in the  **mount**  function, the read-only attribute is enabled for the FAT file system. All APIs with the write attribute, such as  **write**,  **mkdir**, and  **unlink**, and files that are opened not by using the attribute  **O\_RDONLY**  are rejected and the error code  **EACCESS**  is thrown.

    -   When  **MS\_NOSYNC**  is carried in the  **mount**  function, FAT does not proactively write the content in the cache back to the storage device. The FAT-related APIs  **open**,  **close**,  **unlink**,  **rename**,  **mkdir**,  **rmdir**, and  **truncate**  do not automatically perform the  **sync**  operation, which improves the operation speed. However, the upper layer must actively invoke the  **sync**  operation to synchronize data. Otherwise, data may be lost after a power outage.


-   The FAT file system supports periodical cache flushing. After  **LOSCFG\_FS\_FAT\_CACHE\_SYNC\_THREAD**  is enabled in  **menuconfig**, the OpenHarmony kernel creates a task to flush the cache. By default, the OpenHarmony kernel checks the percentage of dirty data blocks in the cache every 5 seconds. If the percentage exceeds 80%, the OpenHarmony kernel performs the  **sync**  operation to write all dirty data in the cache back to the disk. The task priority, flush interval, and dirty data block percentage thresholds can be set by calling  **LOS\_SetSyncThreadPrio**,  **LOS\_SetSyncThreadInterval**, and  **LOS\_SetDirtyRatioThreshold**, respectively.

-   The default cache size is 16 blocks, and each block has 256 sectors.


## Development Guidelines<a name="section26081559713"></a>

**Device Identification**

-   Multi-partition is enabled if  **FF\_MULTI\_PARTITION**  in the  **ffconf.h**  file is set to  **1**.

-   Multi-device is enabled if  **FF\_VOLUMES**  in the  **ffconf.h**  file is greater than 2.


When multi-device and multi-partition are enabled, the system automatically identifies an inserted SD card and registers the device node.  **mmcblk0**  \(card 0\) and  **mmcblk1**  \(card 1\) are independent primary devices.  **mmcblk0p0**  and  **mmcblk0p1**  are two partitions of card 0 and can be used as partitions. Do not use the primary device if a partition exists.

You can run the  **partinfo**  command to view information about identified partitions.

```
OHOS # partinfo /dev/mmcblk0p0 
part info :                                                                     
disk id          : 0                                                            
part_id in system: 0                                                            
part no in disk  : 0                                                            
part no in mbr   : 1                                                            
part filesystem  : 0C                                                           
part dev name    : mmcblk0p0                                                    
part sec start   : 8192                                                         
part sec count   : 31108096 
```

**FAT Mounting**

Mount a FAT file system.

```
OHOS # mount /dev/mmcblk0p0 /vs/sd vfat
```

If the following information is displayed, the FAT file system is mounted:

```
OHOS # mount /dev/mmcblk0p0 /vs/sd vfat
mount ok
```

**FAT Unmounting**

Unmount the FAT file system.

```
OHOS # umount /vs/sd
```

If the following information is displayed, the FAT file system is unmounted:

```
OHOS # umount /vs/sd
umount ok
```

