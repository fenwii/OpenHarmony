# OHOS::Rect<a name="EN-US_TOPIC_0000001055518102"></a>

## **Overview**<a name="section1388445414093532"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a rectangle, including the position data of the four boundaries of the rectangle, and provides functions for rectangle inclusion, intersection, and aggregation. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1632127107093532"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table556973468093532"></a>
<table><thead align="left"><tr id="row538686117093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1551360688093532"><a name="p1551360688093532"></a><a name="p1551360688093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p485600741093532"><a name="p485600741093532"></a><a name="p485600741093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row438954736093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1910046974093532"><a name="p1910046974093532"></a><a name="p1910046974093532"></a><a href="graphic.md#ga7d3779a5cf121ba98026ddbf36705178">Rect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p623026953093532"><a name="p623026953093532"></a><a name="p623026953093532"></a> </p>
<p id="p2130396871093532"><a name="p2130396871093532"></a><a name="p2130396871093532"></a>A constructor used to create a <strong id="b1652060823093532"><a name="b1652060823093532"></a><a name="b1652060823093532"></a><a href="ohos-rect.md">Rect</a></strong> instance. </p>
</td>
</tr>
<tr id="row1833963178093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p73576100093532"><a name="p73576100093532"></a><a name="p73576100093532"></a><a href="graphic.md#ga3729aa7a7f052d182bd20707097f9db9">~Rect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1592664279093532"><a name="p1592664279093532"></a><a name="p1592664279093532"></a> </p>
<p id="p1689026535093532"><a name="p1689026535093532"></a><a name="p1689026535093532"></a>A destructor used to delete the <strong id="b1376716128093532"><a name="b1376716128093532"></a><a name="b1376716128093532"></a><a href="ohos-rect.md">Rect</a></strong> instance. </p>
</td>
</tr>
<tr id="row931530836093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p276082686093532"><a name="p276082686093532"></a><a name="p276082686093532"></a><a href="graphic.md#gab37a12fb10478edcb5389fa0b347c46f">Rect</a> (int16_t left, int16_t top, int16_t right, int16_t bottom)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p735756379093532"><a name="p735756379093532"></a><a name="p735756379093532"></a> </p>
<p id="p134416644093532"><a name="p134416644093532"></a><a name="p134416644093532"></a>A constructor used to create a <strong id="b1742974231093532"><a name="b1742974231093532"></a><a name="b1742974231093532"></a><a href="ohos-rect.md">Rect</a></strong> instance based on the coordinates of the four boundaries. </p>
</td>
</tr>
<tr id="row182294007093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1100348541093532"><a name="p1100348541093532"></a><a name="p1100348541093532"></a><a href="graphic.md#ga766eee89dbd7d4969fb88485893ea662">Rect</a> (const <a href="ohos-rect.md">Rect</a> &amp;other)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1087775415093532"><a name="p1087775415093532"></a><a name="p1087775415093532"></a> </p>
<p id="p1860199296093532"><a name="p1860199296093532"></a><a name="p1860199296093532"></a>A constructor used to create a <strong id="b1676235542093532"><a name="b1676235542093532"></a><a name="b1676235542093532"></a><a href="ohos-rect.md">Rect</a></strong> instance by copying another rectangle. </p>
</td>
</tr>
<tr id="row774830204093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1325503573093532"><a name="p1325503573093532"></a><a name="p1325503573093532"></a><a href="graphic.md#gabcc74bf916f06152b4a69e1a36116e3f">Rect</a> (const <a href="ohos-rect.md">Rect</a> &amp;&amp;other)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1394477520093532"><a name="p1394477520093532"></a><a name="p1394477520093532"></a> </p>
<p id="p278799576093532"><a name="p278799576093532"></a><a name="p278799576093532"></a>A constructor used to create a <strong id="b143982451093532"><a name="b143982451093532"></a><a name="b143982451093532"></a><a href="ohos-rect.md">Rect</a></strong> instance by copying another rectangle. </p>
</td>
</tr>
<tr id="row95039679093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778086776093532"><a name="p778086776093532"></a><a name="p778086776093532"></a><a href="graphic.md#ga4423fe83ed9271d1186711dff65796cb">SetRect</a> (int16_t left, int16_t top, int16_t right, int16_t bottom)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p546408034093532"><a name="p546408034093532"></a><a name="p546408034093532"></a>void </p>
<p id="p1232350013093532"><a name="p1232350013093532"></a><a name="p1232350013093532"></a>Sets the coordinates of the four boundaries of a rectangle. </p>
</td>
</tr>
<tr id="row176946725093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1891409041093532"><a name="p1891409041093532"></a><a name="p1891409041093532"></a><a href="graphic.md#ga2f8315ea6e574aec99210950feef1b55">GetWidth</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p524138738093532"><a name="p524138738093532"></a><a name="p524138738093532"></a>int16_t </p>
<p id="p1148342540093532"><a name="p1148342540093532"></a><a name="p1148342540093532"></a>Obtains the rectangle width. </p>
</td>
</tr>
<tr id="row1186181906093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p235506170093532"><a name="p235506170093532"></a><a name="p235506170093532"></a><a href="graphic.md#ga9a1b7ee8eee0d5fa96739fd0a0bac638">GetHeight</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1460123248093532"><a name="p1460123248093532"></a><a name="p1460123248093532"></a>int16_t </p>
<p id="p1758461133093532"><a name="p1758461133093532"></a><a name="p1758461133093532"></a>Obtains the rectangle height. </p>
</td>
</tr>
<tr id="row1502362213093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p387732963093532"><a name="p387732963093532"></a><a name="p387732963093532"></a><a href="graphic.md#gad0410528e93dcf552129e207dfe37aba">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p247311922093532"><a name="p247311922093532"></a><a name="p247311922093532"></a>int16_t </p>
<p id="p506270964093532"><a name="p506270964093532"></a><a name="p506270964093532"></a>Obtains the left boundary coordinate of the rectangle. </p>
</td>
</tr>
<tr id="row1211421426093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1936551673093532"><a name="p1936551673093532"></a><a name="p1936551673093532"></a><a href="graphic.md#gaa3b94d5228cabba6341039e8f28fda74">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p960659599093532"><a name="p960659599093532"></a><a name="p960659599093532"></a>int16_t </p>
<p id="p1174460819093532"><a name="p1174460819093532"></a><a name="p1174460819093532"></a>Obtains the top boundary coordinate of the rectangle. </p>
</td>
</tr>
<tr id="row1507805411093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p715257261093532"><a name="p715257261093532"></a><a name="p715257261093532"></a><a href="graphic.md#ga2f4bd954929225e2f124db4c9d2c62ec">GetLeft</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p876451370093532"><a name="p876451370093532"></a><a name="p876451370093532"></a>int16_t </p>
<p id="p482785778093532"><a name="p482785778093532"></a><a name="p482785778093532"></a>Obtains the left boundary coordinate of the rectangle. </p>
</td>
</tr>
<tr id="row841865013093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1181690286093532"><a name="p1181690286093532"></a><a name="p1181690286093532"></a><a href="graphic.md#ga9ab9c7eda50b517e55d608270360f0a0">GetTop</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1393360379093532"><a name="p1393360379093532"></a><a name="p1393360379093532"></a>int16_t </p>
<p id="p541125043093532"><a name="p541125043093532"></a><a name="p541125043093532"></a>Obtains the top boundary coordinate of the rectangle. </p>
</td>
</tr>
<tr id="row1864296400093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1743648937093532"><a name="p1743648937093532"></a><a name="p1743648937093532"></a><a href="graphic.md#gab7695173ebb2f4b8e9aa58947786a379">GetRight</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1207694638093532"><a name="p1207694638093532"></a><a name="p1207694638093532"></a>int16_t </p>
<p id="p2054429345093532"><a name="p2054429345093532"></a><a name="p2054429345093532"></a>Obtains the right boundary coordinate of the rectangle. </p>
</td>
</tr>
<tr id="row1471713951093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p825521572093532"><a name="p825521572093532"></a><a name="p825521572093532"></a><a href="graphic.md#ga6c2f9cf035a36c605e20ccc76de8fbea">GetBottom</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137567932093532"><a name="p2137567932093532"></a><a name="p2137567932093532"></a>int16_t </p>
<p id="p1676998540093532"><a name="p1676998540093532"></a><a name="p1676998540093532"></a>Obtains the bottom boundary coordinate of the rectangle. </p>
</td>
</tr>
<tr id="row1732778902093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p466363877093532"><a name="p466363877093532"></a><a name="p466363877093532"></a><a href="graphic.md#ga6d14ede131d4a9445e0890632d2e4370">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1827494791093532"><a name="p1827494791093532"></a><a name="p1827494791093532"></a>void </p>
<p id="p888379999093532"><a name="p888379999093532"></a><a name="p888379999093532"></a>Changes the left boundary coordinate of the rectangle without changing the rectangle width. </p>
</td>
</tr>
<tr id="row868229430093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1566510560093532"><a name="p1566510560093532"></a><a name="p1566510560093532"></a><a href="graphic.md#ga260393d7b4c514eebc2a28187ec6f8b4">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985180775093532"><a name="p985180775093532"></a><a name="p985180775093532"></a>void </p>
<p id="p1752532566093532"><a name="p1752532566093532"></a><a name="p1752532566093532"></a>Changes the top boundary coordinate of the rectangle without changing the rectangle height. </p>
</td>
</tr>
<tr id="row405837192093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p333686574093532"><a name="p333686574093532"></a><a name="p333686574093532"></a><a href="graphic.md#ga723d2b5ace818a6b71e0570339689690">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1579544357093532"><a name="p1579544357093532"></a><a name="p1579544357093532"></a>void </p>
<p id="p696684943093532"><a name="p696684943093532"></a><a name="p696684943093532"></a>Changes the coordinates of the left and top boundaries of the rectangle without changing the rectangle width and height. </p>
</td>
</tr>
<tr id="row1361228679093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1657146253093532"><a name="p1657146253093532"></a><a name="p1657146253093532"></a><a href="graphic.md#ga8a31c03ecb4a452d79374b392537f183">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2033646277093532"><a name="p2033646277093532"></a><a name="p2033646277093532"></a>void </p>
<p id="p1096764553093532"><a name="p1096764553093532"></a><a name="p1096764553093532"></a>Changes the width of the rectangle without changing the coordinate of the left boundary. </p>
</td>
</tr>
<tr id="row328717210093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1199602199093532"><a name="p1199602199093532"></a><a name="p1199602199093532"></a><a href="graphic.md#ga8e3fab1e0d6cd4671c6628b94c493d0f">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1109335266093532"><a name="p1109335266093532"></a><a name="p1109335266093532"></a>void </p>
<p id="p1251315934093532"><a name="p1251315934093532"></a><a name="p1251315934093532"></a>Changes the height of the rectangle without changing the coordinate of the top boundary. </p>
</td>
</tr>
<tr id="row90853163093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1533658593093532"><a name="p1533658593093532"></a><a name="p1533658593093532"></a><a href="graphic.md#ga043a1c4f0aaf4eed2ddf99083ed993bb">SetLeft</a> (int16_t left)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1274073924093532"><a name="p1274073924093532"></a><a name="p1274073924093532"></a>void </p>
<p id="p1298061310093532"><a name="p1298061310093532"></a><a name="p1298061310093532"></a>Sets the coordinate of the left boundary of a rectangle. </p>
</td>
</tr>
<tr id="row138379359093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408059730093532"><a name="p1408059730093532"></a><a name="p1408059730093532"></a><a href="graphic.md#gae7c63105b7e1871f231a1a8dfad48de7">SetTop</a> (int16_t top)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1239889921093532"><a name="p1239889921093532"></a><a name="p1239889921093532"></a>void </p>
<p id="p588738659093532"><a name="p588738659093532"></a><a name="p588738659093532"></a>Sets the coordinate of the top boundary of a rectangle. </p>
</td>
</tr>
<tr id="row1263779109093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p888567847093532"><a name="p888567847093532"></a><a name="p888567847093532"></a><a href="graphic.md#ga314f4443ef95351a80e6edaaeff11674">SetRight</a> (int16_t right)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p363321690093532"><a name="p363321690093532"></a><a name="p363321690093532"></a>void </p>
<p id="p312608395093532"><a name="p312608395093532"></a><a name="p312608395093532"></a>Sets the coordinate of the right boundary of a rectangle. </p>
</td>
</tr>
<tr id="row454391226093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1823970242093532"><a name="p1823970242093532"></a><a name="p1823970242093532"></a><a href="graphic.md#ga764001fa9f51716fd3dacac691cbca6d">SetBottom</a> (int16_t bottom)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p195181168093532"><a name="p195181168093532"></a><a name="p195181168093532"></a>void </p>
<p id="p1964058437093532"><a name="p1964058437093532"></a><a name="p1964058437093532"></a>Sets the coordinate of the bottom boundary of a rectangle. </p>
</td>
</tr>
<tr id="row669708971093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119553297093532"><a name="p1119553297093532"></a><a name="p1119553297093532"></a><a href="graphic.md#ga6d51096b1d1b1929d8ee6a0d25c153d8">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2000723225093532"><a name="p2000723225093532"></a><a name="p2000723225093532"></a>void </p>
<p id="p374620981093532"><a name="p374620981093532"></a><a name="p374620981093532"></a>Sets the width and height of a rectangle. </p>
</td>
</tr>
<tr id="row1821107214093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p541049472093532"><a name="p541049472093532"></a><a name="p541049472093532"></a><a href="graphic.md#ga37f61dc21e0acc2ae877687f06d11e50">GetSize</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1650863044093532"><a name="p1650863044093532"></a><a name="p1650863044093532"></a>uint32_t </p>
<p id="p2014823414093532"><a name="p2014823414093532"></a><a name="p2014823414093532"></a>Obtains the area of a rectangle. </p>
</td>
</tr>
<tr id="row632834352093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1462462191093532"><a name="p1462462191093532"></a><a name="p1462462191093532"></a><a href="graphic.md#ga1af82c2a558d4003d5d3b19302325a73">Intersect</a> (const <a href="ohos-rect.md">Rect</a> &amp;rect1, const <a href="ohos-rect.md">Rect</a> &amp;rect2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p453738292093532"><a name="p453738292093532"></a><a name="p453738292093532"></a>bool </p>
<p id="p13733701093532"><a name="p13733701093532"></a><a name="p13733701093532"></a>Checks whether two rectangles intersect. </p>
</td>
</tr>
<tr id="row1821463193093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p105843162093532"><a name="p105843162093532"></a><a name="p105843162093532"></a><a href="graphic.md#ga6269289055eab8876cc3b3c946ddd4a4">Join</a> (const <a href="ohos-rect.md">Rect</a> &amp;rect1, const <a href="ohos-rect.md">Rect</a> &amp;rect2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p775128817093532"><a name="p775128817093532"></a><a name="p775128817093532"></a>void </p>
<p id="p515019681093532"><a name="p515019681093532"></a><a name="p515019681093532"></a>Obtains the minimum rectangle that contains another two rectangles. </p>
</td>
</tr>
<tr id="row1039932591093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1809910992093532"><a name="p1809910992093532"></a><a name="p1809910992093532"></a><a href="graphic.md#ga1a810eb98134027556294620821c2548">IsContains</a> (const <a href="ohos-vector2-t.md">Vector2</a>&lt; int16_t &gt; &amp;point) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1512192964093532"><a name="p1512192964093532"></a><a name="p1512192964093532"></a>bool </p>
<p id="p799769264093532"><a name="p799769264093532"></a><a name="p799769264093532"></a>Checks whether the rectangle contains a coordinate point. </p>
</td>
</tr>
<tr id="row1931371556093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1700967901093532"><a name="p1700967901093532"></a><a name="p1700967901093532"></a><a href="graphic.md#ga5f3cb137429e00b2e7fe1e39f7e9faad">IsContains</a> (const <a href="ohos-point.md">Point</a> &amp;point) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p415941482093532"><a name="p415941482093532"></a><a name="p415941482093532"></a>bool </p>
<p id="p1319204071093532"><a name="p1319204071093532"></a><a name="p1319204071093532"></a>Checks whether the rectangle contains a coordinate point. </p>
</td>
</tr>
<tr id="row787002010093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1272638247093532"><a name="p1272638247093532"></a><a name="p1272638247093532"></a><a href="graphic.md#ga808a2b486872f5d1dc1f3e944352bcfb">IsExtends</a> (const <a href="ohos-rect.md">Rect</a> &amp;other) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052639736093532"><a name="p1052639736093532"></a><a name="p1052639736093532"></a>bool </p>
<p id="p352251293093532"><a name="p352251293093532"></a><a name="p352251293093532"></a>Checks whether the rectangle is adjacent to another rectangle horizontally or vertically. </p>
</td>
</tr>
<tr id="row1810583246093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087860603093532"><a name="p2087860603093532"></a><a name="p2087860603093532"></a><a href="graphic.md#gacc346d49f3a8ee42662d34140afcbc9e">IsIntersect</a> (const <a href="ohos-rect.md">Rect</a> &amp;other) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041250520093532"><a name="p1041250520093532"></a><a name="p1041250520093532"></a>bool </p>
<p id="p1451694579093532"><a name="p1451694579093532"></a><a name="p1451694579093532"></a>Checks whether the rectangle intersects with another rectangle. </p>
</td>
</tr>
<tr id="row481356361093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1474600168093532"><a name="p1474600168093532"></a><a name="p1474600168093532"></a><a href="graphic.md#ga3e17c74e6eaf3b01b5e009db582da498">IsContains</a> (const <a href="ohos-rect.md">Rect</a> &amp;other) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041733434093532"><a name="p1041733434093532"></a><a name="p1041733434093532"></a>bool </p>
<p id="p414332026093532"><a name="p414332026093532"></a><a name="p414332026093532"></a>Checks whether the rectangle contains another rectangle. </p>
</td>
</tr>
<tr id="row804465160093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1029901554093532"><a name="p1029901554093532"></a><a name="p1029901554093532"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p853179418093532"><a name="p853179418093532"></a><a name="p853179418093532"></a>void * </p>
<p id="p576802825093532"><a name="p576802825093532"></a><a name="p576802825093532"></a>Overrides the <strong id="b1183401655093532"><a name="b1183401655093532"></a><a name="b1183401655093532"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row59238993093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183696319093532"><a name="p1183696319093532"></a><a name="p1183696319093532"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2014724293093532"><a name="p2014724293093532"></a><a name="p2014724293093532"></a>void </p>
<p id="p2053244929093532"><a name="p2053244929093532"></a><a name="p2053244929093532"></a>Overrides the <strong id="b428978377093532"><a name="b428978377093532"></a><a name="b428978377093532"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

