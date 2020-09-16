# OHOS::UIImageView<a name="EN-US_TOPIC_0000001054718151"></a>

## **Overview**<a name="section1545184381093534"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the functions related to an image view. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1697520539093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1214206220093534"></a>
<table><thead align="left"><tr id="row1309220909093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1009111700093534"><a name="p1009111700093534"></a><a name="p1009111700093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1700657919093534"><a name="p1700657919093534"></a><a name="p1700657919093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row170596344093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p117340242093534"><a name="p117340242093534"></a><a name="p117340242093534"></a><a href="graphic.md#ga3db47186dbc7a0cb996c23abcdaf2c38">UIImageView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2035571453093534"><a name="p2035571453093534"></a><a name="p2035571453093534"></a> </p>
<p id="p254345450093534"><a name="p254345450093534"></a><a name="p254345450093534"></a>A default constructor used to create a <strong id="b428107836093534"><a name="b428107836093534"></a><a name="b428107836093534"></a><a href="ohos-uiimageview.md">UIImageView</a></strong> instance. </p>
</td>
</tr>
<tr id="row83171197093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p146602496093534"><a name="p146602496093534"></a><a name="p146602496093534"></a><a href="graphic.md#ga8be6fe17af73ab21f97effa26dbacaca">~UIImageView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p144057403093534"><a name="p144057403093534"></a><a name="p144057403093534"></a>virtual </p>
<p id="p1274517416093534"><a name="p1274517416093534"></a><a name="p1274517416093534"></a>A destructor used to delete the <strong id="b253324117093534"><a name="b253324117093534"></a><a name="b253324117093534"></a><a href="ohos-uiimageview.md">UIImageView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1798802826093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1882017343093534"><a name="p1882017343093534"></a><a name="p1882017343093534"></a><a href="graphic.md#ga5dc99855271c582e960e0952cca8227c">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p484283091093534"><a name="p484283091093534"></a><a name="p484283091093534"></a>UIViewType </p>
<p id="p1067316781093534"><a name="p1067316781093534"></a><a name="p1067316781093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row42231833093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p972666578093534"><a name="p972666578093534"></a><a name="p972666578093534"></a><a href="graphic.md#ga20ea7dd2d8ddb16cf9750ccdcc2a2803">GetWidth</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p495218483093534"><a name="p495218483093534"></a><a name="p495218483093534"></a>int16_t </p>
<p id="p710728422093534"><a name="p710728422093534"></a><a name="p710728422093534"></a>Obtains the width of this image view. </p>
</td>
</tr>
<tr id="row1033054428093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p320195065093534"><a name="p320195065093534"></a><a name="p320195065093534"></a><a href="graphic.md#gaddc6e68c67782eaad40977c6c2256cdd">GetHeight</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1928628984093534"><a name="p1928628984093534"></a><a name="p1928628984093534"></a>int16_t </p>
<p id="p1006712077093534"><a name="p1006712077093534"></a><a name="p1006712077093534"></a>Obtains the height of this image view. </p>
</td>
</tr>
<tr id="row1062443708093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1422773765093534"><a name="p1422773765093534"></a><a name="p1422773765093534"></a><a href="graphic.md#ga5d79816831f61406c1c8bd300da9973e">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1142860152093534"><a name="p1142860152093534"></a><a name="p1142860152093534"></a>bool </p>
<p id="p1538138748093534"><a name="p1538138748093534"></a><a name="p1538138748093534"></a>Checks whether this image view needs to be covered to optimize the drawing process. </p>
</td>
</tr>
<tr id="row127683865093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1519329827093534"><a name="p1519329827093534"></a><a name="p1519329827093534"></a><a href="graphic.md#ga565cecb8ac66f2009dc4783da9bdc699">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p353207364093534"><a name="p353207364093534"></a><a name="p353207364093534"></a>void </p>
<p id="p1527800565093534"><a name="p1527800565093534"></a><a name="p1527800565093534"></a>Draws this image view. </p>
</td>
</tr>
<tr id="row1252444496093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p89144634093534"><a name="p89144634093534"></a><a name="p89144634093534"></a><a href="graphic.md#ga4e2dac4fd52a54a828f13db5ab51d110">SetSrc</a> (const char *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1621917627093534"><a name="p1621917627093534"></a><a name="p1621917627093534"></a>void </p>
<p id="p1123900158093534"><a name="p1123900158093534"></a><a name="p1123900158093534"></a>Sets the image path. </p>
</td>
</tr>
<tr id="row2052247587093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p985645550093534"><a name="p985645550093534"></a><a name="p985645550093534"></a><a href="graphic.md#ga18a9eed434132ac60c127ca1fc03e663">SetSrc</a> (const <a href="ohos-imageinfo.md">ImageInfo</a> *src)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1650724411093534"><a name="p1650724411093534"></a><a name="p1650724411093534"></a>void </p>
<p id="p425242992093534"><a name="p425242992093534"></a><a name="p425242992093534"></a>Sets the image information. </p>
</td>
</tr>
<tr id="row1585605426093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p229540576093534"><a name="p229540576093534"></a><a name="p229540576093534"></a><a href="graphic.md#gab3f60d7eff9b467c64edc90293dbb21d">SetAutoEnable</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1849514593093534"><a name="p1849514593093534"></a><a name="p1849514593093534"></a>void </p>
<p id="p1308504855093534"><a name="p1308504855093534"></a><a name="p1308504855093534"></a>Sets whether the image view size needs to be adaptive to the image size. </p>
</td>
</tr>
<tr id="row1385948946093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p255929459093534"><a name="p255929459093534"></a><a name="p255929459093534"></a><a href="graphic.md#ga339c80c2f8f05ff0d79638dc61c71d5a">SetBlurLevel</a> (BlurLevel level)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2111478506093534"><a name="p2111478506093534"></a><a name="p2111478506093534"></a>void </p>
<p id="p1081213544093534"><a name="p1081213544093534"></a><a name="p1081213544093534"></a>Sets the blur level for this image when it is rotated or scaled. </p>
</td>
</tr>
<tr id="row1159834864093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755251868093534"><a name="p1755251868093534"></a><a name="p1755251868093534"></a><a href="graphic.md#ga8c891ce7719b97f6d49b0554caa371cb">GetBlurLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1800620859093534"><a name="p1800620859093534"></a><a name="p1800620859093534"></a>BlurLevel </p>
<p id="p848521405093534"><a name="p848521405093534"></a><a name="p848521405093534"></a>Obtains the blur level of this image when it is rotated or scaled. </p>
</td>
</tr>
<tr id="row1051396640093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p903083515093534"><a name="p903083515093534"></a><a name="p903083515093534"></a><a href="graphic.md#gacd3bafd7cd7dfb83d46d4fae36eae612">SetTransformAlgorithm</a> (TransformAlgorithm algorithm)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1852647484093534"><a name="p1852647484093534"></a><a name="p1852647484093534"></a>void </p>
<p id="p802457883093534"><a name="p802457883093534"></a><a name="p802457883093534"></a>Sets the algorithm used for image rotation and scaling. </p>
</td>
</tr>
<tr id="row1433332591093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p874417008093534"><a name="p874417008093534"></a><a name="p874417008093534"></a><a href="graphic.md#gac7b75c6fa653d3ac0c8bc9062939d293">GetTransformAlgorithm</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1812512788093534"><a name="p1812512788093534"></a><a name="p1812512788093534"></a>TransformAlgorithm </p>
<p id="p151073292093534"><a name="p151073292093534"></a><a name="p151073292093534"></a>Obtains the algorithm used for image rotation and scaling. </p>
</td>
</tr>
<tr id="row112808830093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p892013356093534"><a name="p892013356093534"></a><a name="p892013356093534"></a><a href="graphic.md#ga3824befafd4f4dda003195ca2bbef399">GetPath</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1312129059093534"><a name="p1312129059093534"></a><a name="p1312129059093534"></a>const char * </p>
<p id="p1423804280093534"><a name="p1423804280093534"></a><a name="p1423804280093534"></a>Obtains the image path.</p>
</td>
</tr>
<tr id="row1292765405093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1903606121093534"><a name="p1903606121093534"></a><a name="p1903606121093534"></a><a href="graphic.md#gaa9fbde27be3e3ea2fc6b4dabbf588af8">GetImageInfo</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p891867468093534"><a name="p891867468093534"></a><a name="p891867468093534"></a>const <a href="ohos-imageinfo.md">ImageInfo</a> * </p>
<p id="p1934660954093534"><a name="p1934660954093534"></a><a name="p1934660954093534"></a>Obtains image information.</p>
</td>
</tr>
<tr id="row1578452546093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1278116661093534"><a name="p1278116661093534"></a><a name="p1278116661093534"></a><a href="graphic.md#ga07da08c8507a3dbee5c21ea0de170a16">GetSrcType</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902379297093534"><a name="p1902379297093534"></a><a name="p1902379297093534"></a>uint8_t </p>
<p id="p238063632093534"><a name="p238063632093534"></a><a name="p238063632093534"></a>Obtains the image type.</p>
</td>
</tr>
<tr id="row9770404093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429163222093534"><a name="p429163222093534"></a><a name="p429163222093534"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p562332157093534"><a name="p562332157093534"></a><a name="p562332157093534"></a> </p>
<p id="p265343508093534"><a name="p265343508093534"></a><a name="p265343508093534"></a>A default constructor used to create an <strong id="b427085575093534"><a name="b427085575093534"></a><a name="b427085575093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1700899012093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p635775579093534"><a name="p635775579093534"></a><a name="p635775579093534"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1393275788093534"><a name="p1393275788093534"></a><a name="p1393275788093534"></a> </p>
<p id="p2125418794093534"><a name="p2125418794093534"></a><a name="p2125418794093534"></a>A constructor used to create an <strong id="b390410059093534"><a name="b390410059093534"></a><a name="b390410059093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1222284423093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1574731325093534"><a name="p1574731325093534"></a><a name="p1574731325093534"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p401651869093534"><a name="p401651869093534"></a><a name="p401651869093534"></a>virtual </p>
<p id="p273681824093534"><a name="p273681824093534"></a><a name="p273681824093534"></a>A destructor used to delete the <strong id="b979355916093534"><a name="b979355916093534"></a><a name="b979355916093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1492563518093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p558788039093534"><a name="p558788039093534"></a><a name="p558788039093534"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1964899735093534"><a name="p1964899735093534"></a><a name="p1964899735093534"></a>virtual void </p>
<p id="p727768681093534"><a name="p727768681093534"></a><a name="p727768681093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1784980455093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1182313723093534"><a name="p1182313723093534"></a><a name="p1182313723093534"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p607523037093534"><a name="p607523037093534"></a><a name="p607523037093534"></a>void </p>
<p id="p587650212093534"><a name="p587650212093534"></a><a name="p587650212093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1089459184093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1075833302093534"><a name="p1075833302093534"></a><a name="p1075833302093534"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1564480290093534"><a name="p1564480290093534"></a><a name="p1564480290093534"></a>void </p>
<p id="p652914759093534"><a name="p652914759093534"></a><a name="p652914759093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1383578839093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1472048853093534"><a name="p1472048853093534"></a><a name="p1472048853093534"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p505945374093534"><a name="p505945374093534"></a><a name="p505945374093534"></a>virtual bool </p>
<p id="p1213266804093534"><a name="p1213266804093534"></a><a name="p1213266804093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1605249611093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p65784759093534"><a name="p65784759093534"></a><a name="p65784759093534"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p731772174093534"><a name="p731772174093534"></a><a name="p731772174093534"></a>virtual bool </p>
<p id="p1945458881093534"><a name="p1945458881093534"></a><a name="p1945458881093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1866977355093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p857313488093534"><a name="p857313488093534"></a><a name="p857313488093534"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1856218556093534"><a name="p1856218556093534"></a><a name="p1856218556093534"></a>virtual bool </p>
<p id="p1052142718093534"><a name="p1052142718093534"></a><a name="p1052142718093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row843854981093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p681582577093534"><a name="p681582577093534"></a><a name="p681582577093534"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073059594093534"><a name="p2073059594093534"></a><a name="p2073059594093534"></a>virtual bool </p>
<p id="p1410825803093534"><a name="p1410825803093534"></a><a name="p1410825803093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1632636148093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1883093365093534"><a name="p1883093365093534"></a><a name="p1883093365093534"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2043325838093534"><a name="p2043325838093534"></a><a name="p2043325838093534"></a>virtual void </p>
<p id="p823437036093534"><a name="p823437036093534"></a><a name="p823437036093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row953565056093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p803864830093534"><a name="p803864830093534"></a><a name="p803864830093534"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2016595694093534"><a name="p2016595694093534"></a><a name="p2016595694093534"></a>virtual void </p>
<p id="p704207062093534"><a name="p704207062093534"></a><a name="p704207062093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1657989379093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1821767034093534"><a name="p1821767034093534"></a><a name="p1821767034093534"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p107415349093534"><a name="p107415349093534"></a><a name="p107415349093534"></a>virtual void </p>
<p id="p245818325093534"><a name="p245818325093534"></a><a name="p245818325093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row959921619093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p81096901093534"><a name="p81096901093534"></a><a name="p81096901093534"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1476676292093534"><a name="p1476676292093534"></a><a name="p1476676292093534"></a>virtual void </p>
<p id="p1201912167093534"><a name="p1201912167093534"></a><a name="p1201912167093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row818524057093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p895097066093534"><a name="p895097066093534"></a><a name="p895097066093534"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1541333674093534"><a name="p1541333674093534"></a><a name="p1541333674093534"></a>void </p>
<p id="p980281031093534"><a name="p980281031093534"></a><a name="p980281031093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1515632649093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1067634916093534"><a name="p1067634916093534"></a><a name="p1067634916093534"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1694868092093534"><a name="p1694868092093534"></a><a name="p1694868092093534"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p843323200093534"><a name="p843323200093534"></a><a name="p843323200093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row140757471093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p935923378093534"><a name="p935923378093534"></a><a name="p935923378093534"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1275874818093534"><a name="p1275874818093534"></a><a name="p1275874818093534"></a>void </p>
<p id="p257784125093534"><a name="p257784125093534"></a><a name="p257784125093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1533845330093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1542119171093534"><a name="p1542119171093534"></a><a name="p1542119171093534"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p392026962093534"><a name="p392026962093534"></a><a name="p392026962093534"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p365862176093534"><a name="p365862176093534"></a><a name="p365862176093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row442459636093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p818505924093534"><a name="p818505924093534"></a><a name="p818505924093534"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p81341093093534"><a name="p81341093093534"></a><a name="p81341093093534"></a>void </p>
<p id="p1584546217093534"><a name="p1584546217093534"></a><a name="p1584546217093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row492256698093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1096898743093534"><a name="p1096898743093534"></a><a name="p1096898743093534"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p634027619093534"><a name="p634027619093534"></a><a name="p634027619093534"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p1590542304093534"><a name="p1590542304093534"></a><a name="p1590542304093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1380378976093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p48242964093534"><a name="p48242964093534"></a><a name="p48242964093534"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p503606222093534"><a name="p503606222093534"></a><a name="p503606222093534"></a>void </p>
<p id="p1665540932093534"><a name="p1665540932093534"></a><a name="p1665540932093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row836816889093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p849143807093534"><a name="p849143807093534"></a><a name="p849143807093534"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p613316103093534"><a name="p613316103093534"></a><a name="p613316103093534"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1358518260093534"><a name="p1358518260093534"></a><a name="p1358518260093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1284007799093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p498311995093534"><a name="p498311995093534"></a><a name="p498311995093534"></a><a href="graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p786786284093534"><a name="p786786284093534"></a><a name="p786786284093534"></a>virtual void </p>
<p id="p321757673093534"><a name="p321757673093534"></a><a name="p321757673093534"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row279813323093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1046773346093534"><a name="p1046773346093534"></a><a name="p1046773346093534"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1469638817093534"><a name="p1469638817093534"></a><a name="p1469638817093534"></a>void </p>
<p id="p458043797093534"><a name="p458043797093534"></a><a name="p458043797093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row2000558170093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1839724755093534"><a name="p1839724755093534"></a><a name="p1839724755093534"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1099350190093534"><a name="p1099350190093534"></a><a name="p1099350190093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p522597840093534"><a name="p522597840093534"></a><a name="p522597840093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row213038342093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1524641922093534"><a name="p1524641922093534"></a><a name="p1524641922093534"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p823417847093534"><a name="p823417847093534"></a><a name="p823417847093534"></a>void </p>
<p id="p1588953333093534"><a name="p1588953333093534"></a><a name="p1588953333093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1084000680093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1048875268093534"><a name="p1048875268093534"></a><a name="p1048875268093534"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p376042140093534"><a name="p376042140093534"></a><a name="p376042140093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1622398436093534"><a name="p1622398436093534"></a><a name="p1622398436093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row2134288870093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p27906253093534"><a name="p27906253093534"></a><a name="p27906253093534"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448584266093534"><a name="p448584266093534"></a><a name="p448584266093534"></a>virtual void </p>
<p id="p1539982728093534"><a name="p1539982728093534"></a><a name="p1539982728093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1168315011093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1943040011093534"><a name="p1943040011093534"></a><a name="p1943040011093534"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1339705139093534"><a name="p1339705139093534"></a><a name="p1339705139093534"></a>bool </p>
<p id="p923744669093534"><a name="p923744669093534"></a><a name="p923744669093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row208945134093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p399841591093534"><a name="p399841591093534"></a><a name="p399841591093534"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p925341070093534"><a name="p925341070093534"></a><a name="p925341070093534"></a>void </p>
<p id="p810451178093534"><a name="p810451178093534"></a><a name="p810451178093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1863353611093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p278234620093534"><a name="p278234620093534"></a><a name="p278234620093534"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p162384601093534"><a name="p162384601093534"></a><a name="p162384601093534"></a>bool </p>
<p id="p1841861976093534"><a name="p1841861976093534"></a><a name="p1841861976093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row698892986093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p127206384093534"><a name="p127206384093534"></a><a name="p127206384093534"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1722780210093534"><a name="p1722780210093534"></a><a name="p1722780210093534"></a>void </p>
<p id="p2139638624093534"><a name="p2139638624093534"></a><a name="p2139638624093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row812151511093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1230494426093534"><a name="p1230494426093534"></a><a name="p1230494426093534"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2068865153093534"><a name="p2068865153093534"></a><a name="p2068865153093534"></a>bool </p>
<p id="p1617934189093534"><a name="p1617934189093534"></a><a name="p1617934189093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row472543561093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p479229587093534"><a name="p479229587093534"></a><a name="p479229587093534"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1475826459093534"><a name="p1475826459093534"></a><a name="p1475826459093534"></a>void </p>
<p id="p1106954757093534"><a name="p1106954757093534"></a><a name="p1106954757093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1331655337093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1635138057093534"><a name="p1635138057093534"></a><a name="p1635138057093534"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2126895832093534"><a name="p2126895832093534"></a><a name="p2126895832093534"></a>bool </p>
<p id="p1824311106093534"><a name="p1824311106093534"></a><a name="p1824311106093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row321487448093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1204760374093534"><a name="p1204760374093534"></a><a name="p1204760374093534"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1488089435093534"><a name="p1488089435093534"></a><a name="p1488089435093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p805046571093534"><a name="p805046571093534"></a><a name="p805046571093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1589355069093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p158612557093534"><a name="p158612557093534"></a><a name="p158612557093534"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343418208093534"><a name="p343418208093534"></a><a name="p343418208093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p394018303093534"><a name="p394018303093534"></a><a name="p394018303093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row662483769093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1106016515093534"><a name="p1106016515093534"></a><a name="p1106016515093534"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1062386241093534"><a name="p1062386241093534"></a><a name="p1062386241093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p378305418093534"><a name="p378305418093534"></a><a name="p378305418093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1944930422093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p144164295093534"><a name="p144164295093534"></a><a name="p144164295093534"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p137658990093534"><a name="p137658990093534"></a><a name="p137658990093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1913463763093534"><a name="p1913463763093534"></a><a name="p1913463763093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row2052413864093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p148804602093534"><a name="p148804602093534"></a><a name="p148804602093534"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1258197417093534"><a name="p1258197417093534"></a><a name="p1258197417093534"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p177028466093534"><a name="p177028466093534"></a><a name="p177028466093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1095457520093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1916842139093534"><a name="p1916842139093534"></a><a name="p1916842139093534"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1962544426093534"><a name="p1962544426093534"></a><a name="p1962544426093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p542883085093534"><a name="p542883085093534"></a><a name="p542883085093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1038530164093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p666690658093534"><a name="p666690658093534"></a><a name="p666690658093534"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p93627497093534"><a name="p93627497093534"></a><a name="p93627497093534"></a>void </p>
<p id="p1408763666093534"><a name="p1408763666093534"></a><a name="p1408763666093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row403486765093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p403971644093534"><a name="p403971644093534"></a><a name="p403971644093534"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p481802068093534"><a name="p481802068093534"></a><a name="p481802068093534"></a>virtual void </p>
<p id="p725493092093534"><a name="p725493092093534"></a><a name="p725493092093534"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row125907404093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1159160509093534"><a name="p1159160509093534"></a><a name="p1159160509093534"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452379737093534"><a name="p1452379737093534"></a><a name="p1452379737093534"></a>virtual void </p>
<p id="p1726987988093534"><a name="p1726987988093534"></a><a name="p1726987988093534"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1656892625093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2038604043093534"><a name="p2038604043093534"></a><a name="p2038604043093534"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p569226903093534"><a name="p569226903093534"></a><a name="p569226903093534"></a>virtual void </p>
<p id="p1568473288093534"><a name="p1568473288093534"></a><a name="p1568473288093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1028776034093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079308785093534"><a name="p2079308785093534"></a><a name="p2079308785093534"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2057602281093534"><a name="p2057602281093534"></a><a name="p2057602281093534"></a>virtual void </p>
<p id="p1288397233093534"><a name="p1288397233093534"></a><a name="p1288397233093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row104444278093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1354402645093534"><a name="p1354402645093534"></a><a name="p1354402645093534"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p258659964093534"><a name="p258659964093534"></a><a name="p258659964093534"></a>int16_t </p>
<p id="p540115190093534"><a name="p540115190093534"></a><a name="p540115190093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row124265453093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p227912061093534"><a name="p227912061093534"></a><a name="p227912061093534"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1229404238093534"><a name="p1229404238093534"></a><a name="p1229404238093534"></a>virtual void </p>
<p id="p1761440954093534"><a name="p1761440954093534"></a><a name="p1761440954093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1144629551093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p540974916093534"><a name="p540974916093534"></a><a name="p540974916093534"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1414230625093534"><a name="p1414230625093534"></a><a name="p1414230625093534"></a>int16_t </p>
<p id="p2090259789093534"><a name="p2090259789093534"></a><a name="p2090259789093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1047602511093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1377314676093534"><a name="p1377314676093534"></a><a name="p1377314676093534"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1303283519093534"><a name="p1303283519093534"></a><a name="p1303283519093534"></a>virtual void </p>
<p id="p1502276749093534"><a name="p1502276749093534"></a><a name="p1502276749093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1723695237093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1556569140093534"><a name="p1556569140093534"></a><a name="p1556569140093534"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1262116336093534"><a name="p1262116336093534"></a><a name="p1262116336093534"></a>virtual void </p>
<p id="p1502682627093534"><a name="p1502682627093534"></a><a name="p1502682627093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1948703870093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p27214644093534"><a name="p27214644093534"></a><a name="p27214644093534"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449290335093534"><a name="p449290335093534"></a><a name="p449290335093534"></a>bool </p>
<p id="p224307410093534"><a name="p224307410093534"></a><a name="p224307410093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1626748308093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2131022550093534"><a name="p2131022550093534"></a><a name="p2131022550093534"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p663958661093534"><a name="p663958661093534"></a><a name="p663958661093534"></a>void </p>
<p id="p331111915093534"><a name="p331111915093534"></a><a name="p331111915093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row36695271093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1496709021093534"><a name="p1496709021093534"></a><a name="p1496709021093534"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1608346607093534"><a name="p1608346607093534"></a><a name="p1608346607093534"></a>void </p>
<p id="p1984137522093534"><a name="p1984137522093534"></a><a name="p1984137522093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row2057858018093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p44537417093534"><a name="p44537417093534"></a><a name="p44537417093534"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p596915973093534"><a name="p596915973093534"></a><a name="p596915973093534"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p635137846093534"><a name="p635137846093534"></a><a name="p635137846093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1448860131093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1694421156093534"><a name="p1694421156093534"></a><a name="p1694421156093534"></a><a href="graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1635490170093534"><a name="p1635490170093534"></a><a name="p1635490170093534"></a>virtual <a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1679631855093534"><a name="p1679631855093534"></a><a name="p1679631855093534"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row51857240093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p713978814093534"><a name="p713978814093534"></a><a name="p713978814093534"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p570827242093534"><a name="p570827242093534"></a><a name="p570827242093534"></a>void </p>
<p id="p1079073552093534"><a name="p1079073552093534"></a><a name="p1079073552093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1835936636093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1941333275093534"><a name="p1941333275093534"></a><a name="p1941333275093534"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p865552715093534"><a name="p865552715093534"></a><a name="p865552715093534"></a>const char * </p>
<p id="p920033632093534"><a name="p920033632093534"></a><a name="p920033632093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row147803053093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1761566385093534"><a name="p1761566385093534"></a><a name="p1761566385093534"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p451010809093534"><a name="p451010809093534"></a><a name="p451010809093534"></a>void </p>
<p id="p598874440093534"><a name="p598874440093534"></a><a name="p598874440093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row250243294093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p148384542093534"><a name="p148384542093534"></a><a name="p148384542093534"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1362281905093534"><a name="p1362281905093534"></a><a name="p1362281905093534"></a>int16_t </p>
<p id="p779712963093534"><a name="p779712963093534"></a><a name="p779712963093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row2045381317093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p291384166093534"><a name="p291384166093534"></a><a name="p291384166093534"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p615406417093534"><a name="p615406417093534"></a><a name="p615406417093534"></a>virtual void </p>
<p id="p426421642093534"><a name="p426421642093534"></a><a name="p426421642093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row2087434113093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1417290323093534"><a name="p1417290323093534"></a><a name="p1417290323093534"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1660686378093534"><a name="p1660686378093534"></a><a name="p1660686378093534"></a>void </p>
<p id="p19684700093534"><a name="p19684700093534"></a><a name="p19684700093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row2011908151093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1832544535093534"><a name="p1832544535093534"></a><a name="p1832544535093534"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1557918634093534"><a name="p1557918634093534"></a><a name="p1557918634093534"></a>void </p>
<p id="p799440952093534"><a name="p799440952093534"></a><a name="p799440952093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row290277572093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1302447735093534"><a name="p1302447735093534"></a><a name="p1302447735093534"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p351543890093534"><a name="p351543890093534"></a><a name="p351543890093534"></a>void </p>
<p id="p1332886787093534"><a name="p1332886787093534"></a><a name="p1332886787093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row480284081093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p601608645093534"><a name="p601608645093534"></a><a name="p601608645093534"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p9848799093534"><a name="p9848799093534"></a><a name="p9848799093534"></a>void </p>
<p id="p489758728093534"><a name="p489758728093534"></a><a name="p489758728093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1270992399093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p500716227093534"><a name="p500716227093534"></a><a name="p500716227093534"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226272580093534"><a name="p1226272580093534"></a><a name="p1226272580093534"></a>void </p>
<p id="p1847217317093534"><a name="p1847217317093534"></a><a name="p1847217317093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row17731157093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1960174089093534"><a name="p1960174089093534"></a><a name="p1960174089093534"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p148649006093534"><a name="p148649006093534"></a><a name="p148649006093534"></a>void </p>
<p id="p248373747093534"><a name="p248373747093534"></a><a name="p248373747093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row635696620093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1155188794093534"><a name="p1155188794093534"></a><a name="p1155188794093534"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2114700078093534"><a name="p2114700078093534"></a><a name="p2114700078093534"></a>void </p>
<p id="p1858882340093534"><a name="p1858882340093534"></a><a name="p1858882340093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row37653032093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1966849229093534"><a name="p1966849229093534"></a><a name="p1966849229093534"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809117883093534"><a name="p1809117883093534"></a><a name="p1809117883093534"></a>void </p>
<p id="p627603685093534"><a name="p627603685093534"></a><a name="p627603685093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1961095339093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841634784093534"><a name="p1841634784093534"></a><a name="p1841634784093534"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2001807926093534"><a name="p2001807926093534"></a><a name="p2001807926093534"></a>void </p>
<p id="p1442043741093534"><a name="p1442043741093534"></a><a name="p1442043741093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row619760518093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p704172041093534"><a name="p704172041093534"></a><a name="p704172041093534"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p306067475093534"><a name="p306067475093534"></a><a name="p306067475093534"></a>void </p>
<p id="p1079924914093534"><a name="p1079924914093534"></a><a name="p1079924914093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row413543888093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1636314972093534"><a name="p1636314972093534"></a><a name="p1636314972093534"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1216464624093534"><a name="p1216464624093534"></a><a name="p1216464624093534"></a>void </p>
<p id="p1267207130093534"><a name="p1267207130093534"></a><a name="p1267207130093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1173222780093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1808316090093534"><a name="p1808316090093534"></a><a name="p1808316090093534"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1408304538093534"><a name="p1408304538093534"></a><a name="p1408304538093534"></a>void </p>
<p id="p812118089093534"><a name="p812118089093534"></a><a name="p812118089093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1814835717093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1400550009093534"><a name="p1400550009093534"></a><a name="p1400550009093534"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1300403218093534"><a name="p1300403218093534"></a><a name="p1300403218093534"></a>void </p>
<p id="p1257469097093534"><a name="p1257469097093534"></a><a name="p1257469097093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1187483073093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1674829969093534"><a name="p1674829969093534"></a><a name="p1674829969093534"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p900681457093534"><a name="p900681457093534"></a><a name="p900681457093534"></a>void </p>
<p id="p556339592093534"><a name="p556339592093534"></a><a name="p556339592093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row80770817093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1065414165093534"><a name="p1065414165093534"></a><a name="p1065414165093534"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p609933952093534"><a name="p609933952093534"></a><a name="p609933952093534"></a>void </p>
<p id="p1093174225093534"><a name="p1093174225093534"></a><a name="p1093174225093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row906586580093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1796637750093534"><a name="p1796637750093534"></a><a name="p1796637750093534"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p120335994093534"><a name="p120335994093534"></a><a name="p120335994093534"></a>virtual void </p>
<p id="p1005158836093534"><a name="p1005158836093534"></a><a name="p1005158836093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row691459774093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p742255729093534"><a name="p742255729093534"></a><a name="p742255729093534"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2000198744093534"><a name="p2000198744093534"></a><a name="p2000198744093534"></a>virtual void </p>
<p id="p1568941663093534"><a name="p1568941663093534"></a><a name="p1568941663093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row219190626093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2113347582093534"><a name="p2113347582093534"></a><a name="p2113347582093534"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1315963950093534"><a name="p1315963950093534"></a><a name="p1315963950093534"></a>virtual int64_t </p>
<p id="p1235178321093534"><a name="p1235178321093534"></a><a name="p1235178321093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1362210402093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p413252506093534"><a name="p413252506093534"></a><a name="p413252506093534"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1284877369093534"><a name="p1284877369093534"></a><a name="p1284877369093534"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p1525515517093534"><a name="p1525515517093534"></a><a name="p1525515517093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1067878497093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1251459618093534"><a name="p1251459618093534"></a><a name="p1251459618093534"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p55773713093534"><a name="p55773713093534"></a><a name="p55773713093534"></a>void * </p>
<p id="p230497989093534"><a name="p230497989093534"></a><a name="p230497989093534"></a>Overrides the <strong id="b1789661522093534"><a name="b1789661522093534"></a><a name="b1789661522093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row710677548093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p447713225093534"><a name="p447713225093534"></a><a name="p447713225093534"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1725638184093534"><a name="p1725638184093534"></a><a name="p1725638184093534"></a>void </p>
<p id="p1107125928093534"><a name="p1107125928093534"></a><a name="p1107125928093534"></a>Overrides the <strong id="b683004310093534"><a name="b683004310093534"></a><a name="b683004310093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Protected Attributes<a name="pro-attribs"></a>

<a name="table435488453093534"></a>
<table><thead align="left"><tr id="row1872728973093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1052890065093534"><a name="p1052890065093534"></a><a name="p1052890065093534"></a>Protected Attribute Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p360359864093534"><a name="p360359864093534"></a><a name="p360359864093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row824219997093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2041999686093534"><a name="p2041999686093534"></a><a name="p2041999686093534"></a><a href="graphic.md#ga3e530646bd55e49f0e5b0052e121f040">imageWidth_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p284496418093534"><a name="p284496418093534"></a><a name="p284496418093534"></a>Represents the width of this image. </p>
</td>
</tr>
<tr id="row1494847003093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p539266110093534"><a name="p539266110093534"></a><a name="p539266110093534"></a><a href="graphic.md#ga5a7112d86d7b11b904b57c853817621d">imageHeight_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1921087601093534"><a name="p1921087601093534"></a><a name="p1921087601093534"></a>Represents the height of this image. </p>
</td>
</tr>
<tr id="row105862795093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p188727935093534"><a name="p188727935093534"></a><a name="p188727935093534"></a><a href="graphic.md#gac13c0b542f4d7f789754bacf572894b2">autoEnable_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1656085243093534"><a name="p1656085243093534"></a><a name="p1656085243093534"></a>Specifies whether automatic adaptation is enabled. </p>
</td>
</tr>
<tr id="row568808747093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p472314730093534"><a name="p472314730093534"></a><a name="p472314730093534"></a><a href="graphic.md#ga687a71ca22c04a7e761969f1fab1b06f">needRefresh_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p859197821093534"><a name="p859197821093534"></a><a name="p859197821093534"></a>Specifies whether a refresh is needed. </p>
</td>
</tr>
<tr id="row48028876093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p432001583093534"><a name="p432001583093534"></a><a name="p432001583093534"></a><a href="graphic.md#gacbbee3e74893c43864b116779d97ad09">colorFormat_</a>: 4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1124430465093534"><a name="p1124430465093534"></a><a name="p1124430465093534"></a>Represents the color format of this image. </p>
</td>
</tr>
<tr id="row346848217093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1772469076093534"><a name="p1772469076093534"></a><a name="p1772469076093534"></a><a href="graphic.md#ga1c57bd4af56c49a11060e32b6e33066c">blurLevel_</a>: 2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932805707093534"><a name="p1932805707093534"></a><a name="p1932805707093534"></a>Represents the blur level of this image when it is rotated or scaled. </p>
</td>
</tr>
<tr id="row1308498725093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1008983664093534"><a name="p1008983664093534"></a><a name="p1008983664093534"></a><a href="graphic.md#ga5a8f8683c377c59c6a3c193f18468e60">algorithm_</a>: 1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p733989272093534"><a name="p733989272093534"></a><a name="p733989272093534"></a>Represents the algorithm used for image rotation and scaling. </p>
</td>
</tr>
</tbody>
</table>

