# ability\_info.h<a name="ZH-CN_TOPIC_0000001054479523"></a>

## **Overview**<a name="section1957674083093524"></a>

**Related Modules:**

[BundleManager](BundleManager.md)

**Description:**

Declares structures and functions for managing ability information. 

You can use the function provided in this file to clear ability information.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1041553760093524"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table543734020093524"></a>
<table><thead align="left"><tr id="row1760710600093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p967410859093524"><a name="p967410859093524"></a><a name="p967410859093524"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2123316474093524"><a name="p2123316474093524"></a><a name="p2123316474093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1172670133093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2053008785093524"><a name="p2053008785093524"></a><a name="p2053008785093524"></a><a href="AbilityInfo.md">AbilityInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2129249823093524"><a name="p2129249823093524"></a><a name="p2129249823093524"></a>Defines the ability information. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table972915483093524"></a>
<table><thead align="left"><tr id="row162098074093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p837980774093524"><a name="p837980774093524"></a><a name="p837980774093524"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p525022373093524"><a name="p525022373093524"></a><a name="p525022373093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1117943234093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1097109650093524"><a name="p1097109650093524"></a><a name="p1097109650093524"></a><a href="BundleManager.md#ga44b675d687acff3d739404c1227b4259">AbilityType</a> { <a href="BundleManager.md#gga44b675d687acff3d739404c1227b4259a6ce26a62afab55d7606ad4e92428b30c">UNKNOWN</a> = 0, <a href="BundleManager.md#gga44b675d687acff3d739404c1227b4259ab788d9e2cde88d51a5cda409f75db490">PAGE</a>, <a href="BundleManager.md#gga44b675d687acff3d739404c1227b4259a5f6d448017ecd0a56245e38b76596e07">SERVICE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p225039890093524"><a name="p225039890093524"></a><a name="p225039890093524"></a>Enumerates types of templates used by an ability. </p>
</td>
</tr>
<tr id="row580643503093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p620264422093524"><a name="p620264422093524"></a><a name="p620264422093524"></a><a href="BundleManager.md#ga605d46d860e356a74db6842e66522854">LaunchMode</a> { <a href="BundleManager.md#gga605d46d860e356a74db6842e66522854a57da18394d2f90538c40b0b8d4a3a3c7">SINGLETON</a> = 0, <a href="BundleManager.md#gga605d46d860e356a74db6842e66522854a9de934790934fe831fe946c851e8338e">STANDARD</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1001197814093524"><a name="p1001197814093524"></a><a name="p1001197814093524"></a>Enumerates startup modes of an ability. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table406898866093524"></a>
<table><thead align="left"><tr id="row646606308093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p8296114093524"><a name="p8296114093524"></a><a name="p8296114093524"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1612235381093524"><a name="p1612235381093524"></a><a name="p1612235381093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1688787853093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1854932118093524"><a name="p1854932118093524"></a><a name="p1854932118093524"></a><a href="BundleManager.md#ga7377545918725f75645b59b1b7a319fa">ClearAbilityInfo</a> (<a href="AbilityInfo.md">AbilityInfo</a> *abilityInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1043672355093524"><a name="p1043672355093524"></a><a name="p1043672355093524"></a>void&nbsp;</p>
<p id="p2043363460093524"><a name="p2043363460093524"></a><a name="p2043363460093524"></a>Clears an <a href="AbilityInfo.md">AbilityInfo</a> object. </p>
</td>
</tr>
</tbody>
</table>

