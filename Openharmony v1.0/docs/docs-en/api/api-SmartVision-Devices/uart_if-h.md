# uart\_if.h<a name="EN-US_TOPIC_0000001055039498"></a>

## **Overview**<a name="section4900870093527"></a>

**Related Modules:**

[UART](uart.md)

**Description:**

Declares standard UART APIs. 

**Since:**

1.0

## **Summary**<a name="section1485813573093527"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1624930839093527"></a>
<table><thead align="left"><tr id="row1576081718093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p479694904093527"><a name="p479694904093527"></a><a name="p479694904093527"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p305471414093527"><a name="p305471414093527"></a><a name="p305471414093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row195678275093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p430760983093527"><a name="p430760983093527"></a><a name="p430760983093527"></a><a href="uartattribute.md">UartAttribute</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1590311422093527"><a name="p1590311422093527"></a><a name="p1590311422093527"></a>Defines basic attributes of the UART port. </p>
</td>
</tr>
</tbody>
</table>

## Macros<a name="define-members"></a>

<a name="table267910755093527"></a>
<table><thead align="left"><tr id="row1638574849093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1124319015093527"><a name="p1124319015093527"></a><a name="p1124319015093527"></a>Macro Name and Value</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p957128434093527"><a name="p957128434093527"></a><a name="p957128434093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1637276026093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p479973437093527"><a name="p479973437093527"></a><a name="p479973437093527"></a><a href="uart_if-h.md#af5e815055116901ca2031dfa07aab973">UART_ATTR_DATABIT_8</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2111789724093527"><a name="p2111789724093527"></a><a name="p2111789724093527"></a>Indicates the UART word length, which is 8 data bits per frame. </p>
</td>
</tr>
<tr id="row94414899093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1486986110093527"><a name="p1486986110093527"></a><a name="p1486986110093527"></a><a href="uart_if-h.md#a1a0f284bb3f73eb5f410a3b800f05c3d">UART_ATTR_DATABIT_7</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p547053454093527"><a name="p547053454093527"></a><a name="p547053454093527"></a>Indicates the UART word length, which is 7 data bits per frame. </p>
</td>
</tr>
<tr id="row564913763093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1581206974093527"><a name="p1581206974093527"></a><a name="p1581206974093527"></a><a href="uart_if-h.md#a0170d90e903308157615a9d492522a45">UART_ATTR_DATABIT_6</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p43166249093527"><a name="p43166249093527"></a><a name="p43166249093527"></a>Indicates the UART word length, which is 6 data bits per frame. </p>
</td>
</tr>
<tr id="row1629846167093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p689691590093527"><a name="p689691590093527"></a><a name="p689691590093527"></a><a href="uart_if-h.md#af7add98615bfa0f6b9fa612aefcb1a86">UART_ATTR_DATABIT_5</a>   3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p656397699093527"><a name="p656397699093527"></a><a name="p656397699093527"></a>Indicates the UART word length, which is 5 data bits per frame. </p>
</td>
</tr>
<tr id="row1705425608093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1694761609093527"><a name="p1694761609093527"></a><a name="p1694761609093527"></a><a href="uart_if-h.md#a4babcc869fd207988d961ccca101abd2">UART_ATTR_PARITY_NONE</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1417272971093527"><a name="p1417272971093527"></a><a name="p1417272971093527"></a>Indicates that the UART device has no parity bit. </p>
</td>
</tr>
<tr id="row1202301849093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1749969521093527"><a name="p1749969521093527"></a><a name="p1749969521093527"></a><a href="uart_if-h.md#a5fee103697a67af905c21a2107141ceb">UART_ATTR_PARITY_ODD</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p749088985093527"><a name="p749088985093527"></a><a name="p749088985093527"></a>Indicates that the UART device has an odd parity bit. </p>
</td>
</tr>
<tr id="row1589773847093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1369867932093527"><a name="p1369867932093527"></a><a name="p1369867932093527"></a><a href="uart_if-h.md#a9f3c0d0f62f5d9320567948fd4d92be2">UART_ATTR_PARITY_EVEN</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1473693677093527"><a name="p1473693677093527"></a><a name="p1473693677093527"></a>Indicates that the UART device has an even parity bit. </p>
</td>
</tr>
<tr id="row1636289564093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p467521476093527"><a name="p467521476093527"></a><a name="p467521476093527"></a><a href="uart_if-h.md#a22c4b8c1eb660d64564900a2088bd1ee">UART_ATTR_PARITY_MARK</a>   3</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p115952420093527"><a name="p115952420093527"></a><a name="p115952420093527"></a>Indicates that the parity bit is 1. </p>
</td>
</tr>
<tr id="row2027644398093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1705576967093527"><a name="p1705576967093527"></a><a name="p1705576967093527"></a><a href="uart_if-h.md#a1817d247706383e20fea3699a95a466a">UART_ATTR_PARITY_SPACE</a>   4</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p103653612093527"><a name="p103653612093527"></a><a name="p103653612093527"></a>Indicates that the parity bit is 0. </p>
</td>
</tr>
<tr id="row139524069093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1169461258093527"><a name="p1169461258093527"></a><a name="p1169461258093527"></a><a href="uart_if-h.md#a985cd0b852a617f1265315030bc1cf8c">UART_ATTR_STOPBIT_1</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p449616698093527"><a name="p449616698093527"></a><a name="p449616698093527"></a>Indicates that the UART device has 1 stop bit. </p>
</td>
</tr>
<tr id="row1648640070093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p190294640093527"><a name="p190294640093527"></a><a name="p190294640093527"></a><a href="uart_if-h.md#a2ebde6313789cc5d787c274240f64deb">UART_ATTR_STOPBIT_1P5</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1258210614093527"><a name="p1258210614093527"></a><a name="p1258210614093527"></a>Indicates that the UART device has 1.5 stop bits. </p>
</td>
</tr>
<tr id="row84668351093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p344126867093527"><a name="p344126867093527"></a><a name="p344126867093527"></a><a href="uart_if-h.md#a97875399f1914c0b66c5c6cea59afe38">UART_ATTR_STOPBIT_2</a>   2</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1715701436093527"><a name="p1715701436093527"></a><a name="p1715701436093527"></a>Indicates that the UART device has 2 stop bits. </p>
</td>
</tr>
<tr id="row1779191568093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p984669101093527"><a name="p984669101093527"></a><a name="p984669101093527"></a><a href="uart_if-h.md#a0266381d78b0452a252e195ff9515906">UART_ATTR_RTS_DIS</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p602316918093527"><a name="p602316918093527"></a><a name="p602316918093527"></a>Indicates that <a href="request.md">Request</a> To Send (RTS) is disabled for the UART device. </p>
</td>
</tr>
<tr id="row493967635093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p124292543093527"><a name="p124292543093527"></a><a name="p124292543093527"></a><a href="uart_if-h.md#a7cfdcad6fe75be1ccb06bed6d94da7e6">UART_ATTR_RTS_EN</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p463896249093527"><a name="p463896249093527"></a><a name="p463896249093527"></a>Indicates that RTS is enabled for the UART device. </p>
</td>
</tr>
<tr id="row1636343005093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1821060740093527"><a name="p1821060740093527"></a><a name="p1821060740093527"></a><a href="uart_if-h.md#a326c98b1572b40a83a0e4635eb856e5e">UART_ATTR_CTS_DIS</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1395162325093527"><a name="p1395162325093527"></a><a name="p1395162325093527"></a>Indicates that Clear To Send (CTS) is disabled for the UART device. </p>
</td>
</tr>
<tr id="row1164868689093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p430270146093527"><a name="p430270146093527"></a><a name="p430270146093527"></a><a href="uart_if-h.md#a097c9cebfaf73088fc9e8bea12bfe12f">UART_ATTR_CTS_EN</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1897449765093527"><a name="p1897449765093527"></a><a name="p1897449765093527"></a>Indicates that CTS is enabled for the UART device. </p>
</td>
</tr>
<tr id="row324196087093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p719333132093527"><a name="p719333132093527"></a><a name="p719333132093527"></a><a href="uart_if-h.md#acb395fb111f746ecf37ab86d255024a4">UART_ATTR_RX_FIFO_DIS</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p147045015093527"><a name="p147045015093527"></a><a name="p147045015093527"></a>Indicates that First In First Out (FIFO) is disabled for the receiving UART. </p>
</td>
</tr>
<tr id="row1174770426093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p744747470093527"><a name="p744747470093527"></a><a name="p744747470093527"></a><a href="uart_if-h.md#a1e1fcc1dbf4cfab102ea77fbae2b9bb5">UART_ATTR_RX_FIFO_EN</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p36875678093527"><a name="p36875678093527"></a><a name="p36875678093527"></a>Indicates that FIFO is enabled for the receiving UART. </p>
</td>
</tr>
<tr id="row1437956432093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1878985920093527"><a name="p1878985920093527"></a><a name="p1878985920093527"></a><a href="uart_if-h.md#a220e22bdcc6c4bc4de7c9896a22b0ae2">UART_ATTR_TX_FIFO_DIS</a>   0</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p869002595093527"><a name="p869002595093527"></a><a name="p869002595093527"></a>Indicates that FIFO is disabled for the transmitting UART. </p>
</td>
</tr>
<tr id="row188347080093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1673292556093527"><a name="p1673292556093527"></a><a name="p1673292556093527"></a><a href="uart_if-h.md#aa434b054edcab341947c1c4dd71972eb">UART_ATTR_TX_FIFO_EN</a>   1</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p53611762093527"><a name="p53611762093527"></a><a name="p53611762093527"></a>Indicates that FIFO is enabled for the transmitting UART. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table662707539093527"></a>
<table><thead align="left"><tr id="row1557293483093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p356314504093527"><a name="p356314504093527"></a><a name="p356314504093527"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1433410403093527"><a name="p1433410403093527"></a><a name="p1433410403093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1837651474093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p150175129093527"><a name="p150175129093527"></a><a name="p150175129093527"></a><a href="uart.md#gab9e041a0802a7e24da22215b458bf7db">UartTransMode</a> {   <a href="uart.md#ggab9e041a0802a7e24da22215b458bf7dba969508add5bf29906cb8ed29cc724c12">UART_MODE_RD_BLOCK</a> = 0, <a href="uart.md#ggab9e041a0802a7e24da22215b458bf7dbad3855fe94d0ff6f630d552eed8b9acb1">UART_MODE_RD_NONBLOCK</a>, <a href="uart.md#ggab9e041a0802a7e24da22215b458bf7dba9aaa55c3b790ae8955a015a8f68c2cde">UART_MODE_DMA_RX_EN</a>, <a href="uart.md#ggab9e041a0802a7e24da22215b458bf7dbab33780e5d6e4607bae091771146e70ac">UART_MODE_DMA_RX_DIS</a>,   <a href="uart.md#ggab9e041a0802a7e24da22215b458bf7dbadecd4cef66348d7e9a5c6d1ad122d98a">UART_MODE_DMA_TX_EN</a>, <a href="uart.md#ggab9e041a0802a7e24da22215b458bf7dbab4aee82f37b579d2506c1c1cd36d7a65">UART_MODE_DMA_TX_DIS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p963091240093527"><a name="p963091240093527"></a><a name="p963091240093527"></a>Enumerates UART transmission modes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table133462965093527"></a>
<table><thead align="left"><tr id="row1682636094093527"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1962704383093527"><a name="p1962704383093527"></a><a name="p1962704383093527"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p90383042093527"><a name="p90383042093527"></a><a name="p90383042093527"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row612414594093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p385950719093527"><a name="p385950719093527"></a><a name="p385950719093527"></a><a href="uart.md#ga6ae805c768e6deea29c6228ea76c8488">UartOpen</a> (uint32_t port)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p973745404093527"><a name="p973745404093527"></a><a name="p973745404093527"></a>struct <a href="devhandle.md">DevHandle</a> * </p>
<p id="p1160200787093527"><a name="p1160200787093527"></a><a name="p1160200787093527"></a>Obtains the UART device handle. </p>
</td>
</tr>
<tr id="row1464353367093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1273698839093527"><a name="p1273698839093527"></a><a name="p1273698839093527"></a><a href="uart.md#ga74b8204f8ac55c11b987e39ffdbb3b15">UartClose</a> (struct <a href="devhandle.md">DevHandle</a> *handle)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1669185606093527"><a name="p1669185606093527"></a><a name="p1669185606093527"></a>void </p>
<p id="p669420015093527"><a name="p669420015093527"></a><a name="p669420015093527"></a>Releases the UART device handle. </p>
</td>
</tr>
<tr id="row882401123093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p419485129093527"><a name="p419485129093527"></a><a name="p419485129093527"></a><a href="uart.md#ga54a3b29fa5873a7b8c28ed3e6b3a3b01">UartRead</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p140534119093527"><a name="p140534119093527"></a><a name="p140534119093527"></a>int32_t </p>
<p id="p1604485254093527"><a name="p1604485254093527"></a><a name="p1604485254093527"></a>Reads data of a specified size from a UART device. </p>
</td>
</tr>
<tr id="row478078031093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p545069818093527"><a name="p545069818093527"></a><a name="p545069818093527"></a><a href="uart.md#ga691854921cfab7bf37432cf3e7421eeb">UartWrite</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint8_t *data, uint32_t size)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p123306622093527"><a name="p123306622093527"></a><a name="p123306622093527"></a>int32_t </p>
<p id="p573421610093527"><a name="p573421610093527"></a><a name="p573421610093527"></a>Writes data of a specified size into a UART device. </p>
</td>
</tr>
<tr id="row2087284478093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p788155434093527"><a name="p788155434093527"></a><a name="p788155434093527"></a><a href="uart.md#gad772be330d172d19feea0a080f88dd74">UartGetBaud</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t *baudRate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p3049900093527"><a name="p3049900093527"></a><a name="p3049900093527"></a>int32_t </p>
<p id="p494579193093527"><a name="p494579193093527"></a><a name="p494579193093527"></a>Obtains the baud rate of the UART device. </p>
</td>
</tr>
<tr id="row1915098509093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p415182898093527"><a name="p415182898093527"></a><a name="p415182898093527"></a><a href="uart.md#ga0877da0a10ad2b159d7cdb65137ed570">UartSetBaud</a> (struct <a href="devhandle.md">DevHandle</a> *handle, uint32_t baudRate)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1801096035093527"><a name="p1801096035093527"></a><a name="p1801096035093527"></a>int32_t </p>
<p id="p1009914343093527"><a name="p1009914343093527"></a><a name="p1009914343093527"></a>Sets the baud rate for the UART device. </p>
</td>
</tr>
<tr id="row639563052093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p370485474093527"><a name="p370485474093527"></a><a name="p370485474093527"></a><a href="uart.md#ga84e704c1f1dafd2a8c5fb44229834bf4">UartGetAttribute</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="uartattribute.md">UartAttribute</a> *attribute)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p846432300093527"><a name="p846432300093527"></a><a name="p846432300093527"></a>int32_t </p>
<p id="p776272685093527"><a name="p776272685093527"></a><a name="p776272685093527"></a>Obtains the UART attribute. </p>
</td>
</tr>
<tr id="row496523685093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p256990546093527"><a name="p256990546093527"></a><a name="p256990546093527"></a><a href="uart.md#gadb447d9e1624cf778175af2d827c9d67">UartSetAttribute</a> (struct <a href="devhandle.md">DevHandle</a> *handle, struct <a href="uartattribute.md">UartAttribute</a> *attribute)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1550688130093527"><a name="p1550688130093527"></a><a name="p1550688130093527"></a>int32_t </p>
<p id="p658680631093527"><a name="p658680631093527"></a><a name="p658680631093527"></a>Sets the UART attribute. </p>
</td>
</tr>
<tr id="row264008761093527"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p657786213093527"><a name="p657786213093527"></a><a name="p657786213093527"></a><a href="uart.md#ga30c7e8742c049e6407333693da039a97">UartSetTransMode</a> (struct <a href="devhandle.md">DevHandle</a> *handle, enum <a href="uart.md#gab9e041a0802a7e24da22215b458bf7db">UartTransMode</a> mode)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1589458981093527"><a name="p1589458981093527"></a><a name="p1589458981093527"></a>int32_t </p>
<p id="p1241233022093527"><a name="p1241233022093527"></a><a name="p1241233022093527"></a>Sets the UART transmission mode. </p>
</td>
</tr>
</tbody>
</table>

