# OHOS::UIArcLabel<a name="EN-US_TOPIC_0000001055518110"></a>

## **Overview**<a name="section878629493093533"></a>

**Related Modules:**

[Graphic](graphic.md)

**Description:**

Defines functions related to an arc label. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section901717575093533"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table448330235093533"></a>
<table><thead align="left"><tr id="row1147231538093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p905803864093533"><a name="p905803864093533"></a><a name="p905803864093533"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p123411531093533"><a name="p123411531093533"></a><a name="p123411531093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row628187556093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2012904604093533"><a name="p2012904604093533"></a><a name="p2012904604093533"></a><a href="ohos-uiarclabel-arctextinfo.md">ArcTextInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p535900800093533"><a name="p535900800093533"></a><a name="p535900800093533"></a>Stores the attribute information about this arc text to draw. </p>
</td>
</tr>
</tbody>
</table>

## Public Types<a name="pub-types"></a>

<a name="table2113923389093533"></a>
<table><thead align="left"><tr id="row994663744093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p618764570093533"><a name="p618764570093533"></a><a name="p618764570093533"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p26027318093533"><a name="p26027318093533"></a><a name="p26027318093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1337059413093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1821382494093533"><a name="p1821382494093533"></a><a name="p1821382494093533"></a><a href="graphic.md#ga0778527bee4a7ddd8d46395585a5cfb9">TextOrientation</a> : uint8_t { <a href="graphic.md#gga0778527bee4a7ddd8d46395585a5cfb9a554a7418c4c0dafd902ebd377b87c80c">TextOrientation::INSIDE</a>, <a href="graphic.md#gga0778527bee4a7ddd8d46395585a5cfb9a93da25bafef6761717afc6b25c17ea16">TextOrientation::OUTSIDE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p382821054093533"><a name="p382821054093533"></a><a name="p382821054093533"></a>Enumerates text orientations. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table715264824093533"></a>
<table><thead align="left"><tr id="row823596625093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p781716783093533"><a name="p781716783093533"></a><a name="p781716783093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1854500055093533"><a name="p1854500055093533"></a><a name="p1854500055093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1756833914093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2062954137093533"><a name="p2062954137093533"></a><a name="p2062954137093533"></a><a href="graphic.md#gaeb650e68c370ef4d09d0eb0b30e4346e">UIArcLabel</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p653192552093533"><a name="p653192552093533"></a><a name="p653192552093533"></a> </p>
<p id="p1544809565093533"><a name="p1544809565093533"></a><a name="p1544809565093533"></a>A default constructor used to create a <strong id="b707189873093533"><a name="b707189873093533"></a><a name="b707189873093533"></a><a href="ohos-uiarclabel.md">UIArcLabel</a></strong> instance. </p>
</td>
</tr>
<tr id="row1814183803093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1010123860093533"><a name="p1010123860093533"></a><a name="p1010123860093533"></a><a href="graphic.md#ga89c52725ea96d25f451c2cd29f9cee22">~UIArcLabel</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1275470221093533"><a name="p1275470221093533"></a><a name="p1275470221093533"></a>virtual </p>
<p id="p435973708093533"><a name="p435973708093533"></a><a name="p435973708093533"></a>A destructor used to delete the <strong id="b1833395453093533"><a name="b1833395453093533"></a><a name="b1833395453093533"></a><a href="ohos-uiarclabel.md">UIArcLabel</a></strong> instance. </p>
</td>
</tr>
<tr id="row1788481364093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p879099625093533"><a name="p879099625093533"></a><a name="p879099625093533"></a><a href="graphic.md#ga2ebe9b09e69cd04b00db686dbec8c32c">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p309911618093533"><a name="p309911618093533"></a><a name="p309911618093533"></a>UIViewType </p>
<p id="p296869424093533"><a name="p296869424093533"></a><a name="p296869424093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row773524913093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617266121093533"><a name="p617266121093533"></a><a name="p617266121093533"></a><a href="graphic.md#gae2348ef2f06893325ca3366856657199">GetWidth</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p114852733093533"><a name="p114852733093533"></a><a name="p114852733093533"></a>int16_t </p>
<p id="p1018184357093533"><a name="p1018184357093533"></a><a name="p1018184357093533"></a>Obtains the width of this arc text. </p>
</td>
</tr>
<tr id="row119118932093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p734891974093533"><a name="p734891974093533"></a><a name="p734891974093533"></a><a href="graphic.md#ga37dbe21b6a8206460136b18a2d0e3f65">GetHeight</a> () override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p431402721093533"><a name="p431402721093533"></a><a name="p431402721093533"></a>int16_t </p>
<p id="p519713356093533"><a name="p519713356093533"></a><a name="p519713356093533"></a>Obtains the height of this arc text. </p>
</td>
</tr>
<tr id="row35723223093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2087746416093533"><a name="p2087746416093533"></a><a name="p2087746416093533"></a><a href="graphic.md#ga6085d982d8ec3d570b2eabc7d1a58b67">SetText</a> (const char *text)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p565674455093533"><a name="p565674455093533"></a><a name="p565674455093533"></a>void </p>
<p id="p470867307093533"><a name="p470867307093533"></a><a name="p470867307093533"></a>Sets the text content for this arc label. </p>
</td>
</tr>
<tr id="row778279114093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p485863647093533"><a name="p485863647093533"></a><a name="p485863647093533"></a><a href="graphic.md#gaf6541786a44218c7561a9e0f38dea985">GetText</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2082043690093533"><a name="p2082043690093533"></a><a name="p2082043690093533"></a>const char * </p>
<p id="p1097856449093533"><a name="p1097856449093533"></a><a name="p1097856449093533"></a>Obtains the text of this arc label. </p>
</td>
</tr>
<tr id="row714133742093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1330867128093533"><a name="p1330867128093533"></a><a name="p1330867128093533"></a><a href="graphic.md#gad379123d69ceb0dbb49d4055f9abac82">SetAlign</a> (<a href="graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> horizontalAlign)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1946079584093533"><a name="p1946079584093533"></a><a name="p1946079584093533"></a>void </p>
<p id="p2050793716093533"><a name="p2050793716093533"></a><a name="p2050793716093533"></a>Sets the alignment mode for this text. </p>
</td>
</tr>
<tr id="row1267255097093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1221120260093533"><a name="p1221120260093533"></a><a name="p1221120260093533"></a><a href="graphic.md#ga81db66fbe12615d85c68971e58201939">GetHorAlign</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1310114904093533"><a name="p1310114904093533"></a><a name="p1310114904093533"></a><a href="graphic.md#ga3f99b58f731a37cacde72d5e0c934593">UITextLanguageAlignment</a> </p>
<p id="p498057207093533"><a name="p498057207093533"></a><a name="p498057207093533"></a>Obtains the horizontal alignment mode. </p>
</td>
</tr>
<tr id="row413197317093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p26410105093533"><a name="p26410105093533"></a><a name="p26410105093533"></a><a href="graphic.md#ga337ba2ef9996c1b55a99408e63f0153e">GetDirect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1834410279093533"><a name="p1834410279093533"></a><a name="p1834410279093533"></a><a href="graphic.md#ga0c108f97781843f67c101b47b6c00cf0">UITextLanguageDirect</a> </p>
<p id="p140690236093533"><a name="p140690236093533"></a><a name="p140690236093533"></a>Obtains the direction of this text. </p>
</td>
</tr>
<tr id="row111465159093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1890755431093533"><a name="p1890755431093533"></a><a name="p1890755431093533"></a><a href="graphic.md#gad77dde925091bf68bb39316208a304ce">SetFontId</a> (uint8_t fontId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1518052083093533"><a name="p1518052083093533"></a><a name="p1518052083093533"></a>void </p>
<p id="p397582643093533"><a name="p397582643093533"></a><a name="p397582643093533"></a>Sets the font ID for this arc label. </p>
</td>
</tr>
<tr id="row350536006093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p666822485093533"><a name="p666822485093533"></a><a name="p666822485093533"></a><a href="graphic.md#gadbd5e4fae21ad3fb7dedf16b414c149d">GetFontId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1903089124093533"><a name="p1903089124093533"></a><a name="p1903089124093533"></a>uint8_t </p>
<p id="p1596170918093533"><a name="p1596170918093533"></a><a name="p1596170918093533"></a>Obtains the font ID composed of font name and size. </p>
</td>
</tr>
<tr id="row395096317093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p299856298093533"><a name="p299856298093533"></a><a name="p299856298093533"></a><a href="graphic.md#gaa45fef56dbe7296f3273586cbc29c7ed">SetFont</a> (const char *name, uint8_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620412986093533"><a name="p620412986093533"></a><a name="p620412986093533"></a>void </p>
<p id="p1666744731093533"><a name="p1666744731093533"></a><a name="p1666744731093533"></a>Sets the font for this arc label. </p>
</td>
</tr>
<tr id="row593094239093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1136553124093533"><a name="p1136553124093533"></a><a name="p1136553124093533"></a><a href="graphic.md#ga0679d838c86fbf540574a41ce0cfbdaf">SetArcTextCenter</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2029213863093533"><a name="p2029213863093533"></a><a name="p2029213863093533"></a>void </p>
<p id="p452837678093533"><a name="p452837678093533"></a><a name="p452837678093533"></a>Sets the center position for this arc text. </p>
</td>
</tr>
<tr id="row405924960093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p435066113093533"><a name="p435066113093533"></a><a name="p435066113093533"></a><a href="graphic.md#ga761fd2ed6abed4489c5dff744c03c8e7">GetArcTextCenter</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2016154330093533"><a name="p2016154330093533"></a><a name="p2016154330093533"></a><a href="ohos-point.md">Point</a> </p>
<p id="p1046482683093533"><a name="p1046482683093533"></a><a name="p1046482683093533"></a>Obtains the center position of this arc text. </p>
</td>
</tr>
<tr id="row821901622093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1001522982093533"><a name="p1001522982093533"></a><a name="p1001522982093533"></a><a href="graphic.md#ga304513546d8c396e89719725acf0a086">SetArcTextRadius</a> (uint16_t radius)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1328462533093533"><a name="p1328462533093533"></a><a name="p1328462533093533"></a>void </p>
<p id="p966843281093533"><a name="p966843281093533"></a><a name="p966843281093533"></a>Sets the radius for this arc text. </p>
</td>
</tr>
<tr id="row413020476093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p597379073093533"><a name="p597379073093533"></a><a name="p597379073093533"></a><a href="graphic.md#ga19ef3f705a2a486b8da7688ccff6f09d">GetArcTextRadius</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1046165381093533"><a name="p1046165381093533"></a><a name="p1046165381093533"></a>uint16_t </p>
<p id="p1341309355093533"><a name="p1341309355093533"></a><a name="p1341309355093533"></a>Obtains the radius of this arc text. </p>
</td>
</tr>
<tr id="row963786837093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1103430376093533"><a name="p1103430376093533"></a><a name="p1103430376093533"></a><a href="graphic.md#gaea37f7ce223d76e5b74dc098fc74cbf9">SetArcTextAngle</a> (int16_t startAngle, int16_t endAngle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2111277497093533"><a name="p2111277497093533"></a><a name="p2111277497093533"></a>void </p>
<p id="p244028239093533"><a name="p244028239093533"></a><a name="p244028239093533"></a>Sets the start angle and end angle for this arc text. </p>
</td>
</tr>
<tr id="row1456899188093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p28666750093533"><a name="p28666750093533"></a><a name="p28666750093533"></a><a href="graphic.md#ga6f60f48c3fe4571d09bfa74cb46837fa">GetArcTextStartAngle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1590874888093533"><a name="p1590874888093533"></a><a name="p1590874888093533"></a>int16_t </p>
<p id="p1569147944093533"><a name="p1569147944093533"></a><a name="p1569147944093533"></a>Obtains the start angle of this arc text. </p>
</td>
</tr>
<tr id="row1310063160093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1178442465093533"><a name="p1178442465093533"></a><a name="p1178442465093533"></a><a href="graphic.md#ga3ed7572ec5135e169ae1b6230dcfe7d2">GetArcTextEndAngle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2090546654093533"><a name="p2090546654093533"></a><a name="p2090546654093533"></a>int16_t </p>
<p id="p1907351664093533"><a name="p1907351664093533"></a><a name="p1907351664093533"></a>Obtains the end angle of this arc text. </p>
</td>
</tr>
<tr id="row842049048093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p109428635093533"><a name="p109428635093533"></a><a name="p109428635093533"></a><a href="graphic.md#gad24333f7363f2d73988f479e73b62b92">SetArcTextOrientation</a> (<a href="graphic.md#ga0778527bee4a7ddd8d46395585a5cfb9">TextOrientation</a> orientation)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p190872529093533"><a name="p190872529093533"></a><a name="p190872529093533"></a>void </p>
<p id="p830253530093533"><a name="p830253530093533"></a><a name="p830253530093533"></a>Sets the orientation for this arc text. </p>
</td>
</tr>
<tr id="row531288089093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p382501930093533"><a name="p382501930093533"></a><a name="p382501930093533"></a><a href="graphic.md#ga34fe8930d4ff654327e45c0abaafc037">GetArcTextOrientation</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1110121824093533"><a name="p1110121824093533"></a><a name="p1110121824093533"></a><a href="graphic.md#ga0778527bee4a7ddd8d46395585a5cfb9">TextOrientation</a> </p>
<p id="p190758001093533"><a name="p190758001093533"></a><a name="p190758001093533"></a>Obtains the orientation of this arc text. </p>
</td>
</tr>
<tr id="row311924735093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1593542336093533"><a name="p1593542336093533"></a><a name="p1593542336093533"></a><a href="graphic.md#ga9f3b69ad5511a4bd8f3aede212f3f374">OnDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1956778029093533"><a name="p1956778029093533"></a><a name="p1956778029093533"></a>virtual void </p>
<p id="p304223166093533"><a name="p304223166093533"></a><a name="p304223166093533"></a>Draws an arc text. </p>
</td>
</tr>
<tr id="row1229863304093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1237028890093533"><a name="p1237028890093533"></a><a name="p1237028890093533"></a><a href="graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p762739423093533"><a name="p762739423093533"></a><a name="p762739423093533"></a> </p>
<p id="p1187966608093533"><a name="p1187966608093533"></a><a name="p1187966608093533"></a>A default constructor used to create an <strong id="b1758114894093533"><a name="b1758114894093533"></a><a name="b1758114894093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1205384501093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p671236751093533"><a name="p671236751093533"></a><a name="p671236751093533"></a><a href="graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p452288040093533"><a name="p452288040093533"></a><a name="p452288040093533"></a> </p>
<p id="p788334783093533"><a name="p788334783093533"></a><a name="p788334783093533"></a>A constructor used to create an <strong id="b36765070093533"><a name="b36765070093533"></a><a name="b36765070093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1550122958093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1751563323093533"><a name="p1751563323093533"></a><a name="p1751563323093533"></a><a href="graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1012268494093533"><a name="p1012268494093533"></a><a name="p1012268494093533"></a>virtual </p>
<p id="p766942212093533"><a name="p766942212093533"></a><a name="p766942212093533"></a>A destructor used to delete the <strong id="b214416713093533"><a name="b214416713093533"></a><a name="b214416713093533"></a><a href="ohos-uiview.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row610647553093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1115063395093533"><a name="p1115063395093533"></a><a name="p1115063395093533"></a><a href="graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1820447820093533"><a name="p1820447820093533"></a><a name="p1820447820093533"></a>virtual bool </p>
<p id="p1250516883093533"><a name="p1250516883093533"></a><a name="p1250516883093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1091544788093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p380378005093533"><a name="p380378005093533"></a><a name="p380378005093533"></a><a href="graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p523867651093533"><a name="p523867651093533"></a><a name="p523867651093533"></a>virtual void </p>
<p id="p1678181820093533"><a name="p1678181820093533"></a><a name="p1678181820093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row612379517093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p218184427093533"><a name="p218184427093533"></a><a name="p218184427093533"></a><a href="graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p601050330093533"><a name="p601050330093533"></a><a name="p601050330093533"></a>void </p>
<p id="p1633290304093533"><a name="p1633290304093533"></a><a name="p1633290304093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row426416077093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p346972033093533"><a name="p346972033093533"></a><a name="p346972033093533"></a><a href="graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="ohos-rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1788046940093533"><a name="p1788046940093533"></a><a name="p1788046940093533"></a>void </p>
<p id="p1114041480093533"><a name="p1114041480093533"></a><a name="p1114041480093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1272479342093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p321220447093533"><a name="p321220447093533"></a><a name="p321220447093533"></a><a href="graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="ohos-longpressevent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p533117050093533"><a name="p533117050093533"></a><a name="p533117050093533"></a>virtual bool </p>
<p id="p828413340093533"><a name="p828413340093533"></a><a name="p828413340093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row242429274093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p541566986093533"><a name="p541566986093533"></a><a name="p541566986093533"></a><a href="graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p476693274093533"><a name="p476693274093533"></a><a name="p476693274093533"></a>virtual bool </p>
<p id="p1263649764093533"><a name="p1263649764093533"></a><a name="p1263649764093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row562635286093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p772907906093533"><a name="p772907906093533"></a><a name="p772907906093533"></a><a href="graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2147404180093533"><a name="p2147404180093533"></a><a name="p2147404180093533"></a>virtual bool </p>
<p id="p1380066058093533"><a name="p1380066058093533"></a><a name="p1380066058093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row749021976093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p772950661093533"><a name="p772950661093533"></a><a name="p772950661093533"></a><a href="graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="ohos-dragevent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1339102066093533"><a name="p1339102066093533"></a><a name="p1339102066093533"></a>virtual bool </p>
<p id="p243709633093533"><a name="p243709633093533"></a><a name="p243709633093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row2088306580093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p37190393093533"><a name="p37190393093533"></a><a name="p37190393093533"></a><a href="graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="ohos-clickevent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p620238609093533"><a name="p620238609093533"></a><a name="p620238609093533"></a>virtual void </p>
<p id="p156730713093533"><a name="p156730713093533"></a><a name="p156730713093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row593303011093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p66755364093533"><a name="p66755364093533"></a><a name="p66755364093533"></a><a href="graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="ohos-pressevent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1901468096093533"><a name="p1901468096093533"></a><a name="p1901468096093533"></a>virtual void </p>
<p id="p602447421093533"><a name="p602447421093533"></a><a name="p602447421093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row916258091093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1585592462093533"><a name="p1585592462093533"></a><a name="p1585592462093533"></a><a href="graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="ohos-releaseevent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p908797121093533"><a name="p908797121093533"></a><a name="p908797121093533"></a>virtual void </p>
<p id="p1873332081093533"><a name="p1873332081093533"></a><a name="p1873332081093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1167781998093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1118360123093533"><a name="p1118360123093533"></a><a name="p1118360123093533"></a><a href="graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="ohos-cancelevent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2106992841093533"><a name="p2106992841093533"></a><a name="p2106992841093533"></a>virtual void </p>
<p id="p581480768093533"><a name="p581480768093533"></a><a name="p581480768093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row267681194093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1434925105093533"><a name="p1434925105093533"></a><a name="p1434925105093533"></a><a href="graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p166566258093533"><a name="p166566258093533"></a><a name="p166566258093533"></a>void </p>
<p id="p969746401093533"><a name="p969746401093533"></a><a name="p969746401093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row316041306093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p380999950093533"><a name="p380999950093533"></a><a name="p380999950093533"></a><a href="graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2141482356093533"><a name="p2141482356093533"></a><a name="p2141482356093533"></a><a href="ohos-uiview-ondraglistener.md">OnDragListener</a> *&amp; </p>
<p id="p675626532093533"><a name="p675626532093533"></a><a name="p675626532093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row1814426537093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p833241540093533"><a name="p833241540093533"></a><a name="p833241540093533"></a><a href="graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p213527997093533"><a name="p213527997093533"></a><a name="p213527997093533"></a>void </p>
<p id="p1769977117093533"><a name="p1769977117093533"></a><a name="p1769977117093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row54505914093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p851623751093533"><a name="p851623751093533"></a><a name="p851623751093533"></a><a href="graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1412435363093533"><a name="p1412435363093533"></a><a name="p1412435363093533"></a><a href="ohos-uiview-onclicklistener.md">OnClickListener</a> *&amp; </p>
<p id="p73130781093533"><a name="p73130781093533"></a><a name="p73130781093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row444376533093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p166346985093533"><a name="p166346985093533"></a><a name="p166346985093533"></a><a href="graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p318618652093533"><a name="p318618652093533"></a><a name="p318618652093533"></a>void </p>
<p id="p881729093533"><a name="p881729093533"></a><a name="p881729093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row2832473093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1731388870093533"><a name="p1731388870093533"></a><a name="p1731388870093533"></a><a href="graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1471267370093533"><a name="p1471267370093533"></a><a name="p1471267370093533"></a><a href="ohos-uiview-onlongpresslistener.md">OnLongPressListener</a> *&amp; </p>
<p id="p61664582093533"><a name="p61664582093533"></a><a name="p61664582093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row324558249093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997662792093533"><a name="p997662792093533"></a><a name="p997662792093533"></a><a href="graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p437401881093533"><a name="p437401881093533"></a><a name="p437401881093533"></a>void </p>
<p id="p303863987093533"><a name="p303863987093533"></a><a name="p303863987093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1309361290093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p881851366093533"><a name="p881851366093533"></a><a name="p881851366093533"></a><a href="graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1902688346093533"><a name="p1902688346093533"></a><a name="p1902688346093533"></a><a href="ohos-uiview-ontouchlistener.md">OnTouchListener</a> *&amp; </p>
<p id="p929204980093533"><a name="p929204980093533"></a><a name="p929204980093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1967912384093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1272002293093533"><a name="p1272002293093533"></a><a name="p1272002293093533"></a><a href="graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="ohos-point.md">Point</a> &amp;point, <a href="ohos-uiview.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p403369200093533"><a name="p403369200093533"></a><a name="p403369200093533"></a>virtual void </p>
<p id="p275425510093533"><a name="p275425510093533"></a><a name="p275425510093533"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row35693883093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1347370096093533"><a name="p1347370096093533"></a><a name="p1347370096093533"></a><a href="graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="ohos-uiview.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2052192283093533"><a name="p2052192283093533"></a><a name="p2052192283093533"></a>void </p>
<p id="p1239412372093533"><a name="p1239412372093533"></a><a name="p1239412372093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1951939288093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1363915146093533"><a name="p1363915146093533"></a><a name="p1363915146093533"></a><a href="graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267875543093533"><a name="p267875543093533"></a><a name="p267875543093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p1470548794093533"><a name="p1470548794093533"></a><a name="p1470548794093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row511895924093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p116654499093533"><a name="p116654499093533"></a><a name="p116654499093533"></a><a href="graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="ohos-uiview.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1488982618093533"><a name="p1488982618093533"></a><a name="p1488982618093533"></a>void </p>
<p id="p1112303527093533"><a name="p1112303527093533"></a><a name="p1112303527093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1486159337093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1171283951093533"><a name="p1171283951093533"></a><a name="p1171283951093533"></a><a href="graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1838777540093533"><a name="p1838777540093533"></a><a name="p1838777540093533"></a><a href="ohos-uiview.md">UIView</a> * </p>
<p id="p372348463093533"><a name="p372348463093533"></a><a name="p372348463093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row1256670017093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p457477526093533"><a name="p457477526093533"></a><a name="p457477526093533"></a><a href="graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p926834598093533"><a name="p926834598093533"></a><a name="p926834598093533"></a>virtual void </p>
<p id="p1529180790093533"><a name="p1529180790093533"></a><a name="p1529180790093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1700105260093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1779207809093533"><a name="p1779207809093533"></a><a name="p1779207809093533"></a><a href="graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p130429168093533"><a name="p130429168093533"></a><a name="p130429168093533"></a>bool </p>
<p id="p721330664093533"><a name="p721330664093533"></a><a name="p721330664093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row1901525269093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p524020273093533"><a name="p524020273093533"></a><a name="p524020273093533"></a><a href="graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1801741932093533"><a name="p1801741932093533"></a><a name="p1801741932093533"></a>void </p>
<p id="p1562106242093533"><a name="p1562106242093533"></a><a name="p1562106242093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1629870320093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p81606369093533"><a name="p81606369093533"></a><a name="p81606369093533"></a><a href="graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p348347292093533"><a name="p348347292093533"></a><a name="p348347292093533"></a>bool </p>
<p id="p2001634366093533"><a name="p2001634366093533"></a><a name="p2001634366093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1852590257093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1087087352093533"><a name="p1087087352093533"></a><a name="p1087087352093533"></a><a href="graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p5082731093533"><a name="p5082731093533"></a><a name="p5082731093533"></a>void </p>
<p id="p1197234359093533"><a name="p1197234359093533"></a><a name="p1197234359093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row2135338072093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1051353733093533"><a name="p1051353733093533"></a><a name="p1051353733093533"></a><a href="graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1363860951093533"><a name="p1363860951093533"></a><a name="p1363860951093533"></a>bool </p>
<p id="p1011311555093533"><a name="p1011311555093533"></a><a name="p1011311555093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1311525346093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1191380529093533"><a name="p1191380529093533"></a><a name="p1191380529093533"></a><a href="graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313697429093533"><a name="p1313697429093533"></a><a name="p1313697429093533"></a>void </p>
<p id="p1661438236093533"><a name="p1661438236093533"></a><a name="p1661438236093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1793854229093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p567132594093533"><a name="p567132594093533"></a><a name="p567132594093533"></a><a href="graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p390061042093533"><a name="p390061042093533"></a><a name="p390061042093533"></a>bool </p>
<p id="p1712135050093533"><a name="p1712135050093533"></a><a name="p1712135050093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row494786592093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2044240891093533"><a name="p2044240891093533"></a><a name="p2044240891093533"></a><a href="graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p442377430093533"><a name="p442377430093533"></a><a name="p442377430093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p769714483093533"><a name="p769714483093533"></a><a name="p769714483093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row480605259093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1759960075093533"><a name="p1759960075093533"></a><a name="p1759960075093533"></a><a href="graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1293082967093533"><a name="p1293082967093533"></a><a name="p1293082967093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p857392790093533"><a name="p857392790093533"></a><a name="p857392790093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row576099164093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1790788025093533"><a name="p1790788025093533"></a><a name="p1790788025093533"></a><a href="graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p268148535093533"><a name="p268148535093533"></a><a name="p268148535093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p1475521437093533"><a name="p1475521437093533"></a><a name="p1475521437093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row542712787093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2055133275093533"><a name="p2055133275093533"></a><a name="p2055133275093533"></a><a href="graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p500379422093533"><a name="p500379422093533"></a><a name="p500379422093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p835455765093533"><a name="p835455765093533"></a><a name="p835455765093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row126547810093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2018071765093533"><a name="p2018071765093533"></a><a name="p2018071765093533"></a><a href="graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p871781978093533"><a name="p871781978093533"></a><a name="p871781978093533"></a>virtual <a href="ohos-rect.md">Rect</a> </p>
<p id="p368327752093533"><a name="p368327752093533"></a><a name="p368327752093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row469781371093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1152870519093533"><a name="p1152870519093533"></a><a name="p1152870519093533"></a><a href="graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p566113484093533"><a name="p566113484093533"></a><a name="p566113484093533"></a><a href="ohos-rect.md">Rect</a> </p>
<p id="p79091304093533"><a name="p79091304093533"></a><a name="p79091304093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1682843799093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1990507109093533"><a name="p1990507109093533"></a><a name="p1990507109093533"></a><a href="graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1893721193093533"><a name="p1893721193093533"></a><a name="p1893721193093533"></a>void </p>
<p id="p512277770093533"><a name="p512277770093533"></a><a name="p512277770093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1955730063093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2071995123093533"><a name="p2071995123093533"></a><a name="p2071995123093533"></a><a href="graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764640725093533"><a name="p764640725093533"></a><a name="p764640725093533"></a>virtual void </p>
<p id="p586014611093533"><a name="p586014611093533"></a><a name="p586014611093533"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row995897427093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1793421798093533"><a name="p1793421798093533"></a><a name="p1793421798093533"></a><a href="graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p503288866093533"><a name="p503288866093533"></a><a name="p503288866093533"></a>virtual void </p>
<p id="p2134895192093533"><a name="p2134895192093533"></a><a name="p2134895192093533"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row658870508093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1771834724093533"><a name="p1771834724093533"></a><a name="p1771834724093533"></a><a href="graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1366335592093533"><a name="p1366335592093533"></a><a name="p1366335592093533"></a>virtual void </p>
<p id="p1752007806093533"><a name="p1752007806093533"></a><a name="p1752007806093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1971132467093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1318167666093533"><a name="p1318167666093533"></a><a name="p1318167666093533"></a><a href="graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1487816575093533"><a name="p1487816575093533"></a><a name="p1487816575093533"></a>virtual void </p>
<p id="p1763971714093533"><a name="p1763971714093533"></a><a name="p1763971714093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row42906214093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1175401359093533"><a name="p1175401359093533"></a><a name="p1175401359093533"></a><a href="graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1275469603093533"><a name="p1275469603093533"></a><a name="p1275469603093533"></a>int16_t </p>
<p id="p545177351093533"><a name="p545177351093533"></a><a name="p545177351093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row389148272093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p193095599093533"><a name="p193095599093533"></a><a name="p193095599093533"></a><a href="graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1162213047093533"><a name="p1162213047093533"></a><a name="p1162213047093533"></a>virtual void </p>
<p id="p1259411336093533"><a name="p1259411336093533"></a><a name="p1259411336093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row589777598093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p865455202093533"><a name="p865455202093533"></a><a name="p865455202093533"></a><a href="graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p35775785093533"><a name="p35775785093533"></a><a name="p35775785093533"></a>int16_t </p>
<p id="p329190104093533"><a name="p329190104093533"></a><a name="p329190104093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row919720940093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2136225944093533"><a name="p2136225944093533"></a><a name="p2136225944093533"></a><a href="graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1133539959093533"><a name="p1133539959093533"></a><a name="p1133539959093533"></a>virtual void </p>
<p id="p991176488093533"><a name="p991176488093533"></a><a name="p991176488093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1188982262093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1229643121093533"><a name="p1229643121093533"></a><a name="p1229643121093533"></a><a href="graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1363013157093533"><a name="p1363013157093533"></a><a name="p1363013157093533"></a>virtual void </p>
<p id="p787214758093533"><a name="p787214758093533"></a><a name="p787214758093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row2012624809093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2019448269093533"><a name="p2019448269093533"></a><a name="p2019448269093533"></a><a href="graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p647418249093533"><a name="p647418249093533"></a><a name="p647418249093533"></a>bool </p>
<p id="p2113899824093533"><a name="p2113899824093533"></a><a name="p2113899824093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row2109090698093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1110359252093533"><a name="p1110359252093533"></a><a name="p1110359252093533"></a><a href="graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1847629943093533"><a name="p1847629943093533"></a><a name="p1847629943093533"></a>void </p>
<p id="p416089157093533"><a name="p416089157093533"></a><a name="p416089157093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1613476818093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p607106035093533"><a name="p607106035093533"></a><a name="p607106035093533"></a><a href="graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="ohos-transformmap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p430464603093533"><a name="p430464603093533"></a><a name="p430464603093533"></a>void </p>
<p id="p1312619787093533"><a name="p1312619787093533"></a><a name="p1312619787093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1877049463093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p411767685093533"><a name="p411767685093533"></a><a name="p411767685093533"></a><a href="graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1125153497093533"><a name="p1125153497093533"></a><a name="p1125153497093533"></a><a href="ohos-transformmap.md">TransformMap</a> &amp; </p>
<p id="p1681438744093533"><a name="p1681438744093533"></a><a name="p1681438744093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row401942612093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p349476453093533"><a name="p349476453093533"></a><a name="p349476453093533"></a><a href="graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p513724866093533"><a name="p513724866093533"></a><a name="p513724866093533"></a>virtual <a href="ohos-uiview.md">UIView</a> * </p>
<p id="p193095585093533"><a name="p193095585093533"></a><a name="p193095585093533"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row125223085093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p660816165093533"><a name="p660816165093533"></a><a name="p660816165093533"></a><a href="graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p839869821093533"><a name="p839869821093533"></a><a name="p839869821093533"></a>void </p>
<p id="p1378596229093533"><a name="p1378596229093533"></a><a name="p1378596229093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row916223461093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p135864713093533"><a name="p135864713093533"></a><a name="p135864713093533"></a><a href="graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p680693771093533"><a name="p680693771093533"></a><a name="p680693771093533"></a>const char * </p>
<p id="p94223350093533"><a name="p94223350093533"></a><a name="p94223350093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1537305869093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1426544868093533"><a name="p1426544868093533"></a><a name="p1426544868093533"></a><a href="graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="en-us_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p690739466093533"><a name="p690739466093533"></a><a name="p690739466093533"></a>void </p>
<p id="p2119672819093533"><a name="p2119672819093533"></a><a name="p2119672819093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1825775462093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1335513080093533"><a name="p1335513080093533"></a><a name="p1335513080093533"></a><a href="graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p564654206093533"><a name="p564654206093533"></a><a name="p564654206093533"></a>int16_t </p>
<p id="p1854288636093533"><a name="p1854288636093533"></a><a name="p1854288636093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1465398259093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1462541116093533"><a name="p1462541116093533"></a><a name="p1462541116093533"></a><a href="graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p725546106093533"><a name="p725546106093533"></a><a name="p725546106093533"></a>virtual void </p>
<p id="p831609256093533"><a name="p831609256093533"></a><a name="p831609256093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row2006302577093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1209354694093533"><a name="p1209354694093533"></a><a name="p1209354694093533"></a><a href="graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1525116382093533"><a name="p1525116382093533"></a><a name="p1525116382093533"></a>void </p>
<p id="p819164989093533"><a name="p819164989093533"></a><a name="p819164989093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row705467056093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p784936772093533"><a name="p784936772093533"></a><a name="p784936772093533"></a><a href="graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p411182865093533"><a name="p411182865093533"></a><a name="p411182865093533"></a>void </p>
<p id="p383455635093533"><a name="p383455635093533"></a><a name="p383455635093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row311842013093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1816356077093533"><a name="p1816356077093533"></a><a name="p1816356077093533"></a><a href="graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p420423924093533"><a name="p420423924093533"></a><a name="p420423924093533"></a>void </p>
<p id="p764784769093533"><a name="p764784769093533"></a><a name="p764784769093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1426896060093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977108223093533"><a name="p977108223093533"></a><a name="p977108223093533"></a><a href="graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1498304790093533"><a name="p1498304790093533"></a><a name="p1498304790093533"></a>void </p>
<p id="p576393238093533"><a name="p576393238093533"></a><a name="p576393238093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1309791943093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p670623262093533"><a name="p670623262093533"></a><a name="p670623262093533"></a><a href="graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1660844442093533"><a name="p1660844442093533"></a><a name="p1660844442093533"></a>void </p>
<p id="p873022007093533"><a name="p873022007093533"></a><a name="p873022007093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1501932781093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p713917916093533"><a name="p713917916093533"></a><a name="p713917916093533"></a><a href="graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p410808745093533"><a name="p410808745093533"></a><a name="p410808745093533"></a>void </p>
<p id="p1405889050093533"><a name="p1405889050093533"></a><a name="p1405889050093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row955540742093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1458018416093533"><a name="p1458018416093533"></a><a name="p1458018416093533"></a><a href="graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1542454743093533"><a name="p1542454743093533"></a><a name="p1542454743093533"></a>void </p>
<p id="p1674035571093533"><a name="p1674035571093533"></a><a name="p1674035571093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row577928588093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1848295344093533"><a name="p1848295344093533"></a><a name="p1848295344093533"></a><a href="graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p97794957093533"><a name="p97794957093533"></a><a name="p97794957093533"></a>void </p>
<p id="p1595494380093533"><a name="p1595494380093533"></a><a name="p1595494380093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row75780906093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1555469470093533"><a name="p1555469470093533"></a><a name="p1555469470093533"></a><a href="graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1737570622093533"><a name="p1737570622093533"></a><a name="p1737570622093533"></a>void </p>
<p id="p213223066093533"><a name="p213223066093533"></a><a name="p213223066093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1055699497093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2031626125093533"><a name="p2031626125093533"></a><a name="p2031626125093533"></a><a href="graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p472972214093533"><a name="p472972214093533"></a><a name="p472972214093533"></a>void </p>
<p id="p731743068093533"><a name="p731743068093533"></a><a name="p731743068093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row571930074093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1675838905093533"><a name="p1675838905093533"></a><a name="p1675838905093533"></a><a href="graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p354045930093533"><a name="p354045930093533"></a><a name="p354045930093533"></a>void </p>
<p id="p1027110637093533"><a name="p1027110637093533"></a><a name="p1027110637093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1894274156093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1645612332093533"><a name="p1645612332093533"></a><a name="p1645612332093533"></a><a href="graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p228664135093533"><a name="p228664135093533"></a><a name="p228664135093533"></a>void </p>
<p id="p1161090150093533"><a name="p1161090150093533"></a><a name="p1161090150093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row54668379093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p700963968093533"><a name="p700963968093533"></a><a name="p700963968093533"></a><a href="graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1717469806093533"><a name="p1717469806093533"></a><a name="p1717469806093533"></a>void </p>
<p id="p83996012093533"><a name="p83996012093533"></a><a name="p83996012093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row907137505093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p354288544093533"><a name="p354288544093533"></a><a name="p354288544093533"></a><a href="graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p598271984093533"><a name="p598271984093533"></a><a name="p598271984093533"></a>void </p>
<p id="p401387308093533"><a name="p401387308093533"></a><a name="p401387308093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row1547294537093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p927785937093533"><a name="p927785937093533"></a><a name="p927785937093533"></a><a href="graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p389306681093533"><a name="p389306681093533"></a><a name="p389306681093533"></a>void </p>
<p id="p1985114175093533"><a name="p1985114175093533"></a><a name="p1985114175093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1793332413093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p599749916093533"><a name="p599749916093533"></a><a name="p599749916093533"></a><a href="graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="ohos-style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1560286577093533"><a name="p1560286577093533"></a><a name="p1560286577093533"></a>virtual void </p>
<p id="p371065145093533"><a name="p371065145093533"></a><a name="p371065145093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1993916641093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p589867981093533"><a name="p589867981093533"></a><a name="p589867981093533"></a><a href="graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1434043906093533"><a name="p1434043906093533"></a><a name="p1434043906093533"></a>virtual void </p>
<p id="p69101294093533"><a name="p69101294093533"></a><a name="p69101294093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row388791675093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p764040232093533"><a name="p764040232093533"></a><a name="p764040232093533"></a><a href="graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1141129393093533"><a name="p1141129393093533"></a><a name="p1141129393093533"></a>virtual int64_t </p>
<p id="p1916329763093533"><a name="p1916329763093533"></a><a name="p1916329763093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1938554000093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p746991275093533"><a name="p746991275093533"></a><a name="p746991275093533"></a><a href="graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p330120540093533"><a name="p330120540093533"></a><a name="p330120540093533"></a>const <a href="ohos-style.md">Style</a> &amp; </p>
<p id="p246409062093533"><a name="p246409062093533"></a><a name="p246409062093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1805302379093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1793263825093533"><a name="p1793263825093533"></a><a name="p1793263825093533"></a><a href="graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p51628864093533"><a name="p51628864093533"></a><a name="p51628864093533"></a>void * </p>
<p id="p1446586729093533"><a name="p1446586729093533"></a><a name="p1446586729093533"></a>Overrides the <strong id="b1824444923093533"><a name="b1824444923093533"></a><a name="b1824444923093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1366673312093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2101762080093533"><a name="p2101762080093533"></a><a name="p2101762080093533"></a><a href="graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p15292500093533"><a name="p15292500093533"></a><a name="p15292500093533"></a>void </p>
<p id="p1939074838093533"><a name="p1939074838093533"></a><a name="p1939074838093533"></a>Overrides the <strong id="b814748636093533"><a name="b814748636093533"></a><a name="b814748636093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

