# fcntl.h<a name="ZH-CN_TOPIC_0000001054909428"></a>

## **Overview**<a name="section1295896674084829"></a>

**Related Modules:**

[FS](FS.md)

**Description:**

Declares structures and functions used for file and directory operations such as opening a file, creating a file, and allocating space. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section226426351084829"></a>

## Macros<a name="define-members"></a>

<a name="table1368211481084829"></a>
<table><thead align="left"><tr id="row316137115084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p743860379084829"><a name="p743860379084829"></a><a name="p743860379084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1051021258084829"><a name="p1051021258084829"></a><a name="p1051021258084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1946618737084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p114783818084829"><a name="p114783818084829"></a><a name="p114783818084829"></a><a href="FS.md#ga4dc4d45e07d2abc899bcaf04b2846a87">O_ACCMODE</a>&nbsp;&nbsp;&nbsp;(03|O_SEARCH)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1569394785084829"><a name="p1569394785084829"></a><a name="p1569394785084829"></a>Access mode. </p>
</td>
</tr>
<tr id="row1187569927084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p308327087084829"><a name="p308327087084829"></a><a name="p308327087084829"></a><a href="FS.md#ga7a68c9ffaac7dbcd652225dd7c06a54b">O_RDONLY</a>&nbsp;&nbsp;&nbsp;00</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519376403084829"><a name="p519376403084829"></a><a name="p519376403084829"></a>Read-only. </p>
</td>
</tr>
<tr id="row1350830628084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1595552199084829"><a name="p1595552199084829"></a><a name="p1595552199084829"></a><a href="FS.md#ga11b644a8526139c4cc1850dac1271ced">O_WRONLY</a>&nbsp;&nbsp;&nbsp;01</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1835788364084829"><a name="p1835788364084829"></a><a name="p1835788364084829"></a>Write-only. </p>
</td>
</tr>
<tr id="row1610296391084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1647060502084829"><a name="p1647060502084829"></a><a name="p1647060502084829"></a><a href="FS.md#gabb0586253488ee61072b73557eeb873b">O_RDWR</a>&nbsp;&nbsp;&nbsp;02</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1369193895084829"><a name="p1369193895084829"></a><a name="p1369193895084829"></a>Read and write. </p>
</td>
</tr>
<tr id="row305364461084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p606233505084829"><a name="p606233505084829"></a><a name="p606233505084829"></a><a href="FS.md#ga3bc050c90515f35b4cd6cea24760110c">fallocate64</a>&nbsp;&nbsp;&nbsp;<a href="FS.md#ga26ba05fc43886db02fe169b35e04bfdf">fallocate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1212418046084829"><a name="p1212418046084829"></a><a name="p1212418046084829"></a>Pre-allocates space to a file. See <a href="FS.md#ga26ba05fc43886db02fe169b35e04bfdf">fallocate</a>. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table970227086084829"></a>
<table><thead align="left"><tr id="row1757931062084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p788376109084829"><a name="p788376109084829"></a><a name="p788376109084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p201916293084829"><a name="p201916293084829"></a><a name="p201916293084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row363867485084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p765243227084829"><a name="p765243227084829"></a><a name="p765243227084829"></a><a href="FS.md#gafddc24a65767ae35f275be8ccf53e036">creat</a> (const char *path, mode_t mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1893637776084829"><a name="p1893637776084829"></a><a name="p1893637776084829"></a>int&nbsp;</p>
<p id="p933683308084829"><a name="p933683308084829"></a><a name="p933683308084829"></a>Creates a file or rewrites an existing file. </p>
</td>
</tr>
<tr id="row850150140084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1180208923084829"><a name="p1180208923084829"></a><a name="p1180208923084829"></a><a href="FS.md#ga219205a58e244a5acd35b767ac50ef9c">open</a> (const char *path, int oflags,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p717127921084829"><a name="p717127921084829"></a><a name="p717127921084829"></a>int&nbsp;</p>
<p id="p1034669329084829"><a name="p1034669329084829"></a><a name="p1034669329084829"></a>Opens a file. </p>
</td>
</tr>
<tr id="row1565011972084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1521551283084829"><a name="p1521551283084829"></a><a name="p1521551283084829"></a><a href="FS.md#ga26ba05fc43886db02fe169b35e04bfdf">fallocate</a> (int fd, int mode, off_t offset, off_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p279394076084829"><a name="p279394076084829"></a><a name="p279394076084829"></a>int&nbsp;</p>
<p id="p837167029084829"><a name="p837167029084829"></a><a name="p837167029084829"></a>Pre-allocates space to a file. </p>
</td>
</tr>
<tr id="row1872845278084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2072268742084829"><a name="p2072268742084829"></a><a name="p2072268742084829"></a><a href="FS.md#gad39ebe4c4767eaa9a680777400cfaafe">fcntl</a> (int fd, int cmd,...)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p111928920084829"><a name="p111928920084829"></a><a name="p111928920084829"></a>int&nbsp;</p>
<p id="p1196158391084829"><a name="p1196158391084829"></a><a name="p1196158391084829"></a>Manipulates a specified file descriptor. </p>
</td>
</tr>
</tbody>
</table>