## **Details**<a name="section1799215568093527"></a>

## **Macro Definition Documentation**<a name="section1742437954093527"></a>

## UART\_ATTR\_CTS\_DIS<a name="a326c98b1572b40a83a0e4635eb856e5e"></a>

```
#define UART_ATTR_CTS_DIS   0
```

 **Description:**

Indicates that Clear To Send \(CTS\) is disabled for the UART device. 

## UART\_ATTR\_CTS\_EN<a name="a097c9cebfaf73088fc9e8bea12bfe12f"></a>

```
#define UART_ATTR_CTS_EN   1
```

 **Description:**

Indicates that CTS is enabled for the UART device. 

## UART\_ATTR\_DATABIT\_5<a name="af7add98615bfa0f6b9fa612aefcb1a86"></a>

```
#define UART_ATTR_DATABIT_5   3
```

 **Description:**

Indicates the UART word length, which is 5 data bits per frame. 

## UART\_ATTR\_DATABIT\_6<a name="a0170d90e903308157615a9d492522a45"></a>

```
#define UART_ATTR_DATABIT_6   2
```

 **Description:**

Indicates the UART word length, which is 6 data bits per frame. 

## UART\_ATTR\_DATABIT\_7<a name="a1a0f284bb3f73eb5f410a3b800f05c3d"></a>

