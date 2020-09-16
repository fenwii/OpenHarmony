# OHOS::UIDigitalClock<a name="ZH-CN_TOPIC_0000001055358132"></a>

## **Overview**<a name="section995120822093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Displays time digitally. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1500627122093534"></a>

## Public Types<a name="pub-types"></a>

<a name="table531156608093534"></a>
<table><thead align="left"><tr id="row704799221093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p962153826093534"><a name="p962153826093534"></a><a name="p962153826093534"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p361590715093534"><a name="p361590715093534"></a><a name="p361590715093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2037336362093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p28997224093534"><a name="p28997224093534"></a><a name="p28997224093534"></a><a href="Graphic.md#gabe3b64b11e5bf5d7b54e1039e40f306b">DisplayMode</a> { <a href="Graphic.md#ggabe3b64b11e5bf5d7b54e1039e40f306bafc93e631e582de9e4128be8e6d41dbfe">DISPLAY_12_HOUR_NO_SECONDS</a>, <a href="Graphic.md#ggabe3b64b11e5bf5d7b54e1039e40f306ba0c5adc8c80a47a33eb7bfcbcad0b4163">DISPLAY_24_HOUR_NO_SECONDS</a>, <a href="Graphic.md#ggabe3b64b11e5bf5d7b54e1039e40f306baa5cbeab2c7366db7f33b2e95da20615b">DISPLAY_12_HOUR</a>, <a href="Graphic.md#ggabe3b64b11e5bf5d7b54e1039e40f306ba833c0664bba32e6fe4a53a1c471d0eb8">DISPLAY_24_HOUR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p645868214093534"><a name="p645868214093534"></a><a name="p645868214093534"></a>Enumerates the display modes of this digital clock. </p>
</td>
</tr>
<tr id="row1711357013093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2100254224093534"><a name="p2100254224093534"></a><a name="p2100254224093534"></a><a href="Graphic.md#gaa6aacc9ecbf5e20f22e50e542a69f472">TimeElement</a> { <a href="Graphic.md#ggaa6aacc9ecbf5e20f22e50e542a69f472a8c15c8462a73ec9c9d9d3ad542ba4946">HOUR_ELEMENT</a>, <a href="Graphic.md#ggaa6aacc9ecbf5e20f22e50e542a69f472ae60c24ee0bb6908798a770cb39034de2">MINUTE_ELEMENT</a>, <a href="Graphic.md#ggaa6aacc9ecbf5e20f22e50e542a69f472a0299da12b65446f25e530d8d20881a1a">SECOND_ELEMENT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2048155052093534"><a name="p2048155052093534"></a><a name="p2048155052093534"></a>Enumerates the time elements of this digital clock. </p>
</td>
</tr>
<tr id="row415295817093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p643391642093534"><a name="p643391642093534"></a><a name="p643391642093534"></a><a href="Graphic.md#ga19db90932bc71e6bbced6ccf2935ac98">WorkMode</a> { <a href="Graphic.md#gga19db90932bc71e6bbced6ccf2935ac98a2025ac1a1f63409f0b37f444547ec859">ALWAYS_ON</a>, <a href="Graphic.md#gga19db90932bc71e6bbced6ccf2935ac98a8d32f103a422c6675618f5e9773b2eaa">NORMAL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1787184089093534"><a name="p1787184089093534"></a><a name="p1787184089093534"></a>Enumerates the working modes of this clock. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table586759558093534"></a>
<table><thead align="left"><tr id="row1474836518093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1548160599093534"><a name="p1548160599093534"></a><a name="p1548160599093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p426411684093534"><a name="p426411684093534"></a><a name="p426411684093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row307944113093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2061853759093534"><a name="p2061853759093534"></a><a name="p2061853759093534"></a><a href="Graphic.md#gac89c3f554cea687e0b7d7338319c8d0b">UIDigitalClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p856910440093534"><a name="p856910440093534"></a><a name="p856910440093534"></a>&nbsp;</p>
<p id="p1691419971093534"><a name="p1691419971093534"></a><a name="p1691419971093534"></a>A default constructor used to create a <strong id="b2053598396093534"><a name="b2053598396093534"></a><a name="b2053598396093534"></a><a href="OHOS-UIDigitalClock.md">UIDigitalClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row1710680658093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p912447869093534"><a name="p912447869093534"></a><a name="p912447869093534"></a><a href="Graphic.md#gaf4daabe77c9ab8264618a4f970b0a15e">~UIDigitalClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1970289806093534"><a name="p1970289806093534"></a><a name="p1970289806093534"></a>virtual&nbsp;</p>
<p id="p270811924093534"><a name="p270811924093534"></a><a name="p270811924093534"></a>A destructor used to delete the <strong id="b1225461805093534"><a name="b1225461805093534"></a><a name="b1225461805093534"></a><a href="OHOS-UIDigitalClock.md">UIDigitalClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row393515302093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1393972049093534"><a name="p1393972049093534"></a><a name="p1393972049093534"></a><a href="Graphic.md#ga567a8195e8520b74b682de697cfe1d90">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1070576500093534"><a name="p1070576500093534"></a><a name="p1070576500093534"></a>UIViewType&nbsp;</p>
<p id="p1128159764093534"><a name="p1128159764093534"></a><a name="p1128159764093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1346467371093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1590849186093534"><a name="p1590849186093534"></a><a name="p1590849186093534"></a><a href="Graphic.md#ga9013bc4fa8bfc77cf75b898db1a0fbf6">SetFontId</a> (uint8_t fontId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p670973810093534"><a name="p670973810093534"></a><a name="p670973810093534"></a>void&nbsp;</p>
<p id="p45676163093534"><a name="p45676163093534"></a><a name="p45676163093534"></a>Sets the dynamic font ID for this digital clock. </p>
</td>
</tr>
<tr id="row799953471093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1269102481093534"><a name="p1269102481093534"></a><a name="p1269102481093534"></a><a href="Graphic.md#gaa41d0c6ab53a4451e9e90199dbaa3895">SetFont</a> (const char *name, uint8_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1526594798093534"><a name="p1526594798093534"></a><a name="p1526594798093534"></a>void&nbsp;</p>
<p id="p1785101380093534"><a name="p1785101380093534"></a><a name="p1785101380093534"></a>Sets the dynamic font for this digital clock. </p>
</td>
</tr>
<tr id="row962254009093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p430610357093534"><a name="p430610357093534"></a><a name="p430610357093534"></a><a href="Graphic.md#gaabdefd6f104682c755886594e259e810">SetColor</a> (<a href="OHOS-Color32.md">ColorType</a> color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p325800704093534"><a name="p325800704093534"></a><a name="p325800704093534"></a>void&nbsp;</p>
<p id="p618823139093534"><a name="p618823139093534"></a><a name="p618823139093534"></a>Sets the font color for this digital clock. </p>
</td>
</tr>
<tr id="row1005360307093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p722968684093534"><a name="p722968684093534"></a><a name="p722968684093534"></a><a href="Graphic.md#ga2ac4d800eb47c4238d160819e165a30a">SetDisplayMode</a> (<a href="Graphic.md#gabe3b64b11e5bf5d7b54e1039e40f306b">DisplayMode</a> dm)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1050358232093534"><a name="p1050358232093534"></a><a name="p1050358232093534"></a>void&nbsp;</p>
<p id="p1751395009093534"><a name="p1751395009093534"></a><a name="p1751395009093534"></a>Sets the display mode for this digital clock. </p>
</td>
</tr>
<tr id="row367669971093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p76801914093534"><a name="p76801914093534"></a><a name="p76801914093534"></a><a href="Graphic.md#ga14a5b4ca3e2eda9ff0f6a7ad2bc11f48">GetDisplayMode</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p11215245093534"><a name="p11215245093534"></a><a name="p11215245093534"></a><a href="Graphic.md#gabe3b64b11e5bf5d7b54e1039e40f306b">DisplayMode</a>&nbsp;</p>
<p id="p966105068093534"><a name="p966105068093534"></a><a name="p966105068093534"></a>Obtains the display mode of this digital clock. </p>
</td>
</tr>
<tr id="row687443377093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p113231917093534"><a name="p113231917093534"></a><a name="p113231917093534"></a><a href="Graphic.md#gaf45e9196d307551e693807cae2f8b4d2">DisplayLeadingZero</a> (bool displayLeadingZero)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p133791294093534"><a name="p133791294093534"></a><a name="p133791294093534"></a>void&nbsp;</p>
<p id="p1546437871093534"><a name="p1546437871093534"></a><a name="p1546437871093534"></a>Sets whether to add <strong id="b1099496478093534"><a name="b1099496478093534"></a><a name="b1099496478093534"></a>0</strong> before the hour of this digital clock. </p>
</td>
</tr>
<tr id="row233908690093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14304712093534"><a name="p14304712093534"></a><a name="p14304712093534"></a><a href="Graphic.md#ga1565dcdb5ab0403fa477fd74c5920b99">SetOpacity</a> (uint8_t opacity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1935912004093534"><a name="p1935912004093534"></a><a name="p1935912004093534"></a>void&nbsp;</p>
<p id="p1825541765093534"><a name="p1825541765093534"></a><a name="p1825541765093534"></a>Sets the opacity for this digital clock. </p>
</td>
</tr>
<tr id="row1281982637093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p238623492093534"><a name="p238623492093534"></a><a name="p238623492093534"></a><a href="Graphic.md#ga713ec508a94eb05eab0aa5ab1c7f41ca">GetOpacity</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1877031079093534"><a name="p1877031079093534"></a><a name="p1877031079093534"></a>uint8_t&nbsp;</p>
<p id="p2044641740093534"><a name="p2044641740093534"></a><a name="p2044641740093534"></a>Obtains the opacity of this digital clock. </p>
</td>
</tr>
<tr id="row787770041093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1157021099093534"><a name="p1157021099093534"></a><a name="p1157021099093534"></a><a href="Graphic.md#ga386c03c483ef38cb5310563b6ba9bc02">UpdateClock</a> (bool clockInit) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1812569311093534"><a name="p1812569311093534"></a><a name="p1812569311093534"></a>void&nbsp;</p>
<p id="p1677720070093534"><a name="p1677720070093534"></a><a name="p1677720070093534"></a>Updates this digital clock. </p>
</td>
</tr>
<tr id="row753226145093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p136892745093534"><a name="p136892745093534"></a><a name="p136892745093534"></a><a href="Graphic.md#ga160a40d9f81c72b606b3c5b05168bacf">UIAbstractClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p632915389093534"><a name="p632915389093534"></a><a name="p632915389093534"></a>&nbsp;</p>
<p id="p1562087628093534"><a name="p1562087628093534"></a><a name="p1562087628093534"></a>A default constructor used to create a <strong id="b1725762542093534"><a name="b1725762542093534"></a><a name="b1725762542093534"></a><a href="OHOS-UIAbstractClock.md">UIAbstractClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row1650564464093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1263519093534"><a name="p1263519093534"></a><a name="p1263519093534"></a><a href="Graphic.md#ga93d3d68e48a79ee7fc4b42a9c0c0ccc1">UIAbstractClock</a> (uint8_t hour, uint8_t minute, uint8_t second)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646988191093534"><a name="p1646988191093534"></a><a name="p1646988191093534"></a>&nbsp;</p>
<p id="p169121908093534"><a name="p169121908093534"></a><a name="p169121908093534"></a>A constructor used to create a <strong id="b830404467093534"><a name="b830404467093534"></a><a name="b830404467093534"></a><a href="OHOS-UIAbstractClock.md">UIAbstractClock</a></strong> instance with time elements (hour, minute and second). </p>
</td>
</tr>
<tr id="row309376748093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1937273595093534"><a name="p1937273595093534"></a><a name="p1937273595093534"></a><a href="Graphic.md#ga0fb0c108b319f02b9d42b34c1d2c8708">~UIAbstractClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1003673543093534"><a name="p1003673543093534"></a><a name="p1003673543093534"></a>virtual&nbsp;</p>
<p id="p667782967093534"><a name="p667782967093534"></a><a name="p667782967093534"></a>A destructor used to delete the <strong id="b1458964501093534"><a name="b1458964501093534"></a><a name="b1458964501093534"></a><a href="OHOS-UIAbstractClock.md">UIAbstractClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row2097667015093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1245727419093534"><a name="p1245727419093534"></a><a name="p1245727419093534"></a><a href="Graphic.md#ga44a7312163a4192670c00bb8f9916e51">SetTime24Hour</a> (uint8_t hour, uint8_t minute, uint8_t second)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751409189093534"><a name="p751409189093534"></a><a name="p751409189093534"></a>void&nbsp;</p>
<p id="p816848935093534"><a name="p816848935093534"></a><a name="p816848935093534"></a>Sets the time in 24-hour format. </p>
</td>
</tr>
<tr id="row35806106093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1152367481093534"><a name="p1152367481093534"></a><a name="p1152367481093534"></a><a href="Graphic.md#ga37750dfa0b5a47c8dcb61547dd991a6a">SetTime12Hour</a> (uint8_t hour, uint8_t minute, uint8_t second, bool am)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1914849852093534"><a name="p1914849852093534"></a><a name="p1914849852093534"></a>void&nbsp;</p>
<p id="p1371715916093534"><a name="p1371715916093534"></a><a name="p1371715916093534"></a>Sets the time in 12-hour format. </p>
</td>
</tr>
<tr id="row121868225093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p894259631093534"><a name="p894259631093534"></a><a name="p894259631093534"></a><a href="Graphic.md#ga8cf863dfcd63410f2f20572a51f2516b">GetCurrentHour</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1443792187093534"><a name="p1443792187093534"></a><a name="p1443792187093534"></a>uint8_t&nbsp;</p>
<p id="p1244377251093534"><a name="p1244377251093534"></a><a name="p1244377251093534"></a>Obtains the current number of hours. </p>
</td>
</tr>
<tr id="row1163054850093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p29349569093534"><a name="p29349569093534"></a><a name="p29349569093534"></a><a href="Graphic.md#ga5f0eea09577104d9126a07bfbc0b780a">GetCurrentMinute</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2016928967093534"><a name="p2016928967093534"></a><a name="p2016928967093534"></a>uint8_t&nbsp;</p>
<p id="p1748609382093534"><a name="p1748609382093534"></a><a name="p1748609382093534"></a>Obtains the current number of minutes. </p>
</td>
</tr>
<tr id="row1160675226093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p285885089093534"><a name="p285885089093534"></a><a name="p285885089093534"></a><a href="Graphic.md#ga7bd4d2d4631d9ea373d008ec7a5d18ff">GetCurrentSecond</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p938194215093534"><a name="p938194215093534"></a><a name="p938194215093534"></a>uint8_t&nbsp;</p>
<p id="p1071349405093534"><a name="p1071349405093534"></a><a name="p1071349405093534"></a>Obtains the current number of seconds. </p>
</td>
</tr>
<tr id="row619472982093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1367044830093534"><a name="p1367044830093534"></a><a name="p1367044830093534"></a><a href="Graphic.md#gaf4c05e6acf6700d7edb69dc49cd6fef8">IncOneSecond</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1416427854093534"><a name="p1416427854093534"></a><a name="p1416427854093534"></a>void&nbsp;</p>
<p id="p662692656093534"><a name="p662692656093534"></a><a name="p662692656093534"></a>Increases the time by one second. </p>
</td>
</tr>
<tr id="row1256151378093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p441106365093534"><a name="p441106365093534"></a><a name="p441106365093534"></a><a href="Graphic.md#gaafa5df66c896268de27bf335c1b72b92">SetWorkMode</a> (<a href="Graphic.md#ga19db90932bc71e6bbced6ccf2935ac98">WorkMode</a> newMode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052977441093534"><a name="p1052977441093534"></a><a name="p1052977441093534"></a>virtual void&nbsp;</p>
<p id="p397935434093534"><a name="p397935434093534"></a><a name="p397935434093534"></a>Sets the working mode for this clock. </p>
</td>
</tr>
<tr id="row1009015515093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p202355909093534"><a name="p202355909093534"></a><a name="p202355909093534"></a><a href="Graphic.md#gad2d78422d212ef1e93bb4a23e1ee3859">GetWorkMode</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1586260088093534"><a name="p1586260088093534"></a><a name="p1586260088093534"></a>virtual <a href="Graphic.md#ga19db90932bc71e6bbced6ccf2935ac98">WorkMode</a>&nbsp;</p>
<p id="p2070900474093534"><a name="p2070900474093534"></a><a name="p2070900474093534"></a>Obtains the working mode of this clock. </p>
</td>
</tr>
<tr id="row833354947093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1979144749093534"><a name="p1979144749093534"></a><a name="p1979144749093534"></a><a href="Graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1680827503093534"><a name="p1680827503093534"></a><a name="p1680827503093534"></a>&nbsp;</p>
<p id="p1940337250093534"><a name="p1940337250093534"></a><a name="p1940337250093534"></a>A default constructor used to create a <strong id="b510658075093534"><a name="b510658075093534"></a><a name="b510658075093534"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1828179249093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1444950357093534"><a name="p1444950357093534"></a><a name="p1444950357093534"></a><a href="Graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28532926093534"><a name="p28532926093534"></a><a name="p28532926093534"></a>virtual&nbsp;</p>
<p id="p286810203093534"><a name="p286810203093534"></a><a name="p286810203093534"></a>A destructor used to delete the <strong id="b441594838093534"><a name="b441594838093534"></a><a name="b441594838093534"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row2092622438093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806128860093534"><a name="p1806128860093534"></a><a name="p1806128860093534"></a><a href="Graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p222699656093534"><a name="p222699656093534"></a><a name="p222699656093534"></a>UIViewType&nbsp;</p>
<p id="p1943741355093534"><a name="p1943741355093534"></a><a name="p1943741355093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1608169885093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1816924866093534"><a name="p1816924866093534"></a><a name="p1816924866093534"></a><a href="Graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1009369852093534"><a name="p1009369852093534"></a><a name="p1009369852093534"></a>virtual void&nbsp;</p>
<p id="p1480604474093534"><a name="p1480604474093534"></a><a name="p1480604474093534"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row663201791093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1093214820093534"><a name="p1093214820093534"></a><a name="p1093214820093534"></a><a href="Graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="OHOS-UIView.md">UIView</a> *prevView, <a href="OHOS-UIView.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1242438180093534"><a name="p1242438180093534"></a><a name="p1242438180093534"></a>virtual void&nbsp;</p>
<p id="p2044901182093534"><a name="p2044901182093534"></a><a name="p2044901182093534"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row113176535093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p947233926093534"><a name="p947233926093534"></a><a name="p947233926093534"></a><a href="Graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p928655149093534"><a name="p928655149093534"></a><a name="p928655149093534"></a>virtual void&nbsp;</p>
<p id="p1711717637093534"><a name="p1711717637093534"></a><a name="p1711717637093534"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row1932408575093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1697973679093534"><a name="p1697973679093534"></a><a name="p1697973679093534"></a><a href="Graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p790002063093534"><a name="p790002063093534"></a><a name="p790002063093534"></a>virtual void&nbsp;</p>
<p id="p203075702093534"><a name="p203075702093534"></a><a name="p203075702093534"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row808463921093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p129951970093534"><a name="p129951970093534"></a><a name="p129951970093534"></a><a href="Graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1199193963093534"><a name="p1199193963093534"></a><a name="p1199193963093534"></a>virtual void&nbsp;</p>
<p id="p1814183880093534"><a name="p1814183880093534"></a><a name="p1814183880093534"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row304424328093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1437698424093534"><a name="p1437698424093534"></a><a name="p1437698424093534"></a><a href="Graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p76209926093534"><a name="p76209926093534"></a><a name="p76209926093534"></a>virtual void&nbsp;</p>
<p id="p283763288093534"><a name="p283763288093534"></a><a name="p283763288093534"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row854472628093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1628911825093534"><a name="p1628911825093534"></a><a name="p1628911825093534"></a><a href="Graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1221311364093534"><a name="p1221311364093534"></a><a name="p1221311364093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p222537144093534"><a name="p222537144093534"></a><a name="p222537144093534"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1251373674093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1265483258093534"><a name="p1265483258093534"></a><a name="p1265483258093534"></a><a href="Graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p709000768093534"><a name="p709000768093534"></a><a name="p709000768093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p141575407093534"><a name="p141575407093534"></a><a name="p141575407093534"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row786328883093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1507916750093534"><a name="p1507916750093534"></a><a name="p1507916750093534"></a><a href="Graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1023455077093534"><a name="p1023455077093534"></a><a name="p1023455077093534"></a>void&nbsp;</p>
<p id="p259645994093534"><a name="p259645994093534"></a><a name="p259645994093534"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row911743618093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1440982013093534"><a name="p1440982013093534"></a><a name="p1440982013093534"></a><a href="Graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1404485800093534"><a name="p1404485800093534"></a><a name="p1404485800093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1592225211093534"><a name="p1592225211093534"></a><a name="p1592225211093534"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row2037920512093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p760780083093534"><a name="p760780083093534"></a><a name="p760780083093534"></a><a href="Graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p14541146093534"><a name="p14541146093534"></a><a name="p14541146093534"></a>void&nbsp;</p>
<p id="p795141828093534"><a name="p795141828093534"></a><a name="p795141828093534"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row1149385461093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p873593165093534"><a name="p873593165093534"></a><a name="p873593165093534"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1161964360093534"><a name="p1161964360093534"></a><a name="p1161964360093534"></a>&nbsp;</p>
<p id="p1948862391093534"><a name="p1948862391093534"></a><a name="p1948862391093534"></a>A default constructor used to create an <strong id="b2115680947093534"><a name="b2115680947093534"></a><a name="b2115680947093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1981636595093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p528161950093534"><a name="p528161950093534"></a><a name="p528161950093534"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p467112975093534"><a name="p467112975093534"></a><a name="p467112975093534"></a>&nbsp;</p>
<p id="p764514458093534"><a name="p764514458093534"></a><a name="p764514458093534"></a>A constructor used to create an <strong id="b1027537324093534"><a name="b1027537324093534"></a><a name="b1027537324093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1233072662093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244496818093534"><a name="p1244496818093534"></a><a name="p1244496818093534"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p80762451093534"><a name="p80762451093534"></a><a name="p80762451093534"></a>virtual&nbsp;</p>
<p id="p1780004902093534"><a name="p1780004902093534"></a><a name="p1780004902093534"></a>A destructor used to delete the <strong id="b1709493939093534"><a name="b1709493939093534"></a><a name="b1709493939093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row867461303093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778899363093534"><a name="p778899363093534"></a><a name="p778899363093534"></a><a href="Graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1875786892093534"><a name="p1875786892093534"></a><a name="p1875786892093534"></a>virtual bool&nbsp;</p>
<p id="p814930280093534"><a name="p814930280093534"></a><a name="p814930280093534"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row235503116093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149879033093534"><a name="p1149879033093534"></a><a name="p1149879033093534"></a><a href="Graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1707959186093534"><a name="p1707959186093534"></a><a name="p1707959186093534"></a>virtual void&nbsp;</p>
<p id="p711102694093534"><a name="p711102694093534"></a><a name="p711102694093534"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row97047246093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1116649091093534"><a name="p1116649091093534"></a><a name="p1116649091093534"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p117184519093534"><a name="p117184519093534"></a><a name="p117184519093534"></a>virtual void&nbsp;</p>
<p id="p1821765155093534"><a name="p1821765155093534"></a><a name="p1821765155093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row425326238093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p750511615093534"><a name="p750511615093534"></a><a name="p750511615093534"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p979449918093534"><a name="p979449918093534"></a><a name="p979449918093534"></a>virtual void&nbsp;</p>
<p id="p560054818093534"><a name="p560054818093534"></a><a name="p560054818093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row346605754093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p595616398093534"><a name="p595616398093534"></a><a name="p595616398093534"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p611670319093534"><a name="p611670319093534"></a><a name="p611670319093534"></a>void&nbsp;</p>
<p id="p1198990035093534"><a name="p1198990035093534"></a><a name="p1198990035093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row2128931849093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p678568452093534"><a name="p678568452093534"></a><a name="p678568452093534"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p993557843093534"><a name="p993557843093534"></a><a name="p993557843093534"></a>void&nbsp;</p>
<p id="p1645950232093534"><a name="p1645950232093534"></a><a name="p1645950232093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1863352302093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1240686749093534"><a name="p1240686749093534"></a><a name="p1240686749093534"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p902802323093534"><a name="p902802323093534"></a><a name="p902802323093534"></a>virtual bool&nbsp;</p>
<p id="p86481802093534"><a name="p86481802093534"></a><a name="p86481802093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1248546429093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1542650655093534"><a name="p1542650655093534"></a><a name="p1542650655093534"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1216229204093534"><a name="p1216229204093534"></a><a name="p1216229204093534"></a>virtual bool&nbsp;</p>
<p id="p794625500093534"><a name="p794625500093534"></a><a name="p794625500093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row679559351093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1939836915093534"><a name="p1939836915093534"></a><a name="p1939836915093534"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p348681879093534"><a name="p348681879093534"></a><a name="p348681879093534"></a>virtual bool&nbsp;</p>
<p id="p1491825076093534"><a name="p1491825076093534"></a><a name="p1491825076093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1904756679093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p442401567093534"><a name="p442401567093534"></a><a name="p442401567093534"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p815345771093534"><a name="p815345771093534"></a><a name="p815345771093534"></a>virtual bool&nbsp;</p>
<p id="p1893864114093534"><a name="p1893864114093534"></a><a name="p1893864114093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1417257316093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1034896108093534"><a name="p1034896108093534"></a><a name="p1034896108093534"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327062213093534"><a name="p327062213093534"></a><a name="p327062213093534"></a>virtual void&nbsp;</p>
<p id="p1076049603093534"><a name="p1076049603093534"></a><a name="p1076049603093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row341025725093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1497040667093534"><a name="p1497040667093534"></a><a name="p1497040667093534"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1693944777093534"><a name="p1693944777093534"></a><a name="p1693944777093534"></a>virtual void&nbsp;</p>
<p id="p862798483093534"><a name="p862798483093534"></a><a name="p862798483093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1806021368093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1382993085093534"><a name="p1382993085093534"></a><a name="p1382993085093534"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p556365786093534"><a name="p556365786093534"></a><a name="p556365786093534"></a>virtual void&nbsp;</p>
<p id="p509787566093534"><a name="p509787566093534"></a><a name="p509787566093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row920330941093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1127199444093534"><a name="p1127199444093534"></a><a name="p1127199444093534"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1100180273093534"><a name="p1100180273093534"></a><a name="p1100180273093534"></a>virtual void&nbsp;</p>
<p id="p2060731385093534"><a name="p2060731385093534"></a><a name="p2060731385093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row357605628093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p764334858093534"><a name="p764334858093534"></a><a name="p764334858093534"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p737023506093534"><a name="p737023506093534"></a><a name="p737023506093534"></a>void&nbsp;</p>
<p id="p756669551093534"><a name="p756669551093534"></a><a name="p756669551093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row442000148093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1081839479093534"><a name="p1081839479093534"></a><a name="p1081839479093534"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1237849054093534"><a name="p1237849054093534"></a><a name="p1237849054093534"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p1676146101093534"><a name="p1676146101093534"></a><a name="p1676146101093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row387017896093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2083943001093534"><a name="p2083943001093534"></a><a name="p2083943001093534"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p447367017093534"><a name="p447367017093534"></a><a name="p447367017093534"></a>void&nbsp;</p>
<p id="p587964125093534"><a name="p587964125093534"></a><a name="p587964125093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1965554640093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969627281093534"><a name="p1969627281093534"></a><a name="p1969627281093534"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p374440630093534"><a name="p374440630093534"></a><a name="p374440630093534"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p2036629165093534"><a name="p2036629165093534"></a><a name="p2036629165093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row274284398093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1707257916093534"><a name="p1707257916093534"></a><a name="p1707257916093534"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1061290675093534"><a name="p1061290675093534"></a><a name="p1061290675093534"></a>void&nbsp;</p>
<p id="p647693236093534"><a name="p647693236093534"></a><a name="p647693236093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row531411969093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p543358207093534"><a name="p543358207093534"></a><a name="p543358207093534"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p541343749093534"><a name="p541343749093534"></a><a name="p541343749093534"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p787848809093534"><a name="p787848809093534"></a><a name="p787848809093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row494511830093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1673726692093534"><a name="p1673726692093534"></a><a name="p1673726692093534"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1871816810093534"><a name="p1871816810093534"></a><a name="p1871816810093534"></a>void&nbsp;</p>
<p id="p1809747776093534"><a name="p1809747776093534"></a><a name="p1809747776093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row265438066093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p420043012093534"><a name="p420043012093534"></a><a name="p420043012093534"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1734191973093534"><a name="p1734191973093534"></a><a name="p1734191973093534"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p252273042093534"><a name="p252273042093534"></a><a name="p252273042093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1627608519093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p659716966093534"><a name="p659716966093534"></a><a name="p659716966093534"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181321195093534"><a name="p181321195093534"></a><a name="p181321195093534"></a>void&nbsp;</p>
<p id="p106567851093534"><a name="p106567851093534"></a><a name="p106567851093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row660814075093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242127552093534"><a name="p1242127552093534"></a><a name="p1242127552093534"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1135649138093534"><a name="p1135649138093534"></a><a name="p1135649138093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p211284619093534"><a name="p211284619093534"></a><a name="p211284619093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1512816038093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1894000884093534"><a name="p1894000884093534"></a><a name="p1894000884093534"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p171256123093534"><a name="p171256123093534"></a><a name="p171256123093534"></a>void&nbsp;</p>
<p id="p1058991717093534"><a name="p1058991717093534"></a><a name="p1058991717093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1280196833093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1804897253093534"><a name="p1804897253093534"></a><a name="p1804897253093534"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327095676093534"><a name="p1327095676093534"></a><a name="p1327095676093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p982185489093534"><a name="p982185489093534"></a><a name="p982185489093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1921854888093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1830829043093534"><a name="p1830829043093534"></a><a name="p1830829043093534"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181617196093534"><a name="p181617196093534"></a><a name="p181617196093534"></a>virtual void&nbsp;</p>
<p id="p908292474093534"><a name="p908292474093534"></a><a name="p908292474093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row704111199093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2067257706093534"><a name="p2067257706093534"></a><a name="p2067257706093534"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1424504223093534"><a name="p1424504223093534"></a><a name="p1424504223093534"></a>bool&nbsp;</p>
<p id="p409279605093534"><a name="p409279605093534"></a><a name="p409279605093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1809636885093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1679022143093534"><a name="p1679022143093534"></a><a name="p1679022143093534"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2147080362093534"><a name="p2147080362093534"></a><a name="p2147080362093534"></a>void&nbsp;</p>
<p id="p1828252512093534"><a name="p1828252512093534"></a><a name="p1828252512093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1997633275093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1566810414093534"><a name="p1566810414093534"></a><a name="p1566810414093534"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1860937751093534"><a name="p1860937751093534"></a><a name="p1860937751093534"></a>bool&nbsp;</p>
<p id="p214905977093534"><a name="p214905977093534"></a><a name="p214905977093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1646259156093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p687171712093534"><a name="p687171712093534"></a><a name="p687171712093534"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466489270093534"><a name="p1466489270093534"></a><a name="p1466489270093534"></a>void&nbsp;</p>
<p id="p864638024093534"><a name="p864638024093534"></a><a name="p864638024093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row518324886093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p300531072093534"><a name="p300531072093534"></a><a name="p300531072093534"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021609178093534"><a name="p2021609178093534"></a><a name="p2021609178093534"></a>bool&nbsp;</p>
<p id="p1082420402093534"><a name="p1082420402093534"></a><a name="p1082420402093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1375335851093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1042196572093534"><a name="p1042196572093534"></a><a name="p1042196572093534"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p788463415093534"><a name="p788463415093534"></a><a name="p788463415093534"></a>void&nbsp;</p>
<p id="p470148090093534"><a name="p470148090093534"></a><a name="p470148090093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1888709436093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p286156831093534"><a name="p286156831093534"></a><a name="p286156831093534"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p325048948093534"><a name="p325048948093534"></a><a name="p325048948093534"></a>bool&nbsp;</p>
<p id="p293777949093534"><a name="p293777949093534"></a><a name="p293777949093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1223524966093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2059937771093534"><a name="p2059937771093534"></a><a name="p2059937771093534"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p848037919093534"><a name="p848037919093534"></a><a name="p848037919093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1441282636093534"><a name="p1441282636093534"></a><a name="p1441282636093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row835149113093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p312115554093534"><a name="p312115554093534"></a><a name="p312115554093534"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p117024942093534"><a name="p117024942093534"></a><a name="p117024942093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p561685997093534"><a name="p561685997093534"></a><a name="p561685997093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1682160443093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p336417872093534"><a name="p336417872093534"></a><a name="p336417872093534"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p648541589093534"><a name="p648541589093534"></a><a name="p648541589093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p69572801093534"><a name="p69572801093534"></a><a name="p69572801093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row965910313093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p849352605093534"><a name="p849352605093534"></a><a name="p849352605093534"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1255932233093534"><a name="p1255932233093534"></a><a name="p1255932233093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p673542435093534"><a name="p673542435093534"></a><a name="p673542435093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row2054945510093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p875766470093534"><a name="p875766470093534"></a><a name="p875766470093534"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p573412588093534"><a name="p573412588093534"></a><a name="p573412588093534"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p2018913350093534"><a name="p2018913350093534"></a><a name="p2018913350093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1274381298093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p819683952093534"><a name="p819683952093534"></a><a name="p819683952093534"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p866524247093534"><a name="p866524247093534"></a><a name="p866524247093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p337741365093534"><a name="p337741365093534"></a><a name="p337741365093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row576780515093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p504082794093534"><a name="p504082794093534"></a><a name="p504082794093534"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p636671549093534"><a name="p636671549093534"></a><a name="p636671549093534"></a>void&nbsp;</p>
<p id="p471294597093534"><a name="p471294597093534"></a><a name="p471294597093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1884013311093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408701533093534"><a name="p1408701533093534"></a><a name="p1408701533093534"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550151560093534"><a name="p1550151560093534"></a><a name="p1550151560093534"></a>virtual void&nbsp;</p>
<p id="p405269790093534"><a name="p405269790093534"></a><a name="p405269790093534"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row842859707093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1418021724093534"><a name="p1418021724093534"></a><a name="p1418021724093534"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1169250164093534"><a name="p1169250164093534"></a><a name="p1169250164093534"></a>virtual int16_t&nbsp;</p>
<p id="p550779303093534"><a name="p550779303093534"></a><a name="p550779303093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1093227344093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p148516755093534"><a name="p148516755093534"></a><a name="p148516755093534"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1632310273093534"><a name="p1632310273093534"></a><a name="p1632310273093534"></a>virtual void&nbsp;</p>
<p id="p753029626093534"><a name="p753029626093534"></a><a name="p753029626093534"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row2037025455093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1536530547093534"><a name="p1536530547093534"></a><a name="p1536530547093534"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p385609635093534"><a name="p385609635093534"></a><a name="p385609635093534"></a>virtual int16_t&nbsp;</p>
<p id="p1811430220093534"><a name="p1811430220093534"></a><a name="p1811430220093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1534977254093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1869775824093534"><a name="p1869775824093534"></a><a name="p1869775824093534"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p344031624093534"><a name="p344031624093534"></a><a name="p344031624093534"></a>virtual void&nbsp;</p>
<p id="p1546777977093534"><a name="p1546777977093534"></a><a name="p1546777977093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row750708644093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1667278941093534"><a name="p1667278941093534"></a><a name="p1667278941093534"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p151952769093534"><a name="p151952769093534"></a><a name="p151952769093534"></a>virtual void&nbsp;</p>
<p id="p1035285273093534"><a name="p1035285273093534"></a><a name="p1035285273093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1845712828093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p180540054093534"><a name="p180540054093534"></a><a name="p180540054093534"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2142429376093534"><a name="p2142429376093534"></a><a name="p2142429376093534"></a>int16_t&nbsp;</p>
<p id="p1035435720093534"><a name="p1035435720093534"></a><a name="p1035435720093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1473382660093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p124553740093534"><a name="p124553740093534"></a><a name="p124553740093534"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p869802633093534"><a name="p869802633093534"></a><a name="p869802633093534"></a>virtual void&nbsp;</p>
<p id="p902437485093534"><a name="p902437485093534"></a><a name="p902437485093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1973221151093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p763551563093534"><a name="p763551563093534"></a><a name="p763551563093534"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2139363005093534"><a name="p2139363005093534"></a><a name="p2139363005093534"></a>int16_t&nbsp;</p>
<p id="p158895820093534"><a name="p158895820093534"></a><a name="p158895820093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1962201525093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p309211733093534"><a name="p309211733093534"></a><a name="p309211733093534"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p440287835093534"><a name="p440287835093534"></a><a name="p440287835093534"></a>virtual void&nbsp;</p>
<p id="p782729160093534"><a name="p782729160093534"></a><a name="p782729160093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row319181667093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p773973074093534"><a name="p773973074093534"></a><a name="p773973074093534"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p494743919093534"><a name="p494743919093534"></a><a name="p494743919093534"></a>virtual void&nbsp;</p>
<p id="p1858698744093534"><a name="p1858698744093534"></a><a name="p1858698744093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row340023385093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1015422026093534"><a name="p1015422026093534"></a><a name="p1015422026093534"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1777297122093534"><a name="p1777297122093534"></a><a name="p1777297122093534"></a>bool&nbsp;</p>
<p id="p1457446091093534"><a name="p1457446091093534"></a><a name="p1457446091093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row228187959093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p218527712093534"><a name="p218527712093534"></a><a name="p218527712093534"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p980004948093534"><a name="p980004948093534"></a><a name="p980004948093534"></a>void&nbsp;</p>
<p id="p1273162333093534"><a name="p1273162333093534"></a><a name="p1273162333093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row65535660093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1643925742093534"><a name="p1643925742093534"></a><a name="p1643925742093534"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p711410245093534"><a name="p711410245093534"></a><a name="p711410245093534"></a>void&nbsp;</p>
<p id="p1845078170093534"><a name="p1845078170093534"></a><a name="p1845078170093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row457221353093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228196936093534"><a name="p228196936093534"></a><a name="p228196936093534"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p909034419093534"><a name="p909034419093534"></a><a name="p909034419093534"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p1411645084093534"><a name="p1411645084093534"></a><a name="p1411645084093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row253156567093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p784418614093534"><a name="p784418614093534"></a><a name="p784418614093534"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2028509324093534"><a name="p2028509324093534"></a><a name="p2028509324093534"></a>void&nbsp;</p>
<p id="p1419365996093534"><a name="p1419365996093534"></a><a name="p1419365996093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row105059556093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p912826633093534"><a name="p912826633093534"></a><a name="p912826633093534"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p208170992093534"><a name="p208170992093534"></a><a name="p208170992093534"></a>const char *&nbsp;</p>
<p id="p1780776126093534"><a name="p1780776126093534"></a><a name="p1780776126093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row2081636510093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p274031620093534"><a name="p274031620093534"></a><a name="p274031620093534"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p842929358093534"><a name="p842929358093534"></a><a name="p842929358093534"></a>void&nbsp;</p>
<p id="p1400663861093534"><a name="p1400663861093534"></a><a name="p1400663861093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row778322612093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p155424367093534"><a name="p155424367093534"></a><a name="p155424367093534"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1423904762093534"><a name="p1423904762093534"></a><a name="p1423904762093534"></a>int16_t&nbsp;</p>
<p id="p1512735032093534"><a name="p1512735032093534"></a><a name="p1512735032093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1939883372093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p627301998093534"><a name="p627301998093534"></a><a name="p627301998093534"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1897989302093534"><a name="p1897989302093534"></a><a name="p1897989302093534"></a>virtual void&nbsp;</p>
<p id="p1911662196093534"><a name="p1911662196093534"></a><a name="p1911662196093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row808928402093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1813443688093534"><a name="p1813443688093534"></a><a name="p1813443688093534"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2076769962093534"><a name="p2076769962093534"></a><a name="p2076769962093534"></a>void&nbsp;</p>
<p id="p1708234017093534"><a name="p1708234017093534"></a><a name="p1708234017093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row558343477093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1479744787093534"><a name="p1479744787093534"></a><a name="p1479744787093534"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389240471093534"><a name="p1389240471093534"></a><a name="p1389240471093534"></a>void&nbsp;</p>
<p id="p1945548361093534"><a name="p1945548361093534"></a><a name="p1945548361093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row950986276093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p525280517093534"><a name="p525280517093534"></a><a name="p525280517093534"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1060583395093534"><a name="p1060583395093534"></a><a name="p1060583395093534"></a>void&nbsp;</p>
<p id="p1869049431093534"><a name="p1869049431093534"></a><a name="p1869049431093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row50534305093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p722410166093534"><a name="p722410166093534"></a><a name="p722410166093534"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p601494739093534"><a name="p601494739093534"></a><a name="p601494739093534"></a>void&nbsp;</p>
<p id="p537100553093534"><a name="p537100553093534"></a><a name="p537100553093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1596166483093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p936128881093534"><a name="p936128881093534"></a><a name="p936128881093534"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p494652826093534"><a name="p494652826093534"></a><a name="p494652826093534"></a>void&nbsp;</p>
<p id="p43830148093534"><a name="p43830148093534"></a><a name="p43830148093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row894088825093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p72763090093534"><a name="p72763090093534"></a><a name="p72763090093534"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1963792107093534"><a name="p1963792107093534"></a><a name="p1963792107093534"></a>void&nbsp;</p>
<p id="p1648581296093534"><a name="p1648581296093534"></a><a name="p1648581296093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row281356119093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2040638272093534"><a name="p2040638272093534"></a><a name="p2040638272093534"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1623531456093534"><a name="p1623531456093534"></a><a name="p1623531456093534"></a>void&nbsp;</p>
<p id="p1457944266093534"><a name="p1457944266093534"></a><a name="p1457944266093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row502432659093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p868366217093534"><a name="p868366217093534"></a><a name="p868366217093534"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1671703091093534"><a name="p1671703091093534"></a><a name="p1671703091093534"></a>void&nbsp;</p>
<p id="p1049935115093534"><a name="p1049935115093534"></a><a name="p1049935115093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row448224231093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1650312869093534"><a name="p1650312869093534"></a><a name="p1650312869093534"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1967354424093534"><a name="p1967354424093534"></a><a name="p1967354424093534"></a>void&nbsp;</p>
<p id="p1254014769093534"><a name="p1254014769093534"></a><a name="p1254014769093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row456999005093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p171913729093534"><a name="p171913729093534"></a><a name="p171913729093534"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p129658080093534"><a name="p129658080093534"></a><a name="p129658080093534"></a>void&nbsp;</p>
<p id="p1715586956093534"><a name="p1715586956093534"></a><a name="p1715586956093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1026491169093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1258790085093534"><a name="p1258790085093534"></a><a name="p1258790085093534"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p168739145093534"><a name="p168739145093534"></a><a name="p168739145093534"></a>void&nbsp;</p>
<p id="p46577494093534"><a name="p46577494093534"></a><a name="p46577494093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1902201781093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p452726873093534"><a name="p452726873093534"></a><a name="p452726873093534"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1427179684093534"><a name="p1427179684093534"></a><a name="p1427179684093534"></a>void&nbsp;</p>
<p id="p1706431512093534"><a name="p1706431512093534"></a><a name="p1706431512093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row167558066093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617579231093534"><a name="p617579231093534"></a><a name="p617579231093534"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1233903826093534"><a name="p1233903826093534"></a><a name="p1233903826093534"></a>void&nbsp;</p>
<p id="p791576671093534"><a name="p791576671093534"></a><a name="p791576671093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1052747911093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2065248404093534"><a name="p2065248404093534"></a><a name="p2065248404093534"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343687613093534"><a name="p343687613093534"></a><a name="p343687613093534"></a>void&nbsp;</p>
<p id="p71241529093534"><a name="p71241529093534"></a><a name="p71241529093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1877170479093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p20551648093534"><a name="p20551648093534"></a><a name="p20551648093534"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1598738725093534"><a name="p1598738725093534"></a><a name="p1598738725093534"></a>void&nbsp;</p>
<p id="p1672393119093534"><a name="p1672393119093534"></a><a name="p1672393119093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1892301694093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1155041048093534"><a name="p1155041048093534"></a><a name="p1155041048093534"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p437698633093534"><a name="p437698633093534"></a><a name="p437698633093534"></a>virtual void&nbsp;</p>
<p id="p280590116093534"><a name="p280590116093534"></a><a name="p280590116093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row75774203093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p917586560093534"><a name="p917586560093534"></a><a name="p917586560093534"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1771904872093534"><a name="p1771904872093534"></a><a name="p1771904872093534"></a>virtual void&nbsp;</p>
<p id="p2059441677093534"><a name="p2059441677093534"></a><a name="p2059441677093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1038529760093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1014605853093534"><a name="p1014605853093534"></a><a name="p1014605853093534"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1414888145093534"><a name="p1414888145093534"></a><a name="p1414888145093534"></a>virtual int64_t&nbsp;</p>
<p id="p1719598330093534"><a name="p1719598330093534"></a><a name="p1719598330093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row83486970093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p249697871093534"><a name="p249697871093534"></a><a name="p249697871093534"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p883241321093534"><a name="p883241321093534"></a><a name="p883241321093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1247833380093534"><a name="p1247833380093534"></a><a name="p1247833380093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row62140798093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1340274134093534"><a name="p1340274134093534"></a><a name="p1340274134093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2115897083093534"><a name="p2115897083093534"></a><a name="p2115897083093534"></a>void *&nbsp;</p>
<p id="p999928711093534"><a name="p999928711093534"></a><a name="p999928711093534"></a>Overrides the <strong id="b210895943093534"><a name="b210895943093534"></a><a name="b210895943093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row2134241133093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2135224715093534"><a name="p2135224715093534"></a><a name="p2135224715093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p65033487093534"><a name="p65033487093534"></a><a name="p65033487093534"></a>void&nbsp;</p>
<p id="p535034521093534"><a name="p535034521093534"></a><a name="p535034521093534"></a>Overrides the <strong id="b1434987450093534"><a name="b1434987450093534"></a><a name="b1434987450093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table666333531093534"></a>
<table><thead align="left"><tr id="row1784475775093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1991726241093534"><a name="p1991726241093534"></a><a name="p1991726241093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1366580768093534"><a name="p1366580768093534"></a><a name="p1366580768093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row114244215093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p948502550093534"><a name="p948502550093534"></a><a name="p948502550093534"></a><a href="Graphic.md#ga7f433b8551722451f880e7fa05731a2f">ONE_MINUTE_IN_SECOND</a> = 60</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1751108324093534"><a name="p1751108324093534"></a><a name="p1751108324093534"></a>Represents 60 seconds per minute. </p>
</td>
</tr>
<tr id="row942952279093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p95258686093534"><a name="p95258686093534"></a><a name="p95258686093534"></a><a href="Graphic.md#ga5434b911b6f7e0637ac0626c9dd0f513">ONE_HOUR_IN_MINUTE</a> = 60</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1625981771093534"><a name="p1625981771093534"></a><a name="p1625981771093534"></a>Represents 60 minutes per hour. </p>
</td>
</tr>
<tr id="row554948073093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p650757057093534"><a name="p650757057093534"></a><a name="p650757057093534"></a><a href="Graphic.md#gae7742f1e715885ecc4f5b67d57530319">ONE_DAY_IN_HOUR</a> = 24</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p841784230093534"><a name="p841784230093534"></a><a name="p841784230093534"></a>Represents 24 hours per day. </p>
</td>
</tr>
<tr id="row1257548927093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1248571939093534"><a name="p1248571939093534"></a><a name="p1248571939093534"></a><a href="Graphic.md#gae40a5ae3834b626e2976fab83f166171">HALF_DAY_IN_HOUR</a> = 12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1150878449093534"><a name="p1150878449093534"></a><a name="p1150878449093534"></a>Represents 12 hours every half day. </p>
</td>
</tr>
<tr id="row1768897344093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p382546064093534"><a name="p382546064093534"></a><a name="p382546064093534"></a><a href="Graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1030843704093534"><a name="p1030843704093534"></a><a name="p1030843704093534"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1423124629093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p676651313093534"><a name="p676651313093534"></a><a name="p676651313093534"></a><a href="Graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1557307759093534"><a name="p1557307759093534"></a><a name="p1557307759093534"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row2054730578093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2142223717093534"><a name="p2142223717093534"></a><a name="p2142223717093534"></a><a href="Graphic.md#gaabfbbb277dabf5477c628336a429f8ad">currentHour_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2122488727093534"><a name="p2122488727093534"></a><a name="p2122488727093534"></a>Represents the current number of hours. </p>
</td>
</tr>
<tr id="row789424501093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453773765093534"><a name="p453773765093534"></a><a name="p453773765093534"></a><a href="Graphic.md#ga34c3518c0dc9f35fc77b240b6f8d0dcb">currentMinute_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311172541093534"><a name="p311172541093534"></a><a name="p311172541093534"></a>Represents the current number of minutes. </p>
</td>
</tr>
<tr id="row1917468115093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1110774834093534"><a name="p1110774834093534"></a><a name="p1110774834093534"></a><a href="Graphic.md#ga5b2749cdc5e52551731923d8268b8d5d">currentSecond_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2044286587093534"><a name="p2044286587093534"></a><a name="p2044286587093534"></a>Represents the current number of seconds. </p>
</td>
</tr>
<tr id="row1652195007093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2022216010093534"><a name="p2022216010093534"></a><a name="p2022216010093534"></a><a href="Graphic.md#gab08c7c490a5b42fcdee04d45b5521d1c">mode_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1992805602093534"><a name="p1992805602093534"></a><a name="p1992805602093534"></a>Represents the current working mode of this clock. </p>
</td>
</tr>
<tr id="row927621584093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2104030135093534"><a name="p2104030135093534"></a><a name="p2104030135093534"></a><a href="Graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p678611920093534"><a name="p678611920093534"></a><a name="p678611920093534"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row1230851455093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p238066831093534"><a name="p238066831093534"></a><a name="p238066831093534"></a><a href="Graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p512202986093534"><a name="p512202986093534"></a><a name="p512202986093534"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row286519752093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1788973344093534"><a name="p1788973344093534"></a><a name="p1788973344093534"></a><a href="Graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p339062730093534"><a name="p339062730093534"></a><a name="p339062730093534"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row67007634093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p278681593093534"><a name="p278681593093534"></a><a name="p278681593093534"></a><a href="Graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653826365093534"><a name="p1653826365093534"></a><a name="p1653826365093534"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1204940264093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p948699421093534"><a name="p948699421093534"></a><a name="p948699421093534"></a><a href="Graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1545331606093534"><a name="p1545331606093534"></a><a name="p1545331606093534"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row612000460093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p536240044093534"><a name="p536240044093534"></a><a name="p536240044093534"></a><a href="Graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p884015182093534"><a name="p884015182093534"></a><a name="p884015182093534"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

