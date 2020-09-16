# service.h<a name="ZH-CN_TOPIC_0000001054595095"></a>

## **Overview**<a name="section1772556243090253"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Provides basic types and constants of services. 

This file is mainly used for service development. This file provides basic capabilities such as lifecycle functions of services, inherited macros, and task configuration. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2113005334090253"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table805753810090253"></a>
<table><thead align="left"><tr id="row2069145768090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2032830476090253"><a name="p2032830476090253"></a><a name="p2032830476090253"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p637722508090253"><a name="p637722508090253"></a><a name="p637722508090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row707615658090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1003130161090253"><a name="p1003130161090253"></a><a name="p1003130161090253"></a><a href="TaskConfig.md">TaskConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1970170003090253"><a name="p1970170003090253"></a><a name="p1970170003090253"></a>Defines task configurations for a service. </p>
</td>
</tr>
<tr id="row849095432090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p955377861090253"><a name="p955377861090253"></a><a name="p955377861090253"></a><a href="Service.md">Service</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1598314574090253"><a name="p1598314574090253"></a><a name="p1598314574090253"></a>Indicates the basic type of a service. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1922026721090253"></a>
<table><thead align="left"><tr id="row1875298635090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p77721638090253"><a name="p77721638090253"></a><a name="p77721638090253"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1195729642090253"><a name="p1195729642090253"></a><a name="p1195729642090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1028416989090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1777540044090253"><a name="p1777540044090253"></a><a name="p1777540044090253"></a><a href="Samgr.md#gae9253a7fc1d0acbab91414b4cacc1d84">INHERIT_SERVICE</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p542720478090253"><a name="p542720478090253"></a><a name="p542720478090253"></a>Indicates the macro used to inherit the members from the <strong id="b434675994090253"><a name="b434675994090253"></a><a name="b434675994090253"></a>service</strong> class. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1152631106090253"></a>
<table><thead align="left"><tr id="row1414365446090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p186535281090253"><a name="p186535281090253"></a><a name="p186535281090253"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p899338903090253"><a name="p899338903090253"></a><a name="p899338903090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row459716883090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p122066919090253"><a name="p122066919090253"></a><a name="p122066919090253"></a><a href="Samgr.md#gab265648f2dbef93878ad8c383712b43a">TaskType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2049985716090253"><a name="p2049985716090253"></a><a name="p2049985716090253"></a>typedef enum <a href="Samgr.md#ga026844c14ab62f42a2e19b54d622609b">TaskType</a>&nbsp;</p>
<p id="p1889632983090253"><a name="p1889632983090253"></a><a name="p1889632983090253"></a>Enumerates task types. </p>
</td>
</tr>
<tr id="row109103178090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1542537032090253"><a name="p1542537032090253"></a><a name="p1542537032090253"></a><a href="Samgr.md#gae9c7eed07272a46851d61e646b6e86d5">SpecifyTag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1151003920090253"><a name="p1151003920090253"></a><a name="p1151003920090253"></a>typedef enum <a href="Samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0">SpecifyTag</a>&nbsp;</p>
<p id="p812478044090253"><a name="p812478044090253"></a><a name="p812478044090253"></a>Specifies the tag for the task shared by multiple services. </p>
</td>
</tr>
<tr id="row166243723090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1732243873090253"><a name="p1732243873090253"></a><a name="p1732243873090253"></a><a href="Samgr.md#gaef69bbb3353ea484414c3bbaf8ec362b">TaskPriority</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1726749219090253"><a name="p1726749219090253"></a><a name="p1726749219090253"></a>typedef enum <a href="Samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa">TaskPriority</a>&nbsp;</p>
<p id="p1333082242090253"><a name="p1333082242090253"></a><a name="p1333082242090253"></a>Enumerates task priority. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table776816378090253"></a>
<table><thead align="left"><tr id="row1600083462090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p650176304090253"><a name="p650176304090253"></a><a name="p650176304090253"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p174453986090253"><a name="p174453986090253"></a><a name="p174453986090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1522710603090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1065868203090253"><a name="p1065868203090253"></a><a name="p1065868203090253"></a><a href="Samgr.md#ga026844c14ab62f42a2e19b54d622609b">TaskType</a> { <a href="Samgr.md#gga026844c14ab62f42a2e19b54d622609ba5e16ebf94e3d37c775ce51bbe4468e99">SHARED_TASK</a> = 0, <a href="Samgr.md#gga026844c14ab62f42a2e19b54d622609baa1dcd6759a5b023d945ae8c955e48315">SINGLE_TASK</a> = 1, <a href="Samgr.md#gga026844c14ab62f42a2e19b54d622609ba84f51cfcf3f659a99aabbd85924c5376">SPECIFIED_TASK</a> = 2, <a href="Samgr.md#gga026844c14ab62f42a2e19b54d622609baf1a2b164c6a01dd1290f3e79171a8f11">NO_TASK</a> = 0xFF }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2116544981090253"><a name="p2116544981090253"></a><a name="p2116544981090253"></a>Enumerates task types. </p>
</td>
</tr>
<tr id="row780092727090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p953950780090253"><a name="p953950780090253"></a><a name="p953950780090253"></a><a href="Samgr.md#ga704a59a45a705ef7a15d16e3cab8c1b0">SpecifyTag</a> { <a href="Samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a5cf3038af9f9528363577dd32e4eb955">LEVEL_HIGH</a> = 0, <a href="Samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a889647ca5662082ace422e57b1da6647">LEVEL_MIDDLE</a> = 1, <a href="Samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0a1541ce26187ac34e3e99559669751cf5">LEVEL_LOW</a> = 2, <a href="Samgr.md#gga704a59a45a705ef7a15d16e3cab8c1b0afc8d0aa33bc1d911f92931fa5e287263">LEVEL_CUSTOM_BEGIN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2139806557090253"><a name="p2139806557090253"></a><a name="p2139806557090253"></a>Specifies the tag for the task shared by multiple services. </p>
</td>
</tr>
<tr id="row719869993090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p713467325090253"><a name="p713467325090253"></a><a name="p713467325090253"></a><a href="Samgr.md#gaee057e5f06a7b2533e6f58bde34d15fa">TaskPriority</a> { &nbsp;&nbsp;<a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faaf8a2513dc9a78bb09c0520af65a3f402">PRI_LOW</a> = 9, <a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faa6f05a14315026dd5f3e5bc87cf745258">PRI_BELOW_NORMAL</a> = 16, <a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faa8ffe612e81f7db9099f774b853533063">PRI_NORMAL</a> = 24, <a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faacb1f8848eb9a8c56779869b418ef9cb6">PRI_ABOVE_NORMAL</a> = 32, &nbsp;&nbsp;<a href="Samgr.md#ggaee057e5f06a7b2533e6f58bde34d15faab9766c2f87357a5cc6e3b14ccbc2c54b">PRI_BUTT</a> = 39 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p529380778090253"><a name="p529380778090253"></a><a name="p529380778090253"></a>Enumerates task priority. </p>
</td>
</tr>
</tbody>
</table>

