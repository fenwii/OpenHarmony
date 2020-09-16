# DeviceResourceIface<a name="EN-US_TOPIC_0000001054918151"></a>

## **Overview**<a name="section394612064084835"></a>

**Related Modules:**

[DriverConfig](driverconfig.md)

**Description:**

Provides functions for obtaining information about the device resource configuration tree. 

This structure provides functions for obtaining information about the device resource configuration tree, including the root node, the  **unit**  attribute data, and the  **String**  attribute data.

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section598301610084835"></a>

## Data Fields<a name="pub-attribs"></a>

<a name="table1799520772084835"></a>
<table><thead align="left"><tr id="row755615975084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1194023675084835"><a name="p1194023675084835"></a><a name="p1194023675084835"></a>Variable Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p910269254084835"><a name="p910269254084835"></a><a name="p910269254084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row629394692084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p867245585084835"><a name="p867245585084835"></a><a name="p867245585084835"></a><a href="deviceresourceiface.md#adc489c2c907ebf9a098c91ba110a2c37">GetRootNode</a> )(void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p8380935084835"><a name="p8380935084835"></a><a name="p8380935084835"></a>const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *(* </p>
<p id="p1505020482084835"><a name="p1505020482084835"></a><a name="p1505020482084835"></a>Obtains the root node of the configuration tree. </p>
</td>
</tr>
<tr id="row1960870120084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p161896771084835"><a name="p161896771084835"></a><a name="p161896771084835"></a><a href="deviceresourceiface.md#a0a3446a50f3644a29cf812af0c915f8a">GetBool</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417469728084835"><a name="p1417469728084835"></a><a name="p1417469728084835"></a>bool(* </p>
<p id="p330241478084835"><a name="p330241478084835"></a><a name="p330241478084835"></a>Obtains the value of a <strong id="b165326080084835"><a name="b165326080084835"></a><a name="b165326080084835"></a>BOOL</strong> attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row746907264084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2038935674084835"><a name="p2038935674084835"></a><a name="p2038935674084835"></a><a href="deviceresourceiface.md#a5610a62186ad18320dadcad7077fb3bb">GetUint8</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint8_t *value, uint8_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p881851511084835"><a name="p881851511084835"></a><a name="p881851511084835"></a>int32_t(* </p>
<p id="p208475129084835"><a name="p208475129084835"></a><a name="p208475129084835"></a>Obtains the value of a <strong id="b125895658084835"><a name="b125895658084835"></a><a name="b125895658084835"></a>Uint8</strong> attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row1917048932084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1918868983084835"><a name="p1918868983084835"></a><a name="p1918868983084835"></a><a href="deviceresourceiface.md#a0973933ace2447ec38a82e7995e2c5af">GetUint8ArrayElem</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint32_t <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, uint8_t *value, uint8_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p892464790084835"><a name="p892464790084835"></a><a name="p892464790084835"></a>int32_t(* </p>
<p id="p136754967084835"><a name="p136754967084835"></a><a name="p136754967084835"></a>Obtains the value of a <strong id="b1639352015084835"><a name="b1639352015084835"></a><a name="b1639352015084835"></a>Unit8</strong> array attribute numbered <strong id="b1513374962084835"><a name="b1513374962084835"></a><a name="b1513374962084835"></a>index</strong> of a configuration tree node. </p>
</td>
</tr>
<tr id="row773540320084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1343972679084835"><a name="p1343972679084835"></a><a name="p1343972679084835"></a><a href="deviceresourceiface.md#a067d741f2c3938ca08be2282e741b0a4">GetUint8Array</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint8_t *value, uint32_t len, uint8_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p644396659084835"><a name="p644396659084835"></a><a name="p644396659084835"></a>int32_t(* </p>
<p id="p1555551375084835"><a name="p1555551375084835"></a><a name="p1555551375084835"></a>Obtains the values of a <strong id="b1990166919084835"><a name="b1990166919084835"></a><a name="b1990166919084835"></a>Uint8</strong> array attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row549861067084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p682233103084835"><a name="p682233103084835"></a><a name="p682233103084835"></a><a href="deviceresourceiface.md#a1d3191febf1c9a0731a1614295a1529b">GetUint16</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint16_t *value, uint16_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1223141713084835"><a name="p1223141713084835"></a><a name="p1223141713084835"></a>int32_t(* </p>
<p id="p1356491091084835"><a name="p1356491091084835"></a><a name="p1356491091084835"></a>Obtains the value of a <strong id="b1802940492084835"><a name="b1802940492084835"></a><a name="b1802940492084835"></a>Uint16</strong> attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row612112674084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1009920697084835"><a name="p1009920697084835"></a><a name="p1009920697084835"></a><a href="deviceresourceiface.md#a27abcf7cdca0b25b6e620b75590e0a2d">GetUint16ArrayElem</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint32_t <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, uint16_t *value, uint16_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p334216972084835"><a name="p334216972084835"></a><a name="p334216972084835"></a>int32_t(* </p>
<p id="p178942421084835"><a name="p178942421084835"></a><a name="p178942421084835"></a>Obtains the value of a <strong id="b1961742124084835"><a name="b1961742124084835"></a><a name="b1961742124084835"></a>Uint16</strong> array attribute numbered <strong id="b331555663084835"><a name="b331555663084835"></a><a name="b331555663084835"></a>index</strong> of a configuration tree node. </p>
</td>
</tr>
<tr id="row1067381688084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1412748024084835"><a name="p1412748024084835"></a><a name="p1412748024084835"></a><a href="deviceresourceiface.md#a54977ca0fd60515bad5e33adf830fc64">GetUint16Array</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint16_t *value, uint32_t len, uint16_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p715179816084835"><a name="p715179816084835"></a><a name="p715179816084835"></a>int32_t(* </p>
<p id="p1519823336084835"><a name="p1519823336084835"></a><a name="p1519823336084835"></a>Obtains the values of a <strong id="b204479249084835"><a name="b204479249084835"></a><a name="b204479249084835"></a>Uint16</strong> array attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row615011474084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p459338102084835"><a name="p459338102084835"></a><a name="p459338102084835"></a><a href="deviceresourceiface.md#a87cf305ff9cabdbeb5011e6c04106b9e">GetUint32</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint32_t *value, uint32_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1410592469084835"><a name="p1410592469084835"></a><a name="p1410592469084835"></a>int32_t(* </p>
<p id="p561733025084835"><a name="p561733025084835"></a><a name="p561733025084835"></a>Obtains the value of a <strong id="b574486530084835"><a name="b574486530084835"></a><a name="b574486530084835"></a>Uint32</strong> attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row1067769874084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p123643724084835"><a name="p123643724084835"></a><a name="p123643724084835"></a><a href="deviceresourceiface.md#a942b67fcd814a37d92e33f3de33c2ff5">GetUint32ArrayElem</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint32_t <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, uint32_t *value, uint32_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1276332013084835"><a name="p1276332013084835"></a><a name="p1276332013084835"></a>int32_t(* </p>
<p id="p246656348084835"><a name="p246656348084835"></a><a name="p246656348084835"></a>Obtains the value of a <strong id="b477090819084835"><a name="b477090819084835"></a><a name="b477090819084835"></a>Uint32</strong> array attribute numbered <strong id="b435099388084835"><a name="b435099388084835"></a><a name="b435099388084835"></a>index</strong> of a configuration tree node. </p>
</td>
</tr>
<tr id="row1006743188084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p916560081084835"><a name="p916560081084835"></a><a name="p916560081084835"></a><a href="deviceresourceiface.md#a2ed5d24a45946e270b4416c400839966">GetUint32Array</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint32_t *value, uint32_t len, uint32_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1246464079084835"><a name="p1246464079084835"></a><a name="p1246464079084835"></a>int32_t(* </p>
<p id="p572372263084835"><a name="p572372263084835"></a><a name="p572372263084835"></a>Obtains the values of a <strong id="b287558234084835"><a name="b287558234084835"></a><a name="b287558234084835"></a>Uint32</strong> array attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row1292949983084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1830374893084835"><a name="p1830374893084835"></a><a name="p1830374893084835"></a><a href="deviceresourceiface.md#a3c364db9381da16449bb96d6be86aed8">GetUint64</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint64_t *value, uint64_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1182709153084835"><a name="p1182709153084835"></a><a name="p1182709153084835"></a>int32_t(* </p>
<p id="p1740832828084835"><a name="p1740832828084835"></a><a name="p1740832828084835"></a>Obtains the value of a <strong id="b1238493083084835"><a name="b1238493083084835"></a><a name="b1238493083084835"></a>Uint64</strong> attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row199195480084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1359143994084835"><a name="p1359143994084835"></a><a name="p1359143994084835"></a><a href="deviceresourceiface.md#aac32428eb3762de48514bd14348fd230">GetUint64ArrayElem</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint32_t <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, uint64_t *value, uint64_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p249842612084835"><a name="p249842612084835"></a><a name="p249842612084835"></a>int32_t(* </p>
<p id="p1659233842084835"><a name="p1659233842084835"></a><a name="p1659233842084835"></a>Obtains the value of a <strong id="b234837146084835"><a name="b234837146084835"></a><a name="b234837146084835"></a>Uint64</strong> array attribute numbered <strong id="b1986662687084835"><a name="b1986662687084835"></a><a name="b1986662687084835"></a>index</strong> of a configuration tree node. </p>
</td>
</tr>
<tr id="row17265912084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p271850426084835"><a name="p271850426084835"></a><a name="p271850426084835"></a><a href="deviceresourceiface.md#ab378caa47c5b01c31ca602d4eaa3046f">GetUint64Array</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint64_t *value, uint32_t len, uint64_t def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p244158015084835"><a name="p244158015084835"></a><a name="p244158015084835"></a>int32_t(* </p>
<p id="p1897299291084835"><a name="p1897299291084835"></a><a name="p1897299291084835"></a>Obtains the values of a <strong id="b886677175084835"><a name="b886677175084835"></a><a name="b886677175084835"></a>Uint64</strong> array attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row1508900724084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p490228660084835"><a name="p490228660084835"></a><a name="p490228660084835"></a><a href="deviceresourceiface.md#a1989a47b8d61401e57ee523e01bc25ee">GetString</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, const char **value, const char *def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p695264865084835"><a name="p695264865084835"></a><a name="p695264865084835"></a>int32_t(* </p>
<p id="p701443913084835"><a name="p701443913084835"></a><a name="p701443913084835"></a>Obtains the value of a <strong id="b1133031075084835"><a name="b1133031075084835"></a><a name="b1133031075084835"></a>String</strong> attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row1516983187084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1207208842084835"><a name="p1207208842084835"></a><a name="p1207208842084835"></a><a href="deviceresourceiface.md#a787eb71963c16c96bca913729078dd9d">GetStringArrayElem</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName, uint32_t <a href="utils.md#ga1d3748ca570dcb09a2fb28e8015107dd">index</a>, const char **value, const char *def)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1293371748084835"><a name="p1293371748084835"></a><a name="p1293371748084835"></a>int32_t(* </p>
<p id="p967022428084835"><a name="p967022428084835"></a><a name="p967022428084835"></a>Obtains the value of a <strong id="b473207834084835"><a name="b473207834084835"></a><a name="b473207834084835"></a>String</strong> array attribute numbered <strong id="b1591669042084835"><a name="b1591669042084835"></a><a name="b1591669042084835"></a>index</strong> of a configuration tree node. </p>
</td>
</tr>
<tr id="row538225857084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2126133896084835"><a name="p2126133896084835"></a><a name="p2126133896084835"></a><a href="deviceresourceiface.md#a0fafd4d32592ce2fbe951807995c5ab3">GetElemNum</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p686145140084835"><a name="p686145140084835"></a><a name="p686145140084835"></a>int32_t(* </p>
<p id="p1343534058084835"><a name="p1343534058084835"></a><a name="p1343534058084835"></a>Obtains the number of values for an array attribute of a configuration tree node. </p>
</td>
</tr>
<tr id="row404039076084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2088058821084835"><a name="p2088058821084835"></a><a name="p2088058821084835"></a><a href="deviceresourceiface.md#a8d7c819ee3d00ded8eef01b0594f3571">GetNodeByMatchAttr</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrValue)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1047746854084835"><a name="p1047746854084835"></a><a name="p1047746854084835"></a>const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *(* </p>
<p id="p1148494140084835"><a name="p1148494140084835"></a><a name="p1148494140084835"></a>Obtains a specified child node of the current tree node based on the value of a specific reserved attribute (for example, the reserved attribute of the HCS is <strong id="b412100718084835"><a name="b412100718084835"></a><a name="b412100718084835"></a>match_attr</strong>). </p>
</td>
</tr>
<tr id="row2060649073084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p87945612084835"><a name="p87945612084835"></a><a name="p87945612084835"></a><a href="deviceresourceiface.md#a70d5844ef0f0c35b9eb3bbba177bccc0">GetChildNode</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *nodeName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p127464833084835"><a name="p127464833084835"></a><a name="p127464833084835"></a>const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *(* </p>
<p id="p1465773996084835"><a name="p1465773996084835"></a><a name="p1465773996084835"></a>Obtains the child node with a specified node name from a parent node. </p>
</td>
</tr>
<tr id="row1988000586084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p795212697084835"><a name="p795212697084835"></a><a name="p795212697084835"></a><a href="deviceresourceiface.md#a8066548056633048c008e7a29aac8c8f">GetNodeByRefAttr</a> )(const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *node, const char *attrName)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2037809503084835"><a name="p2037809503084835"></a><a name="p2037809503084835"></a>const struct <a href="deviceresourcenode.md">DeviceResourceNode</a> *(* </p>
<p id="p714666670084835"><a name="p714666670084835"></a><a name="p714666670084835"></a>Obtains the node that is specified by a node-type attribute of a configuration tree node. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section905455736084835"></a>

