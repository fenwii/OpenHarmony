# OHOS::Line<a name="ZH-CN_TOPIC_0000001054718157"></a>

## **Overview**<a name="section141558883093535"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines a line, which consists of the start and end points. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1845050409093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1464340997093535"></a>
<table><thead align="left"><tr id="row697736055093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1203587969093535"><a name="p1203587969093535"></a><a name="p1203587969093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p584767003093535"><a name="p584767003093535"></a><a name="p584767003093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row288345901093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1495254857093535"><a name="p1495254857093535"></a><a name="p1495254857093535"></a><a href="Graphic.md#ga3c8dd952afc5a76f8628c7f702755bd8">Line</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p873299877093535"><a name="p873299877093535"></a><a name="p873299877093535"></a>&nbsp;</p>
<p id="p1442069573093535"><a name="p1442069573093535"></a><a name="p1442069573093535"></a>The default constructor used to create a <strong id="b1237524572093535"><a name="b1237524572093535"></a><a name="b1237524572093535"></a><a href="OHOS-Line.md">Line</a></strong> instance. </p>
</td>
</tr>
<tr id="row1888757394093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p346437886093535"><a name="p346437886093535"></a><a name="p346437886093535"></a><a href="Graphic.md#ga0bda554c3c7d5950637a50ffbbec2269">Line</a> (const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;a, const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;b)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p299254045093535"><a name="p299254045093535"></a><a name="p299254045093535"></a>&nbsp;</p>
<p id="p836061910093535"><a name="p836061910093535"></a><a name="p836061910093535"></a>A constructor used to create a <strong id="b1016583182093535"><a name="b1016583182093535"></a><a name="b1016583182093535"></a><a href="OHOS-Line.md">Line</a></strong> instance. </p>
</td>
</tr>
<tr id="row38807939093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1518892865093535"><a name="p1518892865093535"></a><a name="p1518892865093535"></a><a href="Graphic.md#ga216de7fbcb274d28bb5a50d0e0692aa0">Line</a> (int16_t x1, int16_t <a href="zh-cn_topic_0000001055039462.md#ga369368526a105f3fba6776b11586070c">y1</a>, int16_t x2, int16_t y2)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1777784858093535"><a name="p1777784858093535"></a><a name="p1777784858093535"></a>&nbsp;</p>
<p id="p2049950433093535"><a name="p2049950433093535"></a><a name="p2049950433093535"></a>A constructor used to create a <strong id="b848365096093535"><a name="b848365096093535"></a><a name="b848365096093535"></a><a href="OHOS-Line.md">Line</a></strong> instance. </p>
</td>
</tr>
<tr id="row2050702166093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429732316093535"><a name="p429732316093535"></a><a name="p429732316093535"></a><a href="Graphic.md#ga86d5bfc47854c5e85363adce571de167">~Line</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1578406171093535"><a name="p1578406171093535"></a><a name="p1578406171093535"></a>&nbsp;</p>
<p id="p585187010093535"><a name="p585187010093535"></a><a name="p585187010093535"></a>A destructor used to delete the <strong id="b1964440175093535"><a name="b1964440175093535"></a><a name="b1964440175093535"></a><a href="OHOS-Line.md">Line</a></strong> instance. </p>
</td>
</tr>
<tr id="row394217525093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1563875037093535"><a name="p1563875037093535"></a><a name="p1563875037093535"></a><a href="Graphic.md#gafeae0169d5e3e92fcbc743c09cd4f6d0">operator[]</a> (uint8_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1357546947093535"><a name="p1357546947093535"></a><a name="p1357546947093535"></a><a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt; &amp;&nbsp;</p>
<p id="p1172791989093535"><a name="p1172791989093535"></a><a name="p1172791989093535"></a>Obtains the start or end point of the line based on the value of <strong id="b1098737861093535"><a name="b1098737861093535"></a><a name="b1098737861093535"></a>index</strong>. </p>
</td>
</tr>
<tr id="row1473852690093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1212489756093535"><a name="p1212489756093535"></a><a name="p1212489756093535"></a><a href="Graphic.md#ga3f747832db7335f2198c7746140a6631">operator[]</a> (uint8_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p125210789093535"><a name="p125210789093535"></a><a name="p125210789093535"></a>const <a href="OHOS-Vector2-T.md">Vector2</a>&lt; int16_t &gt;&nbsp;</p>
<p id="p535812280093535"><a name="p535812280093535"></a><a name="p535812280093535"></a>Obtains the start or end point of the line based on the value of <strong id="b979774157093535"><a name="b979774157093535"></a><a name="b979774157093535"></a>index</strong>. </p>
</td>
</tr>
<tr id="row178256128093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p585742799093535"><a name="p585742799093535"></a><a name="p585742799093535"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1409927232093535"><a name="p1409927232093535"></a><a name="p1409927232093535"></a>void *&nbsp;</p>
<p id="p1229638012093535"><a name="p1229638012093535"></a><a name="p1229638012093535"></a>Overrides the <strong id="b1419042078093535"><a name="b1419042078093535"></a><a name="b1419042078093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row787037457093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1808455299093535"><a name="p1808455299093535"></a><a name="p1808455299093535"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1031537367093535"><a name="p1031537367093535"></a><a name="p1031537367093535"></a>void&nbsp;</p>
<p id="p666336288093535"><a name="p666336288093535"></a><a name="p666336288093535"></a>Overrides the <strong id="b548242277093535"><a name="b548242277093535"></a><a name="b548242277093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

