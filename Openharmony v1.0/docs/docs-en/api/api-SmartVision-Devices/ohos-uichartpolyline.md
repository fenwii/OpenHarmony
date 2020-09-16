# OHOS::UIChartPolyline<a name="EN-US_TOPIC_0000001054799623"></a>

## **Overview**<a name="section922585698093534"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Provides special functions for implementing a polyline. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section988209938093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table27952913093534"></a>
<table><thead align="left"><tr id="row1318050871093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p77170954093534"><a name="p77170954093534"></a><a name="p77170954093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1989293954093534"><a name="p1989293954093534"></a><a name="p1989293954093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2128968263093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2118926769093534"><a name="p2118926769093534"></a><a name="p2118926769093534"></a><a href="graphic.md#gaf32e6833f395ca6ac8620277531d5ea7">UIChartPolyline</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p645026339093534"><a name="p645026339093534"></a><a name="p645026339093534"></a> </p>
<p id="p1655406200093534"><a name="p1655406200093534"></a><a name="p1655406200093534"></a>A constructor used to create a <strong id="b1132462692093534"><a name="b1132462692093534"></a><a name="b1132462692093534"></a><a href="ohos-uichartpolyline.md">UIChartPolyline</a></strong> instance. </p>
</td>
</tr>
<tr id="row1468990677093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1628006002093534"><a name="p1628006002093534"></a><a name="p1628006002093534"></a><a href="graphic.md#ga620a90ab246ec8c5c55aed8985329cb9">~UIChartPolyline</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p69053707093534"><a name="p69053707093534"></a><a name="p69053707093534"></a>virtual </p>
<p id="p1410680328093534"><a name="p1410680328093534"></a><a name="p1410680328093534"></a>A destructor used to delete the <strong id="b1763442001093534"><a name="b1763442001093534"></a><a name="b1763442001093534"></a><a href="ohos-uichartpolyline.md">UIChartPolyline</a></strong> instance. </p>
</td>
</tr>
<tr id="row38303587093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p635245453093534"><a name="p635245453093534"></a><a name="p635245453093534"></a><a href="graphic.md#ga53594e65076b8588bcc48d4c69fbe8fd">RefreshChart</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1289915290093534"><a name="p1289915290093534"></a><a name="p1289915290093534"></a>void </p>
<p id="p852920847093534"><a name="p852920847093534"></a><a name="p852920847093534"></a>Refreshes a line chart and redraws the dirty region. </p>
</td>
</tr>
<tr id="row1018262408093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1920633737093534"><a name="p1920633737093534"></a><a name="p1920633737093534"></a><a href="graphic.md#gacf4303bade3933dcac90459fa38d6e1f">SetGradientOpacity</a> (uint8_t minOpa, uint8_t maxOpa)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p717916862093534"><a name="p717916862093534"></a><a name="p717916862093534"></a>void </p>
<p id="p1072876044093534"><a name="p1072876044093534"></a><a name="p1072876044093534"></a>Sets the opacity range of the fill color gradient. </p>
</td>
</tr>
<tr id="row546945155093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p441121052093534"><a name="p441121052093534"></a><a name="p441121052093534"></a><a href="graphic.md#gafdab5b0f7f8563d475c5aba2aeb1e828">SetGradientBottom</a> (uint16_t bottom)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1240312564093534"><a name="p1240312564093534"></a><a name="p1240312564093534"></a>void </p>
<p id="p1830830350093534"><a name="p1830830350093534"></a><a name="p1830830350093534"></a>Sets the distance between the bottom edge of the fill color range and the x-axis. </p>
</td>
</tr>
<tr id="row1711033258093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1640766021093534"><a name="p1640766021093534"></a><a name="p1640766021093534"></a><a href="graphic.md#ga3ab02ed367123e4f84e5ab145f5ed949">UIChart</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1253963780093534"><a name="p1253963780093534"></a><a name="p1253963780093534"></a> </p>
<p id="p1526114956093534"><a name="p1526114956093534"></a><a name="p1526114956093534"></a>A constructor used to create a <strong id="b148778033093534"><a name="b148778033093534"></a><a name="b148778033093534"></a><a href="ohos-uichart.md">UIChart</a></strong> instance. </p>
</td>
</tr>
<tr id="row1912684951093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1995902032093534"><a name="p1995902032093534"></a><a name="p1995902032093534"></a><a href="graphic.md#gab5d79c4736d822116dcdd7ed6e45294e">~UIChart</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2025985366093534"><a name="p2025985366093534"></a><a name="p2025985366093534"></a>virtual </p>
<p id="p1628364883093534"><a name="p1628364883093534"></a><a name="p1628364883093534"></a>A destructor used to delete the <strong id="b1178607981093534"><a name="b1178607981093534"></a><a name="b1178607981093534"></a><a href="ohos-uichart.md">UIChart</a></strong> instance. </p>
</td>
</tr>
<tr id="row337723829093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1370701386093534"><a name="p1370701386093534"></a><a name="p1370701386093534"></a><a href="graphic.md#gaea65298b6e4a71a2de65c13e1b14ed7b">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p442796205093534"><a name="p442796205093534"></a><a name="p442796205093534"></a>UIViewType </p>
<p id="p1489298278093534"><a name="p1489298278093534"></a><a name="p1489298278093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row3381964093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1424487326093534"><a name="p1424487326093534"></a><a name="p1424487326093534"></a><a href="graphic.md#ga54b3c4122ebaeefe74587ca69aa98600">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1234395900093534"><a name="p1234395900093534"></a><a name="p1234395900093534"></a>void </p>
<p id="p1386489187093534"><a name="p1386489187093534"></a><a name="p1386489187093534"></a>Sets the height for this component. </p>
</td>
</tr>
<tr id="row86755232093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1173468353093534"><a name="p1173468353093534"></a><a name="p1173468353093534"></a><a href="graphic.md#ga2ae317808111cd58e6ba93e030f23111">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801185773093534"><a name="p801185773093534"></a><a name="p801185773093534"></a>void </p>
<p id="p2057284216093534"><a name="p2057284216093534"></a><a name="p2057284216093534"></a>Sets the width for this component. </p>
</td>
</tr>
<tr id="row343096408093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p313775601093534"><a name="p313775601093534"></a><a name="p313775601093534"></a><a href="graphic.md#ga9a8287a522f00bb3dbe60af8f242054a">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226756757093534"><a name="p1226756757093534"></a><a name="p1226756757093534"></a>bool </p>
<p id="p1770361007093534"><a name="p1770361007093534"></a><a name="p1770361007093534"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row399976311093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1509219808093534"><a name="p1509219808093534"></a><a name="p1509219808093534"></a><a href="graphic.md#ga5c101948cb2cfb8394af0bcb56f65efb">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p597689103093534"><a name="p597689103093534"></a><a name="p597689103093534"></a>void </p>
<p id="p607662617093534"><a name="p607662617093534"></a><a name="p607662617093534"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1443151760093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p416238089093534"><a name="p416238089093534"></a><a name="p416238089093534"></a><a href="graphic.md#gafc510047aac4e7eebd5b229e726ef762">AddDataSerial</a> (<a href="ohos-uichartdataserial.md">UIChartDataSerial</a> *dataSerial)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1232188777093534"><a name="p1232188777093534"></a><a name="p1232188777093534"></a>virtual bool </p>
<p id="p236350364093534"><a name="p236350364093534"></a><a name="p236350364093534"></a>Adds a data set. </p>
</td>
</tr>
<tr id="row1809447686093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1260497644093534"><a name="p1260497644093534"></a><a name="p1260497644093534"></a><a href="graphic.md#ga2af81fbcd6a17ef250bf07e2d7606b8d">DeleteDataSerial</a> (<a href="ohos-uichartdataserial.md">UIChartDataSerial</a> *dataSerial)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p874101554093534"><a name="p874101554093534"></a><a name="p874101554093534"></a>virtual bool </p>
<p id="p999275677093534"><a name="p999275677093534"></a><a name="p999275677093534"></a>Deletes a data set. </p>
</td>
</tr>
<tr id="row359876921093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886297254093534"><a name="p1886297254093534"></a><a name="p1886297254093534"></a><a href="graphic.md#gae2752857fbcb9f1541cd811321bfc2c6">ClearDataSerial</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p581148933093534"><a name="p581148933093534"></a><a name="p581148933093534"></a>virtual void </p>
<p id="p641325497093534"><a name="p641325497093534"></a><a name="p641325497093534"></a>Clears all data sets. </p>
</td>
</tr>
<tr id="row154079989093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1247735715093534"><a name="p1247735715093534"></a><a name="p1247735715093534"></a><a href="graphic.md#ga010c178e2c1dec79e4af10cbf4545257">GetXAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p66663034093534"><a name="p66663034093534"></a><a name="p66663034093534"></a><a href="ohos-uixaxis.md">UIXAxis</a> &amp; </p>
<p id="p1073255598093534"><a name="p1073255598093534"></a><a name="p1073255598093534"></a>Obtains the x-axis instance. </p>
</td>
</tr>
<tr id="row1912321535093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1105496551093534"><a name="p1105496551093534"></a><a name="p1105496551093534"></a><a href="graphic.md#ga696227300be45585be102f6a7f66b7b1">GetYAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1783793055093534"><a name="p1783793055093534"></a><a name="p1783793055093534"></a><a href="ohos-uiyaxis.md">UIYAxis</a> &amp; </p>
<p id="p1644505171093534"><a name="p1644505171093534"></a><a name="p1644505171093534"></a>Obtains the y-axis instance. </p>
</td>
</tr>
<tr id="row486145852093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1509984456093534"><a name="p1509984456093534"></a><a name="p1509984456093534"></a><a href="graphic.md#ga7c99edd3adfb60796be92e98fd71a705">EnableReverse</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2025194803093534"><a name="p2025194803093534"></a><a name="p2025194803093534"></a>void </p>
<p id="p1009148884093534"><a name="p1009148884093534"></a><a name="p1009148884093534"></a>Enables chart reverse. </p>
</td>
</tr>
<tr id="row1052248075093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2144464088093534"><a name="p2144464088093534"></a><a name="p2144464088093534"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1436529838093534"><a name="p1436529838093534"></a><a name="p1436529838093534"></a> </p>
<p id="p1353916701093534"><a name="p1353916701093534"></a><a name="p1353916701093534"></a>A default constructor used to create a <strong id="b281887137093534"><a name="b281887137093534"></a><a name="b281887137093534"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row935364795093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841281835093534"><a name="p1841281835093534"></a><a name="p1841281835093534"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p798501988093534"><a name="p798501988093534"></a><a name="p798501988093534"></a>virtual </p>
<p id="p627192382093534"><a name="p627192382093534"></a><a name="p627192382093534"></a>A destructor used to delete the <strong id="b1864749925093534"><a name="b1864749925093534"></a><a name="b1864749925093534"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1481430866093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1428424385093534"><a name="p1428424385093534"></a><a name="p1428424385093534"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1555230675093534"><a name="p1555230675093534"></a><a name="p1555230675093534"></a>UIViewType </p>
<p id="p1638550501093534"><a name="p1638550501093534"></a><a name="p1638550501093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row506220067093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p985932294093534"><a name="p985932294093534"></a><a name="p985932294093534"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521870938093534"><a name="p1521870938093534"></a><a name="p1521870938093534"></a>virtual void </p>
<p id="p1876103475093534"><a name="p1876103475093534"></a><a name="p1876103475093534"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row344053458093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1405210418093534"><a name="p1405210418093534"></a><a name="p1405210418093534"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995420979093534"><a name="p1995420979093534"></a><a name="p1995420979093534"></a>virtual void </p>
<p id="p552088093534"><a name="p552088093534"></a><a name="p552088093534"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1382928800093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p550281795093534"><a name="p550281795093534"></a><a name="p550281795093534"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1048348199093534"><a name="p1048348199093534"></a><a name="p1048348199093534"></a>virtual void </p>
<p id="p959201290093534"><a name="p959201290093534"></a><a name="p959201290093534"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row1838244616093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p121078754093534"><a name="p121078754093534"></a><a name="p121078754093534"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p218940353093534"><a name="p218940353093534"></a><a name="p218940353093534"></a>virtual void </p>
<p id="p40187014093534"><a name="p40187014093534"></a><a name="p40187014093534"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1456142017093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401494936093534"><a name="p1401494936093534"></a><a name="p1401494936093534"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1265282803093534"><a name="p1265282803093534"></a><a name="p1265282803093534"></a>virtual void </p>
<p id="p2052659721093534"><a name="p2052659721093534"></a><a name="p2052659721093534"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row464588408093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1260249363093534"><a name="p1260249363093534"></a><a name="p1260249363093534"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1662973366093534"><a name="p1662973366093534"></a><a name="p1662973366093534"></a>virtual void </p>
<p id="p95710165093534"><a name="p95710165093534"></a><a name="p95710165093534"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row10021091093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p772966267093534"><a name="p772966267093534"></a><a name="p772966267093534"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p802615634093534"><a name="p802615634093534"></a><a name="p802615634093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p2104353062093534"><a name="p2104353062093534"></a><a name="p2104353062093534"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row976743395093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p54929300093534"><a name="p54929300093534"></a><a name="p54929300093534"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p973294812093534"><a name="p973294812093534"></a><a name="p973294812093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p848105469093534"><a name="p848105469093534"></a><a name="p848105469093534"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row1374859200093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1600174701093534"><a name="p1600174701093534"></a><a name="p1600174701093534"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343932634093534"><a name="p343932634093534"></a><a name="p343932634093534"></a>void </p>
<p id="p1735104820093534"><a name="p1735104820093534"></a><a name="p1735104820093534"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1010501107093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1797367781093534"><a name="p1797367781093534"></a><a name="p1797367781093534"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p950608304093534"><a name="p950608304093534"></a><a name="p950608304093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1369004817093534"><a name="p1369004817093534"></a><a name="p1369004817093534"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row3983911093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505255093093534"><a name="p1505255093093534"></a><a name="p1505255093093534"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p576808123093534"><a name="p576808123093534"></a><a name="p576808123093534"></a>void </p>
<p id="p1290429570093534"><a name="p1290429570093534"></a><a name="p1290429570093534"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row2104048743093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898654700093534"><a name="p1898654700093534"></a><a name="p1898654700093534"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1993363209093534"><a name="p1993363209093534"></a><a name="p1993363209093534"></a> </p>
<p id="p2098015706093534"><a name="p2098015706093534"></a><a name="p2098015706093534"></a>A default constructor used to create an <strong id="b1482284936093534"><a name="b1482284936093534"></a><a name="b1482284936093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1070895858093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390081176093534"><a name="p390081176093534"></a><a name="p390081176093534"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1842025092093534"><a name="p1842025092093534"></a><a name="p1842025092093534"></a> </p>
<p id="p843752054093534"><a name="p843752054093534"></a><a name="p843752054093534"></a>A constructor used to create an <strong id="b1767421193093534"><a name="b1767421193093534"></a><a name="b1767421193093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row832072233093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p618158006093534"><a name="p618158006093534"></a><a name="p618158006093534"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1813524174093534"><a name="p1813524174093534"></a><a name="p1813524174093534"></a>virtual </p>
<p id="p920513503093534"><a name="p920513503093534"></a><a name="p920513503093534"></a>A destructor used to delete the <strong id="b128685446093534"><a name="b128685446093534"></a><a name="b128685446093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row2107161233093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1884882363093534"><a name="p1884882363093534"></a><a name="p1884882363093534"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p376492681093534"><a name="p376492681093534"></a><a name="p376492681093534"></a>virtual void </p>
<p id="p319465491093534"><a name="p319465491093534"></a><a name="p319465491093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row457650185093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1369275284093534"><a name="p1369275284093534"></a><a name="p1369275284093534"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p660461045093534"><a name="p660461045093534"></a><a name="p660461045093534"></a>void </p>
<p id="p420888923093534"><a name="p420888923093534"></a><a name="p420888923093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1737927698093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2040921055093534"><a name="p2040921055093534"></a><a name="p2040921055093534"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1617743889093534"><a name="p1617743889093534"></a><a name="p1617743889093534"></a>void </p>
<p id="p71067466093534"><a name="p71067466093534"></a><a name="p71067466093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1162698180093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p647333934093534"><a name="p647333934093534"></a><a name="p647333934093534"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p328006243093534"><a name="p328006243093534"></a><a name="p328006243093534"></a>virtual bool </p>
<p id="p1212143030093534"><a name="p1212143030093534"></a><a name="p1212143030093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row880024528093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236752926093534"><a name="p236752926093534"></a><a name="p236752926093534"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2103603394093534"><a name="p2103603394093534"></a><a name="p2103603394093534"></a>virtual bool </p>
<p id="p851793202093534"><a name="p851793202093534"></a><a name="p851793202093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row806388350093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p293781661093534"><a name="p293781661093534"></a><a name="p293781661093534"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653041578093534"><a name="p1653041578093534"></a><a name="p1653041578093534"></a>virtual bool </p>
<p id="p1776122352093534"><a name="p1776122352093534"></a><a name="p1776122352093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row713047541093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1406428962093534"><a name="p1406428962093534"></a><a name="p1406428962093534"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1678187338093534"><a name="p1678187338093534"></a><a name="p1678187338093534"></a>virtual bool </p>
<p id="p204545129093534"><a name="p204545129093534"></a><a name="p204545129093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1022922212093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p221697492093534"><a name="p221697492093534"></a><a name="p221697492093534"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1829112966093534"><a name="p1829112966093534"></a><a name="p1829112966093534"></a>virtual void </p>
<p id="p2058322120093534"><a name="p2058322120093534"></a><a name="p2058322120093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row26510859093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p720319440093534"><a name="p720319440093534"></a><a name="p720319440093534"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2145094592093534"><a name="p2145094592093534"></a><a name="p2145094592093534"></a>virtual void </p>
<p id="p204517929093534"><a name="p204517929093534"></a><a name="p204517929093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1948747332093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p618746765093534"><a name="p618746765093534"></a><a name="p618746765093534"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1693758946093534"><a name="p1693758946093534"></a><a name="p1693758946093534"></a>virtual void </p>
<p id="p536755652093534"><a name="p536755652093534"></a><a name="p536755652093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1881372105093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p722353383093534"><a name="p722353383093534"></a><a name="p722353383093534"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p497041777093534"><a name="p497041777093534"></a><a name="p497041777093534"></a>virtual void </p>
<p id="p497426083093534"><a name="p497426083093534"></a><a name="p497426083093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row1856853577093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651404635093534"><a name="p651404635093534"></a><a name="p651404635093534"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p911806421093534"><a name="p911806421093534"></a><a name="p911806421093534"></a>void </p>
<p id="p303793153093534"><a name="p303793153093534"></a><a name="p303793153093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1915681245093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806616783093534"><a name="p1806616783093534"></a><a name="p1806616783093534"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p517039392093534"><a name="p517039392093534"></a><a name="p517039392093534"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p1308582978093534"><a name="p1308582978093534"></a><a name="p1308582978093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row883300317093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p878380916093534"><a name="p878380916093534"></a><a name="p878380916093534"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1557165717093534"><a name="p1557165717093534"></a><a name="p1557165717093534"></a>void </p>
<p id="p1947796487093534"><a name="p1947796487093534"></a><a name="p1947796487093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1733988583093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p594219714093534"><a name="p594219714093534"></a><a name="p594219714093534"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p316118661093534"><a name="p316118661093534"></a><a name="p316118661093534"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p1313427049093534"><a name="p1313427049093534"></a><a name="p1313427049093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row244626729093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p120199388093534"><a name="p120199388093534"></a><a name="p120199388093534"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p976056015093534"><a name="p976056015093534"></a><a name="p976056015093534"></a>void </p>
<p id="p202352668093534"><a name="p202352668093534"></a><a name="p202352668093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row596518204093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1227691923093534"><a name="p1227691923093534"></a><a name="p1227691923093534"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p951148526093534"><a name="p951148526093534"></a><a name="p951148526093534"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p1019551487093534"><a name="p1019551487093534"></a><a name="p1019551487093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1844777902093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1048703811093534"><a name="p1048703811093534"></a><a name="p1048703811093534"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1850992552093534"><a name="p1850992552093534"></a><a name="p1850992552093534"></a>void </p>
<p id="p1699986459093534"><a name="p1699986459093534"></a><a name="p1699986459093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row494438283093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1442745424093534"><a name="p1442745424093534"></a><a name="p1442745424093534"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074362201093534"><a name="p1074362201093534"></a><a name="p1074362201093534"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1448423011093534"><a name="p1448423011093534"></a><a name="p1448423011093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row491105862093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1570287683093534"><a name="p1570287683093534"></a><a name="p1570287683093534"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1840714913093534"><a name="p1840714913093534"></a><a name="p1840714913093534"></a>void </p>
<p id="p858988921093534"><a name="p858988921093534"></a><a name="p858988921093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1116547884093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p93294093093534"><a name="p93294093093534"></a><a name="p93294093093534"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1463033223093534"><a name="p1463033223093534"></a><a name="p1463033223093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1029222177093534"><a name="p1029222177093534"></a><a name="p1029222177093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row2024025425093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1881452466093534"><a name="p1881452466093534"></a><a name="p1881452466093534"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926173347093534"><a name="p926173347093534"></a><a name="p926173347093534"></a>void </p>
<p id="p1948627342093534"><a name="p1948627342093534"></a><a name="p1948627342093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1466022494093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106358374093534"><a name="p2106358374093534"></a><a name="p2106358374093534"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1087393185093534"><a name="p1087393185093534"></a><a name="p1087393185093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1383491727093534"><a name="p1383491727093534"></a><a name="p1383491727093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1468201515093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1779927812093534"><a name="p1779927812093534"></a><a name="p1779927812093534"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1213303910093534"><a name="p1213303910093534"></a><a name="p1213303910093534"></a>virtual void </p>
<p id="p267462026093534"><a name="p267462026093534"></a><a name="p267462026093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row715456008093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p274149050093534"><a name="p274149050093534"></a><a name="p274149050093534"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1396464331093534"><a name="p1396464331093534"></a><a name="p1396464331093534"></a>bool </p>
<p id="p1900107882093534"><a name="p1900107882093534"></a><a name="p1900107882093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1064092801093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1682001777093534"><a name="p1682001777093534"></a><a name="p1682001777093534"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p8603140093534"><a name="p8603140093534"></a><a name="p8603140093534"></a>void </p>
<p id="p1862114192093534"><a name="p1862114192093534"></a><a name="p1862114192093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row989981104093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p175387913093534"><a name="p175387913093534"></a><a name="p175387913093534"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1970657489093534"><a name="p1970657489093534"></a><a name="p1970657489093534"></a>bool </p>
<p id="p1584996650093534"><a name="p1584996650093534"></a><a name="p1584996650093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row2109894446093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p773311266093534"><a name="p773311266093534"></a><a name="p773311266093534"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p585836500093534"><a name="p585836500093534"></a><a name="p585836500093534"></a>void </p>
<p id="p840263576093534"><a name="p840263576093534"></a><a name="p840263576093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1107279179093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1266217052093534"><a name="p1266217052093534"></a><a name="p1266217052093534"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1371133741093534"><a name="p1371133741093534"></a><a name="p1371133741093534"></a>bool </p>
<p id="p37538708093534"><a name="p37538708093534"></a><a name="p37538708093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row143363058093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p106869304093534"><a name="p106869304093534"></a><a name="p106869304093534"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1361711889093534"><a name="p1361711889093534"></a><a name="p1361711889093534"></a>void </p>
<p id="p1806636814093534"><a name="p1806636814093534"></a><a name="p1806636814093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1695068607093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1199528051093534"><a name="p1199528051093534"></a><a name="p1199528051093534"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1512442596093534"><a name="p1512442596093534"></a><a name="p1512442596093534"></a>bool </p>
<p id="p1143862939093534"><a name="p1143862939093534"></a><a name="p1143862939093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1035404331093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329327405093534"><a name="p329327405093534"></a><a name="p329327405093534"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p943391278093534"><a name="p943391278093534"></a><a name="p943391278093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1804506401093534"><a name="p1804506401093534"></a><a name="p1804506401093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1744876923093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1513212423093534"><a name="p1513212423093534"></a><a name="p1513212423093534"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p68151551093534"><a name="p68151551093534"></a><a name="p68151551093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p578643145093534"><a name="p578643145093534"></a><a name="p578643145093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row595112477093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119156659093534"><a name="p1119156659093534"></a><a name="p1119156659093534"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p527611958093534"><a name="p527611958093534"></a><a name="p527611958093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1709593704093534"><a name="p1709593704093534"></a><a name="p1709593704093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row635476398093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1646828286093534"><a name="p1646828286093534"></a><a name="p1646828286093534"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p44835095093534"><a name="p44835095093534"></a><a name="p44835095093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p937065948093534"><a name="p937065948093534"></a><a name="p937065948093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row52655732093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1493582328093534"><a name="p1493582328093534"></a><a name="p1493582328093534"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1665559562093534"><a name="p1665559562093534"></a><a name="p1665559562093534"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1571728138093534"><a name="p1571728138093534"></a><a name="p1571728138093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1173804709093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p920435869093534"><a name="p920435869093534"></a><a name="p920435869093534"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1224029761093534"><a name="p1224029761093534"></a><a name="p1224029761093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p398250522093534"><a name="p398250522093534"></a><a name="p398250522093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row353967431093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1196426638093534"><a name="p1196426638093534"></a><a name="p1196426638093534"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1849648445093534"><a name="p1849648445093534"></a><a name="p1849648445093534"></a>void </p>
<p id="p1913649391093534"><a name="p1913649391093534"></a><a name="p1913649391093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row998516060093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p172576276093534"><a name="p172576276093534"></a><a name="p172576276093534"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p528271612093534"><a name="p528271612093534"></a><a name="p528271612093534"></a>virtual int16_t </p>
<p id="p55205036093534"><a name="p55205036093534"></a><a name="p55205036093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1789956678093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1417042458093534"><a name="p1417042458093534"></a><a name="p1417042458093534"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p692837705093534"><a name="p692837705093534"></a><a name="p692837705093534"></a>virtual int16_t </p>
<p id="p2023766007093534"><a name="p2023766007093534"></a><a name="p2023766007093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row48988766093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1778233068093534"><a name="p1778233068093534"></a><a name="p1778233068093534"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1574694311093534"><a name="p1574694311093534"></a><a name="p1574694311093534"></a>virtual void </p>
<p id="p602208555093534"><a name="p602208555093534"></a><a name="p602208555093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1952479645093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p741440350093534"><a name="p741440350093534"></a><a name="p741440350093534"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p774092649093534"><a name="p774092649093534"></a><a name="p774092649093534"></a>virtual void </p>
<p id="p1334744604093534"><a name="p1334744604093534"></a><a name="p1334744604093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row482609241093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1441188218093534"><a name="p1441188218093534"></a><a name="p1441188218093534"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1298026707093534"><a name="p1298026707093534"></a><a name="p1298026707093534"></a>int16_t </p>
<p id="p68196461093534"><a name="p68196461093534"></a><a name="p68196461093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1799213710093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1569672991093534"><a name="p1569672991093534"></a><a name="p1569672991093534"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p594769643093534"><a name="p594769643093534"></a><a name="p594769643093534"></a>virtual void </p>
<p id="p1195802178093534"><a name="p1195802178093534"></a><a name="p1195802178093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row991368898093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p345985287093534"><a name="p345985287093534"></a><a name="p345985287093534"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p713867329093534"><a name="p713867329093534"></a><a name="p713867329093534"></a>int16_t </p>
<p id="p1644118039093534"><a name="p1644118039093534"></a><a name="p1644118039093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1183990335093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p874413174093534"><a name="p874413174093534"></a><a name="p874413174093534"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p880427386093534"><a name="p880427386093534"></a><a name="p880427386093534"></a>virtual void </p>
<p id="p1711951919093534"><a name="p1711951919093534"></a><a name="p1711951919093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1276875803093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p528062800093534"><a name="p528062800093534"></a><a name="p528062800093534"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1444950869093534"><a name="p1444950869093534"></a><a name="p1444950869093534"></a>virtual void </p>
<p id="p1672853912093534"><a name="p1672853912093534"></a><a name="p1672853912093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1099100072093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1881651780093534"><a name="p1881651780093534"></a><a name="p1881651780093534"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p162998411093534"><a name="p162998411093534"></a><a name="p162998411093534"></a>bool </p>
<p id="p829579146093534"><a name="p829579146093534"></a><a name="p829579146093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row449281380093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1378162287093534"><a name="p1378162287093534"></a><a name="p1378162287093534"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087739427093534"><a name="p2087739427093534"></a><a name="p2087739427093534"></a>void </p>
<p id="p1433171238093534"><a name="p1433171238093534"></a><a name="p1433171238093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row428167402093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1514659035093534"><a name="p1514659035093534"></a><a name="p1514659035093534"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2045790342093534"><a name="p2045790342093534"></a><a name="p2045790342093534"></a>void </p>
<p id="p1571228385093534"><a name="p1571228385093534"></a><a name="p1571228385093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row525698331093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p408479621093534"><a name="p408479621093534"></a><a name="p408479621093534"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p69748855093534"><a name="p69748855093534"></a><a name="p69748855093534"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p85445000093534"><a name="p85445000093534"></a><a name="p85445000093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row802909102093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851530757093534"><a name="p1851530757093534"></a><a name="p1851530757093534"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809925541093534"><a name="p1809925541093534"></a><a name="p1809925541093534"></a>void </p>
<p id="p238978665093534"><a name="p238978665093534"></a><a name="p238978665093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row497213903093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1933395508093534"><a name="p1933395508093534"></a><a name="p1933395508093534"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p210983832093534"><a name="p210983832093534"></a><a name="p210983832093534"></a>const char * </p>
<p id="p1145958580093534"><a name="p1145958580093534"></a><a name="p1145958580093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row537203815093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1476204881093534"><a name="p1476204881093534"></a><a name="p1476204881093534"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1044467516093534"><a name="p1044467516093534"></a><a name="p1044467516093534"></a>void </p>
<p id="p2128274697093534"><a name="p2128274697093534"></a><a name="p2128274697093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1593760244093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1596306120093534"><a name="p1596306120093534"></a><a name="p1596306120093534"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1768132637093534"><a name="p1768132637093534"></a><a name="p1768132637093534"></a>int16_t </p>
<p id="p2086519855093534"><a name="p2086519855093534"></a><a name="p2086519855093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row331134251093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p989497692093534"><a name="p989497692093534"></a><a name="p989497692093534"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p209797335093534"><a name="p209797335093534"></a><a name="p209797335093534"></a>virtual void </p>
<p id="p1081998851093534"><a name="p1081998851093534"></a><a name="p1081998851093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1753787294093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p216241522093534"><a name="p216241522093534"></a><a name="p216241522093534"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p423696076093534"><a name="p423696076093534"></a><a name="p423696076093534"></a>void </p>
<p id="p1638241832093534"><a name="p1638241832093534"></a><a name="p1638241832093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row528121163093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p202018655093534"><a name="p202018655093534"></a><a name="p202018655093534"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2134244432093534"><a name="p2134244432093534"></a><a name="p2134244432093534"></a>void </p>
<p id="p122745209093534"><a name="p122745209093534"></a><a name="p122745209093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1266809521093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p541662543093534"><a name="p541662543093534"></a><a name="p541662543093534"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p305316294093534"><a name="p305316294093534"></a><a name="p305316294093534"></a>void </p>
<p id="p1259594005093534"><a name="p1259594005093534"></a><a name="p1259594005093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1706245986093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p220009375093534"><a name="p220009375093534"></a><a name="p220009375093534"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257185532093534"><a name="p257185532093534"></a><a name="p257185532093534"></a>void </p>
<p id="p886396010093534"><a name="p886396010093534"></a><a name="p886396010093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1436336871093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1263586342093534"><a name="p1263586342093534"></a><a name="p1263586342093534"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p891650310093534"><a name="p891650310093534"></a><a name="p891650310093534"></a>void </p>
<p id="p1598640106093534"><a name="p1598640106093534"></a><a name="p1598640106093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row185476987093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p438202304093534"><a name="p438202304093534"></a><a name="p438202304093534"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p232632309093534"><a name="p232632309093534"></a><a name="p232632309093534"></a>void </p>
<p id="p1584353990093534"><a name="p1584353990093534"></a><a name="p1584353990093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1855456753093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p242973240093534"><a name="p242973240093534"></a><a name="p242973240093534"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1082029008093534"><a name="p1082029008093534"></a><a name="p1082029008093534"></a>void </p>
<p id="p818612211093534"><a name="p818612211093534"></a><a name="p818612211093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1242859889093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1230167595093534"><a name="p1230167595093534"></a><a name="p1230167595093534"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p981075781093534"><a name="p981075781093534"></a><a name="p981075781093534"></a>void </p>
<p id="p1718677365093534"><a name="p1718677365093534"></a><a name="p1718677365093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1501493608093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1521779221093534"><a name="p1521779221093534"></a><a name="p1521779221093534"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p965148229093534"><a name="p965148229093534"></a><a name="p965148229093534"></a>void </p>
<p id="p1037519177093534"><a name="p1037519177093534"></a><a name="p1037519177093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row41879308093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1949307013093534"><a name="p1949307013093534"></a><a name="p1949307013093534"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p237619844093534"><a name="p237619844093534"></a><a name="p237619844093534"></a>void </p>
<p id="p1779509903093534"><a name="p1779509903093534"></a><a name="p1779509903093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1598669700093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p530498825093534"><a name="p530498825093534"></a><a name="p530498825093534"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1036177107093534"><a name="p1036177107093534"></a><a name="p1036177107093534"></a>void </p>
<p id="p1197160862093534"><a name="p1197160862093534"></a><a name="p1197160862093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1870196740093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1333178428093534"><a name="p1333178428093534"></a><a name="p1333178428093534"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p320055543093534"><a name="p320055543093534"></a><a name="p320055543093534"></a>void </p>
<p id="p629268697093534"><a name="p629268697093534"></a><a name="p629268697093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row2136078746093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1282669274093534"><a name="p1282669274093534"></a><a name="p1282669274093534"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1174532080093534"><a name="p1174532080093534"></a><a name="p1174532080093534"></a>void </p>
<p id="p2028964963093534"><a name="p2028964963093534"></a><a name="p2028964963093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1681440484093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p46510867093534"><a name="p46510867093534"></a><a name="p46510867093534"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p89286327093534"><a name="p89286327093534"></a><a name="p89286327093534"></a>void </p>
<p id="p351585415093534"><a name="p351585415093534"></a><a name="p351585415093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1314725883093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1155675312093534"><a name="p1155675312093534"></a><a name="p1155675312093534"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2048868358093534"><a name="p2048868358093534"></a><a name="p2048868358093534"></a>void </p>
<p id="p993098245093534"><a name="p993098245093534"></a><a name="p993098245093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1004542850093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p9939568093534"><a name="p9939568093534"></a><a name="p9939568093534"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p341209921093534"><a name="p341209921093534"></a><a name="p341209921093534"></a>virtual void </p>
<p id="p1228210528093534"><a name="p1228210528093534"></a><a name="p1228210528093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1094284893093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p663543735093534"><a name="p663543735093534"></a><a name="p663543735093534"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p137903184093534"><a name="p137903184093534"></a><a name="p137903184093534"></a>virtual void </p>
<p id="p100540003093534"><a name="p100540003093534"></a><a name="p100540003093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1334971632093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1787717395093534"><a name="p1787717395093534"></a><a name="p1787717395093534"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1264178656093534"><a name="p1264178656093534"></a><a name="p1264178656093534"></a>virtual int64_t </p>
<p id="p1450412526093534"><a name="p1450412526093534"></a><a name="p1450412526093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1729741526093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1132120560093534"><a name="p1132120560093534"></a><a name="p1132120560093534"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p333462749093534"><a name="p333462749093534"></a><a name="p333462749093534"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p1173446281093534"><a name="p1173446281093534"></a><a name="p1173446281093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row248047977093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p689988762093534"><a name="p689988762093534"></a><a name="p689988762093534"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1362438786093534"><a name="p1362438786093534"></a><a name="p1362438786093534"></a>void * </p>
<p id="p1815327900093534"><a name="p1815327900093534"></a><a name="p1815327900093534"></a>Overrides the <strong id="b1700059003093534"><a name="b1700059003093534"></a><a name="b1700059003093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1242091035093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p215933802093534"><a name="p215933802093534"></a><a name="p215933802093534"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1451577347093534"><a name="p1451577347093534"></a><a name="p1451577347093534"></a>void </p>
<p id="p1353175821093534"><a name="p1353175821093534"></a><a name="p1353175821093534"></a>Overrides the <strong id="b1255699272093534"><a name="b1255699272093534"></a><a name="b1255699272093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1128303073093534"></a>
<table><thead align="left"><tr id="row505582749093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1304851095093534"><a name="p1304851095093534"></a><a name="p1304851095093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2142372579093534"><a name="p2142372579093534"></a><a name="p2142372579093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1818901391093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1994520578093534"><a name="p1994520578093534"></a><a name="p1994520578093534"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1935844584093534"><a name="p1935844584093534"></a><a name="p1935844584093534"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row895309489093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p565952826093534"><a name="p565952826093534"></a><a name="p565952826093534"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2062957031093534"><a name="p2062957031093534"></a><a name="p2062957031093534"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row772967319093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1579559852093534"><a name="p1579559852093534"></a><a name="p1579559852093534"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1542732050093534"><a name="p1542732050093534"></a><a name="p1542732050093534"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row1120904358093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p212265894093534"><a name="p212265894093534"></a><a name="p212265894093534"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278393445093534"><a name="p278393445093534"></a><a name="p278393445093534"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row71718920093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1049902893093534"><a name="p1049902893093534"></a><a name="p1049902893093534"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1404065604093534"><a name="p1404065604093534"></a><a name="p1404065604093534"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1641462649093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1865809631093534"><a name="p1865809631093534"></a><a name="p1865809631093534"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p930675080093534"><a name="p930675080093534"></a><a name="p930675080093534"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row682078238093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1990394891093534"><a name="p1990394891093534"></a><a name="p1990394891093534"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1108527157093534"><a name="p1108527157093534"></a><a name="p1108527157093534"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1151046617093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1151346716093534"><a name="p1151346716093534"></a><a name="p1151346716093534"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p923062249093534"><a name="p923062249093534"></a><a name="p923062249093534"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

