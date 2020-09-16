# OHOS::UIView<a name="EN-US_TOPIC_0000001054718155"></a>

## **Overview**<a name="section108701852093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the base class of a view, providing basic view attributes and operations. All views are derived from this class. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section766154749093535"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table32775974093535"></a>
<table><thead align="left"><tr id="row1672128692093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1910149181093535"><a name="p1910149181093535"></a><a name="p1910149181093535"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1653231048093535"><a name="p1653231048093535"></a><a name="p1653231048093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1050494566093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1792002535093535"><a name="p1792002535093535"></a><a name="p1792002535093535"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p981948006093535"><a name="p981948006093535"></a><a name="p981948006093535"></a>Defines a click event listener. You need to register this listener with the view to listen to click events. </p>
</td>
</tr>
<tr id="row948317532093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p260267450093535"><a name="p260267450093535"></a><a name="p260267450093535"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1574741775093535"><a name="p1574741775093535"></a><a name="p1574741775093535"></a>Defines a drag event listener. You need to register this listener with the view to listen to drag events. </p>
</td>
</tr>
<tr id="row2103652673093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p922970071093535"><a name="p922970071093535"></a><a name="p922970071093535"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1821360758093535"><a name="p1821360758093535"></a><a name="p1821360758093535"></a>Defines a long-press event listener. You need to register this listener with the view to listen to long-press events. </p>
</td>
</tr>
<tr id="row1717193633093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1161342517093535"><a name="p1161342517093535"></a><a name="p1161342517093535"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p310862788093535"><a name="p310862788093535"></a><a name="p310862788093535"></a>Defines a touch event listener. You need to register this listener with the view to listen to touch events. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table54729272093535"></a>
<table><thead align="left"><tr id="row306081208093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p503956476093535"><a name="p503956476093535"></a><a name="p503956476093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1644455078093535"><a name="p1644455078093535"></a><a name="p1644455078093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1151418165093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p625638471093535"><a name="p625638471093535"></a><a name="p625638471093535"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p897396390093535"><a name="p897396390093535"></a><a name="p897396390093535"></a> </p>
<p id="p1591449529093535"><a name="p1591449529093535"></a><a name="p1591449529093535"></a>A default constructor used to create an <strong id="b444950104093535"><a name="b444950104093535"></a><a name="b444950104093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1126935606093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1621014399093535"><a name="p1621014399093535"></a><a name="p1621014399093535"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1738008144093535"><a name="p1738008144093535"></a><a name="p1738008144093535"></a> </p>
<p id="p338942853093535"><a name="p338942853093535"></a><a name="p338942853093535"></a>A constructor used to create an <strong id="b1760842580093535"><a name="b1760842580093535"></a><a name="b1760842580093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row2105849767093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1608605563093535"><a name="p1608605563093535"></a><a name="p1608605563093535"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p892227836093535"><a name="p892227836093535"></a><a name="p892227836093535"></a>virtual </p>
<p id="p1047085166093535"><a name="p1047085166093535"></a><a name="p1047085166093535"></a>A destructor used to delete the <strong id="b1730818781093535"><a name="b1730818781093535"></a><a name="b1730818781093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row227535296093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p193717141093535"><a name="p193717141093535"></a><a name="p193717141093535"></a><a href="graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p277957375093535"><a name="p277957375093535"></a><a name="p277957375093535"></a>virtual bool </p>
<p id="p1307619993093535"><a name="p1307619993093535"></a><a name="p1307619993093535"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1983409915093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1562849720093535"><a name="p1562849720093535"></a><a name="p1562849720093535"></a><a href="graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p173218766093535"><a name="p173218766093535"></a><a name="p173218766093535"></a>virtual void </p>
<p id="p2010674721093535"><a name="p2010674721093535"></a><a name="p2010674721093535"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row156176610093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p773352720093535"><a name="p773352720093535"></a><a name="p773352720093535"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2132313406093535"><a name="p2132313406093535"></a><a name="p2132313406093535"></a>virtual void </p>
<p id="p712326353093535"><a name="p712326353093535"></a><a name="p712326353093535"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row930488829093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p432107106093535"><a name="p432107106093535"></a><a name="p432107106093535"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p474264120093535"><a name="p474264120093535"></a><a name="p474264120093535"></a>virtual void </p>
<p id="p287381432093535"><a name="p287381432093535"></a><a name="p287381432093535"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row613685568093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1367440748093535"><a name="p1367440748093535"></a><a name="p1367440748093535"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1420719942093535"><a name="p1420719942093535"></a><a name="p1420719942093535"></a>void </p>
<p id="p396910510093535"><a name="p396910510093535"></a><a name="p396910510093535"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row378135630093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1243104689093535"><a name="p1243104689093535"></a><a name="p1243104689093535"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p936384249093535"><a name="p936384249093535"></a><a name="p936384249093535"></a>void </p>
<p id="p1367596323093535"><a name="p1367596323093535"></a><a name="p1367596323093535"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row31379093093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p503289831093535"><a name="p503289831093535"></a><a name="p503289831093535"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p682808912093535"><a name="p682808912093535"></a><a name="p682808912093535"></a>virtual bool </p>
<p id="p1018711600093535"><a name="p1018711600093535"></a><a name="p1018711600093535"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1085617546093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p220126009093535"><a name="p220126009093535"></a><a name="p220126009093535"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p638878496093535"><a name="p638878496093535"></a><a name="p638878496093535"></a>virtual bool </p>
<p id="p317193613093535"><a name="p317193613093535"></a><a name="p317193613093535"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row668893872093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1559134268093535"><a name="p1559134268093535"></a><a name="p1559134268093535"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2089878418093535"><a name="p2089878418093535"></a><a name="p2089878418093535"></a>virtual bool </p>
<p id="p98293043093535"><a name="p98293043093535"></a><a name="p98293043093535"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row912115758093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1728311634093535"><a name="p1728311634093535"></a><a name="p1728311634093535"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1246109342093535"><a name="p1246109342093535"></a><a name="p1246109342093535"></a>virtual bool </p>
<p id="p269381263093535"><a name="p269381263093535"></a><a name="p269381263093535"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row696776238093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1765433372093535"><a name="p1765433372093535"></a><a name="p1765433372093535"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1518477392093535"><a name="p1518477392093535"></a><a name="p1518477392093535"></a>virtual void </p>
<p id="p1125251873093535"><a name="p1125251873093535"></a><a name="p1125251873093535"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row720264075093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p866076286093535"><a name="p866076286093535"></a><a name="p866076286093535"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p687650259093535"><a name="p687650259093535"></a><a name="p687650259093535"></a>virtual void </p>
<p id="p1111502506093535"><a name="p1111502506093535"></a><a name="p1111502506093535"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1551711653093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p139962398093535"><a name="p139962398093535"></a><a name="p139962398093535"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p22909030093535"><a name="p22909030093535"></a><a name="p22909030093535"></a>virtual void </p>
<p id="p2070554125093535"><a name="p2070554125093535"></a><a name="p2070554125093535"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row346028202093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1792981296093535"><a name="p1792981296093535"></a><a name="p1792981296093535"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p240611168093535"><a name="p240611168093535"></a><a name="p240611168093535"></a>virtual void </p>
<p id="p1791190287093535"><a name="p1791190287093535"></a><a name="p1791190287093535"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row439500057093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1834877521093535"><a name="p1834877521093535"></a><a name="p1834877521093535"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p636946535093535"><a name="p636946535093535"></a><a name="p636946535093535"></a>void </p>
<p id="p1102854888093535"><a name="p1102854888093535"></a><a name="p1102854888093535"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row596081925093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p584898434093535"><a name="p584898434093535"></a><a name="p584898434093535"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514261652093535"><a name="p514261652093535"></a><a name="p514261652093535"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p1324887849093535"><a name="p1324887849093535"></a><a name="p1324887849093535"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1075944203093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p574428129093535"><a name="p574428129093535"></a><a name="p574428129093535"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67936870093535"><a name="p67936870093535"></a><a name="p67936870093535"></a>void </p>
<p id="p301971802093535"><a name="p301971802093535"></a><a name="p301971802093535"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1880203924093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671861684093535"><a name="p671861684093535"></a><a name="p671861684093535"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1872960830093535"><a name="p1872960830093535"></a><a name="p1872960830093535"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p1770757169093535"><a name="p1770757169093535"></a><a name="p1770757169093535"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1942179920093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p186990369093535"><a name="p186990369093535"></a><a name="p186990369093535"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1245024289093535"><a name="p1245024289093535"></a><a name="p1245024289093535"></a>void </p>
<p id="p834390503093535"><a name="p834390503093535"></a><a name="p834390503093535"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1251911490093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1723606758093535"><a name="p1723606758093535"></a><a name="p1723606758093535"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1421494066093535"><a name="p1421494066093535"></a><a name="p1421494066093535"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p1191559909093535"><a name="p1191559909093535"></a><a name="p1191559909093535"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1797857060093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p592273790093535"><a name="p592273790093535"></a><a name="p592273790093535"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1151243455093535"><a name="p1151243455093535"></a><a name="p1151243455093535"></a>void </p>
<p id="p971963587093535"><a name="p971963587093535"></a><a name="p971963587093535"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1533857705093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1753696654093535"><a name="p1753696654093535"></a><a name="p1753696654093535"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p963054833093535"><a name="p963054833093535"></a><a name="p963054833093535"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1896098274093535"><a name="p1896098274093535"></a><a name="p1896098274093535"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row2081691774093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1441058543093535"><a name="p1441058543093535"></a><a name="p1441058543093535"></a><a href="graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p594885973093535"><a name="p594885973093535"></a><a name="p594885973093535"></a>virtual void </p>
<p id="p1176812524093535"><a name="p1176812524093535"></a><a name="p1176812524093535"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row218614007093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1972340191093535"><a name="p1972340191093535"></a><a name="p1972340191093535"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p277076386093535"><a name="p277076386093535"></a><a name="p277076386093535"></a>void </p>
<p id="p1602336185093535"><a name="p1602336185093535"></a><a name="p1602336185093535"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1688094837093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1009177835093535"><a name="p1009177835093535"></a><a name="p1009177835093535"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p29907027093535"><a name="p29907027093535"></a><a name="p29907027093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1210877285093535"><a name="p1210877285093535"></a><a name="p1210877285093535"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1604725995093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1388121345093535"><a name="p1388121345093535"></a><a name="p1388121345093535"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p758772383093535"><a name="p758772383093535"></a><a name="p758772383093535"></a>void </p>
<p id="p1212701395093535"><a name="p1212701395093535"></a><a name="p1212701395093535"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row794627736093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1647103440093535"><a name="p1647103440093535"></a><a name="p1647103440093535"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2005598938093535"><a name="p2005598938093535"></a><a name="p2005598938093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p2123031116093535"><a name="p2123031116093535"></a><a name="p2123031116093535"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row205257698093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p824004450093535"><a name="p824004450093535"></a><a name="p824004450093535"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p996516425093535"><a name="p996516425093535"></a><a name="p996516425093535"></a>virtual void </p>
<p id="p1502649456093535"><a name="p1502649456093535"></a><a name="p1502649456093535"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row602594560093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p753232427093535"><a name="p753232427093535"></a><a name="p753232427093535"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1461819011093535"><a name="p1461819011093535"></a><a name="p1461819011093535"></a>bool </p>
<p id="p890290390093535"><a name="p890290390093535"></a><a name="p890290390093535"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row327472678093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p417186452093535"><a name="p417186452093535"></a><a name="p417186452093535"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1787943027093535"><a name="p1787943027093535"></a><a name="p1787943027093535"></a>void </p>
<p id="p1642660065093535"><a name="p1642660065093535"></a><a name="p1642660065093535"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row2006993288093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1140923254093535"><a name="p1140923254093535"></a><a name="p1140923254093535"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635458984093535"><a name="p635458984093535"></a><a name="p635458984093535"></a>bool </p>
<p id="p388014450093535"><a name="p388014450093535"></a><a name="p388014450093535"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1682437233093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1310688058093535"><a name="p1310688058093535"></a><a name="p1310688058093535"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1242347340093535"><a name="p1242347340093535"></a><a name="p1242347340093535"></a>void </p>
<p id="p1813281860093535"><a name="p1813281860093535"></a><a name="p1813281860093535"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row2039929518093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1838688286093535"><a name="p1838688286093535"></a><a name="p1838688286093535"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1346154893093535"><a name="p1346154893093535"></a><a name="p1346154893093535"></a>bool </p>
<p id="p383826318093535"><a name="p383826318093535"></a><a name="p383826318093535"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row444606084093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1338866317093535"><a name="p1338866317093535"></a><a name="p1338866317093535"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p340777602093535"><a name="p340777602093535"></a><a name="p340777602093535"></a>void </p>
<p id="p531264483093535"><a name="p531264483093535"></a><a name="p531264483093535"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row2101644339093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1641234795093535"><a name="p1641234795093535"></a><a name="p1641234795093535"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1107613193093535"><a name="p1107613193093535"></a><a name="p1107613193093535"></a>bool </p>
<p id="p289714201093535"><a name="p289714201093535"></a><a name="p289714201093535"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1049453614093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1373404081093535"><a name="p1373404081093535"></a><a name="p1373404081093535"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p303564089093535"><a name="p303564089093535"></a><a name="p303564089093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1656336048093535"><a name="p1656336048093535"></a><a name="p1656336048093535"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row986914622093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1999254912093535"><a name="p1999254912093535"></a><a name="p1999254912093535"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2018278104093535"><a name="p2018278104093535"></a><a name="p2018278104093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1806929669093535"><a name="p1806929669093535"></a><a name="p1806929669093535"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row2057439691093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1757571466093535"><a name="p1757571466093535"></a><a name="p1757571466093535"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p471175656093535"><a name="p471175656093535"></a><a name="p471175656093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1465689604093535"><a name="p1465689604093535"></a><a name="p1465689604093535"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row435013565093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2073802256093535"><a name="p2073802256093535"></a><a name="p2073802256093535"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2014252054093535"><a name="p2014252054093535"></a><a name="p2014252054093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p273339283093535"><a name="p273339283093535"></a><a name="p273339283093535"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1141139812093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p983051626093535"><a name="p983051626093535"></a><a name="p983051626093535"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1787737333093535"><a name="p1787737333093535"></a><a name="p1787737333093535"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1426293759093535"><a name="p1426293759093535"></a><a name="p1426293759093535"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row563672850093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1538700574093535"><a name="p1538700574093535"></a><a name="p1538700574093535"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p197260000093535"><a name="p197260000093535"></a><a name="p197260000093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p449424326093535"><a name="p449424326093535"></a><a name="p449424326093535"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row622630283093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p887180962093535"><a name="p887180962093535"></a><a name="p887180962093535"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1472224924093535"><a name="p1472224924093535"></a><a name="p1472224924093535"></a>void </p>
<p id="p1485657754093535"><a name="p1485657754093535"></a><a name="p1485657754093535"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1114808624093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1717919434093535"><a name="p1717919434093535"></a><a name="p1717919434093535"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p17769996093535"><a name="p17769996093535"></a><a name="p17769996093535"></a>virtual void </p>
<p id="p503801296093535"><a name="p503801296093535"></a><a name="p503801296093535"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row757659695093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044528087093535"><a name="p2044528087093535"></a><a name="p2044528087093535"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101302859093535"><a name="p101302859093535"></a><a name="p101302859093535"></a>virtual int16_t </p>
<p id="p1383382516093535"><a name="p1383382516093535"></a><a name="p1383382516093535"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1139964994093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1727730211093535"><a name="p1727730211093535"></a><a name="p1727730211093535"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p198524943093535"><a name="p198524943093535"></a><a name="p198524943093535"></a>virtual void </p>
<p id="p1293528362093535"><a name="p1293528362093535"></a><a name="p1293528362093535"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1318283181093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1009362373093535"><a name="p1009362373093535"></a><a name="p1009362373093535"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1741197140093535"><a name="p1741197140093535"></a><a name="p1741197140093535"></a>virtual int16_t </p>
<p id="p281415992093535"><a name="p281415992093535"></a><a name="p281415992093535"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1356143123093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p324705972093535"><a name="p324705972093535"></a><a name="p324705972093535"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p671921189093535"><a name="p671921189093535"></a><a name="p671921189093535"></a>virtual void </p>
<p id="p1234781760093535"><a name="p1234781760093535"></a><a name="p1234781760093535"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row976882668093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p461406152093535"><a name="p461406152093535"></a><a name="p461406152093535"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1616796152093535"><a name="p1616796152093535"></a><a name="p1616796152093535"></a>virtual void </p>
<p id="p1870704909093535"><a name="p1870704909093535"></a><a name="p1870704909093535"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row970287145093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p537870059093535"><a name="p537870059093535"></a><a name="p537870059093535"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p723815980093535"><a name="p723815980093535"></a><a name="p723815980093535"></a>int16_t </p>
<p id="p1472852309093535"><a name="p1472852309093535"></a><a name="p1472852309093535"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row735622456093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p797690748093535"><a name="p797690748093535"></a><a name="p797690748093535"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554463949093535"><a name="p1554463949093535"></a><a name="p1554463949093535"></a>virtual void </p>
<p id="p42838768093535"><a name="p42838768093535"></a><a name="p42838768093535"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row953728591093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p534491621093535"><a name="p534491621093535"></a><a name="p534491621093535"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1555706557093535"><a name="p1555706557093535"></a><a name="p1555706557093535"></a>int16_t </p>
<p id="p1948143102093535"><a name="p1948143102093535"></a><a name="p1948143102093535"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row560808541093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p214878306093535"><a name="p214878306093535"></a><a name="p214878306093535"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1579985823093535"><a name="p1579985823093535"></a><a name="p1579985823093535"></a>virtual void </p>
<p id="p496175605093535"><a name="p496175605093535"></a><a name="p496175605093535"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row947452430093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p359351048093535"><a name="p359351048093535"></a><a name="p359351048093535"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2000881570093535"><a name="p2000881570093535"></a><a name="p2000881570093535"></a>virtual void </p>
<p id="p2072780714093535"><a name="p2072780714093535"></a><a name="p2072780714093535"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1019799430093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p664294398093535"><a name="p664294398093535"></a><a name="p664294398093535"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1383813366093535"><a name="p1383813366093535"></a><a name="p1383813366093535"></a>bool </p>
<p id="p846432194093535"><a name="p846432194093535"></a><a name="p846432194093535"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1939860090093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772429453093535"><a name="p1772429453093535"></a><a name="p1772429453093535"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p723662692093535"><a name="p723662692093535"></a><a name="p723662692093535"></a>void </p>
<p id="p1713875041093535"><a name="p1713875041093535"></a><a name="p1713875041093535"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row258091874093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p796442499093535"><a name="p796442499093535"></a><a name="p796442499093535"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1463242715093535"><a name="p1463242715093535"></a><a name="p1463242715093535"></a>void </p>
<p id="p205227495093535"><a name="p205227495093535"></a><a name="p205227495093535"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1551852457093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p527729669093535"><a name="p527729669093535"></a><a name="p527729669093535"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p942111042093535"><a name="p942111042093535"></a><a name="p942111042093535"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p784405697093535"><a name="p784405697093535"></a><a name="p784405697093535"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1502677234093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p922531402093535"><a name="p922531402093535"></a><a name="p922531402093535"></a><a href="graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1153528437093535"><a name="p1153528437093535"></a><a name="p1153528437093535"></a>virtual <a href="ohos-uiview.md">UIView</a> * </p>
<p id="p312723210093535"><a name="p312723210093535"></a><a name="p312723210093535"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row803427365093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p683863127093535"><a name="p683863127093535"></a><a name="p683863127093535"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p215069041093535"><a name="p215069041093535"></a><a name="p215069041093535"></a>void </p>
<p id="p1668738135093535"><a name="p1668738135093535"></a><a name="p1668738135093535"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1423345031093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858461946093535"><a name="p858461946093535"></a><a name="p858461946093535"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1225705887093535"><a name="p1225705887093535"></a><a name="p1225705887093535"></a>const char * </p>
<p id="p1189443857093535"><a name="p1189443857093535"></a><a name="p1189443857093535"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1666326804093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1625656314093535"><a name="p1625656314093535"></a><a name="p1625656314093535"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p274302908093535"><a name="p274302908093535"></a><a name="p274302908093535"></a>void </p>
<p id="p786684522093535"><a name="p786684522093535"></a><a name="p786684522093535"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row585954793093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p128292016093535"><a name="p128292016093535"></a><a name="p128292016093535"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1224799239093535"><a name="p1224799239093535"></a><a name="p1224799239093535"></a>int16_t </p>
<p id="p541931905093535"><a name="p541931905093535"></a><a name="p541931905093535"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1643802119093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p295398964093535"><a name="p295398964093535"></a><a name="p295398964093535"></a><a href="graphic.md#ga6d23780da1faa1071197b716bca365e0">GetViewType</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2000963269093535"><a name="p2000963269093535"></a><a name="p2000963269093535"></a>virtual UIViewType </p>
<p id="p2131498244093535"><a name="p2131498244093535"></a><a name="p2131498244093535"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1252591758093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1079877508093535"><a name="p1079877508093535"></a><a name="p1079877508093535"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367207669093535"><a name="p1367207669093535"></a><a name="p1367207669093535"></a>virtual void </p>
<p id="p570993717093535"><a name="p570993717093535"></a><a name="p570993717093535"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1780261497093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p261460018093535"><a name="p261460018093535"></a><a name="p261460018093535"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2077960152093535"><a name="p2077960152093535"></a><a name="p2077960152093535"></a>void </p>
<p id="p728743094093535"><a name="p728743094093535"></a><a name="p728743094093535"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row851563498093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p300766120093535"><a name="p300766120093535"></a><a name="p300766120093535"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p331422540093535"><a name="p331422540093535"></a><a name="p331422540093535"></a>void </p>
<p id="p1731547494093535"><a name="p1731547494093535"></a><a name="p1731547494093535"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row676161302093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p949960672093535"><a name="p949960672093535"></a><a name="p949960672093535"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p219606470093535"><a name="p219606470093535"></a><a name="p219606470093535"></a>void </p>
<p id="p2060083975093535"><a name="p2060083975093535"></a><a name="p2060083975093535"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1959346240093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p885882235093535"><a name="p885882235093535"></a><a name="p885882235093535"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389769881093535"><a name="p1389769881093535"></a><a name="p1389769881093535"></a>void </p>
<p id="p2138010387093535"><a name="p2138010387093535"></a><a name="p2138010387093535"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row215032977093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1532024645093535"><a name="p1532024645093535"></a><a name="p1532024645093535"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p236847885093535"><a name="p236847885093535"></a><a name="p236847885093535"></a>void </p>
<p id="p1254362851093535"><a name="p1254362851093535"></a><a name="p1254362851093535"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row882405135093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p642713675093535"><a name="p642713675093535"></a><a name="p642713675093535"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p884109429093535"><a name="p884109429093535"></a><a name="p884109429093535"></a>void </p>
<p id="p1047669473093535"><a name="p1047669473093535"></a><a name="p1047669473093535"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row397859586093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p620193273093535"><a name="p620193273093535"></a><a name="p620193273093535"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1120103882093535"><a name="p1120103882093535"></a><a name="p1120103882093535"></a>void </p>
<p id="p466220595093535"><a name="p466220595093535"></a><a name="p466220595093535"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1779292539093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p141602312093535"><a name="p141602312093535"></a><a name="p141602312093535"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1271875526093535"><a name="p1271875526093535"></a><a name="p1271875526093535"></a>void </p>
<p id="p774433232093535"><a name="p774433232093535"></a><a name="p774433232093535"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row3479936093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p889129639093535"><a name="p889129639093535"></a><a name="p889129639093535"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1136525892093535"><a name="p1136525892093535"></a><a name="p1136525892093535"></a>void </p>
<p id="p1512537890093535"><a name="p1512537890093535"></a><a name="p1512537890093535"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row2087887252093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2000305915093535"><a name="p2000305915093535"></a><a name="p2000305915093535"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087370215093535"><a name="p2087370215093535"></a><a name="p2087370215093535"></a>void </p>
<p id="p1678018087093535"><a name="p1678018087093535"></a><a name="p1678018087093535"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row543388745093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p449265331093535"><a name="p449265331093535"></a><a name="p449265331093535"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1189363600093535"><a name="p1189363600093535"></a><a name="p1189363600093535"></a>void </p>
<p id="p2038116546093535"><a name="p2038116546093535"></a><a name="p2038116546093535"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row467614726093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2046638000093535"><a name="p2046638000093535"></a><a name="p2046638000093535"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p720722522093535"><a name="p720722522093535"></a><a name="p720722522093535"></a>void </p>
<p id="p1598528008093535"><a name="p1598528008093535"></a><a name="p1598528008093535"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row827511472093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1251276181093535"><a name="p1251276181093535"></a><a name="p1251276181093535"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1746428584093535"><a name="p1746428584093535"></a><a name="p1746428584093535"></a>void </p>
<p id="p2066712892093535"><a name="p2066712892093535"></a><a name="p2066712892093535"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row2019534577093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298454752093535"><a name="p298454752093535"></a><a name="p298454752093535"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p741669374093535"><a name="p741669374093535"></a><a name="p741669374093535"></a>void </p>
<p id="p333539838093535"><a name="p333539838093535"></a><a name="p333539838093535"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1150543364093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p962395725093535"><a name="p962395725093535"></a><a name="p962395725093535"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1990977069093535"><a name="p1990977069093535"></a><a name="p1990977069093535"></a>void </p>
<p id="p705203879093535"><a name="p705203879093535"></a><a name="p705203879093535"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1917185284093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1945883314093535"><a name="p1945883314093535"></a><a name="p1945883314093535"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p287758276093535"><a name="p287758276093535"></a><a name="p287758276093535"></a>virtual void </p>
<p id="p1584441849093535"><a name="p1584441849093535"></a><a name="p1584441849093535"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1395123764093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1405521469093535"><a name="p1405521469093535"></a><a name="p1405521469093535"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p89602947093535"><a name="p89602947093535"></a><a name="p89602947093535"></a>virtual void </p>
<p id="p340471974093535"><a name="p340471974093535"></a><a name="p340471974093535"></a>Sets a style. </p>
</td>
</tr>
<tr id="row368089371093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2064024232093535"><a name="p2064024232093535"></a><a name="p2064024232093535"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1819055200093535"><a name="p1819055200093535"></a><a name="p1819055200093535"></a>virtual int64_t </p>
<p id="p200632255093535"><a name="p200632255093535"></a><a name="p200632255093535"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1380104860093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1801610972093535"><a name="p1801610972093535"></a><a name="p1801610972093535"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032224187093535"><a name="p1032224187093535"></a><a name="p1032224187093535"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p2112560525093535"><a name="p2112560525093535"></a><a name="p2112560525093535"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1492380107093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p776673178093535"><a name="p776673178093535"></a><a name="p776673178093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1106439551093535"><a name="p1106439551093535"></a><a name="p1106439551093535"></a>void * </p>
<p id="p1326113423093535"><a name="p1326113423093535"></a><a name="p1326113423093535"></a>Overrides the <strong id="b1537085682093535"><a name="b1537085682093535"></a><a name="b1537085682093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1193068836093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p689189173093535"><a name="p689189173093535"></a><a name="p689189173093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1652490759093535"><a name="p1652490759093535"></a><a name="p1652490759093535"></a>void </p>
<p id="p1418160492093535"><a name="p1418160492093535"></a><a name="p1418160492093535"></a>Overrides the <strong id="b1235416213093535"><a name="b1235416213093535"></a><a name="b1235416213093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

