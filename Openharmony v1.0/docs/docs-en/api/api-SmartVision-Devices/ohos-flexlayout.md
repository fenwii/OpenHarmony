# OHOS::FlexLayout<a name="EN-US_TOPIC_0000001055078171"></a>

## **Overview**<a name="section136671101093535"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines a flexible layout container. You can perform simple adaptive layout on child views that the container holds, for example, to evenly arrange all child views in the same row or column. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section94004548093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table895788308093535"></a>
<table><thead align="left"><tr id="row1171885345093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p149445572093535"><a name="p149445572093535"></a><a name="p149445572093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1225426089093535"><a name="p1225426089093535"></a><a name="p1225426089093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1128889958093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1798902250093535"><a name="p1798902250093535"></a><a name="p1798902250093535"></a><a href="graphic.md#gac06da499194705b22e31a8a78022ceab">FlexLayout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p296001896093535"><a name="p296001896093535"></a><a name="p296001896093535"></a> </p>
<p id="p128578278093535"><a name="p128578278093535"></a><a name="p128578278093535"></a>A default constructor used to create a <strong id="b1649083675093535"><a name="b1649083675093535"></a><a name="b1649083675093535"></a><a href="ohos-flexlayout.md">FlexLayout</a></strong> instance. </p>
</td>
</tr>
<tr id="row143571193093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2009627160093535"><a name="p2009627160093535"></a><a name="p2009627160093535"></a><a href="graphic.md#gada390db4ca762cf1dac06abfcd74e543">~FlexLayout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p356060408093535"><a name="p356060408093535"></a><a name="p356060408093535"></a>virtual </p>
<p id="p352159233093535"><a name="p352159233093535"></a><a name="p352159233093535"></a>A destructor used to delete the <strong id="b217686737093535"><a name="b217686737093535"></a><a name="b217686737093535"></a><a href="ohos-flexlayout.md">FlexLayout</a></strong> instance. </p>
</td>
</tr>
<tr id="row1670662843093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p825598381093535"><a name="p825598381093535"></a><a name="p825598381093535"></a><a href="graphic.md#gaa683d4401ecb3c19a5b5c2cea1252636">SetMajorAxisAlign</a> (const AlignType &amp;align)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2063315470093535"><a name="p2063315470093535"></a><a name="p2063315470093535"></a>void </p>
<p id="p1921324576093535"><a name="p1921324576093535"></a><a name="p1921324576093535"></a>Sets the alignment mode of the primary axis (the axis where the layout direction is located). The child views in the layout are placed in this mode in the direction of the primary axis. </p>
</td>
</tr>
<tr id="row10399401093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790327513093535"><a name="p790327513093535"></a><a name="p790327513093535"></a><a href="graphic.md#gadb57c6de7bcd0c04cde8004019e32b32">SetSecondaryAxisAlign</a> (const AlignType &amp;align)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1435983201093535"><a name="p1435983201093535"></a><a name="p1435983201093535"></a>void </p>
<p id="p230963149093535"><a name="p230963149093535"></a><a name="p230963149093535"></a>Sets the alignment mode of the secondary axis (the axis perpendicular to the set layout direction). </p>
</td>
</tr>
<tr id="row122056267093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p416354032093535"><a name="p416354032093535"></a><a name="p416354032093535"></a><a href="graphic.md#gade436564eb29d29e32220863a6fe94e1">SetFlexWrap</a> (uint8_t wrap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p40488395093535"><a name="p40488395093535"></a><a name="p40488395093535"></a>void </p>
<p id="p636470364093535"><a name="p636470364093535"></a><a name="p636470364093535"></a>Sets whether to support word wrap. </p>
</td>
</tr>
<tr id="row709331525093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864728653093535"><a name="p1864728653093535"></a><a name="p1864728653093535"></a><a href="graphic.md#ga976abe5b006bef9018dd0d8ee2380526">LayoutChildren</a> (bool needInvalidate=false) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p826110817093535"><a name="p826110817093535"></a><a name="p826110817093535"></a>virtual void </p>
<p id="p332119143093535"><a name="p332119143093535"></a><a name="p332119143093535"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row654405277093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2125389728093535"><a name="p2125389728093535"></a><a name="p2125389728093535"></a><a href="graphic.md#gaba1ca0f86a85d3c5636ca543b0ed08d8">Layout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1189675827093535"><a name="p1189675827093535"></a><a name="p1189675827093535"></a> </p>
<p id="p1073227742093535"><a name="p1073227742093535"></a><a name="p1073227742093535"></a>A default constructor used to create a <strong id="b6215738093535"><a name="b6215738093535"></a><a name="b6215738093535"></a><a href="ohos-layout.md">Layout</a></strong> instance. </p>
</td>
</tr>
<tr id="row806691877093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p237542293093535"><a name="p237542293093535"></a><a name="p237542293093535"></a><a href="graphic.md#ga6c7cc7a849197fe014ea57d0534728bf">~Layout</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p435270054093535"><a name="p435270054093535"></a><a name="p435270054093535"></a>virtual </p>
<p id="p1314661798093535"><a name="p1314661798093535"></a><a name="p1314661798093535"></a>A destructor used to delete the <strong id="b645066304093535"><a name="b645066304093535"></a><a name="b645066304093535"></a><a href="ohos-layout.md">Layout</a></strong> instance. </p>
</td>
</tr>
<tr id="row1581428669093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p38235837093535"><a name="p38235837093535"></a><a name="p38235837093535"></a><a href="graphic.md#gada9223ec4d664c00a9640c8b9cbcacc3">SetLayoutDirection</a> (const <a href="codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a> &amp;direction)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1219657715093535"><a name="p1219657715093535"></a><a name="p1219657715093535"></a>void </p>
<p id="p1425338899093535"><a name="p1425338899093535"></a><a name="p1425338899093535"></a>Sets the layout direction. </p>
</td>
</tr>
<tr id="row1572806841093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1596935385093535"><a name="p1596935385093535"></a><a name="p1596935385093535"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p340506365093535"><a name="p340506365093535"></a><a name="p340506365093535"></a> </p>
<p id="p24290621093535"><a name="p24290621093535"></a><a name="p24290621093535"></a>A default constructor used to create a <strong id="b643983559093535"><a name="b643983559093535"></a><a name="b643983559093535"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row283624968093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2081935107093535"><a name="p2081935107093535"></a><a name="p2081935107093535"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1143253584093535"><a name="p1143253584093535"></a><a name="p1143253584093535"></a>virtual </p>
<p id="p1686234167093535"><a name="p1686234167093535"></a><a name="p1686234167093535"></a>A destructor used to delete the <strong id="b50375346093535"><a name="b50375346093535"></a><a name="b50375346093535"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1050721109093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p171089911093535"><a name="p171089911093535"></a><a name="p171089911093535"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179168233093535"><a name="p1179168233093535"></a><a name="p1179168233093535"></a>UIViewType </p>
<p id="p975746950093535"><a name="p975746950093535"></a><a name="p975746950093535"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row287025727093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1309028734093535"><a name="p1309028734093535"></a><a name="p1309028734093535"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1572318651093535"><a name="p1572318651093535"></a><a name="p1572318651093535"></a>virtual void </p>
<p id="p756647013093535"><a name="p756647013093535"></a><a name="p756647013093535"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row411141554093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1973155182093535"><a name="p1973155182093535"></a><a name="p1973155182093535"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2141650467093535"><a name="p2141650467093535"></a><a name="p2141650467093535"></a>virtual void </p>
<p id="p399673266093535"><a name="p399673266093535"></a><a name="p399673266093535"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1388022854093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1836553523093535"><a name="p1836553523093535"></a><a name="p1836553523093535"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p648353639093535"><a name="p648353639093535"></a><a name="p648353639093535"></a>virtual void </p>
<p id="p700319858093535"><a name="p700319858093535"></a><a name="p700319858093535"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row588330561093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p317465168093535"><a name="p317465168093535"></a><a name="p317465168093535"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1058830518093535"><a name="p1058830518093535"></a><a name="p1058830518093535"></a>virtual void </p>
<p id="p155194962093535"><a name="p155194962093535"></a><a name="p155194962093535"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1145042480093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p567905160093535"><a name="p567905160093535"></a><a name="p567905160093535"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p296979481093535"><a name="p296979481093535"></a><a name="p296979481093535"></a>virtual void </p>
<p id="p1399368814093535"><a name="p1399368814093535"></a><a name="p1399368814093535"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row2047724544093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p928031041093535"><a name="p928031041093535"></a><a name="p928031041093535"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1969537842093535"><a name="p1969537842093535"></a><a name="p1969537842093535"></a>virtual void </p>
<p id="p884328527093535"><a name="p884328527093535"></a><a name="p884328527093535"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row1226829036093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p83975770093535"><a name="p83975770093535"></a><a name="p83975770093535"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p300963256093535"><a name="p300963256093535"></a><a name="p300963256093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1762449338093535"><a name="p1762449338093535"></a><a name="p1762449338093535"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row258057990093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1785802969093535"><a name="p1785802969093535"></a><a name="p1785802969093535"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p334061834093535"><a name="p334061834093535"></a><a name="p334061834093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1343048361093535"><a name="p1343048361093535"></a><a name="p1343048361093535"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row1553176597093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244988441093535"><a name="p1244988441093535"></a><a name="p1244988441093535"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p452228428093535"><a name="p452228428093535"></a><a name="p452228428093535"></a>void </p>
<p id="p378295951093535"><a name="p378295951093535"></a><a name="p378295951093535"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1810595642093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1629620717093535"><a name="p1629620717093535"></a><a name="p1629620717093535"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1188580276093535"><a name="p1188580276093535"></a><a name="p1188580276093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1180749635093535"><a name="p1180749635093535"></a><a name="p1180749635093535"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row708716615093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p629206726093535"><a name="p629206726093535"></a><a name="p629206726093535"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p639767036093535"><a name="p639767036093535"></a><a name="p639767036093535"></a>void </p>
<p id="p406067659093535"><a name="p406067659093535"></a><a name="p406067659093535"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row1846089300093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1758859004093535"><a name="p1758859004093535"></a><a name="p1758859004093535"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p728565861093535"><a name="p728565861093535"></a><a name="p728565861093535"></a> </p>
<p id="p165034028093535"><a name="p165034028093535"></a><a name="p165034028093535"></a>A default constructor used to create an <strong id="b921427941093535"><a name="b921427941093535"></a><a name="b921427941093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1706615874093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p668528496093535"><a name="p668528496093535"></a><a name="p668528496093535"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1552945175093535"><a name="p1552945175093535"></a><a name="p1552945175093535"></a> </p>
<p id="p1200482638093535"><a name="p1200482638093535"></a><a name="p1200482638093535"></a>A constructor used to create an <strong id="b669524570093535"><a name="b669524570093535"></a><a name="b669524570093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1542440822093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p158249234093535"><a name="p158249234093535"></a><a name="p158249234093535"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1117631932093535"><a name="p1117631932093535"></a><a name="p1117631932093535"></a>virtual </p>
<p id="p33150406093535"><a name="p33150406093535"></a><a name="p33150406093535"></a>A destructor used to delete the <strong id="b728228060093535"><a name="b728228060093535"></a><a name="b728228060093535"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1105806209093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1269840650093535"><a name="p1269840650093535"></a><a name="p1269840650093535"></a><a href="graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620739982093535"><a name="p620739982093535"></a><a name="p620739982093535"></a>virtual bool </p>
<p id="p1987597737093535"><a name="p1987597737093535"></a><a name="p1987597737093535"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1232008945093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2046487666093535"><a name="p2046487666093535"></a><a name="p2046487666093535"></a><a href="graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1835039130093535"><a name="p1835039130093535"></a><a name="p1835039130093535"></a>virtual void </p>
<p id="p1319145915093535"><a name="p1319145915093535"></a><a name="p1319145915093535"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row2009096179093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1004914671093535"><a name="p1004914671093535"></a><a name="p1004914671093535"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1512848556093535"><a name="p1512848556093535"></a><a name="p1512848556093535"></a>virtual void </p>
<p id="p2015103633093535"><a name="p2015103633093535"></a><a name="p2015103633093535"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row444592427093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p86535380093535"><a name="p86535380093535"></a><a name="p86535380093535"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p967375466093535"><a name="p967375466093535"></a><a name="p967375466093535"></a>virtual void </p>
<p id="p1018975818093535"><a name="p1018975818093535"></a><a name="p1018975818093535"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row935997643093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p525237406093535"><a name="p525237406093535"></a><a name="p525237406093535"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p217274776093535"><a name="p217274776093535"></a><a name="p217274776093535"></a>void </p>
<p id="p1660011732093535"><a name="p1660011732093535"></a><a name="p1660011732093535"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1841261154093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p615107680093535"><a name="p615107680093535"></a><a name="p615107680093535"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1718555447093535"><a name="p1718555447093535"></a><a name="p1718555447093535"></a>void </p>
<p id="p1402096426093535"><a name="p1402096426093535"></a><a name="p1402096426093535"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row441640217093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1045498674093535"><a name="p1045498674093535"></a><a name="p1045498674093535"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p900393894093535"><a name="p900393894093535"></a><a name="p900393894093535"></a>virtual bool </p>
<p id="p135519459093535"><a name="p135519459093535"></a><a name="p135519459093535"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row207486979093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p292748072093535"><a name="p292748072093535"></a><a name="p292748072093535"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p856628293093535"><a name="p856628293093535"></a><a name="p856628293093535"></a>virtual bool </p>
<p id="p66165543093535"><a name="p66165543093535"></a><a name="p66165543093535"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1842922505093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1103112682093535"><a name="p1103112682093535"></a><a name="p1103112682093535"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p595507662093535"><a name="p595507662093535"></a><a name="p595507662093535"></a>virtual bool </p>
<p id="p1305772074093535"><a name="p1305772074093535"></a><a name="p1305772074093535"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1157182740093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p395710315093535"><a name="p395710315093535"></a><a name="p395710315093535"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p586128766093535"><a name="p586128766093535"></a><a name="p586128766093535"></a>virtual bool </p>
<p id="p604025168093535"><a name="p604025168093535"></a><a name="p604025168093535"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row950521726093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p784634263093535"><a name="p784634263093535"></a><a name="p784634263093535"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p531875103093535"><a name="p531875103093535"></a><a name="p531875103093535"></a>virtual void </p>
<p id="p108574141093535"><a name="p108574141093535"></a><a name="p108574141093535"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row195982741093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1383277714093535"><a name="p1383277714093535"></a><a name="p1383277714093535"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p478681014093535"><a name="p478681014093535"></a><a name="p478681014093535"></a>virtual void </p>
<p id="p1043440841093535"><a name="p1043440841093535"></a><a name="p1043440841093535"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1022271525093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1199600183093535"><a name="p1199600183093535"></a><a name="p1199600183093535"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1619335551093535"><a name="p1619335551093535"></a><a name="p1619335551093535"></a>virtual void </p>
<p id="p163279118093535"><a name="p163279118093535"></a><a name="p163279118093535"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1127619133093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p418172748093535"><a name="p418172748093535"></a><a name="p418172748093535"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1857460846093535"><a name="p1857460846093535"></a><a name="p1857460846093535"></a>virtual void </p>
<p id="p1724036884093535"><a name="p1724036884093535"></a><a name="p1724036884093535"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row252575293093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p597407588093535"><a name="p597407588093535"></a><a name="p597407588093535"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p832880315093535"><a name="p832880315093535"></a><a name="p832880315093535"></a>void </p>
<p id="p1932227244093535"><a name="p1932227244093535"></a><a name="p1932227244093535"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row289494764093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146339815093535"><a name="p2146339815093535"></a><a name="p2146339815093535"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p94480218093535"><a name="p94480218093535"></a><a name="p94480218093535"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p946426249093535"><a name="p946426249093535"></a><a name="p946426249093535"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row796766952093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p588652542093535"><a name="p588652542093535"></a><a name="p588652542093535"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1097975836093535"><a name="p1097975836093535"></a><a name="p1097975836093535"></a>void </p>
<p id="p1030522691093535"><a name="p1030522691093535"></a><a name="p1030522691093535"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1977010608093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1200926575093535"><a name="p1200926575093535"></a><a name="p1200926575093535"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p396110216093535"><a name="p396110216093535"></a><a name="p396110216093535"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p1775029058093535"><a name="p1775029058093535"></a><a name="p1775029058093535"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row708281179093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1515557909093535"><a name="p1515557909093535"></a><a name="p1515557909093535"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1036503289093535"><a name="p1036503289093535"></a><a name="p1036503289093535"></a>void </p>
<p id="p417552304093535"><a name="p417552304093535"></a><a name="p417552304093535"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1228099516093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1297638781093535"><a name="p1297638781093535"></a><a name="p1297638781093535"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278386426093535"><a name="p278386426093535"></a><a name="p278386426093535"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p1474678288093535"><a name="p1474678288093535"></a><a name="p1474678288093535"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row149593767093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1544530671093535"><a name="p1544530671093535"></a><a name="p1544530671093535"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p218418047093535"><a name="p218418047093535"></a><a name="p218418047093535"></a>void </p>
<p id="p627576083093535"><a name="p627576083093535"></a><a name="p627576083093535"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row615655264093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2008824751093535"><a name="p2008824751093535"></a><a name="p2008824751093535"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1913999475093535"><a name="p1913999475093535"></a><a name="p1913999475093535"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1566197075093535"><a name="p1566197075093535"></a><a name="p1566197075093535"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1996666220093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p862279661093535"><a name="p862279661093535"></a><a name="p862279661093535"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p403526556093535"><a name="p403526556093535"></a><a name="p403526556093535"></a>void </p>
<p id="p1390290370093535"><a name="p1390290370093535"></a><a name="p1390290370093535"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row721535174093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1339349314093535"><a name="p1339349314093535"></a><a name="p1339349314093535"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p768749926093535"><a name="p768749926093535"></a><a name="p768749926093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1075375753093535"><a name="p1075375753093535"></a><a name="p1075375753093535"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1147220138093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1378709473093535"><a name="p1378709473093535"></a><a name="p1378709473093535"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403171898093535"><a name="p1403171898093535"></a><a name="p1403171898093535"></a>void </p>
<p id="p1026473872093535"><a name="p1026473872093535"></a><a name="p1026473872093535"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row945169844093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907376759093535"><a name="p907376759093535"></a><a name="p907376759093535"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1311155283093535"><a name="p1311155283093535"></a><a name="p1311155283093535"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1681740891093535"><a name="p1681740891093535"></a><a name="p1681740891093535"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row456413035093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p429223545093535"><a name="p429223545093535"></a><a name="p429223545093535"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p323802910093535"><a name="p323802910093535"></a><a name="p323802910093535"></a>virtual void </p>
<p id="p1885118124093535"><a name="p1885118124093535"></a><a name="p1885118124093535"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1530783289093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1072502493093535"><a name="p1072502493093535"></a><a name="p1072502493093535"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p264269568093535"><a name="p264269568093535"></a><a name="p264269568093535"></a>bool </p>
<p id="p1449089765093535"><a name="p1449089765093535"></a><a name="p1449089765093535"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1905372539093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1835855477093535"><a name="p1835855477093535"></a><a name="p1835855477093535"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1734544406093535"><a name="p1734544406093535"></a><a name="p1734544406093535"></a>void </p>
<p id="p488969913093535"><a name="p488969913093535"></a><a name="p488969913093535"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1539690121093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2006179012093535"><a name="p2006179012093535"></a><a name="p2006179012093535"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p772355264093535"><a name="p772355264093535"></a><a name="p772355264093535"></a>bool </p>
<p id="p1722093567093535"><a name="p1722093567093535"></a><a name="p1722093567093535"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1285296894093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p491130164093535"><a name="p491130164093535"></a><a name="p491130164093535"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p841987160093535"><a name="p841987160093535"></a><a name="p841987160093535"></a>void </p>
<p id="p1624716641093535"><a name="p1624716641093535"></a><a name="p1624716641093535"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row879102387093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p288316182093535"><a name="p288316182093535"></a><a name="p288316182093535"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p849125348093535"><a name="p849125348093535"></a><a name="p849125348093535"></a>bool </p>
<p id="p1817958958093535"><a name="p1817958958093535"></a><a name="p1817958958093535"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row516814599093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p544760888093535"><a name="p544760888093535"></a><a name="p544760888093535"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1529560385093535"><a name="p1529560385093535"></a><a name="p1529560385093535"></a>void </p>
<p id="p2008320090093535"><a name="p2008320090093535"></a><a name="p2008320090093535"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1233419614093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p239432245093535"><a name="p239432245093535"></a><a name="p239432245093535"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763825560093535"><a name="p763825560093535"></a><a name="p763825560093535"></a>bool </p>
<p id="p1282015558093535"><a name="p1282015558093535"></a><a name="p1282015558093535"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row406198458093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2139558887093535"><a name="p2139558887093535"></a><a name="p2139558887093535"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p465910998093535"><a name="p465910998093535"></a><a name="p465910998093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p415659732093535"><a name="p415659732093535"></a><a name="p415659732093535"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row951623475093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p130475549093535"><a name="p130475549093535"></a><a name="p130475549093535"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p127379468093535"><a name="p127379468093535"></a><a name="p127379468093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1569814283093535"><a name="p1569814283093535"></a><a name="p1569814283093535"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1621537756093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p847289383093535"><a name="p847289383093535"></a><a name="p847289383093535"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p320520497093535"><a name="p320520497093535"></a><a name="p320520497093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p274971875093535"><a name="p274971875093535"></a><a name="p274971875093535"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row330359202093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1687653897093535"><a name="p1687653897093535"></a><a name="p1687653897093535"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1673888149093535"><a name="p1673888149093535"></a><a name="p1673888149093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1946347502093535"><a name="p1946347502093535"></a><a name="p1946347502093535"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1087687810093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p949252266093535"><a name="p949252266093535"></a><a name="p949252266093535"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1124275883093535"><a name="p1124275883093535"></a><a name="p1124275883093535"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1256508538093535"><a name="p1256508538093535"></a><a name="p1256508538093535"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1784027053093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1971584845093535"><a name="p1971584845093535"></a><a name="p1971584845093535"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1690799881093535"><a name="p1690799881093535"></a><a name="p1690799881093535"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1432336576093535"><a name="p1432336576093535"></a><a name="p1432336576093535"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1018012284093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1608656475093535"><a name="p1608656475093535"></a><a name="p1608656475093535"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1196215481093535"><a name="p1196215481093535"></a><a name="p1196215481093535"></a>void </p>
<p id="p984213919093535"><a name="p984213919093535"></a><a name="p984213919093535"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row528974369093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p952108793093535"><a name="p952108793093535"></a><a name="p952108793093535"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p559347281093535"><a name="p559347281093535"></a><a name="p559347281093535"></a>virtual void </p>
<p id="p1330252430093535"><a name="p1330252430093535"></a><a name="p1330252430093535"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1995943693093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1289619901093535"><a name="p1289619901093535"></a><a name="p1289619901093535"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p5652259093535"><a name="p5652259093535"></a><a name="p5652259093535"></a>virtual int16_t </p>
<p id="p1543774069093535"><a name="p1543774069093535"></a><a name="p1543774069093535"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1167235479093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p244039113093535"><a name="p244039113093535"></a><a name="p244039113093535"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1831271747093535"><a name="p1831271747093535"></a><a name="p1831271747093535"></a>virtual void </p>
<p id="p1665895308093535"><a name="p1665895308093535"></a><a name="p1665895308093535"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row986648443093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p976060855093535"><a name="p976060855093535"></a><a name="p976060855093535"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1645349324093535"><a name="p1645349324093535"></a><a name="p1645349324093535"></a>virtual int16_t </p>
<p id="p1219595821093535"><a name="p1219595821093535"></a><a name="p1219595821093535"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1288646231093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1089066546093535"><a name="p1089066546093535"></a><a name="p1089066546093535"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p768064672093535"><a name="p768064672093535"></a><a name="p768064672093535"></a>virtual void </p>
<p id="p1798755018093535"><a name="p1798755018093535"></a><a name="p1798755018093535"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row2094107769093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1893428385093535"><a name="p1893428385093535"></a><a name="p1893428385093535"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1566943077093535"><a name="p1566943077093535"></a><a name="p1566943077093535"></a>virtual void </p>
<p id="p1476919690093535"><a name="p1476919690093535"></a><a name="p1476919690093535"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1377046215093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1369333412093535"><a name="p1369333412093535"></a><a name="p1369333412093535"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1428094379093535"><a name="p1428094379093535"></a><a name="p1428094379093535"></a>int16_t </p>
<p id="p1204283313093535"><a name="p1204283313093535"></a><a name="p1204283313093535"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row472021491093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2080173025093535"><a name="p2080173025093535"></a><a name="p2080173025093535"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p671259083093535"><a name="p671259083093535"></a><a name="p671259083093535"></a>virtual void </p>
<p id="p992715285093535"><a name="p992715285093535"></a><a name="p992715285093535"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row2055422016093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2009706155093535"><a name="p2009706155093535"></a><a name="p2009706155093535"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1057243704093535"><a name="p1057243704093535"></a><a name="p1057243704093535"></a>int16_t </p>
<p id="p1685078899093535"><a name="p1685078899093535"></a><a name="p1685078899093535"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1063709536093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p391994468093535"><a name="p391994468093535"></a><a name="p391994468093535"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p915558397093535"><a name="p915558397093535"></a><a name="p915558397093535"></a>virtual void </p>
<p id="p1287532437093535"><a name="p1287532437093535"></a><a name="p1287532437093535"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row616684927093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2084072251093535"><a name="p2084072251093535"></a><a name="p2084072251093535"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p35070684093535"><a name="p35070684093535"></a><a name="p35070684093535"></a>virtual void </p>
<p id="p79791725093535"><a name="p79791725093535"></a><a name="p79791725093535"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row220660684093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1530929426093535"><a name="p1530929426093535"></a><a name="p1530929426093535"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1207827583093535"><a name="p1207827583093535"></a><a name="p1207827583093535"></a>bool </p>
<p id="p2036426022093535"><a name="p2036426022093535"></a><a name="p2036426022093535"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1546718599093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p448152113093535"><a name="p448152113093535"></a><a name="p448152113093535"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1163152308093535"><a name="p1163152308093535"></a><a name="p1163152308093535"></a>void </p>
<p id="p1766474368093535"><a name="p1766474368093535"></a><a name="p1766474368093535"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row200571741093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p5578659093535"><a name="p5578659093535"></a><a name="p5578659093535"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p416872932093535"><a name="p416872932093535"></a><a name="p416872932093535"></a>void </p>
<p id="p1123662426093535"><a name="p1123662426093535"></a><a name="p1123662426093535"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row665894838093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p372030954093535"><a name="p372030954093535"></a><a name="p372030954093535"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1357905548093535"><a name="p1357905548093535"></a><a name="p1357905548093535"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p1898091740093535"><a name="p1898091740093535"></a><a name="p1898091740093535"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row2059211785093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1886300640093535"><a name="p1886300640093535"></a><a name="p1886300640093535"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p29102908093535"><a name="p29102908093535"></a><a name="p29102908093535"></a>void </p>
<p id="p284360606093535"><a name="p284360606093535"></a><a name="p284360606093535"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1026062322093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p526893697093535"><a name="p526893697093535"></a><a name="p526893697093535"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p196397174093535"><a name="p196397174093535"></a><a name="p196397174093535"></a>const char * </p>
<p id="p1672862093093535"><a name="p1672862093093535"></a><a name="p1672862093093535"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row996598006093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1707396020093535"><a name="p1707396020093535"></a><a name="p1707396020093535"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p105296863093535"><a name="p105296863093535"></a><a name="p105296863093535"></a>void </p>
<p id="p874842557093535"><a name="p874842557093535"></a><a name="p874842557093535"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1231280952093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1302786148093535"><a name="p1302786148093535"></a><a name="p1302786148093535"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p537446817093535"><a name="p537446817093535"></a><a name="p537446817093535"></a>int16_t </p>
<p id="p661313915093535"><a name="p661313915093535"></a><a name="p661313915093535"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1124864089093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1386143010093535"><a name="p1386143010093535"></a><a name="p1386143010093535"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858193589093535"><a name="p858193589093535"></a><a name="p858193589093535"></a>void </p>
<p id="p1552192649093535"><a name="p1552192649093535"></a><a name="p1552192649093535"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row680304008093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p805663113093535"><a name="p805663113093535"></a><a name="p805663113093535"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1501316759093535"><a name="p1501316759093535"></a><a name="p1501316759093535"></a>void </p>
<p id="p63881337093535"><a name="p63881337093535"></a><a name="p63881337093535"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row726225863093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p978001625093535"><a name="p978001625093535"></a><a name="p978001625093535"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267511787093535"><a name="p267511787093535"></a><a name="p267511787093535"></a>void </p>
<p id="p1519730779093535"><a name="p1519730779093535"></a><a name="p1519730779093535"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1647681732093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p692796289093535"><a name="p692796289093535"></a><a name="p692796289093535"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p394777851093535"><a name="p394777851093535"></a><a name="p394777851093535"></a>void </p>
<p id="p1441997922093535"><a name="p1441997922093535"></a><a name="p1441997922093535"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1546357150093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1447588599093535"><a name="p1447588599093535"></a><a name="p1447588599093535"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p231036558093535"><a name="p231036558093535"></a><a name="p231036558093535"></a>void </p>
<p id="p504668498093535"><a name="p504668498093535"></a><a name="p504668498093535"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1205503212093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1276230737093535"><a name="p1276230737093535"></a><a name="p1276230737093535"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213249379093535"><a name="p213249379093535"></a><a name="p213249379093535"></a>void </p>
<p id="p281161366093535"><a name="p281161366093535"></a><a name="p281161366093535"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1544721523093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p725279070093535"><a name="p725279070093535"></a><a name="p725279070093535"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1271927350093535"><a name="p1271927350093535"></a><a name="p1271927350093535"></a>void </p>
<p id="p1130079793093535"><a name="p1130079793093535"></a><a name="p1130079793093535"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row167873737093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1722278949093535"><a name="p1722278949093535"></a><a name="p1722278949093535"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1419757075093535"><a name="p1419757075093535"></a><a name="p1419757075093535"></a>void </p>
<p id="p1293899510093535"><a name="p1293899510093535"></a><a name="p1293899510093535"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1153675617093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p758029113093535"><a name="p758029113093535"></a><a name="p758029113093535"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1314015894093535"><a name="p1314015894093535"></a><a name="p1314015894093535"></a>void </p>
<p id="p1865408516093535"><a name="p1865408516093535"></a><a name="p1865408516093535"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1124945391093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p889430537093535"><a name="p889430537093535"></a><a name="p889430537093535"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1856943166093535"><a name="p1856943166093535"></a><a name="p1856943166093535"></a>void </p>
<p id="p773032258093535"><a name="p773032258093535"></a><a name="p773032258093535"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1322973993093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2080837052093535"><a name="p2080837052093535"></a><a name="p2080837052093535"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p41395778093535"><a name="p41395778093535"></a><a name="p41395778093535"></a>void </p>
<p id="p546861759093535"><a name="p546861759093535"></a><a name="p546861759093535"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1792428970093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1151058493093535"><a name="p1151058493093535"></a><a name="p1151058493093535"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1260192282093535"><a name="p1260192282093535"></a><a name="p1260192282093535"></a>void </p>
<p id="p2116776296093535"><a name="p2116776296093535"></a><a name="p2116776296093535"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1128455029093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p230861897093535"><a name="p230861897093535"></a><a name="p230861897093535"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p81070369093535"><a name="p81070369093535"></a><a name="p81070369093535"></a>void </p>
<p id="p574812286093535"><a name="p574812286093535"></a><a name="p574812286093535"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row362063129093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p273412042093535"><a name="p273412042093535"></a><a name="p273412042093535"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1485237984093535"><a name="p1485237984093535"></a><a name="p1485237984093535"></a>void </p>
<p id="p446848545093535"><a name="p446848545093535"></a><a name="p446848545093535"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row165404551093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1684543556093535"><a name="p1684543556093535"></a><a name="p1684543556093535"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p940941305093535"><a name="p940941305093535"></a><a name="p940941305093535"></a>void </p>
<p id="p1488766791093535"><a name="p1488766791093535"></a><a name="p1488766791093535"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1049187837093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1460884276093535"><a name="p1460884276093535"></a><a name="p1460884276093535"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p980925695093535"><a name="p980925695093535"></a><a name="p980925695093535"></a>virtual void </p>
<p id="p802522372093535"><a name="p802522372093535"></a><a name="p802522372093535"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1834580351093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1474233765093535"><a name="p1474233765093535"></a><a name="p1474233765093535"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p64633177093535"><a name="p64633177093535"></a><a name="p64633177093535"></a>virtual void </p>
<p id="p1138824781093535"><a name="p1138824781093535"></a><a name="p1138824781093535"></a>Sets a style. </p>
</td>
</tr>
<tr id="row181865081093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1961147405093535"><a name="p1961147405093535"></a><a name="p1961147405093535"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052661592093535"><a name="p1052661592093535"></a><a name="p1052661592093535"></a>virtual int64_t </p>
<p id="p1877823234093535"><a name="p1877823234093535"></a><a name="p1877823234093535"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row150770587093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p641896204093535"><a name="p641896204093535"></a><a name="p641896204093535"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1275562832093535"><a name="p1275562832093535"></a><a name="p1275562832093535"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p324354087093535"><a name="p324354087093535"></a><a name="p324354087093535"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1354507894093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p376838925093535"><a name="p376838925093535"></a><a name="p376838925093535"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1749660621093535"><a name="p1749660621093535"></a><a name="p1749660621093535"></a>void * </p>
<p id="p1601030917093535"><a name="p1601030917093535"></a><a name="p1601030917093535"></a>Overrides the <strong id="b468317068093535"><a name="b468317068093535"></a><a name="b468317068093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row509743902093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911805574093535"><a name="p1911805574093535"></a><a name="p1911805574093535"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2033563590093535"><a name="p2033563590093535"></a><a name="p2033563590093535"></a>void </p>
<p id="p734931082093535"><a name="p734931082093535"></a><a name="p734931082093535"></a>Overrides the <strong id="b969785191093535"><a name="b969785191093535"></a><a name="b969785191093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table2059074100093535"></a>
<table><thead align="left"><tr id="row2096803868093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p705050370093535"><a name="p705050370093535"></a><a name="p705050370093535"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p738185786093535"><a name="p738185786093535"></a><a name="p738185786093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row10706073093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p928206136093535"><a name="p928206136093535"></a><a name="p928206136093535"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p271202986093535"><a name="p271202986093535"></a><a name="p271202986093535"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1214351105093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p805208532093535"><a name="p805208532093535"></a><a name="p805208532093535"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p143959072093535"><a name="p143959072093535"></a><a name="p143959072093535"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row1642015577093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220135600093535"><a name="p1220135600093535"></a><a name="p1220135600093535"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1359559785093535"><a name="p1359559785093535"></a><a name="p1359559785093535"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row578193114093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1907333413093535"><a name="p1907333413093535"></a><a name="p1907333413093535"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p410673038093535"><a name="p410673038093535"></a><a name="p410673038093535"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row1052543542093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1840102990093535"><a name="p1840102990093535"></a><a name="p1840102990093535"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1495139931093535"><a name="p1495139931093535"></a><a name="p1495139931093535"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1029288546093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1093658670093535"><a name="p1093658670093535"></a><a name="p1093658670093535"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2008777319093535"><a name="p2008777319093535"></a><a name="p2008777319093535"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1424355650093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1836087356093535"><a name="p1836087356093535"></a><a name="p1836087356093535"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1186981593093535"><a name="p1186981593093535"></a><a name="p1186981593093535"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row420469900093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p237113099093535"><a name="p237113099093535"></a><a name="p237113099093535"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p493739457093535"><a name="p493739457093535"></a><a name="p493739457093535"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

