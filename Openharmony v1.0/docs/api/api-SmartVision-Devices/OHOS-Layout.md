# OHOS::Layout<a name="ZH-CN_TOPIC_0000001054918187"></a>

## **Overview**<a name="section105744611093535"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines the base class of the layout, which indicates the basic data types and operations that may be used in the layout. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1706507874093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1261470304093535"></a>
<table><thead align="left"><tr id="row1097243136093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1614918049093535"><a name="p1614918049093535"></a><a name="p1614918049093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1292253356093535"><a name="p1292253356093535"></a><a name="p1292253356093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1276783964093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p708369103093535"><a name="p708369103093535"></a><a name="p708369103093535"></a><a href="Graphic.md#gaba1ca0f86a85d3c5636ca543b0ed08d8">Layout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p68454074093535"><a name="p68454074093535"></a><a name="p68454074093535"></a>&nbsp;</p>
<p id="p275743290093535"><a name="p275743290093535"></a><a name="p275743290093535"></a>A default constructor used to create a <strong id="b798777478093535"><a name="b798777478093535"></a><a name="b798777478093535"></a><a href="OHOS-Layout.md">Layout</a></strong> instance. </p>
</td>
</tr>
<tr id="row1737342721093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p446760740093535"><a name="p446760740093535"></a><a name="p446760740093535"></a><a href="Graphic.md#ga6c7cc7a849197fe014ea57d0534728bf">~Layout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p352568330093535"><a name="p352568330093535"></a><a name="p352568330093535"></a>virtual&nbsp;</p>
<p id="p1921778601093535"><a name="p1921778601093535"></a><a name="p1921778601093535"></a>A destructor used to delete the <strong id="b966980473093535"><a name="b966980473093535"></a><a name="b966980473093535"></a><a href="OHOS-Layout.md">Layout</a></strong> instance. </p>
</td>
</tr>
<tr id="row1984192521093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2058777418093535"><a name="p2058777418093535"></a><a name="p2058777418093535"></a><a href="Graphic.md#gada9223ec4d664c00a9640c8b9cbcacc3">SetLayoutDirection</a> (const <a href="Codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a> &amp;direction)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1980718871093535"><a name="p1980718871093535"></a><a name="p1980718871093535"></a>void&nbsp;</p>
<p id="p285238085093535"><a name="p285238085093535"></a><a name="p285238085093535"></a>Sets the layout direction. </p>
</td>
</tr>
<tr id="row1124506475093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p986914600093535"><a name="p986914600093535"></a><a name="p986914600093535"></a><a href="Graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1360583441093535"><a name="p1360583441093535"></a><a name="p1360583441093535"></a>&nbsp;</p>
<p id="p586759203093535"><a name="p586759203093535"></a><a name="p586759203093535"></a>A default constructor used to create a <strong id="b1873033195093535"><a name="b1873033195093535"></a><a name="b1873033195093535"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1517877522093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671314183093535"><a name="p671314183093535"></a><a name="p671314183093535"></a><a href="Graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p466751651093535"><a name="p466751651093535"></a><a name="p466751651093535"></a>virtual&nbsp;</p>
<p id="p1264486247093535"><a name="p1264486247093535"></a><a name="p1264486247093535"></a>A destructor used to delete the <strong id="b857881300093535"><a name="b857881300093535"></a><a name="b857881300093535"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1304033909093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617051247093535"><a name="p617051247093535"></a><a name="p617051247093535"></a><a href="Graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2084039920093535"><a name="p2084039920093535"></a><a name="p2084039920093535"></a>UIViewType&nbsp;</p>
<p id="p1420296115093535"><a name="p1420296115093535"></a><a name="p1420296115093535"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row618128497093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1412255855093535"><a name="p1412255855093535"></a><a name="p1412255855093535"></a><a href="Graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p837959702093535"><a name="p837959702093535"></a><a name="p837959702093535"></a>virtual void&nbsp;</p>
<p id="p367764799093535"><a name="p367764799093535"></a><a name="p367764799093535"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row888510598093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p825462702093535"><a name="p825462702093535"></a><a name="p825462702093535"></a><a href="Graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="OHOS-UIView.md">UIView</a> *prevView, <a href="OHOS-UIView.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p729777975093535"><a name="p729777975093535"></a><a name="p729777975093535"></a>virtual void&nbsp;</p>
<p id="p104895193093535"><a name="p104895193093535"></a><a name="p104895193093535"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row143041976093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1157046132093535"><a name="p1157046132093535"></a><a name="p1157046132093535"></a><a href="Graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1281811559093535"><a name="p1281811559093535"></a><a name="p1281811559093535"></a>virtual void&nbsp;</p>
<p id="p1027816896093535"><a name="p1027816896093535"></a><a name="p1027816896093535"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row59356328093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1898664254093535"><a name="p1898664254093535"></a><a name="p1898664254093535"></a><a href="Graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1235136680093535"><a name="p1235136680093535"></a><a name="p1235136680093535"></a>virtual void&nbsp;</p>
<p id="p1520286989093535"><a name="p1520286989093535"></a><a name="p1520286989093535"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row288942157093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1254434508093535"><a name="p1254434508093535"></a><a name="p1254434508093535"></a><a href="Graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1309922577093535"><a name="p1309922577093535"></a><a name="p1309922577093535"></a>virtual void&nbsp;</p>
<p id="p529906619093535"><a name="p529906619093535"></a><a name="p529906619093535"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1473730642093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p183894120093535"><a name="p183894120093535"></a><a name="p183894120093535"></a><a href="Graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2004310325093535"><a name="p2004310325093535"></a><a name="p2004310325093535"></a>virtual void&nbsp;</p>
<p id="p745886222093535"><a name="p745886222093535"></a><a name="p745886222093535"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row1191292718093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1905491458093535"><a name="p1905491458093535"></a><a name="p1905491458093535"></a><a href="Graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1477933083093535"><a name="p1477933083093535"></a><a name="p1477933083093535"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p543716008093535"><a name="p543716008093535"></a><a name="p543716008093535"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1894997835093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p813268502093535"><a name="p813268502093535"></a><a name="p813268502093535"></a><a href="Graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p898523067093535"><a name="p898523067093535"></a><a name="p898523067093535"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1448637616093535"><a name="p1448637616093535"></a><a name="p1448637616093535"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row476131838093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2080752944093535"><a name="p2080752944093535"></a><a name="p2080752944093535"></a><a href="Graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246751527093535"><a name="p246751527093535"></a><a name="p246751527093535"></a>void&nbsp;</p>
<p id="p247737463093535"><a name="p247737463093535"></a><a name="p247737463093535"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row2085615091093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p150201304093535"><a name="p150201304093535"></a><a name="p150201304093535"></a><a href="Graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1972383710093535"><a name="p1972383710093535"></a><a name="p1972383710093535"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p914529900093535"><a name="p914529900093535"></a><a name="p914529900093535"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row2016463690093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1564811845093535"><a name="p1564811845093535"></a><a name="p1564811845093535"></a><a href="Graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p137102186093535"><a name="p137102186093535"></a><a name="p137102186093535"></a>void&nbsp;</p>
<p id="p715169031093535"><a name="p715169031093535"></a><a name="p715169031093535"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row1806447876093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p192608882093535"><a name="p192608882093535"></a><a name="p192608882093535"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1168222941093535"><a name="p1168222941093535"></a><a name="p1168222941093535"></a>&nbsp;</p>
<p id="p273276837093535"><a name="p273276837093535"></a><a name="p273276837093535"></a>A default constructor used to create an <strong id="b1102102904093535"><a name="b1102102904093535"></a><a name="b1102102904093535"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row959314893093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p897804878093535"><a name="p897804878093535"></a><a name="p897804878093535"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1087293772093535"><a name="p1087293772093535"></a><a name="p1087293772093535"></a>&nbsp;</p>
<p id="p690035420093535"><a name="p690035420093535"></a><a name="p690035420093535"></a>A constructor used to create an <strong id="b900520750093535"><a name="b900520750093535"></a><a name="b900520750093535"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row966302731093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p680101628093535"><a name="p680101628093535"></a><a name="p680101628093535"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p671352243093535"><a name="p671352243093535"></a><a name="p671352243093535"></a>virtual&nbsp;</p>
<p id="p325226122093535"><a name="p325226122093535"></a><a name="p325226122093535"></a>A destructor used to delete the <strong id="b2025206748093535"><a name="b2025206748093535"></a><a name="b2025206748093535"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1473957347093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1591051605093535"><a name="p1591051605093535"></a><a name="p1591051605093535"></a><a href="Graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1899228648093535"><a name="p1899228648093535"></a><a name="p1899228648093535"></a>virtual bool&nbsp;</p>
<p id="p256758223093535"><a name="p256758223093535"></a><a name="p256758223093535"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1573456979093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p888371963093535"><a name="p888371963093535"></a><a name="p888371963093535"></a><a href="Graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p613821410093535"><a name="p613821410093535"></a><a name="p613821410093535"></a>virtual void&nbsp;</p>
<p id="p988441670093535"><a name="p988441670093535"></a><a name="p988441670093535"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1341046421093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p333105227093535"><a name="p333105227093535"></a><a name="p333105227093535"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2062463244093535"><a name="p2062463244093535"></a><a name="p2062463244093535"></a>virtual void&nbsp;</p>
<p id="p1627374328093535"><a name="p1627374328093535"></a><a name="p1627374328093535"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row119605352093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p825303484093535"><a name="p825303484093535"></a><a name="p825303484093535"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p672886564093535"><a name="p672886564093535"></a><a name="p672886564093535"></a>virtual void&nbsp;</p>
<p id="p631436141093535"><a name="p631436141093535"></a><a name="p631436141093535"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1345195782093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p924179273093535"><a name="p924179273093535"></a><a name="p924179273093535"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1246667742093535"><a name="p1246667742093535"></a><a name="p1246667742093535"></a>void&nbsp;</p>
<p id="p984311642093535"><a name="p984311642093535"></a><a name="p984311642093535"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row634289966093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2054478941093535"><a name="p2054478941093535"></a><a name="p2054478941093535"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p444617348093535"><a name="p444617348093535"></a><a name="p444617348093535"></a>void&nbsp;</p>
<p id="p1488064131093535"><a name="p1488064131093535"></a><a name="p1488064131093535"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row296886681093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1636764616093535"><a name="p1636764616093535"></a><a name="p1636764616093535"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p924250309093535"><a name="p924250309093535"></a><a name="p924250309093535"></a>virtual bool&nbsp;</p>
<p id="p1062771477093535"><a name="p1062771477093535"></a><a name="p1062771477093535"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row237100520093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p576149446093535"><a name="p576149446093535"></a><a name="p576149446093535"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p828282113093535"><a name="p828282113093535"></a><a name="p828282113093535"></a>virtual bool&nbsp;</p>
<p id="p772529721093535"><a name="p772529721093535"></a><a name="p772529721093535"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1686540902093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1375992737093535"><a name="p1375992737093535"></a><a name="p1375992737093535"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1405033465093535"><a name="p1405033465093535"></a><a name="p1405033465093535"></a>virtual bool&nbsp;</p>
<p id="p667911582093535"><a name="p667911582093535"></a><a name="p667911582093535"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1900667134093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p460150210093535"><a name="p460150210093535"></a><a name="p460150210093535"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1904337034093535"><a name="p1904337034093535"></a><a name="p1904337034093535"></a>virtual bool&nbsp;</p>
<p id="p1374467017093535"><a name="p1374467017093535"></a><a name="p1374467017093535"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row2062169995093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p16146573093535"><a name="p16146573093535"></a><a name="p16146573093535"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101374147093535"><a name="p101374147093535"></a><a name="p101374147093535"></a>virtual void&nbsp;</p>
<p id="p29833939093535"><a name="p29833939093535"></a><a name="p29833939093535"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row460316271093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p386195890093535"><a name="p386195890093535"></a><a name="p386195890093535"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p899376888093535"><a name="p899376888093535"></a><a name="p899376888093535"></a>virtual void&nbsp;</p>
<p id="p291607919093535"><a name="p291607919093535"></a><a name="p291607919093535"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1389409124093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1943924742093535"><a name="p1943924742093535"></a><a name="p1943924742093535"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p55739683093535"><a name="p55739683093535"></a><a name="p55739683093535"></a>virtual void&nbsp;</p>
<p id="p2057385688093535"><a name="p2057385688093535"></a><a name="p2057385688093535"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row998945537093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051042892093535"><a name="p2051042892093535"></a><a name="p2051042892093535"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p54055272093535"><a name="p54055272093535"></a><a name="p54055272093535"></a>virtual void&nbsp;</p>
<p id="p1370636775093535"><a name="p1370636775093535"></a><a name="p1370636775093535"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row512905523093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1193153883093535"><a name="p1193153883093535"></a><a name="p1193153883093535"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p417646143093535"><a name="p417646143093535"></a><a name="p417646143093535"></a>void&nbsp;</p>
<p id="p1275119569093535"><a name="p1275119569093535"></a><a name="p1275119569093535"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1111957157093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p571371538093535"><a name="p571371538093535"></a><a name="p571371538093535"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1351828975093535"><a name="p1351828975093535"></a><a name="p1351828975093535"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p2049543509093535"><a name="p2049543509093535"></a><a name="p2049543509093535"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row76650844093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p95643311093535"><a name="p95643311093535"></a><a name="p95643311093535"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p694673714093535"><a name="p694673714093535"></a><a name="p694673714093535"></a>void&nbsp;</p>
<p id="p1736647063093535"><a name="p1736647063093535"></a><a name="p1736647063093535"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row458275198093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1925141725093535"><a name="p1925141725093535"></a><a name="p1925141725093535"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1977005660093535"><a name="p1977005660093535"></a><a name="p1977005660093535"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p1913729473093535"><a name="p1913729473093535"></a><a name="p1913729473093535"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row329492016093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2076445068093535"><a name="p2076445068093535"></a><a name="p2076445068093535"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2127796085093535"><a name="p2127796085093535"></a><a name="p2127796085093535"></a>void&nbsp;</p>
<p id="p579504475093535"><a name="p579504475093535"></a><a name="p579504475093535"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1431924573093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1227557859093535"><a name="p1227557859093535"></a><a name="p1227557859093535"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1460773006093535"><a name="p1460773006093535"></a><a name="p1460773006093535"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p623767340093535"><a name="p623767340093535"></a><a name="p623767340093535"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row18763732093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1442124880093535"><a name="p1442124880093535"></a><a name="p1442124880093535"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p997928906093535"><a name="p997928906093535"></a><a name="p997928906093535"></a>void&nbsp;</p>
<p id="p430613866093535"><a name="p430613866093535"></a><a name="p430613866093535"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1748487887093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p596190752093535"><a name="p596190752093535"></a><a name="p596190752093535"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p177412633093535"><a name="p177412633093535"></a><a name="p177412633093535"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p379311810093535"><a name="p379311810093535"></a><a name="p379311810093535"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row143706529093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1202293228093535"><a name="p1202293228093535"></a><a name="p1202293228093535"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1648298617093535"><a name="p1648298617093535"></a><a name="p1648298617093535"></a>void&nbsp;</p>
<p id="p964624829093535"><a name="p964624829093535"></a><a name="p964624829093535"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row177349145093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2091571448093535"><a name="p2091571448093535"></a><a name="p2091571448093535"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p996158555093535"><a name="p996158555093535"></a><a name="p996158555093535"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1975308421093535"><a name="p1975308421093535"></a><a name="p1975308421093535"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1168981556093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p949155518093535"><a name="p949155518093535"></a><a name="p949155518093535"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1694691726093535"><a name="p1694691726093535"></a><a name="p1694691726093535"></a>void&nbsp;</p>
<p id="p2000056455093535"><a name="p2000056455093535"></a><a name="p2000056455093535"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1905472131093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p410403744093535"><a name="p410403744093535"></a><a name="p410403744093535"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2018419487093535"><a name="p2018419487093535"></a><a name="p2018419487093535"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1186004743093535"><a name="p1186004743093535"></a><a name="p1186004743093535"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1355445360093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p98910225093535"><a name="p98910225093535"></a><a name="p98910225093535"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1122541542093535"><a name="p1122541542093535"></a><a name="p1122541542093535"></a>virtual void&nbsp;</p>
<p id="p1204244452093535"><a name="p1204244452093535"></a><a name="p1204244452093535"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1935061225093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1897775667093535"><a name="p1897775667093535"></a><a name="p1897775667093535"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p710719594093535"><a name="p710719594093535"></a><a name="p710719594093535"></a>bool&nbsp;</p>
<p id="p1297708971093535"><a name="p1297708971093535"></a><a name="p1297708971093535"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row474578139093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p415551095093535"><a name="p415551095093535"></a><a name="p415551095093535"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1062429029093535"><a name="p1062429029093535"></a><a name="p1062429029093535"></a>void&nbsp;</p>
<p id="p1486165565093535"><a name="p1486165565093535"></a><a name="p1486165565093535"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row130502587093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p654533086093535"><a name="p654533086093535"></a><a name="p654533086093535"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1500565192093535"><a name="p1500565192093535"></a><a name="p1500565192093535"></a>bool&nbsp;</p>
<p id="p559064163093535"><a name="p559064163093535"></a><a name="p559064163093535"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1578458102093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1761629164093535"><a name="p1761629164093535"></a><a name="p1761629164093535"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389249432093535"><a name="p1389249432093535"></a><a name="p1389249432093535"></a>void&nbsp;</p>
<p id="p1723732590093535"><a name="p1723732590093535"></a><a name="p1723732590093535"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row201162151093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1066854789093535"><a name="p1066854789093535"></a><a name="p1066854789093535"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p124230251093535"><a name="p124230251093535"></a><a name="p124230251093535"></a>bool&nbsp;</p>
<p id="p1617037020093535"><a name="p1617037020093535"></a><a name="p1617037020093535"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row14007848093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1315609253093535"><a name="p1315609253093535"></a><a name="p1315609253093535"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1831434284093535"><a name="p1831434284093535"></a><a name="p1831434284093535"></a>void&nbsp;</p>
<p id="p2140148674093535"><a name="p2140148674093535"></a><a name="p2140148674093535"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row748352744093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1016056776093535"><a name="p1016056776093535"></a><a name="p1016056776093535"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1679340012093535"><a name="p1679340012093535"></a><a name="p1679340012093535"></a>bool&nbsp;</p>
<p id="p380062798093535"><a name="p380062798093535"></a><a name="p380062798093535"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row739392575093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2105026318093535"><a name="p2105026318093535"></a><a name="p2105026318093535"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p648228484093535"><a name="p648228484093535"></a><a name="p648228484093535"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p576463271093535"><a name="p576463271093535"></a><a name="p576463271093535"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row693310776093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1343422948093535"><a name="p1343422948093535"></a><a name="p1343422948093535"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1220820856093535"><a name="p1220820856093535"></a><a name="p1220820856093535"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p780823187093535"><a name="p780823187093535"></a><a name="p780823187093535"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row348393419093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1267639874093535"><a name="p1267639874093535"></a><a name="p1267639874093535"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p676779186093535"><a name="p676779186093535"></a><a name="p676779186093535"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p442159903093535"><a name="p442159903093535"></a><a name="p442159903093535"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row493530070093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1859116404093535"><a name="p1859116404093535"></a><a name="p1859116404093535"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1825824152093535"><a name="p1825824152093535"></a><a name="p1825824152093535"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1577735576093535"><a name="p1577735576093535"></a><a name="p1577735576093535"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row644260780093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1032330118093535"><a name="p1032330118093535"></a><a name="p1032330118093535"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1764143968093535"><a name="p1764143968093535"></a><a name="p1764143968093535"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1292580166093535"><a name="p1292580166093535"></a><a name="p1292580166093535"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row977031961093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p242359923093535"><a name="p242359923093535"></a><a name="p242359923093535"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577695143093535"><a name="p577695143093535"></a><a name="p577695143093535"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p645326276093535"><a name="p645326276093535"></a><a name="p645326276093535"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1816430293093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p254899964093535"><a name="p254899964093535"></a><a name="p254899964093535"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511668272093535"><a name="p1511668272093535"></a><a name="p1511668272093535"></a>void&nbsp;</p>
<p id="p26018869093535"><a name="p26018869093535"></a><a name="p26018869093535"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row2048021359093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381826607093535"><a name="p381826607093535"></a><a name="p381826607093535"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p469571516093535"><a name="p469571516093535"></a><a name="p469571516093535"></a>virtual void&nbsp;</p>
<p id="p64417744093535"><a name="p64417744093535"></a><a name="p64417744093535"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1874508484093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p569658016093535"><a name="p569658016093535"></a><a name="p569658016093535"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p574678558093535"><a name="p574678558093535"></a><a name="p574678558093535"></a>virtual int16_t&nbsp;</p>
<p id="p1475038695093535"><a name="p1475038695093535"></a><a name="p1475038695093535"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row559407516093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p351677187093535"><a name="p351677187093535"></a><a name="p351677187093535"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p970969735093535"><a name="p970969735093535"></a><a name="p970969735093535"></a>virtual void&nbsp;</p>
<p id="p1980233548093535"><a name="p1980233548093535"></a><a name="p1980233548093535"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1376576104093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1207655246093535"><a name="p1207655246093535"></a><a name="p1207655246093535"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1351408102093535"><a name="p1351408102093535"></a><a name="p1351408102093535"></a>virtual int16_t&nbsp;</p>
<p id="p1741591116093535"><a name="p1741591116093535"></a><a name="p1741591116093535"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row638355233093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p42413442093535"><a name="p42413442093535"></a><a name="p42413442093535"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1489707699093535"><a name="p1489707699093535"></a><a name="p1489707699093535"></a>virtual void&nbsp;</p>
<p id="p644894604093535"><a name="p644894604093535"></a><a name="p644894604093535"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row883014218093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1340088119093535"><a name="p1340088119093535"></a><a name="p1340088119093535"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135364024093535"><a name="p135364024093535"></a><a name="p135364024093535"></a>virtual void&nbsp;</p>
<p id="p1316928253093535"><a name="p1316928253093535"></a><a name="p1316928253093535"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1152763161093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p732797116093535"><a name="p732797116093535"></a><a name="p732797116093535"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1510245482093535"><a name="p1510245482093535"></a><a name="p1510245482093535"></a>int16_t&nbsp;</p>
<p id="p1445987846093535"><a name="p1445987846093535"></a><a name="p1445987846093535"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1777890598093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1675516019093535"><a name="p1675516019093535"></a><a name="p1675516019093535"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1947974166093535"><a name="p1947974166093535"></a><a name="p1947974166093535"></a>virtual void&nbsp;</p>
<p id="p1265839846093535"><a name="p1265839846093535"></a><a name="p1265839846093535"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row420209769093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1428740126093535"><a name="p1428740126093535"></a><a name="p1428740126093535"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1050739841093535"><a name="p1050739841093535"></a><a name="p1050739841093535"></a>int16_t&nbsp;</p>
<p id="p889092329093535"><a name="p889092329093535"></a><a name="p889092329093535"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1105254182093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1152958758093535"><a name="p1152958758093535"></a><a name="p1152958758093535"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452295620093535"><a name="p1452295620093535"></a><a name="p1452295620093535"></a>virtual void&nbsp;</p>
<p id="p1490306832093535"><a name="p1490306832093535"></a><a name="p1490306832093535"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row661735984093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1600856838093535"><a name="p1600856838093535"></a><a name="p1600856838093535"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1615193585093535"><a name="p1615193585093535"></a><a name="p1615193585093535"></a>virtual void&nbsp;</p>
<p id="p906837123093535"><a name="p906837123093535"></a><a name="p906837123093535"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row915296042093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p636794718093535"><a name="p636794718093535"></a><a name="p636794718093535"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p715626228093535"><a name="p715626228093535"></a><a name="p715626228093535"></a>bool&nbsp;</p>
<p id="p2007777722093535"><a name="p2007777722093535"></a><a name="p2007777722093535"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row382688773093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1421068828093535"><a name="p1421068828093535"></a><a name="p1421068828093535"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653372128093535"><a name="p1653372128093535"></a><a name="p1653372128093535"></a>void&nbsp;</p>
<p id="p1380717857093535"><a name="p1380717857093535"></a><a name="p1380717857093535"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row878100234093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p506720730093535"><a name="p506720730093535"></a><a name="p506720730093535"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1373361923093535"><a name="p1373361923093535"></a><a name="p1373361923093535"></a>void&nbsp;</p>
<p id="p2080504281093535"><a name="p2080504281093535"></a><a name="p2080504281093535"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1146452136093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1485843438093535"><a name="p1485843438093535"></a><a name="p1485843438093535"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1515387959093535"><a name="p1515387959093535"></a><a name="p1515387959093535"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p2005806230093535"><a name="p2005806230093535"></a><a name="p2005806230093535"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1302879566093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217547608093535"><a name="p1217547608093535"></a><a name="p1217547608093535"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p501798991093535"><a name="p501798991093535"></a><a name="p501798991093535"></a>void&nbsp;</p>
<p id="p199061512093535"><a name="p199061512093535"></a><a name="p199061512093535"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1730307080093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p460749374093535"><a name="p460749374093535"></a><a name="p460749374093535"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p343987352093535"><a name="p343987352093535"></a><a name="p343987352093535"></a>const char *&nbsp;</p>
<p id="p1826607221093535"><a name="p1826607221093535"></a><a name="p1826607221093535"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1095714546093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2121112166093535"><a name="p2121112166093535"></a><a name="p2121112166093535"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1793599788093535"><a name="p1793599788093535"></a><a name="p1793599788093535"></a>void&nbsp;</p>
<p id="p623077550093535"><a name="p623077550093535"></a><a name="p623077550093535"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1035159592093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907372399093535"><a name="p907372399093535"></a><a name="p907372399093535"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1124820674093535"><a name="p1124820674093535"></a><a name="p1124820674093535"></a>int16_t&nbsp;</p>
<p id="p2072553510093535"><a name="p2072553510093535"></a><a name="p2072553510093535"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row591146347093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1580998431093535"><a name="p1580998431093535"></a><a name="p1580998431093535"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p40807912093535"><a name="p40807912093535"></a><a name="p40807912093535"></a>virtual void&nbsp;</p>
<p id="p438242733093535"><a name="p438242733093535"></a><a name="p438242733093535"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row456751090093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1696540384093535"><a name="p1696540384093535"></a><a name="p1696540384093535"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p729232135093535"><a name="p729232135093535"></a><a name="p729232135093535"></a>void&nbsp;</p>
<p id="p719942069093535"><a name="p719942069093535"></a><a name="p719942069093535"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row184432067093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2062946767093535"><a name="p2062946767093535"></a><a name="p2062946767093535"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449608304093535"><a name="p449608304093535"></a><a name="p449608304093535"></a>void&nbsp;</p>
<p id="p1120730725093535"><a name="p1120730725093535"></a><a name="p1120730725093535"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1223549244093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2085330892093535"><a name="p2085330892093535"></a><a name="p2085330892093535"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p954766081093535"><a name="p954766081093535"></a><a name="p954766081093535"></a>void&nbsp;</p>
<p id="p559591499093535"><a name="p559591499093535"></a><a name="p559591499093535"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row250064695093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p788714074093535"><a name="p788714074093535"></a><a name="p788714074093535"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p326429596093535"><a name="p326429596093535"></a><a name="p326429596093535"></a>void&nbsp;</p>
<p id="p1284057553093535"><a name="p1284057553093535"></a><a name="p1284057553093535"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1068142163093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1169637160093535"><a name="p1169637160093535"></a><a name="p1169637160093535"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p737802637093535"><a name="p737802637093535"></a><a name="p737802637093535"></a>void&nbsp;</p>
<p id="p1775225572093535"><a name="p1775225572093535"></a><a name="p1775225572093535"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row2063547731093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329408943093535"><a name="p329408943093535"></a><a name="p329408943093535"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2039670699093535"><a name="p2039670699093535"></a><a name="p2039670699093535"></a>void&nbsp;</p>
<p id="p1369499211093535"><a name="p1369499211093535"></a><a name="p1369499211093535"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row859697149093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p703282886093535"><a name="p703282886093535"></a><a name="p703282886093535"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389683630093535"><a name="p1389683630093535"></a><a name="p1389683630093535"></a>void&nbsp;</p>
<p id="p1644832902093535"><a name="p1644832902093535"></a><a name="p1644832902093535"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row2074697168093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1871335292093535"><a name="p1871335292093535"></a><a name="p1871335292093535"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p745631023093535"><a name="p745631023093535"></a><a name="p745631023093535"></a>void&nbsp;</p>
<p id="p1222226362093535"><a name="p1222226362093535"></a><a name="p1222226362093535"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1545492085093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1071884211093535"><a name="p1071884211093535"></a><a name="p1071884211093535"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p871524543093535"><a name="p871524543093535"></a><a name="p871524543093535"></a>void&nbsp;</p>
<p id="p844135461093535"><a name="p844135461093535"></a><a name="p844135461093535"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1028754228093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p964276650093535"><a name="p964276650093535"></a><a name="p964276650093535"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1446521584093535"><a name="p1446521584093535"></a><a name="p1446521584093535"></a>void&nbsp;</p>
<p id="p1031268131093535"><a name="p1031268131093535"></a><a name="p1031268131093535"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row223000694093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p276557143093535"><a name="p276557143093535"></a><a name="p276557143093535"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p661123974093535"><a name="p661123974093535"></a><a name="p661123974093535"></a>void&nbsp;</p>
<p id="p1083648290093535"><a name="p1083648290093535"></a><a name="p1083648290093535"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1460360348093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1302434991093535"><a name="p1302434991093535"></a><a name="p1302434991093535"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p732001231093535"><a name="p732001231093535"></a><a name="p732001231093535"></a>void&nbsp;</p>
<p id="p1809244288093535"><a name="p1809244288093535"></a><a name="p1809244288093535"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1505324266093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p854166634093535"><a name="p854166634093535"></a><a name="p854166634093535"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1536340721093535"><a name="p1536340721093535"></a><a name="p1536340721093535"></a>void&nbsp;</p>
<p id="p1526797304093535"><a name="p1526797304093535"></a><a name="p1526797304093535"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row555115221093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p88035089093535"><a name="p88035089093535"></a><a name="p88035089093535"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p683122565093535"><a name="p683122565093535"></a><a name="p683122565093535"></a>void&nbsp;</p>
<p id="p1919323121093535"><a name="p1919323121093535"></a><a name="p1919323121093535"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row15832996093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p280042527093535"><a name="p280042527093535"></a><a name="p280042527093535"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p867813376093535"><a name="p867813376093535"></a><a name="p867813376093535"></a>void&nbsp;</p>
<p id="p1370863047093535"><a name="p1370863047093535"></a><a name="p1370863047093535"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1732138972093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2130370877093535"><a name="p2130370877093535"></a><a name="p2130370877093535"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p800875197093535"><a name="p800875197093535"></a><a name="p800875197093535"></a>virtual void&nbsp;</p>
<p id="p510530180093535"><a name="p510530180093535"></a><a name="p510530180093535"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1309989407093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2032360125093535"><a name="p2032360125093535"></a><a name="p2032360125093535"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p88239686093535"><a name="p88239686093535"></a><a name="p88239686093535"></a>virtual void&nbsp;</p>
<p id="p1953525213093535"><a name="p1953525213093535"></a><a name="p1953525213093535"></a>Sets a style. </p>
</td>
</tr>
<tr id="row71128383093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p704192255093535"><a name="p704192255093535"></a><a name="p704192255093535"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1137286800093535"><a name="p1137286800093535"></a><a name="p1137286800093535"></a>virtual int64_t&nbsp;</p>
<p id="p1405537513093535"><a name="p1405537513093535"></a><a name="p1405537513093535"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row426776328093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1514440360093535"><a name="p1514440360093535"></a><a name="p1514440360093535"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1079653640093535"><a name="p1079653640093535"></a><a name="p1079653640093535"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p277672627093535"><a name="p277672627093535"></a><a name="p277672627093535"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1612115872093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1723992103093535"><a name="p1723992103093535"></a><a name="p1723992103093535"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1375081494093535"><a name="p1375081494093535"></a><a name="p1375081494093535"></a>void *&nbsp;</p>
<p id="p626748058093535"><a name="p626748058093535"></a><a name="p626748058093535"></a>Overrides the <strong id="b1540411233093535"><a name="b1540411233093535"></a><a name="b1540411233093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1774858035093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2069664735093535"><a name="p2069664735093535"></a><a name="p2069664735093535"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1756470172093535"><a name="p1756470172093535"></a><a name="p1756470172093535"></a>void&nbsp;</p>
<p id="p1094987969093535"><a name="p1094987969093535"></a><a name="p1094987969093535"></a>Overrides the <strong id="b1073743556093535"><a name="b1073743556093535"></a><a name="b1073743556093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1216361004093535"></a>
<table><thead align="left"><tr id="row1955576613093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p353003394093535"><a name="p353003394093535"></a><a name="p353003394093535"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p996340082093535"><a name="p996340082093535"></a><a name="p996340082093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row180688748093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1321556195093535"><a name="p1321556195093535"></a><a name="p1321556195093535"></a><a href="Graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1058613723093535"><a name="p1058613723093535"></a><a name="p1058613723093535"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row120170814093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1134573309093535"><a name="p1134573309093535"></a><a name="p1134573309093535"></a><a href="Graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1962886318093535"><a name="p1962886318093535"></a><a name="p1962886318093535"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row295108289093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1736560220093535"><a name="p1736560220093535"></a><a name="p1736560220093535"></a><a href="Graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p662357014093535"><a name="p662357014093535"></a><a name="p662357014093535"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row892858814093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p179790705093535"><a name="p179790705093535"></a><a name="p179790705093535"></a><a href="Graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2007178445093535"><a name="p2007178445093535"></a><a name="p2007178445093535"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row2023024533093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589836797093535"><a name="p589836797093535"></a><a name="p589836797093535"></a><a href="Graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1797974630093535"><a name="p1797974630093535"></a><a name="p1797974630093535"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row193535623093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1123916431093535"><a name="p1123916431093535"></a><a name="p1123916431093535"></a><a href="Graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1554348718093535"><a name="p1554348718093535"></a><a name="p1554348718093535"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1845092509093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2101825374093535"><a name="p2101825374093535"></a><a name="p2101825374093535"></a><a href="Graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1851227187093535"><a name="p1851227187093535"></a><a name="p1851227187093535"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row871978676093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p539934081093535"><a name="p539934081093535"></a><a name="p539934081093535"></a><a href="Graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p974612764093535"><a name="p974612764093535"></a><a name="p974612764093535"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

