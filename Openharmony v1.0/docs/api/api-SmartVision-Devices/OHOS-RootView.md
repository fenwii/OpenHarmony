# OHOS::RootView<a name="ZH-CN_TOPIC_0000001054598173"></a>

## **Overview**<a name="section1866989165093532"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines the functions related to a root view which contains its child views and represents the root node in a tree structure. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section97144983093532"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1492956693093532"></a>
<table><thead align="left"><tr id="row1638955323093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1262498811093532"><a name="p1262498811093532"></a><a name="p1262498811093532"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1031591586093532"><a name="p1031591586093532"></a><a name="p1031591586093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1273788413093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671559659093532"><a name="p671559659093532"></a><a name="p671559659093532"></a><a href="OHOS-RootView-OnKeyActListener.md">OnKeyActListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p435901761093532"><a name="p435901761093532"></a><a name="p435901761093532"></a>Represents the listener for monitoring physical key events. </p>
</td>
</tr>
<tr id="row1876341182093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907165956093532"><a name="p907165956093532"></a><a name="p907165956093532"></a><a href="OHOS-RootView-OnVirtualDeviceEventListener.md">OnVirtualDeviceEventListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1291859036093532"><a name="p1291859036093532"></a><a name="p1291859036093532"></a>Listens for the input events triggered by a virtual device other than human touching or physical pressing. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1153752995093532"></a>
<table><thead align="left"><tr id="row874554140093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p644037626093532"><a name="p644037626093532"></a><a name="p644037626093532"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p506637894093532"><a name="p506637894093532"></a><a name="p506637894093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1540332255093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2127544989093532"><a name="p2127544989093532"></a><a name="p2127544989093532"></a><a href="Graphic.md#ga7b96c15cdbe0edd5045e479b3b2fe1eb">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1365264269093532"><a name="p1365264269093532"></a><a name="p1365264269093532"></a>UIViewType&nbsp;</p>
<p id="p1305295096093532"><a name="p1305295096093532"></a><a name="p1305295096093532"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row280770307093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1009305123093532"><a name="p1009305123093532"></a><a name="p1009305123093532"></a><a href="Graphic.md#gaffcd945698a2df5f3fde5342c74719a9">OnKeyEvent</a> (const <a href="OHOS-KeyEvent.md">KeyEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1610074606093532"><a name="p1610074606093532"></a><a name="p1610074606093532"></a>virtual void&nbsp;</p>
<p id="p1406339057093532"><a name="p1406339057093532"></a><a name="p1406339057093532"></a>Executes a physical key event. </p>
</td>
</tr>
<tr id="row106589632093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p30736257093532"><a name="p30736257093532"></a><a name="p30736257093532"></a><a href="Graphic.md#ga3c0fce0e3a6c1b83324e54468d077bb0">SetOnKeyActListener</a> (<a href="OHOS-RootView-OnKeyActListener.md">OnKeyActListener</a> *onKeyActListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1461326579093532"><a name="p1461326579093532"></a><a name="p1461326579093532"></a>void&nbsp;</p>
<p id="p112013274093532"><a name="p112013274093532"></a><a name="p112013274093532"></a>Sets the listener that contains a callback to be invoked upon a physical key event. </p>
</td>
</tr>
<tr id="row619279116093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p334720627093532"><a name="p334720627093532"></a><a name="p334720627093532"></a><a href="Graphic.md#ga00303597af333088c06a45346f4a77f2">ClearOnKeyActListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p610729301093532"><a name="p610729301093532"></a><a name="p610729301093532"></a>void&nbsp;</p>
<p id="p446450589093532"><a name="p446450589093532"></a><a name="p446450589093532"></a>Clears the listener for monitoring physical key events. </p>
</td>
</tr>
<tr id="row243943115093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p556708284093532"><a name="p556708284093532"></a><a name="p556708284093532"></a><a href="Graphic.md#gae86a0b7fa1a2c4fee021cb7bed2d418c">OnVirtualDeviceEvent</a> (const <a href="OHOS-VirtualDeviceEvent.md">VirtualDeviceEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2071085498093532"><a name="p2071085498093532"></a><a name="p2071085498093532"></a>virtual void&nbsp;</p>
<p id="p63995247093532"><a name="p63995247093532"></a><a name="p63995247093532"></a>Executes an input event triggered by a virtual device. </p>
</td>
</tr>
<tr id="row1656529183093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p835601386093532"><a name="p835601386093532"></a><a name="p835601386093532"></a><a href="Graphic.md#gac12473c0dc9b293f6be9553afbb7c5d6">SetOnVirtualDeviceEventListener</a> (<a href="OHOS-RootView-OnVirtualDeviceEventListener.md">OnVirtualDeviceEventListener</a> *onVirtualDeviceEventListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2068864566093532"><a name="p2068864566093532"></a><a name="p2068864566093532"></a>void&nbsp;</p>
<p id="p129600299093532"><a name="p129600299093532"></a><a name="p129600299093532"></a>Sets a listener for monitoring the input events of a virtual device. </p>
</td>
</tr>
<tr id="row1896521524093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1441960206093532"><a name="p1441960206093532"></a><a name="p1441960206093532"></a><a href="Graphic.md#ga0b550a305c0cda1dc510b2446c56ed82">ClearOnVirtualDeviceEventListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p974254594093532"><a name="p974254594093532"></a><a name="p974254594093532"></a>void&nbsp;</p>
<p id="p1979489866093532"><a name="p1979489866093532"></a><a name="p1979489866093532"></a>Clears the listener for monitoring the input events of a virtual device. </p>
</td>
</tr>
<tr id="row1195442568093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p874287006093532"><a name="p874287006093532"></a><a name="p874287006093532"></a><a href="Graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p717207430093532"><a name="p717207430093532"></a><a name="p717207430093532"></a>&nbsp;</p>
<p id="p467687401093532"><a name="p467687401093532"></a><a name="p467687401093532"></a>A default constructor used to create a <strong id="b352479931093532"><a name="b352479931093532"></a><a name="b352479931093532"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1240375473093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1655134026093532"><a name="p1655134026093532"></a><a name="p1655134026093532"></a><a href="Graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1522623515093532"><a name="p1522623515093532"></a><a name="p1522623515093532"></a>virtual&nbsp;</p>
<p id="p1275012826093532"><a name="p1275012826093532"></a><a name="p1275012826093532"></a>A destructor used to delete the <strong id="b1406574096093532"><a name="b1406574096093532"></a><a name="b1406574096093532"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row198305700093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616049912093532"><a name="p1616049912093532"></a><a name="p1616049912093532"></a><a href="Graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1269270711093532"><a name="p1269270711093532"></a><a name="p1269270711093532"></a>UIViewType&nbsp;</p>
<p id="p248824532093532"><a name="p248824532093532"></a><a name="p248824532093532"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1508702881093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1907358614093532"><a name="p1907358614093532"></a><a name="p1907358614093532"></a><a href="Graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p853456177093532"><a name="p853456177093532"></a><a name="p853456177093532"></a>virtual void&nbsp;</p>
<p id="p1659214482093532"><a name="p1659214482093532"></a><a name="p1659214482093532"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row354869265093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p66140182093532"><a name="p66140182093532"></a><a name="p66140182093532"></a><a href="Graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="OHOS-UIView.md">UIView</a> *prevView, <a href="OHOS-UIView.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p174795308093532"><a name="p174795308093532"></a><a name="p174795308093532"></a>virtual void&nbsp;</p>
<p id="p1347457757093532"><a name="p1347457757093532"></a><a name="p1347457757093532"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row748108660093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p151345648093532"><a name="p151345648093532"></a><a name="p151345648093532"></a><a href="Graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1622316476093532"><a name="p1622316476093532"></a><a name="p1622316476093532"></a>virtual void&nbsp;</p>
<p id="p2060832373093532"><a name="p2060832373093532"></a><a name="p2060832373093532"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row921673490093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p343874143093532"><a name="p343874143093532"></a><a name="p343874143093532"></a><a href="Graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p442847153093532"><a name="p442847153093532"></a><a name="p442847153093532"></a>virtual void&nbsp;</p>
<p id="p1029919791093532"><a name="p1029919791093532"></a><a name="p1029919791093532"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row225837627093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2076404995093532"><a name="p2076404995093532"></a><a name="p2076404995093532"></a><a href="Graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p89938551093532"><a name="p89938551093532"></a><a name="p89938551093532"></a>virtual void&nbsp;</p>
<p id="p1093910091093532"><a name="p1093910091093532"></a><a name="p1093910091093532"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1440233039093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p196758534093532"><a name="p196758534093532"></a><a name="p196758534093532"></a><a href="Graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p273947582093532"><a name="p273947582093532"></a><a name="p273947582093532"></a>virtual void&nbsp;</p>
<p id="p1904076611093532"><a name="p1904076611093532"></a><a name="p1904076611093532"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row199532197093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1040382201093532"><a name="p1040382201093532"></a><a name="p1040382201093532"></a><a href="Graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1122871487093532"><a name="p1122871487093532"></a><a name="p1122871487093532"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p755273222093532"><a name="p755273222093532"></a><a name="p755273222093532"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1116854315093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1388550577093532"><a name="p1388550577093532"></a><a name="p1388550577093532"></a><a href="Graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p293717728093532"><a name="p293717728093532"></a><a name="p293717728093532"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p269692561093532"><a name="p269692561093532"></a><a name="p269692561093532"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row1840732834093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p969187257093532"><a name="p969187257093532"></a><a name="p969187257093532"></a><a href="Graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510679695093532"><a name="p1510679695093532"></a><a name="p1510679695093532"></a>void&nbsp;</p>
<p id="p1602420149093532"><a name="p1602420149093532"></a><a name="p1602420149093532"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1278984568093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p903863465093532"><a name="p903863465093532"></a><a name="p903863465093532"></a><a href="Graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1690270581093532"><a name="p1690270581093532"></a><a name="p1690270581093532"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p2114041974093532"><a name="p2114041974093532"></a><a name="p2114041974093532"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row1342034412093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228103084093532"><a name="p228103084093532"></a><a name="p228103084093532"></a><a href="Graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1879768182093532"><a name="p1879768182093532"></a><a name="p1879768182093532"></a>void&nbsp;</p>
<p id="p729842935093532"><a name="p729842935093532"></a><a name="p729842935093532"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row143296341093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p979778994093532"><a name="p979778994093532"></a><a name="p979778994093532"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p899261493093532"><a name="p899261493093532"></a><a name="p899261493093532"></a>&nbsp;</p>
<p id="p387787273093532"><a name="p387787273093532"></a><a name="p387787273093532"></a>A default constructor used to create an <strong id="b1228754602093532"><a name="b1228754602093532"></a><a name="b1228754602093532"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row190591008093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1828439337093532"><a name="p1828439337093532"></a><a name="p1828439337093532"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p308266965093532"><a name="p308266965093532"></a><a name="p308266965093532"></a>&nbsp;</p>
<p id="p201816735093532"><a name="p201816735093532"></a><a name="p201816735093532"></a>A constructor used to create an <strong id="b2028701364093532"><a name="b2028701364093532"></a><a name="b2028701364093532"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row712709199093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1067171598093532"><a name="p1067171598093532"></a><a name="p1067171598093532"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2002030650093532"><a name="p2002030650093532"></a><a name="p2002030650093532"></a>virtual&nbsp;</p>
<p id="p1103790934093532"><a name="p1103790934093532"></a><a name="p1103790934093532"></a>A destructor used to delete the <strong id="b1082949693093532"><a name="b1082949693093532"></a><a name="b1082949693093532"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1357260518093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1788932994093532"><a name="p1788932994093532"></a><a name="p1788932994093532"></a><a href="Graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p83018008093532"><a name="p83018008093532"></a><a name="p83018008093532"></a>virtual bool&nbsp;</p>
<p id="p2073478379093532"><a name="p2073478379093532"></a><a name="p2073478379093532"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1835302656093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1403708014093532"><a name="p1403708014093532"></a><a name="p1403708014093532"></a><a href="Graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p435864446093532"><a name="p435864446093532"></a><a name="p435864446093532"></a>virtual void&nbsp;</p>
<p id="p521525813093532"><a name="p521525813093532"></a><a name="p521525813093532"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row692806268093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p213002903093532"><a name="p213002903093532"></a><a name="p213002903093532"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1439029735093532"><a name="p1439029735093532"></a><a name="p1439029735093532"></a>virtual void&nbsp;</p>
<p id="p1495457767093532"><a name="p1495457767093532"></a><a name="p1495457767093532"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1001042204093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p721581309093532"><a name="p721581309093532"></a><a name="p721581309093532"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p723029107093532"><a name="p723029107093532"></a><a name="p723029107093532"></a>virtual void&nbsp;</p>
<p id="p1680080549093532"><a name="p1680080549093532"></a><a name="p1680080549093532"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row849837816093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p685185098093532"><a name="p685185098093532"></a><a name="p685185098093532"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p456276862093532"><a name="p456276862093532"></a><a name="p456276862093532"></a>void&nbsp;</p>
<p id="p1186184335093532"><a name="p1186184335093532"></a><a name="p1186184335093532"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row18089811093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1381958612093532"><a name="p1381958612093532"></a><a name="p1381958612093532"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p365072677093532"><a name="p365072677093532"></a><a name="p365072677093532"></a>void&nbsp;</p>
<p id="p1684502220093532"><a name="p1684502220093532"></a><a name="p1684502220093532"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1825410761093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1451046545093532"><a name="p1451046545093532"></a><a name="p1451046545093532"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1145028701093532"><a name="p1145028701093532"></a><a name="p1145028701093532"></a>virtual bool&nbsp;</p>
<p id="p1595780694093532"><a name="p1595780694093532"></a><a name="p1595780694093532"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row804543436093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1652347296093532"><a name="p1652347296093532"></a><a name="p1652347296093532"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p993426285093532"><a name="p993426285093532"></a><a name="p993426285093532"></a>virtual bool&nbsp;</p>
<p id="p1807662434093532"><a name="p1807662434093532"></a><a name="p1807662434093532"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row667282645093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119613871093532"><a name="p1119613871093532"></a><a name="p1119613871093532"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p945506268093532"><a name="p945506268093532"></a><a name="p945506268093532"></a>virtual bool&nbsp;</p>
<p id="p434592417093532"><a name="p434592417093532"></a><a name="p434592417093532"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1807460515093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806310041093532"><a name="p806310041093532"></a><a name="p806310041093532"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p767232329093532"><a name="p767232329093532"></a><a name="p767232329093532"></a>virtual bool&nbsp;</p>
<p id="p246631007093532"><a name="p246631007093532"></a><a name="p246631007093532"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1828711571093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p251887788093532"><a name="p251887788093532"></a><a name="p251887788093532"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p900393323093532"><a name="p900393323093532"></a><a name="p900393323093532"></a>virtual void&nbsp;</p>
<p id="p839519200093532"><a name="p839519200093532"></a><a name="p839519200093532"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row186484364093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1562669924093532"><a name="p1562669924093532"></a><a name="p1562669924093532"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1874163173093532"><a name="p1874163173093532"></a><a name="p1874163173093532"></a>virtual void&nbsp;</p>
<p id="p1269636057093532"><a name="p1269636057093532"></a><a name="p1269636057093532"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1707872022093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1387911051093532"><a name="p1387911051093532"></a><a name="p1387911051093532"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p599908001093532"><a name="p599908001093532"></a><a name="p599908001093532"></a>virtual void&nbsp;</p>
<p id="p1497199164093532"><a name="p1497199164093532"></a><a name="p1497199164093532"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1249110846093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1133697650093532"><a name="p1133697650093532"></a><a name="p1133697650093532"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1066464771093532"><a name="p1066464771093532"></a><a name="p1066464771093532"></a>virtual void&nbsp;</p>
<p id="p831159502093532"><a name="p831159502093532"></a><a name="p831159502093532"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row398386997093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1276487576093532"><a name="p1276487576093532"></a><a name="p1276487576093532"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1592432448093532"><a name="p1592432448093532"></a><a name="p1592432448093532"></a>void&nbsp;</p>
<p id="p1996318280093532"><a name="p1996318280093532"></a><a name="p1996318280093532"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1867105637093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1473888630093532"><a name="p1473888630093532"></a><a name="p1473888630093532"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p381533184093532"><a name="p381533184093532"></a><a name="p381533184093532"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p778285208093532"><a name="p778285208093532"></a><a name="p778285208093532"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1660715257093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p494690944093532"><a name="p494690944093532"></a><a name="p494690944093532"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p363890929093532"><a name="p363890929093532"></a><a name="p363890929093532"></a>void&nbsp;</p>
<p id="p1167030854093532"><a name="p1167030854093532"></a><a name="p1167030854093532"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row198728615093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1601218921093532"><a name="p1601218921093532"></a><a name="p1601218921093532"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p557313327093532"><a name="p557313327093532"></a><a name="p557313327093532"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p1555220378093532"><a name="p1555220378093532"></a><a name="p1555220378093532"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1150707012093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1677155128093532"><a name="p1677155128093532"></a><a name="p1677155128093532"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p855723432093532"><a name="p855723432093532"></a><a name="p855723432093532"></a>void&nbsp;</p>
<p id="p1791908693093532"><a name="p1791908693093532"></a><a name="p1791908693093532"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row901088613093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1120620363093532"><a name="p1120620363093532"></a><a name="p1120620363093532"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p851988575093532"><a name="p851988575093532"></a><a name="p851988575093532"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p1576179832093532"><a name="p1576179832093532"></a><a name="p1576179832093532"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row2049062263093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1076963618093532"><a name="p1076963618093532"></a><a name="p1076963618093532"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1134853763093532"><a name="p1134853763093532"></a><a name="p1134853763093532"></a>void&nbsp;</p>
<p id="p689244862093532"><a name="p689244862093532"></a><a name="p689244862093532"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row182341504093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1648067315093532"><a name="p1648067315093532"></a><a name="p1648067315093532"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p521894774093532"><a name="p521894774093532"></a><a name="p521894774093532"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p1269362402093532"><a name="p1269362402093532"></a><a name="p1269362402093532"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row790289335093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858813541093532"><a name="p858813541093532"></a><a name="p858813541093532"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1760680947093532"><a name="p1760680947093532"></a><a name="p1760680947093532"></a>void&nbsp;</p>
<p id="p1530361095093532"><a name="p1530361095093532"></a><a name="p1530361095093532"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1022321273093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1036013555093532"><a name="p1036013555093532"></a><a name="p1036013555093532"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1358824687093532"><a name="p1358824687093532"></a><a name="p1358824687093532"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p122087251093532"><a name="p122087251093532"></a><a name="p122087251093532"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1787074567093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p127660232093532"><a name="p127660232093532"></a><a name="p127660232093532"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1316176730093532"><a name="p1316176730093532"></a><a name="p1316176730093532"></a>void&nbsp;</p>
<p id="p13775564093532"><a name="p13775564093532"></a><a name="p13775564093532"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row824326221093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p27122324093532"><a name="p27122324093532"></a><a name="p27122324093532"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1598274360093532"><a name="p1598274360093532"></a><a name="p1598274360093532"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p986475013093532"><a name="p986475013093532"></a><a name="p986475013093532"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1072170771093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p986140841093532"><a name="p986140841093532"></a><a name="p986140841093532"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422048546093532"><a name="p422048546093532"></a><a name="p422048546093532"></a>virtual void&nbsp;</p>
<p id="p1701803655093532"><a name="p1701803655093532"></a><a name="p1701803655093532"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row885878865093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p61581584093532"><a name="p61581584093532"></a><a name="p61581584093532"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p911848099093532"><a name="p911848099093532"></a><a name="p911848099093532"></a>bool&nbsp;</p>
<p id="p305400548093532"><a name="p305400548093532"></a><a name="p305400548093532"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1153470334093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146773942093532"><a name="p2146773942093532"></a><a name="p2146773942093532"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1280430354093532"><a name="p1280430354093532"></a><a name="p1280430354093532"></a>void&nbsp;</p>
<p id="p96286787093532"><a name="p96286787093532"></a><a name="p96286787093532"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row2086136011093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1638983639093532"><a name="p1638983639093532"></a><a name="p1638983639093532"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1789970295093532"><a name="p1789970295093532"></a><a name="p1789970295093532"></a>bool&nbsp;</p>
<p id="p619646417093532"><a name="p619646417093532"></a><a name="p619646417093532"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row329615672093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1524088745093532"><a name="p1524088745093532"></a><a name="p1524088745093532"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1900170321093532"><a name="p1900170321093532"></a><a name="p1900170321093532"></a>void&nbsp;</p>
<p id="p643503683093532"><a name="p643503683093532"></a><a name="p643503683093532"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1974118642093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2038827631093532"><a name="p2038827631093532"></a><a name="p2038827631093532"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1435289743093532"><a name="p1435289743093532"></a><a name="p1435289743093532"></a>bool&nbsp;</p>
<p id="p1700513309093532"><a name="p1700513309093532"></a><a name="p1700513309093532"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row353798585093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1742617535093532"><a name="p1742617535093532"></a><a name="p1742617535093532"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p447171108093532"><a name="p447171108093532"></a><a name="p447171108093532"></a>void&nbsp;</p>
<p id="p2015071599093532"><a name="p2015071599093532"></a><a name="p2015071599093532"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1595675538093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p424100574093532"><a name="p424100574093532"></a><a name="p424100574093532"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p48398216093532"><a name="p48398216093532"></a><a name="p48398216093532"></a>bool&nbsp;</p>
<p id="p509915501093532"><a name="p509915501093532"></a><a name="p509915501093532"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1869824223093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1651763193093532"><a name="p1651763193093532"></a><a name="p1651763193093532"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1388493896093532"><a name="p1388493896093532"></a><a name="p1388493896093532"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1391542949093532"><a name="p1391542949093532"></a><a name="p1391542949093532"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row246223527093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2000912245093532"><a name="p2000912245093532"></a><a name="p2000912245093532"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1040593792093532"><a name="p1040593792093532"></a><a name="p1040593792093532"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p324162526093532"><a name="p324162526093532"></a><a name="p324162526093532"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row372649298093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p886087678093532"><a name="p886087678093532"></a><a name="p886087678093532"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p430838407093532"><a name="p430838407093532"></a><a name="p430838407093532"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p656089619093532"><a name="p656089619093532"></a><a name="p656089619093532"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row2114069296093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p258704158093532"><a name="p258704158093532"></a><a name="p258704158093532"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226714831093532"><a name="p1226714831093532"></a><a name="p1226714831093532"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1105552792093532"><a name="p1105552792093532"></a><a name="p1105552792093532"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1694301695093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1561916401093532"><a name="p1561916401093532"></a><a name="p1561916401093532"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p823222537093532"><a name="p823222537093532"></a><a name="p823222537093532"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p605905676093532"><a name="p605905676093532"></a><a name="p605905676093532"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row415414014093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1188692671093532"><a name="p1188692671093532"></a><a name="p1188692671093532"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p440427200093532"><a name="p440427200093532"></a><a name="p440427200093532"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1937454456093532"><a name="p1937454456093532"></a><a name="p1937454456093532"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row977168492093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1516136658093532"><a name="p1516136658093532"></a><a name="p1516136658093532"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1016579647093532"><a name="p1016579647093532"></a><a name="p1016579647093532"></a>void&nbsp;</p>
<p id="p265331268093532"><a name="p265331268093532"></a><a name="p265331268093532"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row119860700093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p414080056093532"><a name="p414080056093532"></a><a name="p414080056093532"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1941288193093532"><a name="p1941288193093532"></a><a name="p1941288193093532"></a>virtual void&nbsp;</p>
<p id="p1568497420093532"><a name="p1568497420093532"></a><a name="p1568497420093532"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row510025326093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p36794006093532"><a name="p36794006093532"></a><a name="p36794006093532"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1662470754093532"><a name="p1662470754093532"></a><a name="p1662470754093532"></a>virtual int16_t&nbsp;</p>
<p id="p256449909093532"><a name="p256449909093532"></a><a name="p256449909093532"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row920906368093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256160910093532"><a name="p256160910093532"></a><a name="p256160910093532"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p11837370093532"><a name="p11837370093532"></a><a name="p11837370093532"></a>virtual void&nbsp;</p>
<p id="p1895839082093532"><a name="p1895839082093532"></a><a name="p1895839082093532"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1437993565093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p845290394093532"><a name="p845290394093532"></a><a name="p845290394093532"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1774047154093532"><a name="p1774047154093532"></a><a name="p1774047154093532"></a>virtual int16_t&nbsp;</p>
<p id="p1033390359093532"><a name="p1033390359093532"></a><a name="p1033390359093532"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row2076350855093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p987835230093532"><a name="p987835230093532"></a><a name="p987835230093532"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p275549826093532"><a name="p275549826093532"></a><a name="p275549826093532"></a>virtual void&nbsp;</p>
<p id="p2068400654093532"><a name="p2068400654093532"></a><a name="p2068400654093532"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1632448595093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2083291781093532"><a name="p2083291781093532"></a><a name="p2083291781093532"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1862279462093532"><a name="p1862279462093532"></a><a name="p1862279462093532"></a>virtual void&nbsp;</p>
<p id="p1684719890093532"><a name="p1684719890093532"></a><a name="p1684719890093532"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1570305609093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2012581147093532"><a name="p2012581147093532"></a><a name="p2012581147093532"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p493296137093532"><a name="p493296137093532"></a><a name="p493296137093532"></a>int16_t&nbsp;</p>
<p id="p863444494093532"><a name="p863444494093532"></a><a name="p863444494093532"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1175115822093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p392241003093532"><a name="p392241003093532"></a><a name="p392241003093532"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1612782734093532"><a name="p1612782734093532"></a><a name="p1612782734093532"></a>virtual void&nbsp;</p>
<p id="p133669304093532"><a name="p133669304093532"></a><a name="p133669304093532"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1528845942093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1429707950093532"><a name="p1429707950093532"></a><a name="p1429707950093532"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p736746594093532"><a name="p736746594093532"></a><a name="p736746594093532"></a>int16_t&nbsp;</p>
<p id="p1597225106093532"><a name="p1597225106093532"></a><a name="p1597225106093532"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row836281574093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1601551767093532"><a name="p1601551767093532"></a><a name="p1601551767093532"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1185257559093532"><a name="p1185257559093532"></a><a name="p1185257559093532"></a>virtual void&nbsp;</p>
<p id="p1217896748093532"><a name="p1217896748093532"></a><a name="p1217896748093532"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1138780600093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p53214680093532"><a name="p53214680093532"></a><a name="p53214680093532"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p604983815093532"><a name="p604983815093532"></a><a name="p604983815093532"></a>virtual void&nbsp;</p>
<p id="p1947276249093532"><a name="p1947276249093532"></a><a name="p1947276249093532"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1235437519093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1216519513093532"><a name="p1216519513093532"></a><a name="p1216519513093532"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p816187453093532"><a name="p816187453093532"></a><a name="p816187453093532"></a>bool&nbsp;</p>
<p id="p559857614093532"><a name="p559857614093532"></a><a name="p559857614093532"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row612347629093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2105023203093532"><a name="p2105023203093532"></a><a name="p2105023203093532"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1288933228093532"><a name="p1288933228093532"></a><a name="p1288933228093532"></a>void&nbsp;</p>
<p id="p93230144093532"><a name="p93230144093532"></a><a name="p93230144093532"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row497446041093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691883783093532"><a name="p691883783093532"></a><a name="p691883783093532"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p36735832093532"><a name="p36735832093532"></a><a name="p36735832093532"></a>void&nbsp;</p>
<p id="p2090812732093532"><a name="p2090812732093532"></a><a name="p2090812732093532"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1355230311093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1286920879093532"><a name="p1286920879093532"></a><a name="p1286920879093532"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p232342626093532"><a name="p232342626093532"></a><a name="p232342626093532"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p923525292093532"><a name="p923525292093532"></a><a name="p923525292093532"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row502288083093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2081172492093532"><a name="p2081172492093532"></a><a name="p2081172492093532"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1458064606093532"><a name="p1458064606093532"></a><a name="p1458064606093532"></a>void&nbsp;</p>
<p id="p1660217536093532"><a name="p1660217536093532"></a><a name="p1660217536093532"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row876287439093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p341755279093532"><a name="p341755279093532"></a><a name="p341755279093532"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1268141930093532"><a name="p1268141930093532"></a><a name="p1268141930093532"></a>const char *&nbsp;</p>
<p id="p377658520093532"><a name="p377658520093532"></a><a name="p377658520093532"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row281882150093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1597396506093532"><a name="p1597396506093532"></a><a name="p1597396506093532"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1126660233093532"><a name="p1126660233093532"></a><a name="p1126660233093532"></a>void&nbsp;</p>
<p id="p254005699093532"><a name="p254005699093532"></a><a name="p254005699093532"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row768336482093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p979571139093532"><a name="p979571139093532"></a><a name="p979571139093532"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1628888130093532"><a name="p1628888130093532"></a><a name="p1628888130093532"></a>int16_t&nbsp;</p>
<p id="p1691594933093532"><a name="p1691594933093532"></a><a name="p1691594933093532"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1203469540093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1906481479093532"><a name="p1906481479093532"></a><a name="p1906481479093532"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1182764304093532"><a name="p1182764304093532"></a><a name="p1182764304093532"></a>virtual void&nbsp;</p>
<p id="p1102861916093532"><a name="p1102861916093532"></a><a name="p1102861916093532"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row286066722093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p320964220093532"><a name="p320964220093532"></a><a name="p320964220093532"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p823594193093532"><a name="p823594193093532"></a><a name="p823594193093532"></a>void&nbsp;</p>
<p id="p714359057093532"><a name="p714359057093532"></a><a name="p714359057093532"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row570376552093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p90839281093532"><a name="p90839281093532"></a><a name="p90839281093532"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2077358007093532"><a name="p2077358007093532"></a><a name="p2077358007093532"></a>void&nbsp;</p>
<p id="p731646613093532"><a name="p731646613093532"></a><a name="p731646613093532"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row634928306093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p911617138093532"><a name="p911617138093532"></a><a name="p911617138093532"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1442912607093532"><a name="p1442912607093532"></a><a name="p1442912607093532"></a>void&nbsp;</p>
<p id="p1823466422093532"><a name="p1823466422093532"></a><a name="p1823466422093532"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row914015260093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2084760642093532"><a name="p2084760642093532"></a><a name="p2084760642093532"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1147604481093532"><a name="p1147604481093532"></a><a name="p1147604481093532"></a>void&nbsp;</p>
<p id="p40958943093532"><a name="p40958943093532"></a><a name="p40958943093532"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1834964407093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1371597056093532"><a name="p1371597056093532"></a><a name="p1371597056093532"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1400648902093532"><a name="p1400648902093532"></a><a name="p1400648902093532"></a>void&nbsp;</p>
<p id="p1674989366093532"><a name="p1674989366093532"></a><a name="p1674989366093532"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row91923125093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p765513771093532"><a name="p765513771093532"></a><a name="p765513771093532"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695394245093532"><a name="p1695394245093532"></a><a name="p1695394245093532"></a>void&nbsp;</p>
<p id="p109816761093532"><a name="p109816761093532"></a><a name="p109816761093532"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row659098460093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2029326589093532"><a name="p2029326589093532"></a><a name="p2029326589093532"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p318034750093532"><a name="p318034750093532"></a><a name="p318034750093532"></a>void&nbsp;</p>
<p id="p1418853919093532"><a name="p1418853919093532"></a><a name="p1418853919093532"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1614026541093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p860316324093532"><a name="p860316324093532"></a><a name="p860316324093532"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p85325923093532"><a name="p85325923093532"></a><a name="p85325923093532"></a>void&nbsp;</p>
<p id="p1142991009093532"><a name="p1142991009093532"></a><a name="p1142991009093532"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row418363754093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1833690026093532"><a name="p1833690026093532"></a><a name="p1833690026093532"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1561701346093532"><a name="p1561701346093532"></a><a name="p1561701346093532"></a>void&nbsp;</p>
<p id="p326347868093532"><a name="p326347868093532"></a><a name="p326347868093532"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1336447882093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p777318745093532"><a name="p777318745093532"></a><a name="p777318745093532"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1645320262093532"><a name="p1645320262093532"></a><a name="p1645320262093532"></a>void&nbsp;</p>
<p id="p1044085758093532"><a name="p1044085758093532"></a><a name="p1044085758093532"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1371497619093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1589841497093532"><a name="p1589841497093532"></a><a name="p1589841497093532"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p295795241093532"><a name="p295795241093532"></a><a name="p295795241093532"></a>void&nbsp;</p>
<p id="p2088499268093532"><a name="p2088499268093532"></a><a name="p2088499268093532"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1933665115093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907141663093532"><a name="p907141663093532"></a><a name="p907141663093532"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1172188221093532"><a name="p1172188221093532"></a><a name="p1172188221093532"></a>void&nbsp;</p>
<p id="p1416060303093532"><a name="p1416060303093532"></a><a name="p1416060303093532"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row609842775093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1142436284093532"><a name="p1142436284093532"></a><a name="p1142436284093532"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p365808436093532"><a name="p365808436093532"></a><a name="p365808436093532"></a>void&nbsp;</p>
<p id="p485418941093532"><a name="p485418941093532"></a><a name="p485418941093532"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1516161148093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1475816613093532"><a name="p1475816613093532"></a><a name="p1475816613093532"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p890288009093532"><a name="p890288009093532"></a><a name="p890288009093532"></a>void&nbsp;</p>
<p id="p1964220229093532"><a name="p1964220229093532"></a><a name="p1964220229093532"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1627732703093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p22700247093532"><a name="p22700247093532"></a><a name="p22700247093532"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p166517059093532"><a name="p166517059093532"></a><a name="p166517059093532"></a>void&nbsp;</p>
<p id="p1622101332093532"><a name="p1622101332093532"></a><a name="p1622101332093532"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1629063515093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1154723769093532"><a name="p1154723769093532"></a><a name="p1154723769093532"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p501001776093532"><a name="p501001776093532"></a><a name="p501001776093532"></a>virtual void&nbsp;</p>
<p id="p467583245093532"><a name="p467583245093532"></a><a name="p467583245093532"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1581579896093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1250185650093532"><a name="p1250185650093532"></a><a name="p1250185650093532"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1639480438093532"><a name="p1639480438093532"></a><a name="p1639480438093532"></a>virtual void&nbsp;</p>
<p id="p229533596093532"><a name="p229533596093532"></a><a name="p229533596093532"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1644119675093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p769093104093532"><a name="p769093104093532"></a><a name="p769093104093532"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1314428923093532"><a name="p1314428923093532"></a><a name="p1314428923093532"></a>virtual int64_t&nbsp;</p>
<p id="p2137089189093532"><a name="p2137089189093532"></a><a name="p2137089189093532"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row315231046093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1827707710093532"><a name="p1827707710093532"></a><a name="p1827707710093532"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p463418699093532"><a name="p463418699093532"></a><a name="p463418699093532"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1069591657093532"><a name="p1069591657093532"></a><a name="p1069591657093532"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1359030222093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p36883761093532"><a name="p36883761093532"></a><a name="p36883761093532"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1161228956093532"><a name="p1161228956093532"></a><a name="p1161228956093532"></a>void *&nbsp;</p>
<p id="p825582659093532"><a name="p825582659093532"></a><a name="p825582659093532"></a>Overrides the <strong id="b1201380685093532"><a name="b1201380685093532"></a><a name="b1201380685093532"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1091927790093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1315410015093532"><a name="p1315410015093532"></a><a name="p1315410015093532"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1378094988093532"><a name="p1378094988093532"></a><a name="p1378094988093532"></a>void&nbsp;</p>
<p id="p1043402206093532"><a name="p1043402206093532"></a><a name="p1043402206093532"></a>Overrides the <strong id="b128735159093532"><a name="b128735159093532"></a><a name="b128735159093532"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table132424014093532"></a>
<table><thead align="left"><tr id="row2077180349093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p848086391093532"><a name="p848086391093532"></a><a name="p848086391093532"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p292491684093532"><a name="p292491684093532"></a><a name="p292491684093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1602871269093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p368115731093532"><a name="p368115731093532"></a><a name="p368115731093532"></a><a href="Graphic.md#ga924ce70adcad92d852ba1d1faa441ac8">GetInstance</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p100500638093532"><a name="p100500638093532"></a><a name="p100500638093532"></a>static <a href="OHOS-RootView.md">RootView</a> *&nbsp;</p>
<p id="p839781776093532"><a name="p839781776093532"></a><a name="p839781776093532"></a>Obtains a singleton <strong id="b2076314467093532"><a name="b2076314467093532"></a><a name="b2076314467093532"></a><a href="OHOS-RootView.md">RootView</a></strong> instance. </p>
</td>
</tr>
<tr id="row864905143093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985395366093532"><a name="p1985395366093532"></a><a name="p1985395366093532"></a><a href="Graphic.md#gabb3c193eea516b09f9ed6932b298ab9a">FindSubView</a> (const <a href="OHOS-UIView.md">UIView</a> &amp;parentView, const <a href="OHOS-UIView.md">UIView</a> *subView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1044176903093532"><a name="p1044176903093532"></a><a name="p1044176903093532"></a>static bool&nbsp;</p>
<p id="p1441701237093532"><a name="p1441701237093532"></a><a name="p1441701237093532"></a>Checks whether the target view is one of the child views of the specified parent view. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table51843791093532"></a>
<table><thead align="left"><tr id="row731582966093532"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1420826145093532"><a name="p1420826145093532"></a><a name="p1420826145093532"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p440920364093532"><a name="p440920364093532"></a><a name="p440920364093532"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row6341441093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2083149111093532"><a name="p2083149111093532"></a><a name="p2083149111093532"></a><a href="Graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844248631093532"><a name="p1844248631093532"></a><a name="p1844248631093532"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row227004915093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p753455597093532"><a name="p753455597093532"></a><a name="p753455597093532"></a><a href="Graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p866301939093532"><a name="p866301939093532"></a><a name="p866301939093532"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row571230686093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p57730194093532"><a name="p57730194093532"></a><a name="p57730194093532"></a><a href="Graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p218766314093532"><a name="p218766314093532"></a><a name="p218766314093532"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row1513510086093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1609390152093532"><a name="p1609390152093532"></a><a name="p1609390152093532"></a><a href="Graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510292705093532"><a name="p1510292705093532"></a><a name="p1510292705093532"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row1968975349093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p301453955093532"><a name="p301453955093532"></a><a name="p301453955093532"></a><a href="Graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695592349093532"><a name="p1695592349093532"></a><a name="p1695592349093532"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1285654169093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p103280618093532"><a name="p103280618093532"></a><a name="p103280618093532"></a><a href="Graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1892690506093532"><a name="p1892690506093532"></a><a name="p1892690506093532"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row503632709093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p673197882093532"><a name="p673197882093532"></a><a name="p673197882093532"></a><a href="Graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1767836626093532"><a name="p1767836626093532"></a><a name="p1767836626093532"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1650478644093532"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1313497581093532"><a name="p1313497581093532"></a><a name="p1313497581093532"></a><a href="Graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p893609453093532"><a name="p893609453093532"></a><a name="p893609453093532"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

