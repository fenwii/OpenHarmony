# wifi\_mac80211\_ops.h<a name="ZH-CN_TOPIC_0000001054879520"></a>

## **Overview**<a name="section374492310084834"></a>

**Related Modules:**

[WLAN](WLAN.md)

**Description:**

Declares Media Access Control \(MAC\) APIs and functions related to control flows. 

This file declares APIs for scanning, connection, disconnection, and mode conversion, as well as data structures of the parameters of these APIs.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2061578440084834"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1078733917084834"></a>
<table><thead align="left"><tr id="row2032615057084834"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p384811771084834"><a name="p384811771084834"></a><a name="p384811771084834"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1088269676084834"><a name="p1088269676084834"></a><a name="p1088269676084834"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1931248843084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p481619112084834"><a name="p481619112084834"></a><a name="p481619112084834"></a><a href="KeyParams.md">KeyParams</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1943204476084834"><a name="p1943204476084834"></a><a name="p1943204476084834"></a>Describes a key. </p>
</td>
</tr>
<tr id="row193588226084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1663785965084834"><a name="p1663785965084834"></a><a name="p1663785965084834"></a><a href="Ieee80211Channel.md">Ieee80211Channel</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p975066648084834"><a name="p975066648084834"></a><a name="p975066648084834"></a>Describes a communication channel. </p>
</td>
</tr>
<tr id="row369149342084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1101512997084834"><a name="p1101512997084834"></a><a name="p1101512997084834"></a><a href="Ieee80211Rate.md">Ieee80211Rate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p262530186084834"><a name="p262530186084834"></a><a name="p262530186084834"></a>Describes the IEEE 802.11 rate. </p>
</td>
</tr>
<tr id="row2143449456084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170405186084834"><a name="p170405186084834"></a><a name="p170405186084834"></a><a href="Ieee80211McsInfo.md">Ieee80211McsInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p784666835084834"><a name="p784666835084834"></a><a name="p784666835084834"></a>Describes IEEE 802.11 Modulation and Coding Scheme (MCS) information. </p>
</td>
</tr>
<tr id="row1863240130084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872305437084834"><a name="p1872305437084834"></a><a name="p1872305437084834"></a><a href="Ieee80211StaHtCap.md">Ieee80211StaHtCap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1857118199084834"><a name="p1857118199084834"></a><a name="p1857118199084834"></a>Describes the IEEE 802.11 high-throughput (HT) capability. </p>
</td>
</tr>
<tr id="row992638711084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p679570798084834"><a name="p679570798084834"></a><a name="p679570798084834"></a><a href="Ieee80211SupportedBand.md">Ieee80211SupportedBand</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1058798448084834"><a name="p1058798448084834"></a><a name="p1058798448084834"></a>Describes IEEE 802.11 band information. </p>
</td>
</tr>
<tr id="row2110983091084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298961122084834"><a name="p298961122084834"></a><a name="p298961122084834"></a><a href="Wiphy.md">Wiphy</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1961856449084834"><a name="p1961856449084834"></a><a name="p1961856449084834"></a>Describes a wiphy device. </p>
</td>
</tr>
<tr id="row1235519113084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p484601109084834"><a name="p484601109084834"></a><a name="p484601109084834"></a><a href="WifiSsid.md">WifiSsid</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p223594919084834"><a name="p223594919084834"></a><a name="p223594919084834"></a>Describes an SSID. </p>
</td>
</tr>
<tr id="row184238508084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p799486307084834"><a name="p799486307084834"></a><a name="p799486307084834"></a><a href="ChannelDef.md">ChannelDef</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p739985811084834"><a name="p739985811084834"></a><a name="p739985811084834"></a>Describes a communication channel. </p>
</td>
</tr>
<tr id="row1248325131084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p202059886084834"><a name="p202059886084834"></a><a name="p202059886084834"></a><a href="WirelessDev.md">WirelessDev</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1620567909084834"><a name="p1620567909084834"></a><a name="p1620567909084834"></a>Describes a wireless device. </p>
</td>
</tr>
<tr id="row7850097084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p996514700084834"><a name="p996514700084834"></a><a name="p996514700084834"></a><a href="WifiScanRequest.md">WifiScanRequest</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p902706537084834"><a name="p902706537084834"></a><a name="p902706537084834"></a>Describes scan request parameters. </p>
</td>
</tr>
<tr id="row1481060177084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1035807439084834"><a name="p1035807439084834"></a><a name="p1035807439084834"></a><a href="CryptoSettings.md">CryptoSettings</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p779009754084834"><a name="p779009754084834"></a><a name="p779009754084834"></a>Describes cryptography settings. </p>
</td>
</tr>
<tr id="row727972448084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p38003701084834"><a name="p38003701084834"></a><a name="p38003701084834"></a><a href="MacAddress.md">MacAddress</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p72936192084834"><a name="p72936192084834"></a><a name="p72936192084834"></a>Describes the device MAC address. </p>
</td>
</tr>
<tr id="row317387377084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p119206230084834"><a name="p119206230084834"></a><a name="p119206230084834"></a><a href="WifiConnectParams.md">WifiConnectParams</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1635965278084834"><a name="p1635965278084834"></a><a name="p1635965278084834"></a>Describes parameters for a connection request. </p>
</td>
</tr>
<tr id="row1148976339084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p307539681084834"><a name="p307539681084834"></a><a name="p307539681084834"></a><a href="VifParams.md">VifParams</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p651555729084834"><a name="p651555729084834"></a><a name="p651555729084834"></a>Describes virtual API parameters. </p>
</td>
</tr>
<tr id="row176410118084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p431955289084834"><a name="p431955289084834"></a><a name="p431955289084834"></a><a href="StationDelParameters.md">StationDelParameters</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1789824895084834"><a name="p1789824895084834"></a><a name="p1789824895084834"></a>Describes parameters for canceling a connection. </p>
</td>
</tr>
<tr id="row1190967954084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p58876898084834"><a name="p58876898084834"></a><a name="p58876898084834"></a><a href="MacConfigParam.md">MacConfigParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p225201516084834"><a name="p225201516084834"></a><a name="p225201516084834"></a>Describes MAC configuration parameters. </p>
</td>
</tr>
<tr id="row1994661571084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p159350261084834"><a name="p159350261084834"></a><a name="p159350261084834"></a><a href="Mac80211DisconnectParam.md">Mac80211DisconnectParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1976095921084834"><a name="p1976095921084834"></a><a name="p1976095921084834"></a>Describes disconnection parameters. </p>
</td>
</tr>
<tr id="row55665046084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1669155536084834"><a name="p1669155536084834"></a><a name="p1669155536084834"></a><a href="Mac80211Ssids.md">Mac80211Ssids</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868531868084834"><a name="p1868531868084834"></a><a name="p1868531868084834"></a>Describes SSIDs. </p>
</td>
</tr>
<tr id="row1265233861084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1438349182084834"><a name="p1438349182084834"></a><a name="p1438349182084834"></a><a href="Mac80211beaconParam.md">Mac80211beaconParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p47673384084834"><a name="p47673384084834"></a><a name="p47673384084834"></a>Describes beacon parameters. </p>
</td>
</tr>
<tr id="row403189812084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1649378101084834"><a name="p1649378101084834"></a><a name="p1649378101084834"></a><a href="WifiMac80211Ops.md">WifiMac80211Ops</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1017483316084834"><a name="p1017483316084834"></a><a name="p1017483316084834"></a>Describes MAC-layer control APIs that need to be implemented by the driver. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table587012412084834"></a>
<table><thead align="left"><tr id="row987719948084834"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p787456838084834"><a name="p787456838084834"></a><a name="p787456838084834"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p372650164084834"><a name="p372650164084834"></a><a name="p372650164084834"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row819233921084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1353869964084834"><a name="p1353869964084834"></a><a name="p1353869964084834"></a><a href="WLAN.md#ga3e8945c521d2392cb775494570c560b3">WifiConnectParams</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p983973657084834"><a name="p983973657084834"></a><a name="p983973657084834"></a>typedef struct <a href="WifiConnectParams.md">WifiConnectParams</a>&nbsp;</p>
<p id="p2008666655084834"><a name="p2008666655084834"></a><a name="p2008666655084834"></a>Describes parameters for a connection request. </p>
</td>
</tr>
<tr id="row440968732084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p910900759084834"><a name="p910900759084834"></a><a name="p910900759084834"></a><a href="WLAN.md#ga85f7d8a3795887f090e0a6439b1df6e1">Mac80211SetMacParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p304991451084834"><a name="p304991451084834"></a><a name="p304991451084834"></a>typedef struct <a href="MacConfigParam.md">MacConfigParam</a>&nbsp;</p>
<p id="p1309948927084834"><a name="p1309948927084834"></a><a name="p1309948927084834"></a>Describes MAC configuration parameters. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1032574874084834"></a>
<table><thead align="left"><tr id="row2120011977084834"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1619479146084834"><a name="p1619479146084834"></a><a name="p1619479146084834"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p751514269084834"><a name="p751514269084834"></a><a name="p751514269084834"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2089751962084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1349667157084834"><a name="p1349667157084834"></a><a name="p1349667157084834"></a><a href="WLAN.md#ga75cba3dc6ab4c5dc5653b037433b3abf">MacSetType</a> { <a href="WLAN.md#gga75cba3dc6ab4c5dc5653b037433b3abfa52532b66ba237505f04a57b382f67cb1">MAC_BEACON_SET</a> = 0, <a href="WLAN.md#gga75cba3dc6ab4c5dc5653b037433b3abfa8bb6332eadf8a54cdcf7d02b6040e7f3">MAC_BEACON_ADD</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p69093415084834"><a name="p69093415084834"></a><a name="p69093415084834"></a>Enumerates setting types of MAC addresses. </p>
</td>
</tr>
<tr id="row1978158464084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1044531126084834"><a name="p1044531126084834"></a><a name="p1044531126084834"></a><a href="WLAN.md#ga9882f415202cf9acb0f4cdfbc456a88d">Ieee80211Band</a> { <a href="WLAN.md#gga9882f415202cf9acb0f4cdfbc456a88daf339f82c036557f42f668a358aa96da3">IEEE80211_BAND_2GHZ</a>, <a href="WLAN.md#gga9882f415202cf9acb0f4cdfbc456a88da0871c8866251ec4e668e956bb0427cfa">IEEE80211_BAND_5GHZ</a>, <a href="WLAN.md#gga9882f415202cf9acb0f4cdfbc456a88da703cf67d516a80d6dae1b1995017b9a4">IEEE80211_NUM_BANDS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p217241545084834"><a name="p217241545084834"></a><a name="p217241545084834"></a>Enumerates frequency bands. </p>
</td>
</tr>
<tr id="row438760750084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p901637932084834"><a name="p901637932084834"></a><a name="p901637932084834"></a><a href="WLAN.md#ga9d902b330de99c24b2a8c3ba7120af21">WifiChannelType</a> { <a href="WLAN.md#gga9d902b330de99c24b2a8c3ba7120af21ae0707e29a1748ee7f33d51acabaf8810">WIFI_CHAN_NO_HT</a>, <a href="WLAN.md#gga9d902b330de99c24b2a8c3ba7120af21a255f513fd4efa8bce0c015086e0588ea">WIFI_CHAN_HT20</a>, <a href="WLAN.md#gga9d902b330de99c24b2a8c3ba7120af21a1c6dbd2c2f6be59e4fa8312fe6009a98">WIFI_CHAN_HT40MINUS</a>, <a href="WLAN.md#gga9d902b330de99c24b2a8c3ba7120af21abdc85daa4bd2fdda2cfb14a975099652">WIFI_CHAN_HT40PLUS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p618650735084834"><a name="p618650735084834"></a><a name="p618650735084834"></a>Enumerates channel types. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1870544456084834"></a>
<table><thead align="left"><tr id="row937815670084834"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1017091292084834"><a name="p1017091292084834"></a><a name="p1017091292084834"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1297893574084834"><a name="p1297893574084834"></a><a name="p1297893574084834"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1675457722084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1762550803084834"><a name="p1762550803084834"></a><a name="p1762550803084834"></a><a href="WLAN.md#ga6542a735af0fe7496789c3c55380adfa">Mac80211RegisterOps</a> (struct <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> *ops) __attribute__((weak))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1068775402084834"><a name="p1068775402084834"></a><a name="p1068775402084834"></a>int32_t&nbsp;</p>
<p id="p98791596084834"><a name="p98791596084834"></a><a name="p98791596084834"></a>Registers a <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> object. </p>
</td>
</tr>
<tr id="row297823607084834"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p995469429084834"><a name="p995469429084834"></a><a name="p995469429084834"></a><a href="WLAN.md#gad7c34413d81d55ba090c90404d340c8a">Mac80211GetOps</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1976301203084834"><a name="p1976301203084834"></a><a name="p1976301203084834"></a>struct <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> *&nbsp;</p>
<p id="p1966411142084834"><a name="p1966411142084834"></a><a name="p1966411142084834"></a>Obtains the <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> object that the driver needs to implement. </p>
</td>
</tr>
</tbody>
</table>

