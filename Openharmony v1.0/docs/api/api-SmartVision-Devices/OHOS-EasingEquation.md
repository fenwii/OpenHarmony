# OHOS::EasingEquation<a name="ZH-CN_TOPIC_0000001055039534"></a>

## **Overview**<a name="section97557664093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines functions for specifying the velocity of an animation. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section885458724093533"></a>

## Static Public Member Functions<a name="pub-static-methods"></a>

<a name="table1105853379093533"></a>
<table><thead align="left"><tr id="row991524357093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2008444026093533"><a name="p2008444026093533"></a><a name="p2008444026093533"></a>Static Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2011007768093533"><a name="p2011007768093533"></a><a name="p2011007768093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row204898760093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1129395481093533"><a name="p1129395481093533"></a><a name="p1129395481093533"></a><a href="Graphic.md#gab7cf0e64a0d363d8b448262d719ac97a">SetBackOvershoot</a> (double overshoot)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p444352841093533"><a name="p444352841093533"></a><a name="p444352841093533"></a>static void&nbsp;</p>
<p id="p620162213093533"><a name="p620162213093533"></a><a name="p620162213093533"></a>Sets the parameter <strong id="b1175140337093533"><a name="b1175140337093533"></a><a name="b1175140337093533"></a>s</strong> in the equation <strong id="b2133126385093533"><a name="b2133126385093533"></a><a name="b2133126385093533"></a>(s+1)*t^3 - s*t^2</strong> for a back easing. </p>
</td>
</tr>
<tr id="row1902060137093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p907441044093533"><a name="p907441044093533"></a><a name="p907441044093533"></a><a href="Graphic.md#ga4598524b16a33de497fa9321d887d3b1">BackEaseIn</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1743250192093533"><a name="p1743250192093533"></a><a name="p1743250192093533"></a>static int16_t&nbsp;</p>
<p id="p2008280688093533"><a name="p2008280688093533"></a><a name="p2008280688093533"></a>Eases in with an overshoot. </p>
</td>
</tr>
<tr id="row504697082093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p549717496093533"><a name="p549717496093533"></a><a name="p549717496093533"></a><a href="Graphic.md#ga7399f01f7abc33413bf25aa17a99c2f2">BackEaseOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p741740474093533"><a name="p741740474093533"></a><a name="p741740474093533"></a>static int16_t&nbsp;</p>
<p id="p833695393093533"><a name="p833695393093533"></a><a name="p833695393093533"></a>Eases out with an overshoot. </p>
</td>
</tr>
<tr id="row942741922093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p534371203093533"><a name="p534371203093533"></a><a name="p534371203093533"></a><a href="Graphic.md#gac7c2a9a1dfce384438a3bd9d6c0c2525">BackEaseInOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1112901168093533"><a name="p1112901168093533"></a><a name="p1112901168093533"></a>static int16_t&nbsp;</p>
<p id="p1799190930093533"><a name="p1799190930093533"></a><a name="p1799190930093533"></a>Eases in and then out with an overshoot. </p>
</td>
</tr>
<tr id="row774523206093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p467081677093533"><a name="p467081677093533"></a><a name="p467081677093533"></a><a href="Graphic.md#ga446c958f14b3d6de24e2c1bab171bba2">CircEaseIn</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p496789381093533"><a name="p496789381093533"></a><a name="p496789381093533"></a>static int16_t&nbsp;</p>
<p id="p1874975606093533"><a name="p1874975606093533"></a><a name="p1874975606093533"></a>Eases in shaping like a circular curve. </p>
</td>
</tr>
<tr id="row1021254518093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1982570402093533"><a name="p1982570402093533"></a><a name="p1982570402093533"></a><a href="Graphic.md#gaab8fad8664d648df7e5e224b68ee54ad">CircEaseOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2046459365093533"><a name="p2046459365093533"></a><a name="p2046459365093533"></a>static int16_t&nbsp;</p>
<p id="p2048142985093533"><a name="p2048142985093533"></a><a name="p2048142985093533"></a>Eases out shaping like a circular curve. </p>
</td>
</tr>
<tr id="row1727523982093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1755638171093533"><a name="p1755638171093533"></a><a name="p1755638171093533"></a><a href="Graphic.md#ga68c392dad14e1bef192b085aeec6ca9b">CircEaseInOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448185095093533"><a name="p448185095093533"></a><a name="p448185095093533"></a>static int16_t&nbsp;</p>
<p id="p171176698093533"><a name="p171176698093533"></a><a name="p171176698093533"></a>Eases in and then out shaping like a circular curve. </p>
</td>
</tr>
<tr id="row1871257105093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1784747575093533"><a name="p1784747575093533"></a><a name="p1784747575093533"></a><a href="Graphic.md#ga5c91a83cc424fb7e4e1f40cae6b3be66">CubicEaseIn</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1204757406093533"><a name="p1204757406093533"></a><a name="p1204757406093533"></a>static int16_t&nbsp;</p>
<p id="p609416028093533"><a name="p609416028093533"></a><a name="p609416028093533"></a>Eases in shaping like a cubic curve. </p>
</td>
</tr>
<tr id="row1386508581093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1981189917093533"><a name="p1981189917093533"></a><a name="p1981189917093533"></a><a href="Graphic.md#ga529a948d9f6711a5f2726af5f10d7a48">CubicEaseOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1646317608093533"><a name="p1646317608093533"></a><a name="p1646317608093533"></a>static int16_t&nbsp;</p>
<p id="p1683034723093533"><a name="p1683034723093533"></a><a name="p1683034723093533"></a>Eases out shaping like a cubic curve. </p>
</td>
</tr>
<tr id="row435766193093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p530102783093533"><a name="p530102783093533"></a><a name="p530102783093533"></a><a href="Graphic.md#gad99ea4ed828f274f111f492eea123cb4">CubicEaseInOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1991775330093533"><a name="p1991775330093533"></a><a name="p1991775330093533"></a>static int16_t&nbsp;</p>
<p id="p2069513610093533"><a name="p2069513610093533"></a><a name="p2069513610093533"></a>Eases in and then out shaping like a cubic curve. </p>
</td>
</tr>
<tr id="row645313754093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p829946937093533"><a name="p829946937093533"></a><a name="p829946937093533"></a><a href="Graphic.md#ga8af9a1f527ffaa5006cf0ee867f7d7d0">LinearEaseNone</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p582746442093533"><a name="p582746442093533"></a><a name="p582746442093533"></a>static int16_t&nbsp;</p>
<p id="p1952031933093533"><a name="p1952031933093533"></a><a name="p1952031933093533"></a>Displays no linear easing effects. </p>
</td>
</tr>
<tr id="row989246393093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p570709307093533"><a name="p570709307093533"></a><a name="p570709307093533"></a><a href="Graphic.md#ga72a9b93086c8466767942863a7d5cb78">QuadEaseIn</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p298303116093533"><a name="p298303116093533"></a><a name="p298303116093533"></a>static int16_t&nbsp;</p>
<p id="p558262387093533"><a name="p558262387093533"></a><a name="p558262387093533"></a>Eases in shaping like a quadratic curve. </p>
</td>
</tr>
<tr id="row1032865340093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p412189524093533"><a name="p412189524093533"></a><a name="p412189524093533"></a><a href="Graphic.md#ga0c9cd2781e17f7077b4c9d5847eb90c8">QuadEaseOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1452577025093533"><a name="p1452577025093533"></a><a name="p1452577025093533"></a>static int16_t&nbsp;</p>
<p id="p1892708567093533"><a name="p1892708567093533"></a><a name="p1892708567093533"></a>Eases out shaping like a quadratic curve. </p>
</td>
</tr>
<tr id="row847933444093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1930100882093533"><a name="p1930100882093533"></a><a name="p1930100882093533"></a><a href="Graphic.md#ga8f62ddc3f1b2b33904845601108d6f64">QuadEaseInOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p420090946093533"><a name="p420090946093533"></a><a name="p420090946093533"></a>static int16_t&nbsp;</p>
<p id="p435408388093533"><a name="p435408388093533"></a><a name="p435408388093533"></a>Eases in and then out shaping like a quadratic curve. </p>
</td>
</tr>
<tr id="row1461737789093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1494433378093533"><a name="p1494433378093533"></a><a name="p1494433378093533"></a><a href="Graphic.md#ga9ddf5221cdde5f6a37096300847a50ac">QuintEaseIn</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1152170870093533"><a name="p1152170870093533"></a><a name="p1152170870093533"></a>static int16_t&nbsp;</p>
<p id="p713319109093533"><a name="p713319109093533"></a><a name="p713319109093533"></a>Eases in shaping like a quintic curve. </p>
</td>
</tr>
<tr id="row1776786608093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p238399955093533"><a name="p238399955093533"></a><a name="p238399955093533"></a><a href="Graphic.md#gaa61e26b2bff3f69edced36d0c0d17a45">QuintEaseOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1829590545093533"><a name="p1829590545093533"></a><a name="p1829590545093533"></a>static int16_t&nbsp;</p>
<p id="p601659680093533"><a name="p601659680093533"></a><a name="p601659680093533"></a>Eases out shaping like a quintic curve. </p>
</td>
</tr>
<tr id="row1189723147093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p980334108093533"><a name="p980334108093533"></a><a name="p980334108093533"></a><a href="Graphic.md#ga8bea02f98d26a97072f32369370a421b">QuintEaseInOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p927303082093533"><a name="p927303082093533"></a><a name="p927303082093533"></a>static int16_t&nbsp;</p>
<p id="p1794618440093533"><a name="p1794618440093533"></a><a name="p1794618440093533"></a>Eases in and then out shaping like a quintic curve. </p>
</td>
</tr>
<tr id="row2034493118093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p485100019093533"><a name="p485100019093533"></a><a name="p485100019093533"></a><a href="Graphic.md#ga89ee91a569b73c6ebb29ae4dfd2777f9">SineEaseIn</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p395411423093533"><a name="p395411423093533"></a><a name="p395411423093533"></a>static int16_t&nbsp;</p>
<p id="p1737802756093533"><a name="p1737802756093533"></a><a name="p1737802756093533"></a>Eases in shaping like a sinusoidal curve. </p>
</td>
</tr>
<tr id="row607443015093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1030121554093533"><a name="p1030121554093533"></a><a name="p1030121554093533"></a><a href="Graphic.md#ga34018757e69d7920557030f33393048d">SineEaseOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764805566093533"><a name="p764805566093533"></a><a name="p764805566093533"></a>static int16_t&nbsp;</p>
<p id="p806772214093533"><a name="p806772214093533"></a><a name="p806772214093533"></a>Eases out shaping like a sinusoidal curve. </p>
</td>
</tr>
<tr id="row849106029093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1936727108093533"><a name="p1936727108093533"></a><a name="p1936727108093533"></a><a href="Graphic.md#ga2c3b14232a67095b0b941bae3a7b2e54">SineEaseInOut</a> (int16_t startPos, int16_t endPos, uint16_t curTime, uint16_t durationTime)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1575999461093533"><a name="p1575999461093533"></a><a name="p1575999461093533"></a>static int16_t&nbsp;</p>
<p id="p2129678497093533"><a name="p2129678497093533"></a><a name="p2129678497093533"></a>Eases in and then out shaping like a sinusoidal curve. </p>
</td>
</tr>
</tbody>
</table>

## Additional Inherited Members<a name="inherited"></a>

<a name="table1772559697093533"></a>
<table><thead align="left"><tr id="row1276867051093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1062985684093533"><a name="p1062985684093533"></a><a name="p1062985684093533"></a>Additional Inherited Member Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1899048598093533"><a name="p1899048598093533"></a><a name="p1899048598093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row446105983093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1563445849093533"><a name="p1563445849093533"></a><a name="p1563445849093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052944979093533"><a name="p1052944979093533"></a><a name="p1052944979093533"></a>Overrides the <strong id="b815453812093533"><a name="b815453812093533"></a><a name="b815453812093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row1749025114093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p670367464093533"><a name="p670367464093533"></a><a name="p670367464093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1837644458093533"><a name="p1837644458093533"></a><a name="p1837644458093533"></a>Overrides the <strong id="b322127151093533"><a name="b322127151093533"></a><a name="b322127151093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

