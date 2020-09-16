# DriverUtils<a name="EN-US_TOPIC_0000001055518036"></a>

## **Overview**<a name="section2123919063084825"></a>

Defines common macros and interfaces of the driver module. 

This module provides interfaces such as log printing, doubly linked list operations, and work queues.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1072867833084825"></a>

## Files<a name="files"></a>

<a name="table780061921084825"></a>
<table><thead align="left"><tr id="row65919580084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1519289556084825"><a name="p1519289556084825"></a><a name="p1519289556084825"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p650357773084825"><a name="p650357773084825"></a><a name="p650357773084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1962991451084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1868421064084825"><a name="p1868421064084825"></a><a name="p1868421064084825"></a><a href="hdf_base-h.md">hdf_base.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p145656584084825"><a name="p145656584084825"></a><a name="p145656584084825"></a>Declares driver common types, including the enumerated values returned by the function and the macro for obtaining the array size. </p>
</td>
</tr>
<tr id="row872440764084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651911877084825"><a name="p651911877084825"></a><a name="p651911877084825"></a><a href="hdf_dlist-h.md">hdf_dlist.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1328038997084825"><a name="p1328038997084825"></a><a name="p1328038997084825"></a>Declares doubly linked list structures and interfaces. </p>
</td>
</tr>
<tr id="row751152391084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1434610738084825"><a name="p1434610738084825"></a><a name="p1434610738084825"></a><a href="hdf_log-h.md">hdf_log.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1512139379084825"><a name="p1512139379084825"></a><a name="p1512139379084825"></a>Declares log printing functions of the driver module. This module provides functions for printing logs at the verbose, debug, information, warning, and error levels. </p>
</td>
</tr>
<tr id="row977274514084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1424566993084825"><a name="p1424566993084825"></a><a name="p1424566993084825"></a><a href="hdf_workqueue-h.md">hdf_workqueue.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p541663861084825"><a name="p541663861084825"></a><a name="p541663861084825"></a>Declares work queue structures and interfaces. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1075516551084825"></a>
<table><thead align="left"><tr id="row225811947084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2135231296084825"><a name="p2135231296084825"></a><a name="p2135231296084825"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1706017655084825"><a name="p1706017655084825"></a><a name="p1706017655084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1226698881084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1585812706084825"><a name="p1585812706084825"></a><a name="p1585812706084825"></a><a href="dlisthead.md">DListHead</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1351194284084825"><a name="p1351194284084825"></a><a name="p1351194284084825"></a>Describes a doubly linked list. </p>
</td>
</tr>
<tr id="row229076574084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2047965275084825"><a name="p2047965275084825"></a><a name="p2047965275084825"></a><a href="hdfwork.md">HdfWork</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p89648867084825"><a name="p89648867084825"></a><a name="p89648867084825"></a>Describes a work item and a delayed work item. This structure defines the work and delayed work items, and then calls the initialization function <a href="driverutils.md#gad171adc8eda320fd01049a2b87ea62fb">HdfWorkInit</a> or <a href="driverutils.md#ga55bf669dc6740c65e4d45a4f641db2f1">HdfDelayedWorkInit</a> to perform initialization. The <strong id="b1576598809084825"><a name="b1576598809084825"></a><a name="b1576598809084825"></a><a href="driverutils.md#ga82cc68d656aa17317634b07d49dae160">HdfAddWork()</a></strong> function is to add a work item to a work queue immediately, and the <strong id="b651526638084825"><a name="b651526638084825"></a><a name="b651526638084825"></a><a href="driverutils.md#gaef781ccc1579db3070745088da47b2c5">HdfAddDelayedWork()</a></strong> function is to add a work item to a work queue after the configured delayed time. </p>
</td>
</tr>
<tr id="row728017963084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p740730039084825"><a name="p740730039084825"></a><a name="p740730039084825"></a><a href="hdfworkqueue.md">HdfWorkQueue</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p592727068084825"><a name="p592727068084825"></a><a name="p592727068084825"></a>Describes a work queue. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1926518244084825"></a>
<table><thead align="left"><tr id="row151459126084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1664133268084825"><a name="p1664133268084825"></a><a name="p1664133268084825"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1470399967084825"><a name="p1470399967084825"></a><a name="p1470399967084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2025295376084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p233019185084825"><a name="p233019185084825"></a><a name="p233019185084825"></a><em id="ga4dc11d1abeb6b0d2a40e20a553f491f4"><a name="ga4dc11d1abeb6b0d2a40e20a553f491f4"></a><a name="ga4dc11d1abeb6b0d2a40e20a553f491f4"></a></em>HDF_WAIT_FOREVER    0xFFFFFFFF</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1008667351084825"><a name="p1008667351084825"></a><a name="p1008667351084825"></a>Indicates that the function keeps waiting to obtain a semaphore or mutex. </p>
</td>
</tr>
<tr id="row1721740562084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p756749079084825"><a name="p756749079084825"></a><a name="p756749079084825"></a><em id="ga5255c6a1e2a87df682c1c0ed36fc1b2f"><a name="ga5255c6a1e2a87df682c1c0ed36fc1b2f"></a><a name="ga5255c6a1e2a87df682c1c0ed36fc1b2f"></a></em>HDF_ARRAY_SIZE (a)   (sizeof(a) / sizeof((a)[0]))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1086409202084825"><a name="p1086409202084825"></a><a name="p1086409202084825"></a>Defines the array size. </p>
</td>
</tr>
<tr id="row1030854569084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2033450525084825"><a name="p2033450525084825"></a><a name="p2033450525084825"></a><em id="ga8f2520dfc5a6cd0bac044845318b020c"><a name="ga8f2520dfc5a6cd0bac044845318b020c"></a><a name="ga8f2520dfc5a6cd0bac044845318b020c"></a></em>HDF_KILO_UNIT    1000</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p23978054084825"><a name="p23978054084825"></a><a name="p23978054084825"></a>Defines a time conversion unit, for example, the unit for converting from second to millisecond. </p>
</td>
</tr>
<tr id="row1477106683084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p271121412084825"><a name="p271121412084825"></a><a name="p271121412084825"></a><a href="driverutils.md#ga818b9cca761fe7bc18e4e417da772976">CONTAINER_OF</a>(ptr, type, member)   (type *)((char *)(ptr) - (char *)&amp;((type *)0)-&gt;member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p203348715084825"><a name="p203348715084825"></a><a name="p203348715084825"></a>Obtains the address of a structure variable from its member address. </p>
</td>
</tr>
<tr id="row835884812084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p609049311084825"><a name="p609049311084825"></a><a name="p609049311084825"></a><a href="driverutils.md#ga203de9c01fefc8bbbae746685794cfcc">DLIST_FIRST_ENTRY</a>(ptr, type, member)   <a href="driverutils.md#ga818b9cca761fe7bc18e4e417da772976">CONTAINER_OF</a>((ptr)-&gt;next, type, member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p697466841084825"><a name="p697466841084825"></a><a name="p697466841084825"></a>Obtains the first node of a doubly linked list. </p>
</td>
</tr>
<tr id="row449177386084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p374438371084825"><a name="p374438371084825"></a><a name="p374438371084825"></a><a href="driverutils.md#ga25ac08cc864bd59050f7e2ca77df1f23">DLIST_LAST_ENTRY</a>(ptr, type, member)   <a href="driverutils.md#ga818b9cca761fe7bc18e4e417da772976">CONTAINER_OF</a>((ptr)-&gt;prev, type, member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1846467564084825"><a name="p1846467564084825"></a><a name="p1846467564084825"></a>Obtains the last node of a doubly linked list. </p>
</td>
</tr>
<tr id="row1548055229084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p748238588084825"><a name="p748238588084825"></a><a name="p748238588084825"></a><a href="driverutils.md#ga2b53b2bcf35b8cfb32e429cacbcc0a8d">DLIST_FOR_EACH_ENTRY</a>(pos, head, type, member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p993262969084825"><a name="p993262969084825"></a><a name="p993262969084825"></a>Traverses all nodes in a doubly linked list. </p>
</td>
</tr>
<tr id="row855772017084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p365860195084825"><a name="p365860195084825"></a><a name="p365860195084825"></a><a href="driverutils.md#ga8e6f49c1fed85c031f29e8acce377ea0">DLIST_FOR_EACH_ENTRY_SAFE</a>(pos, tmp, head, type, member)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p132926340084825"><a name="p132926340084825"></a><a name="p132926340084825"></a>Traverses all nodes in a doubly linked list. This function is used to delete the nodes pointed to by <strong id="b649840505084825"><a name="b649840505084825"></a><a name="b649840505084825"></a>pos</strong> during traversal. </p>
</td>
</tr>
<tr id="row1359639984084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p443979189084825"><a name="p443979189084825"></a><a name="p443979189084825"></a><a href="driverutils.md#ga7e862bda9f0b95d1628f6f62598f1f42">LOG_TAG_MARK_EXTEND</a>(HDF_TAG)   #HDF_TAG</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
<tr id="row882388768084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1404922253084825"><a name="p1404922253084825"></a><a name="p1404922253084825"></a><a href="driverutils.md#ga4abebfca1aaeb8125f85800425caf304">HDF_LOGV</a>(fmt, arg...)   <a href="io.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:V/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2092386574084825"><a name="p2092386574084825"></a><a name="p2092386574084825"></a>Prints logs at the verbose level. </p>
</td>
</tr>
<tr id="row1674900513084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1438698925084825"><a name="p1438698925084825"></a><a name="p1438698925084825"></a><a href="driverutils.md#gaa0411582f697619cdb045ae61ac42539">HDF_LOGD</a>(fmt, arg...)   <a href="io.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:D/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p173539554084825"><a name="p173539554084825"></a><a name="p173539554084825"></a>Prints logs at the debug level. </p>
</td>
</tr>
<tr id="row1580537271084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p188594163084825"><a name="p188594163084825"></a><a name="p188594163084825"></a><a href="driverutils.md#ga369d56841d17e6908fc6885fcb814b80">HDF_LOGI</a>(fmt, arg...)   <a href="io.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:I/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2074744697084825"><a name="p2074744697084825"></a><a name="p2074744697084825"></a>Prints logs at the information level. </p>
</td>
</tr>
<tr id="row669109087084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2005868737084825"><a name="p2005868737084825"></a><a name="p2005868737084825"></a><a href="driverutils.md#ga72f232dade88b85aff2d8c0e42b82df0">HDF_LOGW</a>(fmt, arg...)   <a href="io.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:W/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1022524472084825"><a name="p1022524472084825"></a><a name="p1022524472084825"></a>Prints logs at the warning level. </p>
</td>
</tr>
<tr id="row289727072084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p987616676084825"><a name="p987616676084825"></a><a name="p987616676084825"></a><a href="driverutils.md#gaacd0eb778948960a7f97af155287ce8c">HDF_LOGE</a>(fmt, arg...)   <a href="io.md#ga98631211a4a8aee62f572375d5b637be">printf</a>("[HDF:E/" LOG_TAG "]" fmt "\r\n", ##arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1732831628084825"><a name="p1732831628084825"></a><a name="p1732831628084825"></a>Prints logs at the error level. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table2004608104084825"></a>
<table><thead align="left"><tr id="row1083684571084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p924256894084825"><a name="p924256894084825"></a><a name="p924256894084825"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p761414225084825"><a name="p761414225084825"></a><a name="p761414225084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1037446030084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872119220084825"><a name="p1872119220084825"></a><a name="p1872119220084825"></a><a href="driverutils.md#ga30665d61b03fae4a2ebc778c3d775ce5">HdfWorkFunc</a>) (void *)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1518757312084825"><a name="p1518757312084825"></a><a name="p1518757312084825"></a>typedef void(* </p>
<p id="p44641876084825"><a name="p44641876084825"></a><a name="p44641876084825"></a>Describes a work execution function type. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table160707455084825"></a>
<table><thead align="left"><tr id="row1894050203084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p891354799084825"><a name="p891354799084825"></a><a name="p891354799084825"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1810975285084825"><a name="p1810975285084825"></a><a name="p1810975285084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1924758086084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2057573855084825"><a name="p2057573855084825"></a><a name="p2057573855084825"></a><a href="driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67">HDF_STATUS</a> {   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a66cefc3d8cb74728358899034d8d141f">HDF_SUCCESS</a> = 0, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a454a8a08dd1a4b166b2aff6af90266d0">HDF_FAILURE</a> = -1, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67ac6e0c4313436d7222b7dc9bf21e092ed">HDF_ERR_NOT_SUPPORT</a> = -2, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a87e9e0ca4600bc8967556e668abf6718">HDF_ERR_INVALID_PARAM</a> = -3,   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a14a42b17e53bbd65b4f15d56df41ae70">HDF_ERR_INVALID_OBJECT</a> = -4, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a0ad904f070baaf23e6a4bf8fbdf928f5">HDF_ERR_MALLOC_FAIL</a> = -6, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a0c698c789d0dec0b054d5f1cf10003d7">HDF_ERR_TIMEOUT</a> = -7, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a77fd634e04dc131c2ca0435372c1f13b">HDF_ERR_THREAD_CREATE_FAIL</a> = -10,   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a44e8f39984cb2b4f7790b2ceab8b7670">HDF_ERR_QUEUE_FULL</a> = -15, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a9c98586b0a30928afdd3f8fee5083e9b">HDF_ERR_DEVICE_BUSY</a> = -16, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a79c1aa5fb70b16b6b62b9f92e06b76d8">HDF_ERR_IO</a> = -17, <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a140804bae8a12c1ae2f3bbb07dd942d9">HDF_ERR_BAD_FD</a> = -18,   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a0d6ae6ce941fe02f540dc38897e9aac6">HDF_BSP_ERR_OP</a> = HDF_BSP_ERR_NUM(-1), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a6005454a71463ece52e0aa518f5032c2">HDF_ERR_BSP_PLT_API_ERR</a> = HDF_BSP_ERR_NUM(-2), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a520a898768b87a190ead33e693196946">HDF_PAL_ERR_DEV_CREATE</a> = HDF_BSP_ERR_NUM(-3), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a0cd3b31917d5ebb591bcbc7bd1099d55">HDF_PAL_ERR_INNER</a> = HDF_BSP_ERR_NUM(-4),   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67ac7475bfa5f540b4324e551f5e7d7b2bd">HDF_DEV_ERR_NO_MEMORY</a> = HDF_DEV_ERR_NUM(-1), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67abde6ef565b453d3fc7734338db4db62d">HDF_DEV_ERR_NO_DEVICE</a> = HDF_DEV_ERR_NUM(-2), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a7d31e3b26c26010b0b1cf64596982005">HDF_DEV_ERR_NO_DEVICE_SERVICE</a> = HDF_DEV_ERR_NUM(-3), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a50fbd0d6fba63406ee384eb0c2ddaab5">HDF_DEV_ERR_DEV_INIT_FAIL</a> = HDF_DEV_ERR_NUM(-4),   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a318d4f725c1e85fb8c55acac7ed80112">HDF_DEV_ERR_PUBLISH_FAIL</a> = HDF_DEV_ERR_NUM(-5), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a676ff9d5ba402e93f44465d309cf4f94">HDF_DEV_ERR_ATTACHDEV_FAIL</a> = HDF_DEV_ERR_NUM(-6), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67a4cfc60685fac5ac921651fdaea845c1a">HDF_DEV_ERR_NODATA</a> = HDF_DEV_ERR_NUM(-7), <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67adbecc6285acfc5030abff4612b9cf916">HDF_DEV_ERR_NORANGE</a> = HDF_DEV_ERR_NUM(-8),   <a href="driverutils.md#gga7e01536ecbe9b17563dd3fe256202a67aace3a9148b526f670290e7829f3dd9df">HDF_DEV_ERR_OP</a> = HDF_DEV_ERR_NUM(-10) }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p194856480084825"><a name="p194856480084825"></a><a name="p194856480084825"></a>Enumerates HDF return value types. </p>
</td>
</tr>
<tr id="row290065763084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p901472891084825"><a name="p901472891084825"></a><a name="p901472891084825"></a>{ <a href="driverutils.md#ggaabfcbcb5ac86a1edac4035264bc7d2b8a75df1ca644f77f78bf3539e356f2e446">HDF_WORK_BUSY_PENDING</a> = 1 &lt;&lt; 0, <a href="driverutils.md#ggaabfcbcb5ac86a1edac4035264bc7d2b8a56532f81e262cca4680e754627d6dc44">HDF_WORK_BUSY_RUNNING</a> = 1 &lt;&lt; 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p226172976084825"><a name="p226172976084825"></a><a name="p226172976084825"></a>Enumerates statuses of a work item or a delayed work item. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1214511589084825"></a>
<table><thead align="left"><tr id="row1576029347084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1361534987084825"><a name="p1361534987084825"></a><a name="p1361534987084825"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p109585994084825"><a name="p109585994084825"></a><a name="p109585994084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1699295630084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1735984284084825"><a name="p1735984284084825"></a><a name="p1735984284084825"></a><a href="driverutils.md#ga0a86a18ad591f485663834799dd38dea">DListHeadInit</a> (struct <a href="dlisthead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931620206084825"><a name="p931620206084825"></a><a name="p931620206084825"></a>static void </p>
<p id="p1667500674084825"><a name="p1667500674084825"></a><a name="p1667500674084825"></a>Initializes a doubly linked list. </p>
</td>
</tr>
<tr id="row469504230084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p158282600084825"><a name="p158282600084825"></a><a name="p158282600084825"></a><a href="driverutils.md#ga9b4053294ad63f0bdacb4841a14ba208">DListIsEmpty</a> (const struct <a href="dlisthead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2008239460084825"><a name="p2008239460084825"></a><a name="p2008239460084825"></a>static bool </p>
<p id="p1250103516084825"><a name="p1250103516084825"></a><a name="p1250103516084825"></a>Checks whether a doubly linked list is empty. </p>
</td>
</tr>
<tr id="row1638135923084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245708523084825"><a name="p1245708523084825"></a><a name="p1245708523084825"></a><a href="driverutils.md#ga42d23fa1f55097bae91664c5e4a78e1e">DListRemove</a> (struct <a href="dlisthead.md">DListHead</a> *<a href="entry.md">entry</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1666900602084825"><a name="p1666900602084825"></a><a name="p1666900602084825"></a>static void </p>
<p id="p263224683084825"><a name="p263224683084825"></a><a name="p263224683084825"></a>Removes a node from a doubly linked list. </p>
</td>
</tr>
<tr id="row1348011291084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p570476466084825"><a name="p570476466084825"></a><a name="p570476466084825"></a><a href="driverutils.md#ga60e796c868630dd403ef4fdcc60c12e8">DListInsertHead</a> (struct <a href="dlisthead.md">DListHead</a> *<a href="entry.md">entry</a>, struct <a href="dlisthead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137863293084825"><a name="p2137863293084825"></a><a name="p2137863293084825"></a>static void </p>
<p id="p1334434487084825"><a name="p1334434487084825"></a><a name="p1334434487084825"></a>Inserts a node from the head of a doubly linked list. </p>
</td>
</tr>
<tr id="row1312205659084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1185063848084825"><a name="p1185063848084825"></a><a name="p1185063848084825"></a><a href="driverutils.md#gaa1d386162f8f6401fe8ac6d70d237517">DListInsertTail</a> (struct <a href="dlisthead.md">DListHead</a> *<a href="entry.md">entry</a>, struct <a href="dlisthead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508783367084825"><a name="p508783367084825"></a><a name="p508783367084825"></a>static void </p>
<p id="p1753124394084825"><a name="p1753124394084825"></a><a name="p1753124394084825"></a>Inserts a node from the tail of a doubly linked list. </p>
</td>
</tr>
<tr id="row64980078084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1058157050084825"><a name="p1058157050084825"></a><a name="p1058157050084825"></a><a href="driverutils.md#gac4acad10a7c49cc4b2d773aedbfa1e11">DListMerge</a> (struct <a href="dlisthead.md">DListHead</a> *list, struct <a href="dlisthead.md">DListHead</a> *head)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p565760990084825"><a name="p565760990084825"></a><a name="p565760990084825"></a>static void </p>
<p id="p119520152084825"><a name="p119520152084825"></a><a name="p119520152084825"></a>Merges two linked lists by adding the list specified by <strong id="b39529846084825"><a name="b39529846084825"></a><a name="b39529846084825"></a>list</strong> to the head of the list specified by <strong id="b1124474177084825"><a name="b1124474177084825"></a><a name="b1124474177084825"></a>head</strong> and initializes the merged list. </p>
</td>
</tr>
<tr id="row799656796084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p703135577084825"><a name="p703135577084825"></a><a name="p703135577084825"></a><a href="driverutils.md#gad7afae1dc691818c513094c873decabd">HdfWorkQueueInit</a> (<a href="hdfworkqueue.md">HdfWorkQueue</a> *queue, char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1903307530084825"><a name="p1903307530084825"></a><a name="p1903307530084825"></a>int32_t </p>
<p id="p615335582084825"><a name="p615335582084825"></a><a name="p615335582084825"></a>Initializes a work queue. </p>
</td>
</tr>
<tr id="row1294120684084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205804911084825"><a name="p205804911084825"></a><a name="p205804911084825"></a><a href="driverutils.md#gad171adc8eda320fd01049a2b87ea62fb">HdfWorkInit</a> (<a href="hdfwork.md">HdfWork</a> *work, <a href="driverutils.md#ga30665d61b03fae4a2ebc778c3d775ce5">HdfWorkFunc</a> func, void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p673134483084825"><a name="p673134483084825"></a><a name="p673134483084825"></a>int32_t </p>
<p id="p1653378296084825"><a name="p1653378296084825"></a><a name="p1653378296084825"></a>Initializes a work item. </p>
</td>
</tr>
<tr id="row1727763829084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1976927200084825"><a name="p1976927200084825"></a><a name="p1976927200084825"></a><a href="driverutils.md#ga55bf669dc6740c65e4d45a4f641db2f1">HdfDelayedWorkInit</a> (<a href="hdfwork.md">HdfWork</a> *work, <a href="driverutils.md#ga30665d61b03fae4a2ebc778c3d775ce5">HdfWorkFunc</a> func, void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p216188448084825"><a name="p216188448084825"></a><a name="p216188448084825"></a>int32_t </p>
<p id="p805693370084825"><a name="p805693370084825"></a><a name="p805693370084825"></a>Initializes a delayed work item. </p>
</td>
</tr>
<tr id="row2105953793084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1174292924084825"><a name="p1174292924084825"></a><a name="p1174292924084825"></a><a href="driverutils.md#gae6166caaf1b114e17834c50414b2d52e">HdfWorkDestroy</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p623805540084825"><a name="p623805540084825"></a><a name="p623805540084825"></a>void </p>
<p id="p1582836520084825"><a name="p1582836520084825"></a><a name="p1582836520084825"></a>Destroys a work item. </p>
</td>
</tr>
<tr id="row1805498412084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183286320084825"><a name="p1183286320084825"></a><a name="p1183286320084825"></a><a href="driverutils.md#ga04ec328639aefd71683175e4c214fb80">HdfWorkQueueDestroy</a> (<a href="hdfworkqueue.md">HdfWorkQueue</a> *queue)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1393509144084825"><a name="p1393509144084825"></a><a name="p1393509144084825"></a>void </p>
<p id="p1127584774084825"><a name="p1127584774084825"></a><a name="p1127584774084825"></a>Destroys a work queue. </p>
</td>
</tr>
<tr id="row875856007084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1803452615084825"><a name="p1803452615084825"></a><a name="p1803452615084825"></a><a href="driverutils.md#gaaaced5c0365d1a1232167b738f08b5ce">HdfDelayedWorkDestroy</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038639393084825"><a name="p1038639393084825"></a><a name="p1038639393084825"></a>void </p>
<p id="p1762111882084825"><a name="p1762111882084825"></a><a name="p1762111882084825"></a>Destroys a delayed work item. </p>
</td>
</tr>
<tr id="row223843028084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892101585084825"><a name="p1892101585084825"></a><a name="p1892101585084825"></a><a href="driverutils.md#ga82cc68d656aa17317634b07d49dae160">HdfAddWork</a> (<a href="hdfworkqueue.md">HdfWorkQueue</a> *queue, <a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1907562962084825"><a name="p1907562962084825"></a><a name="p1907562962084825"></a>bool </p>
<p id="p329898379084825"><a name="p329898379084825"></a><a name="p329898379084825"></a>Adds a work item to a work queue. </p>
</td>
</tr>
<tr id="row557148595084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p811956497084825"><a name="p811956497084825"></a><a name="p811956497084825"></a><a href="driverutils.md#gaef781ccc1579db3070745088da47b2c5">HdfAddDelayedWork</a> (<a href="hdfworkqueue.md">HdfWorkQueue</a> *queue, <a href="hdfwork.md">HdfWork</a> *work, unsigned long ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1309154046084825"><a name="p1309154046084825"></a><a name="p1309154046084825"></a>bool </p>
<p id="p1580816793084825"><a name="p1580816793084825"></a><a name="p1580816793084825"></a>Adds a delayed work item to a work queue. </p>
</td>
</tr>
<tr id="row1327021427084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892958700084825"><a name="p1892958700084825"></a><a name="p1892958700084825"></a><a href="driverutils.md#ga37595ed36b8ce7be84c914aebfd99d00">HdfWorkBusy</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p828075169084825"><a name="p828075169084825"></a><a name="p828075169084825"></a>unsigned int </p>
<p id="p2101508500084825"><a name="p2101508500084825"></a><a name="p2101508500084825"></a>Obtains the status of a work item or delayed work item. </p>
</td>
</tr>
<tr id="row1388456989084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000170789084825"><a name="p1000170789084825"></a><a name="p1000170789084825"></a><a href="driverutils.md#gaab300487bdb9f3496bb823c657275dd3">HdfCancelWorkSync</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p540313679084825"><a name="p540313679084825"></a><a name="p540313679084825"></a>bool </p>
<p id="p1597208246084825"><a name="p1597208246084825"></a><a name="p1597208246084825"></a>Cancels a work item. This function waits until the work item is complete. </p>
</td>
</tr>
<tr id="row832592343084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1868763323084825"><a name="p1868763323084825"></a><a name="p1868763323084825"></a><a href="driverutils.md#gad53e46938809200db3caafdc85decc5a">HdfCancelDelayedWorkSync</a> (<a href="hdfwork.md">HdfWork</a> *work)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p147384353084825"><a name="p147384353084825"></a><a name="p147384353084825"></a>bool </p>
<p id="p1686459625084825"><a name="p1686459625084825"></a><a name="p1686459625084825"></a>Cancels a delayed work item. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section412027031084825"></a>

## **Macro Definition Documentation**<a name="section459737105084825"></a>

## CONTAINER\_OF<a name="ga818b9cca761fe7bc18e4e417da772976"></a>

```
#define CONTAINER_OF( ptr,  type,  member )   (type *)((char *)(ptr) - (char *)&((type *)0)->member)
```

 **Description:**

Obtains the address of a structure variable from its member address. 

**Parameters:**

<a name="table607007437084825"></a>
<table><thead align="left"><tr id="row1509841947084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2137152436084825"><a name="p2137152436084825"></a><a name="p2137152436084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1418817109084825"><a name="p1418817109084825"></a><a name="p1418817109084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1046479310084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure member address. </td>
</tr>
<tr id="row1465786430084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure type. </td>
</tr>
<tr id="row1793581279084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">member</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure member. </td>
</tr>
</tbody>
</table>

## DLIST\_FIRST\_ENTRY<a name="ga203de9c01fefc8bbbae746685794cfcc"></a>

```
#define DLIST_FIRST_ENTRY( ptr,  type,  member )   [CONTAINER_OF](driverutils.md#ga818b9cca761fe7bc18e4e417da772976)((ptr)->next, type, member)
```

 **Description:**

Obtains the first node of a doubly linked list. 

**Parameters:**

<a name="table856497049084825"></a>
<table><thead align="left"><tr id="row723310217084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p635817458084825"><a name="p635817458084825"></a><a name="p635817458084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1492452903084825"><a name="p1492452903084825"></a><a name="p1492452903084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row925901234084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure member address. </td>
</tr>
<tr id="row441620693084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure type. </td>
</tr>
<tr id="row2043768913084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">member</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure member. </td>
</tr>
</tbody>
</table>

## DLIST\_FOR\_EACH\_ENTRY<a name="ga2b53b2bcf35b8cfb32e429cacbcc0a8d"></a>

```
#define DLIST_FOR_EACH_ENTRY( pos,  head,  type,  member )
```

```
Values: for ((pos) = [CONTAINER_OF](driverutils.md#ga818b9cca761fe7bc18e4e417da772976)((head)->next, type, member); \

 &(pos)->member != (head); \

 (pos) = [CONTAINER_OF](driverutils.md#ga818b9cca761fe7bc18e4e417da772976)((pos)->member.next, type, member))


```

 **Description:**

Traverses all nodes in a doubly linked list. 

**Parameters:**

<a name="table535249008084825"></a>
<table><thead align="left"><tr id="row102514329084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1795797075084825"><a name="p1795797075084825"></a><a name="p1795797075084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1130650080084825"><a name="p1130650080084825"></a><a name="p1130650080084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2047238167084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pos</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the structure variable. </td>
</tr>
<tr id="row204516806084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">head</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the linked list head. </td>
</tr>
<tr id="row2116523264084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure type. </td>
</tr>
<tr id="row422943384084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">member</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the member type of the structure. </td>
</tr>
</tbody>
</table>

## DLIST\_FOR\_EACH\_ENTRY\_SAFE<a name="ga8e6f49c1fed85c031f29e8acce377ea0"></a>

```
#define DLIST_FOR_EACH_ENTRY_SAFE( pos,  tmp,  head,  type,  member )
```

```
Values: for ((pos) = [CONTAINER_OF](driverutils.md#ga818b9cca761fe7bc18e4e417da772976)((head)->next, type, member), \

 (tmp) = [CONTAINER_OF](driverutils.md#ga818b9cca761fe7bc18e4e417da772976)((pos)->member.next, type, member); \

 &(pos)->member != (head); \

 (pos) = (tmp), (tmp) = [CONTAINER_OF](driverutils.md#ga818b9cca761fe7bc18e4e417da772976)((pos)->member.next, type, member))


```

 **Description:**

Traverses all nodes in a doubly linked list. This function is used to delete the nodes pointed to by  **pos**  during traversal. 

**Parameters:**

<a name="table625076230084825"></a>
<table><thead align="left"><tr id="row126762239084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p213196532084825"><a name="p213196532084825"></a><a name="p213196532084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1062100159084825"><a name="p1062100159084825"></a><a name="p1062100159084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row275405350084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">pos</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the structure variable. </td>
</tr>
<tr id="row2051153233084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tmp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the structure variable, pointing to the next node of <strong id="b202465651084825"><a name="b202465651084825"></a><a name="b202465651084825"></a>pos</strong>. </td>
</tr>
<tr id="row168673444084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">head</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the linked list head. </td>
</tr>
<tr id="row435607105084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure type. </td>
</tr>
<tr id="row1565789737084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">member</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the member type of the structure. </td>
</tr>
</tbody>
</table>

## DLIST\_LAST\_ENTRY<a name="ga25ac08cc864bd59050f7e2ca77df1f23"></a>

```
#define DLIST_LAST_ENTRY( ptr,  type,  member )   [CONTAINER_OF](driverutils.md#ga818b9cca761fe7bc18e4e417da772976)((ptr)->prev, type, member)
```

 **Description:**

Obtains the last node of a doubly linked list. 

**Parameters:**

<a name="table1827477525084825"></a>
<table><thead align="left"><tr id="row1048374537084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p643063297084825"><a name="p643063297084825"></a><a name="p643063297084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p530930722084825"><a name="p530930722084825"></a><a name="p530930722084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row797782433084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ptr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure member address. </td>
</tr>
<tr id="row1396843152084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure type. </td>
</tr>
<tr id="row2004236491084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">member</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the structure member. </td>
</tr>
</tbody>
</table>

## HDF\_LOGD<a name="gaa0411582f697619cdb045ae61ac42539"></a>

```
#define HDF_LOGD( fmt,  arg... )   [printf](io.md#ga98631211a4a8aee62f572375d5b637be)("[HDF:D/" LOG_TAG "]" fmt "\r\n", ##arg)
```

 **Description:**

Prints logs at the debug level. 

To use this function, you must define  **HDF\_LOG\_TAG**, for example, \#define HDF\_LOG\_TAG evt.

## HDF\_LOGE<a name="gaacd0eb778948960a7f97af155287ce8c"></a>

```
#define HDF_LOGE( fmt,  arg... )   [printf](io.md#ga98631211a4a8aee62f572375d5b637be)("[HDF:E/" LOG_TAG "]" fmt "\r\n", ##arg)
```

 **Description:**

Prints logs at the error level. 

To use this function, you must define  **HDF\_LOG\_TAG**, for example, \#define HDF\_LOG\_TAG evt.

## HDF\_LOGI<a name="ga369d56841d17e6908fc6885fcb814b80"></a>

```
#define HDF_LOGI( fmt,  arg... )   [printf](io.md#ga98631211a4a8aee62f572375d5b637be)("[HDF:I/" LOG_TAG "]" fmt "\r\n", ##arg)
```

 **Description:**

Prints logs at the information level. 

To use this function, you must define  **HDF\_LOG\_TAG**, for example, \#define HDF\_LOG\_TAG evt.

## HDF\_LOGV<a name="ga4abebfca1aaeb8125f85800425caf304"></a>

```
#define HDF_LOGV( fmt,  arg... )   [printf](io.md#ga98631211a4a8aee62f572375d5b637be)("[HDF:V/" LOG_TAG "]" fmt "\r\n", ##arg)
```

 **Description:**

Prints logs at the verbose level. 

To use this function, you must define  **HDF\_LOG\_TAG**, for example, \#define HDF\_LOG\_TAG evt.

## HDF\_LOGW<a name="ga72f232dade88b85aff2d8c0e42b82df0"></a>

```
#define HDF_LOGW( fmt,  arg... )   [printf](io.md#ga98631211a4a8aee62f572375d5b637be)("[HDF:W/" LOG_TAG "]" fmt "\r\n", ##arg)
```

 **Description:**

Prints logs at the warning level. 

To use this function, you must define  **HDF\_LOG\_TAG**, for example, \#define HDF\_LOG\_TAG evt.

## LOG\_TAG\_MARK\_EXTEND<a name="ga7e862bda9f0b95d1628f6f62598f1f42"></a>

```
#define LOG_TAG_MARK_EXTEND( HDF_TAG)   #HDF_TAG
```

 **Description:**

Add quotation mark 

## **Typedef Documentation**<a name="section1148440589084825"></a>

## HdfWorkFunc<a name="ga30665d61b03fae4a2ebc778c3d775ce5"></a>

```
typedef void(* HdfWorkFunc) (void *)
```

 **Description:**

Describes a work execution function type. 

The thread of the work queue executes this function after the work item is added to the work queue. 

## **Enumeration Type Documentation**<a name="section1109549527084825"></a>

## anonymous enum<a name="gaabfcbcb5ac86a1edac4035264bc7d2b8"></a>

```
anonymous enum
```

 **Description:**

Enumerates statuses of a work item or a delayed work item. 

<a name="table339655220084825"></a>
<table><thead align="left"><tr id="row327979527084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2079349570084825"><a name="p2079349570084825"></a><a name="p2079349570084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1062069118084825"><a name="p1062069118084825"></a><a name="p1062069118084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1825840659084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaabfcbcb5ac86a1edac4035264bc7d2b8a75df1ca644f77f78bf3539e356f2e446"><a name="ggaabfcbcb5ac86a1edac4035264bc7d2b8a75df1ca644f77f78bf3539e356f2e446"></a><a name="ggaabfcbcb5ac86a1edac4035264bc7d2b8a75df1ca644f77f78bf3539e356f2e446"></a></strong>HDF_WORK_BUSY_PENDING </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p541396207084825"><a name="p541396207084825"></a><a name="p541396207084825"></a>The work item or delayed work item is pending. </p>
 </td>
</tr>
<tr id="row931795601084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaabfcbcb5ac86a1edac4035264bc7d2b8a56532f81e262cca4680e754627d6dc44"><a name="ggaabfcbcb5ac86a1edac4035264bc7d2b8a56532f81e262cca4680e754627d6dc44"></a><a name="ggaabfcbcb5ac86a1edac4035264bc7d2b8a56532f81e262cca4680e754627d6dc44"></a></strong>HDF_WORK_BUSY_RUNNING </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p617972835084825"><a name="p617972835084825"></a><a name="p617972835084825"></a>The work item or delayed work item is running. </p>
 </td>
</tr>
</tbody>
</table>

## HDF\_STATUS<a name="ga7e01536ecbe9b17563dd3fe256202a67"></a>

```
enum [HDF_STATUS](driverutils.md#ga7e01536ecbe9b17563dd3fe256202a67)
```

 **Description:**

Enumerates HDF return value types. 

<a name="table1895520408084825"></a>
<table><thead align="left"><tr id="row1324163945084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p984995674084825"><a name="p984995674084825"></a><a name="p984995674084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p849668538084825"><a name="p849668538084825"></a><a name="p849668538084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row222020496084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a66cefc3d8cb74728358899034d8d141f"><a name="gga7e01536ecbe9b17563dd3fe256202a67a66cefc3d8cb74728358899034d8d141f"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a66cefc3d8cb74728358899034d8d141f"></a></strong>HDF_SUCCESS </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1851722184084825"><a name="p1851722184084825"></a><a name="p1851722184084825"></a>The operation is successful. </p>
 </td>
</tr>
<tr id="row951711222084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a454a8a08dd1a4b166b2aff6af90266d0"><a name="gga7e01536ecbe9b17563dd3fe256202a67a454a8a08dd1a4b166b2aff6af90266d0"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a454a8a08dd1a4b166b2aff6af90266d0"></a></strong>HDF_FAILURE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1754771205084825"><a name="p1754771205084825"></a><a name="p1754771205084825"></a>Failed to invoke the OS underlying function. </p>
 </td>
</tr>
<tr id="row609090847084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67ac6e0c4313436d7222b7dc9bf21e092ed"><a name="gga7e01536ecbe9b17563dd3fe256202a67ac6e0c4313436d7222b7dc9bf21e092ed"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67ac6e0c4313436d7222b7dc9bf21e092ed"></a></strong>HDF_ERR_NOT_SUPPORT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2082323164084825"><a name="p2082323164084825"></a><a name="p2082323164084825"></a>Not supported. </p>
 </td>
</tr>
<tr id="row226980562084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a87e9e0ca4600bc8967556e668abf6718"><a name="gga7e01536ecbe9b17563dd3fe256202a67a87e9e0ca4600bc8967556e668abf6718"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a87e9e0ca4600bc8967556e668abf6718"></a></strong>HDF_ERR_INVALID_PARAM </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703992815084825"><a name="p1703992815084825"></a><a name="p1703992815084825"></a>Invalid parameter. </p>
 </td>
</tr>
<tr id="row702803426084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a14a42b17e53bbd65b4f15d56df41ae70"><a name="gga7e01536ecbe9b17563dd3fe256202a67a14a42b17e53bbd65b4f15d56df41ae70"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a14a42b17e53bbd65b4f15d56df41ae70"></a></strong>HDF_ERR_INVALID_OBJECT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1820292642084825"><a name="p1820292642084825"></a><a name="p1820292642084825"></a>Invalid object. </p>
 </td>
</tr>
<tr id="row426068453084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a0ad904f070baaf23e6a4bf8fbdf928f5"><a name="gga7e01536ecbe9b17563dd3fe256202a67a0ad904f070baaf23e6a4bf8fbdf928f5"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a0ad904f070baaf23e6a4bf8fbdf928f5"></a></strong>HDF_ERR_MALLOC_FAIL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p817078182084825"><a name="p817078182084825"></a><a name="p817078182084825"></a>Memory allocation fails. </p>
 </td>
</tr>
<tr id="row1515486724084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a0c698c789d0dec0b054d5f1cf10003d7"><a name="gga7e01536ecbe9b17563dd3fe256202a67a0c698c789d0dec0b054d5f1cf10003d7"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a0c698c789d0dec0b054d5f1cf10003d7"></a></strong>HDF_ERR_TIMEOUT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1040118169084825"><a name="p1040118169084825"></a><a name="p1040118169084825"></a>Timeout occurs. </p>
 </td>
</tr>
<tr id="row1055487925084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a77fd634e04dc131c2ca0435372c1f13b"><a name="gga7e01536ecbe9b17563dd3fe256202a67a77fd634e04dc131c2ca0435372c1f13b"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a77fd634e04dc131c2ca0435372c1f13b"></a></strong>HDF_ERR_THREAD_CREATE_FAIL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p48741964084825"><a name="p48741964084825"></a><a name="p48741964084825"></a>Failed to create a thread. </p>
 </td>
</tr>
<tr id="row653594915084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a44e8f39984cb2b4f7790b2ceab8b7670"><a name="gga7e01536ecbe9b17563dd3fe256202a67a44e8f39984cb2b4f7790b2ceab8b7670"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a44e8f39984cb2b4f7790b2ceab8b7670"></a></strong>HDF_ERR_QUEUE_FULL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1879769956084825"><a name="p1879769956084825"></a><a name="p1879769956084825"></a>The queue is full. </p>
 </td>
</tr>
<tr id="row927353858084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a9c98586b0a30928afdd3f8fee5083e9b"><a name="gga7e01536ecbe9b17563dd3fe256202a67a9c98586b0a30928afdd3f8fee5083e9b"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a9c98586b0a30928afdd3f8fee5083e9b"></a></strong>HDF_ERR_DEVICE_BUSY </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1795734018084825"><a name="p1795734018084825"></a><a name="p1795734018084825"></a>The device is busy. </p>
 </td>
</tr>
<tr id="row1426722256084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a79c1aa5fb70b16b6b62b9f92e06b76d8"><a name="gga7e01536ecbe9b17563dd3fe256202a67a79c1aa5fb70b16b6b62b9f92e06b76d8"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a79c1aa5fb70b16b6b62b9f92e06b76d8"></a></strong>HDF_ERR_IO </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1523039273084825"><a name="p1523039273084825"></a><a name="p1523039273084825"></a>I/O error. </p>
 </td>
</tr>
<tr id="row409765482084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a140804bae8a12c1ae2f3bbb07dd942d9"><a name="gga7e01536ecbe9b17563dd3fe256202a67a140804bae8a12c1ae2f3bbb07dd942d9"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a140804bae8a12c1ae2f3bbb07dd942d9"></a></strong>HDF_ERR_BAD_FD </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868857735084825"><a name="p1868857735084825"></a><a name="p1868857735084825"></a>Incorrect file descriptor. </p>
 </td>
</tr>
<tr id="row1158370354084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a0d6ae6ce941fe02f540dc38897e9aac6"><a name="gga7e01536ecbe9b17563dd3fe256202a67a0d6ae6ce941fe02f540dc38897e9aac6"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a0d6ae6ce941fe02f540dc38897e9aac6"></a></strong>HDF_BSP_ERR_OP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1869071525084825"><a name="p1869071525084825"></a><a name="p1869071525084825"></a>Failed to operate a BSP module. </p>
 </td>
</tr>
<tr id="row805332946084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a6005454a71463ece52e0aa518f5032c2"><a name="gga7e01536ecbe9b17563dd3fe256202a67a6005454a71463ece52e0aa518f5032c2"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a6005454a71463ece52e0aa518f5032c2"></a></strong>HDF_ERR_BSP_PLT_API_ERR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554474764084825"><a name="p1554474764084825"></a><a name="p1554474764084825"></a>The platform API of the BSP module is incorrect. </p>
 </td>
</tr>
<tr id="row1345643223084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a520a898768b87a190ead33e693196946"><a name="gga7e01536ecbe9b17563dd3fe256202a67a520a898768b87a190ead33e693196946"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a520a898768b87a190ead33e693196946"></a></strong>HDF_PAL_ERR_DEV_CREATE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67220447084825"><a name="p67220447084825"></a><a name="p67220447084825"></a>Failed to create a BSP module device. </p>
 </td>
</tr>
<tr id="row1829496677084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a0cd3b31917d5ebb591bcbc7bd1099d55"><a name="gga7e01536ecbe9b17563dd3fe256202a67a0cd3b31917d5ebb591bcbc7bd1099d55"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a0cd3b31917d5ebb591bcbc7bd1099d55"></a></strong>HDF_PAL_ERR_INNER </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p496217272084825"><a name="p496217272084825"></a><a name="p496217272084825"></a>Internal error codes of the BSP module. </p>
 </td>
</tr>
<tr id="row706997389084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67ac7475bfa5f540b4324e551f5e7d7b2bd"><a name="gga7e01536ecbe9b17563dd3fe256202a67ac7475bfa5f540b4324e551f5e7d7b2bd"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67ac7475bfa5f540b4324e551f5e7d7b2bd"></a></strong>HDF_DEV_ERR_NO_MEMORY </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1634050088084825"><a name="p1634050088084825"></a><a name="p1634050088084825"></a>Failed to allocate memory to the device module. </p>
 </td>
</tr>
<tr id="row841078896084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67abde6ef565b453d3fc7734338db4db62d"><a name="gga7e01536ecbe9b17563dd3fe256202a67abde6ef565b453d3fc7734338db4db62d"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67abde6ef565b453d3fc7734338db4db62d"></a></strong>HDF_DEV_ERR_NO_DEVICE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p64324569084825"><a name="p64324569084825"></a><a name="p64324569084825"></a>The device module has no device. </p>
 </td>
</tr>
<tr id="row1844707301084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a7d31e3b26c26010b0b1cf64596982005"><a name="gga7e01536ecbe9b17563dd3fe256202a67a7d31e3b26c26010b0b1cf64596982005"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a7d31e3b26c26010b0b1cf64596982005"></a></strong>HDF_DEV_ERR_NO_DEVICE_SERVICE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1155122621084825"><a name="p1155122621084825"></a><a name="p1155122621084825"></a>The device module has no device service. </p>
 </td>
</tr>
<tr id="row128454488084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a50fbd0d6fba63406ee384eb0c2ddaab5"><a name="gga7e01536ecbe9b17563dd3fe256202a67a50fbd0d6fba63406ee384eb0c2ddaab5"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a50fbd0d6fba63406ee384eb0c2ddaab5"></a></strong>HDF_DEV_ERR_DEV_INIT_FAIL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1177776337084825"><a name="p1177776337084825"></a><a name="p1177776337084825"></a>Failed to initialize a device module. </p>
 </td>
</tr>
<tr id="row1649340468084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a318d4f725c1e85fb8c55acac7ed80112"><a name="gga7e01536ecbe9b17563dd3fe256202a67a318d4f725c1e85fb8c55acac7ed80112"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a318d4f725c1e85fb8c55acac7ed80112"></a></strong>HDF_DEV_ERR_PUBLISH_FAIL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1259458664084825"><a name="p1259458664084825"></a><a name="p1259458664084825"></a>The device module failed to release a service. </p>
 </td>
</tr>
<tr id="row1770818222084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a676ff9d5ba402e93f44465d309cf4f94"><a name="gga7e01536ecbe9b17563dd3fe256202a67a676ff9d5ba402e93f44465d309cf4f94"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a676ff9d5ba402e93f44465d309cf4f94"></a></strong>HDF_DEV_ERR_ATTACHDEV_FAIL </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653730782084825"><a name="p1653730782084825"></a><a name="p1653730782084825"></a>Failed to attach a device to a device module. </p>
 </td>
</tr>
<tr id="row45354059084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67a4cfc60685fac5ac921651fdaea845c1a"><a name="gga7e01536ecbe9b17563dd3fe256202a67a4cfc60685fac5ac921651fdaea845c1a"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67a4cfc60685fac5ac921651fdaea845c1a"></a></strong>HDF_DEV_ERR_NODATA </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p176941421084825"><a name="p176941421084825"></a><a name="p176941421084825"></a>Failed to read data from a device module. </p>
 </td>
</tr>
<tr id="row484915338084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67adbecc6285acfc5030abff4612b9cf916"><a name="gga7e01536ecbe9b17563dd3fe256202a67adbecc6285acfc5030abff4612b9cf916"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67adbecc6285acfc5030abff4612b9cf916"></a></strong>HDF_DEV_ERR_NORANGE </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1990814928084825"><a name="p1990814928084825"></a><a name="p1990814928084825"></a>The device module data is out of range. </p>
 </td>
</tr>
<tr id="row1960236694084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7e01536ecbe9b17563dd3fe256202a67aace3a9148b526f670290e7829f3dd9df"><a name="gga7e01536ecbe9b17563dd3fe256202a67aace3a9148b526f670290e7829f3dd9df"></a><a name="gga7e01536ecbe9b17563dd3fe256202a67aace3a9148b526f670290e7829f3dd9df"></a></strong>HDF_DEV_ERR_OP </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027969095084825"><a name="p1027969095084825"></a><a name="p1027969095084825"></a>Failed to operate a device module. </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1815342574084825"></a>

## DListHeadInit\(\)<a name="ga0a86a18ad591f485663834799dd38dea"></a>

```
static void DListHeadInit (struct [DListHead](dlisthead.md) * head)
```

 **Description:**

Initializes a doubly linked list. 

**Parameters:**

<a name="table1369214509084825"></a>
<table><thead align="left"><tr id="row970610759084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1351663602084825"><a name="p1351663602084825"></a><a name="p1351663602084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p212893455084825"><a name="p212893455084825"></a><a name="p212893455084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row698290017084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">head</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the linked list <a href="dlisthead.md">DListHead</a>. The parameter cannot be empty. </td>
</tr>
</tbody>
</table>

## DListInsertHead\(\)<a name="ga60e796c868630dd403ef4fdcc60c12e8"></a>

```
static void DListInsertHead (struct [DListHead](dlisthead.md) * entry, struct [DListHead](dlisthead.md) * head )
```

 **Description:**

Inserts a node from the head of a doubly linked list. 

**Parameters:**

<a name="table1596333233084825"></a>
<table><thead align="left"><tr id="row1206650449084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1049897813084825"><a name="p1049897813084825"></a><a name="p1049897813084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p183944137084825"><a name="p183944137084825"></a><a name="p183944137084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2029815721084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">entry</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the node to insert. For details, see <a href="dlisthead.md">DListHead</a>. The parameter cannot be empty. </td>
</tr>
<tr id="row1305598287084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">head</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the linked list <a href="dlisthead.md">DListHead</a>. The parameter cannot be empty. </td>
</tr>
</tbody>
</table>

## DListInsertTail\(\)<a name="gaa1d386162f8f6401fe8ac6d70d237517"></a>

```
static void DListInsertTail (struct [DListHead](dlisthead.md) * entry, struct [DListHead](dlisthead.md) * head )
```

 **Description:**

Inserts a node from the tail of a doubly linked list. 

**Parameters:**

<a name="table606303139084825"></a>
<table><thead align="left"><tr id="row1832322273084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1172462300084825"><a name="p1172462300084825"></a><a name="p1172462300084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1009081857084825"><a name="p1009081857084825"></a><a name="p1009081857084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row376406857084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">entry</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the node to insert. For details, see <a href="dlisthead.md">DListHead</a>. The parameter cannot be empty. </td>
</tr>
<tr id="row627770872084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">head</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the linked list <a href="dlisthead.md">DListHead</a>. The parameter cannot be empty. </td>
</tr>
</tbody>
</table>

## DListIsEmpty\(\)<a name="ga9b4053294ad63f0bdacb4841a14ba208"></a>

```
static bool DListIsEmpty (const struct [DListHead](dlisthead.md) * head)
```

 **Description:**

Checks whether a doubly linked list is empty. 

**Parameters:**

<a name="table194510099084825"></a>
<table><thead align="left"><tr id="row880085684084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p450609782084825"><a name="p450609782084825"></a><a name="p450609782084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1516991557084825"><a name="p1516991557084825"></a><a name="p1516991557084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1718780609084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">head</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the linked list <a href="dlisthead.md">DListHead</a>. The parameter cannot be empty. </td>
</tr>
</tbody>
</table>

## DListMerge\(\)<a name="gac4acad10a7c49cc4b2d773aedbfa1e11"></a>

```
static void DListMerge (struct [DListHead](dlisthead.md) * list, struct [DListHead](dlisthead.md) * head )
```

 **Description:**

Merges two linked lists by adding the list specified by  **list**  to the head of the list specified by  **head**  and initializes the merged list. 

**Parameters:**

<a name="table578607853084825"></a>
<table><thead align="left"><tr id="row929991700084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p918711066084825"><a name="p918711066084825"></a><a name="p918711066084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p765318388084825"><a name="p765318388084825"></a><a name="p765318388084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row578889798084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">list</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the linked list <a href="dlisthead.md">DListHead</a>. The parameter cannot be empty. </td>
</tr>
<tr id="row539212754084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">head</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the linked list <a href="dlisthead.md">DListHead</a>. The parameter cannot be empty. </td>
</tr>
</tbody>
</table>

## DListRemove\(\)<a name="ga42d23fa1f55097bae91664c5e4a78e1e"></a>

```
static void DListRemove (struct [DListHead](dlisthead.md) * entry)
```

 **Description:**

Removes a node from a doubly linked list. 

**Parameters:**

<a name="table406711629084825"></a>
<table><thead align="left"><tr id="row2016981849084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p670821871084825"><a name="p670821871084825"></a><a name="p670821871084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1661249930084825"><a name="p1661249930084825"></a><a name="p1661249930084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1477044711084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">entry</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the node to remove. For details, see <a href="dlisthead.md">DListHead</a>. The parameter cannot be empty. </td>
</tr>
</tbody>
</table>

## HdfAddDelayedWork\(\)<a name="gaef781ccc1579db3070745088da47b2c5"></a>

```
bool HdfAddDelayedWork ([HdfWorkQueue](hdfworkqueue.md) * queue, [HdfWork](hdfwork.md) * work, unsigned long ms )
```

 **Description:**

Adds a delayed work item to a work queue. 

A delayed work item is added to a work queue after the configured delayed time \(ms\), and the thread of the work queue executes the work function.

**Parameters:**

<a name="table1712827296084825"></a>
<table><thead align="left"><tr id="row647765348084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p903777409084825"><a name="p903777409084825"></a><a name="p903777409084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2137545810084825"><a name="p2137545810084825"></a><a name="p2137545810084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1922205144084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">queue</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work queue <a href="hdfworkqueue.md">HdfWorkQueue</a>. </td>
</tr>
<tr id="row1986180957084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">work</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the delayed work item <a href="hdfwork.md">HdfWork</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise. 



## HdfAddWork\(\)<a name="ga82cc68d656aa17317634b07d49dae160"></a>

```
bool HdfAddWork ([HdfWorkQueue](hdfworkqueue.md) * queue, [HdfWork](hdfwork.md) * work )
```

 **Description:**

Adds a work item to a work queue. 

After a work item is added to a work queue, the thread of the work queue executes the function of the work item.

**Parameters:**

<a name="table1011576647084825"></a>
<table><thead align="left"><tr id="row99937496084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p665443855084825"><a name="p665443855084825"></a><a name="p665443855084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p379228435084825"><a name="p379228435084825"></a><a name="p379228435084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1492801142084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">queue</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work queue <a href="hdfworkqueue.md">HdfWorkQueue</a>. </td>
</tr>
<tr id="row1684946047084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">work</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work item <a href="hdfwork.md">HdfWork</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise. 



## HdfCancelDelayedWorkSync\(\)<a name="gad53e46938809200db3caafdc85decc5a"></a>

```
bool HdfCancelDelayedWorkSync ([HdfWork](hdfwork.md) * work)
```

 **Description:**

Cancels a delayed work item. 

**Parameters:**

<a name="table782510709084825"></a>
<table><thead align="left"><tr id="row1302526069084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1977925123084825"><a name="p1977925123084825"></a><a name="p1977925123084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1122711832084825"><a name="p1122711832084825"></a><a name="p1122711832084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row299658106084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">work</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the delayed work item <a href="hdfwork.md">HdfWork</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise. 



## HdfCancelWorkSync\(\)<a name="gaab300487bdb9f3496bb823c657275dd3"></a>

```
bool HdfCancelWorkSync ([HdfWork](hdfwork.md) * work)
```

 **Description:**

Cancels a work item. This function waits until the work item is complete. 

**Parameters:**

<a name="table678719306084825"></a>
<table><thead align="left"><tr id="row1982056232084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p307166674084825"><a name="p307166674084825"></a><a name="p307166674084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2026783770084825"><a name="p2026783770084825"></a><a name="p2026783770084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1643480565084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">work</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work item <a href="hdfwork.md">HdfWork</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the operation is successful; returns  **false**  otherwise. 



## HdfDelayedWorkDestroy\(\)<a name="gaaaced5c0365d1a1232167b738f08b5ce"></a>

```
void HdfDelayedWorkDestroy ([HdfWork](hdfwork.md) * work)
```

 **Description:**

Destroys a delayed work item. 

**Parameters:**

<a name="table848287468084825"></a>
<table><thead align="left"><tr id="row1208037860084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p861172169084825"><a name="p861172169084825"></a><a name="p861172169084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1350760755084825"><a name="p1350760755084825"></a><a name="p1350760755084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2103780053084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">work</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the delayed work item <a href="hdfwork.md">HdfWork</a>. </td>
</tr>
</tbody>
</table>

## HdfDelayedWorkInit\(\)<a name="ga55bf669dc6740c65e4d45a4f641db2f1"></a>

```
int32_t HdfDelayedWorkInit ([HdfWork](hdfwork.md) * work, [HdfWorkFunc](driverutils.md#ga30665d61b03fae4a2ebc778c3d775ce5) func, void * arg )
```

 **Description:**

Initializes a delayed work item. 

This function uses  **func**  and  **arg**  to initialize a work item. The work item is added to a work queue after the configured delayed time. The thread of the work queue executes this function, and  **arg**  is passed to  **func**.

**Parameters:**

<a name="table579864640084825"></a>
<table><thead align="left"><tr id="row1068006854084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p666259405084825"><a name="p666259405084825"></a><a name="p666259405084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2050719394084825"><a name="p2050719394084825"></a><a name="p2050719394084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1126183797084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">work</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the delayed work item <a href="hdfwork.md">HdfWork</a>. </td>
</tr>
<tr id="row2037983079084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the work execution function. </td>
</tr>
<tr id="row1963373328084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">arg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the argument of the work execution function.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1722305618084825"></a>
<table><thead align="left"><tr id="row1981706527084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1266535144084825"><a name="p1266535144084825"></a><a name="p1266535144084825"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1695908334084825"><a name="p1695908334084825"></a><a name="p1695908334084825"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1568575101084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p97473067084825"><a name="p97473067084825"></a><a name="p97473067084825"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1806223479084825"><a name="p1806223479084825"></a><a name="p1806223479084825"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row1787008210084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p864344975084825"><a name="p864344975084825"></a><a name="p864344975084825"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p291205210084825"><a name="p291205210084825"></a><a name="p291205210084825"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row232852342084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p559685129084825"><a name="p559685129084825"></a><a name="p559685129084825"></a>HDF_ERR_MALLOC_FAIL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p75798484084825"><a name="p75798484084825"></a><a name="p75798484084825"></a>Memory allocation fails. </p>
</td>
</tr>
</tbody>
</table>

## HdfWorkBusy\(\)<a name="ga37595ed36b8ce7be84c914aebfd99d00"></a>

```
unsigned int HdfWorkBusy ([HdfWork](hdfwork.md) * work)
```

 **Description:**

Obtains the status of a work item or delayed work item. 

**Parameters:**

<a name="table832537779084825"></a>
<table><thead align="left"><tr id="row233366320084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2064554711084825"><a name="p2064554711084825"></a><a name="p2064554711084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1825531316084825"><a name="p1825531316084825"></a><a name="p1825531316084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1978914112084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">work</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work item or delayed work item <a href="hdfwork.md">HdfWork</a>. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **HDF\_WORK\_BUSY\_PENDING**  if the work item is pending; returns  **HDF\_WORK\_BUSY\_RUNNING**  if the work item is running. 



## HdfWorkDestroy\(\)<a name="gae6166caaf1b114e17834c50414b2d52e"></a>

```
void HdfWorkDestroy ([HdfWork](hdfwork.md) * work)
```

 **Description:**

Destroys a work item. 

**Parameters:**

<a name="table1962872652084825"></a>
<table><thead align="left"><tr id="row1216255992084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1432662316084825"><a name="p1432662316084825"></a><a name="p1432662316084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p78098992084825"><a name="p78098992084825"></a><a name="p78098992084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row619862539084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">work</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work item <a href="hdfwork.md">HdfWork</a>. </td>
</tr>
</tbody>
</table>

## HdfWorkInit\(\)<a name="gad171adc8eda320fd01049a2b87ea62fb"></a>

```
int32_t HdfWorkInit ([HdfWork](hdfwork.md) * work, [HdfWorkFunc](driverutils.md#ga30665d61b03fae4a2ebc778c3d775ce5) func, void * arg )
```

 **Description:**

Initializes a work item. 

This function uses  **func**  and  **arg**  to initialize a work item. After the work item is added to a work queue, the thread of the work queue executes this function, and  **arg**  is passed to  **func**.

**Parameters:**

<a name="table552003396084825"></a>
<table><thead align="left"><tr id="row44762648084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p893641306084825"><a name="p893641306084825"></a><a name="p893641306084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p367084665084825"><a name="p367084665084825"></a><a name="p367084665084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1862632107084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">work</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work item <a href="hdfwork.md">HdfWork</a>. </td>
</tr>
<tr id="row1360728428084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the work execution function. </td>
</tr>
<tr id="row1058932203084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">arg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the argument of the work execution function.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1848727306084825"></a>
<table><thead align="left"><tr id="row1701541034084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p913458445084825"><a name="p913458445084825"></a><a name="p913458445084825"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1481617293084825"><a name="p1481617293084825"></a><a name="p1481617293084825"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1173717253084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p306032314084825"><a name="p306032314084825"></a><a name="p306032314084825"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p155219831084825"><a name="p155219831084825"></a><a name="p155219831084825"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row2011888903084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p929517181084825"><a name="p929517181084825"></a><a name="p929517181084825"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1435097206084825"><a name="p1435097206084825"></a><a name="p1435097206084825"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row1651379375084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1972387644084825"><a name="p1972387644084825"></a><a name="p1972387644084825"></a>HDF_ERR_MALLOC_FAIL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1516423840084825"><a name="p1516423840084825"></a><a name="p1516423840084825"></a>Memory allocation fails. </p>
</td>
</tr>
</tbody>
</table>

## HdfWorkQueueDestroy\(\)<a name="ga04ec328639aefd71683175e4c214fb80"></a>

```
void HdfWorkQueueDestroy ([HdfWorkQueue](hdfworkqueue.md) * queue)
```

 **Description:**

Destroys a work queue. 

**Parameters:**

<a name="table534332528084825"></a>
<table><thead align="left"><tr id="row2111071909084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1080804239084825"><a name="p1080804239084825"></a><a name="p1080804239084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p921154413084825"><a name="p921154413084825"></a><a name="p921154413084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row185869870084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">queue</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work queue <a href="hdfworkqueue.md">HdfWorkQueue</a>. </td>
</tr>
</tbody>
</table>

## HdfWorkQueueInit\(\)<a name="gad7afae1dc691818c513094c873decabd"></a>

```
int32_t HdfWorkQueueInit ([HdfWorkQueue](hdfworkqueue.md) * queue, char * name )
```

 **Description:**

Initializes a work queue. 

When a work queue is initialized, a thread is created. The thread cyclically executes the work items in the work queue, that is, executes their functions.

**Parameters:**

<a name="table1446626544084825"></a>
<table><thead align="left"><tr id="row663254396084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1423544993084825"><a name="p1423544993084825"></a><a name="p1423544993084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1701035140084825"><a name="p1701035140084825"></a><a name="p1701035140084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row618175613084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">queue</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work queue <strong id="b1612481182084825"><a name="b1612481182084825"></a><a name="b1612481182084825"></a>OsalWorkQueue</strong>. </td>
</tr>
<tr id="row1931931216084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the work queue name.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns a value listed below: 

<a name="table1624438230084825"></a>
<table><thead align="left"><tr id="row1662721686084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1620245203084825"><a name="p1620245203084825"></a><a name="p1620245203084825"></a>HDF_STATUS </p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p665441168084825"><a name="p665441168084825"></a><a name="p665441168084825"></a>Description  </p>
</th>
</tr>
</thead>
<tbody><tr id="row1226767596084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p659673729084825"><a name="p659673729084825"></a><a name="p659673729084825"></a>HDF_SUCCESS </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p651322260084825"><a name="p651322260084825"></a><a name="p651322260084825"></a>The operation is successful. </p>
</td>
</tr>
<tr id="row2063000705084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1065398867084825"><a name="p1065398867084825"></a><a name="p1065398867084825"></a>HDF_ERR_INVALID_PARAM </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1506005893084825"><a name="p1506005893084825"></a><a name="p1506005893084825"></a>Invalid parameter. </p>
</td>
</tr>
<tr id="row887463540084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275297654084825"><a name="p275297654084825"></a><a name="p275297654084825"></a>HDF_ERR_MALLOC_FAIL </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1666168169084825"><a name="p1666168169084825"></a><a name="p1666168169084825"></a>Memory allocation fails. </p>
</td>
</tr>
</tbody>
</table>

