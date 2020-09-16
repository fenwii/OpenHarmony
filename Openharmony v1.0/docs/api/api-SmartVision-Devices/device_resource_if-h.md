# device\_resource\_if.h<a name="ZH-CN_TOPIC_0000001055518054"></a>

## **Overview**<a name="section719225615093524"></a>

**Related Modules:**

[DriverConfig](DriverConfig.md)

**Description:**

Declares the API for querying the configuration tree. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section381572850093524"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1329979176093524"></a>
<table><thead align="left"><tr id="row72849452093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1555124789093524"><a name="p1555124789093524"></a><a name="p1555124789093524"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p506528448093524"><a name="p506528448093524"></a><a name="p506528448093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row50785585093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1675153535093524"><a name="p1675153535093524"></a><a name="p1675153535093524"></a><a href="DeviceResourceAttr.md">DeviceResourceAttr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1436274534093524"><a name="p1436274534093524"></a><a name="p1436274534093524"></a>Defines the attributes of a tree node in the configuration tree. </p>
</td>
</tr>
<tr id="row957474291093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1876156328093524"><a name="p1876156328093524"></a><a name="p1876156328093524"></a><a href="DeviceResourceNode.md">DeviceResourceNode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2059363642093524"><a name="p2059363642093524"></a><a name="p2059363642093524"></a>Defines a tree node in the configuration tree. </p>
</td>
</tr>
<tr id="row239098545093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p34696890093524"><a name="p34696890093524"></a><a name="p34696890093524"></a><a href="DeviceResourceIface.md">DeviceResourceIface</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1632824324093524"><a name="p1632824324093524"></a><a name="p1632824324093524"></a>Provides functions for obtaining information about the device resource configuration tree. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table105517115093524"></a>
<table><thead align="left"><tr id="row195251626093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1616479980093524"><a name="p1616479980093524"></a><a name="p1616479980093524"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p926783747093524"><a name="p926783747093524"></a><a name="p926783747093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1955663808093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1276921774093524"><a name="p1276921774093524"></a><a name="p1276921774093524"></a><a href="DriverConfig.md#gaea582d01be42ff534e33b0484094af9b">DEV_RES_NODE_FOR_EACH_ATTR</a>(node, attr)&nbsp;&nbsp;&nbsp;for ((attr) = (node)-&gt;attrData; (attr) != <a href="zh-cn_topic_0000001055198076.md#ga070d2ce7b6bb7e5c05602aa8c308d0c4">NULL</a>; (attr) = (attr)-&gt;next)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1621267436093524"><a name="p1621267436093524"></a><a name="p1621267436093524"></a>Traverses the attributes of the current configuration tree node. </p>
</td>
</tr>
<tr id="row1926411557093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1615777821093524"><a name="p1615777821093524"></a><a name="p1615777821093524"></a><a href="DriverConfig.md#ga1b848db724617a3cf0e5b3f2453b8846">DEV_RES_NODE_FOR_EACH_CHILD_NODE</a>(node, childNode)&nbsp;&nbsp;&nbsp;for ((childNode) = (node)-&gt;child; (childNode) != <a href="zh-cn_topic_0000001055198076.md#ga070d2ce7b6bb7e5c05602aa8c308d0c4">NULL</a>; (childNode) = (childNode)-&gt;sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1285045338093524"><a name="p1285045338093524"></a><a name="p1285045338093524"></a>Traverses the child nodes of the current configuration tree node. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table649856298093524"></a>
<table><thead align="left"><tr id="row437770684093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1902592019093524"><a name="p1902592019093524"></a><a name="p1902592019093524"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1865068580093524"><a name="p1865068580093524"></a><a name="p1865068580093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1997622601093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1501705719093524"><a name="p1501705719093524"></a><a name="p1501705719093524"></a><a href="DriverConfig.md#ga09c9585a5d95c79fd5ee4bd8863ba66a">DeviceResourceType</a> { <a href="DriverConfig.md#gga09c9585a5d95c79fd5ee4bd8863ba66aa7827b61588e550672bc41a3710e13ce9">HDF_CONFIG_SOURCE</a> = 0, <a href="DriverConfig.md#gga09c9585a5d95c79fd5ee4bd8863ba66aaef2863a469df3ea6871d640e3669a2f2">INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p373696566093524"><a name="p373696566093524"></a><a name="p373696566093524"></a>Enumerates configuration file types. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1604608892093524"></a>
<table><thead align="left"><tr id="row736257535093524"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p742894425093524"><a name="p742894425093524"></a><a name="p742894425093524"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1170956399093524"><a name="p1170956399093524"></a><a name="p1170956399093524"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1183212357093524"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p877442674093524"><a name="p877442674093524"></a><a name="p877442674093524"></a><a href="DriverConfig.md#gabfbfb1ffec32f04e8f3660eadb7677a0">DeviceResourceGetIfaceInstance</a> (<a href="DriverConfig.md#ga09c9585a5d95c79fd5ee4bd8863ba66a">DeviceResourceType</a> type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1084685418093524"><a name="p1084685418093524"></a><a name="p1084685418093524"></a>struct <a href="DeviceResourceIface.md">DeviceResourceIface</a> *&nbsp;</p>
<p id="p534488540093524"><a name="p534488540093524"></a><a name="p534488540093524"></a>Obtains the device resource interface handle of the corresponding configuration tree type. </p>
</td>
</tr>
</tbody>
</table>

