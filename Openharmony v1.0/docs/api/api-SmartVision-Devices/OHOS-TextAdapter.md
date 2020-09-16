# OHOS::TextAdapter<a name="ZH-CN_TOPIC_0000001054799619"></a>

## **Overview**<a name="section546493951084838"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines a text adapter, which implements  [UILabel](OHOS-UILabel.md)  instance construction and supports text data and continuous integer data. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1855908776084838"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1791602158084838"></a>
<table><thead align="left"><tr id="row1670584808084838"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p560068546084838"><a name="p560068546084838"></a><a name="p560068546084838"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p873650574084838"><a name="p873650574084838"></a><a name="p873650574084838"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1496762910084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2115329264084838"><a name="p2115329264084838"></a><a name="p2115329264084838"></a><a href="Graphic.md#ga38bde4aa4a0952341ad74284ff686832">TextAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p279661632084838"><a name="p279661632084838"></a><a name="p279661632084838"></a>&nbsp;</p>
<p id="p533559338084838"><a name="p533559338084838"></a><a name="p533559338084838"></a>A constructor used to create a <strong id="b1864818966084838"><a name="b1864818966084838"></a><a name="b1864818966084838"></a><a href="OHOS-UILabel.md">UILabel</a></strong> instance. </p>
</td>
</tr>
<tr id="row985556938084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p264967524084838"><a name="p264967524084838"></a><a name="p264967524084838"></a><a href="Graphic.md#ga1e868c845df224beff2f3c6f49593d3b">~TextAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p737433426084838"><a name="p737433426084838"></a><a name="p737433426084838"></a>virtual&nbsp;</p>
<p id="p1366588777084838"><a name="p1366588777084838"></a><a name="p1366588777084838"></a>A destructor used to delete the <strong id="b1477478829084838"><a name="b1477478829084838"></a><a name="b1477478829084838"></a><a href="OHOS-UILabel.md">UILabel</a></strong> instance. </p>
</td>
</tr>
<tr id="row1728673534084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2022285327084838"><a name="p2022285327084838"></a><a name="p2022285327084838"></a><a href="Graphic.md#ga733211ca13eccff628bb2712c27b885e">GetView</a> (<a href="OHOS-UIView.md">UIView</a> *inView, int16_t <a href="UTILS.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2001556916084838"><a name="p2001556916084838"></a><a name="p2001556916084838"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1313512064084838"><a name="p1313512064084838"></a><a name="p1313512064084838"></a>Obtains a <strong id="b903806779084838"><a name="b903806779084838"></a><a name="b903806779084838"></a><a href="OHOS-UILabel.md">UILabel</a></strong> instance to convert adapter data into another <strong id="b659805803084838"><a name="b659805803084838"></a><a name="b659805803084838"></a><a href="OHOS-UILabel.md">UILabel</a></strong> instance. </p>
</td>
</tr>
<tr id="row2004720088084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p398747851084838"><a name="p398747851084838"></a><a name="p398747851084838"></a><a href="Graphic.md#gabe6f62c7e3284e04b37451963e803a96">SetData</a> (<a href="OHOS-List-T.md">List</a>&lt; const char * &gt; *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1513872075084838"><a name="p1513872075084838"></a><a name="p1513872075084838"></a>void&nbsp;</p>
<p id="p2043193594084838"><a name="p2043193594084838"></a><a name="p2043193594084838"></a>Sets the <a href="OHOS-UILabel.md">UILabel</a> adapter data, which is a string linked list. </p>
</td>
</tr>
<tr id="row1153587586084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p7945051084838"><a name="p7945051084838"></a><a name="p7945051084838"></a><a href="Graphic.md#ga9521d17dfaf251b42deafc182aea8a1e">SetData</a> (int16_t start, int16_t end)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1455002026084838"><a name="p1455002026084838"></a><a name="p1455002026084838"></a>void&nbsp;</p>
<p id="p296409454084838"><a name="p296409454084838"></a><a name="p296409454084838"></a>Sets continuously increasing data. For example, if you need to set data <strong id="b1688346563084838"><a name="b1688346563084838"></a><a name="b1688346563084838"></a>0</strong>, <strong id="b1543811595084838"><a name="b1543811595084838"></a><a name="b1543811595084838"></a>1</strong>, <strong id="b1497363476084838"><a name="b1497363476084838"></a><a name="b1497363476084838"></a>2</strong>, <strong id="b868802323084838"><a name="b868802323084838"></a><a name="b868802323084838"></a>3</strong>, <strong id="b1405106992084838"><a name="b1405106992084838"></a><a name="b1405106992084838"></a>4</strong>, use this function to set <strong id="b1424253417084838"><a name="b1424253417084838"></a><a name="b1424253417084838"></a>start</strong> to 0 and <strong id="b1989670583084838"><a name="b1989670583084838"></a><a name="b1989670583084838"></a>end</strong> to 4. </p>
</td>
</tr>
<tr id="row1097464882084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1342457153084838"><a name="p1342457153084838"></a><a name="p1342457153084838"></a><a href="Graphic.md#gaf0ec9f4036ed071ab95081bb3237f89a">SetFontId</a> (uint8_t fontId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p964934002084838"><a name="p964934002084838"></a><a name="p964934002084838"></a>void&nbsp;</p>
<p id="p1784367755084838"><a name="p1784367755084838"></a><a name="p1784367755084838"></a>Sets font ID. </p>
</td>
</tr>
<tr id="row1516150308084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p409828436084838"><a name="p409828436084838"></a><a name="p409828436084838"></a><a href="Graphic.md#ga077ac9bece7019abc2a755031ddc5575">GetFontId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2044368022084838"><a name="p2044368022084838"></a><a name="p2044368022084838"></a>uint8_t&nbsp;</p>
<p id="p1002968624084838"><a name="p1002968624084838"></a><a name="p1002968624084838"></a>Obtains font ID. </p>
</td>
</tr>
<tr id="row220012943084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p457301433084838"><a name="p457301433084838"></a><a name="p457301433084838"></a><a href="Graphic.md#ga28d957b0aa0324e876a871eae1b80d3f">SetFont</a> (const char *name, uint8_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p634821284084838"><a name="p634821284084838"></a><a name="p634821284084838"></a>void&nbsp;</p>
<p id="p229681455084838"><a name="p229681455084838"></a><a name="p229681455084838"></a>Sets the font. </p>
</td>
</tr>
<tr id="row1199377186084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1932819136084838"><a name="p1932819136084838"></a><a name="p1932819136084838"></a><a href="Graphic.md#gacba8806f0f63a2b0436dbe4ec1b4d01c">GetStyle</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p356980379084838"><a name="p356980379084838"></a><a name="p356980379084838"></a><a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p2108865313084838"><a name="p2108865313084838"></a><a name="p2108865313084838"></a>Obtains the <a href="OHOS-UILabel.md">UILabel</a> adapter style. </p>
</td>
</tr>
<tr id="row733966503084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p740332628084838"><a name="p740332628084838"></a><a name="p740332628084838"></a><a href="Graphic.md#gaa8d1098628c391a687b08f4ccdba0a4d">GetCount</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p91160939084838"><a name="p91160939084838"></a><a name="p91160939084838"></a>virtual uint16_t&nbsp;</p>
<p id="p2136494433084838"><a name="p2136494433084838"></a><a name="p2136494433084838"></a>Obtains the <strong id="b1280274889084838"><a name="b1280274889084838"></a><a name="b1280274889084838"></a>data</strong> size of the <a href="OHOS-UILabel.md">UILabel</a> adapter. </p>
</td>
</tr>
<tr id="row1816111946084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1822225199084838"><a name="p1822225199084838"></a><a name="p1822225199084838"></a><a href="Graphic.md#gaed7f27b1dbf4f50ae8eda00cc6cb6a27">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2071104545084838"><a name="p2071104545084838"></a><a name="p2071104545084838"></a>void&nbsp;</p>
<p id="p547314687084838"><a name="p547314687084838"></a><a name="p547314687084838"></a>Sets the width of <a href="OHOS-UILabel.md">UILabel</a> constructed by the adapter. </p>
</td>
</tr>
<tr id="row1636930279084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1280949001084838"><a name="p1280949001084838"></a><a name="p1280949001084838"></a><a href="Graphic.md#ga618021df16f2156ddeeb12d5a8fa14f9">SetDirect</a> (<a href="Graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a> direct)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p807390559084838"><a name="p807390559084838"></a><a name="p807390559084838"></a>void&nbsp;</p>
<p id="p1026847338084838"><a name="p1026847338084838"></a><a name="p1026847338084838"></a>Sets the direction of the <a href="OHOS-UILabel.md">UILabel</a> constructed by the adapter. </p>
</td>
</tr>
<tr id="row670793012084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1073682766084838"><a name="p1073682766084838"></a><a name="p1073682766084838"></a><a href="Graphic.md#ga2c83259c064091d74deac1e4a69f834c">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1190652378084838"><a name="p1190652378084838"></a><a name="p1190652378084838"></a>void&nbsp;</p>
<p id="p1315022291084838"><a name="p1315022291084838"></a><a name="p1315022291084838"></a>Sets the height of the <a href="OHOS-UILabel.md">UILabel</a> constructed by the adapter. </p>
</td>
</tr>
<tr id="row860932558084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p317650144084838"><a name="p317650144084838"></a><a name="p317650144084838"></a><a href="Graphic.md#gafc5f3b2c909753f4a7ef53daa80b530b">SetLineBreakMode</a> (const uint8_t lineBreakMode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1239942840084838"><a name="p1239942840084838"></a><a name="p1239942840084838"></a>void&nbsp;</p>
<p id="p469089640084838"><a name="p469089640084838"></a><a name="p469089640084838"></a>Sets the <strong id="b273737410084838"><a name="b273737410084838"></a><a name="b273737410084838"></a>LineBreakMode</strong> attribute of <a href="OHOS-UILabel.md">UILabel</a> constructed by the adapter. For details about the values of <strong id="b1120431409084838"><a name="b1120431409084838"></a><a name="b1120431409084838"></a>LineBreakMode</strong>, see <strong id="b1646172844084838"><a name="b1646172844084838"></a><a name="b1646172844084838"></a>LINE_BREAK_ADAPT</strong>, <strong id="b404900143084838"><a name="b404900143084838"></a><a name="b404900143084838"></a>LINE_BREAK_WRAP</strong>, <strong id="b673326054084838"><a name="b673326054084838"></a><a name="b673326054084838"></a>LINE_BREAK_ELLIPSIS</strong>, and <strong id="b1713023868084838"><a name="b1713023868084838"></a><a name="b1713023868084838"></a>LINE_BREAK_MARQUEE</strong>. </p>
</td>
</tr>
<tr id="row598655452084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1000558598084838"><a name="p1000558598084838"></a><a name="p1000558598084838"></a><a href="Graphic.md#ga9aa8cecae666906c7fa3d292d6c1c842">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">UIView::OnClickListener</a> *clickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p136729102084838"><a name="p136729102084838"></a><a name="p136729102084838"></a>void&nbsp;</p>
<p id="p1170389950084838"><a name="p1170389950084838"></a><a name="p1170389950084838"></a>Sets the callback function to be invoked upon a click event. </p>
</td>
</tr>
<tr id="row1383757522084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p469000950084838"><a name="p469000950084838"></a><a name="p469000950084838"></a><a href="Graphic.md#gadad75361a42fd390b5f9c5edad2f2f0b">SetTextFormatter</a> (<a href="OHOS-TextFormatter.md">TextFormatter</a> *formatter)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1722943691084838"><a name="p1722943691084838"></a><a name="p1722943691084838"></a>void&nbsp;</p>
<p id="p675548975084838"><a name="p675548975084838"></a><a name="p675548975084838"></a>Sets the text formatter. </p>
</td>
</tr>
<tr id="row1651809235084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p994588086084838"><a name="p994588086084838"></a><a name="p994588086084838"></a><a href="Graphic.md#gab60e1c77fb98352bd62e56b550d75d88">AbstractAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1293018890084838"><a name="p1293018890084838"></a><a name="p1293018890084838"></a>&nbsp;</p>
<p id="p1538363430084838"><a name="p1538363430084838"></a><a name="p1538363430084838"></a>A constructor used to create an <strong id="b436487458084838"><a name="b436487458084838"></a><a name="b436487458084838"></a><a href="OHOS-AbstractAdapter.md">AbstractAdapter</a></strong> instance. </p>
</td>
</tr>
<tr id="row136537338084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1667916387084838"><a name="p1667916387084838"></a><a name="p1667916387084838"></a><a href="Graphic.md#ga86fbbc62904d459ec4fa39bab7703af7">~AbstractAdapter</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1573683011084838"><a name="p1573683011084838"></a><a name="p1573683011084838"></a>virtual&nbsp;</p>
<p id="p1839061885084838"><a name="p1839061885084838"></a><a name="p1839061885084838"></a>A destructor used to delete the <strong id="b346197667084838"><a name="b346197667084838"></a><a name="b346197667084838"></a><a href="OHOS-AbstractAdapter.md">AbstractAdapter</a></strong> instance. </p>
</td>
</tr>
<tr id="row1200019004084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1870233647084838"><a name="p1870233647084838"></a><a name="p1870233647084838"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p989838731084838"><a name="p989838731084838"></a><a name="p989838731084838"></a>void *&nbsp;</p>
<p id="p644666314084838"><a name="p644666314084838"></a><a name="p644666314084838"></a>Overrides the <strong id="b33957851084838"><a name="b33957851084838"></a><a name="b33957851084838"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1854921966084838"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p14248898084838"><a name="p14248898084838"></a><a name="p14248898084838"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p907519838084838"><a name="p907519838084838"></a><a name="p907519838084838"></a>void&nbsp;</p>
<p id="p77862512084838"><a name="p77862512084838"></a><a name="p77862512084838"></a>Overrides the <strong id="b1496153482084838"><a name="b1496153482084838"></a><a name="b1496153482084838"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

