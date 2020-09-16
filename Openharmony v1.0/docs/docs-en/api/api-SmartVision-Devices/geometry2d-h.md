# geometry2d.h<a name="EN-US_TOPIC_0000001054799567"></a>

## **Overview**<a name="section2018101397093525"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines attributes of 2D geometries \(including points, lines, rectangles, and polygons\) of the lightweight graphics system and provides functions for performing operations on the geometries. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1594265359093525"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1462562788093525"></a>
<table><thead align="left"><tr id="row127496653093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p773362873093525"><a name="p773362873093525"></a><a name="p773362873093525"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p60411748093525"><a name="p60411748093525"></a><a name="p60411748093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2103650560093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p686668386093525"><a name="p686668386093525"></a><a name="p686668386093525"></a><a href="ohos-line.md">OHOS::Line</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1709122869093525"><a name="p1709122869093525"></a><a name="p1709122869093525"></a>Defines a line, which consists of the start and end points. </p>
</td>
</tr>
<tr id="row2030601052093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1626115649093525"><a name="p1626115649093525"></a><a name="p1626115649093525"></a><a href="ohos-polygon.md">OHOS::Polygon</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p642097471093525"><a name="p642097471093525"></a><a name="p642097471093525"></a>Defines a polygon, including vertex coordinates and the maximum number of vertices (defined by <a href="graphic.md#gafff78acb69e2b147b6f33d68e570ef54">MAX_VERTEX_NUM</a>). </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table968920291093525"></a>
<table><thead align="left"><tr id="row1268302333093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p869244826093525"><a name="p869244826093525"></a><a name="p869244826093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1479442040093525"><a name="p1479442040093525"></a><a name="p1479442040093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1326972488093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1677282833093525"><a name="p1677282833093525"></a><a name="p1677282833093525"></a><a href="graphic.md#ga1779d4dd0671282d297f1693252ca9d9">OHOS::Intersect</a> (const Line &amp;a, const Line &amp;b, Vector2&lt; int16_t &gt; &amp;out)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96403076093525"><a name="p96403076093525"></a><a name="p96403076093525"></a>bool </p>
<p id="p428587785093525"><a name="p428587785093525"></a><a name="p428587785093525"></a>Checks whether line segment a and line segment b intersect, and returns the intersection point (if available). </p>
</td>
</tr>
<tr id="row1963972841093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872736361093525"><a name="p1872736361093525"></a><a name="p1872736361093525"></a><a href="graphic.md#gace8a8524c6f91aa2f0f9be73a628da20">OHOS::IsIntersect</a> (const Line &amp;a, const Line &amp;b)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1757796439093525"><a name="p1757796439093525"></a><a name="p1757796439093525"></a>bool </p>
<p id="p593677405093525"><a name="p593677405093525"></a><a name="p593677405093525"></a>Chekcs whether line segment a and line segment b intersect. </p>
</td>
</tr>
<tr id="row1893547586093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2010246118093525"><a name="p2010246118093525"></a><a name="p2010246118093525"></a><a href="graphic.md#ga0001387a136a87fb2c2e2b5eb3363c72">OHOS::Clip</a> (Polygon &amp;poly, const Line &amp;line)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1696587660093525"><a name="p1696587660093525"></a><a name="p1696587660093525"></a>void </p>
<p id="p1400173347093525"><a name="p1400173347093525"></a><a name="p1400173347093525"></a>Clips a polygon by using a line segment. </p>
</td>
</tr>
<tr id="row1041490323093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p827173024093525"><a name="p827173024093525"></a><a name="p827173024093525"></a><a href="graphic.md#ga9fd2882e4813fbf4dbe77baa50d97b5c">OHOS::SuthHodgClip</a> (const <a href="rect.md">Rect</a> &amp;clipRect, const Polygon &amp;polygon)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p3222704093525"><a name="p3222704093525"></a><a name="p3222704093525"></a>Polygon </p>
<p id="p1188964015093525"><a name="p1188964015093525"></a><a name="p1188964015093525"></a>Implements Sutherland-Hodgman, an algorithm used for clipping polygons. </p>
</td>
</tr>
<tr id="row2138499439093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p264736704093525"><a name="p264736704093525"></a><a name="p264736704093525"></a><a href="graphic.md#ga22219a4351530d5a6914bdc5dcf406d0">OHOS::Clip</a> (const Line &amp;line, const Polygon &amp;poly, Vector2&lt; int16_t &gt; *pOut, uint8_t *pNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1334549485093525"><a name="p1334549485093525"></a><a name="p1334549485093525"></a>void </p>
<p id="p1771148137093525"><a name="p1771148137093525"></a><a name="p1771148137093525"></a>Clips a polygon by using a line segment and obtains the intersections. </p>
</td>
</tr>
</tbody>
</table>

