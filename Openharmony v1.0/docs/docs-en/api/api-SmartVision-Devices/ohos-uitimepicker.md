# OHOS::UITimePicker<a name="EN-US_TOPIC_0000001054879560"></a>

## **Overview**<a name="section868520065093534"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the time picker. The time is in the format of "hour:minute" or "hour:minute:second". The selected time is highlighted. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section713245785093534"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table786879110093534"></a>
<table><thead align="left"><tr id="row748195873093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p414568704093534"><a name="p414568704093534"></a><a name="p414568704093534"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1910699341093534"><a name="p1910699341093534"></a><a name="p1910699341093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row590652449093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245789827093534"><a name="p1245789827093534"></a><a name="p1245789827093534"></a><a href="ohos-uitimepicker-selectedlistener.md">SelectedListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p802247034093534"><a name="p802247034093534"></a><a name="p802247034093534"></a>Defines the listener used by the time picker. This listener is triggered when an item is selected after sliding stops. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table576394214093534"></a>
<table><thead align="left"><tr id="row994825026093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1184688006093534"><a name="p1184688006093534"></a><a name="p1184688006093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2066579056093534"><a name="p2066579056093534"></a><a name="p2066579056093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row520177287093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p904617074093534"><a name="p904617074093534"></a><a name="p904617074093534"></a><a href="graphic.md#ga125b46b02ee28c0ba6403ef024196b03">UITimePicker</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1860484832093534"><a name="p1860484832093534"></a><a name="p1860484832093534"></a> </p>
<p id="p1020330028093534"><a name="p1020330028093534"></a><a name="p1020330028093534"></a>A constructor used to create a <strong id="b194886880093534"><a name="b194886880093534"></a><a name="b194886880093534"></a><a href="ohos-uitimepicker.md">UITimePicker</a></strong> instance. </p>
</td>
</tr>
<tr id="row1575377474093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1291218228093534"><a name="p1291218228093534"></a><a name="p1291218228093534"></a><a href="graphic.md#gaf5906b1a1389a599c0086f25cfc02fa0">~UITimePicker</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1764542750093534"><a name="p1764542750093534"></a><a name="p1764542750093534"></a>virtual </p>
<p id="p2012291302093534"><a name="p2012291302093534"></a><a name="p2012291302093534"></a>A destructor used to delete the <strong id="b1256831559093534"><a name="b1256831559093534"></a><a name="b1256831559093534"></a><a href="ohos-uitimepicker.md">UITimePicker</a></strong> instance. </p>
</td>
</tr>
<tr id="row64928069093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p988855499093534"><a name="p988855499093534"></a><a name="p988855499093534"></a><a href="graphic.md#gaf4770cfad2f6368b22e9ea581b12aefa">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2135085616093534"><a name="p2135085616093534"></a><a name="p2135085616093534"></a>UIViewType </p>
<p id="p895844043093534"><a name="p895844043093534"></a><a name="p895844043093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row456749129093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p582511910093534"><a name="p582511910093534"></a><a name="p582511910093534"></a><a href="graphic.md#gaecddab27ffd11267d3f613a1cf7f1549">SetSelected</a> (const char *value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1318393237093534"><a name="p1318393237093534"></a><a name="p1318393237093534"></a>bool </p>
<p id="p862842557093534"><a name="p862842557093534"></a><a name="p862842557093534"></a>Sets the time currently selected in the time picker. </p>
</td>
</tr>
<tr id="row1677481597093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p500828043093534"><a name="p500828043093534"></a><a name="p500828043093534"></a><a href="graphic.md#gac8c1732e78fa64af294694b2bbb35366">GetSelectValue</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1446721315093534"><a name="p1446721315093534"></a><a name="p1446721315093534"></a>const char * </p>
<p id="p1533679438093534"><a name="p1533679438093534"></a><a name="p1533679438093534"></a>Obtains the time currently selected in the time picker. </p>
</td>
</tr>
<tr id="row306778400093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p732528702093534"><a name="p732528702093534"></a><a name="p732528702093534"></a><a href="graphic.md#gac6475a538bb4e0e839dd8f9b0e3ae200">GetSelectHour</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1161961493093534"><a name="p1161961493093534"></a><a name="p1161961493093534"></a>const char * </p>
<p id="p674663348093534"><a name="p674663348093534"></a><a name="p674663348093534"></a>Obtains the hour currently selected in the time picker. </p>
</td>
</tr>
<tr id="row1582374978093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p200795929093534"><a name="p200795929093534"></a><a name="p200795929093534"></a><a href="graphic.md#ga0ccecc8d45fdda042ea0667ab9cc1181">GetSelectMinute</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1019478526093534"><a name="p1019478526093534"></a><a name="p1019478526093534"></a>const char * </p>
<p id="p1740133796093534"><a name="p1740133796093534"></a><a name="p1740133796093534"></a>Obtains the minute currently selected in the time picker. </p>
</td>
</tr>
<tr id="row1291255942093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p113850869093534"><a name="p113850869093534"></a><a name="p113850869093534"></a><a href="graphic.md#ga2e02f298f9b9bcf0520ebd2d0ef40677">GetSelectSecond</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p875436776093534"><a name="p875436776093534"></a><a name="p875436776093534"></a>const char * </p>
<p id="p234365055093534"><a name="p234365055093534"></a><a name="p234365055093534"></a>Obtains the second currently selected in the time picker. </p>
</td>
</tr>
<tr id="row143228465093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1935033904093534"><a name="p1935033904093534"></a><a name="p1935033904093534"></a><a href="graphic.md#ga54e8588b0be58272d1fef244c5e9ba27">SetItemHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1937953307093534"><a name="p1937953307093534"></a><a name="p1937953307093534"></a>void </p>
<p id="p1968857012093534"><a name="p1968857012093534"></a><a name="p1968857012093534"></a>Sets the height of each item in the time picker. </p>
</td>
</tr>
<tr id="row570196931093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1991246198093534"><a name="p1991246198093534"></a><a name="p1991246198093534"></a><a href="graphic.md#gaa2402a0538f08fb4d6857c356be7699c">EnableSecond</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p672928935093534"><a name="p672928935093534"></a><a name="p672928935093534"></a>void </p>
<p id="p643722739093534"><a name="p643722739093534"></a><a name="p643722739093534"></a>Sets whether to enable seconds in the time picker. </p>
</td>
</tr>
<tr id="row651814275093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p762985054093534"><a name="p762985054093534"></a><a name="p762985054093534"></a><a href="graphic.md#gab1847d20b4ae671aaa512f978e043ee1">SetTextStyle</a> (uint8_t backgroundFontId, uint8_t highlightFontId, <a href="ohos-color32.md">ColorType</a> backgroundColor, <a href="ohos-color32.md">ColorType</a> highlightColor)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1950509006093534"><a name="p1950509006093534"></a><a name="p1950509006093534"></a>void </p>
<p id="p1923474181093534"><a name="p1923474181093534"></a><a name="p1923474181093534"></a>Sets the text format in the time picker, including the font ID and color. </p>
</td>
</tr>
<tr id="row381384209093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1392855716093534"><a name="p1392855716093534"></a><a name="p1392855716093534"></a><a href="graphic.md#gad8dc3b2df7fe8aed16776a063efc8b4b">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1264335187093534"><a name="p1264335187093534"></a><a name="p1264335187093534"></a>void </p>
<p id="p284068045093534"><a name="p284068045093534"></a><a name="p284068045093534"></a>Sets the width for the time picker. </p>
</td>
</tr>
<tr id="row1359066118093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p686857375093534"><a name="p686857375093534"></a><a name="p686857375093534"></a><a href="graphic.md#ga06667e791f24098f22ef096ee6af77ad">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p685196741093534"><a name="p685196741093534"></a><a name="p685196741093534"></a>void </p>
<p id="p2141075584093534"><a name="p2141075584093534"></a><a name="p2141075584093534"></a>Sets the height for the time picker. </p>
</td>
</tr>
<tr id="row757933887093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p167650123093534"><a name="p167650123093534"></a><a name="p167650123093534"></a><a href="graphic.md#gaa49ecf72e74e9b835c6fc19c701bf454">RegisterSelectedListener</a> (<a href="ohos-uitimepicker-selectedlistener.md">SelectedListener</a> *timePickerListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p873401871093534"><a name="p873401871093534"></a><a name="p873401871093534"></a>void </p>
<p id="p749050208093534"><a name="p749050208093534"></a><a name="p749050208093534"></a>Registers a listener for a selected event. </p>
</td>
</tr>
<tr id="row970060759093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1629518224093534"><a name="p1629518224093534"></a><a name="p1629518224093534"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201758058093534"><a name="p1201758058093534"></a><a name="p1201758058093534"></a> </p>
<p id="p477133520093534"><a name="p477133520093534"></a><a name="p477133520093534"></a>A default constructor used to create a <strong id="b1662913592093534"><a name="b1662913592093534"></a><a name="b1662913592093534"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1186300274093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p320248323093534"><a name="p320248323093534"></a><a name="p320248323093534"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p829021122093534"><a name="p829021122093534"></a><a name="p829021122093534"></a>virtual </p>
<p id="p1903439667093534"><a name="p1903439667093534"></a><a name="p1903439667093534"></a>A destructor used to delete the <strong id="b832997715093534"><a name="b832997715093534"></a><a name="b832997715093534"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1430993220093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1749473070093534"><a name="p1749473070093534"></a><a name="p1749473070093534"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620068033093534"><a name="p620068033093534"></a><a name="p620068033093534"></a>UIViewType </p>
<p id="p1357899448093534"><a name="p1357899448093534"></a><a name="p1357899448093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row591825791093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p452223999093534"><a name="p452223999093534"></a><a name="p452223999093534"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p408581572093534"><a name="p408581572093534"></a><a name="p408581572093534"></a>virtual void </p>
<p id="p1296852707093534"><a name="p1296852707093534"></a><a name="p1296852707093534"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row1977282806093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1847081230093534"><a name="p1847081230093534"></a><a name="p1847081230093534"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481182382093534"><a name="p1481182382093534"></a><a name="p1481182382093534"></a>virtual void </p>
<p id="p1937582866093534"><a name="p1937582866093534"></a><a name="p1937582866093534"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1203046713093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1787904974093534"><a name="p1787904974093534"></a><a name="p1787904974093534"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p363114846093534"><a name="p363114846093534"></a><a name="p363114846093534"></a>virtual void </p>
<p id="p833799355093534"><a name="p833799355093534"></a><a name="p833799355093534"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row1908744637093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1530513678093534"><a name="p1530513678093534"></a><a name="p1530513678093534"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p303078155093534"><a name="p303078155093534"></a><a name="p303078155093534"></a>virtual void </p>
<p id="p322350100093534"><a name="p322350100093534"></a><a name="p322350100093534"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1175345978093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1713613943093534"><a name="p1713613943093534"></a><a name="p1713613943093534"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1660323900093534"><a name="p1660323900093534"></a><a name="p1660323900093534"></a>virtual void </p>
<p id="p1581257857093534"><a name="p1581257857093534"></a><a name="p1581257857093534"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row2109927929093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1850532542093534"><a name="p1850532542093534"></a><a name="p1850532542093534"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2016223698093534"><a name="p2016223698093534"></a><a name="p2016223698093534"></a>virtual void </p>
<p id="p1193907466093534"><a name="p1193907466093534"></a><a name="p1193907466093534"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row1961734571093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1837072871093534"><a name="p1837072871093534"></a><a name="p1837072871093534"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2094745983093534"><a name="p2094745983093534"></a><a name="p2094745983093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1570295668093534"><a name="p1570295668093534"></a><a name="p1570295668093534"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1359439616093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1188254664093534"><a name="p1188254664093534"></a><a name="p1188254664093534"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1895201667093534"><a name="p1895201667093534"></a><a name="p1895201667093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p859847194093534"><a name="p859847194093534"></a><a name="p859847194093534"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row1321638835093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1201251654093534"><a name="p1201251654093534"></a><a name="p1201251654093534"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p602470702093534"><a name="p602470702093534"></a><a name="p602470702093534"></a>void </p>
<p id="p1272213816093534"><a name="p1272213816093534"></a><a name="p1272213816093534"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1783717862093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p655320493093534"><a name="p655320493093534"></a><a name="p655320493093534"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p382806723093534"><a name="p382806723093534"></a><a name="p382806723093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p227032531093534"><a name="p227032531093534"></a><a name="p227032531093534"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row402841574093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1115506480093534"><a name="p1115506480093534"></a><a name="p1115506480093534"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p559946722093534"><a name="p559946722093534"></a><a name="p559946722093534"></a>void </p>
<p id="p1595902266093534"><a name="p1595902266093534"></a><a name="p1595902266093534"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row1511550209093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1316029473093534"><a name="p1316029473093534"></a><a name="p1316029473093534"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1740388979093534"><a name="p1740388979093534"></a><a name="p1740388979093534"></a> </p>
<p id="p1540035545093534"><a name="p1540035545093534"></a><a name="p1540035545093534"></a>A default constructor used to create an <strong id="b841146406093534"><a name="b841146406093534"></a><a name="b841146406093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1155201616093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1942235771093534"><a name="p1942235771093534"></a><a name="p1942235771093534"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1338590845093534"><a name="p1338590845093534"></a><a name="p1338590845093534"></a> </p>
<p id="p1911547717093534"><a name="p1911547717093534"></a><a name="p1911547717093534"></a>A constructor used to create an <strong id="b611686307093534"><a name="b611686307093534"></a><a name="b611686307093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1313833469093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p413759508093534"><a name="p413759508093534"></a><a name="p413759508093534"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p999646889093534"><a name="p999646889093534"></a><a name="p999646889093534"></a>virtual </p>
<p id="p2049505366093534"><a name="p2049505366093534"></a><a name="p2049505366093534"></a>A destructor used to delete the <strong id="b1551768923093534"><a name="b1551768923093534"></a><a name="b1551768923093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row195788005093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p189705083093534"><a name="p189705083093534"></a><a name="p189705083093534"></a><a href="graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1157216539093534"><a name="p1157216539093534"></a><a name="p1157216539093534"></a>virtual bool </p>
<p id="p1911416626093534"><a name="p1911416626093534"></a><a name="p1911416626093534"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row16143034093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1340025772093534"><a name="p1340025772093534"></a><a name="p1340025772093534"></a><a href="graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278492943093534"><a name="p278492943093534"></a><a name="p278492943093534"></a>virtual void </p>
<p id="p116479413093534"><a name="p116479413093534"></a><a name="p116479413093534"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row414982806093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1794963099093534"><a name="p1794963099093534"></a><a name="p1794963099093534"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1457061161093534"><a name="p1457061161093534"></a><a name="p1457061161093534"></a>virtual void </p>
<p id="p1355978566093534"><a name="p1355978566093534"></a><a name="p1355978566093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1039422761093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1055261782093534"><a name="p1055261782093534"></a><a name="p1055261782093534"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1935931967093534"><a name="p1935931967093534"></a><a name="p1935931967093534"></a>virtual void </p>
<p id="p1432719523093534"><a name="p1432719523093534"></a><a name="p1432719523093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row904115675093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422700918093534"><a name="p422700918093534"></a><a name="p422700918093534"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1129460946093534"><a name="p1129460946093534"></a><a name="p1129460946093534"></a>void </p>
<p id="p1415553354093534"><a name="p1415553354093534"></a><a name="p1415553354093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row367969258093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1650434187093534"><a name="p1650434187093534"></a><a name="p1650434187093534"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2110215443093534"><a name="p2110215443093534"></a><a name="p2110215443093534"></a>void </p>
<p id="p1743294311093534"><a name="p1743294311093534"></a><a name="p1743294311093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1222477722093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p316063876093534"><a name="p316063876093534"></a><a name="p316063876093534"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2059041193093534"><a name="p2059041193093534"></a><a name="p2059041193093534"></a>virtual bool </p>
<p id="p966268947093534"><a name="p966268947093534"></a><a name="p966268947093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1180177630093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1112355283093534"><a name="p1112355283093534"></a><a name="p1112355283093534"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1573033704093534"><a name="p1573033704093534"></a><a name="p1573033704093534"></a>virtual bool </p>
<p id="p1655102263093534"><a name="p1655102263093534"></a><a name="p1655102263093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1694317370093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1150738301093534"><a name="p1150738301093534"></a><a name="p1150738301093534"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1692009223093534"><a name="p1692009223093534"></a><a name="p1692009223093534"></a>virtual bool </p>
<p id="p917242850093534"><a name="p917242850093534"></a><a name="p917242850093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1158297425093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1878427225093534"><a name="p1878427225093534"></a><a name="p1878427225093534"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p304713742093534"><a name="p304713742093534"></a><a name="p304713742093534"></a>virtual bool </p>
<p id="p7505377093534"><a name="p7505377093534"></a><a name="p7505377093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row471101207093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244831518093534"><a name="p1244831518093534"></a><a name="p1244831518093534"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p478006316093534"><a name="p478006316093534"></a><a name="p478006316093534"></a>virtual void </p>
<p id="p1848170148093534"><a name="p1848170148093534"></a><a name="p1848170148093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row965167201093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1097945772093534"><a name="p1097945772093534"></a><a name="p1097945772093534"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1961248315093534"><a name="p1961248315093534"></a><a name="p1961248315093534"></a>virtual void </p>
<p id="p1279719103093534"><a name="p1279719103093534"></a><a name="p1279719103093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row2089317813093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1639292346093534"><a name="p1639292346093534"></a><a name="p1639292346093534"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1256580708093534"><a name="p1256580708093534"></a><a name="p1256580708093534"></a>virtual void </p>
<p id="p1238818433093534"><a name="p1238818433093534"></a><a name="p1238818433093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row869994828093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1778737693093534"><a name="p1778737693093534"></a><a name="p1778737693093534"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1583450179093534"><a name="p1583450179093534"></a><a name="p1583450179093534"></a>virtual void </p>
<p id="p1102489398093534"><a name="p1102489398093534"></a><a name="p1102489398093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row517016575093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p371968973093534"><a name="p371968973093534"></a><a name="p371968973093534"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p308059451093534"><a name="p308059451093534"></a><a name="p308059451093534"></a>void </p>
<p id="p6020227093534"><a name="p6020227093534"></a><a name="p6020227093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1424464203093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p927431647093534"><a name="p927431647093534"></a><a name="p927431647093534"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1996742722093534"><a name="p1996742722093534"></a><a name="p1996742722093534"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p20596576093534"><a name="p20596576093534"></a><a name="p20596576093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row647089416093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p229639676093534"><a name="p229639676093534"></a><a name="p229639676093534"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1200566621093534"><a name="p1200566621093534"></a><a name="p1200566621093534"></a>void </p>
<p id="p1342348847093534"><a name="p1342348847093534"></a><a name="p1342348847093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1569607872093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p176022683093534"><a name="p176022683093534"></a><a name="p176022683093534"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1643165630093534"><a name="p1643165630093534"></a><a name="p1643165630093534"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p229669465093534"><a name="p229669465093534"></a><a name="p229669465093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row560400015093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1623496399093534"><a name="p1623496399093534"></a><a name="p1623496399093534"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1688252251093534"><a name="p1688252251093534"></a><a name="p1688252251093534"></a>void </p>
<p id="p106533323093534"><a name="p106533323093534"></a><a name="p106533323093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1656020501093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1159751164093534"><a name="p1159751164093534"></a><a name="p1159751164093534"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p206241707093534"><a name="p206241707093534"></a><a name="p206241707093534"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p771535753093534"><a name="p771535753093534"></a><a name="p771535753093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row373250145093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1095680257093534"><a name="p1095680257093534"></a><a name="p1095680257093534"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p509862011093534"><a name="p509862011093534"></a><a name="p509862011093534"></a>void </p>
<p id="p1947648130093534"><a name="p1947648130093534"></a><a name="p1947648130093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row22317161093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p156184522093534"><a name="p156184522093534"></a><a name="p156184522093534"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1218636087093534"><a name="p1218636087093534"></a><a name="p1218636087093534"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1204530183093534"><a name="p1204530183093534"></a><a name="p1204530183093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1029246954093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1349060476093534"><a name="p1349060476093534"></a><a name="p1349060476093534"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p484337572093534"><a name="p484337572093534"></a><a name="p484337572093534"></a>void </p>
<p id="p209512081093534"><a name="p209512081093534"></a><a name="p209512081093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row989034597093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2111769374093534"><a name="p2111769374093534"></a><a name="p2111769374093534"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96849127093534"><a name="p96849127093534"></a><a name="p96849127093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p315431856093534"><a name="p315431856093534"></a><a name="p315431856093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1466426291093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p906389856093534"><a name="p906389856093534"></a><a name="p906389856093534"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p710333380093534"><a name="p710333380093534"></a><a name="p710333380093534"></a>void </p>
<p id="p2028785752093534"><a name="p2028785752093534"></a><a name="p2028785752093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row956518132093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p641034765093534"><a name="p641034765093534"></a><a name="p641034765093534"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p111688631093534"><a name="p111688631093534"></a><a name="p111688631093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p276859543093534"><a name="p276859543093534"></a><a name="p276859543093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row2133159801093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790712271093534"><a name="p790712271093534"></a><a name="p790712271093534"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p919543074093534"><a name="p919543074093534"></a><a name="p919543074093534"></a>virtual void </p>
<p id="p1018472229093534"><a name="p1018472229093534"></a><a name="p1018472229093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row115279916093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p93330593093534"><a name="p93330593093534"></a><a name="p93330593093534"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1884248964093534"><a name="p1884248964093534"></a><a name="p1884248964093534"></a>bool </p>
<p id="p1776734432093534"><a name="p1776734432093534"></a><a name="p1776734432093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1187609946093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1043331985093534"><a name="p1043331985093534"></a><a name="p1043331985093534"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p374939274093534"><a name="p374939274093534"></a><a name="p374939274093534"></a>void </p>
<p id="p178918029093534"><a name="p178918029093534"></a><a name="p178918029093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row600960819093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1096366291093534"><a name="p1096366291093534"></a><a name="p1096366291093534"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p880104706093534"><a name="p880104706093534"></a><a name="p880104706093534"></a>bool </p>
<p id="p2106225647093534"><a name="p2106225647093534"></a><a name="p2106225647093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1570667966093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p36447298093534"><a name="p36447298093534"></a><a name="p36447298093534"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1462602464093534"><a name="p1462602464093534"></a><a name="p1462602464093534"></a>void </p>
<p id="p496350485093534"><a name="p496350485093534"></a><a name="p496350485093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row114904739093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1307127848093534"><a name="p1307127848093534"></a><a name="p1307127848093534"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91284092093534"><a name="p91284092093534"></a><a name="p91284092093534"></a>bool </p>
<p id="p1938140221093534"><a name="p1938140221093534"></a><a name="p1938140221093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row231595093093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p746783109093534"><a name="p746783109093534"></a><a name="p746783109093534"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1883426709093534"><a name="p1883426709093534"></a><a name="p1883426709093534"></a>void </p>
<p id="p308555692093534"><a name="p308555692093534"></a><a name="p308555692093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row551053204093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1464750414093534"><a name="p1464750414093534"></a><a name="p1464750414093534"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1638671378093534"><a name="p1638671378093534"></a><a name="p1638671378093534"></a>bool </p>
<p id="p1751007988093534"><a name="p1751007988093534"></a><a name="p1751007988093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1647251102093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p270903574093534"><a name="p270903574093534"></a><a name="p270903574093534"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1834306945093534"><a name="p1834306945093534"></a><a name="p1834306945093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p402929178093534"><a name="p402929178093534"></a><a name="p402929178093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1286340351093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2027423556093534"><a name="p2027423556093534"></a><a name="p2027423556093534"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p561110375093534"><a name="p561110375093534"></a><a name="p561110375093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p2020106822093534"><a name="p2020106822093534"></a><a name="p2020106822093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1030032532093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973060139093534"><a name="p973060139093534"></a><a name="p973060139093534"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140392100093534"><a name="p140392100093534"></a><a name="p140392100093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1058189675093534"><a name="p1058189675093534"></a><a name="p1058189675093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row8803551093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1859190868093534"><a name="p1859190868093534"></a><a name="p1859190868093534"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1319124672093534"><a name="p1319124672093534"></a><a name="p1319124672093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p274015618093534"><a name="p274015618093534"></a><a name="p274015618093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1058432973093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p991115961093534"><a name="p991115961093534"></a><a name="p991115961093534"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1341699707093534"><a name="p1341699707093534"></a><a name="p1341699707093534"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1230531498093534"><a name="p1230531498093534"></a><a name="p1230531498093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1543285644093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1951112117093534"><a name="p1951112117093534"></a><a name="p1951112117093534"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1042039237093534"><a name="p1042039237093534"></a><a name="p1042039237093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1958453566093534"><a name="p1958453566093534"></a><a name="p1958453566093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row768853600093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p46596989093534"><a name="p46596989093534"></a><a name="p46596989093534"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1793847681093534"><a name="p1793847681093534"></a><a name="p1793847681093534"></a>void </p>
<p id="p2096580390093534"><a name="p2096580390093534"></a><a name="p2096580390093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row87753209093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616181927093534"><a name="p1616181927093534"></a><a name="p1616181927093534"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p867006696093534"><a name="p867006696093534"></a><a name="p867006696093534"></a>virtual int16_t </p>
<p id="p2111038976093534"><a name="p2111038976093534"></a><a name="p2111038976093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row2106724801093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p648568857093534"><a name="p648568857093534"></a><a name="p648568857093534"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p399571359093534"><a name="p399571359093534"></a><a name="p399571359093534"></a>virtual int16_t </p>
<p id="p2011924223093534"><a name="p2011924223093534"></a><a name="p2011924223093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row2121429445093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1977261073093534"><a name="p1977261073093534"></a><a name="p1977261073093534"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1458855577093534"><a name="p1458855577093534"></a><a name="p1458855577093534"></a>virtual void </p>
<p id="p1696879542093534"><a name="p1696879542093534"></a><a name="p1696879542093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row2146423531093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p536625366093534"><a name="p536625366093534"></a><a name="p536625366093534"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1693202627093534"><a name="p1693202627093534"></a><a name="p1693202627093534"></a>virtual void </p>
<p id="p413253007093534"><a name="p413253007093534"></a><a name="p413253007093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1953751240093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p281311992093534"><a name="p281311992093534"></a><a name="p281311992093534"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226902294093534"><a name="p1226902294093534"></a><a name="p1226902294093534"></a>int16_t </p>
<p id="p1484793174093534"><a name="p1484793174093534"></a><a name="p1484793174093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1446751320093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p755606243093534"><a name="p755606243093534"></a><a name="p755606243093534"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2139024980093534"><a name="p2139024980093534"></a><a name="p2139024980093534"></a>virtual void </p>
<p id="p1734961577093534"><a name="p1734961577093534"></a><a name="p1734961577093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1829413772093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1483747983093534"><a name="p1483747983093534"></a><a name="p1483747983093534"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2024536138093534"><a name="p2024536138093534"></a><a name="p2024536138093534"></a>int16_t </p>
<p id="p1124860426093534"><a name="p1124860426093534"></a><a name="p1124860426093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1138831622093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p167977461093534"><a name="p167977461093534"></a><a name="p167977461093534"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p938123748093534"><a name="p938123748093534"></a><a name="p938123748093534"></a>virtual void </p>
<p id="p1876850835093534"><a name="p1876850835093534"></a><a name="p1876850835093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1587817608093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1535558267093534"><a name="p1535558267093534"></a><a name="p1535558267093534"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p336110955093534"><a name="p336110955093534"></a><a name="p336110955093534"></a>virtual void </p>
<p id="p1497251494093534"><a name="p1497251494093534"></a><a name="p1497251494093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1405453411093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419229877093534"><a name="p419229877093534"></a><a name="p419229877093534"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069494615093534"><a name="p2069494615093534"></a><a name="p2069494615093534"></a>bool </p>
<p id="p1154602812093534"><a name="p1154602812093534"></a><a name="p1154602812093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row667680509093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1487721724093534"><a name="p1487721724093534"></a><a name="p1487721724093534"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p303555233093534"><a name="p303555233093534"></a><a name="p303555233093534"></a>void </p>
<p id="p1610433994093534"><a name="p1610433994093534"></a><a name="p1610433994093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1773533067093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p518342109093534"><a name="p518342109093534"></a><a name="p518342109093534"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p146198068093534"><a name="p146198068093534"></a><a name="p146198068093534"></a>void </p>
<p id="p263023630093534"><a name="p263023630093534"></a><a name="p263023630093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1665054684093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p380675818093534"><a name="p380675818093534"></a><a name="p380675818093534"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1706994474093534"><a name="p1706994474093534"></a><a name="p1706994474093534"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p467728292093534"><a name="p467728292093534"></a><a name="p467728292093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row856090661093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220247295093534"><a name="p1220247295093534"></a><a name="p1220247295093534"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p626827912093534"><a name="p626827912093534"></a><a name="p626827912093534"></a>void </p>
<p id="p1838253812093534"><a name="p1838253812093534"></a><a name="p1838253812093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1312370108093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205751291093534"><a name="p205751291093534"></a><a name="p205751291093534"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510178128093534"><a name="p1510178128093534"></a><a name="p1510178128093534"></a>const char * </p>
<p id="p2057676495093534"><a name="p2057676495093534"></a><a name="p2057676495093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row2122507730093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419998209093534"><a name="p419998209093534"></a><a name="p419998209093534"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367964131093534"><a name="p1367964131093534"></a><a name="p1367964131093534"></a>void </p>
<p id="p2018421008093534"><a name="p2018421008093534"></a><a name="p2018421008093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row796608407093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p363791512093534"><a name="p363791512093534"></a><a name="p363791512093534"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1054598641093534"><a name="p1054598641093534"></a><a name="p1054598641093534"></a>int16_t </p>
<p id="p1142593117093534"><a name="p1142593117093534"></a><a name="p1142593117093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1689576896093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p8823524093534"><a name="p8823524093534"></a><a name="p8823524093534"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1663768546093534"><a name="p1663768546093534"></a><a name="p1663768546093534"></a>virtual void </p>
<p id="p1606453675093534"><a name="p1606453675093534"></a><a name="p1606453675093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1028996423093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p114902827093534"><a name="p114902827093534"></a><a name="p114902827093534"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705365318093534"><a name="p1705365318093534"></a><a name="p1705365318093534"></a>void </p>
<p id="p750995638093534"><a name="p750995638093534"></a><a name="p750995638093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row29494414093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p877157786093534"><a name="p877157786093534"></a><a name="p877157786093534"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403485082093534"><a name="p1403485082093534"></a><a name="p1403485082093534"></a>void </p>
<p id="p744130348093534"><a name="p744130348093534"></a><a name="p744130348093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1275015582093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p375706014093534"><a name="p375706014093534"></a><a name="p375706014093534"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p30680445093534"><a name="p30680445093534"></a><a name="p30680445093534"></a>void </p>
<p id="p1819177523093534"><a name="p1819177523093534"></a><a name="p1819177523093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row765618859093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p434998207093534"><a name="p434998207093534"></a><a name="p434998207093534"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1941736860093534"><a name="p1941736860093534"></a><a name="p1941736860093534"></a>void </p>
<p id="p258116275093534"><a name="p258116275093534"></a><a name="p258116275093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1663188807093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p711476020093534"><a name="p711476020093534"></a><a name="p711476020093534"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p675457794093534"><a name="p675457794093534"></a><a name="p675457794093534"></a>void </p>
<p id="p609506975093534"><a name="p609506975093534"></a><a name="p609506975093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1204552542093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p164106504093534"><a name="p164106504093534"></a><a name="p164106504093534"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1491585298093534"><a name="p1491585298093534"></a><a name="p1491585298093534"></a>void </p>
<p id="p237903949093534"><a name="p237903949093534"></a><a name="p237903949093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1960284898093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1599573739093534"><a name="p1599573739093534"></a><a name="p1599573739093534"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1353709862093534"><a name="p1353709862093534"></a><a name="p1353709862093534"></a>void </p>
<p id="p1952902755093534"><a name="p1952902755093534"></a><a name="p1952902755093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1337846255093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1300666881093534"><a name="p1300666881093534"></a><a name="p1300666881093534"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1350894241093534"><a name="p1350894241093534"></a><a name="p1350894241093534"></a>void </p>
<p id="p622259328093534"><a name="p622259328093534"></a><a name="p622259328093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row389104187093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1440318394093534"><a name="p1440318394093534"></a><a name="p1440318394093534"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1483683126093534"><a name="p1483683126093534"></a><a name="p1483683126093534"></a>void </p>
<p id="p797140098093534"><a name="p797140098093534"></a><a name="p797140098093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1527763628093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p804121863093534"><a name="p804121863093534"></a><a name="p804121863093534"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1077781500093534"><a name="p1077781500093534"></a><a name="p1077781500093534"></a>void </p>
<p id="p1755526232093534"><a name="p1755526232093534"></a><a name="p1755526232093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row92380289093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2140806007093534"><a name="p2140806007093534"></a><a name="p2140806007093534"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p770065883093534"><a name="p770065883093534"></a><a name="p770065883093534"></a>void </p>
<p id="p787065423093534"><a name="p787065423093534"></a><a name="p787065423093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1995354682093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1812624507093534"><a name="p1812624507093534"></a><a name="p1812624507093534"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514858570093534"><a name="p514858570093534"></a><a name="p514858570093534"></a>void </p>
<p id="p1876354291093534"><a name="p1876354291093534"></a><a name="p1876354291093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row453141379093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p875707518093534"><a name="p875707518093534"></a><a name="p875707518093534"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p73597042093534"><a name="p73597042093534"></a><a name="p73597042093534"></a>void </p>
<p id="p2075747474093534"><a name="p2075747474093534"></a><a name="p2075747474093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row2090023632093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1778355765093534"><a name="p1778355765093534"></a><a name="p1778355765093534"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1104425752093534"><a name="p1104425752093534"></a><a name="p1104425752093534"></a>void </p>
<p id="p1931844157093534"><a name="p1931844157093534"></a><a name="p1931844157093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row64415428093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1533011787093534"><a name="p1533011787093534"></a><a name="p1533011787093534"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1084160142093534"><a name="p1084160142093534"></a><a name="p1084160142093534"></a>void </p>
<p id="p487573268093534"><a name="p487573268093534"></a><a name="p487573268093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1430762967093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1275624093534"><a name="p1275624093534"></a><a name="p1275624093534"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p874657130093534"><a name="p874657130093534"></a><a name="p874657130093534"></a>virtual void </p>
<p id="p1227037616093534"><a name="p1227037616093534"></a><a name="p1227037616093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row229986079093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p230140140093534"><a name="p230140140093534"></a><a name="p230140140093534"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1356376157093534"><a name="p1356376157093534"></a><a name="p1356376157093534"></a>virtual void </p>
<p id="p1289646075093534"><a name="p1289646075093534"></a><a name="p1289646075093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row900236231093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p175508868093534"><a name="p175508868093534"></a><a name="p175508868093534"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p368033225093534"><a name="p368033225093534"></a><a name="p368033225093534"></a>virtual int64_t </p>
<p id="p1359665338093534"><a name="p1359665338093534"></a><a name="p1359665338093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row874123623093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1553871914093534"><a name="p1553871914093534"></a><a name="p1553871914093534"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1713602202093534"><a name="p1713602202093534"></a><a name="p1713602202093534"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p992948435093534"><a name="p992948435093534"></a><a name="p992948435093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1014391556093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2002829835093534"><a name="p2002829835093534"></a><a name="p2002829835093534"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1053225917093534"><a name="p1053225917093534"></a><a name="p1053225917093534"></a>void * </p>
<p id="p579261208093534"><a name="p579261208093534"></a><a name="p579261208093534"></a>Overrides the <strong id="b967567009093534"><a name="b967567009093534"></a><a name="b967567009093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1186698100093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p660166487093534"><a name="p660166487093534"></a><a name="p660166487093534"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p512882728093534"><a name="p512882728093534"></a><a name="p512882728093534"></a>void </p>
<p id="p1037320537093534"><a name="p1037320537093534"></a><a name="p1037320537093534"></a>Overrides the <strong id="b1780820485093534"><a name="b1780820485093534"></a><a name="b1780820485093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1933328308093534"></a>
<table><thead align="left"><tr id="row1838849556093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1872673482093534"><a name="p1872673482093534"></a><a name="p1872673482093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1880065760093534"><a name="p1880065760093534"></a><a name="p1880065760093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1233605018093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1178290073093534"><a name="p1178290073093534"></a><a name="p1178290073093534"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1245471195093534"><a name="p1245471195093534"></a><a name="p1245471195093534"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1750466080093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p385187515093534"><a name="p385187515093534"></a><a name="p385187515093534"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1108706763093534"><a name="p1108706763093534"></a><a name="p1108706763093534"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row865768334093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p814265334093534"><a name="p814265334093534"></a><a name="p814265334093534"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1770811546093534"><a name="p1770811546093534"></a><a name="p1770811546093534"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row23166809093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1692269713093534"><a name="p1692269713093534"></a><a name="p1692269713093534"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p909365483093534"><a name="p909365483093534"></a><a name="p909365483093534"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row895867315093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p740056376093534"><a name="p740056376093534"></a><a name="p740056376093534"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1507964214093534"><a name="p1507964214093534"></a><a name="p1507964214093534"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1561484111093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1215213623093534"><a name="p1215213623093534"></a><a name="p1215213623093534"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p854344884093534"><a name="p854344884093534"></a><a name="p854344884093534"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1116470303093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1757749563093534"><a name="p1757749563093534"></a><a name="p1757749563093534"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p555323400093534"><a name="p555323400093534"></a><a name="p555323400093534"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row261925208093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p670518162093534"><a name="p670518162093534"></a><a name="p670518162093534"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1348991312093534"><a name="p1348991312093534"></a><a name="p1348991312093534"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

