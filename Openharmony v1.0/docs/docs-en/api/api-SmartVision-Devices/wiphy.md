# Wiphy<a name="EN-US_TOPIC_0000001054479605"></a>

## **Overview**<a name="section1466431081093537"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Describes a wiphy device. 

**Since:**

1.0

## **Summary**<a name="section1247935344093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1141138029093537"></a>
<table><thead align="left"><tr id="row716017626093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p217954507093537"><a name="p217954507093537"></a><a name="p217954507093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1111158173093537"><a name="p1111158173093537"></a><a name="p1111158173093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1227438593093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2120211046093537"><a name="p2120211046093537"></a><a name="p2120211046093537"></a><a href="wlan.md#ga5396b8e87fe6a6be0c7dd789fe289c50">permAddr</a> [WLAN_MAC_ADDR_LEN]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p526006353093537"><a name="p526006353093537"></a><a name="p526006353093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row321925697093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p334178319093537"><a name="p334178319093537"></a><a name="p334178319093537"></a><a href="wlan.md#ga8d1059e645ca6684e9ea82044e03270b">addrMask</a> [WLAN_MAC_ADDR_LEN]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2076471389093537"><a name="p2076471389093537"></a><a name="p2076471389093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row1536919827093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044960761093537"><a name="p2044960761093537"></a><a name="p2044960761093537"></a><a href="wlan.md#ga0f4b1664afa7f688b0e7fe974e8676a2">flags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1811429024093537"><a name="p1811429024093537"></a><a name="p1811429024093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row1256169749093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1700409853093537"><a name="p1700409853093537"></a><a name="p1700409853093537"></a><a href="wlan.md#ga0c0e8af92ed7d85cbcc04bcf4f13a8b7">signalType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1248327825093537"><a name="p1248327825093537"></a><a name="p1248327825093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row2066405472093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1206422677093537"><a name="p1206422677093537"></a><a name="p1206422677093537"></a><a href="wlan.md#gac64622da7ddfc981d13380a66321ee61">maxScanSsids</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p293685799093537"><a name="p293685799093537"></a><a name="p293685799093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row490465385093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1671239326093537"><a name="p1671239326093537"></a><a name="p1671239326093537"></a><a href="wlan.md#ga33ab965c40e11c007cadf1116113ca21">interfaceModes</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757119739093537"><a name="p757119739093537"></a><a name="p757119739093537"></a>uint16_t </p>
</td>
</tr>
<tr id="row962697933093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p604235849093537"><a name="p604235849093537"></a><a name="p604235849093537"></a><a href="wlan.md#ga249fb8ce5c398f3c6588519e58cd11e9">maxScanIeLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1181544193093537"><a name="p1181544193093537"></a><a name="p1181544193093537"></a>uint16_t </p>
</td>
</tr>
<tr id="row1632050078093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228834393093537"><a name="p228834393093537"></a><a name="p228834393093537"></a><a href="wlan.md#gabdd49dff12ed26c47f1935fb2bf3d873">aucRsv</a> [WIPHY_RSV_SIZE]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p529494185093537"><a name="p529494185093537"></a><a name="p529494185093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row1310691193093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p225469913093537"><a name="p225469913093537"></a><a name="p225469913093537"></a><a href="wlan.md#gab6cb6ce28cef7f1f5dc0d19380e8ad05">nCipherSuites</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1930916770093537"><a name="p1930916770093537"></a><a name="p1930916770093537"></a>int32_t </p>
</td>
</tr>
<tr id="row1880063085093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2033245826093537"><a name="p2033245826093537"></a><a name="p2033245826093537"></a><a href="wlan.md#ga011f5a473787d4700441e4bf7387673a">cipherSuites</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p912028967093537"><a name="p912028967093537"></a><a name="p912028967093537"></a>const uint32_t * </p>
</td>
</tr>
<tr id="row45007360093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p631893943093537"><a name="p631893943093537"></a><a name="p631893943093537"></a><a href="wlan.md#gafa733ea2e4b2efa2dc10938956a95f85">fragThreshold</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p917944494093537"><a name="p917944494093537"></a><a name="p917944494093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row296733979093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p265073608093537"><a name="p265073608093537"></a><a name="p265073608093537"></a><a href="wlan.md#ga00874e60aa7dc8c7455732e633586813">rtsThreshold</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p899873145093537"><a name="p899873145093537"></a><a name="p899873145093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row477043918093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p867076573093537"><a name="p867076573093537"></a><a name="p867076573093537"></a><a href="wlan.md#gaf3ab07acceaeff1edc793cb23d739ec5">bands</a> [<a href="wlan.md#gga9882f415202cf9acb0f4cdfbc456a88da703cf67d516a80d6dae1b1995017b9a4">IEEE80211_NUM_BANDS</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p639112146093537"><a name="p639112146093537"></a><a name="p639112146093537"></a>struct <a href="ieee80211supportedband.md">Ieee80211SupportedBand</a> * </p>
</td>
</tr>
<tr id="row2075839466093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p295589507093537"><a name="p295589507093537"></a><a name="p295589507093537"></a><a href="wlan.md#ga760737c03ad122b360ca8ed814869e4b">priv</a> [WIPHY_PRIV_SIZE]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1282000055093537"><a name="p1282000055093537"></a><a name="p1282000055093537"></a>uint8_t </p>
</td>
</tr>
</tbody>
</table>

