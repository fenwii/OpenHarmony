# wifi\_device\_config.h<a name="ZH-CN_TOPIC_0000001055515022"></a>

## **Overview**<a name="section778453403090253"></a>

**Related Modules:**

[Wifiservice](Wifiservice.md)

**Description:**

Defines the Wi-Fi station configuration. 

The Wi-Fi station configuration includes the security type and data length. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section92915215090253"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1632346778090253"></a>
<table><thead align="left"><tr id="row1066158153090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2065168689090253"><a name="p2065168689090253"></a><a name="p2065168689090253"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1850630100090253"><a name="p1850630100090253"></a><a name="p1850630100090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1764187907090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2025371893090253"><a name="p2025371893090253"></a><a name="p2025371893090253"></a><a href="WifiDeviceConfig.md">WifiDeviceConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p87309775090253"><a name="p87309775090253"></a><a name="p87309775090253"></a>Represents the Wi-Fi station configuration used to connect to a specified Wi-Fi device. </p>
</td>
</tr>
<tr id="row839625054090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p480251231090253"><a name="p480251231090253"></a><a name="p480251231090253"></a><a href="WifiScanParams.md">WifiScanParams</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p447499068090253"><a name="p447499068090253"></a><a name="p447499068090253"></a>Represents the Wi-Fi station configuration used to connect to a specified Wi-Fi device. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1503721551090253"></a>
<table><thead align="left"><tr id="row1269534120090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p121017280090253"><a name="p121017280090253"></a><a name="p121017280090253"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1723251136090253"><a name="p1723251136090253"></a><a name="p1723251136090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1252331470090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p552119585090253"><a name="p552119585090253"></a><a name="p552119585090253"></a><a href="Wifiservice.md#ga87d47fede3b37780bbd2f4981b560e54">WIFI_MAX_CONFIG_SIZE</a>&nbsp;&nbsp;&nbsp;10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p658558243090253"><a name="p658558243090253"></a><a name="p658558243090253"></a>Indicates the maximum number of Wi-Fi station configurations that can be added using <a href="Wifiservice.md#gaa0a50013ff978d6f82c655403946d8c9">AddDeviceConfig</a>. </p>
</td>
</tr>
<tr id="row479433443090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453134552090253"><a name="p453134552090253"></a><a name="p453134552090253"></a><a href="Wifiservice.md#ga658039dc314dff5e764e40677c84f5d9">WIFI_CONFIG_INVALID</a>&nbsp;&nbsp;&nbsp;(-1)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1941608123090253"><a name="p1941608123090253"></a><a name="p1941608123090253"></a>Indicates the value of <strong id="b776154048090253"><a name="b776154048090253"></a><a name="b776154048090253"></a>networkId</strong> when the configuration file is unavailable. </p>
</td>
</tr>
<tr id="row1375580461090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1395504616090253"><a name="p1395504616090253"></a><a name="p1395504616090253"></a><a href="Wifiservice.md#ga7e01d8c5079081de486637b4482c937a">WIFI_MAX_SSID_LEN</a>&nbsp;&nbsp;&nbsp;33</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1175710872090253"><a name="p1175710872090253"></a><a name="p1175710872090253"></a>Indicates the maximum length of a Wi-Fi SSID. </p>
</td>
</tr>
<tr id="row200151684090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p642407973090253"><a name="p642407973090253"></a><a name="p642407973090253"></a><a href="Wifiservice.md#ga6017e2d011b6cffcd3663db81a2b52d8">WIFI_MAX_KEY_LEN</a>&nbsp;&nbsp;&nbsp;65</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p837582006090253"><a name="p837582006090253"></a><a name="p837582006090253"></a>Indicates the maximum length of a Wi-Fi key. </p>
</td>
</tr>
<tr id="row680028476090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000324886090253"><a name="p1000324886090253"></a><a name="p1000324886090253"></a><a href="Wifiservice.md#gabc871a0934ad71ec71b29de3f9bc4815">WIFI_MAC_LEN</a>&nbsp;&nbsp;&nbsp;6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p190370001090253"><a name="p190370001090253"></a><a name="p190370001090253"></a>Indicates the maximum length of a Wi-Fi MAC address or a Wi-Fi BSSID. </p>
</td>
</tr>
<tr id="row1612075949090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1816820259090253"><a name="p1816820259090253"></a><a name="p1816820259090253"></a><a href="Wifiservice.md#ga101f9d44cb01fce5704f10ba8d9c7960">WIFI_PSK_LEN</a>&nbsp;&nbsp;&nbsp;32</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2046472406090253"><a name="p2046472406090253"></a><a name="p2046472406090253"></a>Indicates the maximum length of a Wi-Fi PSK. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table1920202335090253"></a>
<table><thead align="left"><tr id="row1864337667090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1931051230090253"><a name="p1931051230090253"></a><a name="p1931051230090253"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p267340654090253"><a name="p267340654090253"></a><a name="p267340654090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row96228885090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p970128392090253"><a name="p970128392090253"></a><a name="p970128392090253"></a><a href="Wifiservice.md#gaa32cc451f81eeb416eda5968f71f4612">WifiDeviceConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1016196292090253"><a name="p1016196292090253"></a><a name="p1016196292090253"></a>typedef struct <a href="WifiDeviceConfig.md">WifiDeviceConfig</a>&nbsp;</p>
<p id="p395612447090253"><a name="p395612447090253"></a><a name="p395612447090253"></a>Represents the Wi-Fi station configuration used to connect to a specified Wi-Fi device. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table87518810090253"></a>
<table><thead align="left"><tr id="row1937378214090253"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p590388314090253"><a name="p590388314090253"></a><a name="p590388314090253"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1097251928090253"><a name="p1097251928090253"></a><a name="p1097251928090253"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1703356761090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1850222011090253"><a name="p1850222011090253"></a><a name="p1850222011090253"></a><a href="Wifiservice.md#ga97c133f7db7c1234babcde03c4ce1b05">WifiSecurityType</a> { &nbsp;&nbsp;<a href="Wifiservice.md#gga97c133f7db7c1234babcde03c4ce1b05ad512f146aed5b76788c5be8dfb370f13">WIFI_SEC_TYPE_INVALID</a> = -1, <a href="Wifiservice.md#gga97c133f7db7c1234babcde03c4ce1b05a0ee2ed98b3ed21009c7d1b19945b8976">WIFI_SEC_TYPE_OPEN</a>, <a href="Wifiservice.md#gga97c133f7db7c1234babcde03c4ce1b05a2d99c910346eb2a47965aea234f2fbe6">WIFI_SEC_TYPE_WEP</a>, <a href="Wifiservice.md#gga97c133f7db7c1234babcde03c4ce1b05acec838f5f04a983f722c0cf749468870">WIFI_SEC_TYPE_PSK</a>, &nbsp;&nbsp;<a href="Wifiservice.md#gga97c133f7db7c1234babcde03c4ce1b05a7fe59ec8c8f2b2337f6b3a2268a9cfb4">WIFI_SEC_TYPE_SAE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1347089000090253"><a name="p1347089000090253"></a><a name="p1347089000090253"></a>Enumerates Wi-Fi security types. </p>
</td>
</tr>
<tr id="row1938883251090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p654320538090253"><a name="p654320538090253"></a><a name="p654320538090253"></a><a href="Wifiservice.md#gaa1a44d23b8478232f14d2adfc82cee77">WifiPskType</a> { <a href="Wifiservice.md#ggaa1a44d23b8478232f14d2adfc82cee77aedaceae77cb05c54cc8775653cfea4e8">WIFI_PSK_TYPE_ASCII</a> = 0, <a href="Wifiservice.md#ggaa1a44d23b8478232f14d2adfc82cee77ad480d8db3b2f13d7d53c8d8cab22f10a">WIFI_PSK_TYPE_HEX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1101939593090253"><a name="p1101939593090253"></a><a name="p1101939593090253"></a>Enumerates psk encryption types. </p>
</td>
</tr>
<tr id="row1341274830090253"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1390335995090253"><a name="p1390335995090253"></a><a name="p1390335995090253"></a><a href="Wifiservice.md#ga007bf5e22727debc02cad860e41a60a3">WifiScanType</a> { <a href="Wifiservice.md#gga007bf5e22727debc02cad860e41a60a3ad0d2a6703ee6092223acfae5bd295ab0">WIFI_FREQ_SCAN</a>, <a href="Wifiservice.md#gga007bf5e22727debc02cad860e41a60a3a0b97d9caa917ae9d6f23738424dd25a1">WIFI_SSID_SCAN</a>, <a href="Wifiservice.md#gga007bf5e22727debc02cad860e41a60a3a95e3be3877b0f9c483cb3b0575b6dce2">WIFI_BSSID_SCAN</a>, <a href="Wifiservice.md#gga007bf5e22727debc02cad860e41a60a3a75b4c033f7ddd140a17061c0bdb9d71a">WIFI_BAND_SCAN</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1263875893090253"><a name="p1263875893090253"></a><a name="p1263875893090253"></a>Enumerates Wi-Fi scan types. </p>
</td>
</tr>
</tbody>
</table>

