# OHOS::Color<a name="ZH-CN_TOPIC_0000001055078157"></a>

## **Overview**<a name="section941983751093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Converts colors in different formats and defines common colors. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section998697107093533"></a>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table2013263418093533"></a>
<table><thead align="left"><tr id="row1539610855093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1158676388093533"><a name="p1158676388093533"></a><a name="p1158676388093533"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p708411955093533"><a name="p708411955093533"></a><a name="p708411955093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row177524583093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1902547530093533"><a name="p1902547530093533"></a><a name="p1902547530093533"></a><a href="Graphic.md#gae12573eec4d4db025e96b5d9679e4b3f">GetMixColor</a> (<a href="OHOS-Color32.md">ColorType</a> c1, <a href="OHOS-Color32.md">ColorType</a> c2, uint8_t mix)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p922365826093533"><a name="p922365826093533"></a><a name="p922365826093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1387654745093533"><a name="p1387654745093533"></a><a name="p1387654745093533"></a>Mixes two colors (color 1 and color 2) based on a specified opacity. </p>
</td>
</tr>
<tr id="row1059642300093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1190074167093533"><a name="p1190074167093533"></a><a name="p1190074167093533"></a><a href="Graphic.md#ga0c3bb99c625896eeab6eb0acbe14f437">GetColorFromRGB</a> (uint8_t r8, uint8_t g8, uint8_t b8)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1025261840093533"><a name="p1025261840093533"></a><a name="p1025261840093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1472227300093533"><a name="p1472227300093533"></a><a name="p1472227300093533"></a>Obtains the color based on the RGB color value. </p>
</td>
</tr>
<tr id="row1463243912093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478552973093533"><a name="p478552973093533"></a><a name="p478552973093533"></a><a href="Graphic.md#ga0a7e632d54e39d1d46e64c6cf20690cc">GetColorFromRGBA</a> (uint8_t r8, uint8_t g8, uint8_t b8, uint8_t alpha)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1288983833093533"><a name="p1288983833093533"></a><a name="p1288983833093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p712567369093533"><a name="p712567369093533"></a><a name="p712567369093533"></a>Obtains the color based on the RGBA color value. </p>
</td>
</tr>
<tr id="row2122655258093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p372524149093533"><a name="p372524149093533"></a><a name="p372524149093533"></a><a href="Graphic.md#ga461b46dd76842ad4b0ffdc88202223a7">ColorTo32</a> (<a href="OHOS-Color32.md">ColorType</a> color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p122249886093533"><a name="p122249886093533"></a><a name="p122249886093533"></a>static uint32_t&nbsp;</p>
<p id="p1500804899093533"><a name="p1500804899093533"></a><a name="p1500804899093533"></a>Converts color data into the RGBA8888 format. </p>
</td>
</tr>
<tr id="row1259614605093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1150340922093533"><a name="p1150340922093533"></a><a name="p1150340922093533"></a><a href="Graphic.md#gaaca42d51bc5f28d5dbd5b1635be50224">ColorTo32</a> (<a href="OHOS-Color16.md">Color16</a> color, uint8_t alpha)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p537413166093533"><a name="p537413166093533"></a><a name="p537413166093533"></a>static uint32_t&nbsp;</p>
<p id="p1308388051093533"><a name="p1308388051093533"></a><a name="p1308388051093533"></a>Converts color data with the 16-bit color depth into the RGBA8888 format. </p>
</td>
</tr>
<tr id="row1376309942093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p841628138093533"><a name="p841628138093533"></a><a name="p841628138093533"></a><a href="Graphic.md#ga2a6a0bd067a05ee35793fefc8f9f4d1e">ColorTo16</a> (<a href="OHOS-Color32.md">Color32</a> color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p146042381093533"><a name="p146042381093533"></a><a name="p146042381093533"></a>static uint16_t&nbsp;</p>
<p id="p70305693093533"><a name="p70305693093533"></a><a name="p70305693093533"></a>Converts color data from the RGBA8888 format into the RGB565 format. </p>
</td>
</tr>
<tr id="row1082004519093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1069943547093533"><a name="p1069943547093533"></a><a name="p1069943547093533"></a><a href="Graphic.md#gad98c45688cd59b11e9e766e62e24252f">White</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p12849631093533"><a name="p12849631093533"></a><a name="p12849631093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p484582010093533"><a name="p484582010093533"></a><a name="p484582010093533"></a>Obtains the color data of white. </p>
</td>
</tr>
<tr id="row1312822678093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1053413295093533"><a name="p1053413295093533"></a><a name="p1053413295093533"></a><a href="Graphic.md#ga6dcfcd450637398b7b7d28ce7464d153">Silver</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2055237827093533"><a name="p2055237827093533"></a><a name="p2055237827093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1546841789093533"><a name="p1546841789093533"></a><a name="p1546841789093533"></a>Obtains the color data of silver. </p>
</td>
</tr>
<tr id="row1363016868093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1985791961093533"><a name="p1985791961093533"></a><a name="p1985791961093533"></a><a href="Graphic.md#ga920421d6dc1d9fbc21d5002948eb43c6">Gray</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1620088271093533"><a name="p1620088271093533"></a><a name="p1620088271093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1917437731093533"><a name="p1917437731093533"></a><a name="p1917437731093533"></a>Obtains the color data of gray. </p>
</td>
</tr>
<tr id="row2130694916093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p470019205093533"><a name="p470019205093533"></a><a name="p470019205093533"></a><a href="Graphic.md#gac821c879969c94ec048117738e4bbef2">Black</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p840584523093533"><a name="p840584523093533"></a><a name="p840584523093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1618501554093533"><a name="p1618501554093533"></a><a name="p1618501554093533"></a>Obtains the color data of black. </p>
</td>
</tr>
<tr id="row853013152093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1257582304093533"><a name="p1257582304093533"></a><a name="p1257582304093533"></a><a href="Graphic.md#gac7d29e91471253cbef9d709d74bc0d78">Red</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p121525907093533"><a name="p121525907093533"></a><a name="p121525907093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p366960632093533"><a name="p366960632093533"></a><a name="p366960632093533"></a>Obtains the color data of red. </p>
</td>
</tr>
<tr id="row805432247093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1163885398093533"><a name="p1163885398093533"></a><a name="p1163885398093533"></a><a href="Graphic.md#gaf8342e9323109066e57434445de4423e">Maroon</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1519435345093533"><a name="p1519435345093533"></a><a name="p1519435345093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1993230699093533"><a name="p1993230699093533"></a><a name="p1993230699093533"></a>Obtains the color data of maroon. </p>
</td>
</tr>
<tr id="row98208470093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1311003722093533"><a name="p1311003722093533"></a><a name="p1311003722093533"></a><a href="Graphic.md#gadd545c06bdd497b259179379e6910e15">Yellow</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1781664083093533"><a name="p1781664083093533"></a><a name="p1781664083093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1357849283093533"><a name="p1357849283093533"></a><a name="p1357849283093533"></a>Obtains the color data of yellow. </p>
</td>
</tr>
<tr id="row1865268213093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p425904212093533"><a name="p425904212093533"></a><a name="p425904212093533"></a><a href="Graphic.md#ga8c8d03f5579dbb976119cee384856e3b">Olive</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p189714479093533"><a name="p189714479093533"></a><a name="p189714479093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p208742327093533"><a name="p208742327093533"></a><a name="p208742327093533"></a>Obtains the color data of olive. </p>
</td>
</tr>
<tr id="row1692443527093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p629687156093533"><a name="p629687156093533"></a><a name="p629687156093533"></a><a href="Graphic.md#ga629dc5c95263df097a06b207a36b1dca">Lime</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1389574232093533"><a name="p1389574232093533"></a><a name="p1389574232093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1815942000093533"><a name="p1815942000093533"></a><a name="p1815942000093533"></a>Obtains the color data of lime. </p>
</td>
</tr>
<tr id="row1531176868093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p587476794093533"><a name="p587476794093533"></a><a name="p587476794093533"></a><a href="Graphic.md#ga672e4e015f76e7cef0a4b819ee95f082">Green</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p615748757093533"><a name="p615748757093533"></a><a name="p615748757093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p54560226093533"><a name="p54560226093533"></a><a name="p54560226093533"></a>Obtains the color data of green. </p>
</td>
</tr>
<tr id="row347597133093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p402275478093533"><a name="p402275478093533"></a><a name="p402275478093533"></a><a href="Graphic.md#ga9d6b730a0799da3254543613acb0a3fa">Cyan</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p105696559093533"><a name="p105696559093533"></a><a name="p105696559093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p318380086093533"><a name="p318380086093533"></a><a name="p318380086093533"></a>Obtains the color data of cyan. </p>
</td>
</tr>
<tr id="row380650877093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p892596544093533"><a name="p892596544093533"></a><a name="p892596544093533"></a><a href="Graphic.md#ga24da6b938c938b3defeb56ff79a4c4f5">Aqua</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p498500972093533"><a name="p498500972093533"></a><a name="p498500972093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1776033215093533"><a name="p1776033215093533"></a><a name="p1776033215093533"></a>Obtains the color data of aqua. </p>
</td>
</tr>
<tr id="row1211779780093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p190269786093533"><a name="p190269786093533"></a><a name="p190269786093533"></a><a href="Graphic.md#ga9f4afc8d27c8e90d5295b281a7198fe5">Teal</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p499842457093533"><a name="p499842457093533"></a><a name="p499842457093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1363776085093533"><a name="p1363776085093533"></a><a name="p1363776085093533"></a>Obtains the color data of teal. </p>
</td>
</tr>
<tr id="row1884059499093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1684181031093533"><a name="p1684181031093533"></a><a name="p1684181031093533"></a><a href="Graphic.md#ga3b02160a068039d3801580c8e35008b4">Blue</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p491215287093533"><a name="p491215287093533"></a><a name="p491215287093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1918945451093533"><a name="p1918945451093533"></a><a name="p1918945451093533"></a>Obtains the color data of blue. </p>
</td>
</tr>
<tr id="row734889687093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p559492089093533"><a name="p559492089093533"></a><a name="p559492089093533"></a><a href="Graphic.md#ga327d185847eab86cbe297a1e35f0d5d7">Navy</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1255653927093533"><a name="p1255653927093533"></a><a name="p1255653927093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1705104966093533"><a name="p1705104966093533"></a><a name="p1705104966093533"></a>Obtains the color data of navy. </p>
</td>
</tr>
<tr id="row1988463946093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1683042113093533"><a name="p1683042113093533"></a><a name="p1683042113093533"></a><a href="Graphic.md#ga4cbaf5650de24fc1ae45f93571b92f37">Magenta</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1327155544093533"><a name="p1327155544093533"></a><a name="p1327155544093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1375303571093533"><a name="p1375303571093533"></a><a name="p1375303571093533"></a>Obtains the color data of magenta. </p>
</td>
</tr>
<tr id="row2074277341093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p594759997093533"><a name="p594759997093533"></a><a name="p594759997093533"></a><a href="Graphic.md#ga7ec7f44a7a7d828641b739616b01dadb">Purple</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p291944320093533"><a name="p291944320093533"></a><a name="p291944320093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p1437702732093533"><a name="p1437702732093533"></a><a name="p1437702732093533"></a>Obtains the color data of purple. </p>
</td>
</tr>
<tr id="row959541870093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1386738741093533"><a name="p1386738741093533"></a><a name="p1386738741093533"></a><a href="Graphic.md#gae127df687f7b04f9debc853498678aeb">Orange</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1331241574093533"><a name="p1331241574093533"></a><a name="p1331241574093533"></a>static <a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p874845853093533"><a name="p874845853093533"></a><a name="p874845853093533"></a>Obtains the color data of orange. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table610618547093533"></a>
<table><thead align="left"><tr id="row994016048093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1088505050093533"><a name="p1088505050093533"></a><a name="p1088505050093533"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p569140820093533"><a name="p569140820093533"></a><a name="p569140820093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row460213814093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997769177093533"><a name="p997769177093533"></a><a name="p997769177093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p498690578093533"><a name="p498690578093533"></a><a name="p498690578093533"></a>Overrides the <strong id="b1813034268093533"><a name="b1813034268093533"></a><a name="b1813034268093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row386023552093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p554865711093533"><a name="p554865711093533"></a><a name="p554865711093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p656319003093533"><a name="p656319003093533"></a><a name="p656319003093533"></a>Overrides the <strong id="b239446271093533"><a name="b239446271093533"></a><a name="b239446271093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

