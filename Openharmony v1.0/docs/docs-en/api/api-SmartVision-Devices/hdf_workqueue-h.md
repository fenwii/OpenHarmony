# hdf\_workqueue.h<a name="EN-US_TOPIC_0000001054718095"></a>

## **Overview**<a name="section1234926961084830"></a>

**Related Modules:**

[DriverUtils](driverutils.md)

**Description:**

Declares work queue structures and interfaces. 

This file provides interfaces such as initializing a work queue, a work item, and a delayed work item, adding a work or delayed work item to a work queue, and destroying a work queue, a work item, and a delayed work item. You need to define a work queue, a work item, and a delayed work item, and then call the initialization function to initialize them. The work item, delayed work item, and work queue must be destroyed when they are no longer used.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1843817954084830"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1611516449084830"></a>
<table><thead align="left"><tr id="row1360238883084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1968042402084830"><a name="p1968042402084830"></a><a name="p1968042402084830"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p943818314084830"><a name="p943818314084830"></a><a name="p943818314084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1434911255084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p514069162084830"><a name="p514069162084830"></a><a name="p514069162084830"></a><a href="hdfwork.md">HdfWork</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p907779839084830"><a name="p907779839084830"></a><a name="p907779839084830"></a>Describes a work item and a delayed work item. This structure defines the work and delayed work items, and then calls the initialization function <a href="driverutils.md#gad171adc8eda320fd01049a2b87ea62fb">HdfWorkInit</a> or <a href="driverutils.md#ga55bf669dc6740c65e4d45a4f641db2f1">HdfDelayedWorkInit</a> to perform initialization. The <strong id="b614088124084830"><a name="b614088124084830"></a><a name="b614088124084830"></a><a href="driverutils.md#ga82cc68d656aa17317634b07d49dae160">HdfAddWork()</a></strong> function is to add a work item to a work queue immediately, and the <strong id="b1217678816084830"><a name="b1217678816084830"></a><a name="b1217678816084830"></a><a href="driverutils.md#gaef781ccc1579db3070745088da47b2c5">HdfAddDelayedWork()</a></strong> function is to add a work item to a work queue after the configured delayed time. </p>
</td>
</tr>
<tr id="row1802013458084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p998152855084830"><a name="p998152855084830"></a><a name="p998152855084830"></a><a href="hdfworkqueue.md">HdfWorkQueue</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1365611694084830"><a name="p1365611694084830"></a><a name="p1365611694084830"></a>Describes a work queue. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1345698165084830"></a>
<table><thead align="left"><tr id="row1597367619084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1031734572084830"><a name="p1031734572084830"></a><a name="p1031734572084830"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1460598530084830"><a name="p1460598530084830"></a><a name="p1460598530084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row490139171084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1102368224084830"><a name="p1102368224084830"></a><a name="p1102368224084830"></a><a href="driverutils.md#ga30665d61b03fae4a2ebc778c3d775ce5">HdfWorkFunc</a>) (void *)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p269047179084830"><a name="p269047179084830"></a><a name="p269047179084830"></a>typedef void(* </p>
<p id="p1999600304084830"><a name="p1999600304084830"></a><a name="p1999600304084830"></a>Describes a work execution function type. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1556875748084830"></a>
<table><thead align="left"><tr id="row2124463498084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1496982916084830"><a name="p1496982916084830"></a><a name="p1496982916084830"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1776550794084830"><a name="p1776550794084830"></a><a name="p1776550794084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row669166566084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1601257371084830"><a name="p1601257371084830"></a><a name="p1601257371084830"></a>{ <a href="driverutils.md#ggaabfcbcb5ac86a1edac4035264bc7d2b8a75df1ca644f77f78bf3539e356f2e446">HDF_WORK_BUSY_PENDING</a> = 1 &lt;&lt; 0, <a href="driverutils.md#ggaabfcbcb5ac86a1edac4035264bc7d2b8a56532f81e262cca4680e754627d6dc44">HDF_WORK_BUSY_RUNNING</a> = 1 &lt;&lt; 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1971952756084830"><a name="p1971952756084830"></a><a name="p1971952756084830"></a>Enumerates statuses of a work item or a delayed work item. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table441679450084830"></a>
<table><thead align="left"><tr id="row339047166084830"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p232532670084830"><a name="p232532670084830"></a><a name="p232532670084830"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p841794344084830"><a name="p841794344084830"></a><a name="p841794344084830"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row147242575084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1313646015084830"><a name="p1313646015084830"></a><a name="p1313646015084830"></a><a href="driverutils.md#gad7afae1dc691818c513094c873decabd">HdfWorkQueueInit</a> (<a href="hdfworkqueue.md">HdfWorkQueue</a> *queue, char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1706687062084830"><a name="p1706687062084830"></a><a name="p1706687062084830"></a>int32_t </p>
<p id="p284401409084830"><a name="p284401409084830"></a><a name="p284401409084830"></a>Initializes a work queue. </p>
</td>
</tr>
<tr id="row556623978084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p599591141084830"><a name="p599591141084830"></a><a name="p599591141084830"></a><a href="driverutils.md#gad171adc8eda320fd01049a2b87ea62fb">HdfWorkInit</a> (<a href="hdfwork.md">HdfWork</a> *work, <a href="driverutils.md#ga30665d61b03fae4a2ebc778c3d775ce5">HdfWorkFunc</a> func, void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1755883664084830"><a name="p1755883664084830"></a><a name="p1755883664084830"></a>int32_t </p>
<p id="p416488721084830"><a name="p416488721084830"></a><a name="p416488721084830"></a>Initializes a work item. </p>
</td>
</tr>
<tr id="row1787455279084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2064729633084830"><a name="p2064729633084830"></a><a name="p2064729633084830"></a><a href="driverutils.md#ga55bf669dc6740c65e4d45a4f641db2f1">HdfDelayedWorkInit</a> (<a href="hdfwork.md">HdfWork</a> *work, <a href="driverutils.md#ga30665d61b03fae4a2ebc778c3d775ce5">HdfWorkFunc</a> func, void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1344171128084830"><a name="p1344171128084830"></a><a name="p1344171128084830"></a>int32_t </p>
<p id="p1602471906084830"><a name="p1602471906084830"></a><a name="p1602471906084830"></a>Initializes a delayed work item. </p>
</td>
</tr>
<tr id="row477224259084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1121109798084830"><a name="p1121109798084830"></a><a name="p1121109798084830"></a><a href="driverutils.md#gae6166caaf1b114e17834c50414b2d52e">HdfWorkDestroy</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1238969536084830"><a name="p1238969536084830"></a><a name="p1238969536084830"></a>void </p>
<p id="p1967184621084830"><a name="p1967184621084830"></a><a name="p1967184621084830"></a>Destroys a work item. </p>
</td>
</tr>
<tr id="row1014511519084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p463421174084830"><a name="p463421174084830"></a><a name="p463421174084830"></a><a href="driverutils.md#ga04ec328639aefd71683175e4c214fb80">HdfWorkQueueDestroy</a> (<a href="hdfworkqueue.md">HdfWorkQueue</a> *queue)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p891089876084830"><a name="p891089876084830"></a><a name="p891089876084830"></a>void </p>
<p id="p258088213084830"><a name="p258088213084830"></a><a name="p258088213084830"></a>Destroys a work queue. </p>
</td>
</tr>
<tr id="row1811834620084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1034360051084830"><a name="p1034360051084830"></a><a name="p1034360051084830"></a><a href="driverutils.md#gaaaced5c0365d1a1232167b738f08b5ce">HdfDelayedWorkDestroy</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681311062084830"><a name="p1681311062084830"></a><a name="p1681311062084830"></a>void </p>
<p id="p1748378682084830"><a name="p1748378682084830"></a><a name="p1748378682084830"></a>Destroys a delayed work item. </p>
</td>
</tr>
<tr id="row347413514084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1595651010084830"><a name="p1595651010084830"></a><a name="p1595651010084830"></a><a href="driverutils.md#ga82cc68d656aa17317634b07d49dae160">HdfAddWork</a> (<a href="hdfworkqueue.md">HdfWorkQueue</a> *queue, <a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p875301184084830"><a name="p875301184084830"></a><a name="p875301184084830"></a>bool </p>
<p id="p1896119807084830"><a name="p1896119807084830"></a><a name="p1896119807084830"></a>Adds a work item to a work queue. </p>
</td>
</tr>
<tr id="row946016147084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p359686978084830"><a name="p359686978084830"></a><a name="p359686978084830"></a><a href="driverutils.md#gaef781ccc1579db3070745088da47b2c5">HdfAddDelayedWork</a> (<a href="hdfworkqueue.md">HdfWorkQueue</a> *queue, <a href="hdfwork.md">HdfWork</a> *work, unsigned long ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p258667420084830"><a name="p258667420084830"></a><a name="p258667420084830"></a>bool </p>
<p id="p1833995004084830"><a name="p1833995004084830"></a><a name="p1833995004084830"></a>Adds a delayed work item to a work queue. </p>
</td>
</tr>
<tr id="row1727584565084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p623052194084830"><a name="p623052194084830"></a><a name="p623052194084830"></a><a href="driverutils.md#ga37595ed36b8ce7be84c914aebfd99d00">HdfWorkBusy</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p521268089084830"><a name="p521268089084830"></a><a name="p521268089084830"></a>unsigned int </p>
<p id="p1799315868084830"><a name="p1799315868084830"></a><a name="p1799315868084830"></a>Obtains the status of a work item or delayed work item. </p>
</td>
</tr>
<tr id="row1501275061084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1665384149084830"><a name="p1665384149084830"></a><a name="p1665384149084830"></a><a href="driverutils.md#gaab300487bdb9f3496bb823c657275dd3">HdfCancelWorkSync</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p420342372084830"><a name="p420342372084830"></a><a name="p420342372084830"></a>bool </p>
<p id="p358413145084830"><a name="p358413145084830"></a><a name="p358413145084830"></a>Cancels a work item. This function waits until the work item is complete. </p>
</td>
</tr>
<tr id="row768685854084830"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527212482084830"><a name="p1527212482084830"></a><a name="p1527212482084830"></a><a href="driverutils.md#gad53e46938809200db3caafdc85decc5a">HdfCancelDelayedWorkSync</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1546014179084830"><a name="p1546014179084830"></a><a name="p1546014179084830"></a>bool </p>
<p id="p69545758084830"><a name="p69545758084830"></a><a name="p69545758084830"></a>Cancels a delayed work item. </p>
</td>
</tr>
</tbody>
</table>

