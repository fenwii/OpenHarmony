# NFS<a name="ZH-CN_TOPIC_0000001052170493"></a>

## 概述<a name="section18322139164413"></a>

NFS是Network File System（网络文件系统）的缩写。它最大的功能是可以通过网络，让不同的机器、不同的操作系统彼此分享其他用户的文件。因此，用户可以简单地将它看做是一个文件系统服务，在一定程度上相当于Windows环境下的共享文件夹。

NFS客户端用户，能够将网络远程的NFS服务端分享的目录挂载到本地端的机器中，运行程序和共享文件，但不占用当前的系统资源，所以，在本地端的机器看起来，远程服务端的目录就好像是自己的一个磁盘一样。

## 注意事项<a name="section532912331467"></a>

-   当前NFS文件不支持权限控制，请在创建NFS目录和文件时使用777权限。

-   当前NFS文件不支读阻塞和写阻塞。

-   当前NFS文件不支持信号功能。

-   当前NFS文件系统mount路径长度（不包含IP的长度）不超过255个字符，超过时返回ENAMETOOLONG错误。

-   当前NFS文件支持的操作有：open, close, read, write, seek, dup, dup2, sync, opendir, closedir, readdir, readdir\_r, rewinddir,  scandir, statfs, remove, unlink, mkdir, rmdir, rename, stat, stat64, seek64, mmap, mount, umount。

-   当前NFS支持TCP和UDP两种传输层协议，默认使用TCP。

-   open打开一个文件，参数有O\_TRUNC时，必须同时拥有写的权限，才会将文件中的内容清空。

-   在文件未关闭的情况下，rename\(\)函数重命名A为B之后，不会改变文件fd。

-   NFS功能目前处于beta测试阶段，可能存在功能不稳定的情况，建议您不要用于正式商用产品当中。


## 开发指导<a name="section166873374711"></a>

1.  **搭建NFS服务器**。

    这里以Ubuntu操作系统为例，说明服务器端设置步骤。

    1.  安装NFS服务器软件。

        设置好Ubuntu系统的下载源，保证网络连接好的情况下执行：

        ```
        sudo apt-get install nfs-kernel-server
        ```

    2.  创建用于挂载的目录并设置完全权限

        ```
        mkdir /home/sqbin/nfs
        sudo chmod 777 /home/sqbin/nfs
        ```

    3.  设置和启动NFS server。

        修改NFS配置文件/etc/exports，添加如下一行：

        ```
        /home/sqbin/nfs *(rw,no_root_squash,async)
        ```

        其中/home/sqbin/nfs是NFS共享的根目录。

        执行以下命令启动NFS server：

        ```
        sudo /etc/init.d/nfs-kernel-server start
        ```

        执行以下命令重启NFS server：

        ```
        sudo /etc/init.d/nfs-kernel-server restart
        ```


2.  **设置单板为NFS客户端**。

    本指导中的NFS客户端指运行OpenHarmony内核的设备。

    1.  硬件连接设置。

        OpenHarmony内核设备连接到NFS服务器的网络。设置两者IP，使其处于同一网段。比如，设置NFS服务器的IP为10.67.212.178/24，设OpenHarmony内核设备IP为10.67.212.3/24。

        OpenHarmony内核设备上的IP信息可通过ifconfig命令查看。

    2.  启动网络，确保单板到NFS服务器之间的网络通畅。

        启动以太网或者其他类型网络，使用ping命令检查到服务器的网络是否通畅。

        ```
        OHOS # ping 10.67.212.178
        [0]Reply from 10.67.212.178: time=1ms TTL=63
        [1]Reply from 10.67.212.178: time=0ms TTL=63
        [2]Reply from 10.67.212.178: time=1ms TTL=63
        [3]Reply from 10.67.212.178: time=1ms TTL=63
        --- 10.67.212.178 ping statistics ---
        4 packets transmitted, 4 received, 0 loss
        ```

        客户端NFS初始化，运行命令：

        ```
        OHOS # mkdir /nfs
        OHOS # mount 10.67.212.178:/home/sqbin/nfs /nfs nfs 1011 1000
        ```

        将从串口得到如下回应信息，表明初始化NFS客户端成功。

        ```
        OHOS # mount 10.67.212.178:/home/sqbin/nfs /nfs nfs 1011 1000
        Mount nfs on 10.67.212.178:/home/sqbin/nfs, uid:1011, gid:1000
        Mount nfs finished.
        ```

        该命令将服务器10.67.212.178上的/home/sqbin/nfs目录mount在OpenHarmony内核设备上的/nfs上。

        >![](public_sys-resources/icon-note.gif) **说明：** 
        >本例默认nfs server已经配置可用，即示例中服务器10.67.212.178上的/home/sqbin/nfs已配置可访问。

        mount命令的格式为：

        ```
        mount <SERVER_IP:SERVER_PATH> <CLIENT_PATH> nfs
        ```

        其中“SERVER\_IP“表示服务器的IP地址；“SERVER\_PATH“表示服务器端NFS共享目录路径；“CLIENT\_PATH“表示设备上的NFS路径。

        如果不想有NFS访问权限限制，请在Linux命令行将NFS根目录权限设置成777：

        ```
        chmod -R 777 /home/sqbin/nfs
        ```

        至此，NFS客户端设置完毕。NFS文件系统已成功挂载。


3.  **利用NFS共享文件**。

    在NFS服务器下新建目录dir，并保存。在OpenHarmony内核下运行ls命令：

    ```
    OHOS # ls /nfs
    ```

    则可从串口得到如下回应：

    ```
    OHOS # ls /nfs 
    Directory /nfs:                 
    drwxr-xr-x 0        u:0     g:0     dir
    ```

    可见，刚刚在NFS服务器上新建的dir目录已同步到客户端\(OpenHarmony内核系统\)的/nfs目录，两者保持同步。

    同样地，在客户端\(OpenHarmony内核系统\)上创建文件和目录，在NFS服务器上也可以访问，读者可自行体验。

    **平台差异性**。

    目前，NFS客户端仅支持NFS v3部分规范要求，因此对于规范支持不全的服务器，无法完全兼容。在开发测试过程中，建议使用Linux的NFS server，因为其对NFS支持很完善。


