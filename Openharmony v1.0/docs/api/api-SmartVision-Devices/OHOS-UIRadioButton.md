# OHOS::UIRadioButton<a name="ZH-CN_TOPIC_0000001054879558"></a>

## **Overview**<a name="section265241864093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents a radio button. 

Only one option can be selected with the radio button.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1717327259093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table7422386093534"></a>
<table><thead align="left"><tr id="row958943742093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p163573762093534"><a name="p163573762093534"></a><a name="p163573762093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2058460265093534"><a name="p2058460265093534"></a><a name="p2058460265093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row398248062093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793307758093534"><a name="p793307758093534"></a><a name="p793307758093534"></a><a href="Graphic.md#gaae79b6ffd2b156a8d42263a322985284">UIRadioButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1960154791093534"><a name="p1960154791093534"></a><a name="p1960154791093534"></a>&nbsp;</p>
<p id="p55347725093534"><a name="p55347725093534"></a><a name="p55347725093534"></a>A constructor used to create a <strong id="b2061451946093534"><a name="b2061451946093534"></a><a name="b2061451946093534"></a><a href="OHOS-UIRadioButton.md">UIRadioButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row1638593250093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1501971754093534"><a name="p1501971754093534"></a><a name="p1501971754093534"></a><a href="Graphic.md#ga9b48f8664f04f08b94dca2e0b3821595">UIRadioButton</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1638849307093534"><a name="p1638849307093534"></a><a name="p1638849307093534"></a> &nbsp;</p>
<p id="p154942467093534"><a name="p154942467093534"></a><a name="p154942467093534"></a>Default constructor. </p>
</td>
</tr>
<tr id="row1171420714093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p254883662093534"><a name="p254883662093534"></a><a name="p254883662093534"></a><a href="Graphic.md#ga1b9fbd5840829e912aa4013a343e7b36">~UIRadioButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p34406863093534"><a name="p34406863093534"></a><a name="p34406863093534"></a>virtual&nbsp;</p>
<p id="p1267982915093534"><a name="p1267982915093534"></a><a name="p1267982915093534"></a>A destructor used to delete the <strong id="b578364736093534"><a name="b578364736093534"></a><a name="b578364736093534"></a><a href="OHOS-UIRadioButton.md">UIRadioButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row259199580093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1895706861093534"><a name="p1895706861093534"></a><a name="p1895706861093534"></a><a href="Graphic.md#ga2efe6a87345903726c721fc7a9ed4365">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1152333093534"><a name="p1152333093534"></a><a name="p1152333093534"></a>UIViewType&nbsp;</p>
<p id="p399080486093534"><a name="p399080486093534"></a><a name="p399080486093534"></a>Obtains the component type. </p>
</td>
</tr>
<tr id="row1578849073093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2091964633093534"><a name="p2091964633093534"></a><a name="p2091964633093534"></a><a href="Graphic.md#gade9069f6e553c6c43f7684e835b584e5">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p962807182093534"><a name="p962807182093534"></a><a name="p962807182093534"></a>bool&nbsp;</p>
<p id="p1895059438093534"><a name="p1895059438093534"></a><a name="p1895059438093534"></a>Do something before draw, this function will be invoked mainly to check if this view need to cover invalidate area so render manager can decide which layer to draw firstly. </p>
</td>
</tr>
<tr id="row1265598724093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1302680723093534"><a name="p1302680723093534"></a><a name="p1302680723093534"></a><a href="Graphic.md#ga7b6849c94b9d8b90cbbe890790fedf1e">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9837626093534"><a name="p9837626093534"></a><a name="p9837626093534"></a>void&nbsp;</p>
<p id="p1725222724093534"><a name="p1725222724093534"></a><a name="p1725222724093534"></a>Executes the click event action OnClickEvent will reverse the selected state of checkbox. Example: If the check box is selected, the checkbox status is changed to Unselected after the click action is taken. </p>
</td>
</tr>
<tr id="row1498921383093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1614496648093534"><a name="p1614496648093534"></a><a name="p1614496648093534"></a><a href="Graphic.md#gad56eb918dbfec65f8f596572a9911286">SetName</a> (const char *name)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p466642045093534"><a name="p466642045093534"></a><a name="p466642045093534"></a>void&nbsp;</p>
<p id="p1995143014093534"><a name="p1995143014093534"></a><a name="p1995143014093534"></a>Sets the name for this radio button. </p>
</td>
</tr>
<tr id="row6847919093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p111329614093534"><a name="p111329614093534"></a><a name="p111329614093534"></a><a href="Graphic.md#ga7d2125ee509f1555888549277f31a7a7">GetName</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1610251740093534"><a name="p1610251740093534"></a><a name="p1610251740093534"></a>const char *&nbsp;</p>
<p id="p457859307093534"><a name="p457859307093534"></a><a name="p457859307093534"></a>Obtains the name of this radio button. </p>
</td>
</tr>
<tr id="row727373013093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p968139619093534"><a name="p968139619093534"></a><a name="p968139619093534"></a><a href="Graphic.md#ga811085fbe237690f21a95e7df2a7c45f">UICheckBox</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1515208109093534"><a name="p1515208109093534"></a><a name="p1515208109093534"></a>&nbsp;</p>
<p id="p1970262330093534"><a name="p1970262330093534"></a><a name="p1970262330093534"></a>A constructor used to create a <strong id="b1009806225093534"><a name="b1009806225093534"></a><a name="b1009806225093534"></a><a href="OHOS-UICheckBox.md">UICheckBox</a></strong> instance. </p>
</td>
</tr>
<tr id="row1922036629093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p371903855093534"><a name="p371903855093534"></a><a name="p371903855093534"></a><a href="Graphic.md#ga061c90b24caa6595b70a9da9f96c5c4e">~UICheckBox</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1658075324093534"><a name="p1658075324093534"></a><a name="p1658075324093534"></a>virtual&nbsp;</p>
<p id="p1960030568093534"><a name="p1960030568093534"></a><a name="p1960030568093534"></a>A destructor used to delete the <strong id="b1019385158093534"><a name="b1019385158093534"></a><a name="b1019385158093534"></a><a href="OHOS-UICheckBox.md">UICheckBox</a></strong> instance. </p>
</td>
</tr>
<tr id="row155975376093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1835472551093534"><a name="p1835472551093534"></a><a name="p1835472551093534"></a><a href="Graphic.md#gad72c8f6a67fc3fb86da8eabffcf5315d">SetOnChangeListener</a> (<a href="OHOS-UICheckBox-OnChangeListener.md">OnChangeListener</a> *onStateChangeListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1168253648093534"><a name="p1168253648093534"></a><a name="p1168253648093534"></a>void&nbsp;</p>
<p id="p1715360673093534"><a name="p1715360673093534"></a><a name="p1715360673093534"></a>Sets the listener for this check box. </p>
</td>
</tr>
<tr id="row2077541798093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1503613629093534"><a name="p1503613629093534"></a><a name="p1503613629093534"></a><a href="Graphic.md#ga8e75f8411fb25e564c82573a12773189">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p949738917093534"><a name="p949738917093534"></a><a name="p949738917093534"></a>void&nbsp;</p>
<p id="p1004257396093534"><a name="p1004257396093534"></a><a name="p1004257396093534"></a>Executes the draw action Ondraw invokes the rendering function provided by the underlying layer to draw pictures based on the selected status of the checkbox. </p>
</td>
</tr>
<tr id="row964108273093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p186521125093534"><a name="p186521125093534"></a><a name="p186521125093534"></a><a href="Graphic.md#ga2e1ac9e3084d018febf5ac0912a27c72">SetImages</a> (const char *selectedImageSrc, const char *unselectedImageSrc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p206839133093534"><a name="p206839133093534"></a><a name="p206839133093534"></a>virtual void&nbsp;</p>
<p id="p105080562093534"><a name="p105080562093534"></a><a name="p105080562093534"></a>Sets the images for this check box. </p>
</td>
</tr>
<tr id="row1542076072093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712631234093534"><a name="p1712631234093534"></a><a name="p1712631234093534"></a><a href="Graphic.md#ga89eb87d02e7b31fc6517b8744751f021">SetImages</a> (const <a href="OHOS-ImageInfo.md">ImageInfo</a> *selectedImageSrc, const <a href="OHOS-ImageInfo.md">ImageInfo</a> *unselectedImageSrc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p92550048093534"><a name="p92550048093534"></a><a name="p92550048093534"></a>virtual void&nbsp;</p>
<p id="p2052358541093534"><a name="p2052358541093534"></a><a name="p2052358541093534"></a>Sets the images for this check box. </p>
</td>
</tr>
<tr id="row1446115399093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2015675563093534"><a name="p2015675563093534"></a><a name="p2015675563093534"></a><a href="Graphic.md#gab3cddc176a6834fabc7c53912c97237c">GetState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1895743435093534"><a name="p1895743435093534"></a><a name="p1895743435093534"></a><a href="Graphic.md#ga15a3f0302aded0e4d1584ddc6002335d">UICheckBoxState</a>&nbsp;</p>
<p id="p1911685078093534"><a name="p1911685078093534"></a><a name="p1911685078093534"></a>Obtains the state of this check box. </p>
</td>
</tr>
<tr id="row448180247093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p819239758093534"><a name="p819239758093534"></a><a name="p819239758093534"></a><a href="Graphic.md#ga32217050815d4d9129ace5ab410fb82d">SetState</a> (<a href="Graphic.md#ga15a3f0302aded0e4d1584ddc6002335d">UICheckBoxState</a> state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989775342093534"><a name="p1989775342093534"></a><a name="p1989775342093534"></a>void&nbsp;</p>
<p id="p825606185093534"><a name="p825606185093534"></a><a name="p825606185093534"></a>Sets the state for this check box. </p>
</td>
</tr>
<tr id="row2019221358093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p113806994093534"><a name="p113806994093534"></a><a name="p113806994093534"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p852010586093534"><a name="p852010586093534"></a><a name="p852010586093534"></a>&nbsp;</p>
<p id="p1798361493093534"><a name="p1798361493093534"></a><a name="p1798361493093534"></a>A default constructor used to create an <strong id="b134238612093534"><a name="b134238612093534"></a><a name="b134238612093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1383292045093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p826933505093534"><a name="p826933505093534"></a><a name="p826933505093534"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1817197838093534"><a name="p1817197838093534"></a><a name="p1817197838093534"></a>&nbsp;</p>
<p id="p952848312093534"><a name="p952848312093534"></a><a name="p952848312093534"></a>A constructor used to create an <strong id="b1121722428093534"><a name="b1121722428093534"></a><a name="b1121722428093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row2074264200093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p942137622093534"><a name="p942137622093534"></a><a name="p942137622093534"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p719744710093534"><a name="p719744710093534"></a><a name="p719744710093534"></a>virtual&nbsp;</p>
<p id="p1022914231093534"><a name="p1022914231093534"></a><a name="p1022914231093534"></a>A destructor used to delete the <strong id="b1893274439093534"><a name="b1893274439093534"></a><a name="b1893274439093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1913327003093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p529862540093534"><a name="p529862540093534"></a><a name="p529862540093534"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1640135546093534"><a name="p1640135546093534"></a><a name="p1640135546093534"></a>virtual void&nbsp;</p>
<p id="p547589885093534"><a name="p547589885093534"></a><a name="p547589885093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row575119348093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1131577507093534"><a name="p1131577507093534"></a><a name="p1131577507093534"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1447932948093534"><a name="p1447932948093534"></a><a name="p1447932948093534"></a>virtual void&nbsp;</p>
<p id="p738991624093534"><a name="p738991624093534"></a><a name="p738991624093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1415008540093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1989717163093534"><a name="p1989717163093534"></a><a name="p1989717163093534"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27017965093534"><a name="p27017965093534"></a><a name="p27017965093534"></a>void&nbsp;</p>
<p id="p43586936093534"><a name="p43586936093534"></a><a name="p43586936093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1991162120093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1650481323093534"><a name="p1650481323093534"></a><a name="p1650481323093534"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032835700093534"><a name="p1032835700093534"></a><a name="p1032835700093534"></a>void&nbsp;</p>
<p id="p1467706424093534"><a name="p1467706424093534"></a><a name="p1467706424093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1584220907093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1096172417093534"><a name="p1096172417093534"></a><a name="p1096172417093534"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2113510854093534"><a name="p2113510854093534"></a><a name="p2113510854093534"></a>virtual bool&nbsp;</p>
<p id="p751901957093534"><a name="p751901957093534"></a><a name="p751901957093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1186261036093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p356492413093534"><a name="p356492413093534"></a><a name="p356492413093534"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p316190749093534"><a name="p316190749093534"></a><a name="p316190749093534"></a>virtual bool&nbsp;</p>
<p id="p1231889018093534"><a name="p1231889018093534"></a><a name="p1231889018093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1617387658093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1935869763093534"><a name="p1935869763093534"></a><a name="p1935869763093534"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p10283533093534"><a name="p10283533093534"></a><a name="p10283533093534"></a>virtual bool&nbsp;</p>
<p id="p1098102905093534"><a name="p1098102905093534"></a><a name="p1098102905093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1608372023093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1952530546093534"><a name="p1952530546093534"></a><a name="p1952530546093534"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1143198030093534"><a name="p1143198030093534"></a><a name="p1143198030093534"></a>virtual bool&nbsp;</p>
<p id="p1212086836093534"><a name="p1212086836093534"></a><a name="p1212086836093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row593002995093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p558423877093534"><a name="p558423877093534"></a><a name="p558423877093534"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p658060710093534"><a name="p658060710093534"></a><a name="p658060710093534"></a>virtual void&nbsp;</p>
<p id="p1163569808093534"><a name="p1163569808093534"></a><a name="p1163569808093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1715358158093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p905782241093534"><a name="p905782241093534"></a><a name="p905782241093534"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1979415908093534"><a name="p1979415908093534"></a><a name="p1979415908093534"></a>virtual void&nbsp;</p>
<p id="p363360512093534"><a name="p363360512093534"></a><a name="p363360512093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row344575788093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1540772677093534"><a name="p1540772677093534"></a><a name="p1540772677093534"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1185518134093534"><a name="p1185518134093534"></a><a name="p1185518134093534"></a>virtual void&nbsp;</p>
<p id="p795887326093534"><a name="p795887326093534"></a><a name="p795887326093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row514938942093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p186387705093534"><a name="p186387705093534"></a><a name="p186387705093534"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1062527352093534"><a name="p1062527352093534"></a><a name="p1062527352093534"></a>void&nbsp;</p>
<p id="p1884894236093534"><a name="p1884894236093534"></a><a name="p1884894236093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row258466336093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2083197620093534"><a name="p2083197620093534"></a><a name="p2083197620093534"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1776661086093534"><a name="p1776661086093534"></a><a name="p1776661086093534"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p635872348093534"><a name="p635872348093534"></a><a name="p635872348093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row2016926456093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p702645301093534"><a name="p702645301093534"></a><a name="p702645301093534"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1300736438093534"><a name="p1300736438093534"></a><a name="p1300736438093534"></a>void&nbsp;</p>
<p id="p1989495126093534"><a name="p1989495126093534"></a><a name="p1989495126093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row653041144093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997115208093534"><a name="p1997115208093534"></a><a name="p1997115208093534"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2097719446093534"><a name="p2097719446093534"></a><a name="p2097719446093534"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p248685591093534"><a name="p248685591093534"></a><a name="p248685591093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row339375740093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1836288262093534"><a name="p1836288262093534"></a><a name="p1836288262093534"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1030645532093534"><a name="p1030645532093534"></a><a name="p1030645532093534"></a>void&nbsp;</p>
<p id="p1642968741093534"><a name="p1642968741093534"></a><a name="p1642968741093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1864980306093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p946272754093534"><a name="p946272754093534"></a><a name="p946272754093534"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646398120093534"><a name="p1646398120093534"></a><a name="p1646398120093534"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p940450093093534"><a name="p940450093093534"></a><a name="p940450093093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1661727994093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p624280723093534"><a name="p624280723093534"></a><a name="p624280723093534"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p933678566093534"><a name="p933678566093534"></a><a name="p933678566093534"></a>void&nbsp;</p>
<p id="p1561502300093534"><a name="p1561502300093534"></a><a name="p1561502300093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1527785165093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1450894970093534"><a name="p1450894970093534"></a><a name="p1450894970093534"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1956005629093534"><a name="p1956005629093534"></a><a name="p1956005629093534"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p1626474138093534"><a name="p1626474138093534"></a><a name="p1626474138093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row519442240093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p377784829093534"><a name="p377784829093534"></a><a name="p377784829093534"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1043118488093534"><a name="p1043118488093534"></a><a name="p1043118488093534"></a>virtual void&nbsp;</p>
<p id="p1728619121093534"><a name="p1728619121093534"></a><a name="p1728619121093534"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row1496059132093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1207988203093534"><a name="p1207988203093534"></a><a name="p1207988203093534"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1638388755093534"><a name="p1638388755093534"></a><a name="p1638388755093534"></a>void&nbsp;</p>
<p id="p1883576355093534"><a name="p1883576355093534"></a><a name="p1883576355093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row668625321093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p982160180093534"><a name="p982160180093534"></a><a name="p982160180093534"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p994063478093534"><a name="p994063478093534"></a><a name="p994063478093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1333113793093534"><a name="p1333113793093534"></a><a name="p1333113793093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row844486841093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1127684162093534"><a name="p1127684162093534"></a><a name="p1127684162093534"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p446716775093534"><a name="p446716775093534"></a><a name="p446716775093534"></a>void&nbsp;</p>
<p id="p700093712093534"><a name="p700093712093534"></a><a name="p700093712093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1438426139093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1828374507093534"><a name="p1828374507093534"></a><a name="p1828374507093534"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1880683682093534"><a name="p1880683682093534"></a><a name="p1880683682093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1229345441093534"><a name="p1229345441093534"></a><a name="p1229345441093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row263656092093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1785463139093534"><a name="p1785463139093534"></a><a name="p1785463139093534"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572954930093534"><a name="p572954930093534"></a><a name="p572954930093534"></a>virtual void&nbsp;</p>
<p id="p867632009093534"><a name="p867632009093534"></a><a name="p867632009093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row538096701093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p982552651093534"><a name="p982552651093534"></a><a name="p982552651093534"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p938990592093534"><a name="p938990592093534"></a><a name="p938990592093534"></a>bool&nbsp;</p>
<p id="p1039458614093534"><a name="p1039458614093534"></a><a name="p1039458614093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1013628795093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1661349032093534"><a name="p1661349032093534"></a><a name="p1661349032093534"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1770503411093534"><a name="p1770503411093534"></a><a name="p1770503411093534"></a>void&nbsp;</p>
<p id="p1083321660093534"><a name="p1083321660093534"></a><a name="p1083321660093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row453898868093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1901590862093534"><a name="p1901590862093534"></a><a name="p1901590862093534"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1103922974093534"><a name="p1103922974093534"></a><a name="p1103922974093534"></a>bool&nbsp;</p>
<p id="p2093442763093534"><a name="p2093442763093534"></a><a name="p2093442763093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1453326977093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1813759821093534"><a name="p1813759821093534"></a><a name="p1813759821093534"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1827572767093534"><a name="p1827572767093534"></a><a name="p1827572767093534"></a>void&nbsp;</p>
<p id="p719101334093534"><a name="p719101334093534"></a><a name="p719101334093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1090840579093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p261490660093534"><a name="p261490660093534"></a><a name="p261490660093534"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1619807065093534"><a name="p1619807065093534"></a><a name="p1619807065093534"></a>bool&nbsp;</p>
<p id="p843776590093534"><a name="p843776590093534"></a><a name="p843776590093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1692921277093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p774804599093534"><a name="p774804599093534"></a><a name="p774804599093534"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p891127999093534"><a name="p891127999093534"></a><a name="p891127999093534"></a>void&nbsp;</p>
<p id="p1254560640093534"><a name="p1254560640093534"></a><a name="p1254560640093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row352164300093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1104017498093534"><a name="p1104017498093534"></a><a name="p1104017498093534"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p606618648093534"><a name="p606618648093534"></a><a name="p606618648093534"></a>bool&nbsp;</p>
<p id="p204173157093534"><a name="p204173157093534"></a><a name="p204173157093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1315998235093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p901209474093534"><a name="p901209474093534"></a><a name="p901209474093534"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1242249299093534"><a name="p1242249299093534"></a><a name="p1242249299093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1835559260093534"><a name="p1835559260093534"></a><a name="p1835559260093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row748596935093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1823807208093534"><a name="p1823807208093534"></a><a name="p1823807208093534"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1891890335093534"><a name="p1891890335093534"></a><a name="p1891890335093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1557952525093534"><a name="p1557952525093534"></a><a name="p1557952525093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1295079482093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1643808795093534"><a name="p1643808795093534"></a><a name="p1643808795093534"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p466027573093534"><a name="p466027573093534"></a><a name="p466027573093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p197909420093534"><a name="p197909420093534"></a><a name="p197909420093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1770818733093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1614590244093534"><a name="p1614590244093534"></a><a name="p1614590244093534"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1930333727093534"><a name="p1930333727093534"></a><a name="p1930333727093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1479516932093534"><a name="p1479516932093534"></a><a name="p1479516932093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row996052485093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1953787226093534"><a name="p1953787226093534"></a><a name="p1953787226093534"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2136861135093534"><a name="p2136861135093534"></a><a name="p2136861135093534"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1110635030093534"><a name="p1110635030093534"></a><a name="p1110635030093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1884384523093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1848945846093534"><a name="p1848945846093534"></a><a name="p1848945846093534"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2121432266093534"><a name="p2121432266093534"></a><a name="p2121432266093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1473157863093534"><a name="p1473157863093534"></a><a name="p1473157863093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1446960048093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1989832796093534"><a name="p1989832796093534"></a><a name="p1989832796093534"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1987620732093534"><a name="p1987620732093534"></a><a name="p1987620732093534"></a>void&nbsp;</p>
<p id="p1371150616093534"><a name="p1371150616093534"></a><a name="p1371150616093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row243060589093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1814909760093534"><a name="p1814909760093534"></a><a name="p1814909760093534"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p146192612093534"><a name="p146192612093534"></a><a name="p146192612093534"></a>virtual void&nbsp;</p>
<p id="p2028392990093534"><a name="p2028392990093534"></a><a name="p2028392990093534"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1618373845093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1398435704093534"><a name="p1398435704093534"></a><a name="p1398435704093534"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p290719715093534"><a name="p290719715093534"></a><a name="p290719715093534"></a>virtual int16_t&nbsp;</p>
<p id="p1465532514093534"><a name="p1465532514093534"></a><a name="p1465532514093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1973572445093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p224590954093534"><a name="p224590954093534"></a><a name="p224590954093534"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931391184093534"><a name="p931391184093534"></a><a name="p931391184093534"></a>virtual void&nbsp;</p>
<p id="p1357796747093534"><a name="p1357796747093534"></a><a name="p1357796747093534"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row2049539425093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1504701377093534"><a name="p1504701377093534"></a><a name="p1504701377093534"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1396612259093534"><a name="p1396612259093534"></a><a name="p1396612259093534"></a>virtual int16_t&nbsp;</p>
<p id="p1406844542093534"><a name="p1406844542093534"></a><a name="p1406844542093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row713601972093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p397516043093534"><a name="p397516043093534"></a><a name="p397516043093534"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p649585265093534"><a name="p649585265093534"></a><a name="p649585265093534"></a>virtual void&nbsp;</p>
<p id="p130890565093534"><a name="p130890565093534"></a><a name="p130890565093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row107597598093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p633437347093534"><a name="p633437347093534"></a><a name="p633437347093534"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p77062894093534"><a name="p77062894093534"></a><a name="p77062894093534"></a>virtual void&nbsp;</p>
<p id="p1849167560093534"><a name="p1849167560093534"></a><a name="p1849167560093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row854602785093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1740835436093534"><a name="p1740835436093534"></a><a name="p1740835436093534"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p46305390093534"><a name="p46305390093534"></a><a name="p46305390093534"></a>int16_t&nbsp;</p>
<p id="p896319230093534"><a name="p896319230093534"></a><a name="p896319230093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row471997095093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p964364688093534"><a name="p964364688093534"></a><a name="p964364688093534"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1407435572093534"><a name="p1407435572093534"></a><a name="p1407435572093534"></a>virtual void&nbsp;</p>
<p id="p37535183093534"><a name="p37535183093534"></a><a name="p37535183093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1470345663093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p614259312093534"><a name="p614259312093534"></a><a name="p614259312093534"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1919729823093534"><a name="p1919729823093534"></a><a name="p1919729823093534"></a>int16_t&nbsp;</p>
<p id="p507041291093534"><a name="p507041291093534"></a><a name="p507041291093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1301033333093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1343663599093534"><a name="p1343663599093534"></a><a name="p1343663599093534"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p681436010093534"><a name="p681436010093534"></a><a name="p681436010093534"></a>virtual void&nbsp;</p>
<p id="p1343305736093534"><a name="p1343305736093534"></a><a name="p1343305736093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1232409617093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p149144206093534"><a name="p149144206093534"></a><a name="p149144206093534"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1021754422093534"><a name="p1021754422093534"></a><a name="p1021754422093534"></a>virtual void&nbsp;</p>
<p id="p1323101422093534"><a name="p1323101422093534"></a><a name="p1323101422093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row214443352093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1225289186093534"><a name="p1225289186093534"></a><a name="p1225289186093534"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p269849093093534"><a name="p269849093093534"></a><a name="p269849093093534"></a>bool&nbsp;</p>
<p id="p1105893329093534"><a name="p1105893329093534"></a><a name="p1105893329093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1667793117093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p160327323093534"><a name="p160327323093534"></a><a name="p160327323093534"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2004304357093534"><a name="p2004304357093534"></a><a name="p2004304357093534"></a>void&nbsp;</p>
<p id="p1902759563093534"><a name="p1902759563093534"></a><a name="p1902759563093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row990073778093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p769266650093534"><a name="p769266650093534"></a><a name="p769266650093534"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1467636985093534"><a name="p1467636985093534"></a><a name="p1467636985093534"></a>void&nbsp;</p>
<p id="p1136507957093534"><a name="p1136507957093534"></a><a name="p1136507957093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row922490801093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197048458093534"><a name="p1197048458093534"></a><a name="p1197048458093534"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929482638093534"><a name="p929482638093534"></a><a name="p929482638093534"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p87844077093534"><a name="p87844077093534"></a><a name="p87844077093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1530494116093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p950024340093534"><a name="p950024340093534"></a><a name="p950024340093534"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452117368093534"><a name="p1452117368093534"></a><a name="p1452117368093534"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p2126828571093534"><a name="p2126828571093534"></a><a name="p2126828571093534"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row1851632227093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1296380504093534"><a name="p1296380504093534"></a><a name="p1296380504093534"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1067596838093534"><a name="p1067596838093534"></a><a name="p1067596838093534"></a>void&nbsp;</p>
<p id="p1863057694093534"><a name="p1863057694093534"></a><a name="p1863057694093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row677927056093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1686072092093534"><a name="p1686072092093534"></a><a name="p1686072092093534"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1184807800093534"><a name="p1184807800093534"></a><a name="p1184807800093534"></a>const char *&nbsp;</p>
<p id="p829797743093534"><a name="p829797743093534"></a><a name="p829797743093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1079912748093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2025381441093534"><a name="p2025381441093534"></a><a name="p2025381441093534"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1873217170093534"><a name="p1873217170093534"></a><a name="p1873217170093534"></a>void&nbsp;</p>
<p id="p2143523309093534"><a name="p2143523309093534"></a><a name="p2143523309093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1412160372093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1090207978093534"><a name="p1090207978093534"></a><a name="p1090207978093534"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1605929762093534"><a name="p1605929762093534"></a><a name="p1605929762093534"></a>int16_t&nbsp;</p>
<p id="p1073605704093534"><a name="p1073605704093534"></a><a name="p1073605704093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1098722736093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p556801979093534"><a name="p556801979093534"></a><a name="p556801979093534"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p780671859093534"><a name="p780671859093534"></a><a name="p780671859093534"></a>virtual void&nbsp;</p>
<p id="p6142757093534"><a name="p6142757093534"></a><a name="p6142757093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row47969113093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p158847090093534"><a name="p158847090093534"></a><a name="p158847090093534"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p305178247093534"><a name="p305178247093534"></a><a name="p305178247093534"></a>void&nbsp;</p>
<p id="p838198949093534"><a name="p838198949093534"></a><a name="p838198949093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row793887325093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p749657732093534"><a name="p749657732093534"></a><a name="p749657732093534"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p697337538093534"><a name="p697337538093534"></a><a name="p697337538093534"></a>void&nbsp;</p>
<p id="p287423165093534"><a name="p287423165093534"></a><a name="p287423165093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row156664283093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2027246192093534"><a name="p2027246192093534"></a><a name="p2027246192093534"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p688953243093534"><a name="p688953243093534"></a><a name="p688953243093534"></a>void&nbsp;</p>
<p id="p284825040093534"><a name="p284825040093534"></a><a name="p284825040093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row459470805093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p85485504093534"><a name="p85485504093534"></a><a name="p85485504093534"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1973362073093534"><a name="p1973362073093534"></a><a name="p1973362073093534"></a>void&nbsp;</p>
<p id="p976706173093534"><a name="p976706173093534"></a><a name="p976706173093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1166642093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149933343093534"><a name="p1149933343093534"></a><a name="p1149933343093534"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p41906693093534"><a name="p41906693093534"></a><a name="p41906693093534"></a>void&nbsp;</p>
<p id="p16528840093534"><a name="p16528840093534"></a><a name="p16528840093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1518653493093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612938492093534"><a name="p612938492093534"></a><a name="p612938492093534"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278966965093534"><a name="p278966965093534"></a><a name="p278966965093534"></a>void&nbsp;</p>
<p id="p1715023742093534"><a name="p1715023742093534"></a><a name="p1715023742093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row562664735093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1794450639093534"><a name="p1794450639093534"></a><a name="p1794450639093534"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p231961803093534"><a name="p231961803093534"></a><a name="p231961803093534"></a>void&nbsp;</p>
<p id="p1064373003093534"><a name="p1064373003093534"></a><a name="p1064373003093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1661704979093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p202204599093534"><a name="p202204599093534"></a><a name="p202204599093534"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1477720752093534"><a name="p1477720752093534"></a><a name="p1477720752093534"></a>void&nbsp;</p>
<p id="p1515842159093534"><a name="p1515842159093534"></a><a name="p1515842159093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1007591727093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1052801366093534"><a name="p1052801366093534"></a><a name="p1052801366093534"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p682066300093534"><a name="p682066300093534"></a><a name="p682066300093534"></a>void&nbsp;</p>
<p id="p341782371093534"><a name="p341782371093534"></a><a name="p341782371093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1162771227093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p249470248093534"><a name="p249470248093534"></a><a name="p249470248093534"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2022547443093534"><a name="p2022547443093534"></a><a name="p2022547443093534"></a>void&nbsp;</p>
<p id="p1623110848093534"><a name="p1623110848093534"></a><a name="p1623110848093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1327635576093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1393252555093534"><a name="p1393252555093534"></a><a name="p1393252555093534"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p561738748093534"><a name="p561738748093534"></a><a name="p561738748093534"></a>void&nbsp;</p>
<p id="p2001110851093534"><a name="p2001110851093534"></a><a name="p2001110851093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1980191232093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1529759798093534"><a name="p1529759798093534"></a><a name="p1529759798093534"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1495410270093534"><a name="p1495410270093534"></a><a name="p1495410270093534"></a>void&nbsp;</p>
<p id="p1439690633093534"><a name="p1439690633093534"></a><a name="p1439690633093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row688712955093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1257575260093534"><a name="p1257575260093534"></a><a name="p1257575260093534"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p882404419093534"><a name="p882404419093534"></a><a name="p882404419093534"></a>void&nbsp;</p>
<p id="p183630289093534"><a name="p183630289093534"></a><a name="p183630289093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row995507978093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p898848056093534"><a name="p898848056093534"></a><a name="p898848056093534"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1004788723093534"><a name="p1004788723093534"></a><a name="p1004788723093534"></a>void&nbsp;</p>
<p id="p719461339093534"><a name="p719461339093534"></a><a name="p719461339093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1913847622093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645599808093534"><a name="p645599808093534"></a><a name="p645599808093534"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p938312838093534"><a name="p938312838093534"></a><a name="p938312838093534"></a>void&nbsp;</p>
<p id="p100937529093534"><a name="p100937529093534"></a><a name="p100937529093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1409061593093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1884801212093534"><a name="p1884801212093534"></a><a name="p1884801212093534"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1405449090093534"><a name="p1405449090093534"></a><a name="p1405449090093534"></a>virtual void&nbsp;</p>
<p id="p1200293891093534"><a name="p1200293891093534"></a><a name="p1200293891093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row681509400093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1490948240093534"><a name="p1490948240093534"></a><a name="p1490948240093534"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1591915830093534"><a name="p1591915830093534"></a><a name="p1591915830093534"></a>virtual void&nbsp;</p>
<p id="p1237926638093534"><a name="p1237926638093534"></a><a name="p1237926638093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1337795645093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p995299763093534"><a name="p995299763093534"></a><a name="p995299763093534"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1615133258093534"><a name="p1615133258093534"></a><a name="p1615133258093534"></a>virtual int64_t&nbsp;</p>
<p id="p969318841093534"><a name="p969318841093534"></a><a name="p969318841093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1694259591093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1836280864093534"><a name="p1836280864093534"></a><a name="p1836280864093534"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1120713817093534"><a name="p1120713817093534"></a><a name="p1120713817093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p648792383093534"><a name="p648792383093534"></a><a name="p648792383093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row495015685093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488891244093534"><a name="p1488891244093534"></a><a name="p1488891244093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1516121817093534"><a name="p1516121817093534"></a><a name="p1516121817093534"></a>void *&nbsp;</p>
<p id="p2018186831093534"><a name="p2018186831093534"></a><a name="p2018186831093534"></a>Overrides the <strong id="b593571745093534"><a name="b593571745093534"></a><a name="b593571745093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row133535515093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1024520338093534"><a name="p1024520338093534"></a><a name="p1024520338093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p483702582093534"><a name="p483702582093534"></a><a name="p483702582093534"></a>void&nbsp;</p>
<p id="p750307048093534"><a name="p750307048093534"></a><a name="p750307048093534"></a>Overrides the <strong id="b256600240093534"><a name="b256600240093534"></a><a name="b256600240093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1212446346093534"></a>
<table><thead align="left"><tr id="row719969403093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2086080693093534"><a name="p2086080693093534"></a><a name="p2086080693093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p720919600093534"><a name="p720919600093534"></a><a name="p720919600093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2047615534093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228011165093534"><a name="p228011165093534"></a><a name="p228011165093534"></a><a href="Graphic.md#ga15a3f0302aded0e4d1584ddc6002335d">UICheckBoxState</a> : uint8_t </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1210533321093534"><a name="p1210533321093534"></a><a name="p1210533321093534"></a>Enumerates the states of a check box. </p>
</td>
</tr>
</tbody>
</table>

