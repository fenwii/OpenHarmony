# OHOS::Text<a name="EN-US_TOPIC_0000001055678112"></a>

## **Overview**<a name="section1147823719093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Represents the base class of  **[Text](ohos-text.md)**, providing the text attribute setting and text drawing capabilities for components that require font display. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1707684078093533"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table677496323093533"></a>
<table><thead align="left"><tr id="row804932818093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p79161986093533"><a name="p79161986093533"></a><a name="p79161986093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1543038753093533"><a name="p1543038753093533"></a><a name="p1543038753093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row392785468093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1817845658093533"><a name="p1817845658093533"></a><a name="p1817845658093533"></a><a href="graphic.md#ga7ea8e1b0f5e199317c3134b575431ce6">Text</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1163839808093533"><a name="p1163839808093533"></a><a name="p1163839808093533"></a> </p>
<p id="p79147680093533"><a name="p79147680093533"></a><a name="p79147680093533"></a>A constructor used to create a <strong id="b1637245305093533"><a name="b1637245305093533"></a><a name="b1637245305093533"></a><a href="ohos-text.md">Text</a></strong> instance. </p>
</td>
</tr>
<tr id="row1368946574093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p881004253093533"><a name="p881004253093533"></a><a name="p881004253093533"></a><a href="graphic.md#gae15585b395b286ee404a57a61baa81f1">~Text</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p469942381093533"><a name="p469942381093533"></a><a name="p469942381093533"></a>virtual </p>
<p id="p1891855372093533"><a name="p1891855372093533"></a><a name="p1891855372093533"></a>A destructor used to delete the <strong id="b2034586683093533"><a name="b2034586683093533"></a><a name="b2034586683093533"></a><a href="ohos-text.md">Text</a></strong> instance. </p>
</td>
</tr>
<tr id="row1143110243093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1782882036093533"><a name="p1782882036093533"></a><a name="p1782882036093533"></a><a href="graphic.md#gaf4c592a07fe20af21e0ddae2d8203d96">SetText</a> (const char *text)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p566880234093533"><a name="p566880234093533"></a><a name="p566880234093533"></a>void </p>
<p id="p2136302840093533"><a name="p2136302840093533"></a><a name="p2136302840093533"></a>Sets the content for this text. </p>
</td>
</tr>
<tr id="row576013084093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1660850838093533"><a name="p1660850838093533"></a><a name="p1660850838093533"></a><a href="graphic.md#gafcc64349913763e8d7feaf7bd9cbd639">GetText</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p607848449093533"><a name="p607848449093533"></a><a name="p607848449093533"></a>const char * </p>
<p id="p818655908093533"><a name="p818655908093533"></a><a name="p818655908093533"></a>Obtains the content of this text. </p>
</td>
</tr>
<tr id="row65890897093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p185436450093533"><a name="p185436450093533"></a><a name="p185436450093533"></a><a href="graphic.md#ga1c1a26e57098662f787a1bb44bb9da8c">SetFont</a> (const char *name, uint8_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1951875413093533"><a name="p1951875413093533"></a><a name="p1951875413093533"></a>void </p>
<p id="p1103505068093533"><a name="p1103505068093533"></a><a name="p1103505068093533"></a>Sets the font name and size. </p>
</td>
</tr>
<tr id="row1520245566093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1247438487093533"><a name="p1247438487093533"></a><a name="p1247438487093533"></a><a href="graphic.md#gac27135182c89eabec65e22df079dc413">SetFontId</a> (uint8_t fontId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908651714093533"><a name="p908651714093533"></a><a name="p908651714093533"></a>void </p>
<p id="p642757801093533"><a name="p642757801093533"></a><a name="p642757801093533"></a>Sets the font ID. </p>
</td>
</tr>
<tr id="row653765165093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p743182417093533"><a name="p743182417093533"></a><a name="p743182417093533"></a><a href="graphic.md#ga32ba629806e9d8553bbcd441b4e66d55">GetFontId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1816528354093533"><a name="p1816528354093533"></a><a name="p1816528354093533"></a>uint8_t </p>
<p id="p1478674081093533"><a name="p1478674081093533"></a><a name="p1478674081093533"></a>Obtains the font ID. </p>
</td>
</tr>
<tr id="row28252932093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p925480891093533"><a name="p925480891093533"></a><a name="p925480891093533"></a><a href="graphic.md#ga96801aa6350a8533496b0718d67f0b9c">SetDirect</a> (<a href="graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a> direct)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1189110819093533"><a name="p1189110819093533"></a><a name="p1189110819093533"></a>void </p>
<p id="p1122780716093533"><a name="p1122780716093533"></a><a name="p1122780716093533"></a>Sets the direction for this text. </p>
</td>
</tr>
<tr id="row1014393018093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p612431794093533"><a name="p612431794093533"></a><a name="p612431794093533"></a><a href="graphic.md#gacd469d16b0f3a8e7406d736f5e857996">GetDirect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p518837453093533"><a name="p518837453093533"></a><a name="p518837453093533"></a><a href="graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a> </p>
<p id="p1230940892093533"><a name="p1230940892093533"></a><a name="p1230940892093533"></a>Obtains the direction of this text. </p>
</td>
</tr>
<tr id="row1002709872093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1411058001093533"><a name="p1411058001093533"></a><a name="p1411058001093533"></a><a href="graphic.md#gad4721f5014971f6017aaaa5cc0af6845">SetAlign</a> (<a href="graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> horizontalAlign, <a href="graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> verticalAlign=TEXT_ALIGNMENT_TOP)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2109562979093533"><a name="p2109562979093533"></a><a name="p2109562979093533"></a>void </p>
<p id="p50899354093533"><a name="p50899354093533"></a><a name="p50899354093533"></a>Sets the alignment mode for this text. </p>
</td>
</tr>
<tr id="row1943746739093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1783847850093533"><a name="p1783847850093533"></a><a name="p1783847850093533"></a><a href="graphic.md#ga3c17868fb06a77f43587c67de4ca5ab6">GetHorAlign</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p786219924093533"><a name="p786219924093533"></a><a name="p786219924093533"></a><a href="graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> </p>
<p id="p787588128093533"><a name="p787588128093533"></a><a name="p787588128093533"></a>Obtains the horizontal alignment mode. </p>
</td>
</tr>
<tr id="row1939051656093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2121211790093533"><a name="p2121211790093533"></a><a name="p2121211790093533"></a><a href="graphic.md#gac312f642e12cfad8d974f8159984864e">GetVerAlign</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847739070093533"><a name="p1847739070093533"></a><a name="p1847739070093533"></a><a href="graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> </p>
<p id="p1160176788093533"><a name="p1160176788093533"></a><a name="p1160176788093533"></a>Obtains the vertical alignment mode. </p>
</td>
</tr>
<tr id="row757152844093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p232482358093533"><a name="p232482358093533"></a><a name="p232482358093533"></a><a href="graphic.md#ga2ec83b586a0a7ebe402bb70a31be2ca6">SetTextRotation</a> (LabelRotateDegree angle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1565723428093533"><a name="p1565723428093533"></a><a name="p1565723428093533"></a>void </p>
<p id="p1421992531093533"><a name="p1421992531093533"></a><a name="p1421992531093533"></a>Sets the clockwise rotation angle for this text. </p>
</td>
</tr>
<tr id="row1373223216093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p322975862093533"><a name="p322975862093533"></a><a name="p322975862093533"></a><a href="graphic.md#ga2dcc364f56ffa8bada573c7f96c92b0e">GetTextRotation</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p443442393093533"><a name="p443442393093533"></a><a name="p443442393093533"></a>LabelRotateDegree </p>
<p id="p661503862093533"><a name="p661503862093533"></a><a name="p661503862093533"></a>Obtains the clockwise rotation degree of this text. </p>
</td>
</tr>
<tr id="row1063542886093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p681362078093533"><a name="p681362078093533"></a><a name="p681362078093533"></a><a href="graphic.md#gae36f3e226f23d8d7dff174054f60a741">GetTextRotateDegree</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p458196079093533"><a name="p458196079093533"></a><a name="p458196079093533"></a>uint16_t </p>
<p id="p352761604093533"><a name="p352761604093533"></a><a name="p352761604093533"></a>Obtains the number of text rotation degrees. </p>
</td>
</tr>
<tr id="row971863627093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p960209477093533"><a name="p960209477093533"></a><a name="p960209477093533"></a><a href="graphic.md#ga7e3e2deccb36992428d7984681329f09">GetTextSize</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1679138614093533"><a name="p1679138614093533"></a><a name="p1679138614093533"></a><a href="ohos-point.md">Point</a> </p>
<p id="p736980929093533"><a name="p736980929093533"></a><a name="p736980929093533"></a>Obtains the size of this text. </p>
</td>
</tr>
<tr id="row1616953332093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p240232983093533"><a name="p240232983093533"></a><a name="p240232983093533"></a><a href="graphic.md#ga7aa8b64ece3c4b3bf592dc88fc7c11d2">SetExpandWidth</a> (bool expand)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1864611434093533"><a name="p1864611434093533"></a><a name="p1864611434093533"></a>void </p>
<p id="p409441279093533"><a name="p409441279093533"></a><a name="p409441279093533"></a>Sets whether to adapt the component width to this text. </p>
</td>
</tr>
<tr id="row1819872405093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p695934686093533"><a name="p695934686093533"></a><a name="p695934686093533"></a><a href="graphic.md#gaab55ac2d3f8e45b4bfb5fd5ae07d1edd">IsExpandWidth</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p994000844093533"><a name="p994000844093533"></a><a name="p994000844093533"></a>bool </p>
<p id="p131992675093533"><a name="p131992675093533"></a><a name="p131992675093533"></a>Checks whether the component width adapts to this text. </p>
</td>
</tr>
<tr id="row833067207093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1901189141093533"><a name="p1901189141093533"></a><a name="p1901189141093533"></a><a href="graphic.md#gac08f297a1593424d754450c75bc47045">SetExpandHeight</a> (bool expand)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p370066073093533"><a name="p370066073093533"></a><a name="p370066073093533"></a>void </p>
<p id="p337015955093533"><a name="p337015955093533"></a><a name="p337015955093533"></a>Sets whether to adapt the component height to this text. </p>
</td>
</tr>
<tr id="row241546178093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1250984523093533"><a name="p1250984523093533"></a><a name="p1250984523093533"></a><a href="graphic.md#ga09475a9cd4e86b19d4c3d4206ea5ffc6">IsExpandHeight</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1747997889093533"><a name="p1747997889093533"></a><a name="p1747997889093533"></a>bool </p>
<p id="p2027145177093533"><a name="p2027145177093533"></a><a name="p2027145177093533"></a>Checks whether the component height adapts to this text. </p>
</td>
</tr>
<tr id="row1358207342093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p183097806093533"><a name="p183097806093533"></a><a name="p183097806093533"></a><a href="graphic.md#ga302dc8ff172b67c104363710f4b53cb0">GetEllipsisIndex</a> (const <a href="ohos-rect.md">Rect</a> &amp;textRect, const <a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1134950564093533"><a name="p1134950564093533"></a><a name="p1134950564093533"></a>uint16_t </p>
<p id="p1490032055093533"><a name="p1490032055093533"></a><a name="p1490032055093533"></a>Obtains the index of the character from where text will be replaced by ellipses based on the text rectangle and style. </p>
</td>
</tr>
</tbody>
</table>

## Static Public Attributes<a name="pub-static-attribs"></a>

<a name="table8168335093533"></a>
<table><thead align="left"><tr id="row902412138093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p990808506093533"><a name="p990808506093533"></a><a name="p990808506093533"></a>Static Public Attribute Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2008903761093533"><a name="p2008903761093533"></a><a name="p2008903761093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row344559005093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p990512809093533"><a name="p990512809093533"></a><a name="p990512809093533"></a><a href="graphic.md#gaeacbcd7308bba53ba1154424143cd349">TEXT_ELLIPSIS_END_INV</a> = 0xFFFF</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">&nbsp;</td>
</tr>
</tbody>
</table>

