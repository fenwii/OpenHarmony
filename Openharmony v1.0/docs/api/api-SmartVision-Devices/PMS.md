# PMS<a name="ZH-CN_TOPIC_0000001054479519"></a>

## **Overview**<a name="section1804038249093523"></a>

Manages permissions. 

This module provides interfaces for managing permissions of third-party applications.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1030192304093523"></a>

## Files<a name="files"></a>

<a name="table1300451231093523"></a>
<table><thead align="left"><tr id="row755082270093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1997937978093523"><a name="p1997937978093523"></a><a name="p1997937978093523"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p825681923093523"><a name="p825681923093523"></a><a name="p825681923093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1561195447093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1536508164093523"><a name="p1536508164093523"></a><a name="p1536508164093523"></a><a href="pms_interface-h.md">pms_interface.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p507139866093523"><a name="p507139866093523"></a><a name="p507139866093523"></a>Declares interfaces for managing permissions. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table276730916093523"></a>
<table><thead align="left"><tr id="row1940599100093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1220986345093523"><a name="p1220986345093523"></a><a name="p1220986345093523"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1336336152093523"><a name="p1336336152093523"></a><a name="p1336336152093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1545359325093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p421680772093523"><a name="p421680772093523"></a><a name="p421680772093523"></a><a href="PMS.md#ga302af5b52a877e47436fa85b9866f26b">CheckPermission</a> (int taskID, const char *permissionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1227839693093523"><a name="p1227839693093523"></a><a name="p1227839693093523"></a>int&nbsp;</p>
<p id="p1451895412093523"><a name="p1451895412093523"></a><a name="p1451895412093523"></a>Checks whether the caller (generally a third-party application) has a specified permission of a system service API. </p>
</td>
</tr>
<tr id="row1259727857093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p647761973093523"><a name="p647761973093523"></a><a name="p647761973093523"></a><a href="PMS.md#gab279d23a1850f03e73de08b25e734679">QueryPermission</a> (const char *identifier, <a href="PermissionSaved.md">PermissionSaved</a> **permissions, int *permNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p944594007093523"><a name="p944594007093523"></a><a name="p944594007093523"></a>int&nbsp;</p>
<p id="p560419437093523"><a name="p560419437093523"></a><a name="p560419437093523"></a>Queries all permissions requested by the application and checks whether these permissions are granted. </p>
</td>
</tr>
<tr id="row1467373636093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p39860519093523"><a name="p39860519093523"></a><a name="p39860519093523"></a><a href="PMS.md#gad6c5889b56e196477152bbf4ce9f462c">GrantPermission</a> (const char *identifier, const char *permName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1683172755093523"><a name="p1683172755093523"></a><a name="p1683172755093523"></a>int&nbsp;</p>
<p id="p1544751534093523"><a name="p1544751534093523"></a><a name="p1544751534093523"></a>Grants a specified permission to the application. </p>
</td>
</tr>
<tr id="row532398545093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p700357473093523"><a name="p700357473093523"></a><a name="p700357473093523"></a><a href="PMS.md#ga75cad2f174190a59d40e963481ddcbd7">RevokePermission</a> (const char *identifier, const char *permName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1120952773093523"><a name="p1120952773093523"></a><a name="p1120952773093523"></a>int&nbsp;</p>
<p id="p787848164093523"><a name="p787848164093523"></a><a name="p787848164093523"></a>Revokes a specified permission from the application. </p>
</td>
</tr>
<tr id="row1745821041093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p881961745093523"><a name="p881961745093523"></a><a name="p881961745093523"></a><a href="PMS.md#ga796cd1425210a0cc4f6e416b1c649a1d">GrantRuntimePermission</a> (int taskID, const char *permissionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1133186295093523"><a name="p1133186295093523"></a><a name="p1133186295093523"></a>int&nbsp;</p>
<p id="p755081147093523"><a name="p755081147093523"></a><a name="p755081147093523"></a>Grants a specified runtime permission to an application. </p>
</td>
</tr>
<tr id="row1497043509093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793303330093523"><a name="p793303330093523"></a><a name="p793303330093523"></a><a href="PMS.md#ga65583c7e348108aedf5ed3c7a096e5d3">RequestPermission</a> (int taskID, const char *permissionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1611908264093523"><a name="p1611908264093523"></a><a name="p1611908264093523"></a>int&nbsp;</p>
<p id="p86308589093523"><a name="p86308589093523"></a><a name="p86308589093523"></a>Requests a specified permission. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1321206602093523"></a>

## **Function Documentation**<a name="section1888471031093523"></a>

## CheckPermission\(\)<a name="ga302af5b52a877e47436fa85b9866f26b"></a>

```
int CheckPermission (int taskID, const char * permissionName )
```

 **Description:**

Checks whether the caller \(generally a third-party application\) has a specified permission of a system service API. 

**Parameters:**

<a name="table986621750093523"></a>
<table><thead align="left"><tr id="row1546514797093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1925863475093523"><a name="p1925863475093523"></a><a name="p1925863475093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1122667900093523"><a name="p1122667900093523"></a><a name="p1122667900093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2020830790093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">taskId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the process ID of the caller. The range is [0, INT_MAX]. </td>
</tr>
<tr id="row1403323289093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">permissionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the permission name. For details, see the developer documentation. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **1**  if the caller has the permission; returns  **0**  otherwise.



## GrantPermission\(\)<a name="gad6c5889b56e196477152bbf4ce9f462c"></a>

```
int GrantPermission (const char * identifier, const char * permName )
```

 **Description:**

Grants a specified permission to the application. 

**Parameters:**

<a name="table775426778093523"></a>
<table><thead align="left"><tr id="row521998183093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p586062767093523"><a name="p586062767093523"></a><a name="p586062767093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2049216540093523"><a name="p2049216540093523"></a><a name="p2049216540093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1371167583093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identifier</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the application bundle name. </td>
</tr>
<tr id="row1721475250093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">permName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the permission name. For details, see the developer documentation. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the permission is successfully granted; returns an error code defined in  [PmsErrorCode](Pms_types.md#gacb79d7f5cd64c73479e0bdd9525265a8)  otherwise.



## GrantRuntimePermission\(\)<a name="ga796cd1425210a0cc4f6e416b1c649a1d"></a>

```
int GrantRuntimePermission (int taskID, const char * permissionName )
```

 **Description:**

Grants a specified runtime permission to an application. 

This function applies to sensitive permissions that can be granted to the application only when the application is running.

**Parameters:**

<a name="table1635158209093523"></a>
<table><thead align="left"><tr id="row1083166238093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1795980010093523"><a name="p1795980010093523"></a><a name="p1795980010093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1630632010093523"><a name="p1630632010093523"></a><a name="p1630632010093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1499170885093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">taskId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the process ID of the application. The range is [0, INT_MAX]. </td>
</tr>
<tr id="row1779445220093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">permissionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the permission name. For details, see the developer documentation. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the permission is successfully granted; returns an error code defined in  [PmsErrorCode](Pms_types.md#gacb79d7f5cd64c73479e0bdd9525265a8)  otherwise.



## QueryPermission\(\)<a name="gab279d23a1850f03e73de08b25e734679"></a>

```
int QueryPermission (const char * identifier, [PermissionSaved](PermissionSaved.md) ** permissions, int * permNum )
```

 **Description:**

Queries all permissions requested by the application and checks whether these permissions are granted. 

**Parameters:**

<a name="table1617135903093523"></a>
<table><thead align="left"><tr id="row2071274973093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2091900312093523"><a name="p2091900312093523"></a><a name="p2091900312093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p777964074093523"><a name="p777964074093523"></a><a name="p777964074093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row839572611093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identifier</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the application bundle name. </td>
</tr>
<tr id="row1190131854093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">permissions</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the array of permissions. You need to pass the <a href="PermissionSaved.md">PermissionSaved</a> pointer and release it after finishing using it. </td>
</tr>
<tr id="row931843553093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">permNum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the number of permissions in the array, which is an integer. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [PmsErrorCode](Pms_types.md#gacb79d7f5cd64c73479e0bdd9525265a8)  otherwise.



## RequestPermission\(\)<a name="ga65583c7e348108aedf5ed3c7a096e5d3"></a>

```
int RequestPermission (int taskID, const char * permissionName )
```

 **Description:**

Requests a specified permission. 

**Parameters:**

<a name="table482138403093523"></a>
<table><thead align="left"><tr id="row354840402093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1149172215093523"><a name="p1149172215093523"></a><a name="p1149172215093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p106294904093523"><a name="p106294904093523"></a><a name="p106294904093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1177550769093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">taskId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the process ID of the application. The range is [0, INT_MAX]. </td>
</tr>
<tr id="row1174117407093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">permissionName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the permission name. For details, see the developer documentation. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [PmsErrorCode](Pms_types.md#gacb79d7f5cd64c73479e0bdd9525265a8)  otherwise.



## RevokePermission\(\)<a name="ga75cad2f174190a59d40e963481ddcbd7"></a>

```
int RevokePermission (const char * identifier, const char * permName )
```

 **Description:**

Revokes a specified permission from the application. 

**Parameters:**

<a name="table2008976000093523"></a>
<table><thead align="left"><tr id="row2097175932093523"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p691604523093523"><a name="p691604523093523"></a><a name="p691604523093523"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1433376684093523"><a name="p1433376684093523"></a><a name="p1433376684093523"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1762787735093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">identifier</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the application bundle name. </td>
</tr>
<tr id="row1186004489093523"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">permName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the permission name. For details, see the developer documentation. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the permission is successfully revoked; returns an error code defined in  [PmsErrorCode](Pms_types.md#gacb79d7f5cd64c73479e0bdd9525265a8)  otherwise.



