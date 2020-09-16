# iproxy\_server.h<a name="ZH-CN_TOPIC_0000001054799571"></a>

## **Overview**<a name="section1974448822093525"></a>

**Related Modules:**

[Registry](Registry.md)

**Description:**

Provides the server proxy. 

This feature is required for providing cross-process system capabilities. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section117344686093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1648565140093525"></a>
<table><thead align="left"><tr id="row771502531093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1532829897093525"><a name="p1532829897093525"></a><a name="p1532829897093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1586962136093525"><a name="p1586962136093525"></a><a name="p1586962136093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1391429281093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691933346093525"><a name="p691933346093525"></a><a name="p691933346093525"></a><a href="IServerProxy.md">IServerProxy</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1206073212093525"><a name="p1206073212093525"></a><a name="p1206073212093525"></a>Defines the base class of the server proxy object. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table916461642093525"></a>
<table><thead align="left"><tr id="row184177833093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1729806093525"><a name="p1729806093525"></a><a name="p1729806093525"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p279414057093525"><a name="p279414057093525"></a><a name="p279414057093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row554611739093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2073896413093525"><a name="p2073896413093525"></a><a name="p2073896413093525"></a><a href="Registry.md#gad513d97bfb873f27c9b8f69a5a418d55">SERVER_PROXY_VER</a>&nbsp;&nbsp;&nbsp;0x80</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p596425774093525"><a name="p596425774093525"></a><a name="p596425774093525"></a>Defines the default version number of the server proxy. </p>
</td>
</tr>
<tr id="row140348555093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p164952268093525"><a name="p164952268093525"></a><a name="p164952268093525"></a><a href="Registry.md#ga58e6d24ef278dceb3fb9c77527acdb5c">INHERIT_SERVER_IPROXY</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p788675352093525"><a name="p788675352093525"></a><a name="p788675352093525"></a>Inherits the server proxy function. </p>
</td>
</tr>
<tr id="row619605524093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1850412541093525"><a name="p1850412541093525"></a><a name="p1850412541093525"></a><a href="Registry.md#ga9ad9b5f0e1f50f2528cbef67957b2319">INHERIT_IPROXY_ENTRY</a>(T)&nbsp;&nbsp;&nbsp;<a href="Samgr.md#gad6324fd90dd636180efa2a59b377e65c">INHERIT_IUNKNOWNENTRY</a>(T)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1160366110093525"><a name="p1160366110093525"></a><a name="p1160366110093525"></a>Inherits the server proxy class. </p>
</td>
</tr>
<tr id="row1690149409093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1476917419093525"><a name="p1476917419093525"></a><a name="p1476917419093525"></a><a href="Registry.md#ga3c3f1e77cc1a495f48a4b3cd0f8934be">SERVER_IPROXY_BEGIN</a>&nbsp;&nbsp;&nbsp;<a href="Samgr.md#ga52ec6b5b03d56b0dfe7277785246bda1">IUNKNOWN_ENTRY_BEGIN</a>(<a href="Registry.md#gad513d97bfb873f27c9b8f69a5a418d55">SERVER_PROXY_VER</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1369745791093525"><a name="p1369745791093525"></a><a name="p1369745791093525"></a>Defines the beginning of the default initialization for the server proxy class. </p>
</td>
</tr>
<tr id="row1740203272093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1039179512093525"><a name="p1039179512093525"></a><a name="p1039179512093525"></a><a href="Registry.md#ga59b6c10043506af716ce9052a5a964a7">IPROXY_END</a>&nbsp;&nbsp;&nbsp;<a href="Samgr.md#ga4ef734474ece49aa938d8ebd5b54bdb3">IUNKNOWN_ENTRY_END</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p318350127093525"><a name="p318350127093525"></a><a name="p318350127093525"></a>Defines the end of the default initialization for the server proxy class. </p>
</td>
</tr>
</tbody>
</table>

