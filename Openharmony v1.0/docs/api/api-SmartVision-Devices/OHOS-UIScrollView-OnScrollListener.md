# OHOS::UIScrollView::OnScrollListener<a name="ZH-CN_TOPIC_0000001055358134"></a>

## **Overview**<a name="section1301227584093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents a listener that contains a callback to be invoked upon scroll state changes. The state can either be  **SCROLL\_STATE\_STOP**  or  **SCROLL\_STATE\_MOVE**. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1952371215093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table541142682093534"></a>
<table><thead align="left"><tr id="row732285466093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p637744680093534"><a name="p637744680093534"></a><a name="p637744680093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p4438132093534"><a name="p4438132093534"></a><a name="p4438132093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1030275338093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1813387675093534"><a name="p1813387675093534"></a><a name="p1813387675093534"></a><a href="Graphic.md#gad065bfe4e322d036b5bd9e30667754a6">OnScrollListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p925778424093534"><a name="p925778424093534"></a><a name="p925778424093534"></a>&nbsp;</p>
<p id="p1974057277093534"><a name="p1974057277093534"></a><a name="p1974057277093534"></a>A constructor used to create an <strong id="b970022760093534"><a name="b970022760093534"></a><a name="b970022760093534"></a><a href="OHOS-UIScrollView-OnScrollListener.md">OnScrollListener</a></strong> instance with the default scroll state <strong id="b521285473093534"><a name="b521285473093534"></a><a name="b521285473093534"></a>SCROLL_STATE_STOP</strong>. </p>
</td>
</tr>
<tr id="row310155202093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p402601820093534"><a name="p402601820093534"></a><a name="p402601820093534"></a><a href="Graphic.md#ga14fe076dffea62fdd281cd13e846de2d">~OnScrollListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1394584269093534"><a name="p1394584269093534"></a><a name="p1394584269093534"></a>virtual&nbsp;</p>
<p id="p799999362093534"><a name="p799999362093534"></a><a name="p799999362093534"></a>A destructor used to delete the <strong id="b499987646093534"><a name="b499987646093534"></a><a name="b499987646093534"></a><a href="OHOS-UIScrollView-OnScrollListener.md">OnScrollListener</a></strong> instance. </p>
</td>
</tr>
<tr id="row1037079787093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1320919184093534"><a name="p1320919184093534"></a><a name="p1320919184093534"></a><a href="Graphic.md#ga8000c484a999483edc66e8dd1b7ceaf6">OnScrollStart</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p692421806093534"><a name="p692421806093534"></a><a name="p692421806093534"></a>virtual void&nbsp;</p>
<p id="p1881544119093534"><a name="p1881544119093534"></a><a name="p1881544119093534"></a>Called when a scroll starts. </p>
</td>
</tr>
<tr id="row1637565398093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p278352355093534"><a name="p278352355093534"></a><a name="p278352355093534"></a><a href="Graphic.md#ga958c02ddc348eadaaf08f917f55aba63">OnScrollEnd</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059250463093534"><a name="p1059250463093534"></a><a name="p1059250463093534"></a>virtual void&nbsp;</p>
<p id="p173972467093534"><a name="p173972467093534"></a><a name="p173972467093534"></a>Called when a scroll ends. </p>
</td>
</tr>
<tr id="row2019926486093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p998400031093534"><a name="p998400031093534"></a><a name="p998400031093534"></a><a href="Graphic.md#ga15a8abaeb958bfa972b541b59fabd8a7">GetScrollState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p785207086093534"><a name="p785207086093534"></a><a name="p785207086093534"></a>uint8_t&nbsp;</p>
<p id="p711135678093534"><a name="p711135678093534"></a><a name="p711135678093534"></a>Obtains the scroll state of this view. </p>
</td>
</tr>
<tr id="row437894882093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p938346530093534"><a name="p938346530093534"></a><a name="p938346530093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p187166280093534"><a name="p187166280093534"></a><a name="p187166280093534"></a>void *&nbsp;</p>
<p id="p1418607459093534"><a name="p1418607459093534"></a><a name="p1418607459093534"></a>Overrides the <strong id="b243222991093534"><a name="b243222991093534"></a><a name="b243222991093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row630873310093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p426946833093534"><a name="p426946833093534"></a><a name="p426946833093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1971679501093534"><a name="p1971679501093534"></a><a name="p1971679501093534"></a>void&nbsp;</p>
<p id="p1480736647093534"><a name="p1480736647093534"></a><a name="p1480736647093534"></a>Overrides the <strong id="b1791146467093534"><a name="b1791146467093534"></a><a name="b1791146467093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

