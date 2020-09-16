# OHOS::UIAbstractClock<a name="ZH-CN_TOPIC_0000001055358128"></a>

## **Overview**<a name="section1830693519093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

An abstract class that contains functions for converting units of time \(hour, minute, and second\), setting and obtaining the time. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1975654017093533"></a>

## Public Types<a name="pub-types"></a>

<a name="table31484024093533"></a>
<table><thead align="left"><tr id="row366808779093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p64491466093533"><a name="p64491466093533"></a><a name="p64491466093533"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p919781259093533"><a name="p919781259093533"></a><a name="p919781259093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1067442859093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1399647762093533"><a name="p1399647762093533"></a><a name="p1399647762093533"></a><a href="Graphic.md#ga19db90932bc71e6bbced6ccf2935ac98">WorkMode</a> { <a href="Graphic.md#gga19db90932bc71e6bbced6ccf2935ac98a2025ac1a1f63409f0b37f444547ec859">ALWAYS_ON</a>, <a href="Graphic.md#gga19db90932bc71e6bbced6ccf2935ac98a8d32f103a422c6675618f5e9773b2eaa">NORMAL</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p992597079093533"><a name="p992597079093533"></a><a name="p992597079093533"></a>Enumerates the working modes of this clock. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table152628231093533"></a>
<table><thead align="left"><tr id="row62834998093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1084083921093533"><a name="p1084083921093533"></a><a name="p1084083921093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1558529266093533"><a name="p1558529266093533"></a><a name="p1558529266093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row334755582093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p277181405093533"><a name="p277181405093533"></a><a name="p277181405093533"></a><a href="Graphic.md#ga160a40d9f81c72b606b3c5b05168bacf">UIAbstractClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756180985093533"><a name="p756180985093533"></a><a name="p756180985093533"></a>&nbsp;</p>
<p id="p856346985093533"><a name="p856346985093533"></a><a name="p856346985093533"></a>A default constructor used to create a <strong id="b594614076093533"><a name="b594614076093533"></a><a name="b594614076093533"></a><a href="OHOS-UIAbstractClock.md">UIAbstractClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row83661640093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1104760137093533"><a name="p1104760137093533"></a><a name="p1104760137093533"></a><a href="Graphic.md#ga93d3d68e48a79ee7fc4b42a9c0c0ccc1">UIAbstractClock</a> (uint8_t hour, uint8_t minute, uint8_t second)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1278999728093533"><a name="p1278999728093533"></a><a name="p1278999728093533"></a>&nbsp;</p>
<p id="p1743418170093533"><a name="p1743418170093533"></a><a name="p1743418170093533"></a>A constructor used to create a <strong id="b772253190093533"><a name="b772253190093533"></a><a name="b772253190093533"></a><a href="OHOS-UIAbstractClock.md">UIAbstractClock</a></strong> instance with time elements (hour, minute and second). </p>
</td>
</tr>
<tr id="row255712858093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p87106121093533"><a name="p87106121093533"></a><a name="p87106121093533"></a><a href="Graphic.md#ga0fb0c108b319f02b9d42b34c1d2c8708">~UIAbstractClock</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964701171093533"><a name="p964701171093533"></a><a name="p964701171093533"></a>virtual&nbsp;</p>
<p id="p547365548093533"><a name="p547365548093533"></a><a name="p547365548093533"></a>A destructor used to delete the <strong id="b1565923776093533"><a name="b1565923776093533"></a><a name="b1565923776093533"></a><a href="OHOS-UIAbstractClock.md">UIAbstractClock</a></strong> instance. </p>
</td>
</tr>
<tr id="row567844540093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p670471846093533"><a name="p670471846093533"></a><a name="p670471846093533"></a><a href="Graphic.md#ga8f7edc9e099688b4fd2b3ed3171eac58">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p146848504093533"><a name="p146848504093533"></a><a name="p146848504093533"></a>UIViewType&nbsp;</p>
<p id="p1090304469093533"><a name="p1090304469093533"></a><a name="p1090304469093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1977804688093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1568676684093533"><a name="p1568676684093533"></a><a name="p1568676684093533"></a><a href="Graphic.md#ga44a7312163a4192670c00bb8f9916e51">SetTime24Hour</a> (uint8_t hour, uint8_t minute, uint8_t second)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p532525975093533"><a name="p532525975093533"></a><a name="p532525975093533"></a>void&nbsp;</p>
<p id="p203475222093533"><a name="p203475222093533"></a><a name="p203475222093533"></a>Sets the time in 24-hour format. </p>
</td>
</tr>
<tr id="row240343114093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1486209109093533"><a name="p1486209109093533"></a><a name="p1486209109093533"></a><a href="Graphic.md#ga37750dfa0b5a47c8dcb61547dd991a6a">SetTime12Hour</a> (uint8_t hour, uint8_t minute, uint8_t second, bool am)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p165849904093533"><a name="p165849904093533"></a><a name="p165849904093533"></a>void&nbsp;</p>
<p id="p1673775844093533"><a name="p1673775844093533"></a><a name="p1673775844093533"></a>Sets the time in 12-hour format. </p>
</td>
</tr>
<tr id="row1953344830093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1038852963093533"><a name="p1038852963093533"></a><a name="p1038852963093533"></a><a href="Graphic.md#ga8cf863dfcd63410f2f20572a51f2516b">GetCurrentHour</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1724279157093533"><a name="p1724279157093533"></a><a name="p1724279157093533"></a>uint8_t&nbsp;</p>
<p id="p1286384067093533"><a name="p1286384067093533"></a><a name="p1286384067093533"></a>Obtains the current number of hours. </p>
</td>
</tr>
<tr id="row1869977513093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1274146306093533"><a name="p1274146306093533"></a><a name="p1274146306093533"></a><a href="Graphic.md#ga5f0eea09577104d9126a07bfbc0b780a">GetCurrentMinute</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705364793093533"><a name="p1705364793093533"></a><a name="p1705364793093533"></a>uint8_t&nbsp;</p>
<p id="p1941634956093533"><a name="p1941634956093533"></a><a name="p1941634956093533"></a>Obtains the current number of minutes. </p>
</td>
</tr>
<tr id="row271446088093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p604490349093533"><a name="p604490349093533"></a><a name="p604490349093533"></a><a href="Graphic.md#ga7bd4d2d4631d9ea373d008ec7a5d18ff">GetCurrentSecond</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932458379093533"><a name="p1932458379093533"></a><a name="p1932458379093533"></a>uint8_t&nbsp;</p>
<p id="p1818040236093533"><a name="p1818040236093533"></a><a name="p1818040236093533"></a>Obtains the current number of seconds. </p>
</td>
</tr>
<tr id="row1972060230093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1692891933093533"><a name="p1692891933093533"></a><a name="p1692891933093533"></a><a href="Graphic.md#gaf4c05e6acf6700d7edb69dc49cd6fef8">IncOneSecond</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1151623547093533"><a name="p1151623547093533"></a><a name="p1151623547093533"></a>void&nbsp;</p>
<p id="p1837713372093533"><a name="p1837713372093533"></a><a name="p1837713372093533"></a>Increases the time by one second. </p>
</td>
</tr>
<tr id="row1475649342093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1682306910093533"><a name="p1682306910093533"></a><a name="p1682306910093533"></a><a href="Graphic.md#gad7c0fba1eac5d10998954e9c1e097197">UpdateClock</a> (bool clockInit)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1196543222093533"><a name="p1196543222093533"></a><a name="p1196543222093533"></a>virtual void&nbsp;</p>
<p id="p853722857093533"><a name="p853722857093533"></a><a name="p853722857093533"></a>Updates this clock. </p>
</td>
</tr>
<tr id="row1104017287093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1022616357093533"><a name="p1022616357093533"></a><a name="p1022616357093533"></a><a href="Graphic.md#gaafa5df66c896268de27bf335c1b72b92">SetWorkMode</a> (<a href="Graphic.md#ga19db90932bc71e6bbced6ccf2935ac98">WorkMode</a> newMode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p403590869093533"><a name="p403590869093533"></a><a name="p403590869093533"></a>virtual void&nbsp;</p>
<p id="p418312933093533"><a name="p418312933093533"></a><a name="p418312933093533"></a>Sets the working mode for this clock. </p>
</td>
</tr>
<tr id="row959756327093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p813164762093533"><a name="p813164762093533"></a><a name="p813164762093533"></a><a href="Graphic.md#gad2d78422d212ef1e93bb4a23e1ee3859">GetWorkMode</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1107929977093533"><a name="p1107929977093533"></a><a name="p1107929977093533"></a>virtual <a href="Graphic.md#ga19db90932bc71e6bbced6ccf2935ac98">WorkMode</a>&nbsp;</p>
<p id="p1691817190093533"><a name="p1691817190093533"></a><a name="p1691817190093533"></a>Obtains the working mode of this clock. </p>
</td>
</tr>
<tr id="row420859644093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p606982720093533"><a name="p606982720093533"></a><a name="p606982720093533"></a><a href="Graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1628601786093533"><a name="p1628601786093533"></a><a name="p1628601786093533"></a>&nbsp;</p>
<p id="p1531654861093533"><a name="p1531654861093533"></a><a name="p1531654861093533"></a>A default constructor used to create a <strong id="b1316789819093533"><a name="b1316789819093533"></a><a name="b1316789819093533"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row284885548093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1861013807093533"><a name="p1861013807093533"></a><a name="p1861013807093533"></a><a href="Graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1362714415093533"><a name="p1362714415093533"></a><a name="p1362714415093533"></a>virtual&nbsp;</p>
<p id="p19298837093533"><a name="p19298837093533"></a><a name="p19298837093533"></a>A destructor used to delete the <strong id="b557137717093533"><a name="b557137717093533"></a><a name="b557137717093533"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1165067892093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1446243107093533"><a name="p1446243107093533"></a><a name="p1446243107093533"></a><a href="Graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1843591506093533"><a name="p1843591506093533"></a><a name="p1843591506093533"></a>UIViewType&nbsp;</p>
<p id="p322418584093533"><a name="p322418584093533"></a><a name="p322418584093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1425947876093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p610262106093533"><a name="p610262106093533"></a><a name="p610262106093533"></a><a href="Graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1873411169093533"><a name="p1873411169093533"></a><a name="p1873411169093533"></a>virtual void&nbsp;</p>
<p id="p1232657291093533"><a name="p1232657291093533"></a><a name="p1232657291093533"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row623818360093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p105220654093533"><a name="p105220654093533"></a><a name="p105220654093533"></a><a href="Graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="OHOS-UIView.md">UIView</a> *prevView, <a href="OHOS-UIView.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p155842840093533"><a name="p155842840093533"></a><a name="p155842840093533"></a>virtual void&nbsp;</p>
<p id="p1750644273093533"><a name="p1750644273093533"></a><a name="p1750644273093533"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row32961962093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1564815926093533"><a name="p1564815926093533"></a><a name="p1564815926093533"></a><a href="Graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p35042067093533"><a name="p35042067093533"></a><a name="p35042067093533"></a>virtual void&nbsp;</p>
<p id="p2138041390093533"><a name="p2138041390093533"></a><a name="p2138041390093533"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row191229724093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p263675253093533"><a name="p263675253093533"></a><a name="p263675253093533"></a><a href="Graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p378466263093533"><a name="p378466263093533"></a><a name="p378466263093533"></a>virtual void&nbsp;</p>
<p id="p533472126093533"><a name="p533472126093533"></a><a name="p533472126093533"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1961703489093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1295890241093533"><a name="p1295890241093533"></a><a name="p1295890241093533"></a><a href="Graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p601524088093533"><a name="p601524088093533"></a><a name="p601524088093533"></a>virtual void&nbsp;</p>
<p id="p204738744093533"><a name="p204738744093533"></a><a name="p204738744093533"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row255921711093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p916365269093533"><a name="p916365269093533"></a><a name="p916365269093533"></a><a href="Graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1612714808093533"><a name="p1612714808093533"></a><a name="p1612714808093533"></a>virtual void&nbsp;</p>
<p id="p775483171093533"><a name="p775483171093533"></a><a name="p775483171093533"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row1046905684093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149426651093533"><a name="p1149426651093533"></a><a name="p1149426651093533"></a><a href="Graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1478375271093533"><a name="p1478375271093533"></a><a name="p1478375271093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1929064160093533"><a name="p1929064160093533"></a><a name="p1929064160093533"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1467390400093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p465473578093533"><a name="p465473578093533"></a><a name="p465473578093533"></a><a href="Graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1424876123093533"><a name="p1424876123093533"></a><a name="p1424876123093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1331310197093533"><a name="p1331310197093533"></a><a name="p1331310197093533"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row198976664093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p375059543093533"><a name="p375059543093533"></a><a name="p375059543093533"></a><a href="Graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687123967093533"><a name="p1687123967093533"></a><a name="p1687123967093533"></a>void&nbsp;</p>
<p id="p1471919527093533"><a name="p1471919527093533"></a><a name="p1471919527093533"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1189945513093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1384503337093533"><a name="p1384503337093533"></a><a name="p1384503337093533"></a><a href="Graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748330564093533"><a name="p748330564093533"></a><a name="p748330564093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p264357492093533"><a name="p264357492093533"></a><a name="p264357492093533"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row708024339093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1419579168093533"><a name="p1419579168093533"></a><a name="p1419579168093533"></a><a href="Graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1864436554093533"><a name="p1864436554093533"></a><a name="p1864436554093533"></a>void&nbsp;</p>
<p id="p1389377958093533"><a name="p1389377958093533"></a><a name="p1389377958093533"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row1282609368093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1227674946093533"><a name="p1227674946093533"></a><a name="p1227674946093533"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p324146862093533"><a name="p324146862093533"></a><a name="p324146862093533"></a>&nbsp;</p>
<p id="p1180450200093533"><a name="p1180450200093533"></a><a name="p1180450200093533"></a>A default constructor used to create an <strong id="b1475862977093533"><a name="b1475862977093533"></a><a name="b1475862977093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1715478458093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2076649038093533"><a name="p2076649038093533"></a><a name="p2076649038093533"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904639706093533"><a name="p904639706093533"></a><a name="p904639706093533"></a>&nbsp;</p>
<p id="p2078541438093533"><a name="p2078541438093533"></a><a name="p2078541438093533"></a>A constructor used to create an <strong id="b1889708882093533"><a name="b1889708882093533"></a><a name="b1889708882093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1960938198093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1312145907093533"><a name="p1312145907093533"></a><a name="p1312145907093533"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1922121622093533"><a name="p1922121622093533"></a><a name="p1922121622093533"></a>virtual&nbsp;</p>
<p id="p928666588093533"><a name="p928666588093533"></a><a name="p928666588093533"></a>A destructor used to delete the <strong id="b906083289093533"><a name="b906083289093533"></a><a name="b906083289093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row696885280093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1199379142093533"><a name="p1199379142093533"></a><a name="p1199379142093533"></a><a href="Graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369846314093533"><a name="p369846314093533"></a><a name="p369846314093533"></a>virtual bool&nbsp;</p>
<p id="p1235687144093533"><a name="p1235687144093533"></a><a name="p1235687144093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1465384341093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1166718048093533"><a name="p1166718048093533"></a><a name="p1166718048093533"></a><a href="Graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2048709463093533"><a name="p2048709463093533"></a><a name="p2048709463093533"></a>virtual void&nbsp;</p>
<p id="p1786837081093533"><a name="p1786837081093533"></a><a name="p1786837081093533"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1172744873093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1278887571093533"><a name="p1278887571093533"></a><a name="p1278887571093533"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2105644320093533"><a name="p2105644320093533"></a><a name="p2105644320093533"></a>virtual void&nbsp;</p>
<p id="p805654234093533"><a name="p805654234093533"></a><a name="p805654234093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row786422910093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1638342480093533"><a name="p1638342480093533"></a><a name="p1638342480093533"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1712857286093533"><a name="p1712857286093533"></a><a name="p1712857286093533"></a>virtual void&nbsp;</p>
<p id="p598366169093533"><a name="p598366169093533"></a><a name="p598366169093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1619779030093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1513610998093533"><a name="p1513610998093533"></a><a name="p1513610998093533"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p970621837093533"><a name="p970621837093533"></a><a name="p970621837093533"></a>void&nbsp;</p>
<p id="p1785937241093533"><a name="p1785937241093533"></a><a name="p1785937241093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row584864480093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p210516897093533"><a name="p210516897093533"></a><a name="p210516897093533"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p911305085093533"><a name="p911305085093533"></a><a name="p911305085093533"></a>void&nbsp;</p>
<p id="p694706119093533"><a name="p694706119093533"></a><a name="p694706119093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row516350690093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p752358052093533"><a name="p752358052093533"></a><a name="p752358052093533"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p413305252093533"><a name="p413305252093533"></a><a name="p413305252093533"></a>virtual bool&nbsp;</p>
<p id="p948984228093533"><a name="p948984228093533"></a><a name="p948984228093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1896906449093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1924723698093533"><a name="p1924723698093533"></a><a name="p1924723698093533"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932112580093533"><a name="p1932112580093533"></a><a name="p1932112580093533"></a>virtual bool&nbsp;</p>
<p id="p727606447093533"><a name="p727606447093533"></a><a name="p727606447093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1048531129093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2028728078093533"><a name="p2028728078093533"></a><a name="p2028728078093533"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p578503305093533"><a name="p578503305093533"></a><a name="p578503305093533"></a>virtual bool&nbsp;</p>
<p id="p1141874879093533"><a name="p1141874879093533"></a><a name="p1141874879093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row196115586093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p527392171093533"><a name="p527392171093533"></a><a name="p527392171093533"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p507926173093533"><a name="p507926173093533"></a><a name="p507926173093533"></a>virtual bool&nbsp;</p>
<p id="p241065761093533"><a name="p241065761093533"></a><a name="p241065761093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1775078862093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p432763193093533"><a name="p432763193093533"></a><a name="p432763193093533"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p402743990093533"><a name="p402743990093533"></a><a name="p402743990093533"></a>virtual void&nbsp;</p>
<p id="p1485067101093533"><a name="p1485067101093533"></a><a name="p1485067101093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row1027055947093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494260181093533"><a name="p1494260181093533"></a><a name="p1494260181093533"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1187421256093533"><a name="p1187421256093533"></a><a name="p1187421256093533"></a>virtual void&nbsp;</p>
<p id="p213085309093533"><a name="p213085309093533"></a><a name="p213085309093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1222699264093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1282810530093533"><a name="p1282810530093533"></a><a name="p1282810530093533"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1973405230093533"><a name="p1973405230093533"></a><a name="p1973405230093533"></a>virtual void&nbsp;</p>
<p id="p337599622093533"><a name="p337599622093533"></a><a name="p337599622093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row813619970093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p500038922093533"><a name="p500038922093533"></a><a name="p500038922093533"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p549644763093533"><a name="p549644763093533"></a><a name="p549644763093533"></a>virtual void&nbsp;</p>
<p id="p1411665962093533"><a name="p1411665962093533"></a><a name="p1411665962093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row1343728274093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2023742902093533"><a name="p2023742902093533"></a><a name="p2023742902093533"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1099444231093533"><a name="p1099444231093533"></a><a name="p1099444231093533"></a>void&nbsp;</p>
<p id="p196420655093533"><a name="p196420655093533"></a><a name="p196420655093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1537848443093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p414249576093533"><a name="p414249576093533"></a><a name="p414249576093533"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2051760712093533"><a name="p2051760712093533"></a><a name="p2051760712093533"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p982557966093533"><a name="p982557966093533"></a><a name="p982557966093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1477642804093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2137253912093533"><a name="p2137253912093533"></a><a name="p2137253912093533"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p207843084093533"><a name="p207843084093533"></a><a name="p207843084093533"></a>void&nbsp;</p>
<p id="p1115363446093533"><a name="p1115363446093533"></a><a name="p1115363446093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1919328871093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p519079680093533"><a name="p519079680093533"></a><a name="p519079680093533"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p721942487093533"><a name="p721942487093533"></a><a name="p721942487093533"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p70630739093533"><a name="p70630739093533"></a><a name="p70630739093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row2137827673093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p213490586093533"><a name="p213490586093533"></a><a name="p213490586093533"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1225985004093533"><a name="p1225985004093533"></a><a name="p1225985004093533"></a>void&nbsp;</p>
<p id="p133322776093533"><a name="p133322776093533"></a><a name="p133322776093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1744697965093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106891811093533"><a name="p2106891811093533"></a><a name="p2106891811093533"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1319951870093533"><a name="p1319951870093533"></a><a name="p1319951870093533"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p937173216093533"><a name="p937173216093533"></a><a name="p937173216093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1146922900093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1439935450093533"><a name="p1439935450093533"></a><a name="p1439935450093533"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p495179052093533"><a name="p495179052093533"></a><a name="p495179052093533"></a>void&nbsp;</p>
<p id="p1932882335093533"><a name="p1932882335093533"></a><a name="p1932882335093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1605083111093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p463431068093533"><a name="p463431068093533"></a><a name="p463431068093533"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p612790329093533"><a name="p612790329093533"></a><a name="p612790329093533"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p475885936093533"><a name="p475885936093533"></a><a name="p475885936093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row241404334093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1658769040093533"><a name="p1658769040093533"></a><a name="p1658769040093533"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1003154748093533"><a name="p1003154748093533"></a><a name="p1003154748093533"></a>void&nbsp;</p>
<p id="p866440891093533"><a name="p866440891093533"></a><a name="p866440891093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row175157662093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1089173027093533"><a name="p1089173027093533"></a><a name="p1089173027093533"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846493493093533"><a name="p846493493093533"></a><a name="p846493493093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1966647337093533"><a name="p1966647337093533"></a><a name="p1966647337093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1659962164093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p321882830093533"><a name="p321882830093533"></a><a name="p321882830093533"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1740528943093533"><a name="p1740528943093533"></a><a name="p1740528943093533"></a>void&nbsp;</p>
<p id="p1774424750093533"><a name="p1774424750093533"></a><a name="p1774424750093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row61025441093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1545644435093533"><a name="p1545644435093533"></a><a name="p1545644435093533"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9087265093533"><a name="p9087265093533"></a><a name="p9087265093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1761683907093533"><a name="p1761683907093533"></a><a name="p1761683907093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1797330953093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p226050976093533"><a name="p226050976093533"></a><a name="p226050976093533"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p107411387093533"><a name="p107411387093533"></a><a name="p107411387093533"></a>virtual void&nbsp;</p>
<p id="p938139344093533"><a name="p938139344093533"></a><a name="p938139344093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1052435887093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p468195291093533"><a name="p468195291093533"></a><a name="p468195291093533"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1823190063093533"><a name="p1823190063093533"></a><a name="p1823190063093533"></a>bool&nbsp;</p>
<p id="p352401344093533"><a name="p352401344093533"></a><a name="p352401344093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1766940688093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p904924194093533"><a name="p904924194093533"></a><a name="p904924194093533"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p375620120093533"><a name="p375620120093533"></a><a name="p375620120093533"></a>void&nbsp;</p>
<p id="p1845681138093533"><a name="p1845681138093533"></a><a name="p1845681138093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row942742806093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p152798121093533"><a name="p152798121093533"></a><a name="p152798121093533"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1625697674093533"><a name="p1625697674093533"></a><a name="p1625697674093533"></a>bool&nbsp;</p>
<p id="p1474122760093533"><a name="p1474122760093533"></a><a name="p1474122760093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row2130885511093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793297039093533"><a name="p793297039093533"></a><a name="p793297039093533"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p371165832093533"><a name="p371165832093533"></a><a name="p371165832093533"></a>void&nbsp;</p>
<p id="p1309438164093533"><a name="p1309438164093533"></a><a name="p1309438164093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row2070083041093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1068736590093533"><a name="p1068736590093533"></a><a name="p1068736590093533"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p208004722093533"><a name="p208004722093533"></a><a name="p208004722093533"></a>bool&nbsp;</p>
<p id="p839005329093533"><a name="p839005329093533"></a><a name="p839005329093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row827561912093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1610209119093533"><a name="p1610209119093533"></a><a name="p1610209119093533"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p522500354093533"><a name="p522500354093533"></a><a name="p522500354093533"></a>void&nbsp;</p>
<p id="p262074046093533"><a name="p262074046093533"></a><a name="p262074046093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1448732150093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1587196990093533"><a name="p1587196990093533"></a><a name="p1587196990093533"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p705708307093533"><a name="p705708307093533"></a><a name="p705708307093533"></a>bool&nbsp;</p>
<p id="p988718147093533"><a name="p988718147093533"></a><a name="p988718147093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1903064833093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1378407117093533"><a name="p1378407117093533"></a><a name="p1378407117093533"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2095786548093533"><a name="p2095786548093533"></a><a name="p2095786548093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1845820189093533"><a name="p1845820189093533"></a><a name="p1845820189093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1494853104093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p93632335093533"><a name="p93632335093533"></a><a name="p93632335093533"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p976672944093533"><a name="p976672944093533"></a><a name="p976672944093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1959550609093533"><a name="p1959550609093533"></a><a name="p1959550609093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row900662683093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149637953093533"><a name="p1149637953093533"></a><a name="p1149637953093533"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2039313935093533"><a name="p2039313935093533"></a><a name="p2039313935093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p582534248093533"><a name="p582534248093533"></a><a name="p582534248093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row991019402093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1358821958093533"><a name="p1358821958093533"></a><a name="p1358821958093533"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p803198726093533"><a name="p803198726093533"></a><a name="p803198726093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1472052488093533"><a name="p1472052488093533"></a><a name="p1472052488093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1320125163093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p729661116093533"><a name="p729661116093533"></a><a name="p729661116093533"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p806856102093533"><a name="p806856102093533"></a><a name="p806856102093533"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p738979256093533"><a name="p738979256093533"></a><a name="p738979256093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row450979521093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p739589795093533"><a name="p739589795093533"></a><a name="p739589795093533"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p873650588093533"><a name="p873650588093533"></a><a name="p873650588093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1360193012093533"><a name="p1360193012093533"></a><a name="p1360193012093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1488150841093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p491027113093533"><a name="p491027113093533"></a><a name="p491027113093533"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1317059633093533"><a name="p1317059633093533"></a><a name="p1317059633093533"></a>void&nbsp;</p>
<p id="p1439041480093533"><a name="p1439041480093533"></a><a name="p1439041480093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row942113020093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p799140414093533"><a name="p799140414093533"></a><a name="p799140414093533"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1635160785093533"><a name="p1635160785093533"></a><a name="p1635160785093533"></a>virtual void&nbsp;</p>
<p id="p1421793550093533"><a name="p1421793550093533"></a><a name="p1421793550093533"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1783850605093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p668259368093533"><a name="p668259368093533"></a><a name="p668259368093533"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1823665696093533"><a name="p1823665696093533"></a><a name="p1823665696093533"></a>virtual int16_t&nbsp;</p>
<p id="p209814808093533"><a name="p209814808093533"></a><a name="p209814808093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row2127656755093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p799208975093533"><a name="p799208975093533"></a><a name="p799208975093533"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p242559557093533"><a name="p242559557093533"></a><a name="p242559557093533"></a>virtual void&nbsp;</p>
<p id="p1989162362093533"><a name="p1989162362093533"></a><a name="p1989162362093533"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row142267032093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1817907335093533"><a name="p1817907335093533"></a><a name="p1817907335093533"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267713901093533"><a name="p267713901093533"></a><a name="p267713901093533"></a>virtual int16_t&nbsp;</p>
<p id="p1627805769093533"><a name="p1627805769093533"></a><a name="p1627805769093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1094108167093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p172769979093533"><a name="p172769979093533"></a><a name="p172769979093533"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p431384187093533"><a name="p431384187093533"></a><a name="p431384187093533"></a>virtual void&nbsp;</p>
<p id="p454727974093533"><a name="p454727974093533"></a><a name="p454727974093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1192055255093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p941893150093533"><a name="p941893150093533"></a><a name="p941893150093533"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773563719093533"><a name="p773563719093533"></a><a name="p773563719093533"></a>virtual void&nbsp;</p>
<p id="p1776654034093533"><a name="p1776654034093533"></a><a name="p1776654034093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row493876117093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973575748093533"><a name="p973575748093533"></a><a name="p973575748093533"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1142821724093533"><a name="p1142821724093533"></a><a name="p1142821724093533"></a>int16_t&nbsp;</p>
<p id="p677138570093533"><a name="p677138570093533"></a><a name="p677138570093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1857190905093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p155158826093533"><a name="p155158826093533"></a><a name="p155158826093533"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1565257962093533"><a name="p1565257962093533"></a><a name="p1565257962093533"></a>virtual void&nbsp;</p>
<p id="p618098792093533"><a name="p618098792093533"></a><a name="p618098792093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1937848467093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p291520290093533"><a name="p291520290093533"></a><a name="p291520290093533"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p627092538093533"><a name="p627092538093533"></a><a name="p627092538093533"></a>int16_t&nbsp;</p>
<p id="p659350238093533"><a name="p659350238093533"></a><a name="p659350238093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1545022498093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p245745454093533"><a name="p245745454093533"></a><a name="p245745454093533"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p634363200093533"><a name="p634363200093533"></a><a name="p634363200093533"></a>virtual void&nbsp;</p>
<p id="p1988447513093533"><a name="p1988447513093533"></a><a name="p1988447513093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1343206756093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1760681859093533"><a name="p1760681859093533"></a><a name="p1760681859093533"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1096038726093533"><a name="p1096038726093533"></a><a name="p1096038726093533"></a>virtual void&nbsp;</p>
<p id="p445284180093533"><a name="p445284180093533"></a><a name="p445284180093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1072254666093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p182551722093533"><a name="p182551722093533"></a><a name="p182551722093533"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1392191957093533"><a name="p1392191957093533"></a><a name="p1392191957093533"></a>bool&nbsp;</p>
<p id="p1437298948093533"><a name="p1437298948093533"></a><a name="p1437298948093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row641189586093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p76687728093533"><a name="p76687728093533"></a><a name="p76687728093533"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2140779593093533"><a name="p2140779593093533"></a><a name="p2140779593093533"></a>void&nbsp;</p>
<p id="p1793016011093533"><a name="p1793016011093533"></a><a name="p1793016011093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row220420225093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p301249337093533"><a name="p301249337093533"></a><a name="p301249337093533"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1997296260093533"><a name="p1997296260093533"></a><a name="p1997296260093533"></a>void&nbsp;</p>
<p id="p1313363993093533"><a name="p1313363993093533"></a><a name="p1313363993093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row2055927252093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872149147093533"><a name="p1872149147093533"></a><a name="p1872149147093533"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p69086648093533"><a name="p69086648093533"></a><a name="p69086648093533"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p444638734093533"><a name="p444638734093533"></a><a name="p444638734093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1542570618093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p783487888093533"><a name="p783487888093533"></a><a name="p783487888093533"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2289074093533"><a name="p2289074093533"></a><a name="p2289074093533"></a>void&nbsp;</p>
<p id="p2075146498093533"><a name="p2075146498093533"></a><a name="p2075146498093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row944692377093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1966260338093533"><a name="p1966260338093533"></a><a name="p1966260338093533"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748309320093533"><a name="p748309320093533"></a><a name="p748309320093533"></a>const char *&nbsp;</p>
<p id="p1360059522093533"><a name="p1360059522093533"></a><a name="p1360059522093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row784530164093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p554769202093533"><a name="p554769202093533"></a><a name="p554769202093533"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p528459449093533"><a name="p528459449093533"></a><a name="p528459449093533"></a>void&nbsp;</p>
<p id="p641733512093533"><a name="p641733512093533"></a><a name="p641733512093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1045034232093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1271436010093533"><a name="p1271436010093533"></a><a name="p1271436010093533"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p805953406093533"><a name="p805953406093533"></a><a name="p805953406093533"></a>int16_t&nbsp;</p>
<p id="p360630843093533"><a name="p360630843093533"></a><a name="p360630843093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1616289826093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2037507762093533"><a name="p2037507762093533"></a><a name="p2037507762093533"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1221857660093533"><a name="p1221857660093533"></a><a name="p1221857660093533"></a>virtual void&nbsp;</p>
<p id="p1110409843093533"><a name="p1110409843093533"></a><a name="p1110409843093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row772082552093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p295905456093533"><a name="p295905456093533"></a><a name="p295905456093533"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2002111095093533"><a name="p2002111095093533"></a><a name="p2002111095093533"></a>void&nbsp;</p>
<p id="p676271976093533"><a name="p676271976093533"></a><a name="p676271976093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row175056907093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1273309072093533"><a name="p1273309072093533"></a><a name="p1273309072093533"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1005881507093533"><a name="p1005881507093533"></a><a name="p1005881507093533"></a>void&nbsp;</p>
<p id="p1856470495093533"><a name="p1856470495093533"></a><a name="p1856470495093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row733413509093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1437061245093533"><a name="p1437061245093533"></a><a name="p1437061245093533"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1933153204093533"><a name="p1933153204093533"></a><a name="p1933153204093533"></a>void&nbsp;</p>
<p id="p964423447093533"><a name="p964423447093533"></a><a name="p964423447093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row856932972093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1633698985093533"><a name="p1633698985093533"></a><a name="p1633698985093533"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1243535812093533"><a name="p1243535812093533"></a><a name="p1243535812093533"></a>void&nbsp;</p>
<p id="p924941856093533"><a name="p924941856093533"></a><a name="p924941856093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1670087968093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1367906779093533"><a name="p1367906779093533"></a><a name="p1367906779093533"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1966228841093533"><a name="p1966228841093533"></a><a name="p1966228841093533"></a>void&nbsp;</p>
<p id="p1937712863093533"><a name="p1937712863093533"></a><a name="p1937712863093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1763449205093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1636783713093533"><a name="p1636783713093533"></a><a name="p1636783713093533"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p844969051093533"><a name="p844969051093533"></a><a name="p844969051093533"></a>void&nbsp;</p>
<p id="p852403206093533"><a name="p852403206093533"></a><a name="p852403206093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1634299192093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1050652457093533"><a name="p1050652457093533"></a><a name="p1050652457093533"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1303742223093533"><a name="p1303742223093533"></a><a name="p1303742223093533"></a>void&nbsp;</p>
<p id="p1819911469093533"><a name="p1819911469093533"></a><a name="p1819911469093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1017059347093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1681328593093533"><a name="p1681328593093533"></a><a name="p1681328593093533"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773909108093533"><a name="p773909108093533"></a><a name="p773909108093533"></a>void&nbsp;</p>
<p id="p1086943370093533"><a name="p1086943370093533"></a><a name="p1086943370093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row191056130093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p83454176093533"><a name="p83454176093533"></a><a name="p83454176093533"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2079090389093533"><a name="p2079090389093533"></a><a name="p2079090389093533"></a>void&nbsp;</p>
<p id="p1674809339093533"><a name="p1674809339093533"></a><a name="p1674809339093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1608971191093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2102760518093533"><a name="p2102760518093533"></a><a name="p2102760518093533"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466521487093533"><a name="p1466521487093533"></a><a name="p1466521487093533"></a>void&nbsp;</p>
<p id="p814863583093533"><a name="p814863583093533"></a><a name="p814863583093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row440046831093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p667748520093533"><a name="p667748520093533"></a><a name="p667748520093533"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1271327991093533"><a name="p1271327991093533"></a><a name="p1271327991093533"></a>void&nbsp;</p>
<p id="p74781204093533"><a name="p74781204093533"></a><a name="p74781204093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1403060814093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1876787192093533"><a name="p1876787192093533"></a><a name="p1876787192093533"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1924535450093533"><a name="p1924535450093533"></a><a name="p1924535450093533"></a>void&nbsp;</p>
<p id="p776634603093533"><a name="p776634603093533"></a><a name="p776634603093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1974057475093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401136677093533"><a name="p1401136677093533"></a><a name="p1401136677093533"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699751257093533"><a name="p1699751257093533"></a><a name="p1699751257093533"></a>void&nbsp;</p>
<p id="p11743978093533"><a name="p11743978093533"></a><a name="p11743978093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row743568081093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1653899398093533"><a name="p1653899398093533"></a><a name="p1653899398093533"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p218901581093533"><a name="p218901581093533"></a><a name="p218901581093533"></a>void&nbsp;</p>
<p id="p62703224093533"><a name="p62703224093533"></a><a name="p62703224093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row483779658093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106519587093533"><a name="p2106519587093533"></a><a name="p2106519587093533"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p793046036093533"><a name="p793046036093533"></a><a name="p793046036093533"></a>void&nbsp;</p>
<p id="p2126110029093533"><a name="p2126110029093533"></a><a name="p2126110029093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row220827335093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p489147619093533"><a name="p489147619093533"></a><a name="p489147619093533"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1232553112093533"><a name="p1232553112093533"></a><a name="p1232553112093533"></a>virtual void&nbsp;</p>
<p id="p1850277429093533"><a name="p1850277429093533"></a><a name="p1850277429093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1419200778093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1284690157093533"><a name="p1284690157093533"></a><a name="p1284690157093533"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p219670591093533"><a name="p219670591093533"></a><a name="p219670591093533"></a>virtual void&nbsp;</p>
<p id="p51125597093533"><a name="p51125597093533"></a><a name="p51125597093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1659206585093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p29408673093533"><a name="p29408673093533"></a><a name="p29408673093533"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p579088137093533"><a name="p579088137093533"></a><a name="p579088137093533"></a>virtual int64_t&nbsp;</p>
<p id="p787103125093533"><a name="p787103125093533"></a><a name="p787103125093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1414573666093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p927622307093533"><a name="p927622307093533"></a><a name="p927622307093533"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1081942570093533"><a name="p1081942570093533"></a><a name="p1081942570093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1550956978093533"><a name="p1550956978093533"></a><a name="p1550956978093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1026652234093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p72297871093533"><a name="p72297871093533"></a><a name="p72297871093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p378660244093533"><a name="p378660244093533"></a><a name="p378660244093533"></a>void *&nbsp;</p>
<p id="p1858798754093533"><a name="p1858798754093533"></a><a name="p1858798754093533"></a>Overrides the <strong id="b1272816010093533"><a name="b1272816010093533"></a><a name="b1272816010093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row161183866093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1544701865093533"><a name="p1544701865093533"></a><a name="p1544701865093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1841170393093533"><a name="p1841170393093533"></a><a name="p1841170393093533"></a>void&nbsp;</p>
<p id="p1672709571093533"><a name="p1672709571093533"></a><a name="p1672709571093533"></a>Overrides the <strong id="b1344046792093533"><a name="b1344046792093533"></a><a name="b1344046792093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Attributes<a name="pub-static-attribs"></a>

<a name="table1742436434093533"></a>
<table><thead align="left"><tr id="row54279241093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1791347584093533"><a name="p1791347584093533"></a><a name="p1791347584093533"></a>Static Public Attribute Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2095993625093533"><a name="p2095993625093533"></a><a name="p2095993625093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1064264866093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p292731734093533"><a name="p292731734093533"></a><a name="p292731734093533"></a><a href="Graphic.md#ga7f433b8551722451f880e7fa05731a2f">ONE_MINUTE_IN_SECOND</a> = 60</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1948137143093533"><a name="p1948137143093533"></a><a name="p1948137143093533"></a>Represents 60 seconds per minute. </p>
</td>
</tr>
<tr id="row433064721093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p778319597093533"><a name="p778319597093533"></a><a name="p778319597093533"></a><a href="Graphic.md#ga5434b911b6f7e0637ac0626c9dd0f513">ONE_HOUR_IN_MINUTE</a> = 60</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121104215093533"><a name="p1121104215093533"></a><a name="p1121104215093533"></a>Represents 60 minutes per hour. </p>
</td>
</tr>
<tr id="row432746036093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p368554682093533"><a name="p368554682093533"></a><a name="p368554682093533"></a><a href="Graphic.md#gae7742f1e715885ecc4f5b67d57530319">ONE_DAY_IN_HOUR</a> = 24</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1375464004093533"><a name="p1375464004093533"></a><a name="p1375464004093533"></a>Represents 24 hours per day. </p>
</td>
</tr>
<tr id="row1354446945093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p523205055093533"><a name="p523205055093533"></a><a name="p523205055093533"></a><a href="Graphic.md#gae40a5ae3834b626e2976fab83f166171">HALF_DAY_IN_HOUR</a> = 12</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p374950392093533"><a name="p374950392093533"></a><a name="p374950392093533"></a>Represents 12 hours every half day. </p>
</td>
</tr>
</tbody>
</table>

## Protected Attributes<a name="pro-attribs"></a>

<a name="table1225602036093533"></a>
<table><thead align="left"><tr id="row1645762301093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1563614948093533"><a name="p1563614948093533"></a><a name="p1563614948093533"></a>Protected Attribute Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p907222949093533"><a name="p907222949093533"></a><a name="p907222949093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row637404839093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p522489418093533"><a name="p522489418093533"></a><a name="p522489418093533"></a><a href="Graphic.md#gaabfbbb277dabf5477c628336a429f8ad">currentHour_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1376292165093533"><a name="p1376292165093533"></a><a name="p1376292165093533"></a>Represents the current number of hours. </p>
</td>
</tr>
<tr id="row1893312395093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p667855578093533"><a name="p667855578093533"></a><a name="p667855578093533"></a><a href="Graphic.md#ga34c3518c0dc9f35fc77b240b6f8d0dcb">currentMinute_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681022378093533"><a name="p1681022378093533"></a><a name="p1681022378093533"></a>Represents the current number of minutes. </p>
</td>
</tr>
<tr id="row430777617093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p474074634093533"><a name="p474074634093533"></a><a name="p474074634093533"></a><a href="Graphic.md#ga5b2749cdc5e52551731923d8268b8d5d">currentSecond_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1456471381093533"><a name="p1456471381093533"></a><a name="p1456471381093533"></a>Represents the current number of seconds. </p>
</td>
</tr>
<tr id="row263774063093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2928602093533"><a name="p2928602093533"></a><a name="p2928602093533"></a><a href="Graphic.md#gab08c7c490a5b42fcdee04d45b5521d1c">mode_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1666433507093533"><a name="p1666433507093533"></a><a name="p1666433507093533"></a>Represents the current working mode of this clock. </p>
</td>
</tr>
<tr id="row2105642853093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p562115293093533"><a name="p562115293093533"></a><a name="p562115293093533"></a><a href="Graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p59629640093533"><a name="p59629640093533"></a><a name="p59629640093533"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row683731064093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2129281936093533"><a name="p2129281936093533"></a><a name="p2129281936093533"></a><a href="Graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p308553332093533"><a name="p308553332093533"></a><a name="p308553332093533"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row1485836488093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p623072516093533"><a name="p623072516093533"></a><a name="p623072516093533"></a><a href="Graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p502844322093533"><a name="p502844322093533"></a><a name="p502844322093533"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row939041030093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p788919924093533"><a name="p788919924093533"></a><a name="p788919924093533"></a><a href="Graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1997942127093533"><a name="p1997942127093533"></a><a name="p1997942127093533"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row374608401093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p564331184093533"><a name="p564331184093533"></a><a name="p564331184093533"></a><a href="Graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p776599990093533"><a name="p776599990093533"></a><a name="p776599990093533"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row174874568093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242891351093533"><a name="p1242891351093533"></a><a name="p1242891351093533"></a><a href="Graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1765682296093533"><a name="p1765682296093533"></a><a name="p1765682296093533"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table243240828093533"></a>
<table><thead align="left"><tr id="row81396923093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1747255059093533"><a name="p1747255059093533"></a><a name="p1747255059093533"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p999118159093533"><a name="p999118159093533"></a><a name="p999118159093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2036765856093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p726104351093533"><a name="p726104351093533"></a><a name="p726104351093533"></a><a href="Graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1734787405093533"><a name="p1734787405093533"></a><a name="p1734787405093533"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1343911981093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p839364683093533"><a name="p839364683093533"></a><a name="p839364683093533"></a><a href="Graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p829018313093533"><a name="p829018313093533"></a><a name="p829018313093533"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
</tbody>
</table>

