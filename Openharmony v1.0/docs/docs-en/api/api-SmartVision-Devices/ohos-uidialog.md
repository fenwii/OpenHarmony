# OHOS::UIDialog<a name="EN-US_TOPIC_0000001055198154"></a>

## **Overview**<a name="section250739381093534"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Represents a dialog box. 

A dialog box displays information for user input. After a button is clicked in the dialog box, the corresponding callback event is triggered.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1702833998093534"></a>

## Public Types<a name="pub-types"></a>

<a name="table1165102841093534"></a>
<table><thead align="left"><tr id="row686388660093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1082192905093534"><a name="p1082192905093534"></a><a name="p1082192905093534"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p199139138093534"><a name="p199139138093534"></a><a name="p199139138093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row329730392093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1758802560093534"><a name="p1758802560093534"></a><a name="p1758802560093534"></a><a href="graphic.md#ga1bfefa0b46fd5a79a28d0c9a75114295">DialogButtonType</a> { <a href="graphic.md#gga1bfefa0b46fd5a79a28d0c9a75114295a39ef626649e9e14c6561411867e50f00">DialogButtonType::BUTTON1</a>, <a href="graphic.md#gga1bfefa0b46fd5a79a28d0c9a75114295a752441e0500e1807164a5f758ed93a8c">DialogButtonType::BUTTON2</a>, <a href="graphic.md#gga1bfefa0b46fd5a79a28d0c9a75114295a86707c1d7552f48007cc25b77a2db21b">DialogButtonType::BUTTON3</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1524048169093534"><a name="p1524048169093534"></a><a name="p1524048169093534"></a>Enumerates buttons in a dialog box. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table851066320093534"></a>
<table><thead align="left"><tr id="row101378046093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1895959438093534"><a name="p1895959438093534"></a><a name="p1895959438093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1579038389093534"><a name="p1579038389093534"></a><a name="p1579038389093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1334799032093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1465462768093534"><a name="p1465462768093534"></a><a name="p1465462768093534"></a><a href="graphic.md#gaeaaddc56316206d4465ce8c927a686b7">UIDialog</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p204753587093534"><a name="p204753587093534"></a><a name="p204753587093534"></a> </p>
<p id="p627378643093534"><a name="p627378643093534"></a><a name="p627378643093534"></a>A constructor used to create a <strong id="b478633266093534"><a name="b478633266093534"></a><a name="b478633266093534"></a><a href="ohos-uidialog.md">UIDialog</a></strong> instance. </p>
</td>
</tr>
<tr id="row600472799093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p469442098093534"><a name="p469442098093534"></a><a name="p469442098093534"></a><a href="graphic.md#gae5b58ec7225efdbfaf9947e46bfd2616">~UIDialog</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p569705964093534"><a name="p569705964093534"></a><a name="p569705964093534"></a>virtual </p>
<p id="p1276623247093534"><a name="p1276623247093534"></a><a name="p1276623247093534"></a>A destructor used to delete the <strong id="b198321125093534"><a name="b198321125093534"></a><a name="b198321125093534"></a><a href="ohos-uidialog.md">UIDialog</a></strong> instance. </p>
</td>
</tr>
<tr id="row777661715093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p264779139093534"><a name="p264779139093534"></a><a name="p264779139093534"></a><a href="graphic.md#gac0b18fe28ee4ad44814d3897d3cd5c05">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1494003939093534"><a name="p1494003939093534"></a><a name="p1494003939093534"></a>UIViewType </p>
<p id="p1385111928093534"><a name="p1385111928093534"></a><a name="p1385111928093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row342428739093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1832503994093534"><a name="p1832503994093534"></a><a name="p1832503994093534"></a><a href="graphic.md#ga5629d5a1e19bc38087e8b35d65292714">SetTitle</a> (const char *title)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2078057409093534"><a name="p2078057409093534"></a><a name="p2078057409093534"></a>void </p>
<p id="p1551855802093534"><a name="p1551855802093534"></a><a name="p1551855802093534"></a>Sets the title for this dialog box. </p>
</td>
</tr>
<tr id="row448055605093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1867172945093534"><a name="p1867172945093534"></a><a name="p1867172945093534"></a><a href="graphic.md#ga597e95748fba71238a99c8c17ed848a5">SetText</a> (const char *text)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1504772538093534"><a name="p1504772538093534"></a><a name="p1504772538093534"></a>void </p>
<p id="p1616322764093534"><a name="p1616322764093534"></a><a name="p1616322764093534"></a>Sets the text for this dialog box. </p>
</td>
</tr>
<tr id="row207194703093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p913672869093534"><a name="p913672869093534"></a><a name="p913672869093534"></a><a href="graphic.md#ga6b3cf14760fc07e38f51d366a8e5fdb9">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p821574951093534"><a name="p821574951093534"></a><a name="p821574951093534"></a>bool </p>
<p id="p1318738570093534"><a name="p1318738570093534"></a><a name="p1318738570093534"></a>Checks whether this label needs to be covered before drawing it. </p>
</td>
</tr>
<tr id="row546826681093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1356738853093534"><a name="p1356738853093534"></a><a name="p1356738853093534"></a><a href="graphic.md#gaa8bcf4d2d60becd105d0b87ee2ec18af">SetButton</a> (<a href="graphic.md#ga1bfefa0b46fd5a79a28d0c9a75114295">DialogButtonType</a> buttonType, const char *text, <a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1591418190093534"><a name="p1591418190093534"></a><a name="p1591418190093534"></a>void </p>
<p id="p1452415360093534"><a name="p1452415360093534"></a><a name="p1452415360093534"></a>Sets a button for this dialog box. </p>
</td>
</tr>
<tr id="row646717334093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p524204161093534"><a name="p524204161093534"></a><a name="p524204161093534"></a><a href="graphic.md#gaf836d530b3fa9d50f70053c2b0b528d6">SetVisible</a> (bool visible) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1374526790093534"><a name="p1374526790093534"></a><a name="p1374526790093534"></a>void </p>
<p id="p2006509936093534"><a name="p2006509936093534"></a><a name="p2006509936093534"></a>Sets whether a dialog box is visible. </p>
</td>
</tr>
<tr id="row34206725093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1573130283093534"><a name="p1573130283093534"></a><a name="p1573130283093534"></a><a href="graphic.md#gadae043c6d43d5436ec0374e5d128c654">UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p871669977093534"><a name="p871669977093534"></a><a name="p871669977093534"></a> </p>
<p id="p1063701689093534"><a name="p1063701689093534"></a><a name="p1063701689093534"></a>A default constructor used to create a <strong id="b1564344492093534"><a name="b1564344492093534"></a><a name="b1564344492093534"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row410921834093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1102279694093534"><a name="p1102279694093534"></a><a name="p1102279694093534"></a><a href="graphic.md#ga19ec065bd41a01f0925a4a9ffa450d1c">~UIViewGroup</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p484168724093534"><a name="p484168724093534"></a><a name="p484168724093534"></a>virtual </p>
<p id="p1382722636093534"><a name="p1382722636093534"></a><a name="p1382722636093534"></a>A destructor used to delete the <strong id="b411730006093534"><a name="b411730006093534"></a><a name="b411730006093534"></a><a href="ohos-uiviewgroup.md">UIViewGroup</a></strong> instance. </p>
</td>
</tr>
<tr id="row277187597093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1774911030093534"><a name="p1774911030093534"></a><a name="p1774911030093534"></a><a href="graphic.md#gad5756764839a844ee9bee0c186798029">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p648007754093534"><a name="p648007754093534"></a><a name="p648007754093534"></a>UIViewType </p>
<p id="p964411519093534"><a name="p964411519093534"></a><a name="p964411519093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row747659343093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p111991506093534"><a name="p111991506093534"></a><a name="p111991506093534"></a><a href="graphic.md#gacf5db120308ac7783c493f5437f06cee">Add</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p490147109093534"><a name="p490147109093534"></a><a name="p490147109093534"></a>virtual void </p>
<p id="p1155918402093534"><a name="p1155918402093534"></a><a name="p1155918402093534"></a>Adds a child view. </p>
</td>
</tr>
<tr id="row1691431380093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712344953093534"><a name="p1712344953093534"></a><a name="p1712344953093534"></a><a href="graphic.md#ga84195a993bfe50d8302435ababb63966">Insert</a> (<a href="ohos-uiview.md">UIView</a> *prevView, <a href="ohos-uiview.md">UIView</a> *insertView)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266678961093534"><a name="p1266678961093534"></a><a name="p1266678961093534"></a>virtual void </p>
<p id="p2041488491093534"><a name="p2041488491093534"></a><a name="p2041488491093534"></a>Inserts a new child view behind the current one. </p>
</td>
</tr>
<tr id="row1275324097093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p524893987093534"><a name="p524893987093534"></a><a name="p524893987093534"></a><a href="graphic.md#ga25523928b24d6692f18aed31edb07006">Remove</a> (<a href="ohos-uiview.md">UIView</a> *view)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1549245877093534"><a name="p1549245877093534"></a><a name="p1549245877093534"></a>virtual void </p>
<p id="p2056392482093534"><a name="p2056392482093534"></a><a name="p2056392482093534"></a>Removes a child view. </p>
</td>
</tr>
<tr id="row1914581945093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1062300744093534"><a name="p1062300744093534"></a><a name="p1062300744093534"></a><a href="graphic.md#gaf3ee08173d92932687809049e3c11e9b">RemoveAll</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1832970017093534"><a name="p1832970017093534"></a><a name="p1832970017093534"></a>virtual void </p>
<p id="p22371138093534"><a name="p22371138093534"></a><a name="p22371138093534"></a>Removes all child views. </p>
</td>
</tr>
<tr id="row145919078093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p325270159093534"><a name="p325270159093534"></a><a name="p325270159093534"></a><a href="graphic.md#ga7ea54fc6ef3a8b7dec1bf88ab189f7c7">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p70021544093534"><a name="p70021544093534"></a><a name="p70021544093534"></a>virtual void </p>
<p id="p758545113093534"><a name="p758545113093534"></a><a name="p758545113093534"></a>Obtains the target child view that is visible and can respond to touch events based on given coordinates. </p>
</td>
</tr>
<tr id="row100294143093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p804997549093534"><a name="p804997549093534"></a><a name="p804997549093534"></a><a href="graphic.md#ga776c6c1640cb88b537af227fa5eb0725">MoveChildByOffset</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1854766893093534"><a name="p1854766893093534"></a><a name="p1854766893093534"></a>virtual void </p>
<p id="p1765791228093534"><a name="p1765791228093534"></a><a name="p1765791228093534"></a>Moves all child views. </p>
</td>
</tr>
<tr id="row1049847211093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1931638979093534"><a name="p1931638979093534"></a><a name="p1931638979093534"></a><a href="graphic.md#ga6fed8238b89b013552c5a247aa2471df">GetChildrenHead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p680688323093534"><a name="p680688323093534"></a><a name="p680688323093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1360249584093534"><a name="p1360249584093534"></a><a name="p1360249584093534"></a>Obtains the first child view in this view group. </p>
</td>
</tr>
<tr id="row258407177093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1292112155093534"><a name="p1292112155093534"></a><a name="p1292112155093534"></a><a href="graphic.md#ga1361baa76fbabd2fc81cc249c6868691">GetChildrenTail</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1299801431093534"><a name="p1299801431093534"></a><a name="p1299801431093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1451065540093534"><a name="p1451065540093534"></a><a name="p1451065540093534"></a>Obtains the last child view in this view group. </p>
</td>
</tr>
<tr id="row1488384020093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1919778660093534"><a name="p1919778660093534"></a><a name="p1919778660093534"></a><a href="graphic.md#gad53c52e619a54358a413a836ae0c1861">SetDisallowIntercept</a> (bool flag)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1460889656093534"><a name="p1460889656093534"></a><a name="p1460889656093534"></a>void </p>
<p id="p817061563093534"><a name="p817061563093534"></a><a name="p817061563093534"></a>Sets whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row494671826093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1115433626093534"><a name="p1115433626093534"></a><a name="p1115433626093534"></a><a href="graphic.md#gae9f6ddb5819392546463d6371147c486">GetChildById</a> (const char *id) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p772278405093534"><a name="p772278405093534"></a><a name="p772278405093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p559031435093534"><a name="p559031435093534"></a><a name="p559031435093534"></a>Obtains the target child view with a specified ID. </p>
</td>
</tr>
<tr id="row1006325512093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1183736776093534"><a name="p1183736776093534"></a><a name="p1183736776093534"></a><a href="graphic.md#ga6442ba36114d739df1b17ca8943cc087">SetAutoSize</a> (bool state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p113092773093534"><a name="p113092773093534"></a><a name="p113092773093534"></a>void </p>
<p id="p643906205093534"><a name="p643906205093534"></a><a name="p643906205093534"></a>Sets whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
<tr id="row959157201093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1503206554093534"><a name="p1503206554093534"></a><a name="p1503206554093534"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1470336400093534"><a name="p1470336400093534"></a><a name="p1470336400093534"></a> </p>
<p id="p220206051093534"><a name="p220206051093534"></a><a name="p220206051093534"></a>A default constructor used to create an <strong id="b177982871093534"><a name="b177982871093534"></a><a name="b177982871093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row322694792093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p197515673093534"><a name="p197515673093534"></a><a name="p197515673093534"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1203392833093534"><a name="p1203392833093534"></a><a name="p1203392833093534"></a> </p>
<p id="p844073235093534"><a name="p844073235093534"></a><a name="p844073235093534"></a>A constructor used to create an <strong id="b557694974093534"><a name="b557694974093534"></a><a name="b557694974093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row830351236093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p935385481093534"><a name="p935385481093534"></a><a name="p935385481093534"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p473734555093534"><a name="p473734555093534"></a><a name="p473734555093534"></a>virtual </p>
<p id="p755374933093534"><a name="p755374933093534"></a><a name="p755374933093534"></a>A destructor used to delete the <strong id="b51526603093534"><a name="b51526603093534"></a><a name="b51526603093534"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row949209982093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p782413897093534"><a name="p782413897093534"></a><a name="p782413897093534"></a><a href="graphic.md#ga9a5f43bdc03cde30323b570bfb7ae425">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1538127441093534"><a name="p1538127441093534"></a><a name="p1538127441093534"></a>virtual void </p>
<p id="p1180792321093534"><a name="p1180792321093534"></a><a name="p1180792321093534"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row207502021093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1514618037093534"><a name="p1514618037093534"></a><a name="p1514618037093534"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p49424413093534"><a name="p49424413093534"></a><a name="p49424413093534"></a>virtual void </p>
<p id="p1807136605093534"><a name="p1807136605093534"></a><a name="p1807136605093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1661160901093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p952550849093534"><a name="p952550849093534"></a><a name="p952550849093534"></a><a href="graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1485307976093534"><a name="p1485307976093534"></a><a name="p1485307976093534"></a>virtual void </p>
<p id="p745163070093534"><a name="p745163070093534"></a><a name="p745163070093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row304738743093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p453861285093534"><a name="p453861285093534"></a><a name="p453861285093534"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1561307720093534"><a name="p1561307720093534"></a><a name="p1561307720093534"></a>void </p>
<p id="p1180083753093534"><a name="p1180083753093534"></a><a name="p1180083753093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1211105642093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1686797272093534"><a name="p1686797272093534"></a><a name="p1686797272093534"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1206744570093534"><a name="p1206744570093534"></a><a name="p1206744570093534"></a>void </p>
<p id="p1879619822093534"><a name="p1879619822093534"></a><a name="p1879619822093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1139413639093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1550584962093534"><a name="p1550584962093534"></a><a name="p1550584962093534"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p483542570093534"><a name="p483542570093534"></a><a name="p483542570093534"></a>virtual bool </p>
<p id="p1247182991093534"><a name="p1247182991093534"></a><a name="p1247182991093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row171217051093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1246584887093534"><a name="p1246584887093534"></a><a name="p1246584887093534"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1730254335093534"><a name="p1730254335093534"></a><a name="p1730254335093534"></a>virtual bool </p>
<p id="p2044568445093534"><a name="p2044568445093534"></a><a name="p2044568445093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row312932516093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1675262649093534"><a name="p1675262649093534"></a><a name="p1675262649093534"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1950495060093534"><a name="p1950495060093534"></a><a name="p1950495060093534"></a>virtual bool </p>
<p id="p411622943093534"><a name="p411622943093534"></a><a name="p411622943093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row74326885093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1857224582093534"><a name="p1857224582093534"></a><a name="p1857224582093534"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1078476080093534"><a name="p1078476080093534"></a><a name="p1078476080093534"></a>virtual bool </p>
<p id="p686676741093534"><a name="p686676741093534"></a><a name="p686676741093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1287191239093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p748984774093534"><a name="p748984774093534"></a><a name="p748984774093534"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p545547139093534"><a name="p545547139093534"></a><a name="p545547139093534"></a>virtual void </p>
<p id="p281122509093534"><a name="p281122509093534"></a><a name="p281122509093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row1821124053093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p152468660093534"><a name="p152468660093534"></a><a name="p152468660093534"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1249678451093534"><a name="p1249678451093534"></a><a name="p1249678451093534"></a>virtual void </p>
<p id="p1298973826093534"><a name="p1298973826093534"></a><a name="p1298973826093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1765551550093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1778635025093534"><a name="p1778635025093534"></a><a name="p1778635025093534"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p886490685093534"><a name="p886490685093534"></a><a name="p886490685093534"></a>virtual void </p>
<p id="p1866541817093534"><a name="p1866541817093534"></a><a name="p1866541817093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row918775502093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p176312868093534"><a name="p176312868093534"></a><a name="p176312868093534"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p743390773093534"><a name="p743390773093534"></a><a name="p743390773093534"></a>virtual void </p>
<p id="p1177684669093534"><a name="p1177684669093534"></a><a name="p1177684669093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row90947459093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1445909999093534"><a name="p1445909999093534"></a><a name="p1445909999093534"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p138043024093534"><a name="p138043024093534"></a><a name="p138043024093534"></a>void </p>
<p id="p2060032517093534"><a name="p2060032517093534"></a><a name="p2060032517093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row567124589093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1088527320093534"><a name="p1088527320093534"></a><a name="p1088527320093534"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p568510021093534"><a name="p568510021093534"></a><a name="p568510021093534"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p2085287738093534"><a name="p2085287738093534"></a><a name="p2085287738093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1915517101093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1564842517093534"><a name="p1564842517093534"></a><a name="p1564842517093534"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059487559093534"><a name="p1059487559093534"></a><a name="p1059487559093534"></a>void </p>
<p id="p1975086952093534"><a name="p1975086952093534"></a><a name="p1975086952093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row165887606093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1768564521093534"><a name="p1768564521093534"></a><a name="p1768564521093534"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p822535573093534"><a name="p822535573093534"></a><a name="p822535573093534"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p1834618278093534"><a name="p1834618278093534"></a><a name="p1834618278093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row140537954093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p946422711093534"><a name="p946422711093534"></a><a name="p946422711093534"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p814469446093534"><a name="p814469446093534"></a><a name="p814469446093534"></a>void </p>
<p id="p243504852093534"><a name="p243504852093534"></a><a name="p243504852093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row372381526093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p284459909093534"><a name="p284459909093534"></a><a name="p284459909093534"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699671851093534"><a name="p1699671851093534"></a><a name="p1699671851093534"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p943464554093534"><a name="p943464554093534"></a><a name="p943464554093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row111774184093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p222422360093534"><a name="p222422360093534"></a><a name="p222422360093534"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1992778079093534"><a name="p1992778079093534"></a><a name="p1992778079093534"></a>void </p>
<p id="p30651470093534"><a name="p30651470093534"></a><a name="p30651470093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row946853040093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p147573203093534"><a name="p147573203093534"></a><a name="p147573203093534"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1875858185093534"><a name="p1875858185093534"></a><a name="p1875858185093534"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p1406555955093534"><a name="p1406555955093534"></a><a name="p1406555955093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1412370914093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p852385519093534"><a name="p852385519093534"></a><a name="p852385519093534"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1329692330093534"><a name="p1329692330093534"></a><a name="p1329692330093534"></a>void </p>
<p id="p1852494800093534"><a name="p1852494800093534"></a><a name="p1852494800093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1307671819093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1373546873093534"><a name="p1373546873093534"></a><a name="p1373546873093534"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2070361313093534"><a name="p2070361313093534"></a><a name="p2070361313093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p443627209093534"><a name="p443627209093534"></a><a name="p443627209093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row737824069093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2115175998093534"><a name="p2115175998093534"></a><a name="p2115175998093534"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1212231788093534"><a name="p1212231788093534"></a><a name="p1212231788093534"></a>void </p>
<p id="p1441788715093534"><a name="p1441788715093534"></a><a name="p1441788715093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1950008334093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1243479987093534"><a name="p1243479987093534"></a><a name="p1243479987093534"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p393499783093534"><a name="p393499783093534"></a><a name="p393499783093534"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p899138093534"><a name="p899138093534"></a><a name="p899138093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1395498890093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1258466535093534"><a name="p1258466535093534"></a><a name="p1258466535093534"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1406755793093534"><a name="p1406755793093534"></a><a name="p1406755793093534"></a>bool </p>
<p id="p100654736093534"><a name="p100654736093534"></a><a name="p100654736093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1821094132093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1802261682093534"><a name="p1802261682093534"></a><a name="p1802261682093534"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p495792636093534"><a name="p495792636093534"></a><a name="p495792636093534"></a>void </p>
<p id="p1381971925093534"><a name="p1381971925093534"></a><a name="p1381971925093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1466367414093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p297782841093534"><a name="p297782841093534"></a><a name="p297782841093534"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1337832990093534"><a name="p1337832990093534"></a><a name="p1337832990093534"></a>bool </p>
<p id="p6657015093534"><a name="p6657015093534"></a><a name="p6657015093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1450242291093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p971015937093534"><a name="p971015937093534"></a><a name="p971015937093534"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p899813113093534"><a name="p899813113093534"></a><a name="p899813113093534"></a>void </p>
<p id="p34181700093534"><a name="p34181700093534"></a><a name="p34181700093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row739873600093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1903102583093534"><a name="p1903102583093534"></a><a name="p1903102583093534"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1290682352093534"><a name="p1290682352093534"></a><a name="p1290682352093534"></a>bool </p>
<p id="p510941405093534"><a name="p510941405093534"></a><a name="p510941405093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1404161819093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p722002160093534"><a name="p722002160093534"></a><a name="p722002160093534"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p932748319093534"><a name="p932748319093534"></a><a name="p932748319093534"></a>void </p>
<p id="p1001254972093534"><a name="p1001254972093534"></a><a name="p1001254972093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1084725579093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1864142829093534"><a name="p1864142829093534"></a><a name="p1864142829093534"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p25770385093534"><a name="p25770385093534"></a><a name="p25770385093534"></a>bool </p>
<p id="p1730132133093534"><a name="p1730132133093534"></a><a name="p1730132133093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row666330690093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651770105093534"><a name="p651770105093534"></a><a name="p651770105093534"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p654008655093534"><a name="p654008655093534"></a><a name="p654008655093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1474118764093534"><a name="p1474118764093534"></a><a name="p1474118764093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row199063508093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p295897634093534"><a name="p295897634093534"></a><a name="p295897634093534"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1293898737093534"><a name="p1293898737093534"></a><a name="p1293898737093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p573786668093534"><a name="p573786668093534"></a><a name="p573786668093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1943812481093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2116734263093534"><a name="p2116734263093534"></a><a name="p2116734263093534"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p80742911093534"><a name="p80742911093534"></a><a name="p80742911093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p40132229093534"><a name="p40132229093534"></a><a name="p40132229093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1407645231093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p206856824093534"><a name="p206856824093534"></a><a name="p206856824093534"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p187152439093534"><a name="p187152439093534"></a><a name="p187152439093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1054896680093534"><a name="p1054896680093534"></a><a name="p1054896680093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1832017577093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1550502389093534"><a name="p1550502389093534"></a><a name="p1550502389093534"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p475365498093534"><a name="p475365498093534"></a><a name="p475365498093534"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p1183785230093534"><a name="p1183785230093534"></a><a name="p1183785230093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1856131473093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985288981093534"><a name="p1985288981093534"></a><a name="p1985288981093534"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1663566708093534"><a name="p1663566708093534"></a><a name="p1663566708093534"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1685924952093534"><a name="p1685924952093534"></a><a name="p1685924952093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1865863116093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1212175330093534"><a name="p1212175330093534"></a><a name="p1212175330093534"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1321559044093534"><a name="p1321559044093534"></a><a name="p1321559044093534"></a>void </p>
<p id="p819365115093534"><a name="p819365115093534"></a><a name="p819365115093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row247713058093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p643219705093534"><a name="p643219705093534"></a><a name="p643219705093534"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1424138572093534"><a name="p1424138572093534"></a><a name="p1424138572093534"></a>virtual void </p>
<p id="p2143862049093534"><a name="p2143862049093534"></a><a name="p2143862049093534"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1997995151093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1113699505093534"><a name="p1113699505093534"></a><a name="p1113699505093534"></a><a href="graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1642905946093534"><a name="p1642905946093534"></a><a name="p1642905946093534"></a>virtual int16_t </p>
<p id="p454342136093534"><a name="p454342136093534"></a><a name="p454342136093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1755144426093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p748112415093534"><a name="p748112415093534"></a><a name="p748112415093534"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p117460043093534"><a name="p117460043093534"></a><a name="p117460043093534"></a>virtual void </p>
<p id="p268922137093534"><a name="p268922137093534"></a><a name="p268922137093534"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row1650125481093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1106875504093534"><a name="p1106875504093534"></a><a name="p1106875504093534"></a><a href="graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1169522667093534"><a name="p1169522667093534"></a><a name="p1169522667093534"></a>virtual int16_t </p>
<p id="p1211547193093534"><a name="p1211547193093534"></a><a name="p1211547193093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row1270045564093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2049012769093534"><a name="p2049012769093534"></a><a name="p2049012769093534"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p803488213093534"><a name="p803488213093534"></a><a name="p803488213093534"></a>virtual void </p>
<p id="p105234685093534"><a name="p105234685093534"></a><a name="p105234685093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1931895952093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220489394093534"><a name="p1220489394093534"></a><a name="p1220489394093534"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2013734439093534"><a name="p2013734439093534"></a><a name="p2013734439093534"></a>virtual void </p>
<p id="p1413019556093534"><a name="p1413019556093534"></a><a name="p1413019556093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row2109762565093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p253690117093534"><a name="p253690117093534"></a><a name="p253690117093534"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1111010452093534"><a name="p1111010452093534"></a><a name="p1111010452093534"></a>int16_t </p>
<p id="p1404230828093534"><a name="p1404230828093534"></a><a name="p1404230828093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row775174817093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2034156825093534"><a name="p2034156825093534"></a><a name="p2034156825093534"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p95068534093534"><a name="p95068534093534"></a><a name="p95068534093534"></a>virtual void </p>
<p id="p902391395093534"><a name="p902391395093534"></a><a name="p902391395093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row413111898093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1701530963093534"><a name="p1701530963093534"></a><a name="p1701530963093534"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p286280308093534"><a name="p286280308093534"></a><a name="p286280308093534"></a>int16_t </p>
<p id="p724446972093534"><a name="p724446972093534"></a><a name="p724446972093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row391472075093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505342408093534"><a name="p1505342408093534"></a><a name="p1505342408093534"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2117450187093534"><a name="p2117450187093534"></a><a name="p2117450187093534"></a>virtual void </p>
<p id="p1251234048093534"><a name="p1251234048093534"></a><a name="p1251234048093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1466020577093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1467017118093534"><a name="p1467017118093534"></a><a name="p1467017118093534"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p113224816093534"><a name="p113224816093534"></a><a name="p113224816093534"></a>virtual void </p>
<p id="p568865509093534"><a name="p568865509093534"></a><a name="p568865509093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row2132188057093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1098292079093534"><a name="p1098292079093534"></a><a name="p1098292079093534"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074704305093534"><a name="p1074704305093534"></a><a name="p1074704305093534"></a>bool </p>
<p id="p1062685904093534"><a name="p1062685904093534"></a><a name="p1062685904093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1542053135093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2118579174093534"><a name="p2118579174093534"></a><a name="p2118579174093534"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073935631093534"><a name="p2073935631093534"></a><a name="p2073935631093534"></a>void </p>
<p id="p978160804093534"><a name="p978160804093534"></a><a name="p978160804093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row877398891093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p557196344093534"><a name="p557196344093534"></a><a name="p557196344093534"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p464573217093534"><a name="p464573217093534"></a><a name="p464573217093534"></a>void </p>
<p id="p1544157094093534"><a name="p1544157094093534"></a><a name="p1544157094093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1437799879093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p662455410093534"><a name="p662455410093534"></a><a name="p662455410093534"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p206094524093534"><a name="p206094524093534"></a><a name="p206094524093534"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p2124575903093534"><a name="p2124575903093534"></a><a name="p2124575903093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row265329245093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1516113013093534"><a name="p1516113013093534"></a><a name="p1516113013093534"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p947883508093534"><a name="p947883508093534"></a><a name="p947883508093534"></a>void </p>
<p id="p1926783053093534"><a name="p1926783053093534"></a><a name="p1926783053093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1750585727093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p7258406093534"><a name="p7258406093534"></a><a name="p7258406093534"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p120742062093534"><a name="p120742062093534"></a><a name="p120742062093534"></a>const char * </p>
<p id="p736065174093534"><a name="p736065174093534"></a><a name="p736065174093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1697294403093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2093745966093534"><a name="p2093745966093534"></a><a name="p2093745966093534"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1513981802093534"><a name="p1513981802093534"></a><a name="p1513981802093534"></a>void </p>
<p id="p417290085093534"><a name="p417290085093534"></a><a name="p417290085093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row2023197547093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1338746846093534"><a name="p1338746846093534"></a><a name="p1338746846093534"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p277042978093534"><a name="p277042978093534"></a><a name="p277042978093534"></a>int16_t </p>
<p id="p1651893347093534"><a name="p1651893347093534"></a><a name="p1651893347093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row204483508093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1909278599093534"><a name="p1909278599093534"></a><a name="p1909278599093534"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1350880321093534"><a name="p1350880321093534"></a><a name="p1350880321093534"></a>virtual void </p>
<p id="p284608463093534"><a name="p284608463093534"></a><a name="p284608463093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1533375554093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1006738367093534"><a name="p1006738367093534"></a><a name="p1006738367093534"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1721709213093534"><a name="p1721709213093534"></a><a name="p1721709213093534"></a>void </p>
<p id="p882093950093534"><a name="p882093950093534"></a><a name="p882093950093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row425781174093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p136393582093534"><a name="p136393582093534"></a><a name="p136393582093534"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p667179065093534"><a name="p667179065093534"></a><a name="p667179065093534"></a>void </p>
<p id="p830359511093534"><a name="p830359511093534"></a><a name="p830359511093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1215883090093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p452570061093534"><a name="p452570061093534"></a><a name="p452570061093534"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2064004112093534"><a name="p2064004112093534"></a><a name="p2064004112093534"></a>void </p>
<p id="p472848784093534"><a name="p472848784093534"></a><a name="p472848784093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1024012237093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1707110569093534"><a name="p1707110569093534"></a><a name="p1707110569093534"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p393866603093534"><a name="p393866603093534"></a><a name="p393866603093534"></a>void </p>
<p id="p2084137901093534"><a name="p2084137901093534"></a><a name="p2084137901093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1479679126093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2001538528093534"><a name="p2001538528093534"></a><a name="p2001538528093534"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p904469806093534"><a name="p904469806093534"></a><a name="p904469806093534"></a>void </p>
<p id="p2060574781093534"><a name="p2060574781093534"></a><a name="p2060574781093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1727014179093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2053852082093534"><a name="p2053852082093534"></a><a name="p2053852082093534"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1181620388093534"><a name="p1181620388093534"></a><a name="p1181620388093534"></a>void </p>
<p id="p143787057093534"><a name="p143787057093534"></a><a name="p143787057093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row111423825093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p472850672093534"><a name="p472850672093534"></a><a name="p472850672093534"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p148097370093534"><a name="p148097370093534"></a><a name="p148097370093534"></a>void </p>
<p id="p1559377210093534"><a name="p1559377210093534"></a><a name="p1559377210093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1937828919093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p242470626093534"><a name="p242470626093534"></a><a name="p242470626093534"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p747322856093534"><a name="p747322856093534"></a><a name="p747322856093534"></a>void </p>
<p id="p982483294093534"><a name="p982483294093534"></a><a name="p982483294093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row104041677093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1878358466093534"><a name="p1878358466093534"></a><a name="p1878358466093534"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p137977571093534"><a name="p137977571093534"></a><a name="p137977571093534"></a>void </p>
<p id="p2016870242093534"><a name="p2016870242093534"></a><a name="p2016870242093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1347044718093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1552590151093534"><a name="p1552590151093534"></a><a name="p1552590151093534"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2055113949093534"><a name="p2055113949093534"></a><a name="p2055113949093534"></a>void </p>
<p id="p1056275596093534"><a name="p1056275596093534"></a><a name="p1056275596093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1915852665093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p887064499093534"><a name="p887064499093534"></a><a name="p887064499093534"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p28317463093534"><a name="p28317463093534"></a><a name="p28317463093534"></a>void </p>
<p id="p1259295338093534"><a name="p1259295338093534"></a><a name="p1259295338093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row2059826947093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p895954607093534"><a name="p895954607093534"></a><a name="p895954607093534"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p178967064093534"><a name="p178967064093534"></a><a name="p178967064093534"></a>void </p>
<p id="p328461915093534"><a name="p328461915093534"></a><a name="p328461915093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1998023814093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1594454344093534"><a name="p1594454344093534"></a><a name="p1594454344093534"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p473745950093534"><a name="p473745950093534"></a><a name="p473745950093534"></a>void </p>
<p id="p1830711853093534"><a name="p1830711853093534"></a><a name="p1830711853093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row914082188093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1816343701093534"><a name="p1816343701093534"></a><a name="p1816343701093534"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p74277865093534"><a name="p74277865093534"></a><a name="p74277865093534"></a>void </p>
<p id="p900105128093534"><a name="p900105128093534"></a><a name="p900105128093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row725406696093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2085310476093534"><a name="p2085310476093534"></a><a name="p2085310476093534"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p595252160093534"><a name="p595252160093534"></a><a name="p595252160093534"></a>void </p>
<p id="p236208520093534"><a name="p236208520093534"></a><a name="p236208520093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row722178193093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1131791193093534"><a name="p1131791193093534"></a><a name="p1131791193093534"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1784068699093534"><a name="p1784068699093534"></a><a name="p1784068699093534"></a>virtual void </p>
<p id="p542021402093534"><a name="p542021402093534"></a><a name="p542021402093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1144821478093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2041732608093534"><a name="p2041732608093534"></a><a name="p2041732608093534"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p603416227093534"><a name="p603416227093534"></a><a name="p603416227093534"></a>virtual void </p>
<p id="p1661772758093534"><a name="p1661772758093534"></a><a name="p1661772758093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row2047286686093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p184477401093534"><a name="p184477401093534"></a><a name="p184477401093534"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1094906047093534"><a name="p1094906047093534"></a><a name="p1094906047093534"></a>virtual int64_t </p>
<p id="p863344836093534"><a name="p863344836093534"></a><a name="p863344836093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1863702937093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1582366975093534"><a name="p1582366975093534"></a><a name="p1582366975093534"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p419943701093534"><a name="p419943701093534"></a><a name="p419943701093534"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p1583201509093534"><a name="p1583201509093534"></a><a name="p1583201509093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1478293837093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p785103212093534"><a name="p785103212093534"></a><a name="p785103212093534"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1322711864093534"><a name="p1322711864093534"></a><a name="p1322711864093534"></a>void * </p>
<p id="p899097312093534"><a name="p899097312093534"></a><a name="p899097312093534"></a>Overrides the <strong id="b332695198093534"><a name="b332695198093534"></a><a name="b332695198093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1681139845093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422690847093534"><a name="p422690847093534"></a><a name="p422690847093534"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p551471919093534"><a name="p551471919093534"></a><a name="p551471919093534"></a>void </p>
<p id="p980507251093534"><a name="p980507251093534"></a><a name="p980507251093534"></a>Overrides the <strong id="b971240796093534"><a name="b971240796093534"></a><a name="b971240796093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table945603237093534"></a>
<table><thead align="left"><tr id="row21069473093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1384790128093534"><a name="p1384790128093534"></a><a name="p1384790128093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2006797744093534"><a name="p2006797744093534"></a><a name="p2006797744093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row144677957093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1551408116093534"><a name="p1551408116093534"></a><a name="p1551408116093534"></a><a href="graphic.md#ga34fe81b667a13b06a579600827e0531b">GetAllChildRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101922456093534"><a name="p101922456093534"></a><a name="p101922456093534"></a>Obtains the rectangle area of a new view group after being adaptive to the size of all child views. </p>
</td>
</tr>
<tr id="row519478290093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p152434416093534"><a name="p152434416093534"></a><a name="p152434416093534"></a><a href="graphic.md#ga06a5bd621f6532fe5c8fd08a2c1314b2">OnChildChanged</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p73029235093534"><a name="p73029235093534"></a><a name="p73029235093534"></a>Performs operations needed after a child view is added or removed. </p>
</td>
</tr>
<tr id="row406426010093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p334674504093534"><a name="p334674504093534"></a><a name="p334674504093534"></a><a href="graphic.md#ga82ac8a2ca47014ecb5e142e1cd7d30c1">childrenHead_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p179055698093534"><a name="p179055698093534"></a><a name="p179055698093534"></a>Indicates the pointer to the first child view of this view group. </p>
</td>
</tr>
<tr id="row1363251979093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1628316694093534"><a name="p1628316694093534"></a><a name="p1628316694093534"></a><a href="graphic.md#gaa0d6d1c8775e4765f8ae40d4573e0a83">childrenTail_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1322471690093534"><a name="p1322471690093534"></a><a name="p1322471690093534"></a>Indicates the pointer to the last child view of this view group. </p>
</td>
</tr>
<tr id="row871343407093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1446960786093534"><a name="p1446960786093534"></a><a name="p1446960786093534"></a><a href="graphic.md#gaba49c636834e80a53373dd4c3687e298">childrenNum_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1428308301093534"><a name="p1428308301093534"></a><a name="p1428308301093534"></a>Represents the number of child views. </p>
</td>
</tr>
<tr id="row1540286919093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p797144292093534"><a name="p797144292093534"></a><a name="p797144292093534"></a><a href="graphic.md#ga732108111fa141d8ad1d8a76f761307b">isDragging_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p580716849093534"><a name="p580716849093534"></a><a name="p580716849093534"></a>Specifies the sliding state of this view group. </p>
</td>
</tr>
<tr id="row1824948051093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1534200189093534"><a name="p1534200189093534"></a><a name="p1534200189093534"></a><a href="graphic.md#ga712f1c3641cb16674202fbc723af8b74">disallowIntercept_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p960265589093534"><a name="p960265589093534"></a><a name="p960265589093534"></a>Specifies whether this view group is intercepted upon touch events. </p>
</td>
</tr>
<tr id="row2023596993093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p621058328093534"><a name="p621058328093534"></a><a name="p621058328093534"></a><a href="graphic.md#ga1053e3677195fd4f98d68196d31d2cb5">isAutoSize_</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p705410901093534"><a name="p705410901093534"></a><a name="p705410901093534"></a>Specifies whether the size of this view group is adaptive to that of all child views. </p>
</td>
</tr>
</tbody>
</table>