## **Field Documentation**<a name="section109081634084835"></a>

## GetBool<a name="a0a3446a50f3644a29cf812af0c915f8a"></a>

```
bool(* DeviceResourceIface::GetBool) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName)
```

 **Description:**

Obtains the value of a  **BOOL**  attribute of a configuration tree node. 

**Parameters:**

<a name="table1693631423084835"></a>
<table><thead align="left"><tr id="row1354038841084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p61376513084835"><a name="p61376513084835"></a><a name="p61376513084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p747319636084835"><a name="p747319636084835"></a><a name="p747319636084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row257295219084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row776033448084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the attribute.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the value of the  **BOOL**  attribute if the operation is successful; returns  **false**  if  **node**  and  **attrName**  are null pointers. 



## GetChildNode<a name="a70d5844ef0f0c35b9eb3bbba177bccc0"></a>

```
const struct [DeviceResourceNode](deviceresourcenode.md)*(* DeviceResourceIface::GetChildNode) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *nodeName)
```

 **Description:**

Obtains the child node with a specified node name from a parent node. 

**Parameters:**

<a name="table1779528955084835"></a>
<table><thead align="left"><tr id="row887315300084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1264618855084835"><a name="p1264618855084835"></a><a name="p1264618855084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p995585251084835"><a name="p995585251084835"></a><a name="p995585251084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1754780854084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the parent node. </td>
</tr>
<tr id="row494955280084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">nodeName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the child node to obtain.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the child nodes if the operation is successful; returns  **NULL**  otherwise. 



