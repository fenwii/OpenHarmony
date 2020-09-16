# OHOS::DragEvent<a name="EN-US_TOPIC_0000001054479593"></a>

## **Overview**<a name="section375988796093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a drag event, which indicates a certain movement \(more than 10 pixels\) after a view is pressed. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section374973940093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1514512270093535"></a>
<table><thead align="left"><tr id="row1749356511093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1791354777093535"><a name="p1791354777093535"></a><a name="p1791354777093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1118526305093535"><a name="p1118526305093535"></a><a name="p1118526305093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row420118413093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p979562917093535"><a name="p979562917093535"></a><a name="p979562917093535"></a><a href="graphic.md#gae9af79f667fc1324739d2a07fdd5d94e">DragEvent</a> (const <a href="ohos-point.md">Point</a> &amp;newPos, const <a href="ohos-point.md">Point</a> &amp;lastPos, const <a href="ohos-point.md">Point</a> &amp;totalLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p472832500093535"><a name="p472832500093535"></a><a name="p472832500093535"></a> </p>
<p id="p1110172948093535"><a name="p1110172948093535"></a><a name="p1110172948093535"></a>A constructor used to create a <strong id="b634868178093535"><a name="b634868178093535"></a><a name="b634868178093535"></a><a href="ohos-dragevent.md">DragEvent</a></strong> instance. </p>
</td>
</tr>
<tr id="row2060032513093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p358336541093535"><a name="p358336541093535"></a><a name="p358336541093535"></a><a href="graphic.md#gabed19ea6c1b15b861653485349133468">~DragEvent</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763444014093535"><a name="p763444014093535"></a><a name="p763444014093535"></a>virtual </p>
<p id="p11648280093535"><a name="p11648280093535"></a><a name="p11648280093535"></a>A destructor used to delete the <strong id="b1692772126093535"><a name="b1692772126093535"></a><a name="b1692772126093535"></a><a href="ohos-dragevent.md">DragEvent</a></strong> instance. </p>
</td>
</tr>
<tr id="row703305271093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p97536297093535"><a name="p97536297093535"></a><a name="p97536297093535"></a><a href="graphic.md#ga2b5a66f36249b23e69cccfc2859847c1">GetLastPoint</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p103989620093535"><a name="p103989620093535"></a><a name="p103989620093535"></a>const <a href="ohos-point.md">Point</a> &amp; </p>
<p id="p920257711093535"><a name="p920257711093535"></a><a name="p920257711093535"></a>Obtains the coordinates of the last position in the drag event. </p>
</td>
</tr>
<tr id="row1599633837093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1900763694093535"><a name="p1900763694093535"></a><a name="p1900763694093535"></a><a href="graphic.md#gadeada49639b81e405b8b54e2629361ee">GetStartPoint</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1630901005093535"><a name="p1630901005093535"></a><a name="p1630901005093535"></a>const <a href="ohos-point.md">Point</a> &amp; </p>
<p id="p507052005093535"><a name="p507052005093535"></a><a name="p507052005093535"></a>Obtains the start coordinates in the drag event. </p>
</td>
</tr>
<tr id="row728213705093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p993314566093535"><a name="p993314566093535"></a><a name="p993314566093535"></a><a href="graphic.md#ga8399680c67bc048745257a1b56250834">SetPreLastPoint</a> (const <a href="ohos-point.md">Point</a> &amp;preLastPos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p319866975093535"><a name="p319866975093535"></a><a name="p319866975093535"></a>void </p>
<p id="p1159771053093535"><a name="p1159771053093535"></a><a name="p1159771053093535"></a>Sets the coordinates of the stay position before the last position in the drag event. </p>
</td>
</tr>
<tr id="row1559667377093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2102779832093535"><a name="p2102779832093535"></a><a name="p2102779832093535"></a><a href="graphic.md#ga7a7198c95326af4ad0d2e2a85fb99ef6">GetPreLastPoint</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p590482368093535"><a name="p590482368093535"></a><a name="p590482368093535"></a>const <a href="ohos-point.md">Point</a> &amp; </p>
<p id="p1448883756093535"><a name="p1448883756093535"></a><a name="p1448883756093535"></a>Obtains the coordinates of the stay position before the last position in the drag event. </p>
</td>
</tr>
<tr id="row599354748093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p240305858093535"><a name="p240305858093535"></a><a name="p240305858093535"></a><a href="graphic.md#gaf0ab47609e2dc46109f889847d9d7f9d">GetDragDirection</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p525103650093535"><a name="p525103650093535"></a><a name="p525103650093535"></a>uint8_t </p>
<p id="p1457964967093535"><a name="p1457964967093535"></a><a name="p1457964967093535"></a>Obtains the direction in the drag event. </p>
</td>
</tr>
<tr id="row1845488858093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755301367093535"><a name="p1755301367093535"></a><a name="p1755301367093535"></a><a href="graphic.md#ga4e504ef2c5ef58bb0c79bbfdb0168d0d">GetDeltaX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1430399560093535"><a name="p1430399560093535"></a><a name="p1430399560093535"></a>int16_t </p>
<p id="p172114056093535"><a name="p172114056093535"></a><a name="p172114056093535"></a>Obtains the difference between the current position and the last position of the view in the x-axis. </p>
</td>
</tr>
<tr id="row191109740093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p420430065093535"><a name="p420430065093535"></a><a name="p420430065093535"></a><a href="graphic.md#ga13e3996546917d71612b34285f8b9dd7">GetDeltaY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p889648627093535"><a name="p889648627093535"></a><a name="p889648627093535"></a>int16_t </p>
<p id="p1797700697093535"><a name="p1797700697093535"></a><a name="p1797700697093535"></a>Obtains the difference between the current position and the last position of the view in the y-axis. </p>
</td>
</tr>
<tr id="row1724128163093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p428300760093535"><a name="p428300760093535"></a><a name="p428300760093535"></a><a href="graphic.md#ga89cd09ced5537a3479b7901ba8abc6da">Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908651811093535"><a name="p908651811093535"></a><a name="p908651811093535"></a> </p>
<p id="p1882226633093535"><a name="p1882226633093535"></a><a name="p1882226633093535"></a>A default constructor used to create an <strong id="b1947269154093535"><a name="b1947269154093535"></a><a name="b1947269154093535"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row122274591093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p463944550093535"><a name="p463944550093535"></a><a name="p463944550093535"></a><a href="graphic.md#ga57a9f07c8203c6a60f3b25c4edb526a0">Event</a> (const <a href="ohos-point.md">Point</a> &amp;curPos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1410213984093535"><a name="p1410213984093535"></a><a name="p1410213984093535"></a> </p>
<p id="p1609553664093535"><a name="p1609553664093535"></a><a name="p1609553664093535"></a>A constructor used to create an <strong id="b1869607969093535"><a name="b1869607969093535"></a><a name="b1869607969093535"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1351168419093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1174105924093535"><a name="p1174105924093535"></a><a name="p1174105924093535"></a><a href="graphic.md#gabafa07a6393f4757f402bf9437561fa4">~Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1883693774093535"><a name="p1883693774093535"></a><a name="p1883693774093535"></a>virtual </p>
<p id="p1812392750093535"><a name="p1812392750093535"></a><a name="p1812392750093535"></a>A destructor used to delete the <strong id="b1619180217093535"><a name="b1619180217093535"></a><a name="b1619180217093535"></a><a href="ohos-event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row475153781093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1630548778093535"><a name="p1630548778093535"></a><a name="p1630548778093535"></a><a href="graphic.md#gaea811c661ad416d7f70912ad6fcce269">GetCurrentPos</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032244522093535"><a name="p1032244522093535"></a><a name="p1032244522093535"></a>const <a href="ohos-point.md">Point</a> &amp; </p>
<p id="p242100536093535"><a name="p242100536093535"></a><a name="p242100536093535"></a>Obtains the position where an event occurs. </p>
</td>
</tr>
<tr id="row9636156093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p70110628093535"><a name="p70110628093535"></a><a name="p70110628093535"></a><a href="graphic.md#ga7d56c2a99ab2c98eec9ebc03f67b7777">GetTimeStamp</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1364767409093535"><a name="p1364767409093535"></a><a name="p1364767409093535"></a>const TimeType &amp; </p>
<p id="p2015892218093535"><a name="p2015892218093535"></a><a name="p2015892218093535"></a>Obtains the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row1543475498093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p11359895093535"><a name="p11359895093535"></a><a name="p11359895093535"></a><a href="graphic.md#gabee47ba229e81c44f648cf5b3203010f">SetTimeStamp</a> (const TimeType &amp;timeStamp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1839883773093535"><a name="p1839883773093535"></a><a name="p1839883773093535"></a>void </p>
<p id="p366250085093535"><a name="p366250085093535"></a><a name="p366250085093535"></a>Sets the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row19153108093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1628612281093535"><a name="p1628612281093535"></a><a name="p1628612281093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p909969992093535"><a name="p909969992093535"></a><a name="p909969992093535"></a>void * </p>
<p id="p531446792093535"><a name="p531446792093535"></a><a name="p531446792093535"></a>Overrides the <strong id="b441674610093535"><a name="b441674610093535"></a><a name="b441674610093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row66974360093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p214435319093535"><a name="p214435319093535"></a><a name="p214435319093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1143726140093535"><a name="p1143726140093535"></a><a name="p1143726140093535"></a>void </p>
<p id="p235781896093535"><a name="p235781896093535"></a><a name="p235781896093535"></a>Overrides the <strong id="b1681245128093535"><a name="b1681245128093535"></a><a name="b1681245128093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

