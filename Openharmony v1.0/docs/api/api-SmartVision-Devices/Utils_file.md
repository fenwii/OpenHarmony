# Utils\_file<a name="ZH-CN_TOPIC_0000001054652799"></a>

## **Overview**<a name="section409870799113023"></a>

Performs operations on a file. 

This module allows you to performs file operations such as to open, close, read, and write a file, and to obtain the file size. The filing system varies according to the hardware platform. The following limitations are imposed on a platform that uses the Serial Peripheral Interface Flash Filing System \(SPIFFS\): 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1255662923113023"></a>

## Files<a name="files"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="utils_file-h.md">utils_file.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Performs operations on a file, including to open, close, write, read, and delete a file. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><em id="gafa5fb3a195634a2b4e4f6e5e1960802a"><a name="gafa5fb3a195634a2b4e4f6e5e1960802a"></a><a name="gafa5fb3a195634a2b4e4f6e5e1960802a"></a></em>SEEK_SET_FS &nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the file header. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><em id="ga46bccca36e2775acc050dec021b22e5a"><a name="ga46bccca36e2775acc050dec021b22e5a"></a><a name="ga46bccca36e2775acc050dec021b22e5a"></a></em>SEEK_CUR_FS &nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the current read and write position. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><em id="ga6473cd9cb4026767b830c18643231dc7"><a name="ga6473cd9cb4026767b830c18643231dc7"></a><a name="ga6473cd9cb4026767b830c18643231dc7"></a></em>SEEK_END_FS &nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the end of the file. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><em id="gaa1719eabbbb0bccff567de8507c9e24f"><a name="gaa1719eabbbb0bccff567de8507c9e24f"></a><a name="gaa1719eabbbb0bccff567de8507c9e24f"></a></em>O_RDONLY_FS &nbsp;&nbsp;&nbsp;00</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by<a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in read-only mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><em id="gae466b69cbf84b032fc08a96ad7cf5360"><a name="gae466b69cbf84b032fc08a96ad7cf5360"></a><a name="gae466b69cbf84b032fc08a96ad7cf5360"></a></em>O_WRONLY_FS &nbsp;&nbsp;&nbsp;01</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in write-only mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><em id="ga76ab262236051a318fcd05f269849d4e"><a name="ga76ab262236051a318fcd05f269849d4e"></a><a name="ga76ab262236051a318fcd05f269849d4e"></a></em>O_RDWR_FS &nbsp;&nbsp;&nbsp;02</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in read-and-write mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><em id="ga79f003e100f1a5126fbea0dc355e3483"><a name="ga79f003e100f1a5126fbea0dc355e3483"></a><a name="ga79f003e100f1a5126fbea0dc355e3483"></a></em>O_CREAT_FS &nbsp;&nbsp;&nbsp;0100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to create a file when the file to open does not exist. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><a href="Utils_file.md#ga4d6101d81a55a4a7ba0810e39342c5c5">O_EXCL_FS</a>&nbsp;&nbsp;&nbsp;0200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to check whether the file to open exists when <a href="Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483">O_CREAT_FS</a> is already set. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><em id="ga763cb660cbe7ddec2613116c55f5923b"><a name="ga763cb660cbe7ddec2613116c55f5923b"></a><a name="ga763cb660cbe7ddec2613116c55f5923b"></a></em>O_TRUNC_FS &nbsp;&nbsp;&nbsp;01000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to clear the file content if the file exists and can be opened in write mode. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p><em id="gaf0446daf637d995666e937071838dd8f"><a name="gaf0446daf637d995666e937071838dd8f"></a><a name="gaf0446daf637d995666e937071838dd8f"></a></em>O_APPEND_FS &nbsp;&nbsp;&nbsp;02000</p>
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

## **Details**<a name="section733841185113023"></a>

## **Macro Definition Documentation**<a name="section1145198923113023"></a>

## O\_EXCL\_FS<a name="ga4d6101d81a55a4a7ba0810e39342c5c5"></a>

```
#define O_EXCL_FS   0200
```

 **Description:**

Defines a flag used by  [UtilsFileOpen](Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899)  to check whether the file to open exists when  [O\_CREAT\_FS](Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483)  is already set. 

If the file does not exist, a new file will be created. If the file exists, the file cannot be opened. 

## **Function Documentation**<a name="section1822096272113023"></a>

## UtilsFileClose\(\)<a name="ga8a2da755514b89ca541f8e8e6c6255f3"></a>

```
int UtilsFileClose (int fd)
```

 **Description:**

Closes a file with the specified file descriptor. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file descriptor of the file to close. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the file is closed; returns  **-1**  otherwise. 



## UtilsFileCopy\(\)<a name="ga08f0677a9f668ba7738031daaed25722"></a>

```
int UtilsFileCopy (const char * src, const char * dest )
```

 **Description:**

Copies the source file to a target file. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">src</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the source file to copy. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dest</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target file. </td>
</tr>
</tbody>
</table>

**Attention:**

