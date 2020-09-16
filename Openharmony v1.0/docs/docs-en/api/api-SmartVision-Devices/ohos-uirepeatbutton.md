# OHOS::UIRepeatButton<a name="EN-US_TOPIC_0000001055198156"></a>

## **Overview**<a name="section458773765093534"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Represents a repeat button. 

If a repeat button is clicked and hold, the click event is triggered continuously.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section467436759093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table2082805135093534"></a>
<table><thead align="left"><tr id="row78691587093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1592907159093534"><a name="p1592907159093534"></a><a name="p1592907159093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1540372391093534"><a name="p1540372391093534"></a><a name="p1540372391093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1166062105093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087240692093534"><a name="p2087240692093534"></a><a name="p2087240692093534"></a><a href="graphic.md#gac43cbe638a874231842ad80c23c00b0a">UIRepeatButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p214018466093534"><a name="p214018466093534"></a><a name="p214018466093534"></a> </p>
<p id="p478278767093534"><a name="p478278767093534"></a><a name="p478278767093534"></a>A constructor used to create a <strong id="b859231747093534"><a name="b859231747093534"></a><a name="b859231747093534"></a><a href="ohos-uirepeatbutton.md">UIRepeatButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row1722155391093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2028145711093534"><a name="p2028145711093534"></a><a name="p2028145711093534"></a><a href="graphic.md#ga2e2a8bc2b9aa21899356dbad7a242900">~UIRepeatButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074322364093534"><a name="p1074322364093534"></a><a name="p1074322364093534"></a>virtual </p>
<p id="p75395396093534"><a name="p75395396093534"></a><a name="p75395396093534"></a>A destructor used to delete the <strong id="b124993634093534"><a name="b124993634093534"></a><a name="b124993634093534"></a><a href="ohos-uirepeatbutton.md">UIRepeatButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row1899175384093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p460137276093534"><a name="p460137276093534"></a><a name="p460137276093534"></a><a href="graphic.md#gac391336aedd68659b7f76bee59eba521">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2105156023093534"><a name="p2105156023093534"></a><a name="p2105156023093534"></a>UIViewType </p>
<p id="p399660777093534"><a name="p399660777093534"></a><a name="p399660777093534"></a>Obtains the component type. </p>
</td>
</tr>
<tr id="row933916988093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p779655080093534"><a name="p779655080093534"></a><a name="p779655080093534"></a><a href="graphic.md#ga88637ae5acd7701ded0d0e88fb28227d">SetInterval</a> (uint16_t interval)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p224680958093534"><a name="p224680958093534"></a><a name="p224680958093534"></a>virtual void </p>
<p id="p256325696093534"><a name="p256325696093534"></a><a name="p256325696093534"></a>Sets the interval between two consecutive click events. </p>
</td>
</tr>
<tr id="row1066481675093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1497278812093534"><a name="p1497278812093534"></a><a name="p1497278812093534"></a><a href="graphic.md#gad772c84a309dbaa150b66f697e5b8ed8">GetInterval</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p417442314093534"><a name="p417442314093534"></a><a name="p417442314093534"></a>virtual uint16_t </p>
<p id="p1010879001093534"><a name="p1010879001093534"></a><a name="p1010879001093534"></a>Obtains the interval between two consecutive click events. </p>
</td>
</tr>
<tr id="row167819239093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p91516933093534"><a name="p91516933093534"></a><a name="p91516933093534"></a><a href="graphic.md#gaca17d1cfa9daa35a88d387ebc1d9352c">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1698844201093534"><a name="p1698844201093534"></a><a name="p1698844201093534"></a>virtual void </p>
<p id="p1179548146093534"><a name="p1179548146093534"></a><a name="p1179548146093534"></a>The action of click event. </p>
</td>
</tr>
<tr id="row1430348391093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p504556204093534"><a name="p504556204093534"></a><a name="p504556204093534"></a><a href="graphic.md#gadd5891c03d95d07d127558b5bc9a7bd7">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p787464795093534"><a name="p787464795093534"></a><a name="p787464795093534"></a>virtual void </p>
<p id="p185003459093534"><a name="p185003459093534"></a><a name="p185003459093534"></a>The action of release event. </p>
</td>
</tr>
<tr id="row66366717093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p557176753093534"><a name="p557176753093534"></a><a name="p557176753093534"></a><a href="graphic.md#ga33de0d99700bd1c289d967458477606f">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1071402019093534"><a name="p1071402019093534"></a><a name="p1071402019093534"></a>virtual bool </p>
<p id="p1906465724093534"><a name="p1906465724093534"></a><a name="p1906465724093534"></a>The action of long press event. </p>
</td>
</tr>
<tr id="row1803340937093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1040969461093534"><a name="p1040969461093534"></a><a name="p1040969461093534"></a><a href="graphic.md#gaba3c785f0e636cd1ac1317b9d3fcf430">HandleTickEvent</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1164664937093534"><a name="p1164664937093534"></a><a name="p1164664937093534"></a> void </p>
<p id="p1824288478093534"><a name="p1824288478093534"></a><a name="p1824288478093534"></a>handle the event of long pressing. </p>
</td>
</tr>
<tr id="row1453528031093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p833799062093534"><a name="p833799062093534"></a><a name="p833799062093534"></a><a href="graphic.md#ga3aee093d4c583223850a7ad80d5bed79">UIButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1713599096093534"><a name="p1713599096093534"></a><a name="p1713599096093534"></a> </p>
<p id="p1298067863093534"><a name="p1298067863093534"></a><a name="p1298067863093534"></a>A constructor used to create a <strong id="b2084763572093534"><a name="b2084763572093534"></a><a name="b2084763572093534"></a><a href="ohos-uibutton.md">UIButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row1184450111093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p951637235093534"><a name="p951637235093534"></a><a name="p951637235093534"></a><a href="graphic.md#ga33e30931e9b3557634b2b2be93bc41f6">UIButton</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1187625873093534"><a name="p1187625873093534"></a><a name="p1187625873093534"></a> </p>
<p id="p590978719093534"><a name="p590978719093534"></a><a name="p590978719093534"></a>A constructor used to create a <strong id="b188309460093534"><a name="b188309460093534"></a><a name="b188309460093534"></a><a href="ohos-uibutton.md">UIButton</a></strong> instance based on the button ID. </p>
</td>
</tr>
<tr id="row596230480093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1496845310093534"><a name="p1496845310093534"></a><a name="p1496845310093534"></a><a href="graphic.md#ga0c5fbcf319fc6df8170d407a337b9d8b">~UIButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p988245758093534"><a name="p988245758093534"></a><a name="p988245758093534"></a>virtual </p>
<p id="p1145037398093534"><a name="p1145037398093534"></a><a name="p1145037398093534"></a>A destructor used to delete the <strong id="b354301663093534"><a name="b354301663093534"></a><a name="b354301663093534"></a><a href="ohos-uibutton.md">UIButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row1743317652093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1876627374093534"><a name="p1876627374093534"></a><a name="p1876627374093534"></a><a href="graphic.md#gaf64d9ec1744ab9c7385dd64d30a786e4">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1635126589093534"><a name="p1635126589093534"></a><a name="p1635126589093534"></a>bool </p>
<p id="p1231339607093534"><a name="p1231339607093534"></a><a name="p1231339607093534"></a>Do something before draw, this function will be invoked mainly to check if this view need to cover invalidate area so render manager can decide which layer to draw firstly. </p>
</td>
</tr>
<tr id="row629838704093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2099086840093534"><a name="p2099086840093534"></a><a name="p2099086840093534"></a><a href="graphic.md#ga1d887720c89170abd3c8a400a791765d">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p160292050093534"><a name="p160292050093534"></a><a name="p160292050093534"></a>void </p>
<p id="p1228631741093534"><a name="p1228631741093534"></a><a name="p1228631741093534"></a>Executes the press event action. </p>
</td>
</tr>
<tr id="row1529676359093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p509753256093534"><a name="p509753256093534"></a><a name="p509753256093534"></a><a href="graphic.md#ga4f481e0ce91f87c6b70f6e0190e4f34f">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p636773259093534"><a name="p636773259093534"></a><a name="p636773259093534"></a>void </p>
<p id="p1395757066093534"><a name="p1395757066093534"></a><a name="p1395757066093534"></a>Executes the cancel event action. </p>
</td>
</tr>
<tr id="row1135296948093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1933713354093534"><a name="p1933713354093534"></a><a name="p1933713354093534"></a><a href="graphic.md#ga60194db1c1bba6a0ef963bdbbe9f972f">SetImageSrc</a> (const char *defaultImgSrc, const char *triggeredImgSrc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1791347857093534"><a name="p1791347857093534"></a><a name="p1791347857093534"></a>void </p>
<p id="p1490385263093534"><a name="p1490385263093534"></a><a name="p1490385263093534"></a>Sets the image for this button. </p>
</td>
</tr>
<tr id="row351157637093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1782297561093534"><a name="p1782297561093534"></a><a name="p1782297561093534"></a><a href="graphic.md#gab751bc5941edb403022d65d2c605a241">SetImageSrc</a> (const <a href="ohos-imageinfo.md">ImageInfo</a> *defaultImgSrc, const <a href="ohos-imageinfo.md">ImageInfo</a> *triggeredImgSrc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1080327023093534"><a name="p1080327023093534"></a><a name="p1080327023093534"></a>void </p>
<p id="p421936916093534"><a name="p421936916093534"></a><a name="p421936916093534"></a>Sets the image for this button. </p>
</td>
</tr>
<tr id="row1906197170093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p137602024093534"><a name="p137602024093534"></a><a name="p137602024093534"></a><a href="graphic.md#ga952fcbc88905cf35ec3e09bdf01375f2">SetImagePosition</a> (const int16_t x, const int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p528886144093534"><a name="p528886144093534"></a><a name="p528886144093534"></a>void </p>
<p id="p1592949941093534"><a name="p1592949941093534"></a><a name="p1592949941093534"></a>Sets the position for this image. </p>
</td>
</tr>
<tr id="row539546978093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p80045234093534"><a name="p80045234093534"></a><a name="p80045234093534"></a><a href="graphic.md#ga4d8abf189ddcbf325c60402084d7e3c3">GetImageX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p147850181093534"><a name="p147850181093534"></a><a name="p147850181093534"></a>int16_t </p>
<p id="p1583444338093534"><a name="p1583444338093534"></a><a name="p1583444338093534"></a>Obtains the x-coordinate of this image. </p>
</td>
</tr>
<tr id="row85608579093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1938209911093534"><a name="p1938209911093534"></a><a name="p1938209911093534"></a><a href="graphic.md#ga25a02afb52cc15212084fb6bc8f27afd">GetImageY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1517844705093534"><a name="p1517844705093534"></a><a name="p1517844705093534"></a>int16_t </p>
<p id="p1838464366093534"><a name="p1838464366093534"></a><a name="p1838464366093534"></a>Obtains the y-coordinate of this image. </p>
</td>
</tr>
<tr id="row985330582093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2114751878093534"><a name="p2114751878093534"></a><a name="p2114751878093534"></a><a href="graphic.md#gaf6496e4858473ab2acb80a2be6264a01">GetCurImageSrc</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p305209166093534"><a name="p305209166093534"></a><a name="p305209166093534"></a>const <a href="ohos-image.md">Image</a> * </p>
<p id="p2004811587093534"><a name="p2004811587093534"></a><a name="p2004811587093534"></a>Obtains the image for the current button state. </p>
</td>
</tr>
<tr id="row592047716093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149274819093534"><a name="p1149274819093534"></a><a name="p1149274819093534"></a><a href="graphic.md#ga8cb74b23f740091e59ad350a8dea436b">GetWidth</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1868549608093534"><a name="p1868549608093534"></a><a name="p1868549608093534"></a>int16_t </p>
<p id="p1309831528093534"><a name="p1309831528093534"></a><a name="p1309831528093534"></a>Obtains the width of this image. </p>
</td>
</tr>
<tr id="row249351246093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1369442547093534"><a name="p1369442547093534"></a><a name="p1369442547093534"></a><a href="graphic.md#ga1f8015706cfc73728696bf2bbd3e833b">GetHeight</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1772253993093534"><a name="p1772253993093534"></a><a name="p1772253993093534"></a>int16_t </p>
<p id="p1665444374093534"><a name="p1665444374093534"></a><a name="p1665444374093534"></a>Obtains the height of this image. </p>
</td>
</tr>
<tr id="row1970098178093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1633333524093534"><a name="p1633333524093534"></a><a name="p1633333524093534"></a><a href="graphic.md#ga420f927c473cec8c6f3265ff7c35336f">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1857256016093534"><a name="p1857256016093534"></a><a name="p1857256016093534"></a>void </p>
<p id="p570093075093534"><a name="p570093075093534"></a><a name="p570093075093534"></a>Sets the width for this image. </p>
</td>
</tr>
<tr id="row942815336093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494956396093534"><a name="p1494956396093534"></a><a name="p1494956396093534"></a><a href="graphic.md#ga8b6dbfcd0328753c2c3cef4d14b0ff30">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p243498572093534"><a name="p243498572093534"></a><a name="p243498572093534"></a>void </p>
<p id="p321380791093534"><a name="p321380791093534"></a><a name="p321380791093534"></a>Sets the height for this image. </p>
</td>
</tr>
<tr id="row1699945211093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p577235171093534"><a name="p577235171093534"></a><a name="p577235171093534"></a><a href="graphic.md#ga93994f4d735e4f9a7d3e7d737e2c620c">GetContentRect</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1451514364093534"><a name="p1451514364093534"></a><a name="p1451514364093534"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p163724064093534"><a name="p163724064093534"></a><a name="p163724064093534"></a>Obtains a rectangular area that contains coordinate information. </p>
</td>
</tr>
<tr id="row1947936715093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1695816451093534"><a name="p1695816451093534"></a><a name="p1695816451093534"></a><a href="graphic.md#ga37736a82bec6a01bc5a880e1d01ccccd">GetStyle</a> (uint8_t key) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p780749489093534"><a name="p780749489093534"></a><a name="p780749489093534"></a>int64_t </p>
<p id="p1559654860093534"><a name="p1559654860093534"></a><a name="p1559654860093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1282284016093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p776886370093534"><a name="p776886370093534"></a><a name="p776886370093534"></a><a href="graphic.md#gaa5fdd9b28b8c919dbde0e34d8ae38caf">SetStyle</a> (uint8_t key, int64_t value) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1248723666093534"><a name="p1248723666093534"></a><a name="p1248723666093534"></a>void </p>
<p id="p712840273093534"><a name="p712840273093534"></a><a name="p712840273093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1670554888093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1875127652093534"><a name="p1875127652093534"></a><a name="p1875127652093534"></a><a href="graphic.md#gaa3f74af93c91a24e58fdd06ad7d0bdf9">GetStyleForState</a> (uint8_t key, <a href="graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> state) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1025516871093534"><a name="p1025516871093534"></a><a name="p1025516871093534"></a>int64_t </p>
<p id="p1268294873093534"><a name="p1268294873093534"></a><a name="p1268294873093534"></a>Obtains the style of a button in a specific state. </p>
</td>
</tr>
<tr id="row1462380076093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p551727950093534"><a name="p551727950093534"></a><a name="p551727950093534"></a><a href="graphic.md#ga7ece04980fa99a277bfbb591771f47f1">SetStyleForState</a> (uint8_t key, int64_t value, <a href="graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p274916666093534"><a name="p274916666093534"></a><a name="p274916666093534"></a>void </p>
<p id="p1730341674093534"><a name="p1730341674093534"></a><a name="p1730341674093534"></a>Sets the style for a button in a specific state. </p>
</td>
</tr>
<tr id="row1254140788093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p351994565093534"><a name="p351994565093534"></a><a name="p351994565093534"></a><a href="graphic.md#ga283131701e907e586964189818d04411">Disable</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p852342060093534"><a name="p852342060093534"></a><a name="p852342060093534"></a>void </p>
<p id="p1893579207093534"><a name="p1893579207093534"></a><a name="p1893579207093534"></a>Disables this button. </p>
</td>
</tr>
<tr id="row677224064093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1074772813093534"><a name="p1074772813093534"></a><a name="p1074772813093534"></a><a href="graphic.md#ga3185df8b60a609564f978ed9576fb813">Enable</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p929031585093534"><a name="p929031585093534"></a><a name="p929031585093534"></a>void </p>
<p id="p1694279079093534"><a name="p1694279079093534"></a><a name="p1694279079093534"></a>Enables this button. </p>
</td>
</tr>
<tr id="row857016353093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1905118495093534"><a name="p1905118495093534"></a><a name="p1905118495093534"></a><a href="graphic.md#ga737d850b2adf8a2977369e611764b1ae">SetStateForStyle</a> (<a href="graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1188208467093534"><a name="p1188208467093534"></a><a name="p1188208467093534"></a>void </p>
<p id="p1240041528093534"><a name="p1240041528093534"></a><a name="p1240041528093534"></a>Sets the state for a button. After the setting, calling <a href="graphic.md#gaa5fdd9b28b8c919dbde0e34d8ae38caf">SetStyle</a> will change the style of this button, but not its state. </p>
</td>
</tr>
<tr id="row1081815407093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1273279586093534"><a name="p1273279586093534"></a><a name="p1273279586093534"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1830007744093534"><a name="p1830007744093534"></a><a name="p1830007744093534"></a> </p>
<p id="p1090108349093534"><a name="p1090108349093534"></a><a name="p1090108349093534"></a>A default constructor used to create an <strong id="b645472216093534"><a name="b645472216093534"></a><a name="b645472216093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row996685510093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2107082897093534"><a name="p2107082897093534"></a><a name="p2107082897093534"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1808685823093534"><a name="p1808685823093534"></a><a name="p1808685823093534"></a> </p>
<p id="p624046912093534"><a name="p624046912093534"></a><a name="p624046912093534"></a>A constructor used to create an <strong id="b135202093534"><a name="b135202093534"></a><a name="b135202093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row655013357093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2006073185093534"><a name="p2006073185093534"></a><a name="p2006073185093534"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267777253093534"><a name="p267777253093534"></a><a name="p267777253093534"></a>virtual </p>
<p id="p1998758804093534"><a name="p1998758804093534"></a><a name="p1998758804093534"></a>A destructor used to delete the <strong id="b1357015582093534"><a name="b1357015582093534"></a><a name="b1357015582093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row2088422903093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2145629140093534"><a name="p2145629140093534"></a><a name="p2145629140093534"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1279646541093534"><a name="p1279646541093534"></a><a name="p1279646541093534"></a>virtual void </p>
<p id="p1794915279093534"><a name="p1794915279093534"></a><a name="p1794915279093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1862955333093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1397901125093534"><a name="p1397901125093534"></a><a name="p1397901125093534"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1837508865093534"><a name="p1837508865093534"></a><a name="p1837508865093534"></a>virtual void </p>
<p id="p1286156727093534"><a name="p1286156727093534"></a><a name="p1286156727093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row401278462093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419689680093534"><a name="p419689680093534"></a><a name="p419689680093534"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1477730386093534"><a name="p1477730386093534"></a><a name="p1477730386093534"></a>void </p>
<p id="p764878195093534"><a name="p764878195093534"></a><a name="p764878195093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row800791998093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p292192205093534"><a name="p292192205093534"></a><a name="p292192205093534"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p100777735093534"><a name="p100777735093534"></a><a name="p100777735093534"></a>void </p>
<p id="p1787065837093534"><a name="p1787065837093534"></a><a name="p1787065837093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row537610249093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1684191954093534"><a name="p1684191954093534"></a><a name="p1684191954093534"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1855032212093534"><a name="p1855032212093534"></a><a name="p1855032212093534"></a>virtual bool </p>
<p id="p887346516093534"><a name="p887346516093534"></a><a name="p887346516093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1944564209093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1944171654093534"><a name="p1944171654093534"></a><a name="p1944171654093534"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p684966769093534"><a name="p684966769093534"></a><a name="p684966769093534"></a>virtual bool </p>
<p id="p1934073370093534"><a name="p1934073370093534"></a><a name="p1934073370093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row243400030093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p3403549093534"><a name="p3403549093534"></a><a name="p3403549093534"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1836764208093534"><a name="p1836764208093534"></a><a name="p1836764208093534"></a>virtual bool </p>
<p id="p1736424219093534"><a name="p1736424219093534"></a><a name="p1736424219093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row100330070093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p52912682093534"><a name="p52912682093534"></a><a name="p52912682093534"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p56604915093534"><a name="p56604915093534"></a><a name="p56604915093534"></a>void </p>
<p id="p649181544093534"><a name="p649181544093534"></a><a name="p649181544093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1653292222093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1064367459093534"><a name="p1064367459093534"></a><a name="p1064367459093534"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p223018847093534"><a name="p223018847093534"></a><a name="p223018847093534"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p681823225093534"><a name="p681823225093534"></a><a name="p681823225093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row655911755093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1284220393093534"><a name="p1284220393093534"></a><a name="p1284220393093534"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p787394740093534"><a name="p787394740093534"></a><a name="p787394740093534"></a>void </p>
<p id="p656691919093534"><a name="p656691919093534"></a><a name="p656691919093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1051330696093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2102525366093534"><a name="p2102525366093534"></a><a name="p2102525366093534"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1542376396093534"><a name="p1542376396093534"></a><a name="p1542376396093534"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p2005724326093534"><a name="p2005724326093534"></a><a name="p2005724326093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row847118254093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p824596750093534"><a name="p824596750093534"></a><a name="p824596750093534"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p29254809093534"><a name="p29254809093534"></a><a name="p29254809093534"></a>void </p>
<p id="p2038152619093534"><a name="p2038152619093534"></a><a name="p2038152619093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1839965374093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1605534416093534"><a name="p1605534416093534"></a><a name="p1605534416093534"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1292518794093534"><a name="p1292518794093534"></a><a name="p1292518794093534"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p1830481124093534"><a name="p1830481124093534"></a><a name="p1830481124093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1002573371093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p590286529093534"><a name="p590286529093534"></a><a name="p590286529093534"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p172876928093534"><a name="p172876928093534"></a><a name="p172876928093534"></a>void </p>
<p id="p1452181733093534"><a name="p1452181733093534"></a><a name="p1452181733093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row52350119093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p529408758093534"><a name="p529408758093534"></a><a name="p529408758093534"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p150100197093534"><a name="p150100197093534"></a><a name="p150100197093534"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1645233000093534"><a name="p1645233000093534"></a><a name="p1645233000093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row37952288093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p472390611093534"><a name="p472390611093534"></a><a name="p472390611093534"></a><a href="graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27114537093534"><a name="p27114537093534"></a><a name="p27114537093534"></a>virtual void </p>
<p id="p45604965093534"><a name="p45604965093534"></a><a name="p45604965093534"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row1308191596093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1103160645093534"><a name="p1103160645093534"></a><a name="p1103160645093534"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1542721330093534"><a name="p1542721330093534"></a><a name="p1542721330093534"></a>void </p>
<p id="p598255585093534"><a name="p598255585093534"></a><a name="p598255585093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1414734065093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1501224909093534"><a name="p1501224909093534"></a><a name="p1501224909093534"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p56457760093534"><a name="p56457760093534"></a><a name="p56457760093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1097369742093534"><a name="p1097369742093534"></a><a name="p1097369742093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1537159295093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p347074044093534"><a name="p347074044093534"></a><a name="p347074044093534"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2005624994093534"><a name="p2005624994093534"></a><a name="p2005624994093534"></a>void </p>
<p id="p470353415093534"><a name="p470353415093534"></a><a name="p470353415093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row923176158093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p603413225093534"><a name="p603413225093534"></a><a name="p603413225093534"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p724658002093534"><a name="p724658002093534"></a><a name="p724658002093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1299195295093534"><a name="p1299195295093534"></a><a name="p1299195295093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1348751367093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p800613473093534"><a name="p800613473093534"></a><a name="p800613473093534"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p356624769093534"><a name="p356624769093534"></a><a name="p356624769093534"></a>virtual void </p>
<p id="p11959115093534"><a name="p11959115093534"></a><a name="p11959115093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row960381479093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p104345191093534"><a name="p104345191093534"></a><a name="p104345191093534"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1733468931093534"><a name="p1733468931093534"></a><a name="p1733468931093534"></a>bool </p>
<p id="p1286635310093534"><a name="p1286635310093534"></a><a name="p1286635310093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1150869028093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1639584052093534"><a name="p1639584052093534"></a><a name="p1639584052093534"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1133837612093534"><a name="p1133837612093534"></a><a name="p1133837612093534"></a>void </p>
<p id="p949581635093534"><a name="p949581635093534"></a><a name="p949581635093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row906489735093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p480614599093534"><a name="p480614599093534"></a><a name="p480614599093534"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1827357244093534"><a name="p1827357244093534"></a><a name="p1827357244093534"></a>bool </p>
<p id="p1264899788093534"><a name="p1264899788093534"></a><a name="p1264899788093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1107372209093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p489555850093534"><a name="p489555850093534"></a><a name="p489555850093534"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p380240199093534"><a name="p380240199093534"></a><a name="p380240199093534"></a>void </p>
<p id="p1101868211093534"><a name="p1101868211093534"></a><a name="p1101868211093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row989316152093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1363737384093534"><a name="p1363737384093534"></a><a name="p1363737384093534"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1665858203093534"><a name="p1665858203093534"></a><a name="p1665858203093534"></a>bool </p>
<p id="p1932414424093534"><a name="p1932414424093534"></a><a name="p1932414424093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row25680721093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1739311261093534"><a name="p1739311261093534"></a><a name="p1739311261093534"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p593207751093534"><a name="p593207751093534"></a><a name="p593207751093534"></a>void </p>
<p id="p893790595093534"><a name="p893790595093534"></a><a name="p893790595093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1472831303093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1129750922093534"><a name="p1129750922093534"></a><a name="p1129750922093534"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p509883838093534"><a name="p509883838093534"></a><a name="p509883838093534"></a>bool </p>
<p id="p1996859250093534"><a name="p1996859250093534"></a><a name="p1996859250093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1697482237093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p193742412093534"><a name="p193742412093534"></a><a name="p193742412093534"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1278758032093534"><a name="p1278758032093534"></a><a name="p1278758032093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p2011537615093534"><a name="p2011537615093534"></a><a name="p2011537615093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1818618351093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985386459093534"><a name="p1985386459093534"></a><a name="p1985386459093534"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1740883184093534"><a name="p1740883184093534"></a><a name="p1740883184093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p564342496093534"><a name="p564342496093534"></a><a name="p564342496093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row624519002093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p837616093093534"><a name="p837616093093534"></a><a name="p837616093093534"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1351828499093534"><a name="p1351828499093534"></a><a name="p1351828499093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1215779115093534"><a name="p1215779115093534"></a><a name="p1215779115093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1953241049093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969750841093534"><a name="p1969750841093534"></a><a name="p1969750841093534"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1916907810093534"><a name="p1916907810093534"></a><a name="p1916907810093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p846564680093534"><a name="p846564680093534"></a><a name="p846564680093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row841947659093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985814486093534"><a name="p1985814486093534"></a><a name="p1985814486093534"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459083016093534"><a name="p1459083016093534"></a><a name="p1459083016093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1269442493093534"><a name="p1269442493093534"></a><a name="p1269442493093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1986056988093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p553039581093534"><a name="p553039581093534"></a><a name="p553039581093534"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2016371551093534"><a name="p2016371551093534"></a><a name="p2016371551093534"></a>void </p>
<p id="p391797540093534"><a name="p391797540093534"></a><a name="p391797540093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1542138877093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1195231361093534"><a name="p1195231361093534"></a><a name="p1195231361093534"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1594425240093534"><a name="p1594425240093534"></a><a name="p1594425240093534"></a>virtual void </p>
<p id="p572361654093534"><a name="p572361654093534"></a><a name="p572361654093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row106614406093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p731787312093534"><a name="p731787312093534"></a><a name="p731787312093534"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705625685093534"><a name="p1705625685093534"></a><a name="p1705625685093534"></a>virtual void </p>
<p id="p2047979503093534"><a name="p2047979503093534"></a><a name="p2047979503093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row312938415093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1913407224093534"><a name="p1913407224093534"></a><a name="p1913407224093534"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142448657093534"><a name="p142448657093534"></a><a name="p142448657093534"></a>int16_t </p>
<p id="p115800020093534"><a name="p115800020093534"></a><a name="p115800020093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1636432897093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1329001938093534"><a name="p1329001938093534"></a><a name="p1329001938093534"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p913878113093534"><a name="p913878113093534"></a><a name="p913878113093534"></a>virtual void </p>
<p id="p634262631093534"><a name="p634262631093534"></a><a name="p634262631093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row20341014093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14882067093534"><a name="p14882067093534"></a><a name="p14882067093534"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1341013840093534"><a name="p1341013840093534"></a><a name="p1341013840093534"></a>int16_t </p>
<p id="p1597902006093534"><a name="p1597902006093534"></a><a name="p1597902006093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1276171964093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p120396116093534"><a name="p120396116093534"></a><a name="p120396116093534"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p823477397093534"><a name="p823477397093534"></a><a name="p823477397093534"></a>virtual void </p>
<p id="p1884875213093534"><a name="p1884875213093534"></a><a name="p1884875213093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1690167422093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1939856782093534"><a name="p1939856782093534"></a><a name="p1939856782093534"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2095332218093534"><a name="p2095332218093534"></a><a name="p2095332218093534"></a>virtual void </p>
<p id="p470934782093534"><a name="p470934782093534"></a><a name="p470934782093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row130097990093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1329414956093534"><a name="p1329414956093534"></a><a name="p1329414956093534"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1270464686093534"><a name="p1270464686093534"></a><a name="p1270464686093534"></a>bool </p>
<p id="p2023461723093534"><a name="p2023461723093534"></a><a name="p2023461723093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row917837367093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329757944093534"><a name="p329757944093534"></a><a name="p329757944093534"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1080220791093534"><a name="p1080220791093534"></a><a name="p1080220791093534"></a>void </p>
<p id="p1933102875093534"><a name="p1933102875093534"></a><a name="p1933102875093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row276245813093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1883784677093534"><a name="p1883784677093534"></a><a name="p1883784677093534"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p180144445093534"><a name="p180144445093534"></a><a name="p180144445093534"></a>void </p>
<p id="p165617247093534"><a name="p165617247093534"></a><a name="p165617247093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1086921144093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1684690804093534"><a name="p1684690804093534"></a><a name="p1684690804093534"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p341688712093534"><a name="p341688712093534"></a><a name="p341688712093534"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p869923532093534"><a name="p869923532093534"></a><a name="p869923532093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row401005550093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1982245018093534"><a name="p1982245018093534"></a><a name="p1982245018093534"></a><a href="graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1239891758093534"><a name="p1239891758093534"></a><a name="p1239891758093534"></a>virtual <a href="ohos-uiview.md">UIView</a> * </p>
<p id="p194748763093534"><a name="p194748763093534"></a><a name="p194748763093534"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row1674757178093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1813279394093534"><a name="p1813279394093534"></a><a name="p1813279394093534"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1909111564093534"><a name="p1909111564093534"></a><a name="p1909111564093534"></a>void </p>
<p id="p139247417093534"><a name="p139247417093534"></a><a name="p139247417093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1401832475093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1661841737093534"><a name="p1661841737093534"></a><a name="p1661841737093534"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1953789191093534"><a name="p1953789191093534"></a><a name="p1953789191093534"></a>const char * </p>
<p id="p1732169054093534"><a name="p1732169054093534"></a><a name="p1732169054093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row269104096093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1670623816093534"><a name="p1670623816093534"></a><a name="p1670623816093534"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p939033190093534"><a name="p939033190093534"></a><a name="p939033190093534"></a>void </p>
<p id="p778480448093534"><a name="p778480448093534"></a><a name="p778480448093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row764673018093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217914463093534"><a name="p1217914463093534"></a><a name="p1217914463093534"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369744638093534"><a name="p369744638093534"></a><a name="p369744638093534"></a>int16_t </p>
<p id="p910647096093534"><a name="p910647096093534"></a><a name="p910647096093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row634224050093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1913479764093534"><a name="p1913479764093534"></a><a name="p1913479764093534"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1544758435093534"><a name="p1544758435093534"></a><a name="p1544758435093534"></a>virtual void </p>
<p id="p219357190093534"><a name="p219357190093534"></a><a name="p219357190093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1378060274093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p425183102093534"><a name="p425183102093534"></a><a name="p425183102093534"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p551244279093534"><a name="p551244279093534"></a><a name="p551244279093534"></a>void </p>
<p id="p101747972093534"><a name="p101747972093534"></a><a name="p101747972093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row827383327093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1848280539093534"><a name="p1848280539093534"></a><a name="p1848280539093534"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p506231952093534"><a name="p506231952093534"></a><a name="p506231952093534"></a>void </p>
<p id="p2045571436093534"><a name="p2045571436093534"></a><a name="p2045571436093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row188482428093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1304685727093534"><a name="p1304685727093534"></a><a name="p1304685727093534"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1655761845093534"><a name="p1655761845093534"></a><a name="p1655761845093534"></a>void </p>
<p id="p760141788093534"><a name="p760141788093534"></a><a name="p760141788093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1596459665093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p585604718093534"><a name="p585604718093534"></a><a name="p585604718093534"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p307998572093534"><a name="p307998572093534"></a><a name="p307998572093534"></a>void </p>
<p id="p466533902093534"><a name="p466533902093534"></a><a name="p466533902093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row17129889093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245910030093534"><a name="p1245910030093534"></a><a name="p1245910030093534"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p775386730093534"><a name="p775386730093534"></a><a name="p775386730093534"></a>void </p>
<p id="p1157820077093534"><a name="p1157820077093534"></a><a name="p1157820077093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1635103005093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p354824426093534"><a name="p354824426093534"></a><a name="p354824426093534"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1942733893093534"><a name="p1942733893093534"></a><a name="p1942733893093534"></a>void </p>
<p id="p844061598093534"><a name="p844061598093534"></a><a name="p844061598093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row383720000093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p187172798093534"><a name="p187172798093534"></a><a name="p187172798093534"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1542185607093534"><a name="p1542185607093534"></a><a name="p1542185607093534"></a>void </p>
<p id="p864852226093534"><a name="p864852226093534"></a><a name="p864852226093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1504687749093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p763009501093534"><a name="p763009501093534"></a><a name="p763009501093534"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1302016322093534"><a name="p1302016322093534"></a><a name="p1302016322093534"></a>void </p>
<p id="p1883477399093534"><a name="p1883477399093534"></a><a name="p1883477399093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1649307349093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p134785044093534"><a name="p134785044093534"></a><a name="p134785044093534"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p86320098093534"><a name="p86320098093534"></a><a name="p86320098093534"></a>void </p>
<p id="p388124569093534"><a name="p388124569093534"></a><a name="p388124569093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1385711156093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2138567058093534"><a name="p2138567058093534"></a><a name="p2138567058093534"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1875971030093534"><a name="p1875971030093534"></a><a name="p1875971030093534"></a>void </p>
<p id="p990253112093534"><a name="p990253112093534"></a><a name="p990253112093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row435241714093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2103290957093534"><a name="p2103290957093534"></a><a name="p2103290957093534"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p554124881093534"><a name="p554124881093534"></a><a name="p554124881093534"></a>void </p>
<p id="p1124204630093534"><a name="p1124204630093534"></a><a name="p1124204630093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row2085919910093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p92883268093534"><a name="p92883268093534"></a><a name="p92883268093534"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601090927093534"><a name="p1601090927093534"></a><a name="p1601090927093534"></a>void </p>
<p id="p1502860442093534"><a name="p1502860442093534"></a><a name="p1502860442093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row929844705093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p593282768093534"><a name="p593282768093534"></a><a name="p593282768093534"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1787110623093534"><a name="p1787110623093534"></a><a name="p1787110623093534"></a>void </p>
<p id="p1728253421093534"><a name="p1728253421093534"></a><a name="p1728253421093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row800216262093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1040309611093534"><a name="p1040309611093534"></a><a name="p1040309611093534"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1037390675093534"><a name="p1037390675093534"></a><a name="p1037390675093534"></a>void </p>
<p id="p1942365031093534"><a name="p1942365031093534"></a><a name="p1942365031093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row459461277093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419376485093534"><a name="p419376485093534"></a><a name="p419376485093534"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p179690572093534"><a name="p179690572093534"></a><a name="p179690572093534"></a>void </p>
<p id="p716532476093534"><a name="p716532476093534"></a><a name="p716532476093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1305209936093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p83753049093534"><a name="p83753049093534"></a><a name="p83753049093534"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p581831641093534"><a name="p581831641093534"></a><a name="p581831641093534"></a>virtual void </p>
<p id="p1568403571093534"><a name="p1568403571093534"></a><a name="p1568403571093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1080134329093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1807477927093534"><a name="p1807477927093534"></a><a name="p1807477927093534"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1525409153093534"><a name="p1525409153093534"></a><a name="p1525409153093534"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p189355994093534"><a name="p189355994093534"></a><a name="p189355994093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1857275685093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p342324853093534"><a name="p342324853093534"></a><a name="p342324853093534"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p30451655093534"><a name="p30451655093534"></a><a name="p30451655093534"></a>void * </p>
<p id="p497037344093534"><a name="p497037344093534"></a><a name="p497037344093534"></a>Overrides the <strong id="b1791030340093534"><a name="b1791030340093534"></a><a name="b1791030340093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1686050929093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1790204641093534"><a name="p1790204641093534"></a><a name="p1790204641093534"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1182903239093534"><a name="p1182903239093534"></a><a name="p1182903239093534"></a>void </p>
<p id="p930331290093534"><a name="p930331290093534"></a><a name="p930331290093534"></a>Overrides the <strong id="b1660850415093534"><a name="b1660850415093534"></a><a name="b1660850415093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table869043995093534"></a>
<table><thead align="left"><tr id="row317235485093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p803837192093534"><a name="p803837192093534"></a><a name="p803837192093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p254472959093534"><a name="p254472959093534"></a><a name="p254472959093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row107460657093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1897655616093534"><a name="p1897655616093534"></a><a name="p1897655616093534"></a><a href="graphic.md#gaf9f6c0c373f090e79b9e8d847e186e92">ButtonImageSrc</a> : uint8_t </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1415475536093534"><a name="p1415475536093534"></a><a name="p1415475536093534"></a>Enumerates the images for different button states. </p>
</td>
</tr>
<tr id="row1068128076093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1137918625093534"><a name="p1137918625093534"></a><a name="p1137918625093534"></a><a href="graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> : uint8_t </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p977617960093534"><a name="p977617960093534"></a><a name="p977617960093534"></a>Enumerates the states of this button. </p>
</td>
</tr>
</tbody>
</table>

