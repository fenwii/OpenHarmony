# service.h<a name="ZH-CN_TOPIC_0000001054799579"></a>

## **Overview**<a name="section1897425564084832"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Provides basic types and constants of services. 

This file is mainly used for service development. This file provides basic capabilities such as lifecycle functions of services, inherited macros, and task configuration. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section206423989084832"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1808551741084832"></a>
<table><thead align="left"><tr id="row778827067084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1949389741084832"><a name="p1949389741084832"></a><a name="p1949389741084832"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p441167528084832"><a name="p441167528084832"></a><a name="p441167528084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row181569372084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1615599360084832"><a name="p1615599360084832"></a><a name="p1615599360084832"></a><a href="TaskConfig.md">TaskConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1979168447084832"><a name="p1979168447084832"></a><a name="p1979168447084832"></a>Defines task configurations for a service. </p>
</td>
</tr>
<tr id="row1596912056084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2014326828084832"><a name="p2014326828084832"></a><a name="p2014326828084832"></a><a href="Service.md">Service</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673246394084832"><a name="p1673246394084832"></a><a name="p1673246394084832"></a>Indicates the basic type of a service. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1439620892084832"></a>
<table><thead align="left"><tr id="row1255475717084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p603171103084832"><a name="p603171103084832"></a><a name="p603171103084832"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p971257566084832"><a name="p971257566084832"></a><a name="p971257566084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1488553304084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1229362526084832"><a name="p1229362526084832"></a><a name="p1229362526084832"></a><a href="Samgr.md#gae9253a7fc1d0acbab91414b4cacc1d84">INHERIT_SERVICE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1964898069084832"><a name="p1964898069084832"></a><a name="p1964898069084832"></a>Indicates the macro used to inherit the members from the <strong id="b1598347500084832"><a name="b1598347500084832"></a><a name="b1598347500084832"></a>service</strong> class. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table2092071429084832"></a>
<table><thead align="left"><tr id="row984689225084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1136513394084832"><a name="p1136513394084832"></a><a name="p1136513394084832"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1869499282084832"><a name="p1869499282084832"></a><a name="p1869499282084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1966096118084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p51083783084832"><a name="p51083783084832"></a><a name="p51083783084832"></a><a href="Samgr.md#gab265648f2dbef93878ad8c383712b43a">TaskType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p717368430084832"><a name="p717368430084832"></a><a name="p717368430084832"></a>typedef enum <a href="Samgr.md#ga026844c14ab62f42a2e19b54d622609b">TaskType</a>&nbsp;</p>
<p id="p1704144122084832"><a name="p1704144122084832"></a><a name="p1704144122084832"></a>Enumerates task types. </p>
</td>
</tr>
<tr id="row934194729084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p308858747084832"><a name="p308858747084832"></a><a name="p308858747084832"></a><a href="Samgr.md#gae9c7eed07272a46851d61e646b6e86d5">SpecifyTag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1283453676084832"><a name="p1283453676084832"></a><a name="p1283453676084832"></a>typedef enum <a href="Samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0">SpecifyTag</a>&nbsp;</p>
<p id="p1330712667084832"><a name="p1330712667084832"></a><a name="p1330712667084832"></a>Specifies the tag for the task shared by multiple services. </p>
</td>
</tr>
<tr id="row1311919775084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p787695984084832"><a name="p787695984084832"></a><a name="p787695984084832"></a><a href="Samgr.md#gaef69bbb3353ea484414c3bbaf8ec362b">TaskPriority</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1752175139084832"><a name="p1752175139084832"></a><a name="p1752175139084832"></a>typedef enum <a href="Samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa">TaskPriority</a>&nbsp;</p>
<p id="p1820465003084832"><a name="p1820465003084832"></a><a name="p1820465003084832"></a>Enumerates task priority. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table2051308407084832"></a>
<table><thead align="left"><tr id="row310796048084832"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1567897873084832"><a name="p1567897873084832"></a><a name="p1567897873084832"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1539342999084832"><a name="p1539342999084832"></a><a name="p1539342999084832"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1912834271084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p243872560084832"><a name="p243872560084832"></a><a name="p243872560084832"></a><a href="Samgr.md#ga026844c14ab62f42a2e19b54d622609b">TaskType</a> { <a href="Samgr.md#gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99">SHARED_TASK</a> = 0, <a href="Samgr.md#gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315">SINGLE_TASK</a> = 1, <a href="Samgr.md#gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376">SPECIFIED_TASK</a> = 2, <a href="Samgr.md#gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11">NO_TASK</a> = 0xFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p114636993084832"><a name="p114636993084832"></a><a name="p114636993084832"></a>Enumerates task types. </p>
</td>
</tr>
<tr id="row1096776111084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1112342243084832"><a name="p1112342243084832"></a><a name="p1112342243084832"></a><a href="Samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0">SpecifyTag</a> { <a href="Samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955">LEVEL_HIGH</a> = 0, <a href="Samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647">LEVEL_MIDDLE</a> = 1, <a href="Samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5">LEVEL_LOW</a> = 2, <a href="Samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263">LEVEL_CUSTOM_BEGIN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1896257827084832"><a name="p1896257827084832"></a><a name="p1896257827084832"></a>Specifies the tag for the task shared by multiple services. </p>
</td>
</tr>
<tr id="row1598062355084832"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p607077759084832"><a name="p607077759084832"></a><a name="p607077759084832"></a><a href="Samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa">TaskPriority</a> { &nbsp;&nbsp;<a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402">PRI_LOW</a> = 9, <a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258">PRI_BELOW_NORMAL</a> = 16, <a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063">PRI_NORMAL</a> = 24, <a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6">PRI_ABOVE_NORMAL</a> = 32, &nbsp;&nbsp;<a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b">PRI_BUTT</a> = 39 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p609377876084832"><a name="p609377876084832"></a><a name="p609377876084832"></a>Enumerates task priority. </p>
</td>
</tr>
</tbody>
</table>

