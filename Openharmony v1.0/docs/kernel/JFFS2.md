# JFFS2<a name="ZH-CN_TOPIC_0000001052810482"></a>

## 概述<a name="section01261544730"></a>

JFFS2是Journalling Flash File  System Version 2（日志文件系统）的缩写，是MTD设备上实现的日志型文件系统。JFFS2主要应用于NOR FLASH，其特点是：可读写、支持数据压缩、提供了崩溃/掉电安全保护、提供“写平衡”支持等。

闪存与磁盘介质有许多差异，因此直接将磁盘文件系统运行在闪存上存在性能和安全性上的不足。为解决这一问题，需要实现一个特别针对闪存的文件系统，JFFS2就是这样一种文件系统。

OpenHarmony内核的JFFS2主要应用于对NOR Flash闪存的文件管理，并且支持多分区。

## 注意事项<a name="section94343420"></a>

-   目前JFFS2文件系统用于NOR Flash，最终调用NOR Flash驱动接口，因此使用JFFS2文件系统之前要确保硬件上有NOR Flash，且驱动初始化成功（spinor\_init\(\)返回0）。

-   系统会自动对起始地址和分区大小根据block大小进行对齐操作。有效的分区号为0\~19。

-   目前支持mkfs.jffs2工具，用户可根据自己实际情况修改参数值，其他用法用户可自行搜索查看。

-   open打开一个文件，参数有O\_TRUNC时，会将文件中的内容清空。

-   目前JFFS2文件系统支持的操作有：open, close, read, write, seek, opendir, closedir, readdir, readdir\_r, rewinddir,  statfs, sync, remove, unlink, mkdir, rmdir, rename, stat, stat64, seek64,  mmap, mount, umount, chmod, chown。

-   JFFS2支持以只读属性挂载，当mount函数的入参mountflags为MS\_RDONLY时，JFFS将开启只读属性，所有的带有写入的接口，如write、mkdir、unlink，以及通过非O\_RDONLY属性打开的文件，将均被拒绝，并传出EACCESS错误码。


## 开发指导<a name="section14979101812411"></a>

**添加JFFS2分区**

调用add\_mtd\_partition函数添加JFFS2分区，该函数会自动为设备节点命名，对于JFFS2，其命名规则是“/dev/spinorblk”加上分区号。

add\_mtd\_partition函数有四个参数，第一个参数表示介质，有“nand”和“spinor”两种，JFFS2分区在“spinor”上使用，而“nand”是提供给YAFFS2使用的。

第二个参数表示起始地址，第三个参数表示分区大小，这两个参数都以16进制的形式传入。

最后一个参数表示分区号，有效值为0\~19。

```
if (uwRet = add_mtd_partition("spinor", 0x100000, 0x800000, 0) != 0) {
    dprintf("add jffs2 partition failed, return %d\n", uwRet);
} else {
    dprintf("Mount jffs2 on spinor.\n");
    uwRet = mount("/dev/spinorblk0", "/jffs0", "jffs2", 0, NULL);
    if (uwRet) {
        dprintf("mount jffs2 err %d\n", uwRet);
        dprintf("Mount jffs2 on nor finished.\n");
    }
}

if (uwRet = add_mtd_partition("spinor", 0x900000, 0x200000, 1) != 0) {
    dprintf("add jffs2 partition failed, return %d\n", uwRet);
}
```

成功后，在Shell中可以使用partition  spinor命令查看spinor flash分区信息。

```
OHOS # partition spinor
spinor partition num:0, dev name:/dev/spinorblk0, mountpt:/jffs0, startaddr:0x0100000,length:0x0800000 
spinor partition num:1, dev name:/dev/spinorblk1, mountpt:(null), startaddr:0x0900000,length:0x0200000
```

**挂载JFFS2**

调用mount\(\)函数实现设备节点和挂载点的挂载。

该函数有五个参数，第一个参数表示设备节点，这个参数需要和add\_mtd\_partition\(\)函数对应起来，第二个参数表示挂载点。第三个参数表示文件系统类型。

最后两个参数表示挂载标志和数据，默认为0和NULL；这一操作也可以在Shell中使用mount命令实现，最后两个参数不需要用户给出。

运行命令：

```
OHOS # mount /dev/spinorblk1 /jffs1 jffs2
```

将从串口得到如下回应信息，表明挂载成功。

```
OHOS # mount /dev/spinorblk1 /jffs1 jffs2
mount OK
```

挂载成功后，用户就能对norflash进行读写操作。

**卸载JFFS2**

调用umount\(\)函数卸载分区，只需要正确给出挂载点即可。

运行命令：

```
OHOS # umount /jffs1
```

将从串口得到如下回应信息，表明卸载成功。

```
OHOS # umount /jffs1
umount ok
```

**删除JFFS2分区**

调用delete\_mtd\_partition删除已经卸载的分区。

该函数有两个参数，第一个参数是分区号，第二个参数为介质类型，该函数与add\_mtd\_partition\(\)函数对应。

```
uwRet = delete_mtd_partition(1,"spinor"); 
if(uwRet != 0) {
    printf("delete jffs2 error\n"); 
} else {     
    printf("delete jffs2 ok\n");
}

OHOS # partition spinor 
spinor partition num:0, dev name:/dev/spinorblk0, mountpt:/jffs0, startaddr:0x0100000,length:0x0800000
```

**制作JFFS2文件系统镜像**

使用mkfs.jffs2工具，制作镜像默认命令见下。页大小默认为4KiB，eraseblock大小默认64KiB，镜像大小适应源目录并以0xFF填充为eraseblock大小的整数倍。若实际参数与下面不同时，修改相应参数。

```
./mkfs.jffs2 -d rootfs/ -o rootfs.jffs2
```

**表 1**  指令含义表

<a name="table1925613541465"></a>
<table><thead align="left"><tr id="row325613545615"><th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.1"><p id="p153851336772"><a name="p153851336772"></a><a name="p153851336772"></a>指令</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.2.3.1.2"><p id="p43852366714"><a name="p43852366714"></a><a name="p43852366714"></a>含义</p>
</th>
</tr>
</thead>
<tbody><tr id="row125715410619"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p20385103615715"><a name="p20385103615715"></a><a name="p20385103615715"></a>-s</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1338510362717"><a name="p1338510362717"></a><a name="p1338510362717"></a>页大小，不指定默认为4KiB</p>
</td>
</tr>
<tr id="row787741814720"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p538673616710"><a name="p538673616710"></a><a name="p538673616710"></a>-e</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p6386123612719"><a name="p6386123612719"></a><a name="p6386123612719"></a>eraseblock大小，不指定默认为64KiB</p>
</td>
</tr>
<tr id="row1160020211719"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p83861361079"><a name="p83861361079"></a><a name="p83861361079"></a>-p</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p538612361575"><a name="p538612361575"></a><a name="p538612361575"></a>镜像大小，不指定默认适应源目录并以0xFF填充为eraseblock大小的整数倍</p>
</td>
</tr>
<tr id="row151563245714"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p183864361579"><a name="p183864361579"></a><a name="p183864361579"></a>-d</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p238618361573"><a name="p238618361573"></a><a name="p238618361573"></a>要制作成文件系统镜像的源目录</p>
</td>
</tr>
<tr id="row1323210319714"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.1 "><p id="p103867369710"><a name="p103867369710"></a><a name="p103867369710"></a>-o</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.2.3.1.2 "><p id="p1938603617710"><a name="p1938603617710"></a><a name="p1938603617710"></a>要制成的镜像名称</p>
</td>
</tr>
</tbody>
</table>

