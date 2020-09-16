# OHOS::UISurfaceView<a name="EN-US_TOPIC_0000001054718153"></a>

## **Overview**<a name="section1112384205093534"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Represents a surface view that interacts with the multimedia to achieve camera preview and video playback. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section504279846093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table316157117093534"></a>
<table><thead align="left"><tr id="row677420149093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2024804965093534"><a name="p2024804965093534"></a><a name="p2024804965093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p280455789093534"><a name="p280455789093534"></a><a name="p280455789093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row960020423093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429521076093534"><a name="p429521076093534"></a><a name="p429521076093534"></a><a href="graphic.md#gab8acc0b7172486e8e5d48c09fcd4c878">UISurfaceView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1368641718093534"><a name="p1368641718093534"></a><a name="p1368641718093534"></a> </p>
<p id="p610796392093534"><a name="p610796392093534"></a><a name="p610796392093534"></a>A constructor used to create a <strong id="b297377290093534"><a name="b297377290093534"></a><a name="b297377290093534"></a><a href="ohos-uisurfaceview.md">UISurfaceView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1908190994093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p753321693093534"><a name="p753321693093534"></a><a name="p753321693093534"></a><a href="graphic.md#gabf32743913a2a061ace3a5a3c88fe6fa">~UISurfaceView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1782731174093534"><a name="p1782731174093534"></a><a name="p1782731174093534"></a> </p>
<p id="p1265524986093534"><a name="p1265524986093534"></a><a name="p1265524986093534"></a>A destructor used to delete the <strong id="b1145489894093534"><a name="b1145489894093534"></a><a name="b1145489894093534"></a><a href="ohos-uisurfaceview.md">UISurfaceView</a></strong> instance. </p>
</td>
</tr>
<tr id="row24267734093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p925050497093534"><a name="p925050497093534"></a><a name="p925050497093534"></a><a href="graphic.md#ga0d19e491e590bdfeeb2a6b3fa1a6b090">GetSurface</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1326003594093534"><a name="p1326003594093534"></a><a name="p1326003594093534"></a><a href="ohos-surface.md">Surface</a> * </p>
<p id="p25862224093534"><a name="p25862224093534"></a><a name="p25862224093534"></a>Obtains the surface, which should be used together with the camera and video modules. </p>
</td>
</tr>
<tr id="row81064791093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p477088065093534"><a name="p477088065093534"></a><a name="p477088065093534"></a><a href="graphic.md#ga5d9af67ba074697876ff97f8ece305b7">SetPosition</a> (int16_t x, int16_t y) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p106498545093534"><a name="p106498545093534"></a><a name="p106498545093534"></a>void </p>
<p id="p1491622694093534"><a name="p1491622694093534"></a><a name="p1491622694093534"></a>Sets the position for this view. </p>
</td>
</tr>
<tr id="row886131353093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1204123184093534"><a name="p1204123184093534"></a><a name="p1204123184093534"></a><a href="graphic.md#ga4a505b3b207653c60161d90750f88a9d">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p364941854093534"><a name="p364941854093534"></a><a name="p364941854093534"></a>void </p>
<p id="p1577128345093534"><a name="p1577128345093534"></a><a name="p1577128345093534"></a>Sets the position and size for this view. </p>
</td>
</tr>
<tr id="row1377998394093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1233878964093534"><a name="p1233878964093534"></a><a name="p1233878964093534"></a><a href="graphic.md#gaa860971513d96f553be4e251f25c0262">Resize</a> (int16_t width, int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1918285783093534"><a name="p1918285783093534"></a><a name="p1918285783093534"></a>void </p>
<p id="p505660596093534"><a name="p505660596093534"></a><a name="p505660596093534"></a>Adjusts the size of this view. </p>
</td>
</tr>
<tr id="row1158796451093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p968044422093534"><a name="p968044422093534"></a><a name="p968044422093534"></a><a href="graphic.md#ga87457cce8ab3daa62852815ad36e9692">SetX</a> (int16_t x) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1182004234093534"><a name="p1182004234093534"></a><a name="p1182004234093534"></a>void </p>
<p id="p2027429345093534"><a name="p2027429345093534"></a><a name="p2027429345093534"></a>Sets the x-coordinate for this view. </p>
</td>
</tr>
<tr id="row99203746093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p420558279093534"><a name="p420558279093534"></a><a name="p420558279093534"></a><a href="graphic.md#gad7e27c2508753b6752594c3615b5d2fe">SetY</a> (int16_t y) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751766501093534"><a name="p751766501093534"></a><a name="p751766501093534"></a>void </p>
<p id="p1103797809093534"><a name="p1103797809093534"></a><a name="p1103797809093534"></a>Sets the y-coordinate for this view. </p>
</td>
</tr>
<tr id="row120147404093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1917465413093534"><a name="p1917465413093534"></a><a name="p1917465413093534"></a><a href="graphic.md#ga54c350b75cf87ca112b3c21791f9c559">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1756944267093534"><a name="p1756944267093534"></a><a name="p1756944267093534"></a>void </p>
<p id="p400601339093534"><a name="p400601339093534"></a><a name="p400601339093534"></a>Sets the width for this view. </p>
</td>
</tr>
<tr id="row1786842342093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1607076575093534"><a name="p1607076575093534"></a><a name="p1607076575093534"></a><a href="graphic.md#gaf90ada30a3336b947951d408b685787e">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327341612093534"><a name="p1327341612093534"></a><a name="p1327341612093534"></a>void </p>
<p id="p384691141093534"><a name="p384691141093534"></a><a name="p384691141093534"></a>Sets the height for this view. </p>
</td>
</tr>
<tr id="row1844518822093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p99471160093534"><a name="p99471160093534"></a><a name="p99471160093534"></a><a href="graphic.md#gaa6b5efec0684a2800dba70c697d3902e">SetVisible</a> (bool visible) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2144215553093534"><a name="p2144215553093534"></a><a name="p2144215553093534"></a>void </p>
<p id="p615588684093534"><a name="p615588684093534"></a><a name="p615588684093534"></a>Sets whether this view is visible. </p>
</td>
</tr>
<tr id="row1320133129093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1076645718093534"><a name="p1076645718093534"></a><a name="p1076645718093534"></a><a href="graphic.md#gaeb15d1fb86ad2e2aabddc9c36676894a">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2010765578093534"><a name="p2010765578093534"></a><a name="p2010765578093534"></a>bool </p>
<p id="p1762755440093534"><a name="p1762755440093534"></a><a name="p1762755440093534"></a>Called before this view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so that the drawing process is optimized. </p>
</td>
</tr>
<tr id="row461064510093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p182233391093534"><a name="p182233391093534"></a><a name="p182233391093534"></a><a href="graphic.md#ga30a99c506c6d8d8fc0e0bd81d52e2d52">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p565754020093534"><a name="p565754020093534"></a><a name="p565754020093534"></a>void </p>
<p id="p942224889093534"><a name="p942224889093534"></a><a name="p942224889093534"></a>Called when this view is drawn. </p>
</td>
</tr>
<tr id="row1060044473093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1633807906093534"><a name="p1633807906093534"></a><a name="p1633807906093534"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p270615167093534"><a name="p270615167093534"></a><a name="p270615167093534"></a> </p>
<p id="p1759311466093534"><a name="p1759311466093534"></a><a name="p1759311466093534"></a>A default constructor used to create an <strong id="b1420416211093534"><a name="b1420416211093534"></a><a name="b1420416211093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row579995093093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p726037991093534"><a name="p726037991093534"></a><a name="p726037991093534"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2048129184093534"><a name="p2048129184093534"></a><a name="p2048129184093534"></a> </p>
<p id="p125962405093534"><a name="p125962405093534"></a><a name="p125962405093534"></a>A constructor used to create an <strong id="b717620420093534"><a name="b717620420093534"></a><a name="b717620420093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1051345127093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p780383877093534"><a name="p780383877093534"></a><a name="p780383877093534"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1881132404093534"><a name="p1881132404093534"></a><a name="p1881132404093534"></a>virtual </p>
<p id="p1246893190093534"><a name="p1246893190093534"></a><a name="p1246893190093534"></a>A destructor used to delete the <strong id="b955713827093534"><a name="b955713827093534"></a><a name="b955713827093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row796800033093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p332424290093534"><a name="p332424290093534"></a><a name="p332424290093534"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p605055934093534"><a name="p605055934093534"></a><a name="p605055934093534"></a>virtual void </p>
<p id="p777949055093534"><a name="p777949055093534"></a><a name="p777949055093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1881585497093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1517399151093534"><a name="p1517399151093534"></a><a name="p1517399151093534"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1315981994093534"><a name="p1315981994093534"></a><a name="p1315981994093534"></a>virtual void </p>
<p id="p1827574127093534"><a name="p1827574127093534"></a><a name="p1827574127093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row878398868093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p389500268093534"><a name="p389500268093534"></a><a name="p389500268093534"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p565593159093534"><a name="p565593159093534"></a><a name="p565593159093534"></a>void </p>
<p id="p1625606972093534"><a name="p1625606972093534"></a><a name="p1625606972093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1945849700093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p583345829093534"><a name="p583345829093534"></a><a name="p583345829093534"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p394642262093534"><a name="p394642262093534"></a><a name="p394642262093534"></a>void </p>
<p id="p1755386769093534"><a name="p1755386769093534"></a><a name="p1755386769093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row891218981093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997404133093534"><a name="p1997404133093534"></a><a name="p1997404133093534"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p415048418093534"><a name="p415048418093534"></a><a name="p415048418093534"></a>virtual bool </p>
<p id="p452914727093534"><a name="p452914727093534"></a><a name="p452914727093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row457499833093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1988748892093534"><a name="p1988748892093534"></a><a name="p1988748892093534"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p77110771093534"><a name="p77110771093534"></a><a name="p77110771093534"></a>virtual bool </p>
<p id="p91118387093534"><a name="p91118387093534"></a><a name="p91118387093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row636229897093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p758263157093534"><a name="p758263157093534"></a><a name="p758263157093534"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2070320038093534"><a name="p2070320038093534"></a><a name="p2070320038093534"></a>virtual bool </p>
<p id="p265491923093534"><a name="p265491923093534"></a><a name="p265491923093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1188661325093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p361018548093534"><a name="p361018548093534"></a><a name="p361018548093534"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p852001684093534"><a name="p852001684093534"></a><a name="p852001684093534"></a>virtual bool </p>
<p id="p2039038766093534"><a name="p2039038766093534"></a><a name="p2039038766093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1893599209093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1948145183093534"><a name="p1948145183093534"></a><a name="p1948145183093534"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802137498093534"><a name="p1802137498093534"></a><a name="p1802137498093534"></a>virtual void </p>
<p id="p798372715093534"><a name="p798372715093534"></a><a name="p798372715093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row289288384093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1799866419093534"><a name="p1799866419093534"></a><a name="p1799866419093534"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p520476898093534"><a name="p520476898093534"></a><a name="p520476898093534"></a>virtual void </p>
<p id="p518142656093534"><a name="p518142656093534"></a><a name="p518142656093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row863457143093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2082741855093534"><a name="p2082741855093534"></a><a name="p2082741855093534"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p914147092093534"><a name="p914147092093534"></a><a name="p914147092093534"></a>virtual void </p>
<p id="p1470698868093534"><a name="p1470698868093534"></a><a name="p1470698868093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1082010611093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p625733828093534"><a name="p625733828093534"></a><a name="p625733828093534"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1425967313093534"><a name="p1425967313093534"></a><a name="p1425967313093534"></a>virtual void </p>
<p id="p1989590289093534"><a name="p1989590289093534"></a><a name="p1989590289093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row1213480463093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p402173203093534"><a name="p402173203093534"></a><a name="p402173203093534"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p441806406093534"><a name="p441806406093534"></a><a name="p441806406093534"></a>void </p>
<p id="p1300294220093534"><a name="p1300294220093534"></a><a name="p1300294220093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row31811567093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1574168086093534"><a name="p1574168086093534"></a><a name="p1574168086093534"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1592822870093534"><a name="p1592822870093534"></a><a name="p1592822870093534"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p1837801310093534"><a name="p1837801310093534"></a><a name="p1837801310093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1922748191093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p341354839093534"><a name="p341354839093534"></a><a name="p341354839093534"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1535815576093534"><a name="p1535815576093534"></a><a name="p1535815576093534"></a>void </p>
<p id="p146845518093534"><a name="p146845518093534"></a><a name="p146845518093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1110641855093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p216010338093534"><a name="p216010338093534"></a><a name="p216010338093534"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p23343073093534"><a name="p23343073093534"></a><a name="p23343073093534"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p2130707683093534"><a name="p2130707683093534"></a><a name="p2130707683093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row110840468093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1924485388093534"><a name="p1924485388093534"></a><a name="p1924485388093534"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1350829304093534"><a name="p1350829304093534"></a><a name="p1350829304093534"></a>void </p>
<p id="p1592613590093534"><a name="p1592613590093534"></a><a name="p1592613590093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row404845447093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1054775525093534"><a name="p1054775525093534"></a><a name="p1054775525093534"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p292503844093534"><a name="p292503844093534"></a><a name="p292503844093534"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p58813579093534"><a name="p58813579093534"></a><a name="p58813579093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row10033156093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1809595291093534"><a name="p1809595291093534"></a><a name="p1809595291093534"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2072676854093534"><a name="p2072676854093534"></a><a name="p2072676854093534"></a>void </p>
<p id="p311692352093534"><a name="p311692352093534"></a><a name="p311692352093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row409855902093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p911691174093534"><a name="p911691174093534"></a><a name="p911691174093534"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999344987093534"><a name="p1999344987093534"></a><a name="p1999344987093534"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1677460609093534"><a name="p1677460609093534"></a><a name="p1677460609093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row510334579093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1455820673093534"><a name="p1455820673093534"></a><a name="p1455820673093534"></a><a href="graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p523016985093534"><a name="p523016985093534"></a><a name="p523016985093534"></a>virtual void </p>
<p id="p311231930093534"><a name="p311231930093534"></a><a name="p311231930093534"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row636176945093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p883625200093534"><a name="p883625200093534"></a><a name="p883625200093534"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p569450348093534"><a name="p569450348093534"></a><a name="p569450348093534"></a>void </p>
<p id="p792101015093534"><a name="p792101015093534"></a><a name="p792101015093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row204099370093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p897941412093534"><a name="p897941412093534"></a><a name="p897941412093534"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p715459175093534"><a name="p715459175093534"></a><a name="p715459175093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1297165191093534"><a name="p1297165191093534"></a><a name="p1297165191093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row129623818093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p595900272093534"><a name="p595900272093534"></a><a name="p595900272093534"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1737687089093534"><a name="p1737687089093534"></a><a name="p1737687089093534"></a>void </p>
<p id="p434441500093534"><a name="p434441500093534"></a><a name="p434441500093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1467796603093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2119936326093534"><a name="p2119936326093534"></a><a name="p2119936326093534"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1880305194093534"><a name="p1880305194093534"></a><a name="p1880305194093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p608592973093534"><a name="p608592973093534"></a><a name="p608592973093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1506839505093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1749407245093534"><a name="p1749407245093534"></a><a name="p1749407245093534"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p735654157093534"><a name="p735654157093534"></a><a name="p735654157093534"></a>bool </p>
<p id="p1875382907093534"><a name="p1875382907093534"></a><a name="p1875382907093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row88403929093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1514488408093534"><a name="p1514488408093534"></a><a name="p1514488408093534"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p564473119093534"><a name="p564473119093534"></a><a name="p564473119093534"></a>void </p>
<p id="p1504596465093534"><a name="p1504596465093534"></a><a name="p1504596465093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row258000969093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p635469134093534"><a name="p635469134093534"></a><a name="p635469134093534"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p148377426093534"><a name="p148377426093534"></a><a name="p148377426093534"></a>bool </p>
<p id="p2049277774093534"><a name="p2049277774093534"></a><a name="p2049277774093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row603783177093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p440023850093534"><a name="p440023850093534"></a><a name="p440023850093534"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1033757542093534"><a name="p1033757542093534"></a><a name="p1033757542093534"></a>void </p>
<p id="p269195813093534"><a name="p269195813093534"></a><a name="p269195813093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row131655703093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p546601555093534"><a name="p546601555093534"></a><a name="p546601555093534"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1017241715093534"><a name="p1017241715093534"></a><a name="p1017241715093534"></a>bool </p>
<p id="p1653620984093534"><a name="p1653620984093534"></a><a name="p1653620984093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row888559484093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1414374676093534"><a name="p1414374676093534"></a><a name="p1414374676093534"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904233942093534"><a name="p904233942093534"></a><a name="p904233942093534"></a>void </p>
<p id="p931067176093534"><a name="p931067176093534"></a><a name="p931067176093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row735157953093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1779368560093534"><a name="p1779368560093534"></a><a name="p1779368560093534"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1741942472093534"><a name="p1741942472093534"></a><a name="p1741942472093534"></a>bool </p>
<p id="p1877421402093534"><a name="p1877421402093534"></a><a name="p1877421402093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row576818086093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p826963406093534"><a name="p826963406093534"></a><a name="p826963406093534"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101645622093534"><a name="p101645622093534"></a><a name="p101645622093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p841511401093534"><a name="p841511401093534"></a><a name="p841511401093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row860923284093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997731688093534"><a name="p1997731688093534"></a><a name="p1997731688093534"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p826153641093534"><a name="p826153641093534"></a><a name="p826153641093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p455909597093534"><a name="p455909597093534"></a><a name="p455909597093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row494429188093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p164838554093534"><a name="p164838554093534"></a><a name="p164838554093534"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1992374729093534"><a name="p1992374729093534"></a><a name="p1992374729093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p87626625093534"><a name="p87626625093534"></a><a name="p87626625093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1167700927093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p958018314093534"><a name="p958018314093534"></a><a name="p958018314093534"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1286077569093534"><a name="p1286077569093534"></a><a name="p1286077569093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1328165370093534"><a name="p1328165370093534"></a><a name="p1328165370093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row53129113093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1978369504093534"><a name="p1978369504093534"></a><a name="p1978369504093534"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764465848093534"><a name="p764465848093534"></a><a name="p764465848093534"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p949258867093534"><a name="p949258867093534"></a><a name="p949258867093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row728596234093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p23609006093534"><a name="p23609006093534"></a><a name="p23609006093534"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p991396475093534"><a name="p991396475093534"></a><a name="p991396475093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1715024796093534"><a name="p1715024796093534"></a><a name="p1715024796093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row487878382093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1706442093534"><a name="p1706442093534"></a><a name="p1706442093534"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2098655274093534"><a name="p2098655274093534"></a><a name="p2098655274093534"></a>void </p>
<p id="p700093322093534"><a name="p700093322093534"></a><a name="p700093322093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row166836882093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1397890845093534"><a name="p1397890845093534"></a><a name="p1397890845093534"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p893405486093534"><a name="p893405486093534"></a><a name="p893405486093534"></a>virtual int16_t </p>
<p id="p1911966435093534"><a name="p1911966435093534"></a><a name="p1911966435093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1613426598093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p696895214093534"><a name="p696895214093534"></a><a name="p696895214093534"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1388987828093534"><a name="p1388987828093534"></a><a name="p1388987828093534"></a>virtual int16_t </p>
<p id="p567762632093534"><a name="p567762632093534"></a><a name="p567762632093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row664857692093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1314708127093534"><a name="p1314708127093534"></a><a name="p1314708127093534"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1321237582093534"><a name="p1321237582093534"></a><a name="p1321237582093534"></a>int16_t </p>
<p id="p1921018049093534"><a name="p1921018049093534"></a><a name="p1921018049093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1782492533093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2130601081093534"><a name="p2130601081093534"></a><a name="p2130601081093534"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p72744647093534"><a name="p72744647093534"></a><a name="p72744647093534"></a>int16_t </p>
<p id="p1226327479093534"><a name="p1226327479093534"></a><a name="p1226327479093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1848884703093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p734683391093534"><a name="p734683391093534"></a><a name="p734683391093534"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1147032508093534"><a name="p1147032508093534"></a><a name="p1147032508093534"></a>bool </p>
<p id="p1719755890093534"><a name="p1719755890093534"></a><a name="p1719755890093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1573131018093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1427201627093534"><a name="p1427201627093534"></a><a name="p1427201627093534"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1910252862093534"><a name="p1910252862093534"></a><a name="p1910252862093534"></a>void </p>
<p id="p2039201659093534"><a name="p2039201659093534"></a><a name="p2039201659093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row102162191093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616552591093534"><a name="p1616552591093534"></a><a name="p1616552591093534"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1890304150093534"><a name="p1890304150093534"></a><a name="p1890304150093534"></a>void </p>
<p id="p835653462093534"><a name="p835653462093534"></a><a name="p835653462093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row367749234093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755368439093534"><a name="p1755368439093534"></a><a name="p1755368439093534"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2109929627093534"><a name="p2109929627093534"></a><a name="p2109929627093534"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p1048545828093534"><a name="p1048545828093534"></a><a name="p1048545828093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row903001342093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1273404471093534"><a name="p1273404471093534"></a><a name="p1273404471093534"></a><a href="graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p974025290093534"><a name="p974025290093534"></a><a name="p974025290093534"></a>virtual <a href="ohos-uiview.md">UIView</a> * </p>
<p id="p261874193093534"><a name="p261874193093534"></a><a name="p261874193093534"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row1793819428093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p235263234093534"><a name="p235263234093534"></a><a name="p235263234093534"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1105388095093534"><a name="p1105388095093534"></a><a name="p1105388095093534"></a>void </p>
<p id="p183937663093534"><a name="p183937663093534"></a><a name="p183937663093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row889892335093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1062662053093534"><a name="p1062662053093534"></a><a name="p1062662053093534"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p634649199093534"><a name="p634649199093534"></a><a name="p634649199093534"></a>const char * </p>
<p id="p26846296093534"><a name="p26846296093534"></a><a name="p26846296093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1322241846093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1093874055093534"><a name="p1093874055093534"></a><a name="p1093874055093534"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041456410093534"><a name="p1041456410093534"></a><a name="p1041456410093534"></a>void </p>
<p id="p497363763093534"><a name="p497363763093534"></a><a name="p497363763093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row261292649093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1088228467093534"><a name="p1088228467093534"></a><a name="p1088228467093534"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1231865005093534"><a name="p1231865005093534"></a><a name="p1231865005093534"></a>int16_t </p>
<p id="p374468486093534"><a name="p374468486093534"></a><a name="p374468486093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1995217896093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p859755921093534"><a name="p859755921093534"></a><a name="p859755921093534"></a><a href="graphic.md#ga6d23780da1faa1071197b716bca365e0">GetViewType</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p708612584093534"><a name="p708612584093534"></a><a name="p708612584093534"></a>virtual UIViewType </p>
<p id="p2122393067093534"><a name="p2122393067093534"></a><a name="p2122393067093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1035521634093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2140225250093534"><a name="p2140225250093534"></a><a name="p2140225250093534"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p407067690093534"><a name="p407067690093534"></a><a name="p407067690093534"></a>virtual void </p>
<p id="p1986845001093534"><a name="p1986845001093534"></a><a name="p1986845001093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1846506928093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p632040938093534"><a name="p632040938093534"></a><a name="p632040938093534"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1062725769093534"><a name="p1062725769093534"></a><a name="p1062725769093534"></a>void </p>
<p id="p83906929093534"><a name="p83906929093534"></a><a name="p83906929093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1438747569093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p44694265093534"><a name="p44694265093534"></a><a name="p44694265093534"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1213703401093534"><a name="p1213703401093534"></a><a name="p1213703401093534"></a>void </p>
<p id="p862604089093534"><a name="p862604089093534"></a><a name="p862604089093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row757707007093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p145035810093534"><a name="p145035810093534"></a><a name="p145035810093534"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1848839754093534"><a name="p1848839754093534"></a><a name="p1848839754093534"></a>void </p>
<p id="p1244738768093534"><a name="p1244738768093534"></a><a name="p1244738768093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1170247032093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p15584509093534"><a name="p15584509093534"></a><a name="p15584509093534"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p198981323093534"><a name="p198981323093534"></a><a name="p198981323093534"></a>void </p>
<p id="p1472979924093534"><a name="p1472979924093534"></a><a name="p1472979924093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row459804887093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p849997559093534"><a name="p849997559093534"></a><a name="p849997559093534"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p781189733093534"><a name="p781189733093534"></a><a name="p781189733093534"></a>void </p>
<p id="p393527999093534"><a name="p393527999093534"></a><a name="p393527999093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row37744357093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1567002890093534"><a name="p1567002890093534"></a><a name="p1567002890093534"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p377574675093534"><a name="p377574675093534"></a><a name="p377574675093534"></a>void </p>
<p id="p1815991499093534"><a name="p1815991499093534"></a><a name="p1815991499093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row814991217093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p278316133093534"><a name="p278316133093534"></a><a name="p278316133093534"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p32278304093534"><a name="p32278304093534"></a><a name="p32278304093534"></a>void </p>
<p id="p794868428093534"><a name="p794868428093534"></a><a name="p794868428093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row701909330093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p606838482093534"><a name="p606838482093534"></a><a name="p606838482093534"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1197141831093534"><a name="p1197141831093534"></a><a name="p1197141831093534"></a>void </p>
<p id="p77837500093534"><a name="p77837500093534"></a><a name="p77837500093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1835245357093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1049489761093534"><a name="p1049489761093534"></a><a name="p1049489761093534"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p283805507093534"><a name="p283805507093534"></a><a name="p283805507093534"></a>void </p>
<p id="p2080641126093534"><a name="p2080641126093534"></a><a name="p2080641126093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1251629797093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898725437093534"><a name="p1898725437093534"></a><a name="p1898725437093534"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1146311395093534"><a name="p1146311395093534"></a><a name="p1146311395093534"></a>void </p>
<p id="p1340349332093534"><a name="p1340349332093534"></a><a name="p1340349332093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row513673912093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1965510897093534"><a name="p1965510897093534"></a><a name="p1965510897093534"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p75237404093534"><a name="p75237404093534"></a><a name="p75237404093534"></a>void </p>
<p id="p1494257479093534"><a name="p1494257479093534"></a><a name="p1494257479093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row987605953093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1858337959093534"><a name="p1858337959093534"></a><a name="p1858337959093534"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p337231416093534"><a name="p337231416093534"></a><a name="p337231416093534"></a>void </p>
<p id="p2079845760093534"><a name="p2079845760093534"></a><a name="p2079845760093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1310193098093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1204078073093534"><a name="p1204078073093534"></a><a name="p1204078073093534"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p547315822093534"><a name="p547315822093534"></a><a name="p547315822093534"></a>void </p>
<p id="p774023481093534"><a name="p774023481093534"></a><a name="p774023481093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1907110808093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p813338712093534"><a name="p813338712093534"></a><a name="p813338712093534"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p891265048093534"><a name="p891265048093534"></a><a name="p891265048093534"></a>void </p>
<p id="p484256430093534"><a name="p484256430093534"></a><a name="p484256430093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row860441894093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1702451494093534"><a name="p1702451494093534"></a><a name="p1702451494093534"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1103851128093534"><a name="p1103851128093534"></a><a name="p1103851128093534"></a>void </p>
<p id="p66831066093534"><a name="p66831066093534"></a><a name="p66831066093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1968642175093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228987253093534"><a name="p228987253093534"></a><a name="p228987253093534"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1240180471093534"><a name="p1240180471093534"></a><a name="p1240180471093534"></a>virtual void </p>
<p id="p49318045093534"><a name="p49318045093534"></a><a name="p49318045093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1172573669093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1945326803093534"><a name="p1945326803093534"></a><a name="p1945326803093534"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2143302775093534"><a name="p2143302775093534"></a><a name="p2143302775093534"></a>virtual void </p>
<p id="p1718188103093534"><a name="p1718188103093534"></a><a name="p1718188103093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1387237049093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1079274025093534"><a name="p1079274025093534"></a><a name="p1079274025093534"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1237994196093534"><a name="p1237994196093534"></a><a name="p1237994196093534"></a>virtual int64_t </p>
<p id="p1283774468093534"><a name="p1283774468093534"></a><a name="p1283774468093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row149374244093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p8946339093534"><a name="p8946339093534"></a><a name="p8946339093534"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572258444093534"><a name="p572258444093534"></a><a name="p572258444093534"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p1570973403093534"><a name="p1570973403093534"></a><a name="p1570973403093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1773231051093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2098697751093534"><a name="p2098697751093534"></a><a name="p2098697751093534"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p400159479093534"><a name="p400159479093534"></a><a name="p400159479093534"></a>void * </p>
<p id="p1547763590093534"><a name="p1547763590093534"></a><a name="p1547763590093534"></a>Overrides the <strong id="b1238302156093534"><a name="b1238302156093534"></a><a name="b1238302156093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row513534500093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1981847661093534"><a name="p1981847661093534"></a><a name="p1981847661093534"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1688415243093534"><a name="p1688415243093534"></a><a name="p1688415243093534"></a>void </p>
<p id="p1022784804093534"><a name="p1022784804093534"></a><a name="p1022784804093534"></a>Overrides the <strong id="b1730984850093534"><a name="b1730984850093534"></a><a name="b1730984850093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

