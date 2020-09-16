# OHOS::Polygon<a name="EN-US_TOPIC_0000001055678124"></a>

## **Overview**<a name="section1036148264093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a polygon, including vertex coordinates and the maximum number of vertices \(defined by  [MAX\_VERTEX\_NUM](graphic.md#gafff78acb69e2b147b6f33d68e570ef54)\). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1655935217093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table62048988093535"></a>
<table><thead align="left"><tr id="row1223210378093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p919311669093535"><a name="p919311669093535"></a><a name="p919311669093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p196759167093535"><a name="p196759167093535"></a><a name="p196759167093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row558802088093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p152953427093535"><a name="p152953427093535"></a><a name="p152953427093535"></a><a href="graphic.md#ga56fa89b7be39ff928c8ad488bbaddac3">Polygon</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1138407448093535"><a name="p1138407448093535"></a><a name="p1138407448093535"></a> </p>
<p id="p477893352093535"><a name="p477893352093535"></a><a name="p477893352093535"></a>The default constructor used to create a <strong id="b1984290111093535"><a name="b1984290111093535"></a><a name="b1984290111093535"></a><a href="ohos-polygon.md">Polygon</a></strong> instance. </p>
</td>
</tr>
<tr id="row200581441093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1248719159093535"><a name="p1248719159093535"></a><a name="p1248719159093535"></a><a href="graphic.md#gaa3be3f3605efe49629c024974e56da6a">Polygon</a> (const <a href="ohos-rect.md">Rect</a> &amp;rect)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p153343368093535"><a name="p153343368093535"></a><a name="p153343368093535"></a> </p>
<p id="p62473801093535"><a name="p62473801093535"></a><a name="p62473801093535"></a>A constructor used to construct a <strong id="b5798851093535"><a name="b5798851093535"></a><a name="b5798851093535"></a><a href="ohos-polygon.md">Polygon</a></strong> instance based on a rectangle. </p>
</td>
</tr>
<tr id="row1988143677093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p727537098093535"><a name="p727537098093535"></a><a name="p727537098093535"></a><a href="graphic.md#ga54df053b5f430ed2ee7be14a898f668d">Polygon</a> (const <a href="ohos-vector2-t.md">Vector2</a>&lt; int16_t &gt; *vertexes, const uint8_t vertexNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1722518395093535"><a name="p1722518395093535"></a><a name="p1722518395093535"></a> </p>
<p id="p1237825120093535"><a name="p1237825120093535"></a><a name="p1237825120093535"></a>A constructor used to create a <strong id="b365119075093535"><a name="b365119075093535"></a><a name="b365119075093535"></a><a href="ohos-polygon.md">Polygon</a></strong> instance based on the vertex coordinates and the number of coordinates. </p>
</td>
</tr>
<tr id="row500679881093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1874190897093535"><a name="p1874190897093535"></a><a name="p1874190897093535"></a><a href="graphic.md#gab27ef37ff8b5462c771aed96f58dcac6">~Polygon</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p103286672093535"><a name="p103286672093535"></a><a name="p103286672093535"></a> </p>
<p id="p1412549172093535"><a name="p1412549172093535"></a><a name="p1412549172093535"></a>A destructor used to delete the <strong id="b1667695753093535"><a name="b1667695753093535"></a><a name="b1667695753093535"></a><a href="ohos-polygon.md">Polygon</a></strong> instance. </p>
</td>
</tr>
<tr id="row407324954093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p305466190093535"><a name="p305466190093535"></a><a name="p305466190093535"></a><a href="graphic.md#ga73295e4e05e9063082fb33b9847f4831">MakeAABB</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p600880904093535"><a name="p600880904093535"></a><a name="p600880904093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1154822389093535"><a name="p1154822389093535"></a><a name="p1154822389093535"></a>Obtains the minimum rectangle that can contain the polygon. All vertices of the polygon are inside this rectangle. </p>
</td>
</tr>
<tr id="row819681728093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1658515048093535"><a name="p1658515048093535"></a><a name="p1658515048093535"></a><a href="graphic.md#gaca0240aa7a65b24365064f296ff38a63">GetVertexNum</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1483075577093535"><a name="p1483075577093535"></a><a name="p1483075577093535"></a>uint8_t </p>
<p id="p535005756093535"><a name="p535005756093535"></a><a name="p535005756093535"></a>Obtains the number of vertices of the polygon. </p>
</td>
</tr>
<tr id="row872853979093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1524496043093535"><a name="p1524496043093535"></a><a name="p1524496043093535"></a><a href="graphic.md#gad1990bc3055e0155d324479a2bb3baf1">SetVertexNum</a> (uint8_t vertexNum)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1530045129093535"><a name="p1530045129093535"></a><a name="p1530045129093535"></a>void </p>
<p id="p819494776093535"><a name="p819494776093535"></a><a name="p819494776093535"></a>Sets the number of vertices of a polygon. </p>
</td>
</tr>
<tr id="row311117650093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p978028411093535"><a name="p978028411093535"></a><a name="p978028411093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1469454637093535"><a name="p1469454637093535"></a><a name="p1469454637093535"></a>void * </p>
<p id="p836981622093535"><a name="p836981622093535"></a><a name="p836981622093535"></a>Overrides the <strong id="b1712016616093535"><a name="b1712016616093535"></a><a name="b1712016616093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1154965840093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1087651635093535"><a name="p1087651635093535"></a><a name="p1087651635093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p158357590093535"><a name="p158357590093535"></a><a name="p158357590093535"></a>void </p>
<p id="p1019327418093535"><a name="p1019327418093535"></a><a name="p1019327418093535"></a>Overrides the <strong id="b1905815272093535"><a name="b1905815272093535"></a><a name="b1905815272093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Attributes<a name="pub-static-attribs"></a>

<a name="table512421383093535"></a>
<table><thead align="left"><tr id="row203840695093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p216566729093535"><a name="p216566729093535"></a><a name="p216566729093535"></a>Static Public Attribute Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1428538334093535"><a name="p1428538334093535"></a><a name="p1428538334093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1245615898093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1904612563093535"><a name="p1904612563093535"></a><a name="p1904612563093535"></a><a href="graphic.md#gafff78acb69e2b147b6f33d68e570ef54">MAX_VERTEX_NUM</a> = 8</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
</tbody>
</table>

