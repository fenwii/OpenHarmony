# MEM<a name="ZH-CN_TOPIC_0000001055189439"></a>

## **Overview**<a name="section1912913183084824"></a>

Provides structures and functions for performing memory operations, including memory mapping, remapping, allocation, and release. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1658267858084824"></a>

## Files<a name="files"></a>

<a name="table3042179084824"></a>
<table><thead align="left"><tr id="row812054874084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1176194672084824"><a name="p1176194672084824"></a><a name="p1176194672084824"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p237173750084824"><a name="p237173750084824"></a><a name="p237173750084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1234744111084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886291998084824"><a name="p1886291998084824"></a><a name="p1886291998084824"></a><a href="malloc-h.md">malloc.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p203346041084824"><a name="p203346041084824"></a><a name="p203346041084824"></a>Declares APIs for allocating and releasing memory. </p>
</td>
</tr>
<tr id="row1855116454084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p953517973084824"><a name="p953517973084824"></a><a name="p953517973084824"></a><a href="mman-h.md">mman.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p249160126084824"><a name="p249160126084824"></a><a name="p249160126084824"></a>Declares structures and functions for performing memory operations, including memory mapping, remapping, unmapping, and attribute setting. </p>
</td>
</tr>
<tr id="row146440572084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1913839936084824"><a name="p1913839936084824"></a><a name="p1913839936084824"></a><a href="shm-h.md">shm.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2075740579084824"><a name="p2075740579084824"></a><a name="p2075740579084824"></a>Declares APIs for creating, mapping, deleting, and controlling shared memory. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table108962410084824"></a>
<table><thead align="left"><tr id="row37238497084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p667676610084824"><a name="p667676610084824"></a><a name="p667676610084824"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1368063596084824"><a name="p1368063596084824"></a><a name="p1368063596084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row254907990084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p493779893084824"><a name="p493779893084824"></a><a name="p493779893084824"></a><a href="shmid_ds.md">shmid_ds</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p769695349084824"><a name="p769695349084824"></a><a name="p769695349084824"></a>Stores information about a shared memory segment. </p>
</td>
</tr>
<tr id="row737618268084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p779043113084824"><a name="p779043113084824"></a><a name="p779043113084824"></a><a href="shminfo.md">shminfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p222047412084824"><a name="p222047412084824"></a><a name="p222047412084824"></a>Describes limitations and attributes of system-level shared memory. </p>
</td>
</tr>
<tr id="row1689909426084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p602669859084824"><a name="p602669859084824"></a><a name="p602669859084824"></a><a href="shm_info.md">shm_info</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p817611295084824"><a name="p817611295084824"></a><a name="p817611295084824"></a>Describes system resource information about the shared memory. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1500198759084824"></a>
<table><thead align="left"><tr id="row904468166084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p259380612084824"><a name="p259380612084824"></a><a name="p259380612084824"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p123102738084824"><a name="p123102738084824"></a><a name="p123102738084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1217528099084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p686751702084824"><a name="p686751702084824"></a><a name="p686751702084824"></a><em id="ga8523dcf952f6ff059a3bed717e4f1296"><a name="ga8523dcf952f6ff059a3bed717e4f1296"></a><a name="ga8523dcf952f6ff059a3bed717e4f1296"></a></em>MAP_FAILED &nbsp;&nbsp;&nbsp;((void *) -1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p813956620084824"><a name="p813956620084824"></a><a name="p813956620084824"></a>Indicates the return value of functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a> when the operation fails. </p>
</td>
</tr>
<tr id="row1155901719084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1628198086084824"><a name="p1628198086084824"></a><a name="p1628198086084824"></a><em id="ga57028962c2a7c0c802ca6613492f2ef3"><a name="ga57028962c2a7c0c802ca6613492f2ef3"></a><a name="ga57028962c2a7c0c802ca6613492f2ef3"></a></em>MAP_SHARED &nbsp;&nbsp;&nbsp;0x01</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1312725240084824"><a name="p1312725240084824"></a><a name="p1312725240084824"></a>Indicates the mapping attribute that the updates to the mapping are visible to other processes mapping the same file and are carried through to the underlying file. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row171292457084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p110869228084824"><a name="p110869228084824"></a><a name="p110869228084824"></a><em id="ga398ef47a991a44389aa9818c98a28d24"><a name="ga398ef47a991a44389aa9818c98a28d24"></a><a name="ga398ef47a991a44389aa9818c98a28d24"></a></em>MAP_PRIVATE &nbsp;&nbsp;&nbsp;0x02</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1831566688084824"><a name="p1831566688084824"></a><a name="p1831566688084824"></a>Indicates the mapping attribute that the updates to the mapping are not visible to other mapping processes and are not carried through to the underlying file. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row283700836084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217118486084824"><a name="p1217118486084824"></a><a name="p1217118486084824"></a><em id="ga387ec707b30c5e78cf20a14517a63b96"><a name="ga387ec707b30c5e78cf20a14517a63b96"></a><a name="ga387ec707b30c5e78cf20a14517a63b96"></a></em>MAP_FIXED &nbsp;&nbsp;&nbsp;0x10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p202663715084824"><a name="p202663715084824"></a><a name="p202663715084824"></a>Indicates the mapping attribute that specifies the mapping as fixed mapping. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row1152706215084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1790530733084824"><a name="p1790530733084824"></a><a name="p1790530733084824"></a><em id="ga298ddbffafbe6cf941b92092edfb86a5"><a name="ga298ddbffafbe6cf941b92092edfb86a5"></a><a name="ga298ddbffafbe6cf941b92092edfb86a5"></a></em>MAP_ANON &nbsp;&nbsp;&nbsp;0x20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p113876264084824"><a name="p113876264084824"></a><a name="p113876264084824"></a>Indicates the mapping attribute that specifies the mapping as anonymous mapping without a specified file or device. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row496723867084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1057244533084824"><a name="p1057244533084824"></a><a name="p1057244533084824"></a><em id="gae4f86bff73414c5fc08c058f957212f0"><a name="gae4f86bff73414c5fc08c058f957212f0"></a><a name="gae4f86bff73414c5fc08c058f957212f0"></a></em>MAP_ANONYMOUS &nbsp;&nbsp;&nbsp;<a href="MEM.md#ga298ddbffafbe6cf941b92092edfb86a5">MAP_ANON</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p452837994084824"><a name="p452837994084824"></a><a name="p452837994084824"></a>Indicates the mapping attribute that specifies the mapping as anonymous mapping without a specified file or device. This macro is the synonym for <a href="MEM.md#ga298ddbffafbe6cf941b92092edfb86a5">MAP_ANON</a> and is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row1208280650084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1994298883084824"><a name="p1994298883084824"></a><a name="p1994298883084824"></a><em id="ga6a982b48b8d3eb8eccd17e0d54ee5379"><a name="ga6a982b48b8d3eb8eccd17e0d54ee5379"></a><a name="ga6a982b48b8d3eb8eccd17e0d54ee5379"></a></em>PROT_NONE &nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1285556738084824"><a name="p1285556738084824"></a><a name="p1285556738084824"></a>Indicates that no permission is granted to the current process for accessing the mapping area. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row1892021657084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p564958388084824"><a name="p564958388084824"></a><a name="p564958388084824"></a><em id="ga15bf68ce8b590838b3a5c0b639d8d519"><a name="ga15bf68ce8b590838b3a5c0b639d8d519"></a><a name="ga15bf68ce8b590838b3a5c0b639d8d519"></a></em>PROT_READ &nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2099248122084824"><a name="p2099248122084824"></a><a name="p2099248122084824"></a>Indicates that the current process is granted the read permission on the mapping area. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row799451010084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2035791855084824"><a name="p2035791855084824"></a><a name="p2035791855084824"></a><em id="ga2a79c8ceefb8fc25a940ae07a3d94429"><a name="ga2a79c8ceefb8fc25a940ae07a3d94429"></a><a name="ga2a79c8ceefb8fc25a940ae07a3d94429"></a></em>PROT_WRITE &nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p379231642084824"><a name="p379231642084824"></a><a name="p379231642084824"></a>Indicates that the current process is granted the write permission on the mapping area. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row344191521084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1141227585084824"><a name="p1141227585084824"></a><a name="p1141227585084824"></a><em id="ga77848f068638e916c72cd543f5ecb815"><a name="ga77848f068638e916c72cd543f5ecb815"></a><a name="ga77848f068638e916c72cd543f5ecb815"></a></em>PROT_EXEC &nbsp;&nbsp;&nbsp;4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115269167084824"><a name="p115269167084824"></a><a name="p115269167084824"></a>Indicates that the current process is granted the execute permission on the mapping area. This macro is used as an input parameter passed to functions such as <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </p>
</td>
</tr>
<tr id="row1997647191084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p826672210084824"><a name="p826672210084824"></a><a name="p826672210084824"></a><em id="ga979a9c42ee569172c2017c522c17a0b1"><a name="ga979a9c42ee569172c2017c522c17a0b1"></a><a name="ga979a9c42ee569172c2017c522c17a0b1"></a></em>MREMAP_MAYMOVE &nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p415280211084824"><a name="p415280211084824"></a><a name="p415280211084824"></a>Indicates the remapping attribute that allows the mapping to be relocated to a new address. This macro is used as an input parameter passed to functions such as <a href="MEM.md#ga1b5acd27009fbbf05d18e90640f6ef64">mremap()</a>. </p>
</td>
</tr>
<tr id="row600577389084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1222512667084824"><a name="p1222512667084824"></a><a name="p1222512667084824"></a><em id="ga689fc9cb8e5f54526471e67573624af9"><a name="ga689fc9cb8e5f54526471e67573624af9"></a><a name="ga689fc9cb8e5f54526471e67573624af9"></a></em>MREMAP_FIXED &nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p280614889084824"><a name="p280614889084824"></a><a name="p280614889084824"></a>Indicates the remapping attribute that specifies the mapping as fixed mapping. This macro is used as an input parameter passed to functions such as <a href="MEM.md#ga1b5acd27009fbbf05d18e90640f6ef64">mremap()</a>. </p>
</td>
</tr>
<tr id="row1795418818084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492692620084824"><a name="p1492692620084824"></a><a name="p1492692620084824"></a><em id="ga1f422a47c416c67470e3a0fb8b7529d8"><a name="ga1f422a47c416c67470e3a0fb8b7529d8"></a><a name="ga1f422a47c416c67470e3a0fb8b7529d8"></a></em>SHMLBA &nbsp;&nbsp;&nbsp;4096</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1300108811084824"><a name="p1300108811084824"></a><a name="p1300108811084824"></a>Aligns the shared memory address. </p>
</td>
</tr>
<tr id="row883742196084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p602452957084824"><a name="p602452957084824"></a><a name="p602452957084824"></a><em id="ga45da2dbfb146e926c8fd842379c0362c"><a name="ga45da2dbfb146e926c8fd842379c0362c"></a><a name="ga45da2dbfb146e926c8fd842379c0362c"></a></em>SHM_R &nbsp;&nbsp;&nbsp;0400</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p716552610084824"><a name="p716552610084824"></a><a name="p716552610084824"></a>Indicates that the shared memory segment is readable. This macro is used for setting the <strong id="b1934678511084824"><a name="b1934678511084824"></a><a name="b1934678511084824"></a>shmflg</strong> parameter passed to functions such as <a href="MEM.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </p>
</td>
</tr>
<tr id="row969298200084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p500143069084824"><a name="p500143069084824"></a><a name="p500143069084824"></a><em id="gafd00993215ed6030ec817bf3615044d1"><a name="gafd00993215ed6030ec817bf3615044d1"></a><a name="gafd00993215ed6030ec817bf3615044d1"></a></em>SHM_W &nbsp;&nbsp;&nbsp;0200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p631673564084824"><a name="p631673564084824"></a><a name="p631673564084824"></a>Indicates that the shared memory segment is writable. This macro is used for setting the <strong id="b12279738084824"><a name="b12279738084824"></a><a name="b12279738084824"></a>shmflg</strong> parameter passed to functions such as <a href="MEM.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </p>
</td>
</tr>
<tr id="row201278404084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p928782338084824"><a name="p928782338084824"></a><a name="p928782338084824"></a><em id="ga899e8ef0c4c33e2a5cc708c05c75429a"><a name="ga899e8ef0c4c33e2a5cc708c05c75429a"></a><a name="ga899e8ef0c4c33e2a5cc708c05c75429a"></a></em>SHM_RDONLY &nbsp;&nbsp;&nbsp;010000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695870039084824"><a name="p1695870039084824"></a><a name="p1695870039084824"></a>Indicates that the attached shared memory segment is read-only. This macro is used for setting the <strong id="b282444631084824"><a name="b282444631084824"></a><a name="b282444631084824"></a>shmflg</strong> parameter passed to functions such as <a href="MEM.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat()</a>. </p>
</td>
</tr>
<tr id="row1598989737084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1823408773084824"><a name="p1823408773084824"></a><a name="p1823408773084824"></a><em id="ga4ae5f621aa1333d9d5962c3e9d674a90"><a name="ga4ae5f621aa1333d9d5962c3e9d674a90"></a><a name="ga4ae5f621aa1333d9d5962c3e9d674a90"></a></em>SHM_RND &nbsp;&nbsp;&nbsp;020000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p266221626084824"><a name="p266221626084824"></a><a name="p266221626084824"></a>Indicates that the shared memory address can be rounded to a value meeting the requirement (<a href="MEM.md#ga1f422a47c416c67470e3a0fb8b7529d8">SHMLBA</a>). This macro is used for setting the <strong id="b818116184084824"><a name="b818116184084824"></a><a name="b818116184084824"></a>shmflg</strong> parameter passed to functions such as <a href="MEM.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat()</a>. </p>
</td>
</tr>
<tr id="row1336770385084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p846848077084824"><a name="p846848077084824"></a><a name="p846848077084824"></a><em id="gab652a1a4737f9118a64a8fb74084ef7d"><a name="gab652a1a4737f9118a64a8fb74084ef7d"></a><a name="gab652a1a4737f9118a64a8fb74084ef7d"></a></em>SHM_REMAP &nbsp;&nbsp;&nbsp;040000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1165752233084824"><a name="p1165752233084824"></a><a name="p1165752233084824"></a>Indicates that the memory segment can be remapped. This macro is used for setting the <strong id="b2096452216084824"><a name="b2096452216084824"></a><a name="b2096452216084824"></a>shmflg</strong> parameter passed to functions such as <a href="MEM.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat()</a>. </p>
</td>
</tr>
<tr id="row997724144084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1789536740084824"><a name="p1789536740084824"></a><a name="p1789536740084824"></a><em id="ga0bb6454e0dd48a66376bfaa05170ce82"><a name="ga0bb6454e0dd48a66376bfaa05170ce82"></a><a name="ga0bb6454e0dd48a66376bfaa05170ce82"></a></em>SHM_EXEC &nbsp;&nbsp;&nbsp;0100000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1881394756084824"><a name="p1881394756084824"></a><a name="p1881394756084824"></a>Indicates that the attached shared memory segment is executable. This macro is used for setting the <strong id="b1877450829084824"><a name="b1877450829084824"></a><a name="b1877450829084824"></a>shmflg</strong> parameter passed to functions such as <a href="MEM.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat()</a>. </p>
</td>
</tr>
<tr id="row1622545381084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p187132236084824"><a name="p187132236084824"></a><a name="p187132236084824"></a><em id="ga66735ad43f79860ccdd21888c3ead8cc"><a name="ga66735ad43f79860ccdd21888c3ead8cc"></a><a name="ga66735ad43f79860ccdd21888c3ead8cc"></a></em>SHM_LOCK &nbsp;&nbsp;&nbsp;11</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p459018319084824"><a name="p459018319084824"></a><a name="p459018319084824"></a>Locks the shared memory segment in memory so that it cannot be swapped to the swap partition. This macro is used for setting the <strong id="b66824884084824"><a name="b66824884084824"></a><a name="b66824884084824"></a>shmflg</strong> parameter passed to functions such as <a href="MEM.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </p>
</td>
</tr>
<tr id="row65753657084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492007486084824"><a name="p1492007486084824"></a><a name="p1492007486084824"></a><em id="ga7497459fc5ebe82bbbdfa3809c938312"><a name="ga7497459fc5ebe82bbbdfa3809c938312"></a><a name="ga7497459fc5ebe82bbbdfa3809c938312"></a></em>SHM_UNLOCK &nbsp;&nbsp;&nbsp;12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073791768084824"><a name="p2073791768084824"></a><a name="p2073791768084824"></a>Unlocks the shared memory segment. This macro is used for setting the <strong id="b1033786961084824"><a name="b1033786961084824"></a><a name="b1033786961084824"></a>shmflg</strong> parameter passed to functions such as <a href="MEM.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </p>
</td>
</tr>
<tr id="row286805282084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1105407811084824"><a name="p1105407811084824"></a><a name="p1105407811084824"></a><em id="ga2e0f8c5b0fafab9f2602d19588d03e95"><a name="ga2e0f8c5b0fafab9f2602d19588d03e95"></a><a name="ga2e0f8c5b0fafab9f2602d19588d03e95"></a></em>SHM_STAT &nbsp;&nbsp;&nbsp;(13 | (<a href="IPC.md#ga16a91ee69c3cb6bfec425e1bfd5edd18">IPC_STAT</a> &amp; 0x100))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1084486519084824"><a name="p1084486519084824"></a><a name="p1084486519084824"></a>Obtains a <a href="shmid_ds.md">shmid_ds</a> data structure. This macro is used for setting the <strong id="b1252468571084824"><a name="b1252468571084824"></a><a name="b1252468571084824"></a>cmd</strong> parameter passed to <a href="MEM.md#gab2cfe9a9370d4c74b485876260e2e0fe">shmctl()</a>. </p>
</td>
</tr>
<tr id="row1884143605084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1887695189084824"><a name="p1887695189084824"></a><a name="p1887695189084824"></a><em id="gafecb9e202431a631f42469c9ecbee99e"><a name="gafecb9e202431a631f42469c9ecbee99e"></a><a name="gafecb9e202431a631f42469c9ecbee99e"></a></em>SHM_INFO &nbsp;&nbsp;&nbsp;14</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1245245073084824"><a name="p1245245073084824"></a><a name="p1245245073084824"></a>Obtains a <a href="shm_info.md">shm_info</a> data structure that includes system resource information about this shared memory segment. This macro is used for setting the <strong id="b1201856327084824"><a name="b1201856327084824"></a><a name="b1201856327084824"></a>cmd</strong> parameter passed to <a href="MEM.md#gab2cfe9a9370d4c74b485876260e2e0fe">shmctl()</a>. </p>
</td>
</tr>
<tr id="row792425190084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p863320888084824"><a name="p863320888084824"></a><a name="p863320888084824"></a><em id="ga9e7f0a6d71663d9173d9aae2a2f01220"><a name="ga9e7f0a6d71663d9173d9aae2a2f01220"></a><a name="ga9e7f0a6d71663d9173d9aae2a2f01220"></a></em>SHM_STAT_ANY &nbsp;&nbsp;&nbsp;(15 | (<a href="IPC.md#ga16a91ee69c3cb6bfec425e1bfd5edd18">IPC_STAT</a> &amp; 0x100))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2013360895084824"><a name="p2013360895084824"></a><a name="p2013360895084824"></a>Obtains a <a href="shmid_ds.md">shmid_ds</a> data structure without permission check. This macro is used for setting the <strong id="b1797146264084824"><a name="b1797146264084824"></a><a name="b1797146264084824"></a>cmd</strong> parameter passed to <a href="MEM.md#gab2cfe9a9370d4c74b485876260e2e0fe">shmctl()</a>. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table600970182084824"></a>
<table><thead align="left"><tr id="row2052783631084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1900732467084824"><a name="p1900732467084824"></a><a name="p1900732467084824"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p271361051084824"><a name="p271361051084824"></a><a name="p271361051084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row579056829084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1839963165084824"><a name="p1839963165084824"></a><a name="p1839963165084824"></a><a href="MEM.md#ga7ac38fce3243a7dcf448301ee9ffd392">malloc</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p993506918084824"><a name="p993506918084824"></a><a name="p993506918084824"></a>void *&nbsp;</p>
<p id="p1172603532084824"><a name="p1172603532084824"></a><a name="p1172603532084824"></a>Dynamically allocates a block of uninitialized memory with the specified size. </p>
</td>
</tr>
<tr id="row13445151084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1780562578084824"><a name="p1780562578084824"></a><a name="p1780562578084824"></a><a href="MEM.md#ga62b7798461bd461da64c5f9d35feddf7">calloc</a> (size_t nmemb, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p84905273084824"><a name="p84905273084824"></a><a name="p84905273084824"></a>void *&nbsp;</p>
<p id="p1066402207084824"><a name="p1066402207084824"></a><a name="p1066402207084824"></a>Dynamically allocates multiple blocks of memory with the specified size. </p>
</td>
</tr>
<tr id="row1992768405084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p365227171084824"><a name="p365227171084824"></a><a name="p365227171084824"></a><a href="MEM.md#ga1a6b5e8d2f1c37e5b43e4345586075be">realloc</a> (void *ptr, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p820721363084824"><a name="p820721363084824"></a><a name="p820721363084824"></a>void *&nbsp;</p>
<p id="p141385858084824"><a name="p141385858084824"></a><a name="p141385858084824"></a>Changes the size of a previously allocated memory block pointed to by <strong id="b466250044084824"><a name="b466250044084824"></a><a name="b466250044084824"></a>ptr</strong> to the specified size. </p>
</td>
</tr>
<tr id="row1086360258084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p939809720084824"><a name="p939809720084824"></a><a name="p939809720084824"></a><a href="MEM.md#gafbedc913aa4651b3c3b4b3aecd9b4711">free</a> (void *ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1307063373084824"><a name="p1307063373084824"></a><a name="p1307063373084824"></a>void&nbsp;</p>
<p id="p2029703656084824"><a name="p2029703656084824"></a><a name="p2029703656084824"></a>Frees the memory space pointed to by <strong id="b1773514887084824"><a name="b1773514887084824"></a><a name="b1773514887084824"></a>ptr</strong>. </p>
</td>
</tr>
<tr id="row242462086084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p102463813084824"><a name="p102463813084824"></a><a name="p102463813084824"></a><a href="MEM.md#ga6a1c0668b7069bb45fd6e69f301ed5b9">memalign</a> (size_t alignment, size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p185181806084824"><a name="p185181806084824"></a><a name="p185181806084824"></a>void *&nbsp;</p>
<p id="p1094074856084824"><a name="p1094074856084824"></a><a name="p1094074856084824"></a>Allocates a block of memory with the specified size based on the given alignment mode. </p>
</td>
</tr>
<tr id="row130733337084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p108351048084824"><a name="p108351048084824"></a><a name="p108351048084824"></a><a href="MEM.md#gaa011d7b7bfeba45c8c32e04204a0f565">malloc_usable_size</a> (void *ptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p143183122084824"><a name="p143183122084824"></a><a name="p143183122084824"></a>size_t&nbsp;</p>
<p id="p199485075084824"><a name="p199485075084824"></a><a name="p199485075084824"></a>Obtains the size of the memory block pointed to by <strong id="b1974683797084824"><a name="b1974683797084824"></a><a name="b1974683797084824"></a>ptr</strong>. </p>
</td>
</tr>
<tr id="row1970887887084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422121597084824"><a name="p422121597084824"></a><a name="p422121597084824"></a><a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap</a> (void *addr, size_t length, int prot, int flags, int fd, off_t offset)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1883703622084824"><a name="p1883703622084824"></a><a name="p1883703622084824"></a>void *&nbsp;</p>
<p id="p759717593084824"><a name="p759717593084824"></a><a name="p759717593084824"></a>Creates a mapping between the virtual address space of the calling process and a file or device. </p>
</td>
</tr>
<tr id="row337149447084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p49725344084824"><a name="p49725344084824"></a><a name="p49725344084824"></a><a href="MEM.md#ga1343e4aa663c9e8bb7d1b16d367f0b08">munmap</a> (void *addr, size_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p539013459084824"><a name="p539013459084824"></a><a name="p539013459084824"></a>int&nbsp;</p>
<p id="p1353683996084824"><a name="p1353683996084824"></a><a name="p1353683996084824"></a>Removes all mappings for the specified virtual address space. </p>
</td>
</tr>
<tr id="row1477818312084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1838024203084824"><a name="p1838024203084824"></a><a name="p1838024203084824"></a><a href="MEM.md#gaa0752189f14ca11ba413fc944ae08b9c">mprotect</a> (void *addr, size_t len, int prot)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1094849500084824"><a name="p1094849500084824"></a><a name="p1094849500084824"></a>int&nbsp;</p>
<p id="p93283869084824"><a name="p93283869084824"></a><a name="p93283869084824"></a>Sets protection attributes for the memory pages contained in the memory region starting from <strong id="b1475995804084824"><a name="b1475995804084824"></a><a name="b1475995804084824"></a>addr</strong> with the specified length. </p>
</td>
</tr>
<tr id="row1154156168084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1761564105084824"><a name="p1761564105084824"></a><a name="p1761564105084824"></a><a href="MEM.md#ga1b5acd27009fbbf05d18e90640f6ef64">mremap</a> (void *old_address, size_t old_size, size_t new_size, int flags,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1449500648084824"><a name="p1449500648084824"></a><a name="p1449500648084824"></a>void *&nbsp;</p>
<p id="p649142230084824"><a name="p649142230084824"></a><a name="p649142230084824"></a>Remaps a virtual memory region. </p>
</td>
</tr>
<tr id="row2141309199084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1262609606084824"><a name="p1262609606084824"></a><a name="p1262609606084824"></a><a href="MEM.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat</a> (int shmid, const void *shmaddr, int shmflg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p976720260084824"><a name="p976720260084824"></a><a name="p976720260084824"></a>void *&nbsp;</p>
<p id="p1926212822084824"><a name="p1926212822084824"></a><a name="p1926212822084824"></a>Attaches the shared memory segment identified by <strong id="b2121687632084824"><a name="b2121687632084824"></a><a name="b2121687632084824"></a>shmid</strong> to the address space of the current process. </p>
</td>
</tr>
<tr id="row225393781084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p911715133084824"><a name="p911715133084824"></a><a name="p911715133084824"></a><a href="MEM.md#gab2cfe9a9370d4c74b485876260e2e0fe">shmctl</a> (int shmid, int cmd, struct <a href="shmid_ds.md">shmid_ds</a> *buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1694841363084824"><a name="p1694841363084824"></a><a name="p1694841363084824"></a>int&nbsp;</p>
<p id="p1178613392084824"><a name="p1178613392084824"></a><a name="p1178613392084824"></a>Performs a control operation specified by the <strong id="b1430544839084824"><a name="b1430544839084824"></a><a name="b1430544839084824"></a>cmd</strong> parameter on the shared memory segment identified by <strong id="b1879770909084824"><a name="b1879770909084824"></a><a name="b1879770909084824"></a>shmid</strong>. </p>
</td>
</tr>
<tr id="row1527687719084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1296603742084824"><a name="p1296603742084824"></a><a name="p1296603742084824"></a><a href="MEM.md#ga934738fcc6c27c0d45cff9bb8cc38a7f">shmdt</a> (const void *shmaddr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p315516445084824"><a name="p315516445084824"></a><a name="p315516445084824"></a>int&nbsp;</p>
<p id="p1264346188084824"><a name="p1264346188084824"></a><a name="p1264346188084824"></a>Detaches the shared memory segment attached to the address pointed to by <strong id="b1180620707084824"><a name="b1180620707084824"></a><a name="b1180620707084824"></a>shmaddr</strong> from the address space of the calling process. </p>
</td>
</tr>
<tr id="row437380008084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p603932087084824"><a name="p603932087084824"></a><a name="p603932087084824"></a><a href="MEM.md#ga23e346182fc10c5286f37213e09fefb2">shmget</a> (key_t key, size_t size, int shmflg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1523639761084824"><a name="p1523639761084824"></a><a name="p1523639761084824"></a>int&nbsp;</p>
<p id="p877905428084824"><a name="p877905428084824"></a><a name="p877905428084824"></a>Obtains or creates a shared memory segment with the specified size based on the ID specified by <strong id="b1150263618084824"><a name="b1150263618084824"></a><a name="b1150263618084824"></a>key</strong>. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section610494084084824"></a>

## **Function Documentation**<a name="section1078049142084824"></a>

## calloc\(\)<a name="ga62b7798461bd461da64c5f9d35feddf7"></a>

```
void* calloc (size_t nmemb, size_t size )
```

 **Description:**

Dynamically allocates multiple blocks of memory with the specified size. 

**Parameters:**

<a name="table1339660521084824"></a>
<table><thead align="left"><tr id="row833258820084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p429510752084824"><a name="p429510752084824"></a><a name="p429510752084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1503647998084824"><a name="p1503647998084824"></a><a name="p1503647998084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1108543622084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nmemb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of memory blocks to allocate. </td>
</tr>
<tr id="row751353480084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the memory block to allocate, in bytes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the allocated memory block if the operation is successful; returns  **NULL**  and sets  **errno**  to a value in the following table if the operation fails or  **nmemb**  or  **size**  is set to  **0**. 

<a name="table1723910217084824"></a>
<table><thead align="left"><tr id="row1909779098084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1076719282084824"><a name="p1076719282084824"></a><a name="p1076719282084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p620611015084824"><a name="p620611015084824"></a><a name="p620611015084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1816389185084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1511006443084824"><a name="p1511006443084824"></a><a name="p1511006443084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p654115894084824"><a name="p654115894084824"></a><a name="p654115894084824"></a>Insufficient memory. </p>
</td>
</tr>
</tbody>
</table>

## free\(\)<a name="gafbedc913aa4651b3c3b4b3aecd9b4711"></a>

```
void free (void * ptr)
```

 **Description:**

Frees the memory space pointed to by  **ptr**. 

**Parameters:**

<a name="table1761268741084824"></a>
<table><thead align="left"><tr id="row1428417629084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2098287643084824"><a name="p2098287643084824"></a><a name="p2098287643084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1240993057084824"><a name="p1240993057084824"></a><a name="p1240993057084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row786158824084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to a memory block previously allocated with <a href="UTILS.md#ga7ac38fce3243a7dcf448301ee9ffd392">malloc</a>, <a href="UTILS.md#ga62b7798461bd461da64c5f9d35feddf7">calloc</a> or <a href="UTILS.md#ga1a6b5e8d2f1c37e5b43e4345586075be">realloc</a>. </td>
</tr>
</tbody>
</table>

## malloc\(\)<a name="ga7ac38fce3243a7dcf448301ee9ffd392"></a>

```
void* malloc (size_t size)
```

 **Description:**

Dynamically allocates a block of uninitialized memory with the specified size. 

The allocated memory can be initialized by calling  [memset\(\)](UTILS.md#gace6ee45c30e71865e6eb635200379db9). 

**Parameters:**

<a name="table1379895203084824"></a>
<table><thead align="left"><tr id="row2105847914084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p876525735084824"><a name="p876525735084824"></a><a name="p876525735084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1952229998084824"><a name="p1952229998084824"></a><a name="p1952229998084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row313102975084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the memory block to allocate, in bytes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the allocated memory block if the operation is successful; returns  **NULL**  and sets  **errno**  to a value in the following table if the operation fails or  **size**  is set to  **0**. 

<a name="table328332018084824"></a>
<table><thead align="left"><tr id="row400900894084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p872494485084824"><a name="p872494485084824"></a><a name="p872494485084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p972866424084824"><a name="p972866424084824"></a><a name="p972866424084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row991326776084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p126078823084824"><a name="p126078823084824"></a><a name="p126078823084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p468080182084824"><a name="p468080182084824"></a><a name="p468080182084824"></a>Insufficient memory. </p>
</td>
</tr>
</tbody>
</table>

## malloc\_usable\_size\(\)<a name="gaa011d7b7bfeba45c8c32e04204a0f565"></a>

```
size_t malloc_usable_size (void * ptr)
```

 **Description:**

Obtains the size of the memory block pointed to by  **ptr**. 

**Parameters:**

<a name="table1743043131084824"></a>
<table><thead align="left"><tr id="row989859810084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1649976715084824"><a name="p1649976715084824"></a><a name="p1649976715084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p67369373084824"><a name="p67369373084824"></a><a name="p67369373084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row993174979084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to a block of memory previously allocated by functions such as <a href="MEM.md#ga7ac38fce3243a7dcf448301ee9ffd392">malloc()</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of usable bytes in the block of allocated memory pointed to by  **ptr**; returns  **0**  if  **ptr**  is  **NULL**. 

**See also:**

[malloc\(\)](MEM.md#ga7ac38fce3243a7dcf448301ee9ffd392)  |  [calloc\(\)](MEM.md#ga62b7798461bd461da64c5f9d35feddf7)  |  [realloc\(\)](MEM.md#ga1a6b5e8d2f1c37e5b43e4345586075be) 

## memalign\(\)<a name="ga6a1c0668b7069bb45fd6e69f301ed5b9"></a>

```
void* memalign (size_t alignment, size_t size )
```

 **Description:**

Allocates a block of memory with the specified size based on the given alignment mode. 

The value of  **alignment**  must be a power of two. 

**Parameters:**

<a name="table705296382084824"></a>
<table><thead align="left"><tr id="row2105050070084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p374394890084824"><a name="p374394890084824"></a><a name="p374394890084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1149260371084824"><a name="p1149260371084824"></a><a name="p1149260371084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row398991037084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alignment</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the alignment size of the allocated memory. </td>
</tr>
<tr id="row1620526765084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the memory block to allocate, in bytes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the allocated memory block if the operation is successful; returns  **NULL**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table504200704084824"></a>
<table><thead align="left"><tr id="row769074179084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p694285548084824"><a name="p694285548084824"></a><a name="p694285548084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1470104389084824"><a name="p1470104389084824"></a><a name="p1470104389084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2071353038084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1601618055084824"><a name="p1601618055084824"></a><a name="p1601618055084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1602758482084824"><a name="p1602758482084824"></a><a name="p1602758482084824"></a>Invalid alignment value (not a power of two). </p>
</td>
</tr>
<tr id="row600253606084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778301301084824"><a name="p778301301084824"></a><a name="p778301301084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1358029795084824"><a name="p1358029795084824"></a><a name="p1358029795084824"></a>Insufficient memory. </p>
</td>
</tr>
</tbody>
</table>

## mmap\(\)<a name="gadcdc6990a7641f7ba05f5dd2a603b992"></a>

```
void* mmap (void * addr, size_t length, int prot, int flags, int fd, off_t offset )
```

 **Description:**

Creates a mapping between the virtual address space of the calling process and a file or device. 

The start address for the mapping is specified by  **addr**, and the length to map is specified by  **length**. The contents of the mapping are initialized starting at  **offset**  with the specified  **length**  in the file referred to by the file descriptor  **fd**. 

**Parameters:**

<a name="table1760177935084824"></a>
<table><thead align="left"><tr id="row1144735203084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p41065528084824"><a name="p41065528084824"></a><a name="p41065528084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p416459231084824"><a name="p416459231084824"></a><a name="p416459231084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1123459131084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the start address of the mapping. If this parameter is <strong id="b1888447448084824"><a name="b1888447448084824"></a><a name="b1888447448084824"></a>NULL</strong>, the kernel determines the address to start. </td>
</tr>
<tr id="row1044286937084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">length</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the mapping, in bytes. </td>
</tr>
<tr id="row804231312084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">prot</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the permission to be granted on the mapping area. The permission to grant must not conflict with the open mode of the file. The value of this parameter is the bitwise OR combination of one or more of the following constants: </td>
</tr>
<tr id="row125352896084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether updates are visible to other processes mapping the same segment, and whether updates are carried through to the underlying file. The following table describes available values. </td>
</tr>
<tr id="row1136156585084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file or device to map. </td>
</tr>
<tr id="row2087112049084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">offset</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the offset into the file where the mapping will start. </td>
</tr>
</tbody>
</table>

<a name="table1702301997084824"></a>
<table><thead align="left"><tr id="row1900618505084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p71442180084824"><a name="p71442180084824"></a><a name="p71442180084824"></a>prot </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p738946941084824"><a name="p738946941084824"></a><a name="p738946941084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1236596454084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p704611308084824"><a name="p704611308084824"></a><a name="p704611308084824"></a>PROT_EXEC </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p982857856084824"><a name="p982857856084824"></a><a name="p982857856084824"></a>Executable </p>
</td>
</tr>
<tr id="row2068377492084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2094305164084824"><a name="p2094305164084824"></a><a name="p2094305164084824"></a>PROT_READ </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1994681800084824"><a name="p1994681800084824"></a><a name="p1994681800084824"></a>Readable </p>
</td>
</tr>
<tr id="row1552594768084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p82873017084824"><a name="p82873017084824"></a><a name="p82873017084824"></a>PROT_WRITE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p718134410084824"><a name="p718134410084824"></a><a name="p718134410084824"></a>Writable </p>
</td>
</tr>
</tbody>
</table>

**Attention:**

If the file mapping is successful,  **fd**  cannot be closed before the mapping is deleted. \(This rule does not conform to the Portable Operating System Interface \(POSIX\) standard. You should pay special attention to this rule.\) 

**Returns:**

Returns the pointer to the address where the mapping is placed if the operation is successful; returns  [MAP\_FAILED](MEM.md#ga8523dcf952f6ff059a3bed717e4f1296)  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1251765745084824"></a>
<table><thead align="left"><tr id="row1004790461084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p162440692084824"><a name="p162440692084824"></a><a name="p162440692084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p31516341084824"><a name="p31516341084824"></a><a name="p31516341084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1314902305084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1578428122084824"><a name="p1578428122084824"></a><a name="p1578428122084824"></a>EACCES </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p856722621084824"><a name="p856722621084824"></a><a name="p856722621084824"></a>The file descriptor specified by <strong id="b632838587084824"><a name="b632838587084824"></a><a name="b632838587084824"></a>fd</strong> refers to a non-regular file. The file descriptor specified by <strong id="b1796573722084824"><a name="b1796573722084824"></a><a name="b1796573722084824"></a>fd</strong> is invalid. <a href="MEM.md#ga57028962c2a7c0c802ca6613492f2ef3">MAP_SHARED</a> and <a href="MEM.md#ga2a79c8ceefb8fc25a940ae07a3d94429">PROT_WRITE</a> are specified, but the file identified by <strong id="b670603633084824"><a name="b670603633084824"></a><a name="b670603633084824"></a>fd</strong> is not opened in <a href="FS.md#gabb0586253488ee61072b73557eeb873b">O_RDWR</a> mode. <a href="MEM.md#ga2a79c8ceefb8fc25a940ae07a3d94429">PROT_WRITE</a> is specified, but the file is append-only. </p>
</td>
</tr>
<tr id="row2077208645084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1952556408084824"><a name="p1952556408084824"></a><a name="p1952556408084824"></a>EBADF </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p560535112084824"><a name="p560535112084824"></a><a name="p560535112084824"></a>The file descriptor specified by <strong id="b1328240369084824"><a name="b1328240369084824"></a><a name="b1328240369084824"></a>fd</strong> is invalid, and <a href="MEM.md#gae4f86bff73414c5fc08c058f957212f0">MAP_ANONYMOUS</a> is not specified in <strong id="b140599636084824"><a name="b140599636084824"></a><a name="b140599636084824"></a>flags</strong>. </p>
</td>
</tr>
<tr id="row176716615084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1316943927084824"><a name="p1316943927084824"></a><a name="p1316943927084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1753914867084824"><a name="p1753914867084824"></a><a name="p1753914867084824"></a>The length and offset are too large, <strong id="b708940394084824"><a name="b708940394084824"></a><a name="b708940394084824"></a>addr</strong> is not page-aligned, or the length is <strong id="b1312543172084824"><a name="b1312543172084824"></a><a name="b1312543172084824"></a>0</strong>. Neither <a href="MEM.md#ga57028962c2a7c0c802ca6613492f2ef3">MAP_SHARED</a> nor <a href="MEM.md#gae4f86bff73414c5fc08c058f957212f0">MAP_ANONYMOUS</a> is specified in <strong id="b1286058706084824"><a name="b1286058706084824"></a><a name="b1286058706084824"></a>flags</strong>, or both are specified. </p>
</td>
</tr>
<tr id="row1535572417084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1601797353084824"><a name="p1601797353084824"></a><a name="p1601797353084824"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p735532956084824"><a name="p735532956084824"></a><a name="p735532956084824"></a>The file identified by <strong id="b1996734214084824"><a name="b1996734214084824"></a><a name="b1996734214084824"></a>fd</strong> has been locked. </p>
</td>
</tr>
<tr id="row924132953084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p896350896084824"><a name="p896350896084824"></a><a name="p896350896084824"></a>ENFILE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2077074812084824"><a name="p2077074812084824"></a><a name="p2077074812084824"></a>The total number of open files exceeds the system limit. </p>
</td>
</tr>
<tr id="row1226746846084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1634184362084824"><a name="p1634184362084824"></a><a name="p1634184362084824"></a>ENODEV </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2018214059084824"><a name="p2018214059084824"></a><a name="p2018214059084824"></a>The file identified by <strong id="b261134974084824"><a name="b261134974084824"></a><a name="b261134974084824"></a>fd</strong> does not support memory mapping. </p>
</td>
</tr>
<tr id="row1402815716084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p875725507084824"><a name="p875725507084824"></a><a name="p875725507084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646097757084824"><a name="p1646097757084824"></a><a name="p1646097757084824"></a>Insufficient memory. </p>
</td>
</tr>
<tr id="row1262790967084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1826579547084824"><a name="p1826579547084824"></a><a name="p1826579547084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1636609615084824"><a name="p1636609615084824"></a><a name="p1636609615084824"></a><a href="MEM.md#ga77848f068638e916c72cd543f5ecb815">PROT_EXEC</a> is specified in <strong id="b67696065084824"><a name="b67696065084824"></a><a name="b67696065084824"></a>prot</strong>, but the mapped area belongs to a file on a file system that was mounted non-executable, or the file seal does not allow this operation. </p>
</td>
</tr>
</tbody>
</table>

## mprotect\(\)<a name="gaa0752189f14ca11ba413fc944ae08b9c"></a>

```
int mprotect (void * addr, size_t len, int prot )
```

 **Description:**

Sets protection attributes for the memory pages contained in the memory region starting from  **addr**  with the specified length. 

The address specified by  **addr**  must be page-aligned. If the process attempts to access memory in a manner that violates the protection attributes, an access exception will occur, and the process will be terminated. 

**Parameters:**

<a name="table430136513084824"></a>
<table><thead align="left"><tr id="row146751109084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1500697356084824"><a name="p1500697356084824"></a><a name="p1500697356084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1679724061084824"><a name="p1679724061084824"></a><a name="p1679724061084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row142387357084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the start address of the memory region to modify, which must be a multiple of the page size. </td>
</tr>
<tr id="row2053250008084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the memory region to modify, in bytes. </td>
</tr>
<tr id="row2053527755084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">prot</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the permission of the memory region to modify, which can be a bitwise OR combination of one or more of the constants listed in <strong id="b1416139360084824"><a name="b1416139360084824"></a><a name="b1416139360084824"></a>prot</strong>. </td>
</tr>
</tbody>
</table>

<a name="table1761944556084824"></a>
<table><thead align="left"><tr id="row528869870084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1507549702084824"><a name="p1507549702084824"></a><a name="p1507549702084824"></a>prot </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p95695648084824"><a name="p95695648084824"></a><a name="p95695648084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1711256671084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p725069733084824"><a name="p725069733084824"></a><a name="p725069733084824"></a>PROT_EXEC </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1877546880084824"><a name="p1877546880084824"></a><a name="p1877546880084824"></a>Executable </p>
</td>
</tr>
<tr id="row900880869084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1857641088084824"><a name="p1857641088084824"></a><a name="p1857641088084824"></a>PROT_READ </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p266914823084824"><a name="p266914823084824"></a><a name="p266914823084824"></a>Readable </p>
</td>
</tr>
<tr id="row500168876084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p361813991084824"><a name="p361813991084824"></a><a name="p361813991084824"></a>PROT_WRITE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p44614840084824"><a name="p44614840084824"></a><a name="p44614840084824"></a>Writable </p>
</td>
</tr>
<tr id="row37722607084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1932735803084824"><a name="p1932735803084824"></a><a name="p1932735803084824"></a>PROT_NONE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1584720201084824"><a name="p1584720201084824"></a><a name="p1584720201084824"></a>Not accessible </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table49067707084824"></a>
<table><thead align="left"><tr id="row855231907084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1298390134084824"><a name="p1298390134084824"></a><a name="p1298390134084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1957511535084824"><a name="p1957511535084824"></a><a name="p1957511535084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row423287013084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1437697575084824"><a name="p1437697575084824"></a><a name="p1437697575084824"></a>EACCES </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508245094084824"><a name="p508245094084824"></a><a name="p508245094084824"></a>The memory region cannot be granted the specified permission. This error can occur, for example, when you use <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap</a> to map a file with <strong id="b141620926084824"><a name="b141620926084824"></a><a name="b141620926084824"></a>prot</strong> set to <a href="MEM.md#ga15bf68ce8b590838b3a5c0b639d8d519">PROT_READ</a> and then use this function to set <strong id="b75280781084824"><a name="b75280781084824"></a><a name="b75280781084824"></a>prot</strong> to <a href="MEM.md#ga2a79c8ceefb8fc25a940ae07a3d94429">PROT_WRITE</a>. </p>
</td>
</tr>
<tr id="row2065474637084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p322692356084824"><a name="p322692356084824"></a><a name="p322692356084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p639129453084824"><a name="p639129453084824"></a><a name="p639129453084824"></a><strong id="b1791460719084824"><a name="b1791460719084824"></a><a name="b1791460719084824"></a>addr</strong> is an invalid pointer or it points to an address that is not a multiple of the page size. </p>
</td>
</tr>
<tr id="row396747212084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1958940402084824"><a name="p1958940402084824"></a><a name="p1958940402084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p309922732084824"><a name="p309922732084824"></a><a name="p309922732084824"></a>Internal kernel structures cannot be allocated due to insufficient memory, or addresses in the specified range are invalid for the address space of the process. The total number of mappings with different attributes exceeds the maximum number allowed by the system if the protection attribute of the memory region is changed. </p>
</td>
</tr>
</tbody>
</table>

## mremap\(\)<a name="ga1b5acd27009fbbf05d18e90640f6ef64"></a>

```
void* mremap (void * old_address, size_t old_size, size_t new_size, int flags,  ... )
```

 **Description:**

Remaps a virtual memory region. 

This function expands or shrinks an existing memory mapping, and may also move the mapping at the same time depending on the settings of  **flags**  and the available virtual address space. 

**Parameters:**

<a name="table416588060084824"></a>
<table><thead align="left"><tr id="row1861704842084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p688509121084824"><a name="p688509121084824"></a><a name="p688509121084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1588232327084824"><a name="p1588232327084824"></a><a name="p1588232327084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1435662785084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">old_address</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the old address of the virtual memory region to expand or shrink. </td>
</tr>
<tr id="row344935736084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">old_size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the old size of the virtual memory region. </td>
</tr>
<tr id="row54523210084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">new_size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the requested size of the virtual memory region after the expansion or shrinking. </td>
</tr>
<tr id="row1067857587084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">flags</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether the existing memory can be mapped to a new or specified address. </td>
</tr>
<tr id="row1616238492084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">new_address</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the new address of the virtual memory region. This parameter is optional and is used when <a href="MEM.md#ga689fc9cb8e5f54526471e67573624af9">MREMAP_FIXED</a> is specified in <strong id="b920506898084824"><a name="b920506898084824"></a><a name="b920506898084824"></a>flags</strong>. </td>
</tr>
</tbody>
</table>

<a name="table1995686045084824"></a>
<table><thead align="left"><tr id="row1086692365084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p981293482084824"><a name="p981293482084824"></a><a name="p981293482084824"></a>flags </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p339618865084824"><a name="p339618865084824"></a><a name="p339618865084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1715840691084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p866719931084824"><a name="p866719931084824"></a><a name="p866719931084824"></a>MREMAP_MAYMOVE </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9285359084824"><a name="p9285359084824"></a><a name="p9285359084824"></a>By default, if no enough space is available to expand a mapping at its current location, the operation fails. If this flag is specified, the kernel is allowed to relocate the mapping to a new virtual address when necessary. </p>
</td>
</tr>
<tr id="row883694804084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p123854790084824"><a name="p123854790084824"></a><a name="p123854790084824"></a>MREMAP_FIXED </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p621048489084824"><a name="p621048489084824"></a><a name="p621048489084824"></a>If this flag is specified, the <strong id="b662788196084824"><a name="b662788196084824"></a><a name="b662788196084824"></a>new_address</strong> parameter is enabled in this function and the memory is mapped to a new address. This flag must be used together with <a href="MEM.md#ga979a9c42ee569172c2017c522c17a0b1">MREMAP_MAYMOVE</a>. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the new mapping address if the operation is successful; returns  [MAP\_FAILED](MEM.md#ga8523dcf952f6ff059a3bed717e4f1296)  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table610736912084824"></a>
<table><thead align="left"><tr id="row1614664840084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p741837946084824"><a name="p741837946084824"></a><a name="p741837946084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1468225809084824"><a name="p1468225809084824"></a><a name="p1468225809084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1905722928084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1098215412084824"><a name="p1098215412084824"></a><a name="p1098215412084824"></a>EAGAIN </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1010236136084824"><a name="p1010236136084824"></a><a name="p1010236136084824"></a>The memory segment to expand is locked. </p>
</td>
</tr>
<tr id="row1631499122084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1831024344084824"><a name="p1831024344084824"></a><a name="p1831024344084824"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p856658388084824"><a name="p856658388084824"></a><a name="p856658388084824"></a>Some memory addresses in the range from <strong id="b1221375528084824"><a name="b1221375528084824"></a><a name="b1221375528084824"></a>old_address</strong> to <strong id="b541846672084824"><a name="b541846672084824"></a><a name="b541846672084824"></a>old_address</strong>+<strong id="b934746734084824"><a name="b934746734084824"></a><a name="b934746734084824"></a>old_size</strong> are invalid for this process. </p>
</td>
</tr>
<tr id="row1246163529084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p935530155084824"><a name="p935530155084824"></a><a name="p935530155084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2122862213084824"><a name="p2122862213084824"></a><a name="p2122862213084824"></a><strong id="b1360109993084824"><a name="b1360109993084824"></a><a name="b1360109993084824"></a>old_address</strong> is not a multiple of the page size, or a value other than <a href="MEM.md#ga979a9c42ee569172c2017c522c17a0b1">MREMAP_MAYMOVE</a> and <a href="MEM.md#ga689fc9cb8e5f54526471e67573624af9">MREMAP_FIXED</a> is specified in <strong id="b1318787723084824"><a name="b1318787723084824"></a><a name="b1318787723084824"></a>flags</strong>. <strong id="b150106896084824"><a name="b150106896084824"></a><a name="b150106896084824"></a>new_size</strong> is <strong id="b123317605084824"><a name="b123317605084824"></a><a name="b123317605084824"></a>0</strong>, <strong id="b357119409084824"><a name="b357119409084824"></a><a name="b357119409084824"></a>new_size</strong> or <strong id="b443296510084824"><a name="b443296510084824"></a><a name="b443296510084824"></a>new_address</strong> is invalid, or <a href="MEM.md#ga689fc9cb8e5f54526471e67573624af9">MREMAP_FIXED</a> is specified in <strong id="b773963343084824"><a name="b773963343084824"></a><a name="b773963343084824"></a>flags</strong> without also specifying <a href="MEM.md#ga979a9c42ee569172c2017c522c17a0b1">MREMAP_MAYMOVE</a>. <strong id="b824446774084824"><a name="b824446774084824"></a><a name="b824446774084824"></a>old_size</strong> is <strong id="b36583417084824"><a name="b36583417084824"></a><a name="b36583417084824"></a>0</strong> but <strong id="b792249913084824"><a name="b792249913084824"></a><a name="b792249913084824"></a>old_address</strong> does not point to a shared memory mapping; <strong id="b368982241084824"><a name="b368982241084824"></a><a name="b368982241084824"></a>old_size</strong> is <strong id="b147470632084824"><a name="b147470632084824"></a><a name="b147470632084824"></a>0</strong> but <a href="MEM.md#ga979a9c42ee569172c2017c522c17a0b1">MREMAP_MAYMOVE</a> is not specified in <strong id="b528437867084824"><a name="b528437867084824"></a><a name="b528437867084824"></a>flags</strong>; or the new memory address range specified by <strong id="b1861683658084824"><a name="b1861683658084824"></a><a name="b1861683658084824"></a>new_address</strong> and <strong id="b745998566084824"><a name="b745998566084824"></a><a name="b745998566084824"></a>new_size</strong> overlaps the old memory address range specified by <strong id="b1707792081084824"><a name="b1707792081084824"></a><a name="b1707792081084824"></a>old_address</strong> and <strong id="b71946155084824"><a name="b71946155084824"></a><a name="b71946155084824"></a>old_size</strong>. </p>
</td>
</tr>
<tr id="row1489241317084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p315703486084824"><a name="p315703486084824"></a><a name="p315703486084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1247293176084824"><a name="p1247293176084824"></a><a name="p1247293176084824"></a>Insufficient memory. </p>
</td>
</tr>
</tbody>
</table>

## munmap\(\)<a name="ga1343e4aa663c9e8bb7d1b16d367f0b08"></a>

```
int munmap (void * addr, size_t length )
```

 **Description:**

Removes all mappings for the specified virtual address space. 

After all mappings are removed, any references to addresses within the specified range will generate invalid memory references. The memory region will also be automatically unmapped when the process is terminated. Closing the file descriptor does not remove mappings from the region. 

**Parameters:**

<a name="table1462327341084824"></a>
<table><thead align="left"><tr id="row1834191158084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p950961674084824"><a name="p950961674084824"></a><a name="p950961674084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1161576643084824"><a name="p1161576643084824"></a><a name="p1161576643084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row563309834084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the start address of the memory region to unmap, which is the return value of <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </td>
</tr>
<tr id="row1244196673084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">length</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the address range to unmap, which should be the length specified in <a href="MEM.md#gadcdc6990a7641f7ba05f5dd2a603b992">mmap()</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1713195712084824"></a>
<table><thead align="left"><tr id="row1051785061084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1142412152084824"><a name="p1142412152084824"></a><a name="p1142412152084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p111268583084824"><a name="p111268583084824"></a><a name="p111268583084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1409171310084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p498815665084824"><a name="p498815665084824"></a><a name="p498815665084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311877936084824"><a name="p311877936084824"></a><a name="p311877936084824"></a>Invalid input parameters. </p>
</td>
</tr>
</tbody>
</table>

## realloc\(\)<a name="ga1a6b5e8d2f1c37e5b43e4345586075be"></a>

```
void* realloc (void * ptr, size_t size )
```

 **Description:**

Changes the size of a previously allocated memory block pointed to by  **ptr**  to the specified size. 

The contents of the memory block will be retained from the beginning of the memory pointed to by  **ptr**  to the lesser of the old and new sizes. If the new size is larger than the old size, the added memory portion will not be initialized. The behavior of this function varies depending on the input parameters: 

**Parameters:**

<a name="table872207585084824"></a>
<table><thead align="left"><tr id="row1927656821084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1865161199084824"><a name="p1865161199084824"></a><a name="p1865161199084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p120360343084824"><a name="p120360343084824"></a><a name="p120360343084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1567265769084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to a memory block previously allocated with <a href="UTILS.md#ga7ac38fce3243a7dcf448301ee9ffd392">malloc</a>, <a href="UTILS.md#ga62b7798461bd461da64c5f9d35feddf7">calloc</a> or <a href="UTILS.md#ga1a6b5e8d2f1c37e5b43e4345586075be">realloc</a>. </td>
</tr>
<tr id="row2078597700084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the new size for the memory block, in bytes. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the new memory block if the operation is successful; returns  **NULL**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1988597582084824"></a>
<table><thead align="left"><tr id="row1334015417084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1890642150084824"><a name="p1890642150084824"></a><a name="p1890642150084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p7580352084824"><a name="p7580352084824"></a><a name="p7580352084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2009088708084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p21956588084824"><a name="p21956588084824"></a><a name="p21956588084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p458648466084824"><a name="p458648466084824"></a><a name="p458648466084824"></a>Insufficient memory. </p>
</td>
</tr>
</tbody>
</table>

## shmat\(\)<a name="gac56f61130bf1ddd88ecd6a2e87b4c5cb"></a>

```
void* shmat (int shmid, const void * shmaddr, int shmflg )
```

 **Description:**

Attaches the shared memory segment identified by  **shmid**  to the address space of the current process. 

**Parameters:**

<a name="table2064980321084824"></a>
<table><thead align="left"><tr id="row137299512084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p900208482084824"><a name="p900208482084824"></a><a name="p900208482084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1784764649084824"><a name="p1784764649084824"></a><a name="p1784764649084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row432690362084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">shmid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the shared memory segment to attach, which is obtained by <a href="MEM.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </td>
</tr>
<tr id="row1119446237084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">shmaddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the space address of the current process to attach. If this parameter is <strong id="b295344321084824"><a name="b295344321084824"></a><a name="b295344321084824"></a>NULL</strong>, the system chooses an unused address to attach. </td>
</tr>
<tr id="row1485293988084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">shmflg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the attribute of the shared memory segment to attach, which is the bitwise OR combination of one or more of the following flags: </td>
</tr>
</tbody>
</table>

<a name="table1279999234084824"></a>
<table><thead align="left"><tr id="row180017405084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1119586346084824"><a name="p1119586346084824"></a><a name="p1119586346084824"></a>shmflg </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1014878898084824"><a name="p1014878898084824"></a><a name="p1014878898084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1946813159084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1266293264084824"><a name="p1266293264084824"></a><a name="p1266293264084824"></a>SHM_RND </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1880368780084824"><a name="p1880368780084824"></a><a name="p1880368780084824"></a>Round the attached address. If <strong id="b1211531777084824"><a name="b1211531777084824"></a><a name="b1211531777084824"></a>shmaddr</strong> is not <strong id="b342824011084824"><a name="b342824011084824"></a><a name="b342824011084824"></a>NULL</strong> and <a href="MEM.md#ga4ae5f621aa1333d9d5962c3e9d674a90">SHM_RND</a> is specified in <strong id="b612589726084824"><a name="b612589726084824"></a><a name="b612589726084824"></a>shmflg</strong>, the address is rounded down to the nearest multiple of <a href="MEM.md#ga1f422a47c416c67470e3a0fb8b7529d8">SHMLBA</a>. </p>
</td>
</tr>
<tr id="row1744650195084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p414410975084824"><a name="p414410975084824"></a><a name="p414410975084824"></a>SHM_EXEC </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p15429084084824"><a name="p15429084084824"></a><a name="p15429084084824"></a>Allow the contents of the attached shared memory segment to be executable. </p>
</td>
</tr>
<tr id="row346224294084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997725377084824"><a name="p997725377084824"></a><a name="p997725377084824"></a>SHM_RDONLY </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p53244286084824"><a name="p53244286084824"></a><a name="p53244286084824"></a>Set the contents of the attached shared memory segment to be read-only. </p>
</td>
</tr>
<tr id="row2035291885084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1025819348084824"><a name="p1025819348084824"></a><a name="p1025819348084824"></a>SHM_REMAP </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p868589381084824"><a name="p868589381084824"></a><a name="p868589381084824"></a>Replace any existing mapping in the address range starting at <strong id="b383597274084824"><a name="b383597274084824"></a><a name="b383597274084824"></a>shmaddr</strong> and continuing for the size of the segment during the current memory mapping. When <a href="MEM.md#gab652a1a4737f9118a64a8fb74084ef7d">SHM_REMAP</a> is not specified, an <strong id="b274217121084824"><a name="b274217121084824"></a><a name="b274217121084824"></a>EINVAL</strong> error will be returned if a mapping exists in the address range. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the address of the attached shared memory segment if the operation is successful; returns  **\(void \*\)-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1311732681084824"></a>
<table><thead align="left"><tr id="row619339162084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p705682532084824"><a name="p705682532084824"></a><a name="p705682532084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1490230019084824"><a name="p1490230019084824"></a><a name="p1490230019084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row2121358743084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1786882567084824"><a name="p1786882567084824"></a><a name="p1786882567084824"></a>EACCES </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1105511137084824"><a name="p1105511137084824"></a><a name="p1105511137084824"></a>The current process does not have the required permission on the requested mapping type. </p>
</td>
</tr>
<tr id="row834278449084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2123020549084824"><a name="p2123020549084824"></a><a name="p2123020549084824"></a>EIDRM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1076957489084824"><a name="p1076957489084824"></a><a name="p1076957489084824"></a>The shared memory segment specified by <strong id="b545854162084824"><a name="b545854162084824"></a><a name="b545854162084824"></a>shmid</strong> has been removed. </p>
</td>
</tr>
<tr id="row993421793084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1027133495084824"><a name="p1027133495084824"></a><a name="p1027133495084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1322863348084824"><a name="p1322863348084824"></a><a name="p1322863348084824"></a>The value of <strong id="b1900799810084824"><a name="b1900799810084824"></a><a name="b1900799810084824"></a>shmid</strong> is invalid. <strong id="b1491040353084824"><a name="b1491040353084824"></a><a name="b1491040353084824"></a>shmaddr</strong> is not aligned (not page-aligned and <a href="MEM.md#ga4ae5f621aa1333d9d5962c3e9d674a90">SHM_RND</a> is not specified) or its value is invalid. <a href="MEM.md#gab652a1a4737f9118a64a8fb74084ef7d">SHM_REMAP</a> is specified, but <strong id="b1403660740084824"><a name="b1403660740084824"></a><a name="b1403660740084824"></a>shmaddr</strong> is <strong id="b1867642618084824"><a name="b1867642618084824"></a><a name="b1867642618084824"></a>NULL</strong>. </p>
</td>
</tr>
<tr id="row468066256084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p775175215084824"><a name="p775175215084824"></a><a name="p775175215084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1968392780084824"><a name="p1968392780084824"></a><a name="p1968392780084824"></a>No page tables can be allocated. </p>
</td>
</tr>
</tbody>
</table>

## shmctl\(\)<a name="gab2cfe9a9370d4c74b485876260e2e0fe"></a>

```
int shmctl (int shmid, int cmd, struct [shmid_ds](shmid_ds.md) * buf )
```

 **Description:**

Performs a control operation specified by the  **cmd**  parameter on the shared memory segment identified by  **shmid**. 

**Parameters:**

<a name="table1316377539084824"></a>
<table><thead align="left"><tr id="row203572680084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2030886541084824"><a name="p2030886541084824"></a><a name="p2030886541084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1170762244084824"><a name="p1170762244084824"></a><a name="p1170762244084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1416455454084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">shmid</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Identifies the shared memory segment to attach, which is obtained by <a href="MEM.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </td>
</tr>
<tr id="row1607732691084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cmd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the control operation to perform. The following table describes available values. </td>
</tr>
<tr id="row1047251534084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for storing the information to set or obtain. </td>
</tr>
</tbody>
</table>

<a name="table1707650812084824"></a>
<table><thead align="left"><tr id="row2092420991084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1727103972084824"><a name="p1727103972084824"></a><a name="p1727103972084824"></a>cmd </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1189504295084824"><a name="p1189504295084824"></a><a name="p1189504295084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row420247281084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1366084928084824"><a name="p1366084928084824"></a><a name="p1366084928084824"></a>IPC_STAT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p897996284084824"><a name="p897996284084824"></a><a name="p897996284084824"></a>Copy information from the kernel data structure associated with the shared memory segment identified by <strong id="b798003618084824"><a name="b798003618084824"></a><a name="b798003618084824"></a>shmid</strong> into the <a href="shmid_ds.md">shmid_ds</a> structure pointed to by <strong id="b329285522084824"><a name="b329285522084824"></a><a name="b329285522084824"></a>buf</strong>. </p>
</td>
</tr>
<tr id="row12594795084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1463733136084824"><a name="p1463733136084824"></a><a name="p1463733136084824"></a>SHM_STAT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931957887084824"><a name="p931957887084824"></a><a name="p931957887084824"></a>Return a <a href="shmid_ds.md">shmid_ds</a> data structure. When <a href="MEM.md#ga2e0f8c5b0fafab9f2602d19588d03e95">SHM_STAT</a> is specified, <strong id="b791881216084824"><a name="b791881216084824"></a><a name="b791881216084824"></a>shmid</strong> does not identify a shared memory segment. Instead, it indicates the index to the kernel's internal array that maintains information about all shared memory segments. </p>
</td>
</tr>
<tr id="row914941770084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p69608613084824"><a name="p69608613084824"></a><a name="p69608613084824"></a>IPC_SET </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181223418084824"><a name="p181223418084824"></a><a name="p181223418084824"></a>Write the values of some fields in the <a href="shmid_ds.md">shmid_ds</a> data structure pointed to by <strong id="b1404012142084824"><a name="b1404012142084824"></a><a name="b1404012142084824"></a>buf</strong> to the kernel data structure associated with the specified shared memory segment, updating also its <strong id="b1768987797084824"><a name="b1768987797084824"></a><a name="b1768987797084824"></a>shm_ctime</strong>member. The following fields can be modified: <strong id="b743359334084824"><a name="b743359334084824"></a><a name="b743359334084824"></a>shm_perm.uid</strong>, <strong id="b803074073084824"><a name="b803074073084824"></a><a name="b803074073084824"></a>shm_perm.gid</strong>, and <strong id="b928792975084824"><a name="b928792975084824"></a><a name="b928792975084824"></a>shm_perm.mode</strong>. </p>
</td>
</tr>
<tr id="row1901568975084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1526696326084824"><a name="p1526696326084824"></a><a name="p1526696326084824"></a>IPC_RMID </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1288617317084824"><a name="p1288617317084824"></a><a name="p1288617317084824"></a>Mark the shared memory segment to be destroyed. </p>
</td>
</tr>
<tr id="row351995788084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p855640909084824"><a name="p855640909084824"></a><a name="p855640909084824"></a>IPC_INFO </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p666218134084824"><a name="p666218134084824"></a><a name="p666218134084824"></a>Return information about system-wide shared memory limits and parameters in the structure pointed to by <strong id="b1075871707084824"><a name="b1075871707084824"></a><a name="b1075871707084824"></a>buf</strong>. The returned structure is of the <a href="shminfo.md">shminfo</a> type, and a cast is required. </p>
</td>
</tr>
<tr id="row1749226637084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1086489666084824"><a name="p1086489666084824"></a><a name="p1086489666084824"></a>SHM_INFO </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1527888382084824"><a name="p1527888382084824"></a><a name="p1527888382084824"></a>Return a <a href="shm_info.md">shm_info</a> structure that contains information about system resources consumed by the specified shared memory segment. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1331723913084824"></a>
<table><thead align="left"><tr id="row242553002084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p700427241084824"><a name="p700427241084824"></a><a name="p700427241084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2092083090084824"><a name="p2092083090084824"></a><a name="p2092083090084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row992073766084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1325758842084824"><a name="p1325758842084824"></a><a name="p1325758842084824"></a>EACCES </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1775292264084824"><a name="p1775292264084824"></a><a name="p1775292264084824"></a><a href="IPC.md#ga16a91ee69c3cb6bfec425e1bfd5edd18">IPC_STAT</a> or <a href="MEM.md#ga2e0f8c5b0fafab9f2602d19588d03e95">SHM_STAT</a> is specified in <strong id="b593896170084824"><a name="b593896170084824"></a><a name="b593896170084824"></a>cmb</strong>, but the <strong id="b1716049580084824"><a name="b1716049580084824"></a><a name="b1716049580084824"></a>mode</strong> field in <strong id="b487297955084824"><a name="b487297955084824"></a><a name="b487297955084824"></a>shm_perm</strong> does not allow any read operation on the shared memory segment identified by <strong id="b2117454426084824"><a name="b2117454426084824"></a><a name="b2117454426084824"></a>shmid</strong>. </p>
</td>
</tr>
<tr id="row1675851456084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p442158682084824"><a name="p442158682084824"></a><a name="p442158682084824"></a>EFAULT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2142526176084824"><a name="p2142526176084824"></a><a name="p2142526176084824"></a><a href="MEM.md#ga2e0f8c5b0fafab9f2602d19588d03e95">SHM_STAT</a> or <a href="IPC.md#ga16a91ee69c3cb6bfec425e1bfd5edd18">IPC_STAT</a> is specified in <strong id="b254873317084824"><a name="b254873317084824"></a><a name="b254873317084824"></a>cmd</strong>, but the address pointed to by <strong id="b1247998650084824"><a name="b1247998650084824"></a><a name="b1247998650084824"></a>buf</strong> is not accessible. </p>
</td>
</tr>
<tr id="row1631515084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p203026992084824"><a name="p203026992084824"></a><a name="p203026992084824"></a>EIDRM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2089393110084824"><a name="p2089393110084824"></a><a name="p2089393110084824"></a><strong id="b1069706757084824"><a name="b1069706757084824"></a><a name="b1069706757084824"></a>shmid</strong> points to a removed shared memory segment. </p>
</td>
</tr>
<tr id="row1882413797084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907473414084824"><a name="p907473414084824"></a><a name="p907473414084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p214203822084824"><a name="p214203822084824"></a><a name="p214203822084824"></a>The value of <strong id="b1160460044084824"><a name="b1160460044084824"></a><a name="b1160460044084824"></a>shmid</strong> or <strong id="b673592687084824"><a name="b673592687084824"></a><a name="b673592687084824"></a>cmd</strong> is invalid. When <a href="MEM.md#ga2e0f8c5b0fafab9f2602d19588d03e95">SHM_STAT</a> is specified in <strong id="b237288821084824"><a name="b237288821084824"></a><a name="b237288821084824"></a>cmd</strong>, the value is considered invalid if the index specified by <strong id="b2058380256084824"><a name="b2058380256084824"></a><a name="b2058380256084824"></a>shmid</strong> refers to an unused array slot. </p>
</td>
</tr>
<tr id="row1288045442084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1090958587084824"><a name="p1090958587084824"></a><a name="p1090958587084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p693285326084824"><a name="p693285326084824"></a><a name="p693285326084824"></a>No page tables can be allocated. </p>
</td>
</tr>
<tr id="row628512434084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p723634282084824"><a name="p723634282084824"></a><a name="p723634282084824"></a>EPERM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1127982496084824"><a name="p1127982496084824"></a><a name="p1127982496084824"></a><a href="IPC.md#ga1f1cdce55426e50878b1c71a4fc67a41">IPC_SET</a> or <a href="IPC.md#ga752c83032a7bec60c904d97508ea4599">IPC_RMID</a> is attempted, but the effective user ID of the calling process is not that of the creator or the owner, and the process is not privileged. </p>
</td>
</tr>
</tbody>
</table>

## shmdt\(\)<a name="ga934738fcc6c27c0d45cff9bb8cc38a7f"></a>

```
int shmdt (const void * shmaddr)
```

 **Description:**

Detaches the shared memory segment attached to the address pointed to by  **shmaddr**  from the address space of the calling process. 

**Parameters:**

<a name="table2110210884084824"></a>
<table><thead align="left"><tr id="row1449119520084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1791656116084824"><a name="p1791656116084824"></a><a name="p1791656116084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2084220491084824"><a name="p2084220491084824"></a><a name="p2084220491084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row499600790084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">shmaddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the address of the shared memory segment to detach. The value of this parameter should be the pointer previously returned by <a href="MEM.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat()</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table1681613207084824"></a>
<table><thead align="left"><tr id="row750779876084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p873966071084824"><a name="p873966071084824"></a><a name="p873966071084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p745276177084824"><a name="p745276177084824"></a><a name="p745276177084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1784720307084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1766917195084824"><a name="p1766917195084824"></a><a name="p1766917195084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1289743491084824"><a name="p1289743491084824"></a><a name="p1289743491084824"></a>No shared memory segment is attached to <strong id="b1053507374084824"><a name="b1053507374084824"></a><a name="b1053507374084824"></a>shmaddr</strong>, or <strong id="b579154245084824"><a name="b579154245084824"></a><a name="b579154245084824"></a>shmaddr</strong> is not aligned. </p>
</td>
</tr>
</tbody>
</table>

## shmget\(\)<a name="ga23e346182fc10c5286f37213e09fefb2"></a>

```
int shmget (key_t key, size_t size, int shmflg )
```

 **Description:**

Obtains or creates a shared memory segment with the specified size based on the ID specified by  **key**. 

If the shared memory segment associated with  **key**  does not exist and  [IPC\_CREAT](IPC.md#gace43f23fcb66ddaad964bb8ea8de6e9c)  is specified in  **shmflg**  or if  **key**  has the value  [IPC\_PRIVATE](IPC.md#gae2b9b856a4a657c250b0b2e1cc0835d9), this function creates a shared memory segment with the size equal to the value of  **size**  rounded up to a multiple of  [PAGE\_SIZE](UTILS.md#ga7d467c1d283fdfa1f2081ba1e0d01b6e). 

**Parameters:**

<a name="table1490606037084824"></a>
<table><thead align="left"><tr id="row1546324133084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p448576925084824"><a name="p448576925084824"></a><a name="p448576925084824"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1391873123084824"><a name="p1391873123084824"></a><a name="p1391873123084824"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2073671516084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the key of the shared memory segment. </td>
</tr>
<tr id="row782211243084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the shared memory segment to create. The actual size is rounded up to a multiple of <a href="UTILS.md#ga7d467c1d283fdfa1f2081ba1e0d01b6e">PAGE_SIZE</a>. </td>
</tr>
<tr id="row1254519898084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">shmflg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the attribute of the shared memory segment, which is the bitwise OR combination of one or more of the following flags: </td>
</tr>
</tbody>
</table>

<a name="table569404930084824"></a>
<table><thead align="left"><tr id="row245435762084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1101811589084824"><a name="p1101811589084824"></a><a name="p1101811589084824"></a>shmflg </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p511403142084824"><a name="p511403142084824"></a><a name="p511403142084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1505603362084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1733409120084824"><a name="p1733409120084824"></a><a name="p1733409120084824"></a>IPC_CREAT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1924494101084824"><a name="p1924494101084824"></a><a name="p1924494101084824"></a>Create a new shared memory segment. If this flag is not specified, this function will find the segment with the specified <strong id="b360153636084824"><a name="b360153636084824"></a><a name="b360153636084824"></a>key</strong> and check to see whether the user has permission to access the segment. </p>
</td>
</tr>
<tr id="row1154408837084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p264321520084824"><a name="p264321520084824"></a><a name="p264321520084824"></a>IPC_EXCL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1147857429084824"><a name="p1147857429084824"></a><a name="p1147857429084824"></a>Used together with <a href="IPC.md#gace43f23fcb66ddaad964bb8ea8de6e9c">IPC_CREAT</a> to ensure that this function is called to create a shared memory segment. The calling fails if the segment already exists. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the ID of the shared memory segment if the operation is successful; returns  **-1**  and sets  **errno**  to a value in the following table if the operation fails. 

<a name="table446512980084824"></a>
<table><thead align="left"><tr id="row1404302415084824"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1939772463084824"><a name="p1939772463084824"></a><a name="p1939772463084824"></a>errno </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p88608708084824"><a name="p88608708084824"></a><a name="p88608708084824"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row578746256084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1662803927084824"><a name="p1662803927084824"></a><a name="p1662803927084824"></a>EACCES </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1853521139084824"><a name="p1853521139084824"></a><a name="p1853521139084824"></a>The current process does not have the permission to obtain the specified shared memory segment. </p>
</td>
</tr>
<tr id="row376957746084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p987413098084824"><a name="p987413098084824"></a><a name="p987413098084824"></a>EEXIST </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1727493393084824"><a name="p1727493393084824"></a><a name="p1727493393084824"></a><a href="IPC.md#gacd312ab97691605718a3ee9a1c7c63e9">IPC_EXCL</a> and <a href="IPC.md#gace43f23fcb66ddaad964bb8ea8de6e9c">IPC_CREAT</a> are specified, but the shared memory segment associated with <strong id="b1410722784084824"><a name="b1410722784084824"></a><a name="b1410722784084824"></a>key</strong> already exists. </p>
</td>
</tr>
<tr id="row2145732965084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1758140397084824"><a name="p1758140397084824"></a><a name="p1758140397084824"></a>EINVAL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p372581242084824"><a name="p372581242084824"></a><a name="p372581242084824"></a>The size specified for the shared memory segment to create is less than the value of <strong id="b1769093917084824"><a name="b1769093917084824"></a><a name="b1769093917084824"></a>shmmin</strong> in <a href="shminfo.md">shminfo</a> or greater than the value of <strong id="b1949608438084824"><a name="b1949608438084824"></a><a name="b1949608438084824"></a>shmmax</strong>. The shared memory segment associated with <strong id="b848518116084824"><a name="b848518116084824"></a><a name="b848518116084824"></a>key</strong> already exists, but the value of <strong id="b625508799084824"><a name="b625508799084824"></a><a name="b625508799084824"></a>size</strong> is greater than the size of the segment. </p>
</td>
</tr>
<tr id="row778798498084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p664794931084824"><a name="p664794931084824"></a><a name="p664794931084824"></a>ENOENT </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1749360377084824"><a name="p1749360377084824"></a><a name="p1749360377084824"></a>No segment exists for the given key, and <a href="IPC.md#gace43f23fcb66ddaad964bb8ea8de6e9c">IPC_CREAT</a> is not specified. </p>
</td>
</tr>
<tr id="row1318905123084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1265998852084824"><a name="p1265998852084824"></a><a name="p1265998852084824"></a>ENOMEM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1374577057084824"><a name="p1374577057084824"></a><a name="p1374577057084824"></a>Insufficient memory. </p>
</td>
</tr>
<tr id="row366353494084824"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1600318062084824"><a name="p1600318062084824"></a><a name="p1600318062084824"></a>ENOSPC </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1217902305084824"><a name="p1217902305084824"></a><a name="p1217902305084824"></a>Allocating a segment of the requested size would cause the system to exceed the system-wide limit on shared memory (<strong id="b1475635184084824"><a name="b1475635184084824"></a><a name="b1475635184084824"></a>shmall</strong> in <a href="shminfo.md">shminfo</a>). </p>
</td>
</tr>
</tbody>
</table>

