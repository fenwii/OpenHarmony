# shm.h<a name="EN-US_TOPIC_0000001054948037"></a>

## **Overview**<a name="section1499146359084832"></a>

**Related Modules:**

[MEM](mem.md)

**Description:**

Declares APIs for creating, mapping, deleting, and controlling shared memory. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1489590419084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1864452716084832"></a>
<table><thead align="left"><tr id="row1267441843084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1258483518084832"><a name="p1258483518084832"></a><a name="p1258483518084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p557043108084832"><a name="p557043108084832"></a><a name="p557043108084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row779673316084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1228420679084832"><a name="p1228420679084832"></a><a name="p1228420679084832"></a><a href="shmid_ds.md">shmid_ds</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p223265279084832"><a name="p223265279084832"></a><a name="p223265279084832"></a>Stores information about a shared memory segment. </p>
</td>
</tr>
<tr id="row1589976044084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1115469544084832"><a name="p1115469544084832"></a><a name="p1115469544084832"></a><a href="shminfo.md">shminfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1274697288084832"><a name="p1274697288084832"></a><a name="p1274697288084832"></a>Describes limitations and attributes of system-level shared memory. </p>
</td>
</tr>
<tr id="row1578768779084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p414464552084832"><a name="p414464552084832"></a><a name="p414464552084832"></a><a href="shm_info.md">shm_info</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1636325528084832"><a name="p1636325528084832"></a><a name="p1636325528084832"></a>Describes system resource information about the shared memory. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1389824039084832"></a>
<table><thead align="left"><tr id="row1995633795084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p796358761084832"><a name="p796358761084832"></a><a name="p796358761084832"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p172962958084832"><a name="p172962958084832"></a><a name="p172962958084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1108816288084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1385116358084832"><a name="p1385116358084832"></a><a name="p1385116358084832"></a><a href="mem.md#ga1f422a47c416c67470e3a0fb8b7529d8">SHMLBA</a>   4096</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278858651084832"><a name="p278858651084832"></a><a name="p278858651084832"></a>Aligns the shared memory address. </p>
</td>
</tr>
<tr id="row1176784592084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p442504268084832"><a name="p442504268084832"></a><a name="p442504268084832"></a><a href="mem.md#ga45da2dbfb146e926c8fd842379c0362c">SHM_R</a>   0400</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2097707009084832"><a name="p2097707009084832"></a><a name="p2097707009084832"></a>Indicates that the shared memory segment is readable. This macro is used for setting the <strong id="b1285875085084832"><a name="b1285875085084832"></a><a name="b1285875085084832"></a>shmflg</strong> parameter passed to functions such as <a href="mem.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </p>
</td>
</tr>
<tr id="row1246560925084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p970924561084832"><a name="p970924561084832"></a><a name="p970924561084832"></a><a href="mem.md#gafd00993215ed6030ec817bf3615044d1">SHM_W</a>   0200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1917425793084832"><a name="p1917425793084832"></a><a name="p1917425793084832"></a>Indicates that the shared memory segment is writable. This macro is used for setting the <strong id="b976604742084832"><a name="b976604742084832"></a><a name="b976604742084832"></a>shmflg</strong> parameter passed to functions such as <a href="mem.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </p>
</td>
</tr>
<tr id="row1616760950084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1763238458084832"><a name="p1763238458084832"></a><a name="p1763238458084832"></a><a href="mem.md#ga899e8ef0c4c33e2a5cc708c05c75429a">SHM_RDONLY</a>   010000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491427094084832"><a name="p491427094084832"></a><a name="p491427094084832"></a>Indicates that the attached shared memory segment is read-only. This macro is used for setting the <strong id="b508583748084832"><a name="b508583748084832"></a><a name="b508583748084832"></a>shmflg</strong> parameter passed to functions such as <a href="mem.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat()</a>. </p>
</td>
</tr>
<tr id="row1992712759084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1552854681084832"><a name="p1552854681084832"></a><a name="p1552854681084832"></a><a href="mem.md#ga4ae5f621aa1333d9d5962c3e9d674a90">SHM_RND</a>   020000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p884450539084832"><a name="p884450539084832"></a><a name="p884450539084832"></a>Indicates that the shared memory address can be rounded to a value meeting the requirement (<a href="mem.md#ga1f422a47c416c67470e3a0fb8b7529d8">SHMLBA</a>). This macro is used for setting the <strong id="b1093760369084832"><a name="b1093760369084832"></a><a name="b1093760369084832"></a>shmflg</strong> parameter passed to functions such as <a href="mem.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat()</a>. </p>
</td>
</tr>
<tr id="row275913340084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1493969288084832"><a name="p1493969288084832"></a><a name="p1493969288084832"></a><a href="mem.md#gab652a1a4737f9118a64a8fb74084ef7d">SHM_REMAP</a>   040000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1069866315084832"><a name="p1069866315084832"></a><a name="p1069866315084832"></a>Indicates that the memory segment can be remapped. This macro is used for setting the <strong id="b1242998543084832"><a name="b1242998543084832"></a><a name="b1242998543084832"></a>shmflg</strong> parameter passed to functions such as <a href="mem.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat()</a>. </p>
</td>
</tr>
<tr id="row1237477864084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973026108084832"><a name="p973026108084832"></a><a name="p973026108084832"></a><a href="mem.md#ga0bb6454e0dd48a66376bfaa05170ce82">SHM_EXEC</a>   0100000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1370406263084832"><a name="p1370406263084832"></a><a name="p1370406263084832"></a>Indicates that the attached shared memory segment is executable. This macro is used for setting the <strong id="b655489676084832"><a name="b655489676084832"></a><a name="b655489676084832"></a>shmflg</strong> parameter passed to functions such as <a href="mem.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat()</a>. </p>
</td>
</tr>
<tr id="row1904211215084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p861871057084832"><a name="p861871057084832"></a><a name="p861871057084832"></a><a href="mem.md#ga66735ad43f79860ccdd21888c3ead8cc">SHM_LOCK</a>   11</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1496329915084832"><a name="p1496329915084832"></a><a name="p1496329915084832"></a>Locks the shared memory segment in memory so that it cannot be swapped to the swap partition. This macro is used for setting the <strong id="b789506832084832"><a name="b789506832084832"></a><a name="b789506832084832"></a>shmflg</strong> parameter passed to functions such as <a href="mem.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </p>
</td>
</tr>
<tr id="row1372793530084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2015564741084832"><a name="p2015564741084832"></a><a name="p2015564741084832"></a><a href="mem.md#ga7497459fc5ebe82bbbdfa3809c938312">SHM_UNLOCK</a>   12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1186478408084832"><a name="p1186478408084832"></a><a name="p1186478408084832"></a>Unlocks the shared memory segment. This macro is used for setting the <strong id="b58419809084832"><a name="b58419809084832"></a><a name="b58419809084832"></a>shmflg</strong> parameter passed to functions such as <a href="mem.md#ga23e346182fc10c5286f37213e09fefb2">shmget()</a>. </p>
</td>
</tr>
<tr id="row1730026449084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1031076079084832"><a name="p1031076079084832"></a><a name="p1031076079084832"></a><a href="mem.md#ga2e0f8c5b0fafab9f2602d19588d03e95">SHM_STAT</a>   (13 | (<a href="ipc.md#ga16a91ee69c3cb6bfec425e1bfd5edd18">IPC_STAT</a> &amp; 0x100))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85065422084832"><a name="p85065422084832"></a><a name="p85065422084832"></a>Obtains a <a href="shmid_ds.md">shmid_ds</a> data structure. This macro is used for setting the <strong id="b548927368084832"><a name="b548927368084832"></a><a name="b548927368084832"></a>cmd</strong> parameter passed to <a href="mem.md#gab2cfe9a9370d4c74b485876260e2e0fe">shmctl()</a>. </p>
</td>
</tr>
<tr id="row186365136084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p834497493084832"><a name="p834497493084832"></a><a name="p834497493084832"></a><a href="mem.md#gafecb9e202431a631f42469c9ecbee99e">SHM_INFO</a>   14</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1467305354084832"><a name="p1467305354084832"></a><a name="p1467305354084832"></a>Obtains a <a href="shm_info.md">shm_info</a> data structure that includes system resource information about this shared memory segment. This macro is used for setting the <strong id="b1372311661084832"><a name="b1372311661084832"></a><a name="b1372311661084832"></a>cmd</strong> parameter passed to <a href="mem.md#gab2cfe9a9370d4c74b485876260e2e0fe">shmctl()</a>. </p>
</td>
</tr>
<tr id="row1886820258084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1087959858084832"><a name="p1087959858084832"></a><a name="p1087959858084832"></a><a href="mem.md#ga9e7f0a6d71663d9173d9aae2a2f01220">SHM_STAT_ANY</a>   (15 | (<a href="ipc.md#ga16a91ee69c3cb6bfec425e1bfd5edd18">IPC_STAT</a> &amp; 0x100))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1275422699084832"><a name="p1275422699084832"></a><a name="p1275422699084832"></a>Obtains a <a href="shmid_ds.md">shmid_ds</a> data structure without permission check. This macro is used for setting the <strong id="b1266543665084832"><a name="b1266543665084832"></a><a name="b1266543665084832"></a>cmd</strong> parameter passed to <a href="mem.md#gab2cfe9a9370d4c74b485876260e2e0fe">shmctl()</a>. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table266012207084832"></a>
<table><thead align="left"><tr id="row1362097683084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p456901061084832"><a name="p456901061084832"></a><a name="p456901061084832"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p844744087084832"><a name="p844744087084832"></a><a name="p844744087084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1447042137084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p362824269084832"><a name="p362824269084832"></a><a name="p362824269084832"></a><a href="mem.md#gac56f61130bf1ddd88ecd6a2e87b4c5cb">shmat</a> (int shmid, const void *shmaddr, int shmflg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1298688135084832"><a name="p1298688135084832"></a><a name="p1298688135084832"></a>void * </p>
<p id="p1748909736084832"><a name="p1748909736084832"></a><a name="p1748909736084832"></a>Attaches the shared memory segment identified by <strong id="b2067445238084832"><a name="b2067445238084832"></a><a name="b2067445238084832"></a>shmid</strong> to the address space of the current process. </p>
</td>
</tr>
<tr id="row1375050018084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p40065161084832"><a name="p40065161084832"></a><a name="p40065161084832"></a><a href="mem.md#gab2cfe9a9370d4c74b485876260e2e0fe">shmctl</a> (int shmid, int cmd, struct <a href="shmid_ds.md">shmid_ds</a> *buf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p216866370084832"><a name="p216866370084832"></a><a name="p216866370084832"></a>int </p>
<p id="p1346156822084832"><a name="p1346156822084832"></a><a name="p1346156822084832"></a>Performs a control operation specified by the <strong id="b1577988894084832"><a name="b1577988894084832"></a><a name="b1577988894084832"></a>cmd</strong> parameter on the shared memory segment identified by <strong id="b891706388084832"><a name="b891706388084832"></a><a name="b891706388084832"></a>shmid</strong>. </p>
</td>
</tr>
<tr id="row547291497084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1171798131084832"><a name="p1171798131084832"></a><a name="p1171798131084832"></a><a href="mem.md#ga934738fcc6c27c0d45cff9bb8cc38a7f">shmdt</a> (const void *shmaddr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1425913667084832"><a name="p1425913667084832"></a><a name="p1425913667084832"></a>int </p>
<p id="p578214113084832"><a name="p578214113084832"></a><a name="p578214113084832"></a>Detaches the shared memory segment attached to the address pointed to by <strong id="b1288696753084832"><a name="b1288696753084832"></a><a name="b1288696753084832"></a>shmaddr</strong> from the address space of the calling process. </p>
</td>
</tr>
<tr id="row1398014813084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1268148070084832"><a name="p1268148070084832"></a><a name="p1268148070084832"></a><a href="mem.md#ga23e346182fc10c5286f37213e09fefb2">shmget</a> (key_t key, size_t size, int shmflg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p608366770084832"><a name="p608366770084832"></a><a name="p608366770084832"></a>int </p>
<p id="p852657415084832"><a name="p852657415084832"></a><a name="p852657415084832"></a>Obtains or creates a shared memory segment with the specified size based on the ID specified by <strong id="b1738332354084832"><a name="b1738332354084832"></a><a name="b1738332354084832"></a>key</strong>. </p>
</td>
</tr>
</tbody>
</table>

