# wifiiot\_gpio.h<a name="EN-US_TOPIC_0000001055515024"></a>

## **Overview**<a name="section1550056797090254"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Declares the GPIO interface functions. 

These functions are used for GPIO initialization, input/output settings, and level settings. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section556905466090254"></a>

## Typedefs<a name="typedef-members"></a>

<a name="table210578453090254"></a>
<table><thead align="left"><tr id="row26631136090254"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2014337425090254"><a name="p2014337425090254"></a><a name="p2014337425090254"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1808429966090254"><a name="p1808429966090254"></a><a name="p1808429966090254"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1915468740090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p952521528090254"><a name="p952521528090254"></a><a name="p952521528090254"></a><a href="wifiiot.md#ga93120443d8150e18701ce6d3dd290408">GpioIsrCallbackFunc</a>) (char *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p936383860090254"><a name="p936383860090254"></a><a name="p936383860090254"></a>typedef void(* </p>
<p id="p1358194646090254"><a name="p1358194646090254"></a><a name="p1358194646090254"></a>Indicates the GPIO interrupt callback. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table953908498090254"></a>
<table><thead align="left"><tr id="row133310045090254"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1935380932090254"><a name="p1935380932090254"></a><a name="p1935380932090254"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1519810347090254"><a name="p1519810347090254"></a><a name="p1519810347090254"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1406436292090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p791366284090254"><a name="p791366284090254"></a><a name="p791366284090254"></a><a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> {   <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7ae046fd3cc933c4a52555b32e0ffdb305">WIFI_IOT_GPIO_IDX_0</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7a07e8f1a810e4eea4bbf62c3090b9b2c3">WIFI_IOT_GPIO_IDX_1</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7ac7c272c3c3023e61b1aa7a496ca6520e">WIFI_IOT_GPIO_IDX_2</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7a4fbcd92ee8ce17811e439e9741ede927">WIFI_IOT_GPIO_IDX_3</a>,   <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7aa4fd128cc42f5059812f16ab7731db1f">WIFI_IOT_GPIO_IDX_4</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7a2aab1a0fc68cbbc834a8c9244e9b45f8">WIFI_IOT_GPIO_IDX_5</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7a01e89ab69b089341b8fc10dc6df8b5ff">WIFI_IOT_GPIO_IDX_6</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7a035a212d1b1da2f84c7dcba0b9a5c8e6">WIFI_IOT_GPIO_IDX_7</a>,   <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7ac48a013c85a5701a8c18ce474ba76baf">WIFI_IOT_GPIO_IDX_8</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7ad4279d9a32bfaf63d1f1cf1e7bcea696">WIFI_IOT_GPIO_IDX_9</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7aa3d9ce72cd5fe2382390cd74e902a033">WIFI_IOT_GPIO_IDX_10</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7a596f9afca31a79a1bc43bf929c7045cd">WIFI_IOT_GPIO_IDX_11</a>,   <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7a0e2bde0b5d0914e590803a2c280b3fcd">WIFI_IOT_GPIO_IDX_12</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7a46b47d9cb13dab42e31ec6c6b73447b5">WIFI_IOT_GPIO_IDX_13</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7aefb8b54fba7f3938b23a07838ab330ac">WIFI_IOT_GPIO_IDX_14</a>, <a href="wifiiot.md#ggacb21f234cf149161f1f95f3330eeb8e7a7d4d2abc5105e7d3f9a9a4f96e778232">WIFI_IOT_GPIO_IDX_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p186481113090254"><a name="p186481113090254"></a><a name="p186481113090254"></a>Enumerates GPIO pin IDs. </p>
</td>
</tr>
<tr id="row1370304482090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p766414750090254"><a name="p766414750090254"></a><a name="p766414750090254"></a><a href="wifiiot.md#gac9095d1db72e5046b2ec1895aaec0e6b">WifiIotGpioValue</a> { <a href="wifiiot.md#ggac9095d1db72e5046b2ec1895aaec0e6ba5af1f302a77089f4310cafdf0f19a8e9">WIFI_IOT_GPIO_VALUE0</a> = 0, <a href="wifiiot.md#ggac9095d1db72e5046b2ec1895aaec0e6ba13488c68c87449410ef3de8855025708">WIFI_IOT_GPIO_VALUE1</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p504066823090254"><a name="p504066823090254"></a><a name="p504066823090254"></a>Enumerates GPIO level values. </p>
</td>
</tr>
<tr id="row1355282876090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2026015515090254"><a name="p2026015515090254"></a><a name="p2026015515090254"></a><a href="wifiiot.md#gab4b1fb50c758d491ba297a65e1c7a70a">WifiIotGpioDir</a> { <a href="wifiiot.md#ggab4b1fb50c758d491ba297a65e1c7a70aa4cf28c4ada04aa47ffad38cf1ba4a50d">WIFI_IOT_GPIO_DIR_IN</a> = 0, <a href="wifiiot.md#ggab4b1fb50c758d491ba297a65e1c7a70aa142b702aa598f2482ae27f7d11bdb6eb">WIFI_IOT_GPIO_DIR_OUT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1102993096090254"><a name="p1102993096090254"></a><a name="p1102993096090254"></a>Enumerates GPIO directions. </p>
</td>
</tr>
<tr id="row1093809338090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p201204979090254"><a name="p201204979090254"></a><a name="p201204979090254"></a><a href="wifiiot.md#gac8eb8ad448903ed52c96ccc675e81f94">WifiIotGpioIntType</a> { <a href="wifiiot.md#ggac8eb8ad448903ed52c96ccc675e81f94ab195772135577e55af672a4e40cb7cfe">WIFI_IOT_INT_TYPE_LEVEL</a> = 0, <a href="wifiiot.md#ggac8eb8ad448903ed52c96ccc675e81f94ab06457c13bf24678921dd844e5380b68">WIFI_IOT_INT_TYPE_EDGE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p152585455090254"><a name="p152585455090254"></a><a name="p152585455090254"></a>Enumerates GPIO interrupt trigger modes. </p>
</td>
</tr>
<tr id="row1316922068090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1871372736090254"><a name="p1871372736090254"></a><a name="p1871372736090254"></a><a href="wifiiot.md#gab81589838cedcc3933bb789c97ad3643">WifiIotGpioIntPolarity</a> { <a href="wifiiot.md#ggab81589838cedcc3933bb789c97ad3643a31fc3445fff6122de496652f3e9023cd">WIFI_IOT_GPIO_EDGE_FALL_LEVEL_LOW</a> = 0, <a href="wifiiot.md#ggab81589838cedcc3933bb789c97ad3643ac1c7abc9c4ecc8c336160a1c36d3bfed">WIFI_IOT_GPIO_EDGE_RISE_LEVEL_HIGH</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p764042903090254"><a name="p764042903090254"></a><a name="p764042903090254"></a>Enumerates I/O interrupt polarities. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1760577905090254"></a>
<table><thead align="left"><tr id="row746943002090254"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1228854830090254"><a name="p1228854830090254"></a><a name="p1228854830090254"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1121677929090254"><a name="p1121677929090254"></a><a name="p1121677929090254"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1877745666090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1366045778090254"><a name="p1366045778090254"></a><a name="p1366045778090254"></a><a href="wifiiot.md#ga7a0c4f45b99870ae828a0d3f71561421">GpioInit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1132903766090254"><a name="p1132903766090254"></a><a name="p1132903766090254"></a>unsigned int </p>
<p id="p1017619052090254"><a name="p1017619052090254"></a><a name="p1017619052090254"></a>Initializes the GPIO device. </p>
</td>
</tr>
<tr id="row2137327258090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p150500764090254"><a name="p150500764090254"></a><a name="p150500764090254"></a><a href="wifiiot.md#ga2f829dbe36b81f093f43f59e3fa36212">GpioDeinit</a> (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1813847013090254"><a name="p1813847013090254"></a><a name="p1813847013090254"></a>unsigned int </p>
<p id="p1765244765090254"><a name="p1765244765090254"></a><a name="p1765244765090254"></a>Deinitializes the GPIO device. </p>
</td>
</tr>
<tr id="row1441452640090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1998396903090254"><a name="p1998396903090254"></a><a name="p1998396903090254"></a><a href="wifiiot.md#gabe3de0ab249704929ec95c82815e02b7">GpioSetDir</a> (<a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> id, <a href="wifiiot.md#gab4b1fb50c758d491ba297a65e1c7a70a">WifiIotGpioDir</a> dir)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1421345736090254"><a name="p1421345736090254"></a><a name="p1421345736090254"></a>unsigned int </p>
<p id="p1030751011090254"><a name="p1030751011090254"></a><a name="p1030751011090254"></a>Sets the direction for a GPIO pin. </p>
</td>
</tr>
<tr id="row2060255365090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1978493145090254"><a name="p1978493145090254"></a><a name="p1978493145090254"></a><a href="wifiiot.md#gafdd6f6a174bd31c3805a23dc923d8114">GpioGetDir</a> (<a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> id, <a href="wifiiot.md#gab4b1fb50c758d491ba297a65e1c7a70a">WifiIotGpioDir</a> *dir)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1102045117090254"><a name="p1102045117090254"></a><a name="p1102045117090254"></a>unsigned int </p>
<p id="p2012395084090254"><a name="p2012395084090254"></a><a name="p2012395084090254"></a>Obtains the direction for a GPIO pin. </p>
</td>
</tr>
<tr id="row740134336090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p530816021090254"><a name="p530816021090254"></a><a name="p530816021090254"></a><a href="wifiiot.md#ga13718f6a5c52a272baca64167b67606f">GpioSetOutputVal</a> (<a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> id, <a href="wifiiot.md#gac9095d1db72e5046b2ec1895aaec0e6b">WifiIotGpioValue</a> val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1849944257090254"><a name="p1849944257090254"></a><a name="p1849944257090254"></a>unsigned int </p>
<p id="p1446602266090254"><a name="p1446602266090254"></a><a name="p1446602266090254"></a>Sets the output level value for a GPIO pin. </p>
</td>
</tr>
<tr id="row1412893519090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p784978477090254"><a name="p784978477090254"></a><a name="p784978477090254"></a><a href="wifiiot.md#gadea7c9475f510d00baa054364fd8de9a">GpioGetOutputVal</a> (<a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> id, <a href="wifiiot.md#gac9095d1db72e5046b2ec1895aaec0e6b">WifiIotGpioValue</a> *val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p181595591090254"><a name="p181595591090254"></a><a name="p181595591090254"></a>unsigned int </p>
<p id="p255447410090254"><a name="p255447410090254"></a><a name="p255447410090254"></a>Obtains the output level value of a GPIO pin. </p>
</td>
</tr>
<tr id="row639271764090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p713259073090254"><a name="p713259073090254"></a><a name="p713259073090254"></a><a href="wifiiot.md#gad63e45fa986b5dbcf3fb94f4fe7c3ee6">GpioGetInputVal</a> (<a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> id, <a href="wifiiot.md#gac9095d1db72e5046b2ec1895aaec0e6b">WifiIotGpioValue</a> *val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1434138008090254"><a name="p1434138008090254"></a><a name="p1434138008090254"></a>unsigned int </p>
<p id="p1429757194090254"><a name="p1429757194090254"></a><a name="p1429757194090254"></a>Obtains the input level value of a GPIO pin. </p>
</td>
</tr>
<tr id="row419595560090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p84399686090254"><a name="p84399686090254"></a><a name="p84399686090254"></a><a href="wifiiot.md#ga2eaec33b87a24bf1ae6b2a8d7ec38674">GpioRegisterIsrFunc</a> (<a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> id, <a href="wifiiot.md#gac8eb8ad448903ed52c96ccc675e81f94">WifiIotGpioIntType</a> intType, <a href="wifiiot.md#gab81589838cedcc3933bb789c97ad3643">WifiIotGpioIntPolarity</a> intPolarity, <a href="wifiiot.md#ga93120443d8150e18701ce6d3dd290408">GpioIsrCallbackFunc</a> func, char *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p411799188090254"><a name="p411799188090254"></a><a name="p411799188090254"></a>unsigned int </p>
<p id="p1644237183090254"><a name="p1644237183090254"></a><a name="p1644237183090254"></a>Enables the interrupt function for a GPIO pin. </p>
</td>
</tr>
<tr id="row1454933842090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p637877477090254"><a name="p637877477090254"></a><a name="p637877477090254"></a><a href="wifiiot.md#ga403b7bb8037ae1415d5d0dd623379e50">GpioUnregisterIsrFunc</a> (<a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p587263959090254"><a name="p587263959090254"></a><a name="p587263959090254"></a>unsigned int </p>
<p id="p1048546097090254"><a name="p1048546097090254"></a><a name="p1048546097090254"></a>Disables the interrupt function for a GPIO pin. </p>
</td>
</tr>
<tr id="row2022922321090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p714383288090254"><a name="p714383288090254"></a><a name="p714383288090254"></a><a href="wifiiot.md#ga3d2e70a9ffded1937e7423cf59e0f40f">GpioSetIsrMask</a> (<a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> id, unsigned char mask)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1975822543090254"><a name="p1975822543090254"></a><a name="p1975822543090254"></a>unsigned int </p>
<p id="p1983743039090254"><a name="p1983743039090254"></a><a name="p1983743039090254"></a>Masks the interrupt function for a GPIO pin. </p>
</td>
</tr>
<tr id="row81988572090254"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p837411698090254"><a name="p837411698090254"></a><a name="p837411698090254"></a><a href="wifiiot.md#ga400c1978a35742c101881aa825749152">GpioSetIsrMode</a> (<a href="wifiiot.md#gacb21f234cf149161f1f95f3330eeb8e7">WifiIotGpioIdx</a> id, <a href="wifiiot.md#gac8eb8ad448903ed52c96ccc675e81f94">WifiIotGpioIntType</a> intType, <a href="wifiiot.md#gab81589838cedcc3933bb789c97ad3643">WifiIotGpioIntPolarity</a> intPolarity)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1885265174090254"><a name="p1885265174090254"></a><a name="p1885265174090254"></a>unsigned int </p>
<p id="p2018073552090254"><a name="p2018073552090254"></a><a name="p2018073552090254"></a>Sets the interrupt trigger mode of a GPIO pin. </p>
</td>
</tr>
</tbody>
</table>