```
#define UART_ATTR_DATABIT_7   1
```

 **Description:**

Indicates the UART word length, which is 7 data bits per frame. 

## UART\_ATTR\_DATABIT\_8<a name="af5e815055116901ca2031dfa07aab973"></a>

```
#define UART_ATTR_DATABIT_8   0
```

 **Description:**

Indicates the UART word length, which is 8 data bits per frame. 

## UART\_ATTR\_PARITY\_EVEN<a name="a9f3c0d0f62f5d9320567948fd4d92be2"></a>

```
#define UART_ATTR_PARITY_EVEN   2
```

 **Description:**

Indicates that the UART device has an even parity bit. 

## UART\_ATTR\_PARITY\_MARK<a name="a22c4b8c1eb660d64564900a2088bd1ee"></a>

```
#define UART_ATTR_PARITY_MARK   3
```

 **Description:**

Indicates that the parity bit is 1. 

## UART\_ATTR\_PARITY\_NONE<a name="a4babcc869fd207988d961ccca101abd2"></a>

```
#define UART_ATTR_PARITY_NONE   0
```

 **Description:**

Indicates that the UART device has no parity bit. 

## UART\_ATTR\_PARITY\_ODD<a name="a5fee103697a67af905c21a2107141ceb"></a>

```
#define UART_ATTR_PARITY_ODD   1
```

 **Description:**

