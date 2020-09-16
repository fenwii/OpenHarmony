# WifiEvent<a name="ZH-CN_TOPIC_0000001054876478"></a>

## **Overview**<a name="section144926430191903"></a>

**Related Modules:**

[Wifiservice](Wifiservice.md)

**Description:**

Represents the pointer to a Wi-Fi event callback for station and hotspot connection, disconnection, or scan. 

If you do not need a callback, set the value of its pointer to  **NULL**. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section916743370191903"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2118539174191903"></a>
<table><thead align="left"><tr id="row2022726937191903"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p408354200191903"><a name="p408354200191903"></a><a name="p408354200191903"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p554385714191903"><a name="p554385714191903"></a><a name="p554385714191903"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1673695053191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1615342085191903"><a name="p1615342085191903"></a><a name="p1615342085191903"></a><a href="WifiEvent.md#ad2a8de07fb4c8dffcb7885527db2cc87">OnWifiConnectionChanged</a> )(int state, <a href="WifiLinkedInfo.md">WifiLinkedInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1870805406191903"><a name="p1870805406191903"></a><a name="p1870805406191903"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row319933265191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1584772054191903"><a name="p1584772054191903"></a><a name="p1584772054191903"></a><a href="WifiEvent.md#ab66bdeddfe7f9fbfb2ab307ff1f1de95">OnWifiScanStateChanged</a> )(int state, int size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1360801749191903"><a name="p1360801749191903"></a><a name="p1360801749191903"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row435678488191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1996972561191903"><a name="p1996972561191903"></a><a name="p1996972561191903"></a><a href="WifiEvent.md#a47e031d8f8c4ed7addc7f7610c3d080c">OnHotspotStateChanged</a> )(int state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p194840352191903"><a name="p194840352191903"></a><a name="p194840352191903"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row2070324101191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p257841525191903"><a name="p257841525191903"></a><a name="p257841525191903"></a><a href="WifiEvent.md#a7de976a32a0631ff41891bffc1cd0212">OnHotspotStaJoin</a> )(<a href="StationInfo.md">StationInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p84422114191903"><a name="p84422114191903"></a><a name="p84422114191903"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row710680967191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p876359313191903"><a name="p876359313191903"></a><a name="p876359313191903"></a><a href="WifiEvent.md#a41a813377acd4eebaed2e4ca83aeec48">OnHotspotStaLeave</a> )(<a href="StationInfo.md">StationInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1139423777191903"><a name="p1139423777191903"></a><a name="p1139423777191903"></a>void(*&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1598811592191903"></a>

## **Field Documentation**<a name="section1842563426191903"></a>

## OnHotspotStaJoin<a name="a7de976a32a0631ff41891bffc1cd0212"></a>

```
void(* WifiEvent::OnHotspotStaJoin) ([StationInfo](StationInfo.md) *info)
```

 **Description:**

Station connected 

## OnHotspotStaLeave<a name="a41a813377acd4eebaed2e4ca83aeec48"></a>

```
void(* WifiEvent::OnHotspotStaLeave) ([StationInfo](StationInfo.md) *info)
```

 **Description:**

Station disconnected 

## OnHotspotStateChanged<a name="a47e031d8f8c4ed7addc7f7610c3d080c"></a>

```
void(* WifiEvent::OnHotspotStateChanged) (int state)
```

 **Description:**

Hotspot state change 

## OnWifiConnectionChanged<a name="ad2a8de07fb4c8dffcb7885527db2cc87"></a>

```
void(* WifiEvent::OnWifiConnectionChanged) (int state, [WifiLinkedInfo](WifiLinkedInfo.md) *info)
```

 **Description:**

Connection state change 

## OnWifiScanStateChanged<a name="ab66bdeddfe7f9fbfb2ab307ff1f1de95"></a>

```
void(* WifiEvent::OnWifiScanStateChanged) (int state, int size)
```

 **Description:**

Scan state change 

