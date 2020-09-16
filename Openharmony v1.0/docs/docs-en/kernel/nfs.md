# NFS<a name="EN-US_TOPIC_0000001052170493"></a>

## Overview<a name="section18322139164413"></a>

NFS allows you to share files across hosts and OSs over a network. You can treat NFS as a file system service, which is equivalent to folder sharing in the Windows OS to some extent.

An NFS client can mount a directory shared by a remote NFS server to the local host to run programs and share files without occupying the current system resources. The directory of the remote server is like a disk to the local host.

## Important Notes<a name="section532912331467"></a>

-   NFS files do not support permissions control. Use file permission  **777**  when creating NFS directories and files.

-   NFS files do not support read or write blocking.

-   NFS files do not support the signal function.

-   In NFS, the path length \(excluding the IP address\) in a  **mount**  operation cannot exceed 255 characters. If the maximum length is exceeded, the error code  **ENAMETOOLONG**  error is returned.

-   You can perform the following operation on NFS files:  **open**,  **close**,  **read**,  **write**,  **seek**,  **dup**,  **dup2**,  **sync**,  **opendir**,  **closedir**,  **readdir**,  **readdir\_r**,  **rewinddir**,  **scandir**,  **statfs**,  **remove**,  **unlink**,  **mkdir**,  **rmdir**,  **rename**,  **stat**,  **stat64**,  **seek64**,  **mmap**,  **mount**, and  **umount**.

-   Two transport layer protocols are supported in NFS: TCP \(default\) and UDP.

-   When you use  **open**  with the parameter  **O\_TRUNC**  to open a file, the file content will be cleared only when you have the write permission on the file.

-   When file A is not closed and the  **rename\(\)**  function renames file A as B, the fd is not changed.

-   The NFS feature is currently in the beta test and may be unstable. You are advised not to use the feature in commercial products.


## Development Guidelines<a name="section166873374711"></a>

1.  **Create an NFS server.**

    This section uses the Ubuntu operating system \(OS\) as an example to describe how to configure an NFS server.

    1.  Install the NFS server software.

        Set the download source of the Ubuntu OS when the network connection is normal.

        ```
        sudo apt-get install nfs-kernel-server
        ```

    2.  Create a directory for mounting and set full permissions for the directory.

        ```
        mkdir /home/sqbin/nfs
        sudo chmod 777 /home/sqbin/nfs
        ```

    3.  Configure and start the NFS server.

        Append the following line in the  **/etc/exports**  file:

        ```
        /home/sqbin/nfs *(rw,no_root_squash,async)
        ```

        **/home/sqbin/nfs**  is the root directory shared by the NFS server.

        Start the NFS server.

        ```
        sudo /etc/init.d/nfs-kernel-server start
        ```

        Restart the NFS server.

        ```
        sudo /etc/init.d/nfs-kernel-server restart
        ```


2.  **Configure a board as the NFS client.**

    In this section, the NFS client is a device running the OpenHarmony kernel.

    1.  Set the hardware connection.

        Connect the OpenHarmony kernel device to the NFS server. Set their IP addresses in the same network segment. For example, set the IP address of the NFS server to 10.67.212.178/24 and that of the OpenHarmony kernel device to 10.67.212.3/24.

        You can run the  **ifconfig**  command to view the device's IP address.

    2.  Start the network and ensure that the network between the board and NFS server is normal.

        Start the Ethernet or another type of network, and then run  **ping**  to check whether the network connection to the server is normal.

        ```
        OHOS # ping 10.67.212.178
        [0]Reply from 10.67.212.178: time=1ms TTL=63
        [1]Reply from 10.67.212.178: time=0ms TTL=63
        [2]Reply from 10.67.212.178: time=1ms TTL=63
        [3]Reply from 10.67.212.178: time=1ms TTL=63
        --- 10.67.212.178 ping statistics ---
        4 packets transmitted, 4 received, 0 loss
        ```

        Initialize the NFS client.

        ```
        OHOS # mkdir /nfs
        OHOS # mount 10.67.212.178:/home/sqbin/nfs /nfs nfs 1011 1000
        ```

        If the following information is displayed, the NFS client is initialized.

        ```
        OHOS # mount 10.67.212.178:/home/sqbin/nfs /nfs nfs 1011 1000
        Mount nfs on 10.67.212.178:/home/sqbin/nfs, uid:1011, gid:1000
        Mount nfs finished.
        ```

        This command mounts the  **/home/sqbin/nfs**  directory on the NFS server whose IP address is 10.67.212.178 to the  **/nfs**  directory on the device.

        >![](public_sys-resources/icon-note.gif) **NOTE:** 
        >This section assumes that the NFS server is available, that is, the  **/home/sqbin/nfs**  directory on the NFS server 10.67.212.178 is accessible.

        The  **mount**  command format is as follows:

        ```
        mount <SERVER_IP:SERVER_PATH> <CLIENT_PATH> nfs
        ```

        In this command,  **SERVER\_IP**  indicates the IP address of the NFS server,  **SERVER\_PATH**  indicates the path of the shared directory on the NFS server, and  **CLIENT\_PATH**  indicates the NFS path on the device.

        If you do not want to restrict the NFS access permission, set the permission of the NFS root directory to  **777**  on the Linux CLI.

        ```
        chmod -R 777 /home/sqbin/nfs
        ```

        The NFS client setting is complete, and the NFS file system has been mounted.


3.  **Share files using NFS.**

    Create the  **dir**  directory on the NFS server and save the directory. Run the  **ls**  command in the OpenHarmony kernel.

    ```
    OHOS # ls /nfs
    ```

    The following information is returned from the serial port:

    ```
    OHOS # ls /nfs 
    Directory /nfs:                 
    drwxr-xr-x 0        u:0     g:0     dir
    ```

    The  **dir**  directory created on the NFS server has been synchronized to the  **/nfs**  directory on the device.

    Similarly, you can create files and directories on the device and access them on the NFS server.

    **Platform Differences**

    Currently, the NFS client supports some NFS v3 specifications. Therefore, the NFS client is not fully compatible with all types of NFS servers. During the development and test, you are advised to use the Linux NFS server.


