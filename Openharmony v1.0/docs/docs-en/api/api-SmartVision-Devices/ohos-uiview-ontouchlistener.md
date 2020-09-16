# OHOS::UIView::OnTouchListener<a name="EN-US_TOPIC_0000001054918183"></a>

## **Overview**<a name="section206160046093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a touch event listener. You need to register this listener with the view to listen to touch events. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1039588948093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table307509021093535"></a>
<table><thead align="left"><tr id="row712751187093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1878007522093535"><a name="p1878007522093535"></a><a name="p1878007522093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p845385195093535"><a name="p845385195093535"></a><a name="p845385195093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1589791785093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1912099650093535"><a name="p1912099650093535"></a><a name="p1912099650093535"></a><a href="graphic.md#ga2cfaed7013dc76bcbe9a5ea5d51caac3">OnPress</a> (<a href="ohos-uiview.md">UIView</a> &amp;view, const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833752143093535"><a name="p833752143093535"></a><a name="p833752143093535"></a>virtual bool </p>
<p id="p1532226553093535"><a name="p1532226553093535"></a><a name="p1532226553093535"></a>Called when a view is pressed. </p>
</td>
</tr>
<tr id="row324896003093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p35233788093535"><a name="p35233788093535"></a><a name="p35233788093535"></a><a href="graphic.md#ga16fa19e254ae19fe181dba0ac9dd5d1f">OnRelease</a> (<a href="ohos-uiview.md">UIView</a> &amp;view, const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p915580871093535"><a name="p915580871093535"></a><a name="p915580871093535"></a>virtual bool </p>
<p id="p1349722758093535"><a name="p1349722758093535"></a><a name="p1349722758093535"></a>Called when a view is released. </p>
</td>
</tr>
<tr id="row1452496645093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p215381633093535"><a name="p215381633093535"></a><a name="p215381633093535"></a><a href="graphic.md#ga7ce030676f1222599dd6367cd4b9cf7e">OnCancel</a> (<a href="ohos-uiview.md">UIView</a> &amp;view, const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p300235606093535"><a name="p300235606093535"></a><a name="p300235606093535"></a>virtual bool </p>
<p id="p1185324465093535"><a name="p1185324465093535"></a><a name="p1185324465093535"></a>Called when a click event on a view is canceled. </p>
</td>
</tr>
<tr id="row2059852058093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1377117409093535"><a name="p1377117409093535"></a><a name="p1377117409093535"></a><a href="graphic.md#gacf19bb5f0c979bb6889d30a20b2737e1">~OnTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2062739399093535"><a name="p2062739399093535"></a><a name="p2062739399093535"></a>virtual </p>
<p id="p1351847696093535"><a name="p1351847696093535"></a><a name="p1351847696093535"></a>A destructor used to delete the <strong id="b1839434498093535"><a name="b1839434498093535"></a><a name="b1839434498093535"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a></strong> instance. </p>
</td>
</tr>
<tr id="row641566636093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1439061347093535"><a name="p1439061347093535"></a><a name="p1439061347093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p227482862093535"><a name="p227482862093535"></a><a name="p227482862093535"></a>void * </p>
<p id="p620132222093535"><a name="p620132222093535"></a><a name="p620132222093535"></a>Overrides the <strong id="b1442692932093535"><a name="b1442692932093535"></a><a name="b1442692932093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row2062069251093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1181168332093535"><a name="p1181168332093535"></a><a name="p1181168332093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p615146245093535"><a name="p615146245093535"></a><a name="p615146245093535"></a>void </p>
<p id="p1608099086093535"><a name="p1608099086093535"></a><a name="p1608099086093535"></a>Overrides the <strong id="b1138204183093535"><a name="b1138204183093535"></a><a name="b1138204183093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

