# pms\_interface.h<a name="ZH-CN_TOPIC_0000001054718103"></a>

## **Overview**<a name="section1774234485093527"></a>

**Related Modules:**

[PMS](PMS.md)

**Description:**

Declares interfaces for managing permissions. 

The interfaces can be used to authenticate native APIs, query, grant, and revoke permissions, and grant runtime permissions.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1957012543093527"></a>

## Functions<a name="func-members"></a>

<a name="table1076346304093527"></a>
<table><thead align="left"><tr id="row134118961093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p507899657093527"><a name="p507899657093527"></a><a name="p507899657093527"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p24886805093527"><a name="p24886805093527"></a><a name="p24886805093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row460410146093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1325178043093527"><a name="p1325178043093527"></a><a name="p1325178043093527"></a><a href="PMS.md#ga302af5b52a877e47436fa85b9866f26b">CheckPermission</a> (int taskID, const char *permissionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087114830093527"><a name="p2087114830093527"></a><a name="p2087114830093527"></a>int&nbsp;</p>
<p id="p1628533499093527"><a name="p1628533499093527"></a><a name="p1628533499093527"></a>Checks whether the caller (generally a third-party application) has a specified permission of a system service API. </p>
</td>
</tr>
<tr id="row1654263366093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p431802064093527"><a name="p431802064093527"></a><a name="p431802064093527"></a><a href="PMS.md#gab279d23a1850f03e73de08b25e734679">QueryPermission</a> (const char *identifier, <a href="PermissionSaved.md">PermissionSaved</a> **permissions, int *permNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492483446093527"><a name="p492483446093527"></a><a name="p492483446093527"></a>int&nbsp;</p>
<p id="p303933224093527"><a name="p303933224093527"></a><a name="p303933224093527"></a>Queries all permissions requested by the application and checks whether these permissions are granted. </p>
</td>
</tr>
<tr id="row469711285093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p145497226093527"><a name="p145497226093527"></a><a name="p145497226093527"></a><a href="PMS.md#gad6c5889b56e196477152bbf4ce9f462c">GrantPermission</a> (const char *identifier, const char *permName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1552506873093527"><a name="p1552506873093527"></a><a name="p1552506873093527"></a>int&nbsp;</p>
<p id="p184249090093527"><a name="p184249090093527"></a><a name="p184249090093527"></a>Grants a specified permission to the application. </p>
</td>
</tr>
<tr id="row922448599093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p989276168093527"><a name="p989276168093527"></a><a name="p989276168093527"></a><a href="PMS.md#ga75cad2f174190a59d40e963481ddcbd7">RevokePermission</a> (const char *identifier, const char *permName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1086355913093527"><a name="p1086355913093527"></a><a name="p1086355913093527"></a>int&nbsp;</p>
<p id="p1275966913093527"><a name="p1275966913093527"></a><a name="p1275966913093527"></a>Revokes a specified permission from the application. </p>
</td>
</tr>
<tr id="row1659828800093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1923736765093527"><a name="p1923736765093527"></a><a name="p1923736765093527"></a><a href="PMS.md#ga796cd1425210a0cc4f6e416b1c649a1d">GrantRuntimePermission</a> (int taskID, const char *permissionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1872629296093527"><a name="p1872629296093527"></a><a name="p1872629296093527"></a>int&nbsp;</p>
<p id="p1879628209093527"><a name="p1879628209093527"></a><a name="p1879628209093527"></a>Grants a specified runtime permission to an application. </p>
</td>
</tr>
<tr id="row472390128093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1362770478093527"><a name="p1362770478093527"></a><a name="p1362770478093527"></a><a href="PMS.md#ga65583c7e348108aedf5ed3c7a096e5d3">RequestPermission</a> (int taskID, const char *permissionName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1776540323093527"><a name="p1776540323093527"></a><a name="p1776540323093527"></a>int&nbsp;</p>
<p id="p1374784225093527"><a name="p1374784225093527"></a><a name="p1374784225093527"></a>Requests a specified permission. </p>
</td>
</tr>
</tbody>
</table>

