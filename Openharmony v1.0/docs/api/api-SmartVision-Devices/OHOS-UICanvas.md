# OHOS::UICanvas<a name="ZH-CN_TOPIC_0000001054918177"></a>

## **Overview**<a name="section1523122737093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines a canvas, which is used to draw multiple types of 2D graphs. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1033319918093533"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1073751490093533"></a>
<table><thead align="left"><tr id="row1845899060093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p161954114093533"><a name="p161954114093533"></a><a name="p161954114093533"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p378117780093533"><a name="p378117780093533"></a><a name="p378117780093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2120674570093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p609523810093533"><a name="p609523810093533"></a><a name="p609523810093533"></a><a href="OHOS-UICanvas-FontStyle.md">FontStyle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p946134759093533"><a name="p946134759093533"></a><a name="p946134759093533"></a>Defines the font style. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1795820187093533"></a>
<table><thead align="left"><tr id="row143263032093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p675503804093533"><a name="p675503804093533"></a><a name="p675503804093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p163240821093533"><a name="p163240821093533"></a><a name="p163240821093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row948648159093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p718589884093533"><a name="p718589884093533"></a><a name="p718589884093533"></a><a href="Graphic.md#ga60d2ed5d49ef68ae8d6f2a8b58322ed3">UICanvas</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p763547543093533"><a name="p763547543093533"></a><a name="p763547543093533"></a>&nbsp;</p>
<p id="p1246366598093533"><a name="p1246366598093533"></a><a name="p1246366598093533"></a>A constructor used to create a <strong id="b1398227704093533"><a name="b1398227704093533"></a><a name="b1398227704093533"></a><a href="OHOS-UICanvas.md">UICanvas</a></strong> instance. </p>
</td>
</tr>
<tr id="row97762200093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2126624060093533"><a name="p2126624060093533"></a><a name="p2126624060093533"></a><a href="Graphic.md#gaf099d1872cdb070f038c5135309b9b6b">~UICanvas</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1024258986093533"><a name="p1024258986093533"></a><a name="p1024258986093533"></a>virtual&nbsp;</p>
<p id="p1711864943093533"><a name="p1711864943093533"></a><a name="p1711864943093533"></a>A destructor used to delete the <strong id="b283046259093533"><a name="b283046259093533"></a><a name="b283046259093533"></a><a href="OHOS-UICanvas.md">UICanvas</a></strong> instance. </p>
</td>
</tr>
<tr id="row682478370093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1516250704093533"><a name="p1516250704093533"></a><a name="p1516250704093533"></a><a href="Graphic.md#ga467faebb78b4c4a753eaa44b772f0905">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1971542612093533"><a name="p1971542612093533"></a><a name="p1971542612093533"></a>UIViewType&nbsp;</p>
<p id="p592957317093533"><a name="p592957317093533"></a><a name="p592957317093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row2029468690093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p91345288093533"><a name="p91345288093533"></a><a name="p91345288093533"></a><a href="Graphic.md#ga7e20822a6c448bee724f20afad1c69d4">Clear</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p584624112093533"><a name="p584624112093533"></a><a name="p584624112093533"></a>void&nbsp;</p>
<p id="p50403066093533"><a name="p50403066093533"></a><a name="p50403066093533"></a>Clears the entire canvas. </p>
</td>
</tr>
<tr id="row533295891093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p362443385093533"><a name="p362443385093533"></a><a name="p362443385093533"></a><a href="Graphic.md#gaca35fe1a1d344eab80ecb1425a74a91a">SetStartPosition</a> (const <a href="OHOS-Point.md">Point</a> &amp;startPoint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p88620852093533"><a name="p88620852093533"></a><a name="p88620852093533"></a>void&nbsp;</p>
<p id="p1476033145093533"><a name="p1476033145093533"></a><a name="p1476033145093533"></a>Sets the coordinates of the start point for drawing a line. For example, if <strong id="b1887141074093533"><a name="b1887141074093533"></a><a name="b1887141074093533"></a>startPoint</strong> is set to {50, 50}, the line is drawn from this set of coordinates on the canvas. </p>
</td>
</tr>
<tr id="row1102201920093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1793569032093533"><a name="p1793569032093533"></a><a name="p1793569032093533"></a><a href="Graphic.md#gad23f7db18bfa5f91e3cb814193e6932d">GetStartPosition</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p742994745093533"><a name="p742994745093533"></a><a name="p742994745093533"></a>const <a href="OHOS-Point.md">Point</a> &amp;&nbsp;</p>
<p id="p542611630093533"><a name="p542611630093533"></a><a name="p542611630093533"></a>Obtains the coordinates of the start point of a line. </p>
</td>
</tr>
<tr id="row1091025128093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1309955213093533"><a name="p1309955213093533"></a><a name="p1309955213093533"></a><a href="Graphic.md#gac97d9d39484e5a1e36273510ae47327e">DrawLine</a> (const <a href="OHOS-Point.md">Point</a> &amp;endPoint, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1563976852093533"><a name="p1563976852093533"></a><a name="p1563976852093533"></a>void&nbsp;</p>
<p id="p939205237093533"><a name="p939205237093533"></a><a name="p939205237093533"></a>Draws a straight line. </p>
</td>
</tr>
<tr id="row134642957093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p806018220093533"><a name="p806018220093533"></a><a name="p806018220093533"></a><a href="Graphic.md#ga0c5e94526dab6a62d6db0a67385104db">DrawLine</a> (const <a href="OHOS-Point.md">Point</a> &amp;startPoint, const <a href="OHOS-Point.md">Point</a> &amp;endPoint, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p911215671093533"><a name="p911215671093533"></a><a name="p911215671093533"></a>void&nbsp;</p>
<p id="p1796684818093533"><a name="p1796684818093533"></a><a name="p1796684818093533"></a>Draws a straight line from the coordinates of the start point. </p>
</td>
</tr>
<tr id="row583222580093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p658685522093533"><a name="p658685522093533"></a><a name="p658685522093533"></a><a href="Graphic.md#gab6557ddb74b721e4eba6cdabab954a3b">DrawCurve</a> (const <a href="OHOS-Point.md">Point</a> &amp;control1, const <a href="OHOS-Point.md">Point</a> &amp;control2, const <a href="OHOS-Point.md">Point</a> &amp;endPoint, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1472238432093533"><a name="p1472238432093533"></a><a name="p1472238432093533"></a>void&nbsp;</p>
<p id="p1466016338093533"><a name="p1466016338093533"></a><a name="p1466016338093533"></a>Draws a cubic Bezier curve. </p>
</td>
</tr>
<tr id="row600788532093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1819043602093533"><a name="p1819043602093533"></a><a name="p1819043602093533"></a><a href="Graphic.md#gad186e8eab51e97a4854d3a757a3becfb">DrawCurve</a> (const <a href="OHOS-Point.md">Point</a> &amp;startPoint, const <a href="OHOS-Point.md">Point</a> &amp;control1, const <a href="OHOS-Point.md">Point</a> &amp;control2, const <a href="OHOS-Point.md">Point</a> &amp;endPoint, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p640924229093533"><a name="p640924229093533"></a><a name="p640924229093533"></a>void&nbsp;</p>
<p id="p1226040109093533"><a name="p1226040109093533"></a><a name="p1226040109093533"></a>Draws a cubic Bezier curve from the start point coordinates. </p>
</td>
</tr>
<tr id="row228496678093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p925311855093533"><a name="p925311855093533"></a><a name="p925311855093533"></a><a href="Graphic.md#ga1cc0bc88810cdd5554e2b1b14e68c279">DrawRect</a> (const <a href="OHOS-Point.md">Point</a> &amp;startPoint, int16_t height, int16_t width, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1477408281093533"><a name="p1477408281093533"></a><a name="p1477408281093533"></a>void&nbsp;</p>
<p id="p590432329093533"><a name="p590432329093533"></a><a name="p590432329093533"></a>Draws a rectangle. </p>
</td>
</tr>
<tr id="row1784435752093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p146894708093533"><a name="p146894708093533"></a><a name="p146894708093533"></a><a href="Graphic.md#ga974544e34560d0f9d6e162c528fcd7af">DrawCircle</a> (const <a href="OHOS-Point.md">Point</a> &amp;center, uint16_t radius, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1630707919093533"><a name="p1630707919093533"></a><a name="p1630707919093533"></a>void&nbsp;</p>
<p id="p839684984093533"><a name="p839684984093533"></a><a name="p839684984093533"></a>Draws a circle. </p>
</td>
</tr>
<tr id="row2114084904093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977578775093533"><a name="p977578775093533"></a><a name="p977578775093533"></a><a href="Graphic.md#gaf14bc2633c51a16097c3ad35e8bcb314">DrawSector</a> (const <a href="OHOS-Point.md">Point</a> &amp;center, uint16_t radius, int16_t startAngle, int16_t endAngle, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1774111052093533"><a name="p1774111052093533"></a><a name="p1774111052093533"></a>void&nbsp;</p>
<p id="p951139236093533"><a name="p951139236093533"></a><a name="p951139236093533"></a>Draws a sector. </p>
</td>
</tr>
<tr id="row46082499093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p363250066093533"><a name="p363250066093533"></a><a name="p363250066093533"></a><a href="Graphic.md#ga620028da5c71f96416becc877331ba6c">DrawArc</a> (const <a href="OHOS-Point.md">Point</a> &amp;center, uint16_t radius, int16_t startAngle, int16_t endAngle, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2116254732093533"><a name="p2116254732093533"></a><a name="p2116254732093533"></a>void&nbsp;</p>
<p id="p1344552630093533"><a name="p1344552630093533"></a><a name="p1344552630093533"></a>Draws an arc. </p>
</td>
</tr>
<tr id="row567490442093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p685554775093533"><a name="p685554775093533"></a><a name="p685554775093533"></a><a href="Graphic.md#gad5810166b3e02f41319dd4f4229c516c">DrawImage</a> (const <a href="OHOS-Point.md">Point</a> &amp;startPoint, const char *image, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1922451320093533"><a name="p1922451320093533"></a><a name="p1922451320093533"></a>void&nbsp;</p>
<p id="p474315701093533"><a name="p474315701093533"></a><a name="p474315701093533"></a>Draws an image. </p>
</td>
</tr>
<tr id="row1662792704093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1646157204093533"><a name="p1646157204093533"></a><a name="p1646157204093533"></a><a href="Graphic.md#ga32d815e5a459b4a866217a7c5c4bb425">DrawLabel</a> (const <a href="OHOS-Point.md">Point</a> &amp;startPoint, const char *text, uint16_t maxWidth, const <a href="OHOS-UICanvas-FontStyle.md">FontStyle</a> &amp;fontStyle, const <a href="OHOS-Paint.md">Paint</a> &amp;paint)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p625292961093533"><a name="p625292961093533"></a><a name="p625292961093533"></a>void&nbsp;</p>
<p id="p1613549269093533"><a name="p1613549269093533"></a><a name="p1613549269093533"></a>Draws text. </p>
</td>
</tr>
<tr id="row1330705818093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p997875141093533"><a name="p997875141093533"></a><a name="p997875141093533"></a><a href="Graphic.md#gac6122967d3e1f0d312eebed2f93a1369">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1511977217093533"><a name="p1511977217093533"></a><a name="p1511977217093533"></a>virtual void&nbsp;</p>
<p id="p1444873157093533"><a name="p1444873157093533"></a><a name="p1444873157093533"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1074932636093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2088972709093533"><a name="p2088972709093533"></a><a name="p2088972709093533"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p509668282093533"><a name="p509668282093533"></a><a name="p509668282093533"></a>&nbsp;</p>
<p id="p441950506093533"><a name="p441950506093533"></a><a name="p441950506093533"></a>A default constructor used to create an <strong id="b1419089606093533"><a name="b1419089606093533"></a><a name="b1419089606093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row748496464093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1187177617093533"><a name="p1187177617093533"></a><a name="p1187177617093533"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2007171773093533"><a name="p2007171773093533"></a><a name="p2007171773093533"></a>&nbsp;</p>
<p id="p406595480093533"><a name="p406595480093533"></a><a name="p406595480093533"></a>A constructor used to create an <strong id="b60468330093533"><a name="b60468330093533"></a><a name="b60468330093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row110044787093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p815899965093533"><a name="p815899965093533"></a><a name="p815899965093533"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1985494361093533"><a name="p1985494361093533"></a><a name="p1985494361093533"></a>virtual&nbsp;</p>
<p id="p1666731731093533"><a name="p1666731731093533"></a><a name="p1666731731093533"></a>A destructor used to delete the <strong id="b792258029093533"><a name="b792258029093533"></a><a name="b792258029093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row353104933093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1270047610093533"><a name="p1270047610093533"></a><a name="p1270047610093533"></a><a href="Graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1190536019093533"><a name="p1190536019093533"></a><a name="p1190536019093533"></a>virtual bool&nbsp;</p>
<p id="p1943026031093533"><a name="p1943026031093533"></a><a name="p1943026031093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row120301695093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2137714044093533"><a name="p2137714044093533"></a><a name="p2137714044093533"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1349060594093533"><a name="p1349060594093533"></a><a name="p1349060594093533"></a>virtual void&nbsp;</p>
<p id="p1989959338093533"><a name="p1989959338093533"></a><a name="p1989959338093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row2059145789093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1860085670093533"><a name="p1860085670093533"></a><a name="p1860085670093533"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1670839705093533"><a name="p1670839705093533"></a><a name="p1670839705093533"></a>virtual void&nbsp;</p>
<p id="p1779636306093533"><a name="p1779636306093533"></a><a name="p1779636306093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1462674769093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1381313630093533"><a name="p1381313630093533"></a><a name="p1381313630093533"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1644089168093533"><a name="p1644089168093533"></a><a name="p1644089168093533"></a>void&nbsp;</p>
<p id="p946027288093533"><a name="p946027288093533"></a><a name="p946027288093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row81138153093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1579700059093533"><a name="p1579700059093533"></a><a name="p1579700059093533"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1551352802093533"><a name="p1551352802093533"></a><a name="p1551352802093533"></a>void&nbsp;</p>
<p id="p429093122093533"><a name="p429093122093533"></a><a name="p429093122093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1466691008093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1778082485093533"><a name="p1778082485093533"></a><a name="p1778082485093533"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p950050492093533"><a name="p950050492093533"></a><a name="p950050492093533"></a>virtual bool&nbsp;</p>
<p id="p1959183754093533"><a name="p1959183754093533"></a><a name="p1959183754093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row1681432325093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1675893198093533"><a name="p1675893198093533"></a><a name="p1675893198093533"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764932222093533"><a name="p764932222093533"></a><a name="p764932222093533"></a>virtual bool&nbsp;</p>
<p id="p884333796093533"><a name="p884333796093533"></a><a name="p884333796093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row1026818810093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p677586018093533"><a name="p677586018093533"></a><a name="p677586018093533"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p286290742093533"><a name="p286290742093533"></a><a name="p286290742093533"></a>virtual bool&nbsp;</p>
<p id="p663285689093533"><a name="p663285689093533"></a><a name="p663285689093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row760774653093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p13658713093533"><a name="p13658713093533"></a><a name="p13658713093533"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703952427093533"><a name="p1703952427093533"></a><a name="p1703952427093533"></a>virtual bool&nbsp;</p>
<p id="p1656876330093533"><a name="p1656876330093533"></a><a name="p1656876330093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row448705519093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1169385708093533"><a name="p1169385708093533"></a><a name="p1169385708093533"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p825379685093533"><a name="p825379685093533"></a><a name="p825379685093533"></a>virtual void&nbsp;</p>
<p id="p609709857093533"><a name="p609709857093533"></a><a name="p609709857093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row2099561591093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p222733255093533"><a name="p222733255093533"></a><a name="p222733255093533"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2026885562093533"><a name="p2026885562093533"></a><a name="p2026885562093533"></a>virtual void&nbsp;</p>
<p id="p648364807093533"><a name="p648364807093533"></a><a name="p648364807093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row996113527093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1956784710093533"><a name="p1956784710093533"></a><a name="p1956784710093533"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1317902615093533"><a name="p1317902615093533"></a><a name="p1317902615093533"></a>virtual void&nbsp;</p>
<p id="p1935197240093533"><a name="p1935197240093533"></a><a name="p1935197240093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1019744156093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p445135939093533"><a name="p445135939093533"></a><a name="p445135939093533"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p963149530093533"><a name="p963149530093533"></a><a name="p963149530093533"></a>virtual void&nbsp;</p>
<p id="p646290779093533"><a name="p646290779093533"></a><a name="p646290779093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row1657493981093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p334626392093533"><a name="p334626392093533"></a><a name="p334626392093533"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1535596011093533"><a name="p1535596011093533"></a><a name="p1535596011093533"></a>void&nbsp;</p>
<p id="p610699691093533"><a name="p610699691093533"></a><a name="p610699691093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row428939703093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p468894256093533"><a name="p468894256093533"></a><a name="p468894256093533"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p353327290093533"><a name="p353327290093533"></a><a name="p353327290093533"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p1364974821093533"><a name="p1364974821093533"></a><a name="p1364974821093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row340796681093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p665327970093533"><a name="p665327970093533"></a><a name="p665327970093533"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p817299416093533"><a name="p817299416093533"></a><a name="p817299416093533"></a>void&nbsp;</p>
<p id="p1742275765093533"><a name="p1742275765093533"></a><a name="p1742275765093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row148205818093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1949766391093533"><a name="p1949766391093533"></a><a name="p1949766391093533"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p955692592093533"><a name="p955692592093533"></a><a name="p955692592093533"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p1064252777093533"><a name="p1064252777093533"></a><a name="p1064252777093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1640893723093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p383767902093533"><a name="p383767902093533"></a><a name="p383767902093533"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p33786018093533"><a name="p33786018093533"></a><a name="p33786018093533"></a>void&nbsp;</p>
<p id="p907625660093533"><a name="p907625660093533"></a><a name="p907625660093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row825896749093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p958602023093533"><a name="p958602023093533"></a><a name="p958602023093533"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1875290388093533"><a name="p1875290388093533"></a><a name="p1875290388093533"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p106139398093533"><a name="p106139398093533"></a><a name="p106139398093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row2019522396093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1325434013093533"><a name="p1325434013093533"></a><a name="p1325434013093533"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1009262237093533"><a name="p1009262237093533"></a><a name="p1009262237093533"></a>void&nbsp;</p>
<p id="p2028694995093533"><a name="p2028694995093533"></a><a name="p2028694995093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row1085864487093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1342889098093533"><a name="p1342889098093533"></a><a name="p1342889098093533"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p625834103093533"><a name="p625834103093533"></a><a name="p625834103093533"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p1048127106093533"><a name="p1048127106093533"></a><a name="p1048127106093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1913285722093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1505578034093533"><a name="p1505578034093533"></a><a name="p1505578034093533"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1968115863093533"><a name="p1968115863093533"></a><a name="p1968115863093533"></a>virtual void&nbsp;</p>
<p id="p406218203093533"><a name="p406218203093533"></a><a name="p406218203093533"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row1006765038093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p188569333093533"><a name="p188569333093533"></a><a name="p188569333093533"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p504059815093533"><a name="p504059815093533"></a><a name="p504059815093533"></a>void&nbsp;</p>
<p id="p562995346093533"><a name="p562995346093533"></a><a name="p562995346093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row1449317726093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806535029093533"><a name="p1806535029093533"></a><a name="p1806535029093533"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p802026011093533"><a name="p802026011093533"></a><a name="p802026011093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1451839188093533"><a name="p1451839188093533"></a><a name="p1451839188093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row609213362093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p265720403093533"><a name="p265720403093533"></a><a name="p265720403093533"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1460173006093533"><a name="p1460173006093533"></a><a name="p1460173006093533"></a>void&nbsp;</p>
<p id="p4723193093533"><a name="p4723193093533"></a><a name="p4723193093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1079517004093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2011283482093533"><a name="p2011283482093533"></a><a name="p2011283482093533"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p912197023093533"><a name="p912197023093533"></a><a name="p912197023093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p728603256093533"><a name="p728603256093533"></a><a name="p728603256093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row395967466093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p898666206093533"><a name="p898666206093533"></a><a name="p898666206093533"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1038679586093533"><a name="p1038679586093533"></a><a name="p1038679586093533"></a>virtual void&nbsp;</p>
<p id="p693180654093533"><a name="p693180654093533"></a><a name="p693180654093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row182949204093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p294601317093533"><a name="p294601317093533"></a><a name="p294601317093533"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1213710253093533"><a name="p1213710253093533"></a><a name="p1213710253093533"></a>bool&nbsp;</p>
<p id="p1848655101093533"><a name="p1848655101093533"></a><a name="p1848655101093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row653272433093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p543280247093533"><a name="p543280247093533"></a><a name="p543280247093533"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p774110784093533"><a name="p774110784093533"></a><a name="p774110784093533"></a>void&nbsp;</p>
<p id="p1134519792093533"><a name="p1134519792093533"></a><a name="p1134519792093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row961573470093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p931593580093533"><a name="p931593580093533"></a><a name="p931593580093533"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508191598093533"><a name="p508191598093533"></a><a name="p508191598093533"></a>bool&nbsp;</p>
<p id="p554800920093533"><a name="p554800920093533"></a><a name="p554800920093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row657047620093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1611942846093533"><a name="p1611942846093533"></a><a name="p1611942846093533"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p12821361093533"><a name="p12821361093533"></a><a name="p12821361093533"></a>void&nbsp;</p>
<p id="p505138447093533"><a name="p505138447093533"></a><a name="p505138447093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row980226041093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p248740995093533"><a name="p248740995093533"></a><a name="p248740995093533"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1108140460093533"><a name="p1108140460093533"></a><a name="p1108140460093533"></a>bool&nbsp;</p>
<p id="p785341392093533"><a name="p785341392093533"></a><a name="p785341392093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row339040282093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p346953800093533"><a name="p346953800093533"></a><a name="p346953800093533"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1084668995093533"><a name="p1084668995093533"></a><a name="p1084668995093533"></a>void&nbsp;</p>
<p id="p1655280082093533"><a name="p1655280082093533"></a><a name="p1655280082093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1514813100093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p341652172093533"><a name="p341652172093533"></a><a name="p341652172093533"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1032760679093533"><a name="p1032760679093533"></a><a name="p1032760679093533"></a>bool&nbsp;</p>
<p id="p69376954093533"><a name="p69376954093533"></a><a name="p69376954093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row642183775093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1897321526093533"><a name="p1897321526093533"></a><a name="p1897321526093533"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1582261896093533"><a name="p1582261896093533"></a><a name="p1582261896093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1685295166093533"><a name="p1685295166093533"></a><a name="p1685295166093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row1144714012093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p329222639093533"><a name="p329222639093533"></a><a name="p329222639093533"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2066136297093533"><a name="p2066136297093533"></a><a name="p2066136297093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1395590490093533"><a name="p1395590490093533"></a><a name="p1395590490093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row561582831093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p385144236093533"><a name="p385144236093533"></a><a name="p385144236093533"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p3689370093533"><a name="p3689370093533"></a><a name="p3689370093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1475972802093533"><a name="p1475972802093533"></a><a name="p1475972802093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row251382934093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2076555204093533"><a name="p2076555204093533"></a><a name="p2076555204093533"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p79238221093533"><a name="p79238221093533"></a><a name="p79238221093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p753205002093533"><a name="p753205002093533"></a><a name="p753205002093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row454678463093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1818236358093533"><a name="p1818236358093533"></a><a name="p1818236358093533"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p882384489093533"><a name="p882384489093533"></a><a name="p882384489093533"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1444528364093533"><a name="p1444528364093533"></a><a name="p1444528364093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row571833502093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1197923007093533"><a name="p1197923007093533"></a><a name="p1197923007093533"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p853906350093533"><a name="p853906350093533"></a><a name="p853906350093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p756948824093533"><a name="p756948824093533"></a><a name="p756948824093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1739814390093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1293314474093533"><a name="p1293314474093533"></a><a name="p1293314474093533"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p508582773093533"><a name="p508582773093533"></a><a name="p508582773093533"></a>void&nbsp;</p>
<p id="p1436357896093533"><a name="p1436357896093533"></a><a name="p1436357896093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row350827626093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1762177074093533"><a name="p1762177074093533"></a><a name="p1762177074093533"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p947322406093533"><a name="p947322406093533"></a><a name="p947322406093533"></a>virtual void&nbsp;</p>
<p id="p1097786967093533"><a name="p1097786967093533"></a><a name="p1097786967093533"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row1513922735093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p514908834093533"><a name="p514908834093533"></a><a name="p514908834093533"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p345551604093533"><a name="p345551604093533"></a><a name="p345551604093533"></a>virtual int16_t&nbsp;</p>
<p id="p736768673093533"><a name="p736768673093533"></a><a name="p736768673093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row389894417093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1121287495093533"><a name="p1121287495093533"></a><a name="p1121287495093533"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1880613755093533"><a name="p1880613755093533"></a><a name="p1880613755093533"></a>virtual void&nbsp;</p>
<p id="p1885992844093533"><a name="p1885992844093533"></a><a name="p1885992844093533"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row411650274093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1283380851093533"><a name="p1283380851093533"></a><a name="p1283380851093533"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1802557464093533"><a name="p1802557464093533"></a><a name="p1802557464093533"></a>virtual int16_t&nbsp;</p>
<p id="p608447437093533"><a name="p608447437093533"></a><a name="p608447437093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row709743217093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1131505300093533"><a name="p1131505300093533"></a><a name="p1131505300093533"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p864022715093533"><a name="p864022715093533"></a><a name="p864022715093533"></a>virtual void&nbsp;</p>
<p id="p975963867093533"><a name="p975963867093533"></a><a name="p975963867093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row1151137838093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1586387360093533"><a name="p1586387360093533"></a><a name="p1586387360093533"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2108839202093533"><a name="p2108839202093533"></a><a name="p2108839202093533"></a>virtual void&nbsp;</p>
<p id="p870183020093533"><a name="p870183020093533"></a><a name="p870183020093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row380316380093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1509822089093533"><a name="p1509822089093533"></a><a name="p1509822089093533"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2126967876093533"><a name="p2126967876093533"></a><a name="p2126967876093533"></a>int16_t&nbsp;</p>
<p id="p1454723104093533"><a name="p1454723104093533"></a><a name="p1454723104093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row2119216800093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1081405142093533"><a name="p1081405142093533"></a><a name="p1081405142093533"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1103615920093533"><a name="p1103615920093533"></a><a name="p1103615920093533"></a>virtual void&nbsp;</p>
<p id="p2006781191093533"><a name="p2006781191093533"></a><a name="p2006781191093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1724189839093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793396671093533"><a name="p793396671093533"></a><a name="p793396671093533"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p38686549093533"><a name="p38686549093533"></a><a name="p38686549093533"></a>int16_t&nbsp;</p>
<p id="p1970443380093533"><a name="p1970443380093533"></a><a name="p1970443380093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1540513372093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1805450361093533"><a name="p1805450361093533"></a><a name="p1805450361093533"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p557719587093533"><a name="p557719587093533"></a><a name="p557719587093533"></a>virtual void&nbsp;</p>
<p id="p1735960427093533"><a name="p1735960427093533"></a><a name="p1735960427093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row413551083093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1842271744093533"><a name="p1842271744093533"></a><a name="p1842271744093533"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1418612040093533"><a name="p1418612040093533"></a><a name="p1418612040093533"></a>virtual void&nbsp;</p>
<p id="p1652920059093533"><a name="p1652920059093533"></a><a name="p1652920059093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1331955858093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1223552754093533"><a name="p1223552754093533"></a><a name="p1223552754093533"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1391200125093533"><a name="p1391200125093533"></a><a name="p1391200125093533"></a>bool&nbsp;</p>
<p id="p358883848093533"><a name="p358883848093533"></a><a name="p358883848093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row977505342093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1503303530093533"><a name="p1503303530093533"></a><a name="p1503303530093533"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1908001335093533"><a name="p1908001335093533"></a><a name="p1908001335093533"></a>void&nbsp;</p>
<p id="p2141742667093533"><a name="p2141742667093533"></a><a name="p2141742667093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row659263867093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1329509093093533"><a name="p1329509093093533"></a><a name="p1329509093093533"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p159407517093533"><a name="p159407517093533"></a><a name="p159407517093533"></a>void&nbsp;</p>
<p id="p1102502677093533"><a name="p1102502677093533"></a><a name="p1102502677093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1293153605093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1240088938093533"><a name="p1240088938093533"></a><a name="p1240088938093533"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p217926973093533"><a name="p217926973093533"></a><a name="p217926973093533"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p925443904093533"><a name="p925443904093533"></a><a name="p925443904093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1076260624093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p59218440093533"><a name="p59218440093533"></a><a name="p59218440093533"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1108207119093533"><a name="p1108207119093533"></a><a name="p1108207119093533"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p502818293093533"><a name="p502818293093533"></a><a name="p502818293093533"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row1581763339093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p977603419093533"><a name="p977603419093533"></a><a name="p977603419093533"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2015695209093533"><a name="p2015695209093533"></a><a name="p2015695209093533"></a>void&nbsp;</p>
<p id="p1196595549093533"><a name="p1196595549093533"></a><a name="p1196595549093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row943496483093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p311121817093533"><a name="p311121817093533"></a><a name="p311121817093533"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p83635597093533"><a name="p83635597093533"></a><a name="p83635597093533"></a>const char *&nbsp;</p>
<p id="p1105911602093533"><a name="p1105911602093533"></a><a name="p1105911602093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row2133979936093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1029486908093533"><a name="p1029486908093533"></a><a name="p1029486908093533"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1193240368093533"><a name="p1193240368093533"></a><a name="p1193240368093533"></a>void&nbsp;</p>
<p id="p1841770435093533"><a name="p1841770435093533"></a><a name="p1841770435093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row157552662093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p39538018093533"><a name="p39538018093533"></a><a name="p39538018093533"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2096018459093533"><a name="p2096018459093533"></a><a name="p2096018459093533"></a>int16_t&nbsp;</p>
<p id="p2042070284093533"><a name="p2042070284093533"></a><a name="p2042070284093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row31134945093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p571911189093533"><a name="p571911189093533"></a><a name="p571911189093533"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p860945468093533"><a name="p860945468093533"></a><a name="p860945468093533"></a>virtual void&nbsp;</p>
<p id="p1497538577093533"><a name="p1497538577093533"></a><a name="p1497538577093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1583782873093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p239879891093533"><a name="p239879891093533"></a><a name="p239879891093533"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1524082755093533"><a name="p1524082755093533"></a><a name="p1524082755093533"></a>void&nbsp;</p>
<p id="p790176619093533"><a name="p790176619093533"></a><a name="p790176619093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row1797703585093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p557885346093533"><a name="p557885346093533"></a><a name="p557885346093533"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p373234618093533"><a name="p373234618093533"></a><a name="p373234618093533"></a>void&nbsp;</p>
<p id="p1279310210093533"><a name="p1279310210093533"></a><a name="p1279310210093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row2098509153093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p655630088093533"><a name="p655630088093533"></a><a name="p655630088093533"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2072137586093533"><a name="p2072137586093533"></a><a name="p2072137586093533"></a>void&nbsp;</p>
<p id="p1350566136093533"><a name="p1350566136093533"></a><a name="p1350566136093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row456711186093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p122914260093533"><a name="p122914260093533"></a><a name="p122914260093533"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2053027449093533"><a name="p2053027449093533"></a><a name="p2053027449093533"></a>void&nbsp;</p>
<p id="p607888857093533"><a name="p607888857093533"></a><a name="p607888857093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1387212902093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p126323457093533"><a name="p126323457093533"></a><a name="p126323457093533"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1457041484093533"><a name="p1457041484093533"></a><a name="p1457041484093533"></a>void&nbsp;</p>
<p id="p1042515053093533"><a name="p1042515053093533"></a><a name="p1042515053093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row517614850093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p374154813093533"><a name="p374154813093533"></a><a name="p374154813093533"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p79887878093533"><a name="p79887878093533"></a><a name="p79887878093533"></a>void&nbsp;</p>
<p id="p1827979340093533"><a name="p1827979340093533"></a><a name="p1827979340093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row783330470093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p451978014093533"><a name="p451978014093533"></a><a name="p451978014093533"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1176540618093533"><a name="p1176540618093533"></a><a name="p1176540618093533"></a>void&nbsp;</p>
<p id="p1360253696093533"><a name="p1360253696093533"></a><a name="p1360253696093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row399811190093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p444673999093533"><a name="p444673999093533"></a><a name="p444673999093533"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1998877215093533"><a name="p1998877215093533"></a><a name="p1998877215093533"></a>void&nbsp;</p>
<p id="p1042970870093533"><a name="p1042970870093533"></a><a name="p1042970870093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1768567531093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1257855672093533"><a name="p1257855672093533"></a><a name="p1257855672093533"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403362776093533"><a name="p1403362776093533"></a><a name="p1403362776093533"></a>void&nbsp;</p>
<p id="p1273397793093533"><a name="p1273397793093533"></a><a name="p1273397793093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row2098352410093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p199063412093533"><a name="p199063412093533"></a><a name="p199063412093533"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2017646358093533"><a name="p2017646358093533"></a><a name="p2017646358093533"></a>void&nbsp;</p>
<p id="p2128670849093533"><a name="p2128670849093533"></a><a name="p2128670849093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row339391244093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p66083666093533"><a name="p66083666093533"></a><a name="p66083666093533"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p813027812093533"><a name="p813027812093533"></a><a name="p813027812093533"></a>void&nbsp;</p>
<p id="p1920242566093533"><a name="p1920242566093533"></a><a name="p1920242566093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1179723306093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p435616770093533"><a name="p435616770093533"></a><a name="p435616770093533"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1945694413093533"><a name="p1945694413093533"></a><a name="p1945694413093533"></a>void&nbsp;</p>
<p id="p1514550167093533"><a name="p1514550167093533"></a><a name="p1514550167093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1761845441093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p584659838093533"><a name="p584659838093533"></a><a name="p584659838093533"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1680973113093533"><a name="p1680973113093533"></a><a name="p1680973113093533"></a>void&nbsp;</p>
<p id="p722286650093533"><a name="p722286650093533"></a><a name="p722286650093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row379631594093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1305169983093533"><a name="p1305169983093533"></a><a name="p1305169983093533"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1466908310093533"><a name="p1466908310093533"></a><a name="p1466908310093533"></a>void&nbsp;</p>
<p id="p1047307812093533"><a name="p1047307812093533"></a><a name="p1047307812093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row815621599093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1815164174093533"><a name="p1815164174093533"></a><a name="p1815164174093533"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1365538698093533"><a name="p1365538698093533"></a><a name="p1365538698093533"></a>void&nbsp;</p>
<p id="p863691346093533"><a name="p863691346093533"></a><a name="p863691346093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1817298714093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p829907920093533"><a name="p829907920093533"></a><a name="p829907920093533"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1890994665093533"><a name="p1890994665093533"></a><a name="p1890994665093533"></a>virtual void&nbsp;</p>
<p id="p1778147741093533"><a name="p1778147741093533"></a><a name="p1778147741093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1340061361093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1635330128093533"><a name="p1635330128093533"></a><a name="p1635330128093533"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p20691142093533"><a name="p20691142093533"></a><a name="p20691142093533"></a>virtual void&nbsp;</p>
<p id="p1758194384093533"><a name="p1758194384093533"></a><a name="p1758194384093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1027858524093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1706939630093533"><a name="p1706939630093533"></a><a name="p1706939630093533"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1578823629093533"><a name="p1578823629093533"></a><a name="p1578823629093533"></a>virtual int64_t&nbsp;</p>
<p id="p400651045093533"><a name="p400651045093533"></a><a name="p400651045093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1698007473093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p927250235093533"><a name="p927250235093533"></a><a name="p927250235093533"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833312290093533"><a name="p833312290093533"></a><a name="p833312290093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p418272487093533"><a name="p418272487093533"></a><a name="p418272487093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row421106473093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1235060992093533"><a name="p1235060992093533"></a><a name="p1235060992093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1444924630093533"><a name="p1444924630093533"></a><a name="p1444924630093533"></a>void *&nbsp;</p>
<p id="p2110284407093533"><a name="p2110284407093533"></a><a name="p2110284407093533"></a>Overrides the <strong id="b1493212063093533"><a name="b1493212063093533"></a><a name="b1493212063093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row994194818093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1178136688093533"><a name="p1178136688093533"></a><a name="p1178136688093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2051978332093533"><a name="p2051978332093533"></a><a name="p2051978332093533"></a>void&nbsp;</p>
<p id="p134631706093533"><a name="p134631706093533"></a><a name="p134631706093533"></a>Overrides the <strong id="b1970917644093533"><a name="b1970917644093533"></a><a name="b1970917644093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

