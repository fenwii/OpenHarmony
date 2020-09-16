# WifiLinkedInfo<a name="ZH-CN_TOPIC_0000001055195070"></a>

## **Overview**<a name="section1797440792191903"></a>

**Related Modules:**

[Wifiservice](Wifiservice.md)

**Description:**

Represents the Wi-Fi connection information. 

This refers to the information about the hotspot connected to this station. The information is obtained using  [GetLinkedInfo](Wifiservice.md#gaa8f07a31b01761da44f0fe90d461c168).

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1700061953191903"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1755669983191903"></a>
<table><thead align="left"><tr id="row1776022147191903"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1082144124191903"><a name="p1082144124191903"></a><a name="p1082144124191903"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1352008501191903"><a name="p1352008501191903"></a><a name="p1352008501191903"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1794995029191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2091125967191903"><a name="p2091125967191903"></a><a name="p2091125967191903"></a><a href="WifiLinkedInfo.md#a0f557af231a258550f760b1a92aa733e">ssid</a> [<a href="Wifiservice.md#ga7e01d8c5079081de486637b4482c937a">WIFI_MAX_SSID_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1870972992191903"><a name="p1870972992191903"></a><a name="p1870972992191903"></a>char&nbsp;</p>
</td>
</tr>
<tr id="row2088356068191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2089675624191903"><a name="p2089675624191903"></a><a name="p2089675624191903"></a><a href="WifiLinkedInfo.md#a3f0356f452ed695738e3e5cb08f9c65f">bssid</a> [<a href="Wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815">WIFI_MAC_LEN</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1765801702191903"><a name="p1765801702191903"></a><a name="p1765801702191903"></a>unsigned char&nbsp;</p>
</td>
</tr>
<tr id="row191883499191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p515543670191903"><a name="p515543670191903"></a><a name="p515543670191903"></a><a href="WifiLinkedInfo.md#acd91b72e5f8c24820adc535be0592991">rssi</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1158292429191903"><a name="p1158292429191903"></a><a name="p1158292429191903"></a>int&nbsp;</p>
</td>
</tr>
<tr id="row1439919605191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p121049426191903"><a name="p121049426191903"></a><a name="p121049426191903"></a><a href="WifiLinkedInfo.md#a65475ec0dbd48760f7b9914e253730b9">connState</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1737321150191903"><a name="p1737321150191903"></a><a name="p1737321150191903"></a><a href="Wifiservice.md#ga970b7d5373775b1c7f3b31074bae50e1">WifiConnState</a>&nbsp;</p>
</td>
</tr>
<tr id="row348556927191903"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p315077612191903"><a name="p315077612191903"></a><a name="p315077612191903"></a><a href="WifiLinkedInfo.md#a3a19295ddfaee0706413cf716521d02d">disconnectedReason</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1760285191903"><a name="p1760285191903"></a><a name="p1760285191903"></a>unsigned short&nbsp;</p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section243656672191903"></a>

## **Field Documentation**<a name="section2117568757191903"></a>

## bssid<a name="a3f0356f452ed695738e3e5cb08f9c65f"></a>

```
unsigned char WifiLinkedInfo::bssid[[WIFI_MAC_LEN](Wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815)]
```

 **Description:**

Basic service set ID \(BSSID\). For its length, see  [WIFI\_MAC\_LEN](Wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815). 

## connState<a name="a65475ec0dbd48760f7b9914e253730b9"></a>

```
[WifiConnState](Wifiservice.md#ga970b7d5373775b1c7f3b31074bae50e1) WifiLinkedInfo::connState
```

 **Description:**

Wi-Fi connection state, which is defined in  [WifiConnState](Wifiservice.md#ga970b7d5373775b1c7f3b31074bae50e1) 

## disconnectedReason<a name="a3a19295ddfaee0706413cf716521d02d"></a>

```
unsigned short WifiLinkedInfo::disconnectedReason
```

 **Description:**

Reason for Wi-Fi disconnection 

## rssi<a name="acd91b72e5f8c24820adc535be0592991"></a>

```
int WifiLinkedInfo::rssi
```

 **Description:**

Received signal strength indicator \(RSSI\) 

## ssid<a name="a0f557af231a258550f760b1a92aa733e"></a>

```
char WifiLinkedInfo::ssid[[WIFI_MAX_SSID_LEN](Wifiservice.md#ga7e01d8c5079081de486637b4482c937a)]
```

 **Description:**

[Service](Service.md)  set ID \(SSID\). For its length, see  [WIFI\_MAX\_SSID\_LEN](Wifiservice.md#ga7e01d8c5079081de486637b4482c937a). 

