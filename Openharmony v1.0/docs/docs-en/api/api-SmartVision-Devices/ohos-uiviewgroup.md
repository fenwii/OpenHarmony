# OHOS::UIViewGroup<a name="EN-US_TOPIC_0000001055678122"></a>

## **Overview**<a name="section1288839074093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Represents a view group that consists of its child views. 

The child views can be added to, inserted in, and removed from the view group. Child views that are added later are displayed at the upper layer of this view group. All child views are stored in a linked list.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section669197839093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table413566257093535"></a>
<table><thead align="left"><tr id="row553583260093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2114947294093535"><a name="p2114947294093535"></a><a name="p2114947294093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1547083342093535"><a name="p1547083342093535"></a><a name="p1547083342093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row503787692093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1162251699093535"><a name="p1162251699093535"></a><a name="p1162251699093535"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1538948654093535"><a name="p1538948654093535"></a><a name="p1538948654093535"></a> </p>
<p id="p764952377093535"><a name="p764952377093535"></a><a name="p764952377093535"></a>A default constructor used to create a <strong id="b81664611093535"><a name="b81664611093535"></a><a name="b81664611093535"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1689657286093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1687625621093535"><a name="p1687625621093535"></a><a name="p1687625621093535"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1841174629093535"><a name="p1841174629093535"></a><a name="p1841174629093535"></a>virtual </p>
<p id="p1966796804093535"><a name="p1966796804093535"></a><a name="p1966796804093535"></a>A destructor used to delete the <strong id="b12335881093535"><a name="b12335881093535"></a><a name="b12335881093535"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row588134513093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1111467150093535"><a name="p1111467150093535"></a><a name="p1111467150093535"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p445717724093535"><a name="p445717724093535"></a><a name="p445717724093535"></a>UIViewType </p>
<p id="p1010730617093535"><a name="p1010730617093535"></a><a name="p1010730617093535"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1247105559093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1174048217093535"><a name="p1174048217093535"></a><a name="p1174048217093535"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1864760001093535"><a name="p1864760001093535"></a><a name="p1864760001093535"></a>virtual void </p>
<p id="p2044823564093535"><a name="p2044823564093535"></a><a name="p2044823564093535"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row379664952093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p142240820093535"><a name="p142240820093535"></a><a name="p142240820093535"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1735950141093535"><a name="p1735950141093535"></a><a name="p1735950141093535"></a>virtual void </p>
<p id="p115303236093535"><a name="p115303236093535"></a><a name="p115303236093535"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1387767392093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2135880490093535"><a name="p2135880490093535"></a><a name="p2135880490093535"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p260764201093535"><a name="p260764201093535"></a><a name="p260764201093535"></a>virtual void </p>
<p id="p260743706093535"><a name="p260743706093535"></a><a name="p260743706093535"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row32548185093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2060310427093535"><a name="p2060310427093535"></a><a name="p2060310427093535"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1514315933093535"><a name="p1514315933093535"></a><a name="p1514315933093535"></a>virtual void </p>
<p id="p1287548344093535"><a name="p1287548344093535"></a><a name="p1287548344093535"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1662839126093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p556998662093535"><a name="p556998662093535"></a><a name="p556998662093535"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1069001977093535"><a name="p1069001977093535"></a><a name="p1069001977093535"></a>virtual void </p>
<p id="p1158832384093535"><a name="p1158832384093535"></a><a name="p1158832384093535"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row47981364093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1240195644093535"><a name="p1240195644093535"></a><a name="p1240195644093535"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p842867508093535"><a name="p842867508093535"></a><a name="p842867508093535"></a>virtual void </p>
<p id="p479973867093535"><a name="p479973867093535"></a><a name="p479973867093535"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row269927275093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793036518093535"><a name="p793036518093535"></a><a name="p793036518093535"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1437974824093535"><a name="p1437974824093535"></a><a name="p1437974824093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p599440156093535"><a name="p599440156093535"></a><a name="p599440156093535"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1377850150093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p269496722093535"><a name="p269496722093535"></a><a name="p269496722093535"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1774253120093535"><a name="p1774253120093535"></a><a name="p1774253120093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p961065782093535"><a name="p961065782093535"></a><a name="p961065782093535"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row1405393182093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1495270775093535"><a name="p1495270775093535"></a><a name="p1495270775093535"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p749441893093535"><a name="p749441893093535"></a><a name="p749441893093535"></a>void </p>
<p id="p691437713093535"><a name="p691437713093535"></a><a name="p691437713093535"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row169980964093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1953859606093535"><a name="p1953859606093535"></a><a name="p1953859606093535"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1961929034093535"><a name="p1961929034093535"></a><a name="p1961929034093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p441088632093535"><a name="p441088632093535"></a><a name="p441088632093535"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row1736168895093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1282257522093535"><a name="p1282257522093535"></a><a name="p1282257522093535"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1801097225093535"><a name="p1801097225093535"></a><a name="p1801097225093535"></a>void </p>
<p id="p1658862337093535"><a name="p1658862337093535"></a><a name="p1658862337093535"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row1616715841093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1865166657093535"><a name="p1865166657093535"></a><a name="p1865166657093535"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1017041038093535"><a name="p1017041038093535"></a><a name="p1017041038093535"></a> </p>
<p id="p1635478165093535"><a name="p1635478165093535"></a><a name="p1635478165093535"></a>A default constructor used to create an <strong id="b2114398461093535"><a name="b2114398461093535"></a><a name="b2114398461093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1409120993093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1177646154093535"><a name="p1177646154093535"></a><a name="p1177646154093535"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1947492377093535"><a name="p1947492377093535"></a><a name="p1947492377093535"></a> </p>
<p id="p1210859182093535"><a name="p1210859182093535"></a><a name="p1210859182093535"></a>A constructor used to create an <strong id="b1696666114093535"><a name="b1696666114093535"></a><a name="b1696666114093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row475387502093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p826807014093535"><a name="p826807014093535"></a><a name="p826807014093535"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p399568526093535"><a name="p399568526093535"></a><a name="p399568526093535"></a>virtual </p>
<p id="p402089605093535"><a name="p402089605093535"></a><a name="p402089605093535"></a>A destructor used to delete the <strong id="b269287198093535"><a name="b269287198093535"></a><a name="b269287198093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1093319750093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p287782028093535"><a name="p287782028093535"></a><a name="p287782028093535"></a><a href="graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757950205093535"><a name="p757950205093535"></a><a name="p757950205093535"></a>virtual bool </p>
<p id="p2001260539093535"><a name="p2001260539093535"></a><a name="p2001260539093535"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1865319839093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1497019495093535"><a name="p1497019495093535"></a><a name="p1497019495093535"></a><a href="graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p917439786093535"><a name="p917439786093535"></a><a name="p917439786093535"></a>virtual void </p>
<p id="p188591231093535"><a name="p188591231093535"></a><a name="p188591231093535"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1122822887093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1204510694093535"><a name="p1204510694093535"></a><a name="p1204510694093535"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p859611270093535"><a name="p859611270093535"></a><a name="p859611270093535"></a>virtual void </p>
<p id="p359560010093535"><a name="p359560010093535"></a><a name="p359560010093535"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row235739331093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p922069440093535"><a name="p922069440093535"></a><a name="p922069440093535"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2033575987093535"><a name="p2033575987093535"></a><a name="p2033575987093535"></a>virtual void </p>
<p id="p1524483480093535"><a name="p1524483480093535"></a><a name="p1524483480093535"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row542474000093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1984652570093535"><a name="p1984652570093535"></a><a name="p1984652570093535"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2107790919093535"><a name="p2107790919093535"></a><a name="p2107790919093535"></a>void </p>
<p id="p2083175714093535"><a name="p2083175714093535"></a><a name="p2083175714093535"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row648648036093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p470268531093535"><a name="p470268531093535"></a><a name="p470268531093535"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1749045425093535"><a name="p1749045425093535"></a><a name="p1749045425093535"></a>void </p>
<p id="p36431017093535"><a name="p36431017093535"></a><a name="p36431017093535"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row262514533093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1129524823093535"><a name="p1129524823093535"></a><a name="p1129524823093535"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265021285093535"><a name="p265021285093535"></a><a name="p265021285093535"></a>virtual bool </p>
<p id="p622044529093535"><a name="p622044529093535"></a><a name="p622044529093535"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row48482045093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p97223820093535"><a name="p97223820093535"></a><a name="p97223820093535"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p963667125093535"><a name="p963667125093535"></a><a name="p963667125093535"></a>virtual bool </p>
<p id="p346573198093535"><a name="p346573198093535"></a><a name="p346573198093535"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row780841632093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p452825100093535"><a name="p452825100093535"></a><a name="p452825100093535"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p189121194093535"><a name="p189121194093535"></a><a name="p189121194093535"></a>virtual bool </p>
<p id="p906174473093535"><a name="p906174473093535"></a><a name="p906174473093535"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row124348033093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1476976648093535"><a name="p1476976648093535"></a><a name="p1476976648093535"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2015032821093535"><a name="p2015032821093535"></a><a name="p2015032821093535"></a>virtual bool </p>
<p id="p803113162093535"><a name="p803113162093535"></a><a name="p803113162093535"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row211980706093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p388376523093535"><a name="p388376523093535"></a><a name="p388376523093535"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p423618829093535"><a name="p423618829093535"></a><a name="p423618829093535"></a>virtual void </p>
<p id="p761891093093535"><a name="p761891093093535"></a><a name="p761891093093535"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row671462463093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1510936051093535"><a name="p1510936051093535"></a><a name="p1510936051093535"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p841759244093535"><a name="p841759244093535"></a><a name="p841759244093535"></a>virtual void </p>
<p id="p358126006093535"><a name="p358126006093535"></a><a name="p358126006093535"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1096940255093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p374157880093535"><a name="p374157880093535"></a><a name="p374157880093535"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p937147684093535"><a name="p937147684093535"></a><a name="p937147684093535"></a>virtual void </p>
<p id="p35198635093535"><a name="p35198635093535"></a><a name="p35198635093535"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1125317626093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1891180155093535"><a name="p1891180155093535"></a><a name="p1891180155093535"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1388979725093535"><a name="p1388979725093535"></a><a name="p1388979725093535"></a>virtual void </p>
<p id="p813412170093535"><a name="p813412170093535"></a><a name="p813412170093535"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row425487264093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1247245935093535"><a name="p1247245935093535"></a><a name="p1247245935093535"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1912180166093535"><a name="p1912180166093535"></a><a name="p1912180166093535"></a>void </p>
<p id="p1654816895093535"><a name="p1654816895093535"></a><a name="p1654816895093535"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1339574936093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1544249719093535"><a name="p1544249719093535"></a><a name="p1544249719093535"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p779145505093535"><a name="p779145505093535"></a><a name="p779145505093535"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p1815945423093535"><a name="p1815945423093535"></a><a name="p1815945423093535"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1301206748093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1682988165093535"><a name="p1682988165093535"></a><a name="p1682988165093535"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1792721819093535"><a name="p1792721819093535"></a><a name="p1792721819093535"></a>void </p>
<p id="p986135201093535"><a name="p986135201093535"></a><a name="p986135201093535"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1355547180093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p197892470093535"><a name="p197892470093535"></a><a name="p197892470093535"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267627733093535"><a name="p267627733093535"></a><a name="p267627733093535"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p377644886093535"><a name="p377644886093535"></a><a name="p377644886093535"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row947761085093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2080066089093535"><a name="p2080066089093535"></a><a name="p2080066089093535"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p538543520093535"><a name="p538543520093535"></a><a name="p538543520093535"></a>void </p>
<p id="p747170761093535"><a name="p747170761093535"></a><a name="p747170761093535"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row2034445871093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p741612210093535"><a name="p741612210093535"></a><a name="p741612210093535"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1037938876093535"><a name="p1037938876093535"></a><a name="p1037938876093535"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p510913080093535"><a name="p510913080093535"></a><a name="p510913080093535"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row238909792093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p908802774093535"><a name="p908802774093535"></a><a name="p908802774093535"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1474251674093535"><a name="p1474251674093535"></a><a name="p1474251674093535"></a>void </p>
<p id="p1177087250093535"><a name="p1177087250093535"></a><a name="p1177087250093535"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row2013273529093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1931643954093535"><a name="p1931643954093535"></a><a name="p1931643954093535"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2030264385093535"><a name="p2030264385093535"></a><a name="p2030264385093535"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p790579997093535"><a name="p790579997093535"></a><a name="p790579997093535"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1459549924093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p295396184093535"><a name="p295396184093535"></a><a name="p295396184093535"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p104358353093535"><a name="p104358353093535"></a><a name="p104358353093535"></a>void </p>
<p id="p1080637747093535"><a name="p1080637747093535"></a><a name="p1080637747093535"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row18593761093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149410275093535"><a name="p1149410275093535"></a><a name="p1149410275093535"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1688260182093535"><a name="p1688260182093535"></a><a name="p1688260182093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p507327367093535"><a name="p507327367093535"></a><a name="p507327367093535"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row2056680933093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p501002676093535"><a name="p501002676093535"></a><a name="p501002676093535"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1839888198093535"><a name="p1839888198093535"></a><a name="p1839888198093535"></a>void </p>
<p id="p912261446093535"><a name="p912261446093535"></a><a name="p912261446093535"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row582542008093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p825498783093535"><a name="p825498783093535"></a><a name="p825498783093535"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1733152569093535"><a name="p1733152569093535"></a><a name="p1733152569093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p433356250093535"><a name="p433356250093535"></a><a name="p433356250093535"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1894243807093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p280185615093535"><a name="p280185615093535"></a><a name="p280185615093535"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1247022022093535"><a name="p1247022022093535"></a><a name="p1247022022093535"></a>virtual void </p>
<p id="p139936182093535"><a name="p139936182093535"></a><a name="p139936182093535"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row883319893093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1983910083093535"><a name="p1983910083093535"></a><a name="p1983910083093535"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1065225091093535"><a name="p1065225091093535"></a><a name="p1065225091093535"></a>bool </p>
<p id="p914760670093535"><a name="p914760670093535"></a><a name="p914760670093535"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1209854307093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1640521197093535"><a name="p1640521197093535"></a><a name="p1640521197093535"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1355629245093535"><a name="p1355629245093535"></a><a name="p1355629245093535"></a>void </p>
<p id="p1286170218093535"><a name="p1286170218093535"></a><a name="p1286170218093535"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1768992002093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1813066719093535"><a name="p1813066719093535"></a><a name="p1813066719093535"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1830714042093535"><a name="p1830714042093535"></a><a name="p1830714042093535"></a>bool </p>
<p id="p1185900696093535"><a name="p1185900696093535"></a><a name="p1185900696093535"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1337771053093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1657901082093535"><a name="p1657901082093535"></a><a name="p1657901082093535"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1135035058093535"><a name="p1135035058093535"></a><a name="p1135035058093535"></a>void </p>
<p id="p620582613093535"><a name="p620582613093535"></a><a name="p620582613093535"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1072142838093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851442102093535"><a name="p1851442102093535"></a><a name="p1851442102093535"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p141149197093535"><a name="p141149197093535"></a><a name="p141149197093535"></a>bool </p>
<p id="p1394908447093535"><a name="p1394908447093535"></a><a name="p1394908447093535"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1932045905093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p868682570093535"><a name="p868682570093535"></a><a name="p868682570093535"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p822866897093535"><a name="p822866897093535"></a><a name="p822866897093535"></a>void </p>
<p id="p1471432712093535"><a name="p1471432712093535"></a><a name="p1471432712093535"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row643455126093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p786045633093535"><a name="p786045633093535"></a><a name="p786045633093535"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926584761093535"><a name="p926584761093535"></a><a name="p926584761093535"></a>bool </p>
<p id="p593198331093535"><a name="p593198331093535"></a><a name="p593198331093535"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1328365176093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p884909830093535"><a name="p884909830093535"></a><a name="p884909830093535"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p703617403093535"><a name="p703617403093535"></a><a name="p703617403093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p451316184093535"><a name="p451316184093535"></a><a name="p451316184093535"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row566224795093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p266837336093535"><a name="p266837336093535"></a><a name="p266837336093535"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p433992636093535"><a name="p433992636093535"></a><a name="p433992636093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1440682537093535"><a name="p1440682537093535"></a><a name="p1440682537093535"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row541852037093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p351115363093535"><a name="p351115363093535"></a><a name="p351115363093535"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1981848807093535"><a name="p1981848807093535"></a><a name="p1981848807093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p648434353093535"><a name="p648434353093535"></a><a name="p648434353093535"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1649869231093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997556783093535"><a name="p997556783093535"></a><a name="p997556783093535"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p871576890093535"><a name="p871576890093535"></a><a name="p871576890093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p706591996093535"><a name="p706591996093535"></a><a name="p706591996093535"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row162248075093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p638228965093535"><a name="p638228965093535"></a><a name="p638228965093535"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1900536324093535"><a name="p1900536324093535"></a><a name="p1900536324093535"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p633106210093535"><a name="p633106210093535"></a><a name="p633106210093535"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1961722829093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p272575532093535"><a name="p272575532093535"></a><a name="p272575532093535"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422626167093535"><a name="p422626167093535"></a><a name="p422626167093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1368221156093535"><a name="p1368221156093535"></a><a name="p1368221156093535"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row970013420093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p76960077093535"><a name="p76960077093535"></a><a name="p76960077093535"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p631122872093535"><a name="p631122872093535"></a><a name="p631122872093535"></a>void </p>
<p id="p204706345093535"><a name="p204706345093535"></a><a name="p204706345093535"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1945543803093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p940948006093535"><a name="p940948006093535"></a><a name="p940948006093535"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p209843375093535"><a name="p209843375093535"></a><a name="p209843375093535"></a>virtual void </p>
<p id="p1678192140093535"><a name="p1678192140093535"></a><a name="p1678192140093535"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row286830028093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2132645130093535"><a name="p2132645130093535"></a><a name="p2132645130093535"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1915704711093535"><a name="p1915704711093535"></a><a name="p1915704711093535"></a>virtual int16_t </p>
<p id="p740739711093535"><a name="p740739711093535"></a><a name="p740739711093535"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row610412803093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p244379171093535"><a name="p244379171093535"></a><a name="p244379171093535"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p313133028093535"><a name="p313133028093535"></a><a name="p313133028093535"></a>virtual void </p>
<p id="p864390467093535"><a name="p864390467093535"></a><a name="p864390467093535"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row2141811469093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p515897290093535"><a name="p515897290093535"></a><a name="p515897290093535"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1729959216093535"><a name="p1729959216093535"></a><a name="p1729959216093535"></a>virtual int16_t </p>
<p id="p1117689040093535"><a name="p1117689040093535"></a><a name="p1117689040093535"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row193626400093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p186167062093535"><a name="p186167062093535"></a><a name="p186167062093535"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p494350373093535"><a name="p494350373093535"></a><a name="p494350373093535"></a>virtual void </p>
<p id="p1903508353093535"><a name="p1903508353093535"></a><a name="p1903508353093535"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1014432645093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p355935407093535"><a name="p355935407093535"></a><a name="p355935407093535"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1471324877093535"><a name="p1471324877093535"></a><a name="p1471324877093535"></a>virtual void </p>
<p id="p877995480093535"><a name="p877995480093535"></a><a name="p877995480093535"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row278601893093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p552182587093535"><a name="p552182587093535"></a><a name="p552182587093535"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1050541368093535"><a name="p1050541368093535"></a><a name="p1050541368093535"></a>int16_t </p>
<p id="p212190077093535"><a name="p212190077093535"></a><a name="p212190077093535"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1562827686093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1923228295093535"><a name="p1923228295093535"></a><a name="p1923228295093535"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1820131302093535"><a name="p1820131302093535"></a><a name="p1820131302093535"></a>virtual void </p>
<p id="p1734462633093535"><a name="p1734462633093535"></a><a name="p1734462633093535"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1633169713093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p871112864093535"><a name="p871112864093535"></a><a name="p871112864093535"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p495434675093535"><a name="p495434675093535"></a><a name="p495434675093535"></a>int16_t </p>
<p id="p243688208093535"><a name="p243688208093535"></a><a name="p243688208093535"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row2021490618093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p404176353093535"><a name="p404176353093535"></a><a name="p404176353093535"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2097430757093535"><a name="p2097430757093535"></a><a name="p2097430757093535"></a>virtual void </p>
<p id="p1306779887093535"><a name="p1306779887093535"></a><a name="p1306779887093535"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row2008304658093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p41593648093535"><a name="p41593648093535"></a><a name="p41593648093535"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1339798245093535"><a name="p1339798245093535"></a><a name="p1339798245093535"></a>virtual void </p>
<p id="p2040017539093535"><a name="p2040017539093535"></a><a name="p2040017539093535"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1735267450093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p55227253093535"><a name="p55227253093535"></a><a name="p55227253093535"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1803225528093535"><a name="p1803225528093535"></a><a name="p1803225528093535"></a>bool </p>
<p id="p64866347093535"><a name="p64866347093535"></a><a name="p64866347093535"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1646550177093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429499796093535"><a name="p429499796093535"></a><a name="p429499796093535"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2064987260093535"><a name="p2064987260093535"></a><a name="p2064987260093535"></a>void </p>
<p id="p1777514829093535"><a name="p1777514829093535"></a><a name="p1777514829093535"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row660909761093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p875238153093535"><a name="p875238153093535"></a><a name="p875238153093535"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p486202735093535"><a name="p486202735093535"></a><a name="p486202735093535"></a>void </p>
<p id="p1108562348093535"><a name="p1108562348093535"></a><a name="p1108562348093535"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1725293661093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p448548169093535"><a name="p448548169093535"></a><a name="p448548169093535"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p69527027093535"><a name="p69527027093535"></a><a name="p69527027093535"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p1031441395093535"><a name="p1031441395093535"></a><a name="p1031441395093535"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1565917778093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2082479630093535"><a name="p2082479630093535"></a><a name="p2082479630093535"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p318549472093535"><a name="p318549472093535"></a><a name="p318549472093535"></a>void </p>
<p id="p840251372093535"><a name="p840251372093535"></a><a name="p840251372093535"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row565605427093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1422596652093535"><a name="p1422596652093535"></a><a name="p1422596652093535"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1130909746093535"><a name="p1130909746093535"></a><a name="p1130909746093535"></a>const char * </p>
<p id="p1389637480093535"><a name="p1389637480093535"></a><a name="p1389637480093535"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row368419782093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p769269841093535"><a name="p769269841093535"></a><a name="p769269841093535"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p69318735093535"><a name="p69318735093535"></a><a name="p69318735093535"></a>void </p>
<p id="p781567045093535"><a name="p781567045093535"></a><a name="p781567045093535"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1110484455093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1627581989093535"><a name="p1627581989093535"></a><a name="p1627581989093535"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p131181486093535"><a name="p131181486093535"></a><a name="p131181486093535"></a>int16_t </p>
<p id="p1874482905093535"><a name="p1874482905093535"></a><a name="p1874482905093535"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1373817354093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1829283091093535"><a name="p1829283091093535"></a><a name="p1829283091093535"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1764426797093535"><a name="p1764426797093535"></a><a name="p1764426797093535"></a>virtual void </p>
<p id="p600386563093535"><a name="p600386563093535"></a><a name="p600386563093535"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1395078802093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2075667853093535"><a name="p2075667853093535"></a><a name="p2075667853093535"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p410651207093535"><a name="p410651207093535"></a><a name="p410651207093535"></a>void </p>
<p id="p1261942856093535"><a name="p1261942856093535"></a><a name="p1261942856093535"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1114593850093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298552879093535"><a name="p298552879093535"></a><a name="p298552879093535"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858803196093535"><a name="p858803196093535"></a><a name="p858803196093535"></a>void </p>
<p id="p347903569093535"><a name="p347903569093535"></a><a name="p347903569093535"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row2027160666093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p34899376093535"><a name="p34899376093535"></a><a name="p34899376093535"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p520205827093535"><a name="p520205827093535"></a><a name="p520205827093535"></a>void </p>
<p id="p882839926093535"><a name="p882839926093535"></a><a name="p882839926093535"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row553884808093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p848898253093535"><a name="p848898253093535"></a><a name="p848898253093535"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p364218367093535"><a name="p364218367093535"></a><a name="p364218367093535"></a>void </p>
<p id="p1239058190093535"><a name="p1239058190093535"></a><a name="p1239058190093535"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1005104971093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1208509100093535"><a name="p1208509100093535"></a><a name="p1208509100093535"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653786981093535"><a name="p1653786981093535"></a><a name="p1653786981093535"></a>void </p>
<p id="p1035949468093535"><a name="p1035949468093535"></a><a name="p1035949468093535"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1499597182093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1944651095093535"><a name="p1944651095093535"></a><a name="p1944651095093535"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p757097800093535"><a name="p757097800093535"></a><a name="p757097800093535"></a>void </p>
<p id="p737924909093535"><a name="p737924909093535"></a><a name="p737924909093535"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row359375557093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1544782971093535"><a name="p1544782971093535"></a><a name="p1544782971093535"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1851482349093535"><a name="p1851482349093535"></a><a name="p1851482349093535"></a>void </p>
<p id="p641606570093535"><a name="p641606570093535"></a><a name="p641606570093535"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row139557399093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1029568878093535"><a name="p1029568878093535"></a><a name="p1029568878093535"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1792729033093535"><a name="p1792729033093535"></a><a name="p1792729033093535"></a>void </p>
<p id="p68005250093535"><a name="p68005250093535"></a><a name="p68005250093535"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1757688523093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p587783732093535"><a name="p587783732093535"></a><a name="p587783732093535"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p130556486093535"><a name="p130556486093535"></a><a name="p130556486093535"></a>void </p>
<p id="p1224759855093535"><a name="p1224759855093535"></a><a name="p1224759855093535"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row584958861093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1047377634093535"><a name="p1047377634093535"></a><a name="p1047377634093535"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p113844957093535"><a name="p113844957093535"></a><a name="p113844957093535"></a>void </p>
<p id="p1587390435093535"><a name="p1587390435093535"></a><a name="p1587390435093535"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1913092361093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1281967939093535"><a name="p1281967939093535"></a><a name="p1281967939093535"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1520463660093535"><a name="p1520463660093535"></a><a name="p1520463660093535"></a>void </p>
<p id="p867241704093535"><a name="p867241704093535"></a><a name="p867241704093535"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row830093898093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p853375077093535"><a name="p853375077093535"></a><a name="p853375077093535"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p760038044093535"><a name="p760038044093535"></a><a name="p760038044093535"></a>void </p>
<p id="p749828714093535"><a name="p749828714093535"></a><a name="p749828714093535"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row954668269093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2047081883093535"><a name="p2047081883093535"></a><a name="p2047081883093535"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1372999137093535"><a name="p1372999137093535"></a><a name="p1372999137093535"></a>void </p>
<p id="p1373629491093535"><a name="p1373629491093535"></a><a name="p1373629491093535"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row380047711093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1640798446093535"><a name="p1640798446093535"></a><a name="p1640798446093535"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p189979752093535"><a name="p189979752093535"></a><a name="p189979752093535"></a>void </p>
<p id="p2025056701093535"><a name="p2025056701093535"></a><a name="p2025056701093535"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row575331977093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1526012728093535"><a name="p1526012728093535"></a><a name="p1526012728093535"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p627311178093535"><a name="p627311178093535"></a><a name="p627311178093535"></a>void </p>
<p id="p96027887093535"><a name="p96027887093535"></a><a name="p96027887093535"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row731025533093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p55854964093535"><a name="p55854964093535"></a><a name="p55854964093535"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p536199031093535"><a name="p536199031093535"></a><a name="p536199031093535"></a>virtual void </p>
<p id="p2031977198093535"><a name="p2031977198093535"></a><a name="p2031977198093535"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row389919736093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1596658042093535"><a name="p1596658042093535"></a><a name="p1596658042093535"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p216953619093535"><a name="p216953619093535"></a><a name="p216953619093535"></a>virtual void </p>
<p id="p658407022093535"><a name="p658407022093535"></a><a name="p658407022093535"></a>Sets a style. </p>
</td>
</tr>
<tr id="row414464744093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1312333104093535"><a name="p1312333104093535"></a><a name="p1312333104093535"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p540214235093535"><a name="p540214235093535"></a><a name="p540214235093535"></a>virtual int64_t </p>
<p id="p2036989480093535"><a name="p2036989480093535"></a><a name="p2036989480093535"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1646647337093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1116021057093535"><a name="p1116021057093535"></a><a name="p1116021057093535"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p609098372093535"><a name="p609098372093535"></a><a name="p609098372093535"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p901695295093535"><a name="p901695295093535"></a><a name="p901695295093535"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row606572211093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p51129253093535"><a name="p51129253093535"></a><a name="p51129253093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p434430303093535"><a name="p434430303093535"></a><a name="p434430303093535"></a>void * </p>
<p id="p303650657093535"><a name="p303650657093535"></a><a name="p303650657093535"></a>Overrides the <strong id="b2073260577093535"><a name="b2073260577093535"></a><a name="b2073260577093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row95453842093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p351914040093535"><a name="p351914040093535"></a><a name="p351914040093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2134562515093535"><a name="p2134562515093535"></a><a name="p2134562515093535"></a>void </p>
<p id="p357812687093535"><a name="p357812687093535"></a><a name="p357812687093535"></a>Overrides the <strong id="b154748887093535"><a name="b154748887093535"></a><a name="b154748887093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Protected Member Functions<a name="pro-methods"></a>

