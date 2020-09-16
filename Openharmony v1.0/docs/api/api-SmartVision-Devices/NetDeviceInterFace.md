# NetDeviceInterFace<a name="ZH-CN_TOPIC_0000001055039526"></a>

## **Overview**<a name="section1980757162093532"></a>

**Related Modules:**

[WLAN](WLAN.md)

**Description:**

Defines interfaces that need to be implemented externally by network devices, including initializing, opening, and closing a network device. 

**Since:**

1.0

## **Summary**<a name="section1837891983093532"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1870730433093532"></a>
<table><thead align="left"><tr id="row1595247893093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2100290633093532"><a name="p2100290633093532"></a><a name="p2100290633093532"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1140452212093532"><a name="p1140452212093532"></a><a name="p1140452212093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1085981629093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1057417435093532"><a name="p1057417435093532"></a><a name="p1057417435093532"></a><a href="WLAN.md#ga24cdc29146b8f84d021328e8a31269a5">init</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846083566093532"><a name="p846083566093532"></a><a name="p846083566093532"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row475927687093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1440400512093532"><a name="p1440400512093532"></a><a name="p1440400512093532"></a><a href="WLAN.md#ga371e13402535662210549c3ca3303691">deInit</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p477548820093532"><a name="p477548820093532"></a><a name="p477548820093532"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row1533480914093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p583556345093532"><a name="p583556345093532"></a><a name="p583556345093532"></a><a href="WLAN.md#ga154f75bcfd914b1fb243041186b60a3f">open</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1450099687093532"><a name="p1450099687093532"></a><a name="p1450099687093532"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1787836037093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1303147923093532"><a name="p1303147923093532"></a><a name="p1303147923093532"></a><a href="WLAN.md#ga5e328f3dc0b610672889e66b33bb7cf8">stop</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1788719465093532"><a name="p1788719465093532"></a><a name="p1788719465093532"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row640431440093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1622250586093532"><a name="p1622250586093532"></a><a name="p1622250586093532"></a><a href="WLAN.md#ga5d6e31f59da2eef0998deadd40e13304">xmit</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev, struct <a href="NetBuf.md">NetBuf</a> *netBuff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1855223351093532"><a name="p1855223351093532"></a><a name="p1855223351093532"></a><a href="WLAN.md#ga9fb4e578a15db1b0087d7b3831591ced">NetDevTxResult</a>(*&nbsp;</p>
</td>
</tr>
<tr id="row1514024977093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p550531593093532"><a name="p550531593093532"></a><a name="p550531593093532"></a><a href="WLAN.md#ga6c3d34c3329316632c7f6b6b19d2f983">ioctl</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev, <a href="IfReq.md">IfReq</a> *req, int32_t cmd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p852939400093532"><a name="p852939400093532"></a><a name="p852939400093532"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row937796416093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p357508291093532"><a name="p357508291093532"></a><a name="p357508291093532"></a><a href="WLAN.md#ga104f6b8049728769f54563aa242850b8">setMacAddr</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev, void *addr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p510090765093532"><a name="p510090765093532"></a><a name="p510090765093532"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row126828064093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1431993996093532"><a name="p1431993996093532"></a><a name="p1431993996093532"></a><a href="WLAN.md#ga3dcf9dd183845770dc8589eb98e59fce">getStats</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1308392848093532"><a name="p1308392848093532"></a><a name="p1308392848093532"></a>struct NetDevStats *(*&nbsp;</p>
</td>
</tr>
<tr id="row423617353093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1471791503093532"><a name="p1471791503093532"></a><a name="p1471791503093532"></a><a href="WLAN.md#ga334e7e9c31ff9408ba67aed1cb96a174">setNetIfStatus</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev, <a href="WLAN.md#ga0fb482694e5eac3f48c75de1749c8baf">NetIfStatus</a> status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p928072626093532"><a name="p928072626093532"></a><a name="p928072626093532"></a>void(*&nbsp;</p>
</td>
</tr>
<tr id="row1274075918093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p308982454093532"><a name="p308982454093532"></a><a name="p308982454093532"></a><a href="WLAN.md#ga3e08c5be1dbe6e4aa6fc1f930783c295">selectQueue</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev, struct <a href="NetBuf.md">NetBuf</a> *netBuff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p457856997093532"><a name="p457856997093532"></a><a name="p457856997093532"></a>uint16_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1741437011093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1029441324093532"><a name="p1029441324093532"></a><a name="p1029441324093532"></a><a href="WLAN.md#ga518102ebc29b985161160ae22b066faf">netifNotify</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev, <a href="NetDevNotify.md">NetDevNotify</a> *notify)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1474103464093532"><a name="p1474103464093532"></a><a name="p1474103464093532"></a>uint32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row1661417868093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1160929139093532"><a name="p1160929139093532"></a><a name="p1160929139093532"></a><a href="WLAN.md#ga2035c840c71a43b43451bfe0213ca04a">changeMtu</a> )(struct <a href="NetDevice.md">NetDevice</a> *netDev, int32_t newMtu)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p347858314093532"><a name="p347858314093532"></a><a name="p347858314093532"></a>int32_t(*&nbsp;</p>
</td>
</tr>
<tr id="row46278435093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p297269441093532"><a name="p297269441093532"></a><a name="p297269441093532"></a><a href="WLAN.md#ga8bb9ea881b1bdabe8c45f721310823b1">specialEtherTypeProcess</a> )(const struct <a href="NetDevice.md">NetDevice</a> *netDev, struct <a href="NetBuf.md">NetBuf</a> *buff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389462291093532"><a name="p1389462291093532"></a><a name="p1389462291093532"></a><a href="WLAN.md#ga9c1d6e7df4468671742cb76f72b67af1">ProcessingResult</a>(*&nbsp;</p>
</td>
</tr>
</tbody>
</table>