## GetElemNum<a name="a0fafd4d32592ce2fbe951807995c5ab3"></a>

```
int32_t(* DeviceResourceIface::GetElemNum) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName)
```

 **Description:**

Obtains the number of values for an array attribute of a configuration tree node. 

**Parameters:**

<a name="table1388234166084835"></a>
<table><thead align="left"><tr id="row379813172084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p384105564084835"><a name="p384105564084835"></a><a name="p384105564084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p147143676084835"><a name="p147143676084835"></a><a name="p147143676084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row150092166084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1332825829084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the number of values for an array attribute if the operation is successful; return a negative value otherwise. 



## GetNodeByMatchAttr<a name="a8d7c819ee3d00ded8eef01b0594f3571"></a>

```
const struct [DeviceResourceNode](deviceresourcenode.md)*(* DeviceResourceIface::GetNodeByMatchAttr) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrValue)
```

 **Description:**

Obtains a specified child node of the current tree node based on the value of a specific reserved attribute \(for example, the reserved attribute of the HCS is  **match\_attr**\). 

There is a specific reserved attribute in the syntax of the device resource configuration source file. If this attribute is set for a tree node, you can obtain the node based on the attribute value. Users can set the attribute value based on the usage of their own nodes, but they must ensure that the attribute values are unique.

