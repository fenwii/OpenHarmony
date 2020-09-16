# TcpHeader<a name="EN-US_TOPIC_0000001054598201"></a>

## **Overview**<a name="section1953793543093537"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Defines the TCP header information of a data frame, including the source port number and destination port number. 

**Since:**

1.0

## **Summary**<a name="section1390061163093537"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table889283212093537"></a>
<table><thead align="left"><tr id="row1624938558093537"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1668033172093537"><a name="p1668033172093537"></a><a name="p1668033172093537"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1436719569093537"><a name="p1436719569093537"></a><a name="p1436719569093537"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row411908500093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1336223475093537"><a name="p1336223475093537"></a><a name="p1336223475093537"></a><a href="wlan.md#gae29f9cbe74e4e7f7543e74bb8d039f15">sPort</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751662242093537"><a name="p751662242093537"></a><a name="p751662242093537"></a>uint16_t </p>
</td>
</tr>
<tr id="row1529484477093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p481373652093537"><a name="p481373652093537"></a><a name="p481373652093537"></a><a href="wlan.md#ga2a188a6b8ee0eccceefe0e17818e8707">dPort</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p522825947093537"><a name="p522825947093537"></a><a name="p522825947093537"></a>uint16_t </p>
</td>
</tr>
<tr id="row934575775093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1889621468093537"><a name="p1889621468093537"></a><a name="p1889621468093537"></a><a href="wlan.md#ga5409de9f82a50bf5113dafb316118d4b">seqNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1227539707093537"><a name="p1227539707093537"></a><a name="p1227539707093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row2073948091093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p752865183093537"><a name="p752865183093537"></a><a name="p752865183093537"></a><a href="wlan.md#ga223c54c5ebb2d92ed5f6c50115663b86">ackNum</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p599916193093537"><a name="p599916193093537"></a><a name="p599916193093537"></a>uint32_t </p>
</td>
</tr>
<tr id="row293846498093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1341713610093537"><a name="p1341713610093537"></a><a name="p1341713610093537"></a><a href="wlan.md#gabac9ba66ff160d881083b1f173f411f9">offset</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2112596228093537"><a name="p2112596228093537"></a><a name="p2112596228093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row2005950826093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1322870382093537"><a name="p1322870382093537"></a><a name="p1322870382093537"></a><a href="wlan.md#ga66be1d87b4d2576cee91cd3867b93701">flags</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1476317072093537"><a name="p1476317072093537"></a><a name="p1476317072093537"></a>uint8_t </p>
</td>
</tr>
<tr id="row1582308199093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p620034059093537"><a name="p620034059093537"></a><a name="p620034059093537"></a><a href="wlan.md#ga55cc45eeabc0f857e51e8864ae45de8e">window</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p745572751093537"><a name="p745572751093537"></a><a name="p745572751093537"></a>uint16_t </p>
</td>
</tr>
<tr id="row1599707411093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616621483093537"><a name="p1616621483093537"></a><a name="p1616621483093537"></a><a href="wlan.md#gab32c75fd1d8d8985d9861157907a3a74">check</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1744869083093537"><a name="p1744869083093537"></a><a name="p1744869083093537"></a>uint16_t </p>
</td>
</tr>
<tr id="row1878049471093537"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p215430300093537"><a name="p215430300093537"></a><a name="p215430300093537"></a><a href="wlan.md#ga0c402826ed93d697342d8b1108db7754">urgent</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1603251521093537"><a name="p1603251521093537"></a><a name="p1603251521093537"></a>uint16_t </p>
</td>
</tr>
</tbody>
</table>

