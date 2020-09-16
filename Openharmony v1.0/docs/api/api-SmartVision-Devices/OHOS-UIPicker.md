# OHOS::UIPicker<a name="ZH-CN_TOPIC_0000001054479589"></a>

## **Overview**<a name="section2062082636093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines a picker. Multiple texts or numbers can be put into a sliding list for selection. The selected text or numbers are highlighted. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1511572621093534"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1456686268093534"></a>
<table><thead align="left"><tr id="row1629580473093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p10941482093534"><a name="p10941482093534"></a><a name="p10941482093534"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1328235547093534"><a name="p1328235547093534"></a><a name="p1328235547093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1710248959093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1461797061093534"><a name="p1461797061093534"></a><a name="p1461797061093534"></a><a href="OHOS-UIPicker-SelectedListener.md">SelectedListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1132298687093534"><a name="p1132298687093534"></a><a name="p1132298687093534"></a>Defines the listener used by a picker. This listener is triggered when an item is selected after sliding stops. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table783038320093534"></a>
<table><thead align="left"><tr id="row869001098093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p593510003093534"><a name="p593510003093534"></a><a name="p593510003093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2137177372093534"><a name="p2137177372093534"></a><a name="p2137177372093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1810157419093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1076875516093534"><a name="p1076875516093534"></a><a name="p1076875516093534"></a><a href="Graphic.md#ga527215b87f48c8e4a76c1d1d7979b739">UIPicker</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p989022888093534"><a name="p989022888093534"></a><a name="p989022888093534"></a>&nbsp;</p>
<p id="p1740216605093534"><a name="p1740216605093534"></a><a name="p1740216605093534"></a>A constructor used to create a <strong id="b799982792093534"><a name="b799982792093534"></a><a name="b799982792093534"></a><a href="OHOS-UIPicker.md">UIPicker</a></strong> instance. </p>
</td>
</tr>
<tr id="row923023471093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1286549389093534"><a name="p1286549389093534"></a><a name="p1286549389093534"></a><a href="Graphic.md#ga7aa364d1c552eaf8b8be587e03049f59">~UIPicker</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1841038551093534"><a name="p1841038551093534"></a><a name="p1841038551093534"></a>virtual&nbsp;</p>
<p id="p1696291175093534"><a name="p1696291175093534"></a><a name="p1696291175093534"></a>A destructor used to delete the <strong id="b1649482863093534"><a name="b1649482863093534"></a><a name="b1649482863093534"></a><a href="OHOS-UIPicker.md">UIPicker</a></strong> instance. </p>
</td>
</tr>
<tr id="row910634940093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1960784646093534"><a name="p1960784646093534"></a><a name="p1960784646093534"></a><a href="Graphic.md#ga926337be55785de0b32ad57d7ee85c5c">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181423357093534"><a name="p181423357093534"></a><a name="p181423357093534"></a>UIViewType&nbsp;</p>
<p id="p397563113093534"><a name="p397563113093534"></a><a name="p397563113093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1036625035093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1957344288093534"><a name="p1957344288093534"></a><a name="p1957344288093534"></a><a href="Graphic.md#ga3e2a703a10017c789366029b297969ab">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p276486907093534"><a name="p276486907093534"></a><a name="p276486907093534"></a>bool&nbsp;</p>
<p id="p2143086084093534"><a name="p2143086084093534"></a><a name="p2143086084093534"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1269915063093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p351979043093534"><a name="p351979043093534"></a><a name="p351979043093534"></a><a href="Graphic.md#ga419bb15f72b02f009a76a84e1242b37a">SetValues</a> (const char *value[], uint16_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432184198093534"><a name="p1432184198093534"></a><a name="p1432184198093534"></a>bool&nbsp;</p>
<p id="p1182319613093534"><a name="p1182319613093534"></a><a name="p1182319613093534"></a>Sets dynamic text data in the picker by using a string array. </p>
</td>
</tr>
<tr id="row757944962093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051887514093534"><a name="p2051887514093534"></a><a name="p2051887514093534"></a><a href="Graphic.md#gadc27ad0369bad90526a59d0cefdb9697">SetValues</a> (int16_t start, int16_t end)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p221954300093534"><a name="p221954300093534"></a><a name="p221954300093534"></a>bool&nbsp;</p>
<p id="p549221202093534"><a name="p549221202093534"></a><a name="p549221202093534"></a>Sets the numeric data in the picker by using a given numeric range. </p>
</td>
</tr>
<tr id="row1994473816093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1560884082093534"><a name="p1560884082093534"></a><a name="p1560884082093534"></a><a href="Graphic.md#ga81e69c460191bbe3606ac540433178a1">ClearValues</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p286968686093534"><a name="p286968686093534"></a><a name="p286968686093534"></a>virtual void&nbsp;</p>
<p id="p42898135093534"><a name="p42898135093534"></a><a name="p42898135093534"></a>Clears all values in the picker. </p>
</td>
</tr>
<tr id="row2119441306093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p398689942093534"><a name="p398689942093534"></a><a name="p398689942093534"></a><a href="Graphic.md#ga11a0d71430e826f1971744e5ce1c9048">SetFontId</a> (uint8_t backgroundFontId, uint8_t highlightFontId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p953140545093534"><a name="p953140545093534"></a><a name="p953140545093534"></a>void&nbsp;</p>
<p id="p694303997093534"><a name="p694303997093534"></a><a name="p694303997093534"></a>Sets the font IDs of dynamic text, which is the string array set through <a href="Graphic.md#ga419bb15f72b02f009a76a84e1242b37a">SetValues</a>. </p>
</td>
</tr>
<tr id="row1304741654093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p91570509093534"><a name="p91570509093534"></a><a name="p91570509093534"></a><a href="Graphic.md#gaaf111e4de815c455ddc35d200c1de7af">GetBackgroundFontId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p790998319093534"><a name="p790998319093534"></a><a name="p790998319093534"></a>uint16_t&nbsp;</p>
<p id="p1330358771093534"><a name="p1330358771093534"></a><a name="p1330358771093534"></a>Obtains the font ID of the background text. </p>
</td>
</tr>
<tr id="row688409313093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p243474994093534"><a name="p243474994093534"></a><a name="p243474994093534"></a><a href="Graphic.md#ga3a03222a252380aa738186e9c004dc1a">GetHighlightFontId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p272516531093534"><a name="p272516531093534"></a><a name="p272516531093534"></a>uint16_t&nbsp;</p>
<p id="p905111831093534"><a name="p905111831093534"></a><a name="p905111831093534"></a>Obtains the font ID of the highlighted text. </p>
</td>
</tr>
<tr id="row1289444558093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p859498466093534"><a name="p859498466093534"></a><a name="p859498466093534"></a><a href="Graphic.md#ga281508b16585cdf4531e29872486e6c8">SetTextColor</a> (<a href="OHOS-Color32.md">ColorType</a> backgroundColor, <a href="OHOS-Color32.md">ColorType</a> highlightColor)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p847810134093534"><a name="p847810134093534"></a><a name="p847810134093534"></a>void&nbsp;</p>
<p id="p436406442093534"><a name="p436406442093534"></a><a name="p436406442093534"></a>Sets the text color. </p>
</td>
</tr>
<tr id="row374399723093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1300008164093534"><a name="p1300008164093534"></a><a name="p1300008164093534"></a><a href="Graphic.md#ga2acbf79147239f60aafa2c78ccc2ff6d">GetBackgroundTextColor</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p475408728093534"><a name="p475408728093534"></a><a name="p475408728093534"></a><a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1224255131093534"><a name="p1224255131093534"></a><a name="p1224255131093534"></a>Obtains the color of the background text. </p>
</td>
</tr>
<tr id="row2072244071093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1507371573093534"><a name="p1507371573093534"></a><a name="p1507371573093534"></a><a href="Graphic.md#gaf51c8e0d1defb52191bc5f0b2c960695">GetHighlightTextColor</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p959457232093534"><a name="p959457232093534"></a><a name="p959457232093534"></a><a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p609482987093534"><a name="p609482987093534"></a><a name="p609482987093534"></a>Obtains the color of the highlighted text. </p>
</td>
</tr>
<tr id="row1998993989093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2060070804093534"><a name="p2060070804093534"></a><a name="p2060070804093534"></a><a href="Graphic.md#ga07eb2080a6052c19dba2873fcfae2c34">SetSelected</a> (uint16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p488346175093534"><a name="p488346175093534"></a><a name="p488346175093534"></a>bool&nbsp;</p>
<p id="p1377449848093534"><a name="p1377449848093534"></a><a name="p1377449848093534"></a>Sets the index of the item currently selected in the picker. </p>
</td>
</tr>
<tr id="row170268429093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1259172831093534"><a name="p1259172831093534"></a><a name="p1259172831093534"></a><a href="Graphic.md#ga7c9d757790dfaae67fad110577b57ee9">GetSelected</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p103541997093534"><a name="p103541997093534"></a><a name="p103541997093534"></a>uint16_t&nbsp;</p>
<p id="p1436245936093534"><a name="p1436245936093534"></a><a name="p1436245936093534"></a>Obtains the index of the item currently selected in the picker. </p>
</td>
</tr>
<tr id="row943424431093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1986784693093534"><a name="p1986784693093534"></a><a name="p1986784693093534"></a><a href="Graphic.md#ga6a6d9ca48f543f4f6cf6073d6cca359a">SetItemHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1872622181093534"><a name="p1872622181093534"></a><a name="p1872622181093534"></a>void&nbsp;</p>
<p id="p851712789093534"><a name="p851712789093534"></a><a name="p851712789093534"></a>Sets the height of each item in the picker. </p>
</td>
</tr>
<tr id="row1653268956093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p746104983093534"><a name="p746104983093534"></a><a name="p746104983093534"></a><a href="Graphic.md#ga792a345948af532f9c06cd40c05d1a2d">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1682870592093534"><a name="p1682870592093534"></a><a name="p1682870592093534"></a>void&nbsp;</p>
<p id="p307306216093534"><a name="p307306216093534"></a><a name="p307306216093534"></a>Sets the width for this component. </p>
</td>
</tr>
<tr id="row1423252168093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851682695093534"><a name="p1851682695093534"></a><a name="p1851682695093534"></a><a href="Graphic.md#ga167979fe09694b0f0c09e9c676189bea">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1799558438093534"><a name="p1799558438093534"></a><a name="p1799558438093534"></a>void&nbsp;</p>
<p id="p1899764763093534"><a name="p1899764763093534"></a><a name="p1899764763093534"></a>Sets the height for this component. </p>
</td>
</tr>
<tr id="row845532978093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984201550093534"><a name="p984201550093534"></a><a name="p984201550093534"></a><a href="Graphic.md#ga742f27b59ae3c19dfb5d99e84ca19554">SetLoopState</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1177968683093534"><a name="p1177968683093534"></a><a name="p1177968683093534"></a>void&nbsp;</p>
<p id="p543420547093534"><a name="p543420547093534"></a><a name="p543420547093534"></a>Sets whether a picker can slide cyclically. </p>
</td>
</tr>
<tr id="row1202365070093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p7689341093534"><a name="p7689341093534"></a><a name="p7689341093534"></a><a href="Graphic.md#ga70a514c87a883999a93b6c9d3713be61">RegisterSelectedListener</a> (<a href="OHOS-UIPicker-SelectedListener.md">SelectedListener</a> *pickerListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p585116615093534"><a name="p585116615093534"></a><a name="p585116615093534"></a>void&nbsp;</p>
<p id="p699729293093534"><a name="p699729293093534"></a><a name="p699729293093534"></a>Registers a listener for a selected event. </p>
</td>
</tr>
<tr id="row1282287252093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p489492597093534"><a name="p489492597093534"></a><a name="p489492597093534"></a><a href="Graphic.md#gad0c36e1430f8db5571fd92b82d6d6bc1">SetDirect</a> (<a href="Graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a> direct)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1003489162093534"><a name="p1003489162093534"></a><a name="p1003489162093534"></a>void&nbsp;</p>
<p id="p431143266093534"><a name="p431143266093534"></a><a name="p431143266093534"></a>Sets the text direction. </p>
</td>
</tr>
<tr id="row62841510093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2004809351093534"><a name="p2004809351093534"></a><a name="p2004809351093534"></a><a href="Graphic.md#ga564153af81a4a41ceab63622506d25eb">SetTextFormatter</a> (<a href="OHOS-TextFormatter.md">TextFormatter</a> *formatter)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p202796724093534"><a name="p202796724093534"></a><a name="p202796724093534"></a>void&nbsp;</p>
<p id="p1137600328093534"><a name="p1137600328093534"></a><a name="p1137600328093534"></a>Sets the text formatter. </p>
</td>
</tr>
<tr id="row1171207280093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p181008968093534"><a name="p181008968093534"></a><a name="p181008968093534"></a><a href="Graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1524306971093534"><a name="p1524306971093534"></a><a name="p1524306971093534"></a>&nbsp;</p>
<p id="p1654229212093534"><a name="p1654229212093534"></a><a name="p1654229212093534"></a>A default constructor used to create a <strong id="b1316399190093534"><a name="b1316399190093534"></a><a name="b1316399190093534"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row998952239093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p406809433093534"><a name="p406809433093534"></a><a name="p406809433093534"></a><a href="Graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1198954592093534"><a name="p1198954592093534"></a><a name="p1198954592093534"></a>virtual&nbsp;</p>
<p id="p1660131302093534"><a name="p1660131302093534"></a><a name="p1660131302093534"></a>A destructor used to delete the <strong id="b2068067610093534"><a name="b2068067610093534"></a><a name="b2068067610093534"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row584435167093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1271551114093534"><a name="p1271551114093534"></a><a name="p1271551114093534"></a><a href="Graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p788988054093534"><a name="p788988054093534"></a><a name="p788988054093534"></a>UIViewType&nbsp;</p>
<p id="p1822526225093534"><a name="p1822526225093534"></a><a name="p1822526225093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row831147944093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1389737505093534"><a name="p1389737505093534"></a><a name="p1389737505093534"></a><a href="Graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p718291300093534"><a name="p718291300093534"></a><a name="p718291300093534"></a>virtual void&nbsp;</p>
<p id="p1421314777093534"><a name="p1421314777093534"></a><a name="p1421314777093534"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row868445456093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p827949779093534"><a name="p827949779093534"></a><a name="p827949779093534"></a><a href="Graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="OHOS-UIView.md">UIView</a> *prevView, <a href="OHOS-UIView.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2007251715093534"><a name="p2007251715093534"></a><a name="p2007251715093534"></a>virtual void&nbsp;</p>
<p id="p916893285093534"><a name="p916893285093534"></a><a name="p916893285093534"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1249637654093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p376997538093534"><a name="p376997538093534"></a><a name="p376997538093534"></a><a href="Graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p781677368093534"><a name="p781677368093534"></a><a name="p781677368093534"></a>virtual void&nbsp;</p>
<p id="p294580943093534"><a name="p294580943093534"></a><a name="p294580943093534"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row705287083093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p35315083093534"><a name="p35315083093534"></a><a name="p35315083093534"></a><a href="Graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p634676933093534"><a name="p634676933093534"></a><a name="p634676933093534"></a>virtual void&nbsp;</p>
<p id="p642338705093534"><a name="p642338705093534"></a><a name="p642338705093534"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row2102839911093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p840760006093534"><a name="p840760006093534"></a><a name="p840760006093534"></a><a href="Graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929258200093534"><a name="p929258200093534"></a><a name="p929258200093534"></a>virtual void&nbsp;</p>
<p id="p2016763181093534"><a name="p2016763181093534"></a><a name="p2016763181093534"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1822473067093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1491913761093534"><a name="p1491913761093534"></a><a name="p1491913761093534"></a><a href="Graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1194810723093534"><a name="p1194810723093534"></a><a name="p1194810723093534"></a>virtual void&nbsp;</p>
<p id="p184548956093534"><a name="p184548956093534"></a><a name="p184548956093534"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row904550132093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217067421093534"><a name="p1217067421093534"></a><a name="p1217067421093534"></a><a href="Graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1519958093093534"><a name="p1519958093093534"></a><a name="p1519958093093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1952042351093534"><a name="p1952042351093534"></a><a name="p1952042351093534"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1612886054093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1399565463093534"><a name="p1399565463093534"></a><a name="p1399565463093534"></a><a href="Graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p375420934093534"><a name="p375420934093534"></a><a name="p375420934093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1689287248093534"><a name="p1689287248093534"></a><a name="p1689287248093534"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row725964711093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p301583608093534"><a name="p301583608093534"></a><a name="p301583608093534"></a><a href="Graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p421939412093534"><a name="p421939412093534"></a><a name="p421939412093534"></a>void&nbsp;</p>
<p id="p1833793187093534"><a name="p1833793187093534"></a><a name="p1833793187093534"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row142593012093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1728873180093534"><a name="p1728873180093534"></a><a name="p1728873180093534"></a><a href="Graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p634112855093534"><a name="p634112855093534"></a><a name="p634112855093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p364794836093534"><a name="p364794836093534"></a><a name="p364794836093534"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row2116627895093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1385184809093534"><a name="p1385184809093534"></a><a name="p1385184809093534"></a><a href="Graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1806337902093534"><a name="p1806337902093534"></a><a name="p1806337902093534"></a>void&nbsp;</p>
<p id="p1729417111093534"><a name="p1729417111093534"></a><a name="p1729417111093534"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row830103290093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2082510286093534"><a name="p2082510286093534"></a><a name="p2082510286093534"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1501363508093534"><a name="p1501363508093534"></a><a name="p1501363508093534"></a>&nbsp;</p>
<p id="p202308229093534"><a name="p202308229093534"></a><a name="p202308229093534"></a>A default constructor used to create an <strong id="b1596055581093534"><a name="b1596055581093534"></a><a name="b1596055581093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row385745198093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1701050732093534"><a name="p1701050732093534"></a><a name="p1701050732093534"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1579908771093534"><a name="p1579908771093534"></a><a name="p1579908771093534"></a>&nbsp;</p>
<p id="p2035202554093534"><a name="p2035202554093534"></a><a name="p2035202554093534"></a>A constructor used to create an <strong id="b617306568093534"><a name="b617306568093534"></a><a name="b617306568093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1484838136093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000767611093534"><a name="p1000767611093534"></a><a name="p1000767611093534"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1725180096093534"><a name="p1725180096093534"></a><a name="p1725180096093534"></a>virtual&nbsp;</p>
<p id="p523003051093534"><a name="p523003051093534"></a><a name="p523003051093534"></a>A destructor used to delete the <strong id="b976994813093534"><a name="b976994813093534"></a><a name="b976994813093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1284112104093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p434082096093534"><a name="p434082096093534"></a><a name="p434082096093534"></a><a href="Graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904173372093534"><a name="p904173372093534"></a><a name="p904173372093534"></a>virtual void&nbsp;</p>
<p id="p1518173484093534"><a name="p1518173484093534"></a><a name="p1518173484093534"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1330808115093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1977091830093534"><a name="p1977091830093534"></a><a name="p1977091830093534"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p446679737093534"><a name="p446679737093534"></a><a name="p446679737093534"></a>virtual void&nbsp;</p>
<p id="p818910597093534"><a name="p818910597093534"></a><a name="p818910597093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row758595439093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p512614973093534"><a name="p512614973093534"></a><a name="p512614973093534"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p211479671093534"><a name="p211479671093534"></a><a name="p211479671093534"></a>virtual void&nbsp;</p>
<p id="p1458055098093534"><a name="p1458055098093534"></a><a name="p1458055098093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row686206558093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p132256761093534"><a name="p132256761093534"></a><a name="p132256761093534"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2007110607093534"><a name="p2007110607093534"></a><a name="p2007110607093534"></a>void&nbsp;</p>
<p id="p46530708093534"><a name="p46530708093534"></a><a name="p46530708093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row957803363093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1921024790093534"><a name="p1921024790093534"></a><a name="p1921024790093534"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1914510366093534"><a name="p1914510366093534"></a><a name="p1914510366093534"></a>void&nbsp;</p>
<p id="p681976069093534"><a name="p681976069093534"></a><a name="p681976069093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row686257361093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492073772093534"><a name="p1492073772093534"></a><a name="p1492073772093534"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p993441287093534"><a name="p993441287093534"></a><a name="p993441287093534"></a>virtual bool&nbsp;</p>
<p id="p818371922093534"><a name="p818371922093534"></a><a name="p818371922093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row626848716093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1972838488093534"><a name="p1972838488093534"></a><a name="p1972838488093534"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1910892710093534"><a name="p1910892710093534"></a><a name="p1910892710093534"></a>virtual bool&nbsp;</p>
<p id="p347336428093534"><a name="p347336428093534"></a><a name="p347336428093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1544257707093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p458274461093534"><a name="p458274461093534"></a><a name="p458274461093534"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2114026584093534"><a name="p2114026584093534"></a><a name="p2114026584093534"></a>virtual bool&nbsp;</p>
<p id="p6971992093534"><a name="p6971992093534"></a><a name="p6971992093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row217433109093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p988288031093534"><a name="p988288031093534"></a><a name="p988288031093534"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1318126088093534"><a name="p1318126088093534"></a><a name="p1318126088093534"></a>virtual bool&nbsp;</p>
<p id="p1793628784093534"><a name="p1793628784093534"></a><a name="p1793628784093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row36823992093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505809630093534"><a name="p1505809630093534"></a><a name="p1505809630093534"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1114941031093534"><a name="p1114941031093534"></a><a name="p1114941031093534"></a>virtual void&nbsp;</p>
<p id="p1343993451093534"><a name="p1343993451093534"></a><a name="p1343993451093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row1515367217093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p709450436093534"><a name="p709450436093534"></a><a name="p709450436093534"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2038519135093534"><a name="p2038519135093534"></a><a name="p2038519135093534"></a>virtual void&nbsp;</p>
<p id="p1826037679093534"><a name="p1826037679093534"></a><a name="p1826037679093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1956711717093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429902380093534"><a name="p429902380093534"></a><a name="p429902380093534"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2119704046093534"><a name="p2119704046093534"></a><a name="p2119704046093534"></a>virtual void&nbsp;</p>
<p id="p1752669968093534"><a name="p1752669968093534"></a><a name="p1752669968093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1881414537093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p956170116093534"><a name="p956170116093534"></a><a name="p956170116093534"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354364845093534"><a name="p1354364845093534"></a><a name="p1354364845093534"></a>virtual void&nbsp;</p>
<p id="p1333418618093534"><a name="p1333418618093534"></a><a name="p1333418618093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row1871263316093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p897467006093534"><a name="p897467006093534"></a><a name="p897467006093534"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p269509380093534"><a name="p269509380093534"></a><a name="p269509380093534"></a>void&nbsp;</p>
<p id="p1901936576093534"><a name="p1901936576093534"></a><a name="p1901936576093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row681891354093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1256671453093534"><a name="p1256671453093534"></a><a name="p1256671453093534"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1023790266093534"><a name="p1023790266093534"></a><a name="p1023790266093534"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p2027564144093534"><a name="p2027564144093534"></a><a name="p2027564144093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1881494880093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1252905898093534"><a name="p1252905898093534"></a><a name="p1252905898093534"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p161284423093534"><a name="p161284423093534"></a><a name="p161284423093534"></a>void&nbsp;</p>
<p id="p268916393093534"><a name="p268916393093534"></a><a name="p268916393093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1024007475093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790592131093534"><a name="p790592131093534"></a><a name="p790592131093534"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p566472234093534"><a name="p566472234093534"></a><a name="p566472234093534"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p345686365093534"><a name="p345686365093534"></a><a name="p345686365093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1516233351093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p703239728093534"><a name="p703239728093534"></a><a name="p703239728093534"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1991923809093534"><a name="p1991923809093534"></a><a name="p1991923809093534"></a>void&nbsp;</p>
<p id="p1094434554093534"><a name="p1094434554093534"></a><a name="p1094434554093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row360884300093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1141939772093534"><a name="p1141939772093534"></a><a name="p1141939772093534"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1605120993093534"><a name="p1605120993093534"></a><a name="p1605120993093534"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p14020810093534"><a name="p14020810093534"></a><a name="p14020810093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1444190377093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1253731826093534"><a name="p1253731826093534"></a><a name="p1253731826093534"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p328794930093534"><a name="p328794930093534"></a><a name="p328794930093534"></a>void&nbsp;</p>
<p id="p1215450846093534"><a name="p1215450846093534"></a><a name="p1215450846093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1194264893093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1498146050093534"><a name="p1498146050093534"></a><a name="p1498146050093534"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1243263512093534"><a name="p1243263512093534"></a><a name="p1243263512093534"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p906516798093534"><a name="p906516798093534"></a><a name="p906516798093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row113396387093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1586941206093534"><a name="p1586941206093534"></a><a name="p1586941206093534"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p445566188093534"><a name="p445566188093534"></a><a name="p445566188093534"></a>void&nbsp;</p>
<p id="p2090114615093534"><a name="p2090114615093534"></a><a name="p2090114615093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row117066659093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p940417533093534"><a name="p940417533093534"></a><a name="p940417533093534"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p259951259093534"><a name="p259951259093534"></a><a name="p259951259093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p325135560093534"><a name="p325135560093534"></a><a name="p325135560093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1766453408093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p424025888093534"><a name="p424025888093534"></a><a name="p424025888093534"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1357478472093534"><a name="p1357478472093534"></a><a name="p1357478472093534"></a>void&nbsp;</p>
<p id="p358287964093534"><a name="p358287964093534"></a><a name="p358287964093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1755041190093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1730406791093534"><a name="p1730406791093534"></a><a name="p1730406791093534"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1486596892093534"><a name="p1486596892093534"></a><a name="p1486596892093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1612124165093534"><a name="p1612124165093534"></a><a name="p1612124165093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row611577552093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p354647794093534"><a name="p354647794093534"></a><a name="p354647794093534"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868898965093534"><a name="p1868898965093534"></a><a name="p1868898965093534"></a>virtual void&nbsp;</p>
<p id="p1662475133093534"><a name="p1662475133093534"></a><a name="p1662475133093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row934765070093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671260846093534"><a name="p671260846093534"></a><a name="p671260846093534"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p183692992093534"><a name="p183692992093534"></a><a name="p183692992093534"></a>bool&nbsp;</p>
<p id="p1405631695093534"><a name="p1405631695093534"></a><a name="p1405631695093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row74384427093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1998944162093534"><a name="p1998944162093534"></a><a name="p1998944162093534"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p193717108093534"><a name="p193717108093534"></a><a name="p193717108093534"></a>void&nbsp;</p>
<p id="p1625289291093534"><a name="p1625289291093534"></a><a name="p1625289291093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row323455719093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1099128300093534"><a name="p1099128300093534"></a><a name="p1099128300093534"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p122254909093534"><a name="p122254909093534"></a><a name="p122254909093534"></a>bool&nbsp;</p>
<p id="p854960649093534"><a name="p854960649093534"></a><a name="p854960649093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1153424699093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p682184233093534"><a name="p682184233093534"></a><a name="p682184233093534"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1825004282093534"><a name="p1825004282093534"></a><a name="p1825004282093534"></a>void&nbsp;</p>
<p id="p1760078773093534"><a name="p1760078773093534"></a><a name="p1760078773093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row808525199093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1341675130093534"><a name="p1341675130093534"></a><a name="p1341675130093534"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p933575300093534"><a name="p933575300093534"></a><a name="p933575300093534"></a>bool&nbsp;</p>
<p id="p1497417929093534"><a name="p1497417929093534"></a><a name="p1497417929093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1968771240093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453518206093534"><a name="p453518206093534"></a><a name="p453518206093534"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p137207890093534"><a name="p137207890093534"></a><a name="p137207890093534"></a>void&nbsp;</p>
<p id="p1854631136093534"><a name="p1854631136093534"></a><a name="p1854631136093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row769175287093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p697442688093534"><a name="p697442688093534"></a><a name="p697442688093534"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1582688649093534"><a name="p1582688649093534"></a><a name="p1582688649093534"></a>bool&nbsp;</p>
<p id="p1774725176093534"><a name="p1774725176093534"></a><a name="p1774725176093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1286383036093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p735243853093534"><a name="p735243853093534"></a><a name="p735243853093534"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1525059308093534"><a name="p1525059308093534"></a><a name="p1525059308093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1621349502093534"><a name="p1621349502093534"></a><a name="p1621349502093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row111242992093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p322784371093534"><a name="p322784371093534"></a><a name="p322784371093534"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p394088998093534"><a name="p394088998093534"></a><a name="p394088998093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1164258525093534"><a name="p1164258525093534"></a><a name="p1164258525093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1951235583093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p99052740093534"><a name="p99052740093534"></a><a name="p99052740093534"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1984327359093534"><a name="p1984327359093534"></a><a name="p1984327359093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p739795245093534"><a name="p739795245093534"></a><a name="p739795245093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row359695422093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1698085189093534"><a name="p1698085189093534"></a><a name="p1698085189093534"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1740214250093534"><a name="p1740214250093534"></a><a name="p1740214250093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p933191084093534"><a name="p933191084093534"></a><a name="p933191084093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row950839245093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2069351548093534"><a name="p2069351548093534"></a><a name="p2069351548093534"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1130030847093534"><a name="p1130030847093534"></a><a name="p1130030847093534"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p651818962093534"><a name="p651818962093534"></a><a name="p651818962093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1457351175093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1791657271093534"><a name="p1791657271093534"></a><a name="p1791657271093534"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1136273014093534"><a name="p1136273014093534"></a><a name="p1136273014093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1017167368093534"><a name="p1017167368093534"></a><a name="p1017167368093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1645237125093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p672179693093534"><a name="p672179693093534"></a><a name="p672179693093534"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1134237398093534"><a name="p1134237398093534"></a><a name="p1134237398093534"></a>void&nbsp;</p>
<p id="p1375853184093534"><a name="p1375853184093534"></a><a name="p1375853184093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row2017419969093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1689462998093534"><a name="p1689462998093534"></a><a name="p1689462998093534"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1422512284093534"><a name="p1422512284093534"></a><a name="p1422512284093534"></a>virtual int16_t&nbsp;</p>
<p id="p129344399093534"><a name="p129344399093534"></a><a name="p129344399093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row717929970093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p281788672093534"><a name="p281788672093534"></a><a name="p281788672093534"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p407622135093534"><a name="p407622135093534"></a><a name="p407622135093534"></a>virtual int16_t&nbsp;</p>
<p id="p1577687353093534"><a name="p1577687353093534"></a><a name="p1577687353093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1341554226093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1298513423093534"><a name="p1298513423093534"></a><a name="p1298513423093534"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p786565940093534"><a name="p786565940093534"></a><a name="p786565940093534"></a>virtual void&nbsp;</p>
<p id="p1706794879093534"><a name="p1706794879093534"></a><a name="p1706794879093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1341775416093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1725219700093534"><a name="p1725219700093534"></a><a name="p1725219700093534"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p687010488093534"><a name="p687010488093534"></a><a name="p687010488093534"></a>virtual void&nbsp;</p>
<p id="p401175197093534"><a name="p401175197093534"></a><a name="p401175197093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1268161682093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1002427805093534"><a name="p1002427805093534"></a><a name="p1002427805093534"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1461706293093534"><a name="p1461706293093534"></a><a name="p1461706293093534"></a>int16_t&nbsp;</p>
<p id="p430972557093534"><a name="p430972557093534"></a><a name="p430972557093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1551585925093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p486798913093534"><a name="p486798913093534"></a><a name="p486798913093534"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p261496928093534"><a name="p261496928093534"></a><a name="p261496928093534"></a>virtual void&nbsp;</p>
<p id="p336823042093534"><a name="p336823042093534"></a><a name="p336823042093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row341648055093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2037881011093534"><a name="p2037881011093534"></a><a name="p2037881011093534"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012302906093534"><a name="p1012302906093534"></a><a name="p1012302906093534"></a>int16_t&nbsp;</p>
<p id="p1119114725093534"><a name="p1119114725093534"></a><a name="p1119114725093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row765661141093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2057953432093534"><a name="p2057953432093534"></a><a name="p2057953432093534"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p15326264093534"><a name="p15326264093534"></a><a name="p15326264093534"></a>virtual void&nbsp;</p>
<p id="p1070041541093534"><a name="p1070041541093534"></a><a name="p1070041541093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row2034487758093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p417833060093534"><a name="p417833060093534"></a><a name="p417833060093534"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p676975085093534"><a name="p676975085093534"></a><a name="p676975085093534"></a>virtual void&nbsp;</p>
<p id="p1428925142093534"><a name="p1428925142093534"></a><a name="p1428925142093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1222416436093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1849572038093534"><a name="p1849572038093534"></a><a name="p1849572038093534"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2102351574093534"><a name="p2102351574093534"></a><a name="p2102351574093534"></a>bool&nbsp;</p>
<p id="p221102018093534"><a name="p221102018093534"></a><a name="p221102018093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row715290978093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p275350880093534"><a name="p275350880093534"></a><a name="p275350880093534"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695222529093534"><a name="p1695222529093534"></a><a name="p1695222529093534"></a>void&nbsp;</p>
<p id="p1863130685093534"><a name="p1863130685093534"></a><a name="p1863130685093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row847089322093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1430062042093534"><a name="p1430062042093534"></a><a name="p1430062042093534"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p810788305093534"><a name="p810788305093534"></a><a name="p810788305093534"></a>void&nbsp;</p>
<p id="p212038277093534"><a name="p212038277093534"></a><a name="p212038277093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1355507222093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1628773154093534"><a name="p1628773154093534"></a><a name="p1628773154093534"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514173899093534"><a name="p514173899093534"></a><a name="p514173899093534"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p506075548093534"><a name="p506075548093534"></a><a name="p506075548093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1843907284093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1698454807093534"><a name="p1698454807093534"></a><a name="p1698454807093534"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1433759153093534"><a name="p1433759153093534"></a><a name="p1433759153093534"></a>void&nbsp;</p>
<p id="p1945492256093534"><a name="p1945492256093534"></a><a name="p1945492256093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1981908328093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p816521157093534"><a name="p816521157093534"></a><a name="p816521157093534"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p507584376093534"><a name="p507584376093534"></a><a name="p507584376093534"></a>const char *&nbsp;</p>
<p id="p1097989548093534"><a name="p1097989548093534"></a><a name="p1097989548093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1117992674093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1953113083093534"><a name="p1953113083093534"></a><a name="p1953113083093534"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1546617210093534"><a name="p1546617210093534"></a><a name="p1546617210093534"></a>void&nbsp;</p>
<p id="p1873358972093534"><a name="p1873358972093534"></a><a name="p1873358972093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row785554767093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p207720331093534"><a name="p207720331093534"></a><a name="p207720331093534"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1669098723093534"><a name="p1669098723093534"></a><a name="p1669098723093534"></a>int16_t&nbsp;</p>
<p id="p1544938785093534"><a name="p1544938785093534"></a><a name="p1544938785093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row208760059093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p931679695093534"><a name="p931679695093534"></a><a name="p931679695093534"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1197062070093534"><a name="p1197062070093534"></a><a name="p1197062070093534"></a>virtual void&nbsp;</p>
<p id="p1718683973093534"><a name="p1718683973093534"></a><a name="p1718683973093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row172996743093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p472534679093534"><a name="p472534679093534"></a><a name="p472534679093534"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1986577275093534"><a name="p1986577275093534"></a><a name="p1986577275093534"></a>void&nbsp;</p>
<p id="p1782027406093534"><a name="p1782027406093534"></a><a name="p1782027406093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1258415338093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p832675885093534"><a name="p832675885093534"></a><a name="p832675885093534"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p570478372093534"><a name="p570478372093534"></a><a name="p570478372093534"></a>void&nbsp;</p>
<p id="p640938870093534"><a name="p640938870093534"></a><a name="p640938870093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1281965792093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p425586156093534"><a name="p425586156093534"></a><a name="p425586156093534"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510542736093534"><a name="p1510542736093534"></a><a name="p1510542736093534"></a>void&nbsp;</p>
<p id="p1217583624093534"><a name="p1217583624093534"></a><a name="p1217583624093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row2127798256093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1348314114093534"><a name="p1348314114093534"></a><a name="p1348314114093534"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1968065718093534"><a name="p1968065718093534"></a><a name="p1968065718093534"></a>void&nbsp;</p>
<p id="p14365061093534"><a name="p14365061093534"></a><a name="p14365061093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1794783077093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p576314189093534"><a name="p576314189093534"></a><a name="p576314189093534"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1499970463093534"><a name="p1499970463093534"></a><a name="p1499970463093534"></a>void&nbsp;</p>
<p id="p873457116093534"><a name="p873457116093534"></a><a name="p873457116093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1893173101093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p813610402093534"><a name="p813610402093534"></a><a name="p813610402093534"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p324071763093534"><a name="p324071763093534"></a><a name="p324071763093534"></a>void&nbsp;</p>
<p id="p357617030093534"><a name="p357617030093534"></a><a name="p357617030093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row532154883093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1645546949093534"><a name="p1645546949093534"></a><a name="p1645546949093534"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266955111093534"><a name="p1266955111093534"></a><a name="p1266955111093534"></a>void&nbsp;</p>
<p id="p558109996093534"><a name="p558109996093534"></a><a name="p558109996093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row614266063093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1884189004093534"><a name="p1884189004093534"></a><a name="p1884189004093534"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1224594179093534"><a name="p1224594179093534"></a><a name="p1224594179093534"></a>void&nbsp;</p>
<p id="p1167669937093534"><a name="p1167669937093534"></a><a name="p1167669937093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1121810200093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1108202501093534"><a name="p1108202501093534"></a><a name="p1108202501093534"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2140851870093534"><a name="p2140851870093534"></a><a name="p2140851870093534"></a>void&nbsp;</p>
<p id="p2094292024093534"><a name="p2094292024093534"></a><a name="p2094292024093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row845527341093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892021312093534"><a name="p1892021312093534"></a><a name="p1892021312093534"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567162653093534"><a name="p1567162653093534"></a><a name="p1567162653093534"></a>void&nbsp;</p>
<p id="p411504151093534"><a name="p411504151093534"></a><a name="p411504151093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1850833692093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p692835802093534"><a name="p692835802093534"></a><a name="p692835802093534"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p256358927093534"><a name="p256358927093534"></a><a name="p256358927093534"></a>void&nbsp;</p>
<p id="p1026215083093534"><a name="p1026215083093534"></a><a name="p1026215083093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1432303284093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1650872367093534"><a name="p1650872367093534"></a><a name="p1650872367093534"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1092897948093534"><a name="p1092897948093534"></a><a name="p1092897948093534"></a>void&nbsp;</p>
<p id="p787790022093534"><a name="p787790022093534"></a><a name="p787790022093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row631275576093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p732292287093534"><a name="p732292287093534"></a><a name="p732292287093534"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p202480667093534"><a name="p202480667093534"></a><a name="p202480667093534"></a>void&nbsp;</p>
<p id="p113822520093534"><a name="p113822520093534"></a><a name="p113822520093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row388894945093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1015453196093534"><a name="p1015453196093534"></a><a name="p1015453196093534"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681521336093534"><a name="p1681521336093534"></a><a name="p1681521336093534"></a>void&nbsp;</p>
<p id="p1404932016093534"><a name="p1404932016093534"></a><a name="p1404932016093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row981946183093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2126692448093534"><a name="p2126692448093534"></a><a name="p2126692448093534"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p80487990093534"><a name="p80487990093534"></a><a name="p80487990093534"></a>void&nbsp;</p>
<p id="p1943164853093534"><a name="p1943164853093534"></a><a name="p1943164853093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row63078076093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1202830045093534"><a name="p1202830045093534"></a><a name="p1202830045093534"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p701051615093534"><a name="p701051615093534"></a><a name="p701051615093534"></a>virtual void&nbsp;</p>
<p id="p1372347509093534"><a name="p1372347509093534"></a><a name="p1372347509093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row657740924093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1359280246093534"><a name="p1359280246093534"></a><a name="p1359280246093534"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p18765885093534"><a name="p18765885093534"></a><a name="p18765885093534"></a>virtual void&nbsp;</p>
<p id="p365981794093534"><a name="p365981794093534"></a><a name="p365981794093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row94317653093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1733332232093534"><a name="p1733332232093534"></a><a name="p1733332232093534"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2082258648093534"><a name="p2082258648093534"></a><a name="p2082258648093534"></a>virtual int64_t&nbsp;</p>
<p id="p1729818973093534"><a name="p1729818973093534"></a><a name="p1729818973093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row450328257093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p587629044093534"><a name="p587629044093534"></a><a name="p587629044093534"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p594005628093534"><a name="p594005628093534"></a><a name="p594005628093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p709938081093534"><a name="p709938081093534"></a><a name="p709938081093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1119491537093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p960687087093534"><a name="p960687087093534"></a><a name="p960687087093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1207461168093534"><a name="p1207461168093534"></a><a name="p1207461168093534"></a>void *&nbsp;</p>
<p id="p2084639279093534"><a name="p2084639279093534"></a><a name="p2084639279093534"></a>Overrides the <strong id="b1255040569093534"><a name="b1255040569093534"></a><a name="b1255040569093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1066176567093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p733352567093534"><a name="p733352567093534"></a><a name="p733352567093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p14571507093534"><a name="p14571507093534"></a><a name="p14571507093534"></a>void&nbsp;</p>
<p id="p299596274093534"><a name="p299596274093534"></a><a name="p299596274093534"></a>Overrides the <strong id="b810633465093534"><a name="b810633465093534"></a><a name="b810633465093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1435246102093534"></a>
<table><thead align="left"><tr id="row1912918374093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p423209994093534"><a name="p423209994093534"></a><a name="p423209994093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p135277517093534"><a name="p135277517093534"></a><a name="p135277517093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1399804647093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1794960687093534"><a name="p1794960687093534"></a><a name="p1794960687093534"></a><a href="Graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p131406381093534"><a name="p131406381093534"></a><a name="p131406381093534"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1551753890093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p308043887093534"><a name="p308043887093534"></a><a name="p308043887093534"></a><a href="Graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p640638813093534"><a name="p640638813093534"></a><a name="p640638813093534"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row1398397333093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1853387033093534"><a name="p1853387033093534"></a><a name="p1853387033093534"></a><a href="Graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p402438567093534"><a name="p402438567093534"></a><a name="p402438567093534"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row1301547121093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p175721182093534"><a name="p175721182093534"></a><a name="p175721182093534"></a><a href="Graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p873178181093534"><a name="p873178181093534"></a><a name="p873178181093534"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row193440866093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p931876216093534"><a name="p931876216093534"></a><a name="p931876216093534"></a><a href="Graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2088583098093534"><a name="p2088583098093534"></a><a name="p2088583098093534"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1491846738093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1587449922093534"><a name="p1587449922093534"></a><a name="p1587449922093534"></a><a href="Graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1980573870093534"><a name="p1980573870093534"></a><a name="p1980573870093534"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row203304587093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p302779865093534"><a name="p302779865093534"></a><a name="p302779865093534"></a><a href="Graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1575843925093534"><a name="p1575843925093534"></a><a name="p1575843925093534"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row408910742093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1873796722093534"><a name="p1873796722093534"></a><a name="p1873796722093534"></a><a href="Graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1587568704093534"><a name="p1587568704093534"></a><a name="p1587568704093534"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

