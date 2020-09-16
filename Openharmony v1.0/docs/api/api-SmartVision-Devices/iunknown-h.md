# iunknown.h<a name="ZH-CN_TOPIC_0000001055039488"></a>

## **Overview**<a name="section641705678084830"></a>

**Related Modules:**

[Samgr](Samgr.md)

**Description:**

Provides the base class and default implementation for external functions of system capabilities. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1156113287084830"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table895637064084830"></a>
<table><thead align="left"><tr id="row654176831084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2041187822084830"><a name="p2041187822084830"></a><a name="p2041187822084830"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p882078530084830"><a name="p882078530084830"></a><a name="p882078530084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2138181317084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p857911686084830"><a name="p857911686084830"></a><a name="p857911686084830"></a><a href="IUnknown.md">IUnknown</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p522917277084830"><a name="p522917277084830"></a><a name="p522917277084830"></a>Defines the <strong id="b692343110084830"><a name="b692343110084830"></a><a name="b692343110084830"></a><a href="IUnknown.md">IUnknown</a></strong> class. </p>
</td>
</tr>
<tr id="row54735334084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1201500953084830"><a name="p1201500953084830"></a><a name="p1201500953084830"></a><a href="IUnknownEntry.md">IUnknownEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1096899150084830"><a name="p1096899150084830"></a><a name="p1096899150084830"></a>Defines the <strong id="b1838099609084830"><a name="b1838099609084830"></a><a name="b1838099609084830"></a><a href="IUnknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table936314430084830"></a>
<table><thead align="left"><tr id="row236380279084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p450226381084830"><a name="p450226381084830"></a><a name="p450226381084830"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1260912754084830"><a name="p1260912754084830"></a><a name="p1260912754084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row625496426084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p540704124084830"><a name="p540704124084830"></a><a name="p540704124084830"></a><a href="Samgr.md#ga13dae059206df8d2d9b9b42e694b3f9c">DEFAULT_VERSION</a>&nbsp;&nbsp;&nbsp;0x20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1040984436084830"><a name="p1040984436084830"></a><a name="p1040984436084830"></a>Defines the default <a href="IUnknown.md">IUnknown</a> version. You can customize the version. </p>
</td>
</tr>
<tr id="row1652351074084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p192090493084830"><a name="p192090493084830"></a><a name="p192090493084830"></a><a href="Samgr.md#gab74532a22d6993d0ffc014d36253397f">INHERIT_IUNKNOWN</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p876554168084830"><a name="p876554168084830"></a><a name="p876554168084830"></a>Defines the macro for inheriting the <strong id="b1703088648084830"><a name="b1703088648084830"></a><a name="b1703088648084830"></a><a href="IUnknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1758856601084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1524783554084830"><a name="p1524783554084830"></a><a name="p1524783554084830"></a><a href="Samgr.md#gad6324fd90dd636180efa2a59b377e65c">INHERIT_IUNKNOWNENTRY</a>(T)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p673334611084830"><a name="p673334611084830"></a><a name="p673334611084830"></a>Defines the macro for inheriting the classes that implement the <strong id="b1078044138084830"><a name="b1078044138084830"></a><a name="b1078044138084830"></a><a href="IUnknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row520286303084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p868637436084830"><a name="p868637436084830"></a><a name="p868637436084830"></a><a href="Samgr.md#gac8d8c9671531f9340427153d50ca4a2b">DEFAULT_IUNKNOWN_IMPL</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1063932903084830"><a name="p1063932903084830"></a><a name="p1063932903084830"></a>Defines the default marco for initializing the <strong id="b1929798914084830"><a name="b1929798914084830"></a><a name="b1929798914084830"></a><a href="IUnknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1488006371084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911472658084830"><a name="p1911472658084830"></a><a name="p1911472658084830"></a><a href="Samgr.md#ga52ec6b5b03d56b0dfe7277785246bda1">IUNKNOWN_ENTRY_BEGIN</a>(version)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p580879832084830"><a name="p580879832084830"></a><a name="p580879832084830"></a>Defines the macro for initializing the classes that implement the <strong id="b1068240111084830"><a name="b1068240111084830"></a><a name="b1068240111084830"></a><a href="IUnknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1027866468084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478948441084830"><a name="p478948441084830"></a><a name="p478948441084830"></a><a href="Samgr.md#ga4ef734474ece49aa938d8ebd5b54bdb3">IUNKNOWN_ENTRY_END</a>&nbsp;&nbsp;&nbsp;}</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1649825345084830"><a name="p1649825345084830"></a><a name="p1649825345084830"></a><a href="IUnknown.md">IUnknown</a> Defines the end macro for initializing the <strong id="b1374032865084830"><a name="b1374032865084830"></a><a name="b1374032865084830"></a><a href="IUnknown.md">IUnknown</a></strong> implementation object. </p>
</td>
</tr>
<tr id="row66854266084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1051370527084830"><a name="p1051370527084830"></a><a name="p1051370527084830"></a><a href="Samgr.md#ga9403f55c3f75fd03854dcd37c231e05b">GET_IUNKNOWN</a>(T)&nbsp;&nbsp;&nbsp;(<a href="IUnknown.md">IUnknown</a> *)(&amp;((T).iUnknown))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012727949084830"><a name="p1012727949084830"></a><a name="p1012727949084830"></a>Obtains the pointer of the <strong id="b63038940084830"><a name="b63038940084830"></a><a name="b63038940084830"></a><a href="IUnknown.md">IUnknown</a></strong> interface object from the subclass object T (generic macro) of the <strong id="b990204633084830"><a name="b990204633084830"></a><a name="b990204633084830"></a><a href="IUnknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1132779026084830"></a>
<table><thead align="left"><tr id="row1103156157084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p979781369084830"><a name="p979781369084830"></a><a name="p979781369084830"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1883219171084830"><a name="p1883219171084830"></a><a name="p1883219171084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1819341537084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719609970084830"><a name="p719609970084830"></a><a name="p719609970084830"></a><a href="Samgr.md#gacaa7db32a018a33a2bbf919cde8d8f9c">IUnknownEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491855118084830"><a name="p491855118084830"></a><a name="p491855118084830"></a>typedef struct <a href="IUnknownEntry.md">IUnknownEntry</a>&nbsp;</p>
<p id="p368677031084830"><a name="p368677031084830"></a><a name="p368677031084830"></a>Defines the <strong id="b1618452053084830"><a name="b1618452053084830"></a><a name="b1618452053084830"></a><a href="IUnknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table393400514084830"></a>
<table><thead align="left"><tr id="row975647794084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p331101035084830"><a name="p331101035084830"></a><a name="p331101035084830"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1069235739084830"><a name="p1069235739084830"></a><a name="p1069235739084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1729385454084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1069954623084830"><a name="p1069954623084830"></a><a name="p1069954623084830"></a><a href="Samgr.md#ga9abef49ec89bf913c3bed03faf478c1e">IUNKNOWN_AddRef</a> (<a href="IUnknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p615411485084830"><a name="p615411485084830"></a><a name="p615411485084830"></a>int&nbsp;</p>
<p id="p1069883525084830"><a name="p1069883525084830"></a><a name="p1069883525084830"></a>Increments the reference count in this <strong id="b270675002084830"><a name="b270675002084830"></a><a name="b270675002084830"></a><a href="IUnknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row581855083084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p183784042084830"><a name="p183784042084830"></a><a name="p183784042084830"></a><a href="Samgr.md#gac857d12648500c7dab1cb43e85ae2ed4">IUNKNOWN_QueryInterface</a> (<a href="IUnknown.md">IUnknown</a> *iUnknown, int ver, void **target)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p289516873084830"><a name="p289516873084830"></a><a name="p289516873084830"></a>int&nbsp;</p>
<p id="p870707760084830"><a name="p870707760084830"></a><a name="p870707760084830"></a>Queries the <strong id="b1434275730084830"><a name="b1434275730084830"></a><a name="b1434275730084830"></a><a href="IUnknown.md">IUnknown</a></strong> interfaces of a specified version (downcasting). </p>
</td>
</tr>
<tr id="row570504233084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2115708139084830"><a name="p2115708139084830"></a><a name="p2115708139084830"></a><a href="Samgr.md#gabd462f8a5e6460a68760cd0719982296">IUNKNOWN_Release</a> (<a href="IUnknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1987659964084830"><a name="p1987659964084830"></a><a name="p1987659964084830"></a>int&nbsp;</p>
<p id="p926740162084830"><a name="p926740162084830"></a><a name="p926740162084830"></a>Releases a reference to an <strong id="b796419661084830"><a name="b796419661084830"></a><a name="b796419661084830"></a><a href="IUnknown.md">IUnknown</a></strong> interface that is no longer used. </p>
</td>
</tr>
</tbody>
</table>