Indicates that the UART device has an odd parity bit. 

## UART\_ATTR\_PARITY\_SPACE<a name="a1817d247706383e20fea3699a95a466a"></a>

```
#define UART_ATTR_PARITY_SPACE   4
```

 **Description:**

Indicates that the parity bit is 0. 

## UART\_ATTR\_RTS\_DIS<a name="a0266381d78b0452a252e195ff9515906"></a>

```
#define UART_ATTR_RTS_DIS   0
```

 **Description:**

Indicates that  [Request](request.md)  To Send \(RTS\) is disabled for the UART device. 

## UART\_ATTR\_RTS\_EN<a name="a7cfdcad6fe75be1ccb06bed6d94da7e6"></a>

```
#define UART_ATTR_RTS_EN   1
```

 **Description:**

Indicates that RTS is enabled for the UART device. 

## UART\_ATTR\_RX\_FIFO\_DIS<a name="acb395fb111f746ecf37ab86d255024a4"></a>

```
#define UART_ATTR_RX_FIFO_DIS   0
```

 **Description:**

Indicates that First In First Out \(FIFO\) is disabled for the receiving UART. 

## UART\_ATTR\_RX\_FIFO\_EN<a name="a1e1fcc1dbf4cfab102ea77fbae2b9bb5"></a>

