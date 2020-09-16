# OHOS::UIAnalogClock::Hand<a name="EN-US_TOPIC_0000001054918175"></a>

## **Overview**<a name="section84972521093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the basic attributes of the analog clock hands. This is an inner class of  **[UIAbstractClock](ohos-uiabstractclock.md)**. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section2095217974093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1940799366093533"></a>
<table><thead align="left"><tr id="row2016812343093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1408086593093533"><a name="p1408086593093533"></a><a name="p1408086593093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1300763478093533"><a name="p1300763478093533"></a><a name="p1300763478093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row7507023093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p820097594093533"><a name="p820097594093533"></a><a name="p820097594093533"></a><a href="graphic.md#gac075169429f99f60ed660a44db7f4031">Hand</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1598170865093533"><a name="p1598170865093533"></a><a name="p1598170865093533"></a> </p>
<p id="p523535200093533"><a name="p523535200093533"></a><a name="p523535200093533"></a>A default constructor used to create a <strong id="b1253864254093533"><a name="b1253864254093533"></a><a name="b1253864254093533"></a><a href="ohos-uianalogclock-hand.md">Hand</a></strong> instance. </p>
</td>
</tr>
<tr id="row638258948093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p946579394093533"><a name="p946579394093533"></a><a name="p946579394093533"></a><a href="graphic.md#ga1e433482830dd12b9b40430dab92505f">~Hand</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p957276305093533"><a name="p957276305093533"></a><a name="p957276305093533"></a>virtual </p>
<p id="p1839773043093533"><a name="p1839773043093533"></a><a name="p1839773043093533"></a>A destructor used to delete the <strong id="b1872151553093533"><a name="b1872151553093533"></a><a name="b1872151553093533"></a><a href="ohos-uianalogclock-hand.md">Hand</a></strong> instance. </p>
</td>
</tr>
<tr id="row1637393063093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p269788545093533"><a name="p269788545093533"></a><a name="p269788545093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1910606838093533"><a name="p1910606838093533"></a><a name="p1910606838093533"></a>void * </p>
<p id="p1816513678093533"><a name="p1816513678093533"></a><a name="p1816513678093533"></a>Overrides the <strong id="b1506482776093533"><a name="b1506482776093533"></a><a name="b1506482776093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row142134493093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2049729074093533"><a name="p2049729074093533"></a><a name="p2049729074093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p776968825093533"><a name="p776968825093533"></a><a name="p776968825093533"></a>void </p>
<p id="p2080261165093533"><a name="p2080261165093533"></a><a name="p2080261165093533"></a>Overrides the <strong id="b727013161093533"><a name="b727013161093533"></a><a name="b727013161093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Data Fields<a name="pub-attribs"></a>

