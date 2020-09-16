# utils\_file.h<a name="ZH-CN_TOPIC_0000001054492874"></a>

## **Overview**<a name="section1717808287113030"></a>

**Related Modules:**

[Utils\_file](Utils_file.md)

**Description:**

Performs operations on a file, including to open, close, write, read, and delete a file. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section81333060113030"></a>

## Macros<a name="define-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#gafa5fb3a195634a2b4e4f6e5e1960802a">SEEK_SET_FS</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the file header. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga46bccca36e2775acc050dec021b22e5a">SEEK_CUR_FS</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the current read and write position. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga6473cd9cb4026767b830c18643231dc7">SEEK_END_FS</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the end of the file. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#gaa1719eabbbb0bccff567de8507c9e24f">O_RDONLY_FS</a>&nbsp;&nbsp;&nbsp;00</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by<a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in read-only mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#gae466b69cbf84b032fc08a96ad7cf5360">O_WRONLY_FS</a>&nbsp;&nbsp;&nbsp;01</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in write-only mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga76ab262236051a318fcd05f269849d4e">O_RDWR_FS</a>&nbsp;&nbsp;&nbsp;02</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in read-and-write mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483">O_CREAT_FS</a>&nbsp;&nbsp;&nbsp;0100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to create a file when the file to open does not exist. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga4d6101d81a55a4a7ba0810e39342c5c5">O_EXCL_FS</a>&nbsp;&nbsp;&nbsp;0200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to check whether the file to open exists when <a href="Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483">O_CREAT_FS</a> is already set. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga763cb660cbe7ddec2613116c55f5923b">O_TRUNC_FS</a>&nbsp;&nbsp;&nbsp;01000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to clear the file content if the file exists and can be opened in write mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#gaf0446daf637d995666e937071838dd8f">O_APPEND_FS</a>&nbsp;&nbsp;&nbsp;02000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to start reading or writing from the end of a file. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> (const char *path, int oflag, int mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Opens or creates a file. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga8a2da755514b89ca541f8e8e6c6255f3">UtilsFileClose</a> (int fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Closes a file with the specified file descriptor. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga7734f32bdec1147422827ab93f12c5bd">UtilsFileRead</a> (int fd, char *buf, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Reads a specified length of data from a file with the specified file descriptor and writes the data into the buffer. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga40c464689432ef9952cd3425157de9b2">UtilsFileWrite</a> (int fd, const char *buf, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Writes a specified length of data into a file with the specified file descriptor. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga014fb79a2be2c1c4900664a5ce2d64dc">UtilsFileDelete</a> (const char *path)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Deletes a specified file. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga7eb19c588dff86f8801a212681db5dcc">UtilsFileStat</a> (const char *path, unsigned int *fileSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Obtains the file size. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> (int fd, int offset, unsigned int whence)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Adjusts the read and write position offset in a file. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga08f0677a9f668ba7738031daaed25722">UtilsFileCopy</a> (const char *src, const char *dest)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Copies the source file to a target file. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#gaae711f5bc3368b36b38aaf5643dca984">UtilsFileMove</a> (const char *src, const char *dest)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>int&nbsp;</p>
<p>Moves the source file into a target file. </p>
</td>
</tr>
</tbody>
</table>

