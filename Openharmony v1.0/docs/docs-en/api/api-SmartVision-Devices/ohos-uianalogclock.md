# OHOS::UIAnalogClock<a name="EN-US_TOPIC_0000001054718147"></a>

## **Overview**<a name="section1105961093093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Provides the functions related to an analog clock. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section396648721093533"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table490734803093533"></a>
<table><thead align="left"><tr id="row1706598559093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p759934985093533"><a name="p759934985093533"></a><a name="p759934985093533"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p354349341093533"><a name="p354349341093533"></a><a name="p354349341093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row585647340093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p200296529093533"><a name="p200296529093533"></a><a name="p200296529093533"></a><a href="ohos-uianalogclock-hand.md">Hand</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p114086620093533"><a name="p114086620093533"></a><a name="p114086620093533"></a>Defines the basic attributes of the analog clock hands. This is an inner class of <strong id="b426460776093533"><a name="b426460776093533"></a><a name="b426460776093533"></a><a href="ohos-uiabstractclock.md">UIAbstractClock</a></strong>. </p>
</td>
</tr>
</tbody>
</table>

## Public Types<a name="pub-types"></a>

<a name="table1204376653093533"></a>
<table><thead align="left"><tr id="row669505518093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p247897643093533"><a name="p247897643093533"></a><a name="p247897643093533"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p603197502093533"><a name="p603197502093533"></a><a name="p603197502093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row259448320093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1510113920093533"><a name="p1510113920093533"></a><a name="p1510113920093533"></a><a href="graphic.md#ga13cf64ea5bd39550976aaf65b1381edf">HandType</a> { <a href="graphic.md#gga13cf64ea5bd39550976aaf65b1381edfa2b8ab55559dff5a849bf7445f6865958">HandType::HOUR_HAND</a>, <a href="graphic.md#gga13cf64ea5bd39550976aaf65b1381edfa50ddc7aea61ec54878c173e1423af447">HandType::MINUTE_HAND</a>, <a href="graphic.md#gga13cf64ea5bd39550976aaf65b1381edfa620c615d18fdb1b23ed04df57842909d">HandType::SECOND_HAND</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213392937093533"><a name="p213392937093533"></a><a name="p213392937093533"></a>Enumerates the clock hand types. </p>
</td>
</tr>
<tr id="row1447917484093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1693846883093533"><a name="p1693846883093533"></a><a name="p1693846883093533"></a><a href="graphic.md#ga0a595eeb50ce4e7dfff9ede16098d2db">DrawType</a> { <a href="graphic.md#gga0a595eeb50ce4e7dfff9ede16098d2dba6ddf16010fbdac5db23575583cb8a388">DrawType::DRAW_LINE</a>, <a href="graphic.md#gga0a595eeb50ce4e7dfff9ede16098d2dba5cb6a362b1dec2b19422e9e9a6bbda3c">DrawType::DRAW_IMAGE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1871495807093533"><a name="p1871495807093533"></a><a name="p1871495807093533"></a>Enumerates the drawing types of a clock hand. </p>
</td>
</tr>
<tr id="row1417492683093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p289659884093533"><a name="p289659884093533"></a><a name="p289659884093533"></a><a href="graphic.md#ga19db90932bc71e6bbced6ccf2935ac98">WorkMode</a> { <a href="graphic.md#gga19db90932bc71e6bbced6ccf2935ac98a2025ac1a1f63409f0b37f444547ec859">ALWAYS_ON</a>, <a href="graphic.md#gga19db90932bc71e6bbced6ccf2935ac98a8d32f103a422c6675618f5e9773b2eaa">NORMAL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748530872093533"><a name="p748530872093533"></a><a name="p748530872093533"></a>Enumerates the working modes of this clock. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1194379409093533"></a>
<table><thead align="left"><tr id="row155691282093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2042824954093533"><a name="p2042824954093533"></a><a name="p2042824954093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1284573401093533"><a name="p1284573401093533"></a><a name="p1284573401093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1088156173093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p198768618093533"><a name="p198768618093533"></a><a name="p198768618093533"></a><a href="graphic.md#ga2e986cb53c62dd015edced59450b9fff">UIAnalogClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1196590316093533"><a name="p1196590316093533"></a><a name="p1196590316093533"></a> </p>
<p id="p421389879093533"><a name="p421389879093533"></a><a name="p421389879093533"></a>A default constructor used to create a <strong id="b695601675093533"><a name="b695601675093533"></a><a name="b695601675093533"></a><a href="ohos-uianalogclock.md">UIAnalogClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row1667001223093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1178783523093533"><a name="p1178783523093533"></a><a name="p1178783523093533"></a><a href="graphic.md#ga4b06e05f003e25206d5fa772b303dcc5">~UIAnalogClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1460031955093533"><a name="p1460031955093533"></a><a name="p1460031955093533"></a>virtual </p>
<p id="p1981053369093533"><a name="p1981053369093533"></a><a name="p1981053369093533"></a>A destructor used to delete the <strong id="b639098287093533"><a name="b639098287093533"></a><a name="b639098287093533"></a><a href="ohos-uianalogclock.md">UIAnalogClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row256952649093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973020530093533"><a name="p973020530093533"></a><a name="p973020530093533"></a><a href="graphic.md#ga2f5123df8cbcc4f55c5192acbe30ba0d">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p431132862093533"><a name="p431132862093533"></a><a name="p431132862093533"></a>UIViewType </p>
<p id="p2072671277093533"><a name="p2072671277093533"></a><a name="p2072671277093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row186667759093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1571577767093533"><a name="p1571577767093533"></a><a name="p1571577767093533"></a><a href="graphic.md#ga18816e5dae6a7b79cbc408b1bc70c584">SetHandImage</a> (<a href="graphic.md#ga13cf64ea5bd39550976aaf65b1381edf">HandType</a> type, const <a href="ohos-uiimageview.md">UIImageView</a> &amp;img, <a href="ohos-point.md">Point</a> position, <a href="ohos-point.md">Point</a> center)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p726072478093533"><a name="p726072478093533"></a><a name="p726072478093533"></a>void </p>
<p id="p4136234093533"><a name="p4136234093533"></a><a name="p4136234093533"></a>Sets the image used to draw a clock hand. </p>
</td>
</tr>
<tr id="row68344667093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1971904584093533"><a name="p1971904584093533"></a><a name="p1971904584093533"></a><a href="graphic.md#ga271358e8076b55ed48de19350b3e55de">SetHandLine</a> (<a href="graphic.md#ga13cf64ea5bd39550976aaf65b1381edf">HandType</a> type, <a href="ohos-point.md">Point</a> position, <a href="ohos-point.md">Point</a> center, <a href="ohos-color32.md">ColorType</a> color, uint16_t width, uint16_t height, OpacityType opacity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1423608141093533"><a name="p1423608141093533"></a><a name="p1423608141093533"></a>void </p>
<p id="p80822325093533"><a name="p80822325093533"></a><a name="p80822325093533"></a>Sets the line used to draw a clock hand. </p>
</td>
</tr>
<tr id="row77149557093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p241479322093533"><a name="p241479322093533"></a><a name="p241479322093533"></a><a href="graphic.md#ga4943396addd8f88fb131aa03319e3d8a">GetHandRotateCenter</a> (<a href="graphic.md#ga13cf64ea5bd39550976aaf65b1381edf">HandType</a> type) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p848042605093533"><a name="p848042605093533"></a><a name="p848042605093533"></a><a href="ohos-point.md">Point</a> </p>
<p id="p1178244050093533"><a name="p1178244050093533"></a><a name="p1178244050093533"></a>Obtains the rotation center of a specified clock hand. </p>
</td>
</tr>
<tr id="row1020309344093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p119188513093533"><a name="p119188513093533"></a><a name="p119188513093533"></a><a href="graphic.md#ga56b260401694fce13dc5f744cb8bf471">GetHandPosition</a> (<a href="graphic.md#ga13cf64ea5bd39550976aaf65b1381edf">HandType</a> type) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1551871614093533"><a name="p1551871614093533"></a><a name="p1551871614093533"></a><a href="ohos-point.md">Point</a> </p>
<p id="p1406297868093533"><a name="p1406297868093533"></a><a name="p1406297868093533"></a>Obtains the position of a specified clock hand. </p>
</td>
</tr>
<tr id="row763491792093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1711574782093533"><a name="p1711574782093533"></a><a name="p1711574782093533"></a><a href="graphic.md#ga3fdfc7872768c5f5cea6627958f53ff8">GetHandInitAngle</a> (<a href="graphic.md#ga13cf64ea5bd39550976aaf65b1381edf">HandType</a> type) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1214824779093533"><a name="p1214824779093533"></a><a name="p1214824779093533"></a>uint16_t </p>
<p id="p609429450093533"><a name="p609429450093533"></a><a name="p609429450093533"></a>Obtains the initial rotation angle of the specified clock hand. </p>
</td>
</tr>
<tr id="row1652292617093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p23757429093533"><a name="p23757429093533"></a><a name="p23757429093533"></a><a href="graphic.md#ga4092ecd3068a58937b750d308e8eca5f">GetHandCurrentAngle</a> (<a href="graphic.md#ga13cf64ea5bd39550976aaf65b1381edf">HandType</a> type) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1859783588093533"><a name="p1859783588093533"></a><a name="p1859783588093533"></a>uint16_t </p>
<p id="p473250024093533"><a name="p473250024093533"></a><a name="p473250024093533"></a>Obtains the current rotation angle of the specified clock hand. </p>
</td>
</tr>
<tr id="row1562766686093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1561481732093533"><a name="p1561481732093533"></a><a name="p1561481732093533"></a><a href="graphic.md#ga3099f37f0ff8cd1229c0734098649173">SetInitTime24Hour</a> (uint8_t hour, uint8_t minute, uint8_t second)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1823141277093533"><a name="p1823141277093533"></a><a name="p1823141277093533"></a>void </p>
<p id="p1348651737093533"><a name="p1348651737093533"></a><a name="p1348651737093533"></a>Sets the initial time in the 24-hour format. </p>
</td>
</tr>
<tr id="row607983057093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864150881093533"><a name="p1864150881093533"></a><a name="p1864150881093533"></a><a href="graphic.md#gaa118c65942244bb0948b626944c0eaf9">SetInitTime12Hour</a> (uint8_t hour, uint8_t minute, uint8_t second, bool am)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1598321549093533"><a name="p1598321549093533"></a><a name="p1598321549093533"></a>void </p>
<p id="p993849005093533"><a name="p993849005093533"></a><a name="p993849005093533"></a>Sets the initial time in the 12-hour format. </p>
</td>
</tr>
<tr id="row1101986474093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1434648516093533"><a name="p1434648516093533"></a><a name="p1434648516093533"></a><a href="graphic.md#ga6c943119bd89a863ec5f05722a1fd146">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1109880960093533"><a name="p1109880960093533"></a><a name="p1109880960093533"></a>void </p>
<p id="p1801465419093533"><a name="p1801465419093533"></a><a name="p1801465419093533"></a>Draws an analog clock. </p>
</td>
</tr>
<tr id="row937725247093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1463345264093533"><a name="p1463345264093533"></a><a name="p1463345264093533"></a><a href="graphic.md#ga1366a4ca45babb67f3103279a2bbc0bf">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1286382994093533"><a name="p1286382994093533"></a><a name="p1286382994093533"></a>virtual void </p>
<p id="p1310536353093533"><a name="p1310536353093533"></a><a name="p1310536353093533"></a>Performs the operations needed after the drawing. </p>
</td>
</tr>
<tr id="row188051489093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p574131005093533"><a name="p574131005093533"></a><a name="p574131005093533"></a><a href="graphic.md#ga01d3098090d17bdd720df6e861784e13">SetPosition</a> (int16_t x, int16_t y) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p164097164093533"><a name="p164097164093533"></a><a name="p164097164093533"></a>void </p>
<p id="p729035113093533"><a name="p729035113093533"></a><a name="p729035113093533"></a>Sets the position for this analog clock. </p>
</td>
</tr>
<tr id="row1915498130093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p639964186093533"><a name="p639964186093533"></a><a name="p639964186093533"></a><a href="graphic.md#gaa7fad079e41c8efd137781350b60687b">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2003517645093533"><a name="p2003517645093533"></a><a name="p2003517645093533"></a>void </p>
<p id="p2026189113093533"><a name="p2026189113093533"></a><a name="p2026189113093533"></a>Sets the position and size for this analog clock. </p>
</td>
</tr>
<tr id="row717241604093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p748235632093533"><a name="p748235632093533"></a><a name="p748235632093533"></a><a href="graphic.md#ga1714e171ff1e9248932a9f2c14c82d12">SetWorkMode</a> (<a href="graphic.md#ga19db90932bc71e6bbced6ccf2935ac98">WorkMode</a> newMode) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1399876501093533"><a name="p1399876501093533"></a><a name="p1399876501093533"></a>void </p>
<p id="p1698716907093533"><a name="p1698716907093533"></a><a name="p1698716907093533"></a>Sets the working mode for this analog clock. </p>
</td>
</tr>
<tr id="row1269522734093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1667749302093533"><a name="p1667749302093533"></a><a name="p1667749302093533"></a><a href="graphic.md#ga5274a3e5b66e5f80aab899ef4e61edb2">UpdateClock</a> (bool clockInit) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p225346520093533"><a name="p225346520093533"></a><a name="p225346520093533"></a>void </p>
<p id="p1109775625093533"><a name="p1109775625093533"></a><a name="p1109775625093533"></a>Updates the time of this analog clock. </p>
</td>
</tr>
<tr id="row712330078093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p82775689093533"><a name="p82775689093533"></a><a name="p82775689093533"></a><a href="graphic.md#ga160a40d9f81c72b606b3c5b05168bacf">UIAbstractClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1449941353093533"><a name="p1449941353093533"></a><a name="p1449941353093533"></a> </p>
<p id="p1032999133093533"><a name="p1032999133093533"></a><a name="p1032999133093533"></a>A default constructor used to create a <strong id="b1514464799093533"><a name="b1514464799093533"></a><a name="b1514464799093533"></a><a href="ohos-uiabstractclock.md">UIAbstractClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row1993456057093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p67834041093533"><a name="p67834041093533"></a><a name="p67834041093533"></a><a href="graphic.md#ga93d3d68e48a79ee7fc4b42a9c0c0ccc1">UIAbstractClock</a> (uint8_t hour, uint8_t minute, uint8_t second)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p666664901093533"><a name="p666664901093533"></a><a name="p666664901093533"></a> </p>
<p id="p1290334737093533"><a name="p1290334737093533"></a><a name="p1290334737093533"></a>A constructor used to create a <strong id="b1682122942093533"><a name="b1682122942093533"></a><a name="b1682122942093533"></a><a href="ohos-uiabstractclock.md">UIAbstractClock</a></strong> instance with time elements (hour, minute and second). </p>
</td>
</tr>
<tr id="row886029682093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p662146813093533"><a name="p662146813093533"></a><a name="p662146813093533"></a><a href="graphic.md#ga0fb0c108b319f02b9d42b34c1d2c8708">~UIAbstractClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403723219093533"><a name="p1403723219093533"></a><a name="p1403723219093533"></a>virtual </p>
<p id="p1708359697093533"><a name="p1708359697093533"></a><a name="p1708359697093533"></a>A destructor used to delete the <strong id="b878646865093533"><a name="b878646865093533"></a><a name="b878646865093533"></a><a href="ohos-uiabstractclock.md">UIAbstractClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row282211469093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1067132814093533"><a name="p1067132814093533"></a><a name="p1067132814093533"></a><a href="graphic.md#ga44a7312163a4192670c00bb8f9916e51">SetTime24Hour</a> (uint8_t hour, uint8_t minute, uint8_t second)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1900995967093533"><a name="p1900995967093533"></a><a name="p1900995967093533"></a>void </p>
<p id="p1241023435093533"><a name="p1241023435093533"></a><a name="p1241023435093533"></a>Sets the time in 24-hour format. </p>
</td>
</tr>
<tr id="row535837640093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079857224093533"><a name="p2079857224093533"></a><a name="p2079857224093533"></a><a href="graphic.md#ga37750dfa0b5a47c8dcb61547dd991a6a">SetTime12Hour</a> (uint8_t hour, uint8_t minute, uint8_t second, bool am)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773326476093533"><a name="p773326476093533"></a><a name="p773326476093533"></a>void </p>
<p id="p1142364509093533"><a name="p1142364509093533"></a><a name="p1142364509093533"></a>Sets the time in 12-hour format. </p>
</td>
</tr>
<tr id="row1894648517093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p71038022093533"><a name="p71038022093533"></a><a name="p71038022093533"></a><a href="graphic.md#ga8cf863dfcd63410f2f20572a51f2516b">GetCurrentHour</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1468983144093533"><a name="p1468983144093533"></a><a name="p1468983144093533"></a>uint8_t </p>
<p id="p542969217093533"><a name="p542969217093533"></a><a name="p542969217093533"></a>Obtains the current number of hours. </p>
</td>
</tr>
<tr id="row544379582093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p380867990093533"><a name="p380867990093533"></a><a name="p380867990093533"></a><a href="graphic.md#ga5f0eea09577104d9126a07bfbc0b780a">GetCurrentMinute</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1836931901093533"><a name="p1836931901093533"></a><a name="p1836931901093533"></a>uint8_t </p>
<p id="p1572152729093533"><a name="p1572152729093533"></a><a name="p1572152729093533"></a>Obtains the current number of minutes. </p>
</td>
</tr>
<tr id="row319867557093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2086200367093533"><a name="p2086200367093533"></a><a name="p2086200367093533"></a><a href="graphic.md#ga7bd4d2d4631d9ea373d008ec7a5d18ff">GetCurrentSecond</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1787722992093533"><a name="p1787722992093533"></a><a name="p1787722992093533"></a>uint8_t </p>
<p id="p272471901093533"><a name="p272471901093533"></a><a name="p272471901093533"></a>Obtains the current number of seconds. </p>
</td>
</tr>
<tr id="row1508705431093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p32777554093533"><a name="p32777554093533"></a><a name="p32777554093533"></a><a href="graphic.md#gaf4c05e6acf6700d7edb69dc49cd6fef8">IncOneSecond</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1536280498093533"><a name="p1536280498093533"></a><a name="p1536280498093533"></a>void </p>
<p id="p182367134093533"><a name="p182367134093533"></a><a name="p182367134093533"></a>Increases the time by one second. </p>
</td>
</tr>
<tr id="row1259295731093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p605111837093533"><a name="p605111837093533"></a><a name="p605111837093533"></a><a href="graphic.md#gad2d78422d212ef1e93bb4a23e1ee3859">GetWorkMode</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p843580766093533"><a name="p843580766093533"></a><a name="p843580766093533"></a>virtual <a href="graphic.md#ga19db90932bc71e6bbced6ccf2935ac98">WorkMode</a> </p>
<p id="p539326655093533"><a name="p539326655093533"></a><a name="p539326655093533"></a>Obtains the working mode of this clock. </p>
</td>
</tr>
<tr id="row1981217519093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1982921660093533"><a name="p1982921660093533"></a><a name="p1982921660093533"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052948439093533"><a name="p1052948439093533"></a><a name="p1052948439093533"></a> </p>
<p id="p1110318134093533"><a name="p1110318134093533"></a><a name="p1110318134093533"></a>A default constructor used to create a <strong id="b308476597093533"><a name="b308476597093533"></a><a name="b308476597093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row627957980093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2094191968093533"><a name="p2094191968093533"></a><a name="p2094191968093533"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1441702140093533"><a name="p1441702140093533"></a><a name="p1441702140093533"></a>virtual </p>
<p id="p1354578452093533"><a name="p1354578452093533"></a><a name="p1354578452093533"></a>A destructor used to delete the <strong id="b61961820093533"><a name="b61961820093533"></a><a name="b61961820093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row901854903093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p727121834093533"><a name="p727121834093533"></a><a name="p727121834093533"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1615087239093533"><a name="p1615087239093533"></a><a name="p1615087239093533"></a>UIViewType </p>
<p id="p1392606365093533"><a name="p1392606365093533"></a><a name="p1392606365093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row718954382093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p990582788093533"><a name="p990582788093533"></a><a name="p990582788093533"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1983332830093533"><a name="p1983332830093533"></a><a name="p1983332830093533"></a>virtual void </p>
<p id="p905167704093533"><a name="p905167704093533"></a><a name="p905167704093533"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row1413904962093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p923735533093533"><a name="p923735533093533"></a><a name="p923735533093533"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1569188992093533"><a name="p1569188992093533"></a><a name="p1569188992093533"></a>virtual void </p>
<p id="p65787760093533"><a name="p65787760093533"></a><a name="p65787760093533"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1196915818093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1250867350093533"><a name="p1250867350093533"></a><a name="p1250867350093533"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p949876136093533"><a name="p949876136093533"></a><a name="p949876136093533"></a>virtual void </p>
<p id="p1124534039093533"><a name="p1124534039093533"></a><a name="p1124534039093533"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row1796211574093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1797128448093533"><a name="p1797128448093533"></a><a name="p1797128448093533"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p106859204093533"><a name="p106859204093533"></a><a name="p106859204093533"></a>virtual void </p>
<p id="p1558378126093533"><a name="p1558378126093533"></a><a name="p1558378126093533"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row810799557093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p302923196093533"><a name="p302923196093533"></a><a name="p302923196093533"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1293661151093533"><a name="p1293661151093533"></a><a name="p1293661151093533"></a>virtual void </p>
<p id="p1655893311093533"><a name="p1655893311093533"></a><a name="p1655893311093533"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1486799560093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p872281796093533"><a name="p872281796093533"></a><a name="p872281796093533"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1218325470093533"><a name="p1218325470093533"></a><a name="p1218325470093533"></a>virtual void </p>
<p id="p2109352536093533"><a name="p2109352536093533"></a><a name="p2109352536093533"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row1234009365093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1020634756093533"><a name="p1020634756093533"></a><a name="p1020634756093533"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p975006043093533"><a name="p975006043093533"></a><a name="p975006043093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p486870710093533"><a name="p486870710093533"></a><a name="p486870710093533"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1464066093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712168764093533"><a name="p1712168764093533"></a><a name="p1712168764093533"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1994462057093533"><a name="p1994462057093533"></a><a name="p1994462057093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1329858874093533"><a name="p1329858874093533"></a><a name="p1329858874093533"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row216369504093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401308301093533"><a name="p1401308301093533"></a><a name="p1401308301093533"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p199194911093533"><a name="p199194911093533"></a><a name="p199194911093533"></a>void </p>
<p id="p151277677093533"><a name="p151277677093533"></a><a name="p151277677093533"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1483744841093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1799430177093533"><a name="p1799430177093533"></a><a name="p1799430177093533"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073683966093533"><a name="p2073683966093533"></a><a name="p2073683966093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p740349153093533"><a name="p740349153093533"></a><a name="p740349153093533"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row441474714093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1005846734093533"><a name="p1005846734093533"></a><a name="p1005846734093533"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p462790611093533"><a name="p462790611093533"></a><a name="p462790611093533"></a>void </p>
<p id="p550650227093533"><a name="p550650227093533"></a><a name="p550650227093533"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row522249769093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p97119676093533"><a name="p97119676093533"></a><a name="p97119676093533"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1171245010093533"><a name="p1171245010093533"></a><a name="p1171245010093533"></a> </p>
<p id="p163292741093533"><a name="p163292741093533"></a><a name="p163292741093533"></a>A default constructor used to create an <strong id="b1785908256093533"><a name="b1785908256093533"></a><a name="b1785908256093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row351474337093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671246163093533"><a name="p671246163093533"></a><a name="p671246163093533"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1260056573093533"><a name="p1260056573093533"></a><a name="p1260056573093533"></a> </p>
<p id="p931381071093533"><a name="p931381071093533"></a><a name="p931381071093533"></a>A constructor used to create an <strong id="b428458431093533"><a name="b428458431093533"></a><a name="b428458431093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1031165964093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p170311852093533"><a name="p170311852093533"></a><a name="p170311852093533"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1272299022093533"><a name="p1272299022093533"></a><a name="p1272299022093533"></a>virtual </p>
<p id="p1925247962093533"><a name="p1925247962093533"></a><a name="p1925247962093533"></a>A destructor used to delete the <strong id="b1622638454093533"><a name="b1622638454093533"></a><a name="b1622638454093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row2057652716093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1421421306093533"><a name="p1421421306093533"></a><a name="p1421421306093533"></a><a href="graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1551032154093533"><a name="p1551032154093533"></a><a name="p1551032154093533"></a>virtual bool </p>
<p id="p190621361093533"><a name="p190621361093533"></a><a name="p190621361093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1639776737093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p389170925093533"><a name="p389170925093533"></a><a name="p389170925093533"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2118046832093533"><a name="p2118046832093533"></a><a name="p2118046832093533"></a>virtual void </p>
<p id="p482922201093533"><a name="p482922201093533"></a><a name="p482922201093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1158597242093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p407113095093533"><a name="p407113095093533"></a><a name="p407113095093533"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p554816460093533"><a name="p554816460093533"></a><a name="p554816460093533"></a>void </p>
<p id="p439726741093533"><a name="p439726741093533"></a><a name="p439726741093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row401160858093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p264496085093533"><a name="p264496085093533"></a><a name="p264496085093533"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2128121987093533"><a name="p2128121987093533"></a><a name="p2128121987093533"></a>void </p>
<p id="p571738670093533"><a name="p571738670093533"></a><a name="p571738670093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1034214729093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1960108964093533"><a name="p1960108964093533"></a><a name="p1960108964093533"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p204015946093533"><a name="p204015946093533"></a><a name="p204015946093533"></a>virtual bool </p>
<p id="p1657411362093533"><a name="p1657411362093533"></a><a name="p1657411362093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row809208487093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492231808093533"><a name="p1492231808093533"></a><a name="p1492231808093533"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p524541994093533"><a name="p524541994093533"></a><a name="p524541994093533"></a>virtual bool </p>
<p id="p942417195093533"><a name="p942417195093533"></a><a name="p942417195093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1231639093093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p541283607093533"><a name="p541283607093533"></a><a name="p541283607093533"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452264618093533"><a name="p1452264618093533"></a><a name="p1452264618093533"></a>virtual bool </p>
<p id="p1754486835093533"><a name="p1754486835093533"></a><a name="p1754486835093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row587733679093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453336506093533"><a name="p453336506093533"></a><a name="p453336506093533"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1766524082093533"><a name="p1766524082093533"></a><a name="p1766524082093533"></a>virtual bool </p>
<p id="p41739796093533"><a name="p41739796093533"></a><a name="p41739796093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row499848862093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p761492792093533"><a name="p761492792093533"></a><a name="p761492792093533"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1502322775093533"><a name="p1502322775093533"></a><a name="p1502322775093533"></a>virtual void </p>
<p id="p714719438093533"><a name="p714719438093533"></a><a name="p714719438093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row144330270093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p802532485093533"><a name="p802532485093533"></a><a name="p802532485093533"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p797318209093533"><a name="p797318209093533"></a><a name="p797318209093533"></a>virtual void </p>
<p id="p1083081171093533"><a name="p1083081171093533"></a><a name="p1083081171093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1011804441093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1815319365093533"><a name="p1815319365093533"></a><a name="p1815319365093533"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449476382093533"><a name="p449476382093533"></a><a name="p449476382093533"></a>virtual void </p>
<p id="p222555091093533"><a name="p222555091093533"></a><a name="p222555091093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1159510593093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1586122573093533"><a name="p1586122573093533"></a><a name="p1586122573093533"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1744730904093533"><a name="p1744730904093533"></a><a name="p1744730904093533"></a>virtual void </p>
<p id="p345353025093533"><a name="p345353025093533"></a><a name="p345353025093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row638812995093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1517064796093533"><a name="p1517064796093533"></a><a name="p1517064796093533"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1282371701093533"><a name="p1282371701093533"></a><a name="p1282371701093533"></a>void </p>
<p id="p1611276310093533"><a name="p1611276310093533"></a><a name="p1611276310093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row767007435093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1130692194093533"><a name="p1130692194093533"></a><a name="p1130692194093533"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p150659086093533"><a name="p150659086093533"></a><a name="p150659086093533"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p1324236359093533"><a name="p1324236359093533"></a><a name="p1324236359093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row985685229093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p748256760093533"><a name="p748256760093533"></a><a name="p748256760093533"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1232459572093533"><a name="p1232459572093533"></a><a name="p1232459572093533"></a>void </p>
<p id="p1418548050093533"><a name="p1418548050093533"></a><a name="p1418548050093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row29238851093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1211835609093533"><a name="p1211835609093533"></a><a name="p1211835609093533"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1427909005093533"><a name="p1427909005093533"></a><a name="p1427909005093533"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p2087710952093533"><a name="p2087710952093533"></a><a name="p2087710952093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1760563067093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p962973240093533"><a name="p962973240093533"></a><a name="p962973240093533"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p87506125093533"><a name="p87506125093533"></a><a name="p87506125093533"></a>void </p>
<p id="p1745570240093533"><a name="p1745570240093533"></a><a name="p1745570240093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1626479244093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079307199093533"><a name="p2079307199093533"></a><a name="p2079307199093533"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1607697134093533"><a name="p1607697134093533"></a><a name="p1607697134093533"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p1095935089093533"><a name="p1095935089093533"></a><a name="p1095935089093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row995778784093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p476963154093533"><a name="p476963154093533"></a><a name="p476963154093533"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1412376820093533"><a name="p1412376820093533"></a><a name="p1412376820093533"></a>void </p>
<p id="p2106207687093533"><a name="p2106207687093533"></a><a name="p2106207687093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row643555962093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p894953133093533"><a name="p894953133093533"></a><a name="p894953133093533"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1492637358093533"><a name="p1492637358093533"></a><a name="p1492637358093533"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1591824206093533"><a name="p1591824206093533"></a><a name="p1591824206093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row524774734093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1212383890093533"><a name="p1212383890093533"></a><a name="p1212383890093533"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601262398093533"><a name="p1601262398093533"></a><a name="p1601262398093533"></a>void </p>
<p id="p287854369093533"><a name="p287854369093533"></a><a name="p287854369093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1897771785093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589624812093533"><a name="p589624812093533"></a><a name="p589624812093533"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699358839093533"><a name="p1699358839093533"></a><a name="p1699358839093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1073971448093533"><a name="p1073971448093533"></a><a name="p1073971448093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1574928589093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p83951914093533"><a name="p83951914093533"></a><a name="p83951914093533"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1125806590093533"><a name="p1125806590093533"></a><a name="p1125806590093533"></a>void </p>
<p id="p788518158093533"><a name="p788518158093533"></a><a name="p788518158093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1547907048093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p219876437093533"><a name="p219876437093533"></a><a name="p219876437093533"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p706778789093533"><a name="p706778789093533"></a><a name="p706778789093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1211603157093533"><a name="p1211603157093533"></a><a name="p1211603157093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row870397013093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1142113814093533"><a name="p1142113814093533"></a><a name="p1142113814093533"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p902141086093533"><a name="p902141086093533"></a><a name="p902141086093533"></a>virtual void </p>
<p id="p1501099691093533"><a name="p1501099691093533"></a><a name="p1501099691093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1280604647093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p959282739093533"><a name="p959282739093533"></a><a name="p959282739093533"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2091933778093533"><a name="p2091933778093533"></a><a name="p2091933778093533"></a>bool </p>
<p id="p282536960093533"><a name="p282536960093533"></a><a name="p282536960093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1895376149093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p824192612093533"><a name="p824192612093533"></a><a name="p824192612093533"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908469098093533"><a name="p908469098093533"></a><a name="p908469098093533"></a>void </p>
<p id="p1368710876093533"><a name="p1368710876093533"></a><a name="p1368710876093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row794498687093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p167802553093533"><a name="p167802553093533"></a><a name="p167802553093533"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1763838294093533"><a name="p1763838294093533"></a><a name="p1763838294093533"></a>bool </p>
<p id="p1258934369093533"><a name="p1258934369093533"></a><a name="p1258934369093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row494819427093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494972924093533"><a name="p1494972924093533"></a><a name="p1494972924093533"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p894024985093533"><a name="p894024985093533"></a><a name="p894024985093533"></a>void </p>
<p id="p819976815093533"><a name="p819976815093533"></a><a name="p819976815093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1638556548093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1827760553093533"><a name="p1827760553093533"></a><a name="p1827760553093533"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1812936712093533"><a name="p1812936712093533"></a><a name="p1812936712093533"></a>bool </p>
<p id="p1728277089093533"><a name="p1728277089093533"></a><a name="p1728277089093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row974036224093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p653398730093533"><a name="p653398730093533"></a><a name="p653398730093533"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1976970490093533"><a name="p1976970490093533"></a><a name="p1976970490093533"></a>void </p>
<p id="p397818745093533"><a name="p397818745093533"></a><a name="p397818745093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row363815349093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1887450652093533"><a name="p1887450652093533"></a><a name="p1887450652093533"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1633247330093533"><a name="p1633247330093533"></a><a name="p1633247330093533"></a>bool </p>
<p id="p2056699179093533"><a name="p2056699179093533"></a><a name="p2056699179093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1035450148093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1118846968093533"><a name="p1118846968093533"></a><a name="p1118846968093533"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1557944271093533"><a name="p1557944271093533"></a><a name="p1557944271093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1321585501093533"><a name="p1321585501093533"></a><a name="p1321585501093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row516511984093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1121343300093533"><a name="p1121343300093533"></a><a name="p1121343300093533"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p221044341093533"><a name="p221044341093533"></a><a name="p221044341093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p321934875093533"><a name="p321934875093533"></a><a name="p321934875093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row2096249382093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p842533872093533"><a name="p842533872093533"></a><a name="p842533872093533"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032040423093533"><a name="p1032040423093533"></a><a name="p1032040423093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p511881679093533"><a name="p511881679093533"></a><a name="p511881679093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row834409455093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1917224959093533"><a name="p1917224959093533"></a><a name="p1917224959093533"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1821284523093533"><a name="p1821284523093533"></a><a name="p1821284523093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1099038643093533"><a name="p1099038643093533"></a><a name="p1099038643093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1783757335093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1854192146093533"><a name="p1854192146093533"></a><a name="p1854192146093533"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1635513220093533"><a name="p1635513220093533"></a><a name="p1635513220093533"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1568294685093533"><a name="p1568294685093533"></a><a name="p1568294685093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1126209160093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1308367633093533"><a name="p1308367633093533"></a><a name="p1308367633093533"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p480472805093533"><a name="p480472805093533"></a><a name="p480472805093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p489041883093533"><a name="p489041883093533"></a><a name="p489041883093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1182663542093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1572417540093533"><a name="p1572417540093533"></a><a name="p1572417540093533"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1137129210093533"><a name="p1137129210093533"></a><a name="p1137129210093533"></a>void </p>
<p id="p472750911093533"><a name="p472750911093533"></a><a name="p472750911093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row731766977093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p234189642093533"><a name="p234189642093533"></a><a name="p234189642093533"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1759741951093533"><a name="p1759741951093533"></a><a name="p1759741951093533"></a>virtual void </p>
<p id="p1847880122093533"><a name="p1847880122093533"></a><a name="p1847880122093533"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1350987645093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521242424093533"><a name="p521242424093533"></a><a name="p521242424093533"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2066781048093533"><a name="p2066781048093533"></a><a name="p2066781048093533"></a>virtual int16_t </p>
<p id="p875387577093533"><a name="p875387577093533"></a><a name="p875387577093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1655926228093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p557791890093533"><a name="p557791890093533"></a><a name="p557791890093533"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1337039219093533"><a name="p1337039219093533"></a><a name="p1337039219093533"></a>virtual void </p>
<p id="p1232762720093533"><a name="p1232762720093533"></a><a name="p1232762720093533"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1291472332093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p615430515093533"><a name="p615430515093533"></a><a name="p615430515093533"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1404926029093533"><a name="p1404926029093533"></a><a name="p1404926029093533"></a>virtual int16_t </p>
<p id="p1926340344093533"><a name="p1926340344093533"></a><a name="p1926340344093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1811787248093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p526846259093533"><a name="p526846259093533"></a><a name="p526846259093533"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1221377285093533"><a name="p1221377285093533"></a><a name="p1221377285093533"></a>virtual void </p>
<p id="p330913501093533"><a name="p330913501093533"></a><a name="p330913501093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1158271860093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1560296497093533"><a name="p1560296497093533"></a><a name="p1560296497093533"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1199781428093533"><a name="p1199781428093533"></a><a name="p1199781428093533"></a>virtual void </p>
<p id="p820864793093533"><a name="p820864793093533"></a><a name="p820864793093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row2107471888093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1860240687093533"><a name="p1860240687093533"></a><a name="p1860240687093533"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1722425076093533"><a name="p1722425076093533"></a><a name="p1722425076093533"></a>int16_t </p>
<p id="p1868659604093533"><a name="p1868659604093533"></a><a name="p1868659604093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row335365403093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p396260808093533"><a name="p396260808093533"></a><a name="p396260808093533"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p746679186093533"><a name="p746679186093533"></a><a name="p746679186093533"></a>virtual void </p>
<p id="p2099328050093533"><a name="p2099328050093533"></a><a name="p2099328050093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row697336201093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p291629097093533"><a name="p291629097093533"></a><a name="p291629097093533"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1936409810093533"><a name="p1936409810093533"></a><a name="p1936409810093533"></a>int16_t </p>
<p id="p1233503489093533"><a name="p1233503489093533"></a><a name="p1233503489093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1449049090093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p400644580093533"><a name="p400644580093533"></a><a name="p400644580093533"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p52053960093533"><a name="p52053960093533"></a><a name="p52053960093533"></a>bool </p>
<p id="p1956869073093533"><a name="p1956869073093533"></a><a name="p1956869073093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row864278281093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1458426354093533"><a name="p1458426354093533"></a><a name="p1458426354093533"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p107790258093533"><a name="p107790258093533"></a><a name="p107790258093533"></a>void </p>
<p id="p162829356093533"><a name="p162829356093533"></a><a name="p162829356093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1160078776093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p305720623093533"><a name="p305720623093533"></a><a name="p305720623093533"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1304878234093533"><a name="p1304878234093533"></a><a name="p1304878234093533"></a>void </p>
<p id="p1839588737093533"><a name="p1839588737093533"></a><a name="p1839588737093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1457365270093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p408396442093533"><a name="p408396442093533"></a><a name="p408396442093533"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2038319168093533"><a name="p2038319168093533"></a><a name="p2038319168093533"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p686394423093533"><a name="p686394423093533"></a><a name="p686394423093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row413459112093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p314592024093533"><a name="p314592024093533"></a><a name="p314592024093533"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p23167199093533"><a name="p23167199093533"></a><a name="p23167199093533"></a>void </p>
<p id="p199202524093533"><a name="p199202524093533"></a><a name="p199202524093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row248185478093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1648465179093533"><a name="p1648465179093533"></a><a name="p1648465179093533"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1579657694093533"><a name="p1579657694093533"></a><a name="p1579657694093533"></a>const char * </p>
<p id="p25927116093533"><a name="p25927116093533"></a><a name="p25927116093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row289900479093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p68813624093533"><a name="p68813624093533"></a><a name="p68813624093533"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1348195604093533"><a name="p1348195604093533"></a><a name="p1348195604093533"></a>void </p>
<p id="p1325141951093533"><a name="p1325141951093533"></a><a name="p1325141951093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1076945138093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p300487828093533"><a name="p300487828093533"></a><a name="p300487828093533"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1318944369093533"><a name="p1318944369093533"></a><a name="p1318944369093533"></a>int16_t </p>
<p id="p1531939070093533"><a name="p1531939070093533"></a><a name="p1531939070093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row945217858093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985786149093533"><a name="p1985786149093533"></a><a name="p1985786149093533"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1913308312093533"><a name="p1913308312093533"></a><a name="p1913308312093533"></a>virtual void </p>
<p id="p961483115093533"><a name="p961483115093533"></a><a name="p961483115093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1156910597093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p761482639093533"><a name="p761482639093533"></a><a name="p761482639093533"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p182630404093533"><a name="p182630404093533"></a><a name="p182630404093533"></a>void </p>
<p id="p2060205156093533"><a name="p2060205156093533"></a><a name="p2060205156093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row2105859409093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1927093791093533"><a name="p1927093791093533"></a><a name="p1927093791093533"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1877716241093533"><a name="p1877716241093533"></a><a name="p1877716241093533"></a>void </p>
<p id="p319111210093533"><a name="p319111210093533"></a><a name="p319111210093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1589739979093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1341941430093533"><a name="p1341941430093533"></a><a name="p1341941430093533"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p283605899093533"><a name="p283605899093533"></a><a name="p283605899093533"></a>void </p>
<p id="p448737783093533"><a name="p448737783093533"></a><a name="p448737783093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row883314312093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1090524797093533"><a name="p1090524797093533"></a><a name="p1090524797093533"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1405926856093533"><a name="p1405926856093533"></a><a name="p1405926856093533"></a>void </p>
<p id="p1598685083093533"><a name="p1598685083093533"></a><a name="p1598685083093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1372921236093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p963186377093533"><a name="p963186377093533"></a><a name="p963186377093533"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1556986354093533"><a name="p1556986354093533"></a><a name="p1556986354093533"></a>void </p>
<p id="p1312854593093533"><a name="p1312854593093533"></a><a name="p1312854593093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1525461643093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p776689489093533"><a name="p776689489093533"></a><a name="p776689489093533"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p618406940093533"><a name="p618406940093533"></a><a name="p618406940093533"></a>void </p>
<p id="p1659856095093533"><a name="p1659856095093533"></a><a name="p1659856095093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row358018274093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1270140358093533"><a name="p1270140358093533"></a><a name="p1270140358093533"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p470265958093533"><a name="p470265958093533"></a><a name="p470265958093533"></a>void </p>
<p id="p1330876463093533"><a name="p1330876463093533"></a><a name="p1330876463093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row357046861093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p272943708093533"><a name="p272943708093533"></a><a name="p272943708093533"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p755874875093533"><a name="p755874875093533"></a><a name="p755874875093533"></a>void </p>
<p id="p846321308093533"><a name="p846321308093533"></a><a name="p846321308093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row510698747093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p597106902093533"><a name="p597106902093533"></a><a name="p597106902093533"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p339739404093533"><a name="p339739404093533"></a><a name="p339739404093533"></a>void </p>
<p id="p1621257224093533"><a name="p1621257224093533"></a><a name="p1621257224093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1486634750093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1327735843093533"><a name="p1327735843093533"></a><a name="p1327735843093533"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1005017638093533"><a name="p1005017638093533"></a><a name="p1005017638093533"></a>void </p>
<p id="p368865700093533"><a name="p368865700093533"></a><a name="p368865700093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1015627370093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1782635077093533"><a name="p1782635077093533"></a><a name="p1782635077093533"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1608419116093533"><a name="p1608419116093533"></a><a name="p1608419116093533"></a>void </p>
<p id="p366242601093533"><a name="p366242601093533"></a><a name="p366242601093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row664577716093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p885375795093533"><a name="p885375795093533"></a><a name="p885375795093533"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p818118361093533"><a name="p818118361093533"></a><a name="p818118361093533"></a>void </p>
<p id="p1732931775093533"><a name="p1732931775093533"></a><a name="p1732931775093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row245234733093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1108988117093533"><a name="p1108988117093533"></a><a name="p1108988117093533"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1343799141093533"><a name="p1343799141093533"></a><a name="p1343799141093533"></a>void </p>
<p id="p2088137142093533"><a name="p2088137142093533"></a><a name="p2088137142093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row2065876715093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2139093440093533"><a name="p2139093440093533"></a><a name="p2139093440093533"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1893466461093533"><a name="p1893466461093533"></a><a name="p1893466461093533"></a>void </p>
<p id="p1488531933093533"><a name="p1488531933093533"></a><a name="p1488531933093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row74079781093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p19540658093533"><a name="p19540658093533"></a><a name="p19540658093533"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1048279171093533"><a name="p1048279171093533"></a><a name="p1048279171093533"></a>void </p>
<p id="p841123407093533"><a name="p841123407093533"></a><a name="p841123407093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1946782982093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p242314597093533"><a name="p242314597093533"></a><a name="p242314597093533"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p872946124093533"><a name="p872946124093533"></a><a name="p872946124093533"></a>virtual void </p>
<p id="p738728245093533"><a name="p738728245093533"></a><a name="p738728245093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row281546285093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1648802197093533"><a name="p1648802197093533"></a><a name="p1648802197093533"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2057394711093533"><a name="p2057394711093533"></a><a name="p2057394711093533"></a>virtual void </p>
<p id="p1112288821093533"><a name="p1112288821093533"></a><a name="p1112288821093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1369103974093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2129837942093533"><a name="p2129837942093533"></a><a name="p2129837942093533"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p740326752093533"><a name="p740326752093533"></a><a name="p740326752093533"></a>virtual int64_t </p>
<p id="p1193722286093533"><a name="p1193722286093533"></a><a name="p1193722286093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1932306686093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1288962397093533"><a name="p1288962397093533"></a><a name="p1288962397093533"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1855289938093533"><a name="p1855289938093533"></a><a name="p1855289938093533"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p567410932093533"><a name="p567410932093533"></a><a name="p567410932093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row770443579093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p571027610093533"><a name="p571027610093533"></a><a name="p571027610093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p168326893093533"><a name="p168326893093533"></a><a name="p168326893093533"></a>void * </p>
<p id="p999987207093533"><a name="p999987207093533"></a><a name="p999987207093533"></a>Overrides the <strong id="b2091630461093533"><a name="b2091630461093533"></a><a name="b2091630461093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row648711676093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1633051478093533"><a name="p1633051478093533"></a><a name="p1633051478093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1483338093533"><a name="p1483338093533"></a><a name="p1483338093533"></a>void </p>
<p id="p1524977220093533"><a name="p1524977220093533"></a><a name="p1524977220093533"></a>Overrides the <strong id="b1624695599093533"><a name="b1624695599093533"></a><a name="b1624695599093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1803473228093533"></a>
<table><thead align="left"><tr id="row2066894937093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2018841792093533"><a name="p2018841792093533"></a><a name="p2018841792093533"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p947970027093533"><a name="p947970027093533"></a><a name="p947970027093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1211395018093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p131991814093533"><a name="p131991814093533"></a><a name="p131991814093533"></a><a href="graphic.md#ga7f433b8551722451f880e7fa05731a2f">ONE_MINUTE_IN_SECOND</a> = 60</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p139559232093533"><a name="p139559232093533"></a><a name="p139559232093533"></a>Represents 60 seconds per minute. </p>
</td>
</tr>
<tr id="row119314737093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1532003572093533"><a name="p1532003572093533"></a><a name="p1532003572093533"></a><a href="graphic.md#ga5434b911b6f7e0637ac0626c9dd0f513">ONE_HOUR_IN_MINUTE</a> = 60</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p679546126093533"><a name="p679546126093533"></a><a name="p679546126093533"></a>Represents 60 minutes per hour. </p>
</td>
</tr>
<tr id="row726478386093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2096774928093533"><a name="p2096774928093533"></a><a name="p2096774928093533"></a><a href="graphic.md#gae7742f1e715885ecc4f5b67d57530319">ONE_DAY_IN_HOUR</a> = 24</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p952501270093533"><a name="p952501270093533"></a><a name="p952501270093533"></a>Represents 24 hours per day. </p>
</td>
</tr>
<tr id="row1415210151093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1680180705093533"><a name="p1680180705093533"></a><a name="p1680180705093533"></a><a href="graphic.md#gae40a5ae3834b626e2976fab83f166171">HALF_DAY_IN_HOUR</a> = 12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p227698163093533"><a name="p227698163093533"></a><a name="p227698163093533"></a>Represents 12 hours every half day. </p>
</td>
</tr>
<tr id="row1197795519093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1464439355093533"><a name="p1464439355093533"></a><a name="p1464439355093533"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1558516975093533"><a name="p1558516975093533"></a><a name="p1558516975093533"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row779273844093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p449015898093533"><a name="p449015898093533"></a><a name="p449015898093533"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2017656334093533"><a name="p2017656334093533"></a><a name="p2017656334093533"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row1951573304093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1536720121093533"><a name="p1536720121093533"></a><a name="p1536720121093533"></a><a href="graphic.md#gaabfbbb277dabf5477c628336a429f8ad">currentHour_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2044196835093533"><a name="p2044196835093533"></a><a name="p2044196835093533"></a>Represents the current number of hours. </p>
</td>
</tr>
<tr id="row1209053440093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1860857582093533"><a name="p1860857582093533"></a><a name="p1860857582093533"></a><a href="graphic.md#ga34c3518c0dc9f35fc77b240b6f8d0dcb">currentMinute_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773023892093533"><a name="p773023892093533"></a><a name="p773023892093533"></a>Represents the current number of minutes. </p>
</td>
</tr>
<tr id="row1245627024093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1932218041093533"><a name="p1932218041093533"></a><a name="p1932218041093533"></a><a href="graphic.md#ga5b2749cdc5e52551731923d8268b8d5d">currentSecond_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p102496623093533"><a name="p102496623093533"></a><a name="p102496623093533"></a>Represents the current number of seconds. </p>
</td>
</tr>
<tr id="row157231173093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p508687770093533"><a name="p508687770093533"></a><a name="p508687770093533"></a><a href="graphic.md#gab08c7c490a5b42fcdee04d45b5521d1c">mode_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1188058355093533"><a name="p1188058355093533"></a><a name="p1188058355093533"></a>Represents the current working mode of this clock. </p>
</td>
</tr>
<tr id="row1592403097093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p694410932093533"><a name="p694410932093533"></a><a name="p694410932093533"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9631175093533"><a name="p9631175093533"></a><a name="p9631175093533"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row110165748093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1048098110093533"><a name="p1048098110093533"></a><a name="p1048098110093533"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964218658093533"><a name="p964218658093533"></a><a name="p964218658093533"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row152287525093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645364867093533"><a name="p645364867093533"></a><a name="p645364867093533"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p956146493093533"><a name="p956146493093533"></a><a name="p956146493093533"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1580047371093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p877863952093533"><a name="p877863952093533"></a><a name="p877863952093533"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1985306503093533"><a name="p1985306503093533"></a><a name="p1985306503093533"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1018315499093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1741786664093533"><a name="p1741786664093533"></a><a name="p1741786664093533"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p713940207093533"><a name="p713940207093533"></a><a name="p713940207093533"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1501310146093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1773259014093533"><a name="p1773259014093533"></a><a name="p1773259014093533"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p249824642093533"><a name="p249824642093533"></a><a name="p249824642093533"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

