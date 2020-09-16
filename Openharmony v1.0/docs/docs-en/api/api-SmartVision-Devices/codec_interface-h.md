# codec\_interface.h<a name="EN-US_TOPIC_0000001054718089"></a>

## **Overview**<a name="section1510716459084828"></a>

**Related Modules:**

[Codec](codec.md)

**Description:**

Declares codec-related APIs, including functions for initializing audio and video codecs, setting parameters, and controlling and transferring data. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section7636335084828"></a>

## Functions<a name="func-members"></a>

<a name="table1682840473084828"></a>
<table><thead align="left"><tr id="row1481812303084828"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p80335669084828"><a name="p80335669084828"></a><a name="p80335669084828"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1751793269084828"><a name="p1751793269084828"></a><a name="p1751793269084828"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1092937500084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1511487061084828"><a name="p1511487061084828"></a><a name="p1511487061084828"></a><a href="codec.md#gadb2714f1e7a69419cefd38a2ad1f9829">CodecInit</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1649825339084828"><a name="p1649825339084828"></a><a name="p1649825339084828"></a>int32_t </p>
<p id="p1417185605084828"><a name="p1417185605084828"></a><a name="p1417185605084828"></a>Initializes the internal audio and video submodules of the codec. </p>
</td>
</tr>
<tr id="row144975403084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p649037662084828"><a name="p649037662084828"></a><a name="p649037662084828"></a><a href="codec.md#ga2d6eb231ca7766990cfa8c1841637245">CodecDeinit</a> ()</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2105676987084828"><a name="p2105676987084828"></a><a name="p2105676987084828"></a>int32_t </p>
<p id="p569541319084828"><a name="p569541319084828"></a><a name="p569541319084828"></a>Deinitializes the internal audio and video submodules of the codec. </p>
</td>
</tr>
<tr id="row1325922120084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1469175653084828"><a name="p1469175653084828"></a><a name="p1469175653084828"></a><a href="codec.md#gaf0bb69d2f8c5ad0fec6959b353ee1acd">CodecEnumerateCapbility</a> (uint32_t <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, <a href="codec.md#ga1876710b1f2fe1d80e8b9de9ff28e0e3">CodecCapbility</a> *cap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1402286556084828"><a name="p1402286556084828"></a><a name="p1402286556084828"></a>int32_t </p>
<p id="p635027781084828"><a name="p635027781084828"></a><a name="p635027781084828"></a>Obtains the capabilities of a specified media type based on an index. </p>
</td>
</tr>
<tr id="row1370421659084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p550278157084828"><a name="p550278157084828"></a><a name="p550278157084828"></a><a href="codec.md#ga1a6fbf6e84e01fdc1af59caa4203ce8e">CodecGetCapbility</a> (<a href="codec.md#ga1bee586eafa91dfb60f94ba40fc95faa">AvCodecMime</a> mime, <a href="codec.md#ga03b4b6ae5fb82af68d46aaea3d3e4d79">CodecType</a> type, uint32_t flags, <a href="codec.md#ga1876710b1f2fe1d80e8b9de9ff28e0e3">CodecCapbility</a> *cap)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p766284835084828"><a name="p766284835084828"></a><a name="p766284835084828"></a>int32_t </p>
<p id="p196418284084828"><a name="p196418284084828"></a><a name="p196418284084828"></a>Obtains the capabilities of a specified media type. </p>
</td>
</tr>
<tr id="row1452887326084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1014366028084828"><a name="p1014366028084828"></a><a name="p1014366028084828"></a><a href="codec.md#ga74aa0395a51f004390f7a92fb68faddd">CodecCreate</a> (const char *name, const <a href="param.md">Param</a> *attr, int len, <a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1300827907084828"><a name="p1300827907084828"></a><a name="p1300827907084828"></a>int32_t </p>
<p id="p794927053084828"><a name="p794927053084828"></a><a name="p794927053084828"></a>Creates a specific codec component and returns the component context through a handle. </p>
</td>
</tr>
<tr id="row1313569955084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p284329595084828"><a name="p284329595084828"></a><a name="p284329595084828"></a><a href="codec.md#ga1bc0592b05e4f687e2bef2ffb83102b8">CodecDestroy</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p288521609084828"><a name="p288521609084828"></a><a name="p288521609084828"></a>int32_t </p>
<p id="p1756755568084828"><a name="p1756755568084828"></a><a name="p1756755568084828"></a>Destroys a codec component. </p>
</td>
</tr>
<tr id="row1988714031084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p298009415084828"><a name="p298009415084828"></a><a name="p298009415084828"></a><a href="codec.md#ga36a994c5f9f4d104aad0c24b5e8cbd37">CodecSetPortMode</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, <a href="codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a> type, <a href="codec.md#gacc0fd55192fd9f663121b037b06f41e8">BufferMode</a> mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p671788526084828"><a name="p671788526084828"></a><a name="p671788526084828"></a>int32_t </p>
<p id="p1680293168084828"><a name="p1680293168084828"></a><a name="p1680293168084828"></a>Sets the input or output buffer mode. </p>
</td>
</tr>
<tr id="row2051453233084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1626249989084828"><a name="p1626249989084828"></a><a name="p1626249989084828"></a><a href="codec.md#gaa080cf23aa5f77b30f3b90a026d97cc0">CodecSetParameter</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, const <a href="param.md">Param</a> *params, int paramCnt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1899152405084828"><a name="p1899152405084828"></a><a name="p1899152405084828"></a>int32_t </p>
<p id="p1514364229084828"><a name="p1514364229084828"></a><a name="p1514364229084828"></a>Sets parameters required by a codec component. </p>
</td>
</tr>
<tr id="row1180071879084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p87782646084828"><a name="p87782646084828"></a><a name="p87782646084828"></a><a href="codec.md#ga1d812eac032e3e05cf5bf71b03e93f65">CodecGetParameter</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, <a href="param.md">Param</a> *params, int paramCnt)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1793508265084828"><a name="p1793508265084828"></a><a name="p1793508265084828"></a>int32_t </p>
<p id="p434449871084828"><a name="p434449871084828"></a><a name="p434449871084828"></a>Obtains parameters from a codec component. </p>
</td>
</tr>
<tr id="row1010047897084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1066596118084828"><a name="p1066596118084828"></a><a name="p1066596118084828"></a><a href="codec.md#ga38c1744b0b4be5817ef49556ae665d18">CodecStart</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p805826522084828"><a name="p805826522084828"></a><a name="p805826522084828"></a>int32_t </p>
<p id="p1967925096084828"><a name="p1967925096084828"></a><a name="p1967925096084828"></a>Starts a codec component. </p>
</td>
</tr>
<tr id="row1459719554084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1451408430084828"><a name="p1451408430084828"></a><a name="p1451408430084828"></a><a href="codec.md#ga8e7913c052c2e45e193fb0aab3f5c7fd">CodecStop</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1306291644084828"><a name="p1306291644084828"></a><a name="p1306291644084828"></a>int32_t </p>
<p id="p1423777299084828"><a name="p1423777299084828"></a><a name="p1423777299084828"></a>Stops a codec component. </p>
</td>
</tr>
<tr id="row1191045045084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1796631862084828"><a name="p1796631862084828"></a><a name="p1796631862084828"></a><a href="codec.md#gaa6ed6c24e29f8fdfbbb0a3d562260a6a">CodecFlush</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, <a href="codec.md#ga8ef30fa9c08e08c8706653571f9f5b81">DirectionType</a> directType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p475857428084828"><a name="p475857428084828"></a><a name="p475857428084828"></a>int32_t </p>
<p id="p273063746084828"><a name="p273063746084828"></a><a name="p273063746084828"></a>Clears the cache when the codec component is the running state. </p>
</td>
</tr>
<tr id="row1432737053084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p221226115084828"><a name="p221226115084828"></a><a name="p221226115084828"></a><a href="codec.md#ga0daece8dbf22da84f926761c994819bc">CodecQueueInput</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, const <a href="inputinfo.md">InputInfo</a> *inputData, uint32_t timeoutMs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1046593519084828"><a name="p1046593519084828"></a><a name="p1046593519084828"></a>int32_t </p>
<p id="p1637101078084828"><a name="p1637101078084828"></a><a name="p1637101078084828"></a>Queues input data. </p>
</td>
</tr>
<tr id="row95602801084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p995660483084828"><a name="p995660483084828"></a><a name="p995660483084828"></a><a href="codec.md#ga91d7e1566c90d7cb9ac846eecad0024f">CodecDequeInput</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, uint32_t timeoutMs, <a href="inputinfo.md">InputInfo</a> *inputData)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2114703178084828"><a name="p2114703178084828"></a><a name="p2114703178084828"></a>int32_t </p>
<p id="p847755638084828"><a name="p847755638084828"></a><a name="p847755638084828"></a>Dequeues input data that has been used. </p>
</td>
</tr>
<tr id="row1230425643084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2020508747084828"><a name="p2020508747084828"></a><a name="p2020508747084828"></a><a href="codec.md#gac98f3505082c3cb2413d9e95eef9c804">CodecQueueOutput</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, <a href="outputinfo.md">OutputInfo</a> *outInfo, uint32_t timeoutMs, int releaseFenceFd)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1985980182084828"><a name="p1985980182084828"></a><a name="p1985980182084828"></a>int32_t </p>
<p id="p1094765293084828"><a name="p1094765293084828"></a><a name="p1094765293084828"></a>Queues output data. </p>
</td>
</tr>
<tr id="row2041813342084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1870505306084828"><a name="p1870505306084828"></a><a name="p1870505306084828"></a><a href="codec.md#gab575752467517eb8e6766773c1e3fb23">CodecDequeueOutput</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, uint32_t timeoutMs, int *acquireFd, <a href="outputinfo.md">OutputInfo</a> *outInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p994733508084828"><a name="p994733508084828"></a><a name="p994733508084828"></a>int32_t </p>
<p id="p968528719084828"><a name="p968528719084828"></a><a name="p968528719084828"></a>Dequeues output data. </p>
</td>
</tr>
<tr id="row1673579581084828"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1848732106084828"><a name="p1848732106084828"></a><a name="p1848732106084828"></a><a href="codec.md#ga28ec6149d05765ee75f4836e0b092406">CodecSetCallback</a> (<a href="codec.md#ga9381a619f36ac8d5d7f467d2f0404183">CODEC_HANDLETYPE</a> handle, const <a href="codeccallback.md">CodecCallback</a> *cb, <a href="codec.md#ga58d2f4a8d12daa1dcf4eb297f3ebaabc">UINTPTR</a> instance)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1556302023084828"><a name="p1556302023084828"></a><a name="p1556302023084828"></a>int32_t </p>
<p id="p357673905084828"><a name="p357673905084828"></a><a name="p357673905084828"></a>Sets the callback function. </p>
</td>
</tr>
</tbody>
</table>

