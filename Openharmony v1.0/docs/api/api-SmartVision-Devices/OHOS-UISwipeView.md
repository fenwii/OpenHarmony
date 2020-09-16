# OHOS::UISwipeView<a name="ZH-CN_TOPIC_0000001055518116"></a>

## **Overview**<a name="section1139955523084840"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents a swipe view. 

Each swipe view consists of multiple child views, which can be navigated through swiping. The child views can be either horizontal or vertical.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section625360098084840"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1631960820084840"></a>
<table><thead align="left"><tr id="row918921990084840"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1363229173084840"><a name="p1363229173084840"></a><a name="p1363229173084840"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1454798019084840"><a name="p1454798019084840"></a><a name="p1454798019084840"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row667882031084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1339879590084840"><a name="p1339879590084840"></a><a name="p1339879590084840"></a><a href="OHOS-UISwipeView-OnSwipeListener.md">OnSwipeListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1373422513084840"><a name="p1373422513084840"></a><a name="p1373422513084840"></a>Represents a listener for changes of the swipe view. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1328212515084840"></a>
<table><thead align="left"><tr id="row433149365084840"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p174944690084840"><a name="p174944690084840"></a><a name="p174944690084840"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1794489219084840"><a name="p1794489219084840"></a><a name="p1794489219084840"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1685042549084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p224897249084840"><a name="p224897249084840"></a><a name="p224897249084840"></a><a href="Graphic.md#ga3a460525251fde8e30c35be808151509">UISwipeView</a> (uint8_t direction=<a href="Graphic.md#ga34dfbde0fad8baade31c02d9e8dd5026">HORIZONTAL</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1541774993084840"><a name="p1541774993084840"></a><a name="p1541774993084840"></a>&nbsp;</p>
<p id="p339793257084840"><a name="p339793257084840"></a><a name="p339793257084840"></a>A constructor used to create a <strong id="b560915816084840"><a name="b560915816084840"></a><a name="b560915816084840"></a><a href="OHOS-UISwipeView.md">UISwipeView</a></strong> instance. </p>
</td>
</tr>
<tr id="row2029531725084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p566412623084840"><a name="p566412623084840"></a><a name="p566412623084840"></a><a href="Graphic.md#gaf51c21b72dcbe790c3bb7b83b53b3cef">~UISwipeView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1091281364084840"><a name="p1091281364084840"></a><a name="p1091281364084840"></a>virtual&nbsp;</p>
<p id="p740952012084840"><a name="p740952012084840"></a><a name="p740952012084840"></a>A destructor used to delete the <strong id="b2095370542084840"><a name="b2095370542084840"></a><a name="b2095370542084840"></a><a href="OHOS-UISwipeView.md">UISwipeView</a></strong> instance. </p>
</td>
</tr>
<tr id="row730556862084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p348312770084840"><a name="p348312770084840"></a><a name="p348312770084840"></a><a href="Graphic.md#ga71ae0dd892d8d9b8d277ba2b5572182d">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p58879449084840"><a name="p58879449084840"></a><a name="p58879449084840"></a>UIViewType&nbsp;</p>
<p id="p697336152084840"><a name="p697336152084840"></a><a name="p697336152084840"></a>Obtains the component type. </p>
</td>
</tr>
<tr id="row1935620642084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984255482084840"><a name="p984255482084840"></a><a name="p984255482084840"></a><a href="Graphic.md#ga29be43640abe185baef5ead904a729cb">SetDirection</a> (uint8_t direction)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1587763393084840"><a name="p1587763393084840"></a><a name="p1587763393084840"></a>void&nbsp;</p>
<p id="p622777629084840"><a name="p622777629084840"></a><a name="p622777629084840"></a>Sets the dragging direction. </p>
</td>
</tr>
<tr id="row57085218084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1365283940084840"><a name="p1365283940084840"></a><a name="p1365283940084840"></a><a href="Graphic.md#gad84dab74af54c23e6e724bdebb8b7df9">GetDirection</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1431680618084840"><a name="p1431680618084840"></a><a name="p1431680618084840"></a>uint8_t&nbsp;</p>
<p id="p1100714249084840"><a name="p1100714249084840"></a><a name="p1100714249084840"></a>Obtains the dragging direction. </p>
</td>
</tr>
<tr id="row1851325596084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1984973352084840"><a name="p1984973352084840"></a><a name="p1984973352084840"></a><a href="Graphic.md#ga1cdc37a33412d6134ed7214300bc1c87">Add</a> (<a href="OHOS-UIView.md">UIView</a> *view) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1306480390084840"><a name="p1306480390084840"></a><a name="p1306480390084840"></a>void&nbsp;</p>
<p id="p1714251051084840"><a name="p1714251051084840"></a><a name="p1714251051084840"></a>Adds a view. </p>
</td>
</tr>
<tr id="row658808568084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p52336502084840"><a name="p52336502084840"></a><a name="p52336502084840"></a><a href="Graphic.md#ga154efaf952ba1db65e53efdd29f0027b">Insert</a> (<a href="OHOS-UIView.md">UIView</a> *prevView, <a href="OHOS-UIView.md">UIView</a> *insertView) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p401340246084840"><a name="p401340246084840"></a><a name="p401340246084840"></a>void&nbsp;</p>
<p id="p1489466429084840"><a name="p1489466429084840"></a><a name="p1489466429084840"></a>Inserts a view. </p>
</td>
</tr>
<tr id="row876086937084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1099029727084840"><a name="p1099029727084840"></a><a name="p1099029727084840"></a><a href="Graphic.md#ga2a4f70938a7d2298a318dff6dff95e85">Remove</a> (<a href="OHOS-UIView.md">UIView</a> *view) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p855580475084840"><a name="p855580475084840"></a><a name="p855580475084840"></a>virtual void&nbsp;</p>
<p id="p1274252143084840"><a name="p1274252143084840"></a><a name="p1274252143084840"></a>Deletes a view. </p>
</td>
</tr>
<tr id="row124787025084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1342890729084840"><a name="p1342890729084840"></a><a name="p1342890729084840"></a><a href="Graphic.md#gaedb8649e42a712463158f42eb66efc33">SetCurrentPage</a> (uint16_t <a href="UTILS.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, bool needAnimator=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1836310504084840"><a name="p1836310504084840"></a><a name="p1836310504084840"></a>void&nbsp;</p>
<p id="p449059563084840"><a name="p449059563084840"></a><a name="p449059563084840"></a>Sets the index for the current tab. </p>
</td>
</tr>
<tr id="row1815880069084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p33841401084840"><a name="p33841401084840"></a><a name="p33841401084840"></a><a href="Graphic.md#gaea0c52e94714dff049117227a1fd1849">GetCurrentPage</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p868814303084840"><a name="p868814303084840"></a><a name="p868814303084840"></a>uint16_t&nbsp;</p>
<p id="p379972058084840"><a name="p379972058084840"></a><a name="p379972058084840"></a>Obtains the current tab index. </p>
</td>
</tr>
<tr id="row1380010112084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1069487778084840"><a name="p1069487778084840"></a><a name="p1069487778084840"></a><a href="Graphic.md#ga9b91ece1e4492afd3e4705e49bc511f3">GetCurrentView</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p168711257084840"><a name="p168711257084840"></a><a name="p168711257084840"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1825326428084840"><a name="p1825326428084840"></a><a name="p1825326428084840"></a>Obtains the current view. </p>
</td>
</tr>
<tr id="row178287315084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1396649209084840"><a name="p1396649209084840"></a><a name="p1396649209084840"></a><a href="Graphic.md#ga834d61387b0243cd0505f6d03d32a8f8">SetBlankSize</a> (uint16_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1496869906084840"><a name="p1496869906084840"></a><a name="p1496869906084840"></a>void&nbsp;</p>
<p id="p429995981084840"><a name="p429995981084840"></a><a name="p429995981084840"></a>Sets a blank size, as defined in <a href="Graphic.md#ga81883a607d2cb3356560fc0f8f84cf74">DEFAULT_BLANK_SIZE</a>. </p>
</td>
</tr>
<tr id="row1538067643084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969158741084840"><a name="p1969158741084840"></a><a name="p1969158741084840"></a><a href="Graphic.md#ga888ec9a6ddaa4051e7c2e5d76832565c">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1259124329084840"><a name="p1259124329084840"></a><a name="p1259124329084840"></a>bool&nbsp;</p>
<p id="p1004223695084840"><a name="p1004223695084840"></a><a name="p1004223695084840"></a>revice drag event, Switch to specified view when drag </p>
</td>
</tr>
<tr id="row1624575911084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p681714182084840"><a name="p681714182084840"></a><a name="p681714182084840"></a><a href="Graphic.md#gab57d973cea1186dd90eec91cd27da1fb">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1044197727084840"><a name="p1044197727084840"></a><a name="p1044197727084840"></a>bool&nbsp;</p>
<p id="p242413201084840"><a name="p242413201084840"></a><a name="p242413201084840"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row920218529084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2100452094084840"><a name="p2100452094084840"></a><a name="p2100452094084840"></a><a href="Graphic.md#gadb01e8e5702625c3a99f383eb7ae1664">SetAnimatorTime</a> (uint16_t <a href="TIME.md#gae7841e681c8c9d59818568d39553642c">time</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1153825662084840"><a name="p1153825662084840"></a><a name="p1153825662084840"></a>void&nbsp;</p>
<p id="p1914764154084840"><a name="p1914764154084840"></a><a name="p1914764154084840"></a>Sets the time for the page being animated. The page will go beyond the blank during this time. </p>
</td>
</tr>
<tr id="row1566849282084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p240754674084840"><a name="p240754674084840"></a><a name="p240754674084840"></a><a href="Graphic.md#ga7f7dce8193817e29c9b82af47934d788">SetLoopState</a> (bool loop)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1774679273084840"><a name="p1774679273084840"></a><a name="p1774679273084840"></a>void&nbsp;</p>
<p id="p705941696084840"><a name="p705941696084840"></a><a name="p705941696084840"></a>Sets whether the swipe view supports a cycle swipe. </p>
</td>
</tr>
<tr id="row63227581084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p905026032084840"><a name="p905026032084840"></a><a name="p905026032084840"></a><a href="Graphic.md#ga3c58441c4b07cf575b96b85df5e3a3bf">GetViewByIndex</a> (uint16_t <a href="UTILS.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1211366584084840"><a name="p1211366584084840"></a><a name="p1211366584084840"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1925001713084840"><a name="p1925001713084840"></a><a name="p1925001713084840"></a>Obtains a view based on its index. </p>
</td>
</tr>
<tr id="row715946671084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1912890522084840"><a name="p1912890522084840"></a><a name="p1912890522084840"></a><a href="Graphic.md#ga4c33414b3a828d1750deed3cceb86daf">GetOnSwipeListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p878932424084840"><a name="p878932424084840"></a><a name="p878932424084840"></a><a href="OHOS-UISwipeView-OnSwipeListener.md">OnSwipeListener</a> *&amp;&nbsp;</p>
<p id="p1875435554084840"><a name="p1875435554084840"></a><a name="p1875435554084840"></a>Obtains the listener set for swipe events. </p>
</td>
</tr>
<tr id="row1448720866084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p526035051084840"><a name="p526035051084840"></a><a name="p526035051084840"></a><a href="Graphic.md#ga7d4a3dc25f189ab19eaef4a62cd0428e">SetOnSwipeListener</a> (<a href="OHOS-UISwipeView-OnSwipeListener.md">OnSwipeListener</a> *onSwipeListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514804060084840"><a name="p514804060084840"></a><a name="p514804060084840"></a>void&nbsp;</p>
<p id="p354678199084840"><a name="p354678199084840"></a><a name="p354678199084840"></a>Sets the listener that contains a callback to be invoked upon a swipe event. </p>
</td>
</tr>
<tr id="row1636241595084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p187721839084840"><a name="p187721839084840"></a><a name="p187721839084840"></a><a href="Graphic.md#ga93a169fba7c98f6534692cba9e8d539b">UIAbstractScroll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1086780868084840"><a name="p1086780868084840"></a><a name="p1086780868084840"></a>&nbsp;</p>
<p id="p183527122084840"><a name="p183527122084840"></a><a name="p183527122084840"></a>A constructor used to create a <strong id="b1783963826084840"><a name="b1783963826084840"></a><a name="b1783963826084840"></a><a href="OHOS-UIAbstractScroll.md">UIAbstractScroll</a></strong> instance. </p>
</td>
</tr>
<tr id="row1710180609084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p355971341084840"><a name="p355971341084840"></a><a name="p355971341084840"></a><a href="Graphic.md#ga414798ec7357edc85409128fba0a813c">~UIAbstractScroll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1962589673084840"><a name="p1962589673084840"></a><a name="p1962589673084840"></a>virtual&nbsp;</p>
<p id="p729606867084840"><a name="p729606867084840"></a><a name="p729606867084840"></a>A destructor used to delete the <strong id="b2074569438084840"><a name="b2074569438084840"></a><a name="b2074569438084840"></a><a href="OHOS-UIAbstractScroll.md">UIAbstractScroll</a></strong> instance. </p>
</td>
</tr>
<tr id="row1054730675084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1081388371084840"><a name="p1081388371084840"></a><a name="p1081388371084840"></a><a href="Graphic.md#ga443783170697bea9a933843ad2a92283">GetDirection</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p489208253084840"><a name="p489208253084840"></a><a name="p489208253084840"></a>uint8_t&nbsp;</p>
<p id="p442985492084840"><a name="p442985492084840"></a><a name="p442985492084840"></a>Obtains the scroll direction. </p>
</td>
</tr>
<tr id="row582499238084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1627920940084840"><a name="p1627920940084840"></a><a name="p1627920940084840"></a><a href="Graphic.md#gab37cea97d63ee9ca609c9a1ed0f1e281">SetScrollBlankSize</a> (uint16_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p786045183084840"><a name="p786045183084840"></a><a name="p786045183084840"></a>void&nbsp;</p>
<p id="p634646417084840"><a name="p634646417084840"></a><a name="p634646417084840"></a>Sets the blank size for this scroll view. </p>
</td>
</tr>
<tr id="row165793199084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p290227351084840"><a name="p290227351084840"></a><a name="p290227351084840"></a><a href="Graphic.md#gae2d6f5c97a316ecd3b41fecfa35a351f">SetMaxScrollDistance</a> (uint16_t distance)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1099002664084840"><a name="p1099002664084840"></a><a name="p1099002664084840"></a>void&nbsp;</p>
<p id="p614528645084840"><a name="p614528645084840"></a><a name="p614528645084840"></a>Sets the maximum scroll distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1873976070084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1138380984084840"><a name="p1138380984084840"></a><a name="p1138380984084840"></a><a href="Graphic.md#ga5d7fefcd2057e868a8f6c6a6000aa7ef">SetReboundSize</a> (uint16_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p530448007084840"><a name="p530448007084840"></a><a name="p530448007084840"></a>void&nbsp;</p>
<p id="p646585017084840"><a name="p646585017084840"></a><a name="p646585017084840"></a>Sets the rebound size, which is the distance a knob moves after being released when it reaches the end of a scrollbar. </p>
</td>
</tr>
<tr id="row1742839302084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p35572516084840"><a name="p35572516084840"></a><a name="p35572516084840"></a><a href="Graphic.md#ga71a2b17d4145479ed2e2ca000eb7e86e">GetMaxScrollDistance</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1067832826084840"><a name="p1067832826084840"></a><a name="p1067832826084840"></a>uint16_t&nbsp;</p>
<p id="p169517349084840"><a name="p169517349084840"></a><a name="p169517349084840"></a>Obtains the maximum scroll distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1138761898084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p372993014084840"><a name="p372993014084840"></a><a name="p372993014084840"></a><a href="Graphic.md#ga957ec65a7efad6818be6df5169158aad">SetDragFunc</a> (EasingFunc func)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1739927061084840"><a name="p1739927061084840"></a><a name="p1739927061084840"></a>void&nbsp;</p>
<p id="p111943208084840"><a name="p111943208084840"></a><a name="p111943208084840"></a>Sets the easing function that specifies a scroll animation after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1421332180084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p29919806084840"><a name="p29919806084840"></a><a name="p29919806084840"></a><a href="Graphic.md#ga4dde5f89d70304e77a96d4f4679438c2">SetThrowDrag</a> (bool throwDrag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p37737603084840"><a name="p37737603084840"></a><a name="p37737603084840"></a>void&nbsp;</p>
<p id="p1451723338084840"><a name="p1451723338084840"></a><a name="p1451723338084840"></a>Sets whether to continue scrolling after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1113293930084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p35699705084840"><a name="p35699705084840"></a><a name="p35699705084840"></a><a href="Graphic.md#gad344babd5b251ed908cdf628fae55093">SetDragACCLevel</a> (uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p322834856084840"><a name="p322834856084840"></a><a name="p322834856084840"></a>void&nbsp;</p>
<p id="p198166616084840"><a name="p198166616084840"></a><a name="p198166616084840"></a>Sets the drag acceleration. </p>
</td>
</tr>
<tr id="row1569760872084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p555399125084840"><a name="p555399125084840"></a><a name="p555399125084840"></a><a href="Graphic.md#ga29e68195b56783f265d85506f130c664">GetDragACCLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p170356986084840"><a name="p170356986084840"></a><a name="p170356986084840"></a>uint8_t&nbsp;</p>
<p id="p1911117994084840"><a name="p1911117994084840"></a><a name="p1911117994084840"></a>Obtains the drag acceleration. </p>
</td>
</tr>
<tr id="row907434786084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p960235222084840"><a name="p960235222084840"></a><a name="p960235222084840"></a><a href="Graphic.md#gafab9d1a8f5987b50f9111c733ada6341">SetSwipeACCLevel</a> (uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1420092000084840"><a name="p1420092000084840"></a><a name="p1420092000084840"></a>void&nbsp;</p>
<p id="p118677111084840"><a name="p118677111084840"></a><a name="p118677111084840"></a>Sets the compensation distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1845293469084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p511504619084840"><a name="p511504619084840"></a><a name="p511504619084840"></a><a href="Graphic.md#ga25dad3242949f0fbeff47d6df06053f6">GetSwipeACCLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p393568199084840"><a name="p393568199084840"></a><a name="p393568199084840"></a>uint8_t&nbsp;</p>
<p id="p2132229224084840"><a name="p2132229224084840"></a><a name="p2132229224084840"></a>Obtains the compensation distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1430595300084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p158058358084840"><a name="p158058358084840"></a><a name="p158058358084840"></a><a href="Graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p243142957084840"><a name="p243142957084840"></a><a name="p243142957084840"></a>&nbsp;</p>
<p id="p1288661968084840"><a name="p1288661968084840"></a><a name="p1288661968084840"></a>A default constructor used to create a <strong id="b1311927712084840"><a name="b1311927712084840"></a><a name="b1311927712084840"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row2000029818084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1933037240084840"><a name="p1933037240084840"></a><a name="p1933037240084840"></a><a href="Graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2011801113084840"><a name="p2011801113084840"></a><a name="p2011801113084840"></a>virtual&nbsp;</p>
<p id="p1061593537084840"><a name="p1061593537084840"></a><a name="p1061593537084840"></a>A destructor used to delete the <strong id="b1770771974084840"><a name="b1770771974084840"></a><a name="b1770771974084840"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1370316296084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1275431366084840"><a name="p1275431366084840"></a><a name="p1275431366084840"></a><a href="Graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p877237214084840"><a name="p877237214084840"></a><a name="p877237214084840"></a>UIViewType&nbsp;</p>
<p id="p2054109372084840"><a name="p2054109372084840"></a><a name="p2054109372084840"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1643099681084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14317570084840"><a name="p14317570084840"></a><a name="p14317570084840"></a><a href="Graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p553532450084840"><a name="p553532450084840"></a><a name="p553532450084840"></a>virtual void&nbsp;</p>
<p id="p2018898618084840"><a name="p2018898618084840"></a><a name="p2018898618084840"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row268108930084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1476233198084840"><a name="p1476233198084840"></a><a name="p1476233198084840"></a><a href="Graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p911778965084840"><a name="p911778965084840"></a><a name="p911778965084840"></a>virtual void&nbsp;</p>
<p id="p1550236081084840"><a name="p1550236081084840"></a><a name="p1550236081084840"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1623877902084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1829616180084840"><a name="p1829616180084840"></a><a name="p1829616180084840"></a><a href="Graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p681233703084840"><a name="p681233703084840"></a><a name="p681233703084840"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1072452605084840"><a name="p1072452605084840"></a><a name="p1072452605084840"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row813014188084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p639177028084840"><a name="p639177028084840"></a><a name="p639177028084840"></a><a href="Graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1273491878084840"><a name="p1273491878084840"></a><a name="p1273491878084840"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1751442331084840"><a name="p1751442331084840"></a><a name="p1751442331084840"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row569169260084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p548732193084840"><a name="p548732193084840"></a><a name="p548732193084840"></a><a href="Graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1091166773084840"><a name="p1091166773084840"></a><a name="p1091166773084840"></a>void&nbsp;</p>
<p id="p1713305409084840"><a name="p1713305409084840"></a><a name="p1713305409084840"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row700786512084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p919422255084840"><a name="p919422255084840"></a><a name="p919422255084840"></a><a href="Graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1507596542084840"><a name="p1507596542084840"></a><a name="p1507596542084840"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1749731066084840"><a name="p1749731066084840"></a><a name="p1749731066084840"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row1065449692084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298070086084840"><a name="p298070086084840"></a><a name="p298070086084840"></a><a href="Graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p859761619084840"><a name="p859761619084840"></a><a name="p859761619084840"></a>void&nbsp;</p>
<p id="p628554075084840"><a name="p628554075084840"></a><a name="p628554075084840"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row702662524084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1672160279084840"><a name="p1672160279084840"></a><a name="p1672160279084840"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2009234524084840"><a name="p2009234524084840"></a><a name="p2009234524084840"></a>&nbsp;</p>
<p id="p820375323084840"><a name="p820375323084840"></a><a name="p820375323084840"></a>A default constructor used to create an <strong id="b2132175026084840"><a name="b2132175026084840"></a><a name="b2132175026084840"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1026899304084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p923762821084840"><a name="p923762821084840"></a><a name="p923762821084840"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1386853536084840"><a name="p1386853536084840"></a><a name="p1386853536084840"></a>&nbsp;</p>
<p id="p1976566155084840"><a name="p1976566155084840"></a><a name="p1976566155084840"></a>A constructor used to create an <strong id="b1385379983084840"><a name="b1385379983084840"></a><a name="b1385379983084840"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1357280739084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1778353029084840"><a name="p1778353029084840"></a><a name="p1778353029084840"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1597433711084840"><a name="p1597433711084840"></a><a name="p1597433711084840"></a>virtual&nbsp;</p>
<p id="p897691084084840"><a name="p897691084084840"></a><a name="p897691084084840"></a>A destructor used to delete the <strong id="b1064028632084840"><a name="b1064028632084840"></a><a name="b1064028632084840"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row2062590490084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2066779990084840"><a name="p2066779990084840"></a><a name="p2066779990084840"></a><a href="Graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p596934959084840"><a name="p596934959084840"></a><a name="p596934959084840"></a>virtual bool&nbsp;</p>
<p id="p1992009221084840"><a name="p1992009221084840"></a><a name="p1992009221084840"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row2103786237084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1855045169084840"><a name="p1855045169084840"></a><a name="p1855045169084840"></a><a href="Graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1376010686084840"><a name="p1376010686084840"></a><a name="p1376010686084840"></a>virtual void&nbsp;</p>
<p id="p666931158084840"><a name="p666931158084840"></a><a name="p666931158084840"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row715219815084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1798094315084840"><a name="p1798094315084840"></a><a name="p1798094315084840"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2141509387084840"><a name="p2141509387084840"></a><a name="p2141509387084840"></a>virtual void&nbsp;</p>
<p id="p1456849972084840"><a name="p1456849972084840"></a><a name="p1456849972084840"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1796467315084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1185263741084840"><a name="p1185263741084840"></a><a name="p1185263741084840"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p268639560084840"><a name="p268639560084840"></a><a name="p268639560084840"></a>virtual void&nbsp;</p>
<p id="p1747058003084840"><a name="p1747058003084840"></a><a name="p1747058003084840"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1916282555084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1615345202084840"><a name="p1615345202084840"></a><a name="p1615345202084840"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1882852956084840"><a name="p1882852956084840"></a><a name="p1882852956084840"></a>void&nbsp;</p>
<p id="p1420180273084840"><a name="p1420180273084840"></a><a name="p1420180273084840"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1626430687084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1725626310084840"><a name="p1725626310084840"></a><a name="p1725626310084840"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1851453149084840"><a name="p1851453149084840"></a><a name="p1851453149084840"></a>void&nbsp;</p>
<p id="p1474320418084840"><a name="p1474320418084840"></a><a name="p1474320418084840"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row879067200084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p962651302084840"><a name="p962651302084840"></a><a name="p962651302084840"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p23237360084840"><a name="p23237360084840"></a><a name="p23237360084840"></a>virtual bool&nbsp;</p>
<p id="p2003543535084840"><a name="p2003543535084840"></a><a name="p2003543535084840"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row8022525084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1817709924084840"><a name="p1817709924084840"></a><a name="p1817709924084840"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p723590546084840"><a name="p723590546084840"></a><a name="p723590546084840"></a>virtual bool&nbsp;</p>
<p id="p1250498523084840"><a name="p1250498523084840"></a><a name="p1250498523084840"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row2086697177084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p232873974084840"><a name="p232873974084840"></a><a name="p232873974084840"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2141625970084840"><a name="p2141625970084840"></a><a name="p2141625970084840"></a>virtual void&nbsp;</p>
<p id="p991765736084840"><a name="p991765736084840"></a><a name="p991765736084840"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row797320507084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1063620166084840"><a name="p1063620166084840"></a><a name="p1063620166084840"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2028480148084840"><a name="p2028480148084840"></a><a name="p2028480148084840"></a>virtual void&nbsp;</p>
<p id="p1265880924084840"><a name="p1265880924084840"></a><a name="p1265880924084840"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1726269043084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1053911031084840"><a name="p1053911031084840"></a><a name="p1053911031084840"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459564400084840"><a name="p1459564400084840"></a><a name="p1459564400084840"></a>virtual void&nbsp;</p>
<p id="p1453723680084840"><a name="p1453723680084840"></a><a name="p1453723680084840"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row2140657383084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1490893436084840"><a name="p1490893436084840"></a><a name="p1490893436084840"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p230986795084840"><a name="p230986795084840"></a><a name="p230986795084840"></a>virtual void&nbsp;</p>
<p id="p1821711343084840"><a name="p1821711343084840"></a><a name="p1821711343084840"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row738523701084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p955005500084840"><a name="p955005500084840"></a><a name="p955005500084840"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1089824851084840"><a name="p1089824851084840"></a><a name="p1089824851084840"></a>void&nbsp;</p>
<p id="p1557175086084840"><a name="p1557175086084840"></a><a name="p1557175086084840"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1986295460084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1586634259084840"><a name="p1586634259084840"></a><a name="p1586634259084840"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p450520594084840"><a name="p450520594084840"></a><a name="p450520594084840"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p1738924708084840"><a name="p1738924708084840"></a><a name="p1738924708084840"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row912819309084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1803125083084840"><a name="p1803125083084840"></a><a name="p1803125083084840"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p893071000084840"><a name="p893071000084840"></a><a name="p893071000084840"></a>void&nbsp;</p>
<p id="p1099815614084840"><a name="p1099815614084840"></a><a name="p1099815614084840"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1450535608084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1681053375084840"><a name="p1681053375084840"></a><a name="p1681053375084840"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p231447180084840"><a name="p231447180084840"></a><a name="p231447180084840"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p282086140084840"><a name="p282086140084840"></a><a name="p282086140084840"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row920432999084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p888389183084840"><a name="p888389183084840"></a><a name="p888389183084840"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1125360111084840"><a name="p1125360111084840"></a><a name="p1125360111084840"></a>void&nbsp;</p>
<p id="p429622760084840"><a name="p429622760084840"></a><a name="p429622760084840"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row637216966084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1812197756084840"><a name="p1812197756084840"></a><a name="p1812197756084840"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1645204037084840"><a name="p1645204037084840"></a><a name="p1645204037084840"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p1693302496084840"><a name="p1693302496084840"></a><a name="p1693302496084840"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1945251268084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1791427888084840"><a name="p1791427888084840"></a><a name="p1791427888084840"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p50252298084840"><a name="p50252298084840"></a><a name="p50252298084840"></a>void&nbsp;</p>
<p id="p2067973377084840"><a name="p2067973377084840"></a><a name="p2067973377084840"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row419255468084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p753890933084840"><a name="p753890933084840"></a><a name="p753890933084840"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p843979286084840"><a name="p843979286084840"></a><a name="p843979286084840"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p1366886590084840"><a name="p1366886590084840"></a><a name="p1366886590084840"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1926246731084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p901506075084840"><a name="p901506075084840"></a><a name="p901506075084840"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p927955908084840"><a name="p927955908084840"></a><a name="p927955908084840"></a>void&nbsp;</p>
<p id="p529997342084840"><a name="p529997342084840"></a><a name="p529997342084840"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1242555842084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1371897481084840"><a name="p1371897481084840"></a><a name="p1371897481084840"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1887676974084840"><a name="p1887676974084840"></a><a name="p1887676974084840"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p210979256084840"><a name="p210979256084840"></a><a name="p210979256084840"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row117644865084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p302975860084840"><a name="p302975860084840"></a><a name="p302975860084840"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p789534024084840"><a name="p789534024084840"></a><a name="p789534024084840"></a>void&nbsp;</p>
<p id="p1689713407084840"><a name="p1689713407084840"></a><a name="p1689713407084840"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1551283222084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p968070616084840"><a name="p968070616084840"></a><a name="p968070616084840"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p378629019084840"><a name="p378629019084840"></a><a name="p378629019084840"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1155573223084840"><a name="p1155573223084840"></a><a name="p1155573223084840"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1387626641084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1288922855084840"><a name="p1288922855084840"></a><a name="p1288922855084840"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2071692987084840"><a name="p2071692987084840"></a><a name="p2071692987084840"></a>virtual void&nbsp;</p>
<p id="p471946141084840"><a name="p471946141084840"></a><a name="p471946141084840"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row2113243685084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494918226084840"><a name="p1494918226084840"></a><a name="p1494918226084840"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p983276558084840"><a name="p983276558084840"></a><a name="p983276558084840"></a>bool&nbsp;</p>
<p id="p101449684084840"><a name="p101449684084840"></a><a name="p101449684084840"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1268197816084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p964725861084840"><a name="p964725861084840"></a><a name="p964725861084840"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p600460210084840"><a name="p600460210084840"></a><a name="p600460210084840"></a>void&nbsp;</p>
<p id="p1922731641084840"><a name="p1922731641084840"></a><a name="p1922731641084840"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row43650522084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p363641123084840"><a name="p363641123084840"></a><a name="p363641123084840"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1974713613084840"><a name="p1974713613084840"></a><a name="p1974713613084840"></a>bool&nbsp;</p>
<p id="p31015587084840"><a name="p31015587084840"></a><a name="p31015587084840"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1492095051084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p254296937084840"><a name="p254296937084840"></a><a name="p254296937084840"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1393008725084840"><a name="p1393008725084840"></a><a name="p1393008725084840"></a>void&nbsp;</p>
<p id="p4306586084840"><a name="p4306586084840"></a><a name="p4306586084840"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row928174167084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p365550627084840"><a name="p365550627084840"></a><a name="p365550627084840"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1530057333084840"><a name="p1530057333084840"></a><a name="p1530057333084840"></a>bool&nbsp;</p>
<p id="p1676846820084840"><a name="p1676846820084840"></a><a name="p1676846820084840"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1333924187084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p21538120084840"><a name="p21538120084840"></a><a name="p21538120084840"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p659170701084840"><a name="p659170701084840"></a><a name="p659170701084840"></a>void&nbsp;</p>
<p id="p538632782084840"><a name="p538632782084840"></a><a name="p538632782084840"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row558941102084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1061833968084840"><a name="p1061833968084840"></a><a name="p1061833968084840"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1592987108084840"><a name="p1592987108084840"></a><a name="p1592987108084840"></a>bool&nbsp;</p>
<p id="p1782070704084840"><a name="p1782070704084840"></a><a name="p1782070704084840"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row530350043084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1584165759084840"><a name="p1584165759084840"></a><a name="p1584165759084840"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1154223133084840"><a name="p1154223133084840"></a><a name="p1154223133084840"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1435300298084840"><a name="p1435300298084840"></a><a name="p1435300298084840"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row694258821084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1337571023084840"><a name="p1337571023084840"></a><a name="p1337571023084840"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1284288474084840"><a name="p1284288474084840"></a><a name="p1284288474084840"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1739674494084840"><a name="p1739674494084840"></a><a name="p1739674494084840"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row386390423084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1653237298084840"><a name="p1653237298084840"></a><a name="p1653237298084840"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748967714084840"><a name="p748967714084840"></a><a name="p748967714084840"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1188760350084840"><a name="p1188760350084840"></a><a name="p1188760350084840"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1421040150084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1076879497084840"><a name="p1076879497084840"></a><a name="p1076879497084840"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1286563321084840"><a name="p1286563321084840"></a><a name="p1286563321084840"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1659330830084840"><a name="p1659330830084840"></a><a name="p1659330830084840"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row69386925084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170166130084840"><a name="p170166130084840"></a><a name="p170166130084840"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2144275385084840"><a name="p2144275385084840"></a><a name="p2144275385084840"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p470620741084840"><a name="p470620741084840"></a><a name="p470620741084840"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row967266615084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p554836010084840"><a name="p554836010084840"></a><a name="p554836010084840"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p366967049084840"><a name="p366967049084840"></a><a name="p366967049084840"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p2087266990084840"><a name="p2087266990084840"></a><a name="p2087266990084840"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1072441803084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p412161419084840"><a name="p412161419084840"></a><a name="p412161419084840"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p624136426084840"><a name="p624136426084840"></a><a name="p624136426084840"></a>void&nbsp;</p>
<p id="p1242648923084840"><a name="p1242648923084840"></a><a name="p1242648923084840"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1327875470084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1827460950084840"><a name="p1827460950084840"></a><a name="p1827460950084840"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p417297384084840"><a name="p417297384084840"></a><a name="p417297384084840"></a>virtual void&nbsp;</p>
<p id="p566449568084840"><a name="p566449568084840"></a><a name="p566449568084840"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row182326337084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220924491084840"><a name="p1220924491084840"></a><a name="p1220924491084840"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p359134528084840"><a name="p359134528084840"></a><a name="p359134528084840"></a>virtual int16_t&nbsp;</p>
<p id="p828852037084840"><a name="p828852037084840"></a><a name="p828852037084840"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row680588941084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1688813897084840"><a name="p1688813897084840"></a><a name="p1688813897084840"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p485886566084840"><a name="p485886566084840"></a><a name="p485886566084840"></a>virtual void&nbsp;</p>
<p id="p1885264357084840"><a name="p1885264357084840"></a><a name="p1885264357084840"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1351583933084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p634306771084840"><a name="p634306771084840"></a><a name="p634306771084840"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p758554248084840"><a name="p758554248084840"></a><a name="p758554248084840"></a>virtual int16_t&nbsp;</p>
<p id="p1457115919084840"><a name="p1457115919084840"></a><a name="p1457115919084840"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1997046124084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1222808775084840"><a name="p1222808775084840"></a><a name="p1222808775084840"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1122634418084840"><a name="p1122634418084840"></a><a name="p1122634418084840"></a>virtual void&nbsp;</p>
<p id="p1392790806084840"><a name="p1392790806084840"></a><a name="p1392790806084840"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1673165962084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1392007958084840"><a name="p1392007958084840"></a><a name="p1392007958084840"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1828089546084840"><a name="p1828089546084840"></a><a name="p1828089546084840"></a>virtual void&nbsp;</p>
<p id="p127302744084840"><a name="p127302744084840"></a><a name="p127302744084840"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1048136105084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p652232868084840"><a name="p652232868084840"></a><a name="p652232868084840"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p442416856084840"><a name="p442416856084840"></a><a name="p442416856084840"></a>int16_t&nbsp;</p>
<p id="p1011563638084840"><a name="p1011563638084840"></a><a name="p1011563638084840"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row106193226084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p46245757084840"><a name="p46245757084840"></a><a name="p46245757084840"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751614689084840"><a name="p751614689084840"></a><a name="p751614689084840"></a>virtual void&nbsp;</p>
<p id="p227297378084840"><a name="p227297378084840"></a><a name="p227297378084840"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1258222280084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p348221545084840"><a name="p348221545084840"></a><a name="p348221545084840"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1273345759084840"><a name="p1273345759084840"></a><a name="p1273345759084840"></a>int16_t&nbsp;</p>
<p id="p506291520084840"><a name="p506291520084840"></a><a name="p506291520084840"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row572360235084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p458017499084840"><a name="p458017499084840"></a><a name="p458017499084840"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1147519147084840"><a name="p1147519147084840"></a><a name="p1147519147084840"></a>virtual void&nbsp;</p>
<p id="p1016501952084840"><a name="p1016501952084840"></a><a name="p1016501952084840"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1164149519084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p963571854084840"><a name="p963571854084840"></a><a name="p963571854084840"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p952478868084840"><a name="p952478868084840"></a><a name="p952478868084840"></a>virtual void&nbsp;</p>
<p id="p731730183084840"><a name="p731730183084840"></a><a name="p731730183084840"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row2085527321084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p482473580084840"><a name="p482473580084840"></a><a name="p482473580084840"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p529510779084840"><a name="p529510779084840"></a><a name="p529510779084840"></a>bool&nbsp;</p>
<p id="p641400003084840"><a name="p641400003084840"></a><a name="p641400003084840"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1330035259084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p899853631084840"><a name="p899853631084840"></a><a name="p899853631084840"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p193143418084840"><a name="p193143418084840"></a><a name="p193143418084840"></a>void&nbsp;</p>
<p id="p1785409011084840"><a name="p1785409011084840"></a><a name="p1785409011084840"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row118932495084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p955142750084840"><a name="p955142750084840"></a><a name="p955142750084840"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1547251920084840"><a name="p1547251920084840"></a><a name="p1547251920084840"></a>void&nbsp;</p>
<p id="p486711224084840"><a name="p486711224084840"></a><a name="p486711224084840"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row518263350084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p665198851084840"><a name="p665198851084840"></a><a name="p665198851084840"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p286696308084840"><a name="p286696308084840"></a><a name="p286696308084840"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p131515246084840"><a name="p131515246084840"></a><a name="p131515246084840"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1804353994084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1565446905084840"><a name="p1565446905084840"></a><a name="p1565446905084840"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1248081556084840"><a name="p1248081556084840"></a><a name="p1248081556084840"></a>void&nbsp;</p>
<p id="p127595226084840"><a name="p127595226084840"></a><a name="p127595226084840"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1409705170084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p134685317084840"><a name="p134685317084840"></a><a name="p134685317084840"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2074574070084840"><a name="p2074574070084840"></a><a name="p2074574070084840"></a>const char *&nbsp;</p>
<p id="p2101494431084840"><a name="p2101494431084840"></a><a name="p2101494431084840"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row811033783084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p50783731084840"><a name="p50783731084840"></a><a name="p50783731084840"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="UTILS.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2146641439084840"><a name="p2146641439084840"></a><a name="p2146641439084840"></a>void&nbsp;</p>
<p id="p884488748084840"><a name="p884488748084840"></a><a name="p884488748084840"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row504266661084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1598389010084840"><a name="p1598389010084840"></a><a name="p1598389010084840"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1338386826084840"><a name="p1338386826084840"></a><a name="p1338386826084840"></a>int16_t&nbsp;</p>
<p id="p793457035084840"><a name="p793457035084840"></a><a name="p793457035084840"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1555611824084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1360588178084840"><a name="p1360588178084840"></a><a name="p1360588178084840"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p452354793084840"><a name="p452354793084840"></a><a name="p452354793084840"></a>virtual void&nbsp;</p>
<p id="p888929202084840"><a name="p888929202084840"></a><a name="p888929202084840"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row2045508932084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p735768370084840"><a name="p735768370084840"></a><a name="p735768370084840"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p63456889084840"><a name="p63456889084840"></a><a name="p63456889084840"></a>void&nbsp;</p>
<p id="p322025010084840"><a name="p322025010084840"></a><a name="p322025010084840"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row513032642084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p527513884084840"><a name="p527513884084840"></a><a name="p527513884084840"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p755356712084840"><a name="p755356712084840"></a><a name="p755356712084840"></a>void&nbsp;</p>
<p id="p223297074084840"><a name="p223297074084840"></a><a name="p223297074084840"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row37731007084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2082289880084840"><a name="p2082289880084840"></a><a name="p2082289880084840"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1357020285084840"><a name="p1357020285084840"></a><a name="p1357020285084840"></a>void&nbsp;</p>
<p id="p67062473084840"><a name="p67062473084840"></a><a name="p67062473084840"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row391720106084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p647587367084840"><a name="p647587367084840"></a><a name="p647587367084840"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p141438556084840"><a name="p141438556084840"></a><a name="p141438556084840"></a>void&nbsp;</p>
<p id="p1570578462084840"><a name="p1570578462084840"></a><a name="p1570578462084840"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row2053910992084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1700026243084840"><a name="p1700026243084840"></a><a name="p1700026243084840"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p611979901084840"><a name="p611979901084840"></a><a name="p611979901084840"></a>void&nbsp;</p>
<p id="p653955046084840"><a name="p653955046084840"></a><a name="p653955046084840"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1396622461084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p629897425084840"><a name="p629897425084840"></a><a name="p629897425084840"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p636783498084840"><a name="p636783498084840"></a><a name="p636783498084840"></a>void&nbsp;</p>
<p id="p1180205709084840"><a name="p1180205709084840"></a><a name="p1180205709084840"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1960741201084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911935313084840"><a name="p1911935313084840"></a><a name="p1911935313084840"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p536094511084840"><a name="p536094511084840"></a><a name="p536094511084840"></a>void&nbsp;</p>
<p id="p2079536501084840"><a name="p2079536501084840"></a><a name="p2079536501084840"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row135240863084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p144295581084840"><a name="p144295581084840"></a><a name="p144295581084840"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1468533235084840"><a name="p1468533235084840"></a><a name="p1468533235084840"></a>void&nbsp;</p>
<p id="p659798843084840"><a name="p659798843084840"></a><a name="p659798843084840"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row469013443084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p853808988084840"><a name="p853808988084840"></a><a name="p853808988084840"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1570750305084840"><a name="p1570750305084840"></a><a name="p1570750305084840"></a>void&nbsp;</p>
<p id="p1796550343084840"><a name="p1796550343084840"></a><a name="p1796550343084840"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1572639131084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p547669405084840"><a name="p547669405084840"></a><a name="p547669405084840"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p277551081084840"><a name="p277551081084840"></a><a name="p277551081084840"></a>void&nbsp;</p>
<p id="p248769908084840"><a name="p248769908084840"></a><a name="p248769908084840"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row642707258084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1881338302084840"><a name="p1881338302084840"></a><a name="p1881338302084840"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p220519415084840"><a name="p220519415084840"></a><a name="p220519415084840"></a>void&nbsp;</p>
<p id="p188618622084840"><a name="p188618622084840"></a><a name="p188618622084840"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1838750739084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1462970200084840"><a name="p1462970200084840"></a><a name="p1462970200084840"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1040775049084840"><a name="p1040775049084840"></a><a name="p1040775049084840"></a>void&nbsp;</p>
<p id="p906993940084840"><a name="p906993940084840"></a><a name="p906993940084840"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row983552331084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p995045135084840"><a name="p995045135084840"></a><a name="p995045135084840"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p735622267084840"><a name="p735622267084840"></a><a name="p735622267084840"></a>void&nbsp;</p>
<p id="p1346117298084840"><a name="p1346117298084840"></a><a name="p1346117298084840"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1316479355084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244502653084840"><a name="p1244502653084840"></a><a name="p1244502653084840"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1399698278084840"><a name="p1399698278084840"></a><a name="p1399698278084840"></a>void&nbsp;</p>
<p id="p1234429709084840"><a name="p1234429709084840"></a><a name="p1234429709084840"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row824537388084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p898916036084840"><a name="p898916036084840"></a><a name="p898916036084840"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p404165179084840"><a name="p404165179084840"></a><a name="p404165179084840"></a>void&nbsp;</p>
<p id="p867226111084840"><a name="p867226111084840"></a><a name="p867226111084840"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1196393265084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p444140157084840"><a name="p444140157084840"></a><a name="p444140157084840"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1593512587084840"><a name="p1593512587084840"></a><a name="p1593512587084840"></a>virtual void&nbsp;</p>
<p id="p1975861707084840"><a name="p1975861707084840"></a><a name="p1975861707084840"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row392632709084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p638467221084840"><a name="p638467221084840"></a><a name="p638467221084840"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1220746748084840"><a name="p1220746748084840"></a><a name="p1220746748084840"></a>virtual void&nbsp;</p>
<p id="p415512055084840"><a name="p415512055084840"></a><a name="p415512055084840"></a>Sets a style. </p>
</td>
</tr>
<tr id="row2009324881084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p535445324084840"><a name="p535445324084840"></a><a name="p535445324084840"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p941850374084840"><a name="p941850374084840"></a><a name="p941850374084840"></a>virtual int64_t&nbsp;</p>
<p id="p1693765909084840"><a name="p1693765909084840"></a><a name="p1693765909084840"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1917271804084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1012838727084840"><a name="p1012838727084840"></a><a name="p1012838727084840"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p873749785084840"><a name="p873749785084840"></a><a name="p873749785084840"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p838796329084840"><a name="p838796329084840"></a><a name="p838796329084840"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1279226897084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p939388525084840"><a name="p939388525084840"></a><a name="p939388525084840"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p464332484084840"><a name="p464332484084840"></a><a name="p464332484084840"></a>void *&nbsp;</p>
<p id="p2069128143084840"><a name="p2069128143084840"></a><a name="p2069128143084840"></a>Overrides the <strong id="b601189076084840"><a name="b601189076084840"></a><a name="b601189076084840"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1939323558084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1414849901084840"><a name="p1414849901084840"></a><a name="p1414849901084840"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p440280888084840"><a name="p440280888084840"></a><a name="p440280888084840"></a>void&nbsp;</p>
<p id="p1950022110084840"><a name="p1950022110084840"></a><a name="p1950022110084840"></a>Overrides the <strong id="b1198346848084840"><a name="b1198346848084840"></a><a name="b1198346848084840"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Attributes<a name="pub-static-attribs"></a>

<a name="table279937552084840"></a>
<table><thead align="left"><tr id="row1729529010084840"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p571135258084840"><a name="p571135258084840"></a><a name="p571135258084840"></a>Static Public Attribute Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p423248958084840"><a name="p423248958084840"></a><a name="p423248958084840"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1065621797084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2117243651084840"><a name="p2117243651084840"></a><a name="p2117243651084840"></a><a href="Graphic.md#ga34dfbde0fad8baade31c02d9e8dd5026">HORIZONTAL</a> = 0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p288615531084840"><a name="p288615531084840"></a><a name="p288615531084840"></a>Indicates the horizontal direction. </p>
</td>
</tr>
<tr id="row1018425873084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1213351775084840"><a name="p1213351775084840"></a><a name="p1213351775084840"></a><a href="Graphic.md#gacb8ccc9545b6c306f9eff97eaf5276aa">VERTICAL</a> = 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p174836116084840"><a name="p174836116084840"></a><a name="p174836116084840"></a>Indicates the vertical direction. </p>
</td>
</tr>
</tbody>
</table>

## Protected Member Functions<a name="pro-methods"></a>

<a name="table835377218084840"></a>
<table><thead align="left"><tr id="row2062268419084840"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1157354871084840"><a name="p1157354871084840"></a><a name="p1157354871084840"></a>Protected Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1015833664084840"><a name="p1015833664084840"></a><a name="p1015833664084840"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1696195948084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p776770171084840"><a name="p776770171084840"></a><a name="p776770171084840"></a><a href="Graphic.md#ga4db88368bb4908ee05aa1137982b6d0e">MoveChildByOffset</a> (int16_t xOffset, int16_t yOffset) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1091084606084840"><a name="p1091084606084840"></a><a name="p1091084606084840"></a>void&nbsp;</p>
<p id="p1581160268084840"><a name="p1581160268084840"></a><a name="p1581160268084840"></a>Moves the position of all child views. </p>
</td>
</tr>
<tr id="row2102171800084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p37924784084840"><a name="p37924784084840"></a><a name="p37924784084840"></a><a href="Graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1468885520084840"><a name="p1468885520084840"></a><a name="p1468885520084840"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p152861571084840"><a name="p152861571084840"></a><a name="p152861571084840"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1206402543084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1916196045084840"><a name="p1916196045084840"></a><a name="p1916196045084840"></a><a href="Graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p381967496084840"><a name="p381967496084840"></a><a name="p381967496084840"></a>virtual void&nbsp;</p>
<p id="p1554058850084840"><a name="p1554058850084840"></a><a name="p1554058850084840"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
</tbody>
</table>

## Static Protected Attributes<a name="pro-static-attribs"></a>

<a name="table613473993084840"></a>
<table><thead align="left"><tr id="row1158076440084840"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p350896808084840"><a name="p350896808084840"></a><a name="p350896808084840"></a>Static Protected Attribute Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1848542868084840"><a name="p1848542868084840"></a><a name="p1848542868084840"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1975715505084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087761686084840"><a name="p2087761686084840"></a><a name="p2087761686084840"></a><a href="Graphic.md#gadcba2d82501e76cfd140f05c77f96a01">ANIMATOR_TIME</a> = 12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p249178209084840"><a name="p249178209084840"></a><a name="p249178209084840"></a>Indicates that the animation duration is 12 ticks. </p>
</td>
</tr>
<tr id="row2095133963084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p450416467084840"><a name="p450416467084840"></a><a name="p450416467084840"></a><a href="Graphic.md#ga0fc4210d617931b5cb229b1ac0313249">STOP_DISTANCE</a> = 5</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p42587764084840"><a name="p42587764084840"></a><a name="p42587764084840"></a>Indicates the maximum distance of an invalid dragging. Dragging is not triggered if the distance is less than this value. </p>
</td>
</tr>
<tr id="row1490208180084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p727683476084840"><a name="p727683476084840"></a><a name="p727683476084840"></a><a href="Graphic.md#ga81883a607d2cb3356560fc0f8f84cf74">DEFAULT_BLANK_SIZE</a> = 30</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p894327666084840"><a name="p894327666084840"></a><a name="p894327666084840"></a>Indicates the maximum distance between the first and the last tab when the current view is not in a cycle swipe mode. The page can be rebound after the setting. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table647227892084840"></a>
<table><thead align="left"><tr id="row1755877157084840"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p376453330084840"><a name="p376453330084840"></a><a name="p376453330084840"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p257824283084840"><a name="p257824283084840"></a><a name="p257824283084840"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1608934859084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1076146223084840"><a name="p1076146223084840"></a><a name="p1076146223084840"></a><a href="Graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1491849845084840"><a name="p1491849845084840"></a><a name="p1491849845084840"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row325112413084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1972647668084840"><a name="p1972647668084840"></a><a name="p1972647668084840"></a><a href="Graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2121311153084840"><a name="p2121311153084840"></a><a name="p2121311153084840"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row1432522303084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1023236732084840"><a name="p1023236732084840"></a><a name="p1023236732084840"></a><a href="Graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2011415315084840"><a name="p2011415315084840"></a><a name="p2011415315084840"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row624356427084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p937145577084840"><a name="p937145577084840"></a><a name="p937145577084840"></a><a href="Graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p692430958084840"><a name="p692430958084840"></a><a name="p692430958084840"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row208017287084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1382918473084840"><a name="p1382918473084840"></a><a name="p1382918473084840"></a><a href="Graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699692209084840"><a name="p699692209084840"></a><a name="p699692209084840"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row578022516084840"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1529967966084840"><a name="p1529967966084840"></a><a name="p1529967966084840"></a><a href="Graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101429059084840"><a name="p101429059084840"></a><a name="p101429059084840"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

