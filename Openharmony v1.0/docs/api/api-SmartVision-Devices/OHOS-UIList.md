# OHOS::UIList<a name="ZH-CN_TOPIC_0000001054799625"></a>

## **Overview**<a name="section640973495093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents a scrollable list which is used with the adapter  [AbstractAdapter](OHOS-AbstractAdapter.md)  to implement scrolling, inertial scrolling, automatic alignment, and invoking of a callback when a child view is selected at the preset position as this list scrolls. 

You need to override  [AbstractAdapter](OHOS-AbstractAdapter.md)  to implement functions for setting and saving data, obtaining data quantity, and creating child views.  **[UIList](OHOS-UIList.md)**  is used when there is a large number of child views with a fixed format. This list automatically reclaims the child views removed out of the current view as it scrolls so that as many as child views can be displayed with a lower memory consumption.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1642728694093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table630305156093534"></a>
<table><thead align="left"><tr id="row322706118093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p569232451093534"><a name="p569232451093534"></a><a name="p569232451093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1790266459093534"><a name="p1790266459093534"></a><a name="p1790266459093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row417710421093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1432285640093534"><a name="p1432285640093534"></a><a name="p1432285640093534"></a><a href="Graphic.md#ga56c15f8c21c433c8a08a151e33b521cf">UIList</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1800157446093534"><a name="p1800157446093534"></a><a name="p1800157446093534"></a>&nbsp;</p>
<p id="p902041531093534"><a name="p902041531093534"></a><a name="p902041531093534"></a>A constructor used to create a <strong id="b854691979093534"><a name="b854691979093534"></a><a name="b854691979093534"></a><a href="OHOS-UIList.md">UIList</a></strong> instance in the vertical direction. </p>
</td>
</tr>
<tr id="row1632755667093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p401785224093534"><a name="p401785224093534"></a><a name="p401785224093534"></a><a href="Graphic.md#ga2da1983fedabd5ea06a8a544aeb2cf04">UIList</a> (uint8_t direction)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1643459214093534"><a name="p1643459214093534"></a><a name="p1643459214093534"></a>&nbsp;</p>
<p id="p411681014093534"><a name="p411681014093534"></a><a name="p411681014093534"></a>A constructor used to create a <strong id="b1594258042093534"><a name="b1594258042093534"></a><a name="b1594258042093534"></a><a href="OHOS-UIList.md">UIList</a></strong> instance in the specified direction. </p>
</td>
</tr>
<tr id="row1350108187093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1094934909093534"><a name="p1094934909093534"></a><a name="p1094934909093534"></a><a href="Graphic.md#ga84de0a8214747d118abfd3d1185ffa63">~UIList</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p752043590093534"><a name="p752043590093534"></a><a name="p752043590093534"></a>virtual&nbsp;</p>
<p id="p880083673093534"><a name="p880083673093534"></a><a name="p880083673093534"></a>A destructor used to delete the <strong id="b1505870937093534"><a name="b1505870937093534"></a><a name="b1505870937093534"></a><a href="OHOS-UIList.md">UIList</a></strong> instance. </p>
</td>
</tr>
<tr id="row1001152129093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1524053265093534"><a name="p1524053265093534"></a><a name="p1524053265093534"></a><a href="Graphic.md#ga6e11e5de67f87ed6cf6c44f60b7d4096">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265870745093534"><a name="p265870745093534"></a><a name="p265870745093534"></a>UIViewType&nbsp;</p>
<p id="p507645235093534"><a name="p507645235093534"></a><a name="p507645235093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1125139244093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p562493233093534"><a name="p562493233093534"></a><a name="p562493233093534"></a><a href="Graphic.md#ga7e99d1fb891879195c19c211c6de6600">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p23667520093534"><a name="p23667520093534"></a><a name="p23667520093534"></a>bool&nbsp;</p>
<p id="p1175799184093534"><a name="p1175799184093534"></a><a name="p1175799184093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1947165742093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1666509555093534"><a name="p1666509555093534"></a><a name="p1666509555093534"></a><a href="Graphic.md#ga225e59d60271c9012a017136d2aab0d6">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p51312953093534"><a name="p51312953093534"></a><a name="p51312953093534"></a>bool&nbsp;</p>
<p id="p759924715093534"><a name="p759924715093534"></a><a name="p759924715093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1897468963093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p121624772093534"><a name="p121624772093534"></a><a name="p121624772093534"></a><a href="Graphic.md#gaa6ba86e78d4a12ea47b6aaa8dd88f882">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266958766093534"><a name="p1266958766093534"></a><a name="p1266958766093534"></a>void&nbsp;</p>
<p id="p450660346093534"><a name="p450660346093534"></a><a name="p450660346093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row907080134093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p26055104093534"><a name="p26055104093534"></a><a name="p26055104093534"></a><a href="Graphic.md#gaa44fd515481de0f1de5d20a62be63267">SetAdapter</a> (<a href="OHOS-AbstractAdapter.md">AbstractAdapter</a> *adapter)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p754502935093534"><a name="p754502935093534"></a><a name="p754502935093534"></a>void&nbsp;</p>
<p id="p813082651093534"><a name="p813082651093534"></a><a name="p813082651093534"></a>Sets the adapter for this list. The content of this list is initialized when the adapter is set. </p>
</td>
</tr>
<tr id="row1901788380093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1710189227093534"><a name="p1710189227093534"></a><a name="p1710189227093534"></a><a href="Graphic.md#gafe121e0cc150122486049dcaf83f3c26">MoveChildByOffset</a> (int16_t x, int16_t y) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p735931143093534"><a name="p735931143093534"></a><a name="p735931143093534"></a>virtual void&nbsp;</p>
<p id="p2006439803093534"><a name="p2006439803093534"></a><a name="p2006439803093534"></a>Moves the position of all child views. </p>
</td>
</tr>
<tr id="row1311797875093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p123382110093534"><a name="p123382110093534"></a><a name="p123382110093534"></a><a href="Graphic.md#ga9a760e34ff783d738d414d26af3903e5">ScrollTo</a> (uint16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1991611518093534"><a name="p1991611518093534"></a><a name="p1991611518093534"></a>void&nbsp;</p>
<p id="p1794581003093534"><a name="p1794581003093534"></a><a name="p1794581003093534"></a>Scrolls to change the index of the first row or column of the current view. </p>
</td>
</tr>
<tr id="row621212093093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1288723297093534"><a name="p1288723297093534"></a><a name="p1288723297093534"></a><a href="Graphic.md#gaf97d599fe1147a71e44a5a107edeac77">ScrollBy</a> (int16_t distance)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2036531866093534"><a name="p2036531866093534"></a><a name="p2036531866093534"></a>void&nbsp;</p>
<p id="p1396185023093534"><a name="p1396185023093534"></a><a name="p1396185023093534"></a>Scrolls the content in this list. </p>
</td>
</tr>
<tr id="row1509073271093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1462576932093534"><a name="p1462576932093534"></a><a name="p1462576932093534"></a><a href="Graphic.md#gaa8023e5c4e0688841263d0f576e76218">SetStartIndex</a> (uint16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p780599395093534"><a name="p780599395093534"></a><a name="p780599395093534"></a>void&nbsp;</p>
<p id="p1638364219093534"><a name="p1638364219093534"></a><a name="p1638364219093534"></a>Sets the start index for this list. </p>
</td>
</tr>
<tr id="row1247596645093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1303838407093534"><a name="p1303838407093534"></a><a name="p1303838407093534"></a><a href="Graphic.md#ga0ce3080df2c5226d20d446bc9c28b694">GetStartIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1085750516093534"><a name="p1085750516093534"></a><a name="p1085750516093534"></a>uint16_t&nbsp;</p>
<p id="p1383861710093534"><a name="p1383861710093534"></a><a name="p1383861710093534"></a>Obtains the start index of this list. The default value is <strong id="b304608062093534"><a name="b304608062093534"></a><a name="b304608062093534"></a>0</strong>. </p>
</td>
</tr>
<tr id="row2115959453093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1502508411093534"><a name="p1502508411093534"></a><a name="p1502508411093534"></a><a href="Graphic.md#gaa07b156ab757cd20486ec0bcbf4c17ac">SetLoopState</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p652039428093534"><a name="p652039428093534"></a><a name="p652039428093534"></a>void&nbsp;</p>
<p id="p590694934093534"><a name="p590694934093534"></a><a name="p590694934093534"></a>Sets the loop state for this list, in which a loop scroll is possible since the top and bottom of the list are connected together. </p>
</td>
</tr>
<tr id="row1963595749093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1652701586093534"><a name="p1652701586093534"></a><a name="p1652701586093534"></a><a href="Graphic.md#ga78d73f33cc63d0121342f52a818881d5">GetLoopState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1693543559093534"><a name="p1693543559093534"></a><a name="p1693543559093534"></a>bool&nbsp;</p>
<p id="p1053335334093534"><a name="p1053335334093534"></a><a name="p1053335334093534"></a>Checks whether this list is in a loop state. </p>
</td>
</tr>
<tr id="row1496189744093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p680447598093534"><a name="p680447598093534"></a><a name="p680447598093534"></a><a href="Graphic.md#ga919b4f3116ca0d0971a48b7a14921954">SetSelectPosition</a> (uint16_t position)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1411672819093534"><a name="p1411672819093534"></a><a name="p1411672819093534"></a>void&nbsp;</p>
<p id="p1844751552093534"><a name="p1844751552093534"></a><a name="p1844751552093534"></a>Sets the position where a child view is selected as this list scrolls. </p>
</td>
</tr>
<tr id="row1526201842093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1684266630093534"><a name="p1684266630093534"></a><a name="p1684266630093534"></a><a href="Graphic.md#ga199fdcf3ef797e5f61073a4be3b06642">GetSelectView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p461770303093534"><a name="p461770303093534"></a><a name="p461770303093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p440383910093534"><a name="p440383910093534"></a><a name="p440383910093534"></a>Obtains the child view being selected at the preset position. </p>
</td>
</tr>
<tr id="row1266664549093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14093736093534"><a name="p14093736093534"></a><a name="p14093736093534"></a><a href="Graphic.md#gad6b2f7598033f4e1d0d73e30b0e41f02">SetScrollStateListener</a> (<a href="OHOS-ListScrollListener.md">ListScrollListener</a> *scrollListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p858879280093534"><a name="p858879280093534"></a><a name="p858879280093534"></a>void&nbsp;</p>
<p id="p66785463093534"><a name="p66785463093534"></a><a name="p66785463093534"></a>Sets the listener that contains a callback to be invoked when a child view is selected as this list scrolls. </p>
</td>
</tr>
<tr id="row1194526920093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1713793117093534"><a name="p1713793117093534"></a><a name="p1713793117093534"></a><a href="Graphic.md#gaf2aabfa8e8edd803d034c23efe45f57b">RefreshList</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p467081431093534"><a name="p467081431093534"></a><a name="p467081431093534"></a>void&nbsp;</p>
<p id="p1485512202093534"><a name="p1485512202093534"></a><a name="p1485512202093534"></a>Refreshes this list. The number of child views in the current view is fixed and the positions of those reserved child views as this list scrolls remain unchanged. </p>
</td>
</tr>
<tr id="row1597599024093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p640488506093534"><a name="p640488506093534"></a><a name="p640488506093534"></a><a href="Graphic.md#ga034799920648552008146a0d9aca3424">EnableAutoAlign</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p437251172093534"><a name="p437251172093534"></a><a name="p437251172093534"></a>void&nbsp;</p>
<p id="p1861371310093534"><a name="p1861371310093534"></a><a name="p1861371310093534"></a>Sets the automatic alignment state for this list. When a scroll stops, a child view is selected and its position is automatically aligned with the preset position. </p>
</td>
</tr>
<tr id="row1102588471093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p969334715093534"><a name="p969334715093534"></a><a name="p969334715093534"></a><a href="Graphic.md#gaa55aae2e8066fecc5941e021a7f30d7e">RemoveAll</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422425372093534"><a name="p422425372093534"></a><a name="p422425372093534"></a>void&nbsp;</p>
<p id="p1597598689093534"><a name="p1597598689093534"></a><a name="p1597598689093534"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row1664754992093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p106028216093534"><a name="p106028216093534"></a><a name="p106028216093534"></a><a href="Graphic.md#ga93a169fba7c98f6534692cba9e8d539b">UIAbstractScroll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1300822085093534"><a name="p1300822085093534"></a><a name="p1300822085093534"></a>&nbsp;</p>
<p id="p1739969272093534"><a name="p1739969272093534"></a><a name="p1739969272093534"></a>A constructor used to create a <strong id="b558244288093534"><a name="b558244288093534"></a><a name="b558244288093534"></a><a href="OHOS-UIAbstractScroll.md">UIAbstractScroll</a></strong> instance. </p>
</td>
</tr>
<tr id="row1019514832093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p742620903093534"><a name="p742620903093534"></a><a name="p742620903093534"></a><a href="Graphic.md#ga414798ec7357edc85409128fba0a813c">~UIAbstractScroll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p664115981093534"><a name="p664115981093534"></a><a name="p664115981093534"></a>virtual&nbsp;</p>
<p id="p1946449917093534"><a name="p1946449917093534"></a><a name="p1946449917093534"></a>A destructor used to delete the <strong id="b585047402093534"><a name="b585047402093534"></a><a name="b585047402093534"></a><a href="OHOS-UIAbstractScroll.md">UIAbstractScroll</a></strong> instance. </p>
</td>
</tr>
<tr id="row711889031093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p475302926093534"><a name="p475302926093534"></a><a name="p475302926093534"></a><a href="Graphic.md#ga443783170697bea9a933843ad2a92283">GetDirection</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1259528926093534"><a name="p1259528926093534"></a><a name="p1259528926093534"></a>uint8_t&nbsp;</p>
<p id="p2054101115093534"><a name="p2054101115093534"></a><a name="p2054101115093534"></a>Obtains the scroll direction. </p>
</td>
</tr>
<tr id="row749642078093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1330777585093534"><a name="p1330777585093534"></a><a name="p1330777585093534"></a><a href="Graphic.md#gab37cea97d63ee9ca609c9a1ed0f1e281">SetScrollBlankSize</a> (uint16_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1138054426093534"><a name="p1138054426093534"></a><a name="p1138054426093534"></a>void&nbsp;</p>
<p id="p1179344303093534"><a name="p1179344303093534"></a><a name="p1179344303093534"></a>Sets the blank size for this scroll view. </p>
</td>
</tr>
<tr id="row936132808093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1313839528093534"><a name="p1313839528093534"></a><a name="p1313839528093534"></a><a href="Graphic.md#gae2d6f5c97a316ecd3b41fecfa35a351f">SetMaxScrollDistance</a> (uint16_t distance)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p424395447093534"><a name="p424395447093534"></a><a name="p424395447093534"></a>void&nbsp;</p>
<p id="p132718365093534"><a name="p132718365093534"></a><a name="p132718365093534"></a>Sets the maximum scroll distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row339504228093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p415003699093534"><a name="p415003699093534"></a><a name="p415003699093534"></a><a href="Graphic.md#ga5d7fefcd2057e868a8f6c6a6000aa7ef">SetReboundSize</a> (uint16_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2089449485093534"><a name="p2089449485093534"></a><a name="p2089449485093534"></a>void&nbsp;</p>
<p id="p1000598404093534"><a name="p1000598404093534"></a><a name="p1000598404093534"></a>Sets the rebound size, which is the distance a knob moves after being released when it reaches the end of a scrollbar. </p>
</td>
</tr>
<tr id="row2049649844093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1020895696093534"><a name="p1020895696093534"></a><a name="p1020895696093534"></a><a href="Graphic.md#ga71a2b17d4145479ed2e2ca000eb7e86e">GetMaxScrollDistance</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1371909805093534"><a name="p1371909805093534"></a><a name="p1371909805093534"></a>uint16_t&nbsp;</p>
<p id="p266276509093534"><a name="p266276509093534"></a><a name="p266276509093534"></a>Obtains the maximum scroll distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row866454568093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p349765069093534"><a name="p349765069093534"></a><a name="p349765069093534"></a><a href="Graphic.md#ga957ec65a7efad6818be6df5169158aad">SetDragFunc</a> (EasingFunc func)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1242132401093534"><a name="p1242132401093534"></a><a name="p1242132401093534"></a>void&nbsp;</p>
<p id="p800423728093534"><a name="p800423728093534"></a><a name="p800423728093534"></a>Sets the easing function that specifies a scroll animation after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row115655321093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p293576855093534"><a name="p293576855093534"></a><a name="p293576855093534"></a><a href="Graphic.md#ga4dde5f89d70304e77a96d4f4679438c2">SetThrowDrag</a> (bool throwDrag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p822300264093534"><a name="p822300264093534"></a><a name="p822300264093534"></a>void&nbsp;</p>
<p id="p920758286093534"><a name="p920758286093534"></a><a name="p920758286093534"></a>Sets whether to continue scrolling after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row647075016093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2105563090093534"><a name="p2105563090093534"></a><a name="p2105563090093534"></a><a href="Graphic.md#gad344babd5b251ed908cdf628fae55093">SetDragACCLevel</a> (uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p46765010093534"><a name="p46765010093534"></a><a name="p46765010093534"></a>void&nbsp;</p>
<p id="p1218681930093534"><a name="p1218681930093534"></a><a name="p1218681930093534"></a>Sets the drag acceleration. </p>
</td>
</tr>
<tr id="row514993285093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p742188744093534"><a name="p742188744093534"></a><a name="p742188744093534"></a><a href="Graphic.md#ga29e68195b56783f265d85506f130c664">GetDragACCLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p116517019093534"><a name="p116517019093534"></a><a name="p116517019093534"></a>uint8_t&nbsp;</p>
<p id="p1957170002093534"><a name="p1957170002093534"></a><a name="p1957170002093534"></a>Obtains the drag acceleration. </p>
</td>
</tr>
<tr id="row1581666498093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1364600467093534"><a name="p1364600467093534"></a><a name="p1364600467093534"></a><a href="Graphic.md#gafab9d1a8f5987b50f9111c733ada6341">SetSwipeACCLevel</a> (uint16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1639104132093534"><a name="p1639104132093534"></a><a name="p1639104132093534"></a>void&nbsp;</p>
<p id="p1109833745093534"><a name="p1109833745093534"></a><a name="p1109833745093534"></a>Sets the compensation distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row832271106093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1278252547093534"><a name="p1278252547093534"></a><a name="p1278252547093534"></a><a href="Graphic.md#ga25dad3242949f0fbeff47d6df06053f6">GetSwipeACCLevel</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1890289121093534"><a name="p1890289121093534"></a><a name="p1890289121093534"></a>uint8_t&nbsp;</p>
<p id="p313025993093534"><a name="p313025993093534"></a><a name="p313025993093534"></a>Obtains the compensation distance after a finger lifts the screen. </p>
</td>
</tr>
<tr id="row1384888962093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p873791086093534"><a name="p873791086093534"></a><a name="p873791086093534"></a><a href="Graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1226411057093534"><a name="p1226411057093534"></a><a name="p1226411057093534"></a>&nbsp;</p>
<p id="p410960909093534"><a name="p410960909093534"></a><a name="p410960909093534"></a>A default constructor used to create a <strong id="b152255023093534"><a name="b152255023093534"></a><a name="b152255023093534"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row614850772093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1296955592093534"><a name="p1296955592093534"></a><a name="p1296955592093534"></a><a href="Graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1101374811093534"><a name="p1101374811093534"></a><a name="p1101374811093534"></a>virtual&nbsp;</p>
<p id="p1629546631093534"><a name="p1629546631093534"></a><a name="p1629546631093534"></a>A destructor used to delete the <strong id="b1804219807093534"><a name="b1804219807093534"></a><a name="b1804219807093534"></a><a href="OHOS-UIViewGroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row99462474093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1991176237093534"><a name="p1991176237093534"></a><a name="p1991176237093534"></a><a href="Graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p511048428093534"><a name="p511048428093534"></a><a name="p511048428093534"></a>UIViewType&nbsp;</p>
<p id="p2072655606093534"><a name="p2072655606093534"></a><a name="p2072655606093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row538626471093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p626423404093534"><a name="p626423404093534"></a><a name="p626423404093534"></a><a href="Graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1746221275093534"><a name="p1746221275093534"></a><a name="p1746221275093534"></a>virtual void&nbsp;</p>
<p id="p2143109468093534"><a name="p2143109468093534"></a><a name="p2143109468093534"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row980336493093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p908001815093534"><a name="p908001815093534"></a><a name="p908001815093534"></a><a href="Graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="OHOS-UIView.md">UIView</a> *prevView, <a href="OHOS-UIView.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p273465302093534"><a name="p273465302093534"></a><a name="p273465302093534"></a>virtual void&nbsp;</p>
<p id="p1889280530093534"><a name="p1889280530093534"></a><a name="p1889280530093534"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1127294583093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p439827832093534"><a name="p439827832093534"></a><a name="p439827832093534"></a><a href="Graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="OHOS-UIView.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2120383172093534"><a name="p2120383172093534"></a><a name="p2120383172093534"></a>virtual void&nbsp;</p>
<p id="p1485718757093534"><a name="p1485718757093534"></a><a name="p1485718757093534"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row1377808228093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1068508927093534"><a name="p1068508927093534"></a><a name="p1068508927093534"></a><a href="Graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p427155639093534"><a name="p427155639093534"></a><a name="p427155639093534"></a>virtual void&nbsp;</p>
<p id="p1329307270093534"><a name="p1329307270093534"></a><a name="p1329307270093534"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row1459420863093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p369206482093534"><a name="p369206482093534"></a><a name="p369206482093534"></a><a href="Graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p941895943093534"><a name="p941895943093534"></a><a name="p941895943093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1925470160093534"><a name="p1925470160093534"></a><a name="p1925470160093534"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row1373609286093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1704845187093534"><a name="p1704845187093534"></a><a name="p1704845187093534"></a><a href="Graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1145695885093534"><a name="p1145695885093534"></a><a name="p1145695885093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1220711743093534"><a name="p1220711743093534"></a><a name="p1220711743093534"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row1846662855093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1350761597093534"><a name="p1350761597093534"></a><a name="p1350761597093534"></a><a href="Graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1724192583093534"><a name="p1724192583093534"></a><a name="p1724192583093534"></a>void&nbsp;</p>
<p id="p457866589093534"><a name="p457866589093534"></a><a name="p457866589093534"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row1638469473093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1239909480093534"><a name="p1239909480093534"></a><a name="p1239909480093534"></a><a href="Graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p184205315093534"><a name="p184205315093534"></a><a name="p184205315093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1382891506093534"><a name="p1382891506093534"></a><a name="p1382891506093534"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row1952279303093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p420375657093534"><a name="p420375657093534"></a><a name="p420375657093534"></a><a href="Graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1995721223093534"><a name="p1995721223093534"></a><a name="p1995721223093534"></a>void&nbsp;</p>
<p id="p1277919048093534"><a name="p1277919048093534"></a><a name="p1277919048093534"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row61200045093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1356029896093534"><a name="p1356029896093534"></a><a name="p1356029896093534"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1264134456093534"><a name="p1264134456093534"></a><a name="p1264134456093534"></a>&nbsp;</p>
<p id="p165155263093534"><a name="p165155263093534"></a><a name="p165155263093534"></a>A default constructor used to create an <strong id="b320695612093534"><a name="b320695612093534"></a><a name="b320695612093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row14279097093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p752339595093534"><a name="p752339595093534"></a><a name="p752339595093534"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1934815232093534"><a name="p1934815232093534"></a><a name="p1934815232093534"></a>&nbsp;</p>
<p id="p1124203266093534"><a name="p1124203266093534"></a><a name="p1124203266093534"></a>A constructor used to create an <strong id="b819701841093534"><a name="b819701841093534"></a><a name="b819701841093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1928379084093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p402418877093534"><a name="p402418877093534"></a><a name="p402418877093534"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053819054093534"><a name="p2053819054093534"></a><a name="p2053819054093534"></a>virtual&nbsp;</p>
<p id="p95804344093534"><a name="p95804344093534"></a><a name="p95804344093534"></a>A destructor used to delete the <strong id="b843625454093534"><a name="b843625454093534"></a><a name="b843625454093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1113680301093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1926636048093534"><a name="p1926636048093534"></a><a name="p1926636048093534"></a><a href="Graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705601828093534"><a name="p1705601828093534"></a><a name="p1705601828093534"></a>virtual bool&nbsp;</p>
<p id="p528640935093534"><a name="p528640935093534"></a><a name="p528640935093534"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row2112675832093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p987030681093534"><a name="p987030681093534"></a><a name="p987030681093534"></a><a href="Graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p953427674093534"><a name="p953427674093534"></a><a name="p953427674093534"></a>virtual void&nbsp;</p>
<p id="p798814015093534"><a name="p798814015093534"></a><a name="p798814015093534"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row294732877093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984072596093534"><a name="p984072596093534"></a><a name="p984072596093534"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p630931538093534"><a name="p630931538093534"></a><a name="p630931538093534"></a>virtual void&nbsp;</p>
<p id="p320117386093534"><a name="p320117386093534"></a><a name="p320117386093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row818079380093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p82389004093534"><a name="p82389004093534"></a><a name="p82389004093534"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p676134294093534"><a name="p676134294093534"></a><a name="p676134294093534"></a>virtual void&nbsp;</p>
<p id="p30305535093534"><a name="p30305535093534"></a><a name="p30305535093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1235963578093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p235930396093534"><a name="p235930396093534"></a><a name="p235930396093534"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1775642509093534"><a name="p1775642509093534"></a><a name="p1775642509093534"></a>void&nbsp;</p>
<p id="p1141705501093534"><a name="p1141705501093534"></a><a name="p1141705501093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row219268180093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p175659043093534"><a name="p175659043093534"></a><a name="p175659043093534"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2051539565093534"><a name="p2051539565093534"></a><a name="p2051539565093534"></a>void&nbsp;</p>
<p id="p921399362093534"><a name="p921399362093534"></a><a name="p921399362093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row2023792532093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1461330997093534"><a name="p1461330997093534"></a><a name="p1461330997093534"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p456201348093534"><a name="p456201348093534"></a><a name="p456201348093534"></a>virtual bool&nbsp;</p>
<p id="p645576464093534"><a name="p645576464093534"></a><a name="p645576464093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row886209865093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1436675322093534"><a name="p1436675322093534"></a><a name="p1436675322093534"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p334879078093534"><a name="p334879078093534"></a><a name="p334879078093534"></a>virtual bool&nbsp;</p>
<p id="p909813930093534"><a name="p909813930093534"></a><a name="p909813930093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row212932107093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494548002093534"><a name="p1494548002093534"></a><a name="p1494548002093534"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1551688032093534"><a name="p1551688032093534"></a><a name="p1551688032093534"></a>virtual void&nbsp;</p>
<p id="p1647396806093534"><a name="p1647396806093534"></a><a name="p1647396806093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row2112593128093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1251576912093534"><a name="p1251576912093534"></a><a name="p1251576912093534"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p647978762093534"><a name="p647978762093534"></a><a name="p647978762093534"></a>virtual void&nbsp;</p>
<p id="p1574752813093534"><a name="p1574752813093534"></a><a name="p1574752813093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row191479418093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969796192093534"><a name="p1969796192093534"></a><a name="p1969796192093534"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p943745191093534"><a name="p943745191093534"></a><a name="p943745191093534"></a>virtual void&nbsp;</p>
<p id="p785939337093534"><a name="p785939337093534"></a><a name="p785939337093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row994401936093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p401874153093534"><a name="p401874153093534"></a><a name="p401874153093534"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2103490646093534"><a name="p2103490646093534"></a><a name="p2103490646093534"></a>void&nbsp;</p>
<p id="p277836542093534"><a name="p277836542093534"></a><a name="p277836542093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1371196705093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1496851281093534"><a name="p1496851281093534"></a><a name="p1496851281093534"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1900132672093534"><a name="p1900132672093534"></a><a name="p1900132672093534"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p1558290724093534"><a name="p1558290724093534"></a><a name="p1558290724093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row422352866093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419141771093534"><a name="p419141771093534"></a><a name="p419141771093534"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1258859001093534"><a name="p1258859001093534"></a><a name="p1258859001093534"></a>void&nbsp;</p>
<p id="p1588982310093534"><a name="p1588982310093534"></a><a name="p1588982310093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row2016265506093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1217516648093534"><a name="p1217516648093534"></a><a name="p1217516648093534"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p881600545093534"><a name="p881600545093534"></a><a name="p881600545093534"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p1350554257093534"><a name="p1350554257093534"></a><a name="p1350554257093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1118803470093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1650495307093534"><a name="p1650495307093534"></a><a name="p1650495307093534"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p175820943093534"><a name="p175820943093534"></a><a name="p175820943093534"></a>void&nbsp;</p>
<p id="p831027725093534"><a name="p831027725093534"></a><a name="p831027725093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1341518331093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1794988395093534"><a name="p1794988395093534"></a><a name="p1794988395093534"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p160236976093534"><a name="p160236976093534"></a><a name="p160236976093534"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p115186806093534"><a name="p115186806093534"></a><a name="p115186806093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1851448577093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256864927093534"><a name="p256864927093534"></a><a name="p256864927093534"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027027134093534"><a name="p1027027134093534"></a><a name="p1027027134093534"></a>void&nbsp;</p>
<p id="p1551074663093534"><a name="p1551074663093534"></a><a name="p1551074663093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1631243166093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292069181093534"><a name="p1292069181093534"></a><a name="p1292069181093534"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p525643818093534"><a name="p525643818093534"></a><a name="p525643818093534"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p285490591093534"><a name="p285490591093534"></a><a name="p285490591093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1391898480093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p649658928093534"><a name="p649658928093534"></a><a name="p649658928093534"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p317507234093534"><a name="p317507234093534"></a><a name="p317507234093534"></a>void&nbsp;</p>
<p id="p931035426093534"><a name="p931035426093534"></a><a name="p931035426093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1027248670093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1409020242093534"><a name="p1409020242093534"></a><a name="p1409020242093534"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1805692031093534"><a name="p1805692031093534"></a><a name="p1805692031093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1749635295093534"><a name="p1749635295093534"></a><a name="p1749635295093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row922570859093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p879618492093534"><a name="p879618492093534"></a><a name="p879618492093534"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2874723093534"><a name="p2874723093534"></a><a name="p2874723093534"></a>void&nbsp;</p>
<p id="p1012814206093534"><a name="p1012814206093534"></a><a name="p1012814206093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row187598774093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1541638695093534"><a name="p1541638695093534"></a><a name="p1541638695093534"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417934064093534"><a name="p1417934064093534"></a><a name="p1417934064093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1520196520093534"><a name="p1520196520093534"></a><a name="p1520196520093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1123300070093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1933532024093534"><a name="p1933532024093534"></a><a name="p1933532024093534"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p475148447093534"><a name="p475148447093534"></a><a name="p475148447093534"></a>virtual void&nbsp;</p>
<p id="p588289838093534"><a name="p588289838093534"></a><a name="p588289838093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1703443449093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1311807976093534"><a name="p1311807976093534"></a><a name="p1311807976093534"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1574235201093534"><a name="p1574235201093534"></a><a name="p1574235201093534"></a>bool&nbsp;</p>
<p id="p1317728592093534"><a name="p1317728592093534"></a><a name="p1317728592093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row2114468393093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p955669283093534"><a name="p955669283093534"></a><a name="p955669283093534"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1093751650093534"><a name="p1093751650093534"></a><a name="p1093751650093534"></a>void&nbsp;</p>
<p id="p737857936093534"><a name="p737857936093534"></a><a name="p737857936093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row310855596093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1532001448093534"><a name="p1532001448093534"></a><a name="p1532001448093534"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p874805772093534"><a name="p874805772093534"></a><a name="p874805772093534"></a>bool&nbsp;</p>
<p id="p520459407093534"><a name="p520459407093534"></a><a name="p520459407093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row615656167093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p684433934093534"><a name="p684433934093534"></a><a name="p684433934093534"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265901236093534"><a name="p265901236093534"></a><a name="p265901236093534"></a>void&nbsp;</p>
<p id="p805663013093534"><a name="p805663013093534"></a><a name="p805663013093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1942001903093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p413287223093534"><a name="p413287223093534"></a><a name="p413287223093534"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1725570700093534"><a name="p1725570700093534"></a><a name="p1725570700093534"></a>bool&nbsp;</p>
<p id="p314734268093534"><a name="p314734268093534"></a><a name="p314734268093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1915964217093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617566885093534"><a name="p617566885093534"></a><a name="p617566885093534"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1256350438093534"><a name="p1256350438093534"></a><a name="p1256350438093534"></a>void&nbsp;</p>
<p id="p1699684140093534"><a name="p1699684140093534"></a><a name="p1699684140093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1072518579093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p521996784093534"><a name="p521996784093534"></a><a name="p521996784093534"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p184828471093534"><a name="p184828471093534"></a><a name="p184828471093534"></a>bool&nbsp;</p>
<p id="p368103397093534"><a name="p368103397093534"></a><a name="p368103397093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1762350196093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1600322217093534"><a name="p1600322217093534"></a><a name="p1600322217093534"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1878292192093534"><a name="p1878292192093534"></a><a name="p1878292192093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1958466216093534"><a name="p1958466216093534"></a><a name="p1958466216093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1994319610093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1139858493093534"><a name="p1139858493093534"></a><a name="p1139858493093534"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p6820368093534"><a name="p6820368093534"></a><a name="p6820368093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1370531528093534"><a name="p1370531528093534"></a><a name="p1370531528093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1672020775093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1616315393093534"><a name="p1616315393093534"></a><a name="p1616315393093534"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1436976235093534"><a name="p1436976235093534"></a><a name="p1436976235093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1919740663093534"><a name="p1919740663093534"></a><a name="p1919740663093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row836585672093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1923355439093534"><a name="p1923355439093534"></a><a name="p1923355439093534"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620249712093534"><a name="p620249712093534"></a><a name="p620249712093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1294408778093534"><a name="p1294408778093534"></a><a name="p1294408778093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1363542066093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1587736747093534"><a name="p1587736747093534"></a><a name="p1587736747093534"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p898683483093534"><a name="p898683483093534"></a><a name="p898683483093534"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p2054130629093534"><a name="p2054130629093534"></a><a name="p2054130629093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row986733930093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1014877117093534"><a name="p1014877117093534"></a><a name="p1014877117093534"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1098746317093534"><a name="p1098746317093534"></a><a name="p1098746317093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p606883473093534"><a name="p606883473093534"></a><a name="p606883473093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1983926275093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p756893346093534"><a name="p756893346093534"></a><a name="p756893346093534"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p956368707093534"><a name="p956368707093534"></a><a name="p956368707093534"></a>void&nbsp;</p>
<p id="p446353085093534"><a name="p446353085093534"></a><a name="p446353085093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row517464993093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p746475724093534"><a name="p746475724093534"></a><a name="p746475724093534"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1687808804093534"><a name="p1687808804093534"></a><a name="p1687808804093534"></a>virtual void&nbsp;</p>
<p id="p821006976093534"><a name="p821006976093534"></a><a name="p821006976093534"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row621962081093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p258106691093534"><a name="p258106691093534"></a><a name="p258106691093534"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1622091472093534"><a name="p1622091472093534"></a><a name="p1622091472093534"></a>virtual int16_t&nbsp;</p>
<p id="p1387897161093534"><a name="p1387897161093534"></a><a name="p1387897161093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1713321411093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1605034737093534"><a name="p1605034737093534"></a><a name="p1605034737093534"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p633249342093534"><a name="p633249342093534"></a><a name="p633249342093534"></a>virtual void&nbsp;</p>
<p id="p1561532907093534"><a name="p1561532907093534"></a><a name="p1561532907093534"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row646691462093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1899857610093534"><a name="p1899857610093534"></a><a name="p1899857610093534"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p647517166093534"><a name="p647517166093534"></a><a name="p647517166093534"></a>virtual int16_t&nbsp;</p>
<p id="p1238311726093534"><a name="p1238311726093534"></a><a name="p1238311726093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1245658932093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p448395163093534"><a name="p448395163093534"></a><a name="p448395163093534"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1630238638093534"><a name="p1630238638093534"></a><a name="p1630238638093534"></a>virtual void&nbsp;</p>
<p id="p735614018093534"><a name="p735614018093534"></a><a name="p735614018093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row351428578093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1323116098093534"><a name="p1323116098093534"></a><a name="p1323116098093534"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2031264526093534"><a name="p2031264526093534"></a><a name="p2031264526093534"></a>virtual void&nbsp;</p>
<p id="p1253307636093534"><a name="p1253307636093534"></a><a name="p1253307636093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row19513439093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236100826093534"><a name="p236100826093534"></a><a name="p236100826093534"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1502212944093534"><a name="p1502212944093534"></a><a name="p1502212944093534"></a>int16_t&nbsp;</p>
<p id="p1839594041093534"><a name="p1839594041093534"></a><a name="p1839594041093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row496499958093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p190779380093534"><a name="p190779380093534"></a><a name="p190779380093534"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p673407471093534"><a name="p673407471093534"></a><a name="p673407471093534"></a>virtual void&nbsp;</p>
<p id="p1256693197093534"><a name="p1256693197093534"></a><a name="p1256693197093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row690933327093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1004688362093534"><a name="p1004688362093534"></a><a name="p1004688362093534"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1601028207093534"><a name="p1601028207093534"></a><a name="p1601028207093534"></a>int16_t&nbsp;</p>
<p id="p255903511093534"><a name="p255903511093534"></a><a name="p255903511093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row63303315093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p562658309093534"><a name="p562658309093534"></a><a name="p562658309093534"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p765304519093534"><a name="p765304519093534"></a><a name="p765304519093534"></a>virtual void&nbsp;</p>
<p id="p1163340944093534"><a name="p1163340944093534"></a><a name="p1163340944093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row535428020093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p708724205093534"><a name="p708724205093534"></a><a name="p708724205093534"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1099935395093534"><a name="p1099935395093534"></a><a name="p1099935395093534"></a>virtual void&nbsp;</p>
<p id="p1472476303093534"><a name="p1472476303093534"></a><a name="p1472476303093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1674454876093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1205290390093534"><a name="p1205290390093534"></a><a name="p1205290390093534"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1653569710093534"><a name="p1653569710093534"></a><a name="p1653569710093534"></a>bool&nbsp;</p>
<p id="p1503037265093534"><a name="p1503037265093534"></a><a name="p1503037265093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row2033978906093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p441923753093534"><a name="p441923753093534"></a><a name="p441923753093534"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1097423776093534"><a name="p1097423776093534"></a><a name="p1097423776093534"></a>void&nbsp;</p>
<p id="p1782519714093534"><a name="p1782519714093534"></a><a name="p1782519714093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1797654299093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892891466093534"><a name="p1892891466093534"></a><a name="p1892891466093534"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1050478518093534"><a name="p1050478518093534"></a><a name="p1050478518093534"></a>void&nbsp;</p>
<p id="p453896103093534"><a name="p453896103093534"></a><a name="p453896103093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1844514221093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p339879168093534"><a name="p339879168093534"></a><a name="p339879168093534"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1933210746093534"><a name="p1933210746093534"></a><a name="p1933210746093534"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p547529710093534"><a name="p547529710093534"></a><a name="p547529710093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1239961487093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2129435030093534"><a name="p2129435030093534"></a><a name="p2129435030093534"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1850135192093534"><a name="p1850135192093534"></a><a name="p1850135192093534"></a>void&nbsp;</p>
<p id="p1880334434093534"><a name="p1880334434093534"></a><a name="p1880334434093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row52279348093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1204199908093534"><a name="p1204199908093534"></a><a name="p1204199908093534"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p396603918093534"><a name="p396603918093534"></a><a name="p396603918093534"></a>const char *&nbsp;</p>
<p id="p889281529093534"><a name="p889281529093534"></a><a name="p889281529093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row324186174093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p490001193093534"><a name="p490001193093534"></a><a name="p490001193093534"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1292343670093534"><a name="p1292343670093534"></a><a name="p1292343670093534"></a>void&nbsp;</p>
<p id="p1643822951093534"><a name="p1643822951093534"></a><a name="p1643822951093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row43942406093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1618792840093534"><a name="p1618792840093534"></a><a name="p1618792840093534"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p528102390093534"><a name="p528102390093534"></a><a name="p528102390093534"></a>int16_t&nbsp;</p>
<p id="p1190967564093534"><a name="p1190967564093534"></a><a name="p1190967564093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row720019102093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p188601588093534"><a name="p188601588093534"></a><a name="p188601588093534"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1085757072093534"><a name="p1085757072093534"></a><a name="p1085757072093534"></a>virtual void&nbsp;</p>
<p id="p734889164093534"><a name="p734889164093534"></a><a name="p734889164093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row527232900093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1029051807093534"><a name="p1029051807093534"></a><a name="p1029051807093534"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1063707965093534"><a name="p1063707965093534"></a><a name="p1063707965093534"></a>void&nbsp;</p>
<p id="p1766009455093534"><a name="p1766009455093534"></a><a name="p1766009455093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row756812906093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1164869257093534"><a name="p1164869257093534"></a><a name="p1164869257093534"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1385639421093534"><a name="p1385639421093534"></a><a name="p1385639421093534"></a>void&nbsp;</p>
<p id="p1141405605093534"><a name="p1141405605093534"></a><a name="p1141405605093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1643041958093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p484967456093534"><a name="p484967456093534"></a><a name="p484967456093534"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p890867687093534"><a name="p890867687093534"></a><a name="p890867687093534"></a>void&nbsp;</p>
<p id="p654871631093534"><a name="p654871631093534"></a><a name="p654871631093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row127582331093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p555431885093534"><a name="p555431885093534"></a><a name="p555431885093534"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p40401385093534"><a name="p40401385093534"></a><a name="p40401385093534"></a>void&nbsp;</p>
<p id="p828637969093534"><a name="p828637969093534"></a><a name="p828637969093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1255067171093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2013383918093534"><a name="p2013383918093534"></a><a name="p2013383918093534"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p585275412093534"><a name="p585275412093534"></a><a name="p585275412093534"></a>void&nbsp;</p>
<p id="p461764973093534"><a name="p461764973093534"></a><a name="p461764973093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row311488765093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1787184294093534"><a name="p1787184294093534"></a><a name="p1787184294093534"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1837507828093534"><a name="p1837507828093534"></a><a name="p1837507828093534"></a>void&nbsp;</p>
<p id="p1158759003093534"><a name="p1158759003093534"></a><a name="p1158759003093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1092733628093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505619297093534"><a name="p1505619297093534"></a><a name="p1505619297093534"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p604773860093534"><a name="p604773860093534"></a><a name="p604773860093534"></a>void&nbsp;</p>
<p id="p1140546188093534"><a name="p1140546188093534"></a><a name="p1140546188093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row555223341093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1088011626093534"><a name="p1088011626093534"></a><a name="p1088011626093534"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1881639307093534"><a name="p1881639307093534"></a><a name="p1881639307093534"></a>void&nbsp;</p>
<p id="p1913725301093534"><a name="p1913725301093534"></a><a name="p1913725301093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1283257648093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1829186351093534"><a name="p1829186351093534"></a><a name="p1829186351093534"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p842366483093534"><a name="p842366483093534"></a><a name="p842366483093534"></a>void&nbsp;</p>
<p id="p1050070582093534"><a name="p1050070582093534"></a><a name="p1050070582093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row680475889093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1492170486093534"><a name="p1492170486093534"></a><a name="p1492170486093534"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059236343093534"><a name="p1059236343093534"></a><a name="p1059236343093534"></a>void&nbsp;</p>
<p id="p1226077334093534"><a name="p1226077334093534"></a><a name="p1226077334093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1855648279093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1055313822093534"><a name="p1055313822093534"></a><a name="p1055313822093534"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p120877050093534"><a name="p120877050093534"></a><a name="p120877050093534"></a>void&nbsp;</p>
<p id="p141452982093534"><a name="p141452982093534"></a><a name="p141452982093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row215029955093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1373304174093534"><a name="p1373304174093534"></a><a name="p1373304174093534"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1088236564093534"><a name="p1088236564093534"></a><a name="p1088236564093534"></a>void&nbsp;</p>
<p id="p1990313835093534"><a name="p1990313835093534"></a><a name="p1990313835093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row2043383378093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1162934643093534"><a name="p1162934643093534"></a><a name="p1162934643093534"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p744521825093534"><a name="p744521825093534"></a><a name="p744521825093534"></a>void&nbsp;</p>
<p id="p176707244093534"><a name="p176707244093534"></a><a name="p176707244093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1085197832093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1516621546093534"><a name="p1516621546093534"></a><a name="p1516621546093534"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1730239673093534"><a name="p1730239673093534"></a><a name="p1730239673093534"></a>void&nbsp;</p>
<p id="p414812936093534"><a name="p414812936093534"></a><a name="p414812936093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row342038972093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1304713364093534"><a name="p1304713364093534"></a><a name="p1304713364093534"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1887839416093534"><a name="p1887839416093534"></a><a name="p1887839416093534"></a>void&nbsp;</p>
<p id="p542039418093534"><a name="p542039418093534"></a><a name="p542039418093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1483931923093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p757946380093534"><a name="p757946380093534"></a><a name="p757946380093534"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p868041074093534"><a name="p868041074093534"></a><a name="p868041074093534"></a>virtual void&nbsp;</p>
<p id="p1481948226093534"><a name="p1481948226093534"></a><a name="p1481948226093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row547669729093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p220281301093534"><a name="p220281301093534"></a><a name="p220281301093534"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1219053465093534"><a name="p1219053465093534"></a><a name="p1219053465093534"></a>virtual void&nbsp;</p>
<p id="p2036616682093534"><a name="p2036616682093534"></a><a name="p2036616682093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row2076688743093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1116869401093534"><a name="p1116869401093534"></a><a name="p1116869401093534"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1640395587093534"><a name="p1640395587093534"></a><a name="p1640395587093534"></a>virtual int64_t&nbsp;</p>
<p id="p37201328093534"><a name="p37201328093534"></a><a name="p37201328093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1771711141093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1098346491093534"><a name="p1098346491093534"></a><a name="p1098346491093534"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1414850534093534"><a name="p1414850534093534"></a><a name="p1414850534093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1168957026093534"><a name="p1168957026093534"></a><a name="p1168957026093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1535145384093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p342866763093534"><a name="p342866763093534"></a><a name="p342866763093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1643500965093534"><a name="p1643500965093534"></a><a name="p1643500965093534"></a>void *&nbsp;</p>
<p id="p609454942093534"><a name="p609454942093534"></a><a name="p609454942093534"></a>Overrides the <strong id="b1896429976093534"><a name="b1896429976093534"></a><a name="b1896429976093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row816783391093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1578335293093534"><a name="p1578335293093534"></a><a name="p1578335293093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p158265565093534"><a name="p158265565093534"></a><a name="p158265565093534"></a>void&nbsp;</p>
<p id="p1607105610093534"><a name="p1607105610093534"></a><a name="p1607105610093534"></a>Overrides the <strong id="b1431445082093534"><a name="b1431445082093534"></a><a name="b1431445082093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table353235355093534"></a>
<table><thead align="left"><tr id="row1961583816093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1430671297093534"><a name="p1430671297093534"></a><a name="p1430671297093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1063483078093534"><a name="p1063483078093534"></a><a name="p1063483078093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1616361407093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2086111075093534"><a name="p2086111075093534"></a><a name="p2086111075093534"></a><a href="Graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p374395991093534"><a name="p374395991093534"></a><a name="p374395991093534"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row1955501948093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1907390911093534"><a name="p1907390911093534"></a><a name="p1907390911093534"></a><a href="Graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1281499028093534"><a name="p1281499028093534"></a><a name="p1281499028093534"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row1916000342093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1278403959093534"><a name="p1278403959093534"></a><a name="p1278403959093534"></a><a href="Graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1155567514093534"><a name="p1155567514093534"></a><a name="p1155567514093534"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row1154594022093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p224722594093534"><a name="p224722594093534"></a><a name="p224722594093534"></a><a href="Graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p20495883093534"><a name="p20495883093534"></a><a name="p20495883093534"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row927774760093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1180159660093534"><a name="p1180159660093534"></a><a name="p1180159660093534"></a><a href="Graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p782719460093534"><a name="p782719460093534"></a><a name="p782719460093534"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row128360622093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p736507162093534"><a name="p736507162093534"></a><a name="p736507162093534"></a><a href="Graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038165540093534"><a name="p1038165540093534"></a><a name="p1038165540093534"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row69801972093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p993676644093534"><a name="p993676644093534"></a><a name="p993676644093534"></a><a href="Graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p851160858093534"><a name="p851160858093534"></a><a name="p851160858093534"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row798657304093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p120684526093534"><a name="p120684526093534"></a><a name="p120684526093534"></a><a href="Graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1067787841093534"><a name="p1067787841093534"></a><a name="p1067787841093534"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

