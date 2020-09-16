# utils\_file.h<a name="ZH-CN_TOPIC_0000001054715053"></a>

## **Overview**<a name="section403012150191853"></a>

**Related Modules:**

[Utils\_file](Utils_file.md)

**Description:**

Performs operations on a file, including to open, close, write, read, and delete a file. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section599557771191853"></a>

## Macros<a name="define-members"></a>

<a name="table959068315191853"></a>
<table><thead align="left"><tr id="row1219257688191853"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2040579362191853"><a name="p2040579362191853"></a><a name="p2040579362191853"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p93821762191853"><a name="p93821762191853"></a><a name="p93821762191853"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row950716010191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1970483557191853"><a name="p1970483557191853"></a><a name="p1970483557191853"></a><a href="Utils_file.md#gafa5fb3a195634a2b4e4f6e5e1960802a">SEEK_SET_FS</a>&nbsp;&nbsp;&nbsp;0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1268847910191853"><a name="p1268847910191853"></a><a name="p1268847910191853"></a>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the file header. </p>
</td>
</tr>
<tr id="row1269806913191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1376004564191853"><a name="p1376004564191853"></a><a name="p1376004564191853"></a><a href="Utils_file.md#ga46bccca36e2775acc050dec021b22e5a">SEEK_CUR_FS</a>&nbsp;&nbsp;&nbsp;1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1838482659191853"><a name="p1838482659191853"></a><a name="p1838482659191853"></a>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the current read and write position. </p>
</td>
</tr>
<tr id="row498725706191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245858313191853"><a name="p1245858313191853"></a><a name="p1245858313191853"></a><a href="Utils_file.md#ga6473cd9cb4026767b830c18643231dc7">SEEK_END_FS</a>&nbsp;&nbsp;&nbsp;2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1779188189191853"><a name="p1779188189191853"></a><a name="p1779188189191853"></a>Defines the offset position used by <a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> in a file to start offsetting from the end of the file. </p>
</td>
</tr>
<tr id="row337090717191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p173573375191853"><a name="p173573375191853"></a><a name="p173573375191853"></a><a href="Utils_file.md#gaa1719eabbbb0bccff567de8507c9e24f">O_RDONLY_FS</a>&nbsp;&nbsp;&nbsp;00</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1975786500191853"><a name="p1975786500191853"></a><a name="p1975786500191853"></a>Defines a flag used by<a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in read-only mode. </p>
</td>
</tr>
<tr id="row1297930447191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245730258191853"><a name="p1245730258191853"></a><a name="p1245730258191853"></a><a href="Utils_file.md#gae466b69cbf84b032fc08a96ad7cf5360">O_WRONLY_FS</a>&nbsp;&nbsp;&nbsp;01</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964620683191853"><a name="p964620683191853"></a><a name="p964620683191853"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in write-only mode. </p>
</td>
</tr>
<tr id="row1470904523191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p260387735191853"><a name="p260387735191853"></a><a name="p260387735191853"></a><a href="Utils_file.md#ga76ab262236051a318fcd05f269849d4e">O_RDWR_FS</a>&nbsp;&nbsp;&nbsp;02</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1914233536191853"><a name="p1914233536191853"></a><a name="p1914233536191853"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to open a file in read-and-write mode. </p>
</td>
</tr>
<tr id="row62296545191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p623619978191853"><a name="p623619978191853"></a><a name="p623619978191853"></a><a href="Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483">O_CREAT_FS</a>&nbsp;&nbsp;&nbsp;0100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p132335497191853"><a name="p132335497191853"></a><a name="p132335497191853"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to create a file when the file to open does not exist. </p>
</td>
</tr>
<tr id="row568606362191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1270559050191853"><a name="p1270559050191853"></a><a name="p1270559050191853"></a><a href="Utils_file.md#ga4d6101d81a55a4a7ba0810e39342c5c5">O_EXCL_FS</a>&nbsp;&nbsp;&nbsp;0200</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p783799926191853"><a name="p783799926191853"></a><a name="p783799926191853"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to check whether the file to open exists when <a href="Utils_file.md#ga79f003e100f1a5126fbea0dc355e3483">O_CREAT_FS</a> is already set. </p>
</td>
</tr>
<tr id="row63413120191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1367027965191853"><a name="p1367027965191853"></a><a name="p1367027965191853"></a><a href="Utils_file.md#ga763cb660cbe7ddec2613116c55f5923b">O_TRUNC_FS</a>&nbsp;&nbsp;&nbsp;01000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p689451984191853"><a name="p689451984191853"></a><a name="p689451984191853"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to clear the file content if the file exists and can be opened in write mode. </p>
</td>
</tr>
<tr id="row1053581917191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p317116367191853"><a name="p317116367191853"></a><a name="p317116367191853"></a><a href="Utils_file.md#gaf0446daf637d995666e937071838dd8f">O_APPEND_FS</a>&nbsp;&nbsp;&nbsp;02000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p685908369191853"><a name="p685908369191853"></a><a name="p685908369191853"></a>Defines a flag used by <a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> to start reading or writing from the end of a file. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1640050563191853"></a>
<table><thead align="left"><tr id="row1995284782191853"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p35167023191853"><a name="p35167023191853"></a><a name="p35167023191853"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1103513716191853"><a name="p1103513716191853"></a><a name="p1103513716191853"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1695862099191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p440080723191853"><a name="p440080723191853"></a><a name="p440080723191853"></a><a href="Utils_file.md#ga17115e4a2d52b37bffcbd465e2c1a899">UtilsFileOpen</a> (const char *path, int oflag, int mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2134905171191853"><a name="p2134905171191853"></a><a name="p2134905171191853"></a>int&nbsp;</p>
<p id="p1789942616191853"><a name="p1789942616191853"></a><a name="p1789942616191853"></a>Opens or creates a file. </p>
</td>
</tr>
<tr id="row123058195191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616490831191853"><a name="p1616490831191853"></a><a name="p1616490831191853"></a><a href="Utils_file.md#ga8a2da755514b89ca541f8e8e6c6255f3">UtilsFileClose</a> (int fd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1415586684191853"><a name="p1415586684191853"></a><a name="p1415586684191853"></a>int&nbsp;</p>
<p id="p735865114191853"><a name="p735865114191853"></a><a name="p735865114191853"></a>Closes a file with the specified file descriptor. </p>
</td>
</tr>
<tr id="row356810246191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p393682040191853"><a name="p393682040191853"></a><a name="p393682040191853"></a><a href="Utils_file.md#ga7734f32bdec1147422827ab93f12c5bd">UtilsFileRead</a> (int fd, char *buf, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1749644592191853"><a name="p1749644592191853"></a><a name="p1749644592191853"></a>int&nbsp;</p>
<p id="p199646501191853"><a name="p199646501191853"></a><a name="p199646501191853"></a>Reads a specified length of data from a file with the specified file descriptor and writes the data into the buffer. </p>
</td>
</tr>
<tr id="row1764903851191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p883783865191853"><a name="p883783865191853"></a><a name="p883783865191853"></a><a href="Utils_file.md#ga40c464689432ef9952cd3425157de9b2">UtilsFileWrite</a> (int fd, const char *buf, unsigned int len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1520861461191853"><a name="p1520861461191853"></a><a name="p1520861461191853"></a>int&nbsp;</p>
<p id="p756970916191853"><a name="p756970916191853"></a><a name="p756970916191853"></a>Writes a specified length of data into a file with the specified file descriptor. </p>
</td>
</tr>
<tr id="row1384368021191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p758919604191853"><a name="p758919604191853"></a><a name="p758919604191853"></a><a href="Utils_file.md#ga014fb79a2be2c1c4900664a5ce2d64dc">UtilsFileDelete</a> (const char *path)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2037079721191853"><a name="p2037079721191853"></a><a name="p2037079721191853"></a>int&nbsp;</p>
<p id="p760577581191853"><a name="p760577581191853"></a><a name="p760577581191853"></a>Deletes a specified file. </p>
</td>
</tr>
<tr id="row578316618191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p841073960191853"><a name="p841073960191853"></a><a name="p841073960191853"></a><a href="Utils_file.md#ga7eb19c588dff86f8801a212681db5dcc">UtilsFileStat</a> (const char *path, unsigned int *fileSize)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1458992713191853"><a name="p1458992713191853"></a><a name="p1458992713191853"></a>int&nbsp;</p>
<p id="p2050010395191853"><a name="p2050010395191853"></a><a name="p2050010395191853"></a>Obtains the file size. </p>
</td>
</tr>
<tr id="row1792841426191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2010244016191853"><a name="p2010244016191853"></a><a name="p2010244016191853"></a><a href="Utils_file.md#ga5ae2e96182ab66be3b048a970383764c">UtilsFileSeek</a> (int fd, int offset, unsigned int whence)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2063236589191853"><a name="p2063236589191853"></a><a name="p2063236589191853"></a>int&nbsp;</p>
<p id="p1919223718191853"><a name="p1919223718191853"></a><a name="p1919223718191853"></a>Adjusts the read and write position offset in a file. </p>
</td>
</tr>
<tr id="row108302978191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1811289540191853"><a name="p1811289540191853"></a><a name="p1811289540191853"></a><a href="Utils_file.md#ga08f0677a9f668ba7738031daaed25722">UtilsFileCopy</a> (const char *src, const char *dest)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p546726741191853"><a name="p546726741191853"></a><a name="p546726741191853"></a>int&nbsp;</p>
<p id="p462436083191853"><a name="p462436083191853"></a><a name="p462436083191853"></a>Copies the source file to a target file. </p>
</td>
</tr>
<tr id="row164448117191853"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p963757289191853"><a name="p963757289191853"></a><a name="p963757289191853"></a><a href="Utils_file.md#gaae711f5bc3368b36b38aaf5643dca984">UtilsFileMove</a> (const char *src, const char *dest)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832538994191853"><a name="p832538994191853"></a><a name="p832538994191853"></a>int&nbsp;</p>
<p id="p1842078692191853"><a name="p1842078692191853"></a><a name="p1842078692191853"></a>Moves the source file into a target file. </p>
</td>
</tr>
</tbody>
</table>