```
#define UART_ATTR_RX_FIFO_EN   1
```

 **Description:**

Indicates that FIFO is enabled for the receiving UART. 

## UART\_ATTR\_STOPBIT\_1<a name="a985cd0b852a617f1265315030bc1cf8c"></a>

```
#define UART_ATTR_STOPBIT_1   0
```

 **Description:**

Indicates that the UART device has 1 stop bit. 

## UART\_ATTR\_STOPBIT\_1P5<a name="a2ebde6313789cc5d787c274240f64deb"></a>

```
#define UART_ATTR_STOPBIT_1P5   1
```

 **Description:**

Indicates that the UART device has 1.5 stop bits. 

## UART\_ATTR\_STOPBIT\_2<a name="a97875399f1914c0b66c5c6cea59afe38"></a>

```
#define UART_ATTR_STOPBIT_2   2
```

 **Description:**

Indicates that the UART device has 2 stop bits. 

## UART\_ATTR\_TX\_FIFO\_DIS<a name="a220e22bdcc6c4bc4de7c9896a22b0ae2"></a>

```
#define UART_ATTR_TX_FIFO_DIS   0
```

 **Description:**

Indicates that FIFO is disabled for the transmitting UART. 

## UART\_ATTR\_TX\_FIFO\_EN<a name="aa434b054edcab341947c1c4dd71972eb"></a>

```
#define UART_ATTR_TX_FIFO_EN   1
```

 **Description:**

Indicates that FIFO is enabled for the transmitting UART. 

