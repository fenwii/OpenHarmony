# OHOS::UIBoxProgress<a name="ZH-CN_TOPIC_0000001055198152"></a>

## **Overview**<a name="section1516015302093533"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Represents a linear progress bar. 

This class is used to set the range and current value to display the linear progress bar which can be in multiple directions.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section1068298935093533"></a>

## Public Types<a name="pub-types"></a>

<a name="table1446473958093533"></a>
<table><thead align="left"><tr id="row2029706745093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1543017273093533"><a name="p1543017273093533"></a><a name="p1543017273093533"></a>Public Type Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p189397218093533"><a name="p189397218093533"></a><a name="p189397218093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1649723241093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p211585688093533"><a name="p211585688093533"></a><a name="p211585688093533"></a><a href="Graphic.md#ga4a7a2c192206c8b18379f42a5fd176eb">Direction</a> : uint8_t { <a href="Graphic.md#gga4a7a2c192206c8b18379f42a5fd176eba43cb7d46f0e18f315d43b82024093b51">Direction::DIR_LEFT_TO_RIGHT</a>, <a href="Graphic.md#gga4a7a2c192206c8b18379f42a5fd176eba49e31df5a7fc02ee8c2f85b5e15f0145">Direction::DIR_RIGHT_TO_LEFT</a>, <a href="Graphic.md#gga4a7a2c192206c8b18379f42a5fd176eba68baeaa89ae4576fc3d9ac732f87a116">Direction::DIR_TOP_TO_BOTTOM</a>, <a href="Graphic.md#gga4a7a2c192206c8b18379f42a5fd176eba78b28982b481790c740bc9b2c1292baa">Direction::DIR_BOTTOM_TO_TOP</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1549714102093533"><a name="p1549714102093533"></a><a name="p1549714102093533"></a>Enumerates the directions of the progress bar. </p>
</td>
</tr>
</tbody>
</table>

## Public Member Functions<a name="pub-methods"></a>

