# WifiMac80211Ops<a name="ZH-CN_TOPIC_0000001054598203"></a>

## **Overview**<a name="section809700101084842"></a>

**Related Modules:**

[WLAN](WLAN.md)

**Description:**

Describes MAC-layer control APIs that need to be implemented by the driver. 

**Since:**

1.0

## **Summary**<a name="section432572741084842"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table707640118084842"></a>
<table><thead align="left"><tr id="row1067623380084842"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p314058054084842"><a name="p314058054084842"></a><a name="p314058054084842"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1948451261084842"><a name="p1948451261084842"></a><a name="p1948451261084842"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row949996979084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1733295837084842"><a name="p1733295837084842"></a><a name="p1733295837084842"></a><a href="WLAN.md#ga0a4446bf704b9f4b673f68ff97002b1b">changeVirtualIntf</a> )(<a href="NetDevice.md">NetDevice</a> *netDev, uint8_t iftype, uint32_t *flags, struct <a href="VifParams.md">VifParams</a> *params)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2116096109084842"><a name="p2116096109084842"></a><a name="p2116096109084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row595855350084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1571497458084842"><a name="p1571497458084842"></a><a name="p1571497458084842"></a><a href="WLAN.md#ga519c91a244639e25a8c604e284486873">setSsid</a> )(<a href="NetDevice.md">NetDevice</a> *netDev, const uint8_t *ssid, uint32_t ssidLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p705890806084842"><a name="p705890806084842"></a><a name="p705890806084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1067213486084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p218730540084842"><a name="p218730540084842"></a><a name="p218730540084842"></a><a href="WLAN.md#ga37e19745783d5dbf8439b9f1f89ca6f5">setMeshId</a> )(<a href="NetDevice.md">NetDevice</a> *netDev, const char *meshId, uint32_t meshIdLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1317294999084842"><a name="p1317294999084842"></a><a name="p1317294999084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1108018159084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1936236269084842"><a name="p1936236269084842"></a><a name="p1936236269084842"></a><a href="WLAN.md#ga177446df24b19e4ddca32e9719d6fe8e">setMacAddr</a> )(<a href="NetDevice.md">NetDevice</a> *netDev, <a href="WLAN.md#ga85f7d8a3795887f090e0a6439b1df6e1">Mac80211SetMacParam</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1111677984084842"><a name="p1111677984084842"></a><a name="p1111677984084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1627046804084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p615972082084842"><a name="p615972082084842"></a><a name="p615972082084842"></a><a href="WLAN.md#ga833043e11a73c8f53cb918e25715939e">changeBeacon</a> )(<a href="NetDevice.md">NetDevice</a> *netDev, <a href="Mac80211beaconParam.md">Mac80211beaconParam</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2126262255084842"><a name="p2126262255084842"></a><a name="p2126262255084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1913706519084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2130112415084842"><a name="p2130112415084842"></a><a name="p2130112415084842"></a><a href="WLAN.md#ga166ca94a9482995f3e1f58263eeeed02">setChannel</a> )(<a href="NetDevice.md">NetDevice</a> *netDev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2111894127084842"><a name="p2111894127084842"></a><a name="p2111894127084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1641937130084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p745692553084842"><a name="p745692553084842"></a><a name="p745692553084842"></a><a href="WLAN.md#ga367902162f25b7b4c5b80372bb6a81f2">addKey</a> )(struct <a href="NetDevice.md">NetDevice</a> *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *macAddr, struct <a href="KeyParams.md">KeyParams</a> *params)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p81219953084842"><a name="p81219953084842"></a><a name="p81219953084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row899227140084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p989827613084842"><a name="p989827613084842"></a><a name="p989827613084842"></a><a href="WLAN.md#ga7edb052049a9420b938085322c6a0418">delKey</a> )(struct <a href="NetDevice.md">NetDevice</a> *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *macAddr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p337546595084842"><a name="p337546595084842"></a><a name="p337546595084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row187742809084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1342372725084842"><a name="p1342372725084842"></a><a name="p1342372725084842"></a><a href="WLAN.md#gae4e2e0af8777ab0bae98b1816664bddc">setDefaultKey</a> )(struct <a href="NetDevice.md">NetDevice</a> *netdev, uint8_t keyIndex, bool unicast, bool multicas)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p947245658084842"><a name="p947245658084842"></a><a name="p947245658084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row544275295084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p447583182084842"><a name="p447583182084842"></a><a name="p447583182084842"></a><a href="WLAN.md#ga203437a6b1d66758f2217f7154ce1210">startAp</a> )(<a href="NetDevice.md">NetDevice</a> *netDev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1371156885084842"><a name="p1371156885084842"></a><a name="p1371156885084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1448496561084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478617089084842"><a name="p478617089084842"></a><a name="p478617089084842"></a><a href="WLAN.md#gaf30acc8bd9ecd9bffbc46f423423266e">stopAp</a> )(<a href="NetDevice.md">NetDevice</a> *netDev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p611020684084842"><a name="p611020684084842"></a><a name="p611020684084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1218095205084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1174373987084842"><a name="p1174373987084842"></a><a name="p1174373987084842"></a><a href="WLAN.md#ga974552db5307795e70d5868edccecc1c">delStation</a> )(<a href="NetDevice.md">NetDevice</a> *netDev, const uint8_t *macAddr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p689970439084842"><a name="p689970439084842"></a><a name="p689970439084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row2020735536084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1209283503084842"><a name="p1209283503084842"></a><a name="p1209283503084842"></a><a href="WLAN.md#ga9f26a0c3e31e1b57cc8b357964cce3db">connect</a> )(<a href="NetDevice.md">NetDevice</a> *netDev, <a href="WifiConnectParams.md">WifiConnectParams</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1620159743084842"><a name="p1620159743084842"></a><a name="p1620159743084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1396284153084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p595092656084842"><a name="p595092656084842"></a><a name="p595092656084842"></a><a href="WLAN.md#ga558d3d417f465ca592dc94c3040b2d1f">disconnect</a> )(<a href="NetDevice.md">NetDevice</a> *netDev, uint16_t reasonCode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p434373680084842"><a name="p434373680084842"></a><a name="p434373680084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row2072218142084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1666886644084842"><a name="p1666886644084842"></a><a name="p1666886644084842"></a><a href="WLAN.md#ga259da70c25a528287c433af2f7bcf530">startScan</a> )(<a href="NetDevice.md">NetDevice</a> *netDev, struct <a href="WifiScanRequest.md">WifiScanRequest</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1149565783084842"><a name="p1149565783084842"></a><a name="p1149565783084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row304183241084842"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1686142177084842"><a name="p1686142177084842"></a><a name="p1686142177084842"></a><a href="WLAN.md#gab870d8100c1c9cb60b27c75a44bb30d4">abortScan</a> )(<a href="NetDevice.md">NetDevice</a> *netDev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p68583376084842"><a name="p68583376084842"></a><a name="p68583376084842"></a>int32_t(*&nbsp;</p>
</td>
</tr>
</tbody>
</table>

