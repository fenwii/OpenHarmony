# OHOS::UIView::OnDragListener<a name="ZH-CN_TOPIC_0000001054598189"></a>

## **Overview**<a name="section720343009093535"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines a drag event listener. You need to register this listener with the view to listen to drag events. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1898448858093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1293802348093535"></a>
<table><thead align="left"><tr id="row1643634659093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1815611237093535"><a name="p1815611237093535"></a><a name="p1815611237093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1926993820093535"><a name="p1926993820093535"></a><a name="p1926993820093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1070898143093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1790876605093535"><a name="p1790876605093535"></a><a name="p1790876605093535"></a><a href="Graphic.md#ga876bada94186d79c03de6da64c26e636">OnDragStart</a> (<a href="OHOS-UIView.md">UIView</a> &amp;view, const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1309114099093535"><a name="p1309114099093535"></a><a name="p1309114099093535"></a>virtual bool&nbsp;</p>
<p id="p1648251539093535"><a name="p1648251539093535"></a><a name="p1648251539093535"></a>Called when a view starts to drag. </p>
</td>
</tr>
<tr id="row1838498526093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p777513762093535"><a name="p777513762093535"></a><a name="p777513762093535"></a><a href="Graphic.md#gac112ce602c6939a52781d13440255b0c">OnDrag</a> (<a href="OHOS-UIView.md">UIView</a> &amp;view, const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1105782576093535"><a name="p1105782576093535"></a><a name="p1105782576093535"></a>virtual bool&nbsp;</p>
<p id="p1717042794093535"><a name="p1717042794093535"></a><a name="p1717042794093535"></a>Called when a view is being dragged. </p>
</td>
</tr>
<tr id="row1207059153093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183653403093535"><a name="p1183653403093535"></a><a name="p1183653403093535"></a><a href="Graphic.md#gab9e57971ae7e9925eaa3ccef245cbd72">OnDragEnd</a> (<a href="OHOS-UIView.md">UIView</a> &amp;view, const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1007731057093535"><a name="p1007731057093535"></a><a name="p1007731057093535"></a>virtual bool&nbsp;</p>
<p id="p393708755093535"><a name="p393708755093535"></a><a name="p393708755093535"></a>Called when a view stops dragging. </p>
</td>
</tr>
<tr id="row323114565093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1069663567093535"><a name="p1069663567093535"></a><a name="p1069663567093535"></a><a href="Graphic.md#ga34c01de74c319674fc94d1d74bb6e77e">~OnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p827879859093535"><a name="p827879859093535"></a><a name="p827879859093535"></a>virtual&nbsp;</p>
<p id="p1743716794093535"><a name="p1743716794093535"></a><a name="p1743716794093535"></a>A destructor used to delete the <strong id="b1786573529093535"><a name="b1786573529093535"></a><a name="b1786573529093535"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a></strong> instance. </p>
</td>
</tr>
<tr id="row1392058031093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p611260274093535"><a name="p611260274093535"></a><a name="p611260274093535"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514132515093535"><a name="p514132515093535"></a><a name="p514132515093535"></a>void *&nbsp;</p>
<p id="p1079038878093535"><a name="p1079038878093535"></a><a name="p1079038878093535"></a>Overrides the <strong id="b1045595869093535"><a name="b1045595869093535"></a><a name="b1045595869093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row909205615093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521987600093535"><a name="p521987600093535"></a><a name="p521987600093535"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p884788524093535"><a name="p884788524093535"></a><a name="p884788524093535"></a>void&nbsp;</p>
<p id="p315616903093535"><a name="p315616903093535"></a><a name="p315616903093535"></a>Overrides the <strong id="b1675226832093535"><a name="b1675226832093535"></a><a name="b1675226832093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

