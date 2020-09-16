# OHOS::TransformMap<a name="ZH-CN_TOPIC_0000001055078173"></a>

## **Overview**<a name="section2039282623093536"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Transforms a rectangle, including rotation and scaling. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section149753405093536"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table90261561093536"></a>
<table><thead align="left"><tr id="row786559664093536"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p766411597093536"><a name="p766411597093536"></a><a name="p766411597093536"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p321783625093536"><a name="p321783625093536"></a><a name="p321783625093536"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1140734949093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892610317093536"><a name="p1892610317093536"></a><a name="p1892610317093536"></a><a href="Graphic.md#ga3b20453b0a161da3a1a761fd75da9975">TransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2113630354093536"><a name="p2113630354093536"></a><a name="p2113630354093536"></a>&nbsp;</p>
<p id="p612429939093536"><a name="p612429939093536"></a><a name="p612429939093536"></a>The default constructor used to create a <strong id="b1152088952093536"><a name="b1152088952093536"></a><a name="b1152088952093536"></a><a href="OHOS-TransformMap.md">TransformMap</a></strong> instance. </p>
</td>
</tr>
<tr id="row1789232873093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1256081698093536"><a name="p1256081698093536"></a><a name="p1256081698093536"></a><a href="Graphic.md#ga84f0243719d4b43d0ee3a22e74c165bb">TransformMap</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;rect)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p531079564093536"><a name="p531079564093536"></a><a name="p531079564093536"></a>&nbsp;</p>
<p id="p410833077093536"><a name="p410833077093536"></a><a name="p410833077093536"></a>A constructor used to create a <strong id="b316926269093536"><a name="b316926269093536"></a><a name="b316926269093536"></a><a href="OHOS-TransformMap.md">TransformMap</a></strong> instance. </p>
</td>
</tr>
<tr id="row382772980093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1419412009093536"><a name="p1419412009093536"></a><a name="p1419412009093536"></a><a href="Graphic.md#gaaa46c8a5a343df76b418423a9f2344ba">~TransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p937606103093536"><a name="p937606103093536"></a><a name="p937606103093536"></a>&nbsp;</p>
<p id="p1522915625093536"><a name="p1522915625093536"></a><a name="p1522915625093536"></a>A destructor used to delete the <strong id="b1362356321093536"><a name="b1362356321093536"></a><a name="b1362356321093536"></a><a href="OHOS-TransformMap.md">TransformMap</a></strong> instance. </p>
</td>
</tr>
<tr id="row761130703093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p494061972093536"><a name="p494061972093536"></a><a name="p494061972093536"></a><a href="Graphic.md#ga6a50a29fe85e89c6d4445822c7a2946b">GetClockWise</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p564713395093536"><a name="p564713395093536"></a><a name="p564713395093536"></a>bool&nbsp;</p>
<p id="p693819140093536"><a name="p693819140093536"></a><a name="p693819140093536"></a>Checks whether the vertex coordinates of a polygon are clockwise. </p>
</td>
</tr>
<tr id="row1335714563093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1962943192093536"><a name="p1962943192093536"></a><a name="p1962943192093536"></a><a href="Graphic.md#gaaf0b94adde30d2ee1f3c82ef5d8c60c9">SetPolygon</a> (const <a href="OHOS-Polygon.md">Polygon</a> &amp;polygon)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1368740630093536"><a name="p1368740630093536"></a><a name="p1368740630093536"></a>void&nbsp;</p>
<p id="p712668427093536"><a name="p712668427093536"></a><a name="p712668427093536"></a>Sets a polygon after rectangle transformation. </p>
</td>
</tr>
<tr id="row22896046093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1605283987093536"><a name="p1605283987093536"></a><a name="p1605283987093536"></a><a href="Graphic.md#ga84f8d315da89e7aae7bf29478dbb51df">GetPolygon</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1485121801093536"><a name="p1485121801093536"></a><a name="p1485121801093536"></a><a href="OHOS-Polygon.md">Polygon</a>&nbsp;</p>
<p id="p1504649769093536"><a name="p1504649769093536"></a><a name="p1504649769093536"></a>Obtains the polygon after rectangle transformation. </p>
</td>
</tr>
<tr id="row777570769093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p976998877093536"><a name="p976998877093536"></a><a name="p976998877093536"></a><a href="Graphic.md#ga8a44fb7a813f5f183307191e96e18670">GetPivot</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1490256744093536"><a name="p1490256744093536"></a><a name="p1490256744093536"></a><a href="OHOS-Point.md">Point</a>&nbsp;</p>
<p id="p1533203905093536"><a name="p1533203905093536"></a><a name="p1533203905093536"></a>Obtains the pivot for the rotation or scaling operation. </p>
</td>
</tr>
<tr id="row1340952182093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1795634485093536"><a name="p1795634485093536"></a><a name="p1795634485093536"></a><a href="Graphic.md#ga84ec8032b9c8a4121c7464e6c14c7d01">IsInvalid</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1430759702093536"><a name="p1430759702093536"></a><a name="p1430759702093536"></a>bool&nbsp;</p>
<p id="p1967151767093536"><a name="p1967151767093536"></a><a name="p1967151767093536"></a>Checks whether the <strong id="b486608471093536"><a name="b486608471093536"></a><a name="b486608471093536"></a><a href="OHOS-TransformMap.md">TransformMap</a></strong> instance is invalid. When the vertices are all 0, the <strong id="b169073200093536"><a name="b169073200093536"></a><a name="b169073200093536"></a><a href="OHOS-TransformMap.md">TransformMap</a></strong> is invalid. </p>
</td>
</tr>
<tr id="row1165428047093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p483038864093536"><a name="p483038864093536"></a><a name="p483038864093536"></a><a href="Graphic.md#gaa2d8a5d822e40757f98c2a2820efed99">GetBoxRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p122438578093536"><a name="p122438578093536"></a><a name="p122438578093536"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1345600277093536"><a name="p1345600277093536"></a><a name="p1345600277093536"></a>Obtains the minimum rectangle that can contain a polygon. All vertices of the polygon are inside this rectangle. </p>
</td>
</tr>
<tr id="row1546785019093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p492898367093536"><a name="p492898367093536"></a><a name="p492898367093536"></a><a href="Graphic.md#gaea4c507789bf4c27daef3e81176c656d">Rotate</a> (int16_t angle, const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;pivot)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1397480407093536"><a name="p1397480407093536"></a><a name="p1397480407093536"></a>void&nbsp;</p>
<p id="p191331300093536"><a name="p191331300093536"></a><a name="p191331300093536"></a>Rotates the rectangle. </p>
</td>
</tr>
<tr id="row1299470559093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1490385937093536"><a name="p1490385937093536"></a><a name="p1490385937093536"></a><a href="Graphic.md#gae9344b31226a5a35035ccb845bf9cff2">Scale</a> (const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; float &gt; scale, const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;pivot)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1639526998093536"><a name="p1639526998093536"></a><a name="p1639526998093536"></a>void&nbsp;</p>
<p id="p1217696209093536"><a name="p1217696209093536"></a><a name="p1217696209093536"></a>Scales the rectangle. </p>
</td>
</tr>
<tr id="row669334977093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p168302821093536"><a name="p168302821093536"></a><a name="p168302821093536"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p114957657093536"><a name="p114957657093536"></a><a name="p114957657093536"></a>void *&nbsp;</p>
<p id="p774492048093536"><a name="p774492048093536"></a><a name="p774492048093536"></a>Overrides the <strong id="b2006476113093536"><a name="b2006476113093536"></a><a name="b2006476113093536"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1332274488093536"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205003669093536"><a name="p205003669093536"></a><a name="p205003669093536"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p848825188093536"><a name="p848825188093536"></a><a name="p848825188093536"></a>void&nbsp;</p>
<p id="p1694128117093536"><a name="p1694128117093536"></a><a name="p1694128117093536"></a>Overrides the <strong id="b1177021182093536"><a name="b1177021182093536"></a><a name="b1177021182093536"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

