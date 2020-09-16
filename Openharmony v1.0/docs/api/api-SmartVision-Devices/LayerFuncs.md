# LayerFuncs<a name="ZH-CN_TOPIC_0000001055678100"></a>

## **Overview**<a name="section1050788151093531"></a>

**Related Modules:**

[Display](Display.md)

**Description:**

Defines pointers to the layer driver functions. 

## **Summary**<a name="section884507617093531"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table897862247093531"></a>
<table><thead align="left"><tr id="row1801789020093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p580584264093531"><a name="p580584264093531"></a><a name="p580584264093531"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1447025685093531"><a name="p1447025685093531"></a><a name="p1447025685093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1290209619093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1761511737093531"><a name="p1761511737093531"></a><a name="p1761511737093531"></a><a href="LayerFuncs.md#a0641c3b48542646daa80386122bed46a">InitDisplay</a> )(uint32_t devId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p854108477093531"><a name="p854108477093531"></a><a name="p854108477093531"></a>int32_t(*&nbsp;</p>
<p id="p858279981093531"><a name="p858279981093531"></a><a name="p858279981093531"></a>Initializes a display device. </p>
</td>
</tr>
<tr id="row705927014093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1325594315093531"><a name="p1325594315093531"></a><a name="p1325594315093531"></a><a href="LayerFuncs.md#a8d7a715d7d2b4bd5ab0db92c2a1eec93">DeinitDisplay</a> )(uint32_t devId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p642152892093531"><a name="p642152892093531"></a><a name="p642152892093531"></a>int32_t(*&nbsp;</p>
<p id="p1941568498093531"><a name="p1941568498093531"></a><a name="p1941568498093531"></a>Deinitializes a display device. </p>
</td>
</tr>
<tr id="row1375052931093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1619603363093531"><a name="p1619603363093531"></a><a name="p1619603363093531"></a><a href="LayerFuncs.md#aba57e2b79df0e774727d0c07ef90e715">GetDisplayInfo</a> )(uint32_t devId, <a href="DisplayInfo.md">DisplayInfo</a> *dispInfo)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p969801017093531"><a name="p969801017093531"></a><a name="p969801017093531"></a>int32_t(*&nbsp;</p>
<p id="p571383769093531"><a name="p571383769093531"></a><a name="p571383769093531"></a>Obtains information about a display device. </p>
</td>
</tr>
<tr id="row657199072093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p529170825093531"><a name="p529170825093531"></a><a name="p529170825093531"></a><a href="LayerFuncs.md#a795f4e168d5b284a9c33f636c278207f">OpenLayer</a> )(uint32_t devId, const <a href="LayerInfo.md">LayerInfo</a> *layerInfo, uint32_t *layerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2115517563093531"><a name="p2115517563093531"></a><a name="p2115517563093531"></a>int32_t(*&nbsp;</p>
<p id="p1321274281093531"><a name="p1321274281093531"></a><a name="p1321274281093531"></a>Opens a layer on a specified display device. </p>
</td>
</tr>
<tr id="row484321565093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1003638687093531"><a name="p1003638687093531"></a><a name="p1003638687093531"></a><a href="LayerFuncs.md#a2e375f75209da329f131b914377e9616">CloseLayer</a> )(uint32_t devId, uint32_t layerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p308821775093531"><a name="p308821775093531"></a><a name="p308821775093531"></a>int32_t(*&nbsp;</p>
<p id="p1426803714093531"><a name="p1426803714093531"></a><a name="p1426803714093531"></a>Closes a layer that is no longer required on a specified display device. </p>
</td>
</tr>
<tr id="row1101309460093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1712191943093531"><a name="p1712191943093531"></a><a name="p1712191943093531"></a><a href="LayerFuncs.md#aaa5bf7f98e8dc47510a4f26fb38094b6">SetLayerVisible</a> )(uint32_t devId, uint32_t layerId, bool visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p363999925093531"><a name="p363999925093531"></a><a name="p363999925093531"></a>int32_t(*&nbsp;</p>
<p id="p709852316093531"><a name="p709852316093531"></a><a name="p709852316093531"></a>Sets whether a layer is visible. </p>
</td>
</tr>
<tr id="row944841608093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1689743827093531"><a name="p1689743827093531"></a><a name="p1689743827093531"></a><a href="LayerFuncs.md#a6bbff71bb4f17eb84a4db4857a0b0985">GetLayerVisibleState</a> )(uint32_t devId, uint32_t layerId, bool *visible)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p291167239093531"><a name="p291167239093531"></a><a name="p291167239093531"></a>int32_t(*&nbsp;</p>
<p id="p1074825475093531"><a name="p1074825475093531"></a><a name="p1074825475093531"></a>Checks whether a layer is visible. </p>
</td>
</tr>
<tr id="row57270837093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p790845491093531"><a name="p790845491093531"></a><a name="p790845491093531"></a><a href="LayerFuncs.md#ab58e66b0676b1baa1662c175d43bf219">SetLayerSize</a> )(uint32_t devId, uint32_t layerId, <a href="IRect.md">IRect</a> *rect)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1090797462093531"><a name="p1090797462093531"></a><a name="p1090797462093531"></a>int32_t(*&nbsp;</p>
<p id="p1773045931093531"><a name="p1773045931093531"></a><a name="p1773045931093531"></a>Sets the size of a layer. </p>
</td>
</tr>
<tr id="row1511842937093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p311479173093531"><a name="p311479173093531"></a><a name="p311479173093531"></a><a href="LayerFuncs.md#a56be84be25eba64497b2a842c1f68b26">GetLayerSize</a> )(uint32_t devId, uint32_t layerId, <a href="IRect.md">IRect</a> *rect)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1709282148093531"><a name="p1709282148093531"></a><a name="p1709282148093531"></a>int32_t(*&nbsp;</p>
<p id="p185929585093531"><a name="p185929585093531"></a><a name="p185929585093531"></a>Obtains the size of a layer. </p>
</td>
</tr>
<tr id="row1204712439093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p88960164093531"><a name="p88960164093531"></a><a name="p88960164093531"></a><a href="LayerFuncs.md#a4f925226529e27678df19423fa6f83ad">SetLayerCrop</a> )(uint32_t devId, uint32_t layerId, <a href="IRect.md">IRect</a> *rect)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2074544270093531"><a name="p2074544270093531"></a><a name="p2074544270093531"></a>int32_t(*&nbsp;</p>
<p id="p193713054093531"><a name="p193713054093531"></a><a name="p193713054093531"></a>Sets the rectangular area to crop for a layer. </p>
</td>
</tr>
<tr id="row4319023093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1777642484093531"><a name="p1777642484093531"></a><a name="p1777642484093531"></a><a href="LayerFuncs.md#aa3803c2a6395651d1538ffb62d29733d">SetLayerZorder</a> )(uint32_t devId, uint32_t layerId, uint32_t zorder)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p184143524093531"><a name="p184143524093531"></a><a name="p184143524093531"></a>int32_t(*&nbsp;</p>
<p id="p1181114921093531"><a name="p1181114921093531"></a><a name="p1181114921093531"></a>Sets the z-order for a layer. </p>
</td>
</tr>
<tr id="row1874075351093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p486334247093531"><a name="p486334247093531"></a><a name="p486334247093531"></a><a href="LayerFuncs.md#a5644645442e1d6943b55ce0a6a801b8c">GetLayerZorder</a> )(uint32_t devId, uint32_t layerId, uint32_t *zorder)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p271904733093531"><a name="p271904733093531"></a><a name="p271904733093531"></a>int32_t(*&nbsp;</p>
<p id="p1476215370093531"><a name="p1476215370093531"></a><a name="p1476215370093531"></a>Obtains the z-order of a layer. </p>
</td>
</tr>
<tr id="row1847792393093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p695525281093531"><a name="p695525281093531"></a><a name="p695525281093531"></a><a href="LayerFuncs.md#a456aa01ca3ffa81d2e49c0a9487f816f">SetLayerPreMulti</a> )(uint32_t devId, uint32_t layerId, bool preMul)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p759922950093531"><a name="p759922950093531"></a><a name="p759922950093531"></a>int32_t(*&nbsp;</p>
<p id="p267696715093531"><a name="p267696715093531"></a><a name="p267696715093531"></a>Sets layer premultiplication. </p>
</td>
</tr>
<tr id="row194655880093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1845156226093531"><a name="p1845156226093531"></a><a name="p1845156226093531"></a><a href="LayerFuncs.md#a4a0e26f8401da1232f03bb37502ff4bd">GetLayerPreMulti</a> )(uint32_t devId, uint32_t layerId, bool *preMul)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1003022766093531"><a name="p1003022766093531"></a><a name="p1003022766093531"></a>int32_t(*&nbsp;</p>
<p id="p927666764093531"><a name="p927666764093531"></a><a name="p927666764093531"></a>Obtains the premultiplication flag of a layer. </p>
</td>
</tr>
<tr id="row400547406093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p265279476093531"><a name="p265279476093531"></a><a name="p265279476093531"></a><a href="LayerFuncs.md#a20e554afa2f7b1015fd23ce240344b13">SetLayerAlpha</a> )(uint32_t devId, uint32_t layerid, <a href="LayerAlpha.md">LayerAlpha</a> *alpha)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1439542188093531"><a name="p1439542188093531"></a><a name="p1439542188093531"></a>int32_t(*&nbsp;</p>
<p id="p1019388064093531"><a name="p1019388064093531"></a><a name="p1019388064093531"></a>Sets the alpha value for a layer. </p>
</td>
</tr>
<tr id="row1294561651093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p721242077093531"><a name="p721242077093531"></a><a name="p721242077093531"></a><a href="LayerFuncs.md#acf1e01338eeb0fd957f53ed0d2551394">GetLayerAlpha</a> )(uint32_t devId, uint32_t layerId, <a href="LayerAlpha.md">LayerAlpha</a> *alpha)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1979044114093531"><a name="p1979044114093531"></a><a name="p1979044114093531"></a>int32_t(*&nbsp;</p>
<p id="p910903822093531"><a name="p910903822093531"></a><a name="p910903822093531"></a>Obtains the alpha value of a layer. </p>
</td>
</tr>
<tr id="row1184821856093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p601005063093531"><a name="p601005063093531"></a><a name="p601005063093531"></a><a href="LayerFuncs.md#a5701fe1e0e2414de577aa5329bd873c9">SetLayerColorKey</a> )(uint32_t devId, uint32_t layerId, bool enable, uint32_t key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p155517740093531"><a name="p155517740093531"></a><a name="p155517740093531"></a>int32_t(*&nbsp;</p>
<p id="p1736270720093531"><a name="p1736270720093531"></a><a name="p1736270720093531"></a>Sets the color key for a layer. </p>
</td>
</tr>
<tr id="row1888941624093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1748335140093531"><a name="p1748335140093531"></a><a name="p1748335140093531"></a><a href="LayerFuncs.md#aea882232b6279b8be82c45e889187b24">GetLayerColorKey</a> )(uint32_t devId, uint32_t layerId, bool *enable, uint32_t *key)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2140044781093531"><a name="p2140044781093531"></a><a name="p2140044781093531"></a>int32_t(*&nbsp;</p>
<p id="p927857568093531"><a name="p927857568093531"></a><a name="p927857568093531"></a>Obtains the color key of a layer. </p>
</td>
</tr>
<tr id="row1901687058093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1699717131093531"><a name="p1699717131093531"></a><a name="p1699717131093531"></a><a href="LayerFuncs.md#a3982c76e093852ef386fc372581be4af">SetLayerPalette</a> )(uint32_t devId, uint32_t layerId, uint32_t *palette, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p13040619093531"><a name="p13040619093531"></a><a name="p13040619093531"></a>int32_t(*&nbsp;</p>
<p id="p450376859093531"><a name="p450376859093531"></a><a name="p450376859093531"></a>Sets the palette for a layer. </p>
</td>
</tr>
<tr id="row1761515508093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p695796286093531"><a name="p695796286093531"></a><a name="p695796286093531"></a><a href="LayerFuncs.md#af713bc39e51dc8168c278e2f126bf4e3">GetLayerPalette</a> )(uint32_t devId, uint32_t layerId, uint32_t *palette, uint32_t len)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1420431936093531"><a name="p1420431936093531"></a><a name="p1420431936093531"></a>int32_t(*&nbsp;</p>
<p id="p329947031093531"><a name="p329947031093531"></a><a name="p329947031093531"></a>Obtains the palette of a layer. </p>
</td>
</tr>
<tr id="row1382141007093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2050664918093531"><a name="p2050664918093531"></a><a name="p2050664918093531"></a><a href="LayerFuncs.md#a707a6ae5144ee329110822dd8301cb22">SetTransformMode</a> )(uint32_t devId, uint32_t layerId, <a href="Display.md#gaa65f3b21a9a92ff022e435a7304126d2">TransformType</a> type)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p70591593093531"><a name="p70591593093531"></a><a name="p70591593093531"></a>int32_t(*&nbsp;</p>
<p id="p977437106093531"><a name="p977437106093531"></a><a name="p977437106093531"></a>Sets the transform mode for a layer. </p>
</td>
</tr>
<tr id="row977558620093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p295434907093531"><a name="p295434907093531"></a><a name="p295434907093531"></a><a href="LayerFuncs.md#a46c9750d8615dc874b66ac4b10796b24">SetLayerCompression</a> )(uint32_t devId, uint32_t layerId, int32_t compType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1158110644093531"><a name="p1158110644093531"></a><a name="p1158110644093531"></a>int32_t(*&nbsp;</p>
<p id="p1485653205093531"><a name="p1485653205093531"></a><a name="p1485653205093531"></a>Sets the compression feature for a layer. </p>
</td>
</tr>
<tr id="row290541066093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p138006922093531"><a name="p138006922093531"></a><a name="p138006922093531"></a><a href="LayerFuncs.md#ab0b5855ea4ee5228516303cba84907ce">GetLayerCompression</a> )(uint32_t devId, uint32_t layerId, int32_t *compType)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1246865172093531"><a name="p1246865172093531"></a><a name="p1246865172093531"></a>int32_t(*&nbsp;</p>
<p id="p2090539520093531"><a name="p2090539520093531"></a><a name="p2090539520093531"></a>Checks whether the compression feature is enabled for a layer. </p>
</td>
</tr>
<tr id="row1975661216093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p903415271093531"><a name="p903415271093531"></a><a name="p903415271093531"></a><a href="LayerFuncs.md#a7aa2a7bf4c0aed948c8617adec2d91b6">SetLayerDirtyRegion</a> )(uint32_t devId, uint32_t layerId, <a href="IRect.md">IRect</a> *region)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p66636054093531"><a name="p66636054093531"></a><a name="p66636054093531"></a>int32_t(*&nbsp;</p>
<p id="p1065423353093531"><a name="p1065423353093531"></a><a name="p1065423353093531"></a>Sets the flushing area for a layer. </p>
</td>
</tr>
<tr id="row1724532702093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p574167614093531"><a name="p574167614093531"></a><a name="p574167614093531"></a><a href="LayerFuncs.md#a40b406f6b4e6a812a36605041e0e81d6">GetLayerBuffer</a> )(uint32_t devId, uint32_t layerId, <a href="LayerBuffer.md">LayerBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2089235664093531"><a name="p2089235664093531"></a><a name="p2089235664093531"></a>int32_t(*&nbsp;</p>
<p id="p1211231736093531"><a name="p1211231736093531"></a><a name="p1211231736093531"></a>Obtains the buffer of a layer. </p>
</td>
</tr>
<tr id="row1347494713093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1849440551093531"><a name="p1849440551093531"></a><a name="p1849440551093531"></a><a href="LayerFuncs.md#abb480bf2b85e93841c49fdc9800bd1e7">Flush</a> )(uint32_t devId, uint32_t layerId, <a href="LayerBuffer.md">LayerBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p262609741093531"><a name="p262609741093531"></a><a name="p262609741093531"></a>int32_t(*&nbsp;</p>
<p id="p2038692562093531"><a name="p2038692562093531"></a><a name="p2038692562093531"></a>Flushes a layer. </p>
</td>
</tr>
<tr id="row1337367313093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2102945464093531"><a name="p2102945464093531"></a><a name="p2102945464093531"></a><a href="LayerFuncs.md#a62471eb83a24d0a84dabd53018666336">WaitForVBlank</a> )(uint32_t devId, uint32_t layerId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1248161901093531"><a name="p1248161901093531"></a><a name="p1248161901093531"></a>int32_t(*&nbsp;</p>
<p id="p1129923339093531"><a name="p1129923339093531"></a><a name="p1129923339093531"></a>Waits for the arrival of vertical blanking. </p>
</td>
</tr>
<tr id="row1961747558093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p468466593093531"><a name="p468466593093531"></a><a name="p468466593093531"></a><a href="LayerFuncs.md#a751377d6d1877cd9e878208b94339407">SnapShot</a> )(uint32_t devId, <a href="LayerBuffer.md">LayerBuffer</a> *buffer)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p527839475093531"><a name="p527839475093531"></a><a name="p527839475093531"></a>int32_t(*&nbsp;</p>
<p id="p294871108093531"><a name="p294871108093531"></a><a name="p294871108093531"></a>Implements the snapshot feature. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1957842618093531"></a>

