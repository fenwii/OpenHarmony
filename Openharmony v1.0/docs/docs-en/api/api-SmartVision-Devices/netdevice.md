# NetDevice<a name="EN-US_TOPIC_0000001054799609"></a>

## **Overview**<a name="section1139162829093532"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Defines a network device, including the network interface category and name, and network port type. 

**Since:**

1.0

## **Summary**<a name="section156486564093532"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table12031317093532"></a>
<table><thead align="left"><tr id="row931330865093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1962933456093532"><a name="p1962933456093532"></a><a name="p1962933456093532"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p305577916093532"><a name="p305577916093532"></a><a name="p305577916093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1619078052093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2025104788093532"><a name="p2025104788093532"></a><a name="p2025104788093532"></a><a href="wlan.md#ga95102f11976f69a7c700944614fa06b2">netifCateg</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p551626157093532"><a name="p551626157093532"></a><a name="p551626157093532"></a><a href="wlan.md#ga530241881cd17e03f8ae254ef1d9755e">NetIfCategory</a> </p>
</td>
</tr>
<tr id="row372612463093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1620695887093532"><a name="p1620695887093532"></a><a name="p1620695887093532"></a><a href="wlan.md#ga74b1c5d9a04465f4b47b36ece7470aab">name</a> [IFNAMSIZ]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p708739618093532"><a name="p708739618093532"></a><a name="p708739618093532"></a>char </p>
</td>
</tr>
<tr id="row628888796093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p516755335093532"><a name="p516755335093532"></a><a name="p516755335093532"></a><a href="wlan.md#ga4758167363bad30116f4bcdb4cc1ae2a">LinkLayerType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p399644996093532"><a name="p399644996093532"></a><a name="p399644996093532"></a><a href="wlan.md#gad3175955d2e6ef3c4f52da9b509d5b4a">NetLinkType</a> </p>
</td>
</tr>
<tr id="row1633176210093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1630658791093532"><a name="p1630658791093532"></a><a name="p1630658791093532"></a><a href="wlan.md#ga4a20c090f2e28ed317957d4ed5fc28fd">funType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p317899879093532"><a name="p317899879093532"></a><a name="p317899879093532"></a><a href="iftype.md">IfType</a> </p>
</td>
</tr>
<tr id="row1727139928093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2133661506093532"><a name="p2133661506093532"></a><a name="p2133661506093532"></a><a href="wlan.md#gacbe765a13d3de60f6c4f297234444553">macAddr</a> [<a href="wlan.md#gae01dbae885bc8abecb82bd865515c081">MAC_ADDR_SIZE</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1955681565093532"><a name="p1955681565093532"></a><a name="p1955681565093532"></a>char </p>
</td>
</tr>
<tr id="row1567807577093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p383831405093532"><a name="p383831405093532"></a><a name="p383831405093532"></a><a href="wlan.md#ga01a8027b2e16aa30a6da3ee99c0f3890">flags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1109586722093532"><a name="p1109586722093532"></a><a name="p1109586722093532"></a>uint32_t </p>
</td>
</tr>
<tr id="row1409689841093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p502323249093532"><a name="p502323249093532"></a><a name="p502323249093532"></a><a href="wlan.md#ga3c55b245d63ce32ea02f2890fc8e75a8">mtu</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p917171549093532"><a name="p917171549093532"></a><a name="p917171549093532"></a>uint32_t </p>
</td>
</tr>
<tr id="row1957863184093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1014430337093532"><a name="p1014430337093532"></a><a name="p1014430337093532"></a><a href="wlan.md#ga480ec41047ece56996f42b0f72a6e079">watchdogTime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1806711747093532"><a name="p1806711747093532"></a><a name="p1806711747093532"></a>int32_t </p>
</td>
</tr>
<tr id="row1508135844093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p418369785093532"><a name="p418369785093532"></a><a name="p418369785093532"></a><a href="wlan.md#gaf3cfb6012fad954900ccded1305e0e73">lastRxTime</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1686651724093532"><a name="p1686651724093532"></a><a name="p1686651724093532"></a>uint32_t </p>
</td>
</tr>
<tr id="row257995150093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p452904098093532"><a name="p452904098093532"></a><a name="p452904098093532"></a><a href="wlan.md#ga585cec837551180e542b29d263dd585c">hardHeaderLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p168869627093532"><a name="p168869627093532"></a><a name="p168869627093532"></a>uint16_t </p>
</td>
</tr>
<tr id="row832864796093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1708798159093532"><a name="p1708798159093532"></a><a name="p1708798159093532"></a><a href="wlan.md#ga9241a41c1cb62a68e3d8c93b9dfe4790">neededHeadRoom</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1561815192093532"><a name="p1561815192093532"></a><a name="p1561815192093532"></a>uint16_t </p>
</td>
</tr>
<tr id="row1184709704093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p843895413093532"><a name="p843895413093532"></a><a name="p843895413093532"></a><a href="wlan.md#ga3ad6638d07aef608b8d5e4b20a478e03">neededTailRoom</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p211251916093532"><a name="p211251916093532"></a><a name="p211251916093532"></a>uint16_t </p>
</td>
</tr>
<tr id="row589026467093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p711554617093532"><a name="p711554617093532"></a><a name="p711554617093532"></a><a href="wlan.md#gafc2646cdc533135a303ca91bf9ebe7ec">addrLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1645613354093532"><a name="p1645613354093532"></a><a name="p1645613354093532"></a>uint8_t </p>
</td>
</tr>
<tr id="row70825049093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p773637072093532"><a name="p773637072093532"></a><a name="p773637072093532"></a><a href="wlan.md#gac2b0eefb68664e9458311017ce31275b">mlPriv</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932398256093532"><a name="p1932398256093532"></a><a name="p1932398256093532"></a>void * </p>
</td>
</tr>
<tr id="row1834264500093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1999857490093532"><a name="p1999857490093532"></a><a name="p1999857490093532"></a><a href="wlan.md#ga3d04317fd4d2c8932808d6dd07fedcf4">ieee80211Ptr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1727636207093532"><a name="p1727636207093532"></a><a name="p1727636207093532"></a>struct <a href="wirelessdev.md">WirelessDev</a> * </p>
</td>
</tr>
<tr id="row1147136319093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1332071628093532"><a name="p1332071628093532"></a><a name="p1332071628093532"></a><a href="wlan.md#ga659f5eb4ee2cef37cb93acea357acb75">specialProcPriv</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p821232017093532"><a name="p821232017093532"></a><a name="p821232017093532"></a>void * </p>
</td>
</tr>
<tr id="row1677495516093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390097446093532"><a name="p390097446093532"></a><a name="p390097446093532"></a><a href="wlan.md#gaf154f5a9cbf4d297bc6fc7550ae9a819">netDeviceIf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p721292818093532"><a name="p721292818093532"></a><a name="p721292818093532"></a>struct <a href="netdeviceinterface.md">NetDeviceInterFace</a> * </p>
</td>
</tr>
<tr id="row2042135990093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1214678639093532"><a name="p1214678639093532"></a><a name="p1214678639093532"></a><a href="wlan.md#ga6f725a86ac73ba02449952d3f8fbcff9">owner</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1659957691093532"><a name="p1659957691093532"></a><a name="p1659957691093532"></a>struct <a href="netdevice.md">NetDevice</a> * </p>
</td>
</tr>
<tr id="row284261030093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1456877447093532"><a name="p1456877447093532"></a><a name="p1456877447093532"></a><a href="wlan.md#gafdd796dab998fb2ff695af4d50abdc13">stats</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p533538162093532"><a name="p533538162093532"></a><a name="p533538162093532"></a>struct NetDevStats </p>
</td>
</tr>
</tbody>
</table>

