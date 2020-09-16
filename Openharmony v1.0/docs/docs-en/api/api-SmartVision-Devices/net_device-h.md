# net\_device.h<a name="EN-US_TOPIC_0000001055358082"></a>

## **Overview**<a name="section240164416084831"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Defines WLAN network device interfaces. 

This module provides network device operations for driver development. The operations are as follows: Initializes, adds, obtains, and deletes a network device. Reports network data, informs the network layer of the data link layer status, sets IP addresses, and starts or stops Dynamic Host Configuration Protocol \(DHCP\). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section767259753084831"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1377252997084831"></a>
<table><thead align="left"><tr id="row821801301084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p704658272084831"><a name="p704658272084831"></a><a name="p704658272084831"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1994740131084831"><a name="p1994740131084831"></a><a name="p1994740131084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1403621384084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2130790879084831"><a name="p2130790879084831"></a><a name="p2130790879084831"></a><a href="etherheader.md">EtherHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p451793521084831"><a name="p451793521084831"></a><a name="p451793521084831"></a>Defines the Ethernet header information of a data frame, including the destination address, source address, and Ethernet type. </p>
</td>
</tr>
<tr id="row850346955084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p279686349084831"><a name="p279686349084831"></a><a name="p279686349084831"></a><a href="ipheader.md">IpHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2023365489084831"><a name="p2023365489084831"></a><a name="p2023365489084831"></a>Defines the IP header information of a data frame, including the version number, service type, and total length. </p>
</td>
</tr>
<tr id="row2099612347084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p815084645084831"><a name="p815084645084831"></a><a name="p815084645084831"></a><a href="udpheader.md">UdpHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p653034504084831"><a name="p653034504084831"></a><a name="p653034504084831"></a>Defines the UDP header information of a data frame, including the source port number and destination port number. </p>
</td>
</tr>
<tr id="row2115210426084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p514879067084831"><a name="p514879067084831"></a><a name="p514879067084831"></a><a href="tcpheader.md">TcpHeader</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1423214414084831"><a name="p1423214414084831"></a><a name="p1423214414084831"></a>Defines the TCP header information of a data frame, including the source port number and destination port number. </p>
</td>
</tr>
<tr id="row391167139084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1896288955084831"><a name="p1896288955084831"></a><a name="p1896288955084831"></a><a href="ipv4addr.md">IpV4Addr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2065704474084831"><a name="p2065704474084831"></a><a name="p2065704474084831"></a>Defines an IPv4 address. </p>
</td>
</tr>
<tr id="row1372327129084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1114969443084831"><a name="p1114969443084831"></a><a name="p1114969443084831"></a><a href="netdevnotify.md">NetDevNotify</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1543654266084831"><a name="p1543654266084831"></a><a name="p1543654266084831"></a>Defines a network device notification, including an IP address and the notification type. </p>
</td>
</tr>
<tr id="row910370793084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2056666012084831"><a name="p2056666012084831"></a><a name="p2056666012084831"></a><a href="iftype.md">IfType</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p583766362084831"><a name="p583766362084831"></a><a name="p583766362084831"></a>Defines the network port type, for example, the WLAN network port. </p>
</td>
</tr>
<tr id="row357450841084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1391185400084831"><a name="p1391185400084831"></a><a name="p1391185400084831"></a><a href="ifreq.md">IfReq</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1858233761084831"><a name="p1858233761084831"></a><a name="p1858233761084831"></a>Defines ioctrl data. </p>
</td>
</tr>
<tr id="row1450765283084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p513092885084831"><a name="p513092885084831"></a><a name="p513092885084831"></a><a href="netdevice.md">NetDevice</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1020344195084831"><a name="p1020344195084831"></a><a name="p1020344195084831"></a>Defines a network device, including the network interface category and name, and network port type. </p>
</td>
</tr>
<tr id="row455364831084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2135273082084831"><a name="p2135273082084831"></a><a name="p2135273082084831"></a><a href="netdeviceinterface.md">NetDeviceInterFace</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2086590577084831"><a name="p2086590577084831"></a><a name="p2086590577084831"></a>Defines interfaces that need to be implemented externally by network devices, including initializing, opening, and closing a network device. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table6216931084831"></a>
<table><thead align="left"><tr id="row1675692545084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1449331561084831"><a name="p1449331561084831"></a><a name="p1449331561084831"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p972889184084831"><a name="p972889184084831"></a><a name="p972889184084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1225343734084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p887265806084831"><a name="p887265806084831"></a><a name="p887265806084831"></a><a href="wlan.md#gae01dbae885bc8abecb82bd865515c081">MAC_ADDR_SIZE</a>   6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p451762658084831"><a name="p451762658084831"></a><a name="p451762658084831"></a>Indicates a 6-byte MAC address. </p>
</td>
</tr>
<tr id="row945945299084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2053454568084831"><a name="p2053454568084831"></a><a name="p2053454568084831"></a><a href="wlan.md#gad9c939a90358c2cb6b788af7b84821a1">NET_DEVICE_IFF_RUNNING</a>   IFF_RUNNING</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2141415563084831"><a name="p2141415563084831"></a><a name="p2141415563084831"></a>Indicates that the network port is working. </p>
</td>
</tr>
<tr id="row1904730364084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p964917439084831"><a name="p964917439084831"></a><a name="p964917439084831"></a><a href="wlan.md#ga74e41a940b9c245f2bc8eaba01d4cee2">ETHER_TYPE_RARP</a>   0x8035</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p878372610084831"><a name="p878372610084831"></a><a name="p878372610084831"></a>Indicates Reverse Address Resolution Protocol (RARP). </p>
</td>
</tr>
<tr id="row28956228084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p31589372084831"><a name="p31589372084831"></a><a name="p31589372084831"></a><a href="wlan.md#ga3bc75b7ed75e7da0abf818f0f1a769d3">ETHER_TYPE_PAE</a>   0x888e</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1492410794084831"><a name="p1492410794084831"></a><a name="p1492410794084831"></a>Indicates Port Access Entity (PAE). </p>
</td>
</tr>
<tr id="row1525372037084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1152852418084831"><a name="p1152852418084831"></a><a name="p1152852418084831"></a><a href="wlan.md#ga61a8e2c9705e0c7000235c60639f3f97">ETHER_TYPE_IP</a>   0x0800</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1600916612084831"><a name="p1600916612084831"></a><a name="p1600916612084831"></a>Indicates Internet Protocol (IP). </p>
</td>
</tr>
<tr id="row1307444161084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p123319214084831"><a name="p123319214084831"></a><a name="p123319214084831"></a><a href="wlan.md#ga4759f448b5669a1f33ff7d6912a1b131">ETHER_TYPE_AARP</a>   0x80f3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2013452277084831"><a name="p2013452277084831"></a><a name="p2013452277084831"></a>Indicates AppleTalk Address Resolution Protocol (AARP). </p>
</td>
</tr>
<tr id="row622406274084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1448416831084831"><a name="p1448416831084831"></a><a name="p1448416831084831"></a><a href="wlan.md#gaa0b348d7d0f58adb49e152c79b93b519">ETHER_TYPE_IPX</a>   0x8137</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2014617650084831"><a name="p2014617650084831"></a><a name="p2014617650084831"></a>Indicates Internetwork Packet Exchange (IPX). </p>
</td>
</tr>
<tr id="row1569182549084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1172411077084831"><a name="p1172411077084831"></a><a name="p1172411077084831"></a><a href="wlan.md#ga3f5d778e8eb1a7ad731921a460e6c1dd">ETHER_TYPE_ARP</a>   0x0806</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p862890778084831"><a name="p862890778084831"></a><a name="p862890778084831"></a>Indicates Address Resolution Protocol (ARP). </p>
</td>
</tr>
<tr id="row870307521084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1104182148084831"><a name="p1104182148084831"></a><a name="p1104182148084831"></a><a href="wlan.md#gadd8fcb263b0d4f3e9c09aafe4c6b64e0">ETHER_TYPE_IPV6</a>   0x86dd</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1583080728084831"><a name="p1583080728084831"></a><a name="p1583080728084831"></a>Indicates Internet Protocol version 6 (IPv6). </p>
</td>
</tr>
<tr id="row1835440926084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1895505196084831"><a name="p1895505196084831"></a><a name="p1895505196084831"></a><a href="wlan.md#ga0418380e708e716910958ed2aab3921d">ETHER_TYPE_TDLS</a>   0x890d</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2134205078084831"><a name="p2134205078084831"></a><a name="p2134205078084831"></a>Indicates Tunneled Direct Link Setup (TDLS). </p>
</td>
</tr>
<tr id="row455016626084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p566726009084831"><a name="p566726009084831"></a><a name="p566726009084831"></a><a href="wlan.md#gaaaa516211cec2b61e3717c5fec36952f">ETHER_TYPE_VLAN</a>   0x8100</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p980146123084831"><a name="p980146123084831"></a><a name="p980146123084831"></a>Indicates Virtual Local Area Network (VLAN). </p>
</td>
</tr>
<tr id="row1479010859084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p698683156084831"><a name="p698683156084831"></a><a name="p698683156084831"></a><a href="wlan.md#ga89fb6635bc0c9eab11de63ec141938a6">ETHER_TYPE_WAI</a>   0x88b4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1997872783084831"><a name="p1997872783084831"></a><a name="p1997872783084831"></a>Indicates WLAN Authentication and Privacy Infrastructure (WAPI). </p>
</td>
</tr>
<tr id="row2113104827084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p869244581084831"><a name="p869244581084831"></a><a name="p869244581084831"></a><a href="wlan.md#ga7da55985d58df9fac85217e1195d4b7c">ETHER_LLTD_TYPE</a>   0x88D9</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2100796392084831"><a name="p2100796392084831"></a><a name="p2100796392084831"></a>Indicates Link Layer Topology Discovery (LLTD). </p>
</td>
</tr>
<tr id="row64568967084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p315845463084831"><a name="p315845463084831"></a><a name="p315845463084831"></a><a href="wlan.md#ga0fb3b00b4300fcbd562e07d5f91aaca0">ETHER_ONE_X_TYPE</a>   0x888E</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1133687554084831"><a name="p1133687554084831"></a><a name="p1133687554084831"></a>Indicates 802.1x network port authentication. </p>
</td>
</tr>
<tr id="row501511396084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1642886163084831"><a name="p1642886163084831"></a><a name="p1642886163084831"></a><a href="wlan.md#gaefd300f6277931e053c899367ad96536">ETHER_TUNNEL_TYPE</a>   0x88bd</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1534347781084831"><a name="p1534347781084831"></a><a name="p1534347781084831"></a>Indicates a tunnel protocol. </p>
</td>
</tr>
<tr id="row845590378084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1175996213084831"><a name="p1175996213084831"></a><a name="p1175996213084831"></a><a href="wlan.md#ga70914271e18c471460d1d00cec8af522">ETHER_TYPE_PPP_DISC</a>   0x8863</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p996497952084831"><a name="p996497952084831"></a><a name="p996497952084831"></a>Indicates the point-to-point discovery type. </p>
</td>
</tr>
<tr id="row363794301084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1212150640084831"><a name="p1212150640084831"></a><a name="p1212150640084831"></a><a href="wlan.md#gaf4b193dda19de66eba7a99b64b3a0c6c">ETHER_TYPE_PPP_SES</a>   0x8864</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027564035084831"><a name="p1027564035084831"></a><a name="p1027564035084831"></a>Indicates the point-to-point session discovery type. </p>
</td>
</tr>
<tr id="row660187061084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p80466749084831"><a name="p80466749084831"></a><a name="p80466749084831"></a><a href="wlan.md#ga6fca23e8bd12854706021a45fe3cd352">ETHER_TYPE_6LO</a>   0xa0ed</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p398709657084831"><a name="p398709657084831"></a><a name="p398709657084831"></a>Indicates IPv6 over Low Power Wireless Personal Area Networks (6LoWPANs). </p>
</td>
</tr>
<tr id="row1737514102084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1122361570084831"><a name="p1122361570084831"></a><a name="p1122361570084831"></a><a href="wlan.md#ga96b31b1ec02746766191916559cec530">TCP_PROTOCAL</a>   6</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p575045316084831"><a name="p575045316084831"></a><a name="p575045316084831"></a>Indicates the Transmission Control Protocol (TCP). </p>
</td>
</tr>
<tr id="row443543642084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1177073890084831"><a name="p1177073890084831"></a><a name="p1177073890084831"></a><a href="wlan.md#ga06cdba6ef1f4bc477016c6bbae7ce444">UDP_PROTOCAL</a>   17</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1530817725084831"><a name="p1530817725084831"></a><a name="p1530817725084831"></a>Indicates the User Datagram Protocol (UDP). </p>
</td>
</tr>
<tr id="row1158703561084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2085393299084831"><a name="p2085393299084831"></a><a name="p2085393299084831"></a><a href="wlan.md#gab7ea98963ef9a6aecac843b0ea6bbcee">IP_PRI_SHIFT</a>   5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p129949498084831"><a name="p129949498084831"></a><a name="p129949498084831"></a>Indicates the shift in the priority for an IP address. </p>
</td>
</tr>
<tr id="row743706815084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2100867227084831"><a name="p2100867227084831"></a><a name="p2100867227084831"></a><a href="wlan.md#ga2db7b9e1310a372d11d568e34958e158">DHCP_UDP_SRC_PORT</a>   68</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1258818298084831"><a name="p1258818298084831"></a><a name="p1258818298084831"></a>Indicates the source port number of DHCP. </p>
</td>
</tr>
<tr id="row1457969859084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1237928909084831"><a name="p1237928909084831"></a><a name="p1237928909084831"></a><a href="wlan.md#gad92d590d45b6f76db61dd87fed7fa770">DHCP_UDP_DES_PORT</a>   67</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1563000851084831"><a name="p1563000851084831"></a><a name="p1563000851084831"></a>Indicates the destination port number of DHCP. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table914817105084831"></a>
<table><thead align="left"><tr id="row223822882084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p417557827084831"><a name="p417557827084831"></a><a name="p417557827084831"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1580596404084831"><a name="p1580596404084831"></a><a name="p1580596404084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1673879024084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p933527891084831"><a name="p933527891084831"></a><a name="p933527891084831"></a><a href="wlan.md#gac26e4b0cda623f27420f9ce77befbb1f">NetDevice</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201461494084831"><a name="p1201461494084831"></a><a name="p1201461494084831"></a>typedef struct <a href="netdevice.md">NetDevice</a> </p>
<p id="p466167875084831"><a name="p466167875084831"></a><a name="p466167875084831"></a>Defines a network device, including the network interface category and name, and network port type. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table80156147084831"></a>
<table><thead align="left"><tr id="row375795766084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p634124221084831"><a name="p634124221084831"></a><a name="p634124221084831"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p379575594084831"><a name="p379575594084831"></a><a name="p379575594084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1208875927084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1363366422084831"><a name="p1363366422084831"></a><a name="p1363366422084831"></a><a href="wlan.md#ga530241881cd17e03f8ae254ef1d9755e">NetIfCategory</a> { <a href="wlan.md#gga530241881cd17e03f8ae254ef1d9755eaab9c78d744764e8f66591ee4a8d7b3cb">LITE_OS</a>, <a href="wlan.md#gga530241881cd17e03f8ae254ef1d9755eafdfffeab76fab0306aa033c650ae0cfa">RICH_OS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p576393148084831"><a name="p576393148084831"></a><a name="p576393148084831"></a>Enumerates network interface categories, including lightweight OS and rich OS. </p>
</td>
</tr>
<tr id="row1052148618084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1272082006084831"><a name="p1272082006084831"></a><a name="p1272082006084831"></a><a href="wlan.md#ga0fb482694e5eac3f48c75de1749c8baf">NetIfStatus</a> { <a href="wlan.md#gga0fb482694e5eac3f48c75de1749c8bafaeda2ad3830d5a42070617fd0211baf95">NETIF_DOWN</a>, <a href="wlan.md#gga0fb482694e5eac3f48c75de1749c8bafa64a69f6624102c11bd658c09daf0f865">NETIF_UP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p705194482084831"><a name="p705194482084831"></a><a name="p705194482084831"></a>Enumerates network interface states, including online and offline. </p>
</td>
</tr>
<tr id="row118554039084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2131886589084831"><a name="p2131886589084831"></a><a name="p2131886589084831"></a><a href="wlan.md#ga7b1187d116fb065d7927ad9f77edd842">NetIfLinkStatus</a> { <a href="wlan.md#gga7b1187d116fb065d7927ad9f77edd842a8586d0e791ca4f7026853d85740650b5">NETIF_LINK_DOWN</a>, <a href="wlan.md#gga7b1187d116fb065d7927ad9f77edd842ac3108dbea78b5f0f928e6e5e4ea045f2">NETIF_LINK_UP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1905443299084831"><a name="p1905443299084831"></a><a name="p1905443299084831"></a>Enumerates network link layer states, including online and offline. </p>
</td>
</tr>
<tr id="row175825263084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p294619926084831"><a name="p294619926084831"></a><a name="p294619926084831"></a><a href="wlan.md#gad3175955d2e6ef3c4f52da9b509d5b4a">NetLinkType</a> { <a href="wlan.md#ggad3175955d2e6ef3c4f52da9b509d5b4aa2d49c28127ce1d558ad5ea2f92e89fd7">ETHERNET_LINK</a> = 1, <a href="wlan.md#ggad3175955d2e6ef3c4f52da9b509d5b4aadfed684cd7f64cc1aea5944657866db6">WIFI_LINK</a> = 801 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1913385941084831"><a name="p1913385941084831"></a><a name="p1913385941084831"></a>Enumerates data link types, including Ethernet and WLAN. </p>
</td>
</tr>
<tr id="row1109880685084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2127501054084831"><a name="p2127501054084831"></a><a name="p2127501054084831"></a><a href="wlan.md#ga9c1d6e7df4468671742cb76f72b67af1">ProcessingResult</a> { <a href="wlan.md#gga9c1d6e7df4468671742cb76f72b67af1a5ce4c56e88c31420a02d3b7f068e0799">PROCESSING_CONTINUE</a>, <a href="wlan.md#gga9c1d6e7df4468671742cb76f72b67af1a2fcbb133dcd739ab4a04b00bececd70a">PROCESSING_COMPLETE</a>, <a href="wlan.md#gga9c1d6e7df4468671742cb76f72b67af1afe177a1b88ea1cdcc0e41181c2c73e83">PROCESSING_ERROR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p755939994084831"><a name="p755939994084831"></a><a name="p755939994084831"></a>Enumerates data processing results, including continuing processing, processing completed, and error. </p>
</td>
</tr>
<tr id="row202093748084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969751930084831"><a name="p1969751930084831"></a><a name="p1969751930084831"></a><a href="wlan.md#ga9fb4e578a15db1b0087d7b3831591ced">NetDevTxResult</a> { <a href="wlan.md#gga9fb4e578a15db1b0087d7b3831591ceda734cacd083ffc8d233cab8d4deb6b38b">NETDEV_TX_OK</a> = 0x00, <a href="wlan.md#gga9fb4e578a15db1b0087d7b3831591cedaf0a0ac437358f6af42c3e38795c46d35">NETDEV_TX_BUSY</a> = 0x10, <a href="wlan.md#gga9fb4e578a15db1b0087d7b3831591ceda7eb70cee5761fe8954f94b660c37eaa8">NETDEV_TX_LOCKED</a> = 0x20 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1674058425084831"><a name="p1674058425084831"></a><a name="p1674058425084831"></a>Enumerates data sending results, including sending succeeded, other data being sent at the link layer, and data link layer being locked. </p>
</td>
</tr>
<tr id="row1679362089084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p618916213084831"><a name="p618916213084831"></a><a name="p618916213084831"></a><a href="wlan.md#gac69954f56fcc99fc8aac68aa157831c7">Protocol80211IfType</a> {   <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7a6b209b916aabd18f2a950a82e68b6a4c">PROTOCOL_80211_IFTYPE_UNSPECIFIED</a>, <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7a0926a98ddc2ceec4ba58ebfc01c5fe35">PROTOCOL_80211_IFTYPE_ADHOC</a>, <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7acd26f8cefbd658e9ea02feecefd054fb">PROTOCOL_80211_IFTYPE_STATION</a>, <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7a9e92654b9ab6ed6eb62868f1e0e4ea8f">PROTOCOL_80211_IFTYPE_AP</a>,   <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7a991ad1a3f8c43b06c4eeb9dc88acdb1e">PROTOCOL_80211_IFTYPE_AP_VLAN</a>, <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7aa25631c32cd6c996a7c96ba4f61299e2">PROTOCOL_80211_IFTYPE_WDS</a>, <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7a3ff1c1358af5a0c50b64e0ef0e96a970">PROTOCOL_80211_IFTYPE_MONITOR</a>, <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7a382756b8a71015cd536cdbc113c4f483">PROTOCOL_80211_IFTYPE_MESH_POINT</a>,   <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7acfd81d6e484c6f7a3b863327af112cfc">PROTOCOL_80211_IFTYPE_P2P_CLIENT</a>, <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7abca0ccb5cf4c14af9b6ff0bd9eeb4173">PROTOCOL_80211_IFTYPE_P2P_GO</a>, <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7ad63ad4a5a66892e842e4d75cc82b0755">PROTOCOL_80211_IFTYPE_P2P_DEVICE</a>, <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7a7f1fa9726ab20597baaa9ebf884b26cd">PROTOCOL_80211_IFTYPE_NUM</a>,   <a href="wlan.md#ggac69954f56fcc99fc8aac68aa157831c7a37b72ea7c4cd81dd4c427e2d721c9499">PROTOCOL_80211_IFTYPE_MAX</a> = PROTOCOL_80211_IFTYPE_NUM - 1 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1215070939084831"><a name="p1215070939084831"></a><a name="p1215070939084831"></a>Enumerates 802.11 network port types, including AP, STA, and P2P. </p>
</td>
</tr>
<tr id="row1498365362084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1582096874084831"><a name="p1582096874084831"></a><a name="p1582096874084831"></a><a href="wlan.md#ga9023c5dc1cc43758cbb468d78af41c2d">NetdeviceError</a> { <a href="wlan.md#gga9023c5dc1cc43758cbb468d78af41c2dafe771f5d0d84d17922f466d3eed83d6b">COMMON_ERROR</a> = 1, <a href="wlan.md#gga9023c5dc1cc43758cbb468d78af41c2daf5426609de8db5782b340a6bcd7e94d6">ADD_LWIP_ERROR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1234567215084831"><a name="p1234567215084831"></a><a name="p1234567215084831"></a>Enumerates network device errors, including common errors and errors in adding network devices to LwIP. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2014738522084831"></a>
<table><thead align="left"><tr id="row125304498084831"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p304499379084831"><a name="p304499379084831"></a><a name="p304499379084831"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p667861655084831"><a name="p667861655084831"></a><a name="p667861655084831"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1754055830084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1439618138084831"><a name="p1439618138084831"></a><a name="p1439618138084831"></a><a href="wlan.md#ga8d2bff6673ec21ba317d596a84df7ca8">NetDeviceInit</a> (const char *ifName, uint32_t len, <a href="wlan.md#ga530241881cd17e03f8ae254ef1d9755e">NetIfCategory</a> ifCategory)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p330455777084831"><a name="p330455777084831"></a><a name="p330455777084831"></a>struct <a href="netdevice.md">NetDevice</a> * </p>
<p id="p1383715927084831"><a name="p1383715927084831"></a><a name="p1383715927084831"></a>Initializes a network device to obtain its instance. </p>
</td>
</tr>
<tr id="row656274430084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2133567005084831"><a name="p2133567005084831"></a><a name="p2133567005084831"></a><a href="wlan.md#gaf4a2fa8b1a35d4cadd8247ee8fed60a4">NetDeviceDeInit</a> (struct <a href="netdevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1085685939084831"><a name="p1085685939084831"></a><a name="p1085685939084831"></a>int32_t </p>
<p id="p848609101084831"><a name="p848609101084831"></a><a name="p848609101084831"></a>Deletes a network device. </p>
</td>
</tr>
<tr id="row1724601842084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2070453816084831"><a name="p2070453816084831"></a><a name="p2070453816084831"></a><a href="wlan.md#ga64be10f09b180d3098e9550163131dbd">NetDeviceAdd</a> (struct <a href="netdevice.md">NetDevice</a> *netDevice, <a href="wlan.md#gac69954f56fcc99fc8aac68aa157831c7">Protocol80211IfType</a> ifType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1556203232084831"><a name="p1556203232084831"></a><a name="p1556203232084831"></a>int32_t </p>
<p id="p1696866509084831"><a name="p1696866509084831"></a><a name="p1696866509084831"></a>Adds a network device to a protocol stack. </p>
</td>
</tr>
<tr id="row827809666084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p185901019084831"><a name="p185901019084831"></a><a name="p185901019084831"></a><a href="wlan.md#ga6c93cb701cf2523eaa7bbeabd4acf3ab">NetDeviceDelete</a> (struct <a href="netdevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p31047133084831"><a name="p31047133084831"></a><a name="p31047133084831"></a>int32_t </p>
<p id="p1768256730084831"><a name="p1768256730084831"></a><a name="p1768256730084831"></a>Deletes a network device from a protocol stack. </p>
</td>
</tr>
<tr id="row792438277084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1479167468084831"><a name="p1479167468084831"></a><a name="p1479167468084831"></a><a href="wlan.md#ga6d90d1bf783a83db1d838d03f8c1d93a">NetDeviceGetInstByName</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053349835084831"><a name="p2053349835084831"></a><a name="p2053349835084831"></a>struct <a href="netdevice.md">NetDevice</a> * </p>
<p id="p1612751913084831"><a name="p1612751913084831"></a><a name="p1612751913084831"></a>Obtains the initialized network device instance by a specified device name. </p>
</td>
</tr>
<tr id="row841848234084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2029888435084831"><a name="p2029888435084831"></a><a name="p2029888435084831"></a><a href="wlan.md#ga20fcbcc248e99917c17223a97fe5d70e">NetDeviceIsAnyInstRunning</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p996053934084831"><a name="p996053934084831"></a><a name="p996053934084831"></a>bool </p>
<p id="p1828105461084831"><a name="p1828105461084831"></a><a name="p1828105461084831"></a>Checks whether there are working devices among the added network devices. </p>
</td>
</tr>
<tr id="row1423040048084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419177766084831"><a name="p419177766084831"></a><a name="p419177766084831"></a><a href="wlan.md#ga05b08c890c69f3e633447f14e16d30f7">NetDeviceIsInstRunning</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1030785971084831"><a name="p1030785971084831"></a><a name="p1030785971084831"></a>bool </p>
<p id="p277072880084831"><a name="p277072880084831"></a><a name="p277072880084831"></a>Checks whether a specified network device is working. </p>
</td>
</tr>
<tr id="row1916750249084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1133898841084831"><a name="p1133898841084831"></a><a name="p1133898841084831"></a><a href="wlan.md#ga8c8d400a6b4eb64445a2b4ea12102c9a">NetDevGetRegisterCount</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2146097243084831"><a name="p2146097243084831"></a><a name="p2146097243084831"></a>uint32_t </p>
<p id="p381684600084831"><a name="p381684600084831"></a><a name="p381684600084831"></a>Obtains the number of added network devices. </p>
</td>
</tr>
<tr id="row24026244084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p144026981084831"><a name="p144026981084831"></a><a name="p144026981084831"></a><a href="wlan.md#ga5d2a4fd370e2115b4c1fc8ecc46d64ab">NetDeviceGetCap</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p111614147084831"><a name="p111614147084831"></a><a name="p111614147084831"></a>uint32_t </p>
<p id="p1385961377084831"><a name="p1385961377084831"></a><a name="p1385961377084831"></a>Obtains the maximum number of network devices that can be registered with this system at the same time. </p>
</td>
</tr>
<tr id="row410998543084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p681419226084831"><a name="p681419226084831"></a><a name="p681419226084831"></a><a href="wlan.md#gab45261476e710c30335975726af3a834">NetDeviceGetInstByIndex</a> (uint32_t <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2045535962084831"><a name="p2045535962084831"></a><a name="p2045535962084831"></a>struct <a href="netdevice.md">NetDevice</a> * </p>
<p id="p1959220030084831"><a name="p1959220030084831"></a><a name="p1959220030084831"></a>Obtains a network device instance based on the index number. </p>
</td>
</tr>
<tr id="row158663943084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2115065460084831"><a name="p2115065460084831"></a><a name="p2115065460084831"></a><a href="wlan.md#gadd5c08aa8e65a12db062b1b88d53cece">NetIfSetAddr</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice, const <a href="ipv4addr.md">IpV4Addr</a> *ipAddr, const <a href="ipv4addr.md">IpV4Addr</a> *netMask, const <a href="ipv4addr.md">IpV4Addr</a> *gw)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p930117611084831"><a name="p930117611084831"></a><a name="p930117611084831"></a>int32_t </p>
<p id="p1693453382084831"><a name="p1693453382084831"></a><a name="p1693453382084831"></a>Sets an IP address, mask, and gateway. </p>
</td>
</tr>
<tr id="row545223544084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p957897398084831"><a name="p957897398084831"></a><a name="p957897398084831"></a><a href="wlan.md#gaa14fc68a382284491a272992d5c477cb">NetIfSetStatus</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice, <a href="wlan.md#ga0fb482694e5eac3f48c75de1749c8baf">NetIfStatus</a> status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773203116084831"><a name="p773203116084831"></a><a name="p773203116084831"></a>int32_t </p>
<p id="p1929398537084831"><a name="p1929398537084831"></a><a name="p1929398537084831"></a>Notifies the network layer of the network port state. </p>
</td>
</tr>
<tr id="row902751042084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p32600452084831"><a name="p32600452084831"></a><a name="p32600452084831"></a><a href="wlan.md#gaee9c68875ef541ed915045ab7a047ee8">NetIfSetLinkStatus</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice, <a href="wlan.md#ga7b1187d116fb065d7927ad9f77edd842">NetIfLinkStatus</a> status)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1448262692084831"><a name="p1448262692084831"></a><a name="p1448262692084831"></a>int32_t </p>
<p id="p1102047405084831"><a name="p1102047405084831"></a><a name="p1102047405084831"></a>Notifies the network layer of the data link layer status. </p>
</td>
</tr>
<tr id="row1923948946084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1133611011084831"><a name="p1133611011084831"></a><a name="p1133611011084831"></a><a href="wlan.md#ga44006f6e066aff9f6a3310559e781582">NetIfRx</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice, struct <a href="netbuf.md">NetBuf</a> *buff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p439015060084831"><a name="p439015060084831"></a><a name="p439015060084831"></a>int32_t </p>
<p id="p414369842084831"><a name="p414369842084831"></a><a name="p414369842084831"></a>Transfers the input data packets from the network side to a protocol stack. </p>
</td>
</tr>
<tr id="row1587183979084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1152854620084831"><a name="p1152854620084831"></a><a name="p1152854620084831"></a><a href="wlan.md#gad252107cdd20e9d3d0ab33fbfc2161e9">NetIfRxNi</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice, struct <a href="netbuf.md">NetBuf</a> *buff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1774840337084831"><a name="p1774840337084831"></a><a name="p1774840337084831"></a>int32_t </p>
<p id="p981123850084831"><a name="p981123850084831"></a><a name="p981123850084831"></a>Transfers data packets from the network side to a protocol stack in an interrupt processing thread. </p>
</td>
</tr>
<tr id="row296868980084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1032139885084831"><a name="p1032139885084831"></a><a name="p1032139885084831"></a><a href="wlan.md#gae97c7abcf556be34798622a85162c35e">NetIfDhcpsStart</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice, char *ip, u16_t ipNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p242785819084831"><a name="p242785819084831"></a><a name="p242785819084831"></a>int32_t </p>
<p id="p1008900914084831"><a name="p1008900914084831"></a><a name="p1008900914084831"></a>Starts the DHCP server. </p>
</td>
</tr>
<tr id="row713763730084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1622803093084831"><a name="p1622803093084831"></a><a name="p1622803093084831"></a><a href="wlan.md#gaadfeb819b4cb623870823fa5c9793b4c">NetIfDhcpsStop</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p453355441084831"><a name="p453355441084831"></a><a name="p453355441084831"></a>int32_t </p>
<p id="p445509498084831"><a name="p445509498084831"></a><a name="p445509498084831"></a>Stops the DHCP server. </p>
</td>
</tr>
<tr id="row655887487084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1881048020084831"><a name="p1881048020084831"></a><a name="p1881048020084831"></a><a href="wlan.md#ga5fdd93c820b994adf1b76eb8d50e4f88">NetIfDhcpStart</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2072605003084831"><a name="p2072605003084831"></a><a name="p2072605003084831"></a>int32_t </p>
<p id="p1176747306084831"><a name="p1176747306084831"></a><a name="p1176747306084831"></a>Starts the DHCP client of a specified network device. </p>
</td>
</tr>
<tr id="row495622478084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p669411665084831"><a name="p669411665084831"></a><a name="p669411665084831"></a><a href="wlan.md#ga22f97a3fc45841e874ab2072c14e0f3e">NetIfDhcpStop</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p248510165084831"><a name="p248510165084831"></a><a name="p248510165084831"></a>int32_t </p>
<p id="p955359968084831"><a name="p955359968084831"></a><a name="p955359968084831"></a>Stops the DHCP client of a specified network device. </p>
</td>
</tr>
<tr id="row2042436844084831"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p318297667084831"><a name="p318297667084831"></a><a name="p318297667084831"></a><a href="wlan.md#ga389ec95a3c8170c4ca74487f8bc1d8ac">NetIfDhcpIsBound</a> (const struct <a href="netdevice.md">NetDevice</a> *netDevice)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699369078084831"><a name="p1699369078084831"></a><a name="p1699369078084831"></a>int32_t </p>
<p id="p1994639577084831"><a name="p1994639577084831"></a><a name="p1994639577084831"></a>Obtains the DHCP negotiation status of a specified network device. </p>
</td>
</tr>
</tbody>
</table>

