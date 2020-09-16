# wifi\_event.h<a name="EN-US_TOPIC_0000001055036448"></a>

## **Overview**<a name="section882997837191854"></a>

**Related Modules:**

[Wifiservice](wifiservice.md)

**Description:**

Defines callbacks and structure of Wi-Fi events. 

[RegisterWifiEvent](wifiservice.md#ga0e4d452915d1588664b91837b821eada)  can be used to listen for Wi-Fi connection, disconnection, and scan events. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section224000788191854"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table581210628191854"></a>
<table><thead align="left"><tr id="row1385906476191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1105739885191854"><a name="p1105739885191854"></a><a name="p1105739885191854"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2015403696191854"><a name="p2015403696191854"></a><a name="p2015403696191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row654254574191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1664147710191854"><a name="p1664147710191854"></a><a name="p1664147710191854"></a><a href="wifievent.md">WifiEvent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2118664659191854"><a name="p2118664659191854"></a><a name="p2118664659191854"></a>Represents the pointer to a Wi-Fi event callback for station and hotspot connection, disconnection, or scan. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table791102263191854"></a>
<table><thead align="left"><tr id="row1049564609191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p375647426191854"><a name="p375647426191854"></a><a name="p375647426191854"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1573659069191854"><a name="p1573659069191854"></a><a name="p1573659069191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row735793042191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1160616512191854"><a name="p1160616512191854"></a><a name="p1160616512191854"></a><a href="wifiservice.md#ga9f956732e8e8da52eb25a84a7c42e2bb">WIFI_STA_ACTIVE</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2044033094191854"><a name="p2044033094191854"></a><a name="p2044033094191854"></a>Indicates that the Wi-Fi station mode is enabled. </p>
</td>
</tr>
<tr id="row1679784279191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p118657265191854"><a name="p118657265191854"></a><a name="p118657265191854"></a><a href="wifiservice.md#gaf26289b0fe6ef5ae86395c0556187cf8">WIFI_STA_NOT_ACTIVE</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p445543499191854"><a name="p445543499191854"></a><a name="p445543499191854"></a>Indicates that the Wi-Fi station mode is disabled. </p>
</td>
</tr>
<tr id="row1100942311191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p606858882191854"><a name="p606858882191854"></a><a name="p606858882191854"></a><a href="wifiservice.md#gabf45f5779e5e04c8204db6a0d206af11">WIFI_HOTSPOT_ACTIVE</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1333834003191854"><a name="p1333834003191854"></a><a name="p1333834003191854"></a>Indicates that the Wi-Fi hotspot mode is enabled. </p>
</td>
</tr>
<tr id="row117145491191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1619307724191854"><a name="p1619307724191854"></a><a name="p1619307724191854"></a><a href="wifiservice.md#ga7dd021b8f69312a304632fd1d0244f02">WIFI_HOTSPOT_NOT_ACTIVE</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1288819886191854"><a name="p1288819886191854"></a><a name="p1288819886191854"></a>Indicates that the Wi-Fi hotspot mode is disabled. </p>
</td>
</tr>
<tr id="row970884863191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1381257157191854"><a name="p1381257157191854"></a><a name="p1381257157191854"></a><a href="wifiservice.md#gaace417e14bf248f54aaa3d4f84138b14">WIFI_MAX_EVENT_SIZE</a>   10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1400039594191854"><a name="p1400039594191854"></a><a name="p1400039594191854"></a>Indicates the maximum number of event listeners that can be registered using <a href="wifiservice.md#ga0e4d452915d1588664b91837b821eada">RegisterWifiEvent</a>. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table821043850191854"></a>
<table><thead align="left"><tr id="row617734762191854"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1091374400191854"><a name="p1091374400191854"></a><a name="p1091374400191854"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1388976306191854"><a name="p1388976306191854"></a><a name="p1388976306191854"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row463209902191854"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1091078971191854"><a name="p1091078971191854"></a><a name="p1091078971191854"></a><a href="wifiservice.md#ga6be99f93ce0d2d222c1f5f0a8217354d">WifiEventState</a> { <a href="wifiservice.md#gga6be99f93ce0d2d222c1f5f0a8217354daf35b74863c0b412178cb09d48303736b">WIFI_STATE_NOT_AVALIABLE</a> = 0, <a href="wifiservice.md#gga6be99f93ce0d2d222c1f5f0a8217354dac8939f62259c1f574abd1b251aa3b7c5">WIFI_STATE_AVALIABLE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1697006884191854"><a name="p1697006884191854"></a><a name="p1697006884191854"></a>Enumerates states in Wi-Fi events. </p>
</td>
</tr>
</tbody>
</table>

