# WifiFeature<a name="EN-US_TOPIC_0000001055678136"></a>

## **Overview**<a name="section1868448886093537"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Defines a WLAN feature. 

**Since:**

1.0

## **Summary**<a name="section172360035093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1724991357093537"></a>
<table><thead align="left"><tr id="row650193364093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1449404187093537"><a name="p1449404187093537"></a><a name="p1449404187093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p995106195093537"><a name="p995106195093537"></a><a name="p995106195093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1676093335093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1237511085093537"><a name="p1237511085093537"></a><a name="p1237511085093537"></a><a href="wlan.md#gae63e4c5602dbc64bd9905d6b6a4e7aad">name</a> [<a href="wlan.md#gaf460a45a5e365279ca6bc5b3e8750542">MAX_WIFI_COMPONENT_NAME_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2115598754093537"><a name="p2115598754093537"></a><a name="p2115598754093537"></a>char </p>
</td>
</tr>
<tr id="row1366348583093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1180884606093537"><a name="p1180884606093537"></a><a name="p1180884606093537"></a><a href="wlan.md#ga213bff4c0d74fb3db3ff7c21bea781ae">chip</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1125117095093537"><a name="p1125117095093537"></a><a name="p1125117095093537"></a>struct <a href="hdfwifichipdata.md">HdfWifiChipData</a> * </p>
</td>
</tr>
<tr id="row1608967521093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p558240782093537"><a name="p558240782093537"></a><a name="p558240782093537"></a><a href="wlan.md#ga8b09c66c75ed9515bbf5f76e25c86e57">init</a> )(struct <a href="wififeature.md">WifiFeature</a> *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p829590947093537"><a name="p829590947093537"></a><a name="p829590947093537"></a>int32_t(* </p>
</td>
</tr>
<tr id="row520831648093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429944276093537"><a name="p429944276093537"></a><a name="p429944276093537"></a><a href="wlan.md#gaf03445197e62e8d5cc5de5c7bba185dd">deInit</a> )(struct <a href="wififeature.md">WifiFeature</a> *feature)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1935998610093537"><a name="p1935998610093537"></a><a name="p1935998610093537"></a>int32_t(* </p>
</td>
</tr>
</tbody>
</table>

