# mman.h<a name="ZH-CN_TOPIC_0000001054748009"></a>

## **Overview**<a name="section430457698084831"></a>

**Related Modules:**

[MEM](MEM.md)

**Description:**

Declares structures and functions for performing memory operations, including memory mapping, remapping, unmapping, and attribute setting. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1121207223084831"></a>

## Macros<a name="define-members"></a>

<a name="table750236435084831"></a>
<table><thead align="left"><tr id="row1057385235084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p843684496084831"><a name="p843684496084831"></a><a name="p843684496084831"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1940673983084831"><a name="p1940673983084831"></a><a name="p1940673983084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row351194118084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1981813674084831"><a name="p1981813674084831"></a><a name="p1981813674084831"></a><a href="MEM.md#ga8523dcf952f6ff059a3bed717e4f1296">MAP_FAILED</a>&nbsp;&nbsp;&nbsp;((void *) -1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p711965961084831"><a name="p711965961084831"></a><a name="p711965961084831"></a>Indicates the return value of functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a> when the operation fails. </p>
</td>
</tr>
<tr id="row146309956084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1887461880084831"><a name="p1887461880084831"></a><a name="p1887461880084831"></a><a href="MEM.md#ga57028962c2a7c0c802ca6613492f2ef3">MAP_SHARED</a>&nbsp;&nbsp;&nbsp;0x01</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1087540116084831"><a name="p1087540116084831"></a><a name="p1087540116084831"></a>Indicates the mapping attribute that the updates to the mapping are visible to other processes mapping the same file and are carried through to the underlying file. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row1155130352084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1001466012084831"><a name="p1001466012084831"></a><a name="p1001466012084831"></a><a href="MEM.md#ga398ef47a991a44389aa9818c98a28d24">MAP_PRIVATE</a>&nbsp;&nbsp;&nbsp;0x02</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p537501991084831"><a name="p537501991084831"></a><a name="p537501991084831"></a>Indicates the mapping attribute that the updates to the mapping are not visible to other mapping processes and are not carried through to the underlying file. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row979877198084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p482536534084831"><a name="p482536534084831"></a><a name="p482536534084831"></a><a href="MEM.md#ga387ec707b30c5e78cf20a14517a63b96">MAP_FIXED</a>&nbsp;&nbsp;&nbsp;0x10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1202745259084831"><a name="p1202745259084831"></a><a name="p1202745259084831"></a>Indicates the mapping attribute that specifies the mapping as fixed mapping. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row1974673398084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1473597098084831"><a name="p1473597098084831"></a><a name="p1473597098084831"></a><a href="MEM.md#ga298ddbffafbe6cf941b92092edfb86a5">MAP_ANON</a>&nbsp;&nbsp;&nbsp;0x20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p165857434084831"><a name="p165857434084831"></a><a name="p165857434084831"></a>Indicates the mapping attribute that specifies the mapping as anonymous mapping without a specified file or device. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row677944115084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p765497444084831"><a name="p765497444084831"></a><a name="p765497444084831"></a><a href="MEM.md#gae4f86bff73414c5fc08c058f957212f0">MAP_ANONYMOUS</a>&nbsp;&nbsp;&nbsp;<a href="MEM.md#ga298ddbffafbe6cf941b92092edfb86a5">MAP_ANON</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1453426300084831"><a name="p1453426300084831"></a><a name="p1453426300084831"></a>Indicates the mapping attribute that specifies the mapping as anonymous mapping without a specified file or device. This macro is the synonym for <a href="MEM.md#ga298ddbffafbe6cf941b92092edfb86a5">MAP_ANON</a> and is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row1934884922084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1023035326084831"><a name="p1023035326084831"></a><a name="p1023035326084831"></a><a href="MEM.md#ga6a982b48b8d3eb8eccd17e0d54ee5379">PROT_NONE</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p905990833084831"><a name="p905990833084831"></a><a name="p905990833084831"></a>Indicates that no permission is granted to the current process for accessing the mapping area. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row698308211084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1583874803084831"><a name="p1583874803084831"></a><a name="p1583874803084831"></a><a href="MEM.md#ga15bf68ce8b590838b3a5c0b639d8d519">PROT_READ</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1731015531084831"><a name="p1731015531084831"></a><a name="p1731015531084831"></a>Indicates that the current process is granted the read permission on the mapping area. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row739762694084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p99689371084831"><a name="p99689371084831"></a><a name="p99689371084831"></a><a href="MEM.md#ga2a79c8ceefb8fc25a940ae07a3d94429">PROT_WRITE</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p864433717084831"><a name="p864433717084831"></a><a name="p864433717084831"></a>Indicates that the current process is granted the write permission on the mapping area. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row1184260034084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1765170354084831"><a name="p1765170354084831"></a><a name="p1765170354084831"></a><a href="MEM.md#ga77848f068638e916c72cd543f5ecb815">PROT_EXEC</a>&nbsp;&nbsp;&nbsp;4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1971594199084831"><a name="p1971594199084831"></a><a name="p1971594199084831"></a>Indicates that the current process is granted the execute permission on the mapping area. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row1308436275084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p331545502084831"><a name="p331545502084831"></a><a name="p331545502084831"></a><a href="MEM.md#ga979a9c42ee569172c2017c522c17a0b1">MREMAP_MAYMOVE</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2131154285084831"><a name="p2131154285084831"></a><a name="p2131154285084831"></a>Indicates the remapping attribute that allows the mapping to be relocated to a new address. This macro is used as an input parameter passed to functions such as <a href="MEM.md#ga1b5acd27009fbbf05d18e90640f6ef64">mremap()</a>. </p>
</td>
</tr>
<tr id="row772877562084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1750936125084831"><a name="p1750936125084831"></a><a name="p1750936125084831"></a><a href="MEM.md#ga689fc9cb8e5f54526471e67573624af9">MREMAP_FIXED</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1211328047084831"><a name="p1211328047084831"></a><a name="p1211328047084831"></a>Indicates the remapping attribute that specifies the mapping as fixed mapping. This macro is used as an input parameter passed to functions such as <a href="MEM.md#ga1b5acd27009fbbf05d18e90640f6ef64">mremap()</a>. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table599357133084831"></a>
<table><thead align="left"><tr id="row1862934436084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2061280045084831"><a name="p2061280045084831"></a><a name="p2061280045084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p415592375084831"><a name="p415592375084831"></a><a name="p415592375084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2130157778084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p831385248084831"><a name="p831385248084831"></a><a name="p831385248084831"></a><a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap</a> (void *addr, size_t length, int prot, int flags, int fd, off_t offset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p68347051084831"><a name="p68347051084831"></a><a name="p68347051084831"></a>void *&nbsp;</p>
<p id="p157269985084831"><a name="p157269985084831"></a><a name="p157269985084831"></a>Creates a mapping between the virtual address space of the calling process and a file or device. </p>
</td>
</tr>
<tr id="row924339813084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p891999503084831"><a name="p891999503084831"></a><a name="p891999503084831"></a><a href="MEM.md#ga1343e4aa663c9e8bb7d1b16d367f0b08">munmap</a> (void *addr, size_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2030261723084831"><a name="p2030261723084831"></a><a name="p2030261723084831"></a>int&nbsp;</p>
<p id="p407278383084831"><a name="p407278383084831"></a><a name="p407278383084831"></a>Removes all mappings for the specified virtual address space. </p>
</td>
</tr>
<tr id="row1513608497084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1894161973084831"><a name="p1894161973084831"></a><a name="p1894161973084831"></a><a href="MEM.md#gaa0752189f14ca11ba413fc944ae08b9c">mprotect</a> (void *addr, size_t len, int prot)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265578593084831"><a name="p265578593084831"></a><a name="p265578593084831"></a>int&nbsp;</p>
<p id="p133115223084831"><a name="p133115223084831"></a><a name="p133115223084831"></a>Sets protection attributes for the memory pages contained in the memory region starting from <strong id="b340185618084831"><a name="b340185618084831"></a><a name="b340185618084831"></a>addr</strong> with the specified length. </p>
</td>
</tr>
<tr id="row467832469084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p542689219084831"><a name="p542689219084831"></a><a name="p542689219084831"></a><a href="MEM.md#ga1b5acd27009fbbf05d18e90640f6ef64">mremap</a> (void *old_address, size_t old_size, size_t new_size, int flags,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p733010049084831"><a name="p733010049084831"></a><a name="p733010049084831"></a>void *&nbsp;</p>
<p id="p850944901084831"><a name="p850944901084831"></a><a name="p850944901084831"></a>Remaps a virtual memory region. </p>
</td>
</tr>
</tbody>
</table>

