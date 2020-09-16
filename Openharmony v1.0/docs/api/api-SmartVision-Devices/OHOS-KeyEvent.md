# OHOS::KeyEvent<a name="ZH-CN_TOPIC_0000001055198160"></a>

## **Overview**<a name="section1810139862093535"></a>

**Related Modules:**

[Graphic](Graphic.md)

**Description:**

Defines a key event, which indicates that a physical button is pressed or released. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section302703685093535"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table243125813093535"></a>
<table><thead align="left"><tr id="row307972263093535"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1190829060093535"><a name="p1190829060093535"></a><a name="p1190829060093535"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p792514786093535"><a name="p792514786093535"></a><a name="p792514786093535"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1184531231093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p291459893093535"><a name="p291459893093535"></a><a name="p291459893093535"></a><a href="Graphic.md#ga3a52d91ac5d8fd7779baafae6ec92f9b">KeyEvent</a> (uint16_t keyId, uint16_t state)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2068634433093535"><a name="p2068634433093535"></a><a name="p2068634433093535"></a>&nbsp;</p>
<p id="p209686811093535"><a name="p209686811093535"></a><a name="p209686811093535"></a>A constructor used to create a <strong id="b835539016093535"><a name="b835539016093535"></a><a name="b835539016093535"></a><a href="OHOS-KeyEvent.md">KeyEvent</a></strong> instance. </p>
</td>
</tr>
<tr id="row327227114093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1587358560093535"><a name="p1587358560093535"></a><a name="p1587358560093535"></a><a href="Graphic.md#ga468e77700a90ef155a2428af9176551e">~KeyEvent</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1874997557093535"><a name="p1874997557093535"></a><a name="p1874997557093535"></a>&nbsp;</p>
<p id="p756628997093535"><a name="p756628997093535"></a><a name="p756628997093535"></a>A destructor used to delete the <strong id="b444939318093535"><a name="b444939318093535"></a><a name="b444939318093535"></a><a href="OHOS-KeyEvent.md">KeyEvent</a></strong> instance. </p>
</td>
</tr>
<tr id="row882871571093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1071749573093535"><a name="p1071749573093535"></a><a name="p1071749573093535"></a><a href="Graphic.md#gae2b2b83cc3a562b3173f69c95722db99">GetKeyId</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p353128776093535"><a name="p353128776093535"></a><a name="p353128776093535"></a>uint16_t&nbsp;</p>
<p id="p1694673422093535"><a name="p1694673422093535"></a><a name="p1694673422093535"></a>Obtains the key ID. </p>
</td>
</tr>
<tr id="row1099894104093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1259555504093535"><a name="p1259555504093535"></a><a name="p1259555504093535"></a><a href="Graphic.md#gaf93661e10da4b4df75c04d8fd199a5e8">GetState</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p278435718093535"><a name="p278435718093535"></a><a name="p278435718093535"></a>uint16_t&nbsp;</p>
<p id="p1135974590093535"><a name="p1135974590093535"></a><a name="p1135974590093535"></a>Obtains the key state. </p>
</td>
</tr>
<tr id="row889916282093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1786909497093535"><a name="p1786909497093535"></a><a name="p1786909497093535"></a><a href="Graphic.md#ga89cd09ced5537a3479b7901ba8abc6da">Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1091259189093535"><a name="p1091259189093535"></a><a name="p1091259189093535"></a>&nbsp;</p>
<p id="p2042821815093535"><a name="p2042821815093535"></a><a name="p2042821815093535"></a>A default constructor used to create an <strong id="b1126951523093535"><a name="b1126951523093535"></a><a name="b1126951523093535"></a><a href="OHOS-Event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1771507784093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1286990786093535"><a name="p1286990786093535"></a><a name="p1286990786093535"></a><a href="Graphic.md#ga57a9f07c8203c6a60f3b25c4edb526a0">Event</a> (const <a href="OHOS-Point.md">Point</a> &amp;curPos)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2035816948093535"><a name="p2035816948093535"></a><a name="p2035816948093535"></a>&nbsp;</p>
<p id="p852811048093535"><a name="p852811048093535"></a><a name="p852811048093535"></a>A constructor used to create an <strong id="b69265613093535"><a name="b69265613093535"></a><a name="b69265613093535"></a><a href="OHOS-Event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1141032488093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p493844563093535"><a name="p493844563093535"></a><a name="p493844563093535"></a><a href="Graphic.md#gabafa07a6393f4757f402bf9437561fa4">~Event</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p707663655093535"><a name="p707663655093535"></a><a name="p707663655093535"></a>virtual&nbsp;</p>
<p id="p881735045093535"><a name="p881735045093535"></a><a name="p881735045093535"></a>A destructor used to delete the <strong id="b1630740756093535"><a name="b1630740756093535"></a><a name="b1630740756093535"></a><a href="OHOS-Event.md">Event</a></strong> instance. </p>
</td>
</tr>
<tr id="row1162569361093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p966463652093535"><a name="p966463652093535"></a><a name="p966463652093535"></a><a href="Graphic.md#gaea811c661ad416d7f70912ad6fcce269">GetCurrentPos</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1175853389093535"><a name="p1175853389093535"></a><a name="p1175853389093535"></a>const <a href="OHOS-Point.md">Point</a> &amp;&nbsp;</p>
<p id="p1269379535093535"><a name="p1269379535093535"></a><a name="p1269379535093535"></a>Obtains the position where an event occurs. </p>
</td>
</tr>
<tr id="row933499694093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1808713167093535"><a name="p1808713167093535"></a><a name="p1808713167093535"></a><a href="Graphic.md#ga7d56c2a99ab2c98eec9ebc03f67b7777">GetTimeStamp</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1623744739093535"><a name="p1623744739093535"></a><a name="p1623744739093535"></a>const TimeType &amp;&nbsp;</p>
<p id="p623077793093535"><a name="p623077793093535"></a><a name="p623077793093535"></a>Obtains the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row430276191093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1605730482093535"><a name="p1605730482093535"></a><a name="p1605730482093535"></a><a href="Graphic.md#gabee47ba229e81c44f648cf5b3203010f">SetTimeStamp</a> (const TimeType &amp;timeStamp)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p510500544093535"><a name="p510500544093535"></a><a name="p510500544093535"></a>void&nbsp;</p>
<p id="p698278374093535"><a name="p698278374093535"></a><a name="p698278374093535"></a>Sets the timestamp when an event occurs. </p>
</td>
</tr>
<tr id="row598649754093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1534084902093535"><a name="p1534084902093535"></a><a name="p1534084902093535"></a><a href="Graphic.md#ga4854963aa969ee20a6cd174a70f5cd23">operator new</a> (size_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p290990255093535"><a name="p290990255093535"></a><a name="p290990255093535"></a>void *&nbsp;</p>
<p id="p367949732093535"><a name="p367949732093535"></a><a name="p367949732093535"></a>Overrides the <strong id="b1072854379093535"><a name="b1072854379093535"></a><a name="b1072854379093535"></a>new</strong> function. </p>
</td>
</tr>
<tr id="row846343089093535"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1895470073093535"><a name="p1895470073093535"></a><a name="p1895470073093535"></a><a href="Graphic.md#gadf1997a0f56ac2b220e7f0f8e8e0a6ef">operator delete</a> (void *p)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1765620969093535"><a name="p1765620969093535"></a><a name="p1765620969093535"></a>void&nbsp;</p>
<p id="p1060070937093535"><a name="p1060070937093535"></a><a name="p1060070937093535"></a>Overrides the <strong id="b433394960093535"><a name="b433394960093535"></a><a name="b433394960093535"></a>delete</strong> function. </p>
</td>
</tr>
</tbody>
</table>