## **Field Documentation**<a name="section219752633093531"></a>

## CloseLayer<a name="a2e375f75209da329f131b914377e9616"></a>

```
int32_t(* LayerFuncs::CloseLayer) (uint32_t devId, uint32_t layerId)
```

 **Description:**

Closes a layer that is no longer required on a specified display device. 

**Parameters:**

<a name="table1388587933093531"></a>
<table><thead align="left"><tr id="row1326945359093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p395676765093531"><a name="p395676765093531"></a><a name="p395676765093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2109815906093531"><a name="p2109815906093531"></a><a name="p2109815906093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row120617066093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row388381540093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[OpenLayer](LayerFuncs.md#a795f4e168d5b284a9c33f636c278207f) 

## DeinitDisplay<a name="a8d7a715d7d2b4bd5ab0db92c2a1eec93"></a>

```
int32_t(* LayerFuncs::DeinitDisplay) (uint32_t devId)
```

 **Description:**

Deinitializes a display device. 

**Parameters:**

<a name="table2050872451093531"></a>
<table><thead align="left"><tr id="row758924228093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1798225751093531"><a name="p1798225751093531"></a><a name="p1798225751093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p602934640093531"><a name="p602934640093531"></a><a name="p602934640093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row417296870093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[InitDisplay](LayerFuncs.md#a0641c3b48542646daa80386122bed46a) 

