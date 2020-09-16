# osal\_time.h<a name="ZH-CN_TOPIC_0000001055358084"></a>

## **Overview**<a name="section1414599671093526"></a>

**Related Modules:**

[OSAL](OSAL.md)

**Description:**

Declares the time, sleep, and delay interfaces. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section900019222093526"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1325204773093526"></a>
<table><thead align="left"><tr id="row1889305855093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1012210875093526"><a name="p1012210875093526"></a><a name="p1012210875093526"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1851182630093526"><a name="p1851182630093526"></a><a name="p1851182630093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row282091822093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p663667285093526"><a name="p663667285093526"></a><a name="p663667285093526"></a><a href="OsalTimespec.md">OsalTimespec</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1356358089093526"><a name="p1356358089093526"></a><a name="p1356358089093526"></a>Defines time. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1822396517093526"></a>
<table><thead align="left"><tr id="row1244645178093526"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1785668891093526"><a name="p1785668891093526"></a><a name="p1785668891093526"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1050083787093526"><a name="p1050083787093526"></a><a name="p1050083787093526"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row155921378093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1069554440093526"><a name="p1069554440093526"></a><a name="p1069554440093526"></a><a href="OSAL.md#ga8b9ca3498c54b11dcbe88a2a456f23ab">OsalSleep</a> (uint32_t sec)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964260803093526"><a name="p964260803093526"></a><a name="p964260803093526"></a>void&nbsp;</p>
<p id="p1611070177093526"><a name="p1611070177093526"></a><a name="p1611070177093526"></a>Describes thread sleep, in seconds. </p>
</td>
</tr>
<tr id="row978104402093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p903527797093526"><a name="p903527797093526"></a><a name="p903527797093526"></a><a href="OSAL.md#ga2361dc099952df28aaef8968f9f4b9a7">OsalMSleep</a> (uint32_t ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1448395725093526"><a name="p1448395725093526"></a><a name="p1448395725093526"></a>void&nbsp;</p>
<p id="p227632697093526"><a name="p227632697093526"></a><a name="p227632697093526"></a>Describes thread sleep, in milliseconds. </p>
</td>
</tr>
<tr id="row1156365743093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p520432837093526"><a name="p520432837093526"></a><a name="p520432837093526"></a><a href="OSAL.md#ga649d3090dcf9ba0e22649e11ac40831f">OsalGetTime</a> (<a href="OsalTimespec.md">OsalTimespec</a> *<a href="zh-cn_topic_0000001054879478.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p880090624093526"><a name="p880090624093526"></a><a name="p880090624093526"></a>int32_t&nbsp;</p>
<p id="p1609451701093526"><a name="p1609451701093526"></a><a name="p1609451701093526"></a>Obtains the second and microsecond time. </p>
</td>
</tr>
<tr id="row498418299093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1883649064093526"><a name="p1883649064093526"></a><a name="p1883649064093526"></a><a href="OSAL.md#ga36b0af6646f887175993e78391a5cabc">OsalDiffTime</a> (const <a href="OsalTimespec.md">OsalTimespec</a> *start, const <a href="OsalTimespec.md">OsalTimespec</a> *end, <a href="OsalTimespec.md">OsalTimespec</a> *diff)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p499209031093526"><a name="p499209031093526"></a><a name="p499209031093526"></a>int32_t&nbsp;</p>
<p id="p1700687746093526"><a name="p1700687746093526"></a><a name="p1700687746093526"></a>Obtains time difference. </p>
</td>
</tr>
<tr id="row483219257093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1700476304093526"><a name="p1700476304093526"></a><a name="p1700476304093526"></a><a href="OSAL.md#gaf91cb1945b66e324fbb0761aa2f98ea3">OsalGetSysTimeMs</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135911673093526"><a name="p135911673093526"></a><a name="p135911673093526"></a>uint64_t&nbsp;</p>
<p id="p1034104151093526"><a name="p1034104151093526"></a><a name="p1034104151093526"></a>Obtains the system time. </p>
</td>
</tr>
<tr id="row1712557313093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1647750465093526"><a name="p1647750465093526"></a><a name="p1647750465093526"></a><a href="OSAL.md#ga82ddd682a2441a22dd6148f634a6cea4">OsalMDelay</a> (uint32_t ms)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1947045170093526"><a name="p1947045170093526"></a><a name="p1947045170093526"></a>void&nbsp;</p>
<p id="p687404405093526"><a name="p687404405093526"></a><a name="p687404405093526"></a>Describes thread delay, in milliseconds. </p>
</td>
</tr>
<tr id="row1235845876093526"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1812616935093526"><a name="p1812616935093526"></a><a name="p1812616935093526"></a><a href="OSAL.md#ga7ae78fa3318a82dbd769827d4f373958">OsalUDelay</a> (uint32_t us)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2103223833093526"><a name="p2103223833093526"></a><a name="p2103223833093526"></a>void&nbsp;</p>
<p id="p1530316008093526"><a name="p1530316008093526"></a><a name="p1530316008093526"></a>Describes thread delay, in microseconds. </p>
</td>
</tr>
</tbody>
</table>

