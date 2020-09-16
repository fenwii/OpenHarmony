# OHOS::UIAbstractScroll<a name="EN-US_TOPIC_0000001054598181"></a>

## **Overview**<a name="section2075932052093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines the attributes of a scroll, including the scroll direction, blank size of a scroll view, velocity and effects of a scroll animation. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1608678257093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1259283925093533"></a>
<table><thead align="left"><tr id="row1695334249093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1209581026093533"><a name="p1209581026093533"></a><a name="p1209581026093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1796602245093533"><a name="p1796602245093533"></a><a name="p1796602245093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1586368875093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p26408442093533"><a name="p26408442093533"></a><a name="p26408442093533"></a><a href="graphic.md#ga93a169fba7c98f6534692cba9e8d539b">UIAbstractScroll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1441318986093533"><a name="p1441318986093533"></a><a name="p1441318986093533"></a> </p>
<p id="p1616432490093533"><a name="p1616432490093533"></a><a name="p1616432490093533"></a>A constructor used to create a <strong id="b171176245093533"><a name="b171176245093533"></a><a name="b171176245093533"></a><a href="ohos-uiabstractscroll.md">UIAbstractScroll</a></strong> instance. </p>
</td>
</tr>
<tr id="row1185403416093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1307892418093533"><a name="p1307892418093533"></a><a name="p1307892418093533"></a><a href="graphic.md#ga414798ec7357edc85409128fba0a813c">~UIAbstractScroll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1767162680093533"><a name="p1767162680093533"></a><a name="p1767162680093533"></a>virtual </p>
<p id="p1352461904093533"><a name="p1352461904093533"></a><a name="p1352461904093533"></a>A destructor used to delete the <strong id="b1752271983093533"><a name="b1752271983093533"></a><a name="b1752271983093533"></a><a href="ohos-uiabstractscroll.md">UIAbstractScroll</a></strong> instance. </p>
</td>
</tr>
<tr id="row996629730093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1075118844093533"><a name="p1075118844093533"></a><a name="p1075118844093533"></a><a href="graphic.md#gaeb9e84901b38ef75fa650fc5a27ffc65">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1720161008093533"><a name="p1720161008093533"></a><a name="p1720161008093533"></a>UIViewType </p>
<p id="p1964057873093533"><a name="p1964057873093533"></a><a name="p1964057873093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1237649909093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p274820966093533"><a name="p274820966093533"></a><a name="p274820966093533"></a><a href="graphic.md#ga443783170697bea9a933843ad2a92283">GetDirection</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1170014928093533"><a name="p1170014928093533"></a><a name="p1170014928093533"></a>uint8_t </p>
<p id="p1717281353093533"><a name="p1717281353093533"></a><a name="p1717281353093533"></a>Obtains the scroll direction. </p>
</td>
</tr>
<tr id="row1315298886093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1489872994093533"><a name="p1489872994093533"></a><a name="p1489872994093533"></a><a href="graphic.md#gab37cea97d63ee9ca609c9a1ed0f1e281">SetScrollBlankSize</a> (uint16_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p129875114093533"><a name="p129875114093533"></a><a name="p129875114093533"></a>void </p>
<p id="p1369309869093533"><a name="p1369309869093533"></a><a name="p1369309869093533"></a>Sets the blank size for this scroll view. </p>
</td>
</tr>
<tr id="row924161856093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1744837498093533"><a name="p1744837498093533"></a><a name="p1744837498093533"></a><a href="graphic.md#gae2d6f5c97a316ecd3b41fecfa35a351f">SetMaxScrollDistance</a> (uint16_t distance)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1542607585093533"><a name="p1542607585093533"></a><a name="p1542607585093533"></a>void </p>
<p id="p96382912093533"><a name="p96382912093533"></a><a name="p96382912093533"></a>Sets the maximum scroll distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1645085939093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p633044138093533"><a name="p633044138093533"></a><a name="p633044138093533"></a><a href="graphic.md#ga5d7fefcd2057e868a8f6c6a6000aa7ef">SetReboundSize</a> (uint16_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995780650093533"><a name="p1995780650093533"></a><a name="p1995780650093533"></a>void </p>
<p id="p270392404093533"><a name="p270392404093533"></a><a name="p270392404093533"></a>Sets the rebound size, which is the distance a knob moves after being released when it reaches the end of a scrollbar. </p>
</td>
</tr>
<tr id="row330732575093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2124982392093533"><a name="p2124982392093533"></a><a name="p2124982392093533"></a><a href="graphic.md#ga71a2b17d4145479ed2e2ca000eb7e86e">GetMaxScrollDistance</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p262254566093533"><a name="p262254566093533"></a><a name="p262254566093533"></a>uint16_t </p>
<p id="p368729132093533"><a name="p368729132093533"></a><a name="p368729132093533"></a>Obtains the maximum scroll distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row436969701093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2091819703093533"><a name="p2091819703093533"></a><a name="p2091819703093533"></a><a href="graphic.md#ga957ec65a7efad6818be6df5169158aad">SetDragFunc</a> (EasingFunc func)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p811540224093533"><a name="p811540224093533"></a><a name="p811540224093533"></a>void </p>
<p id="p1175067399093533"><a name="p1175067399093533"></a><a name="p1175067399093533"></a>Sets the easing function that specifies a scroll animation after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1974443221093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1136524101093533"><a name="p1136524101093533"></a><a name="p1136524101093533"></a><a href="graphic.md#ga4dde5f89d70304e77a96d4f4679438c2">SetThrowDrag</a> (bool throwDrag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1821989755093533"><a name="p1821989755093533"></a><a name="p1821989755093533"></a>void </p>
<p id="p1702714177093533"><a name="p1702714177093533"></a><a name="p1702714177093533"></a>Sets whether to continue scrolling after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row452493505093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p361537102093533"><a name="p361537102093533"></a><a name="p361537102093533"></a><a href="graphic.md#ga5013215d3075616ae081849ef52bb57a">MoveChildByOffset</a> (int16_t offsetX, int16_t offsetY) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1341541254093533"><a name="p1341541254093533"></a><a name="p1341541254093533"></a>void </p>
<p id="p1485352165093533"><a name="p1485352165093533"></a><a name="p1485352165093533"></a>Moves the position of all child views. </p>
</td>
</tr>
<tr id="row1887009420093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1173684425093533"><a name="p1173684425093533"></a><a name="p1173684425093533"></a><a href="graphic.md#gad344babd5b251ed908cdf628fae55093">SetDragACCLevel</a> (uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514510060093533"><a name="p514510060093533"></a><a name="p514510060093533"></a>void </p>
<p id="p1958165183093533"><a name="p1958165183093533"></a><a name="p1958165183093533"></a>Sets the drag acceleration. </p>
</td>
</tr>
<tr id="row1447022261093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p879347623093533"><a name="p879347623093533"></a><a name="p879347623093533"></a><a href="graphic.md#ga29e68195b56783f265d85506f130c664">GetDragACCLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1367379022093533"><a name="p1367379022093533"></a><a name="p1367379022093533"></a>uint8_t </p>
<p id="p1153528571093533"><a name="p1153528571093533"></a><a name="p1153528571093533"></a>Obtains the drag acceleration. </p>
</td>
</tr>
<tr id="row74266303093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1928633365093533"><a name="p1928633365093533"></a><a name="p1928633365093533"></a><a href="graphic.md#gafab9d1a8f5987b50f9111c733ada6341">SetSwipeACCLevel</a> (uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p320914635093533"><a name="p320914635093533"></a><a name="p320914635093533"></a>void </p>
<p id="p1646324369093533"><a name="p1646324369093533"></a><a name="p1646324369093533"></a>Sets the compensation distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row144958638093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1563453313093533"><a name="p1563453313093533"></a><a name="p1563453313093533"></a><a href="graphic.md#ga25dad3242949f0fbeff47d6df06053f6">GetSwipeACCLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1536928663093533"><a name="p1536928663093533"></a><a name="p1536928663093533"></a>uint8_t </p>
<p id="p1727159999093533"><a name="p1727159999093533"></a><a name="p1727159999093533"></a>Obtains the compensation distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1844201731093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1825426577093533"><a name="p1825426577093533"></a><a name="p1825426577093533"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1628880389093533"><a name="p1628880389093533"></a><a name="p1628880389093533"></a> </p>
<p id="p5654744093533"><a name="p5654744093533"></a><a name="p5654744093533"></a>A default constructor used to create a <strong id="b1415466495093533"><a name="b1415466495093533"></a><a name="b1415466495093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row653771506093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14863844093533"><a name="p14863844093533"></a><a name="p14863844093533"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1413656742093533"><a name="p1413656742093533"></a><a name="p1413656742093533"></a>virtual </p>
<p id="p1317316189093533"><a name="p1317316189093533"></a><a name="p1317316189093533"></a>A destructor used to delete the <strong id="b673614693093533"><a name="b673614693093533"></a><a name="b673614693093533"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row1573148150093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494763781093533"><a name="p1494763781093533"></a><a name="p1494763781093533"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p68994433093533"><a name="p68994433093533"></a><a name="p68994433093533"></a>UIViewType </p>
<p id="p750747682093533"><a name="p750747682093533"></a><a name="p750747682093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row158628034093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p431731436093533"><a name="p431731436093533"></a><a name="p431731436093533"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p572157784093533"><a name="p572157784093533"></a><a name="p572157784093533"></a>virtual void </p>
<p id="p1482038324093533"><a name="p1482038324093533"></a><a name="p1482038324093533"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row825724924093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p962138697093533"><a name="p962138697093533"></a><a name="p962138697093533"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p650455031093533"><a name="p650455031093533"></a><a name="p650455031093533"></a>virtual void </p>
<p id="p2066956881093533"><a name="p2066956881093533"></a><a name="p2066956881093533"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1151311552093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1181403221093533"><a name="p1181403221093533"></a><a name="p1181403221093533"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1639919377093533"><a name="p1639919377093533"></a><a name="p1639919377093533"></a>virtual void </p>
<p id="p1964603891093533"><a name="p1964603891093533"></a><a name="p1964603891093533"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row1418178694093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1490576733093533"><a name="p1490576733093533"></a><a name="p1490576733093533"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p697942019093533"><a name="p697942019093533"></a><a name="p697942019093533"></a>virtual void </p>
<p id="p1341149296093533"><a name="p1341149296093533"></a><a name="p1341149296093533"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1310683290093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p845055466093533"><a name="p845055466093533"></a><a name="p845055466093533"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137361476093533"><a name="p2137361476093533"></a><a name="p2137361476093533"></a>virtual void </p>
<p id="p427959371093533"><a name="p427959371093533"></a><a name="p427959371093533"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1190639114093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1300647832093533"><a name="p1300647832093533"></a><a name="p1300647832093533"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p606974357093533"><a name="p606974357093533"></a><a name="p606974357093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1994048436093533"><a name="p1994048436093533"></a><a name="p1994048436093533"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row121714412093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p199122806093533"><a name="p199122806093533"></a><a name="p199122806093533"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2096063884093533"><a name="p2096063884093533"></a><a name="p2096063884093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1388143705093533"><a name="p1388143705093533"></a><a name="p1388143705093533"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row797591502093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p244223248093533"><a name="p244223248093533"></a><a name="p244223248093533"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226794473093533"><a name="p1226794473093533"></a><a name="p1226794473093533"></a>void </p>
<p id="p1833940969093533"><a name="p1833940969093533"></a><a name="p1833940969093533"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row2106309023093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1971621256093533"><a name="p1971621256093533"></a><a name="p1971621256093533"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p608107502093533"><a name="p608107502093533"></a><a name="p608107502093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p351911240093533"><a name="p351911240093533"></a><a name="p351911240093533"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row818278800093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1881396795093533"><a name="p1881396795093533"></a><a name="p1881396795093533"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p813004763093533"><a name="p813004763093533"></a><a name="p813004763093533"></a>void </p>
<p id="p1903802709093533"><a name="p1903802709093533"></a><a name="p1903802709093533"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row345873136093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1448789132093533"><a name="p1448789132093533"></a><a name="p1448789132093533"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1588100645093533"><a name="p1588100645093533"></a><a name="p1588100645093533"></a> </p>
<p id="p1488970745093533"><a name="p1488970745093533"></a><a name="p1488970745093533"></a>A default constructor used to create an <strong id="b250863596093533"><a name="b250863596093533"></a><a name="b250863596093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row2040440073093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1648297086093533"><a name="p1648297086093533"></a><a name="p1648297086093533"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p471031049093533"><a name="p471031049093533"></a><a name="p471031049093533"></a> </p>
<p id="p697757619093533"><a name="p697757619093533"></a><a name="p697757619093533"></a>A constructor used to create an <strong id="b174887936093533"><a name="b174887936093533"></a><a name="b174887936093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row43821662093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p810053905093533"><a name="p810053905093533"></a><a name="p810053905093533"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1785061713093533"><a name="p1785061713093533"></a><a name="p1785061713093533"></a>virtual </p>
<p id="p1378255735093533"><a name="p1378255735093533"></a><a name="p1378255735093533"></a>A destructor used to delete the <strong id="b2021134493093533"><a name="b2021134493093533"></a><a name="b2021134493093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row50505032093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1034238095093533"><a name="p1034238095093533"></a><a name="p1034238095093533"></a><a href="graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p55926029093533"><a name="p55926029093533"></a><a name="p55926029093533"></a>virtual bool </p>
<p id="p1471564341093533"><a name="p1471564341093533"></a><a name="p1471564341093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1702214437093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p981364715093533"><a name="p981364715093533"></a><a name="p981364715093533"></a><a href="graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1756810225093533"><a name="p1756810225093533"></a><a name="p1756810225093533"></a>virtual void </p>
<p id="p1796657708093533"><a name="p1796657708093533"></a><a name="p1796657708093533"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1190625724093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1043252476093533"><a name="p1043252476093533"></a><a name="p1043252476093533"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p203028221093533"><a name="p203028221093533"></a><a name="p203028221093533"></a>virtual void </p>
<p id="p2076855023093533"><a name="p2076855023093533"></a><a name="p2076855023093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row495204124093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1574084402093533"><a name="p1574084402093533"></a><a name="p1574084402093533"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1950130111093533"><a name="p1950130111093533"></a><a name="p1950130111093533"></a>virtual void </p>
<p id="p885390787093533"><a name="p885390787093533"></a><a name="p885390787093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row204210951093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1467417005093533"><a name="p1467417005093533"></a><a name="p1467417005093533"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p976277782093533"><a name="p976277782093533"></a><a name="p976277782093533"></a>void </p>
<p id="p1710100722093533"><a name="p1710100722093533"></a><a name="p1710100722093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row14331455093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p956822300093533"><a name="p956822300093533"></a><a name="p956822300093533"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1207632010093533"><a name="p1207632010093533"></a><a name="p1207632010093533"></a>void </p>
<p id="p1638692306093533"><a name="p1638692306093533"></a><a name="p1638692306093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row615228498093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1487280426093533"><a name="p1487280426093533"></a><a name="p1487280426093533"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1209365609093533"><a name="p1209365609093533"></a><a name="p1209365609093533"></a>virtual bool </p>
<p id="p1285687287093533"><a name="p1285687287093533"></a><a name="p1285687287093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1294209746093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1743828911093533"><a name="p1743828911093533"></a><a name="p1743828911093533"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695036990093533"><a name="p1695036990093533"></a><a name="p1695036990093533"></a>virtual bool </p>
<p id="p598138883093533"><a name="p598138883093533"></a><a name="p598138883093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row511442680093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1634889423093533"><a name="p1634889423093533"></a><a name="p1634889423093533"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1054545741093533"><a name="p1054545741093533"></a><a name="p1054545741093533"></a>virtual bool </p>
<p id="p1220151920093533"><a name="p1220151920093533"></a><a name="p1220151920093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1519555745093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1100396440093533"><a name="p1100396440093533"></a><a name="p1100396440093533"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2027941687093533"><a name="p2027941687093533"></a><a name="p2027941687093533"></a>virtual bool </p>
<p id="p1206400362093533"><a name="p1206400362093533"></a><a name="p1206400362093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row583183546093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p189998872093533"><a name="p189998872093533"></a><a name="p189998872093533"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1487779236093533"><a name="p1487779236093533"></a><a name="p1487779236093533"></a>virtual void </p>
<p id="p1801170107093533"><a name="p1801170107093533"></a><a name="p1801170107093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row1911375126093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1908629855093533"><a name="p1908629855093533"></a><a name="p1908629855093533"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p163464278093533"><a name="p163464278093533"></a><a name="p163464278093533"></a>virtual void </p>
<p id="p749956121093533"><a name="p749956121093533"></a><a name="p749956121093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row289028324093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1283591203093533"><a name="p1283591203093533"></a><a name="p1283591203093533"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p510719416093533"><a name="p510719416093533"></a><a name="p510719416093533"></a>virtual void </p>
<p id="p2072827809093533"><a name="p2072827809093533"></a><a name="p2072827809093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row659282936093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p760970113093533"><a name="p760970113093533"></a><a name="p760970113093533"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2010602809093533"><a name="p2010602809093533"></a><a name="p2010602809093533"></a>virtual void </p>
<p id="p1863857745093533"><a name="p1863857745093533"></a><a name="p1863857745093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row2078952051093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2097332908093533"><a name="p2097332908093533"></a><a name="p2097332908093533"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p122026914093533"><a name="p122026914093533"></a><a name="p122026914093533"></a>void </p>
<p id="p1811241286093533"><a name="p1811241286093533"></a><a name="p1811241286093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1255820194093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1453742813093533"><a name="p1453742813093533"></a><a name="p1453742813093533"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073866251093533"><a name="p2073866251093533"></a><a name="p2073866251093533"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p653336792093533"><a name="p653336792093533"></a><a name="p653336792093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row800563702093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p817439211093533"><a name="p817439211093533"></a><a name="p817439211093533"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1791323621093533"><a name="p1791323621093533"></a><a name="p1791323621093533"></a>void </p>
<p id="p2044781320093533"><a name="p2044781320093533"></a><a name="p2044781320093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row92071283093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p723896088093533"><a name="p723896088093533"></a><a name="p723896088093533"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1278150696093533"><a name="p1278150696093533"></a><a name="p1278150696093533"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p1055456100093533"><a name="p1055456100093533"></a><a name="p1055456100093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1536417931093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1929810700093533"><a name="p1929810700093533"></a><a name="p1929810700093533"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p991082486093533"><a name="p991082486093533"></a><a name="p991082486093533"></a>void </p>
<p id="p125925186093533"><a name="p125925186093533"></a><a name="p125925186093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1411650568093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p700666545093533"><a name="p700666545093533"></a><a name="p700666545093533"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p932007657093533"><a name="p932007657093533"></a><a name="p932007657093533"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p776613830093533"><a name="p776613830093533"></a><a name="p776613830093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1286162933093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1768669866093533"><a name="p1768669866093533"></a><a name="p1768669866093533"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p838866623093533"><a name="p838866623093533"></a><a name="p838866623093533"></a>void </p>
<p id="p327374578093533"><a name="p327374578093533"></a><a name="p327374578093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1769250558093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1701111775093533"><a name="p1701111775093533"></a><a name="p1701111775093533"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p246316122093533"><a name="p246316122093533"></a><a name="p246316122093533"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1910672323093533"><a name="p1910672323093533"></a><a name="p1910672323093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row51863377093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p532739258093533"><a name="p532739258093533"></a><a name="p532739258093533"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p972389945093533"><a name="p972389945093533"></a><a name="p972389945093533"></a>void </p>
<p id="p117257626093533"><a name="p117257626093533"></a><a name="p117257626093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1642839244093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1714491266093533"><a name="p1714491266093533"></a><a name="p1714491266093533"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p369816710093533"><a name="p369816710093533"></a><a name="p369816710093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1552309988093533"><a name="p1552309988093533"></a><a name="p1552309988093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1998449960093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292359254093533"><a name="p1292359254093533"></a><a name="p1292359254093533"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p157777413093533"><a name="p157777413093533"></a><a name="p157777413093533"></a>void </p>
<p id="p1508601400093533"><a name="p1508601400093533"></a><a name="p1508601400093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1221005692093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p682016002093533"><a name="p682016002093533"></a><a name="p682016002093533"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p671579454093533"><a name="p671579454093533"></a><a name="p671579454093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1935721500093533"><a name="p1935721500093533"></a><a name="p1935721500093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1402604131093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p727872661093533"><a name="p727872661093533"></a><a name="p727872661093533"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1724507778093533"><a name="p1724507778093533"></a><a name="p1724507778093533"></a>virtual void </p>
<p id="p1371628482093533"><a name="p1371628482093533"></a><a name="p1371628482093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1161361588093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p924860981093533"><a name="p924860981093533"></a><a name="p924860981093533"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601648147093533"><a name="p1601648147093533"></a><a name="p1601648147093533"></a>bool </p>
<p id="p1803127211093533"><a name="p1803127211093533"></a><a name="p1803127211093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1136112146093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1239016658093533"><a name="p1239016658093533"></a><a name="p1239016658093533"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1743402715093533"><a name="p1743402715093533"></a><a name="p1743402715093533"></a>void </p>
<p id="p1689590372093533"><a name="p1689590372093533"></a><a name="p1689590372093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1444010309093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1290144859093533"><a name="p1290144859093533"></a><a name="p1290144859093533"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p681440874093533"><a name="p681440874093533"></a><a name="p681440874093533"></a>bool </p>
<p id="p971775138093533"><a name="p971775138093533"></a><a name="p971775138093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row156125423093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1728231453093533"><a name="p1728231453093533"></a><a name="p1728231453093533"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2001036484093533"><a name="p2001036484093533"></a><a name="p2001036484093533"></a>void </p>
<p id="p266592530093533"><a name="p266592530093533"></a><a name="p266592530093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1965028716093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p642135180093533"><a name="p642135180093533"></a><a name="p642135180093533"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2131784489093533"><a name="p2131784489093533"></a><a name="p2131784489093533"></a>bool </p>
<p id="p410363045093533"><a name="p410363045093533"></a><a name="p410363045093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1921822438093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p938664276093533"><a name="p938664276093533"></a><a name="p938664276093533"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p699922275093533"><a name="p699922275093533"></a><a name="p699922275093533"></a>void </p>
<p id="p1063104763093533"><a name="p1063104763093533"></a><a name="p1063104763093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row2049268784093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p508985075093533"><a name="p508985075093533"></a><a name="p508985075093533"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p173690437093533"><a name="p173690437093533"></a><a name="p173690437093533"></a>bool </p>
<p id="p1808307242093533"><a name="p1808307242093533"></a><a name="p1808307242093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row804782534093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p241845852093533"><a name="p241845852093533"></a><a name="p241845852093533"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p150659128093533"><a name="p150659128093533"></a><a name="p150659128093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1263953040093533"><a name="p1263953040093533"></a><a name="p1263953040093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row501309347093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1693503103093533"><a name="p1693503103093533"></a><a name="p1693503103093533"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1786512909093533"><a name="p1786512909093533"></a><a name="p1786512909093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p759827124093533"><a name="p759827124093533"></a><a name="p759827124093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row199152326093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p815242935093533"><a name="p815242935093533"></a><a name="p815242935093533"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1672690438093533"><a name="p1672690438093533"></a><a name="p1672690438093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1948051976093533"><a name="p1948051976093533"></a><a name="p1948051976093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1840447241093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p475852162093533"><a name="p475852162093533"></a><a name="p475852162093533"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p65376851093533"><a name="p65376851093533"></a><a name="p65376851093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p398160938093533"><a name="p398160938093533"></a><a name="p398160938093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1134496199093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p804902342093533"><a name="p804902342093533"></a><a name="p804902342093533"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1474432275093533"><a name="p1474432275093533"></a><a name="p1474432275093533"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1317353856093533"><a name="p1317353856093533"></a><a name="p1317353856093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row453501154093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1609688923093533"><a name="p1609688923093533"></a><a name="p1609688923093533"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p279623657093533"><a name="p279623657093533"></a><a name="p279623657093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p425169130093533"><a name="p425169130093533"></a><a name="p425169130093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1703987732093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p655280942093533"><a name="p655280942093533"></a><a name="p655280942093533"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1630833555093533"><a name="p1630833555093533"></a><a name="p1630833555093533"></a>void </p>
<p id="p1409990749093533"><a name="p1409990749093533"></a><a name="p1409990749093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row819008453093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p7709290093533"><a name="p7709290093533"></a><a name="p7709290093533"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p755107996093533"><a name="p755107996093533"></a><a name="p755107996093533"></a>virtual void </p>
<p id="p1210087247093533"><a name="p1210087247093533"></a><a name="p1210087247093533"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row855093056093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p385336891093533"><a name="p385336891093533"></a><a name="p385336891093533"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1597885550093533"><a name="p1597885550093533"></a><a name="p1597885550093533"></a>virtual int16_t </p>
<p id="p1322688226093533"><a name="p1322688226093533"></a><a name="p1322688226093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1074059031093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p247049802093533"><a name="p247049802093533"></a><a name="p247049802093533"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1856299907093533"><a name="p1856299907093533"></a><a name="p1856299907093533"></a>virtual void </p>
<p id="p1420215518093533"><a name="p1420215518093533"></a><a name="p1420215518093533"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row472499915093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1910885641093533"><a name="p1910885641093533"></a><a name="p1910885641093533"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p13277110093533"><a name="p13277110093533"></a><a name="p13277110093533"></a>virtual int16_t </p>
<p id="p897395790093533"><a name="p897395790093533"></a><a name="p897395790093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1623264975093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1293981348093533"><a name="p1293981348093533"></a><a name="p1293981348093533"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1035158693093533"><a name="p1035158693093533"></a><a name="p1035158693093533"></a>virtual void </p>
<p id="p808260290093533"><a name="p808260290093533"></a><a name="p808260290093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1552940190093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p623471354093533"><a name="p623471354093533"></a><a name="p623471354093533"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1255715342093533"><a name="p1255715342093533"></a><a name="p1255715342093533"></a>virtual void </p>
<p id="p1308802028093533"><a name="p1308802028093533"></a><a name="p1308802028093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1334403873093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p696988198093533"><a name="p696988198093533"></a><a name="p696988198093533"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p108289068093533"><a name="p108289068093533"></a><a name="p108289068093533"></a>int16_t </p>
<p id="p1044216157093533"><a name="p1044216157093533"></a><a name="p1044216157093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1443839845093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1888728531093533"><a name="p1888728531093533"></a><a name="p1888728531093533"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p996878703093533"><a name="p996878703093533"></a><a name="p996878703093533"></a>virtual void </p>
<p id="p672880762093533"><a name="p672880762093533"></a><a name="p672880762093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1619702401093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2110341473093533"><a name="p2110341473093533"></a><a name="p2110341473093533"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1175835485093533"><a name="p1175835485093533"></a><a name="p1175835485093533"></a>int16_t </p>
<p id="p1837443522093533"><a name="p1837443522093533"></a><a name="p1837443522093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row929267792093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1911372885093533"><a name="p1911372885093533"></a><a name="p1911372885093533"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1520488191093533"><a name="p1520488191093533"></a><a name="p1520488191093533"></a>virtual void </p>
<p id="p1996436619093533"><a name="p1996436619093533"></a><a name="p1996436619093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row526617597093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1739150980093533"><a name="p1739150980093533"></a><a name="p1739150980093533"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p901362903093533"><a name="p901362903093533"></a><a name="p901362903093533"></a>virtual void </p>
<p id="p1589423112093533"><a name="p1589423112093533"></a><a name="p1589423112093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1700625068093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p246751142093533"><a name="p246751142093533"></a><a name="p246751142093533"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p820741499093533"><a name="p820741499093533"></a><a name="p820741499093533"></a>bool </p>
<p id="p1540865925093533"><a name="p1540865925093533"></a><a name="p1540865925093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1332633037093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p538633009093533"><a name="p538633009093533"></a><a name="p538633009093533"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2028596664093533"><a name="p2028596664093533"></a><a name="p2028596664093533"></a>void </p>
<p id="p666230151093533"><a name="p666230151093533"></a><a name="p666230151093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row273043042093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1895048558093533"><a name="p1895048558093533"></a><a name="p1895048558093533"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038340395093533"><a name="p1038340395093533"></a><a name="p1038340395093533"></a>void </p>
<p id="p731505734093533"><a name="p731505734093533"></a><a name="p731505734093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row339326800093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1833266969093533"><a name="p1833266969093533"></a><a name="p1833266969093533"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1194722204093533"><a name="p1194722204093533"></a><a name="p1194722204093533"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p1000815478093533"><a name="p1000815478093533"></a><a name="p1000815478093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row572568291093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p682916172093533"><a name="p682916172093533"></a><a name="p682916172093533"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2049109490093533"><a name="p2049109490093533"></a><a name="p2049109490093533"></a>void </p>
<p id="p1521651343093533"><a name="p1521651343093533"></a><a name="p1521651343093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row894440777093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1531974991093533"><a name="p1531974991093533"></a><a name="p1531974991093533"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1158881623093533"><a name="p1158881623093533"></a><a name="p1158881623093533"></a>const char * </p>
<p id="p345999167093533"><a name="p345999167093533"></a><a name="p345999167093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row2063960781093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p128036160093533"><a name="p128036160093533"></a><a name="p128036160093533"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p436990856093533"><a name="p436990856093533"></a><a name="p436990856093533"></a>void </p>
<p id="p1654288603093533"><a name="p1654288603093533"></a><a name="p1654288603093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1672064347093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p899027730093533"><a name="p899027730093533"></a><a name="p899027730093533"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p621851780093533"><a name="p621851780093533"></a><a name="p621851780093533"></a>int16_t </p>
<p id="p277220128093533"><a name="p277220128093533"></a><a name="p277220128093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row117692286093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1379946357093533"><a name="p1379946357093533"></a><a name="p1379946357093533"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1575631467093533"><a name="p1575631467093533"></a><a name="p1575631467093533"></a>virtual void </p>
<p id="p431144556093533"><a name="p431144556093533"></a><a name="p431144556093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row451804624093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p676840801093533"><a name="p676840801093533"></a><a name="p676840801093533"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1904186264093533"><a name="p1904186264093533"></a><a name="p1904186264093533"></a>void </p>
<p id="p1993930671093533"><a name="p1993930671093533"></a><a name="p1993930671093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1727170982093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2025341262093533"><a name="p2025341262093533"></a><a name="p2025341262093533"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p295759407093533"><a name="p295759407093533"></a><a name="p295759407093533"></a>void </p>
<p id="p736841895093533"><a name="p736841895093533"></a><a name="p736841895093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1678378895093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2033042380093533"><a name="p2033042380093533"></a><a name="p2033042380093533"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1672514902093533"><a name="p1672514902093533"></a><a name="p1672514902093533"></a>void </p>
<p id="p518488217093533"><a name="p518488217093533"></a><a name="p518488217093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row784983530093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p777485810093533"><a name="p777485810093533"></a><a name="p777485810093533"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1943424169093533"><a name="p1943424169093533"></a><a name="p1943424169093533"></a>void </p>
<p id="p1114889274093533"><a name="p1114889274093533"></a><a name="p1114889274093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1824108037093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p262678162093533"><a name="p262678162093533"></a><a name="p262678162093533"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1025597282093533"><a name="p1025597282093533"></a><a name="p1025597282093533"></a>void </p>
<p id="p1806423892093533"><a name="p1806423892093533"></a><a name="p1806423892093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row2027658237093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1612664384093533"><a name="p1612664384093533"></a><a name="p1612664384093533"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1229247990093533"><a name="p1229247990093533"></a><a name="p1229247990093533"></a>void </p>
<p id="p1277259238093533"><a name="p1277259238093533"></a><a name="p1277259238093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1178768975093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1678806942093533"><a name="p1678806942093533"></a><a name="p1678806942093533"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1566431956093533"><a name="p1566431956093533"></a><a name="p1566431956093533"></a>void </p>
<p id="p361877309093533"><a name="p361877309093533"></a><a name="p361877309093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1371108459093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1003808196093533"><a name="p1003808196093533"></a><a name="p1003808196093533"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p666100208093533"><a name="p666100208093533"></a><a name="p666100208093533"></a>void </p>
<p id="p2073130766093533"><a name="p2073130766093533"></a><a name="p2073130766093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1153705283093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1279170774093533"><a name="p1279170774093533"></a><a name="p1279170774093533"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p638576239093533"><a name="p638576239093533"></a><a name="p638576239093533"></a>void </p>
<p id="p1097945004093533"><a name="p1097945004093533"></a><a name="p1097945004093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row927688135093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p151802800093533"><a name="p151802800093533"></a><a name="p151802800093533"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901461180093533"><a name="p1901461180093533"></a><a name="p1901461180093533"></a>void </p>
<p id="p1630258409093533"><a name="p1630258409093533"></a><a name="p1630258409093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1304227200093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1811619842093533"><a name="p1811619842093533"></a><a name="p1811619842093533"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p442566569093533"><a name="p442566569093533"></a><a name="p442566569093533"></a>void </p>
<p id="p2111915372093533"><a name="p2111915372093533"></a><a name="p2111915372093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1996261122093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1670294962093533"><a name="p1670294962093533"></a><a name="p1670294962093533"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1890654027093533"><a name="p1890654027093533"></a><a name="p1890654027093533"></a>void </p>
<p id="p179478390093533"><a name="p179478390093533"></a><a name="p179478390093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row2033119249093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p19647760093533"><a name="p19647760093533"></a><a name="p19647760093533"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1961331232093533"><a name="p1961331232093533"></a><a name="p1961331232093533"></a>void </p>
<p id="p397271410093533"><a name="p397271410093533"></a><a name="p397271410093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row956575334093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p425470443093533"><a name="p425470443093533"></a><a name="p425470443093533"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p323121171093533"><a name="p323121171093533"></a><a name="p323121171093533"></a>void </p>
<p id="p1951690965093533"><a name="p1951690965093533"></a><a name="p1951690965093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1857129450093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p979190221093533"><a name="p979190221093533"></a><a name="p979190221093533"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1164362654093533"><a name="p1164362654093533"></a><a name="p1164362654093533"></a>void </p>
<p id="p1235909034093533"><a name="p1235909034093533"></a><a name="p1235909034093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1871569137093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1482438942093533"><a name="p1482438942093533"></a><a name="p1482438942093533"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p52092998093533"><a name="p52092998093533"></a><a name="p52092998093533"></a>virtual void </p>
<p id="p763196751093533"><a name="p763196751093533"></a><a name="p763196751093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row2058439804093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p537656029093533"><a name="p537656029093533"></a><a name="p537656029093533"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1365123932093533"><a name="p1365123932093533"></a><a name="p1365123932093533"></a>virtual void </p>
<p id="p468315566093533"><a name="p468315566093533"></a><a name="p468315566093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1884504591093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589922185093533"><a name="p589922185093533"></a><a name="p589922185093533"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1556097211093533"><a name="p1556097211093533"></a><a name="p1556097211093533"></a>virtual int64_t </p>
<p id="p1538994807093533"><a name="p1538994807093533"></a><a name="p1538994807093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row142583204093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1111925823093533"><a name="p1111925823093533"></a><a name="p1111925823093533"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1690038678093533"><a name="p1690038678093533"></a><a name="p1690038678093533"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p459072922093533"><a name="p459072922093533"></a><a name="p459072922093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row27377128093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1364909660093533"><a name="p1364909660093533"></a><a name="p1364909660093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p16301714093533"><a name="p16301714093533"></a><a name="p16301714093533"></a>void * </p>
<p id="p1990938915093533"><a name="p1990938915093533"></a><a name="p1990938915093533"></a>Overrides the <strong id="b892999416093533"><a name="b892999416093533"></a><a name="b892999416093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1912214248093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1162243943093533"><a name="p1162243943093533"></a><a name="p1162243943093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p885739757093533"><a name="p885739757093533"></a><a name="p885739757093533"></a>void </p>
<p id="p1808199910093533"><a name="p1808199910093533"></a><a name="p1808199910093533"></a>Overrides the <strong id="b423842751093533"><a name="b423842751093533"></a><a name="b423842751093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1842211191093533"></a>
<table><thead align="left"><tr id="row1110075929093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2083072496093533"><a name="p2083072496093533"></a><a name="p2083072496093533"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1815692257093533"><a name="p1815692257093533"></a><a name="p1815692257093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row376570209093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1025303133093533"><a name="p1025303133093533"></a><a name="p1025303133093533"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1326105426093533"><a name="p1326105426093533"></a><a name="p1326105426093533"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1724388826093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p263034394093533"><a name="p263034394093533"></a><a name="p263034394093533"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p837601996093533"><a name="p837601996093533"></a><a name="p837601996093533"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row1347515245093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806283664093533"><a name="p1806283664093533"></a><a name="p1806283664093533"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1193724419093533"><a name="p1193724419093533"></a><a name="p1193724419093533"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row315281535093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p741583911093533"><a name="p741583911093533"></a><a name="p741583911093533"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p211821185093533"><a name="p211821185093533"></a><a name="p211821185093533"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row596442557093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p214436720093533"><a name="p214436720093533"></a><a name="p214436720093533"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p709157381093533"><a name="p709157381093533"></a><a name="p709157381093533"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1157897237093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1909334363093533"><a name="p1909334363093533"></a><a name="p1909334363093533"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p539369123093533"><a name="p539369123093533"></a><a name="p539369123093533"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1330209539093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1851893193093533"><a name="p1851893193093533"></a><a name="p1851893193093533"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p738346591093533"><a name="p738346591093533"></a><a name="p738346591093533"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row17812795093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p133929798093533"><a name="p133929798093533"></a><a name="p133929798093533"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p194773919093533"><a name="p194773919093533"></a><a name="p194773919093533"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

