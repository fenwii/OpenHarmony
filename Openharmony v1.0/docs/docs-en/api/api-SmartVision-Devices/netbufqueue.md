# NetBufQueue<a name="EN-US_TOPIC_0000001055678102"></a>

## **Overview**<a name="section1390295686093531"></a>

**Related Modules:**

[WLAN](wlan.md)

**Description:**

Indicates the queues for storing network data. 

Queues can be used to process multiple pieces of network data in a centralized manner, improving efficiency.

**Since:**

1.0

## **Summary**<a name="section1563970888093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1029951979093531"></a>
<table><thead align="left"><tr id="row1986311241093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p670637717093531"><a name="p670637717093531"></a><a name="p670637717093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1240699581093531"><a name="p1240699581093531"></a><a name="p1240699581093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1556470365093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p642640044093531"><a name="p642640044093531"></a><a name="p642640044093531"></a><a href="wlan.md#ga473ab87a57006bb6ed69c5e5ea666f5c">dlist</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p896195784093531"><a name="p896195784093531"></a><a name="p896195784093531"></a>struct <a href="dlisthead.md">DListHead</a> </p>
</td>
</tr>
<tr id="row1493664677093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1311984947093531"><a name="p1311984947093531"></a><a name="p1311984947093531"></a><a href="wlan.md#gab8e922b274e1854731b5fd22d8dde62d">size</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1539938498093531"><a name="p1539938498093531"></a><a name="p1539938498093531"></a>uint32_t </p>
</td>
</tr>
<tr id="row1140511310093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1663325398093531"><a name="p1663325398093531"></a><a name="p1663325398093531"></a><a href="wlan.md#gadd22ee64f7d9703d6c4cde54b512aaa0">lock</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1470297484093531"><a name="p1470297484093531"></a><a name="p1470297484093531"></a>struct Spinlock </p>
</td>
</tr>
</tbody>
</table>