**Parameters:**

<a name="table2107184952084835"></a>
<table><thead align="left"><tr id="row71022918084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p729566929084835"><a name="p729566929084835"></a><a name="p729566929084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p796779469084835"><a name="p796779469084835"></a><a name="p796779469084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2080410478084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the node for whom a child node is to be obtained. The node can be the child node's parent node or grandparent node. </td>
</tr>
<tr id="row1118764723084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrValue</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the value of the reserved attribute configured for the child node.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the target node if the operation is successful; returns  **NULL**  otherwise. 



## GetNodeByRefAttr<a name="a8066548056633048c008e7a29aac8c8f"></a>

```
const struct [DeviceResourceNode](deviceresourcenode.md)*(* DeviceResourceIface::GetNodeByRefAttr) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName)
```

 **Description:**

Obtains the node that is specified by a node-type attribute of a configuration tree node. 

If the attribute value is a configuration tree node, the path of the node is converted to a globally unique  **hashValue**  when the device resource source file is compiled \(for example, the compilation tool of the HCS source file is hc-gen\). For details about the  **hashValue**, see  **DeviceResourceNode**. When you obtain a tree node using the node-type attribute, you obtain the  **hashValue**  through the node-type attribute first, and then traverse the tree to obtain the tree node corresponding to the  **hashValue**.

