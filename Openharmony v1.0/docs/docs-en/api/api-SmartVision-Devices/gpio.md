# GPIO<a name="EN-US_TOPIC_0000001054918103"></a>

## **Overview**<a name="section1804743425093521"></a>

Provides standard general-purpose input/output \(GPIO\) interfaces for driver development. 

You can use this module to perform operations on a GPIO pin, including setting the input/output direction, reading/writing the level value, and setting the interrupt service routine \(ISR\) function.

**Since:**

1.0

## **Summary**<a name="section1990578471093521"></a>

## Files<a name="files"></a>

<a name="table100652972093521"></a>
<table><thead align="left"><tr id="row1245138422093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p823074282093521"><a name="p823074282093521"></a><a name="p823074282093521"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p311341634093521"><a name="p311341634093521"></a><a name="p311341634093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1848302549093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1794678483093521"><a name="p1794678483093521"></a><a name="p1794678483093521"></a><a href="gpio_if-h.md">gpio_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p577784313093521"><a name="p577784313093521"></a><a name="p577784313093521"></a>Declares the standard GPIO interface functions. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table178103356093521"></a>
<table><thead align="left"><tr id="row1143058692093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p599757463093521"><a name="p599757463093521"></a><a name="p599757463093521"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p419103887093521"><a name="p419103887093521"></a><a name="p419103887093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row262182395093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1883176520093521"><a name="p1883176520093521"></a><a name="p1883176520093521"></a><a href="gpio.md#ga8f3b7d0f0aaa1da8117781efe4b1670e">GpioIrqFunc</a>) (uint16_t gpio, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p765234853093521"><a name="p765234853093521"></a><a name="p765234853093521"></a>typedef int32_t(* </p>
<p id="p768650203093521"><a name="p768650203093521"></a><a name="p768650203093521"></a>Defines the function type of a GPIO interrupt service routine (ISR). </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1875607766093521"></a>
<table><thead align="left"><tr id="row1369620546093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p187383255093521"><a name="p187383255093521"></a><a name="p187383255093521"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p48217617093521"><a name="p48217617093521"></a><a name="p48217617093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row753788631093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1150445100093521"><a name="p1150445100093521"></a><a name="p1150445100093521"></a><a href="gpio.md#ga6a25a3efddf2301c7b01a7f0af44fb11">GpioValue</a> { <a href="gpio.md#gga6a25a3efddf2301c7b01a7f0af44fb11aff32e096d7022208ae0dc00c95bd8e08">GPIO_VAL_LOW</a> = 0, <a href="gpio.md#gga6a25a3efddf2301c7b01a7f0af44fb11a9b9c172b01ce33bb20764c8dd5c7835f">GPIO_VAL_HIGH</a> = 1, <a href="gpio.md#gga6a25a3efddf2301c7b01a7f0af44fb11a6f009070245b6c7d3b48e990b2cc133a">GPIO_VAL_ERR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1988176013093521"><a name="p1988176013093521"></a><a name="p1988176013093521"></a>Enumerates GPIO level values. </p>
</td>
</tr>
<tr id="row605476899093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p133078902093521"><a name="p133078902093521"></a><a name="p133078902093521"></a><a href="gpio.md#ga71f27d3ba7ca04d9448199fca38ae19d">GpioDirType</a> { <a href="gpio.md#gga71f27d3ba7ca04d9448199fca38ae19da3881053acb92aad7798425cdbb565fff">GPIO_DIR_IN</a> = 0, <a href="gpio.md#gga71f27d3ba7ca04d9448199fca38ae19da73c68266253638e2246dda97a0d65d91">GPIO_DIR_OUT</a> = 1, <a href="gpio.md#gga71f27d3ba7ca04d9448199fca38ae19da13b9029a753d3c4a2fad6f863f5161bd">GPIO_DIR_ERR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1288369553093521"><a name="p1288369553093521"></a><a name="p1288369553093521"></a>Enumerates GPIO directions. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table618804954093521"></a>
<table><thead align="left"><tr id="row57001009093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1447281977093521"><a name="p1447281977093521"></a><a name="p1447281977093521"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1807098605093521"><a name="p1807098605093521"></a><a name="p1807098605093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1180648336093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p494162663093521"><a name="p494162663093521"></a><a name="p494162663093521"></a><a href="gpio.md#ga267cb09db1f12ac3f08f847e4141f3c5">GpioRead</a> (uint16_t gpio, uint16_t *val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1400430069093521"><a name="p1400430069093521"></a><a name="p1400430069093521"></a>int32_t </p>
<p id="p1033881069093521"><a name="p1033881069093521"></a><a name="p1033881069093521"></a>Reads the level value of a GPIO pin. </p>
</td>
</tr>
<tr id="row103140372093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1456008398093521"><a name="p1456008398093521"></a><a name="p1456008398093521"></a><a href="gpio.md#ga7dee8242ba9335b3217635ba64764bc4">GpioWrite</a> (uint16_t gpio, uint16_t val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1669643728093521"><a name="p1669643728093521"></a><a name="p1669643728093521"></a>int32_t </p>
<p id="p1845105568093521"><a name="p1845105568093521"></a><a name="p1845105568093521"></a>Writes the level value for a GPIO pin. </p>
</td>
</tr>
<tr id="row1618274893093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p252147887093521"><a name="p252147887093521"></a><a name="p252147887093521"></a><a href="gpio.md#ga5c628216d209fa76c69eca69856bc0ae">GpioSetDir</a> (uint16_t gpio, uint16_t dir)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p298341460093521"><a name="p298341460093521"></a><a name="p298341460093521"></a>int32_t </p>
<p id="p1722470912093521"><a name="p1722470912093521"></a><a name="p1722470912093521"></a>Sets the input/output direction for a GPIO pin. </p>
</td>
</tr>
<tr id="row1593651887093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1203320369093521"><a name="p1203320369093521"></a><a name="p1203320369093521"></a><a href="gpio.md#ga6eb1536930b7ec5e263667ba30dfc6fb">GpioGetDir</a> (uint16_t gpio, uint16_t *dir)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p347853726093521"><a name="p347853726093521"></a><a name="p347853726093521"></a>int32_t </p>
<p id="p727539354093521"><a name="p727539354093521"></a><a name="p727539354093521"></a>Obtains the input/output direction of a GPIO pin. </p>
</td>
</tr>
<tr id="row501003093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p643668811093521"><a name="p643668811093521"></a><a name="p643668811093521"></a><a href="gpio.md#ga6ea5d16b8d73cb74e36d367f05cb7f6e">GpioSetIrq</a> (uint16_t gpio, uint16_t mode, <a href="gpio.md#ga8f3b7d0f0aaa1da8117781efe4b1670e">GpioIrqFunc</a> func, void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p257597347093521"><a name="p257597347093521"></a><a name="p257597347093521"></a>int32_t </p>
<p id="p964853529093521"><a name="p964853529093521"></a><a name="p964853529093521"></a>Sets the ISR function for a GPIO pin. </p>
</td>
</tr>
<tr id="row244405023093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1220780265093521"><a name="p1220780265093521"></a><a name="p1220780265093521"></a><a href="gpio.md#ga0e417971d72956f64a3160525c2be19f">GpioUnSetIrq</a> (uint16_t gpio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1323823995093521"><a name="p1323823995093521"></a><a name="p1323823995093521"></a>int32_t </p>
<p id="p554571449093521"><a name="p554571449093521"></a><a name="p554571449093521"></a>Cancels the setting of the ISR function for a GPIO pin. </p>
</td>
</tr>
<tr id="row445547268093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1367071759093521"><a name="p1367071759093521"></a><a name="p1367071759093521"></a><a href="gpio.md#gafcf00796a949245d665e672ae0294aee">GpioEnableIrq</a> (uint16_t gpio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1326687919093521"><a name="p1326687919093521"></a><a name="p1326687919093521"></a>int32_t </p>
<p id="p2065870055093521"><a name="p2065870055093521"></a><a name="p2065870055093521"></a>Enables a GPIO pin interrupt. </p>
</td>
</tr>
<tr id="row458603231093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p431617222093521"><a name="p431617222093521"></a><a name="p431617222093521"></a><a href="gpio.md#gafa01dc510f26d5aff102d72679920929">GpioDisableIrq</a> (uint16_t gpio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1052755397093521"><a name="p1052755397093521"></a><a name="p1052755397093521"></a>int32_t </p>
<p id="p707990547093521"><a name="p707990547093521"></a><a name="p707990547093521"></a>Disables a GPIO pin interrupt. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section486324721093521"></a>

## **Typedef Documentation**<a name="section1370542574093521"></a>

## GpioIrqFunc<a name="ga8f3b7d0f0aaa1da8117781efe4b1670e"></a>

```
typedef int32_t(* GpioIrqFunc) (uint16_t gpio, void *data)
```

 **Description:**

Defines the function type of a GPIO interrupt service routine \(ISR\). 

This function is used when you call  [GpioSetIrq](gpio.md#ga6ea5d16b8d73cb74e36d367f05cb7f6e)  to register the ISR for a GPIO pin.

**Parameters:**

<a name="table613587846093521"></a>
<table><thead align="left"><tr id="row1327302536093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1153871651093521"><a name="p1153871651093521"></a><a name="p1153871651093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p619433690093521"><a name="p619433690093521"></a><a name="p619433690093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1094639927093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gpio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the GPIO number of the ISR. </td>
</tr>
<tr id="row1772374551093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the private data passed to this ISR (The data is specified when the ISR is registered).</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the ISR function type is successfully defined; returns a negative value otherwise. 

**See also:**

[GpioSetIrq](gpio.md#ga6ea5d16b8d73cb74e36d367f05cb7f6e) 

## **Enumeration Type Documentation**<a name="section1142716666093521"></a>

## GpioDirType<a name="ga71f27d3ba7ca04d9448199fca38ae19d"></a>

```
enum [GpioDirType](gpio.md#ga71f27d3ba7ca04d9448199fca38ae19d)
```

 **Description:**

Enumerates GPIO directions. 

<a name="table1341402805093521"></a>
<table><thead align="left"><tr id="row1583108882093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1541399074093521"><a name="p1541399074093521"></a><a name="p1541399074093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p111504694093521"><a name="p111504694093521"></a><a name="p111504694093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1591255621093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga71f27d3ba7ca04d9448199fca38ae19da3881053acb92aad7798425cdbb565fff"><a name="gga71f27d3ba7ca04d9448199fca38ae19da3881053acb92aad7798425cdbb565fff"></a><a name="gga71f27d3ba7ca04d9448199fca38ae19da3881053acb92aad7798425cdbb565fff"></a></strong>GPIO_DIR_IN </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1138917370093521"><a name="p1138917370093521"></a><a name="p1138917370093521"></a>Input direction </p>
 </td>
</tr>
<tr id="row1081612296093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga71f27d3ba7ca04d9448199fca38ae19da73c68266253638e2246dda97a0d65d91"><a name="gga71f27d3ba7ca04d9448199fca38ae19da73c68266253638e2246dda97a0d65d91"></a><a name="gga71f27d3ba7ca04d9448199fca38ae19da73c68266253638e2246dda97a0d65d91"></a></strong>GPIO_DIR_OUT </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p601319759093521"><a name="p601319759093521"></a><a name="p601319759093521"></a>Output direction </p>
 </td>
</tr>
<tr id="row676415948093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga71f27d3ba7ca04d9448199fca38ae19da13b9029a753d3c4a2fad6f863f5161bd"><a name="gga71f27d3ba7ca04d9448199fca38ae19da13b9029a753d3c4a2fad6f863f5161bd"></a><a name="gga71f27d3ba7ca04d9448199fca38ae19da13b9029a753d3c4a2fad6f863f5161bd"></a></strong>GPIO_DIR_ERR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p279015606093521"><a name="p279015606093521"></a><a name="p279015606093521"></a>Invalid direction </p>
 </td>
</tr>
</tbody>
</table>

## GpioValue<a name="ga6a25a3efddf2301c7b01a7f0af44fb11"></a>

```
enum [GpioValue](gpio.md#ga6a25a3efddf2301c7b01a7f0af44fb11)
```

 **Description:**

Enumerates GPIO level values. 

<a name="table1112777929093521"></a>
<table><thead align="left"><tr id="row1938519169093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1910660425093521"><a name="p1910660425093521"></a><a name="p1910660425093521"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1744689228093521"><a name="p1744689228093521"></a><a name="p1744689228093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row370714775093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6a25a3efddf2301c7b01a7f0af44fb11aff32e096d7022208ae0dc00c95bd8e08"><a name="gga6a25a3efddf2301c7b01a7f0af44fb11aff32e096d7022208ae0dc00c95bd8e08"></a><a name="gga6a25a3efddf2301c7b01a7f0af44fb11aff32e096d7022208ae0dc00c95bd8e08"></a></strong>GPIO_VAL_LOW </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p245529945093521"><a name="p245529945093521"></a><a name="p245529945093521"></a>Low GPIO level </p>
 </td>
</tr>
<tr id="row547466174093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6a25a3efddf2301c7b01a7f0af44fb11a9b9c172b01ce33bb20764c8dd5c7835f"><a name="gga6a25a3efddf2301c7b01a7f0af44fb11a9b9c172b01ce33bb20764c8dd5c7835f"></a><a name="gga6a25a3efddf2301c7b01a7f0af44fb11a9b9c172b01ce33bb20764c8dd5c7835f"></a></strong>GPIO_VAL_HIGH </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1568412233093521"><a name="p1568412233093521"></a><a name="p1568412233093521"></a>High GPIO level </p>
 </td>
</tr>
<tr id="row1183212813093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="gga6a25a3efddf2301c7b01a7f0af44fb11a6f009070245b6c7d3b48e990b2cc133a"><a name="gga6a25a3efddf2301c7b01a7f0af44fb11a6f009070245b6c7d3b48e990b2cc133a"></a><a name="gga6a25a3efddf2301c7b01a7f0af44fb11a6f009070245b6c7d3b48e990b2cc133a"></a></strong>GPIO_VAL_ERR </td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1266798957093521"><a name="p1266798957093521"></a><a name="p1266798957093521"></a>Invalid GPIO level </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section249746267093521"></a>

## GpioDisableIrq\(\)<a name="gafa01dc510f26d5aff102d72679920929"></a>

```
int32_t GpioDisableIrq (uint16_t gpio)
```

 **Description:**

Disables a GPIO pin interrupt. 

You can call this function when you need to temporarily mask a GPIO pin interrupt or cancel an ISR function.

**Parameters:**

<a name="table2015322469093521"></a>
<table><thead align="left"><tr id="row1276004179093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p462184014093521"><a name="p462184014093521"></a><a name="p462184014093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1601797964093521"><a name="p1601797964093521"></a><a name="p1601797964093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1339402845093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gpio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the GPIO pin number.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the GPIO pin interrupt is successfully disabled; returns a negative value otherwise. 



## GpioEnableIrq\(\)<a name="gafcf00796a949245d665e672ae0294aee"></a>

```
int32_t GpioEnableIrq (uint16_t gpio)
```

 **Description:**

Enables a GPIO pin interrupt. 

Before enabling the interrupt, you must call  [GpioSetIrq](gpio.md#ga6ea5d16b8d73cb74e36d367f05cb7f6e)  to set the ISR function for the GPIO pin.

**Parameters:**

<a name="table1350472043093521"></a>
<table><thead align="left"><tr id="row289366664093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p377669568093521"><a name="p377669568093521"></a><a name="p377669568093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1635473643093521"><a name="p1635473643093521"></a><a name="p1635473643093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row61648703093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gpio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the GPIO pin number.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the GPIO pin interrupt is successfully enabled; returns a negative value otherwise. 



## GpioGetDir\(\)<a name="ga6eb1536930b7ec5e263667ba30dfc6fb"></a>

```
int32_t GpioGetDir (uint16_t gpio, uint16_t * dir )
```

 **Description:**

Obtains the input/output direction of a GPIO pin. 

**Parameters:**

<a name="table599090416093521"></a>
<table><thead align="left"><tr id="row1129437629093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p384666373093521"><a name="p384666373093521"></a><a name="p384666373093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p377670505093521"><a name="p377670505093521"></a><a name="p377670505093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row739218589093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gpio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the GPIO pin number. </td>
</tr>
<tr id="row1604541400093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dir</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained input/output direction. For details, see <a href="gpio.md#ga71f27d3ba7ca04d9448199fca38ae19d">GpioDirType</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the GPIO pin direction is successfully obtained; returns a negative value otherwise. 



## GpioRead\(\)<a name="ga267cb09db1f12ac3f08f847e4141f3c5"></a>

```
int32_t GpioRead (uint16_t gpio, uint16_t * val )
```

 **Description:**

Reads the level value of a GPIO pin. 

Before using this function, you need to call  [GpioSetDir](gpio.md#ga5c628216d209fa76c69eca69856bc0ae)  to set the GPIO pin direction to input.

**Parameters:**

<a name="table1059324793093521"></a>
<table><thead align="left"><tr id="row853887646093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2017120339093521"><a name="p2017120339093521"></a><a name="p2017120339093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p689204345093521"><a name="p689204345093521"></a><a name="p689204345093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1463770376093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gpio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the GPIO pin number. </td>
</tr>
<tr id="row331234839093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">val</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the read level value. For details, see <a href="gpio.md#ga6a25a3efddf2301c7b01a7f0af44fb11">GpioValue</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the GPIO pin level value is successfully read; returns a negative value otherwise. 



## GpioSetDir\(\)<a name="ga5c628216d209fa76c69eca69856bc0ae"></a>

```
int32_t GpioSetDir (uint16_t gpio, uint16_t dir )
```

 **Description:**

Sets the input/output direction for a GPIO pin. 

Generally, you can set the direction to input when external level signals need to be read, and set the direction to output when the level signals need to be sent externally.

**Parameters:**

<a name="table1387434759093521"></a>
<table><thead align="left"><tr id="row2062285985093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p139920621093521"><a name="p139920621093521"></a><a name="p139920621093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1620208923093521"><a name="p1620208923093521"></a><a name="p1620208923093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row707746578093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gpio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the GPIO pin number. </td>
</tr>
<tr id="row578188182093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">dir</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the direction to set. For details, see <a href="gpio.md#ga71f27d3ba7ca04d9448199fca38ae19d">GpioDirType</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the GPIO pin direction is successfully set; returns a negative value otherwise. 



## GpioSetIrq\(\)<a name="ga6ea5d16b8d73cb74e36d367f05cb7f6e"></a>

```
int32_t GpioSetIrq (uint16_t gpio, uint16_t mode, [GpioIrqFunc](gpio.md#ga8f3b7d0f0aaa1da8117781efe4b1670e) func, void * arg )
```

 **Description:**

Sets the ISR function for a GPIO pin. 

Before using a GPIO pin as an interrupt, you must call this function to set an ISR function for this GPIO pin, including the ISR parameters and the interrupt trigger mode. After the setting is successful, you also need to call  [GpioEnableIrq](gpio.md#gafcf00796a949245d665e672ae0294aee)  to enable the interrupt, so that the ISR function can respond correctly.

**Parameters:**

<a name="table1558554865093521"></a>
<table><thead align="left"><tr id="row1137417484093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p2039967137093521"><a name="p2039967137093521"></a><a name="p2039967137093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p917812213093521"><a name="p917812213093521"></a><a name="p917812213093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row220698980093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gpio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the GPIO pin number. </td>
</tr>
<tr id="row666233774093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the interrupt trigger mode. For details, see <a href="osal.md#gga78cd126b10424753db6f39f9b72ea124ab98297946a624d99a3fad6adac899f2c">OSAL_IRQF_TRIGGER_RISING</a>. </td>
</tr>
<tr id="row1087423234093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">func</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the ISR function to set, which is specified by <a href="gpio.md#ga8f3b7d0f0aaa1da8117781efe4b1670e">GpioIrqFunc</a>. </td>
</tr>
<tr id="row1619588608093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">arg</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the parameters passed to the ISR function.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the ISR function of the GPIO pin is successfully set; returns a negative value otherwise. 



## GpioUnSetIrq\(\)<a name="ga0e417971d72956f64a3160525c2be19f"></a>

```
int32_t GpioUnSetIrq (uint16_t gpio)
```

 **Description:**

Cancels the setting of the ISR function for a GPIO pin. 

If you do not need the GPIO pin as an interrupt, call this function to cancel the ISR function set via  [GpioSetIrq](gpio.md#ga6ea5d16b8d73cb74e36d367f05cb7f6e). Since this ISR function is no longer valid, you are advised to use  [GpioDisableIrq](gpio.md#gafa01dc510f26d5aff102d72679920929)  to disable the GPIO pin interrupt.

**Parameters:**

<a name="table1685595681093521"></a>
<table><thead align="left"><tr id="row1674409793093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1705141597093521"><a name="p1705141597093521"></a><a name="p1705141597093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p175379192093521"><a name="p175379192093521"></a><a name="p175379192093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row212976678093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gpio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the GPIO pin number.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the ISR function of the GPIO pin is successfully cancelled; returns a negative value otherwise. 



## GpioWrite\(\)<a name="ga7dee8242ba9335b3217635ba64764bc4"></a>

```
int32_t GpioWrite (uint16_t gpio, uint16_t val )
```

 **Description:**

Writes the level value for a GPIO pin. 

Before using this function, you need to call  [GpioSetDir](gpio.md#ga5c628216d209fa76c69eca69856bc0ae)  to set the GPIO pin direction to output.

**Parameters:**

<a name="table1180578998093521"></a>
<table><thead align="left"><tr id="row1069690891093521"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p495289818093521"><a name="p495289818093521"></a><a name="p495289818093521"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p53440548093521"><a name="p53440548093521"></a><a name="p53440548093521"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2100556819093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">gpio</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the GPIO pin number. </td>
</tr>
<tr id="row717887841093521"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">val</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the level value to be written. For details, see <a href="gpio.md#ga6a25a3efddf2301c7b01a7f0af44fb11">GpioValue</a>.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the GPIO pin level value is successfully written; returns a negative value otherwise. 



