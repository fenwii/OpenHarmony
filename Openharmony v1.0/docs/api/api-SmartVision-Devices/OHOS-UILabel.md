# OHOS::UILabel<a name="ZH-CN_TOPIC_0000001055198150"></a>

## **Overview**<a name="section1006845929093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines the functions for presenting a label in a specified area, setting the style and background color of a label, and setting the display mode of a long label text. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1674225588093533"></a>

## Public Types<a name="pub-types"></a>

<a name="table257356162093533"></a>
<table><thead align="left"><tr id="row112485638093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p817409818093533"><a name="p817409818093533"></a><a name="p817409818093533"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p531067528093533"><a name="p531067528093533"></a><a name="p531067528093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row33524390093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1509354369093533"><a name="p1509354369093533"></a><a name="p1509354369093533"></a><a href="Graphic.md#gaf2ba9acac6cafffc549781ace0475cd5">LineBreakMode</a> : uint8_t { &nbsp;&nbsp;<a href="Graphic.md#ggaf2ba9acac6cafffc549781ace0475cd5a03a7da624ae08162b5e74ad67e50467f">LINE_BREAK_ADAPT</a> = 0, <a href="Graphic.md#ggaf2ba9acac6cafffc549781ace0475cd5abc49de1d3936e957882efbb3259dc5be">LINE_BREAK_STRETCH</a>, <a href="Graphic.md#ggaf2ba9acac6cafffc549781ace0475cd5a2d55ab62d9cead746eb1eaaad1e4e621">LINE_BREAK_WRAP</a>, <a href="Graphic.md#ggaf2ba9acac6cafffc549781ace0475cd5ac15f8bb00b735e743b621f24a864b0ed">LINE_BREAK_ELLIPSIS</a>, &nbsp;&nbsp;<a href="Graphic.md#ggaf2ba9acac6cafffc549781ace0475cd5a6d3e13d5e53904899020e2c44f6ca82d">LINE_BREAK_MARQUEE</a>, <a href="Graphic.md#ggaf2ba9acac6cafffc549781ace0475cd5a4111b08e919f919c314556753aa3ff46">LINE_BREAK_CLIP</a>, <a href="Graphic.md#ggaf2ba9acac6cafffc549781ace0475cd5afb101ae817692c5bada96ba35f9a636d">LINE_BREAK_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p366107978093533"><a name="p366107978093533"></a><a name="p366107978093533"></a>Enumerates the display modes of a long text. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1664741238093533"></a>
<table><thead align="left"><tr id="row340546740093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1498426861093533"><a name="p1498426861093533"></a><a name="p1498426861093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1232118875093533"><a name="p1232118875093533"></a><a name="p1232118875093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row531092828093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2084566026093533"><a name="p2084566026093533"></a><a name="p2084566026093533"></a><a href="Graphic.md#ga7e145ba3fb7b78ecefa1018a9540be32">UILabel</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1113967995093533"><a name="p1113967995093533"></a><a name="p1113967995093533"></a>&nbsp;</p>
<p id="p1363039107093533"><a name="p1363039107093533"></a><a name="p1363039107093533"></a>A constructor used to create a <strong id="b275619282093533"><a name="b275619282093533"></a><a name="b275619282093533"></a><a href="OHOS-UILabel.md">UILabel</a></strong> instance. </p>
</td>
</tr>
<tr id="row1523602195093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1983270913093533"><a name="p1983270913093533"></a><a name="p1983270913093533"></a><a href="Graphic.md#ga8509fa2391e0ddd37faed27e35845fc5">~UILabel</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1546552746093533"><a name="p1546552746093533"></a><a name="p1546552746093533"></a>virtual&nbsp;</p>
<p id="p523347986093533"><a name="p523347986093533"></a><a name="p523347986093533"></a>A destructor used to delete the <strong id="b477729397093533"><a name="b477729397093533"></a><a name="b477729397093533"></a><a href="OHOS-UILabel.md">UILabel</a></strong> instance. </p>
</td>
</tr>
<tr id="row1752563500093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1624966332093533"><a name="p1624966332093533"></a><a name="p1624966332093533"></a><a href="Graphic.md#gaebb514dc68a761c444af0e0e89dfcb6f">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p197812734093533"><a name="p197812734093533"></a><a name="p197812734093533"></a>UIViewType&nbsp;</p>
<p id="p1839180764093533"><a name="p1839180764093533"></a><a name="p1839180764093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1390670064093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2041953792093533"><a name="p2041953792093533"></a><a name="p2041953792093533"></a><a href="Graphic.md#ga95bc777cda044ada4401d9c5900226c6">GetWidth</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p128909327093533"><a name="p128909327093533"></a><a name="p128909327093533"></a>int16_t&nbsp;</p>
<p id="p1090864958093533"><a name="p1090864958093533"></a><a name="p1090864958093533"></a>Obtains the width of this label. </p>
</td>
</tr>
<tr id="row1988699904093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p546536621093533"><a name="p546536621093533"></a><a name="p546536621093533"></a><a href="Graphic.md#ga148f6d32ed06364dbee0190f6ff77b59">GetHeight</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1503463934093533"><a name="p1503463934093533"></a><a name="p1503463934093533"></a>int16_t&nbsp;</p>
<p id="p1625678004093533"><a name="p1625678004093533"></a><a name="p1625678004093533"></a>Obtains the height of this label. </p>
</td>
</tr>
<tr id="row617818659093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1190049331093533"><a name="p1190049331093533"></a><a name="p1190049331093533"></a><a href="Graphic.md#gaac293fb7f318e1855fba21b740147061">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p447625732093533"><a name="p447625732093533"></a><a name="p447625732093533"></a>bool&nbsp;</p>
<p id="p445517649093533"><a name="p445517649093533"></a><a name="p445517649093533"></a>Checks whether this label needs to be covered before drawing it. </p>
</td>
</tr>
<tr id="row76662508093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1142605870093533"><a name="p1142605870093533"></a><a name="p1142605870093533"></a><a href="Graphic.md#ga911199741bf792b5de00789b4c8d780d">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p157926314093533"><a name="p157926314093533"></a><a name="p157926314093533"></a>void&nbsp;</p>
<p id="p1329976014093533"><a name="p1329976014093533"></a><a name="p1329976014093533"></a>Draws this label. </p>
</td>
</tr>
<tr id="row800827491093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1263636438093533"><a name="p1263636438093533"></a><a name="p1263636438093533"></a><a href="Graphic.md#gab1f3eafda465d09aaa886f09db7e47c1">SetText</a> (const char *text)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p145818437093533"><a name="p145818437093533"></a><a name="p145818437093533"></a>void&nbsp;</p>
<p id="p1995230294093533"><a name="p1995230294093533"></a><a name="p1995230294093533"></a>Sets the text content for this label. </p>
</td>
</tr>
<tr id="row1189233728093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p712730062093533"><a name="p712730062093533"></a><a name="p712730062093533"></a><a href="Graphic.md#gafa76232f16f5aad2a84fedbb31c4f0f7">GetText</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1583217083093533"><a name="p1583217083093533"></a><a name="p1583217083093533"></a>const char *&nbsp;</p>
<p id="p2038288344093533"><a name="p2038288344093533"></a><a name="p2038288344093533"></a>Obtains the text of this label. </p>
</td>
</tr>
<tr id="row55403848093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p475478310093533"><a name="p475478310093533"></a><a name="p475478310093533"></a><a href="Graphic.md#ga406c7972fbf4950aaa8c4cef8c86acc5">SetLineBreakMode</a> (const uint8_t lineBreakMode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p76719265093533"><a name="p76719265093533"></a><a name="p76719265093533"></a>void&nbsp;</p>
<p id="p975367472093533"><a name="p975367472093533"></a><a name="p975367472093533"></a>Sets the line break mode for this text. </p>
</td>
</tr>
<tr id="row1838414405093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p552370560093533"><a name="p552370560093533"></a><a name="p552370560093533"></a><a href="Graphic.md#gab8924e40668b2c882d5dac624b49c6e8">GetLineBreakMode</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p203775310093533"><a name="p203775310093533"></a><a name="p203775310093533"></a>uint8_t&nbsp;</p>
<p id="p1534015705093533"><a name="p1534015705093533"></a><a name="p1534015705093533"></a>Obtains the line break mode of this text. </p>
</td>
</tr>
<tr id="row843254160093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p559527370093533"><a name="p559527370093533"></a><a name="p559527370093533"></a><a href="Graphic.md#ga07e45127ac9569064beb2a63753d2673">SetTextColor</a> (<a href="OHOS-Color32.md">ColorType</a> color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p41194394093533"><a name="p41194394093533"></a><a name="p41194394093533"></a>void&nbsp;</p>
<p id="p1784860855093533"><a name="p1784860855093533"></a><a name="p1784860855093533"></a>Sets the color for this text. </p>
</td>
</tr>
<tr id="row2059935525093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p651616441093533"><a name="p651616441093533"></a><a name="p651616441093533"></a><a href="Graphic.md#ga963236ec609ea50610f7ef2bf85ea6df">GetTextColor</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p209447951093533"><a name="p209447951093533"></a><a name="p209447951093533"></a><a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1658114138093533"><a name="p1658114138093533"></a><a name="p1658114138093533"></a>Obtains the color of this text. </p>
</td>
</tr>
<tr id="row1132079567093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1424523214093533"><a name="p1424523214093533"></a><a name="p1424523214093533"></a><a href="Graphic.md#ga889e1adc1a74db59dc161cb7031b1f23">SetAlign</a> (<a href="Graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> horizontalAlign, <a href="Graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> verticalAlign=TEXT_ALIGNMENT_TOP)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1812990934093533"><a name="p1812990934093533"></a><a name="p1812990934093533"></a>void&nbsp;</p>
<p id="p475627153093533"><a name="p475627153093533"></a><a name="p475627153093533"></a>Sets the alignment mode for this text. </p>
</td>
</tr>
<tr id="row18642114093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390194281093533"><a name="p390194281093533"></a><a name="p390194281093533"></a><a href="Graphic.md#ga97a9af1537884de541336633edc54c72">GetHorAlign</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1344502685093533"><a name="p1344502685093533"></a><a name="p1344502685093533"></a><a href="Graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a>&nbsp;</p>
<p id="p1211790943093533"><a name="p1211790943093533"></a><a name="p1211790943093533"></a>Obtains the horizontal alignment mode. </p>
</td>
</tr>
<tr id="row370122823093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2125491673093533"><a name="p2125491673093533"></a><a name="p2125491673093533"></a><a href="Graphic.md#gaf4acdd488481fe6ce0e79eb6a9d35d78">GetVerAlign</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p917660839093533"><a name="p917660839093533"></a><a name="p917660839093533"></a><a href="Graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a>&nbsp;</p>
<p id="p117488414093533"><a name="p117488414093533"></a><a name="p117488414093533"></a>Obtains the vertical alignment mode. </p>
</td>
</tr>
<tr id="row388499595093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617936421093533"><a name="p617936421093533"></a><a name="p617936421093533"></a><a href="Graphic.md#ga51d43cfa57f438939627066d66a3f6cb">SetDirect</a> (<a href="Graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a> direct)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1634549604093533"><a name="p1634549604093533"></a><a name="p1634549604093533"></a>void&nbsp;</p>
<p id="p1380559969093533"><a name="p1380559969093533"></a><a name="p1380559969093533"></a>Sets the direction for this text. </p>
</td>
</tr>
<tr id="row1996289810093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p245445914093533"><a name="p245445914093533"></a><a name="p245445914093533"></a><a href="Graphic.md#gab7bbf711b9cd21935a29c4183c249d80">GetDirect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p979297647093533"><a name="p979297647093533"></a><a name="p979297647093533"></a><a href="Graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a>&nbsp;</p>
<p id="p1155898168093533"><a name="p1155898168093533"></a><a name="p1155898168093533"></a>Obtains the direction of this text. </p>
</td>
</tr>
<tr id="row742345184093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p641925837093533"><a name="p641925837093533"></a><a name="p641925837093533"></a><a href="Graphic.md#gaf8b585ae9aa99d4876e1d81c8b193300">SetFontId</a> (uint8_t fontId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1197399310093533"><a name="p1197399310093533"></a><a name="p1197399310093533"></a>void&nbsp;</p>
<p id="p1039254867093533"><a name="p1039254867093533"></a><a name="p1039254867093533"></a>Sets the font ID for this label. </p>
</td>
</tr>
<tr id="row1763616380093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p304020680093533"><a name="p304020680093533"></a><a name="p304020680093533"></a><a href="Graphic.md#ga8484c4167b7638b2bbaa10ba447c9a2f">GetFontId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327766434093533"><a name="p1327766434093533"></a><a name="p1327766434093533"></a>uint8_t&nbsp;</p>
<p id="p1146713858093533"><a name="p1146713858093533"></a><a name="p1146713858093533"></a>Obtains the font ID composed of font name and size. </p>
</td>
</tr>
<tr id="row458083561093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1888256137093533"><a name="p1888256137093533"></a><a name="p1888256137093533"></a><a href="Graphic.md#gad4b6741054c0041c6df365b1d41d49ec">SetFont</a> (const char *name, uint8_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1869035646093533"><a name="p1869035646093533"></a><a name="p1869035646093533"></a>void&nbsp;</p>
<p id="p701793713093533"><a name="p701793713093533"></a><a name="p701793713093533"></a>Sets the font for this label. </p>
</td>
</tr>
<tr id="row2069806585093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p821428456093533"><a name="p821428456093533"></a><a name="p821428456093533"></a><a href="Graphic.md#gaf95611590551b86e5e49efce1cab5069">SetRollSpeed</a> (uint16_t speed)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p276430995093533"><a name="p276430995093533"></a><a name="p276430995093533"></a>void&nbsp;</p>
<p id="p72958081093533"><a name="p72958081093533"></a><a name="p72958081093533"></a>Sets the scroll speed for this text. </p>
</td>
</tr>
<tr id="row1657756804093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2038690656093533"><a name="p2038690656093533"></a><a name="p2038690656093533"></a><a href="Graphic.md#gaff1afb0c1079bbab70c0f012ba62ea88">GetTextWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p344876852093533"><a name="p344876852093533"></a><a name="p344876852093533"></a>uint16_t&nbsp;</p>
<p id="p890535541093533"><a name="p890535541093533"></a><a name="p890535541093533"></a>Obtains the width of this text. </p>
</td>
</tr>
<tr id="row1812055447093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p22571503093533"><a name="p22571503093533"></a><a name="p22571503093533"></a><a href="Graphic.md#gaecbce6ea5599f99b1a2b150608cfc9e3">GetTextHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p128320256093533"><a name="p128320256093533"></a><a name="p128320256093533"></a>uint16_t&nbsp;</p>
<p id="p1363505249093533"><a name="p1363505249093533"></a><a name="p1363505249093533"></a>Obtains the height of this text. </p>
</td>
</tr>
<tr id="row1065010763093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1061192940093533"><a name="p1061192940093533"></a><a name="p1061192940093533"></a><a href="Graphic.md#gaeb4eb6f2b82574eb005fdbf17b0b926b">SetRollStartPos</a> (int16_t pos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1707910530093533"><a name="p1707910530093533"></a><a name="p1707910530093533"></a>void&nbsp;</p>
<p id="p358010910093533"><a name="p358010910093533"></a><a name="p358010910093533"></a>Sets the position where this text starts to roll. </p>
</td>
</tr>
<tr id="row1644374341093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p815806933093533"><a name="p815806933093533"></a><a name="p815806933093533"></a><a href="Graphic.md#gaa2bb611ed34bcb9fc5eb2d208409ab7a">GetRollStartPos</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764804796093533"><a name="p764804796093533"></a><a name="p764804796093533"></a>int16_t&nbsp;</p>
<p id="p929002409093533"><a name="p929002409093533"></a><a name="p929002409093533"></a>Obtains the position where this text starts to roll. </p>
</td>
</tr>
<tr id="row453277448093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329211244093533"><a name="p329211244093533"></a><a name="p329211244093533"></a><a href="Graphic.md#ga4000481fca247d526961d9da6809a806">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p554127297093533"><a name="p554127297093533"></a><a name="p554127297093533"></a>void&nbsp;</p>
<p id="p713293543093533"><a name="p713293543093533"></a><a name="p713293543093533"></a>Sets the width for this label. </p>
</td>
</tr>
<tr id="row1027338645093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1151302944093533"><a name="p1151302944093533"></a><a name="p1151302944093533"></a><a href="Graphic.md#ga9998ddd0dfc0863d31f931a76f1da033">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1571293024093533"><a name="p1571293024093533"></a><a name="p1571293024093533"></a>void&nbsp;</p>
<p id="p1485178722093533"><a name="p1485178722093533"></a><a name="p1485178722093533"></a>Sets the height for this label. </p>
</td>
</tr>
<tr id="row1365077902093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1934312384093533"><a name="p1934312384093533"></a><a name="p1934312384093533"></a><a href="Graphic.md#ga3c8eb22a51f4ec16640f5003c32d0341">SetTextRotation</a> (LabelRotateDegree angle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p941443349093533"><a name="p941443349093533"></a><a name="p941443349093533"></a>void&nbsp;</p>
<p id="p1887127285093533"><a name="p1887127285093533"></a><a name="p1887127285093533"></a>Sets the clockwise rotation angle for this text. </p>
</td>
</tr>
<tr id="row667357259093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p175639023093533"><a name="p175639023093533"></a><a name="p175639023093533"></a><a href="Graphic.md#ga610cb09fe19aafbb65899b060ee3cac7">GetTextRotation</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1157387899093533"><a name="p1157387899093533"></a><a name="p1157387899093533"></a>LabelRotateDegree&nbsp;</p>
<p id="p912790567093533"><a name="p912790567093533"></a><a name="p912790567093533"></a>Obtains the clockwise rotation degree of this text. </p>
</td>
</tr>
<tr id="row867964242093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329575643093533"><a name="p329575643093533"></a><a name="p329575643093533"></a><a href="Graphic.md#gaef9e2e7f3a8849875e2a29e961a7e590">GetTextRotateDegree</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267118309093533"><a name="p267118309093533"></a><a name="p267118309093533"></a>uint16_t&nbsp;</p>
<p id="p1596326226093533"><a name="p1596326226093533"></a><a name="p1596326226093533"></a>Obtains the number of text rotation degrees. </p>
</td>
</tr>
<tr id="row1581284847093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2116949547093533"><a name="p2116949547093533"></a><a name="p2116949547093533"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1456049068093533"><a name="p1456049068093533"></a><a name="p1456049068093533"></a>&nbsp;</p>
<p id="p1397727204093533"><a name="p1397727204093533"></a><a name="p1397727204093533"></a>A default constructor used to create an <strong id="b1847311909093533"><a name="b1847311909093533"></a><a name="b1847311909093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row908760542093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1642632144093533"><a name="p1642632144093533"></a><a name="p1642632144093533"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p229759451093533"><a name="p229759451093533"></a><a name="p229759451093533"></a>&nbsp;</p>
<p id="p1723793829093533"><a name="p1723793829093533"></a><a name="p1723793829093533"></a>A constructor used to create an <strong id="b1681044808093533"><a name="b1681044808093533"></a><a name="b1681044808093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1630114199093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p465307132093533"><a name="p465307132093533"></a><a name="p465307132093533"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1252704538093533"><a name="p1252704538093533"></a><a name="p1252704538093533"></a>virtual&nbsp;</p>
<p id="p1915039109093533"><a name="p1915039109093533"></a><a name="p1915039109093533"></a>A destructor used to delete the <strong id="b1503468516093533"><a name="b1503468516093533"></a><a name="b1503468516093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1969114888093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1009185970093533"><a name="p1009185970093533"></a><a name="p1009185970093533"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p524777895093533"><a name="p524777895093533"></a><a name="p524777895093533"></a>virtual void&nbsp;</p>
<p id="p80171099093533"><a name="p80171099093533"></a><a name="p80171099093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row501481675093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1033840896093533"><a name="p1033840896093533"></a><a name="p1033840896093533"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p174768768093533"><a name="p174768768093533"></a><a name="p174768768093533"></a>void&nbsp;</p>
<p id="p75719995093533"><a name="p75719995093533"></a><a name="p75719995093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row1211799336093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1313632190093533"><a name="p1313632190093533"></a><a name="p1313632190093533"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p483435200093533"><a name="p483435200093533"></a><a name="p483435200093533"></a>void&nbsp;</p>
<p id="p1566044758093533"><a name="p1566044758093533"></a><a name="p1566044758093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1801408655093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1304003614093533"><a name="p1304003614093533"></a><a name="p1304003614093533"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1932672204093533"><a name="p1932672204093533"></a><a name="p1932672204093533"></a>virtual bool&nbsp;</p>
<p id="p274775398093533"><a name="p274775398093533"></a><a name="p274775398093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row891084248093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1566381293093533"><a name="p1566381293093533"></a><a name="p1566381293093533"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1828761625093533"><a name="p1828761625093533"></a><a name="p1828761625093533"></a>virtual bool&nbsp;</p>
<p id="p314876192093533"><a name="p314876192093533"></a><a name="p314876192093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1492910131093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p40688091093533"><a name="p40688091093533"></a><a name="p40688091093533"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1844723177093533"><a name="p1844723177093533"></a><a name="p1844723177093533"></a>virtual bool&nbsp;</p>
<p id="p1267583659093533"><a name="p1267583659093533"></a><a name="p1267583659093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1515030093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1252049759093533"><a name="p1252049759093533"></a><a name="p1252049759093533"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p962442420093533"><a name="p962442420093533"></a><a name="p962442420093533"></a>virtual bool&nbsp;</p>
<p id="p1616427347093533"><a name="p1616427347093533"></a><a name="p1616427347093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1748536272093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p684861270093533"><a name="p684861270093533"></a><a name="p684861270093533"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1019634880093533"><a name="p1019634880093533"></a><a name="p1019634880093533"></a>virtual void&nbsp;</p>
<p id="p39979009093533"><a name="p39979009093533"></a><a name="p39979009093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row1044605704093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2045064280093533"><a name="p2045064280093533"></a><a name="p2045064280093533"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1339797289093533"><a name="p1339797289093533"></a><a name="p1339797289093533"></a>virtual void&nbsp;</p>
<p id="p424391497093533"><a name="p424391497093533"></a><a name="p424391497093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1270584148093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p308945728093533"><a name="p308945728093533"></a><a name="p308945728093533"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1328572387093533"><a name="p1328572387093533"></a><a name="p1328572387093533"></a>virtual void&nbsp;</p>
<p id="p511989789093533"><a name="p511989789093533"></a><a name="p511989789093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1430036367093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1195134919093533"><a name="p1195134919093533"></a><a name="p1195134919093533"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327305589093533"><a name="p327305589093533"></a><a name="p327305589093533"></a>virtual void&nbsp;</p>
<p id="p555187878093533"><a name="p555187878093533"></a><a name="p555187878093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row941613267093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2098034377093533"><a name="p2098034377093533"></a><a name="p2098034377093533"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p743334514093533"><a name="p743334514093533"></a><a name="p743334514093533"></a>void&nbsp;</p>
<p id="p1242941676093533"><a name="p1242941676093533"></a><a name="p1242941676093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row991329284093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p576611108093533"><a name="p576611108093533"></a><a name="p576611108093533"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1481133458093533"><a name="p1481133458093533"></a><a name="p1481133458093533"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p898010895093533"><a name="p898010895093533"></a><a name="p898010895093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1488502191093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1115366947093533"><a name="p1115366947093533"></a><a name="p1115366947093533"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1295494719093533"><a name="p1295494719093533"></a><a name="p1295494719093533"></a>void&nbsp;</p>
<p id="p186974409093533"><a name="p186974409093533"></a><a name="p186974409093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1464259908093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p678537942093533"><a name="p678537942093533"></a><a name="p678537942093533"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p902150229093533"><a name="p902150229093533"></a><a name="p902150229093533"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p253663901093533"><a name="p253663901093533"></a><a name="p253663901093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1873695863093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p230689558093533"><a name="p230689558093533"></a><a name="p230689558093533"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1565834625093533"><a name="p1565834625093533"></a><a name="p1565834625093533"></a>void&nbsp;</p>
<p id="p840295517093533"><a name="p840295517093533"></a><a name="p840295517093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1218057935093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p943596521093533"><a name="p943596521093533"></a><a name="p943596521093533"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p206159178093533"><a name="p206159178093533"></a><a name="p206159178093533"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p1973023598093533"><a name="p1973023598093533"></a><a name="p1973023598093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row643876922093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1118994173093533"><a name="p1118994173093533"></a><a name="p1118994173093533"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1075389659093533"><a name="p1075389659093533"></a><a name="p1075389659093533"></a>void&nbsp;</p>
<p id="p433349127093533"><a name="p433349127093533"></a><a name="p433349127093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1068803623093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p683787276093533"><a name="p683787276093533"></a><a name="p683787276093533"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p360115058093533"><a name="p360115058093533"></a><a name="p360115058093533"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p1170488141093533"><a name="p1170488141093533"></a><a name="p1170488141093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row495205950093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p799948163093533"><a name="p799948163093533"></a><a name="p799948163093533"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1921730924093533"><a name="p1921730924093533"></a><a name="p1921730924093533"></a>virtual void&nbsp;</p>
<p id="p1347411540093533"><a name="p1347411540093533"></a><a name="p1347411540093533"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row1999232673093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1862234686093533"><a name="p1862234686093533"></a><a name="p1862234686093533"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1794661626093533"><a name="p1794661626093533"></a><a name="p1794661626093533"></a>void&nbsp;</p>
<p id="p1380977263093533"><a name="p1380977263093533"></a><a name="p1380977263093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row797287448093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p823943625093533"><a name="p823943625093533"></a><a name="p823943625093533"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2142761199093533"><a name="p2142761199093533"></a><a name="p2142761199093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1399137102093533"><a name="p1399137102093533"></a><a name="p1399137102093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row1886775293093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p898646550093533"><a name="p898646550093533"></a><a name="p898646550093533"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2099685573093533"><a name="p2099685573093533"></a><a name="p2099685573093533"></a>void&nbsp;</p>
<p id="p1185881900093533"><a name="p1185881900093533"></a><a name="p1185881900093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row32139452093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p363465725093533"><a name="p363465725093533"></a><a name="p363465725093533"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2012844878093533"><a name="p2012844878093533"></a><a name="p2012844878093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p549119323093533"><a name="p549119323093533"></a><a name="p549119323093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row147204371093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2013259074093533"><a name="p2013259074093533"></a><a name="p2013259074093533"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1786396086093533"><a name="p1786396086093533"></a><a name="p1786396086093533"></a>virtual void&nbsp;</p>
<p id="p1976895593093533"><a name="p1976895593093533"></a><a name="p1976895593093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1970726334093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p600057408093533"><a name="p600057408093533"></a><a name="p600057408093533"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1869159691093533"><a name="p1869159691093533"></a><a name="p1869159691093533"></a>bool&nbsp;</p>
<p id="p1947577160093533"><a name="p1947577160093533"></a><a name="p1947577160093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1895406245093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1974400341093533"><a name="p1974400341093533"></a><a name="p1974400341093533"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p920149520093533"><a name="p920149520093533"></a><a name="p920149520093533"></a>void&nbsp;</p>
<p id="p1991290163093533"><a name="p1991290163093533"></a><a name="p1991290163093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1958151711093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1311318737093533"><a name="p1311318737093533"></a><a name="p1311318737093533"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p920727924093533"><a name="p920727924093533"></a><a name="p920727924093533"></a>bool&nbsp;</p>
<p id="p1214616198093533"><a name="p1214616198093533"></a><a name="p1214616198093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row310022021093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p396184010093533"><a name="p396184010093533"></a><a name="p396184010093533"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1501067124093533"><a name="p1501067124093533"></a><a name="p1501067124093533"></a>void&nbsp;</p>
<p id="p279839479093533"><a name="p279839479093533"></a><a name="p279839479093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row466547268093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1998740529093533"><a name="p1998740529093533"></a><a name="p1998740529093533"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763784538093533"><a name="p763784538093533"></a><a name="p763784538093533"></a>bool&nbsp;</p>
<p id="p854614865093533"><a name="p854614865093533"></a><a name="p854614865093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row784514775093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1573481896093533"><a name="p1573481896093533"></a><a name="p1573481896093533"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1748964772093533"><a name="p1748964772093533"></a><a name="p1748964772093533"></a>void&nbsp;</p>
<p id="p478428635093533"><a name="p478428635093533"></a><a name="p478428635093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1748661906093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2103300689093533"><a name="p2103300689093533"></a><a name="p2103300689093533"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1704861634093533"><a name="p1704861634093533"></a><a name="p1704861634093533"></a>bool&nbsp;</p>
<p id="p1803103304093533"><a name="p1803103304093533"></a><a name="p1803103304093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row197713034093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1650264950093533"><a name="p1650264950093533"></a><a name="p1650264950093533"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p403819658093533"><a name="p403819658093533"></a><a name="p403819658093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p213817654093533"><a name="p213817654093533"></a><a name="p213817654093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1876924780093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1718072325093533"><a name="p1718072325093533"></a><a name="p1718072325093533"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1682139968093533"><a name="p1682139968093533"></a><a name="p1682139968093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1685607938093533"><a name="p1685607938093533"></a><a name="p1685607938093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1095725940093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p225391428093533"><a name="p225391428093533"></a><a name="p225391428093533"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1950334373093533"><a name="p1950334373093533"></a><a name="p1950334373093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1018086542093533"><a name="p1018086542093533"></a><a name="p1018086542093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row996197099093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1759786988093533"><a name="p1759786988093533"></a><a name="p1759786988093533"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p469266118093533"><a name="p469266118093533"></a><a name="p469266118093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p468944092093533"><a name="p468944092093533"></a><a name="p468944092093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1386759505093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1012359584093533"><a name="p1012359584093533"></a><a name="p1012359584093533"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p696877341093533"><a name="p696877341093533"></a><a name="p696877341093533"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1299880082093533"><a name="p1299880082093533"></a><a name="p1299880082093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1545121699093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1997956419093533"><a name="p1997956419093533"></a><a name="p1997956419093533"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1016204865093533"><a name="p1016204865093533"></a><a name="p1016204865093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1329907447093533"><a name="p1329907447093533"></a><a name="p1329907447093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row157176597093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1107824816093533"><a name="p1107824816093533"></a><a name="p1107824816093533"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1692254328093533"><a name="p1692254328093533"></a><a name="p1692254328093533"></a>void&nbsp;</p>
<p id="p64467971093533"><a name="p64467971093533"></a><a name="p64467971093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1509246232093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1773757796093533"><a name="p1773757796093533"></a><a name="p1773757796093533"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2027140342093533"><a name="p2027140342093533"></a><a name="p2027140342093533"></a>virtual void&nbsp;</p>
<p id="p816905093093533"><a name="p816905093093533"></a><a name="p816905093093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1973732451093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p236409821093533"><a name="p236409821093533"></a><a name="p236409821093533"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1671949456093533"><a name="p1671949456093533"></a><a name="p1671949456093533"></a>virtual void&nbsp;</p>
<p id="p1190871052093533"><a name="p1190871052093533"></a><a name="p1190871052093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row2048192599093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p716375938093533"><a name="p716375938093533"></a><a name="p716375938093533"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p92331035093533"><a name="p92331035093533"></a><a name="p92331035093533"></a>int16_t&nbsp;</p>
<p id="p719024593093533"><a name="p719024593093533"></a><a name="p719024593093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row2001718554093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p702602826093533"><a name="p702602826093533"></a><a name="p702602826093533"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1454541622093533"><a name="p1454541622093533"></a><a name="p1454541622093533"></a>virtual void&nbsp;</p>
<p id="p144377181093533"><a name="p144377181093533"></a><a name="p144377181093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row482579537093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390658878093533"><a name="p390658878093533"></a><a name="p390658878093533"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1261585104093533"><a name="p1261585104093533"></a><a name="p1261585104093533"></a>int16_t&nbsp;</p>
<p id="p76992364093533"><a name="p76992364093533"></a><a name="p76992364093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1334909741093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977768678093533"><a name="p977768678093533"></a><a name="p977768678093533"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p608130439093533"><a name="p608130439093533"></a><a name="p608130439093533"></a>virtual void&nbsp;</p>
<p id="p291237091093533"><a name="p291237091093533"></a><a name="p291237091093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row301819597093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p947902286093533"><a name="p947902286093533"></a><a name="p947902286093533"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1899301450093533"><a name="p1899301450093533"></a><a name="p1899301450093533"></a>virtual void&nbsp;</p>
<p id="p364978436093533"><a name="p364978436093533"></a><a name="p364978436093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row559911349093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1628977847093533"><a name="p1628977847093533"></a><a name="p1628977847093533"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1648754858093533"><a name="p1648754858093533"></a><a name="p1648754858093533"></a>bool&nbsp;</p>
<p id="p1284966826093533"><a name="p1284966826093533"></a><a name="p1284966826093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1102430222093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1647075681093533"><a name="p1647075681093533"></a><a name="p1647075681093533"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1728415975093533"><a name="p1728415975093533"></a><a name="p1728415975093533"></a>void&nbsp;</p>
<p id="p1773347677093533"><a name="p1773347677093533"></a><a name="p1773347677093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row2131146391093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p312154089093533"><a name="p312154089093533"></a><a name="p312154089093533"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1843992912093533"><a name="p1843992912093533"></a><a name="p1843992912093533"></a>void&nbsp;</p>
<p id="p136722566093533"><a name="p136722566093533"></a><a name="p136722566093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1514610486093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1765903111093533"><a name="p1765903111093533"></a><a name="p1765903111093533"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p272829869093533"><a name="p272829869093533"></a><a name="p272829869093533"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p831592008093533"><a name="p831592008093533"></a><a name="p831592008093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row198065620093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p64603747093533"><a name="p64603747093533"></a><a name="p64603747093533"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p224319409093533"><a name="p224319409093533"></a><a name="p224319409093533"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p477828163093533"><a name="p477828163093533"></a><a name="p477828163093533"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row2084948254093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p390126173093533"><a name="p390126173093533"></a><a name="p390126173093533"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1521019610093533"><a name="p1521019610093533"></a><a name="p1521019610093533"></a>void&nbsp;</p>
<p id="p214607473093533"><a name="p214607473093533"></a><a name="p214607473093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row813067178093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1520075514093533"><a name="p1520075514093533"></a><a name="p1520075514093533"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p427561586093533"><a name="p427561586093533"></a><a name="p427561586093533"></a>const char *&nbsp;</p>
<p id="p1645681494093533"><a name="p1645681494093533"></a><a name="p1645681494093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row745745328093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p725496216093533"><a name="p725496216093533"></a><a name="p725496216093533"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901572217093533"><a name="p1901572217093533"></a><a name="p1901572217093533"></a>void&nbsp;</p>
<p id="p1951188177093533"><a name="p1951188177093533"></a><a name="p1951188177093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row72339458093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p676032411093533"><a name="p676032411093533"></a><a name="p676032411093533"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p339158854093533"><a name="p339158854093533"></a><a name="p339158854093533"></a>int16_t&nbsp;</p>
<p id="p942118649093533"><a name="p942118649093533"></a><a name="p942118649093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1520852185093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1431340397093533"><a name="p1431340397093533"></a><a name="p1431340397093533"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1278812724093533"><a name="p1278812724093533"></a><a name="p1278812724093533"></a>virtual void&nbsp;</p>
<p id="p2132496865093533"><a name="p2132496865093533"></a><a name="p2132496865093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1952683935093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1451871955093533"><a name="p1451871955093533"></a><a name="p1451871955093533"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p974480423093533"><a name="p974480423093533"></a><a name="p974480423093533"></a>void&nbsp;</p>
<p id="p277676824093533"><a name="p277676824093533"></a><a name="p277676824093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1954142274093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p817015569093533"><a name="p817015569093533"></a><a name="p817015569093533"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2108171165093533"><a name="p2108171165093533"></a><a name="p2108171165093533"></a>void&nbsp;</p>
<p id="p973250706093533"><a name="p973250706093533"></a><a name="p973250706093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1325288632093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2089686989093533"><a name="p2089686989093533"></a><a name="p2089686989093533"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1811343947093533"><a name="p1811343947093533"></a><a name="p1811343947093533"></a>void&nbsp;</p>
<p id="p700560032093533"><a name="p700560032093533"></a><a name="p700560032093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1396909273093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2068146553093533"><a name="p2068146553093533"></a><a name="p2068146553093533"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1598996578093533"><a name="p1598996578093533"></a><a name="p1598996578093533"></a>void&nbsp;</p>
<p id="p1002462771093533"><a name="p1002462771093533"></a><a name="p1002462771093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row2125298507093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1936636170093533"><a name="p1936636170093533"></a><a name="p1936636170093533"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p341909173093533"><a name="p341909173093533"></a><a name="p341909173093533"></a>void&nbsp;</p>
<p id="p1962652963093533"><a name="p1962652963093533"></a><a name="p1962652963093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row533114018093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p755184471093533"><a name="p755184471093533"></a><a name="p755184471093533"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1053014900093533"><a name="p1053014900093533"></a><a name="p1053014900093533"></a>void&nbsp;</p>
<p id="p1004487033093533"><a name="p1004487033093533"></a><a name="p1004487033093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row454541955093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1939205351093533"><a name="p1939205351093533"></a><a name="p1939205351093533"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1293204196093533"><a name="p1293204196093533"></a><a name="p1293204196093533"></a>void&nbsp;</p>
<p id="p400623108093533"><a name="p400623108093533"></a><a name="p400623108093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row899744202093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1733727525093533"><a name="p1733727525093533"></a><a name="p1733727525093533"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p180571765093533"><a name="p180571765093533"></a><a name="p180571765093533"></a>void&nbsp;</p>
<p id="p1817288203093533"><a name="p1817288203093533"></a><a name="p1817288203093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row920458469093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298180078093533"><a name="p298180078093533"></a><a name="p298180078093533"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p970676114093533"><a name="p970676114093533"></a><a name="p970676114093533"></a>void&nbsp;</p>
<p id="p1774019820093533"><a name="p1774019820093533"></a><a name="p1774019820093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1692144582093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1828101564093533"><a name="p1828101564093533"></a><a name="p1828101564093533"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2132244995093533"><a name="p2132244995093533"></a><a name="p2132244995093533"></a>void&nbsp;</p>
<p id="p1130865549093533"><a name="p1130865549093533"></a><a name="p1130865549093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1554483413093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1221306997093533"><a name="p1221306997093533"></a><a name="p1221306997093533"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p703554649093533"><a name="p703554649093533"></a><a name="p703554649093533"></a>void&nbsp;</p>
<p id="p276911115093533"><a name="p276911115093533"></a><a name="p276911115093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row121521401093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1073481692093533"><a name="p1073481692093533"></a><a name="p1073481692093533"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1397026902093533"><a name="p1397026902093533"></a><a name="p1397026902093533"></a>void&nbsp;</p>
<p id="p263217683093533"><a name="p263217683093533"></a><a name="p263217683093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row103417859093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1305310506093533"><a name="p1305310506093533"></a><a name="p1305310506093533"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908778205093533"><a name="p908778205093533"></a><a name="p908778205093533"></a>void&nbsp;</p>
<p id="p1323346954093533"><a name="p1323346954093533"></a><a name="p1323346954093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row573340954093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1150725829093533"><a name="p1150725829093533"></a><a name="p1150725829093533"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p839916397093533"><a name="p839916397093533"></a><a name="p839916397093533"></a>void&nbsp;</p>
<p id="p1157747870093533"><a name="p1157747870093533"></a><a name="p1157747870093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1881724962093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1529203608093533"><a name="p1529203608093533"></a><a name="p1529203608093533"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2108157346093533"><a name="p2108157346093533"></a><a name="p2108157346093533"></a>void&nbsp;</p>
<p id="p861678531093533"><a name="p861678531093533"></a><a name="p861678531093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row8966096093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p109311558093533"><a name="p109311558093533"></a><a name="p109311558093533"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p982406911093533"><a name="p982406911093533"></a><a name="p982406911093533"></a>virtual void&nbsp;</p>
<p id="p1864831166093533"><a name="p1864831166093533"></a><a name="p1864831166093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1890681035093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p553372159093533"><a name="p553372159093533"></a><a name="p553372159093533"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1036621777093533"><a name="p1036621777093533"></a><a name="p1036621777093533"></a>virtual void&nbsp;</p>
<p id="p129894332093533"><a name="p129894332093533"></a><a name="p129894332093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1694688682093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1079954426093533"><a name="p1079954426093533"></a><a name="p1079954426093533"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p235735545093533"><a name="p235735545093533"></a><a name="p235735545093533"></a>virtual int64_t&nbsp;</p>
<p id="p2075296358093533"><a name="p2075296358093533"></a><a name="p2075296358093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row540327301093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1894404161093533"><a name="p1894404161093533"></a><a name="p1894404161093533"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1809084297093533"><a name="p1809084297093533"></a><a name="p1809084297093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1649322843093533"><a name="p1649322843093533"></a><a name="p1649322843093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1957704449093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p469009046093533"><a name="p469009046093533"></a><a name="p469009046093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1162805837093533"><a name="p1162805837093533"></a><a name="p1162805837093533"></a>void *&nbsp;</p>
<p id="p1601993560093533"><a name="p1601993560093533"></a><a name="p1601993560093533"></a>Overrides the <strong id="b865372407093533"><a name="b865372407093533"></a><a name="b865372407093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row2097732246093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1747384613093533"><a name="p1747384613093533"></a><a name="p1747384613093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p395372421093533"><a name="p395372421093533"></a><a name="p395372421093533"></a>void&nbsp;</p>
<p id="p507407681093533"><a name="p507407681093533"></a><a name="p507407681093533"></a>Overrides the <strong id="b559632531093533"><a name="b559632531093533"></a><a name="b559632531093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

