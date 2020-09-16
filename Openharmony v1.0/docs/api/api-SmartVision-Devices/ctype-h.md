# ctype.h<a name="ZH-CN_TOPIC_0000001054948031"></a>

## **Overview**<a name="section2081593650084829"></a>

**Related Modules:**

[UTILS](UTILS.md)

**Description:**

Provides functions used for parameter identification. 

You can use the functions in this file to perform the mathematical operations required during development, for example, check whether the passed parameter is an alphabetic character, a blank character, not a number \(NaN\), a control character, or a decimal digit. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section138459077084829"></a>

## Macros<a name="define-members"></a>

<a name="table1892904380084829"></a>
<table><thead align="left"><tr id="row1275595110084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1328069915084829"><a name="p1328069915084829"></a><a name="p1328069915084829"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1699955765084829"><a name="p1699955765084829"></a><a name="p1699955765084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row413606838084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1199321498084829"><a name="p1199321498084829"></a><a name="p1199321498084829"></a><a href="UTILS.md#ga803da2fa3d4650c493068eb474e5e874">_tolower</a>(a)&nbsp;&nbsp;&nbsp;((a)|0x20)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p792760953084829"><a name="p792760953084829"></a><a name="p792760953084829"></a>Converts an uppercase letter to its lowercase equivalent. </p>
</td>
</tr>
<tr id="row1086264725084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1383033970084829"><a name="p1383033970084829"></a><a name="p1383033970084829"></a><a href="UTILS.md#ga2a220adaae919f631f86e4ee91667ac2">_toupper</a>(a)&nbsp;&nbsp;&nbsp;((a)&amp;0x5f)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p985300697084829"><a name="p985300697084829"></a><a name="p985300697084829"></a>Converts a lowercase letter to its uppercase equivalent. </p>
</td>
</tr>
<tr id="row555321676084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p434422089084829"><a name="p434422089084829"></a><a name="p434422089084829"></a><a href="UTILS.md#ga325ce1f1d55d5b154a914a37b1094cf2">isascii</a>(a)&nbsp;&nbsp;&nbsp;(0 ? isascii(a) : (unsigned)(a) &lt; 128)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1139875360084829"><a name="p1139875360084829"></a><a name="p1139875360084829"></a>Checks whether a parameter is an ASCII character. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1848411846084829"></a>
<table><thead align="left"><tr id="row343333518084829"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1795588026084829"><a name="p1795588026084829"></a><a name="p1795588026084829"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1537138260084829"><a name="p1537138260084829"></a><a name="p1537138260084829"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row564714636084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1672674877084829"><a name="p1672674877084829"></a><a name="p1672674877084829"></a><a href="UTILS.md#gadf38e126f73a010f30af76db2a28c6e1">isalnum</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1664744269084829"><a name="p1664744269084829"></a><a name="p1664744269084829"></a>int&nbsp;</p>
<p id="p1580180179084829"><a name="p1580180179084829"></a><a name="p1580180179084829"></a>Checks whether a parameter is an alphabetic character or a decimal digit. </p>
</td>
</tr>
<tr id="row1189960236084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p284012229084829"><a name="p284012229084829"></a><a name="p284012229084829"></a><a href="UTILS.md#ga25908ae63aac2df990634e1ae5bd14d9">isalpha</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p307556846084829"><a name="p307556846084829"></a><a name="p307556846084829"></a>int&nbsp;</p>
<p id="p1178103084829"><a name="p1178103084829"></a><a name="p1178103084829"></a>Checks whether a parameter is an alphabetic character. </p>
</td>
</tr>
<tr id="row1616767849084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p758802845084829"><a name="p758802845084829"></a><a name="p758802845084829"></a><a href="UTILS.md#gaea4929b1b41f1a6d723e0312b1f050ed">isblank</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1775090659084829"><a name="p1775090659084829"></a><a name="p1775090659084829"></a>int&nbsp;</p>
<p id="p1034394312084829"><a name="p1034394312084829"></a><a name="p1034394312084829"></a>Checks whether a parameter is a blank character (space or tap). </p>
</td>
</tr>
<tr id="row378565358084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2073995200084829"><a name="p2073995200084829"></a><a name="p2073995200084829"></a><a href="UTILS.md#ga0008a4e8e7889734dc1d83297de07158">iscntrl</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p151280872084829"><a name="p151280872084829"></a><a name="p151280872084829"></a>int&nbsp;</p>
<p id="p1136115098084829"><a name="p1136115098084829"></a><a name="p1136115098084829"></a>Checks whether a parameter is a control character. A control character is invisible and does not occupy a printing position on a display. </p>
</td>
</tr>
<tr id="row510879572084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p782553560084829"><a name="p782553560084829"></a><a name="p782553560084829"></a><a href="UTILS.md#ga3fa45b35c8abf67a950b6d3d4063dede">isdigit</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1734765084084829"><a name="p1734765084084829"></a><a name="p1734765084084829"></a>int&nbsp;</p>
<p id="p60721526084829"><a name="p60721526084829"></a><a name="p60721526084829"></a>Checks whether a parameter is a decimal digit (0-9). </p>
</td>
</tr>
<tr id="row970709973084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p908793700084829"><a name="p908793700084829"></a><a name="p908793700084829"></a><a href="UTILS.md#ga49f40fd869fd0c90e4497fda08c89561">isgraph</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p438453666084829"><a name="p438453666084829"></a><a name="p438453666084829"></a>int&nbsp;</p>
<p id="p1772934049084829"><a name="p1772934049084829"></a><a name="p1772934049084829"></a>Checks whether a parameter is any printable character except the space character. </p>
</td>
</tr>
<tr id="row1894970964084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p98307761084829"><a name="p98307761084829"></a><a name="p98307761084829"></a><a href="UTILS.md#ga7b8f652a0423a80922dd89d8829db5f2">islower</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p311312639084829"><a name="p311312639084829"></a><a name="p311312639084829"></a>int&nbsp;</p>
<p id="p393587457084829"><a name="p393587457084829"></a><a name="p393587457084829"></a>Checks whether a parameter is a lowercase letter. </p>
</td>
</tr>
<tr id="row1949499568084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1401649564084829"><a name="p1401649564084829"></a><a name="p1401649564084829"></a><a href="UTILS.md#ga99355d8f0fb41ec43effb95189db0ed4">isprint</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p288664393084829"><a name="p288664393084829"></a><a name="p288664393084829"></a>int&nbsp;</p>
<p id="p224432352084829"><a name="p224432352084829"></a><a name="p224432352084829"></a>Checks whether a parameter is a printable character (including space). </p>
</td>
</tr>
<tr id="row133933503084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p803996257084829"><a name="p803996257084829"></a><a name="p803996257084829"></a><a href="UTILS.md#gaf29554b3ec04ea7684482bffed5dbce6">ispunct</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p69912497084829"><a name="p69912497084829"></a><a name="p69912497084829"></a>int&nbsp;</p>
<p id="p2123086278084829"><a name="p2123086278084829"></a><a name="p2123086278084829"></a>Checks whether a parameter is a punctuation or special character. </p>
</td>
</tr>
<tr id="row311850230084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1872745302084829"><a name="p1872745302084829"></a><a name="p1872745302084829"></a><a href="UTILS.md#ga56be4166e4673843042a548a7f513dbc">isspace</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p404724518084829"><a name="p404724518084829"></a><a name="p404724518084829"></a>int&nbsp;</p>
<p id="p1465079474084829"><a name="p1465079474084829"></a><a name="p1465079474084829"></a>Checks whether a parameter is a space character. </p>
</td>
</tr>
<tr id="row1928813531084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p308597664084829"><a name="p308597664084829"></a><a name="p308597664084829"></a><a href="UTILS.md#gadadd6582d46775aab6a51e29d16d9f77">isupper</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p198818391084829"><a name="p198818391084829"></a><a name="p198818391084829"></a>int&nbsp;</p>
<p id="p1605579028084829"><a name="p1605579028084829"></a><a name="p1605579028084829"></a>Checks whether a parameter is an uppercase letter. </p>
</td>
</tr>
<tr id="row792245744084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1081384744084829"><a name="p1081384744084829"></a><a name="p1081384744084829"></a><a href="UTILS.md#gadaf3aadefe3fc4fb07b6be0d7b880f53">isxdigit</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p151765358084829"><a name="p151765358084829"></a><a name="p151765358084829"></a>int&nbsp;</p>
<p id="p697656425084829"><a name="p697656425084829"></a><a name="p697656425084829"></a>Checks whether a parameter is a hexadecimal digit. </p>
</td>
</tr>
<tr id="row998143355084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1048078279084829"><a name="p1048078279084829"></a><a name="p1048078279084829"></a><a href="UTILS.md#gac79d6114c9df7350cedcd8cf921a6ea4">tolower</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p950024402084829"><a name="p950024402084829"></a><a name="p950024402084829"></a>int&nbsp;</p>
<p id="p1512049536084829"><a name="p1512049536084829"></a><a name="p1512049536084829"></a>Converts an uppercase letter specified by <strong id="b1295891156084829"><a name="b1295891156084829"></a><a name="b1295891156084829"></a>c</strong> to its lowercase equivalent. </p>
</td>
</tr>
<tr id="row1551902378084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p164971435084829"><a name="p164971435084829"></a><a name="p164971435084829"></a><a href="UTILS.md#ga9c2f57ac3865af9006fdbfd5db9fd517">toupper</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327310150084829"><a name="p327310150084829"></a><a name="p327310150084829"></a>int&nbsp;</p>
<p id="p1200928836084829"><a name="p1200928836084829"></a><a name="p1200928836084829"></a>Converts a lowercase letter specified by <strong id="b781513609084829"><a name="b781513609084829"></a><a name="b781513609084829"></a>c</strong> to its uppercase equivalent. </p>
</td>
</tr>
<tr id="row989256895084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p210423956084829"><a name="p210423956084829"></a><a name="p210423956084829"></a><a href="UTILS.md#gad87736859769a262b411b49819bc7a25">isalnum_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p428489460084829"><a name="p428489460084829"></a><a name="p428489460084829"></a>int&nbsp;</p>
<p id="p1535365049084829"><a name="p1535365049084829"></a><a name="p1535365049084829"></a>Checks whether a parameter is an alphabetic character or digit for the specified locale. </p>
</td>
</tr>
<tr id="row1837608564084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p690795351084829"><a name="p690795351084829"></a><a name="p690795351084829"></a><a href="UTILS.md#ga6de33cb463fb34283dc5c7c4c230aec4">isalpha_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1639419285084829"><a name="p1639419285084829"></a><a name="p1639419285084829"></a>int&nbsp;</p>
<p id="p1721398574084829"><a name="p1721398574084829"></a><a name="p1721398574084829"></a>Checks whether a parameter is an alphabetic character for the specified locale. </p>
</td>
</tr>
<tr id="row1724424347084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p70592142084829"><a name="p70592142084829"></a><a name="p70592142084829"></a><a href="UTILS.md#ga650853c2fb9fcf2e9c34ac06e1f6f2d6">isblank_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1681642381084829"><a name="p1681642381084829"></a><a name="p1681642381084829"></a>int&nbsp;</p>
<p id="p971684272084829"><a name="p971684272084829"></a><a name="p971684272084829"></a>Checks whether a parameter is a blank character (including spaces and tabs) for the specified locale. </p>
</td>
</tr>
<tr id="row1103733787084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806550944084829"><a name="p1806550944084829"></a><a name="p1806550944084829"></a><a href="UTILS.md#gad475d7607e183036b0add584bdf61b35">iscntrl_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1441608649084829"><a name="p1441608649084829"></a><a name="p1441608649084829"></a>int&nbsp;</p>
<p id="p788480844084829"><a name="p788480844084829"></a><a name="p788480844084829"></a>Checks whether a parameter is a control character for the specified locale. </p>
</td>
</tr>
<tr id="row1047118644084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1018933569084829"><a name="p1018933569084829"></a><a name="p1018933569084829"></a><a href="UTILS.md#ga378e9ee0e69cbbb9ed948598f9aa920d">isdigit_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p380560837084829"><a name="p380560837084829"></a><a name="p380560837084829"></a>int&nbsp;</p>
<p id="p801273513084829"><a name="p801273513084829"></a><a name="p801273513084829"></a>Checks whether a parameter is a decimal digit for the specified locale. </p>
</td>
</tr>
<tr id="row1450528701084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p337429208084829"><a name="p337429208084829"></a><a name="p337429208084829"></a><a href="UTILS.md#gaab3732d493eec8b0c0a720d90dba210c">isgraph_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946504488084829"><a name="p1946504488084829"></a><a name="p1946504488084829"></a>int&nbsp;</p>
<p id="p1757992548084829"><a name="p1757992548084829"></a><a name="p1757992548084829"></a>Checks whether a parameter is any printable character except the space character for the specified locale. </p>
</td>
</tr>
<tr id="row738438032084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2000575678084829"><a name="p2000575678084829"></a><a name="p2000575678084829"></a><a href="UTILS.md#gad7c9319bbe71c048505cd30da34334ea">islower_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p400842692084829"><a name="p400842692084829"></a><a name="p400842692084829"></a>int&nbsp;</p>
<p id="p1934377001084829"><a name="p1934377001084829"></a><a name="p1934377001084829"></a>Checks whether a parameter is a character of lowercase letters for the specified locale. </p>
</td>
</tr>
<tr id="row962106767084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2673402084829"><a name="p2673402084829"></a><a name="p2673402084829"></a><a href="UTILS.md#gaaae36b62a22be9fa67640255ae77ee0d">isprint_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p112070549084829"><a name="p112070549084829"></a><a name="p112070549084829"></a>int&nbsp;</p>
<p id="p1115177877084829"><a name="p1115177877084829"></a><a name="p1115177877084829"></a>Checks whether a parameter is a printable character (including space) for the specified locale. A printable character is visible and occupies a printing position on a display. </p>
</td>
</tr>
<tr id="row1937731847084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p631629360084829"><a name="p631629360084829"></a><a name="p631629360084829"></a><a href="UTILS.md#gaa04b7d22f0c24a9aa5a6f12e933405f8">ispunct_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p393058294084829"><a name="p393058294084829"></a><a name="p393058294084829"></a>int&nbsp;</p>
<p id="p984429006084829"><a name="p984429006084829"></a><a name="p984429006084829"></a>Checks whether a parameter is a punctuation or special character for the specified locale. </p>
</td>
</tr>
<tr id="row669023866084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1659081520084829"><a name="p1659081520084829"></a><a name="p1659081520084829"></a><a href="UTILS.md#ga6a6e04048d6363a76a333d17cac62f8a">isspace_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p773889540084829"><a name="p773889540084829"></a><a name="p773889540084829"></a>int&nbsp;</p>
<p id="p164919638084829"><a name="p164919638084829"></a><a name="p164919638084829"></a>Checks whether a parameter is a blank character for the specified locale. </p>
</td>
</tr>
<tr id="row1755945704084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p9188225084829"><a name="p9188225084829"></a><a name="p9188225084829"></a><a href="UTILS.md#gae10ce576a584fe302d364196d48332c6">isupper_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p962444113084829"><a name="p962444113084829"></a><a name="p962444113084829"></a>int&nbsp;</p>
<p id="p682716441084829"><a name="p682716441084829"></a><a name="p682716441084829"></a>Checks whether a parameter is a character of uppercase letters for the specified locale. </p>
</td>
</tr>
<tr id="row952255442084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p360963436084829"><a name="p360963436084829"></a><a name="p360963436084829"></a><a href="UTILS.md#ga21c1d42504e331cf330026dcb47dcbe2">isxdigit_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1509325943084829"><a name="p1509325943084829"></a><a name="p1509325943084829"></a>int&nbsp;</p>
<p id="p1992893467084829"><a name="p1992893467084829"></a><a name="p1992893467084829"></a>Checks whether a parameter is a hexadecimal digit for the specified locale. </p>
</td>
</tr>
<tr id="row1231907116084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p804301385084829"><a name="p804301385084829"></a><a name="p804301385084829"></a><a href="UTILS.md#ga1921ca31e425387ecff9c9c7657cd4b7">tolower_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p899018022084829"><a name="p899018022084829"></a><a name="p899018022084829"></a>int&nbsp;</p>
<p id="p1705387514084829"><a name="p1705387514084829"></a><a name="p1705387514084829"></a>Converts an upper letter specified by <strong id="b1428939426084829"><a name="b1428939426084829"></a><a name="b1428939426084829"></a>c</strong> to its lowercase equivalent for the specified locale. </p>
</td>
</tr>
<tr id="row863527602084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p490873678084829"><a name="p490873678084829"></a><a name="p490873678084829"></a><a href="UTILS.md#ga77ed6ccc1ae9841df0fc54ad62860715">toupper_l</a> (int c, locale_t locale)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1715693034084829"><a name="p1715693034084829"></a><a name="p1715693034084829"></a>int&nbsp;</p>
<p id="p408756446084829"><a name="p408756446084829"></a><a name="p408756446084829"></a>Converts a lowercase letter specified by <strong id="b1811096997084829"><a name="b1811096997084829"></a><a name="b1811096997084829"></a>c</strong> to its uppercase equivalent for the specified locale. </p>
</td>
</tr>
<tr id="row1653489401084829"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p824209948084829"><a name="p824209948084829"></a><a name="p824209948084829"></a><a href="UTILS.md#gae2edadcc847fa6a98adc9c485da806de">toascii</a> (int c)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p942659597084829"><a name="p942659597084829"></a><a name="p942659597084829"></a>int&nbsp;</p>
<p id="p1427562111084829"><a name="p1427562111084829"></a><a name="p1427562111084829"></a>Converts a parameter of the integer type to an ASCII code. </p>
</td>
</tr>
</tbody>
</table>

