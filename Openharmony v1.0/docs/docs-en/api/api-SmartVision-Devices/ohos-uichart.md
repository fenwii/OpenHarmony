# OHOS::UIChart<a name="EN-US_TOPIC_0000001055039538"></a>

## **Overview**<a name="section1663782380093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the chart class and provides functions such as adding and deleting data sets to display a chart. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section123998803093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table332612537093533"></a>
<table><thead align="left"><tr id="row1379056844093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1993994270093533"><a name="p1993994270093533"></a><a name="p1993994270093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p287561599093533"><a name="p287561599093533"></a><a name="p287561599093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2004027672093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290877531093533"><a name="p1290877531093533"></a><a name="p1290877531093533"></a><a href="graphic.md#ga3ab02ed367123e4f84e5ab145f5ed949">UIChart</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1985066312093533"><a name="p1985066312093533"></a><a name="p1985066312093533"></a> </p>
<p id="p1223243426093533"><a name="p1223243426093533"></a><a name="p1223243426093533"></a>A constructor used to create a <strong id="b1806595690093533"><a name="b1806595690093533"></a><a name="b1806595690093533"></a><a href="ohos-uichart.md">UIChart</a></strong> instance. </p>
</td>
</tr>
<tr id="row841425610093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1485626644093533"><a name="p1485626644093533"></a><a name="p1485626644093533"></a><a href="graphic.md#gab5d79c4736d822116dcdd7ed6e45294e">~UIChart</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p756181162093533"><a name="p756181162093533"></a><a name="p756181162093533"></a>virtual </p>
<p id="p309728074093533"><a name="p309728074093533"></a><a name="p309728074093533"></a>A destructor used to delete the <strong id="b1452236984093533"><a name="b1452236984093533"></a><a name="b1452236984093533"></a><a href="ohos-uichart.md">UIChart</a></strong> instance. </p>
</td>
</tr>
<tr id="row1205539459093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p279598627093533"><a name="p279598627093533"></a><a name="p279598627093533"></a><a href="graphic.md#gaea65298b6e4a71a2de65c13e1b14ed7b">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2026746437093533"><a name="p2026746437093533"></a><a name="p2026746437093533"></a>UIViewType </p>
<p id="p36053305093533"><a name="p36053305093533"></a><a name="p36053305093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row2144681482093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1837905732093533"><a name="p1837905732093533"></a><a name="p1837905732093533"></a><a href="graphic.md#ga54b3c4122ebaeefe74587ca69aa98600">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p285593245093533"><a name="p285593245093533"></a><a name="p285593245093533"></a>void </p>
<p id="p351377083093533"><a name="p351377083093533"></a><a name="p351377083093533"></a>Sets the height for this component. </p>
</td>
</tr>
<tr id="row1428708880093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521719897093533"><a name="p521719897093533"></a><a name="p521719897093533"></a><a href="graphic.md#ga2ae317808111cd58e6ba93e030f23111">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989413334093533"><a name="p1989413334093533"></a><a name="p1989413334093533"></a>void </p>
<p id="p1821037952093533"><a name="p1821037952093533"></a><a name="p1821037952093533"></a>Sets the width for this component. </p>
</td>
</tr>
<tr id="row1451240275093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1978676595093533"><a name="p1978676595093533"></a><a name="p1978676595093533"></a><a href="graphic.md#ga9a8287a522f00bb3dbe60af8f242054a">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p354368605093533"><a name="p354368605093533"></a><a name="p354368605093533"></a>bool </p>
<p id="p184603125093533"><a name="p184603125093533"></a><a name="p184603125093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1988579429093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2018002292093533"><a name="p2018002292093533"></a><a name="p2018002292093533"></a><a href="graphic.md#ga5c101948cb2cfb8394af0bcb56f65efb">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1773732477093533"><a name="p1773732477093533"></a><a name="p1773732477093533"></a>void </p>
<p id="p719966215093533"><a name="p719966215093533"></a><a name="p719966215093533"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1143826180093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1165065426093533"><a name="p1165065426093533"></a><a name="p1165065426093533"></a><a href="graphic.md#gafc510047aac4e7eebd5b229e726ef762">AddDataSerial</a> (<a href="ohos-uichartdataserial.md">UIChartDataSerial</a> *dataSerial)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1324529229093533"><a name="p1324529229093533"></a><a name="p1324529229093533"></a>virtual bool </p>
<p id="p967096506093533"><a name="p967096506093533"></a><a name="p967096506093533"></a>Adds a data set. </p>
</td>
</tr>
<tr id="row1254569300093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1995263455093533"><a name="p1995263455093533"></a><a name="p1995263455093533"></a><a href="graphic.md#ga2af81fbcd6a17ef250bf07e2d7606b8d">DeleteDataSerial</a> (<a href="ohos-uichartdataserial.md">UIChartDataSerial</a> *dataSerial)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1689742385093533"><a name="p1689742385093533"></a><a name="p1689742385093533"></a>virtual bool </p>
<p id="p1822455560093533"><a name="p1822455560093533"></a><a name="p1822455560093533"></a>Deletes a data set. </p>
</td>
</tr>
<tr id="row1695826026093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1309666363093533"><a name="p1309666363093533"></a><a name="p1309666363093533"></a><a href="graphic.md#gae2752857fbcb9f1541cd811321bfc2c6">ClearDataSerial</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2000742730093533"><a name="p2000742730093533"></a><a name="p2000742730093533"></a>virtual void </p>
<p id="p572140642093533"><a name="p572140642093533"></a><a name="p572140642093533"></a>Clears all data sets. </p>
</td>
</tr>
<tr id="row1928837854093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2084098529093533"><a name="p2084098529093533"></a><a name="p2084098529093533"></a><a href="graphic.md#gaaab35011c82308c770cf5c15641fe21c">RefreshChart</a> ()=0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1298024957093533"><a name="p1298024957093533"></a><a name="p1298024957093533"></a>virtual void </p>
<p id="p1278029030093533"><a name="p1278029030093533"></a><a name="p1278029030093533"></a>Refreshes a chart and redraws the dirty region. </p>
</td>
</tr>
<tr id="row716015774093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p701677494093533"><a name="p701677494093533"></a><a name="p701677494093533"></a><a href="graphic.md#ga010c178e2c1dec79e4af10cbf4545257">GetXAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802853779093533"><a name="p1802853779093533"></a><a name="p1802853779093533"></a><a href="ohos-uixaxis.md">UIXAxis</a> &amp; </p>
<p id="p69239091093533"><a name="p69239091093533"></a><a name="p69239091093533"></a>Obtains the x-axis instance. </p>
</td>
</tr>
<tr id="row129651312093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1325631716093533"><a name="p1325631716093533"></a><a name="p1325631716093533"></a><a href="graphic.md#ga696227300be45585be102f6a7f66b7b1">GetYAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p766303986093533"><a name="p766303986093533"></a><a name="p766303986093533"></a><a href="ohos-uiyaxis.md">UIYAxis</a> &amp; </p>
<p id="p1978870965093533"><a name="p1978870965093533"></a><a name="p1978870965093533"></a>Obtains the y-axis instance. </p>
</td>
</tr>
<tr id="row1054201283093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p701276728093533"><a name="p701276728093533"></a><a name="p701276728093533"></a><a href="graphic.md#ga7c99edd3adfb60796be92e98fd71a705">EnableReverse</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p946158582093533"><a name="p946158582093533"></a><a name="p946158582093533"></a>void </p>
<p id="p1431884052093533"><a name="p1431884052093533"></a><a name="p1431884052093533"></a>Enables chart reverse. </p>
</td>
</tr>
<tr id="row1770787409093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1752917490093533"><a name="p1752917490093533"></a><a name="p1752917490093533"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1710501811093533"><a name="p1710501811093533"></a><a name="p1710501811093533"></a> </p>
<p id="p218347356093533"><a name="p218347356093533"></a><a name="p218347356093533"></a>A default constructor used to create a <strong id="b1372233611093533"><a name="b1372233611093533"></a><a name="b1372233611093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row748046698093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1937839601093533"><a name="p1937839601093533"></a><a name="p1937839601093533"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059520323093533"><a name="p1059520323093533"></a><a name="p1059520323093533"></a>virtual </p>
<p id="p1240435405093533"><a name="p1240435405093533"></a><a name="p1240435405093533"></a>A destructor used to delete the <strong id="b1361867949093533"><a name="b1361867949093533"></a><a name="b1361867949093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1631400700093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p918714861093533"><a name="p918714861093533"></a><a name="p918714861093533"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p127442565093533"><a name="p127442565093533"></a><a name="p127442565093533"></a>UIViewType </p>
<p id="p1149701542093533"><a name="p1149701542093533"></a><a name="p1149701542093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row888547262093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p587927232093533"><a name="p587927232093533"></a><a name="p587927232093533"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1773947585093533"><a name="p1773947585093533"></a><a name="p1773947585093533"></a>virtual void </p>
<p id="p1672484336093533"><a name="p1672484336093533"></a><a name="p1672484336093533"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row1494505471093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p222222107093533"><a name="p222222107093533"></a><a name="p222222107093533"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1250771283093533"><a name="p1250771283093533"></a><a name="p1250771283093533"></a>virtual void </p>
<p id="p1528109295093533"><a name="p1528109295093533"></a><a name="p1528109295093533"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row234533107093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2065735145093533"><a name="p2065735145093533"></a><a name="p2065735145093533"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p305781965093533"><a name="p305781965093533"></a><a name="p305781965093533"></a>virtual void </p>
<p id="p1127492534093533"><a name="p1127492534093533"></a><a name="p1127492534093533"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row1498395725093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p51695653093533"><a name="p51695653093533"></a><a name="p51695653093533"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p669667457093533"><a name="p669667457093533"></a><a name="p669667457093533"></a>virtual void </p>
<p id="p188139200093533"><a name="p188139200093533"></a><a name="p188139200093533"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1195315341093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1814703579093533"><a name="p1814703579093533"></a><a name="p1814703579093533"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p109770994093533"><a name="p109770994093533"></a><a name="p109770994093533"></a>virtual void </p>
<p id="p1293641957093533"><a name="p1293641957093533"></a><a name="p1293641957093533"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1005079716093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2118606400093533"><a name="p2118606400093533"></a><a name="p2118606400093533"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1880996207093533"><a name="p1880996207093533"></a><a name="p1880996207093533"></a>virtual void </p>
<p id="p1993154305093533"><a name="p1993154305093533"></a><a name="p1993154305093533"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row5956067093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p915879529093533"><a name="p915879529093533"></a><a name="p915879529093533"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1219519210093533"><a name="p1219519210093533"></a><a name="p1219519210093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1754292852093533"><a name="p1754292852093533"></a><a name="p1754292852093533"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row2135838606093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1350606724093533"><a name="p1350606724093533"></a><a name="p1350606724093533"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1487569067093533"><a name="p1487569067093533"></a><a name="p1487569067093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p943770910093533"><a name="p943770910093533"></a><a name="p943770910093533"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row1470381748093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1084169975093533"><a name="p1084169975093533"></a><a name="p1084169975093533"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p397234234093533"><a name="p397234234093533"></a><a name="p397234234093533"></a>void </p>
<p id="p1564066166093533"><a name="p1564066166093533"></a><a name="p1564066166093533"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1767771313093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p412720665093533"><a name="p412720665093533"></a><a name="p412720665093533"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1594134224093533"><a name="p1594134224093533"></a><a name="p1594134224093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p999486682093533"><a name="p999486682093533"></a><a name="p999486682093533"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row383753433093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p650165400093533"><a name="p650165400093533"></a><a name="p650165400093533"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p776462065093533"><a name="p776462065093533"></a><a name="p776462065093533"></a>void </p>
<p id="p307928350093533"><a name="p307928350093533"></a><a name="p307928350093533"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row1756216277093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1949180744093533"><a name="p1949180744093533"></a><a name="p1949180744093533"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989479862093533"><a name="p1989479862093533"></a><a name="p1989479862093533"></a> </p>
<p id="p1887496670093533"><a name="p1887496670093533"></a><a name="p1887496670093533"></a>A default constructor used to create an <strong id="b1687075335093533"><a name="b1687075335093533"></a><a name="b1687075335093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row15788715093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p961878069093533"><a name="p961878069093533"></a><a name="p961878069093533"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2082508116093533"><a name="p2082508116093533"></a><a name="p2082508116093533"></a> </p>
<p id="p340867512093533"><a name="p340867512093533"></a><a name="p340867512093533"></a>A constructor used to create an <strong id="b1845198963093533"><a name="b1845198963093533"></a><a name="b1845198963093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1753959887093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2125000911093533"><a name="p2125000911093533"></a><a name="p2125000911093533"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2017269879093533"><a name="p2017269879093533"></a><a name="p2017269879093533"></a>virtual </p>
<p id="p24681021093533"><a name="p24681021093533"></a><a name="p24681021093533"></a>A destructor used to delete the <strong id="b1076996152093533"><a name="b1076996152093533"></a><a name="b1076996152093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1304447522093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1858024381093533"><a name="p1858024381093533"></a><a name="p1858024381093533"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1351130853093533"><a name="p1351130853093533"></a><a name="p1351130853093533"></a>virtual void </p>
<p id="p1725518351093533"><a name="p1725518351093533"></a><a name="p1725518351093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1084453930093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p265306763093533"><a name="p265306763093533"></a><a name="p265306763093533"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1823643603093533"><a name="p1823643603093533"></a><a name="p1823643603093533"></a>virtual void </p>
<p id="p1838335785093533"><a name="p1838335785093533"></a><a name="p1838335785093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1805112252093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1414710925093533"><a name="p1414710925093533"></a><a name="p1414710925093533"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1261435234093533"><a name="p1261435234093533"></a><a name="p1261435234093533"></a>void </p>
<p id="p1470147177093533"><a name="p1470147177093533"></a><a name="p1470147177093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row173060289093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p684796841093533"><a name="p684796841093533"></a><a name="p684796841093533"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2077689451093533"><a name="p2077689451093533"></a><a name="p2077689451093533"></a>void </p>
<p id="p485501772093533"><a name="p485501772093533"></a><a name="p485501772093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row683482596093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p586237922093533"><a name="p586237922093533"></a><a name="p586237922093533"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9782581093533"><a name="p9782581093533"></a><a name="p9782581093533"></a>virtual bool </p>
<p id="p1806201885093533"><a name="p1806201885093533"></a><a name="p1806201885093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1291996903093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2008259817093533"><a name="p2008259817093533"></a><a name="p2008259817093533"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2130458028093533"><a name="p2130458028093533"></a><a name="p2130458028093533"></a>virtual bool </p>
<p id="p1175399872093533"><a name="p1175399872093533"></a><a name="p1175399872093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row821171612093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p711752485093533"><a name="p711752485093533"></a><a name="p711752485093533"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p563711558093533"><a name="p563711558093533"></a><a name="p563711558093533"></a>virtual bool </p>
<p id="p742365350093533"><a name="p742365350093533"></a><a name="p742365350093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row772482775093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1225774522093533"><a name="p1225774522093533"></a><a name="p1225774522093533"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1242350637093533"><a name="p1242350637093533"></a><a name="p1242350637093533"></a>virtual bool </p>
<p id="p1964340402093533"><a name="p1964340402093533"></a><a name="p1964340402093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row639168590093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2024734745093533"><a name="p2024734745093533"></a><a name="p2024734745093533"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1365494580093533"><a name="p1365494580093533"></a><a name="p1365494580093533"></a>virtual void </p>
<p id="p65763952093533"><a name="p65763952093533"></a><a name="p65763952093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row397847099093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1665732570093533"><a name="p1665732570093533"></a><a name="p1665732570093533"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1528392192093533"><a name="p1528392192093533"></a><a name="p1528392192093533"></a>virtual void </p>
<p id="p1476355955093533"><a name="p1476355955093533"></a><a name="p1476355955093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1937487284093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1612380429093533"><a name="p1612380429093533"></a><a name="p1612380429093533"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1056227511093533"><a name="p1056227511093533"></a><a name="p1056227511093533"></a>virtual void </p>
<p id="p725189785093533"><a name="p725189785093533"></a><a name="p725189785093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1342576796093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1510825765093533"><a name="p1510825765093533"></a><a name="p1510825765093533"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p897503731093533"><a name="p897503731093533"></a><a name="p897503731093533"></a>virtual void </p>
<p id="p88385372093533"><a name="p88385372093533"></a><a name="p88385372093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row363984346093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1249751483093533"><a name="p1249751483093533"></a><a name="p1249751483093533"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1697140336093533"><a name="p1697140336093533"></a><a name="p1697140336093533"></a>void </p>
<p id="p1754076716093533"><a name="p1754076716093533"></a><a name="p1754076716093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1161827567093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2121468160093533"><a name="p2121468160093533"></a><a name="p2121468160093533"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p677159013093533"><a name="p677159013093533"></a><a name="p677159013093533"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p2044738560093533"><a name="p2044738560093533"></a><a name="p2044738560093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row571959871093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p261592312093533"><a name="p261592312093533"></a><a name="p261592312093533"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1911029214093533"><a name="p1911029214093533"></a><a name="p1911029214093533"></a>void </p>
<p id="p1420154845093533"><a name="p1420154845093533"></a><a name="p1420154845093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row524292474093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p466242770093533"><a name="p466242770093533"></a><a name="p466242770093533"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p724487393093533"><a name="p724487393093533"></a><a name="p724487393093533"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p1082038216093533"><a name="p1082038216093533"></a><a name="p1082038216093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row968476845093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p554293638093533"><a name="p554293638093533"></a><a name="p554293638093533"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1721006916093533"><a name="p1721006916093533"></a><a name="p1721006916093533"></a>void </p>
<p id="p1049024353093533"><a name="p1049024353093533"></a><a name="p1049024353093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1445686478093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1382491677093533"><a name="p1382491677093533"></a><a name="p1382491677093533"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2124045578093533"><a name="p2124045578093533"></a><a name="p2124045578093533"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p685447806093533"><a name="p685447806093533"></a><a name="p685447806093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row2001400113093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p385444390093533"><a name="p385444390093533"></a><a name="p385444390093533"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1305939633093533"><a name="p1305939633093533"></a><a name="p1305939633093533"></a>void </p>
<p id="p877413604093533"><a name="p877413604093533"></a><a name="p877413604093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1097788428093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1894956295093533"><a name="p1894956295093533"></a><a name="p1894956295093533"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p776288491093533"><a name="p776288491093533"></a><a name="p776288491093533"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1034318949093533"><a name="p1034318949093533"></a><a name="p1034318949093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row360100596093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1106385588093533"><a name="p1106385588093533"></a><a name="p1106385588093533"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601876436093533"><a name="p1601876436093533"></a><a name="p1601876436093533"></a>void </p>
<p id="p1383772683093533"><a name="p1383772683093533"></a><a name="p1383772683093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row845457160093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413167734093533"><a name="p1413167734093533"></a><a name="p1413167734093533"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1359117826093533"><a name="p1359117826093533"></a><a name="p1359117826093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1748455816093533"><a name="p1748455816093533"></a><a name="p1748455816093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1440635075093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p333568524093533"><a name="p333568524093533"></a><a name="p333568524093533"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p469155429093533"><a name="p469155429093533"></a><a name="p469155429093533"></a>void </p>
<p id="p1042225699093533"><a name="p1042225699093533"></a><a name="p1042225699093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1018677192093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p105161782093533"><a name="p105161782093533"></a><a name="p105161782093533"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1592021063093533"><a name="p1592021063093533"></a><a name="p1592021063093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1115572594093533"><a name="p1115572594093533"></a><a name="p1115572594093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row501440295093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p823793882093533"><a name="p823793882093533"></a><a name="p823793882093533"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p282312925093533"><a name="p282312925093533"></a><a name="p282312925093533"></a>virtual void </p>
<p id="p1953432988093533"><a name="p1953432988093533"></a><a name="p1953432988093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row650083342093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1876612035093533"><a name="p1876612035093533"></a><a name="p1876612035093533"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p19506381093533"><a name="p19506381093533"></a><a name="p19506381093533"></a>bool </p>
<p id="p1447355183093533"><a name="p1447355183093533"></a><a name="p1447355183093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row422233321093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p362587966093533"><a name="p362587966093533"></a><a name="p362587966093533"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1286590468093533"><a name="p1286590468093533"></a><a name="p1286590468093533"></a>void </p>
<p id="p1374067083093533"><a name="p1374067083093533"></a><a name="p1374067083093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1721023557093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p250930802093533"><a name="p250930802093533"></a><a name="p250930802093533"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p57241567093533"><a name="p57241567093533"></a><a name="p57241567093533"></a>bool </p>
<p id="p1725515177093533"><a name="p1725515177093533"></a><a name="p1725515177093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row807452342093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p499511483093533"><a name="p499511483093533"></a><a name="p499511483093533"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2135200504093533"><a name="p2135200504093533"></a><a name="p2135200504093533"></a>void </p>
<p id="p1312496414093533"><a name="p1312496414093533"></a><a name="p1312496414093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row191256694093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p537008114093533"><a name="p537008114093533"></a><a name="p537008114093533"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650303801093533"><a name="p650303801093533"></a><a name="p650303801093533"></a>bool </p>
<p id="p398458300093533"><a name="p398458300093533"></a><a name="p398458300093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row861059479093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2027592289093533"><a name="p2027592289093533"></a><a name="p2027592289093533"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p41275220093533"><a name="p41275220093533"></a><a name="p41275220093533"></a>void </p>
<p id="p1404254725093533"><a name="p1404254725093533"></a><a name="p1404254725093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1685685099093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1388224932093533"><a name="p1388224932093533"></a><a name="p1388224932093533"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1643884229093533"><a name="p1643884229093533"></a><a name="p1643884229093533"></a>bool </p>
<p id="p561842812093533"><a name="p561842812093533"></a><a name="p561842812093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row597497742093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p323937638093533"><a name="p323937638093533"></a><a name="p323937638093533"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p463786685093533"><a name="p463786685093533"></a><a name="p463786685093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p496879417093533"><a name="p496879417093533"></a><a name="p496879417093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1805759208093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p915173525093533"><a name="p915173525093533"></a><a name="p915173525093533"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1309762572093533"><a name="p1309762572093533"></a><a name="p1309762572093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p518312811093533"><a name="p518312811093533"></a><a name="p518312811093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row312232938093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1988082154093533"><a name="p1988082154093533"></a><a name="p1988082154093533"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1458409906093533"><a name="p1458409906093533"></a><a name="p1458409906093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1694513570093533"><a name="p1694513570093533"></a><a name="p1694513570093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row719698957093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1132761030093533"><a name="p1132761030093533"></a><a name="p1132761030093533"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p724498325093533"><a name="p724498325093533"></a><a name="p724498325093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p236991462093533"><a name="p236991462093533"></a><a name="p236991462093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row869801526093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419469299093533"><a name="p419469299093533"></a><a name="p419469299093533"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1910009381093533"><a name="p1910009381093533"></a><a name="p1910009381093533"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1767338990093533"><a name="p1767338990093533"></a><a name="p1767338990093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row304203170093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p120049324093533"><a name="p120049324093533"></a><a name="p120049324093533"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p810490485093533"><a name="p810490485093533"></a><a name="p810490485093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p2086166675093533"><a name="p2086166675093533"></a><a name="p2086166675093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1514636289093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p867696780093533"><a name="p867696780093533"></a><a name="p867696780093533"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101049251093533"><a name="p101049251093533"></a><a name="p101049251093533"></a>void </p>
<p id="p1582055016093533"><a name="p1582055016093533"></a><a name="p1582055016093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1917905122093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1493753689093533"><a name="p1493753689093533"></a><a name="p1493753689093533"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p684173722093533"><a name="p684173722093533"></a><a name="p684173722093533"></a>virtual int16_t </p>
<p id="p1501873091093533"><a name="p1501873091093533"></a><a name="p1501873091093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1099656806093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1093095274093533"><a name="p1093095274093533"></a><a name="p1093095274093533"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p493620850093533"><a name="p493620850093533"></a><a name="p493620850093533"></a>virtual int16_t </p>
<p id="p972940722093533"><a name="p972940722093533"></a><a name="p972940722093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1164570159093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p841722257093533"><a name="p841722257093533"></a><a name="p841722257093533"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1100464539093533"><a name="p1100464539093533"></a><a name="p1100464539093533"></a>virtual void </p>
<p id="p1891913522093533"><a name="p1891913522093533"></a><a name="p1891913522093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1957892208093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p9819875093533"><a name="p9819875093533"></a><a name="p9819875093533"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257139310093533"><a name="p257139310093533"></a><a name="p257139310093533"></a>virtual void </p>
<p id="p1972254418093533"><a name="p1972254418093533"></a><a name="p1972254418093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row553227468093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1128948133093533"><a name="p1128948133093533"></a><a name="p1128948133093533"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1543483931093533"><a name="p1543483931093533"></a><a name="p1543483931093533"></a>int16_t </p>
<p id="p1359919119093533"><a name="p1359919119093533"></a><a name="p1359919119093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1519900746093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p934158945093533"><a name="p934158945093533"></a><a name="p934158945093533"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1776407189093533"><a name="p1776407189093533"></a><a name="p1776407189093533"></a>virtual void </p>
<p id="p1525499664093533"><a name="p1525499664093533"></a><a name="p1525499664093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row974103889093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p637035793093533"><a name="p637035793093533"></a><a name="p637035793093533"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p906995823093533"><a name="p906995823093533"></a><a name="p906995823093533"></a>int16_t </p>
<p id="p200374140093533"><a name="p200374140093533"></a><a name="p200374140093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row25672995093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p198961873093533"><a name="p198961873093533"></a><a name="p198961873093533"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567647631093533"><a name="p1567647631093533"></a><a name="p1567647631093533"></a>virtual void </p>
<p id="p1426895542093533"><a name="p1426895542093533"></a><a name="p1426895542093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1162553299093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p918820593093533"><a name="p918820593093533"></a><a name="p918820593093533"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1184798560093533"><a name="p1184798560093533"></a><a name="p1184798560093533"></a>virtual void </p>
<p id="p1994200405093533"><a name="p1994200405093533"></a><a name="p1994200405093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1605201176093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2023246418093533"><a name="p2023246418093533"></a><a name="p2023246418093533"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p991788178093533"><a name="p991788178093533"></a><a name="p991788178093533"></a>bool </p>
<p id="p273391065093533"><a name="p273391065093533"></a><a name="p273391065093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1925227023093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1922656028093533"><a name="p1922656028093533"></a><a name="p1922656028093533"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1116333293093533"><a name="p1116333293093533"></a><a name="p1116333293093533"></a>void </p>
<p id="p952108243093533"><a name="p952108243093533"></a><a name="p952108243093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1400234721093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1544467568093533"><a name="p1544467568093533"></a><a name="p1544467568093533"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p153381679093533"><a name="p153381679093533"></a><a name="p153381679093533"></a>void </p>
<p id="p1769149280093533"><a name="p1769149280093533"></a><a name="p1769149280093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1885530625093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1729596890093533"><a name="p1729596890093533"></a><a name="p1729596890093533"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p630334878093533"><a name="p630334878093533"></a><a name="p630334878093533"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p378933647093533"><a name="p378933647093533"></a><a name="p378933647093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1911225566093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p555072944093533"><a name="p555072944093533"></a><a name="p555072944093533"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1035288722093533"><a name="p1035288722093533"></a><a name="p1035288722093533"></a>void </p>
<p id="p1556953808093533"><a name="p1556953808093533"></a><a name="p1556953808093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1372715719093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p289014027093533"><a name="p289014027093533"></a><a name="p289014027093533"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999881912093533"><a name="p1999881912093533"></a><a name="p1999881912093533"></a>const char * </p>
<p id="p1725676697093533"><a name="p1725676697093533"></a><a name="p1725676697093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1444375621093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1919935739093533"><a name="p1919935739093533"></a><a name="p1919935739093533"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1881164488093533"><a name="p1881164488093533"></a><a name="p1881164488093533"></a>void </p>
<p id="p227937463093533"><a name="p227937463093533"></a><a name="p227937463093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row2008195090093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1124460487093533"><a name="p1124460487093533"></a><a name="p1124460487093533"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p927775118093533"><a name="p927775118093533"></a><a name="p927775118093533"></a>int16_t </p>
<p id="p390860441093533"><a name="p390860441093533"></a><a name="p390860441093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row979667908093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851399661093533"><a name="p1851399661093533"></a><a name="p1851399661093533"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1730387983093533"><a name="p1730387983093533"></a><a name="p1730387983093533"></a>virtual void </p>
<p id="p1848123718093533"><a name="p1848123718093533"></a><a name="p1848123718093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row105712421093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p743249301093533"><a name="p743249301093533"></a><a name="p743249301093533"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1679231153093533"><a name="p1679231153093533"></a><a name="p1679231153093533"></a>void </p>
<p id="p1591286836093533"><a name="p1591286836093533"></a><a name="p1591286836093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1382302117093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2105640337093533"><a name="p2105640337093533"></a><a name="p2105640337093533"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p266465984093533"><a name="p266465984093533"></a><a name="p266465984093533"></a>void </p>
<p id="p1636039806093533"><a name="p1636039806093533"></a><a name="p1636039806093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row432466545093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p537692214093533"><a name="p537692214093533"></a><a name="p537692214093533"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1201079864093533"><a name="p1201079864093533"></a><a name="p1201079864093533"></a>void </p>
<p id="p928169364093533"><a name="p928169364093533"></a><a name="p928169364093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row280715277093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p527925095093533"><a name="p527925095093533"></a><a name="p527925095093533"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p417432133093533"><a name="p417432133093533"></a><a name="p417432133093533"></a>void </p>
<p id="p1761378281093533"><a name="p1761378281093533"></a><a name="p1761378281093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1425152846093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p220409592093533"><a name="p220409592093533"></a><a name="p220409592093533"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1196233106093533"><a name="p1196233106093533"></a><a name="p1196233106093533"></a>void </p>
<p id="p242414722093533"><a name="p242414722093533"></a><a name="p242414722093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1906421281093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p966892867093533"><a name="p966892867093533"></a><a name="p966892867093533"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p512965735093533"><a name="p512965735093533"></a><a name="p512965735093533"></a>void </p>
<p id="p1571839126093533"><a name="p1571839126093533"></a><a name="p1571839126093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1606556388093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1741044334093533"><a name="p1741044334093533"></a><a name="p1741044334093533"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p801969195093533"><a name="p801969195093533"></a><a name="p801969195093533"></a>void </p>
<p id="p1941492554093533"><a name="p1941492554093533"></a><a name="p1941492554093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1291343209093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1830640115093533"><a name="p1830640115093533"></a><a name="p1830640115093533"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1837436423093533"><a name="p1837436423093533"></a><a name="p1837436423093533"></a>void </p>
<p id="p63220142093533"><a name="p63220142093533"></a><a name="p63220142093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1978761566093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p980837906093533"><a name="p980837906093533"></a><a name="p980837906093533"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1458006958093533"><a name="p1458006958093533"></a><a name="p1458006958093533"></a>void </p>
<p id="p518842159093533"><a name="p518842159093533"></a><a name="p518842159093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1362734608093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p327952954093533"><a name="p327952954093533"></a><a name="p327952954093533"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2038808821093533"><a name="p2038808821093533"></a><a name="p2038808821093533"></a>void </p>
<p id="p782812012093533"><a name="p782812012093533"></a><a name="p782812012093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row861103833093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p11495493093533"><a name="p11495493093533"></a><a name="p11495493093533"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1722285984093533"><a name="p1722285984093533"></a><a name="p1722285984093533"></a>void </p>
<p id="p896617951093533"><a name="p896617951093533"></a><a name="p896617951093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row431466146093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p386388433093533"><a name="p386388433093533"></a><a name="p386388433093533"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2098182438093533"><a name="p2098182438093533"></a><a name="p2098182438093533"></a>void </p>
<p id="p1621173472093533"><a name="p1621173472093533"></a><a name="p1621173472093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1403184365093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1070935350093533"><a name="p1070935350093533"></a><a name="p1070935350093533"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p553053969093533"><a name="p553053969093533"></a><a name="p553053969093533"></a>void </p>
<p id="p722565734093533"><a name="p722565734093533"></a><a name="p722565734093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row97362427093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p678442907093533"><a name="p678442907093533"></a><a name="p678442907093533"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1319773870093533"><a name="p1319773870093533"></a><a name="p1319773870093533"></a>void </p>
<p id="p6535278093533"><a name="p6535278093533"></a><a name="p6535278093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1723295957093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p588593391093533"><a name="p588593391093533"></a><a name="p588593391093533"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p455145458093533"><a name="p455145458093533"></a><a name="p455145458093533"></a>void </p>
<p id="p651358512093533"><a name="p651358512093533"></a><a name="p651358512093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row582164185093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1298284764093533"><a name="p1298284764093533"></a><a name="p1298284764093533"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p320825953093533"><a name="p320825953093533"></a><a name="p320825953093533"></a>virtual void </p>
<p id="p822065298093533"><a name="p822065298093533"></a><a name="p822065298093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1978349380093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p585768686093533"><a name="p585768686093533"></a><a name="p585768686093533"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1790566750093533"><a name="p1790566750093533"></a><a name="p1790566750093533"></a>virtual void </p>
<p id="p1349955532093533"><a name="p1349955532093533"></a><a name="p1349955532093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row2085985763093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p545021117093533"><a name="p545021117093533"></a><a name="p545021117093533"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p110197885093533"><a name="p110197885093533"></a><a name="p110197885093533"></a>virtual int64_t </p>
<p id="p1216150569093533"><a name="p1216150569093533"></a><a name="p1216150569093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row754206625093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1856576250093533"><a name="p1856576250093533"></a><a name="p1856576250093533"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514823440093533"><a name="p514823440093533"></a><a name="p514823440093533"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p998635176093533"><a name="p998635176093533"></a><a name="p998635176093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1308897589093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1983617014093533"><a name="p1983617014093533"></a><a name="p1983617014093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p882447742093533"><a name="p882447742093533"></a><a name="p882447742093533"></a>void * </p>
<p id="p1871473630093533"><a name="p1871473630093533"></a><a name="p1871473630093533"></a>Overrides the <strong id="b1967480895093533"><a name="b1967480895093533"></a><a name="b1967480895093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1186039001093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p570074796093533"><a name="p570074796093533"></a><a name="p570074796093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91125660093533"><a name="p91125660093533"></a><a name="p91125660093533"></a>void </p>
<p id="p653831856093533"><a name="p653831856093533"></a><a name="p653831856093533"></a>Overrides the <strong id="b1677779555093533"><a name="b1677779555093533"></a><a name="b1677779555093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table737520645093533"></a>
<table><thead align="left"><tr id="row1914602520093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1432953264093533"><a name="p1432953264093533"></a><a name="p1432953264093533"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p284120523093533"><a name="p284120523093533"></a><a name="p284120523093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1240632230093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p325607752093533"><a name="p325607752093533"></a><a name="p325607752093533"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1886742316093533"><a name="p1886742316093533"></a><a name="p1886742316093533"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row695854849093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1374093696093533"><a name="p1374093696093533"></a><a name="p1374093696093533"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p74706886093533"><a name="p74706886093533"></a><a name="p74706886093533"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row914931083093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1427761237093533"><a name="p1427761237093533"></a><a name="p1427761237093533"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p293173936093533"><a name="p293173936093533"></a><a name="p293173936093533"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row1592122251093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290099325093533"><a name="p1290099325093533"></a><a name="p1290099325093533"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p307173431093533"><a name="p307173431093533"></a><a name="p307173431093533"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row794940677093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1300311075093533"><a name="p1300311075093533"></a><a name="p1300311075093533"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p89382889093533"><a name="p89382889093533"></a><a name="p89382889093533"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1695796224093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p129270415093533"><a name="p129270415093533"></a><a name="p129270415093533"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p443365535093533"><a name="p443365535093533"></a><a name="p443365535093533"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row610727180093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p490113032093533"><a name="p490113032093533"></a><a name="p490113032093533"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p619904625093533"><a name="p619904625093533"></a><a name="p619904625093533"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1570609702093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p158180652093533"><a name="p158180652093533"></a><a name="p158180652093533"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2014567714093533"><a name="p2014567714093533"></a><a name="p2014567714093533"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

