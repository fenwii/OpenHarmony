# OHOS::UIYAxis<a name="ZH-CN_TOPIC_0000001054879554"></a>

## **Overview**<a name="section1877928493093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines the unique attributes and functions for the y-axis. This class is used in  [UIChart](OHOS-UIChart.md). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1172361991093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table511894021093533"></a>
<table><thead align="left"><tr id="row1878511084093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p761454150093533"><a name="p761454150093533"></a><a name="p761454150093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1182797144093533"><a name="p1182797144093533"></a><a name="p1182797144093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1699747042093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p94909177093533"><a name="p94909177093533"></a><a name="p94909177093533"></a><a href="Graphic.md#ga0f9a52b48bcd8170b4a64a891a88fb5c">UIYAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1943873054093533"><a name="p1943873054093533"></a><a name="p1943873054093533"></a>&nbsp;</p>
<p id="p857196958093533"><a name="p857196958093533"></a><a name="p857196958093533"></a>A constructor used to create a <strong id="b373156067093533"><a name="b373156067093533"></a><a name="b373156067093533"></a><a href="OHOS-UIYAxis.md">UIYAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row874597144093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p180791602093533"><a name="p180791602093533"></a><a name="p180791602093533"></a><a href="Graphic.md#ga0dc204e8a15fa66762af58142552557c">~UIYAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2025194469093533"><a name="p2025194469093533"></a><a name="p2025194469093533"></a>virtual&nbsp;</p>
<p id="p895242141093533"><a name="p895242141093533"></a><a name="p895242141093533"></a>A destructor used to delete the <strong id="b220783746093533"><a name="b220783746093533"></a><a name="b220783746093533"></a><a href="OHOS-UIYAxis.md">UIYAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row1937090205093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p414202680093533"><a name="p414202680093533"></a><a name="p414202680093533"></a><a href="Graphic.md#gae70c8c411116746a2ab73a6f9bbd1233">TranslateToPixel</a> (int16_t &amp;value) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p871733153093533"><a name="p871733153093533"></a><a name="p871733153093533"></a>void&nbsp;</p>
<p id="p1587362722093533"><a name="p1587362722093533"></a><a name="p1587362722093533"></a>Translates data into the y coordinate of a pixel. </p>
</td>
</tr>
<tr id="row1253414491093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1479916609093533"><a name="p1479916609093533"></a><a name="p1479916609093533"></a><a href="Graphic.md#gae635d27e0a4eba30002e3607c42b914a">SetDataRange</a> (uint16_t min, uint16_t max) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p511837970093533"><a name="p511837970093533"></a><a name="p511837970093533"></a>bool&nbsp;</p>
<p id="p829552020093533"><a name="p829552020093533"></a><a name="p829552020093533"></a>Sets the value range of the y-axis. </p>
</td>
</tr>
<tr id="row1901225967093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1028473270093533"><a name="p1028473270093533"></a><a name="p1028473270093533"></a><a href="Graphic.md#gaf67c1b25c1d1a3ba694cb47f7e9fda85">SetMarkNum</a> (uint16_t count) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p325258070093533"><a name="p325258070093533"></a><a name="p325258070093533"></a>void&nbsp;</p>
<p id="p2079606314093533"><a name="p2079606314093533"></a><a name="p2079606314093533"></a>Sets the number of scales on the Y axis. </p>
</td>
</tr>
<tr id="row1209201211093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1048129846093533"><a name="p1048129846093533"></a><a name="p1048129846093533"></a><a href="Graphic.md#gad79f1c694abce57af451b8f7b0b17c35">UIAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96668854093533"><a name="p96668854093533"></a><a name="p96668854093533"></a>&nbsp;</p>
<p id="p465772175093533"><a name="p465772175093533"></a><a name="p465772175093533"></a>A constructor used to create a <strong id="b1964628293093533"><a name="b1964628293093533"></a><a name="b1964628293093533"></a><a href="OHOS-UIAxis.md">UIAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row2115661994093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1597508215093533"><a name="p1597508215093533"></a><a name="p1597508215093533"></a><a href="Graphic.md#gaacc9ac178b3b235f1186297021eb98d8">~UIAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1824445288093533"><a name="p1824445288093533"></a><a name="p1824445288093533"></a>virtual&nbsp;</p>
<p id="p1939228363093533"><a name="p1939228363093533"></a><a name="p1939228363093533"></a>A destructor used to delete the <strong id="b1009048236093533"><a name="b1009048236093533"></a><a name="b1009048236093533"></a><a href="OHOS-UIAxis.md">UIAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row16680348093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1275290741093533"><a name="p1275290741093533"></a><a name="p1275290741093533"></a><a href="Graphic.md#ga2f46b702f1543c5076a8957a94a780d3">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p128533423093533"><a name="p128533423093533"></a><a name="p128533423093533"></a>UIViewType&nbsp;</p>
<p id="p794558877093533"><a name="p794558877093533"></a><a name="p794558877093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row2068553742093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1779392336093533"><a name="p1779392336093533"></a><a name="p1779392336093533"></a><a href="Graphic.md#ga8ceec5e67fa2c4f161bd9af1f0788bbe">SetLineColor</a> (const <a href="OHOS-Color32.md">ColorType</a> &amp;color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p948197306093533"><a name="p948197306093533"></a><a name="p948197306093533"></a>void&nbsp;</p>
<p id="p1943305142093533"><a name="p1943305142093533"></a><a name="p1943305142093533"></a>Sets the line color of the coordinate axis. </p>
</td>
</tr>
<tr id="row1932178463093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p334146786093533"><a name="p334146786093533"></a><a name="p334146786093533"></a><a href="Graphic.md#ga5360803f425055de52af5f7fa1081cfe">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1356293252093533"><a name="p1356293252093533"></a><a name="p1356293252093533"></a>void&nbsp;</p>
<p id="p2065767151093533"><a name="p2065767151093533"></a><a name="p2065767151093533"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row148482658093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381317404093533"><a name="p381317404093533"></a><a name="p381317404093533"></a><a href="Graphic.md#gad1bf4d83270c0a4ba04f3cffbc67bb97">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p656220353093533"><a name="p656220353093533"></a><a name="p656220353093533"></a>bool&nbsp;</p>
<p id="p208406842093533"><a name="p208406842093533"></a><a name="p208406842093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1599837201093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p519031755093533"><a name="p519031755093533"></a><a name="p519031755093533"></a><a href="Graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2080960384093533"><a name="p2080960384093533"></a><a name="p2080960384093533"></a>&nbsp;</p>
<p id="p1254900247093533"><a name="p1254900247093533"></a><a name="p1254900247093533"></a>A default constructor used to create a <strong id="b1275956936093533"><a name="b1275956936093533"></a><a name="b1275956936093533"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row707281613093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589818400093533"><a name="p589818400093533"></a><a name="p589818400093533"></a><a href="Graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1085919066093533"><a name="p1085919066093533"></a><a name="p1085919066093533"></a>virtual&nbsp;</p>
<p id="p2090362215093533"><a name="p2090362215093533"></a><a name="p2090362215093533"></a>A destructor used to delete the <strong id="b1203654598093533"><a name="b1203654598093533"></a><a name="b1203654598093533"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row152439126093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1373968458093533"><a name="p1373968458093533"></a><a name="p1373968458093533"></a><a href="Graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1127467665093533"><a name="p1127467665093533"></a><a name="p1127467665093533"></a>UIViewType&nbsp;</p>
<p id="p451597049093533"><a name="p451597049093533"></a><a name="p451597049093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row276974302093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2040987951093533"><a name="p2040987951093533"></a><a name="p2040987951093533"></a><a href="Graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1014243144093533"><a name="p1014243144093533"></a><a name="p1014243144093533"></a>virtual void&nbsp;</p>
<p id="p303589893093533"><a name="p303589893093533"></a><a name="p303589893093533"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row1780047492093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1817750677093533"><a name="p1817750677093533"></a><a name="p1817750677093533"></a><a href="Graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="OHOS-UIView.md">UIView</a> *prevView, <a href="OHOS-UIView.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p633547934093533"><a name="p633547934093533"></a><a name="p633547934093533"></a>virtual void&nbsp;</p>
<p id="p1128380801093533"><a name="p1128380801093533"></a><a name="p1128380801093533"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1431123103093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p223929093093533"><a name="p223929093093533"></a><a name="p223929093093533"></a><a href="Graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908105134093533"><a name="p908105134093533"></a><a name="p908105134093533"></a>virtual void&nbsp;</p>
<p id="p1533259219093533"><a name="p1533259219093533"></a><a name="p1533259219093533"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row2034456364093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1268632972093533"><a name="p1268632972093533"></a><a name="p1268632972093533"></a><a href="Graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p591990305093533"><a name="p591990305093533"></a><a name="p591990305093533"></a>virtual void&nbsp;</p>
<p id="p1238016508093533"><a name="p1238016508093533"></a><a name="p1238016508093533"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1553483594093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2089546946093533"><a name="p2089546946093533"></a><a name="p2089546946093533"></a><a href="Graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1081872817093533"><a name="p1081872817093533"></a><a name="p1081872817093533"></a>virtual void&nbsp;</p>
<p id="p1878785405093533"><a name="p1878785405093533"></a><a name="p1878785405093533"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row2026926378093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p488969693093533"><a name="p488969693093533"></a><a name="p488969693093533"></a><a href="Graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1811025949093533"><a name="p1811025949093533"></a><a name="p1811025949093533"></a>virtual void&nbsp;</p>
<p id="p715656535093533"><a name="p715656535093533"></a><a name="p715656535093533"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row1399085571093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1757632728093533"><a name="p1757632728093533"></a><a name="p1757632728093533"></a><a href="Graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1623116477093533"><a name="p1623116477093533"></a><a name="p1623116477093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1880332351093533"><a name="p1880332351093533"></a><a name="p1880332351093533"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1154071129093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1021754060093533"><a name="p1021754060093533"></a><a name="p1021754060093533"></a><a href="Graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p591330130093533"><a name="p591330130093533"></a><a name="p591330130093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1644621737093533"><a name="p1644621737093533"></a><a name="p1644621737093533"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row223648934093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1576731144093533"><a name="p1576731144093533"></a><a name="p1576731144093533"></a><a href="Graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946017912093533"><a name="p1946017912093533"></a><a name="p1946017912093533"></a>void&nbsp;</p>
<p id="p224513956093533"><a name="p224513956093533"></a><a name="p224513956093533"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1518516084093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p438687122093533"><a name="p438687122093533"></a><a name="p438687122093533"></a><a href="Graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1307924614093533"><a name="p1307924614093533"></a><a name="p1307924614093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p791810146093533"><a name="p791810146093533"></a><a name="p791810146093533"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row1091484638093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p344631085093533"><a name="p344631085093533"></a><a name="p344631085093533"></a><a href="Graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1629172365093533"><a name="p1629172365093533"></a><a name="p1629172365093533"></a>void&nbsp;</p>
<p id="p1494335843093533"><a name="p1494335843093533"></a><a name="p1494335843093533"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row646224224093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1953940014093533"><a name="p1953940014093533"></a><a name="p1953940014093533"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1841108213093533"><a name="p1841108213093533"></a><a name="p1841108213093533"></a>&nbsp;</p>
<p id="p1852622878093533"><a name="p1852622878093533"></a><a name="p1852622878093533"></a>A default constructor used to create an <strong id="b1311302891093533"><a name="b1311302891093533"></a><a name="b1311302891093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1111920139093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1784248782093533"><a name="p1784248782093533"></a><a name="p1784248782093533"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1391073228093533"><a name="p1391073228093533"></a><a name="p1391073228093533"></a>&nbsp;</p>
<p id="p1319488038093533"><a name="p1319488038093533"></a><a name="p1319488038093533"></a>A constructor used to create an <strong id="b74601588093533"><a name="b74601588093533"></a><a name="b74601588093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1445114623093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p369490851093533"><a name="p369490851093533"></a><a name="p369490851093533"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p14618217093533"><a name="p14618217093533"></a><a name="p14618217093533"></a>virtual&nbsp;</p>
<p id="p221398340093533"><a name="p221398340093533"></a><a name="p221398340093533"></a>A destructor used to delete the <strong id="b2110487044093533"><a name="b2110487044093533"></a><a name="b2110487044093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1810803494093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1334820226093533"><a name="p1334820226093533"></a><a name="p1334820226093533"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833144061093533"><a name="p833144061093533"></a><a name="p833144061093533"></a>virtual void&nbsp;</p>
<p id="p1273358955093533"><a name="p1273358955093533"></a><a name="p1273358955093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row665894536093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1387441769093533"><a name="p1387441769093533"></a><a name="p1387441769093533"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1344000484093533"><a name="p1344000484093533"></a><a name="p1344000484093533"></a>virtual void&nbsp;</p>
<p id="p1627887070093533"><a name="p1627887070093533"></a><a name="p1627887070093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row2070244140093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p544502795093533"><a name="p544502795093533"></a><a name="p544502795093533"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p983468515093533"><a name="p983468515093533"></a><a name="p983468515093533"></a>void&nbsp;</p>
<p id="p1109560460093533"><a name="p1109560460093533"></a><a name="p1109560460093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1166024932093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p548565281093533"><a name="p548565281093533"></a><a name="p548565281093533"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1260861397093533"><a name="p1260861397093533"></a><a name="p1260861397093533"></a>void&nbsp;</p>
<p id="p1656332235093533"><a name="p1656332235093533"></a><a name="p1656332235093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row152654655093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p646479438093533"><a name="p646479438093533"></a><a name="p646479438093533"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1725986247093533"><a name="p1725986247093533"></a><a name="p1725986247093533"></a>virtual bool&nbsp;</p>
<p id="p479063514093533"><a name="p479063514093533"></a><a name="p479063514093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1272608167093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1361511706093533"><a name="p1361511706093533"></a><a name="p1361511706093533"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1960874036093533"><a name="p1960874036093533"></a><a name="p1960874036093533"></a>virtual bool&nbsp;</p>
<p id="p1089947866093533"><a name="p1089947866093533"></a><a name="p1089947866093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row2011707148093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2144334157093533"><a name="p2144334157093533"></a><a name="p2144334157093533"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908928117093533"><a name="p908928117093533"></a><a name="p908928117093533"></a>virtual bool&nbsp;</p>
<p id="p399117995093533"><a name="p399117995093533"></a><a name="p399117995093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row832286228093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p535335092093533"><a name="p535335092093533"></a><a name="p535335092093533"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p259087346093533"><a name="p259087346093533"></a><a name="p259087346093533"></a>virtual bool&nbsp;</p>
<p id="p218475806093533"><a name="p218475806093533"></a><a name="p218475806093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1943504098093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1066947130093533"><a name="p1066947130093533"></a><a name="p1066947130093533"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1604774250093533"><a name="p1604774250093533"></a><a name="p1604774250093533"></a>virtual void&nbsp;</p>
<p id="p2091646807093533"><a name="p2091646807093533"></a><a name="p2091646807093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row423972453093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p229301449093533"><a name="p229301449093533"></a><a name="p229301449093533"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311105860093533"><a name="p311105860093533"></a><a name="p311105860093533"></a>virtual void&nbsp;</p>
<p id="p1701997717093533"><a name="p1701997717093533"></a><a name="p1701997717093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1307234756093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1523202651093533"><a name="p1523202651093533"></a><a name="p1523202651093533"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1709669515093533"><a name="p1709669515093533"></a><a name="p1709669515093533"></a>virtual void&nbsp;</p>
<p id="p623774828093533"><a name="p623774828093533"></a><a name="p623774828093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1930378521093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1981113262093533"><a name="p1981113262093533"></a><a name="p1981113262093533"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9267816093533"><a name="p9267816093533"></a><a name="p9267816093533"></a>virtual void&nbsp;</p>
<p id="p1859154885093533"><a name="p1859154885093533"></a><a name="p1859154885093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row1837521466093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1887943548093533"><a name="p1887943548093533"></a><a name="p1887943548093533"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p499322931093533"><a name="p499322931093533"></a><a name="p499322931093533"></a>void&nbsp;</p>
<p id="p1698119712093533"><a name="p1698119712093533"></a><a name="p1698119712093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1867613666093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p284276518093533"><a name="p284276518093533"></a><a name="p284276518093533"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p249576491093533"><a name="p249576491093533"></a><a name="p249576491093533"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p2027718204093533"><a name="p2027718204093533"></a><a name="p2027718204093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row75775879093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1446974168093533"><a name="p1446974168093533"></a><a name="p1446974168093533"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226179870093533"><a name="p1226179870093533"></a><a name="p1226179870093533"></a>void&nbsp;</p>
<p id="p1894911724093533"><a name="p1894911724093533"></a><a name="p1894911724093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row821376649093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p153293469093533"><a name="p153293469093533"></a><a name="p153293469093533"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1019695355093533"><a name="p1019695355093533"></a><a name="p1019695355093533"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p1543199273093533"><a name="p1543199273093533"></a><a name="p1543199273093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1806963151093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p487135721093533"><a name="p487135721093533"></a><a name="p487135721093533"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2106135212093533"><a name="p2106135212093533"></a><a name="p2106135212093533"></a>void&nbsp;</p>
<p id="p1908184075093533"><a name="p1908184075093533"></a><a name="p1908184075093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row2068834306093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p839068224093533"><a name="p839068224093533"></a><a name="p839068224093533"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1650547987093533"><a name="p1650547987093533"></a><a name="p1650547987093533"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p791537787093533"><a name="p791537787093533"></a><a name="p791537787093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1299997306093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2042110949093533"><a name="p2042110949093533"></a><a name="p2042110949093533"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p876193523093533"><a name="p876193523093533"></a><a name="p876193523093533"></a>void&nbsp;</p>
<p id="p2108902470093533"><a name="p2108902470093533"></a><a name="p2108902470093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row86889240093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488714717093533"><a name="p1488714717093533"></a><a name="p1488714717093533"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2147345841093533"><a name="p2147345841093533"></a><a name="p2147345841093533"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p896998817093533"><a name="p896998817093533"></a><a name="p896998817093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row537685228093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1790110709093533"><a name="p1790110709093533"></a><a name="p1790110709093533"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p740963549093533"><a name="p740963549093533"></a><a name="p740963549093533"></a>void&nbsp;</p>
<p id="p1444279547093533"><a name="p1444279547093533"></a><a name="p1444279547093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1614002979093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1468861610093533"><a name="p1468861610093533"></a><a name="p1468861610093533"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1370893124093533"><a name="p1370893124093533"></a><a name="p1370893124093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p539332988093533"><a name="p539332988093533"></a><a name="p539332988093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row325943346093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p337430573093533"><a name="p337430573093533"></a><a name="p337430573093533"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459214708093533"><a name="p1459214708093533"></a><a name="p1459214708093533"></a>void&nbsp;</p>
<p id="p859562309093533"><a name="p859562309093533"></a><a name="p859562309093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1209147428093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p108870897093533"><a name="p108870897093533"></a><a name="p108870897093533"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p574092298093533"><a name="p574092298093533"></a><a name="p574092298093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p490825271093533"><a name="p490825271093533"></a><a name="p490825271093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row260597488093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1129541915093533"><a name="p1129541915093533"></a><a name="p1129541915093533"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p517725142093533"><a name="p517725142093533"></a><a name="p517725142093533"></a>virtual void&nbsp;</p>
<p id="p1114568158093533"><a name="p1114568158093533"></a><a name="p1114568158093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row705727706093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p155054236093533"><a name="p155054236093533"></a><a name="p155054236093533"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p320768708093533"><a name="p320768708093533"></a><a name="p320768708093533"></a>bool&nbsp;</p>
<p id="p1985659849093533"><a name="p1985659849093533"></a><a name="p1985659849093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1793543271093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p652028288093533"><a name="p652028288093533"></a><a name="p652028288093533"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1394292231093533"><a name="p1394292231093533"></a><a name="p1394292231093533"></a>void&nbsp;</p>
<p id="p412359149093533"><a name="p412359149093533"></a><a name="p412359149093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row2136006005093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p848320782093533"><a name="p848320782093533"></a><a name="p848320782093533"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388681570093533"><a name="p388681570093533"></a><a name="p388681570093533"></a>bool&nbsp;</p>
<p id="p568575217093533"><a name="p568575217093533"></a><a name="p568575217093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1228978349093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1022516886093533"><a name="p1022516886093533"></a><a name="p1022516886093533"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p831230187093533"><a name="p831230187093533"></a><a name="p831230187093533"></a>void&nbsp;</p>
<p id="p1301441085093533"><a name="p1301441085093533"></a><a name="p1301441085093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row402794985093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1946071623093533"><a name="p1946071623093533"></a><a name="p1946071623093533"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1502377181093533"><a name="p1502377181093533"></a><a name="p1502377181093533"></a>bool&nbsp;</p>
<p id="p1944918224093533"><a name="p1944918224093533"></a><a name="p1944918224093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1737486579093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1945177584093533"><a name="p1945177584093533"></a><a name="p1945177584093533"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p253722618093533"><a name="p253722618093533"></a><a name="p253722618093533"></a>void&nbsp;</p>
<p id="p565719268093533"><a name="p565719268093533"></a><a name="p565719268093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1856373271093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1889574813093533"><a name="p1889574813093533"></a><a name="p1889574813093533"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p302240206093533"><a name="p302240206093533"></a><a name="p302240206093533"></a>bool&nbsp;</p>
<p id="p1957808472093533"><a name="p1957808472093533"></a><a name="p1957808472093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row407433179093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1191653125093533"><a name="p1191653125093533"></a><a name="p1191653125093533"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1085453451093533"><a name="p1085453451093533"></a><a name="p1085453451093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p16623468093533"><a name="p16623468093533"></a><a name="p16623468093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1143062157093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p237936585093533"><a name="p237936585093533"></a><a name="p237936585093533"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1503808518093533"><a name="p1503808518093533"></a><a name="p1503808518093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1922102825093533"><a name="p1922102825093533"></a><a name="p1922102825093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row254724156093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p166421750093533"><a name="p166421750093533"></a><a name="p166421750093533"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p64433896093533"><a name="p64433896093533"></a><a name="p64433896093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p2035173817093533"><a name="p2035173817093533"></a><a name="p2035173817093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row819758895093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1553797276093533"><a name="p1553797276093533"></a><a name="p1553797276093533"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67784691093533"><a name="p67784691093533"></a><a name="p67784691093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1005183070093533"><a name="p1005183070093533"></a><a name="p1005183070093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1579316723093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p355887704093533"><a name="p355887704093533"></a><a name="p355887704093533"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1640326869093533"><a name="p1640326869093533"></a><a name="p1640326869093533"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1478641560093533"><a name="p1478641560093533"></a><a name="p1478641560093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row582147578093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1696127969093533"><a name="p1696127969093533"></a><a name="p1696127969093533"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p444361283093533"><a name="p444361283093533"></a><a name="p444361283093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p696549132093533"><a name="p696549132093533"></a><a name="p696549132093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1594607764093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p472791451093533"><a name="p472791451093533"></a><a name="p472791451093533"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1649432975093533"><a name="p1649432975093533"></a><a name="p1649432975093533"></a>void&nbsp;</p>
<p id="p1149052300093533"><a name="p1149052300093533"></a><a name="p1149052300093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row701347020093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1396580280093533"><a name="p1396580280093533"></a><a name="p1396580280093533"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1770075453093533"><a name="p1770075453093533"></a><a name="p1770075453093533"></a>virtual void&nbsp;</p>
<p id="p1244025091093533"><a name="p1244025091093533"></a><a name="p1244025091093533"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1638332410093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p216991504093533"><a name="p216991504093533"></a><a name="p216991504093533"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p334973599093533"><a name="p334973599093533"></a><a name="p334973599093533"></a>virtual int16_t&nbsp;</p>
<p id="p243267601093533"><a name="p243267601093533"></a><a name="p243267601093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row213981181093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p574186959093533"><a name="p574186959093533"></a><a name="p574186959093533"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1622810155093533"><a name="p1622810155093533"></a><a name="p1622810155093533"></a>virtual void&nbsp;</p>
<p id="p1893851797093533"><a name="p1893851797093533"></a><a name="p1893851797093533"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row629501591093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p34861563093533"><a name="p34861563093533"></a><a name="p34861563093533"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p785887462093533"><a name="p785887462093533"></a><a name="p785887462093533"></a>virtual int16_t&nbsp;</p>
<p id="p240678165093533"><a name="p240678165093533"></a><a name="p240678165093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row875229233093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p391002226093533"><a name="p391002226093533"></a><a name="p391002226093533"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p594419415093533"><a name="p594419415093533"></a><a name="p594419415093533"></a>virtual void&nbsp;</p>
<p id="p1410550301093533"><a name="p1410550301093533"></a><a name="p1410550301093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row2012130706093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p506315884093533"><a name="p506315884093533"></a><a name="p506315884093533"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2022430230093533"><a name="p2022430230093533"></a><a name="p2022430230093533"></a>virtual void&nbsp;</p>
<p id="p1467313655093533"><a name="p1467313655093533"></a><a name="p1467313655093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row299062530093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1786511633093533"><a name="p1786511633093533"></a><a name="p1786511633093533"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1309768490093533"><a name="p1309768490093533"></a><a name="p1309768490093533"></a>int16_t&nbsp;</p>
<p id="p1731124733093533"><a name="p1731124733093533"></a><a name="p1731124733093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1586715290093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p338958020093533"><a name="p338958020093533"></a><a name="p338958020093533"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1262472465093533"><a name="p1262472465093533"></a><a name="p1262472465093533"></a>virtual void&nbsp;</p>
<p id="p1970421045093533"><a name="p1970421045093533"></a><a name="p1970421045093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1188065239093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p609980985093533"><a name="p609980985093533"></a><a name="p609980985093533"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1850400953093533"><a name="p1850400953093533"></a><a name="p1850400953093533"></a>int16_t&nbsp;</p>
<p id="p688907080093533"><a name="p688907080093533"></a><a name="p688907080093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1444728564093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p349270416093533"><a name="p349270416093533"></a><a name="p349270416093533"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432980175093533"><a name="p1432980175093533"></a><a name="p1432980175093533"></a>virtual void&nbsp;</p>
<p id="p2046997698093533"><a name="p2046997698093533"></a><a name="p2046997698093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row787869606093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1769388200093533"><a name="p1769388200093533"></a><a name="p1769388200093533"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1966744797093533"><a name="p1966744797093533"></a><a name="p1966744797093533"></a>virtual void&nbsp;</p>
<p id="p786103286093533"><a name="p786103286093533"></a><a name="p786103286093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row945852470093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1313356797093533"><a name="p1313356797093533"></a><a name="p1313356797093533"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1029162793093533"><a name="p1029162793093533"></a><a name="p1029162793093533"></a>bool&nbsp;</p>
<p id="p1114559887093533"><a name="p1114559887093533"></a><a name="p1114559887093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row731725410093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p473205156093533"><a name="p473205156093533"></a><a name="p473205156093533"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p543739319093533"><a name="p543739319093533"></a><a name="p543739319093533"></a>void&nbsp;</p>
<p id="p287347071093533"><a name="p287347071093533"></a><a name="p287347071093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row123197816093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p583411898093533"><a name="p583411898093533"></a><a name="p583411898093533"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1664618524093533"><a name="p1664618524093533"></a><a name="p1664618524093533"></a>void&nbsp;</p>
<p id="p428457500093533"><a name="p428457500093533"></a><a name="p428457500093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1129564033093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p9009981093533"><a name="p9009981093533"></a><a name="p9009981093533"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p272859539093533"><a name="p272859539093533"></a><a name="p272859539093533"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p1973851436093533"><a name="p1973851436093533"></a><a name="p1973851436093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1675501316093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p808191464093533"><a name="p808191464093533"></a><a name="p808191464093533"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1599108698093533"><a name="p1599108698093533"></a><a name="p1599108698093533"></a>void&nbsp;</p>
<p id="p1525903790093533"><a name="p1525903790093533"></a><a name="p1525903790093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row756351932093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1791394285093533"><a name="p1791394285093533"></a><a name="p1791394285093533"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1402609411093533"><a name="p1402609411093533"></a><a name="p1402609411093533"></a>const char *&nbsp;</p>
<p id="p381862288093533"><a name="p381862288093533"></a><a name="p381862288093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1889429847093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p530411631093533"><a name="p530411631093533"></a><a name="p530411631093533"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2093637446093533"><a name="p2093637446093533"></a><a name="p2093637446093533"></a>void&nbsp;</p>
<p id="p1056047487093533"><a name="p1056047487093533"></a><a name="p1056047487093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row235034490093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1579872603093533"><a name="p1579872603093533"></a><a name="p1579872603093533"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p778575755093533"><a name="p778575755093533"></a><a name="p778575755093533"></a>int16_t&nbsp;</p>
<p id="p1449902390093533"><a name="p1449902390093533"></a><a name="p1449902390093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row180179381093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1301159954093533"><a name="p1301159954093533"></a><a name="p1301159954093533"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p149035079093533"><a name="p149035079093533"></a><a name="p149035079093533"></a>virtual void&nbsp;</p>
<p id="p378685623093533"><a name="p378685623093533"></a><a name="p378685623093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row2129787850093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p582525875093533"><a name="p582525875093533"></a><a name="p582525875093533"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1888056289093533"><a name="p1888056289093533"></a><a name="p1888056289093533"></a>void&nbsp;</p>
<p id="p260772104093533"><a name="p260772104093533"></a><a name="p260772104093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row720670613093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2060513050093533"><a name="p2060513050093533"></a><a name="p2060513050093533"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1221518070093533"><a name="p1221518070093533"></a><a name="p1221518070093533"></a>void&nbsp;</p>
<p id="p467838685093533"><a name="p467838685093533"></a><a name="p467838685093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row173240174093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806440766093533"><a name="p806440766093533"></a><a name="p806440766093533"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620239990093533"><a name="p620239990093533"></a><a name="p620239990093533"></a>void&nbsp;</p>
<p id="p17483057093533"><a name="p17483057093533"></a><a name="p17483057093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1911092992093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1807511860093533"><a name="p1807511860093533"></a><a name="p1807511860093533"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2097664186093533"><a name="p2097664186093533"></a><a name="p2097664186093533"></a>void&nbsp;</p>
<p id="p295257545093533"><a name="p295257545093533"></a><a name="p295257545093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row554885372093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2121656567093533"><a name="p2121656567093533"></a><a name="p2121656567093533"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1990866535093533"><a name="p1990866535093533"></a><a name="p1990866535093533"></a>void&nbsp;</p>
<p id="p184276017093533"><a name="p184276017093533"></a><a name="p184276017093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1288977618093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2099335861093533"><a name="p2099335861093533"></a><a name="p2099335861093533"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1974119353093533"><a name="p1974119353093533"></a><a name="p1974119353093533"></a>void&nbsp;</p>
<p id="p980816325093533"><a name="p980816325093533"></a><a name="p980816325093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1377831409093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408792084093533"><a name="p1408792084093533"></a><a name="p1408792084093533"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p462446416093533"><a name="p462446416093533"></a><a name="p462446416093533"></a>void&nbsp;</p>
<p id="p326514220093533"><a name="p326514220093533"></a><a name="p326514220093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row603715624093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1715165602093533"><a name="p1715165602093533"></a><a name="p1715165602093533"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p295203401093533"><a name="p295203401093533"></a><a name="p295203401093533"></a>void&nbsp;</p>
<p id="p1475794109093533"><a name="p1475794109093533"></a><a name="p1475794109093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row531503597093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p169946900093533"><a name="p169946900093533"></a><a name="p169946900093533"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1320563430093533"><a name="p1320563430093533"></a><a name="p1320563430093533"></a>void&nbsp;</p>
<p id="p1475560366093533"><a name="p1475560366093533"></a><a name="p1475560366093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1578997395093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1671047588093533"><a name="p1671047588093533"></a><a name="p1671047588093533"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p480314221093533"><a name="p480314221093533"></a><a name="p480314221093533"></a>void&nbsp;</p>
<p id="p1081878944093533"><a name="p1081878944093533"></a><a name="p1081878944093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1509912046093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p603990359093533"><a name="p603990359093533"></a><a name="p603990359093533"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1558456848093533"><a name="p1558456848093533"></a><a name="p1558456848093533"></a>void&nbsp;</p>
<p id="p571868540093533"><a name="p571868540093533"></a><a name="p571868540093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1998056944093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p122160897093533"><a name="p122160897093533"></a><a name="p122160897093533"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2098848657093533"><a name="p2098848657093533"></a><a name="p2098848657093533"></a>void&nbsp;</p>
<p id="p2039518745093533"><a name="p2039518745093533"></a><a name="p2039518745093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1491764312093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p153781782093533"><a name="p153781782093533"></a><a name="p153781782093533"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1958496191093533"><a name="p1958496191093533"></a><a name="p1958496191093533"></a>void&nbsp;</p>
<p id="p1775629695093533"><a name="p1775629695093533"></a><a name="p1775629695093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1289407425093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p299719583093533"><a name="p299719583093533"></a><a name="p299719583093533"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p297109495093533"><a name="p297109495093533"></a><a name="p297109495093533"></a>void&nbsp;</p>
<p id="p828219281093533"><a name="p828219281093533"></a><a name="p828219281093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1080491147093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1835177935093533"><a name="p1835177935093533"></a><a name="p1835177935093533"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1411679402093533"><a name="p1411679402093533"></a><a name="p1411679402093533"></a>void&nbsp;</p>
<p id="p1071523949093533"><a name="p1071523949093533"></a><a name="p1071523949093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row737661635093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1488868229093533"><a name="p1488868229093533"></a><a name="p1488868229093533"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p394348559093533"><a name="p394348559093533"></a><a name="p394348559093533"></a>virtual void&nbsp;</p>
<p id="p2048583917093533"><a name="p2048583917093533"></a><a name="p2048583917093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row812282653093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1528218925093533"><a name="p1528218925093533"></a><a name="p1528218925093533"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1730491447093533"><a name="p1730491447093533"></a><a name="p1730491447093533"></a>virtual void&nbsp;</p>
<p id="p5554751093533"><a name="p5554751093533"></a><a name="p5554751093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1438107487093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p985778932093533"><a name="p985778932093533"></a><a name="p985778932093533"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p956067493093533"><a name="p956067493093533"></a><a name="p956067493093533"></a>virtual int64_t&nbsp;</p>
<p id="p1903569313093533"><a name="p1903569313093533"></a><a name="p1903569313093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1058001694093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p363462414093533"><a name="p363462414093533"></a><a name="p363462414093533"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p99484119093533"><a name="p99484119093533"></a><a name="p99484119093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1313912885093533"><a name="p1313912885093533"></a><a name="p1313912885093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1607683961093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1123107146093533"><a name="p1123107146093533"></a><a name="p1123107146093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1243598305093533"><a name="p1243598305093533"></a><a name="p1243598305093533"></a>void *&nbsp;</p>
<p id="p680317806093533"><a name="p680317806093533"></a><a name="p680317806093533"></a>Overrides the <strong id="b1359269179093533"><a name="b1359269179093533"></a><a name="b1359269179093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1338626802093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1091386782093533"><a name="p1091386782093533"></a><a name="p1091386782093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1268941715093533"><a name="p1268941715093533"></a><a name="p1268941715093533"></a>void&nbsp;</p>
<p id="p346390004093533"><a name="p346390004093533"></a><a name="p346390004093533"></a>Overrides the <strong id="b1887279909093533"><a name="b1887279909093533"></a><a name="b1887279909093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1389950536093533"></a>
<table><thead align="left"><tr id="row283551532093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1972465572093533"><a name="p1972465572093533"></a><a name="p1972465572093533"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p407587750093533"><a name="p407587750093533"></a><a name="p407587750093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row329211294093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2028073094093533"><a name="p2028073094093533"></a><a name="p2028073094093533"></a><a href="Graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1322897530093533"><a name="p1322897530093533"></a><a name="p1322897530093533"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1371639524093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p869561557093533"><a name="p869561557093533"></a><a name="p869561557093533"></a><a href="Graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1121171998093533"><a name="p1121171998093533"></a><a name="p1121171998093533"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row1352393265093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1503833906093533"><a name="p1503833906093533"></a><a name="p1503833906093533"></a><a href="Graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p288165595093533"><a name="p288165595093533"></a><a name="p288165595093533"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row833198024093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1118851978093533"><a name="p1118851978093533"></a><a name="p1118851978093533"></a><a href="Graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449944016093533"><a name="p449944016093533"></a><a name="p449944016093533"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row823813646093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p284257896093533"><a name="p284257896093533"></a><a name="p284257896093533"></a><a href="Graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1011676023093533"><a name="p1011676023093533"></a><a name="p1011676023093533"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row524764216093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1238188396093533"><a name="p1238188396093533"></a><a name="p1238188396093533"></a><a href="Graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1648916652093533"><a name="p1648916652093533"></a><a name="p1648916652093533"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1482430342093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1422828534093533"><a name="p1422828534093533"></a><a name="p1422828534093533"></a><a href="Graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p383098797093533"><a name="p383098797093533"></a><a name="p383098797093533"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1755675281093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1330832880093533"><a name="p1330832880093533"></a><a name="p1330832880093533"></a><a href="Graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p495564870093533"><a name="p495564870093533"></a><a name="p495564870093533"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