<a name="table715752614093533"></a>
<table><thead align="left"><tr id="row1400520558093533"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1267617236093533"><a name="p1267617236093533"></a><a name="p1267617236093533"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1825154659093533"><a name="p1825154659093533"></a><a name="p1825154659093533"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1240331488093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p943729787093533"><a name="p943729787093533"></a><a name="p943729787093533"></a><a href="Graphic.md#ga315a532a3e0aa658a64d2f7739483f35">UIBoxProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1337952296093533"><a name="p1337952296093533"></a><a name="p1337952296093533"></a>&nbsp;</p>
<p id="p201840937093533"><a name="p201840937093533"></a><a name="p201840937093533"></a>A constructor used to create a <strong id="b514100523093533"><a name="b514100523093533"></a><a name="b514100523093533"></a><a href="OHOS-UIBoxProgress.md">UIBoxProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row1879294856093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p550152018093533"><a name="p550152018093533"></a><a name="p550152018093533"></a><a href="Graphic.md#ga7a5eefc7d4ad253a286444e76146af7f">~UIBoxProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1515621861093533"><a name="p1515621861093533"></a><a name="p1515621861093533"></a>virtual&nbsp;</p>
<p id="p1015833166093533"><a name="p1015833166093533"></a><a name="p1015833166093533"></a>A destructor used to delete the <strong id="b1603317095093533"><a name="b1603317095093533"></a><a name="b1603317095093533"></a><a href="OHOS-UIBoxProgress.md">UIBoxProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row1203325218093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p344156855093533"><a name="p344156855093533"></a><a name="p344156855093533"></a><a href="Graphic.md#gaa2d380d48776748583f51297715af0b5">GetViewType</a> () const override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1446315020093533"><a name="p1446315020093533"></a><a name="p1446315020093533"></a>UIViewType&nbsp;</p>
<p id="p782167169093533"><a name="p782167169093533"></a><a name="p782167169093533"></a>Obtains the view type. </p>
</td>
</tr>
<tr id="row1623154348093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p445067396093533"><a name="p445067396093533"></a><a name="p445067396093533"></a><a href="Graphic.md#ga4b3eeb9de2443182480a71cadb23178c">SetWidth</a> (int16_t width) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p957943384093533"><a name="p957943384093533"></a><a name="p957943384093533"></a>void&nbsp;</p>
<p id="p1272361466093533"><a name="p1272361466093533"></a><a name="p1272361466093533"></a>Sets the width for the view holding this progress bar. </p>
</td>
</tr>
<tr id="row899597048093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p477237044093533"><a name="p477237044093533"></a><a name="p477237044093533"></a><a href="Graphic.md#ga54299cb7561cee9a03d0fc9d0ddda784">SetHeight</a> (int16_t height) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1942376286093533"><a name="p1942376286093533"></a><a name="p1942376286093533"></a>void&nbsp;</p>
<p id="p817357017093533"><a name="p817357017093533"></a><a name="p817357017093533"></a>Sets the height for this view. </p>
</td>
</tr>
<tr id="row411552456093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p659140218093533"><a name="p659140218093533"></a><a name="p659140218093533"></a><a href="Graphic.md#ga3e2e7d0c37b4945a3f4f456c20cb0177">SetDirection</a> (const <a href="Graphic.md#ga4a7a2c192206c8b18379f42a5fd176eb">Direction</a> &amp;direction)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p772633546093533"><a name="p772633546093533"></a><a name="p772633546093533"></a>void&nbsp;</p>
<p id="p1632971633093533"><a name="p1632971633093533"></a><a name="p1632971633093533"></a>Sets the direction for this progress bar. </p>
</td>
</tr>
<tr id="row254951076093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p847675541093533"><a name="p847675541093533"></a><a name="p847675541093533"></a><a href="Graphic.md#ga493699e8d0e934d7fb3d5502529a1c5e">GetDirection</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1168518356093533"><a name="p1168518356093533"></a><a name="p1168518356093533"></a><a href="Graphic.md#ga4a7a2c192206c8b18379f42a5fd176eb">Direction</a>&nbsp;</p>
<p id="p950363214093533"><a name="p950363214093533"></a><a name="p950363214093533"></a>Obtains the direction of this progress bar. </p>
</td>
</tr>
<tr id="row363302215093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1139514035093533"><a name="p1139514035093533"></a><a name="p1139514035093533"></a><a href="Graphic.md#gada3cf1819e826ee0aed4a40ef00b91a6">SetValidWidth</a> (int16_t width)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p481261965093533"><a name="p481261965093533"></a><a name="p481261965093533"></a>void&nbsp;</p>
<p id="p1921405195093533"><a name="p1921405195093533"></a><a name="p1921405195093533"></a>Sets the actual width for this progress bar. </p>
</td>
</tr>
<tr id="row1560522200093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1464264486093533"><a name="p1464264486093533"></a><a name="p1464264486093533"></a><a href="Graphic.md#ga6577d38d85234e08f709dd0ae131b255">GetValidWidth</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1519709215093533"><a name="p1519709215093533"></a><a name="p1519709215093533"></a>int16_t&nbsp;</p>
<p id="p2026606020093533"><a name="p2026606020093533"></a><a name="p2026606020093533"></a>Obtains the actual width of this progress bar. </p>
</td>
</tr>
<tr id="row1805993917093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p386924592093533"><a name="p386924592093533"></a><a name="p386924592093533"></a><a href="Graphic.md#ga6958b8273ad7a5563dfa19267cc3a13c">SetValidHeight</a> (int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1283803852093533"><a name="p1283803852093533"></a><a name="p1283803852093533"></a>void&nbsp;</p>
<p id="p707689545093533"><a name="p707689545093533"></a><a name="p707689545093533"></a>Sets the actual height for this progress bar. </p>
</td>
</tr>
<tr id="row1148086790093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1934775678093533"><a name="p1934775678093533"></a><a name="p1934775678093533"></a><a href="Graphic.md#ga1e6c92b20c4931a058c0b7775bf180c9">GetValidHeight</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p306874892093533"><a name="p306874892093533"></a><a name="p306874892093533"></a>int16_t&nbsp;</p>
<p id="p382694734093533"><a name="p382694734093533"></a><a name="p382694734093533"></a>Obtains the actual height of this progress bar. </p>
</td>
</tr>
<tr id="row1430235278093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p309135813093533"><a name="p309135813093533"></a><a name="p309135813093533"></a><a href="Graphic.md#ga3321d9b9b156423bdc0abcb8e99efb0d">OnDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea) override</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1059003051093533"><a name="p1059003051093533"></a><a name="p1059003051093533"></a>void&nbsp;</p>
<p id="p279305495093533"><a name="p279305495093533"></a><a name="p279305495093533"></a>Called when a view is drawn. </p>
</td>
</tr>
<tr id="row1413404659093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p346612110093533"><a name="p346612110093533"></a><a name="p346612110093533"></a><a href="Graphic.md#ga8f9bfb4f42ee0e094501ff776e3336da">UIAbstractProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1308177564093533"><a name="p1308177564093533"></a><a name="p1308177564093533"></a>&nbsp;</p>
<p id="p1878562580093533"><a name="p1878562580093533"></a><a name="p1878562580093533"></a>A constructor used to create a <strong id="b1253570488093533"><a name="b1253570488093533"></a><a name="b1253570488093533"></a><a href="OHOS-UIAbstractProgress.md">UIAbstractProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row143652668093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2017902830093533"><a name="p2017902830093533"></a><a name="p2017902830093533"></a><a href="Graphic.md#ga5c1cf7239bf0c0f7d331e63df805b518">~UIAbstractProgress</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1422798766093533"><a name="p1422798766093533"></a><a name="p1422798766093533"></a>virtual&nbsp;</p>
<p id="p1463468870093533"><a name="p1463468870093533"></a><a name="p1463468870093533"></a>A destructor used to delete the <strong id="b343199881093533"><a name="b343199881093533"></a><a name="b343199881093533"></a><a href="OHOS-UIAbstractProgress.md">UIAbstractProgress</a></strong> instance. </p>
</td>
</tr>
<tr id="row889586406093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p974358222093533"><a name="p974358222093533"></a><a name="p974358222093533"></a><a href="Graphic.md#gacb680c1ddc9135371676df504dc6c8f2">EnableBackground</a> (bool enable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p453948608093533"><a name="p453948608093533"></a><a name="p453948608093533"></a>void&nbsp;</p>
<p id="p565336670093533"><a name="p565336670093533"></a><a name="p565336670093533"></a>Sets whether the background of the progress bar is visible. </p>
</td>
</tr>
<tr id="row1878571408093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1502950183093533"><a name="p1502950183093533"></a><a name="p1502950183093533"></a><a href="Graphic.md#ga5f65014431a6489ffa1d4949f9c4449b">SetValue</a> (int16_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p265767347093533"><a name="p265767347093533"></a><a name="p265767347093533"></a>void&nbsp;</p>
<p id="p750588168093533"><a name="p750588168093533"></a><a name="p750588168093533"></a>Sets the current value for this progress bar. </p>
</td>
</tr>
<tr id="row1435028198093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p617504548093533"><a name="p617504548093533"></a><a name="p617504548093533"></a><a href="Graphic.md#ga6face76aa7972efeb6cbb8f525f23135">GetValue</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p275325554093533"><a name="p275325554093533"></a><a name="p275325554093533"></a>int16_t&nbsp;</p>
<p id="p1659979478093533"><a name="p1659979478093533"></a><a name="p1659979478093533"></a>Obtains the current value of this progress bar. </p>
</td>
</tr>
<tr id="row1395203924093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1364567366093533"><a name="p1364567366093533"></a><a name="p1364567366093533"></a><a href="Graphic.md#ga089e3875453011499ad33ed89a44a699">SetRange</a> (int16_t rangeMax, int16_t rangeMin)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p562714134093533"><a name="p562714134093533"></a><a name="p562714134093533"></a>void&nbsp;</p>
<p id="p634248026093533"><a name="p634248026093533"></a><a name="p634248026093533"></a>Sets the range for this progress bar. </p>
</td>
</tr>
<tr id="row1334642925093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p339212234093533"><a name="p339212234093533"></a><a name="p339212234093533"></a><a href="Graphic.md#ga68ab733afcf4224a799ccad2092d1d23">GetRangeMin</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p582383897093533"><a name="p582383897093533"></a><a name="p582383897093533"></a>int16_t&nbsp;</p>
<p id="p1744266586093533"><a name="p1744266586093533"></a><a name="p1744266586093533"></a>Obtains the minimum value of this progress bar. </p>
</td>
</tr>
<tr id="row1661101237093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p138497242093533"><a name="p138497242093533"></a><a name="p138497242093533"></a><a href="Graphic.md#ga1840199f22d5d3e4ef58e41ac8f4febc">GetRangeMax</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1857414429093533"><a name="p1857414429093533"></a><a name="p1857414429093533"></a>int16_t&nbsp;</p>
<p id="p1014993117093533"><a name="p1014993117093533"></a><a name="p1014993117093533"></a>Obtains the maximum value of this progress bar. </p>
</td>
</tr>
<tr id="row291591949093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1408179931093533"><a name="p1408179931093533"></a><a name="p1408179931093533"></a><a href="Graphic.md#ga5b3ec363e391f601e12bf937b9cf77db">SetImage</a> (const char *foregroundImage, const char *backgroundImage=nullptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p835175884093533"><a name="p835175884093533"></a><a name="p835175884093533"></a>void&nbsp;</p>
<p id="p1524513503093533"><a name="p1524513503093533"></a><a name="p1524513503093533"></a>Sets the image for this progress bar. </p>
</td>
</tr>
<tr id="row1144995117093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1634882886093533"><a name="p1634882886093533"></a><a name="p1634882886093533"></a><a href="Graphic.md#ga10723293ab9e384907dd9dacbc9ad448">SetImage</a> (const <a href="OHOS-ImageInfo.md">ImageInfo</a> *foregroundImage, const <a href="OHOS-ImageInfo.md">ImageInfo</a> *backgroundImage=nullptr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1852654630093533"><a name="p1852654630093533"></a><a name="p1852654630093533"></a>void&nbsp;</p>
<p id="p2122495262093533"><a name="p2122495262093533"></a><a name="p2122495262093533"></a>Sets the image as a pixel map for this progress bar. </p>
</td>
</tr>
<tr id="row158815387093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1909505778093533"><a name="p1909505778093533"></a><a name="p1909505778093533"></a><a href="Graphic.md#ga747a29652b441a06d09a97a297aae9bb">SetStep</a> (uint16_t step)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1148723581093533"><a name="p1148723581093533"></a><a name="p1148723581093533"></a>void&nbsp;</p>
<p id="p1077798588093533"><a name="p1077798588093533"></a><a name="p1077798588093533"></a>Sets the step for this progress bar. </p>
</td>
</tr>
<tr id="row207242270093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p793829692093533"><a name="p793829692093533"></a><a name="p793829692093533"></a><a href="Graphic.md#ga9c1678604605a54c2e338d283c46866d">GetStep</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p944745513093533"><a name="p944745513093533"></a><a name="p944745513093533"></a>uint16_t&nbsp;</p>
<p id="p651946149093533"><a name="p651946149093533"></a><a name="p651946149093533"></a>Obtains the current step of this progress bar. </p>
</td>
</tr>
<tr id="row389964010093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p558052590093533"><a name="p558052590093533"></a><a name="p558052590093533"></a><a href="Graphic.md#ga6817b5178e93e5f16f2b420cf5a171c1">SetBackgroundStyle</a> (const <a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p367497373093533"><a name="p367497373093533"></a><a name="p367497373093533"></a>void&nbsp;</p>
<p id="p26137574093533"><a name="p26137574093533"></a><a name="p26137574093533"></a>Sets the background style for this progress bar. </p>
</td>
</tr>
<tr id="row893896380093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2024271809093533"><a name="p2024271809093533"></a><a name="p2024271809093533"></a><a href="Graphic.md#ga23acea0a42587746e35ec5f3a74af59f">SetBackgroundStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p999699965093533"><a name="p999699965093533"></a><a name="p999699965093533"></a>void&nbsp;</p>
<p id="p107740918093533"><a name="p107740918093533"></a><a name="p107740918093533"></a>Sets a background style for this progress bar. </p>
</td>
</tr>
<tr id="row1016341075093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p592474247093533"><a name="p592474247093533"></a><a name="p592474247093533"></a><a href="Graphic.md#gac2ca1212c23c11405b12ae0a46c7eff1">GetBackgroundStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p994673549093533"><a name="p994673549093533"></a><a name="p994673549093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1668205685093533"><a name="p1668205685093533"></a><a name="p1668205685093533"></a>Obtains the background style of this progress bar. </p>
</td>
</tr>
<tr id="row1218759714093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1106967959093533"><a name="p1106967959093533"></a><a name="p1106967959093533"></a><a href="Graphic.md#ga946d3f2c39a79d45149118536b2557a9">GetBackgroundStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2124793051093533"><a name="p2124793051093533"></a><a name="p2124793051093533"></a>int64_t&nbsp;</p>
<p id="p671283850093533"><a name="p671283850093533"></a><a name="p671283850093533"></a>Obtains the value of a background style of this progress bar. </p>
</td>
</tr>
<tr id="row1700027237093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p470566880093533"><a name="p470566880093533"></a><a name="p470566880093533"></a><a href="Graphic.md#gaccebcfa35f98f9bc6be4bb8cc53eb11c">SetForegroundStyle</a> (const <a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p690571320093533"><a name="p690571320093533"></a><a name="p690571320093533"></a>void&nbsp;</p>
<p id="p707935341093533"><a name="p707935341093533"></a><a name="p707935341093533"></a>Sets the foreground style for this progress bar. </p>
</td>
</tr>
<tr id="row48778490093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2073884783093533"><a name="p2073884783093533"></a><a name="p2073884783093533"></a><a href="Graphic.md#gae6386ca25603e42f06087f6b2ef65bae">SetForegroundStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p790315442093533"><a name="p790315442093533"></a><a name="p790315442093533"></a>void&nbsp;</p>
<p id="p598749325093533"><a name="p598749325093533"></a><a name="p598749325093533"></a>Sets a foreground style for this progress bar. </p>
</td>
</tr>
<tr id="row1738659503093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p323979896093533"><a name="p323979896093533"></a><a name="p323979896093533"></a><a href="Graphic.md#gac77f945f375f333f80bd70254b5c1f96">GetForegroundStyle</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1737161585093533"><a name="p1737161585093533"></a><a name="p1737161585093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p448433746093533"><a name="p448433746093533"></a><a name="p448433746093533"></a>Obtains the foreground style of this progress bar. </p>
</td>
</tr>
<tr id="row39690775093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1749488120093533"><a name="p1749488120093533"></a><a name="p1749488120093533"></a><a href="Graphic.md#ga74cd121dd1794d7e8d905b233bd98217">GetForegroundStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p798539215093533"><a name="p798539215093533"></a><a name="p798539215093533"></a>int64_t&nbsp;</p>
<p id="p344390718093533"><a name="p344390718093533"></a><a name="p344390718093533"></a>Obtains the value of a foreground style of this progress bar. </p>
</td>
</tr>
<tr id="row1658994635093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p135863528093533"><a name="p135863528093533"></a><a name="p135863528093533"></a><a href="Graphic.md#gabdc0eb4d279212ea7c3ea7a1f9a85e13">SetCapType</a> (<a href="Graphic.md#ga2db3928cdf793f4950245a6841dd43d6">CapType</a> cap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p976964021093533"><a name="p976964021093533"></a><a name="p976964021093533"></a>void&nbsp;</p>
<p id="p2061524700093533"><a name="p2061524700093533"></a><a name="p2061524700093533"></a>Sets the type of caps on the background and foreground of the progress bar. </p>
</td>
</tr>
<tr id="row649067771093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p920353715093533"><a name="p920353715093533"></a><a name="p920353715093533"></a><a href="Graphic.md#ga7aad5b50d945efe5f9304bc978b2001c">UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1996620177093533"><a name="p1996620177093533"></a><a name="p1996620177093533"></a>&nbsp;</p>
<p id="p1058441001093533"><a name="p1058441001093533"></a><a name="p1058441001093533"></a>A default constructor used to create an <strong id="b1754072521093533"><a name="b1754072521093533"></a><a name="b1754072521093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row1601291747093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1929472418093533"><a name="p1929472418093533"></a><a name="p1929472418093533"></a><a href="Graphic.md#ga57d429bb1cd71782f3b825f1bc6b9362">UIView</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1920841167093533"><a name="p1920841167093533"></a><a name="p1920841167093533"></a>&nbsp;</p>
<p id="p627110643093533"><a name="p627110643093533"></a><a name="p627110643093533"></a>A constructor used to create an <strong id="b1798013282093533"><a name="b1798013282093533"></a><a name="b1798013282093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row2015029548093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1988673745093533"><a name="p1988673745093533"></a><a name="p1988673745093533"></a><a href="Graphic.md#ga17f0ffc1090bdcce0f88288da5962012">~UIView</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1027704941093533"><a name="p1027704941093533"></a><a name="p1027704941093533"></a>virtual&nbsp;</p>
<p id="p1215974887093533"><a name="p1215974887093533"></a><a name="p1215974887093533"></a>A destructor used to delete the <strong id="b460437303093533"><a name="b460437303093533"></a><a name="b460437303093533"></a><a href="OHOS-UIView.md">UIView</a></strong> instance. </p>
</td>
</tr>
<tr id="row499789364093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2089359934093533"><a name="p2089359934093533"></a><a name="p2089359934093533"></a><a href="Graphic.md#gac295fe4851eed72f48e9a63771416d71">OnPreDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2090312966093533"><a name="p2090312966093533"></a><a name="p2090312966093533"></a>virtual bool&nbsp;</p>
<p id="p1893733046093533"><a name="p1893733046093533"></a><a name="p1893733046093533"></a>Called before a view is drawn. This function is used to check whether the parent view of this view needs to be redrawn so as to optimize the drawing process. </p>
</td>
</tr>
<tr id="row940822973093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p112251844093533"><a name="p112251844093533"></a><a name="p112251844093533"></a><a href="Graphic.md#gab70473cd0d8fe7c9d4bb817caeee9153">OnPostDraw</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1432350150093533"><a name="p1432350150093533"></a><a name="p1432350150093533"></a>virtual void&nbsp;</p>
<p id="p1112498881093533"><a name="p1112498881093533"></a><a name="p1112498881093533"></a>Called after a view is drawn. </p>
</td>
</tr>
<tr id="row1438354119093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1673665454093533"><a name="p1673665454093533"></a><a name="p1673665454093533"></a><a href="Graphic.md#ga81726238adeda1efa989be6ed4f4fe5b">ReMeasure</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257975028093533"><a name="p257975028093533"></a><a name="p257975028093533"></a>virtual void&nbsp;</p>
<p id="p1556740197093533"><a name="p1556740197093533"></a><a name="p1556740197093533"></a>Remeasures the view size. </p>
</td>
</tr>
<tr id="row435906894093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p838243983093533"><a name="p838243983093533"></a><a name="p838243983093533"></a><a href="Graphic.md#ga2a9a38b8450fbb196277238a51fbbf99">Invalidate</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p70952983093533"><a name="p70952983093533"></a><a name="p70952983093533"></a>void&nbsp;</p>
<p id="p2117355600093533"><a name="p2117355600093533"></a><a name="p2117355600093533"></a>Refreshes the invalidated area of the view. </p>
</td>
</tr>
<tr id="row185655843093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1279731309093533"><a name="p1279731309093533"></a><a name="p1279731309093533"></a><a href="Graphic.md#gaf0e6b65ced8b931642f2a80c195962d2">InvalidateRect</a> (const <a href="OHOS-Rect.md">Rect</a> &amp;invalidatedArea)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p506206512093533"><a name="p506206512093533"></a><a name="p506206512093533"></a>void&nbsp;</p>
<p id="p78656950093533"><a name="p78656950093533"></a><a name="p78656950093533"></a>Refreshes a view in a specified invalidated area. </p>
</td>
</tr>
<tr id="row868534552093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p166288579093533"><a name="p166288579093533"></a><a name="p166288579093533"></a><a href="Graphic.md#gac311aa47301d727c35fc31f8630d016e">OnLongPressEvent</a> (const <a href="OHOS-LongPressEvent.md">LongPressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p352239069093533"><a name="p352239069093533"></a><a name="p352239069093533"></a>virtual bool&nbsp;</p>
<p id="p1947588501093533"><a name="p1947588501093533"></a><a name="p1947588501093533"></a>Called when the view is long pressed. </p>
</td>
</tr>
<tr id="row652896643093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p178408784093533"><a name="p178408784093533"></a><a name="p178408784093533"></a><a href="Graphic.md#gac0e10556ff99b8a92bfb11df6456d605">OnDragStartEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p930426239093533"><a name="p930426239093533"></a><a name="p930426239093533"></a>virtual bool&nbsp;</p>
<p id="p1875981073093533"><a name="p1875981073093533"></a><a name="p1875981073093533"></a>Called when the view starts to drag. </p>
</td>
</tr>
<tr id="row598090500093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p50218409093533"><a name="p50218409093533"></a><a name="p50218409093533"></a><a href="Graphic.md#ga46249c8caf06b81590d9450e30a31147">OnDragEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1180376562093533"><a name="p1180376562093533"></a><a name="p1180376562093533"></a>virtual bool&nbsp;</p>
<p id="p2115831102093533"><a name="p2115831102093533"></a><a name="p2115831102093533"></a>Called when the view is being dragged. </p>
</td>
</tr>
<tr id="row332640532093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2141317179093533"><a name="p2141317179093533"></a><a name="p2141317179093533"></a><a href="Graphic.md#ga1799d33be73f64ed2066f50d7e65468d">OnDragEndEvent</a> (const <a href="OHOS-DragEvent.md">DragEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1143252796093533"><a name="p1143252796093533"></a><a name="p1143252796093533"></a>virtual bool&nbsp;</p>
<p id="p1246888198093533"><a name="p1246888198093533"></a><a name="p1246888198093533"></a>Called when the view stops dragging. </p>
</td>
</tr>
<tr id="row291640554093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2003443592093533"><a name="p2003443592093533"></a><a name="p2003443592093533"></a><a href="Graphic.md#gad08697a29aae4c58267f494b66b9a547">OnClickEvent</a> (const <a href="OHOS-ClickEvent.md">ClickEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1758902684093533"><a name="p1758902684093533"></a><a name="p1758902684093533"></a>virtual void&nbsp;</p>
<p id="p490050929093533"><a name="p490050929093533"></a><a name="p490050929093533"></a>Called when the view is clicked. </p>
</td>
</tr>
<tr id="row1462324890093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1154733840093533"><a name="p1154733840093533"></a><a name="p1154733840093533"></a><a href="Graphic.md#gafa544ff2d27785a9410a80689f1ad3b1">OnPressEvent</a> (const <a href="OHOS-PressEvent.md">PressEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p768802653093533"><a name="p768802653093533"></a><a name="p768802653093533"></a>virtual void&nbsp;</p>
<p id="p988754071093533"><a name="p988754071093533"></a><a name="p988754071093533"></a>Called when the view is pressed. </p>
</td>
</tr>
<tr id="row101022717093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p84613485093533"><a name="p84613485093533"></a><a name="p84613485093533"></a><a href="Graphic.md#ga7bd1a74563b059b03fbf66f9add53ee3">OnReleaseEvent</a> (const <a href="OHOS-ReleaseEvent.md">ReleaseEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p442786279093533"><a name="p442786279093533"></a><a name="p442786279093533"></a>virtual void&nbsp;</p>
<p id="p217638196093533"><a name="p217638196093533"></a><a name="p217638196093533"></a>Called when the view is released. </p>
</td>
</tr>
<tr id="row2064915987093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p817305595093533"><a name="p817305595093533"></a><a name="p817305595093533"></a><a href="Graphic.md#ga8f01ff25a33b20df0758f564148e579d">OnCancelEvent</a> (const <a href="OHOS-CancelEvent.md">CancelEvent</a> &amp;event)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1768113546093533"><a name="p1768113546093533"></a><a name="p1768113546093533"></a>virtual void&nbsp;</p>
<p id="p1731252897093533"><a name="p1731252897093533"></a><a name="p1731252897093533"></a>Called when a click event on the view is canceled. </p>
</td>
</tr>
<tr id="row193741642093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p318243939093533"><a name="p318243939093533"></a><a name="p318243939093533"></a><a href="Graphic.md#gad8e3cf5f0dd003a6aa932ef04e7b59f2">SetOnDragListener</a> (<a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *onDragListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1222661571093533"><a name="p1222661571093533"></a><a name="p1222661571093533"></a>void&nbsp;</p>
<p id="p192455399093533"><a name="p192455399093533"></a><a name="p192455399093533"></a>Sets a drag event listener for the view. </p>
</td>
</tr>
<tr id="row1787162675093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p155648392093533"><a name="p155648392093533"></a><a name="p155648392093533"></a><a href="Graphic.md#ga45a02cba4887c5c0b8e243941bcdc5cb">GetOnDragListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p567707147093533"><a name="p567707147093533"></a><a name="p567707147093533"></a><a href="OHOS-UIView-OnDragListener.md">OnDragListener</a> *&amp;&nbsp;</p>
<p id="p439792143093533"><a name="p439792143093533"></a><a name="p439792143093533"></a>Obtains the drag event listener for the view. </p>
</td>
</tr>
<tr id="row377658968093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1216842823093533"><a name="p1216842823093533"></a><a name="p1216842823093533"></a><a href="Graphic.md#ga4564bf8d8c7184e9c02bf33c9e171fa3">SetOnClickListener</a> (<a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *onClickListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p397203989093533"><a name="p397203989093533"></a><a name="p397203989093533"></a>void&nbsp;</p>
<p id="p820043017093533"><a name="p820043017093533"></a><a name="p820043017093533"></a>Sets a click event listener for the view. </p>
</td>
</tr>
<tr id="row2085222119093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p559652695093533"><a name="p559652695093533"></a><a name="p559652695093533"></a><a href="Graphic.md#ga35e885cb380c37245fa4305bba10cd4a">GetOnClickListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p341810243093533"><a name="p341810243093533"></a><a name="p341810243093533"></a><a href="OHOS-UIView-OnClickListener.md">OnClickListener</a> *&amp;&nbsp;</p>
<p id="p275449598093533"><a name="p275449598093533"></a><a name="p275449598093533"></a>Obtains the click event listener for the view. </p>
</td>
</tr>
<tr id="row1367893870093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2064786325093533"><a name="p2064786325093533"></a><a name="p2064786325093533"></a><a href="Graphic.md#gabcbe7a0adce600424f7f0d5a7396eb5b">SetOnLongPressListener</a> (<a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *onLongPressListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1444347394093533"><a name="p1444347394093533"></a><a name="p1444347394093533"></a>void&nbsp;</p>
<p id="p1312655865093533"><a name="p1312655865093533"></a><a name="p1312655865093533"></a>Sets a long-press event listener for the view. </p>
</td>
</tr>
<tr id="row728867143093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p478484476093533"><a name="p478484476093533"></a><a name="p478484476093533"></a><a href="Graphic.md#gaafd4d354f5f111e758d046109fd7f656">GetOnLongPressListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1524194359093533"><a name="p1524194359093533"></a><a name="p1524194359093533"></a><a href="OHOS-UIView-OnLongPressListener.md">OnLongPressListener</a> *&amp;&nbsp;</p>
<p id="p1833619484093533"><a name="p1833619484093533"></a><a name="p1833619484093533"></a>Obtains the long-press event listener for the view. </p>
</td>
</tr>
<tr id="row994031172093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1992733966093533"><a name="p1992733966093533"></a><a name="p1992733966093533"></a><a href="Graphic.md#gadd697fbf481f98d9d6ca8b67390071af">SetOnTouchListener</a> (<a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *onTouchListener)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1445306739093533"><a name="p1445306739093533"></a><a name="p1445306739093533"></a>void&nbsp;</p>
<p id="p253828540093533"><a name="p253828540093533"></a><a name="p253828540093533"></a>Sets a touch event listener for the view. </p>
</td>
</tr>
<tr id="row630874941093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p770034064093533"><a name="p770034064093533"></a><a name="p770034064093533"></a><a href="Graphic.md#gae7c65c68653103dae85acdcef78777a6">GetTouchListener</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1071119236093533"><a name="p1071119236093533"></a><a name="p1071119236093533"></a><a href="OHOS-UIView-OnTouchListener.md">OnTouchListener</a> *&amp;&nbsp;</p>
<p id="p14743523093533"><a name="p14743523093533"></a><a name="p14743523093533"></a>Obtains the touch event listener for the view. </p>
</td>
</tr>
<tr id="row1579023322093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1115192787093533"><a name="p1115192787093533"></a><a name="p1115192787093533"></a><a href="Graphic.md#gaea9f334f2481e1c03a2cd8f3078d7c72">GetTargetView</a> (const <a href="OHOS-Point.md">Point</a> &amp;point, <a href="OHOS-UIView.md">UIView</a> **last)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p11399700093533"><a name="p11399700093533"></a><a name="p11399700093533"></a>virtual void&nbsp;</p>
<p id="p1299958278093533"><a name="p1299958278093533"></a><a name="p1299958278093533"></a>Obtains the top-level view based on specified coordinates. </p>
</td>
</tr>
<tr id="row130152787093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p303738917093533"><a name="p303738917093533"></a><a name="p303738917093533"></a><a href="Graphic.md#gaeea67a3a84b4ffe9bfeda418b82184cc">SetParent</a> (<a href="OHOS-UIView.md">UIView</a> *parent)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267957727093533"><a name="p267957727093533"></a><a name="p267957727093533"></a>void&nbsp;</p>
<p id="p374860457093533"><a name="p374860457093533"></a><a name="p374860457093533"></a>Sets the parent view for the view. </p>
</td>
</tr>
<tr id="row2075543699093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p794988241093533"><a name="p794988241093533"></a><a name="p794988241093533"></a><a href="Graphic.md#ga706530e4a38108615d5e0c918685ec96">GetParent</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p777398510093533"><a name="p777398510093533"></a><a name="p777398510093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1034669220093533"><a name="p1034669220093533"></a><a name="p1034669220093533"></a>Obtains the parent view of the view. </p>
</td>
</tr>
<tr id="row409068021093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1970134174093533"><a name="p1970134174093533"></a><a name="p1970134174093533"></a><a href="Graphic.md#ga02bec5de07d93cabc45affba79eba4ad">SetNextSibling</a> (<a href="OHOS-UIView.md">UIView</a> *sibling)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1007959451093533"><a name="p1007959451093533"></a><a name="p1007959451093533"></a>void&nbsp;</p>
<p id="p447180369093533"><a name="p447180369093533"></a><a name="p447180369093533"></a>Sets the next sibling view for the view. </p>
</td>
</tr>
<tr id="row1681703476093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p91952407093533"><a name="p91952407093533"></a><a name="p91952407093533"></a><a href="Graphic.md#gab0030977b30ddc9f2e15dbc2f58937e6">GetNextSibling</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p912013324093533"><a name="p912013324093533"></a><a name="p912013324093533"></a><a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p832049952093533"><a name="p832049952093533"></a><a name="p832049952093533"></a>Obtains the next sibling view of the view. </p>
</td>
</tr>
<tr id="row781888297093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p664568593093533"><a name="p664568593093533"></a><a name="p664568593093533"></a><a href="Graphic.md#ga07e7e1f268bd6ce975f4f0f8487af5d0">SetVisible</a> (bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p601850216093533"><a name="p601850216093533"></a><a name="p601850216093533"></a>virtual void&nbsp;</p>
<p id="p533564112093533"><a name="p533564112093533"></a><a name="p533564112093533"></a>Sets whether the view is visible. </p>
</td>
</tr>
<tr id="row1154287736093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p205306874093533"><a name="p205306874093533"></a><a name="p205306874093533"></a><a href="Graphic.md#gaee178fc0a86ac03a6bdf2ade0c1914c8">IsVisible</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1031083508093533"><a name="p1031083508093533"></a><a name="p1031083508093533"></a>bool&nbsp;</p>
<p id="p1138569783093533"><a name="p1138569783093533"></a><a name="p1138569783093533"></a>Checks whether the view is visible. </p>
</td>
</tr>
<tr id="row718213808093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p883046006093533"><a name="p883046006093533"></a><a name="p883046006093533"></a><a href="Graphic.md#gaf9fb55fd9aa397f7158f1515e90bce02">SetTouchable</a> (bool touch)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p984724679093533"><a name="p984724679093533"></a><a name="p984724679093533"></a>void&nbsp;</p>
<p id="p715489749093533"><a name="p715489749093533"></a><a name="p715489749093533"></a>Sets whether the view is touchable. </p>
</td>
</tr>
<tr id="row1678470829093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p557484193093533"><a name="p557484193093533"></a><a name="p557484193093533"></a><a href="Graphic.md#ga502a53fb77b260fa36b5b3adf82e2340">IsTouchable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1492453430093533"><a name="p1492453430093533"></a><a name="p1492453430093533"></a>bool&nbsp;</p>
<p id="p735034834093533"><a name="p735034834093533"></a><a name="p735034834093533"></a>Checks whether the view is touchable. </p>
</td>
</tr>
<tr id="row517114924093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1383903709093533"><a name="p1383903709093533"></a><a name="p1383903709093533"></a><a href="Graphic.md#gab06abe0fe824c048f3b72974f9a8f0d0">SetDraggable</a> (bool draggable)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p986597598093533"><a name="p986597598093533"></a><a name="p986597598093533"></a>void&nbsp;</p>
<p id="p491284572093533"><a name="p491284572093533"></a><a name="p491284572093533"></a>Sets whether the view is draggable. </p>
</td>
</tr>
<tr id="row2123304885093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p896611671093533"><a name="p896611671093533"></a><a name="p896611671093533"></a><a href="Graphic.md#ga25bb796ff400c767d622cbed280fc500">IsDraggable</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p914088418093533"><a name="p914088418093533"></a><a name="p914088418093533"></a>bool&nbsp;</p>
<p id="p1473618829093533"><a name="p1473618829093533"></a><a name="p1473618829093533"></a>Checks whether the view is draggable. </p>
</td>
</tr>
<tr id="row1298949845093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1926934461093533"><a name="p1926934461093533"></a><a name="p1926934461093533"></a><a href="Graphic.md#ga6c08e49bf7a82a7ebaef0f251e7a6f85">SetDragParentInstead</a> (bool dragParentInstead)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p509143344093533"><a name="p509143344093533"></a><a name="p509143344093533"></a>void&nbsp;</p>
<p id="p124703244093533"><a name="p124703244093533"></a><a name="p124703244093533"></a>Sets whether to transfer the drag event to the parent view for processing when the view is being dragged. </p>
</td>
</tr>
<tr id="row1725936798093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p503503301093533"><a name="p503503301093533"></a><a name="p503503301093533"></a><a href="Graphic.md#gaf0c462bc31e779b1898ad4cdfdad6faf">IsDragParentInstead</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2132830759093533"><a name="p2132830759093533"></a><a name="p2132830759093533"></a>bool&nbsp;</p>
<p id="p683122202093533"><a name="p683122202093533"></a><a name="p683122202093533"></a>Obtains whether the view transfers a drag event to the parent view for processing. </p>
</td>
</tr>
<tr id="row1085679774093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p124611663093533"><a name="p124611663093533"></a><a name="p124611663093533"></a><a href="Graphic.md#ga86cb8d364f18494d67636c55babced5c">GetRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1940463634093533"><a name="p1940463634093533"></a><a name="p1940463634093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p950154306093533"><a name="p950154306093533"></a><a name="p950154306093533"></a>Obtains the absolute rectangle area of the view. When the view has deformation such as rotation, the rectangle area is the intersection set of the absolute rectangle area and deformation matrix. </p>
</td>
</tr>
<tr id="row258557687093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p764883664093533"><a name="p764883664093533"></a><a name="p764883664093533"></a><a href="Graphic.md#ga06e79704a19f2a238982076cac3d059b">GetVisibleRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1733913023093533"><a name="p1733913023093533"></a><a name="p1733913023093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1471169715093533"><a name="p1471169715093533"></a><a name="p1471169715093533"></a>Obtains the visible absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row973348450093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1376158055093533"><a name="p1376158055093533"></a><a name="p1376158055093533"></a><a href="Graphic.md#gab3f8993b3953f27bfc61d53429916cba">GetMaskedRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p218239761093533"><a name="p218239761093533"></a><a name="p218239761093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1915177049093533"><a name="p1915177049093533"></a><a name="p1915177049093533"></a>Obtains the valid absolute rectangle area of the view. The valid area refers to the area where the view can be displayed. Generally, the valid area is the same as the visible view area, but they may be different in the grid layout. </p>
</td>
</tr>
<tr id="row1633712266093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1143074213093533"><a name="p1143074213093533"></a><a name="p1143074213093533"></a><a href="Graphic.md#ga64cf308a09999def1192f9c4e0f17f0a">GetOrigRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p608886329093533"><a name="p608886329093533"></a><a name="p608886329093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p1809561960093533"><a name="p1809561960093533"></a><a name="p1809561960093533"></a>Obtains the absolute rectangle area of the view. </p>
</td>
</tr>
<tr id="row962312827093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p106779780093533"><a name="p106779780093533"></a><a name="p106779780093533"></a><a href="Graphic.md#ga9db88eae712676359d02a92be14fa316">GetContentRect</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1843231535093533"><a name="p1843231535093533"></a><a name="p1843231535093533"></a>virtual <a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p991290523093533"><a name="p991290523093533"></a><a name="p991290523093533"></a>Obtains the content of the absolute rectangle area of the view. This area excludes padding. </p>
</td>
</tr>
<tr id="row1999005059093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p570879947093533"><a name="p570879947093533"></a><a name="p570879947093533"></a><a href="Graphic.md#gae9b96837fa1d45648a2a6fbbfcc5eb4a">GetRelativeRect</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p931791725093533"><a name="p931791725093533"></a><a name="p931791725093533"></a><a href="OHOS-Rect.md">Rect</a>&nbsp;</p>
<p id="p548751334093533"><a name="p548751334093533"></a><a name="p548751334093533"></a>Obtains the rectangular area of the view relative to the parent view, that is, the rectangular area relative to the coordinates of the parent view. </p>
</td>
</tr>
<tr id="row1291634126093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p483241444093533"><a name="p483241444093533"></a><a name="p483241444093533"></a><a href="Graphic.md#gae6c5f3bcf99dc837bcecd60c38d3df5a">ResizeVisibleArea</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p118855884093533"><a name="p118855884093533"></a><a name="p118855884093533"></a>void&nbsp;</p>
<p id="p1480789804093533"><a name="p1480789804093533"></a><a name="p1480789804093533"></a>Adjusts the size of the visible area. This operation may affect the final display size. </p>
</td>
</tr>
<tr id="row1521462875093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p885413537093533"><a name="p885413537093533"></a><a name="p885413537093533"></a><a href="Graphic.md#ga90cf8cffb98d71c30d6fc1d118442dbd">GetWidth</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p108330165093533"><a name="p108330165093533"></a><a name="p108330165093533"></a>virtual int16_t&nbsp;</p>
<p id="p234156345093533"><a name="p234156345093533"></a><a name="p234156345093533"></a>Obtains the width for the view. </p>
</td>
</tr>
<tr id="row816672031093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p888248637093533"><a name="p888248637093533"></a><a name="p888248637093533"></a><a href="Graphic.md#ga9b35f4603a561c7a9a29b023a022ac97">GetHeight</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2075051436093533"><a name="p2075051436093533"></a><a name="p2075051436093533"></a>virtual int16_t&nbsp;</p>
<p id="p496593907093533"><a name="p496593907093533"></a><a name="p496593907093533"></a>Obtains the height for the view. </p>
</td>
</tr>
<tr id="row488574349093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p858783553093533"><a name="p858783553093533"></a><a name="p858783553093533"></a><a href="Graphic.md#gae985b607d2f0701911778bf20d640ccd">Resize</a> (int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1803949338093533"><a name="p1803949338093533"></a><a name="p1803949338093533"></a>virtual void&nbsp;</p>
<p id="p1865033279093533"><a name="p1865033279093533"></a><a name="p1865033279093533"></a>Adjusts the size of the view. </p>
</td>
</tr>
<tr id="row327225696093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p720608222093533"><a name="p720608222093533"></a><a name="p720608222093533"></a><a href="Graphic.md#gaded403626558d28e62bf5632ccbb24b5">SetX</a> (int16_t x)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p655644792093533"><a name="p655644792093533"></a><a name="p655644792093533"></a>virtual void&nbsp;</p>
<p id="p736690717093533"><a name="p736690717093533"></a><a name="p736690717093533"></a>Sets the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row882832280093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1023484324093533"><a name="p1023484324093533"></a><a name="p1023484324093533"></a><a href="Graphic.md#ga89dc5f8fb1cb4b2259dc0439185359f1">GetX</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p743176314093533"><a name="p743176314093533"></a><a name="p743176314093533"></a>int16_t&nbsp;</p>
<p id="p742704081093533"><a name="p742704081093533"></a><a name="p742704081093533"></a>Obtains the x-coordinate for the view. </p>
</td>
</tr>
<tr id="row1417310517093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1732949137093533"><a name="p1732949137093533"></a><a name="p1732949137093533"></a><a href="Graphic.md#gaaa8edc224cf1c7deb2724fb225960877">SetY</a> (int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2058803164093533"><a name="p2058803164093533"></a><a name="p2058803164093533"></a>virtual void&nbsp;</p>
<p id="p2074298066093533"><a name="p2074298066093533"></a><a name="p2074298066093533"></a>Sets the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row2103617206093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p799884083093533"><a name="p799884083093533"></a><a name="p799884083093533"></a><a href="Graphic.md#ga193619d649204b0e9bb854d3b30275c3">GetY</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p20514552093533"><a name="p20514552093533"></a><a name="p20514552093533"></a>int16_t&nbsp;</p>
<p id="p1457504093533"><a name="p1457504093533"></a><a name="p1457504093533"></a>Obtains the y-coordinate for the view. </p>
</td>
</tr>
<tr id="row350371841093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1068936658093533"><a name="p1068936658093533"></a><a name="p1068936658093533"></a><a href="Graphic.md#gab34233f6aeae330b025969137d03e67a">SetPosition</a> (int16_t x, int16_t y)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p587735908093533"><a name="p587735908093533"></a><a name="p587735908093533"></a>virtual void&nbsp;</p>
<p id="p1372720549093533"><a name="p1372720549093533"></a><a name="p1372720549093533"></a>Sets the position for the view. </p>
</td>
</tr>
<tr id="row1137884140093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p178190219093533"><a name="p178190219093533"></a><a name="p178190219093533"></a><a href="Graphic.md#gaf8ce4c009f23b7175b2b34bac4a74262">SetPosition</a> (int16_t x, int16_t y, int16_t width, int16_t height)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p10736695093533"><a name="p10736695093533"></a><a name="p10736695093533"></a>virtual void&nbsp;</p>
<p id="p337720019093533"><a name="p337720019093533"></a><a name="p337720019093533"></a>Adjusts the position and size of the view. </p>
</td>
</tr>
<tr id="row1109688393093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1029436604093533"><a name="p1029436604093533"></a><a name="p1029436604093533"></a><a href="Graphic.md#gab2ce8c11abbd55f40687f38a52511b11">IsViewGroup</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p180208654093533"><a name="p180208654093533"></a><a name="p180208654093533"></a>bool&nbsp;</p>
<p id="p540293630093533"><a name="p540293630093533"></a><a name="p540293630093533"></a>Checks whether the view is a container view. </p>
</td>
</tr>
<tr id="row227649902093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1027089027093533"><a name="p1027089027093533"></a><a name="p1027089027093533"></a><a href="Graphic.md#ga980fc6824c64cfae6af8657aee17af88">SetIntercept</a> (bool isIntercept)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1197926515093533"><a name="p1197926515093533"></a><a name="p1197926515093533"></a>void&nbsp;</p>
<p id="p1473464794093533"><a name="p1473464794093533"></a><a name="p1473464794093533"></a>Sets whether to intercept the drag event. If intercepted, the view does not transfer the drag event to the parent view after local processing. </p>
</td>
</tr>
<tr id="row473456570093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p21844774093533"><a name="p21844774093533"></a><a name="p21844774093533"></a><a href="Graphic.md#ga8623abbbeff458c0cb2d7dc0d1f21e4a">SetTransformMap</a> (const <a href="OHOS-TransformMap.md">TransformMap</a> &amp;transMap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p527076811093533"><a name="p527076811093533"></a><a name="p527076811093533"></a>void&nbsp;</p>
<p id="p182701266093533"><a name="p182701266093533"></a><a name="p182701266093533"></a>Sets the affine transformation matrix. </p>
</td>
</tr>
<tr id="row1865399283093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1495364122093533"><a name="p1495364122093533"></a><a name="p1495364122093533"></a><a href="Graphic.md#gab8cee5a7052a88722768c8ed1324abc1">GetTransformMap</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p551281452093533"><a name="p551281452093533"></a><a name="p551281452093533"></a><a href="OHOS-TransformMap.md">TransformMap</a> &amp;&nbsp;</p>
<p id="p1506387769093533"><a name="p1506387769093533"></a><a name="p1506387769093533"></a>Obtains an affine transformation matrix. </p>
</td>
</tr>
<tr id="row1289024990093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1255916369093533"><a name="p1255916369093533"></a><a name="p1255916369093533"></a><a href="Graphic.md#ga0573aa25307c22319db4629781b5cad2">GetChildById</a> (const char *id) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p135443167093533"><a name="p135443167093533"></a><a name="p135443167093533"></a>virtual <a href="OHOS-UIView.md">UIView</a> *&nbsp;</p>
<p id="p1614630784093533"><a name="p1614630784093533"></a><a name="p1614630784093533"></a>Obtains the child view of a specified ID. </p>
</td>
</tr>
<tr id="row1283312426093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1267780606093533"><a name="p1267780606093533"></a><a name="p1267780606093533"></a><a href="Graphic.md#ga0caaa15c9b304673331e778a266be77f">SetViewId</a> (const char *id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1321437264093533"><a name="p1321437264093533"></a><a name="p1321437264093533"></a>void&nbsp;</p>
<p id="p885906197093533"><a name="p885906197093533"></a><a name="p885906197093533"></a>Sets the view ID. </p>
</td>
</tr>
<tr id="row1702074549093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p480013545093533"><a name="p480013545093533"></a><a name="p480013545093533"></a><a href="Graphic.md#gad6c7644bd2abfa3c92d80776b0bd1936">GetViewId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1159962678093533"><a name="p1159962678093533"></a><a name="p1159962678093533"></a>const char *&nbsp;</p>
<p id="p1611678085093533"><a name="p1611678085093533"></a><a name="p1611678085093533"></a>Obtains the view ID. </p>
</td>
</tr>
<tr id="row2011679896093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1904735936093533"><a name="p1904735936093533"></a><a name="p1904735936093533"></a><a href="Graphic.md#ga77a961aa53567c5214508b4569801c16">SetViewIndex</a> (int16_t <a href="zh-cn_topic_0000001055198076.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1146280947093533"><a name="p1146280947093533"></a><a name="p1146280947093533"></a>void&nbsp;</p>
<p id="p824864020093533"><a name="p824864020093533"></a><a name="p824864020093533"></a>Sets the view index. </p>
</td>
</tr>
<tr id="row882795757093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1806410360093533"><a name="p1806410360093533"></a><a name="p1806410360093533"></a><a href="Graphic.md#ga62f51715b6d420a296ebe0296717b906">GetViewIndex</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p264312733093533"><a name="p264312733093533"></a><a name="p264312733093533"></a>int16_t&nbsp;</p>
<p id="p630067888093533"><a name="p630067888093533"></a><a name="p630067888093533"></a>Obtains the view index. </p>
</td>
</tr>
<tr id="row1416270883093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1606190076093533"><a name="p1606190076093533"></a><a name="p1606190076093533"></a><a href="Graphic.md#gaca871fa2f8219e7ea9388e212d1f1e69">LayoutChildren</a> (bool neeInvalidate=false)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1383182924093533"><a name="p1383182924093533"></a><a name="p1383182924093533"></a>virtual void&nbsp;</p>
<p id="p1843272260093533"><a name="p1843272260093533"></a><a name="p1843272260093533"></a>Lays out all child views according to the preset arrangement mode. </p>
</td>
</tr>
<tr id="row1427307947093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2005939800093533"><a name="p2005939800093533"></a><a name="p2005939800093533"></a><a href="Graphic.md#ga443b86ee9275b0421b37a47bad3264dc">LayoutCenterOfParent</a> (int16_t xOffSet=0, int16_t yOffset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p531090158093533"><a name="p531090158093533"></a><a name="p531090158093533"></a>void&nbsp;</p>
<p id="p997730901093533"><a name="p997730901093533"></a><a name="p997730901093533"></a>Lays out the view in the center of the parent view. </p>
</td>
</tr>
<tr id="row73248179093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1065694665093533"><a name="p1065694665093533"></a><a name="p1065694665093533"></a><a href="Graphic.md#ga94999b271f27cd5d6bfaf303f7d5c708">LayoutLeftOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p498768328093533"><a name="p498768328093533"></a><a name="p498768328093533"></a>void&nbsp;</p>
<p id="p2058400225093533"><a name="p2058400225093533"></a><a name="p2058400225093533"></a>Lays out the view on the left of the parent view. </p>
</td>
</tr>
<tr id="row2134453922093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p586030765093533"><a name="p586030765093533"></a><a name="p586030765093533"></a><a href="Graphic.md#ga479528ed259b5539e423955f2b60517d">LayoutRightOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1422346202093533"><a name="p1422346202093533"></a><a name="p1422346202093533"></a>void&nbsp;</p>
<p id="p270727259093533"><a name="p270727259093533"></a><a name="p270727259093533"></a>Lays out the view on the right of the parent view. </p>
</td>
</tr>
<tr id="row1874881280093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1076606464093533"><a name="p1076606464093533"></a><a name="p1076606464093533"></a><a href="Graphic.md#ga859288ea61ad23ba7e381bbc07769e83">LayoutTopOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p580582040093533"><a name="p580582040093533"></a><a name="p580582040093533"></a>void&nbsp;</p>
<p id="p1625449539093533"><a name="p1625449539093533"></a><a name="p1625449539093533"></a>Lays out the view on the top of the parent view. </p>
</td>
</tr>
<tr id="row1049664292093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1129068704093533"><a name="p1129068704093533"></a><a name="p1129068704093533"></a><a href="Graphic.md#ga809aeee4792ae58218a0bcfcb94d5cdc">LayoutBottomOfParent</a> (int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1989726076093533"><a name="p1989726076093533"></a><a name="p1989726076093533"></a>void&nbsp;</p>
<p id="p91031322093533"><a name="p91031322093533"></a><a name="p91031322093533"></a>Lays out the view on the bottom of the parent view. </p>
</td>
</tr>
<tr id="row1770268000093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1382632380093533"><a name="p1382632380093533"></a><a name="p1382632380093533"></a><a href="Graphic.md#gac7f5f2584c716a56fee3783f8dea6246">AlignLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p550012538093533"><a name="p550012538093533"></a><a name="p550012538093533"></a>void&nbsp;</p>
<p id="p875077179093533"><a name="p875077179093533"></a><a name="p875077179093533"></a>Aligns the view with the left of a sibling view. </p>
</td>
</tr>
<tr id="row957928126093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2066511292093533"><a name="p2066511292093533"></a><a name="p2066511292093533"></a><a href="Graphic.md#gabb1ac454cdf95593c1e387d5e272433c">AlignRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p573562074093533"><a name="p573562074093533"></a><a name="p573562074093533"></a>void&nbsp;</p>
<p id="p1739498913093533"><a name="p1739498913093533"></a><a name="p1739498913093533"></a>Aligns the view with the right of a sibling view. </p>
</td>
</tr>
<tr id="row951655986093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p179611607093533"><a name="p179611607093533"></a><a name="p179611607093533"></a><a href="Graphic.md#ga903d7cbc59bac06d728b7f6435c9a504">AlignTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1621680428093533"><a name="p1621680428093533"></a><a name="p1621680428093533"></a>void&nbsp;</p>
<p id="p1754409792093533"><a name="p1754409792093533"></a><a name="p1754409792093533"></a>Aligns the view with the top of a sibling view. </p>
</td>
</tr>
<tr id="row1904920495093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p405725736093533"><a name="p405725736093533"></a><a name="p405725736093533"></a><a href="Graphic.md#ga7607c3f9661932c495d080e9d92fb1a3">AlignBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p987460801093533"><a name="p987460801093533"></a><a name="p987460801093533"></a>void&nbsp;</p>
<p id="p1283831843093533"><a name="p1283831843093533"></a><a name="p1283831843093533"></a>Aligns the view with the bottom of a sibling view. </p>
</td>
</tr>
<tr id="row1431501189093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p454423999093533"><a name="p454423999093533"></a><a name="p454423999093533"></a><a href="Graphic.md#gac23776dbc2fce7ff30d57438abfa5230">AlignHorCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1694763235093533"><a name="p1694763235093533"></a><a name="p1694763235093533"></a>void&nbsp;</p>
<p id="p1467501092093533"><a name="p1467501092093533"></a><a name="p1467501092093533"></a>Aligns the view with the center of a sibling view in the x-axis. </p>
</td>
</tr>
<tr id="row1615601483093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1416164693093533"><a name="p1416164693093533"></a><a name="p1416164693093533"></a><a href="Graphic.md#gad3caa27aa0cb73ec4656e7d23aa222de">AlignVerCenterToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1577360002093533"><a name="p1577360002093533"></a><a name="p1577360002093533"></a>void&nbsp;</p>
<p id="p907209821093533"><a name="p907209821093533"></a><a name="p907209821093533"></a>Aligns the view with the center of a sibling view in the y-axis. </p>
</td>
</tr>
<tr id="row113434554093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p174676128093533"><a name="p174676128093533"></a><a name="p174676128093533"></a><a href="Graphic.md#ga58f1a34a943c4492970f901d63bbc3d8">LayoutLeftToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2050890240093533"><a name="p2050890240093533"></a><a name="p2050890240093533"></a>void&nbsp;</p>
<p id="p1702042273093533"><a name="p1702042273093533"></a><a name="p1702042273093533"></a>Lays out the view on the left of a sibling view. </p>
</td>
</tr>
<tr id="row1275333309093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1952299421093533"><a name="p1952299421093533"></a><a name="p1952299421093533"></a><a href="Graphic.md#gac4cd64de5291759add164825a323a0d6">LayoutRightToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846426645093533"><a name="p846426645093533"></a><a name="p846426645093533"></a>void&nbsp;</p>
<p id="p2003262432093533"><a name="p2003262432093533"></a><a name="p2003262432093533"></a>Lays out the view on the right of a sibling view. </p>
</td>
</tr>
<tr id="row248379953093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p178697060093533"><a name="p178697060093533"></a><a name="p178697060093533"></a><a href="Graphic.md#gaaa8385807e3a9bea46f8dcc326252a70">LayoutTopToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p49459532093533"><a name="p49459532093533"></a><a name="p49459532093533"></a>void&nbsp;</p>
<p id="p553591264093533"><a name="p553591264093533"></a><a name="p553591264093533"></a>Lays out the view on the above of a sibling view. </p>
</td>
</tr>
<tr id="row666479296093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1405492878093533"><a name="p1405492878093533"></a><a name="p1405492878093533"></a><a href="Graphic.md#gaa23a68e8ef0fb13b362218e71cf67ace">LayoutBottomToSibling</a> (const char *id, int16_t offset=0)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p731299785093533"><a name="p731299785093533"></a><a name="p731299785093533"></a>void&nbsp;</p>
<p id="p31483161093533"><a name="p31483161093533"></a><a name="p31483161093533"></a>Lays out the view on the below of a sibling view. </p>
</td>
</tr>
<tr id="row425504727093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p932969945093533"><a name="p932969945093533"></a><a name="p932969945093533"></a><a href="Graphic.md#ga9c1a3db000fdcd200fec8d2c49f5a0a8">SetStyle</a> (<a href="OHOS-Style.md">Style</a> &amp;style)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2073403704093533"><a name="p2073403704093533"></a><a name="p2073403704093533"></a>virtual void&nbsp;</p>
<p id="p1076441547093533"><a name="p1076441547093533"></a><a name="p1076441547093533"></a>Sets the view style. </p>
</td>
</tr>
<tr id="row1791368447093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p697435397093533"><a name="p697435397093533"></a><a name="p697435397093533"></a><a href="Graphic.md#ga0945c2f05815dc2e466ef9ceaca2f700">SetStyle</a> (uint8_t key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p103828144093533"><a name="p103828144093533"></a><a name="p103828144093533"></a>virtual void&nbsp;</p>
<p id="p2022864774093533"><a name="p2022864774093533"></a><a name="p2022864774093533"></a>Sets a style. </p>
</td>
</tr>
<tr id="row1925071856093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p972653861093533"><a name="p972653861093533"></a><a name="p972653861093533"></a><a href="Graphic.md#ga4ea19bc9f4b487946c9e29e63b54a0e6">GetStyle</a> (uint8_t key) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p768143083093533"><a name="p768143083093533"></a><a name="p768143083093533"></a>virtual int64_t&nbsp;</p>
<p id="p2066273148093533"><a name="p2066273148093533"></a><a name="p2066273148093533"></a>Obtains the value of a style. </p>
</td>
</tr>
<tr id="row1338625765093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2035754644093533"><a name="p2035754644093533"></a><a name="p2035754644093533"></a><a href="Graphic.md#ga1b28213d4c2cd0f8324bce3fe56eb7bb">GetStyleConst</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1228169610093533"><a name="p1228169610093533"></a><a name="p1228169610093533"></a>const <a href="OHOS-Style.md">Style</a> &amp;&nbsp;</p>
<p id="p1499345543093533"><a name="p1499345543093533"></a><a name="p1499345543093533"></a>Obtains the view style. This function applies to scenarios where the style does not need to be modified, which saves memory. </p>
</td>
</tr>
<tr id="row1327323184093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p756065676093533"><a name="p756065676093533"></a><a name="p756065676093533"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1679829105093533"><a name="p1679829105093533"></a><a name="p1679829105093533"></a>void *&nbsp;</p>
<p id="p948118492093533"><a name="p948118492093533"></a><a name="p948118492093533"></a>Overrides the <strong id="b514648103093533"><a name="b514648103093533"></a><a name="b514648103093533"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row825733585093533"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p210148139093533"><a name="p210148139093533"></a><a name="p210148139093533"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1403233237093533"><a name="p1403233237093533"></a><a name="p1403233237093533"></a>void&nbsp;</p>
<p id="p1017136441093533"><a name="p1017136441093533"></a><a name="p1017136441093533"></a>Overrides the <strong id="b31377638093533"><a name="b31377638093533"></a><a name="b31377638093533"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

