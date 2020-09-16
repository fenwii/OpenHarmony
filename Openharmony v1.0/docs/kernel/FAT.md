# FAT<a name="ZH-CN_TOPIC_0000001052170495"></a>

## 概述<a name="section17906101815113"></a>

FAT文件系统是File Allocation Table（文件配置表）的简称，FAT文件系统有FAT12、FAT16、FAT32。FAT文件系统将硬盘分为MBR区、DBR区、FAT区、DIR区、DATA区等5个区域。

FAT文件系统支持多种介质，特别在可移动存储介质（U盘、SD卡、移动硬盘等）上广泛使用。可以使嵌入式设备和Windows、Linux等桌面系统保持很好的兼容性，方便用户管理操作文件。

OpenHarmony内核的FAT文件系统具有代码量和资源占用小、可裁切、支持多种物理介质等特性，并且与Windows、Linux等系统保持兼容，支持多设备、多分区识别等功能。

OpenHarmony内核支持硬盘多分区，可以在主分区以及逻辑分区上创建FAT文件系统。同时OpenHarmony内核也可以识别出硬盘上其他类型的文件系统。

## 注意事项<a name="section781233610116"></a>

-   最多支持同时打开的fatfs文件（文件夹）数为512。

-   以可写方式打开一个文件后，未close前再次打开会失败。多次打开同一文件，必须全部使用只读方式。长时间打开一个文件，没有close时数据会丢失，必须close才能保存。

-   FAT文件系统中，单个文件不能大于4G。

-   当有两个SD卡插槽时，卡0和卡1不固定，先插上的为卡0，后插上的为卡1。

-   当多分区功能打开，存在多分区的情况下，卡0注册的设备节点/dev/mmcblk0\(主设备\)和/dev/mmcblk0p0\(次设备\)是同一个设备，禁止对主设备进行操作。

-   FAT文件系统的读写指针没有分离，所以以O\_APPEND（追加写）方式打开文件后，读指针也在文件尾，读文件前需要用户手动置位。

-   FAT文件系统的stat及lstat函数获取出来的文件时间只是文件的修改时间。暂不支持创建时间和最后访问时间。微软FAT协议不支持1980年以前的时间。

-   open打开一个文件，参数有O\_TRUNC时，会将文件中的内容清空。

-   FAT文件系统支持的操作有：open, close, read, write, seek, sync, opendir, closedir, readdir, rewinddir,  readdir\_r, statfs, remove, unlink, mkdir, rmdir, rename, stat, stat64, seek64,  fallocate, fallocate64, truncate,  truncate64,mount, umount。

-   为避免SD卡使用异常和内存泄漏，SD卡使用过程中拔卡，用户必须先关闭正处于打开状态的文件和目录，之后umount挂载节点。

-   在format操作之前，若fat文件系统已挂载，需确保所有目录及文件全部关闭，否则format会失败。

-   FAT支持只读属性挂载：

    -   当mount函数的入参为MS\_RDONLY时，FAT将开启只读属性，所有的带有写入的接口，如write、mkdir、unlink，以及通过非O\_RDONLY属性打开的文件，将均被拒绝，并传出EACCESS错误码（format接口除外）。

    -   当mount函数的入参为MS\_NOSYNC时，FAT不会主动将cache的内容写回存储器件。FAT的如下接口（open、close、 unlink、rename、mkdir、rmdir、truncate）不会自动进行sync操作，速度可以提升，但是需要上层主动调用sync来进行数据同步，否则下电可能会数据丢失。


-   FAT文件系统有定时刷cache功能。在menuconfig中开启LOSCFG\_FS\_FAT\_CACHE\_SYNC\_THREAD选项，打开后系统会创建一个任务刷cache，默认每隔5秒检查cache中脏数据块比例，超过80%时进行sync操作，将cache中的脏数据全部写回磁盘。任务优先级、刷新时间间隔以及脏数据块比例的阈值可分别通过接口LOS\_SetSyncThreadPrio、  LOS\_SetSyncThreadInterval和LOS\_SetDirtyRatioThreshold设置。

-   当前cache的默认大小为16个块，每个块256个扇区。


## 开发指导<a name="section26081559713"></a>

**设备识别**

-   在ffconf.h文件中配置FF\_MULTI\_PARTITION为1，可使用多分区功能。

-   在ffconf.h文件中配置FF\_VOLUMES大于2时，可使用多设备功能。


多设备、多分区功能开启后，系统对于插上的sd卡自动识别，自动注册设备节点如上图所示。mmcblk0和mmcblk1为卡0和卡1，是独立的主设备，mmcblk0p0、mmcblk0p1为卡0的两个分区，可作为分区设备使用。在有分区设备存在的情况下，禁止使用主设备。

可以使用 partinfo命令查看所识别的分区信息。

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

**FAT文件系统的挂载**

运行命令：

```
OHOS # mount /dev/mmcblk0p0 /vs/sd vfat
```

将从串口得到如下回应信息，表明挂载成功。

```
OHOS # mount /dev/mmcblk0p0 /vs/sd vfat
mount ok
```

**FAT文件系统的卸载**

运行命令：

```
OHOS # umount /vs/sd
```

将从串口得到如下回应信息，表明卸载成功。

```
OHOS # umount /vs/sd
umount ok
```

