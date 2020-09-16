# OHOS::UIChartDataSerial<a name="ZH-CN_TOPIC_0000001055678116"></a>

## **Overview**<a name="section158970526093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines a data set and provides functions such as adding and deleting data points. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section201835883093534"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1792129164093534"></a>
<table><thead align="left"><tr id="row768166562093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1447649604093534"><a name="p1447649604093534"></a><a name="p1447649604093534"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1688433302093534"><a name="p1688433302093534"></a><a name="p1688433302093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1090351353093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p767218439093534"><a name="p767218439093534"></a><a name="p767218439093534"></a><a href="OHOS-UIChartDataSerial-PointStyle.md">PointStyle</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p865946940093534"><a name="p865946940093534"></a><a name="p865946940093534"></a>Defines the style for the top, bottom, and frontmost points in a line chart. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table590786489093534"></a>
<table><thead align="left"><tr id="row856407276093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p889523351093534"><a name="p889523351093534"></a><a name="p889523351093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1849215184093534"><a name="p1849215184093534"></a><a name="p1849215184093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row203961222093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2003330432093534"><a name="p2003330432093534"></a><a name="p2003330432093534"></a><a href="Graphic.md#ga8f1555cd3433927a650e7800a8746779">UIChartDataSerial</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1150632005093534"><a name="p1150632005093534"></a><a name="p1150632005093534"></a>&nbsp;</p>
<p id="p1625369264093534"><a name="p1625369264093534"></a><a name="p1625369264093534"></a>A constructor used to create a <strong id="b1461002221093534"><a name="b1461002221093534"></a><a name="b1461002221093534"></a><a href="OHOS-UIChartDataSerial.md">UIChartDataSerial</a></strong> instance. </p>
</td>
</tr>
<tr id="row1651227074093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1676531416093534"><a name="p1676531416093534"></a><a name="p1676531416093534"></a><a href="Graphic.md#gaaf2cda0d138bb4b3a752f875f146a5bc">~UIChartDataSerial</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1165540845093534"><a name="p1165540845093534"></a><a name="p1165540845093534"></a>virtual&nbsp;</p>
<p id="p2102032855093534"><a name="p2102032855093534"></a><a name="p2102032855093534"></a>A destructor used to delete the <strong id="b517933263093534"><a name="b517933263093534"></a><a name="b517933263093534"></a><a href="OHOS-UIChartDataSerial.md">UIChartDataSerial</a></strong> instance. </p>
</td>
</tr>
<tr id="row1300173854093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p827874570093534"><a name="p827874570093534"></a><a name="p827874570093534"></a><a href="Graphic.md#ga81133f20156b6dc269927a5be9caf653">SetMaxDataCount</a> (uint16_t maxCount)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p928255995093534"><a name="p928255995093534"></a><a name="p928255995093534"></a>bool&nbsp;</p>
<p id="p187084399093534"><a name="p187084399093534"></a><a name="p187084399093534"></a>Sets the maximum number of data points that can be stored in a data set. </p>
</td>
</tr>
<tr id="row553321442093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p565215837093534"><a name="p565215837093534"></a><a name="p565215837093534"></a><a href="Graphic.md#gaa4e5a9c7d456a3753020a3fb88159c83">ModifyPoint</a> (uint16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, const <a href="OHOS-Point.md">Point</a> &amp;point)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p694548479093534"><a name="p694548479093534"></a><a name="p694548479093534"></a>bool&nbsp;</p>
<p id="p1315474300093534"><a name="p1315474300093534"></a><a name="p1315474300093534"></a>Modifies the value of a data point in the data set. </p>
</td>
</tr>
<tr id="row1293363055093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p989373661093534"><a name="p989373661093534"></a><a name="p989373661093534"></a><a href="Graphic.md#ga32f85e7d3d9c67d491caa4105c6fa379">GetPoint</a> (uint16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, <a href="OHOS-Point.md">Point</a> &amp;point)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p897613552093534"><a name="p897613552093534"></a><a name="p897613552093534"></a>bool&nbsp;</p>
<p id="p1801166683093534"><a name="p1801166683093534"></a><a name="p1801166683093534"></a>Obtains the coordinates in the chart for a data point in the data set. </p>
</td>
</tr>
<tr id="row1691163119093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p128418934093534"><a name="p128418934093534"></a><a name="p128418934093534"></a><a href="Graphic.md#ga88d554725405cf9c501f145a25448238">AddPoints</a> (const <a href="OHOS-Point.md">Point</a> *data, uint16_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p82943980093534"><a name="p82943980093534"></a><a name="p82943980093534"></a>bool&nbsp;</p>
<p id="p2019273529093534"><a name="p2019273529093534"></a><a name="p2019273529093534"></a>Adds data points. </p>
</td>
</tr>
<tr id="row2138623084093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1193387021093534"><a name="p1193387021093534"></a><a name="p1193387021093534"></a><a href="Graphic.md#ga148d9b3933a733433a96a48b95cff844">ClearData</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p217522231093534"><a name="p217522231093534"></a><a name="p217522231093534"></a>void&nbsp;</p>
<p id="p225134075093534"><a name="p225134075093534"></a><a name="p225134075093534"></a>Clears all data points. </p>
</td>
</tr>
<tr id="row1796823358093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1242937887093534"><a name="p1242937887093534"></a><a name="p1242937887093534"></a><a href="Graphic.md#ga42b69b4725ed1d61bb8da019562c3fb2">GetDataCount</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2064687070093534"><a name="p2064687070093534"></a><a name="p2064687070093534"></a>uint16_t&nbsp;</p>
<p id="p541487578093534"><a name="p541487578093534"></a><a name="p541487578093534"></a>Obtains the number of data points available in the data set. </p>
</td>
</tr>
<tr id="row188604643093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1916539734093534"><a name="p1916539734093534"></a><a name="p1916539734093534"></a><a href="Graphic.md#ga9a3d5d81adbef7f847b631d03a472fbd">EnableSmooth</a> (bool smooth)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1619935692093534"><a name="p1619935692093534"></a><a name="p1619935692093534"></a>void&nbsp;</p>
<p id="p1400824963093534"><a name="p1400824963093534"></a><a name="p1400824963093534"></a>Sets whether to smooth a polyline. </p>
</td>
</tr>
<tr id="row2068267732093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p963692277093534"><a name="p963692277093534"></a><a name="p963692277093534"></a><a href="Graphic.md#ga5d9211f3eaee4e1c9455709a228087fe">IsSmooth</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p216226706093534"><a name="p216226706093534"></a><a name="p216226706093534"></a>bool&nbsp;</p>
<p id="p795296531093534"><a name="p795296531093534"></a><a name="p795296531093534"></a>Checks whether smoothing is performed on a polyline. </p>
</td>
</tr>
<tr id="row1124325739093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2146486298093534"><a name="p2146486298093534"></a><a name="p2146486298093534"></a><a href="Graphic.md#gaa4635e5332809fc7a275c4077f9d140d">EnableGradient</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p191492021093534"><a name="p191492021093534"></a><a name="p191492021093534"></a>void&nbsp;</p>
<p id="p1297695117093534"><a name="p1297695117093534"></a><a name="p1297695117093534"></a>Enables the fill color of a line chart. </p>
</td>
</tr>
<tr id="row1639267133093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1268667534093534"><a name="p1268667534093534"></a><a name="p1268667534093534"></a><a href="Graphic.md#ga6188c14ea249a34db4819499f4e38133">IsGradient</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1766129301093534"><a name="p1766129301093534"></a><a name="p1766129301093534"></a>bool&nbsp;</p>
<p id="p657412509093534"><a name="p657412509093534"></a><a name="p657412509093534"></a>Checks whether a polyline has a fill color. </p>
</td>
</tr>
<tr id="row455581336093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1125384066093534"><a name="p1125384066093534"></a><a name="p1125384066093534"></a><a href="Graphic.md#ga60c2b77e89d616a416a05f18b5c5c055">GetPeakIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p351304397093534"><a name="p351304397093534"></a><a name="p351304397093534"></a>uint16_t&nbsp;</p>
<p id="p447332922093534"><a name="p447332922093534"></a><a name="p447332922093534"></a>Obtains the index of the top point in the data set. </p>
</td>
</tr>
<tr id="row128057224093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2069489226093534"><a name="p2069489226093534"></a><a name="p2069489226093534"></a><a href="Graphic.md#ga390d7cfb4e3ced676ec6c7ac22c1ccc5">GetLatestIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p329584973093534"><a name="p329584973093534"></a><a name="p329584973093534"></a>uint16_t&nbsp;</p>
<p id="p1994307509093534"><a name="p1994307509093534"></a><a name="p1994307509093534"></a>Obtains the index of the frontmost point (the latest added or modified data point in a data set). </p>
</td>
</tr>
<tr id="row40050378093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p448892458093534"><a name="p448892458093534"></a><a name="p448892458093534"></a><a href="Graphic.md#ga630a7356e3dbcb212a2e88ef0c6b857d">GetValleyIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074767267093534"><a name="p1074767267093534"></a><a name="p1074767267093534"></a>uint16_t&nbsp;</p>
<p id="p85779028093534"><a name="p85779028093534"></a><a name="p85779028093534"></a>Obtains the index of the bottom point in a data set. </p>
</td>
</tr>
<tr id="row2139654943093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1304547476093534"><a name="p1304547476093534"></a><a name="p1304547476093534"></a><a href="Graphic.md#gaf6c796fbd08cab47cf4fc0d41185a591">GetPeakData</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1313446707093534"><a name="p1313446707093534"></a><a name="p1313446707093534"></a>int16_t&nbsp;</p>
<p id="p657972922093534"><a name="p657972922093534"></a><a name="p657972922093534"></a>Obtains the Y value of the top point in a data set. </p>
</td>
</tr>
<tr id="row438425205093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1353052478093534"><a name="p1353052478093534"></a><a name="p1353052478093534"></a><a href="Graphic.md#gae75c525df3451cb5e863d15fd36db07e">GetValleyData</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1651815675093534"><a name="p1651815675093534"></a><a name="p1651815675093534"></a>int16_t&nbsp;</p>
<p id="p1154089791093534"><a name="p1154089791093534"></a><a name="p1154089791093534"></a>Obtains the Y value of the bottom point in a data set. </p>
</td>
</tr>
<tr id="row61959272093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p228682696093534"><a name="p228682696093534"></a><a name="p228682696093534"></a><a href="Graphic.md#gaa35d69c841a74505735d1acb60476f13">GetLineColor</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p152875444093534"><a name="p152875444093534"></a><a name="p152875444093534"></a><a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p962975921093534"><a name="p962975921093534"></a><a name="p962975921093534"></a>Obtains the polyline color of the data set in a line chart. </p>
</td>
</tr>
<tr id="row1699566421093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1700845066093534"><a name="p1700845066093534"></a><a name="p1700845066093534"></a><a href="Graphic.md#ga3b20df3a339aa0f41d404eb3dc1d12ca">GetFillColor</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p467376690093534"><a name="p467376690093534"></a><a name="p467376690093534"></a><a href="OHOS-Color32.md">ColorType</a>&nbsp;</p>
<p id="p575783464093534"><a name="p575783464093534"></a><a name="p575783464093534"></a>Obtains the fill color of the data set. </p>
</td>
</tr>
<tr id="row1801901214093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1147156780093534"><a name="p1147156780093534"></a><a name="p1147156780093534"></a><a href="Graphic.md#gac620b9878a5e28d066dffbcd6145539c">SetFillColor</a> (const <a href="OHOS-Color32.md">ColorType</a> &amp;color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1368260017093534"><a name="p1368260017093534"></a><a name="p1368260017093534"></a>void&nbsp;</p>
<p id="p1576711127093534"><a name="p1576711127093534"></a><a name="p1576711127093534"></a>Sets the fill color of the data set. </p>
</td>
</tr>
<tr id="row519395991093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p49430517093534"><a name="p49430517093534"></a><a name="p49430517093534"></a><a href="Graphic.md#ga94beac0c71885b8546996271c876f999">SetLineColor</a> (const <a href="OHOS-Color32.md">ColorType</a> &amp;color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p877288967093534"><a name="p877288967093534"></a><a name="p877288967093534"></a>void&nbsp;</p>
<p id="p1328892736093534"><a name="p1328892736093534"></a><a name="p1328892736093534"></a>Sets the polyline color of the data set in the line chart. </p>
</td>
</tr>
<tr id="row1415150399093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p186930962093534"><a name="p186930962093534"></a><a name="p186930962093534"></a><a href="Graphic.md#ga02cb658da66c73863ac2a49849e23b24">HidePoint</a> (uint16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, uint16_t count)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1540795585093534"><a name="p1540795585093534"></a><a name="p1540795585093534"></a>void&nbsp;</p>
<p id="p800806290093534"><a name="p800806290093534"></a><a name="p800806290093534"></a>Hides some points in the data set. </p>
</td>
</tr>
<tr id="row1624636523093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2078073314093534"><a name="p2078073314093534"></a><a name="p2078073314093534"></a><a href="Graphic.md#ga607716e734fba2eef917fdee372e43b1">GetHideIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1775867768093534"><a name="p1775867768093534"></a><a name="p1775867768093534"></a>uint16_t&nbsp;</p>
<p id="p108786875093534"><a name="p108786875093534"></a><a name="p108786875093534"></a>Obtains the index from which the data set starts to hide. </p>
</td>
</tr>
<tr id="row1166886261093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244895946093534"><a name="p1244895946093534"></a><a name="p1244895946093534"></a><a href="Graphic.md#ga736907dd9f33b5335f0df5599f5cb006">GetHideCount</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p187248929093534"><a name="p187248929093534"></a><a name="p187248929093534"></a>uint16_t&nbsp;</p>
<p id="p285778973093534"><a name="p285778973093534"></a><a name="p285778973093534"></a>Obtains the number of hidden points in the data set. </p>
</td>
</tr>
<tr id="row1485708833093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p776821236093534"><a name="p776821236093534"></a><a name="p776821236093534"></a><a href="Graphic.md#ga8fcb9d0640963ff30ff010ca5d387ff2">SetHeadPointStyle</a> (const <a href="OHOS-UIChartDataSerial-PointStyle.md">PointStyle</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1386643855093534"><a name="p1386643855093534"></a><a name="p1386643855093534"></a>void&nbsp;</p>
<p id="p822988177093534"><a name="p822988177093534"></a><a name="p822988177093534"></a>Sets the style of the frontmost point on a polyline. </p>
</td>
</tr>
<tr id="row1289405883093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1789908966093534"><a name="p1789908966093534"></a><a name="p1789908966093534"></a><a href="Graphic.md#ga91b0d5442e708e2d2bd39436b5d46baa">SetTopPointStyle</a> (const <a href="OHOS-UIChartDataSerial-PointStyle.md">PointStyle</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1414379272093534"><a name="p1414379272093534"></a><a name="p1414379272093534"></a>void&nbsp;</p>
<p id="p529410111093534"><a name="p529410111093534"></a><a name="p529410111093534"></a>Sets the style of the top point of a polyline. </p>
</td>
</tr>
<tr id="row484320139093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1853400039093534"><a name="p1853400039093534"></a><a name="p1853400039093534"></a><a href="Graphic.md#gab99eef3cd222625e8d3a30cca815ced2">SetBottomPointStyle</a> (const <a href="OHOS-UIChartDataSerial-PointStyle.md">PointStyle</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p473430178093534"><a name="p473430178093534"></a><a name="p473430178093534"></a>void&nbsp;</p>
<p id="p1508802270093534"><a name="p1508802270093534"></a><a name="p1508802270093534"></a>Sets the style of the bottom point of a polyline. </p>
</td>
</tr>
<tr id="row2062685254093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p820716243093534"><a name="p820716243093534"></a><a name="p820716243093534"></a><a href="Graphic.md#ga37a267a68383b41ce1d5c9072c2f7e83">GetHeadPointStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1396004386093534"><a name="p1396004386093534"></a><a name="p1396004386093534"></a>const <a href="OHOS-UIChartDataSerial-PointStyle.md">PointStyle</a> &amp;&nbsp;</p>
<p id="p1742083690093534"><a name="p1742083690093534"></a><a name="p1742083690093534"></a>Obtains the style of the frontmost point on a polyline. </p>
</td>
</tr>
<tr id="row1712091161093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1930657807093534"><a name="p1930657807093534"></a><a name="p1930657807093534"></a><a href="Graphic.md#ga215f5c5f8de923f0aa399a6bbdf78e18">GetTopPointStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1691744644093534"><a name="p1691744644093534"></a><a name="p1691744644093534"></a>const <a href="OHOS-UIChartDataSerial-PointStyle.md">PointStyle</a> &amp;&nbsp;</p>
<p id="p542267081093534"><a name="p542267081093534"></a><a name="p542267081093534"></a>Obtains the style of the top point of a polyline. </p>
</td>
</tr>
<tr id="row1356481282093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p924504776093534"><a name="p924504776093534"></a><a name="p924504776093534"></a><a href="Graphic.md#gaca803ecb139a0dae90825748bdbbf12b">GetBottomPointStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1848532947093534"><a name="p1848532947093534"></a><a name="p1848532947093534"></a>const <a href="OHOS-UIChartDataSerial-PointStyle.md">PointStyle</a> &amp;&nbsp;</p>
<p id="p539296075093534"><a name="p539296075093534"></a><a name="p539296075093534"></a>Obtains the style of the bottom point of a polyline. </p>
</td>
</tr>
<tr id="row1215678752093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p894359813093534"><a name="p894359813093534"></a><a name="p894359813093534"></a><a href="Graphic.md#gaa90973e2315035570ffae0d4c3c2e976">EnableHeadPoint</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1230147157093534"><a name="p1230147157093534"></a><a name="p1230147157093534"></a>void&nbsp;</p>
<p id="p1595826646093534"><a name="p1595826646093534"></a><a name="p1595826646093534"></a>Enables the feature of drawing the frontmost point on a polyline. </p>
</td>
</tr>
<tr id="row333263759093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p705865244093534"><a name="p705865244093534"></a><a name="p705865244093534"></a><a href="Graphic.md#gab97d84ead6aa301d2ae23fc68aa98a9f">EnableTopPoint</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1354124733093534"><a name="p1354124733093534"></a><a name="p1354124733093534"></a>void&nbsp;</p>
<p id="p154100996093534"><a name="p154100996093534"></a><a name="p154100996093534"></a>Enables the feature of drawing the top point of a polyline. If there are multiple top points, only the first one is drawn. </p>
</td>
</tr>
<tr id="row1103993440093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1854528706093534"><a name="p1854528706093534"></a><a name="p1854528706093534"></a><a href="Graphic.md#ga2c0d693d31efd256cc6529255699ddd3">EnableBottomPoint</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1042231543093534"><a name="p1042231543093534"></a><a name="p1042231543093534"></a>void&nbsp;</p>
<p id="p627340249093534"><a name="p627340249093534"></a><a name="p627340249093534"></a>Enables the feature of drawing the bottom point of a polyline. If there are multiple bottom points, only the first one is drawn. </p>
</td>
</tr>
<tr id="row877457731093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p723400350093534"><a name="p723400350093534"></a><a name="p723400350093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1838909129093534"><a name="p1838909129093534"></a><a name="p1838909129093534"></a>void *&nbsp;</p>
<p id="p656297357093534"><a name="p656297357093534"></a><a name="p656297357093534"></a>Overrides the <strong id="b1645802996093534"><a name="b1645802996093534"></a><a name="b1645802996093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1680806665093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2051867826093534"><a name="p2051867826093534"></a><a name="p2051867826093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1375288287093534"><a name="p1375288287093534"></a><a name="p1375288287093534"></a>void&nbsp;</p>
<p id="p759220763093534"><a name="p759220763093534"></a><a name="p759220763093534"></a>Overrides the <strong id="b276563138093534"><a name="b276563138093534"></a><a name="b276563138093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

