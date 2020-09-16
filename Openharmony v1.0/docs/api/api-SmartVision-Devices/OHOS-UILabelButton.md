# OHOS::UILabelButton<a name="ZH-CN_TOPIC_0000001055678118"></a>

## **Overview**<a name="section1758447527093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Provides the functions related to a label button. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section623570385093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1095133272093534"></a>
<table><thead align="left"><tr id="row1181741335093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2004560080093534"><a name="p2004560080093534"></a><a name="p2004560080093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p602303463093534"><a name="p602303463093534"></a><a name="p602303463093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1092963059093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1938612819093534"><a name="p1938612819093534"></a><a name="p1938612819093534"></a><a href="Graphic.md#gadf3e53072501ed36700dea74a3ddbd8f">UILabelButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1273736379093534"><a name="p1273736379093534"></a><a name="p1273736379093534"></a>&nbsp;</p>
<p id="p540915582093534"><a name="p540915582093534"></a><a name="p540915582093534"></a>A constructor used to create a <strong id="b1806258922093534"><a name="b1806258922093534"></a><a name="b1806258922093534"></a><a href="OHOS-UILabelButton.md">UILabelButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row1630554460093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1914502762093534"><a name="p1914502762093534"></a><a name="p1914502762093534"></a><a href="Graphic.md#ga9c585e4c556a62f44c71d538608544ee">~UILabelButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p739715461093534"><a name="p739715461093534"></a><a name="p739715461093534"></a>virtual&nbsp;</p>
<p id="p941354624093534"><a name="p941354624093534"></a><a name="p941354624093534"></a>A destructor used to delete the <strong id="b812601680093534"><a name="b812601680093534"></a><a name="b812601680093534"></a><a href="OHOS-UILabelButton.md">UILabelButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row315726941093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p828603816093534"><a name="p828603816093534"></a><a name="p828603816093534"></a><a href="Graphic.md#ga159c536c3f826165c26fdabdc87f498a">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p49353865093534"><a name="p49353865093534"></a><a name="p49353865093534"></a>void&nbsp;</p>
<p id="p379753084093534"><a name="p379753084093534"></a><a name="p379753084093534"></a>Draws a label button. </p>
</td>
</tr>
<tr id="row827107252093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p952673072093534"><a name="p952673072093534"></a><a name="p952673072093534"></a><a href="Graphic.md#ga7064f161dbf0e539bd089db62339cad8">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1659646745093534"><a name="p1659646745093534"></a><a name="p1659646745093534"></a>UIViewType&nbsp;</p>
<p id="p775159779093534"><a name="p775159779093534"></a><a name="p775159779093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row873884222093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1838180595093534"><a name="p1838180595093534"></a><a name="p1838180595093534"></a><a href="Graphic.md#ga6b5b491c9240a061fc21cf6b98bdaefc">SetText</a> (const char *text)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1480843668093534"><a name="p1480843668093534"></a><a name="p1480843668093534"></a>void&nbsp;</p>
<p id="p734902905093534"><a name="p734902905093534"></a><a name="p734902905093534"></a>Sets the text for this label button. </p>
</td>
</tr>
<tr id="row1795336740093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1636068958093534"><a name="p1636068958093534"></a><a name="p1636068958093534"></a><a href="Graphic.md#ga8d04dd052b36017d89e52be905b50d62">GetText</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p425503759093534"><a name="p425503759093534"></a><a name="p425503759093534"></a>const char *&nbsp;</p>
<p id="p710738113093534"><a name="p710738113093534"></a><a name="p710738113093534"></a>Obtains the text of this label button. </p>
</td>
</tr>
<tr id="row1850860559093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1158728173093534"><a name="p1158728173093534"></a><a name="p1158728173093534"></a><a href="Graphic.md#gaf97dc0d36701691a001ef3fd9e6e8b4f">SetLablePosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p359202395093534"><a name="p359202395093534"></a><a name="p359202395093534"></a>void&nbsp;</p>
<p id="p2101709154093534"><a name="p2101709154093534"></a><a name="p2101709154093534"></a>Sets the position for this label relative to the button holding it. </p>
</td>
</tr>
<tr id="row650445712093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p827628406093534"><a name="p827628406093534"></a><a name="p827628406093534"></a><a href="Graphic.md#gaf98616000ecd2cbb458d59fa77b7fe60">GetLabelPosition</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2036307593093534"><a name="p2036307593093534"></a><a name="p2036307593093534"></a><a href="OHOS-Point.md">Point</a>&nbsp;</p>
<p id="p2049049702093534"><a name="p2049049702093534"></a><a name="p2049049702093534"></a>Obtains the position of this label relative to the button holding it. </p>
</td>
</tr>
<tr id="row1537015534093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p802393294093534"><a name="p802393294093534"></a><a name="p802393294093534"></a><a href="Graphic.md#gab5625481e1a9cb77f30102c76ec76bdd">SetAlign</a> (<a href="Graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> align)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1994489538093534"><a name="p1994489538093534"></a><a name="p1994489538093534"></a>void&nbsp;</p>
<p id="p1076076043093534"><a name="p1076076043093534"></a><a name="p1076076043093534"></a>Sets the alignment mode for this text. </p>
</td>
</tr>
<tr id="row1101339321093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1448090602093534"><a name="p1448090602093534"></a><a name="p1448090602093534"></a><a href="Graphic.md#ga94001af31d34b575be3678f06b77f432">GetAlign</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p714466191093534"><a name="p714466191093534"></a><a name="p714466191093534"></a><a href="Graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a>&nbsp;</p>
<p id="p1706544472093534"><a name="p1706544472093534"></a><a name="p1706544472093534"></a>Obtains the alignment mode of this text. </p>
</td>
</tr>
<tr id="row1620003656093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p93759134093534"><a name="p93759134093534"></a><a name="p93759134093534"></a><a href="Graphic.md#gabdea4ed71d6a22492ff423339cc08d5e">SetDirect</a> (<a href="Graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a> direct)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p562105907093534"><a name="p562105907093534"></a><a name="p562105907093534"></a>void&nbsp;</p>
<p id="p894286041093534"><a name="p894286041093534"></a><a name="p894286041093534"></a>Sets the direction for this text. </p>
</td>
</tr>
<tr id="row2044986427093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1659998718093534"><a name="p1659998718093534"></a><a name="p1659998718093534"></a><a href="Graphic.md#gac39c029ba83cc256fded96108e299ff5">GetDirect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p67690595093534"><a name="p67690595093534"></a><a name="p67690595093534"></a><a href="Graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a>&nbsp;</p>
<p id="p1393327226093534"><a name="p1393327226093534"></a><a name="p1393327226093534"></a>Obtains the direction of this text. </p>
</td>
</tr>
<tr id="row1074461208093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1154109921093534"><a name="p1154109921093534"></a><a name="p1154109921093534"></a><a href="Graphic.md#ga66e316e344c0165a6fd3c5083ea523f4">SetLabelStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;labelStyle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266984988093534"><a name="p1266984988093534"></a><a name="p1266984988093534"></a>void&nbsp;</p>
<p id="p1697906237093534"><a name="p1697906237093534"></a><a name="p1697906237093534"></a>Sets the style for this label. </p>
</td>
</tr>
<tr id="row1496911078093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1351288668093534"><a name="p1351288668093534"></a><a name="p1351288668093534"></a><a href="Graphic.md#gad1d6be2a8aec65bef4c1f598bfde7666">SetLabelStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p618852930093534"><a name="p618852930093534"></a><a name="p618852930093534"></a>void&nbsp;</p>
<p id="p576699272093534"><a name="p576699272093534"></a><a name="p576699272093534"></a>Sets a style for this label. </p>
</td>
</tr>
<tr id="row1306164096093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1688739676093534"><a name="p1688739676093534"></a><a name="p1688739676093534"></a><a href="Graphic.md#gaefaa6ceaa04329594f1539d48fa121f2">GetLabelStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p485577951093534"><a name="p485577951093534"></a><a name="p485577951093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1313697078093534"><a name="p1313697078093534"></a><a name="p1313697078093534"></a>Obtains the style of this label. </p>
</td>
</tr>
<tr id="row911450843093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p587582352093534"><a name="p587582352093534"></a><a name="p587582352093534"></a><a href="Graphic.md#ga21c71c654974ddb388a1890576966524">GetLabelStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1253677386093534"><a name="p1253677386093534"></a><a name="p1253677386093534"></a>int64_t&nbsp;</p>
<p id="p1512191615093534"><a name="p1512191615093534"></a><a name="p1512191615093534"></a>Obtains the value of a style of this label. </p>
</td>
</tr>
<tr id="row1014690004093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1672628186093534"><a name="p1672628186093534"></a><a name="p1672628186093534"></a><a href="Graphic.md#ga55592f14dc16b1e1ae3fc9ab7ee9a976">SetTextColor</a> (<a href="OHOS-Color32.md">ColorType</a> color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p504139239093534"><a name="p504139239093534"></a><a name="p504139239093534"></a>void&nbsp;</p>
<p id="p1080593334093534"><a name="p1080593334093534"></a><a name="p1080593334093534"></a>Sets the color for this text. </p>
</td>
</tr>
<tr id="row1124948919093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1733726014093534"><a name="p1733726014093534"></a><a name="p1733726014093534"></a><a href="Graphic.md#gad84d1829e94b7ec45ab6576bc14c62d0">SetFont</a> (const char *name, uint8_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1862241284093534"><a name="p1862241284093534"></a><a name="p1862241284093534"></a>void&nbsp;</p>
<p id="p116602029093534"><a name="p116602029093534"></a><a name="p116602029093534"></a>Sets the font for this text. </p>
</td>
</tr>
<tr id="row476958066093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p658180963093534"><a name="p658180963093534"></a><a name="p658180963093534"></a><a href="Graphic.md#ga89cde9550d1bd443dad10d11c5c2fbfc">SetFontId</a> (uint8_t fontId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1941675320093534"><a name="p1941675320093534"></a><a name="p1941675320093534"></a>void&nbsp;</p>
<p id="p718737122093534"><a name="p718737122093534"></a><a name="p718737122093534"></a>Sets the font ID. </p>
</td>
</tr>
<tr id="row1895130460093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1536480430093534"><a name="p1536480430093534"></a><a name="p1536480430093534"></a><a href="Graphic.md#ga826c13b3721c17ea43a7ca386a03253c">GetFontId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p805226111093534"><a name="p805226111093534"></a><a name="p805226111093534"></a>uint8_t&nbsp;</p>
<p id="p1787930660093534"><a name="p1787930660093534"></a><a name="p1787930660093534"></a>Obtains the font ID. </p>
</td>
</tr>
<tr id="row576860605093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1229867130093534"><a name="p1229867130093534"></a><a name="p1229867130093534"></a><a href="Graphic.md#ga3aee093d4c583223850a7ad80d5bed79">UIButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p581006265093534"><a name="p581006265093534"></a><a name="p581006265093534"></a>&nbsp;</p>
<p id="p2023615668093534"><a name="p2023615668093534"></a><a name="p2023615668093534"></a>A constructor used to create a <strong id="b506459940093534"><a name="b506459940093534"></a><a name="b506459940093534"></a><a href="OHOS-UIButton.md">UIButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row1589640470093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p877775394093534"><a name="p877775394093534"></a><a name="p877775394093534"></a><a href="Graphic.md#ga33e30931e9b3557634b2b2be93bc41f6">UIButton</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2057249730093534"><a name="p2057249730093534"></a><a name="p2057249730093534"></a>&nbsp;</p>
<p id="p319070400093534"><a name="p319070400093534"></a><a name="p319070400093534"></a>A constructor used to create a <strong id="b312735995093534"><a name="b312735995093534"></a><a name="b312735995093534"></a><a href="OHOS-UIButton.md">UIButton</a></strong> instance based on the button ID. </p>
</td>
</tr>
<tr id="row2102129424093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1847774818093534"><a name="p1847774818093534"></a><a name="p1847774818093534"></a><a href="Graphic.md#ga0c5fbcf319fc6df8170d407a337b9d8b">~UIButton</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1004978330093534"><a name="p1004978330093534"></a><a name="p1004978330093534"></a>virtual&nbsp;</p>
<p id="p1514454857093534"><a name="p1514454857093534"></a><a name="p1514454857093534"></a>A destructor used to delete the <strong id="b2040973906093534"><a name="b2040973906093534"></a><a name="b2040973906093534"></a><a href="OHOS-UIButton.md">UIButton</a></strong> instance. </p>
</td>
</tr>
<tr id="row1187901293093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p872411352093534"><a name="p872411352093534"></a><a name="p872411352093534"></a><a href="Graphic.md#gaf64d9ec1744ab9c7385dd64d30a786e4">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p778417227093534"><a name="p778417227093534"></a><a name="p778417227093534"></a>bool&nbsp;</p>
<p id="p442907636093534"><a name="p442907636093534"></a><a name="p442907636093534"></a>Do something before draw, this function will be invoked mainly to check if this view need to cover invalidate area so render manager can decide which layer to draw firstly. </p>
</td>
</tr>
<tr id="row649012525093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p842198767093534"><a name="p842198767093534"></a><a name="p842198767093534"></a><a href="Graphic.md#ga1d887720c89170abd3c8a400a791765d">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p701422968093534"><a name="p701422968093534"></a><a name="p701422968093534"></a>void&nbsp;</p>
<p id="p1573137970093534"><a name="p1573137970093534"></a><a name="p1573137970093534"></a>Executes the press event action. </p>
</td>
</tr>
<tr id="row1642586806093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1730160669093534"><a name="p1730160669093534"></a><a name="p1730160669093534"></a><a href="Graphic.md#gadb9492eb82ff23f91f9263fc748f24de">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999900151093534"><a name="p1999900151093534"></a><a name="p1999900151093534"></a>void&nbsp;</p>
<p id="p206921107093534"><a name="p206921107093534"></a><a name="p206921107093534"></a>Executes the press release event action. </p>
</td>
</tr>
<tr id="row137205080093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1527820400093534"><a name="p1527820400093534"></a><a name="p1527820400093534"></a><a href="Graphic.md#ga4f481e0ce91f87c6b70f6e0190e4f34f">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p951177555093534"><a name="p951177555093534"></a><a name="p951177555093534"></a>void&nbsp;</p>
<p id="p1765015330093534"><a name="p1765015330093534"></a><a name="p1765015330093534"></a>Executes the cancel event action. </p>
</td>
</tr>
<tr id="row694334439093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p870745155093534"><a name="p870745155093534"></a><a name="p870745155093534"></a><a href="Graphic.md#ga60194db1c1bba6a0ef963bdbbe9f972f">SetImageSrc</a> (const char *defaultImgSrc, const char *triggeredImgSrc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1793704112093534"><a name="p1793704112093534"></a><a name="p1793704112093534"></a>void&nbsp;</p>
<p id="p1654242116093534"><a name="p1654242116093534"></a><a name="p1654242116093534"></a>Sets the image for this button. </p>
</td>
</tr>
<tr id="row2009076240093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1678905861093534"><a name="p1678905861093534"></a><a name="p1678905861093534"></a><a href="Graphic.md#gab751bc5941edb403022d65d2c605a241">SetImageSrc</a> (const <a href="OHOS-ImageInfo.md">ImageInfo</a> *defaultImgSrc, const <a href="OHOS-ImageInfo.md">ImageInfo</a> *triggeredImgSrc)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1972003203093534"><a name="p1972003203093534"></a><a name="p1972003203093534"></a>void&nbsp;</p>
<p id="p917410379093534"><a name="p917410379093534"></a><a name="p917410379093534"></a>Sets the image for this button. </p>
</td>
</tr>
<tr id="row1384829647093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p684800370093534"><a name="p684800370093534"></a><a name="p684800370093534"></a><a href="Graphic.md#ga952fcbc88905cf35ec3e09bdf01375f2">SetImagePosition</a> (const int16_t x, const int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p685639086093534"><a name="p685639086093534"></a><a name="p685639086093534"></a>void&nbsp;</p>
<p id="p1247402958093534"><a name="p1247402958093534"></a><a name="p1247402958093534"></a>Sets the position for this image. </p>
</td>
</tr>
<tr id="row1506196809093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1823485523093534"><a name="p1823485523093534"></a><a name="p1823485523093534"></a><a href="Graphic.md#ga4d8abf189ddcbf325c60402084d7e3c3">GetImageX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p923983315093534"><a name="p923983315093534"></a><a name="p923983315093534"></a>int16_t&nbsp;</p>
<p id="p357247976093534"><a name="p357247976093534"></a><a name="p357247976093534"></a>Obtains the x-coordinate of this image. </p>
</td>
</tr>
<tr id="row679809191093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p215542178093534"><a name="p215542178093534"></a><a name="p215542178093534"></a><a href="Graphic.md#ga25a02afb52cc15212084fb6bc8f27afd">GetImageY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1863137496093534"><a name="p1863137496093534"></a><a name="p1863137496093534"></a>int16_t&nbsp;</p>
<p id="p70138636093534"><a name="p70138636093534"></a><a name="p70138636093534"></a>Obtains the y-coordinate of this image. </p>
</td>
</tr>
<tr id="row1882160025093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1489563397093534"><a name="p1489563397093534"></a><a name="p1489563397093534"></a><a href="Graphic.md#gaf6496e4858473ab2acb80a2be6264a01">GetCurImageSrc</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p156943333093534"><a name="p156943333093534"></a><a name="p156943333093534"></a>const <a href="OHOS-Image.md">Image</a> *&nbsp;</p>
<p id="p308758401093534"><a name="p308758401093534"></a><a name="p308758401093534"></a>Obtains the image for the current button state. </p>
</td>
</tr>
<tr id="row1781893212093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1044591666093534"><a name="p1044591666093534"></a><a name="p1044591666093534"></a><a href="Graphic.md#ga8cb74b23f740091e59ad350a8dea436b">GetWidth</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p422198754093534"><a name="p422198754093534"></a><a name="p422198754093534"></a>int16_t&nbsp;</p>
<p id="p1011877154093534"><a name="p1011877154093534"></a><a name="p1011877154093534"></a>Obtains the width of this image. </p>
</td>
</tr>
<tr id="row1277802124093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p985691754093534"><a name="p985691754093534"></a><a name="p985691754093534"></a><a href="Graphic.md#ga1f8015706cfc73728696bf2bbd3e833b">GetHeight</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p809221678093534"><a name="p809221678093534"></a><a name="p809221678093534"></a>int16_t&nbsp;</p>
<p id="p1737570471093534"><a name="p1737570471093534"></a><a name="p1737570471093534"></a>Obtains the height of this image. </p>
</td>
</tr>
<tr id="row1866182195093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1219796002093534"><a name="p1219796002093534"></a><a name="p1219796002093534"></a><a href="Graphic.md#ga420f927c473cec8c6f3265ff7c35336f">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1437695436093534"><a name="p1437695436093534"></a><a name="p1437695436093534"></a>void&nbsp;</p>
<p id="p1638005337093534"><a name="p1638005337093534"></a><a name="p1638005337093534"></a>Sets the width for this image. </p>
</td>
</tr>
<tr id="row750429847093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p397994574093534"><a name="p397994574093534"></a><a name="p397994574093534"></a><a href="Graphic.md#ga8b6dbfcd0328753c2c3cef4d14b0ff30">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p182451304093534"><a name="p182451304093534"></a><a name="p182451304093534"></a>void&nbsp;</p>
<p id="p1465481075093534"><a name="p1465481075093534"></a><a name="p1465481075093534"></a>Sets the height for this image. </p>
</td>
</tr>
<tr id="row1947171158093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p486154088093534"><a name="p486154088093534"></a><a name="p486154088093534"></a><a href="Graphic.md#ga93994f4d735e4f9a7d3e7d737e2c620c">GetContentRect</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1523908368093534"><a name="p1523908368093534"></a><a name="p1523908368093534"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p482468715093534"><a name="p482468715093534"></a><a name="p482468715093534"></a>Obtains a rectangular area that contains coordinate information. </p>
</td>
</tr>
<tr id="row1489892200093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p883147409093534"><a name="p883147409093534"></a><a name="p883147409093534"></a><a href="Graphic.md#ga37736a82bec6a01bc5a880e1d01ccccd">GetStyle</a> (uint8_t key) const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1325438040093534"><a name="p1325438040093534"></a><a name="p1325438040093534"></a>int64_t&nbsp;</p>
<p id="p294998740093534"><a name="p294998740093534"></a><a name="p294998740093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row51434406093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p836712599093534"><a name="p836712599093534"></a><a name="p836712599093534"></a><a href="Graphic.md#gaa5fdd9b28b8c919dbde0e34d8ae38caf">SetStyle</a> (uint8_t key, int64_t value) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1759442666093534"><a name="p1759442666093534"></a><a name="p1759442666093534"></a>void&nbsp;</p>
<p id="p2028826451093534"><a name="p2028826451093534"></a><a name="p2028826451093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1143547506093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1413500321093534"><a name="p1413500321093534"></a><a name="p1413500321093534"></a><a href="Graphic.md#gaa3f74af93c91a24e58fdd06ad7d0bdf9">GetStyleForState</a> (uint8_t key, <a href="Graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> state) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1884508303093534"><a name="p1884508303093534"></a><a name="p1884508303093534"></a>int64_t&nbsp;</p>
<p id="p1703662730093534"><a name="p1703662730093534"></a><a name="p1703662730093534"></a>Obtains the style of a button in a specific state. </p>
</td>
</tr>
<tr id="row1457376915093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p356019855093534"><a name="p356019855093534"></a><a name="p356019855093534"></a><a href="Graphic.md#ga7ece04980fa99a277bfbb591771f47f1">SetStyleForState</a> (uint8_t key, int64_t value, <a href="Graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038080832093534"><a name="p1038080832093534"></a><a name="p1038080832093534"></a>void&nbsp;</p>
<p id="p682701308093534"><a name="p682701308093534"></a><a name="p682701308093534"></a>Sets the style for a button in a specific state. </p>
</td>
</tr>
<tr id="row1070435981093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858453676093534"><a name="p858453676093534"></a><a name="p858453676093534"></a><a href="Graphic.md#ga283131701e907e586964189818d04411">Disable</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1443834479093534"><a name="p1443834479093534"></a><a name="p1443834479093534"></a>void&nbsp;</p>
<p id="p1651447631093534"><a name="p1651447631093534"></a><a name="p1651447631093534"></a>Disables this button. </p>
</td>
</tr>
<tr id="row180311756093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2038114416093534"><a name="p2038114416093534"></a><a name="p2038114416093534"></a><a href="Graphic.md#ga3185df8b60a609564f978ed9576fb813">Enable</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p124103931093534"><a name="p124103931093534"></a><a name="p124103931093534"></a>void&nbsp;</p>
<p id="p1394730006093534"><a name="p1394730006093534"></a><a name="p1394730006093534"></a>Enables this button. </p>
</td>
</tr>
<tr id="row1588286776093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p374222191093534"><a name="p374222191093534"></a><a name="p374222191093534"></a><a href="Graphic.md#ga737d850b2adf8a2977369e611764b1ae">SetStateForStyle</a> (<a href="Graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p221054524093534"><a name="p221054524093534"></a><a name="p221054524093534"></a>void&nbsp;</p>
<p id="p1846738694093534"><a name="p1846738694093534"></a><a name="p1846738694093534"></a>Sets the state for a button. After the setting, calling <a href="Graphic.md#gaa5fdd9b28b8c919dbde0e34d8ae38caf">SetStyle</a> will change the style of this button, but not its state. </p>
</td>
</tr>
<tr id="row2104527173093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p473010396093534"><a name="p473010396093534"></a><a name="p473010396093534"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p82292331093534"><a name="p82292331093534"></a><a name="p82292331093534"></a>&nbsp;</p>
<p id="p1335307772093534"><a name="p1335307772093534"></a><a name="p1335307772093534"></a>A default constructor used to create an <strong id="b1835215999093534"><a name="b1835215999093534"></a><a name="b1835215999093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row503272140093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451295047093534"><a name="p451295047093534"></a><a name="p451295047093534"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p240415660093534"><a name="p240415660093534"></a><a name="p240415660093534"></a>&nbsp;</p>
<p id="p1200429228093534"><a name="p1200429228093534"></a><a name="p1200429228093534"></a>A constructor used to create an <strong id="b511176705093534"><a name="b511176705093534"></a><a name="b511176705093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row18551936093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390702514093534"><a name="p390702514093534"></a><a name="p390702514093534"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2056481794093534"><a name="p2056481794093534"></a><a name="p2056481794093534"></a>virtual&nbsp;</p>
<p id="p1885602941093534"><a name="p1885602941093534"></a><a name="p1885602941093534"></a>A destructor used to delete the <strong id="b946913918093534"><a name="b946913918093534"></a><a name="b946913918093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row373727412093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2077490978093534"><a name="p2077490978093534"></a><a name="p2077490978093534"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p382122042093534"><a name="p382122042093534"></a><a name="p382122042093534"></a>virtual void&nbsp;</p>
<p id="p162973982093534"><a name="p162973982093534"></a><a name="p162973982093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row269456287093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1102705487093534"><a name="p1102705487093534"></a><a name="p1102705487093534"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p71793201093534"><a name="p71793201093534"></a><a name="p71793201093534"></a>virtual void&nbsp;</p>
<p id="p1849939605093534"><a name="p1849939605093534"></a><a name="p1849939605093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1060772527093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p20849273093534"><a name="p20849273093534"></a><a name="p20849273093534"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p153359409093534"><a name="p153359409093534"></a><a name="p153359409093534"></a>void&nbsp;</p>
<p id="p1976080583093534"><a name="p1976080583093534"></a><a name="p1976080583093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1697996262093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2088030021093534"><a name="p2088030021093534"></a><a name="p2088030021093534"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1247372447093534"><a name="p1247372447093534"></a><a name="p1247372447093534"></a>void&nbsp;</p>
<p id="p260728916093534"><a name="p260728916093534"></a><a name="p260728916093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row17844946093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1888587375093534"><a name="p1888587375093534"></a><a name="p1888587375093534"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1625173011093534"><a name="p1625173011093534"></a><a name="p1625173011093534"></a>virtual bool&nbsp;</p>
<p id="p1025140850093534"><a name="p1025140850093534"></a><a name="p1025140850093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1128845284093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858163933093534"><a name="p858163933093534"></a><a name="p858163933093534"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p755877546093534"><a name="p755877546093534"></a><a name="p755877546093534"></a>virtual bool&nbsp;</p>
<p id="p940743858093534"><a name="p940743858093534"></a><a name="p940743858093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row123522874093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969533349093534"><a name="p1969533349093534"></a><a name="p1969533349093534"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1991737812093534"><a name="p1991737812093534"></a><a name="p1991737812093534"></a>virtual bool&nbsp;</p>
<p id="p1710125532093534"><a name="p1710125532093534"></a><a name="p1710125532093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row891019110093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p892893789093534"><a name="p892893789093534"></a><a name="p892893789093534"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p774989691093534"><a name="p774989691093534"></a><a name="p774989691093534"></a>virtual bool&nbsp;</p>
<p id="p1763561601093534"><a name="p1763561601093534"></a><a name="p1763561601093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row633163974093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1556899282093534"><a name="p1556899282093534"></a><a name="p1556899282093534"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1243834324093534"><a name="p1243834324093534"></a><a name="p1243834324093534"></a>virtual void&nbsp;</p>
<p id="p436024868093534"><a name="p436024868093534"></a><a name="p436024868093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row921555343093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1221438039093534"><a name="p1221438039093534"></a><a name="p1221438039093534"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p174461586093534"><a name="p174461586093534"></a><a name="p174461586093534"></a>void&nbsp;</p>
<p id="p1241127483093534"><a name="p1241127483093534"></a><a name="p1241127483093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1857093312093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1214075320093534"><a name="p1214075320093534"></a><a name="p1214075320093534"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1545517356093534"><a name="p1545517356093534"></a><a name="p1545517356093534"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p876966745093534"><a name="p876966745093534"></a><a name="p876966745093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1838064045093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p206476671093534"><a name="p206476671093534"></a><a name="p206476671093534"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999878950093534"><a name="p1999878950093534"></a><a name="p1999878950093534"></a>void&nbsp;</p>
<p id="p250897908093534"><a name="p250897908093534"></a><a name="p250897908093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row892687668093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p481459111093534"><a name="p481459111093534"></a><a name="p481459111093534"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1427982141093534"><a name="p1427982141093534"></a><a name="p1427982141093534"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p1966350945093534"><a name="p1966350945093534"></a><a name="p1966350945093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row376634244093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p203071430093534"><a name="p203071430093534"></a><a name="p203071430093534"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181602103093534"><a name="p181602103093534"></a><a name="p181602103093534"></a>void&nbsp;</p>
<p id="p355523596093534"><a name="p355523596093534"></a><a name="p355523596093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row645578607093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1965716686093534"><a name="p1965716686093534"></a><a name="p1965716686093534"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p961598185093534"><a name="p961598185093534"></a><a name="p961598185093534"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p684807950093534"><a name="p684807950093534"></a><a name="p684807950093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1434523897093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1303741360093534"><a name="p1303741360093534"></a><a name="p1303741360093534"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1569464683093534"><a name="p1569464683093534"></a><a name="p1569464683093534"></a>void&nbsp;</p>
<p id="p871268230093534"><a name="p871268230093534"></a><a name="p871268230093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1811191481093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p842258945093534"><a name="p842258945093534"></a><a name="p842258945093534"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p167794618093534"><a name="p167794618093534"></a><a name="p167794618093534"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p428686305093534"><a name="p428686305093534"></a><a name="p428686305093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row950093746093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1412169226093534"><a name="p1412169226093534"></a><a name="p1412169226093534"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1632586451093534"><a name="p1632586451093534"></a><a name="p1632586451093534"></a>virtual void&nbsp;</p>
<p id="p882120960093534"><a name="p882120960093534"></a><a name="p882120960093534"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row1047050821093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1195126972093534"><a name="p1195126972093534"></a><a name="p1195126972093534"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p870110973093534"><a name="p870110973093534"></a><a name="p870110973093534"></a>void&nbsp;</p>
<p id="p711524278093534"><a name="p711524278093534"></a><a name="p711524278093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row597269017093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645701912093534"><a name="p645701912093534"></a><a name="p645701912093534"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p419525040093534"><a name="p419525040093534"></a><a name="p419525040093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p472882428093534"><a name="p472882428093534"></a><a name="p472882428093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row553659102093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1083933867093534"><a name="p1083933867093534"></a><a name="p1083933867093534"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1986298344093534"><a name="p1986298344093534"></a><a name="p1986298344093534"></a>void&nbsp;</p>
<p id="p643013452093534"><a name="p643013452093534"></a><a name="p643013452093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1561122538093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p647029919093534"><a name="p647029919093534"></a><a name="p647029919093534"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1561534581093534"><a name="p1561534581093534"></a><a name="p1561534581093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1787879591093534"><a name="p1787879591093534"></a><a name="p1787879591093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row135392921093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1749870381093534"><a name="p1749870381093534"></a><a name="p1749870381093534"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1997706521093534"><a name="p1997706521093534"></a><a name="p1997706521093534"></a>virtual void&nbsp;</p>
<p id="p1291795246093534"><a name="p1291795246093534"></a><a name="p1291795246093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1596150180093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p335059638093534"><a name="p335059638093534"></a><a name="p335059638093534"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1785144654093534"><a name="p1785144654093534"></a><a name="p1785144654093534"></a>bool&nbsp;</p>
<p id="p1148980136093534"><a name="p1148980136093534"></a><a name="p1148980136093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1578508131093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p200025563093534"><a name="p200025563093534"></a><a name="p200025563093534"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p535346876093534"><a name="p535346876093534"></a><a name="p535346876093534"></a>void&nbsp;</p>
<p id="p742703180093534"><a name="p742703180093534"></a><a name="p742703180093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row670669317093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p934863842093534"><a name="p934863842093534"></a><a name="p934863842093534"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2069161025093534"><a name="p2069161025093534"></a><a name="p2069161025093534"></a>bool&nbsp;</p>
<p id="p18632790093534"><a name="p18632790093534"></a><a name="p18632790093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1398233959093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p540377305093534"><a name="p540377305093534"></a><a name="p540377305093534"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p631479934093534"><a name="p631479934093534"></a><a name="p631479934093534"></a>void&nbsp;</p>
<p id="p1147164578093534"><a name="p1147164578093534"></a><a name="p1147164578093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row675655740093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671354661093534"><a name="p671354661093534"></a><a name="p671354661093534"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1935669785093534"><a name="p1935669785093534"></a><a name="p1935669785093534"></a>bool&nbsp;</p>
<p id="p256812084093534"><a name="p256812084093534"></a><a name="p256812084093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1706873064093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1126544473093534"><a name="p1126544473093534"></a><a name="p1126544473093534"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p739469444093534"><a name="p739469444093534"></a><a name="p739469444093534"></a>void&nbsp;</p>
<p id="p2043571475093534"><a name="p2043571475093534"></a><a name="p2043571475093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1409022549093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p618721707093534"><a name="p618721707093534"></a><a name="p618721707093534"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p611522884093534"><a name="p611522884093534"></a><a name="p611522884093534"></a>bool&nbsp;</p>
<p id="p813155194093534"><a name="p813155194093534"></a><a name="p813155194093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row897288527093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p215322372093534"><a name="p215322372093534"></a><a name="p215322372093534"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1715096676093534"><a name="p1715096676093534"></a><a name="p1715096676093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1381471446093534"><a name="p1381471446093534"></a><a name="p1381471446093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1687561537093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p971526563093534"><a name="p971526563093534"></a><a name="p971526563093534"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p996961668093534"><a name="p996961668093534"></a><a name="p996961668093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p749731474093534"><a name="p749731474093534"></a><a name="p749731474093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row749081848093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p914273518093534"><a name="p914273518093534"></a><a name="p914273518093534"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2033165926093534"><a name="p2033165926093534"></a><a name="p2033165926093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1938880341093534"><a name="p1938880341093534"></a><a name="p1938880341093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row735504106093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1798198371093534"><a name="p1798198371093534"></a><a name="p1798198371093534"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p859770219093534"><a name="p859770219093534"></a><a name="p859770219093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1570257305093534"><a name="p1570257305093534"></a><a name="p1570257305093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row890214328093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p104620378093534"><a name="p104620378093534"></a><a name="p104620378093534"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p245804365093534"><a name="p245804365093534"></a><a name="p245804365093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1579011021093534"><a name="p1579011021093534"></a><a name="p1579011021093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1930706548093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1892273033093534"><a name="p1892273033093534"></a><a name="p1892273033093534"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2044146880093534"><a name="p2044146880093534"></a><a name="p2044146880093534"></a>void&nbsp;</p>
<p id="p1288639230093534"><a name="p1288639230093534"></a><a name="p1288639230093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1528233542093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p286409671093534"><a name="p286409671093534"></a><a name="p286409671093534"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278647949093534"><a name="p278647949093534"></a><a name="p278647949093534"></a>virtual void&nbsp;</p>
<p id="p2016304229093534"><a name="p2016304229093534"></a><a name="p2016304229093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row300012470093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p602254233093534"><a name="p602254233093534"></a><a name="p602254233093534"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p883948369093534"><a name="p883948369093534"></a><a name="p883948369093534"></a>virtual void&nbsp;</p>
<p id="p975227565093534"><a name="p975227565093534"></a><a name="p975227565093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row710089537093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1865008206093534"><a name="p1865008206093534"></a><a name="p1865008206093534"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2127290617093534"><a name="p2127290617093534"></a><a name="p2127290617093534"></a>int16_t&nbsp;</p>
<p id="p2066109616093534"><a name="p2066109616093534"></a><a name="p2066109616093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row495369795093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1930845829093534"><a name="p1930845829093534"></a><a name="p1930845829093534"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p741606723093534"><a name="p741606723093534"></a><a name="p741606723093534"></a>virtual void&nbsp;</p>
<p id="p1761612897093534"><a name="p1761612897093534"></a><a name="p1761612897093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row960739148093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1152912963093534"><a name="p1152912963093534"></a><a name="p1152912963093534"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1025814568093534"><a name="p1025814568093534"></a><a name="p1025814568093534"></a>int16_t&nbsp;</p>
<p id="p1993130190093534"><a name="p1993130190093534"></a><a name="p1993130190093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1126358765093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1954636171093534"><a name="p1954636171093534"></a><a name="p1954636171093534"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1219756308093534"><a name="p1219756308093534"></a><a name="p1219756308093534"></a>virtual void&nbsp;</p>
<p id="p336497498093534"><a name="p336497498093534"></a><a name="p336497498093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row299496105093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p810636833093534"><a name="p810636833093534"></a><a name="p810636833093534"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1142030542093534"><a name="p1142030542093534"></a><a name="p1142030542093534"></a>virtual void&nbsp;</p>
<p id="p215508113093534"><a name="p215508113093534"></a><a name="p215508113093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1246506089093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p932014917093534"><a name="p932014917093534"></a><a name="p932014917093534"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1449672147093534"><a name="p1449672147093534"></a><a name="p1449672147093534"></a>bool&nbsp;</p>
<p id="p2108619482093534"><a name="p2108619482093534"></a><a name="p2108619482093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row703689228093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p430198257093534"><a name="p430198257093534"></a><a name="p430198257093534"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1427049319093534"><a name="p1427049319093534"></a><a name="p1427049319093534"></a>void&nbsp;</p>
<p id="p17030477093534"><a name="p17030477093534"></a><a name="p17030477093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row809549685093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p856613956093534"><a name="p856613956093534"></a><a name="p856613956093534"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137722203093534"><a name="p2137722203093534"></a><a name="p2137722203093534"></a>void&nbsp;</p>
<p id="p609795300093534"><a name="p609795300093534"></a><a name="p609795300093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1026044564093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197323547093534"><a name="p1197323547093534"></a><a name="p1197323547093534"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1301820558093534"><a name="p1301820558093534"></a><a name="p1301820558093534"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p68425453093534"><a name="p68425453093534"></a><a name="p68425453093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row184566749093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p49514717093534"><a name="p49514717093534"></a><a name="p49514717093534"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p380103086093534"><a name="p380103086093534"></a><a name="p380103086093534"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1854458798093534"><a name="p1854458798093534"></a><a name="p1854458798093534"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row1424782319093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p222047788093534"><a name="p222047788093534"></a><a name="p222047788093534"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1705949688093534"><a name="p1705949688093534"></a><a name="p1705949688093534"></a>void&nbsp;</p>
<p id="p533563224093534"><a name="p533563224093534"></a><a name="p533563224093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1051526253093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p107384751093534"><a name="p107384751093534"></a><a name="p107384751093534"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1837197081093534"><a name="p1837197081093534"></a><a name="p1837197081093534"></a>const char *&nbsp;</p>
<p id="p2094927650093534"><a name="p2094927650093534"></a><a name="p2094927650093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1111537880093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p232501189093534"><a name="p232501189093534"></a><a name="p232501189093534"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1939194965093534"><a name="p1939194965093534"></a><a name="p1939194965093534"></a>void&nbsp;</p>
<p id="p917613026093534"><a name="p917613026093534"></a><a name="p917613026093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1542067121093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p41959025093534"><a name="p41959025093534"></a><a name="p41959025093534"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p228171372093534"><a name="p228171372093534"></a><a name="p228171372093534"></a>int16_t&nbsp;</p>
<p id="p625272325093534"><a name="p625272325093534"></a><a name="p625272325093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row821151244093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p353688044093534"><a name="p353688044093534"></a><a name="p353688044093534"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1301094855093534"><a name="p1301094855093534"></a><a name="p1301094855093534"></a>virtual void&nbsp;</p>
<p id="p192989414093534"><a name="p192989414093534"></a><a name="p192989414093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row786933096093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1771005564093534"><a name="p1771005564093534"></a><a name="p1771005564093534"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1396221004093534"><a name="p1396221004093534"></a><a name="p1396221004093534"></a>void&nbsp;</p>
<p id="p989593063093534"><a name="p989593063093534"></a><a name="p989593063093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row844385951093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2133860109093534"><a name="p2133860109093534"></a><a name="p2133860109093534"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p520522673093534"><a name="p520522673093534"></a><a name="p520522673093534"></a>void&nbsp;</p>
<p id="p2108525029093534"><a name="p2108525029093534"></a><a name="p2108525029093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row427483004093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p71408265093534"><a name="p71408265093534"></a><a name="p71408265093534"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1333504471093534"><a name="p1333504471093534"></a><a name="p1333504471093534"></a>void&nbsp;</p>
<p id="p532411557093534"><a name="p532411557093534"></a><a name="p532411557093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1815092066093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1375172972093534"><a name="p1375172972093534"></a><a name="p1375172972093534"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2036441496093534"><a name="p2036441496093534"></a><a name="p2036441496093534"></a>void&nbsp;</p>
<p id="p1204915638093534"><a name="p1204915638093534"></a><a name="p1204915638093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row814819764093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p668021813093534"><a name="p668021813093534"></a><a name="p668021813093534"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1583986762093534"><a name="p1583986762093534"></a><a name="p1583986762093534"></a>void&nbsp;</p>
<p id="p1939815194093534"><a name="p1939815194093534"></a><a name="p1939815194093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row902965381093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p375788248093534"><a name="p375788248093534"></a><a name="p375788248093534"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1919379328093534"><a name="p1919379328093534"></a><a name="p1919379328093534"></a>void&nbsp;</p>
<p id="p251747302093534"><a name="p251747302093534"></a><a name="p251747302093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1324736923093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1567299898093534"><a name="p1567299898093534"></a><a name="p1567299898093534"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2011672268093534"><a name="p2011672268093534"></a><a name="p2011672268093534"></a>void&nbsp;</p>
<p id="p738130137093534"><a name="p738130137093534"></a><a name="p738130137093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row237844468093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1837951004093534"><a name="p1837951004093534"></a><a name="p1837951004093534"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1794573623093534"><a name="p1794573623093534"></a><a name="p1794573623093534"></a>void&nbsp;</p>
<p id="p1599110148093534"><a name="p1599110148093534"></a><a name="p1599110148093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row541326481093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1146129213093534"><a name="p1146129213093534"></a><a name="p1146129213093534"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511677232093534"><a name="p1511677232093534"></a><a name="p1511677232093534"></a>void&nbsp;</p>
<p id="p42944755093534"><a name="p42944755093534"></a><a name="p42944755093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row880764682093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p780278426093534"><a name="p780278426093534"></a><a name="p780278426093534"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1799955080093534"><a name="p1799955080093534"></a><a name="p1799955080093534"></a>void&nbsp;</p>
<p id="p360179813093534"><a name="p360179813093534"></a><a name="p360179813093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1396663574093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1058506272093534"><a name="p1058506272093534"></a><a name="p1058506272093534"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703618273093534"><a name="p1703618273093534"></a><a name="p1703618273093534"></a>void&nbsp;</p>
<p id="p160571008093534"><a name="p160571008093534"></a><a name="p160571008093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row2110354718093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1744653270093534"><a name="p1744653270093534"></a><a name="p1744653270093534"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2051340179093534"><a name="p2051340179093534"></a><a name="p2051340179093534"></a>void&nbsp;</p>
<p id="p1575377528093534"><a name="p1575377528093534"></a><a name="p1575377528093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row379808237093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2097244554093534"><a name="p2097244554093534"></a><a name="p2097244554093534"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p843965919093534"><a name="p843965919093534"></a><a name="p843965919093534"></a>void&nbsp;</p>
<p id="p1337820950093534"><a name="p1337820950093534"></a><a name="p1337820950093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row1147930721093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1507108244093534"><a name="p1507108244093534"></a><a name="p1507108244093534"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p837330039093534"><a name="p837330039093534"></a><a name="p837330039093534"></a>void&nbsp;</p>
<p id="p553167642093534"><a name="p553167642093534"></a><a name="p553167642093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row868176605093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1031024745093534"><a name="p1031024745093534"></a><a name="p1031024745093534"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1778196297093534"><a name="p1778196297093534"></a><a name="p1778196297093534"></a>void&nbsp;</p>
<p id="p256255711093534"><a name="p256255711093534"></a><a name="p256255711093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1892502051093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p982777289093534"><a name="p982777289093534"></a><a name="p982777289093534"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2087220875093534"><a name="p2087220875093534"></a><a name="p2087220875093534"></a>virtual void&nbsp;</p>
<p id="p661510320093534"><a name="p661510320093534"></a><a name="p661510320093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1513243605093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p627276260093534"><a name="p627276260093534"></a><a name="p627276260093534"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p792419810093534"><a name="p792419810093534"></a><a name="p792419810093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1238872214093534"><a name="p1238872214093534"></a><a name="p1238872214093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row393808236093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1008031466093534"><a name="p1008031466093534"></a><a name="p1008031466093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389159989093534"><a name="p1389159989093534"></a><a name="p1389159989093534"></a>void *&nbsp;</p>
<p id="p1181841179093534"><a name="p1181841179093534"></a><a name="p1181841179093534"></a>Overrides the <strong id="b818365321093534"><a name="b818365321093534"></a><a name="b818365321093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1692346779093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1477036644093534"><a name="p1477036644093534"></a><a name="p1477036644093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p96571830093534"><a name="p96571830093534"></a><a name="p96571830093534"></a>void&nbsp;</p>
<p id="p1109125053093534"><a name="p1109125053093534"></a><a name="p1109125053093534"></a>Overrides the <strong id="b108169655093534"><a name="b108169655093534"></a><a name="b108169655093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1026860376093534"></a>
<table><thead align="left"><tr id="row743620432093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p720857513093534"><a name="p720857513093534"></a><a name="p720857513093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p7509126093534"><a name="p7509126093534"></a><a name="p7509126093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row613386071093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1773488626093534"><a name="p1773488626093534"></a><a name="p1773488626093534"></a><a href="Graphic.md#gaf9f6c0c373f090e79b9e8d847e186e92">ButtonImageSrc</a> : uint8_t </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646405456093534"><a name="p1646405456093534"></a><a name="p1646405456093534"></a>Enumerates the images for different button states. </p>
</td>
</tr>
<tr id="row1369599708093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1713475054093534"><a name="p1713475054093534"></a><a name="p1713475054093534"></a><a href="Graphic.md#ga188dd55c17ee44be27fa80543f13f729">ButtonState</a> : uint8_t </p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p399576138093534"><a name="p399576138093534"></a><a name="p399576138093534"></a>Enumerates the states of this button. </p>
</td>
</tr>
</tbody>
</table>

