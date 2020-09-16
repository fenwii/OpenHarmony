# wifiiot\_spi.h<a name="ZH-CN_TOPIC_0000001054915091"></a>

## **Overview**<a name="section185179383191857"></a>

**Related Modules:**

[Wifiiot](Wifiiot.md)

**Description:**

Declares the SPI interface functions. 

These functions are used for SPI initialization, deinitialization, and data transmission. 

**Since:**

1.0

**Version:**

1.0

## **Summary**<a name="section878521838191857"></a>

## Data Structures<a name="nested-classes"></a>

<a name="table1173792106191857"></a>
<table><thead align="left"><tr id="row1623926920191857"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p47083962191857"><a name="p47083962191857"></a><a name="p47083962191857"></a>Data Structure Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1960181420191857"><a name="p1960181420191857"></a><a name="p1960181420191857"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row192848201191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1842219091191857"><a name="p1842219091191857"></a><a name="p1842219091191857"></a><a href="WifiIotSpiCfgBasicInfo.md">WifiIotSpiCfgBasicInfo</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1283439341191857"><a name="p1283439341191857"></a><a name="p1283439341191857"></a>Defines data communication parameters. </p>
</td>
</tr>
<tr id="row1717925572191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1935028825191857"><a name="p1935028825191857"></a><a name="p1935028825191857"></a><a href="WifiIotSpiCfgInitParam.md">WifiIotSpiCfgInitParam</a></p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p912455580191857"><a name="p912455580191857"></a><a name="p912455580191857"></a>Specifies whether a device is a master or slave device. </p>
</td>
</tr>
</tbody>
</table>

## Typedefs<a name="typedef-members"></a>

<a name="table279400056191857"></a>
<table><thead align="left"><tr id="row1020769595191857"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1430668881191857"><a name="p1430668881191857"></a><a name="p1430668881191857"></a>Typedef Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p875439481191857"><a name="p875439481191857"></a><a name="p875439481191857"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row712456426191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1358868276191857"><a name="p1358868276191857"></a><a name="p1358868276191857"></a><a href="Wifiiot.md#gad1acc3e9c9d1c63f70aeb9d5201ed1f0">SpiIsrFunc</a>) (void)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p496596547191857"><a name="p496596547191857"></a><a name="p496596547191857"></a> typedef void(*&nbsp;</p>
<p id="p916744108191857"><a name="p916744108191857"></a><a name="p916744108191857"></a>Indicates the SPI callback, which is used in <a href="Wifiiot.md#ga35305efc779b6386532fdb7a96fc5a1a">SpiRegisterUsrFunc</a>. </p>
</td>
</tr>
</tbody>
</table>

## Enumerations<a name="enum-members"></a>

