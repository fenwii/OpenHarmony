# wifiiot\_uart.h<a name="EN-US_TOPIC_0000001054715057"></a>

## **Overview**<a name="section347491462191857"></a>

**Related Modules:**

[Wifiiot](wifiiot.md)

**Description:**

Declares the UART interface functions. 

These functions are used for UART initialization, data input/output, and data flow control. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section306766326191857"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1584297228191857"></a>
<table><thead align="left"><tr id="row508504152191857"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1608815909191857"><a name="p1608815909191857"></a><a name="p1608815909191857"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p923852385191857"><a name="p923852385191857"></a><a name="p923852385191857"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row2094308786191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p807250116191857"><a name="p807250116191857"></a><a name="p807250116191857"></a><a href="wifiiotuartattribute.md">WifiIotUartAttribute</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p448937023191857"><a name="p448937023191857"></a><a name="p448937023191857"></a>Defines the basic attributes of a UART device. </p>
</td>
</tr>
<tr id="row1261450262191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p536877146191857"><a name="p536877146191857"></a><a name="p536877146191857"></a><a href="wifiiotuartextraattr.md">WifiIotUartExtraAttr</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1074507306191857"><a name="p1074507306191857"></a><a name="p1074507306191857"></a>Defines the extended attributes of a UART device. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table1017270322191857"></a>
<table><thead align="left"><tr id="row1185399149191857"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p746468269191857"><a name="p746468269191857"></a><a name="p746468269191857"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1406109388191857"><a name="p1406109388191857"></a><a name="p1406109388191857"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1446598124191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2117840979191857"><a name="p2117840979191857"></a><a name="p2117840979191857"></a><a href="wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> { <a href="wifiiot.md#gga2699252424e5469ef243ae279a263c44a857a6dfad592ed99b2d8bb33d904efc1">WIFI_IOT_UART_IDX_0</a>, <a href="wifiiot.md#gga2699252424e5469ef243ae279a263c44afb78269eebd0488de767da02fd576c97">WIFI_IOT_UART_IDX_1</a>, <a href="wifiiot.md#gga2699252424e5469ef243ae279a263c44afe10e4ecae6f290980243f74c0582e8f">WIFI_IOT_UART_IDX_2</a>, <a href="wifiiot.md#gga2699252424e5469ef243ae279a263c44a4f01b665c25a5c2fb4188156c138a13d">WIFI_IOT_UART_IDX_MAX</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1245939348191857"><a name="p1245939348191857"></a><a name="p1245939348191857"></a>Enumerates the UART serial number. </p>
</td>
</tr>
<tr id="row1684554456191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1966342076191857"><a name="p1966342076191857"></a><a name="p1966342076191857"></a><a href="wifiiot.md#gafdf1adfc0e0ed18282aa3006300b12b4">WifiIotUartIdxDataBit</a> { <a href="wifiiot.md#ggafdf1adfc0e0ed18282aa3006300b12b4afd012e7a4332f70fd227e3471adf337b">WIFI_IOT_UART_DATA_BIT_5</a> = 5, <a href="wifiiot.md#ggafdf1adfc0e0ed18282aa3006300b12b4aff9e05b0da6c4120371c89d0c07e25b8">WIFI_IOT_UART_DATA_BIT_6</a>, <a href="wifiiot.md#ggafdf1adfc0e0ed18282aa3006300b12b4a45121424f9ea54a738fbb976ff3e9bee">WIFI_IOT_UART_DATA_BIT_7</a>, <a href="wifiiot.md#ggafdf1adfc0e0ed18282aa3006300b12b4a2dd7698b7154c4905e6908336347ddb1">WIFI_IOT_UART_DATA_BIT_8</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1503511033191857"><a name="p1503511033191857"></a><a name="p1503511033191857"></a>Enumerates the number of UART data bits. </p>
</td>
</tr>
<tr id="row240724089191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1726019100191857"><a name="p1726019100191857"></a><a name="p1726019100191857"></a><a href="wifiiot.md#gab0a1b43e8e98b028717e6557003b3172">WifiIotUartStopBit</a> { <a href="wifiiot.md#ggab0a1b43e8e98b028717e6557003b3172accbf9f04cf5f1e8203ead9d5663ee8e8">WIFI_IOT_UART_STOP_BIT_1</a> = 1, <a href="wifiiot.md#ggab0a1b43e8e98b028717e6557003b3172a6c40d45a17b4c9d38696284d01faa8e8">WIFI_IOT_UART_STOP_BIT_2</a> = 2 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p796200531191857"><a name="p796200531191857"></a><a name="p796200531191857"></a>Enumerates the number of UART stop bits. </p>
</td>
</tr>
<tr id="row1084716311191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p866608521191857"><a name="p866608521191857"></a><a name="p866608521191857"></a><a href="wifiiot.md#ga9cee98ab295d2e42ab7f0fb614268602">WifiIotUartParity</a> { <a href="wifiiot.md#gga9cee98ab295d2e42ab7f0fb614268602aaa5d06991c6d267b87c8b2e89e3bae4b">WIFI_IOT_UART_PARITY_NONE</a> = 0, <a href="wifiiot.md#gga9cee98ab295d2e42ab7f0fb614268602a2552846d7dac988f292b2495a6a3b193">WIFI_IOT_UART_PARITY_ODD</a> = 1, <a href="wifiiot.md#gga9cee98ab295d2e42ab7f0fb614268602af4deb913ecbe142ef3df8e9f0b985e36">WIFI_IOT_UART_PARITY_EVEN</a> = 2 }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1277263355191857"><a name="p1277263355191857"></a><a name="p1277263355191857"></a>Enumerates the UART parity bit. </p>
</td>
</tr>
<tr id="row2043742027191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1796305788191857"><a name="p1796305788191857"></a><a name="p1796305788191857"></a><a href="wifiiot.md#ga1c15f86994b472d35bee5d6b57d42a49">WifiIotUartFifoLine</a> {   <a href="wifiiot.md#gga1c15f86994b472d35bee5d6b57d42a49a3003d4ad2672ef855b80317b708a0fdb">WIFI_IOT_FIFO_LINE_ONE_EIGHT</a> = 1, <a href="wifiiot.md#gga1c15f86994b472d35bee5d6b57d42a49af9a3ea60c05bd3cc8cc793d358543f7c">WIFI_IOT_FIFO_LINE_ONE_QUARTER</a>, <a href="wifiiot.md#gga1c15f86994b472d35bee5d6b57d42a49a3f8731dc0941726af9cd00ba1b2bf3ee">WIFI_IOT_FIFO_LINE_HALF</a>, <a href="wifiiot.md#gga1c15f86994b472d35bee5d6b57d42a49aac418922b4708891f9b35b7169569eae">WIFI_IOT_FIFO_LINE_THREE_QUARTERS</a>,   <a href="wifiiot.md#gga1c15f86994b472d35bee5d6b57d42a49a6fb9cbffe9467f79f72bd49f504d6407">WIFI_IOT_FIFO_LINE_SEVEN_EIGHTS</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p627855817191857"><a name="p627855817191857"></a><a name="p627855817191857"></a>Enumerates UART FIFO interrupt thresholds. </p>
</td>
</tr>
<tr id="row360887087191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1136723319191857"><a name="p1136723319191857"></a><a name="p1136723319191857"></a><a href="wifiiot.md#ga93f35a58dc54e29d4892d1e94179c72d">WifiIotUartBlockState</a> { <a href="wifiiot.md#gga93f35a58dc54e29d4892d1e94179c72da4c82baa44ed8c8c48f3a0f4659e9a05b">WIFI_IOT_UART_BLOCK_STATE_NONE_BLOCK</a> = 1, <a href="wifiiot.md#gga93f35a58dc54e29d4892d1e94179c72da17f7be87206b00b8e42a5ab3d48be1de">WIFI_IOT_UART_BLOCK_STATE_BLOCK</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1993759260191857"><a name="p1993759260191857"></a><a name="p1993759260191857"></a>Enumerates UART block states. </p>
</td>
</tr>
<tr id="row1752305814191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1239723128191857"><a name="p1239723128191857"></a><a name="p1239723128191857"></a><a href="wifiiot.md#gaf36ed6a640d85e79dfee020131e0d86f">WifiIotUartDmaState</a> { <a href="wifiiot.md#ggaf36ed6a640d85e79dfee020131e0d86fa7c272d8288c6a14d6f8a663e6aa148c7">WIFI_IOT_UART_NONE_DMA</a> = 1, <a href="wifiiot.md#ggaf36ed6a640d85e79dfee020131e0d86facdc483dbfb6421d1604e1b2008fac7ac">WIFI_IOT_UART_USE_DMA</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p186961027191857"><a name="p186961027191857"></a><a name="p186961027191857"></a>Enumerates UART DMA states. </p>
</td>
</tr>
<tr id="row1953730259191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p148288452191857"><a name="p148288452191857"></a><a name="p148288452191857"></a><a href="wifiiot.md#gacf7ec5d973706e8239c7c6e4a470d8ab">WifiIotFlowCtrl</a> { <a href="wifiiot.md#ggacf7ec5d973706e8239c7c6e4a470d8aba90bfc480060d1a4e23805dd0512fe428">WIFI_IOT_FLOW_CTRL_NONE</a>, <a href="wifiiot.md#ggacf7ec5d973706e8239c7c6e4a470d8aba0abb36c9eb6e80ed338f99d87d3ebfbf">WIFI_IOT_FLOW_CTRL_RTS_CTS</a>, <a href="wifiiot.md#ggacf7ec5d973706e8239c7c6e4a470d8aba92b50039dcab731820e2b360ab9ecaeb">WIFI_IOT_FLOW_CTRL_RTS_ONLY</a>, <a href="wifiiot.md#ggacf7ec5d973706e8239c7c6e4a470d8aba470242c7e05e69b3e24de131bdd418ae">WIFI_IOT_FLOW_CTRL_CTS_ONLY</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1088996256191857"><a name="p1088996256191857"></a><a name="p1088996256191857"></a>Enumerates hardware flow control modes. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table719220560191857"></a>
<table><thead align="left"><tr id="row1483575991191857"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p641219847191857"><a name="p641219847191857"></a><a name="p641219847191857"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p711553596191857"><a name="p711553596191857"></a><a name="p711553596191857"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row523222382191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1187228858191857"><a name="p1187228858191857"></a><a name="p1187228858191857"></a><a href="wifiiot.md#gabd8789246727fe776404b03814822376">UartInit</a> (<a href="wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> id, const <a href="wifiiotuartattribute.md">WifiIotUartAttribute</a> *param, const <a href="wifiiotuartextraattr.md">WifiIotUartExtraAttr</a> *extraAttr)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p154740033191857"><a name="p154740033191857"></a><a name="p154740033191857"></a>unsigned int </p>
<p id="p1281134733191857"><a name="p1281134733191857"></a><a name="p1281134733191857"></a>Configures a UART device. </p>
</td>
</tr>
<tr id="row1153241061191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1741383202191857"><a name="p1741383202191857"></a><a name="p1741383202191857"></a><a href="wifiiot.md#ga048ac867ce0e1cac9b588840e8a50d1d">UartRead</a> (<a href="wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> id, unsigned char *data, unsigned int dataLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1152208069191857"><a name="p1152208069191857"></a><a name="p1152208069191857"></a>int </p>
<p id="p13712809191857"><a name="p13712809191857"></a><a name="p13712809191857"></a>Reads data from a UART device. </p>
</td>
</tr>
<tr id="row81533019191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p613281461191857"><a name="p613281461191857"></a><a name="p613281461191857"></a><a href="wifiiot.md#gaac619810d8212e36ac8fbbc133d6308c">UartWrite</a> (<a href="wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> id, const unsigned char *data, unsigned int dataLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1626032021191857"><a name="p1626032021191857"></a><a name="p1626032021191857"></a>int </p>
<p id="p1074749995191857"><a name="p1074749995191857"></a><a name="p1074749995191857"></a>Writes data to a UART device. </p>
</td>
</tr>
<tr id="row1986657303191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1462388678191857"><a name="p1462388678191857"></a><a name="p1462388678191857"></a><a href="wifiiot.md#gaa0519aee188e7def8ea1e76caaabab7b">UartDeinit</a> (<a href="wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> id)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p657035054191857"><a name="p657035054191857"></a><a name="p657035054191857"></a>unsigned int </p>
<p id="p913831767191857"><a name="p913831767191857"></a><a name="p913831767191857"></a>Deinitializes a UART device. </p>
</td>
</tr>
<tr id="row1668484757191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p515850217191857"><a name="p515850217191857"></a><a name="p515850217191857"></a><a href="wifiiot.md#ga5ae5acc039c3446225daf8b1b60a89d1">UartSetFlowCtrl</a> (<a href="wifiiot.md#ga2699252424e5469ef243ae279a263c44">WifiIotUartIdx</a> id, <a href="wifiiot.md#gacf7ec5d973706e8239c7c6e4a470d8ab">WifiIotFlowCtrl</a> flowCtrl)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1346929998191857"><a name="p1346929998191857"></a><a name="p1346929998191857"></a>unsigned int </p>
<p id="p190061216191857"><a name="p190061216191857"></a><a name="p190061216191857"></a>Sets UART hardware flow control. </p>
</td>
</tr>
</tbody>
</table>

