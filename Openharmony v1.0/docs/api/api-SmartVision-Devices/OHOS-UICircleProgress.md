# OHOS::UICircleProgress<a name="ZH-CN_TOPIC_0000001054879556"></a>

## **Overview**<a name="section837527900093534"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents a circular progress bar. 

This class is used to set the start and end angles, range, and current value to display the circular progress bar.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section57054819093534"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table995419933093534"></a>
<table><thead align="left"><tr id="row695943516093534"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p645068472093534"><a name="p645068472093534"></a><a name="p645068472093534"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p132863448093534"><a name="p132863448093534"></a><a name="p132863448093534"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1396616069093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1430631484093534"><a name="p1430631484093534"></a><a name="p1430631484093534"></a><a href="Graphic.md#gae6d547653f0448f9151fa257cbf9c3ac">UICircleProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p656575673093534"><a name="p656575673093534"></a><a name="p656575673093534"></a>&nbsp;</p>
<p id="p791909357093534"><a name="p791909357093534"></a><a name="p791909357093534"></a>A constructor used to create a <strong id="b1890992425093534"><a name="b1890992425093534"></a><a name="b1890992425093534"></a><a href="OHOS-UICircleProgress.md">UICircleProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row839967514093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2079069560093534"><a name="p2079069560093534"></a><a name="p2079069560093534"></a><a href="Graphic.md#ga10a9da813e933b3513e22a95bb81af98">~UICircleProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1383846310093534"><a name="p1383846310093534"></a><a name="p1383846310093534"></a>virtual&nbsp;</p>
<p id="p45198609093534"><a name="p45198609093534"></a><a name="p45198609093534"></a>A destructor used to delete the <strong id="b235664980093534"><a name="b235664980093534"></a><a name="b235664980093534"></a><a href="OHOS-UICircleProgress.md">UICircleProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row1290350590093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1962507003093534"><a name="p1962507003093534"></a><a name="p1962507003093534"></a><a href="Graphic.md#gab1d8fc06d4a73db344efd271d68a62e6">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p895196976093534"><a name="p895196976093534"></a><a name="p895196976093534"></a>UIViewType&nbsp;</p>
<p id="p348924727093534"><a name="p348924727093534"></a><a name="p348924727093534"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row426625379093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p119814252093534"><a name="p119814252093534"></a><a name="p119814252093534"></a><a href="Graphic.md#ga98bc4ea99629e4d5c7ca5ca4b43e8e96">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1750381282093534"><a name="p1750381282093534"></a><a name="p1750381282093534"></a>bool&nbsp;</p>
<p id="p45278568093534"><a name="p45278568093534"></a><a name="p45278568093534"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row1777510650093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p381858501093534"><a name="p381858501093534"></a><a name="p381858501093534"></a><a href="Graphic.md#ga611f2f03c22499c428d1de3392ee4861">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1863894807093534"><a name="p1863894807093534"></a><a name="p1863894807093534"></a>void&nbsp;</p>
<p id="p233101099093534"><a name="p233101099093534"></a><a name="p233101099093534"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1670433991093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1039798409093534"><a name="p1039798409093534"></a><a name="p1039798409093534"></a><a href="Graphic.md#ga6cf6b8ab0934ce8c0ea1821da0791317">SetCenterPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1774757261093534"><a name="p1774757261093534"></a><a name="p1774757261093534"></a>void&nbsp;</p>
<p id="p1142566941093534"><a name="p1142566941093534"></a><a name="p1142566941093534"></a>Sets the coordinates of the center point for this circular progress bar. </p>
</td>
</tr>
<tr id="row1723528058093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617172179093534"><a name="p617172179093534"></a><a name="p617172179093534"></a><a href="Graphic.md#ga706ac374a1383cef01dfc59c5257e480">GetCenterPosition</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p945758152093534"><a name="p945758152093534"></a><a name="p945758152093534"></a><a href="OHOS-Point.md">Point</a>&nbsp;</p>
<p id="p842338205093534"><a name="p842338205093534"></a><a name="p842338205093534"></a>Obtains the coordinates of the center point for this circular progress bar. </p>
</td>
</tr>
<tr id="row1325495039093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p11081605093534"><a name="p11081605093534"></a><a name="p11081605093534"></a><a href="Graphic.md#ga80377fb579f6698cefd5fcf74d0cde46">SetRadius</a> (uint16_t radius)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695526600093534"><a name="p1695526600093534"></a><a name="p1695526600093534"></a>void&nbsp;</p>
<p id="p707670885093534"><a name="p707670885093534"></a><a name="p707670885093534"></a>Sets the outer radius for this circular progress bar. </p>
</td>
</tr>
<tr id="row1220358643093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p567391453093534"><a name="p567391453093534"></a><a name="p567391453093534"></a><a href="Graphic.md#gabb2869e683ccd799891a8869613ec8c7">GetRadius</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2097923549093534"><a name="p2097923549093534"></a><a name="p2097923549093534"></a>uint16_t&nbsp;</p>
<p id="p1779770427093534"><a name="p1779770427093534"></a><a name="p1779770427093534"></a>Obtains the outer radius of this circular progress bar. </p>
</td>
</tr>
<tr id="row1890047786093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p901762990093534"><a name="p901762990093534"></a><a name="p901762990093534"></a><a href="Graphic.md#gae27e30bd77b83bc55ecc9f2a5643943a">SetStartAngle</a> (int16_t startAngle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1148289630093534"><a name="p1148289630093534"></a><a name="p1148289630093534"></a>void&nbsp;</p>
<p id="p1848575217093534"><a name="p1848575217093534"></a><a name="p1848575217093534"></a>Sets the start angle. </p>
</td>
</tr>
<tr id="row1507947422093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p25300203093534"><a name="p25300203093534"></a><a name="p25300203093534"></a><a href="Graphic.md#ga37a3e63da7a8658e48a25ae9ec73abea">GetStartAngle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1199580964093534"><a name="p1199580964093534"></a><a name="p1199580964093534"></a>int16_t&nbsp;</p>
<p id="p1397982347093534"><a name="p1397982347093534"></a><a name="p1397982347093534"></a>Obtains the start angle. </p>
</td>
</tr>
<tr id="row747157121093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2078500626093534"><a name="p2078500626093534"></a><a name="p2078500626093534"></a><a href="Graphic.md#ga831186bf208f8236b006b13cc122c82c">SetEndAngle</a> (int16_t endAngle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p759297646093534"><a name="p759297646093534"></a><a name="p759297646093534"></a>void&nbsp;</p>
<p id="p2056183291093534"><a name="p2056183291093534"></a><a name="p2056183291093534"></a>Sets the end angle. </p>
</td>
</tr>
<tr id="row341270974093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1454255281093534"><a name="p1454255281093534"></a><a name="p1454255281093534"></a><a href="Graphic.md#gacab2327bfc24ee985818a95d468af181">GetEndAngle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p351293507093534"><a name="p351293507093534"></a><a name="p351293507093534"></a>int16_t&nbsp;</p>
<p id="p159525223093534"><a name="p159525223093534"></a><a name="p159525223093534"></a>Obtains the end angle. </p>
</td>
</tr>
<tr id="row1129315451093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p701100552093534"><a name="p701100552093534"></a><a name="p701100552093534"></a><a href="Graphic.md#ga62b71500ccc75673be297d2e114c0c1b">SetProgressImagePosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1343072631093534"><a name="p1343072631093534"></a><a name="p1343072631093534"></a>void&nbsp;</p>
<p id="p1909237965093534"><a name="p1909237965093534"></a><a name="p1909237965093534"></a>Sets the coordinates of the foreground image for this progress bar relative to the view. </p>
</td>
</tr>
<tr id="row344751737093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p614919798093534"><a name="p614919798093534"></a><a name="p614919798093534"></a><a href="Graphic.md#ga66b95a4793bc60596a56be00849b8296">SetBackgroundImagePosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p325450800093534"><a name="p325450800093534"></a><a name="p325450800093534"></a>void&nbsp;</p>
<p id="p288851360093534"><a name="p288851360093534"></a><a name="p288851360093534"></a>Sets the coordinates of the background image for this progress bar relative to the view. </p>
</td>
</tr>
<tr id="row256209495093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p785252306093534"><a name="p785252306093534"></a><a name="p785252306093534"></a><a href="Graphic.md#gad0453bc291f75f4864c112f9f2f474db">SetLineColor</a> (<a href="OHOS-Color32.md">ColorType</a> color)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p732965772093534"><a name="p732965772093534"></a><a name="p732965772093534"></a>void&nbsp;</p>
<p id="p2091219968093534"><a name="p2091219968093534"></a><a name="p2091219968093534"></a>Sets the foreground color for this progress bar. </p>
</td>
</tr>
<tr id="row853934227093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1827270169093534"><a name="p1827270169093534"></a><a name="p1827270169093534"></a><a href="Graphic.md#ga8f9bfb4f42ee0e094501ff776e3336da">UIAbstractProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1923676112093534"><a name="p1923676112093534"></a><a name="p1923676112093534"></a>&nbsp;</p>
<p id="p1678503894093534"><a name="p1678503894093534"></a><a name="p1678503894093534"></a>A constructor used to create a <strong id="b2003965832093534"><a name="b2003965832093534"></a><a name="b2003965832093534"></a><a href="OHOS-UIAbstractProgress.md">UIAbstractProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row1103984987093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p189338828093534"><a name="p189338828093534"></a><a name="p189338828093534"></a><a href="Graphic.md#ga5c1cf7239bf0c0f7d331e63df805b518">~UIAbstractProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1338164380093534"><a name="p1338164380093534"></a><a name="p1338164380093534"></a>virtual&nbsp;</p>
<p id="p452269358093534"><a name="p452269358093534"></a><a name="p452269358093534"></a>A destructor used to delete the <strong id="b264543677093534"><a name="b264543677093534"></a><a name="b264543677093534"></a><a href="OHOS-UIAbstractProgress.md">UIAbstractProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row718513185093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1770731770093534"><a name="p1770731770093534"></a><a name="p1770731770093534"></a><a href="Graphic.md#gacb680c1ddc9135371676df504dc6c8f2">EnableBackground</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p556590164093534"><a name="p556590164093534"></a><a name="p556590164093534"></a>void&nbsp;</p>
<p id="p190333442093534"><a name="p190333442093534"></a><a name="p190333442093534"></a>Sets whether the background of the progress bar is visible. </p>
</td>
</tr>
<tr id="row1513549462093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1116433600093534"><a name="p1116433600093534"></a><a name="p1116433600093534"></a><a href="Graphic.md#ga5f65014431a6489ffa1d4949f9c4449b">SetValue</a> (int16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p240138884093534"><a name="p240138884093534"></a><a name="p240138884093534"></a>void&nbsp;</p>
<p id="p941190375093534"><a name="p941190375093534"></a><a name="p941190375093534"></a>Sets the current value for this progress bar. </p>
</td>
</tr>
<tr id="row540341709093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1771473908093534"><a name="p1771473908093534"></a><a name="p1771473908093534"></a><a href="Graphic.md#ga6face76aa7972efeb6cbb8f525f23135">GetValue</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1496129066093534"><a name="p1496129066093534"></a><a name="p1496129066093534"></a>int16_t&nbsp;</p>
<p id="p2058655874093534"><a name="p2058655874093534"></a><a name="p2058655874093534"></a>Obtains the current value of this progress bar. </p>
</td>
</tr>
<tr id="row80759923093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1378571367093534"><a name="p1378571367093534"></a><a name="p1378571367093534"></a><a href="Graphic.md#ga089e3875453011499ad33ed89a44a699">SetRange</a> (int16_t rangeMax, int16_t rangeMin)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1757550572093534"><a name="p1757550572093534"></a><a name="p1757550572093534"></a>void&nbsp;</p>
<p id="p277083286093534"><a name="p277083286093534"></a><a name="p277083286093534"></a>Sets the range for this progress bar. </p>
</td>
</tr>
<tr id="row2094946103093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p750596805093534"><a name="p750596805093534"></a><a name="p750596805093534"></a><a href="Graphic.md#ga68ab733afcf4224a799ccad2092d1d23">GetRangeMin</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1237950991093534"><a name="p1237950991093534"></a><a name="p1237950991093534"></a>int16_t&nbsp;</p>
<p id="p2057916994093534"><a name="p2057916994093534"></a><a name="p2057916994093534"></a>Obtains the minimum value of this progress bar. </p>
</td>
</tr>
<tr id="row1107460455093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1996082682093534"><a name="p1996082682093534"></a><a name="p1996082682093534"></a><a href="Graphic.md#ga1840199f22d5d3e4ef58e41ac8f4febc">GetRangeMax</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1172925106093534"><a name="p1172925106093534"></a><a name="p1172925106093534"></a>int16_t&nbsp;</p>
<p id="p303629025093534"><a name="p303629025093534"></a><a name="p303629025093534"></a>Obtains the maximum value of this progress bar. </p>
</td>
</tr>
<tr id="row403056536093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p428623194093534"><a name="p428623194093534"></a><a name="p428623194093534"></a><a href="Graphic.md#ga5b3ec363e391f601e12bf937b9cf77db">SetImage</a> (const char *foregroundImage, const char *backgroundImage=nullptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2123711347093534"><a name="p2123711347093534"></a><a name="p2123711347093534"></a>void&nbsp;</p>
<p id="p1136671312093534"><a name="p1136671312093534"></a><a name="p1136671312093534"></a>Sets the image for this progress bar. </p>
</td>
</tr>
<tr id="row245394055093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2032321213093534"><a name="p2032321213093534"></a><a name="p2032321213093534"></a><a href="Graphic.md#ga10723293ab9e384907dd9dacbc9ad448">SetImage</a> (const <a href="OHOS-ImageInfo.md">ImageInfo</a> *foregroundImage, const <a href="OHOS-ImageInfo.md">ImageInfo</a> *backgroundImage=nullptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p720147380093534"><a name="p720147380093534"></a><a name="p720147380093534"></a>void&nbsp;</p>
<p id="p250055129093534"><a name="p250055129093534"></a><a name="p250055129093534"></a>Sets the image as a pixel map for this progress bar. </p>
</td>
</tr>
<tr id="row1006941664093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p300251157093534"><a name="p300251157093534"></a><a name="p300251157093534"></a><a href="Graphic.md#ga747a29652b441a06d09a97a297aae9bb">SetStep</a> (uint16_t step)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p600250226093534"><a name="p600250226093534"></a><a name="p600250226093534"></a>void&nbsp;</p>
<p id="p102939137093534"><a name="p102939137093534"></a><a name="p102939137093534"></a>Sets the step for this progress bar. </p>
</td>
</tr>
<tr id="row529387927093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p674385357093534"><a name="p674385357093534"></a><a name="p674385357093534"></a><a href="Graphic.md#ga9c1678604605a54c2e338d283c46866d">GetStep</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1025863885093534"><a name="p1025863885093534"></a><a name="p1025863885093534"></a>uint16_t&nbsp;</p>
<p id="p459697880093534"><a name="p459697880093534"></a><a name="p459697880093534"></a>Obtains the current step of this progress bar. </p>
</td>
</tr>
<tr id="row2020511671093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p400906545093534"><a name="p400906545093534"></a><a name="p400906545093534"></a><a href="Graphic.md#ga6817b5178e93e5f16f2b420cf5a171c1">SetBackgroundStyle</a> (const <a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p677564549093534"><a name="p677564549093534"></a><a name="p677564549093534"></a>void&nbsp;</p>
<p id="p995362324093534"><a name="p995362324093534"></a><a name="p995362324093534"></a>Sets the background style for this progress bar. </p>
</td>
</tr>
<tr id="row1066526479093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p272289280093534"><a name="p272289280093534"></a><a name="p272289280093534"></a><a href="Graphic.md#ga23acea0a42587746e35ec5f3a74af59f">SetBackgroundStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1854878365093534"><a name="p1854878365093534"></a><a name="p1854878365093534"></a>void&nbsp;</p>
<p id="p171822305093534"><a name="p171822305093534"></a><a name="p171822305093534"></a>Sets a background style for this progress bar. </p>
</td>
</tr>
<tr id="row1202301203093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1438173168093534"><a name="p1438173168093534"></a><a name="p1438173168093534"></a><a href="Graphic.md#gac2ca1212c23c11405b12ae0a46c7eff1">GetBackgroundStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1053561480093534"><a name="p1053561480093534"></a><a name="p1053561480093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1741623444093534"><a name="p1741623444093534"></a><a name="p1741623444093534"></a>Obtains the background style of this progress bar. </p>
</td>
</tr>
<tr id="row790539694093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1262853681093534"><a name="p1262853681093534"></a><a name="p1262853681093534"></a><a href="Graphic.md#ga946d3f2c39a79d45149118536b2557a9">GetBackgroundStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1064075300093534"><a name="p1064075300093534"></a><a name="p1064075300093534"></a>int64_t&nbsp;</p>
<p id="p1906037005093534"><a name="p1906037005093534"></a><a name="p1906037005093534"></a>Obtains the value of a background style of this progress bar. </p>
</td>
</tr>
<tr id="row1467350177093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1717093529093534"><a name="p1717093529093534"></a><a name="p1717093529093534"></a><a href="Graphic.md#gaccebcfa35f98f9bc6be4bb8cc53eb11c">SetForegroundStyle</a> (const <a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p34273764093534"><a name="p34273764093534"></a><a name="p34273764093534"></a>void&nbsp;</p>
<p id="p943984745093534"><a name="p943984745093534"></a><a name="p943984745093534"></a>Sets the foreground style for this progress bar. </p>
</td>
</tr>
<tr id="row1266603330093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1753242769093534"><a name="p1753242769093534"></a><a name="p1753242769093534"></a><a href="Graphic.md#gae6386ca25603e42f06087f6b2ef65bae">SetForegroundStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1078035688093534"><a name="p1078035688093534"></a><a name="p1078035688093534"></a>void&nbsp;</p>
<p id="p731303314093534"><a name="p731303314093534"></a><a name="p731303314093534"></a>Sets a foreground style for this progress bar. </p>
</td>
</tr>
<tr id="row2131897732093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p264526840093534"><a name="p264526840093534"></a><a name="p264526840093534"></a><a href="Graphic.md#gac77f945f375f333f80bd70254b5c1f96">GetForegroundStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1614812454093534"><a name="p1614812454093534"></a><a name="p1614812454093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p2066825113093534"><a name="p2066825113093534"></a><a name="p2066825113093534"></a>Obtains the foreground style of this progress bar. </p>
</td>
</tr>
<tr id="row673865675093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1572614168093534"><a name="p1572614168093534"></a><a name="p1572614168093534"></a><a href="Graphic.md#ga74cd121dd1794d7e8d905b233bd98217">GetForegroundStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p628481315093534"><a name="p628481315093534"></a><a name="p628481315093534"></a>int64_t&nbsp;</p>
<p id="p1416166685093534"><a name="p1416166685093534"></a><a name="p1416166685093534"></a>Obtains the value of a foreground style of this progress bar. </p>
</td>
</tr>
<tr id="row330778631093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1567287827093534"><a name="p1567287827093534"></a><a name="p1567287827093534"></a><a href="Graphic.md#gabdc0eb4d279212ea7c3ea7a1f9a85e13">SetCapType</a> (<a href="Graphic.md#ga2db3928cdf793f4950245a6841dd43d6">CapType</a> cap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p915333890093534"><a name="p915333890093534"></a><a name="p915333890093534"></a>void&nbsp;</p>
<p id="p763670047093534"><a name="p763670047093534"></a><a name="p763670047093534"></a>Sets the type of caps on the background and foreground of the progress bar. </p>
</td>
</tr>
<tr id="row82750247093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1426898431093534"><a name="p1426898431093534"></a><a name="p1426898431093534"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2000031771093534"><a name="p2000031771093534"></a><a name="p2000031771093534"></a>&nbsp;</p>
<p id="p1116189500093534"><a name="p1116189500093534"></a><a name="p1116189500093534"></a>A default constructor used to create an <strong id="b1755317883093534"><a name="b1755317883093534"></a><a name="b1755317883093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row465935717093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1855080997093534"><a name="p1855080997093534"></a><a name="p1855080997093534"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1158495633093534"><a name="p1158495633093534"></a><a name="p1158495633093534"></a>&nbsp;</p>
<p id="p1027779699093534"><a name="p1027779699093534"></a><a name="p1027779699093534"></a>A constructor used to create an <strong id="b454555739093534"><a name="b454555739093534"></a><a name="b454555739093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1058212615093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1602343699093534"><a name="p1602343699093534"></a><a name="p1602343699093534"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p420747179093534"><a name="p420747179093534"></a><a name="p420747179093534"></a>virtual&nbsp;</p>
<p id="p2128821265093534"><a name="p2128821265093534"></a><a name="p2128821265093534"></a>A destructor used to delete the <strong id="b491049300093534"><a name="b491049300093534"></a><a name="b491049300093534"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row193678180093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1229102571093534"><a name="p1229102571093534"></a><a name="p1229102571093534"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2094010422093534"><a name="p2094010422093534"></a><a name="p2094010422093534"></a>virtual void&nbsp;</p>
<p id="p425392529093534"><a name="p425392529093534"></a><a name="p425392529093534"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1285951260093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1940546682093534"><a name="p1940546682093534"></a><a name="p1940546682093534"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p563373849093534"><a name="p563373849093534"></a><a name="p563373849093534"></a>virtual void&nbsp;</p>
<p id="p1598554857093534"><a name="p1598554857093534"></a><a name="p1598554857093534"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row1877933545093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1260513763093534"><a name="p1260513763093534"></a><a name="p1260513763093534"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p605554750093534"><a name="p605554750093534"></a><a name="p605554750093534"></a>void&nbsp;</p>
<p id="p488286116093534"><a name="p488286116093534"></a><a name="p488286116093534"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row125421748093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p452965845093534"><a name="p452965845093534"></a><a name="p452965845093534"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1041595271093534"><a name="p1041595271093534"></a><a name="p1041595271093534"></a>void&nbsp;</p>
<p id="p1835649771093534"><a name="p1835649771093534"></a><a name="p1835649771093534"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row1212541783093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p474361203093534"><a name="p474361203093534"></a><a name="p474361203093534"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1087088070093534"><a name="p1087088070093534"></a><a name="p1087088070093534"></a>virtual bool&nbsp;</p>
<p id="p2055712658093534"><a name="p2055712658093534"></a><a name="p2055712658093534"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row719041021093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p884201314093534"><a name="p884201314093534"></a><a name="p884201314093534"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1480354401093534"><a name="p1480354401093534"></a><a name="p1480354401093534"></a>virtual bool&nbsp;</p>
<p id="p627249795093534"><a name="p627249795093534"></a><a name="p627249795093534"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row619372608093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1274467918093534"><a name="p1274467918093534"></a><a name="p1274467918093534"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1152875229093534"><a name="p1152875229093534"></a><a name="p1152875229093534"></a>virtual bool&nbsp;</p>
<p id="p1196200595093534"><a name="p1196200595093534"></a><a name="p1196200595093534"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row269366097093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p403668303093534"><a name="p403668303093534"></a><a name="p403668303093534"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p345366609093534"><a name="p345366609093534"></a><a name="p345366609093534"></a>virtual bool&nbsp;</p>
<p id="p941804639093534"><a name="p941804639093534"></a><a name="p941804639093534"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row380866702093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p254743529093534"><a name="p254743529093534"></a><a name="p254743529093534"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2097976263093534"><a name="p2097976263093534"></a><a name="p2097976263093534"></a>virtual void&nbsp;</p>
<p id="p734995991093534"><a name="p734995991093534"></a><a name="p734995991093534"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row1426068787093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p490714410093534"><a name="p490714410093534"></a><a name="p490714410093534"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p591964031093534"><a name="p591964031093534"></a><a name="p591964031093534"></a>virtual void&nbsp;</p>
<p id="p1510356231093534"><a name="p1510356231093534"></a><a name="p1510356231093534"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row1578263653093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p167683952093534"><a name="p167683952093534"></a><a name="p167683952093534"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p359186732093534"><a name="p359186732093534"></a><a name="p359186732093534"></a>virtual void&nbsp;</p>
<p id="p1132179121093534"><a name="p1132179121093534"></a><a name="p1132179121093534"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row1751158205093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2070834802093534"><a name="p2070834802093534"></a><a name="p2070834802093534"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2134948985093534"><a name="p2134948985093534"></a><a name="p2134948985093534"></a>virtual void&nbsp;</p>
<p id="p1483861700093534"><a name="p1483861700093534"></a><a name="p1483861700093534"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row285342682093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p580541088093534"><a name="p580541088093534"></a><a name="p580541088093534"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1581788047093534"><a name="p1581788047093534"></a><a name="p1581788047093534"></a>void&nbsp;</p>
<p id="p248983450093534"><a name="p248983450093534"></a><a name="p248983450093534"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1013735426093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p633650643093534"><a name="p633650643093534"></a><a name="p633650643093534"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p693435177093534"><a name="p693435177093534"></a><a name="p693435177093534"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p263298804093534"><a name="p263298804093534"></a><a name="p263298804093534"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row410239680093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1092003483093534"><a name="p1092003483093534"></a><a name="p1092003483093534"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p728930973093534"><a name="p728930973093534"></a><a name="p728930973093534"></a>void&nbsp;</p>
<p id="p2004195295093534"><a name="p2004195295093534"></a><a name="p2004195295093534"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row324347764093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2122038389093534"><a name="p2122038389093534"></a><a name="p2122038389093534"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p16798930093534"><a name="p16798930093534"></a><a name="p16798930093534"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p1695005672093534"><a name="p1695005672093534"></a><a name="p1695005672093534"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1294552909093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1172211055093534"><a name="p1172211055093534"></a><a name="p1172211055093534"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p675516756093534"><a name="p675516756093534"></a><a name="p675516756093534"></a>void&nbsp;</p>
<p id="p171651145093534"><a name="p171651145093534"></a><a name="p171651145093534"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row864333429093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p83080006093534"><a name="p83080006093534"></a><a name="p83080006093534"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p352566019093534"><a name="p352566019093534"></a><a name="p352566019093534"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p1595061008093534"><a name="p1595061008093534"></a><a name="p1595061008093534"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row1288331555093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1535040972093534"><a name="p1535040972093534"></a><a name="p1535040972093534"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p205327086093534"><a name="p205327086093534"></a><a name="p205327086093534"></a>void&nbsp;</p>
<p id="p850012485093534"><a name="p850012485093534"></a><a name="p850012485093534"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row786758773093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244740088093534"><a name="p1244740088093534"></a><a name="p1244740088093534"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p785305003093534"><a name="p785305003093534"></a><a name="p785305003093534"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p995843666093534"><a name="p995843666093534"></a><a name="p995843666093534"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row979559696093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149148344093534"><a name="p1149148344093534"></a><a name="p1149148344093534"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1029609792093534"><a name="p1029609792093534"></a><a name="p1029609792093534"></a>virtual void&nbsp;</p>
<p id="p1046079761093534"><a name="p1046079761093534"></a><a name="p1046079761093534"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row1414093903093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p762871290093534"><a name="p762871290093534"></a><a name="p762871290093534"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1808297652093534"><a name="p1808297652093534"></a><a name="p1808297652093534"></a>void&nbsp;</p>
<p id="p1290045323093534"><a name="p1290045323093534"></a><a name="p1290045323093534"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row494865625093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p655140255093534"><a name="p655140255093534"></a><a name="p655140255093534"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1224957209093534"><a name="p1224957209093534"></a><a name="p1224957209093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1294227621093534"><a name="p1294227621093534"></a><a name="p1294227621093534"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row102430077093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p374914526093534"><a name="p374914526093534"></a><a name="p374914526093534"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p881680815093534"><a name="p881680815093534"></a><a name="p881680815093534"></a>void&nbsp;</p>
<p id="p952454884093534"><a name="p952454884093534"></a><a name="p952454884093534"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1996934907093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1464645168093534"><a name="p1464645168093534"></a><a name="p1464645168093534"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2039686708093534"><a name="p2039686708093534"></a><a name="p2039686708093534"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p242474476093534"><a name="p242474476093534"></a><a name="p242474476093534"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row561633518093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1342293037093534"><a name="p1342293037093534"></a><a name="p1342293037093534"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1468623775093534"><a name="p1468623775093534"></a><a name="p1468623775093534"></a>virtual void&nbsp;</p>
<p id="p861617702093534"><a name="p861617702093534"></a><a name="p861617702093534"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1145216657093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1547584772093534"><a name="p1547584772093534"></a><a name="p1547584772093534"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1084947515093534"><a name="p1084947515093534"></a><a name="p1084947515093534"></a>bool&nbsp;</p>
<p id="p68197865093534"><a name="p68197865093534"></a><a name="p68197865093534"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row2054497278093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p509192626093534"><a name="p509192626093534"></a><a name="p509192626093534"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1163926459093534"><a name="p1163926459093534"></a><a name="p1163926459093534"></a>void&nbsp;</p>
<p id="p486116279093534"><a name="p486116279093534"></a><a name="p486116279093534"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row579033583093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p694979292093534"><a name="p694979292093534"></a><a name="p694979292093534"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1586706365093534"><a name="p1586706365093534"></a><a name="p1586706365093534"></a>bool&nbsp;</p>
<p id="p1907161208093534"><a name="p1907161208093534"></a><a name="p1907161208093534"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row1882163345093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p143986800093534"><a name="p143986800093534"></a><a name="p143986800093534"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p752095938093534"><a name="p752095938093534"></a><a name="p752095938093534"></a>void&nbsp;</p>
<p id="p1805557982093534"><a name="p1805557982093534"></a><a name="p1805557982093534"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row1944992784093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1232908099093534"><a name="p1232908099093534"></a><a name="p1232908099093534"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1621781831093534"><a name="p1621781831093534"></a><a name="p1621781831093534"></a>bool&nbsp;</p>
<p id="p1539546323093534"><a name="p1539546323093534"></a><a name="p1539546323093534"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row845138138093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p307814243093534"><a name="p307814243093534"></a><a name="p307814243093534"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1599419302093534"><a name="p1599419302093534"></a><a name="p1599419302093534"></a>void&nbsp;</p>
<p id="p512137798093534"><a name="p512137798093534"></a><a name="p512137798093534"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row372287145093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1346547932093534"><a name="p1346547932093534"></a><a name="p1346547932093534"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2003583522093534"><a name="p2003583522093534"></a><a name="p2003583522093534"></a>bool&nbsp;</p>
<p id="p360784405093534"><a name="p360784405093534"></a><a name="p360784405093534"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1963514108093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1692976694093534"><a name="p1692976694093534"></a><a name="p1692976694093534"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1532005878093534"><a name="p1532005878093534"></a><a name="p1532005878093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p813647572093534"><a name="p813647572093534"></a><a name="p813647572093534"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row904416591093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1789790608093534"><a name="p1789790608093534"></a><a name="p1789790608093534"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p816069843093534"><a name="p816069843093534"></a><a name="p816069843093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1530790379093534"><a name="p1530790379093534"></a><a name="p1530790379093534"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1391872750093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1557322588093534"><a name="p1557322588093534"></a><a name="p1557322588093534"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p900702806093534"><a name="p900702806093534"></a><a name="p900702806093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1263694163093534"><a name="p1263694163093534"></a><a name="p1263694163093534"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row698339261093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1282861983093534"><a name="p1282861983093534"></a><a name="p1282861983093534"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1135319157093534"><a name="p1135319157093534"></a><a name="p1135319157093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1789998820093534"><a name="p1789998820093534"></a><a name="p1789998820093534"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row1048595346093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p468008193093534"><a name="p468008193093534"></a><a name="p468008193093534"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p62248092093534"><a name="p62248092093534"></a><a name="p62248092093534"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1682477036093534"><a name="p1682477036093534"></a><a name="p1682477036093534"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row776747427093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1717455457093534"><a name="p1717455457093534"></a><a name="p1717455457093534"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1277585357093534"><a name="p1277585357093534"></a><a name="p1277585357093534"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1323189832093534"><a name="p1323189832093534"></a><a name="p1323189832093534"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1187340863093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p32156700093534"><a name="p32156700093534"></a><a name="p32156700093534"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p372335480093534"><a name="p372335480093534"></a><a name="p372335480093534"></a>void&nbsp;</p>
<p id="p729808206093534"><a name="p729808206093534"></a><a name="p729808206093534"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1791305351093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p988496762093534"><a name="p988496762093534"></a><a name="p988496762093534"></a><a href="Graphic.md#ga3375ec5ef059fd88c657af4552d2fa4f">SetWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p733914340093534"><a name="p733914340093534"></a><a name="p733914340093534"></a>virtual void&nbsp;</p>
<p id="p1047257067093534"><a name="p1047257067093534"></a><a name="p1047257067093534"></a>Sets the width for the view. </p>
</td>
</tr>
<tr id="row775885656093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1122170405093534"><a name="p1122170405093534"></a><a name="p1122170405093534"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1336851507093534"><a name="p1336851507093534"></a><a name="p1336851507093534"></a>virtual int16_t&nbsp;</p>
<p id="p133193009093534"><a name="p133193009093534"></a><a name="p133193009093534"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row1918991205093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p875340301093534"><a name="p875340301093534"></a><a name="p875340301093534"></a><a href="Graphic.md#ga9c7110620d5dc3a7bd3efe1fc2edd125">SetHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1174337745093534"><a name="p1174337745093534"></a><a name="p1174337745093534"></a>virtual void&nbsp;</p>
<p id="p1421669712093534"><a name="p1421669712093534"></a><a name="p1421669712093534"></a>Sets the height for the view. </p>
</td>
</tr>
<tr id="row750339842093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p933330656093534"><a name="p933330656093534"></a><a name="p933330656093534"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1109951454093534"><a name="p1109951454093534"></a><a name="p1109951454093534"></a>virtual int16_t&nbsp;</p>
<p id="p806886057093534"><a name="p806886057093534"></a><a name="p806886057093534"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row2089569130093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2046322863093534"><a name="p2046322863093534"></a><a name="p2046322863093534"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p282815475093534"><a name="p282815475093534"></a><a name="p282815475093534"></a>virtual void&nbsp;</p>
<p id="p827355836093534"><a name="p827355836093534"></a><a name="p827355836093534"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row2100057768093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1385587371093534"><a name="p1385587371093534"></a><a name="p1385587371093534"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p510455020093534"><a name="p510455020093534"></a><a name="p510455020093534"></a>virtual void&nbsp;</p>
<p id="p1440924232093534"><a name="p1440924232093534"></a><a name="p1440924232093534"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1288692077093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p680359600093534"><a name="p680359600093534"></a><a name="p680359600093534"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p873854188093534"><a name="p873854188093534"></a><a name="p873854188093534"></a>int16_t&nbsp;</p>
<p id="p1207239771093534"><a name="p1207239771093534"></a><a name="p1207239771093534"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row302935542093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p95527943093534"><a name="p95527943093534"></a><a name="p95527943093534"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1215661484093534"><a name="p1215661484093534"></a><a name="p1215661484093534"></a>virtual void&nbsp;</p>
<p id="p785898556093534"><a name="p785898556093534"></a><a name="p785898556093534"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row941305754093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p547329799093534"><a name="p547329799093534"></a><a name="p547329799093534"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1472790566093534"><a name="p1472790566093534"></a><a name="p1472790566093534"></a>int16_t&nbsp;</p>
<p id="p1085722196093534"><a name="p1085722196093534"></a><a name="p1085722196093534"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row1259785587093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2104200448093534"><a name="p2104200448093534"></a><a name="p2104200448093534"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1563426963093534"><a name="p1563426963093534"></a><a name="p1563426963093534"></a>virtual void&nbsp;</p>
<p id="p1373856390093534"><a name="p1373856390093534"></a><a name="p1373856390093534"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row705417718093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1433926581093534"><a name="p1433926581093534"></a><a name="p1433926581093534"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p405160650093534"><a name="p405160650093534"></a><a name="p405160650093534"></a>virtual void&nbsp;</p>
<p id="p205829710093534"><a name="p205829710093534"></a><a name="p205829710093534"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1448904819093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p168831470093534"><a name="p168831470093534"></a><a name="p168831470093534"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1428171771093534"><a name="p1428171771093534"></a><a name="p1428171771093534"></a>bool&nbsp;</p>
<p id="p1745069181093534"><a name="p1745069181093534"></a><a name="p1745069181093534"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row70713977093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1790205553093534"><a name="p1790205553093534"></a><a name="p1790205553093534"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p428517659093534"><a name="p428517659093534"></a><a name="p428517659093534"></a>void&nbsp;</p>
<p id="p1522445465093534"><a name="p1522445465093534"></a><a name="p1522445465093534"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row1062630988093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p86362282093534"><a name="p86362282093534"></a><a name="p86362282093534"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p398289922093534"><a name="p398289922093534"></a><a name="p398289922093534"></a>void&nbsp;</p>
<p id="p531191415093534"><a name="p531191415093534"></a><a name="p531191415093534"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1577630134093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p356495853093534"><a name="p356495853093534"></a><a name="p356495853093534"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1907718286093534"><a name="p1907718286093534"></a><a name="p1907718286093534"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p1411485556093534"><a name="p1411485556093534"></a><a name="p1411485556093534"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1431260014093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p132291698093534"><a name="p132291698093534"></a><a name="p132291698093534"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p658631228093534"><a name="p658631228093534"></a><a name="p658631228093534"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p511235065093534"><a name="p511235065093534"></a><a name="p511235065093534"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row2058847495093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p467444721093534"><a name="p467444721093534"></a><a name="p467444721093534"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1652126780093534"><a name="p1652126780093534"></a><a name="p1652126780093534"></a>void&nbsp;</p>
<p id="p806028027093534"><a name="p806028027093534"></a><a name="p806028027093534"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row257044282093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p712061130093534"><a name="p712061130093534"></a><a name="p712061130093534"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073834269093534"><a name="p2073834269093534"></a><a name="p2073834269093534"></a>const char *&nbsp;</p>
<p id="p2092682611093534"><a name="p2092682611093534"></a><a name="p2092682611093534"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row1787372047093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1360709672093534"><a name="p1360709672093534"></a><a name="p1360709672093534"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p522184327093534"><a name="p522184327093534"></a><a name="p522184327093534"></a>void&nbsp;</p>
<p id="p1487717634093534"><a name="p1487717634093534"></a><a name="p1487717634093534"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row1244553754093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p31673578093534"><a name="p31673578093534"></a><a name="p31673578093534"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1400643642093534"><a name="p1400643642093534"></a><a name="p1400643642093534"></a>int16_t&nbsp;</p>
<p id="p1629724507093534"><a name="p1629724507093534"></a><a name="p1629724507093534"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row44667065093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719664302093534"><a name="p719664302093534"></a><a name="p719664302093534"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1353615642093534"><a name="p1353615642093534"></a><a name="p1353615642093534"></a>virtual void&nbsp;</p>
<p id="p1130178815093534"><a name="p1130178815093534"></a><a name="p1130178815093534"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1599204456093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p105852062093534"><a name="p105852062093534"></a><a name="p105852062093534"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p39209540093534"><a name="p39209540093534"></a><a name="p39209540093534"></a>void&nbsp;</p>
<p id="p2047170842093534"><a name="p2047170842093534"></a><a name="p2047170842093534"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row923617820093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1647325946093534"><a name="p1647325946093534"></a><a name="p1647325946093534"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1861959631093534"><a name="p1861959631093534"></a><a name="p1861959631093534"></a>void&nbsp;</p>
<p id="p518944513093534"><a name="p518944513093534"></a><a name="p518944513093534"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row1739331463093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1133683195093534"><a name="p1133683195093534"></a><a name="p1133683195093534"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p78252268093534"><a name="p78252268093534"></a><a name="p78252268093534"></a>void&nbsp;</p>
<p id="p1761042069093534"><a name="p1761042069093534"></a><a name="p1761042069093534"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row835006846093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2099945695093534"><a name="p2099945695093534"></a><a name="p2099945695093534"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1703590352093534"><a name="p1703590352093534"></a><a name="p1703590352093534"></a>void&nbsp;</p>
<p id="p1979442017093534"><a name="p1979442017093534"></a><a name="p1979442017093534"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row796863483093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p384303911093534"><a name="p384303911093534"></a><a name="p384303911093534"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1744596648093534"><a name="p1744596648093534"></a><a name="p1744596648093534"></a>void&nbsp;</p>
<p id="p1945728252093534"><a name="p1945728252093534"></a><a name="p1945728252093534"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1942552774093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1119420922093534"><a name="p1119420922093534"></a><a name="p1119420922093534"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p654127800093534"><a name="p654127800093534"></a><a name="p654127800093534"></a>void&nbsp;</p>
<p id="p1240372658093534"><a name="p1240372658093534"></a><a name="p1240372658093534"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row523519630093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p438585705093534"><a name="p438585705093534"></a><a name="p438585705093534"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p176067338093534"><a name="p176067338093534"></a><a name="p176067338093534"></a>void&nbsp;</p>
<p id="p1479899211093534"><a name="p1479899211093534"></a><a name="p1479899211093534"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row267952385093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1113199082093534"><a name="p1113199082093534"></a><a name="p1113199082093534"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1538607706093534"><a name="p1538607706093534"></a><a name="p1538607706093534"></a>void&nbsp;</p>
<p id="p2049462162093534"><a name="p2049462162093534"></a><a name="p2049462162093534"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1874921767093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1839055490093534"><a name="p1839055490093534"></a><a name="p1839055490093534"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p182318550093534"><a name="p182318550093534"></a><a name="p182318550093534"></a>void&nbsp;</p>
<p id="p2092708386093534"><a name="p2092708386093534"></a><a name="p2092708386093534"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1569984834093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p929031094093534"><a name="p929031094093534"></a><a name="p929031094093534"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1926857272093534"><a name="p1926857272093534"></a><a name="p1926857272093534"></a>void&nbsp;</p>
<p id="p188534519093534"><a name="p188534519093534"></a><a name="p188534519093534"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1028770105093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p711924905093534"><a name="p711924905093534"></a><a name="p711924905093534"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p701408263093534"><a name="p701408263093534"></a><a name="p701408263093534"></a>void&nbsp;</p>
<p id="p1788071877093534"><a name="p1788071877093534"></a><a name="p1788071877093534"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row1605366248093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2144951341093534"><a name="p2144951341093534"></a><a name="p2144951341093534"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115060356093534"><a name="p115060356093534"></a><a name="p115060356093534"></a>void&nbsp;</p>
<p id="p463780781093534"><a name="p463780781093534"></a><a name="p463780781093534"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row781140286093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p704497538093534"><a name="p704497538093534"></a><a name="p704497538093534"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p820662903093534"><a name="p820662903093534"></a><a name="p820662903093534"></a>void&nbsp;</p>
<p id="p1197812116093534"><a name="p1197812116093534"></a><a name="p1197812116093534"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row7165945093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1763716898093534"><a name="p1763716898093534"></a><a name="p1763716898093534"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p560151507093534"><a name="p560151507093534"></a><a name="p560151507093534"></a>void&nbsp;</p>
<p id="p240084365093534"><a name="p240084365093534"></a><a name="p240084365093534"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row2007358743093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1493610011093534"><a name="p1493610011093534"></a><a name="p1493610011093534"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1196130169093534"><a name="p1196130169093534"></a><a name="p1196130169093534"></a>void&nbsp;</p>
<p id="p2013736694093534"><a name="p2013736694093534"></a><a name="p2013736694093534"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row1475542094093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p658802669093534"><a name="p658802669093534"></a><a name="p658802669093534"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p833610505093534"><a name="p833610505093534"></a><a name="p833610505093534"></a>virtual void&nbsp;</p>
<p id="p1695753645093534"><a name="p1695753645093534"></a><a name="p1695753645093534"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row835586604093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p206999234093534"><a name="p206999234093534"></a><a name="p206999234093534"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1206733971093534"><a name="p1206733971093534"></a><a name="p1206733971093534"></a>virtual void&nbsp;</p>
<p id="p1137421267093534"><a name="p1137421267093534"></a><a name="p1137421267093534"></a>Sets a style. </p>
</td>
</tr>
<tr id="row51823409093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p174671750093534"><a name="p174671750093534"></a><a name="p174671750093534"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p387156437093534"><a name="p387156437093534"></a><a name="p387156437093534"></a>virtual int64_t&nbsp;</p>
<p id="p1718292588093534"><a name="p1718292588093534"></a><a name="p1718292588093534"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1134050890093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1149087447093534"><a name="p1149087447093534"></a><a name="p1149087447093534"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p786608765093534"><a name="p786608765093534"></a><a name="p786608765093534"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p37742613093534"><a name="p37742613093534"></a><a name="p37742613093534"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row996952050093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2035724424093534"><a name="p2035724424093534"></a><a name="p2035724424093534"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p703889488093534"><a name="p703889488093534"></a><a name="p703889488093534"></a>void *&nbsp;</p>
<p id="p2100599842093534"><a name="p2100599842093534"></a><a name="p2100599842093534"></a>Overrides the <strong id="b69060379093534"><a name="b69060379093534"></a><a name="b69060379093534"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1219040686093534"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1252017911093534"><a name="p1252017911093534"></a><a name="p1252017911093534"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1930531519093534"><a name="p1930531519093534"></a><a name="p1930531519093534"></a>void&nbsp;</p>
<p id="p1689556127093534"><a name="p1689556127093534"></a><a name="p1689556127093534"></a>Overrides the <strong id="b768288126093534"><a name="b768288126093534"></a><a name="b768288126093534"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