**Parameters:**

<a name="table885581576084835"></a>
<table><thead align="left"><tr id="row181240118084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1887717730084835"><a name="p1887717730084835"></a><a name="p1887717730084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1027171463084835"><a name="p1027171463084835"></a><a name="p1027171463084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row510481296084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the tree node whose attribute is to obtain. </td>
</tr>
<tr id="row561997981084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of attribute whose value is a node path. </td>
</tr>
</tbody>
</table>

**Returns:**

Returns the target node if the operation is successful; returns  **NULL**  otherwise. 



## GetRootNode<a name="adc489c2c907ebf9a098c91ba110a2c37"></a>

```
const struct [DeviceResourceNode](deviceresourcenode.md)*(* DeviceResourceIface::GetRootNode) (void)
```

 **Description:**

Obtains the root node of the configuration tree. 

When the driver framework is started, a configuration tree is created. You can use this function to obtain the root node of the configuration tree.

**Returns:**

Returns the root node of the configuration tree if the operation is successful; returns  **NULL**  otherwise. 



## GetString<a name="a1989a47b8d61401e57ee523e01bc25ee"></a>

```
int32_t(* DeviceResourceIface::GetString) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, const char **value, const char *def)
```

 **Description:**

Obtains the value of a  **String**  attribute of a configuration tree node. 

**Parameters:**

<a name="table1098118732084835"></a>
<table><thead align="left"><tr id="row845484248084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1359567129084835"><a name="p1359567129084835"></a><a name="p1359567129084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p329551266084835"><a name="p329551266084835"></a><a name="p329551266084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1528096631084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row18790938084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the attribute. </td>
</tr>
<tr id="row1084075844084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the memory where the obtained data is stored. The string memory is provided by the function implementer. Users only need to transfer the double pointer. The memory cannot be released after being used. </td>
</tr>
<tr id="row1551322461084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to be passed to <strong id="b1751170623084835"><a name="b1751170623084835"></a><a name="b1751170623084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetStringArrayElem<a name="a787eb71963c16c96bca913729078dd9d"></a>

```
int32_t(* DeviceResourceIface::GetStringArrayElem) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint32_t [index](utils.md#ga1d3748ca570dcb09a2fb28e8015107dd), const char **value, const char *def)
```

 **Description:**

Obtains the value of a  **String**  array attribute numbered  **index**  of a configuration tree node. 

**Parameters:**

<a name="table306400688084835"></a>
<table><thead align="left"><tr id="row842468805084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p666858566084835"><a name="p666858566084835"></a><a name="p666858566084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p629667626084835"><a name="p629667626084835"></a><a name="p629667626084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1746598822084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1639096993084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute. </td>
</tr>
<tr id="row739201142084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of the index (counting from 0) where the value is to obtain. </td>
</tr>
<tr id="row556231468084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the double pointer to the memory where the obtained data is stored. The string memory is provided by the function implementer. Users only need to transfer the double pointer. The memory cannot be released after being used. </td>
</tr>
<tr id="row1803722695084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">def Indicates the value to be passed to <strong id="b1234486795084835"><a name="b1234486795084835"></a><a name="b1234486795084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint16<a name="a1d3191febf1c9a0731a1614295a1529b"></a>

```
int32_t(* DeviceResourceIface::GetUint16) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint16_t *value, uint16_t def)
```

 **Description:**

Obtains the value of a  **Uint16**  attribute of a configuration tree node. 

**Parameters:**

