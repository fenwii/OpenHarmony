# gpio\_if.h<a name="ZH-CN_TOPIC_0000001055518056"></a>

## **Overview**<a name="section1944668999093525"></a>

**Related Modules:**

[GPIO](GPIO.md)

**Description:**

Declares the standard GPIO interface functions. 

**Since:**

1.0

## **Summary**<a name="section1727731254093525"></a>

## Typedefs<a name="typedef-members"></a>

<a name="table1589337186093525"></a>
<table><thead align="left"><tr id="row1416172452093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1195878570093525"><a name="p1195878570093525"></a><a name="p1195878570093525"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2058372822093525"><a name="p2058372822093525"></a><a name="p2058372822093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1515464930093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1731801660093525"><a name="p1731801660093525"></a><a name="p1731801660093525"></a><a href="GPIO.md#ga8f3b7d0f0aaa1da8117781efe4b1670e">GpioIrqFunc</a>) (uint16_t gpio, void *data)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1526421391093525"><a name="p1526421391093525"></a><a name="p1526421391093525"></a>typedef int32_t(*&nbsp;</p>
<p id="p531480224093525"><a name="p531480224093525"></a><a name="p531480224093525"></a>Defines the function type of a GPIO interrupt service routine (ISR). </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table406964366093525"></a>
<table><thead align="left"><tr id="row1321215397093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1465394970093525"><a name="p1465394970093525"></a><a name="p1465394970093525"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p353972010093525"><a name="p353972010093525"></a><a name="p353972010093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1541721609093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2040196149093525"><a name="p2040196149093525"></a><a name="p2040196149093525"></a><a href="GPIO.md#ga6a25a3efddf2301c7b01a7f0af44fb11">GpioValue</a> { <a href="GPIO.md#gga6a25a3efddf2301c7b01a7f0af44fb11aff32e096d7022208ae0dc00c95bd8e08">GPIO_VAL_LOW</a> = 0, <a href="GPIO.md#gga6a25a3efddf2301c7b01a7f0af44fb11a9b9c172b01ce33bb20764c8dd5c7835f">GPIO_VAL_HIGH</a> = 1, <a href="GPIO.md#gga6a25a3efddf2301c7b01a7f0af44fb11a6f009070245b6c7d3b48e990b2cc133a">GPIO_VAL_ERR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p891849267093525"><a name="p891849267093525"></a><a name="p891849267093525"></a>Enumerates GPIO level values. </p>
</td>
</tr>
<tr id="row794582949093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p878821529093525"><a name="p878821529093525"></a><a name="p878821529093525"></a><a href="GPIO.md#ga71f27d3ba7ca04d9448199fca38ae19d">GpioDirType</a> { <a href="GPIO.md#gga71f27d3ba7ca04d9448199fca38ae19da3881053acb92aad7798425cdbb565fff">GPIO_DIR_IN</a> = 0, <a href="GPIO.md#gga71f27d3ba7ca04d9448199fca38ae19da73c68266253638e2246dda97a0d65d91">GPIO_DIR_OUT</a> = 1, <a href="GPIO.md#gga71f27d3ba7ca04d9448199fca38ae19da13b9029a753d3c4a2fad6f863f5161bd">GPIO_DIR_ERR</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2120219831093525"><a name="p2120219831093525"></a><a name="p2120219831093525"></a>Enumerates GPIO directions. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table1486210797093525"></a>
<table><thead align="left"><tr id="row1294156111093525"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p666628771093525"><a name="p666628771093525"></a><a name="p666628771093525"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p2066031502093525"><a name="p2066031502093525"></a><a name="p2066031502093525"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row618206516093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1788359671093525"><a name="p1788359671093525"></a><a name="p1788359671093525"></a><a href="GPIO.md#ga267cb09db1f12ac3f08f847e4141f3c5">GpioRead</a> (uint16_t gpio, uint16_t *val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p535765376093525"><a name="p535765376093525"></a><a name="p535765376093525"></a>int32_t&nbsp;</p>
<p id="p509720568093525"><a name="p509720568093525"></a><a name="p509720568093525"></a>Reads the level value of a GPIO pin. </p>
</td>
</tr>
<tr id="row2052979895093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1877051775093525"><a name="p1877051775093525"></a><a name="p1877051775093525"></a><a href="GPIO.md#ga7dee8242ba9335b3217635ba64764bc4">GpioWrite</a> (uint16_t gpio, uint16_t val)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p754255742093525"><a name="p754255742093525"></a><a name="p754255742093525"></a>int32_t&nbsp;</p>
<p id="p1741949158093525"><a name="p1741949158093525"></a><a name="p1741949158093525"></a>Writes the level value for a GPIO pin. </p>
</td>
</tr>
<tr id="row182998170093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1321565838093525"><a name="p1321565838093525"></a><a name="p1321565838093525"></a><a href="GPIO.md#ga5c628216d209fa76c69eca69856bc0ae">GpioSetDir</a> (uint16_t gpio, uint16_t dir)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1231789661093525"><a name="p1231789661093525"></a><a name="p1231789661093525"></a>int32_t&nbsp;</p>
<p id="p1708938136093525"><a name="p1708938136093525"></a><a name="p1708938136093525"></a>Sets the input/output direction for a GPIO pin. </p>
</td>
</tr>
<tr id="row1190927522093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1410849678093525"><a name="p1410849678093525"></a><a name="p1410849678093525"></a><a href="GPIO.md#ga6eb1536930b7ec5e263667ba30dfc6fb">GpioGetDir</a> (uint16_t gpio, uint16_t *dir)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2056425586093525"><a name="p2056425586093525"></a><a name="p2056425586093525"></a>int32_t&nbsp;</p>
<p id="p138058763093525"><a name="p138058763093525"></a><a name="p138058763093525"></a>Obtains the input/output direction of a GPIO pin. </p>
</td>
</tr>
<tr id="row1324429715093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p78497656093525"><a name="p78497656093525"></a><a name="p78497656093525"></a><a href="GPIO.md#ga6ea5d16b8d73cb74e36d367f05cb7f6e">GpioSetIrq</a> (uint16_t gpio, uint16_t mode, <a href="GPIO.md#ga8f3b7d0f0aaa1da8117781efe4b1670e">GpioIrqFunc</a> func, void *arg)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1629043579093525"><a name="p1629043579093525"></a><a name="p1629043579093525"></a>int32_t&nbsp;</p>
<p id="p199316244093525"><a name="p199316244093525"></a><a name="p199316244093525"></a>Sets the ISR function for a GPIO pin. </p>
</td>
</tr>
<tr id="row48598003093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1066672345093525"><a name="p1066672345093525"></a><a name="p1066672345093525"></a><a href="GPIO.md#ga0e417971d72956f64a3160525c2be19f">GpioUnSetIrq</a> (uint16_t gpio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1190314442093525"><a name="p1190314442093525"></a><a name="p1190314442093525"></a>int32_t&nbsp;</p>
<p id="p1547979313093525"><a name="p1547979313093525"></a><a name="p1547979313093525"></a>Cancels the setting of the ISR function for a GPIO pin. </p>
</td>
</tr>
<tr id="row635196069093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1007654053093525"><a name="p1007654053093525"></a><a name="p1007654053093525"></a><a href="GPIO.md#gafcf00796a949245d665e672ae0294aee">GpioEnableIrq</a> (uint16_t gpio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1832446299093525"><a name="p1832446299093525"></a><a name="p1832446299093525"></a>int32_t&nbsp;</p>
<p id="p1750477328093525"><a name="p1750477328093525"></a><a name="p1750477328093525"></a>Enables a GPIO pin interrupt. </p>
</td>
</tr>
<tr id="row589998032093525"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1508630448093525"><a name="p1508630448093525"></a><a name="p1508630448093525"></a><a href="GPIO.md#gafa01dc510f26d5aff102d72679920929">GpioDisableIrq</a> (uint16_t gpio)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p144670230093525"><a name="p144670230093525"></a><a name="p144670230093525"></a>int32_t&nbsp;</p>
<p id="p1384590075093525"><a name="p1384590075093525"></a><a name="p1384590075093525"></a>Disables a GPIO pin interrupt. </p>
</td>
</tr>
</tbody>
</table>