## Flush<a name="abb480bf2b85e93841c49fdc9800bd1e7"></a>

```
int32_t(* LayerFuncs::Flush) (uint32_t devId, uint32_t layerId, [LayerBuffer](LayerBuffer.md) *buffer)
```

 **Description:**

Flushes a layer. 

Display data in the buffer is flushed to a specified layer so that the image data is displayed on the screen.

**Parameters:**

<a name="table678214912093531"></a>
<table><thead align="left"><tr id="row675629429093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p54443304093531"><a name="p54443304093531"></a><a name="p54443304093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1361074167093531"><a name="p1361074167093531"></a><a name="p1361074167093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1108364237093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row194761284093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row873215645093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer in which the display data is to flush.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## GetDisplayInfo<a name="aba57e2b79df0e774727d0c07ef90e715"></a>

```
int32_t(* LayerFuncs::GetDisplayInfo) (uint32_t devId, [DisplayInfo](DisplayInfo.md) *dispInfo)
```

 **Description:**

Obtains information about a display device. 

**Parameters:**

<a name="table350393961093531"></a>
<table><thead align="left"><tr id="row1252037398093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1708419097093531"><a name="p1708419097093531"></a><a name="p1708419097093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p102499992093531"><a name="p102499992093531"></a><a name="p102499992093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1053371586093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row408036878093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dispInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the display device information obtained.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## GetLayerAlpha<a name="acf1e01338eeb0fd957f53ed0d2551394"></a>

