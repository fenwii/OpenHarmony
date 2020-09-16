# transform.h<a name="ZH-CN_TOPIC_0000001054799581"></a>

## **Overview**<a name="section1274257094093527"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Provides functions to transform components, points, and line segments, including rotation and scaling. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section400054880093527"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table86655079093527"></a>
<table><thead align="left"><tr id="row1165137746093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p687225461093527"><a name="p687225461093527"></a><a name="p687225461093527"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p175200799093527"><a name="p175200799093527"></a><a name="p175200799093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row212084986093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1884409769093527"><a name="p1884409769093527"></a><a name="p1884409769093527"></a><a href="OHOS-TransformMap.md">OHOS::TransformMap</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1678606098093527"><a name="p1678606098093527"></a><a name="p1678606098093527"></a>Transforms a rectangle, including rotation and scaling. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table2112847979093527"></a>
<table><thead align="left"><tr id="row890542954093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1947494172093527"><a name="p1947494172093527"></a><a name="p1947494172093527"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p319202985093527"><a name="p319202985093527"></a><a name="p319202985093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row622889642093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790514658093527"><a name="p790514658093527"></a><a name="p790514658093527"></a><a href="Graphic.md#ga9bb4f3256ad01b5abdd347de1fea09ee">OHOS::Rotate</a> (const Vector2&lt; int16_t &gt; &amp;point, int16_t angle, const Vector2&lt; int16_t &gt; &amp;pivot, Vector2&lt; int16_t &gt; &amp;out)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p75873161093527"><a name="p75873161093527"></a><a name="p75873161093527"></a>void&nbsp;</p>
<p id="p952562354093527"><a name="p952562354093527"></a><a name="p952562354093527"></a>Rotates a point around the pivot by a certain angle. </p>
</td>
</tr>
<tr id="row586374583093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1619110916093527"><a name="p1619110916093527"></a><a name="p1619110916093527"></a><a href="Graphic.md#gac57d591450b239f8e375f4c7b287f0d8">OHOS::Rotate</a> (const Line &amp;origLine, int16_t angle, const Vector2&lt; int16_t &gt; &amp;pivot, Line &amp;out)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1227968921093527"><a name="p1227968921093527"></a><a name="p1227968921093527"></a>void&nbsp;</p>
<p id="p1703599422093527"><a name="p1703599422093527"></a><a name="p1703599422093527"></a>Rotates a line around the pivot by a certain angle. </p>
</td>
</tr>
<tr id="row540857582093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p414719234093527"><a name="p414719234093527"></a><a name="p414719234093527"></a><a href="Graphic.md#ga77d0dea6024cd2bb980f27f789db77c3">OHOS::Rotate</a> (const <a href="Rect.md">Rect</a> &amp;origRect, int16_t angle, const Vector2&lt; int16_t &gt; &amp;pivot, Polygon &amp;out)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1693319838093527"><a name="p1693319838093527"></a><a name="p1693319838093527"></a>void&nbsp;</p>
<p id="p1722566609093527"><a name="p1722566609093527"></a><a name="p1722566609093527"></a>Rotates a rectangle around the pivot by a certain angle. </p>
</td>
</tr>
</tbody>
</table>

