# OHOS::UIButton<a name="ZH-CN_TOPIC_0000001055358130"></a>

## **Overview**<a name="section377678966093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents a button. 

This component responds to the press and release events.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section800105389093533"></a>

## Public Types<a name="pub-types"></a>

<a name="table773006005093533"></a>
<table><thead align="left"><tr id="row432343439093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p496947146093533"><a name="p496947146093533"></a><a name="p496947146093533"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p621140016093533"><a name="p621140016093533"></a><a name="p621140016093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row940987781093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p150098906093533"><a name="p150098906093533"></a><a name="p150098906093533"></a><a href="Graphic.md#gaf9f6c0c373f090e79b9e8d847e186e92">ButtonImageSrc</a> : uint8_t </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p495845134093533"><a name="p495845134093533"></a><a name="p495845134093533"></a>Enumerates the images for different button states. </p>
</td>
</tr>
<tr id="row2095860139093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p629761433093533"><a name="p629761433093533"></a><a name="p629761433093533"></a><a href="Graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> : uint8_t </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1883566902093533"><a name="p1883566902093533"></a><a name="p1883566902093533"></a>Enumerates the states of this button. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table636830004093533"></a>
<table><thead align="left"><tr id="row1707529613093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1892702948093533"><a name="p1892702948093533"></a><a name="p1892702948093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p16634933093533"><a name="p16634933093533"></a><a name="p16634933093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1868485118093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907944156093533"><a name="p907944156093533"></a><a name="p907944156093533"></a><a href="Graphic.md#ga3aee093d4c583223850a7ad80d5bed79">UIButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p38599148093533"><a name="p38599148093533"></a><a name="p38599148093533"></a>&nbsp;</p>
<p id="p611281160093533"><a name="p611281160093533"></a><a name="p611281160093533"></a>A constructor used to create a <strong id="b1552401539093533"><a name="b1552401539093533"></a><a name="b1552401539093533"></a><a href="OHOS-UIButton.md">UIButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row571074645093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1027043198093533"><a name="p1027043198093533"></a><a name="p1027043198093533"></a><a href="Graphic.md#ga33e30931e9b3557634b2b2be93bc41f6">UIButton</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1498892844093533"><a name="p1498892844093533"></a><a name="p1498892844093533"></a>&nbsp;</p>
<p id="p1095613318093533"><a name="p1095613318093533"></a><a name="p1095613318093533"></a>A constructor used to create a <strong id="b269185977093533"><a name="b269185977093533"></a><a name="b269185977093533"></a><a href="OHOS-UIButton.md">UIButton</a></strong> instance based on the button ID. </p>
</td>
</tr>
<tr id="row1250034360093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p243741381093533"><a name="p243741381093533"></a><a name="p243741381093533"></a><a href="Graphic.md#ga0c5fbcf319fc6df8170d407a337b9d8b">~UIButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1011210191093533"><a name="p1011210191093533"></a><a name="p1011210191093533"></a>virtual&nbsp;</p>
<p id="p187807863093533"><a name="p187807863093533"></a><a name="p187807863093533"></a>A destructor used to delete the <strong id="b169449710093533"><a name="b169449710093533"></a><a name="b169449710093533"></a><a href="OHOS-UIButton.md">UIButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row1975055125093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1414902540093533"><a name="p1414902540093533"></a><a name="p1414902540093533"></a><a href="Graphic.md#gad19f55fb0de64f3f39485292d0629dc7">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1263762952093533"><a name="p1263762952093533"></a><a name="p1263762952093533"></a>UIViewType&nbsp;</p>
<p id="p709670134093533"><a name="p709670134093533"></a><a name="p709670134093533"></a>Obtains the component type. </p>
</td>
</tr>
<tr id="row1570168271093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1467896856093533"><a name="p1467896856093533"></a><a name="p1467896856093533"></a><a href="Graphic.md#gaf64d9ec1744ab9c7385dd64d30a786e4">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p874122735093533"><a name="p874122735093533"></a><a name="p874122735093533"></a>bool&nbsp;</p>
<p id="p373866956093533"><a name="p373866956093533"></a><a name="p373866956093533"></a>Do something before draw, this function will be invoked mainly to check if this view need to cover invalidate area so render manager can decide which layer to draw firstly. </p>
</td>
</tr>
<tr id="row1687538412093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p561241032093533"><a name="p561241032093533"></a><a name="p561241032093533"></a><a href="Graphic.md#gae69843b87be9fcdab3e4ac776547f3bc">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p968122331093533"><a name="p968122331093533"></a><a name="p968122331093533"></a>void&nbsp;</p>
<p id="p391236031093533"><a name="p391236031093533"></a><a name="p391236031093533"></a>Executes the draw action. </p>
</td>
</tr>
<tr id="row8815685093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p311260767093533"><a name="p311260767093533"></a><a name="p311260767093533"></a><a href="Graphic.md#ga1d887720c89170abd3c8a400a791765d">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1988053747093533"><a name="p1988053747093533"></a><a name="p1988053747093533"></a>void&nbsp;</p>
<p id="p279346491093533"><a name="p279346491093533"></a><a name="p279346491093533"></a>Executes the press event action. </p>
</td>
</tr>
<tr id="row1868896825093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1639369379093533"><a name="p1639369379093533"></a><a name="p1639369379093533"></a><a href="Graphic.md#gadb9492eb82ff23f91f9263fc748f24de">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p305648556093533"><a name="p305648556093533"></a><a name="p305648556093533"></a>void&nbsp;</p>
<p id="p1925233086093533"><a name="p1925233086093533"></a><a name="p1925233086093533"></a>Executes the press release event action. </p>
</td>
</tr>
<tr id="row612456422093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p140725664093533"><a name="p140725664093533"></a><a name="p140725664093533"></a><a href="Graphic.md#ga4f481e0ce91f87c6b70f6e0190e4f34f">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1713452432093533"><a name="p1713452432093533"></a><a name="p1713452432093533"></a>void&nbsp;</p>
<p id="p1343486946093533"><a name="p1343486946093533"></a><a name="p1343486946093533"></a>Executes the cancel event action. </p>
</td>
</tr>
<tr id="row492564423093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1757962951093533"><a name="p1757962951093533"></a><a name="p1757962951093533"></a><a href="Graphic.md#ga60194db1c1bba6a0ef963bdbbe9f972f">SetImageSrc</a> (const char *defaultImgSrc, const char *triggeredImgSrc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p330219611093533"><a name="p330219611093533"></a><a name="p330219611093533"></a>void&nbsp;</p>
<p id="p324898731093533"><a name="p324898731093533"></a><a name="p324898731093533"></a>Sets the image for this button. </p>
</td>
</tr>
<tr id="row1602737766093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p102112998093533"><a name="p102112998093533"></a><a name="p102112998093533"></a><a href="Graphic.md#gab751bc5941edb403022d65d2c605a241">SetImageSrc</a> (const <a href="OHOS-ImageInfo.md">ImageInfo</a> *defaultImgSrc, const <a href="OHOS-ImageInfo.md">ImageInfo</a> *triggeredImgSrc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1363800494093533"><a name="p1363800494093533"></a><a name="p1363800494093533"></a>void&nbsp;</p>
<p id="p603648553093533"><a name="p603648553093533"></a><a name="p603648553093533"></a>Sets the image for this button. </p>
</td>
</tr>
<tr id="row1615699731093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1662599006093533"><a name="p1662599006093533"></a><a name="p1662599006093533"></a><a href="Graphic.md#ga952fcbc88905cf35ec3e09bdf01375f2">SetImagePosition</a> (const int16_t x, const int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p200171388093533"><a name="p200171388093533"></a><a name="p200171388093533"></a>void&nbsp;</p>
<p id="p344244534093533"><a name="p344244534093533"></a><a name="p344244534093533"></a>Sets the position for this image. </p>
</td>
</tr>
<tr id="row2125500803093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1170743321093533"><a name="p1170743321093533"></a><a name="p1170743321093533"></a><a href="Graphic.md#ga4d8abf189ddcbf325c60402084d7e3c3">GetImageX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1235976914093533"><a name="p1235976914093533"></a><a name="p1235976914093533"></a>int16_t&nbsp;</p>
<p id="p1573533210093533"><a name="p1573533210093533"></a><a name="p1573533210093533"></a>Obtains the x-coordinate of this image. </p>
</td>
</tr>
<tr id="row731542766093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p456227791093533"><a name="p456227791093533"></a><a name="p456227791093533"></a><a href="Graphic.md#ga25a02afb52cc15212084fb6bc8f27afd">GetImageY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p564606622093533"><a name="p564606622093533"></a><a name="p564606622093533"></a>int16_t&nbsp;</p>
<p id="p53279379093533"><a name="p53279379093533"></a><a name="p53279379093533"></a>Obtains the y-coordinate of this image. </p>
</td>
</tr>
<tr id="row1430375848093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1852165315093533"><a name="p1852165315093533"></a><a name="p1852165315093533"></a><a href="Graphic.md#gaf6496e4858473ab2acb80a2be6264a01">GetCurImageSrc</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p424122550093533"><a name="p424122550093533"></a><a name="p424122550093533"></a>const <a href="OHOS-Image.md">Image</a> *&nbsp;</p>
<p id="p1409386633093533"><a name="p1409386633093533"></a><a name="p1409386633093533"></a>Obtains the image for the current button state. </p>
</td>
</tr>
<tr id="row1865452009093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2045494741093533"><a name="p2045494741093533"></a><a name="p2045494741093533"></a><a href="Graphic.md#ga8cb74b23f740091e59ad350a8dea436b">GetWidth</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p333593526093533"><a name="p333593526093533"></a><a name="p333593526093533"></a>int16_t&nbsp;</p>
<p id="p80704271093533"><a name="p80704271093533"></a><a name="p80704271093533"></a>Obtains the width of this image. </p>
</td>
</tr>
<tr id="row185912688093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1008630503093533"><a name="p1008630503093533"></a><a name="p1008630503093533"></a><a href="Graphic.md#ga1f8015706cfc73728696bf2bbd3e833b">GetHeight</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p626166494093533"><a name="p626166494093533"></a><a name="p626166494093533"></a>int16_t&nbsp;</p>
<p id="p1441101303093533"><a name="p1441101303093533"></a><a name="p1441101303093533"></a>Obtains the height of this image. </p>
</td>
</tr>
<tr id="row417850561093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p752394721093533"><a name="p752394721093533"></a><a name="p752394721093533"></a><a href="Graphic.md#ga420f927c473cec8c6f3265ff7c35336f">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p315050319093533"><a name="p315050319093533"></a><a name="p315050319093533"></a>void&nbsp;</p>
<p id="p2105902070093533"><a name="p2105902070093533"></a><a name="p2105902070093533"></a>Sets the width for this image. </p>
</td>
</tr>
<tr id="row1221652853093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1447546096093533"><a name="p1447546096093533"></a><a name="p1447546096093533"></a><a href="Graphic.md#ga8b6dbfcd0328753c2c3cef4d14b0ff30">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1100406552093533"><a name="p1100406552093533"></a><a name="p1100406552093533"></a>void&nbsp;</p>
<p id="p384625089093533"><a name="p384625089093533"></a><a name="p384625089093533"></a>Sets the height for this image. </p>
</td>
</tr>
<tr id="row1815353841093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1263796895093533"><a name="p1263796895093533"></a><a name="p1263796895093533"></a><a href="Graphic.md#ga93994f4d735e4f9a7d3e7d737e2c620c">GetContentRect</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p192114438093533"><a name="p192114438093533"></a><a name="p192114438093533"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p801309667093533"><a name="p801309667093533"></a><a name="p801309667093533"></a>Obtains a rectangular area that contains coordinate information. </p>
</td>
</tr>
<tr id="row727846002093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1277751312093533"><a name="p1277751312093533"></a><a name="p1277751312093533"></a><a href="Graphic.md#ga37736a82bec6a01bc5a880e1d01ccccd">GetStyle</a> (uint8_t key) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p218507819093533"><a name="p218507819093533"></a><a name="p218507819093533"></a>int64_t&nbsp;</p>
<p id="p1123731364093533"><a name="p1123731364093533"></a><a name="p1123731364093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row77213272093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1418538906093533"><a name="p1418538906093533"></a><a name="p1418538906093533"></a><a href="Graphic.md#gaa5fdd9b28b8c919dbde0e34d8ae38caf">SetStyle</a> (uint8_t key, int64_t value) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1050692952093533"><a name="p1050692952093533"></a><a name="p1050692952093533"></a>void&nbsp;</p>
<p id="p155994137093533"><a name="p155994137093533"></a><a name="p155994137093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1615453798093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1825140157093533"><a name="p1825140157093533"></a><a name="p1825140157093533"></a><a href="Graphic.md#gaa3f74af93c91a24e58fdd06ad7d0bdf9">GetStyleForState</a> (uint8_t key, <a href="Graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> state) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p131498545093533"><a name="p131498545093533"></a><a name="p131498545093533"></a>int64_t&nbsp;</p>
<p id="p1933131659093533"><a name="p1933131659093533"></a><a name="p1933131659093533"></a>Obtains the style of a button in a specific state. </p>
</td>
</tr>
<tr id="row361783836093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1587333866093533"><a name="p1587333866093533"></a><a name="p1587333866093533"></a><a href="Graphic.md#ga7ece04980fa99a277bfbb591771f47f1">SetStyleForState</a> (uint8_t key, int64_t value, <a href="Graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p141441850093533"><a name="p141441850093533"></a><a name="p141441850093533"></a>void&nbsp;</p>
<p id="p1009795630093533"><a name="p1009795630093533"></a><a name="p1009795630093533"></a>Sets the style for a button in a specific state. </p>
</td>
</tr>
<tr id="row1409867864093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p461562379093533"><a name="p461562379093533"></a><a name="p461562379093533"></a><a href="Graphic.md#ga283131701e907e586964189818d04411">Disable</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2066465503093533"><a name="p2066465503093533"></a><a name="p2066465503093533"></a>void&nbsp;</p>
<p id="p1727229602093533"><a name="p1727229602093533"></a><a name="p1727229602093533"></a>Disables this button. </p>
</td>
</tr>
<tr id="row1411369366093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2045958857093533"><a name="p2045958857093533"></a><a name="p2045958857093533"></a><a href="Graphic.md#ga3185df8b60a609564f978ed9576fb813">Enable</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1280508156093533"><a name="p1280508156093533"></a><a name="p1280508156093533"></a>void&nbsp;</p>
<p id="p86956576093533"><a name="p86956576093533"></a><a name="p86956576093533"></a>Enables this button. </p>
</td>
</tr>
<tr id="row993722449093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p439428355093533"><a name="p439428355093533"></a><a name="p439428355093533"></a><a href="Graphic.md#ga737d850b2adf8a2977369e611764b1ae">SetStateForStyle</a> (<a href="Graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p765343535093533"><a name="p765343535093533"></a><a name="p765343535093533"></a>void&nbsp;</p>
<p id="p682831076093533"><a name="p682831076093533"></a><a name="p682831076093533"></a>Sets the state for a button. After the setting, calling <a href="Graphic.md#gaa5fdd9b28b8c919dbde0e34d8ae38caf">SetStyle</a> will change the style of this button, but not its state. </p>
</td>
</tr>
<tr id="row475629391093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p569328125093533"><a name="p569328125093533"></a><a name="p569328125093533"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p435014020093533"><a name="p435014020093533"></a><a name="p435014020093533"></a>&nbsp;</p>
<p id="p1843505515093533"><a name="p1843505515093533"></a><a name="p1843505515093533"></a>A default constructor used to create an <strong id="b1023623841093533"><a name="b1023623841093533"></a><a name="b1023623841093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row464281597093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691411105093533"><a name="p691411105093533"></a><a name="p691411105093533"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1247083289093533"><a name="p1247083289093533"></a><a name="p1247083289093533"></a>&nbsp;</p>
<p id="p405151747093533"><a name="p405151747093533"></a><a name="p405151747093533"></a>A constructor used to create an <strong id="b1721652212093533"><a name="b1721652212093533"></a><a name="b1721652212093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1242031253093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p455851258093533"><a name="p455851258093533"></a><a name="p455851258093533"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p196152187093533"><a name="p196152187093533"></a><a name="p196152187093533"></a>virtual&nbsp;</p>
<p id="p1494156579093533"><a name="p1494156579093533"></a><a name="p1494156579093533"></a>A destructor used to delete the <strong id="b1719193015093533"><a name="b1719193015093533"></a><a name="b1719193015093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row758429936093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p892652295093533"><a name="p892652295093533"></a><a name="p892652295093533"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2145691655093533"><a name="p2145691655093533"></a><a name="p2145691655093533"></a>virtual void&nbsp;</p>
<p id="p1619634201093533"><a name="p1619634201093533"></a><a name="p1619634201093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row2130990461093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492035408093533"><a name="p1492035408093533"></a><a name="p1492035408093533"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p340122471093533"><a name="p340122471093533"></a><a name="p340122471093533"></a>virtual void&nbsp;</p>
<p id="p1796267301093533"><a name="p1796267301093533"></a><a name="p1796267301093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1847397949093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1301540980093533"><a name="p1301540980093533"></a><a name="p1301540980093533"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p725921038093533"><a name="p725921038093533"></a><a name="p725921038093533"></a>void&nbsp;</p>
<p id="p1491966750093533"><a name="p1491966750093533"></a><a name="p1491966750093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row90130944093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1451621868093533"><a name="p1451621868093533"></a><a name="p1451621868093533"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p185259858093533"><a name="p185259858093533"></a><a name="p185259858093533"></a>void&nbsp;</p>
<p id="p319326676093533"><a name="p319326676093533"></a><a name="p319326676093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1473991840093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p52848666093533"><a name="p52848666093533"></a><a name="p52848666093533"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p49875018093533"><a name="p49875018093533"></a><a name="p49875018093533"></a>virtual bool&nbsp;</p>
<p id="p1454386131093533"><a name="p1454386131093533"></a><a name="p1454386131093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row297135341093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p880528466093533"><a name="p880528466093533"></a><a name="p880528466093533"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2008335941093533"><a name="p2008335941093533"></a><a name="p2008335941093533"></a>virtual bool&nbsp;</p>
<p id="p61014238093533"><a name="p61014238093533"></a><a name="p61014238093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1928141453093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244145497093533"><a name="p1244145497093533"></a><a name="p1244145497093533"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1779202964093533"><a name="p1779202964093533"></a><a name="p1779202964093533"></a>virtual bool&nbsp;</p>
<p id="p761342517093533"><a name="p761342517093533"></a><a name="p761342517093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row337071843093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1865271845093533"><a name="p1865271845093533"></a><a name="p1865271845093533"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p507839656093533"><a name="p507839656093533"></a><a name="p507839656093533"></a>virtual bool&nbsp;</p>
<p id="p364859205093533"><a name="p364859205093533"></a><a name="p364859205093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row2062972775093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1822985083093533"><a name="p1822985083093533"></a><a name="p1822985083093533"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1086807790093533"><a name="p1086807790093533"></a><a name="p1086807790093533"></a>virtual void&nbsp;</p>
<p id="p796084443093533"><a name="p796084443093533"></a><a name="p796084443093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row301505246093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1870761746093533"><a name="p1870761746093533"></a><a name="p1870761746093533"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1316344125093533"><a name="p1316344125093533"></a><a name="p1316344125093533"></a>void&nbsp;</p>
<p id="p537072132093533"><a name="p537072132093533"></a><a name="p537072132093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1519446215093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1736164588093533"><a name="p1736164588093533"></a><a name="p1736164588093533"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2101332222093533"><a name="p2101332222093533"></a><a name="p2101332222093533"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p1336385493093533"><a name="p1336385493093533"></a><a name="p1336385493093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row378822780093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1801713487093533"><a name="p1801713487093533"></a><a name="p1801713487093533"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1903812315093533"><a name="p1903812315093533"></a><a name="p1903812315093533"></a>void&nbsp;</p>
<p id="p1548640448093533"><a name="p1548640448093533"></a><a name="p1548640448093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row496272640093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1520508486093533"><a name="p1520508486093533"></a><a name="p1520508486093533"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p841692278093533"><a name="p841692278093533"></a><a name="p841692278093533"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p386656420093533"><a name="p386656420093533"></a><a name="p386656420093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1682099779093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1975342658093533"><a name="p1975342658093533"></a><a name="p1975342658093533"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1379644948093533"><a name="p1379644948093533"></a><a name="p1379644948093533"></a>void&nbsp;</p>
<p id="p1741545305093533"><a name="p1741545305093533"></a><a name="p1741545305093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row568114450093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1944773578093533"><a name="p1944773578093533"></a><a name="p1944773578093533"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p603821918093533"><a name="p603821918093533"></a><a name="p603821918093533"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p550046616093533"><a name="p550046616093533"></a><a name="p550046616093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row780971344093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p960104438093533"><a name="p960104438093533"></a><a name="p960104438093533"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28426731093533"><a name="p28426731093533"></a><a name="p28426731093533"></a>void&nbsp;</p>
<p id="p1214446723093533"><a name="p1214446723093533"></a><a name="p1214446723093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1119901622093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p29051002093533"><a name="p29051002093533"></a><a name="p29051002093533"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847347091093533"><a name="p1847347091093533"></a><a name="p1847347091093533"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p379393389093533"><a name="p379393389093533"></a><a name="p379393389093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row2111791529093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1720983034093533"><a name="p1720983034093533"></a><a name="p1720983034093533"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p524754878093533"><a name="p524754878093533"></a><a name="p524754878093533"></a>virtual void&nbsp;</p>
<p id="p894559336093533"><a name="p894559336093533"></a><a name="p894559336093533"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row1092129875093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1395044775093533"><a name="p1395044775093533"></a><a name="p1395044775093533"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p367537337093533"><a name="p367537337093533"></a><a name="p367537337093533"></a>void&nbsp;</p>
<p id="p1217938895093533"><a name="p1217938895093533"></a><a name="p1217938895093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row580706590093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p647049652093533"><a name="p647049652093533"></a><a name="p647049652093533"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2139689616093533"><a name="p2139689616093533"></a><a name="p2139689616093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p448612272093533"><a name="p448612272093533"></a><a name="p448612272093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row31824661093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1652128978093533"><a name="p1652128978093533"></a><a name="p1652128978093533"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2061495337093533"><a name="p2061495337093533"></a><a name="p2061495337093533"></a>void&nbsp;</p>
<p id="p868745862093533"><a name="p868745862093533"></a><a name="p868745862093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row471441758093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1950800636093533"><a name="p1950800636093533"></a><a name="p1950800636093533"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p546996267093533"><a name="p546996267093533"></a><a name="p546996267093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1292860249093533"><a name="p1292860249093533"></a><a name="p1292860249093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row481804671093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p317764376093533"><a name="p317764376093533"></a><a name="p317764376093533"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p321474437093533"><a name="p321474437093533"></a><a name="p321474437093533"></a>virtual void&nbsp;</p>
<p id="p991103483093533"><a name="p991103483093533"></a><a name="p991103483093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row879606759093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1569333802093533"><a name="p1569333802093533"></a><a name="p1569333802093533"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073211340093533"><a name="p2073211340093533"></a><a name="p2073211340093533"></a>bool&nbsp;</p>
<p id="p698215250093533"><a name="p698215250093533"></a><a name="p698215250093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1736791888093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1720122266093533"><a name="p1720122266093533"></a><a name="p1720122266093533"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2090189273093533"><a name="p2090189273093533"></a><a name="p2090189273093533"></a>void&nbsp;</p>
<p id="p1620587631093533"><a name="p1620587631093533"></a><a name="p1620587631093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1469589472093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p885492759093533"><a name="p885492759093533"></a><a name="p885492759093533"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1959703995093533"><a name="p1959703995093533"></a><a name="p1959703995093533"></a>bool&nbsp;</p>
<p id="p1445561155093533"><a name="p1445561155093533"></a><a name="p1445561155093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row933629384093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1534055722093533"><a name="p1534055722093533"></a><a name="p1534055722093533"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1223308721093533"><a name="p1223308721093533"></a><a name="p1223308721093533"></a>void&nbsp;</p>
<p id="p1752529826093533"><a name="p1752529826093533"></a><a name="p1752529826093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1079465756093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1640484077093533"><a name="p1640484077093533"></a><a name="p1640484077093533"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1036166571093533"><a name="p1036166571093533"></a><a name="p1036166571093533"></a>bool&nbsp;</p>
<p id="p1345497819093533"><a name="p1345497819093533"></a><a name="p1345497819093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1295073268093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1206896331093533"><a name="p1206896331093533"></a><a name="p1206896331093533"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p644009113093533"><a name="p644009113093533"></a><a name="p644009113093533"></a>void&nbsp;</p>
<p id="p202970384093533"><a name="p202970384093533"></a><a name="p202970384093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row123999257093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1218198824093533"><a name="p1218198824093533"></a><a name="p1218198824093533"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p515984066093533"><a name="p515984066093533"></a><a name="p515984066093533"></a>bool&nbsp;</p>
<p id="p1002768923093533"><a name="p1002768923093533"></a><a name="p1002768923093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1192503356093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p736504740093533"><a name="p736504740093533"></a><a name="p736504740093533"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1603224411093533"><a name="p1603224411093533"></a><a name="p1603224411093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1208550055093533"><a name="p1208550055093533"></a><a name="p1208550055093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1275415662093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1762347136093533"><a name="p1762347136093533"></a><a name="p1762347136093533"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p913043954093533"><a name="p913043954093533"></a><a name="p913043954093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p2114492363093533"><a name="p2114492363093533"></a><a name="p2114492363093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1271118967093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1324356220093533"><a name="p1324356220093533"></a><a name="p1324356220093533"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1863725925093533"><a name="p1863725925093533"></a><a name="p1863725925093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1921023433093533"><a name="p1921023433093533"></a><a name="p1921023433093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row431024600093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1530822893093533"><a name="p1530822893093533"></a><a name="p1530822893093533"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p374433542093533"><a name="p374433542093533"></a><a name="p374433542093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1627334370093533"><a name="p1627334370093533"></a><a name="p1627334370093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1516429799093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1713713044093533"><a name="p1713713044093533"></a><a name="p1713713044093533"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p481717557093533"><a name="p481717557093533"></a><a name="p481717557093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p711239209093533"><a name="p711239209093533"></a><a name="p711239209093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row832260807093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p504788629093533"><a name="p504788629093533"></a><a name="p504788629093533"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1399597897093533"><a name="p1399597897093533"></a><a name="p1399597897093533"></a>void&nbsp;</p>
<p id="p560300676093533"><a name="p560300676093533"></a><a name="p560300676093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1491310155093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1912224415093533"><a name="p1912224415093533"></a><a name="p1912224415093533"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1797464848093533"><a name="p1797464848093533"></a><a name="p1797464848093533"></a>virtual void&nbsp;</p>
<p id="p1146741404093533"><a name="p1146741404093533"></a><a name="p1146741404093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1201907110093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2011447178093533"><a name="p2011447178093533"></a><a name="p2011447178093533"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1491741295093533"><a name="p1491741295093533"></a><a name="p1491741295093533"></a>virtual void&nbsp;</p>
<p id="p981432142093533"><a name="p981432142093533"></a><a name="p981432142093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row641347998093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p757566551093533"><a name="p757566551093533"></a><a name="p757566551093533"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1640947505093533"><a name="p1640947505093533"></a><a name="p1640947505093533"></a>int16_t&nbsp;</p>
<p id="p1526716016093533"><a name="p1526716016093533"></a><a name="p1526716016093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row498706989093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p162681702093533"><a name="p162681702093533"></a><a name="p162681702093533"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p217786868093533"><a name="p217786868093533"></a><a name="p217786868093533"></a>virtual void&nbsp;</p>
<p id="p1711668198093533"><a name="p1711668198093533"></a><a name="p1711668198093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row874776188093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1970736643093533"><a name="p1970736643093533"></a><a name="p1970736643093533"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1573803719093533"><a name="p1573803719093533"></a><a name="p1573803719093533"></a>int16_t&nbsp;</p>
<p id="p753021617093533"><a name="p753021617093533"></a><a name="p753021617093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1102265967093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2063647583093533"><a name="p2063647583093533"></a><a name="p2063647583093533"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p672270948093533"><a name="p672270948093533"></a><a name="p672270948093533"></a>virtual void&nbsp;</p>
<p id="p2059863785093533"><a name="p2059863785093533"></a><a name="p2059863785093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1673134714093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p842729487093533"><a name="p842729487093533"></a><a name="p842729487093533"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p850830658093533"><a name="p850830658093533"></a><a name="p850830658093533"></a>virtual void&nbsp;</p>
<p id="p47494119093533"><a name="p47494119093533"></a><a name="p47494119093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row323619619093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1800977907093533"><a name="p1800977907093533"></a><a name="p1800977907093533"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929893865093533"><a name="p929893865093533"></a><a name="p929893865093533"></a>bool&nbsp;</p>
<p id="p30425127093533"><a name="p30425127093533"></a><a name="p30425127093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row178922557093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1062323993093533"><a name="p1062323993093533"></a><a name="p1062323993093533"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1120059198093533"><a name="p1120059198093533"></a><a name="p1120059198093533"></a>void&nbsp;</p>
<p id="p896652990093533"><a name="p896652990093533"></a><a name="p896652990093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1625253483093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p996269367093533"><a name="p996269367093533"></a><a name="p996269367093533"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p457281627093533"><a name="p457281627093533"></a><a name="p457281627093533"></a>void&nbsp;</p>
<p id="p1121755663093533"><a name="p1121755663093533"></a><a name="p1121755663093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1944412726093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1626883067093533"><a name="p1626883067093533"></a><a name="p1626883067093533"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1515105094093533"><a name="p1515105094093533"></a><a name="p1515105094093533"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p1399042173093533"><a name="p1399042173093533"></a><a name="p1399042173093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row541673721093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408237923093533"><a name="p1408237923093533"></a><a name="p1408237923093533"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p784731456093533"><a name="p784731456093533"></a><a name="p784731456093533"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p581713132093533"><a name="p581713132093533"></a><a name="p581713132093533"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row1868466256093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1716236602093533"><a name="p1716236602093533"></a><a name="p1716236602093533"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2081877500093533"><a name="p2081877500093533"></a><a name="p2081877500093533"></a>void&nbsp;</p>
<p id="p392974279093533"><a name="p392974279093533"></a><a name="p392974279093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1658454713093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p476067188093533"><a name="p476067188093533"></a><a name="p476067188093533"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p878506176093533"><a name="p878506176093533"></a><a name="p878506176093533"></a>const char *&nbsp;</p>
<p id="p1065675413093533"><a name="p1065675413093533"></a><a name="p1065675413093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row746813997093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2094209317093533"><a name="p2094209317093533"></a><a name="p2094209317093533"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p843914767093533"><a name="p843914767093533"></a><a name="p843914767093533"></a>void&nbsp;</p>
<p id="p2055504693093533"><a name="p2055504693093533"></a><a name="p2055504693093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1465201987093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997413838093533"><a name="p997413838093533"></a><a name="p997413838093533"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p31466440093533"><a name="p31466440093533"></a><a name="p31466440093533"></a>int16_t&nbsp;</p>
<p id="p773627096093533"><a name="p773627096093533"></a><a name="p773627096093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row730794581093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p223022332093533"><a name="p223022332093533"></a><a name="p223022332093533"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1395992934093533"><a name="p1395992934093533"></a><a name="p1395992934093533"></a>virtual void&nbsp;</p>
<p id="p1654920161093533"><a name="p1654920161093533"></a><a name="p1654920161093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row2004186464093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p649367527093533"><a name="p649367527093533"></a><a name="p649367527093533"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p952105775093533"><a name="p952105775093533"></a><a name="p952105775093533"></a>void&nbsp;</p>
<p id="p2009331158093533"><a name="p2009331158093533"></a><a name="p2009331158093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row868949538093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p283557777093533"><a name="p283557777093533"></a><a name="p283557777093533"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p381011899093533"><a name="p381011899093533"></a><a name="p381011899093533"></a>void&nbsp;</p>
<p id="p1286286928093533"><a name="p1286286928093533"></a><a name="p1286286928093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row520993667093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p262118726093533"><a name="p262118726093533"></a><a name="p262118726093533"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1381327811093533"><a name="p1381327811093533"></a><a name="p1381327811093533"></a>void&nbsp;</p>
<p id="p471685585093533"><a name="p471685585093533"></a><a name="p471685585093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row277635478093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p733029514093533"><a name="p733029514093533"></a><a name="p733029514093533"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p177052071093533"><a name="p177052071093533"></a><a name="p177052071093533"></a>void&nbsp;</p>
<p id="p2117984993093533"><a name="p2117984993093533"></a><a name="p2117984993093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row254667480093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1657439084093533"><a name="p1657439084093533"></a><a name="p1657439084093533"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p287109059093533"><a name="p287109059093533"></a><a name="p287109059093533"></a>void&nbsp;</p>
<p id="p1817375841093533"><a name="p1817375841093533"></a><a name="p1817375841093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1065626963093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p896016252093533"><a name="p896016252093533"></a><a name="p896016252093533"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1168831531093533"><a name="p1168831531093533"></a><a name="p1168831531093533"></a>void&nbsp;</p>
<p id="p824105557093533"><a name="p824105557093533"></a><a name="p824105557093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row81998714093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p676843084093533"><a name="p676843084093533"></a><a name="p676843084093533"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1942462826093533"><a name="p1942462826093533"></a><a name="p1942462826093533"></a>void&nbsp;</p>
<p id="p495784849093533"><a name="p495784849093533"></a><a name="p495784849093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row407453005093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p18769138093533"><a name="p18769138093533"></a><a name="p18769138093533"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1490618427093533"><a name="p1490618427093533"></a><a name="p1490618427093533"></a>void&nbsp;</p>
<p id="p782674246093533"><a name="p782674246093533"></a><a name="p782674246093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1964621430093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1007559040093533"><a name="p1007559040093533"></a><a name="p1007559040093533"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1071419406093533"><a name="p1071419406093533"></a><a name="p1071419406093533"></a>void&nbsp;</p>
<p id="p1537492670093533"><a name="p1537492670093533"></a><a name="p1537492670093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row239240303093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p320156488093533"><a name="p320156488093533"></a><a name="p320156488093533"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1308965784093533"><a name="p1308965784093533"></a><a name="p1308965784093533"></a>void&nbsp;</p>
<p id="p1927036043093533"><a name="p1927036043093533"></a><a name="p1927036043093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row2037561379093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p847418266093533"><a name="p847418266093533"></a><a name="p847418266093533"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1733371849093533"><a name="p1733371849093533"></a><a name="p1733371849093533"></a>void&nbsp;</p>
<p id="p1839401035093533"><a name="p1839401035093533"></a><a name="p1839401035093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1944387076093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p432482980093533"><a name="p432482980093533"></a><a name="p432482980093533"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1161975856093533"><a name="p1161975856093533"></a><a name="p1161975856093533"></a>void&nbsp;</p>
<p id="p665674233093533"><a name="p665674233093533"></a><a name="p665674233093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row519019290093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p342653016093533"><a name="p342653016093533"></a><a name="p342653016093533"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763523926093533"><a name="p763523926093533"></a><a name="p763523926093533"></a>void&nbsp;</p>
<p id="p691795917093533"><a name="p691795917093533"></a><a name="p691795917093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row363593497093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1107740548093533"><a name="p1107740548093533"></a><a name="p1107740548093533"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p342978512093533"><a name="p342978512093533"></a><a name="p342978512093533"></a>void&nbsp;</p>
<p id="p656133384093533"><a name="p656133384093533"></a><a name="p656133384093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row947541507093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p186751540093533"><a name="p186751540093533"></a><a name="p186751540093533"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p988348370093533"><a name="p988348370093533"></a><a name="p988348370093533"></a>void&nbsp;</p>
<p id="p1042238955093533"><a name="p1042238955093533"></a><a name="p1042238955093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row402104056093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1150300769093533"><a name="p1150300769093533"></a><a name="p1150300769093533"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p53106515093533"><a name="p53106515093533"></a><a name="p53106515093533"></a>virtual void&nbsp;</p>
<p id="p1424174871093533"><a name="p1424174871093533"></a><a name="p1424174871093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row2129555600093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2080740046093533"><a name="p2080740046093533"></a><a name="p2080740046093533"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p684847515093533"><a name="p684847515093533"></a><a name="p684847515093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p808715538093533"><a name="p808715538093533"></a><a name="p808715538093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row30278590093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1370392081093533"><a name="p1370392081093533"></a><a name="p1370392081093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1850819510093533"><a name="p1850819510093533"></a><a name="p1850819510093533"></a>void *&nbsp;</p>
<p id="p1328748505093533"><a name="p1328748505093533"></a><a name="p1328748505093533"></a>Overrides the <strong id="b1095764786093533"><a name="b1095764786093533"></a><a name="b1095764786093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row841953604093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p695113514093533"><a name="p695113514093533"></a><a name="p695113514093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858205826093533"><a name="p858205826093533"></a><a name="p858205826093533"></a>void&nbsp;</p>
<p id="p1544251786093533"><a name="p1544251786093533"></a><a name="p1544251786093533"></a>Overrides the <strong id="b392383263093533"><a name="b392383263093533"></a><a name="b392383263093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

