# OHOS::VirtualDeviceEvent<a name="EN-US_TOPIC_0000001054918185"></a>

## **Overview**<a name="section1616182232084840"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a virtual device event, which is used to receive a customized input event and call back the listening function registered. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2079140351084840"></a>

## Public Types<a name="pub-types"></a>

<a name="table1126849122084840"></a>
<table><thead align="left"><tr id="row953530346084840"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p791751788084840"><a name="p791751788084840"></a><a name="p791751788084840"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1932969178084840"><a name="p1932969178084840"></a><a name="p1932969178084840"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1008424851084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p988485967084840"><a name="p988485967084840"></a><a name="p988485967084840"></a><a href="graphic.md#gaf8133740d5a3cb2f88a7f33cb11c6dbd">DeviceType</a> </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p854223737084840"><a name="p854223737084840"></a><a name="p854223737084840"></a>Enumerates virtual device types. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1841569448084840"></a>
<table><thead align="left"><tr id="row782273273084840"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p561680202084840"><a name="p561680202084840"></a><a name="p561680202084840"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p651783151084840"><a name="p651783151084840"></a><a name="p651783151084840"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row348516415084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1337026935084840"><a name="p1337026935084840"></a><a name="p1337026935084840"></a><a href="graphic.md#ga4832bd35eeae9c4402c1cba6294fe55b">VirtualDeviceEvent</a> (uint16_t type, uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1456624695084840"><a name="p1456624695084840"></a><a name="p1456624695084840"></a> </p>
<p id="p766393218084840"><a name="p766393218084840"></a><a name="p766393218084840"></a>A constructor used to create a <strong id="b953477828084840"><a name="b953477828084840"></a><a name="b953477828084840"></a><a href="ohos-virtualdeviceevent.md">VirtualDeviceEvent</a></strong> instance. </p>
</td>
</tr>
<tr id="row403714590084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p920723384084840"><a name="p920723384084840"></a><a name="p920723384084840"></a><a href="graphic.md#ga72e6afde17a0376e756b463e04a86ba1">~VirtualDeviceEvent</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1220383522084840"><a name="p1220383522084840"></a><a name="p1220383522084840"></a> </p>
<p id="p1300411681084840"><a name="p1300411681084840"></a><a name="p1300411681084840"></a>A destructor used to delete the <strong id="b1887484223084840"><a name="b1887484223084840"></a><a name="b1887484223084840"></a><a href="ohos-virtualdeviceevent.md">VirtualDeviceEvent</a></strong> instance. </p>
</td>
</tr>
<tr id="row1918483634084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p911336535084840"><a name="p911336535084840"></a><a name="p911336535084840"></a><a href="graphic.md#ga47a12f474dd7351a303e4959a05b17d1">GetType</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481535097084840"><a name="p1481535097084840"></a><a name="p1481535097084840"></a>uint16_t </p>
<p id="p1192646521084840"><a name="p1192646521084840"></a><a name="p1192646521084840"></a>Obtains the type of the virtual device. </p>
</td>
</tr>
<tr id="row1559249482084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2086906040084840"><a name="p2086906040084840"></a><a name="p2086906040084840"></a><a href="graphic.md#gae0619e7f8b3c97548f763f281bdd8261">GetState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p296115128084840"><a name="p296115128084840"></a><a name="p296115128084840"></a>uint16_t </p>
<p id="p1838260400084840"><a name="p1838260400084840"></a><a name="p1838260400084840"></a>Obtains the state of the virtual event. </p>
</td>
</tr>
<tr id="row378529871084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1162867859084840"><a name="p1162867859084840"></a><a name="p1162867859084840"></a><a href="graphic.md#ga89cd09ced5537a3479b7901ba8abc6da">Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p861783917084840"><a name="p861783917084840"></a><a name="p861783917084840"></a> </p>
<p id="p1195371703084840"><a name="p1195371703084840"></a><a name="p1195371703084840"></a>A default constructor used to create an <strong id="b1141056034084840"><a name="b1141056034084840"></a><a name="b1141056034084840"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row619073542084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205828040084840"><a name="p205828040084840"></a><a name="p205828040084840"></a><a href="graphic.md#ga57a9f07c8203c6a60f3b25c4edb526a0">Event</a> (const <a href="ohos-point.md">Point</a> &amp;curPos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1474594939084840"><a name="p1474594939084840"></a><a name="p1474594939084840"></a> </p>
<p id="p433016960084840"><a name="p433016960084840"></a><a name="p433016960084840"></a>A constructor used to create an <strong id="b1991197008084840"><a name="b1991197008084840"></a><a name="b1991197008084840"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1835104256084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1315842802084840"><a name="p1315842802084840"></a><a name="p1315842802084840"></a><a href="graphic.md#gabafa07a6393f4757f402bf9437561fa4">~Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1735849891084840"><a name="p1735849891084840"></a><a name="p1735849891084840"></a>virtual </p>
<p id="p392283955084840"><a name="p392283955084840"></a><a name="p392283955084840"></a>A destructor used to delete the <strong id="b518867198084840"><a name="b518867198084840"></a><a name="b518867198084840"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1413176362084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1167360435084840"><a name="p1167360435084840"></a><a name="p1167360435084840"></a><a href="graphic.md#gaea811c661ad416d7f70912ad6fcce269">GetCurrentPos</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1959551284084840"><a name="p1959551284084840"></a><a name="p1959551284084840"></a>const <a href="ohos-point.md">Point</a> &amp; </p>
<p id="p1272958720084840"><a name="p1272958720084840"></a><a name="p1272958720084840"></a>Obtains the position where an event occurs. </p>
</td>
</tr>
<tr id="row2104736164084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1184690440084840"><a name="p1184690440084840"></a><a name="p1184690440084840"></a><a href="graphic.md#ga7d56c2a99ab2c98eec9ebc03f67b7777">GetTimeStamp</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p457558242084840"><a name="p457558242084840"></a><a name="p457558242084840"></a>const TimeType &amp; </p>
<p id="p1011236340084840"><a name="p1011236340084840"></a><a name="p1011236340084840"></a>Obtains the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row113972936084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p221188719084840"><a name="p221188719084840"></a><a name="p221188719084840"></a><a href="graphic.md#gabee47ba229e81c44f648cf5b3203010f">SetTimeStamp</a> (const TimeType &amp;timeStamp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p963596114084840"><a name="p963596114084840"></a><a name="p963596114084840"></a>void </p>
<p id="p1310456576084840"><a name="p1310456576084840"></a><a name="p1310456576084840"></a>Sets the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row838220006084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217096293084840"><a name="p1217096293084840"></a><a name="p1217096293084840"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2030772652084840"><a name="p2030772652084840"></a><a name="p2030772652084840"></a>void * </p>
<p id="p1438114483084840"><a name="p1438114483084840"></a><a name="p1438114483084840"></a>Overrides the <strong id="b1532299214084840"><a name="b1532299214084840"></a><a name="b1532299214084840"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row642412093084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p745214365084840"><a name="p745214365084840"></a><a name="p745214365084840"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p777008008084840"><a name="p777008008084840"></a><a name="p777008008084840"></a>void </p>
<p id="p1534959275084840"><a name="p1534959275084840"></a><a name="p1534959275084840"></a>Overrides the <strong id="b2111410949084840"><a name="b2111410949084840"></a><a name="b2111410949084840"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

