# OHOS::ListScrollListener<a name="ZH-CN_TOPIC_0000001055518114"></a>

## **Overview**<a name="section977636662084839"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents a listener that contains a callback to be invoked when the scroll state changes or when a new child view is selected at the preset position as this list scrolls. The scroll state can be \{**\} or SCROLL\_STATE\_MOVE\}. **

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section283047623084839"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1623017130084839"></a>
<table><thead align="left"><tr id="row451862500084839"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p795555050084839"><a name="p795555050084839"></a><a name="p795555050084839"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p317108990084839"><a name="p317108990084839"></a><a name="p317108990084839"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1742256722084839"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1142384720084839"><a name="p1142384720084839"></a><a name="p1142384720084839"></a><a href="Graphic.md#gabed0d1b84d44874c94487796be82748f">ListScrollListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1671956719084839"><a name="p1671956719084839"></a><a name="p1671956719084839"></a>&nbsp;</p>
<p id="p1194018139084839"><a name="p1194018139084839"></a><a name="p1194018139084839"></a>A constructor used to create a <strong id="b1307447596084839"><a name="b1307447596084839"></a><a name="b1307447596084839"></a><a href="OHOS-ListScrollListener.md">ListScrollListener</a></strong> instance with the default state <strong id="b1838536647084839"><a name="b1838536647084839"></a><a name="b1838536647084839"></a>SCROLL_STATE_STOP</strong>. </p>
</td>
</tr>
<tr id="row974972079084839"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p717812358084839"><a name="p717812358084839"></a><a name="p717812358084839"></a><a href="Graphic.md#gace5864b41e1f07feecb33b3f897fe02d">~ListScrollListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1412860401084839"><a name="p1412860401084839"></a><a name="p1412860401084839"></a>virtual&nbsp;</p>
<p id="p443219448084839"><a name="p443219448084839"></a><a name="p443219448084839"></a>A destructor used to delete the <strong id="b579594951084839"><a name="b579594951084839"></a><a name="b579594951084839"></a><a href="OHOS-ListScrollListener.md">ListScrollListener</a></strong> instance. </p>
</td>
</tr>
<tr id="row1415594546084839"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1549035898084839"><a name="p1549035898084839"></a><a name="p1549035898084839"></a><a href="Graphic.md#gae802e8b4c48f7d416d6809ba8fa89428">OnScrollStart</a> (int16_t <a href="UTILS.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, <a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1277492120084839"><a name="p1277492120084839"></a><a name="p1277492120084839"></a>virtual void&nbsp;</p>
<p id="p1673187730084839"><a name="p1673187730084839"></a><a name="p1673187730084839"></a>Called when a scroll starts. </p>
</td>
</tr>
<tr id="row316027435084839"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p398777933084839"><a name="p398777933084839"></a><a name="p398777933084839"></a><a href="Graphic.md#ga74cc55be27bfd4c21f10d859bc1fbd3d">OnScrollEnd</a> (int16_t <a href="UTILS.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, <a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p333091515084839"><a name="p333091515084839"></a><a name="p333091515084839"></a>virtual void&nbsp;</p>
<p id="p668615407084839"><a name="p668615407084839"></a><a name="p668615407084839"></a>Called when a scroll ends. </p>
</td>
</tr>
<tr id="row1239268735084839"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1370305487084839"><a name="p1370305487084839"></a><a name="p1370305487084839"></a><a href="Graphic.md#gab6b77fec222bb03439d2d0a37538f1f0">OnItemSelected</a> (int16_t <a href="UTILS.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, <a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1652611595084839"><a name="p1652611595084839"></a><a name="p1652611595084839"></a>virtual void&nbsp;</p>
<p id="p2120213667084839"><a name="p2120213667084839"></a><a name="p2120213667084839"></a>Called when a new child view is selected at the preset position as this list scrolls. For details about how to set the position, see <strong id="b132602106084839"><a name="b132602106084839"></a><a name="b132602106084839"></a>SetSelectPosition</strong>. </p>
</td>
</tr>
<tr id="row1789970682084839"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2093954429084839"><a name="p2093954429084839"></a><a name="p2093954429084839"></a><a href="Graphic.md#ga3710c81b7fe02708da391d23cf08ddad">GetScrollState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1034762863084839"><a name="p1034762863084839"></a><a name="p1034762863084839"></a>uint8_t&nbsp;</p>
<p id="p2063610299084839"><a name="p2063610299084839"></a><a name="p2063610299084839"></a>Obtains the scroll state of this list. </p>
</td>
</tr>
<tr id="row807476592084839"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p268153373084839"><a name="p268153373084839"></a><a name="p268153373084839"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1634102454084839"><a name="p1634102454084839"></a><a name="p1634102454084839"></a>void *&nbsp;</p>
<p id="p830091960084839"><a name="p830091960084839"></a><a name="p830091960084839"></a>Overrides the <strong id="b679844749084839"><a name="b679844749084839"></a><a name="b679844749084839"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1522181931084839"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p480437836084839"><a name="p480437836084839"></a><a name="p480437836084839"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p661059672084839"><a name="p661059672084839"></a><a name="p661059672084839"></a>void&nbsp;</p>
<p id="p1342053637084839"><a name="p1342053637084839"></a><a name="p1342053637084839"></a>Overrides the <strong id="b201038202084839"><a name="b201038202084839"></a><a name="b201038202084839"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

