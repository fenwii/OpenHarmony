# NetBuf<a name="ZH-CN_TOPIC_0000001054718135"></a>

## **Overview**<a name="section1625678102084837"></a>

**Related Modules:**

[WLAN](WLAN.md)

**Description:**

Records and saves a network data buffer. 

This structure is used to transmit network data between the protocol stack and network driver.

**Since:**

1.0

## **Summary**<a name="section1501513872084837"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table893636836084837"></a>
<table><thead align="left"><tr id="row1730876917084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p412854279084837"><a name="p412854279084837"></a><a name="p412854279084837"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p264462825084837"><a name="p264462825084837"></a><a name="p264462825084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row753435950084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p462584040084837"><a name="p462584040084837"></a><a name="p462584040084837"></a><a href="WLAN.md#ga6de94d9c8f9dd8d608a091673fa130c4">dlist</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p458038691084837"><a name="p458038691084837"></a><a name="p458038691084837"></a>struct <a href="DListHead.md">DListHead</a>&nbsp;</p>
</td>
</tr>
<tr id="row1369323341084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1190451992084837"><a name="p1190451992084837"></a><a name="p1190451992084837"></a><a href="WLAN.md#ga49eacbbc8b4231a05464768103b8593f">bufs</a> [<a href="WLAN.md#ggae4d5251432e1a9e6803c0240cc492e18aeef2a730ef9f722cfbac0b24998f8e19">MAX_BUF_NUM</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p876423257084837"><a name="p876423257084837"></a><a name="p876423257084837"></a>struct BufField&nbsp;</p>
</td>
</tr>
<tr id="row839081105084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1905768701084837"><a name="p1905768701084837"></a><a name="p1905768701084837"></a><a href="WLAN.md#gad94b7aff082f5d891a3250dfc6307ce0">mem</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p151329760084837"><a name="p151329760084837"></a><a name="p151329760084837"></a>uint8_t *&nbsp;</p>
</td>
</tr>
<tr id="row1483300346084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1947854909084837"><a name="p1947854909084837"></a><a name="p1947854909084837"></a><a href="WLAN.md#ga559e952054ce59e81d2ff9b38634b60c">len</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p177941754084837"><a name="p177941754084837"></a><a name="p177941754084837"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row939619998084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422786321084837"><a name="p422786321084837"></a><a name="p422786321084837"></a><a href="WLAN.md#gafb7e6f774a44888f5c44c3dffc6c5616">dataLen</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p38646158084837"><a name="p38646158084837"></a><a name="p38646158084837"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row13353888084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505685275084837"><a name="p1505685275084837"></a><a name="p1505685275084837"></a><a href="WLAN.md#gafa78f2abfa4f977cfb3bd52a6ae05d61">dev</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2067444866084837"><a name="p2067444866084837"></a><a name="p2067444866084837"></a>void *&nbsp;</p>
</td>
</tr>
<tr id="row1706919839084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p207642815084837"><a name="p207642815084837"></a><a name="p207642815084837"></a><a href="WLAN.md#gaa56eababaaaeda2ec724f21889a20ccd">qmap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1578893084837"><a name="p1578893084837"></a><a name="p1578893084837"></a>uint32_t&nbsp;</p>
</td>
</tr>
<tr id="row1309627539084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p383483768084837"><a name="p383483768084837"></a><a name="p383483768084837"></a><a href="WLAN.md#ga197b5045451ca25a03f478df0bd03514">rsv</a> [<a href="WLAN.md#ga794c035a19a38acc000146a8f9a4ec80">MAX_NETBUF_RESEVER_SIZE</a>]</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1184788907084837"><a name="p1184788907084837"></a><a name="p1184788907084837"></a>uint8_t&nbsp;</p>
</td>
</tr>
</tbody>
</table>