<a name="table1542875612084835"></a>
<table><thead align="left"><tr id="row954766385084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1799439307084835"><a name="p1799439307084835"></a><a name="p1799439307084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2101077580084835"><a name="p2101077580084835"></a><a name="p2101077580084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1247877057084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1361352294084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the attribute. </td>
</tr>
<tr id="row204016238084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory that stores the obtained data. The memory is applied by the user. </td>
</tr>
<tr id="row385595105084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into the memory pointed by <strong id="b1487680794084835"><a name="b1487680794084835"></a><a name="b1487680794084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint16Array<a name="a54977ca0fd60515bad5e33adf830fc64"></a>

```
int32_t(* DeviceResourceIface::GetUint16Array) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint16_t *value, uint32_t len, uint16_t def)
```

 **Description:**

Obtains the values of a  **Uint16**  array attribute of a configuration tree node. 

**Parameters:**

<a name="table1217020629084835"></a>
<table><thead align="left"><tr id="row1054204937084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1157733845084835"><a name="p1157733845084835"></a><a name="p1157733845084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p699519443084835"><a name="p699519443084835"></a><a name="p699519443084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1396601735084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row786392498084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute. </td>
</tr>
<tr id="row1953803359084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the array that stores the obtained data. The memory of the array is applied by the user. </td>
</tr>
<tr id="row2088269934084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the array. </td>
</tr>
<tr id="row665233019084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into <strong id="b1153426435084835"><a name="b1153426435084835"></a><a name="b1153426435084835"></a>value</strong> if the operation fails. If the obtained attribute value contains 32-bit or 64-bit data, the element corresponding to the 32-bit or 64-bit data in the array is filled using the value of <strong id="b397864415084835"><a name="b397864415084835"></a><a name="b397864415084835"></a>def</strong>, and the other elements are filled with the actual value obtained. If the failure is caused by other exceptions, the first element in the array is filled using the value of <strong id="b1106803619084835"><a name="b1106803619084835"></a><a name="b1106803619084835"></a>def</strong>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint16ArrayElem<a name="a27abcf7cdca0b25b6e620b75590e0a2d"></a>

```
int32_t(* DeviceResourceIface::GetUint16ArrayElem) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint32_t [index](utils.md#ga1d3748ca570dcb09a2fb28e8015107dd), uint16_t *value, uint16_t def)
```

 **Description:**

Obtains the value of a  **Uint16**  array attribute numbered  **index**  of a configuration tree node. 

**Parameters:**

<a name="table70522193084835"></a>
<table><thead align="left"><tr id="row1495696991084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p430065858084835"><a name="p430065858084835"></a><a name="p430065858084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p95572827084835"><a name="p95572827084835"></a><a name="p95572827084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row676030755084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1857545521084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute. </td>
</tr>
<tr id="row1574643143084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of the index (counting from 0) where the value is to obtain. </td>
</tr>
<tr id="row2075428141084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory that stores the obtained data. The memory is applied by the user. </td>
</tr>
<tr id="row739745318084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into the memory pointed by <strong id="b2074104095084835"><a name="b2074104095084835"></a><a name="b2074104095084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint32<a name="a87cf305ff9cabdbeb5011e6c04106b9e"></a>

```
int32_t(* DeviceResourceIface::GetUint32) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint32_t *value, uint32_t def)
```

 **Description:**

Obtains the value of a  **Uint32**  attribute of a configuration tree node. 

**Parameters:**

<a name="table256710093084835"></a>
<table><thead align="left"><tr id="row628584659084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p585858137084835"><a name="p585858137084835"></a><a name="p585858137084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2072164924084835"><a name="p2072164924084835"></a><a name="p2072164924084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1678562193084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1426321147084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the attribute. </td>
</tr>
<tr id="row511349137084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory that stores the obtained data. The memory is applied by the user. </td>
</tr>
<tr id="row818807997084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into the memory pointed by <strong id="b257467945084835"><a name="b257467945084835"></a><a name="b257467945084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint32Array<a name="a2ed5d24a45946e270b4416c400839966"></a>

```
int32_t(* DeviceResourceIface::GetUint32Array) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint32_t *value, uint32_t len, uint32_t def)
```

 **Description:**

Obtains the values of a  **Uint32**  array attribute of a configuration tree node. 

**Parameters:**

