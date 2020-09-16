# Kernel File System<a name="EN-US_TOPIC_0000001051611726"></a>

The OpenHarmony kernel supports the following file systems: Virtual File System \(VFS\), Network File System \(NFS\), RAM File System \(RAMFS\), File Allocation Table \(FAT\), and Journalling Flash File System Version 2 \(JFFS2\).

The table below describes the functions of these file systems.

**Table  1**  File system functions

<a name="table6330194819415"></a>
<table><thead align="left"><tr id="row6331184864111"><th class="cellrowborder" valign="top" width="11.559999999999999%" id="mcps1.2.3.1.1"><p id="p17644161411438"><a name="p17644161411438"></a><a name="p17644161411438"></a>File System</p>
</th>
<th class="cellrowborder" valign="top" width="88.44%" id="mcps1.2.3.1.2"><p id="p116441414184312"><a name="p116441414184312"></a><a name="p116441414184312"></a>Function</p>
</th>
</tr>
</thead>
<tbody><tr id="row371213562318"><td class="cellrowborder" valign="top" width="11.559999999999999%" headers="mcps1.2.3.1.1 "><p id="p37130569316"><a name="p37130569316"></a><a name="p37130569316"></a>VFS</p>
</td>
<td class="cellrowborder" valign="top" width="88.44%" headers="mcps1.2.3.1.2 "><p id="p1771335615316"><a name="p1771335615316"></a><a name="p1771335615316"></a>In essence, VFS is not a real file system. It is an abstract layer on top of a heterogeneous file system and provides you with a unified Unix-like file operation interface.</p>
</td>
</tr>
<tr id="row189255844219"><td class="cellrowborder" valign="top" width="11.559999999999999%" headers="mcps1.2.3.1.1 "><p id="p1564481494319"><a name="p1564481494319"></a><a name="p1564481494319"></a>NFS</p>
</td>
<td class="cellrowborder" valign="top" width="88.44%" headers="mcps1.2.3.1.2 "><p id="p764561414434"><a name="p764561414434"></a><a name="p764561414434"></a>NFS allows you to share files across hosts and OSs over a network.</p>
</td>
</tr>
<tr id="row17332194820411"><td class="cellrowborder" valign="top" width="11.559999999999999%" headers="mcps1.2.3.1.1 "><p id="p2064561415435"><a name="p2064561415435"></a><a name="p2064561415435"></a>RAMFS</p>
</td>
<td class="cellrowborder" valign="top" width="88.44%" headers="mcps1.2.3.1.2 "><p id="p12646614204320"><a name="p12646614204320"></a><a name="p12646614204320"></a>RAMFS is a RAM-based file system. All files are stored in the RAM, and file read/write operations are performed in the RAM, which reduces the read/write loss of the memory and improves the data read/write speed. It provides a RAM-based storage buffer for dynamic file systems.</p>
</td>
</tr>
<tr id="row16332174894116"><td class="cellrowborder" valign="top" width="11.559999999999999%" headers="mcps1.2.3.1.1 "><p id="p1864571410433"><a name="p1864571410433"></a><a name="p1864571410433"></a>FAT</p>
</td>
<td class="cellrowborder" valign="top" width="88.44%" headers="mcps1.2.3.1.2 "><p id="p364511141434"><a name="p364511141434"></a><a name="p364511141434"></a>There are FAT12, FAT16, and FAT32. FAT is often used on removable storage media (such as USB flash drives, SD cards, and portable hard disks) to provide better compatibility between devices and desktop systems such as Windows and Linux.</p>
</td>
</tr>
<tr id="row1880218157414"><td class="cellrowborder" valign="top" width="11.559999999999999%" headers="mcps1.2.3.1.1 "><p id="p19645814144312"><a name="p19645814144312"></a><a name="p19645814144312"></a>JFFS2</p>
</td>
<td class="cellrowborder" valign="top" width="88.44%" headers="mcps1.2.3.1.2 "><p id="p8645161454314"><a name="p8645161454314"></a><a name="p8645161454314"></a>JFFS2 is a journal-type file system implemented on Memory Technology Devices (MTDs). It is mainly used to manage files of the NOR flash memory. JFFS2 used in the <span id="text181481059803"><a name="text181481059803"></a><a name="text181481059803"></a>OpenHarmony</span> kernel supports multiple partitions.</p>
</td>
</tr>
</tbody>
</table>

-   **[VFS](vfs.md)**  

-   **[NFS](nfs.md)**  

-   **[RAMFS](ramfs.md)**  

-   **[FAT](fat.md)**  

-   **[JFFS2](jffs2.md)**  


