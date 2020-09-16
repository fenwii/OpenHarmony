# Pms\_types<a name="ZH-CN_TOPIC_0000001055039472"></a>

## **Overview**<a name="section654028751093523"></a>

Defines variables and data structures used by the permission management module. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1062221250093523"></a>

## Files<a name="files"></a>

<a name="table1208747370093523"></a>
<table><thead align="left"><tr id="row137331430093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p748113718093523"><a name="p748113718093523"></a><a name="p748113718093523"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1931685306093523"><a name="p1931685306093523"></a><a name="p1931685306093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1965751353093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p603554727093523"><a name="p603554727093523"></a><a name="p603554727093523"></a><a href="pms_types-h.md">pms_types.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p249576442093523"><a name="p249576442093523"></a><a name="p249576442093523"></a>Declares variables and data structures used by the permission management module. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1384965003093523"></a>
<table><thead align="left"><tr id="row1760091354093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1880017084093523"><a name="p1880017084093523"></a><a name="p1880017084093523"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1174289464093523"><a name="p1174289464093523"></a><a name="p1174289464093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1839295017093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p5790628093523"><a name="p5790628093523"></a><a name="p5790628093523"></a><a href="PermissionSaved.md">PermissionSaved</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p424719541093523"><a name="p424719541093523"></a><a name="p424719541093523"></a>Defines the permission, including the name, description, and whether the permission is granted. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1740405027093523"></a>
<table><thead align="left"><tr id="row1900547718093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p408744369093523"><a name="p408744369093523"></a><a name="p408744369093523"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1950599923093523"><a name="p1950599923093523"></a><a name="p1950599923093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1378003584093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1479810345093523"><a name="p1479810345093523"></a><a name="p1479810345093523"></a><a href="Pms_types.md#ga1d7d82a3741ecedc4d993b523d95c0c8">PERM_NAME_LEN</a>&nbsp;&nbsp;&nbsp;64</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p944267486093523"><a name="p944267486093523"></a><a name="p944267486093523"></a>Indicates the length of a permission name. </p>
</td>
</tr>
<tr id="row1649749172093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997815561093523"><a name="p997815561093523"></a><a name="p997815561093523"></a><a href="Pms_types.md#gafb859b51e2b9552103cf1ba665e8eb7a">PERM_DESC_LEN</a>&nbsp;&nbsp;&nbsp;128</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1143196862093523"><a name="p1143196862093523"></a><a name="p1143196862093523"></a>Indicates the length of a permission description. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table670382853093523"></a>
<table><thead align="left"><tr id="row289936890093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p539656308093523"><a name="p539656308093523"></a><a name="p539656308093523"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p544874686093523"><a name="p544874686093523"></a><a name="p544874686093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row877085388093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p678215283093523"><a name="p678215283093523"></a><a name="p678215283093523"></a><a href="Pms_types.md#ga56644f429963f015addb12e36e2344f7">IsGranted</a> { , <a href="Pms_types.md#gga56644f429963f015addb12e36e2344f7a440c8b08fdd77c2aa90283c06dbe465a">GRANTED</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p133776191093523"><a name="p133776191093523"></a><a name="p133776191093523"></a>Enumerates granting statuses of the permission. </p>
</td>
</tr>
<tr id="row1368490793093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p993283492093523"><a name="p993283492093523"></a><a name="p993283492093523"></a><a href="Pms_types.md#gacb79d7f5cd64c73479e0bdd9525265a8">PmsErrorCode</a> { , &nbsp;&nbsp;<a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8ad3d70d0327fc60a9067f853bbe938fd4">PERM_ERRORCODE_INVALID_PARAMS</a> = 10, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8ae6c8da1f46cf729021be0ee3ac28d506">PERM_ERRORCODE_INVALID_PERMNAME</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a29ad932e0c9f71f287b0854635fbfdfc">PERM_ERRORCODE_MALLOC_FAIL</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a93548eedb6a47d5240f04d9e7066ae42">PERM_ERRORCODE_OPENFD_FAIL</a>, &nbsp;&nbsp;<a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8ad5bbbd7a5c1964a8e32f8cd910d1e1b1">PERM_ERRORCODE_READFD_FAIL</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8ac9f97daf3819939bec448a74633d76dd">PERM_ERRORCODE_WRITEFD_FAIL</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a93871916c514e5e08b5e71668e78c5f9">PERM_ERRORCODE_JSONPARSE_FAIL</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a21d2c3ca74a60578d909d7e3599d2329">PERM_ERRORCODE_COPY_ERROR</a>, &nbsp;&nbsp;<a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8ab60b867e2cd8d6dad65fec5438bc9d8f">PERM_ERRORCODE_FIELD_TOO_LONG</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8ae50528fd433961afa3d384a296d7c1e1">PERM_ERRORCODE_PERM_NOT_EXIST</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8aee363de3178fe3be3d48c6b93a9ab0e2">PERM_ERRORCODE_UNLINK_ERROR</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a09f77eaf46086239b3e72abfe8629d6d">PERM_ERRORCODE_FILE_NOT_EXIST</a>, &nbsp;&nbsp;<a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a2041efbb9d8c5dd30df4894ee7cc7b1e">PERM_ERRORCODE_MEMSET_FAIL</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a62c441a20ff74358ff3400a60d11d2a2">PERM_ERRORCODE_STAT_FAIL</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8ae652b4433e08622981c7457b4ead9dd8">PERM_ERRORCODE_PATH_INVALID</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a28397170788e73451c03bdacaf07bb09">PERM_ERRORCODE_TOO_MUCH_PERM</a>, &nbsp;&nbsp;<a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a20ce1cb092907845a84f138e45d06651">PERM_ERRORCODE_TASKID_NOT_EXIST</a>, <a href="Pms_types.md#ggacb79d7f5cd64c73479e0bdd9525265a8a2e7d34ab9f33c396cac29e094277fef5">PERM_ERRORCODE_PERM_NUM_ERROR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1571045641093523"><a name="p1571045641093523"></a><a name="p1571045641093523"></a>Enumerates error codes of the permission management module. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1494447039093523"></a>

## **Macro Definition Documentation**<a name="section672684534093523"></a>

## PERM\_DESC\_LEN<a name="gafb859b51e2b9552103cf1ba665e8eb7a"></a>

```
#define PERM_DESC_LEN   128
```

 **Description:**

Indicates the length of a permission description. 

The default length is 128 bytes, including the terminating null byte  **'\\0'**. 

## PERM\_NAME\_LEN<a name="ga1d7d82a3741ecedc4d993b523d95c0c8"></a>

```
#define PERM_NAME_LEN   64
```

 **Description:**

Indicates the length of a permission name. 

The default length is 64 bytes, including the terminating null byte  **'\\0'**. 

## **Enumeration Type Documentation**<a name="section1553193258093523"></a>

## IsGranted<a name="ga56644f429963f015addb12e36e2344f7"></a>

```
enum [IsGranted](Pms_types.md#ga56644f429963f015addb12e36e2344f7)
```

 **Description:**

Enumerates granting statuses of the permission. 

<a name="table508106762093523"></a>
<table><thead align="left"><tr id="row1107882364093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1277508211093523"><a name="p1277508211093523"></a><a name="p1277508211093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1267542566093523"><a name="p1267542566093523"></a><a name="p1267542566093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row522772015093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga56644f429963f015addb12e36e2344f7a440c8b08fdd77c2aa90283c06dbe465a"><a name="gga56644f429963f015addb12e36e2344f7a440c8b08fdd77c2aa90283c06dbe465a"></a><a name="gga56644f429963f015addb12e36e2344f7a440c8b08fdd77c2aa90283c06dbe465a"></a></strong>GRANTED&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1698708848093523"><a name="p1698708848093523"></a><a name="p1698708848093523"></a>Not granted </p>
 </td>
</tr>
</tbody>
</table>

## PmsErrorCode<a name="gacb79d7f5cd64c73479e0bdd9525265a8"></a>

```
enum [PmsErrorCode](Pms_types.md#gacb79d7f5cd64c73479e0bdd9525265a8)
```

 **Description:**

Enumerates error codes of the permission management module. 

<a name="table2101249955093523"></a>
<table><thead align="left"><tr id="row1589566080093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p497649792093523"><a name="p497649792093523"></a><a name="p497649792093523"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1474797060093523"><a name="p1474797060093523"></a><a name="p1474797060093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row990332130093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8ad3d70d0327fc60a9067f853bbe938fd4"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ad3d70d0327fc60a9067f853bbe938fd4"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ad3d70d0327fc60a9067f853bbe938fd4"></a></strong>PERM_ERRORCODE_INVALID_PARAMS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1098642548093523"><a name="p1098642548093523"></a><a name="p1098642548093523"></a>Success </p>
 </td>
</tr>
<tr id="row1884961421093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8ae6c8da1f46cf729021be0ee3ac28d506"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ae6c8da1f46cf729021be0ee3ac28d506"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ae6c8da1f46cf729021be0ee3ac28d506"></a></strong>PERM_ERRORCODE_INVALID_PERMNAME&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p771734799093523"><a name="p771734799093523"></a><a name="p771734799093523"></a>Invalid parameters </p>
 </td>
</tr>
<tr id="row627655878093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a29ad932e0c9f71f287b0854635fbfdfc"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a29ad932e0c9f71f287b0854635fbfdfc"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a29ad932e0c9f71f287b0854635fbfdfc"></a></strong>PERM_ERRORCODE_MALLOC_FAIL&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1067027527093523"><a name="p1067027527093523"></a><a name="p1067027527093523"></a>Invalid permission name </p>
 </td>
</tr>
<tr id="row1886436726093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a93548eedb6a47d5240f04d9e7066ae42"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a93548eedb6a47d5240f04d9e7066ae42"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a93548eedb6a47d5240f04d9e7066ae42"></a></strong>PERM_ERRORCODE_OPENFD_FAIL&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1729982865093523"><a name="p1729982865093523"></a><a name="p1729982865093523"></a>Failed to allocate memory using the <strong id="b400815476093523"><a name="b400815476093523"></a><a name="b400815476093523"></a>malloc</strong> function. </p>
 </td>
</tr>
<tr id="row1538119687093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8ad5bbbd7a5c1964a8e32f8cd910d1e1b1"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ad5bbbd7a5c1964a8e32f8cd910d1e1b1"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ad5bbbd7a5c1964a8e32f8cd910d1e1b1"></a></strong>PERM_ERRORCODE_READFD_FAIL&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1841592892093523"><a name="p1841592892093523"></a><a name="p1841592892093523"></a>Failed to open the file descriptor. </p>
 </td>
</tr>
<tr id="row1945079534093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8ac9f97daf3819939bec448a74633d76dd"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ac9f97daf3819939bec448a74633d76dd"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ac9f97daf3819939bec448a74633d76dd"></a></strong>PERM_ERRORCODE_WRITEFD_FAIL&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p73522769093523"><a name="p73522769093523"></a><a name="p73522769093523"></a>Failed to read the file descriptor. </p>
 </td>
</tr>
<tr id="row1866448204093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a93871916c514e5e08b5e71668e78c5f9"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a93871916c514e5e08b5e71668e78c5f9"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a93871916c514e5e08b5e71668e78c5f9"></a></strong>PERM_ERRORCODE_JSONPARSE_FAIL&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1579189356093523"><a name="p1579189356093523"></a><a name="p1579189356093523"></a>Failed to write the file descriptor. </p>
 </td>
</tr>
<tr id="row79685109093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a21d2c3ca74a60578d909d7e3599d2329"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a21d2c3ca74a60578d909d7e3599d2329"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a21d2c3ca74a60578d909d7e3599d2329"></a></strong>PERM_ERRORCODE_COPY_ERROR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p56053899093523"><a name="p56053899093523"></a><a name="p56053899093523"></a>Failed to parse the JSON string. </p>
 </td>
</tr>
<tr id="row342638501093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8ab60b867e2cd8d6dad65fec5438bc9d8f"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ab60b867e2cd8d6dad65fec5438bc9d8f"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ab60b867e2cd8d6dad65fec5438bc9d8f"></a></strong>PERM_ERRORCODE_FIELD_TOO_LONG&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1954597394093523"><a name="p1954597394093523"></a><a name="p1954597394093523"></a>Failed to copy the string. </p>
 </td>
</tr>
<tr id="row76057815093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8ae50528fd433961afa3d384a296d7c1e1"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ae50528fd433961afa3d384a296d7c1e1"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ae50528fd433961afa3d384a296d7c1e1"></a></strong>PERM_ERRORCODE_PERM_NOT_EXIST&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1691216090093523"><a name="p1691216090093523"></a><a name="p1691216090093523"></a>The permission name or description is too long. </p>
 </td>
</tr>
<tr id="row384875401093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8aee363de3178fe3be3d48c6b93a9ab0e2"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8aee363de3178fe3be3d48c6b93a9ab0e2"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8aee363de3178fe3be3d48c6b93a9ab0e2"></a></strong>PERM_ERRORCODE_UNLINK_ERROR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1743459942093523"><a name="p1743459942093523"></a><a name="p1743459942093523"></a>The permission does not exist. </p>
 </td>
</tr>
<tr id="row229092117093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a09f77eaf46086239b3e72abfe8629d6d"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a09f77eaf46086239b3e72abfe8629d6d"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a09f77eaf46086239b3e72abfe8629d6d"></a></strong>PERM_ERRORCODE_FILE_NOT_EXIST&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1009564586093523"><a name="p1009564586093523"></a><a name="p1009564586093523"></a>Failed to delete the permission file. </p>
 </td>
</tr>
<tr id="row688584181093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a2041efbb9d8c5dd30df4894ee7cc7b1e"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a2041efbb9d8c5dd30df4894ee7cc7b1e"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a2041efbb9d8c5dd30df4894ee7cc7b1e"></a></strong>PERM_ERRORCODE_MEMSET_FAIL&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p744877457093523"><a name="p744877457093523"></a><a name="p744877457093523"></a>The file does not exist. </p>
 </td>
</tr>
<tr id="row548261925093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a62c441a20ff74358ff3400a60d11d2a2"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a62c441a20ff74358ff3400a60d11d2a2"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a62c441a20ff74358ff3400a60d11d2a2"></a></strong>PERM_ERRORCODE_STAT_FAIL&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p691449145093523"><a name="p691449145093523"></a><a name="p691449145093523"></a>Failed to set memory using the <strong id="b1753021715093523"><a name="b1753021715093523"></a><a name="b1753021715093523"></a>memset</strong> function. </p>
 </td>
</tr>
<tr id="row106095909093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8ae652b4433e08622981c7457b4ead9dd8"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ae652b4433e08622981c7457b4ead9dd8"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8ae652b4433e08622981c7457b4ead9dd8"></a></strong>PERM_ERRORCODE_PATH_INVALID&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369359857093523"><a name="p369359857093523"></a><a name="p369359857093523"></a>Failed to obtain information about the named file using the <strong id="b1321630381093523"><a name="b1321630381093523"></a><a name="b1321630381093523"></a>stat</strong> function. </p>
 </td>
</tr>
<tr id="row254201014093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a28397170788e73451c03bdacaf07bb09"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a28397170788e73451c03bdacaf07bb09"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a28397170788e73451c03bdacaf07bb09"></a></strong>PERM_ERRORCODE_TOO_MUCH_PERM&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1865025079093523"><a name="p1865025079093523"></a><a name="p1865025079093523"></a>Invalid path </p>
 </td>
</tr>
<tr id="row129776056093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a20ce1cb092907845a84f138e45d06651"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a20ce1cb092907845a84f138e45d06651"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a20ce1cb092907845a84f138e45d06651"></a></strong>PERM_ERRORCODE_TASKID_NOT_EXIST&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620804013093523"><a name="p620804013093523"></a><a name="p620804013093523"></a>Too many permissions </p>
 </td>
</tr>
<tr id="row2146215340093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggacb79d7f5cd64c73479e0bdd9525265a8a2e7d34ab9f33c396cac29e094277fef5"><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a2e7d34ab9f33c396cac29e094277fef5"></a><a name="ggacb79d7f5cd64c73479e0bdd9525265a8a2e7d34ab9f33c396cac29e094277fef5"></a></strong>PERM_ERRORCODE_PERM_NUM_ERROR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2130396943093523"><a name="p2130396943093523"></a><a name="p2130396943093523"></a>The process ID does not exist. </p>
 </td>
</tr>
</tbody>
</table>

## **Variable Documentation**<a name="section1452099538093523"></a>

## desc<a name="gac30cf9ead0186519b49c3ecd58e39937"></a>

```
char PermissionSaved::desc[[PERM_DESC_LEN](Pms_types.md#gafb859b51e2b9552103cf1ba665e8eb7a)]
```

 **Description:**

Permission name. For details about its length, see  [PERM\_NAME\_LEN](Pms_types.md#ga1d7d82a3741ecedc4d993b523d95c0c8). 

## granted<a name="ga1b618be368f56d0d8c857aacc5b42baf"></a>

```
enum [IsGranted](Pms_types.md#ga56644f429963f015addb12e36e2344f7) PermissionSaved::granted
```

 **Description:**

Permission description. For details about its length, see  [PERM\_DESC\_LEN](Pms_types.md#gafb859b51e2b9552103cf1ba665e8eb7a). 

