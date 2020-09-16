# OHOS::Paint<a name="ZH-CN_TOPIC_0000001055078161"></a>

## **Overview**<a name="section949459544093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines the basic styles of graphs drawn on canvases. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1533100702093533"></a>

## Public Types<a name="pub-types"></a>

<a name="table1495013338093533"></a>
<table><thead align="left"><tr id="row170699735093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p604231729093533"><a name="p604231729093533"></a><a name="p604231729093533"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1088323455093533"><a name="p1088323455093533"></a><a name="p1088323455093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2118027505093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p7077811093533"><a name="p7077811093533"></a><a name="p7077811093533"></a><a href="Graphic.md#ga548320a469b7862fa416af062cad5d7a">PaintStyle</a> { <a href="Graphic.md#gga548320a469b7862fa416af062cad5d7aa16a9f85a0cca54cb2e20bb58a6a41a41">STROKE_STYLE</a> = 1, <a href="Graphic.md#gga548320a469b7862fa416af062cad5d7aa706e9d250b4f9ef43008dcd61eb67bb6">FILL_STYLE</a>, <a href="Graphic.md#gga548320a469b7862fa416af062cad5d7aa30415cae54bf38e3275e847b5ab3ef1c">STROKE_FILL_STYLE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p336463940093533"><a name="p336463940093533"></a><a name="p336463940093533"></a>Enumerates paint styles of a closed graph. The styles are invalid for non-closed graphs. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1012556315093533"></a>
<table><thead align="left"><tr id="row289806939093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1039796090093533"><a name="p1039796090093533"></a><a name="p1039796090093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2071691597093533"><a name="p2071691597093533"></a><a name="p2071691597093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row494731722093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p269647611093533"><a name="p269647611093533"></a><a name="p269647611093533"></a><a href="Graphic.md#ga68ecc0cb6bc379284fd1fbaebb8dcfcd">Paint</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1235137873093533"><a name="p1235137873093533"></a><a name="p1235137873093533"></a>&nbsp;</p>
<p id="p1955461605093533"><a name="p1955461605093533"></a><a name="p1955461605093533"></a>A constructor used to create a <strong id="b1676680704093533"><a name="b1676680704093533"></a><a name="b1676680704093533"></a><a href="OHOS-Paint.md">Paint</a></strong> instance. </p>
</td>
</tr>
<tr id="row226283935093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1510051207093533"><a name="p1510051207093533"></a><a name="p1510051207093533"></a><a href="Graphic.md#ga53f5ef8053f9e468a2fcf6c81449d16d">~Paint</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2081802026093533"><a name="p2081802026093533"></a><a name="p2081802026093533"></a>virtual&nbsp;</p>
<p id="p1646694060093533"><a name="p1646694060093533"></a><a name="p1646694060093533"></a>A destructor used to delete the <strong id="b1061702916093533"><a name="b1061702916093533"></a><a name="b1061702916093533"></a><a href="OHOS-Paint.md">Paint</a></strong> instance. </p>
</td>
</tr>
<tr id="row997162200093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1085372359093533"><a name="p1085372359093533"></a><a name="p1085372359093533"></a><a href="Graphic.md#gab93dc15f466a656150e62d7620d34333">SetStyle</a> (<a href="Graphic.md#ga548320a469b7862fa416af062cad5d7a">PaintStyle</a> style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p544580873093533"><a name="p544580873093533"></a><a name="p544580873093533"></a>void&nbsp;</p>
<p id="p1228838515093533"><a name="p1228838515093533"></a><a name="p1228838515093533"></a>Sets the paint style of a closed graph. </p>
</td>
</tr>
<tr id="row1509174467093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1255621320093533"><a name="p1255621320093533"></a><a name="p1255621320093533"></a><a href="Graphic.md#ga18429dcf1a0dfbe0bf3e5718efa65128">GetStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2007401812093533"><a name="p2007401812093533"></a><a name="p2007401812093533"></a><a href="Graphic.md#ga548320a469b7862fa416af062cad5d7a">PaintStyle</a>&nbsp;</p>
<p id="p1810297185093533"><a name="p1810297185093533"></a><a name="p1810297185093533"></a>Obtains the paint style of a closed graph. </p>
</td>
</tr>
<tr id="row1662607079093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1561031387093533"><a name="p1561031387093533"></a><a name="p1561031387093533"></a><a href="Graphic.md#gad56b6b014e1d061ba93ba8e6c135b90a">SetStrokeWidth</a> (uint16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p596417505093533"><a name="p596417505093533"></a><a name="p596417505093533"></a>void&nbsp;</p>
<p id="p196820906093533"><a name="p196820906093533"></a><a name="p196820906093533"></a>Sets the width of a line or border. </p>
</td>
</tr>
<tr id="row1680508838093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p974829459093533"><a name="p974829459093533"></a><a name="p974829459093533"></a><a href="Graphic.md#gaf8420a460f4a21c9208674e07893c3f0">GetStrokeWidth</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p17461284093533"><a name="p17461284093533"></a><a name="p17461284093533"></a>uint16_t&nbsp;</p>
<p id="p1493156901093533"><a name="p1493156901093533"></a><a name="p1493156901093533"></a>Obtains the width of a line or border. </p>
</td>
</tr>
<tr id="row1417081462093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p758826169093533"><a name="p758826169093533"></a><a name="p758826169093533"></a><a href="Graphic.md#gaff7464c7456b1e7caf9464ff61ab2527">SetStrokeColor</a> (<a href="OHOS-Color32.md">ColorType</a> color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1536468117093533"><a name="p1536468117093533"></a><a name="p1536468117093533"></a>void&nbsp;</p>
<p id="p1855801003093533"><a name="p1855801003093533"></a><a name="p1855801003093533"></a>Sets the color of a line or border. </p>
</td>
</tr>
<tr id="row1983377804093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1467821185093533"><a name="p1467821185093533"></a><a name="p1467821185093533"></a><a href="Graphic.md#gaf9dba05cf9c9f91853a523d961e76fb1">GetStrokeColor</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p492984223093533"><a name="p492984223093533"></a><a name="p492984223093533"></a><a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1838132441093533"><a name="p1838132441093533"></a><a name="p1838132441093533"></a>Obtains the color of a line or border. </p>
</td>
</tr>
<tr id="row633607110093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p570039808093533"><a name="p570039808093533"></a><a name="p570039808093533"></a><a href="Graphic.md#gab1b0e3a5e21ce2ec8454311ed31956ae">SetFillColor</a> (<a href="OHOS-Color32.md">ColorType</a> color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p966239095093533"><a name="p966239095093533"></a><a name="p966239095093533"></a>void&nbsp;</p>
<p id="p1741853917093533"><a name="p1741853917093533"></a><a name="p1741853917093533"></a>Sets fill color. </p>
</td>
</tr>
<tr id="row633787009093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2024683585093533"><a name="p2024683585093533"></a><a name="p2024683585093533"></a><a href="Graphic.md#gadc1b88c39670f103e0c84a089e2178cf">GetFillColor</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p808970748093533"><a name="p808970748093533"></a><a name="p808970748093533"></a><a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1080130885093533"><a name="p1080130885093533"></a><a name="p1080130885093533"></a>Obtains the fill color. </p>
</td>
</tr>
<tr id="row353025929093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p554293158093533"><a name="p554293158093533"></a><a name="p554293158093533"></a><a href="Graphic.md#gacd329fb89bbf6f0e3fd4f9a61f4ce60f">SetOpacity</a> (uint8_t opacity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1716678209093533"><a name="p1716678209093533"></a><a name="p1716678209093533"></a>void&nbsp;</p>
<p id="p605426009093533"><a name="p605426009093533"></a><a name="p605426009093533"></a>Sets the opacity. </p>
</td>
</tr>
<tr id="row602025469093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p768456195093533"><a name="p768456195093533"></a><a name="p768456195093533"></a><a href="Graphic.md#ga3a47fccd734ec0e79af89bedacdd4357">GetOpacity</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p404854759093533"><a name="p404854759093533"></a><a name="p404854759093533"></a>uint8_t&nbsp;</p>
<p id="p1013032937093533"><a name="p1013032937093533"></a><a name="p1013032937093533"></a>Obtains the opacity. </p>
</td>
</tr>
<tr id="row1451061659093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1619179228093533"><a name="p1619179228093533"></a><a name="p1619179228093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p942148298093533"><a name="p942148298093533"></a><a name="p942148298093533"></a>void *&nbsp;</p>
<p id="p1491605720093533"><a name="p1491605720093533"></a><a name="p1491605720093533"></a>Overrides the <strong id="b805620856093533"><a name="b805620856093533"></a><a name="b805620856093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1815073540093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p154464567093533"><a name="p154464567093533"></a><a name="p154464567093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452453274093533"><a name="p1452453274093533"></a><a name="p1452453274093533"></a>void&nbsp;</p>
<p id="p775204444093533"><a name="p775204444093533"></a><a name="p775204444093533"></a>Overrides the <strong id="b747598070093533"><a name="b747598070093533"></a><a name="b747598070093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