<a name="table68599990191857"></a>
<table><thead align="left"><tr id="row1520132006191857"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p1698695849191857"><a name="p1698695849191857"></a><a name="p1698695849191857"></a>Enumeration Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p229732183191857"><a name="p229732183191857"></a><a name="p229732183191857"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1490632918191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1065102588191857"><a name="p1065102588191857"></a><a name="p1065102588191857"></a><a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> { <a href="Wifiiot.md#gga1d095e78d92cdf2ffc5e34443726e44ba3a13c86181ffb2c6927f86f423ec40b4">WIFI_IOT_SPI_ID_0</a> = 0, <a href="Wifiiot.md#gga1d095e78d92cdf2ffc5e34443726e44baeb87de3e3fe320957bc97c2fcc430da1">WIFI_IOT_SPI_ID_1</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p48207632191857"><a name="p48207632191857"></a><a name="p48207632191857"></a>Enumerates SPI channel IDs. </p>
</td>
</tr>
<tr id="row592076863191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1580265225191857"><a name="p1580265225191857"></a><a name="p1580265225191857"></a><a href="Wifiiot.md#gad6674c8b0989b6a329d5fd5ff0d5d750">WifiIotSpiCfgClockCpol</a> { <a href="Wifiiot.md#ggad6674c8b0989b6a329d5fd5ff0d5d750a07059b75b690958e26aa89a6004bf271">WIFI_IOT_SPI_CFG_CLOCK_CPOL_0</a>, <a href="Wifiiot.md#ggad6674c8b0989b6a329d5fd5ff0d5d750a0a0c2d8a56ac7fb1c965e496ef9d24fd">WIFI_IOT_SPI_CFG_CLOCK_CPOL_1</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1514729589191857"><a name="p1514729589191857"></a><a name="p1514729589191857"></a>Enumerates communication polarities. </p>
</td>
</tr>
<tr id="row1423288990191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1834718656191857"><a name="p1834718656191857"></a><a name="p1834718656191857"></a><a href="Wifiiot.md#ga1eb13cffbbdec9da1d57c766763b94e5">WifiIotSpiCfgClockCpha</a> { <a href="Wifiiot.md#gga1eb13cffbbdec9da1d57c766763b94e5af8cbca20bbbc6c065eae3cb21382d3b6">WIFI_IOT_SPI_CFG_CLOCK_CPHA_0</a>, <a href="Wifiiot.md#gga1eb13cffbbdec9da1d57c766763b94e5abd4a35c6cbe22a90892f1f877eb9be3f">WIFI_IOT_SPI_CFG_CLOCK_CPHA_1</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1723124806191857"><a name="p1723124806191857"></a><a name="p1723124806191857"></a>Enumerates communication phases. </p>
</td>
</tr>
<tr id="row20197199191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1244377543191857"><a name="p1244377543191857"></a><a name="p1244377543191857"></a><a href="Wifiiot.md#gaef7c192e049db14e2326c0bfba181670">WifiIotSpiCfgFramMode</a> { <a href="Wifiiot.md#ggaef7c192e049db14e2326c0bfba181670a3d7e1d60fe5cdf86cd72cca5e20109fb">WIFI_IOT_SPI_CFG_FRAM_MODE_MOTOROLA</a>, <a href="Wifiiot.md#ggaef7c192e049db14e2326c0bfba181670a8b16cdb5100d57654c512e88275c789d">WIFI_IOT_SPI_CFG_FRAM_MODE_TI</a>, <a href="Wifiiot.md#ggaef7c192e049db14e2326c0bfba181670a2f0198dff6d832a556a621b5de0606fc">WIFI_IOT_SPI_CFG_FRAM_MODE_MICROWIRE</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1245533784191857"><a name="p1245533784191857"></a><a name="p1245533784191857"></a>Enumerates communication protocols. </p>
</td>
</tr>
<tr id="row1233876120191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2014492231191857"><a name="p2014492231191857"></a><a name="p2014492231191857"></a><a href="Wifiiot.md#ga6f2e44db2698c33b81bd6caa438a55ea">WifiIotSpiCfgDataWidth</a> { &nbsp;&nbsp;<a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaaddfa282d58578fc81ac526987564e6ee">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_4BIT</a> = 0x3, <a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaa9de2e6dd354e226a820c079b8bac65b6">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_5BIT</a>, <a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaaa4144e7267c3a0417d8d0100cfcf50dd">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_6BIT</a>, <a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaa95f9ec882c23c6e61182dbc64a4204ff">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_7BIT</a>, &nbsp;&nbsp;<a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaa87c4e51ad22460a2ee1e8f4a818ab4d0">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_8BIT</a>, <a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaa1760c12ab9015525fa00483aa3ae6ce3">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_9BIT</a>, <a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaa2d5436642374f2e20544f4dd23b2a82e">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_10BIT</a>, <a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaa7de25e82ef22f3d7ecca7ba6740affaf">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_11BIT</a>, &nbsp;&nbsp;<a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaa7ef096c72549f4bdccd2da349928d197">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_12BIT</a>, <a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaadfa6793a7643c016f8946dbb6fefb393">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_13BIT</a>, <a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaaa10903f6e508f27f7290345ad77e8aad">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_14BIT</a>, <a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaa626cba1c95892d1265908e94b8df725a">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_15BIT</a>, &nbsp;&nbsp;<a href="Wifiiot.md#gga6f2e44db2698c33b81bd6caa438a55eaa3dba59e8d0c84fa68875aa4ff3988e9c">WIFI_IOT_SPI_CFG_DATA_WIDTH_E_16BIT</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1666434271191857"><a name="p1666434271191857"></a><a name="p1666434271191857"></a>Enumerates the communication data width, that is, the number of valid bits in each frame. </p>
</td>
</tr>
<tr id="row1623822614191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2097137585191857"><a name="p2097137585191857"></a><a name="p2097137585191857"></a><a href="Wifiiot.md#ga31924085df23a024413fa6e63e13c41e">WifiIotSpiCfgEndian</a> { <a href="Wifiiot.md#gga31924085df23a024413fa6e63e13c41ea68812944912ba0729ae0efeb2d126c2a">WIFI_IOT_SPI_CFG_ENDIAN_LITTLE</a>, <a href="Wifiiot.md#gga31924085df23a024413fa6e63e13c41eabed491171ca62fc1cfcc5d7b7b0413b1">WIFI_IOT_SPI_CFG_ENDIAN_BIG</a> }</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1695624044191857"><a name="p1695624044191857"></a><a name="p1695624044191857"></a>Enumerates the endian mode of each frame. </p>
</td>
</tr>
</tbody>
</table>

## Functions<a name="func-members"></a>

<a name="table346729196191857"></a>
<table><thead align="left"><tr id="row2077268498191857"><th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.1"><p id="p882557170191857"><a name="p882557170191857"></a><a name="p882557170191857"></a>Function Name</p>
</th>
<th class="cellrowborder" valign="top" width="50%" id="mcps1.1.3.1.2"><p id="p1502852253191857"><a name="p1502852253191857"></a><a name="p1502852253191857"></a>Description</p>
</th>
</tr>
</thead>
<tbody><tr id="row1017908223191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p544972471191857"><a name="p544972471191857"></a><a name="p544972471191857"></a><a href="Wifiiot.md#gabc5bfa19d08bcbd824a81cfdb476bc03">SpiSlaveWrite</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, char *writeData, unsigned int byteLen, unsigned int timeOutMs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p722013933191857"><a name="p722013933191857"></a><a name="p722013933191857"></a>unsigned int&nbsp;</p>
<p id="p1110194540191857"><a name="p1110194540191857"></a><a name="p1110194540191857"></a>Sends data in SPI slave mode. </p>
</td>
</tr>
<tr id="row804667765191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1897092600191857"><a name="p1897092600191857"></a><a name="p1897092600191857"></a><a href="Wifiiot.md#gaf6b980dbae9b819c801db16cd933379d">SpiSlaveRead</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, char *readData, unsigned int byteLen, unsigned int timeOutMs)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p864784018191857"><a name="p864784018191857"></a><a name="p864784018191857"></a>unsigned int&nbsp;</p>
<p id="p25059782191857"><a name="p25059782191857"></a><a name="p25059782191857"></a>Reads data in SPI slave mode. </p>
</td>
</tr>
<tr id="row1250779572191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1683689026191857"><a name="p1683689026191857"></a><a name="p1683689026191857"></a><a href="Wifiiot.md#ga9b550208916b4fa86385768cc81e0c5b">SpiHostWrite</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, char *writeData, unsigned int byteLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1362424277191857"><a name="p1362424277191857"></a><a name="p1362424277191857"></a>unsigned int&nbsp;</p>
<p id="p1651188237191857"><a name="p1651188237191857"></a><a name="p1651188237191857"></a>Sends data in half-duplex SPI master mode. </p>
</td>
</tr>
<tr id="row1099711881191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1978895992191857"><a name="p1978895992191857"></a><a name="p1978895992191857"></a><a href="Wifiiot.md#ga72b7cd1ad546f88982385c5ca054580d">SpiHostRead</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, char *readData, unsigned int byteLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1202009098191857"><a name="p1202009098191857"></a><a name="p1202009098191857"></a>unsigned int&nbsp;</p>
<p id="p1812199332191857"><a name="p1812199332191857"></a><a name="p1812199332191857"></a>Reads data in half-duplex SPI master mode. </p>
</td>
</tr>
<tr id="row902396758191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1323903483191857"><a name="p1323903483191857"></a><a name="p1323903483191857"></a><a href="Wifiiot.md#ga3ad87923c61c537f8366da76d6384dd1">SpiHostWriteread</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, char *writeData, char *readData, unsigned int byteLen)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2122862332191857"><a name="p2122862332191857"></a><a name="p2122862332191857"></a>unsigned int&nbsp;</p>
<p id="p2142088501191857"><a name="p2142088501191857"></a><a name="p2142088501191857"></a>Sends and reads data in full-duplex SPI master mode. </p>
</td>
</tr>
<tr id="row1081814650191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p2028095091191857"><a name="p2028095091191857"></a><a name="p2028095091191857"></a><a href="Wifiiot.md#ga7218dd7e5ae463ce2c29a6952c100893">SpiSetBasicInfo</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, const <a href="WifiIotSpiCfgBasicInfo.md">WifiIotSpiCfgBasicInfo</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1080294335191857"><a name="p1080294335191857"></a><a name="p1080294335191857"></a>unsigned int&nbsp;</p>
<p id="p1714879284191857"><a name="p1714879284191857"></a><a name="p1714879284191857"></a>Sets the SPI channel parameter. </p>
</td>
</tr>
<tr id="row1735299844191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1141881984191857"><a name="p1141881984191857"></a><a name="p1141881984191857"></a><a href="Wifiiot.md#gafb1a0999baf079d2907b73554f3fe458">SpiInit</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, <a href="WifiIotSpiCfgInitParam.md">WifiIotSpiCfgInitParam</a> initParam, const <a href="WifiIotSpiCfgBasicInfo.md">WifiIotSpiCfgBasicInfo</a> *param)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p267383664191857"><a name="p267383664191857"></a><a name="p267383664191857"></a>unsigned int&nbsp;</p>
<p id="p1078613680191857"><a name="p1078613680191857"></a><a name="p1078613680191857"></a>Initializes an SPI device. </p>
</td>
</tr>
<tr id="row617724963191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p332008562191857"><a name="p332008562191857"></a><a name="p332008562191857"></a><a href="Wifiiot.md#ga1e39213f9d9fa488eaf9f172ab675b24">SpiDeinit</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1336967274191857"><a name="p1336967274191857"></a><a name="p1336967274191857"></a>unsigned int&nbsp;</p>
<p id="p989409488191857"><a name="p989409488191857"></a><a name="p989409488191857"></a>Deinitializes an SPI device. </p>
</td>
</tr>
<tr id="row324605708191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1805653202191857"><a name="p1805653202191857"></a><a name="p1805653202191857"></a><a href="Wifiiot.md#gaea32f9be9e75da8ee8ae342c513ccbfb">SpiSetIrqMode</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, unsigned char irqEn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p2117350838191857"><a name="p2117350838191857"></a><a name="p2117350838191857"></a>unsigned int&nbsp;</p>
<p id="p237304231191857"><a name="p237304231191857"></a><a name="p237304231191857"></a>Sets whether to enable the interrupt request (IRQ) mode for an SPI device. </p>
</td>
</tr>
<tr id="row1432785067191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1155279580191857"><a name="p1155279580191857"></a><a name="p1155279580191857"></a><a href="Wifiiot.md#ga607d3d5b1f69cb89183566fb1d23f4cc">SpiSetDmaMode</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, unsigned char dmaEn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p745401202191857"><a name="p745401202191857"></a><a name="p745401202191857"></a>unsigned int&nbsp;</p>
<p id="p579787806191857"><a name="p579787806191857"></a><a name="p579787806191857"></a>Sets whether to enable DMA to transfer data for an SPI device in slave mode. </p>
</td>
</tr>
<tr id="row1674701607191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p153099255191857"><a name="p153099255191857"></a><a name="p153099255191857"></a><a href="Wifiiot.md#ga35305efc779b6386532fdb7a96fc5a1a">SpiRegisterUsrFunc</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, <a href="Wifiiot.md#gad1acc3e9c9d1c63f70aeb9d5201ed1f0">SpiIsrFunc</a> prepareF, <a href="Wifiiot.md#gad1acc3e9c9d1c63f70aeb9d5201ed1f0">SpiIsrFunc</a> restoreF)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1342436760191857"><a name="p1342436760191857"></a><a name="p1342436760191857"></a>unsigned int&nbsp;</p>
<p id="p360544965191857"><a name="p360544965191857"></a><a name="p360544965191857"></a>Registers the data TX preparation/recovery function. </p>
</td>
</tr>
<tr id="row1795278142191857"><td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.1 "><p id="p1620167226191857"><a name="p1620167226191857"></a><a name="p1620167226191857"></a><a href="Wifiiot.md#ga42dad507650369b456549515d73d75a1">SpiSetLoopBackMode</a> (<a href="Wifiiot.md#ga1d095e78d92cdf2ffc5e34443726e44b">WifiIotSpiIdx</a> spiId, unsigned char lbEn)</p>
</td>
<td class="cellrowborder" valign="top" width="50%" headers="mcps1.1.3.1.2 "><p id="p1871245474191857"><a name="p1871245474191857"></a><a name="p1871245474191857"></a>unsigned int&nbsp;</p>
<p id="p1605215172191857"><a name="p1605215172191857"></a><a name="p1605215172191857"></a>Sets whether to enable loopback test for an SPI device. </p>
</td>
</tr>
</tbody>
</table>

