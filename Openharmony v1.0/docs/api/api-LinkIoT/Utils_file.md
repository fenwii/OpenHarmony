# Utils\_file<a name="ZH-CN_TOPIC_0000001054796527"></a>

## **Overview**<a name="section8302598090252"></a>

Performs operations on a file. 

This module allows you to performs file operations such as to open, close, read, and write a file, and to obtain the file size. The filing system varies according to the hardware platform. The following limitations are imposed on a platform that uses the Serial Peripheral Interface Flash Filing System \(SPIFFS\): 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section102885079090252"></a>

## Files<a name="files"></a>

<a name="table1772494705090252"></a>
<table><thead align="left"><tr id="row879837619090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p685759466090252"><a name="p685759466090252"></a><a name="p685759466090252"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p930498485090252"><a name="p930498485090252"></a><a name="p930498485090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1253176830090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p686402109090252"><a name="p686402109090252"></a><a name="p686402109090252"></a><a href="utils_file-h.md">utils_file.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1830821451090252"><a name="p1830821451090252"></a><a name="p1830821451090252"></a>Performs operations on a file, including to open, close, write, read, and delete a file. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table597907418090252"></a>
<table><thead align="left"><tr id="row263848064090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1784554380090252"><a name="p1784554380090252"></a><a name="p1784554380090252"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1446209625090252"><a name="p1446209625090252"></a><a name="p1446209625090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row532417835090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290688214090252"><a name="p1290688214090252"></a><a name="p1290688214090252"></a><a href="Utils_file.md#gafa5fb3a195634a2b4e4f6e5e1960802a">SEEK_SET_FS</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1281178355090252"><a name="p1281178355090252"></a><a name="p1281178355090252"></a>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the file header. </p>
</td>
</tr>
<tr id="row1208235577090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1859140717090252"><a name="p1859140717090252"></a><a name="p1859140717090252"></a><a href="Utils_file.md#ga46bccca36e2775acc050dec021b22e5a">SEEK_CUR_FS</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p839086539090252"><a name="p839086539090252"></a><a name="p839086539090252"></a>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the current read and write position. </p>
</td>
</tr>
<tr id="row1582728498090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p19098814090252"><a name="p19098814090252"></a><a name="p19098814090252"></a><a href="Utils_file.md#ga6473cd9cb4026767b830c18643231dc7">SEEK_END_FS</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p178708947090252"><a name="p178708947090252"></a><a name="p178708947090252"></a>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the end of the file. </p>
</td>
</tr>
<tr id="row1152179396090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1829813520090252"><a name="p1829813520090252"></a><a name="p1829813520090252"></a><a href="Utils_file.md#gaa1719eabbbb0bccff567de8507c9e24f">O_RDONLY_FS</a>&nbsp;&nbsp;&nbsp;00</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p170662911090252"><a name="p170662911090252"></a><a name="p170662911090252"></a>Defines a flag used by<a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in read-only mode. </p>
</td>
</tr>
<tr id="row408660148090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1676636482090252"><a name="p1676636482090252"></a><a name="p1676636482090252"></a><a href="Utils_file.md#gae466b69cbf84b032fc08a96ad7cf5360">O_WRONLY_FS</a>&nbsp;&nbsp;&nbsp;01</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1737265431090252"><a name="p1737265431090252"></a><a name="p1737265431090252"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in write-only mode. </p>
</td>
</tr>
<tr id="row862100624090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1305390480090252"><a name="p1305390480090252"></a><a name="p1305390480090252"></a><a href="Utils_file.md#ga76ab262236051a318fcd05f269849d4e">O_RDWR_FS</a>&nbsp;&nbsp;&nbsp;02</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1800625323090252"><a name="p1800625323090252"></a><a name="p1800625323090252"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in read-and-write mode. </p>
</td>
</tr>
<tr id="row542486999090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691284015090252"><a name="p691284015090252"></a><a name="p691284015090252"></a><a href="Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483">O_CREAT_FS</a>&nbsp;&nbsp;&nbsp;0100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p883550237090252"><a name="p883550237090252"></a><a name="p883550237090252"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to create a file when the file to open does not exist. </p>
</td>
</tr>
<tr id="row1475822001090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478555423090252"><a name="p478555423090252"></a><a name="p478555423090252"></a><a href="Utils_file.md#ga4d6101d81a55a4a7ba0810e39342c5c5">O_EXCL_FS</a>&nbsp;&nbsp;&nbsp;0200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p468795690090252"><a name="p468795690090252"></a><a name="p468795690090252"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to check whether the file to open exists when <a href="Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483">O_CREAT_FS</a> is already set. </p>
</td>
</tr>
<tr id="row534140425090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2135466121090252"><a name="p2135466121090252"></a><a name="p2135466121090252"></a><a href="Utils_file.md#ga763cb660cbe7ddec2613116c55f5923b">O_TRUNC_FS</a>&nbsp;&nbsp;&nbsp;01000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p991349713090252"><a name="p991349713090252"></a><a name="p991349713090252"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to clear the file content if the file exists and can be opened in write mode. </p>
</td>
</tr>
<tr id="row1604294011090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1101862252090252"><a name="p1101862252090252"></a><a name="p1101862252090252"></a><a href="Utils_file.md#gaf0446daf637d995666e937071838dd8f">O_APPEND_FS</a>&nbsp;&nbsp;&nbsp;02000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327000057090252"><a name="p327000057090252"></a><a name="p327000057090252"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to start reading or writing from the end of a file. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table225432441090252"></a>
<table><thead align="left"><tr id="row156944607090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1948616625090252"><a name="p1948616625090252"></a><a name="p1948616625090252"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p940633535090252"><a name="p940633535090252"></a><a name="p940633535090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row648823785090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2125586781090252"><a name="p2125586781090252"></a><a name="p2125586781090252"></a><a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> (const char *path, int oflag, int mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519257951090252"><a name="p519257951090252"></a><a name="p519257951090252"></a>int&nbsp;</p>
<p id="p579908178090252"><a name="p579908178090252"></a><a name="p579908178090252"></a>Opens or creates a file. </p>
</td>
</tr>
<tr id="row246992962090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2014299248090252"><a name="p2014299248090252"></a><a name="p2014299248090252"></a><a href="Utils_file.md#ga8a2da755514b89ca541f8e8e6c6255f3">UtilsFileClose</a> (int fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1037340082090252"><a name="p1037340082090252"></a><a name="p1037340082090252"></a>int&nbsp;</p>
<p id="p1576360728090252"><a name="p1576360728090252"></a><a name="p1576360728090252"></a>Closes a file with the specified file descriptor. </p>
</td>
</tr>
<tr id="row350046480090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p737987506090252"><a name="p737987506090252"></a><a name="p737987506090252"></a><a href="Utils_file.md#ga7734f32bdec1147422827ab93f12c5bd">UtilsFileRead</a> (int fd, char *buf, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1095932828090252"><a name="p1095932828090252"></a><a name="p1095932828090252"></a>int&nbsp;</p>
<p id="p1291537000090252"><a name="p1291537000090252"></a><a name="p1291537000090252"></a>Reads a specified length of data from a file with the specified file descriptor and writes the data into the buffer. </p>
</td>
</tr>
<tr id="row1317675063090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p767765788090252"><a name="p767765788090252"></a><a name="p767765788090252"></a><a href="Utils_file.md#ga40c464689432ef9952cd3425157de9b2">UtilsFileWrite</a> (int fd, const char *buf, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847552900090252"><a name="p1847552900090252"></a><a name="p1847552900090252"></a>int&nbsp;</p>
<p id="p1815629256090252"><a name="p1815629256090252"></a><a name="p1815629256090252"></a>Writes a specified length of data into a file with the specified file descriptor. </p>
</td>
</tr>
<tr id="row555555434090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521491702090252"><a name="p521491702090252"></a><a name="p521491702090252"></a><a href="Utils_file.md#ga014fb79a2be2c1c4900664a5ce2d64dc">UtilsFileDelete</a> (const char *path)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1071328508090252"><a name="p1071328508090252"></a><a name="p1071328508090252"></a>int&nbsp;</p>
<p id="p12708136090252"><a name="p12708136090252"></a><a name="p12708136090252"></a>Deletes a specified file. </p>
</td>
</tr>
<tr id="row1246631860090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p441988013090252"><a name="p441988013090252"></a><a name="p441988013090252"></a><a href="Utils_file.md#ga7eb19c588dff86f8801a212681db5dcc">UtilsFileStat</a> (const char *path, unsigned int *fileSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p391824278090252"><a name="p391824278090252"></a><a name="p391824278090252"></a>int&nbsp;</p>
<p id="p1233182208090252"><a name="p1233182208090252"></a><a name="p1233182208090252"></a>Obtains the file size. </p>
</td>
</tr>
<tr id="row121487126090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413019394090252"><a name="p1413019394090252"></a><a name="p1413019394090252"></a><a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> (int fd, int offset, unsigned int whence)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1461876641090252"><a name="p1461876641090252"></a><a name="p1461876641090252"></a>int&nbsp;</p>
<p id="p1770194559090252"><a name="p1770194559090252"></a><a name="p1770194559090252"></a>Adjusts the read and write position offset in a file. </p>
</td>
</tr>
<tr id="row1183931482090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p622756644090252"><a name="p622756644090252"></a><a name="p622756644090252"></a><a href="Utils_file.md#ga08f0677a9f668ba7738031daaed25722">UtilsFileCopy</a> (const char *src, const char *dest)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p402940138090252"><a name="p402940138090252"></a><a name="p402940138090252"></a>int&nbsp;</p>
<p id="p1345769782090252"><a name="p1345769782090252"></a><a name="p1345769782090252"></a>Copies the source file to a target file. </p>
</td>
</tr>
<tr id="row704260759090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1042872262090252"><a name="p1042872262090252"></a><a name="p1042872262090252"></a><a href="Utils_file.md#gaae711f5bc3368b36b38aaf5643dca984">UtilsFileMove</a> (const char *src, const char *dest)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459491591090252"><a name="p1459491591090252"></a><a name="p1459491591090252"></a>int&nbsp;</p>
<p id="p570715329090252"><a name="p570715329090252"></a><a name="p570715329090252"></a>Moves the source file into a target file. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section13604878090252"></a>

## **Macro Definition Documentation**<a name="section1978189461090252"></a>

## O\_APPEND\_FS<a name="gaf0446daf637d995666e937071838dd8f"></a>

```
#define O_APPEND_FS   02000
```

 **Description:**

Defines a flag used by  [UtilsFileOpen](Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899)  to start reading or writing from the end of a file. 

## O\_CREAT\_FS<a name="ga79f003e100f1a5126fbea0dc355e3483"></a>

```
#define O_CREAT_FS   0100
```

 **Description:**

Defines a flag used by  [UtilsFileOpen](Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899)  to create a file when the file to open does not exist. 

## O\_EXCL\_FS<a name="ga4d6101d81a55a4a7ba0810e39342c5c5"></a>

```
#define O_EXCL_FS   0200
```

 **Description:**

Defines a flag used by  [UtilsFileOpen](Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899)  to check whether the file to open exists when  [O\_CREAT\_FS](Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483)  is already set. 

If the file does not exist, a new file will be created. If the file exists, the file cannot be opened. 

## O\_RDONLY\_FS<a name="gaa1719eabbbb0bccff567de8507c9e24f"></a>

```
#define O_RDONLY_FS   00
```

 **Description:**

Defines a flag used by[UtilsFileOpen](Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899)  to open a file in read-only mode. 

## O\_RDWR\_FS<a name="ga76ab262236051a318fcd05f269849d4e"></a>

```
#define O_RDWR_FS   02
```

 **Description:**

Defines a flag used by  [UtilsFileOpen](Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899)  to open a file in read-and-write mode. 

## O\_TRUNC\_FS<a name="ga763cb660cbe7ddec2613116c55f5923b"></a>

```
#define O_TRUNC_FS   01000
```

 **Description:**

Defines a flag used by  [UtilsFileOpen](Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899)  to clear the file content if the file exists and can be opened in write mode. 

## O\_WRONLY\_FS<a name="gae466b69cbf84b032fc08a96ad7cf5360"></a>

```
#define O_WRONLY_FS   01
```

 **Description:**

Defines a flag used by  [UtilsFileOpen](Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899)  to open a file in write-only mode. 

## SEEK\_CUR\_FS<a name="ga46bccca36e2775acc050dec021b22e5a"></a>

```
#define SEEK_CUR_FS   1
```

 **Description:**

Defines the offset position used by  [UtilsFileSeek](Utils_file.md#ga5ae2e96182ab66be3b048a970383764c)  in a file to start offsetting from the current read and write position. 

## SEEK\_END\_FS<a name="ga6473cd9cb4026767b830c18643231dc7"></a>

```
#define SEEK_END_FS   2
```

 **Description:**

Defines the offset position used by  [UtilsFileSeek](Utils_file.md#ga5ae2e96182ab66be3b048a970383764c)  in a file to start offsetting from the end of the file. 

## SEEK\_SET\_FS<a name="gafa5fb3a195634a2b4e4f6e5e1960802a"></a>

```
#define SEEK_SET_FS   0
```

 **Description:**

Defines the offset position used by  [UtilsFileSeek](Utils_file.md#ga5ae2e96182ab66be3b048a970383764c)  in a file to start offsetting from the file header. 

## **Function Documentation**<a name="section611128505090252"></a>

## UtilsFileClose\(\)<a name="ga8a2da755514b89ca541f8e8e6c6255f3"></a>

```
int UtilsFileClose (int fd)
```

 **Description:**

Closes a file with the specified file descriptor. 

**Parameters:**

<a name="table1947792292090252"></a>
<table><thead align="left"><tr id="row667615082090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1246085127090252"><a name="p1246085127090252"></a><a name="p1246085127090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p404687878090252"><a name="p404687878090252"></a><a name="p404687878090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row8130340090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
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

<a name="table2064501038090252"></a>
<table><thead align="left"><tr id="row2131786561090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1530224014090252"><a name="p1530224014090252"></a><a name="p1530224014090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1300100015090252"><a name="p1300100015090252"></a><a name="p1300100015090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1975342825090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">src</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the source file to copy. </td>
</tr>
<tr id="row782922091090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dest</td>
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

<a name="table832786977090252"></a>
<table><thead align="left"><tr id="row2138666610090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p648682171090252"><a name="p648682171090252"></a><a name="p648682171090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p137113302090252"><a name="p137113302090252"></a><a name="p137113302090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row994940171090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">path</td>
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

<a name="table1499702673090252"></a>
<table><thead align="left"><tr id="row97052062090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1161473623090252"><a name="p1161473623090252"></a><a name="p1161473623090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p625513203090252"><a name="p625513203090252"></a><a name="p625513203090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1078876241090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">src</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the source file. </td>
</tr>
<tr id="row642466478090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dest</td>
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

<a name="table806804756090252"></a>
<table><thead align="left"><tr id="row1445908595090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p858442138090252"><a name="p858442138090252"></a><a name="p858442138090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1187723731090252"><a name="p1187723731090252"></a><a name="p1187723731090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1818404012090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">path</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file to open or create. </td>
</tr>
<tr id="row288348451090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">oflag</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the mode of opening a file. The following modes are supported. These modes can be used together, with each of them identified by "or". </td>
</tr>
<tr id="row574682032090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Used for function compatibility. This parameter does not take effect in any scenario. </td>
</tr>
</tbody>
</table>

<a name="table489834403090252"></a>
<table><thead align="left"><tr id="row951726739090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p193455261090252"><a name="p193455261090252"></a><a name="p193455261090252"></a>oflag </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1747880466090252"><a name="p1747880466090252"></a><a name="p1747880466090252"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row161979955090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2956329090252"><a name="p2956329090252"></a><a name="p2956329090252"></a>O_RDONLY_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1271519797090252"><a name="p1271519797090252"></a><a name="p1271519797090252"></a>For details, see <a href="Utils_file.md#gaa1719eabbbb0bccff567de8507c9e24f">O_RDONLY_FS</a>. </p>
</td>
</tr>
<tr id="row1082396157090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p226250039090252"><a name="p226250039090252"></a><a name="p226250039090252"></a>O_WRONLY_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p352932106090252"><a name="p352932106090252"></a><a name="p352932106090252"></a>For details, see <a href="Utils_file.md#gae466b69cbf84b032fc08a96ad7cf5360">O_WRONLY_FS</a>. </p>
</td>
</tr>
<tr id="row2058274764090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1734796871090252"><a name="p1734796871090252"></a><a name="p1734796871090252"></a>O_RDWR_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1091776571090252"><a name="p1091776571090252"></a><a name="p1091776571090252"></a>For details, see <a href="Utils_file.md#ga76ab262236051a318fcd05f269849d4e">O_RDWR_FS</a>. </p>
</td>
</tr>
<tr id="row147635708090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1293175277090252"><a name="p1293175277090252"></a><a name="p1293175277090252"></a>O_CREAT_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1956553087090252"><a name="p1956553087090252"></a><a name="p1956553087090252"></a>For details, see <a href="Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483">O_CREAT_FS</a>. </p>
</td>
</tr>
<tr id="row1227158254090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p883344963090252"><a name="p883344963090252"></a><a name="p883344963090252"></a>O_EXCL_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985642139090252"><a name="p985642139090252"></a><a name="p985642139090252"></a>For details, see <a href="Utils_file.md#ga4d6101d81a55a4a7ba0810e39342c5c5">O_EXCL_FS</a>. </p>
</td>
</tr>
<tr id="row265639787090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p360079025090252"><a name="p360079025090252"></a><a name="p360079025090252"></a>O_TRUNC_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1576307865090252"><a name="p1576307865090252"></a><a name="p1576307865090252"></a>For details, see <a href="Utils_file.md#ga763cb660cbe7ddec2613116c55f5923b">O_TRUNC_FS</a>. </p>
</td>
</tr>
<tr id="row31094937090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1798118802090252"><a name="p1798118802090252"></a><a name="p1798118802090252"></a>O_APPEND_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445192339090252"><a name="p1445192339090252"></a><a name="p1445192339090252"></a>For details, see <a href="Utils_file.md#gaf0446daf637d995666e937071838dd8f">O_APPEND_FS</a>. </p>
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

<a name="table1562178197090252"></a>
<table><thead align="left"><tr id="row1458341170090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p97971623090252"><a name="p97971623090252"></a><a name="p97971623090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p393707379090252"><a name="p393707379090252"></a><a name="p393707379090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row702012039090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file descriptor of the file to read. </td>
</tr>
<tr id="row266115083090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer that stores the read data. This is an output parameter. </td>
</tr>
<tr id="row1330179530090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
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

<a name="table1678559809090252"></a>
<table><thead align="left"><tr id="row1720250952090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p553050028090252"><a name="p553050028090252"></a><a name="p553050028090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1847889180090252"><a name="p1847889180090252"></a><a name="p1847889180090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row80278767090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file descriptor of the file where the read and write position offset needs adjustment. </td>
</tr>
<tr id="row1548253682090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">offset</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the offset of the read and write position based on the <strong id="b1932609261090252"><a name="b1932609261090252"></a><a name="b1932609261090252"></a>whence</strong> parameter. The value can be negative if the value of <strong id="b437558922090252"><a name="b437558922090252"></a><a name="b437558922090252"></a>whence</strong> is <strong id="b1431689095090252"><a name="b1431689095090252"></a><a name="b1431689095090252"></a>SEEK_CUR_FS</strong> or <strong id="b1881802759090252"><a name="b1881802759090252"></a><a name="b1881802759090252"></a>SEEK_END_FS</strong>. </td>
</tr>
<tr id="row1477111010090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">whence</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the start position of the offset. The following start positions are supported. </td>
</tr>
</tbody>
</table>

<a name="table529921206090252"></a>
<table><thead align="left"><tr id="row1961049431090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2074393992090252"><a name="p2074393992090252"></a><a name="p2074393992090252"></a>whence </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1370524845090252"><a name="p1370524845090252"></a><a name="p1370524845090252"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1185491232090252"><td class="cellrowborder" rowspan="2" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p766441572090252"><a name="p766441572090252"></a><a name="p766441572090252"></a>SEEK_SET_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p660356571090252"><a name="p660356571090252"></a><a name="p660356571090252"></a>Adjusts the read and write position to the file header. </p>
</td>
</tr>
<tr id="row792116595090252"><td class="cellrowborder" valign="top" headers="mcps1.1.3.1.1 "><p id="p1245367246090252"><a name="p1245367246090252"></a><a name="p1245367246090252"></a>Then adds the offset after the read and write position. </p>
</td>
</tr>
<tr id="row1909675213090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p368505887090252"><a name="p368505887090252"></a><a name="p368505887090252"></a>SEEK_CUR_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1209630218090252"><a name="p1209630218090252"></a><a name="p1209630218090252"></a>Adds the offset after the current read and write position. </p>
</td>
</tr>
<tr id="row766033530090252"><td class="cellrowborder" rowspan="2" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1888783558090252"><a name="p1888783558090252"></a><a name="p1888783558090252"></a>SEEK_END_FS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p452078865090252"><a name="p452078865090252"></a><a name="p452078865090252"></a>Adjusts the read and write position to the end of the file. </p>
</td>
</tr>
<tr id="row787961918090252"><td class="cellrowborder" valign="top" headers="mcps1.1.3.1.1 "><p id="p886847249090252"><a name="p886847249090252"></a><a name="p886847249090252"></a>Then adds the offset after the read and write position. </p>
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

<a name="table1290979579090252"></a>
<table><thead align="left"><tr id="row2055804334090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1765882774090252"><a name="p1765882774090252"></a><a name="p1765882774090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p360111290090252"><a name="p360111290090252"></a><a name="p360111290090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1976537308090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">path</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file name. </td>
</tr>
<tr id="row821085001090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fileSize</td>
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

<a name="table1264070477090252"></a>
<table><thead align="left"><tr id="row1203210174090252"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p547880059090252"><a name="p547880059090252"></a><a name="p547880059090252"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1947363239090252"><a name="p1947363239090252"></a><a name="p1947363239090252"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row531581075090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">fd</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the file descriptor of the file where to write the data. </td>
</tr>
<tr id="row1673361784090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the data to write. </td>
</tr>
<tr id="row1776939828090252"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the data to write. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of bytes of the data if the data is written; returns  **-1**  otherwise. 