<a name="table2116625456093535"></a>
<table><thead align="left"><tr id="row1696512059093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p839943161093535"><a name="p839943161093535"></a><a name="p839943161093535"></a>Protected Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p870294331093535"><a name="p870294331093535"></a><a name="p870294331093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1752818134093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p338320852093535"><a name="p338320852093535"></a><a name="p338320852093535"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1562342830093535"><a name="p1562342830093535"></a><a name="p1562342830093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1185947141093535"><a name="p1185947141093535"></a><a name="p1185947141093535"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1742522570093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1687603743093535"><a name="p1687603743093535"></a><a name="p1687603743093535"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p355673595093535"><a name="p355673595093535"></a><a name="p355673595093535"></a>virtual void </p>
<p id="p305083110093535"><a name="p305083110093535"></a><a name="p305083110093535"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
</tbody>
</table>

## Protected Attributes<a name="pro-attribs"></a>

<a name="table513835193093535"></a>
<table><thead align="left"><tr id="row565936985093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1016917368093535"><a name="p1016917368093535"></a><a name="p1016917368093535"></a>Protected Attribute Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p288573233093535"><a name="p288573233093535"></a><a name="p288573233093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1355027406093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1830202765093535"><a name="p1830202765093535"></a><a name="p1830202765093535"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833668442093535"><a name="p833668442093535"></a><a name="p833668442093535"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row270171711093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1575400189093535"><a name="p1575400189093535"></a><a name="p1575400189093535"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p146856409093535"><a name="p146856409093535"></a><a name="p146856409093535"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row135606268093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p697358711093535"><a name="p697358711093535"></a><a name="p697358711093535"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1562473364093535"><a name="p1562473364093535"></a><a name="p1562473364093535"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row558725985093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p798352111093535"><a name="p798352111093535"></a><a name="p798352111093535"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p53338689093535"><a name="p53338689093535"></a><a name="p53338689093535"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row774906877093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1055061621093535"><a name="p1055061621093535"></a><a name="p1055061621093535"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904331741093535"><a name="p904331741093535"></a><a name="p904331741093535"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row495336950093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1962045456093535"><a name="p1962045456093535"></a><a name="p1962045456093535"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p533808847093535"><a name="p533808847093535"></a><a name="p533808847093535"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

