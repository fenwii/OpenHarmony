# WifiConnectParams<a name="EN-US_TOPIC_0000001055078181"></a>

## **Overview**<a name="section1426042301093537"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Describes parameters for a connection request. 

**Since:**

1.0

## **Summary**<a name="section585283650093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table2066674766093537"></a>
<table><thead align="left"><tr id="row1884772333093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1698762589093537"><a name="p1698762589093537"></a><a name="p1698762589093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p991258357093537"><a name="p991258357093537"></a><a name="p991258357093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row183361079093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1363042274093537"><a name="p1363042274093537"></a><a name="p1363042274093537"></a><a href="wlan.md#ga0c59333afe2ac58387c92260a8268de7">channel</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1616861572093537"><a name="p1616861572093537"></a><a name="p1616861572093537"></a>struct <a href="ieee80211channel.md">Ieee80211Channel</a> * </p>
</td>
</tr>
<tr id="row581516228093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1480401781093537"><a name="p1480401781093537"></a><a name="p1480401781093537"></a><a href="wlan.md#gaf088c497d633df51d8bee24e7a778c22">bssid</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179264051093537"><a name="p1179264051093537"></a><a name="p1179264051093537"></a>uint8_t * </p>
</td>
</tr>
<tr id="row1312377629093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119509628093537"><a name="p1119509628093537"></a><a name="p1119509628093537"></a><a href="wlan.md#ga875dd450960cc445dd2a12355bc6912c">ssid</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1215043435093537"><a name="p1215043435093537"></a><a name="p1215043435093537"></a>uint8_t * </p>
</td>
</tr>
<tr id="row1644924204093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1030451925093537"><a name="p1030451925093537"></a><a name="p1030451925093537"></a><a href="wlan.md#ga8274aa0c44fe19a615c38c67eb799c87">ie</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1095944629093537"><a name="p1095944629093537"></a><a name="p1095944629093537"></a>uint8_t * </p>
</td>
</tr>
<tr id="row453093078093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p607829037093537"><a name="p607829037093537"></a><a name="p607829037093537"></a><a href="wlan.md#ga18a38015e45de3571893b8c1edea991a">ssidLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1309987897093537"><a name="p1309987897093537"></a><a name="p1309987897093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row1365832241093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1881405797093537"><a name="p1881405797093537"></a><a name="p1881405797093537"></a><a href="wlan.md#gad5c61386055631b64c953fa46c2aad24">ieLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1465830136093537"><a name="p1465830136093537"></a><a name="p1465830136093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row1032126562093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1797368426093537"><a name="p1797368426093537"></a><a name="p1797368426093537"></a><a href="wlan.md#gaa91e37ddf709a3553a6352623ea8c341">crypto</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2024192790093537"><a name="p2024192790093537"></a><a name="p2024192790093537"></a>struct <a href="cryptosettings.md">CryptoSettings</a> </p>
</td>
</tr>
<tr id="row261911196093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2082651359093537"><a name="p2082651359093537"></a><a name="p2082651359093537"></a><a href="wlan.md#ga6ca72a4cfcb196dda7c2ca2562a1b20b">key</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1830901434093537"><a name="p1830901434093537"></a><a name="p1830901434093537"></a>const uint8_t * </p>
</td>
</tr>
<tr id="row636288406093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549719191093537"><a name="p549719191093537"></a><a name="p549719191093537"></a><a href="wlan.md#ga2c9cdaa7b998a7ffb4378f4a6cedbb75">authType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1397444799093537"><a name="p1397444799093537"></a><a name="p1397444799093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row56214738093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p51083728093537"><a name="p51083728093537"></a><a name="p51083728093537"></a><a href="wlan.md#ga81e32b68cb7ae4a68b1d42633fc181fe">privacy</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p559662340093537"><a name="p559662340093537"></a><a name="p559662340093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row2109196349093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1283718976093537"><a name="p1283718976093537"></a><a name="p1283718976093537"></a><a href="wlan.md#ga98603c2c633e6ca1ad940269cfb01e58">keyLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1430204642093537"><a name="p1430204642093537"></a><a name="p1430204642093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row953845558093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1069868484093537"><a name="p1069868484093537"></a><a name="p1069868484093537"></a><a href="wlan.md#ga27eb8efb66b131f8495baf2dcaee6eb6">keyIdx</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1494191226093537"><a name="p1494191226093537"></a><a name="p1494191226093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row1267696416093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1120766536093537"><a name="p1120766536093537"></a><a name="p1120766536093537"></a><a href="wlan.md#ga8212747b66b319e95586ad90d4191300">mfp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858627256093537"><a name="p858627256093537"></a><a name="p858627256093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row209072894093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p676492263093537"><a name="p676492263093537"></a><a name="p676492263093537"></a><a href="wlan.md#gac0b10633f99311af30dd220ae9d19e34">aucResv</a> [WIFI_CONNECT_PARM_RESV_SIZE]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2109815614093537"><a name="p2109815614093537"></a><a name="p2109815614093537"></a>uint8_t </p>
</td>
</tr>
</tbody>
</table>

