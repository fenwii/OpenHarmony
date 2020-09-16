# OHOS::UIXAxis<a name="EN-US_TOPIC_0000001054479585"></a>

## **Overview**<a name="section1527426257093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the unique attributes and functions for the x-axis. This class is used in  [UIChart](ohos-uichart.md). 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1662419083093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table384676778093533"></a>
<table><thead align="left"><tr id="row471016318093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p348394688093533"><a name="p348394688093533"></a><a name="p348394688093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p920499957093533"><a name="p920499957093533"></a><a name="p920499957093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1770112566093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1850770247093533"><a name="p1850770247093533"></a><a name="p1850770247093533"></a><a href="graphic.md#ga8cc8e2c8249360ccfc89462fff33ca4a">UIXAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p734696885093533"><a name="p734696885093533"></a><a name="p734696885093533"></a> </p>
<p id="p1549667230093533"><a name="p1549667230093533"></a><a name="p1549667230093533"></a>A constructor used to create a <strong id="b1289463055093533"><a name="b1289463055093533"></a><a name="b1289463055093533"></a><a href="ohos-uixaxis.md">UIXAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row1612403568093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p995389745093533"><a name="p995389745093533"></a><a name="p995389745093533"></a><a href="graphic.md#gaa4e8939fb25fc20dd93ed030044b019f">~UIXAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1522939592093533"><a name="p1522939592093533"></a><a name="p1522939592093533"></a>virtual </p>
<p id="p1298704938093533"><a name="p1298704938093533"></a><a name="p1298704938093533"></a>A destructor used to delete the <strong id="b894071563093533"><a name="b894071563093533"></a><a name="b894071563093533"></a><a href="ohos-uixaxis.md">UIXAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row44557394093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p79164531093533"><a name="p79164531093533"></a><a name="p79164531093533"></a><a href="graphic.md#ga9407ddab6d7e65fc075ca37b86163e6f">TranslateToPixel</a> (int16_t &amp;value) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1538850586093533"><a name="p1538850586093533"></a><a name="p1538850586093533"></a>void </p>
<p id="p1515050406093533"><a name="p1515050406093533"></a><a name="p1515050406093533"></a>Translates data into the x coordinate of a pixel. </p>
</td>
</tr>
<tr id="row2111921886093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1739734676093533"><a name="p1739734676093533"></a><a name="p1739734676093533"></a><a href="graphic.md#ga2181796eef584a71a5db9186399720aa">SetDataRange</a> (uint16_t min, uint16_t max) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p782038310093533"><a name="p782038310093533"></a><a name="p782038310093533"></a>bool </p>
<p id="p70641151093533"><a name="p70641151093533"></a><a name="p70641151093533"></a>Sets the value range of the X axis. </p>
</td>
</tr>
<tr id="row1199579476093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p619474948093533"><a name="p619474948093533"></a><a name="p619474948093533"></a><a href="graphic.md#ga46f4151f1379809749ab2ba364d55170">SetMarkNum</a> (uint16_t count) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p966912189093533"><a name="p966912189093533"></a><a name="p966912189093533"></a>void </p>
<p id="p378875883093533"><a name="p378875883093533"></a><a name="p378875883093533"></a>Sets the number of scales on the x-axis. </p>
</td>
</tr>
<tr id="row663105393093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2113420407093533"><a name="p2113420407093533"></a><a name="p2113420407093533"></a><a href="graphic.md#gad79f1c694abce57af451b8f7b0b17c35">UIAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p660966370093533"><a name="p660966370093533"></a><a name="p660966370093533"></a> </p>
<p id="p1969975729093533"><a name="p1969975729093533"></a><a name="p1969975729093533"></a>A constructor used to create a <strong id="b150345002093533"><a name="b150345002093533"></a><a name="b150345002093533"></a><a href="ohos-uiaxis.md">UIAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row1154300167093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p721230350093533"><a name="p721230350093533"></a><a name="p721230350093533"></a><a href="graphic.md#gaacc9ac178b3b235f1186297021eb98d8">~UIAxis</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p48716575093533"><a name="p48716575093533"></a><a name="p48716575093533"></a>virtual </p>
<p id="p1084850440093533"><a name="p1084850440093533"></a><a name="p1084850440093533"></a>A destructor used to delete the <strong id="b67159730093533"><a name="b67159730093533"></a><a name="b67159730093533"></a><a href="ohos-uiaxis.md">UIAxis</a></strong> instance. </p>
</td>
</tr>
<tr id="row137815805093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1878664446093533"><a name="p1878664446093533"></a><a name="p1878664446093533"></a><a href="graphic.md#ga2f46b702f1543c5076a8957a94a780d3">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1665348754093533"><a name="p1665348754093533"></a><a name="p1665348754093533"></a>UIViewType </p>
<p id="p873925628093533"><a name="p873925628093533"></a><a name="p873925628093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1736925847093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p840565234093533"><a name="p840565234093533"></a><a name="p840565234093533"></a><a href="graphic.md#ga8ceec5e67fa2c4f161bd9af1f0788bbe">SetLineColor</a> (const <a href="ohos-color32.md">ColorType</a> &amp;color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1581979555093533"><a name="p1581979555093533"></a><a name="p1581979555093533"></a>void </p>
<p id="p73836976093533"><a name="p73836976093533"></a><a name="p73836976093533"></a>Sets the line color of the coordinate axis. </p>
</td>
</tr>
<tr id="row675295005093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1835780188093533"><a name="p1835780188093533"></a><a name="p1835780188093533"></a><a href="graphic.md#ga5360803f425055de52af5f7fa1081cfe">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p499429622093533"><a name="p499429622093533"></a><a name="p499429622093533"></a>void </p>
<p id="p639043688093533"><a name="p639043688093533"></a><a name="p639043688093533"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1389733022093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1785486227093533"><a name="p1785486227093533"></a><a name="p1785486227093533"></a><a href="graphic.md#gad1bf4d83270c0a4ba04f3cffbc67bb97">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567318355093533"><a name="p1567318355093533"></a><a name="p1567318355093533"></a>bool </p>
<p id="p807258534093533"><a name="p807258534093533"></a><a name="p807258534093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1286623306093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1322477385093533"><a name="p1322477385093533"></a><a name="p1322477385093533"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142473864093533"><a name="p142473864093533"></a><a name="p142473864093533"></a> </p>
<p id="p1793409265093533"><a name="p1793409265093533"></a><a name="p1793409265093533"></a>A default constructor used to create a <strong id="b612219347093533"><a name="b612219347093533"></a><a name="b612219347093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row723230851093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2059759435093533"><a name="p2059759435093533"></a><a name="p2059759435093533"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1453456795093533"><a name="p1453456795093533"></a><a name="p1453456795093533"></a>virtual </p>
<p id="p1583689054093533"><a name="p1583689054093533"></a><a name="p1583689054093533"></a>A destructor used to delete the <strong id="b1968010651093533"><a name="b1968010651093533"></a><a name="b1968010651093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1700343306093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1416414768093533"><a name="p1416414768093533"></a><a name="p1416414768093533"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p860567930093533"><a name="p860567930093533"></a><a name="p860567930093533"></a>UIViewType </p>
<p id="p1318460494093533"><a name="p1318460494093533"></a><a name="p1318460494093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1216099191093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2111779329093533"><a name="p2111779329093533"></a><a name="p2111779329093533"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1867075319093533"><a name="p1867075319093533"></a><a name="p1867075319093533"></a>virtual void </p>
<p id="p1989821906093533"><a name="p1989821906093533"></a><a name="p1989821906093533"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row1725462176093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1583307428093533"><a name="p1583307428093533"></a><a name="p1583307428093533"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1350549376093533"><a name="p1350549376093533"></a><a name="p1350549376093533"></a>virtual void </p>
<p id="p2138154038093533"><a name="p2138154038093533"></a><a name="p2138154038093533"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row699792122093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1087886590093533"><a name="p1087886590093533"></a><a name="p1087886590093533"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1412146623093533"><a name="p1412146623093533"></a><a name="p1412146623093533"></a>virtual void </p>
<p id="p140317926093533"><a name="p140317926093533"></a><a name="p140317926093533"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row1461224284093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p848229838093533"><a name="p848229838093533"></a><a name="p848229838093533"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p868155769093533"><a name="p868155769093533"></a><a name="p868155769093533"></a>virtual void </p>
<p id="p712410517093533"><a name="p712410517093533"></a><a name="p712410517093533"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1279498501093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1914353102093533"><a name="p1914353102093533"></a><a name="p1914353102093533"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p219349401093533"><a name="p219349401093533"></a><a name="p219349401093533"></a>virtual void </p>
<p id="p748348068093533"><a name="p748348068093533"></a><a name="p748348068093533"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row127433717093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p287327562093533"><a name="p287327562093533"></a><a name="p287327562093533"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1283726740093533"><a name="p1283726740093533"></a><a name="p1283726740093533"></a>virtual void </p>
<p id="p676409343093533"><a name="p676409343093533"></a><a name="p676409343093533"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row1689061837093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1537197537093533"><a name="p1537197537093533"></a><a name="p1537197537093533"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p738414514093533"><a name="p738414514093533"></a><a name="p738414514093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p123035870093533"><a name="p123035870093533"></a><a name="p123035870093533"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row783538059093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1563617661093533"><a name="p1563617661093533"></a><a name="p1563617661093533"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1306369914093533"><a name="p1306369914093533"></a><a name="p1306369914093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p2030140505093533"><a name="p2030140505093533"></a><a name="p2030140505093533"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row1271335499093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1363893175093533"><a name="p1363893175093533"></a><a name="p1363893175093533"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1103173356093533"><a name="p1103173356093533"></a><a name="p1103173356093533"></a>void </p>
<p id="p1985070381093533"><a name="p1985070381093533"></a><a name="p1985070381093533"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row115988667093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401853714093533"><a name="p1401853714093533"></a><a name="p1401853714093533"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1286383784093533"><a name="p1286383784093533"></a><a name="p1286383784093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1916554088093533"><a name="p1916554088093533"></a><a name="p1916554088093533"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row1005980061093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p307133945093533"><a name="p307133945093533"></a><a name="p307133945093533"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p831808217093533"><a name="p831808217093533"></a><a name="p831808217093533"></a>void </p>
<p id="p296156442093533"><a name="p296156442093533"></a><a name="p296156442093533"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row1207421333093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1348486505093533"><a name="p1348486505093533"></a><a name="p1348486505093533"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577265245093533"><a name="p577265245093533"></a><a name="p577265245093533"></a> </p>
<p id="p1297682839093533"><a name="p1297682839093533"></a><a name="p1297682839093533"></a>A default constructor used to create an <strong id="b829104735093533"><a name="b829104735093533"></a><a name="b829104735093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1907704909093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2009545958093533"><a name="p2009545958093533"></a><a name="p2009545958093533"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572398659093533"><a name="p572398659093533"></a><a name="p572398659093533"></a> </p>
<p id="p461193403093533"><a name="p461193403093533"></a><a name="p461193403093533"></a>A constructor used to create an <strong id="b1834721176093533"><a name="b1834721176093533"></a><a name="b1834721176093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row596546091093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p500134939093533"><a name="p500134939093533"></a><a name="p500134939093533"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1283679894093533"><a name="p1283679894093533"></a><a name="p1283679894093533"></a>virtual </p>
<p id="p879667472093533"><a name="p879667472093533"></a><a name="p879667472093533"></a>A destructor used to delete the <strong id="b2010689683093533"><a name="b2010689683093533"></a><a name="b2010689683093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row908283247093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1340568974093533"><a name="p1340568974093533"></a><a name="p1340568974093533"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2011471782093533"><a name="p2011471782093533"></a><a name="p2011471782093533"></a>virtual void </p>
<p id="p713730047093533"><a name="p713730047093533"></a><a name="p713730047093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1916282603093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1395196875093533"><a name="p1395196875093533"></a><a name="p1395196875093533"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1590197309093533"><a name="p1590197309093533"></a><a name="p1590197309093533"></a>virtual void </p>
<p id="p1470539766093533"><a name="p1470539766093533"></a><a name="p1470539766093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1217074965093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1316262975093533"><a name="p1316262975093533"></a><a name="p1316262975093533"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p873565000093533"><a name="p873565000093533"></a><a name="p873565000093533"></a>void </p>
<p id="p1821331256093533"><a name="p1821331256093533"></a><a name="p1821331256093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1799485940093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p715266739093533"><a name="p715266739093533"></a><a name="p715266739093533"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p479759764093533"><a name="p479759764093533"></a><a name="p479759764093533"></a>void </p>
<p id="p1911945567093533"><a name="p1911945567093533"></a><a name="p1911945567093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1834717243093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1826740483093533"><a name="p1826740483093533"></a><a name="p1826740483093533"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p767342782093533"><a name="p767342782093533"></a><a name="p767342782093533"></a>virtual bool </p>
<p id="p2048118093093533"><a name="p2048118093093533"></a><a name="p2048118093093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1748744469093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2075183133093533"><a name="p2075183133093533"></a><a name="p2075183133093533"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1622331332093533"><a name="p1622331332093533"></a><a name="p1622331332093533"></a>virtual bool </p>
<p id="p1040566798093533"><a name="p1040566798093533"></a><a name="p1040566798093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row241941193093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1007185483093533"><a name="p1007185483093533"></a><a name="p1007185483093533"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1627126699093533"><a name="p1627126699093533"></a><a name="p1627126699093533"></a>virtual bool </p>
<p id="p2135874964093533"><a name="p2135874964093533"></a><a name="p2135874964093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1167788341093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1146588717093533"><a name="p1146588717093533"></a><a name="p1146588717093533"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2026717046093533"><a name="p2026717046093533"></a><a name="p2026717046093533"></a>virtual bool </p>
<p id="p1326758559093533"><a name="p1326758559093533"></a><a name="p1326758559093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1756036468093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1594852383093533"><a name="p1594852383093533"></a><a name="p1594852383093533"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1125134987093533"><a name="p1125134987093533"></a><a name="p1125134987093533"></a>virtual void </p>
<p id="p2102905150093533"><a name="p2102905150093533"></a><a name="p2102905150093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row388580539093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1775285852093533"><a name="p1775285852093533"></a><a name="p1775285852093533"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388723569093533"><a name="p388723569093533"></a><a name="p388723569093533"></a>virtual void </p>
<p id="p808660369093533"><a name="p808660369093533"></a><a name="p808660369093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row324441417093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p860547444093533"><a name="p860547444093533"></a><a name="p860547444093533"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1233358306093533"><a name="p1233358306093533"></a><a name="p1233358306093533"></a>virtual void </p>
<p id="p2051704318093533"><a name="p2051704318093533"></a><a name="p2051704318093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row454218793093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p290326098093533"><a name="p290326098093533"></a><a name="p290326098093533"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1193757778093533"><a name="p1193757778093533"></a><a name="p1193757778093533"></a>virtual void </p>
<p id="p872054921093533"><a name="p872054921093533"></a><a name="p872054921093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row403734413093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p258837346093533"><a name="p258837346093533"></a><a name="p258837346093533"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1921320011093533"><a name="p1921320011093533"></a><a name="p1921320011093533"></a>void </p>
<p id="p1371731339093533"><a name="p1371731339093533"></a><a name="p1371731339093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row666219988093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p483469185093533"><a name="p483469185093533"></a><a name="p483469185093533"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1627782179093533"><a name="p1627782179093533"></a><a name="p1627782179093533"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p914946044093533"><a name="p914946044093533"></a><a name="p914946044093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row675453094093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p197927007093533"><a name="p197927007093533"></a><a name="p197927007093533"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1680658532093533"><a name="p1680658532093533"></a><a name="p1680658532093533"></a>void </p>
<p id="p30880130093533"><a name="p30880130093533"></a><a name="p30880130093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row282091730093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1751939515093533"><a name="p1751939515093533"></a><a name="p1751939515093533"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p614586281093533"><a name="p614586281093533"></a><a name="p614586281093533"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p977927534093533"><a name="p977927534093533"></a><a name="p977927534093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row616211951093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p597665031093533"><a name="p597665031093533"></a><a name="p597665031093533"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601012266093533"><a name="p1601012266093533"></a><a name="p1601012266093533"></a>void </p>
<p id="p1393813298093533"><a name="p1393813298093533"></a><a name="p1393813298093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row896732166093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2094252269093533"><a name="p2094252269093533"></a><a name="p2094252269093533"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1070511475093533"><a name="p1070511475093533"></a><a name="p1070511475093533"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p1679343992093533"><a name="p1679343992093533"></a><a name="p1679343992093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1417941835093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p278622477093533"><a name="p278622477093533"></a><a name="p278622477093533"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1502358267093533"><a name="p1502358267093533"></a><a name="p1502358267093533"></a>void </p>
<p id="p1497958411093533"><a name="p1497958411093533"></a><a name="p1497958411093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row554410022093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1059133154093533"><a name="p1059133154093533"></a><a name="p1059133154093533"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p176619311093533"><a name="p176619311093533"></a><a name="p176619311093533"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p702863185093533"><a name="p702863185093533"></a><a name="p702863185093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row58144060093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p306148919093533"><a name="p306148919093533"></a><a name="p306148919093533"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1818318852093533"><a name="p1818318852093533"></a><a name="p1818318852093533"></a>void </p>
<p id="p573354175093533"><a name="p573354175093533"></a><a name="p573354175093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1514584109093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p507764601093533"><a name="p507764601093533"></a><a name="p507764601093533"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1140430794093533"><a name="p1140430794093533"></a><a name="p1140430794093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p289991612093533"><a name="p289991612093533"></a><a name="p289991612093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row693404892093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1657387585093533"><a name="p1657387585093533"></a><a name="p1657387585093533"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1348826686093533"><a name="p1348826686093533"></a><a name="p1348826686093533"></a>void </p>
<p id="p786011932093533"><a name="p786011932093533"></a><a name="p786011932093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1295462723093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p189945858093533"><a name="p189945858093533"></a><a name="p189945858093533"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p952963829093533"><a name="p952963829093533"></a><a name="p952963829093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1605237444093533"><a name="p1605237444093533"></a><a name="p1605237444093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1261215691093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1277994784093533"><a name="p1277994784093533"></a><a name="p1277994784093533"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p476171218093533"><a name="p476171218093533"></a><a name="p476171218093533"></a>virtual void </p>
<p id="p701247059093533"><a name="p701247059093533"></a><a name="p701247059093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row526664024093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p76297995093533"><a name="p76297995093533"></a><a name="p76297995093533"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1422595835093533"><a name="p1422595835093533"></a><a name="p1422595835093533"></a>bool </p>
<p id="p1860332308093533"><a name="p1860332308093533"></a><a name="p1860332308093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1154385409093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1115749361093533"><a name="p1115749361093533"></a><a name="p1115749361093533"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p41425253093533"><a name="p41425253093533"></a><a name="p41425253093533"></a>void </p>
<p id="p1366139660093533"><a name="p1366139660093533"></a><a name="p1366139660093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row414259322093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2056081155093533"><a name="p2056081155093533"></a><a name="p2056081155093533"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p614163745093533"><a name="p614163745093533"></a><a name="p614163745093533"></a>bool </p>
<p id="p761611575093533"><a name="p761611575093533"></a><a name="p761611575093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row49719639093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1695047463093533"><a name="p1695047463093533"></a><a name="p1695047463093533"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p747733206093533"><a name="p747733206093533"></a><a name="p747733206093533"></a>void </p>
<p id="p160173959093533"><a name="p160173959093533"></a><a name="p160173959093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row2007979403093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1774094354093533"><a name="p1774094354093533"></a><a name="p1774094354093533"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p955231361093533"><a name="p955231361093533"></a><a name="p955231361093533"></a>bool </p>
<p id="p132812689093533"><a name="p132812689093533"></a><a name="p132812689093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1766874858093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p443331023093533"><a name="p443331023093533"></a><a name="p443331023093533"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1817715351093533"><a name="p1817715351093533"></a><a name="p1817715351093533"></a>void </p>
<p id="p2111596377093533"><a name="p2111596377093533"></a><a name="p2111596377093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1692986709093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p33698322093533"><a name="p33698322093533"></a><a name="p33698322093533"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1023475381093533"><a name="p1023475381093533"></a><a name="p1023475381093533"></a>bool </p>
<p id="p1189250843093533"><a name="p1189250843093533"></a><a name="p1189250843093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1883758207093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p904660132093533"><a name="p904660132093533"></a><a name="p904660132093533"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p97125412093533"><a name="p97125412093533"></a><a name="p97125412093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p434200762093533"><a name="p434200762093533"></a><a name="p434200762093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1041820558093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p489810208093533"><a name="p489810208093533"></a><a name="p489810208093533"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1053608561093533"><a name="p1053608561093533"></a><a name="p1053608561093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1998848717093533"><a name="p1998848717093533"></a><a name="p1998848717093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1119031557093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617920074093533"><a name="p617920074093533"></a><a name="p617920074093533"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1648840133093533"><a name="p1648840133093533"></a><a name="p1648840133093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1823303050093533"><a name="p1823303050093533"></a><a name="p1823303050093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1954544548093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p646796195093533"><a name="p646796195093533"></a><a name="p646796195093533"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388904757093533"><a name="p388904757093533"></a><a name="p388904757093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p2036807605093533"><a name="p2036807605093533"></a><a name="p2036807605093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1694848224093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p188752296093533"><a name="p188752296093533"></a><a name="p188752296093533"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1693827882093533"><a name="p1693827882093533"></a><a name="p1693827882093533"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1419047946093533"><a name="p1419047946093533"></a><a name="p1419047946093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1040134346093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p768319871093533"><a name="p768319871093533"></a><a name="p768319871093533"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179771469093533"><a name="p1179771469093533"></a><a name="p1179771469093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p2065122385093533"><a name="p2065122385093533"></a><a name="p2065122385093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1071088415093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549323175093533"><a name="p549323175093533"></a><a name="p549323175093533"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p290716798093533"><a name="p290716798093533"></a><a name="p290716798093533"></a>void </p>
<p id="p1196275747093533"><a name="p1196275747093533"></a><a name="p1196275747093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1697941246093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1782310686093533"><a name="p1782310686093533"></a><a name="p1782310686093533"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2049746554093533"><a name="p2049746554093533"></a><a name="p2049746554093533"></a>virtual void </p>
<p id="p760493316093533"><a name="p760493316093533"></a><a name="p760493316093533"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1118778863093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p218349715093533"><a name="p218349715093533"></a><a name="p218349715093533"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p959600938093533"><a name="p959600938093533"></a><a name="p959600938093533"></a>virtual int16_t </p>
<p id="p370482409093533"><a name="p370482409093533"></a><a name="p370482409093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1638398778093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p169783120093533"><a name="p169783120093533"></a><a name="p169783120093533"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1310651930093533"><a name="p1310651930093533"></a><a name="p1310651930093533"></a>virtual void </p>
<p id="p34279516093533"><a name="p34279516093533"></a><a name="p34279516093533"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1039374597093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1480549120093533"><a name="p1480549120093533"></a><a name="p1480549120093533"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1911164295093533"><a name="p1911164295093533"></a><a name="p1911164295093533"></a>virtual int16_t </p>
<p id="p1510867848093533"><a name="p1510867848093533"></a><a name="p1510867848093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1238199312093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p323956389093533"><a name="p323956389093533"></a><a name="p323956389093533"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1031284045093533"><a name="p1031284045093533"></a><a name="p1031284045093533"></a>virtual void </p>
<p id="p26344532093533"><a name="p26344532093533"></a><a name="p26344532093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row678361507093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p59926766093533"><a name="p59926766093533"></a><a name="p59926766093533"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059602787093533"><a name="p1059602787093533"></a><a name="p1059602787093533"></a>virtual void </p>
<p id="p439521644093533"><a name="p439521644093533"></a><a name="p439521644093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row373442325093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1218257930093533"><a name="p1218257930093533"></a><a name="p1218257930093533"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137922005093533"><a name="p2137922005093533"></a><a name="p2137922005093533"></a>int16_t </p>
<p id="p86674486093533"><a name="p86674486093533"></a><a name="p86674486093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1257855225093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p891847164093533"><a name="p891847164093533"></a><a name="p891847164093533"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p120707546093533"><a name="p120707546093533"></a><a name="p120707546093533"></a>virtual void </p>
<p id="p1683925178093533"><a name="p1683925178093533"></a><a name="p1683925178093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row2137398391093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1521686366093533"><a name="p1521686366093533"></a><a name="p1521686366093533"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p45007167093533"><a name="p45007167093533"></a><a name="p45007167093533"></a>int16_t </p>
<p id="p833735966093533"><a name="p833735966093533"></a><a name="p833735966093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1363375844093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1843252359093533"><a name="p1843252359093533"></a><a name="p1843252359093533"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p679347687093533"><a name="p679347687093533"></a><a name="p679347687093533"></a>virtual void </p>
<p id="p459139127093533"><a name="p459139127093533"></a><a name="p459139127093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row997327794093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1377306231093533"><a name="p1377306231093533"></a><a name="p1377306231093533"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751171093533"><a name="p751171093533"></a><a name="p751171093533"></a>virtual void </p>
<p id="p832499033093533"><a name="p832499033093533"></a><a name="p832499033093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row2123455945093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p996083504093533"><a name="p996083504093533"></a><a name="p996083504093533"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p517802905093533"><a name="p517802905093533"></a><a name="p517802905093533"></a>bool </p>
<p id="p43995803093533"><a name="p43995803093533"></a><a name="p43995803093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row324962524093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p584496565093533"><a name="p584496565093533"></a><a name="p584496565093533"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p748692518093533"><a name="p748692518093533"></a><a name="p748692518093533"></a>void </p>
<p id="p351618672093533"><a name="p351618672093533"></a><a name="p351618672093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1336710495093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1629446435093533"><a name="p1629446435093533"></a><a name="p1629446435093533"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p547332750093533"><a name="p547332750093533"></a><a name="p547332750093533"></a>void </p>
<p id="p472520186093533"><a name="p472520186093533"></a><a name="p472520186093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row706236829093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1392539446093533"><a name="p1392539446093533"></a><a name="p1392539446093533"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p673056535093533"><a name="p673056535093533"></a><a name="p673056535093533"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p1427974834093533"><a name="p1427974834093533"></a><a name="p1427974834093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row2032831206093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1528276502093533"><a name="p1528276502093533"></a><a name="p1528276502093533"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p58469636093533"><a name="p58469636093533"></a><a name="p58469636093533"></a>void </p>
<p id="p899303395093533"><a name="p899303395093533"></a><a name="p899303395093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1365233403093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p433260446093533"><a name="p433260446093533"></a><a name="p433260446093533"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p98717395093533"><a name="p98717395093533"></a><a name="p98717395093533"></a>const char * </p>
<p id="p1261708875093533"><a name="p1261708875093533"></a><a name="p1261708875093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1265775829093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p852643931093533"><a name="p852643931093533"></a><a name="p852643931093533"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p954981405093533"><a name="p954981405093533"></a><a name="p954981405093533"></a>void </p>
<p id="p1342650970093533"><a name="p1342650970093533"></a><a name="p1342650970093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row110323359093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p279222029093533"><a name="p279222029093533"></a><a name="p279222029093533"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p998238379093533"><a name="p998238379093533"></a><a name="p998238379093533"></a>int16_t </p>
<p id="p1151175164093533"><a name="p1151175164093533"></a><a name="p1151175164093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1816821279093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p28079374093533"><a name="p28079374093533"></a><a name="p28079374093533"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p994239268093533"><a name="p994239268093533"></a><a name="p994239268093533"></a>virtual void </p>
<p id="p35475225093533"><a name="p35475225093533"></a><a name="p35475225093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row620025267093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p472295910093533"><a name="p472295910093533"></a><a name="p472295910093533"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p673773509093533"><a name="p673773509093533"></a><a name="p673773509093533"></a>void </p>
<p id="p1463526536093533"><a name="p1463526536093533"></a><a name="p1463526536093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row276477535093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p788047120093533"><a name="p788047120093533"></a><a name="p788047120093533"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p395240895093533"><a name="p395240895093533"></a><a name="p395240895093533"></a>void </p>
<p id="p2052925470093533"><a name="p2052925470093533"></a><a name="p2052925470093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1403440006093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1945045505093533"><a name="p1945045505093533"></a><a name="p1945045505093533"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179885963093533"><a name="p1179885963093533"></a><a name="p1179885963093533"></a>void </p>
<p id="p663715836093533"><a name="p663715836093533"></a><a name="p663715836093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row54928557093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p704288252093533"><a name="p704288252093533"></a><a name="p704288252093533"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1485918827093533"><a name="p1485918827093533"></a><a name="p1485918827093533"></a>void </p>
<p id="p401042316093533"><a name="p401042316093533"></a><a name="p401042316093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row970178817093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1344230546093533"><a name="p1344230546093533"></a><a name="p1344230546093533"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2065713261093533"><a name="p2065713261093533"></a><a name="p2065713261093533"></a>void </p>
<p id="p1022397775093533"><a name="p1022397775093533"></a><a name="p1022397775093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row212469298093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2082608811093533"><a name="p2082608811093533"></a><a name="p2082608811093533"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p671127394093533"><a name="p671127394093533"></a><a name="p671127394093533"></a>void </p>
<p id="p883683635093533"><a name="p883683635093533"></a><a name="p883683635093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row109590558093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p973601715093533"><a name="p973601715093533"></a><a name="p973601715093533"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1531014217093533"><a name="p1531014217093533"></a><a name="p1531014217093533"></a>void </p>
<p id="p444910243093533"><a name="p444910243093533"></a><a name="p444910243093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row492892848093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p488365863093533"><a name="p488365863093533"></a><a name="p488365863093533"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p120141323093533"><a name="p120141323093533"></a><a name="p120141323093533"></a>void </p>
<p id="p28561846093533"><a name="p28561846093533"></a><a name="p28561846093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1652320914093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1943538675093533"><a name="p1943538675093533"></a><a name="p1943538675093533"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p388008452093533"><a name="p388008452093533"></a><a name="p388008452093533"></a>void </p>
<p id="p606746381093533"><a name="p606746381093533"></a><a name="p606746381093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1492840061093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1056576679093533"><a name="p1056576679093533"></a><a name="p1056576679093533"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p578973250093533"><a name="p578973250093533"></a><a name="p578973250093533"></a>void </p>
<p id="p1619288365093533"><a name="p1619288365093533"></a><a name="p1619288365093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row392323700093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2030636469093533"><a name="p2030636469093533"></a><a name="p2030636469093533"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p142912736093533"><a name="p142912736093533"></a><a name="p142912736093533"></a>void </p>
<p id="p896715284093533"><a name="p896715284093533"></a><a name="p896715284093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1745846515093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p427703397093533"><a name="p427703397093533"></a><a name="p427703397093533"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1488400681093533"><a name="p1488400681093533"></a><a name="p1488400681093533"></a>void </p>
<p id="p1007008067093533"><a name="p1007008067093533"></a><a name="p1007008067093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1042174397093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1452123467093533"><a name="p1452123467093533"></a><a name="p1452123467093533"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p928436769093533"><a name="p928436769093533"></a><a name="p928436769093533"></a>void </p>
<p id="p1791420870093533"><a name="p1791420870093533"></a><a name="p1791420870093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1121561376093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1547611830093533"><a name="p1547611830093533"></a><a name="p1547611830093533"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p689732396093533"><a name="p689732396093533"></a><a name="p689732396093533"></a>void </p>
<p id="p1038806164093533"><a name="p1038806164093533"></a><a name="p1038806164093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row490846516093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1443645385093533"><a name="p1443645385093533"></a><a name="p1443645385093533"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p313281983093533"><a name="p313281983093533"></a><a name="p313281983093533"></a>void </p>
<p id="p1314988896093533"><a name="p1314988896093533"></a><a name="p1314988896093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row258107629093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p359285638093533"><a name="p359285638093533"></a><a name="p359285638093533"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p206548554093533"><a name="p206548554093533"></a><a name="p206548554093533"></a>virtual void </p>
<p id="p1094454960093533"><a name="p1094454960093533"></a><a name="p1094454960093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1323538693093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1894122319093533"><a name="p1894122319093533"></a><a name="p1894122319093533"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p70332451093533"><a name="p70332451093533"></a><a name="p70332451093533"></a>virtual void </p>
<p id="p2120469953093533"><a name="p2120469953093533"></a><a name="p2120469953093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row933487718093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p859736367093533"><a name="p859736367093533"></a><a name="p859736367093533"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p608162358093533"><a name="p608162358093533"></a><a name="p608162358093533"></a>virtual int64_t </p>
<p id="p1865861862093533"><a name="p1865861862093533"></a><a name="p1865861862093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row794769209093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1853433792093533"><a name="p1853433792093533"></a><a name="p1853433792093533"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2136565935093533"><a name="p2136565935093533"></a><a name="p2136565935093533"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p1457429177093533"><a name="p1457429177093533"></a><a name="p1457429177093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row771095248093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1541106377093533"><a name="p1541106377093533"></a><a name="p1541106377093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1970952273093533"><a name="p1970952273093533"></a><a name="p1970952273093533"></a>void * </p>
<p id="p1259504306093533"><a name="p1259504306093533"></a><a name="p1259504306093533"></a>Overrides the <strong id="b1890281699093533"><a name="b1890281699093533"></a><a name="b1890281699093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row719674444093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1470099166093533"><a name="p1470099166093533"></a><a name="p1470099166093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1874664467093533"><a name="p1874664467093533"></a><a name="p1874664467093533"></a>void </p>
<p id="p922314646093533"><a name="p922314646093533"></a><a name="p922314646093533"></a>Overrides the <strong id="b946158394093533"><a name="b946158394093533"></a><a name="b946158394093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1063682998093533"></a>
<table><thead align="left"><tr id="row179290744093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1328540039093533"><a name="p1328540039093533"></a><a name="p1328540039093533"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p705146007093533"><a name="p705146007093533"></a><a name="p705146007093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row733719587093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p117261020093533"><a name="p117261020093533"></a><a name="p117261020093533"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p158490328093533"><a name="p158490328093533"></a><a name="p158490328093533"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row365097768093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1548112949093533"><a name="p1548112949093533"></a><a name="p1548112949093533"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1179123895093533"><a name="p1179123895093533"></a><a name="p1179123895093533"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row1282290228093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p444699404093533"><a name="p444699404093533"></a><a name="p444699404093533"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1409413161093533"><a name="p1409413161093533"></a><a name="p1409413161093533"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row2058377116093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p331569637093533"><a name="p331569637093533"></a><a name="p331569637093533"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p37862810093533"><a name="p37862810093533"></a><a name="p37862810093533"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row1607035724093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106167440093533"><a name="p2106167440093533"></a><a name="p2106167440093533"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1113328702093533"><a name="p1113328702093533"></a><a name="p1113328702093533"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1786651597093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p999062847093533"><a name="p999062847093533"></a><a name="p999062847093533"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932783054093533"><a name="p1932783054093533"></a><a name="p1932783054093533"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row836919629093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p113689817093533"><a name="p113689817093533"></a><a name="p113689817093533"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p569067079093533"><a name="p569067079093533"></a><a name="p569067079093533"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1421845533093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1664083095093533"><a name="p1664083095093533"></a><a name="p1664083095093533"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1955754384093533"><a name="p1955754384093533"></a><a name="p1955754384093533"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

