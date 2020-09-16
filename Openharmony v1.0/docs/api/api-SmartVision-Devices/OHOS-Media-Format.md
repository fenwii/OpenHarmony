# OHOS::Media::Format<a name="ZH-CN_TOPIC_0000001055039530"></a>

## **Overview**<a name="section2022192628084837"></a>

**Related Modules:**

[MultiMedia\_MediaCommon](MultiMedia_MediaCommon.md)

**Description:**

Saves and sets media metadata, such as the media playback duration. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section3439966084837"></a>

## Public Member Functions<a name="pub-methods"></a>

<a name="table1841983333084837"></a>
<table><thead align="left"><tr id="row1722218816084837"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1358150087084837"><a name="p1358150087084837"></a><a name="p1358150087084837"></a>Public Member Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p639817500084837"><a name="p639817500084837"></a><a name="p639817500084837"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1445684363084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p517439156084837"><a name="p517439156084837"></a><a name="p517439156084837"></a><a href="MultiMedia_MediaCommon.md#ga42435567c8fd61fd2da4834465aca98e">Format</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1693037617084837"><a name="p1693037617084837"></a><a name="p1693037617084837"></a>&nbsp;</p>
<p id="p520657212084837"><a name="p520657212084837"></a><a name="p520657212084837"></a>Default constructor of the <a href="OHOS-Media-Format.md">Format</a> instance. </p>
</td>
</tr>
<tr id="row1397659611084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1369935612084837"><a name="p1369935612084837"></a><a name="p1369935612084837"></a><a href="MultiMedia_MediaCommon.md#ga66771efe315d001e79a14d316c58718e">PutIntValue</a> (const std::string &amp;key, int32_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1178411532084837"><a name="p1178411532084837"></a><a name="p1178411532084837"></a>bool&nbsp;</p>
<p id="p1013928760084837"><a name="p1013928760084837"></a><a name="p1013928760084837"></a>Sets metadata of the integer type. </p>
</td>
</tr>
<tr id="row1608102972084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p342352463084837"><a name="p342352463084837"></a><a name="p342352463084837"></a><a href="MultiMedia_MediaCommon.md#ga5b4477636095d80ec4e65c1be617c61c">PutLongValue</a> (const std::string &amp;key, int64_t value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1467032964084837"><a name="p1467032964084837"></a><a name="p1467032964084837"></a>bool&nbsp;</p>
<p id="p315848353084837"><a name="p315848353084837"></a><a name="p315848353084837"></a>Sets metadata of the long integer type. </p>
</td>
</tr>
<tr id="row703855077084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1278968960084837"><a name="p1278968960084837"></a><a name="p1278968960084837"></a><a href="MultiMedia_MediaCommon.md#gabec9417120824f5bb9eb676be380016f">PutFloatValue</a> (const std::string &amp;key, float value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p534948698084837"><a name="p534948698084837"></a><a name="p534948698084837"></a>bool&nbsp;</p>
<p id="p349666164084837"><a name="p349666164084837"></a><a name="p349666164084837"></a>Sets metadata of the single-precision floating-point type. </p>
</td>
</tr>
<tr id="row1982469102084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1340863439084837"><a name="p1340863439084837"></a><a name="p1340863439084837"></a><a href="MultiMedia_MediaCommon.md#ga9a98a92eb4436301853a049b5f3313c6">PutDoubleValue</a> (const std::string &amp;key, double value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2019423956084837"><a name="p2019423956084837"></a><a name="p2019423956084837"></a>bool&nbsp;</p>
<p id="p495478757084837"><a name="p495478757084837"></a><a name="p495478757084837"></a>Sets metadata of the double-precision floating-point type. </p>
</td>
</tr>
<tr id="row2039432484084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p987870365084837"><a name="p987870365084837"></a><a name="p987870365084837"></a><a href="MultiMedia_MediaCommon.md#gabdc104597559320256930f420eaab82f">PutStringValue</a> (const std::string &amp;key, const std::string &amp;value)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p136938344084837"><a name="p136938344084837"></a><a name="p136938344084837"></a>bool&nbsp;</p>
<p id="p322011156084837"><a name="p322011156084837"></a><a name="p322011156084837"></a>Sets metadata of the string type. </p>
</td>
</tr>
<tr id="row1153185146084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1379951995084837"><a name="p1379951995084837"></a><a name="p1379951995084837"></a><a href="MultiMedia_MediaCommon.md#ga798ef733a253558757f49714090b3969">GetIntValue</a> (const std::string &amp;key, int32_t &amp;value) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p103915937084837"><a name="p103915937084837"></a><a name="p103915937084837"></a>bool&nbsp;</p>
<p id="p2000866882084837"><a name="p2000866882084837"></a><a name="p2000866882084837"></a>Obtains the metadata value of the integer type. </p>
</td>
</tr>
<tr id="row1267326502084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1599259509084837"><a name="p1599259509084837"></a><a name="p1599259509084837"></a><a href="MultiMedia_MediaCommon.md#ga7f1c503f40b78083cb9b9ae9ce93d3b4">GetLongValue</a> (const std::string &amp;key, int64_t &amp;value) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267956233084837"><a name="p267956233084837"></a><a name="p267956233084837"></a>bool&nbsp;</p>
<p id="p1779884757084837"><a name="p1779884757084837"></a><a name="p1779884757084837"></a>Obtains the metadata value of the long integer type. </p>
</td>
</tr>
<tr id="row1066193495084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p518475896084837"><a name="p518475896084837"></a><a name="p518475896084837"></a><a href="MultiMedia_MediaCommon.md#gac4e963a9fe320c0143ed33df5f737cb3">GetFloatValue</a> (const std::string &amp;key, float &amp;value) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1477179059084837"><a name="p1477179059084837"></a><a name="p1477179059084837"></a>bool&nbsp;</p>
<p id="p711110914084837"><a name="p711110914084837"></a><a name="p711110914084837"></a>Obtains the metadata value of the single-precision floating-point type. </p>
</td>
</tr>
<tr id="row1748893564084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1341416423084837"><a name="p1341416423084837"></a><a name="p1341416423084837"></a><a href="MultiMedia_MediaCommon.md#gafe949ed0c2d9dcb5c5e57c7fde226f3e">GetDoubleValue</a> (const std::string &amp;key, double &amp;value) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2098475590084837"><a name="p2098475590084837"></a><a name="p2098475590084837"></a>bool&nbsp;</p>
<p id="p324795423084837"><a name="p324795423084837"></a><a name="p324795423084837"></a>Obtains the metadata value of the double-precision floating-point type. </p>
</td>
</tr>
<tr id="row1981320827084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1447353169084837"><a name="p1447353169084837"></a><a name="p1447353169084837"></a><a href="MultiMedia_MediaCommon.md#ga089a3e44e128fb662b72c56b53c7068b">GetStringValue</a> (const std::string &amp;key, std::string &amp;value) const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p602754331084837"><a name="p602754331084837"></a><a name="p602754331084837"></a>bool&nbsp;</p>
<p id="p332363695084837"><a name="p332363695084837"></a><a name="p332363695084837"></a>Obtains the metadata value of the string type. </p>
</td>
</tr>
<tr id="row532689222084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p422969976084837"><a name="p422969976084837"></a><a name="p422969976084837"></a><a href="MultiMedia_MediaCommon.md#ga4adff4846515cef00987a360a4d117af">GetFormatMap</a> () const</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p215962740084837"><a name="p215962740084837"></a><a name="p215962740084837"></a>const std::map&lt; std::string, <a href="OHOS-Media-FormatData.md">FormatData</a> * &gt; &amp;&nbsp;</p>
<p id="p1777232990084837"><a name="p1777232990084837"></a><a name="p1777232990084837"></a>Obtains the metadata map. </p>
</td>
</tr>
<tr id="row1454651933084837"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p95170271084837"><a name="p95170271084837"></a><a name="p95170271084837"></a><a href="MultiMedia_MediaCommon.md#ga528134c9f87bf755077b3ef51d64e198">CopyFrom</a> (const <a href="OHOS-Media-Format.md">Format</a> &amp;format)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2137280475084837"><a name="p2137280475084837"></a><a name="p2137280475084837"></a>bool&nbsp;</p>
<p id="p1874013097084837"><a name="p1874013097084837"></a><a name="p1874013097084837"></a>Sets all metadata to a specified format. </p>
</td>
</tr>
</tbody>
</table>

