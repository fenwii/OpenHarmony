# wifiiot\_partition.h<a name="EN-US_TOPIC_0000001055355042"></a>

## **Overview**<a name="section345877574191856"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Declares the partition interface functions. 

These functions are used to initialize partitions and obtain partition tables. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1030570646191856"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table42920466191856"></a>
<table><thead align="left"><tr id="row845415333191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p254898800191856"><a name="p254898800191856"></a><a name="p254898800191856"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p853742928191856"><a name="p853742928191856"></a><a name="p853742928191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2118902034191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1215156774191856"><a name="p1215156774191856"></a><a name="p1215156774191856"></a><a href="wifiiotflashpartitioninfo.md">WifiIotFlashPartitionInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650011640191856"><a name="p650011640191856"></a><a name="p650011640191856"></a>Describes an entry in a flash partition table. </p>
</td>
</tr>
<tr id="row382414771191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1620171200191856"><a name="p1620171200191856"></a><a name="p1620171200191856"></a><a href="wifiiotflashpartitiontable.md">WifiIotFlashPartitionTable</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1042177026191856"><a name="p1042177026191856"></a><a name="p1042177026191856"></a>Describes a flash partition table. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table847235709191856"></a>
<table><thead align="left"><tr id="row65394483191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p736920675191856"><a name="p736920675191856"></a><a name="p736920675191856"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1320344038191856"><a name="p1320344038191856"></a><a name="p1320344038191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row617285772191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1775751331191856"><a name="p1775751331191856"></a><a name="p1775751331191856"></a><a href="wifiiot.md#gafa09129be9f2e306ae54ab9d913d4c96">WIFI_IOT_FLASH_PARTITON_MAX</a>   12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1154904977191856"><a name="p1154904977191856"></a><a name="p1154904977191856"></a>Indicates the maximum number of partition tables. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table2045033614191856"></a>
<table><thead align="left"><tr id="row950735587191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p221055544191856"><a name="p221055544191856"></a><a name="p221055544191856"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p703883551191856"><a name="p703883551191856"></a><a name="p703883551191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1296423366191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1709841567191856"><a name="p1709841567191856"></a><a name="p1709841567191856"></a><a href="wifiiot.md#ga2f287bbb40987fe6d1d7fa525574c00c">WifiIotFlashPartitionTableId</a> {   <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00ca084dbf8aafce9c7a3ecad33da66e05b0">WIFI_IOT_FLASH_PARTITON_BOOT</a> = 0, <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00cabb8d227a662a66aad9557d9fc817a8fb">WIFI_IOT_FLASH_PARTITON_FACTORY_NV</a>, <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00ca427d6a8603c364374b5eb714450e18c8">WIFI_IOT_FLASH_PARTITON_NORMAL_NV</a>, <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00ca50131238794a26984f0f1209f94b338f">WIFI_IOT_FLASH_PARTITON_NORMAL_NV_BACKUP</a>,   <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00ca779875726c11006ea771f1ad2fb8af9b">WIFI_IOT_FLASH_PARTITON_KERNEL_A</a>, <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00caddd52544b51d83e70cfe5966852f9780">WIFI_IOT_FLASH_PARTITON_KERNEL_B</a>, <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00ca4f7f1e1f9120cf095a9c7b5d076c4ba4">WIFI_IOT_FLASH_PARTITON_HILINK</a>, <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00cacff32ff0901d4ca46814d747880579fa">WIFI_IOT_FLASH_PARTITON_FILE_SYSTEM</a>,   <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00cae8c645e2e5d130218b6eaec1e57dc8ee">WIFI_IOT_FLASH_PARTITON_USR_RESERVE</a>, <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00ca70a3cdffb76b64cbacf6973bf06e0a0a">WIFI_IOT_FLASH_PARTITON_HILINK_PKI</a>, <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00ca84650ae2f4cd3e7be0a1a24eb378e28c">WIFI_IOT_FLASH_PARTITON_CRASH_INFO</a>, <a href="wifiiot.md#gga2f287bbb40987fe6d1d7fa525574c00ca7068d177a4cdb8239445b7cc5763d132">WIFI_IOT_FLASH_PARTITON_BOOT_BACK</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p100641453191856"><a name="p100641453191856"></a><a name="p100641453191856"></a>Indicates the partition table ID. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table740025705191856"></a>
<table><thead align="left"><tr id="row1548627452191856"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1488887914191856"><a name="p1488887914191856"></a><a name="p1488887914191856"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1660467742191856"><a name="p1660467742191856"></a><a name="p1660467742191856"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row83987449191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p716236964191856"><a name="p716236964191856"></a><a name="p716236964191856"></a><a href="wifiiot.md#ga89c372b7c3071619dfe5b05d3e779e9e">FlashPartitionInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p256929888191856"><a name="p256929888191856"></a><a name="p256929888191856"></a>unsigned int </p>
<p id="p1146322928191856"><a name="p1146322928191856"></a><a name="p1146322928191856"></a>Initializes a flash partition. </p>
</td>
</tr>
<tr id="row1324650813191856"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p192047891191856"><a name="p192047891191856"></a><a name="p192047891191856"></a><a href="wifiiot.md#ga1279111f8892710f1a84bb03fd8df2be">GetPartitionTable</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p615890478191856"><a name="p615890478191856"></a><a name="p615890478191856"></a><a href="wifiiotflashpartitiontable.md">WifiIotFlashPartitionTable</a> * </p>
<p id="p1787967733191856"><a name="p1787967733191856"></a><a name="p1787967733191856"></a>Obtains a flash partition table. </p>
</td>
</tr>
</tbody>
</table>

