# ISessionListener<a name="ZH-CN_TOPIC_0000001054715059"></a>

## **Overview**<a name="section1768895681191859"></a>

**Related Modules:**

[Softbus](Softbus.md)

**Description:**

Defines session callbacks. 

When a session is opened or closed, or there is data to process, the related callback is invoked.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2016306633191859"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table965988094191859"></a>
<table><thead align="left"><tr id="row645153363191859"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1448110963191859"><a name="p1448110963191859"></a><a name="p1448110963191859"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1031093945191859"><a name="p1031093945191859"></a><a name="p1031093945191859"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2041463740191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1537997215191859"><a name="p1537997215191859"></a><a name="p1537997215191859"></a><a href="Softbus.md#ga2b042b85e03d66f1988c348414b2db6e">onSessionOpened</a> )(int sessionId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p557900749191859"><a name="p557900749191859"></a><a name="p557900749191859"></a>int(*&nbsp;</p>
<p id="p517155758191859"><a name="p517155758191859"></a><a name="p517155758191859"></a>Called when a session is opened. </p>
</td>
</tr>
<tr id="row4016908191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1649602230191859"><a name="p1649602230191859"></a><a name="p1649602230191859"></a><a href="Softbus.md#ga2088a4e0e196030d8e428a828298eba0">onSessionClosed</a> )(int sessionId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1751716194191859"><a name="p1751716194191859"></a><a name="p1751716194191859"></a>void(*&nbsp;</p>
<p id="p341307002191859"><a name="p341307002191859"></a><a name="p341307002191859"></a>Called when a session is closed. </p>
</td>
</tr>
<tr id="row500010611191859"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p985068536191859"><a name="p985068536191859"></a><a name="p985068536191859"></a><a href="Softbus.md#ga95243f25fa04ef29f7f8f0b3a440dbd3">onBytesReceived</a> )(int sessionId, const void *data, unsigned int dataLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1948110511191859"><a name="p1948110511191859"></a><a name="p1948110511191859"></a>void(*&nbsp;</p>
<p id="p1947871887191859"><a name="p1947871887191859"></a><a name="p1947871887191859"></a>Called when data is received. </p>
</td>
</tr>
</tbody>
</table>

