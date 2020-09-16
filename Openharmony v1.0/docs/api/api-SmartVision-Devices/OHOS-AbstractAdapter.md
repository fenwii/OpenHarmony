# OHOS::AbstractAdapter<a name="ZH-CN_TOPIC_0000001055518108"></a>

## **Overview**<a name="section1985521876093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines the base class for adapters. You can derive  **[AbstractAdapter](OHOS-AbstractAdapter.md)**  based on actual requirements and use the  **[GetView\(\)](Graphic.md#gab155b2f4a6d8fd97755dcd1e6d3d8361)**  and  **[GetCount\(\)](Graphic.md#ga67021b360d4097c475d5e24519b5276d)**  functions to implement adapters of different data types. For details, see  [TextAdapter](OHOS-TextAdapter.md). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section345035747093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1578808003093533"></a>
<table><thead align="left"><tr id="row735833963093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p885980295093533"><a name="p885980295093533"></a><a name="p885980295093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p434818331093533"><a name="p434818331093533"></a><a name="p434818331093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row241611107093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p48801785093533"><a name="p48801785093533"></a><a name="p48801785093533"></a><a href="Graphic.md#gab60e1c77fb98352bd62e56b550d75d88">AbstractAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p840015877093533"><a name="p840015877093533"></a><a name="p840015877093533"></a>&nbsp;</p>
<p id="p1597125587093533"><a name="p1597125587093533"></a><a name="p1597125587093533"></a>A constructor used to create an <strong id="b661669589093533"><a name="b661669589093533"></a><a name="b661669589093533"></a><a href="OHOS-AbstractAdapter.md">AbstractAdapter</a></strong> instance. </p>
</td>
</tr>
<tr id="row418572021093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1189659860093533"><a name="p1189659860093533"></a><a name="p1189659860093533"></a><a href="Graphic.md#ga86fbbc62904d459ec4fa39bab7703af7">~AbstractAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1628944438093533"><a name="p1628944438093533"></a><a name="p1628944438093533"></a>virtual&nbsp;</p>
<p id="p237976538093533"><a name="p237976538093533"></a><a name="p237976538093533"></a>A destructor used to delete the <strong id="b1272221002093533"><a name="b1272221002093533"></a><a name="b1272221002093533"></a><a href="OHOS-AbstractAdapter.md">AbstractAdapter</a></strong> instance. </p>
</td>
</tr>
<tr id="row499675889093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1522038674093533"><a name="p1522038674093533"></a><a name="p1522038674093533"></a><a href="Graphic.md#ga67021b360d4097c475d5e24519b5276d">GetCount</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1698568987093533"><a name="p1698568987093533"></a><a name="p1698568987093533"></a>virtual uint16_t&nbsp;</p>
<p id="p1012448790093533"><a name="p1012448790093533"></a><a name="p1012448790093533"></a>Obtains the number of adapter data items. </p>
</td>
</tr>
<tr id="row610788760093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1431582946093533"><a name="p1431582946093533"></a><a name="p1431582946093533"></a><a href="Graphic.md#gab155b2f4a6d8fd97755dcd1e6d3d8361">GetView</a> (<a href="OHOS-UIView.md">UIView</a> *inView, int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2109236995093533"><a name="p2109236995093533"></a><a name="p2109236995093533"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p2050524629093533"><a name="p2050524629093533"></a><a name="p2050524629093533"></a>Obtains a <strong id="b860580476093533"><a name="b860580476093533"></a><a name="b860580476093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance to convert adapter data into another <strong id="b11733876093533"><a name="b11733876093533"></a><a name="b11733876093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row334880872093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275260853093533"><a name="p275260853093533"></a><a name="p275260853093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1798350128093533"><a name="p1798350128093533"></a><a name="p1798350128093533"></a>void *&nbsp;</p>
<p id="p891662716093533"><a name="p891662716093533"></a><a name="p891662716093533"></a>Overrides the <strong id="b1196775009093533"><a name="b1196775009093533"></a><a name="b1196775009093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row857805059093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1697671160093533"><a name="p1697671160093533"></a><a name="p1697671160093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p236392886093533"><a name="p236392886093533"></a><a name="p236392886093533"></a>void&nbsp;</p>
<p id="p1554890618093533"><a name="p1554890618093533"></a><a name="p1554890618093533"></a>Overrides the <strong id="b349961370093533"><a name="b349961370093533"></a><a name="b349961370093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