If the number of opened files reaches the upper limit \(32\), close any two files first. Otherwise, the file cannot be copied. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## UtilsFileDelete\(\)<a name="ga014fb79a2be2c1c4900664a5ce2d64dc"></a>

```
int UtilsFileDelete (const char * path)
```

 **Description:**

Deletes a specified file. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">path</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file to delete. </td>
</tr>
</tbody>
</table>

**Attention:**

If the number of opened files reaches the upper limit \(32\), close any of them first. Otherwise, the file cannot be deleted. 

**Returns:**

Returns  **0**  if the file is deleted; returns  **-1**  otherwise. 



## UtilsFileMove\(\)<a name="gaae711f5bc3368b36b38aaf5643dca984"></a>

```
int UtilsFileMove (const char * src, const char * dest )
```

 **Description:**

Moves the source file into a target file. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">src</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the source file. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dest</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the target file. </td>
</tr>
</tbody>
</table>

**Attention:**

If the number of opened files reaches the upper limit \(32\), close any two files first. Otherwise, the file cannot be moved. 

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise. 



## UtilsFileOpen\(\)<a name="ga17115e4a2d52b37bffcbd465e2c1a899"></a>

```
int UtilsFileOpen (const char * path, int oflag, int mode )
```

 **Description:**

Opens or creates a file. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">path</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file to open or create. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">oflag</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the mode of opening a file. The following modes are supported. These modes can be used together, with each of them identified by "or". </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Used for function compatibility. This parameter does not take effect in any scenario. </td>
</tr>
</tbody>
</table>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>oflag </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description  </p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>O_RDONLY_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>For details, see <a href="Utils_file.md#gaa1719eabbbb0bccff567de8507c9e24f">O_RDONLY_FS</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>O_WRONLY_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>For details, see <a href="Utils_file.md#gae466b69cbf84b032fc08a96ad7cf5360">O_WRONLY_FS</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>O_RDWR_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>For details, see <a href="Utils_file.md#ga76ab262236051a318fcd05f269849d4e">O_RDWR_FS</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>O_CREAT_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>For details, see <a href="Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483">O_CREAT_FS</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>O_EXCL_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>For details, see <a href="Utils_file.md#ga4d6101d81a55a4a7ba0810e39342c5c5">O_EXCL_FS</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>O_TRUNC_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>For details, see <a href="Utils_file.md#ga763cb660cbe7ddec2613116c55f5923b">O_TRUNC_FS</a>. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>O_APPEND_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>For details, see <a href="Utils_file.md#gaf0446daf637d995666e937071838dd8f">O_APPEND_FS</a>. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the file descriptor if the file is opened or created; returns  **-1**  otherwise. 



## UtilsFileRead\(\)<a name="ga7734f32bdec1147422827ab93f12c5bd"></a>

```
int UtilsFileRead (int fd, char * buf, unsigned int len )
```

 **Description:**

Reads a specified length of data from a file with the specified file descriptor and writes the data into the buffer. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file descriptor of the file to read. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer that stores the read data. This is an output parameter. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to read. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of bytes of the data if the data is read; returns  **-1**  otherwise. 



## UtilsFileSeek\(\)<a name="ga5ae2e96182ab66be3b048a970383764c"></a>

```
int UtilsFileSeek (int fd, int offset, unsigned int whence )
```

 **Description:**

Adjusts the read and write position offset in a file. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file descriptor of the file where the read and write position offset needs adjustment. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">offset</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the offset of the read and write position based on the <strong>whence</strong> parameter. The value can be negative if the value of <strong>whence</strong> is <strong>SEEK_CUR_FS</strong> or <strong>SEEK_END_FS</strong>. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">whence</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the start position of the offset. The following start positions are supported. </td>
</tr>
</tbody>
</table>

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>whence </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description  </p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>SEEK_SET_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Adjusts the read and write position to the file header. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>^ </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Then adds the offset after the read and write position. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>SEEK_CUR_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Adds the offset after the current read and write position. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>SEEK_END_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Adjusts the read and write position to the end of the file. </p>
</td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p>^ </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p>Then adds the offset after the read and write position. </p>
</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the current read and write position if the operation is successful; returns  **-1**  otherwise. 



## UtilsFileStat\(\)<a name="ga7eb19c588dff86f8801a212681db5dcc"></a>

```
int UtilsFileStat (const char * path, unsigned int * fileSize )
```

 **Description:**

Obtains the file size. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">path</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file name. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fileSize</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file size. This is an output parameter. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the file size is obtained; returns  **-1**  otherwise. 



## UtilsFileWrite\(\)<a name="ga40c464689432ef9952cd3425157de9b2"></a>

```
int UtilsFileWrite (int fd, const char * buf, unsigned int len )
```

 **Description:**

Writes a specified length of data into a file with the specified file descriptor. 

**Parameters:**

<table><thead align="left"><tr><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p>Description</p>
</th>
</tr>
</thead>
<tbody><tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file descriptor of the file where to write the data. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data to write. </td>
</tr>
<tr><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of bytes of the data if the data is written; returns  **-1**  otherwise. 



