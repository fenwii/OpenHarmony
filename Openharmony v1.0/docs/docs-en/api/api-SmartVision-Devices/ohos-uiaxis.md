# OHOS::UIAxis<a name="EN-US_TOPIC_0000001054799621"></a>

## **Overview**<a name="section579769269093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Represents the coordinate axis base class, which defines the basic attributes of coordinate axis, sets whether a coordinate axis is visible, and sets the number of scales on a coordinate axis. This class is used in  [UIChart](ohos-uichart.md). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section714921317093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table20060365093533"></a>
<table><thead align="left"><tr id="row1768942132093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p528529814093533"><a name="p528529814093533"></a><a name="p528529814093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p214406417093533"><a name="p214406417093533"></a><a name="p214406417093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1137236116093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1796658404093533"><a name="p1796658404093533"></a><a name="p1796658404093533"></a><a href="graphic.md#gad79f1c694abce57af451b8f7b0b17c35">UIAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1191370351093533"><a name="p1191370351093533"></a><a name="p1191370351093533"></a> </p>
<p id="p2021157406093533"><a name="p2021157406093533"></a><a name="p2021157406093533"></a>A constructor used to create a <strong id="b1783716592093533"><a name="b1783716592093533"></a><a name="b1783716592093533"></a><a href="ohos-uiaxis.md">UIAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row1812647698093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244641605093533"><a name="p1244641605093533"></a><a name="p1244641605093533"></a><a href="graphic.md#gaacc9ac178b3b235f1186297021eb98d8">~UIAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p592857092093533"><a name="p592857092093533"></a><a name="p592857092093533"></a>virtual </p>
<p id="p1422500091093533"><a name="p1422500091093533"></a><a name="p1422500091093533"></a>A destructor used to delete the <strong id="b1019766184093533"><a name="b1019766184093533"></a><a name="b1019766184093533"></a><a href="ohos-uiaxis.md">UIAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row1445664353093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1921595751093533"><a name="p1921595751093533"></a><a name="p1921595751093533"></a><a href="graphic.md#ga2f46b702f1543c5076a8957a94a780d3">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p197522415093533"><a name="p197522415093533"></a><a name="p197522415093533"></a>UIViewType </p>
<p id="p1576125573093533"><a name="p1576125573093533"></a><a name="p1576125573093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row956846802093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1154596895093533"><a name="p1154596895093533"></a><a name="p1154596895093533"></a><a href="graphic.md#gabb486419e729add9ff85a24371253bf8">SetDataRange</a> (uint16_t min, uint16_t max)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1857139465093533"><a name="p1857139465093533"></a><a name="p1857139465093533"></a>virtual bool </p>
<p id="p1513114986093533"><a name="p1513114986093533"></a><a name="p1513114986093533"></a>Sets the value range of a coordinate axis. </p>
</td>
</tr>
<tr id="row1398360071093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2110648543093533"><a name="p2110648543093533"></a><a name="p2110648543093533"></a><a href="graphic.md#gaebe68b636d2147f2e69bd658696dc4ee">SetMarkNum</a> (uint16_t count)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1918013431093533"><a name="p1918013431093533"></a><a name="p1918013431093533"></a>virtual void </p>
<p id="p1435911593093533"><a name="p1435911593093533"></a><a name="p1435911593093533"></a>Sets the number of scales on a coordinate axis. </p>
</td>
</tr>
<tr id="row772676439093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290347746093533"><a name="p1290347746093533"></a><a name="p1290347746093533"></a><a href="graphic.md#ga8ceec5e67fa2c4f161bd9af1f0788bbe">SetLineColor</a> (const <a href="ohos-color32.md">ColorType</a> &amp;color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1395109393093533"><a name="p1395109393093533"></a><a name="p1395109393093533"></a>void </p>
<p id="p1869725070093533"><a name="p1869725070093533"></a><a name="p1869725070093533"></a>Sets the line color of the coordinate axis. </p>
</td>
</tr>
<tr id="row450333952093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p569235896093533"><a name="p569235896093533"></a><a name="p569235896093533"></a><a href="graphic.md#ga5360803f425055de52af5f7fa1081cfe">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2107573369093533"><a name="p2107573369093533"></a><a name="p2107573369093533"></a>void </p>
<p id="p659456640093533"><a name="p659456640093533"></a><a name="p659456640093533"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1709825126093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p772713776093533"><a name="p772713776093533"></a><a name="p772713776093533"></a><a href="graphic.md#gad1bf4d83270c0a4ba04f3cffbc67bb97">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1896099450093533"><a name="p1896099450093533"></a><a name="p1896099450093533"></a>bool </p>
<p id="p50935298093533"><a name="p50935298093533"></a><a name="p50935298093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row585967552093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1461710544093533"><a name="p1461710544093533"></a><a name="p1461710544093533"></a><a href="graphic.md#ga8ff3fd2953897245e4f6e3cb6bd71495">TranslateToPixel</a> (int16_t &amp;value)=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1986653270093533"><a name="p1986653270093533"></a><a name="p1986653270093533"></a>virtual void </p>
<p id="p97290758093533"><a name="p97290758093533"></a><a name="p97290758093533"></a>Translates data into pixel coordinates. </p>
</td>
</tr>
<tr id="row414937440093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806654074093533"><a name="p806654074093533"></a><a name="p806654074093533"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1882940389093533"><a name="p1882940389093533"></a><a name="p1882940389093533"></a> </p>
<p id="p2145986641093533"><a name="p2145986641093533"></a><a name="p2145986641093533"></a>A default constructor used to create a <strong id="b1799837155093533"><a name="b1799837155093533"></a><a name="b1799837155093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1065380203093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1631950570093533"><a name="p1631950570093533"></a><a name="p1631950570093533"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71559598093533"><a name="p71559598093533"></a><a name="p71559598093533"></a>virtual </p>
<p id="p1001406271093533"><a name="p1001406271093533"></a><a name="p1001406271093533"></a>A destructor used to delete the <strong id="b1255307136093533"><a name="b1255307136093533"></a><a name="b1255307136093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row303496080093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p875235826093533"><a name="p875235826093533"></a><a name="p875235826093533"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p746373484093533"><a name="p746373484093533"></a><a name="p746373484093533"></a>UIViewType </p>
<p id="p1638157108093533"><a name="p1638157108093533"></a><a name="p1638157108093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1362833808093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1938316213093533"><a name="p1938316213093533"></a><a name="p1938316213093533"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p100758093533"><a name="p100758093533"></a><a name="p100758093533"></a>virtual void </p>
<p id="p530335249093533"><a name="p530335249093533"></a><a name="p530335249093533"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row1678927125093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p755940616093533"><a name="p755940616093533"></a><a name="p755940616093533"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1565407341093533"><a name="p1565407341093533"></a><a name="p1565407341093533"></a>virtual void </p>
<p id="p125578166093533"><a name="p125578166093533"></a><a name="p125578166093533"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row2084969416093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691539202093533"><a name="p691539202093533"></a><a name="p691539202093533"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422462959093533"><a name="p422462959093533"></a><a name="p422462959093533"></a>virtual void </p>
<p id="p321029147093533"><a name="p321029147093533"></a><a name="p321029147093533"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row203445716093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1310210020093533"><a name="p1310210020093533"></a><a name="p1310210020093533"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1829893481093533"><a name="p1829893481093533"></a><a name="p1829893481093533"></a>virtual void </p>
<p id="p283662611093533"><a name="p283662611093533"></a><a name="p283662611093533"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row2090817884093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1570748754093533"><a name="p1570748754093533"></a><a name="p1570748754093533"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p424201059093533"><a name="p424201059093533"></a><a name="p424201059093533"></a>virtual void </p>
<p id="p2108908977093533"><a name="p2108908977093533"></a><a name="p2108908977093533"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1105256741093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p691052001093533"><a name="p691052001093533"></a><a name="p691052001093533"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1801240156093533"><a name="p1801240156093533"></a><a name="p1801240156093533"></a>virtual void </p>
<p id="p910656410093533"><a name="p910656410093533"></a><a name="p910656410093533"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row993074741093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p62705966093533"><a name="p62705966093533"></a><a name="p62705966093533"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p728292526093533"><a name="p728292526093533"></a><a name="p728292526093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p754120155093533"><a name="p754120155093533"></a><a name="p754120155093533"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1672520822093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p259341851093533"><a name="p259341851093533"></a><a name="p259341851093533"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1139620860093533"><a name="p1139620860093533"></a><a name="p1139620860093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1643177988093533"><a name="p1643177988093533"></a><a name="p1643177988093533"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row516494302093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1933457600093533"><a name="p1933457600093533"></a><a name="p1933457600093533"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p684178278093533"><a name="p684178278093533"></a><a name="p684178278093533"></a>void </p>
<p id="p709124501093533"><a name="p709124501093533"></a><a name="p709124501093533"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1538163570093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p561764002093533"><a name="p561764002093533"></a><a name="p561764002093533"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p687409969093533"><a name="p687409969093533"></a><a name="p687409969093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p285160992093533"><a name="p285160992093533"></a><a name="p285160992093533"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row1840443966093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p209636227093533"><a name="p209636227093533"></a><a name="p209636227093533"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1097073836093533"><a name="p1097073836093533"></a><a name="p1097073836093533"></a>void </p>
<p id="p718050463093533"><a name="p718050463093533"></a><a name="p718050463093533"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row218764179093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2137543911093533"><a name="p2137543911093533"></a><a name="p2137543911093533"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p745052811093533"><a name="p745052811093533"></a><a name="p745052811093533"></a> </p>
<p id="p224824898093533"><a name="p224824898093533"></a><a name="p224824898093533"></a>A default constructor used to create an <strong id="b604929771093533"><a name="b604929771093533"></a><a name="b604929771093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row840131931093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1736291091093533"><a name="p1736291091093533"></a><a name="p1736291091093533"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p877933740093533"><a name="p877933740093533"></a><a name="p877933740093533"></a> </p>
<p id="p1354097765093533"><a name="p1354097765093533"></a><a name="p1354097765093533"></a>A constructor used to create an <strong id="b1527193444093533"><a name="b1527193444093533"></a><a name="b1527193444093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row261123481093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p987318234093533"><a name="p987318234093533"></a><a name="p987318234093533"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1338917275093533"><a name="p1338917275093533"></a><a name="p1338917275093533"></a>virtual </p>
<p id="p1743910617093533"><a name="p1743910617093533"></a><a name="p1743910617093533"></a>A destructor used to delete the <strong id="b2011607434093533"><a name="b2011607434093533"></a><a name="b2011607434093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row478910727093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p264998390093533"><a name="p264998390093533"></a><a name="p264998390093533"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p272692903093533"><a name="p272692903093533"></a><a name="p272692903093533"></a>virtual void </p>
<p id="p1377005470093533"><a name="p1377005470093533"></a><a name="p1377005470093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row664075052093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p511093442093533"><a name="p511093442093533"></a><a name="p511093442093533"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1508106925093533"><a name="p1508106925093533"></a><a name="p1508106925093533"></a>virtual void </p>
<p id="p784696090093533"><a name="p784696090093533"></a><a name="p784696090093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row959089776093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1970238152093533"><a name="p1970238152093533"></a><a name="p1970238152093533"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p368810997093533"><a name="p368810997093533"></a><a name="p368810997093533"></a>void </p>
<p id="p2126165079093533"><a name="p2126165079093533"></a><a name="p2126165079093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row2013807647093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1030077560093533"><a name="p1030077560093533"></a><a name="p1030077560093533"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1383779213093533"><a name="p1383779213093533"></a><a name="p1383779213093533"></a>void </p>
<p id="p1361697310093533"><a name="p1361697310093533"></a><a name="p1361697310093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row37338074093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p741680474093533"><a name="p741680474093533"></a><a name="p741680474093533"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p695163332093533"><a name="p695163332093533"></a><a name="p695163332093533"></a>virtual bool </p>
<p id="p1825606888093533"><a name="p1825606888093533"></a><a name="p1825606888093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row726560914093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1148503821093533"><a name="p1148503821093533"></a><a name="p1148503821093533"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1736182691093533"><a name="p1736182691093533"></a><a name="p1736182691093533"></a>virtual bool </p>
<p id="p756607866093533"><a name="p756607866093533"></a><a name="p756607866093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row834194637093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1658692508093533"><a name="p1658692508093533"></a><a name="p1658692508093533"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2031372050093533"><a name="p2031372050093533"></a><a name="p2031372050093533"></a>virtual bool </p>
<p id="p1674087942093533"><a name="p1674087942093533"></a><a name="p1674087942093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1361548674093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p592023469093533"><a name="p592023469093533"></a><a name="p592023469093533"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1641498133093533"><a name="p1641498133093533"></a><a name="p1641498133093533"></a>virtual bool </p>
<p id="p391843858093533"><a name="p391843858093533"></a><a name="p391843858093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row814001672093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p44802468093533"><a name="p44802468093533"></a><a name="p44802468093533"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p427439077093533"><a name="p427439077093533"></a><a name="p427439077093533"></a>virtual void </p>
<p id="p609987878093533"><a name="p609987878093533"></a><a name="p609987878093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row1713414335093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973100228093533"><a name="p973100228093533"></a><a name="p973100228093533"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1088136926093533"><a name="p1088136926093533"></a><a name="p1088136926093533"></a>virtual void </p>
<p id="p243431527093533"><a name="p243431527093533"></a><a name="p243431527093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row236123231093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p377847384093533"><a name="p377847384093533"></a><a name="p377847384093533"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p609714092093533"><a name="p609714092093533"></a><a name="p609714092093533"></a>virtual void </p>
<p id="p491081492093533"><a name="p491081492093533"></a><a name="p491081492093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row716851756093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1808874100093533"><a name="p1808874100093533"></a><a name="p1808874100093533"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1643446121093533"><a name="p1643446121093533"></a><a name="p1643446121093533"></a>virtual void </p>
<p id="p1119965283093533"><a name="p1119965283093533"></a><a name="p1119965283093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row608615780093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p498594163093533"><a name="p498594163093533"></a><a name="p498594163093533"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p776033781093533"><a name="p776033781093533"></a><a name="p776033781093533"></a>void </p>
<p id="p617893571093533"><a name="p617893571093533"></a><a name="p617893571093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row597033934093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p468525413093533"><a name="p468525413093533"></a><a name="p468525413093533"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p173635672093533"><a name="p173635672093533"></a><a name="p173635672093533"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p511301707093533"><a name="p511301707093533"></a><a name="p511301707093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row243001661093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1542280636093533"><a name="p1542280636093533"></a><a name="p1542280636093533"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p918682440093533"><a name="p918682440093533"></a><a name="p918682440093533"></a>void </p>
<p id="p1142521788093533"><a name="p1142521788093533"></a><a name="p1142521788093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1342452382093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2052593742093533"><a name="p2052593742093533"></a><a name="p2052593742093533"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1769809064093533"><a name="p1769809064093533"></a><a name="p1769809064093533"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p2004146696093533"><a name="p2004146696093533"></a><a name="p2004146696093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row911170586093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1211149051093533"><a name="p1211149051093533"></a><a name="p1211149051093533"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1063579856093533"><a name="p1063579856093533"></a><a name="p1063579856093533"></a>void </p>
<p id="p1954773447093533"><a name="p1954773447093533"></a><a name="p1954773447093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1740194843093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1974578285093533"><a name="p1974578285093533"></a><a name="p1974578285093533"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p429567997093533"><a name="p429567997093533"></a><a name="p429567997093533"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p187734322093533"><a name="p187734322093533"></a><a name="p187734322093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row183431769093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p155138506093533"><a name="p155138506093533"></a><a name="p155138506093533"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2013472304093533"><a name="p2013472304093533"></a><a name="p2013472304093533"></a>void </p>
<p id="p1520277545093533"><a name="p1520277545093533"></a><a name="p1520277545093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1182943861093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p659349191093533"><a name="p659349191093533"></a><a name="p659349191093533"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278809186093533"><a name="p278809186093533"></a><a name="p278809186093533"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p293409339093533"><a name="p293409339093533"></a><a name="p293409339093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row262867183093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p263787012093533"><a name="p263787012093533"></a><a name="p263787012093533"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1011149826093533"><a name="p1011149826093533"></a><a name="p1011149826093533"></a>void </p>
<p id="p1174985167093533"><a name="p1174985167093533"></a><a name="p1174985167093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1274180255093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p547152306093533"><a name="p547152306093533"></a><a name="p547152306093533"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p359531461093533"><a name="p359531461093533"></a><a name="p359531461093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1280834179093533"><a name="p1280834179093533"></a><a name="p1280834179093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row899332229093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2050404918093533"><a name="p2050404918093533"></a><a name="p2050404918093533"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1347420188093533"><a name="p1347420188093533"></a><a name="p1347420188093533"></a>void </p>
<p id="p150146110093533"><a name="p150146110093533"></a><a name="p150146110093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1345184351093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p815409749093533"><a name="p815409749093533"></a><a name="p815409749093533"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2147414229093533"><a name="p2147414229093533"></a><a name="p2147414229093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p2071125466093533"><a name="p2071125466093533"></a><a name="p2071125466093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1609268587093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1457893455093533"><a name="p1457893455093533"></a><a name="p1457893455093533"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p521491485093533"><a name="p521491485093533"></a><a name="p521491485093533"></a>virtual void </p>
<p id="p1270989419093533"><a name="p1270989419093533"></a><a name="p1270989419093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row2128949832093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1750117725093533"><a name="p1750117725093533"></a><a name="p1750117725093533"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p845685667093533"><a name="p845685667093533"></a><a name="p845685667093533"></a>bool </p>
<p id="p140559740093533"><a name="p140559740093533"></a><a name="p140559740093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1342505969093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p103529734093533"><a name="p103529734093533"></a><a name="p103529734093533"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p380815921093533"><a name="p380815921093533"></a><a name="p380815921093533"></a>void </p>
<p id="p2112643677093533"><a name="p2112643677093533"></a><a name="p2112643677093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row397707646093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1507787916093533"><a name="p1507787916093533"></a><a name="p1507787916093533"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650241540093533"><a name="p650241540093533"></a><a name="p650241540093533"></a>bool </p>
<p id="p760808130093533"><a name="p760808130093533"></a><a name="p760808130093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1385034425093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1357151424093533"><a name="p1357151424093533"></a><a name="p1357151424093533"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801836538093533"><a name="p801836538093533"></a><a name="p801836538093533"></a>void </p>
<p id="p1407080850093533"><a name="p1407080850093533"></a><a name="p1407080850093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row337929919093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p274613940093533"><a name="p274613940093533"></a><a name="p274613940093533"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687773888093533"><a name="p1687773888093533"></a><a name="p1687773888093533"></a>bool </p>
<p id="p1222967715093533"><a name="p1222967715093533"></a><a name="p1222967715093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1106758624093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p995408242093533"><a name="p995408242093533"></a><a name="p995408242093533"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p510915748093533"><a name="p510915748093533"></a><a name="p510915748093533"></a>void </p>
<p id="p1740002785093533"><a name="p1740002785093533"></a><a name="p1740002785093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1654512688093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1139922945093533"><a name="p1139922945093533"></a><a name="p1139922945093533"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1203256537093533"><a name="p1203256537093533"></a><a name="p1203256537093533"></a>bool </p>
<p id="p497886357093533"><a name="p497886357093533"></a><a name="p497886357093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1823440082093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p609884643093533"><a name="p609884643093533"></a><a name="p609884643093533"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p750029591093533"><a name="p750029591093533"></a><a name="p750029591093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1767066157093533"><a name="p1767066157093533"></a><a name="p1767066157093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1650277586093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1284479015093533"><a name="p1284479015093533"></a><a name="p1284479015093533"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p917606334093533"><a name="p917606334093533"></a><a name="p917606334093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1136043770093533"><a name="p1136043770093533"></a><a name="p1136043770093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row818853928093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1062228488093533"><a name="p1062228488093533"></a><a name="p1062228488093533"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p197535419093533"><a name="p197535419093533"></a><a name="p197535419093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p767662881093533"><a name="p767662881093533"></a><a name="p767662881093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row729652219093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505430031093533"><a name="p1505430031093533"></a><a name="p1505430031093533"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p44252724093533"><a name="p44252724093533"></a><a name="p44252724093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1232565659093533"><a name="p1232565659093533"></a><a name="p1232565659093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row2134347185093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p714918274093533"><a name="p714918274093533"></a><a name="p714918274093533"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1849511928093533"><a name="p1849511928093533"></a><a name="p1849511928093533"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1868924434093533"><a name="p1868924434093533"></a><a name="p1868924434093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row2051086309093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p235919421093533"><a name="p235919421093533"></a><a name="p235919421093533"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p803824942093533"><a name="p803824942093533"></a><a name="p803824942093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1998786650093533"><a name="p1998786650093533"></a><a name="p1998786650093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row927271087093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1964612697093533"><a name="p1964612697093533"></a><a name="p1964612697093533"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p205651778093533"><a name="p205651778093533"></a><a name="p205651778093533"></a>void </p>
<p id="p492142996093533"><a name="p492142996093533"></a><a name="p492142996093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row2100535403093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p180746547093533"><a name="p180746547093533"></a><a name="p180746547093533"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p769763091093533"><a name="p769763091093533"></a><a name="p769763091093533"></a>virtual void </p>
<p id="p385845568093533"><a name="p385845568093533"></a><a name="p385845568093533"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row294842036093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1961652999093533"><a name="p1961652999093533"></a><a name="p1961652999093533"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1262366879093533"><a name="p1262366879093533"></a><a name="p1262366879093533"></a>virtual int16_t </p>
<p id="p1907394921093533"><a name="p1907394921093533"></a><a name="p1907394921093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row939411898093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2005224213093533"><a name="p2005224213093533"></a><a name="p2005224213093533"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1804777357093533"><a name="p1804777357093533"></a><a name="p1804777357093533"></a>virtual void </p>
<p id="p1579106758093533"><a name="p1579106758093533"></a><a name="p1579106758093533"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row474670728093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p919119105093533"><a name="p919119105093533"></a><a name="p919119105093533"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p625857494093533"><a name="p625857494093533"></a><a name="p625857494093533"></a>virtual int16_t </p>
<p id="p727527714093533"><a name="p727527714093533"></a><a name="p727527714093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row118317913093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1760055323093533"><a name="p1760055323093533"></a><a name="p1760055323093533"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2021618392093533"><a name="p2021618392093533"></a><a name="p2021618392093533"></a>virtual void </p>
<p id="p1012706864093533"><a name="p1012706864093533"></a><a name="p1012706864093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row483997293093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1813939970093533"><a name="p1813939970093533"></a><a name="p1813939970093533"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1564627893093533"><a name="p1564627893093533"></a><a name="p1564627893093533"></a>virtual void </p>
<p id="p1339953475093533"><a name="p1339953475093533"></a><a name="p1339953475093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1250451879093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197497914093533"><a name="p1197497914093533"></a><a name="p1197497914093533"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1194586893093533"><a name="p1194586893093533"></a><a name="p1194586893093533"></a>int16_t </p>
<p id="p544609296093533"><a name="p544609296093533"></a><a name="p544609296093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1041750619093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p563813629093533"><a name="p563813629093533"></a><a name="p563813629093533"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1392547032093533"><a name="p1392547032093533"></a><a name="p1392547032093533"></a>virtual void </p>
<p id="p719440111093533"><a name="p719440111093533"></a><a name="p719440111093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1860269858093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2134293660093533"><a name="p2134293660093533"></a><a name="p2134293660093533"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p728892344093533"><a name="p728892344093533"></a><a name="p728892344093533"></a>int16_t </p>
<p id="p1758466196093533"><a name="p1758466196093533"></a><a name="p1758466196093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row705242137093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2136567874093533"><a name="p2136567874093533"></a><a name="p2136567874093533"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p897964381093533"><a name="p897964381093533"></a><a name="p897964381093533"></a>virtual void </p>
<p id="p1524624112093533"><a name="p1524624112093533"></a><a name="p1524624112093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row164089296093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1075349881093533"><a name="p1075349881093533"></a><a name="p1075349881093533"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p603977138093533"><a name="p603977138093533"></a><a name="p603977138093533"></a>virtual void </p>
<p id="p1669744908093533"><a name="p1669744908093533"></a><a name="p1669744908093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row318031957093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p18839899093533"><a name="p18839899093533"></a><a name="p18839899093533"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1800049655093533"><a name="p1800049655093533"></a><a name="p1800049655093533"></a>bool </p>
<p id="p88552404093533"><a name="p88552404093533"></a><a name="p88552404093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row503729647093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1756499377093533"><a name="p1756499377093533"></a><a name="p1756499377093533"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773275712093533"><a name="p773275712093533"></a><a name="p773275712093533"></a>void </p>
<p id="p1345451701093533"><a name="p1345451701093533"></a><a name="p1345451701093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1178608896093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1344700233093533"><a name="p1344700233093533"></a><a name="p1344700233093533"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p467040768093533"><a name="p467040768093533"></a><a name="p467040768093533"></a>void </p>
<p id="p1348374231093533"><a name="p1348374231093533"></a><a name="p1348374231093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1619193147093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1173870252093533"><a name="p1173870252093533"></a><a name="p1173870252093533"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p457191774093533"><a name="p457191774093533"></a><a name="p457191774093533"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p1382102302093533"><a name="p1382102302093533"></a><a name="p1382102302093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1216926325093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1372235166093533"><a name="p1372235166093533"></a><a name="p1372235166093533"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1426599564093533"><a name="p1426599564093533"></a><a name="p1426599564093533"></a>void </p>
<p id="p610098667093533"><a name="p610098667093533"></a><a name="p610098667093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row452865827093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1641606320093533"><a name="p1641606320093533"></a><a name="p1641606320093533"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1281710897093533"><a name="p1281710897093533"></a><a name="p1281710897093533"></a>const char * </p>
<p id="p589025319093533"><a name="p589025319093533"></a><a name="p589025319093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row252304250093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1600978679093533"><a name="p1600978679093533"></a><a name="p1600978679093533"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1431330038093533"><a name="p1431330038093533"></a><a name="p1431330038093533"></a>void </p>
<p id="p140749545093533"><a name="p140749545093533"></a><a name="p140749545093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1718474816093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p509087461093533"><a name="p509087461093533"></a><a name="p509087461093533"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p214582135093533"><a name="p214582135093533"></a><a name="p214582135093533"></a>int16_t </p>
<p id="p1242644190093533"><a name="p1242644190093533"></a><a name="p1242644190093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1795610844093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p987439112093533"><a name="p987439112093533"></a><a name="p987439112093533"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1081861572093533"><a name="p1081861572093533"></a><a name="p1081861572093533"></a>virtual void </p>
<p id="p1045662194093533"><a name="p1045662194093533"></a><a name="p1045662194093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1960728558093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1934729725093533"><a name="p1934729725093533"></a><a name="p1934729725093533"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p851755941093533"><a name="p851755941093533"></a><a name="p851755941093533"></a>void </p>
<p id="p221719623093533"><a name="p221719623093533"></a><a name="p221719623093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1010850725093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p214132714093533"><a name="p214132714093533"></a><a name="p214132714093533"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1431378262093533"><a name="p1431378262093533"></a><a name="p1431378262093533"></a>void </p>
<p id="p1259035250093533"><a name="p1259035250093533"></a><a name="p1259035250093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row2063427282093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146508311093533"><a name="p2146508311093533"></a><a name="p2146508311093533"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1163902029093533"><a name="p1163902029093533"></a><a name="p1163902029093533"></a>void </p>
<p id="p130604093533"><a name="p130604093533"></a><a name="p130604093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1883276198093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2141934852093533"><a name="p2141934852093533"></a><a name="p2141934852093533"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p114405001093533"><a name="p114405001093533"></a><a name="p114405001093533"></a>void </p>
<p id="p375572485093533"><a name="p375572485093533"></a><a name="p375572485093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1046312311093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1925707027093533"><a name="p1925707027093533"></a><a name="p1925707027093533"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p724559330093533"><a name="p724559330093533"></a><a name="p724559330093533"></a>void </p>
<p id="p1780246755093533"><a name="p1780246755093533"></a><a name="p1780246755093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1491835322093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422494206093533"><a name="p422494206093533"></a><a name="p422494206093533"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1720611970093533"><a name="p1720611970093533"></a><a name="p1720611970093533"></a>void </p>
<p id="p1220158111093533"><a name="p1220158111093533"></a><a name="p1220158111093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1885780965093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1966720954093533"><a name="p1966720954093533"></a><a name="p1966720954093533"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550013095093533"><a name="p1550013095093533"></a><a name="p1550013095093533"></a>void </p>
<p id="p1614308754093533"><a name="p1614308754093533"></a><a name="p1614308754093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row421937471093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p33596741093533"><a name="p33596741093533"></a><a name="p33596741093533"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1228578530093533"><a name="p1228578530093533"></a><a name="p1228578530093533"></a>void </p>
<p id="p873524716093533"><a name="p873524716093533"></a><a name="p873524716093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row611097557093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p816308796093533"><a name="p816308796093533"></a><a name="p816308796093533"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1351188034093533"><a name="p1351188034093533"></a><a name="p1351188034093533"></a>void </p>
<p id="p1477085093533"><a name="p1477085093533"></a><a name="p1477085093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1992983140093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1327698757093533"><a name="p1327698757093533"></a><a name="p1327698757093533"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1326681946093533"><a name="p1326681946093533"></a><a name="p1326681946093533"></a>void </p>
<p id="p1201631717093533"><a name="p1201631717093533"></a><a name="p1201631717093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row143379066093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p108153339093533"><a name="p108153339093533"></a><a name="p108153339093533"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1935292482093533"><a name="p1935292482093533"></a><a name="p1935292482093533"></a>void </p>
<p id="p1574400886093533"><a name="p1574400886093533"></a><a name="p1574400886093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row28106805093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1143080325093533"><a name="p1143080325093533"></a><a name="p1143080325093533"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1892489702093533"><a name="p1892489702093533"></a><a name="p1892489702093533"></a>void </p>
<p id="p2030422650093533"><a name="p2030422650093533"></a><a name="p2030422650093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row629770453093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1848239517093533"><a name="p1848239517093533"></a><a name="p1848239517093533"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1237784025093533"><a name="p1237784025093533"></a><a name="p1237784025093533"></a>void </p>
<p id="p606998578093533"><a name="p606998578093533"></a><a name="p606998578093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1416932561093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p271114760093533"><a name="p271114760093533"></a><a name="p271114760093533"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1769288832093533"><a name="p1769288832093533"></a><a name="p1769288832093533"></a>void </p>
<p id="p919948780093533"><a name="p919948780093533"></a><a name="p919948780093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row718900041093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1237684970093533"><a name="p1237684970093533"></a><a name="p1237684970093533"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p113348685093533"><a name="p113348685093533"></a><a name="p113348685093533"></a>void </p>
<p id="p1586264512093533"><a name="p1586264512093533"></a><a name="p1586264512093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row823777140093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1221834071093533"><a name="p1221834071093533"></a><a name="p1221834071093533"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1048963811093533"><a name="p1048963811093533"></a><a name="p1048963811093533"></a>virtual void </p>
<p id="p1931936767093533"><a name="p1931936767093533"></a><a name="p1931936767093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row114589408093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1307770222093533"><a name="p1307770222093533"></a><a name="p1307770222093533"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p916775102093533"><a name="p916775102093533"></a><a name="p916775102093533"></a>virtual void </p>
<p id="p1637843056093533"><a name="p1637843056093533"></a><a name="p1637843056093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1356021948093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p309474982093533"><a name="p309474982093533"></a><a name="p309474982093533"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1797667771093533"><a name="p1797667771093533"></a><a name="p1797667771093533"></a>virtual int64_t </p>
<p id="p1069695051093533"><a name="p1069695051093533"></a><a name="p1069695051093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1098301364093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p706832694093533"><a name="p706832694093533"></a><a name="p706832694093533"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p400785828093533"><a name="p400785828093533"></a><a name="p400785828093533"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p1430736270093533"><a name="p1430736270093533"></a><a name="p1430736270093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1715715785093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1423333931093533"><a name="p1423333931093533"></a><a name="p1423333931093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p274098043093533"><a name="p274098043093533"></a><a name="p274098043093533"></a>void * </p>
<p id="p457486978093533"><a name="p457486978093533"></a><a name="p457486978093533"></a>Overrides the <strong id="b1105974574093533"><a name="b1105974574093533"></a><a name="b1105974574093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1023587775093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p488831011093533"><a name="p488831011093533"></a><a name="p488831011093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1488380226093533"><a name="p1488380226093533"></a><a name="p1488380226093533"></a>void </p>
<p id="p1483277094093533"><a name="p1483277094093533"></a><a name="p1483277094093533"></a>Overrides the <strong id="b804268376093533"><a name="b804268376093533"></a><a name="b804268376093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table444884039093533"></a>
<table><thead align="left"><tr id="row2042828434093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p955470877093533"><a name="p955470877093533"></a><a name="p955470877093533"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1461042268093533"><a name="p1461042268093533"></a><a name="p1461042268093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row590959200093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p240085919093533"><a name="p240085919093533"></a><a name="p240085919093533"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1616394658093533"><a name="p1616394658093533"></a><a name="p1616394658093533"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row175765705093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984027219093533"><a name="p984027219093533"></a><a name="p984027219093533"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1658235229093533"><a name="p1658235229093533"></a><a name="p1658235229093533"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row549302080093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p841687447093533"><a name="p841687447093533"></a><a name="p841687447093533"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1997030018093533"><a name="p1997030018093533"></a><a name="p1997030018093533"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row1768450335093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1741046756093533"><a name="p1741046756093533"></a><a name="p1741046756093533"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p775857842093533"><a name="p775857842093533"></a><a name="p775857842093533"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row1371298823093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1638883251093533"><a name="p1638883251093533"></a><a name="p1638883251093533"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1406264945093533"><a name="p1406264945093533"></a><a name="p1406264945093533"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row420328053093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1315974494093533"><a name="p1315974494093533"></a><a name="p1315974494093533"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2135892847093533"><a name="p2135892847093533"></a><a name="p2135892847093533"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1602614496093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1044213852093533"><a name="p1044213852093533"></a><a name="p1044213852093533"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1768900710093533"><a name="p1768900710093533"></a><a name="p1768900710093533"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row266630128093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p189272470093533"><a name="p189272470093533"></a><a name="p189272470093533"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p504579125093533"><a name="p504579125093533"></a><a name="p504579125093533"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

