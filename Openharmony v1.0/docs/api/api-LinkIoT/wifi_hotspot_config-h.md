# wifi\_hotspot\_config.h<a name="ZH-CN_TOPIC_0000001054876470"></a>

## **Overview**<a name="section1585029466191854"></a>

**Related Modules:**

[Wifiservice](Wifiservice.md)

**Description:**

Defines the Wi-Fi hotspot configuration. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2121703524191854"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table974216113191854"></a>
<table><thead align="left"><tr id="row611716081191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p874099958191854"><a name="p874099958191854"></a><a name="p874099958191854"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p918485569191854"><a name="p918485569191854"></a><a name="p918485569191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row912237927191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1916637155191854"><a name="p1916637155191854"></a><a name="p1916637155191854"></a><a href="HotspotConfig.md">HotspotConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p602889975191854"><a name="p602889975191854"></a><a name="p602889975191854"></a>Represents the hotspot configuration. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1333704322191854"></a>
<table><thead align="left"><tr id="row1516457345191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p991210715191854"><a name="p991210715191854"></a><a name="p991210715191854"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p751710229191854"><a name="p751710229191854"></a><a name="p751710229191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row150916282191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1987379613191854"><a name="p1987379613191854"></a><a name="p1987379613191854"></a><a href="Wifiservice.md#ga3aaba95d8760c837c01e209e52387711">WIFI_MAX_STA_NUM</a>&nbsp;&nbsp;&nbsp;6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p740019018191854"><a name="p740019018191854"></a><a name="p740019018191854"></a>Defines the maximum number of stations connected to a hotspot. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table2089654420191854"></a>
<table><thead align="left"><tr id="row1333469306191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1846613090191854"><a name="p1846613090191854"></a><a name="p1846613090191854"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1918283874191854"><a name="p1918283874191854"></a><a name="p1918283874191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1991246493191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p895899531191854"><a name="p895899531191854"></a><a name="p895899531191854"></a><a href="Wifiservice.md#gadb1b12fe6311711103e759aac7a470d4">RssiLevel</a> { <a href="Wifiservice.md#ggadb1b12fe6311711103e759aac7a470d4aac8c19cbf7131479b25de098fbdeb8d8">RSSI_LEVEL_1</a> = 1, <a href="Wifiservice.md#ggadb1b12fe6311711103e759aac7a470d4a57b5d33edaf93c78c05ab061d0592f0b">RSSI_LEVEL_2</a> = 2, <a href="Wifiservice.md#ggadb1b12fe6311711103e759aac7a470d4af91f262e971e83291e8bf6abe2bb7658">RSSI_LEVEL_3</a> = 3, <a href="Wifiservice.md#ggadb1b12fe6311711103e759aac7a470d4a553e0aaf0ca409a2cde703825ffbe0d2">RSSI_LEVEL_4</a> = 4 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p614051317191854"><a name="p614051317191854"></a><a name="p614051317191854"></a>Enumerates received signal strength indicator (RSSI) levels. </p>
</td>
</tr>
<tr id="row1877577714191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p841015152191854"><a name="p841015152191854"></a><a name="p841015152191854"></a><a href="Wifiservice.md#ga37e10532da87571ee89193beac42d246">HotspotBandType</a> { <a href="Wifiservice.md#gga37e10532da87571ee89193beac42d246ad4c4672bd05d6d0ef3f22861758df731">HOTSPOT_BAND_TYPE_2G</a> = 1, <a href="Wifiservice.md#gga37e10532da87571ee89193beac42d246a6eef5e29e90860fbffaa4744e5f069de">HOTSPOT_BAND_TYPE_5G</a> = 2 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1749048445191854"><a name="p1749048445191854"></a><a name="p1749048445191854"></a>Enumerates frequency bands supported by the Wi-Fi hotspot mode. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1602750438191854"></a>
<table><thead align="left"><tr id="row1311443782191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1757176199191854"><a name="p1757176199191854"></a><a name="p1757176199191854"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1761012699191854"><a name="p1761012699191854"></a><a name="p1761012699191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1339908630191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p454295772191854"><a name="p454295772191854"></a><a name="p454295772191854"></a><a href="Wifiservice.md#gaf384863106ea0ba10efc4a0bd3c86d24">SetBand</a> (int band)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1375311303191854"><a name="p1375311303191854"></a><a name="p1375311303191854"></a><a href="Wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a>&nbsp;</p>
<p id="p277000848191854"><a name="p277000848191854"></a><a name="p277000848191854"></a>Sets the frequency band for this hotspot. </p>
</td>
</tr>
<tr id="row2041408674191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p871568123191854"><a name="p871568123191854"></a><a name="p871568123191854"></a><a href="Wifiservice.md#gaa7b20be6e6d8f9b04ec7d417a1c6410c">GetBand</a> (int *result)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1739429443191854"><a name="p1739429443191854"></a><a name="p1739429443191854"></a><a href="Wifiservice.md#ga2506c6ad226c4feb1d19248013ff9568">WifiErrorCode</a>&nbsp;</p>
<p id="p216614321191854"><a name="p216614321191854"></a><a name="p216614321191854"></a>Obtains the frequency band of this hotspot. </p>
</td>
</tr>
</tbody>
</table>