<a name="table1657516199093533"></a>
<table><thead align="left"><tr id="row1954459622093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1557543217093533"><a name="p1557543217093533"></a><a name="p1557543217093533"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2126767406093533"><a name="p2126767406093533"></a><a name="p2126767406093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row370251635093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1855029883093533"><a name="p1855029883093533"></a><a name="p1855029883093533"></a><a href="graphic.md#ga809741355c5cc352c0755915002b987f">center_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1075623374093533"><a name="p1075623374093533"></a><a name="p1075623374093533"></a> <a href="ohos-point.md">Point</a> </p>
<p id="p106737323093533"><a name="p106737323093533"></a><a name="p106737323093533"></a>Represents the rotation center of a clock hand. </p>
</td>
</tr>
<tr id="row1106397095093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651106564093533"><a name="p651106564093533"></a><a name="p651106564093533"></a><a href="graphic.md#gac140795ee9a077a7ccc4f9f466e7d3a0">initAngle_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1312173306093533"><a name="p1312173306093533"></a><a name="p1312173306093533"></a> uint16_t </p>
<p id="p2024934510093533"><a name="p2024934510093533"></a><a name="p2024934510093533"></a>Represents the initial clockwise rotation angle of a clock hand. The default value is <strong id="b1864205794093533"><a name="b1864205794093533"></a><a name="b1864205794093533"></a>0</strong>, indicating that the hand direction is vertically upward. </p>
</td>
</tr>
<tr id="row775114161093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1594676495093533"><a name="p1594676495093533"></a><a name="p1594676495093533"></a><a href="graphic.md#ga55c99b69410211c1afa8a2038e248d46">preAngle_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1057897101093533"><a name="p1057897101093533"></a><a name="p1057897101093533"></a> uint16_t </p>
<p id="p1599576408093533"><a name="p1599576408093533"></a><a name="p1599576408093533"></a>Represents the latest rotation angle of this clock hand. </p>
</td>
</tr>
<tr id="row248534339093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1593304389093533"><a name="p1593304389093533"></a><a name="p1593304389093533"></a><a href="graphic.md#ga33b72e532b7391016669673b75c776e0">nextAngle_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p569994513093533"><a name="p569994513093533"></a><a name="p569994513093533"></a> uint16_t </p>
<p id="p481475914093533"><a name="p481475914093533"></a><a name="p481475914093533"></a>Represents the next rotation angle of this clock hand. </p>
</td>
</tr>
<tr id="row491507874093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p50523285093533"><a name="p50523285093533"></a><a name="p50523285093533"></a><a href="graphic.md#gab84788e217377616073a56752a6b4d42">position_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p921340814093533"><a name="p921340814093533"></a><a name="p921340814093533"></a> <a href="ohos-point.md">Point</a> </p>
<p id="p819621652093533"><a name="p819621652093533"></a><a name="p819621652093533"></a>Represents the position of a hand on this analog clock. </p>
</td>
</tr>
<tr id="row1860500649093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2118347247093533"><a name="p2118347247093533"></a><a name="p2118347247093533"></a><a href="graphic.md#gae08106f4adf8b064a5163f52f46f42ab">imageInfo_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032004577093533"><a name="p1032004577093533"></a><a name="p1032004577093533"></a> <a href="ohos-imageinfo.md">ImageInfo</a> </p>
<p id="p30471665093533"><a name="p30471665093533"></a><a name="p30471665093533"></a>Represents the image information of this clock hand. </p>
</td>
</tr>
<tr id="row1397067513093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1337327138093533"><a name="p1337327138093533"></a><a name="p1337327138093533"></a><a href="graphic.md#ga884ffa215aff8d5094430581985432a7">trans_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1314038510093533"><a name="p1314038510093533"></a><a name="p1314038510093533"></a> <a href="ohos-transformmap.md">TransformMap</a> </p>
<p id="p1245986910093533"><a name="p1245986910093533"></a><a name="p1245986910093533"></a>Represents the information about the rotation and translation of this clock hand. </p>
</td>
</tr>
<tr id="row1864106030093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1506023900093533"><a name="p1506023900093533"></a><a name="p1506023900093533"></a><a href="graphic.md#gab0dc9c3ed8b2cd59a8d8b0db23920b6a">target_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1647437209093533"><a name="p1647437209093533"></a><a name="p1647437209093533"></a> <a href="ohos-rect.md">Rect</a> </p>
<p id="p951345568093533"><a name="p951345568093533"></a><a name="p951345568093533"></a>Represents the new rectangle area after the rotation and translation. </p>
</td>
</tr>
<tr id="row231986625093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p179059136093533"><a name="p179059136093533"></a><a name="p179059136093533"></a><a href="graphic.md#ga869869c28bbfb68610e35b13d5e42704">color_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2083212637093533"><a name="p2083212637093533"></a><a name="p2083212637093533"></a> <a href="ohos-color32.md">ColorType</a> </p>
<p id="p107107288093533"><a name="p107107288093533"></a><a name="p107107288093533"></a>Represents the color of this clock hand. </p>
</td>
</tr>
<tr id="row971114845093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p482079774093533"><a name="p482079774093533"></a><a name="p482079774093533"></a><a href="graphic.md#gaea93bf4419cbd77518adb9b5818459c1">width_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1323531110093533"><a name="p1323531110093533"></a><a name="p1323531110093533"></a> uint16_t </p>
<p id="p1841072414093533"><a name="p1841072414093533"></a><a name="p1841072414093533"></a>Represents the width of this clock hand. </p>
</td>
</tr>
<tr id="row1846724765093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806751595093533"><a name="p1806751595093533"></a><a name="p1806751595093533"></a><a href="graphic.md#gaab68804b560953e15fd645d8cc3e3cb1">height_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p810574023093533"><a name="p810574023093533"></a><a name="p810574023093533"></a> uint16_t </p>
<p id="p1005399828093533"><a name="p1005399828093533"></a><a name="p1005399828093533"></a>Represents the height of this clock hand. </p>
</td>
</tr>
<tr id="row1646801293093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1711212218093533"><a name="p1711212218093533"></a><a name="p1711212218093533"></a><a href="graphic.md#ga61f8aca511f419a431751251b95da518">opacity_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p350892992093533"><a name="p350892992093533"></a><a name="p350892992093533"></a> OpacityType </p>
<p id="p146962793093533"><a name="p146962793093533"></a><a name="p146962793093533"></a>Represents the opacity of this clock hand. </p>
</td>
</tr>
<tr id="row769301986093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1931978797093533"><a name="p1931978797093533"></a><a name="p1931978797093533"></a><a href="graphic.md#ga110679ca3eaad8f786a8c4afc07d36c0">drawtype_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p909907773093533"><a name="p909907773093533"></a><a name="p909907773093533"></a> <a href="graphic.md#ga0a595eeb50ce4e7dfff9ede16098d2db">DrawType</a> </p>
<p id="p807348279093533"><a name="p807348279093533"></a><a name="p807348279093533"></a>Represents the drawing type of this clock hand. </p>
</td>
</tr>
</tbody>
</table>

