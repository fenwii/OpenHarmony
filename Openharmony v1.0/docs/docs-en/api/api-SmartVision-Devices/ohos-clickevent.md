# OHOS::ClickEvent<a name="EN-US_TOPIC_0000001055039546"></a>

## **Overview**<a name="section209185582093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a click event, which indicates that a finger is pressed on the screen and then lifted within 1 second. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2028268663093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table967760315093535"></a>
<table><thead align="left"><tr id="row1852691230093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2002058091093535"><a name="p2002058091093535"></a><a name="p2002058091093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p584505750093535"><a name="p584505750093535"></a><a name="p584505750093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1547848705093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1970339258093535"><a name="p1970339258093535"></a><a name="p1970339258093535"></a><a href="graphic.md#gaeb51d39715cc72b383ba6059bd0d1053">ClickEvent</a> (const <a href="ohos-point.md">Point</a> &amp;pos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p400383980093535"><a name="p400383980093535"></a><a name="p400383980093535"></a> </p>
<p id="p834647793093535"><a name="p834647793093535"></a><a name="p834647793093535"></a>A constructor used to create a <strong id="b1274758574093535"><a name="b1274758574093535"></a><a name="b1274758574093535"></a><a href="ohos-clickevent.md">ClickEvent</a></strong> instance. </p>
</td>
</tr>
<tr id="row2091962811093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p286965403093535"><a name="p286965403093535"></a><a name="p286965403093535"></a><a href="graphic.md#ga75b3bef18631b1640c31dd1191f35ef7">~ClickEvent</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p489917982093535"><a name="p489917982093535"></a><a name="p489917982093535"></a>virtual </p>
<p id="p246776431093535"><a name="p246776431093535"></a><a name="p246776431093535"></a>A destructor used to delete the <strong id="b557290045093535"><a name="b557290045093535"></a><a name="b557290045093535"></a><a href="ohos-clickevent.md">ClickEvent</a></strong> instance. </p>
</td>
</tr>
<tr id="row1549723034093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1557159117093535"><a name="p1557159117093535"></a><a name="p1557159117093535"></a><a href="graphic.md#ga89cd09ced5537a3479b7901ba8abc6da">Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1518133722093535"><a name="p1518133722093535"></a><a name="p1518133722093535"></a> </p>
<p id="p142255690093535"><a name="p142255690093535"></a><a name="p142255690093535"></a>A default constructor used to create an <strong id="b949311993093535"><a name="b949311993093535"></a><a name="b949311993093535"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1199639784093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p927754665093535"><a name="p927754665093535"></a><a name="p927754665093535"></a><a href="graphic.md#ga57a9f07c8203c6a60f3b25c4edb526a0">Event</a> (const <a href="ohos-point.md">Point</a> &amp;curPos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2036842937093535"><a name="p2036842937093535"></a><a name="p2036842937093535"></a> </p>
<p id="p980749672093535"><a name="p980749672093535"></a><a name="p980749672093535"></a>A constructor used to create an <strong id="b583957786093535"><a name="b583957786093535"></a><a name="b583957786093535"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row102988873093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1988029500093535"><a name="p1988029500093535"></a><a name="p1988029500093535"></a><a href="graphic.md#gabafa07a6393f4757f402bf9437561fa4">~Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p87613247093535"><a name="p87613247093535"></a><a name="p87613247093535"></a>virtual </p>
<p id="p41740171093535"><a name="p41740171093535"></a><a name="p41740171093535"></a>A destructor used to delete the <strong id="b1542200166093535"><a name="b1542200166093535"></a><a name="b1542200166093535"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1425587997093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p504068851093535"><a name="p504068851093535"></a><a name="p504068851093535"></a><a href="graphic.md#gaea811c661ad416d7f70912ad6fcce269">GetCurrentPos</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1795795034093535"><a name="p1795795034093535"></a><a name="p1795795034093535"></a>const <a href="ohos-point.md">Point</a> &amp; </p>
<p id="p1935628502093535"><a name="p1935628502093535"></a><a name="p1935628502093535"></a>Obtains the position where an event occurs. </p>
</td>
</tr>
<tr id="row413164189093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1230426372093535"><a name="p1230426372093535"></a><a name="p1230426372093535"></a><a href="graphic.md#ga7d56c2a99ab2c98eec9ebc03f67b7777">GetTimeStamp</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1475936952093535"><a name="p1475936952093535"></a><a name="p1475936952093535"></a>const TimeType &amp; </p>
<p id="p1373430970093535"><a name="p1373430970093535"></a><a name="p1373430970093535"></a>Obtains the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row1372480794093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1460073066093535"><a name="p1460073066093535"></a><a name="p1460073066093535"></a><a href="graphic.md#gabee47ba229e81c44f648cf5b3203010f">SetTimeStamp</a> (const TimeType &amp;timeStamp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1895502216093535"><a name="p1895502216093535"></a><a name="p1895502216093535"></a>void </p>
<p id="p2116504860093535"><a name="p2116504860093535"></a><a name="p2116504860093535"></a>Sets the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row564390039093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1791545181093535"><a name="p1791545181093535"></a><a name="p1791545181093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635604955093535"><a name="p635604955093535"></a><a name="p635604955093535"></a>void * </p>
<p id="p983718745093535"><a name="p983718745093535"></a><a name="p983718745093535"></a>Overrides the <strong id="b974095152093535"><a name="b974095152093535"></a><a name="b974095152093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1126825282093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p273850518093535"><a name="p273850518093535"></a><a name="p273850518093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p382525125093535"><a name="p382525125093535"></a><a name="p382525125093535"></a>void </p>
<p id="p1103392101093535"><a name="p1103392101093535"></a><a name="p1103392101093535"></a>Overrides the <strong id="b1933508063093535"><a name="b1933508063093535"></a><a name="b1933508063093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

