# osal\_file.h<a name="EN-US_TOPIC_0000001054918129"></a>

## **Overview**<a name="section348088835093526"></a>

**Related Modules:**

[OSAL](osal.md)

**Description:**

Declares the file structures and interfaces. 

This file provides interfaces for opening, closing, reading, and writing a file, and setting the read/write offset.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1680136449093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table237287878093526"></a>
<table><thead align="left"><tr id="row1591130814093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p427935936093526"><a name="p427935936093526"></a><a name="p427935936093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2107275091093526"><a name="p2107275091093526"></a><a name="p2107275091093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1135886228093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1417062182093526"><a name="p1417062182093526"></a><a name="p1417062182093526"></a><a href="osalfile.md">OsalFile</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1169336084093526"><a name="p1169336084093526"></a><a name="p1169336084093526"></a>Declares a file type. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1711236483093526"></a>
<table><thead align="left"><tr id="row1794508428093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p309359747093526"><a name="p309359747093526"></a><a name="p309359747093526"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p976017898093526"><a name="p976017898093526"></a><a name="p976017898093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row875828934093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p137382420093526"><a name="p137382420093526"></a><a name="p137382420093526"></a><a href="osal.md#gab208afeed35dd98f6a0ccf807e9c722d">OSAL_O_RD_ONLY</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1895715986093526"><a name="p1895715986093526"></a><a name="p1895715986093526"></a>Opens a file in read-only mode. </p>
</td>
</tr>
<tr id="row174037700093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p874658882093526"><a name="p874658882093526"></a><a name="p874658882093526"></a><a href="osal.md#ga1e37c3fb82a2bcff729f97478bc28f81">OSAL_O_WR_ONLY</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p108516513093526"><a name="p108516513093526"></a><a name="p108516513093526"></a>Opens a file in write-only mode. </p>
</td>
</tr>
<tr id="row481201904093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p115068528093526"><a name="p115068528093526"></a><a name="p115068528093526"></a><a href="osal.md#gabac6ceec2cb877ae0c4c0c89f2e13451">OSAL_O_RDWR</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1315889418093526"><a name="p1315889418093526"></a><a name="p1315889418093526"></a>Opens a file in read and write mode. </p>
</td>
</tr>
<tr id="row39742898093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p704022998093526"><a name="p704022998093526"></a><a name="p704022998093526"></a><a href="osal.md#ga9cb465f6d142e859258e14199702906e">OSAL_S_IREAD</a>   00400</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p126242826093526"><a name="p126242826093526"></a><a name="p126242826093526"></a>Defines the read permission for the owner. </p>
</td>
</tr>
<tr id="row1532904986093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p126158443093526"><a name="p126158443093526"></a><a name="p126158443093526"></a><a href="osal.md#gaf93f6ab3441029a84b5f04904daf68be">OSAL_S_IWRITE</a>   00200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p516843374093526"><a name="p516843374093526"></a><a name="p516843374093526"></a>Defines the write permission for the owner. </p>
</td>
</tr>
<tr id="row900182107093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1031203343093526"><a name="p1031203343093526"></a><a name="p1031203343093526"></a><a href="osal.md#gaa168a8495f19631b9d4de6e5da688e26">OSAL_S_IEXEC</a>   00100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p188348816093526"><a name="p188348816093526"></a><a name="p188348816093526"></a>Defines the execution permission for the owner. </p>
</td>
</tr>
<tr id="row1190038698093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p502364522093526"><a name="p502364522093526"></a><a name="p502364522093526"></a><a href="osal.md#ga008dcb6a04b63ef620c25aa5b41f211a">OSAL_S_IRGRP</a>   00040</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027692329093526"><a name="p1027692329093526"></a><a name="p1027692329093526"></a>Defines the read permission for the group. </p>
</td>
</tr>
<tr id="row996329510093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p656388113093526"><a name="p656388113093526"></a><a name="p656388113093526"></a><a href="osal.md#ga982f1e009c6caeb8060e6442a866803f">OSAL_S_IWGRP</a>   00020</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1137339751093526"><a name="p1137339751093526"></a><a name="p1137339751093526"></a>Defines the write permission for the group. </p>
</td>
</tr>
<tr id="row199490067093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1511664785093526"><a name="p1511664785093526"></a><a name="p1511664785093526"></a><a href="osal.md#gaa1e6fa403fcd99229902e9a8cd98a74c">OSAL_S_IXGRP</a>   00010</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p815089720093526"><a name="p815089720093526"></a><a name="p815089720093526"></a>Defines the execution permission for the group. </p>
</td>
</tr>
<tr id="row638140266093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p470310360093526"><a name="p470310360093526"></a><a name="p470310360093526"></a><a href="osal.md#ga01e4a94482a048060c250d3d5d899cd6">OSAL_S_IROTH</a>   00004</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1655961714093526"><a name="p1655961714093526"></a><a name="p1655961714093526"></a>Defines the read permission for others. </p>
</td>
</tr>
<tr id="row974665804093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1416187593093526"><a name="p1416187593093526"></a><a name="p1416187593093526"></a><a href="osal.md#gaea63281bfbac42036bb549c2bda2d192">OSAL_S_IWOTH</a>   00002</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1949586978093526"><a name="p1949586978093526"></a><a name="p1949586978093526"></a>Defines the write permission for others. </p>
</td>
</tr>
<tr id="row2110045609093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p766498237093526"><a name="p766498237093526"></a><a name="p766498237093526"></a><a href="osal.md#ga9e308388be9855050060a87a93191d5e">OSAL_S_IXOTH</a>   00001</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p60040359093526"><a name="p60040359093526"></a><a name="p60040359093526"></a>Defines the execution permission for others. </p>
</td>
</tr>
<tr id="row1218459766093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997145054093526"><a name="p1997145054093526"></a><a name="p1997145054093526"></a><a href="osal.md#ga110fc469c88e83828679a3dedb4b5f3d">OSAL_SEEK_SET</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p564704665093526"><a name="p564704665093526"></a><a name="p564704665093526"></a>Defines the offset from the file header. </p>
</td>
</tr>
<tr id="row6681315093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1761381321093526"><a name="p1761381321093526"></a><a name="p1761381321093526"></a><a href="osal.md#ga2ae6c04da45367479db0f914b250a0a7">OSAL_SEEK_CUR</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1618964041093526"><a name="p1618964041093526"></a><a name="p1618964041093526"></a>Defines the offset from the current position. </p>
</td>
</tr>
<tr id="row1607877327093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p694020990093526"><a name="p694020990093526"></a><a name="p694020990093526"></a><a href="osal.md#gaf282e1e5207b934c0c71ce9558ac1940">OSAL_SEEK_END</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p767120582093526"><a name="p767120582093526"></a><a name="p767120582093526"></a>Defines the offset from the end of the file. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table230604028093526"></a>
<table><thead align="left"><tr id="row1964966453093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1315673446093526"><a name="p1315673446093526"></a><a name="p1315673446093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1124097793093526"><a name="p1124097793093526"></a><a name="p1124097793093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1092518050093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1084277315093526"><a name="p1084277315093526"></a><a name="p1084277315093526"></a><a href="osal.md#ga6707125b6ac5e13912a181877f18f292">OsalFileOpen</a> (<a href="osalfile.md">OsalFile</a> *file, const char *path, int flags, uint32_t rights)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p606630208093526"><a name="p606630208093526"></a><a name="p606630208093526"></a>int32_t </p>
<p id="p1922916291093526"><a name="p1922916291093526"></a><a name="p1922916291093526"></a>Opens a file. </p>
</td>
</tr>
<tr id="row1122103538093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1153258223093526"><a name="p1153258223093526"></a><a name="p1153258223093526"></a><a href="osal.md#ga305f575f875ff26bb907c67c23dfb16a">OsalFileWrite</a> (<a href="osalfile.md">OsalFile</a> *file, const void *string, uint32_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466691954093526"><a name="p1466691954093526"></a><a name="p1466691954093526"></a>ssize_t </p>
<p id="p1648489530093526"><a name="p1648489530093526"></a><a name="p1648489530093526"></a>Writes a file. </p>
</td>
</tr>
<tr id="row1183720870093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p946726175093526"><a name="p946726175093526"></a><a name="p946726175093526"></a><a href="osal.md#ga8786ab2baa8669e79173ab7ab47d67bb">OsalFileClose</a> (<a href="osalfile.md">OsalFile</a> *file)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p548637635093526"><a name="p548637635093526"></a><a name="p548637635093526"></a>void </p>
<p id="p714946295093526"><a name="p714946295093526"></a><a name="p714946295093526"></a>Closes a file. </p>
</td>
</tr>
<tr id="row1875068180093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044146252093526"><a name="p2044146252093526"></a><a name="p2044146252093526"></a><a href="osal.md#gac8ebc8dc4b9ce9725875868f69fd17a8">OsalFileRead</a> (<a href="osalfile.md">OsalFile</a> *file, void *buf, uint32_t length)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p770469820093526"><a name="p770469820093526"></a><a name="p770469820093526"></a>ssize_t </p>
<p id="p139297568093526"><a name="p139297568093526"></a><a name="p139297568093526"></a>Reads a file. </p>
</td>
</tr>
<tr id="row1459406026093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1121884828093526"><a name="p1121884828093526"></a><a name="p1121884828093526"></a><a href="osal.md#gaada4d66f4bb789bb4113e4084da6dea2">OsalFileLseek</a> (<a href="osalfile.md">OsalFile</a> *file, off_t offset, int32_t whence)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p560444913093526"><a name="p560444913093526"></a><a name="p560444913093526"></a>off_t </p>
<p id="p19492821093526"><a name="p19492821093526"></a><a name="p19492821093526"></a>Sets the file read/write offset. </p>
</td>
</tr>
</tbody>
</table>

