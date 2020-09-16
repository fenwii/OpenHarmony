# OHOS::GridLayout<a name="EN-US_TOPIC_0000001054598193"></a>

## **Overview**<a name="section1210836219093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a grid layout container. You can perform simple grid layout on child views that the container holds. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1339143672093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table83695137093535"></a>
<table><thead align="left"><tr id="row140416109093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p995287923093535"><a name="p995287923093535"></a><a name="p995287923093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1574009407093535"><a name="p1574009407093535"></a><a name="p1574009407093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row89205263093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p8171982093535"><a name="p8171982093535"></a><a name="p8171982093535"></a><a href="graphic.md#ga9c612ad9265b7031ed95844277608b3e">GridLayout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p880037093093535"><a name="p880037093093535"></a><a name="p880037093093535"></a> </p>
<p id="p328846068093535"><a name="p328846068093535"></a><a name="p328846068093535"></a>A default constructor used to create a <strong id="b1066430642093535"><a name="b1066430642093535"></a><a name="b1066430642093535"></a><a href="ohos-gridlayout.md">GridLayout</a></strong> instance. </p>
</td>
</tr>
<tr id="row771278555093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1841442390093535"><a name="p1841442390093535"></a><a name="p1841442390093535"></a><a href="graphic.md#ga1c2e62760fdb7032341272197f376358">~GridLayout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p144535779093535"><a name="p144535779093535"></a><a name="p144535779093535"></a>virtual </p>
<p id="p560276236093535"><a name="p560276236093535"></a><a name="p560276236093535"></a>A destructor used to delete the <strong id="b1947280896093535"><a name="b1947280896093535"></a><a name="b1947280896093535"></a><a href="ohos-gridlayout.md">GridLayout</a></strong> instance. </p>
</td>
</tr>
<tr id="row985120995093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453712823093535"><a name="p453712823093535"></a><a name="p453712823093535"></a><a href="graphic.md#gac2df1f13d5ee6d2e6993c9a51eb9a716">SetRows</a> (const uint16_t &amp;rows)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213623840093535"><a name="p213623840093535"></a><a name="p213623840093535"></a>void </p>
<p id="p1737264845093535"><a name="p1737264845093535"></a><a name="p1737264845093535"></a>Sets the number of rows in a grid. </p>
</td>
</tr>
<tr id="row369730275093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2068052535093535"><a name="p2068052535093535"></a><a name="p2068052535093535"></a><a href="graphic.md#gab5737dec2f5c0bc812dee9c4bc7a796b">SetCols</a> (const uint16_t &amp;cols)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1727973547093535"><a name="p1727973547093535"></a><a name="p1727973547093535"></a>void </p>
<p id="p2034788824093535"><a name="p2034788824093535"></a><a name="p2034788824093535"></a>Sets the number of columns in a grid. </p>
</td>
</tr>
<tr id="row795574740093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1486150500093535"><a name="p1486150500093535"></a><a name="p1486150500093535"></a><a href="graphic.md#ga449c17a9fa3898aac9ac68a2c48363a3">LayoutChildren</a> (bool needInvalidate=false) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p466796203093535"><a name="p466796203093535"></a><a name="p466796203093535"></a>virtual void </p>
<p id="p1726002036093535"><a name="p1726002036093535"></a><a name="p1726002036093535"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1913084496093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1608021140093535"><a name="p1608021140093535"></a><a name="p1608021140093535"></a><a href="graphic.md#gaba1ca0f86a85d3c5636ca543b0ed08d8">Layout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1029024452093535"><a name="p1029024452093535"></a><a name="p1029024452093535"></a> </p>
<p id="p1060019351093535"><a name="p1060019351093535"></a><a name="p1060019351093535"></a>A default constructor used to create a <strong id="b379398368093535"><a name="b379398368093535"></a><a name="b379398368093535"></a><a href="ohos-layout.md">Layout</a></strong> instance. </p>
</td>
</tr>
<tr id="row2033290604093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1035981326093535"><a name="p1035981326093535"></a><a name="p1035981326093535"></a><a href="graphic.md#ga6c7cc7a849197fe014ea57d0534728bf">~Layout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1345022624093535"><a name="p1345022624093535"></a><a name="p1345022624093535"></a>virtual </p>
<p id="p566055052093535"><a name="p566055052093535"></a><a name="p566055052093535"></a>A destructor used to delete the <strong id="b1202847718093535"><a name="b1202847718093535"></a><a name="b1202847718093535"></a><a href="ohos-layout.md">Layout</a></strong> instance. </p>
</td>
</tr>
<tr id="row1352302494093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p197547377093535"><a name="p197547377093535"></a><a name="p197547377093535"></a><a href="graphic.md#gada9223ec4d664c00a9640c8b9cbcacc3">SetLayoutDirection</a> (const <a href="codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a> &amp;direction)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1870949457093535"><a name="p1870949457093535"></a><a name="p1870949457093535"></a>void </p>
<p id="p1250316972093535"><a name="p1250316972093535"></a><a name="p1250316972093535"></a>Sets the layout direction. </p>
</td>
</tr>
<tr id="row1746672660093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1571382370093535"><a name="p1571382370093535"></a><a name="p1571382370093535"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2019400828093535"><a name="p2019400828093535"></a><a name="p2019400828093535"></a> </p>
<p id="p920705053093535"><a name="p920705053093535"></a><a name="p920705053093535"></a>A default constructor used to create a <strong id="b790534368093535"><a name="b790534368093535"></a><a name="b790534368093535"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1835062414093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1574863176093535"><a name="p1574863176093535"></a><a name="p1574863176093535"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p635456842093535"><a name="p635456842093535"></a><a name="p635456842093535"></a>virtual </p>
<p id="p1559722125093535"><a name="p1559722125093535"></a><a name="p1559722125093535"></a>A destructor used to delete the <strong id="b293851589093535"><a name="b293851589093535"></a><a name="b293851589093535"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1217367317093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p249908216093535"><a name="p249908216093535"></a><a name="p249908216093535"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1947422943093535"><a name="p1947422943093535"></a><a name="p1947422943093535"></a>UIViewType </p>
<p id="p756902808093535"><a name="p756902808093535"></a><a name="p756902808093535"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row280949535093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2026921874093535"><a name="p2026921874093535"></a><a name="p2026921874093535"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p364555526093535"><a name="p364555526093535"></a><a name="p364555526093535"></a>virtual void </p>
<p id="p669996177093535"><a name="p669996177093535"></a><a name="p669996177093535"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row1051631003093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1224880770093535"><a name="p1224880770093535"></a><a name="p1224880770093535"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p370428313093535"><a name="p370428313093535"></a><a name="p370428313093535"></a>virtual void </p>
<p id="p2037352696093535"><a name="p2037352696093535"></a><a name="p2037352696093535"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1236486890093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p555005517093535"><a name="p555005517093535"></a><a name="p555005517093535"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1721342706093535"><a name="p1721342706093535"></a><a name="p1721342706093535"></a>virtual void </p>
<p id="p4792997093535"><a name="p4792997093535"></a><a name="p4792997093535"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row540317814093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p505743177093535"><a name="p505743177093535"></a><a name="p505743177093535"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1500656815093535"><a name="p1500656815093535"></a><a name="p1500656815093535"></a>virtual void </p>
<p id="p1635716705093535"><a name="p1635716705093535"></a><a name="p1635716705093535"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1542980208093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p662322718093535"><a name="p662322718093535"></a><a name="p662322718093535"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1777107185093535"><a name="p1777107185093535"></a><a name="p1777107185093535"></a>virtual void </p>
<p id="p349848794093535"><a name="p349848794093535"></a><a name="p349848794093535"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row241000863093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1654634817093535"><a name="p1654634817093535"></a><a name="p1654634817093535"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p683421795093535"><a name="p683421795093535"></a><a name="p683421795093535"></a>virtual void </p>
<p id="p1045506269093535"><a name="p1045506269093535"></a><a name="p1045506269093535"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row261978255093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1426915001093535"><a name="p1426915001093535"></a><a name="p1426915001093535"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1106232698093535"><a name="p1106232698093535"></a><a name="p1106232698093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1074558291093535"><a name="p1074558291093535"></a><a name="p1074558291093535"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row851689569093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1395491307093535"><a name="p1395491307093535"></a><a name="p1395491307093535"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2083105057093535"><a name="p2083105057093535"></a><a name="p2083105057093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1893521888093535"><a name="p1893521888093535"></a><a name="p1893521888093535"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row949969393093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p121387301093535"><a name="p121387301093535"></a><a name="p121387301093535"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1227810832093535"><a name="p1227810832093535"></a><a name="p1227810832093535"></a>void </p>
<p id="p1738920241093535"><a name="p1738920241093535"></a><a name="p1738920241093535"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row540876809093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1912066268093535"><a name="p1912066268093535"></a><a name="p1912066268093535"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p691586531093535"><a name="p691586531093535"></a><a name="p691586531093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p335817440093535"><a name="p335817440093535"></a><a name="p335817440093535"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row2129441040093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1469529487093535"><a name="p1469529487093535"></a><a name="p1469529487093535"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311726577093535"><a name="p311726577093535"></a><a name="p311726577093535"></a>void </p>
<p id="p926382245093535"><a name="p926382245093535"></a><a name="p926382245093535"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row1092615672093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p890513913093535"><a name="p890513913093535"></a><a name="p890513913093535"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p233000843093535"><a name="p233000843093535"></a><a name="p233000843093535"></a> </p>
<p id="p1347062682093535"><a name="p1347062682093535"></a><a name="p1347062682093535"></a>A default constructor used to create an <strong id="b619405638093535"><a name="b619405638093535"></a><a name="b619405638093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row912936862093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p543249332093535"><a name="p543249332093535"></a><a name="p543249332093535"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p180015633093535"><a name="p180015633093535"></a><a name="p180015633093535"></a> </p>
<p id="p1066046031093535"><a name="p1066046031093535"></a><a name="p1066046031093535"></a>A constructor used to create an <strong id="b22192656093535"><a name="b22192656093535"></a><a name="b22192656093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row847829371093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1185740329093535"><a name="p1185740329093535"></a><a name="p1185740329093535"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p175171026093535"><a name="p175171026093535"></a><a name="p175171026093535"></a>virtual </p>
<p id="p1616887691093535"><a name="p1616887691093535"></a><a name="p1616887691093535"></a>A destructor used to delete the <strong id="b1934658655093535"><a name="b1934658655093535"></a><a name="b1934658655093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1437236538093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p981760192093535"><a name="p981760192093535"></a><a name="p981760192093535"></a><a href="graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1310690506093535"><a name="p1310690506093535"></a><a name="p1310690506093535"></a>virtual bool </p>
<p id="p1451501354093535"><a name="p1451501354093535"></a><a name="p1451501354093535"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1887315974093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p469534982093535"><a name="p469534982093535"></a><a name="p469534982093535"></a><a href="graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1959950290093535"><a name="p1959950290093535"></a><a name="p1959950290093535"></a>virtual void </p>
<p id="p1545610718093535"><a name="p1545610718093535"></a><a name="p1545610718093535"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row502098259093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1922043261093535"><a name="p1922043261093535"></a><a name="p1922043261093535"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p694940163093535"><a name="p694940163093535"></a><a name="p694940163093535"></a>virtual void </p>
<p id="p1270818355093535"><a name="p1270818355093535"></a><a name="p1270818355093535"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row572338662093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1654353610093535"><a name="p1654353610093535"></a><a name="p1654353610093535"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1268783897093535"><a name="p1268783897093535"></a><a name="p1268783897093535"></a>virtual void </p>
<p id="p1542169221093535"><a name="p1542169221093535"></a><a name="p1542169221093535"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row2096044521093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p656626114093535"><a name="p656626114093535"></a><a name="p656626114093535"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p393105648093535"><a name="p393105648093535"></a><a name="p393105648093535"></a>void </p>
<p id="p222771560093535"><a name="p222771560093535"></a><a name="p222771560093535"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1143622564093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612537696093535"><a name="p612537696093535"></a><a name="p612537696093535"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650008356093535"><a name="p650008356093535"></a><a name="p650008356093535"></a>void </p>
<p id="p1624316846093535"><a name="p1624316846093535"></a><a name="p1624316846093535"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row795310380093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p742887141093535"><a name="p742887141093535"></a><a name="p742887141093535"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p576741311093535"><a name="p576741311093535"></a><a name="p576741311093535"></a>virtual bool </p>
<p id="p584797720093535"><a name="p584797720093535"></a><a name="p584797720093535"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1257454056093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1272928333093535"><a name="p1272928333093535"></a><a name="p1272928333093535"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p163318779093535"><a name="p163318779093535"></a><a name="p163318779093535"></a>virtual bool </p>
<p id="p2062183470093535"><a name="p2062183470093535"></a><a name="p2062183470093535"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1120393389093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1421093005093535"><a name="p1421093005093535"></a><a name="p1421093005093535"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1502388067093535"><a name="p1502388067093535"></a><a name="p1502388067093535"></a>virtual bool </p>
<p id="p1315530635093535"><a name="p1315530635093535"></a><a name="p1315530635093535"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1613111180093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413821851093535"><a name="p1413821851093535"></a><a name="p1413821851093535"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p68790145093535"><a name="p68790145093535"></a><a name="p68790145093535"></a>virtual bool </p>
<p id="p1023525011093535"><a name="p1023525011093535"></a><a name="p1023525011093535"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1876866661093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p166947263093535"><a name="p166947263093535"></a><a name="p166947263093535"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p127963880093535"><a name="p127963880093535"></a><a name="p127963880093535"></a>virtual void </p>
<p id="p1057967356093535"><a name="p1057967356093535"></a><a name="p1057967356093535"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row902048965093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1269502617093535"><a name="p1269502617093535"></a><a name="p1269502617093535"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846862017093535"><a name="p846862017093535"></a><a name="p846862017093535"></a>virtual void </p>
<p id="p39518249093535"><a name="p39518249093535"></a><a name="p39518249093535"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1189837935093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p600843574093535"><a name="p600843574093535"></a><a name="p600843574093535"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p385337880093535"><a name="p385337880093535"></a><a name="p385337880093535"></a>virtual void </p>
<p id="p35791563093535"><a name="p35791563093535"></a><a name="p35791563093535"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row910866179093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p117909957093535"><a name="p117909957093535"></a><a name="p117909957093535"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p385682181093535"><a name="p385682181093535"></a><a name="p385682181093535"></a>virtual void </p>
<p id="p806114162093535"><a name="p806114162093535"></a><a name="p806114162093535"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row921423344093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1303607960093535"><a name="p1303607960093535"></a><a name="p1303607960093535"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1096620708093535"><a name="p1096620708093535"></a><a name="p1096620708093535"></a>void </p>
<p id="p437046023093535"><a name="p437046023093535"></a><a name="p437046023093535"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1104507932093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1725309039093535"><a name="p1725309039093535"></a><a name="p1725309039093535"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1459248067093535"><a name="p1459248067093535"></a><a name="p1459248067093535"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p1149873972093535"><a name="p1149873972093535"></a><a name="p1149873972093535"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1136613388093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044552517093535"><a name="p2044552517093535"></a><a name="p2044552517093535"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96482805093535"><a name="p96482805093535"></a><a name="p96482805093535"></a>void </p>
<p id="p1218872010093535"><a name="p1218872010093535"></a><a name="p1218872010093535"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row555049730093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1988737031093535"><a name="p1988737031093535"></a><a name="p1988737031093535"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1400306759093535"><a name="p1400306759093535"></a><a name="p1400306759093535"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p381865883093535"><a name="p381865883093535"></a><a name="p381865883093535"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1895758769093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p679362344093535"><a name="p679362344093535"></a><a name="p679362344093535"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1821974270093535"><a name="p1821974270093535"></a><a name="p1821974270093535"></a>void </p>
<p id="p487838579093535"><a name="p487838579093535"></a><a name="p487838579093535"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row32398516093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1511167728093535"><a name="p1511167728093535"></a><a name="p1511167728093535"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p59872512093535"><a name="p59872512093535"></a><a name="p59872512093535"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p763920978093535"><a name="p763920978093535"></a><a name="p763920978093535"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row397469394093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1510526033093535"><a name="p1510526033093535"></a><a name="p1510526033093535"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1853928166093535"><a name="p1853928166093535"></a><a name="p1853928166093535"></a>void </p>
<p id="p534628752093535"><a name="p534628752093535"></a><a name="p534628752093535"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row270602543093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p222089066093535"><a name="p222089066093535"></a><a name="p222089066093535"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p359842385093535"><a name="p359842385093535"></a><a name="p359842385093535"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p788777520093535"><a name="p788777520093535"></a><a name="p788777520093535"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row902564309093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1048151768093535"><a name="p1048151768093535"></a><a name="p1048151768093535"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2010665971093535"><a name="p2010665971093535"></a><a name="p2010665971093535"></a>void </p>
<p id="p610068281093535"><a name="p610068281093535"></a><a name="p610068281093535"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1080775727093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1986711203093535"><a name="p1986711203093535"></a><a name="p1986711203093535"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p118676159093535"><a name="p118676159093535"></a><a name="p118676159093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1951790176093535"><a name="p1951790176093535"></a><a name="p1951790176093535"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row355171802093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p856845524093535"><a name="p856845524093535"></a><a name="p856845524093535"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p638514470093535"><a name="p638514470093535"></a><a name="p638514470093535"></a>void </p>
<p id="p764942506093535"><a name="p764942506093535"></a><a name="p764942506093535"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row593940222093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2059464706093535"><a name="p2059464706093535"></a><a name="p2059464706093535"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367027315093535"><a name="p1367027315093535"></a><a name="p1367027315093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1496698529093535"><a name="p1496698529093535"></a><a name="p1496698529093535"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row235638225093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p52500813093535"><a name="p52500813093535"></a><a name="p52500813093535"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p734424906093535"><a name="p734424906093535"></a><a name="p734424906093535"></a>virtual void </p>
<p id="p901025951093535"><a name="p901025951093535"></a><a name="p901025951093535"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1441407315093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p46806164093535"><a name="p46806164093535"></a><a name="p46806164093535"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p480213244093535"><a name="p480213244093535"></a><a name="p480213244093535"></a>bool </p>
<p id="p1208625366093535"><a name="p1208625366093535"></a><a name="p1208625366093535"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1489323076093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p722011135093535"><a name="p722011135093535"></a><a name="p722011135093535"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901736234093535"><a name="p1901736234093535"></a><a name="p1901736234093535"></a>void </p>
<p id="p521277002093535"><a name="p521277002093535"></a><a name="p521277002093535"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row934804705093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2015197458093535"><a name="p2015197458093535"></a><a name="p2015197458093535"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p177941784093535"><a name="p177941784093535"></a><a name="p177941784093535"></a>bool </p>
<p id="p705034674093535"><a name="p705034674093535"></a><a name="p705034674093535"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row255032570093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1952477241093535"><a name="p1952477241093535"></a><a name="p1952477241093535"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038727269093535"><a name="p1038727269093535"></a><a name="p1038727269093535"></a>void </p>
<p id="p1197078047093535"><a name="p1197078047093535"></a><a name="p1197078047093535"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1832470421093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p481143461093535"><a name="p481143461093535"></a><a name="p481143461093535"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1907634592093535"><a name="p1907634592093535"></a><a name="p1907634592093535"></a>bool </p>
<p id="p523505075093535"><a name="p523505075093535"></a><a name="p523505075093535"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1690948103093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p999637590093535"><a name="p999637590093535"></a><a name="p999637590093535"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p419812140093535"><a name="p419812140093535"></a><a name="p419812140093535"></a>void </p>
<p id="p1712412201093535"><a name="p1712412201093535"></a><a name="p1712412201093535"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row138793858093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p482956455093535"><a name="p482956455093535"></a><a name="p482956455093535"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p788934867093535"><a name="p788934867093535"></a><a name="p788934867093535"></a>bool </p>
<p id="p42479880093535"><a name="p42479880093535"></a><a name="p42479880093535"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1034247332093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1070409676093535"><a name="p1070409676093535"></a><a name="p1070409676093535"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p307244150093535"><a name="p307244150093535"></a><a name="p307244150093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1324096013093535"><a name="p1324096013093535"></a><a name="p1324096013093535"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row526683828093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p158381915093535"><a name="p158381915093535"></a><a name="p158381915093535"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763422383093535"><a name="p763422383093535"></a><a name="p763422383093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1257966456093535"><a name="p1257966456093535"></a><a name="p1257966456093535"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1273731648093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p413072282093535"><a name="p413072282093535"></a><a name="p413072282093535"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2045087247093535"><a name="p2045087247093535"></a><a name="p2045087247093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1841873214093535"><a name="p1841873214093535"></a><a name="p1841873214093535"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row2121533068093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p675662571093535"><a name="p675662571093535"></a><a name="p675662571093535"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650787270093535"><a name="p650787270093535"></a><a name="p650787270093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p544201774093535"><a name="p544201774093535"></a><a name="p544201774093535"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row758713224093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1117532397093535"><a name="p1117532397093535"></a><a name="p1117532397093535"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p932365921093535"><a name="p932365921093535"></a><a name="p932365921093535"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1622464858093535"><a name="p1622464858093535"></a><a name="p1622464858093535"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row715024562093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1566786271093535"><a name="p1566786271093535"></a><a name="p1566786271093535"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p27201676093535"><a name="p27201676093535"></a><a name="p27201676093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p115614551093535"><a name="p115614551093535"></a><a name="p115614551093535"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1622896277093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p169058739093535"><a name="p169058739093535"></a><a name="p169058739093535"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p972444323093535"><a name="p972444323093535"></a><a name="p972444323093535"></a>void </p>
<p id="p991041658093535"><a name="p991041658093535"></a><a name="p991041658093535"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1391002446093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1905154108093535"><a name="p1905154108093535"></a><a name="p1905154108093535"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2144389085093535"><a name="p2144389085093535"></a><a name="p2144389085093535"></a>virtual void </p>
<p id="p1356786715093535"><a name="p1356786715093535"></a><a name="p1356786715093535"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row200507233093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p661678564093535"><a name="p661678564093535"></a><a name="p661678564093535"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1373224449093535"><a name="p1373224449093535"></a><a name="p1373224449093535"></a>virtual int16_t </p>
<p id="p1538198523093535"><a name="p1538198523093535"></a><a name="p1538198523093535"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1005979136093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790096262093535"><a name="p790096262093535"></a><a name="p790096262093535"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p470433844093535"><a name="p470433844093535"></a><a name="p470433844093535"></a>virtual void </p>
<p id="p151064645093535"><a name="p151064645093535"></a><a name="p151064645093535"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1114485979093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1117269520093535"><a name="p1117269520093535"></a><a name="p1117269520093535"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1813211959093535"><a name="p1813211959093535"></a><a name="p1813211959093535"></a>virtual int16_t </p>
<p id="p1460773735093535"><a name="p1460773735093535"></a><a name="p1460773735093535"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row330402617093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p169182340093535"><a name="p169182340093535"></a><a name="p169182340093535"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964683964093535"><a name="p964683964093535"></a><a name="p964683964093535"></a>virtual void </p>
<p id="p1961523493093535"><a name="p1961523493093535"></a><a name="p1961523493093535"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row838369884093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p851867850093535"><a name="p851867850093535"></a><a name="p851867850093535"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1985606565093535"><a name="p1985606565093535"></a><a name="p1985606565093535"></a>virtual void </p>
<p id="p1244007878093535"><a name="p1244007878093535"></a><a name="p1244007878093535"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row703453158093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p970773153093535"><a name="p970773153093535"></a><a name="p970773153093535"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1512388481093535"><a name="p1512388481093535"></a><a name="p1512388481093535"></a>int16_t </p>
<p id="p1691614345093535"><a name="p1691614345093535"></a><a name="p1691614345093535"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1938164675093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1198250233093535"><a name="p1198250233093535"></a><a name="p1198250233093535"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p324428370093535"><a name="p324428370093535"></a><a name="p324428370093535"></a>virtual void </p>
<p id="p220357504093535"><a name="p220357504093535"></a><a name="p220357504093535"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row2012971434093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2134878485093535"><a name="p2134878485093535"></a><a name="p2134878485093535"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1051251484093535"><a name="p1051251484093535"></a><a name="p1051251484093535"></a>int16_t </p>
<p id="p419411842093535"><a name="p419411842093535"></a><a name="p419411842093535"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1975209246093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1858464573093535"><a name="p1858464573093535"></a><a name="p1858464573093535"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p398950709093535"><a name="p398950709093535"></a><a name="p398950709093535"></a>virtual void </p>
<p id="p501905695093535"><a name="p501905695093535"></a><a name="p501905695093535"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1315608650093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1391143217093535"><a name="p1391143217093535"></a><a name="p1391143217093535"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p517273991093535"><a name="p517273991093535"></a><a name="p517273991093535"></a>virtual void </p>
<p id="p1338450768093535"><a name="p1338450768093535"></a><a name="p1338450768093535"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row247658718093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p374544862093535"><a name="p374544862093535"></a><a name="p374544862093535"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448629429093535"><a name="p448629429093535"></a><a name="p448629429093535"></a>bool </p>
<p id="p729663761093535"><a name="p729663761093535"></a><a name="p729663761093535"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row513848952093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2131922863093535"><a name="p2131922863093535"></a><a name="p2131922863093535"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p486705328093535"><a name="p486705328093535"></a><a name="p486705328093535"></a>void </p>
<p id="p1664559205093535"><a name="p1664559205093535"></a><a name="p1664559205093535"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row664265464093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p201174095093535"><a name="p201174095093535"></a><a name="p201174095093535"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1741185220093535"><a name="p1741185220093535"></a><a name="p1741185220093535"></a>void </p>
<p id="p1418120708093535"><a name="p1418120708093535"></a><a name="p1418120708093535"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1221925674093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p632945901093535"><a name="p632945901093535"></a><a name="p632945901093535"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p402673795093535"><a name="p402673795093535"></a><a name="p402673795093535"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p1321843354093535"><a name="p1321843354093535"></a><a name="p1321843354093535"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row570739915093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p971340143093535"><a name="p971340143093535"></a><a name="p971340143093535"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1866728287093535"><a name="p1866728287093535"></a><a name="p1866728287093535"></a>void </p>
<p id="p874219147093535"><a name="p874219147093535"></a><a name="p874219147093535"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1312433146093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p928672218093535"><a name="p928672218093535"></a><a name="p928672218093535"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p899965461093535"><a name="p899965461093535"></a><a name="p899965461093535"></a>const char * </p>
<p id="p760521280093535"><a name="p760521280093535"></a><a name="p760521280093535"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row475513523093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p836660521093535"><a name="p836660521093535"></a><a name="p836660521093535"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p121317864093535"><a name="p121317864093535"></a><a name="p121317864093535"></a>void </p>
<p id="p1226389197093535"><a name="p1226389197093535"></a><a name="p1226389197093535"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1313644323093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p999285453093535"><a name="p999285453093535"></a><a name="p999285453093535"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311661219093535"><a name="p311661219093535"></a><a name="p311661219093535"></a>int16_t </p>
<p id="p2145015032093535"><a name="p2145015032093535"></a><a name="p2145015032093535"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1000070263093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p957944921093535"><a name="p957944921093535"></a><a name="p957944921093535"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1597197742093535"><a name="p1597197742093535"></a><a name="p1597197742093535"></a>void </p>
<p id="p2043951286093535"><a name="p2043951286093535"></a><a name="p2043951286093535"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row866892267093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1580336660093535"><a name="p1580336660093535"></a><a name="p1580336660093535"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1206777758093535"><a name="p1206777758093535"></a><a name="p1206777758093535"></a>void </p>
<p id="p1749452166093535"><a name="p1749452166093535"></a><a name="p1749452166093535"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1834525864093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381706351093535"><a name="p381706351093535"></a><a name="p381706351093535"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1018656234093535"><a name="p1018656234093535"></a><a name="p1018656234093535"></a>void </p>
<p id="p206561147093535"><a name="p206561147093535"></a><a name="p206561147093535"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1043882709093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1124567160093535"><a name="p1124567160093535"></a><a name="p1124567160093535"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p685436861093535"><a name="p685436861093535"></a><a name="p685436861093535"></a>void </p>
<p id="p401027490093535"><a name="p401027490093535"></a><a name="p401027490093535"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1089197280093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p782977547093535"><a name="p782977547093535"></a><a name="p782977547093535"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492083360093535"><a name="p492083360093535"></a><a name="p492083360093535"></a>void </p>
<p id="p992747310093535"><a name="p992747310093535"></a><a name="p992747310093535"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row553396113093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1267324848093535"><a name="p1267324848093535"></a><a name="p1267324848093535"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p633414066093535"><a name="p633414066093535"></a><a name="p633414066093535"></a>void </p>
<p id="p317428537093535"><a name="p317428537093535"></a><a name="p317428537093535"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1962022805093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p908012659093535"><a name="p908012659093535"></a><a name="p908012659093535"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p470529124093535"><a name="p470529124093535"></a><a name="p470529124093535"></a>void </p>
<p id="p1719052993093535"><a name="p1719052993093535"></a><a name="p1719052993093535"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row362388187093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p775046760093535"><a name="p775046760093535"></a><a name="p775046760093535"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p538822424093535"><a name="p538822424093535"></a><a name="p538822424093535"></a>void </p>
<p id="p765614727093535"><a name="p765614727093535"></a><a name="p765614727093535"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row439499634093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1423130857093535"><a name="p1423130857093535"></a><a name="p1423130857093535"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p896018118093535"><a name="p896018118093535"></a><a name="p896018118093535"></a>void </p>
<p id="p1262217231093535"><a name="p1262217231093535"></a><a name="p1262217231093535"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1091135183093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p534027367093535"><a name="p534027367093535"></a><a name="p534027367093535"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p292503837093535"><a name="p292503837093535"></a><a name="p292503837093535"></a>void </p>
<p id="p958989576093535"><a name="p958989576093535"></a><a name="p958989576093535"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1165741732093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1564151748093535"><a name="p1564151748093535"></a><a name="p1564151748093535"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1228185293093535"><a name="p1228185293093535"></a><a name="p1228185293093535"></a>void </p>
<p id="p1411041702093535"><a name="p1411041702093535"></a><a name="p1411041702093535"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row2082232824093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1270696007093535"><a name="p1270696007093535"></a><a name="p1270696007093535"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1807985436093535"><a name="p1807985436093535"></a><a name="p1807985436093535"></a>void </p>
<p id="p457189398093535"><a name="p457189398093535"></a><a name="p457189398093535"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row663884876093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1480822805093535"><a name="p1480822805093535"></a><a name="p1480822805093535"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1794108134093535"><a name="p1794108134093535"></a><a name="p1794108134093535"></a>void </p>
<p id="p1310735165093535"><a name="p1310735165093535"></a><a name="p1310735165093535"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1839851989093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2083684564093535"><a name="p2083684564093535"></a><a name="p2083684564093535"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p925221709093535"><a name="p925221709093535"></a><a name="p925221709093535"></a>void </p>
<p id="p554748419093535"><a name="p554748419093535"></a><a name="p554748419093535"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1648098492093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1625368271093535"><a name="p1625368271093535"></a><a name="p1625368271093535"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p194842385093535"><a name="p194842385093535"></a><a name="p194842385093535"></a>void </p>
<p id="p1615181765093535"><a name="p1615181765093535"></a><a name="p1615181765093535"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row191414527093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1171500122093535"><a name="p1171500122093535"></a><a name="p1171500122093535"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1361436823093535"><a name="p1361436823093535"></a><a name="p1361436823093535"></a>virtual void </p>
<p id="p1283306892093535"><a name="p1283306892093535"></a><a name="p1283306892093535"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row489673342093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p322976808093535"><a name="p322976808093535"></a><a name="p322976808093535"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p63969323093535"><a name="p63969323093535"></a><a name="p63969323093535"></a>virtual void </p>
<p id="p573057501093535"><a name="p573057501093535"></a><a name="p573057501093535"></a>Sets a style. </p>
</td>
</tr>
<tr id="row659776546093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1667891651093535"><a name="p1667891651093535"></a><a name="p1667891651093535"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p829056848093535"><a name="p829056848093535"></a><a name="p829056848093535"></a>virtual int64_t </p>
<p id="p1797116761093535"><a name="p1797116761093535"></a><a name="p1797116761093535"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row440909033093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p885779831093535"><a name="p885779831093535"></a><a name="p885779831093535"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1401096149093535"><a name="p1401096149093535"></a><a name="p1401096149093535"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p1509349805093535"><a name="p1509349805093535"></a><a name="p1509349805093535"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row2077808543093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p935474313093535"><a name="p935474313093535"></a><a name="p935474313093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p864373677093535"><a name="p864373677093535"></a><a name="p864373677093535"></a>void * </p>
<p id="p1732456235093535"><a name="p1732456235093535"></a><a name="p1732456235093535"></a>Overrides the <strong id="b2127888646093535"><a name="b2127888646093535"></a><a name="b2127888646093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row755177568093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1860476069093535"><a name="p1860476069093535"></a><a name="p1860476069093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p157496969093535"><a name="p157496969093535"></a><a name="p157496969093535"></a>void </p>
<p id="p1801273472093535"><a name="p1801273472093535"></a><a name="p1801273472093535"></a>Overrides the <strong id="b2021386794093535"><a name="b2021386794093535"></a><a name="b2021386794093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table353735943093535"></a>
<table><thead align="left"><tr id="row595605837093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p24971547093535"><a name="p24971547093535"></a><a name="p24971547093535"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1419538810093535"><a name="p1419538810093535"></a><a name="p1419538810093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1594477392093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1370052059093535"><a name="p1370052059093535"></a><a name="p1370052059093535"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p678334480093535"><a name="p678334480093535"></a><a name="p678334480093535"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1188399931093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p344267541093535"><a name="p344267541093535"></a><a name="p344267541093535"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1064699767093535"><a name="p1064699767093535"></a><a name="p1064699767093535"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row1303029656093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p988652269093535"><a name="p988652269093535"></a><a name="p988652269093535"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1325348704093535"><a name="p1325348704093535"></a><a name="p1325348704093535"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row559935805093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p525635156093535"><a name="p525635156093535"></a><a name="p525635156093535"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p522094760093535"><a name="p522094760093535"></a><a name="p522094760093535"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row119150711093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1412643266093535"><a name="p1412643266093535"></a><a name="p1412643266093535"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p15316093535"><a name="p15316093535"></a><a name="p15316093535"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row618456950093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1875710279093535"><a name="p1875710279093535"></a><a name="p1875710279093535"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p221304036093535"><a name="p221304036093535"></a><a name="p221304036093535"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1808177231093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1870356468093535"><a name="p1870356468093535"></a><a name="p1870356468093535"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1819498435093535"><a name="p1819498435093535"></a><a name="p1819498435093535"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1825984012093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1381539777093535"><a name="p1381539777093535"></a><a name="p1381539777093535"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1788382950093535"><a name="p1788382950093535"></a><a name="p1788382950093535"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

