# OHOS::UISlider<a name="ZH-CN_TOPIC_0000001054918181"></a>

## **Overview**<a name="section274368724093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents a slider. 

Users can drag or click the knob to adjust the progress of an event.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1808434739093534"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table338023826093534"></a>
<table><thead align="left"><tr id="row1119310996093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p395807688093534"><a name="p395807688093534"></a><a name="p395807688093534"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1661764030093534"><a name="p1661764030093534"></a><a name="p1661764030093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1864916235093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1409471127093534"><a name="p1409471127093534"></a><a name="p1409471127093534"></a><a href="OHOS-UISlider-UISliderEventListener.md">UISliderEventListener</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p468367142093534"><a name="p468367142093534"></a><a name="p468367142093534"></a>Represents the listener for a slider change. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1585214876093534"></a>
<table><thead align="left"><tr id="row791346775093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1906814805093534"><a name="p1906814805093534"></a><a name="p1906814805093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p943905150093534"><a name="p943905150093534"></a><a name="p943905150093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row149093545093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1247514410093534"><a name="p1247514410093534"></a><a name="p1247514410093534"></a><a href="Graphic.md#ga67f8d874edcd65b1610117052ceed0a6">UISlider</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p210197667093534"><a name="p210197667093534"></a><a name="p210197667093534"></a>&nbsp;</p>
<p id="p863330241093534"><a name="p863330241093534"></a><a name="p863330241093534"></a>A constructor used to create a <strong id="b289163867093534"><a name="b289163867093534"></a><a name="b289163867093534"></a><a href="OHOS-UISlider.md">UISlider</a></strong> instance. </p>
</td>
</tr>
<tr id="row1336847941093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1075188376093534"><a name="p1075188376093534"></a><a name="p1075188376093534"></a><a href="Graphic.md#ga024c4f15347a0b70920ab745efe8d250">~UISlider</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p299315884093534"><a name="p299315884093534"></a><a name="p299315884093534"></a>virtual&nbsp;</p>
<p id="p2058074666093534"><a name="p2058074666093534"></a><a name="p2058074666093534"></a>A destructor used to delete the <strong id="b1838911630093534"><a name="b1838911630093534"></a><a name="b1838911630093534"></a><a href="OHOS-UISlider.md">UISlider</a></strong> instance. </p>
</td>
</tr>
<tr id="row1884716129093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p996793266093534"><a name="p996793266093534"></a><a name="p996793266093534"></a><a href="Graphic.md#gac2070526833718284148689678c542a9">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p274917602093534"><a name="p274917602093534"></a><a name="p274917602093534"></a>UIViewType&nbsp;</p>
<p id="p1169009413093534"><a name="p1169009413093534"></a><a name="p1169009413093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1236195590093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p819682435093534"><a name="p819682435093534"></a><a name="p819682435093534"></a><a href="Graphic.md#gaf0de71e2d767ccfc3cb41679185a5529">SetKnobWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1117933392093534"><a name="p1117933392093534"></a><a name="p1117933392093534"></a>void&nbsp;</p>
<p id="p1368120380093534"><a name="p1368120380093534"></a><a name="p1368120380093534"></a>Sets the width for this knob. </p>
</td>
</tr>
<tr id="row8242206093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p667049373093534"><a name="p667049373093534"></a><a name="p667049373093534"></a><a href="Graphic.md#ga9bac904abdf8b097778fea5febc1ec00">GetKnobWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695955761093534"><a name="p1695955761093534"></a><a name="p1695955761093534"></a>int16_t&nbsp;</p>
<p id="p1832959638093534"><a name="p1832959638093534"></a><a name="p1832959638093534"></a>Obtains the knob width. </p>
</td>
</tr>
<tr id="row1521423883093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p351169361093534"><a name="p351169361093534"></a><a name="p351169361093534"></a><a href="Graphic.md#ga0685ff139a48f556a2323d06470ad301">SetImage</a> (const <a href="OHOS-ImageInfo.md">ImageInfo</a> *backgroundImage, const <a href="OHOS-ImageInfo.md">ImageInfo</a> *foregroundImage, const <a href="OHOS-ImageInfo.md">ImageInfo</a> *knobImage)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1362586910093534"><a name="p1362586910093534"></a><a name="p1362586910093534"></a>void&nbsp;</p>
<p id="p1033197916093534"><a name="p1033197916093534"></a><a name="p1033197916093534"></a>Sets the images as pixel maps for this slider, including the background, foreground, and knob images. </p>
</td>
</tr>
<tr id="row641201861093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p859467477093534"><a name="p859467477093534"></a><a name="p859467477093534"></a><a href="Graphic.md#gaea596b36fd10c26361666aeda1aca01e">SetImage</a> (const char *backgroundImage, const char *foregroundImage, const char *knobImage)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p359278893093534"><a name="p359278893093534"></a><a name="p359278893093534"></a>void&nbsp;</p>
<p id="p518740956093534"><a name="p518740956093534"></a><a name="p518740956093534"></a>Sets the images for this slider, including the background, foreground, and knob images. </p>
</td>
</tr>
<tr id="row1008031241093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1838125589093534"><a name="p1838125589093534"></a><a name="p1838125589093534"></a><a href="Graphic.md#ga8369feb4c08ec7a01e7200a881acb94b">SetSliderColor</a> (const <a href="OHOS-Color32.md">ColorType</a> backgroundColor, const <a href="OHOS-Color32.md">ColorType</a> foregroundColor, const <a href="OHOS-Color32.md">ColorType</a> knobColor)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p942294947093534"><a name="p942294947093534"></a><a name="p942294947093534"></a>void&nbsp;</p>
<p id="p1362360878093534"><a name="p1362360878093534"></a><a name="p1362360878093534"></a>Sets the colors for this slider, including the background, foreground, and knob colors. </p>
</td>
</tr>
<tr id="row756699298093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1039361064093534"><a name="p1039361064093534"></a><a name="p1039361064093534"></a><a href="Graphic.md#ga977ead9a79667465b107ca0776868712">SetSliderRadius</a> (int16_t backgroundRadius, int16_t foregroundRadius, int16_t knobRadius)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p644649888093534"><a name="p644649888093534"></a><a name="p644649888093534"></a>void&nbsp;</p>
<p id="p907076391093534"><a name="p907076391093534"></a><a name="p907076391093534"></a>Sets the corner radiuses for this slider, including the background, foreground, and knob corner radiuses. </p>
</td>
</tr>
<tr id="row710801850093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p457670237093534"><a name="p457670237093534"></a><a name="p457670237093534"></a><a href="Graphic.md#gac78f9aa2fe12353627a74f87fe49ef4b">SetKnobStyle</a> (const <a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p923921137093534"><a name="p923921137093534"></a><a name="p923921137093534"></a>void&nbsp;</p>
<p id="p754085779093534"><a name="p754085779093534"></a><a name="p754085779093534"></a>Sets the knob style. </p>
</td>
</tr>
<tr id="row1068568436093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p250641870093534"><a name="p250641870093534"></a><a name="p250641870093534"></a><a href="Graphic.md#ga80c30c69e9f565269b09fc9d7ded432e">SetKnobStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1245283661093534"><a name="p1245283661093534"></a><a name="p1245283661093534"></a>void&nbsp;</p>
<p id="p292664629093534"><a name="p292664629093534"></a><a name="p292664629093534"></a>Sets a knob style. </p>
</td>
</tr>
<tr id="row1016530440093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p797289689093534"><a name="p797289689093534"></a><a name="p797289689093534"></a><a href="Graphic.md#gaecf92fe00a7565d034937e89fe2cf1e6">GetKnobStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p355534494093534"><a name="p355534494093534"></a><a name="p355534494093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1108300574093534"><a name="p1108300574093534"></a><a name="p1108300574093534"></a>Obtains the knob style. </p>
</td>
</tr>
<tr id="row564079573093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p147117812093534"><a name="p147117812093534"></a><a name="p147117812093534"></a><a href="Graphic.md#ga1fef57bd5d9a11a9c1946e8efec71b61">GetKnobStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p486114127093534"><a name="p486114127093534"></a><a name="p486114127093534"></a>int64_t&nbsp;</p>
<p id="p1198864594093534"><a name="p1198864594093534"></a><a name="p1198864594093534"></a>Obtains the value of a knob style. </p>
</td>
</tr>
<tr id="row1546186758093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p768609994093534"><a name="p768609994093534"></a><a name="p768609994093534"></a><a href="Graphic.md#ga05029e55d4ccb50cd45f1cd2a53917e4">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p655867684093534"><a name="p655867684093534"></a><a name="p655867684093534"></a>void&nbsp;</p>
<p id="p164021254093534"><a name="p164021254093534"></a><a name="p164021254093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row2130107160093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1090223064093534"><a name="p1090223064093534"></a><a name="p1090223064093534"></a><a href="Graphic.md#ga4481d4453dbf06cc808e4848a814ed7e">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p591318643093534"><a name="p591318643093534"></a><a name="p591318643093534"></a>bool&nbsp;</p>
<p id="p947443531093534"><a name="p947443531093534"></a><a name="p947443531093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row1459457022093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p268906249093534"><a name="p268906249093534"></a><a name="p268906249093534"></a><a href="Graphic.md#gae9136559779057065708312fb62304bb">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p667860555093534"><a name="p667860555093534"></a><a name="p667860555093534"></a>bool&nbsp;</p>
<p id="p616573585093534"><a name="p616573585093534"></a><a name="p616573585093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row1570115975093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858938397093534"><a name="p858938397093534"></a><a name="p858938397093534"></a><a href="Graphic.md#gaf0483e605613ee1789332e67f00f5e2d">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1541826701093534"><a name="p1541826701093534"></a><a name="p1541826701093534"></a>bool&nbsp;</p>
<p id="p1328310798093534"><a name="p1328310798093534"></a><a name="p1328310798093534"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row64985893093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1644378544093534"><a name="p1644378544093534"></a><a name="p1644378544093534"></a><a href="Graphic.md#gad6bd59e05d77868e595d087fd2de5d00">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p276499767093534"><a name="p276499767093534"></a><a name="p276499767093534"></a>void&nbsp;</p>
<p id="p1522452170093534"><a name="p1522452170093534"></a><a name="p1522452170093534"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1417806911093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p143074854093534"><a name="p143074854093534"></a><a name="p143074854093534"></a><a href="Graphic.md#ga1319a5ea74ad822cb12b0f48c19ccb5d">SetSliderEventListener</a> (<a href="OHOS-UISlider-UISliderEventListener.md">UISliderEventListener</a> *listener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1804239747093534"><a name="p1804239747093534"></a><a name="p1804239747093534"></a>void&nbsp;</p>
<p id="p58234582093534"><a name="p58234582093534"></a><a name="p58234582093534"></a>Sets the listener for a slider change. </p>
</td>
</tr>
<tr id="row1084873592093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p299835235093534"><a name="p299835235093534"></a><a name="p299835235093534"></a><a href="Graphic.md#ga315a532a3e0aa658a64d2f7739483f35">UIBoxProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1385229709093534"><a name="p1385229709093534"></a><a name="p1385229709093534"></a>&nbsp;</p>
<p id="p1533665890093534"><a name="p1533665890093534"></a><a name="p1533665890093534"></a>A constructor used to create a <strong id="b1447849613093534"><a name="b1447849613093534"></a><a name="b1447849613093534"></a><a href="OHOS-UIBoxProgress.md">UIBoxProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row2138893240093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p532929157093534"><a name="p532929157093534"></a><a name="p532929157093534"></a><a href="Graphic.md#ga7a5eefc7d4ad253a286444e76146af7f">~UIBoxProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833962911093534"><a name="p833962911093534"></a><a name="p833962911093534"></a>virtual&nbsp;</p>
<p id="p224785451093534"><a name="p224785451093534"></a><a name="p224785451093534"></a>A destructor used to delete the <strong id="b1009961190093534"><a name="b1009961190093534"></a><a name="b1009961190093534"></a><a href="OHOS-UIBoxProgress.md">UIBoxProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row1521889395093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1274476051093534"><a name="p1274476051093534"></a><a name="p1274476051093534"></a><a href="Graphic.md#ga4b3eeb9de2443182480a71cadb23178c">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p835942336093534"><a name="p835942336093534"></a><a name="p835942336093534"></a>void&nbsp;</p>
<p id="p829520518093534"><a name="p829520518093534"></a><a name="p829520518093534"></a>Sets the width for the view holding this progress bar. </p>
</td>
</tr>
<tr id="row312246944093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1999827461093534"><a name="p1999827461093534"></a><a name="p1999827461093534"></a><a href="Graphic.md#ga54299cb7561cee9a03d0fc9d0ddda784">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p514652818093534"><a name="p514652818093534"></a><a name="p514652818093534"></a>void&nbsp;</p>
<p id="p1615349787093534"><a name="p1615349787093534"></a><a name="p1615349787093534"></a>Sets the height for this view. </p>
</td>
</tr>
<tr id="row611194918093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1809258425093534"><a name="p1809258425093534"></a><a name="p1809258425093534"></a><a href="Graphic.md#ga3e2e7d0c37b4945a3f4f456c20cb0177">SetDirection</a> (const <a href="Graphic.md#ga4a7a2c192206c8b18379f42a5fd176eb">Direction</a> &amp;direction)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p337371289093534"><a name="p337371289093534"></a><a name="p337371289093534"></a>void&nbsp;</p>
<p id="p1349066992093534"><a name="p1349066992093534"></a><a name="p1349066992093534"></a>Sets the direction for this progress bar. </p>
</td>
</tr>
<tr id="row90979337093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p459479473093534"><a name="p459479473093534"></a><a name="p459479473093534"></a><a href="Graphic.md#ga493699e8d0e934d7fb3d5502529a1c5e">GetDirection</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1966466370093534"><a name="p1966466370093534"></a><a name="p1966466370093534"></a><a href="Graphic.md#ga4a7a2c192206c8b18379f42a5fd176eb">Direction</a>&nbsp;</p>
<p id="p1161654285093534"><a name="p1161654285093534"></a><a name="p1161654285093534"></a>Obtains the direction of this progress bar. </p>
</td>
</tr>
<tr id="row1041288671093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1265299523093534"><a name="p1265299523093534"></a><a name="p1265299523093534"></a><a href="Graphic.md#gada3cf1819e826ee0aed4a40ef00b91a6">SetValidWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027663386093534"><a name="p1027663386093534"></a><a name="p1027663386093534"></a>void&nbsp;</p>
<p id="p1607072261093534"><a name="p1607072261093534"></a><a name="p1607072261093534"></a>Sets the actual width for this progress bar. </p>
</td>
</tr>
<tr id="row1928201850093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1323052231093534"><a name="p1323052231093534"></a><a name="p1323052231093534"></a><a href="Graphic.md#ga6577d38d85234e08f709dd0ae131b255">GetValidWidth</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p418963338093534"><a name="p418963338093534"></a><a name="p418963338093534"></a>int16_t&nbsp;</p>
<p id="p2030206025093534"><a name="p2030206025093534"></a><a name="p2030206025093534"></a>Obtains the actual width of this progress bar. </p>
</td>
</tr>
<tr id="row1591763724093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1467789636093534"><a name="p1467789636093534"></a><a name="p1467789636093534"></a><a href="Graphic.md#ga6958b8273ad7a5563dfa19267cc3a13c">SetValidHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1808681418093534"><a name="p1808681418093534"></a><a name="p1808681418093534"></a>void&nbsp;</p>
<p id="p14061057093534"><a name="p14061057093534"></a><a name="p14061057093534"></a>Sets the actual height for this progress bar. </p>
</td>
</tr>
<tr id="row460467452093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p581258785093534"><a name="p581258785093534"></a><a name="p581258785093534"></a><a href="Graphic.md#ga1e6c92b20c4931a058c0b7775bf180c9">GetValidHeight</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2054104108093534"><a name="p2054104108093534"></a><a name="p2054104108093534"></a>int16_t&nbsp;</p>
<p id="p507581364093534"><a name="p507581364093534"></a><a name="p507581364093534"></a>Obtains the actual height of this progress bar. </p>
</td>
</tr>
<tr id="row1231781631093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p93376389093534"><a name="p93376389093534"></a><a name="p93376389093534"></a><a href="Graphic.md#ga8f9bfb4f42ee0e094501ff776e3336da">UIAbstractProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1544392158093534"><a name="p1544392158093534"></a><a name="p1544392158093534"></a>&nbsp;</p>
<p id="p1137694770093534"><a name="p1137694770093534"></a><a name="p1137694770093534"></a>A constructor used to create a <strong id="b45918922093534"><a name="b45918922093534"></a><a name="b45918922093534"></a><a href="OHOS-UIAbstractProgress.md">UIAbstractProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row515845220093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p965972390093534"><a name="p965972390093534"></a><a name="p965972390093534"></a><a href="Graphic.md#ga5c1cf7239bf0c0f7d331e63df805b518">~UIAbstractProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1650986487093534"><a name="p1650986487093534"></a><a name="p1650986487093534"></a>virtual&nbsp;</p>
<p id="p760059054093534"><a name="p760059054093534"></a><a name="p760059054093534"></a>A destructor used to delete the <strong id="b1154607323093534"><a name="b1154607323093534"></a><a name="b1154607323093534"></a><a href="OHOS-UIAbstractProgress.md">UIAbstractProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row2041195615093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1885292989093534"><a name="p1885292989093534"></a><a name="p1885292989093534"></a><a href="Graphic.md#gacb680c1ddc9135371676df504dc6c8f2">EnableBackground</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p17758093534"><a name="p17758093534"></a><a name="p17758093534"></a>void&nbsp;</p>
<p id="p925872048093534"><a name="p925872048093534"></a><a name="p925872048093534"></a>Sets whether the background of the progress bar is visible. </p>
</td>
</tr>
<tr id="row325839507093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p76167740093534"><a name="p76167740093534"></a><a name="p76167740093534"></a><a href="Graphic.md#ga5f65014431a6489ffa1d4949f9c4449b">SetValue</a> (int16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p212332923093534"><a name="p212332923093534"></a><a name="p212332923093534"></a>void&nbsp;</p>
<p id="p1028700729093534"><a name="p1028700729093534"></a><a name="p1028700729093534"></a>Sets the current value for this progress bar. </p>
</td>
</tr>
<tr id="row266102910093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1098031007093534"><a name="p1098031007093534"></a><a name="p1098031007093534"></a><a href="Graphic.md#ga6face76aa7972efeb6cbb8f525f23135">GetValue</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p33048430093534"><a name="p33048430093534"></a><a name="p33048430093534"></a>int16_t&nbsp;</p>
<p id="p359337751093534"><a name="p359337751093534"></a><a name="p359337751093534"></a>Obtains the current value of this progress bar. </p>
</td>
</tr>
<tr id="row1089833814093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p496726372093534"><a name="p496726372093534"></a><a name="p496726372093534"></a><a href="Graphic.md#ga089e3875453011499ad33ed89a44a699">SetRange</a> (int16_t rangeMax, int16_t rangeMin)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p945241978093534"><a name="p945241978093534"></a><a name="p945241978093534"></a>void&nbsp;</p>
<p id="p1790897770093534"><a name="p1790897770093534"></a><a name="p1790897770093534"></a>Sets the range for this progress bar. </p>
</td>
</tr>
<tr id="row1693004414093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719286755093534"><a name="p719286755093534"></a><a name="p719286755093534"></a><a href="Graphic.md#ga68ab733afcf4224a799ccad2092d1d23">GetRangeMin</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p236824577093534"><a name="p236824577093534"></a><a name="p236824577093534"></a>int16_t&nbsp;</p>
<p id="p1898585492093534"><a name="p1898585492093534"></a><a name="p1898585492093534"></a>Obtains the minimum value of this progress bar. </p>
</td>
</tr>
<tr id="row1951167849093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1467122577093534"><a name="p1467122577093534"></a><a name="p1467122577093534"></a><a href="Graphic.md#ga1840199f22d5d3e4ef58e41ac8f4febc">GetRangeMax</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p501311633093534"><a name="p501311633093534"></a><a name="p501311633093534"></a>int16_t&nbsp;</p>
<p id="p1014661199093534"><a name="p1014661199093534"></a><a name="p1014661199093534"></a>Obtains the maximum value of this progress bar. </p>
</td>
</tr>
<tr id="row1981240047093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1843818028093534"><a name="p1843818028093534"></a><a name="p1843818028093534"></a><a href="Graphic.md#ga5b3ec363e391f601e12bf937b9cf77db">SetImage</a> (const char *foregroundImage, const char *backgroundImage=nullptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1458380940093534"><a name="p1458380940093534"></a><a name="p1458380940093534"></a>void&nbsp;</p>
<p id="p1319806043093534"><a name="p1319806043093534"></a><a name="p1319806043093534"></a>Sets the image for this progress bar. </p>
</td>
</tr>
<tr id="row166133837093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p884050385093534"><a name="p884050385093534"></a><a name="p884050385093534"></a><a href="Graphic.md#ga10723293ab9e384907dd9dacbc9ad448">SetImage</a> (const <a href="OHOS-ImageInfo.md">ImageInfo</a> *foregroundImage, const <a href="OHOS-ImageInfo.md">ImageInfo</a> *backgroundImage=nullptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1329373661093534"><a name="p1329373661093534"></a><a name="p1329373661093534"></a>void&nbsp;</p>
<p id="p1478318862093534"><a name="p1478318862093534"></a><a name="p1478318862093534"></a>Sets the image as a pixel map for this progress bar. </p>
</td>
</tr>
<tr id="row68507200093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1016289030093534"><a name="p1016289030093534"></a><a name="p1016289030093534"></a><a href="Graphic.md#ga747a29652b441a06d09a97a297aae9bb">SetStep</a> (uint16_t step)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1800873565093534"><a name="p1800873565093534"></a><a name="p1800873565093534"></a>void&nbsp;</p>
<p id="p133950874093534"><a name="p133950874093534"></a><a name="p133950874093534"></a>Sets the step for this progress bar. </p>
</td>
</tr>
<tr id="row660931094093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p896947337093534"><a name="p896947337093534"></a><a name="p896947337093534"></a><a href="Graphic.md#ga9c1678604605a54c2e338d283c46866d">GetStep</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1160045896093534"><a name="p1160045896093534"></a><a name="p1160045896093534"></a>uint16_t&nbsp;</p>
<p id="p1536577608093534"><a name="p1536577608093534"></a><a name="p1536577608093534"></a>Obtains the current step of this progress bar. </p>
</td>
</tr>
<tr id="row1828874918093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1431025284093534"><a name="p1431025284093534"></a><a name="p1431025284093534"></a><a href="Graphic.md#ga6817b5178e93e5f16f2b420cf5a171c1">SetBackgroundStyle</a> (const <a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137463170093534"><a name="p2137463170093534"></a><a name="p2137463170093534"></a>void&nbsp;</p>
<p id="p999485756093534"><a name="p999485756093534"></a><a name="p999485756093534"></a>Sets the background style for this progress bar. </p>
</td>
</tr>
<tr id="row2005232528093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1556972759093534"><a name="p1556972759093534"></a><a name="p1556972759093534"></a><a href="Graphic.md#ga23acea0a42587746e35ec5f3a74af59f">SetBackgroundStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1539260047093534"><a name="p1539260047093534"></a><a name="p1539260047093534"></a>void&nbsp;</p>
<p id="p895232271093534"><a name="p895232271093534"></a><a name="p895232271093534"></a>Sets a background style for this progress bar. </p>
</td>
</tr>
<tr id="row1398634759093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1034432877093534"><a name="p1034432877093534"></a><a name="p1034432877093534"></a><a href="Graphic.md#gac2ca1212c23c11405b12ae0a46c7eff1">GetBackgroundStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p622901828093534"><a name="p622901828093534"></a><a name="p622901828093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1575671978093534"><a name="p1575671978093534"></a><a name="p1575671978093534"></a>Obtains the background style of this progress bar. </p>
</td>
</tr>
<tr id="row770617181093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p293627429093534"><a name="p293627429093534"></a><a name="p293627429093534"></a><a href="Graphic.md#ga946d3f2c39a79d45149118536b2557a9">GetBackgroundStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1040610773093534"><a name="p1040610773093534"></a><a name="p1040610773093534"></a>int64_t&nbsp;</p>
<p id="p1366416555093534"><a name="p1366416555093534"></a><a name="p1366416555093534"></a>Obtains the value of a background style of this progress bar. </p>
</td>
</tr>
<tr id="row1716658255093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478565599093534"><a name="p478565599093534"></a><a name="p478565599093534"></a><a href="Graphic.md#gaccebcfa35f98f9bc6be4bb8cc53eb11c">SetForegroundStyle</a> (const <a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1797146614093534"><a name="p1797146614093534"></a><a name="p1797146614093534"></a>void&nbsp;</p>
<p id="p219868106093534"><a name="p219868106093534"></a><a name="p219868106093534"></a>Sets the foreground style for this progress bar. </p>
</td>
</tr>
<tr id="row1754914593093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p396204466093534"><a name="p396204466093534"></a><a name="p396204466093534"></a><a href="Graphic.md#gae6386ca25603e42f06087f6b2ef65bae">SetForegroundStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1659611329093534"><a name="p1659611329093534"></a><a name="p1659611329093534"></a>void&nbsp;</p>
<p id="p1154693830093534"><a name="p1154693830093534"></a><a name="p1154693830093534"></a>Sets a foreground style for this progress bar. </p>
</td>
</tr>
<tr id="row1752255787093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p310667812093534"><a name="p310667812093534"></a><a name="p310667812093534"></a><a href="Graphic.md#gac77f945f375f333f80bd70254b5c1f96">GetForegroundStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p101534368093534"><a name="p101534368093534"></a><a name="p101534368093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1204938167093534"><a name="p1204938167093534"></a><a name="p1204938167093534"></a>Obtains the foreground style of this progress bar. </p>
</td>
</tr>
<tr id="row885821865093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p492225705093534"><a name="p492225705093534"></a><a name="p492225705093534"></a><a href="Graphic.md#ga74cd121dd1794d7e8d905b233bd98217">GetForegroundStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1603727126093534"><a name="p1603727126093534"></a><a name="p1603727126093534"></a>int64_t&nbsp;</p>
<p id="p1159962469093534"><a name="p1159962469093534"></a><a name="p1159962469093534"></a>Obtains the value of a foreground style of this progress bar. </p>
</td>
</tr>
<tr id="row307101543093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1702968877093534"><a name="p1702968877093534"></a><a name="p1702968877093534"></a><a href="Graphic.md#gabdc0eb4d279212ea7c3ea7a1f9a85e13">SetCapType</a> (<a href="Graphic.md#ga2db3928cdf793f4950245a6841dd43d6">CapType</a> cap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1102720405093534"><a name="p1102720405093534"></a><a name="p1102720405093534"></a>void&nbsp;</p>
<p id="p657359014093534"><a name="p657359014093534"></a><a name="p657359014093534"></a>Sets the type of caps on the background and foreground of the progress bar. </p>
</td>
</tr>
<tr id="row1447438733093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p441881796093534"><a name="p441881796093534"></a><a name="p441881796093534"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2017333908093534"><a name="p2017333908093534"></a><a name="p2017333908093534"></a>&nbsp;</p>
<p id="p1075851161093534"><a name="p1075851161093534"></a><a name="p1075851161093534"></a>A default constructor used to create an <strong id="b1995540210093534"><a name="b1995540210093534"></a><a name="b1995540210093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row382707216093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p988422912093534"><a name="p988422912093534"></a><a name="p988422912093534"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p965147951093534"><a name="p965147951093534"></a><a name="p965147951093534"></a>&nbsp;</p>
<p id="p892868221093534"><a name="p892868221093534"></a><a name="p892868221093534"></a>A constructor used to create an <strong id="b1062245739093534"><a name="b1062245739093534"></a><a name="b1062245739093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1757355142093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1861745225093534"><a name="p1861745225093534"></a><a name="p1861745225093534"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1171556806093534"><a name="p1171556806093534"></a><a name="p1171556806093534"></a>virtual&nbsp;</p>
<p id="p165571007093534"><a name="p165571007093534"></a><a name="p165571007093534"></a>A destructor used to delete the <strong id="b1548253906093534"><a name="b1548253906093534"></a><a name="b1548253906093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row679339599093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p442329006093534"><a name="p442329006093534"></a><a name="p442329006093534"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1353574774093534"><a name="p1353574774093534"></a><a name="p1353574774093534"></a>virtual void&nbsp;</p>
<p id="p693397955093534"><a name="p693397955093534"></a><a name="p693397955093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1726906985093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p162412251093534"><a name="p162412251093534"></a><a name="p162412251093534"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1270355105093534"><a name="p1270355105093534"></a><a name="p1270355105093534"></a>virtual void&nbsp;</p>
<p id="p91739131093534"><a name="p91739131093534"></a><a name="p91739131093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1828745238093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1547519170093534"><a name="p1547519170093534"></a><a name="p1547519170093534"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1660424859093534"><a name="p1660424859093534"></a><a name="p1660424859093534"></a>void&nbsp;</p>
<p id="p1730427681093534"><a name="p1730427681093534"></a><a name="p1730427681093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row566214697093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1945974119093534"><a name="p1945974119093534"></a><a name="p1945974119093534"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p378743886093534"><a name="p378743886093534"></a><a name="p378743886093534"></a>void&nbsp;</p>
<p id="p1837670208093534"><a name="p1837670208093534"></a><a name="p1837670208093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1598781282093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1253940708093534"><a name="p1253940708093534"></a><a name="p1253940708093534"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1822117552093534"><a name="p1822117552093534"></a><a name="p1822117552093534"></a>virtual bool&nbsp;</p>
<p id="p2046311696093534"><a name="p2046311696093534"></a><a name="p2046311696093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1632077156093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p991392312093534"><a name="p991392312093534"></a><a name="p991392312093534"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p430331742093534"><a name="p430331742093534"></a><a name="p430331742093534"></a>virtual bool&nbsp;</p>
<p id="p180492476093534"><a name="p180492476093534"></a><a name="p180492476093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row610964013093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p467095201093534"><a name="p467095201093534"></a><a name="p467095201093534"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2015571918093534"><a name="p2015571918093534"></a><a name="p2015571918093534"></a>virtual void&nbsp;</p>
<p id="p389506517093534"><a name="p389506517093534"></a><a name="p389506517093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row965815855093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2072686954093534"><a name="p2072686954093534"></a><a name="p2072686954093534"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1920002893093534"><a name="p1920002893093534"></a><a name="p1920002893093534"></a>virtual void&nbsp;</p>
<p id="p1628806533093534"><a name="p1628806533093534"></a><a name="p1628806533093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1266781820093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1503960968093534"><a name="p1503960968093534"></a><a name="p1503960968093534"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1211208459093534"><a name="p1211208459093534"></a><a name="p1211208459093534"></a>virtual void&nbsp;</p>
<p id="p1523714863093534"><a name="p1523714863093534"></a><a name="p1523714863093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row654234165093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p709328910093534"><a name="p709328910093534"></a><a name="p709328910093534"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1939609505093534"><a name="p1939609505093534"></a><a name="p1939609505093534"></a>void&nbsp;</p>
<p id="p60435496093534"><a name="p60435496093534"></a><a name="p60435496093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1835378784093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p854881589093534"><a name="p854881589093534"></a><a name="p854881589093534"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278639540093534"><a name="p278639540093534"></a><a name="p278639540093534"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p1202154142093534"><a name="p1202154142093534"></a><a name="p1202154142093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1392191786093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1563578943093534"><a name="p1563578943093534"></a><a name="p1563578943093534"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p417603361093534"><a name="p417603361093534"></a><a name="p417603361093534"></a>void&nbsp;</p>
<p id="p2070445737093534"><a name="p2070445737093534"></a><a name="p2070445737093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row1463330596093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p649781402093534"><a name="p649781402093534"></a><a name="p649781402093534"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p291996458093534"><a name="p291996458093534"></a><a name="p291996458093534"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p93374789093534"><a name="p93374789093534"></a><a name="p93374789093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row893162112093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p508685869093534"><a name="p508685869093534"></a><a name="p508685869093534"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1194440315093534"><a name="p1194440315093534"></a><a name="p1194440315093534"></a>void&nbsp;</p>
<p id="p1775483420093534"><a name="p1775483420093534"></a><a name="p1775483420093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row25095426093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p857373442093534"><a name="p857373442093534"></a><a name="p857373442093534"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p418925213093534"><a name="p418925213093534"></a><a name="p418925213093534"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p1248931829093534"><a name="p1248931829093534"></a><a name="p1248931829093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row543713384093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p584726015093534"><a name="p584726015093534"></a><a name="p584726015093534"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p327097034093534"><a name="p327097034093534"></a><a name="p327097034093534"></a>void&nbsp;</p>
<p id="p1067379432093534"><a name="p1067379432093534"></a><a name="p1067379432093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row266203548093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p336334929093534"><a name="p336334929093534"></a><a name="p336334929093534"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2065481696093534"><a name="p2065481696093534"></a><a name="p2065481696093534"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p1405573539093534"><a name="p1405573539093534"></a><a name="p1405573539093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row667492638093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1748468545093534"><a name="p1748468545093534"></a><a name="p1748468545093534"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p862049284093534"><a name="p862049284093534"></a><a name="p862049284093534"></a>virtual void&nbsp;</p>
<p id="p1954455989093534"><a name="p1954455989093534"></a><a name="p1954455989093534"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row699875374093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p465438056093534"><a name="p465438056093534"></a><a name="p465438056093534"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1999174950093534"><a name="p1999174950093534"></a><a name="p1999174950093534"></a>void&nbsp;</p>
<p id="p1108978572093534"><a name="p1108978572093534"></a><a name="p1108978572093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1799272770093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2070809917093534"><a name="p2070809917093534"></a><a name="p2070809917093534"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1224849273093534"><a name="p1224849273093534"></a><a name="p1224849273093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p2080593975093534"><a name="p2080593975093534"></a><a name="p2080593975093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row783586449093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p484993565093534"><a name="p484993565093534"></a><a name="p484993565093534"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p959847119093534"><a name="p959847119093534"></a><a name="p959847119093534"></a>void&nbsp;</p>
<p id="p298982921093534"><a name="p298982921093534"></a><a name="p298982921093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row345605664093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381675589093534"><a name="p381675589093534"></a><a name="p381675589093534"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p457918204093534"><a name="p457918204093534"></a><a name="p457918204093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p426631484093534"><a name="p426631484093534"></a><a name="p426631484093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1515399841093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1976260497093534"><a name="p1976260497093534"></a><a name="p1976260497093534"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1800084403093534"><a name="p1800084403093534"></a><a name="p1800084403093534"></a>virtual void&nbsp;</p>
<p id="p198955712093534"><a name="p198955712093534"></a><a name="p198955712093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row219592575093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p455444224093534"><a name="p455444224093534"></a><a name="p455444224093534"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1718438474093534"><a name="p1718438474093534"></a><a name="p1718438474093534"></a>bool&nbsp;</p>
<p id="p1814131403093534"><a name="p1814131403093534"></a><a name="p1814131403093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1771047654093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1247667851093534"><a name="p1247667851093534"></a><a name="p1247667851093534"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1493288807093534"><a name="p1493288807093534"></a><a name="p1493288807093534"></a>void&nbsp;</p>
<p id="p1973735191093534"><a name="p1973735191093534"></a><a name="p1973735191093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row921644284093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p683296301093534"><a name="p683296301093534"></a><a name="p683296301093534"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1145840866093534"><a name="p1145840866093534"></a><a name="p1145840866093534"></a>bool&nbsp;</p>
<p id="p336167975093534"><a name="p336167975093534"></a><a name="p336167975093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row407560723093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1948690462093534"><a name="p1948690462093534"></a><a name="p1948690462093534"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1544116780093534"><a name="p1544116780093534"></a><a name="p1544116780093534"></a>void&nbsp;</p>
<p id="p1599130599093534"><a name="p1599130599093534"></a><a name="p1599130599093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1998169012093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298662445093534"><a name="p298662445093534"></a><a name="p298662445093534"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1014529328093534"><a name="p1014529328093534"></a><a name="p1014529328093534"></a>bool&nbsp;</p>
<p id="p228873811093534"><a name="p228873811093534"></a><a name="p228873811093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1900359441093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p221849954093534"><a name="p221849954093534"></a><a name="p221849954093534"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p226283132093534"><a name="p226283132093534"></a><a name="p226283132093534"></a>void&nbsp;</p>
<p id="p1771095365093534"><a name="p1771095365093534"></a><a name="p1771095365093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row164280085093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1896487540093534"><a name="p1896487540093534"></a><a name="p1896487540093534"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p175096983093534"><a name="p175096983093534"></a><a name="p175096983093534"></a>bool&nbsp;</p>
<p id="p820964082093534"><a name="p820964082093534"></a><a name="p820964082093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1200964899093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1602758774093534"><a name="p1602758774093534"></a><a name="p1602758774093534"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1637693288093534"><a name="p1637693288093534"></a><a name="p1637693288093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1029159377093534"><a name="p1029159377093534"></a><a name="p1029159377093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1922203496093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p142287953093534"><a name="p142287953093534"></a><a name="p142287953093534"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1840617116093534"><a name="p1840617116093534"></a><a name="p1840617116093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1316880496093534"><a name="p1316880496093534"></a><a name="p1316880496093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row951892369093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2047756428093534"><a name="p2047756428093534"></a><a name="p2047756428093534"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p915222458093534"><a name="p915222458093534"></a><a name="p915222458093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p889020881093534"><a name="p889020881093534"></a><a name="p889020881093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1967135247093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1390002508093534"><a name="p1390002508093534"></a><a name="p1390002508093534"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1142038436093534"><a name="p1142038436093534"></a><a name="p1142038436093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p526757684093534"><a name="p526757684093534"></a><a name="p526757684093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row850320500093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p944793175093534"><a name="p944793175093534"></a><a name="p944793175093534"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1714475987093534"><a name="p1714475987093534"></a><a name="p1714475987093534"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1703631827093534"><a name="p1703631827093534"></a><a name="p1703631827093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1287652136093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p30360479093534"><a name="p30360479093534"></a><a name="p30360479093534"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1514190717093534"><a name="p1514190717093534"></a><a name="p1514190717093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p644487457093534"><a name="p644487457093534"></a><a name="p644487457093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1808952015093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p299131965093534"><a name="p299131965093534"></a><a name="p299131965093534"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2101209009093534"><a name="p2101209009093534"></a><a name="p2101209009093534"></a>void&nbsp;</p>
<p id="p1803805855093534"><a name="p1803805855093534"></a><a name="p1803805855093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1830365085093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1825165376093534"><a name="p1825165376093534"></a><a name="p1825165376093534"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p478580475093534"><a name="p478580475093534"></a><a name="p478580475093534"></a>virtual int16_t&nbsp;</p>
<p id="p1848599083093534"><a name="p1848599083093534"></a><a name="p1848599083093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1764767840093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969021059093534"><a name="p1969021059093534"></a><a name="p1969021059093534"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p478595626093534"><a name="p478595626093534"></a><a name="p478595626093534"></a>virtual int16_t&nbsp;</p>
<p id="p647520602093534"><a name="p647520602093534"></a><a name="p647520602093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row101288161093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p645745514093534"><a name="p645745514093534"></a><a name="p645745514093534"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1054451160093534"><a name="p1054451160093534"></a><a name="p1054451160093534"></a>virtual void&nbsp;</p>
<p id="p1161158378093534"><a name="p1161158378093534"></a><a name="p1161158378093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row951044545093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p230344864093534"><a name="p230344864093534"></a><a name="p230344864093534"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1626410926093534"><a name="p1626410926093534"></a><a name="p1626410926093534"></a>virtual void&nbsp;</p>
<p id="p1374588263093534"><a name="p1374588263093534"></a><a name="p1374588263093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row383726073093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1131089935093534"><a name="p1131089935093534"></a><a name="p1131089935093534"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p806224207093534"><a name="p806224207093534"></a><a name="p806224207093534"></a>int16_t&nbsp;</p>
<p id="p716465868093534"><a name="p716465868093534"></a><a name="p716465868093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1707174789093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1074317723093534"><a name="p1074317723093534"></a><a name="p1074317723093534"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1039996449093534"><a name="p1039996449093534"></a><a name="p1039996449093534"></a>virtual void&nbsp;</p>
<p id="p1963249762093534"><a name="p1963249762093534"></a><a name="p1963249762093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1199130437093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1115150888093534"><a name="p1115150888093534"></a><a name="p1115150888093534"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p487705839093534"><a name="p487705839093534"></a><a name="p487705839093534"></a>int16_t&nbsp;</p>
<p id="p218432383093534"><a name="p218432383093534"></a><a name="p218432383093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1851727422093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1577304706093534"><a name="p1577304706093534"></a><a name="p1577304706093534"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p222831162093534"><a name="p222831162093534"></a><a name="p222831162093534"></a>virtual void&nbsp;</p>
<p id="p956316140093534"><a name="p956316140093534"></a><a name="p956316140093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row2138201906093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1638414445093534"><a name="p1638414445093534"></a><a name="p1638414445093534"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1426337870093534"><a name="p1426337870093534"></a><a name="p1426337870093534"></a>virtual void&nbsp;</p>
<p id="p1396184656093534"><a name="p1396184656093534"></a><a name="p1396184656093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1457535975093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1969050725093534"><a name="p1969050725093534"></a><a name="p1969050725093534"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p838199695093534"><a name="p838199695093534"></a><a name="p838199695093534"></a>bool&nbsp;</p>
<p id="p1858143852093534"><a name="p1858143852093534"></a><a name="p1858143852093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row1465002185093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1272050443093534"><a name="p1272050443093534"></a><a name="p1272050443093534"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417262232093534"><a name="p1417262232093534"></a><a name="p1417262232093534"></a>void&nbsp;</p>
<p id="p1638070361093534"><a name="p1638070361093534"></a><a name="p1638070361093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1226223211093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p410145881093534"><a name="p410145881093534"></a><a name="p410145881093534"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1157711192093534"><a name="p1157711192093534"></a><a name="p1157711192093534"></a>void&nbsp;</p>
<p id="p1811329562093534"><a name="p1811329562093534"></a><a name="p1811329562093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row28514515093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1206443963093534"><a name="p1206443963093534"></a><a name="p1206443963093534"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p283063568093534"><a name="p283063568093534"></a><a name="p283063568093534"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p669777600093534"><a name="p669777600093534"></a><a name="p669777600093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row940783605093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p524585000093534"><a name="p524585000093534"></a><a name="p524585000093534"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1812355646093534"><a name="p1812355646093534"></a><a name="p1812355646093534"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1941697090093534"><a name="p1941697090093534"></a><a name="p1941697090093534"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row240840292093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1280250628093534"><a name="p1280250628093534"></a><a name="p1280250628093534"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p592749148093534"><a name="p592749148093534"></a><a name="p592749148093534"></a>void&nbsp;</p>
<p id="p1531339914093534"><a name="p1531339914093534"></a><a name="p1531339914093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1586556902093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1204014752093534"><a name="p1204014752093534"></a><a name="p1204014752093534"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p953241151093534"><a name="p953241151093534"></a><a name="p953241151093534"></a>const char *&nbsp;</p>
<p id="p1938044617093534"><a name="p1938044617093534"></a><a name="p1938044617093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row53381100093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1203898894093534"><a name="p1203898894093534"></a><a name="p1203898894093534"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p221218019093534"><a name="p221218019093534"></a><a name="p221218019093534"></a>void&nbsp;</p>
<p id="p1619358124093534"><a name="p1619358124093534"></a><a name="p1619358124093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1737897752093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408572572093534"><a name="p1408572572093534"></a><a name="p1408572572093534"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1640531449093534"><a name="p1640531449093534"></a><a name="p1640531449093534"></a>int16_t&nbsp;</p>
<p id="p806418894093534"><a name="p806418894093534"></a><a name="p806418894093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row611803977093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1209753972093534"><a name="p1209753972093534"></a><a name="p1209753972093534"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p506288559093534"><a name="p506288559093534"></a><a name="p506288559093534"></a>virtual void&nbsp;</p>
<p id="p1662137171093534"><a name="p1662137171093534"></a><a name="p1662137171093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1908807937093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p893154419093534"><a name="p893154419093534"></a><a name="p893154419093534"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p100972626093534"><a name="p100972626093534"></a><a name="p100972626093534"></a>void&nbsp;</p>
<p id="p877199317093534"><a name="p877199317093534"></a><a name="p877199317093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1130703567093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p485059837093534"><a name="p485059837093534"></a><a name="p485059837093534"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1625176044093534"><a name="p1625176044093534"></a><a name="p1625176044093534"></a>void&nbsp;</p>
<p id="p1958705449093534"><a name="p1958705449093534"></a><a name="p1958705449093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1662609417093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p953035981093534"><a name="p953035981093534"></a><a name="p953035981093534"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p711577137093534"><a name="p711577137093534"></a><a name="p711577137093534"></a>void&nbsp;</p>
<p id="p869568665093534"><a name="p869568665093534"></a><a name="p869568665093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1817883214093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1061469214093534"><a name="p1061469214093534"></a><a name="p1061469214093534"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p836430880093534"><a name="p836430880093534"></a><a name="p836430880093534"></a>void&nbsp;</p>
<p id="p1116502140093534"><a name="p1116502140093534"></a><a name="p1116502140093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row748128630093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p392446047093534"><a name="p392446047093534"></a><a name="p392446047093534"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p676911792093534"><a name="p676911792093534"></a><a name="p676911792093534"></a>void&nbsp;</p>
<p id="p1415412302093534"><a name="p1415412302093534"></a><a name="p1415412302093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row2130585371093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p555554496093534"><a name="p555554496093534"></a><a name="p555554496093534"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2000193740093534"><a name="p2000193740093534"></a><a name="p2000193740093534"></a>void&nbsp;</p>
<p id="p1754394627093534"><a name="p1754394627093534"></a><a name="p1754394627093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row1136567177093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p260604374093534"><a name="p260604374093534"></a><a name="p260604374093534"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p518147532093534"><a name="p518147532093534"></a><a name="p518147532093534"></a>void&nbsp;</p>
<p id="p1679166106093534"><a name="p1679166106093534"></a><a name="p1679166106093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row1055420183093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1164936536093534"><a name="p1164936536093534"></a><a name="p1164936536093534"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p751451279093534"><a name="p751451279093534"></a><a name="p751451279093534"></a>void&nbsp;</p>
<p id="p947380618093534"><a name="p947380618093534"></a><a name="p947380618093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row535313195093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2106467482093534"><a name="p2106467482093534"></a><a name="p2106467482093534"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1062936025093534"><a name="p1062936025093534"></a><a name="p1062936025093534"></a>void&nbsp;</p>
<p id="p1369306670093534"><a name="p1369306670093534"></a><a name="p1369306670093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row124410220093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1322399523093534"><a name="p1322399523093534"></a><a name="p1322399523093534"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2072442545093534"><a name="p2072442545093534"></a><a name="p2072442545093534"></a>void&nbsp;</p>
<p id="p1234852639093534"><a name="p1234852639093534"></a><a name="p1234852639093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1375221000093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p795652546093534"><a name="p795652546093534"></a><a name="p795652546093534"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1905585118093534"><a name="p1905585118093534"></a><a name="p1905585118093534"></a>void&nbsp;</p>
<p id="p189333277093534"><a name="p189333277093534"></a><a name="p189333277093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row45159477093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p497017368093534"><a name="p497017368093534"></a><a name="p497017368093534"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1033802532093534"><a name="p1033802532093534"></a><a name="p1033802532093534"></a>void&nbsp;</p>
<p id="p2139659009093534"><a name="p2139659009093534"></a><a name="p2139659009093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row493921902093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1689563079093534"><a name="p1689563079093534"></a><a name="p1689563079093534"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p277726581093534"><a name="p277726581093534"></a><a name="p277726581093534"></a>void&nbsp;</p>
<p id="p61467132093534"><a name="p61467132093534"></a><a name="p61467132093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row483911372093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1640785499093534"><a name="p1640785499093534"></a><a name="p1640785499093534"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p528424582093534"><a name="p528424582093534"></a><a name="p528424582093534"></a>void&nbsp;</p>
<p id="p2056021100093534"><a name="p2056021100093534"></a><a name="p2056021100093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1978717569093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p659419055093534"><a name="p659419055093534"></a><a name="p659419055093534"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1168908979093534"><a name="p1168908979093534"></a><a name="p1168908979093534"></a>void&nbsp;</p>
<p id="p441792713093534"><a name="p441792713093534"></a><a name="p441792713093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row789529057093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1668305427093534"><a name="p1668305427093534"></a><a name="p1668305427093534"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p990269565093534"><a name="p990269565093534"></a><a name="p990269565093534"></a>virtual void&nbsp;</p>
<p id="p1710836340093534"><a name="p1710836340093534"></a><a name="p1710836340093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row2128667125093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2070866067093534"><a name="p2070866067093534"></a><a name="p2070866067093534"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1430112804093534"><a name="p1430112804093534"></a><a name="p1430112804093534"></a>virtual void&nbsp;</p>
<p id="p1787693124093534"><a name="p1787693124093534"></a><a name="p1787693124093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1598342809093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p725117794093534"><a name="p725117794093534"></a><a name="p725117794093534"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1263741139093534"><a name="p1263741139093534"></a><a name="p1263741139093534"></a>virtual int64_t&nbsp;</p>
<p id="p528008046093534"><a name="p528008046093534"></a><a name="p528008046093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1360820150093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1888714090093534"><a name="p1888714090093534"></a><a name="p1888714090093534"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038038531093534"><a name="p1038038531093534"></a><a name="p1038038531093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p661764710093534"><a name="p661764710093534"></a><a name="p661764710093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1161420239093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1882632467093534"><a name="p1882632467093534"></a><a name="p1882632467093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1157039002093534"><a name="p1157039002093534"></a><a name="p1157039002093534"></a>void *&nbsp;</p>
<p id="p1172617381093534"><a name="p1172617381093534"></a><a name="p1172617381093534"></a>Overrides the <strong id="b1052289854093534"><a name="b1052289854093534"></a><a name="b1052289854093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row739335668093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1640896015093534"><a name="p1640896015093534"></a><a name="p1640896015093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1567990198093534"><a name="p1567990198093534"></a><a name="p1567990198093534"></a>void&nbsp;</p>
<p id="p1315047479093534"><a name="p1315047479093534"></a><a name="p1315047479093534"></a>Overrides the <strong id="b2063425309093534"><a name="b2063425309093534"></a><a name="b2063425309093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1573599146093534"></a>
<table><thead align="left"><tr id="row360087968093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p95142839093534"><a name="p95142839093534"></a><a name="p95142839093534"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p817854390093534"><a name="p817854390093534"></a><a name="p817854390093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row494328530093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p686875491093534"><a name="p686875491093534"></a><a name="p686875491093534"></a><a href="Graphic.md#ga4a7a2c192206c8b18379f42a5fd176eb">Direction</a> : uint8_t { <a href="Graphic.md#gga4a7a2c192206c8b18379f42a5fd176eba43cb7d46f0e18f315d43b82024093b51">Direction::DIR_LEFT_TO_RIGHT</a>, <a href="Graphic.md#gga4a7a2c192206c8b18379f42a5fd176eba49e31df5a7fc02ee8c2f85b5e15f0145">Direction::DIR_RIGHT_TO_LEFT</a>, <a href="Graphic.md#gga4a7a2c192206c8b18379f42a5fd176eba68baeaa89ae4576fc3d9ac732f87a116">Direction::DIR_TOP_TO_BOTTOM</a>, <a href="Graphic.md#gga4a7a2c192206c8b18379f42a5fd176eba78b28982b481790c740bc9b2c1292baa">Direction::DIR_BOTTOM_TO_TOP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140835786093534"><a name="p140835786093534"></a><a name="p140835786093534"></a>Enumerates the directions of the progress bar. </p>
</td>
</tr>
</tbody>
</table>

