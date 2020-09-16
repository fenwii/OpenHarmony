# UART<a name="ZH-CN_TOPIC_0000001054799549"></a>

## **Overview**<a name="section1195206280084825"></a>

Defines standard APIs of universal asynchronous receiver/transmitter \(UART\) capabilities. 

You can use this module to access the UART and enable the driver to operate a UART-compliant device. The functions in this module help you to obtain and release the UART device handle, read and write data, obtain and set the baud rate and device attributes.

**Since:**

1.0

## **Summary**<a name="section1479405280084825"></a>

## Files<a name="files"></a>

<a name="table56947266084825"></a>
<table><thead align="left"><tr id="row1216775758084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p560802929084825"><a name="p560802929084825"></a><a name="p560802929084825"></a>File Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p519356729084825"><a name="p519356729084825"></a><a name="p519356729084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1756664987084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p365395049084825"><a name="p365395049084825"></a><a name="p365395049084825"></a><a href="uart_if-h.md">uart_if.h</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1136638503084825"><a name="p1136638503084825"></a><a name="p1136638503084825"></a>Declares standard UART APIs. </p>
</td>
</tr>
</tbody>
</table>

## Data Structures<a name="nested-classes"></a>

<a name="table1212179520084825"></a>
<table><thead align="left"><tr id="row1108468800084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p865088880084825"><a name="p865088880084825"></a><a name="p865088880084825"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p968301544084825"><a name="p968301544084825"></a><a name="p968301544084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row810051881084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1315974902084825"><a name="p1315974902084825"></a><a name="p1315974902084825"></a><a href="UartAttribute.md">UartAttribute</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p484560446084825"><a name="p484560446084825"></a><a name="p484560446084825"></a>Defines basic attributes of the UART port. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table217195361084825"></a>
<table><thead align="left"><tr id="row1605660091084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1309098269084825"><a name="p1309098269084825"></a><a name="p1309098269084825"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p79047923084825"><a name="p79047923084825"></a><a name="p79047923084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row660124458084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p247159058084825"><a name="p247159058084825"></a><a name="p247159058084825"></a><a href="UART.md#gab9e041a0802a7e24da22215b458bf7db">UartTransMode</a> { &nbsp;&nbsp;<a href="UART.md#ggab9e041a0802a7e24da22215b458bf7dba969508add5bf29906cb8ed29cc724c12">UART_MODE_RD_BLOCK</a> = 0, <a href="UART.md#ggab9e041a0802a7e24da22215b458bf7dbad3855fe94d0ff6f630d552eed8b9acb1">UART_MODE_RD_NONBLOCK</a>, <a href="UART.md#ggab9e041a0802a7e24da22215b458bf7dba9aaa55c3b790ae8955a015a8f68c2cde">UART_MODE_DMA_RX_EN</a>, <a href="UART.md#ggab9e041a0802a7e24da22215b458bf7dbab33780e5d6e4607bae091771146e70ac">UART_MODE_DMA_RX_DIS</a>, &nbsp;&nbsp;<a href="UART.md#ggab9e041a0802a7e24da22215b458bf7dbadecd4cef66348d7e9a5c6d1ad122d98a">UART_MODE_DMA_TX_EN</a>, <a href="UART.md#ggab9e041a0802a7e24da22215b458bf7dbab4aee82f37b579d2506c1c1cd36d7a65">UART_MODE_DMA_TX_DIS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p954300138084825"><a name="p954300138084825"></a><a name="p954300138084825"></a>Enumerates UART transmission modes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table510914458084825"></a>
<table><thead align="left"><tr id="row472748548084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p17960350084825"><a name="p17960350084825"></a><a name="p17960350084825"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p380506758084825"><a name="p380506758084825"></a><a name="p380506758084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row524266626084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1915810766084825"><a name="p1915810766084825"></a><a name="p1915810766084825"></a><a href="UART.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a> (uint32_t port)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p105462537084825"><a name="p105462537084825"></a><a name="p105462537084825"></a>struct <a href="DevHandle.md">DevHandle</a> *&nbsp;</p>
<p id="p647205479084825"><a name="p647205479084825"></a><a name="p647205479084825"></a>Obtains the UART device handle. </p>
</td>
</tr>
<tr id="row1969318777084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2120755219084825"><a name="p2120755219084825"></a><a name="p2120755219084825"></a><a href="UART.md#ga74b8204f8ac55c11b987e39ffdbb3b15">UartClose</a> (struct <a href="DevHandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1677818840084825"><a name="p1677818840084825"></a><a name="p1677818840084825"></a>void&nbsp;</p>
<p id="p1581209684084825"><a name="p1581209684084825"></a><a name="p1581209684084825"></a>Releases the UART device handle. </p>
</td>
</tr>
<tr id="row249781960084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1906605195084825"><a name="p1906605195084825"></a><a name="p1906605195084825"></a><a href="UART.md#ga54a3b29fa5873a7b8c28ed3e6b3a3b01">UartRead</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p753447933084825"><a name="p753447933084825"></a><a name="p753447933084825"></a>int32_t&nbsp;</p>
<p id="p150373871084825"><a name="p150373871084825"></a><a name="p150373871084825"></a>Reads data of a specified size from a UART device. </p>
</td>
</tr>
<tr id="row1024453673084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1489487546084825"><a name="p1489487546084825"></a><a name="p1489487546084825"></a><a href="UART.md#ga691854921cfab7bf37432cf3e7421eeb">UartWrite</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p819534269084825"><a name="p819534269084825"></a><a name="p819534269084825"></a>int32_t&nbsp;</p>
<p id="p2095131816084825"><a name="p2095131816084825"></a><a name="p2095131816084825"></a>Writes data of a specified size into a UART device. </p>
</td>
</tr>
<tr id="row1597568880084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1757863847084825"><a name="p1757863847084825"></a><a name="p1757863847084825"></a><a href="UART.md#gad772be330d172d19feea0a080f88dd74">UartGetBaud</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint32_t *baudRate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p979307560084825"><a name="p979307560084825"></a><a name="p979307560084825"></a>int32_t&nbsp;</p>
<p id="p538678811084825"><a name="p538678811084825"></a><a name="p538678811084825"></a>Obtains the baud rate of the UART device. </p>
</td>
</tr>
<tr id="row1143241906084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1857983682084825"><a name="p1857983682084825"></a><a name="p1857983682084825"></a><a href="UART.md#ga0877da0a10ad2b159d7cdb65137ed570">UartSetBaud</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, uint32_t baudRate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1418776364084825"><a name="p1418776364084825"></a><a name="p1418776364084825"></a>int32_t&nbsp;</p>
<p id="p296002887084825"><a name="p296002887084825"></a><a name="p296002887084825"></a>Sets the baud rate for the UART device. </p>
</td>
</tr>
<tr id="row2082398979084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p765291659084825"><a name="p765291659084825"></a><a name="p765291659084825"></a><a href="UART.md#ga84e704c1f1dafd2a8c5fb44229834bf4">UartGetAttribute</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, struct <a href="UartAttribute.md">UartAttribute</a> *attribute)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p11294643084825"><a name="p11294643084825"></a><a name="p11294643084825"></a>int32_t&nbsp;</p>
<p id="p899232836084825"><a name="p899232836084825"></a><a name="p899232836084825"></a>Obtains the UART attribute. </p>
</td>
</tr>
<tr id="row293626087084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p748082155084825"><a name="p748082155084825"></a><a name="p748082155084825"></a><a href="UART.md#gadb447d9e1624cf778175af2d827c9d67">UartSetAttribute</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, struct <a href="UartAttribute.md">UartAttribute</a> *attribute)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1220423005084825"><a name="p1220423005084825"></a><a name="p1220423005084825"></a>int32_t&nbsp;</p>
<p id="p1684512435084825"><a name="p1684512435084825"></a><a name="p1684512435084825"></a>Sets the UART attribute. </p>
</td>
</tr>
<tr id="row1958634248084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1609582953084825"><a name="p1609582953084825"></a><a name="p1609582953084825"></a><a href="UART.md#ga30c7e8742c049e6407333693da039a97">UartSetTransMode</a> (struct <a href="DevHandle.md">DevHandle</a> *handle, enum <a href="UART.md#gab9e041a0802a7e24da22215b458bf7db">UartTransMode</a> mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1080335211084825"><a name="p1080335211084825"></a><a name="p1080335211084825"></a>int32_t&nbsp;</p>
<p id="p757762966084825"><a name="p757762966084825"></a><a name="p757762966084825"></a>Sets the UART transmission mode. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section96954936084825"></a>

## **Enumeration Type Documentation**<a name="section203603966084825"></a>

## UartTransMode<a name="gab9e041a0802a7e24da22215b458bf7db"></a>

```
enum [UartTransMode](UART.md#gab9e041a0802a7e24da22215b458bf7db)
```

 **Description:**

Enumerates UART transmission modes. 

**Attention:**

The UART controller determines whether an enumerated transmission mode is supported.


<a name="table302717674084825"></a>
<table><thead align="left"><tr id="row694665449084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1975378746084825"><a name="p1975378746084825"></a><a name="p1975378746084825"></a>Enumerator</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p573495856084825"><a name="p573495856084825"></a><a name="p573495856084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row284209363084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab9e041a0802a7e24da22215b458bf7dba969508add5bf29906cb8ed29cc724c12"><a name="ggab9e041a0802a7e24da22215b458bf7dba969508add5bf29906cb8ed29cc724c12"></a><a name="ggab9e041a0802a7e24da22215b458bf7dba969508add5bf29906cb8ed29cc724c12"></a></strong>UART_MODE_RD_BLOCK&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1699397938084825"><a name="p1699397938084825"></a><a name="p1699397938084825"></a>Blocking mode </p>
 </td>
</tr>
<tr id="row1128366141084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab9e041a0802a7e24da22215b458bf7dbad3855fe94d0ff6f630d552eed8b9acb1"><a name="ggab9e041a0802a7e24da22215b458bf7dbad3855fe94d0ff6f630d552eed8b9acb1"></a><a name="ggab9e041a0802a7e24da22215b458bf7dbad3855fe94d0ff6f630d552eed8b9acb1"></a></strong>UART_MODE_RD_NONBLOCK&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p600742788084825"><a name="p600742788084825"></a><a name="p600742788084825"></a>Non-blocking mode </p>
 </td>
</tr>
<tr id="row449913138084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab9e041a0802a7e24da22215b458bf7dba9aaa55c3b790ae8955a015a8f68c2cde"><a name="ggab9e041a0802a7e24da22215b458bf7dba9aaa55c3b790ae8955a015a8f68c2cde"></a><a name="ggab9e041a0802a7e24da22215b458bf7dba9aaa55c3b790ae8955a015a8f68c2cde"></a></strong>UART_MODE_DMA_RX_EN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1391982930084825"><a name="p1391982930084825"></a><a name="p1391982930084825"></a>DMA enabled for data receiving </p>
 </td>
</tr>
<tr id="row1141855287084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab9e041a0802a7e24da22215b458bf7dbab33780e5d6e4607bae091771146e70ac"><a name="ggab9e041a0802a7e24da22215b458bf7dbab33780e5d6e4607bae091771146e70ac"></a><a name="ggab9e041a0802a7e24da22215b458bf7dbab33780e5d6e4607bae091771146e70ac"></a></strong>UART_MODE_DMA_RX_DIS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p648936481084825"><a name="p648936481084825"></a><a name="p648936481084825"></a>DMA disabled for data receiving </p>
 </td>
</tr>
<tr id="row1760858067084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab9e041a0802a7e24da22215b458bf7dbadecd4cef66348d7e9a5c6d1ad122d98a"><a name="ggab9e041a0802a7e24da22215b458bf7dbadecd4cef66348d7e9a5c6d1ad122d98a"></a><a name="ggab9e041a0802a7e24da22215b458bf7dbadecd4cef66348d7e9a5c6d1ad122d98a"></a></strong>UART_MODE_DMA_TX_EN&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p48368208084825"><a name="p48368208084825"></a><a name="p48368208084825"></a>DMA enabled for data transmitting </p>
 </td>
</tr>
<tr id="row611632096084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><strong id="ggab9e041a0802a7e24da22215b458bf7dbab4aee82f37b579d2506c1c1cd36d7a65"><a name="ggab9e041a0802a7e24da22215b458bf7dbab4aee82f37b579d2506c1c1cd36d7a65"></a><a name="ggab9e041a0802a7e24da22215b458bf7dbab4aee82f37b579d2506c1c1cd36d7a65"></a></strong>UART_MODE_DMA_TX_DIS&nbsp;</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1209038416084825"><a name="p1209038416084825"></a><a name="p1209038416084825"></a>DMA disabled for data transmitting </p>
 </td>
</tr>
</tbody>
</table>

## **Function Documentation**<a name="section137924919084825"></a>

## UartClose\(\)<a name="ga74b8204f8ac55c11b987e39ffdbb3b15"></a>

```
void UartClose (struct [DevHandle](DevHandle.md) * handle)
```

 **Description:**

Releases the UART device handle. 

If you no longer need to access the UART device, you should call this function to close its handle so as to release unused memory resources.

**Parameters:**

<a name="table78848858084825"></a>
<table><thead align="left"><tr id="row134279530084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p705580276084825"><a name="p705580276084825"></a><a name="p705580276084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1532011850084825"><a name="p1532011850084825"></a><a name="p1532011850084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row760697344084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the UART device handle, which is obtained via <a href="UART.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a>.</td>
</tr>
</tbody>
</table>

## UartGetAttribute\(\)<a name="ga84e704c1f1dafd2a8c5fb44229834bf4"></a>

```
int32_t UartGetAttribute (struct [DevHandle](DevHandle.md) * handle, struct [UartAttribute](UartAttribute.md) * attribute )
```

 **Description:**

Obtains the UART attribute. 

UART attributes include data bits, stop bits, parity bit, CTS, RTS, and receiving and transmitting FIFO.

**Parameters:**

<a name="table629140986084825"></a>
<table><thead align="left"><tr id="row453703749084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1613147547084825"><a name="p1613147547084825"></a><a name="p1613147547084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p384481021084825"><a name="p384481021084825"></a><a name="p384481021084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row803790489084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the UART device handle, which is obtained via <a href="UART.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a>. </td>
</tr>
<tr id="row506868311084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attribute</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained UART attribute.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the UART attribute is obtained; returns a negative number otherwise. 



## UartGetBaud\(\)<a name="gad772be330d172d19feea0a080f88dd74"></a>

```
int32_t UartGetBaud (struct [DevHandle](DevHandle.md) * handle, uint32_t * baudRate )
```

 **Description:**

Obtains the baud rate of the UART device. 

**Parameters:**

<a name="table867252447084825"></a>
<table><thead align="left"><tr id="row421101352084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p534878651084825"><a name="p534878651084825"></a><a name="p534878651084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p587414729084825"><a name="p587414729084825"></a><a name="p587414729084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1961628666084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the UART device handle, which is obtained via <a href="UART.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a>. </td>
</tr>
<tr id="row1203811305084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">baudRate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the obtained baud rate.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the baud rate is obtained; returns a negative number otherwise. 



## UartOpen\(\)<a name="ga6ae805c768e6deea29c6228ea76c8488"></a>

```
struct [DevHandle](DevHandle.md)* UartOpen (uint32_t port)
```

 **Description:**

Obtains the UART device handle. 

Before accessing the UART device, you must call this function to obtain the UART device handle.

**Parameters:**

<a name="table1707660011084825"></a>
<table><thead align="left"><tr id="row1658020460084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p587635237084825"><a name="p587635237084825"></a><a name="p587635237084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p968776176084825"><a name="p968776176084825"></a><a name="p968776176084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row424039146084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">port</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the UART port.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the pointer to the UART device handle if the handle is obtained; returns  **NULL**  otherwise. 



## UartRead\(\)<a name="ga54a3b29fa5873a7b8c28ed3e6b3a3b01"></a>

```
int32_t UartRead (struct [DevHandle](DevHandle.md) * handle, uint8_t * data, uint32_t size )
```

 **Description:**

Reads data of a specified size from a UART device. 

**Parameters:**

<a name="table239237885084825"></a>
<table><thead align="left"><tr id="row1024809453084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1430064604084825"><a name="p1430064604084825"></a><a name="p1430064604084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1071588763084825"><a name="p1071588763084825"></a><a name="p1071588763084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2048032409084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the UART device handle, which is obtained via <a href="UART.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a>. </td>
</tr>
<tr id="row2003430481084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the buffer for receiving the data. </td>
</tr>
<tr id="row1002418034084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the data to read.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns the size of the data that is successfully read; returns a negative number if the reading fails. 



## UartSetAttribute\(\)<a name="gadb447d9e1624cf778175af2d827c9d67"></a>

```
int32_t UartSetAttribute (struct [DevHandle](DevHandle.md) * handle, struct [UartAttribute](UartAttribute.md) * attribute )
```

 **Description:**

Sets the UART attribute. 

UART attributes include data bits, stop bits, parity bit, CTS, RTS, and receiving and transmitting FIFO.

**Parameters:**

<a name="table1572178900084825"></a>
<table><thead align="left"><tr id="row1101794957084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p531128949084825"><a name="p531128949084825"></a><a name="p531128949084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1336525168084825"><a name="p1336525168084825"></a><a name="p1336525168084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2132061262084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the UART device handle, which is obtained via <a href="UART.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a>. </td>
</tr>
<tr id="row2025829258084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">attribute</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the UART attribute to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative number otherwise. 



## UartSetBaud\(\)<a name="ga0877da0a10ad2b159d7cdb65137ed570"></a>

```
int32_t UartSetBaud (struct [DevHandle](DevHandle.md) * handle, uint32_t baudRate )
```

 **Description:**

Sets the baud rate for the UART device. 

**Parameters:**

<a name="table1301496674084825"></a>
<table><thead align="left"><tr id="row1986605253084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p584496548084825"><a name="p584496548084825"></a><a name="p584496548084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1401007599084825"><a name="p1401007599084825"></a><a name="p1401007599084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2090288845084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the UART device handle, which is obtained via <a href="UART.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a>. </td>
</tr>
<tr id="row1632853910084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">baudRate</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the baud rate to set.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative number otherwise. 



## UartSetTransMode\(\)<a name="ga30c7e8742c049e6407333693da039a97"></a>

```
int32_t UartSetTransMode (struct [DevHandle](DevHandle.md) * handle, enum [UartTransMode](UART.md#gab9e041a0802a7e24da22215b458bf7db) mode )
```

 **Description:**

Sets the UART transmission mode. 

**Parameters:**

<a name="table1379489027084825"></a>
<table><thead align="left"><tr id="row1876805452084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p391412968084825"><a name="p391412968084825"></a><a name="p391412968084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1070993900084825"><a name="p1070993900084825"></a><a name="p1070993900084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row956078800084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the UART device handle, which is obtained via <a href="UART.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a>. </td>
</tr>
<tr id="row728585290084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">mode</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates a transmission mode enumerated in {@linkUartTransMode}.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the setting is successful; returns a negative number otherwise. 



## UartWrite\(\)<a name="ga691854921cfab7bf37432cf3e7421eeb"></a>

```
int32_t UartWrite (struct [DevHandle](DevHandle.md) * handle, uint8_t * data, uint32_t size )
```

 **Description:**

Writes data of a specified size into a UART device. 

**Parameters:**

<a name="table1358024021084825"></a>
<table><thead align="left"><tr id="row276376104084825"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p23959278084825"><a name="p23959278084825"></a><a name="p23959278084825"></a>Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1004262646084825"><a name="p1004262646084825"></a><a name="p1004262646084825"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row96751975084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">handle</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the UART device handle, which is obtained via <a href="UART.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a>. </td>
</tr>
<tr id="row2055205716084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">data</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the pointer to the data to write. </td>
</tr>
<tr id="row292064288084825"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 ">size</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 ">Indicates the size of the data to write.</td>
</tr>
</tbody>
</table>

**Returns:**

Returns  **0**  if the data is successfully written; returns a negative number otherwise. 



