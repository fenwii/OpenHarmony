# OHOS::UISlider::UISliderEventListener<a name="ZH-CN_TOPIC_0000001054598187"></a>

## **Overview**<a name="section719355167093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents the listener for a slider change. 

This is an inner class of  **[UISlider](OHOS-UISlider.md)**  used to listen for slider events and invoke the callback function.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section109061004093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table109223580093534"></a>
<table><thead align="left"><tr id="row1301608619093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p72573842093534"><a name="p72573842093534"></a><a name="p72573842093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p162125422093534"><a name="p162125422093534"></a><a name="p162125422093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row594676722093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p970073168093534"><a name="p970073168093534"></a><a name="p970073168093534"></a><a href="Graphic.md#gaf7923989ab1a8cb8a0b643ef65d02134">~UISliderEventListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p396543624093534"><a name="p396543624093534"></a><a name="p396543624093534"></a>virtual&nbsp;</p>
<p id="p1878605720093534"><a name="p1878605720093534"></a><a name="p1878605720093534"></a>A destructor used to delete the <strong id="b570108007093534"><a name="b570108007093534"></a><a name="b570108007093534"></a> <a href="OHOS-UISlider-UISliderEventListener.md">UISliderEventListener</a> </strong> instance. </p>
</td>
</tr>
<tr id="row587081469093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1600370123093534"><a name="p1600370123093534"></a><a name="p1600370123093534"></a><a href="Graphic.md#ga6044e7ac9a27c7a85cc855dd32e4df5e">OnChange</a> (int16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1563187662093534"><a name="p1563187662093534"></a><a name="p1563187662093534"></a>virtual void&nbsp;</p>
<p id="p2100116742093534"><a name="p2100116742093534"></a><a name="p2100116742093534"></a>Called when the slider is dragged or clicked. This is a virtual function, which needs your implementation. </p>
</td>
</tr>
<tr id="row1279677374093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p678715457093534"><a name="p678715457093534"></a><a name="p678715457093534"></a><a href="Graphic.md#gaf8982c429bfa52c1a8a01d1115b596e6">OnRelease</a> (int16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1750386703093534"><a name="p1750386703093534"></a><a name="p1750386703093534"></a>virtual void&nbsp;</p>
<p id="p696681399093534"><a name="p696681399093534"></a><a name="p696681399093534"></a>Called when the slider is released. This is a virtual function, which needs your implementation. </p>
</td>
</tr>
<tr id="row453632034093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p328927714093534"><a name="p328927714093534"></a><a name="p328927714093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1315742435093534"><a name="p1315742435093534"></a><a name="p1315742435093534"></a>void *&nbsp;</p>
<p id="p1965494368093534"><a name="p1965494368093534"></a><a name="p1965494368093534"></a>Overrides the <strong id="b218490791093534"><a name="b218490791093534"></a><a name="b218490791093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row33116383093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1039871707093534"><a name="p1039871707093534"></a><a name="p1039871707093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1132761767093534"><a name="p1132761767093534"></a><a name="p1132761767093534"></a>void&nbsp;</p>
<p id="p1962760772093534"><a name="p1962760772093534"></a><a name="p1962760772093534"></a>Overrides the <strong id="b396925091093534"><a name="b396925091093534"></a><a name="b396925091093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

