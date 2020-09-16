# IpHeader<a name="EN-US_TOPIC_0000001055518094"></a>

## **Overview**<a name="section1973559391093531"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Defines the IP header information of a data frame, including the version number, service type, and total length. 

**Since:**

1.0

## **Summary**<a name="section1562540729093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1348591861093531"></a>
<table><thead align="left"><tr id="row1749390429093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p531585113093531"><a name="p531585113093531"></a><a name="p531585113093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1892422270093531"><a name="p1892422270093531"></a><a name="p1892422270093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1301313745093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864638331093531"><a name="p1864638331093531"></a><a name="p1864638331093531"></a><a href="wlan.md#gae31602cb3fb4f012749e6d44e73bd5bf">versionAndHl</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1480194271093531"><a name="p1480194271093531"></a><a name="p1480194271093531"></a>uint8_t </p>
</td>
</tr>
<tr id="row1398876083093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p476888228093531"><a name="p476888228093531"></a><a name="p476888228093531"></a><a href="wlan.md#ga324f15b4a41342c026ce3ad253ed9498">tos</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1438156934093531"><a name="p1438156934093531"></a><a name="p1438156934093531"></a>uint8_t </p>
</td>
</tr>
<tr id="row949233940093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1100499377093531"><a name="p1100499377093531"></a><a name="p1100499377093531"></a><a href="wlan.md#ga35aa269c5b304d238c65aedaa28e3da5">totLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1398129848093531"><a name="p1398129848093531"></a><a name="p1398129848093531"></a>uint16_t </p>
</td>
</tr>
<tr id="row1614726821093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1395160200093531"><a name="p1395160200093531"></a><a name="p1395160200093531"></a><a href="wlan.md#ga2d5c09b859bc0faddc8a42339973bdd4">id</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1586572862093531"><a name="p1586572862093531"></a><a name="p1586572862093531"></a>uint16_t </p>
</td>
</tr>
<tr id="row662797867093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1390654661093531"><a name="p1390654661093531"></a><a name="p1390654661093531"></a><a href="wlan.md#gaf329df46f50a5dcf4dd87c103317401b">fragInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p531157061093531"><a name="p531157061093531"></a><a name="p531157061093531"></a>uint16_t </p>
</td>
</tr>
<tr id="row1364695059093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1214135146093531"><a name="p1214135146093531"></a><a name="p1214135146093531"></a><a href="wlan.md#gad380e64b2d33d75ce04d65126b54fb8f">ttl</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2028029418093531"><a name="p2028029418093531"></a><a name="p2028029418093531"></a>uint8_t </p>
</td>
</tr>
<tr id="row1103657333093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521918308093531"><a name="p521918308093531"></a><a name="p521918308093531"></a><a href="wlan.md#ga029ab0914b5854efe279e442aec3b423">protocol</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1767281549093531"><a name="p1767281549093531"></a><a name="p1767281549093531"></a>uint8_t </p>
</td>
</tr>
<tr id="row1706151770093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p781177568093531"><a name="p781177568093531"></a><a name="p781177568093531"></a><a href="wlan.md#gaf3b4d16f68ab697df71ca8589f00397c">check</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p574151019093531"><a name="p574151019093531"></a><a name="p574151019093531"></a>uint16_t </p>
</td>
</tr>
<tr id="row1333430711093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1502042162093531"><a name="p1502042162093531"></a><a name="p1502042162093531"></a><a href="wlan.md#ga22e36dfd118fbe9deee40135f87a0568">sAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1155422291093531"><a name="p1155422291093531"></a><a name="p1155422291093531"></a>uint32_t </p>
</td>
</tr>
<tr id="row1060992690093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1887911479093531"><a name="p1887911479093531"></a><a name="p1887911479093531"></a><a href="wlan.md#ga5124eb108341354708e52775df8899ef">dAddr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p788350029093531"><a name="p788350029093531"></a><a name="p788350029093531"></a>uint32_t </p>
</td>
</tr>
</tbody>
</table>

