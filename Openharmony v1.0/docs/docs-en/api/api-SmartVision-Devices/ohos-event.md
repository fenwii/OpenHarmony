# OHOS::Event<a name="EN-US_TOPIC_0000001054879562"></a>

## **Overview**<a name="section1273014811093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the base class of a user input event and provides functions to record information such as the event position and timestamp. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1067192687093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1471386360093535"></a>
<table><thead align="left"><tr id="row2098138764093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p983972744093535"><a name="p983972744093535"></a><a name="p983972744093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1553202871093535"><a name="p1553202871093535"></a><a name="p1553202871093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row577897064093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p559135359093535"><a name="p559135359093535"></a><a name="p559135359093535"></a><a href="graphic.md#ga89cd09ced5537a3479b7901ba8abc6da">Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985361878093535"><a name="p985361878093535"></a><a name="p985361878093535"></a> </p>
<p id="p762561373093535"><a name="p762561373093535"></a><a name="p762561373093535"></a>A default constructor used to create an <strong id="b1753463483093535"><a name="b1753463483093535"></a><a name="b1753463483093535"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1764690445093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p136112921093535"><a name="p136112921093535"></a><a name="p136112921093535"></a><a href="graphic.md#ga57a9f07c8203c6a60f3b25c4edb526a0">Event</a> (const <a href="ohos-point.md">Point</a> &amp;curPos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p161214686093535"><a name="p161214686093535"></a><a name="p161214686093535"></a> </p>
<p id="p1400677985093535"><a name="p1400677985093535"></a><a name="p1400677985093535"></a>A constructor used to create an <strong id="b86986364093535"><a name="b86986364093535"></a><a name="b86986364093535"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row2107965358093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p82833828093535"><a name="p82833828093535"></a><a name="p82833828093535"></a><a href="graphic.md#gabafa07a6393f4757f402bf9437561fa4">~Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1678001567093535"><a name="p1678001567093535"></a><a name="p1678001567093535"></a>virtual </p>
<p id="p471204810093535"><a name="p471204810093535"></a><a name="p471204810093535"></a>A destructor used to delete the <strong id="b824280656093535"><a name="b824280656093535"></a><a name="b824280656093535"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1125707739093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1295253290093535"><a name="p1295253290093535"></a><a name="p1295253290093535"></a><a href="graphic.md#gaea811c661ad416d7f70912ad6fcce269">GetCurrentPos</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p556984152093535"><a name="p556984152093535"></a><a name="p556984152093535"></a>const <a href="ohos-point.md">Point</a> &amp; </p>
<p id="p637848333093535"><a name="p637848333093535"></a><a name="p637848333093535"></a>Obtains the position where an event occurs. </p>
</td>
</tr>
<tr id="row1183412265093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1888990149093535"><a name="p1888990149093535"></a><a name="p1888990149093535"></a><a href="graphic.md#ga7d56c2a99ab2c98eec9ebc03f67b7777">GetTimeStamp</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1478411978093535"><a name="p1478411978093535"></a><a name="p1478411978093535"></a>const TimeType &amp; </p>
<p id="p1052380122093535"><a name="p1052380122093535"></a><a name="p1052380122093535"></a>Obtains the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row1952160932093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864630949093535"><a name="p1864630949093535"></a><a name="p1864630949093535"></a><a href="graphic.md#gabee47ba229e81c44f648cf5b3203010f">SetTimeStamp</a> (const TimeType &amp;timeStamp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p683099646093535"><a name="p683099646093535"></a><a name="p683099646093535"></a>void </p>
<p id="p30971494093535"><a name="p30971494093535"></a><a name="p30971494093535"></a>Sets the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row584452564093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1732112914093535"><a name="p1732112914093535"></a><a name="p1732112914093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p74416735093535"><a name="p74416735093535"></a><a name="p74416735093535"></a>void * </p>
<p id="p402811373093535"><a name="p402811373093535"></a><a name="p402811373093535"></a>Overrides the <strong id="b174661821093535"><a name="b174661821093535"></a><a name="b174661821093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row498390982093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183377881093535"><a name="p1183377881093535"></a><a name="p1183377881093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p182708633093535"><a name="p182708633093535"></a><a name="p182708633093535"></a>void </p>
<p id="p2034777362093535"><a name="p2034777362093535"></a><a name="p2034777362093535"></a>Overrides the <strong id="b1195381002093535"><a name="b1195381002093535"></a><a name="b1195381002093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