<a name="table1086914587084835"></a>
<table><thead align="left"><tr id="row1305337199084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p727223727084835"><a name="p727223727084835"></a><a name="p727223727084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1985657493084835"><a name="p1985657493084835"></a><a name="p1985657493084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row385553595084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1136059338084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute. </td>
</tr>
<tr id="row767149245084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to an array that stores the obtained data. </td>
</tr>
<tr id="row1068628529084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the array that stores the obtained data. The memory of the array is applied by the user. </td>
</tr>
<tr id="row397311497084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into <strong id="b1259568851084835"><a name="b1259568851084835"></a><a name="b1259568851084835"></a>value</strong> if the operation fails. If the obtained attribute value contains 64-bit data, the element corresponding to the 64-bit data in the array is filled using the value of <strong id="b1102623494084835"><a name="b1102623494084835"></a><a name="b1102623494084835"></a>def</strong>, and the other elements are filled with the actual value obtained. If the failure is caused by other exceptions, the first element in the array is filled using the value of <strong id="b1769487611084835"><a name="b1769487611084835"></a><a name="b1769487611084835"></a>def</strong>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint32ArrayElem<a name="a942b67fcd814a37d92e33f3de33c2ff5"></a>

```
int32_t(* DeviceResourceIface::GetUint32ArrayElem) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint32_t [index](utils.md#ga1d3748ca570dcb09a2fb28e8015107dd), uint32_t *value, uint32_t def)
```

 **Description:**

Obtains the value of a  **Uint32**  array attribute numbered  **index**  of a configuration tree node. 

**Parameters:**

<a name="table845880502084835"></a>
<table><thead align="left"><tr id="row640023383084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p460453142084835"><a name="p460453142084835"></a><a name="p460453142084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1915500252084835"><a name="p1915500252084835"></a><a name="p1915500252084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1510619636084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1228098239084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute. </td>
</tr>
<tr id="row583526561084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of the index (counting from 0) where the value is to obtain. </td>
</tr>
<tr id="row1529692944084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory that stores the obtained data. The memory is applied by the user. </td>
</tr>
<tr id="row192179420084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into the memory pointed by <strong id="b1695489054084835"><a name="b1695489054084835"></a><a name="b1695489054084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint64<a name="a3c364db9381da16449bb96d6be86aed8"></a>

```
int32_t(* DeviceResourceIface::GetUint64) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint64_t *value, uint64_t def)
```

 **Description:**

Obtains the value of a  **Uint64**  attribute of a configuration tree node. 

**Parameters:**

<a name="table53427408084835"></a>
<table><thead align="left"><tr id="row241667332084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p634730000084835"><a name="p634730000084835"></a><a name="p634730000084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p990079625084835"><a name="p990079625084835"></a><a name="p990079625084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1759235924084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row43977496084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the attribute. </td>
</tr>
<tr id="row1774089006084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory that stores the obtained data. The memory is applied by the user. </td>
</tr>
<tr id="row1789293657084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into the memory pointed by <strong id="b1038226797084835"><a name="b1038226797084835"></a><a name="b1038226797084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint64Array<a name="ab378caa47c5b01c31ca602d4eaa3046f"></a>

```
int32_t(* DeviceResourceIface::GetUint64Array) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint64_t *value, uint32_t len, uint64_t def)
```

 **Description:**

Obtains the values of a  **Uint64**  array attribute of a configuration tree node. 

**Parameters:**

<a name="table1517919410084835"></a>
<table><thead align="left"><tr id="row1282031485084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p702866313084835"><a name="p702866313084835"></a><a name="p702866313084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p152633406084835"><a name="p152633406084835"></a><a name="p152633406084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2015520535084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1888838788084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute. </td>
</tr>
<tr id="row961482271084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the array that stores the obtained data. The memory of the array is applied by the user. </td>
</tr>
<tr id="row583621592084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the array. </td>
</tr>
<tr id="row1612033279084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into the first element in the <strong id="b2131414697084835"><a name="b2131414697084835"></a><a name="b2131414697084835"></a>value</strong> array if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint64ArrayElem<a name="aac32428eb3762de48514bd14348fd230"></a>

```
int32_t(* DeviceResourceIface::GetUint64ArrayElem) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint32_t [index](utils.md#ga1d3748ca570dcb09a2fb28e8015107dd), uint64_t *value, uint64_t def)
```

 **Description:**

Obtains the value of a  **Uint64**  array attribute numbered  **index**  of a configuration tree node. 

**Parameters:**

