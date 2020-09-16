# WLAN<a name="ZH-CN_TOPIC_0000001055198080"></a>

## **Overview**<a name="section1032606480084825"></a>

Defines a WLAN module that supports cross-OS migration, component adaptation, and modular assembly and compilation. Driver developers of WLAN vendors can adapt their driver code based on the unified APIs provided by the WLAN module. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1767144108084825"></a>

## Files<a name="files"></a>

<a name="table2033637396084825"></a>
<table><thead align="left"><tr id="row503985669084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p565675641084825"><a name="p565675641084825"></a><a name="p565675641084825"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p901925798084825"><a name="p901925798084825"></a><a name="p901925798084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1246580312084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p425952148084825"><a name="p425952148084825"></a><a name="p425952148084825"></a><a href="hdf_netbuf-h.md">hdf_netbuf.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p338275140084825"><a name="p338275140084825"></a><a name="p338275140084825"></a>Declares network data buffers and provides APIs for operating buffer queues. </p>
</td>
</tr>
<tr id="row1226059148084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p516785273084825"><a name="p516785273084825"></a><a name="p516785273084825"></a><a href="hdf_wifi_event-h.md">hdf_wifi_event.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p87309713084825"><a name="p87309713084825"></a><a name="p87309713084825"></a>Declares WLAN driver events. </p>
</td>
</tr>
<tr id="row1811963044084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079165498084825"><a name="p2079165498084825"></a><a name="p2079165498084825"></a><a href="hdf_wifi_product-h.md">hdf_wifi_product.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1694101134084825"><a name="p1694101134084825"></a><a name="p1694101134084825"></a>Declares the data structure of the WLAN module. </p>
</td>
</tr>
<tr id="row1447286912084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p526496068084825"><a name="p526496068084825"></a><a name="p526496068084825"></a><a href="net_device-h.md">net_device.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p569848373084825"><a name="p569848373084825"></a><a name="p569848373084825"></a>Defines WLAN network device interfaces. </p>
</td>
</tr>
<tr id="row327338862084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1254589233084825"><a name="p1254589233084825"></a><a name="p1254589233084825"></a><a href="wifi_inc-h.md">wifi_inc.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1712395036084825"><a name="p1712395036084825"></a><a name="p1712395036084825"></a>Describes the data structure of WLAN features and bus. </p>
</td>
</tr>
<tr id="row3243132084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806406566084825"><a name="p806406566084825"></a><a name="p806406566084825"></a><a href="wifi_mac80211_ops-h.md">wifi_mac80211_ops.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p50085401084825"><a name="p50085401084825"></a><a name="p50085401084825"></a>Declares Media Access Control (MAC) APIs and functions related to control flows. </p>
</td>
</tr>
<tr id="row1137640641084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p676930249084825"><a name="p676930249084825"></a><a name="p676930249084825"></a><a href="wifi_module-h.md">wifi_module.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2062258791084825"><a name="p2062258791084825"></a><a name="p2062258791084825"></a>Provides features of the WLAN module and functions to create and delete modules. </p>
</td>
</tr>
<tr id="row1449556058084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1181653173084825"><a name="p1181653173084825"></a><a name="p1181653173084825"></a><a href="wifi_module_config-h.md">wifi_module_config.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p786785951084825"><a name="p786785951084825"></a><a name="p786785951084825"></a>Declares the WLAN module configuration. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1268756168084825"></a>
<table><thead align="left"><tr id="row96394776084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1995819568084825"><a name="p1995819568084825"></a><a name="p1995819568084825"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1294674251084825"><a name="p1294674251084825"></a><a name="p1294674251084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row212819498084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p861012324084825"><a name="p861012324084825"></a><a name="p861012324084825"></a><a href="NetBuf.md">NetBuf</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p255244355084825"><a name="p255244355084825"></a><a name="p255244355084825"></a>Records and saves a network data buffer. </p>
</td>
</tr>
<tr id="row1002140109084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1272967513084825"><a name="p1272967513084825"></a><a name="p1272967513084825"></a><a href="NetBufQueue.md">NetBufQueue</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554356259084825"><a name="p1554356259084825"></a><a name="p1554356259084825"></a>Indicates the queues for storing network data. </p>
</td>
</tr>
<tr id="row355201972084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p712913285084825"><a name="p712913285084825"></a><a name="p712913285084825"></a><a href="RateInfo.md">RateInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1414291346084825"><a name="p1414291346084825"></a><a name="p1414291346084825"></a>Defines the rate information received or sent over WLAN. </p>
</td>
</tr>
<tr id="row2038111466084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1838483629084825"><a name="p1838483629084825"></a><a name="p1838483629084825"></a><a href="StaBssParameters.md">StaBssParameters</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1120744470084825"><a name="p1120744470084825"></a><a name="p1120744470084825"></a>Defines parameters related to the WLAN module that works in station mode. </p>
</td>
</tr>
<tr id="row232540377084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1705002008084825"><a name="p1705002008084825"></a><a name="p1705002008084825"></a><a href="StaFlagUpdate.md">StaFlagUpdate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p675250434084825"><a name="p675250434084825"></a><a name="p675250434084825"></a>Defines the update of the <strong id="b1870933312084825"><a name="b1870933312084825"></a><a name="b1870933312084825"></a>Sta</strong> flag. </p>
</td>
</tr>
<tr id="row358904021084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p449499818084825"><a name="p449499818084825"></a><a name="p449499818084825"></a><a href="StationInfo.md">StationInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p382414611084825"><a name="p382414611084825"></a><a name="p382414611084825"></a>Defines station information. </p>
</td>
</tr>
<tr id="row30068194084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1396224126084825"><a name="p1396224126084825"></a><a name="p1396224126084825"></a><a href="Auth.md">Auth</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1298373188084825"><a name="p1298373188084825"></a><a name="p1298373188084825"></a>Defines authentication information. </p>
</td>
</tr>
<tr id="row161578841084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1895275840084825"><a name="p1895275840084825"></a><a name="p1895275840084825"></a><a href="Deauth.md">Deauth</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367878265084825"><a name="p1367878265084825"></a><a name="p1367878265084825"></a>Defines deauthentication information. </p>
</td>
</tr>
<tr id="row486116409084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1551069028084825"><a name="p1551069028084825"></a><a name="p1551069028084825"></a><a href="AssocReq.md">AssocReq</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2141212939084825"><a name="p2141212939084825"></a><a name="p2141212939084825"></a>Defines station association request. </p>
</td>
</tr>
<tr id="row1778076331084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1409842297084825"><a name="p1409842297084825"></a><a name="p1409842297084825"></a><a href="AssocResp.md">AssocResp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1449441836084825"><a name="p1449441836084825"></a><a name="p1449441836084825"></a>Defines station association response. </p>
</td>
</tr>
<tr id="row150193824084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2110108327084825"><a name="p2110108327084825"></a><a name="p2110108327084825"></a><a href="ReassocReq.md">ReassocReq</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p660680254084825"><a name="p660680254084825"></a><a name="p660680254084825"></a>Defines station reassociation request. </p>
</td>
</tr>
<tr id="row827685477084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1730514929084825"><a name="p1730514929084825"></a><a name="p1730514929084825"></a><a href="ReassocResp.md">ReassocResp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p654464115084825"><a name="p654464115084825"></a><a name="p654464115084825"></a>Defines station reassociation response. </p>
</td>
</tr>
<tr id="row1529259583084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p443931171084825"><a name="p443931171084825"></a><a name="p443931171084825"></a><a href="Disassoc.md">Disassoc</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1858579490084825"><a name="p1858579490084825"></a><a name="p1858579490084825"></a>Defines station disconnection. </p>
</td>
</tr>
<tr id="row1246179105084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106424248084825"><a name="p2106424248084825"></a><a name="p2106424248084825"></a><a href="Beacon.md">Beacon</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1874031729084825"><a name="p1874031729084825"></a><a name="p1874031729084825"></a>Defines the update of the <strong id="b1951055288084825"><a name="b1951055288084825"></a><a name="b1951055288084825"></a>Sta</strong> flag. </p>
</td>
</tr>
<tr id="row2114733329084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000512309084825"><a name="p1000512309084825"></a><a name="p1000512309084825"></a><a href="ProbeResp.md">ProbeResp</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p882198080084825"><a name="p882198080084825"></a><a name="p882198080084825"></a>Defines scanning response. </p>
</td>
</tr>
<tr id="row1874089248084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1647764370084825"><a name="p1647764370084825"></a><a name="p1647764370084825"></a><a href="Ieee80211Mgmt.md">Ieee80211Mgmt</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1283292298084825"><a name="p1283292298084825"></a><a name="p1283292298084825"></a>Defines management frame information. </p>
</td>
</tr>
<tr id="row66158235084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p745997471084825"><a name="p745997471084825"></a><a name="p745997471084825"></a><a href="ScannedBssInfo.md">ScannedBssInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p79642845084825"><a name="p79642845084825"></a><a name="p79642845084825"></a>Represents the scanned BSS information. </p>
</td>
</tr>
<tr id="row1628479855084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217747622084825"><a name="p1217747622084825"></a><a name="p1217747622084825"></a><a href="ConnetResult.md">ConnetResult</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p804777495084825"><a name="p804777495084825"></a><a name="p804777495084825"></a>Defines association results. </p>
</td>
</tr>
<tr id="row898260939084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1178626389084825"><a name="p1178626389084825"></a><a name="p1178626389084825"></a><a href="HdfWifiProductData.md">HdfWifiProductData</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1104957349084825"><a name="p1104957349084825"></a><a name="p1104957349084825"></a>Defines the WLAN module. </p>
</td>
</tr>
<tr id="row1025866528084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p101287128084825"><a name="p101287128084825"></a><a name="p101287128084825"></a><a href="EtherHeader.md">EtherHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1899060866084825"><a name="p1899060866084825"></a><a name="p1899060866084825"></a>Defines the Ethernet header information of a data frame, including the destination address, source address, and Ethernet type. </p>
</td>
</tr>
<tr id="row871490678084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1376954759084825"><a name="p1376954759084825"></a><a name="p1376954759084825"></a><a href="IpHeader.md">IpHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1863867095084825"><a name="p1863867095084825"></a><a name="p1863867095084825"></a>Defines the IP header information of a data frame, including the version number, service type, and total length. </p>
</td>
</tr>
<tr id="row668168082084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p781441274084825"><a name="p781441274084825"></a><a name="p781441274084825"></a><a href="UdpHeader.md">UdpHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1402792905084825"><a name="p1402792905084825"></a><a name="p1402792905084825"></a>Defines the UDP header information of a data frame, including the source port number and destination port number. </p>
</td>
</tr>
<tr id="row1970387563084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1728312990084825"><a name="p1728312990084825"></a><a name="p1728312990084825"></a><a href="TcpHeader.md">TcpHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1713842074084825"><a name="p1713842074084825"></a><a name="p1713842074084825"></a>Defines the TCP header information of a data frame, including the source port number and destination port number. </p>
</td>
</tr>
<tr id="row1279929409084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1225973853084825"><a name="p1225973853084825"></a><a name="p1225973853084825"></a><a href="IpV4Addr.md">IpV4Addr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p22354337084825"><a name="p22354337084825"></a><a name="p22354337084825"></a>Defines an IPv4 address. </p>
</td>
</tr>
<tr id="row877801147084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p447696599084825"><a name="p447696599084825"></a><a name="p447696599084825"></a><a href="NetDevNotify.md">NetDevNotify</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p882971432084825"><a name="p882971432084825"></a><a name="p882971432084825"></a>Defines a network device notification, including an IP address and the notification type. </p>
</td>
</tr>
<tr id="row120510233084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p781444153084825"><a name="p781444153084825"></a><a name="p781444153084825"></a><a href="IfType.md">IfType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p263774232084825"><a name="p263774232084825"></a><a name="p263774232084825"></a>Defines the network port type, for example, the WLAN network port. </p>
</td>
</tr>
<tr id="row1111167550084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1876675287084825"><a name="p1876675287084825"></a><a name="p1876675287084825"></a><a href="IfReq.md">IfReq</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1684848408084825"><a name="p1684848408084825"></a><a name="p1684848408084825"></a>Defines ioctrl data. </p>
</td>
</tr>
<tr id="row2091963878084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p712169118084825"><a name="p712169118084825"></a><a name="p712169118084825"></a><a href="NetDevice.md">NetDevice</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1585232035084825"><a name="p1585232035084825"></a><a name="p1585232035084825"></a>Defines a network device, including the network interface category and name, and network port type. </p>
</td>
</tr>
<tr id="row194389778084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1625300184084825"><a name="p1625300184084825"></a><a name="p1625300184084825"></a><a href="NetDeviceInterFace.md">NetDeviceInterFace</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p307643204084825"><a name="p307643204084825"></a><a name="p307643204084825"></a>Defines interfaces that need to be implemented externally by network devices, including initializing, opening, and closing a network device. </p>
</td>
</tr>
<tr id="row144099480084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1585731265084825"><a name="p1585731265084825"></a><a name="p1585731265084825"></a><a href="KeyParams.md">KeyParams</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p727022085084825"><a name="p727022085084825"></a><a name="p727022085084825"></a>Describes a key. </p>
</td>
</tr>
<tr id="row1944178538084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2090018302084825"><a name="p2090018302084825"></a><a name="p2090018302084825"></a><a href="Ieee80211Channel.md">Ieee80211Channel</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p447605481084825"><a name="p447605481084825"></a><a name="p447605481084825"></a>Describes a communication channel. </p>
</td>
</tr>
<tr id="row1600774618084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898470312084825"><a name="p1898470312084825"></a><a name="p1898470312084825"></a><a href="Ieee80211Rate.md">Ieee80211Rate</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1456842051084825"><a name="p1456842051084825"></a><a name="p1456842051084825"></a>Describes the IEEE 802.11 rate. </p>
</td>
</tr>
<tr id="row2096514646084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2024039879084825"><a name="p2024039879084825"></a><a name="p2024039879084825"></a><a href="Ieee80211McsInfo.md">Ieee80211McsInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p234873617084825"><a name="p234873617084825"></a><a name="p234873617084825"></a>Describes IEEE 802.11 Modulation and Coding Scheme (MCS) information. </p>
</td>
</tr>
<tr id="row317026423084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1200351970084825"><a name="p1200351970084825"></a><a name="p1200351970084825"></a><a href="Ieee80211StaHtCap.md">Ieee80211StaHtCap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p46678365084825"><a name="p46678365084825"></a><a name="p46678365084825"></a>Describes the IEEE 802.11 high-throughput (HT) capability. </p>
</td>
</tr>
<tr id="row1178819148084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2140427858084825"><a name="p2140427858084825"></a><a name="p2140427858084825"></a><a href="Ieee80211SupportedBand.md">Ieee80211SupportedBand</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1194651240084825"><a name="p1194651240084825"></a><a name="p1194651240084825"></a>Describes IEEE 802.11 band information. </p>
</td>
</tr>
<tr id="row1994091302084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1958513064084825"><a name="p1958513064084825"></a><a name="p1958513064084825"></a><a href="Wiphy.md">Wiphy</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p298035621084825"><a name="p298035621084825"></a><a name="p298035621084825"></a>Describes a wiphy device. </p>
</td>
</tr>
<tr id="row1108826596084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1529702534084825"><a name="p1529702534084825"></a><a name="p1529702534084825"></a><a href="WifiSsid.md">WifiSsid</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p187195053084825"><a name="p187195053084825"></a><a name="p187195053084825"></a>Describes an SSID. </p>
</td>
</tr>
<tr id="row1989571727084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p251902089084825"><a name="p251902089084825"></a><a name="p251902089084825"></a><a href="ChannelDef.md">ChannelDef</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1331425354084825"><a name="p1331425354084825"></a><a name="p1331425354084825"></a>Describes a communication channel. </p>
</td>
</tr>
<tr id="row859895123084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p147373983084825"><a name="p147373983084825"></a><a name="p147373983084825"></a><a href="WirelessDev.md">WirelessDev</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p111264133084825"><a name="p111264133084825"></a><a name="p111264133084825"></a>Describes a wireless device. </p>
</td>
</tr>
<tr id="row1181686275084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1086670083084825"><a name="p1086670083084825"></a><a name="p1086670083084825"></a><a href="WifiScanRequest.md">WifiScanRequest</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p218356774084825"><a name="p218356774084825"></a><a name="p218356774084825"></a>Describes scan request parameters. </p>
</td>
</tr>
<tr id="row1053325197084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1769820519084825"><a name="p1769820519084825"></a><a name="p1769820519084825"></a><a href="CryptoSettings.md">CryptoSettings</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989510143084825"><a name="p1989510143084825"></a><a name="p1989510143084825"></a>Describes cryptography settings. </p>
</td>
</tr>
<tr id="row1088839609084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1873881274084825"><a name="p1873881274084825"></a><a name="p1873881274084825"></a><a href="MacAddress.md">MacAddress</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1981859363084825"><a name="p1981859363084825"></a><a name="p1981859363084825"></a>Describes the device MAC address. </p>
</td>
</tr>
<tr id="row1221562012084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1054461992084825"><a name="p1054461992084825"></a><a name="p1054461992084825"></a><a href="WifiConnectParams.md">WifiConnectParams</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1113261643084825"><a name="p1113261643084825"></a><a name="p1113261643084825"></a>Describes parameters for a connection request. </p>
</td>
</tr>
<tr id="row137988507084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1045478784084825"><a name="p1045478784084825"></a><a name="p1045478784084825"></a><a href="VifParams.md">VifParams</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2139403840084825"><a name="p2139403840084825"></a><a name="p2139403840084825"></a>Describes virtual API parameters. </p>
</td>
</tr>
<tr id="row853978345084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p833555601084825"><a name="p833555601084825"></a><a name="p833555601084825"></a><a href="StationDelParameters.md">StationDelParameters</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1416500048084825"><a name="p1416500048084825"></a><a name="p1416500048084825"></a>Describes parameters for canceling a connection. </p>
</td>
</tr>
<tr id="row1620679454084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000734535084825"><a name="p1000734535084825"></a><a name="p1000734535084825"></a><a href="MacConfigParam.md">MacConfigParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p694462105084825"><a name="p694462105084825"></a><a name="p694462105084825"></a>Describes MAC configuration parameters. </p>
</td>
</tr>
<tr id="row1824391002084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p608695004084825"><a name="p608695004084825"></a><a name="p608695004084825"></a><a href="Mac80211DisconnectParam.md">Mac80211DisconnectParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1934225993084825"><a name="p1934225993084825"></a><a name="p1934225993084825"></a>Describes disconnection parameters. </p>
</td>
</tr>
<tr id="row1400097536084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p511854530084825"><a name="p511854530084825"></a><a name="p511854530084825"></a><a href="Mac80211Ssids.md">Mac80211Ssids</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926307390084825"><a name="p926307390084825"></a><a name="p926307390084825"></a>Describes SSIDs. </p>
</td>
</tr>
<tr id="row1305605301084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183704669084825"><a name="p1183704669084825"></a><a name="p1183704669084825"></a><a href="Mac80211beaconParam.md">Mac80211beaconParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p965576446084825"><a name="p965576446084825"></a><a name="p965576446084825"></a>Describes beacon parameters. </p>
</td>
</tr>
<tr id="row1256233487084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1458584659084825"><a name="p1458584659084825"></a><a name="p1458584659084825"></a><a href="WifiMac80211Ops.md">WifiMac80211Ops</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1723910314084825"><a name="p1723910314084825"></a><a name="p1723910314084825"></a>Describes MAC-layer control APIs that need to be implemented by the driver. </p>
</td>
</tr>
<tr id="row1578245617084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p615208437084825"><a name="p615208437084825"></a><a name="p615208437084825"></a><a href="WifiModuleIface.md">WifiModuleIface</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1318865326084825"><a name="p1318865326084825"></a><a name="p1318865326084825"></a>Defines WLAN module APIs. </p>
</td>
</tr>
<tr id="row468786702084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p844776319084825"><a name="p844776319084825"></a><a name="p844776319084825"></a><a href="WifiModule.md">WifiModule</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1421861050084825"><a name="p1421861050084825"></a><a name="p1421861050084825"></a>Defines the WLAN module. </p>
</td>
</tr>
<tr id="row1414669227084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1006550063084825"><a name="p1006550063084825"></a><a name="p1006550063084825"></a><a href="WifiFeature.md">WifiFeature</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1704694282084825"><a name="p1704694282084825"></a><a name="p1704694282084825"></a>Defines a WLAN feature. </p>
</td>
</tr>
<tr id="row1906634323084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p826378917084825"><a name="p826378917084825"></a><a name="p826378917084825"></a><a href="WifiFeatureList.md">WifiFeatureList</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388428483084825"><a name="p388428483084825"></a><a name="p388428483084825"></a>Defines the WLAN feature list. </p>
</td>
</tr>
<tr id="row1142583386084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p878299781084825"><a name="p878299781084825"></a><a name="p878299781084825"></a><a href="HdfWifiChipData.md">HdfWifiChipData</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p437805873084825"><a name="p437805873084825"></a><a name="p437805873084825"></a>Defines a WLAN chip. </p>
</td>
</tr>
<tr id="row1947274267084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p834195660084825"><a name="p834195660084825"></a><a name="p834195660084825"></a><a href="WifiModuleConfig.md">WifiModuleConfig</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2143482278084825"><a name="p2143482278084825"></a><a name="p2143482278084825"></a>Defines the WLAN module configuration. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table1747060861084825"></a>
<table><thead align="left"><tr id="row1896045722084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1611090378084825"><a name="p1611090378084825"></a><a name="p1611090378084825"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p986202139084825"><a name="p986202139084825"></a><a name="p986202139084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1754488081084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p679246474084825"><a name="p679246474084825"></a><a name="p679246474084825"></a><a href="WLAN.md#ga794c035a19a38acc000146a8f9a4ec80">MAX_NETBUF_RESEVER_SIZE</a>&nbsp;&nbsp;&nbsp;68</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1831397951084825"><a name="p1831397951084825"></a><a name="p1831397951084825"></a>Defines the reserved field of a network data buffer used to store private information. </p>
</td>
</tr>
<tr id="row418908754084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p929475971084825"><a name="p929475971084825"></a><a name="p929475971084825"></a><em id="gae01dbae885bc8abecb82bd865515c081"><a name="gae01dbae885bc8abecb82bd865515c081"></a><a name="gae01dbae885bc8abecb82bd865515c081"></a></em>MAC_ADDR_SIZE &nbsp;&nbsp;&nbsp;6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1180149781084825"><a name="p1180149781084825"></a><a name="p1180149781084825"></a>Indicates a 6-byte MAC address. </p>
</td>
</tr>
<tr id="row264601602084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220017523084825"><a name="p1220017523084825"></a><a name="p1220017523084825"></a><em id="gad9c939a90358c2cb6b788af7b84821a1"><a name="gad9c939a90358c2cb6b788af7b84821a1"></a><a name="gad9c939a90358c2cb6b788af7b84821a1"></a></em>NET_DEVICE_IFF_RUNNING &nbsp;&nbsp;&nbsp;IFF_RUNNING</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p190254371084825"><a name="p190254371084825"></a><a name="p190254371084825"></a>Indicates that the network port is working. </p>
</td>
</tr>
<tr id="row448754916084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p873334436084825"><a name="p873334436084825"></a><a name="p873334436084825"></a><em id="ga74e41a940b9c245f2bc8eaba01d4cee2"><a name="ga74e41a940b9c245f2bc8eaba01d4cee2"></a><a name="ga74e41a940b9c245f2bc8eaba01d4cee2"></a></em>ETHER_TYPE_RARP &nbsp;&nbsp;&nbsp;0x8035</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p924472380084825"><a name="p924472380084825"></a><a name="p924472380084825"></a>Indicates Reverse Address Resolution Protocol (RARP). </p>
</td>
</tr>
<tr id="row480373488084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p553476701084825"><a name="p553476701084825"></a><a name="p553476701084825"></a><em id="ga3bc75b7ed75e7da0abf818f0f1a769d3"><a name="ga3bc75b7ed75e7da0abf818f0f1a769d3"></a><a name="ga3bc75b7ed75e7da0abf818f0f1a769d3"></a></em>ETHER_TYPE_PAE &nbsp;&nbsp;&nbsp;0x888e</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p943634965084825"><a name="p943634965084825"></a><a name="p943634965084825"></a>Indicates Port Access Entity (PAE). </p>
</td>
</tr>
<tr id="row129919064084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1873759889084825"><a name="p1873759889084825"></a><a name="p1873759889084825"></a><em id="ga61a8e2c9705e0c7000235c60639f3f97"><a name="ga61a8e2c9705e0c7000235c60639f3f97"></a><a name="ga61a8e2c9705e0c7000235c60639f3f97"></a></em>ETHER_TYPE_IP &nbsp;&nbsp;&nbsp;0x0800</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p324919198084825"><a name="p324919198084825"></a><a name="p324919198084825"></a>Indicates Internet Protocol (IP). </p>
</td>
</tr>
<tr id="row628193136084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1085731795084825"><a name="p1085731795084825"></a><a name="p1085731795084825"></a><em id="ga4759f448b5669a1f33ff7d6912a1b131"><a name="ga4759f448b5669a1f33ff7d6912a1b131"></a><a name="ga4759f448b5669a1f33ff7d6912a1b131"></a></em>ETHER_TYPE_AARP &nbsp;&nbsp;&nbsp;0x80f3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926315002084825"><a name="p926315002084825"></a><a name="p926315002084825"></a>Indicates AppleTalk Address Resolution Protocol (AARP). </p>
</td>
</tr>
<tr id="row951171859084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p893279091084825"><a name="p893279091084825"></a><a name="p893279091084825"></a><em id="gaa0b348d7d0f58adb49e152c79b93b519"><a name="gaa0b348d7d0f58adb49e152c79b93b519"></a><a name="gaa0b348d7d0f58adb49e152c79b93b519"></a></em>ETHER_TYPE_IPX &nbsp;&nbsp;&nbsp;0x8137</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p329024118084825"><a name="p329024118084825"></a><a name="p329024118084825"></a>Indicates Internetwork Packet Exchange (IPX). </p>
</td>
</tr>
<tr id="row1141665186084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p303672876084825"><a name="p303672876084825"></a><a name="p303672876084825"></a><em id="ga3f5d778e8eb1a7ad731921a460e6c1dd"><a name="ga3f5d778e8eb1a7ad731921a460e6c1dd"></a><a name="ga3f5d778e8eb1a7ad731921a460e6c1dd"></a></em>ETHER_TYPE_ARP &nbsp;&nbsp;&nbsp;0x0806</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1865888183084825"><a name="p1865888183084825"></a><a name="p1865888183084825"></a>Indicates Address Resolution Protocol (ARP). </p>
</td>
</tr>
<tr id="row2029661057084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p438873412084825"><a name="p438873412084825"></a><a name="p438873412084825"></a><em id="gadd8fcb263b0d4f3e9c09aafe4c6b64e0"><a name="gadd8fcb263b0d4f3e9c09aafe4c6b64e0"></a><a name="gadd8fcb263b0d4f3e9c09aafe4c6b64e0"></a></em>ETHER_TYPE_IPV6 &nbsp;&nbsp;&nbsp;0x86dd</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p354509993084825"><a name="p354509993084825"></a><a name="p354509993084825"></a>Indicates Internet Protocol version 6 (IPv6). </p>
</td>
</tr>
<tr id="row1088256224084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1908765240084825"><a name="p1908765240084825"></a><a name="p1908765240084825"></a><em id="ga0418380e708e716910958ed2aab3921d"><a name="ga0418380e708e716910958ed2aab3921d"></a><a name="ga0418380e708e716910958ed2aab3921d"></a></em>ETHER_TYPE_TDLS &nbsp;&nbsp;&nbsp;0x890d</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521165161084825"><a name="p1521165161084825"></a><a name="p1521165161084825"></a>Indicates Tunneled Direct Link Setup (TDLS). </p>
</td>
</tr>
<tr id="row2047901319084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1460099035084825"><a name="p1460099035084825"></a><a name="p1460099035084825"></a><em id="gaaaa516211cec2b61e3717c5fec36952f"><a name="gaaaa516211cec2b61e3717c5fec36952f"></a><a name="gaaaa516211cec2b61e3717c5fec36952f"></a></em>ETHER_TYPE_VLAN &nbsp;&nbsp;&nbsp;0x8100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1598962562084825"><a name="p1598962562084825"></a><a name="p1598962562084825"></a>Indicates Virtual Local Area Network (VLAN). </p>
</td>
</tr>
<tr id="row1265287238084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p133333133084825"><a name="p133333133084825"></a><a name="p133333133084825"></a><em id="ga89fb6635bc0c9eab11de63ec141938a6"><a name="ga89fb6635bc0c9eab11de63ec141938a6"></a><a name="ga89fb6635bc0c9eab11de63ec141938a6"></a></em>ETHER_TYPE_WAI &nbsp;&nbsp;&nbsp;0x88b4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2039125272084825"><a name="p2039125272084825"></a><a name="p2039125272084825"></a>Indicates WLAN Authentication and Privacy Infrastructure (WAPI). </p>
</td>
</tr>
<tr id="row1210336789084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1935895335084825"><a name="p1935895335084825"></a><a name="p1935895335084825"></a><em id="ga7da55985d58df9fac85217e1195d4b7c"><a name="ga7da55985d58df9fac85217e1195d4b7c"></a><a name="ga7da55985d58df9fac85217e1195d4b7c"></a></em>ETHER_LLTD_TYPE &nbsp;&nbsp;&nbsp;0x88D9</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1461202115084825"><a name="p1461202115084825"></a><a name="p1461202115084825"></a>Indicates Link Layer Topology Discovery (LLTD). </p>
</td>
</tr>
<tr id="row1246171026084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p832217775084825"><a name="p832217775084825"></a><a name="p832217775084825"></a><em id="ga0fb3b00b4300fcbd562e07d5f91aaca0"><a name="ga0fb3b00b4300fcbd562e07d5f91aaca0"></a><a name="ga0fb3b00b4300fcbd562e07d5f91aaca0"></a></em>ETHER_ONE_X_TYPE &nbsp;&nbsp;&nbsp;0x888E</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519524156084825"><a name="p519524156084825"></a><a name="p519524156084825"></a>Indicates 802.1x network port authentication. </p>
</td>
</tr>
<tr id="row563687675084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p522023922084825"><a name="p522023922084825"></a><a name="p522023922084825"></a><em id="gaefd300f6277931e053c899367ad96536"><a name="gaefd300f6277931e053c899367ad96536"></a><a name="gaefd300f6277931e053c899367ad96536"></a></em>ETHER_TUNNEL_TYPE &nbsp;&nbsp;&nbsp;0x88bd</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1773863815084825"><a name="p1773863815084825"></a><a name="p1773863815084825"></a>Indicates a tunnel protocol. </p>
</td>
</tr>
<tr id="row920058407084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911731707084825"><a name="p1911731707084825"></a><a name="p1911731707084825"></a><em id="ga70914271e18c471460d1d00cec8af522"><a name="ga70914271e18c471460d1d00cec8af522"></a><a name="ga70914271e18c471460d1d00cec8af522"></a></em>ETHER_TYPE_PPP_DISC &nbsp;&nbsp;&nbsp;0x8863</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1575159326084825"><a name="p1575159326084825"></a><a name="p1575159326084825"></a>Indicates the point-to-point discovery type. </p>
</td>
</tr>
<tr id="row1780766758084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1192074947084825"><a name="p1192074947084825"></a><a name="p1192074947084825"></a><em id="gaf4b193dda19de66eba7a99b64b3a0c6c"><a name="gaf4b193dda19de66eba7a99b64b3a0c6c"></a><a name="gaf4b193dda19de66eba7a99b64b3a0c6c"></a></em>ETHER_TYPE_PPP_SES &nbsp;&nbsp;&nbsp;0x8864</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p608504659084825"><a name="p608504659084825"></a><a name="p608504659084825"></a>Indicates the point-to-point session discovery type. </p>
</td>
</tr>
<tr id="row12488223084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p673410045084825"><a name="p673410045084825"></a><a name="p673410045084825"></a><em id="ga6fca23e8bd12854706021a45fe3cd352"><a name="ga6fca23e8bd12854706021a45fe3cd352"></a><a name="ga6fca23e8bd12854706021a45fe3cd352"></a></em>ETHER_TYPE_6LO &nbsp;&nbsp;&nbsp;0xa0ed</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1149185533084825"><a name="p1149185533084825"></a><a name="p1149185533084825"></a>Indicates IPv6 over Low Power Wireless Personal Area Networks (6LoWPANs). </p>
</td>
</tr>
<tr id="row1703378956084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p696839313084825"><a name="p696839313084825"></a><a name="p696839313084825"></a><em id="ga96b31b1ec02746766191916559cec530"><a name="ga96b31b1ec02746766191916559cec530"></a><a name="ga96b31b1ec02746766191916559cec530"></a></em>TCP_PROTOCAL &nbsp;&nbsp;&nbsp;6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p597921816084825"><a name="p597921816084825"></a><a name="p597921816084825"></a>Indicates the Transmission Control Protocol (TCP). </p>
</td>
</tr>
<tr id="row163707271084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1932750946084825"><a name="p1932750946084825"></a><a name="p1932750946084825"></a><em id="ga06cdba6ef1f4bc477016c6bbae7ce444"><a name="ga06cdba6ef1f4bc477016c6bbae7ce444"></a><a name="ga06cdba6ef1f4bc477016c6bbae7ce444"></a></em>UDP_PROTOCAL &nbsp;&nbsp;&nbsp;17</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1515617496084825"><a name="p1515617496084825"></a><a name="p1515617496084825"></a>Indicates the User Datagram Protocol (UDP). </p>
</td>
</tr>
<tr id="row48736991084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p748881441084825"><a name="p748881441084825"></a><a name="p748881441084825"></a><em id="gab7ea98963ef9a6aecac843b0ea6bbcee"><a name="gab7ea98963ef9a6aecac843b0ea6bbcee"></a><a name="gab7ea98963ef9a6aecac843b0ea6bbcee"></a></em>IP_PRI_SHIFT &nbsp;&nbsp;&nbsp;5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p302420411084825"><a name="p302420411084825"></a><a name="p302420411084825"></a>Indicates the shift in the priority for an IP address. </p>
</td>
</tr>
<tr id="row1523630777084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1521608539084825"><a name="p1521608539084825"></a><a name="p1521608539084825"></a><em id="ga2db7b9e1310a372d11d568e34958e158"><a name="ga2db7b9e1310a372d11d568e34958e158"></a><a name="ga2db7b9e1310a372d11d568e34958e158"></a></em>DHCP_UDP_SRC_PORT &nbsp;&nbsp;&nbsp;68</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926781059084825"><a name="p926781059084825"></a><a name="p926781059084825"></a>Indicates the source port number of DHCP. </p>
</td>
</tr>
<tr id="row635976832084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p98030645084825"><a name="p98030645084825"></a><a name="p98030645084825"></a><em id="gad92d590d45b6f76db61dd87fed7fa770"><a name="gad92d590d45b6f76db61dd87fed7fa770"></a><a name="gad92d590d45b6f76db61dd87fed7fa770"></a></em>DHCP_UDP_DES_PORT &nbsp;&nbsp;&nbsp;67</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p235246273084825"><a name="p235246273084825"></a><a name="p235246273084825"></a>Indicates the destination port number of DHCP. </p>
</td>
</tr>
<tr id="row736791689084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2014520396084825"><a name="p2014520396084825"></a><a name="p2014520396084825"></a><a href="WLAN.md#gaf460a45a5e365279ca6bc5b3e8750542">MAX_WIFI_COMPONENT_NAME_LEN</a>&nbsp;&nbsp;&nbsp;10</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p896826241084825"><a name="p896826241084825"></a><a name="p896826241084825"></a>Indicates the length of the name of a WLAN module or feature. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table204932320084825"></a>
<table><thead align="left"><tr id="row751548985084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p960036845084825"><a name="p960036845084825"></a><a name="p960036845084825"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p101136667084825"><a name="p101136667084825"></a><a name="p101136667084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1383288514084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1719399686084825"><a name="p1719399686084825"></a><a name="p1719399686084825"></a><a href="WLAN.md#gac26e4b0cda623f27420f9ce77befbb1f">NetDevice</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1594619058084825"><a name="p1594619058084825"></a><a name="p1594619058084825"></a>typedef struct <a href="NetDevice.md">NetDevice</a>&nbsp;</p>
<p id="p69312251084825"><a name="p69312251084825"></a><a name="p69312251084825"></a>Defines a network device, including the network interface category and name, and network port type. </p>
</td>
</tr>
<tr id="row95495678084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p56447407084825"><a name="p56447407084825"></a><a name="p56447407084825"></a><a href="WLAN.md#ga3e8945c521d2392cb775494570c560b3">WifiConnectParams</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1155000181084825"><a name="p1155000181084825"></a><a name="p1155000181084825"></a>typedef struct <a href="WifiConnectParams.md">WifiConnectParams</a>&nbsp;</p>
<p id="p24505260084825"><a name="p24505260084825"></a><a name="p24505260084825"></a>Describes parameters for a connection request. </p>
</td>
</tr>
<tr id="row371748914084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p11666924084825"><a name="p11666924084825"></a><a name="p11666924084825"></a><a href="WLAN.md#ga85f7d8a3795887f090e0a6439b1df6e1">Mac80211SetMacParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2128231641084825"><a name="p2128231641084825"></a><a name="p2128231641084825"></a>typedef struct <a href="MacConfigParam.md">MacConfigParam</a>&nbsp;</p>
<p id="p1512653855084825"><a name="p1512653855084825"></a><a name="p1512653855084825"></a>Describes MAC configuration parameters. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1164834020084825"></a>
<table><thead align="left"><tr id="row1828622470084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p988478308084825"><a name="p988478308084825"></a><a name="p988478308084825"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1581861060084825"><a name="p1581861060084825"></a><a name="p1581861060084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1024267727084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p936382827084825"><a name="p936382827084825"></a><a name="p936382827084825"></a>{ <a href="WLAN.md#ggae4d5251432e1a9e6803c0240cc492e18a0e4808dd476b314c0fdbf417307f8b92">E_HEAD_BUF</a>, <a href="WLAN.md#ggae4d5251432e1a9e6803c0240cc492e18a4b374b76d2b9bb60c31a1a540369b6d4">E_DATA_BUF</a>, <a href="WLAN.md#ggae4d5251432e1a9e6803c0240cc492e18a316baeacb77ecf28631a76f1dbea872d">E_TAIL_BUF</a>, <a href="WLAN.md#ggae4d5251432e1a9e6803c0240cc492e18aeef2a730ef9f722cfbac0b24998f8e19">MAX_BUF_NUM</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1774701555084825"><a name="p1774701555084825"></a><a name="p1774701555084825"></a>Enumerates the segments of a network data buffer. </p>
</td>
</tr>
<tr id="row433670695084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1040107129084825"><a name="p1040107129084825"></a><a name="p1040107129084825"></a><a href="WLAN.md#gaf3e873b51f0cfa077aca9d33ed7a0960">WifiHmacMgmtStatus</a> { &nbsp;&nbsp;<a href="WLAN.md#ggaf3e873b51f0cfa077aca9d33ed7a0960ad9c7e2f362bd6fcadef189fa2a5d7c63">WIFI_HMAC_MGMT_SUCCESS</a> = 0, <a href="WLAN.md#ggaf3e873b51f0cfa077aca9d33ed7a0960a539c65a358a20b9731fc66fc60ebcbc2">WIFI_HMAC_MGMT_INVALID</a> = 1, <a href="WLAN.md#ggaf3e873b51f0cfa077aca9d33ed7a0960ad1731acef8ddb8c50bcc26ae80fa83a3">WIFI_HMAC_MGMT_TIMEOUT</a> = 2, <a href="WLAN.md#ggaf3e873b51f0cfa077aca9d33ed7a0960a05f532edadae3b6afc80b7575dd46961">WIFI_HMAC_MGMT_REFUSED</a> = 3, &nbsp;&nbsp;<a href="WLAN.md#ggaf3e873b51f0cfa077aca9d33ed7a0960a9e241ef81e72de130e1fda573ce2a412">WIFI_HMAC_MGMT_TOMANY_REQ</a> = 4, <a href="WLAN.md#ggaf3e873b51f0cfa077aca9d33ed7a0960aa3db4634dc2727e029aef13384bc3940">WIFI_HMAC_MGMT_ALREADY_BSS</a> = 5 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1964642578084825"><a name="p1964642578084825"></a><a name="p1964642578084825"></a>Enumerates MLME management statuses, indicating whether a device is successfully associated or fails to be associated. </p>
</td>
</tr>
<tr id="row1357833058084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1287830980084825"><a name="p1287830980084825"></a><a name="p1287830980084825"></a><a href="WLAN.md#ga530241881cd17e03f8ae254ef1d9755e">NetIfCategory</a> { <a href="WLAN.md#gga530241881cd17e03f8ae254ef1d9755eaab9c78d744764e8f66591ee4a8d7b3cb">LITE_OS</a>, <a href="WLAN.md#gga530241881cd17e03f8ae254ef1d9755eafdfffeab76fab0306aa033c650ae0cfa">RICH_OS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1958974450084825"><a name="p1958974450084825"></a><a name="p1958974450084825"></a>Enumerates network interface categories, including lightweight OS and rich OS. </p>
</td>
</tr>
<tr id="row654696182084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1097023930084825"><a name="p1097023930084825"></a><a name="p1097023930084825"></a><a href="WLAN.md#ga0fb482694e5eac3f48c75de1749c8baf">NetIfStatus</a> { <a href="WLAN.md#gga0fb482694e5eac3f48c75de1749c8bafaeda2ad3830d5a42070617fd0211baf95">NETIF_DOWN</a>, <a href="WLAN.md#gga0fb482694e5eac3f48c75de1749c8bafa64a69f6624102c11bd658c09daf0f865">NETIF_UP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p510376941084825"><a name="p510376941084825"></a><a name="p510376941084825"></a>Enumerates network interface states, including online and offline. </p>
</td>
</tr>
<tr id="row1599191368084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p920588451084825"><a name="p920588451084825"></a><a name="p920588451084825"></a><a href="WLAN.md#ga7b1187d116fb065d7927ad9f77edd842">NetIfLinkStatus</a> { <a href="WLAN.md#gga7b1187d116fb065d7927ad9f77edd842a8586d0e791ca4f7026853d85740650b5">NETIF_LINK_DOWN</a>, <a href="WLAN.md#gga7b1187d116fb065d7927ad9f77edd842ac3108dbea78b5f0f928e6e5e4ea045f2">NETIF_LINK_UP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p998974083084825"><a name="p998974083084825"></a><a name="p998974083084825"></a>Enumerates network link layer states, including online and offline. </p>
</td>
</tr>
<tr id="row469313546084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851913344084825"><a name="p1851913344084825"></a><a name="p1851913344084825"></a><a href="WLAN.md#gad3175955d2e6ef3c4f52da9b509d5b4a">NetLinkType</a> { <a href="WLAN.md#ggad3175955d2e6ef3c4f52da9b509d5b4aa2d49c28127ce1d558ad5ea2f92e89fd7">ETHERNET_LINK</a> = 1, <a href="WLAN.md#ggad3175955d2e6ef3c4f52da9b509d5b4aadfed684cd7f64cc1aea5944657866db6">WIFI_LINK</a> = 801 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1970102921084825"><a name="p1970102921084825"></a><a name="p1970102921084825"></a>Enumerates data link types, including Ethernet and WLAN. </p>
</td>
</tr>
<tr id="row424480343084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1047155955084825"><a name="p1047155955084825"></a><a name="p1047155955084825"></a><a href="WLAN.md#ga9c1d6e7df4468671742cb76f72b67af1">ProcessingResult</a> { <a href="WLAN.md#gga9c1d6e7df4468671742cb76f72b67af1a5ce4c56e88c31420a02d3b7f068e0799">PROCESSING_CONTINUE</a>, <a href="WLAN.md#gga9c1d6e7df4468671742cb76f72b67af1a2fcbb133dcd739ab4a04b00bececd70a">PROCESSING_COMPLETE</a>, <a href="WLAN.md#gga9c1d6e7df4468671742cb76f72b67af1afe177a1b88ea1cdcc0e41181c2c73e83">PROCESSING_ERROR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p754342483084825"><a name="p754342483084825"></a><a name="p754342483084825"></a>Enumerates data processing results, including continuing processing, processing completed, and error. </p>
</td>
</tr>
<tr id="row775433973084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1986819000084825"><a name="p1986819000084825"></a><a name="p1986819000084825"></a><a href="WLAN.md#ga9fb4e578a15db1b0087d7b3831591ced">NetDevTxResult</a> { <a href="WLAN.md#gga9fb4e578a15db1b0087d7b3831591ceda734cacd083ffc8d233cab8d4deb6b38b">NETDEV_TX_OK</a> = 0x00, <a href="WLAN.md#gga9fb4e578a15db1b0087d7b3831591cedaf0a0ac437358f6af42c3e38795c46d35">NETDEV_TX_BUSY</a> = 0x10, <a href="WLAN.md#gga9fb4e578a15db1b0087d7b3831591ceda7eb70cee5761fe8954f94b660c37eaa8">NETDEV_TX_LOCKED</a> = 0x20 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1580343757084825"><a name="p1580343757084825"></a><a name="p1580343757084825"></a>Enumerates data sending results, including sending succeeded, other data being sent at the link layer, and data link layer being locked. </p>
</td>
</tr>
<tr id="row1993731759084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1479308724084825"><a name="p1479308724084825"></a><a name="p1479308724084825"></a><a href="WLAN.md#gac69954f56fcc99fc8aac68aa157831c7">Protocol80211IfType</a> { &nbsp;&nbsp;<a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7a6b209b916aabd18f2a950a82e68b6a4c">PROTOCOL_80211_IFTYPE_UNSPECIFIED</a>, <a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7a0926a98ddc2ceec4ba58ebfc01c5fe35">PROTOCOL_80211_IFTYPE_ADHOC</a>, <a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7acd26f8cefbd658e9ea02feecefd054fb">PROTOCOL_80211_IFTYPE_STATION</a>, <a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7a9e92654b9ab6ed6eb62868f1e0e4ea8f">PROTOCOL_80211_IFTYPE_AP</a>, &nbsp;&nbsp;<a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7a991ad1a3f8c43b06c4eeb9dc88acdb1e">PROTOCOL_80211_IFTYPE_AP_VLAN</a>, <a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7aa25631c32cd6c996a7c96ba4f61299e2">PROTOCOL_80211_IFTYPE_WDS</a>, <a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7a3ff1c1358af5a0c50b64e0ef0e96a970">PROTOCOL_80211_IFTYPE_MONITOR</a>, <a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7a382756b8a71015cd536cdbc113c4f483">PROTOCOL_80211_IFTYPE_MESH_POINT</a>, &nbsp;&nbsp;<a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7acfd81d6e484c6f7a3b863327af112cfc">PROTOCOL_80211_IFTYPE_P2P_CLIENT</a>, <a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7abca0ccb5cf4c14af9b6ff0bd9eeb4173">PROTOCOL_80211_IFTYPE_P2P_GO</a>, <a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7ad63ad4a5a66892e842e4d75cc82b0755">PROTOCOL_80211_IFTYPE_P2P_DEVICE</a>, <a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7a7f1fa9726ab20597baaa9ebf884b26cd">PROTOCOL_80211_IFTYPE_NUM</a>, &nbsp;&nbsp;<a href="WLAN.md#ggac69954f56fcc99fc8aac68aa157831c7a37b72ea7c4cd81dd4c427e2d721c9499">PROTOCOL_80211_IFTYPE_MAX</a> = PROTOCOL_80211_IFTYPE_NUM - 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1114811664084825"><a name="p1114811664084825"></a><a name="p1114811664084825"></a>Enumerates 802.11 network port types, including AP, STA, and P2P. </p>
</td>
</tr>
<tr id="row46896183084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1626510261084825"><a name="p1626510261084825"></a><a name="p1626510261084825"></a><a href="WLAN.md#ga9023c5dc1cc43758cbb468d78af41c2d">NetdeviceError</a> { <a href="WLAN.md#gga9023c5dc1cc43758cbb468d78af41c2dafe771f5d0d84d17922f466d3eed83d6b">COMMON_ERROR</a> = 1, <a href="WLAN.md#gga9023c5dc1cc43758cbb468d78af41c2daf5426609de8db5782b340a6bcd7e94d6">ADD_LWIP_ERROR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p780643668084825"><a name="p780643668084825"></a><a name="p780643668084825"></a>Enumerates network device errors, including common errors and errors in adding network devices to LwIP. </p>
</td>
</tr>
<tr id="row693061029084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1455686906084825"><a name="p1455686906084825"></a><a name="p1455686906084825"></a><a href="WLAN.md#gaec03ba36d71cc2d5f3209bc24aa6ee10">WifiMainFeatureType</a> { &nbsp;&nbsp;<a href="WLAN.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10a038fb1847d290b75b15949b6471b46ad">HDF_WIFI_FEATURE_BASE</a>, <a href="WLAN.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10aaec6c1686d47187e64fd108e0e797133">HDF_WIFI_FEATURE_AP</a>, <a href="WLAN.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10a0e814bd1cfc59a253cc575d3548a9d4e">HDF_WIFI_FEATURE_STA</a>, <a href="WLAN.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10a8e87c1727fa86bf92ee05cad85e7f872">HDF_WIFI_FEATURE_P2P</a>, &nbsp;&nbsp;<a href="WLAN.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10ae30b51638bc2c2fb739b3ddec6c5b92b">HDF_WIFI_FEATURE_NAN</a>, <a href="WLAN.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10ac12422e335003fbd392bff47c53c0352">HDF_WIFI_FEATURE_RTT</a>, <a href="WLAN.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10a28ff5971d579c1754e03a5f79a0c9e6f">HDF_WIFI_FEATURE_NUM</a> = 10 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1058583578084825"><a name="p1058583578084825"></a><a name="p1058583578084825"></a>Enumerates feature types of a WLAN module. </p>
</td>
</tr>
<tr id="row691759181084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p506840049084825"><a name="p506840049084825"></a><a name="p506840049084825"></a><a href="WLAN.md#ga1c5537e64f05b5e91b951ddeb66d4261">WifiBusType</a> { <a href="WLAN.md#gga1c5537e64f05b5e91b951ddeb66d4261a0eba50f5eecb33326083a82adbaa0848">BUS_SDIO</a>, <a href="WLAN.md#gga1c5537e64f05b5e91b951ddeb66d4261a2f4f9ff60278d511660c21e211133666">BUS_USB</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p779996008084825"><a name="p779996008084825"></a><a name="p779996008084825"></a>Enumerates bus types of a WLAN module. </p>
</td>
</tr>
<tr id="row633429393084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p134809849084825"><a name="p134809849084825"></a><a name="p134809849084825"></a><a href="WLAN.md#ga75cba3dc6ab4c5dc5653b037433b3abf">MacSetType</a> { <a href="WLAN.md#gga75cba3dc6ab4c5dc5653b037433b3abfa52532b66ba237505f04a57b382f67cb1">MAC_BEACON_SET</a> = 0, <a href="WLAN.md#gga75cba3dc6ab4c5dc5653b037433b3abfa8bb6332eadf8a54cdcf7d02b6040e7f3">MAC_BEACON_ADD</a> = 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p857957116084825"><a name="p857957116084825"></a><a name="p857957116084825"></a>Enumerates setting types of MAC addresses. </p>
</td>
</tr>
<tr id="row62374319084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2008379822084825"><a name="p2008379822084825"></a><a name="p2008379822084825"></a><a href="WLAN.md#ga9882f415202cf9acb0f4cdfbc456a88d">Ieee80211Band</a> { <a href="WLAN.md#gga9882f415202cf9acb0f4cdfbc456a88daf339f82c036557f42f668a358aa96da3">IEEE80211_BAND_2GHZ</a>, <a href="WLAN.md#gga9882f415202cf9acb0f4cdfbc456a88da0871c8866251ec4e668e956bb0427cfa">IEEE80211_BAND_5GHZ</a>, <a href="WLAN.md#gga9882f415202cf9acb0f4cdfbc456a88da703cf67d516a80d6dae1b1995017b9a4">IEEE80211_NUM_BANDS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1561599154084825"><a name="p1561599154084825"></a><a name="p1561599154084825"></a>Enumerates frequency bands. </p>
</td>
</tr>
<tr id="row195451602084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p283011041084825"><a name="p283011041084825"></a><a name="p283011041084825"></a><a href="WLAN.md#ga9d902b330de99c24b2a8c3ba7120af21">WifiChannelType</a> { <a href="WLAN.md#gga9d902b330de99c24b2a8c3ba7120af21ae0707e29a1748ee7f33d51acabaf8810">WIFI_CHAN_NO_HT</a>, <a href="WLAN.md#gga9d902b330de99c24b2a8c3ba7120af21a255f513fd4efa8bce0c015086e0588ea">WIFI_CHAN_HT20</a>, <a href="WLAN.md#gga9d902b330de99c24b2a8c3ba7120af21a1c6dbd2c2f6be59e4fa8312fe6009a98">WIFI_CHAN_HT40MINUS</a>, <a href="WLAN.md#gga9d902b330de99c24b2a8c3ba7120af21abdc85daa4bd2fdda2cfb14a975099652">WIFI_CHAN_HT40PLUS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2102598250084825"><a name="p2102598250084825"></a><a name="p2102598250084825"></a>Enumerates channel types. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1605600583084825"></a>
<table><thead align="left"><tr id="row441174369084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1077950841084825"><a name="p1077950841084825"></a><a name="p1077950841084825"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p52972305084825"><a name="p52972305084825"></a><a name="p52972305084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row541140603084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p852369826084825"><a name="p852369826084825"></a><a name="p852369826084825"></a><a href="WLAN.md#ga6e754d5529b23b413d1fe00102a95db9">NetBufQueueInit</a> (struct <a href="NetBufQueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p667479773084825"><a name="p667479773084825"></a><a name="p667479773084825"></a>static void&nbsp;</p>
<p id="p944377017084825"><a name="p944377017084825"></a><a name="p944377017084825"></a>Initializes a network data buffer queue. </p>
</td>
</tr>
<tr id="row358929665084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1333137806084825"><a name="p1333137806084825"></a><a name="p1333137806084825"></a><a href="WLAN.md#gaaa5c00efd1dedecf846af4dd108b6701">NetBufQueueSize</a> (const struct <a href="NetBufQueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p357172194084825"><a name="p357172194084825"></a><a name="p357172194084825"></a>static uint32_t&nbsp;</p>
<p id="p701952793084825"><a name="p701952793084825"></a><a name="p701952793084825"></a>Obtains the size of a network data buffer queue. </p>
</td>
</tr>
<tr id="row924787971084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1171390481084825"><a name="p1171390481084825"></a><a name="p1171390481084825"></a><a href="WLAN.md#ga36297284c60746f2b6895d94ea5e2dc3">NetBufQueueIsEmpty</a> (const struct <a href="NetBufQueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995115876084825"><a name="p1995115876084825"></a><a name="p1995115876084825"></a>static bool&nbsp;</p>
<p id="p1352735256084825"><a name="p1352735256084825"></a><a name="p1352735256084825"></a>Checks whether the network data buffer queue is empty. </p>
</td>
</tr>
<tr id="row1034171787084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p820686816084825"><a name="p820686816084825"></a><a name="p820686816084825"></a><a href="WLAN.md#ga25bf5d56e8afec1bc80080b20c3b7daa">NetBufQueueEnqueue</a> (struct <a href="NetBufQueue.md">NetBufQueue</a> *q, struct <a href="NetBuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1527476398084825"><a name="p1527476398084825"></a><a name="p1527476398084825"></a>void&nbsp;</p>
<p id="p1177383357084825"><a name="p1177383357084825"></a><a name="p1177383357084825"></a>Adds a network data buffer to the tail of a queue. </p>
</td>
</tr>
<tr id="row278446560084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p255285072084825"><a name="p255285072084825"></a><a name="p255285072084825"></a><a href="WLAN.md#ga5ebe7aff6d5187645869f067b0a8f659">NetBufQueueEnqueueHead</a> (struct <a href="NetBufQueue.md">NetBufQueue</a> *q, struct <a href="NetBuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1576672338084825"><a name="p1576672338084825"></a><a name="p1576672338084825"></a>void&nbsp;</p>
<p id="p1138731631084825"><a name="p1138731631084825"></a><a name="p1138731631084825"></a>Adds a network data buffer to the header of a queue. </p>
</td>
</tr>
<tr id="row2061135066084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p101299220084825"><a name="p101299220084825"></a><a name="p101299220084825"></a><a href="WLAN.md#ga4ad66d7ca7aabda3aef08fa541dc9ee4">NetBufQueueDequeue</a> (struct <a href="NetBufQueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1421001419084825"><a name="p1421001419084825"></a><a name="p1421001419084825"></a>struct <a href="NetBuf.md">NetBuf</a> *&nbsp;</p>
<p id="p1453670991084825"><a name="p1453670991084825"></a><a name="p1453670991084825"></a>Obtains a network data buffer from the header of a queue and deletes it from the queue. </p>
</td>
</tr>
<tr id="row1020022106084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p920845610084825"><a name="p920845610084825"></a><a name="p920845610084825"></a><a href="WLAN.md#ga390319a0419c26c73552bcee6b8d5c32">NetBufQueueDequeueTail</a> (struct <a href="NetBufQueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367851958084825"><a name="p1367851958084825"></a><a name="p1367851958084825"></a>struct <a href="NetBuf.md">NetBuf</a> *&nbsp;</p>
<p id="p373810008084825"><a name="p373810008084825"></a><a name="p373810008084825"></a>Obtains a network data buffer from the tail of a queue and deletes it from the queue. </p>
</td>
</tr>
<tr id="row221752023084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2007380022084825"><a name="p2007380022084825"></a><a name="p2007380022084825"></a><a href="WLAN.md#ga082b7a173ca09288c3b418ce4e4faa7d">NetBufQueueAtHead</a> (const struct <a href="NetBufQueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1664050969084825"><a name="p1664050969084825"></a><a name="p1664050969084825"></a>static struct <a href="NetBuf.md">NetBuf</a> *&nbsp;</p>
<p id="p395700834084825"><a name="p395700834084825"></a><a name="p395700834084825"></a>Obtains the network data buffer from the header of a queue, without deleting it from the queue. </p>
</td>
</tr>
<tr id="row364335160084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1727967708084825"><a name="p1727967708084825"></a><a name="p1727967708084825"></a><a href="WLAN.md#ga9de36bf1db57bd4eb042e87cb63dae69">NetBufQueueAtTail</a> (const struct <a href="NetBufQueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2043707981084825"><a name="p2043707981084825"></a><a name="p2043707981084825"></a>static struct <a href="NetBuf.md">NetBuf</a> *&nbsp;</p>
<p id="p1319577802084825"><a name="p1319577802084825"></a><a name="p1319577802084825"></a>Obtains the network data buffer from the tail of a queue, without deleting it from the queue. </p>
</td>
</tr>
<tr id="row2037335513084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p731214503084825"><a name="p731214503084825"></a><a name="p731214503084825"></a><a href="WLAN.md#ga79045ebd1636c27bee454e9541498f33">NetBufQueueClear</a> (struct <a href="NetBufQueue.md">NetBufQueue</a> *q)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1967929584084825"><a name="p1967929584084825"></a><a name="p1967929584084825"></a>void&nbsp;</p>
<p id="p1575728523084825"><a name="p1575728523084825"></a><a name="p1575728523084825"></a>Clears a network data buffer queue and releases the network data buffer in the queue. </p>
</td>
</tr>
<tr id="row2113184080084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p364011217084825"><a name="p364011217084825"></a><a name="p364011217084825"></a><a href="WLAN.md#ga2331e6b8c8f1ac4f00f8a1206fb1a3d8">NetBufQueueConcat</a> (struct <a href="NetBufQueue.md">NetBufQueue</a> *q, struct <a href="NetBufQueue.md">NetBufQueue</a> *add)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687140264084825"><a name="p1687140264084825"></a><a name="p1687140264084825"></a>void&nbsp;</p>
<p id="p344217843084825"><a name="p344217843084825"></a><a name="p344217843084825"></a>Moves all network data buffers from one queue to another and clears the source queue. </p>
</td>
</tr>
<tr id="row2126926366084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1699344054084825"><a name="p1699344054084825"></a><a name="p1699344054084825"></a><a href="WLAN.md#ga5ced2af63a9064b0e33d0aa4e86b3fc1">NetBufAlloc</a> (uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1200260729084825"><a name="p1200260729084825"></a><a name="p1200260729084825"></a>struct <a href="NetBuf.md">NetBuf</a> *&nbsp;</p>
<p id="p897695004084825"><a name="p897695004084825"></a><a name="p897695004084825"></a>Applies for a network data buffer. </p>
</td>
</tr>
<tr id="row804687681084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p96320675084825"><a name="p96320675084825"></a><a name="p96320675084825"></a><a href="WLAN.md#ga9320642699593dfecd79dc30132dd4eb">NetBufFree</a> (struct <a href="NetBuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p366013397084825"><a name="p366013397084825"></a><a name="p366013397084825"></a>void&nbsp;</p>
<p id="p1274888163084825"><a name="p1274888163084825"></a><a name="p1274888163084825"></a>Releases a network data buffer. </p>
</td>
</tr>
<tr id="row1866952483084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p673308037084825"><a name="p673308037084825"></a><a name="p673308037084825"></a><a href="WLAN.md#ga74198f03268aadc025f6b76056b09604">NetBufDevAlloc</a> (const struct <a href="NetDevice.md">NetDevice</a> *dev, uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p106905617084825"><a name="p106905617084825"></a><a name="p106905617084825"></a>struct <a href="NetBuf.md">NetBuf</a> *&nbsp;</p>
<p id="p577024193084825"><a name="p577024193084825"></a><a name="p577024193084825"></a>Applies for a network data buffer based on the reserved space and requested size set by a network device. </p>
</td>
</tr>
<tr id="row1568599552084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p94211560084825"><a name="p94211560084825"></a><a name="p94211560084825"></a><a href="WLAN.md#gac4ec1cedef616e61038dcb6dbf67d204">NetBufPush</a> (struct <a href="NetBuf.md">NetBuf</a> *nb, uint32_t id, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p7108137084825"><a name="p7108137084825"></a><a name="p7108137084825"></a>void *&nbsp;</p>
<p id="p1520076617084825"><a name="p1520076617084825"></a><a name="p1520076617084825"></a>Performs operations based on the segment ID of a network data buffer. The function is opposite to that of <a href="WLAN.md#ga81f298aebc5b7772f173e2f6fadc004f">NetBufPop</a>. </p>
</td>
</tr>
<tr id="row1532955856084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1695657983084825"><a name="p1695657983084825"></a><a name="p1695657983084825"></a><a href="WLAN.md#ga81f298aebc5b7772f173e2f6fadc004f">NetBufPop</a> (struct <a href="NetBuf.md">NetBuf</a> *nb, uint32_t id, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p74743453084825"><a name="p74743453084825"></a><a name="p74743453084825"></a>void *&nbsp;</p>
<p id="p1706212545084825"><a name="p1706212545084825"></a><a name="p1706212545084825"></a>Performs operations based on the segment ID of a network data buffer. The function is opposite to that of <a href="WLAN.md#gac4ec1cedef616e61038dcb6dbf67d204">NetBufPush</a>. </p>
</td>
</tr>
<tr id="row15902047084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1475711841084825"><a name="p1475711841084825"></a><a name="p1475711841084825"></a><a href="WLAN.md#gacd40d5004291b4aaa5c27703d9379c9c">NetBufGetAddress</a> (const struct <a href="NetBuf.md">NetBuf</a> *nb, uint32_t id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257083819084825"><a name="p257083819084825"></a><a name="p257083819084825"></a>static uint8_t *&nbsp;</p>
<p id="p1112576955084825"><a name="p1112576955084825"></a><a name="p1112576955084825"></a>Obtains the address of a specified buffer segment in a network data buffer. </p>
</td>
</tr>
<tr id="row30017752084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1327349024084825"><a name="p1327349024084825"></a><a name="p1327349024084825"></a><a href="WLAN.md#ga09245834fe9f55fe475a0dc226a6a709">NetBufGetRoom</a> (const struct <a href="NetBuf.md">NetBuf</a> *nb, uint32_t id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1406481078084825"><a name="p1406481078084825"></a><a name="p1406481078084825"></a>static uint32_t&nbsp;</p>
<p id="p1886479495084825"><a name="p1886479495084825"></a><a name="p1886479495084825"></a>Obtains the size of a specified buffer segment space in a network data buffer. </p>
</td>
</tr>
<tr id="row61947022084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1695381079084825"><a name="p1695381079084825"></a><a name="p1695381079084825"></a><a href="WLAN.md#ga67eeb57ebe467b9caa4f31734955727b">NetBufGetDataLen</a> (const struct <a href="NetBuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p903010747084825"><a name="p903010747084825"></a><a name="p903010747084825"></a>static uint32_t&nbsp;</p>
<p id="p515394670084825"><a name="p515394670084825"></a><a name="p515394670084825"></a>Obtains the actual data length of the data segment of a network data buffer. </p>
</td>
</tr>
<tr id="row870132585084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p212636234084825"><a name="p212636234084825"></a><a name="p212636234084825"></a><a href="WLAN.md#ga623e0b15e65f317f746b53b9a4530bdd">NetBufResizeRoom</a> (struct <a href="NetBuf.md">NetBuf</a> *nb, uint32_t head, uint32_t tail)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313687348084825"><a name="p1313687348084825"></a><a name="p1313687348084825"></a>int32_t&nbsp;</p>
<p id="p1599248895084825"><a name="p1599248895084825"></a><a name="p1599248895084825"></a>Adjusts the size of a network data buffer space. </p>
</td>
</tr>
<tr id="row1641606959084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p310398789084825"><a name="p310398789084825"></a><a name="p310398789084825"></a><a href="WLAN.md#ga89ee14a3da1b7b83325045af9c488ef8">NetBufConcat</a> (struct <a href="NetBuf.md">NetBuf</a> *nb, struct <a href="NetBuf.md">NetBuf</a> *cnb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1326128466084825"><a name="p1326128466084825"></a><a name="p1326128466084825"></a>uint32_t&nbsp;</p>
<p id="p1532848656084825"><a name="p1532848656084825"></a><a name="p1532848656084825"></a>Copies data in a network data buffer to another network data buffer. </p>
</td>
</tr>
<tr id="row872000526084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p196011191084825"><a name="p196011191084825"></a><a name="p196011191084825"></a><a href="WLAN.md#ga8d44f8dbfa75583d0056702b5a2d32a1">Pbuf2NetBuf</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev, struct pbuf *lwipBuf)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1979887332084825"><a name="p1979887332084825"></a><a name="p1979887332084825"></a>struct <a href="NetBuf.md">NetBuf</a> *&nbsp;</p>
<p id="p391167199084825"><a name="p391167199084825"></a><a name="p391167199084825"></a>Converts the <strong id="b1366025808084825"><a name="b1366025808084825"></a><a name="b1366025808084825"></a>pbuf</strong> structure of Lightweight TCP/IP Stack (lwIP) to a network data buffer. </p>
</td>
</tr>
<tr id="row570744836084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1548583853084825"><a name="p1548583853084825"></a><a name="p1548583853084825"></a><a href="WLAN.md#ga88e4943fc1b1f4e31f388bf8eec57476">NetBuf2Pbuf</a> (const struct <a href="NetBuf.md">NetBuf</a> *nb)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p543523761084825"><a name="p543523761084825"></a><a name="p543523761084825"></a>struct pbuf *&nbsp;</p>
<p id="p1807499856084825"><a name="p1807499856084825"></a><a name="p1807499856084825"></a>Converts a network data buffer to the <strong id="b634803142084825"><a name="b634803142084825"></a><a name="b634803142084825"></a>pbuf</strong> structure of Lightweight TCP/IP Stack (lwIP). </p>
</td>
</tr>
<tr id="row1224023625084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p911686987084825"><a name="p911686987084825"></a><a name="p911686987084825"></a><a href="WLAN.md#ga31edc1e9de8835e0e8a9c1e89fad3bd9">HdfWifiEventNewSta</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev, const uint8_t *macAddr, uint8_t addrLen, const struct <a href="StationInfo.md">StationInfo</a> *info)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673124185084825"><a name="p1673124185084825"></a><a name="p1673124185084825"></a>int32_t&nbsp;</p>
<p id="p431412730084825"><a name="p431412730084825"></a><a name="p431412730084825"></a>Reports a new STA event. </p>
</td>
</tr>
<tr id="row732085887084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p48150422084825"><a name="p48150422084825"></a><a name="p48150422084825"></a><a href="WLAN.md#ga208ef54b2a601f416a472bb1e21fae7e">HdfWifiEventDelSta</a> (struct <a href="NetDevice.md">NetDevice</a> *netdev, const uint8_t *macAddr, uint8_t addrLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1493879050084825"><a name="p1493879050084825"></a><a name="p1493879050084825"></a>int32_t&nbsp;</p>
<p id="p948213623084825"><a name="p948213623084825"></a><a name="p948213623084825"></a>Reports a station deletion event. </p>
</td>
</tr>
<tr id="row1993376028084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1109653105084825"><a name="p1109653105084825"></a><a name="p1109653105084825"></a><a href="WLAN.md#ga941675fb683212e6e0d8e1529b300482">HdfWifiEventInformBssFrame</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev, struct <a href="Wiphy.md">Wiphy</a> *wiphy, const struct <a href="Ieee80211Channel.md">Ieee80211Channel</a> *channel, const struct <a href="ScannedBssInfo.md">ScannedBssInfo</a> *bssInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p301756573084825"><a name="p301756573084825"></a><a name="p301756573084825"></a>int32_t&nbsp;</p>
<p id="p1754174596084825"><a name="p1754174596084825"></a><a name="p1754174596084825"></a>Reports a scanned BSS event. </p>
</td>
</tr>
<tr id="row49966361084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1450046546084825"><a name="p1450046546084825"></a><a name="p1450046546084825"></a><a href="WLAN.md#ga41efbd6788a80604b81ae117a363b657">HdfWifiEventScanDone</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev, WifiScanStatus status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p532818784084825"><a name="p532818784084825"></a><a name="p532818784084825"></a>int32_t&nbsp;</p>
<p id="p1662383976084825"><a name="p1662383976084825"></a><a name="p1662383976084825"></a>Reports a scanning completion event. </p>
</td>
</tr>
<tr id="row24648938084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1990755763084825"><a name="p1990755763084825"></a><a name="p1990755763084825"></a><a href="WLAN.md#gaf9e61f36e11d7d2e94e7969a8ecf22f1">HdfWifiEventConnectResult</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev, const struct <a href="ConnetResult.md">ConnetResult</a> *result)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p783148476084825"><a name="p783148476084825"></a><a name="p783148476084825"></a>int32_t&nbsp;</p>
<p id="p1402251634084825"><a name="p1402251634084825"></a><a name="p1402251634084825"></a>Reports a connection result event. </p>
</td>
</tr>
<tr id="row515580729084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1931656044084825"><a name="p1931656044084825"></a><a name="p1931656044084825"></a><a href="WLAN.md#ga58b1a613d784233a1e84027079e1ea57">HdfWifiEventDisconnected</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev, uint16_t reason, const uint8_t *ie, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1974516692084825"><a name="p1974516692084825"></a><a name="p1974516692084825"></a>int32_t&nbsp;</p>
<p id="p1640366337084825"><a name="p1640366337084825"></a><a name="p1640366337084825"></a>Reports a disconnection event. </p>
</td>
</tr>
<tr id="row55161792084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429553113084825"><a name="p429553113084825"></a><a name="p429553113084825"></a><a href="WLAN.md#ga1721c7e1b5af0240a663ea9f0fe12854">HdfWifiEventMgmtTxStatus</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev, const uint8_t *buf, size_t len, uint8_t ack)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p235227077084825"><a name="p235227077084825"></a><a name="p235227077084825"></a>int32_t&nbsp;</p>
<p id="p1489764096084825"><a name="p1489764096084825"></a><a name="p1489764096084825"></a>Reports a transmission management status event. </p>
</td>
</tr>
<tr id="row215392069084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1433834314084825"><a name="p1433834314084825"></a><a name="p1433834314084825"></a><a href="WLAN.md#gad47d56e4332ccd14116368444a4b330f">HdfWifiEventRxMgmt</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev, int32_t freq, int32_t sigMbm, const uint8_t *buf, size_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1053572317084825"><a name="p1053572317084825"></a><a name="p1053572317084825"></a>int32_t&nbsp;</p>
<p id="p1731560271084825"><a name="p1731560271084825"></a><a name="p1731560271084825"></a>Reports a receive management status event. </p>
</td>
</tr>
<tr id="row1482037011084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1279585028084825"><a name="p1279585028084825"></a><a name="p1279585028084825"></a><a href="WLAN.md#ga2aa62f7e8e72e8f9df0b2101c08a9d44">HdfWifiEventCsaChannelSwitch</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev, int32_t freq)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1606332328084825"><a name="p1606332328084825"></a><a name="p1606332328084825"></a>int32_t&nbsp;</p>
<p id="p28816214084825"><a name="p28816214084825"></a><a name="p28816214084825"></a>Reports a CSA channel switching event. </p>
</td>
</tr>
<tr id="row213428149084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p859829091084825"><a name="p859829091084825"></a><a name="p859829091084825"></a><a href="WLAN.md#gafda13471995c91e65326a9aa374ae1c9">HdfWifiEventTimeoutDisconnected</a> (const struct <a href="NetDevice.md">NetDevice</a> *netdev)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1177995866084825"><a name="p1177995866084825"></a><a name="p1177995866084825"></a>int32_t&nbsp;</p>
<p id="p749911726084825"><a name="p749911726084825"></a><a name="p749911726084825"></a>Reports a timeout disconnection event. </p>
</td>
</tr>
<tr id="row78064023084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1658925658084825"><a name="p1658925658084825"></a><a name="p1658925658084825"></a><a href="WLAN.md#ga3e60f4568723471226107848ddbe582f">HdfWifiEventEapolRecv</a> (const char *name, void *context)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1148839520084825"><a name="p1148839520084825"></a><a name="p1148839520084825"></a>int32_t&nbsp;</p>
<p id="p958896241084825"><a name="p958896241084825"></a><a name="p958896241084825"></a>Reports the event of receiving the EAPOL frame and notifies WPA to read the EAPOL frame. </p>
</td>
</tr>
<tr id="row1458293819084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p479831583084825"><a name="p479831583084825"></a><a name="p479831583084825"></a><a href="WLAN.md#ga77f15efb80095134d08cc63b62229f21">HdfWifiGetProduct</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p697278925084825"><a name="p697278925084825"></a><a name="p697278925084825"></a>struct <a href="HdfWifiProductData.md">HdfWifiProductData</a> *&nbsp;</p>
<p id="p473931499084825"><a name="p473931499084825"></a><a name="p473931499084825"></a>Obtains the data structure of the WLAN module. </p>
</td>
</tr>
<tr id="row2015276954084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p252494419084825"><a name="p252494419084825"></a><a name="p252494419084825"></a><a href="WLAN.md#ga8d2bff6673ec21ba317d596a84df7ca8">NetDeviceInit</a> (const char *ifName, uint32_t len, <a href="WLAN.md#ga530241881cd17e03f8ae254ef1d9755e">NetIfCategory</a> ifCategory)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p975785956084825"><a name="p975785956084825"></a><a name="p975785956084825"></a>struct <a href="NetDevice.md">NetDevice</a> *&nbsp;</p>
<p id="p872471734084825"><a name="p872471734084825"></a><a name="p872471734084825"></a>Initializes a network device to obtain its instance. </p>
</td>
</tr>
<tr id="row2090392617084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1444003890084825"><a name="p1444003890084825"></a><a name="p1444003890084825"></a><a href="WLAN.md#gaf4a2fa8b1a35d4cadd8247ee8fed60a4">NetDeviceDeInit</a> (struct <a href="NetDevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1461375752084825"><a name="p1461375752084825"></a><a name="p1461375752084825"></a>int32_t&nbsp;</p>
<p id="p138625288084825"><a name="p138625288084825"></a><a name="p138625288084825"></a>Deletes a network device. </p>
</td>
</tr>
<tr id="row1380783911084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778281832084825"><a name="p778281832084825"></a><a name="p778281832084825"></a><a href="WLAN.md#ga64be10f09b180d3098e9550163131dbd">NetDeviceAdd</a> (struct <a href="NetDevice.md">NetDevice</a> *netDevice, <a href="WLAN.md#gac69954f56fcc99fc8aac68aa157831c7">Protocol80211IfType</a> ifType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1259749661084825"><a name="p1259749661084825"></a><a name="p1259749661084825"></a>int32_t&nbsp;</p>
<p id="p48986248084825"><a name="p48986248084825"></a><a name="p48986248084825"></a>Adds a network device to a protocol stack. </p>
</td>
</tr>
<tr id="row2064623408084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p558875160084825"><a name="p558875160084825"></a><a name="p558875160084825"></a><a href="WLAN.md#ga6c93cb701cf2523eaa7bbeabd4acf3ab">NetDeviceDelete</a> (struct <a href="NetDevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1462947475084825"><a name="p1462947475084825"></a><a name="p1462947475084825"></a>int32_t&nbsp;</p>
<p id="p362832233084825"><a name="p362832233084825"></a><a name="p362832233084825"></a>Deletes a network device from a protocol stack. </p>
</td>
</tr>
<tr id="row585568510084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p241374339084825"><a name="p241374339084825"></a><a name="p241374339084825"></a><a href="WLAN.md#ga6d90d1bf783a83db1d838d03f8c1d93a">NetDeviceGetInstByName</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901494474084825"><a name="p1901494474084825"></a><a name="p1901494474084825"></a>struct <a href="NetDevice.md">NetDevice</a> *&nbsp;</p>
<p id="p1014699949084825"><a name="p1014699949084825"></a><a name="p1014699949084825"></a>Obtains the initialized network device instance by a specified device name. </p>
</td>
</tr>
<tr id="row1271693245084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p237988074084825"><a name="p237988074084825"></a><a name="p237988074084825"></a><a href="WLAN.md#ga20fcbcc248e99917c17223a97fe5d70e">NetDeviceIsAnyInstRunning</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1278242479084825"><a name="p1278242479084825"></a><a name="p1278242479084825"></a>bool&nbsp;</p>
<p id="p523137548084825"><a name="p523137548084825"></a><a name="p523137548084825"></a>Checks whether there are working devices among the added network devices. </p>
</td>
</tr>
<tr id="row886289235084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997340764084825"><a name="p1997340764084825"></a><a name="p1997340764084825"></a><a href="WLAN.md#ga05b08c890c69f3e633447f14e16d30f7">NetDeviceIsInstRunning</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p567269397084825"><a name="p567269397084825"></a><a name="p567269397084825"></a>bool&nbsp;</p>
<p id="p92234676084825"><a name="p92234676084825"></a><a name="p92234676084825"></a>Checks whether a specified network device is working. </p>
</td>
</tr>
<tr id="row339294347084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051982656084825"><a name="p2051982656084825"></a><a name="p2051982656084825"></a><a href="WLAN.md#ga8c8d400a6b4eb64445a2b4ea12102c9a">NetDevGetRegisterCount</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1456039319084825"><a name="p1456039319084825"></a><a name="p1456039319084825"></a>uint32_t&nbsp;</p>
<p id="p1120074660084825"><a name="p1120074660084825"></a><a name="p1120074660084825"></a>Obtains the number of added network devices. </p>
</td>
</tr>
<tr id="row812845937084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1043740719084825"><a name="p1043740719084825"></a><a name="p1043740719084825"></a><a href="WLAN.md#ga5d2a4fd370e2115b4c1fc8ecc46d64ab">NetDeviceGetCap</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1075053834084825"><a name="p1075053834084825"></a><a name="p1075053834084825"></a>uint32_t&nbsp;</p>
<p id="p120439361084825"><a name="p120439361084825"></a><a name="p120439361084825"></a>Obtains the maximum number of network devices that can be registered with this system at the same time. </p>
</td>
</tr>
<tr id="row1719651007084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1705949749084825"><a name="p1705949749084825"></a><a name="p1705949749084825"></a><a href="WLAN.md#gab45261476e710c30335975726af3a834">NetDeviceGetInstByIndex</a> (uint32_t <a href="UTILS.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1540375885084825"><a name="p1540375885084825"></a><a name="p1540375885084825"></a>struct <a href="NetDevice.md">NetDevice</a> *&nbsp;</p>
<p id="p134598663084825"><a name="p134598663084825"></a><a name="p134598663084825"></a>Obtains a network device instance based on the index number. </p>
</td>
</tr>
<tr id="row1018638971084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p526554113084825"><a name="p526554113084825"></a><a name="p526554113084825"></a><a href="WLAN.md#gadd5c08aa8e65a12db062b1b88d53cece">NetIfSetAddr</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice, const <a href="IpV4Addr.md">IpV4Addr</a> *ipAddr, const <a href="IpV4Addr.md">IpV4Addr</a> *netMask, const <a href="IpV4Addr.md">IpV4Addr</a> *gw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p789768761084825"><a name="p789768761084825"></a><a name="p789768761084825"></a>int32_t&nbsp;</p>
<p id="p1772496716084825"><a name="p1772496716084825"></a><a name="p1772496716084825"></a>Sets an IP address, mask, and gateway. </p>
</td>
</tr>
<tr id="row2033857933084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1931593409084825"><a name="p1931593409084825"></a><a name="p1931593409084825"></a><a href="WLAN.md#gaa14fc68a382284491a272992d5c477cb">NetIfSetStatus</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice, <a href="WLAN.md#ga0fb482694e5eac3f48c75de1749c8baf">NetIfStatus</a> status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p190725508084825"><a name="p190725508084825"></a><a name="p190725508084825"></a>int32_t&nbsp;</p>
<p id="p1386226841084825"><a name="p1386226841084825"></a><a name="p1386226841084825"></a>Notifies the network layer of the network port state. </p>
</td>
</tr>
<tr id="row913924194084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1948516222084825"><a name="p1948516222084825"></a><a name="p1948516222084825"></a><a href="WLAN.md#gaee9c68875ef541ed915045ab7a047ee8">NetIfSetLinkStatus</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice, <a href="WLAN.md#ga7b1187d116fb065d7927ad9f77edd842">NetIfLinkStatus</a> status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1305578093084825"><a name="p1305578093084825"></a><a name="p1305578093084825"></a>int32_t&nbsp;</p>
<p id="p871702814084825"><a name="p871702814084825"></a><a name="p871702814084825"></a>Notifies the network layer of the data link layer status. </p>
</td>
</tr>
<tr id="row1276802930084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1611990622084825"><a name="p1611990622084825"></a><a name="p1611990622084825"></a><a href="WLAN.md#ga44006f6e066aff9f6a3310559e781582">NetIfRx</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice, struct <a href="NetBuf.md">NetBuf</a> *buff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751263551084825"><a name="p751263551084825"></a><a name="p751263551084825"></a>int32_t&nbsp;</p>
<p id="p1571724502084825"><a name="p1571724502084825"></a><a name="p1571724502084825"></a>Transfers the input data packets from the network side to a protocol stack. </p>
</td>
</tr>
<tr id="row614922090084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1982269196084825"><a name="p1982269196084825"></a><a name="p1982269196084825"></a><a href="WLAN.md#gad252107cdd20e9d3d0ab33fbfc2161e9">NetIfRxNi</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice, struct <a href="NetBuf.md">NetBuf</a> *buff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1728688226084825"><a name="p1728688226084825"></a><a name="p1728688226084825"></a>int32_t&nbsp;</p>
<p id="p765294307084825"><a name="p765294307084825"></a><a name="p765294307084825"></a>Transfers data packets from the network side to a protocol stack in an interrupt processing thread. </p>
</td>
</tr>
<tr id="row1944908144084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p915676169084825"><a name="p915676169084825"></a><a name="p915676169084825"></a><a href="WLAN.md#gae97c7abcf556be34798622a85162c35e">NetIfDhcpsStart</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice, char *ip, u16_t ipNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p847441707084825"><a name="p847441707084825"></a><a name="p847441707084825"></a>int32_t&nbsp;</p>
<p id="p226979222084825"><a name="p226979222084825"></a><a name="p226979222084825"></a>Starts the DHCP server. </p>
</td>
</tr>
<tr id="row772241890084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p665607162084825"><a name="p665607162084825"></a><a name="p665607162084825"></a><a href="WLAN.md#gaadfeb819b4cb623870823fa5c9793b4c">NetIfDhcpsStop</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p634033820084825"><a name="p634033820084825"></a><a name="p634033820084825"></a>int32_t&nbsp;</p>
<p id="p498350218084825"><a name="p498350218084825"></a><a name="p498350218084825"></a>Stops the DHCP server. </p>
</td>
</tr>
<tr id="row288150561084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p586055623084825"><a name="p586055623084825"></a><a name="p586055623084825"></a><a href="WLAN.md#ga5fdd93c820b994adf1b76eb8d50e4f88">NetIfDhcpStart</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p160067069084825"><a name="p160067069084825"></a><a name="p160067069084825"></a>int32_t&nbsp;</p>
<p id="p911215862084825"><a name="p911215862084825"></a><a name="p911215862084825"></a>Starts the DHCP client of a specified network device. </p>
</td>
</tr>
<tr id="row394537973084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1463985268084825"><a name="p1463985268084825"></a><a name="p1463985268084825"></a><a href="WLAN.md#ga22f97a3fc45841e874ab2072c14e0f3e">NetIfDhcpStop</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1241503735084825"><a name="p1241503735084825"></a><a name="p1241503735084825"></a>int32_t&nbsp;</p>
<p id="p693663479084825"><a name="p693663479084825"></a><a name="p693663479084825"></a>Stops the DHCP client of a specified network device. </p>
</td>
</tr>
<tr id="row922866141084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1943862592084825"><a name="p1943862592084825"></a><a name="p1943862592084825"></a><a href="WLAN.md#ga389ec95a3c8170c4ca74487f8bc1d8ac">NetIfDhcpIsBound</a> (const struct <a href="NetDevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p806462850084825"><a name="p806462850084825"></a><a name="p806462850084825"></a>int32_t&nbsp;</p>
<p id="p867772876084825"><a name="p867772876084825"></a><a name="p867772876084825"></a>Obtains the DHCP negotiation status of a specified network device. </p>
</td>
</tr>
<tr id="row833027013084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p29221534084825"><a name="p29221534084825"></a><a name="p29221534084825"></a><a href="WLAN.md#ga6542a735af0fe7496789c3c55380adfa">Mac80211RegisterOps</a> (struct <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> *ops) __attribute__((weak))</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p264153960084825"><a name="p264153960084825"></a><a name="p264153960084825"></a>int32_t&nbsp;</p>
<p id="p1813123949084825"><a name="p1813123949084825"></a><a name="p1813123949084825"></a>Registers a <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> object. </p>
</td>
</tr>
<tr id="row182780935084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1126539611084825"><a name="p1126539611084825"></a><a name="p1126539611084825"></a><a href="WLAN.md#gad7c34413d81d55ba090c90404d340c8a">Mac80211GetOps</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1854068429084825"><a name="p1854068429084825"></a><a name="p1854068429084825"></a>struct <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> *&nbsp;</p>
<p id="p667308424084825"><a name="p667308424084825"></a><a name="p667308424084825"></a>Obtains the <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> object that the driver needs to implement. </p>
</td>
</tr>
<tr id="row1192446675084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1459071125084825"><a name="p1459071125084825"></a><a name="p1459071125084825"></a><a href="WLAN.md#gaf5d1df53f08cae98ecfd440f9b425709">WifiModuleCreate</a> (const struct HdfConfigWifiModuleConfig *config)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p353502503084825"><a name="p353502503084825"></a><a name="p353502503084825"></a>struct <a href="WifiModule.md">WifiModule</a> *&nbsp;</p>
<p id="p1645899757084825"><a name="p1645899757084825"></a><a name="p1645899757084825"></a>Creates a <a href="WifiModule.md">WifiModule</a> object based on a specified configuration generated by the HCS. </p>
</td>
</tr>
<tr id="row1315858759084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1688233618084825"><a name="p1688233618084825"></a><a name="p1688233618084825"></a><a href="WLAN.md#gae14e3786e60f16a100197d28bae5a362">WifiModuleDelete</a> (struct <a href="WifiModule.md">WifiModule</a> *module)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p113271108084825"><a name="p113271108084825"></a><a name="p113271108084825"></a>void&nbsp;</p>
<p id="p2100180800084825"><a name="p2100180800084825"></a><a name="p2100180800084825"></a>Deletes a specified <a href="WifiModule.md">WifiModule</a> object. </p>
</td>
</tr>
<tr id="row1843164170084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1491994380084825"><a name="p1491994380084825"></a><a name="p1491994380084825"></a><a href="WLAN.md#ga395848b77fc10f2213d5b12793861292">DelFeature</a> (struct <a href="WifiModule.md">WifiModule</a> *module, uint16_t featureType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1363671052084825"><a name="p1363671052084825"></a><a name="p1363671052084825"></a>int32_t&nbsp;</p>
<p id="p458339421084825"><a name="p458339421084825"></a><a name="p458339421084825"></a>Deletes a specified feature from a specified module. </p>
</td>
</tr>
<tr id="row740168330084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1481284075084825"><a name="p1481284075084825"></a><a name="p1481284075084825"></a><a href="WLAN.md#gae928a69366143780650b73c6b030c3a7">AddFeature</a> (struct <a href="WifiModule.md">WifiModule</a> *module, uint16_t featureType, struct <a href="WifiFeature.md">WifiFeature</a> *featureData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1516042556084825"><a name="p1516042556084825"></a><a name="p1516042556084825"></a>int32_t&nbsp;</p>
<p id="p601542954084825"><a name="p601542954084825"></a><a name="p601542954084825"></a>Adds a specified feature to a specified module. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1721100178084825"></a>

## **Macro Definition Documentation**<a name="section421538028084825"></a>

## MAX\_NETBUF\_RESEVER\_SIZE<a name="ga794c035a19a38acc000146a8f9a4ec80"></a>

```
#define MAX_NETBUF_RESEVER_SIZE   68
```

 **Description:**

Defines the reserved field of a network data buffer used to store private information. 

The length of the reserved field is  **68**  bytes. 

## MAX\_WIFI\_COMPONENT\_NAME\_LEN<a name="gaf460a45a5e365279ca6bc5b3e8750542"></a>

```
#define MAX_WIFI_COMPONENT_NAME_LEN   10
```

 **Description:**

Indicates the length of the name of a WLAN module or feature. 

The name of a WLAN module or feature cannot contain more than 10 characters; otherwise, the name will be truncated and cannot be identified.

## **Typedef Documentation**<a name="section1031956811084825"></a>

## Mac80211SetMacParam<a name="ga85f7d8a3795887f090e0a6439b1df6e1"></a>

```
typedef struct [MacConfigParam](MacConfigParam.md) [Mac80211SetMacParam](WLAN.md#ga85f7d8a3795887f090e0a6439b1df6e1)
```

 **Description:**

Describes MAC configuration parameters. 

## NetDevice<a name="gac26e4b0cda623f27420f9ce77befbb1f"></a>

```
typedef struct [NetDevice](NetDevice.md) [NetDevice](NetDevice.md)
```

 **Description:**

Defines a network device, including the network interface category and name, and network port type. 

## WifiConnectParams<a name="ga3e8945c521d2392cb775494570c560b3"></a>

```
typedef struct [WifiConnectParams](WifiConnectParams.md) [WifiConnectParams](WifiConnectParams.md)
```

 **Description:**

Describes parameters for a connection request. 

## **Enumeration Type Documentation**<a name="section1432727384084825"></a>

## anonymous enum<a name="gae4d5251432e1a9e6803c0240cc492e18"></a>

```
anonymous enum
```

 **Description:**

Enumerates the segments of a network data buffer. 

The entire network data buffer is divided into three segments: a header, data, and a tail. The header and tail are used to extend both ends of the data segment.

<a name="table911316444084825"></a>
<table><thead align="left"><tr id="row1967509048084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1624636748084825"><a name="p1624636748084825"></a><a name="p1624636748084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1555211435084825"><a name="p1555211435084825"></a><a name="p1555211435084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row830089627084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggae4d5251432e1a9e6803c0240cc492e18a0e4808dd476b314c0fdbf417307f8b92"><a name="ggae4d5251432e1a9e6803c0240cc492e18a0e4808dd476b314c0fdbf417307f8b92"></a><a name="ggae4d5251432e1a9e6803c0240cc492e18a0e4808dd476b314c0fdbf417307f8b92"></a></strong>E_HEAD_BUF&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p241090202084825"><a name="p241090202084825"></a><a name="p241090202084825"></a>Header buffer segment </p>
 </td>
</tr>
<tr id="row1932220954084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggae4d5251432e1a9e6803c0240cc492e18a4b374b76d2b9bb60c31a1a540369b6d4"><a name="ggae4d5251432e1a9e6803c0240cc492e18a4b374b76d2b9bb60c31a1a540369b6d4"></a><a name="ggae4d5251432e1a9e6803c0240cc492e18a4b374b76d2b9bb60c31a1a540369b6d4"></a></strong>E_DATA_BUF&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p878103293084825"><a name="p878103293084825"></a><a name="p878103293084825"></a>Data segment </p>
 </td>
</tr>
<tr id="row147186885084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggae4d5251432e1a9e6803c0240cc492e18a316baeacb77ecf28631a76f1dbea872d"><a name="ggae4d5251432e1a9e6803c0240cc492e18a316baeacb77ecf28631a76f1dbea872d"></a><a name="ggae4d5251432e1a9e6803c0240cc492e18a316baeacb77ecf28631a76f1dbea872d"></a></strong>E_TAIL_BUF&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1591170041084825"><a name="p1591170041084825"></a><a name="p1591170041084825"></a>Tail buffer segment </p>
 </td>
</tr>
<tr id="row1813038247084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggae4d5251432e1a9e6803c0240cc492e18aeef2a730ef9f722cfbac0b24998f8e19"><a name="ggae4d5251432e1a9e6803c0240cc492e18aeef2a730ef9f722cfbac0b24998f8e19"></a><a name="ggae4d5251432e1a9e6803c0240cc492e18aeef2a730ef9f722cfbac0b24998f8e19"></a></strong>MAX_BUF_NUM&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p3060669084825"><a name="p3060669084825"></a><a name="p3060669084825"></a>Maximum number of buffer segments </p>
 </td>
</tr>
</tbody>
</table>

## Ieee80211Band<a name="ga9882f415202cf9acb0f4cdfbc456a88d"></a>

```
enum [Ieee80211Band](WLAN.md#ga9882f415202cf9acb0f4cdfbc456a88d)
```

 **Description:**

Enumerates frequency bands. 

<a name="table80307124084825"></a>
<table><thead align="left"><tr id="row822649343084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p107706126084825"><a name="p107706126084825"></a><a name="p107706126084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p829302837084825"><a name="p829302837084825"></a><a name="p829302837084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row48039124084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9882f415202cf9acb0f4cdfbc456a88daf339f82c036557f42f668a358aa96da3"><a name="gga9882f415202cf9acb0f4cdfbc456a88daf339f82c036557f42f668a358aa96da3"></a><a name="gga9882f415202cf9acb0f4cdfbc456a88daf339f82c036557f42f668a358aa96da3"></a></strong>IEEE80211_BAND_2GHZ&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1806528938084825"><a name="p1806528938084825"></a><a name="p1806528938084825"></a>2.4 GHz </p>
 </td>
</tr>
<tr id="row1769105221084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9882f415202cf9acb0f4cdfbc456a88da0871c8866251ec4e668e956bb0427cfa"><a name="gga9882f415202cf9acb0f4cdfbc456a88da0871c8866251ec4e668e956bb0427cfa"></a><a name="gga9882f415202cf9acb0f4cdfbc456a88da0871c8866251ec4e668e956bb0427cfa"></a></strong>IEEE80211_BAND_5GHZ&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1430433730084825"><a name="p1430433730084825"></a><a name="p1430433730084825"></a>5 GHz </p>
 </td>
</tr>
<tr id="row309055860084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9882f415202cf9acb0f4cdfbc456a88da703cf67d516a80d6dae1b1995017b9a4"><a name="gga9882f415202cf9acb0f4cdfbc456a88da703cf67d516a80d6dae1b1995017b9a4"></a><a name="gga9882f415202cf9acb0f4cdfbc456a88da703cf67d516a80d6dae1b1995017b9a4"></a></strong>IEEE80211_NUM_BANDS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p503435778084825"><a name="p503435778084825"></a><a name="p503435778084825"></a>Reserved </p>
 </td>
</tr>
</tbody>
</table>

## MacSetType<a name="ga75cba3dc6ab4c5dc5653b037433b3abf"></a>

```
enum [MacSetType](WLAN.md#ga75cba3dc6ab4c5dc5653b037433b3abf)
```

 **Description:**

Enumerates setting types of MAC addresses. 

<a name="table1955110402084825"></a>
<table><thead align="left"><tr id="row436972767084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1995448276084825"><a name="p1995448276084825"></a><a name="p1995448276084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1667041917084825"><a name="p1667041917084825"></a><a name="p1667041917084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row59912959084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga75cba3dc6ab4c5dc5653b037433b3abfa52532b66ba237505f04a57b382f67cb1"><a name="gga75cba3dc6ab4c5dc5653b037433b3abfa52532b66ba237505f04a57b382f67cb1"></a><a name="gga75cba3dc6ab4c5dc5653b037433b3abfa52532b66ba237505f04a57b382f67cb1"></a></strong>MAC_BEACON_SET&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1390459229084825"><a name="p1390459229084825"></a><a name="p1390459229084825"></a>Setting a beacon MAC address </p>
 </td>
</tr>
<tr id="row1177302164084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga75cba3dc6ab4c5dc5653b037433b3abfa8bb6332eadf8a54cdcf7d02b6040e7f3"><a name="gga75cba3dc6ab4c5dc5653b037433b3abfa8bb6332eadf8a54cdcf7d02b6040e7f3"></a><a name="gga75cba3dc6ab4c5dc5653b037433b3abfa8bb6332eadf8a54cdcf7d02b6040e7f3"></a></strong>MAC_BEACON_ADD&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71602372084825"><a name="p71602372084825"></a><a name="p71602372084825"></a>Adding a beacon MAC address </p>
 </td>
</tr>
</tbody>
</table>

## NetdeviceError<a name="ga9023c5dc1cc43758cbb468d78af41c2d"></a>

```
enum [NetdeviceError](WLAN.md#ga9023c5dc1cc43758cbb468d78af41c2d)
```

 **Description:**

Enumerates network device errors, including common errors and errors in adding network devices to LwIP. 

<a name="table1717315674084825"></a>
<table><thead align="left"><tr id="row1032976364084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p326418239084825"><a name="p326418239084825"></a><a name="p326418239084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p783759541084825"><a name="p783759541084825"></a><a name="p783759541084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1333712180084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9023c5dc1cc43758cbb468d78af41c2dafe771f5d0d84d17922f466d3eed83d6b"><a name="gga9023c5dc1cc43758cbb468d78af41c2dafe771f5d0d84d17922f466d3eed83d6b"></a><a name="gga9023c5dc1cc43758cbb468d78af41c2dafe771f5d0d84d17922f466d3eed83d6b"></a></strong>COMMON_ERROR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1618077639084825"><a name="p1618077639084825"></a><a name="p1618077639084825"></a>Common errors </p>
 </td>
</tr>
<tr id="row236832543084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9023c5dc1cc43758cbb468d78af41c2daf5426609de8db5782b340a6bcd7e94d6"><a name="gga9023c5dc1cc43758cbb468d78af41c2daf5426609de8db5782b340a6bcd7e94d6"></a><a name="gga9023c5dc1cc43758cbb468d78af41c2daf5426609de8db5782b340a6bcd7e94d6"></a></strong>ADD_LWIP_ERROR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p200736885084825"><a name="p200736885084825"></a><a name="p200736885084825"></a>Errors in adding network devices to LwIP </p>
 </td>
</tr>
</tbody>
</table>

## NetDevTxResult<a name="ga9fb4e578a15db1b0087d7b3831591ced"></a>

```
enum [NetDevTxResult](WLAN.md#ga9fb4e578a15db1b0087d7b3831591ced)
```

 **Description:**

Enumerates data sending results, including sending succeeded, other data being sent at the link layer, and data link layer being locked. 

<a name="table35370989084825"></a>
<table><thead align="left"><tr id="row253468350084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p995061268084825"><a name="p995061268084825"></a><a name="p995061268084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2008370022084825"><a name="p2008370022084825"></a><a name="p2008370022084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row149540183084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9fb4e578a15db1b0087d7b3831591ceda734cacd083ffc8d233cab8d4deb6b38b"><a name="gga9fb4e578a15db1b0087d7b3831591ceda734cacd083ffc8d233cab8d4deb6b38b"></a><a name="gga9fb4e578a15db1b0087d7b3831591ceda734cacd083ffc8d233cab8d4deb6b38b"></a></strong>NETDEV_TX_OK&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1203748156084825"><a name="p1203748156084825"></a><a name="p1203748156084825"></a>Sending succeeded </p>
 </td>
</tr>
<tr id="row465248709084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9fb4e578a15db1b0087d7b3831591cedaf0a0ac437358f6af42c3e38795c46d35"><a name="gga9fb4e578a15db1b0087d7b3831591cedaf0a0ac437358f6af42c3e38795c46d35"></a><a name="gga9fb4e578a15db1b0087d7b3831591cedaf0a0ac437358f6af42c3e38795c46d35"></a></strong>NETDEV_TX_BUSY&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449141853084825"><a name="p449141853084825"></a><a name="p449141853084825"></a>Other data being sent at the link layer </p>
 </td>
</tr>
<tr id="row1064221994084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9fb4e578a15db1b0087d7b3831591ceda7eb70cee5761fe8954f94b660c37eaa8"><a name="gga9fb4e578a15db1b0087d7b3831591ceda7eb70cee5761fe8954f94b660c37eaa8"></a><a name="gga9fb4e578a15db1b0087d7b3831591ceda7eb70cee5761fe8954f94b660c37eaa8"></a></strong>NETDEV_TX_LOCKED&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p486541751084825"><a name="p486541751084825"></a><a name="p486541751084825"></a>Data link layer being locked </p>
 </td>
</tr>
</tbody>
</table>

## NetIfCategory<a name="ga530241881cd17e03f8ae254ef1d9755e"></a>

```
enum [NetIfCategory](WLAN.md#ga530241881cd17e03f8ae254ef1d9755e)
```

 **Description:**

Enumerates network interface categories, including lightweight OS and rich OS. 

<a name="table1909357847084825"></a>
<table><thead align="left"><tr id="row386959437084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1864337744084825"><a name="p1864337744084825"></a><a name="p1864337744084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p309225733084825"><a name="p309225733084825"></a><a name="p309225733084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row522338131084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga530241881cd17e03f8ae254ef1d9755eaab9c78d744764e8f66591ee4a8d7b3cb"><a name="gga530241881cd17e03f8ae254ef1d9755eaab9c78d744764e8f66591ee4a8d7b3cb"></a><a name="gga530241881cd17e03f8ae254ef1d9755eaab9c78d744764e8f66591ee4a8d7b3cb"></a></strong>LITE_OS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p683163322084825"><a name="p683163322084825"></a><a name="p683163322084825"></a>Lightweight OS </p>
 </td>
</tr>
<tr id="row69608925084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga530241881cd17e03f8ae254ef1d9755eafdfffeab76fab0306aa033c650ae0cfa"><a name="gga530241881cd17e03f8ae254ef1d9755eafdfffeab76fab0306aa033c650ae0cfa"></a><a name="gga530241881cd17e03f8ae254ef1d9755eafdfffeab76fab0306aa033c650ae0cfa"></a></strong>RICH_OS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p542595001084825"><a name="p542595001084825"></a><a name="p542595001084825"></a>Rich OS </p>
 </td>
</tr>
</tbody>
</table>

## NetIfLinkStatus<a name="ga7b1187d116fb065d7927ad9f77edd842"></a>

```
enum [NetIfLinkStatus](WLAN.md#ga7b1187d116fb065d7927ad9f77edd842)
```

 **Description:**

Enumerates network link layer states, including online and offline. 

<a name="table1394429006084825"></a>
<table><thead align="left"><tr id="row548212943084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p338750696084825"><a name="p338750696084825"></a><a name="p338750696084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p661570696084825"><a name="p661570696084825"></a><a name="p661570696084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1717919324084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7b1187d116fb065d7927ad9f77edd842a8586d0e791ca4f7026853d85740650b5"><a name="gga7b1187d116fb065d7927ad9f77edd842a8586d0e791ca4f7026853d85740650b5"></a><a name="gga7b1187d116fb065d7927ad9f77edd842a8586d0e791ca4f7026853d85740650b5"></a></strong>NETIF_LINK_DOWN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p523452225084825"><a name="p523452225084825"></a><a name="p523452225084825"></a>Data link offline </p>
 </td>
</tr>
<tr id="row436820247084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga7b1187d116fb065d7927ad9f77edd842ac3108dbea78b5f0f928e6e5e4ea045f2"><a name="gga7b1187d116fb065d7927ad9f77edd842ac3108dbea78b5f0f928e6e5e4ea045f2"></a><a name="gga7b1187d116fb065d7927ad9f77edd842ac3108dbea78b5f0f928e6e5e4ea045f2"></a></strong>NETIF_LINK_UP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2019351466084825"><a name="p2019351466084825"></a><a name="p2019351466084825"></a>Data link online </p>
 </td>
</tr>
</tbody>
</table>

## NetIfStatus<a name="ga0fb482694e5eac3f48c75de1749c8baf"></a>

```
enum [NetIfStatus](WLAN.md#ga0fb482694e5eac3f48c75de1749c8baf)
```

 **Description:**

Enumerates network interface states, including online and offline. 

<a name="table972861272084825"></a>
<table><thead align="left"><tr id="row1344770148084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p526433732084825"><a name="p526433732084825"></a><a name="p526433732084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p734570990084825"><a name="p734570990084825"></a><a name="p734570990084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row500737404084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0fb482694e5eac3f48c75de1749c8bafaeda2ad3830d5a42070617fd0211baf95"><a name="gga0fb482694e5eac3f48c75de1749c8bafaeda2ad3830d5a42070617fd0211baf95"></a><a name="gga0fb482694e5eac3f48c75de1749c8bafaeda2ad3830d5a42070617fd0211baf95"></a></strong>NETIF_DOWN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p397557719084825"><a name="p397557719084825"></a><a name="p397557719084825"></a>Network interface offline </p>
 </td>
</tr>
<tr id="row228245965084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga0fb482694e5eac3f48c75de1749c8bafa64a69f6624102c11bd658c09daf0f865"><a name="gga0fb482694e5eac3f48c75de1749c8bafa64a69f6624102c11bd658c09daf0f865"></a><a name="gga0fb482694e5eac3f48c75de1749c8bafa64a69f6624102c11bd658c09daf0f865"></a></strong>NETIF_UP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p723371374084825"><a name="p723371374084825"></a><a name="p723371374084825"></a>Network interface online </p>
 </td>
</tr>
</tbody>
</table>

## NetLinkType<a name="gad3175955d2e6ef3c4f52da9b509d5b4a"></a>

```
enum [NetLinkType](WLAN.md#gad3175955d2e6ef3c4f52da9b509d5b4a)
```

 **Description:**

Enumerates data link types, including Ethernet and WLAN. 

<a name="table22183281084825"></a>
<table><thead align="left"><tr id="row462714957084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1410900594084825"><a name="p1410900594084825"></a><a name="p1410900594084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p990201095084825"><a name="p990201095084825"></a><a name="p990201095084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1615837647084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad3175955d2e6ef3c4f52da9b509d5b4aa2d49c28127ce1d558ad5ea2f92e89fd7"><a name="ggad3175955d2e6ef3c4f52da9b509d5b4aa2d49c28127ce1d558ad5ea2f92e89fd7"></a><a name="ggad3175955d2e6ef3c4f52da9b509d5b4aa2d49c28127ce1d558ad5ea2f92e89fd7"></a></strong>ETHERNET_LINK&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032002650084825"><a name="p1032002650084825"></a><a name="p1032002650084825"></a>Ethernet </p>
 </td>
</tr>
<tr id="row1169855327084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggad3175955d2e6ef3c4f52da9b509d5b4aadfed684cd7f64cc1aea5944657866db6"><a name="ggad3175955d2e6ef3c4f52da9b509d5b4aadfed684cd7f64cc1aea5944657866db6"></a><a name="ggad3175955d2e6ef3c4f52da9b509d5b4aadfed684cd7f64cc1aea5944657866db6"></a></strong>WIFI_LINK&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764544534084825"><a name="p764544534084825"></a><a name="p764544534084825"></a>WLAN </p>
 </td>
</tr>
</tbody>
</table>

## ProcessingResult<a name="ga9c1d6e7df4468671742cb76f72b67af1"></a>

```
enum [ProcessingResult](WLAN.md#ga9c1d6e7df4468671742cb76f72b67af1)
```

 **Description:**

Enumerates data processing results, including continuing processing, processing completed, and error. 

<a name="table885176758084825"></a>
<table><thead align="left"><tr id="row2082781082084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1535995840084825"><a name="p1535995840084825"></a><a name="p1535995840084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p613776947084825"><a name="p613776947084825"></a><a name="p613776947084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1114710787084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9c1d6e7df4468671742cb76f72b67af1a5ce4c56e88c31420a02d3b7f068e0799"><a name="gga9c1d6e7df4468671742cb76f72b67af1a5ce4c56e88c31420a02d3b7f068e0799"></a><a name="gga9c1d6e7df4468671742cb76f72b67af1a5ce4c56e88c31420a02d3b7f068e0799"></a></strong>PROCESSING_CONTINUE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1085619748084825"><a name="p1085619748084825"></a><a name="p1085619748084825"></a>Continuing processing </p>
 </td>
</tr>
<tr id="row226678776084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9c1d6e7df4468671742cb76f72b67af1a2fcbb133dcd739ab4a04b00bececd70a"><a name="gga9c1d6e7df4468671742cb76f72b67af1a2fcbb133dcd739ab4a04b00bececd70a"></a><a name="gga9c1d6e7df4468671742cb76f72b67af1a2fcbb133dcd739ab4a04b00bececd70a"></a></strong>PROCESSING_COMPLETE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1056745884084825"><a name="p1056745884084825"></a><a name="p1056745884084825"></a>Processing completed </p>
 </td>
</tr>
<tr id="row73126495084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9c1d6e7df4468671742cb76f72b67af1afe177a1b88ea1cdcc0e41181c2c73e83"><a name="gga9c1d6e7df4468671742cb76f72b67af1afe177a1b88ea1cdcc0e41181c2c73e83"></a><a name="gga9c1d6e7df4468671742cb76f72b67af1afe177a1b88ea1cdcc0e41181c2c73e83"></a></strong>PROCESSING_ERROR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p548238215084825"><a name="p548238215084825"></a><a name="p548238215084825"></a>Error </p>
 </td>
</tr>
</tbody>
</table>

## Protocol80211IfType<a name="gac69954f56fcc99fc8aac68aa157831c7"></a>

```
enum [Protocol80211IfType](WLAN.md#gac69954f56fcc99fc8aac68aa157831c7)
```

 **Description:**

Enumerates 802.11 network port types, including AP, STA, and P2P. 

<a name="table535401738084825"></a>
<table><thead align="left"><tr id="row399052847084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1607988228084825"><a name="p1607988228084825"></a><a name="p1607988228084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1458429114084825"><a name="p1458429114084825"></a><a name="p1458429114084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1351592817084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7a6b209b916aabd18f2a950a82e68b6a4c"><a name="ggac69954f56fcc99fc8aac68aa157831c7a6b209b916aabd18f2a950a82e68b6a4c"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7a6b209b916aabd18f2a950a82e68b6a4c"></a></strong>PROTOCOL_80211_IFTYPE_UNSPECIFIED&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p409261941084825"><a name="p409261941084825"></a><a name="p409261941084825"></a>Unspecified </p>
 </td>
</tr>
<tr id="row504968125084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7a0926a98ddc2ceec4ba58ebfc01c5fe35"><a name="ggac69954f56fcc99fc8aac68aa157831c7a0926a98ddc2ceec4ba58ebfc01c5fe35"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7a0926a98ddc2ceec4ba58ebfc01c5fe35"></a></strong>PROTOCOL_80211_IFTYPE_ADHOC&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p693974866084825"><a name="p693974866084825"></a><a name="p693974866084825"></a>Ad hoc network </p>
 </td>
</tr>
<tr id="row459814942084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7acd26f8cefbd658e9ea02feecefd054fb"><a name="ggac69954f56fcc99fc8aac68aa157831c7acd26f8cefbd658e9ea02feecefd054fb"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7acd26f8cefbd658e9ea02feecefd054fb"></a></strong>PROTOCOL_80211_IFTYPE_STATION&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1744001151084825"><a name="p1744001151084825"></a><a name="p1744001151084825"></a>Workstation </p>
 </td>
</tr>
<tr id="row1040263096084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7a9e92654b9ab6ed6eb62868f1e0e4ea8f"><a name="ggac69954f56fcc99fc8aac68aa157831c7a9e92654b9ab6ed6eb62868f1e0e4ea8f"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7a9e92654b9ab6ed6eb62868f1e0e4ea8f"></a></strong>PROTOCOL_80211_IFTYPE_AP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1922974578084825"><a name="p1922974578084825"></a><a name="p1922974578084825"></a>Access point </p>
 </td>
</tr>
<tr id="row626691535084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7a991ad1a3f8c43b06c4eeb9dc88acdb1e"><a name="ggac69954f56fcc99fc8aac68aa157831c7a991ad1a3f8c43b06c4eeb9dc88acdb1e"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7a991ad1a3f8c43b06c4eeb9dc88acdb1e"></a></strong>PROTOCOL_80211_IFTYPE_AP_VLAN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p943380556084825"><a name="p943380556084825"></a><a name="p943380556084825"></a>Virtual access point </p>
 </td>
</tr>
<tr id="row1222548382084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7aa25631c32cd6c996a7c96ba4f61299e2"><a name="ggac69954f56fcc99fc8aac68aa157831c7aa25631c32cd6c996a7c96ba4f61299e2"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7aa25631c32cd6c996a7c96ba4f61299e2"></a></strong>PROTOCOL_80211_IFTYPE_WDS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1939595828084825"><a name="p1939595828084825"></a><a name="p1939595828084825"></a>Wireless distributed system </p>
 </td>
</tr>
<tr id="row2110171063084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7a3ff1c1358af5a0c50b64e0ef0e96a970"><a name="ggac69954f56fcc99fc8aac68aa157831c7a3ff1c1358af5a0c50b64e0ef0e96a970"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7a3ff1c1358af5a0c50b64e0ef0e96a970"></a></strong>PROTOCOL_80211_IFTYPE_MONITOR&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1624624423084825"><a name="p1624624423084825"></a><a name="p1624624423084825"></a>Listening </p>
 </td>
</tr>
<tr id="row136315009084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7a382756b8a71015cd536cdbc113c4f483"><a name="ggac69954f56fcc99fc8aac68aa157831c7a382756b8a71015cd536cdbc113c4f483"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7a382756b8a71015cd536cdbc113c4f483"></a></strong>PROTOCOL_80211_IFTYPE_MESH_POINT&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1044289709084825"><a name="p1044289709084825"></a><a name="p1044289709084825"></a>Mesh network </p>
 </td>
</tr>
<tr id="row196829250084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7acfd81d6e484c6f7a3b863327af112cfc"><a name="ggac69954f56fcc99fc8aac68aa157831c7acfd81d6e484c6f7a3b863327af112cfc"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7acfd81d6e484c6f7a3b863327af112cfc"></a></strong>PROTOCOL_80211_IFTYPE_P2P_CLIENT&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p658213625084825"><a name="p658213625084825"></a><a name="p658213625084825"></a>P2P client </p>
 </td>
</tr>
<tr id="row1268725016084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7abca0ccb5cf4c14af9b6ff0bd9eeb4173"><a name="ggac69954f56fcc99fc8aac68aa157831c7abca0ccb5cf4c14af9b6ff0bd9eeb4173"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7abca0ccb5cf4c14af9b6ff0bd9eeb4173"></a></strong>PROTOCOL_80211_IFTYPE_P2P_GO&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1894326650084825"><a name="p1894326650084825"></a><a name="p1894326650084825"></a>P2P group owner </p>
 </td>
</tr>
<tr id="row2146430040084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7ad63ad4a5a66892e842e4d75cc82b0755"><a name="ggac69954f56fcc99fc8aac68aa157831c7ad63ad4a5a66892e842e4d75cc82b0755"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7ad63ad4a5a66892e842e4d75cc82b0755"></a></strong>PROTOCOL_80211_IFTYPE_P2P_DEVICE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1592191657084825"><a name="p1592191657084825"></a><a name="p1592191657084825"></a>P2P device </p>
 </td>
</tr>
<tr id="row1326753949084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7a7f1fa9726ab20597baaa9ebf884b26cd"><a name="ggac69954f56fcc99fc8aac68aa157831c7a7f1fa9726ab20597baaa9ebf884b26cd"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7a7f1fa9726ab20597baaa9ebf884b26cd"></a></strong>PROTOCOL_80211_IFTYPE_NUM&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1047648419084825"><a name="p1047648419084825"></a><a name="p1047648419084825"></a>Number of network ports </p>
 </td>
</tr>
<tr id="row108476108084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggac69954f56fcc99fc8aac68aa157831c7a37b72ea7c4cd81dd4c427e2d721c9499"><a name="ggac69954f56fcc99fc8aac68aa157831c7a37b72ea7c4cd81dd4c427e2d721c9499"></a><a name="ggac69954f56fcc99fc8aac68aa157831c7a37b72ea7c4cd81dd4c427e2d721c9499"></a></strong>PROTOCOL_80211_IFTYPE_MAX&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1293171931084825"><a name="p1293171931084825"></a><a name="p1293171931084825"></a>Maximum number of 802.11 network port types </p>
 </td>
</tr>
</tbody>
</table>

## WifiBusType<a name="ga1c5537e64f05b5e91b951ddeb66d4261"></a>

```
enum [WifiBusType](WLAN.md#ga1c5537e64f05b5e91b951ddeb66d4261)
```

 **Description:**

Enumerates bus types of a WLAN module. 

<a name="table1057131122084825"></a>
<table><thead align="left"><tr id="row99601160084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1740787443084825"><a name="p1740787443084825"></a><a name="p1740787443084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1769967813084825"><a name="p1769967813084825"></a><a name="p1769967813084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row100760427084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga1c5537e64f05b5e91b951ddeb66d4261a0eba50f5eecb33326083a82adbaa0848"><a name="gga1c5537e64f05b5e91b951ddeb66d4261a0eba50f5eecb33326083a82adbaa0848"></a><a name="gga1c5537e64f05b5e91b951ddeb66d4261a0eba50f5eecb33326083a82adbaa0848"></a></strong>BUS_SDIO&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1750853404084825"><a name="p1750853404084825"></a><a name="p1750853404084825"></a>Secure Digital Input and Output (SDIO) </p>
 </td>
</tr>
<tr id="row299404040084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga1c5537e64f05b5e91b951ddeb66d4261a2f4f9ff60278d511660c21e211133666"><a name="gga1c5537e64f05b5e91b951ddeb66d4261a2f4f9ff60278d511660c21e211133666"></a><a name="gga1c5537e64f05b5e91b951ddeb66d4261a2f4f9ff60278d511660c21e211133666"></a></strong>BUS_USB&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p874954555084825"><a name="p874954555084825"></a><a name="p874954555084825"></a>Universal Serial Bus (USB) </p>
 </td>
</tr>
</tbody>
</table>

## WifiChannelType<a name="ga9d902b330de99c24b2a8c3ba7120af21"></a>

```
enum [WifiChannelType](WLAN.md#ga9d902b330de99c24b2a8c3ba7120af21)
```

 **Description:**

Enumerates channel types. 

<a name="table1076603210084825"></a>
<table><thead align="left"><tr id="row1949263716084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2098505268084825"><a name="p2098505268084825"></a><a name="p2098505268084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p821540686084825"><a name="p821540686084825"></a><a name="p821540686084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1036452313084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9d902b330de99c24b2a8c3ba7120af21ae0707e29a1748ee7f33d51acabaf8810"><a name="gga9d902b330de99c24b2a8c3ba7120af21ae0707e29a1748ee7f33d51acabaf8810"></a><a name="gga9d902b330de99c24b2a8c3ba7120af21ae0707e29a1748ee7f33d51acabaf8810"></a></strong>WIFI_CHAN_NO_HT&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115409553084825"><a name="p115409553084825"></a><a name="p115409553084825"></a>non-HT channel </p>
 </td>
</tr>
<tr id="row2138176507084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9d902b330de99c24b2a8c3ba7120af21a255f513fd4efa8bce0c015086e0588ea"><a name="gga9d902b330de99c24b2a8c3ba7120af21a255f513fd4efa8bce0c015086e0588ea"></a><a name="gga9d902b330de99c24b2a8c3ba7120af21a255f513fd4efa8bce0c015086e0588ea"></a></strong>WIFI_CHAN_HT20&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491342379084825"><a name="p491342379084825"></a><a name="p491342379084825"></a>20 MHz HT channel </p>
 </td>
</tr>
<tr id="row1877766326084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9d902b330de99c24b2a8c3ba7120af21a1c6dbd2c2f6be59e4fa8312fe6009a98"><a name="gga9d902b330de99c24b2a8c3ba7120af21a1c6dbd2c2f6be59e4fa8312fe6009a98"></a><a name="gga9d902b330de99c24b2a8c3ba7120af21a1c6dbd2c2f6be59e4fa8312fe6009a98"></a></strong>WIFI_CHAN_HT40MINUS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p124645629084825"><a name="p124645629084825"></a><a name="p124645629084825"></a>40 MHz minus HT channel (The channel is formed by two 20 MHz HT channels, one as the main channel and the other as the auxiliary channel. The center frequency of the main channel is lower than that of the auxiliary channel.) </p>
 </td>
</tr>
<tr id="row2003569571084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga9d902b330de99c24b2a8c3ba7120af21abdc85daa4bd2fdda2cfb14a975099652"><a name="gga9d902b330de99c24b2a8c3ba7120af21abdc85daa4bd2fdda2cfb14a975099652"></a><a name="gga9d902b330de99c24b2a8c3ba7120af21abdc85daa4bd2fdda2cfb14a975099652"></a></strong>WIFI_CHAN_HT40PLUS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p79581498084825"><a name="p79581498084825"></a><a name="p79581498084825"></a>40 MHz plus HT channel (The channel is formed by two 20 MHz HT channels, one as the main channel and the other as the auxiliary channel. The center frequency of the main channel is higher than that of the auxiliary channel.) </p>
 </td>
</tr>
</tbody>
</table>

## WifiHmacMgmtStatus<a name="gaf3e873b51f0cfa077aca9d33ed7a0960"></a>

```
enum [WifiHmacMgmtStatus](WLAN.md#gaf3e873b51f0cfa077aca9d33ed7a0960)
```

 **Description:**

Enumerates MLME management statuses, indicating whether a device is successfully associated or fails to be associated. 

<a name="table1361141536084825"></a>
<table><thead align="left"><tr id="row438491674084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1197294853084825"><a name="p1197294853084825"></a><a name="p1197294853084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p163523836084825"><a name="p163523836084825"></a><a name="p163523836084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1601213972084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf3e873b51f0cfa077aca9d33ed7a0960ad9c7e2f362bd6fcadef189fa2a5d7c63"><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960ad9c7e2f362bd6fcadef189fa2a5d7c63"></a><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960ad9c7e2f362bd6fcadef189fa2a5d7c63"></a></strong>WIFI_HMAC_MGMT_SUCCESS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832226048084825"><a name="p832226048084825"></a><a name="p832226048084825"></a>Association succeeds </p>
 </td>
</tr>
<tr id="row2024455518084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf3e873b51f0cfa077aca9d33ed7a0960a539c65a358a20b9731fc66fc60ebcbc2"><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960a539c65a358a20b9731fc66fc60ebcbc2"></a><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960a539c65a358a20b9731fc66fc60ebcbc2"></a></strong>WIFI_HMAC_MGMT_INVALID&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p874664992084825"><a name="p874664992084825"></a><a name="p874664992084825"></a>Association fails </p>
 </td>
</tr>
<tr id="row1339528257084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf3e873b51f0cfa077aca9d33ed7a0960ad1731acef8ddb8c50bcc26ae80fa83a3"><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960ad1731acef8ddb8c50bcc26ae80fa83a3"></a><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960ad1731acef8ddb8c50bcc26ae80fa83a3"></a></strong>WIFI_HMAC_MGMT_TIMEOUT&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367195348084825"><a name="p1367195348084825"></a><a name="p1367195348084825"></a>Association timeout </p>
 </td>
</tr>
<tr id="row1457873471084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf3e873b51f0cfa077aca9d33ed7a0960a05f532edadae3b6afc80b7575dd46961"><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960a05f532edadae3b6afc80b7575dd46961"></a><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960a05f532edadae3b6afc80b7575dd46961"></a></strong>WIFI_HMAC_MGMT_REFUSED&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p684807123084825"><a name="p684807123084825"></a><a name="p684807123084825"></a>Association refused </p>
 </td>
</tr>
<tr id="row1395363319084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf3e873b51f0cfa077aca9d33ed7a0960a9e241ef81e72de130e1fda573ce2a412"><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960a9e241ef81e72de130e1fda573ce2a412"></a><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960a9e241ef81e72de130e1fda573ce2a412"></a></strong>WIFI_HMAC_MGMT_TOMANY_REQ&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1783025279084825"><a name="p1783025279084825"></a><a name="p1783025279084825"></a>Repeated association request </p>
 </td>
</tr>
<tr id="row959989132084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaf3e873b51f0cfa077aca9d33ed7a0960aa3db4634dc2727e029aef13384bc3940"><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960aa3db4634dc2727e029aef13384bc3940"></a><a name="ggaf3e873b51f0cfa077aca9d33ed7a0960aa3db4634dc2727e029aef13384bc3940"></a></strong>WIFI_HMAC_MGMT_ALREADY_BSS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p530447604084825"><a name="p530447604084825"></a><a name="p530447604084825"></a>Associated with the BSS </p>
 </td>
</tr>
</tbody>
</table>

## WifiMainFeatureType<a name="gaec03ba36d71cc2d5f3209bc24aa6ee10"></a>

```
enum [WifiMainFeatureType](WLAN.md#gaec03ba36d71cc2d5f3209bc24aa6ee10)
```

 **Description:**

Enumerates feature types of a WLAN module. 

You can query and register a feature or bind a feature to a WLAN module based on the feature type.

<a name="table1457289026084825"></a>
<table><thead align="left"><tr id="row783774269084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p738652082084825"><a name="p738652082084825"></a><a name="p738652082084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p563161916084825"><a name="p563161916084825"></a><a name="p563161916084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row846320803084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaec03ba36d71cc2d5f3209bc24aa6ee10a038fb1847d290b75b15949b6471b46ad"><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10a038fb1847d290b75b15949b6471b46ad"></a><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10a038fb1847d290b75b15949b6471b46ad"></a></strong>HDF_WIFI_FEATURE_BASE&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2089733529084825"><a name="p2089733529084825"></a><a name="p2089733529084825"></a>Base feature </p>
 </td>
</tr>
<tr id="row1127634952084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaec03ba36d71cc2d5f3209bc24aa6ee10aaec6c1686d47187e64fd108e0e797133"><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10aaec6c1686d47187e64fd108e0e797133"></a><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10aaec6c1686d47187e64fd108e0e797133"></a></strong>HDF_WIFI_FEATURE_AP&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p495292062084825"><a name="p495292062084825"></a><a name="p495292062084825"></a>AP </p>
 </td>
</tr>
<tr id="row1868430574084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaec03ba36d71cc2d5f3209bc24aa6ee10a0e814bd1cfc59a253cc575d3548a9d4e"><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10a0e814bd1cfc59a253cc575d3548a9d4e"></a><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10a0e814bd1cfc59a253cc575d3548a9d4e"></a></strong>HDF_WIFI_FEATURE_STA&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1770685530084825"><a name="p1770685530084825"></a><a name="p1770685530084825"></a>Station </p>
 </td>
</tr>
<tr id="row49156929084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaec03ba36d71cc2d5f3209bc24aa6ee10a8e87c1727fa86bf92ee05cad85e7f872"><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10a8e87c1727fa86bf92ee05cad85e7f872"></a><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10a8e87c1727fa86bf92ee05cad85e7f872"></a></strong>HDF_WIFI_FEATURE_P2P&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1386362503084825"><a name="p1386362503084825"></a><a name="p1386362503084825"></a>Peer-to-peer (P2P) </p>
 </td>
</tr>
<tr id="row1643629778084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaec03ba36d71cc2d5f3209bc24aa6ee10ae30b51638bc2c2fb739b3ddec6c5b92b"><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10ae30b51638bc2c2fb739b3ddec6c5b92b"></a><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10ae30b51638bc2c2fb739b3ddec6c5b92b"></a></strong>HDF_WIFI_FEATURE_NAN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422751661084825"><a name="p422751661084825"></a><a name="p422751661084825"></a>Neighbor Awareness Networking (NAN) </p>
 </td>
</tr>
<tr id="row273992029084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaec03ba36d71cc2d5f3209bc24aa6ee10ac12422e335003fbd392bff47c53c0352"><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10ac12422e335003fbd392bff47c53c0352"></a><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10ac12422e335003fbd392bff47c53c0352"></a></strong>HDF_WIFI_FEATURE_RTT&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p37543660084825"><a name="p37543660084825"></a><a name="p37543660084825"></a>Round Trip Time (RTT) </p>
 </td>
</tr>
<tr id="row729517068084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggaec03ba36d71cc2d5f3209bc24aa6ee10a28ff5971d579c1754e03a5f79a0c9e6f"><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10a28ff5971d579c1754e03a5f79a0c9e6f"></a><a name="ggaec03ba36d71cc2d5f3209bc24aa6ee10a28ff5971d579c1754e03a5f79a0c9e6f"></a></strong>HDF_WIFI_FEATURE_NUM&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466187179084825"><a name="p1466187179084825"></a><a name="p1466187179084825"></a>Maximum number of features </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section1015084783084825"></a>

## AddFeature\(\)<a name="gae928a69366143780650b73c6b030c3a7"></a>

```
int32_t AddFeature (struct [WifiModule](WifiModule.md) * module, uint16_t featureType, struct [WifiFeature](WifiFeature.md) * featureData )
```

 **Description:**

Adds a specified feature to a specified module. 

**Parameters:**

<a name="table2033287049084825"></a>
<table><thead align="left"><tr id="row2883893084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p214632228084825"><a name="p214632228084825"></a><a name="p214632228084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1190124384084825"><a name="p1190124384084825"></a><a name="p1190124384084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1577495337084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">module</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the module. </td>
</tr>
<tr id="row1882809258084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">featureType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the type of the feature to add. </td>
</tr>
<tr id="row1499040342084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">featureData</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the feature to add.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the feature is added successfully; returns a negative value otherwise.



## DelFeature\(\)<a name="ga395848b77fc10f2213d5b12793861292"></a>

```
int32_t DelFeature (struct [WifiModule](WifiModule.md) * module, uint16_t featureType )
```

 **Description:**

Deletes a specified feature from a specified module. 

**Parameters:**

<a name="table2033994915084825"></a>
<table><thead align="left"><tr id="row1993926386084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2054993774084825"><a name="p2054993774084825"></a><a name="p2054993774084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p474719577084825"><a name="p474719577084825"></a><a name="p474719577084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1176180715084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">module</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the module. </td>
</tr>
<tr id="row227489830084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">featureType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the type of the feature to delete.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the feature is deleted successfully; returns  **-1**  otherwise.



## HdfWifiEventConnectResult\(\)<a name="gaf9e61f36e11d7d2e94e7969a8ecf22f1"></a>

```
int32_t HdfWifiEventConnectResult (const struct [NetDevice](NetDevice.md) * netdev, const struct [ConnetResult](ConnetResult.md) * result )
```

 **Description:**

Reports a connection result event. 

**Parameters:**

<a name="table1592915029084825"></a>
<table><thead align="left"><tr id="row1877376506084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1930348602084825"><a name="p1930348602084825"></a><a name="p1930348602084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p198899879084825"><a name="p198899879084825"></a><a name="p198899879084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2132569139084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null. </td>
</tr>
<tr id="row832036829084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">result</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the connection result. This parameter cannot be null.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiEventCsaChannelSwitch\(\)<a name="ga2aa62f7e8e72e8f9df0b2101c08a9d44"></a>

```
int32_t HdfWifiEventCsaChannelSwitch (const struct [NetDevice](NetDevice.md) * netdev, int32_t freq )
```

 **Description:**

Reports a CSA channel switching event. 

**Parameters:**

<a name="table1692033283084825"></a>
<table><thead align="left"><tr id="row1592900603084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2049019411084825"><a name="p2049019411084825"></a><a name="p2049019411084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p616654968084825"><a name="p616654968084825"></a><a name="p616654968084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1806817853084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null. </td>
</tr>
<tr id="row1572678873084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">freq</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frequency of the channel.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiEventDelSta\(\)<a name="ga208ef54b2a601f416a472bb1e21fae7e"></a>

```
int32_t HdfWifiEventDelSta (struct [NetDevice](NetDevice.md) * netdev, const uint8_t * macAddr, uint8_t addrLen )
```

 **Description:**

Reports a station deletion event. 

**Parameters:**

<a name="table1841464767084825"></a>
<table><thead align="left"><tr id="row512681258084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1894571001084825"><a name="p1894571001084825"></a><a name="p1894571001084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p256226522084825"><a name="p256226522084825"></a><a name="p256226522084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row5326428084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null. </td>
</tr>
<tr id="row93504872084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">macAddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the MAC address of the station. This parameter cannot be null. </td>
</tr>
<tr id="row2139341793084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addrLen</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the MAC address of the station. The length is fixed to six bytes.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiEventDisconnected\(\)<a name="ga58b1a613d784233a1e84027079e1ea57"></a>

```
int32_t HdfWifiEventDisconnected (const struct [NetDevice](NetDevice.md) * netdev, uint16_t reason, const uint8_t * ie, uint32_t len )
```

 **Description:**

Reports a disconnection event. 

**Parameters:**

<a name="table464849866084825"></a>
<table><thead align="left"><tr id="row1818612093084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p247491845084825"><a name="p247491845084825"></a><a name="p247491845084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1592528690084825"><a name="p1592528690084825"></a><a name="p1592528690084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2007318966084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null. </td>
</tr>
<tr id="row1069714762084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">reason</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the reason for disconnection. </td>
</tr>
<tr id="row416953077084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ie</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the deauth/disassoc frame IE. </td>
</tr>
<tr id="row1284984457084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ieLen</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the deauth/disassoc IE.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiEventEapolRecv\(\)<a name="ga3e60f4568723471226107848ddbe582f"></a>

```
int32_t HdfWifiEventEapolRecv (const char * name, void * context )
```

 **Description:**

Reports the event of receiving the EAPOL frame and notifies WPA to read the EAPOL frame. 

**Parameters:**

<a name="table1832418724084825"></a>
<table><thead align="left"><tr id="row949387462084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1517157932084825"><a name="p1517157932084825"></a><a name="p1517157932084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p212720454084825"><a name="p212720454084825"></a><a name="p212720454084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1409587081084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network port name, for example, <strong id="b241081277084825"><a name="b241081277084825"></a><a name="b241081277084825"></a>wlan0</strong>. </td>
</tr>
<tr id="row1559309539084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">context</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the context. This parameter is reserved.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns  **-1**  otherwise.



## HdfWifiEventInformBssFrame\(\)<a name="ga941675fb683212e6e0d8e1529b300482"></a>

```
int32_t HdfWifiEventInformBssFrame (const struct [NetDevice](NetDevice.md) * netdev, struct [Wiphy](Wiphy.md) * wiphy, const struct [Ieee80211Channel](Ieee80211Channel.md) * channel, const struct [ScannedBssInfo](ScannedBssInfo.md) * bssInfo )
```

 **Description:**

Reports a scanned BSS event. 

**Parameters:**

<a name="table127747350084825"></a>
<table><thead align="left"><tr id="row2140910705084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p549432545084825"><a name="p549432545084825"></a><a name="p549432545084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p500657244084825"><a name="p500657244084825"></a><a name="p500657244084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row840224470084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null. </td>
</tr>
<tr id="row1511658536084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">wiphy</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the physical layer of the wireless network. This parameter cannot be null. </td>
</tr>
<tr id="row1763827889084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">channel</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the channel information. This parameter cannot be null. </td>
</tr>
<tr id="row1337650342084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">bssInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the BSS information. This parameter cannot be null.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiEventMgmtTxStatus\(\)<a name="ga1721c7e1b5af0240a663ea9f0fe12854"></a>

```
int32_t HdfWifiEventMgmtTxStatus (const struct [NetDevice](NetDevice.md) * netdev, const uint8_t * buf, size_t len, uint8_t ack )
```

 **Description:**

Reports a transmission management status event. 

**Parameters:**

<a name="table1603911965084825"></a>
<table><thead align="left"><tr id="row897710611084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1262464366084825"><a name="p1262464366084825"></a><a name="p1262464366084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1398877106084825"><a name="p1398877106084825"></a><a name="p1398877106084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row117328289084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null. </td>
</tr>
<tr id="row702103627084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the transmission management frame. This parameter cannot be null. </td>
</tr>
<tr id="row577771794084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the transmission management frame. </td>
</tr>
<tr id="row359044531084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ack</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates whether the transmission management frame is acknowledged.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiEventNewSta\(\)<a name="ga31edc1e9de8835e0e8a9c1e89fad3bd9"></a>

```
int32_t HdfWifiEventNewSta (const struct [NetDevice](NetDevice.md) * netdev, const uint8_t * macAddr, uint8_t addrLen, const struct [StationInfo](StationInfo.md) * info )
```

 **Description:**

Reports a new STA event. 

**Parameters:**

<a name="table510906649084825"></a>
<table><thead align="left"><tr id="row1021194223084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p611426353084825"><a name="p611426353084825"></a><a name="p611426353084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p60415584084825"><a name="p60415584084825"></a><a name="p60415584084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row8164749084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null. </td>
</tr>
<tr id="row1083379060084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">macAddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the MAC address of the station. This parameter cannot be null. </td>
</tr>
<tr id="row1624980898084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">addrLen</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the MAC address of the station. The length is fixed to six bytes. </td>
</tr>
<tr id="row1587527012084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">info</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the station information.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiEventRxMgmt\(\)<a name="gad47d56e4332ccd14116368444a4b330f"></a>

```
int32_t HdfWifiEventRxMgmt (const struct [NetDevice](NetDevice.md) * netdev, int32_t freq, int32_t sigMbm, const uint8_t * buf, size_t len )
```

 **Description:**

Reports a receive management status event. 

**Parameters:**

<a name="table1186638323084825"></a>
<table><thead align="left"><tr id="row1261873961084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1882640396084825"><a name="p1882640396084825"></a><a name="p1882640396084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2009065827084825"><a name="p2009065827084825"></a><a name="p2009065827084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1140644472084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null. </td>
</tr>
<tr id="row513651633084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">freq</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the frequency of receiving management frame. </td>
</tr>
<tr id="row1451872646084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">sigMbm</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the signal strength (in dBm). </td>
</tr>
<tr id="row1583306451084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the receive management frame. This parameter cannot be null. </td>
</tr>
<tr id="row132037282084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the receive management frame.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiEventScanDone\(\)<a name="ga41efbd6788a80604b81ae117a363b657"></a>

```
int32_t HdfWifiEventScanDone (const struct [NetDevice](NetDevice.md) * netdev, WifiScanStatus status )
```

 **Description:**

Reports a scanning completion event. 

**Parameters:**

<a name="table409142818084825"></a>
<table><thead align="left"><tr id="row639749796084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p333396771084825"><a name="p333396771084825"></a><a name="p333396771084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2099822703084825"><a name="p2099822703084825"></a><a name="p2099822703084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1515165168084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null. </td>
</tr>
<tr id="row1544817373084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">status</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the scanning completion status. Value <strong id="b740812969084825"><a name="b740812969084825"></a><a name="b740812969084825"></a>0</strong> indicates that the scanning is successful, and other values indicate that the scanning fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiEventTimeoutDisconnected\(\)<a name="gafda13471995c91e65326a9aa374ae1c9"></a>

```
int32_t HdfWifiEventTimeoutDisconnected (const struct [NetDevice](NetDevice.md) * netdev)
```

 **Description:**

Reports a timeout disconnection event. 

**Parameters:**

<a name="table550557718084825"></a>
<table><thead align="left"><tr id="row1597321842084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1072784194084825"><a name="p1072784194084825"></a><a name="p1072784194084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2020497786084825"><a name="p2020497786084825"></a><a name="p2020497786084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row983772835084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. This parameter cannot be null.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the event is reported successfully; returns  **-1**  otherwise.



## HdfWifiGetProduct\(\)<a name="ga77f15efb80095134d08cc63b62229f21"></a>

```
struct [HdfWifiProductData](HdfWifiProductData.md)* HdfWifiGetProduct (void )
```

 **Description:**

Obtains the data structure of the WLAN module. 

**Returns:**

Returns the pointer to the data structure of the WLAN module. For details, see  [HdfWifiProductData](HdfWifiProductData.md).



## Mac80211GetOps\(\)<a name="gad7c34413d81d55ba090c90404d340c8a"></a>

```
struct [WifiMac80211Ops](WifiMac80211Ops.md)* Mac80211GetOps (void )
```

 **Description:**

Obtains the  [WifiMac80211Ops](WifiMac80211Ops.md)  object that the driver needs to implement. 

**Returns:**

Returns the pointer to the  [WifiMac80211Ops](WifiMac80211Ops.md)  object.



## Mac80211RegisterOps\(\)<a name="ga6542a735af0fe7496789c3c55380adfa"></a>

```
int32_t Mac80211RegisterOps (struct [WifiMac80211Ops](WifiMac80211Ops.md) * ops)
```

 **Description:**

Registers a  [WifiMac80211Ops](WifiMac80211Ops.md)  object. 

**Parameters:**

<a name="table488596691084825"></a>
<table><thead align="left"><tr id="row267296750084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p23291870084825"><a name="p23291870084825"></a><a name="p23291870084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p464842662084825"><a name="p464842662084825"></a><a name="p464842662084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row769382077084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ops</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="WifiMac80211Ops.md">WifiMac80211Ops</a> object to register.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the  [WifiMac80211Ops](WifiMac80211Ops.md)  object is registered successfully; returns a non-zero value otherwise.



## NetBuf2Pbuf\(\)<a name="ga88e4943fc1b1f4e31f388bf8eec57476"></a>

```
struct pbuf* NetBuf2Pbuf (const struct [NetBuf](NetBuf.md) * nb)
```

 **Description:**

Converts a network data buffer to the  **pbuf**  structure of Lightweight TCP/IP Stack \(lwIP\). 

**Parameters:**

<a name="table1019191739084825"></a>
<table><thead align="left"><tr id="row2009113369084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1204936178084825"><a name="p1204936178084825"></a><a name="p1204936178084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2017054093084825"><a name="p2017054093084825"></a><a name="p2017054093084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row378895340084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the  **pbuf**  structure if the operation is successful; returns  **NULL**  otherwise.



## NetBufAlloc\(\)<a name="ga5ced2af63a9064b0e33d0aa4e86b3fc1"></a>

```
struct [NetBuf](NetBuf.md)* NetBufAlloc (uint32_t size)
```

 **Description:**

Applies for a network data buffer. 

**Parameters:**

<a name="table706370727084825"></a>
<table><thead align="left"><tr id="row82438308084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p9331254084825"><a name="p9331254084825"></a><a name="p9331254084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1699870010084825"><a name="p1699870010084825"></a><a name="p1699870010084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1721768246084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the network data buffer.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the network data buffer if the operation is successful; returns  **NULL**  otherwise.



## NetBufConcat\(\)<a name="ga89ee14a3da1b7b83325045af9c488ef8"></a>

```
uint32_t NetBufConcat (struct [NetBuf](NetBuf.md) * nb, struct [NetBuf](NetBuf.md) * cnb )
```

 **Description:**

Copies data in a network data buffer to another network data buffer. 

**Parameters:**

<a name="table636927648084825"></a>
<table><thead align="left"><tr id="row551192855084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p450546301084825"><a name="p450546301084825"></a><a name="p450546301084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p837045150084825"><a name="p837045150084825"></a><a name="p837045150084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1016847557084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer. </td>
</tr>
<tr id="row831764964084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">cnb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target network data buffer.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetBufDevAlloc\(\)<a name="ga74198f03268aadc025f6b76056b09604"></a>

```
struct [NetBuf](NetBuf.md)* NetBufDevAlloc (const struct [NetDevice](NetDevice.md) * dev, uint32_t size )
```

 **Description:**

Applies for a network data buffer based on the reserved space and requested size set by a network device. 

**Parameters:**

<a name="table432141247084825"></a>
<table><thead align="left"><tr id="row677987116084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p218181591084825"><a name="p218181591084825"></a><a name="p218181591084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p89893655084825"><a name="p89893655084825"></a><a name="p89893655084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1898274797084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. </td>
</tr>
<tr id="row1556385591084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the network data buffer applied.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the network data buffer if the operation is successful; returns  **NULL**  otherwise.



## NetBufFree\(\)<a name="ga9320642699593dfecd79dc30132dd4eb"></a>

```
void NetBufFree (struct [NetBuf](NetBuf.md) * nb)
```

 **Description:**

Releases a network data buffer. 

**Parameters:**

<a name="table58895819084825"></a>
<table><thead align="left"><tr id="row1632522755084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1946492382084825"><a name="p1946492382084825"></a><a name="p1946492382084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p199980292084825"><a name="p199980292084825"></a><a name="p199980292084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row672521012084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer.</td>
</tr>
</tbody>
</table>

## NetBufGetAddress\(\)<a name="gacd40d5004291b4aaa5c27703d9379c9c"></a>

```
static uint8_t* NetBufGetAddress (const struct [NetBuf](NetBuf.md) * nb, uint32_t id )
```

 **Description:**

Obtains the address of a specified buffer segment in a network data buffer. 

**Parameters:**

<a name="table1633634850084825"></a>
<table><thead align="left"><tr id="row296826106084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2116512753084825"><a name="p2116512753084825"></a><a name="p2116512753084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1105003926084825"><a name="p1105003926084825"></a><a name="p1105003926084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1808491531084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer. </td>
</tr>
<tr id="row782284810084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer segment ID.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the address of the specified buffer segment if the operation is successful; returns  **NULL**  if the buffer segment ID is invalid.



## NetBufGetDataLen\(\)<a name="ga67eeb57ebe467b9caa4f31734955727b"></a>

```
static uint32_t NetBufGetDataLen (const struct [NetBuf](NetBuf.md) * nb)
```

 **Description:**

Obtains the actual data length of the data segment of a network data buffer. 

**Parameters:**

<a name="table1903859455084825"></a>
<table><thead align="left"><tr id="row1529107245084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2003124469084825"><a name="p2003124469084825"></a><a name="p2003124469084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1234925514084825"><a name="p1234925514084825"></a><a name="p1234925514084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1235178608084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the actual data length of the data segment.



## NetBufGetRoom\(\)<a name="ga09245834fe9f55fe475a0dc226a6a709"></a>

```
static uint32_t NetBufGetRoom (const struct [NetBuf](NetBuf.md) * nb, uint32_t id )
```

 **Description:**

Obtains the size of a specified buffer segment space in a network data buffer. 

**Parameters:**

<a name="table1973849928084825"></a>
<table><thead align="left"><tr id="row260367438084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2088678736084825"><a name="p2088678736084825"></a><a name="p2088678736084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1090776237084825"><a name="p1090776237084825"></a><a name="p1090776237084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row293342593084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer. </td>
</tr>
<tr id="row1998600477084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer segment ID.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the size of the specified buffer segment space if the operation is successful; returns  **NULL**  if the buffer segment ID is invalid.



## NetBufPop\(\)<a name="ga81f298aebc5b7772f173e2f6fadc004f"></a>

```
void* NetBufPop (struct [NetBuf](NetBuf.md) * nb, uint32_t id, uint32_t len )
```

 **Description:**

Performs operations based on the segment ID of a network data buffer. The function is opposite to that of  [NetBufPush](WLAN.md#gac4ec1cedef616e61038dcb6dbf67d204). 

Description: 

**Parameters:**

<a name="table101262207084825"></a>
<table><thead align="left"><tr id="row1116013269084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p222882489084825"><a name="p222882489084825"></a><a name="p222882489084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p204984963084825"><a name="p204984963084825"></a><a name="p204984963084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1705082110084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer. </td>
</tr>
<tr id="row85481899084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer segment ID. </td>
</tr>
<tr id="row159782964084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the operation length.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the start address of the data segment if the operation is successful; returns  **NULL**  if the operation length exceeds the space of a specified buffer segment.



## NetBufPush\(\)<a name="gac4ec1cedef616e61038dcb6dbf67d204"></a>

```
void* NetBufPush (struct [NetBuf](NetBuf.md) * nb, uint32_t id, uint32_t len )
```

 **Description:**

Performs operations based on the segment ID of a network data buffer. The function is opposite to that of  [NetBufPop](WLAN.md#ga81f298aebc5b7772f173e2f6fadc004f). 

Description: 

**Parameters:**

<a name="table943895340084825"></a>
<table><thead align="left"><tr id="row628956639084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1111753536084825"><a name="p1111753536084825"></a><a name="p1111753536084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p698452348084825"><a name="p698452348084825"></a><a name="p698452348084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1963434856084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer. </td>
</tr>
<tr id="row1212181097084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">id</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the buffer segment ID. </td>
</tr>
<tr id="row1923955298084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the operation length.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the start address of the data segment if the operation is successful; returns  **NULL**  if the operation length exceeds the space of a specified buffer segment.



## NetBufQueueAtHead\(\)<a name="ga082b7a173ca09288c3b418ce4e4faa7d"></a>

```
static struct [NetBuf](NetBuf.md)* NetBufQueueAtHead (const struct [NetBufQueue](NetBufQueue.md) * q)
```

 **Description:**

Obtains the network data buffer from the header of a queue, without deleting it from the queue. 

**Parameters:**

<a name="table2019403601084825"></a>
<table><thead align="left"><tr id="row2087701031084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p325833559084825"><a name="p325833559084825"></a><a name="p325833559084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2017779077084825"><a name="p2017779077084825"></a><a name="p2017779077084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1364098188084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the first network data buffer if the queue is not empty; returns  **NULL**  otherwise.



## NetBufQueueAtTail\(\)<a name="ga9de36bf1db57bd4eb042e87cb63dae69"></a>

```
static struct [NetBuf](NetBuf.md)* NetBufQueueAtTail (const struct [NetBufQueue](NetBufQueue.md) * q)
```

 **Description:**

Obtains the network data buffer from the tail of a queue, without deleting it from the queue. 

**Parameters:**

<a name="table1880848766084825"></a>
<table><thead align="left"><tr id="row1135985305084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p700871293084825"><a name="p700871293084825"></a><a name="p700871293084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1594666553084825"><a name="p1594666553084825"></a><a name="p1594666553084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1299637122084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the last network data buffer if the queue is not empty; returns  **NULL**  otherwise.



## NetBufQueueClear\(\)<a name="ga79045ebd1636c27bee454e9541498f33"></a>

```
void NetBufQueueClear (struct [NetBufQueue](NetBufQueue.md) * q)
```

 **Description:**

Clears a network data buffer queue and releases the network data buffer in the queue. 

**Parameters:**

<a name="table1350643655084825"></a>
<table><thead align="left"><tr id="row305727807084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p315177614084825"><a name="p315177614084825"></a><a name="p315177614084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p335548625084825"><a name="p335548625084825"></a><a name="p335548625084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1097405778084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue.</td>
</tr>
</tbody>
</table>

## NetBufQueueConcat\(\)<a name="ga2331e6b8c8f1ac4f00f8a1206fb1a3d8"></a>

```
void NetBufQueueConcat (struct [NetBufQueue](NetBufQueue.md) * q, struct [NetBufQueue](NetBufQueue.md) * add )
```

 **Description:**

Moves all network data buffers from one queue to another and clears the source queue. 

**Parameters:**

<a name="table553965683084825"></a>
<table><thead align="left"><tr id="row900833810084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p797225047084825"><a name="p797225047084825"></a><a name="p797225047084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1208131202084825"><a name="p1208131202084825"></a><a name="p1208131202084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row918355131084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the target network data buffer queue. </td>
</tr>
<tr id="row1196382313084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">add</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the source network data buffer queue.</td>
</tr>
</tbody>
</table>

## NetBufQueueDequeue\(\)<a name="ga4ad66d7ca7aabda3aef08fa541dc9ee4"></a>

```
struct [NetBuf](NetBuf.md)* NetBufQueueDequeue (struct [NetBufQueue](NetBufQueue.md) * q)
```

 **Description:**

Obtains a network data buffer from the header of a queue and deletes it from the queue. 

**Parameters:**

<a name="table745387200084825"></a>
<table><thead align="left"><tr id="row865219746084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1565764402084825"><a name="p1565764402084825"></a><a name="p1565764402084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1117275983084825"><a name="p1117275983084825"></a><a name="p1117275983084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row146571075084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the first network data buffer if the queue is not empty; returns  **NULL**  otherwise.



## NetBufQueueDequeueTail\(\)<a name="ga390319a0419c26c73552bcee6b8d5c32"></a>

```
struct [NetBuf](NetBuf.md)* NetBufQueueDequeueTail (struct [NetBufQueue](NetBufQueue.md) * q)
```

 **Description:**

Obtains a network data buffer from the tail of a queue and deletes it from the queue. 

**Parameters:**

<a name="table1926534217084825"></a>
<table><thead align="left"><tr id="row841295201084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p68688612084825"><a name="p68688612084825"></a><a name="p68688612084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p655962627084825"><a name="p655962627084825"></a><a name="p655962627084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1361006269084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the last network data buffer if the queue is not empty; returns  **NULL**  otherwise.



## NetBufQueueEnqueue\(\)<a name="ga25bf5d56e8afec1bc80080b20c3b7daa"></a>

```
void NetBufQueueEnqueue (struct [NetBufQueue](NetBufQueue.md) * q, struct [NetBuf](NetBuf.md) * nb )
```

 **Description:**

Adds a network data buffer to the tail of a queue. 

**Parameters:**

<a name="table928929428084825"></a>
<table><thead align="left"><tr id="row396118832084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1509539391084825"><a name="p1509539391084825"></a><a name="p1509539391084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p736150721084825"><a name="p736150721084825"></a><a name="p736150721084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1244005007084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue. </td>
</tr>
<tr id="row1017983089084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer.</td>
</tr>
</tbody>
</table>

## NetBufQueueEnqueueHead\(\)<a name="ga5ebe7aff6d5187645869f067b0a8f659"></a>

```
void NetBufQueueEnqueueHead (struct [NetBufQueue](NetBufQueue.md) * q, struct [NetBuf](NetBuf.md) * nb )
```

 **Description:**

Adds a network data buffer to the header of a queue. 

**Parameters:**

<a name="table11680364084825"></a>
<table><thead align="left"><tr id="row25591013084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1349960060084825"><a name="p1349960060084825"></a><a name="p1349960060084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1896582020084825"><a name="p1896582020084825"></a><a name="p1896582020084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1018869113084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue. </td>
</tr>
<tr id="row592642816084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer.</td>
</tr>
</tbody>
</table>

## NetBufQueueInit\(\)<a name="ga6e754d5529b23b413d1fe00102a95db9"></a>

```
static void NetBufQueueInit (struct [NetBufQueue](NetBufQueue.md) * q)
```

 **Description:**

Initializes a network data buffer queue. 

**Parameters:**

<a name="table337753976084825"></a>
<table><thead align="left"><tr id="row1945497439084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p994368401084825"><a name="p994368401084825"></a><a name="p994368401084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1875661840084825"><a name="p1875661840084825"></a><a name="p1875661840084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row844062025084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue.</td>
</tr>
</tbody>
</table>

## NetBufQueueIsEmpty\(\)<a name="ga36297284c60746f2b6895d94ea5e2dc3"></a>

```
static bool NetBufQueueIsEmpty (const struct [NetBufQueue](NetBufQueue.md) * q)
```

 **Description:**

Checks whether the network data buffer queue is empty. 

**Parameters:**

<a name="table812722523084825"></a>
<table><thead align="left"><tr id="row1342501300084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p531773611084825"><a name="p531773611084825"></a><a name="p531773611084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1654173325084825"><a name="p1654173325084825"></a><a name="p1654173325084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1844268549084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the queue is empty; returns  **false**  otherwise.



## NetBufQueueSize\(\)<a name="gaaa5c00efd1dedecf846af4dd108b6701"></a>

```
static uint32_t NetBufQueueSize (const struct [NetBufQueue](NetBufQueue.md) * q)
```

 **Description:**

Obtains the size of a network data buffer queue. 

**Parameters:**

<a name="table1160544037084825"></a>
<table><thead align="left"><tr id="row561546319084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p238460324084825"><a name="p238460324084825"></a><a name="p238460324084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1879157518084825"><a name="p1879157518084825"></a><a name="p1879157518084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1383580375084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">q</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer queue.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the size of the network data buffer queue.



## NetBufResizeRoom\(\)<a name="ga623e0b15e65f317f746b53b9a4530bdd"></a>

```
int32_t NetBufResizeRoom (struct [NetBuf](NetBuf.md) * nb, uint32_t head, uint32_t tail )
```

 **Description:**

Adjusts the size of a network data buffer space. 

This function is used to apply for a new network data buffer based on the configured reserved space and the size of the source network data buffer, and copy the actual data to the new network data buffer.

**Parameters:**

<a name="table1228202628084825"></a>
<table><thead align="left"><tr id="row915602646084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p408714252084825"><a name="p408714252084825"></a><a name="p408714252084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2097652899084825"><a name="p2097652899084825"></a><a name="p2097652899084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row249157547084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nb</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network data buffer. </td>
</tr>
<tr id="row679121814084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">head</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the header buffer segment reserved. </td>
</tr>
<tr id="row2014599139084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">tail</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the tail buffer segment reserved.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetDevGetRegisterCount\(\)<a name="ga8c8d400a6b4eb64445a2b4ea12102c9a"></a>

```
uint32_t NetDevGetRegisterCount (void )
```

 **Description:**

Obtains the number of added network devices. 

**Returns:**

Returns the number of added network devices.



## NetDeviceAdd\(\)<a name="ga64be10f09b180d3098e9550163131dbd"></a>

```
int32_t NetDeviceAdd (struct [NetDevice](NetDevice.md) * netDevice, [Protocol80211IfType](WLAN.md#gac69954f56fcc99fc8aac68aa157831c7) ifType )
```

 **Description:**

Adds a network device to a protocol stack. 

**Parameters:**

<a name="table1040652582084825"></a>
<table><thead align="left"><tr id="row2110990940084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1005233695084825"><a name="p1005233695084825"></a><a name="p1005233695084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1479033333084825"><a name="p1479033333084825"></a><a name="p1479033333084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2024717418084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device structure obtained during initialization. </td>
</tr>
<tr id="row1705162914084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the network port type, as enumerated in <a href="WLAN.md#gac69954f56fcc99fc8aac68aa157831c7">Protocol80211IfType</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value representing  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67)  if the operation fails.



## NetDeviceDeInit\(\)<a name="gaf4a2fa8b1a35d4cadd8247ee8fed60a4"></a>

```
int32_t NetDeviceDeInit (struct [NetDevice](NetDevice.md) * netDevice)
```

 **Description:**

Deletes a network device. 

**Parameters:**

<a name="table501197055084825"></a>
<table><thead align="left"><tr id="row88967591084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2017616533084825"><a name="p2017616533084825"></a><a name="p2017616533084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2097838682084825"><a name="p2097838682084825"></a><a name="p2097838682084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row845956085084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device structure obtained during initialization.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value representing  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67)  if the operation fails.



## NetDeviceDelete\(\)<a name="ga6c93cb701cf2523eaa7bbeabd4acf3ab"></a>

```
int32_t NetDeviceDelete (struct [NetDevice](NetDevice.md) * netDevice)
```

 **Description:**

Deletes a network device from a protocol stack. 

**Parameters:**

<a name="table37009105084825"></a>
<table><thead align="left"><tr id="row935457720084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p694214713084825"><a name="p694214713084825"></a><a name="p694214713084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1983332090084825"><a name="p1983332090084825"></a><a name="p1983332090084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1131673673084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device structure <strong id="b1768353983084825"><a name="b1768353983084825"></a><a name="b1768353983084825"></a>netDevice</strong> obtained during initialization.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value representing  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67)  if the operation fails.



## NetDeviceGetCap\(\)<a name="ga5d2a4fd370e2115b4c1fc8ecc46d64ab"></a>

```
uint32_t NetDeviceGetCap (void )
```

 **Description:**

Obtains the maximum number of network devices that can be registered with this system at the same time. 

**Returns:**

Returns the maximum number of network devices.



## NetDeviceGetInstByIndex\(\)<a name="gab45261476e710c30335975726af3a834"></a>

```
struct [NetDevice](NetDevice.md)* NetDeviceGetInstByIndex (uint32_t index)
```

 **Description:**

Obtains a network device instance based on the index number. 

**Parameters:**

<a name="table904610515084825"></a>
<table><thead align="left"><tr id="row398048219084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1458061215084825"><a name="p1458061215084825"></a><a name="p1458061215084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1150214200084825"><a name="p1150214200084825"></a><a name="p1150214200084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1631012818084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the index number.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the network device structure  [NetDevice](NetDevice.md)  if the operation is successful; returns  **NULL**  if the operation fails.



## NetDeviceGetInstByName\(\)<a name="ga6d90d1bf783a83db1d838d03f8c1d93a"></a>

```
struct [NetDevice](NetDevice.md)* NetDeviceGetInstByName (const char * name)
```

 **Description:**

Obtains the initialized network device instance by a specified device name. 

**Parameters:**

<a name="table1339574735084825"></a>
<table><thead align="left"><tr id="row676082211084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p108055684084825"><a name="p108055684084825"></a><a name="p108055684084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p805510956084825"><a name="p805510956084825"></a><a name="p805510956084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1583469305084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">name</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device name.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the network device structure  [NetDevice](NetDevice.md)  matching the network device name if the operation is successful; returns  **NULL**  if the operation fails.



## NetDeviceInit\(\)<a name="ga8d2bff6673ec21ba317d596a84df7ca8"></a>

```
struct [NetDevice](NetDevice.md)* NetDeviceInit (const char * ifName, uint32_t len, [NetIfCategory](WLAN.md#ga530241881cd17e03f8ae254ef1d9755e) ifCategory )
```

 **Description:**

Initializes a network device to obtain its instance. 

**Parameters:**

<a name="table1188750451084825"></a>
<table><thead align="left"><tr id="row1467749366084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p892629080084825"><a name="p892629080084825"></a><a name="p892629080084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p589347451084825"><a name="p589347451084825"></a><a name="p589347451084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row547631568084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ifName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device name. </td>
</tr>
<tr id="row1961831884084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the network device name. </td>
</tr>
<tr id="row1342065830084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ifCategory</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the network port category.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the structure  [NetDevice](NetDevice.md)  for the initialized network device if the operation is successful; returns  **NULL**  if the operation fails.



## NetDeviceIsAnyInstRunning\(\)<a name="ga20fcbcc248e99917c17223a97fe5d70e"></a>

```
bool NetDeviceIsAnyInstRunning (void )
```

 **Description:**

Checks whether there are working devices among the added network devices. 

**Returns:**

Returns  **true**  if the added network devices are working; returns  **false**  if none of the added network devices is working.



## NetDeviceIsInstRunning\(\)<a name="ga05b08c890c69f3e633447f14e16d30f7"></a>

```
bool NetDeviceIsInstRunning (const struct [NetDevice](NetDevice.md) * netDevice)
```

 **Description:**

Checks whether a specified network device is working. 

**Parameters:**

<a name="table1187910413084825"></a>
<table><thead align="left"><tr id="row1965286556084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p703974464084825"><a name="p703974464084825"></a><a name="p703974464084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p533183466084825"><a name="p533183466084825"></a><a name="p533183466084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row445545528084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device structure <strong id="b2061034339084825"><a name="b2061034339084825"></a><a name="b2061034339084825"></a>netDevice</strong> obtained during initialization.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **true**  if the specified network device is working; returns  **false**  otherwise.



## NetIfDhcpIsBound\(\)<a name="ga389ec95a3c8170c4ca74487f8bc1d8ac"></a>

```
int32_t NetIfDhcpIsBound (const struct [NetDevice](NetDevice.md) * netDevice)
```

 **Description:**

Obtains the DHCP negotiation status of a specified network device. 

**Parameters:**

<a name="table856211495084825"></a>
<table><thead align="left"><tr id="row1043410776084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p374491355084825"><a name="p374491355084825"></a><a name="p374491355084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p869136476084825"><a name="p869136476084825"></a><a name="p869136476084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1707138694084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device obtained during initialization.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetIfDhcpsStart\(\)<a name="gae97c7abcf556be34798622a85162c35e"></a>

```
int32_t NetIfDhcpsStart (const struct [NetDevice](NetDevice.md) * netDevice, char * ip, u16_t ipNum )
```

 **Description:**

Starts the DHCP server. 

**Parameters:**

<a name="table98014289084825"></a>
<table><thead align="left"><tr id="row481157193084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p316749473084825"><a name="p316749473084825"></a><a name="p316749473084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p460645808084825"><a name="p460645808084825"></a><a name="p460645808084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row325454720084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device structure <strong id="b189593886084825"><a name="b189593886084825"></a><a name="b189593886084825"></a>netDevice</strong> obtained during initialization. </td>
</tr>
<tr id="row562276446084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">beginIp</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the IP address to start. </td>
</tr>
<tr id="row131127283084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ipNum</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of IP addresses.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetIfDhcpsStop\(\)<a name="gaadfeb819b4cb623870823fa5c9793b4c"></a>

```
int32_t NetIfDhcpsStop (const struct [NetDevice](NetDevice.md) * netDevice)
```

 **Description:**

Stops the DHCP server. 

**Parameters:**

<a name="table538081522084825"></a>
<table><thead align="left"><tr id="row2091524878084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p629851475084825"><a name="p629851475084825"></a><a name="p629851475084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1979691107084825"><a name="p1979691107084825"></a><a name="p1979691107084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1415742216084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device structure <strong id="b658847055084825"><a name="b658847055084825"></a><a name="b658847055084825"></a>netDevice</strong> obtained during initialization.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetIfDhcpStart\(\)<a name="ga5fdd93c820b994adf1b76eb8d50e4f88"></a>

```
int32_t NetIfDhcpStart (const struct [NetDevice](NetDevice.md) * netDevice)
```

 **Description:**

Starts the DHCP client of a specified network device. 

**Parameters:**

<a name="table1595252129084825"></a>
<table><thead align="left"><tr id="row1838918959084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p323838335084825"><a name="p323838335084825"></a><a name="p323838335084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p388028479084825"><a name="p388028479084825"></a><a name="p388028479084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1325265338084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device obtained during initialization.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetIfDhcpStop\(\)<a name="ga22f97a3fc45841e874ab2072c14e0f3e"></a>

```
int32_t NetIfDhcpStop (const struct [NetDevice](NetDevice.md) * netDevice)
```

 **Description:**

Stops the DHCP client of a specified network device. 

**Parameters:**

<a name="table1811679971084825"></a>
<table><thead align="left"><tr id="row1433847923084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1768130487084825"><a name="p1768130487084825"></a><a name="p1768130487084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p689505726084825"><a name="p689505726084825"></a><a name="p689505726084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row214191692084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device obtained during initialization.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetIfRx\(\)<a name="ga44006f6e066aff9f6a3310559e781582"></a>

```
int32_t NetIfRx (const struct [NetDevice](NetDevice.md) * netDevice, struct [NetBuf](NetBuf.md) * buff )
```

 **Description:**

Transfers the input data packets from the network side to a protocol stack. 

**Parameters:**

<a name="table1226049785084825"></a>
<table><thead align="left"><tr id="row129480060084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p324827064084825"><a name="p324827064084825"></a><a name="p324827064084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p154379324084825"><a name="p154379324084825"></a><a name="p154379324084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1901809784084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buff</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the network-side data, in Ether format.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetIfRxNi\(\)<a name="gad252107cdd20e9d3d0ab33fbfc2161e9"></a>

```
int32_t NetIfRxNi (const struct [NetDevice](NetDevice.md) * netDevice, struct [NetBuf](NetBuf.md) * buff )
```

 **Description:**

Transfers data packets from the network side to a protocol stack in an interrupt processing thread. 

**Parameters:**

<a name="table820916918084825"></a>
<table><thead align="left"><tr id="row1735398817084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p317196768084825"><a name="p317196768084825"></a><a name="p317196768084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p139178208084825"><a name="p139178208084825"></a><a name="p139178208084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1800631675084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buff</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the network-side data, in Ether format.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value  [HDF\_STATUS](DriverUtils.md#ga7e01536ecbe9b17563dd3fe256202a67)  if the operation fails.



## NetIfSetAddr\(\)<a name="gadd5c08aa8e65a12db062b1b88d53cece"></a>

```
int32_t NetIfSetAddr (const struct [NetDevice](NetDevice.md) * netDevice, const [IpV4Addr](IpV4Addr.md) * ipAddr, const [IpV4Addr](IpV4Addr.md) * netMask, const [IpV4Addr](IpV4Addr.md) * gw )
```

 **Description:**

Sets an IP address, mask, and gateway. 

**Parameters:**

<a name="table2034180162084825"></a>
<table><thead align="left"><tr id="row1322150024084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1202593764084825"><a name="p1202593764084825"></a><a name="p1202593764084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1351681238084825"><a name="p1351681238084825"></a><a name="p1351681238084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1741405499084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device structure <strong id="b1561918289084825"><a name="b1561918289084825"></a><a name="b1561918289084825"></a>netDevice</strong> obtained during initialization. </td>
</tr>
<tr id="row956018689084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">ipAddr</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the IP address to set. </td>
</tr>
<tr id="row886925780084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netMask</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the mask to set. </td>
</tr>
<tr id="row1408124422084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gw</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the gateway to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetIfSetLinkStatus\(\)<a name="gaee9c68875ef541ed915045ab7a047ee8"></a>

```
int32_t NetIfSetLinkStatus (const struct [NetDevice](NetDevice.md) * netDevice, [NetIfLinkStatus](WLAN.md#ga7b1187d116fb065d7927ad9f77edd842) status )
```

 **Description:**

Notifies the network layer of the data link layer status. 

**Parameters:**

<a name="table1486399936084825"></a>
<table><thead align="left"><tr id="row2119225867084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p652685263084825"><a name="p652685263084825"></a><a name="p652685263084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p689791631084825"><a name="p689791631084825"></a><a name="p689791631084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row203450888084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device obtained during initialization. </td>
</tr>
<tr id="row17560903084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">status</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">status Indicates the data link layer status, as enumerated in <strong id="b1600985888084825"><a name="b1600985888084825"></a><a name="b1600985888084825"></a>NetIfLinkSatus</strong>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## NetIfSetStatus\(\)<a name="gaa14fc68a382284491a272992d5c477cb"></a>

```
int32_t NetIfSetStatus (const struct [NetDevice](NetDevice.md) * netDevice, [NetIfStatus](WLAN.md#ga0fb482694e5eac3f48c75de1749c8baf) status )
```

 **Description:**

Notifies the network layer of the network port state. 

**Parameters:**

<a name="table1359268422084825"></a>
<table><thead align="left"><tr id="row1945954471084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1383363498084825"><a name="p1383363498084825"></a><a name="p1383363498084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1991720357084825"><a name="p1991720357084825"></a><a name="p1991720357084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2026631564084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netDevice</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device obtained during initialization. @paramstatus Indicates the network port state, as enumerated in <strong id="b1444701136084825"><a name="b1444701136084825"></a><a name="b1444701136084825"></a>NetIfSatus</strong>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a non-zero value otherwise.



## Pbuf2NetBuf\(\)<a name="ga8d44f8dbfa75583d0056702b5a2d32a1"></a>

```
struct [NetBuf](NetBuf.md)* Pbuf2NetBuf (const struct [NetDevice](NetDevice.md) * netdev, struct pbuf * lwipBuf )
```

 **Description:**

Converts the  **pbuf**  structure of Lightweight TCP/IP Stack \(lwIP\) to a network data buffer. 

When a network device is specified, the reserved space of the network device will be added to the size of the converted network data buffer.

**Parameters:**

<a name="table1682010643084825"></a>
<table><thead align="left"><tr id="row553502168084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p493993814084825"><a name="p493993814084825"></a><a name="p493993814084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1880266538084825"><a name="p1880266538084825"></a><a name="p1880266538084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1080216850084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">netdev</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the network device. </td>
</tr>
<tr id="row2124119902084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">lwip_buf</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data buffer of lwIP.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the network data buffer if the operation is successful; returns  **NULL**  otherwise.



## WifiModuleCreate\(\)<a name="gaf5d1df53f08cae98ecfd440f9b425709"></a>

```
struct [WifiModule](WifiModule.md)* WifiModuleCreate (const struct HdfConfigWifiModuleConfig * config)
```

 **Description:**

Creates a  [WifiModule](WifiModule.md)  object based on a specified configuration generated by the HCS. 

**Parameters:**

<a name="table771158968084825"></a>
<table><thead align="left"><tr id="row1859081557084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2099531343084825"><a name="p2099531343084825"></a><a name="p2099531343084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1105832229084825"><a name="p1105832229084825"></a><a name="p1105832229084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row101925617084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">config</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration generated by the HCS.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the created  [WifiModule](WifiModule.md)  object.



## WifiModuleDelete\(\)<a name="gae14e3786e60f16a100197d28bae5a362"></a>

```
void WifiModuleDelete (struct [WifiModule](WifiModule.md) * module)
```

 **Description:**

Deletes a specified  [WifiModule](WifiModule.md)  object. 

**Parameters:**

<a name="table1459245988084825"></a>
<table><thead align="left"><tr id="row656902790084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1156216040084825"><a name="p1156216040084825"></a><a name="p1156216040084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1879630080084825"><a name="p1879630080084825"></a><a name="p1879630080084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row978505951084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">module</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the <a href="WifiModule.md">WifiModule</a> object to delete.</td>
</tr>
</tbody>
</table>

## **Variable Documentation**<a name="section885401556084825"></a>

## aborted<a name="ga32ea10f832c5a03971033d5f44f3ef6c"></a>

```
uint8_t WifiScanRequest::aborted
```

 **Description:**

Whether to abort the scan 

## abortScan<a name="gab870d8100c1c9cb60b27c75a44bb30d4"></a>

```
int32_t(* WifiMac80211Ops::abortScan) ([NetDevice](NetDevice.md) *netDev)
```

 **Description:**

Stopping a scan 

## ackNum<a name="ga223c54c5ebb2d92ed5f6c50115663b86"></a>

```
uint32_t TcpHeader::ackNum
```

 **Description:**

Acknowledgement number 

## addFeature<a name="gadfa86fac18c68b890d3b33a269931efc"></a>

```
int32_t(* WifiModuleIface::addFeature) (struct [WifiModule](WifiModule.md) *module, uint16_t featureType, struct [WifiFeature](WifiFeature.md) *featureData)
```

 **Description:**

Adding a feature 

## addKey<a name="ga367902162f25b7b4c5b80372bb6a81f2"></a>

```
int32_t(* WifiMac80211Ops::addKey) (struct [NetDevice](NetDevice.md) *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *macAddr, struct [KeyParams](KeyParams.md) *params)
```

 **Description:**

Adding a key with specified parameters 

## addr \[1/2\]<a name="gacdd7348f71376cd66b3a0079a1c393d5"></a>

```
uint8_t MacAddress::addr[ETH_ADDR_LEN]
```

 **Description:**

Device MAC address 

## addr \[2/2\]<a name="gabcba7263b501288a2585bfddb77f93c4"></a>

```
uint32_t IpV4Addr::addr
```

 **Description:**

IPv4 address 

## addrLen<a name="gafc2646cdc533135a303ca91bf9ebe7ec"></a>

```
uint8_t NetDevice::addrLen
```

 **Description:**

MAC address length 

## addrMask<a name="ga8d1059e645ca6684e9ea82044e03270b"></a>

```
uint8_t Wiphy::addrMask[WLAN_MAC_ADDR_LEN]
```

 **Description:**

MAC address mask of the wiphy device. If the device supports multiple virtual MAC addresses, the bit whose value is  **1**  in the mask represents a variable part of the MAC address. 

## aid \[1/2\]<a name="ga9885111fb46e5fd771df52f260e80e98"></a>

```
uint16_t AssocResp::aid
```

 **Description:**

Authentication ID 

## aid \[2/2\]<a name="ga9c02f712098d5faa35d6febcd0a26bcf"></a>

```
uint16_t ReassocResp::aid
```

 **Description:**

Authentication ID 

## akmSuites<a name="ga142aeeaed24db6cd329c0b8b78ab13bc"></a>

```
uint32_t CryptoSettings::akmSuites[NL80211_MAX_NR_AKM_SUITES]
```

 **Description:**

AKM suite data. For details, see  **NL80211\_MAX\_NR\_AKM\_SUITES**. 

## ampduDensity<a name="ga90e3ceab29efbe5b144191176f7f8e44"></a>

```
uint8_t Ieee80211StaHtCap::ampduDensity
```

 **Description:**

Minimum MPDU start spacing 

## ampduFactor<a name="ga891bf97aba3202dd8c4f1cbdc288c61f"></a>

```
uint8_t Ieee80211StaHtCap::ampduFactor
```

 **Description:**

Maximum length of an aggregated MAC Protocol Data Unit \(A-MPDU\) 

## arry<a name="ga6d31899685b7a552a5322e93b0ffd972"></a>

```
uint8_t ScannedBssInfo::arry[2]
```

 **Description:**

Reserved 

## assocReq \[1/2\]<a name="ga7bcd238eb3be90e887638d51139f570d"></a>

```
struct [AssocReq](AssocReq.md) Ieee80211Mgmt::assocReq
```

 **Description:**

Association request 

## assocReq \[2/2\]<a name="ga0e632c4ebc342612550167cbd3270c7b"></a>

```
struct { ... } ::assocReq
```

 **Description:**

Association request 

## assocReqIes<a name="gac2e13b44df4b4df0018f801f8a9e0494"></a>

```
const uint8_t* StationInfo::assocReqIes
```

 **Description:**

Information Elements \(IEs\) in Association  [Request](Request.md) 

## assocReqIesLen<a name="ga7822f8e474e18a4f7ae7cee7cbd9bc7c"></a>

```
uint32_t StationInfo::assocReqIesLen
```

 **Description:**

IE length in Association  [Request](Request.md) 

## assocResp \[1/2\]<a name="gad709ecd25bb15fdc7518eeafd47e3706"></a>

```
struct [AssocResp](AssocResp.md) Ieee80211Mgmt::assocResp
```

 **Description:**

Association response 

## assocResp \[2/2\]<a name="gaeca754ff495befc0eb6c96367655c442"></a>

```
struct { ... } ::assocResp
```

 **Description:**

Association response 

## aucArry<a name="ga94fdc9f1d50e8f8561e2fa539bd7c8c8"></a>

```
uint8_t Mac80211Ssids::aucArry[MAC80211_SSIDS_AUC_SIZE]
```

 **Description:**

AuC data array 

## aucResv<a name="gac0b10633f99311af30dd220ae9d19e34"></a>

```
uint8_t WifiConnectParams::aucResv[WIFI_CONNECT_PARM_RESV_SIZE]
```

 **Description:**

Reserved field 

## aucRsv \[1/2\]<a name="gaf00464a59d6bda90ad57cd6201736245"></a>

```
uint8_t Ieee80211StaHtCap::aucRsv[IEEE80211_STAHTCAP_RESV]
```

 **Description:**

Reserved field 

## aucRsv \[2/2\]<a name="gabdd49dff12ed26c47f1935fb2bf3d873"></a>

```
uint8_t Wiphy::aucRsv[WIPHY_RSV_SIZE]
```

 **Description:**

Manual alignment of data structures 

## aucSsid<a name="ga47c550859928cbc795333cb26b138ba3"></a>

```
uint8_t Mac80211Ssids::aucSsid[OAL_IEEE80211_MAX_SSID_LEN]
```

 **Description:**

SSID array 

## auth \[1/2\]<a name="ga804940b221f326dd0f6b20e33fa5b232"></a>

```
struct { ... } ::auth
```

 **Description:**

Authentication Information 

## auth \[2/2\]<a name="ga797e6d02e8d4fdb4bd372d3c5286c6e9"></a>

```
struct [Auth](Auth.md) Ieee80211Mgmt::auth
```

 **Description:**

Authentication Information 

## authAlg<a name="gafe2c9439abca834df69dba0aa57a6d5f"></a>

```
uint16_t Auth::authAlg
```

 **Description:**

Authentication algorithm 

## authTransaction<a name="gad8e67419612ed5fea439e74efb16d4c4"></a>

```
uint16_t Auth::authTransaction
```

 **Description:**

Authentication transaction 

## authType<a name="ga2c9cdaa7b998a7ffb4378f4a6cedbb75"></a>

```
uint8_t WifiConnectParams::authType
```

 **Description:**

Authorization type 

## band \[1/2\]<a name="gaab4e3330566d5b0b02e7c6117c7b9a73"></a>

```
enum [Ieee80211Band](WLAN.md#ga9882f415202cf9acb0f4cdfbc456a88d) Ieee80211Channel::band
```

 **Description:**

Frequency band, either 2.4 GHz or 5 GHz 

## band \[2/2\]<a name="gabfd4562987e1c8b6daea0d10ca8c2751"></a>

```
enum [Ieee80211Band](WLAN.md#ga9882f415202cf9acb0f4cdfbc456a88d) Ieee80211SupportedBand::band
```

 **Description:**

Band matching this data structure description 

## bands<a name="gaf3ab07acceaeff1edc793cb23d739ec5"></a>

```
struct [Ieee80211SupportedBand](Ieee80211SupportedBand.md)* Wiphy::bands[[IEEE80211_NUM_BANDS](WLAN.md#gga9882f415202cf9acb0f4cdfbc456a88da703cf67d516a80d6dae1b1995017b9a4)]
```

 **Description:**

Supported bands 

## beacon \[1/2\]<a name="ga368a66f24e860ef013989c410fa0fb3e"></a>

```
struct [Beacon](Beacon.md) Ieee80211Mgmt::beacon
```

 **Description:**

[Beacon](Beacon.md)  frame 

## beacon \[2/2\]<a name="ga6507ea23b2297719aa7a87cc58b619ab"></a>

```
struct { ... } ::beacon
```

 **Description:**

[Beacon](Beacon.md)  frame 

## beaconData<a name="ga80cf5c2a3596c32ddc1de60d51c3e33d"></a>

```
WifiBeaconData* Mac80211beaconParam::beaconData
```

 **Description:**

[Beacon](Beacon.md)  frame data 

## beaconFound<a name="ga55c6f1eaedc16b99dc299530a0dc6f83"></a>

```
int8_t Ieee80211Channel::beaconFound
```

 **Description:**

When a beacon frame is found in this channel 

## beaconInt \[1/2\]<a name="ga34eacc801b02cefbfe742a6451b95770"></a>

```
uint16_t Beacon::beaconInt
```

 **Description:**

[Beacon](Beacon.md)  interval 

## beaconInt \[2/2\]<a name="ga8438721279093a38779f1ab7f6ed59dc"></a>

```
uint16_t ProbeResp::beaconInt
```

 **Description:**

[Beacon](Beacon.md)  interval 

## beaconInterval<a name="gad49083c0d110aef00878071800040069"></a>

```
uint16_t StaBssParameters::beaconInterval
```

 **Description:**

[Beacon](Beacon.md)  interval 

## beaconLossCount<a name="gaa669232960c93e73558062e466d0fb02"></a>

```
uint32_t StationInfo::beaconLossCount
```

 **Description:**

Number of beacon loss events triggered 

## bitrate<a name="gab8e1e3d778d0739a728ae5d3a77fe502"></a>

```
uint16_t Ieee80211Rate::bitrate
```

 **Description:**

Bit rate, in 100 kbit/s 

## bitrates<a name="ga4a0d4f26cbf81f839b25c2808e50856a"></a>

```
struct [Ieee80211Rate](Ieee80211Rate.md)* Ieee80211SupportedBand::bitrates
```

 **Description:**

An array of supported bit rates 

## bssid \[1/3\]<a name="gac8415aaa2b1a60e17712776826b2514a"></a>

```
uint8_t Ieee80211Mgmt::bssid[6]
```

 **Description:**

BSS ID 

## bssid \[2/3\]<a name="gacfb1f8dc523cea7d4394b912c0c508ea"></a>

```
uint8_t ConnetResult::bssid[ETH_ADDR_LEN]
```

 **Description:**

MAC address of the AP associated with the station 

## bssid \[3/3\]<a name="gaf088c497d633df51d8bee24e7a778c22"></a>

```
uint8_t* WifiConnectParams::bssid
```

 **Description:**

AP basic service set identifier \(BSSID\). If this parameter is not specified, the AP BSSID is automatically obtained from the scan result. 

## bssParam<a name="ga0b38e5935241d2f3cd05c2e5bba1c8e1"></a>

```
struct [StaBssParameters](StaBssParameters.md) StationInfo::bssParam
```

 **Description:**

Current BSS parameters 

## bufs<a name="ga49eacbbc8b4231a05464768103b8593f"></a>

```
struct BufField NetBuf::bufs[[MAX_BUF_NUM](WLAN.md#ggae4d5251432e1a9e6803c0240cc492e18aeef2a730ef9f722cfbac0b24998f8e19)]
```

 **Description:**

Defines buffer segments used to record the offset address \(based on the memory buffer address\) and length of each buffer segment, including the header buffer segment, data segment, and tail buffer segment. For details, see  [MAX\_BUF\_NUM](WLAN.md#ggae4d5251432e1a9e6803c0240cc492e18aeef2a730ef9f722cfbac0b24998f8e19). 

## cap<a name="ga56216c033dd738a3100c8e0d9c1dd1a8"></a>

```
uint16_t Ieee80211StaHtCap::cap
```

 **Description:**

HT capability table provided in 802.11n 

## capabInfo \[1/6\]<a name="gadc4d122edd92d777956cb913aa27918b"></a>

```
uint16_t AssocReq::capabInfo
```

 **Description:**

WLAN capability information 

## capabInfo \[2/6\]<a name="ga53356e3d7b67cdeca0e6110dbb8b46f7"></a>

```
uint16_t AssocResp::capabInfo
```

 **Description:**

WLAN capability information 

## capabInfo \[3/6\]<a name="ga3e5e0b8af464d5990e451d6a97c6e89b"></a>

```
uint16_t ReassocReq::capabInfo
```

 **Description:**

WLAN capability information 

## capabInfo \[4/6\]<a name="ga718001853f9317e9108339cfe5e6531b"></a>

```
uint16_t ReassocResp::capabInfo
```

 **Description:**

WLAN capability information 

## capabInfo \[5/6\]<a name="gaabddc721f70c869a51d5893ea58012cc"></a>

```
uint16_t Beacon::capabInfo
```

 **Description:**

WLAN capability information 

## capabInfo \[6/6\]<a name="ga0389de8c9241c7e8622e3cf643ee8efe"></a>

```
uint16_t ProbeResp::capabInfo
```

 **Description:**

WLAN capability information 

## centerFreq<a name="ga42300a5593bf6b40a4d823af2dbe2a5d"></a>

```
uint16_t Ieee80211Channel::centerFreq
```

 **Description:**

Center frequency 

## centerFreq1<a name="ga650d64bab38809286d34acd11f292507"></a>

```
int32_t ChannelDef::centerFreq1
```

 **Description:**

Center frequency 1 

## centerFreq2<a name="ga62d64617036c65e3964657c692a39f6a"></a>

```
int32_t ChannelDef::centerFreq2
```

 **Description:**

Center frequency 2 

## chan<a name="ga165ba815b4ddb9558f90bd0bf82e23f0"></a>

```
struct [Ieee80211Channel](Ieee80211Channel.md)* ChannelDef::chan
```

 **Description:**

Channel information 

## changeBeacon<a name="ga833043e11a73c8f53cb918e25715939e"></a>

```
int32_t(* WifiMac80211Ops::changeBeacon) ([NetDevice](NetDevice.md) *netDev, [Mac80211beaconParam](Mac80211beaconParam.md) *param)
```

 **Description:**

Setting the beacon frame based on specified parameters 

## changeMtu<a name="ga2035c840c71a43b43451bfe0213ca04a"></a>

```
int32_t(* NetDeviceInterFace::changeMtu) (struct [NetDevice](NetDevice.md) *netDev, int32_t newMtu)
```

 **Description:**

Changes the maximum number of transmission units. 

## changeVirtualIntf<a name="ga0a4446bf704b9f4b673f68ff97002b1b"></a>

```
int32_t(* WifiMac80211Ops::changeVirtualIntf) ([NetDevice](NetDevice.md) *netDev, uint8_t iftype, uint32_t *flags, struct [VifParams](VifParams.md) *params)
```

 **Description:**

Changing virtual APIs 

## channel<a name="ga0c59333afe2ac58387c92260a8268de7"></a>

```
struct [Ieee80211Channel](Ieee80211Channel.md)* WifiConnectParams::channel
```

 **Description:**

Connection channel. If this parameter is not specified, the connection channel is automatically obtained from the scan result. 

## channels \[1/2\]<a name="gaabb5ffed3a294507d4f51d598fd98717"></a>

```
struct [Ieee80211Channel](Ieee80211Channel.md)* WifiScanRequest::channels[MAX_SCAN_CHANNELS]
```

 **Description:**

Channels to scan for. For details, see  **MAX\_SCAN\_CHANNELS**. 

## channels \[2/2\]<a name="ga02df34a92ff5010c8b70ed8cdbd90fb1"></a>

```
struct [Ieee80211Channel](Ieee80211Channel.md)* Ieee80211SupportedBand::channels
```

 **Description:**

An array of supported channels 

## check \[1/3\]<a name="gaf3b4d16f68ab697df71ca8589f00397c"></a>

```
uint16_t IpHeader::check
```

 **Description:**

Header check 

## check \[2/3\]<a name="gae93142de73db5e7e18f2d247387d79ee"></a>

```
uint16_t UdpHeader::check
```

 **Description:**

Header check 

## check \[3/3\]<a name="gab32c75fd1d8d8985d9861157907a3a74"></a>

```
uint16_t TcpHeader::check
```

 **Description:**

Checksum 

## chip<a name="ga213bff4c0d74fb3db3ff7c21bea781ae"></a>

```
struct [HdfWifiChipData](HdfWifiChipData.md)* WifiFeature::chip
```

 **Description:**

Chip 

## cipher<a name="ga2efb1151fccead84c0d4257717760936"></a>

```
uint32_t KeyParams::cipher
```

 **Description:**

Cipher suite 

## cipherGroup<a name="ga9be34adb7e26191321b38c37b341e20d"></a>

```
uint32_t CryptoSettings::cipherGroup
```

 **Description:**

Cipher group 

## ciphersPairwise<a name="ga53c85b4e0f5f5e10bb16935fb8a77df0"></a>

```
uint32_t CryptoSettings::ciphersPairwise[NL80211_MAX_NR_CIPHER_SUITES]
```

 **Description:**

Unicast cipher suite. For details, see  **NL80211\_MAX\_NR\_CIPHER\_SUITES**. 

## cipherSuites<a name="ga011f5a473787d4700441e4bf7387673a"></a>

```
const uint32_t* Wiphy::cipherSuites
```

 **Description:**

Supported cipher suites 

## connect<a name="ga9f26a0c3e31e1b57cc8b357964cce3db"></a>

```
int32_t(* WifiMac80211Ops::connect) ([NetDevice](NetDevice.md) *netDev, [WifiConnectParams](WifiConnectParams.md) *param)
```

 **Description:**

Starting a connection based on the specified parameters 

## connectedTime<a name="ga7a260a68741622c415faa30f345802f1"></a>

```
uint32_t StationInfo::connectedTime
```

 **Description:**

Duration \(in seconds\) since the last station connection 

## connectStatus<a name="ga22925ebc7c0b94465c53b886307c67dd"></a>

```
uint16_t ConnetResult::connectStatus
```

 **Description:**

Connection status 

## controlPort<a name="ga2f49a07024546730d0cd60e93cb9e450"></a>

```
int8_t CryptoSettings::controlPort
```

 **Description:**

Whether the user space control port is authorized. The value  **true**  indicates that the user space control port is unauthorized. 

## controlPortEthertype<a name="ga67b6c08be0641796798513fbbb13dd73"></a>

```
uint16_t CryptoSettings::controlPortEthertype
```

 **Description:**

Data can be transmitted over an unauthenticated port. 

## controlPortNoEncrypt<a name="ga020b34dbfd5f961c86ef416873a9c02c"></a>

```
int8_t CryptoSettings::controlPortNoEncrypt
```

 **Description:**

Whether to encrypt frames transmitted over the control port. The value  **1**  indicates that the frames are not encrypted. 

## crypto<a name="gaa91e37ddf709a3553a6352623ea8c341"></a>

```
struct [CryptoSettings](CryptoSettings.md) WifiConnectParams::crypto
```

 **Description:**

Cryptography information 

## currentAp<a name="ga451da053aeae74e215da41757196ac2c"></a>

```
uint8_t ReassocReq::currentAp[6]
```

 **Description:**

Current AP 

## dAddr<a name="ga5124eb108341354708e52775df8899ef"></a>

```
uint32_t IpHeader::dAddr
```

 **Description:**

Destination address 

## dataLen<a name="gafb7e6f774a44888f5c44c3dffc6c5616"></a>

```
uint32_t NetBuf::dataLen
```

 **Description:**

Actual data length of the network data buffer 

## deauth \[1/2\]<a name="ga65ccc20a9dd404cfb020ecfe9a3301a1"></a>

```
struct [Deauth](Deauth.md) Ieee80211Mgmt::deauth
```

 **Description:**

Deauthentication Information 

## deauth \[2/2\]<a name="ga3ec147e23f0e5d9698a55e7963459ef4"></a>

```
struct { ... } ::deauth
```

 **Description:**

Deauthentication Information 

## deinit<a name="gaf4ad8f670757555c0535b5a5fa5fa8d9"></a>

```
int32_t(* HdfWifiChipData::deinit) (struct [HdfWifiChipData](HdfWifiChipData.md) *chipData)
```

 **Description:**

Function for deinitializing the chip 

## deInit \[1/3\]<a name="ga371e13402535662210549c3ca3303691"></a>

```
void(* NetDeviceInterFace::deInit) (struct [NetDevice](NetDevice.md) *netDev)
```

 **Description:**

Deinitializes a network device to be delete. 

## deInit \[2/3\]<a name="gaf03445197e62e8d5cc5de5c7bba185dd"></a>

```
int32_t(* WifiFeature::deInit) (struct [WifiFeature](WifiFeature.md) *feature)
```

 **Description:**

Function for deinitializing the feature 

## deInit \[3/3\]<a name="ga378c89a04bb867068d3c86c5680ca9c0"></a>

```
int32_t(* WifiModuleIface::deInit) (struct [WifiModule](WifiModule.md) *module)
```

 **Description:**

Deinitializing a WLAN module 

## delFeature<a name="ga764ebf11b82c57d5185df50fab72a1d8"></a>

```
int32_t(* WifiModuleIface::delFeature) (struct [WifiModule](WifiModule.md) *module, uint16_t featureType)
```

 **Description:**

Deleting a feature 

## delKey<a name="ga7edb052049a9420b938085322c6a0418"></a>

```
int32_t(* WifiMac80211Ops::delKey) (struct [NetDevice](NetDevice.md) *netdev, uint8_t keyIndex, bool pairwise, const uint8_t *macAddr)
```

 **Description:**

Deleting a key based on a specified MAC address 

## delStation<a name="ga974552db5307795e70d5868edccecc1c"></a>

```
int32_t(* WifiMac80211Ops::delStation) ([NetDevice](NetDevice.md) *netDev, const uint8_t *macAddr)
```

 **Description:**

Deleting a station with a specified MAC address 

## dest<a name="ga21658fd4eb65ed4559958e3074f21081"></a>

```
uint16_t UdpHeader::dest
```

 **Description:**

Destination port number 

## dev \[1/2\]<a name="gafa78f2abfa4f977cfb3bd52a6ae05d61"></a>

```
void* NetBuf::dev
```

 **Description:**

Network device that receives the network data 

## dev \[2/2\]<a name="gada8e463843d9e5fef133d41fd745dc42"></a>

```
struct [NetDevice](NetDevice.md)* WifiScanRequest::dev
```

 **Description:**

A specified network device to scan for 

## device<a name="ga689a86688de16eed6ffa023417967c9a"></a>

```
struct [HdfDeviceObject](HdfDeviceObject.md)* HdfWifiProductData::device
```

 **Description:**

Structure of the Device Object 

## disassoc \[1/2\]<a name="gaab6d978c74d57fecc8f113446d07f3e5"></a>

```
struct { ... } ::disassoc
```

 **Description:**

Disconnected 

## disassoc \[2/2\]<a name="ga1c92855062b3cbbcc94f6e4cf3076473"></a>

```
struct [Disassoc](Disassoc.md) Ieee80211Mgmt::disassoc
```

 **Description:**

Disconnected 

## disconnect<a name="ga558d3d417f465ca592dc94c3040b2d1f"></a>

```
int32_t(* WifiMac80211Ops::disconnect) ([NetDevice](NetDevice.md) *netDev, uint16_t reasonCode)
```

 **Description:**

Canceling a connection 

## dlist \[1/2\]<a name="ga6de94d9c8f9dd8d608a091673fa130c4"></a>

```
struct [DListHead](DListHead.md) NetBuf::dlist
```

 **Description:**

Doubly linked list. Generally, multiple network data buffers are linked by using a doubly linked list. 

## dlist \[2/2\]<a name="ga473ab87a57006bb6ed69c5e5ea666f5c"></a>

```
struct [DListHead](DListHead.md) NetBufQueue::dlist
```

 **Description:**

Doubly linked list. Generally, multiple network data buffers are linked by using a doubly linked list. 

## dPort<a name="ga2a188a6b8ee0eccceefe0e17818e8707"></a>

```
uint16_t TcpHeader::dPort
```

 **Description:**

Destination port number 

## dstAddr<a name="ga4e602eacdc2481c6d91b1e42e7a7233c"></a>

```
uint8_t Ieee80211Mgmt::dstAddr[6]
```

 **Description:**

Destination MAC address 

## dtimPeriod \[1/2\]<a name="gac532b47f0a538e68bb340437d840fbcc"></a>

```
uint8_t StaBssParameters::dtimPeriod
```

 **Description:**

Delivery Traffic Indication Message \(DTIM\) period of BSS 

## dtimPeriod \[2/2\]<a name="gad63b5d23db5e2bf8b9ca57bdb7de4c82"></a>

```
int32_t Mac80211beaconParam::dtimPeriod
```

 **Description:**

Delivery Traffic Indication Message \(DTIM\) interval 

## duration<a name="gad1ea2da7ade6335e8c273284208d551d"></a>

```
uint16_t Ieee80211Mgmt::duration
```

 **Description:**

Duration 

## etherDhost<a name="ga987c92ec1c7c5e637ba93d18edcf87c4"></a>

```
uint8_t EtherHeader::etherDhost[[MAC_ADDR_SIZE](WLAN.md#gae01dbae885bc8abecb82bd865515c081)]
```

 **Description:**

Destination address  [MAC\_ADDR\_SIZE](WLAN.md#gae01dbae885bc8abecb82bd865515c081) 

## etherShost<a name="gaaee5baebf4a693ad44d0ae9530d9dfbd"></a>

```
uint8_t EtherHeader::etherShost[[MAC_ADDR_SIZE](WLAN.md#gae01dbae885bc8abecb82bd865515c081)]
```

 **Description:**

Source address  [MAC\_ADDR\_SIZE](WLAN.md#gae01dbae885bc8abecb82bd865515c081) 

## etherType<a name="ga6a0916fd23f851ba6cd2bcd3700123b2"></a>

```
uint16_t EtherHeader::etherType
```

 **Description:**

Ethernet type, such as 0x8035 \(RARP\), 0x888e \(EAPOL\), PAE/802.1x, 0x0800 \(IP\), 0x86dd \(IPV6\), and 0x0806 \(ARP\) 

## fake<a name="ga82e8bdd989fd03bf9cc3b5f6a14ec05b"></a>

```
uint32_t IfReq::fake
```

 **Description:**

magic field 

## fe<a name="ga772b7d7c4b5cc3ecdab421a0b2337e91"></a>

```
struct [WifiFeature](WifiFeature.md)* WifiFeatureList::fe[[HDF_WIFI_FEATURE_NUM](WLAN.md#ggaec03ba36d71cc2d5f3209bc24aa6ee10a28ff5971d579c1754e03a5f79a0c9e6f)]
```

 **Description:**

An array of WLAN features 

## feList<a name="ga347d5b39c9a96835ae85358ba0895cc3"></a>

```
struct [WifiFeatureList](WifiFeatureList.md)* WifiModule::feList
```

 **Description:**

WLAN features 

## filled<a name="ga14e0c28a09471313507c1ef6f704ad8a"></a>

```
uint32_t StationInfo::filled
```

 **Description:**

Flag values of relevant structures 

## flags \[1/7\]<a name="gaaf4d141dbf9493524661415d7940b853"></a>

```
uint8_t RateInfo::flags
```

 **Description:**

Flag field, used to indicate a specific rate transmission type of 802.11n 

## flags \[2/7\]<a name="ga192ebb83d79d9bed8ee35ceb3d91f1df"></a>

```
uint8_t StaBssParameters::flags
```

 **Description:**

Flag, used to indicate a specific rate transmission type of 802.11n 

## flags \[3/7\]<a name="gaadedfd33df129639f135a6f5d0322e4e"></a>

```
uint32_t Ieee80211Channel::flags
```

 **Description:**

WLAN channel flag 

## flags \[4/7\]<a name="ga0265e4d32fef1bb7c94f14671763655b"></a>

```
uint32_t Ieee80211Rate::flags
```

 **Description:**

Rate flag 

## flags \[5/7\]<a name="ga0f4b1664afa7f688b0e7fe974e8676a2"></a>

```
uint32_t Wiphy::flags
```

 **Description:**

[Wiphy](Wiphy.md)  device attributes 

## flags \[6/7\]<a name="ga66be1d87b4d2576cee91cd3867b93701"></a>

```
uint8_t TcpHeader::flags
```

 **Description:**

Flags 

## flags \[7/7\]<a name="ga01a8027b2e16aa30a6da3ee99c0f3890"></a>

```
uint32_t NetDevice::flags
```

 **Description:**

Network port status 

## fragInfo<a name="gaf329df46f50a5dcf4dd87c103317401b"></a>

```
uint16_t IpHeader::fragInfo
```

 **Description:**

Fragmentation information 

## fragThreshold<a name="gafa733ea2e4b2efa2dc10938956a95f85"></a>

```
uint32_t Wiphy::fragThreshold
```

 **Description:**

Fragment threshold 

## frameControl<a name="ga52e127b6032bc14b0828d775f45c164d"></a>

```
uint16_t Ieee80211Mgmt::frameControl
```

 **Description:**

Frame control field 

## freq \[1/2\]<a name="ga9489887bd02837a40e9560f1a4acd211"></a>

```
int16_t ScannedBssInfo::freq
```

 **Description:**

Center frequency of the channel where the BSS is located 

## freq \[2/2\]<a name="ga5ca4a2c4e1cdfe1d9e4bd1592855e5a0"></a>

```
uint16_t ConnetResult::freq
```

 **Description:**

Frequency of the AP 

## funType<a name="ga4a20c090f2e28ed317957d4ed5fc28fd"></a>

```
[IfType](IfType.md) NetDevice::funType
```

 **Description:**

Network port type 

## generation<a name="ga4b17833011fe840879c7bcd74aac9f9d"></a>

```
int32_t StationInfo::generation
```

 **Description:**

Generation number 

## getModule<a name="gad7c080e7ac22daf18529184da55e910c"></a>

```
struct [WifiModule](WifiModule.md)*(* WifiModuleIface::getModule) (void)
```

 **Description:**

Obtaining a WLAN module 

## getStats<a name="ga3dcf9dd183845770dc8589eb98e59fce"></a>

```
struct NetDevStats*(* NetDeviceInterFace::getStats) (struct [NetDevice](NetDevice.md) *netDev)
```

 **Description:**

Obtains the statistics. 

## hardHeaderLen<a name="ga585cec837551180e542b29d263dd585c"></a>

```
uint16_t NetDevice::hardHeaderLen
```

 **Description:**

Header length 

## hiddenSsid<a name="gac5c5a9f217e8fdf4d94cf78f8311d254"></a>

```
uint8_t Mac80211beaconParam::hiddenSsid
```

 **Description:**

Whether to hide the SSID 

## hslConfig<a name="gae67367af307406e4693e7c4cdba69baf"></a>

```
const struct HdfConfigWifiModuleConfig* WifiModuleConfig::hslConfig
```

 **Description:**

Configuration of each feature of the WLAN module 

## htCap<a name="gaf1a61194a3fdac2516e391534e5e15d6"></a>

```
struct [Ieee80211StaHtCap](Ieee80211StaHtCap.md) Ieee80211SupportedBand::htCap
```

 **Description:**

HT capability 

## htSupported<a name="gaf5a9bd33d4d6eaf38052d3c52c261db6"></a>

```
uint8_t Ieee80211StaHtCap::htSupported
```

 **Description:**

Whether the station supports HT 

## hwValue \[1/2\]<a name="ga88c500579917b7a4b0167623851abcf2"></a>

```
uint16_t Ieee80211Channel::hwValue
```

 **Description:**

Hardware information 

## hwValue \[2/2\]<a name="gaf1d7fcab109296f61b1e46315c56ad61"></a>

```
uint16_t Ieee80211Rate::hwValue
```

 **Description:**

Hardware information 

## hwValueShort<a name="ga0c64e3b8824a84ceab38b2c4c3c53e9c"></a>

```
uint16_t Ieee80211Rate::hwValueShort
```

 **Description:**

Hardware information specified when a short preamble is used 

## id<a name="ga2d5c09b859bc0faddc8a42339973bdd4"></a>

```
uint16_t IpHeader::id
```

 **Description:**

Each data packet sent by the host 

## ie \[1/2\]<a name="ga92b16a60570fd1d28b948ee43f9b0124"></a>

```
uint8_t* WifiScanRequest::ie
```

 **Description:**

IEEE 802.11 buffer 

## ie \[2/2\]<a name="ga8274aa0c44fe19a615c38c67eb799c87"></a>

```
uint8_t* WifiConnectParams::ie
```

 **Description:**

IEEE 802.11 information required for the connection 

## ieee80211Ptr<a name="ga3d04317fd4d2c8932808d6dd07fedcf4"></a>

```
struct [WirelessDev](WirelessDev.md)* NetDevice::ieee80211Ptr
```

 **Description:**

Pointer to a wireless device 

## ieLen \[1/2\]<a name="gaa26674156ac0814fbc1f45b8e11b7b9f"></a>

```
uint32_t WifiScanRequest::ieLen
```

 **Description:**

IEEE 802.11 buffer length 

## ieLen \[2/2\]<a name="gad5c61386055631b64c953fa46c2aad24"></a>

```
uint32_t WifiConnectParams::ieLen
```

 **Description:**

IEEE 802.11 length 

## iface<a name="ga8666b5068c46aa89a3cae49b7a31c224"></a>

```
struct [WifiModuleIface](WifiModuleIface.md)* WifiModule::iface
```

 **Description:**

APIs 

## ifrData<a name="gadc2f148a30a6ef88b5938fea193ac9e5"></a>

```
uint8_t* IfReq::ifrData
```

 **Description:**

Data pointer 

## iftype<a name="ga8e9277b73be8498a73999151e093693e"></a>

```
uint8_t WirelessDev::iftype
```

 **Description:**

API type 

## inactiveTime<a name="ga6326315bb50ed95fc0ce5ce65177cb78"></a>

```
uint32_t StationInfo::inactiveTime
```

 **Description:**

Duration \(in milliseconds\) since the last station activity 

## init \[1/4\]<a name="gabbafd20c6c6cc8eb20777cdd588b46cd"></a>

```
int32_t(* HdfWifiChipData::init) (struct [HdfWifiChipData](HdfWifiChipData.md) *chipData, const struct HdfConfigWifiChip *chipConfig)
```

 **Description:**

Function for initializing the chip 

## init \[2/4\]<a name="ga24cdc29146b8f84d021328e8a31269a5"></a>

```
int32_t(* NetDeviceInterFace::init) (struct [NetDevice](NetDevice.md) *netDev)
```

 **Description:**

Initializes a network device to be added. 

## init \[3/4\]<a name="ga8b09c66c75ed9515bbf5f76e25c86e57"></a>

```
int32_t(* WifiFeature::init) (struct [WifiFeature](WifiFeature.md) *feature)
```

 **Description:**

Function for initializing the feature 

## init \[4/4\]<a name="gadf3d907844092764d8c8d3ce150e1712"></a>

```
int32_t(* WifiModuleIface::init) (struct [WifiModule](WifiModule.md) *module)
```

 **Description:**

Initializing a WLAN module 

## interfaceModes<a name="ga33ab965c40e11c007cadf1116113ca21"></a>

```
uint16_t Wiphy::interfaceModes
```

 **Description:**

Bitmask of an API type that is valid for the wiphy device 

## interval<a name="ga691fb611afdc35bbf6951977119c8772"></a>

```
int32_t Mac80211beaconParam::interval
```

 **Description:**

[Beacon](Beacon.md)  interval 

## ioctl<a name="ga6c3d34c3329316632c7f6b6b19d2f983"></a>

```
int32_t(* NetDeviceInterFace::ioctl) (struct [NetDevice](NetDevice.md) *netDev, [IfReq](IfReq.md) *req, int32_t cmd)
```

 **Description:**

Used for the control command word. 

## ipAddr<a name="ga814742f62c24ff2895a18ad157df4874"></a>

```
uint32_t NetDevNotify::ipAddr
```

 **Description:**

IP address 

## key \[1/2\]<a name="ga0c19dd081453de295f3095c2cf7aced4"></a>

```
uint8_t* KeyParams::key
```

 **Description:**

Key content 

## key \[2/2\]<a name="ga6ca72a4cfcb196dda7c2ca2562a1b20b"></a>

```
const uint8_t* WifiConnectParams::key
```

 **Description:**

Wired Equivalent Privacy \(WEP\) key used for Shared Key Authentication \(SKA\) 

## keyIdx<a name="ga27eb8efb66b131f8495baf2dcaee6eb6"></a>

```
uint8_t WifiConnectParams::keyIdx
```

 **Description:**

Index of the WEP key used for SKA 

## keyLen \[1/2\]<a name="gae913f805139a4111b98617ab8e678528"></a>

```
int32_t KeyParams::keyLen
```

 **Description:**

Key length 

## keyLen \[2/2\]<a name="ga98603c2c633e6ca1ad940269cfb01e58"></a>

```
uint8_t WifiConnectParams::keyLen
```

 **Description:**

Key length 

## lastRxTime<a name="gaf3cfb6012fad954900ccded1305e0e73"></a>

```
uint32_t NetDevice::lastRxTime
```

 **Description:**

Last time when data is received 

## legacy<a name="gaf51b764aa77423df71236454f2804a62"></a>

```
uint16_t RateInfo::legacy
```

 **Description:**

100 kbit/s bit rate defined in 802.11a/b/g 

## len \[1/2\]<a name="ga559e952054ce59e81d2ff9b38634b60c"></a>

```
uint32_t NetBuf::len
```

 **Description:**

Length of the memory buffer 

## len \[2/2\]<a name="ga90b8c3dd672bad2f722900101db236f2"></a>

```
uint16_t UdpHeader::len
```

 **Description:**

Length of a data packet 

## LinkLayerType<a name="ga4758167363bad30116f4bcdb4cc1ae2a"></a>

```
[NetLinkType](WLAN.md#gad3175955d2e6ef3c4f52da9b509d5b4a) NetDevice::LinkLayerType
```

 **Description:**

Data link layer type 

## listenInterval \[1/2\]<a name="ga4755cf88f3c370bb7e704e7ab1f1f46b"></a>

```
uint16_t AssocReq::listenInterval
```

 **Description:**

Scan interval 

## listenInterval \[2/2\]<a name="gad95ef561c78f9312941cbd559e11b873"></a>

```
uint16_t ReassocReq::listenInterval
```

 **Description:**

Scan interval 

## llid<a name="gadc926d27f91b736e04f9ba2ffe663aeb"></a>

```
uint16_t StationInfo::llid
```

 **Description:**

Local mesh ID 

## lock<a name="gadd22ee64f7d9703d6c4cde54b512aaa0"></a>

```
struct Spinlock NetBufQueue::lock
```

 **Description:**

Queue operation lock 

## mac \[1/2\]<a name="gaa9ba863f7e3f07f710274cbfecb0080e"></a>

```
uint8_t MacConfigParam::mac[WLAN_MAC_ADDR_LEN]
```

 **Description:**

MAC address. For details about its length, see  **WLAN\_MAC\_ADDR\_LEN**. 

## mac \[2/2\]<a name="ga83cfa2d4899721ac3448d99ea5b0bef2"></a>

```
const uint8_t* StationDelParameters::mac
```

 **Description:**

MAC address of the station to which the connection is to be canceled 

## macAddr \[1/3\]<a name="gacbe765a13d3de60f6c4f297234444553"></a>

```
char NetDevice::macAddr[[MAC_ADDR_SIZE](WLAN.md#gae01dbae885bc8abecb82bd865515c081)]
```

 **Description:**

MAC address  [MAC\_ADDR\_SIZE](WLAN.md#gae01dbae885bc8abecb82bd865515c081) 

## macAddr \[2/3\]<a name="ga98f76b11c4cac6945526d048cb925e6c"></a>

```
uint8_t Mac80211DisconnectParam::macAddr[WLAN_MAC_ADDR_LEN]
```

 **Description:**

Device MAC address 

## macAddr \[3/3\]<a name="ga84ee6f62e15f1e8252d97b0b3ef55239"></a>

```
uint8_t* VifParams::macAddr
```

 **Description:**

MAC address 

## mask<a name="gabcb55b1def4998381497e79e602a61d5"></a>

```
uint32_t StaFlagUpdate::mask
```

 **Description:**

Flag mask 

## maxAntennaGain<a name="gacd256a8179e084497aad4cacfac77dc2"></a>

```
int32_t Ieee80211Channel::maxAntennaGain
```

 **Description:**

Maximum antenna gain, in dBi 

## maxPower<a name="gaf998a486d7bc53071e68374a13aa18d8"></a>

```
int32_t Ieee80211Channel::maxPower
```

 **Description:**

Maximum transmit power, in dBm 

## maxScanIeLen<a name="ga249fb8ce5c398f3c6588519e58cd11e9"></a>

```
uint16_t Wiphy::maxScanIeLen
```

 **Description:**

Maximum SSID length 

## maxScanSsids<a name="gac64622da7ddfc981d13380a66321ee61"></a>

```
uint8_t Wiphy::maxScanSsids
```

 **Description:**

Maximum number of scanned service set identifiers \(SSIDs\) 

## mcs \[1/2\]<a name="ga5a8aea5e5f47700d6634ec48dc4a1f9f"></a>

```
uint8_t RateInfo::mcs
```

 **Description:**

Modulation and Coding Scheme \(MCS\) index of the HT/VHT/HE rate 

## mcs \[2/2\]<a name="gab100d81d329ddf8584ade014d20acc2d"></a>

```
struct [Ieee80211McsInfo](Ieee80211McsInfo.md) Ieee80211StaHtCap::mcs
```

 **Description:**

MCS rate 

## mem<a name="gad94b7aff082f5d891a3250dfc6307ce0"></a>

```
uint8_t* NetBuf::mem
```

 **Description:**

Memory buffer address 

## mfp<a name="ga8212747b66b319e95586ad90d4191300"></a>

```
uint8_t WifiConnectParams::mfp
```

 **Description:**

Whether to enable Management Frame Protection \(MFP\) 

## mgmt<a name="ga345b0140ecaa55ffc7c85bf96548efc9"></a>

```
struct [Ieee80211Mgmt](Ieee80211Mgmt.md)* ScannedBssInfo::mgmt
```

 **Description:**

Start address of the management frame 

## mgmtLen<a name="gaa40e6cfe80596087c25e256215123890"></a>

```
uint32_t ScannedBssInfo::mgmtLen
```

 **Description:**

Management frame length 

## mlPriv<a name="gac2b0eefb68664e9458311017ce31275b"></a>

```
void* NetDevice::mlPriv
```

 **Description:**

Private structure for the driver 

## module<a name="ga1d78d86692abec4c85fa96ea5c446509"></a>

```
struct [WifiModule](WifiModule.md)* HdfWifiProductData::module
```

 **Description:**

Structure of the WLAN module 

## moduleConfig<a name="gaa54566af9b7dda68e119649b3510c858"></a>

```
struct [WifiModuleConfig](WifiModuleConfig.md) WifiModule::moduleConfig
```

 **Description:**

Module configurations 

## modulePrivate<a name="gab8c955bd3dd2cb79c3c0c3dfdc3b08f5"></a>

```
void* WifiModule::modulePrivate
```

 **Description:**

Private data 

## mtu<a name="ga3c55b245d63ce32ea02f2890fc8e75a8"></a>

```
uint32_t NetDevice::mtu
```

 **Description:**

Maximum transmission unit 

## n\_akmSuites<a name="ga35627fc7ac0924a52e51427375501f8a"></a>

```
int32_t CryptoSettings::n_akmSuites
```

 **Description:**

Number of authentication and key management \(AKM\) suites 

## n\_ciphersPairwise<a name="gace9dbbf9c1a035b350224b1832d35377"></a>

```
int32_t CryptoSettings::n_ciphersPairwise
```

 **Description:**

Number of unicast ciphers supported by the access point \(AP\) 

## name \[1/3\]<a name="ga74b1c5d9a04465f4b47b36ece7470aab"></a>

```
char NetDevice::name[IFNAMSIZ]
```

 **Description:**

Network device name  **IFNAMSIZ** 

## name \[2/3\]<a name="gae63e4c5602dbc64bd9905d6b6a4e7aad"></a>

```
char WifiFeature::name[[MAX_WIFI_COMPONENT_NAME_LEN](WLAN.md#gaf460a45a5e365279ca6bc5b3e8750542)]
```

 **Description:**

[Feature](Feature.md)  name, which can contain a maximum of 10 characters 

## name \[3/3\]<a name="ga02ee61c30fc06116d5dee320eda37bfe"></a>

```
char HdfWifiChipData::name[[MAX_WIFI_COMPONENT_NAME_LEN](WLAN.md#gaf460a45a5e365279ca6bc5b3e8750542)]
```

 **Description:**

Chip name 

## nBitrates<a name="ga355299d64b9af1d889750bda9216734b"></a>

```
int32_t Ieee80211SupportedBand::nBitrates
```

 **Description:**

Length of the array of supported bit rates 

## nChannels \[1/2\]<a name="gaf075c96dac24e5b685d35481c78ecb01"></a>

```
int32_t Ieee80211SupportedBand::nChannels
```

 **Description:**

Length of the array of supported channels 

## nChannels \[2/2\]<a name="ga3150e4a25b1800ee713e08fbf9077116"></a>

```
uint32_t WifiScanRequest::nChannels
```

 **Description:**

Number of channels to scan for 

## nCipherSuites<a name="gab6cb6ce28cef7f1f5dc0d19380e8ad05"></a>

```
int32_t Wiphy::nCipherSuites
```

 **Description:**

Number of supported cipher suites 

## neededHeadRoom<a name="ga9241a41c1cb62a68e3d8c93b9dfe4790"></a>

```
uint16_t NetDevice::neededHeadRoom
```

 **Description:**

Length reserved for the header in netbuff[NetBuf](NetBuf.md) 

## neededTailRoom<a name="ga3ad6638d07aef608b8d5e4b20a478e03"></a>

```
uint16_t NetDevice::neededTailRoom
```

 **Description:**

Length reserved for the tail in netbuff[NetBuf](NetBuf.md) 

## netdev<a name="gacf9e3f94cbac9cf8ae3382aea0d6c5f6"></a>

```
struct [NetDevice](NetDevice.md)* WirelessDev::netdev
```

 **Description:**

Network device 

## netDeviceIf<a name="gaf154f5a9cbf4d297bc6fc7550ae9a819"></a>

```
struct [NetDeviceInterFace](NetDeviceInterFace.md)* NetDevice::netDeviceIf
```

 **Description:**

Network device interface 

## netifCateg<a name="ga95102f11976f69a7c700944614fa06b2"></a>

```
[NetIfCategory](WLAN.md#ga530241881cd17e03f8ae254ef1d9755e) NetDevice::netifCateg
```

 **Description:**

Network interface category  [NetIfCategory](WLAN.md#ga530241881cd17e03f8ae254ef1d9755e) 

## netifNotify<a name="ga518102ebc29b985161160ae22b066faf"></a>

```
uint32_t(* NetDeviceInterFace::netifNotify) (struct [NetDevice](NetDevice.md) *netDev, [NetDevNotify](NetDevNotify.md) *notify)
```

 **Description:**

Notifies the network port status. 

## notifyType<a name="ga5b652685d8841c46872427b87507f4e7"></a>

```
uint32_t NetDevNotify::notifyType
```

 **Description:**

Notification type \(reserved\) 

## nss<a name="gac9516b58cac5a7294541958513514c0b"></a>

```
uint8_t RateInfo::nss
```

 **Description:**

Number of streams \(for VHT and HE only\) 

## nSsids<a name="gaf7bf0f80492f28c7c285f8023505bb8e"></a>

```
uint32_t WifiScanRequest::nSsids
```

 **Description:**

Number of SSIDs to scan for 

## offset \[1/2\]<a name="ga5f5c974dbd2e5608b3ea2e768e4559ca"></a>

```
int64_t StationInfo::offset
```

 **Description:**

Time offset of station 

## offset \[2/2\]<a name="gabac9ba66ff160d881083b1f173f411f9"></a>

```
uint8_t TcpHeader::offset
```

 **Description:**

Header length 

## open<a name="ga154f75bcfd914b1fb243041186b60a3f"></a>

```
int32_t(* NetDeviceInterFace::open) (struct [NetDevice](NetDevice.md) *netDev)
```

 **Description:**

Opens the data link layer. 

## operationType<a name="ga98a709ca72bbd2625125b378c08b6d9e"></a>

```
uint8_t Mac80211beaconParam::operationType
```

 **Description:**

Operation type 

## ops<a name="ga920007113f95ee9ce9b0d51ca0cf42bc"></a>

```
struct [WifiMac80211Ops](WifiMac80211Ops.md)* HdfWifiChipData::ops
```

 **Description:**

Chip MAC address 

## origFlags<a name="gaa8e6146a2fa16a47e794d7d9bbaccf1e"></a>

```
uint32_t Ieee80211Channel::origFlags
```

 **Description:**

Channel flags 

## origMag<a name="gaf5bc0d20f7c46fbcfd69cb62c3470dfe"></a>

```
int32_t Ieee80211Channel::origMag
```

 **Description:**

Reserved field 

## origMpwr<a name="gaa9666ab4a0f723741328722d1ab74588"></a>

```
int32_t Ieee80211Channel::origMpwr
```

 **Description:**

Reserved field 

## owner<a name="ga6f725a86ac73ba02449952d3f8fbcff9"></a>

```
struct [NetDevice](NetDevice.md)* NetDevice::owner
```

 **Description:**

Network device 

## p2pMode<a name="gad17af431fa1dd6157d3118023459a784"></a>

```
uint8_t MacConfigParam::p2pMode
```

 **Description:**

Whether the peer-to-peer \(P2P\) mode is used. 

## permAddr<a name="ga5396b8e87fe6a6be0c7dd789fe289c50"></a>

```
uint8_t Wiphy::permAddr[WLAN_MAC_ADDR_LEN]
```

 **Description:**

Permanent MAC address of the wiphy device. For its length, see  **WLAN\_MAC\_ADDR\_LEN**. 

## plid<a name="ga7dedfef626385689a1baa20e9764ff05"></a>

```
uint16_t StationInfo::plid
```

 **Description:**

Peer mesh ID 

## plinkState<a name="gaf505fd1078d9f5a0d5374d9538e8d5bb"></a>

```
uint8_t StationInfo::plinkState
```

 **Description:**

Mesh peer state 

## prefixSsidScanFlag<a name="ga5b6c8df255d62a73114aad42c1e4868d"></a>

```
uint8_t WifiScanRequest::prefixSsidScanFlag
```

 **Description:**

Reserved field 

## presetChandef<a name="ga142433e20a4e8168774cf50dfbbfd27b"></a>

```
struct [ChannelDef](ChannelDef.md) WirelessDev::presetChandef
```

 **Description:**

Channel information 

## priv<a name="ga760737c03ad122b360ca8ed814869e4b"></a>

```
uint8_t Wiphy::priv[WIPHY_PRIV_SIZE]
```

 **Description:**

Reserved field 

## privacy<a name="ga81e32b68cb7ae4a68b1d42633fc181fe"></a>

```
uint8_t WifiConnectParams::privacy
```

 **Description:**

Whether to use a privacy-enabled AP 

## probeResp \[1/2\]<a name="gaf7a356fae762de47cd69f142725c88ed"></a>

```
struct { ... } ::probeResp
```

 **Description:**

Probe response frame 

## probeResp \[2/2\]<a name="ga4111b0df54692760f9e56b52fe1ba841"></a>

```
struct [ProbeResp](ProbeResp.md) Ieee80211Mgmt::probeResp
```

 **Description:**

Probe response frame 

## product\_name<a name="ga97418ebfac2a3a4ecc77c3c98b1ae810"></a>

```
char HdfWifiProductData::product_name[[MAX_WIFI_COMPONENT_NAME_LEN](WLAN.md#gaf460a45a5e365279ca6bc5b3e8750542)]
```

 **Description:**

WLAN module name, which contains a maximum of 10 bytes 

## protocol<a name="ga029ab0914b5854efe279e442aec3b423"></a>

```
uint8_t IpHeader::protocol
```

 **Description:**

Protocol, such as 1 \(ICMP\), 2 \(IGMP\), 6 \(TCP\), 17 \(UDP\), and 89 \(OSPF\) 

## qmap<a name="gaa56eababaaaeda2ec724f21889a20ccd"></a>

```
uint32_t NetBuf::qmap
```

 **Description:**

Queue mappings of the network data buffer 

## reasonCode \[1/4\]<a name="gaa31a88b9f6b93548fe64aa39048bc78d"></a>

```
uint16_t Deauth::reasonCode
```

 **Description:**

Deauthentication cause code 

## reasonCode \[2/4\]<a name="gabbe22887613c2c96802b092f23898553"></a>

```
uint16_t Disassoc::reasonCode
```

 **Description:**

Cause code 

## reasonCode \[3/4\]<a name="gaadcc8f71dfd7b2c5ecc072cceb5fa3bb"></a>

```
uint16_t StationDelParameters::reasonCode
```

 **Description:**

Cause of the cancellation 

## reasonCode \[4/4\]<a name="ga5fe7610b3bff3864f9a2fee995c907ef"></a>

```
uint16_t Mac80211DisconnectParam::reasonCode
```

 **Description:**

Disconnection reason code 

## reassocReq \[1/2\]<a name="ga6adc227e753714342c3f1423aa5f16f7"></a>

```
struct { ... } ::reassocReq
```

 **Description:**

Re-authentication 

## reassocReq \[2/2\]<a name="ga6e7eeaa3e4d604a221f598e51c3869eb"></a>

```
struct [ReassocReq](ReassocReq.md) Ieee80211Mgmt::reassocReq
```

 **Description:**

Re-authentication 

## reassocResp \[1/2\]<a name="gab23b4bd33fd0295774a4ca362ea9312d"></a>

```
struct [ReassocResp](ReassocResp.md) Ieee80211Mgmt::reassocResp
```

 **Description:**

Re-authentication response 

## reassocResp \[2/2\]<a name="gac250479a0ad8da7dfe10bb5f55396eae"></a>

```
struct { ... } ::reassocResp
```

 **Description:**

Re-authentication response 

## reqIe<a name="ga1ba76217df6a0a67be62ab623f68ee66"></a>

```
uint8_t* ConnetResult::reqIe
```

 **Description:**

Association request IE 

## reqIeLen<a name="gaade69412094ceaa5374c76513064f00a"></a>

```
uint32_t ConnetResult::reqIeLen
```

 **Description:**

Length of the association request IE 

## reserved<a name="ga92cf658154d7d1fddeebc4a01cc317d6"></a>

```
uint8_t Ieee80211McsInfo::reserved[IEEE80211_MACINFO_RESV]
```

 **Description:**

Reserved field 

## resv \[1/4\]<a name="ga8ae51118ee5e1a121bad85055ecad454"></a>

```
uint8_t Ieee80211Channel::resv[IEEE80211_CHANNEL_RESV]
```

 **Description:**

Reserved field 

## resv \[2/4\]<a name="ga9bb2fd298749eab513163e3a7a2b03ee"></a>

```
uint8_t WifiScanRequest::resv[SCAN_REQUEST_RESV_SIZE]
```

 **Description:**

Reserved field 

## resv \[3/4\]<a name="ga7c1cd7fbd4ccdf7babf89394cc78ab77"></a>

```
uint8_t WirelessDev::resv[WIRELESS_DEV_RESV_SIZE]
```

 **Description:**

Reserved field 

## resv \[4/4\]<a name="ga740712d61cb553af65d36d1a65f0a483"></a>

```
uint8_t RateInfo::resv
```

 **Description:**

Reserved 

## resv1<a name="ga4bf7e03861cdefd017d6669994a1df43"></a>

```
uint8_t StationInfo::resv1
```

 **Description:**

Reserved 

## rspIe<a name="ga113ce1420c647c51b89dca5ab436f82e"></a>

```
uint8_t* ConnetResult::rspIe
```

 **Description:**

Association response IE 

## rspIeLen<a name="ga0756bccba43358d534d8c5a254d63686"></a>

```
uint32_t ConnetResult::rspIeLen
```

 **Description:**

Length of the association response IE 

## rsv \[1/2\]<a name="gaec41f143c3551e59da63ab2e9d9c9c53"></a>

```
uint8_t Ieee80211Rate::rsv[IEEE80211_RATE_RESV]
```

 **Description:**

Reserved field 

## rsv \[2/2\]<a name="ga197b5045451ca25a03f478df0bd03514"></a>

```
uint8_t NetBuf::rsv[[MAX_NETBUF_RESEVER_SIZE](WLAN.md#ga794c035a19a38acc000146a8f9a4ec80)]
```

 **Description:**

Reserved field. For details, see  [MAX\_NETBUF\_RESEVER\_SIZE](WLAN.md#ga794c035a19a38acc000146a8f9a4ec80). 

## rtsThreshold<a name="ga00874e60aa7dc8c7455732e633586813"></a>

```
uint32_t Wiphy::rtsThreshold
```

 **Description:**

[Request](Request.md)  To Send \(RTS\) threshold 

## rxBytes \[1/2\]<a name="ga8445328bc8d5cc4ba8bc5d5f8ec0c1fa"></a>

```
uint64_t StationInfo::rxBytes
```

 **Description:**

Received bytes 

## rxBytes \[2/2\]<a name="ga809ff3fc1f051abbb655cc7ea6cbd900"></a>

```
uint32_t NetDevStats::rxBytes
```

 **Description:**

Total number of received bits 

## rxDropped<a name="gae3a86ad63c016badbd0ac72bf572afa3"></a>

```
uint32_t NetDevStats::rxDropped
```

 **Description:**

Packets that are dropped after being received 

## rxDroppedMisc<a name="ga9506e6f1cd855cf8116dd650f68966ac"></a>

```
uint32_t StationInfo::rxDroppedMisc
```

 **Description:**

Number of receive failures 

## rxErrors<a name="gabf0cb61284e0cba862c5e8db62b63fa9"></a>

```
uint32_t NetDevStats::rxErrors
```

 **Description:**

Number of received error packets 

## rxHighest<a name="gad76dc235ae05680bdde62564f5a6c10b"></a>

```
uint16_t Ieee80211McsInfo::rxHighest
```

 **Description:**

Maximum rate for receiving data 

## rxMask<a name="gaaa1851c2f6db9ccf446f70eb272196f5"></a>

```
uint8_t Ieee80211McsInfo::rxMask[IEEE80211_HT_MCS_MASK_LEN]
```

 **Description:**

Mask for receiving data 

## rxPackets \[1/2\]<a name="gac890bb6b9e08670ec2bb1a0c41ab1cdc"></a>

```
uint32_t StationInfo::rxPackets
```

 **Description:**

Received data packets 

## rxPackets \[2/2\]<a name="ga691401a65931b7753fe1f67749074755"></a>

```
uint32_t NetDevStats::rxPackets
```

 **Description:**

Total number of received packets 

## rxRate<a name="ga7ccb9050859ba196054590b2294f3a40"></a>

```
struct [RateInfo](RateInfo.md) StationInfo::rxRate
```

 **Description:**

Receive rate 

## sAddr<a name="ga22e36dfd118fbe9deee40135f87a0568"></a>

```
uint32_t IpHeader::sAddr
```

 **Description:**

Source address 

## selectQueue<a name="ga3e08c5be1dbe6e4aa6fc1f930783c295"></a>

```
uint16_t(* NetDeviceInterFace::selectQueue) (struct [NetDevice](NetDevice.md) *netDev, struct [NetBuf](NetBuf.md) *netBuff)
```

 **Description:**

Selects a priority queue. 

## seq<a name="ga00bfccb54d7fc37bc2ddbf9ebf3937bb"></a>

```
uint8_t* KeyParams::seq
```

 **Description:**

Content of a Temporal Key Integrity Protocol \(TKIP\) or Counter Mode Cipher Block Chaining Message Authentication Code Protocol \(CCMP\) key 

## seqCtrl<a name="gab3b6ce7596b771a8bb0af0edbad416fd"></a>

```
uint16_t Ieee80211Mgmt::seqCtrl
```

 **Description:**

Sequence control 

## seqLen<a name="ga6b1bb1722c1205c1b560c01c58d35018"></a>

```
int32_t KeyParams::seqLen
```

 **Description:**

Length of a TKIP or CCMP key 

## seqNum<a name="ga5409de9f82a50bf5113dafb316118d4b"></a>

```
uint32_t TcpHeader::seqNum
```

 **Description:**

Sequence number 

## set<a name="ga9c47590735e6ba21c557361770f76338"></a>

```
uint32_t StaFlagUpdate::set
```

 **Description:**

Flag value 

## setChannel<a name="ga166ca94a9482995f3e1f58263eeeed02"></a>

```
int32_t(* WifiMac80211Ops::setChannel) ([NetDevice](NetDevice.md) *netDev)
```

 **Description:**

Setting the channel 

## setDefaultKey<a name="gae4e2e0af8777ab0bae98b1816664bddc"></a>

```
int32_t(* WifiMac80211Ops::setDefaultKey) (struct [NetDevice](NetDevice.md) *netdev, uint8_t keyIndex, bool unicast, bool multicas)
```

 **Description:**

Setting the default key 

## setMacAddr \[1/2\]<a name="ga177446df24b19e4ddca32e9719d6fe8e"></a>

```
int32_t(* WifiMac80211Ops::setMacAddr) ([NetDevice](NetDevice.md) *netDev, [Mac80211SetMacParam](WLAN.md#ga85f7d8a3795887f090e0a6439b1df6e1) *param)
```

 **Description:**

Setting the MAC address 

## setMacAddr \[2/2\]<a name="ga104f6b8049728769f54563aa242850b8"></a>

```
int32_t(* NetDeviceInterFace::setMacAddr) (struct [NetDevice](NetDevice.md) *netDev, void *addr)
```

 **Description:**

Sets the MAC address. 

## setMeshId<a name="ga37e19745783d5dbf8439b9f1f89ca6f5"></a>

```
int32_t(* WifiMac80211Ops::setMeshId) ([NetDevice](NetDevice.md) *netDev, const char *meshId, uint32_t meshIdLen)
```

 **Description:**

Setting the mesh ID 

## setNetIfStatus<a name="ga334e7e9c31ff9408ba67aed1cb96a174"></a>

```
void(* NetDeviceInterFace::setNetIfStatus) (struct [NetDevice](NetDevice.md) *netDev, [NetIfStatus](WLAN.md#ga0fb482694e5eac3f48c75de1749c8baf) status)
```

 **Description:**

Sets the network port status. 

## setSsid<a name="ga519c91a244639e25a8c604e284486873"></a>

```
int32_t(* WifiMac80211Ops::setSsid) ([NetDevice](NetDevice.md) *netDev, const uint8_t *ssid, uint32_t ssidLen)
```

 **Description:**

Setting the SSID 

## signal \[1/2\]<a name="gaf34477153f092bd07bd8a80ca29d16bf"></a>

```
int8_t StationInfo::signal
```

 **Description:**

Signal strength 

## signal \[2/2\]<a name="ga20f18f7993df9723a0f3e7520ae715e2"></a>

```
int32_t ScannedBssInfo::signal
```

 **Description:**

Signal strength 

## signalAvg<a name="ga5423c3f5c2797588018ae3e32582e0bf"></a>

```
int8_t StationInfo::signalAvg
```

 **Description:**

Average signal strength 

## signalType<a name="ga0c0e8af92ed7d85cbcc04bcf4f13a8b7"></a>

```
uint8_t Wiphy::signalType
```

 **Description:**

Signal type 

## size<a name="gab8e922b274e1854731b5fd22d8dde62d"></a>

```
uint32_t NetBufQueue::size
```

 **Description:**

Number of network data buffers in the queue 

## source<a name="gaa51376bc21358f5c14e8c21ddc9afa00"></a>

```
uint16_t UdpHeader::source
```

 **Description:**

Source port number 

## specialEtherTypeProcess<a name="ga8bb9ea881b1bdabe8c45f721310823b1"></a>

```
[ProcessingResult](WLAN.md#ga9c1d6e7df4468671742cb76f72b67af1)(* NetDeviceInterFace::specialEtherTypeProcess) (const struct [NetDevice](NetDevice.md) *netDev, struct [NetBuf](NetBuf.md) *buff)
```

 **Description:**

Performs private processing without involving network-layer data. 

## specialProcPriv<a name="ga659f5eb4ee2cef37cb93acea357acb75"></a>

```
void* NetDevice::specialProcPriv
```

 **Description:**

Private structure for data processing 

## sPort<a name="gae29f9cbe74e4e7f7543e74bb8d039f15"></a>

```
uint16_t TcpHeader::sPort
```

 **Description:**

Source port number 

## srcAddr<a name="ga636095dd14f2219a50cd5d86e7f94cde"></a>

```
uint8_t Ieee80211Mgmt::srcAddr[6]
```

 **Description:**

Source MAC address 

## ssid \[1/2\]<a name="ga320f45c28aa8ca8095159b8a0a114268"></a>

```
uint8_t WifiSsid::ssid[IEEE80211_MAX_SSID_LEN]
```

 **Description:**

SSID content, which contains a maximum of 32 bytes 

## ssid \[2/2\]<a name="ga875dd450960cc445dd2a12355bc6912c"></a>

```
uint8_t* WifiConnectParams::ssid
```

 **Description:**

SSID 

## ssidLen \[1/3\]<a name="ga35c2bd750767a87abf1c45b480124669"></a>

```
uint8_t WifiSsid::ssidLen
```

 **Description:**

SSID length 

## ssidLen \[2/3\]<a name="ga18a38015e45de3571893b8c1edea991a"></a>

```
uint32_t WifiConnectParams::ssidLen
```

 **Description:**

SSID length 

## ssidLen \[3/3\]<a name="gac5c6ea249ba044d37f2b85df506cd898"></a>

```
uint8_t Mac80211Ssids::ssidLen
```

 **Description:**

SSID length 

## ssids<a name="ga761056fae3d79073bbc33ad3f00a7319"></a>

```
struct [WifiSsid](WifiSsid.md)* WifiScanRequest::ssids
```

 **Description:**

SSIDs to scan for 

## staFlags<a name="gae3d8b6844b2838f2622405f27d9eb33b"></a>

```
struct [StaFlagUpdate](StaFlagUpdate.md) StationInfo::staFlags
```

 **Description:**

Station flag masks and values 

## startAp<a name="ga203437a6b1d66758f2217f7154ce1210"></a>

```
int32_t(* WifiMac80211Ops::startAp) ([NetDevice](NetDevice.md) *netDev)
```

 **Description:**

Starting an AP 

## startScan<a name="ga259da70c25a528287c433af2f7bcf530"></a>

```
int32_t(* WifiMac80211Ops::startScan) ([NetDevice](NetDevice.md) *netDev, struct [WifiScanRequest](WifiScanRequest.md) *param)
```

 **Description:**

Starting a scan based on the specified parameters 

## state<a name="gaf3ac6e671103cb8319d7ed2af62883f2"></a>

```
char HdfWifiProductData::state
```

 **Description:**

WLAN module state 

## stats<a name="gafdd796dab998fb2ff695af4d50abdc13"></a>

```
struct NetDevStats NetDevice::stats
```

 **Description:**

Network statistics 

## statusCode \[1/4\]<a name="gaf37ac11db8228fec9975121b199311f7"></a>

```
uint16_t Auth::statusCode
```

 **Description:**

Authentication status code 

## statusCode \[2/4\]<a name="gafffefc2805012b07d7f23dcc3cc014e5"></a>

```
uint16_t AssocResp::statusCode
```

 **Description:**

Status code 

## statusCode \[3/4\]<a name="ga245f8361fce97aa71072505cac290411"></a>

```
uint16_t ReassocResp::statusCode
```

 **Description:**

Status code 

## statusCode \[4/4\]<a name="gaddcc87402a9e4e6f09098d5e7c25eebe"></a>

```
uint16_t ConnetResult::statusCode
```

 **Description:**

16-bit status code defined in the IEEE protocol 

## stop<a name="ga5e328f3dc0b610672889e66b33bb7cf8"></a>

```
int32_t(* NetDeviceInterFace::stop) (struct [NetDevice](NetDevice.md) *netDev)
```

 **Description:**

Closes the data link layer. 

## stopAp<a name="gaf30acc8bd9ecd9bffbc46f423423266e"></a>

```
int32_t(* WifiMac80211Ops::stopAp) ([NetDevice](NetDevice.md) *netDev)
```

 **Description:**

Stopping an AP 

## subtype<a name="gac649567339d882d98c5f4ba98bbb241e"></a>

```
uint8_t StationDelParameters::subtype
```

 **Description:**

Cancellation type 

## timestamp \[1/2\]<a name="ga9ff8a9a52a3e4f341e7ff49dd7bf76b8"></a>

```
uint64_t Beacon::timestamp
```

 **Description:**

Timestamp 

## timestamp \[2/2\]<a name="ga061a09e9bc3131127aa09d956f60b040"></a>

```
uint64_t ProbeResp::timestamp
```

 **Description:**

Timestamp 

## tos<a name="ga324f15b4a41342c026ce3ad253ed9498"></a>

```
uint8_t IpHeader::tos
```

 **Description:**

[Service](Service.md)  type 

## totLen<a name="ga35aa269c5b304d238c65aedaa28e3da5"></a>

```
uint16_t IpHeader::totLen
```

 **Description:**

Total length of an IP data packet 

## ttl<a name="gad380e64b2d33d75ce04d65126b54fb8f"></a>

```
uint8_t IpHeader::ttl
```

 **Description:**

Generation time 

## txBytes \[1/2\]<a name="ga3084ceeea5b4c0ab032f59f5c5988ef8"></a>

```
uint64_t StationInfo::txBytes
```

 **Description:**

Transmitted bytes 

## txBytes \[2/2\]<a name="ga665048e0ce5b8dffa2a3b69bad0bf231"></a>

```
uint32_t NetDevStats::txBytes
```

 **Description:**

Total number of transmitted bits 

## txDropped<a name="ga6d9439773d9721261de50a521c301fd9"></a>

```
uint32_t NetDevStats::txDropped
```

 **Description:**

Packets dropped before transmission 

## txErrors<a name="gac95614d9e1d400c6ed6f06b8f6aaf0a0"></a>

```
uint32_t NetDevStats::txErrors
```

 **Description:**

Transmitted error packets 

## txFailed<a name="gab02c662294106f07045b103fcf4eb689"></a>

```
uint32_t StationInfo::txFailed
```

 **Description:**

Number of failed transmissions 

## txPackets \[1/2\]<a name="ga0f048248764942c6717dce0695039c1d"></a>

```
uint32_t StationInfo::txPackets
```

 **Description:**

Transmitted data packets 

## txPackets \[2/2\]<a name="gac9d132b276538f055db2443e61f00b72"></a>

```
uint32_t NetDevStats::txPackets
```

 **Description:**

Total number of transmitted packets 

## txParams<a name="ga9cb852fd0e898070ffb355080d4079cd"></a>

```
uint8_t Ieee80211McsInfo::txParams
```

 **Description:**

Parameters for sending data 

## txPetries<a name="gaae49c0ae8a58b58adf92be62af7147fd"></a>

```
uint32_t StationInfo::txPetries
```

 **Description:**

Number of retransmissions 

## txRate<a name="ga959e150b0327d9a30db768aec89426ae"></a>

```
struct [RateInfo](RateInfo.md) StationInfo::txRate
```

 **Description:**

Transmission rate 

## type<a name="ga4c59fb9385e56ed8017ee48d36bac554"></a>

```
uint16_t HdfWifiChipData::type
```

 **Description:**

Chip type 

## updateModule<a name="ga5166022e5100e57fe0b307a4254e3dc1"></a>

```
int32_t(* WifiModuleIface::updateModule) (struct [WifiModule](WifiModule.md) *module)
```

 **Description:**

Updating a WLAN module based on a specified configuration. 

## urgent<a name="ga0c402826ed93d697342d8b1108db7754"></a>

```
uint16_t TcpHeader::urgent
```

 **Description:**

Urgent pointer 

## use4Addr<a name="ga554a530b88a15955fd9859ec08b569f3"></a>

```
int32_t VifParams::use4Addr
```

 **Description:**

Whether to use a frame containing four addresses 

## variable \[1/7\]<a name="ga114bed8793f4e32fba36ca20c9ac10d8"></a>

```
uint8_t Auth::variable[0]
```

 **Description:**

Algorithm challenge information stored in a flexible array 

## variable \[2/7\]<a name="ga69066d587669a7b69106d618e90fbad3"></a>

```
uint8_t AssocReq::variable[0]
```

 **Description:**

SSID and rate information stored in a flexible array 

## variable \[3/7\]<a name="gaf087bcdc5ec6bd2fc84981ccc1b85612"></a>

```
uint8_t AssocResp::variable[0]
```

 **Description:**

Rate information stored in a flexible array 

## variable \[4/7\]<a name="ga27b1d2abd28404a65166381dffdd5d57"></a>

```
uint8_t ReassocReq::variable[0]
```

 **Description:**

SSID and rate information stored in a flexible array 

## variable \[5/7\]<a name="gaf330f60c8afa98503226325a3d4328f9"></a>

```
uint8_t ReassocResp::variable[0]
```

 **Description:**

Rate information stored in a flexible array 

## variable \[6/7\]<a name="ga0de9d9ef52da27a0a11753d152c2fb64"></a>

```
uint8_t Beacon::variable[0]
```

 **Description:**

SSID and rate information 

## variable \[7/7\]<a name="ga9606f7f13ca77c203e07d48e65608bb3"></a>

```
uint8_t ProbeResp::variable[0]
```

 **Description:**

SSID and rate information 

## versionAndHl<a name="gae31602cb3fb4f012749e6d44e73bd5bf"></a>

```
uint8_t IpHeader::versionAndHl
```

 **Description:**

Version and header length 

## watchdogTime<a name="ga480ec41047ece56996f42b0f72a6e079"></a>

```
int32_t NetDevice::watchdogTime
```

 **Description:**

Watchdog duration 

## wdev<a name="ga09f1cdfc6c524ca96aed6b1894baa720"></a>

```
struct [WirelessDev](WirelessDev.md)* WifiScanRequest::wdev
```

 **Description:**

A specified wireless device to scan for 

## width<a name="gae9ff862b7d4a7145eb00275d57938b4f"></a>

```
enum [WifiChannelType](WLAN.md#ga9d902b330de99c24b2a8c3ba7120af21) ChannelDef::width
```

 **Description:**

Bandwidth 

## window<a name="ga55cc45eeabc0f857e51e8864ae45de8e"></a>

```
uint16_t TcpHeader::window
```

 **Description:**

Window size 

## wiphy \[1/2\]<a name="ga86835b49d9ac8e3965d710334d1ecdf2"></a>

```
struct [Wiphy](Wiphy.md)* WirelessDev::wiphy
```

 **Description:**

[Wiphy](Wiphy.md)  device 

## wiphy \[2/2\]<a name="ga43dd029f6f34ccb0255e519aded47478"></a>

```
struct [Wiphy](Wiphy.md)* WifiScanRequest::wiphy
```

 **Description:**

A specified wiphy device to scan for 

## wlanType<a name="gaf957402f9938b5bf37a7c39737f18e69"></a>

```
[Protocol80211IfType](WLAN.md#gac69954f56fcc99fc8aac68aa157831c7) IfType::wlanType
```

 **Description:**

WLAN network port type: AP or STA 

## wpaVersions<a name="ga2b21ef556b428238d4dc5009b82087ff"></a>

```
uint32_t CryptoSettings::wpaVersions
```

 **Description:**

WPA version 

## xmit<a name="ga5d6e31f59da2eef0998deadd40e13304"></a>

```
[NetDevTxResult](WLAN.md#ga9fb4e578a15db1b0087d7b3831591ced)(* NetDeviceInterFace::xmit) (struct [NetDevice](NetDevice.md) *netDev, struct [NetBuf](NetBuf.md) *netBuff)
```

 **Description:**

Sends data. 