```
int32_t(* LayerFuncs::GetLayerAlpha) (uint32_t devId, uint32_t layerId, [LayerAlpha](LayerAlpha.md) *alpha)
```

 **Description:**

Obtains the alpha value of a layer. 

**Parameters:**

<a name="table25418260093531"></a>
<table><thead align="left"><tr id="row1869068225093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1225363482093531"><a name="p1225363482093531"></a><a name="p1225363482093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1626018140093531"><a name="p1626018140093531"></a><a name="p1626018140093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1828275366093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row130095139093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row1321886392093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alpha</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained alpha value.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[SetLayerAlpha](LayerFuncs.md#a20e554afa2f7b1015fd23ce240344b13) 

## GetLayerBuffer<a name="a40b406f6b4e6a812a36605041e0e81d6"></a>

```
int32_t(* LayerFuncs::GetLayerBuffer) (uint32_t devId, uint32_t layerId, [LayerBuffer](LayerBuffer.md) *buffer)
```

 **Description:**

Obtains the buffer of a layer. 

After drawing a picture in the buffer, the application calls the  [Flush](LayerFuncs.md#abb480bf2b85e93841c49fdc9800bd1e7)  function to display the picture on the screen.

**Parameters:**

<a name="table1832265915093531"></a>
<table><thead align="left"><tr id="row1085262865093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p944703234093531"><a name="p944703234093531"></a><a name="p944703234093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p482414576093531"><a name="p482414576093531"></a><a name="p482414576093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1858301275093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row2006096958093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row1375174231093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained buffer.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[Flush](LayerFuncs.md#abb480bf2b85e93841c49fdc9800bd1e7) 

## GetLayerColorKey<a name="aea882232b6279b8be82c45e889187b24"></a>

```
int32_t(* LayerFuncs::GetLayerColorKey) (uint32_t devId, uint32_t layerId, bool *enable, uint32_t *key)
```

 **Description:**

Obtains the color key of a layer. 

**Parameters:**

<a name="table1454758102093531"></a>
<table><thead align="left"><tr id="row81899739093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p830941648093531"><a name="p830941648093531"></a><a name="p830941648093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2110619386093531"><a name="p2110619386093531"></a><a name="p2110619386093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row206914393093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row532574434093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row1828372537093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">enable</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the color key enable bit. </td>
</tr>
<tr id="row761109968093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the color key.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[SetLayerColorKey](LayerFuncs.md#a5701fe1e0e2414de577aa5329bd873c9) 

## GetLayerCompression<a name="ab0b5855ea4ee5228516303cba84907ce"></a>

```
int32_t(* LayerFuncs::GetLayerCompression) (uint32_t devId, uint32_t layerId, int32_t *compType)
```

 **Description:**

Checks whether the compression feature is enabled for a layer. 

**Parameters:**

<a name="table531700448093531"></a>
<table><thead align="left"><tr id="row1959725322093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1279781375093531"><a name="p1279781375093531"></a><a name="p1279781375093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p895211156093531"><a name="p895211156093531"></a><a name="p895211156093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row342222990093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row1022257881093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row1171134176093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">compType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the variable specifying whether the compression feature is enabled.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[SetLayerCompression](LayerFuncs.md#a46c9750d8615dc874b66ac4b10796b24) 

## GetLayerPalette<a name="af713bc39e51dc8168c278e2f126bf4e3"></a>

```
int32_t(* LayerFuncs::GetLayerPalette) (uint32_t devId, uint32_t layerId, uint32_t *palette, uint32_t len)
```

 **Description:**

Obtains the palette of a layer. 

**Parameters:**

<a name="table1242616570093531"></a>
<table><thead align="left"><tr id="row1576036959093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p899160420093531"><a name="p899160420093531"></a><a name="p899160420093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2039609593093531"><a name="p2039609593093531"></a><a name="p2039609593093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row865245955093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row1674406385093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row1626074369093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">palette</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained palette. </td>
</tr>
<tr id="row1010174164093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the palette.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[SetLayerPalette](LayerFuncs.md#a3982c76e093852ef386fc372581be4af) 

## GetLayerPreMulti<a name="a4a0e26f8401da1232f03bb37502ff4bd"></a>

```
int32_t(* LayerFuncs::GetLayerPreMulti) (uint32_t devId, uint32_t layerId, bool *preMul)
```

 **Description:**

Obtains the premultiplication flag of a layer. 

**Parameters:**

<a name="table1846833321093531"></a>
<table><thead align="left"><tr id="row1991316039093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1887410458093531"><a name="p1887410458093531"></a><a name="p1887410458093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p660237536093531"><a name="p660237536093531"></a><a name="p660237536093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1030127948093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row1770627252093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row1729116278093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">preMul</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained layer premultiplication flag.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[SetLayerPreMulti](LayerFuncs.md#a456aa01ca3ffa81d2e49c0a9487f816f) 

## GetLayerSize<a name="a56be84be25eba64497b2a842c1f68b26"></a>

```
int32_t(* LayerFuncs::GetLayerSize) (uint32_t devId, uint32_t layerId, [IRect](IRect.md) *rect)
```

 **Description:**

Obtains the size of a layer. 

**Parameters:**

<a name="table1122569136093531"></a>
<table><thead align="left"><tr id="row1179113461093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p929921090093531"><a name="p929921090093531"></a><a name="p929921090093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p509335603093531"><a name="p509335603093531"></a><a name="p509335603093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1056608761093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row1083453896093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row601771995093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rect</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained layer size.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[SetLayerSize](LayerFuncs.md#ab58e66b0676b1baa1662c175d43bf219) 

## GetLayerVisibleState<a name="a6bbff71bb4f17eb84a4db4857a0b0985"></a>

```
int32_t(* LayerFuncs::GetLayerVisibleState) (uint32_t devId, uint32_t layerId, bool *visible)
```

 **Description:**

Checks whether a layer is visible. 

**Parameters:**

<a name="table825927307093531"></a>
<table><thead align="left"><tr id="row179301628093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p61508176093531"><a name="p61508176093531"></a><a name="p61508176093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2078522371093531"><a name="p2078522371093531"></a><a name="p2078522371093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row924584418093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row892464969093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row421385068093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">visible</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained layer visibility. The value <strong id="b319192629093531"><a name="b319192629093531"></a><a name="b319192629093531"></a>true</strong> indicates that the layer is visible, and <strong id="b684068235093531"><a name="b684068235093531"></a><a name="b684068235093531"></a>false</strong> indicates that the layer is invisible.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[SetLayerVisible](LayerFuncs.md#aaa5bf7f98e8dc47510a4f26fb38094b6) 

## GetLayerZorder<a name="a5644645442e1d6943b55ce0a6a801b8c"></a>

```
int32_t(* LayerFuncs::GetLayerZorder) (uint32_t devId, uint32_t layerId, uint32_t *zorder)
```

 **Description:**

Obtains the z-order of a layer. 

**Parameters:**

<a name="table1915332005093531"></a>
<table><thead align="left"><tr id="row1637367783093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1556493325093531"><a name="p1556493325093531"></a><a name="p1556493325093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p319004314093531"><a name="p319004314093531"></a><a name="p319004314093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1710790864093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row310381938093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row105963335093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">zorder</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained z-order. The value is an integer ranging from 0 to 255. A larger z-order value indicates a higher layer.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[SetLayerZorder](LayerFuncs.md#aa3803c2a6395651d1538ffb62d29733d) 

## InitDisplay<a name="a0641c3b48542646daa80386122bed46a"></a>

```
int32_t(* LayerFuncs::InitDisplay) (uint32_t devId)
```

 **Description:**

Initializes a display device. 

**Parameters:**

<a name="table504573639093531"></a>
<table><thead align="left"><tr id="row17384343093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p832253932093531"><a name="p832253932093531"></a><a name="p832253932093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2140304851093531"><a name="p2140304851093531"></a><a name="p2140304851093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row734618597093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[DeinitDisplay](LayerFuncs.md#a8d7a715d7d2b4bd5ab0db92c2a1eec93) 

## OpenLayer<a name="a795f4e168d5b284a9c33f636c278207f"></a>

```
int32_t(* LayerFuncs::OpenLayer) (uint32_t devId, const [LayerInfo](LayerInfo.md) *layerInfo, uint32_t *layerId)
```

 **Description:**

Opens a layer on a specified display device. 

Before using a layer on the GUI, you must open the layer based on the layer information. After the layer is opened, you can obtain the layer ID and then use other functions based on the layer ID.

**Parameters:**

<a name="table256384849093531"></a>
<table><thead align="left"><tr id="row106611282093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p324761645093531"><a name="p324761645093531"></a><a name="p324761645093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p200308706093531"><a name="p200308706093531"></a><a name="p200308706093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1405462089093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row2584690093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerInfo</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the layer information passed to open a layer, including the layer type, layer size, and pixel format. </td>
</tr>
<tr id="row139559933093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the layer ID, which identifies a unique layer. The layer ID is returned to the GUI after the layer is successfully opened.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[CloseLayer](LayerFuncs.md#a2e375f75209da329f131b914377e9616) 

## SetLayerAlpha<a name="a20e554afa2f7b1015fd23ce240344b13"></a>

```
int32_t(* LayerFuncs::SetLayerAlpha) (uint32_t devId, uint32_t layerid, [LayerAlpha](LayerAlpha.md) *alpha)
```

 **Description:**

Sets the alpha value for a layer. 

**Parameters:**

<a name="table1634544080093531"></a>
<table><thead align="left"><tr id="row1100759469093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1196420401093531"><a name="p1196420401093531"></a><a name="p1196420401093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1674907026093531"><a name="p1674907026093531"></a><a name="p1674907026093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1833544359093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row1757367915093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row2025273889093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">alpha</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the alpha value to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[GetLayerAlpha](LayerFuncs.md#acf1e01338eeb0fd957f53ed0d2551394) 

## SetLayerColorKey<a name="a5701fe1e0e2414de577aa5329bd873c9"></a>

```
int32_t(* LayerFuncs::SetLayerColorKey) (uint32_t devId, uint32_t layerId, bool enable, uint32_t key)
```

 **Description:**

Sets the color key for a layer. 

The color key is used during layer overlay.

**Parameters:**

<a name="table484300340093531"></a>
<table><thead align="left"><tr id="row988694115093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2041875825093531"><a name="p2041875825093531"></a><a name="p2041875825093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p175497064093531"><a name="p175497064093531"></a><a name="p175497064093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row860406182093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row162588810093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row508898727093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">enable</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specify whether to enable the color key. </td>
</tr>
<tr id="row1728112134093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">key</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the color key.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[GetLayerColorKey](LayerFuncs.md#aea882232b6279b8be82c45e889187b24) 

## SetLayerCompression<a name="a46c9750d8615dc874b66ac4b10796b24"></a>

```
int32_t(* LayerFuncs::SetLayerCompression) (uint32_t devId, uint32_t layerId, int32_t compType)
```

 **Description:**

Sets the compression feature for a layer. 

In specific scenarios, images need to be compressed. You can set whether to enable layer compression.

**Parameters:**

<a name="table563576349093531"></a>
<table><thead align="left"><tr id="row1529493241093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1406223806093531"><a name="p1406223806093531"></a><a name="p1406223806093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1821647985093531"><a name="p1821647985093531"></a><a name="p1821647985093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row69655650093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row864443729093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row632304956093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">compType</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether to enable the compression feature. The value <strong id="b1830491168093531"><a name="b1830491168093531"></a><a name="b1830491168093531"></a>true&gt;/b&gt; means to enable compression, and <strong id="b308358235093531"><a name="b308358235093531"></a><a name="b308358235093531"></a>false&gt; means the opposite.</strong></strong></td>
</tr>
</tbody>
</table>

**Returns:**

**** Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. ****

**See also:**

**** [GetLayerCompression](LayerFuncs.md#ab0b5855ea4ee5228516303cba84907ce) **** 

## SetLayerCrop<a name="a4f925226529e27678df19423fa6f83ad"></a>

```
int32_t(* LayerFuncs::SetLayerCrop) (uint32_t devId, uint32_t layerId, [IRect](IRect.md) *rect)
```

 **Description:**

Sets the rectangular area to crop for a layer. 

**Parameters:**

<a name="table202040679093531"></a>
<table><thead align="left"><tr id="row145522317093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p417430236093531"><a name="p417430236093531"></a><a name="p417430236093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1251325215093531"><a name="p1251325215093531"></a><a name="p1251325215093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row672930651093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row1617062420093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row879691193093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rect</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the rectangular area to crop.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## SetLayerDirtyRegion<a name="a7aa2a7bf4c0aed948c8617adec2d91b6"></a>

```
int32_t(* LayerFuncs::SetLayerDirtyRegion) (uint32_t devId, uint32_t layerId, [IRect](IRect.md) *region)
```

 **Description:**

Sets the flushing area for a layer. 

After the GUI draws an image, you must set the layer flushing area before calling the  [Flush](LayerFuncs.md#abb480bf2b85e93841c49fdc9800bd1e7)  function to flush the screen.

**Parameters:**

<a name="table851028772093531"></a>
<table><thead align="left"><tr id="row2060333437093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2054333734093531"><a name="p2054333734093531"></a><a name="p2054333734093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1904335617093531"><a name="p1904335617093531"></a><a name="p1904335617093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1636357435093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row290451342093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row7325443093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">region</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the flushing area to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## SetLayerPalette<a name="a3982c76e093852ef386fc372581be4af"></a>

```
int32_t(* LayerFuncs::SetLayerPalette) (uint32_t devId, uint32_t layerId, uint32_t *palette, uint32_t len)
```

 **Description:**

Sets the palette for a layer. 

**Parameters:**

<a name="table1282389703093531"></a>
<table><thead align="left"><tr id="row1126292470093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p938597574093531"><a name="p938597574093531"></a><a name="p938597574093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p221293482093531"><a name="p221293482093531"></a><a name="p221293482093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1704166952093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row653753729093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row1400954845093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">palette</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the palette to set. </td>
</tr>
<tr id="row1705217419093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the palette.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[GetLayerPalette](LayerFuncs.md#af713bc39e51dc8168c278e2f126bf4e3) 

## SetLayerPreMulti<a name="a456aa01ca3ffa81d2e49c0a9487f816f"></a>

```
int32_t(* LayerFuncs::SetLayerPreMulti) (uint32_t devId, uint32_t layerId, bool preMul)
```

 **Description:**

Sets layer premultiplication. 

**Parameters:**

<a name="table1394885929093531"></a>
<table><thead align="left"><tr id="row2008335903093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2020796955093531"><a name="p2020796955093531"></a><a name="p2020796955093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p36368346093531"><a name="p36368346093531"></a><a name="p36368346093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row293165169093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row1232136311093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row55797100093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">preMul</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Specifies whether to enable layer premultiplication. The value <strong id="b1847713051093531"><a name="b1847713051093531"></a><a name="b1847713051093531"></a>1</strong> means to enable layer premultiplication, and <strong id="b1889594482093531"><a name="b1889594482093531"></a><a name="b1889594482093531"></a>0</strong> means the opposite.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[GetLayerPreMulti](LayerFuncs.md#a4a0e26f8401da1232f03bb37502ff4bd) 

## SetLayerSize<a name="ab58e66b0676b1baa1662c175d43bf219"></a>

```
int32_t(* LayerFuncs::SetLayerSize) (uint32_t devId, uint32_t layerId, [IRect](IRect.md) *rect)
```

 **Description:**

Sets the size of a layer. 

**Parameters:**

<a name="table278860076093531"></a>
<table><thead align="left"><tr id="row480762880093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1315234625093531"><a name="p1315234625093531"></a><a name="p1315234625093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p806382432093531"><a name="p806382432093531"></a><a name="p806382432093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1469557999093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row396094898093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row1004138495093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">rect</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the layer size to set, in pixels.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[GetLayerSize](LayerFuncs.md#a56be84be25eba64497b2a842c1f68b26) 

## SetLayerVisible<a name="aaa5bf7f98e8dc47510a4f26fb38094b6"></a>

```
int32_t(* LayerFuncs::SetLayerVisible) (uint32_t devId, uint32_t layerId, bool visible)
```

 **Description:**

Sets whether a layer is visible. 

A visible layer is displayed on the screen, whereas an invisible layer is not displayed on the screen.

**Parameters:**

<a name="table200615585093531"></a>
<table><thead align="left"><tr id="row1820877154093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p447177618093531"><a name="p447177618093531"></a><a name="p447177618093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p603092946093531"><a name="p603092946093531"></a><a name="p603092946093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1255658259093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row2005245510093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row777897011093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">visible</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the visibility to set for the layer. The value <strong id="b359302402093531"><a name="b359302402093531"></a><a name="b359302402093531"></a>true</strong> means to set the layer to be visible, and <strong id="b665747200093531"><a name="b665747200093531"></a><a name="b665747200093531"></a>false</strong> means the opposite.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[GetLayerVisibleState](LayerFuncs.md#a6bbff71bb4f17eb84a4db4857a0b0985) 

## SetLayerZorder<a name="aa3803c2a6395651d1538ffb62d29733d"></a>

```
int32_t(* LayerFuncs::SetLayerZorder) (uint32_t devId, uint32_t layerId, uint32_t zorder)
```

 **Description:**

Sets the z-order for a layer. 

A larger z-order value indicates a higher layer.

**Parameters:**

<a name="table2092383133093531"></a>
<table><thead align="left"><tr id="row2131634649093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1946247641093531"><a name="p1946247641093531"></a><a name="p1946247641093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p725176743093531"><a name="p725176743093531"></a><a name="p725176743093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row792333034093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row1252891266093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row606847427093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">zorder</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the z-order to set. The value is an integer ranging from 0 to 255.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 

**See also:**

[GetLayerZorder](LayerFuncs.md#a5644645442e1d6943b55ce0a6a801b8c) 

## SetTransformMode<a name="a707a6ae5144ee329110822dd8301cb22"></a>

```
int32_t(* LayerFuncs::SetTransformMode) (uint32_t devId, uint32_t layerId, [TransformType](Display.md#gaa65f3b21a9a92ff022e435a7304126d2) type)
```

 **Description:**

Sets the transform mode for a layer. 

Using this function, you can rotate, scale, and move the layer.

**Parameters:**

<a name="table396527547093531"></a>
<table><thead align="left"><tr id="row1784814313093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p949541882093531"><a name="p949541882093531"></a><a name="p949541882093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1601894993093531"><a name="p1601894993093531"></a><a name="p1601894993093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row619059072093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row134464179093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row317716929093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">type</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the transformation mode to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## SnapShot<a name="a751377d6d1877cd9e878208b94339407"></a>

```
int32_t(* LayerFuncs::SnapShot) (uint32_t devId, [LayerBuffer](LayerBuffer.md) *buffer)
```

 **Description:**

Implements the snapshot feature. 

This function saves the screenshot of image data on the display device to the buffer for debugging or as requested by applications.

**Parameters:**

<a name="table1069192154093531"></a>
<table><thead align="left"><tr id="row1618470585093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p818370175093531"><a name="p818370175093531"></a><a name="p818370175093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1883261800093531"><a name="p1883261800093531"></a><a name="p1883261800093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1315996068093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row823216927093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">buffer</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for saving screenshots.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



## WaitForVBlank<a name="a62471eb83a24d0a84dabd53018666336"></a>

```
int32_t(* LayerFuncs::WaitForVBlank) (uint32_t devId, uint32_t layerId)
```

 **Description:**

Waits for the arrival of vertical blanking. 

This function blocks the process until vertical blanking arrives, implementing the synchronization between software and hardware.

**Parameters:**

<a name="table950159958093531"></a>
<table><thead align="left"><tr id="row533202272093531"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1570369132093531"><a name="p1570369132093531"></a><a name="p1570369132093531"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p6749341093531"><a name="p6749341093531"></a><a name="p6749341093531"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row712612358093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">devId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ID of a display device. The value ranges from 0 to 4, where 0 indicates the first display device and 4 indicates the last display device. </td>
</tr>
<tr id="row1440376428093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">layerId</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the layer ID, which identifies a unique layer. You can perform operations on the layer with the specified layer ID. </td>
</tr>
<tr id="row964608140093531"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">timeOut</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the maximum duration that the process waits for the arrival of vertical blanking.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns an error code defined in  [DispErrCode](Display.md#ga12a925dadef7573cd74d63d06824f9b0)  otherwise. 



