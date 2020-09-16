# ISessionListener<a name="ZH-CN_TOPIC_0000001054598163"></a>

## **Overview**<a name="section1684544519093531"></a>

**Related Modules:**

[Softbus](Softbus.md)

**Description:**

Defines session callbacks. 

When a session is opened or closed, or there is data to process, the related callback is invoked.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1159791738093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1626347623093531"></a>
<table><thead align="left"><tr id="row580634333093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p828802155093531"><a name="p828802155093531"></a><a name="p828802155093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p321331105093531"><a name="p321331105093531"></a><a name="p321331105093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1717021391093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1732784737093531"><a name="p1732784737093531"></a><a name="p1732784737093531"></a><a href="Softbus.md#ga2b042b85e03d66f1988c348414b2db6e">onSessionOpened</a> )(int sessionId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929368451093531"><a name="p929368451093531"></a><a name="p929368451093531"></a>int(*&nbsp;</p>
<p id="p1708269778093531"><a name="p1708269778093531"></a><a name="p1708269778093531"></a>Called when a session is opened. </p>
</td>
</tr>
<tr id="row566645183093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p872048186093531"><a name="p872048186093531"></a><a name="p872048186093531"></a><a href="Softbus.md#ga2088a4e0e196030d8e428a828298eba0">onSessionClosed</a> )(int sessionId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1626325700093531"><a name="p1626325700093531"></a><a name="p1626325700093531"></a>void(*&nbsp;</p>
<p id="p869580546093531"><a name="p869580546093531"></a><a name="p869580546093531"></a>Called when a session is closed. </p>
</td>
</tr>
<tr id="row464002999093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2038293822093531"><a name="p2038293822093531"></a><a name="p2038293822093531"></a><a href="Softbus.md#ga95243f25fa04ef29f7f8f0b3a440dbd3">onBytesReceived</a> )(int sessionId, const void *data, unsigned int dataLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1878327538093531"><a name="p1878327538093531"></a><a name="p1878327538093531"></a>void(*&nbsp;</p>
<p id="p2114840071093531"><a name="p2114840071093531"></a><a name="p2114840071093531"></a>Called when data is received. </p>
</td>
</tr>
</tbody>
</table>

