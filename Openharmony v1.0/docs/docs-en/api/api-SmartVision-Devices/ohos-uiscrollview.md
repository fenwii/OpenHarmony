# OHOS::UIScrollView<a name="EN-US_TOPIC_0000001055078165"></a>

## **Overview**<a name="section118958724093534"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Supports horizontal or vertical scroll of child views. This class is inherited from  [UIAbstractScroll](ohos-uiabstractscroll.md). 

Horizontal or vertical scroll occurs only when the width or height of the child view is greater than that of the  **[UIScrollView](ohos-uiscrollview.md)**.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section903379228093534"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table197356170093534"></a>
<table><thead align="left"><tr id="row859182093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1683669084093534"><a name="p1683669084093534"></a><a name="p1683669084093534"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p832947089093534"><a name="p832947089093534"></a><a name="p832947089093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1332784363093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p772344169093534"><a name="p772344169093534"></a><a name="p772344169093534"></a><a href="ohos-uiscrollview-onscrolllistener.md">OnScrollListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1470352662093534"><a name="p1470352662093534"></a><a name="p1470352662093534"></a>Represents a listener that contains a callback to be invoked upon scroll state changes. The state can either be <strong id="b1926941223093534"><a name="b1926941223093534"></a><a name="b1926941223093534"></a>SCROLL_STATE_STOP</strong> or <strong id="b2034399391093534"><a name="b2034399391093534"></a><a name="b2034399391093534"></a>SCROLL_STATE_MOVE</strong>. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table206521381093534"></a>
<table><thead align="left"><tr id="row790901344093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p280771633093534"><a name="p280771633093534"></a><a name="p280771633093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1418216577093534"><a name="p1418216577093534"></a><a name="p1418216577093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1744127333093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1909960933093534"><a name="p1909960933093534"></a><a name="p1909960933093534"></a><a href="graphic.md#ga83285fe2d337f5d2242204e739e130ab">UIScrollView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1694594340093534"><a name="p1694594340093534"></a><a name="p1694594340093534"></a> </p>
<p id="p561209847093534"><a name="p561209847093534"></a><a name="p561209847093534"></a>A constructor used to create a <strong id="b165830339093534"><a name="b165830339093534"></a><a name="b165830339093534"></a><a href="ohos-uiscrollview.md">UIScrollView</a></strong> instance, with both horizontal and vertical scrolls supported. </p>
</td>
</tr>
<tr id="row634331270093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719937129093534"><a name="p719937129093534"></a><a name="p719937129093534"></a><a href="graphic.md#ga1b5f674824f5c27038329aa1223b137b">~UIScrollView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2119291090093534"><a name="p2119291090093534"></a><a name="p2119291090093534"></a>virtual </p>
<p id="p664763924093534"><a name="p664763924093534"></a><a name="p664763924093534"></a>A destructor used to delete the <strong id="b520292415093534"><a name="b520292415093534"></a><a name="b520292415093534"></a><a href="ohos-uiscrollview.md">UIScrollView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1429578965093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p336370578093534"><a name="p336370578093534"></a><a name="p336370578093534"></a><a href="graphic.md#ga1feefd393c568a12ec4e877e207d598c">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1762173786093534"><a name="p1762173786093534"></a><a name="p1762173786093534"></a>UIViewType </p>
<p id="p324834200093534"><a name="p324834200093534"></a><a name="p324834200093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row874619222093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1922808550093534"><a name="p1922808550093534"></a><a name="p1922808550093534"></a><a href="graphic.md#ga8a7764e5a85e40b497a67fdf54a1b4c8">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059639469093534"><a name="p1059639469093534"></a><a name="p1059639469093534"></a>void </p>
<p id="p2022972018093534"><a name="p2022972018093534"></a><a name="p2022972018093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row821259875093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1353959067093534"><a name="p1353959067093534"></a><a name="p1353959067093534"></a><a href="graphic.md#ga2fde4511d743ccc257308d9a0c035076">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p963386271093534"><a name="p963386271093534"></a><a name="p963386271093534"></a>bool </p>
<p id="p191143275093534"><a name="p191143275093534"></a><a name="p191143275093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1648319132093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1238644911093534"><a name="p1238644911093534"></a><a name="p1238644911093534"></a><a href="graphic.md#ga05e30354bc97373fbd30f8c045dbbeea">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1388673440093534"><a name="p1388673440093534"></a><a name="p1388673440093534"></a>bool </p>
<p id="p1199074338093534"><a name="p1199074338093534"></a><a name="p1199074338093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1968410438093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1890469675093534"><a name="p1890469675093534"></a><a name="p1890469675093534"></a><a href="graphic.md#ga54572308575db6d19997343c65d72fbb">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p393060112093534"><a name="p393060112093534"></a><a name="p393060112093534"></a>void </p>
<p id="p1879639788093534"><a name="p1879639788093534"></a><a name="p1879639788093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row23589027093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973621764093534"><a name="p973621764093534"></a><a name="p973621764093534"></a><a href="graphic.md#ga233e426fee2ff5b0973637bb3bf545ee">ScrollBy</a> (int16_t xDistance, int16_t yDistance)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1339281553093534"><a name="p1339281553093534"></a><a name="p1339281553093534"></a>void </p>
<p id="p1857820608093534"><a name="p1857820608093534"></a><a name="p1857820608093534"></a>Scrolls the content of this view. </p>
</td>
</tr>
<tr id="row1238984869093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p829047101093534"><a name="p829047101093534"></a><a name="p829047101093534"></a><a href="graphic.md#ga992fe30e6840d966688154ea96c362f4">SetScrollbarWidth</a> (uint8_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1135149848093534"><a name="p1135149848093534"></a><a name="p1135149848093534"></a>void </p>
<p id="p1391500554093534"><a name="p1391500554093534"></a><a name="p1391500554093534"></a>Sets the width for this scroll bar. </p>
</td>
</tr>
<tr id="row613501354093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p109217415093534"><a name="p109217415093534"></a><a name="p109217415093534"></a><a href="graphic.md#ga53a40f1c665fc7333e6aac156a1f5b81">SetHorizontalScrollState</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1416799479093534"><a name="p1416799479093534"></a><a name="p1416799479093534"></a>void </p>
<p id="p1118889637093534"><a name="p1118889637093534"></a><a name="p1118889637093534"></a>Sets whether a horizontal scroll is enabled. </p>
</td>
</tr>
<tr id="row896610237093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1157463677093534"><a name="p1157463677093534"></a><a name="p1157463677093534"></a><a href="graphic.md#ga0549786419ae52253f832a44cad91afe">GetHorizontalScrollState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1955692802093534"><a name="p1955692802093534"></a><a name="p1955692802093534"></a>bool </p>
<p id="p2106588867093534"><a name="p2106588867093534"></a><a name="p2106588867093534"></a>Checks whether a horizontal scroll is enabled. </p>
</td>
</tr>
<tr id="row21874751093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1860364500093534"><a name="p1860364500093534"></a><a name="p1860364500093534"></a><a href="graphic.md#ga8a6839614c863229666675c289a5cff4">SetVerticalScrollState</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1482420062093534"><a name="p1482420062093534"></a><a name="p1482420062093534"></a>void </p>
<p id="p384219760093534"><a name="p384219760093534"></a><a name="p384219760093534"></a>Sets whether a vertical scroll is enabled. </p>
</td>
</tr>
<tr id="row659185365093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1612642445093534"><a name="p1612642445093534"></a><a name="p1612642445093534"></a><a href="graphic.md#gac2095a64edba0fe0483a5475b11b45b2">GetVerticalScrollState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1317006047093534"><a name="p1317006047093534"></a><a name="p1317006047093534"></a>bool </p>
<p id="p1199979598093534"><a name="p1199979598093534"></a><a name="p1199979598093534"></a>Checks whether a vertical scroll is enabled. </p>
</td>
</tr>
<tr id="row911089959093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p410456998093534"><a name="p410456998093534"></a><a name="p410456998093534"></a><a href="graphic.md#ga011dae1414a147441e1d32d548545f24">SetXScrollBarVisible</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p270900416093534"><a name="p270900416093534"></a><a name="p270900416093534"></a>void </p>
<p id="p1511453455093534"><a name="p1511453455093534"></a><a name="p1511453455093534"></a>Sets whether the horizontal scroll bar is visible. </p>
</td>
</tr>
<tr id="row2508745093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p331052397093534"><a name="p331052397093534"></a><a name="p331052397093534"></a><a href="graphic.md#ga36fcdfce31fab72f54a37062d3f4a6f1">SetYScrollBarVisible</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p909587012093534"><a name="p909587012093534"></a><a name="p909587012093534"></a>void </p>
<p id="p1834184649093534"><a name="p1834184649093534"></a><a name="p1834184649093534"></a>Sets whether the vertical scroll bar is visible. </p>
</td>
</tr>
<tr id="row1172896821093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2077039984093534"><a name="p2077039984093534"></a><a name="p2077039984093534"></a><a href="graphic.md#gad66c58c77db0dd0c507e45290ad5cd24">RegisterScrollListener</a> (<a href="ohos-uiscrollview-onscrolllistener.md">OnScrollListener</a> *scrollListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1773227314093534"><a name="p1773227314093534"></a><a name="p1773227314093534"></a>void </p>
<p id="p787266973093534"><a name="p787266973093534"></a><a name="p787266973093534"></a>Registers a listener that contains a callback to be invoked upon scroll state changes. </p>
</td>
</tr>
<tr id="row215732746093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1818377881093534"><a name="p1818377881093534"></a><a name="p1818377881093534"></a><a href="graphic.md#ga93a169fba7c98f6534692cba9e8d539b">UIAbstractScroll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p463204499093534"><a name="p463204499093534"></a><a name="p463204499093534"></a> </p>
<p id="p931606849093534"><a name="p931606849093534"></a><a name="p931606849093534"></a>A constructor used to create a <strong id="b940795215093534"><a name="b940795215093534"></a><a name="b940795215093534"></a><a href="ohos-uiabstractscroll.md">UIAbstractScroll</a></strong> instance. </p>
</td>
</tr>
<tr id="row423260534093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p235244415093534"><a name="p235244415093534"></a><a name="p235244415093534"></a><a href="graphic.md#ga414798ec7357edc85409128fba0a813c">~UIAbstractScroll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1351304125093534"><a name="p1351304125093534"></a><a name="p1351304125093534"></a>virtual </p>
<p id="p382509781093534"><a name="p382509781093534"></a><a name="p382509781093534"></a>A destructor used to delete the <strong id="b1295854954093534"><a name="b1295854954093534"></a><a name="b1295854954093534"></a><a href="ohos-uiabstractscroll.md">UIAbstractScroll</a></strong> instance. </p>
</td>
</tr>
<tr id="row1494557724093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1682343660093534"><a name="p1682343660093534"></a><a name="p1682343660093534"></a><a href="graphic.md#ga443783170697bea9a933843ad2a92283">GetDirection</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1533250612093534"><a name="p1533250612093534"></a><a name="p1533250612093534"></a>uint8_t </p>
<p id="p1888597267093534"><a name="p1888597267093534"></a><a name="p1888597267093534"></a>Obtains the scroll direction. </p>
</td>
</tr>
<tr id="row809471836093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1006962885093534"><a name="p1006962885093534"></a><a name="p1006962885093534"></a><a href="graphic.md#gab37cea97d63ee9ca609c9a1ed0f1e281">SetScrollBlankSize</a> (uint16_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p303119781093534"><a name="p303119781093534"></a><a name="p303119781093534"></a>void </p>
<p id="p671722910093534"><a name="p671722910093534"></a><a name="p671722910093534"></a>Sets the blank size for this scroll view. </p>
</td>
</tr>
<tr id="row1040736684093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1301294696093534"><a name="p1301294696093534"></a><a name="p1301294696093534"></a><a href="graphic.md#gae2d6f5c97a316ecd3b41fecfa35a351f">SetMaxScrollDistance</a> (uint16_t distance)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p3451298093534"><a name="p3451298093534"></a><a name="p3451298093534"></a>void </p>
<p id="p105755402093534"><a name="p105755402093534"></a><a name="p105755402093534"></a>Sets the maximum scroll distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row632290013093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1458875686093534"><a name="p1458875686093534"></a><a name="p1458875686093534"></a><a href="graphic.md#ga5d7fefcd2057e868a8f6c6a6000aa7ef">SetReboundSize</a> (uint16_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p54994223093534"><a name="p54994223093534"></a><a name="p54994223093534"></a>void </p>
<p id="p1859221721093534"><a name="p1859221721093534"></a><a name="p1859221721093534"></a>Sets the rebound size, which is the distance a knob moves after being released when it reaches the end of a scrollbar. </p>
</td>
</tr>
<tr id="row2012653018093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1800489635093534"><a name="p1800489635093534"></a><a name="p1800489635093534"></a><a href="graphic.md#ga71a2b17d4145479ed2e2ca000eb7e86e">GetMaxScrollDistance</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p622437249093534"><a name="p622437249093534"></a><a name="p622437249093534"></a>uint16_t </p>
<p id="p574912197093534"><a name="p574912197093534"></a><a name="p574912197093534"></a>Obtains the maximum scroll distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row884525641093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1319052804093534"><a name="p1319052804093534"></a><a name="p1319052804093534"></a><a href="graphic.md#ga957ec65a7efad6818be6df5169158aad">SetDragFunc</a> (EasingFunc func)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069931890093534"><a name="p2069931890093534"></a><a name="p2069931890093534"></a>void </p>
<p id="p933014000093534"><a name="p933014000093534"></a><a name="p933014000093534"></a>Sets the easing function that specifies a scroll animation after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1781526944093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p449289221093534"><a name="p449289221093534"></a><a name="p449289221093534"></a><a href="graphic.md#ga4dde5f89d70304e77a96d4f4679438c2">SetThrowDrag</a> (bool throwDrag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2048262124093534"><a name="p2048262124093534"></a><a name="p2048262124093534"></a>void </p>
<p id="p448902544093534"><a name="p448902544093534"></a><a name="p448902544093534"></a>Sets whether to continue scrolling after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1122397873093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p903921253093534"><a name="p903921253093534"></a><a name="p903921253093534"></a><a href="graphic.md#ga5013215d3075616ae081849ef52bb57a">MoveChildByOffset</a> (int16_t offsetX, int16_t offsetY) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1340499460093534"><a name="p1340499460093534"></a><a name="p1340499460093534"></a>void </p>
<p id="p1703663621093534"><a name="p1703663621093534"></a><a name="p1703663621093534"></a>Moves the position of all child views. </p>
</td>
</tr>
<tr id="row1823571261093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1186436482093534"><a name="p1186436482093534"></a><a name="p1186436482093534"></a><a href="graphic.md#gad344babd5b251ed908cdf628fae55093">SetDragACCLevel</a> (uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p512292184093534"><a name="p512292184093534"></a><a name="p512292184093534"></a>void </p>
<p id="p910365047093534"><a name="p910365047093534"></a><a name="p910365047093534"></a>Sets the drag acceleration. </p>
</td>
</tr>
<tr id="row1715454414093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1243965586093534"><a name="p1243965586093534"></a><a name="p1243965586093534"></a><a href="graphic.md#ga29e68195b56783f265d85506f130c664">GetDragACCLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p273332423093534"><a name="p273332423093534"></a><a name="p273332423093534"></a>uint8_t </p>
<p id="p1655027337093534"><a name="p1655027337093534"></a><a name="p1655027337093534"></a>Obtains the drag acceleration. </p>
</td>
</tr>
<tr id="row574056059093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1463683696093534"><a name="p1463683696093534"></a><a name="p1463683696093534"></a><a href="graphic.md#gafab9d1a8f5987b50f9111c733ada6341">SetSwipeACCLevel</a> (uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p880522166093534"><a name="p880522166093534"></a><a name="p880522166093534"></a>void </p>
<p id="p1350264486093534"><a name="p1350264486093534"></a><a name="p1350264486093534"></a>Sets the compensation distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row256489687093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p622511461093534"><a name="p622511461093534"></a><a name="p622511461093534"></a><a href="graphic.md#ga25dad3242949f0fbeff47d6df06053f6">GetSwipeACCLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1296320123093534"><a name="p1296320123093534"></a><a name="p1296320123093534"></a>uint8_t </p>
<p id="p1890342466093534"><a name="p1890342466093534"></a><a name="p1890342466093534"></a>Obtains the compensation distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row873707439093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1150944617093534"><a name="p1150944617093534"></a><a name="p1150944617093534"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p351486258093534"><a name="p351486258093534"></a><a name="p351486258093534"></a> </p>
<p id="p149484763093534"><a name="p149484763093534"></a><a name="p149484763093534"></a>A default constructor used to create a <strong id="b999094963093534"><a name="b999094963093534"></a><a name="b999094963093534"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row745666408093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1760540357093534"><a name="p1760540357093534"></a><a name="p1760540357093534"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1986539230093534"><a name="p1986539230093534"></a><a name="p1986539230093534"></a>virtual </p>
<p id="p1690429041093534"><a name="p1690429041093534"></a><a name="p1690429041093534"></a>A destructor used to delete the <strong id="b632170492093534"><a name="b632170492093534"></a><a name="b632170492093534"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row652494512093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p26101852093534"><a name="p26101852093534"></a><a name="p26101852093534"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p333530009093534"><a name="p333530009093534"></a><a name="p333530009093534"></a>UIViewType </p>
<p id="p1205001534093534"><a name="p1205001534093534"></a><a name="p1205001534093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1252334562093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1862884711093534"><a name="p1862884711093534"></a><a name="p1862884711093534"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1825003015093534"><a name="p1825003015093534"></a><a name="p1825003015093534"></a>virtual void </p>
<p id="p1654837977093534"><a name="p1654837977093534"></a><a name="p1654837977093534"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row1828652527093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2068199377093534"><a name="p2068199377093534"></a><a name="p2068199377093534"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p489803297093534"><a name="p489803297093534"></a><a name="p489803297093534"></a>virtual void </p>
<p id="p2097576124093534"><a name="p2097576124093534"></a><a name="p2097576124093534"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row950682605093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p450070292093534"><a name="p450070292093534"></a><a name="p450070292093534"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1336196060093534"><a name="p1336196060093534"></a><a name="p1336196060093534"></a>virtual void </p>
<p id="p1288997322093534"><a name="p1288997322093534"></a><a name="p1288997322093534"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row379828918093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1228528334093534"><a name="p1228528334093534"></a><a name="p1228528334093534"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181773674093534"><a name="p181773674093534"></a><a name="p181773674093534"></a>virtual void </p>
<p id="p1062564816093534"><a name="p1062564816093534"></a><a name="p1062564816093534"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1515370414093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1731839509093534"><a name="p1731839509093534"></a><a name="p1731839509093534"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p817169862093534"><a name="p817169862093534"></a><a name="p817169862093534"></a>virtual void </p>
<p id="p1511805371093534"><a name="p1511805371093534"></a><a name="p1511805371093534"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1200138318093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1227311443093534"><a name="p1227311443093534"></a><a name="p1227311443093534"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021854285093534"><a name="p2021854285093534"></a><a name="p2021854285093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p411223238093534"><a name="p411223238093534"></a><a name="p411223238093534"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1424245003093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p945315618093534"><a name="p945315618093534"></a><a name="p945315618093534"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p930377626093534"><a name="p930377626093534"></a><a name="p930377626093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1535798178093534"><a name="p1535798178093534"></a><a name="p1535798178093534"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row562996228093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1351964653093534"><a name="p1351964653093534"></a><a name="p1351964653093534"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1138253330093534"><a name="p1138253330093534"></a><a name="p1138253330093534"></a>void </p>
<p id="p1852525898093534"><a name="p1852525898093534"></a><a name="p1852525898093534"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1211091543093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1041309500093534"><a name="p1041309500093534"></a><a name="p1041309500093534"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p950775999093534"><a name="p950775999093534"></a><a name="p950775999093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p568678590093534"><a name="p568678590093534"></a><a name="p568678590093534"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row233270946093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p870395547093534"><a name="p870395547093534"></a><a name="p870395547093534"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p362210088093534"><a name="p362210088093534"></a><a name="p362210088093534"></a>void </p>
<p id="p585823620093534"><a name="p585823620093534"></a><a name="p585823620093534"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row2113849148093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p151516205093534"><a name="p151516205093534"></a><a name="p151516205093534"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1474999871093534"><a name="p1474999871093534"></a><a name="p1474999871093534"></a> </p>
<p id="p1851989793093534"><a name="p1851989793093534"></a><a name="p1851989793093534"></a>A default constructor used to create an <strong id="b1924731872093534"><a name="b1924731872093534"></a><a name="b1924731872093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1896495658093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1666247126093534"><a name="p1666247126093534"></a><a name="p1666247126093534"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1602644034093534"><a name="p1602644034093534"></a><a name="p1602644034093534"></a> </p>
<p id="p1813397550093534"><a name="p1813397550093534"></a><a name="p1813397550093534"></a>A constructor used to create an <strong id="b616559491093534"><a name="b616559491093534"></a><a name="b616559491093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row676555013093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1072312913093534"><a name="p1072312913093534"></a><a name="p1072312913093534"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85568605093534"><a name="p85568605093534"></a><a name="p85568605093534"></a>virtual </p>
<p id="p1684703153093534"><a name="p1684703153093534"></a><a name="p1684703153093534"></a>A destructor used to delete the <strong id="b1297852067093534"><a name="b1297852067093534"></a><a name="b1297852067093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1814757382093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1720599763093534"><a name="p1720599763093534"></a><a name="p1720599763093534"></a><a href="graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327728495093534"><a name="p1327728495093534"></a><a name="p1327728495093534"></a>virtual bool </p>
<p id="p827857232093534"><a name="p827857232093534"></a><a name="p827857232093534"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row2048665695093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p622834740093534"><a name="p622834740093534"></a><a name="p622834740093534"></a><a href="graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p408817848093534"><a name="p408817848093534"></a><a name="p408817848093534"></a>virtual void </p>
<p id="p438468974093534"><a name="p438468974093534"></a><a name="p438468974093534"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1696124859093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p828200708093534"><a name="p828200708093534"></a><a name="p828200708093534"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1712891208093534"><a name="p1712891208093534"></a><a name="p1712891208093534"></a>virtual void </p>
<p id="p427695615093534"><a name="p427695615093534"></a><a name="p427695615093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1832657112093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1250161955093534"><a name="p1250161955093534"></a><a name="p1250161955093534"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1879777678093534"><a name="p1879777678093534"></a><a name="p1879777678093534"></a>void </p>
<p id="p2087580632093534"><a name="p2087580632093534"></a><a name="p2087580632093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1979126914093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1337738993093534"><a name="p1337738993093534"></a><a name="p1337738993093534"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p221880721093534"><a name="p221880721093534"></a><a name="p221880721093534"></a>void </p>
<p id="p1846980538093534"><a name="p1846980538093534"></a><a name="p1846980538093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row461310505093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2038787915093534"><a name="p2038787915093534"></a><a name="p2038787915093534"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1881277441093534"><a name="p1881277441093534"></a><a name="p1881277441093534"></a>virtual bool </p>
<p id="p2111210978093534"><a name="p2111210978093534"></a><a name="p2111210978093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1362111956093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p582011707093534"><a name="p582011707093534"></a><a name="p582011707093534"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1325338983093534"><a name="p1325338983093534"></a><a name="p1325338983093534"></a>virtual bool </p>
<p id="p1973584052093534"><a name="p1973584052093534"></a><a name="p1973584052093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1776167686093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p269220502093534"><a name="p269220502093534"></a><a name="p269220502093534"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2126514683093534"><a name="p2126514683093534"></a><a name="p2126514683093534"></a>virtual void </p>
<p id="p1712099472093534"><a name="p1712099472093534"></a><a name="p1712099472093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row701368728093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1467608977093534"><a name="p1467608977093534"></a><a name="p1467608977093534"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1878677805093534"><a name="p1878677805093534"></a><a name="p1878677805093534"></a>virtual void </p>
<p id="p405956111093534"><a name="p405956111093534"></a><a name="p405956111093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row144439756093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p336776992093534"><a name="p336776992093534"></a><a name="p336776992093534"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1330566906093534"><a name="p1330566906093534"></a><a name="p1330566906093534"></a>virtual void </p>
<p id="p1199609064093534"><a name="p1199609064093534"></a><a name="p1199609064093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row1521679509093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p260139792093534"><a name="p260139792093534"></a><a name="p260139792093534"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757368046093534"><a name="p757368046093534"></a><a name="p757368046093534"></a>void </p>
<p id="p1190220067093534"><a name="p1190220067093534"></a><a name="p1190220067093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1751455707093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p568728213093534"><a name="p568728213093534"></a><a name="p568728213093534"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p768154125093534"><a name="p768154125093534"></a><a name="p768154125093534"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p21274087093534"><a name="p21274087093534"></a><a name="p21274087093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row123882169093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1926089298093534"><a name="p1926089298093534"></a><a name="p1926089298093534"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1034862697093534"><a name="p1034862697093534"></a><a name="p1034862697093534"></a>void </p>
<p id="p1428816997093534"><a name="p1428816997093534"></a><a name="p1428816997093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1319276804093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p919999028093534"><a name="p919999028093534"></a><a name="p919999028093534"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1004645732093534"><a name="p1004645732093534"></a><a name="p1004645732093534"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p1252879081093534"><a name="p1252879081093534"></a><a name="p1252879081093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row470253482093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1536580489093534"><a name="p1536580489093534"></a><a name="p1536580489093534"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1751175711093534"><a name="p1751175711093534"></a><a name="p1751175711093534"></a>void </p>
<p id="p401146304093534"><a name="p401146304093534"></a><a name="p401146304093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1667588908093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p720910917093534"><a name="p720910917093534"></a><a name="p720910917093534"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1615907617093534"><a name="p1615907617093534"></a><a name="p1615907617093534"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p257466313093534"><a name="p257466313093534"></a><a name="p257466313093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row400259868093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p911474655093534"><a name="p911474655093534"></a><a name="p911474655093534"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1672488812093534"><a name="p1672488812093534"></a><a name="p1672488812093534"></a>void </p>
<p id="p58437578093534"><a name="p58437578093534"></a><a name="p58437578093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row600546896093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413173027093534"><a name="p1413173027093534"></a><a name="p1413173027093534"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985293930093534"><a name="p985293930093534"></a><a name="p985293930093534"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1306411962093534"><a name="p1306411962093534"></a><a name="p1306411962093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row561076661093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973179902093534"><a name="p973179902093534"></a><a name="p973179902093534"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p107458811093534"><a name="p107458811093534"></a><a name="p107458811093534"></a>void </p>
<p id="p847789402093534"><a name="p847789402093534"></a><a name="p847789402093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row875047059093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p188739479093534"><a name="p188739479093534"></a><a name="p188739479093534"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p8121231093534"><a name="p8121231093534"></a><a name="p8121231093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1002156847093534"><a name="p1002156847093534"></a><a name="p1002156847093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row729760291093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p827943331093534"><a name="p827943331093534"></a><a name="p827943331093534"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p139915949093534"><a name="p139915949093534"></a><a name="p139915949093534"></a>void </p>
<p id="p1294140270093534"><a name="p1294140270093534"></a><a name="p1294140270093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row763571577093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1487193934093534"><a name="p1487193934093534"></a><a name="p1487193934093534"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p412389712093534"><a name="p412389712093534"></a><a name="p412389712093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p767190195093534"><a name="p767190195093534"></a><a name="p767190195093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1852801697093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1116392606093534"><a name="p1116392606093534"></a><a name="p1116392606093534"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p330154254093534"><a name="p330154254093534"></a><a name="p330154254093534"></a>virtual void </p>
<p id="p894627741093534"><a name="p894627741093534"></a><a name="p894627741093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row44989396093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p599426659093534"><a name="p599426659093534"></a><a name="p599426659093534"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p319531333093534"><a name="p319531333093534"></a><a name="p319531333093534"></a>bool </p>
<p id="p1136785801093534"><a name="p1136785801093534"></a><a name="p1136785801093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1756250205093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1784787993093534"><a name="p1784787993093534"></a><a name="p1784787993093534"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491003413093534"><a name="p491003413093534"></a><a name="p491003413093534"></a>void </p>
<p id="p818722307093534"><a name="p818722307093534"></a><a name="p818722307093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1579712685093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p789457131093534"><a name="p789457131093534"></a><a name="p789457131093534"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p415154300093534"><a name="p415154300093534"></a><a name="p415154300093534"></a>bool </p>
<p id="p175064369093534"><a name="p175064369093534"></a><a name="p175064369093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1817238063093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2013428089093534"><a name="p2013428089093534"></a><a name="p2013428089093534"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p716610735093534"><a name="p716610735093534"></a><a name="p716610735093534"></a>void </p>
<p id="p1060228779093534"><a name="p1060228779093534"></a><a name="p1060228779093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row465495046093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p6175478093534"><a name="p6175478093534"></a><a name="p6175478093534"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p530708314093534"><a name="p530708314093534"></a><a name="p530708314093534"></a>bool </p>
<p id="p1737203819093534"><a name="p1737203819093534"></a><a name="p1737203819093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row856956020093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p495080055093534"><a name="p495080055093534"></a><a name="p495080055093534"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p519435183093534"><a name="p519435183093534"></a><a name="p519435183093534"></a>void </p>
<p id="p161556039093534"><a name="p161556039093534"></a><a name="p161556039093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row90562883093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1843915207093534"><a name="p1843915207093534"></a><a name="p1843915207093534"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902886257093534"><a name="p1902886257093534"></a><a name="p1902886257093534"></a>bool </p>
<p id="p637343419093534"><a name="p637343419093534"></a><a name="p637343419093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row745110798093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p999890883093534"><a name="p999890883093534"></a><a name="p999890883093534"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p15548292093534"><a name="p15548292093534"></a><a name="p15548292093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p2037205382093534"><a name="p2037205382093534"></a><a name="p2037205382093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row184448757093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p600521064093534"><a name="p600521064093534"></a><a name="p600521064093534"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1615546675093534"><a name="p1615546675093534"></a><a name="p1615546675093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p261276578093534"><a name="p261276578093534"></a><a name="p261276578093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1825690150093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p280961459093534"><a name="p280961459093534"></a><a name="p280961459093534"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1458369053093534"><a name="p1458369053093534"></a><a name="p1458369053093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p58344373093534"><a name="p58344373093534"></a><a name="p58344373093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1358527457093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p183258428093534"><a name="p183258428093534"></a><a name="p183258428093534"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p922108823093534"><a name="p922108823093534"></a><a name="p922108823093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p172884146093534"><a name="p172884146093534"></a><a name="p172884146093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row217464374093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2020148235093534"><a name="p2020148235093534"></a><a name="p2020148235093534"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1438558375093534"><a name="p1438558375093534"></a><a name="p1438558375093534"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1925932910093534"><a name="p1925932910093534"></a><a name="p1925932910093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row90341451093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1067451434093534"><a name="p1067451434093534"></a><a name="p1067451434093534"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1689788478093534"><a name="p1689788478093534"></a><a name="p1689788478093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1906356429093534"><a name="p1906356429093534"></a><a name="p1906356429093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row196711495093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1308110535093534"><a name="p1308110535093534"></a><a name="p1308110535093534"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p263394751093534"><a name="p263394751093534"></a><a name="p263394751093534"></a>void </p>
<p id="p867106604093534"><a name="p867106604093534"></a><a name="p867106604093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1101893752093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p224023478093534"><a name="p224023478093534"></a><a name="p224023478093534"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452830096093534"><a name="p1452830096093534"></a><a name="p1452830096093534"></a>virtual void </p>
<p id="p1051606530093534"><a name="p1051606530093534"></a><a name="p1051606530093534"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row841729574093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p892338924093534"><a name="p892338924093534"></a><a name="p892338924093534"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p451652091093534"><a name="p451652091093534"></a><a name="p451652091093534"></a>virtual int16_t </p>
<p id="p191419238093534"><a name="p191419238093534"></a><a name="p191419238093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1461848111093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p636457534093534"><a name="p636457534093534"></a><a name="p636457534093534"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p309353136093534"><a name="p309353136093534"></a><a name="p309353136093534"></a>virtual void </p>
<p id="p867719669093534"><a name="p867719669093534"></a><a name="p867719669093534"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1475182093093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p608455797093534"><a name="p608455797093534"></a><a name="p608455797093534"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1077000430093534"><a name="p1077000430093534"></a><a name="p1077000430093534"></a>virtual int16_t </p>
<p id="p959602727093534"><a name="p959602727093534"></a><a name="p959602727093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row736926417093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p407709713093534"><a name="p407709713093534"></a><a name="p407709713093534"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p768596391093534"><a name="p768596391093534"></a><a name="p768596391093534"></a>virtual void </p>
<p id="p1435799390093534"><a name="p1435799390093534"></a><a name="p1435799390093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1278894686093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p588829071093534"><a name="p588829071093534"></a><a name="p588829071093534"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p775930109093534"><a name="p775930109093534"></a><a name="p775930109093534"></a>virtual void </p>
<p id="p25234262093534"><a name="p25234262093534"></a><a name="p25234262093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1819391649093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1707393695093534"><a name="p1707393695093534"></a><a name="p1707393695093534"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1635951402093534"><a name="p1635951402093534"></a><a name="p1635951402093534"></a>int16_t </p>
<p id="p984279268093534"><a name="p984279268093534"></a><a name="p984279268093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row223819583093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p930686801093534"><a name="p930686801093534"></a><a name="p930686801093534"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041372166093534"><a name="p1041372166093534"></a><a name="p1041372166093534"></a>virtual void </p>
<p id="p1027768349093534"><a name="p1027768349093534"></a><a name="p1027768349093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row251184810093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1064304527093534"><a name="p1064304527093534"></a><a name="p1064304527093534"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1391241567093534"><a name="p1391241567093534"></a><a name="p1391241567093534"></a>int16_t </p>
<p id="p261649024093534"><a name="p261649024093534"></a><a name="p261649024093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row143319137093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p155748269093534"><a name="p155748269093534"></a><a name="p155748269093534"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p399066192093534"><a name="p399066192093534"></a><a name="p399066192093534"></a>virtual void </p>
<p id="p971037490093534"><a name="p971037490093534"></a><a name="p971037490093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1181071459093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1925862768093534"><a name="p1925862768093534"></a><a name="p1925862768093534"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p892878857093534"><a name="p892878857093534"></a><a name="p892878857093534"></a>virtual void </p>
<p id="p890202063093534"><a name="p890202063093534"></a><a name="p890202063093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1260049190093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1724490405093534"><a name="p1724490405093534"></a><a name="p1724490405093534"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2084378879093534"><a name="p2084378879093534"></a><a name="p2084378879093534"></a>bool </p>
<p id="p1874902777093534"><a name="p1874902777093534"></a><a name="p1874902777093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row887903623093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1731836066093534"><a name="p1731836066093534"></a><a name="p1731836066093534"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2042551624093534"><a name="p2042551624093534"></a><a name="p2042551624093534"></a>void </p>
<p id="p97017060093534"><a name="p97017060093534"></a><a name="p97017060093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1942527761093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1982772076093534"><a name="p1982772076093534"></a><a name="p1982772076093534"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p165407716093534"><a name="p165407716093534"></a><a name="p165407716093534"></a>void </p>
<p id="p425370828093534"><a name="p425370828093534"></a><a name="p425370828093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1528294824093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p472489383093534"><a name="p472489383093534"></a><a name="p472489383093534"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p19772492093534"><a name="p19772492093534"></a><a name="p19772492093534"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p101006171093534"><a name="p101006171093534"></a><a name="p101006171093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1883040742093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1108569374093534"><a name="p1108569374093534"></a><a name="p1108569374093534"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1155255128093534"><a name="p1155255128093534"></a><a name="p1155255128093534"></a>void </p>
<p id="p319261834093534"><a name="p319261834093534"></a><a name="p319261834093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1334415890093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p794331988093534"><a name="p794331988093534"></a><a name="p794331988093534"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p222693748093534"><a name="p222693748093534"></a><a name="p222693748093534"></a>const char * </p>
<p id="p78825061093534"><a name="p78825061093534"></a><a name="p78825061093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1870502721093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p561776791093534"><a name="p561776791093534"></a><a name="p561776791093534"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1057696788093534"><a name="p1057696788093534"></a><a name="p1057696788093534"></a>void </p>
<p id="p117432472093534"><a name="p117432472093534"></a><a name="p117432472093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row836456411093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p457047492093534"><a name="p457047492093534"></a><a name="p457047492093534"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1723630646093534"><a name="p1723630646093534"></a><a name="p1723630646093534"></a>int16_t </p>
<p id="p1359877891093534"><a name="p1359877891093534"></a><a name="p1359877891093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row699538199093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p331494771093534"><a name="p331494771093534"></a><a name="p331494771093534"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p827713660093534"><a name="p827713660093534"></a><a name="p827713660093534"></a>virtual void </p>
<p id="p2052612449093534"><a name="p2052612449093534"></a><a name="p2052612449093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row364335949093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p454483961093534"><a name="p454483961093534"></a><a name="p454483961093534"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p379715994093534"><a name="p379715994093534"></a><a name="p379715994093534"></a>void </p>
<p id="p1949621691093534"><a name="p1949621691093534"></a><a name="p1949621691093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row507324931093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p957367318093534"><a name="p957367318093534"></a><a name="p957367318093534"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1411693685093534"><a name="p1411693685093534"></a><a name="p1411693685093534"></a>void </p>
<p id="p1958370704093534"><a name="p1958370704093534"></a><a name="p1958370704093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1106206510093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1797894933093534"><a name="p1797894933093534"></a><a name="p1797894933093534"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1769417101093534"><a name="p1769417101093534"></a><a name="p1769417101093534"></a>void </p>
<p id="p2053173679093534"><a name="p2053173679093534"></a><a name="p2053173679093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row394887896093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p96646074093534"><a name="p96646074093534"></a><a name="p96646074093534"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p439030634093534"><a name="p439030634093534"></a><a name="p439030634093534"></a>void </p>
<p id="p923217672093534"><a name="p923217672093534"></a><a name="p923217672093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row643201037093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p105236703093534"><a name="p105236703093534"></a><a name="p105236703093534"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1911181062093534"><a name="p1911181062093534"></a><a name="p1911181062093534"></a>void </p>
<p id="p1635393702093534"><a name="p1635393702093534"></a><a name="p1635393702093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row244747206093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p535571810093534"><a name="p535571810093534"></a><a name="p535571810093534"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1482022918093534"><a name="p1482022918093534"></a><a name="p1482022918093534"></a>void </p>
<p id="p392774123093534"><a name="p392774123093534"></a><a name="p392774123093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row353690080093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1496148011093534"><a name="p1496148011093534"></a><a name="p1496148011093534"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069633230093534"><a name="p2069633230093534"></a><a name="p2069633230093534"></a>void </p>
<p id="p143775148093534"><a name="p143775148093534"></a><a name="p143775148093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row446384349093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p145737677093534"><a name="p145737677093534"></a><a name="p145737677093534"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p231933853093534"><a name="p231933853093534"></a><a name="p231933853093534"></a>void </p>
<p id="p1643719946093534"><a name="p1643719946093534"></a><a name="p1643719946093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1066981050093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2071806380093534"><a name="p2071806380093534"></a><a name="p2071806380093534"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687827416093534"><a name="p1687827416093534"></a><a name="p1687827416093534"></a>void </p>
<p id="p1813243745093534"><a name="p1813243745093534"></a><a name="p1813243745093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row798803891093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1125315136093534"><a name="p1125315136093534"></a><a name="p1125315136093534"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1957147783093534"><a name="p1957147783093534"></a><a name="p1957147783093534"></a>void </p>
<p id="p2140770223093534"><a name="p2140770223093534"></a><a name="p2140770223093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1679656311093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p3786890093534"><a name="p3786890093534"></a><a name="p3786890093534"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763594493093534"><a name="p763594493093534"></a><a name="p763594493093534"></a>void </p>
<p id="p1503177845093534"><a name="p1503177845093534"></a><a name="p1503177845093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row248561149093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1094190986093534"><a name="p1094190986093534"></a><a name="p1094190986093534"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1150835910093534"><a name="p1150835910093534"></a><a name="p1150835910093534"></a>void </p>
<p id="p1594600292093534"><a name="p1594600292093534"></a><a name="p1594600292093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row2021888835093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p338267914093534"><a name="p338267914093534"></a><a name="p338267914093534"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2105909806093534"><a name="p2105909806093534"></a><a name="p2105909806093534"></a>void </p>
<p id="p130997095093534"><a name="p130997095093534"></a><a name="p130997095093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row177672200093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p116310435093534"><a name="p116310435093534"></a><a name="p116310435093534"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1720174353093534"><a name="p1720174353093534"></a><a name="p1720174353093534"></a>void </p>
<p id="p1447799763093534"><a name="p1447799763093534"></a><a name="p1447799763093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row194639291093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p395668482093534"><a name="p395668482093534"></a><a name="p395668482093534"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p464984918093534"><a name="p464984918093534"></a><a name="p464984918093534"></a>void </p>
<p id="p1765684493093534"><a name="p1765684493093534"></a><a name="p1765684493093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row500037450093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1916733637093534"><a name="p1916733637093534"></a><a name="p1916733637093534"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1263036058093534"><a name="p1263036058093534"></a><a name="p1263036058093534"></a>virtual void </p>
<p id="p896978332093534"><a name="p896978332093534"></a><a name="p896978332093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1398295180093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494130478093534"><a name="p1494130478093534"></a><a name="p1494130478093534"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1165646708093534"><a name="p1165646708093534"></a><a name="p1165646708093534"></a>virtual void </p>
<p id="p1357046457093534"><a name="p1357046457093534"></a><a name="p1357046457093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row790352835093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1279731900093534"><a name="p1279731900093534"></a><a name="p1279731900093534"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432283185093534"><a name="p1432283185093534"></a><a name="p1432283185093534"></a>virtual int64_t </p>
<p id="p1755465736093534"><a name="p1755465736093534"></a><a name="p1755465736093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row309259600093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p500572831093534"><a name="p500572831093534"></a><a name="p500572831093534"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343771989093534"><a name="p343771989093534"></a><a name="p343771989093534"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p1957925139093534"><a name="p1957925139093534"></a><a name="p1957925139093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1545585048093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1581111828093534"><a name="p1581111828093534"></a><a name="p1581111828093534"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p889457588093534"><a name="p889457588093534"></a><a name="p889457588093534"></a>void * </p>
<p id="p990752762093534"><a name="p990752762093534"></a><a name="p990752762093534"></a>Overrides the <strong id="b962831172093534"><a name="b962831172093534"></a><a name="b962831172093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row900837400093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1956037605093534"><a name="p1956037605093534"></a><a name="p1956037605093534"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p861104157093534"><a name="p861104157093534"></a><a name="p861104157093534"></a>void </p>
<p id="p616306030093534"><a name="p616306030093534"></a><a name="p616306030093534"></a>Overrides the <strong id="b765168509093534"><a name="b765168509093534"></a><a name="b765168509093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1372175373093534"></a>
<table><thead align="left"><tr id="row1928587420093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p730490706093534"><a name="p730490706093534"></a><a name="p730490706093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1205606813093534"><a name="p1205606813093534"></a><a name="p1205606813093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row128784678093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1034223665093534"><a name="p1034223665093534"></a><a name="p1034223665093534"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703384485093534"><a name="p1703384485093534"></a><a name="p1703384485093534"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1345104489093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1501197699093534"><a name="p1501197699093534"></a><a name="p1501197699093534"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1542861288093534"><a name="p1542861288093534"></a><a name="p1542861288093534"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row974838576093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1437032631093534"><a name="p1437032631093534"></a><a name="p1437032631093534"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1425559341093534"><a name="p1425559341093534"></a><a name="p1425559341093534"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row1146022913093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1239838698093534"><a name="p1239838698093534"></a><a name="p1239838698093534"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p683989618093534"><a name="p683989618093534"></a><a name="p683989618093534"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1977860126093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p302214804093534"><a name="p302214804093534"></a><a name="p302214804093534"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868983641093534"><a name="p1868983641093534"></a><a name="p1868983641093534"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1117444551093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1052009004093534"><a name="p1052009004093534"></a><a name="p1052009004093534"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572148257093534"><a name="p572148257093534"></a><a name="p572148257093534"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row856534998093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1810621559093534"><a name="p1810621559093534"></a><a name="p1810621559093534"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1320275531093534"><a name="p1320275531093534"></a><a name="p1320275531093534"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

