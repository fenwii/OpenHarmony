# DriverConfig<a name="ZH-CN_TOPIC_0000001055678040"></a>

## **Overview**<a name="section2001887733093521"></a>

Defines an API for HDF driver developers to read driver configuration information. 

During version compilation of the device resource source file defined by developers, the compilation tool \(for example, the compilation tool of the HCS file is hc-gen\) generates bytecodes. When the HDF starts, it transfers the bytecode memory to the  **DriverConfig**  module. The  **DriverConfig**  module converts the bytecodes into a configuration tree and provides an API for developers to query the tree.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1148166350093521"></a>

## Files<a name="files"></a>

<a name="table861132199093521"></a>
<table><thead align="left"><tr id="row2021548233093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p563723604093521"><a name="p563723604093521"></a><a name="p563723604093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1817051643093521"><a name="p1817051643093521"></a><a name="p1817051643093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row289997896093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p106947936093521"><a name="p106947936093521"></a><a name="p106947936093521"></a><a href="device_resource_if-h.md">device_resource_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p776029536093521"><a name="p776029536093521"></a><a name="p776029536093521"></a>Declares the API for querying the configuration tree. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1246379501093521"></a>
<table><thead align="left"><tr id="row1043525628093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1282515541093521"><a name="p1282515541093521"></a><a name="p1282515541093521"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p989243506093521"><a name="p989243506093521"></a><a name="p989243506093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1881446183093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p581218983093521"><a name="p581218983093521"></a><a name="p581218983093521"></a><a href="DeviceResourceAttr.md">DeviceResourceAttr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p319042923093521"><a name="p319042923093521"></a><a name="p319042923093521"></a>Defines the attributes of a tree node in the configuration tree. </p>
</td>
</tr>
<tr id="row244028421093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1019387477093521"><a name="p1019387477093521"></a><a name="p1019387477093521"></a><a href="DeviceResourceNode.md">DeviceResourceNode</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p487071105093521"><a name="p487071105093521"></a><a name="p487071105093521"></a>Defines a tree node in the configuration tree. </p>
</td>
</tr>
<tr id="row62993263093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1807201055093521"><a name="p1807201055093521"></a><a name="p1807201055093521"></a><a href="DeviceResourceIface.md">DeviceResourceIface</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p596282317093521"><a name="p596282317093521"></a><a name="p596282317093521"></a>Provides functions for obtaining information about the device resource configuration tree. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table2124123261093521"></a>
<table><thead align="left"><tr id="row280176795093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p42934148093521"><a name="p42934148093521"></a><a name="p42934148093521"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p850341126093521"><a name="p850341126093521"></a><a name="p850341126093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row837450485093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p17078096093521"><a name="p17078096093521"></a><a name="p17078096093521"></a><a href="DriverConfig.md#gaea582d01be42ff534e33b0484094af9b">DEV_RES_NODE_FOR_EACH_ATTR</a>(node, attr)&nbsp;&nbsp;&nbsp;for ((attr) = (node)-&gt;attrData; (attr) != <a href="zh-cn_topic_0000001055198076.md#ga070d2ce7b6bb7e5c05602aa8c308d0c4">NULL</a>; (attr) = (attr)-&gt;next)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p992892153093521"><a name="p992892153093521"></a><a name="p992892153093521"></a>Traverses the attributes of the current configuration tree node. </p>
</td>
</tr>
<tr id="row10054648093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p724973173093521"><a name="p724973173093521"></a><a name="p724973173093521"></a><a href="DriverConfig.md#ga1b848db724617a3cf0e5b3f2453b8846">DEV_RES_NODE_FOR_EACH_CHILD_NODE</a>(node, childNode)&nbsp;&nbsp;&nbsp;for ((childNode) = (node)-&gt;child; (childNode) != <a href="zh-cn_topic_0000001055198076.md#ga070d2ce7b6bb7e5c05602aa8c308d0c4">NULL</a>; (childNode) = (childNode)-&gt;sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1641924510093521"><a name="p1641924510093521"></a><a name="p1641924510093521"></a>Traverses the child nodes of the current configuration tree node. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1467230069093521"></a>
<table><thead align="left"><tr id="row433656087093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1837446934093521"><a name="p1837446934093521"></a><a name="p1837446934093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1745612756093521"><a name="p1745612756093521"></a><a name="p1745612756093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2057174590093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1934690929093521"><a name="p1934690929093521"></a><a name="p1934690929093521"></a><a href="DriverConfig.md#ga09c9585a5d95c79fd5ee4bd8863ba66a">DeviceResourceType</a> { <a href="DriverConfig.md#gga09c9585a5d95c79fd5ee4bd8863ba66aa7827b61588e550672bc41a3710e13ce9">HDF_CONFIG_SOURCE</a> = 0, <a href="DriverConfig.md#gga09c9585a5d95c79fd5ee4bd8863ba66aaef2863a469df3ea6871d640e3669a2f2">INVALID</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832481284093521"><a name="p832481284093521"></a><a name="p832481284093521"></a>Enumerates configuration file types. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1680253383093521"></a>
<table><thead align="left"><tr id="row1865247946093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1379291322093521"><a name="p1379291322093521"></a><a name="p1379291322093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1740910582093521"><a name="p1740910582093521"></a><a name="p1740910582093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2023445878093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p30367556093521"><a name="p30367556093521"></a><a name="p30367556093521"></a><a href="DriverConfig.md#gabfbfb1ffec32f04e8f3660eadb7677a0">DeviceResourceGetIfaceInstance</a> (<a href="DriverConfig.md#ga09c9585a5d95c79fd5ee4bd8863ba66a">DeviceResourceType</a> type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p888904383093521"><a name="p888904383093521"></a><a name="p888904383093521"></a>struct <a href="DeviceResourceIface.md">DeviceResourceIface</a> *&nbsp;</p>
<p id="p138131052093521"><a name="p138131052093521"></a><a name="p138131052093521"></a>Obtains the device resource interface handle of the corresponding configuration tree type. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1600667479093521"></a>

## **Macro Definition Documentation**<a name="section136771460093521"></a>

## DEV\_RES\_NODE\_FOR\_EACH\_ATTR<a name="gaea582d01be42ff534e33b0484094af9b"></a>

```
#define DEV_RES_NODE_FOR_EACH_ATTR( node,  attr )   for ((attr) = (node)->attrData; (attr) != [NULL](zh-cn_topic_0000001055198076.md#ga070d2ce7b6bb7e5c05602aa8c308d0c4); (attr) = (attr)->next)
```

 **Description:**

Traverses the attributes of the current configuration tree node. 

This operation is a  **for**  loop in essence.

**Parameters:**

<a name="table544446605093521"></a>
<table><thead align="left"><tr id="row839777374093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1431269272093521"><a name="p1431269272093521"></a><a name="p1431269272093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2063731717093521"><a name="p2063731717093521"></a><a name="p2063731717093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row528967700093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the configuration tree node to traverse. </td>
</tr>
<tr id="row655952578093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the traversed attributes. </td>
</tr>
</tbody>
</table>

## DEV\_RES\_NODE\_FOR\_EACH\_CHILD\_NODE<a name="ga1b848db724617a3cf0e5b3f2453b8846"></a>

```
#define DEV_RES_NODE_FOR_EACH_CHILD_NODE( node,  childNode )   for ((childNode) = (node)->child; (childNode) != [NULL](zh-cn_topic_0000001055198076.md#ga070d2ce7b6bb7e5c05602aa8c308d0c4); (childNode) = (childNode)->sibling)
```

 **Description:**

Traverses the child nodes of the current configuration tree node. 

This operation is a  **for**  loop in essence.

**Parameters:**

<a name="table1595126624093521"></a>
<table><thead align="left"><tr id="row943733954093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1507238433093521"><a name="p1507238433093521"></a><a name="p1507238433093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1987105526093521"><a name="p1987105526093521"></a><a name="p1987105526093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1603514489093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the configuration tree node to traverse. </td>
</tr>
<tr id="row295562436093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">childNode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the traversed child nodes. </td>
</tr>
</tbody>
</table>

## **Enumeration Type Documentation**<a name="section840063954093521"></a>

## DeviceResourceType<a name="ga09c9585a5d95c79fd5ee4bd8863ba66a"></a>

```
enum [DeviceResourceType](DriverConfig.md#ga09c9585a5d95c79fd5ee4bd8863ba66a)
```

 **Description:**

Enumerates configuration file types. 

<a name="table491312470093521"></a>
<table><thead align="left"><tr id="row1655993568093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1290293639093521"><a name="p1290293639093521"></a><a name="p1290293639093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1889208917093521"><a name="p1889208917093521"></a><a name="p1889208917093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row752681433093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga09c9585a5d95c79fd5ee4bd8863ba66aa7827b61588e550672bc41a3710e13ce9"><a name="gga09c9585a5d95c79fd5ee4bd8863ba66aa7827b61588e550672bc41a3710e13ce9"></a><a name="gga09c9585a5d95c79fd5ee4bd8863ba66aa7827b61588e550672bc41a3710e13ce9"></a></strong>HDF_CONFIG_SOURCE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142843555093521"><a name="p142843555093521"></a><a name="p142843555093521"></a>HDF configuration file </p>
 </td>
</tr>
<tr id="row913402320093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga09c9585a5d95c79fd5ee4bd8863ba66aaef2863a469df3ea6871d640e3669a2f2"><a name="gga09c9585a5d95c79fd5ee4bd8863ba66aaef2863a469df3ea6871d640e3669a2f2"></a><a name="gga09c9585a5d95c79fd5ee4bd8863ba66aaef2863a469df3ea6871d640e3669a2f2"></a></strong>INVALID&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1159887801093521"><a name="p1159887801093521"></a><a name="p1159887801093521"></a>Invalid configuration file type </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section687736995093521"></a>

## DeviceResourceGetIfaceInstance\(\)<a name="gabfbfb1ffec32f04e8f3660eadb7677a0"></a>

```
struct [DeviceResourceIface](DeviceResourceIface.md)* DeviceResourceGetIfaceInstance ([DeviceResourceType](DriverConfig.md#ga09c9585a5d95c79fd5ee4bd8863ba66a) type)
```

 **Description:**

Obtains the device resource interface handle of the corresponding configuration tree type. 

You can use the obtained handle to use the device resource interface.

**Parameters:**

<a name="table61495903093521"></a>
<table><thead align="left"><tr id="row1819756474093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1102010014093521"><a name="p1102010014093521"></a><a name="p1102010014093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p701322174093521"><a name="p701322174093521"></a><a name="p701322174093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row579431028093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the type of the device resource interface handle to obtain.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the device resource interface handle if the operation is successful; returns  **NULL**  otherwise. 