<a name="table598315479084835"></a>
<table><thead align="left"><tr id="row1467582859084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p61504812084835"><a name="p61504812084835"></a><a name="p61504812084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1159081383084835"><a name="p1159081383084835"></a><a name="p1159081383084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2038365630084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1400650463084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute. </td>
</tr>
<tr id="row1876670848084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of the index (counting from 0) where the value is to obtain. </td>
</tr>
<tr id="row864213114084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory that stores the obtained data. The memory is applied by the user. </td>
</tr>
<tr id="row1488012592084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into the memory pointed by <strong id="b1971155739084835"><a name="b1971155739084835"></a><a name="b1971155739084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint8<a name="a5610a62186ad18320dadcad7077fb3bb"></a>

```
int32_t(* DeviceResourceIface::GetUint8) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint8_t *value, uint8_t def)
```

 **Description:**

Obtains the value of a  **Uint8**  attribute of a configuration tree node. 

**Parameters:**

<a name="table626699598084835"></a>
<table><thead align="left"><tr id="row1030670866084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1241131074084835"><a name="p1241131074084835"></a><a name="p1241131074084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2131397077084835"><a name="p2131397077084835"></a><a name="p2131397077084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row126681429084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1016414406084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the attribute. </td>
</tr>
<tr id="row518070819084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory that stores the obtained data. The memory is applied by the user. </td>
</tr>
<tr id="row689750345084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into the memory pointed by <strong id="b723931204084835"><a name="b723931204084835"></a><a name="b723931204084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the attribute value is obtained successfully; returns a negative value otherwise. 



## GetUint8Array<a name="a067d741f2c3938ca08be2282e741b0a4"></a>

```
int32_t(* DeviceResourceIface::GetUint8Array) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint8_t *value, uint32_t len, uint8_t def)
```

 **Description:**

Obtains the values of a  **Uint8**  array attribute of a configuration tree node. 

**Parameters:**

<a name="table1015295864084835"></a>
<table><thead align="left"><tr id="row2135712802084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p975402259084835"><a name="p975402259084835"></a><a name="p975402259084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1673845288084835"><a name="p1673845288084835"></a><a name="p1673845288084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1451332752084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row1379747908084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute. </td>
</tr>
<tr id="row1263280995084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the array that stores the obtained data. The memory of the array is applied by the user. </td>
</tr>
<tr id="row107117246084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">len</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the length of the array. </td>
</tr>
<tr id="row1691795546084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into <strong id="b196869478084835"><a name="b196869478084835"></a><a name="b196869478084835"></a>value</strong> if the operation fails. If the obtained attribute value contains 16-bit, 32-bit, or 64-bit data, the element corresponding to the 16-bit, 32-bit, or 64-bit data in the array is filled using the value of <strong id="b2001451139084835"><a name="b2001451139084835"></a><a name="b2001451139084835"></a>def</strong>, and the other elements are filled with the actual value obtained. If the failure is caused by other exceptions, the first element in the array is filled using the value of <strong id="b104428801084835"><a name="b104428801084835"></a><a name="b104428801084835"></a>def</strong>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the operation is successful; returns a negative value otherwise. 



## GetUint8ArrayElem<a name="a0973933ace2447ec38a82e7995e2c5af"></a>

```
int32_t(* DeviceResourceIface::GetUint8ArrayElem) (const struct [DeviceResourceNode](deviceresourcenode.md) *node, const char *attrName, uint32_t [index](utils.md#ga1d3748ca570dcb09a2fb28e8015107dd), uint8_t *value, uint8_t def)
```

 **Description:**

Obtains the value of a  **Unit8**  array attribute numbered  **index**  of a configuration tree node. 

**Parameters:**

<a name="table771441208084835"></a>
<table><thead align="left"><tr id="row866481064084835"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p753508722084835"><a name="p753508722084835"></a><a name="p753508722084835"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1858562521084835"><a name="p1858562521084835"></a><a name="p1858562521084835"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row398210623084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">node</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the configuration tree node. </td>
</tr>
<tr id="row2147049412084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attrName</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the name of the array attribute. </td>
</tr>
<tr id="row1639007704084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">index</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the number of the index (counting from 0) where the value is to obtain. </td>
</tr>
<tr id="row2014571318084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">value</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the memory that stores the obtained data. The memory is applied by the user. </td>
</tr>
<tr id="row1097616421084835"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">def</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the value to fill into the memory pointed by <strong id="b101751802084835"><a name="b101751802084835"></a><a name="b101751802084835"></a>value</strong> if the operation fails.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the array attribute value is obtained successfully; returns a negative value otherwise. 



