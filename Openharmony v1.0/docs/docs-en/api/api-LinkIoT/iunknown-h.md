# iunknown.h<a name="EN-US_TOPIC_0000001054915085"></a>

## **Overview**<a name="section619730128090253"></a>

**Related Modules:**

[Samgr](samgr.md)

**Description:**

Provides the base class and default implementation for external functions of system capabilities. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section100591794090253"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1432256756090253"></a>
<table><thead align="left"><tr id="row80805279090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p207231302090253"><a name="p207231302090253"></a><a name="p207231302090253"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p425267759090253"><a name="p425267759090253"></a><a name="p425267759090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1057911084090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p111800273090253"><a name="p111800273090253"></a><a name="p111800273090253"></a><a href="iunknown.md">IUnknown</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p791822315090253"><a name="p791822315090253"></a><a name="p791822315090253"></a>Defines the <strong id="b1067631895090253"><a name="b1067631895090253"></a><a name="b1067631895090253"></a><a href="iunknown.md">IUnknown</a></strong> class. </p>
</td>
</tr>
<tr id="row1491492178090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2069826869090253"><a name="p2069826869090253"></a><a name="p2069826869090253"></a><a href="iunknownentry.md">IUnknownEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p333430709090253"><a name="p333430709090253"></a><a name="p333430709090253"></a>Defines the <strong id="b1338944950090253"><a name="b1338944950090253"></a><a name="b1338944950090253"></a><a href="iunknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1231466853090253"></a>
<table><thead align="left"><tr id="row1813592926090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1117060316090253"><a name="p1117060316090253"></a><a name="p1117060316090253"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p647078675090253"><a name="p647078675090253"></a><a name="p647078675090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1459413745090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p140855933090253"><a name="p140855933090253"></a><a name="p140855933090253"></a><a href="samgr.md#ga13dae059206df8d2d9b9b42e694b3f9c">DEFAULT_VERSION</a>   0x20</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p149239436090253"><a name="p149239436090253"></a><a name="p149239436090253"></a>Defines the default <a href="iunknown.md">IUnknown</a> version. You can customize the version. </p>
</td>
</tr>
<tr id="row1503822619090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p665175998090253"><a name="p665175998090253"></a><a name="p665175998090253"></a><a href="samgr.md#gab74532a22d6993d0ffc014d36253397f">INHERIT_IUNKNOWN</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2093922845090253"><a name="p2093922845090253"></a><a name="p2093922845090253"></a>Defines the macro for inheriting the <strong id="b243994198090253"><a name="b243994198090253"></a><a name="b243994198090253"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1907649822090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1123102479090253"><a name="p1123102479090253"></a><a name="p1123102479090253"></a><a href="samgr.md#gad6324fd90dd636180efa2a59b377e65c">INHERIT_IUNKNOWNENTRY</a>(T)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1581084022090253"><a name="p1581084022090253"></a><a name="p1581084022090253"></a>Defines the macro for inheriting the classes that implement the <strong id="b1367041525090253"><a name="b1367041525090253"></a><a name="b1367041525090253"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row974609339090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p322563658090253"><a name="p322563658090253"></a><a name="p322563658090253"></a><a href="samgr.md#gac8d8c9671531f9340427153d50ca4a2b">DEFAULT_IUNKNOWN_IMPL</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p731841218090253"><a name="p731841218090253"></a><a name="p731841218090253"></a>Defines the default marco for initializing the <strong id="b2032355268090253"><a name="b2032355268090253"></a><a name="b2032355268090253"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1126611995090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1156362202090253"><a name="p1156362202090253"></a><a name="p1156362202090253"></a><a href="samgr.md#ga52ec6b5b03d56b0dfe7277785246bda1">IUNKNOWN_ENTRY_BEGIN</a>(version)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p900093645090253"><a name="p900093645090253"></a><a name="p900093645090253"></a>Defines the macro for initializing the classes that implement the <strong id="b398621318090253"><a name="b398621318090253"></a><a name="b398621318090253"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1941183625090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292455719090253"><a name="p1292455719090253"></a><a name="p1292455719090253"></a><a href="samgr.md#ga4ef734474ece49aa938d8ebd5b54bdb3">IUNKNOWN_ENTRY_END</a>   }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1330899573090253"><a name="p1330899573090253"></a><a name="p1330899573090253"></a><a href="iunknown.md">IUnknown</a> Defines the end macro for initializing the <strong id="b434081071090253"><a name="b434081071090253"></a><a name="b434081071090253"></a><a href="iunknown.md">IUnknown</a></strong> implementation object. </p>
</td>
</tr>
<tr id="row907737836090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p142791000090253"><a name="p142791000090253"></a><a name="p142791000090253"></a><a href="samgr.md#ga9403f55c3f75fd03854dcd37c231e05b">GET_IUNKNOWN</a>(T)   (<a href="iunknown.md">IUnknown</a> *)(&amp;((T).iUnknown))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p884419836090253"><a name="p884419836090253"></a><a name="p884419836090253"></a>Obtains the pointer of the <strong id="b320309095090253"><a name="b320309095090253"></a><a name="b320309095090253"></a><a href="iunknown.md">IUnknown</a></strong> interface object from the subclass object T (generic macro) of the <strong id="b943602423090253"><a name="b943602423090253"></a><a name="b943602423090253"></a><a href="iunknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table189408026090253"></a>
<table><thead align="left"><tr id="row1862850804090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1073852904090253"><a name="p1073852904090253"></a><a name="p1073852904090253"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p477458803090253"><a name="p477458803090253"></a><a name="p477458803090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1297190936090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p463496610090253"><a name="p463496610090253"></a><a name="p463496610090253"></a><a href="samgr.md#gacaa7db32a018a33a2bbf919cde8d8f9c">IUnknownEntry</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1665840818090253"><a name="p1665840818090253"></a><a name="p1665840818090253"></a>typedef struct <a href="iunknownentry.md">IUnknownEntry</a> </p>
<p id="p1487386067090253"><a name="p1487386067090253"></a><a name="p1487386067090253"></a>Defines the <strong id="b1850800922090253"><a name="b1850800922090253"></a><a name="b1850800922090253"></a><a href="iunknown.md">IUnknown</a></strong> implementation class. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1012909939090253"></a>
<table><thead align="left"><tr id="row2138668652090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1478800092090253"><a name="p1478800092090253"></a><a name="p1478800092090253"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1986397126090253"><a name="p1986397126090253"></a><a name="p1986397126090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1259476627090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1236131304090253"><a name="p1236131304090253"></a><a name="p1236131304090253"></a><a href="samgr.md#ga9abef49ec89bf913c3bed03faf478c1e">IUNKNOWN_AddRef</a> (<a href="iunknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p371267030090253"><a name="p371267030090253"></a><a name="p371267030090253"></a>int </p>
<p id="p1376182843090253"><a name="p1376182843090253"></a><a name="p1376182843090253"></a>Increments the reference count in this <strong id="b184360889090253"><a name="b184360889090253"></a><a name="b184360889090253"></a><a href="iunknown.md">IUnknown</a></strong> interface. </p>
</td>
</tr>
<tr id="row1821461524090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p409030512090253"><a name="p409030512090253"></a><a name="p409030512090253"></a><a href="samgr.md#gac857d12648500c7dab1cb43e85ae2ed4">IUNKNOWN_QueryInterface</a> (<a href="iunknown.md">IUnknown</a> *iUnknown, int ver, void **target)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1359651438090253"><a name="p1359651438090253"></a><a name="p1359651438090253"></a>int </p>
<p id="p1550237596090253"><a name="p1550237596090253"></a><a name="p1550237596090253"></a>Queries the <strong id="b1043927244090253"><a name="b1043927244090253"></a><a name="b1043927244090253"></a><a href="iunknown.md">IUnknown</a></strong> interfaces of a specified version (downcasting). </p>
</td>
</tr>
<tr id="row260171734090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2024212988090253"><a name="p2024212988090253"></a><a name="p2024212988090253"></a><a href="samgr.md#gabd462f8a5e6460a68760cd0719982296">IUNKNOWN_Release</a> (<a href="iunknown.md">IUnknown</a> *iUnknown)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p943583898090253"><a name="p943583898090253"></a><a name="p943583898090253"></a>int </p>
<p id="p302667683090253"><a name="p302667683090253"></a><a name="p302667683090253"></a>Releases a reference to an <strong id="b1221186974090253"><a name="b1221186974090253"></a><a name="b1221186974090253"></a><a href="iunknown.md">IUnknown</a></strong> interface that is no longer used. </p>
</td>
</tr>
</tbody>
</table>

