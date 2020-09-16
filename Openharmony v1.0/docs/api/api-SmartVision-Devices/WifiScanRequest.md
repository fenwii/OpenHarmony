# WifiScanRequest<a name="ZH-CN_TOPIC_0000001055358150"></a>

## **Overview**<a name="section1909399662093537"></a>

**Related Modules:**

[WLAN](WLAN.md)

**Description:**

Describes scan request parameters. 

**Since:**

1.0

## **Summary**<a name="section159153441093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1786976054093537"></a>
<table><thead align="left"><tr id="row116437298093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p992170511093537"><a name="p992170511093537"></a><a name="p992170511093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1230596905093537"><a name="p1230596905093537"></a><a name="p1230596905093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row964028294093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p206734648093537"><a name="p206734648093537"></a><a name="p206734648093537"></a><a href="WLAN.md#ga761056fae3d79073bbc33ad3f00a7319">ssids</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1469755413093537"><a name="p1469755413093537"></a><a name="p1469755413093537"></a>struct <a href="WifiSsid.md">WifiSsid</a> *&nbsp;</p>
</td>
</tr>
<tr id="row1475595341093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1668111704093537"><a name="p1668111704093537"></a><a name="p1668111704093537"></a><a href="WLAN.md#gaf7bf0f80492f28c7c285f8023505bb8e">nSsids</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p831768643093537"><a name="p831768643093537"></a><a name="p831768643093537"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row961045682093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1079063445093537"><a name="p1079063445093537"></a><a name="p1079063445093537"></a><a href="WLAN.md#ga3150e4a25b1800ee713e08fbf9077116">nChannels</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p34899903093537"><a name="p34899903093537"></a><a name="p34899903093537"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1143510312093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p800902216093537"><a name="p800902216093537"></a><a name="p800902216093537"></a><a href="WLAN.md#gaa26674156ac0814fbc1f45b8e11b7b9f">ieLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1712148920093537"><a name="p1712148920093537"></a><a name="p1712148920093537"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1822134606093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p524701564093537"><a name="p524701564093537"></a><a name="p524701564093537"></a><a href="WLAN.md#ga43dd029f6f34ccb0255e519aded47478">wiphy</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2125583310093537"><a name="p2125583310093537"></a><a name="p2125583310093537"></a>struct <a href="Wiphy.md">Wiphy</a> *&nbsp;</p>
</td>
</tr>
<tr id="row923155366093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1978477402093537"><a name="p1978477402093537"></a><a name="p1978477402093537"></a><a href="WLAN.md#gada8e463843d9e5fef133d41fd745dc42">dev</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p766046444093537"><a name="p766046444093537"></a><a name="p766046444093537"></a>struct <a href="NetDevice.md">NetDevice</a> *&nbsp;</p>
</td>
</tr>
<tr id="row1722871975093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p777261357093537"><a name="p777261357093537"></a><a name="p777261357093537"></a><a href="WLAN.md#ga09f1cdfc6c524ca96aed6b1894baa720">wdev</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1876813720093537"><a name="p1876813720093537"></a><a name="p1876813720093537"></a>struct <a href="WirelessDev.md">WirelessDev</a> *&nbsp;</p>
</td>
</tr>
<tr id="row2086265524093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2040654393093537"><a name="p2040654393093537"></a><a name="p2040654393093537"></a><a href="WLAN.md#ga32ea10f832c5a03971033d5f44f3ef6c">aborted</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1692885300093537"><a name="p1692885300093537"></a><a name="p1692885300093537"></a>uint8_t&nbsp;</p>
</td>
</tr>
<tr id="row791048291093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1868701602093537"><a name="p1868701602093537"></a><a name="p1868701602093537"></a><a href="WLAN.md#ga5b6c8df255d62a73114aad42c1e4868d">prefixSsidScanFlag</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p808997078093537"><a name="p808997078093537"></a><a name="p808997078093537"></a>uint8_t&nbsp;</p>
</td>
</tr>
<tr id="row1648447297093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p428924301093537"><a name="p428924301093537"></a><a name="p428924301093537"></a><a href="WLAN.md#ga9bb2fd298749eab513163e3a7a2b03ee">resv</a> [SCAN_REQUEST_RESV_SIZE]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p708250669093537"><a name="p708250669093537"></a><a name="p708250669093537"></a>uint8_t&nbsp;</p>
</td>
</tr>
<tr id="row207093620093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p828876280093537"><a name="p828876280093537"></a><a name="p828876280093537"></a><a href="WLAN.md#ga92b16a60570fd1d28b948ee43f9b0124">ie</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p649732436093537"><a name="p649732436093537"></a><a name="p649732436093537"></a>uint8_t *&nbsp;</p>
</td>
</tr>
<tr id="row1792428381093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1207527658093537"><a name="p1207527658093537"></a><a name="p1207527658093537"></a><a href="WLAN.md#gaabb5ffed3a294507d4f51d598fd98717">channels</a> [MAX_SCAN_CHANNELS]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p122052805093537"><a name="p122052805093537"></a><a name="p122052805093537"></a>struct <a href="Ieee80211Channel.md">Ieee80211Channel</a> *&nbsp;</p>
</td>
</tr>
</tbody>
</table>

